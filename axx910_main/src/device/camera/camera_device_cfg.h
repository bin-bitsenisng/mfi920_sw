#ifndef _CAMERA_CFG_H_
#define _CAMERA_CFG_H_

#define CAMERA_DEVICE_NUM 8
#define CAMERA_API_PREFERENCE cv::CAP_V4L2

#define CAMERA_TYPE ARDU_CAM

#define WEB_CAM     0
#define ARDU_CAM    1

#define BIND_STRING "ipc:///tmp/cam_ipc"

#define CAM_IMAGE_SIZE_MAX		(8*1024*1024) // 8M

#define CAPTURE_RESOLUTION "VGA"
#define CAPTURE_WIDTH   640//1920
#define CAPTURE_HEIGHT  480//1080
#define FRAME_RATE      30
#define FLIP_METHOD     2

#endif