#ifndef _SP_PARAMETERS_H_
#define _SP_PARAMETERS_H_


#include "radar_cfg.h"


/**************************************************************************************
-------------------------------------   define   --------------------------------------
**************************************************************************************/
#define SP_PI																		3.141592653589793f
#define SP_DEG2RAD						   										0.017453292519943f
#define SP_RAD2DEG					    										57.295779513082323f

#define SP_NUM_TX				    											RADAR_CFG_NUM_TX
#define SP_NUM_RX					    										RADAR_CFG_NUM_RX
#define SP_RM_NUM_TX															1


/*  Detection Modulation */
#define SP_NUM_SAMPLES														RADAR_CFG_NUM_SAMPLES
#define SP_NUM_CHIRPS														RADAR_CFG_NUM_CHIRPS

#define SP_NUM_FFT_R															SP_NUM_SAMPLES
#define SP_NUM_FFT_R_HALF													(SP_NUM_SAMPLES / 2)
#define SP_NUM_FFT_D															SP_NUM_CHIRPS


/* Reference Modulation */
#define SP_RM_NUM_SAMPLES		   										RADAR_CFG_RM_NUM_SAMPLES
#define SP_RM_NUM_CHIRPS													RADAR_CFG_RM_NUM_CHIRPS

#define SP_RM_NUM_FFT_R														SP_RM_NUM_SAMPLES
#define SP_RM_NUM_FFT_R_HALF												(SP_RM_NUM_FFT_R / 2)
#define SP_RM_NUM_FFT_D													SP_RM_NUM_CHIRPS



/* Modulation Spec. */
#define SP_LIGHT_SPEED														3.0e8f
#define SP_CENTER_FREQ														RADAR_CFG_CENTER_FREQ
#define SP_LAMDA																(SP_LIGHT_SPEED / SP_CENTER_FREQ)

#define SP_SAMPLING_FREQ													RADAR_CFG_SAMPLING_FREQ
#define SP_SAMPLING_TIME													(1.0f / SP_SAMPLING_FREQ)
#define SP_SWEEP_TIME															(SP_SAMPLING_TIME * SP_NUM_SAMPLES)
#define SP_RM_SWEEP_TIME													(SP_SAMPLING_TIME * SP_RM_NUM_SAMPLES)


/* LR */
#define SP_LR_BANDWIDTH													RADAR_CFG_LR_BANDWIDTH
#define SP_LR_CHIRP_INTERVAL												RADAR_CFG_FRAME_DE_CHIRP_INTERVAL

/* MR */
#define SP_MR_BANDWIDTH													RADAR_CFG_MR_BANDWIDTH
#define SP_MR_CHIRP_INTERVAL												RADAR_CFG_FRAME_DE_CHIRP_INTERVAL

/* SR */
#define SP_SR_BANDWIDTH													RADAR_CFG_SR_BANDWIDTH
#define SP_SR_CHIRP_INTERVAL												RADAR_CFG_FRAME_DE_CHIRP_INTERVAL

/* RM*/
#define SP_RM_BANDWIDTH													RADAR_CFG_RM_BANDWIDTH
#define SP_RM_CHIRP_INTERVAL												RADAR_CFG_FRAME_RM_CHIRP_INTERVAL


/* Ego Motion Compensation */
#define SP_EGO_NUM_FILTER_STEP											3
#define SP_EGO_GPS_SPD_FILTER_GAIN										0.85f
#define SP_EGO_GPS_SPD_COMP_FILTER_GAIN							0.95f
#define SP_EGO_YAWRATE_OFFSET											(0.0f)
#define SP_EGO_YAWRATE_FILTER_GAIN									0.5f
#define SP_EGO_YAWRATE_LOW_VEL_MAX									4.0f
#define SP_EGO_YAWRATE_LOW_VEL_FILTER_GAIN						0.6f
#define SP_EGO_RADIUS_BY_YAW_VEL_MIN								1.0f
#define SP_EGO_RADIUS_FILTER_GAIN										0.85f


/* Output parameters */
#define SP_NUM_OBJECT_MAX												(1024*4)
#define SP_NUM_CLST_MAX												    256
#define SP_NUM_TRACK_MAX													64

/* Sensor Cal Paremeters */
#define SP_CAL_SAMPLE_NUM													0xF001			/* F01 - A -  0xF014   F01 - B -  F001  Seoul Robotic - F002*/
#define SP_CAL_LR_INDEX														21
#define SP_CAL_MR_INDEX														153	
#define SP_CAL_SR_INDEX														306

/* temporary setting parameters */
#define SP_DEBUG_DATA_LOGGING_ON									1







#endif

