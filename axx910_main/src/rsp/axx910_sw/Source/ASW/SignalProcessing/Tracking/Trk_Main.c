/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Trk_Main.h"
#include "Trk_Input.h"
#include "Trk_Clustering.h"
#include "Trk_Association.h"
#include "Trk_Managing.h"
#include "Trk_Correction.h"
#include "Trk_Prediction.h"
#include "Trk_SensorFusion.h"
#include "Trk_Output.h"


/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/
float32_t			gTrkCycleTime;
int16_t				gMeasCnt;
int16_t				gMsclCnt;

TrkEgoMotionInfo_t	gTrkEgoMotionInfo;
KalmanParam_t		KalmanParam;
MeasData_t			gMeasData[TRK_NUM_MEAS_MAX];
MeasClst_t			gMeasClst[TRK_NUM_CLUSTER_MAX];
ClstData_t			gClstData[TRK_NUM_CLUSTER_MAX];
TrackData_t			gTrackData[TRK_NUM_TRACK_MAX];
TrackOut_t			gTrackOut[TRK_NUM_TRACK_MAX];

/* Vision */
VisionObjData_t		gVisionObj[TRK_NUM_TRACK_MAX];
int16_t				gVisionObjCnt;
CameraParam_t		gCameraParam;

/* FreeSpace */
FreeSpaceOut_t		gFreespaceOut;

/* Road boundary */
RoadBoundary_t		gRoadBoundary[2];


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
static void Trk_vScanInit(void);

static void Trk_vEgoMotionInit(TrkEgoMotionInfo_t *TrkEgoMotionInfo);
static void Trk_vInitCameraParam(void);

/* Reflection type (body/wheel) detection using the prediction of updated/moving object */
static void Trk_vWheelMeasDetection(void);

static void undistort(float32_t p_d[2], float32_t p_u[2]);
static void normalize(float32_t pt_p[2], float32_t pt_n[2]);
static void denormalize(float32_t pt_n[2], float32_t pt_p[2]);
static void distort_normal(float32_t pt_p[2], float32_t pt_d[2]);
static void Trk_vRoadBoundary_Detection();
static void TrK_vRoadBoundary_GhostFiltering();

/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Trk_vSysInit(void)
{ 
	int16_t i_trk;
	int16_t i_clst;

	gTrkCycleTime = 0.0f;

	Trk_vInputInit();

	Trk_vEgoMotionInit(&gTrkEgoMotionInfo);

	for (i_clst = 0; i_clst < TRK_NUM_CLUSTER_MAX; i_clst++)
	{
		Clst_vInit(&gClstData[i_clst]);
	}

	for (i_trk = 0; i_trk < TRK_NUM_TRACK_MAX; i_trk++)
	{
		Trk_vInit(&gTrackData[i_trk]);
		Trk_vOutInit(&gTrackOut[i_trk]);
	}

#if TRK_VISION_OBJECT_INPUT
	Trk_vInitCameraParam();
#endif

	Trk_vInitOcc();

}


void Trk_vMain(void)
{
	/* Initialization */
	Trk_vScanInit();

	/* Input processing */
	Trk_vInputProc();

	/* Road boundary detection */
	Trk_vRoadBoundary_Detection();

	/* Pre-processing */
	Trk_vPrediction();
	Clst_vPrediction();

	/* Measurement clustering */
	Clst_vMeasClustering();

	/* Wheel measurment detection */
	Trk_vWheelMeasDetection();

	/* Sensor fusion object matching */
	Trk_vSensorFusionObjectMatching();
	Trk_vSensorFusionClusterMatching();
	Trk_vSensorFusionClassDecision();

	/* Cluster tracking */
	Clst_vAssociation();
	Clst_vManagement();
	Clst_vCorrection();

	/* Object tracking */
	Trk_vAssociation();
	Trk_vManagement();
	Trk_vCorrection();
	Trk_vAdditions();

	/* Freespace Detection */
	Trk_vProcessFreeSpace();

	/* Post-processing */
	TrK_vRoadBoundary_GhostFiltering();

	/* Output */
	Trk_vOut();

}


void Trk_vRoadBoundary_Detection()
{
#if TRK_RB_DETECTION_FLAG
	float32_t mat_A[3][3];
	float32_t mat_Ainv[3][3];
	float32_t mat_B[3];
	float32_t mat_model[3];
	float32_t mat_model_best[3];
	float32_t x_dist;
	float32_t y_dist;
	float32_t model_y_val;
	float32_t x_min;
	float32_t x_max;
	float32_t x_pos;
	float32_t y_pos; 

	int32_t i_dir;								/* road boundary direction: left/right */
	int32_t i_meas;								/* measurement index */
	int32_t i_meas_filter;						/* filtering measuremt index */
	int32_t n_meas_filter;						/* the number of filtering measurement */
	int32_t i_iter;
	int32_t i_rand;
	int32_t i_meas_random_sample[3];
	int32_t i_sample;
	int32_t i_inliers;
	int32_t i_map;
	int32_t min_idx;
	int32_t max_idx;
	int32_t valid_data_max;
	int32_t cnt;
	int32_t pass_cnt;
	
	uint8_t pass_cond;


	/************************************
	/******** Initialization ************
	************************************/
	/* Parameter passing */
	float32_t activation_speed_min_mps	= TRK_RB_ACTIVATION_SPEED_MIN_KPH / 3.6f;
	int32_t n_meas						= gMeasCnt;
	int32_t n_iter						= TRK_RB_RANSAC_NUM_ITERATION;
	float32_t meas_min_y_pos			= TRK_RB_MEAS_MIN_Y_POS;
	float32_t meas_min_x_pos			= TRK_RB_MEAS_MIN_X_POS;
	float32_t meas_max_x_pos			= TRK_RB_MEAS_MAX_X_POS;
	float32_t meas_max_x_pos_min_sample = TRK_RB_MEAS_MAX_X_POS_OF_MINIMUM_SAMPLE;
	int32_t min_cnt_for_regression		= TRK_RB_REGRESSION_MEAS_MIN_CNT;
	int32_t max_cnt_search_sample		= TRK_RB_RANSAC_SEARCH_SAMPLE_CNT_MAX;
	float32_t min_x_dist_btw_sample		= TRK_RB_RANSAC_MIN_X_DIST_BTW_SAMPLE;
	float32_t max_y_dist_btw_sample		= TRK_RB_RANSAC_MAX_Y_DIST_BTW_SAMPLE;
	int32_t min_cnt_inlier				= TRK_RB_RANSAC_MIN_CNT_INLIER;
	float32_t ransac_lat_error_min		= TRK_RB_RANSAC_LATERAL_ERROR_MIN;
	float32_t ransac_lat_error_slope	= TRK_RB_RANSAC_LATERAL_ERROR_SLOPE;
	float32_t min_dist_within_inlier	= TRK_RB_MIN_DIST_WITHIN_INLIER;
	int32_t rb_map_size					= TRK_RB_CONF_MAP_NUM_BIN;
	float32_t rb_conf_valid_min			= TRK_RB_CONF_VALID_MIN;


	/*****************************
	******* Initialization *******
	*****************************/
	/* Initialize rand() by seed */
	srand(0);

	for (i_dir = 0; i_dir < 2; i_dir++)
	{
		/* Init output */
		gRoadBoundary[i_dir].error_flag = RB_ERROR_INIT;		/* initialized */
		gRoadBoundary[i_dir].pass_sampling_cnt = 0;
		memset(gRoadBoundary[i_dir].rb_y_pos, 0, rb_map_size * sizeof(float32_t));
		memset(gRoadBoundary[i_dir].rb_conf, 0, rb_map_size * sizeof(float32_t));
		memset(gRoadBoundary[i_dir].quad_coef, 0, 3 * sizeof(float32_t));
	}


	/*****************************************
	******* Check operating condition  *******
	*****************************************/
	/* to bo placed on the begin of algorith */
	if (gTrkEgoMotionInfo.f32VehSpeed_comp < activation_speed_min_mps)
	{
		gRoadBoundary[0].error_flag = RB_ERROR_UNDER_ACT_SPD;
		gRoadBoundary[1].error_flag = RB_ERROR_UNDER_ACT_SPD;
		return;
	}


	/************************************
	******* Measurement filtering *******
	************************************/
	for (i_dir = 0; i_dir < 2; i_dir++)
	{
		cnt = 0;
		for (i_meas = 0; i_meas < n_meas; i_meas++)
		{
			if (gMeasData[i_meas].MovState == STATIONARY) {}
			else { continue; }

			if (gMeasData[i_meas].f32PosX >= meas_max_x_pos_min_sample) {}
			else if ((i_dir == 0) && (gMeasData[i_meas].f32PosY >  meas_min_y_pos)) {}
			else if ((i_dir == 1) && (gMeasData[i_meas].f32PosY < -meas_min_y_pos)) {}
			else { continue; }

			if (_trk_isbound(gMeasData[i_meas].f32PosX, meas_min_x_pos, meas_max_x_pos)) {}
			else { continue; }

			gRoadBoundary[i_dir].meas_filter[cnt] = i_meas;
			cnt++;
		}
		gRoadBoundary[i_dir].n_meas_filter = cnt;
	}


	/********************************************
	******* RANSAC (fixed random sample) ********
	********************************************/
	for (i_dir = 0; i_dir < 2; i_dir++)
	{
		n_meas_filter = gRoadBoundary[i_dir].n_meas_filter;
		if (n_meas_filter >= min_cnt_for_regression)
		{
			valid_data_max = min_cnt_inlier;
			pass_cnt = 0;
			memset(mat_model_best, 0, 3 * sizeof(float32_t));
			for (i_iter = 0; i_iter < n_iter; i_iter++)
			{
				/* Random sampling - 3 point	*/

				/***** First *****/
				i_meas_random_sample[0] = floor((rand() % n_meas_filter));

				/***** Second *****/
				pass_cond = 0;
				for (i_rand = 0; i_rand < max_cnt_search_sample; i_rand++)
				{
					i_meas_random_sample[1] = floor((rand() % n_meas_filter));
					x_dist = _trk_abs(gMeasData[gRoadBoundary[i_dir].meas_filter[i_meas_random_sample[1]]].f32PosX - gMeasData[gRoadBoundary[i_dir].meas_filter[i_meas_random_sample[0]]].f32PosX);
					y_dist = _trk_abs(gMeasData[gRoadBoundary[i_dir].meas_filter[i_meas_random_sample[1]]].f32PosY - gMeasData[gRoadBoundary[i_dir].meas_filter[i_meas_random_sample[0]]].f32PosY);

					if ((i_meas_random_sample[1] != i_meas_random_sample[0])
						&& (i_meas_random_sample[1] >= 0)
						&& (x_dist >= min_x_dist_btw_sample)
						&& (y_dist <= max_y_dist_btw_sample)
						)
					{
						pass_cond = 1;
						break;
					}
				}

				if (pass_cond != 1)
				{
					continue;
				}

				/***** Third *****/
				pass_cond = 0;
				for (i_rand = 0; i_rand < max_cnt_search_sample; i_rand++)
				{
					i_meas_random_sample[2] = floor((rand() % n_meas_filter));

					x_dist = _trk_abs(gMeasData[gRoadBoundary[i_dir].meas_filter[i_meas_random_sample[2]]].f32PosX - gMeasData[gRoadBoundary[i_dir].meas_filter[i_meas_random_sample[0]]].f32PosX);
					x_dist = _trk_min(x_dist, _trk_abs(gMeasData[gRoadBoundary[i_dir].meas_filter[i_meas_random_sample[2]]].f32PosX - gMeasData[gRoadBoundary[i_dir].meas_filter[i_meas_random_sample[1]]].f32PosX));

					y_dist = _trk_abs(gMeasData[gRoadBoundary[i_dir].meas_filter[i_meas_random_sample[2]]].f32PosY - gMeasData[gRoadBoundary[i_dir].meas_filter[i_meas_random_sample[0]]].f32PosY);
					y_dist = _trk_max(y_dist, _trk_abs(gMeasData[gRoadBoundary[i_dir].meas_filter[i_meas_random_sample[2]]].f32PosY - gMeasData[gRoadBoundary[i_dir].meas_filter[i_meas_random_sample[1]]].f32PosY));

					x_min  = _trk_min(gMeasData[gRoadBoundary[i_dir].meas_filter[i_meas_random_sample[0]]].f32PosX, gMeasData[gRoadBoundary[i_dir].meas_filter[i_meas_random_sample[1]]].f32PosX);
					x_min = _trk_min(x_min, gMeasData[gRoadBoundary[i_dir].meas_filter[i_meas_random_sample[2]]].f32PosX);

					if ((i_meas_random_sample[2] != i_meas_random_sample[0])
						&& (i_meas_random_sample[2] != i_meas_random_sample[1])
						&& (i_meas_random_sample[2] >= 0)
						&& (x_dist >= min_x_dist_btw_sample)
						&& (y_dist <= max_y_dist_btw_sample)
						&& (x_min <= meas_max_x_pos_min_sample)
						)
					{
						pass_cond = 1;
						break;
					}
				}

				if (pass_cond != 1)
				{
					continue;
				}

				pass_cnt++;

				/* Quadratice regression (A * X = B)	*/
				for (i_sample = 0; i_sample < 3; i_sample++)
				{
					i_meas = gRoadBoundary[i_dir].meas_filter[i_meas_random_sample[i_sample]];
					mat_A[i_sample][0] = _trk_pow2(gMeasData[i_meas].f32PosX);
					mat_A[i_sample][1] = gMeasData[i_meas].f32PosX;
					mat_A[i_sample][2] = 1;

					mat_B[i_sample] = gMeasData[i_meas].f32PosY;
				}

				MatInv3x3(mat_A, mat_Ainv);
				MatMul_3x3and3x1(mat_Ainv, mat_B, mat_model);


				/* Evaluation */
				cnt = 0;
				for (i_meas_filter = 0; i_meas_filter < n_meas_filter; i_meas_filter++)
				{

					i_meas = gRoadBoundary[i_dir].meas_filter[i_meas_filter];
					model_y_val = mat_model[0] * _trk_pow2(gMeasData[i_meas].f32PosX) + mat_model[1] * gMeasData[i_meas].f32PosX + mat_model[2];

					if (_trk_abs(gMeasData[i_meas].f32PosY - model_y_val) < ransac_lat_error_min + ransac_lat_error_slope * gMeasData[i_meas].f32PosX)
					{
						cnt++;
					}
				}

				if (cnt > valid_data_max)
				{
					memcpy(mat_model_best, mat_model, 3 * sizeof(float32_t));
					valid_data_max = cnt;
				}
			}

			gRoadBoundary[i_dir].pass_sampling_cnt = pass_cnt;
			gRoadBoundary[i_dir].n_inliers = valid_data_max;
			memcpy(gRoadBoundary[i_dir].quad_coef, mat_model_best, 3 * sizeof(float32_t));

			if (valid_data_max > min_cnt_inlier)
			{
				gRoadBoundary[i_dir].error_flag = RB_ERROR_NONE;	/* 0: succeed */
			}
			else
			{
				gRoadBoundary[i_dir].error_flag = RB_ERROR_LOW_NUM_INLIER;	/* 2: fail to fit data */
			}
		}
		else
		{
			gRoadBoundary[i_dir].error_flag = RB_ERROR_LON_NUM_MEAS;		/* 1: not enough data for regression */
		}
	}


	/***********************************
	********** Find inliers ************
	***********************************/
	for (i_dir = 0; i_dir < 2; i_dir++)
	{
		if (gRoadBoundary[i_dir].error_flag == RB_ERROR_NONE)
		{
			x_max = meas_min_x_pos;
			x_min = meas_max_x_pos;
			cnt = 0;

			for (i_meas_filter = 0; i_meas_filter < gRoadBoundary[i_dir].n_meas_filter; i_meas_filter++)
			{
				i_meas = gRoadBoundary[i_dir].meas_filter[i_meas_filter];

				model_y_val = gRoadBoundary[i_dir].quad_coef[0] * gMeasData[i_meas].f32PosX * gMeasData[i_meas].f32PosX
							+ gRoadBoundary[i_dir].quad_coef[1] * gMeasData[i_meas].f32PosX 
							+ gRoadBoundary[i_dir].quad_coef[2];

				if (_trk_abs(gMeasData[i_meas].f32PosY - model_y_val) < ransac_lat_error_min + ransac_lat_error_slope * gMeasData[i_meas].f32PosX)
				{
					gMeasData[i_meas].rb_flag = 1;
					gRoadBoundary[i_dir].inliers[cnt] = i_meas;

					if (gMeasData[i_meas].f32PosX < x_min)
					{
						x_min = gMeasData[i_meas].f32PosX;
						min_idx = i_meas;
					}

					if (gMeasData[i_meas].f32PosX > x_max)
					{
						x_max = gMeasData[i_meas].f32PosX;
						max_idx = i_meas;
					}
					cnt++;
				}
			}

			if (cnt > 0)
			{
				if (_sp_hypotf(gMeasData[max_idx].f32PosX - gMeasData[min_idx].f32PosX, gMeasData[max_idx].f32PosY - gMeasData[min_idx].f32PosY) < min_dist_within_inlier)
				{
					gRoadBoundary[i_dir].error_flag = RB_ERROR_SMALL_INLIER;
				}
			}
		}
	}


	/******************************************
	******* Project inliers to x-axis *********
	******************************************/
	for (i_dir = 0; i_dir < 2; i_dir++)
	{
		/* Initialization */
		memset(gRoadBoundary[i_dir].rb_conf,  0, rb_map_size * sizeof(float32_t));
		for (i_map = 0; i_map < rb_map_size; i_map++)
		{
			if (i_dir == 0)
			{
				gRoadBoundary[i_dir].rb_y_min[i_map] = -1000.0f;
			}
			else
			{
				gRoadBoundary[i_dir].rb_y_min[i_map] = 1000.0f;
			}
		}

		/* Check rb confidency and minimum y pos from inliers */
		for (i_inliers = 0; i_inliers < gRoadBoundary[i_dir].n_inliers; i_inliers++)
		{
			i_meas = gRoadBoundary[i_dir].inliers[i_inliers];

			/* get index of probability map: 0 ~ rb_map_size */
			i_map = val2bin(gMeasData[i_meas].f32PosX, meas_min_x_pos, meas_max_x_pos, (float32_t)rb_map_size);
			gRoadBoundary[i_dir].rb_conf[i_map]++;
			gRoadBoundary[i_dir].rb_y_min[i_map] = _trk_min(gMeasData[i_meas].f32PosX, gRoadBoundary[i_dir].rb_y_min[i_map]);
		}

		/* Find x pos range of rb map */
		gRoadBoundary[i_dir].rb_x_max = meas_min_x_pos;
		gRoadBoundary[i_dir].rb_x_min = meas_max_x_pos;
		for (i_map = 0; i_map < rb_map_size; i_map++)
		{
			if (gRoadBoundary[i_dir].rb_conf[i_map] >= rb_conf_valid_min)
			{
				gRoadBoundary[i_dir].rb_x_max = _trk_max(gRoadBoundary[i_dir].rb_x_max, i_map);
				gRoadBoundary[i_dir].rb_x_min = _trk_min(gRoadBoundary[i_dir].rb_x_min, i_map);
			}
		}

		/* Calc y pos of rb map */
		for (i_map = gRoadBoundary[i_dir].rb_x_min; i_map <= gRoadBoundary[i_dir].rb_x_max; i_map++)
		{
			x_pos = bin2val((float32_t)i_map, meas_min_x_pos, meas_max_x_pos, (float32_t)rb_map_size);
			y_pos = gRoadBoundary[i_dir].quad_coef[0] * x_pos * x_pos
				  + gRoadBoundary[i_dir].quad_coef[1] * x_pos
				  + gRoadBoundary[i_dir].quad_coef[2];

			gRoadBoundary[i_dir].rb_y_pos[i_map] = y_pos;
		}

	}
#endif
}



static void TrK_vRoadBoundary_GhostFiltering()
{
#if TRK_RB_GHOST_FILTERING_FLAG
	int32_t i_obj;
	int32_t i_map;
	int32_t i_dir;

	uint8_t ghost_flag;
	float32_t meas_min_x_pos						= TRK_RB_MEAS_MIN_X_POS;
	float32_t meas_max_x_pos						= TRK_RB_MEAS_MAX_X_POS;
	int32_t rb_map_size								= TRK_RB_CONF_MAP_NUM_BIN;
	float32_t rb_ghost_filtering_x_margin			= TRK_RB_GHOST_FILTERING_X_MARGIN;
	float32_t rb_ghost_filtering_y_margin			= TRK_RB_GHOST_FILTERING_Y_MARGIN;
	float32_t rb_ghost_filtering_object_deletion	= TRK_RB_GHOST_FILTERING_OBJECT_DELETION_FLAG;
	
	for (i_dir = 0; i_dir < 2; i_dir++)
	{
		if (gRoadBoundary[i_dir].error_flag == RB_ERROR_NONE)
		{		
			for (i_obj = 0; i_obj < TRK_NUM_TRACK_MAX; i_obj++)
			{
				if ((gTrackData[i_obj].Status != INVALID) 
					&& ((gTrackData[i_obj].MovState == PRECEDING) || (gTrackData[i_obj].MovState == ONCOMING))
					)
				{
					i_map = val2bin(gTrackData[i_obj].UpdState.f32StateX[0], meas_min_x_pos, meas_max_x_pos, (float32_t)rb_map_size);
					
					if (_trk_isbound(i_map, gRoadBoundary[i_dir].rb_x_min - rb_ghost_filtering_x_margin, 
											gRoadBoundary[i_dir].rb_x_max + rb_ghost_filtering_x_margin))
					{
						if (((i_dir == 0) 
							&& (gTrackData[i_obj].UpdState.f32StateY[0] + gTrackData[i_obj].UpdState.f32Width * 0.5 
								> gRoadBoundary[i_dir].rb_y_pos[i_map] - rb_ghost_filtering_y_margin))
						 || ((i_dir == 1) 
							 && (gTrackData[i_obj].UpdState.f32StateY[0] - gTrackData[i_obj].UpdState.f32Width * 0.5 
								< gRoadBoundary[i_dir].rb_y_pos[i_map] + rb_ghost_filtering_y_margin)))
						{
							if (rb_ghost_filtering_object_deletion == 1)
							{
								Trk_vInit(&gTrackData[i_obj]);
							}
							else
							{
								gTrackData[i_obj].ghost_flag = 1;
							}

							continue;
						}
					}
				}
			}
		}
	}
#endif
}





void MatInv3x3(float32_t src[][3], float32_t dst[][3])
{
	float32_t det;

	dst[0][0] = (src[1][1] * src[2][2] - src[1][2] * src[2][1]);
	dst[0][1] = (src[0][1] * src[2][2] - src[0][2] * src[2][1]) * (-1);
	dst[0][2] = (src[0][1] * src[1][2] - src[0][2] * src[1][1]);
	dst[1][0] = (src[1][0] * src[2][2] - src[1][2] * src[2][0]) * (-1);
	dst[1][1] = (src[0][0] * src[2][2] - src[0][2] * src[2][0]);
	dst[1][2] = (src[0][0] * src[1][2] - src[0][2] * src[1][0]) * (-1);
	dst[2][0] = (src[1][0] * src[2][1] - src[1][1] * src[2][1]);
	dst[2][1] = (src[0][0] * src[2][1] - src[0][1] * src[2][0]) * (-1);
	dst[2][2] = (src[0][0] * src[1][1] - src[0][1] * src[1][0]);

	det = (src[0][0] * dst[0][0]) + (src[0][1] * dst[1][0]) + (src[0][2] * dst[2][0]);

	dst[0][0] /= (det + TRK_APPROXIMATE_ZERO);
	dst[0][1] /= (det + TRK_APPROXIMATE_ZERO);
	dst[0][2] /= (det + TRK_APPROXIMATE_ZERO);
	dst[1][0] /= (det + TRK_APPROXIMATE_ZERO);
	dst[1][1] /= (det + TRK_APPROXIMATE_ZERO);
	dst[1][2] /= (det + TRK_APPROXIMATE_ZERO);
	dst[2][0] /= (det + TRK_APPROXIMATE_ZERO);
	dst[2][1] /= (det + TRK_APPROXIMATE_ZERO);
	dst[2][2] /= (det + TRK_APPROXIMATE_ZERO);
}


/* image to world projection on ground plane using homography matrix */
void img2wld(float32_t img[3], float32_t wld[3], float32_t H[][3])
{
	float32_t img_n[3];

#if TRK_CAMERA_INTRINSIC_UNDISTORTION_FLAG
	undistort(img, img);
#endif

	MatMul_3x3and3x1(H, img, wld);
	wld[0] = wld[0] / (wld[2] + TRK_APPROXIMATE_ZERO);
	wld[1] = wld[1] / (wld[2] + TRK_APPROXIMATE_ZERO);
}


/* world to image projection using pojection matrix */
void wld2img(float32_t wld[4], float32_t img[3], float32_t P[][4])
{
	MatMul_3x4and4x1(P, wld, img);
	img[0] = img[0] / (img[2] + TRK_APPROXIMATE_ZERO);
	img[1] = img[1] / (img[2] + TRK_APPROXIMATE_ZERO);

#if TRK_CAMERA_INTRINSIC_UNDISTORTION_FLAG
	normalize(img, img);
	distort_normal(img, img);
	denormalize(img, img);
#endif
}


void undistort(float32_t p_d[2], float32_t p_u[2])
{
	int16_t i_test;
	float32_t p_d_n[2];
	float32_t p_u_n[2];
	float32_t p_u_n_test[2];
	float32_t err[2];

	normalize(p_d, p_d_n);

	p_u_n[0] = p_d_n[0];
	p_u_n[1] = p_d_n[1];

	for (i_test = 0 ; i_test < 3 ; i_test++)
	{
		distort_normal(p_u_n, p_u_n_test);
		err[0] = p_u_n_test[0] - p_d_n[0];
		err[1] = p_u_n_test[1] - p_d_n[1];
		p_u_n[0] -= err[0] * 0.5;
		p_u_n[1] -= err[1] * 0.5;

		if ((err[0] < 1) && (err[1] < 1))
		{
			break;
		}
	}

	denormalize(p_u_n, p_u);
}


void normalize(float32_t pt_p[2], float32_t pt_n[2])
{
	pt_n[1] = (pt_p[1] - TRK_CAMERA_INTRINSIC_CY) / TRK_CAMERA_INTRINSIC_FY;
	pt_n[0] = (pt_p[0] - TRK_CAMERA_INTRINSIC_CX) / TRK_CAMERA_INTRINSIC_FX - TRK_CAMERA_INTRINSIC_SKEW * pt_n[1];
}


void denormalize(float32_t pt_n[2], float32_t pt_p[2])
{
	pt_p[0] = TRK_CAMERA_INTRINSIC_FX * (pt_n[0] + TRK_CAMERA_INTRINSIC_SKEW * pt_n[1]) + TRK_CAMERA_INTRINSIC_CX;
	pt_p[1] = TRK_CAMERA_INTRINSIC_FY *  pt_n[1]										+ TRK_CAMERA_INTRINSIC_CY;
}


void distort_normal(float32_t pt_p[2], float32_t pt_d[2])
{
	float32_t r2;
	float32_t radial_d;

	r2 = pt_p[0] * pt_p[0] + pt_p[1] * pt_p[1];
	radial_d = 1 + TRK_CAMERA_INTRINSIC_K1 * (r2)
				 + TRK_CAMERA_INTRINSIC_K2 * (r2 * r2) 
				 + TRK_CAMERA_INTRINSIC_K3 * (r2 * r2 * r2);

	pt_d[0] = radial_d * pt_p[0] + 2 * TRK_CAMERA_INTRINSIC_P1 * pt_p[0] * pt_p[1] + TRK_CAMERA_INTRINSIC_P2 * (r2 + 2 * pt_p[0] * pt_p[0]);
	pt_d[1] = radial_d * pt_p[0] + TRK_CAMERA_INTRINSIC_P1 * (r2 + 2 * pt_p[1] * pt_p[1]) + 2 * TRK_CAMERA_INTRINSIC_P2 * pt_p[0] * pt_p[1];
}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/

static void Trk_vScanInit(void)
{
	int16_t i_trk;
	int16_t i_clst;

	gTrkCycleTime = gSpCycleTime;

	KalmanParam.F[0][0] = 1.0f;
	KalmanParam.F[0][1] = gTrkCycleTime;
	KalmanParam.F[1][0] = 0.0f;
	KalmanParam.F[1][1] = 1.0f;

	MatTranspose_2x2(KalmanParam.F, KalmanParam.F_Trs);

	KalmanParam.H[0][0] = 1.0f;
	KalmanParam.H[0][1] = 0.0f;
	KalmanParam.H[1][0] = 0.0f;
	KalmanParam.H[1][1] = 1.0f;

	MatTranspose_2x2(KalmanParam.H, KalmanParam.H_Trs);

	KalmanParam.I[0][0] = 1.0f;
	KalmanParam.I[0][1] = 0.0f;
	KalmanParam.I[1][0] = 0.0f;
	KalmanParam.I[1][1] = 1.0f;

	KalmanParam.Qx[0][0] = _sp_pow3(gTrkCycleTime) * TRKLET_STD_Q_ACC_X / 3.0f;
	KalmanParam.Qx[0][1] = 0.0f;
	KalmanParam.Qx[1][0] = KalmanParam.Qx[0][1];
	KalmanParam.Qx[1][1] = gTrkCycleTime * TRKLET_STD_Q_ACC_X;

	KalmanParam.Qy[0][0] = _sp_pow3(gTrkCycleTime) * TRKLET_STD_Q_ACC_Y / 3.0f;
	KalmanParam.Qy[0][1] = 0.0f;
	KalmanParam.Qy[1][0] = KalmanParam.Qy[0][1];
	KalmanParam.Qy[1][1] = gTrkCycleTime * TRKLET_STD_Q_ACC_Y;

	/* Initialize Ego and Measurement info */
	Trk_vInputInit();

	/* Initialize Cluster Data */
	for (i_clst = 0; i_clst < TRK_NUM_CLUSTER_MAX; i_clst++)
	{
		if (gClstData[i_clst].Status != INVALID)
		{
			gClstData[i_clst].s16AssoMeasClstCnt = 0;
			gClstData[i_clst].s16AssoMeasNoisePtCnt = 0;
		}
	}

	/* Initialize Track MeasState */
	for (i_trk = 0; i_trk < TRK_NUM_TRACK_MAX; i_trk++)
	{
		if (gTrackData[i_trk].Status != INVALID)
		{
			gTrackData[i_trk].MeasState.f32StateX[0] = 0.0f;
			gTrackData[i_trk].MeasState.f32StateX[1] = 0.0f;

			gTrackData[i_trk].MeasState.f32StateY[0] = 0.0f;
			gTrackData[i_trk].MeasState.f32StateY[1] = 0.0f;

			gTrackData[i_trk].MeasState.f32Ref_PosX = 0.0f;
			gTrackData[i_trk].MeasState.f32Ref_PosY = 0.0f;

			gTrackData[i_trk].MeasState.f32BoundingBoxX[0] = -10000.0f;
			gTrackData[i_trk].MeasState.f32BoundingBoxX[1] = -10000.0f;
			gTrackData[i_trk].MeasState.f32BoundingBoxX[2] = 10000.0f;
			gTrackData[i_trk].MeasState.f32BoundingBoxX[3] = 10000.0f;

			gTrackData[i_trk].MeasState.f32BoundingBoxY[0] = -10000.0f;
			gTrackData[i_trk].MeasState.f32BoundingBoxY[1] = 10000.0f;
			gTrackData[i_trk].MeasState.f32BoundingBoxY[2] = 10000.0f;
			gTrackData[i_trk].MeasState.f32BoundingBoxY[3] = -10000.0f;

			gTrackData[i_trk].MeasState.f32Length = 0.0f;
			gTrackData[i_trk].MeasState.f32Width = 0.0f;

			gTrackData[i_trk].MeasState.f32StateHeading[0] = 0.0f;
			gTrackData[i_trk].MeasState.f32StateHeading[1] = 0.0f;
			gTrackData[i_trk].u8Merging_Flag = 0;
		
			/* Road boundary */
			gTrackData[i_trk].ghost_flag = 0;

			/* Sensor fusion */
			gTrackData[i_trk].fusion_state = SF_RADAR_ONLY;
			gTrackData[i_trk].bbox_overlap_ratio = 0.0f;
			gTrackData[i_trk].match_vision_obj_idx = -1;
		}
	}

}


/* Reflection type (body/wheel) detection using the prediction of updated/moving object */
static void Trk_vWheelMeasDetection(void)
{
	int16_t i_clst;
	int16_t i_clst2;
	int16_t i_trk;
	int16_t i_meas;
	float32_t PosObj[2];
	float32_t PosMeas[2];
	float32_t PosDiff[2];
	float32_t Expect_Trk_Rng_rate;
	float32_t abs_temp_ResRr;
	float32_t gate_posx;
	float32_t gate_posy;
	float32_t gate_rr;

	/* Wheelspin detection based on MsmtClst */
	for (i_clst = 0; i_clst < TRK_NUM_CLUSTER_MAX; i_clst++)
	{
		if ((gMeasClst[i_clst].State == VALID_CLST) &&
			(gMeasClst[i_clst].MovState != STATIONARY) &&
			(gMeasClst[i_clst].ReflectType != REFLECT_TYPE_WHEEL))
		{
			for (i_clst2 = (i_clst + 1); i_clst2 < TRK_NUM_CLUSTER_MAX; i_clst2++)
			{
				if ((gMeasClst[i_clst2].State == VALID_CLST) &&
					(gMeasClst[i_clst2].MovState != STATIONARY) &&
					(gMeasClst[i_clst2].ReflectType != REFLECT_TYPE_WHEEL))
				{
					if ((_sp_abs(gMeasClst[i_clst].Xpos.f32Mean - gMeasClst[i_clst2].Xpos.f32Mean) < ((gMeasClst[i_clst].Xpos.f32StdDev + gMeasClst[i_clst2].Xpos.f32StdDev) * 0.5f + 0.3f)) &&
						(_sp_abs(gMeasClst[i_clst].Ypos.f32Mean - gMeasClst[i_clst2].Ypos.f32Mean) < ((gMeasClst[i_clst].Ypos.f32StdDev + gMeasClst[i_clst2].Ypos.f32StdDev) * 0.5f + 0.3f)) &&
						(_sp_abs(gMeasClst[i_clst].RangeRate.f32Mean - gMeasClst[i_clst2].RangeRate.f32Mean) > 1.0f))
					{
						if ((gMeasClst[i_clst].Xpos.f32StdDev > gMeasClst[i_clst2].Xpos.f32StdDev) &&
							(gMeasClst[i_clst].Ypos.f32StdDev > gMeasClst[i_clst2].Ypos.f32StdDev))
						{
							gMeasClst[i_clst2].ReflectType = REFLECT_TYPE_WHEEL;
						}
						else if ((gMeasClst[i_clst].Xpos.f32StdDev < gMeasClst[i_clst2].Xpos.f32StdDev) &&
							(gMeasClst[i_clst].Ypos.f32StdDev < gMeasClst[i_clst2].Ypos.f32StdDev))
						{
							gMeasClst[i_clst].ReflectType = REFLECT_TYPE_WHEEL;
						}
						else
						{
							if (gMeasClst[i_clst].Xpos.f32StdDev - gMeasClst[i_clst2].Xpos.f32StdDev > 0.3f)
							{
								gMeasClst[i_clst2].ReflectType = REFLECT_TYPE_WHEEL;
							}
							else if (gMeasClst[i_clst].Xpos.f32StdDev - gMeasClst[i_clst2].Xpos.f32StdDev < -0.3f)
							{
								gMeasClst[i_clst].ReflectType = REFLECT_TYPE_WHEEL;
							}
							else if (gMeasClst[i_clst].Ypos.f32StdDev - gMeasClst[i_clst2].Ypos.f32StdDev > 0.3f)
							{
								gMeasClst[i_clst2].ReflectType = REFLECT_TYPE_WHEEL;
							}
							else if (gMeasClst[i_clst].Ypos.f32StdDev - gMeasClst[i_clst2].Ypos.f32StdDev < -0.3f)
							{
								gMeasClst[i_clst].ReflectType = REFLECT_TYPE_WHEEL;
							}
							else
							{
								/* Do nothing */
							}
						}
					}
				}
			}
		}
	}

	/* Find neighbor measurement from moving/updated object on previous scan */
	for (i_trk = 0; i_trk < TRK_NUM_TRACK_MAX; i_trk++)
	{
		if ((gTrackData[i_trk].Status == UPDATED_TRACK)
			&& ((gTrackData[i_trk].MovState == PRECEDING) || (gTrackData[i_trk].MovState == ONCOMING)))
		{
			PosObj[0] = NegRotateX(gTrackData[i_trk].PredState.f32StateX[0], gTrackData[i_trk].PredState.f32StateY[0], gTrackData[i_trk].PredState.f32StateHeading[0]);
			PosObj[1] = NegRotateY(gTrackData[i_trk].PredState.f32StateX[0], gTrackData[i_trk].PredState.f32StateY[0], gTrackData[i_trk].PredState.f32StateHeading[0]);

			for (i_meas = 0; i_meas < gMeasCnt; i_meas++)
			{
				if (gMeasData[i_meas].ReflectType == REFLECT_TYPE_UNKNOWN)
				{
					gate_posx = (gTrackData[i_trk].PredState.f32Length * 0.5f) + TRK_WHEEL_DETECTION_BODY_GATE_POS_LONG;
					gate_posy = (gTrackData[i_trk].PredState.f32Width * 0.5f) + TRK_WHEEL_DETECTION_BODY_GATE_POS_LAT;
					gate_rr = TRK_WHEEL_DETECTION_BODY_GATE_RANGE_RATE;

					PosMeas[0] = NegRotateX(gMeasData[i_meas].f32PosX, gMeasData[i_meas].f32PosY, gTrackData[i_trk].PredState.f32StateHeading[0]);
					PosMeas[1] = NegRotateY(gMeasData[i_meas].f32PosX, gMeasData[i_meas].f32PosY, gTrackData[i_trk].PredState.f32StateHeading[0]);

					MatSub_2x1(PosObj, PosMeas, PosDiff)
					MatAbs2x1(PosDiff, PosDiff);

					if ((PosDiff[0] < gate_posx) && (PosDiff[1] < gate_posy))
					{
						Expect_Trk_Rng_rate = NegRotateX(gTrackData[i_trk].PredState.f32StateX[1] - gTrkEgoMotionInfo.f32VelX, gTrackData[i_trk].PredState.f32StateY[1] - gTrkEgoMotionInfo.f32VelY, gMeasData[i_meas].f32AziAng);
						abs_temp_ResRr = _trk_abs(gMeasData[i_meas].f32RangeRate_rdr - Expect_Trk_Rng_rate);

						if (abs_temp_ResRr <= gate_rr)
						{
							gMeasData[i_meas].ReflectTypeProb += gTrackData[i_trk].u16StatusAge;
						}
						else
						{
							gMeasData[i_meas].ReflectTypeProb -= gTrackData[i_trk].u16StatusAge;
						}
					}
				}
			}
		}
	}

	/* Determine measurement reflection type */
	for (i_meas = 0; i_meas < gMeasCnt; i_meas++)
	{
		if (gMeasData[i_meas].s16Cluster_idx == -1)
		{
			if (gMeasData[i_meas].ReflectType == REFLECT_TYPE_UNKNOWN)
			{
				if (gMeasData[i_meas].ReflectTypeProb > 0)
				{
					gMeasData[i_meas].ReflectType = REFLECT_TYPE_BODY;
				}
				else if (gMeasData[i_meas].ReflectTypeProb < 0)
				{
					gMeasData[i_meas].ReflectType = REFLECT_TYPE_WHEEL;
				}
				else
				{
					gMeasData[i_meas].ReflectType = REFLECT_TYPE_UNKNOWN;
				}
			}
		}
	}
}


static void Trk_vEgoMotionInit(TrkEgoMotionInfo_t *TrkEgoMotionInfo)
{
	TrkEgoMotionInfo->f32VehSpeed_can = 0.0f;
	TrkEgoMotionInfo->f32VehSpeed_comp = 0.0f;
	TrkEgoMotionInfo->f32YawRate_can = 0.0f;
	TrkEgoMotionInfo->f32YawRate_comp = 0.0f;
	TrkEgoMotionInfo->f32SteerAng_deg = 0.0f;

	TrkEgoMotionInfo->f32VelX = 0.0f;
	TrkEgoMotionInfo->f32VelY = 0.0f;
	TrkEgoMotionInfo->f32DeltaYaw_deg = 0.0f;
	TrkEgoMotionInfo->f32PathRadius = 0.0f;

	TrkEgoMotionInfo->prev_VehSpeed = 0.0f;
	TrkEgoMotionInfo->prev_YawRate = 0.0f;
	TrkEgoMotionInfo->prev_SteerAngle = 0.0f;
	TrkEgoMotionInfo->init_flag = 0;
}


static void Trk_vInitCameraParam(void)
{
	float32_t temp3x3_1[3][3];
	float32_t temp3x3_2[3][3];
	float32_t temp3x3_3[3][3];
	float32_t temp3x4[3][4];
	float32_t temp3x1[3];

	gCameraParam.image_size[0] = TRK_IMAGE_WIDTH;
	gCameraParam.image_size[1] = TRK_IMAGE_HEIGHT;

	/* Intrinsic */
	gCameraParam.K[0][0] = TRK_CAMERA_INTRINSIC_FX;
	gCameraParam.K[0][1] = TRK_CAMERA_INTRINSIC_SKEW;
	gCameraParam.K[0][2] = TRK_CAMERA_INTRINSIC_CX;
	gCameraParam.K[1][0] = 0.0f;
	gCameraParam.K[1][1] = TRK_CAMERA_INTRINSIC_FY;
	gCameraParam.K[1][2] = TRK_CAMERA_INTRINSIC_CY;
	gCameraParam.K[2][0] = 0.0f;
	gCameraParam.K[2][1] = 0.0f;
	gCameraParam.K[2][2] = 1.0f;

	/* Distortion */
	gCameraParam.k1 = TRK_CAMERA_INTRINSIC_K1;
	gCameraParam.k2 = TRK_CAMERA_INTRINSIC_K2;
	gCameraParam.k3 = TRK_CAMERA_INTRINSIC_K3;
	gCameraParam.p1 = TRK_CAMERA_INTRINSIC_P1;
	gCameraParam.p2 = TRK_CAMERA_INTRINSIC_P2;

	/* Extrinsic */
	MatRotZ(_trk_deg2rad(TRK_CAMERA_EXTRINSIC_ANGLE_ROLL * (-1)), temp3x3_1);		/* 1st rotation : "un-roll" */
	MatRotX(_trk_deg2rad(TRK_CAMERA_EXTRINSIC_ANGLE_PITCH - 90.0f), temp3x3_2);		/* "un-pitch" and point camera's Z down */
	MatMul_3x3and3x3(temp3x3_1, temp3x3_2, temp3x3_3);

	MatRotZ(_trk_deg2rad(TRK_CAMERA_EXTRINSIC_ANGLE_YAW), temp3x3_1);				/* point the camera forward */
	MatMul_3x3and3x3(temp3x3_3, temp3x3_1, temp3x3_2);

	temp3x1[0] = TRK_CAMERA_EXTRINSIC_POS_Y;										/* Translation in world units */
	temp3x1[1] = TRK_CAMERA_EXTRINSIC_POS_X;
	temp3x1[2] = TRK_CAMERA_EXTRINSIC_POS_Z;
	MatMul_3x3and3x1(temp3x3_2, temp3x1, gCameraParam.t);
	
	MatRotZ(_trk_deg2rad(90.0f), temp3x3_3);										/* X-Y swap */
	MatMul_3x3and3x3(temp3x3_2, temp3x3_3, temp3x3_1);

	MatRotY(_trk_deg2rad(-180.0f), temp3x3_2);										/* last rotation: point camera's Z up */
	MatMul_3x3and3x3(temp3x3_1, temp3x3_2, gCameraParam.R);

	MatConcat_3x3_3x1(gCameraParam.R, gCameraParam.t, temp3x4);
	MatMul_3x3and3x4(gCameraParam.K, temp3x4, gCameraParam.P);

	/* Discard z component */
	temp3x3_1[0][0] = gCameraParam.P[0][0];
	temp3x3_1[0][1] = gCameraParam.P[0][1];
	temp3x3_1[0][2] = gCameraParam.P[0][3];
	temp3x3_1[1][0] = gCameraParam.P[1][0];
	temp3x3_1[1][1] = gCameraParam.P[1][1];
	temp3x3_1[1][2] = gCameraParam.P[1][3];
	temp3x3_1[2][0] = gCameraParam.P[2][0];
	temp3x3_1[2][1] = gCameraParam.P[2][1];
	temp3x3_1[2][2] = gCameraParam.P[2][3];

	MatInv3x3(temp3x3_1, gCameraParam.H);

}
