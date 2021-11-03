/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Pre_Main.h"
#include "Obj_Main.h"
#include "Obj_FreqEst.h"
#include "bts_cfarlib.h"
#include "Obj_CFAR.h"

#ifdef CUDA_ACC
#include "Cuda_bts_lib.cuh"
#endif

/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/
CfarCfg_t RM_RangeCfarCfg;
CfarCfg_t RM_DopplerCfarCfg;

CfarCfg_t LR_RangeCfarCfg;
CfarCfg_t LR_DopplerCfarCfg;

CfarCfg_t MR_RangeCfarCfg;
CfarCfg_t MR_DopplerCfarCfg;

CfarCfg_t SR_RangeCfarCfg;
CfarCfg_t SR_DopplerCfarCfg;

/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
#if defined(CUDA_ACC) && !defined(CUDA_ACC)
static void Obj_vRangeCfar_cuda(Cuda_BeamData_t* BeamData, CfarCfg_t* cfg);
static void Obj_vDopplerCfar_cuda(Cuda_BeamData_t* BeamData, CfarCfg_t* cfg);
static void Obj_vSelectionPeak_cuda(Cuda_PreData_t* PreData, Cuda_BeamData_t* BeamData, PeakData_t* PeakData, int16_t MinIdx);

static void Obj_vRangeRefCfar_cuda(Cuda_RefBeamData_t* BeamData, CfarCfg_t* cfg);
static void Obj_vDopplerRefCfar_cuda(Cuda_RefBeamData_t* BeamData, CfarCfg_t* cfg);
static void Obj_vSelectionRefPeak_cuda(Cuda_RefPreData_t* PreData, Cuda_RefBeamData_t* BeamData, RefPeakData_t* PeakData, int16_t MinIdx);
#elif defined(CUDA_ACC) && defined(CUDA_ACC)
static void Obj_vRangeCfar_cuda(Cuda_BeamData_t* BeamData, CfarCfg_t* cfg);
static void Obj_vDopplerCfar_cuda(Cuda_BeamData_t* BeamData, CfarCfg_t* cfg);
static void Obj_vSelectionPeak_cuda(Cuda_PreData_t* PreData, Cuda_BeamData_t* BeamData, Cuda_PeakData_t* PeakData, int16_t MinIdx, int16_t MaxIdx, int16_t PeakMax);

static void Obj_vRangeRefCfar_cuda(Cuda_RefBeamData_t* BeamData, CfarCfg_t* cfg);
static void Obj_vDopplerRefCfar_cuda(Cuda_RefBeamData_t* BeamData, CfarCfg_t* cfg);
static void Obj_vSelectionRefPeak_cuda(Cuda_RefPreData_t* PreData, Cuda_RefBeamData_t* BeamData, RefPeakData_t* PeakData, int16_t MinIdx, int16_t MaxIdx);
#else
static void Obj_vRangeCfar(BeamData_t* BeamData, CfarCfg_t* cfg);
static void Obj_vDopplerCfar(BeamData_t* BeamData, CfarCfg_t* cfg);
static void Obj_vSelectionPeak(PreData_t* PreData, BeamData_t* BeamData, PeakData_t* PeakData, int16_t MinIdx, int16_t MaxIdx);

static void Obj_vRangeRefCfar(RefBeamData_t* BeamData, CfarCfg_t* cfg);
static void Obj_vDopplerRefCfar(RefBeamData_t* BeamData, CfarCfg_t* cfg);
static void Obj_vSelectionRefPeak(RefPreData_t* PreData, RefBeamData_t* BeamData, RefPeakData_t* PeakData, int16_t MinIdx, int16_t MaxIdx);
#endif

/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Obj_vCFAR_SysInit(void)
{
	/* CFAR Configuration */
	RM_RangeCfarCfg.eExtsType			= RANGE_EXTENSION;
	RM_RangeCfarCfg.eCfarType			= CA_CFAR;
	RM_RangeCfarCfg.u16NumCells		= OBJ_RM_NUM_FFT_R - OBJ_NCI_RANGE_INIT_IDX_RM;
	RM_RangeCfarCfg.u8GuardCells		= OBJ_CFAR_RM_NUM_GUARD_CELL_R;
	RM_RangeCfarCfg.u8RefCells			= OBJ_CFAR_RM_NUM_REF_CELL_HALF_R;
	RM_RangeCfarCfg.u8ExtsSize			= OBJ_CFAR_RM_NUM_EXTEN_CELL_R;
	RM_RangeCfarCfg.u8KthOrder			= OBJ_CFAR_RM_OSCFAR_KTH_ORDER_R;
	RM_RangeCfarCfg.f32Alpha				= OBJ_CFAR_RM_THRESHOLD_ALPHA_R * (float)1 / OBJ_CFAR_RM_NUM_REF_CELL_HALF_R * 0.5f;
	RM_RangeCfarCfg.f32BaseTh			= OBJ_CFAR_RM_BASE_THRESHOLD_R;

	RM_DopplerCfarCfg.eExtsType			= DOPP_EXTENSION;
	RM_DopplerCfarCfg.eCfarType			= CA_CFAR;
	RM_DopplerCfarCfg.u16NumCells		= OBJ_RM_NUM_FFT_D;
	RM_DopplerCfarCfg.u8GuardCells		= OBJ_CFAR_RM_NUM_GUARD_CELL_D;
	RM_DopplerCfarCfg.u8RefCells			= OBJ_CFAR_RM_NUM_REF_CELL_HALF_D;
	RM_DopplerCfarCfg.u8ExtsSize			= OBJ_CFAR_RM_NUM_EXTEN_CELL_D;
	RM_DopplerCfarCfg.u8KthOrder		= 0;
	RM_DopplerCfarCfg.f32Alpha			= OBJ_CFAR_RM_THRESHOLD_ALPHA_D * (float)1 / OBJ_CFAR_RM_NUM_REF_CELL_HALF_D * 0.5f;
	RM_DopplerCfarCfg.f32BaseTh			= OBJ_CFAR_RM_BASE_THRESHOLD_D;

	LR_RangeCfarCfg.eCfarType				= CA_CFAR;
	LR_RangeCfarCfg.eExtsType				= RANGE_EXTENSION;
	LR_RangeCfarCfg.u16NumCells			= OBJ_NUM_FFT_R - OBJ_NCI_RANGE_INIT_IDX;
	LR_RangeCfarCfg.u8GuardCells			= OBJ_CFAR_LR_NUM_GUARD_CELL_R;
	LR_RangeCfarCfg.u8RefCells				= OBJ_CFAR_LR_NUM_REF_CELL_HALF_R;
	LR_RangeCfarCfg.u8ExtsSize				= OBJ_CFAR_LR_NUM_EXTEN_CELL_R;
	LR_RangeCfarCfg.u8KthOrder			= OBJ_CFAR_LR_OSCFAR_KTH_ORDER_R;
	LR_RangeCfarCfg.f32Alpha				= OBJ_CFAR_LR_THRESHOLD_ALPHA_R * (float)1 / OBJ_CFAR_LR_NUM_REF_CELL_HALF_R * 0.5f;
	LR_RangeCfarCfg.f32BaseTh				= OBJ_CFAR_LR_BASE_THRESHOLD_R;

	LR_DopplerCfarCfg.eCfarType			= GOS_CFAR;
	LR_DopplerCfarCfg.eExtsType			= DOPP_EXTENSION;
	LR_DopplerCfarCfg.u16NumCells		= OBJ_NUM_FFT_D;
	LR_DopplerCfarCfg.u8GuardCells		= OBJ_CFAR_LR_NUM_GUARD_CELL_D;
	LR_DopplerCfarCfg.u8RefCells			= OBJ_CFAR_LR_NUM_REF_CELL_HALF_D;
	LR_DopplerCfarCfg.u8ExtsSize			= OBJ_CFAR_LR_NUM_EXTEN_CELL_D;
	LR_DopplerCfarCfg.u8KthOrder			= OBJ_CFAR_LR_OSCFAR_KTH_ORDER_D;
	LR_DopplerCfarCfg.f32BaseTh			= OBJ_CFAR_LR_BASE_THRESHOLD_D;

	if (LR_DopplerCfarCfg.eCfarType == CA_CFAR)
	{
		LR_DopplerCfarCfg.f32Alpha		= OBJ_CFAR_LR_THRESHOLD_ALPHA_D * (float)1 / OBJ_CFAR_LR_NUM_REF_CELL_HALF_D * 0.5f;
	}
	else if (LR_DopplerCfarCfg.eCfarType == GOS_CFAR)
	{
		LR_DopplerCfarCfg.f32Alpha		= OBJ_CFAR_LR_THRESHOLD_ALPHA_D;
	}
	else
	{

	}
	
	MR_RangeCfarCfg.eCfarType			= CA_CFAR;
	MR_RangeCfarCfg.eExtsType			= RANGE_EXTENSION;
	MR_RangeCfarCfg.u16NumCells		= OBJ_NUM_FFT_R - OBJ_NCI_RANGE_INIT_IDX;
	MR_RangeCfarCfg.u8GuardCells		= OBJ_CFAR_MR_NUM_GUARD_CELL_R;
	MR_RangeCfarCfg.u8RefCells			= OBJ_CFAR_MR_NUM_REF_CELL_HALF_R;
	MR_RangeCfarCfg.u8ExtsSize			= OBJ_CFAR_MR_NUM_EXTEN_CELL_R;
	MR_RangeCfarCfg.u8KthOrder			= OBJ_CFAR_MR_OSCFAR_KTH_ORDER_R;
	MR_RangeCfarCfg.f32Alpha				= OBJ_CFAR_MR_THRESHOLD_ALPHA_R * (float)1 / OBJ_CFAR_MR_NUM_REF_CELL_HALF_R * 0.5f;
	MR_RangeCfarCfg.f32BaseTh			= OBJ_CFAR_MR_BASE_THRESHOLD_R;

	MR_DopplerCfarCfg.eCfarType			= GOS_CFAR;
	MR_DopplerCfarCfg.eExtsType			= DOPP_EXTENSION;
	MR_DopplerCfarCfg.u16NumCells		= OBJ_NUM_FFT_D;
	MR_DopplerCfarCfg.u8GuardCells		= OBJ_CFAR_MR_NUM_GUARD_CELL_D;
	MR_DopplerCfarCfg.u8RefCells			= OBJ_CFAR_MR_NUM_REF_CELL_HALF_D;
	MR_DopplerCfarCfg.u8ExtsSize			= OBJ_CFAR_MR_NUM_EXTEN_CELL_D;
	MR_DopplerCfarCfg.u8KthOrder		= OBJ_CFAR_MR_OSCFAR_KTH_ORDER_D;
	MR_DopplerCfarCfg.f32BaseTh			= OBJ_CFAR_MR_BASE_THRESHOLD_D;

	if (MR_DopplerCfarCfg.eCfarType == CA_CFAR)
	{
		MR_DopplerCfarCfg.f32Alpha = OBJ_CFAR_MR_THRESHOLD_ALPHA_D * (float32_t)1 / OBJ_CFAR_MR_NUM_REF_CELL_HALF_D * 0.5f;
	}
	else if (MR_DopplerCfarCfg.eCfarType == GOS_CFAR)
	{
		MR_DopplerCfarCfg.f32Alpha = OBJ_CFAR_MR_THRESHOLD_ALPHA_D;
	}
	else
	{

	}

	SR_RangeCfarCfg.eCfarType				= CA_CFAR;
	SR_RangeCfarCfg.eExtsType				= RANGE_EXTENSION;
	SR_RangeCfarCfg.u16NumCells			= OBJ_NUM_FFT_R - OBJ_NCI_RANGE_INIT_IDX;
	SR_RangeCfarCfg.u8GuardCells			= OBJ_CFAR_SR_NUM_GUARD_CELL_R;
	SR_RangeCfarCfg.u8RefCells			= OBJ_CFAR_SR_NUM_REF_CELL_HALF_R;
	SR_RangeCfarCfg.u8ExtsSize			= OBJ_CFAR_SR_NUM_EXTEN_CELL_R;
	SR_RangeCfarCfg.u8KthOrder			= OBJ_CFAR_SR_OSCFAR_KTH_ORDER_R;
	SR_RangeCfarCfg.f32Alpha				= OBJ_CFAR_SR_THRESHOLD_ALPHA_R * (float32_t)1 / OBJ_CFAR_SR_NUM_REF_CELL_HALF_R * 0.5f;
	SR_RangeCfarCfg.f32BaseTh				= OBJ_CFAR_SR_BASE_THRESHOLD_R;

	SR_DopplerCfarCfg.eCfarType			= GOS_CFAR;
	SR_DopplerCfarCfg.eExtsType			= DOPP_EXTENSION;
	SR_DopplerCfarCfg.u16NumCells		= OBJ_NUM_FFT_D;
	SR_DopplerCfarCfg.u8GuardCells		= OBJ_CFAR_SR_NUM_GUARD_CELL_D;
	SR_DopplerCfarCfg.u8RefCells			= OBJ_CFAR_SR_NUM_REF_CELL_HALF_D;
	SR_DopplerCfarCfg.u8ExtsSize			= OBJ_CFAR_SR_NUM_EXTEN_CELL_D;
	SR_DopplerCfarCfg.u8KthOrder		= OBJ_CFAR_SR_OSCFAR_KTH_ORDER_D;
	SR_DopplerCfarCfg.f32BaseTh			= OBJ_CFAR_SR_BASE_THRESHOLD_D;


	if (SR_DopplerCfarCfg.eCfarType == CA_CFAR)
	{
		SR_DopplerCfarCfg.f32Alpha = OBJ_CFAR_SR_THRESHOLD_ALPHA_D * (float32_t)1 / OBJ_CFAR_SR_NUM_REF_CELL_HALF_D * 0.5f;
	}
	else if (SR_DopplerCfarCfg.eCfarType == GOS_CFAR)
	{
		SR_DopplerCfarCfg.f32Alpha = OBJ_CFAR_SR_THRESHOLD_ALPHA_D;
	}
	else
	{

	}

	for (int16_t i = 0; i < CFARLIB_CFAREXTSCELL_MAX; i++)
	{
		RM_RangeCfarCfg.f32AccumSum[i]		= 0.f;
		RM_DopplerCfarCfg.f32AccumSum[i]		= 0.f;
		LR_RangeCfarCfg.f32AccumSum[i]			= 0.f;
		LR_DopplerCfarCfg.f32AccumSum[i]		= 0.f;
		MR_RangeCfarCfg.f32AccumSum[i]		= 0.f;
		MR_DopplerCfarCfg.f32AccumSum[i]		= 0.f;
		SR_RangeCfarCfg.f32AccumSum[i]			= 0.f;
		SR_DopplerCfarCfg.f32AccumSum[i]		= 0.f;
	}
}


void Obj_vCFAR(void)
{
#ifdef LINUX
	struct timeval startTime, endTime;
	double diffTime;
#endif

#ifdef CUDA_ACC
	//Obj_vRangeRefCfar_cuda(&gRM_BeamData, &RM_RangeCfarCfg);
	//Obj_vRangeCfar_cuda(&gLR_BeamData, &LR_RangeCfarCfg);
	//Obj_vRangeCfar_cuda(&gMR_BeamData, &MR_RangeCfarCfg);
	//Obj_vRangeCfar_cuda(&gSR_BeamData, &SR_RangeCfarCfg);
#if WIN32
	if (gPeakMode == 0)
	{
		Obj_vDopplerRefCfar_cuda(&gRM_BeamData, &RM_DopplerCfarCfg);
		Obj_vDopplerCfar_cuda(&gLR_BeamData, &LR_DopplerCfarCfg);
		Obj_vDopplerCfar_cuda(&gMR_BeamData, &MR_DopplerCfarCfg);
		Obj_vDopplerCfar_cuda(&gSR_BeamData, &SR_DopplerCfarCfg);

		Obj_vSelectionRefPeak_cuda(&gRM_PreData, &gRM_BeamData, &gRM_PeakData, OBJ_CFAR_RM_R_IDX_MIN, OBJ_CFAR_RM_R_IDX_MAX);
		Obj_vSelectionPeak_cuda(&gLR_PreData, &gLR_BeamData, &gLR_PeakData, OBJ_CFAR_LR_R_IDX_MIN, OBJ_CFAR_LR_R_IDX_MAX, OBJ_NUM_LR_PEAK_MAX);
		Obj_vSelectionPeak_cuda(&gMR_PreData, &gMR_BeamData, &gMR_PeakData, OBJ_CFAR_MR_R_IDX_MIN, OBJ_CFAR_MR_R_IDX_MAX, OBJ_NUM_MR_PEAK_MAX);
		Obj_vSelectionPeak_cuda(&gSR_PreData, &gSR_BeamData, &gSR_PeakData, OBJ_CFAR_SR_R_IDX_MIN, OBJ_CFAR_SR_R_IDX_MAX, OBJ_NUM_SR_PEAK_MAX);
	}
	else
	{
		Obj_vDopplerRefCfar_cuda(&gRM_BeamData, &RM_DopplerCfarCfg);
		Obj_vDopplerCfar_cuda(&gLR_BeamData, &LR_DopplerCfarCfg);
		Obj_vDopplerCfar_cuda(&gMR_BeamData, &MR_DopplerCfarCfg);
		Obj_vDopplerCfar_cuda(&gSR_BeamData, &SR_DopplerCfarCfg);
	}
#else

	Obj_vDopplerRefCfar_cuda(&gRM_BeamData, &RM_DopplerCfarCfg);
	Obj_vDopplerCfar_cuda(&gLR_BeamData, &LR_DopplerCfarCfg);
	Obj_vDopplerCfar_cuda(&gMR_BeamData, &MR_DopplerCfarCfg);
	Obj_vDopplerCfar_cuda(&gSR_BeamData, &SR_DopplerCfarCfg);

	Obj_vSelectionRefPeak_cuda(&gRM_PreData, &gRM_BeamData, &gRM_PeakData, OBJ_CFAR_RM_R_IDX_MIN, OBJ_CFAR_RM_R_IDX_MAX);
	Obj_vSelectionPeak_cuda(&gLR_PreData, &gLR_BeamData, &gLR_PeakData, OBJ_CFAR_LR_R_IDX_MIN, OBJ_CFAR_LR_R_IDX_MAX, OBJ_NUM_LR_PEAK_MAX);
	Obj_vSelectionPeak_cuda(&gMR_PreData, &gMR_BeamData, &gMR_PeakData, OBJ_CFAR_MR_R_IDX_MIN, OBJ_CFAR_MR_R_IDX_MAX, OBJ_NUM_MR_PEAK_MAX);
	Obj_vSelectionPeak_cuda(&gSR_PreData, &gSR_BeamData, &gSR_PeakData, OBJ_CFAR_SR_R_IDX_MIN, OBJ_CFAR_SR_R_IDX_MAX, OBJ_NUM_SR_PEAK_MAX);

#endif

#else
	//Obj_vRangeRefCfar(&gRM_BeamData, &RM_RangeCfarCfg);
	Obj_vDopplerRefCfar(&gRM_BeamData, &RM_DopplerCfarCfg);
	Obj_vSelectionRefPeak(&gRM_PreData, &gRM_BeamData, &gRM_PeakData, OBJ_CFAR_RM_R_IDX_MIN, OBJ_CFAR_RM_R_IDX_MAX);

	//Obj_vRangeCfar(&gLR_BeamData, &LR_RangeCfarCfg);
	Obj_vDopplerCfar(&gLR_BeamData, &LR_DopplerCfarCfg);
	Obj_vSelectionPeak(&gLR_PreData, &gLR_BeamData, &gLR_PeakData, OBJ_CFAR_LR_R_IDX_MIN, OBJ_CFAR_LR_R_IDX_MAX);

	//Obj_vRangeCfar(&gMR_BeamData, &MR_RangeCfarCfg);
	Obj_vDopplerCfar(&gMR_BeamData, &MR_DopplerCfarCfg);
	Obj_vSelectionPeak(&gMR_PreData, &gMR_BeamData, &gMR_PeakData, OBJ_CFAR_MR_R_IDX_MIN, OBJ_CFAR_MR_R_IDX_MAX);

	//Obj_vRangeCfar(&gSR_BeamData, &SR_RangeCfarCfg);
	Obj_vDopplerCfar(&gSR_BeamData, &SR_DopplerCfarCfg);
	Obj_vSelectionPeak(&gSR_PreData, &gSR_BeamData, &gSR_PeakData, OBJ_CFAR_SR_R_IDX_MIN, OBJ_CFAR_SR_R_IDX_MAX);
#endif
}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
#ifdef CUDA_ACC
static void Obj_vRangeCfar_cuda(Cuda_BeamData_t* BeamData, CfarCfg_t* cfg)
#else
static void Obj_vRangeCfar(BeamData_t* BeamData, CfarCfg_t* cfg)
#endif
{
	int16_t i, di;
	for (i = 0; i < (2 * cfg->u8ExtsSize + cfg->u16NumCells + 1); i++)
	{
		cfg->f32AccumSum[i] = 0.f;
	}
	for (di = 0; di < OBJ_NUM_FFT_D; di++)
	{
#ifdef CUDA_ACC
		cfarlib_vCA_cfar_range(&BeamData->f32PowSpectrum[OBJ_NCI_RANGE_INIT_IDX * OBJ_NUM_FFT_D + di], &BeamData->u8CfarOut_R[di], cfg, cfg->f32AccumSum, OBJ_NUM_FFT_D, &BeamData->f32CfarTh_R[di], OBJ_NCI_RANGE_INIT_IDX);
#else
		cfarlib_vCA_cfar_range(&BeamData->f32PowSpectrum[OBJ_NCI_RANGE_INIT_IDX][di], &BeamData->u8CfarOut_R[di], cfg, cfg->f32AccumSum, OBJ_NUM_FFT_D, &BeamData->f32CfarTh_R[di], OBJ_NCI_RANGE_INIT_IDX);
#endif
	}
}

#ifdef CUDA_ACC
static void Obj_vDopplerCfar_cuda(Cuda_BeamData_t* BeamData, CfarCfg_t* cfg)
#else
static void Obj_vDopplerCfar(BeamData_t* BeamData, CfarCfg_t* cfg)
#endif
{
	int16_t i, ri;
	float32_t ri_norm_temp;

	
	for (i = 0; i < (2 * cfg->u8ExtsSize + cfg->u16NumCells + 1); i++)
	{
		cfg->f32AccumSum[i] = 0.f;
	}
	

	for (ri = OBJ_NCI_RANGE_INIT_IDX; ri < OBJ_NUM_FFT_R - 1; ri++)
	{
		ri_norm_temp = ((float32_t)ri * (1.0f / (float32_t)OBJ_NUM_FFT_R));

#ifdef CUDA_ACC
		if (cfg->eCfarType == CA_CFAR)
			cfarlib_vCA_cfar_doppler(&(BeamData->f32PowSpectrum[ri * OBJ_NUM_FFT_D]), BeamData->u8CfarOut_D[ri], cfg, cfg->f32AccumSum, OBJ_NUM_FFT_D, BeamData->f32CfarTh_D[ri], OBJ_NCI_RANGE_INIT_IDX, ri_norm_temp);
		else if (cfg->eCfarType == GOS_CFAR)
		{
			cfarlib_vOS_cfar_doppler(&(BeamData->f32PowSpectrum[ri * OBJ_NUM_FFT_D]), BeamData->u8CfarOut_D[ri], cfg, BeamData->f32CfarTh_D[ri]);
		}
		else
		{

		}
#else
		cfarlib_vCA_cfar_doppler(&(BeamData->f32PowSpectrum[ri]), BeamData->u8CfarOut_D[ri], cfg, cfg->f32AccumSum, OBJ_NUM_FFT_D, BeamData->f32CfarTh_D[ri], OBJ_NCI_RANGE_INIT_IDX);
#endif
	}
}

#if defined(CUDA_ACC) && !defined(CUDA_ACC)
static void Obj_vSelectionPeak_cuda(Cuda_PreData_t* PreData, Cuda_BeamData_t* BeamData, PeakData_t* PeakData, int16_t MinIdx)
#elif defined(CUDA_ACC) && defined(CUDA_ACC)
static void Obj_vSelectionPeak_cuda(Cuda_PreData_t* PreData, Cuda_BeamData_t* BeamData, Cuda_PeakData_t* PeakData, int16_t MinIdx, int16_t MaxIdx, int16_t PeakMax)
#else
static void Obj_vSelectionPeak(PreData_t* PreData, BeamData_t* BeamData, PeakData_t* PeakData, int16_t MinIdx, int16_t MaxIdx)
#endif
{
	int16_t ri, di, tx, rx;
	int temp_idx = 0;

	PeakData->s16PeakCnt = 0;
	for (ri = MinIdx; ri < MaxIdx - 1; ri++)
	{
		for (di = 0; di < OBJ_NUM_FFT_D; di++)
		{
			_sp_cnt_break(PeakData->s16PeakCnt, PeakMax);

			if (BeamData->u8CfarOut_D[ri][di])
			{
				PeakData->rdu16FreqIdx[PeakData->s16PeakCnt].R = ri;
				PeakData->rdu16FreqIdx[PeakData->s16PeakCnt].D = di;
				PeakData->f32SllPow[PeakData->s16PeakCnt] = BeamData->f32PowSpectrum[ri * OBJ_NUM_FFT_D + di];
				
				for (tx = 0; tx < OBJ_NUM_TX; tx++)
				{
					for (rx = 0; rx < OBJ_NUM_RX; rx++)
					{

#ifdef CUDA_ACC
						temp_idx = (tx * OBJ_NUM_RX + rx) * OBJ_NUM_FFT_D * (OBJ_NUM_FFT_R + 1) + di * (OBJ_NUM_FFT_R + 1) + ri;

						PeakData->cf32FFTData[PeakData->s16PeakCnt][tx][rx].real = PreData->cf32fftData_2D[temp_idx].real;
						PeakData->cf32FFTData[PeakData->s16PeakCnt][tx][rx].imag = PreData->cf32fftData_2D[temp_idx].imag;
#else
						PeakData->cf32FFTData[PeakData->s16PeakCnt][tx][rx].real = PreData->cf32fftData_2D[ri][tx][rx][di].real;
						PeakData->cf32FFTData[PeakData->s16PeakCnt][tx][rx].imag = PreData->cf32fftData_2D[ri][tx][rx][di].imag;
#endif

					}
				}

#ifdef CUDA_ACC
				Obj_vFreqEstimation_cuda(BeamData, PeakData, PeakData->s16PeakCnt);
#else
				Obj_vFreqEstimation(BeamData, PeakData, PeakData->s16PeakCnt);
#endif
				PeakData->s16PeakCnt++;
			}
		}
	}
}

#ifdef CUDA_ACC
static void Obj_vSelectionRefPeak_cuda(Cuda_RefPreData_t* PreData, Cuda_RefBeamData_t* BeamData, RefPeakData_t* PeakData, int16_t MinIdx, int16_t MaxIdx)
#else
static void Obj_vSelectionRefPeak(RefPreData_t* PreData, RefBeamData_t* BeamData, RefPeakData_t* PeakData, int16_t MinIdx, int16_t MaxIdx)
#endif
{
	int16_t ri, di, tx, rx;
	int temp_idx = 0;

	PeakData->s16PeakCnt = 0;
	for (ri = MinIdx; ri < MaxIdx - 1; ri++)
	{
		
		for (di = 0; di < OBJ_RM_NUM_FFT_D; di++)
		{
			_sp_cnt_break(PeakData->s16PeakCnt, OBJ_NUM_RM_PEAK_MAX);

			
			if (BeamData->u8CfarOut_D[ri][di])
			{
				PeakData->rdu16FreqIdx[PeakData->s16PeakCnt].R = ri;
				PeakData->rdu16FreqIdx[PeakData->s16PeakCnt].D = di;

				for (tx = 0; tx < OBJ_RM_NUM_TX; tx++)
				{
					for (rx = 0; rx < OBJ_NUM_RX; rx++)
					{
#ifdef CUDA_ACC
						temp_idx = (tx * OBJ_NUM_RX + rx) * OBJ_RM_NUM_FFT_D * (OBJ_RM_NUM_FFT_R + 1) + di * (OBJ_RM_NUM_FFT_R + 1) + ri;

						PeakData->cf32FFTData[PeakData->s16PeakCnt][tx][rx].real = PreData->cf32fftData_2D[temp_idx].real;
						PeakData->cf32FFTData[PeakData->s16PeakCnt][tx][rx].imag = PreData->cf32fftData_2D[temp_idx].imag;
#else
						PeakData->cf32FFTData[PeakData->s16PeakCnt][tx][rx].real = PreData->cf32fftData_2D[ri][tx][rx][di].real;
						PeakData->cf32FFTData[PeakData->s16PeakCnt][tx][rx].imag = PreData->cf32fftData_2D[ri][tx][rx][di].imag;
#endif
					}
				}

#ifdef CUDA_ACC
				Obj_vRefFreqEstimation_cuda(BeamData, PeakData, PeakData->s16PeakCnt);
#else
				Obj_vRefFreqEstimation(BeamData, PeakData, PeakData->s16PeakCnt);
#endif
				PeakData->s16PeakCnt++;
			}
		}
	}
}

#ifdef CUDA_ACC
static void Obj_vRangeRefCfar_cuda(Cuda_RefBeamData_t* BeamData, CfarCfg_t* cfg)
#else
static void Obj_vRangeRefCfar(RefBeamData_t* BeamData, CfarCfg_t* cfg)
#endif
{
	int16_t i, di;
	for (i = 0; i < (2 * cfg->u8ExtsSize + cfg->u16NumCells + 1); i++)
	{
		cfg->f32AccumSum[i] = 0.f;
	}
	for (di = 0; di < OBJ_RM_NUM_FFT_D; di++)
	{
#ifdef CUDA_ACC
		cfarlib_vCA_cfar_range(&BeamData->f32PowSpectrum[OBJ_NCI_RANGE_INIT_IDX_RM * OBJ_RM_NUM_FFT_D + di], &BeamData->u8CfarOut_R[di], cfg, cfg->f32AccumSum, OBJ_RM_NUM_FFT_D, &BeamData->f32CfarTh_R[di], OBJ_NCI_RANGE_INIT_IDX_RM);
#else
		cfarlib_vCA_cfar_range(&BeamData->f32PowSpectrum[OBJ_NCI_RANGE_INIT_IDX][di], &BeamData->u8CfarOut_R[di], cfg, cfg->f32AccumSum, OBJ_RM_NUM_FFT_D, &BeamData->f32CfarTh_R[di], OBJ_NCI_RANGE_INIT_IDX);
#endif
	}
}

#ifdef CUDA_ACC
static void Obj_vDopplerRefCfar_cuda(Cuda_RefBeamData_t* BeamData, CfarCfg_t* cfg)
#else
static void Obj_vDopplerRefCfar(RefBeamData_t* BeamData, CfarCfg_t* cfg)
#endif
{
	int16_t i, ri;
	float32_t ri_norm_temp;
	for (i = 0; i < (2 * cfg->u8ExtsSize + cfg->u16NumCells + 1); i++)
	{
		cfg->f32AccumSum[i] = 0.f;
	}
	for (ri = OBJ_NCI_RANGE_INIT_IDX_RM; ri < OBJ_RM_NUM_FFT_R; ri++)
	{
		ri_norm_temp = ((float32_t)ri * (1.0f / (float32_t)OBJ_RM_NUM_FFT_R));
#ifdef CUDA_ACC
		cfarlib_vCA_cfar_doppler(&(BeamData->f32PowSpectrum[ri * OBJ_RM_NUM_FFT_D]), BeamData->u8CfarOut_D[ri], cfg, cfg->f32AccumSum, OBJ_RM_NUM_FFT_D, BeamData->f32CfarTh_D[ri], OBJ_NCI_RANGE_INIT_IDX_RM, ri_norm_temp);
#else
		cfarlib_vCA_cfar_doppler(&(BeamData->f32PowSpectrum[ri]), BeamData->u8CfarOut_D[ri], cfg, cfg->f32AccumSum, OBJ_RM_NUM_FFT_D, BeamData->f32CfarTh_D[ri], OBJ_NCI_RANGE_INIT_IDX);

#endif
	}
}

