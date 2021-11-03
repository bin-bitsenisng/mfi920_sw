#include "context_vision.h"
#include "gstnvdsmeta.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

static gboolean
cv_bbox_draw(VisionCtx *viCtx, cv::Mat mat)
{
        if (FALSE == viCtx->obj_meta_list_update)
        {
                return FALSE;
        }

        gint obj_idx = 0;
        for (NvDsMetaList *l_obj = viCtx->obj_meta_list;
             l_obj != NULL;
             l_obj = l_obj->next)
        {
                NvDsObjectMeta *obj = (NvDsObjectMeta *)l_obj->data;
                //g_print("%dth class id: %d\n", obj_idx, obj->class_id);
                if (obj->class_id == 2) {
                        NvBbox_Coords &_bbox = obj->detector_bbox_info.org_bbox_coords;
                        cv::Rect bbox_cords = cv::Rect (_bbox.left, _bbox.top, _bbox.width, _bbox.height);
                        cv::rectangle (mat, bbox_cords, cv::Scalar (0, 0, 255));
                }

                obj_idx += 1;
        }

        return TRUE;
}