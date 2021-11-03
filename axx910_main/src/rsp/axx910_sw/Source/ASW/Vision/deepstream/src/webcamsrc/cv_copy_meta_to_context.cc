#include "cv_copy_meta_to_context.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>

static cv::Mat *bgr_image;

gboolean
copy_meta_to_context (VisionCtx *viCtx, NvDsBatchMeta *batch_meta, NvBufSurface *surface)
{
        gint n_frame = 0;

        // maybe you receive only 1 frame.
        for (NvDsMetaList *l_frame = batch_meta->frame_meta_list;
                l_frame != NULL;
                l_frame = l_frame->next) {


                NvDsFrameMeta *frame_meta = (NvDsFrameMeta *)(l_frame->data);
                gint frame_width = (gint)surface->surfaceList[frame_meta->batch_id].width;
                gint frame_height = (gint)surface->surfaceList[frame_meta->batch_id].height;
                void *frame_data = surface->surfaceList[frame_meta->batch_id].mappedAddr.addr[0];
                size_t frame_step = surface->surfaceList[frame_meta->batch_id].pitch;

                if (frame_data) {
                        viCtx->frame_height = frame_height;
                        viCtx->frame_width = frame_width;

                        viCtx->obj_meta_list = frame_meta->obj_meta_list;
        
                        g_mutex_lock (&viCtx->obj_meta_list_lock);
                        cv::Mat tmp = cv::Mat (cv::Size (frame_width, frame_height), CV_8UC4, (uchar *)frame_data, frame_step);
                        if(!bgr_image) {
                                bgr_image = new cv::Mat (cv::Size (frame_width, frame_height), CV_8UC3, frame_step);
                        }
                        cv::cvtColor (tmp, *bgr_image, cv::COLOR_RGBA2BGR);
                        viCtx->bgr_image_data = (u_char *)bgr_image;

                        viCtx->obj_meta_list_update = TRUE;
                        g_mutex_unlock (&viCtx->obj_meta_list_lock);
                        //viCtx->frame_step = rgba_image.step;


                }
                n_frame++;
        }
        if (n_frame > 1) {
                g_print ("n_frame > 1, something is wrong\n");
                return GST_FLOW_ERROR;

        }

        return GST_FLOW_OK;
}