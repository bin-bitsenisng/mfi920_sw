/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Trk_Main.h"
#include "Trk_Managing.h"
#include "Trk_Correction.h"


/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
static void Clst_vNewClusterGen(void);
static void Clst_vUpdateStatus(void);

static void Trk_vNewTrkGen(void);
static void Trk_vMerging(void);
static void Trk_vUpdateStatus(void);


/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Clst_vInit(ClstData_t *Cluster)
{
	Cluster->Status 	= INVALID;
	Cluster->MovState 	= STATIONARY;

	Cluster->u16AliveAge 			= 0;
	Cluster->u16StatusAge 			= 0;
	Cluster->s16NewTrkTrans_Score 	= 0;
	Cluster->s16MoveStateCnt 		= 0;

	Cluster->f32PredStateX[0] = 0.0f;
	Cluster->f32PredStateX[1] = 0.0f;
	Cluster->f32PredStateY[0] = 0.0f;
	Cluster->f32PredStateY[1] = 0.0f;
	Cluster->f32UpdStateX[0] = 0.0f;
	Cluster->f32UpdStateX[1] = 0.0f;
	Cluster->f32UpdStateY[0] = 0.0f;
	Cluster->f32UpdStateY[1] = 0.0f;
	
	Cluster->f32AccelX = 0.0f;
	Cluster->f32AccelY = 0.0f;

	Cluster->Kalman.Px[0][0] = 0.0f;
	Cluster->Kalman.Px[0][1] = 0.0f;
	Cluster->Kalman.Px[1][0] = 0.0f;
	Cluster->Kalman.Px[1][1] = 0.0f;
	Cluster->Kalman.Py[0][0] = 0.0f;
	Cluster->Kalman.Py[0][1] = 0.0f;
	Cluster->Kalman.Py[1][0] = 0.0f;
	Cluster->Kalman.Py[1][1] = 0.0f;
	Cluster->Kalman.Kx[0][0] = 0.0f;
	Cluster->Kalman.Kx[0][1] = 0.0f;
	Cluster->Kalman.Kx[1][0] = 0.0f;
	Cluster->Kalman.Kx[1][1] = 0.0f;
	Cluster->Kalman.Ky[0][0] = 0.0f;
	Cluster->Kalman.Ky[0][1] = 0.0f;
	Cluster->Kalman.Ky[1][0] = 0.0f;
	Cluster->Kalman.Ky[1][1] = 0.0f;
	Cluster->Kalman.Rx[0][0] = 0.0f;
	Cluster->Kalman.Rx[0][1] = 0.0f;
	Cluster->Kalman.Rx[1][0] = 0.0f;
	Cluster->Kalman.Rx[1][1] = 0.0f;
	Cluster->Kalman.Ry[0][0] = 0.0f;
	Cluster->Kalman.Ry[0][1] = 0.0f;
	Cluster->Kalman.Ry[1][0] = 0.0f;
	Cluster->Kalman.Ry[1][1] = 0.0f;
	
	Cluster->s16AssoMeasClstCnt = 0;
	Cluster->s16AssoMeasNoisePtCnt = 0;

	Cluster->s16GroupTrkIdx = -1;
	Cluster->s16GroupInconsistentCnt = 0;
	
	Cluster->f32Mean_Range		= 0.0f;
	Cluster->f32Std_Range		= 0.0f;
	Cluster->f32Mean_RangeRate	= 0.0f;
	Cluster->f32Std_RangeRate	= 0.0f;
	Cluster->f32Mean_Azimuth	= 0.0f;
	Cluster->f32Std_Azimuth		= 0.0f;
	Cluster->f32Mean_Xpos		= 0.0f;
	Cluster->f32Std_Xpos		= 0.0f;
	Cluster->f32Mean_Ypos		= 0.0f;
	Cluster->f32Std_Ypos		= 0.0f;
	Cluster->f32Mean_Pow_dB		= 0.0f;
	Cluster->f32Std_Pow_dB		= 0.0f;
	Cluster->f32MaxPow_dB		= 0.0f;

}


void Clst_vManagement(void)
{
	Clst_vNewClusterGen();
	Clst_vUpdateStatus();

}


void Trk_vInit(TrackData_t *Track)
{
	int16_t i_clst;

	Track->Status 		= INVALID;
	Track->u16AliveAge 	= 0;
	Track->u16StatusAge = 0;

	Track->PredState.f32StateX[0] = 0.0f;
	Track->PredState.f32StateX[1] = 0.0f;
	Track->PredState.f32StateY[0] = 0.0f;
	Track->PredState.f32StateY[1] = 0.0f;

	Track->PredState.f32Ref_PosX = 0.0f;
	Track->PredState.f32Ref_PosY = 0.0f;

	Track->PredState.f32BoundingBoxX[0] = 0.0f;
	Track->PredState.f32BoundingBoxX[1] = 0.0f;
	Track->PredState.f32BoundingBoxX[2] = 0.0f;
	Track->PredState.f32BoundingBoxX[3] = 0.0f;

	Track->PredState.f32BoundingBoxY[0] = 0.0f;
	Track->PredState.f32BoundingBoxY[1] = 0.0f;
	Track->PredState.f32BoundingBoxY[2] = 0.0f;
	Track->PredState.f32BoundingBoxY[3] = 0.0f;

	Track->PredState.f32Length = 0.0f;
	Track->PredState.f32Width = 0.0f;

	Track->PredState.f32StateHeading[0] = 0.0f;
	Track->PredState.f32StateHeading[1] = 0.0f;

	Track->PredState.f32StateSpeed[0] = 0.0f;
	Track->PredState.f32StateSpeed[1] = 0.0f;

	Track->UpdState = Track->PredState;
	Track->MeasState = Track->PredState;

	Track->f32AccX = 0.0f;
	Track->f32AccY = 0.0f;

	Track->RefPt 	= REF_INVALID;
	Track->MovState = STATIONARY;

	Track->f32PosZ   = 0.0f;
	Track->f32Height = 0.0f;

	Track->s16GroupClstCnt = 0;
	for(i_clst = 0; i_clst < TRK_NUM_GROUP_CLST_MAX; i_clst++)
	{
		Track->s16GroupClstIdx[i_clst] = 0;
	}
	
	Track->u8Merging_Flag = 0;

	Track->Ph[0][0] = 0.0f;
	Track->Ph[0][1] = 0.0f;
	Track->Ph[1][0] = 0.0f;
	Track->Ph[1][1] = 0.0f;

	Track->Kh[0] = 0.0f;
	Track->Kh[1] = 0.0f;

	Track->f32Pow_dB 	= 0.0f;
	Track->f32MaxPow_dB = 0.0f;

	Track->ghost_flag = 0;

	/************************
	***** sensor fusion *****
	************************/

	/* Update using vision object */
	Track->fusion_state = SF_DEFAULT;
	Track->FusionAge = 0;

	/* Vision object association */
	Track->bbox_overlap_ratio = 0.0; 
	Track->match_vision_obj_idx = -1;

	/* Class decision */
	Track->obj_class = OBJCLASS_UNKNOWN;
	Track->obj_class_prob = 0;
	memset(Track->obj_class_cnt, 0, TRK_SENSOR_FUSION_CLASS_TYPE_MAX * sizeof(float32_t));

}


void Trk_vManagement(void)
{
	Trk_vNewTrkGen();
	Trk_vMerging();
	Trk_vUpdateStatus();

}

/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
static void Clst_vNewClusterGen(void)
{
	uint8_t cond1;	/* condition for moving cluster */
	uint8_t cond2;	/* condition for stationary cluster */
	int16_t i_mscl;
	int16_t i_clst;
	uint8_t empty_space;
	float32_t temp_priority;
	float32_t max_priority;
	
	int16_t newCluster_idx;

	/* Check new cluster generation condition */
	for (i_mscl = 0; i_mscl < gMsclCnt; i_mscl++)
	{
		cond1 = 0;
		cond2 = 0;

		if ((gMeasClst[i_mscl].State == VALID_CLST)
			&& (gMeasClst[i_mscl].s16AssoClstIdx == -1)
			&& (gMeasClst[i_mscl].Range.f32Min < CLST_GENERATION_RANGE_MAX)
			&& (_sp_abs(gMeasClst[i_mscl].AziAng.f32Mean) < CLST_GENERATION_ANGLE_MAX)
			&& (gMeasClst[i_mscl].ReflectType != REFLECT_TYPE_WHEEL))
		{
			if ((gMeasClst[i_mscl].MovState == PRECEDING) || (gMeasClst[i_mscl].MovState == ONCOMING))
			{
				cond1 = 1;
			}
#if TRK_SF_GEN_STATIONARY_CLST_FROM_VOBJ_FLAG
			else if ((gMeasClst[i_mscl].MovState == STATIONARY) && (gMeasClst[i_mscl].MatchVisionObjIdx != -1))
			{
				/* Activated stationary object in case of vision object only */
				cond2 = 1;
			}
#endif
			else
			{
				/* Do nothing */
			}
		}
		else
		{
			/* Do nothing */
		}


		if (cond1 || cond2)
		{
			empty_space = 0;
			max_priority = 0;

			/* Check accessibility */
			for (i_clst = 0; i_clst < TRK_NUM_CLUSTER_MAX; i_clst++)
			{
				if (gClstData[i_clst].Status == INVALID)
				{
					empty_space = 1;
					newCluster_idx = i_clst;
					break;
				}
				else
				{
					temp_priority = _sp_hypotf(gClstData[i_clst].f32PredStateX[0], gClstData[i_clst].f32PredStateY[0]);

					if (gClstData[i_clst].MovState == STATIONARY)
					{
						temp_priority += CLST_PRIORITY_STATIONARY_PENALTY;
					}

					max_priority = _sp_max(temp_priority, max_priority);

					if (max_priority == temp_priority)
					{
						newCluster_idx = i_clst;
					}
				}
			}

			temp_priority = gMeasClst[i_mscl].Range.f32Min;
			if (cond2)
			{
				temp_priority += CLST_PRIORITY_STATIONARY_PENALTY;
			}

			if ((empty_space == 1) || (temp_priority < max_priority))
			{
				gClstData[newCluster_idx].Status 				= NEW_TRACK;
				gClstData[newCluster_idx].MovState 				= gMeasClst[i_mscl].MovState;

				gClstData[newCluster_idx].u16AliveAge 			= 0;
				gClstData[newCluster_idx].u16StatusAge 			= 0;
				gClstData[newCluster_idx].s16NewTrkTrans_Score 	= 0;
				gClstData[newCluster_idx].s16MoveStateCnt 		= 0;

				gClstData[newCluster_idx].f32PredStateX[0] 		= gMeasClst[i_mscl].Xpos.f32Mean;
				gClstData[newCluster_idx].f32PredStateX[1] 		= gMeasClst[i_mscl].RangeRate.f32Mean / _sp_cosdf(gMeasClst[i_mscl].AziAng.f32Mean);
				gClstData[newCluster_idx].f32PredStateY[0] 		= gMeasClst[i_mscl].Ypos.f32Mean;
				gClstData[newCluster_idx].f32PredStateY[1]		= 0.0f;
				gClstData[newCluster_idx].f32UpdStateX[0] 		= 0.0f;
				gClstData[newCluster_idx].f32UpdStateX[1] 		= 0.0f;
				gClstData[newCluster_idx].f32UpdStateY[0] 		= 0.0f;
				gClstData[newCluster_idx].f32UpdStateY[1] 		= 0.0f;
				gClstData[newCluster_idx].f32AccelX 			= 0.0f;
				gClstData[newCluster_idx].f32AccelY 			= 0.0f;

				gClstData[newCluster_idx].Kalman.Px[0][0] 		= _sp_pow2(TRKLET_STD_P_POS_X_INIT);
				gClstData[newCluster_idx].Kalman.Px[0][1] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Px[1][0] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Px[1][1] 		= _sp_pow2(TRKLET_STD_P_VEL_X_INIT);
				gClstData[newCluster_idx].Kalman.Py[0][0] 		= _sp_pow2(TRKLET_STD_P_POS_Y_INIT);
				gClstData[newCluster_idx].Kalman.Py[0][1] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Py[1][0] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Py[1][1] 		= _sp_pow2(TRKLET_STD_P_VEL_Y_INIT);

				gClstData[newCluster_idx].Kalman.Kx[0][0] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Kx[0][1] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Kx[1][0] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Kx[1][1] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Ky[0][0] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Ky[0][1] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Ky[1][0] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Ky[1][1] 		= 0.0f;

				gClstData[newCluster_idx].Kalman.Rx[0][0] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Rx[0][1] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Rx[1][0] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Rx[1][1] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Ry[0][0] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Ry[0][1] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Ry[1][0] 		= 0.0f;
				gClstData[newCluster_idx].Kalman.Ry[1][1] 		= 0.0f;

				gClstData[newCluster_idx].f32Mean_Range			= gMeasClst[i_mscl].Range.f32Mean;
				gClstData[newCluster_idx].f32Std_Range			= gMeasClst[i_mscl].Range.f32StdDev;
				gClstData[newCluster_idx].f32Mean_Azimuth		= gMeasClst[i_mscl].AziAng.f32Mean;
				gClstData[newCluster_idx].f32Std_Azimuth		= gMeasClst[i_mscl].AziAng.f32StdDev;
				gClstData[newCluster_idx].f32Mean_RangeRate		= gMeasClst[i_mscl].RangeRate.f32Mean;
				gClstData[newCluster_idx].f32Std_RangeRate		= gMeasClst[i_mscl].RangeRate.f32StdDev;
				gClstData[newCluster_idx].f32Mean_Xpos			= gMeasClst[i_mscl].Xpos.f32Mean;
				gClstData[newCluster_idx].f32Std_Xpos			= gMeasClst[i_mscl].Xpos.f32StdDev;
				gClstData[newCluster_idx].f32Mean_Ypos			= gMeasClst[i_mscl].Ypos.f32Mean;
				gClstData[newCluster_idx].f32Std_Ypos			= gMeasClst[i_mscl].Ypos.f32StdDev;
				gClstData[newCluster_idx].f32Mean_Pow_dB		= gMeasClst[i_mscl].Power.f32Mean;
				gClstData[newCluster_idx].f32Std_Pow_dB			= gMeasClst[i_mscl].Power.f32StdDev;
				gClstData[newCluster_idx].f32MaxPow_dB			= gMeasClst[i_mscl].Power.f32Max;

				gClstData[newCluster_idx].s16AssoMeasClstCnt = 1;
				gClstData[newCluster_idx].s16AssoMeasClstIdx[0] = i_mscl;
				gClstData[newCluster_idx].s16AssoMeasNoisePtCnt = 0;

				gClstData[newCluster_idx].s16GroupTrkIdx 		  = -1;
				gClstData[newCluster_idx].s16GroupInconsistentCnt = 0;

				gMeasClst[i_mscl].s16AssoClstIdx = newCluster_idx;
		
#if TRK_SF_GEN_STATIONARY_CLST_FROM_VOBJ_FLAG
				if (cond2)
				{
					gClstData[newCluster_idx].MatchVision0bjIdx = gMeasClst[i_mscl].MatchVisionObjIdx;
				}
#endif
			}
		}
	}

}


static void Clst_vUpdateStatus(void)
{
	int16_t i_clst;

	for (i_clst = 0; i_clst < TRK_NUM_CLUSTER_MAX; i_clst++)
	{
		if (gClstData[i_clst].Status != INVALID)
		{
			/* Update Age */
			gClstData[i_clst].u16AliveAge  = (gClstData[i_clst].u16AliveAge < TRK_U16_MAX_NUM)  ? gClstData[i_clst].u16AliveAge + 1 : TRK_U16_MAX_NUM;
			gClstData[i_clst].u16StatusAge = (gClstData[i_clst].u16StatusAge < TRK_U16_MAX_NUM) ? gClstData[i_clst].u16StatusAge + 1 : TRK_U16_MAX_NUM;

			/* Update Track Status */
			if (gClstData[i_clst].Status == NEW_TRACK)
			{
				if ((gClstData[i_clst].s16AssoMeasClstCnt > 0) || (gClstData[i_clst].s16AssoMeasNoisePtCnt > 0))
				{
					gClstData[i_clst].s16NewTrkTrans_Score += CLST_STATUS_TRANS_ASSOCIATED_SCORE;

					if (gClstData[i_clst].s16NewTrkTrans_Score >= CLST_TRANSITION_SCORE)
					{
						gClstData[i_clst].Status = UPDATED_TRACK;
						gClstData[i_clst].u16StatusAge = 1;
					}
				}
				else
				{
					gClstData[i_clst].s16NewTrkTrans_Score -= CLST_COASTED_PENALTY;

					if (gClstData[i_clst].s16NewTrkTrans_Score <= 0)
					{
						Clst_vInit(&gClstData[i_clst]);
					}
				}
			}
			else if (gClstData[i_clst].Status == UPDATED_TRACK)
			{
				if ((gClstData[i_clst].s16AssoMeasClstCnt == 0) && (gClstData[i_clst].s16AssoMeasNoisePtCnt == 0))
				{
					gClstData[i_clst].Status = COASTED_TRACK;
					gClstData[i_clst].u16StatusAge = 1;
				}
			}
			else
			{
				if ((gClstData[i_clst].s16AssoMeasClstCnt > 0) || (gClstData[i_clst].s16AssoMeasNoisePtCnt > 0))
				{
					gClstData[i_clst].Status = UPDATED_TRACK;
					gClstData[i_clst].u16StatusAge = 1;
				}
				else
				{
					if (((gClstData[i_clst].s16GroupTrkIdx == -1) && (gClstData[i_clst].u16StatusAge >= CLST_COASTED_DELETION_STAGE_AGE_NON_GROUPED)) ||
						(gClstData[i_clst].u16StatusAge >= CLST_COASTED_DELETION_STAGE_AGE_GROUPED) ||
						(gClstData[i_clst].f32UpdStateX[0] < 0.0f))
					{
						Clst_vInit(&gClstData[i_clst]);
					}
				}
			}
		}
	}

}


static void Trk_vNewTrkGen(void)
{
	int16_t i_cnt;
	int16_t i_clst, j_clst;
	int16_t i_trk;
	uint8_t empty_space;
	float32_t temp_priority;
	float32_t max_priority;
	int16_t newTrk_idx;
	int16_t nearby_obj_flag;
	
	/* stationary object detection from vision object */
	int16_t i_mscl;
	int16_t i_asso;
	float32_t min_asso_cost;
	float32_t asso_cost;
	int16_t min_asso_cost_mscl_idx;
	int16_t match_vobj_idx;

	int16_t new_obj_gen_flag_radar;
	int16_t new_obj_gen_flag_fusion_stationary;

	for (i_clst = 0; i_clst < TRK_NUM_CLUSTER_MAX; i_clst++)
	{
		new_obj_gen_flag_radar = 0;
		new_obj_gen_flag_fusion_stationary = 0;

		if ((gClstData[i_clst].Status == UPDATED_TRACK) &&
			(gClstData[i_clst].s16GroupTrkIdx == -1))
		{
			empty_space = 0;
			max_priority = 0;
			nearby_obj_flag = 0;

			for (i_trk = 0; i_trk < TRK_NUM_TRACK_MAX; i_trk++)
			{
				if (gTrackData[i_trk].Status == INVALID)
				{
					empty_space = 1;
					newTrk_idx = i_trk;
					break;
				}
				else
				{
					temp_priority = _sp_abs(gTrackData[i_trk].PredState.f32StateY[0]);

					if (gTrackData[i_trk].MovState == STATIONARY)
					{
						temp_priority += TRK_PRIORITY_STATIONARY_PENALTY;
					}

					max_priority = _sp_max(temp_priority, max_priority);

					if (max_priority == temp_priority)
					{
						newTrk_idx = i_trk;
					}
				}
			}

			for (i_trk = 0; i_trk < TRK_NUM_TRACK_MAX; i_trk++)
			{
				if (gTrackData[i_trk].Status != INVALID)
				{
					if ((_sp_abs(NegRotateX(gTrackData[i_trk].PredState.f32StateX[0], gTrackData[i_trk].PredState.f32StateY[0], gTrackData[i_trk].PredState.f32StateHeading[0]) - NegRotateX(gClstData[i_clst].f32UpdStateX[0], gClstData[i_clst].f32UpdStateY[0], gTrackData[i_trk].PredState.f32StateHeading[0])) < ((gTrackData[i_trk].PredState.f32Length * 0.5f) + TRK_NEWTRKGEN_NEARBY_GATE_POS_X)) &&
						(_sp_abs(NegRotateY(gTrackData[i_trk].PredState.f32StateX[0], gTrackData[i_trk].PredState.f32StateY[0], gTrackData[i_trk].PredState.f32StateHeading[0]) - NegRotateY(gClstData[i_clst].f32UpdStateX[0], gClstData[i_clst].f32UpdStateY[0], gTrackData[i_trk].PredState.f32StateHeading[0])) < ((gTrackData[i_trk].PredState.f32Width * 0.5f) + TRK_NEWTRKGEN_NEARBY_GATE_POS_Y)))
					{
						nearby_obj_flag = 1;
						break;
					}
				}
			}

			temp_priority = _sp_abs(gClstData[i_clst].f32UpdStateY[0]);

			if (gClstData[i_clst].MovState == STATIONARY)
			{
				temp_priority += TRK_PRIORITY_STATIONARY_PENALTY;
			}

			if ((empty_space == 1) || (temp_priority < max_priority))
			{
				if ((nearby_obj_flag == 0) 
					&& ((gClstData[i_clst].MovState == PRECEDING) || (gClstData[i_clst].MovState == ONCOMING)))
				{
					new_obj_gen_flag_radar = 1;
				}
#if TRK_SF_GEN_STATIONARY_OBJ_FROM_VOBJ_FLAG
				else if (((gClstData[i_clst].MovState == STATIONARY) || (gClstData[i_clst].MovState == STOPPED)) &&
						 (gClstData[i_clst].s16AssoMeasClstCnt != 0))
				{
					min_asso_cost = TRK_INIT_ASSO_COST;
					min_asso_cost_mscl_idx = -1;
					for (i_asso = 0; i_asso < gClstData[i_clst].s16AssoMeasClstCnt; i_asso++)
					{
						i_mscl = gClstData[i_clst].s16AssoMeasClstIdx[i_asso];
						asso_cost = gMeasClst[i_mscl].f32AssoClstCost;
						if (asso_cost < min_asso_cost)
						{
							min_asso_cost = asso_cost;
							min_asso_cost_mscl_idx = i_mscl;
						}
					}

					if (gMeasClst[min_asso_cost_mscl_idx].MatchVisionObjIdx != -1)
					{
						new_obj_gen_flag_fusion_stationary = 1;
					}
				}
				else
				{
					/* Do nothing */
				}
#endif
			}
		}

		if ((new_obj_gen_flag_radar == 1) || (new_obj_gen_flag_fusion_stationary == 1))
		{
			/* clear cluster and object data before refreshing object */
			for (j_clst = 0; j_clst < gTrackData[newTrk_idx].s16GroupClstCnt; j_clst++)
			{
				gClstData[gTrackData[newTrk_idx].s16GroupClstIdx[j_clst]].s16GroupTrkIdx = -1;
			}

			/* Create new Track */
			gTrackData[newTrk_idx].Status = UPDATED_TRACK;
			gTrackData[newTrk_idx].u16AliveAge = 0;
			gTrackData[newTrk_idx].u16StatusAge = 0;

			gTrackData[newTrk_idx].PredState.f32StateX[0] = gClstData[i_clst].f32UpdStateX[0];
			gTrackData[newTrk_idx].PredState.f32StateX[1] = gClstData[i_clst].f32UpdStateX[1];
			gTrackData[newTrk_idx].PredState.f32StateY[0] = gClstData[i_clst].f32UpdStateY[0];
			gTrackData[newTrk_idx].PredState.f32StateY[1] = gClstData[i_clst].f32UpdStateY[1];

			gTrackData[newTrk_idx].PredState.f32Ref_PosX = gClstData[i_clst].f32UpdStateX[0];
			gTrackData[newTrk_idx].PredState.f32Ref_PosY = gClstData[i_clst].f32UpdStateY[0];

			gTrackData[newTrk_idx].PredState.f32BoundingBoxX[0] = gClstData[i_clst].f32UpdStateX[0];
			gTrackData[newTrk_idx].PredState.f32BoundingBoxX[1] = gClstData[i_clst].f32UpdStateX[0];
			gTrackData[newTrk_idx].PredState.f32BoundingBoxX[2] = gClstData[i_clst].f32UpdStateX[0];
			gTrackData[newTrk_idx].PredState.f32BoundingBoxX[3] = gClstData[i_clst].f32UpdStateX[0];

			gTrackData[newTrk_idx].PredState.f32BoundingBoxY[0] = gClstData[i_clst].f32UpdStateY[0];
			gTrackData[newTrk_idx].PredState.f32BoundingBoxY[1] = gClstData[i_clst].f32UpdStateY[0];
			gTrackData[newTrk_idx].PredState.f32BoundingBoxY[2] = gClstData[i_clst].f32UpdStateY[0];
			gTrackData[newTrk_idx].PredState.f32BoundingBoxY[3] = gClstData[i_clst].f32UpdStateY[0];

			gTrackData[newTrk_idx].MovState = gClstData[i_clst].MovState;

			gTrackData[newTrk_idx].PredState.f32StateSpeed[0] = _sp_hypotf(gClstData[i_clst].f32UpdStateX[1], gClstData[i_clst].f32UpdStateY[1]);
			gTrackData[newTrk_idx].PredState.f32StateSpeed[1] = 0.0f;

			gTrackData[newTrk_idx].f32AccX = 0.0f;
			gTrackData[newTrk_idx].f32AccY = 0.0f;

			gTrackData[newTrk_idx].s16GroupClstCnt = 1;
			gTrackData[newTrk_idx].s16GroupClstIdx[0] = i_clst;
			gTrackData[newTrk_idx].u8Merging_Flag = 0;

			gTrackData[newTrk_idx].Ph[0][0] = _sp_pow2(TRK_STD_P_HEADING_INIT);
			gTrackData[newTrk_idx].Ph[0][1] = 0.0f;
			gTrackData[newTrk_idx].Ph[1][0] = 0.0f;
			gTrackData[newTrk_idx].Ph[1][1] = _sp_pow2(TRK_STD_P_HEADINGRATE_INIT);

			gTrackData[newTrk_idx].Kh[0] = 0.0f;
			gTrackData[newTrk_idx].Kh[1] = 0.0f;

			gTrackData[newTrk_idx].f32Pow_dB = gClstData[i_clst].f32MaxPow_dB - gClstData[i_clst].f32Std_Pow_dB;
			gTrackData[newTrk_idx].f32MaxPow_dB = gClstData[i_clst].f32MaxPow_dB;

			gClstData[i_clst].s16GroupTrkIdx = newTrk_idx;
			gClstData[i_clst].s16GroupInconsistentCnt = 0;

			//TODO set default para
			gTrackData[newTrk_idx].f32PosZ = 0.75f;
			gTrackData[newTrk_idx].f32Height = 1.5f;


			if (new_obj_gen_flag_radar == 1)
			{
				/* Fusion */
				if (gTrackData[newTrk_idx].fusion_state == SF_DEFAULT)
				{
					gTrackData[newTrk_idx].fusion_state = SF_RADAR_ONLY;
				}

				if (gTrackData[newTrk_idx].MovState != STATIONARY)
				{
					gTrackData[newTrk_idx].PredState.f32Width = TRK_INIT_WIDTH_MOVING;
					gTrackData[newTrk_idx].PredState.f32Length = TRK_INIT_LENGTH_MOVING;

					gTrackData[newTrk_idx].PredState.f32StateHeading[0] = _sp_atan2df(gClstData[i_clst].f32UpdStateY[1], gClstData[i_clst].f32UpdStateX[1]);
					gTrackData[newTrk_idx].PredState.f32StateHeading[1] = 0.0f;
				}
				else if (gTrackData[newTrk_idx].MovState == STATIONARY)
				{
					gTrackData[newTrk_idx].PredState.f32Width = TRK_INIT_WIDTH_STATIONARY;
					gTrackData[newTrk_idx].PredState.f32Length = TRK_INIT_LENGTH_STATIONARY;

					gTrackData[newTrk_idx].PredState.f32StateHeading[0] = 0.0f;
					gTrackData[newTrk_idx].PredState.f32StateHeading[1] = 0.0f;
				}
			}
#if TRK_SF_GEN_STATIONARY_OBJ_FROM_VOBJ_FLAG
			else if (new_obj_gen_flag_fusion_stationary == 1)
			{
				match_vobj_idx = gMeasClst[min_asso_cost_mscl_idx].MatchVisionObjIdx;
				gTrackData[newTrk_idx].fusion_state = SF_FUSION_STATIONARY;
				gTrackData[newTrk_idx].match_vision_obj_idx = match_vobj_idx;
				gVisionObj[match_vobj_idx].match_radar_obj_idx = newTrk_idx;
				gTrackData[newTrk_idx].obj_class = gVisionObj[gMeasClst[min_asso_cost_mscl_idx].MatchVisionObjIdx].class_id;


				if (gTrackData[newTrk_idx].obj_class == OBJCLASS_CAR)
				{
					gTrackData[newTrk_idx].PredState.f32Width = TRK_SF_OBJECT_INIT_WIDTH_CAR;
					gTrackData[newTrk_idx].PredState.f32Length = TRK_SF_OBJECT_INIT_LENGTH_CAR;
				}
				else if ((gTrackData[newTrk_idx].obj_class == OBJCLASS_BIKE) || (gTrackData[newTrk_idx].obj_class == OBJCLASS_MOTOR))
				{
					gTrackData[newTrk_idx].PredState.f32Width = TRK_SF_OBJECT_INIT_WIDTH_MOTOR;
					gTrackData[newTrk_idx].PredState.f32Length = TRK_SF_OBJECT_INIT_LENGTH_MOTOR;
				}
				else if (gTrackData[newTrk_idx].obj_class == OBJCLASS_PEDESTRIAN)
				{
					gTrackData[newTrk_idx].PredState.f32Width = TRK_SF_OBJECT_INIT_WIDTH_PEDESTRIAN;
					gTrackData[newTrk_idx].PredState.f32Length = TRK_SF_OBJECT_INIT_LENGTH_PEDESTRIAN;
				}
				else
				{
					gTrackData[newTrk_idx].PredState.f32Width = TRK_SF_OBJECT_INIT_WIDTH_UNKNOWN;
					gTrackData[newTrk_idx].PredState.f32Length = TRK_SF_OBJECT_INIT_LENGTH_UNKNOWN;
				}




#if TRK_SF_STATIONARY_OBJ_HEADING_INIT_METHOD == TRK_SF_STATIONARY_OBJ_HEADING_INIT_MSCL_ROTATION
				gTrackData[newTrk_idx].PredState.f32StateHeading[0] = gMeasClst[min_asso_cost_mscl_idx].RotationAngle;
#elif TRK_SF_STATIONARY_OBJ_HEADING_INIT_METHOD == TRK_SF_STATIONARY_OBJ_HEADING_INIT_EGO_DIRECTION
				gTrackData[newTrk_idx].PredState.f32StateHeading[0] = gTrkEgoMotionInfo.f32YawRate_comp;
#endif
				gTrackData[newTrk_idx].PredState.f32StateHeading[1] = 0.0f;
			}
#endif
			gTrackData[newTrk_idx].RefPt = Trk_vEstimateRefPosition(&gTrackData[newTrk_idx].PredState, gTrackData[newTrk_idx].MovState, gTrackData[newTrk_idx].RefPt);
			Trk_vUpdatePosFromRefPt(&gTrackData[newTrk_idx].PredState, gTrackData[newTrk_idx].RefPt);

		}
	}
}


static void Trk_vMerging(void)
{
	int16_t i_trk1, i_trk2;
	int16_t i_cnt;

	float32_t ave_heading;

	for (i_trk1 = 0; i_trk1 < TRK_NUM_TRACK_MAX; i_trk1++)
	{
		if ((gTrackData[i_trk1].Status != INVALID) &&
			(gTrackData[i_trk1].MovState == PRECEDING || gTrackData[i_trk1].MovState == ONCOMING || gTrackData[i_trk1].MovState == STOPPED))
		{
			for (i_trk2 = (i_trk1 + 1); i_trk2 < TRK_NUM_TRACK_MAX; i_trk2++)
			{
				if ((gTrackData[i_trk2].Status != INVALID) &&
					(gTrackData[i_trk2].MovState == PRECEDING || gTrackData[i_trk2].MovState == ONCOMING || gTrackData[i_trk2].MovState == STOPPED))
				{
					ave_heading = (gTrackData[i_trk1].PredState.f32StateHeading[0] + gTrackData[i_trk2].PredState.f32StateHeading[0]) * 0.5f;

					/* Longitudinal Merging */
					if ((_sp_abs(gTrackData[i_trk1].PredState.f32StateX[1] - gTrackData[i_trk2].PredState.f32StateX[1]) < TRK_LONGITUDINAL_MERGING_GATE_VEL_X) &&
						(_sp_abs(gTrackData[i_trk1].PredState.f32StateY[1] - gTrackData[i_trk2].PredState.f32StateY[1]) < TRK_LONGITUDINAL_MERGING_GATE_VEL_Y) &&
						(_sp_abs(NegRotateY(gTrackData[i_trk1].PredState.f32StateX[0], gTrackData[i_trk1].PredState.f32StateY[0], ave_heading) - NegRotateY(gTrackData[i_trk2].PredState.f32StateX[0], gTrackData[i_trk2].PredState.f32StateY[0], ave_heading)) < TRK_LONGITUDINAL_MERGING_GATE_POS_Y) &&
						(_sp_abs(NegRotateX(gTrackData[i_trk1].PredState.f32StateX[0], gTrackData[i_trk1].PredState.f32StateY[0], ave_heading) - NegRotateX(gTrackData[i_trk2].PredState.f32StateX[0], gTrackData[i_trk2].PredState.f32StateY[0], ave_heading)) < ((gTrackData[i_trk1].PredState.f32Length + gTrackData[i_trk2].PredState.f32Length) * 0.5f + TRK_LONGITUDINAL_MERGING_GATE_POS_X)))
					{
						if (gTrackData[i_trk1].u16AliveAge == 0)
						{
							/* Merge tracklet/measurement from trk1 to trk2 */
							for (i_cnt = 0; i_cnt < gTrackData[i_trk1].s16GroupClstCnt; i_cnt++)
							{
								if (gTrackData[i_trk2].s16GroupClstCnt < TRK_NUM_CLUSTER_MAX)
								{
									gClstData[gTrackData[i_trk1].s16GroupClstIdx[i_cnt]].s16GroupTrkIdx = i_trk2;

									gTrackData[i_trk2].s16GroupClstIdx[gTrackData[i_trk2].s16GroupClstCnt] = gTrackData[i_trk1].s16GroupClstIdx[i_cnt];
									gTrackData[i_trk2].s16GroupClstCnt++;
								}
							}

							gTrackData[i_trk2].u8Merging_Flag = 1;
							Trk_vInit(&gTrackData[i_trk1]);
						}
						else if (gTrackData[i_trk2].u16AliveAge == 0)
						{
							/* Merge tracklet/measurement from trk2 to trk1 */
							for (i_cnt = 0; i_cnt < gTrackData[i_trk2].s16GroupClstCnt; i_cnt++)
							{
								if (gTrackData[i_trk1].s16GroupClstCnt < TRK_NUM_CLUSTER_MAX)
								{
									gClstData[gTrackData[i_trk2].s16GroupClstIdx[i_cnt]].s16GroupTrkIdx = i_trk1;

									gTrackData[i_trk1].s16GroupClstIdx[gTrackData[i_trk1].s16GroupClstCnt] = gTrackData[i_trk2].s16GroupClstIdx[i_cnt];
									gTrackData[i_trk1].s16GroupClstCnt++;
								}
							}

							gTrackData[i_trk1].u8Merging_Flag = 1;
							Trk_vInit(&gTrackData[i_trk2]);
						}
						else if (_sp_hypotf(gTrackData[i_trk1].PredState.f32StateX[0], gTrackData[i_trk1].PredState.f32StateY[0]) > _sp_hypotf(gTrackData[i_trk2].PredState.f32StateX[0], gTrackData[i_trk2].PredState.f32StateY[0]))
						{
							for (i_cnt = 0; i_cnt < gTrackData[i_trk1].s16GroupClstCnt; i_cnt++)
							{
								if (gTrackData[i_trk2].s16GroupClstCnt < TRK_NUM_CLUSTER_MAX)
								{
									gClstData[gTrackData[i_trk1].s16GroupClstIdx[i_cnt]].s16GroupTrkIdx = i_trk2;

									gTrackData[i_trk2].s16GroupClstIdx[gTrackData[i_trk2].s16GroupClstCnt] = gTrackData[i_trk1].s16GroupClstIdx[i_cnt];
									gTrackData[i_trk2].s16GroupClstCnt++;
								}
							}

							gTrackData[i_trk2].u8Merging_Flag = 1;
							Trk_vInit(&gTrackData[i_trk1]);
						}
						else
						{
							for (i_cnt = 0; i_cnt < gTrackData[i_trk2].s16GroupClstCnt; i_cnt++)
							{
								if (gTrackData[i_trk1].s16GroupClstCnt < TRK_NUM_CLUSTER_MAX)
								{
									gClstData[gTrackData[i_trk2].s16GroupClstIdx[i_cnt]].s16GroupTrkIdx = i_trk1;

									gTrackData[i_trk1].s16GroupClstIdx[gTrackData[i_trk1].s16GroupClstCnt] = gTrackData[i_trk2].s16GroupClstIdx[i_cnt];
									gTrackData[i_trk1].s16GroupClstCnt++;
								}
							}

							gTrackData[i_trk1].u8Merging_Flag = 1;
							Trk_vInit(&gTrackData[i_trk2]);
						}
					}
					/* Lateral Merging */
					else if ((_sp_abs(gTrackData[i_trk1].PredState.f32StateX[1] - gTrackData[i_trk2].PredState.f32StateX[1]) < TRK_LATERAL_MERGING_GATE_VEL_X) &&
						(_sp_abs(gTrackData[i_trk1].PredState.f32StateY[1] - gTrackData[i_trk2].PredState.f32StateY[1]) < TRK_LATERAL_MERGING_GATE_VEL_Y) &&
						(_sp_abs(NegRotateX(gTrackData[i_trk1].PredState.f32Ref_PosX, gTrackData[i_trk1].PredState.f32Ref_PosY, ave_heading) - NegRotateX(gTrackData[i_trk2].PredState.f32Ref_PosX, gTrackData[i_trk2].PredState.f32Ref_PosY, ave_heading)) < TRK_LATERAL_MERGING_GATE_POS_X) &&
						(_sp_abs(NegRotateY(gTrackData[i_trk1].PredState.f32StateX[0], gTrackData[i_trk1].PredState.f32StateY[0], ave_heading) - NegRotateY(gTrackData[i_trk2].PredState.f32StateX[0], gTrackData[i_trk2].PredState.f32StateY[0], ave_heading)) < (((gTrackData[i_trk1].PredState.f32Width + gTrackData[i_trk2].PredState.f32Width) * 0.5f) + TRK_LATERAL_MERGING_GATE_POS_Y)))

					{
						if (gTrackData[i_trk1].u16AliveAge < gTrackData[i_trk2].u16AliveAge)
						{
							for (i_cnt = 0; i_cnt < gTrackData[i_trk1].s16GroupClstCnt; i_cnt++)
							{
								if (gTrackData[i_trk2].s16GroupClstCnt < TRK_NUM_CLUSTER_MAX)
								{
									gClstData[gTrackData[i_trk1].s16GroupClstIdx[i_cnt]].s16GroupTrkIdx = i_trk2;

									gTrackData[i_trk2].s16GroupClstIdx[gTrackData[i_trk2].s16GroupClstCnt] = gTrackData[i_trk1].s16GroupClstIdx[i_cnt];
									gTrackData[i_trk2].s16GroupClstCnt++;
								}
							}

							gTrackData[i_trk2].u8Merging_Flag = 2;
							Trk_vInit(&gTrackData[i_trk1]);
						}
						else
						{
							for (i_cnt = 0; i_cnt < gTrackData[i_trk2].s16GroupClstCnt; i_cnt++)
							{
								if (gTrackData[i_trk1].s16GroupClstCnt < TRK_NUM_CLUSTER_MAX)
								{
									gClstData[gTrackData[i_trk2].s16GroupClstIdx[i_cnt]].s16GroupTrkIdx = i_trk1;

									gTrackData[i_trk1].s16GroupClstIdx[gTrackData[i_trk1].s16GroupClstCnt] = gTrackData[i_trk2].s16GroupClstIdx[i_cnt];
									gTrackData[i_trk1].s16GroupClstCnt++;
								}
							}

							gTrackData[i_trk1].u8Merging_Flag = 2;
							Trk_vInit(&gTrackData[i_trk2]);
						}
					}
					else
					{
						/* Do nothing here */
					}
				}
			}
		}
	}

}


static void Trk_vUpdateStatus(void)
{
	int16_t i_trk;
	int16_t i_clst;
	int16_t valid_trklet;
	uint8_t vobj_matching;

	for (i_trk = 0; i_trk < TRK_NUM_TRACK_MAX; i_trk++)
	{
		if (gTrackData[i_trk].Status != INVALID)
		{
			/* Update Age */
			gTrackData[i_trk].u16AliveAge = (gTrackData[i_trk].u16AliveAge < TRK_U16_MAX_NUM) ? gTrackData[i_trk].u16AliveAge + 1 : TRK_U16_MAX_NUM;
			gTrackData[i_trk].u16StatusAge = (gTrackData[i_trk].u16StatusAge < TRK_U16_MAX_NUM) ? gTrackData[i_trk].u16StatusAge + 1 : TRK_U16_MAX_NUM;

			valid_trklet = 0;
			for (i_clst = 0; i_clst < gTrackData[i_trk].s16GroupClstCnt; i_clst++)
			{
				valid_trklet |= ((gClstData[gTrackData[i_trk].s16GroupClstIdx[i_clst]].Status == UPDATED_TRACK)
							 || ((gClstData[gTrackData[i_trk].s16GroupClstIdx[i_clst]].Status == COASTED_TRACK)
							 && (gClstData[gTrackData[i_trk].s16GroupClstIdx[i_clst]].u16StatusAge <= TRK_UPDATE_COASTED_TRKLET_STAGEAGE_MAX)));
			}

#if TRK_SF_GEN_STATIONARY_OBJ_FROM_VOBJ_FLAG
			if ((gTrackData[i_trk].MovState == STATIONARY) && (gTrackData[i_trk].match_vision_obj_idx == -1))
			{
				Trk_vInit(&gTrackData[i_trk]);
				continue;
			}
#endif


#if	TRK_SENSOR_FUSION_UPDATE_FLAG
			/* Check Fusion state */
			if (gTrackData[i_trk].fusion_state == SF_FUSION_MOVING)
			{
				if (valid_trklet == 0)
				{
					gTrackData[i_trk].fusion_state = SF_VISION_ONLY;
				}
			}
			else
			{
				gTrackData[i_trk].fusion_state = SF_RADAR_ONLY;
			}
#endif

			/* Update Track Status */
			if (gTrackData[i_trk].Status == UPDATED_TRACK)
			{
				if ((valid_trklet == 0)
#if	TRK_SENSOR_FUSION_UPDATE_FLAG
					&& (gTrackData[i_trk].fusion_state == SF_RADAR_ONLY)
#endif
					)
				{
					gTrackData[i_trk].Status = COASTED_TRACK;
					gTrackData[i_trk].u16StatusAge = 1;
				}
			}
			else
			{
				if ((valid_trklet == 1)
#if	TRK_SENSOR_FUSION_UPDATE_FLAG
					|| (gTrackData[i_trk].fusion_state == SF_VISION_ONLY)
#endif
					)
				{
					gTrackData[i_trk].Status = UPDATED_TRACK;
					gTrackData[i_trk].u16StatusAge = 1;
				}
				else
				{
					if (gTrackData[i_trk].s16GroupClstCnt == 0)
					{
						Trk_vInit(&gTrackData[i_trk]);
					}
				}
			}
		}
	}

}