#include "caps_filter_init.h"

void
caps_filter_init (
    GstElement *caps_filter,
    const char *vidconv_format
)
{
  GstCaps *caps = NULL;
  GstCapsFeatures *feature = NULL;

  caps = gst_caps_new_simple (
            "video/x-raw",
            "format", G_TYPE_STRING, vidconv_format, 
            NULL);

  feature = gst_caps_features_new ("memory:NVMM", NULL);

  gst_caps_set_features (caps, 0, feature);

  g_object_set (
            G_OBJECT (caps_filter), 
            "caps", caps, 
            NULL);
}