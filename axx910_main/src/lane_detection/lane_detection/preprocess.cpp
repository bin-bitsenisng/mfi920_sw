#include "preprocess.h"

void Preprocessor::scaleDownImage(cv::Mat image, cv::Mat &scale_down_image)
{

}

void Preprocessor::getWarpedImage(cv::Mat image, cv::Mat &warped_image, cv::Mat &unwarped_image)
{
	int height = image.size().height;
	int width = image.size().width;

	warped_image = cv::Mat::zeros(image.size(), CV_8UC3);
	unwarped_image = cv::Mat::zeros(image.size(), CV_8UC3);

	cv::Point2f src[4], dst[4];

	/*src[0] = Point2f(0, 360);
	src[1] = Point2f(640, 340);
	src[2] = Point2f(290, 250);
	src[3] = Point2f(350, 250);*/

	/*src[0] = Point2f(0, 330);
	src[1] = Point2f(640, 330);
	src[2] = Point2f(230, 270);
	src[3] = Point2f(420, 270);*/

#if LOW_RESOLUTION
	src[0] = cv::Point2f(0, 310);
	src[1] = cv::Point2f(640, 310);
	src[2] = cv::Point2f(250, 255);
	src[3] = cv::Point2f(400, 255);
#else
	src[0] = cv::Point2f(0, 340);
	src[1] = cv::Point2f(640, 340);
	src[2] = cv::Point2f(250, 270);
	src[3] = cv::Point2f(350, 270);
#endif

	dst[0] = cv::Point2f(0, 480);
	dst[1] = cv::Point2f(640, 480);
	dst[2] = cv::Point2f(0, 0);
	dst[3] = cv::Point2f(640, 0);

	/*dst[0] = cv::Point2f(0, 240);
	dst[1] = cv::Point2f(320, 240);
	dst[2] = cv::Point2f(0, 0);
	dst[3] = cv::Point2f(320, 0);*/

	perspective_mat = getPerspectiveTransform(src, dst);
	inverse_mat = getPerspectiveTransform(dst, src);

	warpPerspective(image, warped_image, perspective_mat, cv::Size(width, height));
	warpPerspective(warped_image, unwarped_image, inverse_mat, cv::Size(width, height));
}

cv::Mat Preprocessor::absSobelThresh(cv::Mat image, char orient, int thresh_min, int thresh_max)
{
	cv::Mat gray_image;
	cv::Mat sobel_image;
	cv::Mat abs_sobel;
	double min_sobel, max_sobel;
	cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);

	if (orient == 'x')
	{
		Sobel(gray_image, sobel_image, CV_64F, 1, 0);
		abs_sobel = abs(sobel_image);
	}
	else if (orient == 'y')
	{
		Sobel(gray_image, sobel_image, CV_64F, 0, 1);
		abs_sobel = abs(sobel_image);
	}

	cv::Mat scaled_sobel = cv::Mat::zeros(image.size(), CV_8UC1);

	minMaxLoc(abs_sobel, &min_sobel, &max_sobel);

	for (int i = 0; i < abs_sobel.cols; i++)
		for (int j = 0; j < abs_sobel.rows; j++)
		{
			scaled_sobel.at<uchar>(j, i) = (uint8_t)(255.0 * abs_sobel.at<double>(j, i) / max_sobel);
		}

	cv::Mat binary_image = cv::Mat::zeros(image.size(), CV_8UC1);

	for (int i = 0; i < binary_image.cols; i++)
		for (int j = 0; j < binary_image.rows; j++)
		{
			if ((scaled_sobel.at<uchar>(j, i) >= thresh_min) && (scaled_sobel.at<uchar>(j, i) <= thresh_max))
				binary_image.at<uchar>(j, i) = 255;
			else
				continue;
		}

	return binary_image;
}

cv::Mat Preprocessor::magThresh(cv::Mat image, int sobel_kernel, pair<int, int> mag_thresh)
{
	cv::Mat gray_image;
	cv::Mat sobelx, sobely, pow_sobelx, pow_sobely;
	cv::Mat grad_mag = cv::Mat::zeros(image.size(), CV_64F);
	double min_grad_mag, max_grad_mag;
	int scale_factor;
	cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);

	Sobel(gray_image, sobelx, CV_64F, 1, 0, sobel_kernel);
	Sobel(gray_image, sobely, CV_64F, 0, 1, sobel_kernel);

	pow(sobelx, 2, pow_sobelx);
	pow(sobely, 2, pow_sobely);

	sqrt(pow_sobelx + pow_sobely, grad_mag);

	minMaxLoc(grad_mag, &min_grad_mag, &max_grad_mag);
	scale_factor = max_grad_mag / 255;
	grad_mag = grad_mag / scale_factor;

	grad_mag.convertTo(grad_mag, CV_8UC1);

	cv::Mat binary_image = cv::Mat::zeros(grad_mag.size(), CV_8UC1);

	for (int i = 0; i < binary_image.cols; i++)
		for (int j = 0; j < binary_image.rows; j++)
		{
			if ((grad_mag.at<uchar>(j, i) >= mag_thresh.first) && (grad_mag.at<uchar>(j, i) < mag_thresh.second))
				binary_image.at<uchar>(j, i) = 255;
		}

	return binary_image;
}

cv::Mat Preprocessor::dirThreshold(cv::Mat image, int sobel_kernel, pair<double, double> thresh)
{
	cv::Mat gray_image;
	cv::Mat sobelx, sobely;
	cv::Mat abs_grad_dir = cv::Mat::zeros(image.size(), CV_64F);

	vector<vector<double>> res(image.size().height, vector<double>(image.size().width, 0));

	cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);

	Sobel(gray_image, sobelx, CV_64F, 1, 0, sobel_kernel);
	Sobel(gray_image, sobely, CV_64F, 0, 1, sobel_kernel);

	for (int i = 0; i < sobelx.cols; i++)
		for (int j = 0; j < sobely.rows; j++)
			res[j][i] = atan2(abs(sobely.at<double>(j, i)), abs(sobelx.at<double>(j, i)));
	//cout << res[50][50] << endl;
	cv::Mat binary_image = cv::Mat::zeros(image.size(), CV_8UC1);

	for (int i = 0; i < binary_image.cols; i++)
		for (int j = 0; j < binary_image.rows; j++)
		{
			if ((res[j][i] >= thresh.first) && (res[j][i] <= thresh.second))
				binary_image.at<uchar>(j, i) = 255;
		}

	/*for(int i=0; i<absGraddir.cols; i++)
	   for (int j = 0; j < absGraddir.rows; j++)
		  absGraddir.at<double>(j, i) = atan2(abs(sobelY.at<double>(j, i)), abs(sobelX.at<double>(j, i)));

	//Mat binaryImage;
	//threshold(grayImage, binaryImage, thresh.second, thresh.first, THRESH_BINARY_INV);

	Mat binaryImage(absGraddir.size().height, absGraddir.size().width, THRESH_BINARY, Scalar(0));

	for(int i=0; i<binaryImage.cols; i++)
	   for (int j = 0; j < binaryImage.rows; j++)
	   {
		  if ((absGraddir.at<double>(j, i) >= thresh.first) && (absGraddir.at<double>(j, i) <= thresh.second))
			 binaryImage.at<double>(j, i) = 255;
	   }*/

	return binary_image;
}

cv::Mat Preprocessor::hlsThresh(cv::Mat image, pair<int, int> thresh)
{
	cv::Mat hls_image;
	cvtColor(image, hls_image, cv::COLOR_BGR2HLS);

	cv::Mat saturation = cv::Mat::zeros(hls_image.size(), CV_8UC1);

	for (int i = 0; i < saturation.cols; i++)
		for (int j = 0; j < saturation.rows; j++)
		{
			saturation.at<uchar>(j, i) = hls_image.at<cv::Vec3b>(j, i)[2];
		}

	cv::Mat binary_image = cv::Mat::zeros(saturation.size(), CV_8UC1);

	for (int i = 0; i < binary_image.cols; i++)
		for (int j = 0; j < binary_image.rows; j++)
		{
			if ((saturation.at<uchar>(j, i) > thresh.first) && (saturation.at<uchar>(j, i) <= thresh.second))
				binary_image.at<uchar>(j, i) = 255;
		}

	return binary_image;
}

cv::Mat Preprocessor::combinedThresh(cv::Mat image)
{
	cv::Mat abs_binary = absSobelThresh(image, 'x', 50, 255);
	cv::Mat mag_binary = magThresh(image, 3, make_pair(50, 255));
	cv::Mat dir_binary = dirThreshold(image, 15, make_pair(0.7, 1.3));
	cv::Mat hls_binary = hlsThresh(image, make_pair(170, 255));

	cv::Mat combined_binary = cv::Mat::zeros(image.size(), CV_8UC1);

	for (int i = 0; i < combined_binary.cols; i++)
		for (int j = 0; j < combined_binary.rows; j++)
		{
			if ((abs_binary.at<uchar>(j, i) == 255 || (mag_binary.at<uchar>(j, i) == 255 && dir_binary.at<uchar>(j, i) == 255)) || hls_binary.at<uchar>(j, i) == 255)
				combined_binary.at<uchar>(j, i) = 255;
		}

	return combined_binary;
}