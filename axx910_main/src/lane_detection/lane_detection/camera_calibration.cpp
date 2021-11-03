#include "camera_calibration.h"
#include <iostream>
#include "../../rsp/axx910_sw/Source/ASW/SignalProcessing/Tracking/Trk_Parameters.h"

void CameraCalibrator::camToRadar(vector<cv::Point2f> left_point, vector<cv::Point2f> right_point, vector<cv::Point2f> &left_radar_point, vector<cv::Point2f> &right_radar_point)
{
	size_t left_point_size = left_point.size();
	size_t right_point_size = right_point.size();

	float cam_to_radar[] = { cos(extrinsic_angle_yaw), -sin(extrinsic_angle_yaw)*sin(extrinsic_angle_pitch), -sin(extrinsic_angle_yaw)*cos(extrinsic_angle_pitch),
							sin(extrinsic_angle_yaw), cos(extrinsic_angle_yaw)*sin(extrinsic_angle_pitch), cos(extrinsic_angle_yaw)*cos(extrinsic_angle_pitch),
							0, -cos(extrinsic_angle_pitch), sin(extrinsic_angle_pitch) };
	cv::Mat cam_to_radar_mat(3, 3, CV_64FC1, cam_to_radar);
	cv::Mat left_radar_mat, right_radar_mat;

	float cam_pos[] = { extrinsic_pos_x, extrinsic_pos_y, extrinsic_pos_z };
	cv::Mat cam_pos_mat(3, 1, CV_64FC1, cam_pos);

	for (size_t i = 0; i < left_point_size; i++)
	{
		float left_cam_point[] = { left_point[i].x - 320, left_point[i].y - 240, 1 };
		cv::Mat left_cam_mat(3, 1, CV_64FC1, left_cam_point);
		left_radar_mat = cam_to_radar_mat * left_cam_mat + cam_pos_mat;
		left_radar_point.push_back(cv::Point2f(left_radar_mat.at<double>(0, 0), left_radar_mat.at<double>(1, 0)));
	}

	for (size_t i = 0; i < right_point_size; i++)
	{
		float right_cam_point[] = { right_point[i].x - 320, right_point[i].y - 240, 1 };
		cv::Mat right_cam_mat(3, 1, CV_64FC1, right_cam_point);
		right_radar_mat = cam_to_radar_mat * right_cam_mat + cam_pos_mat;
		right_radar_point.push_back(cv::Point2f(right_radar_mat.at<double>(0, 0), right_radar_mat.at<double>(1, 0)));
	}
}

cv::Mat CameraCalibrator::getHomographyMat()
{
	float cam_intrinsic_mat[] = { cam_fx, 0, cam_cx, 0, cam_fy, cam_cy, 0, 0, 1 };
	cv::Mat camera_mat(3, 3, CV_64FC1, cam_intrinsic_mat);
	cv::Mat homography_mat;
	cv::Point2f src[4], dst[4];

	src[0] = cv::Point2f(0, 310);
	src[1] = cv::Point2f(640, 310);
	src[2] = cv::Point2f(250, 255);
	src[3] = cv::Point2f(400, 255);

	dst[0] = cv::Point2f(0, 480);
	dst[1] = cv::Point2f(640, 480);
	dst[2] = cv::Point2f(0, 0);
	dst[3] = cv::Point2f(640, 0);

	return homography_mat;
}