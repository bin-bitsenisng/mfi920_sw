#include "deepstream_app.h"

/**
 * callback function to add application specific metadata.
 * Here it demonstrates how to display the URI of source in addition to
 * the text generated after inference.
 */
static gboolean
overlay_graphics (AppCtx * appCtx, GstBuffer * buf,
    NvDsBatchMeta * batch_meta, guint index)
{
  int srcIndex = appCtx->active_source_index;
  if (srcIndex == -1)
    return TRUE;

  NvDsFrameLatencyInfo *latency_info = NULL;
  NvDsDisplayMeta *display_meta =
      nvds_acquire_display_meta_from_pool (batch_meta);

  display_meta->num_labels = 1;
  display_meta->text_params[0].display_text = g_strdup_printf ("Source: %s",
      appCtx->config.multi_source_config[srcIndex].uri);

  display_meta->text_params[0].y_offset = 20;
  display_meta->text_params[0].x_offset = 20;
  display_meta->text_params[0].font_params.font_color = (NvOSD_ColorParams) {
  0, 1, 0, 1};
  display_meta->text_params[0].font_params.font_size =
      appCtx->config.osd_config.text_size * 1.5;
  display_meta->text_params[0].font_params.font_name = "Serif";
  display_meta->text_params[0].set_bg_clr = 1;
  display_meta->text_params[0].text_bg_clr = (NvOSD_ColorParams) {
  0, 0, 0, 1.0};


  if(nvds_enable_latency_measurement) {
    g_mutex_lock (&appCtx->latency_lock);
    latency_info = &appCtx->latency_info[index];
    display_meta->num_labels++;
    display_meta->text_params[1].display_text = g_strdup_printf ("Latency: %lf",
        latency_info->latency);
    g_mutex_unlock (&appCtx->latency_lock);

    display_meta->text_params[1].y_offset = (display_meta->text_params[0].y_offset * 2 )+
      display_meta->text_params[0].font_params.font_size;
    display_meta->text_params[1].x_offset = 20;
    display_meta->text_params[1].font_params.font_color = (NvOSD_ColorParams) {
      0, 1, 0, 1};
    display_meta->text_params[1].font_params.font_size =
      appCtx->config.osd_config.text_size * 1.5;
    display_meta->text_params[1].font_params.font_name = "Arial";
    display_meta->text_params[1].set_bg_clr = 1;
    display_meta->text_params[1].text_bg_clr = (NvOSD_ColorParams) {
      0, 0, 0, 1.0};
  }

  nvds_add_display_meta_to_frame (nvds_get_nth_frame_meta (batch_meta->
          frame_meta_list, 0), display_meta);
  return TRUE;
}