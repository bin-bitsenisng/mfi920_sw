/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Trk_Main.h"
#include "Trk_Prediction.h"


/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
static void Clst_vEgoMotionComp(ClstData_t* Cluster, TrkEgoMotionInfo_t *EgoInfo);
static void Trk_vEgoMotionComp(TrackData_t* Track, TrkEgoMotionInfo_t *EgoInfo);


/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Clst_vPrediction(void)
{
	int16_t i_clst;
	float32_t temp_Mat[2];
	float32_t temp_Mat_2[2][2];
	float32_t temp_Mat_3[2][2];

	/* Acceleration Input model */
	for (i_clst = 0; i_clst < TRK_NUM_CLUSTER_MAX; i_clst++)
	{
		if (gClstData[i_clst].Status != INVALID)
		{
			MatMul_2x2and2x1(KalmanParam.F, gClstData[i_clst].f32UpdStateX, gClstData[i_clst].f32PredStateX);
			MatMul_2x2and2x1(KalmanParam.F, gClstData[i_clst].f32UpdStateY, gClstData[i_clst].f32PredStateY);

			Clst_vEgoMotionComp(&gClstData[i_clst], &gTrkEgoMotionInfo);
			
			MatMul_2x2and2x2(KalmanParam.F, gClstData[i_clst].Kalman.Px, temp_Mat_2);
			MatMul_2x2and2x2(temp_Mat_2, KalmanParam.F_Trs, temp_Mat_3);
			MatAdd_2x2(temp_Mat_3, KalmanParam.Qx, gClstData[i_clst].Kalman.Px);

			MatMul_2x2and2x2(KalmanParam.F, gClstData[i_clst].Kalman.Py, temp_Mat_2);
			MatMul_2x2and2x2(temp_Mat_2, KalmanParam.F_Trs, temp_Mat_3);
			MatAdd_2x2(temp_Mat_3, KalmanParam.Qy, gClstData[i_clst].Kalman.Py);
		}
	}

}


void Trk_vPrediction(void)
{
	int16_t i_trk;
	int16_t i_corner;
	float32_t temp_X;
	float32_t temp_Y;
	float32_t temp_X_2;
	float32_t temp_Y_2;
	float32_t temp_Mat_3[2];

	/* Constant Velocity */
	for (i_trk = 0; i_trk < TRK_NUM_TRACK_MAX; i_trk++)
	{
		if (gTrackData[i_trk].Status != INVALID)
		{
			MatMul_2x2and2x1(KalmanParam.F, gTrackData[i_trk].UpdState.f32StateX, gTrackData[i_trk].PredState.f32StateX);
			MatMul_2x2and2x1(KalmanParam.F, gTrackData[i_trk].UpdState.f32StateY, gTrackData[i_trk].PredState.f32StateY);

			Trk_vEgoMotionComp(&gTrackData[i_trk], &gTrkEgoMotionInfo);

			gTrackData[i_trk].PredState.f32StateSpeed[1] = gTrackData[i_trk].UpdState.f32StateSpeed[1];
			gTrackData[i_trk].PredState.f32StateSpeed[0] = gTrackData[i_trk].UpdState.f32StateSpeed[0] + (gTrkCycleTime * gTrackData[i_trk].PredState.f32StateHeading[1]);

			gTrackData[i_trk].PredState.f32Length = gTrackData[i_trk].UpdState.f32Length;
			gTrackData[i_trk].PredState.f32Width = gTrackData[i_trk].UpdState.f32Width;

			gTrackData[i_trk].PredState.f32StateHeading[1] = gTrackData[i_trk].UpdState.f32StateHeading[1];
			gTrackData[i_trk].PredState.f32StateHeading[0] = (gTrackData[i_trk].UpdState.f32StateHeading[0] + gTrkCycleTime * gTrackData[i_trk].PredState.f32StateHeading[1]) - gTrkEgoMotionInfo.f32DeltaYaw_deg;

			gTrackData[i_trk].Ph[0][0] += (2.0f * gTrackData[i_trk].Ph[0][1] * gTrkCycleTime) + (gTrackData[i_trk].Ph[1][1] * gTrkCycleTime * gTrkCycleTime) + _sp_pow2(TRK_STD_Q_HEADING);
			gTrackData[i_trk].Ph[0][1] += gTrackData[i_trk].Ph[1][1] * gTrkCycleTime + TRK_STD_Q_HEADING * TRK_STD_Q_HEADINGRATE;
			gTrackData[i_trk].Ph[1][0] = gTrackData[i_trk].Ph[0][1];
			gTrackData[i_trk].Ph[1][1] += _sp_pow2(TRK_STD_Q_HEADINGRATE);

			temp_X = NegRotateX(gTrackData[i_trk].PredState.f32StateX[0], gTrackData[i_trk].PredState.f32StateY[0], gTrackData[i_trk].PredState.f32StateHeading[0]);
			temp_Y = NegRotateY(gTrackData[i_trk].PredState.f32StateX[0], gTrackData[i_trk].PredState.f32StateY[0], gTrackData[i_trk].PredState.f32StateHeading[0]);

			for (i_corner = 0; i_corner < 4; i_corner++)
			{
				switch (i_corner)
				{
				case 0:
					temp_X_2 = temp_X + (gTrackData[i_trk].PredState.f32Length * 0.5f);
					temp_Y_2 = temp_Y + (gTrackData[i_trk].PredState.f32Width * 0.5f);
					break;
				case 1:
					temp_X_2 = temp_X + (gTrackData[i_trk].PredState.f32Length * 0.5f);
					temp_Y_2 = temp_Y - (gTrackData[i_trk].PredState.f32Width * 0.5f);
					break;
				case 2:
					temp_X_2 = temp_X - (gTrackData[i_trk].PredState.f32Length * 0.5f);
					temp_Y_2 = temp_Y - (gTrackData[i_trk].PredState.f32Width * 0.5f);
					break;
				case 3:
					temp_X_2 = temp_X - (gTrackData[i_trk].PredState.f32Length * 0.5f);
					temp_Y_2 = temp_Y + (gTrackData[i_trk].PredState.f32Width * 0.5f);
					break;
				default:
					break;
				}

				gTrackData[i_trk].PredState.f32BoundingBoxX[i_corner] = RotateX(temp_X_2, temp_Y_2, gTrackData[i_trk].PredState.f32StateHeading[0]);
				gTrackData[i_trk].PredState.f32BoundingBoxY[i_corner] = RotateY(temp_X_2, temp_Y_2, gTrackData[i_trk].PredState.f32StateHeading[0]);
			}

			switch (gTrackData[i_trk].RefPt)
			{
			case REF_FRONT_LEFT:
				gTrackData[i_trk].PredState.f32Ref_PosX = gTrackData[i_trk].PredState.f32BoundingBoxX[0];
				gTrackData[i_trk].PredState.f32Ref_PosY = gTrackData[i_trk].PredState.f32BoundingBoxY[0];
				break;
			case REF_FRONT:
				gTrackData[i_trk].PredState.f32Ref_PosX = (gTrackData[i_trk].PredState.f32BoundingBoxX[0] + gTrackData[i_trk].PredState.f32BoundingBoxX[1]) * 0.5f;
				gTrackData[i_trk].PredState.f32Ref_PosY = (gTrackData[i_trk].PredState.f32BoundingBoxY[0] + gTrackData[i_trk].PredState.f32BoundingBoxY[1]) * 0.5f;
				break;
			case REF_FRONT_RIGHT:
				gTrackData[i_trk].PredState.f32Ref_PosX = gTrackData[i_trk].PredState.f32BoundingBoxX[1];
				gTrackData[i_trk].PredState.f32Ref_PosY = gTrackData[i_trk].PredState.f32BoundingBoxY[1];
				break;
			case REF_RIGHT:
				gTrackData[i_trk].PredState.f32Ref_PosX = (gTrackData[i_trk].PredState.f32BoundingBoxX[1] + gTrackData[i_trk].PredState.f32BoundingBoxX[2]) * 0.5f;
				gTrackData[i_trk].PredState.f32Ref_PosY = (gTrackData[i_trk].PredState.f32BoundingBoxY[1] + gTrackData[i_trk].PredState.f32BoundingBoxY[2]) * 0.5f;
				break;
			case REF_REAR_RIGHT:
				gTrackData[i_trk].PredState.f32Ref_PosX = gTrackData[i_trk].PredState.f32BoundingBoxX[2];
				gTrackData[i_trk].PredState.f32Ref_PosY = gTrackData[i_trk].PredState.f32BoundingBoxY[2];
				break;
			case REF_REAR:
				gTrackData[i_trk].PredState.f32Ref_PosX = (gTrackData[i_trk].PredState.f32BoundingBoxX[2] + gTrackData[i_trk].PredState.f32BoundingBoxX[3]) * 0.5f;
				gTrackData[i_trk].PredState.f32Ref_PosY = (gTrackData[i_trk].PredState.f32BoundingBoxY[2] + gTrackData[i_trk].PredState.f32BoundingBoxY[3]) * 0.5f;
				break;
			case REF_REAR_LEFT:
				gTrackData[i_trk].PredState.f32Ref_PosX = gTrackData[i_trk].PredState.f32BoundingBoxX[3];
				gTrackData[i_trk].PredState.f32Ref_PosY = gTrackData[i_trk].PredState.f32BoundingBoxY[3];
				break;
			case REF_LEFT:
				gTrackData[i_trk].PredState.f32Ref_PosX = (gTrackData[i_trk].PredState.f32BoundingBoxX[3] + gTrackData[i_trk].PredState.f32BoundingBoxX[0]) * 0.5f;
				gTrackData[i_trk].PredState.f32Ref_PosY = (gTrackData[i_trk].PredState.f32BoundingBoxY[3] + gTrackData[i_trk].PredState.f32BoundingBoxY[0]) * 0.5f;
				break;
			case REF_CENTER:
				gTrackData[i_trk].PredState.f32Ref_PosX = (gTrackData[i_trk].PredState.f32BoundingBoxX[0] + gTrackData[i_trk].PredState.f32BoundingBoxX[2]) * 0.5f;
				gTrackData[i_trk].PredState.f32Ref_PosY = (gTrackData[i_trk].PredState.f32BoundingBoxY[0] + gTrackData[i_trk].PredState.f32BoundingBoxY[2]) * 0.5f;
				break;
			case REF_INVALID:
			default:
				gTrackData[i_trk].PredState.f32Ref_PosX = 0.0f;
				gTrackData[i_trk].PredState.f32Ref_PosY = 0.0f;
				break;
			}
		}
	}

}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
static void Clst_vEgoMotionComp(ClstData_t* Cluster, TrkEgoMotionInfo_t *EgoInfo)
{
	float32_t travel_dist_x, travel_dist_y;
	int16_t i_state;
	float32_t temp_X, temp_Y;

	travel_dist_x = EgoInfo->f32VelX * gTrkCycleTime;
	travel_dist_y = EgoInfo->f32VelY * gTrkCycleTime;

	Cluster->f32PredStateX[0] -= travel_dist_x;
	Cluster->f32PredStateY[0] -= travel_dist_y;

	for (i_state = 0; i_state < 2; i_state++)
	{
		temp_X = Cluster->f32PredStateX[i_state];
		temp_Y = Cluster->f32PredStateY[i_state];

		Cluster->f32PredStateX[i_state] = NegRotateX(temp_X, temp_Y, EgoInfo->f32DeltaYaw_deg);
		Cluster->f32PredStateY[i_state] = NegRotateY(temp_X, temp_Y, EgoInfo->f32DeltaYaw_deg);
	}

	/* Do not compensate tracklet velocity with host yaw */
	if (Cluster->Status == NEW_TRACK)
	{
		Cluster->f32PredStateX[1] = Cluster->f32UpdStateX[1];
		Cluster->f32PredStateY[1] = Cluster->f32UpdStateY[1];
	}
}


static void Trk_vEgoMotionComp(TrackData_t* Track, TrkEgoMotionInfo_t *EgoInfo)
{
	float32_t travel_dist_x, travel_dist_y;
	int16_t i_state;
	float32_t temp_X, temp_Y;

	travel_dist_x = EgoInfo->f32VelX * gTrkCycleTime;
	travel_dist_y = EgoInfo->f32VelY * gTrkCycleTime;

	Track->PredState.f32StateX[0] -= travel_dist_x;
	Track->PredState.f32StateY[0] -= travel_dist_y;

	for (i_state = 0; i_state < 2; i_state++)
	{
		temp_X = Track->PredState.f32StateX[i_state];
		temp_Y = Track->PredState.f32StateY[i_state];

		Track->PredState.f32StateX[i_state] = NegRotateX(temp_X, temp_Y, EgoInfo->f32DeltaYaw_deg);
		Track->PredState.f32StateY[i_state] = NegRotateY(temp_X, temp_Y, EgoInfo->f32DeltaYaw_deg);
	}

}