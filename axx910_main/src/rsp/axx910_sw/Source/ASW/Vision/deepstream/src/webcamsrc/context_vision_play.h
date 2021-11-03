#include "context_vision.h"

gboolean
vision_play_pipeline(VisionCtx *viCtx)
{
        // run
        // GST_DEBUG_BIN_TO_DOT_FILE (GST_BIN(pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "pipeline");
        g_print("vision_play_pipeline\n");
        gst_element_set_state(viCtx->pipeline, GST_STATE_PLAYING);
        return TRUE;
}