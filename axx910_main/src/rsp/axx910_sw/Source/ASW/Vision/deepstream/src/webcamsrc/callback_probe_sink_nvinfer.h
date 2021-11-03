#include <gst/gst.h>
#include "context_vision.h"
#include <stdlib.h>



static void
__change_bbox_color_for_class_id(
        NvDsObjectMeta *obj,
        BboxConfig *config
)
{
        g_assert (config != NULL);
        g_assert (obj != NULL);

        if (g_hash_table_contains (config->border_color_table, obj->class_id + (gchar *)NULL)) {
                obj->rect_params.border_color = *((NvOSD_ColorParams *)g_hash_table_lookup(
                                                                        config->border_color_table,
                                                                        obj->class_id + (gchar *)NULL));
                // g_print("hash table contains\n");
                // g_print("class_id: %d\n", obj->class_id);
        }
        else {
                obj->rect_params.border_color = config->border_color;
                // g_print("hash table doesn't contains\n");
        }

        obj->rect_params.border_width = config->border_width;
}

static void
process_meta(VisionCtx *viCtx, NvDsBatchMeta *batch_meta)
{
        for (   NvDsMetaList *l_frame = batch_meta->frame_meta_list; 
                l_frame != NULL;
                l_frame = l_frame->next) {

                NvDsFrameMeta *frame_meta = (NvDsFrameMeta *)(l_frame->data);

                g_mutex_lock(&viCtx->obj_meta_list_lock);
                for (   NvDsMetaList *l_obj = frame_meta->obj_meta_list; 
                        l_obj != NULL;
                        l_obj = l_obj->next) {
                        
                        __change_bbox_color_for_class_id(
                                (NvDsObjectMeta *)(l_obj->data),
                                &(viCtx->bbox_config)
                        );
                }
                //viCtx->obj_meta_list = frame_meta->obj_meta_list;
                //viCtx->obj_meta_list_update = TRUE;
                g_mutex_unlock(&viCtx->obj_meta_list_lock);
        }
}

/**
 * Function which processes the inferred buffer and its metadata.
 * It also gives opportunity to attach application specific
 * metadata (e.g. clock, analytics output etc.).
 */
static void
process_buffer(GstBuffer *buf, VisionCtx *viCtx)
{
        NvDsBatchMeta *batch_meta = gst_buffer_get_nvds_batch_meta(buf);
        if (!batch_meta)
        {
                g_print("Batch meta not found for buffer %p\n", buf);
                return;
        }
        process_meta(viCtx, batch_meta);
}

/**
 * Probe function to get results after all inferences(Primary + Secondary)
 * are done. This will be just before OSD or sink (in case OSD is disabled).
 */
static GstPadProbeReturn
callback_probe_src_nvinfer(
    GstPad *pad,
    GstPadProbeInfo *info,
    gpointer _data)
{
        GstBuffer *buf = (GstBuffer *)info->data;
        VisionCtx *viCtx = (VisionCtx *)_data;

        if (gst_buffer_is_writable(buf))
                process_buffer(buf, viCtx);
        return GST_PAD_PROBE_OK;
}