#ifndef _RADAR_H_
#define _RADAR_H_

#ifdef __cplusplus

#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"

//#include "Sp_Main.h"

#include "radar_device_cfg.h"

using namespace cv;

typedef struct radar_device {
    uint16_t* raw_data[NUM_OF_PINGPONG_BUFFER];
} RADAR_DEVICE;

void InitRadar(RADAR_DEVICE* radar_device);
void CaptureRadar(RADAR_DEVICE* radar_device);

#endif

#endif