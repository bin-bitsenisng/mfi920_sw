#ifndef __VISION_CONTEXT_H__
#define __VISION_CONTEXT_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "common.h"
#include <gst/app/gstappsink.h>

        /* Muxer batch formation timeout, for e.g. 40 millisec. Should ideally be set
         * based on the fastest source's framerate. */
#define MUXER_BATCH_TIMEOUT_USEC 33000 // 33ms

        struct _VisionCtx
        {
                int dummy_argc;
                char **dummy_argv;

                GstElement *pipeline;
                GstElement *webcamsrc;
                GstElement *nvvidconv1;

                GstElement *caps_filter;
                GstPad *caps_filter_srcpad;

                GstElement *streammux;
                GstPad *streammux_sinkpad;

                GstElement *nvinfer;
                GstPad *nvinfer_srcpad;
                gulong nvinfer_srcpad_probe_id;
                GstElement *nvvidconv2;

                GstElement *tee;
                GstPad *tee_srcpad0;
                GstPad *tee_srcpad1;

                GstElement *appsink;
                GstPad *appsink_sinkpad;

                GstElement *nvosd;
                GstPad *nvosd_sinkpad;

                GstElement *transform;
                GstElement *videosink;

                //GstBus *bus;
                //guint bus_watch_id;


                // configs
                gchar *nvinfer_configpath;
                gchar *bbox_configpath;
                gchar *format;
                gint width;
                gint height;
                gint fps;
                gboolean use_videosink;

                BboxConfig bbox_config;


                // state
                gboolean quit;
                gboolean obj_meta_list_update;
                NvDsObjectMetaList *obj_meta_list;
                GMutex obj_meta_list_lock;
                u_char *rgba_image_data;
                u_char *bgr_image_data;
                gint frame_width;
                gint frame_height;
                size_t frame_step;
        };

        typedef struct _VisionCtx VisionCtx;

#ifdef __cplusplus
}
#endif

#endif