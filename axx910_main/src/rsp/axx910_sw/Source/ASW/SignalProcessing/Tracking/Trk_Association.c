/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Trk_Main.h"
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
static void Trk_vClusterGrouping(void);


/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Clst_vAssociation(void)
{
	int16_t i_mscl;
	int16_t i_clst;
	int16_t i_meas;
	int16_t NoisePt_AssoIdx;

	float32_t Expect_Trk_Rng_rate;	
	float32_t res_Xpos;
	float32_t res_Ypos;
	float32_t res_rangerate;
	float32_t gate_Xpos;
	float32_t gate_Ypos;
	float32_t Asso_Cost;
	float32_t Min_Cost;

	/* Associate MeasClst to ClstData */
	for (i_mscl = 0; i_mscl < gMsclCnt; i_mscl++)
	{
		if ((gMeasClst[i_mscl].State == VALID_CLST) &&
			(gMeasClst[i_mscl].s16AssoClstIdx == -1))
		{
			gMeasClst[i_mscl].f32AssoClstCost = TRK_INIT_ASSO_COST;

			for (i_clst = 0; i_clst < TRK_NUM_CLUSTER_MAX; i_clst++)
			{
				if ((gClstData[i_clst].Status != INVALID) &&
					((gClstData[i_clst].Status != NEW_TRACK) || ((gMeasClst[i_mscl].MovState != STATIONARY) && (gMeasClst[i_mscl].ReflectType != REFLECT_TYPE_WHEEL))) &&
					(gClstData[i_clst].s16AssoMeasClstCnt < TRK_NUM_MEAS_CLST_ASSOCIATION_MAX))
				{
					Expect_Trk_Rng_rate = NegRotateX(gClstData[i_clst].f32PredStateX[1] - gTrkEgoMotionInfo.f32VelX, gClstData[i_clst].f32PredStateY[1] - gTrkEgoMotionInfo.f32VelY, gMeasClst[i_mscl].AziAng.f32Mean);
					res_rangerate = gMeasClst[i_mscl].RangeRate_rdr.f32Mean - Expect_Trk_Rng_rate;

					res_Xpos = gMeasClst[i_mscl].Xpos.f32Mean - gClstData[i_clst].f32PredStateX[0];
					res_Ypos = gMeasClst[i_mscl].Ypos.f32Mean - gClstData[i_clst].f32PredStateY[0];

					gate_Xpos = _trk_min(_trk_max((gMeasClst[i_mscl].Xpos.f32StdDev + gClstData[i_clst].f32Std_Xpos) * CLST_ASSO_GATE_POS_SIGMA_FACTOR, 1.0f), 4.0f);
					gate_Ypos = _trk_min(_trk_max((gMeasClst[i_mscl].Ypos.f32StdDev + gClstData[i_clst].f32Std_Ypos) * CLST_ASSO_GATE_POS_SIGMA_FACTOR, 1.0f), 4.0f);
					
					if (((_sp_abs(res_rangerate) <= CLST_ASSO_GATE_RANGERATE) || (gMeasClst[i_mscl].ReflectType == REFLECT_TYPE_WHEEL)) &&
						 (_sp_abs(res_Xpos) <= gate_Xpos) &&
						 (_sp_abs(res_Ypos) <= gate_Ypos))
					{
						Asso_Cost = (_sp_abs(res_rangerate) / CLST_ASSO_GATE_RANGERATE) +
									(_sp_abs(res_Xpos) / gate_Xpos) +
									(_sp_abs(res_Ypos) / gate_Ypos);

						Asso_Cost *= (gClstData[i_clst].Status == NEW_TRACK) ? 10.0f : 1.0f;

						if (Asso_Cost < gMeasClst[i_mscl].f32AssoClstCost)
						{
							gMeasClst[i_mscl].f32AssoClstCost = Asso_Cost;

							if (gMeasClst[i_mscl].s16AssoClstIdx != -1)
							{
								gClstData[gMeasClst[i_mscl].s16AssoClstIdx].s16AssoMeasClstCnt--;
							}

							gMeasClst[i_mscl].s16AssoClstIdx = i_clst;
							gMeasClst[i_mscl].State = ASSO_CLST;
							
							gClstData[i_clst].s16AssoMeasClstIdx[gClstData[i_clst].s16AssoMeasClstCnt] = i_mscl;
							gClstData[i_clst].s16AssoMeasClstCnt++;
						}
					}
				}
			}
		}
	}

	/* Associate NoisePt to ClstData */
	for (i_meas = 0; i_meas < gMeasCnt; i_meas++)
	{
		if ((gMeasData[i_meas].Cluster_PtsStat == NOISE_PTS) && (gMeasData[i_meas].u8Cluster_visited == 1))
		{
			Min_Cost = TRK_INIT_ASSO_COST;
			NoisePt_AssoIdx = -1;

			for (i_clst = 0; i_clst < TRK_NUM_CLUSTER_MAX; i_clst++)
			{
				if (((gClstData[i_clst].Status == UPDATED_TRACK) || (gClstData[i_clst].Status == COASTED_TRACK)) &&
					 (gClstData[i_clst].s16AssoMeasNoisePtCnt < TRK_NUM_MEAS_NOISEPT_ASSOCIATION_MAX))
				{
					Expect_Trk_Rng_rate = NegRotateX(gClstData[i_clst].f32PredStateX[1] - gTrkEgoMotionInfo.f32VelX, gClstData[i_clst].f32PredStateY[1] - gTrkEgoMotionInfo.f32VelY, gMeasData[i_meas].f32AziAng);
					res_rangerate = gMeasData[i_meas].f32RangeRate_rdr - Expect_Trk_Rng_rate;

					res_Xpos = gMeasData[i_meas].f32PosX - gClstData[i_clst].f32PredStateX[0];
					res_Ypos = gMeasData[i_meas].f32PosY - gClstData[i_clst].f32PredStateY[0];

					gate_Xpos = _trk_min(_trk_max(gClstData[i_clst].f32Std_Xpos * CLST_ASSO_GATE_POS_SIGMA_FACTOR, 1.0f), 4.0f);
					gate_Ypos = _trk_min(_trk_max(gClstData[i_clst].f32Std_Ypos * CLST_ASSO_GATE_POS_SIGMA_FACTOR, 1.0f), 4.0f);
					
					if (((_sp_abs(res_rangerate) <= CLST_ASSO_GATE_RANGERATE) || (gMeasData[i_meas].ReflectType == REFLECT_TYPE_WHEEL)) &&
						 (_sp_abs(res_Xpos) <= gate_Xpos) &&
						 (_sp_abs(res_Ypos) <= gate_Ypos))
					{
						Asso_Cost = (_sp_abs(res_rangerate) / CLST_ASSO_GATE_RANGERATE) +
									(_sp_abs(res_Xpos) / gate_Xpos) +
									(_sp_abs(res_Ypos) / gate_Ypos);

						if (Asso_Cost < Min_Cost)
						{
							Min_Cost = Asso_Cost;
							NoisePt_AssoIdx = i_clst;
						}
					}
				}
			}

			if (NoisePt_AssoIdx != -1)
			{
				gClstData[NoisePt_AssoIdx].s16AssoMeasNoisePtIdx[gClstData[NoisePt_AssoIdx].s16AssoMeasNoisePtCnt] = i_meas;
				gClstData[NoisePt_AssoIdx].s16AssoMeasNoisePtCnt++;
			}
		}
	}

}


void Trk_vAssociation(void)
{
	Trk_vClusterGrouping();
}




/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
static void Trk_vClusterGrouping(void)
{
	int16_t i_trk;
	int16_t i_clst;
	int16_t clst_idx;
	float32_t trk_posX;
	float32_t trk_posY;
	float32_t clst_posX;
	float32_t clst_posY;
	int16_t prev_GroupClstCnt;
	float32_t grouping_cost;
	float32_t temp_cost;

	/* Check grouped cluster consistency */
	for (i_trk = 0; i_trk < TRK_NUM_TRACK_MAX; i_trk++)
	{
		if (gTrackData[i_trk].Status != INVALID) 
		{
			trk_posX = NegRotateX(gTrackData[i_trk].PredState.f32StateX[0], gTrackData[i_trk].PredState.f32StateY[0], gTrackData[i_trk].PredState.f32StateHeading[0]);
			trk_posY = NegRotateY(gTrackData[i_trk].PredState.f32StateX[0], gTrackData[i_trk].PredState.f32StateY[0], gTrackData[i_trk].PredState.f32StateHeading[0]);

			prev_GroupClstCnt = gTrackData[i_trk].s16GroupClstCnt;
			gTrackData[i_trk].s16GroupClstCnt = 0;

			for (i_clst = 0; i_clst < prev_GroupClstCnt; i_clst++)
			{
				clst_idx = gTrackData[i_trk].s16GroupClstIdx[i_clst];

				if ((gClstData[clst_idx].Status != INVALID) && (gClstData[clst_idx].s16GroupTrkIdx == i_trk))
				{
					clst_posX = NegRotateX(gClstData[clst_idx].f32UpdStateX[0], gClstData[clst_idx].f32UpdStateY[0], gTrackData[i_trk].PredState.f32StateHeading[0]);
					clst_posY = NegRotateY(gClstData[clst_idx].f32UpdStateX[0], gClstData[clst_idx].f32UpdStateY[0], gTrackData[i_trk].PredState.f32StateHeading[0]);

					if (((gTrackData[i_trk].s16GroupClstCnt == 0) && ((prev_GroupClstCnt - i_clst) == 1)) ||
						((_sp_abs(trk_posX - clst_posX) < ((gTrackData[i_trk].PredState.f32Length * 0.5f) + CLST_GROUP_KEEPING_GATE_LONG)) &&
						(_sp_abs(trk_posY - clst_posY) < ((gTrackData[i_trk].PredState.f32Width * 0.5f) + CLST_GROUP_KEEPING_GATE_LAT)) &&
						(_sp_abs(gTrackData[i_trk].PredState.f32StateX[1] - gClstData[clst_idx].f32UpdStateX[1]) < CLST_GROUP_KEEPING_VEL_X) &&
						(_sp_abs(gTrackData[i_trk].PredState.f32StateY[1] - gClstData[clst_idx].f32UpdStateY[1]) < CLST_GROUP_KEEPING_VEL_Y)))
					{
						gTrackData[i_trk].s16GroupClstIdx[gTrackData[i_trk].s16GroupClstCnt] = clst_idx;
						gTrackData[i_trk].s16GroupClstCnt++;

						gClstData[clst_idx].s16GroupTrkIdx = i_trk;
						gClstData[clst_idx].s16GroupInconsistentCnt = 0;
					}
					else
					{
						gClstData[clst_idx].s16GroupInconsistentCnt++;

						if (gClstData[clst_idx].s16GroupInconsistentCnt < CLST_GROUP_INCONSISTENCY_CNT)
						{
							gTrackData[i_trk].s16GroupClstIdx[gTrackData[i_trk].s16GroupClstCnt] = clst_idx;
							gTrackData[i_trk].s16GroupClstCnt++;

							gClstData[clst_idx].s16GroupTrkIdx = i_trk;
						}
						else
						{
							/* Break Trk_Trklet Grouping */
							gTrackData[i_trk].s16GroupClstIdx[i_clst] = -1;
							gClstData[clst_idx].s16GroupTrkIdx = -1;
						}
					}
				}
				else
				{
					/* Break Trk_Trklet Grouping */
					gTrackData[i_trk].s16GroupClstIdx[i_clst] = -1;
					gClstData[clst_idx].s16GroupTrkIdx = -1;
				}
			}
		}
	}

	/* Group ungrouped tracklet */
	for (i_clst = 0; i_clst < TRK_NUM_CLUSTER_MAX; i_clst++)
	{
		if ((gClstData[i_clst].Status == UPDATED_TRACK) &&
			(gClstData[i_clst].s16GroupTrkIdx == -1))
		{
			grouping_cost = 100.0f;

			for (i_trk = 0; i_trk < TRK_NUM_TRACK_MAX; i_trk++)
			{
				if ((gTrackData[i_trk].Status != INVALID) && (gTrackData[i_trk].s16GroupClstCnt < TRK_NUM_GROUP_CLST_MAX))
				{
					trk_posX = NegRotateX(gTrackData[i_trk].PredState.f32StateX[0], gTrackData[i_trk].PredState.f32StateY[0], gTrackData[i_trk].PredState.f32StateHeading[0]);
					trk_posY = NegRotateY(gTrackData[i_trk].PredState.f32StateX[0], gTrackData[i_trk].PredState.f32StateY[0], gTrackData[i_trk].PredState.f32StateHeading[0]);

					clst_posX = NegRotateX(gClstData[i_clst].f32UpdStateX[0], gClstData[i_clst].f32UpdStateY[0], gTrackData[i_trk].PredState.f32StateHeading[0]);
					clst_posY = NegRotateY(gClstData[i_clst].f32UpdStateX[0], gClstData[i_clst].f32UpdStateY[0], gTrackData[i_trk].PredState.f32StateHeading[0]);

					if ((_sp_abs(trk_posX - clst_posX) < ((gTrackData[i_trk].PredState.f32Length * 0.5f) + CLST_GROUP_NEW_GATE_LONG))
						&& (_sp_abs(trk_posY - clst_posY) < ((gTrackData[i_trk].PredState.f32Width * 0.5f) + CLST_GROUP_NEW_GATE_LAT))
						&& (_sp_abs(gTrackData[i_trk].PredState.f32StateX[1] - gClstData[i_clst].f32UpdStateX[1]) < CLST_GROUP_NEW_VEL_X)
						&& (_sp_abs(gTrackData[i_trk].PredState.f32StateY[1] - gClstData[i_clst].f32UpdStateY[1]) < CLST_GROUP_NEW_VEL_Y))
					{
						temp_cost = _sp_abs(trk_posX - clst_posX) / (gTrackData[i_trk].PredState.f32Length * 0.5f) + _sp_abs(trk_posY - clst_posY) / (gTrackData[i_trk].PredState.f32Width * 0.5f) + _sp_hypotf(gTrackData[i_trk].PredState.f32StateX[1] - gClstData[i_clst].f32UpdStateX[1], gTrackData[i_trk].PredState.f32StateY[1] - gClstData[i_clst].f32UpdStateY[1]);

						if (temp_cost < grouping_cost)
						{
							grouping_cost = temp_cost;

							if (gClstData[i_clst].s16GroupTrkIdx != -1)
							{
								gTrackData[gClstData[i_clst].s16GroupTrkIdx].s16GroupClstCnt--;
							}

							gTrackData[i_trk].s16GroupClstIdx[gTrackData[i_trk].s16GroupClstCnt] = i_clst;
							gTrackData[i_trk].s16GroupClstCnt++;

							gClstData[i_clst].s16GroupTrkIdx = i_trk;
							gClstData[i_clst].s16GroupInconsistentCnt = 0;
						}
					}
				}
			}
		}
	}

}