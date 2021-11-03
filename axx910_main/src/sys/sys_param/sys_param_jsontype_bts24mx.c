/************************************************************************
| Project Name: sys_param_jsontype
|    File Name: sys_param_jsontype.c
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
| 2018.07.19   0.0f   SKJ   Creation;
|***********************************************************************/

#include "bts.h"
#include "sys_param_jsontype.h"


#include "sys_config.h"
//#ifndef WIN32
#if !defined(WIN32) && !defined(LINUX)
#include "can_sig.h"
#else
typedef enum
{
	can_sig_id_vehicle_speed,
	can_sig_id_wheel_speed_fl,
	can_sig_id_wheel_speed_fr,
	can_sig_id_wheel_speed_rl,
	can_sig_id_wheel_speed_rr,
	can_sig_id_steerangle,
	can_sig_id_steeranglespeed,
	can_sig_id_yawrate,
	can_sig_id_longaccel,
	can_sig_id_lataccel,
}can_sig_id_t;
#endif

/******************************************************************/
/* Packing Config data set  */
/******************************************************************/

sys_param_sidxdidx_configinfo_packing_t sys_param_sidxdidx_configinfo_packing_default = {
    /*.data_start_marker = */ 0x11AAAA11,
    /*.param_version = */ SYS_PARAMETER_VERSION,// 50, // vietnam release version is 50
    /*.guidstr = */ "",
    /******************************************************************/
    /* SID:0x00, DID:0x00 , system base setup */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did0_system_base.h"

    /******************************************************************/
    /* SID:0x00, DID:0x01 , datetime setup */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did1_datetime.h"


    /******************************************************************/
    /* SID:0x00, DID:0x02 , security setup */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did2_security.h"

    /******************************************************************/
    /* SID:0x00, DID:0x03 , network setup */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did3_network.h"

    /******************************************************************/
    /* SID:0x00, DID:0x04 , infra setup                          */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did4_infra.h"

    /******************************************************************/
    /* SID:0x00, DID:0x05 , serial number setup                       */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did5_serialnumber.h"


    /******************************************************************/
    /* SID:0x00, DID:0x06 , location setup */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did6_location.h"

	/******************************************************************/
	/* SID:0x00, DID: 7 , junction box setup */
	/******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did7_jctbox.h"

	/******************************************************************/
	/* SID:0x00, DID: 8 , RS485 protocol setup */
	/******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did8_rs485_protocol.h"
	/******************************************************************/
	/* SID:0x00, DID: 9 , camera setup */
	/******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did9_camera.h"
    /******************************************************************/
    /* SID:0x00, DID: 10 , radar signal processing EOL setup */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did10_eol.h"

    /******************************************************************/
    /* SID:0x00, DID: 11 , radar signal processing installation setup */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did11_rspinstall.h"

    /******************************************************************/
    /* SID:0x00, DID: 12 , radar rf signal modulation(RSM) setup      */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did12_rsm.h"

	/******************************************************************/
	/* SID:0x00, DID:13  rsp tracking (rsp.trk) setup   */
	/******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did13_rsptracking.h"

    /******************************************************************/
    /* SID:0x00, DID:30~39 rfic tx setup  */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did30_39_rfictx.h"

    /******************************************************************/
    /* SID:0x00, DID:40~49 rfic rx setup  */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did40_49_rficrx.h"

    /******************************************************************/
    /* SID:0x00, DID:50~59 rfic pll setup  */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did50_59_rficpll.h"

    /******************************************************************/
    /* SID:0x00, DID:60 rfm adc adi adar7251 setup  */
    /******************************************************************/
    /******************************************************************/
    /* SID:0x00, DID:62 rfm adc maxim max11043 setup  */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did60_69_rfmadc.h"

	/******************************************************************/
	/* SID:0x00, DID:200~299 Application Service setup  */
	/******************************************************************/
	/******************************************************************/
	/* SID:0x00, DID:200 application packet setup  */
	/******************************************************************/
#include "sys_param_bts24mx/sys_param_sid0did200_299_app_packet.h"

    /******************************************************************/
    /* SID:0x06, DID:0  CAN Communication Setup                      */
    /******************************************************************/
    /******************************************************************/
    /* SID:0x06, DID:1  CAN Signal Setup                              */
    /******************************************************************/
    /******************************************************************/
    /* SID:0x06, DID:2  CAN TX Message Setup                          */
    /******************************************************************/
#if SYS_APP_CANDB_TYPE == SYS_APP_CANDB_TYPE_HKMC1G
#include "sys_param_bts24mx/sys_param_sid6did0_9_can_hkmc1g.h"
#elif SYS_APP_CANDB_TYPE == SYS_APP_CANDB_TYPE_HKMC2G
#include "sys_param_bts24mx/sys_param_sid6did0_9_can_hkmc2g.h"
#elif SYS_APP_CANDB_TYPE == SYS_APP_CANDB_TYPE_J1939
#include "sys_param_bts24mx/sys_param_sid6did0_9_can_j1939.h"
#elif SYS_APP_CANDB_TYPE == SYS_APP_CANDB_TYPE_MITSUBISHI
#include "sys_param_bts24mx/sys_param_sid6did0_9_can_mitsubishi.h"
#endif


    /******************************************************************/
    /* SID:0x07, DID:0  Filesystem Setup                          */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid7did0_filesystem.h"



    /******************************************************************/
    /* SID: 8, DID: 0 , ITS application setup */
    /******************************************************************/
    /******************************************************************/
    /* SID: 8, DID: 1 , ITS application for relay setup */
    /******************************************************************/
    /******************************************************************/
    /* SID: 8, DID: 10 , ITS application for test parameter setup */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid8_its.h"


    /******************************************************************/
    /* SID: 9, DID: 0 , Virtual Fence reflector setup */
    /******************************************************************/
    /******************************************************************/
    /* SID: 9, DID: 1 , Virtual Fence destination server setup */
    /******************************************************************/
    /******************************************************************/
    /* SID: 9, DID: 2 , Virtual Fence relay setup */
    /******************************************************************/
    /******************************************************************/
    /* SID: 9, DID: 3 , UI setup */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid9_vf.h"




    /******************************************************************/
    /* SID: 10, DID: 0 , FCW Forward Collision Warning application setup */
    /******************************************************************/
    /******************************************************************/
    /* SID: 10, DID: 1 , FCW Forward Collision Warning application test */
    /******************************************************************/
#include "sys_param_bts24mx/sys_param_sid10_fcw.h"

	/*.data_start_marker=*/0xBEEFCAFE,
	/*.data_start_marker1=*/0xBEEFCAF0,
	/*.data_start_marker2=*/0xBEEFCAF1,
};

const sys_param_pid8_its_data_t sys_param_pid8_its_data_default = {
    /*"lane":*/ {
        /* "cnt":*/ 4,
        /* "num":*/ {1, 2, 3, 4},
        /* "period":*/ {60, 300, 600},
    },
    /* "count":*/
    {
        /* "ts":*/ 0,
        /* "diff":*/ {10, 5, 2, 3},
        /* "acc":*/
        {
            {60, 61, 62, 63},
            {300, 301, 302, 303},
            {600, 601, 602, 603},
        },
        /* "lc":*/ {1, 3, 2, 1},
        /* "acclc":*/
        {
            {64, 65, 66, 67},
            {304, 305, 306, 307},
            {604, 605, 606, 607},
        },
    },
    /* "speed":*/
    {
        /* "average":*/ {
            {40.5, 25.7, 38.4, 40.4},
            {40.5, 25.7, 38.4, 40.4},
            {40.5, 25.7, 38.4, 40.4},
        },
        /* "min":*/
        {
            {10.5, 15.7, 17.4, 10.4},
            {10.5, 15.7, 17.4, 10.4},
            {10.5, 15.7, 17.4, 10.4},
        },
        /* "max":*/
        {
            {80.5, 120.7, 90.4, 80.4},
            {80.5, 120.7, 90.4, 80.4},
            {80.5, 120.7, 90.4, 80.4},
        },
    },

    /* "event" */
    {
        /* "abnormal":*/
        {
            /* "tid":*/ {0},
            /* "lane":*/ {0},
        },
        /* "reverse":*/
        {
            /* "tid":*/ {0},
            /* "lane":*/ {0},
        },
        /* "speedlimit":*/
        {
            /* "tid":*/ {0},
            /* "lane":*/ {0},
        },
        /* "cs":*/ "y",
        /* "nv":*/
        {
            /* "tid":*/ {0},
        }},
};


