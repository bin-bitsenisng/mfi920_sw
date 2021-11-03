#include "lane_detect.h"
#include "lane_data_output.h"

LaneDataOut lane_data_output;

/*void LaneDetector::laneFit(cv::Mat image, map<string, vector<float>> &lane_data, vector<cv::Point2f> &left_point, vector<cv::Point2f> &right_point, cv::Mat &draw_image)
{
	int num_of_window = 9;
	int window_height = image.size().height / num_of_window;
	int window_width = image.size().width / 6;
	int margin = 50;
	int minPixel = 50;
	vector<cv::Point2f> image_nonzero;
	vector<float> nonzerox;
	vector<float> nonzeroy;
	int window_leftx_low;
	int window_leftx_high;
	int window_rightx_low;
	int window_rightx_high;
	int window_big_y;
	int window_small_y;

	getLaneBase(image);

	int leftx_current = bottom_leftx_base;
	int rightx_current = bottom_rightx_base;

	int top_leftx_current = top_leftx_base;
	int top_rightx_current = top_rightx_base;

	vector<cv::Mat> channels(3, image);

	draw_image = cv::Mat(image.size().height, image.size().width, CV_8UC3);
	merge(channels, draw_image);

	findNonZero(image, image_nonzero);

	for (int i = 0; i < image_nonzero.size(); i++)
	{
		nonzerox.push_back(image_nonzero[i].x);
		nonzeroy.push_back(image_nonzero[i].y);
	}

	vector<float> good_left_inds;
	vector<float> good_right_inds;
	vector<float> lane_inds;
	vector<float> left_lane_inds;
	vector<float> right_lane_inds;
	vector<float> left_pointx;
	vector<float> left_pointy;
	vector<float> right_pointx;
	vector<float> right_pointy;

	for (int j = 0; j < num_of_window; j++)
	{
		window_leftx_low = leftx_current - margin;
		window_leftx_high = leftx_current + margin;
		window_rightx_low = rightx_current - margin;
		window_rightx_high = rightx_current + margin;
		window_big_y = image.size().height - j * window_height;
		window_small_y = image.size().height - (j + 1)*window_height;
		//rectangle(draw_image, cv::Rect(cv::Point(window_leftx_low, window_small_y), cv::Point(window_leftx_high, window_big_y)), cv::Scalar(0, 255, 0), 1, 8, 0);
		//rectangle(draw_image, cv::Rect(cv::Point(window_rightx_low, window_small_y), cv::Point(window_rightx_high, window_big_y)), cv::Scalar(0, 255, 0), 1, 8, 0);

		for (int l = 0; l < nonzerox.size(); l++)
		{
			if ((nonzeroy[l] >= window_small_y) && (nonzeroy[l] < window_big_y) && (nonzerox[l] >= window_leftx_low) && (nonzerox[l] < window_leftx_high))
			{
				good_left_inds.push_back(l);
			}
			if ((nonzeroy[l] >= window_small_y) && (nonzeroy[l] < window_big_y) && (nonzerox[l] >= window_rightx_low) && (nonzerox[l] < window_rightx_high))
			{
				good_right_inds.push_back(l);
			}
		}

		for (int i = 0; i < good_left_inds.size(); i++)
		{
			left_lane_inds.push_back(good_left_inds[i]);
		}

		for (int i = 0; i < good_right_inds.size(); i++)
		{
			right_lane_inds.push_back(good_right_inds[i]);
		}

		if (good_left_inds.size() > minPixel)
		{
			int left_sum = 0;
			for (int a = 0; a < good_left_inds.size(); a++)
			{
				left_sum += nonzerox[good_left_inds[a]];
			}
			leftx_current = left_sum / good_left_inds.size();
		}
		if (good_right_inds.size() > minPixel)
		{
			int right_sum = 0;
			for (int a = 0; a < good_right_inds.size(); a++)
			{
				right_sum += nonzerox[good_right_inds[a]];
			}
			rightx_current = right_sum / good_right_inds.size();
		}
	}

	for (int i = 0; i < left_lane_inds.size(); i++)
	{
		left_pointx.push_back(nonzerox[left_lane_inds[i]]);
		left_pointy.push_back(nonzeroy[left_lane_inds[i]]);
		left_point.push_back(cv::Point2f(left_pointx[i], left_pointy[i]));
	}

	for (int i = 0; i < right_lane_inds.size(); i++)
	{
		right_pointx.push_back(nonzerox[right_lane_inds[i]]);
		right_pointy.push_back(nonzeroy[right_lane_inds[i]]);
		right_point.push_back(cv::Point2f(right_pointx[i], right_pointy[i]));
	}
	cv::Mat left_coefficient = polyfit(left_pointx, left_pointy, 2);
	cv::Mat right_coefficient = polyfit(right_pointx, right_pointy, 2);

	lane_data["leftpointx"] = left_pointx;
	lane_data["leftpointy"] = left_pointy;
	lane_data["rightpointx"] = right_pointx;
	lane_data["rightpointy"] = right_pointy;
	lane_data["fitResult"] = fit_result;
	lane_data["laneInds"] = lane_inds;
	lane_data["leftInds"] = left_lane_inds;
	lane_data["rightInds"] = right_lane_inds;
	lane_data["nonzeroX"] = nonzerox;
	lane_data["nonzeroY"] = nonzeroy;
	lane_data["lanePointX"] = lane_pointx;
}*/

void LaneDetector::laneFit(cv::Mat image, map<string, vector<float>> &lane_data, vector<cv::Point2f> &left_point, vector<cv::Point2f> &right_point, cv::Mat &draw_image)
{
	int num_of_window = 9;
	int window_height = image.size().height / num_of_window;
	int window_width = image.size().width / 6;
	int margin = 50;
	int minPixel = 50;
	vector<cv::Point2f> image_nonzero;
	int window_leftx_low;
	int window_leftx_high;
	int window_rightx_low;
	int window_rightx_high;
	int window_big_y;
	int window_small_y;

	getLaneBase(image);

	int leftx_current = bottom_leftx_base;
	int rightx_current = bottom_rightx_base;

	int top_leftx_current = top_leftx_base;
	int top_rightx_current = top_rightx_base;

	vector<cv::Mat> channels(3, image);

	draw_image = cv::Mat(image.size().height, image.size().width, CV_8UC3);
	merge(channels, draw_image);

	findNonZero(image, image_nonzero);

	int image_nonzero_size = image_nonzero.size();

	vector<float> nonzero_x(image_nonzero_size);
	vector<float> nonzero_y(image_nonzero_size);

	for (int i = 0; i < image_nonzero_size; i++)
	{
		nonzero_x[i] = image_nonzero[i].x;
		nonzero_y[i] = image_nonzero[i].y;
	}

	vector<float> good_left_inds(54450);
	vector<float> good_right_inds(54450);
	vector<float> left_lane_inds(54450);
	vector<float> right_lane_inds(54450);
	vector<float> left_pointx(54450);
	vector<float> left_pointy(54450);
	vector<float> right_pointx(54450);
	vector<float> right_pointy(54450);
	int good_left_inds_index = 0;
	int good_right_inds_index = 0;
	int left_lane_inds_index = 0;
	int right_lane_inds_index = 0;

	for (int j = 0; j < num_of_window; j++)
	{
		window_leftx_low = leftx_current - margin;
		window_leftx_high = leftx_current + margin;
		window_rightx_low = rightx_current - margin;
		window_rightx_high = rightx_current + margin;
		window_big_y = image.size().height - j * window_height;
		window_small_y = image.size().height - (j + 1)*window_height;
		//rectangle(draw_image, cv::Rect(cv::Point(window_leftx_low, window_small_y), cv::Point(window_leftx_high, window_big_y)), cv::Scalar(0, 255, 0), 1, 8, 0);
		//rectangle(draw_image, cv::Rect(cv::Point(window_rightx_low, window_small_y), cv::Point(window_rightx_high, window_big_y)), cv::Scalar(0, 255, 0), 1, 8, 0);

		for (int l = 0; l < image_nonzero_size; l++)
		{
			if ((nonzero_y[l] >= window_small_y) && (nonzero_y[l] < window_big_y) && (nonzero_x[l] >= window_leftx_low) && (nonzero_x[l] < window_leftx_high))
			{
				good_left_inds[good_left_inds_index++] = l;
			}
			if ((nonzero_y[l] >= window_small_y) && (nonzero_y[l] < window_big_y) && (nonzero_x[l] >= window_rightx_low) && (nonzero_x[l] < window_rightx_high))
			{
				good_right_inds[good_right_inds_index++] = l;
			}
		}

		if (good_left_inds_index > minPixel)
		{
			int left_sum = 0;
			for (int a = 0; a < good_left_inds_index; a++)
			{
				left_sum += nonzero_x[good_left_inds[a]];
			}
			leftx_current = left_sum / (good_left_inds_index);
		}
		if (good_right_inds_index > minPixel)
		{
			int right_sum = 0;
			for (int a = 0; a < good_right_inds_index; a++)
			{
				right_sum += nonzero_x[good_right_inds[a]];
			}
			rightx_current = right_sum / (good_right_inds_index);
		}
	}

	left_point.resize(good_left_inds_index);
	right_point.resize(good_right_inds_index);

	for (int i = 0; i < good_left_inds_index; i++)
	{
		left_pointx[i] = nonzero_x[good_left_inds[i]];
		left_pointy[i] = nonzero_y[good_left_inds[i]];
		left_point[i] = cv::Point2f(left_pointx[i], left_pointy[i]);
	}

	for (int i = 0; i < good_right_inds_index; i++)
	{
		right_pointx[i] = nonzero_x[good_right_inds[i]];
		right_pointy[i] = nonzero_y[good_right_inds[i]];
		right_point[i] = cv::Point2f(right_pointx[i], right_pointy[i]);
	}

	lane_data["leftpointx"] = left_pointx;
	lane_data["leftpointy"] = left_pointy;
	lane_data["rightpointx"] = right_pointx;
	lane_data["rightpointy"] = right_pointy;
	lane_data["fitResult"] = fit_result;
	lane_data["leftInds"] = left_lane_inds;
	lane_data["rightInds"] = right_lane_inds;
	lane_data["nonzeroX"] = nonzerox;
	lane_data["nonzeroY"] = nonzeroy;
	lane_data["lanePointX"] = lane_pointx;
}

/*void LaneDetector::getLaneBase(cv::Mat image)
{
	vector<int> bottom_histogram;
	vector<int> top_histogram;
	int bottom_histogram_value;
	int top_histogram_value;
	int image_cols = image.cols;
	int image_rows = image.rows;

	for (int i = 0; i < image_cols; i++)
	{
		bottom_histogram_value = 0;
		for (int j = image_rows / 2; j < image_rows; j++)
		{
			if (image.at<uchar>(j, i) == 255)
				bottom_histogram_value++;
			else
				continue;
		}
		bottom_histogram.push_back(bottom_histogram_value);
	}

	int bottom_midpoint = bottom_histogram.size() / 2;

	for (int i = 0; i < image_cols; i++)
	{
		top_histogram_value = 0;
		for (int j = 0; j < image_rows / 2; j++)
		{
			if (image.at<uchar>(j, i) == 255)
				top_histogram_value++;
			else
				continue;
		}
		top_histogram.push_back(top_histogram_value);
	}

	int top_midpoint = top_histogram.size() / 2;

	bottom_leftx_base = max_element(bottom_histogram.begin(), bottom_histogram.begin() + bottom_midpoint) - bottom_histogram.begin();
	bottom_rightx_base = max_element(bottom_histogram.begin() + bottom_midpoint, bottom_histogram.end()) - bottom_histogram.begin();

	top_leftx_base = max_element(top_histogram.begin(), top_histogram.begin() + top_midpoint) - top_histogram.begin();
	top_rightx_base = max_element(top_histogram.begin() + top_midpoint, top_histogram.end()) - top_histogram.begin();
}*/

void LaneDetector::getLaneBase(cv::Mat image)
{
	vector<int> bottom_histogram(640);
	vector<int> top_histogram(640);
	int bottom_histogram_value;
	int top_histogram_value;
	int image_cols = image.cols;
	int image_rows = image.rows;

	for (int i = 0; i < image_cols; i++)
	{
		bottom_histogram_value = 0;
		for (int j = image_rows / 2; j < image_rows; j++)
		{
			if (image.at<uchar>(j, i) == 255)
				bottom_histogram_value++;
			else
				continue;
		}
		bottom_histogram[i] = bottom_histogram_value;
	}

	int bottom_midpoint = bottom_histogram.size() / 2;

	for (int i = 0; i < image_cols; i++)
	{
		top_histogram_value = 0;
		for (int j = 0; j < image_rows / 2; j++)
		{
			if (image.at<uchar>(j, i) == 255)
				top_histogram_value++;
			else
				continue;
		}
		top_histogram[i] = top_histogram_value;
	}

	int top_midpoint = top_histogram.size() / 2;

	bottom_leftx_base = max_element(bottom_histogram.begin(), bottom_histogram.begin() + bottom_midpoint) - bottom_histogram.begin();
	bottom_rightx_base = max_element(bottom_histogram.begin() + bottom_midpoint, bottom_histogram.end()) - bottom_histogram.begin();

	top_leftx_base = max_element(top_histogram.begin(), top_histogram.begin() + top_midpoint) - top_histogram.begin();
	top_rightx_base = max_element(top_histogram.begin() + top_midpoint, top_histogram.end()) - top_histogram.begin();
}

void LaneDetector::trackLane(cv::Mat image, vector<float> leftfit, vector<float> rightfit, map<string, vector<float>> &lane_data)
{
	vector<cv::Point2f> image_nonzero;
	vector<float> nonzero;
	vector<float> nonzerox;
	vector<float> nonzeroy;

	vector<float> left_lane_inds;
	vector<float> right_lane_inds;

	vector<float> leftx;
	vector<float> lefty;
	vector<float> rightx;
	vector<float> righty;

	//vector<float> leftfit;
	//vector<float> rightfit;

	findNonZero(image, image_nonzero);

	leftfit = polyfit(leftx, lefty, 2);
	rightfit = polyfit(rightx, righty, 2);

	for (int i = 0; i < image_nonzero.size(); i++)
	{
		nonzerox.push_back(image_nonzero[i].x);
		nonzeroy.push_back(image_nonzero[i].y);
	}

	int margin = 50;

	for (int i = 0; i < leftfit.size(); i++)
	{
		if ((nonzerox[i] > (leftfit[0] * pow(nonzeroy[i], 2) + leftfit[1] * nonzeroy[i] + leftfit[2] - margin)) && (nonzerox[i] < (leftfit[0] * pow(nonzeroy[i], 2) + leftfit[1] * nonzeroy[i] + leftfit[2] + margin)))
			left_lane_inds.push_back(nonzerox[i]);
		if ((nonzerox[i] > (rightfit[0] * pow(nonzeroy[i], 2) + rightfit[1] * nonzeroy[i] + rightfit[2] - margin)) && (nonzerox[i] < (rightfit[0] * pow(nonzeroy[i], 2) + rightfit[1] * nonzeroy[i] + rightfit[2] + margin)))
			right_lane_inds.push_back(nonzerox[i]);
	}

	for (int i = 0; i < left_lane_inds.size(); i++)
	{
		leftx.push_back(nonzerox[left_lane_inds[i]]);
		lefty.push_back(nonzeroy[left_lane_inds[i]]);
	}

	for (int i = 0; i < right_lane_inds.size(); i++)
	{
		rightx.push_back(nonzerox[right_lane_inds[i]]);
		righty.push_back(nonzeroy[right_lane_inds[i]]);
	}

	lane_data["nonzeroX"] = nonzerox;
	lane_data["nonzeroY"] = nonzeroy;
	lane_data["leftInds"] = left_lane_inds;
	lane_data["rightInds"] = right_lane_inds;
}

cv::Mat LaneDetector::polyfit(vector<float> pointx, vector<float> pointy, int n)
{
	cv::Mat y(pointx.size(), 1, CV_32F, cv::Scalar::all(0));
	cv::Mat phy(pointx.size(), n, CV_32F, cv::Scalar::all(0));

	for (int i = 0; i < phy.rows; i++)
	{
		float *pr = phy.ptr<float>(i);

		for (int j = 0; j < phy.cols; j++)
			pr[j] = pow(pointx[i], j);
		y.at<float>(i) = pointy[i];
	}

	cv::Mat phy_t = phy.t();
	cv::Mat phy_mul_phyt = phy.t() * phy;
	cv::Mat phy_mul_phy_inv = phy_mul_phyt.inv();
	cv::Mat a = phy_mul_phy_inv * phy_t;
	a = a * y;

	return a;
}

cv::Mat LaneDetector::polyfit(vector<cv::Point2f> in_point, int n)
{
	int size = in_point.size();
	//The number of unknowns required
	int x_num = n + 1;
	//Construct the matrix U and Y
	cv::Mat mat_u(size, x_num, CV_32F, cv::Scalar::all(0));
	cv::Mat mat_y(size, 1, CV_32F, cv::Scalar::all(0));

	for (int i = 0; i < mat_u.rows; ++i)
	{
		for (int j = 0; j < mat_u.cols; ++j)
		{
			mat_u.at<float>(i, j) = pow(in_point[i].x, j);
			//mat_u.at<double>(i, j) = pow(in_point[i].x, j);
		}
	}

	for (int i = 0; i < mat_y.rows; ++i)
	{
		mat_y.at<float>(i, 0) = in_point[i].y;
		//mat_y.at<double>(i, 0) = in_point[i].y;
	}

	//cout << mat_u << endl;

	//Matrix operation, get coefficient matrix K
	cv::Mat mat_k;//(x_num, 1, CV_32F);

	mat_k = (mat_u.t()*mat_u).inv()*mat_u.t()*mat_y;
	
	return mat_k;
}

cv::Mat LaneDetector::multiplyMat(cv::Mat a, cv::Mat b)
{
	int a_rows = a.rows;
	int a_cols = a.cols;
	int b_rows = b.rows;
	int b_cols = b.cols;
	cv::Mat result(a_rows, b_cols, CV_32F, cv::Scalar::all(0));

	for (int i = 0; i < a_rows; i++)
	{
		for (int j = 0; j < b_cols; j++)
		{
			for (int k = 0; k < a_cols; k++)
			{
				result.at<float>(i, j) += a.at<float>(i, k) * b.at<float>(k, j);
			}
		}
	}

	return result;
}

void LaneDetector::drawResult(map<string, vector<float>> lane_data, cv::Mat &draw_image, cv::Mat &input_warped_image)
{
	vector<float> nonzerox = lane_data["nonzeroX"];
	vector<float> nonzeroy = lane_data["nonzeroY"];

	vector<float> lanefit = lane_data["laneFit"];
	vector<float> left_lane_inds = lane_data["leftInds"];
	vector<float> right_lane_inds = lane_data["rightInds"];

	for (int i = 0; i < left_lane_inds.size(); i++)
	{
		draw_image.at<cv::Vec3b>(nonzeroy[left_lane_inds[i]], nonzerox[left_lane_inds[i]]) = cv::Vec3b(0, 0, 255);
		input_warped_image.at<cv::Vec3b>(nonzeroy[left_lane_inds[i]], nonzerox[left_lane_inds[i]]) = cv::Vec3b(0, 0, 255);
		float left_lane_point[] = { nonzeroy[left_lane_inds[i]], nonzerox[left_lane_inds[i]], 1 };
		cv::Mat left_lane_matrix(3, 1, CV_64F, left_lane_point);
	}

	for (int i = 0; i < right_lane_inds.size(); i++)
	{
		draw_image.at<cv::Vec3b>(nonzeroy[right_lane_inds[i]], nonzerox[right_lane_inds[i]]) = cv::Vec3b(0, 0, 255);
		input_warped_image.at<cv::Vec3b>(nonzeroy[right_lane_inds[i]], nonzerox[right_lane_inds[i]]) = cv::Vec3b(0, 0, 255);
		float right_lane_point[] = { nonzeroy[right_lane_inds[i]], nonzerox[right_lane_inds[i]], 1 };
		cv::Mat right_lane_matrix(3, 1, CV_64F, right_lane_point);
	}
}

cv::Mat LaneDetector::getLaneDetectedImage(cv::Mat warped_image, cv::Mat unwarped_image, cv::Mat warped_inverse_mat, cv::Mat &lane_image)
{
	warpPerspective(warped_image, unwarped_image, warped_inverse_mat, cv::Size(warped_image.size().width, warped_image.size().height));
	add(warped_image, unwarped_image, lane_image);

	return lane_image;
}