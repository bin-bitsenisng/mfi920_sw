#include "vision.h"
#include "input_check.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "cv_bbox_draw.hpp"

int main (int argc, char *argv[])
{
        VisionCtx viCtx;
        GOptionContext *optCtx = NULL;
        GError *error = NULL;
        viCtx.use_videosink = FALSE;

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

        cv::Mat bgr;
        cv::Mat rgb;

        cv::namedWindow ("Display window");
        while (!viCtx.quit) {

                if (viCtx.obj_meta_list_update) {

                        g_mutex_lock (&viCtx.obj_meta_list_lock);
                        ((cv::Mat *)viCtx.bgr_image_data)->copyTo (bgr);
                        cv_bbox_draw (&viCtx, bgr);
                        cv::imshow ("Display window", bgr);
                        //cv::cvtColor (bgr, rgb, CV_BGR2RGB);
                        //g_print ("w: %d, h: %d\n", bgr.cols, bgr.rows);
                        //cv::imwrite ("tmp2.bmp", bgr);
                        g_mutex_unlock (&viCtx.obj_meta_list_lock);

                        int k = cv::waitKey (5); // Wait for a keystroke in the window
                        viCtx.obj_meta_list_update = FALSE;
                }
        }
        if (viCtx.bgr_image_data) {
                cv::Mat *tmp = (cv::Mat *)viCtx.bgr_image_data;
                delete tmp;
        }

        vision_unref_context (&viCtx);

        return 0;
}