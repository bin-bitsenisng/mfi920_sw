#include "deepstream_app.h"
#include "deepstream_config_file_parser.h"
#include "bbox_callback.h"
#include "overlay_graphics_callback.h"
#include <string.h>
#include <unistd.h>
#include <termios.h>

GST_DEBUG_CATEGORY (NVDS_APP);

int
main (int argc, char *argv[])
{
  AppCtx *appCtx;
  gint return_value = 0;
  gst_init (&argc, &argv);

  GST_DEBUG_CATEGORY_INIT (NVDS_APP, "NVDS_APP", 0, NULL);

  appCtx = g_malloc0 (sizeof (AppCtx));

  appCtx->cfg_file = argv[1];

  if (!appCtx->cfg_file) {
    NVGSTDS_ERR_MSG_V ("Specify config file");
    return_value = -1;
    goto done;
  }

  appCtx->person_class_id = 0;
  // appCtx->car_class_id = -1; // unused
  appCtx->index = 0;
  appCtx->active_source_index = -1;

  if (!parse_config_file (&appCtx->config, appCtx->cfg_file)) {
    NVGSTDS_ERR_MSG_V ("Failed to parse config file '%s'", appCtx->cfg_file);
    appCtx->return_value = -1;
    goto done;
  }

  if (!create_pipeline (appCtx, 
          NULL,
          all_bbox_generated, 
          NULL, 
          overlay_graphics)) { // TODO: how to share data with callback function?
    NVGSTDS_ERR_MSG_V ("Failed to create pipeline");
    return_value = -1;
    goto done;
  }

  appCtx->main_loop = g_main_loop_new (NULL, FALSE); // TODO: if main context exist, what happened?

  //_intr_setup ();
  //g_timeout_add (400, check_for_interrupt, (gpointer)appCtx);

  if (gst_element_set_state (appCtx->pipeline.pipeline,
          GST_STATE_PAUSED) == GST_STATE_CHANGE_FAILURE) {
    NVGSTDS_ERR_MSG_V ("Failed to set pipeline to PAUSED");
    return_value = -1;
    goto done;
  }

  /* Dont try to set playing state if error is observed */
  if (return_value != -1) {
      if (gst_element_set_state (appCtx->pipeline.pipeline,
              GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE) {

        g_print ("\ncan't set pipeline to playing state.\n");
        return_value = -1;
        goto done;
      }
  }

  g_main_loop_run (appCtx->main_loop); // TODO: async main loop run?


done:
  destroy_pipeline (appCtx);
  if (appCtx->main_loop) {
    g_main_loop_unref (appCtx->main_loop);
  }

  g_free (appCtx);
  gst_deinit ();

  return return_value;
}
