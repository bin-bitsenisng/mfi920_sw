//*****************************************************************
//  Project Name:  IR24X
//     File Name:  sys_param_jsontype_info.h
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


#ifndef SYS_PARAM_JSONTYPE_INFO_H__
#define SYS_PARAM_JSONTYPE_INFO_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "bts.h"
#include "krs_lib.h"
#include <string.h>

#include "sys_param.h"
#include "sys_param_jsontype.h"
#include "sys_param_jsontype_gen.h"

#include "sys_param_jsontype_dump.h"
#include "sys_param_jsontype_load.h"


    typedef int32_t (*sys_param_jsontype_dumpfunc_t)(char *objname, char *buff, void *pvParam);
    typedef int32_t (*sys_param_jsontype_loadfunc_t)(char *jsonbuffer, int len, void *pvParam);


    typedef enum
    {
        sys_param_id_comm_negative_response_t,           /* id for sys_param_comm_negative_response_t */
        sys_param_id_common_comm_ethernet_config_t,      /* id for sys_param_common_comm_ethernet_config_t */
        sys_param_id_common_comm_serialcomm_config_t,    /* id for sys_param_common_comm_serialcomm_config_t */
        sys_param_id_common_comm_tbd_config_t,           /* id for sys_param_common_comm_tbd_config_t */
        sys_param_id_swupdate_config_t,                  /* id for sys_param_swupdate_config_t */
        sys_param_id_consolelog_config_t,                /* id for sys_param_consolelog_config_t */
        sys_param_id_consoleudp_config_t,                /* id for sys_param_consoleudp_config_t */
        sys_param_id_system_sensortype_config_t,         /* id for sys_param_system_sensortype_config_t */
        sys_param_id_system_control_t,                   /* id for sys_param_system_control_t */
        sys_param_id_logic_control_config_t,             /* id for sys_param_logic_control_config_t */
        sys_param_id_system_config_t,                    /* id for sys_param_system_config_t */
        sys_param_id_sid0did0_systembase_config_t,       /* id for sys_param_sid0did0_systembase_config_t */
        sys_param_id_datetime_setup_t,                   /* id for sys_param_datetime_setup_t */
        sys_param_id_sid0did1_datetime_config_t,         /* id for sys_param_sid0did1_datetime_config_t */
        sys_param_id_security_setup_t,                   /* id for sys_param_security_setup_t */
        sys_param_id_sid0did2_security_config_t,         /* id for sys_param_sid0did2_security_config_t */
        sys_param_id_sid0did3_network_config_t,          /* id for sys_param_sid0did3_network_config_t */
        sys_param_id_version_t,                          /* id for sys_param_version_t */
        sys_param_id_version_setup_t,                    /* id for sys_param_version_setup_t */
        sys_param_id_infra_setup_t,                      /* id for sys_param_infra_setup_t */
        sys_param_id_sid0did4_infra_config_t,            /* id for sys_param_sid0did4_infra_config_t */
        sys_param_id_serialnumber_setup_t,               /* id for sys_param_serialnumber_setup_t */
        sys_param_id_sid0did5_serialnumber_config_t,     /* id for sys_param_sid0did5_serialnumber_config_t */
        sys_param_id_location_t,                         /* id for sys_param_location_t */
        sys_param_id_gps_t,                              /* id for sys_param_gps_t */
        sys_param_id_location_setup_t,                   /* id for sys_param_location_setup_t */
        sys_param_id_sid0did6_location_config_t,         /* id for sys_param_sid0did6_location_config_t */
        sys_param_id_jctbox_setup_t,                     /* id for sys_param_jctbox_setup_t */
        sys_param_id_sid0did7_jctbox_config_t,           /* id for sys_param_sid0did7_jctbox_config_t */
        sys_param_id_rs485_protocol_setup_t,             /* id for sys_param_rs485_protocol_setup_t */
        sys_param_id_sid0did8_rs485_protocol_config_t,   /* id for sys_param_sid0did8_rs485_protocol_config_t */
        sys_param_id_cameractrl_setup_t,                 /* id for sys_param_cameractrl_setup_t */
        sys_param_id_camera_setup_t,                     /* id for sys_param_camera_setup_t */
        sys_param_id_sid0did9_camera_config_t,           /* id for sys_param_sid0did9_camera_config_t */
        sys_param_id_rsp_eol_phasecal_t,                 /* id for sys_param_rsp_eol_phasecal_t */
        sys_param_id_rsp_eol_setup_t,                    /* id for sys_param_rsp_eol_setup_t */
        sys_param_id_sid0did10_rsp_eol_config_t,         /* id for sys_param_sid0did10_rsp_eol_config_t */
        sys_param_id_rsp_install_setup_t,                /* id for sys_param_rsp_install_setup_t */
        sys_param_id_sid0did11_rsp_install_config_t,     /* id for sys_param_sid0did11_rsp_install_config_t */
        sys_param_id_rsm_setup_t,                        /* id for sys_param_rsm_setup_t */
        sys_param_id_sid0did12_rsm_config_t,             /* id for sys_param_sid0did12_rsm_config_t */
        sys_param_id_rsptrk_posttune_t,                  /* id for sys_param_rsptrk_posttune_t */
        sys_param_id_rsptrk_trktune_t,                   /* id for sys_param_rsptrk_trktune_t */
        sys_param_id_rsptrk_setup_t,                     /* id for sys_param_rsptrk_setup_t */
        sys_param_id_sid0did13_rsptrk_config_t,          /* id for sys_param_sid0did13_rsptrk_config_t */
        sys_param_id_rfictx_select_t,                    /* id for sys_param_rfictx_select_t */
        sys_param_id_sid0did30_rfictx_select_config_t,   /* id for sys_param_sid0did30_rfictx_select_config_t */
        sys_param_id_rfictx_bgt24at2_setup_t,            /* id for sys_param_rfictx_bgt24at2_setup_t */
        sys_param_id_sid0did31_rfictx_bgt24at2_config_t, /* id for sys_param_sid0did31_rfictx_bgt24at2_config_t */
        sys_param_id_rficrx_select_t,                    /* id for sys_param_rficrx_select_t */
        sys_param_id_sid0did40_rficrx_select_config_t,   /* id for sys_param_sid0did40_rficrx_select_config_t */
        sys_param_id_rficrx_bgt24ar4_setup_t,            /* id for sys_param_rficrx_bgt24ar4_setup_t */
        sys_param_id_sid0did41_rficrx_bgt24ar4_config_t, /* id for sys_param_sid0did41_rficrx_bgt24ar4_config_t */
        sys_param_id_pll_select_t,                       /* id for sys_param_pll_select_t */
        sys_param_id_sid0did50_pll_select_config_t,      /* id for sys_param_sid0did50_pll_select_config_t */
        sys_param_id_pll_lmx2491_setup_t,                /* id for sys_param_pll_lmx2491_setup_t */
        sys_param_id_sid0did51_pll_lmx2491_config_t,     /* id for sys_param_sid0did51_pll_lmx2491_config_t */
        sys_param_id_adc_select_t,                       /* id for sys_param_adc_select_t */
        sys_param_id_sid0did60_adc_select_config_t,      /* id for sys_param_sid0did60_adc_select_config_t */
        sys_param_id_adc_adar7251_setup_t,               /* id for sys_param_adc_adar7251_setup_t */
        sys_param_id_sid0did61_adc_adar7251_config_t,    /* id for sys_param_sid0did61_adc_adar7251_config_t */
        sys_param_id_adc_max11043_setup_t,               /* id for sys_param_adc_max11043_setup_t */
        sys_param_id_sid0did62_adc_max11043_config_t,    /* id for sys_param_sid0did62_adc_max11043_config_t */
        sys_param_id_app_packet_t,                       /* id for sys_param_app_packet_t */
        sys_param_id_app_packet_setup_t,                 /* id for sys_param_app_packet_setup_t */
        sys_param_id_sid0did200_app_packet_config_t,     /* id for sys_param_sid0did200_app_packet_config_t */
        sys_param_id_candrv_channel_setup_t,             /* id for sys_param_candrv_channel_setup_t */
        sys_param_id_candrv_setup_t,                     /* id for sys_param_candrv_setup_t */
        sys_param_id_sid6did0_candrv_config_t,           /* id for sys_param_sid6did0_candrv_config_t */
        sys_param_id_cansignal_t,                        /* id for sys_param_cansignal_t */
        sys_param_id_cansignal_setup_t,                  /* id for sys_param_cansignal_setup_t */
        sys_param_id_sid6did1_cansignal_config_t,        /* id for sys_param_sid6did1_cansignal_config_t */
        sys_param_id_can_txmsg_t,                        /* id for sys_param_can_txmsg_t */
        sys_param_id_cantxmsg_setup_t,                   /* id for sys_param_cantxmsg_setup_t */
        sys_param_id_sid6did2_cantxmsg_config_t,         /* id for sys_param_sid6did2_cantxmsg_config_t */
        sys_param_id_filesystem_setup_t,                 /* id for sys_param_filesystem_setup_t */
        sys_param_id_sid7did0_filesystem_config_t,       /* id for sys_param_sid7did0_filesystem_config_t */
        sys_param_id_status_timestamp_t,                 /* id for sys_param_status_timestamp_t */
        sys_param_id_status_data_position_t,             /* id for sys_param_status_data_position_t */
        sys_param_id_status_data_ecuinfo_t,              /* id for sys_param_status_data_ecuinfo_t */
        sys_param_id_status_data_gps_t,                  /* id for sys_param_status_data_gps_t */
        sys_param_id_pid0_status_data_t,                 /* id for sys_param_pid0_status_data_t */
        sys_param_id_its_setup_timeschedule_t,           /* id for sys_param_its_setup_timeschedule_t */
        sys_param_id_its_setup_laneinfo_lane_t,          /* id for sys_param_its_setup_laneinfo_lane_t */
        sys_param_id_its_setup_zone_t,                   /* id for sys_param_its_setup_zone_t */
        sys_param_id_its_setup_hotspotzone_t,            /* id for sys_param_its_setup_hotspotzone_t */
        sys_param_id_its_setup_laneinfo_t,               /* id for sys_param_its_setup_laneinfo_t */
        sys_param_id_its_setup_area_t,                   /* id for sys_param_its_setup_area_t */
        sys_param_id_its_setup_blackout_t,               /* id for sys_param_its_setup_blackout_t */
        sys_param_id_its_setup_speedlimit_t,             /* id for sys_param_its_setup_speedlimit_t */
        sys_param_id_its_setup_misc_t,                   /* id for sys_param_its_setup_misc_t */
        sys_param_id_its_setup_t,                        /* id for sys_param_its_setup_t */
        sys_param_id_sid8did0_its_config_t,              /* id for sys_param_sid8did0_its_config_t */
        sys_param_id_its_relay_t,                        /* id for sys_param_its_relay_t */
        sys_param_id_its_device_setup_t,                 /* id for sys_param_its_device_setup_t */
        sys_param_id_sid8did1_its_relay_config_t,        /* id for sys_param_sid8did1_its_relay_config_t */
        sys_param_id_its_alignment_setup_t,              /* id for sys_param_its_alignment_setup_t */
        sys_param_id_sid8did2_its_align_config_t,        /* id for sys_param_sid8did2_its_align_config_t */
        sys_param_id_its_testmode_speedlimit_t,          /* id for sys_param_its_testmode_speedlimit_t */
        sys_param_id_its_testmode_trigger_t,             /* id for sys_param_its_testmode_trigger_t */
        sys_param_id_its_testmode_hotspotzone_t,         /* id for sys_param_its_testmode_hotspotzone_t */
        sys_param_id_its_testmode_image_t,               /* id for sys_param_its_testmode_image_t */
        sys_param_id_its_testmode_misc_t,                /* id for sys_param_its_testmode_misc_t */
        sys_param_id_its_testmode_setup_t,               /* id for sys_param_its_testmode_setup_t */
        sys_param_id_sid8did10_its_testmode_config_t,    /* id for sys_param_sid8did10_its_testmode_config_t */
        sys_param_id_its_data_lane_t,                    /* id for sys_param_its_data_lane_t */
        sys_param_id_its_data_count_t,                   /* id for sys_param_its_data_count_t */
        sys_param_id_its_data_speed_t,                   /* id for sys_param_its_data_speed_t */
        sys_param_id_its_data_event_tidlane_t,           /* id for sys_param_its_data_event_tidlane_t */
        sys_param_id_its_data_event_tidlane2_t,          /* id for sys_param_its_data_event_tidlane2_t */
        sys_param_id_its_data_event_t,                   /* id for sys_param_its_data_event_t */
        sys_param_id_pid8_its_data_t,                    /* id for sys_param_pid8_its_data_t */
        sys_param_id_vf_reflector_setup_t,               /* id for sys_param_vf_reflector_setup_t */
        sys_param_id_sid9did0_vf_reflector_config_t,     /* id for sys_param_sid9did0_vf_reflector_config_t */
        sys_param_id_vf_server_setup_t,                  /* id for sys_param_vf_server_setup_t */
        sys_param_id_sid9did1_vf_server_config_t,        /* id for sys_param_sid9did1_vf_server_config_t */
        sys_param_id_vf_relay_setup_t,                   /* id for sys_param_vf_relay_setup_t */
        sys_param_id_sid9did2_vf_relay_config_t,         /* id for sys_param_sid9did2_vf_relay_config_t */
        sys_param_id_vf_ui_setup_t,                      /* id for sys_param_vf_ui_setup_t */
        sys_param_id_sid9did3_vf_ui_config_t,            /* id for sys_param_sid9did3_vf_ui_config_t */
        sys_param_id_pid9_vf_data_t,                     /* id for sys_param_pid9_vf_data_t */
        sys_param_id_fcw_setup_t,                        /* id for sys_param_fcw_setup_t */
        sys_param_id_sid10did0_fcw_config_t,             /* id for sys_param_sid10did0_fcw_config_t */
        sys_param_id_fcwtest_setup_t,                    /* id for sys_param_fcwtest_setup_t */
        sys_param_id_sid10did1_fcwtest_config_t,         /* id for sys_param_sid10did1_fcwtest_config_t */
        sys_param_id_junctionbox_param_t,                /* id for sys_param_junctionbox_param_t */
        sys_param_id_junctionbox_ctrl_t,                 /* id for sys_param_junctionbox_ctrl_t */
        sys_param_id_system_status_t,                    /* id for sys_param_system_status_t */
        sys_param_id_sidxdidx_configinfo_packing_t,      /* id for sys_param_sidxdidx_configinfo_packing_t */
    } sys_param_id_t;


    typedef struct
    {
        sys_param_id_t id;
        int16_t sid;
        int16_t did;
        int16_t pid;
        char *type_name;
        int32_t type_name_len;
        uint32_t typename_hash;
        sys_param_jsontype_dumpfunc_t dumpfunc;
        sys_param_jsontype_loadfunc_t loadfunc;
        void *pvParam;
        void *pvParamDefault;
        int32_t size;
    } sys_param_jsontype_info_t;

#define SYS_PARAM_JSONTYPE_INFO_TABLE_MAX (sizeof(sys_param_jsontype_info_table) / sizeof(sys_param_jsontype_info_t))


    /*************************************************************/
    /* load json string for internal  */
    /*************************************************************/


    /*************************************************************/
    /* load data from json string for external                   */
    /*************************************************************/
    extern const char_t sys_param_guid[40];
    extern const sys_param_jsontype_info_t sys_param_jsontype_info_table[];
    extern sys_param_jsontype_info_t *sys_param_jsontype_info_find(int16_t sid, int16_t did, int16_t pid);


#ifdef __cplusplus
}
#endif


#endif // SYS_PARAM_JSONTYPE_INFO_H__