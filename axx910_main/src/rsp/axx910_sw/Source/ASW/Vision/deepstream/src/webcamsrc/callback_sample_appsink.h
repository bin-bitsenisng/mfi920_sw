#include <gst/gst.h>
#include "context_vision.h"
#include <stdlib.h>
#include <gst/app/gstappsink.h>
#include "nvbufsurface.h"
#include "cv_copy_meta_to_context.h"

/* new_sample is an appsink callback that will extract metadata received
 * tee sink pad and update params for drawing rectangle,
 *object information etc. */


static GstFlowReturn
callback_ref_new_metadata (GstAppSink *appsink, gpointer data)
{
        GstSample *sample;
        GstBuffer *buf = NULL;
        GstMapInfo map;
        NvBufSurface *surface = NULL;
        NvDsMetaList *l_frame = NULL;
        NvDsMetaList *l_obj = NULL;
        gint n_frame = 0;
        gboolean ret;


        VisionCtx *viCtx = (VisionCtx *)data;
        sample = gst_app_sink_pull_sample (appsink);
        // buf_raw_img = gst_app_sink_pull_buffer (appsink);
        memset (&map, 0, sizeof (GstMapInfo));

        // viCtx->bgr_image_data = NULL;

        if (gst_app_sink_is_eos (appsink)) {
                g_print ("EOS received in Appsink********\n");
        }

        if (!sample) {
                g_print ("sample empty\n");
                return GST_FLOW_ERROR;
        }

        /* Obtain GstBuffer from sample and then extract metadata from it. */
        buf = gst_sample_get_buffer (sample);
        ret = gst_buffer_map (buf, &map, GST_MAP_READ);
        if (!ret) {
                g_print ("error in gst_buffer_map\n");
                return GST_FLOW_ERROR;
        }

        if (map.data) {
                surface = (NvBufSurface *)map.data;
                NvBufSurfaceMap (surface, -1, -1, NVBUF_MAP_READ);
                NvBufSurfaceSyncForCpu (surface, -1, -1);

                NvDsBatchMeta *batch_meta = gst_buffer_get_nvds_batch_meta (buf);
                ret = copy_meta_to_context (viCtx, batch_meta, surface);
                if (ret) {
                        g_print ("error in copy_meta_to_context: %d\n", ret);
                        return GST_FLOW_ERROR;
                }

                NvBufSurfaceUnMap (surface, -1, -1);
        }
        gst_buffer_unmap (buf, &map);
        gst_sample_unref (sample);
        return GST_FLOW_OK;
}
