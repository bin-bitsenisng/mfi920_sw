/************************************************************************
 | Project Name: AFI910
 |    File Name: inference_cfg.h
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

#ifndef _INFERENCE_CFG_H_
#define _INFERENCE_CFG_H_

// 640
//#define ANCHOR_FILE "../../../inference/anchor/20210324-bdd100k-yolov5s-640.json"
#define ANCHOR_FILE "../../../inference/anchor/20210521-bdd100k-yolov5s-1280.json"

//#define ENGINE_FILE "../../../inference/engine/20210324-bdd100k-yolov5s-fp16-640-aarch64.engine"
//#define ENGINE_FILE "../../../inference/engine/20210310-bdd100k-yolov5s-fp32-640-aarch64.engine"
//#define ENGINE_FILE "../../../inference/engine/20210521-bdd100k-yolov5s-fp16-1280-aarch64.engine"
//#define ENGINE_FILE "../../../inference/engine/20210521-bdd100k-yolov5s-1120.engine"
//#define ENGINE_FILE "../../../inference/engine/20210521-bdd100k-yolov5s-1024.engine"
#define ENGINE_FILE "../../../inference/engine/20210521-bdd100k-yolov5s-960.engine"

#define AI_INPUT_X  960
//#define AI_INPUT_X  1280
#define AI_INPUT_Y  AI_INPUT_X

#define INPUT_BLOB  "images"
//#define INPUT_BLOB  "data"
#define OUTPUT_BLOB  "output"
//#define OUTPUT_BLOB  "prob"

#define AI_OBJECT_MAX_SIZE  1000

#define DEFAULT_CONF_THRESHOLD  0.25
#define DEFAULT_NMS_THRESHOLD  0.6

#endif