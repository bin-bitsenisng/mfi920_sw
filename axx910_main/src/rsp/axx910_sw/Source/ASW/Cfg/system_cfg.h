/************************************************************************
 | Project Name: Mod620(ROA)
 |    File Name: system_cfg.h
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
 | 2019.01.24   0.0          Creation;
 |***********************************************************************/

#ifndef SYSTEM_CFG_H__
#define SYSTEM_CFG_H__


#define SYS_BUILD_DATE __DATE__
#define SYS_BUILD_TIME __TIME__

#define SYS_BOARD_NAME      "MOD620"
#define SYS_BOARD_REV       01
#define SYS_BOARD_REV_STR   "30XXI"

#define SYS_HW_BE_NAME      "TC336DA"
#define SYS_HW_BE_REV       "10"
#define SYS_HW_RFM_NAME     "BGT60ATR24C"
#define SYS_HW_RFM_REV      "10"


#define SYS_BOARD_REV_10                0x10
#define SYS_BOARD_REV_20                0x20
#define SYS_BOARD_REV_30                0x30

#define SYS_APP_TYPE_CENTRAL		    0x00
#define SYS_APP_TYPE_BASIC_RANGE_METER  0x01
#define SYS_APP_TYPE_VF				    0x02
#define SYS_APP_TYPE_METER			    0x03
#define SYS_APP_TYPE_DAQ			    0x04
#define SYS_APP_TYPE_HUMAN_SENSING      0x05
#define SYS_APP_TYPE_WATER_LEVEL_GUAGE  0x06
#define SYS_APP_TYPE_WATER_SPEED_GUAGE  0x07
#define SYS_APP_TYPE_ETRI_LOGGER        0x08
#define SYS_APP_TYPE_PARKING_LOT_GUARD  0x09
#define SYS_APP_TYPE_GESTURE            0x0A
#define SYS_APP_TYPE_NONE		        0x99

#define SYS_OS_TYPE_AUTOSAROS           0x00
#define SYS_OS_TYPE_ERIKAOS             0x01
#define SYS_OS_TYPE_FREERTOS            0x02
#define SYS_OS_TYPE_NONOS               0x03

#define noSYS_CAN_LOGGING
#define SYS_CAN_PRODUCT
#define SYS_LATENCY_PROFILING

#define SYS_NONOS_GPT_TASK

#define SYS_APP_TYPE        SYS_APP_TYPE_HUMAN_SENSING
#define SYS_OS_TYPE         SYS_OS_TYPE_NONOS
#define SYS_CAN_TYPE        SYS_CAN_PRODUCT


#if SYS_DAQ_ONLY == 0

#if SYS_APP_TYPE == SYS_APP_TYPE_HUMAN_SENSING
#define SYS_PID_STATUS_EN 1
#define SYS_PID_OBJECT_EN 0
#define SYS_PID_TRACK_EN 1
#define SYS_RAW_CHIRP_EN 0
#define SYS_RAW_APP_EN 1
#else
#define SYS_PID_STATUS_EN 1
#define SYS_PID_OBJECT_EN 1
#define SYS_PID_TRACK_EN 1
#define SYS_RAW_CHIRP_EN 1
#define SYS_RAW_APP_EN 1
#endif

#else
#define SYS_PID_STATUS_EN 1
#define SYS_PID_OBJECT_EN 0
#define SYS_PID_TRACK_EN 0
#define SYS_RAW_CHIRP_EN 1
#define SYS_RAW_APP_EN 0
#endif


#endif /* SYSTEM_CFG_H__ */
