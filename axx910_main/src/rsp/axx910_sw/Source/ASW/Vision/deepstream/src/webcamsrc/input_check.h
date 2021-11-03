#include <gst/gst.h>

static int
input_check (const VisionCtx* viCtx)
{
        if (viCtx->width == 0 || viCtx->height == 0 || viCtx->fps == 0) {
                g_printerr ("Width, height or FPS cannot be 0\n");
                return -1;
        }

        if (g_strcmp0 (viCtx->format, "I420") != 0 &&
                g_strcmp0 (viCtx->format, "RGBA") != 0 &&
                g_strcmp0 (viCtx->format, "NV12") != 0) {
                g_printerr ("Only I420, RGBA and NV12 are supported\n");
                return -1;
        }

        return 0;
}