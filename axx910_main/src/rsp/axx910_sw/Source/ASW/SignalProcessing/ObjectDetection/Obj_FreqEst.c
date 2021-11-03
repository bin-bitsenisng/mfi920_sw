/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Obj_Main.h"
#include "Obj_FreqEst.h"


/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/
//#define _fe_modfn(x)			_sp_sqrtf(x)
#define _fe_modfn(x)			x

/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
#if defined(CUDA_ACC) && !defined(CUDA_ACC)
void Obj_vFreqEstimation_cuda(Cuda_BeamData_t* BeamData, PeakData_t* PeakData, int16_t PeakIdx)
#elif defined(CUDA_ACC) && defined(CUDA_ACC)
void Obj_vFreqEstimation_cuda(Cuda_BeamData_t* BeamData, Cuda_PeakData_t* PeakData, int16_t PeakIdx)
#else
void Obj_vFreqEstimation(BeamData_t *BeamData, PeakData_t *PeakData, int16_t PeakIdx)
#endif
{
	rdidxu16_t freq_idx;
	float32_t y1, y2, y3;
	float32_t num, den;


	freq_idx.R = PeakData->rdu16FreqIdx[PeakIdx].R;
	freq_idx.D = PeakData->rdu16FreqIdx[PeakIdx].D;

	/* R Index != 0 */
#ifdef CUDA_ACC
	y1 = _fe_modfn(BeamData->f32PowSpectrum[(freq_idx.R - 1) * OBJ_NUM_FFT_D + freq_idx.D]);
	y2 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_NUM_FFT_D + freq_idx.D]);
	y3 = _fe_modfn(BeamData->f32PowSpectrum[(freq_idx.R + 1) * OBJ_NUM_FFT_D + freq_idx.D]);
#else
	y1 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R - 1][freq_idx.D]);
	y2 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][freq_idx.D]);
	y3 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R + 1][freq_idx.D]);
#endif

	num = OBJ_FE_CORRECTION_VAL_R * (y3 - y1);
	den = y1 + y2 + y3;

	if ((y2 >= y1) && (y2 >= y3))
	{
		PeakData->rdf32EstFreqIdx[PeakIdx].R = (float32_t)(freq_idx.R) + (num / den);
	}
	else
	{
		PeakData->rdf32EstFreqIdx[PeakIdx].R = (float32_t)(freq_idx.R);
	}


	/* D Index */
	if (freq_idx.D == 0)
	{
#ifdef CUDA_ACC
		y1 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_NUM_FFT_D + OBJ_NUM_FFT_D - 1]);
		
		y2 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_NUM_FFT_D + freq_idx.D]);
		y3 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_NUM_FFT_D + freq_idx.D + 1]);
#else
		y1 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][OBJ_NUM_FFT_D - 1]);
		y2 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][freq_idx.D]);
		y3 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][freq_idx.D + 1]);
#endif
	}
	else if (freq_idx.D == (OBJ_NUM_FFT_D - 1))
	{
#ifdef CUDA_ACC
		y1 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_NUM_FFT_D + freq_idx.D - 1]);
		y2 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_NUM_FFT_D + freq_idx.D]);
		y3 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_NUM_FFT_D + 0]);
#else
		y1 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][freq_idx.D - 1]);
		y2 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][freq_idx.D]);
		y3 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][0]);
#endif
	}
	else
	{
#ifdef CUDA_ACC
		y1 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_NUM_FFT_D + freq_idx.D - 1]);
		y2 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_NUM_FFT_D + freq_idx.D]);
		y3 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_NUM_FFT_D + freq_idx.D + 1]);
#else
		y1 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][freq_idx.D - 1]);
		y2 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][freq_idx.D]);
		y3 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][freq_idx.D + 1]);
#endif
	}

	num = OBJ_FE_CORRECTION_VAL_D * (y3 - y1);
	den = y1 + y2 + y3;

	if ((y2 >= y1) && (y2 >= y3))
	{
		PeakData->rdf32EstFreqIdx[PeakIdx].D = (float32_t)(freq_idx.D) + (num / den);
	}
	else
	{
		PeakData->rdf32EstFreqIdx[PeakIdx].D = (float32_t)(freq_idx.D);
	}

}


#ifdef CUDA_ACC
void Obj_vRefFreqEstimation_cuda(Cuda_RefBeamData_t* BeamData, RefPeakData_t* PeakData, int16_t PeakIdx)
#else
void Obj_vRefFreqEstimation(RefBeamData_t *BeamData, RefPeakData_t *PeakData, int16_t PeakIdx)
#endif
{
	rdidxu16_t freq_idx;
	float32_t y1, y2, y3;
	float32_t num, den;

	freq_idx.R = PeakData->rdu16FreqIdx[PeakIdx].R;
	freq_idx.D = PeakData->rdu16FreqIdx[PeakIdx].D;

	/* R Index != 0 */
#ifdef CUDA_ACC
	y1 = _fe_modfn(BeamData->f32PowSpectrum[(freq_idx.R - 1) * OBJ_RM_NUM_FFT_D + freq_idx.D]);
	y2 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_RM_NUM_FFT_D + freq_idx.D]);
	y3 = _fe_modfn(BeamData->f32PowSpectrum[(freq_idx.R + 1) * OBJ_RM_NUM_FFT_D + freq_idx.D]);
#else
	y1 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R - 1][freq_idx.D]);
	y2 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][freq_idx.D]);
	y3 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R + 1][freq_idx.D]);
#endif
	num = OBJ_FE_CORRECTION_VAL_R * (y3 - y1);
	den = y1 + y2 + y3;

	if ((y2 >= y1) && (y2 >= y3))
	{
		PeakData->rdf32EstFreqIdx[PeakIdx].R = (float32_t)(freq_idx.R) + (num / den);
	}
	else
	{
		PeakData->rdf32EstFreqIdx[PeakIdx].R = (float32_t)(freq_idx.R);
	}


	/* D Index */
	if (freq_idx.D == 0)
	{
#ifdef CUDA_ACC
		y1 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_RM_NUM_FFT_D + OBJ_RM_NUM_FFT_D - 1]);
		y2 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_RM_NUM_FFT_D + freq_idx.D]);
		y3 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_RM_NUM_FFT_D + freq_idx.D + 1]);
#else
		y1 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][OBJ_RM_NUM_FFT_D - 1]);
		y2 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][freq_idx.D]);
		y3 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][freq_idx.D + 1]);
#endif
	}
	else if (freq_idx.D == (OBJ_RM_NUM_FFT_D - 1))
	{
#ifdef CUDA_ACC
		y1 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_RM_NUM_FFT_D + freq_idx.D - 1]);
		y2 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_RM_NUM_FFT_D + freq_idx.D]);
		y3 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_RM_NUM_FFT_D + 0]);
#else
		y1 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][freq_idx.D - 1]);
		y2 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][freq_idx.D]);
		y3 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][0]);
#endif
	}
	else
	{
#ifdef CUDA_ACC
		y1 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_RM_NUM_FFT_D + freq_idx.D - 1]);
		y2 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_RM_NUM_FFT_D + freq_idx.D]);
		y3 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R * OBJ_RM_NUM_FFT_D + freq_idx.D + 1]);
#else
		y1 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][freq_idx.D - 1]);
		y2 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][freq_idx.D]);
		y3 = _fe_modfn(BeamData->f32PowSpectrum[freq_idx.R][freq_idx.D + 1]);
#endif
	}

	num = OBJ_FE_CORRECTION_VAL_D * (y3 - y1);
	den = y1 + y2 + y3;

	if ((y2 >= y1) && (y2 >= y3))
	{
		PeakData->rdf32EstFreqIdx[PeakIdx].D = (float32_t)(freq_idx.D) + (num / den);
	}
	else
	{
		PeakData->rdf32EstFreqIdx[PeakIdx].D = (float32_t)(freq_idx.D);
	}

}


