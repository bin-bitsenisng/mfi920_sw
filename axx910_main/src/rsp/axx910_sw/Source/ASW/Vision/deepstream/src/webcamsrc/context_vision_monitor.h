#include "context_vision.h"
#include "gstnvdsmeta.h"

gboolean
vision_monitor_pipeline(VisionCtx *viCtx)
{
        if (FALSE == viCtx->obj_meta_list_update)
        {
                return FALSE;
        }
        // g_print ("vision_monitor pipeline\n");
        gint obj_idx = 0;
        for (NvDsMetaList *l_obj = viCtx->obj_meta_list;
             l_obj != NULL;
             l_obj = l_obj->next)
        {
                NvDsObjectMeta *obj = (NvDsObjectMeta *)l_obj->data;
                g_print("%dth class id: %d\n", obj_idx, obj->class_id);
                obj_idx += 1;
        }
        viCtx->obj_meta_list_update = FALSE;
        return TRUE;
}
