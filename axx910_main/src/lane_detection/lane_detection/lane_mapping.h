#ifndef __LANEMAPPING_H__
#define __LANEMAPPING_H__

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "preprocess.h"
#include "lane_detect.h"

using namespace std;

#define LOW_RESOLUTION 0

class LaneMapper
{
private:
	cv::Mat m_Image;
public:
	void getRadarPoint(vector<cv::Point2f> left_point, vector<cv::Point2f> right_point, vector<cv::Point2f> &left_radar_point, vector<cv::Point2f> &right_radar_point);
	vector<vector<cv::Point2f>> getRadarPoint(int numOfLane, map<string, vector<float>> laneData);
};

#endif