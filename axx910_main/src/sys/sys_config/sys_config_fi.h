/************************************************************************
| Project Name: AFI910
|    File Name: sys_config_fi.h
|  Description: detailed Description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company                        
| --------     ---------------------     -------------------------------
| MHKIM        Myoungha Kim              bitsensing Corporation
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description                                 
| ----------  ----  ------  --------------------------------------------
| 2021.04.08  0.0   mhkim   Creation;
|***********************************************************************/

#ifndef SYS_CONFIG_FI_H__
#define SYS_CONFIG_FI_H__

#define SYS_PARAMETER_VERSION 20210408
#define SYS_HW_BE_VERSION "AFI910F-01-BE-DRAFT"
#define SYS_HW_BE_DATE "2021.02"
#define SYS_HW_FE_VERSION "AFI910F-02-FE"
#define SYS_HW_FE_DATE "2021.02"
#define SYS_SENSOR_TYPE "ADI"
#define SYS_PROTOCOL_VERSION "1.0"
#define SYS_PROTOCOL_DATE "2021.04"
#define SYS_CUSTOMER_VERSION "0.0"
#define SYS_CUSTOMER_DATE "0000.00.00"
#define SYS_CUSTOMER_SPEC "BITSENSING"


#define SYS_GPS_ENABLE 1
#define SYS_WIFI_ENABLE 0
#define SYS_BT_ENABLE 0
#define SYS_LORA_ENABLE 0
#define SYS_IMU_ENABLE 0
#define SYS_ALTITUDE_ENABLE 1
#define SYS_RS485_ENABLE 0
#define SYS_CAN_ENABLE 0
#define SYS_SSR_ENABLE 1
#define SYS_eMMC_ENABLE 0
#define SYS_JCTBOX_ENABLE 0
#define SYS_CAM_ENABLE 1

#define SYS_APP_NAME "AFI"
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
#define SYS_PID_APP_FCW_EN 1
#define SYS_PID_APP_LM_EN 0
#define SYS_PID_AI_OBJECT_EN 1
#define SYS_PID_LANE_DETCION_EN 1
#define SYS_PID_FREESPACE_EN 1
#define SYS_RAW_CHIRP_EN 0
#define SYS_RAW_CHIRP0_EN 0
#define SYS_RAW_CHIRP1_EN 0
#define SYS_RAW_CHIRP2_EN 0
#define SYS_RAW_CHIRP3_EN 0
#define SYS_RAW_APP_EN 1
#define SYS_RAW_APP_ITS_EN 0
#define SYS_RAW_APP_VF_EN 0
#define SYS_RAW_APP_FCW_EN 0
#define SYS_RAW_APP_LM_EN 0
#define SYS_RAW_APP_FI_EN 1
#define SYS_RAW_APP_INSTALL_EN 0
#define SYS_RAW_APP_FLOG_EN 0
#define SYS_RAW_MON_EN 0
#define SYS_RAW_MON_IMU_EN 0
#define SYS_RAW_MON_SYSINFO_EN 0
#define SYS_RAW_MON_POWER_EN 0
#define SYS_RAW_MON_TIME_EN 0
#define SYS_RAW_MON_TASK_EN 0

#define SYS_DAQ_CHANNEL_COUNT 4
#define SYS_DEFAULT_SCANRATE 10
//#define SYS_RSM_N_TIMEDATA_MAX 4096
//#define SYS_RSM_LONGFIRST 0
//#define SYS_RSM_CHIRP_BANDWIDTH 187.5f
//#define SYS_RSP_OBJECT_MAX 256
//#define SYS_RSP_TRACK_MAX 128
#define SYS_AI_OBJECT_MAX 1000
#endif // SYS_CONFIG_ITS_H__
