#include <unistd.h>
#include <zmq.hpp>
#include <chrono>
#include <mutex>
#include <thread>
#include <glib.h>

#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"

#include "camera_calibration.h"
#include "preprocess.h"
#include "lane_detect.h"
#include "lane_mapping.h"
#include "lane_data_output.h"

#include "camera.h"
#include "camera_device_cfg.h"
#include "inference.h"

/*
std::string gstreamer_pipeline (int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) {
	return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
		   std::to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(framerate) +
		   "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" +
		   std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}*/
/*
std::string gstreamer_pipeline (int capture_width, int capture_height, int framerate, int flip_method) {
	return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
		   std::to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(framerate) +
		   "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}
*/

std::string gstreamer_pipeline(int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) {
	return "nvarguscamerasrc ! queue ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
		std::to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(framerate) +
		"/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" +
		std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

std::mutex g_mutex_image_capture;

uint64_t cam_scanindex = 0;

cv::VideoCapture camera_cap;
cv::Mat camera_raw_data;
cv::Mat buffered_camera_raw_data;
cv::Mat inferenced_image_raw_data;
uint32_t jpg_image_size = 0;
uint8_t jpg_image[CAM_IMAGE_SIZE_MAX];
char ai_dummy_data[0];

int encoding_start_flag = 0;
int lane_detection_start_flag = 0;

extern ai_object_t ai_object[AI_OBJECT_MAX_SIZE];
extern LaneDataOut lane_data_output;
static void init_camera(int width, int height);
static void capture_camera(void);
static void encoding_loop(void);
static void lane_detection_loop(void);
static uint32_t encode_image(cv::Mat input_mat_image);

int main(int argc, char **argv)
{
	double confThresh = DEFAULT_CONF_THRESHOLD;
	double nmsThresh = DEFAULT_NMS_THRESHOLD;
	gchar* cam_resolution = CAPTURE_RESOLUTION;
	int cam_width = CAPTURE_WIDTH;
	int cam_height = CAPTURE_HEIGHT;

	GOptionContext* optCtx = NULL;
	GError* error = NULL;

	GOptionEntry entries[] = {
		{"conf_th", 'c', 0, G_OPTION_ARG_DOUBLE, &confThresh, "confidence threshold(0.5)", NULL},
		{"nms_th", 'n', 0, G_OPTION_ARG_DOUBLE, &nmsThresh, "nms threshold(0.4)", NULL},
		{"cam_resolution", 'r', 0, G_OPTION_ARG_STRING, &cam_resolution, "cam_resolution", NULL},
		{NULL}
	};

	optCtx = g_option_context_new("option_context");

	g_option_context_add_main_entries(optCtx, entries, NULL);

	if (!g_option_context_parse(optCtx, &argc, &argv, &error)) {
		g_print("option parsing failed.. default setting will be adapted: %s\n", error->message);
		g_option_context_free(optCtx);
	}

	if (strcmp(cam_resolution, "4K") == 0)
	{
		cam_width = 3840;
		cam_height = 2160;
	}
	else if (strcmp(cam_resolution, "QHD") == 0)
	{
		cam_width = 2560;
		cam_height = 1440;
	}
	else if (strcmp(cam_resolution, "FHD") == 0)
	{
		cam_width = 1920;
		cam_height = 1080;
	}
	else if (strcmp(cam_resolution, "720P") == 0)
	{
		cam_width = 1280;
		cam_height = 720;
	}/*
	else
	{
		VGA;
	}*/

	printf("conf_th: %f, nms_th: %f, cam_resolution: %d x %d\n", confThresh, nmsThresh, cam_width, cam_height);

	zmq::context_t context(1);
	zmq::socket_t socket(context, ZMQ_REP);
	zmq::message_t connect_request;
	zmq::message_t data_request;

	socket.bind(BIND_STRING);
#if STANDALONE_OPERATION == 0
	printf("wait recv first request...\n");

	socket.recv(&connect_request);
	printf("first request received!!\n");
	socket.send(connect_request);
	printf("first reply sended!!\n");

	sleep(3);
#endif

	init_camera(cam_width, cam_height); // 위치 조정 필요.
#if INFERENCE_ENABLE == 1    
	InitInference(confThresh, nmsThresh);
#endif
	std::thread cam_thread(capture_camera);
	std::thread encoding_thread(encoding_loop);
	std::thread lane_detection_thread(lane_detection_loop);
	usleep(200000);

	while (1)
	{
#if STANDALONE_OPERATION == 0
		//  Wait for next request from client
		socket.recv(&data_request);
#endif
		std::chrono::system_clock::time_point time_start, time_end;
#if INFERENCE_ENABLE == 1
		// Inference & Encoding
		time_start = std::chrono::system_clock::now();

		g_mutex_image_capture.lock();
		camera_raw_data.copyTo(buffered_camera_raw_data);
		g_mutex_image_capture.unlock();

		//lane_detection_start_flag = 1;        
		encoding_start_flag = 1;
		//inferenced_image_raw_data = Inference(buffered_camera_raw_data);

		while (encoding_start_flag == 1 || lane_detection_start_flag == 1); // 으으..

		/*
		inferenced_image_raw_data = Inference(camera_raw_data);
		*/
		//jpg_image_size = encode_image(inferenced_image_raw_data);

		time_end = std::chrono::system_clock::now();
		std::cout << "AI + Encoding + Lane detection takes " << std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count() << " ms" << std::endl;
#else
		// Only Encoding

		time_start = std::chrono::system_clock::now();
		g_mutex_image_capture.lock();
		camera_raw_data.copyTo(buffered_camera_raw_data);
		g_mutex_image_capture.unlock();

		jpg_image_size = encode_image(buffered_camera_raw_data);
		time_end = std::chrono::system_clock::now();
		std::cout << "Only Encoding takes " << std::chrono::duration_cast<std::chrono::microseconds>(time_end - time_start).count() << " us" << std::endl << std::endl;
#endif

#if STANDALONE_OPERATION == 0
		//  Send reply back to client
		socket.send((void*)jpg_image, jpg_image_size);

		socket.recv(&data_request);
		socket.send((void*)ai_object, ai_object[0].Ai_num_of_class * sizeof(ai_object) / AI_OBJECT_MAX_SIZE);
		socket.recv(&data_request);
		socket.send((void*)&lane_data_output, sizeof(LaneDataOut));
#endif
		//printf("Sended image to client(Radar process). size: %d\n", jpg_image_size);
		//printf("Sended ai_object.. Ai_num_of_class: %d, total size: %d\n", ai_object[0].Ai_num_of_class, ai_object[0].Ai_num_of_class * sizeof(ai_object) / AI_OBJECT_MAX_SIZE);
		//printf("Sended lane_data.. %f %f %f, %f %f %f\n", lane_data_output.polyfit_on_left_lane[0], \
                                                            lane_data_output.polyfit_on_left_lane[1], \
                                                            lane_data_output.polyfit_on_left_lane[2], \
                                                            lane_data_output.polyfit_on_right_lane[0], \
                                                            lane_data_output.polyfit_on_right_lane[1], \
                                                            lane_data_output.polyfit_on_right_lane[2] \
                                                            );
	}

	return 0;
}

static void init_camera(int width, int height)
{
	int display_width = width;
	int display_height = height;

	std::string pipeline = gstreamer_pipeline(width, height, display_width, display_height, FRAME_RATE, FLIP_METHOD);

	while (1)
	{
		if (CAMERA_TYPE == WEB_CAM)
		{
			camera_cap.open(CAMERA_DEVICE_NUM, CAMERA_API_PREFERENCE);
		}
		else if (CAMERA_TYPE == ARDU_CAM)
		{
			camera_cap.open(pipeline, cv::CAP_GSTREAMER);
		}

		if (!camera_cap.isOpened())
		{
			printf("Camera Videocapture Open Fail.. Retry!\n");
		}
		else
		{
			printf("Camera Videocapture Open Success!\n");
			break;
		}

		usleep(100000);
	}

	if (CAMERA_TYPE == WEB_CAM)
	{
		camera_cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G')); // cam data: JPG
	}
}

static void capture_camera(void)
{
	std::chrono::system_clock::time_point time_start, time_end;

	while (1)
	{
		if (!camera_cap.read(camera_raw_data))
		{
			printf("[ERROR] Camera data capture fail.\n");
		}
	}
}

static void encoding_loop(void)
{
	std::chrono::system_clock::time_point time_start, time_end;

	while (1)
	{
		if (encoding_start_flag == 1)
		{
			jpg_image_size = encode_image(buffered_camera_raw_data);

			encoding_start_flag = 0;
		}

		usleep(100);
	}
}

static void lane_detection_loop(void)
{
	cv::Mat input_image;
	cv::Mat input_warped_image;
	cv::Mat input_unwarped_image;
	cv::Mat warped_image;
	cv::Mat unwarped_image;
	cv::Mat draw_image;
	cv::Mat input_result_image;

	cv::Mat mag_image;
	cv::Mat left_poly_result;
	cv::Mat right_poly_result;

	Preprocessor processor;
	LaneDetector detector;
	LaneMapper mapper;
	CameraCalibrator calibrator;

	std::chrono::system_clock::time_point time_start, time_end;

	while (1)
	{
		if (lane_detection_start_flag == 1)
		{
			map<string, vector<float>> lane_data;
			vector<cv::Point2f> left_point;
			vector<cv::Point2f> right_point;
			vector<cv::Point2f> left_radar_point;
			vector<cv::Point2f> right_radar_point;

			time_start = std::chrono::system_clock::now();

			cv::resize(buffered_camera_raw_data, input_image, cv::Size(640, 480));

			// do lane detection
			mag_image = processor.magThresh(input_image, 3, make_pair(50, 255));
			processor.getWarpedImage(mag_image, warped_image, unwarped_image);
			processor.getWarpedImage(input_image, input_warped_image, input_unwarped_image);
			detector.laneFit(warped_image, lane_data, left_point, right_point, draw_image);
			mapper.getRadarPoint(left_point, right_point, left_radar_point, right_radar_point);

			if (left_point.size() > 0)
			{
				cv::Mat left_poly_result = detector.polyfit(left_radar_point, 2);
				lane_data_output.max_left_lane_range = left_radar_point.back().x;
				lane_data_output.polyfit_on_left_lane[0] = *left_poly_result.ptr<float>(0);
				lane_data_output.polyfit_on_left_lane[1] = *left_poly_result.ptr<float>(1);
				lane_data_output.polyfit_on_left_lane[2] = *left_poly_result.ptr<float>(2);
			}

			if (right_point.size() > 0)
			{
				cv::Mat right_poly_result = detector.polyfit(right_radar_point, 2);
				lane_data_output.max_right_lane_range = right_radar_point.back().x;
				lane_data_output.polyfit_on_right_lane[0] = *right_poly_result.ptr<float>(0);
				lane_data_output.polyfit_on_right_lane[1] = *right_poly_result.ptr<float>(1);
				lane_data_output.polyfit_on_right_lane[2] = *right_poly_result.ptr<float>(2);
			}

			time_end = std::chrono::system_clock::now();
			//std::cout << "Lane detection takes " << std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count() << " ms" << std::endl;

			lane_detection_start_flag = 0;
		}

		usleep(100);
	}
}


static uint32_t encode_image(cv::Mat input_mat_image)
{
	std::vector<uint8_t> buff;//buffer for coding
	std::vector<int32_t> param = std::vector<int>(2);
	param[0] = cv::IMWRITE_JPEG_QUALITY;
	param[1] = 50; //default(95) 0-100

	imencode(".jpg", input_mat_image, buff, param);

	copy(buff.begin(), buff.end(), jpg_image);

	return buff.size();
}
