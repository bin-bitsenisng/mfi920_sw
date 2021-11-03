/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Trk_Freespace.h"

/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/
// Map Size Info
#define ANGLE_NUM_MIDDLE 90U
#define ANGLE_NUM_LONG 20U
#define GRID_NUM_MIDDLE 120U // 120m, Range Resol = 1m;
#define GRID_NUM_LONG 36U //  300m, Range Resol = 5m;
#define MAX_RANGE_LONG 300.0f
#define MAX_RANGE_MIDDLE 120.0f
#define MAP_MODE_NUM 2 // 0 : middle , 1: long

typedef enum
{
	GRIDSTATE_OCC_Free = 0,
	GRIDSTATE_OCC_STATIC = 1,
	GRIDSTATE_OCC_MOVING = 2

} TrkGridMovState_t;

typedef struct
{
	int32_t nAngGridNum;
	int32_t nRangeGridNum;
	int32_t nMaxMeasNuminGrid;
	float32_t fAngStart;
	float32_t fAngRes;
	float32_t fRangeRes;
	float32_t fRangeMax;
	
} MapPara_t;

typedef struct
{
	char cMapState[ANGLE_NUM_MIDDLE][GRID_NUM_MIDDLE];
	char cMoveState[ANGLE_NUM_MIDDLE][GRID_NUM_MIDDLE];
	uint16_t nMeasNum[ANGLE_NUM_MIDDLE][GRID_NUM_MIDDLE];
	float32_t fMaxSNRComp[ANGLE_NUM_MIDDLE][GRID_NUM_MIDDLE];
	float32_t fBelief[ANGLE_NUM_MIDDLE][GRID_NUM_MIDDLE];

} MapInfo_t;


MapPara_t tMapParaSet[MAP_MODE_NUM]; // [0] : middle, [1] : Long

// Occ Map data
static MapInfo_t tMapInfoCurrent[MAP_MODE_NUM];// [0] : middle, [1] : Long
static MapInfo_t tMapInfoPrev[MAP_MODE_NUM]; // [0] : middle, [1] : Long

// Inv Sensor model para
static const float32_t l0 = -0.1f;
//static const float32_t locc = 0.5f;
static const float32_t lfree = -0.3f;
static const float32_t lMax = 2.0f;
static const float32_t lmin = -0.7f;
static const float32_t lTh = 0.4f;
static const float32_t alpha = 1.0f; // angle para (deg)
static const float32_t beta = 1.0f; // range para (m)

// Mapping param
static const float32_t fSNRMAX = 50.0f;
static const float32_t fSNRMIN = 0.0f;
static const float32_t fSNRRangeBiasSlope = 0.05f;
static float32_t fSNRModeBias[3]; //0,1,2,3: LR, MR, SR, RM


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/
float32_t fFreeSpaceRange[90]; // Free sapce output

/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/

static void Trk_vMapCurMeasInfo(void);
static void Trk_vUpdateGridMap(void);
static float32_t Trk_vGetPrevbelief(int AIdxIn, int RidxIn, int ModetypeIn);
static void Trk_vComputeFreeSpace(void);
static int16_t Trk_vCheckIdxBound(int AIdx, int RIdx, int type);
static void Trk_vAddBeliefNear(int AIdx, int Ridx, int type, float fProb);

#ifdef TRK_SIMULATION_MODE
	float32_t freespaceSimout[90];
	static void Trk_vFreeSimout();
#endif

/**************************************************************************************
* ------------------------------   global functions------------------------------- *
**************************************************************************************/
void Trk_vProcessFreeSpace(void)
{
	Trk_vMapCurMeasInfo();
	Trk_vUpdateGridMap();
	Trk_vComputeFreeSpace();

#ifdef TRK_SIMULATION_MODE
	Trk_vFreeSimout();
#endif

}

void Trk_vInitOcc(void)
{
	memset(&tMapInfoPrev[0], 0, sizeof(tMapInfoPrev));
	memset(&tMapInfoCurrent[0], 0, sizeof(tMapInfoCurrent));

	// para middle, long
	tMapParaSet[0].fAngRes = 1.0f;
	tMapParaSet[0].fAngStart = 45.0f;
	tMapParaSet[0].fRangeRes = 1.0f;
	tMapParaSet[0].fRangeMax = 120.0f;
	tMapParaSet[0].nAngGridNum = ANGLE_NUM_MIDDLE;
	tMapParaSet[0].nRangeGridNum = GRID_NUM_MIDDLE;
	tMapParaSet[0].nMaxMeasNuminGrid = 12;
		
	tMapParaSet[1].fAngRes = 1.0f;
	tMapParaSet[1].fAngStart = 10.0f;
	tMapParaSet[1].fRangeRes = 5.0f;
	tMapParaSet[1].fRangeMax = 300.0f;
	tMapParaSet[1].nAngGridNum = ANGLE_NUM_LONG;
	tMapParaSet[1].nRangeGridNum = GRID_NUM_LONG;
	tMapParaSet[1].nMaxMeasNuminGrid = 20;

	fSNRModeBias[0] = 10.0f;
	fSNRModeBias[1] = 5.0f;
	fSNRModeBias[2] = 0.0f;
	fSNRModeBias[3] = 10.0f;
}

/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
static void Trk_vMapCurMeasInfo(void)
{
	int32_t nMode; // 0: middle, 1: long
	int32_t AngIdx;
	int32_t RIdx;
	float32_t fSNRComp;

	memcpy(&tMapInfoPrev[0], &tMapInfoCurrent[0], sizeof(tMapInfoPrev));
	memset(&tMapInfoCurrent[0], 0, sizeof(tMapInfoCurrent));

	for (int16_t nMeasIdx = 0; nMeasIdx < gMeasCnt; nMeasIdx++)
	{
		if (_sp_abs(gMeasData[nMeasIdx].f32PosZ) > 3.0f )
		{
			continue;
		}

		// Find Map Idx
		if (gMeasData[nMeasIdx].f32Range_rdr < tMapParaSet[0].fRangeMax)
		{
			AngIdx = (int)(-1.0f * gMeasData[nMeasIdx].f32AziAng + tMapParaSet[0].fAngStart);
			RIdx = (int)(gMeasData[nMeasIdx].f32Range_rdr / tMapParaSet[0].fRangeRes);
			nMode = 0;
		}
		else
		{
			AngIdx = (int)(-1.0f * gMeasData[nMeasIdx].f32AziAng + tMapParaSet[1].fAngStart);
			RIdx = (int)((gMeasData[nMeasIdx].f32Range_rdr - tMapParaSet[0].fRangeMax) / tMapParaSet[1].fRangeRes);
			nMode = 1;
		}

		fSNRComp = fSNRRangeBiasSlope * gMeasData[nMeasIdx].f32Range_rdr + gMeasData[nMeasIdx].f32Pow_dB + fSNRModeBias[gMeasData[nMeasIdx].u8ModType];

		// 
		if (1 == Trk_vCheckIdxBound(AngIdx, RIdx, nMode))
		{
			if (tMapInfoCurrent[nMode].fMaxSNRComp[AngIdx][RIdx] < fSNRComp)
			{
				tMapInfoCurrent[nMode].fMaxSNRComp[AngIdx][RIdx] = fSNRComp;
			}

			if (tMapInfoCurrent[nMode].nMeasNum[AngIdx][RIdx] < tMapParaSet[nMode].nMaxMeasNuminGrid)
			{
				tMapInfoCurrent[nMode].nMeasNum[AngIdx][RIdx] += 1;
			}

			if ((gMeasData[nMeasIdx].MovState == PRECEDING) 
				|| (gMeasData[nMeasIdx].MovState == ONCOMING))
			{
				tMapInfoCurrent[nMode].cMoveState[AngIdx][RIdx] = GRIDSTATE_OCC_MOVING; 
			}
			else
			{
				tMapInfoCurrent[nMode].cMoveState[AngIdx][RIdx] = GRIDSTATE_OCC_STATIC;
			}
		}
	}
	
}



static void Trk_vUpdateGridMap(void)
{	
	float32_t fprobCurrent;
	float32_t fProbPrev;
	   
	for (int nMode = 0; nMode < MAP_MODE_NUM; nMode++)
	{
		for (int16_t nAngIdx = 0; nAngIdx < tMapParaSet[nMode].nAngGridNum; nAngIdx++)
		{
			for (int16_t nRIdx = 0; nRIdx < tMapParaSet[nMode].nRangeGridNum; nRIdx++)
			{
				// Calc current belief
				if ((tMapInfoCurrent[nMode].nMeasNum[nAngIdx][nRIdx] == 0) ||
					(tMapInfoCurrent[nMode].fMaxSNRComp[nAngIdx][nRIdx] < fSNRMIN))
				{
					fprobCurrent = lfree;
				}
				else
				{
					// pob using Max SNR 
					fprobCurrent = _sp_min(tMapInfoCurrent[nMode].fMaxSNRComp[nAngIdx][nRIdx] / fSNRMAX, 1.0f);

					// prob using Density
					fprobCurrent = _sp_max(fprobCurrent, (float)(tMapInfoCurrent[nMode].nMeasNum[nAngIdx][nRIdx] / tMapParaSet[nMode].nMaxMeasNuminGrid));
				}

				if (tMapInfoCurrent[nMode].cMoveState[nAngIdx][nRIdx] == GRIDSTATE_OCC_MOVING)
				{
					tMapInfoCurrent[nMode].fBelief[nAngIdx][nRIdx] = l0;
					
					if ((1 <= nAngIdx) && (nAngIdx < tMapParaSet[nMode].nAngGridNum - 2))
					{
						tMapInfoCurrent[nMode].cMoveState[nAngIdx - 1][nRIdx] = GRIDSTATE_OCC_STATIC;
						tMapInfoCurrent[nMode].cMoveState[nAngIdx + 1][nRIdx] = GRIDSTATE_OCC_STATIC;
					}
				}
				else
				{
					if (0 == tMapInfoCurrent[nMode].fBelief[nAngIdx][nRIdx])
					{
						tMapInfoCurrent[nMode].fBelief[nAngIdx][nRIdx] = fprobCurrent;
					}
					else
					{
						tMapInfoCurrent[nMode].fBelief[nAngIdx][nRIdx] = _sp_max(tMapInfoCurrent[nMode].fBelief[nAngIdx][nRIdx], fprobCurrent);
					}
				}

				if (lfree != fprobCurrent)					
				{
					Trk_vAddBeliefNear(nAngIdx, nRIdx, nMode, fprobCurrent);
				}

				fProbPrev = Trk_vGetPrevbelief(nAngIdx, nRIdx, nMode);
				
				tMapInfoCurrent[nMode].fBelief[nAngIdx][nRIdx] += fProbPrev;
				tMapInfoCurrent[nMode].fBelief[nAngIdx][nRIdx] = _sp_bound(tMapInfoCurrent[nMode].fBelief[nAngIdx][nRIdx], lmin, lMax);

			}
		}
	}
}


static void Trk_vComputeFreeSpace(void)
{
	float32_t fMinRange;
	
	// Occ Decision 
	for (int nMode = 0; nMode < MAP_MODE_NUM; nMode++)
	{
		for (int16_t nAngIdx = 0; nAngIdx < tMapParaSet[nMode].nAngGridNum; nAngIdx++)
		{
			for (int16_t nRIdx = 0; nRIdx < tMapParaSet[nMode].nRangeGridNum; nRIdx++)
			{
				if ((tMapInfoCurrent[nMode].fBelief[nAngIdx][nRIdx] > lTh)
					|| (tMapInfoCurrent[nMode].cMoveState[nAngIdx][nRIdx] == GRIDSTATE_OCC_MOVING))
				{
					tMapInfoCurrent[nMode].cMapState[nAngIdx][nRIdx] = 1;

				}
				else
				{
					tMapInfoCurrent[nMode].cMapState[nAngIdx][nRIdx] = 0;
				}
			}
		}
	}

	// Free space decision
	for (int16_t nAngIdx = 0; nAngIdx < tMapParaSet[0].nAngGridNum; nAngIdx++)
	{
		fMinRange = tMapParaSet[0].fRangeMax;

		// middle
		for (int16_t nRIdx = 0; nRIdx < tMapParaSet[0].nRangeGridNum; nRIdx++)
		{
			if (1 == tMapInfoCurrent[0].cMapState[nAngIdx][nRIdx])
			{
				fMinRange = nRIdx * tMapParaSet[0].fRangeRes;
 				break;
			}
		}
		
		// long
		if ((tMapParaSet[0].fAngStart - tMapParaSet[1].fAngStart <= nAngIdx) 
			&& (nAngIdx < tMapParaSet[0].fAngStart + tMapParaSet[1].fAngStart)
			&& (fMinRange == tMapParaSet[0].fRangeMax))
		{
			fMinRange = tMapParaSet[1].fRangeMax;
			int16_t nAngIdxLong;
			nAngIdxLong = nAngIdx - (int)(tMapParaSet[0].fAngStart - tMapParaSet[1].fAngStart);

			for (int16_t nRIdx = 0; nRIdx < tMapParaSet[1].nRangeGridNum; nRIdx++)
			{
				if (1 == tMapInfoCurrent[1].cMapState[nAngIdxLong][nRIdx])
				{
					fMinRange = nRIdx * tMapParaSet[1].fRangeRes + tMapParaSet[0].fRangeMax;
					break;
				}
			}
			
		}

		fFreeSpaceRange[nAngIdx] = fMinRange;
	}

	// post processing
	for (int16_t nAngIdx = 1; nAngIdx < tMapParaSet[0].nAngGridNum - 1; nAngIdx++)
	{
		if ((tMapParaSet[0].fAngStart - tMapParaSet[1].fAngStart <= nAngIdx)
			&& (nAngIdx < tMapParaSet[0].fAngStart + tMapParaSet[1].fAngStart))
		{
			fMinRange = tMapParaSet[1].fRangeMax;
		}
		else
		{
			fMinRange = tMapParaSet[0].fRangeMax;
		}

		if ((fFreeSpaceRange[nAngIdx - 1] != fMinRange) &&
			(fFreeSpaceRange[nAngIdx + 1] != fMinRange) &&
			(fFreeSpaceRange[nAngIdx] == fMinRange))
		{
			fFreeSpaceRange[nAngIdx] = (fFreeSpaceRange[nAngIdx - 1] + fFreeSpaceRange[nAngIdx + 1]) / 2.0f;
			fFreeSpaceRange[nAngIdx] = _sp_min(fFreeSpaceRange[nAngIdx], fMinRange);
		}
	}

	// 

	fMinRange = tMapParaSet[0].fRangeMax;

	for (int16_t nAngIdx = 0; nAngIdx < 5; nAngIdx++)
	{
		if (fMinRange != fFreeSpaceRange[nAngIdx])
		{
			for (int16_t nAngIdx2 = 0; nAngIdx2 <= nAngIdx; nAngIdx2++)
			{
				fFreeSpaceRange[nAngIdx2] = fFreeSpaceRange[nAngIdx];
			}

			break;
		}
	}

	for (int16_t nAngIdx = tMapParaSet[0].nAngGridNum - 1; nAngIdx > tMapParaSet[0].nAngGridNum - 1- 5; nAngIdx--)
	{
		if (fMinRange != fFreeSpaceRange[nAngIdx])
		{
			for (int16_t nAngIdx2 = tMapParaSet[0].nAngGridNum - 1; nAngIdx2 > nAngIdx; nAngIdx2--)
			{
				fFreeSpaceRange[nAngIdx2] = fFreeSpaceRange[nAngIdx];
			}

			break;
		}
	}


}




float32_t Trk_vGetPrevbelief(int AIdxIn, int RidxIn, int ModetypeIn)
{
	float32_t fRet = 0.0f;

	// find prev map 		
	float32_t fRange;
	float32_t ftheta;

	float32_t fPosv[2];
	float32_t fPosIn[2];
	float32_t RotMat[2][2];
	float32_t fRotPos[2];
	float32_t fYawv;

	float32_t fRangeIn;
	float32_t fAngIn;

	int nModeTemp;
	int AngIdxTemp;
	int RIdxTemp;

	// ego motion
	fPosv[0] = gTrkEgoMotionInfo.f32VelX * gTrkCycleTime;
	fPosv[1] = gTrkEgoMotionInfo.f32VelY * gTrkCycleTime;

	fYawv = gTrkEgoMotionInfo.f32DeltaYaw_deg;

	RotMat[0][0] = _sp_cosdf(fYawv);
	RotMat[0][1] = -1.0f * _sp_sindf(fYawv);
	RotMat[1][0] = _sp_sindf(fYawv);
	RotMat[1][1] = _sp_cosdf(fYawv);

	AngIdxTemp = -1;
	RIdxTemp = -1;

	fAngIn = (-1.0f * AIdxIn * tMapParaSet[ModetypeIn].fAngRes) + tMapParaSet[ModetypeIn].fAngStart - (tMapParaSet[ModetypeIn].fAngRes / 2.0f);
	fRangeIn = RidxIn * tMapParaSet[ModetypeIn].fRangeRes + (tMapParaSet[ModetypeIn].fRangeRes / 2.0f);

	if (1 == ModetypeIn)
	{
		fRangeIn = fRangeIn + tMapParaSet[0].fRangeMax;
	}

	fPosIn[0] = fRangeIn * _sp_cosdf(fAngIn);
	fPosIn[1] = fRangeIn * _sp_sindf(fAngIn);

	fRotPos[0] = RotMat[0][0] * fPosIn[0] + RotMat[0][1] * fPosIn[1] + fPosv[0];
	fRotPos[1] = RotMat[1][0] * fPosIn[0] + RotMat[1][1] * fPosIn[1] + fPosv[1];

	fRange = sqrtf(fRotPos[0] * fRotPos[0] + fRotPos[1] * fRotPos[1]);
	ftheta = (atan2f(fRotPos[0] , -1.0f * fRotPos[1]) * SP_RAD2DEG ) - 90.0f;	

	if (fRange < tMapParaSet[1].fRangeMax)
	{
		if (fRange < tMapParaSet[0].fRangeMax)
		{
			AngIdxTemp = (int)(-1.0f * ftheta + tMapParaSet[0].fAngStart);
			RIdxTemp = (int)(fRange / tMapParaSet[0].fRangeRes);
			nModeTemp = 0;

		}
		else
		{
			AngIdxTemp = (int)(-1.0f * ftheta + tMapParaSet[1].fAngStart);
			RIdxTemp = (int)((fRange - tMapParaSet[0].fRangeMax) / tMapParaSet[1].fRangeRes);
			nModeTemp = 1;
		}
	}
	else
	{
		nModeTemp = -1;
	}
	

	if ((-1 != nModeTemp) && (1 == Trk_vCheckIdxBound(AngIdxTemp, RIdxTemp, nModeTemp)))
	{
		fRet = tMapInfoPrev[nModeTemp].fBelief[AngIdxTemp][RIdxTemp];
	}

	return fRet;
}



int16_t Trk_vCheckIdxBound(int AIdx, int RIdx, int type)
{
	int16_t nRet = -1;

	// middle
	if ((0 == type) || (1 == type))
	{
		if ((0 <= AIdx) && (AIdx < tMapParaSet[type].nAngGridNum)
			&& (0 <= RIdx) && (RIdx < tMapParaSet[type].nRangeGridNum))
		{
			nRet = 1;
		}
	}

	return nRet;
}


void Trk_vAddBeliefNear(int AIdxIn, int RidxIn, int ModetypeIn, float fProbIn)
{

	int nAIdx;
	int nRIdx;
	int nAngNearNum; 
	int nRNearNum; 
	int nScaleInd;

	float32_t fScale[2];
	float32_t fProb;
	float32_t fAng;

	fScale[0] = 0.6f;
	fScale[1] = 0.3f;
	
	if (1 == ModetypeIn)
	{
		nAngNearNum = 1;
		nRNearNum = 1;
	}
	else
	{
		nAngNearNum = 1;
		fAng = (-1.0f * AIdxIn * tMapParaSet[0].fAngRes);

		if (_sp_abs(fAng) > 30.0f)
		{
			nAngNearNum = 2;
		}

		nRNearNum = 1;

		if ((RidxIn * tMapParaSet[ModetypeIn].fRangeRes) > 50.0f)
		{
			nRNearNum = 2;
		}

	}

	for (int32_t nIndBias = -nAngNearNum * 1; nIndBias <= nAngNearNum; nIndBias++)
	{
		for (int16_t nRIndBias = -nRNearNum * 1; nRIndBias <= nRNearNum; nRIndBias++)
		{
			if ((nIndBias == 0) && (0 == nRIndBias))
			{
				continue;
			}

			nScaleInd = _sp_max(_sp_abs(nIndBias), _sp_abs(nRIndBias)) - 1;
			fProb = fProbIn * fScale[nScaleInd];

			nAIdx = nIndBias + AIdxIn;
			nRIdx = nRIndBias + RidxIn;

			if ((1 == Trk_vCheckIdxBound(nAIdx, nRIdx, ModetypeIn) &&
				tMapInfoCurrent[ModetypeIn].fBelief[nAIdx][nRIdx] < fProb))
			{
				tMapInfoCurrent[ModetypeIn].fBelief[nAIdx][nRIdx] = fProb;

			}
		}
	}
}

static void Trk_vFreeSimout(void)
{

	memcpy(&freespaceSimout[0], &fFreeSpaceRange[0], sizeof(freespaceSimout));	

}
