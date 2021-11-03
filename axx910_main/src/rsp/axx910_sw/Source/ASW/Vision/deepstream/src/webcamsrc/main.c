#include "vision.h"
#include "input_check.h"

int main (int argc, char* argv[])
{
        VisionCtx viCtx;
        GOptionContext* optCtx = NULL;
        GError* error = NULL;

        GOptionEntry entries[] = {
            {"nvinfer", 0, 0, G_OPTION_ARG_STRING, &viCtx.nvinfer_configpath, "nvinfer configpath", NULL},
            {"bbox", 0, 0, G_OPTION_ARG_STRING, &viCtx.bbox_configpath, "bbox configpath", NULL},
            {"format", 0, 0, G_OPTION_ARG_STRING, &viCtx.format, "image format", NULL},
            {"width", 'w', 0, G_OPTION_ARG_INT, &viCtx.width, "image width", NULL},
            {"height", 'h', 0, G_OPTION_ARG_INT, &viCtx.height, "image height", NULL},
            {"fps", 0, 0, G_OPTION_ARG_INT, &viCtx.fps, "fps", NULL},
            {"videosink", 'v', 0, G_OPTION_ARG_NONE, &viCtx.use_videosink, "Use videosink", NULL},
            {NULL} };

        optCtx = g_option_context_new ("library webcamsrc option context");

        g_option_context_add_main_entries (optCtx, entries, NULL);

        g_option_context_add_group (optCtx, gst_init_get_option_group ());

        if (!g_option_context_parse (optCtx, &argc, &argv, &error)) {
                g_print ("option parsing failed: %s\n", error->message);
                g_option_context_free (optCtx);
                exit (1);
        }
        input_check (&viCtx);
        vision_init_context (&viCtx);
        vision_play_pipeline (&viCtx);

        while (!viCtx.quit) {
                vision_monitor_pipeline (&viCtx);
        }

        vision_unref_context (&viCtx);

        return 0;
}