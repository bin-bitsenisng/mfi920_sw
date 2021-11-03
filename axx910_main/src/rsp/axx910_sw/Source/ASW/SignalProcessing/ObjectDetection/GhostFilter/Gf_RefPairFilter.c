/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Gf_Main.h"
#include "Gf_RefPairFilter.h"

/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
static void Gf_vRefPaifFiltering(CalcObjData_t* Obj, RefCalcObjData_t * RefObj, MultiMod_t ModType);

/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Gf_vRefPairFilter(void)
{
	Gf_vRefPaifFiltering(&gLR_ObjData, &gRM_ObjData, LR_MOD);
	Gf_vRefPaifFiltering(&gMR_ObjData, &gRM_ObjData, MR_MOD);
	Gf_vRefPaifFiltering(&gSR_ObjData, &gRM_ObjData, SR_MOD);
}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/

static void Gf_vRefPaifFiltering(CalcObjData_t* DetObj, RefCalcObjData_t * RefObj, MultiMod_t ModType)
{
	int16_t i, j, m, n, k;
	float32_t det_r;
	float32_t det_v;
	float32_t det_ang;

	float32_t ref_r;
	float32_t ref_v;
	float32_t ref_ang;

	float32_t rp_margin_r;
	float32_t rp_margin_v;
	float32_t rp_margin_ang;
	float32_t rp_margin_pow;

	switch (ModType)
	{
	case(LR_MOD):
		rp_margin_r = GF_RPF_PAIR_MARGIN_LR_R;
		rp_margin_v = GF_RPF_PAIR_MARGIN_LR_V;
		//rp_margin_ang = GF_RPF_PAIR_MARGIN_LR_ANG;
;		rp_margin_pow = GF_RPF_PAIR_MARGIN_LR_POW;
		break;

	case(MR_MOD):
		rp_margin_r = GF_RPF_PAIR_MARGIN_MR_R;
		rp_margin_v = GF_RPF_PAIR_MARGIN_MR_V;
		//rp_margin_ang = GF_RPF_PAIR_MARGIN_MR_ANG;
		rp_margin_pow = GF_RPF_PAIR_MARGIN_MR_POW;
		break;

	case(SR_MOD):
		rp_margin_r = GF_RPF_PAIR_MARGIN_SR_R;
		rp_margin_v = GF_RPF_PAIR_MARGIN_SR_V;
		//rp_margin_ang = GF_RPF_PAIR_MARGIN_MR_ANG;
		rp_margin_pow = GF_RPF_PAIR_MARGIN_SR_POW;
		break;
	}

	rp_margin_ang = 0.0f;
	for (i = 0; i < DetObj->s16ObjCnt; i++)
	{
		det_r = DetObj->ObjData[i].f32Range;
		det_v = DetObj->ObjData[i].f32Velocity;
		det_ang = DetObj->ObjData[i].f32AziAngle;

		if (DetObj->ObjData[i].eGFType == AMBIGUOUS_VEL)
		{

			if ((det_r >= 0.0f) && (det_r < 45.0f))
			{
				rp_margin_ang = 4.0f;
			}
			else if ((det_r >= 45.0f) && (det_r < 95.0f))
			{
				rp_margin_ang = 6.0f;
			}
			else if (det_r >= 100.0f)
			{
				rp_margin_ang = 8.0f;
			}
			else
			{

			}

			for (j = 0; j < RefObj->s16ObjCnt; j++)
			{
				if (RefObj->ObjData[j].eGFType == NOT_GHOST)
				{
					ref_r = RefObj->ObjData[j].f32Range;
					ref_v = RefObj->ObjData[j].f32Velocity;
					ref_ang = RefObj->ObjData[j].f32AziAngle;

					if (_sp_abs(det_r - ref_r) < GF_RPF_PAIR_MARGIN_R_ROUGH)
					{
						if ((_sp_abs(det_r - ref_r) < rp_margin_r)
							&& (_sp_abs(det_v - ref_v) < rp_margin_v)
							&& (_sp_abs(det_ang - ref_ang) < rp_margin_ang))
						{
							DetObj->ObjData[i].eGFType = NOT_GHOST;
							break;
						}

						if ((ModType == SR_MOD)
							&& (det_r < 8.0f)
							&& (DetObj->ObjData[i].f32Power > 2.0f))
						{
							if ((DetObj->ObjData[i].rdu16FreqIdx.D == 0U)
								&& (_sp_abs(det_r - ref_r) < 3.0f))
							{
								DetObj->ObjData[i].eGFType = NOT_GHOST;
								break;
							}
						}
					}
				}
			}
		}
	}
}
