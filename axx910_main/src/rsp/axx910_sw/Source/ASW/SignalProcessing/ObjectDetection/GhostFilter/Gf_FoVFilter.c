/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Gf_Main.h"
#include "Gf_FoVFilter.h"


/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
static void Gf_vFoVFiltering_RM(RefCalcObjData_t* Obj);
static void Gf_vFoVFiltering(CalcObjData_t* Obj, MultiMod_t ModType);

//static void Gf_vCFRTFiltering_RM(RefCalcObjData_t* Obj);
static void Gf_vCRFT_Filtering(CalcObjData_t* Obj, MultiMod_t ModType);
static void Gf_vGCRFT_Filtering(CalcObjData_t* Obj, MultiMod_t ModType);


/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Gf_vFoVFilter(void)
{

	//Gf_vFoVFiltering_RM(&gRM_ObjData);
	//Gf_vFoVFiltering(&gLR_ObjData, LR_MOD);
	//Gf_vFoVFiltering(&gMR_ObjData, MR_MOD);
	//Gf_vFoVFiltering(&gSR_ObjData, SR_MOD);

	//Gf_vCRFT_Filtering(&gLR_ObjData, LR_MOD);
	Gf_vCRFT_Filtering(&gMR_ObjData, MR_MOD);
	Gf_vCRFT_Filtering(&gSR_ObjData, SR_MOD);

	Gf_vGCRFT_Filtering(&gMR_ObjData, MR_MOD);
	Gf_vGCRFT_Filtering(&gSR_ObjData, SR_MOD);
}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/



static void Gf_vFoVFiltering(CalcObjData_t* Obj, MultiMod_t ModType)
{
	int16_t i, m, j;
	float32_t range_max;
	float32_t vel_max;
	float32_t azi_ang_max;
	float32_t ele_ang_max;


	switch (ModType)
	{
	case(LR_MOD):
		range_max = GF_FOV_LR_RANGE_MAX;
		vel_max = GF_FOV_LR_VELOCITY_MAX;
		azi_ang_max = GF_FOV_LR_AZIANGLE_MAX;
		ele_ang_max = GF_FOV_LR_ELEANGLE_MAX;
		break;

	case(MR_MOD):
		range_max = GF_FOV_MR_RANGE_MAX;
		vel_max = GF_FOV_MR_VELOCITY_MAX;
		azi_ang_max = GF_FOV_MR_AZIANGLE_MAX;
		ele_ang_max = GF_FOV_MR_ELEANGLE_MAX;
		break;

	case(SR_MOD):
		range_max = GF_FOV_SR_RANGE_MAX;
		vel_max = GF_FOV_SR_VELOCITY_MAX;
		azi_ang_max = GF_FOV_SR_AZIANGLE_MAX;
		ele_ang_max = GF_FOV_SR_ELEANGLE_MAX;
		break;
	}


	for (i = 0; i < Obj->s16ObjCnt; i++)
	{
		if ((_sp_abs(Obj->ObjData[i].f32AziAngle) > azi_ang_max)
			|| (_sp_abs(Obj->ObjData[i].f32EleAngle) > ele_ang_max))
		{
			Obj->ObjData[i].eGFType = FOV_FILTER;
		}

		if ((Obj->ObjData[i].f32Range > range_max)
			|| (_sp_abs(Obj->ObjData[i].f32Velocity > vel_max)))
		{
			Obj->ObjData[i].eGFType = FOV_FILTER;
		}

	}
}







static void Gf_vFoVFiltering_RM(RefCalcObjData_t* Obj)
{
	int16_t i, m, j;
	float32_t range_max;
	float32_t vel_max;
	float32_t azi_ang_max;



	for (i = 0; i < Obj->s16ObjCnt; i++)
	{
		if (Obj->ObjData[i].f32Range > GF_FOV_MR_RANGE_MAX && Obj->ObjData[i].f32Range < GF_FOV_LR_RANGE_MAX)
		{
			if (_sp_abs(Obj->ObjData[i].f32AziAngle) > GF_FOV_RM_LR_AZIANGLE_MAX)
			{
				Obj->ObjData[i].eGFType = FOV_FILTER;
			}
		}
		else if (Obj->ObjData[i].f32Range > GF_FOV_SR_RANGE_MAX && Obj->ObjData[i].f32Range < GF_FOV_MR_RANGE_MAX)
		{
			if (_sp_abs(Obj->ObjData[i].f32AziAngle) > GF_FOV_RM_MR_AZIANGLE_MAX)
			{
				Obj->ObjData[i].eGFType = FOV_FILTER;
			}
		}
		else if (Obj->ObjData[i].f32Range > 0 && Obj->ObjData[i].f32Range > GF_FOV_SR_RANGE_MAX)
		{
			if (_sp_abs(Obj->ObjData[i].f32AziAngle) > GF_FOV_RM_SR_AZIANGLE_MAX)
			{
				Obj->ObjData[i].eGFType = FOV_FILTER;
			}
		}
		else
		{

		}

		if ((Obj->ObjData[i].f32Range > GF_FOV_RM_RANGE_MAX)
			|| (_sp_abs(Obj->ObjData[i].f32Velocity > GF_FOV_RM_VELOCITY_MAX)))
		{
			Obj->ObjData[i].eGFType = FOV_FILTER;
		}

	}
}







static void Gf_vCRFT_Filtering(CalcObjData_t* DetObj, MultiMod_t ModType)
{
	int16_t i, j, m, n, k;
	float32_t det_r;
	float32_t det_v;
	float32_t det_ang;
	float32_t det_pow;

	float32_t ref_r;
	float32_t ref_v;
	float32_t ref_ang;

	float32_t rp_margin_r;
	float32_t rp_margin_v;
	float32_t rp_margin_ang;
	float32_t rp_margin_pow;

	float32_t pow_margin01, pow_margin02, pow_margin03, pow_margin04;
	
	switch (ModType)
	{
	case(LR_MOD):
		pow_margin01 = 5.0f;
		pow_margin02 = 4.5f;
		pow_margin03 = 4.0f;
		pow_margin04 = 2.0f;

		break;

	case(MR_MOD):
		pow_margin01 = 11.0f;   // 2m
		pow_margin02 = 9.0f;	 // 4m
		pow_margin03 = 6.5f;	 // 6m
		pow_margin04 = 2.0f;	 // 8m
		break;

	case(SR_MOD):
		pow_margin01 = 11.0f;	// 2m
		pow_margin02 = 9.0f;	// 4m
		pow_margin03 = 6.5f;	// 6m
		pow_margin04 = 2.0f;	// 8m
		break;
	}

	for (i = 0; i < DetObj->s16ObjCnt; i++)
	{
/*
#if (OBJ_AE_ADD_OBJ_ENABLE == 1)
		if (DetObj->ObjData[i].s16TrackFlag == 1U)
#else
#endif
*/
		{

			det_r = DetObj->ObjData[i].f32Range;
			det_pow = DetObj->ObjData[i].f32Power;

			if (det_r < GF_CRFT_RANGE_MARGIN1)
			{
				if (det_pow < pow_margin01)
				{
					DetObj->ObjData[i].eGFType = CRFT_FILTER;
				}
			}
			else if (det_r < GF_CRFT_RANGE_MARGIN2)
			{
				if (det_pow < pow_margin02)
				{
					DetObj->ObjData[i].eGFType = CRFT_FILTER;
				}
			}
			else if (det_r < GF_CRFT_RANGE_MARGIN3)
			{
				if (det_pow < pow_margin03)
				{
					DetObj->ObjData[i].eGFType = CRFT_FILTER;
				}
			}
			else if (det_r < GF_CRFT_RANGE_MARGIN4)
			{
				if (det_pow < pow_margin03)
				{
					DetObj->ObjData[i].eGFType = CRFT_FILTER;
				}
			}
			else
			{

			}
		}
	}

}





static void Gf_vGCRFT_Filtering(CalcObjData_t* DetObj, MultiMod_t ModType)
{
	int16_t i, j, m, n, k;
	float32_t det_r;
	float32_t det_v;
	float32_t det_aziang;
	float32_t det_eleang;
	float32_t det_pow;
	float32_t vehicle_input;

	switch (ModType)
	{
	case(LR_MOD):
		break;

	case(MR_MOD):
		break;

	case(SR_MOD):
		break;
	}

	vehicle_input = can_sig_data.vehicle_speed*0.2778f;

	for (i = 0; i < DetObj->s16ObjCnt; i++)
	{
		det_r = DetObj->ObjData[i].f32Range;
		det_v = DetObj->ObjData[i].f32Velocity;
		det_aziang = DetObj->ObjData[i].f32AziAngle;
		det_eleang = DetObj->ObjData[i].f32EleAngle;
		det_pow = DetObj->ObjData[i].f32Power;



		if (( det_r < 6.0f)
			 && (_sp_abs(det_v +vehicle_input) < 2.0f)
		 	 && (det_pow < 12.0f) 
			 && (det_eleang < -5.0f))
		{
			DetObj->ObjData[i].eGFType = CRFT_FILTER;
		}

	}

}