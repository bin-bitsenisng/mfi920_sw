#include <gst/gst.h>
#include <glib.h>
#include <stdio.h>
#include <string.h>
#include "gstnvdsmeta.h"

// local
#include "app_context.h"
#include "input_check.h"
#include "input_parse.h"
#include "element_source_app.h"
#include "element_caps_filter.h"
#include "callback_bus.h"
#include "callback_probe_sink_nvinfer.h"
  
#include <signal.h>

/* Muxer batch formation timeout, for e.g. 40 millisec. Should ideally be set
 * based on the fastest source's framerate. */
#define MUXER_BATCH_TIMEOUT_USEC 33000

AppCtx appCtx;


static gpointer 
event_loop_thread(gpointer arg) 
{
    AppCtx *appCtx = (AppCtx *)arg;


    GMainLoop 
        *loop = NULL;
    GstElement 
        *pipeline    = NULL,
        *nvvidconv1  = NULL,
        *caps_filter = NULL,
        *streammux   = NULL,
        *sink        = NULL,
        *pgie        = NULL,
        *nvvidconv2  = NULL,
        *nvosd       = NULL,
        *transform   = NULL;
    GstBus     
        *bus         = NULL;
    guint bus_watch_id;

    GstPad
        *infer_source_pad = NULL,
        *srcpad = NULL,
        *sinkpad = NULL; 

    gulong nvinfer_src_pad_probe_id; 

    AppSrcData data;

    long 
        width  = 0,
        height = 0,
        fps    = 0;

    gchar 
        *format     = NULL,
        *filepath   = NULL,
        *configpath = NULL,
        *bbox_configpath = NULL;

    if ( input_check ((appCtx->argc), (appCtx->argv)) == -1 ) {
        appCtx->quit = TRUE; 
        return NULL;
    }
    if ( input_parse ( &format, &filepath, &configpath, &bbox_configpath, &width, &height, &fps, (const char**)(appCtx->argv)) == -1 ) {
        appCtx->quit = TRUE; 
        return NULL;
    }


    /* Initialize GStreamer */
    g_print("initializing...\n");
    gst_init (&(appCtx->argc), &(appCtx->argv));
    loop = g_main_loop_new (appCtx->context, FALSE);
    appCtx->loop = loop;
    g_main_context_push_thread_default (appCtx->context);

    memset (&data, 0, sizeof(data));
    pipeline        = gst_pipeline_new        ( "dstest-appsrc-pipeline"                                );
    data.app_source = gst_element_factory_make( "appsrc"                 , "app-source"                 ); /* App Source element for reading from raw video file */
    nvvidconv1      = gst_element_factory_make( "nvvideoconvert"         , "nvvideo-converter1"         ); /* Use convertor to convert from software buffer to GPU buffer */
    caps_filter     = gst_element_factory_make( "capsfilter"             , "capsfilter"                 );
    srcpad           = gst_element_get_static_pad  (caps_filter , "src"    );
    streammux       = gst_element_factory_make( "nvstreammux"            , "stream-muxer"               ); /* Create nvstreammux instance to form batches from one or more sources. */
    sinkpad          = gst_element_get_request_pad (streammux   , "sink_0" );
    pgie            = gst_element_factory_make( "nvinfer"                , "primary-nvinference-engine" ); /* Use nvinfer to run inferencing on streammux's output, behaviour of inferencing is set through config file */
    nvvidconv2      = gst_element_factory_make( "nvvideoconvert"         , "nvvideo-converter2"         ); /* Use convertor to convert from NV12 to RGBA as required by nvdsosd */
    nvosd           = gst_element_factory_make( "nvdsosd"                , "nv-onscreendisplay"         ); /* Create OSD to draw on the converted RGBA buffer */
    transform       = gst_element_factory_make( "nvegltransform"         , "nvegl-transform"            ); /* Video transform element for NVMM to EGLimage (supported with nveglglessink only) */
    sink            = gst_element_factory_make( "nveglglessink"          , "nvvideo-renderer"           );

    infer_source_pad = gst_element_get_static_pad  (pgie, "src"   );

    // configure
    g_print("configuring...\n");
    appsrc_data_init (&data, width, height, fps, format, filepath);
    caps_filter_init (caps_filter, data.vidconv_format);

    g_object_set (G_OBJECT (streammux), 
                                        "width"               , width                   ,
                                        "height"              , height                  ,
                                        "batch-size"          , 1                       ,
                                        "live-source"         , TRUE                    ,
                                        "batched-push-timeout", MUXER_BATCH_TIMEOUT_USEC, 
                                        NULL);
    g_object_set (G_OBJECT (pgie),
                                        "config-file-path",     configpath, 
                                        NULL);

    bus          = gst_pipeline_get_bus (     GST_PIPELINE (pipeline)); /* we add a message handler */
    bus_watch_id = gst_bus_add_watch    (bus, callback_bus, loop     );

    nvinfer_src_pad_probe_id = gst_pad_add_probe(infer_source_pad, GST_PAD_PROBE_TYPE_BUFFER, callback_probe_sink_nvinfer, appCtx, NULL);

    config_bbox_parse (&(appCtx->bbox_config), bbox_configpath);

    // link
    g_print("linking...\n");
    gst_bin_add_many (GST_BIN (pipeline),
                                        data.app_source, 
                                        nvvidconv1, caps_filter, streammux, pgie,
                                        nvvidconv2, nvosd, sink, transform, 
                                        NULL);

    if (gst_pad_link (srcpad         , sinkpad     ) != (GST_PAD_LINK_OK)) {
        g_printerr ("Failed to link. Exiting.\n"); 
        appCtx->quit = TRUE; 
        return NULL;
    }
    if (!gst_element_link_many (data.app_source, nvvidconv1, caps_filter, NULL) ||
        !gst_element_link_many (streammux, pgie, nvvidconv2, nvosd, transform, sink, NULL)) {
        g_printerr ("Elements could not be linked: Exiting.\n");
        appCtx->quit = TRUE; 
        return NULL;
    }

    // run

    GST_DEBUG_BIN_TO_DOT_FILE (GST_BIN(pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline");

    g_print ("Now playing: %s\n", filepath);
    gst_element_set_state (pipeline, GST_STATE_PLAYING);

    g_print ("Running...\n");
    g_main_loop_run (loop);


    // final
    g_print ("Returned, stopping playback\n");
    gst_element_set_state (pipeline, GST_STATE_NULL);

    g_print           ("Deleting pipeline\n");
    gst_object_unref  (bus                  );
    gst_object_unref  (srcpad               );
    gst_object_unref  (sinkpad              );
    gst_object_unref   (infer_source_pad);
    gst_object_unref  (GST_OBJECT (pipeline));
    g_source_remove   (bus_watch_id         );
    g_main_loop_unref (loop                 );
    appCtx->quit = TRUE;
    return NULL;
}


int init(AppCtx* appCtx)
{
    appCtx->context = g_main_context_default();
    g_thread_new(NULL, event_loop_thread, (gpointer)appCtx);
    return 0;
}


void intHandler(int dummy) {
    g_print("intHandler called.\n");
    g_main_loop_quit(appCtx.loop);
}


int main(int argc, char *argv[])
{
    appCtx.argc = argc;
    appCtx.argv = argv;
    appCtx.cnt = 0;
    appCtx.quit = FALSE;

    init(&appCtx);

    signal(SIGINT, intHandler);
    while (!appCtx.quit);    
    g_print("quit\n");

    return 0;
} 