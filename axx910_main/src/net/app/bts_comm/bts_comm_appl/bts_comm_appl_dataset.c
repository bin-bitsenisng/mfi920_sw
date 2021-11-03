/************************************************************************
| Project Name: bts_comm_appl_dataset
|    File Name: bts_comm_appl_dataset.c
|  Description: file detailed description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------
| SKJ          SONG KYEONG JIN           Lobeye
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description
| ----------  ----  ------  --------------------------------------------
| 2018.06.26   0.0   SKJ   Creation;
|***********************************************************************/

/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"
#include <string.h>

/* include system driver header */
//#include "drivers.h"
#include "krs_lib.h"

/* include system bsp header */
#include "os.h"

/* include system application header */
#include "sys_param.h"

#include "rsp_main.h"
#include "rsp_thread.h"
/* final include module header */
#include "bts_comm.h"
#include "bts_comm_appl.h"
#include "bts_comm_cmd.h"
#include "bts_comm_packet.h"
#include "bts_comm_status.h"
#include "Sp_Parameters.h"

//#include "Sp_Main.h"
#include "Obj_Main.h"
//#include "App_Main.h"
/* declare global variables */

char_t bts_comm_appl_dataset_json_buffer[bts_COMM_APPL_DATASET_JSON_BUFFER_SIZE];

sys_param_pid0_status_data_t appljson_pid0_status_data;

#define SYS_RAW_MAX_FRAME_NUM N_FRAME_MAX
#if (SYS_APP_TYPE == SYS_APP_TYPE_ITS) || (SYS_APP_TYPE == SYS_APP_TYPE_FCW) || (SYS_APP_TYPE == SYS_APP_TYPE_LEVELMETER)
#if SYS_RSM_LONGFIRST == 0
#define SYS_RAW_CHIRP_UPFMT "2048h"
#define SYS_RAW_CHIRP_DNFMT "2048h"
#define SYS_RAW_CHIRP_UP2FMT "4096h"
#define SYS_RAW_CHIRP_DN2FMT "4096h"
#define SYS_RAW_CHIRP_ALL   "1048576h"
#elif SYS_RSM_LONGFIRST == 1
#define SYS_RAW_CHIRP_UPFMT "4096h"
#define SYS_RAW_CHIRP_DNFMT "4096h"
#define SYS_RAW_CHIRP_UP2FMT "2048h"
#define SYS_RAW_CHIRP_DN2FMT "2048h"
#else
#error "invalid SYS_RSM_LONGFIRST value for ITS"
#endif
#elif SYS_APP_TYPE == SYS_APP_TYPE_VF
#if SYS_RSM_N_TIMEDATA_MAX == 1024
#define SYS_RAW_CHIRP_UPFMT "1024h"
#elif SYS_RSM_N_TIMEDATA_MAX == 2048
#define SYS_RAW_CHIRP_UPFMT "2048h"
#elif SYS_RSM_N_TIMEDATA_MAX == 4096
#define SYS_RAW_CHIRP_UPFMT "4096h"
#elif SYS_RSM_N_TIMEDATA_MAX == 8192
#define SYS_RAW_CHIRP_UPFMT "8192h"
#elif SYS_RSM_N_TIMEDATA_MAX == 16384
#define SYS_RAW_CHIRP_UPFMT "16384h"
#else
#error "invalid SYS_RSM_N_TIMEDATA_MAX parameter"
#endif
#elif SYS_APP_TYPE == SYS_APP_TYPE_MARINE
#if SYS_RSM_LONGFIRST == 0
#define SYS_RAW_CHIRP_UPFMT "4096h"
#define SYS_RAW_CHIRP_DNFMT "4096h"
#define SYS_RAW_CHIRP_UP2FMT "8192h"
#define SYS_RAW_CHIRP_DN2FMT "8192h"
#elif SYS_RSM_LONGFIRST == 1
#define SYS_RAW_CHIRP_UPFMT "8192h"
#define SYS_RAW_CHIRP_DNFMT "8192h"
#define SYS_RAW_CHIRP_UP2FMT "4096h"
#define SYS_RAW_CHIRP_DN2FMT "4096h"
#else
#error "invalid SYS_RSM_LONGFIRST value for MARINE"
#endif
#elif SYS_APP_TYPE == SYS_APP_TYPE_FI
#define SYS_PEAK_DATA_SIZE 0
/*#if SYS_RSM_N_TIMEDATA_MAX == 1024
	#define SYS_RAW_CHIRP_UPFMT "1024h"
#elif SYS_RSM_N_TIMEDATA_MAX == 2048
	#define SYS_RAW_CHIRP_UPFMT "2048h"
#elif SYS_RSM_N_TIMEDATA_MAX == 4096
	#define SYS_RAW_CHIRP_UPFMT "4096h"
#elif SYS_RSM_N_TIMEDATA_MAX == 8192
	#define SYS_RAW_CHIRP_UPFMT "8192h"
#elif SYS_RSM_N_TIMEDATA_MAX == 16384
	#define SYS_RAW_CHIRP_UPFMT "16384h"
#else
	#error "invalid SYS_RSM_N_TIMEDATA_MAX parameter"
#endif*/
#else
#error "invalid SYS_APP_TYPE"
#endif


uint8_t bts_comm_daqinfo_pid2index_lut[bts_comm_pid_max];
uint8_t bts_comm_daqinfo_index2pid_lut[bts_comm_pid_max];
bts_comm_daqinfo_t bts_comm_daqinfo[] = {
	// Packet ID for Default data
	DAQINFO_APPL(SYS_PID_STATUS_EN, &SYS_PARAM_SENSORTYPE.pid_status_en , bts_comm_pid_status, "status"), // 0
	DAQINFO_APPL(SYS_PID_OBJECT_EN, &SYS_PARAM_SENSORTYPE.pid_object_en, bts_comm_pid_object, "object"), // 1
	DAQINFO_APPL(SYS_PID_TRACK_EN, &SYS_PARAM_SENSORTYPE.pid_track_en, bts_comm_pid_track, "track"),    // 2
	DAQINFO_APPL(SYS_PID_IMAGE_EN,  &SYS_PARAM_SENSORTYPE.pid_image_en, bts_comm_pid_image, "image"),   // 3
	DAQINFO_APPL(SYS_PID_IMAGSP_EN,  &SYS_PARAM_SENSORTYPE.pid_imagsp_en,  bts_comm_pid_imagsp, "imagsp"),   // 4
	DAQINFO_APPL(SYS_PID_LOGGER_EN,  &SYS_PARAM_SENSORTYPE.pid_logger_en,bts_comm_pid_logger, "logger"),// 5
	DAQINFO_APPL(SYS_PID_CANLOG_EN,  &SYS_PARAM_SENSORTYPE.pid_canlog_en,bts_comm_pid_canlog, "canlog"),         // 6
	DAQINFO_APPL(SYS_PID_SENSOR_EN,  &SYS_PARAM_SENSORTYPE.pid_sensor_en,bts_comm_pid_sensor, "sensor"),         // 7

	// Packet ID for Applicaton Data
	DAQINFO_APPL(SYS_PID_APP_ITS_EN, &SYS_PARAM_SENSORTYPE.pid_app_its_en,bts_comm_pid_app_its, "its"),               // 8
	DAQINFO_APPL(SYS_PID_APP_VF_EN, &SYS_PARAM_SENSORTYPE.pid_app_vf_en,bts_comm_pid_app_vf, "vf"),                  // 9
	DAQINFO_APPL(SYS_PID_APP_FCW_EN, &SYS_PARAM_SENSORTYPE.pid_app_fcw_en, bts_comm_pid_app_fcw, "fcw"),              // 10
	DAQINFO_APPL(SYS_PID_APP_LM_EN, &SYS_PARAM_SENSORTYPE.pid_app_lm_en, bts_comm_pid_app_lm, "lm"),              // 11
	//DAQINFO_APPL(SYS_PID_AI_OBJECT_EN, &SYS_PARAM_SENSORTYPE.pid_ai_object_en, bts_comm_pid_ai_object, "ai_object"),  // 12
	//DAQINFO_APPL(SYS_PID_AI_OBJECT_EN, &SYS_PARAM_SENSORTYPE.pid_object_en, bts_comm_pid_ai_object, "ai_object"),  // 12
	//DAQINFO_APPL(SYS_PID_LANE_DETCION_EN, &SYS_PARAM_SENSORTYPE.pid_lane_en, bts_comm_pid_lane, "lane"),  // 13
	//DAQINFO_APPL(SYS_PID_LANE_DETCION_EN, &SYS_PARAM_SENSORTYPE.pid_object_en, bts_comm_pid_lane_detection, "lane"),  // 13
	//DAQINFO_APPL(SYS_PID_FREESPACE_EN, &SYS_PARAM_SENSORTYPE.pid_freespace_en, bts_comm_pid_freespace, "freespace"),  // 14
	//DAQINFO_APPL(SYS_PID_FREESPACE_EN, &SYS_PARAM_SENSORTYPE.pid_object_en, bts_comm_pid_freespace, "freespace"),  // 14

	// Packet ID for Radar Chirp Data, it will be merged in to logger PID and deprecated in the future
	//DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp_en,"Sim_TimeData", &gPreData.s16adcData, SP_NUM_TX*SP_NUM_RX*SP_NUM_CHIRPS*SP_NUM_SAMPLES*2, SYS_RAW_CHIRP_ALL, NULL),

#if SYS_RAW_MAX_FRAME_NUM > 0
		DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP0_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp0_en,"PreData_Up_0", &PreData_Up[0].s16Time_Data[0], sizeof(PreData_Up[0].s16Time_Data), SYS_RAW_CHIRP_UPFMT, NULL),
		DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP1_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp1_en,"PreData_Up_1", &PreData_Up[1].s16Time_Data[0], sizeof(PreData_Up[1].s16Time_Data), SYS_RAW_CHIRP_UPFMT, NULL),
		DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP2_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp2_en,"PreData_Up_2", &PreData_Up[2].s16Time_Data[0], sizeof(PreData_Up[2].s16Time_Data), SYS_RAW_CHIRP_UPFMT, NULL),
		DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP3_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp3_en,"PreData_Up_3", &PreData_Up[3].s16Time_Data[0], sizeof(PreData_Up[3].s16Time_Data), SYS_RAW_CHIRP_UPFMT, NULL),
#endif
#if SYS_RAW_MAX_FRAME_NUM > 1
		DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP0_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp0_en,"PreData_Dn_0", &PreData_Dn[0].s16Time_Data[0], sizeof(PreData_Dn[0].s16Time_Data), SYS_RAW_CHIRP_DNFMT, NULL),
		DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP1_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp1_en,"PreData_Dn_1", &PreData_Dn[1].s16Time_Data[0], sizeof(PreData_Dn[1].s16Time_Data), SYS_RAW_CHIRP_DNFMT, NULL),
		DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP2_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp2_en,"PreData_Dn_2", &PreData_Dn[2].s16Time_Data[0], sizeof(PreData_Dn[2].s16Time_Data), SYS_RAW_CHIRP_DNFMT, NULL),
		DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP3_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp3_en,"PreData_Dn_3", &PreData_Dn[3].s16Time_Data[0], sizeof(PreData_Dn[3].s16Time_Data), SYS_RAW_CHIRP_DNFMT, NULL),
#endif
#if SYS_RAW_MAX_FRAME_NUM > 2
		DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP0_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp0_en,"PreData_Up2_0", &PreData_Up2[0].s16Time_Data[0], sizeof(PreData_Up2[0].s16Time_Data), SYS_RAW_CHIRP_UP2FMT, NULL),
		DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP1_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp1_en,"PreData_Up2_1", &PreData_Up2[1].s16Time_Data[0], sizeof(PreData_Up2[1].s16Time_Data), SYS_RAW_CHIRP_UP2FMT, NULL),
		DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP2_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp2_en,"PreData_Up2_2", &PreData_Up2[2].s16Time_Data[0], sizeof(PreData_Up2[2].s16Time_Data), SYS_RAW_CHIRP_UP2FMT, NULL),
		DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP3_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp3_en,"PreData_Up2_3", &PreData_Up2[3].s16Time_Data[0], sizeof(PreData_Up2[3].s16Time_Data), SYS_RAW_CHIRP_UP2FMT, NULL),
#endif
#if SYS_RAW_MAX_FRAME_NUM > 3
		DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP0_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp0_en,"PreData_Dn2_0", &PreData_Dn2[0].s16Time_Data[0], sizeof(PreData_Dn2[0].s16Time_Data), SYS_RAW_CHIRP_DN2FMT, NULL),
		DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP1_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp1_en,"PreData_Dn2_1", &PreData_Dn2[1].s16Time_Data[0], sizeof(PreData_Dn2[1].s16Time_Data), SYS_RAW_CHIRP_DN2FMT, NULL),
		DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP2_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp2_en,"PreData_Dn2_2", &PreData_Dn2[2].s16Time_Data[0], sizeof(PreData_Dn2[2].s16Time_Data), SYS_RAW_CHIRP_DN2FMT, NULL),
		DAQINFO_RAW(SYS_RAW_CHIRP_EN & SYS_RAW_CHIRP3_EN,  &SYS_PARAM_SENSORTYPE.raw_chirp3_en,"PreData_Dn2_3", &PreData_Dn2[3].s16Time_Data[0], sizeof(PreData_Dn2[3].s16Time_Data), SYS_RAW_CHIRP_DN2FMT, NULL),
#endif

		//DAQINFO_RAW(1, &SYS_PARAM_SENSORTYPE.raw_chirp_en, "gSpCurPRF", &gSpCurPRF , 1, "1B", NULL),

		// Packet ID for application specific raw data
		// ref enable 수정되어야 함.

		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "nci_ref_mode", gRM_BeamData.f32PowSpectrum_array, 524288, "131072f", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "nci_lr_mode", gLR_BeamData.f32PowSpectrum_array, 65536, "16384f", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "nci_mr_mode", gMR_BeamData.f32PowSpectrum_array, 65536, "16384f", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "nci_sr_mode", gSR_BeamData.f32PowSpectrum_array, 65536, "16384f", NULL),

		/* R : 512 */
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "rm_fft_peak_data_s16PeakCnt", &gRM_PeakData.s16PeakCnt, 2, "1h", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "rm_fft_peak_data_rdu16FreqIdx", gRM_PeakData.rdu16FreqIdx, 2048, "1024h", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "rm_fft_peak_data_rdf32EstFreqIdx", gRM_PeakData.rdf32EstFreqIdx, 4096, "1024f", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "rm_fft_peak_data_cf32FFTData", gRM_PeakData.cf32FFTData, 65536, "16384f", NULL),

		/* L, M, S : 256 */

		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "lr_fft_peak_data_s16PeakCnt", &gLR_PeakData.s16PeakCnt, 2, "1h", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "lr_fft_peak_data_rdu16FreqIdx", gLR_PeakData.rdu16FreqIdx, 1024, "512h", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "lr_fft_peak_data_rdf32EstFreqIdx", gLR_PeakData.rdf32EstFreqIdx, 2048, "512f", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "lr_fft_peak_data_cf32FFTData", gLR_PeakData.cf32FFTData, 393216, "98304f", NULL),

		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "mr_fft_peak_data_s16PeakCnt", &gMR_PeakData.s16PeakCnt, 2, "1h", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "mr_fft_peak_data_rdu16FreqIdx", gMR_PeakData.rdu16FreqIdx, 1024, "512h", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "mr_fft_peak_data_rdf32EstFreqIdx", gMR_PeakData.rdf32EstFreqIdx, 2048, "512f", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "mr_fft_peak_data_cf32FFTData", gMR_PeakData.cf32FFTData, 393216, "98304f", NULL),

		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "sr_fft_peak_data_s16PeakCnt", &gSR_PeakData.s16PeakCnt, 2, "1h", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "sr_fft_peak_data_rdu16FreqIdx", gSR_PeakData.rdu16FreqIdx, 1024, "512h", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "sr_fft_peak_data_rdf32EstFreqIdx", gSR_PeakData.rdf32EstFreqIdx, 2048, "512f", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "sr_fft_peak_data_cf32FFTData", gSR_PeakData.cf32FFTData, 393216, "98304f", NULL),


		/* L, M, S : 512 */
		/*
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "lr_fft_peak_data_s16PeakCnt", &gLR_PeakData.s16PeakCnt, 2, "1h", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "lr_fft_peak_data_rdu16FreqIdx", gLR_PeakData.rdu16FreqIdx, 2048, "1024h", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "lr_fft_peak_data_rdf32EstFreqIdx", gLR_PeakData.rdf32EstFreqIdx, 4096, "1024f", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "lr_fft_peak_data_cf32FFTData", gLR_PeakData.cf32FFTData, 786432f, "196608f", NULL),

		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "mr_fft_peak_data_s16PeakCnt", &gMR_PeakData.s16PeakCnt, 2, "1h", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "mr_fft_peak_data_rdu16FreqIdx", gMR_PeakData.rdu16FreqIdx, 2048, "1024h", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "mr_fft_peak_data_rdf32EstFreqIdx", gMR_PeakData.rdf32EstFreqIdx, 4096, "1024f", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "mr_fft_peak_data_cf32FFTData", gMR_PeakData.cf32FFTData, 786432f, "196608f", NULL),

		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "sr_fft_peak_data_s16PeakCnt", &gSR_PeakData.s16PeakCnt, 2, "1h", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "sr_fft_peak_data_rdu16FreqIdx", gSR_PeakData.rdu16FreqIdx, 2048, "1024h", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "sr_fft_peak_data_rdf32EstFreqIdx", gSR_PeakData.rdf32EstFreqIdx, 4096, "1024f", NULL),
		DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_FI_EN,  &SYS_PARAM_SENSORTYPE.pid_object_en, "sr_fft_peak_data_cf32FFTData", gSR_PeakData.cf32FFTData, 786432f, "196608f", NULL),
		*/

		// VF
		//DAQINFO_RAW_ITEM(SYS_RAW_APP_EN & SYS_RAW_APP_VF_EN,  &SYS_PARAM_SENSORTYPE.raw_app_vf_en,"Sp_TrackOut", Sp_TrackOut[0], "Sp_Track_Out[0],.Status,.UpdState,.MovState,.paddo ,.f32PosX,.f32PosY,.f32VelX,.f32VelY,.f32Pow_dB",  "B,B,B,B,f,f,f,f,f", NULL),
		//DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_VF_EN,  &SYS_PARAM_SENSORTYPE.raw_app_vf_en,"raw_app_vf_dat", bts_comm_appl_raw_vf.dat ,128, "128B", bts_comm_appl_raw_app_vf_precallback),
		//DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_VF_EN,  &SYS_PARAM_SENSORTYPE.raw_app_vf_en,"raw_app_vf_war", bts_comm_appl_raw_vf.war ,128, "128B", NULL),
		//DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_VF_EN,  &SYS_PARAM_SENSORTYPE.raw_app_vf_en,"raw_app_vf_det", bts_comm_appl_raw_vf.det ,128, "128B", NULL),
		//DAQINFO_RAW(SYS_RAW_APP_EN & SYS_RAW_APP_VF_EN,  &SYS_PARAM_SENSORTYPE.raw_app_vf_en,"raw_app_vf_sw", bts_comm_appl_raw_vf.sw ,128, "128B", NULL),
		// FCW
		//DAQINFO_RAW_ITEM(SYS_RAW_APP_EN & SYS_RAW_APP_FCW_EN, &SYS_PARAM_SENSORTYPE.raw_app_fcw_en,"fcwinfo", comm_appl_fcwinfo,"fcwinfo,.vehicle_speed,.wheel_speed_fl,.wheel_speed_fr,.wheel_speed_rl,.wheel_speed_rr,.steerangle,.steeranglespeed,.yawrate,.longaccel,.lataccel,.eventflag","f,f,f,f,f,f,f,f,f,f,I", bts_comm_appl_raw_app_fcw_precallback),
		// LEVEL METER
		//DAQINFO_RAW_ITEM(SYS_RAW_APP_EN & SYS_RAW_APP_LM_EN, &SYS_PARAM_SENSORTYPE.raw_app_lm_en, "raw_app_lm", bts_comm_appl_raw_app_lm ,"f", bts_comm_appl_raw_app_lm_precallback),
		// INSTALL INFO
		//DAQINFO_RAW_ITEM(SYS_RAW_APP_EN & SYS_RAW_APP_INSTALL_EN, &SYS_PARAM_SENSORTYPE.raw_app_install_en, "raw_app_installinfo", raw_app_installinfo, "raw_app_installinfo,.angle_azi,.angle_ele,.height_m","f,f,f",bts_comm_appl_raw_app_its_install_precallback),
		// FLOG INFO(emmc logger)
		//DAQINFO_RAW_ITEM(SYS_RAW_APP_EN & SYS_RAW_APP_FLOG_EN, &SYS_PARAM_SENSORTYPE.raw_app_flog_en, "raw_app_flog", raw_app_flog, "raw_app_flog,.emmcfreerate,.filenumber,.eventflag,.flog_status","f,I,I,I",bts_comm_appl_raw_app_flog_precallback),

		// Packet ID for monitoring raw data
		//DAQINFO_RAW_ITEM(SYS_RAW_MON_EN & SYS_RAW_MON_IMU_EN, &SYS_PARAM_SENSORTYPE.raw_mon_en,"raw_imu", imu_data,"imu_data,.ax,.ay,.az,.gx,.gy,.gz,.mx,.my,.mz,.pitch,.yaw,.roll,.q0,.q1,.q2,.q3,.temperature_degc,.pressure_hpa,.altidude_m","f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f,f", NULL),
		//DAQINFO_RAW_ITEM(SYS_RAW_MON_EN & SYS_RAW_MON_SYSINFO_EN,  &SYS_PARAM_SENSORTYPE.raw_mon_en,"raw_sysinfo", bts_comm_sysinfo, "sysinfo,.scanindex,.imu_pitch,.imu_yaw,.imu_roll,.imu_hight,.imu_ax,.imu_ay,.imu_az,.timestamp_s,.cycletime_s",  "I,f,f,f,f,f,f,f,d,f", bts_comm_appl_raw_sysinfo_precallback),
		//DAQINFO_RAW_ITEM(SYS_RAW_MON_EN & SYS_RAW_MON_POWER_EN,  &SYS_PARAM_SENSORTYPE.raw_mon_power_en,"raw_power", xadc_drv_cpu_electrical_info, "raw_power,.dietemp,.vccint,.vccaux,.vccbram,.vccpint,.vccpaux,.vccpddr,.pwr24v,.pwr5v,.pwr3v3,.pwr0v75,.pwr2v8,.pwr1v8",  "f,f,f,f,f,f,f,f,f,f,f,f,f", NULL),
		//DAQINFO_RAW_ITEM(SYS_RAW_MON_EN & SYS_RAW_MON_TIME_EN,  &SYS_PARAM_SENSORTYPE.raw_mon_time_en,"raw_cpu_time", bts_comm_appl_performance,"cpu_time,.scanrate_fps,.mod_memcopy,.rsp,.rsp_import,.rsp_scaninit,.rsp_pre,.rsp_obj,.rsp_trk,.rsp_appmain,.rsp_export,.app",  "f,f,f,f,f,f,f,f,f,f,f", bts_comm_appl_raw_cpu_time_precallback),
		//DAQINFO_RAW_ITEM(SYS_RAW_MON_EN & SYS_RAW_MON_TASK_EN, &SYS_PARAM_SENSORTYPE.raw_mon_task_en,"raw_cpu_task", le_trace_buffer, "cpu_task",  "1024H", NULL),

		DAQINFO_END(),
};


/* declare static variables */


/* static function prototypes */

/* functions */

// object


/******************************************************************************
 * function name : bts_comm_appl_dataset_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return void description
 * modification date : 2018.06.26
 *****************************************************************************/
void bts_comm_appl_dataset_init(void)
{
	int32_t i;
	int32_t pid_raw;
	krs_memclearitem(appljson_pid0_status_data);

	krs_memclear(bts_comm_daqinfo_pid2index_lut);
	krs_memclear(bts_comm_daqinfo_index2pid_lut);

	/* make lookup table for get index of bts_comm_daqinfo by pid*/
	pid_raw = bts_comm_pid_raw;
	for (i = 0; i < bts_comm_pid_max; i++)
	{
		if (bts_comm_daqinfo[i].pid < bts_comm_pid_max && bts_comm_daqinfo[i].enable != 0)
		{
			if (bts_comm_daqinfo[i].pid < bts_comm_pid_raw)
			{
				bts_comm_daqinfo_index2pid_lut[i] = bts_comm_daqinfo[i].pid;
				bts_comm_daqinfo_pid2index_lut[bts_comm_daqinfo[i].pid] = i;
			}
			else
			{
				bts_comm_daqinfo_index2pid_lut[i] = pid_raw;
				bts_comm_daqinfo_pid2index_lut[pid_raw] = i;
				pid_raw++;
			}

		}
	}
}




/******************************************************************************
 * function name : bts_comm_daqinfo_is_start
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 pid description
 * \return int32_t description
 * modification date : 2019.09.09
 *****************************************************************************/
int32_t bts_comm_daqinfo_is_start(bts_comm_pid_appl_t pid)
{
	int32_t daqinfoindex;

	daqinfoindex = bts_comm_daqinfo_pid2index_lut[pid];

	if (bts_comm_daqinfo[daqinfoindex].start != 0)
	{
		return retOK;
	}
	return retFail;
}




/******************************************************************************
 * function name : bts_comm_appl_dataset_set_daqstartstop
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *activatelist description
 * \param1 len description
 * \return int32_t description
 * modification date : 2019.09.09
 *****************************************************************************/
int32_t bts_comm_appl_dataset_set_daqstartstop(uint8_t *activatelist, int32_t len)
{
	int32_t i;
	int32_t startstopindex = 0;

	bts_comm_appl_dataset_init();


	startstopindex = 0;
	for (i = 0; i < bts_comm_pid_max; i++)
	{
		if (bts_comm_daqinfo[i].pidtype >= bts_comm_pidtype_end) break;
		if (bts_comm_appl_common_check_activated(&bts_comm_daqinfo[i]) == retOK)
		{
			bts_comm_daqinfo[i].start = activatelist[startstopindex++];
		}
	}
	if (startstopindex != len)
	{
		krs_log("bts_comm_appl_dataset_set_daqstartstop: mismatch daqstartstop(%ld) and daq enableded count(%ld)\n\r", startstopindex, len);
		return retOK;
	}
	return retOK;
}

/* end of file */
