#include "lane_mapping.h"

void LaneMapper::getRadarPoint(vector<cv::Point2f> left_point, vector<cv::Point2f> right_point, vector<cv::Point2f> &left_radar_point, vector<cv::Point2f> &right_radar_point)
{
	size_t left_point_size = left_point.size();
	size_t right_point_size = right_point.size();
	float left_radar_x, left_radar_y;
	float right_radar_x, right_radar_y;

#if LOW_RESOLUTION
	for (size_t i = 0; i < left_point_size; i++)
	{
		left_radar_y = (left_point[i].x - 320.0f) * 1.75f / 175.0f;
		left_radar_x = (480.0f - left_point[i].y) * 25.0f / 480.0f + 2.0f;
		left_radar_point.push_back(cv::Point2f(left_radar_x, left_radar_y));
	}

	for (size_t i = 0; i < right_point_size; i++)
	{
		right_radar_y = (right_point[i].x - 320.0f) * 1.75f / 175.0f;
		right_radar_x = (480.0f - right_point[i].y) * 25.0f / 480.0f + 2.0f;
		right_radar_point.push_back(cv::Point2f(right_radar_x, right_radar_y));
	}
#else
	for (size_t i = 0; i < left_point_size; i++)
	{
		left_radar_y = (left_point[i].x - 320.0f) * 1.75f / 250.0f;
		left_radar_x = (480.0f - left_point[i].y) * 25.0f / 480.0f + 2.0f;
		left_radar_point.push_back(cv::Point2f(left_radar_x, left_radar_y));
	}

	for (size_t i = 0; i < right_point_size; i++)
	{
		right_radar_y = (right_point[i].x - 320.0f) * 1.75f / 250.0f;
		right_radar_x = (480.0f - right_point[i].y) * 25.0f / 480.0f + 2.0f;
		right_radar_point.push_back(cv::Point2f(right_radar_x, right_radar_y));
	}
#endif
}

vector<vector<cv::Point2f>> LaneMapper::getRadarPoint(int numOfLane, map<string, vector<float>> laneData)
{
	vector<vector<float>> radarPointX;
	vector<vector<float>> radarPointY;
	vector<vector<cv::Point2f>> radarPointSet;

	vector<float> nonzeroX = laneData["nonzeroX"];
	vector<float> nonzeroY = laneData["nonzeroY"];

	for (int i = 0; i < numOfLane; i++)
	{
		vector<float> laneInds = laneData["laneInds" + to_string(i)];
		vector<float> laneFit = laneData["laneFit" + to_string(i)];
		vector<float> pointY;
		vector<float> pointX;
		vector<float> index;

		int step = laneInds.size() / 29;

		for (int j = 0; j < laneInds.size(); j += step)
			index.push_back(laneInds[j]);

		sort(index.begin(), index.end());

		for (int k = 0; k < index.size(); k++)
		{
			pointY.push_back(nonzeroY[index[k]]);
			pointX.push_back(nonzeroX[index[k]]);	
		}
		radarPointX.push_back(pointX);
		radarPointY.push_back(pointY);
	}
	for (int x = 0; x < radarPointX.size(); x++)
	{
		vector<cv::Point2f> radarPointXY;
		for (int y = 0; y < radarPointX[0].size(); y++)
		{
			radarPointX[x][y] = (radarPointX[x][y] - 320.0f) * 7.0f / 320.0f + 3.4f;
			radarPointY[x][y] = (480.0f - radarPointY[x][y]) * 70.0f / 480.0f + 25.0f;
			radarPointXY.push_back(cv::Point2f(round(radarPointX[x][y] * 100) / 100.0f, round(radarPointY[x][y] * 100) / 100.0f));
		}
		radarPointSet.push_back(radarPointXY);
	}

	return radarPointSet;
}