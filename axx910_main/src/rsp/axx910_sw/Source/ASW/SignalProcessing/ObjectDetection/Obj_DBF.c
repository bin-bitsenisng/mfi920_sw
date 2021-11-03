/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Pre_Main.h"
#include "Obj_Main.h"
#include "Obj_DBF.h"

/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
#ifndef CUDA_ACC
static void Obj_vNCI(PreData_t* PreData, BeamData_t* BeamData);
static void Obj_vRefNCI(RefPreData_t* PreData, RefBeamData_t* BeamData);
#endif

extern void Obj_vNCI_cuda(uint32_t num_tx, uint32_t num_rx, uint32_t num_fft_r_half, uint32_t num_fft_d, uint32_t nci_range_init_idx, Cuda_PreData_t* PreData, Cuda_BeamData_t* BeamData);

/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Obj_vDBF(void)
{
#ifdef CUDA_ACC
	Obj_vNCI_cuda(SP_RM_NUM_TX, SP_NUM_RX, SP_RM_NUM_FFT_R_HALF, SP_RM_NUM_FFT_D, OBJ_NCI_RANGE_INIT_IDX_RM, &gRM_PreData, &gRM_BeamData);
	Obj_vNCI_cuda(SP_NUM_TX, SP_NUM_RX, SP_NUM_FFT_R_HALF, SP_NUM_FFT_D, OBJ_NCI_RANGE_INIT_IDX, &gLR_PreData, &gLR_BeamData);
	Obj_vNCI_cuda(SP_NUM_TX, SP_NUM_RX, SP_NUM_FFT_R_HALF, SP_NUM_FFT_D, OBJ_NCI_RANGE_INIT_IDX, &gMR_PreData, &gMR_BeamData);
	Obj_vNCI_cuda(SP_NUM_TX, SP_NUM_RX, SP_NUM_FFT_R_HALF, SP_NUM_FFT_D, OBJ_NCI_RANGE_INIT_IDX, &gSR_PreData, &gSR_BeamData);


	memcpy(gRM_BeamData.f32PowSpectrum_array, gRM_BeamData.f32PowSpectrum, sizeof(float32_t) * SP_RM_NUM_FFT_R_HALF * SP_RM_NUM_FFT_D);
	memcpy(gLR_BeamData.f32PowSpectrum_array, gLR_BeamData.f32PowSpectrum, sizeof(float32_t) * SP_NUM_FFT_R_HALF * SP_NUM_FFT_D);
	memcpy(gMR_BeamData.f32PowSpectrum_array, gMR_BeamData.f32PowSpectrum, sizeof(float32_t) * SP_NUM_FFT_R_HALF * SP_NUM_FFT_D);
	memcpy(gSR_BeamData.f32PowSpectrum_array, gSR_BeamData.f32PowSpectrum, sizeof(float32_t) * SP_NUM_FFT_R_HALF * SP_NUM_FFT_D);
	
#else
	Obj_vRefNCI(&gRM_PreData, &gRM_BeamData);
	Obj_vNCI(&gLR_PreData, &gLR_BeamData);
	Obj_vNCI(&gMR_PreData, &gMR_BeamData);
	Obj_vNCI(&gSR_PreData, &gSR_BeamData);
#endif

#ifdef CUDA_ACC

	/*
	for (int16_t ri = 0; ri < 512*5; ri++)
	{
		printf("%f \n", gRM_BeamData.f32PowSpectrum[ri]);
	}
	*/

#else

	/*
	for (int16_t ri = 0; ri < 5; ri++)
	{
		for (int16_t di = 0; di < 512; di++)
		{
			printf("%f\n", gRM_BeamData.f32PowSpectrum[ri][di]);
		}
	}
	*/
#endif

}


void Obj_vDBF_SysInit(void)
{
	int16_t ri, di;

	for (ri = 0; ri < OBJ_NCI_RANGE_INIT_IDX_RM; ri++)
	{
		for (di = 0; di < OBJ_RM_NUM_FFT_D; di++)
		{
#ifdef CUDA_ACC
			gRM_BeamData.f32PowSpectrum[ri * OBJ_RM_NUM_FFT_D + di] = 0.0f;
#else
			gRM_BeamData.f32PowSpectrum[ri][di] = 0.0f;
#endif
		}
	}




	for (ri = 0; ri < OBJ_NCI_RANGE_INIT_IDX; ri++)
	{
		for (di = 0; di < OBJ_NUM_FFT_D; di++)
		{
#ifdef CUDA_ACC
			gLR_BeamData.f32PowSpectrum[ri * OBJ_NUM_FFT_D + di] = 0.0f;
			gMR_BeamData.f32PowSpectrum[ri * OBJ_NUM_FFT_D + di] = 0.0f;
			gSR_BeamData.f32PowSpectrum[ri * OBJ_NUM_FFT_D + di] = 0.0f;
#else
			gLR_BeamData.f32PowSpectrum[ri][di] = 0.0f;
			gMR_BeamData.f32PowSpectrum[ri][di] = 0.0f;
			gSR_BeamData.f32PowSpectrum[ri][di] = 0.0f;
#endif
		}
	}






}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/

static void Obj_vRefNCI(RefPreData_t* PreData, RefBeamData_t* BeamData)
{
	int16_t ri, di, tx, rx;
	float32_t temp_sum;


	for (ri = OBJ_NCI_RANGE_INIT_IDX; ri < OBJ_RM_NUM_FFT_R; ri++)
	{
		for (di = 0; di < OBJ_RM_NUM_FFT_D; di++)
		{
			temp_sum = 0.0f;
			for (tx = 0; tx < OBJ_RM_NUM_TX; tx++)
			{
				for (rx = 0; rx < OBJ_NUM_RX; rx++)
				{
					temp_sum += _sp_pow2(PreData->cf32fftData_2D[ri][tx][rx][di].real) + _sp_pow2(PreData->cf32fftData_2D[ri][tx][rx][di].imag);
				}
			}
			BeamData->f32PowSpectrum[ri][di] = _sp_sqrtf(temp_sum);		/* sqrt 2~3ms Ãß°¡µÊ */
		}
	}
}



static void Obj_vNCI(PreData_t* PreData, BeamData_t* BeamData)
{
	int16_t ri, di, tx, rx;
	float32_t temp_sum;


	for (ri = OBJ_NCI_RANGE_INIT_IDX; ri < OBJ_NUM_FFT_R; ri++)
	{
		for (di = 0; di < OBJ_NUM_FFT_D; di++)
		{
			temp_sum = 0.0f;
			for (tx = 0; tx < OBJ_NUM_TX; tx++)
			{
				for (rx = 0; rx < OBJ_NUM_RX; rx++)
				{
					temp_sum += _sp_pow2(PreData->cf32fftData_2D[ri][tx][rx][di].real) + _sp_pow2(PreData->cf32fftData_2D[ri][tx][rx][di].imag);
				}
			}
			BeamData->f32PowSpectrum[ri][di] = _sp_sqrtf(temp_sum);		/* sqrt 2~3ms Ãß°¡µÊ */
		}
	}
}
