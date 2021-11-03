/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Sp_Main.h"
#include "Pre_Main.h"
#include "Obj_Main.h"
#include "Trk_Main.h"
#include "App_Main.h"
#ifdef LINUX
#include <sys/time.h>
#include "print_common.h"
#endif

/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/
MultiMod_t gSpCurMod;
float32_t gSpCycleTime;
int16_t gInitScanFlag;
SpObjectOut_t Sp_ObjectOut[SP_NUM_OBJECT_MAX];
SpTrackOut_t Sp_TrackOut[SP_NUM_TRACK_MAX];
RadarInst_t gRadarInstInfo;
SpLogInfo_t Sp_LogInfo;


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
static void Sp_vScanInit(void);
static void Sp_vScanEnd(void);
static void Sp_vSetRadarInstInfo(void);
static void Sp_vObjectOut(void);
//static void Sp_vTrackOut(void);
void Sp_vTrackOut(void);
static void Sp_vAppOut(void);

#ifndef LINUX
can_sig_data_t	  can_sig_data;
ai_object_t		  ai_object[AI_OBJECT_MAX_SIZE];
#endif

/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Sp_vSysInit(void)
{
	rsp_lib_init();

	gInitScanFlag = 1;
	gSpCurMod = LR_MOD;

	Sp_vSetRadarInstInfo();
	Pre_vSysInit();
	Obj_vSysInit();
	Trk_vSysInit();
}


void Sp_vMain(void)
{
#ifdef LINUX
	struct timeval startTime, endTime;
	double diffTime;
#endif    

	Sp_vScanInit();
#ifdef LINUX
	gettimeofday(&startTime, NULL);
#endif
	Pre_vMain();
#ifdef LINUX
	gettimeofday(&endTime, NULL);
	diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
	TRACE_TIME_MSG("Pre_vMain(): %lf s\n", diffTime);
	//printf("Pre_vMain(): %lf s\n", diffTime);
#endif

#ifdef LINUX
	gettimeofday(&startTime, NULL);
#endif
	Obj_vMain();
#ifdef LINUX
	gettimeofday(&endTime, NULL);
	diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
	//TRACE_TIME_MSG("Obj_vMain(): %lf s\n", diffTime);
	//printf("Obj_vMain(): %lf s\n", diffTime);
#endif

	Sp_vObjectOut();

#ifdef LINUX
	gettimeofday(&startTime, NULL);
#endif
#ifndef LINUX	

#ifndef WIN32
	//Trk_vMain();
#endif

#endif
#ifdef LINUX
	gettimeofday(&endTime, NULL);
	diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
	//TRACE_TIME_MSG("Trk_vMain(): %lf s\n", diffTime);
	//printf("Trk_vMain(): %lf s\n", diffTime);
#endif

#ifndef LINUX
#ifndef WIN32
	Sp_vTrackOut();
#endif
#endif

	App_vMain();
	Sp_vAppOut();

	Sp_vScanEnd();

}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
static void Sp_vScanInit(void)
{
	gSpCycleTime = (float32_t)RADAR_CFG_CYCLE_TIME_US * 1e-6f;

}


static void Sp_vScanEnd(void)
{
	gInitScanFlag = 0;

	Sp_LogInfo.u8PRFType;
	Sp_LogInfo.u16SMPLNum = SP_CAL_SAMPLE_NUM;
	Sp_LogInfo.u16CycleTime = (uint16_t)(gSpCycleTime * 10000.0f);
	Sp_LogInfo.s16LRPeakCnt = gLR_PeakData.s16PeakCnt;
	Sp_LogInfo.s16MRPeakCnt = gMR_PeakData.s16PeakCnt;
	Sp_LogInfo.s16SRPeakCnt = gSR_PeakData.s16PeakCnt;


}


static void Sp_vSetRadarInstInfo(void)
{
	gRadarInstInfo.f32PosX = TRK_RADAR_INSTALL_POS_X;
	gRadarInstInfo.f32PosY = TRK_RADAR_INSTALL_POS_Y;
	gRadarInstInfo.f32PosZ = TRK_RADAR_INSTALL_POS_Z;
	gRadarInstInfo.f32Reverse = (TRK_RADAR_INSTALL_REVERSE == 0) ? 1.0f : -1.0f;
	gRadarInstInfo.f32AziAng = TRK_RADAR_INSTALL_ANGLE_AZ;
	gRadarInstInfo.f32EleAng = TRK_RADAR_INSTALL_ANGLE_EL;

}


static void Sp_vObjectOut(void)
{
	int16_t i;

	for (i = 0; i < SP_NUM_OBJECT_MAX; i++)
	{
		if (i < gObjOutCnt)
		{
			Sp_ObjectOut[i].u8ModType = (uint8_t)gObjectOut[i].eModType;
			Sp_ObjectOut[i].f32Range_m = gObjectOut[i].f32Range_m;
			Sp_ObjectOut[i].f32Velocity_mps = gObjectOut[i].f32Velocity_mps;
			Sp_ObjectOut[i].f32AziAng_deg = gObjectOut[i].f32AziAng_deg;
			Sp_ObjectOut[i].f32EleAng_deg = gObjectOut[i].f32EleAng_deg;
			

			if ((uint8_t)gObjectOut[i].eModType == RM_MOD)
			{
				Sp_ObjectOut[i].f32Power_dB = gObjectOut[i].f32Power_dB;
			}
			else
			{
				if (gObjectOut[i].s16TrackFlag == 1)
				{
					Sp_ObjectOut[i].f32Power_dB = gObjectOut[i].f32Power_dB;
				}
				else
				{
					Sp_ObjectOut[i].f32Power_dB = 255U;
				}
			}
		}
		else
		{
			Sp_ObjectOut[i].u8ModType = 0;
			Sp_ObjectOut[i].f32Range_m = 0.0f;
			Sp_ObjectOut[i].f32Velocity_mps = 0.0f;
			Sp_ObjectOut[i].f32AziAng_deg = 0.0f;
			Sp_ObjectOut[i].f32EleAng_deg = 0.0f;
			Sp_ObjectOut[i].f32Power_dB = 0.0f;
		}
	}

}


void Sp_vTrackOut(void)
{

	int16_t Tr;


	for (Tr = 0; Tr < SP_NUM_TRACK_MAX; Tr++)
	{
#ifndef WIN32
		Sp_TrackOut[Tr].u8Status = (uint8_t)gTrackOut[Tr].Status;

		if (Sp_TrackOut[Tr].u8Status != 0)
		{
			Sp_TrackOut[Tr].s8Idx = (uint8_t)Tr;
			Sp_TrackOut[Tr].u8UpdState = (uint8_t)gTrackOut[Tr].UpdState;
			Sp_TrackOut[Tr].u8MovState = (uint8_t)gTrackOut[Tr].MovState;
			Sp_TrackOut[Tr].u16AliveAge = (uint8_t)gTrackOut[Tr].u16AliveAge;
			Sp_TrackOut[Tr].f32PosX_m = gTrackOut[Tr].f32PosX;
			Sp_TrackOut[Tr].f32PosY_m = gTrackOut[Tr].f32PosY;
			Sp_TrackOut[Tr].f32RefPosX_m = gTrackOut[Tr].f32RefPosX;
			Sp_TrackOut[Tr].f32RefPosY_m = gTrackOut[Tr].f32RefPosY;
			Sp_TrackOut[Tr].f32VelX_mps = gTrackOut[Tr].f32VelX;
			Sp_TrackOut[Tr].f32VelY_mps = gTrackOut[Tr].f32VelY;
			Sp_TrackOut[Tr].f32HeadingAng_deg = gTrackOut[Tr].f32HeadingAng;
			Sp_TrackOut[Tr].f32Power_dB = gTrackOut[Tr].f32Pow_dB;
			Sp_TrackOut[Tr].f32Width_m = gTrackOut[Tr].f32Width;
			Sp_TrackOut[Tr].f32Length_m = gTrackOut[Tr].f32Length;
			Sp_TrackOut[Tr].u32ObjClass = gTrackOut[Tr].u32ObjClass;
			Sp_TrackOut[Tr].u32FusionType = gTrackOut[Tr].u32FusionType;
			Sp_TrackOut[Tr].f32PosZ = gTrackOut[Tr].f32PosZ;
			Sp_TrackOut[Tr].f32Height = gTrackOut[Tr].f32Height;
		}
		else
		{
			Sp_TrackOut[Tr].s8Idx = -1;
			Sp_TrackOut[Tr].u8UpdState = 0U;
			Sp_TrackOut[Tr].u8MovState = 0U;
			Sp_TrackOut[Tr].u16AliveAge = 0U;
			Sp_TrackOut[Tr].f32PosX_m = 0.0f;
			Sp_TrackOut[Tr].f32PosY_m = 0.0f;
			Sp_TrackOut[Tr].f32RefPosX_m = 0.0f;
			Sp_TrackOut[Tr].f32RefPosY_m = 0.0f;
			Sp_TrackOut[Tr].f32VelX_mps = 0.0f;
			Sp_TrackOut[Tr].f32VelY_mps = 0.0f;
			Sp_TrackOut[Tr].f32HeadingAng_deg = 0.0f;
			Sp_TrackOut[Tr].f32Power_dB = 0.0f;
			Sp_TrackOut[Tr].f32Width_m = 0.0f;
			Sp_TrackOut[Tr].f32Length_m = 0.0f;
			Sp_TrackOut[Tr].u32ObjClass = 0U;
			Sp_TrackOut[Tr].u32FusionType = 0U;
			Sp_TrackOut[Tr].f32PosZ = 0.0f;
			Sp_TrackOut[Tr].f32Height = 0.0f;
		}
	}
#else
		Sp_TrackOut[Tr].u8Status = 0;
		Sp_TrackOut[Tr].s8Idx = -1;
		Sp_TrackOut[Tr].u8UpdState = 0U;
		Sp_TrackOut[Tr].u8MovState = 0U;
		Sp_TrackOut[Tr].u16AliveAge = 0U;
		Sp_TrackOut[Tr].f32PosX_m = 0.0f;
		Sp_TrackOut[Tr].f32PosY_m = 0.0f;
		Sp_TrackOut[Tr].f32RefPosX_m = 0.0f;
		Sp_TrackOut[Tr].f32RefPosY_m = 0.0f;
		Sp_TrackOut[Tr].f32VelX_mps = 0.0f;
		Sp_TrackOut[Tr].f32VelY_mps = 0.0f;
		Sp_TrackOut[Tr].f32HeadingAng_deg = 0.0f;
		Sp_TrackOut[Tr].f32Power_dB = 0.0f;
		Sp_TrackOut[Tr].f32Width_m = 0.0f;
		Sp_TrackOut[Tr].f32Length_m = 0.0f;
		Sp_TrackOut[Tr].u32ObjClass = 0U;
		Sp_TrackOut[Tr].u32FusionType = 0U;
		Sp_TrackOut[Tr].f32PosZ = 0.0f;
		Sp_TrackOut[Tr].f32Height = 0.0f;
	}
#endif

}


static void Sp_vAppOut(void)
{


}

