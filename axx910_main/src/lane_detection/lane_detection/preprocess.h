#ifndef __PREPROCESS_H__
#define __PREPROCESS_H__

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

#define LOW_RESOLUTION 0

const double PI = 3.141592f;

class Preprocessor
{
private:
	cv::Mat image;
	cv::Mat perspective_mat;
	cv::Mat inverse_mat;
public:
	cv::Mat getImage()
	{
		return image;
	}

	cv::Mat getInverseMat()
	{
		return inverse_mat;
	}

	void scaleDownImage(cv::Mat image, cv::Mat &scale_down_image);
	void getWarpedImage(cv::Mat image, cv::Mat &warped_image, cv::Mat &unwarped_image);
	cv::Mat absSobelThresh(cv::Mat image, char orient = 'x', int thresh_min = 20, int thresh_max = 100);
	cv::Mat magThresh(cv::Mat image, int sobel_kernel = 3, pair<int, int> mag_thresh = make_pair(30, 100));
	cv::Mat dirThreshold(cv::Mat image, int sobel_kernel = 3, pair<double, double> thresh = make_pair(0, PI / 2));
	cv::Mat hlsThresh(cv::Mat image, pair<int, int> thresh = make_pair(100, 255));
	cv::Mat combinedThresh(cv::Mat image);
};

#endif