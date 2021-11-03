/************************************************************************
 | Project Name: AFI910
 |    File Name: inference.h
 |  Description: detailed Description
 |-----------------------------------------------------------------------
 |               A U T H O R   I D E N T I T Y
 |-----------------------------------------------------------------------
 | Initials     Name                      Company                        
 | --------     ---------------------     -------------------------------
 | MHKIM        Myoungha Kim              bitsensing Corporation
 |-----------------------------------------------------------------------
 |              R E V I S I O N   H I S T O R Y
 |-----------------------------------------------------------------------
 | Date         Ver  Author  Description                                 
 | ----------  ----  ------  --------------------------------------------
 | 2021.02.01  0.0   mhkim   Creation;
 |***********************************************************************/

#ifndef _INFERENCE_H_
#define _INFERENCE_H_

#ifdef __cplusplus
#include "opencv2/opencv.hpp"
#endif

#include "inference_cfg.h"
#include <stdint.h>

typedef struct 
{
    uint32_t Ai_num_of_class;
    uint32_t Ai_class_id;
    float Ai_confidence;
    uint32_t Ai_height;
    uint32_t Ai_width;
    uint32_t Ai_x_location;
    uint32_t Ai_y_location;
} ai_object_t;

extern ai_object_t ai_object[AI_OBJECT_MAX_SIZE];

void InitInference(double confThresh, double nmsThresh);
#ifdef __cplusplus
cv::Mat Inference(cv::Mat img);
#endif

#endif