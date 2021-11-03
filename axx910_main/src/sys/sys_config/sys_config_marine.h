/************************************************************************
| Project Name: sys_config_marine
|    File Name: sys_config_marine.h
|  Description: file detailed description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------
| SKJ          SONG KYEONG JIN           Bitsensing
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description
| ----------  ----  ------  --------------------------------------------
| 2019.11.28   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef SYS_CONFIG_MARINE_H__
#define SYS_CONFIG_MARINE_H__

#define SYS_PARAMETER_VERSION 20191209
#define SYS_HW_BE_VERSION "BTS24MX BE V11"
#define SYS_HW_BE_DATE "2019.02"
#define SYS_HW_FE_VERSION "BTS24MX-XX10U"
#define SYS_HW_FE_DATE "2019.02"
#define SYS_SENSOR_TYPE "BTS24MX"
#define SYS_PROTOCOL_VERSION "1.4"
#define SYS_PROTOCOL_DATE "2019.03"
#define SYS_CUSTOMER_VERSION "0.1"
#define SYS_CUSTOMER_DATE "2019.12.10"
#define SYS_CUSTOMER_SPEC "BTS"


#define SYS_GPS_ENABLE 1
#define SYS_WIFI_ENABLE 0
#define SYS_BT_ENABLE 0
#define SYS_LORA_ENABLE 0
#define SYS_IMU_ENABLE 1
#define SYS_ALTITUDE_ENABLE 1
#define SYS_RS485_ENABLE 0
#define SYS_CAN_ENABLE 0
#define SYS_SSR_ENABLE 0
#define SYS_eMMC_ENABLE 0
#define SYS_JCTBOX_ENABLE 0
#define SYS_CAM_ENABLE 1

#define SYS_APP_NAME "MARINE"
#define SYS_APP_RADAR_EN 1		// include or exclude radar related features
#define SYS_APP_RS485_EN 0
#define SYS_PID_STATUS_EN 1
#define SYS_PID_OBJECT_EN 1
#define SYS_PID_TRACK_EN 1
#define SYS_PID_IMAGE_EN 1
#define SYS_PID_IMAGSP_EN 0
#define SYS_PID_LOGGER_EN 0
#define SYS_PID_CANLOG_EN 0
#define SYS_PID_SENSOR_EN 0
#define SYS_PID_APP_ITS_EN 0
#define SYS_PID_APP_VF_EN 0
#define SYS_PID_APP_FCW_EN 0
#define SYS_PID_APP_LM_EN 0
#define SYS_PID_APP_MARINE_EN 1
#define SYS_RAW_CHIRP_EN 1
#define SYS_RAW_CHIRP0_EN 1
#define SYS_RAW_CHIRP1_EN 1
#define SYS_RAW_CHIRP2_EN 1
#define SYS_RAW_CHIRP3_EN 1
#define SYS_RAW_APP_EN 0
#define SYS_RAW_APP_ITS_EN 0
#define SYS_RAW_APP_VF_EN 0
#define SYS_RAW_APP_FCW_EN 0
#define SYS_RAW_APP_LM_EN 0
#define SYS_RAW_APP_INSTALL_EN 0
#define SYS_RAW_APP_FLOG_EN 0
#define SYS_RAW_MON_EN 1
#define SYS_RAW_MON_IMU_EN 1
#define SYS_RAW_MON_SYSINFO_EN 1
#define SYS_RAW_MON_POWER_EN 0
#define SYS_RAW_MON_TIME_EN 1
#define SYS_RAW_MON_TASK_EN 0

#define SYS_DAQ_CHANNEL_COUNT 4
#define SYS_DEFAULT_SCANRATE 15 // 10,15,20,25,30
#define SYS_RSM_N_TIMEDATA_MAX 8192
#define SYS_RSM_LONGFIRST 1  // 0: 4K 4K 8K 8K,  1: 8K,8K,4K,4K
#define SYS_RSM_CHIRP_BANDWIDTH 150.0f // 187.5f // 150.0f
#define SYS_RSP_OBJECT_MAX 256
#define SYS_RSP_TRACK_MAX 128

#endif // SYS_CONFIG_MARINE_H__
