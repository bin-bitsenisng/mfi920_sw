/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Obj_Main.h"
#include "Obj_Output.h"


/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
static void Obj_vOutProcessing(CalcObjData_t* ObjData, MultiMod_t CurMod);
static void Obj_vOutProcessing_Ref(RefCalcObjData_t* ObjData, MultiMod_t CurMod);


/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Obj_vOut(void)
{
	gObjOutCnt = 0;
#ifdef WIN32
	gFilteredObjCnt = 0;
	int16_t temp_obj_cnt = 0;
#endif

	Obj_vOutProcessing(&gLR_ObjData, LR_MOD);

#ifdef WIN32
	printf("[RM]	msmt cnt : %d \n", gRM_ObjData.s16ObjCnt);
	printf("==============\n");
	printf("[LR]	msmt cnt : %d \n", gObjOutCnt);
	temp_obj_cnt = gObjOutCnt;
#endif 

	Obj_vOutProcessing(&gMR_ObjData, MR_MOD);

#ifdef  WIN32
	printf("[MR]	msmt cnt : %d \n", (gObjOutCnt - temp_obj_cnt));
	temp_obj_cnt = gObjOutCnt;
#endif 

	Obj_vOutProcessing(&gSR_ObjData, SR_MOD);
	Obj_vOutProcessing_Ref(&gRM_ObjData, RM_MOD);

#ifdef  WIN32
	printf("[SR]	msmt cnt : %d \n", (gObjOutCnt - temp_obj_cnt));
	printf("==============\n");

	printf("[Filtered] msmt cnt : %d\n", gFilteredObjCnt);
	printf("====================\n");

#endif 

}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
static void Obj_vOutProcessing(CalcObjData_t* ObjData, MultiMod_t CurMod)
{
	int16_t i, m, j;
	for (i = 0; i < ObjData->s16ObjCnt; i++)
	{
		_sp_cnt_break(gObjOutCnt, OBJ_NUM_OBJECT_MAX)
			if (ObjData->ObjData[i].eGFType == NOT_GHOST)
			{
#ifdef WIN32
				gObjectOut[gObjOutCnt].eGFType = NOT_GHOST;
				gObjectOut[gObjOutCnt].s16PeakIdx = ObjData->ObjData[i].s16PeakIdx;
				gObjectOut[gObjOutCnt].rdu16FreqIdx.R = ObjData->ObjData[i].rdu16FreqIdx.R;
				gObjectOut[gObjOutCnt].rdu16FreqIdx.D = ObjData->ObjData[i].rdu16FreqIdx.D;
				gObjectOut[gObjOutCnt].s16HarmIdx = ObjData->ObjData[i].s16HarmIdx;
				gObjectOut[gObjOutCnt].s16MatRefPeakIdx = ObjData->ObjData[i].s16MatRefPeakIdx;

				gObjectOut[gObjOutCnt].f32PreAziAngle = ObjData->ObjData[i].f32PreAziAngle;
				gObjectOut[gObjOutCnt].f32PrePow = ObjData->ObjData[i].f32PrePow;
				gObjectOut[gObjOutCnt].f32SllPowdB = ObjData->ObjData[i].f32SllPowdB;

#endif
				gObjectOut[gObjOutCnt].eModType = CurMod;
				gObjectOut[gObjOutCnt].f32Range_m = ObjData->ObjData[i].f32Range;
				gObjectOut[gObjOutCnt].f32Velocity_mps = ObjData->ObjData[i].f32Velocity;
				gObjectOut[gObjOutCnt].f32AziAng_deg = gRadarInstInfo.f32Reverse * ObjData->ObjData[i].f32AziAngle;
				gObjectOut[gObjOutCnt].f32EleAng_deg = gRadarInstInfo.f32Reverse * ObjData->ObjData[i].f32EleAngle + 3.0f;
				
				gObjectOut[gObjOutCnt].f32Power_dB = ObjData->ObjData[i].f32Power;
				gObjectOut[gObjOutCnt].s16TrackFlag = ObjData->ObjData[i].s16TrackFlag;

				gObjOutCnt++;
			}
#ifdef WIN32
			else
			{
				gFilteredObj[gFilteredObjCnt].eGFType = ObjData->ObjData[i].eGFType;
				gFilteredObj[gFilteredObjCnt].s16PeakIdx = ObjData->ObjData[i].s16PeakIdx;
				gFilteredObj[gFilteredObjCnt].rdu16FreqIdx.R = ObjData->ObjData[i].rdu16FreqIdx.R;
				gFilteredObj[gFilteredObjCnt].rdu16FreqIdx.D = ObjData->ObjData[i].rdu16FreqIdx.D;
				gFilteredObj[gFilteredObjCnt].s16HarmIdx = ObjData->ObjData[i].s16HarmIdx;
				gFilteredObj[gFilteredObjCnt].s16MatRefPeakIdx = ObjData->ObjData[i].s16MatRefPeakIdx;

				gFilteredObj[gFilteredObjCnt].f32PreAziAngle = ObjData->ObjData[i].f32PreAziAngle;
				gFilteredObj[gFilteredObjCnt].f32PrePow = ObjData->ObjData[i].f32PrePow;
				gFilteredObj[gFilteredObjCnt].f32SllPowdB = ObjData->ObjData[i].f32SllPowdB;
				
				gFilteredObj[gFilteredObjCnt].eModType = CurMod;
				gFilteredObj[gFilteredObjCnt].f32Range_m = ObjData->ObjData[i].f32Range;
				gFilteredObj[gFilteredObjCnt].f32Velocity_mps = ObjData->ObjData[i].f32Velocity;
				gFilteredObj[gFilteredObjCnt].f32AziAng_deg = gRadarInstInfo.f32Reverse * ObjData->ObjData[i].f32AziAngle;
				gFilteredObj[gFilteredObjCnt].f32EleAng_deg = gRadarInstInfo.f32Reverse * ObjData->ObjData[i].f32EleAngle;
				gFilteredObj[gFilteredObjCnt].f32Power_dB = ObjData->ObjData[i].f32Power;
				gFilteredObj[gFilteredObjCnt].s16TrackFlag = ObjData->ObjData[i].s16TrackFlag;
				gFilteredObjCnt++;
			}
#endif
	}

}


static void Obj_vOutProcessing_Ref(RefCalcObjData_t* ObjData, MultiMod_t CurMod)
{
	int16_t i, m, j;
	float32_t temp_range;
	float32_t temp_angle;
	float32_t temp_x;
	float32_t temp_y;

	for (i = 0; i < ObjData->s16ObjCnt; i++)
	{
		temp_range = (ObjData->ObjData[i].f32Range);
		temp_angle = (ObjData->ObjData[i].f32AziAngle);
		temp_x = temp_range * _sp_cosdf(temp_angle);
		temp_y = temp_range * _sp_sindf(temp_angle);
		_sp_cnt_break(gObjOutCnt, OBJ_NUM_OBJECT_MAX)

			if ((temp_x > 200.0f) 
				&& (temp_x < 300.0f) 
				&& (_sp_abs(temp_y) < 45.0f))
			{
#ifdef WIN32
				gObjectOut[gObjOutCnt].eGFType = NOT_GHOST;
				gObjectOut[gObjOutCnt].s16PeakIdx = ObjData->ObjData[i].s16PeakIdx;
				gObjectOut[gObjOutCnt].rdu16FreqIdx.R = ObjData->ObjData[i].rdu16FreqIdx.R;
				gObjectOut[gObjOutCnt].rdu16FreqIdx.D = ObjData->ObjData[i].rdu16FreqIdx.D;

#endif
				gObjectOut[gObjOutCnt].eModType = CurMod;
				gObjectOut[gObjOutCnt].f32Range_m = ObjData->ObjData[i].f32Range;
				gObjectOut[gObjOutCnt].f32Velocity_mps = ObjData->ObjData[i].f32Velocity;
				gObjectOut[gObjOutCnt].f32AziAng_deg = gRadarInstInfo.f32Reverse * ObjData->ObjData[i].f32AziAngle;
				gObjectOut[gObjOutCnt].f32EleAng_deg = gRadarInstInfo.f32Reverse * ObjData->ObjData[i].f32EleAngle;
				//gObjectOut[gObjOutCnt].f32EleAng_deg = gRadarInstInfo.f32Reverse * ObjData->ObjData[i].f32EleAngle;
				gObjectOut[gObjOutCnt].f32Power_dB = ObjData->ObjData[i].f32Power;
				gObjOutCnt++;
			}
	}

}


