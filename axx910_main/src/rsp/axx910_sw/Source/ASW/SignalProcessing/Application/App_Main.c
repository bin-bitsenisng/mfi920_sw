/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "App_Main.h"
#include "App_Input.h"


/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/
AppTrack_t gAppTrack[SP_NUM_TRACK_MAX];


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void App_vSysInit(void)
{

	
}


void App_vMain(void)
{
	App_vInputProcessing();

}

/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/


