/************************************************************************
| Project Name: bts_log_cfg
|    File Name: bts_log_cfg.h
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
| 2018.08.09   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef BTS_LOG_CFG_H__
#define BTS_LOG_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* include system primitive types */
#include "bts.h"

#define BTS_LOG_STREAMBUFFER_SIZE (32*1024)

/* module specific types  */
#ifndef WIN32
#define BTS_LOG_CFG_FROM_SYS_PARAM 0
#define BTS_LOG_FREERTOS_SUPPORT_EN 0//SYS_CONSOLE_BUFFER_EN
#define BTS_LOG_MTD_SUPPORT_EN 0
#define BTS_LOG_LINEMSGLEN_MAX 256
#define BTS_LOG_TIME_t uint64_t
#define BTS_LOG_FILE_LEN_MAX 16
#define BTS_LOG_FUNCTION_LEN_MAX 20
#define BTS_LOG_MULTICORE_SUPPORT_EN 0
#define BTS_LOG_WDGSUPPORT 0
#define BTS_LOG_UDP_EN 0
#else
#define BTS_LOG_CFG_FROM_SYS_PARAM 0
#define BTS_LOG_FREERTOS_SUPPORT_EN 0
#define BTS_LOG_MTD_SUPPORT_EN 0
#define BTS_LOG_LINEMSGLEN_MAX 256
#define BTS_LOG_TIME_t uint64_t
#define BTS_LOG_FILE_LEN_MAX 16
#define BTS_LOG_FUNCTION_LEN_MAX 20
#define BTS_LOG_MULTICORE_SUPPORT_EN 0
#define BTS_LOG_WDGSUPPORT 0
#define BTS_LOG_UDP_EN 0
#endif


/* define structure for this module */
#if BTS_LOG_CFG_FROM_SYS_PARAM == 0
#define BTS_LOG_OPT_LOG_QEUDEPTH_EN 1
#define BTS_LOG_GLOBAL_LEVEL 5
#define BTS_LOG_OPT_LOGTYPE_EN 1
#define BTS_LOG_OPT_TIME_EN 1
#define BTS_LOG_OPT_DIFFTIME_EN 0
#define BTS_LOG_OPT_DATETIME_EN 1
#define BTS_LOG_OPT_DATETIME_MS_EN 1
#define BTS_LOG_OPT_DATETIME_US_EN 1
#define BTS_LOG_OPT_FILE_EN 1
#define BTS_LOG_OPT_LINE_EN 1
#define BTS_LOG_OPT_FUNCTION_EN 1
#define BTS_LOG_ARRAY_FRONTLEN 16
#define BTS_LOG_ARRAY_BACKLEN 8
#else
//#include "sys_param.h"
#define BTS_LOG_OPT_LOG_QEUDEPTH_EN 1
#define BTS_LOG_GLOBAL_LEVEL SYS_PARAM_CONSOLELOG.bts_log_level
#define BTS_LOG_OPT_LOGTYPE_EN SYS_PARAM_CONSOLELOG.bts_log_opt_type_en
#define BTS_LOG_OPT_TIME_EN SYS_PARAM_CONSOLELOG.bts_log_opt_time_en
#define BTS_LOG_OPT_DIFFTIME_EN SYS_PARAM_CONSOLELOG.bts_log_opt_difftime_en
#define BTS_LOG_OPT_DATETIME_EN SYS_PARAM_CONSOLELOG.bts_log_opt_datetime_en
#define BTS_LOG_OPT_DATETIME_MS_EN SYS_PARAM_CONSOLELOG.bts_log_opt_datetime_ms_en
#define BTS_LOG_OPT_DATETIME_US_EN SYS_PARAM_CONSOLELOG.bts_log_opt_datetime_us_en
#define BTS_LOG_OPT_FILE_EN SYS_PARAM_CONSOLELOG.bts_log_opt_file_en
#define BTS_LOG_OPT_LINE_EN SYS_PARAM_CONSOLELOG.bts_log_opt_line_en
#define BTS_LOG_OPT_FUNCTION_EN SYS_PARAM_CONSOLELOG.bts_log_opt_function_en
#define BTS_LOG_ARRAY_FRONTLEN SYS_PARAM_CONSOLELOG.bts_log_array_frontlen
#define BTS_LOG_ARRAY_BACKLEN SYS_PARAM_CONSOLELOG.bts_log_array_backlen
#endif



/* declare extern global variables */

/* declare extern global functions */



#ifdef __cplusplus
}
#endif

#endif // BTS_LOG_CFG_H__
