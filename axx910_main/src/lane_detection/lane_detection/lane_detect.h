#ifndef __LANEDETECT_H__
#define __LANEDETECT_H__

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;

class LaneDetector
{
private:
	int bottom_leftx_base;
	int bottom_rightx_base;
	int top_leftx_base;
	int top_rightx_base;
	float max_detect_range;
	cv::Mat image;
	cv::Mat draw_image;
	vector<float> lane_pointx;
	vector<vector<float>> left_inds_set;
	vector<vector<float>> right_inds_set;
	map<string, vector<float>> lane_data;
	vector<float> nonzerox;
	vector<float> nonzeroy;
	vector<float> fit_result;
public:
	void getLaneBase(cv::Mat image);
	cv::Mat polyfit(vector<float> pointx, vector<float> pointy, int n);
	cv::Mat polyfit(vector<cv::Point2f> point, int n);
	cv::Mat multiplyMat(cv::Mat a, cv::Mat b);
	void laneFit(cv::Mat image, map<string, vector<float>> &lane_data, vector<cv::Point2f> &left_point, vector<cv::Point2f> &right_point, cv::Mat &draw_image);
	void trackLane(cv::Mat image, vector<float> leftfit, vector<float> rightfit, map<string, vector<float>> &lane_data);
	void drawResult(map<string, vector<float>> lane_data, cv::Mat &draw_image, cv::Mat &input_warped_image);
	cv::Mat getLaneDetectedImage(cv::Mat warped_image, cv::Mat unwarped_image, cv::Mat warped_inverse_mat, cv::Mat &lane_image);
};

#endif