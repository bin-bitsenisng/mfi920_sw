#ifndef _PRE_MAIN_H_
#define _PRE_MAIN_H_

/**************************************************************************************
-------------------------------------   include   -------------------------------------
**************************************************************************************/
#include "Sp_Main.h"
#include "Pre_Parameters.h"

/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
-------------------------------------   define   --------------------------------------
**************************************************************************************/


/**************************************************************************************
----------------------------------   Data Struct   ------------------------------------
**************************************************************************************/
typedef struct
{
	int16_t* s16adcData;
	cmplxf32_t* cf32fftData_1D;
	cmplxf32_t* cf32fftData_2D;
} Cuda_RefPreData_t;


typedef struct
{
	int16_t* s16adcData;
	cmplxf32_t* cf32fftData_1D;
	cmplxf32_t* cf32fftData_2D;
} Cuda_PreData_t;

typedef struct
{
	float32_t* cf32WinCoeffMap;
	float32_t* f32WinCoeff2D;
} Cuda_RefPreWindow_t;

typedef struct
{
	float32_t* cf32WinCoeffMap;
	float32_t* f32WinCoeff2D;
} Cuda_PreWindow_t;


typedef struct
{
	int16_t s16adcData[SP_RM_NUM_CHIRPS][SP_RM_NUM_TX][SP_NUM_RX][SP_RM_NUM_SAMPLES];
	cmplxf32_t cf32fftData_1D[SP_RM_NUM_CHIRPS][SP_RM_NUM_TX][SP_NUM_RX][SP_RM_NUM_FFT_R_HALF];
	cmplxf32_t cf32fftData_2D[SP_RM_NUM_FFT_R_HALF][SP_RM_NUM_TX][SP_NUM_RX][SP_RM_NUM_FFT_D];
} RefPreData_t;


typedef struct
{
	int16_t s16adcData[SP_NUM_CHIRPS][SP_NUM_TX][SP_NUM_RX][SP_NUM_SAMPLES];
	cmplxf32_t cf32fftData_1D[SP_NUM_CHIRPS][SP_NUM_TX][SP_NUM_RX][SP_NUM_FFT_R];
	cmplxf32_t cf32fftData_2D[SP_NUM_FFT_R_HALF][SP_NUM_TX][SP_NUM_RX][SP_NUM_FFT_D];
} PreData_t;

typedef struct
{
	cmplxf32_t cf32WinCoeff1D[SP_RM_NUM_TX][SP_NUM_RX][SP_RM_NUM_FFT_R];
	float32_t f32WinCoeff2D[SP_RM_NUM_FFT_D];
} RefPreWindow_t;

typedef struct
{
	cmplxf32_t cf32WinCoeff1D[SP_NUM_TX][SP_NUM_RX][SP_NUM_FFT_R];
	float32_t f32WinCoeff2D[SP_NUM_FFT_D];
} PreWindow_t;

typedef struct
{
	cmplxf32_t f32RM_PhaseCal[SP_RM_NUM_TX][SP_NUM_RX];
	cmplxf32_t f32LR_PhaseCal[SP_NUM_TX][SP_NUM_RX];
	cmplxf32_t f32MR_PhaseCal[SP_NUM_TX][SP_NUM_RX];
	cmplxf32_t f32SR_PhaseCal[SP_NUM_TX][SP_NUM_RX];
} PhaseCal_t;

/**************************************************************************************
--------------------------------   global variables   ---------------------------------
**************************************************************************************/
#ifdef CUDA_ACC
extern Cuda_RefPreData_t gRM_PreData;
extern Cuda_PreData_t gLR_PreData;
extern Cuda_PreData_t gMR_PreData;
extern Cuda_PreData_t gSR_PreData;

extern Cuda_RefPreWindow_t gRM_PreWindow;
extern Cuda_PreWindow_t gLR_PreWindow;
extern Cuda_PreWindow_t gMR_PreWindow;
extern Cuda_PreWindow_t gSR_PreWindow;

extern PhaseCal_t gPhaseCal;
extern PhaseCal_t gPhaseCal_temp;
extern cmplxf32_t* gLR_CalFFT;
extern cmplxf32_t* gMR_CalFFT;
extern cmplxf32_t* gSR_CalFFT;

#else
extern RefPreData_t gRM_PreData;
extern PreData_t gLR_PreData;
extern PreData_t gMR_PreData;
extern PreData_t gSR_PreData;

extern RefPreWindow_t gRM_PreWindow;
extern PreWindow_t gLR_PreWindow;
extern PreWindow_t gMR_PreWindow;
extern PreWindow_t gSR_PreWindow;

extern PhaseCal_t gPhaseCal;
extern cmplxf32_t gLR_CalFFT[SP_NUM_TX][SP_NUM_RX];
extern cmplxf32_t gMR_CalFFT[SP_NUM_TX][SP_NUM_RX];
extern cmplxf32_t gSR_CalFFT[SP_NUM_TX][SP_NUM_RX];
#endif

/**************************************************************************************
-------------------------------   function prototypes   -------------------------------
**************************************************************************************/
extern void Pre_vSysInit(void);
extern void Pre_vMain(void);

/**************************************************************************************
--------------------------------------   Macro   --------------------------------------
**************************************************************************************/

#endif
