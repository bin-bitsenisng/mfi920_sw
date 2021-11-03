#include <gst/gst.h>

static int 
input_parse (
    gchar **format,
    gchar **configpath,
    gchar **bbox_configpath,
    long *width,
    long *height,
    long *fps,
    const char **argv
)
{
  gchar *endptr1 = NULL, 
        *endptr2 = NULL, 
        *endptr3 = NULL;

  *width = g_ascii_strtoll (argv[1], &endptr1, 10);
  *height = g_ascii_strtoll (argv[2], &endptr2, 10);
  *fps = g_ascii_strtoll (argv[3], &endptr3, 10);

  *format = argv[4];
  if (   (*width == 0 && endptr1 == argv[1]) 
      || (*height == 0 && endptr2 == argv[2])
      || (*fps == 0 && endptr3 == argv[3])) {
    g_printerr ("Incorrect width, height or FPS\n");
    return -1;
  }

        g_print("%d %d %d\n", *width, *height, *fps);
  if (*width == 0 || *height == 0 || *fps == 0) {
    g_printerr ("Width, height or FPS cannot be 0\n");
    return -1;
  }

  if (  g_strcmp0 (*format, "I420") != 0 
        && g_strcmp0 (*format, "RGBA") != 0
        && g_strcmp0 (*format, "NV12") != 0) {

    g_printerr ("Only I420, RGBA and NV12 are supported\n");
    return -1;
  }

  // *filepath = argv[1];
  *configpath = argv[5];
  *bbox_configpath = argv[6];
  // g_print("filepath: %s\n", *filepath);
  g_print("configpath: %s\n", *configpath);
  g_print("bbox_configpath: %s\n", *bbox_configpath);
  return 0;
}