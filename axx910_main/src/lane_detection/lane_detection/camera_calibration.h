#ifndef CAMERA_CALIBRATION_H__
#define CAMERA_CALIBRATION_H__

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <vector>

using namespace std;

#define CALIB_PARAM_HEADER 1

#if CALIB_PARAM_HEADER
/* Camera calibration */
#define TRK_IMAGE_WIDTH							640
#define TRK_IMAGE_HEIGHT						480

#define TRK_CAMERA_INTRINSIC_FX					419.445700234415	/* Focal length in pixels [fx, fy] */
#define TRK_CAMERA_INTRINSIC_FY					420.414436015673	/* Focal length in pixels [fx, fy] */
#define TRK_CAMERA_INTRINSIC_CX					316.506822870493	/* Principle point (Optical center) [cx, cy] */
#define TRK_CAMERA_INTRINSIC_CY					248.358553260895	/* Principle point (Optical center) [cx, cy] */
#define TRK_CAMERA_INTRINSIC_K1					0.0285632334637935	/* Radial distortion */
#define TRK_CAMERA_INTRINSIC_K2					-0.0829532460166363	/* Radial distortion */
#define TRK_CAMERA_INTRINSIC_SKEW				0.0

#define TRK_CAMERA_EXTRINSIC_POS_X				0.0f
#define TRK_CAMERA_EXTRINSIC_POS_Y				0.0f
#define TRK_CAMERA_EXTRINSIC_POS_Z				0.5f
#define TRK_CAMERA_EXTRINSIC_ANGLE_YAW			0.0f
#define TRK_CAMERA_EXTRINSIC_ANGLE_PITCH		-0.1f
#define TRK_CAMERA_EXTRINSIC_ANGLE_ROLL			0.0f

#endif

class CameraCalibrator
{
private:
	float cam_fx;
	float cam_fy;
	float cam_cx;
	float cam_cy;
	float cam_k1;
	float cam_k2;
	float cam_skew;
	float extrinsic_pos_x;
	float extrinsic_pos_y;
	float extrinsic_pos_z;
	float extrinsic_angle_yaw;
	float extrinsic_angle_pitch;
	float extrinsic_angle_roll;
public:
	CameraCalibrator()
	{
		cam_fx = TRK_CAMERA_INTRINSIC_FX;
		cam_fy = TRK_CAMERA_INTRINSIC_FY;
		cam_cx = TRK_CAMERA_INTRINSIC_CX;
		cam_cy = TRK_CAMERA_INTRINSIC_CY;
		cam_k1 = TRK_CAMERA_INTRINSIC_K1;
		cam_k2 = TRK_CAMERA_INTRINSIC_K2;
		cam_skew = TRK_CAMERA_INTRINSIC_SKEW;

		extrinsic_pos_x = TRK_CAMERA_EXTRINSIC_POS_X;
		extrinsic_pos_y = TRK_CAMERA_EXTRINSIC_POS_Y;
		extrinsic_pos_z = TRK_CAMERA_EXTRINSIC_POS_Z;
		extrinsic_angle_yaw = TRK_CAMERA_EXTRINSIC_ANGLE_YAW * CV_PI / 180.0f;
		extrinsic_angle_pitch = TRK_CAMERA_EXTRINSIC_ANGLE_PITCH * CV_PI / 180.0f;
		extrinsic_angle_roll = TRK_CAMERA_EXTRINSIC_ANGLE_ROLL * CV_PI / 180.0f;
	}

	void camToRadar(vector<cv::Point2f> left_point, vector<cv::Point2f> right_point, vector<cv::Point2f> &left_radar_point, vector<cv::Point2f> &right_radar_point);
	cv::Mat getHomographyMat();
};

#endif