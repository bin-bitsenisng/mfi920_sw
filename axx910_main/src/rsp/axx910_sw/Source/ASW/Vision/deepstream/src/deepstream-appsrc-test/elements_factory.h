#include <gst/gst.h>

int 
get_element (
    GstElement **element,
    const gchar *factoryname,
    const gchar *name
);