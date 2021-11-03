#include <gst/gst.h>

int
input_parse (
    gchar **format,
    gchar **filepath,
    gchar **configpath,
    long *width,
    long *height,
    long *fps,
    const char **argv
);