/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Obj_Main.h"
#include "Obj_DBF.h"
#include "Obj_FreqEst.h"
#include "Obj_CFAR.h"
#include "Obj_CalRV.h"
#include "Obj_AngEst.h"
#include "Obj_SelCand.h"
#include "Obj_Output.h"
#include "Gf_Main.h"

#ifdef LINUX
#include <sys/time.h>
#include "print_common.h"
#endif

#ifdef CUDA_ACC
#include "Cuda_bts_lib.cuh"
#endif

/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/
#ifdef CUDA_ACC
Cuda_RefBeamData_t gRM_BeamData;
Cuda_BeamData_t gLR_BeamData;
Cuda_BeamData_t gMR_BeamData;
Cuda_BeamData_t gSR_BeamData;
#else
RefBeamData_t gRM_BeamData;
BeamData_t gLR_BeamData;
BeamData_t gMR_BeamData;
BeamData_t gSR_BeamData;
#endif

RefPeakData_t gRM_PeakData;

#ifdef CUDA_ACC
Cuda_PeakData_t gLR_PeakData;
Cuda_PeakData_t gMR_PeakData;
Cuda_PeakData_t gSR_PeakData;
#else
PeakData_t gLR_PeakData;
PeakData_t gMR_PeakData;
PeakData_t gSR_PeakData;
#endif

RefCalcObjData_t gRM_ObjData;
CalcObjData_t gLR_ObjData;
CalcObjData_t gMR_ObjData;
CalcObjData_t gSR_ObjData;
ObjectOut_t gObjectOut[OBJ_NUM_OBJECT_MAX];

int16_t gObjOutCnt;


#ifdef WIN32
ObjectOut_t gFilteredObj[OBJ_NUM_FILETERD_OBJ_MAX];
int16_t gFilteredObjCnt;
int16_t gPeakMode;
#endif


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/

static void Obj_vScanInit(void);
static void Obj_vGenSteerVec(void);

/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Obj_vSysInit(void)
{
	Obj_vGenSteerVec();
	Obj_vDBF_SysInit();
	Obj_vCFAR_SysInit();
}


void Obj_vMain(void)
{
#ifdef LINUX
    struct timeval startTime, endTime;
    double diffTime;
#endif

    Obj_vScanInit();

#ifdef LINUX
    gettimeofday(&startTime, NULL);
#endif

#ifdef WIN32
	if (gPeakMode == 1)
	{
		//Obj_vDBF();
		Obj_vCFAR();
	}
	else
	{
		Obj_vDBF();
		Obj_vCFAR();
	}
#else

	Obj_vDBF();
	
#ifdef LINUX
    gettimeofday(&endTime, NULL);
    diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
    TRACE_TIME_MSG("Obj_vDBF(): %lf s\n", diffTime);
#endif

#ifdef LINUX
    gettimeofday(&startTime, NULL);
#endif
	
	Obj_vCFAR();
	
#ifdef LINUX
    gettimeofday(&endTime, NULL);
    diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
    TRACE_TIME_MSG("Obj_vCFAR(): %lf s\n", diffTime);
#endif

#endif

	printf("==============\n");
	printf("[RM]	PeakCnt : %d\n", gRM_PeakData.s16PeakCnt);
	printf("==============\n");
	printf("[LR]	PeakCnt : %d\n", gLR_PeakData.s16PeakCnt);
	printf("[MR]	PeakCnt : %d\n", gMR_PeakData.s16PeakCnt);
	printf("[SR]	PeakCnt : %d\n", gSR_PeakData.s16PeakCnt);
	printf("[LMS Total]	PeakCnt : %d\n", gSR_PeakData.s16PeakCnt + gMR_PeakData.s16PeakCnt + gLR_PeakData.s16PeakCnt);
	printf("==============\n");



	Obj_vCalcRV();
	
#ifdef LINUX
    gettimeofday(&startTime, NULL);
#endif

	
	Obj_vAngEst();
	

#ifdef LINUX
    gettimeofday(&endTime, NULL);
    diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
    TRACE_TIME_MSG("Obj_vAngEst(): %lf s\n", diffTime);
#endif

	Obj_vSelCand();


	if (gInitScanFlag == 0)
	{
		Gf_vMain();
	}
	Obj_vOut();
}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
static void Obj_vScanInit(void)
{

}


static void Obj_vGenSteerVec(void)
{
	int16_t i, j, ch;
	float32_t temp_azi_rad;
	float32_t temp_ele_rad;
	float32_t temp_rad;
	float32_t temp_ChPosY[OBJ_AE_NUM_CH] = OBJ_AE_CH_POS_Y;
	float32_t temp_ChPosZ[OBJ_AE_NUM_CH] = OBJ_AE_CH_POS_Z;
	float32_t temp_ChPos[OBJ_AE_RM_NUM_CH] = OBJ_AE_RM_CH_POS;

	alloc_peak_data_gpu_mem();

	/* RM */
	for (j = 0; j < OBJ_AE_AZI_RM_NUM_APS_STEPS; j++)
	{
		gRM_PeakData.f32AziAngTable[j] = (float32_t)(((OBJ_AE_AZI_RM_NUM_APS_STEPS - 1) / 2) - j) * OBJ_AE_AZI_RM_APS_STEP_SIZE;
		temp_rad = (gRM_PeakData.f32AziAngTable[j] * SP_PI) / 180.0f;

		for (ch = 0; ch < OBJ_AE_RM_NUM_CH; ch++)
		{
			gRM_PeakData.cf32SteerVec[j][ch].real = _sp_cosf(2.0f * SP_PI * temp_ChPos[ch] * _sp_sinf(temp_rad));
			gRM_PeakData.cf32SteerVec[j][ch].imag = -_sp_sinf(2.0f * SP_PI * temp_ChPos[ch] * _sp_sinf(temp_rad));
		}
	}

	/* Pre L, M, S*/
	for (j = 0; j < OBJ_AE_PRE_AZI_LR_NUM_APS_STEPS; j++)
	{
		gLR_PeakData.f32PreAziAngTable[j] = (float32_t)(((OBJ_AE_PRE_AZI_LR_NUM_APS_STEPS - 1) / 2) - j) * OBJ_AE_PRE_AZI_LR_APS_STEP_SIZE;
		temp_rad = (gLR_PeakData.f32PreAziAngTable[j] * SP_PI) / 180.0f;
		for (ch = 0; ch < OBJ_AE_RM_NUM_CH; ch++)
		{
			gLR_PeakData.cf32PreSteerVec[j][ch].real = _sp_cosf(2.0f * SP_PI * temp_ChPos[ch] * _sp_sinf(temp_rad));
			gLR_PeakData.cf32PreSteerVec[j][ch].imag = -_sp_sinf(2.0f * SP_PI * temp_ChPos[ch] * _sp_sinf(temp_rad));
		}
	}

	for (j = 0; j < OBJ_AE_PRE_AZI_MR_NUM_APS_STEPS; j++)
	{
		gMR_PeakData.f32PreAziAngTable[j] = (float32_t)(((OBJ_AE_PRE_AZI_MR_NUM_APS_STEPS - 1) / 2) - j) * OBJ_AE_PRE_AZI_MR_APS_STEP_SIZE;
		temp_rad = (gMR_PeakData.f32PreAziAngTable[j] * SP_PI) / 180.0f;
		for (ch = 0; ch < OBJ_AE_RM_NUM_CH; ch++)
		{
			gMR_PeakData.cf32PreSteerVec[j][ch].real = _sp_cosf(2.0f * SP_PI * temp_ChPos[ch] * _sp_sinf(temp_rad));
			gMR_PeakData.cf32PreSteerVec[j][ch].imag = -_sp_sinf(2.0f * SP_PI * temp_ChPos[ch] * _sp_sinf(temp_rad));
		}
	}


	for (j = 0; j < OBJ_AE_PRE_AZI_SR_NUM_APS_STEPS; j++)
	{
		gSR_PeakData.f32PreAziAngTable[j] = (float32_t)(((OBJ_AE_PRE_AZI_SR_NUM_APS_STEPS - 1) / 2) - j) * OBJ_AE_PRE_AZI_SR_APS_STEP_SIZE;
		temp_rad = (gSR_PeakData.f32PreAziAngTable[j] * SP_PI) / 180.0f;
		for (ch = 0; ch < OBJ_AE_RM_NUM_CH; ch++)
		{
			gSR_PeakData.cf32PreSteerVec[j][ch].real = _sp_cosf(2.0f * SP_PI * temp_ChPos[ch] * _sp_sinf(temp_rad));
			gSR_PeakData.cf32PreSteerVec[j][ch].imag = -_sp_sinf(2.0f * SP_PI * temp_ChPos[ch] * _sp_sinf(temp_rad));
		}
	}

	/* LR */
	for (j = 0; j < OBJ_AE_ELE_LR_NUM_APS_STEPS; j++)
	{
		for (i = 0; i < OBJ_AE_AZI_LR_NUM_APS_STEPS; i++)
		{

			gLR_PeakData.f32AziAngTable[i] = (float32_t)(((OBJ_AE_AZI_LR_NUM_APS_STEPS - 1) / 2) - i) * OBJ_AE_AZI_LR_APS_STEP_SIZE;
			gLR_PeakData.f32EleAngTable[j] = (float32_t)(((OBJ_AE_ELE_LR_NUM_APS_STEPS - 1) / 2) - j) * OBJ_AE_ELE_LR_APS_STEP_SIZE;
			//gLR_PeakData.f32EleAngTable[j] = (float32_t)(((OBJ_AE_ELE_LR_NUM_APS_STEPS - 1) / 2) - j) * OBJ_AE_ELE_LR_APS_STEP_SIZE + 5.0f;
			
			temp_azi_rad = (gLR_PeakData.f32AziAngTable[i] * SP_PI) / 180.0f;
			temp_ele_rad = (gLR_PeakData.f32EleAngTable[j] * SP_PI) / 180.0f;

			for (ch = 0; ch < OBJ_AE_NUM_CH; ch++)
			{
#ifdef CUDA_ACC
				gLR_PeakData.cf32SteerVec[j*OBJ_AE_AZI_LR_NUM_APS_STEPS*OBJ_AE_NUM_CH + i*OBJ_AE_NUM_CH + ch].real = _sp_cosf(2.0f * SP_PI * (temp_ChPosY[ch] * _sp_sinf(temp_azi_rad)*_sp_cosf(temp_ele_rad) + temp_ChPosZ[ch] * _sp_sinf(temp_ele_rad)));
				gLR_PeakData.cf32SteerVec[j*OBJ_AE_AZI_LR_NUM_APS_STEPS*OBJ_AE_NUM_CH + i*OBJ_AE_NUM_CH + ch].imag =  _sp_sinf(2.0f * SP_PI * (temp_ChPosY[ch] * _sp_sinf(temp_azi_rad)*_sp_cosf(temp_ele_rad) + temp_ChPosZ[ch] * _sp_sinf(temp_ele_rad)));
#else
				gLR_PeakData.cf32SteerVec[j * OBJ_AE_AZI_LR_NUM_APS_STEPS + i][ch].real = _sp_cosf(2.0f * SP_PI * (temp_ChPosY[ch] * _sp_sinf(temp_azi_rad)*_sp_cosf(temp_ele_rad) - temp_ChPosZ[ch] * _sp_sinf(temp_ele_rad)));
				gLR_PeakData.cf32SteerVec[j * OBJ_AE_AZI_LR_NUM_APS_STEPS + i][ch].imag = -_sp_sinf(2.0f * SP_PI * (temp_ChPosY[ch] * _sp_sinf(temp_azi_rad)*_sp_cosf(temp_ele_rad) - temp_ChPosZ[ch] * _sp_sinf(temp_ele_rad)));
#endif
			}
		}
	}

	/* MR */
	for (j = 0; j < OBJ_AE_ELE_MR_NUM_APS_STEPS; j++)
	{
		for (i = 0; i < OBJ_AE_AZI_MR_NUM_APS_STEPS; i++)
		{
			gMR_PeakData.f32AziAngTable[i] = (float32_t)(((OBJ_AE_AZI_MR_NUM_APS_STEPS - 1) / 2) - i) * OBJ_AE_AZI_MR_APS_STEP_SIZE;
			gMR_PeakData.f32EleAngTable[j] = (float32_t)(((OBJ_AE_ELE_MR_NUM_APS_STEPS - 1) / 2) - j) * OBJ_AE_ELE_MR_APS_STEP_SIZE;
			//gMR_PeakData.f32EleAngTable[j] = (float32_t)(((OBJ_AE_ELE_MR_NUM_APS_STEPS - 1) / 2) - j) * OBJ_AE_ELE_MR_APS_STEP_SIZE + 5.0f;
			temp_azi_rad = (gMR_PeakData.f32AziAngTable[i] * SP_PI) / 180.0f;
			temp_ele_rad = (gMR_PeakData.f32EleAngTable[j] * SP_PI) / 180.0f;

			for (ch = 0; ch < OBJ_AE_NUM_CH; ch++)
			{
#ifdef CUDA_ACC
				gMR_PeakData.cf32SteerVec[j*OBJ_AE_AZI_MR_NUM_APS_STEPS*OBJ_AE_NUM_CH + i*OBJ_AE_NUM_CH + ch].real = _sp_cosf(2.0f * SP_PI * (temp_ChPosY[ch] * _sp_sinf(temp_azi_rad)*_sp_cosf(temp_ele_rad) + temp_ChPosZ[ch] * _sp_sinf(temp_ele_rad)));
				gMR_PeakData.cf32SteerVec[j*OBJ_AE_AZI_MR_NUM_APS_STEPS*OBJ_AE_NUM_CH + i*OBJ_AE_NUM_CH + ch].imag = _sp_sinf(2.0f * SP_PI * (temp_ChPosY[ch] * _sp_sinf(temp_azi_rad)*_sp_cosf(temp_ele_rad) + temp_ChPosZ[ch] * _sp_sinf(temp_ele_rad)));
#else
				gMR_PeakData.cf32SteerVec[j * OBJ_AE_AZI_MR_NUM_APS_STEPS + i][ch].real = _sp_cosf(2.0f * SP_PI * (temp_ChPosY[ch] * _sp_sinf(temp_azi_rad)*_sp_cosf(temp_ele_rad) - temp_ChPosZ[ch] * _sp_sinf(temp_ele_rad)));
				gMR_PeakData.cf32SteerVec[j * OBJ_AE_AZI_MR_NUM_APS_STEPS + i][ch].imag = -_sp_sinf(2.0f * SP_PI * (temp_ChPosY[ch] * _sp_sinf(temp_azi_rad)*_sp_cosf(temp_ele_rad) - temp_ChPosZ[ch] * _sp_sinf(temp_ele_rad)));
#endif	
			}
		}
	}


	/* SR */
	for (j = 0; j < OBJ_AE_ELE_SR_NUM_APS_STEPS; j++)
	{
		for (i = 0; i < OBJ_AE_AZI_SR_NUM_APS_STEPS; i++)
		{
			gSR_PeakData.f32AziAngTable[i] = (float32_t)(((OBJ_AE_AZI_SR_NUM_APS_STEPS - 1) / 2) - i) * OBJ_AE_AZI_SR_APS_STEP_SIZE;
			gSR_PeakData.f32EleAngTable[j] = (float32_t)(((OBJ_AE_ELE_SR_NUM_APS_STEPS - 1) / 2) - j) * OBJ_AE_ELE_SR_APS_STEP_SIZE;
			//gSR_PeakData.f32EleAngTable[j] = (float32_t)(((OBJ_AE_ELE_SR_NUM_APS_STEPS - 1) / 2) - j) * OBJ_AE_ELE_SR_APS_STEP_SIZE + 5.0f;
			temp_azi_rad = (gSR_PeakData.f32AziAngTable[i] * SP_PI) / 180.0f;
			temp_ele_rad = (gSR_PeakData.f32EleAngTable[j] * SP_PI) / 180.0f;
			
			for (ch = 0; ch < OBJ_AE_NUM_CH; ch++)
			{
#ifdef CUDA_ACC
				gSR_PeakData.cf32SteerVec[j*OBJ_AE_AZI_SR_NUM_APS_STEPS*OBJ_AE_NUM_CH + i*OBJ_AE_NUM_CH + ch].real = _sp_cosf(2.0f * SP_PI * (temp_ChPosY[ch] * _sp_sinf(temp_azi_rad)*_sp_cosf(temp_ele_rad) + temp_ChPosZ[ch] * _sp_sinf(temp_ele_rad)));
				gSR_PeakData.cf32SteerVec[j*OBJ_AE_AZI_SR_NUM_APS_STEPS*OBJ_AE_NUM_CH + i*OBJ_AE_NUM_CH + ch].imag = _sp_sinf(2.0f * SP_PI * (temp_ChPosY[ch] * _sp_sinf(temp_azi_rad)*_sp_cosf(temp_ele_rad) + temp_ChPosZ[ch] * _sp_sinf(temp_ele_rad)));
#else				
				gSR_PeakData.cf32SteerVec[j * OBJ_AE_AZI_SR_NUM_APS_STEPS + i][ch].real = _sp_cosf(2.0f * SP_PI * (temp_ChPosY[ch] * _sp_sinf(temp_azi_rad)*_sp_cosf(temp_ele_rad) - temp_ChPosZ[ch] * _sp_sinf(temp_ele_rad)));
				gSR_PeakData.cf32SteerVec[j * OBJ_AE_AZI_SR_NUM_APS_STEPS + i][ch].imag = -_sp_sinf(2.0f * SP_PI * (temp_ChPosY[ch] * _sp_sinf(temp_azi_rad)*_sp_cosf(temp_ele_rad) - temp_ChPosZ[ch] * _sp_sinf(temp_ele_rad)));
#endif
			}
		}
	}
}


