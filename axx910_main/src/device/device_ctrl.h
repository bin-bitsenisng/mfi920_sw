#ifndef _DEVICE_CTRL_H_
#define _DEVICE_CTRL_H_

#ifdef __cplusplus

#include "camera.h"
#include "radar.h"
#include "imu.h"
#include "gps.h"

#include "Sp_Main.h"

typedef struct device_list {
    //CAM_DEVICE camera_device;
    RADAR_DEVICE radar_device;
} DEVICE_LIST;

void InitDevices(DEVICE_LIST* device_list);
void GetDataFromDevices(DEVICE_LIST* device_list, MultiPRF_t curPRF);

#endif

#endif