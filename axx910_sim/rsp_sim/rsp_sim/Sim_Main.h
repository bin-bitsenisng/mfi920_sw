#ifndef _SIM_MAIN_H_
#define _SIM_MAIN_H_


/**************************************************************************************
-------------------------------------   include   -------------------------------------
**************************************************************************************/
#include "Sp_Main.h"
//#include "Pre_Parameters.h"
#include "Obj_Parameters.h"
//#include "Trk_Parameters.h"


/**************************************************************************************
-------------------------------------   define   --------------------------------------
**************************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#define TRK_NUM_EXPORT_TRACKLET_DATA	20
#define TRK_NUM_EXPORT_TRACK_DATA		25


/**************************************************************************************
----------------------------------   Data Struct   ------------------------------------
**************************************************************************************/


/**************************************************************************************
--------------------------------   global variables   ---------------------------------
**************************************************************************************/
		
extern uint32_t initScan;
extern uint32_t finScan;
#if defined(WIN32) || defined(ARM64)
extern uint32_t peakMode;
#endif

extern int16_t Sim_CurrentPRF;
extern int16_t Sim_RadarScanIdx;
extern uint16_t Sim_SampleNumber;
extern float32_t Sim_CycleTime;
extern int16_t Sim_TimeData[SP_NUM_RX][SP_NUM_TX * SP_NUM_CHIRPS * SP_NUM_SAMPLES];

extern int16_t Sim_RM_TimeData[SP_NUM_RX*SP_RM_NUM_CHIRPS * SP_RM_NUM_SAMPLES];
extern int16_t Sim_LR_TimeData[SP_NUM_RX*SP_NUM_TX * SP_NUM_CHIRPS * SP_NUM_SAMPLES];
extern int16_t Sim_MR_TimeData[SP_NUM_RX*SP_NUM_TX * SP_NUM_CHIRPS * SP_NUM_SAMPLES];
extern int16_t Sim_SR_TimeData[SP_NUM_RX*SP_NUM_TX * SP_NUM_CHIRPS * SP_NUM_SAMPLES];


extern int16_t Sim_OutObjCnt;
extern int16_t Sim_OutFilObjCnt;
extern int16_t Sim_REF_OutObjCnt;

extern float32_t Sim_ObjInfo[SP_NUM_OBJECT_MAX][22];
extern float32_t Sim_FilObjInfo[OBJ_NUM_FILETERD_OBJ_MAX][22];
extern float32_t Sim_REF_ObjInfo[OBJ_NUM_RM_CANDIDATE_OBJ][22];

extern float32_t Sim_TrkletInfo[SP_NUM_CLST_MAX][TRK_NUM_EXPORT_TRACKLET_DATA];
extern float32_t Sim_TrkInfo[SP_NUM_TRACK_MAX][TRK_NUM_EXPORT_TRACK_DATA];

extern float32_t Sim_RM_PowSpectrum[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
extern float32_t Sim_LR_PowSpectrum[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
extern float32_t Sim_MR_PowSpectrum[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
extern float32_t Sim_SR_PowSpectrum[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];

extern float32_t Sim_RM_PowSpectrum_log[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
extern float32_t Sim_LR_PowSpectrum_log[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
extern float32_t Sim_MR_PowSpectrum_log[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
extern float32_t Sim_SR_PowSpectrum_log[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];

extern uint8_t Sim_RM_PowSpectrum_mask[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
extern uint8_t Sim_LR_PowSpectrum_mask[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
extern uint8_t Sim_MR_PowSpectrum_mask[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
extern uint8_t Sim_SR_PowSpectrum_mask[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];

extern float32_t Sim_RM_BaseTh;
extern float32_t Sim_LR_BaseTh;
extern float32_t Sim_MR_BaseTh;
extern float32_t Sim_SR_BaseTh;

extern float32_t Sim_RM_RangeCfarTh[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
extern float32_t Sim_RM_DoppCfarTh[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
extern uint8_t Sim_RM_RangeCfarOut[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
extern uint8_t Sim_RM_DoppCfarOut[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];

extern float32_t Sim_LR_RangeCfarTh[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
extern float32_t Sim_LR_DoppCfarTh[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
extern uint8_t Sim_LR_RangeCfarOut[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
extern uint8_t Sim_LR_DoppCfarOut[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];

extern float32_t Sim_MR_RangeCfarTh[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
extern float32_t Sim_MR_DoppCfarTh[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
extern uint8_t Sim_MR_RangeCfarOut[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
extern uint8_t Sim_MR_DoppCfarOut[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];

extern float32_t Sim_SR_RangeCfarTh[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
extern float32_t Sim_SR_DoppCfarTh[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
extern uint8_t Sim_SR_RangeCfarOut[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
extern uint8_t Sim_SR_DoppCfarOut[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];

extern int16_t Sim_RM_PeakCnt;
extern int16_t Sim_LR_PeakCnt;
extern int16_t Sim_MR_PeakCnt;
extern int16_t Sim_SR_PeakCnt;

extern float32_t Sim_RM_PeakInfo[OBJ_NUM_RM_PEAK_MAX][10];
extern float32_t Sim_LR_PeakInfo[OBJ_NUM_PEAK_HARM_MAX][4+192*2];
extern float32_t Sim_MR_PeakInfo[OBJ_NUM_PEAK_HARM_MAX][4+192*2];
extern float32_t Sim_SR_PeakInfo[OBJ_NUM_PEAK_HARM_MAX][4+192*2];

extern float32_t Sim_RM_PeakData[OBJ_NUM_RM_PEAK_MAX][4 + 16*2];
extern float32_t Sim_LR_PeakData[OBJ_NUM_PEAK_HARM_MAX][4 + 192 * 2];
extern float32_t Sim_MR_PeakData[OBJ_NUM_PEAK_HARM_MAX][4 + 192 * 2];
extern float32_t Sim_SR_PeakData[OBJ_NUM_PEAK_HARM_MAX][4 + 192 * 2];

extern float32_t Sim_LR_AziAngleTable[OBJ_AE_AZI_LR_NUM_APS_STEPS];
extern float32_t Sim_LR_EleAngleTable[OBJ_AE_ELE_LR_NUM_APS_STEPS];
extern float32_t Sim_LR_APS[OBJ_NUM_PEAK_HARM_MAX][OBJ_AE_AZI_LR_NUM_APS_STEPS*OBJ_AE_ELE_LR_NUM_APS_STEPS * OBJ_CO_NUM_HARMONICS_MAX];

extern float32_t Sim_MR_AziAngleTable[OBJ_AE_AZI_MR_NUM_APS_STEPS];
extern float32_t Sim_MR_EleAngleTable[OBJ_AE_ELE_MR_NUM_APS_STEPS];
extern float32_t Sim_MR_APS[OBJ_NUM_PEAK_HARM_MAX][OBJ_AE_AZI_MR_NUM_APS_STEPS*OBJ_AE_ELE_MR_NUM_APS_STEPS * OBJ_CO_NUM_HARMONICS_MAX];

extern float32_t Sim_SR_AziAngleTable[OBJ_AE_AZI_SR_NUM_APS_STEPS];
extern float32_t Sim_SR_EleAngleTable[OBJ_AE_ELE_SR_NUM_APS_STEPS];
extern float32_t Sim_SR_APS[OBJ_NUM_PEAK_HARM_MAX][OBJ_AE_AZI_SR_NUM_APS_STEPS*OBJ_AE_ELE_SR_NUM_APS_STEPS * OBJ_CO_NUM_HARMONICS_MAX];

extern float32_t Sim_RM_AziAngleTable[OBJ_AE_AZI_RM_NUM_APS_STEPS];
extern float32_t Sim_RM_APS[OBJ_NUM_RM_PEAK_MAX][OBJ_AE_AZI_RM_NUM_APS_STEPS];

extern float32_t Can[11];
extern float32_t AI[AI_OBJECT_MAX_SIZE][6];
extern float32_t Object[64][20];

/**************************************************************************************
-------------------------------   function prototypes   -------------------------------
**************************************************************************************/
extern void Sim_SysInit(void);
extern void Sim_RadarMain(void);

/**************************************************************************************
--------------------------------------   Macro   --------------------------------------
**************************************************************************************/




#ifdef __cplusplus
}
#endif

#endif


