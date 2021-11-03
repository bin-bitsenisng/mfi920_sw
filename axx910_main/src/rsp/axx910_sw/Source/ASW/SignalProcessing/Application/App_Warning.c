/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "App_Main.h"
#include "App_Warning.h"


/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
static void App_vFCW(void);
static void App_vFVSA(void);


/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void App_vWarning(void)
{
	App_vFCW();
	App_vFVSA();

}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
static void App_vFCW(void)
{

	if (gCIPVInfo.u8TrkIdx == 255U)
	{
		gCIPVInfo.f32TTC = APP_FCW_TTC_INIT;
	}
	else
	{
		if (gAppTrack[gCIPVInfo.u8TrkIdx].f32VelX < 0.0f)
		{
			gCIPVInfo.f32TTC = gAppTrack[gCIPVInfo.u8TrkIdx].f32PosX / (-gAppTrack[gCIPVInfo.u8TrkIdx].f32VelX);
		}
		else
		{
			gCIPVInfo.f32TTC = APP_FCW_TTC_INIT;
		}
	}


	if ((gCIPVInfo.u8TrkIdx != 255U)
		&& (gCIPVInfo.u8SelectedCnt >= APP_FCW_CIPV_AGE_MIN)
		&& (gSpEgoInfo.f32VehSpeed_mps > APP_FCW_EGO_SPD_MIN)
		&& (gSpEgoInfo.f32VehSpeed_mps < APP_FCW_EGO_SPD_MAX)
		&& (gSpEgoInfo.f32PathRadius > APP_FCW_WARN_RADIUS_MIN))
	{
		gFrontWarnInfo.f32PosX_m = gAppTrack[gCIPVInfo.u8TrkIdx].f32PosX;
		gFrontWarnInfo.f32TTC_sec = gCIPVInfo.f32TTC;

		if (gCIPVInfo.f32TTC < APP_FCW_WARN_TTC_3RD)
		{
			gFrontWarnInfo.u8FCWLvl = 3U;
		}
		else if (gCIPVInfo.f32TTC < APP_FCW_WARN_TTC_2ND)
		{
			gFrontWarnInfo.u8FCWLvl = 2U;
		}
		else if (gCIPVInfo.f32TTC < APP_FCW_WARN_TTC_1ST)
		{
			gFrontWarnInfo.u8FCWLvl = 1U;
		}
		else
		{
			gFrontWarnInfo.u8FCWLvl = 0U;
		}
	}
	else
	{
		gFrontWarnInfo.f32PosX_m = 0.0f;
		gFrontWarnInfo.f32TTC_sec = 0.0f;
		gFrontWarnInfo.u8FCWLvl = 0U;
	}

}


static void App_vFVSA(void)
{

	if ((gCIPVInfo.u8FVSAIdx != 255U)
		&& (gAppTrack[gCIPVInfo.u8FVSAIdx].Status == NOT_TARGET))
	{
		gCIPVInfo.u8FVSAIdx = 255U;
		gCIPVInfo.u16StopCnt = 0U;
		gCIPVInfo.u8StoppedFlag = 0U;
	}

	if (gCIPVInfo.u8TrkIdx != 255U)
	{
		/* CIPV Stopped Counting */
		if ((gSpEgoInfo.f32VehSpeed_mps < APP_FVSA_EGO_SPD_MIN)
			&& (gAppTrack[gCIPVInfo.u8TrkIdx].f32PosX < APP_FVSA_STOPPED_RANGE)
			&& (_sp_abs(gAppTrack[gCIPVInfo.u8TrkIdx].f32VelY) < APP_FVSA_STOPPED_VELOCITY_Y)
			&& (_sp_abs(gAppTrack[gCIPVInfo.u8TrkIdx].f32VelX) < APP_FVSA_STOPPED_VELOCITY_X))
		{
			if (gCIPVInfo.u16StopCnt < APP_FVSA_STOPPED_CNT_MIN)
			{
				gCIPVInfo.u16StopCnt++;
			}
			else
			{
				gCIPVInfo.u8StoppedFlag = 1U;
				gCIPVInfo.u8FVSAIdx = gCIPVInfo.u8TrkIdx;
			}
		}
		else
		{
			gCIPVInfo.u16StopCnt = 0U;
		}
	}
	else
	{
		/* CIPS Stopped Counting */
		if ((gCIPVInfo.u8CIPSIdx != 255U)
			&& (gSpEgoInfo.f32VehSpeed_mps < APP_FVSA_EGO_SPD_MIN)
			&& (gAppTrack[gCIPVInfo.u8CIPSIdx].f32PosX < APP_FVSA_STOPPED_RANGE)
			&& (_sp_abs(gAppTrack[gCIPVInfo.u8CIPSIdx].f32VelY) < APP_FVSA_STOPPED_VELOCITY_Y)
			&& (_sp_abs(gAppTrack[gCIPVInfo.u8CIPSIdx].f32VelX) < APP_FVSA_STOPPED_VELOCITY_X))
		{
			if (gCIPVInfo.u16StopCnt < APP_FVSA_STOPPED_CNT_MIN)
			{
				gCIPVInfo.u16StopCnt++;
			}
			else
			{
				gCIPVInfo.u8StoppedFlag = 1U;
				gCIPVInfo.u8FVSAIdx = gCIPVInfo.u8CIPSIdx;
			}
		}
		else
		{
			gCIPVInfo.u16StopCnt = 0U;
		}
	}

	/* Decision */
	if ((gAppTrack[gCIPVInfo.u8TrkIdx].f32PosX > APP_FVSA_WARN_RANGE_MAX)
		|| (gSpEgoInfo.f32VehSpeed_mps > APP_FVSA_EGO_SPD_MIN))
	{
		gCIPVInfo.u8StoppedFlag = 0U;
		gCIPVInfo.u8FVSAIdx = 255U;
	}

	if ((gCIPVInfo.u8StoppedFlag == 1U)
		&& (gCIPVInfo.u8FVSAIdx != 255U)
		&& (gAppTrack[gCIPVInfo.u8FVSAIdx].f32PosX > APP_FVSA_WARN_RANGE_MIN)
		&& (gAppTrack[gCIPVInfo.u8FVSAIdx].f32VelX > APP_FVSA_WARN_VELOCITY))
	{
		gFrontWarnInfo.u8FVSA = 1U;
		gCIPVInfo.u8FVSAIdx = 255U;
		gCIPVInfo.u8StoppedFlag = 0U;
	}
	else
	{
		gFrontWarnInfo.u8FVSA = 0U;
	}

}

