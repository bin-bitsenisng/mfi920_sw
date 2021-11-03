#include <gst/gst.h>

static void
caps_filter_init(
    GstElement *caps_filter,
    const char *vidconv_format,
    const gint width,
    const gint height,
    const gint fps)
{
        g_print("caps_filter_init...\n");
        GstCaps *caps = NULL;
        GstCapsFeatures *feature = NULL;

        caps = gst_caps_new_simple(
            "video/x-raw",
            "format", G_TYPE_STRING, vidconv_format,
            "width", G_TYPE_INT, width,
            "height", G_TYPE_INT, height,
            "fps", G_TYPE_INT, fps,
            NULL);

        feature = gst_caps_features_new("memory:NVMM", NULL);

        gst_caps_set_features(caps, 0, feature);

        g_object_set(
            G_OBJECT(caps_filter),
            "caps", caps,
            NULL);
}