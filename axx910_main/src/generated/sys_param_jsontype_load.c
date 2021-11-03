#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS /* Disable deprecation warning in VS2005+ */
#pragma warning(disable : 4996) /* same with _CRT_SECURE_NO_WARNINGS*/
#endif
//*****************************************************************
//  Project Name:  IR24X
//     File Name:  sys_param_jsontype_load.c
//   Description:  auto generated file. do not modify!
// ----------------------------------------------------------------
//           C O D E    G E N E R A T O R    I N F O R M A T I O N
// ----------------------------------------------------------------
//     Generator: codegen.exe
//       Version: 0.0.1
//          Time: Mon Oct 12 15:37:40 2020
//    Datafile 0: ..\..\src\sys\sys_param\sys_param_jsontype.h
//            ID: 0DBA472B-E37E-4906-9CF0-3FE4D9AB4A0
//
// ----------------------------------------------------------------
//           U S E R    I N F O R M A T I O N
// ----------------------------------------------------------------
// Computer Name: SSONGDESKTOP
//     User Name: user
//     Directory: D:\Workdir\BTS24MX_LWIP2\ir24x_sw\ir24x_main\prebuild\json_info
//
// ----------------------------------------------------------------
//           P R O J E C T    S U M M A R Y
// ----------------------------------------------------------------
//*****************************************************************

#include "bts.h"
#include "krs_lib.h"
#include <string.h>

#include "sys_param.h"
#include "sys_param_jsontype.h"

#include "sys_param_jsontype_gen.h"
#include "sys_param_jsontype_load.h"


/*************************************************************/
/* load json string for internal                             */
/*************************************************************/


/******************************************************************************
 * function name : sys_param_comm_negative_response_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_comm_negative_response_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                       = 0;
    sys_param_comm_negative_response_t *objptr = (sys_param_comm_negative_response_t *)pvParam;
    //sys_param_log("sys_param_comm_negative_response_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_comm_negative_response_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,error:%256s}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => error:%256s */
                              objptr->error);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_common_comm_ethernet_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_common_comm_ethernet_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                            = 0;
    sys_param_common_comm_ethernet_config_t *objptr = (sys_param_common_comm_ethernet_config_t *)pvParam;
    //sys_param_log("sys_param_common_comm_ethernet_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_common_comm_ethernet_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{ip:%32s,nm:%32s,gw:%32s,mac:%32s,dns:%32s,linkspeed:%d,dhcp_en:%B}",
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => ip:%32s */
                              objptr->ip,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => nm:%32s */
                              objptr->nm,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => gw:%32s */
                              objptr->gw,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => mac:%32s */
                              objptr->mac,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => dns:%32s */
                              objptr->dns,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => linkspeed:%d */
                              &objptr->linkspeed,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => dhcp_en:%B */
                              &objptr->dhcp_en);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_common_comm_serialcomm_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_common_comm_serialcomm_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                              = 0;
    sys_param_common_comm_serialcomm_config_t *objptr = (sys_param_common_comm_serialcomm_config_t *)pvParam;
    //sys_param_log("sys_param_common_comm_serialcomm_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_common_comm_serialcomm_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{type:%32s,baudrate:%d,flowcontrol:%32s,data:%d,stopbit:%d}",
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => type:%32s */
                              objptr->type,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => baudrate:%d */
                              &objptr->baudrate,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => flowcontrol:%32s */
                              objptr->flowcontrol,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => data:%d */
                              &objptr->data,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => stopbit:%d */
                              &objptr->stopbit);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_common_comm_tbd_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_common_comm_tbd_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                       = 0;
    sys_param_common_comm_tbd_config_t *objptr = (sys_param_common_comm_tbd_config_t *)pvParam;
    //sys_param_log("sys_param_common_comm_tbd_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_common_comm_tbd_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{type:%32s}",
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => type:%32s */
                              objptr->type);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_swupdate_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_swupdate_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                = 0;
    sys_param_swupdate_config_t *objptr = (sys_param_swupdate_config_t *)pvParam;
    //sys_param_log("sys_param_swupdate_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_swupdate_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{swupdate_request:%d,swupdate_type:%d,swupdate_count:%d,swupdate_timestamp:%lf}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => swupdate_request:%d */
                              &objptr->swupdate_request,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => swupdate_type:%d */
                              &objptr->swupdate_type,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => swupdate_count:%d */
                              &objptr->swupdate_count,
                              /* type:double,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => swupdate_timestamp:%lf */
                              &objptr->swupdate_timestamp);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_consolelog_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_consolelog_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                  = 0;
    sys_param_consolelog_config_t *objptr = (sys_param_consolelog_config_t *)pvParam;
    //sys_param_log("sys_param_consolelog_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_consolelog_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{bts_log_level:%d,bts_log_opt_type_en:%B,bts_log_opt_time_en:%B,bts_log_opt_difftime_en:%B,bts_log_opt_file_en:%B,bts_log_opt_line_en:%B,bts_log_opt_function_en:%B,bts_log_module_comm_packet_en:%B,bts_log_module_comm_appl_callback_en:%B,bts_log_array_frontlen:%d,bts_log_array_backlen:%d,bts_log_cpu_usage:%B,bts_log_opt_datetime_en:%B,bts_log_opt_datetime_ms_en:%B,bts_log_opt_datetime_us_en:%B,bts_log_opt_gps_en:%B}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bts_log_level:%d */
                              &objptr->bts_log_level,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bts_log_opt_type_en:%B */
                              &objptr->bts_log_opt_type_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bts_log_opt_time_en:%B */
                              &objptr->bts_log_opt_time_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bts_log_opt_difftime_en:%B */
                              &objptr->bts_log_opt_difftime_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bts_log_opt_file_en:%B */
                              &objptr->bts_log_opt_file_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bts_log_opt_line_en:%B */
                              &objptr->bts_log_opt_line_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bts_log_opt_function_en:%B */
                              &objptr->bts_log_opt_function_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bts_log_module_comm_packet_en:%B */
                              &objptr->bts_log_module_comm_packet_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bts_log_module_comm_appl_callback_en:%B */
                              &objptr->bts_log_module_comm_appl_callback_en,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bts_log_array_frontlen:%d */
                              &objptr->bts_log_array_frontlen,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bts_log_array_backlen:%d */
                              &objptr->bts_log_array_backlen,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bts_log_cpu_usage:%B */
                              &objptr->bts_log_cpu_usage,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bts_log_opt_datetime_en:%B */
                              &objptr->bts_log_opt_datetime_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bts_log_opt_datetime_ms_en:%B */
                              &objptr->bts_log_opt_datetime_ms_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bts_log_opt_datetime_us_en:%B */
                              &objptr->bts_log_opt_datetime_us_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bts_log_opt_gps_en:%B */
                              &objptr->bts_log_opt_gps_en);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_consoleudp_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_consoleudp_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                  = 0;
    sys_param_consoleudp_config_t *objptr = (sys_param_consoleudp_config_t *)pvParam;
    //sys_param_log("sys_param_consoleudp_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_consoleudp_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{en:%B,ip:%32s,port:%d}",
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => en:%B */
                              &objptr->en,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => ip:%32s */
                              objptr->ip,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => port:%d */
                              &objptr->port);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_system_sensortype_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_system_sensortype_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                         = 0;
    sys_param_system_sensortype_config_t *objptr = (sys_param_system_sensortype_config_t *)pvParam;
    //sys_param_log("sys_param_system_sensortype_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_system_sensortype_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{type:%32s,serialnumber:%32s,opmode_its_en:%B,opmode_vf_en:%B,opmode_fcw_en:%B,opmode_lm_en:%B,pid_status_en:%B,pid_object_en:%B,pid_track_en:%B,pid_image_en:%B,pid_imagsp_en:%B,pid_logger_en:%B,pid_canlog_en:%B,pid_sensor_en:%B,pid_app_its_en:%B,pid_app_vf_en:%B,pid_app_fcw_en:%B,pid_app_lm_en:%B,raw_chirp_en:%B,raw_chirp0_en:%B,raw_chirp1_en:%B,raw_chirp2_en:%B,raw_chirp3_en:%B,raw_app_en:%B,raw_app_its_en:%B,raw_app_vf_en:%B,raw_app_fcw_en:%B,raw_app_lm_en:%B,raw_app_install_en:%B,raw_app_flog_en:%B,raw_mon_en:%B,raw_mon_power_en:%B,raw_mon_time_en:%B,raw_mon_task_en:%B}",
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => type:%32s */
                              objptr->type,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => serialnumber:%32s */
                              objptr->serialnumber,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => opmode_its_en:%B */
                              &objptr->opmode_its_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => opmode_vf_en:%B */
                              &objptr->opmode_vf_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => opmode_fcw_en:%B */
                              &objptr->opmode_fcw_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => opmode_lm_en:%B */
                              &objptr->opmode_lm_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_status_en:%B */
                              &objptr->pid_status_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_object_en:%B */
                              &objptr->pid_object_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_track_en:%B */
                              &objptr->pid_track_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_image_en:%B */
                              &objptr->pid_image_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_imagsp_en:%B */
                              &objptr->pid_imagsp_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_logger_en:%B */
                              &objptr->pid_logger_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_canlog_en:%B */
                              &objptr->pid_canlog_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_sensor_en:%B */
                              &objptr->pid_sensor_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_app_its_en:%B */
                              &objptr->pid_app_its_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_app_vf_en:%B */
                              &objptr->pid_app_vf_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_app_fcw_en:%B */
                              &objptr->pid_app_fcw_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_app_lm_en:%B */
                              &objptr->pid_app_lm_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => raw_chirp_en:%B */
                              &objptr->raw_chirp_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => raw_chirp0_en:%B */
                              &objptr->raw_chirp0_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => raw_chirp1_en:%B */
                              &objptr->raw_chirp1_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => raw_chirp2_en:%B */
                              &objptr->raw_chirp2_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => raw_chirp3_en:%B */
                              &objptr->raw_chirp3_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => raw_app_en:%B */
                              &objptr->raw_app_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => raw_app_its_en:%B */
                              &objptr->raw_app_its_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => raw_app_vf_en:%B */
                              &objptr->raw_app_vf_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => raw_app_fcw_en:%B */
                              &objptr->raw_app_fcw_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => raw_app_lm_en:%B */
                              &objptr->raw_app_lm_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => raw_app_install_en:%B */
                              &objptr->raw_app_install_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => raw_app_flog_en:%B */
                              &objptr->raw_app_flog_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => raw_mon_en:%B */
                              &objptr->raw_mon_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => raw_mon_power_en:%B */
                              &objptr->raw_mon_power_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => raw_mon_time_en:%B */
                              &objptr->raw_mon_time_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => raw_mon_task_en:%B */
                              &objptr->raw_mon_task_en);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_system_control_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_system_control_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount               = 0;
    sys_param_system_control_t *objptr = (sys_param_system_control_t *)pvParam;
    //sys_param_log("sys_param_system_control_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_system_control_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{restart_en:%B,restart_timeout_s:%d}",
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => restart_en:%B */
                              &objptr->restart_en,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => restart_timeout_s:%d */
                              &objptr->restart_timeout_s);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_logic_control_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_logic_control_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                     = 0;
    sys_param_logic_control_config_t *objptr = (sys_param_logic_control_config_t *)pvParam;
    //sys_param_log("sys_param_logic_control_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_logic_control_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{logic_start_scan_offset:%d}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => logic_start_scan_offset:%d */
                              &objptr->logic_start_scan_offset);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_system_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_system_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount              = 0;
    sys_param_system_config_t *objptr = (sys_param_system_config_t *)pvParam;
    //sys_param_log("sys_param_system_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_system_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{swupdate:%M,consolelog:%M,consoleudp:%M,sensortype:%M,eth_default:%M,syscontrol:%M,logiccontrol:%M}",
                              /* type:sys_param_swupdate_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => swupdate:%M */
                              sys_param_swupdate_config_t_loads, (void *)&(objptr->swupdate),
                              /* type:sys_param_consolelog_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => consolelog:%M */
                              sys_param_consolelog_config_t_loads, (void *)&(objptr->consolelog),
                              /* type:sys_param_consoleudp_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => consoleudp:%M */
                              sys_param_consoleudp_config_t_loads, (void *)&(objptr->consoleudp),
                              /* type:sys_param_system_sensortype_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sensortype:%M */
                              sys_param_system_sensortype_config_t_loads, (void *)&(objptr->sensortype),
                              /* type:sys_param_common_comm_ethernet_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => eth_default:%M */
                              sys_param_common_comm_ethernet_config_t_loads, (void *)&(objptr->eth_default),
                              /* type:sys_param_system_control_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => syscontrol:%M */
                              sys_param_system_control_t_loads, (void *)&(objptr->syscontrol),
                              /* type:sys_param_logic_control_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => logiccontrol:%M */
                              sys_param_logic_control_config_t_loads, (void *)&(objptr->logiccontrol));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did0_systembase_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did0_systembase_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                           = 0;
    sys_param_sid0did0_systembase_config_t *objptr = (sys_param_sid0did0_systembase_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did0_systembase_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did0_systembase_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_system_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_system_config_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_datetime_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_datetime_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount               = 0;
    sys_param_datetime_setup_t *objptr = (sys_param_datetime_setup_t *)pvParam;
    //sys_param_log("sys_param_datetime_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_datetime_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{type:%32s,unit:%8s,timestamp:%lf,gps_update_en:%B}",
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => type:%32s */
                              objptr->type,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => unit:%8s */
                              objptr->unit,
                              /* type:double,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => timestamp:%lf */
                              &objptr->timestamp,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => gps_update_en:%B */
                              &objptr->gps_update_en);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did1_datetime_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did1_datetime_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                         = 0;
    sys_param_sid0did1_datetime_config_t *objptr = (sys_param_sid0did1_datetime_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did1_datetime_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did1_datetime_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_datetime_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_datetime_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_security_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_security_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount               = 0;
    sys_param_security_setup_t *objptr = (sys_param_security_setup_t *)pvParam;
    //sys_param_log("sys_param_security_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_security_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{lock_en:%B,admin_password:%32s,user_password:%32s,type:%32s,latitude:%32s,longitude:%32s,direction:%32s}",
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => lock_en:%B */
                              &objptr->lock_en,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => admin_password:%32s */
                              objptr->admin_password,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => user_password:%32s */
                              objptr->user_password,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => type:%32s */
                              objptr->type,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => latitude:%32s */
                              objptr->latitude,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => longitude:%32s */
                              objptr->longitude,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => direction:%32s */
                              objptr->direction);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did2_security_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did2_security_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                         = 0;
    sys_param_sid0did2_security_config_t *objptr = (sys_param_sid0did2_security_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did2_security_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did2_security_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_security_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_security_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did3_network_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did3_network_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                        = 0;
    sys_param_sid0did3_network_config_t *objptr = (sys_param_sid0did3_network_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did3_network_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did3_network_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_common_comm_ethernet_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_common_comm_ethernet_config_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_version_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_version_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount        = 0;
    sys_param_version_t *objptr = (sys_param_version_t *)pvParam;
    //sys_param_log("sys_param_version_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_version_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{ver:%32s,date:%32s,spec:%32s}",
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => ver:%32s */
                              objptr->ver,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => date:%32s */
                              objptr->date,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => spec:%32s */
                              objptr->spec);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_version_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_version_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount              = 0;
    sys_param_version_setup_t *objptr = (sys_param_version_setup_t *)pvParam;
    //sys_param_log("sys_param_version_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_version_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sys:%M,sw:%M,be:%M,fe:%M,housing:%M,cable:%M,protocol:%M,customer:%M}",
                              /* type:sys_param_version_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sys:%M */
                              sys_param_version_t_loads, (void *)&(objptr->sys),
                              /* type:sys_param_version_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sw:%M */
                              sys_param_version_t_loads, (void *)&(objptr->sw),
                              /* type:sys_param_version_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => be:%M */
                              sys_param_version_t_loads, (void *)&(objptr->be),
                              /* type:sys_param_version_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => fe:%M */
                              sys_param_version_t_loads, (void *)&(objptr->fe),
                              /* type:sys_param_version_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => housing:%M */
                              sys_param_version_t_loads, (void *)&(objptr->housing),
                              /* type:sys_param_version_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => cable:%M */
                              sys_param_version_t_loads, (void *)&(objptr->cable),
                              /* type:sys_param_version_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => protocol:%M */
                              sys_param_version_t_loads, (void *)&(objptr->protocol),
                              /* type:sys_param_version_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => customer:%M */
                              sys_param_version_t_loads, (void *)&(objptr->customer));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_infra_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_infra_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount            = 0;
    sys_param_infra_setup_t *objptr = (sys_param_infra_setup_t *)pvParam;
    //sys_param_log("sys_param_infra_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_infra_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{infraid:%32s,radarid:%32s,locationid:%32s,basestationid:%32s,switchid:%32s,desc:%32s,desc1:%32s,desc2:%32s,longitude:%32s,latitude:%32s,direction:%32s,height:%32s,roadid:%32s,roadid1:%32s,roadid2:%32s,area:%32s,area1:%32s,range:%32s,range1:%32s,lane:%32s,lane1:%32s,lane2:%32s,lane3:%32s,lane4:%32s}",
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => infraid:%32s */
                              objptr->infraid,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => radarid:%32s */
                              objptr->radarid,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => locationid:%32s */
                              objptr->locationid,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => basestationid:%32s */
                              objptr->basestationid,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => switchid:%32s */
                              objptr->switchid,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => desc:%32s */
                              objptr->desc,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => desc1:%32s */
                              objptr->desc1,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => desc2:%32s */
                              objptr->desc2,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => longitude:%32s */
                              objptr->longitude,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => latitude:%32s */
                              objptr->latitude,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => direction:%32s */
                              objptr->direction,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => height:%32s */
                              objptr->height,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => roadid:%32s */
                              objptr->roadid,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => roadid1:%32s */
                              objptr->roadid1,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => roadid2:%32s */
                              objptr->roadid2,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => area:%32s */
                              objptr->area,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => area1:%32s */
                              objptr->area1,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => range:%32s */
                              objptr->range,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => range1:%32s */
                              objptr->range1,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => lane:%32s */
                              objptr->lane,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => lane1:%32s */
                              objptr->lane1,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => lane2:%32s */
                              objptr->lane2,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => lane3:%32s */
                              objptr->lane3,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => lane4:%32s */
                              objptr->lane4);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did4_infra_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did4_infra_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                      = 0;
    sys_param_sid0did4_infra_config_t *objptr = (sys_param_sid0did4_infra_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did4_infra_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did4_infra_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_infra_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_infra_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_serialnumber_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_serialnumber_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                   = 0;
    sys_param_serialnumber_setup_t *objptr = (sys_param_serialnumber_setup_t *)pvParam;
    //sys_param_log("sys_param_serialnumber_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_serialnumber_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sys:%32s,be:%32s,fe:%32s}",
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => sys:%32s */
                              objptr->sys,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => be:%32s */
                              objptr->be,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => fe:%32s */
                              objptr->fe);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did5_serialnumber_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did5_serialnumber_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                             = 0;
    sys_param_sid0did5_serialnumber_config_t *objptr = (sys_param_sid0did5_serialnumber_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did5_serialnumber_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did5_serialnumber_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_serialnumber_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_serialnumber_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_location_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_location_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount         = 0;
    sys_param_location_t *objptr = (sys_param_location_t *)pvParam;
    //sys_param_log("sys_param_location_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_location_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{type:%32s,latitude:%lf,longitude:%lf,direction:%f,gps_update_en:%B}",
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => type:%32s */
                              objptr->type,
                              /* type:double,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => latitude:%lf */
                              &objptr->latitude,
                              /* type:double,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => longitude:%lf */
                              &objptr->longitude,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => direction:%f */
                              &objptr->direction,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => gps_update_en:%B */
                              &objptr->gps_update_en);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_gps_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_gps_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount    = 0;
    sys_param_gps_t *objptr = (sys_param_gps_t *)pvParam;
    //sys_param_log("sys_param_gps_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_gps_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{en:%B,manufacture:%32s,default_baudrate:%d,baudrate:%d,rate:%d,dgps_en:%B,swfilter_en:%B}",
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => en:%B */
                              &objptr->en,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => manufacture:%32s */
                              objptr->manufacture,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => default_baudrate:%d */
                              &objptr->default_baudrate,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => baudrate:%d */
                              &objptr->baudrate,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => rate:%d */
                              &objptr->rate,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => dgps_en:%B */
                              &objptr->dgps_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => swfilter_en:%B */
                              &objptr->swfilter_en);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_location_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_location_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount               = 0;
    sys_param_location_setup_t *objptr = (sys_param_location_setup_t *)pvParam;
    //sys_param_log("sys_param_location_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_location_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{location:%M,gps:%M}",
                              /* type:sys_param_location_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => location:%M */
                              sys_param_location_t_loads, (void *)&(objptr->location),
                              /* type:sys_param_gps_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => gps:%M */
                              sys_param_gps_t_loads, (void *)&(objptr->gps));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did6_location_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did6_location_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                         = 0;
    sys_param_sid0did6_location_config_t *objptr = (sys_param_sid0did6_location_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did6_location_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did6_location_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_location_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_location_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_jctbox_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_jctbox_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount             = 0;
    sys_param_jctbox_setup_t *objptr = (sys_param_jctbox_setup_t *)pvParam;
    //sys_param_log("sys_param_jctbox_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_jctbox_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{commtype:%d,highspeed_en:%d,baudrate_default:%d,baudrate_high:%d,packettype:%d,tbd0:%d,tbd1:%d,tbd2:%d,tbd3:%d}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => commtype:%d */
                              &objptr->commtype,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => highspeed_en:%d */
                              &objptr->highspeed_en,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => baudrate_default:%d */
                              &objptr->baudrate_default,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => baudrate_high:%d */
                              &objptr->baudrate_high,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => packettype:%d */
                              &objptr->packettype,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd0:%d */
                              &objptr->tbd0,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd1:%d */
                              &objptr->tbd1,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd2:%d */
                              &objptr->tbd2,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd3:%d */
                              &objptr->tbd3);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did7_jctbox_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did7_jctbox_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                       = 0;
    sys_param_sid0did7_jctbox_config_t *objptr = (sys_param_sid0did7_jctbox_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did7_jctbox_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did7_jctbox_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_jctbox_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_jctbox_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_rs485_protocol_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rs485_protocol_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                     = 0;
    sys_param_rs485_protocol_setup_t *objptr = (sys_param_rs485_protocol_setup_t *)pvParam;
    //sys_param_log("sys_param_rs485_protocol_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_rs485_protocol_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{commtype:%d,highspeed_en:%d,baudrate_default:%d,baudrate_high:%d,packettype:%d,tbd0:%d,tbd1:%d,tbd2:%d,tbd3:%d}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => commtype:%d */
                              &objptr->commtype,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => highspeed_en:%d */
                              &objptr->highspeed_en,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => baudrate_default:%d */
                              &objptr->baudrate_default,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => baudrate_high:%d */
                              &objptr->baudrate_high,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => packettype:%d */
                              &objptr->packettype,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd0:%d */
                              &objptr->tbd0,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd1:%d */
                              &objptr->tbd1,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd2:%d */
                              &objptr->tbd2,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd3:%d */
                              &objptr->tbd3);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did8_rs485_protocol_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did8_rs485_protocol_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                               = 0;
    sys_param_sid0did8_rs485_protocol_config_t *objptr = (sys_param_sid0did8_rs485_protocol_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did8_rs485_protocol_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did8_rs485_protocol_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_rs485_protocol_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_rs485_protocol_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_cameractrl_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_cameractrl_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                 = 0;
    sys_param_cameractrl_setup_t *objptr = (sys_param_cameractrl_setup_t *)pvParam;
    //sys_param_log("sys_param_cameractrl_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_cameractrl_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{en:%d,framerate:%f,imageresolution:%d,imageroi:%d,format:%d,brightness:%d,contrast:%d,gain:%d,exposure_limit:%d,tbd1:%d,tbd2:%d,tbd3:%d,tbd4:%d,tbd5:%d,tbd6:%d,tbd7:%d,tbd8:%d}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => en:%d */
                              &objptr->en,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => framerate:%f */
                              &objptr->framerate,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => imageresolution:%d */
                              &objptr->imageresolution,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => imageroi:%d */
                              &objptr->imageroi,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => format:%d */
                              &objptr->format,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => brightness:%d */
                              &objptr->brightness,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => contrast:%d */
                              &objptr->contrast,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => gain:%d */
                              &objptr->gain,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => exposure_limit:%d */
                              &objptr->exposure_limit,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd1:%d */
                              &objptr->tbd1,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd2:%d */
                              &objptr->tbd2,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd3:%d */
                              &objptr->tbd3,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd4:%d */
                              &objptr->tbd4,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd5:%d */
                              &objptr->tbd5,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd6:%d */
                              &objptr->tbd6,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd7:%d */
                              &objptr->tbd7,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd8:%d */
                              &objptr->tbd8);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_camera_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'cam', 'type': 'sys_param_cameractrl_setup_t', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]'} */
void sys_param_camera_setup_t_loads_cam_array(char *str, int len, void *pvParam_local);
void sys_param_camera_setup_t_loads_cam_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_camera_setup_t *objptr = (sys_param_camera_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_camera_setup_t_loads_cam_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        sys_param_cameractrl_setup_t_loads((char *)ti.ptr, ti.len, &objptr->cam[i]);
    }
}
int32_t sys_param_camera_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount             = 0;
    sys_param_camera_setup_t *objptr = (sys_param_camera_setup_t *)pvParam;
    //sys_param_log("sys_param_camera_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_camera_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{count:%d,cam:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => count:%d */
                              &objptr->count,
                              /* type:sys_param_cameractrl_setup_t,  ismultidimarray : False, isarray : True, isstring : False, - json object type,   - json object array => cam:%M */
                              sys_param_camera_setup_t_loads_cam_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did9_camera_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did9_camera_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                       = 0;
    sys_param_sid0did9_camera_config_t *objptr = (sys_param_sid0did9_camera_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did9_camera_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did9_camera_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_camera_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_camera_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_rsp_eol_phasecal_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rsp_eol_phasecal_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                 = 0;
    sys_param_rsp_eol_phasecal_t *objptr = (sys_param_rsp_eol_phasecal_t *)pvParam;
    //sys_param_log("sys_param_rsp_eol_phasecal_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_rsp_eol_phasecal_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{real:%f,imag:%f}",
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => real:%f */
                              &objptr->real,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => imag:%f */
                              &objptr->imag);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_rsp_eol_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'phasecal', 'type': 'sys_param_rsp_eol_phasecal_t', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]'} */
void sys_param_rsp_eol_setup_t_loads_phasecal_array(char *str, int len, void *pvParam_local);
void sys_param_rsp_eol_setup_t_loads_phasecal_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_rsp_eol_setup_t *objptr = (sys_param_rsp_eol_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_rsp_eol_setup_t_loads_phasecal_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        sys_param_rsp_eol_phasecal_t_loads((char *)ti.ptr, ti.len, &objptr->phasecal[i]);
    }
}
/* {'subfunc': True, 'm_name': 'noise_level_up', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_rsp_eol_setup_t_loads_noise_level_up_array(char *str, int len, void *pvParam_local);
void sys_param_rsp_eol_setup_t_loads_noise_level_up_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_rsp_eol_setup_t *objptr = (sys_param_rsp_eol_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_rsp_eol_setup_t_loads_noise_level_up_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->noise_level_up[i]);
    }
    objptr->noise_level_up[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'noise_level_dn', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_rsp_eol_setup_t_loads_noise_level_dn_array(char *str, int len, void *pvParam_local);
void sys_param_rsp_eol_setup_t_loads_noise_level_dn_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_rsp_eol_setup_t *objptr = (sys_param_rsp_eol_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_rsp_eol_setup_t_loads_noise_level_dn_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->noise_level_dn[i]);
    }
    objptr->noise_level_dn[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'azibeampattern_up', 'type': 'float', 'ismultidimarray': True, 'isarray': True, 'isstring': False, 'm_countlist': [361, 4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i', 'j'], 'localloopvaridx': '[i][j]', 'subfmt': '%f'} */
void sys_param_rsp_eol_setup_t_loads_azibeampattern_up_array(char *str, int len, void *pvParam_local);
void sys_param_rsp_eol_setup_t_loads_azibeampattern_up_array(char *str, int len, void *pvParam_local)
{
    int32_t i, j;
    struct json_token ti, tj;
    sys_param_rsp_eol_setup_t *objptr = (sys_param_rsp_eol_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_rsp_eol_setup_t_loads_azibeampattern_up_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);
        for(j = 0; json_scanf_array_elem(ti.ptr, ti.len, "", j, &tj) > 0; j++)
        {
            //sys_param_log("Index %ld, token [%.*s]\n", j, tj.len, tj.ptr);

            json_scanf((char *)tj.ptr, tj.len, "%f", &objptr->azibeampattern_up[i][j]);
        }
        objptr->azibeampattern_up[i][j] = SYS_PARAM_F32_ARR_END_VALUE;
    }
}
/* {'subfunc': True, 'm_name': 'azibeamphase_up', 'type': 'float', 'ismultidimarray': True, 'isarray': True, 'isstring': False, 'm_countlist': [361, 4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i', 'j'], 'localloopvaridx': '[i][j]', 'subfmt': '%f'} */
void sys_param_rsp_eol_setup_t_loads_azibeamphase_up_array(char *str, int len, void *pvParam_local);
void sys_param_rsp_eol_setup_t_loads_azibeamphase_up_array(char *str, int len, void *pvParam_local)
{
    int32_t i, j;
    struct json_token ti, tj;
    sys_param_rsp_eol_setup_t *objptr = (sys_param_rsp_eol_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_rsp_eol_setup_t_loads_azibeamphase_up_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);
        for(j = 0; json_scanf_array_elem(ti.ptr, ti.len, "", j, &tj) > 0; j++)
        {
            //sys_param_log("Index %ld, token [%.*s]\n", j, tj.len, tj.ptr);

            json_scanf((char *)tj.ptr, tj.len, "%f", &objptr->azibeamphase_up[i][j]);
        }
        objptr->azibeamphase_up[i][j] = SYS_PARAM_F32_ARR_END_VALUE;
    }
}
/* {'subfunc': True, 'm_name': 'azibeampattern_dn', 'type': 'float', 'ismultidimarray': True, 'isarray': True, 'isstring': False, 'm_countlist': [361, 4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i', 'j'], 'localloopvaridx': '[i][j]', 'subfmt': '%f'} */
void sys_param_rsp_eol_setup_t_loads_azibeampattern_dn_array(char *str, int len, void *pvParam_local);
void sys_param_rsp_eol_setup_t_loads_azibeampattern_dn_array(char *str, int len, void *pvParam_local)
{
    int32_t i, j;
    struct json_token ti, tj;
    sys_param_rsp_eol_setup_t *objptr = (sys_param_rsp_eol_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_rsp_eol_setup_t_loads_azibeampattern_dn_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);
        for(j = 0; json_scanf_array_elem(ti.ptr, ti.len, "", j, &tj) > 0; j++)
        {
            //sys_param_log("Index %ld, token [%.*s]\n", j, tj.len, tj.ptr);

            json_scanf((char *)tj.ptr, tj.len, "%f", &objptr->azibeampattern_dn[i][j]);
        }
        objptr->azibeampattern_dn[i][j] = SYS_PARAM_F32_ARR_END_VALUE;
    }
}
/* {'subfunc': True, 'm_name': 'azibeamphase_dn', 'type': 'float', 'ismultidimarray': True, 'isarray': True, 'isstring': False, 'm_countlist': [361, 4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i', 'j'], 'localloopvaridx': '[i][j]', 'subfmt': '%f'} */
void sys_param_rsp_eol_setup_t_loads_azibeamphase_dn_array(char *str, int len, void *pvParam_local);
void sys_param_rsp_eol_setup_t_loads_azibeamphase_dn_array(char *str, int len, void *pvParam_local)
{
    int32_t i, j;
    struct json_token ti, tj;
    sys_param_rsp_eol_setup_t *objptr = (sys_param_rsp_eol_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_rsp_eol_setup_t_loads_azibeamphase_dn_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);
        for(j = 0; json_scanf_array_elem(ti.ptr, ti.len, "", j, &tj) > 0; j++)
        {
            //sys_param_log("Index %ld, token [%.*s]\n", j, tj.len, tj.ptr);

            json_scanf((char *)tj.ptr, tj.len, "%f", &objptr->azibeamphase_dn[i][j]);
        }
        objptr->azibeamphase_dn[i][j] = SYS_PARAM_F32_ARR_END_VALUE;
    }
}
int32_t sys_param_rsp_eol_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount              = 0;
    sys_param_rsp_eol_setup_t *objptr = (sys_param_rsp_eol_setup_t *)pvParam;
    //sys_param_log("sys_param_rsp_eol_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_rsp_eol_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{en:%B,phasecal:%M,noise_level_up:%M,noise_level_dn:%M,aziangstep:%f,aziangmin:%f,aziangmax:%f,azibeampattern_up:%M,azibeamphase_up:%M,azibeampattern_dn:%M,azibeamphase_dn:%M}",
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => en:%B */
                              &objptr->en,
                              /* type:sys_param_rsp_eol_phasecal_t,  ismultidimarray : False, isarray : True, isstring : False, - json object type,   - json object array => phasecal:%M */
                              sys_param_rsp_eol_setup_t_loads_phasecal_array, (void *)objptr,
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => noise_level_up:%M */
                              sys_param_rsp_eol_setup_t_loads_noise_level_up_array, (void *)objptr,
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => noise_level_dn:%M */
                              sys_param_rsp_eol_setup_t_loads_noise_level_dn_array, (void *)objptr,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => aziangstep:%f */
                              &objptr->aziangstep,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => aziangmin:%f */
                              &objptr->aziangmin,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => aziangmax:%f */
                              &objptr->aziangmax,
                              /* type:float,  ismultidimarray : True, isarray : True, isstring : False, - json primitive type,   - json bool/char/int/float multidimensional array => azibeampattern_up:%M */
                              sys_param_rsp_eol_setup_t_loads_azibeampattern_up_array, (void *)objptr,
                              /* type:float,  ismultidimarray : True, isarray : True, isstring : False, - json primitive type,   - json bool/char/int/float multidimensional array => azibeamphase_up:%M */
                              sys_param_rsp_eol_setup_t_loads_azibeamphase_up_array, (void *)objptr,
                              /* type:float,  ismultidimarray : True, isarray : True, isstring : False, - json primitive type,   - json bool/char/int/float multidimensional array => azibeampattern_dn:%M */
                              sys_param_rsp_eol_setup_t_loads_azibeampattern_dn_array, (void *)objptr,
                              /* type:float,  ismultidimarray : True, isarray : True, isstring : False, - json primitive type,   - json bool/char/int/float multidimensional array => azibeamphase_dn:%M */
                              sys_param_rsp_eol_setup_t_loads_azibeamphase_dn_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did10_rsp_eol_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did10_rsp_eol_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                         = 0;
    sys_param_sid0did10_rsp_eol_config_t *objptr = (sys_param_sid0did10_rsp_eol_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did10_rsp_eol_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did10_rsp_eol_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_rsp_eol_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_rsp_eol_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_rsp_install_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rsp_install_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                  = 0;
    sys_param_rsp_install_setup_t *objptr = (sys_param_rsp_install_setup_t *)pvParam;
    //sys_param_log("sys_param_rsp_install_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_rsp_install_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{height:%f,ele_angle:%f,azi_angle:%f,offset_x:%f,offset_y:%f}",
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => height:%f */
                              &objptr->height,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => ele_angle:%f */
                              &objptr->ele_angle,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => azi_angle:%f */
                              &objptr->azi_angle,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => offset_x:%f */
                              &objptr->offset_x,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => offset_y:%f */
                              &objptr->offset_y);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did11_rsp_install_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did11_rsp_install_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                             = 0;
    sys_param_sid0did11_rsp_install_config_t *objptr = (sys_param_sid0did11_rsp_install_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did11_rsp_install_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did11_rsp_install_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_rsp_install_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_rsp_install_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_rsm_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rsm_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount          = 0;
    sys_param_rsm_setup_t *objptr = (sys_param_rsm_setup_t *)pvParam;
    //sys_param_log("sys_param_rsm_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_rsm_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{mode:%d,userfreq:%f,scanrate:%d,daq_sampledelay:%d}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => mode:%d */
                              &objptr->mode,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => userfreq:%f */
                              &objptr->userfreq,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => scanrate:%d */
                              &objptr->scanrate,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => daq_sampledelay:%d */
                              &objptr->daq_sampledelay);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did12_rsm_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did12_rsm_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                     = 0;
    sys_param_sid0did12_rsm_config_t *objptr = (sys_param_sid0did12_rsm_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did12_rsm_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did12_rsm_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_rsm_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_rsm_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_rsptrk_posttune_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rsptrk_posttune_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                = 0;
    sys_param_rsptrk_posttune_t *objptr = (sys_param_rsptrk_posttune_t *)pvParam;
    //sys_param_log("sys_param_rsptrk_posttune_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_rsptrk_posttune_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{LongGate1:%f,LongGate2:%f,LongGate3:%f,LongGateByVel_Gain:%f,MotorCycle_PowTh:%f,MotorCycle_PowTh2:%f,MotorCycleByRange_Gain:%f,TrackOutFilter:%d,tbd8:%f,tbd9:%f,tbd10:%f,tbd11:%f,tbd12:%f,tbd13:%f,tbd14:%f,tbd15:%f}",
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => LongGate1:%f */
                              &objptr->LongGate1,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => LongGate2:%f */
                              &objptr->LongGate2,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => LongGate3:%f */
                              &objptr->LongGate3,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => LongGateByVel_Gain:%f */
                              &objptr->LongGateByVel_Gain,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => MotorCycle_PowTh:%f */
                              &objptr->MotorCycle_PowTh,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => MotorCycle_PowTh2:%f */
                              &objptr->MotorCycle_PowTh2,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => MotorCycleByRange_Gain:%f */
                              &objptr->MotorCycleByRange_Gain,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => TrackOutFilter:%d */
                              &objptr->TrackOutFilter,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd8:%f */
                              &objptr->tbd8,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd9:%f */
                              &objptr->tbd9,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd10:%f */
                              &objptr->tbd10,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd11:%f */
                              &objptr->tbd11,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd12:%f */
                              &objptr->tbd12,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd13:%f */
                              &objptr->tbd13,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd14:%f */
                              &objptr->tbd14,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => tbd15:%f */
                              &objptr->tbd15);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_rsptrk_trktune_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rsptrk_trktune_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount               = 0;
    sys_param_rsptrk_trktune_t *objptr = (sys_param_rsptrk_trktune_t *)pvParam;
    //sys_param_log("sys_param_rsptrk_trktune_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_rsptrk_trktune_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{s16Pt_New2Vrf:%d,s16Pt_Max:%d,s16Pt_New_Upd:%d,s16Pt_New_Coast:%d,s16Pt_Vrf_Upd:%d,s16Pt_Vrf_Coast:%d,f32Pt_NearRange:%f,s16Pt_Vrf_Upd_Near:%d,s16Pt_Vrf_Coast_Near:%d,f32R_GateByEle_W:%f,f32V_GateByEle_W:%f}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => s16Pt_New2Vrf:%d */
                              &objptr->s16Pt_New2Vrf,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => s16Pt_Max:%d */
                              &objptr->s16Pt_Max,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => s16Pt_New_Upd:%d */
                              &objptr->s16Pt_New_Upd,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => s16Pt_New_Coast:%d */
                              &objptr->s16Pt_New_Coast,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => s16Pt_Vrf_Upd:%d */
                              &objptr->s16Pt_Vrf_Upd,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => s16Pt_Vrf_Coast:%d */
                              &objptr->s16Pt_Vrf_Coast,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => f32Pt_NearRange:%f */
                              &objptr->f32Pt_NearRange,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => s16Pt_Vrf_Upd_Near:%d */
                              &objptr->s16Pt_Vrf_Upd_Near,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => s16Pt_Vrf_Coast_Near:%d */
                              &objptr->s16Pt_Vrf_Coast_Near,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => f32R_GateByEle_W:%f */
                              &objptr->f32R_GateByEle_W,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => f32V_GateByEle_W:%f */
                              &objptr->f32V_GateByEle_W);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_rsptrk_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rsptrk_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount             = 0;
    sys_param_rsptrk_setup_t *objptr = (sys_param_rsptrk_setup_t *)pvParam;
    //sys_param_log("sys_param_rsptrk_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_rsptrk_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{posttune:%M,trktune:%M}",
                              /* type:sys_param_rsptrk_posttune_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => posttune:%M */
                              sys_param_rsptrk_posttune_t_loads, (void *)&(objptr->posttune),
                              /* type:sys_param_rsptrk_trktune_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => trktune:%M */
                              sys_param_rsptrk_trktune_t_loads, (void *)&(objptr->trktune));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did13_rsptrk_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did13_rsptrk_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                        = 0;
    sys_param_sid0did13_rsptrk_config_t *objptr = (sys_param_sid0did13_rsptrk_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did13_rsptrk_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did13_rsptrk_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_rsptrk_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_rsptrk_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_rfictx_select_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rfictx_select_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount              = 0;
    sys_param_rfictx_select_t *objptr = (sys_param_rfictx_select_t *)pvParam;
    //sys_param_log("sys_param_rfictx_select_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_rfictx_select_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{rfictx_sel:%d}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => rfictx_sel:%d */
                              &objptr->rfictx_sel);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did30_rfictx_select_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did30_rfictx_select_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                               = 0;
    sys_param_sid0did30_rfictx_select_config_t *objptr = (sys_param_sid0did30_rfictx_select_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did30_rfictx_select_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did30_rfictx_select_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_rfictx_select_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_rfictx_select_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_rfictx_bgt24at2_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rfictx_bgt24at2_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                      = 0;
    sys_param_rfictx_bgt24at2_setup_t *objptr = (sys_param_rfictx_bgt24at2_setup_t *)pvParam;
    //sys_param_log("sys_param_rfictx_bgt24at2_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_rfictx_bgt24at2_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{TX1_A:%d,TX1_SPI_ON:%B,TX1_EN_DAC:%B,TX1_SEL1:%B,PH1_SPI_ON:%B,TX2_A:%d,TX2_SPI_ON:%B,TX2_SEL1:%B,TX2_EN_DAC:%B,PH2_SPI_ON:%B,LO_A:%d,LO_SPI_ON:%B,LO_EN_DAC:%B,LO_SEL1:%B,LO_SEL0:%B,PHLO_SPI_ON:%B,VCO_A:%d,EN_DAC_VCO:%B,EN_VCO:%B,EN_BUF2:%B,EN_BUF1:%B,PH_SEL1:%B,AMUX1_SEL1:%B,AMUX1_SEL0:%B,AMUX2_SEL2:%B,AMUX2_SEL1:%B,AMUX2_SEL0:%B,AMUX3_SEL1:%B,AMUX3_SEL0:%B,EN_DIV:%B,SEL_DIVBUF:%B,SEL_DIV:%B,DIS_DIVOUT:%B}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => TX1_A:%d */
                              &objptr->TX1_A,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => TX1_SPI_ON:%B */
                              &objptr->TX1_SPI_ON,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => TX1_EN_DAC:%B */
                              &objptr->TX1_EN_DAC,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => TX1_SEL1:%B */
                              &objptr->TX1_SEL1,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => PH1_SPI_ON:%B */
                              &objptr->PH1_SPI_ON,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => TX2_A:%d */
                              &objptr->TX2_A,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => TX2_SPI_ON:%B */
                              &objptr->TX2_SPI_ON,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => TX2_SEL1:%B */
                              &objptr->TX2_SEL1,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => TX2_EN_DAC:%B */
                              &objptr->TX2_EN_DAC,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => PH2_SPI_ON:%B */
                              &objptr->PH2_SPI_ON,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => LO_A:%d */
                              &objptr->LO_A,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => LO_SPI_ON:%B */
                              &objptr->LO_SPI_ON,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => LO_EN_DAC:%B */
                              &objptr->LO_EN_DAC,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => LO_SEL1:%B */
                              &objptr->LO_SEL1,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => LO_SEL0:%B */
                              &objptr->LO_SEL0,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => PHLO_SPI_ON:%B */
                              &objptr->PHLO_SPI_ON,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => VCO_A:%d */
                              &objptr->VCO_A,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => EN_DAC_VCO:%B */
                              &objptr->EN_DAC_VCO,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => EN_VCO:%B */
                              &objptr->EN_VCO,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => EN_BUF2:%B */
                              &objptr->EN_BUF2,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => EN_BUF1:%B */
                              &objptr->EN_BUF1,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => PH_SEL1:%B */
                              &objptr->PH_SEL1,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => AMUX1_SEL1:%B */
                              &objptr->AMUX1_SEL1,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => AMUX1_SEL0:%B */
                              &objptr->AMUX1_SEL0,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => AMUX2_SEL2:%B */
                              &objptr->AMUX2_SEL2,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => AMUX2_SEL1:%B */
                              &objptr->AMUX2_SEL1,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => AMUX2_SEL0:%B */
                              &objptr->AMUX2_SEL0,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => AMUX3_SEL1:%B */
                              &objptr->AMUX3_SEL1,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => AMUX3_SEL0:%B */
                              &objptr->AMUX3_SEL0,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => EN_DIV:%B */
                              &objptr->EN_DIV,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => SEL_DIVBUF:%B */
                              &objptr->SEL_DIVBUF,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => SEL_DIV:%B */
                              &objptr->SEL_DIV,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => DIS_DIVOUT:%B */
                              &objptr->DIS_DIVOUT);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did31_rfictx_bgt24at2_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did31_rfictx_bgt24at2_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                                 = 0;
    sys_param_sid0did31_rfictx_bgt24at2_config_t *objptr = (sys_param_sid0did31_rfictx_bgt24at2_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did31_rfictx_bgt24at2_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did31_rfictx_bgt24at2_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_rfictx_bgt24at2_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_rfictx_bgt24at2_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_rficrx_select_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rficrx_select_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount              = 0;
    sys_param_rficrx_select_t *objptr = (sys_param_rficrx_select_t *)pvParam;
    //sys_param_log("sys_param_rficrx_select_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_rficrx_select_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{rficrx_sel:%d}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => rficrx_sel:%d */
                              &objptr->rficrx_sel);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did40_rficrx_select_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did40_rficrx_select_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                               = 0;
    sys_param_sid0did40_rficrx_select_config_t *objptr = (sys_param_sid0did40_rficrx_select_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did40_rficrx_select_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did40_rficrx_select_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_rficrx_select_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_rficrx_select_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_rficrx_bgt24ar4_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rficrx_bgt24ar4_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                      = 0;
    sys_param_rficrx_bgt24ar4_setup_t *objptr = (sys_param_rficrx_bgt24ar4_setup_t *)pvParam;
    //sys_param_log("sys_param_rficrx_bgt24ar4_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_rficrx_bgt24ar4_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{EN_12:%B,LG1_12_6db:%B,HG1_12_12db:%B,LG2_12_6db:%B,MG2_12_12db:%B,HG2_12_18db:%B,EN_34:%B,LG1_34_6db:%B,HG1_34_12db:%B,LG2_34_6db:%B,MG2_34_12db:%B,HG2_34_18db:%B,IFTEST4:%B,IFTEST3:%B,IFTEST2:%B,IFTEST1:%B,PC1:%B,PC2:%B,EN_RF14:%B,EN_RF23:%B,DIS_DIV:%B,DIS_LO:%B,AMUX_SEL0:%B,AMUX_SEL1:%B,AMUX_SEL2:%B,SAT_FLAG_HIZ:%B,SENSOR_SEL0:%B,SENSOR_SEL1:%B,DCO_0:%B,DCO_1:%B,DCO_2:%B,DCO_3:%B}",
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => EN_12:%B */
                              &objptr->EN_12,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => LG1_12_6db:%B */
                              &objptr->LG1_12_6db,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => HG1_12_12db:%B */
                              &objptr->HG1_12_12db,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => LG2_12_6db:%B */
                              &objptr->LG2_12_6db,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => MG2_12_12db:%B */
                              &objptr->MG2_12_12db,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => HG2_12_18db:%B */
                              &objptr->HG2_12_18db,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => EN_34:%B */
                              &objptr->EN_34,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => LG1_34_6db:%B */
                              &objptr->LG1_34_6db,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => HG1_34_12db:%B */
                              &objptr->HG1_34_12db,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => LG2_34_6db:%B */
                              &objptr->LG2_34_6db,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => MG2_34_12db:%B */
                              &objptr->MG2_34_12db,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => HG2_34_18db:%B */
                              &objptr->HG2_34_18db,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => IFTEST4:%B */
                              &objptr->IFTEST4,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => IFTEST3:%B */
                              &objptr->IFTEST3,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => IFTEST2:%B */
                              &objptr->IFTEST2,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => IFTEST1:%B */
                              &objptr->IFTEST1,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => PC1:%B */
                              &objptr->PC1,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => PC2:%B */
                              &objptr->PC2,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => EN_RF14:%B */
                              &objptr->EN_RF14,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => EN_RF23:%B */
                              &objptr->EN_RF23,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => DIS_DIV:%B */
                              &objptr->DIS_DIV,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => DIS_LO:%B */
                              &objptr->DIS_LO,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => AMUX_SEL0:%B */
                              &objptr->AMUX_SEL0,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => AMUX_SEL1:%B */
                              &objptr->AMUX_SEL1,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => AMUX_SEL2:%B */
                              &objptr->AMUX_SEL2,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => SAT_FLAG_HIZ:%B */
                              &objptr->SAT_FLAG_HIZ,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => SENSOR_SEL0:%B */
                              &objptr->SENSOR_SEL0,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => SENSOR_SEL1:%B */
                              &objptr->SENSOR_SEL1,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => DCO_0:%B */
                              &objptr->DCO_0,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => DCO_1:%B */
                              &objptr->DCO_1,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => DCO_2:%B */
                              &objptr->DCO_2,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => DCO_3:%B */
                              &objptr->DCO_3);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did41_rficrx_bgt24ar4_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did41_rficrx_bgt24ar4_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                                 = 0;
    sys_param_sid0did41_rficrx_bgt24ar4_config_t *objptr = (sys_param_sid0did41_rficrx_bgt24ar4_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did41_rficrx_bgt24ar4_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did41_rficrx_bgt24ar4_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_rficrx_bgt24ar4_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_rficrx_bgt24ar4_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_pll_select_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_pll_select_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount           = 0;
    sys_param_pll_select_t *objptr = (sys_param_pll_select_t *)pvParam;
    //sys_param_log("sys_param_pll_select_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_pll_select_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{pll_sel:%d}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pll_sel:%d */
                              &objptr->pll_sel);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did50_pll_select_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did50_pll_select_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                            = 0;
    sys_param_sid0did50_pll_select_config_t *objptr = (sys_param_sid0did50_pll_select_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did50_pll_select_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did50_pll_select_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_pll_select_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_pll_select_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_pll_lmx2491_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_pll_lmx2491_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                  = 0;
    sys_param_pll_lmx2491_setup_t *objptr = (sys_param_pll_lmx2491_setup_t *)pvParam;
    //sys_param_log("sys_param_pll_lmx2491_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_pll_lmx2491_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{regset:%d,cp:%d}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => regset:%d */
                              &objptr->regset,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => cp:%d */
                              &objptr->cp);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did51_pll_lmx2491_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did51_pll_lmx2491_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                             = 0;
    sys_param_sid0did51_pll_lmx2491_config_t *objptr = (sys_param_sid0did51_pll_lmx2491_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did51_pll_lmx2491_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did51_pll_lmx2491_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_pll_lmx2491_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_pll_lmx2491_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_adc_select_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_adc_select_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount           = 0;
    sys_param_adc_select_t *objptr = (sys_param_adc_select_t *)pvParam;
    //sys_param_log("sys_param_adc_select_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_adc_select_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{adc_sel:%d}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => adc_sel:%d */
                              &objptr->adc_sel);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did60_adc_select_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did60_adc_select_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                            = 0;
    sys_param_sid0did60_adc_select_config_t *objptr = (sys_param_sid0did60_adc_select_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did60_adc_select_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did60_adc_select_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_adc_select_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_adc_select_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_adc_adar7251_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'ROUTING', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_adc_adar7251_setup_t_loads_ROUTING_array(char *str, int len, void *pvParam_local);
void sys_param_adc_adar7251_setup_t_loads_ROUTING_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_adc_adar7251_setup_t *objptr = (sys_param_adc_adar7251_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_adc_adar7251_setup_t_loads_ROUTING_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->ROUTING[i]);
    }
    objptr->ROUTING[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'LNA_GAIN', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_adc_adar7251_setup_t_loads_LNA_GAIN_array(char *str, int len, void *pvParam_local);
void sys_param_adc_adar7251_setup_t_loads_LNA_GAIN_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_adc_adar7251_setup_t *objptr = (sys_param_adc_adar7251_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_adc_adar7251_setup_t_loads_LNA_GAIN_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->LNA_GAIN[i]);
    }
    objptr->LNA_GAIN[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'PGA_GAIN', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_adc_adar7251_setup_t_loads_PGA_GAIN_array(char *str, int len, void *pvParam_local);
void sys_param_adc_adar7251_setup_t_loads_PGA_GAIN_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_adc_adar7251_setup_t *objptr = (sys_param_adc_adar7251_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_adc_adar7251_setup_t_loads_PGA_GAIN_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->PGA_GAIN[i]);
    }
    objptr->PGA_GAIN[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
int32_t sys_param_adc_adar7251_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                   = 0;
    sys_param_adc_adar7251_setup_t *objptr = (sys_param_adc_adar7251_setup_t *)pvParam;
    //sys_param_log("sys_param_adc_adar7251_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_adc_adar7251_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{ROUTING:%M,LNA_GAIN:%M,PGA_GAIN:%M,EQ_CAP:%d}",
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => ROUTING:%M */
                              sys_param_adc_adar7251_setup_t_loads_ROUTING_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => LNA_GAIN:%M */
                              sys_param_adc_adar7251_setup_t_loads_LNA_GAIN_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => PGA_GAIN:%M */
                              sys_param_adc_adar7251_setup_t_loads_PGA_GAIN_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => EQ_CAP:%d */
                              &objptr->EQ_CAP);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did61_adc_adar7251_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did61_adc_adar7251_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                              = 0;
    sys_param_sid0did61_adc_adar7251_config_t *objptr = (sys_param_sid0did61_adc_adar7251_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did61_adc_adar7251_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did61_adc_adar7251_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_adc_adar7251_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_adc_adar7251_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_adc_max11043_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'analog_filtermode', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_adc_max11043_setup_t_loads_analog_filtermode_array(char *str, int len, void *pvParam_local);
void sys_param_adc_max11043_setup_t_loads_analog_filtermode_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_adc_max11043_setup_t *objptr = (sys_param_adc_max11043_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_adc_max11043_setup_t_loads_analog_filtermode_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->analog_filtermode[i]);
    }
    objptr->analog_filtermode[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'gain', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_adc_max11043_setup_t_loads_gain_array(char *str, int len, void *pvParam_local);
void sys_param_adc_max11043_setup_t_loads_gain_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_adc_max11043_setup_t *objptr = (sys_param_adc_max11043_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_adc_max11043_setup_t_loads_gain_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->gain[i]);
    }
    objptr->gain[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'digtal_filtermode', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_adc_max11043_setup_t_loads_digtal_filtermode_array(char *str, int len, void *pvParam_local);
void sys_param_adc_max11043_setup_t_loads_digtal_filtermode_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_adc_max11043_setup_t *objptr = (sys_param_adc_max11043_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_adc_max11043_setup_t_loads_digtal_filtermode_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->digtal_filtermode[i]);
    }
    objptr->digtal_filtermode[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'fine_gain', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_adc_max11043_setup_t_loads_fine_gain_array(char *str, int len, void *pvParam_local);
void sys_param_adc_max11043_setup_t_loads_fine_gain_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_adc_max11043_setup_t *objptr = (sys_param_adc_max11043_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_adc_max11043_setup_t_loads_fine_gain_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->fine_gain[i]);
    }
    objptr->fine_gain[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'inputbias', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_adc_max11043_setup_t_loads_inputbias_array(char *str, int len, void *pvParam_local);
void sys_param_adc_max11043_setup_t_loads_inputbias_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_adc_max11043_setup_t *objptr = (sys_param_adc_max11043_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_adc_max11043_setup_t_loads_inputbias_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->inputbias[i]);
    }
    objptr->inputbias[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
int32_t sys_param_adc_max11043_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                   = 0;
    sys_param_adc_max11043_setup_t *objptr = (sys_param_adc_max11043_setup_t *)pvParam;
    //sys_param_log("sys_param_adc_max11043_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_adc_max11043_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{analog_filtermode:%M,gain:%M,digtal_filtermode:%M,fine_gain:%M,inputbias:%M}",
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => analog_filtermode:%M */
                              sys_param_adc_max11043_setup_t_loads_analog_filtermode_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => gain:%M */
                              sys_param_adc_max11043_setup_t_loads_gain_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => digtal_filtermode:%M */
                              sys_param_adc_max11043_setup_t_loads_digtal_filtermode_array, (void *)objptr,
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => fine_gain:%M */
                              sys_param_adc_max11043_setup_t_loads_fine_gain_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => inputbias:%M */
                              sys_param_adc_max11043_setup_t_loads_inputbias_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did62_adc_max11043_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did62_adc_max11043_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                              = 0;
    sys_param_sid0did62_adc_max11043_config_t *objptr = (sys_param_sid0did62_adc_max11043_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did62_adc_max11043_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did62_adc_max11043_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_adc_max11043_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_adc_max11043_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_app_packet_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_app_packet_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount           = 0;
    sys_param_app_packet_t *objptr = (sys_param_app_packet_t *)pvParam;
    //sys_param_log("sys_param_app_packet_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_app_packet_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{server_ip:%32s,port_num:%d,port_en:%d,client_mode_en:%B,pid_simple_en:%B,pid_compress_en:%B,pid_status_en:%B,pid_object_en:%B,pid_track_en:%B,pid_image_en:%B,pid_imagsp_en:%B,pid_logger_en:%B,pid_canlog_en:%B,pid_sensor_en:%B,pid_app_its_en:%B,pid_app_vf_en:%B,pid_app_fcw_en:%B,pid_app_lm_en:%B}",
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => server_ip:%32s */
                              objptr->server_ip,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => port_num:%d */
                              &objptr->port_num,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => port_en:%d */
                              &objptr->port_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => client_mode_en:%B */
                              &objptr->client_mode_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_simple_en:%B */
                              &objptr->pid_simple_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_compress_en:%B */
                              &objptr->pid_compress_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_status_en:%B */
                              &objptr->pid_status_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_object_en:%B */
                              &objptr->pid_object_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_track_en:%B */
                              &objptr->pid_track_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_image_en:%B */
                              &objptr->pid_image_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_imagsp_en:%B */
                              &objptr->pid_imagsp_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_logger_en:%B */
                              &objptr->pid_logger_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_canlog_en:%B */
                              &objptr->pid_canlog_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_sensor_en:%B */
                              &objptr->pid_sensor_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_app_its_en:%B */
                              &objptr->pid_app_its_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_app_vf_en:%B */
                              &objptr->pid_app_vf_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_app_fcw_en:%B */
                              &objptr->pid_app_fcw_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pid_app_lm_en:%B */
                              &objptr->pid_app_lm_en);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_app_packet_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'ports', 'type': 'sys_param_app_packet_t', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]'} */
void sys_param_app_packet_setup_t_loads_ports_array(char *str, int len, void *pvParam_local);
void sys_param_app_packet_setup_t_loads_ports_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_app_packet_setup_t *objptr = (sys_param_app_packet_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_app_packet_setup_t_loads_ports_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        sys_param_app_packet_t_loads((char *)ti.ptr, ti.len, &objptr->ports[i]);
    }
}
int32_t sys_param_app_packet_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                 = 0;
    sys_param_app_packet_setup_t *objptr = (sys_param_app_packet_setup_t *)pvParam;
    //sys_param_log("sys_param_app_packet_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_app_packet_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{count:%d,ports:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => count:%d */
                              &objptr->count,
                              /* type:sys_param_app_packet_t,  ismultidimarray : False, isarray : True, isstring : False, - json object type,   - json object array => ports:%M */
                              sys_param_app_packet_setup_t_loads_ports_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid0did200_app_packet_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did200_app_packet_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                             = 0;
    sys_param_sid0did200_app_packet_config_t *objptr = (sys_param_sid0did200_app_packet_config_t *)pvParam;
    //sys_param_log("sys_param_sid0did200_app_packet_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid0did200_app_packet_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_app_packet_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_app_packet_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_candrv_channel_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'acceptfilter_en', 'type': 'unsigned_char', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%B'} */
void sys_param_candrv_channel_setup_t_loads_acceptfilter_en_array(char *str, int len, void *pvParam_local);
void sys_param_candrv_channel_setup_t_loads_acceptfilter_en_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_candrv_channel_setup_t *objptr = (sys_param_candrv_channel_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_candrv_channel_setup_t_loads_acceptfilter_en_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%B", &objptr->acceptfilter_en[i]);
    }
    objptr->acceptfilter_en[i] = SYS_PARAM_BOOL_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'acceptfilter_id', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_candrv_channel_setup_t_loads_acceptfilter_id_array(char *str, int len, void *pvParam_local);
void sys_param_candrv_channel_setup_t_loads_acceptfilter_id_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_candrv_channel_setup_t *objptr = (sys_param_candrv_channel_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_candrv_channel_setup_t_loads_acceptfilter_id_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->acceptfilter_id[i]);
    }
    objptr->acceptfilter_id[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'acceptfilter_mask', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_candrv_channel_setup_t_loads_acceptfilter_mask_array(char *str, int len, void *pvParam_local);
void sys_param_candrv_channel_setup_t_loads_acceptfilter_mask_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_candrv_channel_setup_t *objptr = (sys_param_candrv_channel_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_candrv_channel_setup_t_loads_acceptfilter_mask_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->acceptfilter_mask[i]);
    }
    objptr->acceptfilter_mask[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
int32_t sys_param_candrv_channel_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                     = 0;
    sys_param_candrv_channel_setup_t *objptr = (sys_param_candrv_channel_setup_t *)pvParam;
    //sys_param_log("sys_param_candrv_channel_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_candrv_channel_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{cantype:%d,baudrate:%d,baudratefd:%d,samplepoint:%d,listenonlymode_en:%B,acceptfilter_en:%M,acceptfilter_id:%M,acceptfilter_mask:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => cantype:%d */
                              &objptr->cantype,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => baudrate:%d */
                              &objptr->baudrate,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => baudratefd:%d */
                              &objptr->baudratefd,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => samplepoint:%d */
                              &objptr->samplepoint,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => listenonlymode_en:%B */
                              &objptr->listenonlymode_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => acceptfilter_en:%M */
                              sys_param_candrv_channel_setup_t_loads_acceptfilter_en_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => acceptfilter_id:%M */
                              sys_param_candrv_channel_setup_t_loads_acceptfilter_id_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => acceptfilter_mask:%M */
                              sys_param_candrv_channel_setup_t_loads_acceptfilter_mask_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_candrv_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'channel', 'type': 'sys_param_candrv_channel_setup_t', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]'} */
void sys_param_candrv_setup_t_loads_channel_array(char *str, int len, void *pvParam_local);
void sys_param_candrv_setup_t_loads_channel_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_candrv_setup_t *objptr = (sys_param_candrv_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_candrv_setup_t_loads_channel_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        sys_param_candrv_channel_setup_t_loads((char *)ti.ptr, ti.len, &objptr->channel[i]);
    }
}
int32_t sys_param_candrv_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount             = 0;
    sys_param_candrv_setup_t *objptr = (sys_param_candrv_setup_t *)pvParam;
    //sys_param_log("sys_param_candrv_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_candrv_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{channel_count:%d,channel:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => channel_count:%d */
                              &objptr->channel_count,
                              /* type:sys_param_candrv_channel_setup_t,  ismultidimarray : False, isarray : True, isstring : False, - json object type,   - json object array => channel:%M */
                              sys_param_candrv_setup_t_loads_channel_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid6did0_candrv_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid6did0_candrv_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                       = 0;
    sys_param_sid6did0_candrv_config_t *objptr = (sys_param_sid6did0_candrv_config_t *)pvParam;
    //sys_param_log("sys_param_sid6did0_candrv_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid6did0_candrv_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_candrv_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_candrv_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_cansignal_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_cansignal_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount          = 0;
    sys_param_cansignal_t *objptr = (sys_param_cansignal_t *)pvParam;
    //sys_param_log("sys_param_cansignal_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_cansignal_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{en:%B,sigid:%d,msgid:%d,name:%32s,type:%c,byteorder:%c,bitpos:%d,length:%d,factor:%f,offset:%f,min:%f,max:%f,unit:%8s}",
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => en:%B */
                              &objptr->en,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sigid:%d */
                              &objptr->sigid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => msgid:%d */
                              &objptr->msgid,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => name:%32s */
                              objptr->name,
                              /* type:signed_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => type:%c */
                              &objptr->type,
                              /* type:signed_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => byteorder:%c */
                              &objptr->byteorder,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => bitpos:%d */
                              &objptr->bitpos,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => length:%d */
                              &objptr->length,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => factor:%f */
                              &objptr->factor,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => offset:%f */
                              &objptr->offset,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => min:%f */
                              &objptr->min,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => max:%f */
                              &objptr->max,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => unit:%8s */
                              objptr->unit);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_cansignal_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'signal', 'type': 'sys_param_cansignal_t', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [16], 'm_countlist_last': 16, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]'} */
void sys_param_cansignal_setup_t_loads_signal_array(char *str, int len, void *pvParam_local);
void sys_param_cansignal_setup_t_loads_signal_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_cansignal_setup_t *objptr = (sys_param_cansignal_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_cansignal_setup_t_loads_signal_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        sys_param_cansignal_t_loads((char *)ti.ptr, ti.len, &objptr->signal[i]);
    }
}
int32_t sys_param_cansignal_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                = 0;
    sys_param_cansignal_setup_t *objptr = (sys_param_cansignal_setup_t *)pvParam;
    //sys_param_log("sys_param_cansignal_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_cansignal_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{signal:%M}",
                              /* type:sys_param_cansignal_t,  ismultidimarray : False, isarray : True, isstring : False, - json object type,   - json object array => signal:%M */
                              sys_param_cansignal_setup_t_loads_signal_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid6did1_cansignal_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid6did1_cansignal_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                          = 0;
    sys_param_sid6did1_cansignal_config_t *objptr = (sys_param_sid6did1_cansignal_config_t *)pvParam;
    //sys_param_log("sys_param_sid6did1_cansignal_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid6did1_cansignal_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_cansignal_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_cansignal_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_can_txmsg_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_can_txmsg_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount          = 0;
    sys_param_can_txmsg_t *objptr = (sys_param_can_txmsg_t *)pvParam;
    //sys_param_log("sys_param_can_txmsg_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_can_txmsg_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{en:%B,start_id:%d,count:%d}",
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => en:%B */
                              &objptr->en,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => start_id:%d */
                              &objptr->start_id,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => count:%d */
                              &objptr->count);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_cantxmsg_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_cantxmsg_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount               = 0;
    sys_param_cantxmsg_setup_t *objptr = (sys_param_cantxmsg_setup_t *)pvParam;
    //sys_param_log("sys_param_cantxmsg_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_cantxmsg_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{status:%M,object:%M,track:%M,extioctrl:%M}",
                              /* type:sys_param_can_txmsg_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => status:%M */
                              sys_param_can_txmsg_t_loads, (void *)&(objptr->status),
                              /* type:sys_param_can_txmsg_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => object:%M */
                              sys_param_can_txmsg_t_loads, (void *)&(objptr->object),
                              /* type:sys_param_can_txmsg_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => track:%M */
                              sys_param_can_txmsg_t_loads, (void *)&(objptr->track),
                              /* type:sys_param_can_txmsg_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => extioctrl:%M */
                              sys_param_can_txmsg_t_loads, (void *)&(objptr->extioctrl));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid6did2_cantxmsg_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid6did2_cantxmsg_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                         = 0;
    sys_param_sid6did2_cantxmsg_config_t *objptr = (sys_param_sid6did2_cantxmsg_config_t *)pvParam;
    //sys_param_log("sys_param_sid6did2_cantxmsg_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid6did2_cantxmsg_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_cantxmsg_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_cantxmsg_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_filesystem_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_filesystem_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                 = 0;
    sys_param_filesystem_setup_t *objptr = (sys_param_filesystem_setup_t *)pvParam;
    //sys_param_log("sys_param_filesystem_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_filesystem_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{isformatted:%B,lastfilenumber:%d,mmc_write_enable:%B}",
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => isformatted:%B */
                              &objptr->isformatted,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => lastfilenumber:%d */
                              &objptr->lastfilenumber,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => mmc_write_enable:%B */
                              &objptr->mmc_write_enable);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid7did0_filesystem_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid7did0_filesystem_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                           = 0;
    sys_param_sid7did0_filesystem_config_t *objptr = (sys_param_sid7did0_filesystem_config_t *)pvParam;
    //sys_param_log("sys_param_sid7did0_filesystem_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid7did0_filesystem_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_filesystem_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_filesystem_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_status_timestamp_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_status_timestamp_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                 = 0;
    sys_param_status_timestamp_t *objptr = (sys_param_status_timestamp_t *)pvParam;
    //sys_param_log("sys_param_status_timestamp_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_status_timestamp_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{timestamp_s:%lf,rsp_timestamp_us:%ld,net_timestamp_us:%ld,rsp_cycletime:%f}",
                              /* type:double,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => timestamp_s:%lf */
                              &objptr->timestamp_s,
                              /* type:long_long,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => rsp_timestamp_us:%ld */
                              &objptr->rsp_timestamp_us,
                              /* type:long_long,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => net_timestamp_us:%ld */
                              &objptr->net_timestamp_us,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => rsp_cycletime:%f */
                              &objptr->rsp_cycletime);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_status_data_position_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_status_data_position_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                     = 0;
    sys_param_status_data_position_t *objptr = (sys_param_status_data_position_t *)pvParam;
    //sys_param_log("sys_param_status_data_position_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_status_data_position_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{yaw:%f,roll:%f,pitch:%f,altitude:%f}",
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => yaw:%f */
                              &objptr->yaw,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => roll:%f */
                              &objptr->roll,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => pitch:%f */
                              &objptr->pitch,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => altitude:%f */
                              &objptr->altitude);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_status_data_ecuinfo_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_status_data_ecuinfo_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                    = 0;
    sys_param_status_data_ecuinfo_t *objptr = (sys_param_status_data_ecuinfo_t *)pvParam;
    //sys_param_log("sys_param_status_data_ecuinfo_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_status_data_ecuinfo_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{temp_core:%f,temp_rfm:%f,vin:%f,v5:%f,v1_5:%f,v1_0:%f}",
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => temp_core:%f */
                              &objptr->temp_core,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => temp_rfm:%f */
                              &objptr->temp_rfm,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => vin:%f */
                              &objptr->vin,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => v5:%f */
                              &objptr->v5,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => v1_5:%f */
                              &objptr->v1_5,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => v1_0:%f */
                              &objptr->v1_0);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_status_data_gps_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_status_data_gps_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                = 0;
    sys_param_status_data_gps_t *objptr = (sys_param_status_data_gps_t *)pvParam;
    //sys_param_log("sys_param_status_data_gps_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_status_data_gps_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{status:%B,data:%1024s}",
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => status:%B */
                              &objptr->status,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => data:%1024s */
                              objptr->data);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_pid0_status_data_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_pid0_status_data_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                 = 0;
    sys_param_pid0_status_data_t *objptr = (sys_param_pid0_status_data_t *)pvParam;
    //sys_param_log("sys_param_pid0_status_data_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_pid0_status_data_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{scanindex:%d,timestamp:%M,position:%M,ecuinfo:%M,gps:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => scanindex:%d */
                              &objptr->scanindex,
                              /* type:sys_param_status_timestamp_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => timestamp:%M */
                              sys_param_status_timestamp_t_loads, (void *)&(objptr->timestamp),
                              /* type:sys_param_status_data_position_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => position:%M */
                              sys_param_status_data_position_t_loads, (void *)&(objptr->position),
                              /* type:sys_param_status_data_ecuinfo_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => ecuinfo:%M */
                              sys_param_status_data_ecuinfo_t_loads, (void *)&(objptr->ecuinfo),
                              /* type:sys_param_status_data_gps_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => gps:%M */
                              sys_param_status_data_gps_t_loads, (void *)&(objptr->gps));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_setup_timeschedule_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_setup_timeschedule_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                       = 0;
    sys_param_its_setup_timeschedule_t *objptr = (sys_param_its_setup_timeschedule_t *)pvParam;
    //sys_param_log("sys_param_its_setup_timeschedule_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_setup_timeschedule_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{timeunit:%8s,updatetime:%d}",
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => timeunit:%8s */
                              objptr->timeunit,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => updatetime:%d */
                              &objptr->updatetime);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_setup_laneinfo_lane_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'x', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [50], 'm_countlist_last': 50, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_its_setup_laneinfo_lane_t_loads_x_array(char *str, int len, void *pvParam_local);
void sys_param_its_setup_laneinfo_lane_t_loads_x_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_setup_laneinfo_lane_t *objptr = (sys_param_its_setup_laneinfo_lane_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_setup_laneinfo_lane_t_loads_x_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->x[i]);
    }
    objptr->x[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'y', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [50], 'm_countlist_last': 50, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_its_setup_laneinfo_lane_t_loads_y_array(char *str, int len, void *pvParam_local);
void sys_param_its_setup_laneinfo_lane_t_loads_y_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_setup_laneinfo_lane_t *objptr = (sys_param_its_setup_laneinfo_lane_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_setup_laneinfo_lane_t_loads_y_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->y[i]);
    }
    objptr->y[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
int32_t sys_param_its_setup_laneinfo_lane_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                        = 0;
    sys_param_its_setup_laneinfo_lane_t *objptr = (sys_param_its_setup_laneinfo_lane_t *)pvParam;
    //sys_param_log("sys_param_its_setup_laneinfo_lane_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_setup_laneinfo_lane_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{x:%M,y:%M}",
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => x:%M */
                              sys_param_its_setup_laneinfo_lane_t_loads_x_array, (void *)objptr,
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => y:%M */
                              sys_param_its_setup_laneinfo_lane_t_loads_y_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_setup_zone_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'x', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [100], 'm_countlist_last': 100, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_its_setup_zone_t_loads_x_array(char *str, int len, void *pvParam_local);
void sys_param_its_setup_zone_t_loads_x_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_setup_zone_t *objptr = (sys_param_its_setup_zone_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_setup_zone_t_loads_x_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->x[i]);
    }
    objptr->x[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'y', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [100], 'm_countlist_last': 100, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_its_setup_zone_t_loads_y_array(char *str, int len, void *pvParam_local);
void sys_param_its_setup_zone_t_loads_y_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_setup_zone_t *objptr = (sys_param_its_setup_zone_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_setup_zone_t_loads_y_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->y[i]);
    }
    objptr->y[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
int32_t sys_param_its_setup_zone_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount               = 0;
    sys_param_its_setup_zone_t *objptr = (sys_param_its_setup_zone_t *)pvParam;
    //sys_param_log("sys_param_its_setup_zone_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_setup_zone_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{x:%M,y:%M}",
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => x:%M */
                              sys_param_its_setup_zone_t_loads_x_array, (void *)objptr,
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => y:%M */
                              sys_param_its_setup_zone_t_loads_y_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_setup_hotspotzone_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'x', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [100], 'm_countlist_last': 100, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_its_setup_hotspotzone_t_loads_x_array(char *str, int len, void *pvParam_local);
void sys_param_its_setup_hotspotzone_t_loads_x_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_setup_hotspotzone_t *objptr = (sys_param_its_setup_hotspotzone_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_setup_hotspotzone_t_loads_x_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->x[i]);
    }
    objptr->x[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'y', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [100], 'm_countlist_last': 100, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_its_setup_hotspotzone_t_loads_y_array(char *str, int len, void *pvParam_local);
void sys_param_its_setup_hotspotzone_t_loads_y_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_setup_hotspotzone_t *objptr = (sys_param_its_setup_hotspotzone_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_setup_hotspotzone_t_loads_y_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->y[i]);
    }
    objptr->y[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
int32_t sys_param_its_setup_hotspotzone_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                      = 0;
    sys_param_its_setup_hotspotzone_t *objptr = (sys_param_its_setup_hotspotzone_t *)pvParam;
    //sys_param_log("sys_param_its_setup_hotspotzone_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_setup_hotspotzone_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{x:%M,y:%M,width:%f,midoffset:%f}",
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => x:%M */
                              sys_param_its_setup_hotspotzone_t_loads_x_array, (void *)objptr,
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => y:%M */
                              sys_param_its_setup_hotspotzone_t_loads_y_array, (void *)objptr,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => width:%f */
                              &objptr->width,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => midoffset:%f */
                              &objptr->midoffset);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_setup_laneinfo_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_setup_laneinfo_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                   = 0;
    sys_param_its_setup_laneinfo_t *objptr = (sys_param_its_setup_laneinfo_t *)pvParam;
    //sys_param_log("sys_param_its_setup_laneinfo_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_setup_laneinfo_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{stepcount:%d,left:%M,hotspotzone:%M,trackingzone:%M,right:%M,number:%d}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => stepcount:%d */
                              &objptr->stepcount,
                              /* type:sys_param_its_setup_laneinfo_lane_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => left:%M */
                              sys_param_its_setup_laneinfo_lane_t_loads, (void *)&(objptr->left),
                              /* type:sys_param_its_setup_hotspotzone_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => hotspotzone:%M */
                              sys_param_its_setup_hotspotzone_t_loads, (void *)&(objptr->hotspotzone),
                              /* type:sys_param_its_setup_zone_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => trackingzone:%M */
                              sys_param_its_setup_zone_t_loads, (void *)&(objptr->trackingzone),
                              /* type:sys_param_its_setup_laneinfo_lane_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => right:%M */
                              sys_param_its_setup_laneinfo_lane_t_loads, (void *)&(objptr->right),
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => number:%d */
                              &objptr->number);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_setup_area_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'x', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_its_setup_area_t_loads_x_array(char *str, int len, void *pvParam_local);
void sys_param_its_setup_area_t_loads_x_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_setup_area_t *objptr = (sys_param_its_setup_area_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_setup_area_t_loads_x_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->x[i]);
    }
    objptr->x[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'y', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_its_setup_area_t_loads_y_array(char *str, int len, void *pvParam_local);
void sys_param_its_setup_area_t_loads_y_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_setup_area_t *objptr = (sys_param_its_setup_area_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_setup_area_t_loads_y_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->y[i]);
    }
    objptr->y[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
int32_t sys_param_its_setup_area_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount               = 0;
    sys_param_its_setup_area_t *objptr = (sys_param_its_setup_area_t *)pvParam;
    //sys_param_log("sys_param_its_setup_area_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_setup_area_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{x:%M,y:%M,t:%f}",
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => x:%M */
                              sys_param_its_setup_area_t_loads_x_array, (void *)objptr,
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => y:%M */
                              sys_param_its_setup_area_t_loads_y_array, (void *)objptr,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => t:%f */
                              &objptr->t);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_setup_blackout_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'area', 'type': 'sys_param_its_setup_area_t', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [10], 'm_countlist_last': 10, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]'} */
void sys_param_its_setup_blackout_t_loads_area_array(char *str, int len, void *pvParam_local);
void sys_param_its_setup_blackout_t_loads_area_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_setup_blackout_t *objptr = (sys_param_its_setup_blackout_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_setup_blackout_t_loads_area_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        sys_param_its_setup_area_t_loads((char *)ti.ptr, ti.len, &objptr->area[i]);
    }
}
int32_t sys_param_its_setup_blackout_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                   = 0;
    sys_param_its_setup_blackout_t *objptr = (sys_param_its_setup_blackout_t *)pvParam;
    //sys_param_log("sys_param_its_setup_blackout_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_setup_blackout_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{count:%d,area:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => count:%d */
                              &objptr->count,
                              /* type:sys_param_its_setup_area_t,  ismultidimarray : False, isarray : True, isstring : False, - json object type,   - json object array => area:%M */
                              sys_param_its_setup_blackout_t_loads_area_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_setup_speedlimit_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_setup_speedlimit_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                     = 0;
    sys_param_its_setup_speedlimit_t *objptr = (sys_param_its_setup_speedlimit_t *)pvParam;
    //sys_param_log("sys_param_its_setup_speedlimit_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_setup_speedlimit_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{high_speedlimit_kph:%f,low_speedlimit_kph:%f,speedlimit_compensation_percentage:%d}",
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => high_speedlimit_kph:%f */
                              &objptr->high_speedlimit_kph,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => low_speedlimit_kph:%f */
                              &objptr->low_speedlimit_kph,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => speedlimit_compensation_percentage:%d */
                              &objptr->speedlimit_compensation_percentage);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_setup_misc_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_setup_misc_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount               = 0;
    sys_param_its_setup_misc_t *objptr = (sys_param_its_setup_misc_t *)pvParam;
    //sys_param_log("sys_param_its_setup_misc_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_setup_misc_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{camera_on:%B,trackingzone_view_on:%B,autoalignment_on:%B,num_track_autoalignment:%d}",
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => camera_on:%B */
                              &objptr->camera_on,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => trackingzone_view_on:%B */
                              &objptr->trackingzone_view_on,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => autoalignment_on:%B */
                              &objptr->autoalignment_on,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => num_track_autoalignment:%d */
                              &objptr->num_track_autoalignment);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'laneinfo', 'type': 'sys_param_its_setup_laneinfo_t', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]'} */
void sys_param_its_setup_t_loads_laneinfo_array(char *str, int len, void *pvParam_local);
void sys_param_its_setup_t_loads_laneinfo_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_setup_t *objptr = (sys_param_its_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_setup_t_loads_laneinfo_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        sys_param_its_setup_laneinfo_t_loads((char *)ti.ptr, ti.len, &objptr->laneinfo[i]);
    }
}
int32_t sys_param_its_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount          = 0;
    sys_param_its_setup_t *objptr = (sys_param_its_setup_t *)pvParam;
    //sys_param_log("sys_param_its_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{timeschedule:%M,misc:%M,middlelane:%f,uplaneangle:%d,downlaneangle:%d,lanecount:%d,speedlimit:%M,laneinfo:%M,blackout:%M}",
                              /* type:sys_param_its_setup_timeschedule_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => timeschedule:%M */
                              sys_param_its_setup_timeschedule_t_loads, (void *)&(objptr->timeschedule),
                              /* type:sys_param_its_setup_misc_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => misc:%M */
                              sys_param_its_setup_misc_t_loads, (void *)&(objptr->misc),
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => middlelane:%f */
                              &objptr->middlelane,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => uplaneangle:%d */
                              &objptr->uplaneangle,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => downlaneangle:%d */
                              &objptr->downlaneangle,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => lanecount:%d */
                              &objptr->lanecount,
                              /* type:sys_param_its_setup_speedlimit_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => speedlimit:%M */
                              sys_param_its_setup_speedlimit_t_loads, (void *)&(objptr->speedlimit),
                              /* type:sys_param_its_setup_laneinfo_t,  ismultidimarray : False, isarray : True, isstring : False, - json object type,   - json object array => laneinfo:%M */
                              sys_param_its_setup_t_loads_laneinfo_array, (void *)objptr,
                              /* type:sys_param_its_setup_blackout_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => blackout:%M */
                              sys_param_its_setup_blackout_t_loads, (void *)&(objptr->blackout));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid8did0_its_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid8did0_its_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                    = 0;
    sys_param_sid8did0_its_config_t *objptr = (sys_param_sid8did0_its_config_t *)pvParam;
    //sys_param_log("sys_param_sid8did0_its_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid8did0_its_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,description:%32s,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => description:%32s */
                              objptr->description,
                              /* type:sys_param_its_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_its_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_relay_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'relay_enable', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_its_relay_t_loads_relay_enable_array(char *str, int len, void *pvParam_local);
void sys_param_its_relay_t_loads_relay_enable_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_relay_t *objptr = (sys_param_its_relay_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_relay_t_loads_relay_enable_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->relay_enable[i]);
    }
    objptr->relay_enable[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'relay_type', 'type': 'char', 'ismultidimarray': True, 'isarray': True, 'isstring': True, 'm_countlist': [2], 'm_countlist_last': 8, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%8s'} */
void sys_param_its_relay_t_loads_relay_type_array(char *str, int len, void *pvParam_local);
void sys_param_its_relay_t_loads_relay_type_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_relay_t *objptr = (sys_param_its_relay_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_relay_t_loads_relay_type_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        strncpy((char *)&objptr->relay_type[i], ti.ptr, ti.len);
    }
}
/* {'subfunc': True, 'm_name': 'relay_on_time_ms', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_its_relay_t_loads_relay_on_time_ms_array(char *str, int len, void *pvParam_local);
void sys_param_its_relay_t_loads_relay_on_time_ms_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_relay_t *objptr = (sys_param_its_relay_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_relay_t_loads_relay_on_time_ms_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->relay_on_time_ms[i]);
    }
    objptr->relay_on_time_ms[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'relay_off_time_ms', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_its_relay_t_loads_relay_off_time_ms_array(char *str, int len, void *pvParam_local);
void sys_param_its_relay_t_loads_relay_off_time_ms_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_relay_t *objptr = (sys_param_its_relay_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_relay_t_loads_relay_off_time_ms_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->relay_off_time_ms[i]);
    }
    objptr->relay_off_time_ms[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'relay_adjust_time_ms', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_its_relay_t_loads_relay_adjust_time_ms_array(char *str, int len, void *pvParam_local);
void sys_param_its_relay_t_loads_relay_adjust_time_ms_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_relay_t *objptr = (sys_param_its_relay_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_relay_t_loads_relay_adjust_time_ms_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->relay_adjust_time_ms[i]);
    }
    objptr->relay_adjust_time_ms[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'relay_lowbound_time_ms', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_its_relay_t_loads_relay_lowbound_time_ms_array(char *str, int len, void *pvParam_local);
void sys_param_its_relay_t_loads_relay_lowbound_time_ms_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_relay_t *objptr = (sys_param_its_relay_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_relay_t_loads_relay_lowbound_time_ms_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->relay_lowbound_time_ms[i]);
    }
    objptr->relay_lowbound_time_ms[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'relay_highbound_time_ms', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_its_relay_t_loads_relay_highbound_time_ms_array(char *str, int len, void *pvParam_local);
void sys_param_its_relay_t_loads_relay_highbound_time_ms_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_relay_t *objptr = (sys_param_its_relay_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_relay_t_loads_relay_highbound_time_ms_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->relay_highbound_time_ms[i]);
    }
    objptr->relay_highbound_time_ms[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'relay_on_event_type', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_its_relay_t_loads_relay_on_event_type_array(char *str, int len, void *pvParam_local);
void sys_param_its_relay_t_loads_relay_on_event_type_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_relay_t *objptr = (sys_param_its_relay_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_relay_t_loads_relay_on_event_type_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->relay_on_event_type[i]);
    }
    objptr->relay_on_event_type[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
int32_t sys_param_its_relay_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount          = 0;
    sys_param_its_relay_t *objptr = (sys_param_its_relay_t *)pvParam;
    //sys_param_log("sys_param_its_relay_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_relay_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{relay_cnt:%d,relay_enable:%M,relay_type:%M,relay_on_time_ms:%M,relay_off_time_ms:%M,relay_adjust_time_ms:%M,relay_lowbound_time_ms:%M,relay_highbound_time_ms:%M,relay_on_event_type:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => relay_cnt:%d */
                              &objptr->relay_cnt,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => relay_enable:%M */
                              sys_param_its_relay_t_loads_relay_enable_array, (void *)objptr,
                              /* type:char,  ismultidimarray : True, isarray : True, isstring : True, - json primitive type,   - json bool/char/int/float multidimensional array => relay_type:%M */
                              sys_param_its_relay_t_loads_relay_type_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => relay_on_time_ms:%M */
                              sys_param_its_relay_t_loads_relay_on_time_ms_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => relay_off_time_ms:%M */
                              sys_param_its_relay_t_loads_relay_off_time_ms_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => relay_adjust_time_ms:%M */
                              sys_param_its_relay_t_loads_relay_adjust_time_ms_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => relay_lowbound_time_ms:%M */
                              sys_param_its_relay_t_loads_relay_lowbound_time_ms_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => relay_highbound_time_ms:%M */
                              sys_param_its_relay_t_loads_relay_highbound_time_ms_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => relay_on_event_type:%M */
                              sys_param_its_relay_t_loads_relay_on_event_type_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_device_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_device_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                 = 0;
    sys_param_its_device_setup_t *objptr = (sys_param_its_device_setup_t *)pvParam;
    //sys_param_log("sys_param_its_device_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_device_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{relay:%M}",
                              /* type:sys_param_its_relay_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => relay:%M */
                              sys_param_its_relay_t_loads, (void *)&(objptr->relay));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid8did1_its_relay_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid8did1_its_relay_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                          = 0;
    sys_param_sid8did1_its_relay_config_t *objptr = (sys_param_sid8did1_its_relay_config_t *)pvParam;
    //sys_param_log("sys_param_sid8did1_its_relay_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid8did1_its_relay_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,description:%32s,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => description:%32s */
                              objptr->description,
                              /* type:sys_param_its_device_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_its_device_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_alignment_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_alignment_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                    = 0;
    sys_param_its_alignment_setup_t *objptr = (sys_param_its_alignment_setup_t *)pvParam;
    //sys_param_log("sys_param_its_alignment_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_alignment_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{autoalignment_on:%B,num_track_autoalignment:%d,status_autoalignment:%d,angle_aligned:%f}",
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => autoalignment_on:%B */
                              &objptr->autoalignment_on,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => num_track_autoalignment:%d */
                              &objptr->num_track_autoalignment,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => status_autoalignment:%d */
                              &objptr->status_autoalignment,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => angle_aligned:%f */
                              &objptr->angle_aligned);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid8did2_its_align_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid8did2_its_align_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                          = 0;
    sys_param_sid8did2_its_align_config_t *objptr = (sys_param_sid8did2_its_align_config_t *)pvParam;
    //sys_param_log("sys_param_sid8did2_its_align_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid8did2_its_align_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,description:%32s,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => description:%32s */
                              objptr->description,
                              /* type:sys_param_its_alignment_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_its_alignment_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_testmode_speedlimit_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_testmode_speedlimit_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                        = 0;
    sys_param_its_testmode_speedlimit_t *objptr = (sys_param_its_testmode_speedlimit_t *)pvParam;
    //sys_param_log("sys_param_its_testmode_speedlimit_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_testmode_speedlimit_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{high_speedlimit_tolerance_percentage:%f,low_speedlimit_tolerance_percentage:%f}",
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => high_speedlimit_tolerance_percentage:%f */
                              &objptr->high_speedlimit_tolerance_percentage,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => low_speedlimit_tolerance_percentage:%f */
                              &objptr->low_speedlimit_tolerance_percentage);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_testmode_trigger_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'trigger_en', 'type': 'unsigned_char', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%B'} */
void sys_param_its_testmode_trigger_t_loads_trigger_en_array(char *str, int len, void *pvParam_local);
void sys_param_its_testmode_trigger_t_loads_trigger_en_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_testmode_trigger_t *objptr = (sys_param_its_testmode_trigger_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_testmode_trigger_t_loads_trigger_en_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%B", &objptr->trigger_en[i]);
    }
    objptr->trigger_en[i] = SYS_PARAM_BOOL_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'trigger_period', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_its_testmode_trigger_t_loads_trigger_period_array(char *str, int len, void *pvParam_local);
void sys_param_its_testmode_trigger_t_loads_trigger_period_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_testmode_trigger_t *objptr = (sys_param_its_testmode_trigger_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_testmode_trigger_t_loads_trigger_period_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->trigger_period[i]);
    }
    objptr->trigger_period[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'trigger_ttlc_time_ms', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_its_testmode_trigger_t_loads_trigger_ttlc_time_ms_array(char *str, int len, void *pvParam_local);
void sys_param_its_testmode_trigger_t_loads_trigger_ttlc_time_ms_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_testmode_trigger_t *objptr = (sys_param_its_testmode_trigger_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_testmode_trigger_t_loads_trigger_ttlc_time_ms_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->trigger_ttlc_time_ms[i]);
    }
    objptr->trigger_ttlc_time_ms[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
int32_t sys_param_its_testmode_trigger_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                     = 0;
    sys_param_its_testmode_trigger_t *objptr = (sys_param_its_testmode_trigger_t *)pvParam;
    //sys_param_log("sys_param_its_testmode_trigger_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_testmode_trigger_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{trigger_en:%M,trigger_period:%M,trigger_ttlc_time_ms:%M}",
                              /* type:unsigned_char,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => trigger_en:%M */
                              sys_param_its_testmode_trigger_t_loads_trigger_en_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => trigger_period:%M */
                              sys_param_its_testmode_trigger_t_loads_trigger_period_array, (void *)objptr,
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => trigger_ttlc_time_ms:%M */
                              sys_param_its_testmode_trigger_t_loads_trigger_ttlc_time_ms_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_testmode_hotspotzone_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'modlane_en', 'type': 'unsigned_char', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%B'} */
void sys_param_its_testmode_hotspotzone_t_loads_modlane_en_array(char *str, int len, void *pvParam_local);
void sys_param_its_testmode_hotspotzone_t_loads_modlane_en_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_testmode_hotspotzone_t *objptr = (sys_param_its_testmode_hotspotzone_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_testmode_hotspotzone_t_loads_modlane_en_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%B", &objptr->modlane_en[i]);
    }
    objptr->modlane_en[i] = SYS_PARAM_BOOL_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'modlane_offset_hotspotzone_y', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_its_testmode_hotspotzone_t_loads_modlane_offset_hotspotzone_y_array(char *str, int len, void *pvParam_local);
void sys_param_its_testmode_hotspotzone_t_loads_modlane_offset_hotspotzone_y_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_testmode_hotspotzone_t *objptr = (sys_param_its_testmode_hotspotzone_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_testmode_hotspotzone_t_loads_modlane_offset_hotspotzone_y_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->modlane_offset_hotspotzone_y[i]);
    }
    objptr->modlane_offset_hotspotzone_y[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'modlane_offset_hotspotzone_width', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_its_testmode_hotspotzone_t_loads_modlane_offset_hotspotzone_width_array(char *str, int len, void *pvParam_local);
void sys_param_its_testmode_hotspotzone_t_loads_modlane_offset_hotspotzone_width_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_testmode_hotspotzone_t *objptr = (sys_param_its_testmode_hotspotzone_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_testmode_hotspotzone_t_loads_modlane_offset_hotspotzone_width_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->modlane_offset_hotspotzone_width[i]);
    }
    objptr->modlane_offset_hotspotzone_width[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'modlane_offset_hotspotzone_offset', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [2], 'm_countlist_last': 2, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_its_testmode_hotspotzone_t_loads_modlane_offset_hotspotzone_offset_array(char *str, int len, void *pvParam_local);
void sys_param_its_testmode_hotspotzone_t_loads_modlane_offset_hotspotzone_offset_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_testmode_hotspotzone_t *objptr = (sys_param_its_testmode_hotspotzone_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_testmode_hotspotzone_t_loads_modlane_offset_hotspotzone_offset_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->modlane_offset_hotspotzone_offset[i]);
    }
    objptr->modlane_offset_hotspotzone_offset[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
int32_t sys_param_its_testmode_hotspotzone_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                         = 0;
    sys_param_its_testmode_hotspotzone_t *objptr = (sys_param_its_testmode_hotspotzone_t *)pvParam;
    //sys_param_log("sys_param_its_testmode_hotspotzone_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_testmode_hotspotzone_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{modlane_en:%M,modlane_offset_hotspotzone_y:%M,modlane_offset_hotspotzone_width:%M,modlane_offset_hotspotzone_offset:%M}",
                              /* type:unsigned_char,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => modlane_en:%M */
                              sys_param_its_testmode_hotspotzone_t_loads_modlane_en_array, (void *)objptr,
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => modlane_offset_hotspotzone_y:%M */
                              sys_param_its_testmode_hotspotzone_t_loads_modlane_offset_hotspotzone_y_array, (void *)objptr,
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => modlane_offset_hotspotzone_width:%M */
                              sys_param_its_testmode_hotspotzone_t_loads_modlane_offset_hotspotzone_width_array, (void *)objptr,
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => modlane_offset_hotspotzone_offset:%M */
                              sys_param_its_testmode_hotspotzone_t_loads_modlane_offset_hotspotzone_offset_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_testmode_image_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_testmode_image_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                   = 0;
    sys_param_its_testmode_image_t *objptr = (sys_param_its_testmode_image_t *)pvParam;
    //sys_param_log("sys_param_its_testmode_image_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_testmode_image_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{skip_image_count:%d}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => skip_image_count:%d */
                              &objptr->skip_image_count);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_testmode_misc_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_testmode_misc_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                  = 0;
    sys_param_its_testmode_misc_t *objptr = (sys_param_its_testmode_misc_t *)pvParam;
    //sys_param_log("sys_param_its_testmode_misc_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_testmode_misc_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{trackzone_xrange:%f,en_lanechange:%B,low_exclude_speed:%f}",
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => trackzone_xrange:%f */
                              &objptr->trackzone_xrange,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => en_lanechange:%B */
                              &objptr->en_lanechange,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => low_exclude_speed:%f */
                              &objptr->low_exclude_speed);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_testmode_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_testmode_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                   = 0;
    sys_param_its_testmode_setup_t *objptr = (sys_param_its_testmode_setup_t *)pvParam;
    //sys_param_log("sys_param_its_testmode_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_testmode_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{speedlimit_tolerance:%M,trigger:%M,modlane:%M,imagetest:%M,misc:%M}",
                              /* type:sys_param_its_testmode_speedlimit_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => speedlimit_tolerance:%M */
                              sys_param_its_testmode_speedlimit_t_loads, (void *)&(objptr->speedlimit_tolerance),
                              /* type:sys_param_its_testmode_trigger_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => trigger:%M */
                              sys_param_its_testmode_trigger_t_loads, (void *)&(objptr->trigger),
                              /* type:sys_param_its_testmode_hotspotzone_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => modlane:%M */
                              sys_param_its_testmode_hotspotzone_t_loads, (void *)&(objptr->modlane),
                              /* type:sys_param_its_testmode_image_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => imagetest:%M */
                              sys_param_its_testmode_image_t_loads, (void *)&(objptr->imagetest),
                              /* type:sys_param_its_testmode_misc_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => misc:%M */
                              sys_param_its_testmode_misc_t_loads, (void *)&(objptr->misc));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid8did10_its_testmode_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid8did10_its_testmode_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                              = 0;
    sys_param_sid8did10_its_testmode_config_t *objptr = (sys_param_sid8did10_its_testmode_config_t *)pvParam;
    //sys_param_log("sys_param_sid8did10_its_testmode_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid8did10_its_testmode_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,description:%32s,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => description:%32s */
                              objptr->description,
                              /* type:sys_param_its_testmode_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_its_testmode_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_data_lane_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'num', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_its_data_lane_t_loads_num_array(char *str, int len, void *pvParam_local);
void sys_param_its_data_lane_t_loads_num_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_data_lane_t *objptr = (sys_param_its_data_lane_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_data_lane_t_loads_num_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->num[i]);
    }
    objptr->num[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'period', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [5], 'm_countlist_last': 5, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_its_data_lane_t_loads_period_array(char *str, int len, void *pvParam_local);
void sys_param_its_data_lane_t_loads_period_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_data_lane_t *objptr = (sys_param_its_data_lane_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_data_lane_t_loads_period_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->period[i]);
    }
    objptr->period[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
int32_t sys_param_its_data_lane_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount              = 0;
    sys_param_its_data_lane_t *objptr = (sys_param_its_data_lane_t *)pvParam;
    //sys_param_log("sys_param_its_data_lane_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_data_lane_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{cnt:%d,num:%M,period:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => cnt:%d */
                              &objptr->cnt,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => num:%M */
                              sys_param_its_data_lane_t_loads_num_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => period:%M */
                              sys_param_its_data_lane_t_loads_period_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_data_count_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'diff', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_its_data_count_t_loads_diff_array(char *str, int len, void *pvParam_local);
void sys_param_its_data_count_t_loads_diff_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_data_count_t *objptr = (sys_param_its_data_count_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_data_count_t_loads_diff_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->diff[i]);
    }
    objptr->diff[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'acc', 'type': 'int', 'ismultidimarray': True, 'isarray': True, 'isstring': False, 'm_countlist': [5, 4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i', 'j'], 'localloopvaridx': '[i][j]', 'subfmt': '%d'} */
void sys_param_its_data_count_t_loads_acc_array(char *str, int len, void *pvParam_local);
void sys_param_its_data_count_t_loads_acc_array(char *str, int len, void *pvParam_local)
{
    int32_t i, j;
    struct json_token ti, tj;
    sys_param_its_data_count_t *objptr = (sys_param_its_data_count_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_data_count_t_loads_acc_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);
        for(j = 0; json_scanf_array_elem(ti.ptr, ti.len, "", j, &tj) > 0; j++)
        {
            //sys_param_log("Index %ld, token [%.*s]\n", j, tj.len, tj.ptr);

            json_scanf((char *)tj.ptr, tj.len, "%d", &objptr->acc[i][j]);
        }
        objptr->acc[i][j] = SYS_PARAM_INT32_ARR_END_VALUE;
    }
}
/* {'subfunc': True, 'm_name': 'lc', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_its_data_count_t_loads_lc_array(char *str, int len, void *pvParam_local);
void sys_param_its_data_count_t_loads_lc_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_data_count_t *objptr = (sys_param_its_data_count_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_data_count_t_loads_lc_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->lc[i]);
    }
    objptr->lc[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'acclc', 'type': 'int', 'ismultidimarray': True, 'isarray': True, 'isstring': False, 'm_countlist': [5, 4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i', 'j'], 'localloopvaridx': '[i][j]', 'subfmt': '%d'} */
void sys_param_its_data_count_t_loads_acclc_array(char *str, int len, void *pvParam_local);
void sys_param_its_data_count_t_loads_acclc_array(char *str, int len, void *pvParam_local)
{
    int32_t i, j;
    struct json_token ti, tj;
    sys_param_its_data_count_t *objptr = (sys_param_its_data_count_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_data_count_t_loads_acclc_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);
        for(j = 0; json_scanf_array_elem(ti.ptr, ti.len, "", j, &tj) > 0; j++)
        {
            //sys_param_log("Index %ld, token [%.*s]\n", j, tj.len, tj.ptr);

            json_scanf((char *)tj.ptr, tj.len, "%d", &objptr->acclc[i][j]);
        }
        objptr->acclc[i][j] = SYS_PARAM_INT32_ARR_END_VALUE;
    }
}
int32_t sys_param_its_data_count_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount               = 0;
    sys_param_its_data_count_t *objptr = (sys_param_its_data_count_t *)pvParam;
    //sys_param_log("sys_param_its_data_count_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_data_count_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{ts:%d,diff:%M,acc:%M,lc:%M,acclc:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => ts:%d */
                              &objptr->ts,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => diff:%M */
                              sys_param_its_data_count_t_loads_diff_array, (void *)objptr,
                              /* type:int,  ismultidimarray : True, isarray : True, isstring : False, - json primitive type,   - json bool/char/int/float multidimensional array => acc:%M */
                              sys_param_its_data_count_t_loads_acc_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => lc:%M */
                              sys_param_its_data_count_t_loads_lc_array, (void *)objptr,
                              /* type:int,  ismultidimarray : True, isarray : True, isstring : False, - json primitive type,   - json bool/char/int/float multidimensional array => acclc:%M */
                              sys_param_its_data_count_t_loads_acclc_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_data_speed_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'average', 'type': 'float', 'ismultidimarray': True, 'isarray': True, 'isstring': False, 'm_countlist': [5, 4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i', 'j'], 'localloopvaridx': '[i][j]', 'subfmt': '%f'} */
void sys_param_its_data_speed_t_loads_average_array(char *str, int len, void *pvParam_local);
void sys_param_its_data_speed_t_loads_average_array(char *str, int len, void *pvParam_local)
{
    int32_t i, j;
    struct json_token ti, tj;
    sys_param_its_data_speed_t *objptr = (sys_param_its_data_speed_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_data_speed_t_loads_average_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);
        for(j = 0; json_scanf_array_elem(ti.ptr, ti.len, "", j, &tj) > 0; j++)
        {
            //sys_param_log("Index %ld, token [%.*s]\n", j, tj.len, tj.ptr);

            json_scanf((char *)tj.ptr, tj.len, "%f", &objptr->average[i][j]);
        }
        objptr->average[i][j] = SYS_PARAM_F32_ARR_END_VALUE;
    }
}
/* {'subfunc': True, 'm_name': 'min', 'type': 'float', 'ismultidimarray': True, 'isarray': True, 'isstring': False, 'm_countlist': [5, 4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i', 'j'], 'localloopvaridx': '[i][j]', 'subfmt': '%f'} */
void sys_param_its_data_speed_t_loads_min_array(char *str, int len, void *pvParam_local);
void sys_param_its_data_speed_t_loads_min_array(char *str, int len, void *pvParam_local)
{
    int32_t i, j;
    struct json_token ti, tj;
    sys_param_its_data_speed_t *objptr = (sys_param_its_data_speed_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_data_speed_t_loads_min_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);
        for(j = 0; json_scanf_array_elem(ti.ptr, ti.len, "", j, &tj) > 0; j++)
        {
            //sys_param_log("Index %ld, token [%.*s]\n", j, tj.len, tj.ptr);

            json_scanf((char *)tj.ptr, tj.len, "%f", &objptr->min[i][j]);
        }
        objptr->min[i][j] = SYS_PARAM_F32_ARR_END_VALUE;
    }
}
/* {'subfunc': True, 'm_name': 'max', 'type': 'float', 'ismultidimarray': True, 'isarray': True, 'isstring': False, 'm_countlist': [5, 4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i', 'j'], 'localloopvaridx': '[i][j]', 'subfmt': '%f'} */
void sys_param_its_data_speed_t_loads_max_array(char *str, int len, void *pvParam_local);
void sys_param_its_data_speed_t_loads_max_array(char *str, int len, void *pvParam_local)
{
    int32_t i, j;
    struct json_token ti, tj;
    sys_param_its_data_speed_t *objptr = (sys_param_its_data_speed_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_data_speed_t_loads_max_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);
        for(j = 0; json_scanf_array_elem(ti.ptr, ti.len, "", j, &tj) > 0; j++)
        {
            //sys_param_log("Index %ld, token [%.*s]\n", j, tj.len, tj.ptr);

            json_scanf((char *)tj.ptr, tj.len, "%f", &objptr->max[i][j]);
        }
        objptr->max[i][j] = SYS_PARAM_F32_ARR_END_VALUE;
    }
}
int32_t sys_param_its_data_speed_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount               = 0;
    sys_param_its_data_speed_t *objptr = (sys_param_its_data_speed_t *)pvParam;
    //sys_param_log("sys_param_its_data_speed_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_data_speed_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{average:%M,min:%M,max:%M}",
                              /* type:float,  ismultidimarray : True, isarray : True, isstring : False, - json primitive type,   - json bool/char/int/float multidimensional array => average:%M */
                              sys_param_its_data_speed_t_loads_average_array, (void *)objptr,
                              /* type:float,  ismultidimarray : True, isarray : True, isstring : False, - json primitive type,   - json bool/char/int/float multidimensional array => min:%M */
                              sys_param_its_data_speed_t_loads_min_array, (void *)objptr,
                              /* type:float,  ismultidimarray : True, isarray : True, isstring : False, - json primitive type,   - json bool/char/int/float multidimensional array => max:%M */
                              sys_param_its_data_speed_t_loads_max_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_data_event_tidlane_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'tid', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [32], 'm_countlist_last': 32, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_its_data_event_tidlane_t_loads_tid_array(char *str, int len, void *pvParam_local);
void sys_param_its_data_event_tidlane_t_loads_tid_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_data_event_tidlane_t *objptr = (sys_param_its_data_event_tidlane_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_data_event_tidlane_t_loads_tid_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->tid[i]);
    }
    objptr->tid[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'lane', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [32], 'm_countlist_last': 32, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_its_data_event_tidlane_t_loads_lane_array(char *str, int len, void *pvParam_local);
void sys_param_its_data_event_tidlane_t_loads_lane_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_data_event_tidlane_t *objptr = (sys_param_its_data_event_tidlane_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_data_event_tidlane_t_loads_lane_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->lane[i]);
    }
    objptr->lane[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
int32_t sys_param_its_data_event_tidlane_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                       = 0;
    sys_param_its_data_event_tidlane_t *objptr = (sys_param_its_data_event_tidlane_t *)pvParam;
    //sys_param_log("sys_param_its_data_event_tidlane_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_data_event_tidlane_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{tid:%M,lane:%M}",
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => tid:%M */
                              sys_param_its_data_event_tidlane_t_loads_tid_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => lane:%M */
                              sys_param_its_data_event_tidlane_t_loads_lane_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_data_event_tidlane2_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'tid', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [32], 'm_countlist_last': 32, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_its_data_event_tidlane2_t_loads_tid_array(char *str, int len, void *pvParam_local);
void sys_param_its_data_event_tidlane2_t_loads_tid_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_its_data_event_tidlane2_t *objptr = (sys_param_its_data_event_tidlane2_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_its_data_event_tidlane2_t_loads_tid_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->tid[i]);
    }
    objptr->tid[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
int32_t sys_param_its_data_event_tidlane2_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                        = 0;
    sys_param_its_data_event_tidlane2_t *objptr = (sys_param_its_data_event_tidlane2_t *)pvParam;
    //sys_param_log("sys_param_its_data_event_tidlane2_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_data_event_tidlane2_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{tid:%M}",
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => tid:%M */
                              sys_param_its_data_event_tidlane2_t_loads_tid_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_its_data_event_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_data_event_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount               = 0;
    sys_param_its_data_event_t *objptr = (sys_param_its_data_event_t *)pvParam;
    //sys_param_log("sys_param_its_data_event_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_its_data_event_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{abnomal:%M,reverse:%M,speedlimit:%M,cs:%8s,notvehicle:%M}",
                              /* type:sys_param_its_data_event_tidlane_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => abnomal:%M */
                              sys_param_its_data_event_tidlane_t_loads, (void *)&(objptr->abnomal),
                              /* type:sys_param_its_data_event_tidlane_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => reverse:%M */
                              sys_param_its_data_event_tidlane_t_loads, (void *)&(objptr->reverse),
                              /* type:sys_param_its_data_event_tidlane_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => speedlimit:%M */
                              sys_param_its_data_event_tidlane_t_loads, (void *)&(objptr->speedlimit),
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => cs:%8s */
                              objptr->cs,
                              /* type:sys_param_its_data_event_tidlane2_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => notvehicle:%M */
                              sys_param_its_data_event_tidlane2_t_loads, (void *)&(objptr->notvehicle));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_pid8_its_data_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_pid8_its_data_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount              = 0;
    sys_param_pid8_its_data_t *objptr = (sys_param_pid8_its_data_t *)pvParam;
    //sys_param_log("sys_param_pid8_its_data_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_pid8_its_data_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{lane:%M,count:%M,speed:%M,event:%M}",
                              /* type:sys_param_its_data_lane_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => lane:%M */
                              sys_param_its_data_lane_t_loads, (void *)&(objptr->lane),
                              /* type:sys_param_its_data_count_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => count:%M */
                              sys_param_its_data_count_t_loads, (void *)&(objptr->count),
                              /* type:sys_param_its_data_speed_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => speed:%M */
                              sys_param_its_data_speed_t_loads, (void *)&(objptr->speed),
                              /* type:sys_param_its_data_event_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => event:%M */
                              sys_param_its_data_event_t_loads, (void *)&(objptr->event));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_vf_reflector_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_vf_reflector_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                   = 0;
    sys_param_vf_reflector_setup_t *objptr = (sys_param_vf_reflector_setup_t *)pvParam;
    //sys_param_log("sys_param_vf_reflector_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_vf_reflector_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{reflector_type:%32s,reflector_distance:%f,reflector_radius:%f}",
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => reflector_type:%32s */
                              objptr->reflector_type,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => reflector_distance:%f */
                              &objptr->reflector_distance,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => reflector_radius:%f */
                              &objptr->reflector_radius);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid9did0_vf_reflector_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid9did0_vf_reflector_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                             = 0;
    sys_param_sid9did0_vf_reflector_config_t *objptr = (sys_param_sid9did0_vf_reflector_config_t *)pvParam;
    //sys_param_log("sys_param_sid9did0_vf_reflector_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid9did0_vf_reflector_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_vf_reflector_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_vf_reflector_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_vf_server_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_vf_server_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                = 0;
    sys_param_vf_server_setup_t *objptr = (sys_param_vf_server_setup_t *)pvParam;
    //sys_param_log("sys_param_vf_server_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_vf_server_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{server_ip:%32s,server_port:%d,server_access_timeout:%d,server_access_retry_cnt:%d,server_sendstack_size:%d,rs485_access_timeout:%d,rs485_access_retry_cnt:%d}",
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => server_ip:%32s */
                              objptr->server_ip,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => server_port:%d */
                              &objptr->server_port,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => server_access_timeout:%d */
                              &objptr->server_access_timeout,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => server_access_retry_cnt:%d */
                              &objptr->server_access_retry_cnt,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => server_sendstack_size:%d */
                              &objptr->server_sendstack_size,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => rs485_access_timeout:%d */
                              &objptr->rs485_access_timeout,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => rs485_access_retry_cnt:%d */
                              &objptr->rs485_access_retry_cnt);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid9did1_vf_server_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid9did1_vf_server_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                          = 0;
    sys_param_sid9did1_vf_server_config_t *objptr = (sys_param_sid9did1_vf_server_config_t *)pvParam;
    //sys_param_log("sys_param_sid9did1_vf_server_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid9did1_vf_server_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_vf_server_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_vf_server_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_vf_relay_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'relay_enable', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_vf_relay_setup_t_loads_relay_enable_array(char *str, int len, void *pvParam_local);
void sys_param_vf_relay_setup_t_loads_relay_enable_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_vf_relay_setup_t *objptr = (sys_param_vf_relay_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_vf_relay_setup_t_loads_relay_enable_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->relay_enable[i]);
    }
    objptr->relay_enable[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'relay_type', 'type': 'char', 'ismultidimarray': True, 'isarray': True, 'isstring': True, 'm_countlist': [4], 'm_countlist_last': 8, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%8s'} */
void sys_param_vf_relay_setup_t_loads_relay_type_array(char *str, int len, void *pvParam_local);
void sys_param_vf_relay_setup_t_loads_relay_type_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_vf_relay_setup_t *objptr = (sys_param_vf_relay_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_vf_relay_setup_t_loads_relay_type_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        strncpy((char *)&objptr->relay_type[i], ti.ptr, ti.len);
    }
}
/* {'subfunc': True, 'm_name': 'relay_on_time_ms', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_vf_relay_setup_t_loads_relay_on_time_ms_array(char *str, int len, void *pvParam_local);
void sys_param_vf_relay_setup_t_loads_relay_on_time_ms_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_vf_relay_setup_t *objptr = (sys_param_vf_relay_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_vf_relay_setup_t_loads_relay_on_time_ms_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->relay_on_time_ms[i]);
    }
    objptr->relay_on_time_ms[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'relay_on_event_type', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [4], 'm_countlist_last': 4, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_vf_relay_setup_t_loads_relay_on_event_type_array(char *str, int len, void *pvParam_local);
void sys_param_vf_relay_setup_t_loads_relay_on_event_type_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_vf_relay_setup_t *objptr = (sys_param_vf_relay_setup_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_vf_relay_setup_t_loads_relay_on_event_type_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->relay_on_event_type[i]);
    }
    objptr->relay_on_event_type[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
int32_t sys_param_vf_relay_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount               = 0;
    sys_param_vf_relay_setup_t *objptr = (sys_param_vf_relay_setup_t *)pvParam;
    //sys_param_log("sys_param_vf_relay_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_vf_relay_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{relay_cnt:%d,relay_enable:%M,relay_type:%M,relay_on_time_ms:%M,relay_on_event_type:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => relay_cnt:%d */
                              &objptr->relay_cnt,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => relay_enable:%M */
                              sys_param_vf_relay_setup_t_loads_relay_enable_array, (void *)objptr,
                              /* type:char,  ismultidimarray : True, isarray : True, isstring : True, - json primitive type,   - json bool/char/int/float multidimensional array => relay_type:%M */
                              sys_param_vf_relay_setup_t_loads_relay_type_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => relay_on_time_ms:%M */
                              sys_param_vf_relay_setup_t_loads_relay_on_time_ms_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => relay_on_event_type:%M */
                              sys_param_vf_relay_setup_t_loads_relay_on_event_type_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid9did2_vf_relay_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid9did2_vf_relay_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                         = 0;
    sys_param_sid9did2_vf_relay_config_t *objptr = (sys_param_sid9did2_vf_relay_config_t *)pvParam;
    //sys_param_log("sys_param_sid9did2_vf_relay_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid9did2_vf_relay_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_vf_relay_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_vf_relay_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_vf_ui_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_vf_ui_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount            = 0;
    sys_param_vf_ui_setup_t *objptr = (sys_param_vf_ui_setup_t *)pvParam;
    //sys_param_log("sys_param_vf_ui_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_vf_ui_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{th_normal:%f,th_caution:%f,th_warning:%f,marker:%f}",
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => th_normal:%f */
                              &objptr->th_normal,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => th_caution:%f */
                              &objptr->th_caution,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => th_warning:%f */
                              &objptr->th_warning,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => marker:%f */
                              &objptr->marker);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid9did3_vf_ui_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid9did3_vf_ui_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                      = 0;
    sys_param_sid9did3_vf_ui_config_t *objptr = (sys_param_sid9did3_vf_ui_config_t *)pvParam;
    //sys_param_log("sys_param_sid9did3_vf_ui_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid9did3_vf_ui_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_vf_ui_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_vf_ui_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_pid9_vf_data_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
/* {'subfunc': True, 'm_name': 'dat', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [25], 'm_countlist_last': 25, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_pid9_vf_data_t_loads_dat_array(char *str, int len, void *pvParam_local);
void sys_param_pid9_vf_data_t_loads_dat_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_pid9_vf_data_t *objptr = (sys_param_pid9_vf_data_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_pid9_vf_data_t_loads_dat_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->dat[i]);
    }
    objptr->dat[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'std', 'type': 'float', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [25], 'm_countlist_last': 25, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%f'} */
void sys_param_pid9_vf_data_t_loads_std_array(char *str, int len, void *pvParam_local);
void sys_param_pid9_vf_data_t_loads_std_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_pid9_vf_data_t *objptr = (sys_param_pid9_vf_data_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_pid9_vf_data_t_loads_std_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%f", &objptr->std[i]);
    }
    objptr->std[i] = SYS_PARAM_F32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'war', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [25], 'm_countlist_last': 25, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_pid9_vf_data_t_loads_war_array(char *str, int len, void *pvParam_local);
void sys_param_pid9_vf_data_t_loads_war_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_pid9_vf_data_t *objptr = (sys_param_pid9_vf_data_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_pid9_vf_data_t_loads_war_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->war[i]);
    }
    objptr->war[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'det', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [25], 'm_countlist_last': 25, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_pid9_vf_data_t_loads_det_array(char *str, int len, void *pvParam_local);
void sys_param_pid9_vf_data_t_loads_det_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_pid9_vf_data_t *objptr = (sys_param_pid9_vf_data_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_pid9_vf_data_t_loads_det_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->det[i]);
    }
    objptr->det[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
/* {'subfunc': True, 'm_name': 'sw', 'type': 'int', 'ismultidimarray': False, 'isarray': True, 'isstring': False, 'm_countlist': [25], 'm_countlist_last': 25, 'localreq': True, 'localloopvarlist': ['i'], 'localloopvaridx': '[i]', 'subfmt': '%d'} */
void sys_param_pid9_vf_data_t_loads_sw_array(char *str, int len, void *pvParam_local);
void sys_param_pid9_vf_data_t_loads_sw_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    struct json_token ti;
    sys_param_pid9_vf_data_t *objptr = (sys_param_pid9_vf_data_t *)pvParam_local;
    //sys_param_log("Parsing array: %.*s\n", len, str);
    //krs_log("sys_param_pid9_vf_data_t_loads_sw_array len:%d\n\r", len);
    for(i = 0; json_scanf_array_elem(str, len, "", i, &ti) > 0; i++)
    {
        //sys_param_log("Index %ld, token [%.*s]\n", i, ti.len, ti.ptr);

        json_scanf((char *)ti.ptr, ti.len, "%d", &objptr->sw[i]);
    }
    objptr->sw[i] = SYS_PARAM_INT32_ARR_END_VALUE;
}
int32_t sys_param_pid9_vf_data_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount             = 0;
    sys_param_pid9_vf_data_t *objptr = (sys_param_pid9_vf_data_t *)pvParam;
    //sys_param_log("sys_param_pid9_vf_data_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_pid9_vf_data_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{cnt:%d,prd:%f,dat:%M,std:%M,war:%M,det:%M,sw:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => cnt:%d */
                              &objptr->cnt,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => prd:%f */
                              &objptr->prd,
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => dat:%M */
                              sys_param_pid9_vf_data_t_loads_dat_array, (void *)objptr,
                              /* type:float,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => std:%M */
                              sys_param_pid9_vf_data_t_loads_std_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => war:%M */
                              sys_param_pid9_vf_data_t_loads_war_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => det:%M */
                              sys_param_pid9_vf_data_t_loads_det_array, (void *)objptr,
                              /* type:int,  ismultidimarray : False, isarray : True, isstring : False, - json primitive type,   - json bool/int/float array => sw:%M */
                              sys_param_pid9_vf_data_t_loads_sw_array, (void *)objptr);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_fcw_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_fcw_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount          = 0;
    sys_param_fcw_setup_t *objptr = (sys_param_fcw_setup_t *)pvParam;
    //sys_param_log("sys_param_fcw_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_fcw_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{vehicle_type:%d,startup_light_en:%B,startup_light_ontime:%d,alert_led_en:%B,alert_spk_en:%B,alert_ssr_en:%B,alert_ledcolor_caution:%d,alert_ledcolor_warning:%d,alert_ledcolor_normal:%d,alert_blink_period:%d,alert_update_period:%d,alert_blocking_period:%d,vehiclespeed_adj_ratio:%f,ttc_low_sec:%f,ttc_high_sec:%f,ttc_egospeed_low_kph:%f,ttc_egospeed_high_kph:%f,ttc_level1_ratio:%f,ttc_level2_ratio:%f,lane_left_m:%f,lane_right_m:%f,lane_range_m:%f,egospeed_min_kph:%f,oncomming_th_kph:%f}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => vehicle_type:%d */
                              &objptr->vehicle_type,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => startup_light_en:%B */
                              &objptr->startup_light_en,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => startup_light_ontime:%d */
                              &objptr->startup_light_ontime,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => alert_led_en:%B */
                              &objptr->alert_led_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => alert_spk_en:%B */
                              &objptr->alert_spk_en,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => alert_ssr_en:%B */
                              &objptr->alert_ssr_en,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => alert_ledcolor_caution:%d */
                              &objptr->alert_ledcolor_caution,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => alert_ledcolor_warning:%d */
                              &objptr->alert_ledcolor_warning,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => alert_ledcolor_normal:%d */
                              &objptr->alert_ledcolor_normal,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => alert_blink_period:%d */
                              &objptr->alert_blink_period,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => alert_update_period:%d */
                              &objptr->alert_update_period,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => alert_blocking_period:%d */
                              &objptr->alert_blocking_period,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => vehiclespeed_adj_ratio:%f */
                              &objptr->vehiclespeed_adj_ratio,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => ttc_low_sec:%f */
                              &objptr->ttc_low_sec,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => ttc_high_sec:%f */
                              &objptr->ttc_high_sec,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => ttc_egospeed_low_kph:%f */
                              &objptr->ttc_egospeed_low_kph,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => ttc_egospeed_high_kph:%f */
                              &objptr->ttc_egospeed_high_kph,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => ttc_level1_ratio:%f */
                              &objptr->ttc_level1_ratio,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => ttc_level2_ratio:%f */
                              &objptr->ttc_level2_ratio,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => lane_left_m:%f */
                              &objptr->lane_left_m,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => lane_right_m:%f */
                              &objptr->lane_right_m,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => lane_range_m:%f */
                              &objptr->lane_range_m,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => egospeed_min_kph:%f */
                              &objptr->egospeed_min_kph,
                              /* type:float,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => oncomming_th_kph:%f */
                              &objptr->oncomming_th_kph);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid10did0_fcw_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid10did0_fcw_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                     = 0;
    sys_param_sid10did0_fcw_config_t *objptr = (sys_param_sid10did0_fcw_config_t *)pvParam;
    //sys_param_log("sys_param_sid10did0_fcw_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid10did0_fcw_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_fcw_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_fcw_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_fcwtest_setup_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_fcwtest_setup_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount              = 0;
    sys_param_fcwtest_setup_t *objptr = (sys_param_fcwtest_setup_t *)pvParam;
    //sys_param_log("sys_param_fcwtest_setup_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_fcwtest_setup_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{test_fcw_event_level1:%B,test_fcw_event_level2:%B,test_jctbox_led:%B,test_jctbox_spk:%B,test_jctbox_ssr:%B,test_tbd0:%B,test_tbd1:%B,test_tbd2:%B,test_tbd3:%B,test_tbd4:%B}",
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => test_fcw_event_level1:%B */
                              &objptr->test_fcw_event_level1,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => test_fcw_event_level2:%B */
                              &objptr->test_fcw_event_level2,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => test_jctbox_led:%B */
                              &objptr->test_jctbox_led,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => test_jctbox_spk:%B */
                              &objptr->test_jctbox_spk,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => test_jctbox_ssr:%B */
                              &objptr->test_jctbox_ssr,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => test_tbd0:%B */
                              &objptr->test_tbd0,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => test_tbd1:%B */
                              &objptr->test_tbd1,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => test_tbd2:%B */
                              &objptr->test_tbd2,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => test_tbd3:%B */
                              &objptr->test_tbd3,
                              /* type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => test_tbd4:%B */
                              &objptr->test_tbd4);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sid10did1_fcwtest_config_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid10did1_fcwtest_config_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                         = 0;
    sys_param_sid10did1_fcwtest_config_t *objptr = (sys_param_sid10did1_fcwtest_config_t *)pvParam;
    //sys_param_log("sys_param_sid10did1_fcwtest_config_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sid10did1_fcwtest_config_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{sid:%d,did:%d,setup:%M}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => sid:%d */
                              &objptr->sid,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => did:%d */
                              &objptr->did,
                              /* type:sys_param_fcwtest_setup_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => setup:%M */
                              sys_param_fcwtest_setup_t_loads, (void *)&(objptr->setup));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_junctionbox_param_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_junctionbox_param_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                  = 0;
    sys_param_junctionbox_param_t *objptr = (sys_param_junctionbox_param_t *)pvParam;
    //sys_param_log("sys_param_junctionbox_param_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_junctionbox_param_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{r:%d,g:%d,b:%d,spk:%d,ssra:%d,ssrb:%d}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => r:%d */
                              &objptr->r,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => g:%d */
                              &objptr->g,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => b:%d */
                              &objptr->b,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => spk:%d */
                              &objptr->spk,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => ssra:%d */
                              &objptr->ssra,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => ssrb:%d */
                              &objptr->ssrb);
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_junctionbox_ctrl_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_junctionbox_ctrl_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                 = 0;
    sys_param_junctionbox_ctrl_t *objptr = (sys_param_junctionbox_ctrl_t *)pvParam;
    //sys_param_log("sys_param_junctionbox_ctrl_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_junctionbox_ctrl_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{cmd:%32s,param:%M}",
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => cmd:%32s */
                              objptr->cmd,
                              /* type:sys_param_junctionbox_param_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => param:%M */
                              sys_param_junctionbox_param_t_loads, (void *)&(objptr->param));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_system_status_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_system_status_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount              = 0;
    sys_param_system_status_t *objptr = (sys_param_system_status_t *)pvParam;
    //sys_param_log("sys_param_system_status_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_system_status_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{devuid:%32s,serialnumber:%32s,swappname:%32s,swversion:%32s,swdate:%d,swtime:%d,sid0did0_systembase_config:%M,sid0did1_datetime_config:%M,sid0did2_security_config:%M,sid0did4_infra_config:%M,sid0did5_serialnumber_config:%M,sid0did6_location_config:%M,sid0did8_rs485_protocol_config:%M,sid0did10_rsp_eol_config:%M,sid0did11_rsp_install_config:%M,sid0did12_rsm_config:%M,sid0did13_rsptrk_config:%M,sid0did200_app_packet_config:%M,sid8did0_its_config:%M,sid8did1_its_relay_config:%M,sid8did2_its_align_config:%M,sid8did10_its_testmode_config:%M}",
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => devuid:%32s */
                              objptr->devuid,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => serialnumber:%32s */
                              objptr->serialnumber,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => swappname:%32s */
                              objptr->swappname,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => swversion:%32s */
                              objptr->swversion,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => swdate:%d */
                              &objptr->swdate,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => swtime:%d */
                              &objptr->swtime,
                              /* type:sys_param_sid0did0_systembase_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did0_systembase_config:%M */
                              sys_param_sid0did0_systembase_config_t_loads, (void *)&(objptr->sid0did0_systembase_config),
                              /* type:sys_param_sid0did1_datetime_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did1_datetime_config:%M */
                              sys_param_sid0did1_datetime_config_t_loads, (void *)&(objptr->sid0did1_datetime_config),
                              /* type:sys_param_sid0did2_security_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did2_security_config:%M */
                              sys_param_sid0did2_security_config_t_loads, (void *)&(objptr->sid0did2_security_config),
                              /* type:sys_param_sid0did4_infra_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did4_infra_config:%M */
                              sys_param_sid0did4_infra_config_t_loads, (void *)&(objptr->sid0did4_infra_config),
                              /* type:sys_param_sid0did5_serialnumber_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did5_serialnumber_config:%M */
                              sys_param_sid0did5_serialnumber_config_t_loads, (void *)&(objptr->sid0did5_serialnumber_config),
                              /* type:sys_param_sid0did6_location_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did6_location_config:%M */
                              sys_param_sid0did6_location_config_t_loads, (void *)&(objptr->sid0did6_location_config),
                              /* type:sys_param_sid0did8_rs485_protocol_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did8_rs485_protocol_config:%M */
                              sys_param_sid0did8_rs485_protocol_config_t_loads, (void *)&(objptr->sid0did8_rs485_protocol_config),
                              /* type:sys_param_sid0did10_rsp_eol_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did10_rsp_eol_config:%M */
                              sys_param_sid0did10_rsp_eol_config_t_loads, (void *)&(objptr->sid0did10_rsp_eol_config),
                              /* type:sys_param_sid0did11_rsp_install_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did11_rsp_install_config:%M */
                              sys_param_sid0did11_rsp_install_config_t_loads, (void *)&(objptr->sid0did11_rsp_install_config),
                              /* type:sys_param_sid0did12_rsm_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did12_rsm_config:%M */
                              sys_param_sid0did12_rsm_config_t_loads, (void *)&(objptr->sid0did12_rsm_config),
                              /* type:sys_param_sid0did13_rsptrk_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did13_rsptrk_config:%M */
                              sys_param_sid0did13_rsptrk_config_t_loads, (void *)&(objptr->sid0did13_rsptrk_config),
                              /* type:sys_param_sid0did200_app_packet_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did200_app_packet_config:%M */
                              sys_param_sid0did200_app_packet_config_t_loads, (void *)&(objptr->sid0did200_app_packet_config),
                              /* type:sys_param_sid8did0_its_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid8did0_its_config:%M */
                              sys_param_sid8did0_its_config_t_loads, (void *)&(objptr->sid8did0_its_config),
                              /* type:sys_param_sid8did1_its_relay_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid8did1_its_relay_config:%M */
                              sys_param_sid8did1_its_relay_config_t_loads, (void *)&(objptr->sid8did1_its_relay_config),
                              /* type:sys_param_sid8did2_its_align_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid8did2_its_align_config:%M */
                              sys_param_sid8did2_its_align_config_t_loads, (void *)&(objptr->sid8did2_its_align_config),
                              /* type:sys_param_sid8did10_its_testmode_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid8did10_its_testmode_config:%M */
                              sys_param_sid8did10_its_testmode_config_t_loads, (void *)&(objptr->sid8did10_its_testmode_config));
    return convertcount;
}

/******************************************************************************
 * function name : sys_param_sidxdidx_configinfo_packing_t_loads
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sidxdidx_configinfo_packing_t_loads(char *jsonbuffer, int len, void *pvParam)
{
    int32_t convertcount                            = 0;
    sys_param_sidxdidx_configinfo_packing_t *objptr = (sys_param_sidxdidx_configinfo_packing_t *)pvParam;
    //sys_param_log("sys_param_sidxdidx_configinfo_packing_t_loads input json :%.*s\n\r", len, jsonbuffer);
    //krs_log("sys_param_sidxdidx_configinfo_packing_t_loads len:%d\n\r", len);
    sys_param_wdg_clear();
    convertcount = json_scanf(jsonbuffer, len,
                              "{data_start_marker:%d,param_version:%d,guidstr:%36s,sid0did0_systembase_config:%M,sid0did1_datetime_config:%M,sid0did2_security_config:%M,sid0did3_network_config:%M,sid0did4_infra_config:%M,sid0did5_serialnumber_config:%M,sid0did6_location_config:%M,sid0did7_jctbox_config:%M,sid0did8_rs485_protocol_config:%M,sid0did9_camera_config:%M,sid0did10_rsp_eol_config:%M,sid0did11_rsp_install_config:%M,sid0did12_rsm_config:%M,sid0did13_rsptrk_config:%M,sid0did30_rfictx_select_config:%M,sid0did31_rfictx_bgt24at2_config:%M,sid0did40_rficrx_select_config:%M,sid0did41_rficrx_bgt24ar4_config:%M,sid0did50_pll_select_config:%M,sid0did51_pll_lmx2491_config:%M,sid0did60_adc_select_config:%M,sid0did61_adc_adar7251_config:%M,sid0did62_adc_max11043_config:%M,sid0did200_app_packet_config:%M,sid6did0_candrv_config:%M,sid6did1_cansignal_config:%M,sid6did2_cantxmsg_config:%M,sid7did0_filesystem_config:%M,sid8did0_its_config:%M,sid8did1_its_relay_config:%M,sid8did2_its_align_config:%M,sid8did10_its_testmode_config:%M,sid9did0_vf_reflector_config:%M,sid9did1_vf_server_config:%M,sid9did2_vf_relay_config:%M,sid9did3_vf_ui_config:%M,sid10did0_fcw_config:%M,sid10did1_fcwtest_config:%M,data_end_marker:%d,data_end_marker1:%d,data_end_marker2:%d}",
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => data_start_marker:%d */
                              &objptr->data_start_marker,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => param_version:%d */
                              &objptr->param_version,
                              /* type:char,  ismultidimarray : False, isarray : True, isstring : True, - json primitive type,   - json char string => guidstr:%36s */
                              objptr->guidstr,
                              /* type:sys_param_sid0did0_systembase_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did0_systembase_config:%M */
                              sys_param_sid0did0_systembase_config_t_loads, (void *)&(objptr->sid0did0_systembase_config),
                              /* type:sys_param_sid0did1_datetime_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did1_datetime_config:%M */
                              sys_param_sid0did1_datetime_config_t_loads, (void *)&(objptr->sid0did1_datetime_config),
                              /* type:sys_param_sid0did2_security_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did2_security_config:%M */
                              sys_param_sid0did2_security_config_t_loads, (void *)&(objptr->sid0did2_security_config),
                              /* type:sys_param_sid0did3_network_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did3_network_config:%M */
                              sys_param_sid0did3_network_config_t_loads, (void *)&(objptr->sid0did3_network_config),
                              /* type:sys_param_sid0did4_infra_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did4_infra_config:%M */
                              sys_param_sid0did4_infra_config_t_loads, (void *)&(objptr->sid0did4_infra_config),
                              /* type:sys_param_sid0did5_serialnumber_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did5_serialnumber_config:%M */
                              sys_param_sid0did5_serialnumber_config_t_loads, (void *)&(objptr->sid0did5_serialnumber_config),
                              /* type:sys_param_sid0did6_location_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did6_location_config:%M */
                              sys_param_sid0did6_location_config_t_loads, (void *)&(objptr->sid0did6_location_config),
                              /* type:sys_param_sid0did7_jctbox_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did7_jctbox_config:%M */
                              sys_param_sid0did7_jctbox_config_t_loads, (void *)&(objptr->sid0did7_jctbox_config),
                              /* type:sys_param_sid0did8_rs485_protocol_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did8_rs485_protocol_config:%M */
                              sys_param_sid0did8_rs485_protocol_config_t_loads, (void *)&(objptr->sid0did8_rs485_protocol_config),
                              /* type:sys_param_sid0did9_camera_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did9_camera_config:%M */
                              sys_param_sid0did9_camera_config_t_loads, (void *)&(objptr->sid0did9_camera_config),
                              /* type:sys_param_sid0did10_rsp_eol_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did10_rsp_eol_config:%M */
                              sys_param_sid0did10_rsp_eol_config_t_loads, (void *)&(objptr->sid0did10_rsp_eol_config),
                              /* type:sys_param_sid0did11_rsp_install_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did11_rsp_install_config:%M */
                              sys_param_sid0did11_rsp_install_config_t_loads, (void *)&(objptr->sid0did11_rsp_install_config),
                              /* type:sys_param_sid0did12_rsm_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did12_rsm_config:%M */
                              sys_param_sid0did12_rsm_config_t_loads, (void *)&(objptr->sid0did12_rsm_config),
                              /* type:sys_param_sid0did13_rsptrk_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did13_rsptrk_config:%M */
                              sys_param_sid0did13_rsptrk_config_t_loads, (void *)&(objptr->sid0did13_rsptrk_config),
                              /* type:sys_param_sid0did30_rfictx_select_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did30_rfictx_select_config:%M */
                              sys_param_sid0did30_rfictx_select_config_t_loads, (void *)&(objptr->sid0did30_rfictx_select_config),
                              /* type:sys_param_sid0did31_rfictx_bgt24at2_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did31_rfictx_bgt24at2_config:%M */
                              sys_param_sid0did31_rfictx_bgt24at2_config_t_loads, (void *)&(objptr->sid0did31_rfictx_bgt24at2_config),
                              /* type:sys_param_sid0did40_rficrx_select_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did40_rficrx_select_config:%M */
                              sys_param_sid0did40_rficrx_select_config_t_loads, (void *)&(objptr->sid0did40_rficrx_select_config),
                              /* type:sys_param_sid0did41_rficrx_bgt24ar4_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did41_rficrx_bgt24ar4_config:%M */
                              sys_param_sid0did41_rficrx_bgt24ar4_config_t_loads, (void *)&(objptr->sid0did41_rficrx_bgt24ar4_config),
                              /* type:sys_param_sid0did50_pll_select_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did50_pll_select_config:%M */
                              sys_param_sid0did50_pll_select_config_t_loads, (void *)&(objptr->sid0did50_pll_select_config),
                              /* type:sys_param_sid0did51_pll_lmx2491_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did51_pll_lmx2491_config:%M */
                              sys_param_sid0did51_pll_lmx2491_config_t_loads, (void *)&(objptr->sid0did51_pll_lmx2491_config),
                              /* type:sys_param_sid0did60_adc_select_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did60_adc_select_config:%M */
                              sys_param_sid0did60_adc_select_config_t_loads, (void *)&(objptr->sid0did60_adc_select_config),
                              /* type:sys_param_sid0did61_adc_adar7251_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did61_adc_adar7251_config:%M */
                              sys_param_sid0did61_adc_adar7251_config_t_loads, (void *)&(objptr->sid0did61_adc_adar7251_config),
                              /* type:sys_param_sid0did62_adc_max11043_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did62_adc_max11043_config:%M */
                              sys_param_sid0did62_adc_max11043_config_t_loads, (void *)&(objptr->sid0did62_adc_max11043_config),
                              /* type:sys_param_sid0did200_app_packet_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid0did200_app_packet_config:%M */
                              sys_param_sid0did200_app_packet_config_t_loads, (void *)&(objptr->sid0did200_app_packet_config),
                              /* type:sys_param_sid6did0_candrv_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid6did0_candrv_config:%M */
                              sys_param_sid6did0_candrv_config_t_loads, (void *)&(objptr->sid6did0_candrv_config),
                              /* type:sys_param_sid6did1_cansignal_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid6did1_cansignal_config:%M */
                              sys_param_sid6did1_cansignal_config_t_loads, (void *)&(objptr->sid6did1_cansignal_config),
                              /* type:sys_param_sid6did2_cantxmsg_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid6did2_cantxmsg_config:%M */
                              sys_param_sid6did2_cantxmsg_config_t_loads, (void *)&(objptr->sid6did2_cantxmsg_config),
                              /* type:sys_param_sid7did0_filesystem_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid7did0_filesystem_config:%M */
                              sys_param_sid7did0_filesystem_config_t_loads, (void *)&(objptr->sid7did0_filesystem_config),
                              /* type:sys_param_sid8did0_its_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid8did0_its_config:%M */
                              sys_param_sid8did0_its_config_t_loads, (void *)&(objptr->sid8did0_its_config),
                              /* type:sys_param_sid8did1_its_relay_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid8did1_its_relay_config:%M */
                              sys_param_sid8did1_its_relay_config_t_loads, (void *)&(objptr->sid8did1_its_relay_config),
                              /* type:sys_param_sid8did2_its_align_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid8did2_its_align_config:%M */
                              sys_param_sid8did2_its_align_config_t_loads, (void *)&(objptr->sid8did2_its_align_config),
                              /* type:sys_param_sid8did10_its_testmode_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid8did10_its_testmode_config:%M */
                              sys_param_sid8did10_its_testmode_config_t_loads, (void *)&(objptr->sid8did10_its_testmode_config),
                              /* type:sys_param_sid9did0_vf_reflector_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid9did0_vf_reflector_config:%M */
                              sys_param_sid9did0_vf_reflector_config_t_loads, (void *)&(objptr->sid9did0_vf_reflector_config),
                              /* type:sys_param_sid9did1_vf_server_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid9did1_vf_server_config:%M */
                              sys_param_sid9did1_vf_server_config_t_loads, (void *)&(objptr->sid9did1_vf_server_config),
                              /* type:sys_param_sid9did2_vf_relay_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid9did2_vf_relay_config:%M */
                              sys_param_sid9did2_vf_relay_config_t_loads, (void *)&(objptr->sid9did2_vf_relay_config),
                              /* type:sys_param_sid9did3_vf_ui_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid9did3_vf_ui_config:%M */
                              sys_param_sid9did3_vf_ui_config_t_loads, (void *)&(objptr->sid9did3_vf_ui_config),
                              /* type:sys_param_sid10did0_fcw_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid10did0_fcw_config:%M */
                              sys_param_sid10did0_fcw_config_t_loads, (void *)&(objptr->sid10did0_fcw_config),
                              /* type:sys_param_sid10did1_fcwtest_config_t,  ismultidimarray : False, isarray : False, isstring : False, - json object type,   - json object => sid10did1_fcwtest_config:%M */
                              sys_param_sid10did1_fcwtest_config_t_loads, (void *)&(objptr->sid10did1_fcwtest_config),
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => data_end_marker:%d */
                              &objptr->data_end_marker,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => data_end_marker1:%d */
                              &objptr->data_end_marker1,
                              /* type:int,  ismultidimarray : False, isarray : False, isstring : False, - json primitive type,   - json bool/int/float single value => data_end_marker2:%d */
                              &objptr->data_end_marker2);
    return convertcount;
}


/* end of file */
