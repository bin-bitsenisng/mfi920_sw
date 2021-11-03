#include <gst/gst.h>
#include <gst/app/gstappsrc.h>
#include <stdio.h>

/* Structure to contain all our information for appsrc,
 * so we can pass it to callbacks */
typedef struct _AppSrcData
{
        GstElement *app_source;
        long frame_size;
        FILE *file; /* Pointer to the raw video file */
        gint appsrc_frame_num;
        guint fps;      /* To set the FPS value */
        guint sourceid; /* To control the GSource */
        gchar *vidconv_format;
} AppSrcData;

static gboolean
read_data(AppSrcData *data)
{
        GstBuffer *buffer;
        GstFlowReturn gstret;

        size_t ret = 0;
        GstMapInfo map;
        buffer = gst_buffer_new_allocate(NULL, data->frame_size, NULL);

        gst_buffer_map(buffer, &map, GST_MAP_WRITE);
        ret = fread(map.data, 1, data->frame_size, data->file);
        map.size = ret;

        gst_buffer_unmap(buffer, &map);
        if (ret > 0) {
                GST_BUFFER_PTS(buffer) =
                    gst_util_uint64_scale(data->appsrc_frame_num, GST_SECOND, data->fps);
                gstret = gst_app_src_push_buffer((GstAppSrc *)data->app_source, buffer);

                if (gstret != GST_FLOW_OK) {
                        g_print("gst_app_src_push_buffer returned %d \n", gstret);
                        return FALSE;
                }
        }
        else if (ret == 0) {
                gstret = gst_app_src_end_of_stream((GstAppSrc *)data->app_source);
                if (gstret != GST_FLOW_OK) {
                        g_print("gst_app_src_end_of_stream returned %d. EoS not queued successfully.\n",
                                gstret);
                        return FALSE;
                }
        }
        else {
                g_print("\n failed to read from file\n");
                return FALSE;
        }
        data->appsrc_frame_num++;

        return TRUE;
}

/* This signal callback triggers when appsrc needs data. Here,
 * we add an idle handler to the mainloop to start pushing
 * data into the appsrc */
static void
start_feed(
    GstElement *source,
    guint size,
    AppSrcData *data)
{
        if (data->sourceid == 0)
        {
                data->sourceid = g_idle_add((GSourceFunc)read_data, data);
        }
}

/* This callback triggers when appsrc has enough data and we can stop sending.
 * We remove the idle handler from the mainloop */
static void
stop_feed(
    GstElement *source,
    AppSrcData *data)
{
        if (data->sourceid != 0)
        {
                g_source_remove(data->sourceid);
                data->sourceid = 0;
        }
}

static void
appsrc_data_init(
    AppSrcData *data,
    const long width,
    const long height,
    const long fps,
    const gchar *format,
    const gchar *filepath)
{
        g_print("appsrc_data_init...\n");

        if (!g_strcmp0(format, "RGBA"))
        {
                data->frame_size = width * height * 4;
                data->vidconv_format = "RGBA";
        }
        else
        {
                data->frame_size = width * height * 1.5;
                data->vidconv_format = "NV12";
        }

        data->file = fopen(filepath, "r");
        data->fps = fps;

        //g_print("%p\n", data->app_source);
        // g_print("%ld\n", data->frame_size);
        // g_print("%s\n", data->vidconv_format);
        // g_print("%p\n", data->file);
        // g_print("%d\n", data->fps);

        // configure
        g_object_set(
            G_OBJECT(data->app_source),
            "caps",
            gst_caps_new_simple(
                "video/x-raw",
                "format", G_TYPE_STRING, format,
                "width", G_TYPE_INT, width,
                "height", G_TYPE_INT, height,
                "framerate", GST_TYPE_FRACTION, data->fps, 1, NULL),
            NULL);

        g_signal_connect(data->app_source, "need-data", G_CALLBACK(start_feed), data);
        g_signal_connect(data->app_source, "enough-data", G_CALLBACK(stop_feed), data);
}
