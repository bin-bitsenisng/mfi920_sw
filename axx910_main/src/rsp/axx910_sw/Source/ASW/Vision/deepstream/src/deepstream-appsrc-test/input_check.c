#include "input_check.h"

int input_check(char argc, char **argv) {
  /* Check input arguments */
  if (argc != 7) {
    g_printerr
        ("Usage: %s <Raw filename> <width> <height> <fps> <format(I420, NV12, RGBA)> <nvinfer configpath>\n",
        argv[0]);
    return -1;
  }
  return 0;
}