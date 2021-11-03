/************************************************************************
 | Project Name: AFI910
 |    File Name: cam_thread.h
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
 | 2021.02.05  0.0   mhkim   Creation;
 |***********************************************************************/

#ifndef _CAM_THREAD_H_
#define _CAM_THREAD_H_

#include "camera_device_cfg.h"
#include <stdint.h>

typedef struct
{
    uint32_t height;
    uint32_t width;
    uint32_t format;
    uint32_t size;
}cam_drv_camera_info_t;

typedef struct
{
	cam_drv_camera_info_t image_info;
	uint8_t image_buffer[CAM_IMAGE_SIZE_MAX];
}cam_drv_image_data_t;

typedef enum
{
	CAMERA_FORMAT_JPEG = 0,
	CAMERA_FORMAT_RAW,
	CAMERA_FORMAT_YUV422,
	CAMERA_FORMAT_NUM,
}cam_image_format;

void StartCAMthread(void);
void ServiceCAM(void);

#ifdef __cplusplus
extern "C" {
#endif
int32_t GetCamJpgFrame(uint8_t* dst_image_packet, uint32_t image_max_size, cam_drv_camera_info_t* frameinfo);
#ifdef __cplusplus
}
#endif

#endif