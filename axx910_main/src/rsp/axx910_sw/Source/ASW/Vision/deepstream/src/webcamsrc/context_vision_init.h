#include "context_vision.h"
#include "config_bbox.h"
#include "element_caps_filter.h"
#include "callback_probe_sink_nvinfer.h"
#include "callback_sample_appsink.h"

gboolean vision_init_context (
        VisionCtx* viCtx)
{
        g_mutex_init (&viCtx->obj_meta_list_lock);

        g_print ("gst_init\n");
        gst_init (&(viCtx->dummy_argc), &(viCtx->dummy_argv));

        viCtx->quit = FALSE;
        viCtx->obj_meta_list_update = FALSE;
        viCtx->pipeline = gst_pipeline_new ("webcamsrcpipeline");

        viCtx->webcamsrc = gst_element_factory_make ("v4l2src", "webcam_src");
        viCtx->nvvidconv1 = gst_element_factory_make ("nvvideoconvert", "nvvideo-converter1"); /* Use convertor to convert from software buffer to GPU buffer */

        viCtx->caps_filter = gst_element_factory_make ("capsfilter", "capsfilter");
        viCtx->caps_filter_srcpad = gst_element_get_static_pad (viCtx->caps_filter, "src");

        viCtx->streammux = gst_element_factory_make ("nvstreammux", "stream-muxer"); /* Create nvstreammux instance to form batches from one or more sources. */
        viCtx->streammux_sinkpad = gst_element_get_request_pad (viCtx->streammux, "sink_0");

        viCtx->nvinfer = gst_element_factory_make ("nvinfer", "primary-nvinference-engine");      /* Use nvinfer to run inferencing on streammux's output, behaviour of inferencing is set through config file */
        viCtx->nvinfer_srcpad = gst_element_get_static_pad (viCtx->nvinfer, "src");
        viCtx->nvvidconv2 = gst_element_factory_make ("nvvideoconvert", "nvvideo-converter2"); /* Use convertor to convert from NV12 to RGBA as required by nvdsosd */

        viCtx->tee = gst_element_factory_make ("tee", "tee"); 
        viCtx->tee_srcpad0 = gst_element_get_request_pad (viCtx->tee, "src_0");

        viCtx->appsink = gst_element_factory_make ("appsink", "app-sink");
        viCtx->appsink_sinkpad = gst_element_get_static_pad (viCtx->appsink, "sink");

        viCtx->bgr_image_data = NULL;


        // configure
        g_print ("configuring...\n");
        caps_filter_init (
                viCtx->caps_filter,
                viCtx->format,
                viCtx->width,
                viCtx->height,
                viCtx->fps);

        g_object_set (G_OBJECT (viCtx->streammux),
                "width", viCtx->width,
                "height", viCtx->height,
                "batch-size", 1,
                "live-source", TRUE,
                "batched-push-timeout", MUXER_BATCH_TIMEOUT_USEC,
                NULL);

        g_object_set (G_OBJECT (viCtx->nvinfer),
                "config-file-path", viCtx->nvinfer_configpath,
                NULL);

        config_bbox_parse (&(viCtx->bbox_config), viCtx->bbox_configpath);

        viCtx->nvinfer_srcpad_probe_id = gst_pad_add_probe (viCtx->nvinfer_srcpad, GST_PAD_PROBE_TYPE_BUFFER, callback_probe_src_nvinfer, viCtx, NULL);

        g_object_set (viCtx->appsink, 
                "emit-signals", TRUE, 
                "async", FALSE, NULL);

        g_signal_connect (viCtx->appsink, 
                "new-sample", G_CALLBACK (callback_ref_new_metadata), (gpointer) viCtx);

        // link
        g_print ("linking...\n");
        gst_bin_add_many (GST_BIN (viCtx->pipeline),
                viCtx->webcamsrc,
                viCtx->nvvidconv1,
                viCtx->caps_filter,
                viCtx->streammux,
                viCtx->nvinfer,
                viCtx->nvvidconv2,
                viCtx->tee,
                viCtx->appsink,
                NULL);

        if (gst_pad_link (viCtx->caps_filter_srcpad, viCtx->streammux_sinkpad) != (GST_PAD_LINK_OK)) {
                g_print ("viCtx->caps_filter_srcpad, viCtx->streammux_sinkpad\n");
                g_printerr ("Failed to link. Exiting.\n");
                viCtx->quit = TRUE;
                return FALSE;
        }

        if (!gst_element_link_many ( viCtx->webcamsrc, viCtx->nvvidconv1, viCtx->caps_filter, NULL) ||
                !gst_element_link_many ( viCtx->streammux, viCtx->nvinfer, viCtx->nvvidconv2, viCtx->tee, NULL)) {
                g_printerr ("Elements could not be linked: Exiting.\n");
                viCtx->quit = TRUE;
                return FALSE;
        }

        if (gst_pad_link (viCtx->tee_srcpad0, viCtx->appsink_sinkpad) != (GST_PAD_LINK_OK)) {
                g_print ("viCtx->tee_srcpad0, viCtx->appsink_sinkpad\n");
                g_printerr ("Failed to link. Exiting.\n");
                viCtx->quit = TRUE;
                return FALSE;
        } 
        

        if (viCtx->use_videosink) {
                viCtx->tee_srcpad1 = gst_element_get_request_pad (viCtx->tee, "src_1");

                viCtx->nvosd = gst_element_factory_make ("nvdsosd", "nv-onscreendisplay");             /* Create OSD to draw on the converted RGBA buffer */
                viCtx->nvosd_sinkpad = gst_element_get_static_pad (viCtx->nvosd, "sink");
                
                viCtx->transform = gst_element_factory_make ("nvegltransform", "nvegl-transform");     /* Video transform element for NVMM to EGLimage (supported with nveglglessink only) */
                viCtx->videosink = gst_element_factory_make ("nveglglessink", "nvvideo-renderer");

                gst_bin_add_many (GST_BIN (viCtx->pipeline),
                        viCtx->nvosd,
                        viCtx->transform,
                        viCtx->videosink,
                        NULL);

                if (!gst_element_link_many (
                        viCtx->nvosd,
                        viCtx->transform,
                        viCtx->videosink, NULL)) {
                        g_printerr ("Elements could not be linked: Exiting.\n");
                        viCtx->quit = TRUE;
                        return FALSE;
                }

                if (gst_pad_link (viCtx->tee_srcpad1, viCtx->nvosd_sinkpad) != (GST_PAD_LINK_OK)) {
                        g_printerr ("Failed to link. Exiting.\n");
                        viCtx->quit = TRUE;
                        return FALSE;
                } 
        } 

        return TRUE;
}