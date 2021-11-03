#ifndef _OBJ_MAIN_H_
#define _OBJ_MAIN_H_
#ifdef __cplusplus
extern "C" {
#endif
	/**************************************************************************************
	-------------------------------------   include   -------------------------------------
	**************************************************************************************/
#include "Sp_Main.h"
#include "Obj_Parameters.h"
#include	"Pre_Main.h"

	/**************************************************************************************
	-------------------------------------   define   --------------------------------------
	**************************************************************************************/


	/**************************************************************************************
	----------------------------------   Data Struct   ------------------------------------
	**************************************************************************************/
	typedef struct
	{
		int16_t R;
		int16_t D;
	} rdidxs16_t;


	typedef struct
	{
		uint16_t R;
		uint16_t D;
	} rdidxu16_t;


	typedef struct
	{
		float32_t R;
		float32_t D;
	} rdidxf32_t;


	typedef struct
	{
		float32_t f32PowSpectrum[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
		float32_t f32PowSpectrum_array[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
		uint8_t u8CfarOut_R[OBJ_NUM_FFT_D][OBJ_NUM_FFT_R];
		uint8_t u8CfarOut_D[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
#if defined(WIN32) || defined(ARM64)
		float32_t f32CfarTh_R[OBJ_NUM_FFT_D][OBJ_NUM_FFT_R];
		float32_t f32CfarTh_D[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
#endif

	} BeamData_t;

	typedef struct
	{
		float32_t f32PowSpectrum[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
		float32_t f32PowSpectrum_array[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
		uint8_t u8CfarOut_R[OBJ_RM_NUM_FFT_D][OBJ_RM_NUM_FFT_R];
		uint8_t u8CfarOut_D[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
#if defined(WIN32) || defined(ARM64)
		float32_t f32CfarTh_R[OBJ_RM_NUM_FFT_D][OBJ_RM_NUM_FFT_R];
		float32_t f32CfarTh_D[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
#endif

	} RefBeamData_t;

	typedef struct
	{
		float32_t* f32PowSpectrum;
		float32_t* f32PowSpectrum_temp;
		float32_t f32PowSpectrum_array[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
		uint8_t u8CfarOut_R[OBJ_NUM_FFT_D][OBJ_NUM_FFT_R];
		uint8_t u8CfarOut_D[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
#if defined(WIN32) || defined(ARM64)
		float32_t f32CfarTh_R[OBJ_NUM_FFT_D][OBJ_NUM_FFT_R];
		float32_t f32CfarTh_D[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
#endif
	} Cuda_BeamData_t;

	typedef struct
	{
		float32_t* f32PowSpectrum;
		float32_t* f32PowSpectrum_temp;
		float32_t f32PowSpectrum_array[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
		uint8_t u8CfarOut_R[OBJ_RM_NUM_FFT_D][OBJ_RM_NUM_FFT_R];
		uint8_t u8CfarOut_D[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
#if defined(WIN32) || defined(ARM64)
		float32_t f32CfarTh_R[OBJ_RM_NUM_FFT_D][OBJ_RM_NUM_FFT_R];
		float32_t f32CfarTh_D[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
#endif
	} Cuda_RefBeamData_t;


	typedef struct
	{
		int16_t s16PeakCnt;
		int16_t s16HarmonicCnt[OBJ_NUM_PEAK_MAX];
		rdidxu16_t rdu16FreqIdx[OBJ_NUM_PEAK_MAX];
		rdidxf32_t rdf32EstFreqIdx[OBJ_NUM_PEAK_MAX];
		cmplxf32_t cf32FFTData[OBJ_NUM_PEAK_MAX][OBJ_NUM_TX][OBJ_NUM_RX];
		float32_t f32Range[OBJ_NUM_PEAK_MAX][OBJ_CO_NUM_HARMONICS_MAX];
		float32_t f32Velocity[OBJ_NUM_PEAK_MAX][OBJ_CO_NUM_HARMONICS_MAX];
		float32_t f32AziAngTable[OBJ_AE_AZI_NUM_APS_STEPS_MAX];
		float32_t f32EleAngTable[OBJ_AE_ELE_NUM_APS_STEPS_MAX];
		cmplxf32_t cf32SteerVec[OBJ_AE_ELE_NUM_APS_STEPS_MAX*OBJ_AE_AZI_NUM_APS_STEPS_MAX][OBJ_AE_NUM_CH];

		int16_t s16AngCnt[OBJ_NUM_PEAK_MAX][OBJ_CO_NUM_HARMONICS_MAX];
		float32_t f32AziAngle[OBJ_NUM_PEAK_MAX][OBJ_CO_NUM_HARMONICS_MAX][OBJ_AE_NUM_TARGET_MAX];
		float32_t f32EleAngle[OBJ_NUM_PEAK_MAX][OBJ_CO_NUM_HARMONICS_MAX][OBJ_AE_NUM_TARGET_MAX];
		float32_t f32Power[OBJ_NUM_PEAK_MAX][OBJ_CO_NUM_HARMONICS_MAX][OBJ_AE_NUM_TARGET_MAX];

		int16_t s16HarmIdx[OBJ_NUM_PEAK_MAX];

#if defined(WIN32) || defined(ARM64)
		float32_t f32APS[OBJ_NUM_PEAK_MAX][OBJ_AE_ELE_NUM_APS_STEPS_MAX*OBJ_AE_AZI_NUM_APS_STEPS_MAX * 2];
#endif

	} PeakData_t;

	typedef struct
	{
		int16_t s16PeakCnt;
		int16_t s16PhCnt;


		int16_t s16HarmonicCnt[OBJ_NUM_PEAK_MAX];

		rdidxu16_t rdu16FreqIdx[OBJ_NUM_PEAK_MAX];
		rdidxu16_t rdu16phFreqIdx[OBJ_NUM_PEAK_HARM_MAX];
		rdidxf32_t rdf32EstFreqIdx[OBJ_NUM_PEAK_MAX];

		float32_t f32SllPow[OBJ_NUM_PEAK_MAX];

		//rdidxf32_t rdf32PhEstFreqIdx[OBJ_NUM_PEAK_HARM_MAX];

		cmplxf32_t cf32FFTData[OBJ_NUM_PEAK_MAX][OBJ_NUM_TX][OBJ_NUM_RX];

		float32_t f32Range[OBJ_NUM_PEAK_MAX][2];
		float32_t f32Velocity[OBJ_NUM_PEAK_MAX][2];

		float32_t f32PhRange[OBJ_NUM_PEAK_HARM_MAX][OBJ_CO_NUM_HARMONICS_MAX];
		float32_t f32PhVelocity[OBJ_NUM_PEAK_HARM_MAX][OBJ_CO_NUM_HARMONICS_MAX];
		cmplxf32_t cf32PhFFTData[OBJ_NUM_PEAK_HARM_MAX][OBJ_NUM_TX*OBJ_NUM_RX];
		float32_t f32PhSllPow[OBJ_NUM_PEAK_HARM_MAX];


		float32_t f32AziAngTable[OBJ_AE_AZI_NUM_APS_STEPS_MAX];
		float32_t f32EleAngTable[OBJ_AE_ELE_NUM_APS_STEPS_MAX];

		float32_t f32PreAziAngTable[OBJ_AE_AZI_RM_NUM_APS_STEPS];

		//cmplxf32_t cf32SteerVec[OBJ_AE_ELE_NUM_APS_STEPS_MAX][OBJ_AE_AZI_NUM_APS_STEPS_MAX][OBJ_AE_NUM_CH];
		cmplxf32_t* cf32SteerVec;
		cmplxf32_t cf32PreSteerVec[OBJ_AE_AZI_NUM_APS_STEPS_MAX][OBJ_AE_RM_NUM_CH];


		int16_t s16AngCnt[OBJ_NUM_PEAK_HARM_MAX][OBJ_CO_NUM_HARMONICS_MAX];
		float32_t f32AziAngle[OBJ_NUM_PEAK_HARM_MAX][OBJ_CO_NUM_HARMONICS_MAX][OBJ_AE_NUM_TARGET_MAX];
		float32_t f32EleAngle[OBJ_NUM_PEAK_HARM_MAX][OBJ_CO_NUM_HARMONICS_MAX][OBJ_AE_NUM_TARGET_MAX];
		float32_t f32Power[OBJ_NUM_PEAK_HARM_MAX][OBJ_CO_NUM_HARMONICS_MAX][OBJ_AE_NUM_TARGET_MAX];
		int16_t s16TrackFlag[OBJ_NUM_PEAK_HARM_MAX][OBJ_CO_NUM_HARMONICS_MAX][OBJ_AE_NUM_TARGET_MAX];

		int16_t s16PreAngCnt[OBJ_NUM_PEAK_MAX];

		float32_t f32MatPreAziAngle[OBJ_NUM_PEAK_MAX][OBJ_AE_RM_NUM_TARGET_MAX];
		float32_t f32MatPrePower[OBJ_NUM_PEAK_MAX][OBJ_AE_RM_NUM_TARGET_MAX];
		float32_t f32PreAziAngle[OBJ_NUM_PEAK_MAX][OBJ_AE_RM_NUM_TARGET_MAX];
		float32_t f32PreEleAngle[OBJ_NUM_PEAK_MAX][OBJ_AE_RM_NUM_TARGET_MAX];
		float32_t f32PrePower[OBJ_NUM_PEAK_MAX][OBJ_AE_RM_NUM_TARGET_MAX];

		int16_t s16PhPreAngCnt[OBJ_NUM_PEAK_HARM_MAX];
		float32_t f32PhPreAziAngle[OBJ_NUM_PEAK_HARM_MAX][OBJ_AE_REF_NUM_TARGET_MAX];
		float32_t f32PhPreEleAngle[OBJ_NUM_PEAK_HARM_MAX][OBJ_AE_REF_NUM_TARGET_MAX];
		float32_t f32PhPrePower[OBJ_NUM_PEAK_HARM_MAX][OBJ_AE_REF_NUM_TARGET_MAX];
		int16_t s16HarmIdx[OBJ_NUM_PEAK_MAX];

#if defined(WIN32) || defined(ARM64)
		float32_t f32APS[OBJ_NUM_PEAK_HARM_MAX][OBJ_AE_ELE_NUM_APS_STEPS_MAX*OBJ_AE_AZI_NUM_APS_STEPS_MAX];
		int16_t s16MatRefPeakIdx[OBJ_NUM_PEAK_MAX];
#endif

	} Cuda_PeakData_t;


	typedef struct
	{
		int16_t s16PeakCnt;
		int16_t s16reseved;

		rdidxu16_t rdu16FreqIdx[OBJ_NUM_RM_PEAK_MAX];
		rdidxf32_t rdf32EstFreqIdx[OBJ_NUM_RM_PEAK_MAX];
		cmplxf32_t cf32FFTData[OBJ_NUM_RM_PEAK_MAX][OBJ_RM_NUM_TX][OBJ_NUM_RX];

		cmplxf32_t cf32SteerVec[OBJ_AE_AZI_RM_NUM_APS_STEPS][OBJ_AE_RM_NUM_CH];

		float32_t f32AziAngTable[OBJ_AE_AZI_RM_NUM_APS_STEPS];
		float32_t f32Range[OBJ_NUM_RM_PEAK_MAX];
		float32_t f32Velocity[OBJ_NUM_RM_PEAK_MAX];
		float32_t f32Power[OBJ_NUM_RM_PEAK_MAX][OBJ_AE_RM_NUM_TARGET_MAX];

		int16_t s16AngCnt[OBJ_NUM_RM_PEAK_MAX];
		float32_t f32AziAngle[OBJ_NUM_RM_PEAK_MAX][OBJ_AE_RM_NUM_TARGET_MAX];
		float32_t f32EleAngle[OBJ_NUM_RM_PEAK_MAX];

#if defined(WIN32) || defined(ARM64)
		float32_t f32APS[OBJ_NUM_RM_PEAK_MAX][OBJ_AE_AZI_RM_NUM_APS_STEPS];
		int16_t s16MatRefPeakIdx[OBJ_NUM_PEAK_MAX];
#endif

	} RefPeakData_t;

	typedef enum
	{
		NOT_GHOST = 0,
		FOV_FILTER = 1,
		HW_NOISE = 2,
		AMBIGUOUS_VEL = 3,
		CRFT_FILTER= 4,

	} GFType_t;


	typedef struct
	{
		int16_t s16HarmonicCnt;
		GFType_t eGFType;
		float32_t f32Range;
		float32_t f32Velocity;
		float32_t f32AziAngle;
		float32_t f32EleAngle;
		float32_t f32Power;
		rdidxu16_t rdu16FreqIdx;
		float32_t f32NoiseVar;

		float32_t f32PreAziAngle;
		float32_t f32PrePow;
		float32_t f32SllPowdB;
		int16_t s16TrackFlag;
#if defined(WIN32) || defined(ARM64)
		int16_t s16PeakIdx;
		int16_t s16HarmIdx;
		int16_t s16MatRefPeakIdx;
		int16_t s16MatRefObjIdx;
#endif
	} CandidateObj_t;


	typedef struct
	{
		GFType_t eGFType;
		float32_t f32Range;
		float32_t f32Velocity;
		float32_t f32AziAngle;
		float32_t f32EleAngle;
		float32_t f32Power;
		rdidxu16_t rdu16FreqIdx;
		float32_t f32NoiseVar;

		int16_t s16AngCnt;
		int16_t s16TrackFlag;
#if defined(WIN32) || defined(ARM64)
		int16_t s16PeakIdx;
#endif
	} RefCandidateObj_t;

	typedef struct
	{
		CandidateObj_t ObjData[OBJ_NUM_CANDIDATE_OBJ*OBJ_AE_NUM_TARGET_MAX];
		int16_t s16ObjCnt;
	} CalcObjData_t;

	typedef struct
	{
		RefCandidateObj_t ObjData[OBJ_NUM_CANDIDATE_OBJ];
		int16_t s16ObjCnt;
	} RefCalcObjData_t;



	typedef struct
	{
		MultiMod_t eModType;
		float32_t f32Range_m;
		float32_t f32Velocity_mps;
		float32_t f32AziAng_deg;
		float32_t f32EleAng_deg;
		float32_t f32Power_dB;
#if defined(WIN32) || defined(ARM64)
		GFType_t eGFType;
		int16_t s16PeakIdx;
		rdidxu16_t rdu16FreqIdx;
		int16_t s16HarmIdx;
		int16_t s16MatRefPeakIdx;

		float32_t f32PreAziAngle;
		float32_t f32PrePow;
		float32_t f32SllPowdB;
		int16_t s16TrackFlag;
#endif

	} ObjectOut_t;

	/**************************************************************************************
	--------------------------------   global variables   ---------------------------------
	**************************************************************************************/
#ifdef CUDA_ACC
	extern Cuda_RefBeamData_t gRM_BeamData;
	extern Cuda_BeamData_t gLR_BeamData;
	extern Cuda_BeamData_t gMR_BeamData;
	extern Cuda_BeamData_t gSR_BeamData;
#else
	extern RefBeamData_t gRM_BeamData;
	extern BeamData_t gLR_BeamData;
	extern BeamData_t gMR_BeamData;
	extern BeamData_t gSR_BeamData;
#endif

	extern RefPeakData_t gRM_PeakData;

#ifdef CUDA_ACC
	extern Cuda_PeakData_t gLR_PeakData;
	extern Cuda_PeakData_t gMR_PeakData;
	extern Cuda_PeakData_t gSR_PeakData;
#else
	extern PeakData_t gLR_PeakData;
	extern PeakData_t gMR_PeakData;
	extern PeakData_t gSR_PeakData;
#endif

	extern RefCalcObjData_t gRM_ObjData;
	extern CalcObjData_t gLR_ObjData;
	extern CalcObjData_t gMR_ObjData;
	extern CalcObjData_t gSR_ObjData;

	extern ObjectOut_t gObjectOut[OBJ_NUM_OBJECT_MAX];
	extern int16_t gObjOutCnt;

#if defined(WIN32) || defined(ARM64)
	extern ObjectOut_t gFilteredObj[OBJ_NUM_FILETERD_OBJ_MAX];
	extern int16_t gFilteredObjCnt;
	extern int16_t gPeakMode;
#endif

	/**************************************************************************************
	-------------------------------   function prototypes   -------------------------------
	**************************************************************************************/
	extern void Obj_vSysInit(void);
	extern void Obj_vMain(void);


	/**************************************************************************************
	--------------------------------------   Macro   --------------------------------------
	**************************************************************************************/
#define _obj_cmplx_mul_s16f32(res,a,b)		(res).real = ((float32_t)((a).real) * ((b).real)) - ((float32_t)((a).imag) * ((b).imag));\
														(res).imag = ((float32_t)((a).real) * ((b).imag)) + ((float32_t)((a).imag) * ((b).real));

#define _obj_cmplx_mul(res,a,b)				(res).real = (((a).real) * ((b).real)) - (((a).imag) * ((b).imag));\
														(res).imag = (((a).real) * ((b).imag)) + (((a).imag) * ((b).real));

#define _obj_cmplx_sub(res,a,b)				(res).real = (( (float32_t)(a).real) - ( (float32_t)(b).real) );\
														(res).imag = (( (float32_t)(a).imag) - ( (float32_t)(b).imag ));

#define _obj_cmplx_abs(res,a)					(res)  = _sp_sqrtf(((float32_t)(a).real)*((float32_t)(a).real) + ((float32_t)(a).imag) * ((float32_t)(a).imag));

#ifdef __cplusplus
}
#endif

#endif

