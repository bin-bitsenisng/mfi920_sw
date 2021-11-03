/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Pre_Main.h"
#include "Pre_fft.h"
#ifdef CUDA_ACC
#include "Cuda_bts_lib.cuh"
#endif

/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
static void Pre_vRangefft(PreData_t* PreData, PreWindow_t* Window);
static void Pre_vDopplerfft(PreData_t* PreData, PreWindow_t* Window);

static void Pre_vRefRangefft(RefPreData_t* PreData, RefPreWindow_t * Window);
static void Pre_vRefDopplerfft(RefPreData_t* PreData, RefPreWindow_t * Window);

/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Pre_vFFT(void)
{
#ifdef CUDA_ACC
	fft_2d_cuda();
#else
	Pre_vRefRangefft(&gRM_PreData, &gRM_PreWindow);
	Pre_vRefDopplerfft(&gRM_PreData, &gRM_PreWindow);

	Pre_vRangefft(&gLR_PreData, &gLR_PreWindow);
	Pre_vRangefft(&gMR_PreData, &gMR_PreWindow);
	Pre_vRangefft(&gSR_PreData, &gSR_PreWindow);

	Pre_vDopplerfft(&gLR_PreData, &gLR_PreWindow);
	Pre_vDopplerfft(&gMR_PreData, &gMR_PreWindow);
	Pre_vDopplerfft(&gSR_PreData, &gSR_PreWindow);
#endif
}

#ifndef CUDA_ACC
/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
static void Pre_vRangefft(PreData_t* PreData, PreWindow_t* Window)
{
	int16_t ri, di, tx, rx;
	cmplxf32_t input_data[SP_NUM_FFT_R];

	for (di = 0; di < SP_NUM_CHIRPS; di++)
	{
		for (tx = 0; tx < SP_NUM_TX; tx++)
		{
			for (rx = 0; rx < SP_NUM_RX; rx++)
			{
				for (ri = 0; ri < SP_NUM_SAMPLES; ri++)
				{
					input_data[ri].real = (float32_t)PreData->s16adcData[di][tx][rx][ri] * Window->cf32WinCoeff1D[tx][rx][ri].real;
					input_data[ri].imag = (float32_t)PreData->s16adcData[di][tx][rx][ri] * Window->cf32WinCoeff1D[tx][rx][ri].imag;
				}

				rsp_lib_fft_c2c_1d_f32(PreData->cf32fftData_1D[di][tx][rx], input_data, SP_NUM_FFT_R);
			}
		}
	}
	
}


static void Pre_vDopplerfft(PreData_t* PreData, PreWindow_t* Window)
{
	int16_t ri, di, tx, rx;
	cmplxf32_t input_data[SP_NUM_FFT_D];


	for (ri = 0; ri < SP_NUM_FFT_R_HALF; ri++)
	{
		for (tx = 0; tx < SP_NUM_TX; tx++)
		{
			for (rx = 0; rx < SP_NUM_RX; rx++)
			{
				for (di = 0; di < SP_NUM_FFT_D; di++)
				{
					input_data[di].real = PreData->cf32fftData_1D[di][tx][rx][ri].real * Window->f32WinCoeff2D[di];
					input_data[di].imag = PreData->cf32fftData_1D[di][tx][rx][ri].imag * Window->f32WinCoeff2D[di];
				}

				rsp_lib_fft_c2c_1d_f32(PreData->cf32fftData_2D[ri][tx][rx], input_data, SP_NUM_FFT_D);
			}
		}
	}

}




static void Pre_vRefRangefft(RefPreData_t* PreData, RefPreWindow_t* Window)
{
	int16_t ri, di, tx, rx;
	cmplxf32_t input_data[SP_RM_NUM_FFT_R];

	for (di = 0; di < SP_RM_NUM_CHIRPS; di++)
	{
		for (tx = 0; tx < SP_RM_NUM_TX; tx++)
		{
			for (rx = 0; rx < SP_NUM_RX; rx++)
			{
				for (ri = 0; ri < SP_RM_NUM_SAMPLES; ri++)
				{
					input_data[ri].real = (float32_t)PreData->s16adcData[di][tx][rx][ri] * Window->cf32WinCoeff1D[tx][rx][ri].real;
					input_data[ri].imag = 0.0f;
				}

				rsp_lib_fft_c2c_1d_f32(PreData->cf32fftData_1D[di][tx][rx], input_data, SP_RM_NUM_FFT_R);
			}
		}
	}
}


static void Pre_vRefDopplerfft(RefPreData_t* PreData, RefPreWindow_t* Window)
{
	int16_t ri, di, tx, rx;
	cmplxf32_t input_data[SP_RM_NUM_FFT_D];


	for (ri = 0; ri < SP_RM_NUM_FFT_R_HALF; ri++)
	{
		for (tx = 0; tx < SP_RM_NUM_TX; tx++)
		{
			for (rx = 0; rx < SP_NUM_RX; rx++)
			{
				for (di = 0; di < SP_RM_NUM_FFT_D; di++)
				{
					input_data[di].real = PreData->cf32fftData_1D[di][tx][rx][ri].real  * Window->f32WinCoeff2D[di]; 
					input_data[di].imag = PreData->cf32fftData_1D[di][tx][rx][ri].imag * Window->f32WinCoeff2D[di];
				}
				
				rsp_lib_fft_c2c_1d_f32(PreData->cf32fftData_2D[ri][tx][rx], input_data, SP_RM_NUM_FFT_D);
			}
		}
	}
}

#endif