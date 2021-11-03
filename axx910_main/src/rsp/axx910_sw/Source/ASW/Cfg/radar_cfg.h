/***********************************************************************
 | Project Name: BTS-ESP32
 |    File Name: radar_cfg.h
 |  Description: detailed Description
 |-----------------------------------------------------------------------
 |               A U T H O R   I D E N T I T Y
 |-----------------------------------------------------------------------
 | Initials     Name                      Company
 | --------     ---------------------     -------------------------------
 |
 |-----------------------------------------------------------------------
 |              R E V I S I O N   H I S T O R Y
 |-----------------------------------------------------------------------
 | Date         Ver  Author  Description
 | ----------  ----  ------  --------------------------------------------
 | 2020.01.13   0.0          Creation;
 |***********************************************************************/

#ifndef RADAR_CFG_H__
#define RADAR_CFG_H__


 /* Radar */
#define RADAR_CFG_MIMO											1
#define RADAR_CFG_NUM_TX										12
#define RADAR_CFG_NUM_RX										16

#define RADAR_CFG_SAMPLING_FREQ							53.3e6f

/* Modulation Spec. */
#define RADAR_CFG_NUM_SHAPE								1

#define RADAR_CFG_RM_NUM_SAMPLES						512
#define RADAR_CFG_RM_NUM_CHIRPS							512

#define RADAR_CFG_NUM_SAMPLES								1024
#define RADAR_CFG_NUM_CHIRPS								32

#define RADAR_CFG_CENTER_FREQ								79.00e9f
#define RADAR_CFG_RM_BANDWIDTH							100.0e6f
#define RADAR_CFG_LR_BANDWIDTH							250.0e6f
#define RADAR_CFG_MR_BANDWIDTH							0.88e9f
#define RADAR_CFG_SR_BANDWIDTH							1.5e9f


#define RADAR_CFG_FRAME_RM_CHIRP_INTERVAL			16.42e-6f		//14.60e-6f		// Frame PING, Tx1
#define RADAR_CFG_FRAME_DE_CHIRP_INTERVAL			26.95e-6f		// Frame PING, Tx1

#define RADAR_CFG_CYCLE_TIME_US							100000		//200000: 4/28 demo version	//100000 //50000

#define RADAR_CFG_CH_NUM										8


#endif /* RADAR_CFG_H__*/
