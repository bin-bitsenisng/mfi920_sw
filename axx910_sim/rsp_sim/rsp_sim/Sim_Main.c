
/**************************************************************************************
-------------------------------------   include   -------------------------------------
**************************************************************************************/
#include "Sp_Main.h"
#include "Pre_Main.h"
#include "Obj_Main.h"
#include "Trk_Main.h"
#include "App_Main.h"
#include "Sim_Main.h"
#include "Obj_Parameters.h"
#include "time.h"
#include "Obj_CFAR.h"
#include "bts_cfarlib.h"

/**************************************************************************************
-------------------------------------   define   --------------------------------------
**************************************************************************************/


/**************************************************************************************
--------------------------------   global variables   ---------------------------------
**************************************************************************************/
uint32_t initScan;
uint32_t finScan;
uint32_t peakMode;

int16_t Sim_CurrentPRF;
int16_t Sim_RadarScanIdx;
uint16_t Sim_SampleNumber;
float32_t Sim_CycleTime;

int16_t Sim_RM_TimeData[SP_NUM_RX*SP_RM_NUM_CHIRPS * SP_RM_NUM_SAMPLES];
int16_t Sim_LR_TimeData[SP_NUM_RX*SP_NUM_TX * SP_NUM_CHIRPS * SP_NUM_SAMPLES];
int16_t Sim_MR_TimeData[SP_NUM_RX*SP_NUM_TX * SP_NUM_CHIRPS * SP_NUM_SAMPLES];
int16_t Sim_SR_TimeData[SP_NUM_RX*SP_NUM_TX * SP_NUM_CHIRPS * SP_NUM_SAMPLES];

int16_t Sim_OutObjCnt;
float32_t Sim_ObjInfo[SP_NUM_OBJECT_MAX][22];

int16_t Sim_REF_OutObjCnt;
float32_t Sim_REF_ObjInfo[OBJ_NUM_RM_CANDIDATE_OBJ][22];

int16_t Sim_OutFilObjCnt;
float32_t Sim_FilObjInfo[OBJ_NUM_FILETERD_OBJ_MAX][22];

float32_t Sim_TrkletInfo[SP_NUM_CLST_MAX][TRK_NUM_EXPORT_TRACKLET_DATA];
float32_t Sim_TrkInfo[SP_NUM_TRACK_MAX][TRK_NUM_EXPORT_TRACK_DATA];

float32_t Sim_RM_PowSpectrum[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
float32_t Sim_LR_PowSpectrum[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
float32_t Sim_MR_PowSpectrum[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
float32_t Sim_SR_PowSpectrum[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];

float32_t Sim_RM_PowSpectrum_log[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
float32_t Sim_LR_PowSpectrum_log[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
float32_t Sim_MR_PowSpectrum_log[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
float32_t Sim_SR_PowSpectrum_log[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];

uint8_t Sim_RM_PowSpectrum_mask[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
uint8_t Sim_LR_PowSpectrum_mask[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
uint8_t Sim_MR_PowSpectrum_mask[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
uint8_t Sim_SR_PowSpectrum_mask[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];


float32_t Sim_RM_BaseTh;
float32_t Sim_LR_BaseTh;
float32_t Sim_MR_BaseTh;
float32_t Sim_SR_BaseTh;

float32_t Sim_RM_RangeCfarTh[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
float32_t Sim_RM_DoppCfarTh[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
uint8_t Sim_RM_RangeCfarOut[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];
uint8_t Sim_RM_DoppCfarOut[OBJ_RM_NUM_FFT_R][OBJ_RM_NUM_FFT_D];

float32_t Sim_LR_RangeCfarTh[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
float32_t Sim_LR_DoppCfarTh[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
uint8_t Sim_LR_RangeCfarOut[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
uint8_t Sim_LR_DoppCfarOut[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];

float32_t Sim_MR_RangeCfarTh[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
float32_t Sim_MR_DoppCfarTh[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
uint8_t Sim_MR_RangeCfarOut[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
uint8_t Sim_MR_DoppCfarOut[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];

float32_t Sim_SR_RangeCfarTh[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
float32_t Sim_SR_DoppCfarTh[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
uint8_t Sim_SR_RangeCfarOut[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];
uint8_t Sim_SR_DoppCfarOut[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];

int16_t Sim_RM_PeakCnt;
int16_t Sim_LR_PeakCnt;
int16_t Sim_MR_PeakCnt;
int16_t Sim_SR_PeakCnt;

float32_t Sim_RM_PeakInfo[OBJ_NUM_RM_PEAK_MAX][10];
float32_t Sim_LR_PeakInfo[OBJ_NUM_PEAK_HARM_MAX][4 + 192 * 2];
float32_t Sim_MR_PeakInfo[OBJ_NUM_PEAK_HARM_MAX][4 + 192 * 2];
float32_t Sim_SR_PeakInfo[OBJ_NUM_PEAK_HARM_MAX][4 + 192 * 2];

float32_t Sim_RM_PeakData[OBJ_NUM_RM_PEAK_MAX][4 + 16 * 2];

float32_t Sim_LR_PeakData[OBJ_NUM_PEAK_HARM_MAX][4 + 192 * 2];
float32_t Sim_MR_PeakData[OBJ_NUM_PEAK_HARM_MAX][4 + 192 * 2];
float32_t Sim_SR_PeakData[OBJ_NUM_PEAK_HARM_MAX][4 + 192 * 2];

float32_t Sim_LR_AziAngleTable[OBJ_AE_AZI_LR_NUM_APS_STEPS];
float32_t Sim_LR_EleAngleTable[OBJ_AE_ELE_LR_NUM_APS_STEPS];
float32_t Sim_LR_APS[OBJ_NUM_PEAK_HARM_MAX][OBJ_AE_AZI_LR_NUM_APS_STEPS*OBJ_AE_ELE_LR_NUM_APS_STEPS*OBJ_CO_NUM_HARMONICS_MAX];

float32_t Sim_MR_AziAngleTable[OBJ_AE_AZI_MR_NUM_APS_STEPS];
float32_t Sim_MR_EleAngleTable[OBJ_AE_ELE_MR_NUM_APS_STEPS];
float32_t Sim_MR_APS[OBJ_NUM_PEAK_HARM_MAX][OBJ_AE_AZI_MR_NUM_APS_STEPS*OBJ_AE_ELE_MR_NUM_APS_STEPS*OBJ_CO_NUM_HARMONICS_MAX];

float32_t Sim_SR_AziAngleTable[OBJ_AE_AZI_SR_NUM_APS_STEPS];
float32_t Sim_SR_EleAngleTable[OBJ_AE_ELE_SR_NUM_APS_STEPS];
float32_t Sim_SR_APS[OBJ_NUM_PEAK_HARM_MAX][OBJ_AE_AZI_SR_NUM_APS_STEPS*OBJ_AE_ELE_SR_NUM_APS_STEPS*OBJ_CO_NUM_HARMONICS_MAX];

float32_t Sim_RM_AziAngleTable[OBJ_AE_AZI_RM_NUM_APS_STEPS];
float32_t Sim_RM_APS[OBJ_NUM_RM_PEAK_MAX][OBJ_AE_AZI_RM_NUM_APS_STEPS];

float32_t Can[11];
float32_t AI[AI_OBJECT_MAX_SIZE][6];
float32_t Object[64][20];
float32_t Object[64][20];



/**************************************************************************************
-------------------------------   function prototypes   -------------------------------
**************************************************************************************/
static void Sim_GetSpInfo(void);
static void Sim_GetAiData(void);
static void Sim_GetCanData(void);
static void Sim_GetTimeData(void);
static void Sim_GetPeakData(void);
static void Sim_Debug(void);
static void Sim_ObjectOut(void);
static void Sim_ClusterOut(void);
static void Sim_TrackOut(void);
static void Sim_AppOut(void);

/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Sim_SysInit(void)
{
	Sp_vSysInit();

}


void Sim_RadarMain(void)
{
	int i;
	clock_t time_start, time_end;
	double res1;

	Sim_GetCanData();
	Sim_GetAiData();


	Sim_GetSpInfo();

	if (peakMode == 0)
	{
		gPeakMode = 0;
		Sim_GetTimeData();
	}
	else
	{
		gPeakMode = 1;
		Sim_GetPeakData();
	}
	Sp_vMain();

	
	//res1 = ((time_end - time_start) / 1000.0f);
	//printf("Sp_v Main data : %.4f\n", res1);

	Sim_ObjectOut();


	Trk_vMain();



	//Sim_ClusterOut();

	Sim_TrackOut();
	Sim_AppOut();
	Sim_Debug();
}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/

static void Sim_GetSpInfo(void)
{
	gSpCycleTime = Sim_CycleTime;
}


static void Sim_GetAiData(void)
{
	int16_t i_obj;

	for (i_obj = 0; i_obj < AI_OBJECT_MAX_SIZE; i_obj++)
	{
		if (AI[i_obj][1] == 0)
		{
			break;
		}
		ai_object[i_obj].Ai_class_id	= (float32_t)AI[i_obj][0];
		ai_object[i_obj].Ai_confidence	= (float32_t)AI[i_obj][1];
		ai_object[i_obj].Ai_height		= (float32_t)AI[i_obj][2];
		ai_object[i_obj].Ai_width		= (float32_t)AI[i_obj][3];
		ai_object[i_obj].Ai_x_location	= (float32_t)AI[i_obj][4];
		ai_object[i_obj].Ai_y_location	= (float32_t)AI[i_obj][5];
	}

	ai_object[0].Ai_num_of_class = i_obj;
}

static void Sim_GetCanData(void)
{
	can_sig_data.vehicle_speed		= Can[0];
	can_sig_data.wheel_speed_fl		= Can[1];
	can_sig_data.wheel_speed_fr		= Can[2];
	can_sig_data.wheel_speed_rl		= Can[3];
	can_sig_data.wheel_speed_rr		= Can[4];
	can_sig_data.steerangle			= Can[5];
	can_sig_data.steeranglespeed	= Can[6];
	can_sig_data.yawrate			= Can[7];
	can_sig_data.longaccel			= Can[8];
	can_sig_data.lataccel			= Can[9];
}

static void Sim_GetTimeData(void)
{
	int16_t ri, di, tx, rx;
	int16_t i;

	memcpy(gRM_PreData.s16adcData, Sim_RM_TimeData, sizeof(Sim_RM_TimeData));
	memcpy(gLR_PreData.s16adcData, Sim_LR_TimeData, sizeof(Sim_LR_TimeData));
	memcpy(gMR_PreData.s16adcData, Sim_MR_TimeData, sizeof(Sim_MR_TimeData));
	memcpy(gSR_PreData.s16adcData, Sim_SR_TimeData, sizeof(Sim_SR_TimeData));

}


static void Sim_GetPeakData(void)
{

	memcpy(gRM_BeamData.f32PowSpectrum, Sim_RM_PowSpectrum, sizeof(float32_t) * OBJ_RM_NUM_FFT_R * OBJ_RM_NUM_FFT_D);
	memcpy(gLR_BeamData.f32PowSpectrum, Sim_LR_PowSpectrum, sizeof(float32_t) * OBJ_NUM_FFT_R * OBJ_NUM_FFT_D);
	memcpy(gMR_BeamData.f32PowSpectrum, Sim_MR_PowSpectrum, sizeof(float32_t) * OBJ_NUM_FFT_R * OBJ_NUM_FFT_D);
	memcpy(gSR_BeamData.f32PowSpectrum, Sim_SR_PowSpectrum, sizeof(float32_t) * OBJ_NUM_FFT_R * OBJ_NUM_FFT_D);

	

	int16_t i, rx, tx, ri, di;

	gRM_PeakData.s16PeakCnt = Sim_RM_PeakCnt;
	gLR_PeakData.s16PeakCnt = Sim_LR_PeakCnt;
	gMR_PeakData.s16PeakCnt = Sim_MR_PeakCnt;
	gSR_PeakData.s16PeakCnt = Sim_SR_PeakCnt;

	for (i = 0; i < gRM_PeakData.s16PeakCnt; i++)
	{
		gRM_PeakData.rdu16FreqIdx[i].R = (uint16_t)Sim_RM_PeakData[i][0];
		gRM_PeakData.rdu16FreqIdx[i].D = (uint16_t)Sim_RM_PeakData[i][1];
		gRM_PeakData.rdf32EstFreqIdx[i].R = Sim_RM_PeakData[i][2];
		gRM_PeakData.rdf32EstFreqIdx[i].D = Sim_RM_PeakData[i][3];

		for (tx = 0; tx < OBJ_RM_NUM_TX; tx++)
		{
			/* 32 : Num_Rx_ch * (real and imag)*/
			for (rx = 0; rx < OBJ_NUM_RX; rx++)
			{
				gRM_PeakData.cf32FFTData[i][tx][rx].real = Sim_RM_PeakData[i][(2 * rx) + 4 + 2 * OBJ_NUM_RX* tx];
				gRM_PeakData.cf32FFTData[i][tx][rx].imag = Sim_RM_PeakData[i][(2 * rx) + 5 + 2 * OBJ_NUM_RX* tx];
			}
		}
	}

	for (i = 0; i < gLR_PeakData.s16PeakCnt; i++)
	{
		gLR_PeakData.rdu16FreqIdx[i].R = (uint16_t)Sim_LR_PeakData[i][0];
		gLR_PeakData.rdu16FreqIdx[i].D = (uint16_t)Sim_LR_PeakData[i][1];
		gLR_PeakData.rdf32EstFreqIdx[i].R = Sim_LR_PeakData[i][2];
		gLR_PeakData.rdf32EstFreqIdx[i].D = Sim_LR_PeakData[i][3];

		ri = gLR_PeakData.rdu16FreqIdx[i].R;
		di = gLR_PeakData.rdu16FreqIdx[i].D;

		gLR_PeakData.f32SllPow[i] = Sim_LR_PowSpectrum[ri][di];

		for (tx = 0; tx < OBJ_NUM_TX; tx++)
		{
			/* 32 : Num_Rx_ch * (real and imag)*/
			for (rx = 0; rx < OBJ_NUM_RX; rx++)
			{
				gLR_PeakData.cf32FFTData[i][tx][rx].real = Sim_LR_PeakData[i][(2 * rx) + 4 + 2 * OBJ_NUM_RX* tx];
				gLR_PeakData.cf32FFTData[i][tx][rx].imag = Sim_LR_PeakData[i][(2 * rx) + 5 + 2 * OBJ_NUM_RX* tx];
			}
		}
	}

	for (i = 0; i < gMR_PeakData.s16PeakCnt; i++)
	{
		gMR_PeakData.rdu16FreqIdx[i].R = (uint16_t)Sim_MR_PeakData[i][0];
		gMR_PeakData.rdu16FreqIdx[i].D = (uint16_t)Sim_MR_PeakData[i][1];
		gMR_PeakData.rdf32EstFreqIdx[i].R = Sim_MR_PeakData[i][2];
		gMR_PeakData.rdf32EstFreqIdx[i].D = Sim_MR_PeakData[i][3];

		ri = gMR_PeakData.rdu16FreqIdx[i].R;
		di = gMR_PeakData.rdu16FreqIdx[i].D;

		gMR_PeakData.f32SllPow[i] = Sim_MR_PowSpectrum[ri][di];
		
		for (tx = 0; tx < OBJ_NUM_TX; tx++)
		{
			/* 32 : Num_Rx_ch * (real and imag)*/
			for (rx = 0; rx < OBJ_NUM_RX; rx++)
			{
				gMR_PeakData.cf32FFTData[i][tx][rx].real = Sim_MR_PeakData[i][(2 * rx) + 4 + 2 * OBJ_NUM_RX* tx];
				gMR_PeakData.cf32FFTData[i][tx][rx].imag = Sim_MR_PeakData[i][(2 * rx) + 5 + 2 * OBJ_NUM_RX* tx];
			}
		}
	}

	for (i = 0; i < gSR_PeakData.s16PeakCnt; i++)
	{
		gSR_PeakData.rdu16FreqIdx[i].R = (uint16_t)Sim_SR_PeakData[i][0];
		gSR_PeakData.rdu16FreqIdx[i].D = (uint16_t)Sim_SR_PeakData[i][1];
		gSR_PeakData.rdf32EstFreqIdx[i].R = Sim_SR_PeakData[i][2];
		gSR_PeakData.rdf32EstFreqIdx[i].D = Sim_SR_PeakData[i][3];

		ri = gSR_PeakData.rdu16FreqIdx[i].R;
		di = gSR_PeakData.rdu16FreqIdx[i].D;

		gSR_PeakData.f32SllPow[i] = Sim_SR_PowSpectrum[ri][di];
	
		for (tx = 0; tx < OBJ_NUM_TX; tx++)
		{
			/* 32 : Num_Rx_ch * (real and imag)*/
			for (rx = 0; rx < OBJ_NUM_RX; rx++)
			{
				gSR_PeakData.cf32FFTData[i][tx][rx].real = Sim_SR_PeakData[i][(2 * rx) + 4 + 2 * OBJ_NUM_RX* tx];
				gSR_PeakData.cf32FFTData[i][tx][rx].imag = Sim_SR_PeakData[i][(2 * rx) + 5 + 2 * OBJ_NUM_RX* tx];
			}
		}
	}

}


static void Sim_Debug(void)
{
	int16_t i, j, k;
	int16_t ri, di;


	//memset(Object, 0, sizeof(float32_t) * 64* 20);

	memset(Sim_RM_PeakInfo, 0, sizeof(float32_t) * OBJ_NUM_RM_PEAK_MAX * 10);
	memset(Sim_LR_PeakInfo, 0, sizeof(float32_t) * OBJ_NUM_PEAK_MAX * 388);
	memset(Sim_MR_PeakInfo, 0, sizeof(float32_t) * OBJ_NUM_PEAK_MAX * 388);
	memset(Sim_SR_PeakInfo, 0, sizeof(float32_t) * OBJ_NUM_PEAK_MAX * 388);

	memset(Sim_RM_PowSpectrum, 0, sizeof(float32_t) * OBJ_RM_NUM_FFT_R * OBJ_RM_NUM_FFT_D);
	memset(Sim_LR_PowSpectrum, 0, sizeof(float32_t) * OBJ_NUM_FFT_R * OBJ_NUM_FFT_D);
	memset(Sim_MR_PowSpectrum, 0, sizeof(float32_t) * OBJ_NUM_FFT_R * OBJ_NUM_FFT_D);
	memset(Sim_SR_PowSpectrum, 0, sizeof(float32_t) * OBJ_NUM_FFT_R * OBJ_NUM_FFT_D);

	memset(Sim_RM_PowSpectrum_mask, 0, sizeof(uint8_t) * OBJ_RM_NUM_FFT_R * OBJ_RM_NUM_FFT_D);
	memset(Sim_LR_PowSpectrum_mask, 0, sizeof(uint8_t) * OBJ_NUM_FFT_R * OBJ_NUM_FFT_D);
	memset(Sim_MR_PowSpectrum_mask, 0, sizeof(uint8_t) * OBJ_NUM_FFT_R * OBJ_NUM_FFT_D);
	memset(Sim_SR_PowSpectrum_mask, 0, sizeof(uint8_t) * OBJ_NUM_FFT_R * OBJ_NUM_FFT_D);

	memcpy(Sim_RM_PowSpectrum, gRM_BeamData.f32PowSpectrum, sizeof(float32_t) * OBJ_RM_NUM_FFT_R * OBJ_RM_NUM_FFT_D);
	memcpy(Sim_LR_PowSpectrum, gLR_BeamData.f32PowSpectrum, sizeof(float32_t) * OBJ_NUM_FFT_R * OBJ_NUM_FFT_D);
	memcpy(Sim_MR_PowSpectrum, gMR_BeamData.f32PowSpectrum, sizeof(float32_t) * OBJ_NUM_FFT_R * OBJ_NUM_FFT_D);
	memcpy(Sim_SR_PowSpectrum, gSR_BeamData.f32PowSpectrum, sizeof(float32_t) * OBJ_NUM_FFT_R * OBJ_NUM_FFT_D);

	memcpy(Sim_RM_DoppCfarOut, gRM_BeamData.u8CfarOut_D, sizeof(uint8_t) * OBJ_RM_NUM_FFT_R * OBJ_RM_NUM_FFT_D);
	memcpy(Sim_LR_DoppCfarOut, gLR_BeamData.u8CfarOut_D, sizeof(uint8_t) * OBJ_NUM_FFT_R * OBJ_NUM_FFT_D);
	memcpy(Sim_MR_DoppCfarOut, gMR_BeamData.u8CfarOut_D, sizeof(uint8_t) * OBJ_NUM_FFT_R * OBJ_NUM_FFT_D);
	memcpy(Sim_SR_DoppCfarOut, gSR_BeamData.u8CfarOut_D, sizeof(uint8_t) * OBJ_NUM_FFT_R * OBJ_NUM_FFT_D);

	for (ri = 0; ri < OBJ_RM_NUM_FFT_R; ri++)
	{
		for (di = 0; di < OBJ_RM_NUM_FFT_D; di++)
		{
			Sim_RM_PowSpectrum_log[ri][di] = 20 * _sp_log10f(Sim_RM_PowSpectrum[ri][di]);
		}
	}

	for (ri = 0; ri < OBJ_NUM_FFT_R; ri++)
	{
		for (di = 0; di < OBJ_NUM_FFT_D; di++)
		{
			Sim_LR_PowSpectrum_log[ri][di] = 20 * _sp_log10f(Sim_LR_PowSpectrum[ri][di]);
			Sim_MR_PowSpectrum_log[ri][di] = 20 * _sp_log10f(Sim_MR_PowSpectrum[ri][di]);
			Sim_SR_PowSpectrum_log[ri][di] = 20 * _sp_log10f(Sim_SR_PowSpectrum[ri][di]);
		}
	}


	Sim_RM_BaseTh = OBJ_CFAR_RM_BASE_THRESHOLD_D;
	Sim_LR_BaseTh = OBJ_CFAR_LR_BASE_THRESHOLD_D;
	Sim_MR_BaseTh = OBJ_CFAR_MR_BASE_THRESHOLD_D;
	Sim_SR_BaseTh = OBJ_CFAR_SR_BASE_THRESHOLD_D;

	/* R Mode*/
	for (ri = 0; ri < OBJ_RM_NUM_FFT_R; ri++)
	{
		for (di = 0; di < OBJ_RM_NUM_FFT_D; di++)
		{
			Sim_RM_RangeCfarTh[ri][di] = gRM_BeamData.f32CfarTh_R[di][ri];
			Sim_RM_DoppCfarTh[ri][di] = gRM_BeamData.f32CfarTh_D[ri][di];
		}
	}

	/* D Mode */
	for (ri = 0; ri < OBJ_NUM_FFT_R; ri++)
	{
		for (di = 0; di < OBJ_NUM_FFT_D; di++)
		{

			Sim_LR_RangeCfarTh[ri][di] = gLR_BeamData.f32CfarTh_R[di][ri];
			Sim_LR_DoppCfarTh[ri][di] = gLR_BeamData.f32CfarTh_D[ri][di];

			Sim_MR_RangeCfarTh[ri][di] = gMR_BeamData.f32CfarTh_R[di][ri];
			Sim_MR_DoppCfarTh[ri][di] = gMR_BeamData.f32CfarTh_D[ri][di];

			Sim_SR_RangeCfarTh[ri][di] = gSR_BeamData.f32CfarTh_R[di][ri];
			Sim_SR_DoppCfarTh[ri][di] = gSR_BeamData.f32CfarTh_D[ri][di];
		}
	}

	/* Peak Data */

	Sim_RM_PeakCnt = gRM_PeakData.s16PeakCnt;
	Sim_LR_PeakCnt = gLR_PeakData.s16PeakCnt;
	Sim_MR_PeakCnt = gMR_PeakData.s16PeakCnt;
	Sim_SR_PeakCnt = gSR_PeakData.s16PeakCnt;

	int16_t peak_idx;
	int16_t temp_ri_idx;
	int16_t temp_di_idx;

	for (peak_idx = 0; peak_idx < Sim_RM_PeakCnt; peak_idx++)
	{	
		temp_ri_idx = (uint16_t)Sim_RM_PeakData[peak_idx][0];
		temp_di_idx = (uint16_t)Sim_RM_PeakData[peak_idx][1];
		Sim_RM_PowSpectrum_mask[temp_ri_idx][temp_di_idx] = 1;
	}

	for (peak_idx = 0; peak_idx < Sim_LR_PeakCnt; peak_idx++)
	{
		temp_ri_idx = (uint16_t)Sim_LR_PeakData[peak_idx][0];
		temp_di_idx = (uint16_t)Sim_LR_PeakData[peak_idx][1];
		Sim_LR_PowSpectrum_mask[temp_ri_idx][temp_di_idx] = 1;
	}

	for (peak_idx = 0; peak_idx < Sim_MR_PeakCnt; peak_idx++)
	{
		temp_ri_idx = (uint16_t)Sim_MR_PeakData[peak_idx][0];
		temp_di_idx = (uint16_t)Sim_MR_PeakData[peak_idx][1];
		Sim_MR_PowSpectrum_mask[temp_ri_idx][temp_di_idx] = 1;
	}

	for (peak_idx = 0; peak_idx < Sim_SR_PeakCnt; peak_idx++)
	{
		temp_ri_idx = (uint16_t)Sim_SR_PeakData[peak_idx][0];
		temp_di_idx = (uint16_t)Sim_SR_PeakData[peak_idx][1];
		Sim_SR_PowSpectrum_mask[temp_ri_idx][temp_di_idx] = 1;
	}



	for (i = 0; i < Sim_RM_PeakCnt; i++)
	{
		Sim_RM_PeakInfo[i][0] = (float32_t)gRM_PeakData.rdu16FreqIdx[i].R;
		Sim_RM_PeakInfo[i][1] = (float32_t)gRM_PeakData.rdu16FreqIdx[i].D;
		Sim_RM_PeakInfo[i][2] = gRM_PeakData.rdf32EstFreqIdx[i].R;
		Sim_RM_PeakInfo[i][3] = gRM_PeakData.rdf32EstFreqIdx[i].D;
		Sim_RM_PeakInfo[i][4] = gRM_PeakData.f32Range[i];
		Sim_RM_PeakInfo[i][5] = gRM_PeakData.f32Velocity[i];
		Sim_RM_PeakInfo[i][6] = gRM_PeakData.f32AziAngle[i][0];
		Sim_RM_PeakInfo[i][7] = gRM_PeakData.f32Power[i][0];
	}


	//Sim_LR_PeakCnt = gLR_PeakData.s16PhCnt;
	//Sim_MR_PeakCnt = gMR_PeakData.s16PhCnt;
	//Sim_SR_PeakCnt = gSR_PeakData.s16PhCnt;

	for (i = 0; i < Sim_LR_PeakCnt; i++)
	{
		Sim_LR_PeakInfo[i][0] = (float32_t)gLR_PeakData.rdu16FreqIdx[i].R;
		Sim_LR_PeakInfo[i][1] = (float32_t)gLR_PeakData.rdu16FreqIdx[i].D;
		Sim_LR_PeakInfo[i][2] = 0.0f;
		Sim_LR_PeakInfo[i][3] = 0.0f;

		Sim_LR_PeakInfo[i][4] = gLR_PeakData.f32Range[i][0];
		Sim_LR_PeakInfo[i][5] = gLR_PeakData.f32Velocity[i][0];
		Sim_LR_PeakInfo[i][6] = 20.0f*_sp_log10f(gLR_PeakData.f32SllPow[i]);
	}


	for (i = 0; i < Sim_MR_PeakCnt; i++)
	{
		Sim_MR_PeakInfo[i][0] = (float32_t)gMR_PeakData.rdu16FreqIdx[i].R;
		Sim_MR_PeakInfo[i][1] = (float32_t)gMR_PeakData.rdu16FreqIdx[i].D;
		Sim_MR_PeakInfo[i][2] = 0.0f;
		Sim_MR_PeakInfo[i][3] = 0.0f;

		Sim_MR_PeakInfo[i][4] = gMR_PeakData.f32Range[i][0];
		Sim_MR_PeakInfo[i][5] = gMR_PeakData.f32Velocity[i][0];
		Sim_MR_PeakInfo[i][6] = 20.0f*_sp_log10f(gMR_PeakData.f32SllPow[i]);
	}

	for (i = 0; i < Sim_SR_PeakCnt; i++)
	{
		Sim_SR_PeakInfo[i][0] = (float32_t)gSR_PeakData.rdu16FreqIdx[i].R;
		Sim_SR_PeakInfo[i][1] = (float32_t)gSR_PeakData.rdu16FreqIdx[i].D;
		Sim_SR_PeakInfo[i][2] = 0.0f;
		Sim_SR_PeakInfo[i][3] = 0.0f;

		Sim_SR_PeakInfo[i][4] = gSR_PeakData.f32Range[i][0];
		Sim_SR_PeakInfo[i][5] = gSR_PeakData.f32Velocity[i][0];
		Sim_SR_PeakInfo[i][6] = 20.0f*_sp_log10f(gSR_PeakData.f32SllPow[i]);
	}


	for (i = 0; i < Sim_LR_PeakCnt; i++)
	{
		for (j = 0; j < OBJ_AE_AZI_LR_NUM_APS_STEPS*OBJ_AE_ELE_LR_NUM_APS_STEPS; j++)
		{
			Sim_LR_APS[i][j] = gLR_PeakData.f32APS[i][j];
		}
	}


	for (i = 0; i < Sim_MR_PeakCnt; i++)
	{
		for (j = 0; j < OBJ_AE_AZI_MR_NUM_APS_STEPS*OBJ_AE_ELE_MR_NUM_APS_STEPS; j++)
		{
			Sim_MR_APS[i][j] = gMR_PeakData.f32APS[i][j];
		}
	}


	for (i = 0; i < Sim_SR_PeakCnt; i++)
	{
		for (j = 0; j < OBJ_AE_AZI_SR_NUM_APS_STEPS*OBJ_AE_ELE_SR_NUM_APS_STEPS; j++)
		{
			Sim_SR_APS[i][j] = gSR_PeakData.f32APS[i][j];
		}
	}


	for (i = 0; i < Sim_RM_PeakCnt; i++)
	{
		for (j = 0; j < OBJ_AE_AZI_RM_NUM_APS_STEPS; j++)
		{

			Sim_RM_APS[i][j] = gRM_PeakData.f32APS[i][j];
		}
	}


	for (i = 0; i < OBJ_AE_AZI_LR_NUM_APS_STEPS; i++)
	{
		Sim_LR_AziAngleTable[i] = gLR_PeakData.f32AziAngTable[i];
	}

	for (i = 0; i < OBJ_AE_ELE_LR_NUM_APS_STEPS; i++)
	{
		Sim_LR_EleAngleTable[i] = gLR_PeakData.f32EleAngTable[i];
	}

	for (i = 0; i < OBJ_AE_AZI_MR_NUM_APS_STEPS; i++)
	{
		Sim_MR_AziAngleTable[i] = gMR_PeakData.f32AziAngTable[i];
	}

	for (i = 0; i < OBJ_AE_ELE_MR_NUM_APS_STEPS; i++)
	{
		Sim_MR_EleAngleTable[i] = gMR_PeakData.f32EleAngTable[i];
	}

	for (i = 0; i < OBJ_AE_AZI_SR_NUM_APS_STEPS; i++)
	{
		Sim_SR_AziAngleTable[i] = gSR_PeakData.f32AziAngTable[i];
	}

	for (i = 0; i < OBJ_AE_ELE_SR_NUM_APS_STEPS; i++)
	{
		Sim_SR_EleAngleTable[i] = gSR_PeakData.f32EleAngTable[i];
	}

	for (i = 0; i < OBJ_AE_AZI_RM_NUM_APS_STEPS; i++)
	{
		Sim_RM_AziAngleTable[i] = gRM_PeakData.f32AziAngTable[i];
	}

}


static void Sim_ObjectOut(void)
{
	memset(Sim_ObjInfo, 0, sizeof(float32_t)*SP_NUM_OBJECT_MAX * 20);
	memset(Sim_REF_ObjInfo, 0, sizeof(float32_t)*(OBJ_NUM_RM_CANDIDATE_OBJ) * 20);

	int16_t i, i_msmt;

	Sim_OutObjCnt = gObjOutCnt;
	Sim_OutFilObjCnt = gFilteredObjCnt;
	Sim_REF_OutObjCnt = gRM_ObjData.s16ObjCnt;


	for (i = 0; i < Sim_OutObjCnt; i++)
	{
		Sim_ObjInfo[i][0] = Sp_ObjectOut[i].f32Range_m;
		Sim_ObjInfo[i][1] = Sp_ObjectOut[i].f32Velocity_mps;
		Sim_ObjInfo[i][2] = Sp_ObjectOut[i].f32AziAng_deg;
		Sim_ObjInfo[i][3] = Sp_ObjectOut[i].f32EleAng_deg;
		Sim_ObjInfo[i][4] = Sp_ObjectOut[i].f32Power_dB;
		Sim_ObjInfo[i][5] = 0.0f;
		Sim_ObjInfo[i][6] = Sp_ObjectOut[i].u8ModType;

		Sim_ObjInfo[i][7] = 0.0f;
		Sim_ObjInfo[i][8] = gObjectOut[i].rdu16FreqIdx.R;
		Sim_ObjInfo[i][9] = gObjectOut[i].rdu16FreqIdx.D;
		Sim_ObjInfo[i][10] = gObjectOut[i].s16PeakIdx;
		Sim_ObjInfo[i][11] = 0.0f;
		Sim_ObjInfo[i][12] = gObjectOut[i].eGFType;
		Sim_ObjInfo[i][13] = 0.0f;
		Sim_ObjInfo[i][14] = 0.0f;
		Sim_ObjInfo[i][15] = gObjectOut[i].s16HarmIdx;
		Sim_ObjInfo[i][16] = gObjectOut[i].s16MatRefPeakIdx;
		Sim_ObjInfo[i][17] = 0.0f;
		Sim_ObjInfo[i][18] = 0.0f;
		Sim_ObjInfo[i][19] = gObjectOut[i].f32PreAziAngle;
		Sim_ObjInfo[i][20] = gObjectOut[i].f32PrePow;
		Sim_ObjInfo[i][21] = gObjectOut[i].f32SllPowdB;


	}

	for (i = Sim_OutObjCnt; i < SP_NUM_OBJECT_MAX; i++)
	{
		Sim_ObjInfo[i][0] = 0.0f;
		Sim_ObjInfo[i][1] = 0.0f;
		Sim_ObjInfo[i][2] = 0.0f;
		Sim_ObjInfo[i][3] = 0.0f;
		Sim_ObjInfo[i][4] = 0.0f;
		Sim_ObjInfo[i][5] = 0.0f;
		Sim_ObjInfo[i][6] = 0.0f;

		Sim_ObjInfo[i][7] = 0.0f;
		Sim_ObjInfo[i][8] = 0.0f;
		Sim_ObjInfo[i][9] = 0.0f;
		Sim_ObjInfo[i][10] = 0.0f;
		Sim_ObjInfo[i][11] = 0.0f;
		Sim_ObjInfo[i][12] = 0.0f;
		Sim_ObjInfo[i][13] = 0.0f;
		Sim_ObjInfo[i][14] = 0.0f;
		Sim_ObjInfo[i][15] = 0.0f;
		Sim_ObjInfo[i][16] = 0.0f;
		Sim_ObjInfo[i][17] = 0.0f;
		Sim_ObjInfo[i][18] = 0.0f;
	}

	for (i = 0; i < Sim_REF_OutObjCnt; i++)
	{
		Sim_REF_ObjInfo[i][0] = gRM_ObjData.ObjData[i].f32Range;									/* Range   */
		Sim_REF_ObjInfo[i][1] = gRM_ObjData.ObjData[i].f32Velocity;									/* Velocity */
		Sim_REF_ObjInfo[i][2] = gRM_ObjData.ObjData[i].f32AziAngle;								/* Angle   */
		Sim_REF_ObjInfo[i][3] = 0.0f;
		Sim_REF_ObjInfo[i][4] = gRM_ObjData.ObjData[i].f32Power;									/* Power   */
		Sim_REF_ObjInfo[i][5] = 0.0f;
		Sim_REF_ObjInfo[i][6] = RM_MOD;
		Sim_REF_ObjInfo[i][7] = 0.0f;
		Sim_REF_ObjInfo[i][8] = (float32_t)gRM_ObjData.ObjData[i].rdu16FreqIdx.R;				/* Freq R */
		Sim_REF_ObjInfo[i][9] = (float32_t)gRM_ObjData.ObjData[i].rdu16FreqIdx.D;				/* Freq D */
		Sim_REF_ObjInfo[i][10] = 0.0f;
		Sim_REF_ObjInfo[i][11] = 0.0f;
		Sim_REF_ObjInfo[i][12] = 0.0f;
		Sim_REF_ObjInfo[i][13] = 0.0f;
		Sim_REF_ObjInfo[i][14] = 0.0f;
	}


	for (i = 0; i < Sim_OutFilObjCnt; i++)
	{
		Sim_FilObjInfo[i][0] = gFilteredObj[i].f32Range_m;
		Sim_FilObjInfo[i][1] = gFilteredObj[i].f32Velocity_mps;
		Sim_FilObjInfo[i][2] = gFilteredObj[i].f32AziAng_deg;
		Sim_FilObjInfo[i][3] = gFilteredObj[i].f32EleAng_deg;
		Sim_FilObjInfo[i][4] = gFilteredObj[i].f32Power_dB;
		Sim_FilObjInfo[i][5] = 0.0f;
		Sim_FilObjInfo[i][6] = gFilteredObj[i].eModType;
		Sim_FilObjInfo[i][7] = 0.0f;
		Sim_FilObjInfo[i][8] = gFilteredObj[i].rdu16FreqIdx.R;
		Sim_FilObjInfo[i][9] = gFilteredObj[i].rdu16FreqIdx.D;
		Sim_FilObjInfo[i][10] = gFilteredObj[i].s16PeakIdx;
		Sim_FilObjInfo[i][11] = 0.0f;
		Sim_FilObjInfo[i][12] = gFilteredObj[i].eGFType;
		Sim_FilObjInfo[i][13] = 0.0f;
		Sim_FilObjInfo[i][14] = 0.0f;
		Sim_FilObjInfo[i][15] = gFilteredObj[i].s16HarmIdx;
		Sim_FilObjInfo[i][16] = gFilteredObj[i].s16MatRefPeakIdx;

		Sim_FilObjInfo[i][17] = 0.0f;
		Sim_FilObjInfo[i][18] = 0.0f;

		Sim_FilObjInfo[i][19] = gFilteredObj[i].f32PreAziAngle;
		Sim_FilObjInfo[i][20] = gFilteredObj[i].f32PrePow;
		Sim_FilObjInfo[i][21] = gFilteredObj[i].f32SllPowdB;
	}

	for (i = Sim_OutFilObjCnt; i < OBJ_NUM_FILETERD_OBJ_MAX; i++)
	{
		Sim_FilObjInfo[i][0] = 0.0f;
		Sim_FilObjInfo[i][1] = 0.0f;
		Sim_FilObjInfo[i][2] = 0.0f;
		Sim_FilObjInfo[i][3] = 0.0f;
		Sim_FilObjInfo[i][4] = 0.0f;
		Sim_FilObjInfo[i][5] = 0.0f;
		Sim_FilObjInfo[i][6] = 0.0f;
		Sim_FilObjInfo[i][7] = 0.0f;
		Sim_FilObjInfo[i][8] = 0.0f;
		Sim_FilObjInfo[i][9] = 0.0f;
		Sim_FilObjInfo[i][10] = 0.0f;
		Sim_FilObjInfo[i][11] = 0.0f;
		Sim_FilObjInfo[i][12] = 0.0f;
		Sim_FilObjInfo[i][13] = 0.0f;
		Sim_FilObjInfo[i][14] = 0.0f;

		Sim_FilObjInfo[i][15] = 0.0f;
		Sim_FilObjInfo[i][16] = 0.0f;
		Sim_FilObjInfo[i][17] = 0.0f;
		Sim_FilObjInfo[i][18] = 0.0f;
		Sim_FilObjInfo[i][19] = 0.0f;
		Sim_FilObjInfo[i][20] = 0.0f;
		Sim_FilObjInfo[i][21] = 0.0f;
	}

}


static void Sim_ClusterOut(void)
{
	uint16_t i;

#ifndef WIN32
	for (i = 0; i < SP_NUM_CLST_MAX; i++)
	{
		Sim_TrkletInfo[i][0] = gClstData[i].Status;
		Sim_TrkletInfo[i][1] = gClstData[i].u16AliveAge;
		Sim_TrkletInfo[i][2] = gClstData[i].u16StatusAge;
		Sim_TrkletInfo[i][3] = gClstData[i].s16NewTrkTrans_Score;
		Sim_TrkletInfo[i][4] = gClstData[i].f32UpdStateX[0];
		Sim_TrkletInfo[i][5] = gClstData[i].f32UpdStateY[0];
		Sim_TrkletInfo[i][6] = gClstData[i].f32UpdStateX[1];
		Sim_TrkletInfo[i][7] = gClstData[i].f32UpdStateY[1];
		Sim_TrkletInfo[i][8] = 0.0f;
		Sim_TrkletInfo[i][9] = gClstData[i].MovState;
		Sim_TrkletInfo[i][10] = gClstData[i].s16MoveStateCnt;
		Sim_TrkletInfo[i][11] = 0.0f;
		Sim_TrkletInfo[i][12] = gClstData[i].s16GroupInconsistentCnt;
		Sim_TrkletInfo[i][13] = i;
#if _DEBUG_VE
		Sim_TrkletInfo[i][18] = gTrackletData[i].f32VelMsmt[0];
		Sim_TrkletInfo[i][19] = gTrackletData[i].f32VelMsmt[1];
#endif
	}

#else
	for (i = 0; i < SP_NUM_CLST_MAX; i++)
	{
		Sim_TrkletInfo[i][0] = 0;
		Sim_TrkletInfo[i][1] = 0;
		Sim_TrkletInfo[i][2] = 0;
		Sim_TrkletInfo[i][3] = 0;
		Sim_TrkletInfo[i][4] = 0;
		Sim_TrkletInfo[i][5] = 0;
		Sim_TrkletInfo[i][6] = 0;
		Sim_TrkletInfo[i][7] = 0;
		Sim_TrkletInfo[i][8] = 0;
		Sim_TrkletInfo[i][9] = 0;
		Sim_TrkletInfo[i][10] = 0;
		Sim_TrkletInfo[i][11] = 0;
		Sim_TrkletInfo[i][12] = 0;
		Sim_TrkletInfo[i][13] = 0;
#if _DEBUG_VE
		Sim_TrkletInfo[i][18] = 0;
		Sim_TrkletInfo[i][19] = 0;
#endif
	}

#endif
}


static void Sim_TrackOut(void)
{
	int16_t i;

	for (i = 0; i < SP_NUM_TRACK_MAX; i++)
	{
		Sim_TrkInfo[i][0] = gTrackData[i].Status;
		Sim_TrkInfo[i][1] = gTrackData[i].u16AliveAge;
		Sim_TrkInfo[i][2] = gTrackData[i].u16StatusAge;
		Sim_TrkInfo[i][3] = gTrackData[i].UpdState.f32StateX[0];
		Sim_TrkInfo[i][4] = gTrackData[i].UpdState.f32StateY[0];
		Sim_TrkInfo[i][5] = gTrackData[i].UpdState.f32StateX[1];
		Sim_TrkInfo[i][6] = gTrackData[i].UpdState.f32StateY[1];
		Sim_TrkInfo[i][7] = gTrackData[i].f32Pow_dB;
		Sim_TrkInfo[i][8] = gTrackData[i].UpdState.f32StateHeading[0];
		Sim_TrkInfo[i][9] = gTrackData[i].UpdState.f32StateHeading[1];
		Sim_TrkInfo[i][10] = gTrackData[i].UpdState.f32Length;
		Sim_TrkInfo[i][11] = gTrackData[i].UpdState.f32Width;
		Sim_TrkInfo[i][12] = gTrackData[i].UpdState.f32Ref_PosX;
		Sim_TrkInfo[i][13] = gTrackData[i].UpdState.f32Ref_PosY;
		Sim_TrkInfo[i][14] = 0;
		Sim_TrkInfo[i][15] = 0;
		Sim_TrkInfo[i][16] = gTrackData[i].u8Merging_Flag;
		Sim_TrkInfo[i][17] = gTrackData[i].MovState;
		Sim_TrkInfo[i][18] = i;
		Sim_TrkInfo[i][19] = 0;
		Sim_TrkInfo[i][20] = 0;
		Sim_TrkInfo[i][23] = 0;
		Sim_TrkInfo[i][24] = 0;
	}
}


static void Sim_AppOut(void)
{

}
