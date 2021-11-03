/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Trk_Main.h"
#include "Trk_Managing.h"
#include "Trk_Correction.h"
#include "Trk_SensorFusion.h"

/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
static void Clst_vCalcStateKalmanGain(ClstData_t *Cluster, KalmanParam_t *Kalman_param);
static void Clst_vKalmanStateUpdate(ClstData_t *Cluster, KalmanParam_t *Kalman_param);
static void Clst_vUpdateMoveState(ClstData_t *Cluster);
static void Clst_vUpdateProperties(ClstData_t *Cluster);

static void Trk_vEstimateTrkSize(TrackData_t *Trk, TrkEgoMotionInfo_t *EgoInfo, RadarInst_t *Radar_param);
static void Trk_vEstimateTrkHeading(TrackData_t *Trk);
static void Trk_vUpdateTrkPower(void);
static void Trk_vUpdateTrkPosZ(void);

/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Clst_vCorrection(void)
{
	int16_t i_clst;

	for (i_clst = 0; i_clst < TRK_NUM_CLUSTER_MAX; i_clst++)
	{
		if (gClstData[i_clst].Status != INVALID)
		{
			/* Update UpdState and KalmanData */
			if (gClstData[i_clst].u16AliveAge == 1)
			{
				gClstData[i_clst].f32UpdStateX[0] = gClstData[i_clst].f32PredStateX[0];
				gClstData[i_clst].f32UpdStateX[1] = gClstData[i_clst].f32PredStateX[1];
				gClstData[i_clst].f32UpdStateY[0] = gClstData[i_clst].f32PredStateY[0];
				gClstData[i_clst].f32UpdStateY[1] = gClstData[i_clst].f32PredStateY[1];
			}
			else
			{
				Clst_vCalcStateKalmanGain(&gClstData[i_clst], &KalmanParam);
				Clst_vKalmanStateUpdate(&gClstData[i_clst], &KalmanParam);
				Clst_vUpdateMoveState(&gClstData[i_clst]);
				Clst_vUpdateProperties(&gClstData[i_clst]);
			}
		}
	}

}


void Trk_vCorrection(void)
{
	int16_t i_trk;
	int16_t i_clst;
	int16_t i_meas;
	int16_t i_meas2;
	int16_t i_corner;

	int16_t weight_sum;
	int16_t clst_idx;
	int16_t meas_idx;
	int16_t meas_idx2;

	float32_t temp_PosX;
	float32_t temp_PosY;
	float32_t temp_VelX;
	float32_t temp_VelY;
	float32_t prev_VelX;
	float32_t prev_VelY;
	float32_t prev_speed;

	for (i_trk = 0; i_trk < TRK_NUM_TRACK_MAX; i_trk++)
	{
		if (gTrackData[i_trk].Status != INVALID)
		{
			if ((gTrackData[i_trk].u16AliveAge == 1) || (gTrackData[i_trk].fusion_state == SF_VISION_ONLY))
			{
				gTrackData[i_trk].MeasState = gTrackData[i_trk].PredState;
				gTrackData[i_trk].UpdState = gTrackData[i_trk].PredState;
			}
			else
			{
				weight_sum = 0;
				if (gTrackData[i_trk].Status == UPDATED_TRACK)
				{
					/* Calculate Measurement BoundingBox */
					for (i_clst = 0; i_clst < gTrackData[i_trk].s16GroupClstCnt; i_clst++)
					{
						clst_idx = gTrackData[i_trk].s16GroupClstIdx[i_clst];

						if ((gClstData[clst_idx].Status == UPDATED_TRACK) ||
							((gClstData[clst_idx].Status == COASTED_TRACK) && (gClstData[clst_idx].u16StatusAge <= TRK_UPDATE_COASTED_TRKLET_STAGEAGE_MAX)))
						{
							temp_PosX = NegRotateX(gClstData[clst_idx].f32UpdStateX[0], gClstData[clst_idx].f32UpdStateY[0], gTrackData[i_trk].PredState.f32StateHeading[0]);
							temp_PosY = NegRotateY(gClstData[clst_idx].f32UpdStateX[0], gClstData[clst_idx].f32UpdStateY[0], gTrackData[i_trk].PredState.f32StateHeading[0]);

							gTrackData[i_trk].MeasState.f32BoundingBoxX[0] = _sp_max(temp_PosX, gTrackData[i_trk].MeasState.f32BoundingBoxX[0]);
							gTrackData[i_trk].MeasState.f32BoundingBoxX[1] = gTrackData[i_trk].MeasState.f32BoundingBoxX[0];
							gTrackData[i_trk].MeasState.f32BoundingBoxX[2] = _sp_min(temp_PosX, gTrackData[i_trk].MeasState.f32BoundingBoxX[2]);
							gTrackData[i_trk].MeasState.f32BoundingBoxX[3] = gTrackData[i_trk].MeasState.f32BoundingBoxX[2];

							gTrackData[i_trk].MeasState.f32BoundingBoxY[0] = _sp_max(temp_PosY, gTrackData[i_trk].MeasState.f32BoundingBoxY[0]);
							gTrackData[i_trk].MeasState.f32BoundingBoxY[1] = _sp_min(temp_PosY, gTrackData[i_trk].MeasState.f32BoundingBoxY[1]);
							gTrackData[i_trk].MeasState.f32BoundingBoxY[2] = gTrackData[i_trk].MeasState.f32BoundingBoxY[1];
							gTrackData[i_trk].MeasState.f32BoundingBoxY[3] = gTrackData[i_trk].MeasState.f32BoundingBoxY[0];

							gTrackData[i_trk].MeasState.f32StateX[1] += (gClstData[clst_idx].u16StatusAge * TRK_UPDATE_TRKLET_VELOCITY_WEIGHT) * gClstData[clst_idx].f32UpdStateX[1];
							gTrackData[i_trk].MeasState.f32StateY[1] += (gClstData[clst_idx].u16StatusAge * TRK_UPDATE_TRKLET_VELOCITY_WEIGHT) * gClstData[clst_idx].f32UpdStateY[1];

							weight_sum += (int16_t)(gClstData[clst_idx].u16StatusAge * TRK_UPDATE_TRKLET_VELOCITY_WEIGHT);

							for (i_meas = 0; i_meas < gClstData[clst_idx].s16AssoMeasClstCnt; i_meas++)
							{
								meas_idx = gClstData[clst_idx].s16AssoMeasClstIdx[i_meas];

								for (i_meas2 = 0; i_meas2 < gMeasClst[meas_idx].MeasNum; i_meas2++)
								{
									meas_idx2 = gMeasClst[meas_idx].MeasIdx[i_meas2];

									temp_PosX = NegRotateX(gMeasData[meas_idx2].f32PosX, gMeasData[meas_idx2].f32PosY, gTrackData[i_trk].PredState.f32StateHeading[0]);
									temp_PosY = NegRotateY(gMeasData[meas_idx2].f32PosX, gMeasData[meas_idx2].f32PosY, gTrackData[i_trk].PredState.f32StateHeading[0]);

									gTrackData[i_trk].MeasState.f32BoundingBoxX[0] = _sp_max(temp_PosX, gTrackData[i_trk].MeasState.f32BoundingBoxX[0]);
									gTrackData[i_trk].MeasState.f32BoundingBoxX[1] = gTrackData[i_trk].MeasState.f32BoundingBoxX[0];
									gTrackData[i_trk].MeasState.f32BoundingBoxX[2] = _sp_min(temp_PosX, gTrackData[i_trk].MeasState.f32BoundingBoxX[2]);
									gTrackData[i_trk].MeasState.f32BoundingBoxX[3] = gTrackData[i_trk].MeasState.f32BoundingBoxX[2];

									gTrackData[i_trk].MeasState.f32BoundingBoxY[0] = _sp_max(temp_PosY, gTrackData[i_trk].MeasState.f32BoundingBoxY[0]);
									gTrackData[i_trk].MeasState.f32BoundingBoxY[1] = _sp_min(temp_PosY, gTrackData[i_trk].MeasState.f32BoundingBoxY[1]);
									gTrackData[i_trk].MeasState.f32BoundingBoxY[2] = gTrackData[i_trk].MeasState.f32BoundingBoxY[1];
									gTrackData[i_trk].MeasState.f32BoundingBoxY[3] = gTrackData[i_trk].MeasState.f32BoundingBoxY[0];
								}
							}

							for (i_meas = 0; i_meas < gClstData[clst_idx].s16AssoMeasNoisePtCnt; i_meas++)
							{
								meas_idx = gClstData[clst_idx].s16AssoMeasNoisePtIdx[i_meas];

								temp_PosX = NegRotateX(gMeasData[meas_idx].f32PosX, gMeasData[meas_idx].f32PosY, gTrackData[i_trk].PredState.f32StateHeading[0]);
								temp_PosY = NegRotateY(gMeasData[meas_idx].f32PosX, gMeasData[meas_idx].f32PosY, gTrackData[i_trk].PredState.f32StateHeading[0]);

								gTrackData[i_trk].MeasState.f32BoundingBoxX[0] = _sp_max(temp_PosX, gTrackData[i_trk].MeasState.f32BoundingBoxX[0]);
								gTrackData[i_trk].MeasState.f32BoundingBoxX[1] = gTrackData[i_trk].MeasState.f32BoundingBoxX[0];
								gTrackData[i_trk].MeasState.f32BoundingBoxX[2] = _sp_min(temp_PosX, gTrackData[i_trk].MeasState.f32BoundingBoxX[2]);
								gTrackData[i_trk].MeasState.f32BoundingBoxX[3] = gTrackData[i_trk].MeasState.f32BoundingBoxX[2];

								gTrackData[i_trk].MeasState.f32BoundingBoxY[0] = _sp_max(temp_PosY, gTrackData[i_trk].MeasState.f32BoundingBoxY[0]);
								gTrackData[i_trk].MeasState.f32BoundingBoxY[1] = _sp_min(temp_PosY, gTrackData[i_trk].MeasState.f32BoundingBoxY[1]);
								gTrackData[i_trk].MeasState.f32BoundingBoxY[2] = gTrackData[i_trk].MeasState.f32BoundingBoxY[1];
								gTrackData[i_trk].MeasState.f32BoundingBoxY[3] = gTrackData[i_trk].MeasState.f32BoundingBoxY[0];
							}
						}
					}

					gTrackData[i_trk].MeasState.f32Length = gTrackData[i_trk].MeasState.f32BoundingBoxX[0] - gTrackData[i_trk].MeasState.f32BoundingBoxX[2];
					gTrackData[i_trk].MeasState.f32Width  = gTrackData[i_trk].MeasState.f32BoundingBoxY[0] - gTrackData[i_trk].MeasState.f32BoundingBoxY[1];

					for (i_corner = 0; i_corner < 4; i_corner++)
					{
						temp_PosX = gTrackData[i_trk].MeasState.f32BoundingBoxX[i_corner];
						temp_PosY = gTrackData[i_trk].MeasState.f32BoundingBoxY[i_corner];

						gTrackData[i_trk].MeasState.f32BoundingBoxX[i_corner] = RotateX(temp_PosX, temp_PosY, gTrackData[i_trk].PredState.f32StateHeading[0]);
						gTrackData[i_trk].MeasState.f32BoundingBoxY[i_corner] = RotateY(temp_PosX, temp_PosY, gTrackData[i_trk].PredState.f32StateHeading[0]);
					}
					gTrackData[i_trk].MeasState.f32StateX[0] = (gTrackData[i_trk].MeasState.f32BoundingBoxX[0] + gTrackData[i_trk].MeasState.f32BoundingBoxX[2]) * 0.5f;
					gTrackData[i_trk].MeasState.f32StateY[0] = (gTrackData[i_trk].MeasState.f32BoundingBoxY[0] + gTrackData[i_trk].MeasState.f32BoundingBoxY[2]) * 0.5f;

					/* Estimate Reference Point */
					gTrackData[i_trk].RefPt = Trk_vEstimateRefPosition(&gTrackData[i_trk].PredState, gTrackData[i_trk].MovState, gTrackData[i_trk].RefPt);

					switch (gTrackData[i_trk].RefPt)
					{
					case REF_FRONT_LEFT:
						gTrackData[i_trk].PredState.f32Ref_PosX = gTrackData[i_trk].PredState.f32BoundingBoxX[0];
						gTrackData[i_trk].PredState.f32Ref_PosY = gTrackData[i_trk].PredState.f32BoundingBoxY[0];
						gTrackData[i_trk].MeasState.f32Ref_PosX = gTrackData[i_trk].MeasState.f32BoundingBoxX[0];
						gTrackData[i_trk].MeasState.f32Ref_PosY = gTrackData[i_trk].MeasState.f32BoundingBoxY[0];
						break;
					case REF_FRONT:
						gTrackData[i_trk].PredState.f32Ref_PosX = (gTrackData[i_trk].PredState.f32BoundingBoxX[0] + gTrackData[i_trk].PredState.f32BoundingBoxX[1]) * 0.5f;
						gTrackData[i_trk].PredState.f32Ref_PosY = (gTrackData[i_trk].PredState.f32BoundingBoxY[0] + gTrackData[i_trk].PredState.f32BoundingBoxY[1]) * 0.5f;
						gTrackData[i_trk].MeasState.f32Ref_PosX = (gTrackData[i_trk].MeasState.f32BoundingBoxX[0] + gTrackData[i_trk].MeasState.f32BoundingBoxX[1]) * 0.5f;
						gTrackData[i_trk].MeasState.f32Ref_PosY = (gTrackData[i_trk].MeasState.f32BoundingBoxY[0] + gTrackData[i_trk].MeasState.f32BoundingBoxY[1]) * 0.5f;
						break;
					case REF_FRONT_RIGHT:
						gTrackData[i_trk].PredState.f32Ref_PosX = gTrackData[i_trk].PredState.f32BoundingBoxX[1];
						gTrackData[i_trk].PredState.f32Ref_PosY = gTrackData[i_trk].PredState.f32BoundingBoxY[1];
						gTrackData[i_trk].MeasState.f32Ref_PosX = gTrackData[i_trk].MeasState.f32BoundingBoxX[1];
						gTrackData[i_trk].MeasState.f32Ref_PosY = gTrackData[i_trk].MeasState.f32BoundingBoxY[1];
						break;
					case REF_RIGHT:
						gTrackData[i_trk].PredState.f32Ref_PosX = (gTrackData[i_trk].PredState.f32BoundingBoxX[1] + gTrackData[i_trk].PredState.f32BoundingBoxX[2]) * 0.5f;
						gTrackData[i_trk].PredState.f32Ref_PosY = (gTrackData[i_trk].PredState.f32BoundingBoxY[1] + gTrackData[i_trk].PredState.f32BoundingBoxY[2]) * 0.5f;
						gTrackData[i_trk].MeasState.f32Ref_PosX = (gTrackData[i_trk].MeasState.f32BoundingBoxX[1] + gTrackData[i_trk].MeasState.f32BoundingBoxX[2]) * 0.5f;
						gTrackData[i_trk].MeasState.f32Ref_PosY = (gTrackData[i_trk].MeasState.f32BoundingBoxY[1] + gTrackData[i_trk].MeasState.f32BoundingBoxY[2]) * 0.5f;
						break;
					case REF_REAR_RIGHT:
						gTrackData[i_trk].PredState.f32Ref_PosX = gTrackData[i_trk].PredState.f32BoundingBoxX[2];
						gTrackData[i_trk].PredState.f32Ref_PosY = gTrackData[i_trk].PredState.f32BoundingBoxY[2];
						gTrackData[i_trk].MeasState.f32Ref_PosX = gTrackData[i_trk].MeasState.f32BoundingBoxX[2];
						gTrackData[i_trk].MeasState.f32Ref_PosY = gTrackData[i_trk].MeasState.f32BoundingBoxY[2];
						break;
					case REF_REAR:
						gTrackData[i_trk].PredState.f32Ref_PosX = (gTrackData[i_trk].PredState.f32BoundingBoxX[2] + gTrackData[i_trk].PredState.f32BoundingBoxX[3]) * 0.5f;
						gTrackData[i_trk].PredState.f32Ref_PosY = (gTrackData[i_trk].PredState.f32BoundingBoxY[2] + gTrackData[i_trk].PredState.f32BoundingBoxY[3]) * 0.5f;
						gTrackData[i_trk].MeasState.f32Ref_PosX = (gTrackData[i_trk].MeasState.f32BoundingBoxX[2] + gTrackData[i_trk].MeasState.f32BoundingBoxX[3]) * 0.5f;
						gTrackData[i_trk].MeasState.f32Ref_PosY = (gTrackData[i_trk].MeasState.f32BoundingBoxY[2] + gTrackData[i_trk].MeasState.f32BoundingBoxY[3]) * 0.5f;
						break;
					case REF_REAR_LEFT:
						gTrackData[i_trk].PredState.f32Ref_PosX = gTrackData[i_trk].PredState.f32BoundingBoxX[3];
						gTrackData[i_trk].PredState.f32Ref_PosY = gTrackData[i_trk].PredState.f32BoundingBoxY[3];
						gTrackData[i_trk].MeasState.f32Ref_PosX = gTrackData[i_trk].MeasState.f32BoundingBoxX[3];
						gTrackData[i_trk].MeasState.f32Ref_PosY = gTrackData[i_trk].MeasState.f32BoundingBoxY[3];
						break;
					case REF_LEFT:
						gTrackData[i_trk].PredState.f32Ref_PosX = (gTrackData[i_trk].PredState.f32BoundingBoxX[3] + gTrackData[i_trk].PredState.f32BoundingBoxX[0]) * 0.5f;
						gTrackData[i_trk].PredState.f32Ref_PosY = (gTrackData[i_trk].PredState.f32BoundingBoxY[3] + gTrackData[i_trk].PredState.f32BoundingBoxY[0]) * 0.5f;
						gTrackData[i_trk].MeasState.f32Ref_PosX = (gTrackData[i_trk].MeasState.f32BoundingBoxX[3] + gTrackData[i_trk].MeasState.f32BoundingBoxX[0]) * 0.5f;
						gTrackData[i_trk].MeasState.f32Ref_PosY = (gTrackData[i_trk].MeasState.f32BoundingBoxY[3] + gTrackData[i_trk].MeasState.f32BoundingBoxY[0]) * 0.5f;
						break;
					case REF_CENTER:
						gTrackData[i_trk].PredState.f32Ref_PosX = (gTrackData[i_trk].PredState.f32BoundingBoxX[0] + gTrackData[i_trk].PredState.f32BoundingBoxX[2]) * 0.5f;
						gTrackData[i_trk].PredState.f32Ref_PosY = (gTrackData[i_trk].PredState.f32BoundingBoxY[0] + gTrackData[i_trk].PredState.f32BoundingBoxY[2]) * 0.5f;
						gTrackData[i_trk].MeasState.f32Ref_PosX = (gTrackData[i_trk].MeasState.f32BoundingBoxX[0] + gTrackData[i_trk].MeasState.f32BoundingBoxX[2]) * 0.5f;
						gTrackData[i_trk].MeasState.f32Ref_PosY = (gTrackData[i_trk].MeasState.f32BoundingBoxY[0] + gTrackData[i_trk].MeasState.f32BoundingBoxY[2]) * 0.5f;
						break;
					case REF_INVALID:
					default:
						gTrackData[i_trk].PredState.f32Ref_PosX = 0.0f;
						gTrackData[i_trk].PredState.f32Ref_PosY = 0.0f;
						gTrackData[i_trk].MeasState.f32Ref_PosX = 0.0f;
						gTrackData[i_trk].MeasState.f32Ref_PosY = 0.0f;
						break;
					}

					if (weight_sum != 0)
					{
						gTrackData[i_trk].MeasState.f32StateX[1] /= weight_sum;
						gTrackData[i_trk].MeasState.f32StateY[1] /= weight_sum;
					}

					gTrackData[i_trk].MeasState.f32StateSpeed[0] = _sp_hypotf(gTrackData[i_trk].MeasState.f32StateX[1], gTrackData[i_trk].MeasState.f32StateY[1]);
				}
				else
				{
					gTrackData[i_trk].MeasState = gTrackData[i_trk].PredState;
					gTrackData[i_trk].UpdState = gTrackData[i_trk].PredState;
				}


				if (gTrackData[i_trk].RefPt != REF_INVALID)
				{
					/* Update States */
					if (weight_sum != 0)
					{
						gTrackData[i_trk].UpdState.f32Ref_PosX = TRK_UPDATE_POS_GAIN * gTrackData[i_trk].MeasState.f32Ref_PosX + (1.0f - TRK_UPDATE_POS_GAIN) * gTrackData[i_trk].PredState.f32Ref_PosX;
						gTrackData[i_trk].UpdState.f32Ref_PosY = TRK_UPDATE_POS_GAIN * gTrackData[i_trk].MeasState.f32Ref_PosY + (1.0f - TRK_UPDATE_POS_GAIN) * gTrackData[i_trk].PredState.f32Ref_PosY;
					}
					else
					{
						gTrackData[i_trk].UpdState.f32Ref_PosX = gTrackData[i_trk].PredState.f32Ref_PosX;
						gTrackData[i_trk].UpdState.f32Ref_PosY = gTrackData[i_trk].PredState.f32Ref_PosY;
					}

					prev_VelX = gTrackData[i_trk].UpdState.f32StateX[1];
					prev_VelY = gTrackData[i_trk].UpdState.f32StateY[1];

					gTrackData[i_trk].UpdState.f32StateX[1] = TRK_UPDATE_VEL_GAIN * gTrackData[i_trk].MeasState.f32StateX[1] + (1.0f - TRK_UPDATE_VEL_GAIN) * gTrackData[i_trk].PredState.f32StateX[1];
					gTrackData[i_trk].UpdState.f32StateY[1] = TRK_UPDATE_VEL_GAIN * gTrackData[i_trk].MeasState.f32StateY[1] + (1.0f - TRK_UPDATE_VEL_GAIN) * gTrackData[i_trk].PredState.f32StateY[1];

					gTrackData[i_trk].f32AccX += TRK_ACC_FILTER_GAIN * (((gTrackData[i_trk].UpdState.f32StateX[1] - prev_VelX) / gTrkCycleTime) - gTrackData[i_trk].f32AccX);
					gTrackData[i_trk].f32AccY += TRK_ACC_FILTER_GAIN * (((gTrackData[i_trk].UpdState.f32StateY[1] - prev_VelY) / gTrkCycleTime) - gTrackData[i_trk].f32AccY);

					gTrackData[i_trk].UpdState.f32StateSpeed[0] = TRK_UPDATE_SPEED_GAIN * gTrackData[i_trk].MeasState.f32StateSpeed[0] + (1.0f - TRK_UPDATE_SPEED_GAIN) * gTrackData[i_trk].PredState.f32StateSpeed[0];

					if ((gTrackData[i_trk].MovState == PRECEDING) || 
						(gTrackData[i_trk].MovState == ONCOMING))
					{
						prev_speed = gTrackData[i_trk].UpdState.f32StateSpeed[0];
						gTrackData[i_trk].UpdState.f32StateSpeed[1] = TRK_UPDATE_SPEEDRATE_GAIN * ((prev_speed - gTrackData[i_trk].MeasState.f32StateSpeed[0]) / gTrkCycleTime) + (1.0f - TRK_UPDATE_SPEEDRATE_GAIN) * gTrackData[i_trk].PredState.f32StateSpeed[1];
					}
					else
					{
						gTrackData[i_trk].UpdState.f32StateSpeed[1] = 0.0f;
					}

					/* Update MovState */
					if (gTrackData[i_trk].UpdState.f32StateSpeed[0] > TRK_STATIONARY_MAX_SPEED)
					{
						if (gTrackData[i_trk].MovState == STATIONARY)
						{
							gTrackData[i_trk].PredState.f32Length = TRK_INIT_LENGTH_MOVING;
							gTrackData[i_trk].PredState.f32Width = TRK_INIT_WIDTH_MOVING;
							gTrackData[i_trk].UpdState.f32Length = TRK_INIT_LENGTH_MOVING;
							gTrackData[i_trk].UpdState.f32Width = TRK_INIT_WIDTH_MOVING;
						}

						if(_sp_abs(gTrackData[i_trk].PredState.f32StateHeading[0]) < 90.0f)
						{
							gTrackData[i_trk].MovState = PRECEDING;
						}
						else
						{
							gTrackData[i_trk].MovState = ONCOMING;
						}
					}
					else
					{
						if ((gTrackData[i_trk].MovState == PRECEDING) || 
							(gTrackData[i_trk].MovState == ONCOMING))
						{
							gTrackData[i_trk].MovState = STOPPED;
							gTrackData[i_trk].UpdState.f32StateSpeed[1] = 0.0f;
						}
					}

					/* Update Size */
					Trk_vEstimateTrkSize(&gTrackData[i_trk], &gTrkEgoMotionInfo, &gRadarInstInfo);

					/* Update Heading */
					Trk_vEstimateTrkHeading(&gTrackData[i_trk]);

					/* Update Position Info */
					Trk_vUpdatePosFromRefPt(&gTrackData[i_trk].UpdState, gTrackData[i_trk].RefPt);
				}
				else
				{
					for (i_clst = 0; i_clst < gTrackData[i_trk].s16GroupClstCnt; i_clst++)
					{
						gClstData[gTrackData[i_trk].s16GroupClstIdx[i_clst]].s16GroupTrkIdx = -1;
					}

					Trk_vInit(&gTrackData[i_trk]);
				}
			}

			/* Sensor fusion - Azimuth correction by referring vision object */
			Trk_vSensorFusionAzimuthCorrection(&gTrackData[i_trk]);

			/* Redefine Size based on classification info */
			if (gTrackData[i_trk].obj_class == OBJCLASS_PEDESTRIAN)
			{
				gTrackData[i_trk].UpdState.f32Length = TRK_INIT_LENGTH_PEDESTRIAN;
				gTrackData[i_trk].UpdState.f32Width = TRK_INIT_WIDTH_PEDESTRIAN;
			}
		}
	}

}


RefPosition_t Trk_vEstimateRefPosition(TrkState_t *PredState, MovState_t Moving_Status, RefPosition_t prev_RefPt)
{
	RefPosition_t RefPt = prev_RefPt;

	float32_t temp_PosX;
	float32_t temp_PosY;
	float32_t sen_PosX;
	float32_t sen_PosY;
	float32_t temp_az;
	float32_t temp_az_2;
	float32_t temp_range;
	float32_t temp_range_2;

	if (Moving_Status == STATIONARY)
	{
		RefPt = REF_CENTER;
	}
	else
	{
		temp_PosX = NegRotateX(PredState->f32StateX[0], PredState->f32StateY[0], PredState->f32StateHeading[0]);
		temp_PosY = NegRotateY(PredState->f32StateX[0], PredState->f32StateY[0], PredState->f32StateHeading[0]);

		sen_PosX = NegRotateX(gRadarInstInfo.f32PosX, gRadarInstInfo.f32PosY, PredState->f32StateHeading[0]);
		sen_PosY = NegRotateY(gRadarInstInfo.f32PosX, gRadarInstInfo.f32PosY, PredState->f32StateHeading[0]);

		if (temp_PosY > sen_PosY)
		{
			temp_az = _sp_atan2df(PredState->f32BoundingBoxY[0] - gRadarInstInfo.f32PosY, PredState->f32BoundingBoxX[0] - gRadarInstInfo.f32PosX);
			temp_az_2 = _sp_atan2df(PredState->f32BoundingBoxY[3] - gRadarInstInfo.f32PosY, PredState->f32BoundingBoxX[3] - gRadarInstInfo.f32PosX);

			temp_range = _sp_hypotf(PredState->f32BoundingBoxX[0] - gRadarInstInfo.f32PosX, PredState->f32BoundingBoxY[0] - gRadarInstInfo.f32PosY);
			temp_range_2 = _sp_hypotf(PredState->f32BoundingBoxX[3] - gRadarInstInfo.f32PosX, PredState->f32BoundingBoxY[3] - gRadarInstInfo.f32PosY);
		}
		else
		{
			temp_az = _sp_atan2df(PredState->f32BoundingBoxY[1] - gRadarInstInfo.f32PosY, PredState->f32BoundingBoxX[1] - gRadarInstInfo.f32PosX);
			temp_az_2 = _sp_atan2df(PredState->f32BoundingBoxY[2] - gRadarInstInfo.f32PosY, PredState->f32BoundingBoxX[2] - gRadarInstInfo.f32PosX);

			temp_range = _sp_hypotf(PredState->f32BoundingBoxX[1] - gRadarInstInfo.f32PosX, PredState->f32BoundingBoxY[1] - gRadarInstInfo.f32PosY);
			temp_range_2 = _sp_hypotf(PredState->f32BoundingBoxX[2] - gRadarInstInfo.f32PosX, PredState->f32BoundingBoxY[2] - gRadarInstInfo.f32PosY);
		}

		if ((temp_PosY + (PredState->f32Width * 0.5f)) < (sen_PosY - TRK_REF_ABIGUIOS_THRESHOLD))
		{
			/* Left */
			if (((_sp_abs(temp_az) < (TRK_REF_ESTIMATION_SENSOR_FOV_MAX)) && (temp_range > TRK_REF_SELECTED_RANGE_MIN)) &&
				((_sp_abs(temp_az_2) < (TRK_REF_ESTIMATION_SENSOR_FOV_MAX)) && (temp_range_2 > TRK_REF_SELECTED_RANGE_MIN)))
			{
				if ((temp_PosX + (PredState->f32Length * 0.5f)) < (sen_PosX - TRK_REF_ABIGUIOS_THRESHOLD))
				{
					RefPt = REF_FRONT_LEFT;
				}
				else if ((temp_PosX - (PredState->f32Length * 0.5f)) > (sen_PosX + TRK_REF_ABIGUIOS_THRESHOLD))
				{
					RefPt = REF_REAR_LEFT;
				}
				else
				{
					RefPt = REF_LEFT;
				}
			}
			else if ((_sp_abs(temp_az) < (TRK_REF_ESTIMATION_SENSOR_FOV_MAX)) && (temp_range > TRK_REF_SELECTED_RANGE_MIN))
			{
				RefPt = REF_FRONT_LEFT;
			}
			else if ((_sp_abs(temp_az_2) < (TRK_REF_ESTIMATION_SENSOR_FOV_MAX)) && (temp_range_2 > TRK_REF_SELECTED_RANGE_MIN))
			{
				RefPt = REF_REAR_LEFT;
			}
			else
			{
				/* Do nothing */
			}
		}
		else if ((temp_PosY - (PredState->f32Width * 0.5f)) > (sen_PosY + TRK_REF_ABIGUIOS_THRESHOLD))
		{
			/* Right */
			if (((_sp_abs(temp_az) < (TRK_REF_ESTIMATION_SENSOR_FOV_MAX)) && (temp_range > TRK_REF_SELECTED_RANGE_MIN)) &&
				((_sp_abs(temp_az_2) < (TRK_REF_ESTIMATION_SENSOR_FOV_MAX)) && (temp_range_2 > TRK_REF_SELECTED_RANGE_MIN)))
			{
				if ((temp_PosX + (PredState->f32Length * 0.5f)) < (sen_PosX - TRK_REF_ABIGUIOS_THRESHOLD))
				{
					RefPt = REF_FRONT_RIGHT;
				}
				else if ((temp_PosX - (PredState->f32Length * 0.5f)) > (sen_PosX + TRK_REF_ABIGUIOS_THRESHOLD))
				{
					RefPt = REF_REAR_RIGHT;
				}
				else
				{
					RefPt = REF_RIGHT;
				}
			}
			else if ((_sp_abs(temp_az) < (TRK_REF_ESTIMATION_SENSOR_FOV_MAX)) && (temp_range > TRK_REF_SELECTED_RANGE_MIN))
			{
				RefPt = REF_FRONT_RIGHT;
			}
			else if ((_sp_abs(temp_az_2) < (TRK_REF_ESTIMATION_SENSOR_FOV_MAX)) && (temp_range_2 > TRK_REF_SELECTED_RANGE_MIN))
			{
				RefPt = REF_REAR_RIGHT;
			}
			else
			{
				/* Do nothing */
			}
		}
		else
		{
			/* Front or Rear face */
			if ((temp_PosX + (PredState->f32Length * 0.5f)) < (sen_PosX - TRK_REF_ABIGUIOS_THRESHOLD) && (temp_range > TRK_REF_SELECTED_RANGE_MIN))
			{
				RefPt = REF_FRONT;
			}
			else
			{
				RefPt = REF_REAR;
			}
		}
	}

	return RefPt;

}


void Trk_vUpdatePosFromRefPt(TrkState_t *TrkState, RefPosition_t Ref_Pt)
{
	int16_t i_corner;
	float32_t temp_X;
	float32_t temp_Y;
	float32_t temp_X_2;
	float32_t temp_Y_2;
	float32_t temp_X_3;
	float32_t temp_Y_3;

	/* Update BoundingBox */
	temp_X = NegRotateX(TrkState->f32Ref_PosX, TrkState->f32Ref_PosY, TrkState->f32StateHeading[0]);
	temp_Y = NegRotateY(TrkState->f32Ref_PosX, TrkState->f32Ref_PosY, TrkState->f32StateHeading[0]);

	switch (Ref_Pt)
	{
	case REF_FRONT_LEFT:
		temp_X_2 = temp_X - (TrkState->f32Length * 0.5f);
		temp_Y_2 = temp_Y - (TrkState->f32Width * 0.5f);
		break;
	case REF_FRONT:
		temp_X_2 = temp_X - (TrkState->f32Length * 0.5f);
		temp_Y_2 = temp_Y;
		break;
	case REF_FRONT_RIGHT:
		temp_X_2 = temp_X - (TrkState->f32Length * 0.5f);
		temp_Y_2 = temp_Y + (TrkState->f32Width * 0.5f);
		break;
	case REF_RIGHT:
		temp_X_2 = temp_X;
		temp_Y_2 = temp_Y + (TrkState->f32Width * 0.5f);
		break;
	case REF_REAR_RIGHT:
		temp_X_2 = temp_X + (TrkState->f32Length * 0.5f);
		temp_Y_2 = temp_Y + (TrkState->f32Width * 0.5f);
		break;
	case REF_REAR:
		temp_X_2 = temp_X + (TrkState->f32Length * 0.5f);
		temp_Y_2 = temp_Y;
		break;
	case REF_REAR_LEFT:
		temp_X_2 = temp_X + (TrkState->f32Length * 0.5f);
		temp_Y_2 = temp_Y - (TrkState->f32Width * 0.5f);
		break;
	case REF_LEFT:
		temp_X_2 = temp_X;
		temp_Y_2 = temp_Y - (TrkState->f32Width * 0.5f);
		break;
	case REF_CENTER:
		temp_X_2 = temp_X;
		temp_Y_2 = temp_Y;
		break;
	case REF_INVALID:
	default:
		temp_X_2 = 0.0f;
		temp_Y_2 = 0.0f;
		break;
	}

	TrkState->f32StateX[0] = RotateX(temp_X_2, temp_Y_2, TrkState->f32StateHeading[0]);
	TrkState->f32StateY[0] = RotateY(temp_X_2, temp_Y_2, TrkState->f32StateHeading[0]);

	for (i_corner = 0; i_corner < 4; i_corner++)
	{
		switch (i_corner)
		{
		case 0:
			temp_X_3 = temp_X_2 + (TrkState->f32Length * 0.5f);
			temp_Y_3 = temp_Y_2 + (TrkState->f32Width * 0.5f);
			break;
		case 1:
			temp_X_3 = temp_X_2 + (TrkState->f32Length * 0.5f);
			temp_Y_3 = temp_Y_2 - (TrkState->f32Width * 0.5f);
			break;
		case 2:
			temp_X_3 = temp_X_2 - (TrkState->f32Length * 0.5f);
			temp_Y_3 = temp_Y_2 - (TrkState->f32Width * 0.5f);
			break;
		case 3:
			temp_X_3 = temp_X_2 - (TrkState->f32Length * 0.5f);
			temp_Y_3 = temp_Y_2 + (TrkState->f32Width * 0.5f);
			break;
		default:
			break;
		}

		TrkState->f32BoundingBoxX[i_corner] = RotateX(temp_X_3, temp_Y_3, TrkState->f32StateHeading[0]);
		TrkState->f32BoundingBoxY[i_corner] = RotateY(temp_X_3, temp_Y_3, TrkState->f32StateHeading[0]);
	}

}


void Trk_vAdditions(void)
{
	Trk_vUpdateTrkPower();
	//Trk_vUpdateTrkPosZ();
}

/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
static void Clst_vCalcStateKalmanGain(ClstData_t *Cluster, KalmanParam_t *Kalman_param)
{
	float32_t Sx[2][2];
	float32_t Sy[2][2];

	float32_t Trklet_Range;
	float32_t Trklet_Az;

	float32_t error_pos_rdr;
	float32_t error_pos_orth;
	float32_t error_rangerate;
	float32_t error_azrate;

	float32_t temp_Mat[2][2];
	float32_t temp_Mat_2[2][2];
	float32_t temp_Mat_3[2][2];
	float32_t temp_Mat_4[2][2];

	Trklet_Range = _sp_hypotf(Cluster->f32UpdStateX[0] - gRadarInstInfo.f32PosX, Cluster->f32UpdStateY[0] - gRadarInstInfo.f32PosY);
	Trklet_Az = _sp_atan2df(Cluster->f32UpdStateY[0] - gRadarInstInfo.f32PosY, Cluster->f32UpdStateX[0] - gRadarInstInfo.f32PosX);

	error_pos_rdr = TRKLET_SIGMA_R_RANGE;
	error_pos_orth = Trklet_Range * _sp_tandf(TRKLET_SIGMA_R_AZIMUTH);
	error_rangerate = TRKLET_SIGMA_R_RANGERATE;
	error_azrate = _sp_bound(TRKLET_SIGMA_R_AZRATE * _sp_pow2(_sp_hypotf(Cluster->f32UpdStateX[1], Cluster->f32UpdStateY[1])), TRKLET_SIGMA_R_AZRATE_MIN, TRKLET_SIGMA_R_AZRATE_MAX);

	Cluster->Kalman.Rx[0][0] = _sp_abs(RotateX(error_pos_rdr, error_pos_orth, Trklet_Az));
	Cluster->Kalman.Rx[0][1] = 0.0f;
	Cluster->Kalman.Rx[1][0] = 0.0f;
	Cluster->Kalman.Rx[1][1] = _sp_abs(RotateX(error_rangerate, 0.0f, Trklet_Az));

	Cluster->Kalman.Ry[0][0] = _sp_abs(RotateY(error_pos_rdr, error_pos_orth, Trklet_Az));
	Cluster->Kalman.Ry[0][1] = 0.0f;
	Cluster->Kalman.Ry[1][0] = 0.0f;
	Cluster->Kalman.Ry[1][1] = _sp_abs(RotateY(error_rangerate, Trklet_Range * (error_azrate * SP_DEG2RAD), Trklet_Az));

	MatMul_2x2and2x2(Kalman_param->H, Cluster->Kalman.Px, temp_Mat);
	MatMul_2x2and2x2(temp_Mat, Kalman_param->H_Trs, temp_Mat_2);
	MatAdd_2x2(temp_Mat_2, Cluster->Kalman.Rx, Sx);
	MatMul_2x2and2x2(Cluster->Kalman.Px, Kalman_param->H_Trs, temp_Mat_3);
	MatInverse_2x2(Sx, temp_Mat_4);
	MatMul_2x2and2x2(temp_Mat_3, temp_Mat_4, Cluster->Kalman.Kx);

	MatMul_2x2and2x2(Kalman_param->H, Cluster->Kalman.Py, temp_Mat);
	MatMul_2x2and2x2(temp_Mat, Kalman_param->H_Trs, temp_Mat_2);
	MatAdd_2x2(temp_Mat_2, Cluster->Kalman.Ry, Sy);
	MatMul_2x2and2x2(Cluster->Kalman.Py, Kalman_param->H_Trs, temp_Mat_3);
	MatInverse_2x2(Sy, temp_Mat_4);
	MatMul_2x2and2x2(temp_Mat_3, temp_Mat_4, Cluster->Kalman.Ky);

}


static void Clst_vKalmanStateUpdate(ClstData_t *Cluster, KalmanParam_t *Kalman_param)
{
	int16_t i_clst;
	int16_t i_meas;
	
	float32_t ave_Range = 0.0f;
	float32_t ave_Az = 0.0f;
	float32_t ave_Rangerate = 0.0f;
	float32_t ave_PosX = 0.0f;
	float32_t ave_PosY = 0.0f;
	float32_t ave_Pow = 0.0f;
	
	int16_t num_msmt;
	int16_t num_msmt_vel;

	float32_t MeasTypeRatio;

	float32_t meas_AzVel;
	float32_t meas_X[2];
	float32_t meas_Y[2];
	float32_t res[2];
	float32_t temp_Mat[2];
	float32_t temp_Mat_2[2][2];
	float32_t temp_Mat_3[2][2];
	float32_t temp_Mat_4[2][2];

	float32_t prev_VelX;
	float32_t prev_VelY;

	/* Update Azimuth Info */
	if ((Cluster->s16AssoMeasClstCnt == 0) && (Cluster->s16AssoMeasNoisePtCnt == 0))
	{
		meas_X[0] = Cluster->f32PredStateX[0];
		meas_X[1] = Cluster->f32PredStateX[1];
		meas_Y[0] = Cluster->f32PredStateY[0];
		meas_Y[1] = Cluster->f32PredStateY[1];
	}
	else
	{
		num_msmt = 0;
		num_msmt_vel = 0;

		for (i_clst = 0; i_clst < Cluster->s16AssoMeasClstCnt; i_clst++)
		{
			ave_Range	  += (gMeasClst[Cluster->s16AssoMeasClstIdx[i_clst]].Range.f32Mean * (float32_t)gMeasClst[Cluster->s16AssoMeasClstIdx[i_clst]].MeasNum);
			ave_Az		  += (gMeasClst[Cluster->s16AssoMeasClstIdx[i_clst]].AziAng.f32Mean * (float32_t)gMeasClst[Cluster->s16AssoMeasClstIdx[i_clst]].MeasNum);
			if (gMeasClst[Cluster->s16AssoMeasClstIdx[i_clst]].ReflectType != REFLECT_TYPE_WHEEL)
			{
				ave_Rangerate += (gMeasClst[Cluster->s16AssoMeasClstIdx[i_clst]].RangeRate.f32Mean * (float32_t)gMeasClst[Cluster->s16AssoMeasClstIdx[i_clst]].MeasNum);
				num_msmt_vel += gMeasClst[Cluster->s16AssoMeasClstIdx[i_clst]].MeasNum;
			}
			ave_PosX	  += (gMeasClst[Cluster->s16AssoMeasClstIdx[i_clst]].Xpos.f32Mean * (float32_t)gMeasClst[Cluster->s16AssoMeasClstIdx[i_clst]].MeasNum);
			ave_PosY	  += (gMeasClst[Cluster->s16AssoMeasClstIdx[i_clst]].Ypos.f32Mean * (float32_t)gMeasClst[Cluster->s16AssoMeasClstIdx[i_clst]].MeasNum);
			ave_Pow		  += (gMeasClst[Cluster->s16AssoMeasClstIdx[i_clst]].Power.f32Mean * (float32_t)gMeasClst[Cluster->s16AssoMeasClstIdx[i_clst]].MeasNum);

			num_msmt += gMeasClst[Cluster->s16AssoMeasClstIdx[i_clst]].MeasNum;
		}

		for (i_meas = 0; i_meas < Cluster->s16AssoMeasNoisePtCnt; i_meas++)
		{
			ave_Range	  += gMeasData[Cluster->s16AssoMeasNoisePtIdx[i_meas]].f32Range_rdr;
			ave_Az		  += gMeasData[Cluster->s16AssoMeasNoisePtIdx[i_meas]].f32AziAng;
			if (gMeasData[Cluster->s16AssoMeasNoisePtIdx[i_meas]].ReflectType != REFLECT_TYPE_WHEEL)
			{
				ave_Rangerate += gMeasData[Cluster->s16AssoMeasNoisePtIdx[i_meas]].f32RangeRate_comp;
				num_msmt_vel++;
			}
			ave_PosX	  += gMeasData[Cluster->s16AssoMeasNoisePtIdx[i_meas]].f32PosX;
			ave_PosY	  += gMeasData[Cluster->s16AssoMeasNoisePtIdx[i_meas]].f32PosY;
			ave_Pow		  += gMeasData[Cluster->s16AssoMeasNoisePtIdx[i_meas]].f32Pow_dB;

			num_msmt++;
		}

		Cluster->f32Mean_Range = ave_Range / (float32_t)num_msmt;
		Cluster->f32Mean_Azimuth = ave_Az / (float32_t)num_msmt;
		Cluster->f32Mean_RangeRate = (num_msmt_vel > 0) ? ave_Rangerate / (float32_t)num_msmt_vel : 0.0f;
		Cluster->f32Mean_Xpos = ave_PosX / (float32_t)num_msmt;
		Cluster->f32Mean_Ypos = ave_PosY / (float32_t)num_msmt;
		Cluster->f32Mean_Pow_dB = ave_Pow / (float32_t)num_msmt;

		/* Update StateX, StateY */
		meas_AzVel = NegRotateY(Cluster->f32PredStateX[1], Cluster->f32PredStateY[1], Cluster->f32Mean_Azimuth);

		meas_X[0] = Cluster->f32Mean_Xpos;
		meas_Y[0] = Cluster->f32Mean_Ypos;

		if (num_msmt_vel > 0)
		{
			meas_X[1] = RotateX(Cluster->f32Mean_RangeRate, meas_AzVel, Cluster->f32Mean_Azimuth);
			meas_Y[1] = RotateY(Cluster->f32Mean_RangeRate, meas_AzVel, Cluster->f32Mean_Azimuth);
		}
		else
		{
			meas_X[1] = Cluster->f32PredStateX[1];
			meas_Y[1] = Cluster->f32PredStateY[1];
		}
	}

	prev_VelX = Cluster->f32UpdStateX[1];
	prev_VelY = Cluster->f32UpdStateY[1];
	
	MatSub_2x1(meas_X, Cluster->f32PredStateX, res);
	MatMul_2x2and2x1(Cluster->Kalman.Kx, res, temp_Mat);
	MatAdd_2x1(Cluster->f32PredStateX, temp_Mat, Cluster->f32UpdStateX);
	MatMul_2x2and2x2(Cluster->Kalman.Kx, Kalman_param->H, temp_Mat_2);
	MatSub_2x2(Kalman_param->I, temp_Mat_2, temp_Mat_3);
	MatMul_2x2and2x2(temp_Mat_3, Cluster->Kalman.Px, temp_Mat_4);
	MatCopy_2x2(temp_Mat_4, Cluster->Kalman.Px);

	MatSub_2x1(meas_Y, Cluster->f32PredStateY, res);
	MatMul_2x2and2x1(Cluster->Kalman.Ky, res, temp_Mat);
	MatAdd_2x1(Cluster->f32PredStateY, temp_Mat, Cluster->f32UpdStateY);
	MatMul_2x2and2x2(Cluster->Kalman.Ky, Kalman_param->H, temp_Mat_2);
	MatSub_2x2(Kalman_param->I, temp_Mat_2, temp_Mat_3);
	MatMul_2x2and2x2(temp_Mat_3, Cluster->Kalman.Py, temp_Mat_4);
	MatCopy_2x2(temp_Mat_4, Cluster->Kalman.Py);

	Cluster->f32AccelX += TRKLET_ACC_FILTER_GAIN * (((Cluster->f32UpdStateX[1] - prev_VelX) / gTrkCycleTime) - Cluster->f32AccelX);
	Cluster->f32AccelY += TRKLET_ACC_FILTER_GAIN * (((Cluster->f32UpdStateY[1] - prev_VelY) / gTrkCycleTime) - Cluster->f32AccelY);

}


static void Clst_vUpdateMoveState(ClstData_t *Cluster)
{
	int16_t i_cnt;

	if ((Cluster->MovState == STATIONARY) ||
		(Cluster->MovState == STOPPED))
	{
		if (_sp_hypotf(Cluster->f32UpdStateX[1], Cluster->f32UpdStateY[1]) > TRKLET_MOVESTATE_TRANSIT_SPEED)
		{
			Cluster->s16MoveStateCnt++;

			if (Cluster->s16MoveStateCnt >= TRKLET_MOVESTATE_TRANSIT_CNT_THRE)
			{
				if (Cluster->f32UpdStateX[1] > 0.0f)
				{
					Cluster->MovState = PRECEDING;
				}
				else
				{
					Cluster->MovState = ONCOMING;
				}
					
				Cluster->s16MoveStateCnt = 0;
			}
		}
		else
		{
			Cluster->s16MoveStateCnt = 0;
		}
	}
	else
	{
		if (_sp_hypotf(Cluster->f32UpdStateX[1], Cluster->f32UpdStateY[1]) < TRKLET_MOVESTATE_TRANSIT_SPEED)
		{
			Cluster->s16MoveStateCnt++;

			if (Cluster->s16MoveStateCnt >= TRKLET_MOVESTATE_TRANSIT_CNT_THRE)
			{
				Cluster->MovState = STOPPED;
				Cluster->s16MoveStateCnt = 0;
			}
		}
		else
		{
			Cluster->s16MoveStateCnt = 0;
		}
	}

}


static void Clst_vUpdateProperties(ClstData_t *Cluster)
{
	int16_t i_cnt;
	int16_t i_clst_idx;
	int16_t i_meas;
	int16_t i_meas_idx;
	int16_t i_noise_idx;
	int16_t meas_cnt;
	int16_t meas_vel_cnt;

	float32_t sum_range;
	float32_t sum_az;
	float32_t sum_rangerate;
	float32_t sum_xpos;
	float32_t sum_ypos;
	float32_t sum_pow;

	float32_t mean_range;
	float32_t mean_az;
	float32_t mean_rangerate;
	float32_t mean_xpos;
	float32_t mean_ypos;
	float32_t mean_pow;

	float32_t difpowsum_range;
	float32_t difpowsum_az;
	float32_t difpowsum_rangerate;
	float32_t difpowsum_xpos;
	float32_t difpowsum_ypos;
	float32_t difpowsum_pow;

	float32_t std_range;
	float32_t std_az;
	float32_t std_rangerate;
	float32_t std_xpos;
	float32_t std_ypos;
	float32_t std_pow;

	float32_t max_pow;

	meas_cnt = 0;
	meas_vel_cnt = 0;

	sum_range = 0;
	sum_az = 0;
	sum_rangerate = 0;
	sum_xpos = 0;
	sum_ypos = 0;
	sum_pow = 0;

	max_pow = Cluster->f32MaxPow_dB;

	if (Cluster->s16AssoMeasClstCnt > 0)
	{
		for (i_cnt = 0; i_cnt < Cluster->s16AssoMeasClstCnt; i_cnt++)
		{
			i_clst_idx = Cluster->s16AssoMeasClstIdx[i_cnt];

			for (i_meas = 0; i_meas < gMeasClst[i_clst_idx].MeasNum; i_meas++)
			{
				i_meas_idx = gMeasClst[i_clst_idx].MeasIdx[i_meas];

				sum_range += gMeasData[i_meas_idx].f32Range_rdr;
				sum_az += gMeasData[i_meas_idx].f32AziAng;
				if (gMeasClst[i_clst_idx].ReflectType != REFLECT_TYPE_WHEEL)
				{
					sum_rangerate += gMeasData[i_meas_idx].f32RangeRate_comp;
					meas_vel_cnt++;
				}
				sum_xpos += gMeasData[i_meas_idx].f32PosX;
				sum_ypos += gMeasData[i_meas_idx].f32PosY;
				sum_pow += gMeasData[i_meas_idx].f32Pow_dB;
				max_pow = _trk_max(gMeasData[i_meas_idx].f32Pow_dB, max_pow);

				meas_cnt++;
			}
		}

		for (i_cnt = 0; i_cnt < Cluster->s16AssoMeasNoisePtCnt; i_cnt++)
		{
			i_noise_idx		= Cluster->s16AssoMeasNoisePtIdx[i_cnt];

			sum_range		+= gMeasData[i_noise_idx].f32Range_rdr;
			sum_az			+= gMeasData[i_noise_idx].f32AziAng;
			if (gMeasData[i_noise_idx].ReflectType != REFLECT_TYPE_WHEEL)
			{
				sum_rangerate += gMeasData[i_noise_idx].f32RangeRate_comp;
				meas_vel_cnt++;
			}
			sum_xpos		+= gMeasData[i_noise_idx].f32PosX;
			sum_ypos		+= gMeasData[i_noise_idx].f32PosY;
			sum_pow			+= gMeasData[i_noise_idx].f32Pow_dB;
			max_pow			= _trk_max(gMeasData[i_noise_idx].f32Pow_dB, max_pow);

			meas_cnt++;
		}

		mean_range		= sum_range		/ meas_cnt;
		mean_az			= sum_az		/ meas_cnt;
		mean_rangerate	= (meas_vel_cnt > 0) ? sum_rangerate / meas_cnt : 0.0f;
		mean_xpos		= sum_xpos		/ meas_cnt;
		mean_ypos		= sum_ypos		/ meas_cnt;
		mean_pow		= sum_pow		/ meas_cnt;

		difpowsum_range = 0;
		difpowsum_az = 0;
		difpowsum_rangerate = 0;
		difpowsum_xpos = 0;
		difpowsum_ypos = 0;
		difpowsum_pow = 0;

		for (i_cnt = 0; i_cnt < Cluster->s16AssoMeasClstCnt; i_cnt++)
		{
			i_clst_idx = Cluster->s16AssoMeasClstIdx[i_cnt];

			for (i_meas = 0; i_meas < gMeasClst[i_clst_idx].MeasNum; i_meas++)
			{
				i_meas_idx			= gMeasClst[i_clst_idx].MeasIdx[i_meas];

				difpowsum_range		+= _trk_pow2(gMeasData[i_meas_idx].f32Range_rdr		 - mean_range);
				difpowsum_az		+= _trk_pow2(gMeasData[i_meas_idx].f32AziAng		 - mean_az);
				if (gMeasClst[i_clst_idx].ReflectType != REFLECT_TYPE_WHEEL)
				{
					difpowsum_rangerate += _trk_pow2(gMeasData[i_meas_idx].f32RangeRate_comp - mean_rangerate);
				}
				difpowsum_xpos		+= _trk_pow2(gMeasData[i_meas_idx].f32PosX			 - mean_xpos);
				difpowsum_ypos		+= _trk_pow2(gMeasData[i_meas_idx].f32PosY			 - mean_ypos);
				difpowsum_pow		+= _trk_pow2(gMeasData[i_meas_idx].f32Pow_dB		 - mean_pow);
			}
		}

		for (i_cnt = 0; i_cnt < Cluster->s16AssoMeasNoisePtCnt; i_cnt++)
		{
			i_noise_idx = Cluster->s16AssoMeasNoisePtIdx[i_cnt];
			
			difpowsum_range		+= _trk_pow2(gMeasData[i_noise_idx].f32Range_rdr	  - mean_range);
			difpowsum_az		+= _trk_pow2(gMeasData[i_noise_idx].f32AziAng		  - mean_az);
			if (gMeasData[i_noise_idx].ReflectType != REFLECT_TYPE_WHEEL)
			{
				difpowsum_rangerate += _trk_pow2(gMeasData[i_noise_idx].f32RangeRate_comp - mean_rangerate);
			}
			difpowsum_xpos		+= _trk_pow2(gMeasData[i_noise_idx].f32PosX			  - mean_xpos);
			difpowsum_ypos		+= _trk_pow2(gMeasData[i_noise_idx].f32PosY			  - mean_ypos);
			difpowsum_pow		+= _trk_pow2(gMeasData[i_noise_idx].f32Pow_dB		  - mean_pow);
		}

		std_range		= _trk_sqrtf(difpowsum_range	 / meas_cnt);
		std_az			= _trk_sqrtf(difpowsum_az		 / meas_cnt);
		std_rangerate	= (meas_vel_cnt > 0) ? _trk_sqrtf(difpowsum_rangerate / meas_cnt) : 0.0f;
		std_xpos		= _trk_sqrtf(difpowsum_xpos		 / meas_cnt);
		std_ypos		= _trk_sqrtf(difpowsum_ypos		 / meas_cnt);
		std_pow			= _trk_sqrtf(difpowsum_pow		 / meas_cnt);

		/* output */
		Cluster->f32Std_Range		+= (CLST_PROP_UPD_RATE * (std_range		- Cluster->f32Std_Range));
		Cluster->f32Std_Azimuth		+= (CLST_PROP_UPD_RATE * (std_az		- Cluster->f32Std_Azimuth));
		Cluster->f32Std_RangeRate	+= (meas_vel_cnt > 0) ? (CLST_PROP_UPD_RATE * (std_rangerate	- Cluster->f32Std_RangeRate)) : 0.0f;
		Cluster->f32Std_Xpos		+= (CLST_PROP_UPD_RATE * (std_xpos		- Cluster->f32Std_Xpos));
		Cluster->f32Std_Ypos		+= (CLST_PROP_UPD_RATE * (std_ypos		- Cluster->f32Std_Ypos));
		Cluster->f32Std_Pow_dB		+= (CLST_PROP_UPD_RATE * (std_pow		- Cluster->f32Std_Pow_dB));
		Cluster->f32MaxPow_dB = max_pow;
	}

}


static void Trk_vEstimateTrkSize(TrackData_t *Trk, TrkEgoMotionInfo_t *EgoInfo, RadarInst_t *Radar_param)
{
	float32_t trk_az;
	float32_t inner_prod;
	float32_t res_l;
	float32_t res_w;	
	float32_t filt_gain_length;
	float32_t filt_gain_width;

	if ((Trk->Status == UPDATED_TRACK) 
		&& ((Trk->MovState != STATIONARY) && (Trk->MovState != STOPPED))
		&& (Trk->obj_class != OBJCLASS_PEDESTRIAN))
	{
		trk_az = _sp_atan2df(Trk->UpdState.f32Ref_PosY - Radar_param->f32PosY, Trk->UpdState.f32Ref_PosX - Radar_param->f32PosX);
		inner_prod = (_sp_cosdf(Trk->PredState.f32StateHeading[0]) * _sp_cosdf(trk_az)) + (_sp_sindf(Trk->PredState.f32StateHeading[0]) * _sp_sindf(trk_az));

		/* Length */
		res_l = Trk->MeasState.f32Length - Trk->PredState.f32Length;

		if ((Trk->u8Merging_Flag == 1) && (Trk->MeasState.f32Length > Trk->PredState.f32Length))
		{
			filt_gain_length = TRK_SIZE_FILTER_GAIN_MERGED;
		}
		else
		{
			filt_gain_length = (Trk->MeasState.f32Length > Trk->PredState.f32Length) ? TRK_SIZE_LENGTH_FILTER_GAIN_FAST : (1.0f - _sp_abs(inner_prod)) * TRK_SIZE_LENGTH_FILTER_GAIN_SLOW;
			res_l = _sp_bound(res_l, -Trk->PredState.f32Length * 0.25f, Trk->PredState.f32Length * 0.25f);
		}
		
		Trk->UpdState.f32Length = Trk->PredState.f32Length + filt_gain_length * res_l;

		/* Width */
		res_w = Trk->MeasState.f32Width - Trk->PredState.f32Width;
		res_w = _sp_bound(res_w, -Trk->PredState.f32Width * 0.25f, Trk->PredState.f32Width * 0.25f);

		filt_gain_width = (Trk->MeasState.f32Width > Trk->PredState.f32Width) ? TRK_SIZE_WIDTH_FILTER_GAIN_FAST : inner_prod * TRK_SIZE_WIDTH_FILTER_GAIN_SLOW;

		Trk->UpdState.f32Width = _sp_bound((Trk->PredState.f32Width + filt_gain_width * res_w),  1.6f, 4.0f);
	}
}


static void Trk_vEstimateTrkHeading(TrackData_t *Trk)
{
	float32_t res;
	float32_t Rh;
	float32_t Sh;

	uint16_t i_clst;
	uint16_t i_mscl;
	uint16_t asso_mscl_cnt;
	float32_t heading_angle;
	

	if ((Trk->MovState == PRECEDING) ||
		(Trk->MovState == ONCOMING))
	{
		if (Trk->Status == UPDATED_TRACK)
		{

			Trk->MeasState.f32StateHeading[0] = _sp_atan2df(Trk->UpdState.f32StateY[1], Trk->UpdState.f32StateX[1]);

#if TRK_HEADING_MSCL_ROTATION_ANGLE_USE_FLAG
			asso_mscl_cnt = 0;
			heading_angle = 0.0f;
			for (i_clst = 0; i_clst < Trk->s16GroupClstCnt; i_clst++)
			{
				for (i_mscl = 0; i_mscl < gClstData[Trk->s16GroupClstIdx[i_clst]].s16AssoMeasClstCnt; i_mscl++)
				{
					asso_mscl_cnt++;
					heading_angle += gMeasClst[i_mscl].RotationAngle;
				}
			}
			if (asso_mscl_cnt > 0)
			{
				Trk->MeasState.f32StateHeading[0] = (1 - TRK_HEADING_MSCL_ROTATION_ANGLE_WEIGHT) * Trk->MeasState.f32StateHeading[0] + (TRK_HEADING_MSCL_ROTATION_ANGLE_WEIGHT)* heading_angle / asso_mscl_cnt;
			}
#endif
		}
		else
		{
			Trk->MeasState.f32StateHeading[0] = Trk->PredState.f32StateHeading[0];
		}

		Trk->MeasState.f32StateHeading[1] = Trk->PredState.f32StateHeading[1];

		res = Trk->MeasState.f32StateHeading[0] - Trk->PredState.f32StateHeading[0];

		while (_sp_abs(res) > 180.0f)
		{
			res -= _sp_sign(res) * 360.0f;
		}

		/* ReInitialize Heading and Ref_Pt */
		if (_sp_abs(res) > TRK_HEADING_REINITIALIZE_ANGLE_DIFF)
		{
			Trk->UpdState.f32StateHeading[0] = Trk->MeasState.f32StateHeading[0];
			Trk->UpdState.f32StateHeading[1] = 0.0f;

			Trk->Ph[0][0] = _sp_pow2(TRK_STD_P_HEADING_INIT);
			Trk->Ph[0][1] = TRK_STD_P_HEADING_INIT * TRK_STD_P_HEADINGRATE_INIT;
			Trk->Ph[1][0] = Trk->Ph[0][1];
			Trk->Ph[1][1] = _sp_pow2(TRK_STD_P_HEADINGRATE_INIT);

			Trk->Kh[0] = 0.0f;
			Trk->Kh[1] = 0.0f;

			Trk_vUpdatePosFromRefPt(&Trk->UpdState, Trk->RefPt);
			Trk->RefPt = Trk_vEstimateRefPosition(&Trk->UpdState, Trk->MovState, Trk->RefPt);
		}
		else
		{
			res = _sp_bound(res, -TRK_HEADING_RESIDUAL_MAX, TRK_HEADING_RESIDUAL_MAX);

			Rh = _sp_pow2(TRK_STD_R_HEADING_MAX * _sp_expf(-Trk->UpdState.f32StateSpeed[0] / TRK_STD_R_HEADING_SPEED_FACTOR));
			Sh = Trk->Ph[0][0] + Rh;

			Trk->Kh[0] = Trk->Ph[0][0] / Sh;
			Trk->Kh[1] = Trk->Ph[1][0] / Sh;

#if TRK_HEADING_FILTERING_METHOD == TRK_HEADING_FILTERING_METHOD_KF
			Trk->UpdState.f32StateHeading[0] = Trk->PredState.f32StateHeading[0] + (Trk->Kh[0] * res);
			Trk->UpdState.f32StateHeading[1] = Trk->PredState.f32StateHeading[1] + (Trk->Kh[1] * res);
#elif TRK_HEADING_FILTERING_METHOD == TRK_HEADING_FILTERING_METHOD_FIXED_GAIN
			Trk->UpdState.f32StateHeading[0] = TRK_HEADING_FILTERING_EST_FIXED_GAIN_VALUE * Trk->PredState.f32StateHeading[0] + (1 - TRK_HEADING_FILTERING_EST_FIXED_GAIN_VALUE) * _trk_bound(Trk->MeasState.f32StateHeading[0], -TRK_HEADING_RESIDUAL_MAX, TRK_HEADING_RESIDUAL_MAX);
			Trk->UpdState.f32StateHeading[1] = TRK_HEADING_FILTERING_EST_FIXED_GAIN_VALUE * Trk->PredState.f32StateHeading[1] + (1 - TRK_HEADING_FILTERING_EST_FIXED_GAIN_VALUE) * _trk_bound(Trk->MeasState.f32StateHeading[1], -TRK_HEADING_RESIDUAL_MAX, TRK_HEADING_RESIDUAL_MAX);
#elif TRK_HEADING_FILTERING_METHOD == TRK_HEADING_FILTERING_METHOD_NO_FILTER
			Trk->UpdState.f32StateHeading[0] = Trk->MeasState.f32StateHeading[0];
			Trk->UpdState.f32StateHeading[1] = Trk->MeasState.f32StateHeading[1];
#endif

			Trk->Ph[0][0] *= (1.0f - Trk->Kh[0]);
			Trk->Ph[1][1] -= Trk->Kh[1] * Trk->Ph[0][1];
			Trk->Ph[0][1] *= (1.0f - Trk->Kh[0]);
			Trk->Ph[1][0] = Trk->Ph[0][1];
		}
	}
	else
	{
#if TRK_SF_STATIONARY_OBJ_HEADING_INIT_METHOD == TRK_SF_STATIONARY_OBJ_HEADING_INIT_LONGITUDINAL
		/* Fix Heading of Stationary track */
		Trk->MeasState.f32StateHeading[0] = Trk->PredState.f32StateHeading[0];

		Trk->UpdState.f32StateHeading[0] = Trk->PredState.f32StateHeading[0];
		Trk->UpdState.f32StateHeading[1] = 0.0f;

		Trk->Ph[0][0] = _sp_pow2(TRK_STD_P_HEADING_INIT);
		Trk->Ph[0][1] = TRK_STD_P_HEADING_INIT * TRK_STD_P_HEADINGRATE_INIT;
		Trk->Ph[1][0] = Trk->Ph[0][1];
		Trk->Ph[1][1] = _sp_pow2(TRK_STD_P_HEADINGRATE_INIT);

		Trk->Kh[0] = 0.0f;
		Trk->Kh[1] = 0.0f;
#elif TRK_SF_STATIONARY_OBJ_HEADING_INIT_METHOD == TRK_SF_STATIONARY_OBJ_HEADING_INIT_MSCL_ROTATION

		asso_mscl_cnt = 0;
		heading_angle = 0.0f;
		for (i_clst = 0; i_clst < Trk->s16GroupClstCnt; i_clst++)
		{
			for (i_mscl = 0; i_mscl < gClstData[Trk->s16GroupClstIdx[i_clst]].s16AssoMeasClstCnt; i_mscl++)
			{
				asso_mscl_cnt++;
				heading_angle += gMeasClst[i_mscl].RotationAngle;
			}
		}

		if (asso_mscl_cnt != 0)
		{
			Trk->MeasState.f32StateHeading[0] = heading_angle / asso_mscl_cnt;
			Trk->MeasState.f32StateHeading[1] = Trk->PredState.f32StateHeading[1];

			Trk->UpdState.f32StateHeading[0] = TRK_SF_STATIONARY_OBJ_HEADING_MSCL_WEIGHT * Trk->MeasState.f32StateHeading[0] + (1 - TRK_SF_STATIONARY_OBJ_HEADING_MSCL_WEIGHT) * Trk->PredState.f32StateHeading[0];
			Trk->UpdState.f32StateHeading[1] = TRK_SF_STATIONARY_OBJ_HEADING_MSCL_WEIGHT * Trk->MeasState.f32StateHeading[1] + (1 - TRK_SF_STATIONARY_OBJ_HEADING_MSCL_WEIGHT) * Trk->PredState.f32StateHeading[1];
		}
		else
		{
			Trk->UpdState.f32StateHeading[0] = Trk->PredState.f32StateHeading[0];
			Trk->UpdState.f32StateHeading[1] = Trk->PredState.f32StateHeading[1];
		}

#elif TRK_SF_STATIONARY_OBJ_HEADING_INIT_METHOD == TRK_SF_STATIONARY_OBJ_HEADING_INIT_EGO_DIRECTION
		Trk->UpdState.f32StateHeading[0] = gTrkEgoMotionInfo.f32YawRate_comp;
		Trk->UpdState.f32StateHeading[1] = Trk->PredState.f32StateHeading[1];
	
#endif
	}

	while (_sp_abs(Trk->UpdState.f32StateHeading[0]) > 180.0f)
	{
		Trk->UpdState.f32StateHeading[0] -= _sp_sign(Trk->UpdState.f32StateHeading[0]) * 360.0f;
	}

}


static void Trk_vUpdateTrkPower(void)
{
	int16_t i_trk;
	int16_t i_clst;
	float32_t tmp_sum;
	float32_t tmp_max;

	for (i_trk = 0; i_trk < TRK_NUM_TRACK_MAX; i_trk++)
	{
		if ((gTrackData[i_trk].Status == UPDATED_TRACK) && (0 < gTrackData[i_trk].s16GroupClstCnt))
		{
			tmp_sum = 0.0f;
			tmp_max = 0.0f;
			for (i_clst = 0; i_clst < gTrackData[i_trk].s16GroupClstCnt; i_clst++)
			{
				tmp_sum += gClstData[gTrackData[i_trk].s16GroupClstIdx[i_clst]].f32Mean_Pow_dB;
				tmp_max = (gClstData[gTrackData[i_trk].s16GroupClstIdx[i_clst]].f32MaxPow_dB > tmp_max) ? gClstData[gTrackData[i_trk].s16GroupClstIdx[i_clst]].f32MaxPow_dB : tmp_max;
			}

			gTrackData[i_trk].f32Pow_dB    = tmp_sum / gTrackData[i_trk].s16GroupClstCnt;
			gTrackData[i_trk].f32MaxPow_dB = tmp_max;			
		}
	}
}




static void Trk_vUpdateTrkPosZ(void)
{

	const float32_t fHeightMin = 1.2f;
	const float32_t fAlpha = 0.6f;

	float32_t fPosTh = 0.5f; // default

	uint8_t nMeasMode;
	uint16_t MeasNumInCluster;
	uint16_t MeasIndInCluster[TRK_CLST_NUM_NEIGHBOR_MAX];
	float32_t f32MeasPosZInCluster[TRK_CLST_NUM_NEIGHBOR_MAX];

	uint16_t tempMeasInd;
	float32_t tempPosZ;

	int16_t nMedianInd;
	float32_t fPosZ;

	float32_t fSum;
	float32_t fMean;
	float32_t fVar;


	for (uint8_t nTrk = 0; nTrk < TRK_NUM_TRACK_MAX; nTrk++)
	{
		nMeasMode = 0;
		MeasNumInCluster = 0;

		// For test check out

		if ((gTrackData[nTrk].Status == UPDATED_TRACK) ||
			(gTrackData[nTrk].Status == NEW_TRACK))
		{
			memset(&MeasIndInCluster[0], 0, sizeof(MeasIndInCluster));
			memset(&f32MeasPosZInCluster[0], 0, sizeof(f32MeasPosZInCluster));

			// Find meas in cluster 
			for (int16_t nCluster = 0; nCluster < gTrackData[nTrk].s16GroupClstCnt; nCluster++)
			{
				int16_t clusterInd = gTrackData[nTrk].s16GroupClstIdx[nCluster];
				int16_t AssoMeasClusterInd;

				for (int n = 0; n < gClstData[clusterInd].s16AssoMeasClstCnt; n++) 
				{
					AssoMeasClusterInd = gClstData[clusterInd].s16AssoMeasClstIdx[n];

					for (uint16_t nMeas = 0; nMeas < gMeasClst[AssoMeasClusterInd].MeasNum; nMeas++)
					{
						uint16_t nMeasInd = gMeasClst[AssoMeasClusterInd].MeasIdx[nMeas];
						MeasIndInCluster[MeasNumInCluster] = nMeasInd;
						f32MeasPosZInCluster[MeasNumInCluster] = gMeasData[nMeasInd].f32PosZ;
						MeasNumInCluster += 1;
					}

					if (TRK_CLST_NUM_NEIGHBOR_MAX == MeasNumInCluster)
					{
						break;
					}
				}
			}

			// Sort Measurements in assending order
			tempPosZ = -1000.0f;

			for (int16_t i = 0; i < MeasNumInCluster - 1; i++)
			{
				for (int16_t j = i + 1; j < MeasNumInCluster; j++)
				{
					if (f32MeasPosZInCluster[i] > f32MeasPosZInCluster[j])
					{
						tempPosZ = f32MeasPosZInCluster[j];
						tempMeasInd = MeasIndInCluster[j];

						f32MeasPosZInCluster[j] = f32MeasPosZInCluster[i];
						f32MeasPosZInCluster[i] = tempPosZ;

						MeasIndInCluster[j] = MeasIndInCluster[i];
						MeasIndInCluster[i] = tempMeasInd;
					}
				}
			}


			fSum = 0.0f;

			for (int16_t i = 0; i < MeasNumInCluster; i++)
			{
				fSum += f32MeasPosZInCluster[i];
			}

			if (MeasNumInCluster > 0)
			{
				fMean = fSum / MeasNumInCluster;
			}

			fVar = 0.0f;

			for (int16_t i = 0; i < MeasNumInCluster; i++)
			{
				fVar += (f32MeasPosZInCluster[i] - fMean) * (f32MeasPosZInCluster[i] - fMean);
			}

			fPosTh = _sp_bound(fVar, 0.5, 1.5);

			// clustering at the median posz
			float32_t fHegiht;

			if (MeasNumInCluster > 0)
			{
				nMedianInd = _sp_max(MeasNumInCluster / 2 - 1, 0);

				int16_t nMinInd = nMedianInd;
				int16_t nMaxInd = nMedianInd;

				// Cluster min
				for (int nind = nMedianInd; nind > 0; nind--)
				{
					if (_sp_abs(f32MeasPosZInCluster[nind] - f32MeasPosZInCluster[nind - 1]) > fPosTh)
					{
						break;
					}

					nMinInd = nind - 1;
				}

				// Cluster max
				for (int nind = nMedianInd; nind < MeasNumInCluster - 1; nind++)
				{
					if (_sp_abs(f32MeasPosZInCluster[nind + 1] - f32MeasPosZInCluster[nind]) > fPosTh)
					{
						break;
					}

					nMaxInd = nind + 1;
				}

				// even num case
				if ((0 == (MeasNumInCluster % 2) && (nMaxInd == nMinInd) && (MeasNumInCluster > 1)))
				{
					nMaxInd = nMinInd + 1;
				}

				fHegiht = f32MeasPosZInCluster[nMaxInd] - f32MeasPosZInCluster[nMinInd];

				if (fHegiht < fHeightMin)
				{
					fHegiht = fHeightMin;
				}

				fPosZ = ((f32MeasPosZInCluster[nMaxInd]) + f32MeasPosZInCluster[nMinInd]) / 2.0f;


				// filtering out
				if (gTrackData[nTrk].Status == NEW_TRACK)
				{
					gTrackData[nTrk].f32PosZ = fPosZ;
					gTrackData[nTrk].f32Height = fHegiht;
				}
				else
				{
					gTrackData[nTrk].f32PosZ = fAlpha * gTrackData[nTrk].f32PosZ + (1.0f - fAlpha) * fPosZ;
					gTrackData[nTrk].f32Height = fAlpha * gTrackData[nTrk].f32Height + (1.0f - fAlpha) * fHegiht;
				}

			}
		}
	}
}
