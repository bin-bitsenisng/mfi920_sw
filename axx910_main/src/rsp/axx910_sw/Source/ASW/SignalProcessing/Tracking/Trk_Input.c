/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Trk_Main.h"
#include "Trk_Input.h"

#if !TRK_SIMULATION_MODE
#include "Obj_Main.h"
#endif

#ifdef LINUX
#include "can_sig.h"
#include "inference.h"
#endif

/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
static void Trk_vMeasInit(void);
static void Trk_vMeasProc(TrkEgoMotionInfo_t *TrkEgoMotionInfo, RadarInst_t *Radar_param, int16_t Meas_Cnt);

#if EGO_MOTION_INPUT
static void Trk_vEgoMotionProc(void);
#endif

#if TRK_VISION_OBJECT_INPUT
static void Trk_vVisionProc(void);
#endif


/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Trk_vInputInit()
{
	Trk_vMeasInit();
}


void Trk_vInputProc(void)
{
#if EGO_MOTION_INPUT
	Trk_vEgoMotionProc();
#endif
	Trk_vMeasProc(&gTrkEgoMotionInfo, &gRadarInstInfo, gObjOutCnt);

#if TRK_VISION_OBJECT_INPUT
	Trk_vVisionProc();
#endif
}

/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
static void Trk_vMeasInit(void)
{
	int16_t i_meas;

	for (i_meas = 0; i_meas < TRK_NUM_MEAS_MAX; i_meas++)
	{
		gMeasData[i_meas].s16ObjNum				= -1;

		gMeasData[i_meas].f32Range3d_rdr		= 0.0f;
		gMeasData[i_meas].f32Range_rdr			= 0.0f;
		gMeasData[i_meas].f32RangeRate3d_rdr	= 0.0f;
		gMeasData[i_meas].f32RangeRate_rdr		= 0.0f;
		gMeasData[i_meas].f32RangeRate_comp		= 0.0f;

		gMeasData[i_meas].f32AziAng_rdr 		= 0.0f;
		gMeasData[i_meas].f32AziAng				= 0.0f;
		gMeasData[i_meas].f32EleAng_rdr			= 0.0f;
		gMeasData[i_meas].f32EleAng				= 0.0f;

		gMeasData[i_meas].f32PosX				= 0.0f;
		gMeasData[i_meas].f32PosY				= 0.0f;
		gMeasData[i_meas].f32PosZ				= 0.0f;
		
		gMeasData[i_meas].MovState 				= STATIONARY;
		gMeasData[i_meas].f32Pow_dB 			= 0.0f;

		gMeasData[i_meas].Cluster_PtsStat		= NOISE_PTS;
		gMeasData[i_meas].s16Cluster_idx 		= -1;
		gMeasData[i_meas].u8Cluster_visited     = 0;

		gMeasData[i_meas].nUpMeas 				= -1;
	}	
}


static void Trk_vEgoMotionProc(void)
{
#if EGO_MOTION_INPUT

	int16_t i, j;
	float32_t Wheelspd_Average			= 0.0f;
	float32_t Stationary_Spd			= 0.0f;
	float32_t temp_obj_vel_v			= 0.0f;
	float32_t obj_vel_x_sum				= 0.0f;
	float32_t stat_obj_cnt				= 0.0f;
	float32_t YawRate_APFG				= 0.0f;
	float32_t SteerAngle_Alpha			= 0.0f;	
	float32_t temp_radius_inv			= 0.0f;

	float32_t f32VehSpeed_Revision		= 0.0f;
	float32_t f32YawRate_Revision		= 0.0f;
	float32_t f32WheelAngle				= 0.0f;
	float32_t f32PathRadius_Estimation	= 30000.0f;

	TrkEgoMotionInfo_t *TrkEgoMotionInfo;

	TrkEgoMotionInfo = &gTrkEgoMotionInfo;

	/* Revision, Estimation EgoMotion Data */
	Wheelspd_Average = (TRK_KPH2MPS * (can_sig_data.wheel_speed_fl + can_sig_data.wheel_speed_fr + can_sig_data.wheel_speed_rl + can_sig_data.wheel_speed_rr)) / 4.0f;

	for (i = 0; i < SP_NUM_OBJECT_MAX; i++)
	{
		if (_sp_abs(gObjectOut[i].f32EleAng_deg) <= TRK_EGO_STATIONARY_ELEV_DEG)
		{
			temp_obj_vel_v = gObjectOut[i].f32Velocity_mps * _sp_cosdf(_sp_abs(gObjectOut[i].f32AziAng_deg) - _sp_abs(gRadarInstInfo.f32AziAng)) * _sp_cosdf(_sp_abs(gObjectOut[i].f32EleAng_deg));
		}
		else
		{
			/**/
		}

		if (_sp_abs(Wheelspd_Average + temp_obj_vel_v) < TRK_EGO_SPDCAN_SPDREV_DIFF)
		{
			obj_vel_x_sum += temp_obj_vel_v;
			stat_obj_cnt++;
		}
		else
		{
			/**/
		}
	}

	if (stat_obj_cnt >= TRK_EGO_SPDCAN_SPDREV_DIFF_CNT)
	{
		Stationary_Spd		 = _sp_max(-(obj_vel_x_sum / stat_obj_cnt), 0.0f);
		f32VehSpeed_Revision = (Wheelspd_Average + Stationary_Spd) / 2;
	}
	else
	{
		f32VehSpeed_Revision = Wheelspd_Average;
	}

	if (TrkEgoMotionInfo->init_flag != 0)
	{
		f32VehSpeed_Revision = TRK_EGO_VEHSPEED_ALPHAFILTER_GAIN * f32VehSpeed_Revision + (1.0f - TRK_EGO_VEHSPEED_ALPHAFILTER_GAIN) * TrkEgoMotionInfo->prev_VehSpeed;

		YawRate_APFG 		 = _sp_expf(f32VehSpeed_Revision * TRK_EGO_YAWRATE_EXP_GAIN);
		f32YawRate_Revision  = YawRate_APFG * (can_sig_data.yawrate + TRK_EGO_YAWRATE_BIAS) + (1.0f - YawRate_APFG) * TrkEgoMotionInfo->prev_YawRate;

		SteerAngle_Alpha 	 = (TRK_EGO_STEERANGLE_ALPHAFILTER_GAIN * can_sig_data.steerangle) + (1.0f - TRK_EGO_STEERANGLE_ALPHAFILTER_GAIN) * TrkEgoMotionInfo->prev_SteerAngle;
		f32WheelAngle		 = SteerAngle_Alpha / TRK_EGO_GENESIS_STEERINGRATIO;
	}
	else
	{
		f32VehSpeed_Revision = Wheelspd_Average;
		f32YawRate_Revision  = can_sig_data.yawrate + TRK_EGO_YAWRATE_BIAS;
		SteerAngle_Alpha 	 = can_sig_data.steerangle;
	}
	
	TrkEgoMotionInfo->prev_VehSpeed	= f32VehSpeed_Revision;
	TrkEgoMotionInfo->prev_YawRate	= f32YawRate_Revision;
	TrkEgoMotionInfo->prev_SteerAngle = SteerAngle_Alpha;

	if (f32VehSpeed_Revision <= TRK_EGO_PATHRADIUS_VEHSPEED)
	{		
		f32PathRadius_Estimation = _sp_bound(_sp_roundf(TRK_EGO_GENESIS_WHEELBASE / _sp_sindf(f32WheelAngle)), -TRK_EGO_PATHRADIUS_MINMAX, TRK_EGO_PATHRADIUS_MINMAX);
	}
	else
	{
		if (f32VehSpeed_Revision < TRK_EGO_RADIUS_BY_YAW_VEL_MIN)
		{
			temp_radius_inv = 0.0f;
		}
		else
		{
			temp_radius_inv = (f32YawRate_Revision / 180.0f * TRK_PI) / f32VehSpeed_Revision;
		}

		if (TrkEgoMotionInfo->init_flag != 0 )
		{
			temp_radius_inv = (TRK_EGO_RADIUS_FILTER_GAIN / f32PathRadius_Estimation) + ((1.0f - TRK_EGO_RADIUS_FILTER_GAIN) * temp_radius_inv);
		}
		else
		{
			/**/
		}

		f32PathRadius_Estimation = _sp_bound(_sp_roundf(1.0f / temp_radius_inv), -TRK_EGO_PATHRADIUS_MINMAX, TRK_EGO_PATHRADIUS_MINMAX);

		if (_sp_abs(f32PathRadius_Estimation) < TRK_EGO_ABS_PATHRADIUS_DEG)
		{
			f32PathRadius_Estimation = _sp_sign(f32PathRadius_Estimation) * 10.0f;
		}
		else
		{
			/**/
		}
	} 

	TrkEgoMotionInfo->init_flag = 1;

	gTrkEgoMotionInfo.f32VehSpeed_can	= can_sig_data.vehicle_speed * TRK_KPH2MPS;
	gTrkEgoMotionInfo.f32VehSpeed_comp	= f32VehSpeed_Revision;

	gTrkEgoMotionInfo.f32YawRate_can	= can_sig_data.yawrate;
	gTrkEgoMotionInfo.f32YawRate_comp	= f32YawRate_Revision;

	gTrkEgoMotionInfo.f32SteerAng_deg	= can_sig_data.steerangle;
	gTrkEgoMotionInfo.f32WheelAng_deg	= f32WheelAngle;
	gTrkEgoMotionInfo.f32PathRadius		= f32PathRadius_Estimation;
	gTrkEgoMotionInfo.f32DeltaYaw_deg	= gTrkEgoMotionInfo.f32YawRate_comp * gTrkCycleTime;
	
	gTrkEgoMotionInfo.f32VelX 			= gTrkEgoMotionInfo.f32VehSpeed_comp * _sp_cosdf(gTrkEgoMotionInfo.f32DeltaYaw_deg);
	gTrkEgoMotionInfo.f32VelY 			= gTrkEgoMotionInfo.f32VehSpeed_comp * _sp_sindf(gTrkEgoMotionInfo.f32DeltaYaw_deg);
#else
	gTrkEgoMotionInfo.f32VehSpeed_mps	= 0.0f;
	gTrkEgoMotionInfo.f32YawRate_degps	= 0.0f;
	gTrkEgoMotionInfo.f32SteerAng_deg	= 0.0f;
	gTrkEgoMotionInfo.f32DeltaYaw_deg	= 0.0f;
	gTrkEgoMotionInfo.f32VelX 			= 0.0f;
	gTrkEgoMotionInfo.f32VelY 			= 0.0f;
#endif

}


static void Trk_vMeasProc(TrkEgoMotionInfo_t *TrkEgoMotionInfo, RadarInst_t *RadarInstallInfo, int16_t Meas_Cnt)
{
	int16_t i, j;
	float32_t range2d;
	float32_t rangerate2d;
	float32_t az_deg, el_deg;
	float32_t cos_el;
	float32_t angleDiff, rangeDiff, minDist;

	float32_t fEleAngRad;
	float32_t fPosZ;

	gMeasCnt = 0;

	for (i = 0; i < Meas_Cnt; i++)
	{
		if ((gObjectOut[i].f32Range_m > TRK_MIN_MEAS_RANGE)
#if !TRK_HIGH_RESOLUTION_INPUT
			&& (gObjectOut[i].s16TrackFlag == 1)
#endif
			)
		{

			fEleAngRad = _sp_sinf(_trk_deg2rad(gObjectOut[gMeasCnt].f32EleAng_deg + RadarInstallInfo->f32EleAng));
			fPosZ = gObjectOut[i].f32Range_m * fEleAngRad + RadarInstallInfo->f32PosZ;

			if (_sp_abs(fPosZ) > TRK_MEAS_POSZ_MAX)
			{
				gMeasData[gMeasCnt].nUpMeas = 1;
			}
			else
			{
				gMeasData[gMeasCnt].nUpMeas = 0;
			}
			
			gMeasData[gMeasCnt].u8ModType = gObjectOut[i].eModType;

			gMeasData[gMeasCnt].f32AziAng_rdr = gObjectOut[i].f32AziAng_deg;
			gMeasData[gMeasCnt].f32AziAng = (RadarInstallInfo->f32Reverse * gMeasData[gMeasCnt].f32AziAng_rdr) + RadarInstallInfo->f32AziAng;

				
#if MEAS_ELEVATION_INPUT
			gMeasData[gMeasCnt].f32EleAng_rdr 		= (gMeasData[gMeasCnt].u8ModType != RM_MOD) ? gObjectOut[i].f32EleAng_deg : 0.0f;
#else
			gMeasData[gMeasCnt].f32EleAng_rdr 		= 0;
#endif
			gMeasData[gMeasCnt].f32EleAng 			= gMeasData[gMeasCnt].f32EleAng_rdr + RadarInstallInfo->f32EleAng;
			cos_el 									= _sp_cosf(_trk_deg2rad(gMeasData[gMeasCnt].f32EleAng));

			gMeasData[gMeasCnt].f32Range3d_rdr 		= gObjectOut[i].f32Range_m;
			gMeasData[gMeasCnt].f32Range_rdr 		= gMeasData[gMeasCnt].f32Range3d_rdr * cos_el;
			
			gMeasData[gMeasCnt].f32RangeRate3d_rdr 	= gObjectOut[i].f32Velocity_mps;
			gMeasData[gMeasCnt].f32RangeRate_rdr 	= gMeasData[gMeasCnt].f32RangeRate3d_rdr / (cos_el + TRK_APPROXIMATE_ZERO);
			gMeasData[gMeasCnt].f32RangeRate_comp 	= gMeasData[gMeasCnt].f32RangeRate_rdr + NegRotateX(TrkEgoMotionInfo->f32VelX, TrkEgoMotionInfo->f32VelY, gMeasData[gMeasCnt].f32AziAng);

			gMeasData[gMeasCnt].f32PosX 			= (gMeasData[gMeasCnt].f32Range_rdr * _sp_cosf(_trk_deg2rad(gMeasData[gMeasCnt].f32AziAng))) + RadarInstallInfo->f32PosX;
			gMeasData[gMeasCnt].f32PosY 			= (gMeasData[gMeasCnt].f32Range_rdr * _sp_sinf(_trk_deg2rad(gMeasData[gMeasCnt].f32AziAng))) + RadarInstallInfo->f32PosY;
			gMeasData[gMeasCnt].f32PosZ 			= (gMeasData[gMeasCnt].f32Range3d_rdr * _sp_sinf(_trk_deg2rad(gMeasData[gMeasCnt].f32EleAng))) + RadarInstallInfo->f32PosZ;
			
			gMeasData[gMeasCnt].f32Pow_dB 			= (float32_t)gObjectOut[i].f32Power_dB;

			if (_sp_abs(gMeasData[gMeasCnt].f32RangeRate_comp) < TRK_MEAS_STATIONARY_MAX_RANGE_RATE)
			{
				gMeasData[gMeasCnt].MovState = STATIONARY;
			}
			else
			{
				if (gMeasData[gMeasCnt].f32RangeRate_comp > 0.0f)
				{
					gMeasData[gMeasCnt].MovState = PRECEDING;
				}
				else
				{
					gMeasData[gMeasCnt].MovState = ONCOMING;
				}
			}
			
			gMeasData[gMeasCnt].ReflectTypeProb = 0.0f;
			if (_sp_abs(gMeasData[gMeasCnt].f32RangeRate_comp) < TRK_MEAS_STATIONARY_MAX_RANGE_RATE)
			{
				gMeasData[gMeasCnt].ReflectType = REFLECT_TYPE_STATIONARY;
			}
			else
			{
				gMeasData[gMeasCnt].ReflectType = REFLECT_TYPE_UNKNOWN;
			}

			gMeasData[gMeasCnt].s16ObjNum 			= i;
			gMeasData[gMeasCnt].Cluster_PtsStat		= NOISE_PTS;
			gMeasData[gMeasCnt].s16Cluster_idx 		= -1;
			gMeasData[gMeasCnt].u8Cluster_visited	= 0;

			gMeasData[gMeasCnt].rb_flag = 0;

			gMeasCnt++;
		}
	}
}


#if TRK_VISION_OBJECT_INPUT
static void Trk_vVisionProc(void)
{
	int16_t i_obj;
	float32_t pos_img[3];
	float32_t *bbox_corner_wld;


	/* Feed data to internal data structure */
	gVisionObjCnt = ai_object[0].Ai_num_of_class;
	for (i_obj = 0; i_obj < gVisionObjCnt; i_obj++)
	{
		gVisionObj[i_obj].obj_id = i_obj;
		gVisionObj[i_obj].bbox_img.x = ai_object[i_obj].Ai_x_location;
		gVisionObj[i_obj].bbox_img.y = ai_object[i_obj].Ai_y_location;
		gVisionObj[i_obj].bbox_img.w = ai_object[i_obj].Ai_width;
		gVisionObj[i_obj].bbox_img.h = ai_object[i_obj].Ai_height;
		gVisionObj[i_obj].class_id = ai_object[i_obj].Ai_class_id;
		gVisionObj[i_obj].confidence = ai_object[i_obj].Ai_confidence;

		gVisionObj[i_obj].fusion_state = SF_VISION_ONLY;

		gVisionObj[i_obj].match_radar_obj_idx = -1;

		gVisionObj[i_obj].MatchMeasClstIdx = -1;
		gVisionObj[i_obj].AzimuthOverlapRatio = 0.0;
	}

	/* Vision object coordinate transformation */
	for (i_obj = 0; i_obj < gVisionObjCnt; i_obj++)
	{
		/* Left bottom of the image bounding box */
		pos_img[0] = gVisionObj[i_obj].bbox_img.x;
		pos_img[1] = gVisionObj[i_obj].bbox_img.y + gVisionObj[i_obj].bbox_img.h - 1;
		pos_img[2] = 1;	/* augmented */

		/* Image to world coordinate transformation assuming z = 0 */
		bbox_corner_wld = gVisionObj[i_obj].bbox_corner_wld[0];
		img2wld(pos_img, bbox_corner_wld, gCameraParam.H);

		/* right bottom of the image bounding box */
		pos_img[0] = gVisionObj[i_obj].bbox_img.x + gVisionObj[i_obj].bbox_img.w - 1;
		pos_img[1] = gVisionObj[i_obj].bbox_img.y + gVisionObj[i_obj].bbox_img.h - 1;
		pos_img[2] = 1;	/* augmented */

		/* Image to world coordinate transformation assuming z = 0 */
		bbox_corner_wld = gVisionObj[i_obj].bbox_corner_wld[1];
		img2wld(pos_img, bbox_corner_wld, gCameraParam.H);
	}

}
#endif
