/************************************************************************
| Project Name: sys_param_jsontype
|    File Name: sys_param_jsontype.h
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
| 2018.07.19   0.0   SKJ   Creation;
| 2019.03.07   0.1   SKJ   Creation;
|***********************************************************************/
#ifndef SYS_PARAM_JSONTYPE_H__
#define SYS_PARAM_JSONTYPE_H__

#ifdef __cplusplus
extern "C" {
#endif


// JSON Object mapping rule:
// JSON   <-> C
// number <-> int32_t / int64_t
// float number <-> float
// double number <-> double
// bool -> unsigned char
// object -> struct
// array -> array , element only the same type is required. (number, string, object etc.)
// string -> char array with SYS_PARAM_STRLEN_MAX length

#define SYS_PARAM_STRLEN_MAX 32
#define SYS_PARAM_STRLEN_MIN 8
#define SYS_PARAM_ERRORMSG_LEN_MAX 256


// array stop value
#define SYS_PARAM_BOOL_ARR_END_VALUE (0xFF)
#define SYS_PARAM_INT8_ARR_END_VALUE (-128)
#define SYS_PARAM_INT32_ARR_END_VALUE (-2147483647)
#define SYS_PARAM_INT64_ARR_END_VALUE (-9223372036854775807LL)
#define SYS_PARAM_F32_ARR_END_VALUE (-3.402823466e+38)
#define SYS_PARAM_F64_ARR_END_VALUE (-1.7976931348623158e+308)

#define jsbool_t unsigned char
#define jsint8_t signed char
#define jsint32_t int
#define jsint64_t long long
#define jsf32_t float
#define jsf64_t double
#define jschar_t char

#ifndef false
#define false 0
#endif
#ifndef true
#define true 1
#endif


typedef enum
{
    sys_param_STRLEN_MAX = SYS_PARAM_STRLEN_MAX,
    sys_param_STRLEN_MIN = SYS_PARAM_STRLEN_MIN,
} sys_param_parameter_t;

//
//    /******************************************************************/
//    /* structure to json unittest  */
//    /******************************************************************/
//    typedef struct
//    {
//        jsbool_t array_bool_1d[4];
//        jsint32_t array_int32_1d[4];
//        jsint64_t array_int64_1d[4];
//        jsf32_t array_f32_1d[4];
//        jsf64_t array_f64_1d[4];
//        jschar_t string_1d[4];
//    } sys_param_array_1d_t;
//
//
//    typedef struct
//    {
//        jsbool_t array_bool_2d[4][8];
//        jsint32_t array_int32_2d[4][8];
//        jsint64_t array_int64_2d[4][8];
//        jsf32_t array_f32_2d[4][8];
//        jsf64_t array_f64_2d[4][8];
//        jschar_t string_2d[4][8];
//    } sys_param_array_2d_t;


//    typedef struct
//    {
//        sys_param_array_1d_t arr1d;
//        sys_param_array_2d_t arr2d;
//        sys_param_array_1d_t arrobj1d[2];
//    } sys_param_array_test_t;


/******************************************************************/
/* response */
/******************************************************************/
typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    jschar_t error[SYS_PARAM_ERRORMSG_LEN_MAX];
} sys_param_comm_negative_response_t;


/******************************************************************/
/* common config parameter setup */
/******************************************************************/
typedef struct
{
    jschar_t ip[SYS_PARAM_STRLEN_MAX];
    jschar_t nm[SYS_PARAM_STRLEN_MAX];
    jschar_t gw[SYS_PARAM_STRLEN_MAX];
    jschar_t mac[SYS_PARAM_STRLEN_MAX];
    jschar_t dns[SYS_PARAM_STRLEN_MAX];
    jsint32_t linkspeed;
    jsbool_t dhcp_en;
} sys_param_common_comm_ethernet_config_t;

typedef struct
{
    jschar_t type[SYS_PARAM_STRLEN_MAX];
    jsint32_t baudrate;
    jschar_t flowcontrol[SYS_PARAM_STRLEN_MAX];
    jsint32_t data;
    jsint32_t stopbit;
} sys_param_common_comm_serialcomm_config_t;


typedef struct
{
    jschar_t type[SYS_PARAM_STRLEN_MAX];
} sys_param_common_comm_tbd_config_t;


/******************************************************************/
/* SID:0x00, DID:0x00 , system base setup */
/******************************************************************/
typedef struct
{
    jsint32_t swupdate_request; //::{0:"update_complete", 1:"swupdate_request"}
    jsint32_t swupdate_type;    //::{0:"udp", 1:"tcp",3:"can",4:"canfd",5:"uart",6:"rs485"}
    jsint32_t swupdate_count;
    jsf64_t swupdate_timestamp; // unix timestamp in second
} sys_param_swupdate_config_t;


typedef struct
{
    jsint32_t bts_log_level;
    jsbool_t bts_log_opt_type_en;
    jsbool_t bts_log_opt_time_en;
    jsbool_t bts_log_opt_difftime_en;
    jsbool_t bts_log_opt_file_en;
    jsbool_t bts_log_opt_line_en;
    jsbool_t bts_log_opt_function_en;
    jsbool_t bts_log_module_comm_packet_en;
    jsbool_t bts_log_module_comm_appl_callback_en;
    jsint32_t bts_log_array_frontlen;
    jsint32_t bts_log_array_backlen;
    jsbool_t bts_log_cpu_usage;
    jsbool_t bts_log_opt_datetime_en;
    jsbool_t bts_log_opt_datetime_ms_en;
    jsbool_t bts_log_opt_datetime_us_en;
    jsbool_t bts_log_opt_gps_en;
} sys_param_consolelog_config_t;

typedef struct
{
	jsbool_t en;
	jschar_t ip[SYS_PARAM_STRLEN_MAX];
	jsint32_t port;
} sys_param_consoleudp_config_t;

typedef struct
{
    jschar_t type[SYS_PARAM_STRLEN_MAX];
    jschar_t serialnumber[SYS_PARAM_STRLEN_MAX];

    jsbool_t opmode_its_en;   // ITS
    jsbool_t opmode_vf_en;    // virtual fense
    jsbool_t opmode_fcw_en;   // FCW
    jsbool_t opmode_lm_en;    // levelmeter

    jsbool_t pid_status_en;
    jsbool_t pid_object_en;
    jsbool_t pid_track_en;
    jsbool_t pid_image_en;
    jsbool_t pid_imagsp_en;
    jsbool_t pid_logger_en;
    jsbool_t pid_canlog_en;
    jsbool_t pid_sensor_en;

    jsbool_t pid_app_its_en;
    jsbool_t pid_app_vf_en;
    jsbool_t pid_app_fcw_en;
    jsbool_t pid_app_lm_en;

    jsbool_t raw_chirp_en;
    jsbool_t raw_chirp0_en;
    jsbool_t raw_chirp1_en;
    jsbool_t raw_chirp2_en;
    jsbool_t raw_chirp3_en;

    jsbool_t raw_app_en;
    jsbool_t raw_app_its_en;
    jsbool_t raw_app_vf_en;
    jsbool_t raw_app_fcw_en;
    jsbool_t raw_app_lm_en;
    jsbool_t raw_app_install_en;
    jsbool_t raw_app_flog_en;

    jsbool_t raw_mon_en;
    jsbool_t raw_mon_power_en;
    jsbool_t raw_mon_time_en;
    jsbool_t raw_mon_task_en;
} sys_param_system_sensortype_config_t;

typedef struct
{
    jsbool_t restart_en;
    jsint32_t restart_timeout_s;
} sys_param_system_control_t;

typedef struct
{
    jsint32_t logic_start_scan_offset;
} sys_param_logic_control_config_t;


typedef struct
{
    sys_param_swupdate_config_t swupdate;
    sys_param_consolelog_config_t consolelog;
    sys_param_consoleudp_config_t consoleudp;
    sys_param_system_sensortype_config_t sensortype;
    sys_param_common_comm_ethernet_config_t eth_default;
    sys_param_system_control_t syscontrol;
    sys_param_logic_control_config_t logiccontrol;
} sys_param_system_config_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_system_config_t setup;
} sys_param_sid0did0_systembase_config_t;


/******************************************************************/
/* SID:0x00, DID:0x01 , datetime setup */
/******************************************************************/
typedef struct
{

    jschar_t type[SYS_PARAM_STRLEN_MAX];
    jschar_t unit[SYS_PARAM_STRLEN_MIN];
    jsf64_t timestamp;
    jsbool_t gps_update_en; // update from gps enable
} sys_param_datetime_setup_t;


typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_datetime_setup_t setup;
} sys_param_sid0did1_datetime_config_t;

/******************************************************************/
/* SID:0x00, DID:0x02 , security setup */
/******************************************************************/
typedef struct
{
    jsbool_t lock_en;
    jschar_t admin_password[SYS_PARAM_STRLEN_MAX];
    jschar_t user_password[SYS_PARAM_STRLEN_MAX];
    jschar_t type[SYS_PARAM_STRLEN_MAX];
    jschar_t latitude[SYS_PARAM_STRLEN_MAX];
    jschar_t longitude[SYS_PARAM_STRLEN_MAX];
    jschar_t direction[SYS_PARAM_STRLEN_MAX];
} sys_param_security_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_security_setup_t setup;
} sys_param_sid0did2_security_config_t;



/******************************************************************/
/* SID:0x00, DID:0x03 , indirect network setup */
/******************************************************************/
typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_common_comm_ethernet_config_t setup;
} sys_param_sid0did3_network_config_t;


/******************************************************************/
/* SID:0x00, DID:0x04 , systemversion setup                       */
/******************************************************************/
typedef struct
{
    jschar_t ver[SYS_PARAM_STRLEN_MAX];
    jschar_t date[SYS_PARAM_STRLEN_MAX];
    jschar_t spec[SYS_PARAM_STRLEN_MAX];
} sys_param_version_t;



typedef struct
{
    sys_param_version_t sys;
    sys_param_version_t sw;
    sys_param_version_t be;
    sys_param_version_t fe;
    sys_param_version_t housing;
    sys_param_version_t cable;
    sys_param_version_t protocol;
    sys_param_version_t customer;
} sys_param_version_setup_t;


typedef struct
{
    jschar_t infraid[SYS_PARAM_STRLEN_MAX];
    jschar_t radarid[SYS_PARAM_STRLEN_MAX];
    jschar_t locationid[SYS_PARAM_STRLEN_MAX];
    jschar_t basestationid[SYS_PARAM_STRLEN_MAX];
    jschar_t switchid[SYS_PARAM_STRLEN_MAX];
    jschar_t desc[SYS_PARAM_STRLEN_MAX];
    jschar_t desc1[SYS_PARAM_STRLEN_MAX];
    jschar_t desc2[SYS_PARAM_STRLEN_MAX];
    jschar_t longitude[SYS_PARAM_STRLEN_MAX];
    jschar_t latitude[SYS_PARAM_STRLEN_MAX];
    jschar_t direction[SYS_PARAM_STRLEN_MAX];
    jschar_t height[SYS_PARAM_STRLEN_MAX];
    jschar_t roadid[SYS_PARAM_STRLEN_MAX];
    jschar_t roadid1[SYS_PARAM_STRLEN_MAX];
    jschar_t roadid2[SYS_PARAM_STRLEN_MAX];
    jschar_t area[SYS_PARAM_STRLEN_MAX];
    jschar_t area1[SYS_PARAM_STRLEN_MAX];
    jschar_t range[SYS_PARAM_STRLEN_MAX];
    jschar_t range1[SYS_PARAM_STRLEN_MAX];
    jschar_t lane[SYS_PARAM_STRLEN_MAX];
    jschar_t lane1[SYS_PARAM_STRLEN_MAX];
    jschar_t lane2[SYS_PARAM_STRLEN_MAX];
    jschar_t lane3[SYS_PARAM_STRLEN_MAX];
    jschar_t lane4[SYS_PARAM_STRLEN_MAX];
} sys_param_infra_setup_t;



typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_infra_setup_t setup;
} sys_param_sid0did4_infra_config_t;

/******************************************************************/
/* SID:0x00, DID:0x05 , serial number setup                       */
/******************************************************************/
typedef struct
{
    jschar_t sys[SYS_PARAM_STRLEN_MAX];
    jschar_t be[SYS_PARAM_STRLEN_MAX];
    jschar_t fe[SYS_PARAM_STRLEN_MAX];
} sys_param_serialnumber_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_serialnumber_setup_t setup;
} sys_param_sid0did5_serialnumber_config_t;


/******************************************************************/
/* SID:0x00, DID:0x06 , location and gps setup */
/******************************************************************/
typedef struct
{
    jschar_t type[SYS_PARAM_STRLEN_MAX]; // type : wgs84, etc
    jsf64_t latitude;
    jsf64_t longitude;
    jsf32_t direction;
    jsbool_t gps_update_en; // enable position update from gps
} sys_param_location_t;


typedef struct
{
	jsbool_t en;
	jschar_t manufacture[SYS_PARAM_STRLEN_MAX];
	jsint32_t default_baudrate;
	jsint32_t baudrate;
	jsint32_t rate;
	jsbool_t dgps_en;
	jsbool_t swfilter_en;
} sys_param_gps_t;

typedef struct
{
	sys_param_location_t location;
	sys_param_gps_t gps;
}sys_param_location_setup_t;


typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_location_setup_t setup;
} sys_param_sid0did6_location_config_t;

/******************************************************************/
/* SID:0x00, DID: 7 , junction box setup */
/******************************************************************/
typedef struct
{
	jsint32_t commtype;  // 0: none, 1: can, 2:ssr_uart, 3: rs485
	jsint32_t highspeed_en; // 0: baudrate_default, 1:baudrate_high
	jsint32_t baudrate_default; // ssr_uart:600, rs485:115200, can:500000
	jsint32_t baudrate_high; // ssr_uart:600, rs485:115200, can:500000
	jsint32_t packettype; // 0: shortbinary, 1:byte, 2:binary, 3:json
	jsint32_t tbd0;
	jsint32_t tbd1;
	jsint32_t tbd2;
	jsint32_t tbd3;
}sys_param_jctbox_setup_t;


typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_jctbox_setup_t setup;
} sys_param_sid0did7_jctbox_config_t;

/******************************************************************/
/* SID:0x00, DID: 8 , rs485 protocol setup */
/******************************************************************/
typedef struct
{
	jsint32_t commtype;  // 0: half duplex rs485, 1:full duplex rs485, 2: half duplex uart, full duplex uart
	jsint32_t highspeed_en; // 0: baudrate_default, 1:baudrate_high
	jsint32_t baudrate_default; // 115200
	jsint32_t baudrate_high; // 230400
	jsint32_t packettype; // bit[0]: 0:binary, 1:ascii,  bit[1]: 0:frame_encoding_disable, 1:frame_encoding_enable, bit[2]: 0:json disable, 1:json enable
	jsint32_t tbd0;
	jsint32_t tbd1;
	jsint32_t tbd2;
	jsint32_t tbd3;
}sys_param_rs485_protocol_setup_t;


typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_rs485_protocol_setup_t setup;
} sys_param_sid0did8_rs485_protocol_config_t;


/******************************************************************/
/* SID:0x00, DID: 9 , camera setup */
/******************************************************************/
#define SYS_PARAM_CAMCFG_MAX 2
typedef struct
{
    jsint32_t en;  // 0: camera disable, 1: camera enable
    jsf32_t framerate; // 0.1 ~ 30.0
    jsint32_t imageresolution; // 640_0480, 1920_1080, 1280_0720, 2592_1944, 320_0240
    jsint32_t imageroi; // 0:disable, x*10000+y
    jsint32_t format; // 0:jpg, 1:raw
    jsint32_t brightness; // 0~100
    jsint32_t contrast;   // 0~100
    jsint32_t gain; // 0~100
    jsint32_t exposure_limit; // 0~100
    jsint32_t tbd1;
    jsint32_t tbd2;
    jsint32_t tbd3;
    jsint32_t tbd4;
    jsint32_t tbd5;
    jsint32_t tbd6;
    jsint32_t tbd7;
    jsint32_t tbd8;
}sys_param_cameractrl_setup_t;

typedef struct
{
    jsint32_t count;
    sys_param_cameractrl_setup_t cam[SYS_PARAM_CAMCFG_MAX];
}sys_param_camera_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_camera_setup_t setup;
} sys_param_sid0did9_camera_config_t;


/******************************************************************/
/* SID:0x00, DID: 10 , radar signal processing EOL setup */
/******************************************************************/
#define SYS_PARAM_RSPCFG_RXCHANNEL_MAX	4
#define SYS_PARAM_RSPCFG_AZIBPNUM_MAX	361
#define SYS_PARAM_RSPCFG_AZIBPNUM		121

typedef struct
{
    jsf32_t real;
    jsf32_t imag;
} sys_param_rsp_eol_phasecal_t;
typedef struct
{
    jsbool_t en;
    sys_param_rsp_eol_phasecal_t phasecal[SYS_PARAM_RSPCFG_RXCHANNEL_MAX];
	jsf32_t noise_level_up[SYS_PARAM_RSPCFG_RXCHANNEL_MAX];
	jsf32_t noise_level_dn[SYS_PARAM_RSPCFG_RXCHANNEL_MAX];
	jsf32_t aziangstep;
	jsf32_t aziangmin;
	jsf32_t aziangmax;

	jsf32_t azibeampattern_up[SYS_PARAM_RSPCFG_AZIBPNUM_MAX][SYS_PARAM_RSPCFG_RXCHANNEL_MAX];
	jsf32_t azibeamphase_up[SYS_PARAM_RSPCFG_AZIBPNUM_MAX][SYS_PARAM_RSPCFG_RXCHANNEL_MAX];
	jsf32_t azibeampattern_dn[SYS_PARAM_RSPCFG_AZIBPNUM_MAX][SYS_PARAM_RSPCFG_RXCHANNEL_MAX];
	jsf32_t azibeamphase_dn[SYS_PARAM_RSPCFG_AZIBPNUM_MAX][SYS_PARAM_RSPCFG_RXCHANNEL_MAX];
} sys_param_rsp_eol_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_rsp_eol_setup_t setup;
} sys_param_sid0did10_rsp_eol_config_t;

/******************************************************************/
/* SID:0x00, DID: 11 , radar signal processing installation setup */
/******************************************************************/
typedef struct
{
    jsf32_t height;
    jsf32_t ele_angle;
    jsf32_t azi_angle;
    jsf32_t offset_x;
    jsf32_t offset_y;
} sys_param_rsp_install_setup_t;
typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_rsp_install_setup_t setup;
} sys_param_sid0did11_rsp_install_config_t;


// typedef struct
// {
//     jsint32_t sid;
//     jsint32_t did;
//     struct {
//         struct {} modulation;
//         struct {} preprocessing;
//         struct {} postprocessing;
//         struct {} tracking;
//         struct {} output;
//     } setup;
// }sys_param_sid0did12_rsp_config_t;

/******************************************************************/
/* SID:0x00, DID: 12 , radar rf signal modulation(RSM) setup      */
/******************************************************************/
typedef struct
{
    jsint32_t mode;   // [0:normal, 1:flat_low, 2: flat_mid, 3: flat_high, 4: flat_userfreq, 5:radiation_off]
    jsf32_t userfreq; // (24.05 ~ 24.25)
    jsint32_t scanrate; // 20,25,30
    jsint32_t daq_sampledelay; // us

} sys_param_rsm_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_rsm_setup_t setup;
} sys_param_sid0did12_rsm_config_t;

/******************************************************************/
/* SID:0x00, DID:13  rsp tracking (rsp.trk) setup   */
/******************************************************************/
typedef struct
{
	jsf32_t LongGate1;
	jsf32_t LongGate2;
	jsf32_t LongGate3;
	jsf32_t LongGateByVel_Gain;
	jsf32_t MotorCycle_PowTh;
	jsf32_t MotorCycle_PowTh2;
	jsf32_t MotorCycleByRange_Gain;
	jsint32_t TrackOutFilter; // 0:New + Verified, 1: Verified only, 2: All
	jsf32_t tbd8;
	jsf32_t tbd9;
	jsf32_t tbd10;
	jsf32_t tbd11;
	jsf32_t tbd12;
	jsf32_t tbd13;
	jsf32_t tbd14;
	jsf32_t tbd15;
}sys_param_rsptrk_posttune_t;


typedef struct
{
	jsint32_t s16Pt_New2Vrf;		// 7
	jsint32_t s16Pt_Max;			// 30
	jsint32_t s16Pt_New_Upd;		// 2
	jsint32_t s16Pt_New_Coast;	// 1
	jsint32_t s16Pt_Vrf_Upd;		// 4
	jsint32_t s16Pt_Vrf_Coast;	// 1
	jsf32_t f32Pt_NearRange;
	jsint32_t s16Pt_Vrf_Upd_Near;	// 4
	jsint32_t s16Pt_Vrf_Coast_Near;	// 1
	jsf32_t f32R_GateByEle_W;
	jsf32_t f32V_GateByEle_W;
} sys_param_rsptrk_trktune_t;

typedef struct
{
	sys_param_rsptrk_posttune_t posttune;
	sys_param_rsptrk_trktune_t trktune;
}sys_param_rsptrk_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_rsptrk_setup_t setup;
} sys_param_sid0did13_rsptrk_config_t;



/******************************************************************/
/* SID:0x00, DID:30~39 rfic tx setup  */
/******************************************************************/
typedef struct
{
    jsint32_t rfictx_sel; // [0:bgt24at2, 1:bgt24ar4, 2:bgt24mtr11,3:bgt24atr11,4:bgt24ltr11,5:bgt24mtr12,6:ums24,7:adi24,8:bgt60t2r4,9:bgt60t1r3,10:awr1243]
} sys_param_rfictx_select_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_rfictx_select_t setup;
} sys_param_sid0did30_rfictx_select_config_t;


typedef struct
{
    jsint32_t TX1_A;
    jsbool_t TX1_SPI_ON;
    jsbool_t TX1_EN_DAC;
    jsbool_t TX1_SEL1;
    jsbool_t PH1_SPI_ON;

    jsint32_t TX2_A;
    jsbool_t TX2_SPI_ON;
    jsbool_t TX2_SEL1;
    jsbool_t TX2_EN_DAC;
    jsbool_t PH2_SPI_ON;

    jsint32_t LO_A;
    jsbool_t LO_SPI_ON;
    jsbool_t LO_EN_DAC;
    jsbool_t LO_SEL1;
    jsbool_t LO_SEL0;
    jsbool_t PHLO_SPI_ON;


    jsint32_t VCO_A;
    jsbool_t EN_DAC_VCO;
    jsbool_t EN_VCO;
    jsbool_t EN_BUF2;
    jsbool_t EN_BUF1;

    jsbool_t PH_SEL1;

    jsbool_t AMUX1_SEL1;
    jsbool_t AMUX1_SEL0;

    jsbool_t AMUX2_SEL2;
    jsbool_t AMUX2_SEL1;
    jsbool_t AMUX2_SEL0;

    jsbool_t AMUX3_SEL1;
    jsbool_t AMUX3_SEL0;


    jsbool_t EN_DIV;
    jsbool_t SEL_DIVBUF;
    jsbool_t SEL_DIV;
    jsbool_t DIS_DIVOUT;
} sys_param_rfictx_bgt24at2_setup_t;
typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_rfictx_bgt24at2_setup_t setup;
} sys_param_sid0did31_rfictx_bgt24at2_config_t;

/******************************************************************/
/* SID:0x00, DID:40~49 rfic rx setup  */
/******************************************************************/
typedef struct
{
    jsint32_t rficrx_sel; // [0:bgt24at2, 1:bgt24ar4, 1:bgt24ar4, 2:bgt24mtr11,3:bgt24atr11,4:bgt24ltr11,5:bgt24mtr12,6:ums24,7:adi24,8:bgt60t2r4,9:bgt60t1r3,10:awr1243]
} sys_param_rficrx_select_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_rficrx_select_t setup;
} sys_param_sid0did40_rficrx_select_config_t;

typedef struct
{
    jsbool_t EN_12;
    jsbool_t LG1_12_6db;
    jsbool_t HG1_12_12db;
    jsbool_t LG2_12_6db;
    jsbool_t MG2_12_12db;
    jsbool_t HG2_12_18db;
    jsbool_t EN_34;
    jsbool_t LG1_34_6db;
    jsbool_t HG1_34_12db;
    jsbool_t LG2_34_6db;
    jsbool_t MG2_34_12db;
    jsbool_t HG2_34_18db;

    jsbool_t IFTEST4; // Activates test signal for IF channel 4
    jsbool_t IFTEST3; // Activates test signal for IF channel 3
    jsbool_t IFTEST2; // Activates test signal for IF channel 2
    jsbool_t IFTEST1; // Activates test signal for IF channel 1
    jsbool_t PC1;     // Test bit
    jsbool_t PC2;     // Test bit
    jsbool_t EN_RF14; // Test bit
    jsbool_t EN_RF23; // Test bit
    jsbool_t DIS_DIV; // Test bit
    jsbool_t DIS_LO;  // Test bit

    jsbool_t AMUX_SEL0;    // Sets analog multiplexer
    jsbool_t AMUX_SEL1;    // Sets analog multiplexer
    jsbool_t AMUX_SEL2;    // Sets analog multiplexer
    jsbool_t SAT_FLAG_HIZ; // Sets sat flag output into high impedance state and enables
                           // multiplexer output to be activ

    jsbool_t SENSOR_SEL0; // Selects power sensor signal
    jsbool_t SENSOR_SEL1; // Selects power sensor signal

    jsbool_t DCO_0; // Test bit
    jsbool_t DCO_1; // Test bit
    jsbool_t DCO_2; // Test bit
    jsbool_t DCO_3; // Test bit
} sys_param_rficrx_bgt24ar4_setup_t;


typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_rficrx_bgt24ar4_setup_t setup;
} sys_param_sid0did41_rficrx_bgt24ar4_config_t;


/******************************************************************/
/* SID:0x00, DID:50~59 rfic pll setup  */
/******************************************************************/
typedef struct
{
    jsint32_t pll_sel; // [0:adf4158, 1:adf4159, 2:lmx2491, 3:lmx2492]
} sys_param_pll_select_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_pll_select_t setup;
} sys_param_sid0did50_pll_select_config_t;


typedef struct
{
    jsint32_t regset; // 0:normal, 1:flat_low, 2:flat_mid, 3:flat_high
    jsint32_t cp;
} sys_param_pll_lmx2491_setup_t;


typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_pll_lmx2491_setup_t setup;
} sys_param_sid0did51_pll_lmx2491_config_t;


/******************************************************************/
/* SID:0x00, DID:60 rfm adc select setup  */
/******************************************************************/
#define SYS_PARAM_ADC_CH_MAX 4
typedef struct
{
    jsint32_t adc_sel; // 0:adar7251, 1:afe5401, 2:max11043
} sys_param_adc_select_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_adc_select_t setup;
} sys_param_sid0did60_adc_select_config_t;

/******************************************************************/
/* SID:0x00, DID:61 rfm adc adi adar7251 setup  */
/******************************************************************/
typedef struct
{
    jsint32_t ROUTING[SYS_PARAM_ADC_CH_MAX];  // [0:SRC_ADC_Disabled, 1:SRC_LNA_PGA_EQ_Path, 2:SRC_LNA_PGA_Path_Bypass_EQ, 3:SRC_Bypass_LNA_PGA_EQ, 4:SRC_Swap_Channels, 5:SRC_Use_Test_Pin]
    jsint32_t LNA_GAIN[SYS_PARAM_ADC_CH_MAX]; // [0:x2, 1:x4, 2:x8, 3:x16]
    jsint32_t PGA_GAIN[SYS_PARAM_ADC_CH_MAX]; //[0:1.4dB, 1:2.8dB,  3:5.6dB, 4:11.2dB]
    jsint32_t EQ_CAP;                         //# EQ HPF CutOffFreq, [0:54KHz, 1:45KHz, 2:37KHz, 3:32KHz]
} sys_param_adc_adar7251_setup_t;


typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_adc_adar7251_setup_t setup;
} sys_param_sid0did61_adc_adar7251_config_t;


/******************************************************************/
/* SID:0x00, DID:62 rfm adc maxim max11043 setup  */
/******************************************************************/
typedef struct
{
    jsint32_t analog_filtermode[SYS_PARAM_ADC_CH_MAX]; // [0:LPF_GAIN8X, 1:EQ, 2:LPF_GAIN16, 3:reserved, 4:bypass]
    jsint32_t gain[SYS_PARAM_ADC_CH_MAX];              //[0:1X, 1:2X, 2:4X]
    jsint32_t digtal_filtermode[SYS_PARAM_ADC_CH_MAX]; // biquad digital filter mode, [0:EQ, 1:LPF]
    jsf32_t fine_gain[SYS_PARAM_ADC_CH_MAX];           // (0.25~3.999)
    jsint32_t inputbias[SYS_PARAM_ADC_CH_MAX];         // [0:33%, 1:35%, 2:38%, 3:40%, 4:42%, 5:44%, 6:46%, 7:48%, 8:50%, 9:52%, 10:54%, 11:56%, 12:58%, 13:60%, 14:62%, 15:65%]
} sys_param_adc_max11043_setup_t;


typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_adc_max11043_setup_t setup;
} sys_param_sid0did62_adc_max11043_config_t;



/******************************************************************/
/* SID:0x00, DID:200~299 Application Service setup  */
/******************************************************************/
/******************************************************************/
/* SID:0x00, DID:200 application packet setup  */
/******************************************************************/
#define SYS_PARAM_APP_PACKET_MAX 4
typedef struct
{
	jschar_t server_ip[SYS_PARAM_STRLEN_MAX];
	jsint32_t port_num;
	jsint32_t port_en;
	jsbool_t client_mode_en;	// 0:server, 1:client
	jsbool_t pid_simple_en;
	jsbool_t pid_compress_en;
    jsbool_t pid_status_en;
    jsbool_t pid_object_en;
    jsbool_t pid_track_en;
    jsbool_t pid_image_en;
    jsbool_t pid_imagsp_en;
    jsbool_t pid_logger_en;
    jsbool_t pid_canlog_en;
    jsbool_t pid_sensor_en;
    jsbool_t pid_app_its_en;
    jsbool_t pid_app_vf_en;
    jsbool_t pid_app_fcw_en;
    jsbool_t pid_app_lm_en;


}sys_param_app_packet_t;
typedef struct
{
	jsint32_t count;
	sys_param_app_packet_t ports[SYS_PARAM_APP_PACKET_MAX];
}sys_param_app_packet_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_app_packet_setup_t setup;
}sys_param_sid0did200_app_packet_config_t;




/******************************************************************/
/* SID:0x06, DID:0  CAN Communication Setup                      */
/******************************************************************/
#define CANDRV_CHANNEL_MAX 2
#define CANDRV_ACCEPTFILTER_COUNT 4
typedef struct
{
    jsint32_t cantype;     // 0:CAN, 1:CANFD
    jsint32_t baudrate;     // 500 kbps
    jsint32_t baudratefd;	// 2000 kbps
    jsint32_t samplepoint; // 75%
    jsbool_t listenonlymode_en;  // 0:normal, 1:listen only
    jsbool_t acceptfilter_en[CANDRV_ACCEPTFILTER_COUNT];
    jsint32_t acceptfilter_id[CANDRV_ACCEPTFILTER_COUNT];
    jsint32_t acceptfilter_mask[CANDRV_ACCEPTFILTER_COUNT];
} sys_param_candrv_channel_setup_t;

typedef struct
{
    jsint32_t channel_count; //
    sys_param_candrv_channel_setup_t channel[CANDRV_CHANNEL_MAX];
} sys_param_candrv_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_candrv_setup_t setup;
} sys_param_sid6did0_candrv_config_t;


/******************************************************************/
/* SID:0x06, DID:1  CAN RX Signal Setup                              */
/******************************************************************/
#define CANSIGNAL_MAX 16 // vehicle speed, wheelsped fl fr rl rr, yaw, sas, g
typedef struct
{
    jsbool_t en;
    jsint32_t sigid;
    jsint32_t msgid;
    jschar_t name[SYS_PARAM_STRLEN_MAX];
	jsint8_t type; // 'U':unsigned, 'S':signed, 'd':double, 'f':float
	jsint8_t byteorder; // 'M': Motorola, 'I':Intel
    jsint32_t bitpos;
    jsint32_t length;
    jsf32_t factor;
    jsf32_t offset;
    jsf32_t min;
    jsf32_t max;
    jschar_t unit[SYS_PARAM_STRLEN_MIN];
} sys_param_cansignal_t;


typedef struct
{
    sys_param_cansignal_t signal[CANSIGNAL_MAX]; // yaw sas g
} sys_param_cansignal_setup_t;


typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_cansignal_setup_t setup;
} sys_param_sid6did1_cansignal_config_t;


/******************************************************************/
/* SID:0x06, DID:2  CAN TX Message Setup                          */
/******************************************************************/
typedef struct
{
    jsbool_t en;
    jsint32_t start_id;
    jsint32_t count;
} sys_param_can_txmsg_t;


typedef struct
{
    sys_param_can_txmsg_t status;
    sys_param_can_txmsg_t object;
    sys_param_can_txmsg_t track;
    sys_param_can_txmsg_t extioctrl;
} sys_param_cantxmsg_setup_t;


typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_cantxmsg_setup_t setup;
} sys_param_sid6did2_cantxmsg_config_t;


/******************************************************************/
/* SID:0x07, DID:0  Filesystem Setup                              */
/******************************************************************/
typedef struct
{
	jsbool_t isformatted;
	jsint32_t lastfilenumber;
	jsbool_t mmc_write_enable;
}sys_param_filesystem_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_filesystem_setup_t setup;
} sys_param_sid7did0_filesystem_config_t;


/******************************************************************/
/* PID: 0, Periodic Status Data  */
/******************************************************************/
typedef struct
{
	jsf64_t timestamp_s;
	jsint64_t rsp_timestamp_us;
	jsint64_t net_timestamp_us;
	jsf32_t   rsp_cycletime;
}sys_param_status_timestamp_t;


typedef struct
{
    jsf32_t yaw;
    jsf32_t roll;
    jsf32_t pitch;
    jsf32_t altitude;
} sys_param_status_data_position_t;

typedef struct
{
    jsf32_t temp_core;
    jsf32_t temp_rfm;
    jsf32_t vin;
    jsf32_t v5;
    jsf32_t v1_5;
    jsf32_t v1_0;
} sys_param_status_data_ecuinfo_t;

typedef struct
{
    jsbool_t status;
    jschar_t data[1024];
} sys_param_status_data_gps_t;


typedef struct
{
    jsint32_t scanindex;
    sys_param_status_timestamp_t timestamp;
    sys_param_status_data_position_t position;
    sys_param_status_data_ecuinfo_t ecuinfo;
    sys_param_status_data_gps_t gps;
} sys_param_pid0_status_data_t;


/******************************************************************/
/* SID: 8, DID: 0 , ITS application setup */
/******************************************************************/
#define SYS_PARAM_ITS_CONFIG_LANECOUNT_MAX 4
#define SYS_PARAM_ITS_CONFIG_LANESTEP_MAX 50
#define SYS_PARAM_ITS_CONFIG_ZONESTEP_MAX 100
#define SYS_PARAM_ITS_CONFIG_BLACKOUT_AREA_MAX 10
#define SYS_PARAM_ITS_CONFIG_PERIOD_COUNT_MAX 5
#define SYS_PARAM_ITS_CONFIG_TIDLIST_MAX 32

typedef struct
{
    jschar_t timeunit[SYS_PARAM_STRLEN_MIN];
    jsint32_t updatetime;
} sys_param_its_setup_timeschedule_t;
typedef struct
{
    jsf32_t x[SYS_PARAM_ITS_CONFIG_LANESTEP_MAX];
    jsf32_t y[SYS_PARAM_ITS_CONFIG_LANESTEP_MAX];
} sys_param_its_setup_laneinfo_lane_t;
typedef struct
{
    jsf32_t x[SYS_PARAM_ITS_CONFIG_ZONESTEP_MAX];
    jsf32_t y[SYS_PARAM_ITS_CONFIG_ZONESTEP_MAX];
} sys_param_its_setup_zone_t;
typedef struct
{
    jsf32_t x[SYS_PARAM_ITS_CONFIG_ZONESTEP_MAX];
    jsf32_t y[SYS_PARAM_ITS_CONFIG_ZONESTEP_MAX];
    jsf32_t width;
    jsf32_t midoffset;
} sys_param_its_setup_hotspotzone_t;
typedef struct
{
    jsint32_t stepcount;
    sys_param_its_setup_laneinfo_lane_t left;
    sys_param_its_setup_hotspotzone_t hotspotzone;
    sys_param_its_setup_zone_t trackingzone;
    sys_param_its_setup_laneinfo_lane_t right;
    jsint32_t number;
} sys_param_its_setup_laneinfo_t;

typedef struct
{
    jsf32_t x[2];
    jsf32_t y[2];
    jsf32_t t;
} sys_param_its_setup_area_t;

typedef struct
{
    jsint32_t count;
    sys_param_its_setup_area_t area[SYS_PARAM_ITS_CONFIG_BLACKOUT_AREA_MAX];
} sys_param_its_setup_blackout_t;

typedef struct
{
    jsf32_t high_speedlimit_kph;
    jsf32_t low_speedlimit_kph;
    jsint32_t speedlimit_compensation_percentage;
} sys_param_its_setup_speedlimit_t;

typedef struct
{
    jsbool_t camera_on;
    jsbool_t trackingzone_view_on;
    jsbool_t autoalignment_on;
    jsint32_t num_track_autoalignment;
} sys_param_its_setup_misc_t;

typedef struct
{
    sys_param_its_setup_timeschedule_t timeschedule;
    sys_param_its_setup_misc_t misc;
    jsf32_t middlelane;
    jsint32_t uplaneangle;
    jsint32_t downlaneangle;
    jsint32_t lanecount;
    sys_param_its_setup_speedlimit_t speedlimit;
    sys_param_its_setup_laneinfo_t laneinfo[SYS_PARAM_ITS_CONFIG_LANECOUNT_MAX];
    sys_param_its_setup_blackout_t blackout;
} sys_param_its_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    jschar_t description[SYS_PARAM_STRLEN_MAX];
    sys_param_its_setup_t setup;
} sys_param_sid8did0_its_config_t;


/******************************************************************/
/* SID: 8, DID: 1 , ITS application for relay setup */
/******************************************************************/
#define SYS_PARAM_ITS_RELAYCNT_MAX 2
typedef struct
{
    jsint32_t relay_cnt;                                                   //:2,
    jsint32_t relay_enable[SYS_PARAM_ITS_RELAYCNT_MAX];                    //:[0,0],
    jschar_t relay_type[SYS_PARAM_ITS_RELAYCNT_MAX][SYS_PARAM_STRLEN_MIN]; //["NO","NO"], // "NO" or "NC"
    jsint32_t relay_on_time_ms[SYS_PARAM_ITS_RELAYCNT_MAX];                //: [10,20], // 0~60000ms
    jsint32_t relay_off_time_ms[SYS_PARAM_ITS_RELAYCNT_MAX];               // : [5,5]
    jsint32_t relay_adjust_time_ms[SYS_PARAM_ITS_RELAYCNT_MAX];
    jsint32_t relay_lowbound_time_ms[SYS_PARAM_ITS_RELAYCNT_MAX];
    jsint32_t relay_highbound_time_ms[SYS_PARAM_ITS_RELAYCNT_MAX];
    jsint32_t relay_on_event_type[SYS_PARAM_ITS_RELAYCNT_MAX]; //:[0,0], // 0:normal, 1:speed over, 2:speed lower, 3:error
} sys_param_its_relay_t;

typedef struct
{
    sys_param_its_relay_t relay;
} sys_param_its_device_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    jschar_t description[SYS_PARAM_STRLEN_MAX];
    sys_param_its_device_setup_t setup;
} sys_param_sid8did1_its_relay_config_t;

/******************************************************************/
/* SID: 8, DID: 2 , ITS auto alignment setup */
/******************************************************************/
typedef struct
{
    jsbool_t autoalignment_on;
    jsint32_t num_track_autoalignment;
    jsint32_t status_autoalignment;
    jsf32_t angle_aligned;
} sys_param_its_alignment_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    jschar_t description[SYS_PARAM_STRLEN_MAX];
    sys_param_its_alignment_setup_t setup;
} sys_param_sid8did2_its_align_config_t;

/******************************************************************/
/* SID: 8, DID: 10 , ITS application for test parameter setup */
/******************************************************************/

typedef struct
{
    jsf32_t high_speedlimit_tolerance_percentage; // 0.0
    jsf32_t low_speedlimit_tolerance_percentage;  // 0.0
} sys_param_its_testmode_speedlimit_t;

typedef struct
{
    jsbool_t trigger_en[SYS_PARAM_ITS_RELAYCNT_MAX];          // [0,0]
    jsint32_t trigger_period[SYS_PARAM_ITS_RELAYCNT_MAX];     // [1000,1000]
    jsf32_t trigger_ttlc_time_ms[SYS_PARAM_ITS_RELAYCNT_MAX]; // [45,45]
} sys_param_its_testmode_trigger_t;

typedef struct
{
    jsbool_t modlane_en[SYS_PARAM_ITS_RELAYCNT_MAX];                       // [0,0]
    jsf32_t modlane_offset_hotspotzone_y[SYS_PARAM_ITS_RELAYCNT_MAX];      // [0,0]
    jsf32_t modlane_offset_hotspotzone_width[SYS_PARAM_ITS_RELAYCNT_MAX];  // [0,0]
    jsf32_t modlane_offset_hotspotzone_offset[SYS_PARAM_ITS_RELAYCNT_MAX]; // [0,0]
} sys_param_its_testmode_hotspotzone_t;

typedef struct
{
    jsint32_t skip_image_count;
} sys_param_its_testmode_image_t;

typedef struct
{
    jsf32_t trackzone_xrange;
    jsbool_t en_lanechange;
    jsf32_t low_exclude_speed;
} sys_param_its_testmode_misc_t;

typedef struct
{
    sys_param_its_testmode_speedlimit_t speedlimit_tolerance;
    sys_param_its_testmode_trigger_t trigger;
    sys_param_its_testmode_hotspotzone_t modlane;
    sys_param_its_testmode_image_t imagetest;
    sys_param_its_testmode_misc_t misc;
} sys_param_its_testmode_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    jschar_t description[SYS_PARAM_STRLEN_MAX];
    sys_param_its_testmode_setup_t setup;
} sys_param_sid8did10_its_testmode_config_t;


/******************************************************************/
/* PID: 8, ITS data  */
/******************************************************************/
typedef struct
{
    jsint32_t cnt;
    jsint32_t num[SYS_PARAM_ITS_CONFIG_LANECOUNT_MAX];
    jsint32_t period[SYS_PARAM_ITS_CONFIG_PERIOD_COUNT_MAX];
} sys_param_its_data_lane_t;

typedef struct
{
    jsint32_t ts;
    jsint32_t diff[SYS_PARAM_ITS_CONFIG_LANECOUNT_MAX];
    jsint32_t acc[SYS_PARAM_ITS_CONFIG_PERIOD_COUNT_MAX][SYS_PARAM_ITS_CONFIG_LANECOUNT_MAX];
    jsint32_t lc[SYS_PARAM_ITS_CONFIG_LANECOUNT_MAX];
    jsint32_t acclc[SYS_PARAM_ITS_CONFIG_PERIOD_COUNT_MAX][SYS_PARAM_ITS_CONFIG_LANECOUNT_MAX];
} sys_param_its_data_count_t;

typedef struct
{
    jsf32_t average[SYS_PARAM_ITS_CONFIG_PERIOD_COUNT_MAX][SYS_PARAM_ITS_CONFIG_LANECOUNT_MAX];
    jsf32_t min[SYS_PARAM_ITS_CONFIG_PERIOD_COUNT_MAX][SYS_PARAM_ITS_CONFIG_LANECOUNT_MAX];
    jsf32_t max[SYS_PARAM_ITS_CONFIG_PERIOD_COUNT_MAX][SYS_PARAM_ITS_CONFIG_LANECOUNT_MAX];
} sys_param_its_data_speed_t;

typedef struct
{
    jsint32_t tid[SYS_PARAM_ITS_CONFIG_TIDLIST_MAX];
    jsint32_t lane[SYS_PARAM_ITS_CONFIG_TIDLIST_MAX];
} sys_param_its_data_event_tidlane_t;

typedef struct
{
    jsint32_t tid[SYS_PARAM_ITS_CONFIG_TIDLIST_MAX];
} sys_param_its_data_event_tidlane2_t;

typedef struct
{
    sys_param_its_data_event_tidlane_t abnomal;    // abnomal driving target id and lane list
    sys_param_its_data_event_tidlane_t reverse;    // reverse driving target id  and lane list
    sys_param_its_data_event_tidlane_t speedlimit; // overspeed driving target id  and lane list
    jschar_t cs[SYS_PARAM_STRLEN_MIN];
    sys_param_its_data_event_tidlane2_t notvehicle; // none vehicle
} sys_param_its_data_event_t;

typedef struct
{
    sys_param_its_data_lane_t lane;
    sys_param_its_data_count_t count;
    sys_param_its_data_speed_t speed;
    sys_param_its_data_event_t event;
} sys_param_pid8_its_data_t;


/******************************************************************/
/* SID: 9, DID: 0 , Virtual Fence reflector setup */
/******************************************************************/
#define SYS_PARAM_VF_DATACNT_MAX 25
#define SYS_PARAM_VF_RELAYCNT_MAX 4
typedef struct
{
    jschar_t reflector_type[SYS_PARAM_STRLEN_MAX]; //:
    jsf32_t reflector_distance;                    //:100.0,  // meter
    jsf32_t reflector_radius;                      //: 2.0      // meter
} sys_param_vf_reflector_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_vf_reflector_setup_t setup;
} sys_param_sid9did0_vf_reflector_config_t;


/******************************************************************/
/* SID: 9, DID: 1 , Virtual Fence destination server setup */
/******************************************************************/
typedef struct
{
    jschar_t server_ip[SYS_PARAM_STRLEN_MAX];
    jsint32_t server_port;             //:4564,
    jsint32_t server_access_timeout;   //: 10000, // milisecond
    jsint32_t server_access_retry_cnt; //: 0,
    jsint32_t server_sendstack_size;   //:
    jsint32_t rs485_access_timeout;    //: 1000, // milisecond
    jsint32_t rs485_access_retry_cnt;  //: 0
} sys_param_vf_server_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;

    sys_param_vf_server_setup_t setup;
} sys_param_sid9did1_vf_server_config_t;

/******************************************************************/
/* SID: 9, DID: 2 , Virtual Fence relay setup */
/******************************************************************/
typedef struct
{
    jsint32_t relay_cnt;                               //:4,
    jsint32_t relay_enable[SYS_PARAM_VF_RELAYCNT_MAX]; //:[0,0,0,0],
    jschar_t relay_type[SYS_PARAM_VF_RELAYCNT_MAX]
                       [SYS_PARAM_STRLEN_MIN];                //["NO","NO","NO","NO"],
                                                              //// "NO" or "NC"
    jsint32_t relay_on_time_ms[SYS_PARAM_VF_RELAYCNT_MAX];    //: [0,0,0,0], // 0~60000ms
    jsint32_t relay_on_event_type[SYS_PARAM_VF_RELAYCNT_MAX]; //:[0,0,0,0], // 0:normal,
                                                              // 1:caution,
                                                              // 2:warning, 3:error
} sys_param_vf_relay_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_vf_relay_setup_t setup;
} sys_param_sid9did2_vf_relay_config_t;

/******************************************************************/
/* SID: 9, DID: 3 , UI setup */
/******************************************************************/
typedef struct
{
    jsf32_t th_normal;  //:100,
    jsf32_t th_caution; //:80,
    jsf32_t th_warning; //:68,
    jsf32_t marker;     //:130
} sys_param_vf_ui_setup_t;
typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_vf_ui_setup_t setup;
} sys_param_sid9did3_vf_ui_config_t;


/******************************************************************/
/* PID: 9, Virtual Fence data  */
/******************************************************************/

typedef struct
{
    jsint32_t cnt;                         // count, integer, 1~
    jsf32_t prd;                           // period, second unit
    jsf32_t dat[SYS_PARAM_VF_DATACNT_MAX]; //:[120,121,128,123], // Virtual Fence RCS data per
                                           // sample,
                                           // unit : dBm, resolution : 1dBm
    jsf32_t std[SYS_PARAM_VF_DATACNT_MAX]; //:[2,2,2,2], // Virtual Fence RCS standard deviation
                                           // data
                                           // per
    // sample, unit : dBm, resolution : 1 dBm
    jsint32_t war[SYS_PARAM_VF_DATACNT_MAX]; //:[0,0,1,1], // warning or caution result per
                                             // sample , 0:No
                                             // warning, 1:Warning
    jsint32_t det[SYS_PARAM_VF_DATACNT_MAX]; //:[0,0,1,0], // danger or detection result per
                                             // sample, 0:No
                                             // detection, 1:detection
    jsint32_t sw[SYS_PARAM_VF_DATACNT_MAX];  //:[0,0,0,0] // Contact switch signal status, 0:off,
                                             // 1:on
} sys_param_pid9_vf_data_t;



/******************************************************************/
/* SID: 10, DID: 0 , FCW Forward Collision Warning application setup */
/******************************************************************/
typedef struct
{
    jsint32_t vehicle_type; // 0:J1939bus, 1:HKMC1G, 2: Toyota pickup
    jsbool_t startup_light_en;  // 1, check for junctionbox initial check
    jsint32_t startup_light_ontime; // 3000
    jsbool_t alert_led_en;
    jsbool_t alert_spk_en;
    jsbool_t alert_ssr_en;
    jsint32_t alert_ledcolor_caution;
    jsint32_t alert_ledcolor_warning;
    jsint32_t alert_ledcolor_normal;
    jsint32_t alert_blink_period;   // 300ms
    jsint32_t alert_update_period;  // 200ms
    jsint32_t alert_blocking_period; // 140ms
    jsf32_t vehiclespeed_adj_ratio;  // 1.0
    jsf32_t ttc_low_sec;            // 1.7s
    jsf32_t ttc_high_sec;
    jsf32_t ttc_egospeed_low_kph;
    jsf32_t ttc_egospeed_high_kph;
    jsf32_t ttc_level1_ratio;
    jsf32_t ttc_level2_ratio;
    jsf32_t lane_left_m;      // > -1.5
    jsf32_t lane_right_m;     // < 1.5
    jsf32_t lane_range_m;     // < 30m
    jsf32_t egospeed_min_kph;   // > 2.0m/s
    jsf32_t oncomming_th_kph; //   > -1.5m/s
}sys_param_fcw_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_fcw_setup_t setup;
} sys_param_sid10did0_fcw_config_t;
/******************************************************************/
/* SID: 10, DID: 1 , FCW Forward Collision Warning application test */
/******************************************************************/
typedef struct
{
    jsbool_t test_fcw_event_level1;
    jsbool_t test_fcw_event_level2;
    jsbool_t test_jctbox_led;
    jsbool_t test_jctbox_spk;
    jsbool_t test_jctbox_ssr;
    jsbool_t test_tbd0;
    jsbool_t test_tbd1;
    jsbool_t test_tbd2;
    jsbool_t test_tbd3;
    jsbool_t test_tbd4;
}sys_param_fcwtest_setup_t;

typedef struct
{
    jsint32_t sid;
    jsint32_t did;
    sys_param_fcwtest_setup_t setup;
} sys_param_sid10did1_fcwtest_config_t;


/******************************************************************/
/* JunctionBox Control Data                                       */
/******************************************************************/
typedef struct
{
	jsint32_t r;
	jsint32_t g;
	jsint32_t b;
	jsint32_t spk;
	jsint32_t ssra;
	jsint32_t ssrb;
}sys_param_junctionbox_param_t;
typedef struct
{
	jschar_t cmd[SYS_PARAM_STRLEN_MAX];
	sys_param_junctionbox_param_t param;
}sys_param_junctionbox_ctrl_t;


/******************************************************************/
/* AppData Server Request Information Data                        */
/*     sys_param_system_status_t                                  */
/******************************************************************/
typedef struct
{
    /* device unique ID */
    jschar_t devuid[SYS_PARAM_STRLEN_MAX];
    /* device serial number */
    jschar_t serialnumber[SYS_PARAM_STRLEN_MAX];
    /* device sw informations */
    jschar_t swappname[SYS_PARAM_STRLEN_MAX];
    jschar_t swversion[SYS_PARAM_STRLEN_MAX];
    jsint32_t swdate;
    jsint32_t swtime;


    sys_param_sid0did0_systembase_config_t sid0did0_systembase_config;
    sys_param_sid0did1_datetime_config_t sid0did1_datetime_config;
    sys_param_sid0did2_security_config_t sid0did2_security_config;
    sys_param_sid0did4_infra_config_t sid0did4_infra_config;
    sys_param_sid0did5_serialnumber_config_t sid0did5_serialnumber_config;
    sys_param_sid0did6_location_config_t sid0did6_location_config;
    sys_param_sid0did8_rs485_protocol_config_t sid0did8_rs485_protocol_config;
    sys_param_sid0did10_rsp_eol_config_t sid0did10_rsp_eol_config;
    sys_param_sid0did11_rsp_install_config_t sid0did11_rsp_install_config;
    sys_param_sid0did12_rsm_config_t sid0did12_rsm_config;
    sys_param_sid0did13_rsptrk_config_t sid0did13_rsptrk_config;
    sys_param_sid0did200_app_packet_config_t sid0did200_app_packet_config;
    sys_param_sid8did0_its_config_t sid8did0_its_config;
    sys_param_sid8did1_its_relay_config_t sid8did1_its_relay_config;
    sys_param_sid8did2_its_align_config_t sid8did2_its_align_config;
    sys_param_sid8did10_its_testmode_config_t sid8did10_its_testmode_config;
}sys_param_system_status_t;


/******************************************************************/
/* Packing Config data set  */
/******************************************************************/

typedef struct
{
    jsint32_t data_start_marker;
    jsint32_t param_version;
    jschar_t guidstr[36];
    sys_param_sid0did0_systembase_config_t sid0did0_systembase_config;
    sys_param_sid0did1_datetime_config_t sid0did1_datetime_config;
    sys_param_sid0did2_security_config_t sid0did2_security_config;
    sys_param_sid0did3_network_config_t sid0did3_network_config;
    sys_param_sid0did4_infra_config_t sid0did4_infra_config;
    sys_param_sid0did5_serialnumber_config_t sid0did5_serialnumber_config;
    sys_param_sid0did6_location_config_t sid0did6_location_config;
    sys_param_sid0did7_jctbox_config_t sid0did7_jctbox_config;
    sys_param_sid0did8_rs485_protocol_config_t sid0did8_rs485_protocol_config;
    sys_param_sid0did9_camera_config_t sid0did9_camera_config;
    sys_param_sid0did10_rsp_eol_config_t sid0did10_rsp_eol_config;
    sys_param_sid0did11_rsp_install_config_t sid0did11_rsp_install_config;
    sys_param_sid0did12_rsm_config_t sid0did12_rsm_config;
    sys_param_sid0did13_rsptrk_config_t sid0did13_rsptrk_config;
    //sys_param_sid0did20_radar_info_t sid0did20_radar_info;

    sys_param_sid0did30_rfictx_select_config_t sid0did30_rfictx_select_config;
    sys_param_sid0did31_rfictx_bgt24at2_config_t sid0did31_rfictx_bgt24at2_config;

    sys_param_sid0did40_rficrx_select_config_t sid0did40_rficrx_select_config;
    sys_param_sid0did41_rficrx_bgt24ar4_config_t sid0did41_rficrx_bgt24ar4_config;

    sys_param_sid0did50_pll_select_config_t sid0did50_pll_select_config;
    sys_param_sid0did51_pll_lmx2491_config_t sid0did51_pll_lmx2491_config;

    sys_param_sid0did60_adc_select_config_t sid0did60_adc_select_config;
    sys_param_sid0did61_adc_adar7251_config_t sid0did61_adc_adar7251_config;
    sys_param_sid0did62_adc_max11043_config_t sid0did62_adc_max11043_config;

    sys_param_sid0did200_app_packet_config_t sid0did200_app_packet_config;

    sys_param_sid6did0_candrv_config_t sid6did0_candrv_config;
    sys_param_sid6did1_cansignal_config_t sid6did1_cansignal_config;
    sys_param_sid6did2_cantxmsg_config_t sid6did2_cantxmsg_config;

    sys_param_sid7did0_filesystem_config_t sid7did0_filesystem_config;

    sys_param_sid8did0_its_config_t sid8did0_its_config;
    sys_param_sid8did1_its_relay_config_t sid8did1_its_relay_config;
    sys_param_sid8did2_its_align_config_t sid8did2_its_align_config;
    sys_param_sid8did10_its_testmode_config_t sid8did10_its_testmode_config;
    sys_param_sid9did0_vf_reflector_config_t sid9did0_vf_reflector_config;
    sys_param_sid9did1_vf_server_config_t sid9did1_vf_server_config;
    sys_param_sid9did2_vf_relay_config_t sid9did2_vf_relay_config;
    sys_param_sid9did3_vf_ui_config_t sid9did3_vf_ui_config;
    sys_param_sid10did0_fcw_config_t sid10did0_fcw_config;
    sys_param_sid10did1_fcwtest_config_t sid10did1_fcwtest_config;
    jsint32_t data_end_marker;
    jsint32_t data_end_marker1;
    jsint32_t data_end_marker2;
} sys_param_sidxdidx_configinfo_packing_t;

//    extern sys_param_array_test_t sys_param_array_test;
//    extern sys_param_array_test_t sys_param_array_test_default;
extern sys_param_sidxdidx_configinfo_packing_t sys_param_sidxdidx_configinfo_packing;
extern sys_param_sidxdidx_configinfo_packing_t sys_param_sidxdidx_configinfo_packing_default;
extern sys_param_sidxdidx_configinfo_packing_t sys_param_sidxdidx_configinfo_packing_factory;

extern const sys_param_pid8_its_data_t sys_param_pid8_its_data_default;

extern sys_param_pid0_status_data_t sys_param_pid0_status_data;
extern sys_param_pid8_its_data_t sys_param_pid8_its_data;
extern sys_param_pid9_vf_data_t sys_param_pid9_vf_data;



#ifdef __cplusplus
}
#endif


#endif // SYS_PARAM_JSONTYPE_H__
