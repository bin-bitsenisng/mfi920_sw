/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Trk_Main.h"
#include "Trk_Output.h"


/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Trk_vOutInit(TrackOut_t *TrackOut)
{
	TrackOut->Status 		= NOT_TARGET;
	TrackOut->MovState 		= STATIONARY;
	TrackOut->u16AliveAge 	= 0;
	TrackOut->f32PosX 		= 0.0f;
	TrackOut->f32VelX 		= 0.0f;
	TrackOut->f32PosY 		= 0.0f;
	TrackOut->f32VelY 		= 0.0f;
	TrackOut->f32RefPosX 	= 0.0f;
	TrackOut->f32RefPosY 	= 0.0f;
	TrackOut->f32Width 		= 0.0f;
	TrackOut->f32Length 	= 0.0f;
	TrackOut->f32Pow_dB 	= 0.0f;
	TrackOut->f32MaxPow_dB 	= 0.0f;
	TrackOut->f32HeadingAng = 0.0f;
	TrackOut->s16UpdPoint 	= 0;
	TrackOut->u32ObjClass 	= OBJCLASS_UNKNOWN;
	TrackOut->u32FusionType = SF_DEFAULT;
	TrackOut->f32PosZ 		= 0.0f;
	TrackOut->f32Height 	= 0.0f;

}


void Trk_vOut(void)
{
	int16_t i_trk;

	for (i_trk = 0; i_trk < TRK_NUM_TRACK_MAX; i_trk++)
	{
		switch (gTrackData[i_trk].Status)
		{
		case  NEW_TRACK:
			gTrackOut[i_trk].Status 	= NEW_TARGET;
			gTrackOut[i_trk].UpdState 	= (gTrackData[i_trk].s16GroupClstCnt > 0) ? UPDATED : COASTING;
			break;
		case  UPDATED_TRACK:
			gTrackOut[i_trk].Status 	= VERIFIED_TARGET;
			gTrackOut[i_trk].UpdState 	= UPDATED;
			break;
		case  COASTED_TRACK:
			gTrackOut[i_trk].Status 	= VERIFIED_TARGET;
			gTrackOut[i_trk].UpdState 	= COASTING;
			break;
		case  INVALID:
			gTrackOut[i_trk].Status 	= NOT_TARGET;
			gTrackOut[i_trk].UpdState 	= COASTING;
			break;
		default:
			gTrackOut[i_trk].Status 	= NOT_TARGET;
			gTrackOut[i_trk].UpdState 	= COASTING;
			break;
		}

		if (gTrackOut[i_trk].Status == VERIFIED_TARGET)
		{
			gTrackOut[i_trk].MovState 		= gTrackData[i_trk].MovState;
			gTrackOut[i_trk].u16AliveAge 	= gTrackData[i_trk].u16AliveAge;
			gTrackOut[i_trk].f32PosX 		= gTrackData[i_trk].UpdState.f32StateX[0];
			gTrackOut[i_trk].f32VelX 		= gTrackData[i_trk].UpdState.f32StateX[1] - gTrkEgoMotionInfo.f32VelX;
			gTrackOut[i_trk].f32PosY 		= gTrackData[i_trk].UpdState.f32StateY[0];
			gTrackOut[i_trk].f32VelY 		= gTrackData[i_trk].UpdState.f32StateY[1] - gTrkEgoMotionInfo.f32VelY;
			gTrackOut[i_trk].f32RefPosX 	= gTrackData[i_trk].UpdState.f32Ref_PosX;
			gTrackOut[i_trk].f32RefPosY 	= gTrackData[i_trk].UpdState.f32Ref_PosY;
			gTrackOut[i_trk].f32Width 		= gTrackData[i_trk].UpdState.f32Width;
			gTrackOut[i_trk].f32Length 		= gTrackData[i_trk].UpdState.f32Length;
			gTrackOut[i_trk].f32Pow_dB 		= gTrackData[i_trk].f32Pow_dB;
			gTrackOut[i_trk].f32MaxPow_dB 	= gTrackData[i_trk].f32MaxPow_dB;
			gTrackOut[i_trk].f32HeadingAng 	= gTrackData[i_trk].UpdState.f32StateHeading[0];
			gTrackOut[i_trk].s16UpdPoint 	= 0;
			gTrackOut[i_trk].u32ObjClass 	= gTrackData[i_trk].obj_class;
			gTrackOut[i_trk].u32FusionType 	= gTrackData[i_trk].fusion_state;
			gTrackOut[i_trk].f32PosZ 		= gTrackData[i_trk].f32PosZ;
			gTrackOut[i_trk].f32Height 		= gTrackData[i_trk].f32Height;
		}
		else
		{
			gTrackOut[i_trk].MovState 		= STATIONARY;
			gTrackOut[i_trk].u16AliveAge 	= 0;
			gTrackOut[i_trk].f32PosX 		= 0.0f;
			gTrackOut[i_trk].f32VelX 		= 0.0f;
			gTrackOut[i_trk].f32PosY 		= 0.0f;
			gTrackOut[i_trk].f32VelY 		= 0.0f;
			gTrackOut[i_trk].f32RefPosX 	= 0.0f;
			gTrackOut[i_trk].f32RefPosY 	= 0.0f;
			gTrackOut[i_trk].f32Width 		= 0.0f;
			gTrackOut[i_trk].f32Length 		= 0.0f;
			gTrackOut[i_trk].f32Pow_dB 		= 0.0f;
			gTrackOut[i_trk].f32MaxPow_dB 	= 0.0f;
			gTrackOut[i_trk].f32HeadingAng 	= 0.0f;
			gTrackOut[i_trk].s16UpdPoint 	= 0;
			gTrackOut[i_trk].u32ObjClass 	= OBJCLASS_UNKNOWN;
			gTrackOut[i_trk].u32FusionType 	= SF_DEFAULT;
			gTrackOut[i_trk].f32PosZ 		= 0.0f;
			gTrackOut[i_trk].f32Height 		= 0.0f;
		}
	}

	// TODO, temp Free space out 
	for (int n = 0; n < 90; n++)
	{
		gFreespaceOut.fFreeRange[n] = (int32_t)(fFreeSpaceRange[n] * 10.0f);
	}

}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/


