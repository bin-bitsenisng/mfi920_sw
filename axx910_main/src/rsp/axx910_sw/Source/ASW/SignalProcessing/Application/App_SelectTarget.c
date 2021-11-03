/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "App_Main.h"


/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
static void App_vCheckInPath(void);
static void App_vSelectCIPV(void);
static void App_vSelectCIPS(void);


/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void App_vSelectionTarget(void)
{
	App_vCheckInPath();
	App_vSelectCIPV();
	App_vSelectCIPS();

}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
static void App_vCheckInPath(void)
{
	int16_t tr;
	float32_t path_pos_y;
	float32_t diff_y;


	for (tr = 0; tr < SP_NUM_TRACK_MAX; tr++)
	{
		if (gAppTrack[tr].Status == VERIFIED_TARGET)
		{
			path_pos_y = _sp_pow2(gAppTrack[tr].f32PosX) / (2.0f * gSpEgoInfo.f32PathRadius);
			diff_y = _sp_abs(path_pos_y - gAppTrack[tr].f32PosY);

			if (diff_y < APP_CIPV_PATH_WIDTH_INNER)
			{
				gAppTrack[tr].u8InPath = 1U;
			}
			else if (diff_y > APP_CIPV_PATH_WIDTH_OUTTER)
			{
				gAppTrack[tr].u8InPath = 0U;
			}
			else
			{
			}
		}
	}

}


static void App_vSelectCIPV(void)
{
	int16_t tr;
	int16_t inpath_flag;
	uint8_t cipv_idx;

	
	if ((gCIPVInfo.u8TrkIdx != 255U)
		&& ((gAppTrack[gCIPVInfo.u8TrkIdx].Status == NOT_TARGET)
			|| (gAppTrack[gCIPVInfo.u8TrkIdx].u8InPath == 0U)))
	{
		gCIPVInfo.u8TrkIdx = 255U;
		gCIPVInfo.u8SelectedCnt = 0U;
	}

	inpath_flag = 0;
	cipv_idx = gCIPVInfo.u8TrkIdx;
	for (tr = 0; tr < SP_NUM_TRACK_MAX; tr++)
	{
		if ((gAppTrack[tr].u8InPath == 1U)
			&& (gAppTrack[tr].MovState != STATIONARY)
			&& ((gAppTrack[tr].f32VelX + gSpEgoInfo.f32VehSpeed_mps) > APP_CIPV_ONCOMMING_VEL_MIN))
		{
			inpath_flag = 1;
			if (cipv_idx != 255U)
			{
				if (gAppTrack[tr].f32PosX < gAppTrack[cipv_idx].f32PosX)
				{
					cipv_idx = (uint8_t)tr;
				}
			}
			else
			{
				cipv_idx = (uint8_t)tr;
			}
		}
	}
	
	if ((cipv_idx != 255U)
		&& (cipv_idx == gCIPVInfo.u8TrkIdx))
	{
		if (gCIPVInfo.u8SelectedCnt < 255U)
		{
			gCIPVInfo.u8SelectedCnt++;
		}
	}
	else
	{
		gCIPVInfo.u8SelectedCnt = 0U;
	}
	gCIPVInfo.u8TrkIdx = cipv_idx;


	if (inpath_flag == 0)
	{
		gCIPVInfo.u8TrkIdx = 255U;
	}

}


static void App_vSelectCIPS(void)
{
	int16_t tr;
	int16_t inpath_flag;


	if ((gCIPVInfo.u8CIPSIdx != 255U)
		&& ((gAppTrack[gCIPVInfo.u8CIPSIdx].Status == NOT_TARGET)
			|| (gAppTrack[gCIPVInfo.u8CIPSIdx].MovState != STATIONARY)
			|| (gAppTrack[gCIPVInfo.u8CIPSIdx].u8InPath == 0U)))
	{
		gCIPVInfo.u8CIPSIdx = 255U;
	}

	inpath_flag = 0;
	for (tr = 0; tr < SP_NUM_TRACK_MAX; tr++)
	{
		if ((gAppTrack[tr].u8InPath == 1U)
			&& (gAppTrack[tr].MovState == STATIONARY))
		{
			inpath_flag = 1;
			if (gCIPVInfo.u8CIPSIdx != 255U)
			{
				if (gAppTrack[tr].f32PosX < gAppTrack[gCIPVInfo.u8CIPSIdx].f32PosX)
				{
					gCIPVInfo.u8CIPSIdx = (uint8_t)tr;
				}
			}
			else
			{
				gCIPVInfo.u8CIPSIdx = (uint8_t)tr;
			}
		}
	}

	if (inpath_flag == 0)
	{
		gCIPVInfo.u8CIPSIdx = 255U;
	}

}
