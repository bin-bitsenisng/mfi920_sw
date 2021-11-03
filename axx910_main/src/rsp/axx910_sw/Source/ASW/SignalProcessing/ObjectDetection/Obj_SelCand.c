/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Obj_Main.h"
#include "Obj_SelCand.h"


/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
#ifdef CUDA_ACC
static void Obj_vSelectCandidate(Cuda_PeakData_t* PeakData, CalcObjData_t* ObjData);
#else
static void Obj_vSelectCandidate(PeakData_t* PeakData, CalcObjData_t* ObjData);
#endif

static void Obj_vSelectCandidate_Ref(RefPeakData_t* PeakData, RefCalcObjData_t* ObjData);

/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Obj_vSelCand(void)
{
	Obj_vSelectCandidate_Ref(&gRM_PeakData, &gRM_ObjData);
	Obj_vSelectCandidate(&gLR_PeakData, &gLR_ObjData);
	Obj_vSelectCandidate(&gMR_PeakData, &gMR_ObjData);
	Obj_vSelectCandidate(&gSR_PeakData, &gSR_ObjData);
}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
#ifdef CUDA_ACC
static void Obj_vSelectCandidate(Cuda_PeakData_t* PeakData, CalcObjData_t* ObjData)
#else
static void Obj_vSelectCandidate(PeakData_t* PeakData, CalcObjData_t* ObjData)
#endif
{
	int16_t i, k, j;
	int16_t obj_cnt;

	obj_cnt = 0;
	for (i = 0; i < PeakData->s16PhCnt; i++)
	{
		_sp_cnt_break(obj_cnt, OBJ_NUM_CANDIDATE_OBJ*OBJ_AE_NUM_TARGET_MAX);

		for (k = 0; k < 1; k++)
		{

			for (j = 0; j < PeakData->s16AngCnt[i][k]; j++)
			{
				_sp_cnt_break(obj_cnt, OBJ_NUM_CANDIDATE_OBJ*OBJ_AE_NUM_TARGET_MAX);

#ifdef WIN32
				ObjData->ObjData[obj_cnt].s16PeakIdx = i;
				ObjData->ObjData[obj_cnt].s16MatRefPeakIdx = PeakData->s16MatRefPeakIdx[i];
				ObjData->ObjData[obj_cnt].s16HarmIdx = k;
#endif


				ObjData->ObjData[obj_cnt].eGFType = AMBIGUOUS_VEL;
				ObjData->ObjData[obj_cnt].s16HarmonicCnt = PeakData->s16HarmonicCnt[i];

				ObjData->ObjData[obj_cnt].rdu16FreqIdx.R = PeakData->rdu16phFreqIdx[i].R;
				ObjData->ObjData[obj_cnt].rdu16FreqIdx.D = PeakData->rdu16phFreqIdx[i].D;
				ObjData->ObjData[obj_cnt].f32Range = PeakData->f32PhRange[i][0];
				ObjData->ObjData[obj_cnt].f32Velocity = PeakData->f32PhVelocity[i][0];

				ObjData->ObjData[obj_cnt].f32AziAngle = PeakData->f32AziAngle[i][k][j];
				ObjData->ObjData[obj_cnt].f32EleAngle = PeakData->f32EleAngle[i][k][j];
				ObjData->ObjData[obj_cnt].f32Power = PeakData->f32Power[i][k][j];

				ObjData->ObjData[obj_cnt].f32PreAziAngle = PeakData->f32PhPreAziAngle[i][0];
				ObjData->ObjData[obj_cnt].f32PrePow = PeakData->f32PhPrePower[i][0];
				ObjData->ObjData[obj_cnt].f32SllPowdB = 20.0f*_sp_log10f(PeakData->f32PhSllPow[i] + 0.001f);

				ObjData->ObjData[obj_cnt].s16TrackFlag = PeakData->s16TrackFlag[i][k][j];

				obj_cnt++;
			}
		}
	}
	ObjData->s16ObjCnt = obj_cnt;
}


static void Obj_vSelectCandidate_Ref(RefPeakData_t* PeakData, RefCalcObjData_t* ObjData)
{
	int16_t i, j, k;
	int16_t obj_cnt;

	obj_cnt = 0;
	for (i = 0; i < PeakData->s16PeakCnt; i++)
	{
		_sp_cnt_break(obj_cnt, OBJ_NUM_RM_CANDIDATE_OBJ);

		for (j = 0; j < PeakData->s16AngCnt[i]; j++)
		{
			_sp_cnt_break(obj_cnt, OBJ_NUM_RM_CANDIDATE_OBJ);
			ObjData->ObjData[obj_cnt].eGFType = NOT_GHOST;
			ObjData->ObjData[obj_cnt].f32AziAngle = PeakData->f32AziAngle[i][j];
			ObjData->ObjData[obj_cnt].f32Power = PeakData->f32Power[i][j];

			ObjData->ObjData[obj_cnt].f32Range = PeakData->f32Range[i];
			ObjData->ObjData[obj_cnt].f32Velocity = PeakData->f32Velocity[i];
			ObjData->ObjData[obj_cnt].f32EleAngle = PeakData->f32EleAngle[i];
			ObjData->ObjData[obj_cnt].rdu16FreqIdx.R = PeakData->rdu16FreqIdx[i].R;
			ObjData->ObjData[obj_cnt].rdu16FreqIdx.D = PeakData->rdu16FreqIdx[i].D;


			ObjData->ObjData[obj_cnt].rdu16FreqIdx.R = PeakData->rdu16FreqIdx[i].R;
			ObjData->ObjData[obj_cnt].rdu16FreqIdx.D = PeakData->rdu16FreqIdx[i].D;

			ObjData->ObjData[obj_cnt].s16TrackFlag = 1;
#ifdef WIN32
			ObjData->ObjData[obj_cnt].s16PeakIdx = i;
#endif
			obj_cnt++;
		}
	}
	ObjData->s16ObjCnt = obj_cnt;

}