#include <gst/gst.h>

static int 
input_check(char argc, char **argv) {
  /* Check input arguments */
  if (argc != 8) {
    g_print("argc != 8\n");
    g_printerr
        ("Usage: %s <Raw filename> <width> <height> <fps> <format(I420, NV12, RGBA)> <nvinfer configpath> <bbox configpath>\n",
        argv[0]);
    return -1;
  }
  return 0;
}