#include "appsrc_data.h"

void 
appsrc_data_init (
    AppSrcData* data,
    const long width, 
    const long height, 
    const long fps, 
    const gchar* format, 
    const gchar* filepath)
{

  if (!g_strcmp0 (format, "RGBA")) {
    data->frame_size = width * height * 4;
    data->vidconv_format = "RGBA";

  } else {
    data->frame_size = width * height * 1.5;
    data->vidconv_format = "NV12";
  }

  data->file = fopen (filepath, "r");
  data->fps = fps;

  //g_print("%p\n", data->app_source);
  g_print("%d\n", data->frame_size);
  g_print("%s\n", data->vidconv_format);
  g_print("%p\n", data->file);
  g_print("%d\n", data->fps);

  // configure
  g_object_set (
      G_OBJECT (data->app_source), 
      "caps",
      gst_caps_new_simple (
          "video/x-raw",
          "format", G_TYPE_STRING, format,
          "width", G_TYPE_INT, width,
          "height", G_TYPE_INT, height,
          "framerate", GST_TYPE_FRACTION, data->fps, 1, NULL), 
      NULL);

  g_print("need-data\n");
  g_signal_connect (data->app_source, "need-data", G_CALLBACK (start_feed), data);
  g_print("enough-data\n");
  g_signal_connect (data->app_source, "enough-data", G_CALLBACK (stop_feed), data);
}

