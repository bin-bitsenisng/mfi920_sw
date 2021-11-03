//*****************************************************************
//  Project Name:  IR24X
//     File Name:  sys_param_jsontype_load.h
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


#ifndef SYS_PARAM_JSONTYPE_LOAD_H__
#define SYS_PARAM_JSONTYPE_LOAD_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "bts.h"
#include "krs_lib.h"
#include <string.h>

#include "sys_param.h"
#include "sys_param_jsontype.h"


    /*************************************************************/
    /* load json string for internal  */
    /*************************************************************/
    extern int32_t sys_param_comm_negative_response_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_common_comm_ethernet_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_common_comm_serialcomm_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_common_comm_tbd_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_swupdate_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_consolelog_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_consoleudp_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_system_sensortype_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_system_control_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_logic_control_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_system_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did0_systembase_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_datetime_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did1_datetime_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_security_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did2_security_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did3_network_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_version_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_version_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_infra_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did4_infra_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_serialnumber_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did5_serialnumber_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_location_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_gps_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_location_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did6_location_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_jctbox_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did7_jctbox_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_rs485_protocol_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did8_rs485_protocol_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_cameractrl_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_camera_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did9_camera_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_rsp_eol_phasecal_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_rsp_eol_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did10_rsp_eol_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_rsp_install_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did11_rsp_install_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_rsm_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did12_rsm_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_rsptrk_posttune_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_rsptrk_trktune_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_rsptrk_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did13_rsptrk_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_rfictx_select_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did30_rfictx_select_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_rfictx_bgt24at2_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did31_rfictx_bgt24at2_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_rficrx_select_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did40_rficrx_select_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_rficrx_bgt24ar4_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did41_rficrx_bgt24ar4_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_pll_select_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did50_pll_select_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_pll_lmx2491_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did51_pll_lmx2491_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_adc_select_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did60_adc_select_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_adc_adar7251_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did61_adc_adar7251_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_adc_max11043_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did62_adc_max11043_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_app_packet_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_app_packet_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid0did200_app_packet_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_candrv_channel_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_candrv_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid6did0_candrv_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_cansignal_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_cansignal_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid6did1_cansignal_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_can_txmsg_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_cantxmsg_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid6did2_cantxmsg_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_filesystem_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid7did0_filesystem_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_status_timestamp_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_status_data_position_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_status_data_ecuinfo_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_status_data_gps_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_pid0_status_data_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_setup_timeschedule_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_setup_laneinfo_lane_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_setup_zone_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_setup_hotspotzone_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_setup_laneinfo_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_setup_area_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_setup_blackout_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_setup_speedlimit_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_setup_misc_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid8did0_its_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_relay_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_device_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid8did1_its_relay_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_alignment_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid8did2_its_align_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_testmode_speedlimit_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_testmode_trigger_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_testmode_hotspotzone_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_testmode_image_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_testmode_misc_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_testmode_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid8did10_its_testmode_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_data_lane_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_data_count_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_data_speed_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_data_event_tidlane_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_data_event_tidlane2_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_its_data_event_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_pid8_its_data_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_vf_reflector_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid9did0_vf_reflector_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_vf_server_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid9did1_vf_server_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_vf_relay_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid9did2_vf_relay_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_vf_ui_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid9did3_vf_ui_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_pid9_vf_data_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_fcw_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid10did0_fcw_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_fcwtest_setup_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sid10did1_fcwtest_config_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_junctionbox_param_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_junctionbox_ctrl_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_system_status_t_loads(char *jsonbuffer, int len, void *pvParam);
    extern int32_t sys_param_sidxdidx_configinfo_packing_t_loads(char *jsonbuffer, int len, void *pvParam);


#ifdef __cplusplus
}
#endif


#endif // SYS_PARAM_JSONTYPE_LOAD_H__