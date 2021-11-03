/************************************************************************
 | Project Name: KRS24
 |    File Name: sys_param.h
 |  Description: detailed Description
 |-----------------------------------------------------------------------
 |               A U T H O R   I D E N T I T Y
 |-----------------------------------------------------------------------
 | Initials     Name                      Company
 | --------     ---------------------     -------------------------------
 | SKJ          SONG KYEONG JIN           KRS Corporation
 |-----------------------------------------------------------------------
 |              R E V I S I O N   H I S T O R Y
 |-----------------------------------------------------------------------
 | Date         Ver  Author  Description
 | ----------  ----  ------  --------------------------------------------
 | 2014.12.02   0.0   SKJ   Creation;
 |***********************************************************************/

#ifndef SYS_PARAM_H__
#define SYS_PARAM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "sys_param_cfg.h"

#if SYS_PARAM_LOG_ENABLE == 1
#define sys_param_log krs_log
#else
#define sys_param_log krs_log_dummy
#endif

#if SYS_PARAM_ASSERT_ENABLE == 1
#define sys_param_assert krs_assert
#else
#define sys_param_assert(x)
#endif


/* module specific types  */


/* define structure for this module */


#define sys_param_match_string(buff, param) (strncmp(buff, param, (sizeof(param) - 1)) == 0 ? retOK : retFail)


#include "sys_param_jsontype.h"
#include "sys_param_jsontype_dump.h"
#include "sys_param_jsontype_gen.h"
#include "sys_param_jsontype_info.h"
#include "sys_param_jsontype_load.h"


#define sys_param_string_check(config, test) (strncmp(config, test, SYS_PARAM_STRLEN_MAX) == 0 ? retOK : retFail)
#define sys_param_bool_array_isend(element) ((element == SYS_PARAM_BOOL_ARR_END_VALUE) ? retOK : retFail)
#define sys_param_int32_array_isend(element) ((element == SYS_PARAM_INT32_ARR_END_VALUE) ? retOK : retFail)
#define sys_param_int64_array_isend(element) ((element == SYS_PARAM_INT64_ARR_END_VALUE) ? retOK : retFail)
#define sys_param_f32_array_isend(element) ((element == SYS_PARAM_F32_ARR_END_VALUE) ? retOK : retFail)
#define sys_param_f64_array_isend(element) ((element == SYS_PARAM_F64_ARR_END_VALUE) ? retOK : retFail)


/* declare extern global variables */
#define SYS_PARAM sys_param_sidxdidx_configinfo_packing

/******************************************************************/
/* SID:0x00, DID:0x00 , system base setup */
/******************************************************************/
#define SYS_PARAM_SYSTEMBASE SYS_PARAM.sid0did0_systembase_config.setup
#define SYS_PARAM_SWUPDATE SYSPARAM_SYTEMBASE.swupdate
#define SYS_PARAM_CONSOLELOG SYS_PARAM_SYSTEMBASE.consolelog
#define SYS_PARAM_CONSOLEUDP SYS_PARAM_SYSTEMBASE.consoleudp
#define SYS_PARAM_SENSORTYPE SYS_PARAM_SYSTEMBASE.sensortype
#define SYS_PARAM_ETHDEFAULT SYS_PARAM_SYSTEMBASE.eth_default
#define SYS_PARAM_SYSCONTROL SYS_PARAM_SYSTEMBASE.syscontrol
#define SYS_PARAM_LOGICCONTROL SYS_PARAM_SYSTEMBASE.logiccontrol

#define SYS_PARAM_ETHDEFAULT_IP SYS_PARAM_ETHDEFAULT.ip
#define SYS_PARAM_ETHDEFAULT_NM SYS_PARAM_ETHDEFAULT.nm
#define SYS_PARAM_ETHDEFAULT_GW SYS_PARAM_ETHDEFAULT.gw
#define SYS_PARAM_ETHDEFAULT_DNS SYS_PARAM_ETHDEFAULT.dns
#define SYS_PARAM_ETHDEFAULT_MAC SYS_PARAM_ETHDEFAULT.mac
#define SYS_PARAM_ETHDEFAULT_LINKSPEED SYS_PARAM_ETHDEFAULT.linkspeed
#define SYS_PARAM_ETHDEFAULT_DHCP_EN SYS_PARAM_ETHDEFAULT.dhcp_en

/******************************************************************/
/* SID:0x00, DID:0x01 , datetime setup */
/******************************************************************/
/******************************************************************/
/* SID:0x00, DID:0x02 , security setup */
/******************************************************************/
/******************************************************************/
/* SID:0x00, DID:0x03 , indirect network setup */
/******************************************************************/
#define SYS_PARAM_NETWORK SYS_PARAM.sid0did3_network_config.setup

/******************************************************************/
/* SID:0x00, DID:0x04 , systemversion setup                       */
/******************************************************************/
#define SYS_PARAM_VERSION SYS_PARAM.sid0did4_version_config.setup

/******************************************************************/
/* SID:0x00, DID:0x05 , serial number setup                       */
/******************************************************************/
#define SYS_PARAM_SERIALNUM SYS_PARAM.sid0did5_serialnumber_config.setup

/******************************************************************/
/* SID:0x00, DID:0x06 , location and gps setup */
/******************************************************************/
#define SYS_PARAM_LOCATION SYS_PARAM.sid0did6_location_config.setup.location
#define SYS_PARAM_GPS SYS_PARAM.sid0did6_location_config.setup.gps

/******************************************************************/
/* SID:0x00, DID: 7 , junction box setup */
/******************************************************************/
#define SYS_PARAM_JCTBOX SYS_PARAM.sid0did7_jctbox_config.setup
/******************************************************************/
/* SID:0x00, DID: 8 , rs485 protocol setup */
/******************************************************************/
#define SYS_PARAM_RS485 SYS_PARAM.sid0did8_rs485_protocol_config.setup
/******************************************************************/
/* SID:0x00, DID: 9 , camera setup */
/******************************************************************/
#define SYS_PARAM_CAM SYS_PARAM.sid0did9_camera_config.setup
#define SYS_PARAM_CAM_COUNT SYS_PARAM_CAM.count
#define SYS_PARAM_CAM0 SYS_PARAM_CAM.cam[0]
#define SYS_PARAM_CAM1 SYS_PARAM_CAM.cam[1]
/******************************************************************/
/* SID:0x00, DID: 10 , radar signal processing EOL setup */
/******************************************************************/
#define SYS_PARAM_RSP_EOL SYS_PARAM.sid0did10_rsp_eol_config.setup

/******************************************************************/
/* SID:0x00, DID: 11 , radar signal processing installation setup */
/******************************************************************/
#define SYS_PARAM_RSP_INSTALL SYS_PARAM.sid0did11_rsp_install_config.setup

/******************************************************************/
/* SID:0x00, DID: 12 , radar rf signal modulation(RSM) setup      */
/******************************************************************/
#define SYS_PARAM_RSM SYS_PARAM.sid0did12_rsm_config.setup
#define SYS_PARAM_RSM_MODE SYS_PARAM_RSM.mode
#define SYS_PARAM_RSM_USERFREQ SYS_PARAM_RSM.userfreq
#define SYS_PARAM_RSM_SCANRATE SYS_PARAM_RSM.scanrate
#define SYS_PARAM_RSM_DAQ_DELAYSAMPLE SYS_PARAM_RSM.daq_sampledelay

/******************************************************************/
/* SID:0x00, DID:13  rsp tracking (rsp.trk) setup   */
/******************************************************************/
#define SYS_PARAM_RSPTRK SYS_PARAM.sid0did13_rsptrk_config.setup
#define SYS_PARAM_RSPTRK_POSTTUNE SYS_PARAM_RSPTRK.posttune
#define SYS_PARAM_RSPTRK_TRKTUNE SYS_PARAM_RSPTRK.trktune

/******************************************************************/
/* SID:0x00, DID:30~39 rfic tx setup  */
/******************************************************************/
#define SYS_PARAM_DAQ_RFTX_SEL SYS_PARAM.sid0did30_rfictx_select_config.setup
#define SYS_PARAM_DAQ_RFTX_BGT24AT2 SYS_PARAM.sid0did31_rfictx_bgt24at2_config.setup

/******************************************************************/
/* SID:0x00, DID:40~49 rfic rx setup  */
/******************************************************************/
#define SYS_PARAM_DAQ_RFRX_SEL SYS_PARAM.sid0did40_rficrx_select_config.setup
#define SYS_PARAM_DAQ_RFRX_BGT24AR4 SYS_PARAM.sid0did41_rficrx_bgt24ar4_config.setup

/******************************************************************/
/* SID:0x00, DID:50~59 rfic pll setup  */
/******************************************************************/
#define SYS_PARAM_DAQ_PLL_SEL SYS_PARAM.sid0did50_pll_select_config.setup
#define SYS_PARAM_DAQ_PLL_LMX2491 SYS_PARAM.sid0did51_pll_lmx2491_config.setup

/******************************************************************/
/* SID:0x00, DID:60 rfm adc select setup  */
/******************************************************************/
#define SYS_PARAM_DAQ_ADC_SEL SYS_PARAM.sid0did60_adc_select_config.setup

/******************************************************************/
/* SID:0x00, DID:60 rfm adc adi adar7251 setup  */
/******************************************************************/
#define SYS_PARAM_DAQ_ADC_ADAR SYS_PARAM.sid0did61_adc_adar7251_config.setup

/******************************************************************/
/* SID:0x00, DID:62 rfm adc maxim max11043 setup  */
/******************************************************************/
#define SYS_PARAM_DAQ_ADC_MAX SYS_PARAM.sid0did62_adc_max11043_config.setup

/******************************************************************/
/* SID:0x00, DID:200 application packet setup  */
/******************************************************************/
#define SYS_PARAM_APPPKT_MAX SYS_PARAM_APP_PACKET_MAX
#define SYS_PARAM_APPPKT SYS_PARAM.sid0did200_app_packet_config.setup
#define SYS_PARAM_APPPKT_COUNT SYS_PARAM_APPPKT.count
#define SYS_PARAM_APPPKT_PORTS SYS_PARAM_APPPKT.ports

/******************************************************************/
/* SID:0x06, DID:0  CAN Communication Setup                      */
/******************************************************************/
#define SYS_PARAM_CANDRV SYS_PARAM.sid6did0_candrv_config.setup

/******************************************************************/
/* SID:0x06, DID:1  CAN RX Signal Setup                              */
/******************************************************************/
#define SYS_PARAM_CANRX SYS_PARAM.sid6did1_cansignal_config.setup

/******************************************************************/
/* SID:0x06, DID:2  CAN TX Message Setup                          */
/******************************************************************/
#define SYS_PARAM_CANTX SYS_PARAM.sid6did2_cantxmsg_config.setup

/******************************************************************/
/* SID:0x07, DID:0  Filesystem Setup                              */
/******************************************************************/
#define SYS_PARAM_FILESYSTEM SYS_PARAM.sid7did0_filesystem_config.setup

/******************************************************************/
/* SID: 8, DID: 0 , ITS application setup */
/******************************************************************/
#define SYS_PARAM_ITS_CONFIG SYS_PARAM.sid8did0_its_config.setup

/******************************************************************/
/* SID: 8, DID: 1 , ITS application for relay setup */
/******************************************************************/
#define SYS_PARAM_ITS_RELAY_CONFIG SYS_PARAM.sid8did1_its_relay_config.setup

/******************************************************************/
/* SID: 8, DID: 2 , ITS auto alignment setup */
/******************************************************************/
#define SYS_PARAM_ITS_ALIGNMENT_CONFIG SYS_PARAM.sid8did2_its_align_config.setup

/******************************************************************/
/* SID: 8, DID: 10 , ITS application for test parameter setup */
/******************************************************************/
#define SYS_PARAM_ITS_TESTMODE_CONFIG SYS_PARAM.sid8did10_its_testmode_config.setup

/******************************************************************/
/* SID: 9, DID: 0 , Virtual Fence reflector setup */
/******************************************************************/
#define SYS_PARAM_VF_REFLECTOR SYS_PARAM.sid9did0_vf_reflector_config.setup

/******************************************************************/
/* SID: 9, DID: 1 , Virtual Fence destination server setup */
/******************************************************************/
#define SYS_PARAM_VF_SERVER SYS_PARAM.sid9did1_vf_server_config.setup

/******************************************************************/
/* SID: 9, DID: 2 , Virtual Fence relay setup */
/******************************************************************/
#define SYS_PARAM_VF_RELAY SYS_PARAM.sid9did2_vf_relay_config.setup

/******************************************************************/
/* SID: 9, DID: 3 , UI setup */
/******************************************************************/
#define SYS_PARAM_VF_SERVER SYS_PARAM.sid9did1_vf_server_config.setup
#define SYS_PARAM_VF_UI SYS_PARAM.sid9did3_vf_ui_config.setup

/******************************************************************/
/* SID: 10, DID: 0 , FCW Forward Collision Warning application setup */
/******************************************************************/
#define SYS_PARAM_FCW SYS_PARAM.sid10did0_fcw_config.setup

/******************************************************************/
/* SID: 10, DID: 1 , FCW Forward Collision Warning application test */
/******************************************************************/
#define SYS_PARAM_FCWTEST SYS_PARAM.sid10did1_fcwtest_config.setup

/* declare extern global functions */
extern int32_t sys_param_init(void);
extern uint32_t sys_param_get_typename_hash(char *str, size_t n);
extern int32_t sys_param_load_from_default(void);
extern int32_t sys_param_load_from_file(const char* filename, void *param);
extern int32_t sys_param_save_to_file(const char* filename, void *param);
extern int32_t sys_param_factoryinit(void);
extern int32_t sys_param_load_from_factory(void *param);
extern int32_t sys_param_save_to_factory(void *param);
extern void sys_param_wdg_clear(void);

#ifdef __cplusplus
}
#endif

#endif /* SYS_PARAM_H__ */
