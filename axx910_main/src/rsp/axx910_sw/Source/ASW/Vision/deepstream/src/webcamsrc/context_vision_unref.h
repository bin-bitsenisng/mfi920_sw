#include "context_vision.h"

gboolean
vision_unref_context (
        VisionCtx *viCtx)
{
        g_print ("Returned, stopping playback\n");
        gst_element_set_state (viCtx->pipeline, GST_STATE_NULL);

        g_print ("Deleting pipeline\n");
        gst_object_unref (viCtx->caps_filter_srcpad);
        gst_object_unref (viCtx->streammux_sinkpad);
        gst_object_unref (viCtx->nvinfer_srcpad);
        gst_object_unref (viCtx->tee_srcpad0);
        if (viCtx->use_videosink) {
                gst_object_unref (viCtx->tee_srcpad1);
                gst_object_unref (viCtx->nvosd_sinkpad);

        }

        gst_object_unref (GST_OBJECT (viCtx->pipeline));
        g_mutex_clear (&viCtx->obj_meta_list_lock);
        viCtx->quit = TRUE;
        return TRUE;
}