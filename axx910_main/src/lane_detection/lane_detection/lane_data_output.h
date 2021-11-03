#ifndef __LANEDATAOUTPUT_H__
#define __LANEDATAOUTPUT_H__

typedef struct
{
	float max_left_lane_range;
	float max_right_lane_range;
	float polyfit_on_left_lane[3];
	float polyfit_on_right_lane[3];
} LaneDataOut;

extern LaneDataOut lane_data_output;

#endif