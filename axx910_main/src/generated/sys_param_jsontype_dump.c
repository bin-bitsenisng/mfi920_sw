//*****************************************************************
//  Project Name:  IR24X
//     File Name:  sys_param_jsontype_dump.c
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

#include "sys_param_jsontype_dump.h"
#include "sys_param_jsontype_gen.h"


/*************************************************************/
/* dump json string for internal prototype */
/*************************************************************/
static int32_t sys_param_comm_negative_response_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_common_comm_ethernet_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_common_comm_serialcomm_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_common_comm_tbd_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_swupdate_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_consolelog_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_consoleudp_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_system_sensortype_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_system_control_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_logic_control_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_system_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did0_systembase_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_datetime_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did1_datetime_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_security_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did2_security_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did3_network_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_version_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_version_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_infra_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did4_infra_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_serialnumber_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did5_serialnumber_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_location_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_gps_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_location_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did6_location_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_jctbox_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did7_jctbox_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_rs485_protocol_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did8_rs485_protocol_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_cameractrl_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_camera_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did9_camera_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_rsp_eol_phasecal_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_rsp_eol_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did10_rsp_eol_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_rsp_install_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did11_rsp_install_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_rsm_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did12_rsm_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_rsptrk_posttune_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_rsptrk_trktune_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_rsptrk_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did13_rsptrk_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_rfictx_select_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did30_rfictx_select_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_rfictx_bgt24at2_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did31_rfictx_bgt24at2_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_rficrx_select_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did40_rficrx_select_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_rficrx_bgt24ar4_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did41_rficrx_bgt24ar4_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_pll_select_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did50_pll_select_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_pll_lmx2491_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did51_pll_lmx2491_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_adc_select_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did60_adc_select_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_adc_adar7251_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did61_adc_adar7251_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_adc_max11043_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did62_adc_max11043_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_app_packet_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_app_packet_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid0did200_app_packet_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_candrv_channel_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_candrv_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid6did0_candrv_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_cansignal_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_cansignal_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid6did1_cansignal_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_can_txmsg_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_cantxmsg_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid6did2_cantxmsg_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_filesystem_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid7did0_filesystem_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_status_timestamp_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_status_data_position_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_status_data_ecuinfo_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_status_data_gps_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_pid0_status_data_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_setup_timeschedule_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_setup_laneinfo_lane_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_setup_zone_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_setup_hotspotzone_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_setup_laneinfo_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_setup_area_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_setup_blackout_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_setup_speedlimit_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_setup_misc_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid8did0_its_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_relay_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_device_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid8did1_its_relay_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_alignment_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid8did2_its_align_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_testmode_speedlimit_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_testmode_trigger_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_testmode_hotspotzone_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_testmode_image_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_testmode_misc_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_testmode_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid8did10_its_testmode_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_data_lane_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_data_count_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_data_speed_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_data_event_tidlane_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_data_event_tidlane2_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_its_data_event_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_pid8_its_data_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_vf_reflector_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid9did0_vf_reflector_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_vf_server_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid9did1_vf_server_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_vf_relay_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid9did2_vf_relay_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_vf_ui_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid9did3_vf_ui_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_pid9_vf_data_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_fcw_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid10did0_fcw_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_fcwtest_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sid10did1_fcwtest_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_junctionbox_param_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_junctionbox_ctrl_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_system_status_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);
static int32_t sys_param_sidxdidx_configinfo_packing_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam);


/*************************************************************/
/* dump json string for internal  */
/*************************************************************/
/******************************************************************************
 * function name : sys_param_comm_negative_response_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_comm_negative_response_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                = JWRITE_OK;
    sys_param_comm_negative_response_t *objptr = (sys_param_comm_negative_response_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[256]
    jwObj_string(jwc, "error", objptr->error);


    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_comm_negative_response_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_common_comm_ethernet_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_common_comm_ethernet_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                     = JWRITE_OK;
    sys_param_common_comm_ethernet_config_t *objptr = (sys_param_common_comm_ethernet_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "ip", objptr->ip);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "nm", objptr->nm);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "gw", objptr->gw);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "mac", objptr->mac);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "dns", objptr->dns);

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "linkspeed", objptr->linkspeed);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "dhcp_en", objptr->dhcp_en);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_common_comm_ethernet_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_common_comm_serialcomm_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_common_comm_serialcomm_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                       = JWRITE_OK;
    sys_param_common_comm_serialcomm_config_t *objptr = (sys_param_common_comm_serialcomm_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "type", objptr->type);

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "baudrate", objptr->baudrate);
    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "flowcontrol", objptr->flowcontrol);

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "data", objptr->data);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "stopbit", objptr->stopbit);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_common_comm_serialcomm_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_common_comm_tbd_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_common_comm_tbd_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                = JWRITE_OK;
    sys_param_common_comm_tbd_config_t *objptr = (sys_param_common_comm_tbd_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "type", objptr->type);


    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_common_comm_tbd_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_swupdate_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_swupdate_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                         = JWRITE_OK;
    sys_param_swupdate_config_t *objptr = (sys_param_swupdate_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "swupdate_request", objptr->swupdate_request);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "swupdate_type", objptr->swupdate_type);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "swupdate_count", objptr->swupdate_count);
    //type:double,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_double(jwc, "swupdate_timestamp", objptr->swupdate_timestamp);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_swupdate_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_consolelog_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_consolelog_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                           = JWRITE_OK;
    sys_param_consolelog_config_t *objptr = (sys_param_consolelog_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "bts_log_level", objptr->bts_log_level);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "bts_log_opt_type_en", objptr->bts_log_opt_type_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "bts_log_opt_time_en", objptr->bts_log_opt_time_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "bts_log_opt_difftime_en", objptr->bts_log_opt_difftime_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "bts_log_opt_file_en", objptr->bts_log_opt_file_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "bts_log_opt_line_en", objptr->bts_log_opt_line_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "bts_log_opt_function_en", objptr->bts_log_opt_function_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "bts_log_module_comm_packet_en", objptr->bts_log_module_comm_packet_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "bts_log_module_comm_appl_callback_en", objptr->bts_log_module_comm_appl_callback_en);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "bts_log_array_frontlen", objptr->bts_log_array_frontlen);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "bts_log_array_backlen", objptr->bts_log_array_backlen);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "bts_log_cpu_usage", objptr->bts_log_cpu_usage);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "bts_log_opt_datetime_en", objptr->bts_log_opt_datetime_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "bts_log_opt_datetime_ms_en", objptr->bts_log_opt_datetime_ms_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "bts_log_opt_datetime_us_en", objptr->bts_log_opt_datetime_us_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "bts_log_opt_gps_en", objptr->bts_log_opt_gps_en);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_consolelog_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_consoleudp_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_consoleudp_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                           = JWRITE_OK;
    sys_param_consoleudp_config_t *objptr = (sys_param_consoleudp_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "en", objptr->en);
    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "ip", objptr->ip);

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "port", objptr->port);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_consoleudp_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_system_sensortype_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_system_sensortype_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                  = JWRITE_OK;
    sys_param_system_sensortype_config_t *objptr = (sys_param_system_sensortype_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "type", objptr->type);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "serialnumber", objptr->serialnumber);

    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "opmode_its_en", objptr->opmode_its_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "opmode_vf_en", objptr->opmode_vf_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "opmode_fcw_en", objptr->opmode_fcw_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "opmode_lm_en", objptr->opmode_lm_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_status_en", objptr->pid_status_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_object_en", objptr->pid_object_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_track_en", objptr->pid_track_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_image_en", objptr->pid_image_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_imagsp_en", objptr->pid_imagsp_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_logger_en", objptr->pid_logger_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_canlog_en", objptr->pid_canlog_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_sensor_en", objptr->pid_sensor_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_app_its_en", objptr->pid_app_its_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_app_vf_en", objptr->pid_app_vf_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_app_fcw_en", objptr->pid_app_fcw_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_app_lm_en", objptr->pid_app_lm_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "raw_chirp_en", objptr->raw_chirp_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "raw_chirp0_en", objptr->raw_chirp0_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "raw_chirp1_en", objptr->raw_chirp1_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "raw_chirp2_en", objptr->raw_chirp2_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "raw_chirp3_en", objptr->raw_chirp3_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "raw_app_en", objptr->raw_app_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "raw_app_its_en", objptr->raw_app_its_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "raw_app_vf_en", objptr->raw_app_vf_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "raw_app_fcw_en", objptr->raw_app_fcw_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "raw_app_lm_en", objptr->raw_app_lm_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "raw_app_install_en", objptr->raw_app_install_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "raw_app_flog_en", objptr->raw_app_flog_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "raw_mon_en", objptr->raw_mon_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "raw_mon_power_en", objptr->raw_mon_power_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "raw_mon_time_en", objptr->raw_mon_time_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "raw_mon_task_en", objptr->raw_mon_task_en);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_system_sensortype_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_system_control_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_system_control_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                        = JWRITE_OK;
    sys_param_system_control_t *objptr = (sys_param_system_control_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "restart_en", objptr->restart_en);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "restart_timeout_s", objptr->restart_timeout_s);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_system_control_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_logic_control_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_logic_control_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                              = JWRITE_OK;
    sys_param_logic_control_config_t *objptr = (sys_param_logic_control_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "logic_start_scan_offset", objptr->logic_start_scan_offset);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_logic_control_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_system_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_system_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                       = JWRITE_OK;
    sys_param_system_config_t *objptr = (sys_param_system_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:sys_param_swupdate_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_swupdate_config_t_dumps(jwc, "swupdate", &objptr->swupdate);
    //type:sys_param_consolelog_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_consolelog_config_t_dumps(jwc, "consolelog", &objptr->consolelog);
    //type:sys_param_consoleudp_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_consoleudp_config_t_dumps(jwc, "consoleudp", &objptr->consoleudp);
    //type:sys_param_system_sensortype_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_system_sensortype_config_t_dumps(jwc, "sensortype", &objptr->sensortype);
    //type:sys_param_common_comm_ethernet_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_common_comm_ethernet_config_t_dumps(jwc, "eth_default", &objptr->eth_default);
    //type:sys_param_system_control_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_system_control_t_dumps(jwc, "syscontrol", &objptr->syscontrol);
    //type:sys_param_logic_control_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_logic_control_config_t_dumps(jwc, "logiccontrol", &objptr->logiccontrol);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_system_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did0_systembase_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did0_systembase_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                    = JWRITE_OK;
    sys_param_sid0did0_systembase_config_t *objptr = (sys_param_sid0did0_systembase_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_system_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_system_config_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did0_systembase_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_datetime_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_datetime_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                        = JWRITE_OK;
    sys_param_datetime_setup_t *objptr = (sys_param_datetime_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "type", objptr->type);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[8]
    jwObj_string(jwc, "unit", objptr->unit);

    //type:double,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_double(jwc, "timestamp", objptr->timestamp);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "gps_update_en", objptr->gps_update_en);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_datetime_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did1_datetime_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did1_datetime_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                  = JWRITE_OK;
    sys_param_sid0did1_datetime_config_t *objptr = (sys_param_sid0did1_datetime_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_datetime_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_datetime_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did1_datetime_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_security_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_security_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                        = JWRITE_OK;
    sys_param_security_setup_t *objptr = (sys_param_security_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "lock_en", objptr->lock_en);
    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "admin_password", objptr->admin_password);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "user_password", objptr->user_password);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "type", objptr->type);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "latitude", objptr->latitude);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "longitude", objptr->longitude);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "direction", objptr->direction);


    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_security_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did2_security_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did2_security_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                  = JWRITE_OK;
    sys_param_sid0did2_security_config_t *objptr = (sys_param_sid0did2_security_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_security_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_security_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did2_security_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did3_network_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did3_network_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                 = JWRITE_OK;
    sys_param_sid0did3_network_config_t *objptr = (sys_param_sid0did3_network_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_common_comm_ethernet_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_common_comm_ethernet_config_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did3_network_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_version_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_version_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                 = JWRITE_OK;
    sys_param_version_t *objptr = (sys_param_version_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "ver", objptr->ver);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "date", objptr->date);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "spec", objptr->spec);


    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_version_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_version_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_version_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                       = JWRITE_OK;
    sys_param_version_setup_t *objptr = (sys_param_version_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:sys_param_version_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_version_t_dumps(jwc, "sys", &objptr->sys);
    //type:sys_param_version_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_version_t_dumps(jwc, "sw", &objptr->sw);
    //type:sys_param_version_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_version_t_dumps(jwc, "be", &objptr->be);
    //type:sys_param_version_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_version_t_dumps(jwc, "fe", &objptr->fe);
    //type:sys_param_version_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_version_t_dumps(jwc, "housing", &objptr->housing);
    //type:sys_param_version_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_version_t_dumps(jwc, "cable", &objptr->cable);
    //type:sys_param_version_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_version_t_dumps(jwc, "protocol", &objptr->protocol);
    //type:sys_param_version_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_version_t_dumps(jwc, "customer", &objptr->customer);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_version_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_infra_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_infra_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                     = JWRITE_OK;
    sys_param_infra_setup_t *objptr = (sys_param_infra_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "infraid", objptr->infraid);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "radarid", objptr->radarid);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "locationid", objptr->locationid);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "basestationid", objptr->basestationid);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "switchid", objptr->switchid);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "desc", objptr->desc);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "desc1", objptr->desc1);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "desc2", objptr->desc2);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "longitude", objptr->longitude);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "latitude", objptr->latitude);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "direction", objptr->direction);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "height", objptr->height);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "roadid", objptr->roadid);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "roadid1", objptr->roadid1);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "roadid2", objptr->roadid2);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "area", objptr->area);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "area1", objptr->area1);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "range", objptr->range);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "range1", objptr->range1);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "lane", objptr->lane);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "lane1", objptr->lane1);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "lane2", objptr->lane2);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "lane3", objptr->lane3);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "lane4", objptr->lane4);


    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_infra_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did4_infra_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did4_infra_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                               = JWRITE_OK;
    sys_param_sid0did4_infra_config_t *objptr = (sys_param_sid0did4_infra_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_infra_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_infra_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did4_infra_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_serialnumber_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_serialnumber_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                            = JWRITE_OK;
    sys_param_serialnumber_setup_t *objptr = (sys_param_serialnumber_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "sys", objptr->sys);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "be", objptr->be);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "fe", objptr->fe);


    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_serialnumber_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did5_serialnumber_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did5_serialnumber_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                      = JWRITE_OK;
    sys_param_sid0did5_serialnumber_config_t *objptr = (sys_param_sid0did5_serialnumber_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_serialnumber_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_serialnumber_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did5_serialnumber_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_location_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_location_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                  = JWRITE_OK;
    sys_param_location_t *objptr = (sys_param_location_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "type", objptr->type);

    //type:double,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_double(jwc, "latitude", objptr->latitude);
    //type:double,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_double(jwc, "longitude", objptr->longitude);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "direction", objptr->direction);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "gps_update_en", objptr->gps_update_en);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_location_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_gps_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_gps_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err             = JWRITE_OK;
    sys_param_gps_t *objptr = (sys_param_gps_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "en", objptr->en);
    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "manufacture", objptr->manufacture);

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "default_baudrate", objptr->default_baudrate);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "baudrate", objptr->baudrate);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "rate", objptr->rate);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "dgps_en", objptr->dgps_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "swfilter_en", objptr->swfilter_en);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_gps_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_location_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_location_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                        = JWRITE_OK;
    sys_param_location_setup_t *objptr = (sys_param_location_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:sys_param_location_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_location_t_dumps(jwc, "location", &objptr->location);
    //type:sys_param_gps_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_gps_t_dumps(jwc, "gps", &objptr->gps);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_location_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did6_location_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did6_location_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                  = JWRITE_OK;
    sys_param_sid0did6_location_config_t *objptr = (sys_param_sid0did6_location_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_location_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_location_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did6_location_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_jctbox_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_jctbox_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                      = JWRITE_OK;
    sys_param_jctbox_setup_t *objptr = (sys_param_jctbox_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "commtype", objptr->commtype);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "highspeed_en", objptr->highspeed_en);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "baudrate_default", objptr->baudrate_default);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "baudrate_high", objptr->baudrate_high);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "packettype", objptr->packettype);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "tbd0", objptr->tbd0);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "tbd1", objptr->tbd1);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "tbd2", objptr->tbd2);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "tbd3", objptr->tbd3);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_jctbox_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did7_jctbox_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did7_jctbox_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                = JWRITE_OK;
    sys_param_sid0did7_jctbox_config_t *objptr = (sys_param_sid0did7_jctbox_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_jctbox_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_jctbox_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did7_jctbox_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_rs485_protocol_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_rs485_protocol_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                              = JWRITE_OK;
    sys_param_rs485_protocol_setup_t *objptr = (sys_param_rs485_protocol_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "commtype", objptr->commtype);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "highspeed_en", objptr->highspeed_en);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "baudrate_default", objptr->baudrate_default);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "baudrate_high", objptr->baudrate_high);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "packettype", objptr->packettype);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "tbd0", objptr->tbd0);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "tbd1", objptr->tbd1);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "tbd2", objptr->tbd2);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "tbd3", objptr->tbd3);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_rs485_protocol_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did8_rs485_protocol_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did8_rs485_protocol_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                        = JWRITE_OK;
    sys_param_sid0did8_rs485_protocol_config_t *objptr = (sys_param_sid0did8_rs485_protocol_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_rs485_protocol_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_rs485_protocol_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did8_rs485_protocol_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_cameractrl_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_cameractrl_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                          = JWRITE_OK;
    sys_param_cameractrl_setup_t *objptr = (sys_param_cameractrl_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "en", objptr->en);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "framerate", objptr->framerate);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "imageresolution", objptr->imageresolution);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "imageroi", objptr->imageroi);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "format", objptr->format);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "brightness", objptr->brightness);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "contrast", objptr->contrast);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "gain", objptr->gain);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "exposure_limit", objptr->exposure_limit);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "tbd1", objptr->tbd1);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "tbd2", objptr->tbd2);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "tbd3", objptr->tbd3);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "tbd4", objptr->tbd4);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "tbd5", objptr->tbd5);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "tbd6", objptr->tbd6);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "tbd7", objptr->tbd7);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "tbd8", objptr->tbd8);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_cameractrl_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_camera_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_camera_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                      = JWRITE_OK;
    sys_param_camera_setup_t *objptr = (sys_param_camera_setup_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "count", objptr->count);
    //type:sys_param_cameractrl_setup_t,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "cam");
    for(i = 0; i < 2; i++)
    {
        jwArr_object(jwc);
        sys_param_cameractrl_setup_t_dumps(jwc, "", &objptr->cam[i]);
        jwEnd(jwc);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_camera_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did9_camera_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did9_camera_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                = JWRITE_OK;
    sys_param_sid0did9_camera_config_t *objptr = (sys_param_sid0did9_camera_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_camera_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_camera_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did9_camera_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_rsp_eol_phasecal_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_rsp_eol_phasecal_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                          = JWRITE_OK;
    sys_param_rsp_eol_phasecal_t *objptr = (sys_param_rsp_eol_phasecal_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "real", objptr->real);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "imag", objptr->imag);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_rsp_eol_phasecal_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_rsp_eol_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_rsp_eol_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                       = JWRITE_OK;
    sys_param_rsp_eol_setup_t *objptr = (sys_param_rsp_eol_setup_t *)pvParam;

    int32_t i, j;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "en", objptr->en);
    //type:sys_param_rsp_eol_phasecal_t,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "phasecal");
    for(i = 0; i < 4; i++)
    {
        jwArr_object(jwc);
        sys_param_rsp_eol_phasecal_t_dumps(jwc, "", &objptr->phasecal[i]);
        jwEnd(jwc);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "noise_level_up");
    for(i = 0; i < 4; i++)
    {
        if(objptr->noise_level_up[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->noise_level_up[i]);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "noise_level_dn");
    for(i = 0; i < 4; i++)
    {
        if(objptr->noise_level_dn[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->noise_level_dn[i]);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "aziangstep", objptr->aziangstep);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "aziangmin", objptr->aziangmin);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "aziangmax", objptr->aziangmax);
    //type:float,  ismultidimarray : True, isarray : True, isstring : False, m_countlist:[361, 4]
    jwObj_array(jwc, "azibeampattern_up");
    for(i = 0; i < 361; i++)
    {
        jwArr_array(jwc);
        for(j = 0; j < 4; j++)
        {
            if(objptr->azibeampattern_up[i][j] <= SYS_PARAM_F32_ARR_END_VALUE)
                break;
            jwArr_float(jwc, (float)objptr->azibeampattern_up[i][j]);
        }
        jwEnd(jwc);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : True, isarray : True, isstring : False, m_countlist:[361, 4]
    jwObj_array(jwc, "azibeamphase_up");
    for(i = 0; i < 361; i++)
    {
        jwArr_array(jwc);
        for(j = 0; j < 4; j++)
        {
            if(objptr->azibeamphase_up[i][j] <= SYS_PARAM_F32_ARR_END_VALUE)
                break;
            jwArr_float(jwc, (float)objptr->azibeamphase_up[i][j]);
        }
        jwEnd(jwc);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : True, isarray : True, isstring : False, m_countlist:[361, 4]
    jwObj_array(jwc, "azibeampattern_dn");
    for(i = 0; i < 361; i++)
    {
        jwArr_array(jwc);
        for(j = 0; j < 4; j++)
        {
            if(objptr->azibeampattern_dn[i][j] <= SYS_PARAM_F32_ARR_END_VALUE)
                break;
            jwArr_float(jwc, (float)objptr->azibeampattern_dn[i][j]);
        }
        jwEnd(jwc);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : True, isarray : True, isstring : False, m_countlist:[361, 4]
    jwObj_array(jwc, "azibeamphase_dn");
    for(i = 0; i < 361; i++)
    {
        jwArr_array(jwc);
        for(j = 0; j < 4; j++)
        {
            if(objptr->azibeamphase_dn[i][j] <= SYS_PARAM_F32_ARR_END_VALUE)
                break;
            jwArr_float(jwc, (float)objptr->azibeamphase_dn[i][j]);
        }
        jwEnd(jwc);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_rsp_eol_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did10_rsp_eol_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did10_rsp_eol_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                  = JWRITE_OK;
    sys_param_sid0did10_rsp_eol_config_t *objptr = (sys_param_sid0did10_rsp_eol_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_rsp_eol_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_rsp_eol_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did10_rsp_eol_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_rsp_install_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_rsp_install_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                           = JWRITE_OK;
    sys_param_rsp_install_setup_t *objptr = (sys_param_rsp_install_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "height", objptr->height);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "ele_angle", objptr->ele_angle);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "azi_angle", objptr->azi_angle);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "offset_x", objptr->offset_x);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "offset_y", objptr->offset_y);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_rsp_install_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did11_rsp_install_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did11_rsp_install_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                      = JWRITE_OK;
    sys_param_sid0did11_rsp_install_config_t *objptr = (sys_param_sid0did11_rsp_install_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_rsp_install_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_rsp_install_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did11_rsp_install_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_rsm_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_rsm_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                   = JWRITE_OK;
    sys_param_rsm_setup_t *objptr = (sys_param_rsm_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "mode", objptr->mode);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "userfreq", objptr->userfreq);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "scanrate", objptr->scanrate);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "daq_sampledelay", objptr->daq_sampledelay);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_rsm_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did12_rsm_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did12_rsm_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                              = JWRITE_OK;
    sys_param_sid0did12_rsm_config_t *objptr = (sys_param_sid0did12_rsm_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_rsm_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_rsm_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did12_rsm_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_rsptrk_posttune_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_rsptrk_posttune_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                         = JWRITE_OK;
    sys_param_rsptrk_posttune_t *objptr = (sys_param_rsptrk_posttune_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "LongGate1", objptr->LongGate1);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "LongGate2", objptr->LongGate2);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "LongGate3", objptr->LongGate3);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "LongGateByVel_Gain", objptr->LongGateByVel_Gain);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "MotorCycle_PowTh", objptr->MotorCycle_PowTh);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "MotorCycle_PowTh2", objptr->MotorCycle_PowTh2);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "MotorCycleByRange_Gain", objptr->MotorCycleByRange_Gain);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "TrackOutFilter", objptr->TrackOutFilter);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "tbd8", objptr->tbd8);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "tbd9", objptr->tbd9);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "tbd10", objptr->tbd10);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "tbd11", objptr->tbd11);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "tbd12", objptr->tbd12);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "tbd13", objptr->tbd13);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "tbd14", objptr->tbd14);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "tbd15", objptr->tbd15);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_rsptrk_posttune_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_rsptrk_trktune_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_rsptrk_trktune_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                        = JWRITE_OK;
    sys_param_rsptrk_trktune_t *objptr = (sys_param_rsptrk_trktune_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "s16Pt_New2Vrf", objptr->s16Pt_New2Vrf);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "s16Pt_Max", objptr->s16Pt_Max);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "s16Pt_New_Upd", objptr->s16Pt_New_Upd);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "s16Pt_New_Coast", objptr->s16Pt_New_Coast);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "s16Pt_Vrf_Upd", objptr->s16Pt_Vrf_Upd);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "s16Pt_Vrf_Coast", objptr->s16Pt_Vrf_Coast);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "f32Pt_NearRange", objptr->f32Pt_NearRange);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "s16Pt_Vrf_Upd_Near", objptr->s16Pt_Vrf_Upd_Near);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "s16Pt_Vrf_Coast_Near", objptr->s16Pt_Vrf_Coast_Near);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "f32R_GateByEle_W", objptr->f32R_GateByEle_W);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "f32V_GateByEle_W", objptr->f32V_GateByEle_W);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_rsptrk_trktune_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_rsptrk_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_rsptrk_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                      = JWRITE_OK;
    sys_param_rsptrk_setup_t *objptr = (sys_param_rsptrk_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:sys_param_rsptrk_posttune_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_rsptrk_posttune_t_dumps(jwc, "posttune", &objptr->posttune);
    //type:sys_param_rsptrk_trktune_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_rsptrk_trktune_t_dumps(jwc, "trktune", &objptr->trktune);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_rsptrk_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did13_rsptrk_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did13_rsptrk_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                 = JWRITE_OK;
    sys_param_sid0did13_rsptrk_config_t *objptr = (sys_param_sid0did13_rsptrk_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_rsptrk_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_rsptrk_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did13_rsptrk_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_rfictx_select_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_rfictx_select_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                       = JWRITE_OK;
    sys_param_rfictx_select_t *objptr = (sys_param_rfictx_select_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "rfictx_sel", objptr->rfictx_sel);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_rfictx_select_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did30_rfictx_select_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did30_rfictx_select_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                        = JWRITE_OK;
    sys_param_sid0did30_rfictx_select_config_t *objptr = (sys_param_sid0did30_rfictx_select_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_rfictx_select_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_rfictx_select_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did30_rfictx_select_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_rfictx_bgt24at2_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_rfictx_bgt24at2_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                               = JWRITE_OK;
    sys_param_rfictx_bgt24at2_setup_t *objptr = (sys_param_rfictx_bgt24at2_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "TX1_A", objptr->TX1_A);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "TX1_SPI_ON", objptr->TX1_SPI_ON);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "TX1_EN_DAC", objptr->TX1_EN_DAC);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "TX1_SEL1", objptr->TX1_SEL1);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "PH1_SPI_ON", objptr->PH1_SPI_ON);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "TX2_A", objptr->TX2_A);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "TX2_SPI_ON", objptr->TX2_SPI_ON);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "TX2_SEL1", objptr->TX2_SEL1);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "TX2_EN_DAC", objptr->TX2_EN_DAC);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "PH2_SPI_ON", objptr->PH2_SPI_ON);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "LO_A", objptr->LO_A);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "LO_SPI_ON", objptr->LO_SPI_ON);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "LO_EN_DAC", objptr->LO_EN_DAC);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "LO_SEL1", objptr->LO_SEL1);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "LO_SEL0", objptr->LO_SEL0);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "PHLO_SPI_ON", objptr->PHLO_SPI_ON);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "VCO_A", objptr->VCO_A);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "EN_DAC_VCO", objptr->EN_DAC_VCO);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "EN_VCO", objptr->EN_VCO);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "EN_BUF2", objptr->EN_BUF2);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "EN_BUF1", objptr->EN_BUF1);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "PH_SEL1", objptr->PH_SEL1);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "AMUX1_SEL1", objptr->AMUX1_SEL1);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "AMUX1_SEL0", objptr->AMUX1_SEL0);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "AMUX2_SEL2", objptr->AMUX2_SEL2);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "AMUX2_SEL1", objptr->AMUX2_SEL1);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "AMUX2_SEL0", objptr->AMUX2_SEL0);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "AMUX3_SEL1", objptr->AMUX3_SEL1);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "AMUX3_SEL0", objptr->AMUX3_SEL0);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "EN_DIV", objptr->EN_DIV);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "SEL_DIVBUF", objptr->SEL_DIVBUF);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "SEL_DIV", objptr->SEL_DIV);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "DIS_DIVOUT", objptr->DIS_DIVOUT);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_rfictx_bgt24at2_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did31_rfictx_bgt24at2_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did31_rfictx_bgt24at2_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                          = JWRITE_OK;
    sys_param_sid0did31_rfictx_bgt24at2_config_t *objptr = (sys_param_sid0did31_rfictx_bgt24at2_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_rfictx_bgt24at2_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_rfictx_bgt24at2_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did31_rfictx_bgt24at2_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_rficrx_select_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_rficrx_select_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                       = JWRITE_OK;
    sys_param_rficrx_select_t *objptr = (sys_param_rficrx_select_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "rficrx_sel", objptr->rficrx_sel);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_rficrx_select_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did40_rficrx_select_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did40_rficrx_select_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                        = JWRITE_OK;
    sys_param_sid0did40_rficrx_select_config_t *objptr = (sys_param_sid0did40_rficrx_select_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_rficrx_select_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_rficrx_select_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did40_rficrx_select_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_rficrx_bgt24ar4_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_rficrx_bgt24ar4_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                               = JWRITE_OK;
    sys_param_rficrx_bgt24ar4_setup_t *objptr = (sys_param_rficrx_bgt24ar4_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "EN_12", objptr->EN_12);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "LG1_12_6db", objptr->LG1_12_6db);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "HG1_12_12db", objptr->HG1_12_12db);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "LG2_12_6db", objptr->LG2_12_6db);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "MG2_12_12db", objptr->MG2_12_12db);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "HG2_12_18db", objptr->HG2_12_18db);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "EN_34", objptr->EN_34);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "LG1_34_6db", objptr->LG1_34_6db);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "HG1_34_12db", objptr->HG1_34_12db);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "LG2_34_6db", objptr->LG2_34_6db);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "MG2_34_12db", objptr->MG2_34_12db);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "HG2_34_18db", objptr->HG2_34_18db);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "IFTEST4", objptr->IFTEST4);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "IFTEST3", objptr->IFTEST3);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "IFTEST2", objptr->IFTEST2);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "IFTEST1", objptr->IFTEST1);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "PC1", objptr->PC1);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "PC2", objptr->PC2);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "EN_RF14", objptr->EN_RF14);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "EN_RF23", objptr->EN_RF23);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "DIS_DIV", objptr->DIS_DIV);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "DIS_LO", objptr->DIS_LO);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "AMUX_SEL0", objptr->AMUX_SEL0);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "AMUX_SEL1", objptr->AMUX_SEL1);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "AMUX_SEL2", objptr->AMUX_SEL2);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "SAT_FLAG_HIZ", objptr->SAT_FLAG_HIZ);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "SENSOR_SEL0", objptr->SENSOR_SEL0);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "SENSOR_SEL1", objptr->SENSOR_SEL1);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "DCO_0", objptr->DCO_0);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "DCO_1", objptr->DCO_1);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "DCO_2", objptr->DCO_2);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "DCO_3", objptr->DCO_3);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_rficrx_bgt24ar4_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did41_rficrx_bgt24ar4_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did41_rficrx_bgt24ar4_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                          = JWRITE_OK;
    sys_param_sid0did41_rficrx_bgt24ar4_config_t *objptr = (sys_param_sid0did41_rficrx_bgt24ar4_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_rficrx_bgt24ar4_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_rficrx_bgt24ar4_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did41_rficrx_bgt24ar4_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_pll_select_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_pll_select_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                    = JWRITE_OK;
    sys_param_pll_select_t *objptr = (sys_param_pll_select_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "pll_sel", objptr->pll_sel);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_pll_select_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did50_pll_select_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did50_pll_select_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                     = JWRITE_OK;
    sys_param_sid0did50_pll_select_config_t *objptr = (sys_param_sid0did50_pll_select_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_pll_select_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_pll_select_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did50_pll_select_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_pll_lmx2491_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_pll_lmx2491_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                           = JWRITE_OK;
    sys_param_pll_lmx2491_setup_t *objptr = (sys_param_pll_lmx2491_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "regset", objptr->regset);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "cp", objptr->cp);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_pll_lmx2491_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did51_pll_lmx2491_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did51_pll_lmx2491_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                      = JWRITE_OK;
    sys_param_sid0did51_pll_lmx2491_config_t *objptr = (sys_param_sid0did51_pll_lmx2491_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_pll_lmx2491_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_pll_lmx2491_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did51_pll_lmx2491_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_adc_select_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_adc_select_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                    = JWRITE_OK;
    sys_param_adc_select_t *objptr = (sys_param_adc_select_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "adc_sel", objptr->adc_sel);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_adc_select_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did60_adc_select_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did60_adc_select_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                     = JWRITE_OK;
    sys_param_sid0did60_adc_select_config_t *objptr = (sys_param_sid0did60_adc_select_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_adc_select_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_adc_select_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did60_adc_select_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_adc_adar7251_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_adc_adar7251_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                            = JWRITE_OK;
    sys_param_adc_adar7251_setup_t *objptr = (sys_param_adc_adar7251_setup_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "ROUTING");
    for(i = 0; i < 4; i++)
    {
        if(objptr->ROUTING[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->ROUTING[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "LNA_GAIN");
    for(i = 0; i < 4; i++)
    {
        if(objptr->LNA_GAIN[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->LNA_GAIN[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "PGA_GAIN");
    for(i = 0; i < 4; i++)
    {
        if(objptr->PGA_GAIN[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->PGA_GAIN[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "EQ_CAP", objptr->EQ_CAP);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_adc_adar7251_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did61_adc_adar7251_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did61_adc_adar7251_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                       = JWRITE_OK;
    sys_param_sid0did61_adc_adar7251_config_t *objptr = (sys_param_sid0did61_adc_adar7251_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_adc_adar7251_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_adc_adar7251_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did61_adc_adar7251_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_adc_max11043_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_adc_max11043_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                            = JWRITE_OK;
    sys_param_adc_max11043_setup_t *objptr = (sys_param_adc_max11043_setup_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "analog_filtermode");
    for(i = 0; i < 4; i++)
    {
        if(objptr->analog_filtermode[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->analog_filtermode[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "gain");
    for(i = 0; i < 4; i++)
    {
        if(objptr->gain[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->gain[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "digtal_filtermode");
    for(i = 0; i < 4; i++)
    {
        if(objptr->digtal_filtermode[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->digtal_filtermode[i]);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "fine_gain");
    for(i = 0; i < 4; i++)
    {
        if(objptr->fine_gain[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->fine_gain[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "inputbias");
    for(i = 0; i < 4; i++)
    {
        if(objptr->inputbias[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->inputbias[i]);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_adc_max11043_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did62_adc_max11043_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did62_adc_max11043_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                       = JWRITE_OK;
    sys_param_sid0did62_adc_max11043_config_t *objptr = (sys_param_sid0did62_adc_max11043_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_adc_max11043_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_adc_max11043_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did62_adc_max11043_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_app_packet_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_app_packet_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                    = JWRITE_OK;
    sys_param_app_packet_t *objptr = (sys_param_app_packet_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "server_ip", objptr->server_ip);

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "port_num", objptr->port_num);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "port_en", objptr->port_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "client_mode_en", objptr->client_mode_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_simple_en", objptr->pid_simple_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_compress_en", objptr->pid_compress_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_status_en", objptr->pid_status_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_object_en", objptr->pid_object_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_track_en", objptr->pid_track_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_image_en", objptr->pid_image_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_imagsp_en", objptr->pid_imagsp_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_logger_en", objptr->pid_logger_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_canlog_en", objptr->pid_canlog_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_sensor_en", objptr->pid_sensor_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_app_its_en", objptr->pid_app_its_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_app_vf_en", objptr->pid_app_vf_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_app_fcw_en", objptr->pid_app_fcw_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "pid_app_lm_en", objptr->pid_app_lm_en);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_app_packet_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_app_packet_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_app_packet_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                          = JWRITE_OK;
    sys_param_app_packet_setup_t *objptr = (sys_param_app_packet_setup_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "count", objptr->count);
    //type:sys_param_app_packet_t,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "ports");
    for(i = 0; i < 4; i++)
    {
        jwArr_object(jwc);
        sys_param_app_packet_t_dumps(jwc, "", &objptr->ports[i]);
        jwEnd(jwc);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_app_packet_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid0did200_app_packet_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid0did200_app_packet_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                      = JWRITE_OK;
    sys_param_sid0did200_app_packet_config_t *objptr = (sys_param_sid0did200_app_packet_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_app_packet_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_app_packet_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid0did200_app_packet_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_candrv_channel_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_candrv_channel_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                              = JWRITE_OK;
    sys_param_candrv_channel_setup_t *objptr = (sys_param_candrv_channel_setup_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "cantype", objptr->cantype);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "baudrate", objptr->baudrate);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "baudratefd", objptr->baudratefd);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "samplepoint", objptr->samplepoint);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "listenonlymode_en", objptr->listenonlymode_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "acceptfilter_en");
    for(i = 0; i < 4; i++)
    {
        if(objptr->acceptfilter_en[i] >= SYS_PARAM_BOOL_ARR_END_VALUE)
            break;
        jwArr_bool(jwc, (unsigned char)objptr->acceptfilter_en[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "acceptfilter_id");
    for(i = 0; i < 4; i++)
    {
        if(objptr->acceptfilter_id[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->acceptfilter_id[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "acceptfilter_mask");
    for(i = 0; i < 4; i++)
    {
        if(objptr->acceptfilter_mask[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->acceptfilter_mask[i]);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_candrv_channel_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_candrv_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_candrv_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                      = JWRITE_OK;
    sys_param_candrv_setup_t *objptr = (sys_param_candrv_setup_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "channel_count", objptr->channel_count);
    //type:sys_param_candrv_channel_setup_t,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "channel");
    for(i = 0; i < 2; i++)
    {
        jwArr_object(jwc);
        sys_param_candrv_channel_setup_t_dumps(jwc, "", &objptr->channel[i]);
        jwEnd(jwc);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_candrv_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid6did0_candrv_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid6did0_candrv_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                = JWRITE_OK;
    sys_param_sid6did0_candrv_config_t *objptr = (sys_param_sid6did0_candrv_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_candrv_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_candrv_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid6did0_candrv_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_cansignal_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_cansignal_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                   = JWRITE_OK;
    sys_param_cansignal_t *objptr = (sys_param_cansignal_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "en", objptr->en);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sigid", objptr->sigid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "msgid", objptr->msgid);
    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "name", objptr->name);

    //type:signed_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "type", objptr->type);
    //type:signed_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "byteorder", objptr->byteorder);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "bitpos", objptr->bitpos);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "length", objptr->length);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "factor", objptr->factor);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "offset", objptr->offset);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "min", objptr->min);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "max", objptr->max);
    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[8]
    jwObj_string(jwc, "unit", objptr->unit);


    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_cansignal_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_cansignal_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_cansignal_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                         = JWRITE_OK;
    sys_param_cansignal_setup_t *objptr = (sys_param_cansignal_setup_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:sys_param_cansignal_t,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[16]
    jwObj_array(jwc, "signal");
    for(i = 0; i < 16; i++)
    {
        jwArr_object(jwc);
        sys_param_cansignal_t_dumps(jwc, "", &objptr->signal[i]);
        jwEnd(jwc);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_cansignal_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid6did1_cansignal_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid6did1_cansignal_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                   = JWRITE_OK;
    sys_param_sid6did1_cansignal_config_t *objptr = (sys_param_sid6did1_cansignal_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_cansignal_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_cansignal_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid6did1_cansignal_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_can_txmsg_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_can_txmsg_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                   = JWRITE_OK;
    sys_param_can_txmsg_t *objptr = (sys_param_can_txmsg_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "en", objptr->en);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "start_id", objptr->start_id);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "count", objptr->count);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_can_txmsg_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_cantxmsg_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_cantxmsg_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                        = JWRITE_OK;
    sys_param_cantxmsg_setup_t *objptr = (sys_param_cantxmsg_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:sys_param_can_txmsg_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_can_txmsg_t_dumps(jwc, "status", &objptr->status);
    //type:sys_param_can_txmsg_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_can_txmsg_t_dumps(jwc, "object", &objptr->object);
    //type:sys_param_can_txmsg_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_can_txmsg_t_dumps(jwc, "track", &objptr->track);
    //type:sys_param_can_txmsg_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_can_txmsg_t_dumps(jwc, "extioctrl", &objptr->extioctrl);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_cantxmsg_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid6did2_cantxmsg_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid6did2_cantxmsg_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                  = JWRITE_OK;
    sys_param_sid6did2_cantxmsg_config_t *objptr = (sys_param_sid6did2_cantxmsg_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_cantxmsg_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_cantxmsg_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid6did2_cantxmsg_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_filesystem_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_filesystem_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                          = JWRITE_OK;
    sys_param_filesystem_setup_t *objptr = (sys_param_filesystem_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "isformatted", objptr->isformatted);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "lastfilenumber", objptr->lastfilenumber);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "mmc_write_enable", objptr->mmc_write_enable);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_filesystem_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid7did0_filesystem_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid7did0_filesystem_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                    = JWRITE_OK;
    sys_param_sid7did0_filesystem_config_t *objptr = (sys_param_sid7did0_filesystem_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_filesystem_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_filesystem_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid7did0_filesystem_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_status_timestamp_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_status_timestamp_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                          = JWRITE_OK;
    sys_param_status_timestamp_t *objptr = (sys_param_status_timestamp_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:double,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_double(jwc, "timestamp_s", objptr->timestamp_s);
    //type:long_long,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int64(jwc, "rsp_timestamp_us", objptr->rsp_timestamp_us);
    //type:long_long,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int64(jwc, "net_timestamp_us", objptr->net_timestamp_us);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "rsp_cycletime", objptr->rsp_cycletime);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_status_timestamp_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_status_data_position_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_status_data_position_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                              = JWRITE_OK;
    sys_param_status_data_position_t *objptr = (sys_param_status_data_position_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "yaw", objptr->yaw);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "roll", objptr->roll);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "pitch", objptr->pitch);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "altitude", objptr->altitude);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_status_data_position_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_status_data_ecuinfo_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_status_data_ecuinfo_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                             = JWRITE_OK;
    sys_param_status_data_ecuinfo_t *objptr = (sys_param_status_data_ecuinfo_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "temp_core", objptr->temp_core);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "temp_rfm", objptr->temp_rfm);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "vin", objptr->vin);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "v5", objptr->v5);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "v1_5", objptr->v1_5);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "v1_0", objptr->v1_0);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_status_data_ecuinfo_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_status_data_gps_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_status_data_gps_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                         = JWRITE_OK;
    sys_param_status_data_gps_t *objptr = (sys_param_status_data_gps_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "status", objptr->status);
    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[1024]
    jwObj_string(jwc, "data", objptr->data);


    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_status_data_gps_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_pid0_status_data_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_pid0_status_data_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                          = JWRITE_OK;
    sys_param_pid0_status_data_t *objptr = (sys_param_pid0_status_data_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "scanindex", objptr->scanindex);
    //type:sys_param_status_timestamp_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_status_timestamp_t_dumps(jwc, "timestamp", &objptr->timestamp);
    //type:sys_param_status_data_position_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_status_data_position_t_dumps(jwc, "position", &objptr->position);
    //type:sys_param_status_data_ecuinfo_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_status_data_ecuinfo_t_dumps(jwc, "ecuinfo", &objptr->ecuinfo);
    //type:sys_param_status_data_gps_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_status_data_gps_t_dumps(jwc, "gps", &objptr->gps);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_pid0_status_data_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_setup_timeschedule_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_setup_timeschedule_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                = JWRITE_OK;
    sys_param_its_setup_timeschedule_t *objptr = (sys_param_its_setup_timeschedule_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[8]
    jwObj_string(jwc, "timeunit", objptr->timeunit);

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "updatetime", objptr->updatetime);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_setup_timeschedule_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_setup_laneinfo_lane_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_setup_laneinfo_lane_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                 = JWRITE_OK;
    sys_param_its_setup_laneinfo_lane_t *objptr = (sys_param_its_setup_laneinfo_lane_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[50]
    jwObj_array(jwc, "x");
    for(i = 0; i < 50; i++)
    {
        if(objptr->x[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->x[i]);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[50]
    jwObj_array(jwc, "y");
    for(i = 0; i < 50; i++)
    {
        if(objptr->y[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->y[i]);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_setup_laneinfo_lane_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_setup_zone_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_setup_zone_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                        = JWRITE_OK;
    sys_param_its_setup_zone_t *objptr = (sys_param_its_setup_zone_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[100]
    jwObj_array(jwc, "x");
    for(i = 0; i < 100; i++)
    {
        if(objptr->x[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->x[i]);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[100]
    jwObj_array(jwc, "y");
    for(i = 0; i < 100; i++)
    {
        if(objptr->y[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->y[i]);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_setup_zone_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_setup_hotspotzone_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_setup_hotspotzone_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                               = JWRITE_OK;
    sys_param_its_setup_hotspotzone_t *objptr = (sys_param_its_setup_hotspotzone_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[100]
    jwObj_array(jwc, "x");
    for(i = 0; i < 100; i++)
    {
        if(objptr->x[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->x[i]);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[100]
    jwObj_array(jwc, "y");
    for(i = 0; i < 100; i++)
    {
        if(objptr->y[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->y[i]);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "width", objptr->width);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "midoffset", objptr->midoffset);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_setup_hotspotzone_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_setup_laneinfo_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_setup_laneinfo_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                            = JWRITE_OK;
    sys_param_its_setup_laneinfo_t *objptr = (sys_param_its_setup_laneinfo_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "stepcount", objptr->stepcount);
    //type:sys_param_its_setup_laneinfo_lane_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_setup_laneinfo_lane_t_dumps(jwc, "left", &objptr->left);
    //type:sys_param_its_setup_hotspotzone_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_setup_hotspotzone_t_dumps(jwc, "hotspotzone", &objptr->hotspotzone);
    //type:sys_param_its_setup_zone_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_setup_zone_t_dumps(jwc, "trackingzone", &objptr->trackingzone);
    //type:sys_param_its_setup_laneinfo_lane_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_setup_laneinfo_lane_t_dumps(jwc, "right", &objptr->right);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "number", objptr->number);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_setup_laneinfo_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_setup_area_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_setup_area_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                        = JWRITE_OK;
    sys_param_its_setup_area_t *objptr = (sys_param_its_setup_area_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "x");
    for(i = 0; i < 2; i++)
    {
        if(objptr->x[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->x[i]);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "y");
    for(i = 0; i < 2; i++)
    {
        if(objptr->y[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->y[i]);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "t", objptr->t);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_setup_area_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_setup_blackout_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_setup_blackout_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                            = JWRITE_OK;
    sys_param_its_setup_blackout_t *objptr = (sys_param_its_setup_blackout_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "count", objptr->count);
    //type:sys_param_its_setup_area_t,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[10]
    jwObj_array(jwc, "area");
    for(i = 0; i < 10; i++)
    {
        jwArr_object(jwc);
        sys_param_its_setup_area_t_dumps(jwc, "", &objptr->area[i]);
        jwEnd(jwc);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_setup_blackout_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_setup_speedlimit_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_setup_speedlimit_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                              = JWRITE_OK;
    sys_param_its_setup_speedlimit_t *objptr = (sys_param_its_setup_speedlimit_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "high_speedlimit_kph", objptr->high_speedlimit_kph);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "low_speedlimit_kph", objptr->low_speedlimit_kph);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "speedlimit_compensation_percentage", objptr->speedlimit_compensation_percentage);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_setup_speedlimit_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_setup_misc_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_setup_misc_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                        = JWRITE_OK;
    sys_param_its_setup_misc_t *objptr = (sys_param_its_setup_misc_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "camera_on", objptr->camera_on);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "trackingzone_view_on", objptr->trackingzone_view_on);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "autoalignment_on", objptr->autoalignment_on);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "num_track_autoalignment", objptr->num_track_autoalignment);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_setup_misc_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                   = JWRITE_OK;
    sys_param_its_setup_t *objptr = (sys_param_its_setup_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:sys_param_its_setup_timeschedule_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_setup_timeschedule_t_dumps(jwc, "timeschedule", &objptr->timeschedule);
    //type:sys_param_its_setup_misc_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_setup_misc_t_dumps(jwc, "misc", &objptr->misc);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "middlelane", objptr->middlelane);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "uplaneangle", objptr->uplaneangle);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "downlaneangle", objptr->downlaneangle);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "lanecount", objptr->lanecount);
    //type:sys_param_its_setup_speedlimit_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_setup_speedlimit_t_dumps(jwc, "speedlimit", &objptr->speedlimit);
    //type:sys_param_its_setup_laneinfo_t,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "laneinfo");
    for(i = 0; i < 4; i++)
    {
        jwArr_object(jwc);
        sys_param_its_setup_laneinfo_t_dumps(jwc, "", &objptr->laneinfo[i]);
        jwEnd(jwc);
    }
    jwEnd(jwc);
    //type:sys_param_its_setup_blackout_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_setup_blackout_t_dumps(jwc, "blackout", &objptr->blackout);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid8did0_its_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid8did0_its_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                             = JWRITE_OK;
    sys_param_sid8did0_its_config_t *objptr = (sys_param_sid8did0_its_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "description", objptr->description);

    //type:sys_param_its_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid8did0_its_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_relay_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_relay_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                   = JWRITE_OK;
    sys_param_its_relay_t *objptr = (sys_param_its_relay_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "relay_cnt", objptr->relay_cnt);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "relay_enable");
    for(i = 0; i < 2; i++)
    {
        if(objptr->relay_enable[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->relay_enable[i]);
    }
    jwEnd(jwc);
    //type:char,  ismultidimarray : True, isarray : True, isstring : True, m_countlist:[2]
    jwObj_array(jwc, "relay_type");
    for(i = 0; i < 2; i++)
    {
        if(strlen(objptr->relay_type[i]) == 0)
            break;
        jwArr_string(jwc, objptr->relay_type[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "relay_on_time_ms");
    for(i = 0; i < 2; i++)
    {
        if(objptr->relay_on_time_ms[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->relay_on_time_ms[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "relay_off_time_ms");
    for(i = 0; i < 2; i++)
    {
        if(objptr->relay_off_time_ms[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->relay_off_time_ms[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "relay_adjust_time_ms");
    for(i = 0; i < 2; i++)
    {
        if(objptr->relay_adjust_time_ms[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->relay_adjust_time_ms[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "relay_lowbound_time_ms");
    for(i = 0; i < 2; i++)
    {
        if(objptr->relay_lowbound_time_ms[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->relay_lowbound_time_ms[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "relay_highbound_time_ms");
    for(i = 0; i < 2; i++)
    {
        if(objptr->relay_highbound_time_ms[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->relay_highbound_time_ms[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "relay_on_event_type");
    for(i = 0; i < 2; i++)
    {
        if(objptr->relay_on_event_type[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->relay_on_event_type[i]);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_relay_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_device_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_device_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                          = JWRITE_OK;
    sys_param_its_device_setup_t *objptr = (sys_param_its_device_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:sys_param_its_relay_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_relay_t_dumps(jwc, "relay", &objptr->relay);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_device_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid8did1_its_relay_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid8did1_its_relay_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                   = JWRITE_OK;
    sys_param_sid8did1_its_relay_config_t *objptr = (sys_param_sid8did1_its_relay_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "description", objptr->description);

    //type:sys_param_its_device_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_device_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid8did1_its_relay_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_alignment_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_alignment_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                             = JWRITE_OK;
    sys_param_its_alignment_setup_t *objptr = (sys_param_its_alignment_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "autoalignment_on", objptr->autoalignment_on);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "num_track_autoalignment", objptr->num_track_autoalignment);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "status_autoalignment", objptr->status_autoalignment);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "angle_aligned", objptr->angle_aligned);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_alignment_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid8did2_its_align_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid8did2_its_align_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                   = JWRITE_OK;
    sys_param_sid8did2_its_align_config_t *objptr = (sys_param_sid8did2_its_align_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "description", objptr->description);

    //type:sys_param_its_alignment_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_alignment_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid8did2_its_align_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_testmode_speedlimit_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_testmode_speedlimit_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                 = JWRITE_OK;
    sys_param_its_testmode_speedlimit_t *objptr = (sys_param_its_testmode_speedlimit_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "high_speedlimit_tolerance_percentage", objptr->high_speedlimit_tolerance_percentage);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "low_speedlimit_tolerance_percentage", objptr->low_speedlimit_tolerance_percentage);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_testmode_speedlimit_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_testmode_trigger_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_testmode_trigger_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                              = JWRITE_OK;
    sys_param_its_testmode_trigger_t *objptr = (sys_param_its_testmode_trigger_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:unsigned_char,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "trigger_en");
    for(i = 0; i < 2; i++)
    {
        if(objptr->trigger_en[i] >= SYS_PARAM_BOOL_ARR_END_VALUE)
            break;
        jwArr_bool(jwc, (unsigned char)objptr->trigger_en[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "trigger_period");
    for(i = 0; i < 2; i++)
    {
        if(objptr->trigger_period[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->trigger_period[i]);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "trigger_ttlc_time_ms");
    for(i = 0; i < 2; i++)
    {
        if(objptr->trigger_ttlc_time_ms[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->trigger_ttlc_time_ms[i]);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_testmode_trigger_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_testmode_hotspotzone_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_testmode_hotspotzone_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                  = JWRITE_OK;
    sys_param_its_testmode_hotspotzone_t *objptr = (sys_param_its_testmode_hotspotzone_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:unsigned_char,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "modlane_en");
    for(i = 0; i < 2; i++)
    {
        if(objptr->modlane_en[i] >= SYS_PARAM_BOOL_ARR_END_VALUE)
            break;
        jwArr_bool(jwc, (unsigned char)objptr->modlane_en[i]);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "modlane_offset_hotspotzone_y");
    for(i = 0; i < 2; i++)
    {
        if(objptr->modlane_offset_hotspotzone_y[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->modlane_offset_hotspotzone_y[i]);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "modlane_offset_hotspotzone_width");
    for(i = 0; i < 2; i++)
    {
        if(objptr->modlane_offset_hotspotzone_width[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->modlane_offset_hotspotzone_width[i]);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[2]
    jwObj_array(jwc, "modlane_offset_hotspotzone_offset");
    for(i = 0; i < 2; i++)
    {
        if(objptr->modlane_offset_hotspotzone_offset[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->modlane_offset_hotspotzone_offset[i]);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_testmode_hotspotzone_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_testmode_image_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_testmode_image_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                            = JWRITE_OK;
    sys_param_its_testmode_image_t *objptr = (sys_param_its_testmode_image_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "skip_image_count", objptr->skip_image_count);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_testmode_image_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_testmode_misc_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_testmode_misc_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                           = JWRITE_OK;
    sys_param_its_testmode_misc_t *objptr = (sys_param_its_testmode_misc_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "trackzone_xrange", objptr->trackzone_xrange);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "en_lanechange", objptr->en_lanechange);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "low_exclude_speed", objptr->low_exclude_speed);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_testmode_misc_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_testmode_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_testmode_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                            = JWRITE_OK;
    sys_param_its_testmode_setup_t *objptr = (sys_param_its_testmode_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:sys_param_its_testmode_speedlimit_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_testmode_speedlimit_t_dumps(jwc, "speedlimit_tolerance", &objptr->speedlimit_tolerance);
    //type:sys_param_its_testmode_trigger_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_testmode_trigger_t_dumps(jwc, "trigger", &objptr->trigger);
    //type:sys_param_its_testmode_hotspotzone_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_testmode_hotspotzone_t_dumps(jwc, "modlane", &objptr->modlane);
    //type:sys_param_its_testmode_image_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_testmode_image_t_dumps(jwc, "imagetest", &objptr->imagetest);
    //type:sys_param_its_testmode_misc_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_testmode_misc_t_dumps(jwc, "misc", &objptr->misc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_testmode_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid8did10_its_testmode_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid8did10_its_testmode_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                       = JWRITE_OK;
    sys_param_sid8did10_its_testmode_config_t *objptr = (sys_param_sid8did10_its_testmode_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "description", objptr->description);

    //type:sys_param_its_testmode_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_testmode_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid8did10_its_testmode_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_data_lane_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_data_lane_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                       = JWRITE_OK;
    sys_param_its_data_lane_t *objptr = (sys_param_its_data_lane_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "cnt", objptr->cnt);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "num");
    for(i = 0; i < 4; i++)
    {
        if(objptr->num[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->num[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[5]
    jwObj_array(jwc, "period");
    for(i = 0; i < 5; i++)
    {
        if(objptr->period[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->period[i]);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_data_lane_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_data_count_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_data_count_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                        = JWRITE_OK;
    sys_param_its_data_count_t *objptr = (sys_param_its_data_count_t *)pvParam;

    int32_t i, j;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "ts", objptr->ts);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "diff");
    for(i = 0; i < 4; i++)
    {
        if(objptr->diff[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->diff[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : True, isarray : True, isstring : False, m_countlist:[5, 4]
    jwObj_array(jwc, "acc");
    for(i = 0; i < 5; i++)
    {
        jwArr_array(jwc);
        for(j = 0; j < 4; j++)
        {
            if(objptr->acc[i][j] <= SYS_PARAM_INT32_ARR_END_VALUE)
                break;
            jwArr_int32(jwc, (int)objptr->acc[i][j]);
        }
        jwEnd(jwc);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "lc");
    for(i = 0; i < 4; i++)
    {
        if(objptr->lc[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->lc[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : True, isarray : True, isstring : False, m_countlist:[5, 4]
    jwObj_array(jwc, "acclc");
    for(i = 0; i < 5; i++)
    {
        jwArr_array(jwc);
        for(j = 0; j < 4; j++)
        {
            if(objptr->acclc[i][j] <= SYS_PARAM_INT32_ARR_END_VALUE)
                break;
            jwArr_int32(jwc, (int)objptr->acclc[i][j]);
        }
        jwEnd(jwc);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_data_count_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_data_speed_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_data_speed_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                        = JWRITE_OK;
    sys_param_its_data_speed_t *objptr = (sys_param_its_data_speed_t *)pvParam;

    int32_t i, j;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:float,  ismultidimarray : True, isarray : True, isstring : False, m_countlist:[5, 4]
    jwObj_array(jwc, "average");
    for(i = 0; i < 5; i++)
    {
        jwArr_array(jwc);
        for(j = 0; j < 4; j++)
        {
            if(objptr->average[i][j] <= SYS_PARAM_F32_ARR_END_VALUE)
                break;
            jwArr_float(jwc, (float)objptr->average[i][j]);
        }
        jwEnd(jwc);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : True, isarray : True, isstring : False, m_countlist:[5, 4]
    jwObj_array(jwc, "min");
    for(i = 0; i < 5; i++)
    {
        jwArr_array(jwc);
        for(j = 0; j < 4; j++)
        {
            if(objptr->min[i][j] <= SYS_PARAM_F32_ARR_END_VALUE)
                break;
            jwArr_float(jwc, (float)objptr->min[i][j]);
        }
        jwEnd(jwc);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : True, isarray : True, isstring : False, m_countlist:[5, 4]
    jwObj_array(jwc, "max");
    for(i = 0; i < 5; i++)
    {
        jwArr_array(jwc);
        for(j = 0; j < 4; j++)
        {
            if(objptr->max[i][j] <= SYS_PARAM_F32_ARR_END_VALUE)
                break;
            jwArr_float(jwc, (float)objptr->max[i][j]);
        }
        jwEnd(jwc);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_data_speed_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_data_event_tidlane_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_data_event_tidlane_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                = JWRITE_OK;
    sys_param_its_data_event_tidlane_t *objptr = (sys_param_its_data_event_tidlane_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[32]
    jwObj_array(jwc, "tid");
    for(i = 0; i < 32; i++)
    {
        if(objptr->tid[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->tid[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[32]
    jwObj_array(jwc, "lane");
    for(i = 0; i < 32; i++)
    {
        if(objptr->lane[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->lane[i]);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_data_event_tidlane_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_data_event_tidlane2_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_data_event_tidlane2_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                 = JWRITE_OK;
    sys_param_its_data_event_tidlane2_t *objptr = (sys_param_its_data_event_tidlane2_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[32]
    jwObj_array(jwc, "tid");
    for(i = 0; i < 32; i++)
    {
        if(objptr->tid[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->tid[i]);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_data_event_tidlane2_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_its_data_event_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_its_data_event_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                        = JWRITE_OK;
    sys_param_its_data_event_t *objptr = (sys_param_its_data_event_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:sys_param_its_data_event_tidlane_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_data_event_tidlane_t_dumps(jwc, "abnomal", &objptr->abnomal);
    //type:sys_param_its_data_event_tidlane_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_data_event_tidlane_t_dumps(jwc, "reverse", &objptr->reverse);
    //type:sys_param_its_data_event_tidlane_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_data_event_tidlane_t_dumps(jwc, "speedlimit", &objptr->speedlimit);
    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[8]
    jwObj_string(jwc, "cs", objptr->cs);

    //type:sys_param_its_data_event_tidlane2_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_data_event_tidlane2_t_dumps(jwc, "notvehicle", &objptr->notvehicle);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_its_data_event_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_pid8_its_data_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_pid8_its_data_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                       = JWRITE_OK;
    sys_param_pid8_its_data_t *objptr = (sys_param_pid8_its_data_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:sys_param_its_data_lane_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_data_lane_t_dumps(jwc, "lane", &objptr->lane);
    //type:sys_param_its_data_count_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_data_count_t_dumps(jwc, "count", &objptr->count);
    //type:sys_param_its_data_speed_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_data_speed_t_dumps(jwc, "speed", &objptr->speed);
    //type:sys_param_its_data_event_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_its_data_event_t_dumps(jwc, "event", &objptr->event);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_pid8_its_data_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_vf_reflector_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_vf_reflector_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                            = JWRITE_OK;
    sys_param_vf_reflector_setup_t *objptr = (sys_param_vf_reflector_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "reflector_type", objptr->reflector_type);

    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "reflector_distance", objptr->reflector_distance);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "reflector_radius", objptr->reflector_radius);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_vf_reflector_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid9did0_vf_reflector_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid9did0_vf_reflector_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                      = JWRITE_OK;
    sys_param_sid9did0_vf_reflector_config_t *objptr = (sys_param_sid9did0_vf_reflector_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_vf_reflector_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_vf_reflector_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid9did0_vf_reflector_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_vf_server_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_vf_server_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                         = JWRITE_OK;
    sys_param_vf_server_setup_t *objptr = (sys_param_vf_server_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "server_ip", objptr->server_ip);

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "server_port", objptr->server_port);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "server_access_timeout", objptr->server_access_timeout);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "server_access_retry_cnt", objptr->server_access_retry_cnt);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "server_sendstack_size", objptr->server_sendstack_size);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "rs485_access_timeout", objptr->rs485_access_timeout);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "rs485_access_retry_cnt", objptr->rs485_access_retry_cnt);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_vf_server_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid9did1_vf_server_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid9did1_vf_server_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                   = JWRITE_OK;
    sys_param_sid9did1_vf_server_config_t *objptr = (sys_param_sid9did1_vf_server_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_vf_server_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_vf_server_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid9did1_vf_server_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_vf_relay_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_vf_relay_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                        = JWRITE_OK;
    sys_param_vf_relay_setup_t *objptr = (sys_param_vf_relay_setup_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "relay_cnt", objptr->relay_cnt);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "relay_enable");
    for(i = 0; i < 4; i++)
    {
        if(objptr->relay_enable[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->relay_enable[i]);
    }
    jwEnd(jwc);
    //type:char,  ismultidimarray : True, isarray : True, isstring : True, m_countlist:[4]
    jwObj_array(jwc, "relay_type");
    for(i = 0; i < 4; i++)
    {
        if(strlen(objptr->relay_type[i]) == 0)
            break;
        jwArr_string(jwc, objptr->relay_type[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "relay_on_time_ms");
    for(i = 0; i < 4; i++)
    {
        if(objptr->relay_on_time_ms[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->relay_on_time_ms[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[4]
    jwObj_array(jwc, "relay_on_event_type");
    for(i = 0; i < 4; i++)
    {
        if(objptr->relay_on_event_type[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->relay_on_event_type[i]);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_vf_relay_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid9did2_vf_relay_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid9did2_vf_relay_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                  = JWRITE_OK;
    sys_param_sid9did2_vf_relay_config_t *objptr = (sys_param_sid9did2_vf_relay_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_vf_relay_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_vf_relay_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid9did2_vf_relay_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_vf_ui_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_vf_ui_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                     = JWRITE_OK;
    sys_param_vf_ui_setup_t *objptr = (sys_param_vf_ui_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "th_normal", objptr->th_normal);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "th_caution", objptr->th_caution);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "th_warning", objptr->th_warning);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "marker", objptr->marker);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_vf_ui_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid9did3_vf_ui_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid9did3_vf_ui_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                               = JWRITE_OK;
    sys_param_sid9did3_vf_ui_config_t *objptr = (sys_param_sid9did3_vf_ui_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_vf_ui_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_vf_ui_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid9did3_vf_ui_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_pid9_vf_data_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_pid9_vf_data_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                      = JWRITE_OK;
    sys_param_pid9_vf_data_t *objptr = (sys_param_pid9_vf_data_t *)pvParam;

    int32_t i;
    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "cnt", objptr->cnt);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "prd", objptr->prd);
    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[25]
    jwObj_array(jwc, "dat");
    for(i = 0; i < 25; i++)
    {
        if(objptr->dat[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->dat[i]);
    }
    jwEnd(jwc);
    //type:float,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[25]
    jwObj_array(jwc, "std");
    for(i = 0; i < 25; i++)
    {
        if(objptr->std[i] <= SYS_PARAM_F32_ARR_END_VALUE)
            break;
        jwArr_float(jwc, (float)objptr->std[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[25]
    jwObj_array(jwc, "war");
    for(i = 0; i < 25; i++)
    {
        if(objptr->war[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->war[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[25]
    jwObj_array(jwc, "det");
    for(i = 0; i < 25; i++)
    {
        if(objptr->det[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->det[i]);
    }
    jwEnd(jwc);
    //type:int,  ismultidimarray : False, isarray : True, isstring : False, m_countlist:[25]
    jwObj_array(jwc, "sw");
    for(i = 0; i < 25; i++)
    {
        if(objptr->sw[i] <= SYS_PARAM_INT32_ARR_END_VALUE)
            break;
        jwArr_int32(jwc, (int)objptr->sw[i]);
    }
    jwEnd(jwc);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_pid9_vf_data_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_fcw_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_fcw_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                   = JWRITE_OK;
    sys_param_fcw_setup_t *objptr = (sys_param_fcw_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "vehicle_type", objptr->vehicle_type);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "startup_light_en", objptr->startup_light_en);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "startup_light_ontime", objptr->startup_light_ontime);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "alert_led_en", objptr->alert_led_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "alert_spk_en", objptr->alert_spk_en);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "alert_ssr_en", objptr->alert_ssr_en);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "alert_ledcolor_caution", objptr->alert_ledcolor_caution);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "alert_ledcolor_warning", objptr->alert_ledcolor_warning);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "alert_ledcolor_normal", objptr->alert_ledcolor_normal);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "alert_blink_period", objptr->alert_blink_period);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "alert_update_period", objptr->alert_update_period);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "alert_blocking_period", objptr->alert_blocking_period);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "vehiclespeed_adj_ratio", objptr->vehiclespeed_adj_ratio);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "ttc_low_sec", objptr->ttc_low_sec);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "ttc_high_sec", objptr->ttc_high_sec);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "ttc_egospeed_low_kph", objptr->ttc_egospeed_low_kph);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "ttc_egospeed_high_kph", objptr->ttc_egospeed_high_kph);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "ttc_level1_ratio", objptr->ttc_level1_ratio);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "ttc_level2_ratio", objptr->ttc_level2_ratio);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "lane_left_m", objptr->lane_left_m);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "lane_right_m", objptr->lane_right_m);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "lane_range_m", objptr->lane_range_m);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "egospeed_min_kph", objptr->egospeed_min_kph);
    //type:float,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_float(jwc, "oncomming_th_kph", objptr->oncomming_th_kph);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_fcw_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid10did0_fcw_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid10did0_fcw_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                              = JWRITE_OK;
    sys_param_sid10did0_fcw_config_t *objptr = (sys_param_sid10did0_fcw_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_fcw_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_fcw_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid10did0_fcw_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_fcwtest_setup_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_fcwtest_setup_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                       = JWRITE_OK;
    sys_param_fcwtest_setup_t *objptr = (sys_param_fcwtest_setup_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "test_fcw_event_level1", objptr->test_fcw_event_level1);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "test_fcw_event_level2", objptr->test_fcw_event_level2);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "test_jctbox_led", objptr->test_jctbox_led);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "test_jctbox_spk", objptr->test_jctbox_spk);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "test_jctbox_ssr", objptr->test_jctbox_ssr);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "test_tbd0", objptr->test_tbd0);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "test_tbd1", objptr->test_tbd1);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "test_tbd2", objptr->test_tbd2);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "test_tbd3", objptr->test_tbd3);
    //type:unsigned_char,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_bool(jwc, "test_tbd4", objptr->test_tbd4);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_fcwtest_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sid10did1_fcwtest_config_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sid10did1_fcwtest_config_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                  = JWRITE_OK;
    sys_param_sid10did1_fcwtest_config_t *objptr = (sys_param_sid10did1_fcwtest_config_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "sid", objptr->sid);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "did", objptr->did);
    //type:sys_param_fcwtest_setup_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_fcwtest_setup_t_dumps(jwc, "setup", &objptr->setup);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sid10did1_fcwtest_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_junctionbox_param_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_junctionbox_param_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                           = JWRITE_OK;
    sys_param_junctionbox_param_t *objptr = (sys_param_junctionbox_param_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "r", objptr->r);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "g", objptr->g);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "b", objptr->b);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "spk", objptr->spk);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "ssra", objptr->ssra);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "ssrb", objptr->ssrb);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_junctionbox_param_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_junctionbox_ctrl_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_junctionbox_ctrl_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                          = JWRITE_OK;
    sys_param_junctionbox_ctrl_t *objptr = (sys_param_junctionbox_ctrl_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "cmd", objptr->cmd);

    //type:sys_param_junctionbox_param_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_junctionbox_param_t_dumps(jwc, "param", &objptr->param);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_junctionbox_ctrl_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_system_status_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_system_status_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                       = JWRITE_OK;
    sys_param_system_status_t *objptr = (sys_param_system_status_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "devuid", objptr->devuid);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "serialnumber", objptr->serialnumber);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "swappname", objptr->swappname);

    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[32]
    jwObj_string(jwc, "swversion", objptr->swversion);

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "swdate", objptr->swdate);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "swtime", objptr->swtime);
    //type:sys_param_sid0did0_systembase_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did0_systembase_config_t_dumps(jwc, "sid0did0_systembase_config", &objptr->sid0did0_systembase_config);
    //type:sys_param_sid0did1_datetime_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did1_datetime_config_t_dumps(jwc, "sid0did1_datetime_config", &objptr->sid0did1_datetime_config);
    //type:sys_param_sid0did2_security_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did2_security_config_t_dumps(jwc, "sid0did2_security_config", &objptr->sid0did2_security_config);
    //type:sys_param_sid0did4_infra_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did4_infra_config_t_dumps(jwc, "sid0did4_infra_config", &objptr->sid0did4_infra_config);
    //type:sys_param_sid0did5_serialnumber_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did5_serialnumber_config_t_dumps(jwc, "sid0did5_serialnumber_config", &objptr->sid0did5_serialnumber_config);
    //type:sys_param_sid0did6_location_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did6_location_config_t_dumps(jwc, "sid0did6_location_config", &objptr->sid0did6_location_config);
    //type:sys_param_sid0did8_rs485_protocol_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did8_rs485_protocol_config_t_dumps(jwc, "sid0did8_rs485_protocol_config", &objptr->sid0did8_rs485_protocol_config);
    //type:sys_param_sid0did10_rsp_eol_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did10_rsp_eol_config_t_dumps(jwc, "sid0did10_rsp_eol_config", &objptr->sid0did10_rsp_eol_config);
    //type:sys_param_sid0did11_rsp_install_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did11_rsp_install_config_t_dumps(jwc, "sid0did11_rsp_install_config", &objptr->sid0did11_rsp_install_config);
    //type:sys_param_sid0did12_rsm_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did12_rsm_config_t_dumps(jwc, "sid0did12_rsm_config", &objptr->sid0did12_rsm_config);
    //type:sys_param_sid0did13_rsptrk_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did13_rsptrk_config_t_dumps(jwc, "sid0did13_rsptrk_config", &objptr->sid0did13_rsptrk_config);
    //type:sys_param_sid0did200_app_packet_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did200_app_packet_config_t_dumps(jwc, "sid0did200_app_packet_config", &objptr->sid0did200_app_packet_config);
    //type:sys_param_sid8did0_its_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid8did0_its_config_t_dumps(jwc, "sid8did0_its_config", &objptr->sid8did0_its_config);
    //type:sys_param_sid8did1_its_relay_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid8did1_its_relay_config_t_dumps(jwc, "sid8did1_its_relay_config", &objptr->sid8did1_its_relay_config);
    //type:sys_param_sid8did2_its_align_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid8did2_its_align_config_t_dumps(jwc, "sid8did2_its_align_config", &objptr->sid8did2_its_align_config);
    //type:sys_param_sid8did10_its_testmode_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid8did10_its_testmode_config_t_dumps(jwc, "sid8did10_its_testmode_config", &objptr->sid8did10_its_testmode_config);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_system_status_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/******************************************************************************
 * function name : sys_param_sidxdidx_configinfo_packing_t_dumps
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
static int32_t sys_param_sidxdidx_configinfo_packing_t_dumps(struct jWriteControl *jwc, char *objname, void *pvParam)
{
    int32_t err                                     = JWRITE_OK;
    sys_param_sidxdidx_configinfo_packing_t *objptr = (sys_param_sidxdidx_configinfo_packing_t *)pvParam;

    if(objname[0] != 0)
    {
        jwObj_object(jwc, objname);
    }

    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "data_start_marker", objptr->data_start_marker);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "param_version", objptr->param_version);
    //type:char,  ismultidimarray : False, isarray : True, isstring : True, m_countlist:[36]
    jwObj_string(jwc, "guidstr", objptr->guidstr);

    //type:sys_param_sid0did0_systembase_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did0_systembase_config_t_dumps(jwc, "sid0did0_systembase_config", &objptr->sid0did0_systembase_config);
    //type:sys_param_sid0did1_datetime_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did1_datetime_config_t_dumps(jwc, "sid0did1_datetime_config", &objptr->sid0did1_datetime_config);
    //type:sys_param_sid0did2_security_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did2_security_config_t_dumps(jwc, "sid0did2_security_config", &objptr->sid0did2_security_config);
    //type:sys_param_sid0did3_network_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did3_network_config_t_dumps(jwc, "sid0did3_network_config", &objptr->sid0did3_network_config);
    //type:sys_param_sid0did4_infra_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did4_infra_config_t_dumps(jwc, "sid0did4_infra_config", &objptr->sid0did4_infra_config);
    //type:sys_param_sid0did5_serialnumber_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did5_serialnumber_config_t_dumps(jwc, "sid0did5_serialnumber_config", &objptr->sid0did5_serialnumber_config);
    //type:sys_param_sid0did6_location_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did6_location_config_t_dumps(jwc, "sid0did6_location_config", &objptr->sid0did6_location_config);
    //type:sys_param_sid0did7_jctbox_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did7_jctbox_config_t_dumps(jwc, "sid0did7_jctbox_config", &objptr->sid0did7_jctbox_config);
    //type:sys_param_sid0did8_rs485_protocol_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did8_rs485_protocol_config_t_dumps(jwc, "sid0did8_rs485_protocol_config", &objptr->sid0did8_rs485_protocol_config);
    //type:sys_param_sid0did9_camera_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did9_camera_config_t_dumps(jwc, "sid0did9_camera_config", &objptr->sid0did9_camera_config);
    //type:sys_param_sid0did10_rsp_eol_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did10_rsp_eol_config_t_dumps(jwc, "sid0did10_rsp_eol_config", &objptr->sid0did10_rsp_eol_config);
    //type:sys_param_sid0did11_rsp_install_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did11_rsp_install_config_t_dumps(jwc, "sid0did11_rsp_install_config", &objptr->sid0did11_rsp_install_config);
    //type:sys_param_sid0did12_rsm_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did12_rsm_config_t_dumps(jwc, "sid0did12_rsm_config", &objptr->sid0did12_rsm_config);
    //type:sys_param_sid0did13_rsptrk_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did13_rsptrk_config_t_dumps(jwc, "sid0did13_rsptrk_config", &objptr->sid0did13_rsptrk_config);
    //type:sys_param_sid0did30_rfictx_select_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did30_rfictx_select_config_t_dumps(jwc, "sid0did30_rfictx_select_config", &objptr->sid0did30_rfictx_select_config);
    //type:sys_param_sid0did31_rfictx_bgt24at2_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did31_rfictx_bgt24at2_config_t_dumps(jwc, "sid0did31_rfictx_bgt24at2_config", &objptr->sid0did31_rfictx_bgt24at2_config);
    //type:sys_param_sid0did40_rficrx_select_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did40_rficrx_select_config_t_dumps(jwc, "sid0did40_rficrx_select_config", &objptr->sid0did40_rficrx_select_config);
    //type:sys_param_sid0did41_rficrx_bgt24ar4_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did41_rficrx_bgt24ar4_config_t_dumps(jwc, "sid0did41_rficrx_bgt24ar4_config", &objptr->sid0did41_rficrx_bgt24ar4_config);
    //type:sys_param_sid0did50_pll_select_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did50_pll_select_config_t_dumps(jwc, "sid0did50_pll_select_config", &objptr->sid0did50_pll_select_config);
    //type:sys_param_sid0did51_pll_lmx2491_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did51_pll_lmx2491_config_t_dumps(jwc, "sid0did51_pll_lmx2491_config", &objptr->sid0did51_pll_lmx2491_config);
    //type:sys_param_sid0did60_adc_select_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did60_adc_select_config_t_dumps(jwc, "sid0did60_adc_select_config", &objptr->sid0did60_adc_select_config);
    //type:sys_param_sid0did61_adc_adar7251_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did61_adc_adar7251_config_t_dumps(jwc, "sid0did61_adc_adar7251_config", &objptr->sid0did61_adc_adar7251_config);
    //type:sys_param_sid0did62_adc_max11043_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did62_adc_max11043_config_t_dumps(jwc, "sid0did62_adc_max11043_config", &objptr->sid0did62_adc_max11043_config);
    //type:sys_param_sid0did200_app_packet_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid0did200_app_packet_config_t_dumps(jwc, "sid0did200_app_packet_config", &objptr->sid0did200_app_packet_config);
    //type:sys_param_sid6did0_candrv_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid6did0_candrv_config_t_dumps(jwc, "sid6did0_candrv_config", &objptr->sid6did0_candrv_config);
    //type:sys_param_sid6did1_cansignal_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid6did1_cansignal_config_t_dumps(jwc, "sid6did1_cansignal_config", &objptr->sid6did1_cansignal_config);
    //type:sys_param_sid6did2_cantxmsg_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid6did2_cantxmsg_config_t_dumps(jwc, "sid6did2_cantxmsg_config", &objptr->sid6did2_cantxmsg_config);
    //type:sys_param_sid7did0_filesystem_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid7did0_filesystem_config_t_dumps(jwc, "sid7did0_filesystem_config", &objptr->sid7did0_filesystem_config);
    //type:sys_param_sid8did0_its_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid8did0_its_config_t_dumps(jwc, "sid8did0_its_config", &objptr->sid8did0_its_config);
    //type:sys_param_sid8did1_its_relay_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid8did1_its_relay_config_t_dumps(jwc, "sid8did1_its_relay_config", &objptr->sid8did1_its_relay_config);
    //type:sys_param_sid8did2_its_align_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid8did2_its_align_config_t_dumps(jwc, "sid8did2_its_align_config", &objptr->sid8did2_its_align_config);
    //type:sys_param_sid8did10_its_testmode_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid8did10_its_testmode_config_t_dumps(jwc, "sid8did10_its_testmode_config", &objptr->sid8did10_its_testmode_config);
    //type:sys_param_sid9did0_vf_reflector_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid9did0_vf_reflector_config_t_dumps(jwc, "sid9did0_vf_reflector_config", &objptr->sid9did0_vf_reflector_config);
    //type:sys_param_sid9did1_vf_server_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid9did1_vf_server_config_t_dumps(jwc, "sid9did1_vf_server_config", &objptr->sid9did1_vf_server_config);
    //type:sys_param_sid9did2_vf_relay_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid9did2_vf_relay_config_t_dumps(jwc, "sid9did2_vf_relay_config", &objptr->sid9did2_vf_relay_config);
    //type:sys_param_sid9did3_vf_ui_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid9did3_vf_ui_config_t_dumps(jwc, "sid9did3_vf_ui_config", &objptr->sid9did3_vf_ui_config);
    //type:sys_param_sid10did0_fcw_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid10did0_fcw_config_t_dumps(jwc, "sid10did0_fcw_config", &objptr->sid10did0_fcw_config);
    //type:sys_param_sid10did1_fcwtest_config_t,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    sys_param_sid10did1_fcwtest_config_t_dumps(jwc, "sid10did1_fcwtest_config", &objptr->sid10did1_fcwtest_config);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "data_end_marker", objptr->data_end_marker);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "data_end_marker1", objptr->data_end_marker1);
    //type:int,  ismultidimarray : False, isarray : False, isstring : False, m_countlist:[1]
    jwObj_int32(jwc, "data_end_marker2", objptr->data_end_marker2);

    if(objname[0] != 0)
    {
        err = jwEnd(jwc);
        if(err != JWRITE_OK)
        {
            sys_param_log("sys_param_sidxdidx_configinfo_packing_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
            sys_param_assert(err == JWRITE_OK);
        }
    }
    return 0;
}


/*************************************************************/
/* dump json string for external  */
/*************************************************************/
/******************************************************************************
 * function name : sys_param_comm_negative_response_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_comm_negative_response_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_comm_negative_response_t *objptr = (sys_param_comm_negative_response_t *)pvParam;
    int32_t err                                = JWRITE_OK;
    int32_t jsonlen                            = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_comm_negative_response_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_comm_negative_response_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_comm_negative_response_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_common_comm_ethernet_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_common_comm_ethernet_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_common_comm_ethernet_config_t *objptr = (sys_param_common_comm_ethernet_config_t *)pvParam;
    int32_t err                                     = JWRITE_OK;
    int32_t jsonlen                                 = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_common_comm_ethernet_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_common_comm_ethernet_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_common_comm_ethernet_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_common_comm_serialcomm_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_common_comm_serialcomm_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_common_comm_serialcomm_config_t *objptr = (sys_param_common_comm_serialcomm_config_t *)pvParam;
    int32_t err                                       = JWRITE_OK;
    int32_t jsonlen                                   = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_common_comm_serialcomm_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_common_comm_serialcomm_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_common_comm_serialcomm_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_common_comm_tbd_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_common_comm_tbd_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_common_comm_tbd_config_t *objptr = (sys_param_common_comm_tbd_config_t *)pvParam;
    int32_t err                                = JWRITE_OK;
    int32_t jsonlen                            = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_common_comm_tbd_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_common_comm_tbd_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_common_comm_tbd_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_swupdate_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_swupdate_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_swupdate_config_t *objptr = (sys_param_swupdate_config_t *)pvParam;
    int32_t err                         = JWRITE_OK;
    int32_t jsonlen                     = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_swupdate_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_swupdate_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_swupdate_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_consolelog_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_consolelog_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_consolelog_config_t *objptr = (sys_param_consolelog_config_t *)pvParam;
    int32_t err                           = JWRITE_OK;
    int32_t jsonlen                       = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_consolelog_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_consolelog_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_consolelog_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_consoleudp_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_consoleudp_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_consoleudp_config_t *objptr = (sys_param_consoleudp_config_t *)pvParam;
    int32_t err                           = JWRITE_OK;
    int32_t jsonlen                       = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_consoleudp_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_consoleudp_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_consoleudp_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_system_sensortype_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_system_sensortype_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_system_sensortype_config_t *objptr = (sys_param_system_sensortype_config_t *)pvParam;
    int32_t err                                  = JWRITE_OK;
    int32_t jsonlen                              = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_system_sensortype_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_system_sensortype_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_system_sensortype_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_system_control_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_system_control_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_system_control_t *objptr = (sys_param_system_control_t *)pvParam;
    int32_t err                        = JWRITE_OK;
    int32_t jsonlen                    = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_system_control_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_system_control_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_system_control_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_logic_control_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_logic_control_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_logic_control_config_t *objptr = (sys_param_logic_control_config_t *)pvParam;
    int32_t err                              = JWRITE_OK;
    int32_t jsonlen                          = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_logic_control_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_logic_control_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_logic_control_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_system_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_system_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_system_config_t *objptr = (sys_param_system_config_t *)pvParam;
    int32_t err                       = JWRITE_OK;
    int32_t jsonlen                   = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_system_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_system_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_system_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did0_systembase_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did0_systembase_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did0_systembase_config_t *objptr = (sys_param_sid0did0_systembase_config_t *)pvParam;
    int32_t err                                    = JWRITE_OK;
    int32_t jsonlen                                = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did0_systembase_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did0_systembase_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did0_systembase_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_datetime_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_datetime_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_datetime_setup_t *objptr = (sys_param_datetime_setup_t *)pvParam;
    int32_t err                        = JWRITE_OK;
    int32_t jsonlen                    = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_datetime_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_datetime_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_datetime_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did1_datetime_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did1_datetime_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did1_datetime_config_t *objptr = (sys_param_sid0did1_datetime_config_t *)pvParam;
    int32_t err                                  = JWRITE_OK;
    int32_t jsonlen                              = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did1_datetime_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did1_datetime_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did1_datetime_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_security_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_security_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_security_setup_t *objptr = (sys_param_security_setup_t *)pvParam;
    int32_t err                        = JWRITE_OK;
    int32_t jsonlen                    = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_security_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_security_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_security_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did2_security_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did2_security_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did2_security_config_t *objptr = (sys_param_sid0did2_security_config_t *)pvParam;
    int32_t err                                  = JWRITE_OK;
    int32_t jsonlen                              = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did2_security_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did2_security_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did2_security_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did3_network_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did3_network_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did3_network_config_t *objptr = (sys_param_sid0did3_network_config_t *)pvParam;
    int32_t err                                 = JWRITE_OK;
    int32_t jsonlen                             = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did3_network_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did3_network_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did3_network_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_version_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_version_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_version_t *objptr = (sys_param_version_t *)pvParam;
    int32_t err                 = JWRITE_OK;
    int32_t jsonlen             = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_version_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_version_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_version_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_version_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_version_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_version_setup_t *objptr = (sys_param_version_setup_t *)pvParam;
    int32_t err                       = JWRITE_OK;
    int32_t jsonlen                   = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_version_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_version_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_version_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_infra_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_infra_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_infra_setup_t *objptr = (sys_param_infra_setup_t *)pvParam;
    int32_t err                     = JWRITE_OK;
    int32_t jsonlen                 = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_infra_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_infra_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_infra_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did4_infra_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did4_infra_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did4_infra_config_t *objptr = (sys_param_sid0did4_infra_config_t *)pvParam;
    int32_t err                               = JWRITE_OK;
    int32_t jsonlen                           = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did4_infra_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did4_infra_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did4_infra_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_serialnumber_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_serialnumber_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_serialnumber_setup_t *objptr = (sys_param_serialnumber_setup_t *)pvParam;
    int32_t err                            = JWRITE_OK;
    int32_t jsonlen                        = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_serialnumber_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_serialnumber_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_serialnumber_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did5_serialnumber_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did5_serialnumber_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did5_serialnumber_config_t *objptr = (sys_param_sid0did5_serialnumber_config_t *)pvParam;
    int32_t err                                      = JWRITE_OK;
    int32_t jsonlen                                  = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did5_serialnumber_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did5_serialnumber_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did5_serialnumber_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_location_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_location_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_location_t *objptr = (sys_param_location_t *)pvParam;
    int32_t err                  = JWRITE_OK;
    int32_t jsonlen              = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_location_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_location_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_location_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_gps_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_gps_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_gps_t *objptr = (sys_param_gps_t *)pvParam;
    int32_t err             = JWRITE_OK;
    int32_t jsonlen         = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_gps_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_gps_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_gps_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_location_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_location_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_location_setup_t *objptr = (sys_param_location_setup_t *)pvParam;
    int32_t err                        = JWRITE_OK;
    int32_t jsonlen                    = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_location_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_location_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_location_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did6_location_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did6_location_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did6_location_config_t *objptr = (sys_param_sid0did6_location_config_t *)pvParam;
    int32_t err                                  = JWRITE_OK;
    int32_t jsonlen                              = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did6_location_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did6_location_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did6_location_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_jctbox_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_jctbox_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_jctbox_setup_t *objptr = (sys_param_jctbox_setup_t *)pvParam;
    int32_t err                      = JWRITE_OK;
    int32_t jsonlen                  = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_jctbox_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_jctbox_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_jctbox_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did7_jctbox_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did7_jctbox_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did7_jctbox_config_t *objptr = (sys_param_sid0did7_jctbox_config_t *)pvParam;
    int32_t err                                = JWRITE_OK;
    int32_t jsonlen                            = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did7_jctbox_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did7_jctbox_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did7_jctbox_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_rs485_protocol_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rs485_protocol_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_rs485_protocol_setup_t *objptr = (sys_param_rs485_protocol_setup_t *)pvParam;
    int32_t err                              = JWRITE_OK;
    int32_t jsonlen                          = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_rs485_protocol_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_rs485_protocol_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_rs485_protocol_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did8_rs485_protocol_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did8_rs485_protocol_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did8_rs485_protocol_config_t *objptr = (sys_param_sid0did8_rs485_protocol_config_t *)pvParam;
    int32_t err                                        = JWRITE_OK;
    int32_t jsonlen                                    = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did8_rs485_protocol_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did8_rs485_protocol_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did8_rs485_protocol_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_cameractrl_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_cameractrl_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_cameractrl_setup_t *objptr = (sys_param_cameractrl_setup_t *)pvParam;
    int32_t err                          = JWRITE_OK;
    int32_t jsonlen                      = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_cameractrl_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_cameractrl_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_cameractrl_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_camera_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_camera_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_camera_setup_t *objptr = (sys_param_camera_setup_t *)pvParam;
    int32_t err                      = JWRITE_OK;
    int32_t jsonlen                  = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_camera_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_camera_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_camera_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did9_camera_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did9_camera_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did9_camera_config_t *objptr = (sys_param_sid0did9_camera_config_t *)pvParam;
    int32_t err                                = JWRITE_OK;
    int32_t jsonlen                            = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did9_camera_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did9_camera_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did9_camera_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_rsp_eol_phasecal_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rsp_eol_phasecal_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_rsp_eol_phasecal_t *objptr = (sys_param_rsp_eol_phasecal_t *)pvParam;
    int32_t err                          = JWRITE_OK;
    int32_t jsonlen                      = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_rsp_eol_phasecal_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_rsp_eol_phasecal_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_rsp_eol_phasecal_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_rsp_eol_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rsp_eol_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_rsp_eol_setup_t *objptr = (sys_param_rsp_eol_setup_t *)pvParam;
    int32_t err                       = JWRITE_OK;
    int32_t jsonlen                   = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_rsp_eol_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_rsp_eol_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_rsp_eol_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did10_rsp_eol_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did10_rsp_eol_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did10_rsp_eol_config_t *objptr = (sys_param_sid0did10_rsp_eol_config_t *)pvParam;
    int32_t err                                  = JWRITE_OK;
    int32_t jsonlen                              = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did10_rsp_eol_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did10_rsp_eol_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did10_rsp_eol_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_rsp_install_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rsp_install_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_rsp_install_setup_t *objptr = (sys_param_rsp_install_setup_t *)pvParam;
    int32_t err                           = JWRITE_OK;
    int32_t jsonlen                       = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_rsp_install_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_rsp_install_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_rsp_install_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did11_rsp_install_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did11_rsp_install_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did11_rsp_install_config_t *objptr = (sys_param_sid0did11_rsp_install_config_t *)pvParam;
    int32_t err                                      = JWRITE_OK;
    int32_t jsonlen                                  = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did11_rsp_install_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did11_rsp_install_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did11_rsp_install_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_rsm_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rsm_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_rsm_setup_t *objptr = (sys_param_rsm_setup_t *)pvParam;
    int32_t err                   = JWRITE_OK;
    int32_t jsonlen               = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_rsm_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_rsm_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_rsm_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did12_rsm_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did12_rsm_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did12_rsm_config_t *objptr = (sys_param_sid0did12_rsm_config_t *)pvParam;
    int32_t err                              = JWRITE_OK;
    int32_t jsonlen                          = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did12_rsm_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did12_rsm_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did12_rsm_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_rsptrk_posttune_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rsptrk_posttune_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_rsptrk_posttune_t *objptr = (sys_param_rsptrk_posttune_t *)pvParam;
    int32_t err                         = JWRITE_OK;
    int32_t jsonlen                     = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_rsptrk_posttune_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_rsptrk_posttune_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_rsptrk_posttune_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_rsptrk_trktune_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rsptrk_trktune_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_rsptrk_trktune_t *objptr = (sys_param_rsptrk_trktune_t *)pvParam;
    int32_t err                        = JWRITE_OK;
    int32_t jsonlen                    = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_rsptrk_trktune_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_rsptrk_trktune_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_rsptrk_trktune_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_rsptrk_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rsptrk_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_rsptrk_setup_t *objptr = (sys_param_rsptrk_setup_t *)pvParam;
    int32_t err                      = JWRITE_OK;
    int32_t jsonlen                  = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_rsptrk_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_rsptrk_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_rsptrk_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did13_rsptrk_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did13_rsptrk_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did13_rsptrk_config_t *objptr = (sys_param_sid0did13_rsptrk_config_t *)pvParam;
    int32_t err                                 = JWRITE_OK;
    int32_t jsonlen                             = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did13_rsptrk_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did13_rsptrk_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did13_rsptrk_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_rfictx_select_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rfictx_select_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_rfictx_select_t *objptr = (sys_param_rfictx_select_t *)pvParam;
    int32_t err                       = JWRITE_OK;
    int32_t jsonlen                   = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_rfictx_select_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_rfictx_select_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_rfictx_select_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did30_rfictx_select_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did30_rfictx_select_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did30_rfictx_select_config_t *objptr = (sys_param_sid0did30_rfictx_select_config_t *)pvParam;
    int32_t err                                        = JWRITE_OK;
    int32_t jsonlen                                    = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did30_rfictx_select_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did30_rfictx_select_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did30_rfictx_select_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_rfictx_bgt24at2_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rfictx_bgt24at2_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_rfictx_bgt24at2_setup_t *objptr = (sys_param_rfictx_bgt24at2_setup_t *)pvParam;
    int32_t err                               = JWRITE_OK;
    int32_t jsonlen                           = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_rfictx_bgt24at2_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_rfictx_bgt24at2_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_rfictx_bgt24at2_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did31_rfictx_bgt24at2_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did31_rfictx_bgt24at2_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did31_rfictx_bgt24at2_config_t *objptr = (sys_param_sid0did31_rfictx_bgt24at2_config_t *)pvParam;
    int32_t err                                          = JWRITE_OK;
    int32_t jsonlen                                      = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did31_rfictx_bgt24at2_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did31_rfictx_bgt24at2_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did31_rfictx_bgt24at2_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_rficrx_select_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rficrx_select_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_rficrx_select_t *objptr = (sys_param_rficrx_select_t *)pvParam;
    int32_t err                       = JWRITE_OK;
    int32_t jsonlen                   = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_rficrx_select_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_rficrx_select_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_rficrx_select_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did40_rficrx_select_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did40_rficrx_select_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did40_rficrx_select_config_t *objptr = (sys_param_sid0did40_rficrx_select_config_t *)pvParam;
    int32_t err                                        = JWRITE_OK;
    int32_t jsonlen                                    = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did40_rficrx_select_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did40_rficrx_select_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did40_rficrx_select_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_rficrx_bgt24ar4_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_rficrx_bgt24ar4_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_rficrx_bgt24ar4_setup_t *objptr = (sys_param_rficrx_bgt24ar4_setup_t *)pvParam;
    int32_t err                               = JWRITE_OK;
    int32_t jsonlen                           = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_rficrx_bgt24ar4_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_rficrx_bgt24ar4_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_rficrx_bgt24ar4_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did41_rficrx_bgt24ar4_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did41_rficrx_bgt24ar4_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did41_rficrx_bgt24ar4_config_t *objptr = (sys_param_sid0did41_rficrx_bgt24ar4_config_t *)pvParam;
    int32_t err                                          = JWRITE_OK;
    int32_t jsonlen                                      = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did41_rficrx_bgt24ar4_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did41_rficrx_bgt24ar4_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did41_rficrx_bgt24ar4_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_pll_select_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_pll_select_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_pll_select_t *objptr = (sys_param_pll_select_t *)pvParam;
    int32_t err                    = JWRITE_OK;
    int32_t jsonlen                = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_pll_select_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_pll_select_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_pll_select_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did50_pll_select_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did50_pll_select_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did50_pll_select_config_t *objptr = (sys_param_sid0did50_pll_select_config_t *)pvParam;
    int32_t err                                     = JWRITE_OK;
    int32_t jsonlen                                 = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did50_pll_select_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did50_pll_select_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did50_pll_select_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_pll_lmx2491_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_pll_lmx2491_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_pll_lmx2491_setup_t *objptr = (sys_param_pll_lmx2491_setup_t *)pvParam;
    int32_t err                           = JWRITE_OK;
    int32_t jsonlen                       = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_pll_lmx2491_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_pll_lmx2491_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_pll_lmx2491_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did51_pll_lmx2491_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did51_pll_lmx2491_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did51_pll_lmx2491_config_t *objptr = (sys_param_sid0did51_pll_lmx2491_config_t *)pvParam;
    int32_t err                                      = JWRITE_OK;
    int32_t jsonlen                                  = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did51_pll_lmx2491_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did51_pll_lmx2491_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did51_pll_lmx2491_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_adc_select_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_adc_select_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_adc_select_t *objptr = (sys_param_adc_select_t *)pvParam;
    int32_t err                    = JWRITE_OK;
    int32_t jsonlen                = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_adc_select_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_adc_select_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_adc_select_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did60_adc_select_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did60_adc_select_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did60_adc_select_config_t *objptr = (sys_param_sid0did60_adc_select_config_t *)pvParam;
    int32_t err                                     = JWRITE_OK;
    int32_t jsonlen                                 = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did60_adc_select_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did60_adc_select_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did60_adc_select_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_adc_adar7251_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_adc_adar7251_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_adc_adar7251_setup_t *objptr = (sys_param_adc_adar7251_setup_t *)pvParam;
    int32_t err                            = JWRITE_OK;
    int32_t jsonlen                        = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_adc_adar7251_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_adc_adar7251_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_adc_adar7251_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did61_adc_adar7251_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did61_adc_adar7251_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did61_adc_adar7251_config_t *objptr = (sys_param_sid0did61_adc_adar7251_config_t *)pvParam;
    int32_t err                                       = JWRITE_OK;
    int32_t jsonlen                                   = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did61_adc_adar7251_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did61_adc_adar7251_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did61_adc_adar7251_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_adc_max11043_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_adc_max11043_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_adc_max11043_setup_t *objptr = (sys_param_adc_max11043_setup_t *)pvParam;
    int32_t err                            = JWRITE_OK;
    int32_t jsonlen                        = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_adc_max11043_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_adc_max11043_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_adc_max11043_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did62_adc_max11043_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did62_adc_max11043_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did62_adc_max11043_config_t *objptr = (sys_param_sid0did62_adc_max11043_config_t *)pvParam;
    int32_t err                                       = JWRITE_OK;
    int32_t jsonlen                                   = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did62_adc_max11043_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did62_adc_max11043_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did62_adc_max11043_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_app_packet_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_app_packet_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_app_packet_t *objptr = (sys_param_app_packet_t *)pvParam;
    int32_t err                    = JWRITE_OK;
    int32_t jsonlen                = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_app_packet_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_app_packet_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_app_packet_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_app_packet_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_app_packet_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_app_packet_setup_t *objptr = (sys_param_app_packet_setup_t *)pvParam;
    int32_t err                          = JWRITE_OK;
    int32_t jsonlen                      = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_app_packet_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_app_packet_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_app_packet_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid0did200_app_packet_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid0did200_app_packet_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid0did200_app_packet_config_t *objptr = (sys_param_sid0did200_app_packet_config_t *)pvParam;
    int32_t err                                      = JWRITE_OK;
    int32_t jsonlen                                  = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid0did200_app_packet_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid0did200_app_packet_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid0did200_app_packet_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_candrv_channel_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_candrv_channel_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_candrv_channel_setup_t *objptr = (sys_param_candrv_channel_setup_t *)pvParam;
    int32_t err                              = JWRITE_OK;
    int32_t jsonlen                          = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_candrv_channel_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_candrv_channel_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_candrv_channel_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_candrv_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_candrv_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_candrv_setup_t *objptr = (sys_param_candrv_setup_t *)pvParam;
    int32_t err                      = JWRITE_OK;
    int32_t jsonlen                  = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_candrv_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_candrv_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_candrv_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid6did0_candrv_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid6did0_candrv_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid6did0_candrv_config_t *objptr = (sys_param_sid6did0_candrv_config_t *)pvParam;
    int32_t err                                = JWRITE_OK;
    int32_t jsonlen                            = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid6did0_candrv_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid6did0_candrv_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid6did0_candrv_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_cansignal_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_cansignal_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_cansignal_t *objptr = (sys_param_cansignal_t *)pvParam;
    int32_t err                   = JWRITE_OK;
    int32_t jsonlen               = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_cansignal_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_cansignal_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_cansignal_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_cansignal_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_cansignal_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_cansignal_setup_t *objptr = (sys_param_cansignal_setup_t *)pvParam;
    int32_t err                         = JWRITE_OK;
    int32_t jsonlen                     = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_cansignal_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_cansignal_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_cansignal_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid6did1_cansignal_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid6did1_cansignal_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid6did1_cansignal_config_t *objptr = (sys_param_sid6did1_cansignal_config_t *)pvParam;
    int32_t err                                   = JWRITE_OK;
    int32_t jsonlen                               = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid6did1_cansignal_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid6did1_cansignal_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid6did1_cansignal_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_can_txmsg_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_can_txmsg_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_can_txmsg_t *objptr = (sys_param_can_txmsg_t *)pvParam;
    int32_t err                   = JWRITE_OK;
    int32_t jsonlen               = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_can_txmsg_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_can_txmsg_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_can_txmsg_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_cantxmsg_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_cantxmsg_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_cantxmsg_setup_t *objptr = (sys_param_cantxmsg_setup_t *)pvParam;
    int32_t err                        = JWRITE_OK;
    int32_t jsonlen                    = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_cantxmsg_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_cantxmsg_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_cantxmsg_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid6did2_cantxmsg_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid6did2_cantxmsg_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid6did2_cantxmsg_config_t *objptr = (sys_param_sid6did2_cantxmsg_config_t *)pvParam;
    int32_t err                                  = JWRITE_OK;
    int32_t jsonlen                              = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid6did2_cantxmsg_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid6did2_cantxmsg_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid6did2_cantxmsg_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_filesystem_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_filesystem_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_filesystem_setup_t *objptr = (sys_param_filesystem_setup_t *)pvParam;
    int32_t err                          = JWRITE_OK;
    int32_t jsonlen                      = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_filesystem_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_filesystem_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_filesystem_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid7did0_filesystem_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid7did0_filesystem_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid7did0_filesystem_config_t *objptr = (sys_param_sid7did0_filesystem_config_t *)pvParam;
    int32_t err                                    = JWRITE_OK;
    int32_t jsonlen                                = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid7did0_filesystem_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid7did0_filesystem_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid7did0_filesystem_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_status_timestamp_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_status_timestamp_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_status_timestamp_t *objptr = (sys_param_status_timestamp_t *)pvParam;
    int32_t err                          = JWRITE_OK;
    int32_t jsonlen                      = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_status_timestamp_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_status_timestamp_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_status_timestamp_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_status_data_position_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_status_data_position_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_status_data_position_t *objptr = (sys_param_status_data_position_t *)pvParam;
    int32_t err                              = JWRITE_OK;
    int32_t jsonlen                          = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_status_data_position_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_status_data_position_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_status_data_position_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_status_data_ecuinfo_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_status_data_ecuinfo_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_status_data_ecuinfo_t *objptr = (sys_param_status_data_ecuinfo_t *)pvParam;
    int32_t err                             = JWRITE_OK;
    int32_t jsonlen                         = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_status_data_ecuinfo_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_status_data_ecuinfo_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_status_data_ecuinfo_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_status_data_gps_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_status_data_gps_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_status_data_gps_t *objptr = (sys_param_status_data_gps_t *)pvParam;
    int32_t err                         = JWRITE_OK;
    int32_t jsonlen                     = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_status_data_gps_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_status_data_gps_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_status_data_gps_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_pid0_status_data_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_pid0_status_data_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_pid0_status_data_t *objptr = (sys_param_pid0_status_data_t *)pvParam;
    int32_t err                          = JWRITE_OK;
    int32_t jsonlen                      = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_pid0_status_data_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_pid0_status_data_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_pid0_status_data_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_setup_timeschedule_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_setup_timeschedule_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_setup_timeschedule_t *objptr = (sys_param_its_setup_timeschedule_t *)pvParam;
    int32_t err                                = JWRITE_OK;
    int32_t jsonlen                            = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_setup_timeschedule_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_setup_timeschedule_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_setup_timeschedule_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_setup_laneinfo_lane_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_setup_laneinfo_lane_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_setup_laneinfo_lane_t *objptr = (sys_param_its_setup_laneinfo_lane_t *)pvParam;
    int32_t err                                 = JWRITE_OK;
    int32_t jsonlen                             = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_setup_laneinfo_lane_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_setup_laneinfo_lane_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_setup_laneinfo_lane_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_setup_zone_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_setup_zone_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_setup_zone_t *objptr = (sys_param_its_setup_zone_t *)pvParam;
    int32_t err                        = JWRITE_OK;
    int32_t jsonlen                    = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_setup_zone_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_setup_zone_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_setup_zone_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_setup_hotspotzone_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_setup_hotspotzone_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_setup_hotspotzone_t *objptr = (sys_param_its_setup_hotspotzone_t *)pvParam;
    int32_t err                               = JWRITE_OK;
    int32_t jsonlen                           = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_setup_hotspotzone_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_setup_hotspotzone_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_setup_hotspotzone_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_setup_laneinfo_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_setup_laneinfo_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_setup_laneinfo_t *objptr = (sys_param_its_setup_laneinfo_t *)pvParam;
    int32_t err                            = JWRITE_OK;
    int32_t jsonlen                        = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_setup_laneinfo_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_setup_laneinfo_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_setup_laneinfo_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_setup_area_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_setup_area_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_setup_area_t *objptr = (sys_param_its_setup_area_t *)pvParam;
    int32_t err                        = JWRITE_OK;
    int32_t jsonlen                    = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_setup_area_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_setup_area_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_setup_area_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_setup_blackout_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_setup_blackout_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_setup_blackout_t *objptr = (sys_param_its_setup_blackout_t *)pvParam;
    int32_t err                            = JWRITE_OK;
    int32_t jsonlen                        = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_setup_blackout_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_setup_blackout_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_setup_blackout_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_setup_speedlimit_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_setup_speedlimit_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_setup_speedlimit_t *objptr = (sys_param_its_setup_speedlimit_t *)pvParam;
    int32_t err                              = JWRITE_OK;
    int32_t jsonlen                          = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_setup_speedlimit_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_setup_speedlimit_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_setup_speedlimit_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_setup_misc_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_setup_misc_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_setup_misc_t *objptr = (sys_param_its_setup_misc_t *)pvParam;
    int32_t err                        = JWRITE_OK;
    int32_t jsonlen                    = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_setup_misc_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_setup_misc_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_setup_misc_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_setup_t *objptr = (sys_param_its_setup_t *)pvParam;
    int32_t err                   = JWRITE_OK;
    int32_t jsonlen               = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid8did0_its_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid8did0_its_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid8did0_its_config_t *objptr = (sys_param_sid8did0_its_config_t *)pvParam;
    int32_t err                             = JWRITE_OK;
    int32_t jsonlen                         = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid8did0_its_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid8did0_its_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid8did0_its_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_relay_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_relay_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_relay_t *objptr = (sys_param_its_relay_t *)pvParam;
    int32_t err                   = JWRITE_OK;
    int32_t jsonlen               = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_relay_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_relay_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_relay_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_device_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_device_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_device_setup_t *objptr = (sys_param_its_device_setup_t *)pvParam;
    int32_t err                          = JWRITE_OK;
    int32_t jsonlen                      = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_device_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_device_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_device_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid8did1_its_relay_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid8did1_its_relay_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid8did1_its_relay_config_t *objptr = (sys_param_sid8did1_its_relay_config_t *)pvParam;
    int32_t err                                   = JWRITE_OK;
    int32_t jsonlen                               = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid8did1_its_relay_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid8did1_its_relay_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid8did1_its_relay_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_alignment_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_alignment_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_alignment_setup_t *objptr = (sys_param_its_alignment_setup_t *)pvParam;
    int32_t err                             = JWRITE_OK;
    int32_t jsonlen                         = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_alignment_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_alignment_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_alignment_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid8did2_its_align_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid8did2_its_align_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid8did2_its_align_config_t *objptr = (sys_param_sid8did2_its_align_config_t *)pvParam;
    int32_t err                                   = JWRITE_OK;
    int32_t jsonlen                               = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid8did2_its_align_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid8did2_its_align_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid8did2_its_align_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_testmode_speedlimit_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_testmode_speedlimit_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_testmode_speedlimit_t *objptr = (sys_param_its_testmode_speedlimit_t *)pvParam;
    int32_t err                                 = JWRITE_OK;
    int32_t jsonlen                             = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_testmode_speedlimit_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_testmode_speedlimit_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_testmode_speedlimit_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_testmode_trigger_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_testmode_trigger_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_testmode_trigger_t *objptr = (sys_param_its_testmode_trigger_t *)pvParam;
    int32_t err                              = JWRITE_OK;
    int32_t jsonlen                          = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_testmode_trigger_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_testmode_trigger_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_testmode_trigger_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_testmode_hotspotzone_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_testmode_hotspotzone_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_testmode_hotspotzone_t *objptr = (sys_param_its_testmode_hotspotzone_t *)pvParam;
    int32_t err                                  = JWRITE_OK;
    int32_t jsonlen                              = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_testmode_hotspotzone_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_testmode_hotspotzone_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_testmode_hotspotzone_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_testmode_image_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_testmode_image_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_testmode_image_t *objptr = (sys_param_its_testmode_image_t *)pvParam;
    int32_t err                            = JWRITE_OK;
    int32_t jsonlen                        = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_testmode_image_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_testmode_image_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_testmode_image_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_testmode_misc_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_testmode_misc_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_testmode_misc_t *objptr = (sys_param_its_testmode_misc_t *)pvParam;
    int32_t err                           = JWRITE_OK;
    int32_t jsonlen                       = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_testmode_misc_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_testmode_misc_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_testmode_misc_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_testmode_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_testmode_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_testmode_setup_t *objptr = (sys_param_its_testmode_setup_t *)pvParam;
    int32_t err                            = JWRITE_OK;
    int32_t jsonlen                        = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_testmode_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_testmode_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_testmode_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid8did10_its_testmode_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid8did10_its_testmode_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid8did10_its_testmode_config_t *objptr = (sys_param_sid8did10_its_testmode_config_t *)pvParam;
    int32_t err                                       = JWRITE_OK;
    int32_t jsonlen                                   = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid8did10_its_testmode_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid8did10_its_testmode_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid8did10_its_testmode_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_data_lane_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_data_lane_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_data_lane_t *objptr = (sys_param_its_data_lane_t *)pvParam;
    int32_t err                       = JWRITE_OK;
    int32_t jsonlen                   = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_data_lane_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_data_lane_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_data_lane_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_data_count_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_data_count_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_data_count_t *objptr = (sys_param_its_data_count_t *)pvParam;
    int32_t err                        = JWRITE_OK;
    int32_t jsonlen                    = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_data_count_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_data_count_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_data_count_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_data_speed_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_data_speed_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_data_speed_t *objptr = (sys_param_its_data_speed_t *)pvParam;
    int32_t err                        = JWRITE_OK;
    int32_t jsonlen                    = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_data_speed_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_data_speed_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_data_speed_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_data_event_tidlane_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_data_event_tidlane_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_data_event_tidlane_t *objptr = (sys_param_its_data_event_tidlane_t *)pvParam;
    int32_t err                                = JWRITE_OK;
    int32_t jsonlen                            = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_data_event_tidlane_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_data_event_tidlane_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_data_event_tidlane_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_data_event_tidlane2_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_data_event_tidlane2_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_data_event_tidlane2_t *objptr = (sys_param_its_data_event_tidlane2_t *)pvParam;
    int32_t err                                 = JWRITE_OK;
    int32_t jsonlen                             = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_data_event_tidlane2_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_data_event_tidlane2_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_data_event_tidlane2_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_its_data_event_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_its_data_event_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_its_data_event_t *objptr = (sys_param_its_data_event_t *)pvParam;
    int32_t err                        = JWRITE_OK;
    int32_t jsonlen                    = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_its_data_event_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_its_data_event_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_its_data_event_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_pid8_its_data_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_pid8_its_data_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_pid8_its_data_t *objptr = (sys_param_pid8_its_data_t *)pvParam;
    int32_t err                       = JWRITE_OK;
    int32_t jsonlen                   = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_pid8_its_data_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_pid8_its_data_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_pid8_its_data_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_vf_reflector_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_vf_reflector_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_vf_reflector_setup_t *objptr = (sys_param_vf_reflector_setup_t *)pvParam;
    int32_t err                            = JWRITE_OK;
    int32_t jsonlen                        = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_vf_reflector_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_vf_reflector_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_vf_reflector_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid9did0_vf_reflector_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid9did0_vf_reflector_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid9did0_vf_reflector_config_t *objptr = (sys_param_sid9did0_vf_reflector_config_t *)pvParam;
    int32_t err                                      = JWRITE_OK;
    int32_t jsonlen                                  = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid9did0_vf_reflector_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid9did0_vf_reflector_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid9did0_vf_reflector_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_vf_server_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_vf_server_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_vf_server_setup_t *objptr = (sys_param_vf_server_setup_t *)pvParam;
    int32_t err                         = JWRITE_OK;
    int32_t jsonlen                     = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_vf_server_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_vf_server_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_vf_server_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid9did1_vf_server_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid9did1_vf_server_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid9did1_vf_server_config_t *objptr = (sys_param_sid9did1_vf_server_config_t *)pvParam;
    int32_t err                                   = JWRITE_OK;
    int32_t jsonlen                               = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid9did1_vf_server_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid9did1_vf_server_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid9did1_vf_server_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_vf_relay_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_vf_relay_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_vf_relay_setup_t *objptr = (sys_param_vf_relay_setup_t *)pvParam;
    int32_t err                        = JWRITE_OK;
    int32_t jsonlen                    = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_vf_relay_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_vf_relay_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_vf_relay_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid9did2_vf_relay_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid9did2_vf_relay_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid9did2_vf_relay_config_t *objptr = (sys_param_sid9did2_vf_relay_config_t *)pvParam;
    int32_t err                                  = JWRITE_OK;
    int32_t jsonlen                              = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid9did2_vf_relay_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid9did2_vf_relay_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid9did2_vf_relay_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_vf_ui_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_vf_ui_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_vf_ui_setup_t *objptr = (sys_param_vf_ui_setup_t *)pvParam;
    int32_t err                     = JWRITE_OK;
    int32_t jsonlen                 = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_vf_ui_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_vf_ui_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_vf_ui_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid9did3_vf_ui_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid9did3_vf_ui_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid9did3_vf_ui_config_t *objptr = (sys_param_sid9did3_vf_ui_config_t *)pvParam;
    int32_t err                               = JWRITE_OK;
    int32_t jsonlen                           = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid9did3_vf_ui_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid9did3_vf_ui_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid9did3_vf_ui_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_pid9_vf_data_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_pid9_vf_data_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_pid9_vf_data_t *objptr = (sys_param_pid9_vf_data_t *)pvParam;
    int32_t err                      = JWRITE_OK;
    int32_t jsonlen                  = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_pid9_vf_data_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_pid9_vf_data_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_pid9_vf_data_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_fcw_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_fcw_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_fcw_setup_t *objptr = (sys_param_fcw_setup_t *)pvParam;
    int32_t err                   = JWRITE_OK;
    int32_t jsonlen               = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_fcw_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_fcw_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_fcw_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid10did0_fcw_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid10did0_fcw_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid10did0_fcw_config_t *objptr = (sys_param_sid10did0_fcw_config_t *)pvParam;
    int32_t err                              = JWRITE_OK;
    int32_t jsonlen                          = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid10did0_fcw_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid10did0_fcw_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid10did0_fcw_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_fcwtest_setup_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_fcwtest_setup_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_fcwtest_setup_t *objptr = (sys_param_fcwtest_setup_t *)pvParam;
    int32_t err                       = JWRITE_OK;
    int32_t jsonlen                   = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_fcwtest_setup_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_fcwtest_setup_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_fcwtest_setup_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sid10did1_fcwtest_config_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sid10did1_fcwtest_config_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sid10did1_fcwtest_config_t *objptr = (sys_param_sid10did1_fcwtest_config_t *)pvParam;
    int32_t err                                  = JWRITE_OK;
    int32_t jsonlen                              = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sid10did1_fcwtest_config_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sid10did1_fcwtest_config_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sid10did1_fcwtest_config_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_junctionbox_param_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_junctionbox_param_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_junctionbox_param_t *objptr = (sys_param_junctionbox_param_t *)pvParam;
    int32_t err                           = JWRITE_OK;
    int32_t jsonlen                       = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_junctionbox_param_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_junctionbox_param_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_junctionbox_param_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_junctionbox_ctrl_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_junctionbox_ctrl_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_junctionbox_ctrl_t *objptr = (sys_param_junctionbox_ctrl_t *)pvParam;
    int32_t err                          = JWRITE_OK;
    int32_t jsonlen                      = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_junctionbox_ctrl_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_junctionbox_ctrl_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_junctionbox_ctrl_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_system_status_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_system_status_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_system_status_t *objptr = (sys_param_system_status_t *)pvParam;
    int32_t err                       = JWRITE_OK;
    int32_t jsonlen                   = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_system_status_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_system_status_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_system_status_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/******************************************************************************
 * function name : sys_param_sidxdidx_configinfo_packing_t_dump
 * \brief Description of this fuction
 * \param0 *objname json object name
 * \param1 *objptr json c struct pointer
 * \return int32_t description
 * modification date : Mon Oct 12 15:37:40 2020
 *****************************************************************************/
int32_t sys_param_sidxdidx_configinfo_packing_t_dump(char *objname, char *buff, void *pvParam)
{
    sys_param_sidxdidx_configinfo_packing_t *objptr = (sys_param_sidxdidx_configinfo_packing_t *)pvParam;
    int32_t err                                     = JWRITE_OK;
    int32_t jsonlen                                 = 0;
    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc;
    jwc = &jwcontrol;


    jwOpen(jwc, buff, SYS_PARAM_JSON_BUFFER_SIZE, JW_OBJECT, SYS_PARAM_JSON_PRETTY_EN);

    sys_param_sidxdidx_configinfo_packing_t_dumps(jwc, objname, objptr);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        jsonlen       = (int32_t)jwLen(jwc);
        buff[jsonlen] = 0;
        sys_param_log("sys_param_sidxdidx_configinfo_packing_t to json len is %ld\n\r", jsonlen);
        return jsonlen;
    }
    else
    {
        sys_param_log("sys_param_sidxdidx_configinfo_packing_t : %s JSON_Err : %ld : %s\n\r", objname, err, jwErrorToString(err));
        return 0;
    }
}


/*

{'sys_param_adc_adar7251_setup_t': {'calcsize': 52,
                                    'decltype': 'struct',
                                    'member': [{'ROUTING': {'calcsize': 4,
                                                            'count': [4],
                                                            'decltype': 'int',
                                                            'offset': 0}},
                                               {'LNA_GAIN': {'calcsize': 4,
                                                             'count': [4],
                                                             'decltype': 'int',
                                                             'offset': 16}},
                                               {'PGA_GAIN': {'calcsize': 4,
                                                             'count': [4],
                                                             'decltype': 'int',
                                                             'offset': 32}},
                                               {'EQ_CAP': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'int',
                                                           'offset': 48}}]},
 'sys_param_adc_max11043_setup_t': {'calcsize': 80,
                                    'decltype': 'struct',
                                    'member': [{'analog_filtermode': {'calcsize': 4,
                                                                      'count': [4],
                                                                      'decltype': 'int',
                                                                      'offset': 0}},
                                               {'gain': {'calcsize': 4,
                                                         'count': [4],
                                                         'decltype': 'int',
                                                         'offset': 16}},
                                               {'digtal_filtermode': {'calcsize': 4,
                                                                      'count': [4],
                                                                      'decltype': 'int',
                                                                      'offset': 32}},
                                               {'fine_gain': {'calcsize': 4,
                                                              'count': [4],
                                                              'decltype': 'float',
                                                              'offset': 48}},
                                               {'inputbias': {'calcsize': 4,
                                                              'count': [4],
                                                              'decltype': 'int',
                                                              'offset': 64}}]},
 'sys_param_adc_select_t': {'calcsize': 4,
                            'decltype': 'struct',
                            'member': [{'adc_sel': {'calcsize': 4,
                                                    'count': [1],
                                                    'decltype': 'int',
                                                    'offset': 0}}]},
 'sys_param_app_packet_setup_t': {'calcsize': 228,
                                  'decltype': 'struct',
                                  'member': [{'count': {'calcsize': 4,
                                                        'count': [1],
                                                        'decltype': 'int',
                                                        'offset': 0}},
                                             {'ports': {'calcsize': 56,
                                                        'count': [4],
                                                        'decltype': 'sys_param_app_packet_t',
                                                        'offset': 4}}]},
 'sys_param_app_packet_t': {'calcsize': 56,
                            'decltype': 'struct',
                            'member': [{'server_ip': {'calcsize': 1,
                                                      'count': [32],
                                                      'decltype': 'char',
                                                      'offset': 0}},
                                       {'port_num': {'calcsize': 4,
                                                     'count': [1],
                                                     'decltype': 'int',
                                                     'offset': 32}},
                                       {'port_en': {'calcsize': 4,
                                                    'count': [1],
                                                    'decltype': 'int',
                                                    'offset': 36}},
                                       {'client_mode_en': {'calcsize': 1,
                                                           'count': [1],
                                                           'decltype': 'unsigned_char',
                                                           'offset': 40}},
                                       {'pid_simple_en': {'calcsize': 1,
                                                          'count': [1],
                                                          'decltype': 'unsigned_char',
                                                          'offset': 41}},
                                       {'pid_compress_en': {'calcsize': 1,
                                                            'count': [1],
                                                            'decltype': 'unsigned_char',
                                                            'offset': 42}},
                                       {'pid_status_en': {'calcsize': 1,
                                                          'count': [1],
                                                          'decltype': 'unsigned_char',
                                                          'offset': 43}},
                                       {'pid_object_en': {'calcsize': 1,
                                                          'count': [1],
                                                          'decltype': 'unsigned_char',
                                                          'offset': 44}},
                                       {'pid_track_en': {'calcsize': 1,
                                                         'count': [1],
                                                         'decltype': 'unsigned_char',
                                                         'offset': 45}},
                                       {'pid_image_en': {'calcsize': 1,
                                                         'count': [1],
                                                         'decltype': 'unsigned_char',
                                                         'offset': 46}},
                                       {'pid_imagsp_en': {'calcsize': 1,
                                                          'count': [1],
                                                          'decltype': 'unsigned_char',
                                                          'offset': 47}},
                                       {'pid_logger_en': {'calcsize': 1,
                                                          'count': [1],
                                                          'decltype': 'unsigned_char',
                                                          'offset': 48}},
                                       {'pid_canlog_en': {'calcsize': 1,
                                                          'count': [1],
                                                          'decltype': 'unsigned_char',
                                                          'offset': 49}},
                                       {'pid_sensor_en': {'calcsize': 1,
                                                          'count': [1],
                                                          'decltype': 'unsigned_char',
                                                          'offset': 50}},
                                       {'pid_app_its_en': {'calcsize': 1,
                                                           'count': [1],
                                                           'decltype': 'unsigned_char',
                                                           'offset': 51}},
                                       {'pid_app_vf_en': {'calcsize': 1,
                                                          'count': [1],
                                                          'decltype': 'unsigned_char',
                                                          'offset': 52}},
                                       {'pid_app_fcw_en': {'calcsize': 1,
                                                           'count': [1],
                                                           'decltype': 'unsigned_char',
                                                           'offset': 53}},
                                       {'pid_app_lm_en': {'calcsize': 1,
                                                          'count': [1],
                                                          'decltype': 'unsigned_char',
                                                          'offset': 54}}]},
 'sys_param_camera_setup_t': {'calcsize': 140,
                              'decltype': 'struct',
                              'member': [{'count': {'calcsize': 4,
                                                    'count': [1],
                                                    'decltype': 'int',
                                                    'offset': 0}},
                                         {'cam': {'calcsize': 68,
                                                  'count': [2],
                                                  'decltype': 'sys_param_cameractrl_setup_t',
                                                  'offset': 4}}]},
 'sys_param_cameractrl_setup_t': {'calcsize': 68,
                                  'decltype': 'struct',
                                  'member': [{'en': {'calcsize': 4,
                                                     'count': [1],
                                                     'decltype': 'int',
                                                     'offset': 0}},
                                             {'framerate': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'float',
                                                            'offset': 4}},
                                             {'imageresolution': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'int',
                                                                  'offset': 8}},
                                             {'imageroi': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'int',
                                                           'offset': 12}},
                                             {'format': {'calcsize': 4,
                                                         'count': [1],
                                                         'decltype': 'int',
                                                         'offset': 16}},
                                             {'brightness': {'calcsize': 4,
                                                             'count': [1],
                                                             'decltype': 'int',
                                                             'offset': 20}},
                                             {'contrast': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'int',
                                                           'offset': 24}},
                                             {'gain': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'int',
                                                       'offset': 28}},
                                             {'exposure_limit': {'calcsize': 4,
                                                                 'count': [1],
                                                                 'decltype': 'int',
                                                                 'offset': 32}},
                                             {'tbd1': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'int',
                                                       'offset': 36}},
                                             {'tbd2': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'int',
                                                       'offset': 40}},
                                             {'tbd3': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'int',
                                                       'offset': 44}},
                                             {'tbd4': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'int',
                                                       'offset': 48}},
                                             {'tbd5': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'int',
                                                       'offset': 52}},
                                             {'tbd6': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'int',
                                                       'offset': 56}},
                                             {'tbd7': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'int',
                                                       'offset': 60}},
                                             {'tbd8': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'int',
                                                       'offset': 64}}]},
 'sys_param_can_txmsg_t': {'calcsize': 12,
                           'decltype': 'struct',
                           'member': [{'en': {'calcsize': 1,
                                              'count': [1],
                                              'decltype': 'unsigned_char',
                                              'offset': 0}},
                                      {'start_id': {'calcsize': 4,
                                                    'count': [1],
                                                    'decltype': 'int',
                                                    'offset': 4}},
                                      {'count': {'calcsize': 4,
                                                 'count': [1],
                                                 'decltype': 'int',
                                                 'offset': 8}}]},
 'sys_param_candrv_channel_setup_t': {'calcsize': 56,
                                      'decltype': 'struct',
                                      'member': [{'cantype': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 0}},
                                                 {'baudrate': {'calcsize': 4,
                                                               'count': [1],
                                                               'decltype': 'int',
                                                               'offset': 4}},
                                                 {'baudratefd': {'calcsize': 4,
                                                                 'count': [1],
                                                                 'decltype': 'int',
                                                                 'offset': 8}},
                                                 {'samplepoint': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'int',
                                                                  'offset': 12}},
                                                 {'listenonlymode_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 16}},
                                                 {'acceptfilter_en': {'calcsize': 1,
                                                                      'count': [4],
                                                                      'decltype': 'unsigned_char',
                                                                      'offset': 20}},
                                                 {'acceptfilter_id': {'calcsize': 4,
                                                                      'count': [4],
                                                                      'decltype': 'int',
                                                                      'offset': 24}},
                                                 {'acceptfilter_mask': {'calcsize': 4,
                                                                        'count': [4],
                                                                        'decltype': 'int',
                                                                        'offset': 40}}]},
 'sys_param_candrv_setup_t': {'calcsize': 116,
                              'decltype': 'struct',
                              'member': [{'channel_count': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'int',
                                                            'offset': 0}},
                                         {'channel': {'calcsize': 56,
                                                      'count': [2],
                                                      'decltype': 'sys_param_candrv_channel_setup_t',
                                                      'offset': 4}}]},
 'sys_param_cansignal_setup_t': {'calcsize': 1280,
                                 'decltype': 'struct',
                                 'member': [{'signal': {'calcsize': 80,
                                                        'count': [16],
                                                        'decltype': 'sys_param_cansignal_t',
                                                        'offset': 0}}]},
 'sys_param_cansignal_t': {'calcsize': 80,
                           'decltype': 'struct',
                           'member': [{'en': {'calcsize': 1,
                                              'count': [1],
                                              'decltype': 'unsigned_char',
                                              'offset': 0}},
                                      {'sigid': {'calcsize': 4,
                                                 'count': [1],
                                                 'decltype': 'int',
                                                 'offset': 4}},
                                      {'msgid': {'calcsize': 4,
                                                 'count': [1],
                                                 'decltype': 'int',
                                                 'offset': 8}},
                                      {'name': {'calcsize': 1,
                                                'count': [32],
                                                'decltype': 'char',
                                                'offset': 12}},
                                      {'type': {'calcsize': 1,
                                                'count': [1],
                                                'decltype': 'signed_char',
                                                'offset': 44}},
                                      {'byteorder': {'calcsize': 1,
                                                     'count': [1],
                                                     'decltype': 'signed_char',
                                                     'offset': 45}},
                                      {'bitpos': {'calcsize': 4,
                                                  'count': [1],
                                                  'decltype': 'int',
                                                  'offset': 48}},
                                      {'length': {'calcsize': 4,
                                                  'count': [1],
                                                  'decltype': 'int',
                                                  'offset': 52}},
                                      {'factor': {'calcsize': 4,
                                                  'count': [1],
                                                  'decltype': 'float',
                                                  'offset': 56}},
                                      {'offset': {'calcsize': 4,
                                                  'count': [1],
                                                  'decltype': 'float',
                                                  'offset': 60}},
                                      {'min': {'calcsize': 4,
                                               'count': [1],
                                               'decltype': 'float',
                                               'offset': 64}},
                                      {'max': {'calcsize': 4,
                                               'count': [1],
                                               'decltype': 'float',
                                               'offset': 68}},
                                      {'unit': {'calcsize': 1,
                                                'count': [8],
                                                'decltype': 'char',
                                                'offset': 72}}]},
 'sys_param_cantxmsg_setup_t': {'calcsize': 48,
                                'decltype': 'struct',
                                'member': [{'status': {'calcsize': 12,
                                                       'count': [1],
                                                       'decltype': 'sys_param_can_txmsg_t',
                                                       'offset': 0}},
                                           {'object': {'calcsize': 12,
                                                       'count': [1],
                                                       'decltype': 'sys_param_can_txmsg_t',
                                                       'offset': 12}},
                                           {'track': {'calcsize': 12,
                                                      'count': [1],
                                                      'decltype': 'sys_param_can_txmsg_t',
                                                      'offset': 24}},
                                           {'extioctrl': {'calcsize': 12,
                                                          'count': [1],
                                                          'decltype': 'sys_param_can_txmsg_t',
                                                          'offset': 36}}]},
 'sys_param_comm_negative_response_t': {'calcsize': 264,
                                        'decltype': 'struct',
                                        'member': [{'sid': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'int',
                                                            'offset': 0}},
                                                   {'did': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'int',
                                                            'offset': 4}},
                                                   {'error': {'calcsize': 1,
                                                              'count': [256],
                                                              'decltype': 'char',
                                                              'offset': 8}}]},
 'sys_param_common_comm_ethernet_config_t': {'calcsize': 168,
                                             'decltype': 'struct',
                                             'member': [{'ip': {'calcsize': 1,
                                                                'count': [32],
                                                                'decltype': 'char',
                                                                'offset': 0}},
                                                        {'nm': {'calcsize': 1,
                                                                'count': [32],
                                                                'decltype': 'char',
                                                                'offset': 32}},
                                                        {'gw': {'calcsize': 1,
                                                                'count': [32],
                                                                'decltype': 'char',
                                                                'offset': 64}},
                                                        {'mac': {'calcsize': 1,
                                                                 'count': [32],
                                                                 'decltype': 'char',
                                                                 'offset': 96}},
                                                        {'dns': {'calcsize': 1,
                                                                 'count': [32],
                                                                 'decltype': 'char',
                                                                 'offset': 128}},
                                                        {'linkspeed': {'calcsize': 4,
                                                                       'count': [1],
                                                                       'decltype': 'int',
                                                                       'offset': 160}},
                                                        {'dhcp_en': {'calcsize': 1,
                                                                     'count': [1],
                                                                     'decltype': 'unsigned_char',
                                                                     'offset': 164}}]},
 'sys_param_common_comm_serialcomm_config_t': {'calcsize': 76,
                                               'decltype': 'struct',
                                               'member': [{'type': {'calcsize': 1,
                                                                    'count': [32],
                                                                    'decltype': 'char',
                                                                    'offset': 0}},
                                                          {'baudrate': {'calcsize': 4,
                                                                        'count': [1],
                                                                        'decltype': 'int',
                                                                        'offset': 32}},
                                                          {'flowcontrol': {'calcsize': 1,
                                                                           'count': [32],
                                                                           'decltype': 'char',
                                                                           'offset': 36}},
                                                          {'data': {'calcsize': 4,
                                                                    'count': [1],
                                                                    'decltype': 'int',
                                                                    'offset': 68}},
                                                          {'stopbit': {'calcsize': 4,
                                                                       'count': [1],
                                                                       'decltype': 'int',
                                                                       'offset': 72}}]},
 'sys_param_common_comm_tbd_config_t': {'calcsize': 32,
                                        'decltype': 'struct',
                                        'member': [{'type': {'calcsize': 1,
                                                             'count': [32],
                                                             'decltype': 'char',
                                                             'offset': 0}}]},
 'sys_param_consolelog_config_t': {'calcsize': 28,
                                   'decltype': 'struct',
                                   'member': [{'bts_log_level': {'calcsize': 4,
                                                                 'count': [1],
                                                                 'decltype': 'int',
                                                                 'offset': 0}},
                                              {'bts_log_opt_type_en': {'calcsize': 1,
                                                                       'count': [1],
                                                                       'decltype': 'unsigned_char',
                                                                       'offset': 4}},
                                              {'bts_log_opt_time_en': {'calcsize': 1,
                                                                       'count': [1],
                                                                       'decltype': 'unsigned_char',
                                                                       'offset': 5}},
                                              {'bts_log_opt_difftime_en': {'calcsize': 1,
                                                                           'count': [1],
                                                                           'decltype': 'unsigned_char',
                                                                           'offset': 6}},
                                              {'bts_log_opt_file_en': {'calcsize': 1,
                                                                       'count': [1],
                                                                       'decltype': 'unsigned_char',
                                                                       'offset': 7}},
                                              {'bts_log_opt_line_en': {'calcsize': 1,
                                                                       'count': [1],
                                                                       'decltype': 'unsigned_char',
                                                                       'offset': 8}},
                                              {'bts_log_opt_function_en': {'calcsize': 1,
                                                                           'count': [1],
                                                                           'decltype': 'unsigned_char',
                                                                           'offset': 9}},
                                              {'bts_log_module_comm_packet_en': {'calcsize': 1,
                                                                                 'count': [1],
                                                                                 'decltype': 'unsigned_char',
                                                                                 'offset': 10}},
                                              {'bts_log_module_comm_appl_callback_en': {'calcsize': 1,
                                                                                        'count': [1],
                                                                                        'decltype': 'unsigned_char',
                                                                                        'offset': 11}},
                                              {'bts_log_array_frontlen': {'calcsize': 4,
                                                                          'count': [1],
                                                                          'decltype': 'int',
                                                                          'offset': 12}},
                                              {'bts_log_array_backlen': {'calcsize': 4,
                                                                         'count': [1],
                                                                         'decltype': 'int',
                                                                         'offset': 16}},
                                              {'bts_log_cpu_usage': {'calcsize': 1,
                                                                     'count': [1],
                                                                     'decltype': 'unsigned_char',
                                                                     'offset': 20}},
                                              {'bts_log_opt_datetime_en': {'calcsize': 1,
                                                                           'count': [1],
                                                                           'decltype': 'unsigned_char',
                                                                           'offset': 21}},
                                              {'bts_log_opt_datetime_ms_en': {'calcsize': 1,
                                                                              'count': [1],
                                                                              'decltype': 'unsigned_char',
                                                                              'offset': 22}},
                                              {'bts_log_opt_datetime_us_en': {'calcsize': 1,
                                                                              'count': [1],
                                                                              'decltype': 'unsigned_char',
                                                                              'offset': 23}},
                                              {'bts_log_opt_gps_en': {'calcsize': 1,
                                                                      'count': [1],
                                                                      'decltype': 'unsigned_char',
                                                                      'offset': 24}}]},
 'sys_param_consoleudp_config_t': {'calcsize': 40,
                                   'decltype': 'struct',
                                   'member': [{'en': {'calcsize': 1,
                                                      'count': [1],
                                                      'decltype': 'unsigned_char',
                                                      'offset': 0}},
                                              {'ip': {'calcsize': 1,
                                                      'count': [32],
                                                      'decltype': 'char',
                                                      'offset': 4}},
                                              {'port': {'calcsize': 4,
                                                        'count': [1],
                                                        'decltype': 'int',
                                                        'offset': 36}}]},
 'sys_param_datetime_setup_t': {'calcsize': 52,
                                'decltype': 'struct',
                                'member': [{'type': {'calcsize': 1,
                                                     'count': [32],
                                                     'decltype': 'char',
                                                     'offset': 0}},
                                           {'unit': {'calcsize': 1,
                                                     'count': [8],
                                                     'decltype': 'char',
                                                     'offset': 32}},
                                           {'timestamp': {'calcsize': 8,
                                                          'count': [1],
                                                          'decltype': 'double',
                                                          'offset': 40}},
                                           {'gps_update_en': {'calcsize': 1,
                                                              'count': [1],
                                                              'decltype': 'unsigned_char',
                                                              'offset': 48}}]},
 'sys_param_fcw_setup_t': {'calcsize': 88,
                           'decltype': 'struct',
                           'member': [{'vehicle_type': {'calcsize': 4,
                                                        'count': [1],
                                                        'decltype': 'int',
                                                        'offset': 0}},
                                      {'startup_light_en': {'calcsize': 1,
                                                            'count': [1],
                                                            'decltype': 'unsigned_char',
                                                            'offset': 4}},
                                      {'startup_light_ontime': {'calcsize': 4,
                                                                'count': [1],
                                                                'decltype': 'int',
                                                                'offset': 8}},
                                      {'alert_led_en': {'calcsize': 1,
                                                        'count': [1],
                                                        'decltype': 'unsigned_char',
                                                        'offset': 12}},
                                      {'alert_spk_en': {'calcsize': 1,
                                                        'count': [1],
                                                        'decltype': 'unsigned_char',
                                                        'offset': 13}},
                                      {'alert_ssr_en': {'calcsize': 1,
                                                        'count': [1],
                                                        'decltype': 'unsigned_char',
                                                        'offset': 14}},
                                      {'alert_ledcolor_caution': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'int',
                                                                  'offset': 16}},
                                      {'alert_ledcolor_warning': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'int',
                                                                  'offset': 20}},
                                      {'alert_ledcolor_normal': {'calcsize': 4,
                                                                 'count': [1],
                                                                 'decltype': 'int',
                                                                 'offset': 24}},
                                      {'alert_blink_period': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 28}},
                                      {'alert_update_period': {'calcsize': 4,
                                                               'count': [1],
                                                               'decltype': 'int',
                                                               'offset': 32}},
                                      {'alert_blocking_period': {'calcsize': 4,
                                                                 'count': [1],
                                                                 'decltype': 'int',
                                                                 'offset': 36}},
                                      {'vehiclespeed_adj_ratio': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'float',
                                                                  'offset': 40}},
                                      {'ttc_low_sec': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'float',
                                                       'offset': 44}},
                                      {'ttc_high_sec': {'calcsize': 4,
                                                        'count': [1],
                                                        'decltype': 'float',
                                                        'offset': 48}},
                                      {'ttc_egospeed_low_kph': {'calcsize': 4,
                                                                'count': [1],
                                                                'decltype': 'float',
                                                                'offset': 52}},
                                      {'ttc_egospeed_high_kph': {'calcsize': 4,
                                                                 'count': [1],
                                                                 'decltype': 'float',
                                                                 'offset': 56}},
                                      {'ttc_level1_ratio': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'float',
                                                            'offset': 60}},
                                      {'ttc_level2_ratio': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'float',
                                                            'offset': 64}},
                                      {'lane_left_m': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'float',
                                                       'offset': 68}},
                                      {'lane_right_m': {'calcsize': 4,
                                                        'count': [1],
                                                        'decltype': 'float',
                                                        'offset': 72}},
                                      {'lane_range_m': {'calcsize': 4,
                                                        'count': [1],
                                                        'decltype': 'float',
                                                        'offset': 76}},
                                      {'egospeed_min_kph': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'float',
                                                            'offset': 80}},
                                      {'oncomming_th_kph': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'float',
                                                            'offset': 84}}]},
 'sys_param_fcwtest_setup_t': {'calcsize': 12,
                               'decltype': 'struct',
                               'member': [{'test_fcw_event_level1': {'calcsize': 1,
                                                                     'count': [1],
                                                                     'decltype': 'unsigned_char',
                                                                     'offset': 0}},
                                          {'test_fcw_event_level2': {'calcsize': 1,
                                                                     'count': [1],
                                                                     'decltype': 'unsigned_char',
                                                                     'offset': 1}},
                                          {'test_jctbox_led': {'calcsize': 1,
                                                               'count': [1],
                                                               'decltype': 'unsigned_char',
                                                               'offset': 2}},
                                          {'test_jctbox_spk': {'calcsize': 1,
                                                               'count': [1],
                                                               'decltype': 'unsigned_char',
                                                               'offset': 3}},
                                          {'test_jctbox_ssr': {'calcsize': 1,
                                                               'count': [1],
                                                               'decltype': 'unsigned_char',
                                                               'offset': 4}},
                                          {'test_tbd0': {'calcsize': 1,
                                                         'count': [1],
                                                         'decltype': 'unsigned_char',
                                                         'offset': 5}},
                                          {'test_tbd1': {'calcsize': 1,
                                                         'count': [1],
                                                         'decltype': 'unsigned_char',
                                                         'offset': 6}},
                                          {'test_tbd2': {'calcsize': 1,
                                                         'count': [1],
                                                         'decltype': 'unsigned_char',
                                                         'offset': 7}},
                                          {'test_tbd3': {'calcsize': 1,
                                                         'count': [1],
                                                         'decltype': 'unsigned_char',
                                                         'offset': 8}},
                                          {'test_tbd4': {'calcsize': 1,
                                                         'count': [1],
                                                         'decltype': 'unsigned_char',
                                                         'offset': 9}}]},
 'sys_param_filesystem_setup_t': {'calcsize': 12,
                                  'decltype': 'struct',
                                  'member': [{'isformatted': {'calcsize': 1,
                                                              'count': [1],
                                                              'decltype': 'unsigned_char',
                                                              'offset': 0}},
                                             {'lastfilenumber': {'calcsize': 4,
                                                                 'count': [1],
                                                                 'decltype': 'int',
                                                                 'offset': 4}},
                                             {'mmc_write_enable': {'calcsize': 1,
                                                                   'count': [1],
                                                                   'decltype': 'unsigned_char',
                                                                   'offset': 8}}]},
 'sys_param_gps_t': {'calcsize': 52,
                     'decltype': 'struct',
                     'member': [{'en': {'calcsize': 1,
                                        'count': [1],
                                        'decltype': 'unsigned_char',
                                        'offset': 0}},
                                {'manufacture': {'calcsize': 1,
                                                 'count': [32],
                                                 'decltype': 'char',
                                                 'offset': 4}},
                                {'default_baudrate': {'calcsize': 4,
                                                      'count': [1],
                                                      'decltype': 'int',
                                                      'offset': 36}},
                                {'baudrate': {'calcsize': 4,
                                              'count': [1],
                                              'decltype': 'int',
                                              'offset': 40}},
                                {'rate': {'calcsize': 4,
                                          'count': [1],
                                          'decltype': 'int',
                                          'offset': 44}},
                                {'dgps_en': {'calcsize': 1,
                                             'count': [1],
                                             'decltype': 'unsigned_char',
                                             'offset': 48}},
                                {'swfilter_en': {'calcsize': 1,
                                                 'count': [1],
                                                 'decltype': 'unsigned_char',
                                                 'offset': 49}}]},
 'sys_param_infra_setup_t': {'calcsize': 768,
                             'decltype': 'struct',
                             'member': [{'infraid': {'calcsize': 1,
                                                     'count': [32],
                                                     'decltype': 'char',
                                                     'offset': 0}},
                                        {'radarid': {'calcsize': 1,
                                                     'count': [32],
                                                     'decltype': 'char',
                                                     'offset': 32}},
                                        {'locationid': {'calcsize': 1,
                                                        'count': [32],
                                                        'decltype': 'char',
                                                        'offset': 64}},
                                        {'basestationid': {'calcsize': 1,
                                                           'count': [32],
                                                           'decltype': 'char',
                                                           'offset': 96}},
                                        {'switchid': {'calcsize': 1,
                                                      'count': [32],
                                                      'decltype': 'char',
                                                      'offset': 128}},
                                        {'desc': {'calcsize': 1,
                                                  'count': [32],
                                                  'decltype': 'char',
                                                  'offset': 160}},
                                        {'desc1': {'calcsize': 1,
                                                   'count': [32],
                                                   'decltype': 'char',
                                                   'offset': 192}},
                                        {'desc2': {'calcsize': 1,
                                                   'count': [32],
                                                   'decltype': 'char',
                                                   'offset': 224}},
                                        {'longitude': {'calcsize': 1,
                                                       'count': [32],
                                                       'decltype': 'char',
                                                       'offset': 256}},
                                        {'latitude': {'calcsize': 1,
                                                      'count': [32],
                                                      'decltype': 'char',
                                                      'offset': 288}},
                                        {'direction': {'calcsize': 1,
                                                       'count': [32],
                                                       'decltype': 'char',
                                                       'offset': 320}},
                                        {'height': {'calcsize': 1,
                                                    'count': [32],
                                                    'decltype': 'char',
                                                    'offset': 352}},
                                        {'roadid': {'calcsize': 1,
                                                    'count': [32],
                                                    'decltype': 'char',
                                                    'offset': 384}},
                                        {'roadid1': {'calcsize': 1,
                                                     'count': [32],
                                                     'decltype': 'char',
                                                     'offset': 416}},
                                        {'roadid2': {'calcsize': 1,
                                                     'count': [32],
                                                     'decltype': 'char',
                                                     'offset': 448}},
                                        {'area': {'calcsize': 1,
                                                  'count': [32],
                                                  'decltype': 'char',
                                                  'offset': 480}},
                                        {'area1': {'calcsize': 1,
                                                   'count': [32],
                                                   'decltype': 'char',
                                                   'offset': 512}},
                                        {'range': {'calcsize': 1,
                                                   'count': [32],
                                                   'decltype': 'char',
                                                   'offset': 544}},
                                        {'range1': {'calcsize': 1,
                                                    'count': [32],
                                                    'decltype': 'char',
                                                    'offset': 576}},
                                        {'lane': {'calcsize': 1,
                                                  'count': [32],
                                                  'decltype': 'char',
                                                  'offset': 608}},
                                        {'lane1': {'calcsize': 1,
                                                   'count': [32],
                                                   'decltype': 'char',
                                                   'offset': 640}},
                                        {'lane2': {'calcsize': 1,
                                                   'count': [32],
                                                   'decltype': 'char',
                                                   'offset': 672}},
                                        {'lane3': {'calcsize': 1,
                                                   'count': [32],
                                                   'decltype': 'char',
                                                   'offset': 704}},
                                        {'lane4': {'calcsize': 1,
                                                   'count': [32],
                                                   'decltype': 'char',
                                                   'offset': 736}}]},
 'sys_param_its_alignment_setup_t': {'calcsize': 16,
                                     'decltype': 'struct',
                                     'member': [{'autoalignment_on': {'calcsize': 1,
                                                                      'count': [1],
                                                                      'decltype': 'unsigned_char',
                                                                      'offset': 0}},
                                                {'num_track_autoalignment': {'calcsize': 4,
                                                                             'count': [1],
                                                                             'decltype': 'int',
                                                                             'offset': 4}},
                                                {'status_autoalignment': {'calcsize': 4,
                                                                          'count': [1],
                                                                          'decltype': 'int',
                                                                          'offset': 8}},
                                                {'angle_aligned': {'calcsize': 4,
                                                                   'count': [1],
                                                                   'decltype': 'float',
                                                                   'offset': 12}}]},
 'sys_param_its_data_count_t': {'calcsize': 196,
                                'decltype': 'struct',
                                'member': [{'ts': {'calcsize': 4,
                                                   'count': [1],
                                                   'decltype': 'int',
                                                   'offset': 0}},
                                           {'diff': {'calcsize': 4,
                                                     'count': [4],
                                                     'decltype': 'int',
                                                     'offset': 4}},
                                           {'acc': {'calcsize': 4,
                                                    'count': [4, 5],
                                                    'decltype': 'int',
                                                    'offset': 20}},
                                           {'lc': {'calcsize': 4,
                                                   'count': [4],
                                                   'decltype': 'int',
                                                   'offset': 100}},
                                           {'acclc': {'calcsize': 4,
                                                      'count': [4, 5],
                                                      'decltype': 'int',
                                                      'offset': 116}}]},
 'sys_param_its_data_event_t': {'calcsize': 904,
                                'decltype': 'struct',
                                'member': [{'abnomal': {'calcsize': 256,
                                                        'count': [1],
                                                        'decltype': 'sys_param_its_data_event_tidlane_t',
                                                        'offset': 0}},
                                           {'reverse': {'calcsize': 256,
                                                        'count': [1],
                                                        'decltype': 'sys_param_its_data_event_tidlane_t',
                                                        'offset': 256}},
                                           {'speedlimit': {'calcsize': 256,
                                                           'count': [1],
                                                           'decltype': 'sys_param_its_data_event_tidlane_t',
                                                           'offset': 512}},
                                           {'cs': {'calcsize': 1,
                                                   'count': [8],
                                                   'decltype': 'char',
                                                   'offset': 768}},
                                           {'notvehicle': {'calcsize': 128,
                                                           'count': [1],
                                                           'decltype': 'sys_param_its_data_event_tidlane2_t',
                                                           'offset': 776}}]},
 'sys_param_its_data_event_tidlane2_t': {'calcsize': 128,
                                         'decltype': 'struct',
                                         'member': [{'tid': {'calcsize': 4,
                                                             'count': [32],
                                                             'decltype': 'int',
                                                             'offset': 0}}]},
 'sys_param_its_data_event_tidlane_t': {'calcsize': 256,
                                        'decltype': 'struct',
                                        'member': [{'tid': {'calcsize': 4,
                                                            'count': [32],
                                                            'decltype': 'int',
                                                            'offset': 0}},
                                                   {'lane': {'calcsize': 4,
                                                             'count': [32],
                                                             'decltype': 'int',
                                                             'offset': 128}}]},
 'sys_param_its_data_lane_t': {'calcsize': 40,
                               'decltype': 'struct',
                               'member': [{'cnt': {'calcsize': 4,
                                                   'count': [1],
                                                   'decltype': 'int',
                                                   'offset': 0}},
                                          {'num': {'calcsize': 4,
                                                   'count': [4],
                                                   'decltype': 'int',
                                                   'offset': 4}},
                                          {'period': {'calcsize': 4,
                                                      'count': [5],
                                                      'decltype': 'int',
                                                      'offset': 20}}]},
 'sys_param_its_data_speed_t': {'calcsize': 240,
                                'decltype': 'struct',
                                'member': [{'average': {'calcsize': 4,
                                                        'count': [4, 5],
                                                        'decltype': 'float',
                                                        'offset': 0}},
                                           {'min': {'calcsize': 4,
                                                    'count': [4, 5],
                                                    'decltype': 'float',
                                                    'offset': 80}},
                                           {'max': {'calcsize': 4,
                                                    'count': [4, 5],
                                                    'decltype': 'float',
                                                    'offset': 160}}]},
 'sys_param_its_device_setup_t': {'calcsize': 76,
                                  'decltype': 'struct',
                                  'member': [{'relay': {'calcsize': 76,
                                                        'count': [1],
                                                        'decltype': 'sys_param_its_relay_t',
                                                        'offset': 0}}]},
 'sys_param_its_relay_t': {'calcsize': 76,
                           'decltype': 'struct',
                           'member': [{'relay_cnt': {'calcsize': 4,
                                                     'count': [1],
                                                     'decltype': 'int',
                                                     'offset': 0}},
                                      {'relay_enable': {'calcsize': 4,
                                                        'count': [2],
                                                        'decltype': 'int',
                                                        'offset': 4}},
                                      {'relay_type': {'calcsize': 1,
                                                      'count': [8, 2],
                                                      'decltype': 'char',
                                                      'offset': 12}},
                                      {'relay_on_time_ms': {'calcsize': 4,
                                                            'count': [2],
                                                            'decltype': 'int',
                                                            'offset': 28}},
                                      {'relay_off_time_ms': {'calcsize': 4,
                                                             'count': [2],
                                                             'decltype': 'int',
                                                             'offset': 36}},
                                      {'relay_adjust_time_ms': {'calcsize': 4,
                                                                'count': [2],
                                                                'decltype': 'int',
                                                                'offset': 44}},
                                      {'relay_lowbound_time_ms': {'calcsize': 4,
                                                                  'count': [2],
                                                                  'decltype': 'int',
                                                                  'offset': 52}},
                                      {'relay_highbound_time_ms': {'calcsize': 4,
                                                                   'count': [2],
                                                                   'decltype': 'int',
                                                                   'offset': 60}},
                                      {'relay_on_event_type': {'calcsize': 4,
                                                               'count': [2],
                                                               'decltype': 'int',
                                                               'offset': 68}}]},
 'sys_param_its_setup_area_t': {'calcsize': 20,
                                'decltype': 'struct',
                                'member': [{'x': {'calcsize': 4,
                                                  'count': [2],
                                                  'decltype': 'float',
                                                  'offset': 0}},
                                           {'y': {'calcsize': 4,
                                                  'count': [2],
                                                  'decltype': 'float',
                                                  'offset': 8}},
                                           {'t': {'calcsize': 4,
                                                  'count': [1],
                                                  'decltype': 'float',
                                                  'offset': 16}}]},
 'sys_param_its_setup_blackout_t': {'calcsize': 204,
                                    'decltype': 'struct',
                                    'member': [{'count': {'calcsize': 4,
                                                          'count': [1],
                                                          'decltype': 'int',
                                                          'offset': 0}},
                                               {'area': {'calcsize': 20,
                                                         'count': [10],
                                                         'decltype': 'sys_param_its_setup_area_t',
                                                         'offset': 4}}]},
 'sys_param_its_setup_hotspotzone_t': {'calcsize': 808,
                                       'decltype': 'struct',
                                       'member': [{'x': {'calcsize': 4,
                                                         'count': [100],
                                                         'decltype': 'float',
                                                         'offset': 0}},
                                                  {'y': {'calcsize': 4,
                                                         'count': [100],
                                                         'decltype': 'float',
                                                         'offset': 400}},
                                                  {'width': {'calcsize': 4,
                                                             'count': [1],
                                                             'decltype': 'float',
                                                             'offset': 800}},
                                                  {'midoffset': {'calcsize': 4,
                                                                 'count': [1],
                                                                 'decltype': 'float',
                                                                 'offset': 804}}]},
 'sys_param_its_setup_laneinfo_lane_t': {'calcsize': 400,
                                         'decltype': 'struct',
                                         'member': [{'x': {'calcsize': 4,
                                                           'count': [50],
                                                           'decltype': 'float',
                                                           'offset': 0}},
                                                    {'y': {'calcsize': 4,
                                                           'count': [50],
                                                           'decltype': 'float',
                                                           'offset': 200}}]},
 'sys_param_its_setup_laneinfo_t': {'calcsize': 2416,
                                    'decltype': 'struct',
                                    'member': [{'stepcount': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 0}},
                                               {'left': {'calcsize': 400,
                                                         'count': [1],
                                                         'decltype': 'sys_param_its_setup_laneinfo_lane_t',
                                                         'offset': 4}},
                                               {'hotspotzone': {'calcsize': 808,
                                                                'count': [1],
                                                                'decltype': 'sys_param_its_setup_hotspotzone_t',
                                                                'offset': 404}},
                                               {'trackingzone': {'calcsize': 800,
                                                                 'count': [1],
                                                                 'decltype': 'sys_param_its_setup_zone_t',
                                                                 'offset': 1212}},
                                               {'right': {'calcsize': 400,
                                                          'count': [1],
                                                          'decltype': 'sys_param_its_setup_laneinfo_lane_t',
                                                          'offset': 2012}},
                                               {'number': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'int',
                                                           'offset': 2412}}]},
 'sys_param_its_setup_misc_t': {'calcsize': 8,
                                'decltype': 'struct',
                                'member': [{'camera_on': {'calcsize': 1,
                                                          'count': [1],
                                                          'decltype': 'unsigned_char',
                                                          'offset': 0}},
                                           {'trackingzone_view_on': {'calcsize': 1,
                                                                     'count': [1],
                                                                     'decltype': 'unsigned_char',
                                                                     'offset': 1}},
                                           {'autoalignment_on': {'calcsize': 1,
                                                                 'count': [1],
                                                                 'decltype': 'unsigned_char',
                                                                 'offset': 2}},
                                           {'num_track_autoalignment': {'calcsize': 4,
                                                                        'count': [1],
                                                                        'decltype': 'int',
                                                                        'offset': 4}}]},
 'sys_param_its_setup_speedlimit_t': {'calcsize': 12,
                                      'decltype': 'struct',
                                      'member': [{'high_speedlimit_kph': {'calcsize': 4,
                                                                          'count': [1],
                                                                          'decltype': 'float',
                                                                          'offset': 0}},
                                                 {'low_speedlimit_kph': {'calcsize': 4,
                                                                         'count': [1],
                                                                         'decltype': 'float',
                                                                         'offset': 4}},
                                                 {'speedlimit_compensation_percentage': {'calcsize': 4,
                                                                                         'count': [1],
                                                                                         'decltype': 'int',
                                                                                         'offset': 8}}]},
 'sys_param_its_setup_t': {'calcsize': 9916,
                           'decltype': 'struct',
                           'member': [{'timeschedule': {'calcsize': 12,
                                                        'count': [1],
                                                        'decltype': 'sys_param_its_setup_timeschedule_t',
                                                        'offset': 0}},
                                      {'misc': {'calcsize': 8,
                                                'count': [1],
                                                'decltype': 'sys_param_its_setup_misc_t',
                                                'offset': 12}},
                                      {'middlelane': {'calcsize': 4,
                                                      'count': [1],
                                                      'decltype': 'float',
                                                      'offset': 20}},
                                      {'uplaneangle': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'int',
                                                       'offset': 24}},
                                      {'downlaneangle': {'calcsize': 4,
                                                         'count': [1],
                                                         'decltype': 'int',
                                                         'offset': 28}},
                                      {'lanecount': {'calcsize': 4,
                                                     'count': [1],
                                                     'decltype': 'int',
                                                     'offset': 32}},
                                      {'speedlimit': {'calcsize': 12,
                                                      'count': [1],
                                                      'decltype': 'sys_param_its_setup_speedlimit_t',
                                                      'offset': 36}},
                                      {'laneinfo': {'calcsize': 2416,
                                                    'count': [4],
                                                    'decltype': 'sys_param_its_setup_laneinfo_t',
                                                    'offset': 48}},
                                      {'blackout': {'calcsize': 204,
                                                    'count': [1],
                                                    'decltype': 'sys_param_its_setup_blackout_t',
                                                    'offset': 9712}}]},
 'sys_param_its_setup_timeschedule_t': {'calcsize': 12,
                                        'decltype': 'struct',
                                        'member': [{'timeunit': {'calcsize': 1,
                                                                 'count': [8],
                                                                 'decltype': 'char',
                                                                 'offset': 0}},
                                                   {'updatetime': {'calcsize': 4,
                                                                   'count': [1],
                                                                   'decltype': 'int',
                                                                   'offset': 8}}]},
 'sys_param_its_setup_zone_t': {'calcsize': 800,
                                'decltype': 'struct',
                                'member': [{'x': {'calcsize': 4,
                                                  'count': [100],
                                                  'decltype': 'float',
                                                  'offset': 0}},
                                           {'y': {'calcsize': 4,
                                                  'count': [100],
                                                  'decltype': 'float',
                                                  'offset': 400}}]},
 'sys_param_its_testmode_hotspotzone_t': {'calcsize': 28,
                                          'decltype': 'struct',
                                          'member': [{'modlane_en': {'calcsize': 1,
                                                                     'count': [2],
                                                                     'decltype': 'unsigned_char',
                                                                     'offset': 0}},
                                                     {'modlane_offset_hotspotzone_y': {'calcsize': 4,
                                                                                       'count': [2],
                                                                                       'decltype': 'float',
                                                                                       'offset': 4}},
                                                     {'modlane_offset_hotspotzone_width': {'calcsize': 4,
                                                                                           'count': [2],
                                                                                           'decltype': 'float',
                                                                                           'offset': 12}},
                                                     {'modlane_offset_hotspotzone_offset': {'calcsize': 4,
                                                                                            'count': [2],
                                                                                            'decltype': 'float',
                                                                                            'offset': 20}}]},
 'sys_param_its_testmode_image_t': {'calcsize': 4,
                                    'decltype': 'struct',
                                    'member': [{'skip_image_count': {'calcsize': 4,
                                                                     'count': [1],
                                                                     'decltype': 'int',
                                                                     'offset': 0}}]},
 'sys_param_its_testmode_misc_t': {'calcsize': 12,
                                   'decltype': 'struct',
                                   'member': [{'trackzone_xrange': {'calcsize': 4,
                                                                    'count': [1],
                                                                    'decltype': 'float',
                                                                    'offset': 0}},
                                              {'en_lanechange': {'calcsize': 1,
                                                                 'count': [1],
                                                                 'decltype': 'unsigned_char',
                                                                 'offset': 4}},
                                              {'low_exclude_speed': {'calcsize': 4,
                                                                     'count': [1],
                                                                     'decltype': 'float',
                                                                     'offset': 8}}]},
 'sys_param_its_testmode_setup_t': {'calcsize': 72,
                                    'decltype': 'struct',
                                    'member': [{'speedlimit_tolerance': {'calcsize': 8,
                                                                         'count': [1],
                                                                         'decltype': 'sys_param_its_testmode_speedlimit_t',
                                                                         'offset': 0}},
                                               {'trigger': {'calcsize': 20,
                                                            'count': [1],
                                                            'decltype': 'sys_param_its_testmode_trigger_t',
                                                            'offset': 8}},
                                               {'modlane': {'calcsize': 28,
                                                            'count': [1],
                                                            'decltype': 'sys_param_its_testmode_hotspotzone_t',
                                                            'offset': 28}},
                                               {'imagetest': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'sys_param_its_testmode_image_t',
                                                              'offset': 56}},
                                               {'misc': {'calcsize': 12,
                                                         'count': [1],
                                                         'decltype': 'sys_param_its_testmode_misc_t',
                                                         'offset': 60}}]},
 'sys_param_its_testmode_speedlimit_t': {'calcsize': 8,
                                         'decltype': 'struct',
                                         'member': [{'high_speedlimit_tolerance_percentage': {'calcsize': 4,
                                                                                              'count': [1],
                                                                                              'decltype': 'float',
                                                                                              'offset': 0}},
                                                    {'low_speedlimit_tolerance_percentage': {'calcsize': 4,
                                                                                             'count': [1],
                                                                                             'decltype': 'float',
                                                                                             'offset': 4}}]},
 'sys_param_its_testmode_trigger_t': {'calcsize': 20,
                                      'decltype': 'struct',
                                      'member': [{'trigger_en': {'calcsize': 1,
                                                                 'count': [2],
                                                                 'decltype': 'unsigned_char',
                                                                 'offset': 0}},
                                                 {'trigger_period': {'calcsize': 4,
                                                                     'count': [2],
                                                                     'decltype': 'int',
                                                                     'offset': 4}},
                                                 {'trigger_ttlc_time_ms': {'calcsize': 4,
                                                                           'count': [2],
                                                                           'decltype': 'float',
                                                                           'offset': 12}}]},
 'sys_param_jctbox_setup_t': {'calcsize': 36,
                              'decltype': 'struct',
                              'member': [{'commtype': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'int',
                                                       'offset': 0}},
                                         {'highspeed_en': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'int',
                                                           'offset': 4}},
                                         {'baudrate_default': {'calcsize': 4,
                                                               'count': [1],
                                                               'decltype': 'int',
                                                               'offset': 8}},
                                         {'baudrate_high': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'int',
                                                            'offset': 12}},
                                         {'packettype': {'calcsize': 4,
                                                         'count': [1],
                                                         'decltype': 'int',
                                                         'offset': 16}},
                                         {'tbd0': {'calcsize': 4,
                                                   'count': [1],
                                                   'decltype': 'int',
                                                   'offset': 20}},
                                         {'tbd1': {'calcsize': 4,
                                                   'count': [1],
                                                   'decltype': 'int',
                                                   'offset': 24}},
                                         {'tbd2': {'calcsize': 4,
                                                   'count': [1],
                                                   'decltype': 'int',
                                                   'offset': 28}},
                                         {'tbd3': {'calcsize': 4,
                                                   'count': [1],
                                                   'decltype': 'int',
                                                   'offset': 32}}]},
 'sys_param_junctionbox_ctrl_t': {'calcsize': 56,
                                  'decltype': 'struct',
                                  'member': [{'cmd': {'calcsize': 1,
                                                      'count': [32],
                                                      'decltype': 'char',
                                                      'offset': 0}},
                                             {'param': {'calcsize': 24,
                                                        'count': [1],
                                                        'decltype': 'sys_param_junctionbox_param_t',
                                                        'offset': 32}}]},
 'sys_param_junctionbox_param_t': {'calcsize': 24,
                                   'decltype': 'struct',
                                   'member': [{'r': {'calcsize': 4,
                                                     'count': [1],
                                                     'decltype': 'int',
                                                     'offset': 0}},
                                              {'g': {'calcsize': 4,
                                                     'count': [1],
                                                     'decltype': 'int',
                                                     'offset': 4}},
                                              {'b': {'calcsize': 4,
                                                     'count': [1],
                                                     'decltype': 'int',
                                                     'offset': 8}},
                                              {'spk': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'int',
                                                       'offset': 12}},
                                              {'ssra': {'calcsize': 4,
                                                        'count': [1],
                                                        'decltype': 'int',
                                                        'offset': 16}},
                                              {'ssrb': {'calcsize': 4,
                                                        'count': [1],
                                                        'decltype': 'int',
                                                        'offset': 20}}]},
 'sys_param_location_setup_t': {'calcsize': 108,
                                'decltype': 'struct',
                                'member': [{'location': {'calcsize': 56,
                                                         'count': [1],
                                                         'decltype': 'sys_param_location_t',
                                                         'offset': 0}},
                                           {'gps': {'calcsize': 52,
                                                    'count': [1],
                                                    'decltype': 'sys_param_gps_t',
                                                    'offset': 56}}]},
 'sys_param_location_t': {'calcsize': 56,
                          'decltype': 'struct',
                          'member': [{'type': {'calcsize': 1,
                                               'count': [32],
                                               'decltype': 'char',
                                               'offset': 0}},
                                     {'latitude': {'calcsize': 8,
                                                   'count': [1],
                                                   'decltype': 'double',
                                                   'offset': 32}},
                                     {'longitude': {'calcsize': 8,
                                                    'count': [1],
                                                    'decltype': 'double',
                                                    'offset': 40}},
                                     {'direction': {'calcsize': 4,
                                                    'count': [1],
                                                    'decltype': 'float',
                                                    'offset': 48}},
                                     {'gps_update_en': {'calcsize': 1,
                                                        'count': [1],
                                                        'decltype': 'unsigned_char',
                                                        'offset': 52}}]},
 'sys_param_logic_control_config_t': {'calcsize': 4,
                                      'decltype': 'struct',
                                      'member': [{'logic_start_scan_offset': {'calcsize': 4,
                                                                              'count': [1],
                                                                              'decltype': 'int',
                                                                              'offset': 0}}]},
 'sys_param_parameter_t': {'calcsize': 1,
                           'decltype': 'enum',
                           'member': [{'sys_param_STRLEN_MAX': 32},
                                      {'sys_param_STRLEN_MIN': 8}]},
 'sys_param_pid0_status_data_t': {'calcsize': 1100,
                                  'decltype': 'struct',
                                  'member': [{'scanindex': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'int',
                                                            'offset': 0}},
                                             {'timestamp': {'calcsize': 28,
                                                            'count': [1],
                                                            'decltype': 'sys_param_status_timestamp_t',
                                                            'offset': 4}},
                                             {'position': {'calcsize': 16,
                                                           'count': [1],
                                                           'decltype': 'sys_param_status_data_position_t',
                                                           'offset': 32}},
                                             {'ecuinfo': {'calcsize': 24,
                                                          'count': [1],
                                                          'decltype': 'sys_param_status_data_ecuinfo_t',
                                                          'offset': 48}},
                                             {'gps': {'calcsize': 1028,
                                                      'count': [1],
                                                      'decltype': 'sys_param_status_data_gps_t',
                                                      'offset': 72}}]},
 'sys_param_pid8_its_data_t': {'calcsize': 1380,
                               'decltype': 'struct',
                               'member': [{'lane': {'calcsize': 40,
                                                    'count': [1],
                                                    'decltype': 'sys_param_its_data_lane_t',
                                                    'offset': 0}},
                                          {'count': {'calcsize': 196,
                                                     'count': [1],
                                                     'decltype': 'sys_param_its_data_count_t',
                                                     'offset': 40}},
                                          {'speed': {'calcsize': 240,
                                                     'count': [1],
                                                     'decltype': 'sys_param_its_data_speed_t',
                                                     'offset': 236}},
                                          {'event': {'calcsize': 904,
                                                     'count': [1],
                                                     'decltype': 'sys_param_its_data_event_t',
                                                     'offset': 476}}]},
 'sys_param_pid9_vf_data_t': {'calcsize': 508,
                              'decltype': 'struct',
                              'member': [{'cnt': {'calcsize': 4,
                                                  'count': [1],
                                                  'decltype': 'int',
                                                  'offset': 0}},
                                         {'prd': {'calcsize': 4,
                                                  'count': [1],
                                                  'decltype': 'float',
                                                  'offset': 4}},
                                         {'dat': {'calcsize': 4,
                                                  'count': [25],
                                                  'decltype': 'float',
                                                  'offset': 8}},
                                         {'std': {'calcsize': 4,
                                                  'count': [25],
                                                  'decltype': 'float',
                                                  'offset': 108}},
                                         {'war': {'calcsize': 4,
                                                  'count': [25],
                                                  'decltype': 'int',
                                                  'offset': 208}},
                                         {'det': {'calcsize': 4,
                                                  'count': [25],
                                                  'decltype': 'int',
                                                  'offset': 308}},
                                         {'sw': {'calcsize': 4,
                                                 'count': [25],
                                                 'decltype': 'int',
                                                 'offset': 408}}]},
 'sys_param_pll_lmx2491_setup_t': {'calcsize': 8,
                                   'decltype': 'struct',
                                   'member': [{'regset': {'calcsize': 4,
                                                          'count': [1],
                                                          'decltype': 'int',
                                                          'offset': 0}},
                                              {'cp': {'calcsize': 4,
                                                      'count': [1],
                                                      'decltype': 'int',
                                                      'offset': 4}}]},
 'sys_param_pll_select_t': {'calcsize': 4,
                            'decltype': 'struct',
                            'member': [{'pll_sel': {'calcsize': 4,
                                                    'count': [1],
                                                    'decltype': 'int',
                                                    'offset': 0}}]},
 'sys_param_rficrx_bgt24ar4_setup_t': {'calcsize': 32,
                                       'decltype': 'struct',
                                       'member': [{'EN_12': {'calcsize': 1,
                                                             'count': [1],
                                                             'decltype': 'unsigned_char',
                                                             'offset': 0}},
                                                  {'LG1_12_6db': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 1}},
                                                  {'HG1_12_12db': {'calcsize': 1,
                                                                   'count': [1],
                                                                   'decltype': 'unsigned_char',
                                                                   'offset': 2}},
                                                  {'LG2_12_6db': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 3}},
                                                  {'MG2_12_12db': {'calcsize': 1,
                                                                   'count': [1],
                                                                   'decltype': 'unsigned_char',
                                                                   'offset': 4}},
                                                  {'HG2_12_18db': {'calcsize': 1,
                                                                   'count': [1],
                                                                   'decltype': 'unsigned_char',
                                                                   'offset': 5}},
                                                  {'EN_34': {'calcsize': 1,
                                                             'count': [1],
                                                             'decltype': 'unsigned_char',
                                                             'offset': 6}},
                                                  {'LG1_34_6db': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 7}},
                                                  {'HG1_34_12db': {'calcsize': 1,
                                                                   'count': [1],
                                                                   'decltype': 'unsigned_char',
                                                                   'offset': 8}},
                                                  {'LG2_34_6db': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 9}},
                                                  {'MG2_34_12db': {'calcsize': 1,
                                                                   'count': [1],
                                                                   'decltype': 'unsigned_char',
                                                                   'offset': 10}},
                                                  {'HG2_34_18db': {'calcsize': 1,
                                                                   'count': [1],
                                                                   'decltype': 'unsigned_char',
                                                                   'offset': 11}},
                                                  {'IFTEST4': {'calcsize': 1,
                                                               'count': [1],
                                                               'decltype': 'unsigned_char',
                                                               'offset': 12}},
                                                  {'IFTEST3': {'calcsize': 1,
                                                               'count': [1],
                                                               'decltype': 'unsigned_char',
                                                               'offset': 13}},
                                                  {'IFTEST2': {'calcsize': 1,
                                                               'count': [1],
                                                               'decltype': 'unsigned_char',
                                                               'offset': 14}},
                                                  {'IFTEST1': {'calcsize': 1,
                                                               'count': [1],
                                                               'decltype': 'unsigned_char',
                                                               'offset': 15}},
                                                  {'PC1': {'calcsize': 1,
                                                           'count': [1],
                                                           'decltype': 'unsigned_char',
                                                           'offset': 16}},
                                                  {'PC2': {'calcsize': 1,
                                                           'count': [1],
                                                           'decltype': 'unsigned_char',
                                                           'offset': 17}},
                                                  {'EN_RF14': {'calcsize': 1,
                                                               'count': [1],
                                                               'decltype': 'unsigned_char',
                                                               'offset': 18}},
                                                  {'EN_RF23': {'calcsize': 1,
                                                               'count': [1],
                                                               'decltype': 'unsigned_char',
                                                               'offset': 19}},
                                                  {'DIS_DIV': {'calcsize': 1,
                                                               'count': [1],
                                                               'decltype': 'unsigned_char',
                                                               'offset': 20}},
                                                  {'DIS_LO': {'calcsize': 1,
                                                              'count': [1],
                                                              'decltype': 'unsigned_char',
                                                              'offset': 21}},
                                                  {'AMUX_SEL0': {'calcsize': 1,
                                                                 'count': [1],
                                                                 'decltype': 'unsigned_char',
                                                                 'offset': 22}},
                                                  {'AMUX_SEL1': {'calcsize': 1,
                                                                 'count': [1],
                                                                 'decltype': 'unsigned_char',
                                                                 'offset': 23}},
                                                  {'AMUX_SEL2': {'calcsize': 1,
                                                                 'count': [1],
                                                                 'decltype': 'unsigned_char',
                                                                 'offset': 24}},
                                                  {'SAT_FLAG_HIZ': {'calcsize': 1,
                                                                    'count': [1],
                                                                    'decltype': 'unsigned_char',
                                                                    'offset': 25}},
                                                  {'SENSOR_SEL0': {'calcsize': 1,
                                                                   'count': [1],
                                                                   'decltype': 'unsigned_char',
                                                                   'offset': 26}},
                                                  {'SENSOR_SEL1': {'calcsize': 1,
                                                                   'count': [1],
                                                                   'decltype': 'unsigned_char',
                                                                   'offset': 27}},
                                                  {'DCO_0': {'calcsize': 1,
                                                             'count': [1],
                                                             'decltype': 'unsigned_char',
                                                             'offset': 28}},
                                                  {'DCO_1': {'calcsize': 1,
                                                             'count': [1],
                                                             'decltype': 'unsigned_char',
                                                             'offset': 29}},
                                                  {'DCO_2': {'calcsize': 1,
                                                             'count': [1],
                                                             'decltype': 'unsigned_char',
                                                             'offset': 30}},
                                                  {'DCO_3': {'calcsize': 1,
                                                             'count': [1],
                                                             'decltype': 'unsigned_char',
                                                             'offset': 31}}]},
 'sys_param_rficrx_select_t': {'calcsize': 4,
                               'decltype': 'struct',
                               'member': [{'rficrx_sel': {'calcsize': 4,
                                                          'count': [1],
                                                          'decltype': 'int',
                                                          'offset': 0}}]},
 'sys_param_rfictx_bgt24at2_setup_t': {'calcsize': 48,
                                       'decltype': 'struct',
                                       'member': [{'TX1_A': {'calcsize': 4,
                                                             'count': [1],
                                                             'decltype': 'int',
                                                             'offset': 0}},
                                                  {'TX1_SPI_ON': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 4}},
                                                  {'TX1_EN_DAC': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 5}},
                                                  {'TX1_SEL1': {'calcsize': 1,
                                                                'count': [1],
                                                                'decltype': 'unsigned_char',
                                                                'offset': 6}},
                                                  {'PH1_SPI_ON': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 7}},
                                                  {'TX2_A': {'calcsize': 4,
                                                             'count': [1],
                                                             'decltype': 'int',
                                                             'offset': 8}},
                                                  {'TX2_SPI_ON': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 12}},
                                                  {'TX2_SEL1': {'calcsize': 1,
                                                                'count': [1],
                                                                'decltype': 'unsigned_char',
                                                                'offset': 13}},
                                                  {'TX2_EN_DAC': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 14}},
                                                  {'PH2_SPI_ON': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 15}},
                                                  {'LO_A': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'int',
                                                            'offset': 16}},
                                                  {'LO_SPI_ON': {'calcsize': 1,
                                                                 'count': [1],
                                                                 'decltype': 'unsigned_char',
                                                                 'offset': 20}},
                                                  {'LO_EN_DAC': {'calcsize': 1,
                                                                 'count': [1],
                                                                 'decltype': 'unsigned_char',
                                                                 'offset': 21}},
                                                  {'LO_SEL1': {'calcsize': 1,
                                                               'count': [1],
                                                               'decltype': 'unsigned_char',
                                                               'offset': 22}},
                                                  {'LO_SEL0': {'calcsize': 1,
                                                               'count': [1],
                                                               'decltype': 'unsigned_char',
                                                               'offset': 23}},
                                                  {'PHLO_SPI_ON': {'calcsize': 1,
                                                                   'count': [1],
                                                                   'decltype': 'unsigned_char',
                                                                   'offset': 24}},
                                                  {'VCO_A': {'calcsize': 4,
                                                             'count': [1],
                                                             'decltype': 'int',
                                                             'offset': 28}},
                                                  {'EN_DAC_VCO': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 32}},
                                                  {'EN_VCO': {'calcsize': 1,
                                                              'count': [1],
                                                              'decltype': 'unsigned_char',
                                                              'offset': 33}},
                                                  {'EN_BUF2': {'calcsize': 1,
                                                               'count': [1],
                                                               'decltype': 'unsigned_char',
                                                               'offset': 34}},
                                                  {'EN_BUF1': {'calcsize': 1,
                                                               'count': [1],
                                                               'decltype': 'unsigned_char',
                                                               'offset': 35}},
                                                  {'PH_SEL1': {'calcsize': 1,
                                                               'count': [1],
                                                               'decltype': 'unsigned_char',
                                                               'offset': 36}},
                                                  {'AMUX1_SEL1': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 37}},
                                                  {'AMUX1_SEL0': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 38}},
                                                  {'AMUX2_SEL2': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 39}},
                                                  {'AMUX2_SEL1': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 40}},
                                                  {'AMUX2_SEL0': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 41}},
                                                  {'AMUX3_SEL1': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 42}},
                                                  {'AMUX3_SEL0': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 43}},
                                                  {'EN_DIV': {'calcsize': 1,
                                                              'count': [1],
                                                              'decltype': 'unsigned_char',
                                                              'offset': 44}},
                                                  {'SEL_DIVBUF': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 45}},
                                                  {'SEL_DIV': {'calcsize': 1,
                                                               'count': [1],
                                                               'decltype': 'unsigned_char',
                                                               'offset': 46}},
                                                  {'DIS_DIVOUT': {'calcsize': 1,
                                                                  'count': [1],
                                                                  'decltype': 'unsigned_char',
                                                                  'offset': 47}}]},
 'sys_param_rfictx_select_t': {'calcsize': 4,
                               'decltype': 'struct',
                               'member': [{'rfictx_sel': {'calcsize': 4,
                                                          'count': [1],
                                                          'decltype': 'int',
                                                          'offset': 0}}]},
 'sys_param_rs485_protocol_setup_t': {'calcsize': 36,
                                      'decltype': 'struct',
                                      'member': [{'commtype': {'calcsize': 4,
                                                               'count': [1],
                                                               'decltype': 'int',
                                                               'offset': 0}},
                                                 {'highspeed_en': {'calcsize': 4,
                                                                   'count': [1],
                                                                   'decltype': 'int',
                                                                   'offset': 4}},
                                                 {'baudrate_default': {'calcsize': 4,
                                                                       'count': [1],
                                                                       'decltype': 'int',
                                                                       'offset': 8}},
                                                 {'baudrate_high': {'calcsize': 4,
                                                                    'count': [1],
                                                                    'decltype': 'int',
                                                                    'offset': 12}},
                                                 {'packettype': {'calcsize': 4,
                                                                 'count': [1],
                                                                 'decltype': 'int',
                                                                 'offset': 16}},
                                                 {'tbd0': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'int',
                                                           'offset': 20}},
                                                 {'tbd1': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'int',
                                                           'offset': 24}},
                                                 {'tbd2': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'int',
                                                           'offset': 28}},
                                                 {'tbd3': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'int',
                                                           'offset': 32}}]},
 'sys_param_rsm_setup_t': {'calcsize': 16,
                           'decltype': 'struct',
                           'member': [{'mode': {'calcsize': 4,
                                                'count': [1],
                                                'decltype': 'int',
                                                'offset': 0}},
                                      {'userfreq': {'calcsize': 4,
                                                    'count': [1],
                                                    'decltype': 'float',
                                                    'offset': 4}},
                                      {'scanrate': {'calcsize': 4,
                                                    'count': [1],
                                                    'decltype': 'int',
                                                    'offset': 8}},
                                      {'daq_sampledelay': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'int',
                                                           'offset': 12}}]},
 'sys_param_rsp_eol_phasecal_t': {'calcsize': 8,
                                  'decltype': 'struct',
                                  'member': [{'real': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'float',
                                                       'offset': 0}},
                                             {'imag': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'float',
                                                       'offset': 4}}]},
 'sys_param_rsp_eol_setup_t': {'calcsize': 23184,
                               'decltype': 'struct',
                               'member': [{'en': {'calcsize': 1,
                                                  'count': [1],
                                                  'decltype': 'unsigned_char',
                                                  'offset': 0}},
                                          {'phasecal': {'calcsize': 8,
                                                        'count': [4],
                                                        'decltype': 'sys_param_rsp_eol_phasecal_t',
                                                        'offset': 4}},
                                          {'noise_level_up': {'calcsize': 4,
                                                              'count': [4],
                                                              'decltype': 'float',
                                                              'offset': 36}},
                                          {'noise_level_dn': {'calcsize': 4,
                                                              'count': [4],
                                                              'decltype': 'float',
                                                              'offset': 52}},
                                          {'aziangstep': {'calcsize': 4,
                                                          'count': [1],
                                                          'decltype': 'float',
                                                          'offset': 68}},
                                          {'aziangmin': {'calcsize': 4,
                                                         'count': [1],
                                                         'decltype': 'float',
                                                         'offset': 72}},
                                          {'aziangmax': {'calcsize': 4,
                                                         'count': [1],
                                                         'decltype': 'float',
                                                         'offset': 76}},
                                          {'azibeampattern_up': {'calcsize': 4,
                                                                 'count': [4,
                                                                           361],
                                                                 'decltype': 'float',
                                                                 'offset': 80}},
                                          {'azibeamphase_up': {'calcsize': 4,
                                                               'count': [4,
                                                                         361],
                                                               'decltype': 'float',
                                                               'offset': 5856}},
                                          {'azibeampattern_dn': {'calcsize': 4,
                                                                 'count': [4,
                                                                           361],
                                                                 'decltype': 'float',
                                                                 'offset': 11632}},
                                          {'azibeamphase_dn': {'calcsize': 4,
                                                               'count': [4,
                                                                         361],
                                                               'decltype': 'float',
                                                               'offset': 17408}}]},
 'sys_param_rsp_install_setup_t': {'calcsize': 20,
                                   'decltype': 'struct',
                                   'member': [{'height': {'calcsize': 4,
                                                          'count': [1],
                                                          'decltype': 'float',
                                                          'offset': 0}},
                                              {'ele_angle': {'calcsize': 4,
                                                             'count': [1],
                                                             'decltype': 'float',
                                                             'offset': 4}},
                                              {'azi_angle': {'calcsize': 4,
                                                             'count': [1],
                                                             'decltype': 'float',
                                                             'offset': 8}},
                                              {'offset_x': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'float',
                                                            'offset': 12}},
                                              {'offset_y': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'float',
                                                            'offset': 16}}]},
 'sys_param_rsptrk_posttune_t': {'calcsize': 64,
                                 'decltype': 'struct',
                                 'member': [{'LongGate1': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'float',
                                                           'offset': 0}},
                                            {'LongGate2': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'float',
                                                           'offset': 4}},
                                            {'LongGate3': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'float',
                                                           'offset': 8}},
                                            {'LongGateByVel_Gain': {'calcsize': 4,
                                                                    'count': [1],
                                                                    'decltype': 'float',
                                                                    'offset': 12}},
                                            {'MotorCycle_PowTh': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'float',
                                                                  'offset': 16}},
                                            {'MotorCycle_PowTh2': {'calcsize': 4,
                                                                   'count': [1],
                                                                   'decltype': 'float',
                                                                   'offset': 20}},
                                            {'MotorCycleByRange_Gain': {'calcsize': 4,
                                                                        'count': [1],
                                                                        'decltype': 'float',
                                                                        'offset': 24}},
                                            {'TrackOutFilter': {'calcsize': 4,
                                                                'count': [1],
                                                                'decltype': 'int',
                                                                'offset': 28}},
                                            {'tbd8': {'calcsize': 4,
                                                      'count': [1],
                                                      'decltype': 'float',
                                                      'offset': 32}},
                                            {'tbd9': {'calcsize': 4,
                                                      'count': [1],
                                                      'decltype': 'float',
                                                      'offset': 36}},
                                            {'tbd10': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'float',
                                                       'offset': 40}},
                                            {'tbd11': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'float',
                                                       'offset': 44}},
                                            {'tbd12': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'float',
                                                       'offset': 48}},
                                            {'tbd13': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'float',
                                                       'offset': 52}},
                                            {'tbd14': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'float',
                                                       'offset': 56}},
                                            {'tbd15': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'float',
                                                       'offset': 60}}]},
 'sys_param_rsptrk_setup_t': {'calcsize': 108,
                              'decltype': 'struct',
                              'member': [{'posttune': {'calcsize': 64,
                                                       'count': [1],
                                                       'decltype': 'sys_param_rsptrk_posttune_t',
                                                       'offset': 0}},
                                         {'trktune': {'calcsize': 44,
                                                      'count': [1],
                                                      'decltype': 'sys_param_rsptrk_trktune_t',
                                                      'offset': 64}}]},
 'sys_param_rsptrk_trktune_t': {'calcsize': 44,
                                'decltype': 'struct',
                                'member': [{'s16Pt_New2Vrf': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 0}},
                                           {'s16Pt_Max': {'calcsize': 4,
                                                          'count': [1],
                                                          'decltype': 'int',
                                                          'offset': 4}},
                                           {'s16Pt_New_Upd': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 8}},
                                           {'s16Pt_New_Coast': {'calcsize': 4,
                                                                'count': [1],
                                                                'decltype': 'int',
                                                                'offset': 12}},
                                           {'s16Pt_Vrf_Upd': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 16}},
                                           {'s16Pt_Vrf_Coast': {'calcsize': 4,
                                                                'count': [1],
                                                                'decltype': 'int',
                                                                'offset': 20}},
                                           {'f32Pt_NearRange': {'calcsize': 4,
                                                                'count': [1],
                                                                'decltype': 'float',
                                                                'offset': 24}},
                                           {'s16Pt_Vrf_Upd_Near': {'calcsize': 4,
                                                                   'count': [1],
                                                                   'decltype': 'int',
                                                                   'offset': 28}},
                                           {'s16Pt_Vrf_Coast_Near': {'calcsize': 4,
                                                                     'count': [1],
                                                                     'decltype': 'int',
                                                                     'offset': 32}},
                                           {'f32R_GateByEle_W': {'calcsize': 4,
                                                                 'count': [1],
                                                                 'decltype': 'float',
                                                                 'offset': 36}},
                                           {'f32V_GateByEle_W': {'calcsize': 4,
                                                                 'count': [1],
                                                                 'decltype': 'float',
                                                                 'offset': 40}}]},
 'sys_param_security_setup_t': {'calcsize': 196,
                                'decltype': 'struct',
                                'member': [{'lock_en': {'calcsize': 1,
                                                        'count': [1],
                                                        'decltype': 'unsigned_char',
                                                        'offset': 0}},
                                           {'admin_password': {'calcsize': 1,
                                                               'count': [32],
                                                               'decltype': 'char',
                                                               'offset': 4}},
                                           {'user_password': {'calcsize': 1,
                                                              'count': [32],
                                                              'decltype': 'char',
                                                              'offset': 36}},
                                           {'type': {'calcsize': 1,
                                                     'count': [32],
                                                     'decltype': 'char',
                                                     'offset': 68}},
                                           {'latitude': {'calcsize': 1,
                                                         'count': [32],
                                                         'decltype': 'char',
                                                         'offset': 100}},
                                           {'longitude': {'calcsize': 1,
                                                          'count': [32],
                                                          'decltype': 'char',
                                                          'offset': 132}},
                                           {'direction': {'calcsize': 1,
                                                          'count': [32],
                                                          'decltype': 'char',
                                                          'offset': 164}}]},
 'sys_param_serialnumber_setup_t': {'calcsize': 96,
                                    'decltype': 'struct',
                                    'member': [{'sys': {'calcsize': 1,
                                                        'count': [32],
                                                        'decltype': 'char',
                                                        'offset': 0}},
                                               {'be': {'calcsize': 1,
                                                       'count': [32],
                                                       'decltype': 'char',
                                                       'offset': 32}},
                                               {'fe': {'calcsize': 1,
                                                       'count': [32],
                                                       'decltype': 'char',
                                                       'offset': 64}}]},
 'sys_param_sid0did0_systembase_config_t': {'calcsize': 372,
                                            'decltype': 'struct',
                                            'member': [{'sid': {'calcsize': 4,
                                                                'count': [1],
                                                                'decltype': 'int',
                                                                'offset': 0}},
                                                       {'did': {'calcsize': 4,
                                                                'count': [1],
                                                                'decltype': 'int',
                                                                'offset': 4}},
                                                       {'setup': {'calcsize': 364,
                                                                  'count': [1],
                                                                  'decltype': 'sys_param_system_config_t',
                                                                  'offset': 8}}]},
 'sys_param_sid0did10_rsp_eol_config_t': {'calcsize': 23192,
                                          'decltype': 'struct',
                                          'member': [{'sid': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 0}},
                                                     {'did': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 4}},
                                                     {'setup': {'calcsize': 23184,
                                                                'count': [1],
                                                                'decltype': 'sys_param_rsp_eol_setup_t',
                                                                'offset': 8}}]},
 'sys_param_sid0did11_rsp_install_config_t': {'calcsize': 28,
                                              'decltype': 'struct',
                                              'member': [{'sid': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'int',
                                                                  'offset': 0}},
                                                         {'did': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'int',
                                                                  'offset': 4}},
                                                         {'setup': {'calcsize': 20,
                                                                    'count': [1],
                                                                    'decltype': 'sys_param_rsp_install_setup_t',
                                                                    'offset': 8}}]},
 'sys_param_sid0did12_rsm_config_t': {'calcsize': 24,
                                      'decltype': 'struct',
                                      'member': [{'sid': {'calcsize': 4,
                                                          'count': [1],
                                                          'decltype': 'int',
                                                          'offset': 0}},
                                                 {'did': {'calcsize': 4,
                                                          'count': [1],
                                                          'decltype': 'int',
                                                          'offset': 4}},
                                                 {'setup': {'calcsize': 16,
                                                            'count': [1],
                                                            'decltype': 'sys_param_rsm_setup_t',
                                                            'offset': 8}}]},
 'sys_param_sid0did13_rsptrk_config_t': {'calcsize': 116,
                                         'decltype': 'struct',
                                         'member': [{'sid': {'calcsize': 4,
                                                             'count': [1],
                                                             'decltype': 'int',
                                                             'offset': 0}},
                                                    {'did': {'calcsize': 4,
                                                             'count': [1],
                                                             'decltype': 'int',
                                                             'offset': 4}},
                                                    {'setup': {'calcsize': 108,
                                                               'count': [1],
                                                               'decltype': 'sys_param_rsptrk_setup_t',
                                                               'offset': 8}}]},
 'sys_param_sid0did1_datetime_config_t': {'calcsize': 60,
                                          'decltype': 'struct',
                                          'member': [{'sid': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 0}},
                                                     {'did': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 4}},
                                                     {'setup': {'calcsize': 52,
                                                                'count': [1],
                                                                'decltype': 'sys_param_datetime_setup_t',
                                                                'offset': 8}}]},
 'sys_param_sid0did200_app_packet_config_t': {'calcsize': 236,
                                              'decltype': 'struct',
                                              'member': [{'sid': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'int',
                                                                  'offset': 0}},
                                                         {'did': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'int',
                                                                  'offset': 4}},
                                                         {'setup': {'calcsize': 228,
                                                                    'count': [1],
                                                                    'decltype': 'sys_param_app_packet_setup_t',
                                                                    'offset': 8}}]},
 'sys_param_sid0did2_security_config_t': {'calcsize': 204,
                                          'decltype': 'struct',
                                          'member': [{'sid': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 0}},
                                                     {'did': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 4}},
                                                     {'setup': {'calcsize': 196,
                                                                'count': [1],
                                                                'decltype': 'sys_param_security_setup_t',
                                                                'offset': 8}}]},
 'sys_param_sid0did30_rfictx_select_config_t': {'calcsize': 12,
                                                'decltype': 'struct',
                                                'member': [{'sid': {'calcsize': 4,
                                                                    'count': [1],
                                                                    'decltype': 'int',
                                                                    'offset': 0}},
                                                           {'did': {'calcsize': 4,
                                                                    'count': [1],
                                                                    'decltype': 'int',
                                                                    'offset': 4}},
                                                           {'setup': {'calcsize': 4,
                                                                      'count': [1],
                                                                      'decltype': 'sys_param_rfictx_select_t',
                                                                      'offset': 8}}]},
 'sys_param_sid0did31_rfictx_bgt24at2_config_t': {'calcsize': 56,
                                                  'decltype': 'struct',
                                                  'member': [{'sid': {'calcsize': 4,
                                                                      'count': [1],
                                                                      'decltype': 'int',
                                                                      'offset': 0}},
                                                             {'did': {'calcsize': 4,
                                                                      'count': [1],
                                                                      'decltype': 'int',
                                                                      'offset': 4}},
                                                             {'setup': {'calcsize': 48,
                                                                        'count': [1],
                                                                        'decltype': 'sys_param_rfictx_bgt24at2_setup_t',
                                                                        'offset': 8}}]},
 'sys_param_sid0did3_network_config_t': {'calcsize': 176,
                                         'decltype': 'struct',
                                         'member': [{'sid': {'calcsize': 4,
                                                             'count': [1],
                                                             'decltype': 'int',
                                                             'offset': 0}},
                                                    {'did': {'calcsize': 4,
                                                             'count': [1],
                                                             'decltype': 'int',
                                                             'offset': 4}},
                                                    {'setup': {'calcsize': 168,
                                                               'count': [1],
                                                               'decltype': 'sys_param_common_comm_ethernet_config_t',
                                                               'offset': 8}}]},
 'sys_param_sid0did40_rficrx_select_config_t': {'calcsize': 12,
                                                'decltype': 'struct',
                                                'member': [{'sid': {'calcsize': 4,
                                                                    'count': [1],
                                                                    'decltype': 'int',
                                                                    'offset': 0}},
                                                           {'did': {'calcsize': 4,
                                                                    'count': [1],
                                                                    'decltype': 'int',
                                                                    'offset': 4}},
                                                           {'setup': {'calcsize': 4,
                                                                      'count': [1],
                                                                      'decltype': 'sys_param_rficrx_select_t',
                                                                      'offset': 8}}]},
 'sys_param_sid0did41_rficrx_bgt24ar4_config_t': {'calcsize': 40,
                                                  'decltype': 'struct',
                                                  'member': [{'sid': {'calcsize': 4,
                                                                      'count': [1],
                                                                      'decltype': 'int',
                                                                      'offset': 0}},
                                                             {'did': {'calcsize': 4,
                                                                      'count': [1],
                                                                      'decltype': 'int',
                                                                      'offset': 4}},
                                                             {'setup': {'calcsize': 32,
                                                                        'count': [1],
                                                                        'decltype': 'sys_param_rficrx_bgt24ar4_setup_t',
                                                                        'offset': 8}}]},
 'sys_param_sid0did4_infra_config_t': {'calcsize': 776,
                                       'decltype': 'struct',
                                       'member': [{'sid': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'int',
                                                           'offset': 0}},
                                                  {'did': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'int',
                                                           'offset': 4}},
                                                  {'setup': {'calcsize': 768,
                                                             'count': [1],
                                                             'decltype': 'sys_param_infra_setup_t',
                                                             'offset': 8}}]},
 'sys_param_sid0did50_pll_select_config_t': {'calcsize': 12,
                                             'decltype': 'struct',
                                             'member': [{'sid': {'calcsize': 4,
                                                                 'count': [1],
                                                                 'decltype': 'int',
                                                                 'offset': 0}},
                                                        {'did': {'calcsize': 4,
                                                                 'count': [1],
                                                                 'decltype': 'int',
                                                                 'offset': 4}},
                                                        {'setup': {'calcsize': 4,
                                                                   'count': [1],
                                                                   'decltype': 'sys_param_pll_select_t',
                                                                   'offset': 8}}]},
 'sys_param_sid0did51_pll_lmx2491_config_t': {'calcsize': 16,
                                              'decltype': 'struct',
                                              'member': [{'sid': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'int',
                                                                  'offset': 0}},
                                                         {'did': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'int',
                                                                  'offset': 4}},
                                                         {'setup': {'calcsize': 8,
                                                                    'count': [1],
                                                                    'decltype': 'sys_param_pll_lmx2491_setup_t',
                                                                    'offset': 8}}]},
 'sys_param_sid0did5_serialnumber_config_t': {'calcsize': 104,
                                              'decltype': 'struct',
                                              'member': [{'sid': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'int',
                                                                  'offset': 0}},
                                                         {'did': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'int',
                                                                  'offset': 4}},
                                                         {'setup': {'calcsize': 96,
                                                                    'count': [1],
                                                                    'decltype': 'sys_param_serialnumber_setup_t',
                                                                    'offset': 8}}]},
 'sys_param_sid0did60_adc_select_config_t': {'calcsize': 12,
                                             'decltype': 'struct',
                                             'member': [{'sid': {'calcsize': 4,
                                                                 'count': [1],
                                                                 'decltype': 'int',
                                                                 'offset': 0}},
                                                        {'did': {'calcsize': 4,
                                                                 'count': [1],
                                                                 'decltype': 'int',
                                                                 'offset': 4}},
                                                        {'setup': {'calcsize': 4,
                                                                   'count': [1],
                                                                   'decltype': 'sys_param_adc_select_t',
                                                                   'offset': 8}}]},
 'sys_param_sid0did61_adc_adar7251_config_t': {'calcsize': 60,
                                               'decltype': 'struct',
                                               'member': [{'sid': {'calcsize': 4,
                                                                   'count': [1],
                                                                   'decltype': 'int',
                                                                   'offset': 0}},
                                                          {'did': {'calcsize': 4,
                                                                   'count': [1],
                                                                   'decltype': 'int',
                                                                   'offset': 4}},
                                                          {'setup': {'calcsize': 52,
                                                                     'count': [1],
                                                                     'decltype': 'sys_param_adc_adar7251_setup_t',
                                                                     'offset': 8}}]},
 'sys_param_sid0did62_adc_max11043_config_t': {'calcsize': 88,
                                               'decltype': 'struct',
                                               'member': [{'sid': {'calcsize': 4,
                                                                   'count': [1],
                                                                   'decltype': 'int',
                                                                   'offset': 0}},
                                                          {'did': {'calcsize': 4,
                                                                   'count': [1],
                                                                   'decltype': 'int',
                                                                   'offset': 4}},
                                                          {'setup': {'calcsize': 80,
                                                                     'count': [1],
                                                                     'decltype': 'sys_param_adc_max11043_setup_t',
                                                                     'offset': 8}}]},
 'sys_param_sid0did6_location_config_t': {'calcsize': 116,
                                          'decltype': 'struct',
                                          'member': [{'sid': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 0}},
                                                     {'did': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 4}},
                                                     {'setup': {'calcsize': 108,
                                                                'count': [1],
                                                                'decltype': 'sys_param_location_setup_t',
                                                                'offset': 8}}]},
 'sys_param_sid0did7_jctbox_config_t': {'calcsize': 44,
                                        'decltype': 'struct',
                                        'member': [{'sid': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'int',
                                                            'offset': 0}},
                                                   {'did': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'int',
                                                            'offset': 4}},
                                                   {'setup': {'calcsize': 36,
                                                              'count': [1],
                                                              'decltype': 'sys_param_jctbox_setup_t',
                                                              'offset': 8}}]},
 'sys_param_sid0did8_rs485_protocol_config_t': {'calcsize': 44,
                                                'decltype': 'struct',
                                                'member': [{'sid': {'calcsize': 4,
                                                                    'count': [1],
                                                                    'decltype': 'int',
                                                                    'offset': 0}},
                                                           {'did': {'calcsize': 4,
                                                                    'count': [1],
                                                                    'decltype': 'int',
                                                                    'offset': 4}},
                                                           {'setup': {'calcsize': 36,
                                                                      'count': [1],
                                                                      'decltype': 'sys_param_rs485_protocol_setup_t',
                                                                      'offset': 8}}]},
 'sys_param_sid0did9_camera_config_t': {'calcsize': 148,
                                        'decltype': 'struct',
                                        'member': [{'sid': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'int',
                                                            'offset': 0}},
                                                   {'did': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'int',
                                                            'offset': 4}},
                                                   {'setup': {'calcsize': 140,
                                                              'count': [1],
                                                              'decltype': 'sys_param_camera_setup_t',
                                                              'offset': 8}}]},
 'sys_param_sid10did0_fcw_config_t': {'calcsize': 96,
                                      'decltype': 'struct',
                                      'member': [{'sid': {'calcsize': 4,
                                                          'count': [1],
                                                          'decltype': 'int',
                                                          'offset': 0}},
                                                 {'did': {'calcsize': 4,
                                                          'count': [1],
                                                          'decltype': 'int',
                                                          'offset': 4}},
                                                 {'setup': {'calcsize': 88,
                                                            'count': [1],
                                                            'decltype': 'sys_param_fcw_setup_t',
                                                            'offset': 8}}]},
 'sys_param_sid10did1_fcwtest_config_t': {'calcsize': 20,
                                          'decltype': 'struct',
                                          'member': [{'sid': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 0}},
                                                     {'did': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 4}},
                                                     {'setup': {'calcsize': 12,
                                                                'count': [1],
                                                                'decltype': 'sys_param_fcwtest_setup_t',
                                                                'offset': 8}}]},
 'sys_param_sid6did0_candrv_config_t': {'calcsize': 124,
                                        'decltype': 'struct',
                                        'member': [{'sid': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'int',
                                                            'offset': 0}},
                                                   {'did': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'int',
                                                            'offset': 4}},
                                                   {'setup': {'calcsize': 116,
                                                              'count': [1],
                                                              'decltype': 'sys_param_candrv_setup_t',
                                                              'offset': 8}}]},
 'sys_param_sid6did1_cansignal_config_t': {'calcsize': 1288,
                                           'decltype': 'struct',
                                           'member': [{'sid': {'calcsize': 4,
                                                               'count': [1],
                                                               'decltype': 'int',
                                                               'offset': 0}},
                                                      {'did': {'calcsize': 4,
                                                               'count': [1],
                                                               'decltype': 'int',
                                                               'offset': 4}},
                                                      {'setup': {'calcsize': 1280,
                                                                 'count': [1],
                                                                 'decltype': 'sys_param_cansignal_setup_t',
                                                                 'offset': 8}}]},
 'sys_param_sid6did2_cantxmsg_config_t': {'calcsize': 56,
                                          'decltype': 'struct',
                                          'member': [{'sid': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 0}},
                                                     {'did': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 4}},
                                                     {'setup': {'calcsize': 48,
                                                                'count': [1],
                                                                'decltype': 'sys_param_cantxmsg_setup_t',
                                                                'offset': 8}}]},
 'sys_param_sid7did0_filesystem_config_t': {'calcsize': 20,
                                            'decltype': 'struct',
                                            'member': [{'sid': {'calcsize': 4,
                                                                'count': [1],
                                                                'decltype': 'int',
                                                                'offset': 0}},
                                                       {'did': {'calcsize': 4,
                                                                'count': [1],
                                                                'decltype': 'int',
                                                                'offset': 4}},
                                                       {'setup': {'calcsize': 12,
                                                                  'count': [1],
                                                                  'decltype': 'sys_param_filesystem_setup_t',
                                                                  'offset': 8}}]},
 'sys_param_sid8did0_its_config_t': {'calcsize': 9956,
                                     'decltype': 'struct',
                                     'member': [{'sid': {'calcsize': 4,
                                                         'count': [1],
                                                         'decltype': 'int',
                                                         'offset': 0}},
                                                {'did': {'calcsize': 4,
                                                         'count': [1],
                                                         'decltype': 'int',
                                                         'offset': 4}},
                                                {'description': {'calcsize': 1,
                                                                 'count': [32],
                                                                 'decltype': 'char',
                                                                 'offset': 8}},
                                                {'setup': {'calcsize': 9916,
                                                           'count': [1],
                                                           'decltype': 'sys_param_its_setup_t',
                                                           'offset': 40}}]},
 'sys_param_sid8did10_its_testmode_config_t': {'calcsize': 112,
                                               'decltype': 'struct',
                                               'member': [{'sid': {'calcsize': 4,
                                                                   'count': [1],
                                                                   'decltype': 'int',
                                                                   'offset': 0}},
                                                          {'did': {'calcsize': 4,
                                                                   'count': [1],
                                                                   'decltype': 'int',
                                                                   'offset': 4}},
                                                          {'description': {'calcsize': 1,
                                                                           'count': [32],
                                                                           'decltype': 'char',
                                                                           'offset': 8}},
                                                          {'setup': {'calcsize': 72,
                                                                     'count': [1],
                                                                     'decltype': 'sys_param_its_testmode_setup_t',
                                                                     'offset': 40}}]},
 'sys_param_sid8did1_its_relay_config_t': {'calcsize': 116,
                                           'decltype': 'struct',
                                           'member': [{'sid': {'calcsize': 4,
                                                               'count': [1],
                                                               'decltype': 'int',
                                                               'offset': 0}},
                                                      {'did': {'calcsize': 4,
                                                               'count': [1],
                                                               'decltype': 'int',
                                                               'offset': 4}},
                                                      {'description': {'calcsize': 1,
                                                                       'count': [32],
                                                                       'decltype': 'char',
                                                                       'offset': 8}},
                                                      {'setup': {'calcsize': 76,
                                                                 'count': [1],
                                                                 'decltype': 'sys_param_its_device_setup_t',
                                                                 'offset': 40}}]},
 'sys_param_sid8did2_its_align_config_t': {'calcsize': 56,
                                           'decltype': 'struct',
                                           'member': [{'sid': {'calcsize': 4,
                                                               'count': [1],
                                                               'decltype': 'int',
                                                               'offset': 0}},
                                                      {'did': {'calcsize': 4,
                                                               'count': [1],
                                                               'decltype': 'int',
                                                               'offset': 4}},
                                                      {'description': {'calcsize': 1,
                                                                       'count': [32],
                                                                       'decltype': 'char',
                                                                       'offset': 8}},
                                                      {'setup': {'calcsize': 16,
                                                                 'count': [1],
                                                                 'decltype': 'sys_param_its_alignment_setup_t',
                                                                 'offset': 40}}]},
 'sys_param_sid9did0_vf_reflector_config_t': {'calcsize': 48,
                                              'decltype': 'struct',
                                              'member': [{'sid': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'int',
                                                                  'offset': 0}},
                                                         {'did': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'int',
                                                                  'offset': 4}},
                                                         {'setup': {'calcsize': 40,
                                                                    'count': [1],
                                                                    'decltype': 'sys_param_vf_reflector_setup_t',
                                                                    'offset': 8}}]},
 'sys_param_sid9did1_vf_server_config_t': {'calcsize': 64,
                                           'decltype': 'struct',
                                           'member': [{'sid': {'calcsize': 4,
                                                               'count': [1],
                                                               'decltype': 'int',
                                                               'offset': 0}},
                                                      {'did': {'calcsize': 4,
                                                               'count': [1],
                                                               'decltype': 'int',
                                                               'offset': 4}},
                                                      {'setup': {'calcsize': 56,
                                                                 'count': [1],
                                                                 'decltype': 'sys_param_vf_server_setup_t',
                                                                 'offset': 8}}]},
 'sys_param_sid9did2_vf_relay_config_t': {'calcsize': 92,
                                          'decltype': 'struct',
                                          'member': [{'sid': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 0}},
                                                     {'did': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'int',
                                                              'offset': 4}},
                                                     {'setup': {'calcsize': 84,
                                                                'count': [1],
                                                                'decltype': 'sys_param_vf_relay_setup_t',
                                                                'offset': 8}}]},
 'sys_param_sid9did3_vf_ui_config_t': {'calcsize': 24,
                                       'decltype': 'struct',
                                       'member': [{'sid': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'int',
                                                           'offset': 0}},
                                                  {'did': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'int',
                                                           'offset': 4}},
                                                  {'setup': {'calcsize': 16,
                                                             'count': [1],
                                                             'decltype': 'sys_param_vf_ui_setup_t',
                                                             'offset': 8}}]},
 'sys_param_sidxdidx_configinfo_packing_t': {'calcsize': 38076,
                                             'decltype': 'struct',
                                             'member': [{'data_start_marker': {'calcsize': 4,
                                                                               'count': [1],
                                                                               'decltype': 'int',
                                                                               'offset': 0}},
                                                        {'param_version': {'calcsize': 4,
                                                                           'count': [1],
                                                                           'decltype': 'int',
                                                                           'offset': 4}},
                                                        {'guidstr': {'calcsize': 1,
                                                                     'count': [36],
                                                                     'decltype': 'char',
                                                                     'offset': 8}},
                                                        {'sid0did0_systembase_config': {'calcsize': 372,
                                                                                        'count': [1],
                                                                                        'decltype': 'sys_param_sid0did0_systembase_config_t',
                                                                                        'offset': 44}},
                                                        {'sid0did1_datetime_config': {'calcsize': 60,
                                                                                      'count': [1],
                                                                                      'decltype': 'sys_param_sid0did1_datetime_config_t',
                                                                                      'offset': 416}},
                                                        {'sid0did2_security_config': {'calcsize': 204,
                                                                                      'count': [1],
                                                                                      'decltype': 'sys_param_sid0did2_security_config_t',
                                                                                      'offset': 476}},
                                                        {'sid0did3_network_config': {'calcsize': 176,
                                                                                     'count': [1],
                                                                                     'decltype': 'sys_param_sid0did3_network_config_t',
                                                                                     'offset': 680}},
                                                        {'sid0did4_infra_config': {'calcsize': 776,
                                                                                   'count': [1],
                                                                                   'decltype': 'sys_param_sid0did4_infra_config_t',
                                                                                   'offset': 856}},
                                                        {'sid0did5_serialnumber_config': {'calcsize': 104,
                                                                                          'count': [1],
                                                                                          'decltype': 'sys_param_sid0did5_serialnumber_config_t',
                                                                                          'offset': 1632}},
                                                        {'sid0did6_location_config': {'calcsize': 116,
                                                                                      'count': [1],
                                                                                      'decltype': 'sys_param_sid0did6_location_config_t',
                                                                                      'offset': 1736}},
                                                        {'sid0did7_jctbox_config': {'calcsize': 44,
                                                                                    'count': [1],
                                                                                    'decltype': 'sys_param_sid0did7_jctbox_config_t',
                                                                                    'offset': 1852}},
                                                        {'sid0did8_rs485_protocol_config': {'calcsize': 44,
                                                                                            'count': [1],
                                                                                            'decltype': 'sys_param_sid0did8_rs485_protocol_config_t',
                                                                                            'offset': 1896}},
                                                        {'sid0did9_camera_config': {'calcsize': 148,
                                                                                    'count': [1],
                                                                                    'decltype': 'sys_param_sid0did9_camera_config_t',
                                                                                    'offset': 1940}},
                                                        {'sid0did10_rsp_eol_config': {'calcsize': 23192,
                                                                                      'count': [1],
                                                                                      'decltype': 'sys_param_sid0did10_rsp_eol_config_t',
                                                                                      'offset': 2088}},
                                                        {'sid0did11_rsp_install_config': {'calcsize': 28,
                                                                                          'count': [1],
                                                                                          'decltype': 'sys_param_sid0did11_rsp_install_config_t',
                                                                                          'offset': 25280}},
                                                        {'sid0did12_rsm_config': {'calcsize': 24,
                                                                                  'count': [1],
                                                                                  'decltype': 'sys_param_sid0did12_rsm_config_t',
                                                                                  'offset': 25308}},
                                                        {'sid0did13_rsptrk_config': {'calcsize': 116,
                                                                                     'count': [1],
                                                                                     'decltype': 'sys_param_sid0did13_rsptrk_config_t',
                                                                                     'offset': 25332}},
                                                        {'sid0did30_rfictx_select_config': {'calcsize': 12,
                                                                                            'count': [1],
                                                                                            'decltype': 'sys_param_sid0did30_rfictx_select_config_t',
                                                                                            'offset': 25448}},
                                                        {'sid0did31_rfictx_bgt24at2_config': {'calcsize': 56,
                                                                                              'count': [1],
                                                                                              'decltype': 'sys_param_sid0did31_rfictx_bgt24at2_config_t',
                                                                                              'offset': 25460}},
                                                        {'sid0did40_rficrx_select_config': {'calcsize': 12,
                                                                                            'count': [1],
                                                                                            'decltype': 'sys_param_sid0did40_rficrx_select_config_t',
                                                                                            'offset': 25516}},
                                                        {'sid0did41_rficrx_bgt24ar4_config': {'calcsize': 40,
                                                                                              'count': [1],
                                                                                              'decltype': 'sys_param_sid0did41_rficrx_bgt24ar4_config_t',
                                                                                              'offset': 25528}},
                                                        {'sid0did50_pll_select_config': {'calcsize': 12,
                                                                                         'count': [1],
                                                                                         'decltype': 'sys_param_sid0did50_pll_select_config_t',
                                                                                         'offset': 25568}},
                                                        {'sid0did51_pll_lmx2491_config': {'calcsize': 16,
                                                                                          'count': [1],
                                                                                          'decltype': 'sys_param_sid0did51_pll_lmx2491_config_t',
                                                                                          'offset': 25580}},
                                                        {'sid0did60_adc_select_config': {'calcsize': 12,
                                                                                         'count': [1],
                                                                                         'decltype': 'sys_param_sid0did60_adc_select_config_t',
                                                                                         'offset': 25596}},
                                                        {'sid0did61_adc_adar7251_config': {'calcsize': 60,
                                                                                           'count': [1],
                                                                                           'decltype': 'sys_param_sid0did61_adc_adar7251_config_t',
                                                                                           'offset': 25608}},
                                                        {'sid0did62_adc_max11043_config': {'calcsize': 88,
                                                                                           'count': [1],
                                                                                           'decltype': 'sys_param_sid0did62_adc_max11043_config_t',
                                                                                           'offset': 25668}},
                                                        {'sid0did200_app_packet_config': {'calcsize': 236,
                                                                                          'count': [1],
                                                                                          'decltype': 'sys_param_sid0did200_app_packet_config_t',
                                                                                          'offset': 25756}},
                                                        {'sid6did0_candrv_config': {'calcsize': 124,
                                                                                    'count': [1],
                                                                                    'decltype': 'sys_param_sid6did0_candrv_config_t',
                                                                                    'offset': 25992}},
                                                        {'sid6did1_cansignal_config': {'calcsize': 1288,
                                                                                       'count': [1],
                                                                                       'decltype': 'sys_param_sid6did1_cansignal_config_t',
                                                                                       'offset': 26116}},
                                                        {'sid6did2_cantxmsg_config': {'calcsize': 56,
                                                                                      'count': [1],
                                                                                      'decltype': 'sys_param_sid6did2_cantxmsg_config_t',
                                                                                      'offset': 27404}},
                                                        {'sid7did0_filesystem_config': {'calcsize': 20,
                                                                                        'count': [1],
                                                                                        'decltype': 'sys_param_sid7did0_filesystem_config_t',
                                                                                        'offset': 27460}},
                                                        {'sid8did0_its_config': {'calcsize': 9956,
                                                                                 'count': [1],
                                                                                 'decltype': 'sys_param_sid8did0_its_config_t',
                                                                                 'offset': 27480}},
                                                        {'sid8did1_its_relay_config': {'calcsize': 116,
                                                                                       'count': [1],
                                                                                       'decltype': 'sys_param_sid8did1_its_relay_config_t',
                                                                                       'offset': 37436}},
                                                        {'sid8did2_its_align_config': {'calcsize': 56,
                                                                                       'count': [1],
                                                                                       'decltype': 'sys_param_sid8did2_its_align_config_t',
                                                                                       'offset': 37552}},
                                                        {'sid8did10_its_testmode_config': {'calcsize': 112,
                                                                                           'count': [1],
                                                                                           'decltype': 'sys_param_sid8did10_its_testmode_config_t',
                                                                                           'offset': 37608}},
                                                        {'sid9did0_vf_reflector_config': {'calcsize': 48,
                                                                                          'count': [1],
                                                                                          'decltype': 'sys_param_sid9did0_vf_reflector_config_t',
                                                                                          'offset': 37720}},
                                                        {'sid9did1_vf_server_config': {'calcsize': 64,
                                                                                       'count': [1],
                                                                                       'decltype': 'sys_param_sid9did1_vf_server_config_t',
                                                                                       'offset': 37768}},
                                                        {'sid9did2_vf_relay_config': {'calcsize': 92,
                                                                                      'count': [1],
                                                                                      'decltype': 'sys_param_sid9did2_vf_relay_config_t',
                                                                                      'offset': 37832}},
                                                        {'sid9did3_vf_ui_config': {'calcsize': 24,
                                                                                   'count': [1],
                                                                                   'decltype': 'sys_param_sid9did3_vf_ui_config_t',
                                                                                   'offset': 37924}},
                                                        {'sid10did0_fcw_config': {'calcsize': 96,
                                                                                  'count': [1],
                                                                                  'decltype': 'sys_param_sid10did0_fcw_config_t',
                                                                                  'offset': 37948}},
                                                        {'sid10did1_fcwtest_config': {'calcsize': 20,
                                                                                      'count': [1],
                                                                                      'decltype': 'sys_param_sid10did1_fcwtest_config_t',
                                                                                      'offset': 38044}},
                                                        {'data_end_marker': {'calcsize': 4,
                                                                             'count': [1],
                                                                             'decltype': 'int',
                                                                             'offset': 38064}},
                                                        {'data_end_marker1': {'calcsize': 4,
                                                                              'count': [1],
                                                                              'decltype': 'int',
                                                                              'offset': 38068}},
                                                        {'data_end_marker2': {'calcsize': 4,
                                                                              'count': [1],
                                                                              'decltype': 'int',
                                                                              'offset': 38072}}]},
 'sys_param_status_data_ecuinfo_t': {'calcsize': 24,
                                     'decltype': 'struct',
                                     'member': [{'temp_core': {'calcsize': 4,
                                                               'count': [1],
                                                               'decltype': 'float',
                                                               'offset': 0}},
                                                {'temp_rfm': {'calcsize': 4,
                                                              'count': [1],
                                                              'decltype': 'float',
                                                              'offset': 4}},
                                                {'vin': {'calcsize': 4,
                                                         'count': [1],
                                                         'decltype': 'float',
                                                         'offset': 8}},
                                                {'v5': {'calcsize': 4,
                                                        'count': [1],
                                                        'decltype': 'float',
                                                        'offset': 12}},
                                                {'v1_5': {'calcsize': 4,
                                                          'count': [1],
                                                          'decltype': 'float',
                                                          'offset': 16}},
                                                {'v1_0': {'calcsize': 4,
                                                          'count': [1],
                                                          'decltype': 'float',
                                                          'offset': 20}}]},
 'sys_param_status_data_gps_t': {'calcsize': 1028,
                                 'decltype': 'struct',
                                 'member': [{'status': {'calcsize': 1,
                                                        'count': [1],
                                                        'decltype': 'unsigned_char',
                                                        'offset': 0}},
                                            {'data': {'calcsize': 1,
                                                      'count': [1024],
                                                      'decltype': 'char',
                                                      'offset': 4}}]},
 'sys_param_status_data_position_t': {'calcsize': 16,
                                      'decltype': 'struct',
                                      'member': [{'yaw': {'calcsize': 4,
                                                          'count': [1],
                                                          'decltype': 'float',
                                                          'offset': 0}},
                                                 {'roll': {'calcsize': 4,
                                                           'count': [1],
                                                           'decltype': 'float',
                                                           'offset': 4}},
                                                 {'pitch': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'float',
                                                            'offset': 8}},
                                                 {'altitude': {'calcsize': 4,
                                                               'count': [1],
                                                               'decltype': 'float',
                                                               'offset': 12}}]},
 'sys_param_status_timestamp_t': {'calcsize': 28,
                                  'decltype': 'struct',
                                  'member': [{'timestamp_s': {'calcsize': 8,
                                                              'count': [1],
                                                              'decltype': 'double',
                                                              'offset': 0}},
                                             {'rsp_timestamp_us': {'calcsize': 8,
                                                                   'count': [1],
                                                                   'decltype': 'long_long',
                                                                   'offset': 8}},
                                             {'net_timestamp_us': {'calcsize': 8,
                                                                   'count': [1],
                                                                   'decltype': 'long_long',
                                                                   'offset': 16}},
                                             {'rsp_cycletime': {'calcsize': 4,
                                                                'count': [1],
                                                                'decltype': 'float',
                                                                'offset': 24}}]},
 'sys_param_swupdate_config_t': {'calcsize': 20,
                                 'decltype': 'struct',
                                 'member': [{'swupdate_request': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'int',
                                                                  'offset': 0}},
                                            {'swupdate_type': {'calcsize': 4,
                                                               'count': [1],
                                                               'decltype': 'int',
                                                               'offset': 4}},
                                            {'swupdate_count': {'calcsize': 4,
                                                                'count': [1],
                                                                'decltype': 'int',
                                                                'offset': 8}},
                                            {'swupdate_timestamp': {'calcsize': 8,
                                                                    'count': [1],
                                                                    'decltype': 'double',
                                                                    'offset': 12}}]},
 'sys_param_system_config_t': {'calcsize': 364,
                               'decltype': 'struct',
                               'member': [{'swupdate': {'calcsize': 20,
                                                        'count': [1],
                                                        'decltype': 'sys_param_swupdate_config_t',
                                                        'offset': 0}},
                                          {'consolelog': {'calcsize': 28,
                                                          'count': [1],
                                                          'decltype': 'sys_param_consolelog_config_t',
                                                          'offset': 20}},
                                          {'consoleudp': {'calcsize': 40,
                                                          'count': [1],
                                                          'decltype': 'sys_param_consoleudp_config_t',
                                                          'offset': 48}},
                                          {'sensortype': {'calcsize': 96,
                                                          'count': [1],
                                                          'decltype': 'sys_param_system_sensortype_config_t',
                                                          'offset': 88}},
                                          {'eth_default': {'calcsize': 168,
                                                           'count': [1],
                                                           'decltype': 'sys_param_common_comm_ethernet_config_t',
                                                           'offset': 184}},
                                          {'syscontrol': {'calcsize': 8,
                                                          'count': [1],
                                                          'decltype': 'sys_param_system_control_t',
                                                          'offset': 352}},
                                          {'logiccontrol': {'calcsize': 4,
                                                            'count': [1],
                                                            'decltype': 'sys_param_logic_control_config_t',
                                                            'offset': 360}}]},
 'sys_param_system_control_t': {'calcsize': 8,
                                'decltype': 'struct',
                                'member': [{'restart_en': {'calcsize': 1,
                                                           'count': [1],
                                                           'decltype': 'unsigned_char',
                                                           'offset': 0}},
                                           {'restart_timeout_s': {'calcsize': 4,
                                                                  'count': [1],
                                                                  'decltype': 'int',
                                                                  'offset': 4}}]},
 'sys_param_system_sensortype_config_t': {'calcsize': 96,
                                          'decltype': 'struct',
                                          'member': [{'type': {'calcsize': 1,
                                                               'count': [32],
                                                               'decltype': 'char',
                                                               'offset': 0}},
                                                     {'serialnumber': {'calcsize': 1,
                                                                       'count': [32],
                                                                       'decltype': 'char',
                                                                       'offset': 32}},
                                                     {'opmode_its_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 64}},
                                                     {'opmode_vf_en': {'calcsize': 1,
                                                                       'count': [1],
                                                                       'decltype': 'unsigned_char',
                                                                       'offset': 65}},
                                                     {'opmode_fcw_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 66}},
                                                     {'opmode_lm_en': {'calcsize': 1,
                                                                       'count': [1],
                                                                       'decltype': 'unsigned_char',
                                                                       'offset': 67}},
                                                     {'pid_status_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 68}},
                                                     {'pid_object_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 69}},
                                                     {'pid_track_en': {'calcsize': 1,
                                                                       'count': [1],
                                                                       'decltype': 'unsigned_char',
                                                                       'offset': 70}},
                                                     {'pid_image_en': {'calcsize': 1,
                                                                       'count': [1],
                                                                       'decltype': 'unsigned_char',
                                                                       'offset': 71}},
                                                     {'pid_imagsp_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 72}},
                                                     {'pid_logger_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 73}},
                                                     {'pid_canlog_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 74}},
                                                     {'pid_sensor_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 75}},
                                                     {'pid_app_its_en': {'calcsize': 1,
                                                                         'count': [1],
                                                                         'decltype': 'unsigned_char',
                                                                         'offset': 76}},
                                                     {'pid_app_vf_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 77}},
                                                     {'pid_app_fcw_en': {'calcsize': 1,
                                                                         'count': [1],
                                                                         'decltype': 'unsigned_char',
                                                                         'offset': 78}},
                                                     {'pid_app_lm_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 79}},
                                                     {'raw_chirp_en': {'calcsize': 1,
                                                                       'count': [1],
                                                                       'decltype': 'unsigned_char',
                                                                       'offset': 80}},
                                                     {'raw_chirp0_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 81}},
                                                     {'raw_chirp1_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 82}},
                                                     {'raw_chirp2_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 83}},
                                                     {'raw_chirp3_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 84}},
                                                     {'raw_app_en': {'calcsize': 1,
                                                                     'count': [1],
                                                                     'decltype': 'unsigned_char',
                                                                     'offset': 85}},
                                                     {'raw_app_its_en': {'calcsize': 1,
                                                                         'count': [1],
                                                                         'decltype': 'unsigned_char',
                                                                         'offset': 86}},
                                                     {'raw_app_vf_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 87}},
                                                     {'raw_app_fcw_en': {'calcsize': 1,
                                                                         'count': [1],
                                                                         'decltype': 'unsigned_char',
                                                                         'offset': 88}},
                                                     {'raw_app_lm_en': {'calcsize': 1,
                                                                        'count': [1],
                                                                        'decltype': 'unsigned_char',
                                                                        'offset': 89}},
                                                     {'raw_app_install_en': {'calcsize': 1,
                                                                             'count': [1],
                                                                             'decltype': 'unsigned_char',
                                                                             'offset': 90}},
                                                     {'raw_app_flog_en': {'calcsize': 1,
                                                                          'count': [1],
                                                                          'decltype': 'unsigned_char',
                                                                          'offset': 91}},
                                                     {'raw_mon_en': {'calcsize': 1,
                                                                     'count': [1],
                                                                     'decltype': 'unsigned_char',
                                                                     'offset': 92}},
                                                     {'raw_mon_power_en': {'calcsize': 1,
                                                                           'count': [1],
                                                                           'decltype': 'unsigned_char',
                                                                           'offset': 93}},
                                                     {'raw_mon_time_en': {'calcsize': 1,
                                                                          'count': [1],
                                                                          'decltype': 'unsigned_char',
                                                                          'offset': 94}},
                                                     {'raw_mon_task_en': {'calcsize': 1,
                                                                          'count': [1],
                                                                          'decltype': 'unsigned_char',
                                                                          'offset': 95}}]},
 'sys_param_system_status_t': {'calcsize': 35648,
                               'decltype': 'struct',
                               'member': [{'devuid': {'calcsize': 1,
                                                      'count': [32],
                                                      'decltype': 'char',
                                                      'offset': 0}},
                                          {'serialnumber': {'calcsize': 1,
                                                            'count': [32],
                                                            'decltype': 'char',
                                                            'offset': 32}},
                                          {'swappname': {'calcsize': 1,
                                                         'count': [32],
                                                         'decltype': 'char',
                                                         'offset': 64}},
                                          {'swversion': {'calcsize': 1,
                                                         'count': [32],
                                                         'decltype': 'char',
                                                         'offset': 96}},
                                          {'swdate': {'calcsize': 4,
                                                      'count': [1],
                                                      'decltype': 'int',
                                                      'offset': 128}},
                                          {'swtime': {'calcsize': 4,
                                                      'count': [1],
                                                      'decltype': 'int',
                                                      'offset': 132}},
                                          {'sid0did0_systembase_config': {'calcsize': 372,
                                                                          'count': [1],
                                                                          'decltype': 'sys_param_sid0did0_systembase_config_t',
                                                                          'offset': 136}},
                                          {'sid0did1_datetime_config': {'calcsize': 60,
                                                                        'count': [1],
                                                                        'decltype': 'sys_param_sid0did1_datetime_config_t',
                                                                        'offset': 508}},
                                          {'sid0did2_security_config': {'calcsize': 204,
                                                                        'count': [1],
                                                                        'decltype': 'sys_param_sid0did2_security_config_t',
                                                                        'offset': 568}},
                                          {'sid0did4_infra_config': {'calcsize': 776,
                                                                     'count': [1],
                                                                     'decltype': 'sys_param_sid0did4_infra_config_t',
                                                                     'offset': 772}},
                                          {'sid0did5_serialnumber_config': {'calcsize': 104,
                                                                            'count': [1],
                                                                            'decltype': 'sys_param_sid0did5_serialnumber_config_t',
                                                                            'offset': 1548}},
                                          {'sid0did6_location_config': {'calcsize': 116,
                                                                        'count': [1],
                                                                        'decltype': 'sys_param_sid0did6_location_config_t',
                                                                        'offset': 1652}},
                                          {'sid0did8_rs485_protocol_config': {'calcsize': 44,
                                                                              'count': [1],
                                                                              'decltype': 'sys_param_sid0did8_rs485_protocol_config_t',
                                                                              'offset': 1768}},
                                          {'sid0did10_rsp_eol_config': {'calcsize': 23192,
                                                                        'count': [1],
                                                                        'decltype': 'sys_param_sid0did10_rsp_eol_config_t',
                                                                        'offset': 1812}},
                                          {'sid0did11_rsp_install_config': {'calcsize': 28,
                                                                            'count': [1],
                                                                            'decltype': 'sys_param_sid0did11_rsp_install_config_t',
                                                                            'offset': 25004}},
                                          {'sid0did12_rsm_config': {'calcsize': 24,
                                                                    'count': [1],
                                                                    'decltype': 'sys_param_sid0did12_rsm_config_t',
                                                                    'offset': 25032}},
                                          {'sid0did13_rsptrk_config': {'calcsize': 116,
                                                                       'count': [1],
                                                                       'decltype': 'sys_param_sid0did13_rsptrk_config_t',
                                                                       'offset': 25056}},
                                          {'sid0did200_app_packet_config': {'calcsize': 236,
                                                                            'count': [1],
                                                                            'decltype': 'sys_param_sid0did200_app_packet_config_t',
                                                                            'offset': 25172}},
                                          {'sid8did0_its_config': {'calcsize': 9956,
                                                                   'count': [1],
                                                                   'decltype': 'sys_param_sid8did0_its_config_t',
                                                                   'offset': 25408}},
                                          {'sid8did1_its_relay_config': {'calcsize': 116,
                                                                         'count': [1],
                                                                         'decltype': 'sys_param_sid8did1_its_relay_config_t',
                                                                         'offset': 35364}},
                                          {'sid8did2_its_align_config': {'calcsize': 56,
                                                                         'count': [1],
                                                                         'decltype': 'sys_param_sid8did2_its_align_config_t',
                                                                         'offset': 35480}},
                                          {'sid8did10_its_testmode_config': {'calcsize': 112,
                                                                             'count': [1],
                                                                             'decltype': 'sys_param_sid8did10_its_testmode_config_t',
                                                                             'offset': 35536}}]},
 'sys_param_version_setup_t': {'calcsize': 768,
                               'decltype': 'struct',
                               'member': [{'sys': {'calcsize': 96,
                                                   'count': [1],
                                                   'decltype': 'sys_param_version_t',
                                                   'offset': 0}},
                                          {'sw': {'calcsize': 96,
                                                  'count': [1],
                                                  'decltype': 'sys_param_version_t',
                                                  'offset': 96}},
                                          {'be': {'calcsize': 96,
                                                  'count': [1],
                                                  'decltype': 'sys_param_version_t',
                                                  'offset': 192}},
                                          {'fe': {'calcsize': 96,
                                                  'count': [1],
                                                  'decltype': 'sys_param_version_t',
                                                  'offset': 288}},
                                          {'housing': {'calcsize': 96,
                                                       'count': [1],
                                                       'decltype': 'sys_param_version_t',
                                                       'offset': 384}},
                                          {'cable': {'calcsize': 96,
                                                     'count': [1],
                                                     'decltype': 'sys_param_version_t',
                                                     'offset': 480}},
                                          {'protocol': {'calcsize': 96,
                                                        'count': [1],
                                                        'decltype': 'sys_param_version_t',
                                                        'offset': 576}},
                                          {'customer': {'calcsize': 96,
                                                        'count': [1],
                                                        'decltype': 'sys_param_version_t',
                                                        'offset': 672}}]},
 'sys_param_version_t': {'calcsize': 96,
                         'decltype': 'struct',
                         'member': [{'ver': {'calcsize': 1,
                                             'count': [32],
                                             'decltype': 'char',
                                             'offset': 0}},
                                    {'date': {'calcsize': 1,
                                              'count': [32],
                                              'decltype': 'char',
                                              'offset': 32}},
                                    {'spec': {'calcsize': 1,
                                              'count': [32],
                                              'decltype': 'char',
                                              'offset': 64}}]},
 'sys_param_vf_reflector_setup_t': {'calcsize': 40,
                                    'decltype': 'struct',
                                    'member': [{'reflector_type': {'calcsize': 1,
                                                                   'count': [32],
                                                                   'decltype': 'char',
                                                                   'offset': 0}},
                                               {'reflector_distance': {'calcsize': 4,
                                                                       'count': [1],
                                                                       'decltype': 'float',
                                                                       'offset': 32}},
                                               {'reflector_radius': {'calcsize': 4,
                                                                     'count': [1],
                                                                     'decltype': 'float',
                                                                     'offset': 36}}]},
 'sys_param_vf_relay_setup_t': {'calcsize': 84,
                                'decltype': 'struct',
                                'member': [{'relay_cnt': {'calcsize': 4,
                                                          'count': [1],
                                                          'decltype': 'int',
                                                          'offset': 0}},
                                           {'relay_enable': {'calcsize': 4,
                                                             'count': [4],
                                                             'decltype': 'int',
                                                             'offset': 4}},
                                           {'relay_type': {'calcsize': 1,
                                                           'count': [8, 4],
                                                           'decltype': 'char',
                                                           'offset': 20}},
                                           {'relay_on_time_ms': {'calcsize': 4,
                                                                 'count': [4],
                                                                 'decltype': 'int',
                                                                 'offset': 52}},
                                           {'relay_on_event_type': {'calcsize': 4,
                                                                    'count': [4],
                                                                    'decltype': 'int',
                                                                    'offset': 68}}]},
 'sys_param_vf_server_setup_t': {'calcsize': 56,
                                 'decltype': 'struct',
                                 'member': [{'server_ip': {'calcsize': 1,
                                                           'count': [32],
                                                           'decltype': 'char',
                                                           'offset': 0}},
                                            {'server_port': {'calcsize': 4,
                                                             'count': [1],
                                                             'decltype': 'int',
                                                             'offset': 32}},
                                            {'server_access_timeout': {'calcsize': 4,
                                                                       'count': [1],
                                                                       'decltype': 'int',
                                                                       'offset': 36}},
                                            {'server_access_retry_cnt': {'calcsize': 4,
                                                                         'count': [1],
                                                                         'decltype': 'int',
                                                                         'offset': 40}},
                                            {'server_sendstack_size': {'calcsize': 4,
                                                                       'count': [1],
                                                                       'decltype': 'int',
                                                                       'offset': 44}},
                                            {'rs485_access_timeout': {'calcsize': 4,
                                                                      'count': [1],
                                                                      'decltype': 'int',
                                                                      'offset': 48}},
                                            {'rs485_access_retry_cnt': {'calcsize': 4,
                                                                        'count': [1],
                                                                        'decltype': 'int',
                                                                        'offset': 52}}]},
 'sys_param_vf_ui_setup_t': {'calcsize': 16,
                             'decltype': 'struct',
                             'member': [{'th_normal': {'calcsize': 4,
                                                       'count': [1],
                                                       'decltype': 'float',
                                                       'offset': 0}},
                                        {'th_caution': {'calcsize': 4,
                                                        'count': [1],
                                                        'decltype': 'float',
                                                        'offset': 4}},
                                        {'th_warning': {'calcsize': 4,
                                                        'count': [1],
                                                        'decltype': 'float',
                                                        'offset': 8}},
                                        {'marker': {'calcsize': 4,
                                                    'count': [1],
                                                    'decltype': 'float',
                                                    'offset': 12}}]}}

ast
FileAST: 
  Typedef: sys_param_parameter_t, [], ['typedef']
    TypeDecl: sys_param_parameter_t, []
      Enum: None
        EnumeratorList: 
          Enumerator: sys_param_STRLEN_MAX
            Constant: int, 32
          Enumerator: sys_param_STRLEN_MIN
            Constant: int, 8
  Typedef: sys_param_comm_negative_response_t, [], ['typedef']
    TypeDecl: sys_param_comm_negative_response_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: error, [], [], []
          ArrayDecl: []
            TypeDecl: error, []
              IdentifierType: ['char']
            Constant: int, 256
  Typedef: sys_param_common_comm_ethernet_config_t, [], ['typedef']
    TypeDecl: sys_param_common_comm_ethernet_config_t, []
      Struct: None
        Decl: ip, [], [], []
          ArrayDecl: []
            TypeDecl: ip, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: nm, [], [], []
          ArrayDecl: []
            TypeDecl: nm, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: gw, [], [], []
          ArrayDecl: []
            TypeDecl: gw, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: mac, [], [], []
          ArrayDecl: []
            TypeDecl: mac, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: dns, [], [], []
          ArrayDecl: []
            TypeDecl: dns, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: linkspeed, [], [], []
          TypeDecl: linkspeed, []
            IdentifierType: ['int']
        Decl: dhcp_en, [], [], []
          TypeDecl: dhcp_en, []
            IdentifierType: ['unsigned', 'char']
  Typedef: sys_param_common_comm_serialcomm_config_t, [], ['typedef']
    TypeDecl: sys_param_common_comm_serialcomm_config_t, []
      Struct: None
        Decl: type, [], [], []
          ArrayDecl: []
            TypeDecl: type, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: baudrate, [], [], []
          TypeDecl: baudrate, []
            IdentifierType: ['int']
        Decl: flowcontrol, [], [], []
          ArrayDecl: []
            TypeDecl: flowcontrol, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: data, [], [], []
          TypeDecl: data, []
            IdentifierType: ['int']
        Decl: stopbit, [], [], []
          TypeDecl: stopbit, []
            IdentifierType: ['int']
  Typedef: sys_param_common_comm_tbd_config_t, [], ['typedef']
    TypeDecl: sys_param_common_comm_tbd_config_t, []
      Struct: None
        Decl: type, [], [], []
          ArrayDecl: []
            TypeDecl: type, []
              IdentifierType: ['char']
            Constant: int, 32
  Typedef: sys_param_swupdate_config_t, [], ['typedef']
    TypeDecl: sys_param_swupdate_config_t, []
      Struct: None
        Decl: swupdate_request, [], [], []
          TypeDecl: swupdate_request, []
            IdentifierType: ['int']
        Decl: swupdate_type, [], [], []
          TypeDecl: swupdate_type, []
            IdentifierType: ['int']
        Decl: swupdate_count, [], [], []
          TypeDecl: swupdate_count, []
            IdentifierType: ['int']
        Decl: swupdate_timestamp, [], [], []
          TypeDecl: swupdate_timestamp, []
            IdentifierType: ['double']
  Typedef: sys_param_consolelog_config_t, [], ['typedef']
    TypeDecl: sys_param_consolelog_config_t, []
      Struct: None
        Decl: bts_log_level, [], [], []
          TypeDecl: bts_log_level, []
            IdentifierType: ['int']
        Decl: bts_log_opt_type_en, [], [], []
          TypeDecl: bts_log_opt_type_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: bts_log_opt_time_en, [], [], []
          TypeDecl: bts_log_opt_time_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: bts_log_opt_difftime_en, [], [], []
          TypeDecl: bts_log_opt_difftime_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: bts_log_opt_file_en, [], [], []
          TypeDecl: bts_log_opt_file_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: bts_log_opt_line_en, [], [], []
          TypeDecl: bts_log_opt_line_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: bts_log_opt_function_en, [], [], []
          TypeDecl: bts_log_opt_function_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: bts_log_module_comm_packet_en, [], [], []
          TypeDecl: bts_log_module_comm_packet_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: bts_log_module_comm_appl_callback_en, [], [], []
          TypeDecl: bts_log_module_comm_appl_callback_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: bts_log_array_frontlen, [], [], []
          TypeDecl: bts_log_array_frontlen, []
            IdentifierType: ['int']
        Decl: bts_log_array_backlen, [], [], []
          TypeDecl: bts_log_array_backlen, []
            IdentifierType: ['int']
        Decl: bts_log_cpu_usage, [], [], []
          TypeDecl: bts_log_cpu_usage, []
            IdentifierType: ['unsigned', 'char']
        Decl: bts_log_opt_datetime_en, [], [], []
          TypeDecl: bts_log_opt_datetime_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: bts_log_opt_datetime_ms_en, [], [], []
          TypeDecl: bts_log_opt_datetime_ms_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: bts_log_opt_datetime_us_en, [], [], []
          TypeDecl: bts_log_opt_datetime_us_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: bts_log_opt_gps_en, [], [], []
          TypeDecl: bts_log_opt_gps_en, []
            IdentifierType: ['unsigned', 'char']
  Typedef: sys_param_consoleudp_config_t, [], ['typedef']
    TypeDecl: sys_param_consoleudp_config_t, []
      Struct: None
        Decl: en, [], [], []
          TypeDecl: en, []
            IdentifierType: ['unsigned', 'char']
        Decl: ip, [], [], []
          ArrayDecl: []
            TypeDecl: ip, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: port, [], [], []
          TypeDecl: port, []
            IdentifierType: ['int']
  Typedef: sys_param_system_sensortype_config_t, [], ['typedef']
    TypeDecl: sys_param_system_sensortype_config_t, []
      Struct: None
        Decl: type, [], [], []
          ArrayDecl: []
            TypeDecl: type, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: serialnumber, [], [], []
          ArrayDecl: []
            TypeDecl: serialnumber, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: opmode_its_en, [], [], []
          TypeDecl: opmode_its_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: opmode_vf_en, [], [], []
          TypeDecl: opmode_vf_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: opmode_fcw_en, [], [], []
          TypeDecl: opmode_fcw_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: opmode_lm_en, [], [], []
          TypeDecl: opmode_lm_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_status_en, [], [], []
          TypeDecl: pid_status_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_object_en, [], [], []
          TypeDecl: pid_object_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_track_en, [], [], []
          TypeDecl: pid_track_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_image_en, [], [], []
          TypeDecl: pid_image_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_imagsp_en, [], [], []
          TypeDecl: pid_imagsp_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_logger_en, [], [], []
          TypeDecl: pid_logger_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_canlog_en, [], [], []
          TypeDecl: pid_canlog_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_sensor_en, [], [], []
          TypeDecl: pid_sensor_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_app_its_en, [], [], []
          TypeDecl: pid_app_its_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_app_vf_en, [], [], []
          TypeDecl: pid_app_vf_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_app_fcw_en, [], [], []
          TypeDecl: pid_app_fcw_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_app_lm_en, [], [], []
          TypeDecl: pid_app_lm_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: raw_chirp_en, [], [], []
          TypeDecl: raw_chirp_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: raw_chirp0_en, [], [], []
          TypeDecl: raw_chirp0_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: raw_chirp1_en, [], [], []
          TypeDecl: raw_chirp1_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: raw_chirp2_en, [], [], []
          TypeDecl: raw_chirp2_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: raw_chirp3_en, [], [], []
          TypeDecl: raw_chirp3_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: raw_app_en, [], [], []
          TypeDecl: raw_app_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: raw_app_its_en, [], [], []
          TypeDecl: raw_app_its_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: raw_app_vf_en, [], [], []
          TypeDecl: raw_app_vf_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: raw_app_fcw_en, [], [], []
          TypeDecl: raw_app_fcw_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: raw_app_lm_en, [], [], []
          TypeDecl: raw_app_lm_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: raw_app_install_en, [], [], []
          TypeDecl: raw_app_install_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: raw_app_flog_en, [], [], []
          TypeDecl: raw_app_flog_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: raw_mon_en, [], [], []
          TypeDecl: raw_mon_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: raw_mon_power_en, [], [], []
          TypeDecl: raw_mon_power_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: raw_mon_time_en, [], [], []
          TypeDecl: raw_mon_time_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: raw_mon_task_en, [], [], []
          TypeDecl: raw_mon_task_en, []
            IdentifierType: ['unsigned', 'char']
  Typedef: sys_param_system_control_t, [], ['typedef']
    TypeDecl: sys_param_system_control_t, []
      Struct: None
        Decl: restart_en, [], [], []
          TypeDecl: restart_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: restart_timeout_s, [], [], []
          TypeDecl: restart_timeout_s, []
            IdentifierType: ['int']
  Typedef: sys_param_logic_control_config_t, [], ['typedef']
    TypeDecl: sys_param_logic_control_config_t, []
      Struct: None
        Decl: logic_start_scan_offset, [], [], []
          TypeDecl: logic_start_scan_offset, []
            IdentifierType: ['int']
  Typedef: sys_param_system_config_t, [], ['typedef']
    TypeDecl: sys_param_system_config_t, []
      Struct: None
        Decl: swupdate, [], [], []
          TypeDecl: swupdate, []
            IdentifierType: ['sys_param_swupdate_config_t']
        Decl: consolelog, [], [], []
          TypeDecl: consolelog, []
            IdentifierType: ['sys_param_consolelog_config_t']
        Decl: consoleudp, [], [], []
          TypeDecl: consoleudp, []
            IdentifierType: ['sys_param_consoleudp_config_t']
        Decl: sensortype, [], [], []
          TypeDecl: sensortype, []
            IdentifierType: ['sys_param_system_sensortype_config_t']
        Decl: eth_default, [], [], []
          TypeDecl: eth_default, []
            IdentifierType: ['sys_param_common_comm_ethernet_config_t']
        Decl: syscontrol, [], [], []
          TypeDecl: syscontrol, []
            IdentifierType: ['sys_param_system_control_t']
        Decl: logiccontrol, [], [], []
          TypeDecl: logiccontrol, []
            IdentifierType: ['sys_param_logic_control_config_t']
  Typedef: sys_param_sid0did0_systembase_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did0_systembase_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_system_config_t']
  Typedef: sys_param_datetime_setup_t, [], ['typedef']
    TypeDecl: sys_param_datetime_setup_t, []
      Struct: None
        Decl: type, [], [], []
          ArrayDecl: []
            TypeDecl: type, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: unit, [], [], []
          ArrayDecl: []
            TypeDecl: unit, []
              IdentifierType: ['char']
            Constant: int, 8
        Decl: timestamp, [], [], []
          TypeDecl: timestamp, []
            IdentifierType: ['double']
        Decl: gps_update_en, [], [], []
          TypeDecl: gps_update_en, []
            IdentifierType: ['unsigned', 'char']
  Typedef: sys_param_sid0did1_datetime_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did1_datetime_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_datetime_setup_t']
  Typedef: sys_param_security_setup_t, [], ['typedef']
    TypeDecl: sys_param_security_setup_t, []
      Struct: None
        Decl: lock_en, [], [], []
          TypeDecl: lock_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: admin_password, [], [], []
          ArrayDecl: []
            TypeDecl: admin_password, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: user_password, [], [], []
          ArrayDecl: []
            TypeDecl: user_password, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: type, [], [], []
          ArrayDecl: []
            TypeDecl: type, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: latitude, [], [], []
          ArrayDecl: []
            TypeDecl: latitude, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: longitude, [], [], []
          ArrayDecl: []
            TypeDecl: longitude, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: direction, [], [], []
          ArrayDecl: []
            TypeDecl: direction, []
              IdentifierType: ['char']
            Constant: int, 32
  Typedef: sys_param_sid0did2_security_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did2_security_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_security_setup_t']
  Typedef: sys_param_sid0did3_network_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did3_network_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_common_comm_ethernet_config_t']
  Typedef: sys_param_version_t, [], ['typedef']
    TypeDecl: sys_param_version_t, []
      Struct: None
        Decl: ver, [], [], []
          ArrayDecl: []
            TypeDecl: ver, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: date, [], [], []
          ArrayDecl: []
            TypeDecl: date, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: spec, [], [], []
          ArrayDecl: []
            TypeDecl: spec, []
              IdentifierType: ['char']
            Constant: int, 32
  Typedef: sys_param_version_setup_t, [], ['typedef']
    TypeDecl: sys_param_version_setup_t, []
      Struct: None
        Decl: sys, [], [], []
          TypeDecl: sys, []
            IdentifierType: ['sys_param_version_t']
        Decl: sw, [], [], []
          TypeDecl: sw, []
            IdentifierType: ['sys_param_version_t']
        Decl: be, [], [], []
          TypeDecl: be, []
            IdentifierType: ['sys_param_version_t']
        Decl: fe, [], [], []
          TypeDecl: fe, []
            IdentifierType: ['sys_param_version_t']
        Decl: housing, [], [], []
          TypeDecl: housing, []
            IdentifierType: ['sys_param_version_t']
        Decl: cable, [], [], []
          TypeDecl: cable, []
            IdentifierType: ['sys_param_version_t']
        Decl: protocol, [], [], []
          TypeDecl: protocol, []
            IdentifierType: ['sys_param_version_t']
        Decl: customer, [], [], []
          TypeDecl: customer, []
            IdentifierType: ['sys_param_version_t']
  Typedef: sys_param_infra_setup_t, [], ['typedef']
    TypeDecl: sys_param_infra_setup_t, []
      Struct: None
        Decl: infraid, [], [], []
          ArrayDecl: []
            TypeDecl: infraid, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: radarid, [], [], []
          ArrayDecl: []
            TypeDecl: radarid, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: locationid, [], [], []
          ArrayDecl: []
            TypeDecl: locationid, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: basestationid, [], [], []
          ArrayDecl: []
            TypeDecl: basestationid, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: switchid, [], [], []
          ArrayDecl: []
            TypeDecl: switchid, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: desc, [], [], []
          ArrayDecl: []
            TypeDecl: desc, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: desc1, [], [], []
          ArrayDecl: []
            TypeDecl: desc1, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: desc2, [], [], []
          ArrayDecl: []
            TypeDecl: desc2, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: longitude, [], [], []
          ArrayDecl: []
            TypeDecl: longitude, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: latitude, [], [], []
          ArrayDecl: []
            TypeDecl: latitude, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: direction, [], [], []
          ArrayDecl: []
            TypeDecl: direction, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: height, [], [], []
          ArrayDecl: []
            TypeDecl: height, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: roadid, [], [], []
          ArrayDecl: []
            TypeDecl: roadid, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: roadid1, [], [], []
          ArrayDecl: []
            TypeDecl: roadid1, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: roadid2, [], [], []
          ArrayDecl: []
            TypeDecl: roadid2, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: area, [], [], []
          ArrayDecl: []
            TypeDecl: area, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: area1, [], [], []
          ArrayDecl: []
            TypeDecl: area1, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: range, [], [], []
          ArrayDecl: []
            TypeDecl: range, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: range1, [], [], []
          ArrayDecl: []
            TypeDecl: range1, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: lane, [], [], []
          ArrayDecl: []
            TypeDecl: lane, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: lane1, [], [], []
          ArrayDecl: []
            TypeDecl: lane1, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: lane2, [], [], []
          ArrayDecl: []
            TypeDecl: lane2, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: lane3, [], [], []
          ArrayDecl: []
            TypeDecl: lane3, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: lane4, [], [], []
          ArrayDecl: []
            TypeDecl: lane4, []
              IdentifierType: ['char']
            Constant: int, 32
  Typedef: sys_param_sid0did4_infra_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did4_infra_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_infra_setup_t']
  Typedef: sys_param_serialnumber_setup_t, [], ['typedef']
    TypeDecl: sys_param_serialnumber_setup_t, []
      Struct: None
        Decl: sys, [], [], []
          ArrayDecl: []
            TypeDecl: sys, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: be, [], [], []
          ArrayDecl: []
            TypeDecl: be, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: fe, [], [], []
          ArrayDecl: []
            TypeDecl: fe, []
              IdentifierType: ['char']
            Constant: int, 32
  Typedef: sys_param_sid0did5_serialnumber_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did5_serialnumber_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_serialnumber_setup_t']
  Typedef: sys_param_location_t, [], ['typedef']
    TypeDecl: sys_param_location_t, []
      Struct: None
        Decl: type, [], [], []
          ArrayDecl: []
            TypeDecl: type, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: latitude, [], [], []
          TypeDecl: latitude, []
            IdentifierType: ['double']
        Decl: longitude, [], [], []
          TypeDecl: longitude, []
            IdentifierType: ['double']
        Decl: direction, [], [], []
          TypeDecl: direction, []
            IdentifierType: ['float']
        Decl: gps_update_en, [], [], []
          TypeDecl: gps_update_en, []
            IdentifierType: ['unsigned', 'char']
  Typedef: sys_param_gps_t, [], ['typedef']
    TypeDecl: sys_param_gps_t, []
      Struct: None
        Decl: en, [], [], []
          TypeDecl: en, []
            IdentifierType: ['unsigned', 'char']
        Decl: manufacture, [], [], []
          ArrayDecl: []
            TypeDecl: manufacture, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: default_baudrate, [], [], []
          TypeDecl: default_baudrate, []
            IdentifierType: ['int']
        Decl: baudrate, [], [], []
          TypeDecl: baudrate, []
            IdentifierType: ['int']
        Decl: rate, [], [], []
          TypeDecl: rate, []
            IdentifierType: ['int']
        Decl: dgps_en, [], [], []
          TypeDecl: dgps_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: swfilter_en, [], [], []
          TypeDecl: swfilter_en, []
            IdentifierType: ['unsigned', 'char']
  Typedef: sys_param_location_setup_t, [], ['typedef']
    TypeDecl: sys_param_location_setup_t, []
      Struct: None
        Decl: location, [], [], []
          TypeDecl: location, []
            IdentifierType: ['sys_param_location_t']
        Decl: gps, [], [], []
          TypeDecl: gps, []
            IdentifierType: ['sys_param_gps_t']
  Typedef: sys_param_sid0did6_location_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did6_location_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_location_setup_t']
  Typedef: sys_param_jctbox_setup_t, [], ['typedef']
    TypeDecl: sys_param_jctbox_setup_t, []
      Struct: None
        Decl: commtype, [], [], []
          TypeDecl: commtype, []
            IdentifierType: ['int']
        Decl: highspeed_en, [], [], []
          TypeDecl: highspeed_en, []
            IdentifierType: ['int']
        Decl: baudrate_default, [], [], []
          TypeDecl: baudrate_default, []
            IdentifierType: ['int']
        Decl: baudrate_high, [], [], []
          TypeDecl: baudrate_high, []
            IdentifierType: ['int']
        Decl: packettype, [], [], []
          TypeDecl: packettype, []
            IdentifierType: ['int']
        Decl: tbd0, [], [], []
          TypeDecl: tbd0, []
            IdentifierType: ['int']
        Decl: tbd1, [], [], []
          TypeDecl: tbd1, []
            IdentifierType: ['int']
        Decl: tbd2, [], [], []
          TypeDecl: tbd2, []
            IdentifierType: ['int']
        Decl: tbd3, [], [], []
          TypeDecl: tbd3, []
            IdentifierType: ['int']
  Typedef: sys_param_sid0did7_jctbox_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did7_jctbox_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_jctbox_setup_t']
  Typedef: sys_param_rs485_protocol_setup_t, [], ['typedef']
    TypeDecl: sys_param_rs485_protocol_setup_t, []
      Struct: None
        Decl: commtype, [], [], []
          TypeDecl: commtype, []
            IdentifierType: ['int']
        Decl: highspeed_en, [], [], []
          TypeDecl: highspeed_en, []
            IdentifierType: ['int']
        Decl: baudrate_default, [], [], []
          TypeDecl: baudrate_default, []
            IdentifierType: ['int']
        Decl: baudrate_high, [], [], []
          TypeDecl: baudrate_high, []
            IdentifierType: ['int']
        Decl: packettype, [], [], []
          TypeDecl: packettype, []
            IdentifierType: ['int']
        Decl: tbd0, [], [], []
          TypeDecl: tbd0, []
            IdentifierType: ['int']
        Decl: tbd1, [], [], []
          TypeDecl: tbd1, []
            IdentifierType: ['int']
        Decl: tbd2, [], [], []
          TypeDecl: tbd2, []
            IdentifierType: ['int']
        Decl: tbd3, [], [], []
          TypeDecl: tbd3, []
            IdentifierType: ['int']
  Typedef: sys_param_sid0did8_rs485_protocol_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did8_rs485_protocol_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_rs485_protocol_setup_t']
  Typedef: sys_param_cameractrl_setup_t, [], ['typedef']
    TypeDecl: sys_param_cameractrl_setup_t, []
      Struct: None
        Decl: en, [], [], []
          TypeDecl: en, []
            IdentifierType: ['int']
        Decl: framerate, [], [], []
          TypeDecl: framerate, []
            IdentifierType: ['float']
        Decl: imageresolution, [], [], []
          TypeDecl: imageresolution, []
            IdentifierType: ['int']
        Decl: imageroi, [], [], []
          TypeDecl: imageroi, []
            IdentifierType: ['int']
        Decl: format, [], [], []
          TypeDecl: format, []
            IdentifierType: ['int']
        Decl: brightness, [], [], []
          TypeDecl: brightness, []
            IdentifierType: ['int']
        Decl: contrast, [], [], []
          TypeDecl: contrast, []
            IdentifierType: ['int']
        Decl: gain, [], [], []
          TypeDecl: gain, []
            IdentifierType: ['int']
        Decl: exposure_limit, [], [], []
          TypeDecl: exposure_limit, []
            IdentifierType: ['int']
        Decl: tbd1, [], [], []
          TypeDecl: tbd1, []
            IdentifierType: ['int']
        Decl: tbd2, [], [], []
          TypeDecl: tbd2, []
            IdentifierType: ['int']
        Decl: tbd3, [], [], []
          TypeDecl: tbd3, []
            IdentifierType: ['int']
        Decl: tbd4, [], [], []
          TypeDecl: tbd4, []
            IdentifierType: ['int']
        Decl: tbd5, [], [], []
          TypeDecl: tbd5, []
            IdentifierType: ['int']
        Decl: tbd6, [], [], []
          TypeDecl: tbd6, []
            IdentifierType: ['int']
        Decl: tbd7, [], [], []
          TypeDecl: tbd7, []
            IdentifierType: ['int']
        Decl: tbd8, [], [], []
          TypeDecl: tbd8, []
            IdentifierType: ['int']
  Typedef: sys_param_camera_setup_t, [], ['typedef']
    TypeDecl: sys_param_camera_setup_t, []
      Struct: None
        Decl: count, [], [], []
          TypeDecl: count, []
            IdentifierType: ['int']
        Decl: cam, [], [], []
          ArrayDecl: []
            TypeDecl: cam, []
              IdentifierType: ['sys_param_cameractrl_setup_t']
            Constant: int, 2
  Typedef: sys_param_sid0did9_camera_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did9_camera_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_camera_setup_t']
  Typedef: sys_param_rsp_eol_phasecal_t, [], ['typedef']
    TypeDecl: sys_param_rsp_eol_phasecal_t, []
      Struct: None
        Decl: real, [], [], []
          TypeDecl: real, []
            IdentifierType: ['float']
        Decl: imag, [], [], []
          TypeDecl: imag, []
            IdentifierType: ['float']
  Typedef: sys_param_rsp_eol_setup_t, [], ['typedef']
    TypeDecl: sys_param_rsp_eol_setup_t, []
      Struct: None
        Decl: en, [], [], []
          TypeDecl: en, []
            IdentifierType: ['unsigned', 'char']
        Decl: phasecal, [], [], []
          ArrayDecl: []
            TypeDecl: phasecal, []
              IdentifierType: ['sys_param_rsp_eol_phasecal_t']
            Constant: int, 4
        Decl: noise_level_up, [], [], []
          ArrayDecl: []
            TypeDecl: noise_level_up, []
              IdentifierType: ['float']
            Constant: int, 4
        Decl: noise_level_dn, [], [], []
          ArrayDecl: []
            TypeDecl: noise_level_dn, []
              IdentifierType: ['float']
            Constant: int, 4
        Decl: aziangstep, [], [], []
          TypeDecl: aziangstep, []
            IdentifierType: ['float']
        Decl: aziangmin, [], [], []
          TypeDecl: aziangmin, []
            IdentifierType: ['float']
        Decl: aziangmax, [], [], []
          TypeDecl: aziangmax, []
            IdentifierType: ['float']
        Decl: azibeampattern_up, [], [], []
          ArrayDecl: []
            ArrayDecl: []
              TypeDecl: azibeampattern_up, []
                IdentifierType: ['float']
              Constant: int, 4
            Constant: int, 361
        Decl: azibeamphase_up, [], [], []
          ArrayDecl: []
            ArrayDecl: []
              TypeDecl: azibeamphase_up, []
                IdentifierType: ['float']
              Constant: int, 4
            Constant: int, 361
        Decl: azibeampattern_dn, [], [], []
          ArrayDecl: []
            ArrayDecl: []
              TypeDecl: azibeampattern_dn, []
                IdentifierType: ['float']
              Constant: int, 4
            Constant: int, 361
        Decl: azibeamphase_dn, [], [], []
          ArrayDecl: []
            ArrayDecl: []
              TypeDecl: azibeamphase_dn, []
                IdentifierType: ['float']
              Constant: int, 4
            Constant: int, 361
  Typedef: sys_param_sid0did10_rsp_eol_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did10_rsp_eol_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_rsp_eol_setup_t']
  Typedef: sys_param_rsp_install_setup_t, [], ['typedef']
    TypeDecl: sys_param_rsp_install_setup_t, []
      Struct: None
        Decl: height, [], [], []
          TypeDecl: height, []
            IdentifierType: ['float']
        Decl: ele_angle, [], [], []
          TypeDecl: ele_angle, []
            IdentifierType: ['float']
        Decl: azi_angle, [], [], []
          TypeDecl: azi_angle, []
            IdentifierType: ['float']
        Decl: offset_x, [], [], []
          TypeDecl: offset_x, []
            IdentifierType: ['float']
        Decl: offset_y, [], [], []
          TypeDecl: offset_y, []
            IdentifierType: ['float']
  Typedef: sys_param_sid0did11_rsp_install_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did11_rsp_install_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_rsp_install_setup_t']
  Typedef: sys_param_rsm_setup_t, [], ['typedef']
    TypeDecl: sys_param_rsm_setup_t, []
      Struct: None
        Decl: mode, [], [], []
          TypeDecl: mode, []
            IdentifierType: ['int']
        Decl: userfreq, [], [], []
          TypeDecl: userfreq, []
            IdentifierType: ['float']
        Decl: scanrate, [], [], []
          TypeDecl: scanrate, []
            IdentifierType: ['int']
        Decl: daq_sampledelay, [], [], []
          TypeDecl: daq_sampledelay, []
            IdentifierType: ['int']
  Typedef: sys_param_sid0did12_rsm_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did12_rsm_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_rsm_setup_t']
  Typedef: sys_param_rsptrk_posttune_t, [], ['typedef']
    TypeDecl: sys_param_rsptrk_posttune_t, []
      Struct: None
        Decl: LongGate1, [], [], []
          TypeDecl: LongGate1, []
            IdentifierType: ['float']
        Decl: LongGate2, [], [], []
          TypeDecl: LongGate2, []
            IdentifierType: ['float']
        Decl: LongGate3, [], [], []
          TypeDecl: LongGate3, []
            IdentifierType: ['float']
        Decl: LongGateByVel_Gain, [], [], []
          TypeDecl: LongGateByVel_Gain, []
            IdentifierType: ['float']
        Decl: MotorCycle_PowTh, [], [], []
          TypeDecl: MotorCycle_PowTh, []
            IdentifierType: ['float']
        Decl: MotorCycle_PowTh2, [], [], []
          TypeDecl: MotorCycle_PowTh2, []
            IdentifierType: ['float']
        Decl: MotorCycleByRange_Gain, [], [], []
          TypeDecl: MotorCycleByRange_Gain, []
            IdentifierType: ['float']
        Decl: TrackOutFilter, [], [], []
          TypeDecl: TrackOutFilter, []
            IdentifierType: ['int']
        Decl: tbd8, [], [], []
          TypeDecl: tbd8, []
            IdentifierType: ['float']
        Decl: tbd9, [], [], []
          TypeDecl: tbd9, []
            IdentifierType: ['float']
        Decl: tbd10, [], [], []
          TypeDecl: tbd10, []
            IdentifierType: ['float']
        Decl: tbd11, [], [], []
          TypeDecl: tbd11, []
            IdentifierType: ['float']
        Decl: tbd12, [], [], []
          TypeDecl: tbd12, []
            IdentifierType: ['float']
        Decl: tbd13, [], [], []
          TypeDecl: tbd13, []
            IdentifierType: ['float']
        Decl: tbd14, [], [], []
          TypeDecl: tbd14, []
            IdentifierType: ['float']
        Decl: tbd15, [], [], []
          TypeDecl: tbd15, []
            IdentifierType: ['float']
  Typedef: sys_param_rsptrk_trktune_t, [], ['typedef']
    TypeDecl: sys_param_rsptrk_trktune_t, []
      Struct: None
        Decl: s16Pt_New2Vrf, [], [], []
          TypeDecl: s16Pt_New2Vrf, []
            IdentifierType: ['int']
        Decl: s16Pt_Max, [], [], []
          TypeDecl: s16Pt_Max, []
            IdentifierType: ['int']
        Decl: s16Pt_New_Upd, [], [], []
          TypeDecl: s16Pt_New_Upd, []
            IdentifierType: ['int']
        Decl: s16Pt_New_Coast, [], [], []
          TypeDecl: s16Pt_New_Coast, []
            IdentifierType: ['int']
        Decl: s16Pt_Vrf_Upd, [], [], []
          TypeDecl: s16Pt_Vrf_Upd, []
            IdentifierType: ['int']
        Decl: s16Pt_Vrf_Coast, [], [], []
          TypeDecl: s16Pt_Vrf_Coast, []
            IdentifierType: ['int']
        Decl: f32Pt_NearRange, [], [], []
          TypeDecl: f32Pt_NearRange, []
            IdentifierType: ['float']
        Decl: s16Pt_Vrf_Upd_Near, [], [], []
          TypeDecl: s16Pt_Vrf_Upd_Near, []
            IdentifierType: ['int']
        Decl: s16Pt_Vrf_Coast_Near, [], [], []
          TypeDecl: s16Pt_Vrf_Coast_Near, []
            IdentifierType: ['int']
        Decl: f32R_GateByEle_W, [], [], []
          TypeDecl: f32R_GateByEle_W, []
            IdentifierType: ['float']
        Decl: f32V_GateByEle_W, [], [], []
          TypeDecl: f32V_GateByEle_W, []
            IdentifierType: ['float']
  Typedef: sys_param_rsptrk_setup_t, [], ['typedef']
    TypeDecl: sys_param_rsptrk_setup_t, []
      Struct: None
        Decl: posttune, [], [], []
          TypeDecl: posttune, []
            IdentifierType: ['sys_param_rsptrk_posttune_t']
        Decl: trktune, [], [], []
          TypeDecl: trktune, []
            IdentifierType: ['sys_param_rsptrk_trktune_t']
  Typedef: sys_param_sid0did13_rsptrk_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did13_rsptrk_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_rsptrk_setup_t']
  Typedef: sys_param_rfictx_select_t, [], ['typedef']
    TypeDecl: sys_param_rfictx_select_t, []
      Struct: None
        Decl: rfictx_sel, [], [], []
          TypeDecl: rfictx_sel, []
            IdentifierType: ['int']
  Typedef: sys_param_sid0did30_rfictx_select_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did30_rfictx_select_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_rfictx_select_t']
  Typedef: sys_param_rfictx_bgt24at2_setup_t, [], ['typedef']
    TypeDecl: sys_param_rfictx_bgt24at2_setup_t, []
      Struct: None
        Decl: TX1_A, [], [], []
          TypeDecl: TX1_A, []
            IdentifierType: ['int']
        Decl: TX1_SPI_ON, [], [], []
          TypeDecl: TX1_SPI_ON, []
            IdentifierType: ['unsigned', 'char']
        Decl: TX1_EN_DAC, [], [], []
          TypeDecl: TX1_EN_DAC, []
            IdentifierType: ['unsigned', 'char']
        Decl: TX1_SEL1, [], [], []
          TypeDecl: TX1_SEL1, []
            IdentifierType: ['unsigned', 'char']
        Decl: PH1_SPI_ON, [], [], []
          TypeDecl: PH1_SPI_ON, []
            IdentifierType: ['unsigned', 'char']
        Decl: TX2_A, [], [], []
          TypeDecl: TX2_A, []
            IdentifierType: ['int']
        Decl: TX2_SPI_ON, [], [], []
          TypeDecl: TX2_SPI_ON, []
            IdentifierType: ['unsigned', 'char']
        Decl: TX2_SEL1, [], [], []
          TypeDecl: TX2_SEL1, []
            IdentifierType: ['unsigned', 'char']
        Decl: TX2_EN_DAC, [], [], []
          TypeDecl: TX2_EN_DAC, []
            IdentifierType: ['unsigned', 'char']
        Decl: PH2_SPI_ON, [], [], []
          TypeDecl: PH2_SPI_ON, []
            IdentifierType: ['unsigned', 'char']
        Decl: LO_A, [], [], []
          TypeDecl: LO_A, []
            IdentifierType: ['int']
        Decl: LO_SPI_ON, [], [], []
          TypeDecl: LO_SPI_ON, []
            IdentifierType: ['unsigned', 'char']
        Decl: LO_EN_DAC, [], [], []
          TypeDecl: LO_EN_DAC, []
            IdentifierType: ['unsigned', 'char']
        Decl: LO_SEL1, [], [], []
          TypeDecl: LO_SEL1, []
            IdentifierType: ['unsigned', 'char']
        Decl: LO_SEL0, [], [], []
          TypeDecl: LO_SEL0, []
            IdentifierType: ['unsigned', 'char']
        Decl: PHLO_SPI_ON, [], [], []
          TypeDecl: PHLO_SPI_ON, []
            IdentifierType: ['unsigned', 'char']
        Decl: VCO_A, [], [], []
          TypeDecl: VCO_A, []
            IdentifierType: ['int']
        Decl: EN_DAC_VCO, [], [], []
          TypeDecl: EN_DAC_VCO, []
            IdentifierType: ['unsigned', 'char']
        Decl: EN_VCO, [], [], []
          TypeDecl: EN_VCO, []
            IdentifierType: ['unsigned', 'char']
        Decl: EN_BUF2, [], [], []
          TypeDecl: EN_BUF2, []
            IdentifierType: ['unsigned', 'char']
        Decl: EN_BUF1, [], [], []
          TypeDecl: EN_BUF1, []
            IdentifierType: ['unsigned', 'char']
        Decl: PH_SEL1, [], [], []
          TypeDecl: PH_SEL1, []
            IdentifierType: ['unsigned', 'char']
        Decl: AMUX1_SEL1, [], [], []
          TypeDecl: AMUX1_SEL1, []
            IdentifierType: ['unsigned', 'char']
        Decl: AMUX1_SEL0, [], [], []
          TypeDecl: AMUX1_SEL0, []
            IdentifierType: ['unsigned', 'char']
        Decl: AMUX2_SEL2, [], [], []
          TypeDecl: AMUX2_SEL2, []
            IdentifierType: ['unsigned', 'char']
        Decl: AMUX2_SEL1, [], [], []
          TypeDecl: AMUX2_SEL1, []
            IdentifierType: ['unsigned', 'char']
        Decl: AMUX2_SEL0, [], [], []
          TypeDecl: AMUX2_SEL0, []
            IdentifierType: ['unsigned', 'char']
        Decl: AMUX3_SEL1, [], [], []
          TypeDecl: AMUX3_SEL1, []
            IdentifierType: ['unsigned', 'char']
        Decl: AMUX3_SEL0, [], [], []
          TypeDecl: AMUX3_SEL0, []
            IdentifierType: ['unsigned', 'char']
        Decl: EN_DIV, [], [], []
          TypeDecl: EN_DIV, []
            IdentifierType: ['unsigned', 'char']
        Decl: SEL_DIVBUF, [], [], []
          TypeDecl: SEL_DIVBUF, []
            IdentifierType: ['unsigned', 'char']
        Decl: SEL_DIV, [], [], []
          TypeDecl: SEL_DIV, []
            IdentifierType: ['unsigned', 'char']
        Decl: DIS_DIVOUT, [], [], []
          TypeDecl: DIS_DIVOUT, []
            IdentifierType: ['unsigned', 'char']
  Typedef: sys_param_sid0did31_rfictx_bgt24at2_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did31_rfictx_bgt24at2_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_rfictx_bgt24at2_setup_t']
  Typedef: sys_param_rficrx_select_t, [], ['typedef']
    TypeDecl: sys_param_rficrx_select_t, []
      Struct: None
        Decl: rficrx_sel, [], [], []
          TypeDecl: rficrx_sel, []
            IdentifierType: ['int']
  Typedef: sys_param_sid0did40_rficrx_select_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did40_rficrx_select_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_rficrx_select_t']
  Typedef: sys_param_rficrx_bgt24ar4_setup_t, [], ['typedef']
    TypeDecl: sys_param_rficrx_bgt24ar4_setup_t, []
      Struct: None
        Decl: EN_12, [], [], []
          TypeDecl: EN_12, []
            IdentifierType: ['unsigned', 'char']
        Decl: LG1_12_6db, [], [], []
          TypeDecl: LG1_12_6db, []
            IdentifierType: ['unsigned', 'char']
        Decl: HG1_12_12db, [], [], []
          TypeDecl: HG1_12_12db, []
            IdentifierType: ['unsigned', 'char']
        Decl: LG2_12_6db, [], [], []
          TypeDecl: LG2_12_6db, []
            IdentifierType: ['unsigned', 'char']
        Decl: MG2_12_12db, [], [], []
          TypeDecl: MG2_12_12db, []
            IdentifierType: ['unsigned', 'char']
        Decl: HG2_12_18db, [], [], []
          TypeDecl: HG2_12_18db, []
            IdentifierType: ['unsigned', 'char']
        Decl: EN_34, [], [], []
          TypeDecl: EN_34, []
            IdentifierType: ['unsigned', 'char']
        Decl: LG1_34_6db, [], [], []
          TypeDecl: LG1_34_6db, []
            IdentifierType: ['unsigned', 'char']
        Decl: HG1_34_12db, [], [], []
          TypeDecl: HG1_34_12db, []
            IdentifierType: ['unsigned', 'char']
        Decl: LG2_34_6db, [], [], []
          TypeDecl: LG2_34_6db, []
            IdentifierType: ['unsigned', 'char']
        Decl: MG2_34_12db, [], [], []
          TypeDecl: MG2_34_12db, []
            IdentifierType: ['unsigned', 'char']
        Decl: HG2_34_18db, [], [], []
          TypeDecl: HG2_34_18db, []
            IdentifierType: ['unsigned', 'char']
        Decl: IFTEST4, [], [], []
          TypeDecl: IFTEST4, []
            IdentifierType: ['unsigned', 'char']
        Decl: IFTEST3, [], [], []
          TypeDecl: IFTEST3, []
            IdentifierType: ['unsigned', 'char']
        Decl: IFTEST2, [], [], []
          TypeDecl: IFTEST2, []
            IdentifierType: ['unsigned', 'char']
        Decl: IFTEST1, [], [], []
          TypeDecl: IFTEST1, []
            IdentifierType: ['unsigned', 'char']
        Decl: PC1, [], [], []
          TypeDecl: PC1, []
            IdentifierType: ['unsigned', 'char']
        Decl: PC2, [], [], []
          TypeDecl: PC2, []
            IdentifierType: ['unsigned', 'char']
        Decl: EN_RF14, [], [], []
          TypeDecl: EN_RF14, []
            IdentifierType: ['unsigned', 'char']
        Decl: EN_RF23, [], [], []
          TypeDecl: EN_RF23, []
            IdentifierType: ['unsigned', 'char']
        Decl: DIS_DIV, [], [], []
          TypeDecl: DIS_DIV, []
            IdentifierType: ['unsigned', 'char']
        Decl: DIS_LO, [], [], []
          TypeDecl: DIS_LO, []
            IdentifierType: ['unsigned', 'char']
        Decl: AMUX_SEL0, [], [], []
          TypeDecl: AMUX_SEL0, []
            IdentifierType: ['unsigned', 'char']
        Decl: AMUX_SEL1, [], [], []
          TypeDecl: AMUX_SEL1, []
            IdentifierType: ['unsigned', 'char']
        Decl: AMUX_SEL2, [], [], []
          TypeDecl: AMUX_SEL2, []
            IdentifierType: ['unsigned', 'char']
        Decl: SAT_FLAG_HIZ, [], [], []
          TypeDecl: SAT_FLAG_HIZ, []
            IdentifierType: ['unsigned', 'char']
        Decl: SENSOR_SEL0, [], [], []
          TypeDecl: SENSOR_SEL0, []
            IdentifierType: ['unsigned', 'char']
        Decl: SENSOR_SEL1, [], [], []
          TypeDecl: SENSOR_SEL1, []
            IdentifierType: ['unsigned', 'char']
        Decl: DCO_0, [], [], []
          TypeDecl: DCO_0, []
            IdentifierType: ['unsigned', 'char']
        Decl: DCO_1, [], [], []
          TypeDecl: DCO_1, []
            IdentifierType: ['unsigned', 'char']
        Decl: DCO_2, [], [], []
          TypeDecl: DCO_2, []
            IdentifierType: ['unsigned', 'char']
        Decl: DCO_3, [], [], []
          TypeDecl: DCO_3, []
            IdentifierType: ['unsigned', 'char']
  Typedef: sys_param_sid0did41_rficrx_bgt24ar4_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did41_rficrx_bgt24ar4_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_rficrx_bgt24ar4_setup_t']
  Typedef: sys_param_pll_select_t, [], ['typedef']
    TypeDecl: sys_param_pll_select_t, []
      Struct: None
        Decl: pll_sel, [], [], []
          TypeDecl: pll_sel, []
            IdentifierType: ['int']
  Typedef: sys_param_sid0did50_pll_select_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did50_pll_select_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_pll_select_t']
  Typedef: sys_param_pll_lmx2491_setup_t, [], ['typedef']
    TypeDecl: sys_param_pll_lmx2491_setup_t, []
      Struct: None
        Decl: regset, [], [], []
          TypeDecl: regset, []
            IdentifierType: ['int']
        Decl: cp, [], [], []
          TypeDecl: cp, []
            IdentifierType: ['int']
  Typedef: sys_param_sid0did51_pll_lmx2491_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did51_pll_lmx2491_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_pll_lmx2491_setup_t']
  Typedef: sys_param_adc_select_t, [], ['typedef']
    TypeDecl: sys_param_adc_select_t, []
      Struct: None
        Decl: adc_sel, [], [], []
          TypeDecl: adc_sel, []
            IdentifierType: ['int']
  Typedef: sys_param_sid0did60_adc_select_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did60_adc_select_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_adc_select_t']
  Typedef: sys_param_adc_adar7251_setup_t, [], ['typedef']
    TypeDecl: sys_param_adc_adar7251_setup_t, []
      Struct: None
        Decl: ROUTING, [], [], []
          ArrayDecl: []
            TypeDecl: ROUTING, []
              IdentifierType: ['int']
            Constant: int, 4
        Decl: LNA_GAIN, [], [], []
          ArrayDecl: []
            TypeDecl: LNA_GAIN, []
              IdentifierType: ['int']
            Constant: int, 4
        Decl: PGA_GAIN, [], [], []
          ArrayDecl: []
            TypeDecl: PGA_GAIN, []
              IdentifierType: ['int']
            Constant: int, 4
        Decl: EQ_CAP, [], [], []
          TypeDecl: EQ_CAP, []
            IdentifierType: ['int']
  Typedef: sys_param_sid0did61_adc_adar7251_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did61_adc_adar7251_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_adc_adar7251_setup_t']
  Typedef: sys_param_adc_max11043_setup_t, [], ['typedef']
    TypeDecl: sys_param_adc_max11043_setup_t, []
      Struct: None
        Decl: analog_filtermode, [], [], []
          ArrayDecl: []
            TypeDecl: analog_filtermode, []
              IdentifierType: ['int']
            Constant: int, 4
        Decl: gain, [], [], []
          ArrayDecl: []
            TypeDecl: gain, []
              IdentifierType: ['int']
            Constant: int, 4
        Decl: digtal_filtermode, [], [], []
          ArrayDecl: []
            TypeDecl: digtal_filtermode, []
              IdentifierType: ['int']
            Constant: int, 4
        Decl: fine_gain, [], [], []
          ArrayDecl: []
            TypeDecl: fine_gain, []
              IdentifierType: ['float']
            Constant: int, 4
        Decl: inputbias, [], [], []
          ArrayDecl: []
            TypeDecl: inputbias, []
              IdentifierType: ['int']
            Constant: int, 4
  Typedef: sys_param_sid0did62_adc_max11043_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did62_adc_max11043_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_adc_max11043_setup_t']
  Typedef: sys_param_app_packet_t, [], ['typedef']
    TypeDecl: sys_param_app_packet_t, []
      Struct: None
        Decl: server_ip, [], [], []
          ArrayDecl: []
            TypeDecl: server_ip, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: port_num, [], [], []
          TypeDecl: port_num, []
            IdentifierType: ['int']
        Decl: port_en, [], [], []
          TypeDecl: port_en, []
            IdentifierType: ['int']
        Decl: client_mode_en, [], [], []
          TypeDecl: client_mode_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_simple_en, [], [], []
          TypeDecl: pid_simple_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_compress_en, [], [], []
          TypeDecl: pid_compress_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_status_en, [], [], []
          TypeDecl: pid_status_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_object_en, [], [], []
          TypeDecl: pid_object_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_track_en, [], [], []
          TypeDecl: pid_track_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_image_en, [], [], []
          TypeDecl: pid_image_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_imagsp_en, [], [], []
          TypeDecl: pid_imagsp_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_logger_en, [], [], []
          TypeDecl: pid_logger_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_canlog_en, [], [], []
          TypeDecl: pid_canlog_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_sensor_en, [], [], []
          TypeDecl: pid_sensor_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_app_its_en, [], [], []
          TypeDecl: pid_app_its_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_app_vf_en, [], [], []
          TypeDecl: pid_app_vf_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_app_fcw_en, [], [], []
          TypeDecl: pid_app_fcw_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: pid_app_lm_en, [], [], []
          TypeDecl: pid_app_lm_en, []
            IdentifierType: ['unsigned', 'char']
  Typedef: sys_param_app_packet_setup_t, [], ['typedef']
    TypeDecl: sys_param_app_packet_setup_t, []
      Struct: None
        Decl: count, [], [], []
          TypeDecl: count, []
            IdentifierType: ['int']
        Decl: ports, [], [], []
          ArrayDecl: []
            TypeDecl: ports, []
              IdentifierType: ['sys_param_app_packet_t']
            Constant: int, 4
  Typedef: sys_param_sid0did200_app_packet_config_t, [], ['typedef']
    TypeDecl: sys_param_sid0did200_app_packet_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_app_packet_setup_t']
  Typedef: sys_param_candrv_channel_setup_t, [], ['typedef']
    TypeDecl: sys_param_candrv_channel_setup_t, []
      Struct: None
        Decl: cantype, [], [], []
          TypeDecl: cantype, []
            IdentifierType: ['int']
        Decl: baudrate, [], [], []
          TypeDecl: baudrate, []
            IdentifierType: ['int']
        Decl: baudratefd, [], [], []
          TypeDecl: baudratefd, []
            IdentifierType: ['int']
        Decl: samplepoint, [], [], []
          TypeDecl: samplepoint, []
            IdentifierType: ['int']
        Decl: listenonlymode_en, [], [], []
          TypeDecl: listenonlymode_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: acceptfilter_en, [], [], []
          ArrayDecl: []
            TypeDecl: acceptfilter_en, []
              IdentifierType: ['unsigned', 'char']
            Constant: int, 4
        Decl: acceptfilter_id, [], [], []
          ArrayDecl: []
            TypeDecl: acceptfilter_id, []
              IdentifierType: ['int']
            Constant: int, 4
        Decl: acceptfilter_mask, [], [], []
          ArrayDecl: []
            TypeDecl: acceptfilter_mask, []
              IdentifierType: ['int']
            Constant: int, 4
  Typedef: sys_param_candrv_setup_t, [], ['typedef']
    TypeDecl: sys_param_candrv_setup_t, []
      Struct: None
        Decl: channel_count, [], [], []
          TypeDecl: channel_count, []
            IdentifierType: ['int']
        Decl: channel, [], [], []
          ArrayDecl: []
            TypeDecl: channel, []
              IdentifierType: ['sys_param_candrv_channel_setup_t']
            Constant: int, 2
  Typedef: sys_param_sid6did0_candrv_config_t, [], ['typedef']
    TypeDecl: sys_param_sid6did0_candrv_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_candrv_setup_t']
  Typedef: sys_param_cansignal_t, [], ['typedef']
    TypeDecl: sys_param_cansignal_t, []
      Struct: None
        Decl: en, [], [], []
          TypeDecl: en, []
            IdentifierType: ['unsigned', 'char']
        Decl: sigid, [], [], []
          TypeDecl: sigid, []
            IdentifierType: ['int']
        Decl: msgid, [], [], []
          TypeDecl: msgid, []
            IdentifierType: ['int']
        Decl: name, [], [], []
          ArrayDecl: []
            TypeDecl: name, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: type, [], [], []
          TypeDecl: type, []
            IdentifierType: ['signed', 'char']
        Decl: byteorder, [], [], []
          TypeDecl: byteorder, []
            IdentifierType: ['signed', 'char']
        Decl: bitpos, [], [], []
          TypeDecl: bitpos, []
            IdentifierType: ['int']
        Decl: length, [], [], []
          TypeDecl: length, []
            IdentifierType: ['int']
        Decl: factor, [], [], []
          TypeDecl: factor, []
            IdentifierType: ['float']
        Decl: offset, [], [], []
          TypeDecl: offset, []
            IdentifierType: ['float']
        Decl: min, [], [], []
          TypeDecl: min, []
            IdentifierType: ['float']
        Decl: max, [], [], []
          TypeDecl: max, []
            IdentifierType: ['float']
        Decl: unit, [], [], []
          ArrayDecl: []
            TypeDecl: unit, []
              IdentifierType: ['char']
            Constant: int, 8
  Typedef: sys_param_cansignal_setup_t, [], ['typedef']
    TypeDecl: sys_param_cansignal_setup_t, []
      Struct: None
        Decl: signal, [], [], []
          ArrayDecl: []
            TypeDecl: signal, []
              IdentifierType: ['sys_param_cansignal_t']
            Constant: int, 16
  Typedef: sys_param_sid6did1_cansignal_config_t, [], ['typedef']
    TypeDecl: sys_param_sid6did1_cansignal_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_cansignal_setup_t']
  Typedef: sys_param_can_txmsg_t, [], ['typedef']
    TypeDecl: sys_param_can_txmsg_t, []
      Struct: None
        Decl: en, [], [], []
          TypeDecl: en, []
            IdentifierType: ['unsigned', 'char']
        Decl: start_id, [], [], []
          TypeDecl: start_id, []
            IdentifierType: ['int']
        Decl: count, [], [], []
          TypeDecl: count, []
            IdentifierType: ['int']
  Typedef: sys_param_cantxmsg_setup_t, [], ['typedef']
    TypeDecl: sys_param_cantxmsg_setup_t, []
      Struct: None
        Decl: status, [], [], []
          TypeDecl: status, []
            IdentifierType: ['sys_param_can_txmsg_t']
        Decl: object, [], [], []
          TypeDecl: object, []
            IdentifierType: ['sys_param_can_txmsg_t']
        Decl: track, [], [], []
          TypeDecl: track, []
            IdentifierType: ['sys_param_can_txmsg_t']
        Decl: extioctrl, [], [], []
          TypeDecl: extioctrl, []
            IdentifierType: ['sys_param_can_txmsg_t']
  Typedef: sys_param_sid6did2_cantxmsg_config_t, [], ['typedef']
    TypeDecl: sys_param_sid6did2_cantxmsg_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_cantxmsg_setup_t']
  Typedef: sys_param_filesystem_setup_t, [], ['typedef']
    TypeDecl: sys_param_filesystem_setup_t, []
      Struct: None
        Decl: isformatted, [], [], []
          TypeDecl: isformatted, []
            IdentifierType: ['unsigned', 'char']
        Decl: lastfilenumber, [], [], []
          TypeDecl: lastfilenumber, []
            IdentifierType: ['int']
        Decl: mmc_write_enable, [], [], []
          TypeDecl: mmc_write_enable, []
            IdentifierType: ['unsigned', 'char']
  Typedef: sys_param_sid7did0_filesystem_config_t, [], ['typedef']
    TypeDecl: sys_param_sid7did0_filesystem_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_filesystem_setup_t']
  Typedef: sys_param_status_timestamp_t, [], ['typedef']
    TypeDecl: sys_param_status_timestamp_t, []
      Struct: None
        Decl: timestamp_s, [], [], []
          TypeDecl: timestamp_s, []
            IdentifierType: ['double']
        Decl: rsp_timestamp_us, [], [], []
          TypeDecl: rsp_timestamp_us, []
            IdentifierType: ['long', 'long']
        Decl: net_timestamp_us, [], [], []
          TypeDecl: net_timestamp_us, []
            IdentifierType: ['long', 'long']
        Decl: rsp_cycletime, [], [], []
          TypeDecl: rsp_cycletime, []
            IdentifierType: ['float']
  Typedef: sys_param_status_data_position_t, [], ['typedef']
    TypeDecl: sys_param_status_data_position_t, []
      Struct: None
        Decl: yaw, [], [], []
          TypeDecl: yaw, []
            IdentifierType: ['float']
        Decl: roll, [], [], []
          TypeDecl: roll, []
            IdentifierType: ['float']
        Decl: pitch, [], [], []
          TypeDecl: pitch, []
            IdentifierType: ['float']
        Decl: altitude, [], [], []
          TypeDecl: altitude, []
            IdentifierType: ['float']
  Typedef: sys_param_status_data_ecuinfo_t, [], ['typedef']
    TypeDecl: sys_param_status_data_ecuinfo_t, []
      Struct: None
        Decl: temp_core, [], [], []
          TypeDecl: temp_core, []
            IdentifierType: ['float']
        Decl: temp_rfm, [], [], []
          TypeDecl: temp_rfm, []
            IdentifierType: ['float']
        Decl: vin, [], [], []
          TypeDecl: vin, []
            IdentifierType: ['float']
        Decl: v5, [], [], []
          TypeDecl: v5, []
            IdentifierType: ['float']
        Decl: v1_5, [], [], []
          TypeDecl: v1_5, []
            IdentifierType: ['float']
        Decl: v1_0, [], [], []
          TypeDecl: v1_0, []
            IdentifierType: ['float']
  Typedef: sys_param_status_data_gps_t, [], ['typedef']
    TypeDecl: sys_param_status_data_gps_t, []
      Struct: None
        Decl: status, [], [], []
          TypeDecl: status, []
            IdentifierType: ['unsigned', 'char']
        Decl: data, [], [], []
          ArrayDecl: []
            TypeDecl: data, []
              IdentifierType: ['char']
            Constant: int, 1024
  Typedef: sys_param_pid0_status_data_t, [], ['typedef']
    TypeDecl: sys_param_pid0_status_data_t, []
      Struct: None
        Decl: scanindex, [], [], []
          TypeDecl: scanindex, []
            IdentifierType: ['int']
        Decl: timestamp, [], [], []
          TypeDecl: timestamp, []
            IdentifierType: ['sys_param_status_timestamp_t']
        Decl: position, [], [], []
          TypeDecl: position, []
            IdentifierType: ['sys_param_status_data_position_t']
        Decl: ecuinfo, [], [], []
          TypeDecl: ecuinfo, []
            IdentifierType: ['sys_param_status_data_ecuinfo_t']
        Decl: gps, [], [], []
          TypeDecl: gps, []
            IdentifierType: ['sys_param_status_data_gps_t']
  Typedef: sys_param_its_setup_timeschedule_t, [], ['typedef']
    TypeDecl: sys_param_its_setup_timeschedule_t, []
      Struct: None
        Decl: timeunit, [], [], []
          ArrayDecl: []
            TypeDecl: timeunit, []
              IdentifierType: ['char']
            Constant: int, 8
        Decl: updatetime, [], [], []
          TypeDecl: updatetime, []
            IdentifierType: ['int']
  Typedef: sys_param_its_setup_laneinfo_lane_t, [], ['typedef']
    TypeDecl: sys_param_its_setup_laneinfo_lane_t, []
      Struct: None
        Decl: x, [], [], []
          ArrayDecl: []
            TypeDecl: x, []
              IdentifierType: ['float']
            Constant: int, 50
        Decl: y, [], [], []
          ArrayDecl: []
            TypeDecl: y, []
              IdentifierType: ['float']
            Constant: int, 50
  Typedef: sys_param_its_setup_zone_t, [], ['typedef']
    TypeDecl: sys_param_its_setup_zone_t, []
      Struct: None
        Decl: x, [], [], []
          ArrayDecl: []
            TypeDecl: x, []
              IdentifierType: ['float']
            Constant: int, 100
        Decl: y, [], [], []
          ArrayDecl: []
            TypeDecl: y, []
              IdentifierType: ['float']
            Constant: int, 100
  Typedef: sys_param_its_setup_hotspotzone_t, [], ['typedef']
    TypeDecl: sys_param_its_setup_hotspotzone_t, []
      Struct: None
        Decl: x, [], [], []
          ArrayDecl: []
            TypeDecl: x, []
              IdentifierType: ['float']
            Constant: int, 100
        Decl: y, [], [], []
          ArrayDecl: []
            TypeDecl: y, []
              IdentifierType: ['float']
            Constant: int, 100
        Decl: width, [], [], []
          TypeDecl: width, []
            IdentifierType: ['float']
        Decl: midoffset, [], [], []
          TypeDecl: midoffset, []
            IdentifierType: ['float']
  Typedef: sys_param_its_setup_laneinfo_t, [], ['typedef']
    TypeDecl: sys_param_its_setup_laneinfo_t, []
      Struct: None
        Decl: stepcount, [], [], []
          TypeDecl: stepcount, []
            IdentifierType: ['int']
        Decl: left, [], [], []
          TypeDecl: left, []
            IdentifierType: ['sys_param_its_setup_laneinfo_lane_t']
        Decl: hotspotzone, [], [], []
          TypeDecl: hotspotzone, []
            IdentifierType: ['sys_param_its_setup_hotspotzone_t']
        Decl: trackingzone, [], [], []
          TypeDecl: trackingzone, []
            IdentifierType: ['sys_param_its_setup_zone_t']
        Decl: right, [], [], []
          TypeDecl: right, []
            IdentifierType: ['sys_param_its_setup_laneinfo_lane_t']
        Decl: number, [], [], []
          TypeDecl: number, []
            IdentifierType: ['int']
  Typedef: sys_param_its_setup_area_t, [], ['typedef']
    TypeDecl: sys_param_its_setup_area_t, []
      Struct: None
        Decl: x, [], [], []
          ArrayDecl: []
            TypeDecl: x, []
              IdentifierType: ['float']
            Constant: int, 2
        Decl: y, [], [], []
          ArrayDecl: []
            TypeDecl: y, []
              IdentifierType: ['float']
            Constant: int, 2
        Decl: t, [], [], []
          TypeDecl: t, []
            IdentifierType: ['float']
  Typedef: sys_param_its_setup_blackout_t, [], ['typedef']
    TypeDecl: sys_param_its_setup_blackout_t, []
      Struct: None
        Decl: count, [], [], []
          TypeDecl: count, []
            IdentifierType: ['int']
        Decl: area, [], [], []
          ArrayDecl: []
            TypeDecl: area, []
              IdentifierType: ['sys_param_its_setup_area_t']
            Constant: int, 10
  Typedef: sys_param_its_setup_speedlimit_t, [], ['typedef']
    TypeDecl: sys_param_its_setup_speedlimit_t, []
      Struct: None
        Decl: high_speedlimit_kph, [], [], []
          TypeDecl: high_speedlimit_kph, []
            IdentifierType: ['float']
        Decl: low_speedlimit_kph, [], [], []
          TypeDecl: low_speedlimit_kph, []
            IdentifierType: ['float']
        Decl: speedlimit_compensation_percentage, [], [], []
          TypeDecl: speedlimit_compensation_percentage, []
            IdentifierType: ['int']
  Typedef: sys_param_its_setup_misc_t, [], ['typedef']
    TypeDecl: sys_param_its_setup_misc_t, []
      Struct: None
        Decl: camera_on, [], [], []
          TypeDecl: camera_on, []
            IdentifierType: ['unsigned', 'char']
        Decl: trackingzone_view_on, [], [], []
          TypeDecl: trackingzone_view_on, []
            IdentifierType: ['unsigned', 'char']
        Decl: autoalignment_on, [], [], []
          TypeDecl: autoalignment_on, []
            IdentifierType: ['unsigned', 'char']
        Decl: num_track_autoalignment, [], [], []
          TypeDecl: num_track_autoalignment, []
            IdentifierType: ['int']
  Typedef: sys_param_its_setup_t, [], ['typedef']
    TypeDecl: sys_param_its_setup_t, []
      Struct: None
        Decl: timeschedule, [], [], []
          TypeDecl: timeschedule, []
            IdentifierType: ['sys_param_its_setup_timeschedule_t']
        Decl: misc, [], [], []
          TypeDecl: misc, []
            IdentifierType: ['sys_param_its_setup_misc_t']
        Decl: middlelane, [], [], []
          TypeDecl: middlelane, []
            IdentifierType: ['float']
        Decl: uplaneangle, [], [], []
          TypeDecl: uplaneangle, []
            IdentifierType: ['int']
        Decl: downlaneangle, [], [], []
          TypeDecl: downlaneangle, []
            IdentifierType: ['int']
        Decl: lanecount, [], [], []
          TypeDecl: lanecount, []
            IdentifierType: ['int']
        Decl: speedlimit, [], [], []
          TypeDecl: speedlimit, []
            IdentifierType: ['sys_param_its_setup_speedlimit_t']
        Decl: laneinfo, [], [], []
          ArrayDecl: []
            TypeDecl: laneinfo, []
              IdentifierType: ['sys_param_its_setup_laneinfo_t']
            Constant: int, 4
        Decl: blackout, [], [], []
          TypeDecl: blackout, []
            IdentifierType: ['sys_param_its_setup_blackout_t']
  Typedef: sys_param_sid8did0_its_config_t, [], ['typedef']
    TypeDecl: sys_param_sid8did0_its_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: description, [], [], []
          ArrayDecl: []
            TypeDecl: description, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_its_setup_t']
  Typedef: sys_param_its_relay_t, [], ['typedef']
    TypeDecl: sys_param_its_relay_t, []
      Struct: None
        Decl: relay_cnt, [], [], []
          TypeDecl: relay_cnt, []
            IdentifierType: ['int']
        Decl: relay_enable, [], [], []
          ArrayDecl: []
            TypeDecl: relay_enable, []
              IdentifierType: ['int']
            Constant: int, 2
        Decl: relay_type, [], [], []
          ArrayDecl: []
            ArrayDecl: []
              TypeDecl: relay_type, []
                IdentifierType: ['char']
              Constant: int, 8
            Constant: int, 2
        Decl: relay_on_time_ms, [], [], []
          ArrayDecl: []
            TypeDecl: relay_on_time_ms, []
              IdentifierType: ['int']
            Constant: int, 2
        Decl: relay_off_time_ms, [], [], []
          ArrayDecl: []
            TypeDecl: relay_off_time_ms, []
              IdentifierType: ['int']
            Constant: int, 2
        Decl: relay_adjust_time_ms, [], [], []
          ArrayDecl: []
            TypeDecl: relay_adjust_time_ms, []
              IdentifierType: ['int']
            Constant: int, 2
        Decl: relay_lowbound_time_ms, [], [], []
          ArrayDecl: []
            TypeDecl: relay_lowbound_time_ms, []
              IdentifierType: ['int']
            Constant: int, 2
        Decl: relay_highbound_time_ms, [], [], []
          ArrayDecl: []
            TypeDecl: relay_highbound_time_ms, []
              IdentifierType: ['int']
            Constant: int, 2
        Decl: relay_on_event_type, [], [], []
          ArrayDecl: []
            TypeDecl: relay_on_event_type, []
              IdentifierType: ['int']
            Constant: int, 2
  Typedef: sys_param_its_device_setup_t, [], ['typedef']
    TypeDecl: sys_param_its_device_setup_t, []
      Struct: None
        Decl: relay, [], [], []
          TypeDecl: relay, []
            IdentifierType: ['sys_param_its_relay_t']
  Typedef: sys_param_sid8did1_its_relay_config_t, [], ['typedef']
    TypeDecl: sys_param_sid8did1_its_relay_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: description, [], [], []
          ArrayDecl: []
            TypeDecl: description, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_its_device_setup_t']
  Typedef: sys_param_its_alignment_setup_t, [], ['typedef']
    TypeDecl: sys_param_its_alignment_setup_t, []
      Struct: None
        Decl: autoalignment_on, [], [], []
          TypeDecl: autoalignment_on, []
            IdentifierType: ['unsigned', 'char']
        Decl: num_track_autoalignment, [], [], []
          TypeDecl: num_track_autoalignment, []
            IdentifierType: ['int']
        Decl: status_autoalignment, [], [], []
          TypeDecl: status_autoalignment, []
            IdentifierType: ['int']
        Decl: angle_aligned, [], [], []
          TypeDecl: angle_aligned, []
            IdentifierType: ['float']
  Typedef: sys_param_sid8did2_its_align_config_t, [], ['typedef']
    TypeDecl: sys_param_sid8did2_its_align_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: description, [], [], []
          ArrayDecl: []
            TypeDecl: description, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_its_alignment_setup_t']
  Typedef: sys_param_its_testmode_speedlimit_t, [], ['typedef']
    TypeDecl: sys_param_its_testmode_speedlimit_t, []
      Struct: None
        Decl: high_speedlimit_tolerance_percentage, [], [], []
          TypeDecl: high_speedlimit_tolerance_percentage, []
            IdentifierType: ['float']
        Decl: low_speedlimit_tolerance_percentage, [], [], []
          TypeDecl: low_speedlimit_tolerance_percentage, []
            IdentifierType: ['float']
  Typedef: sys_param_its_testmode_trigger_t, [], ['typedef']
    TypeDecl: sys_param_its_testmode_trigger_t, []
      Struct: None
        Decl: trigger_en, [], [], []
          ArrayDecl: []
            TypeDecl: trigger_en, []
              IdentifierType: ['unsigned', 'char']
            Constant: int, 2
        Decl: trigger_period, [], [], []
          ArrayDecl: []
            TypeDecl: trigger_period, []
              IdentifierType: ['int']
            Constant: int, 2
        Decl: trigger_ttlc_time_ms, [], [], []
          ArrayDecl: []
            TypeDecl: trigger_ttlc_time_ms, []
              IdentifierType: ['float']
            Constant: int, 2
  Typedef: sys_param_its_testmode_hotspotzone_t, [], ['typedef']
    TypeDecl: sys_param_its_testmode_hotspotzone_t, []
      Struct: None
        Decl: modlane_en, [], [], []
          ArrayDecl: []
            TypeDecl: modlane_en, []
              IdentifierType: ['unsigned', 'char']
            Constant: int, 2
        Decl: modlane_offset_hotspotzone_y, [], [], []
          ArrayDecl: []
            TypeDecl: modlane_offset_hotspotzone_y, []
              IdentifierType: ['float']
            Constant: int, 2
        Decl: modlane_offset_hotspotzone_width, [], [], []
          ArrayDecl: []
            TypeDecl: modlane_offset_hotspotzone_width, []
              IdentifierType: ['float']
            Constant: int, 2
        Decl: modlane_offset_hotspotzone_offset, [], [], []
          ArrayDecl: []
            TypeDecl: modlane_offset_hotspotzone_offset, []
              IdentifierType: ['float']
            Constant: int, 2
  Typedef: sys_param_its_testmode_image_t, [], ['typedef']
    TypeDecl: sys_param_its_testmode_image_t, []
      Struct: None
        Decl: skip_image_count, [], [], []
          TypeDecl: skip_image_count, []
            IdentifierType: ['int']
  Typedef: sys_param_its_testmode_misc_t, [], ['typedef']
    TypeDecl: sys_param_its_testmode_misc_t, []
      Struct: None
        Decl: trackzone_xrange, [], [], []
          TypeDecl: trackzone_xrange, []
            IdentifierType: ['float']
        Decl: en_lanechange, [], [], []
          TypeDecl: en_lanechange, []
            IdentifierType: ['unsigned', 'char']
        Decl: low_exclude_speed, [], [], []
          TypeDecl: low_exclude_speed, []
            IdentifierType: ['float']
  Typedef: sys_param_its_testmode_setup_t, [], ['typedef']
    TypeDecl: sys_param_its_testmode_setup_t, []
      Struct: None
        Decl: speedlimit_tolerance, [], [], []
          TypeDecl: speedlimit_tolerance, []
            IdentifierType: ['sys_param_its_testmode_speedlimit_t']
        Decl: trigger, [], [], []
          TypeDecl: trigger, []
            IdentifierType: ['sys_param_its_testmode_trigger_t']
        Decl: modlane, [], [], []
          TypeDecl: modlane, []
            IdentifierType: ['sys_param_its_testmode_hotspotzone_t']
        Decl: imagetest, [], [], []
          TypeDecl: imagetest, []
            IdentifierType: ['sys_param_its_testmode_image_t']
        Decl: misc, [], [], []
          TypeDecl: misc, []
            IdentifierType: ['sys_param_its_testmode_misc_t']
  Typedef: sys_param_sid8did10_its_testmode_config_t, [], ['typedef']
    TypeDecl: sys_param_sid8did10_its_testmode_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: description, [], [], []
          ArrayDecl: []
            TypeDecl: description, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_its_testmode_setup_t']
  Typedef: sys_param_its_data_lane_t, [], ['typedef']
    TypeDecl: sys_param_its_data_lane_t, []
      Struct: None
        Decl: cnt, [], [], []
          TypeDecl: cnt, []
            IdentifierType: ['int']
        Decl: num, [], [], []
          ArrayDecl: []
            TypeDecl: num, []
              IdentifierType: ['int']
            Constant: int, 4
        Decl: period, [], [], []
          ArrayDecl: []
            TypeDecl: period, []
              IdentifierType: ['int']
            Constant: int, 5
  Typedef: sys_param_its_data_count_t, [], ['typedef']
    TypeDecl: sys_param_its_data_count_t, []
      Struct: None
        Decl: ts, [], [], []
          TypeDecl: ts, []
            IdentifierType: ['int']
        Decl: diff, [], [], []
          ArrayDecl: []
            TypeDecl: diff, []
              IdentifierType: ['int']
            Constant: int, 4
        Decl: acc, [], [], []
          ArrayDecl: []
            ArrayDecl: []
              TypeDecl: acc, []
                IdentifierType: ['int']
              Constant: int, 4
            Constant: int, 5
        Decl: lc, [], [], []
          ArrayDecl: []
            TypeDecl: lc, []
              IdentifierType: ['int']
            Constant: int, 4
        Decl: acclc, [], [], []
          ArrayDecl: []
            ArrayDecl: []
              TypeDecl: acclc, []
                IdentifierType: ['int']
              Constant: int, 4
            Constant: int, 5
  Typedef: sys_param_its_data_speed_t, [], ['typedef']
    TypeDecl: sys_param_its_data_speed_t, []
      Struct: None
        Decl: average, [], [], []
          ArrayDecl: []
            ArrayDecl: []
              TypeDecl: average, []
                IdentifierType: ['float']
              Constant: int, 4
            Constant: int, 5
        Decl: min, [], [], []
          ArrayDecl: []
            ArrayDecl: []
              TypeDecl: min, []
                IdentifierType: ['float']
              Constant: int, 4
            Constant: int, 5
        Decl: max, [], [], []
          ArrayDecl: []
            ArrayDecl: []
              TypeDecl: max, []
                IdentifierType: ['float']
              Constant: int, 4
            Constant: int, 5
  Typedef: sys_param_its_data_event_tidlane_t, [], ['typedef']
    TypeDecl: sys_param_its_data_event_tidlane_t, []
      Struct: None
        Decl: tid, [], [], []
          ArrayDecl: []
            TypeDecl: tid, []
              IdentifierType: ['int']
            Constant: int, 32
        Decl: lane, [], [], []
          ArrayDecl: []
            TypeDecl: lane, []
              IdentifierType: ['int']
            Constant: int, 32
  Typedef: sys_param_its_data_event_tidlane2_t, [], ['typedef']
    TypeDecl: sys_param_its_data_event_tidlane2_t, []
      Struct: None
        Decl: tid, [], [], []
          ArrayDecl: []
            TypeDecl: tid, []
              IdentifierType: ['int']
            Constant: int, 32
  Typedef: sys_param_its_data_event_t, [], ['typedef']
    TypeDecl: sys_param_its_data_event_t, []
      Struct: None
        Decl: abnomal, [], [], []
          TypeDecl: abnomal, []
            IdentifierType: ['sys_param_its_data_event_tidlane_t']
        Decl: reverse, [], [], []
          TypeDecl: reverse, []
            IdentifierType: ['sys_param_its_data_event_tidlane_t']
        Decl: speedlimit, [], [], []
          TypeDecl: speedlimit, []
            IdentifierType: ['sys_param_its_data_event_tidlane_t']
        Decl: cs, [], [], []
          ArrayDecl: []
            TypeDecl: cs, []
              IdentifierType: ['char']
            Constant: int, 8
        Decl: notvehicle, [], [], []
          TypeDecl: notvehicle, []
            IdentifierType: ['sys_param_its_data_event_tidlane2_t']
  Typedef: sys_param_pid8_its_data_t, [], ['typedef']
    TypeDecl: sys_param_pid8_its_data_t, []
      Struct: None
        Decl: lane, [], [], []
          TypeDecl: lane, []
            IdentifierType: ['sys_param_its_data_lane_t']
        Decl: count, [], [], []
          TypeDecl: count, []
            IdentifierType: ['sys_param_its_data_count_t']
        Decl: speed, [], [], []
          TypeDecl: speed, []
            IdentifierType: ['sys_param_its_data_speed_t']
        Decl: event, [], [], []
          TypeDecl: event, []
            IdentifierType: ['sys_param_its_data_event_t']
  Typedef: sys_param_vf_reflector_setup_t, [], ['typedef']
    TypeDecl: sys_param_vf_reflector_setup_t, []
      Struct: None
        Decl: reflector_type, [], [], []
          ArrayDecl: []
            TypeDecl: reflector_type, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: reflector_distance, [], [], []
          TypeDecl: reflector_distance, []
            IdentifierType: ['float']
        Decl: reflector_radius, [], [], []
          TypeDecl: reflector_radius, []
            IdentifierType: ['float']
  Typedef: sys_param_sid9did0_vf_reflector_config_t, [], ['typedef']
    TypeDecl: sys_param_sid9did0_vf_reflector_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_vf_reflector_setup_t']
  Typedef: sys_param_vf_server_setup_t, [], ['typedef']
    TypeDecl: sys_param_vf_server_setup_t, []
      Struct: None
        Decl: server_ip, [], [], []
          ArrayDecl: []
            TypeDecl: server_ip, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: server_port, [], [], []
          TypeDecl: server_port, []
            IdentifierType: ['int']
        Decl: server_access_timeout, [], [], []
          TypeDecl: server_access_timeout, []
            IdentifierType: ['int']
        Decl: server_access_retry_cnt, [], [], []
          TypeDecl: server_access_retry_cnt, []
            IdentifierType: ['int']
        Decl: server_sendstack_size, [], [], []
          TypeDecl: server_sendstack_size, []
            IdentifierType: ['int']
        Decl: rs485_access_timeout, [], [], []
          TypeDecl: rs485_access_timeout, []
            IdentifierType: ['int']
        Decl: rs485_access_retry_cnt, [], [], []
          TypeDecl: rs485_access_retry_cnt, []
            IdentifierType: ['int']
  Typedef: sys_param_sid9did1_vf_server_config_t, [], ['typedef']
    TypeDecl: sys_param_sid9did1_vf_server_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_vf_server_setup_t']
  Typedef: sys_param_vf_relay_setup_t, [], ['typedef']
    TypeDecl: sys_param_vf_relay_setup_t, []
      Struct: None
        Decl: relay_cnt, [], [], []
          TypeDecl: relay_cnt, []
            IdentifierType: ['int']
        Decl: relay_enable, [], [], []
          ArrayDecl: []
            TypeDecl: relay_enable, []
              IdentifierType: ['int']
            Constant: int, 4
        Decl: relay_type, [], [], []
          ArrayDecl: []
            ArrayDecl: []
              TypeDecl: relay_type, []
                IdentifierType: ['char']
              Constant: int, 8
            Constant: int, 4
        Decl: relay_on_time_ms, [], [], []
          ArrayDecl: []
            TypeDecl: relay_on_time_ms, []
              IdentifierType: ['int']
            Constant: int, 4
        Decl: relay_on_event_type, [], [], []
          ArrayDecl: []
            TypeDecl: relay_on_event_type, []
              IdentifierType: ['int']
            Constant: int, 4
  Typedef: sys_param_sid9did2_vf_relay_config_t, [], ['typedef']
    TypeDecl: sys_param_sid9did2_vf_relay_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_vf_relay_setup_t']
  Typedef: sys_param_vf_ui_setup_t, [], ['typedef']
    TypeDecl: sys_param_vf_ui_setup_t, []
      Struct: None
        Decl: th_normal, [], [], []
          TypeDecl: th_normal, []
            IdentifierType: ['float']
        Decl: th_caution, [], [], []
          TypeDecl: th_caution, []
            IdentifierType: ['float']
        Decl: th_warning, [], [], []
          TypeDecl: th_warning, []
            IdentifierType: ['float']
        Decl: marker, [], [], []
          TypeDecl: marker, []
            IdentifierType: ['float']
  Typedef: sys_param_sid9did3_vf_ui_config_t, [], ['typedef']
    TypeDecl: sys_param_sid9did3_vf_ui_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_vf_ui_setup_t']
  Typedef: sys_param_pid9_vf_data_t, [], ['typedef']
    TypeDecl: sys_param_pid9_vf_data_t, []
      Struct: None
        Decl: cnt, [], [], []
          TypeDecl: cnt, []
            IdentifierType: ['int']
        Decl: prd, [], [], []
          TypeDecl: prd, []
            IdentifierType: ['float']
        Decl: dat, [], [], []
          ArrayDecl: []
            TypeDecl: dat, []
              IdentifierType: ['float']
            Constant: int, 25
        Decl: std, [], [], []
          ArrayDecl: []
            TypeDecl: std, []
              IdentifierType: ['float']
            Constant: int, 25
        Decl: war, [], [], []
          ArrayDecl: []
            TypeDecl: war, []
              IdentifierType: ['int']
            Constant: int, 25
        Decl: det, [], [], []
          ArrayDecl: []
            TypeDecl: det, []
              IdentifierType: ['int']
            Constant: int, 25
        Decl: sw, [], [], []
          ArrayDecl: []
            TypeDecl: sw, []
              IdentifierType: ['int']
            Constant: int, 25
  Typedef: sys_param_fcw_setup_t, [], ['typedef']
    TypeDecl: sys_param_fcw_setup_t, []
      Struct: None
        Decl: vehicle_type, [], [], []
          TypeDecl: vehicle_type, []
            IdentifierType: ['int']
        Decl: startup_light_en, [], [], []
          TypeDecl: startup_light_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: startup_light_ontime, [], [], []
          TypeDecl: startup_light_ontime, []
            IdentifierType: ['int']
        Decl: alert_led_en, [], [], []
          TypeDecl: alert_led_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: alert_spk_en, [], [], []
          TypeDecl: alert_spk_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: alert_ssr_en, [], [], []
          TypeDecl: alert_ssr_en, []
            IdentifierType: ['unsigned', 'char']
        Decl: alert_ledcolor_caution, [], [], []
          TypeDecl: alert_ledcolor_caution, []
            IdentifierType: ['int']
        Decl: alert_ledcolor_warning, [], [], []
          TypeDecl: alert_ledcolor_warning, []
            IdentifierType: ['int']
        Decl: alert_ledcolor_normal, [], [], []
          TypeDecl: alert_ledcolor_normal, []
            IdentifierType: ['int']
        Decl: alert_blink_period, [], [], []
          TypeDecl: alert_blink_period, []
            IdentifierType: ['int']
        Decl: alert_update_period, [], [], []
          TypeDecl: alert_update_period, []
            IdentifierType: ['int']
        Decl: alert_blocking_period, [], [], []
          TypeDecl: alert_blocking_period, []
            IdentifierType: ['int']
        Decl: vehiclespeed_adj_ratio, [], [], []
          TypeDecl: vehiclespeed_adj_ratio, []
            IdentifierType: ['float']
        Decl: ttc_low_sec, [], [], []
          TypeDecl: ttc_low_sec, []
            IdentifierType: ['float']
        Decl: ttc_high_sec, [], [], []
          TypeDecl: ttc_high_sec, []
            IdentifierType: ['float']
        Decl: ttc_egospeed_low_kph, [], [], []
          TypeDecl: ttc_egospeed_low_kph, []
            IdentifierType: ['float']
        Decl: ttc_egospeed_high_kph, [], [], []
          TypeDecl: ttc_egospeed_high_kph, []
            IdentifierType: ['float']
        Decl: ttc_level1_ratio, [], [], []
          TypeDecl: ttc_level1_ratio, []
            IdentifierType: ['float']
        Decl: ttc_level2_ratio, [], [], []
          TypeDecl: ttc_level2_ratio, []
            IdentifierType: ['float']
        Decl: lane_left_m, [], [], []
          TypeDecl: lane_left_m, []
            IdentifierType: ['float']
        Decl: lane_right_m, [], [], []
          TypeDecl: lane_right_m, []
            IdentifierType: ['float']
        Decl: lane_range_m, [], [], []
          TypeDecl: lane_range_m, []
            IdentifierType: ['float']
        Decl: egospeed_min_kph, [], [], []
          TypeDecl: egospeed_min_kph, []
            IdentifierType: ['float']
        Decl: oncomming_th_kph, [], [], []
          TypeDecl: oncomming_th_kph, []
            IdentifierType: ['float']
  Typedef: sys_param_sid10did0_fcw_config_t, [], ['typedef']
    TypeDecl: sys_param_sid10did0_fcw_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_fcw_setup_t']
  Typedef: sys_param_fcwtest_setup_t, [], ['typedef']
    TypeDecl: sys_param_fcwtest_setup_t, []
      Struct: None
        Decl: test_fcw_event_level1, [], [], []
          TypeDecl: test_fcw_event_level1, []
            IdentifierType: ['unsigned', 'char']
        Decl: test_fcw_event_level2, [], [], []
          TypeDecl: test_fcw_event_level2, []
            IdentifierType: ['unsigned', 'char']
        Decl: test_jctbox_led, [], [], []
          TypeDecl: test_jctbox_led, []
            IdentifierType: ['unsigned', 'char']
        Decl: test_jctbox_spk, [], [], []
          TypeDecl: test_jctbox_spk, []
            IdentifierType: ['unsigned', 'char']
        Decl: test_jctbox_ssr, [], [], []
          TypeDecl: test_jctbox_ssr, []
            IdentifierType: ['unsigned', 'char']
        Decl: test_tbd0, [], [], []
          TypeDecl: test_tbd0, []
            IdentifierType: ['unsigned', 'char']
        Decl: test_tbd1, [], [], []
          TypeDecl: test_tbd1, []
            IdentifierType: ['unsigned', 'char']
        Decl: test_tbd2, [], [], []
          TypeDecl: test_tbd2, []
            IdentifierType: ['unsigned', 'char']
        Decl: test_tbd3, [], [], []
          TypeDecl: test_tbd3, []
            IdentifierType: ['unsigned', 'char']
        Decl: test_tbd4, [], [], []
          TypeDecl: test_tbd4, []
            IdentifierType: ['unsigned', 'char']
  Typedef: sys_param_sid10did1_fcwtest_config_t, [], ['typedef']
    TypeDecl: sys_param_sid10did1_fcwtest_config_t, []
      Struct: None
        Decl: sid, [], [], []
          TypeDecl: sid, []
            IdentifierType: ['int']
        Decl: did, [], [], []
          TypeDecl: did, []
            IdentifierType: ['int']
        Decl: setup, [], [], []
          TypeDecl: setup, []
            IdentifierType: ['sys_param_fcwtest_setup_t']
  Typedef: sys_param_junctionbox_param_t, [], ['typedef']
    TypeDecl: sys_param_junctionbox_param_t, []
      Struct: None
        Decl: r, [], [], []
          TypeDecl: r, []
            IdentifierType: ['int']
        Decl: g, [], [], []
          TypeDecl: g, []
            IdentifierType: ['int']
        Decl: b, [], [], []
          TypeDecl: b, []
            IdentifierType: ['int']
        Decl: spk, [], [], []
          TypeDecl: spk, []
            IdentifierType: ['int']
        Decl: ssra, [], [], []
          TypeDecl: ssra, []
            IdentifierType: ['int']
        Decl: ssrb, [], [], []
          TypeDecl: ssrb, []
            IdentifierType: ['int']
  Typedef: sys_param_junctionbox_ctrl_t, [], ['typedef']
    TypeDecl: sys_param_junctionbox_ctrl_t, []
      Struct: None
        Decl: cmd, [], [], []
          ArrayDecl: []
            TypeDecl: cmd, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: param, [], [], []
          TypeDecl: param, []
            IdentifierType: ['sys_param_junctionbox_param_t']
  Typedef: sys_param_system_status_t, [], ['typedef']
    TypeDecl: sys_param_system_status_t, []
      Struct: None
        Decl: devuid, [], [], []
          ArrayDecl: []
            TypeDecl: devuid, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: serialnumber, [], [], []
          ArrayDecl: []
            TypeDecl: serialnumber, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: swappname, [], [], []
          ArrayDecl: []
            TypeDecl: swappname, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: swversion, [], [], []
          ArrayDecl: []
            TypeDecl: swversion, []
              IdentifierType: ['char']
            Constant: int, 32
        Decl: swdate, [], [], []
          TypeDecl: swdate, []
            IdentifierType: ['int']
        Decl: swtime, [], [], []
          TypeDecl: swtime, []
            IdentifierType: ['int']
        Decl: sid0did0_systembase_config, [], [], []
          TypeDecl: sid0did0_systembase_config, []
            IdentifierType: ['sys_param_sid0did0_systembase_config_t']
        Decl: sid0did1_datetime_config, [], [], []
          TypeDecl: sid0did1_datetime_config, []
            IdentifierType: ['sys_param_sid0did1_datetime_config_t']
        Decl: sid0did2_security_config, [], [], []
          TypeDecl: sid0did2_security_config, []
            IdentifierType: ['sys_param_sid0did2_security_config_t']
        Decl: sid0did4_infra_config, [], [], []
          TypeDecl: sid0did4_infra_config, []
            IdentifierType: ['sys_param_sid0did4_infra_config_t']
        Decl: sid0did5_serialnumber_config, [], [], []
          TypeDecl: sid0did5_serialnumber_config, []
            IdentifierType: ['sys_param_sid0did5_serialnumber_config_t']
        Decl: sid0did6_location_config, [], [], []
          TypeDecl: sid0did6_location_config, []
            IdentifierType: ['sys_param_sid0did6_location_config_t']
        Decl: sid0did8_rs485_protocol_config, [], [], []
          TypeDecl: sid0did8_rs485_protocol_config, []
            IdentifierType: ['sys_param_sid0did8_rs485_protocol_config_t']
        Decl: sid0did10_rsp_eol_config, [], [], []
          TypeDecl: sid0did10_rsp_eol_config, []
            IdentifierType: ['sys_param_sid0did10_rsp_eol_config_t']
        Decl: sid0did11_rsp_install_config, [], [], []
          TypeDecl: sid0did11_rsp_install_config, []
            IdentifierType: ['sys_param_sid0did11_rsp_install_config_t']
        Decl: sid0did12_rsm_config, [], [], []
          TypeDecl: sid0did12_rsm_config, []
            IdentifierType: ['sys_param_sid0did12_rsm_config_t']
        Decl: sid0did13_rsptrk_config, [], [], []
          TypeDecl: sid0did13_rsptrk_config, []
            IdentifierType: ['sys_param_sid0did13_rsptrk_config_t']
        Decl: sid0did200_app_packet_config, [], [], []
          TypeDecl: sid0did200_app_packet_config, []
            IdentifierType: ['sys_param_sid0did200_app_packet_config_t']
        Decl: sid8did0_its_config, [], [], []
          TypeDecl: sid8did0_its_config, []
            IdentifierType: ['sys_param_sid8did0_its_config_t']
        Decl: sid8did1_its_relay_config, [], [], []
          TypeDecl: sid8did1_its_relay_config, []
            IdentifierType: ['sys_param_sid8did1_its_relay_config_t']
        Decl: sid8did2_its_align_config, [], [], []
          TypeDecl: sid8did2_its_align_config, []
            IdentifierType: ['sys_param_sid8did2_its_align_config_t']
        Decl: sid8did10_its_testmode_config, [], [], []
          TypeDecl: sid8did10_its_testmode_config, []
            IdentifierType: ['sys_param_sid8did10_its_testmode_config_t']
  Typedef: sys_param_sidxdidx_configinfo_packing_t, [], ['typedef']
    TypeDecl: sys_param_sidxdidx_configinfo_packing_t, []
      Struct: None
        Decl: data_start_marker, [], [], []
          TypeDecl: data_start_marker, []
            IdentifierType: ['int']
        Decl: param_version, [], [], []
          TypeDecl: param_version, []
            IdentifierType: ['int']
        Decl: guidstr, [], [], []
          ArrayDecl: []
            TypeDecl: guidstr, []
              IdentifierType: ['char']
            Constant: int, 36
        Decl: sid0did0_systembase_config, [], [], []
          TypeDecl: sid0did0_systembase_config, []
            IdentifierType: ['sys_param_sid0did0_systembase_config_t']
        Decl: sid0did1_datetime_config, [], [], []
          TypeDecl: sid0did1_datetime_config, []
            IdentifierType: ['sys_param_sid0did1_datetime_config_t']
        Decl: sid0did2_security_config, [], [], []
          TypeDecl: sid0did2_security_config, []
            IdentifierType: ['sys_param_sid0did2_security_config_t']
        Decl: sid0did3_network_config, [], [], []
          TypeDecl: sid0did3_network_config, []
            IdentifierType: ['sys_param_sid0did3_network_config_t']
        Decl: sid0did4_infra_config, [], [], []
          TypeDecl: sid0did4_infra_config, []
            IdentifierType: ['sys_param_sid0did4_infra_config_t']
        Decl: sid0did5_serialnumber_config, [], [], []
          TypeDecl: sid0did5_serialnumber_config, []
            IdentifierType: ['sys_param_sid0did5_serialnumber_config_t']
        Decl: sid0did6_location_config, [], [], []
          TypeDecl: sid0did6_location_config, []
            IdentifierType: ['sys_param_sid0did6_location_config_t']
        Decl: sid0did7_jctbox_config, [], [], []
          TypeDecl: sid0did7_jctbox_config, []
            IdentifierType: ['sys_param_sid0did7_jctbox_config_t']
        Decl: sid0did8_rs485_protocol_config, [], [], []
          TypeDecl: sid0did8_rs485_protocol_config, []
            IdentifierType: ['sys_param_sid0did8_rs485_protocol_config_t']
        Decl: sid0did9_camera_config, [], [], []
          TypeDecl: sid0did9_camera_config, []
            IdentifierType: ['sys_param_sid0did9_camera_config_t']
        Decl: sid0did10_rsp_eol_config, [], [], []
          TypeDecl: sid0did10_rsp_eol_config, []
            IdentifierType: ['sys_param_sid0did10_rsp_eol_config_t']
        Decl: sid0did11_rsp_install_config, [], [], []
          TypeDecl: sid0did11_rsp_install_config, []
            IdentifierType: ['sys_param_sid0did11_rsp_install_config_t']
        Decl: sid0did12_rsm_config, [], [], []
          TypeDecl: sid0did12_rsm_config, []
            IdentifierType: ['sys_param_sid0did12_rsm_config_t']
        Decl: sid0did13_rsptrk_config, [], [], []
          TypeDecl: sid0did13_rsptrk_config, []
            IdentifierType: ['sys_param_sid0did13_rsptrk_config_t']
        Decl: sid0did30_rfictx_select_config, [], [], []
          TypeDecl: sid0did30_rfictx_select_config, []
            IdentifierType: ['sys_param_sid0did30_rfictx_select_config_t']
        Decl: sid0did31_rfictx_bgt24at2_config, [], [], []
          TypeDecl: sid0did31_rfictx_bgt24at2_config, []
            IdentifierType: ['sys_param_sid0did31_rfictx_bgt24at2_config_t']
        Decl: sid0did40_rficrx_select_config, [], [], []
          TypeDecl: sid0did40_rficrx_select_config, []
            IdentifierType: ['sys_param_sid0did40_rficrx_select_config_t']
        Decl: sid0did41_rficrx_bgt24ar4_config, [], [], []
          TypeDecl: sid0did41_rficrx_bgt24ar4_config, []
            IdentifierType: ['sys_param_sid0did41_rficrx_bgt24ar4_config_t']
        Decl: sid0did50_pll_select_config, [], [], []
          TypeDecl: sid0did50_pll_select_config, []
            IdentifierType: ['sys_param_sid0did50_pll_select_config_t']
        Decl: sid0did51_pll_lmx2491_config, [], [], []
          TypeDecl: sid0did51_pll_lmx2491_config, []
            IdentifierType: ['sys_param_sid0did51_pll_lmx2491_config_t']
        Decl: sid0did60_adc_select_config, [], [], []
          TypeDecl: sid0did60_adc_select_config, []
            IdentifierType: ['sys_param_sid0did60_adc_select_config_t']
        Decl: sid0did61_adc_adar7251_config, [], [], []
          TypeDecl: sid0did61_adc_adar7251_config, []
            IdentifierType: ['sys_param_sid0did61_adc_adar7251_config_t']
        Decl: sid0did62_adc_max11043_config, [], [], []
          TypeDecl: sid0did62_adc_max11043_config, []
            IdentifierType: ['sys_param_sid0did62_adc_max11043_config_t']
        Decl: sid0did200_app_packet_config, [], [], []
          TypeDecl: sid0did200_app_packet_config, []
            IdentifierType: ['sys_param_sid0did200_app_packet_config_t']
        Decl: sid6did0_candrv_config, [], [], []
          TypeDecl: sid6did0_candrv_config, []
            IdentifierType: ['sys_param_sid6did0_candrv_config_t']
        Decl: sid6did1_cansignal_config, [], [], []
          TypeDecl: sid6did1_cansignal_config, []
            IdentifierType: ['sys_param_sid6did1_cansignal_config_t']
        Decl: sid6did2_cantxmsg_config, [], [], []
          TypeDecl: sid6did2_cantxmsg_config, []
            IdentifierType: ['sys_param_sid6did2_cantxmsg_config_t']
        Decl: sid7did0_filesystem_config, [], [], []
          TypeDecl: sid7did0_filesystem_config, []
            IdentifierType: ['sys_param_sid7did0_filesystem_config_t']
        Decl: sid8did0_its_config, [], [], []
          TypeDecl: sid8did0_its_config, []
            IdentifierType: ['sys_param_sid8did0_its_config_t']
        Decl: sid8did1_its_relay_config, [], [], []
          TypeDecl: sid8did1_its_relay_config, []
            IdentifierType: ['sys_param_sid8did1_its_relay_config_t']
        Decl: sid8did2_its_align_config, [], [], []
          TypeDecl: sid8did2_its_align_config, []
            IdentifierType: ['sys_param_sid8did2_its_align_config_t']
        Decl: sid8did10_its_testmode_config, [], [], []
          TypeDecl: sid8did10_its_testmode_config, []
            IdentifierType: ['sys_param_sid8did10_its_testmode_config_t']
        Decl: sid9did0_vf_reflector_config, [], [], []
          TypeDecl: sid9did0_vf_reflector_config, []
            IdentifierType: ['sys_param_sid9did0_vf_reflector_config_t']
        Decl: sid9did1_vf_server_config, [], [], []
          TypeDecl: sid9did1_vf_server_config, []
            IdentifierType: ['sys_param_sid9did1_vf_server_config_t']
        Decl: sid9did2_vf_relay_config, [], [], []
          TypeDecl: sid9did2_vf_relay_config, []
            IdentifierType: ['sys_param_sid9did2_vf_relay_config_t']
        Decl: sid9did3_vf_ui_config, [], [], []
          TypeDecl: sid9did3_vf_ui_config, []
            IdentifierType: ['sys_param_sid9did3_vf_ui_config_t']
        Decl: sid10did0_fcw_config, [], [], []
          TypeDecl: sid10did0_fcw_config, []
            IdentifierType: ['sys_param_sid10did0_fcw_config_t']
        Decl: sid10did1_fcwtest_config, [], [], []
          TypeDecl: sid10did1_fcwtest_config, []
            IdentifierType: ['sys_param_sid10did1_fcwtest_config_t']
        Decl: data_end_marker, [], [], []
          TypeDecl: data_end_marker, []
            IdentifierType: ['int']
        Decl: data_end_marker1, [], [], []
          TypeDecl: data_end_marker1, []
            IdentifierType: ['int']
        Decl: data_end_marker2, [], [], []
          TypeDecl: data_end_marker2, []
            IdentifierType: ['int']
  Decl: sys_param_sidxdidx_configinfo_packing, [], ['extern'], []
    TypeDecl: sys_param_sidxdidx_configinfo_packing, []
      IdentifierType: ['sys_param_sidxdidx_configinfo_packing_t']
  Decl: sys_param_sidxdidx_configinfo_packing_default, [], ['extern'], []
    TypeDecl: sys_param_sidxdidx_configinfo_packing_default, []
      IdentifierType: ['sys_param_sidxdidx_configinfo_packing_t']
  Decl: sys_param_sidxdidx_configinfo_packing_factory, [], ['extern'], []
    TypeDecl: sys_param_sidxdidx_configinfo_packing_factory, []
      IdentifierType: ['sys_param_sidxdidx_configinfo_packing_t']
  Decl: sys_param_pid8_its_data_default, ['const'], ['extern'], []
    TypeDecl: sys_param_pid8_its_data_default, ['const']
      IdentifierType: ['sys_param_pid8_its_data_t']
  Decl: sys_param_pid0_status_data, [], ['extern'], []
    TypeDecl: sys_param_pid0_status_data, []
      IdentifierType: ['sys_param_pid0_status_data_t']
  Decl: sys_param_pid8_its_data, [], ['extern'], []
    TypeDecl: sys_param_pid8_its_data, []
      IdentifierType: ['sys_param_pid8_its_data_t']
  Decl: sys_param_pid9_vf_data, [], ['extern'], []
    TypeDecl: sys_param_pid9_vf_data, []
      IdentifierType: ['sys_param_pid9_vf_data_t']


*/
