#include <iostream>
#include <chrono>
#include <unistd.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "camera_calibration.h"
#include "preprocess.h"
#include "lane_detect.h"
#include "lane_mapping.h"
#include "lane_data_output.h"

#define LINUX	1

#ifdef LINUX
#include <sys/time.h>
#endif

using namespace std;

int main(int argc, char* argv[])
{
#ifdef LINUX
	struct timeval total_start_time, total_end_time;
	struct timeval start_time, end_time;
	double diff_time;
#elif		
	clock_t start, end;
#endif

	cv::Mat input_image;
	cv::Mat input_warped_image;
	cv::Mat input_unwarped_image;
	cv::Mat warped_image;
	cv::Mat unwarped_image;
	cv::Mat draw_image;
	cv::Mat input_result_image;

	/*class init*/
	Preprocessor processor;
	LaneDetector detector;
	LaneMapper mapper;
	CameraCalibrator calibrator;
	int image_index = 1;

	cv::namedWindow("input", cv::WINDOW_AUTOSIZE);

	while(true)
	{
		//input_image = cv::imread("input/20210426133022/20210426132650/" + to_string(image_index) + ".jpg");
		input_image = cv::imread("../test_image/" + to_string(image_index) + ".jpg");

		if (input_image.empty())
		{
			cout << "No Image!" << endl;
			break;
		}

		cv::resize(input_image, input_image, cv::Size(640, 480));

		/*lane data*/
		LaneDataOut lane_data_output;
		map<string, vector<float>> lane_data;
		vector<cv::Point2f> left_point;
		vector<cv::Point2f> right_point;
		vector<cv::Point2f> left_radar_point;
		vector<cv::Point2f> right_radar_point;
		cv::Mat left_poly_result;
		cv::Mat right_poly_result;

#ifdef LINUX
		gettimeofday(&total_start_time,NULL);
#elif		
		start = clock();
#endif

		/*lane detection process*/
		gettimeofday(&start_time,NULL);
		cv::Mat mag_image = processor.magThresh(input_image, 3, make_pair(50, 255));
		gettimeofday(&end_time,NULL);
		diff_time = end_time.tv_sec + end_time.tv_usec / 1000000.0 - start_time.tv_sec - start_time.tv_usec / 1000000.0;
		printf("magThresh takes %lf ms\n", diff_time*1000);
		//cv::Mat black_image = cv::Mat::zeros(input_image.size(), CV_8UC3);
		gettimeofday(&start_time,NULL);
		processor.getWarpedImage(mag_image, warped_image, unwarped_image);
		gettimeofday(&end_time,NULL);
		diff_time = end_time.tv_sec + end_time.tv_usec / 1000000.0 - start_time.tv_sec - start_time.tv_usec / 1000000.0;
		printf("getWarpedImage takes %lf ms\n", diff_time*1000);

		gettimeofday(&start_time,NULL);
		processor.getWarpedImage(input_image, input_warped_image, input_unwarped_image);
		gettimeofday(&end_time,NULL);
		diff_time = end_time.tv_sec + end_time.tv_usec / 1000000.0 - start_time.tv_sec - start_time.tv_usec / 1000000.0;
		printf("getWarpedImage takes %lf ms\n", diff_time*1000);

		gettimeofday(&start_time,NULL);
		detector.laneFit(warped_image, lane_data, left_point, right_point, draw_image);
		gettimeofday(&end_time,NULL);
		diff_time = end_time.tv_sec + end_time.tv_usec / 1000000.0 - start_time.tv_sec - start_time.tv_usec / 1000000.0;
		printf("laneFit takes %lf ms\n", diff_time*1000);
		
		gettimeofday(&start_time,NULL);
		mapper.getRadarPoint(left_point, right_point, left_radar_point, right_radar_point);
		gettimeofday(&end_time,NULL);
		diff_time = end_time.tv_sec + end_time.tv_usec / 1000000.0 - start_time.tv_sec - start_time.tv_usec / 1000000.0;
		printf("getRadarPoint takes %lf ms\n", diff_time*1000);


		cv::Mat left_poly_result = detector.polyfit(left_radar_point, 2);
		cv::Mat right_poly_result = detector.polyfit(right_radar_point, 2);

		cout << detector.polyfit(left_radar_point, 2) << endl;

		/*get data output*/
		if (left_point.size() > 0)
		{
			left_poly_result = detector.polyfit(left_radar_point, 2);
			lane_data_output.max_left_lane_range = left_radar_point.back().x;
			lane_data_output.polyfit_on_left_lane[0] = *left_poly_result.ptr<float>(0);
			lane_data_output.polyfit_on_left_lane[1] = *left_poly_result.ptr<float>(1);
			lane_data_output.polyfit_on_left_lane[2] = *left_poly_result.ptr<float>(2);
		}
		else
		{
			lane_data_output.max_left_lane_range = 0;
		}

		if (right_point.size() > 0)
		{
			right_poly_result = detector.polyfit(right_radar_point, 2);
			lane_data_output.max_right_lane_range = right_radar_point.back().x;
			lane_data_output.polyfit_on_right_lane[0] = *right_poly_result.ptr<float>(0);
			lane_data_output.polyfit_on_right_lane[1] = *right_poly_result.ptr<float>(1);
			lane_data_output.polyfit_on_right_lane[2] = *right_poly_result.ptr<float>(2);
		}
		else
		{
			lane_data_output.max_right_lane_range = 0;
		}

		cout << left_poly_result << endl;
		cout << right_poly_result << endl;
		cout << lane_data_output.max_left_lane_range << endl;
		cout << lane_data_output.max_right_lane_range << endl;

#ifdef LINUX
		gettimeofday(&total_end_time,NULL);
#elif		
		end = clock();
#endif

		diff_time = total_end_time.tv_sec + total_end_time.tv_usec / 1000000.0 - total_start_time.tv_sec - total_start_time.tv_usec / 1000000.0;
		printf("Elapsed time: %lf ms\n", diff_time*1000);

		/*visualization*/
		//imshow("input", input_image);

		/*keyboard function*/
		/*int keyChar = cv::waitKey();

		if (keyChar == 27)
			break;
		else if (keyChar == 32)
		{
			image_index--;
			continue;
		}
*/
		//while(1);

		//image_index++;

		sleep(1);
	}

	cv::destroyAllWindows();

	return 0;
}