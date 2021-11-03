/************************************************************************
| Project Name: bts_comm_appl_udpcallback
|    File Name: bts_comm_appl_udpcallback.c
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
| 2018.12.27   0.0   SKJ   Creation;
|***********************************************************************/


/* include system primitive types */

#include "bts.h"

/* include system driver header */


/* include system bsp header */


/* include system application header */


/* final include module header */
#include "bts_md5.h"
//#include "drivers.h"
//#include "filesystem.h"
#include "linux_fs_app_cfg.h"
#include "bts_comm.h"
#include "bts_comm_appl.h"
#include "bts_comm_applcmd.h"
#include "bts_comm_applcmd_callback.h"
#include "bts_comm_cfg.h"
#include "bts_comm_status.h"
#include "krs_base64.h"
//#include "modulation.h"
//#include "mtd_app.h"
#include "os.h"
#include "sys_param.h"
#include "system.h"
//#include "taskmgr.h"
//#include "thread_manager.h"

/*
    // simple request/response base command processor, response json format
    1. command json format
        {"cmd":"[read|write|save|etc...", "param":{...}}
    2. response json format
        {"cmd":"[received command]", "resp":"[OK|ERR|RCRP|etc]", "param":{...}}

    3. simple session control model
        normal : password or security access not required
        security : need to unlock security

    4. service description
        4.1 session control
            a. get current session state
                req  : {"cmd":"session", "param":"status"}
                +resp: {"cmd":"session", "resp":"OK", "param":"normal"}
                -resp: {"cmd":"session", "resp":"ERR", "param":"unknown"}

            b. set current session state to normal
                req  : {"cmd":"session", "param":"normal"}
                +resp: {"cmd":"session", "resp":"OK", "param":"normal"}
                -resp: {"cmd":"session", "resp":"ERR", "param":"unkown"}

            c. set current session state to security - get seed
                req  : {"cmd":"getseed", "param":"seed"}
                +resp: {"cmd":"getseed", "resp":"OK", "param":12345678}  // seed is 32bit unsigned
   value -resp: {"cmd":"getseed", "resp":"ERR", "param":"invalidstate"} //

            d. set current session state to security - send key
                req  : {"cmd":"sendkey", "param":<password or generated key based on seed, 32bit
   unsigned value>} +resp: {"cmd":"sendkey", "resp":"OK", "param":"security"}  // seed is 32bit
   unsigned value -resp: {"cmd":"sendkey", "resp":"ERR", "param":"invalidkey"} //

            e. seed key algorithm
                key = hash(f'bitsensing_{seed:08X}))
                hash function : hash_djb2

        4.2 read data by id
                req  : {"cmd":"read", "param":{"sid":0, "did":30}}
                +resp: {"cmd":"read", "resp":"OK", "param":{readed json data}}
                -resp: {"cmd":"read", "resp":"ERR", "param":"unknown sid or did"}

        4.3 write data by id
                req  : {"cmd":"write", "param":{"sid":0, "did":30, "setup":{...}}}
                +resp: {"cmd":"write", "resp":"OK", "param":{...}}
                -resp: {"cmd":"write", "resp":"ERR", "param":"unknown sid or did"}

        4.4 save parameters to mtd
                req  : {"cmd":"save", "param":""}
                +resp: {"cmd":"save", "resp":"OK"}
                -resp: {"cmd":"save", "resp":"ERR", "param":"mtdapp error"}

        4.4 save parameters to factory
                req  : {"cmd":"savefactory"}
                +resp: {"cmd":"savefactory", "resp":"OK"}
                -resp: {"cmd":"savefactory", "resp":"ERR", "param":"save factory error"}

        4.5b load parameters from factory parameters
                req  : {"cmd":"loadfactory"}
                +resp: {"cmd":"loadfactory", "resp":"OK"}
                -resp: {"cmd":"loadfactory", "resp":"ERR", "param":"load factory fail"}

        4.5b factory init
                req  : {"cmd":"factoryinit"}
                +resp: {"cmd":"factoryinit", "resp":"OK"}
                -resp: {"cmd":"factoryinit", "resp":"ERR", "param":"factory init fail"}

        4.6 reportip
                req  : {"cmd":"reportip"}
                +resp: {"cmd":"reportip", "resp":"OK", "param":{"ip":"192.168...."}}
                -resp: {"cmd":"reportip", "resp":"ERR", "param":"unknown ip"}


        4.7.1 setip
                req  : {"cmd":"setip", "param":{"ip":"192.168.10.150", "nm":"255.255.255.0",
   "gw":"192.168.10.1"..., "dhcp":0}} +resp: {"cmd":"setip", "resp":"OK",
   "param":{"ip":"192.168.10.150", "nm":"255.255.255.0", "gw":"192.168.10.1"...}} -resp:
   {"cmd":"setip", "resp":"ERR", "param":"invalid ip"}

        4.7.2 defaultip
                req  : {"cmd":"defaultip"}
                +resp: {"cmd":"defaultip", "resp":"OK", "param":{"ip":"192.168.10.150",
   "nm":"255.255.255.0", "gw":"192.168.10.1"...}} -resp: {"cmd":"defaultip", "resp":"ERR",
   "param":"invalid ip"}

        4.7.4 scan : broadcast only
                req : {"cmd":"scan"}
                +resp: {"cmd":"scan", "resp":"OK", "param":{"devuid":xxxxx, "serialnumber":xxxxx,
   "mac":"xx:xx:xx:xx:xx"}}


        4.7.3 recover : broadcast only, no response code
                req : {"cmd":"recover", "param":{"devuid":<devuid>, "serialnumber":xxxxx,
   "ip":"192.168.10.150", "nm":"255.255.255.0", "gw":"192.168.10.1"..., "dhcp":0}} +resp :
   {"cmd":"recover", "resp":"OK"}


        4.8 mwr : memory write by address
                req  : {"cmd":"mwr", "param":{"address":12345, "size":4,
   "encoding":<"base64","array">, "bytes":[0]}} +resp: {"cmd":"mwr", "resp":"OK",
   "param":{"address":12345, "size":4,  "encoding":<"base64","array">, "bytes":[0]}} -resp:
   {"cmd":"mwr", "resp":"ERR", "param":"invalid address"}

        4.9 mrd : memory read by address
                req  : {"cmd":"mrd", "param":{"address":12345, "size":4}
                +resp: {"cmd":"mrd", "resp":"OK", "param":{"address":12345, "size":4, "bytes":[0]}}
                -resp: {"cmd":"mrd", "resp":"ERR", "param":"invalid address"}

        4.10 fwr : flash cache write by address
            req  : {"cmd":"fwr", "param":{"address":12345, "size":4, "encoding":<"base64","array">,
   "bytes":[0]}} +resp: {"cmd":"fwr", "resp":"OK", "param":{"address":12345, "size":4,
   "encoding":<"base64","array">, "bytes":[0]}} -resp: {"cmd":"fwr", "resp":"ERR", "param":"invalid
   address"}

        4.11 frd: flash cache read by address
                req  : {"cmd":"frd", "param":{"address":12345, "size":4,
   "encoding":<"base64","array">} +resp: {"cmd":"frd", "resp":"OK", "param":{"address":12345,
   "size":4,  "encoding":<"base64","array">, "bytes":[0]}} -resp: {"cmd":"frd", "resp":"ERR",
   "param":"invalid address"}



        4.12 fst : flash cache store
                req  : {"cmd":"fst", "param":{"address":12345, "size":4}
                +resp: {"cmd":"fst", "resp":"OK"}
                -resp: {"cmd":"fst", "resp":"ERR", "param":"invalid address"}

        4.13 fld : flash cache load
            req  : {"cmd":"fld", "param":{"address":12345, "size":4, "cs":"md5"}
            +resp: {"cmd":"fld", "resp":"OK", "param":{"cs":"md5", "value":[]}}
            -resp: {"cmd":"fld", "resp":"ERR", "param":"invalid address"}

        4.14 fcs : flash cache cal checksum
            req  : {"cmd":"fcs", "param":{"address":12345, "size":4, load:<true,false>,"cs":<"md5">}
            +resp: {"cmd":"fcs", "resp":"OK", "param":{"md5":"<hexdecimal value>"}}
            -resp: {"cmd":"fcs", "resp":"ERR", "param":"invalid address"}

        5.1 reset : reset
                req  : {"cmd":"reset"}
                +resp: {"cmd":"reset", "resp":"OK"}
                -resp: {"cmd":"reset", "resp":"ERR", "param":"busy state"}

        6.1 get_daqinfo : get daq information
                req  : {"cmd":"get_daqinfo"}
                +resp: {"cmd":"get_daqinfo", "resp":"OK", "param":{daqinfo....}}
                -resp: {"cmd":"get_daqinfo", "resp":"ERR", "param":"get daqinfo error"}

        7.1 get : get daq information
                req  : {"cmd":"get","param":<"daq"|"swversion"|"hwversion"|etc>}
                +resp: {"cmd":"get", "resp":"OK", "param":{....}}
                -resp: {"cmd":"get", "resp":"ERR", "param":"get xxxx error"}

        8.1 set : set information
                req  : {"cmd":"set","param":{"type":"servertimestamp", "servertimestamp":xxxxxxx}}
                req  : {"cmd":"set","param":{"type":"datetime", "Y":2020,
   "m":9,"d":8,"H":18,"M":53,"S":30,"SS":0.324}}
				req  : {"cmd":"set","param":{"type":"wol", "targetmac":"12:34:56:78:9A:BC"}}
                +resp: {"cmd":"set", "resp":"OK", "param":{....}}
                -resp: {"cmd":"set", "resp":"ERR", "param":"set xxxx error"}
*/
#define bts_comm_applcmd_callback_assert(assert, out, cmd, msg)                          \
    if((assert) == 0)                                                                      \
    {                                                                                      \
        bts_comm_applcmd_callback_log(msg);                                              \
        packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, param:%Q}", cmd, "ERR", msg); \
        return retFail;                                                                    \
    }


extern int32_t bts_comm_applcmd_sendresponse(bts_comm_applcmd_packet_t *pkt);
extern bts_ret_t bts_comm_send_wake_on_lan_packet(char_t *macstr);



int32_t bts_comm_applcmd_callback_get_daqinfo(json_out_t *out,
                                                bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_get(json_out_t *out, bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_set(json_out_t *out, bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_read_data_by_id(json_out_t *out,
                                                    bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_write_data_by_id(json_out_t *out,
                                                     bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_mtdapp_save(json_out_t *out,
                                                bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_mtdapp_savefactory(json_out_t *out,
                                                       bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_mtdapp_loadfactory(json_out_t *out,
                                                       bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_mtdapp_factoryinit(json_out_t *out,
                                                       bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_reportip(json_out_t *out, bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_setip(json_out_t *out, bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_defaultip(json_out_t *out, bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_scan(json_out_t *out, bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_recover(json_out_t *out, bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_memory_write(json_out_t *out,
                                                 bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_memory_read(json_out_t *out,
                                                bts_comm_applcmd_packet_t *packet);

int32_t bts_comm_applcmd_callback_flash_cache_write(json_out_t *out,
                                                      bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_flash_cache_read(json_out_t *out,
                                                     bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_flash_cache_store(json_out_t *out,
                                                      bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_flash_cache_load(json_out_t *out,
                                                     bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_flash_cache_calchecksum(json_out_t *out,
                                                            bts_comm_applcmd_packet_t *packet);
int32_t bts_comm_applcmd_callback_reset(json_out_t *out, bts_comm_applcmd_packet_t *packet);

bts_comm_applcmd_dispatch_table_t bts_comm_applcmd_dispatch_table[] = {
    //{"session", bts_comm_applcmd_session_all, bts_comm_applcmd_callback_session_control},
    {"get_daqinfo", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_get_daqinfo},
    {"get", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_get},
    {"set", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_set},
    {"read", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_read_data_by_id},
    {"write", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_write_data_by_id},
    {"save", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_mtdapp_save},
    {"savefactory", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_mtdapp_savefactory},
    {"loadfactory", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_mtdapp_loadfactory},
    {"factoryinit", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_mtdapp_factoryinit},
    {"reportip", bts_comm_applcmd_session_all, bts_comm_applcmd_callback_reportip},
    {"setip", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_setip},
    {"defaultip", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_defaultip},
    {"scan", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_scan},
    {"recover", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_recover},
    {"mwr", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_memory_write},
    {"mrd", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_memory_read},
    {"fwr", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_flash_cache_write},
    {"frd", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_flash_cache_read},
    {"fst", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_flash_cache_store},
    {"fld", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_flash_cache_load},
    {"fcs", bts_comm_applcmd_session_security,
     bts_comm_applcmd_callback_flash_cache_calchecksum},
    {"reset", bts_comm_applcmd_session_security, bts_comm_applcmd_callback_reset},
};

#define bts_COMM_APPLCMD_CALLBACKCOUNT \
    sizeof(bts_comm_applcmd_dispatch_table) / sizeof(bts_comm_applcmd_dispatch_table_t)

/* declare static variables */


/* static function prototypes */
static char_t bts_comm_applcmd_callback_jsonbuff[bts_COMM_APPLCMD_CALLBACK_JSONBUFFSIZE];
// static bts_comm_applcmd_sessiontype_t bts_comm_applcmd_sessiontype;


/******************************************************************************
 * function name : bts_comm_appl_cmdcallback_dispactch
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packet description
 * \return int32_t description
 * modification date : 2018.12.27
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_dispactch(bts_comm_applcmd_packet_t *packet)
{
    int32_t i;
    int32_t ret;
    char_t command[32] = "";
    json_out_t commandrespout =
        JSON_OUT_BUF(packet->txbuffptr, bts_COMM_APPLCMD_CALLBACK_JSONBUFFSIZE);

    bts_comm_applcmd_callback_assert(packet->rxsize < bts_COMM_APPLCMD_CALLBACK_JSONBUFFSIZE,
                                       &commandrespout, "unknown", "invalid packet size\n\r");
    bts_comm_applcmd_callback_assert(packet->rxbuffptr != NULL, &commandrespout, "unknown",
                                       "invalid rxbuffer address\n\r");

    bts_comm_applcmd_callback_log("cmd callback dispatch: %.*s\n\r", packet->rxsize,
                                    (const char *)packet->rxbuffptr);
    // 1. command extract
    ret = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s}", command);
    bts_comm_applcmd_callback_assert(ret == 1, &commandrespout, "unknown",
                                       "no command available\n\r");

    // 1. command search
    bts_comm_applcmd_callback_log("cmd callback : %s\n\r", command);
    for(i = 0; i < bts_COMM_APPLCMD_CALLBACKCOUNT; i++)
    {
        if(sys_param_match_string(command, bts_comm_applcmd_dispatch_table[i].command) == retOK)
        {
            bts_comm_applcmd_callback_log("cmd callback dispatch to %s\n\r",
                                            bts_comm_applcmd_dispatch_table[i].command);
            // if(bts_comm_applcmd_sessiontype == bts_comm_applcmd_session_normal)
            // {
            //    if((bts_comm_applcmd_dispatch_table[i].sessiontype ==
            //    bts_comm_applcmd_session_normal) ||
            //     (bts_comm_applcmd_dispatch_table[i].sessiontype ==
            //     bts_comm_applcmd_session_all))
            //    {
            //         // except security
            //    }
            // }
            // else if(bts_comm_applcmd_sessiontype == bts_comm_applcmd_session_security)
            // {
            //     // ok all
            // }
            ret = retFail;
            if(bts_comm_applcmd_dispatch_table[i].callback != NULL)
            {
                ret = bts_comm_applcmd_dispatch_table[i].callback(&commandrespout, packet);
            }
            if(packet->txsize > 0)
            {
                packet->txen = 1;
            }

            bts_comm_applcmd_callback_log("cmd callback tx:%.*s\n\r", packet->txsize,
                                            packet->txbuffptr);
            return ret;
        }
    }
    bts_comm_applcmd_callback_assert(1, &commandrespout, command, "no callback available\n\r");

    return retFail;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_session_control
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2018.12.27
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_session_control(json_out_t *out,
                                                    bts_comm_applcmd_packet_t *packet)
{
    int32_t len;
    char_t command[32] = "";
    char_t paramstr[32] = "";
    // packet->rxbuffptr
    // packet->rxsize
    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s, param:%s}", command,
                     paramstr);
    bts_comm_applcmd_callback_assert(len == 2, out, "session", "no command or param available");

    if(sys_param_match_string(paramstr, "status") == retOK)
    {
        packet->txsize =
            json_printf(out, "{cmd:%.*Q, resp:%Q, param:%Q}", 32, "session", "OK", "normal");
        return retOK;
    }
    else if(sys_param_match_string(paramstr, "normal") == retOK)
    {
    }
    else if(sys_param_match_string(paramstr, "seed") == retOK)
    {
    }
    else if(sys_param_match_string(paramstr, "sendkey") == retOK)
    {
    }
    else
    {
    }
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_get_daqinfo
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *out description
 * \param1 *packet description
 * \return0 int32_t description
 * modification date : 2020.09.08
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_get_daqinfo(json_out_t *out,
                                                bts_comm_applcmd_packet_t *packet)
{
    /*
     req  : {"cmd":"get_daqinfo"}
     +resp: {"cmd":"get_daqinfo", "resp":"OK", "param":{daqinfo....}}
     -resp: {"cmd":"get_daqinfo", "resp":"ERR", "param":"get daqinfo error"}
     */
    int32_t len;
    len = bts_comm_appl_common_get_daqinfo(bts_comm_applcmd_callback_jsonbuff,
                                             sizeof(bts_comm_applcmd_callback_jsonbuff));
    bts_comm_applcmd_callback_assert(len > 0, out, "get_daqinfo", "daqinfo json error\n\r");

    packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, param:", "get_daqinfo", "OK");
    packet->txsize += json_printer_buf(out, bts_comm_applcmd_callback_jsonbuff, len);
    packet->txsize += json_printer_buf(out, "}", 1);

    return retOK;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_get
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *out description
 * \param1 *packet description
 * \return0 int32_t description
 * modification date : 2020.09.08
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_get(json_out_t *out, bts_comm_applcmd_packet_t *packet)
{
    /*
        7.1 get : get daq information
                req  : {"cmd":"get","param":<"daqinfo"|"swinfo"|"paraminfo"|etc>}
                +resp: {"cmd":"get", "resp":"OK", "param":{....}}
                -resp: {"cmd":"get", "resp":"ERR", "param":"get xxxx error"}
     */
    int32_t len;
    char_t command[32] = "";
    char_t paramstr[32] = "";
    char_t devuid_buff[20] = "";

    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s, param:%s}", command,
                     paramstr);
    bts_comm_applcmd_callback_assert(len == 2, out, "get", "no command or param available");

    if(sys_param_match_string(paramstr, "daqinfo") == retOK)
    {
        len = bts_comm_appl_common_get_daqinfo(bts_comm_applcmd_callback_jsonbuff,
                                                 sizeof(bts_comm_applcmd_callback_jsonbuff));
        bts_comm_applcmd_callback_assert(len > 0, out, "get", "daqinfo json error\n\r");

        packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, param:", command, "OK");
        packet->txsize += json_printer_buf(out, bts_comm_applcmd_callback_jsonbuff, len);
        packet->txsize += json_printer_buf(out, "}", 1);
    }
    else if(sys_param_match_string(paramstr, "swinfo") == retOK)
    {
        system_devuid_str(devuid_buff, sizeof(devuid_buff));
        packet->txsize = json_printf(out,
                                     "{cmd:%Q, resp:%Q, "
                                     "param:{appname:%Q,version:%Q,date:%d,time:%d,devuid:%Q,"
                                     "serialnumber:%Q,param_version:%d}}",
                                     command, "OK", SYS_APP_NAME, SYS_SW_VERSION,
                                     system_swbuild_date(), system_swbuild_time(), devuid_buff,
                                     (void *)&sys_param_sidxdidx_configinfo_packing
                                         .sid0did0_systembase_config.setup.sensortype.serialnumber,
                                     sys_param_sidxdidx_configinfo_packing.param_version);
    }
    else if(sys_param_match_string(paramstr, "paraminfo") == retOK)
    {
        system_devuid_str(devuid_buff, sizeof(devuid_buff));
        packet->txsize =
            json_printf(out,
                        "{cmd:%Q, resp:%Q, "
                        "param:{param_version:%d,guidstr:%.*Q,start_marker:%d,end_marker:%d,end_"
                        "marker1:%d,end_marker2:%d}}",
                        command, "OK", sys_param_sidxdidx_configinfo_packing.param_version,
                        sizeof(sys_param_sidxdidx_configinfo_packing.guidstr),
                        sys_param_sidxdidx_configinfo_packing.guidstr,
                        sys_param_sidxdidx_configinfo_packing.data_start_marker,
                        sys_param_sidxdidx_configinfo_packing.data_end_marker,
                        sys_param_sidxdidx_configinfo_packing.data_end_marker1,
                        sys_param_sidxdidx_configinfo_packing.data_end_marker2);
    }
    else if(sys_param_match_string(paramstr, "status") == retOK)
    {
        /* device unique ID */
        len = system_get_status_to_json(bts_comm_applcmd_callback_jsonbuff,
                                        sizeof(bts_comm_applcmd_callback_jsonbuff));
        bts_comm_applcmd_callback_assert(len > 0, out, "get", "system status json error\n\r");

        packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, param:", command, "OK");
        packet->txsize += json_printer_buf(out, bts_comm_applcmd_callback_jsonbuff, len);
        packet->txsize += json_printer_buf(out, "}", 1);
    }
    else
    {
        bts_comm_applcmd_callback_assert(len == 2, out, "get", "param not in daq/swinfo");
    }

    return retOK;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_set
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *out description
 * \param1 *packet description
 * \return0 int32_t description
 * modification date : 2020.09.08
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_set(json_out_t *out, bts_comm_applcmd_packet_t *packet)
{
    /*
        8.1 set : set information
                req  : {"cmd":"set","param":{"type":"servertimestamp", "servertimestamp":xxxxxxx}}
                req  : {"cmd":"set","param":{"type":"datetime", "Y":2020,
       "m":9,"d":8,"H":18,"M":53,"S":30,"SS":0.324}}

                +resp: {"cmd":"set", "resp":"OK", "timestamp":xxxxxx.xxx}
                -resp: {"cmd":"set", "resp":"ERR", "param":"set xxxx error"}
     */
    int32_t len;
    char_t command[32] = "";
    char_t commandtype[32] = "";
    char_t targetmac[32]="FF:FF:FF:FF:FF:FF";
    json_token_t t;
    f64_t servertimestamp = 0.0;
    int32_t ret;
    uint8_t resptype=0;
    struct tm ts;


    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s, param:%T}", command,
                     &t);
    bts_comm_applcmd_callback_assert(len == 2, out, "set", "no command or param available");

    len = json_scanf((const char *)t.ptr, t.len, "{type:%s}", commandtype);
    bts_comm_applcmd_callback_assert(len == 1, out, "set", "type is not found\n\r");


    if(sys_param_match_string(commandtype, "servertimestamp") == retOK)
    {

        len = json_scanf((const char *)t.ptr, t.len, "{type:%s, servertimestamp:%lf}", commandtype,
                         &servertimestamp);
        bts_comm_applcmd_callback_assert(len == 2, out, "set",
                                           "servertimestamp field not found\n\r");
        resptype = 0;
    }
    else if(sys_param_match_string(commandtype, "datetime") == retOK)
    {
        len = json_scanf((const char *)t.ptr, t.len,
                         "{type:%s, Y:%d, m:%d,d:%d,H:%d,M:%d,S:%d,SS:%lf}", commandtype,
                         &ts.tm_year, &ts.tm_mon, &ts.tm_mday, &ts.tm_hour, &ts.tm_min, &ts.tm_sec,
                         &servertimestamp);
        bts_comm_applcmd_callback_assert(len == 8, out, "set", "datetime fields are invalid\n\r");

        // adjust for tm struct
        ts.tm_year -= 1900;
        ts.tm_mon -= 1;
        servertimestamp = bts_datetime_make_timestamp(&ts);
        resptype = 0;
    }
    else if(sys_param_match_string(commandtype, "wol") == retOK)
    {
    	len = json_scanf((const char *)t.ptr, t.len, "{type:%s, targetmac:%s}", commandtype,
    	                         targetmac);
    	bts_comm_applcmd_callback_assert(len == 2, out, "set", "wol fields are invalid\n\r");
    	bts_comm_applcmd_callback_log("set wol: targetmac is %s\n\r", targetmac);
    	ret = bts_comm_send_wake_on_lan_packet(targetmac);
    	bts_comm_applcmd_callback_assert(ret == retOK, out, "set", "sending wake on lan magic packet fail\n\r");
    	resptype = 1;

    }
    else
    {
        bts_comm_applcmd_callback_assert(0, out, "set", "invalid type");
    }

    if(resptype==0)
    {
		// Compensate command processing time
		servertimestamp += ((f64_t)(os_time_us() - packet->rxtimestamp)) / 10000000.0;
		bts_datetime_settime(servertimestamp);
		servertimestamp = bts_datetime_gettime();
		packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, timestamp:%lf}", command, "OK", servertimestamp);
    }
    else if(resptype == 1)
    {
    	packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q}", command, "OK");
    }
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_read_data_by_id
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2018.12.27
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_read_data_by_id(json_out_t *out,
                                                    bts_comm_applcmd_packet_t *packet)
{
    /*
        req  : {"cmd":"read", "param":{"sid":0, "did":30}}
        +resp: {"cmd":"read", "resp":"OK", "param":{readed json data}}
        -resp: {"cmd":"read", "resp":"ERR", "param":"unknown sid or did"}
    */
    int32_t sid;
    int32_t did;
    int32_t len;
    char_t command[32] = "";
    json_token_t t;
    sys_param_jsontype_info_t *jsoninfo;

    // packet->rxbuffptr
    // packet->rxsize
    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s, param:%T}", command,
                     &t);
    bts_comm_applcmd_callback_assert(len == 2, out, "read", "no command or param available\n\r");

    len = json_scanf((const char *)t.ptr, t.len, "{sid:%d, did:%d}", &sid, &did);
    bts_comm_applcmd_callback_assert(len == 2, out, command, "no sid or did\n\r");

    bts_comm_applcmd_callback_log("received : sid:%d, did:%d\n\r", sid, did);

    jsoninfo = sys_param_jsontype_info_find(sid, did, -1);
    bts_comm_applcmd_callback_assert(jsoninfo != NULL, out, command,
                                       "not supported sid or did\n\r");

    bts_comm_applcmd_callback_log("read data: %.*s\n\r", (int)jsoninfo->type_name_len,
                                    jsoninfo->type_name);

    len = jsoninfo->dumpfunc("", bts_comm_applcmd_callback_jsonbuff, jsoninfo->pvParam);
    bts_comm_applcmd_callback_assert(len > 0, out, command, "json dump fail\n\r");

    packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, param:", command, "OK");
    packet->txsize += json_printer_buf(out, bts_comm_applcmd_callback_jsonbuff, len);
    packet->txsize += json_printer_buf(out, "}", 1);

    return retOK;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_write_data_by_id
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2018.12.27
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_write_data_by_id(json_out_t *out,
                                                     bts_comm_applcmd_packet_t *packet)
{
    /*
        req  : {"cmd":"write", "param":{"sid":0, "did":30, "setup":{...}}}
        +resp: {"cmd":"write", "resp":"OK"}
        -resp: {"cmd":"write", "resp":"ERR", "param":"unknown sid or did"}
    */
    int32_t sid;
    int32_t did;
    int32_t len;
    char_t command[32] = "";
    json_token_t t;
    sys_param_jsontype_info_t *jsoninfo;

    // packet->rxbuffptr
    // packet->rxsize
    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s, param:%T}", command,
                     &t);
    bts_comm_applcmd_callback_assert(len == 2, out, "write", "no command or param available\n\r");

    len = json_scanf((const char *)t.ptr, t.len, "{sid:%d, did:%d}", &sid, &did);
    bts_comm_applcmd_callback_assert(len == 2, out, command, "no sid or did\n\r");

    bts_comm_applcmd_callback_log("received : sid:%d, did:%d\n\r", sid, did);

    jsoninfo = sys_param_jsontype_info_find(sid, did, -1);
    bts_comm_applcmd_callback_assert(jsoninfo != NULL, out, command,
                                       "not supported sid or did\n\r");

    bts_comm_applcmd_callback_log("write data: %.*s\n\r", (int)jsoninfo->type_name_len,
                                    jsoninfo->type_name);

    len = jsoninfo->loadfunc((char *)t.ptr, t.len, jsoninfo->pvParam);
    bts_comm_applcmd_callback_assert(len > 0, out, command, "json load fail\n\r");

    packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, param:", command, "OK");
    packet->txsize += json_printer_buf(out, t.ptr, t.len);
    packet->txsize += json_printer_buf(out, "}", 1);

    return retOK;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_mtdapp_save
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2018.12.27
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_mtdapp_save(json_out_t *out,
                                                bts_comm_applcmd_packet_t *packet)
{
    /*
        req  : {"cmd":"save", "param":""}
        +resp: {"cmd":"save", "resp":"OK"}
        -resp: {"cmd":"save", "resp":"ERR", "param":"mtdapp error"}
    */

    //if(mtd_app_store(mtdapp) == retOK)
    if(sys_param_save_to_file(SYS_PARAM_FILE_PATH_APP, &sys_param_sidxdidx_configinfo_packing) == retOK)
    {
        packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, param:%Q}", "save", "OK", "");
    }
    else
    {
        packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, param:%Q}", "save", "ERR",
                                     "mtd_app_store return fail");
    }
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_mtdapp_savefactory
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *out description
 * \param1 *packet description
 * \return0 int32_t description
 * modification date : 2020.09.08
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_mtdapp_savefactory(json_out_t *out,
                                                       bts_comm_applcmd_packet_t *packet)
{
    /*
        4.4 save parameters to factory parameters
                req  : {"cmd":"savefactory"}
                +resp: {"cmd":"savefactory", "resp":"OK"}
                -resp: {"cmd":"savefactory", "resp":"ERR", "param":"save factory error"}
    */
    int32_t len;
    char_t command[32] = "";
    int32_t ret;


    // packet->rxbuffptr
    // packet->rxsize
    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s}", command);
    bts_comm_applcmd_callback_assert(len == 1, out, "savefactory",
                                       "savefactory command not found\n\r");


    sys_param_sidxdidx_configinfo_packing.param_version++;
    ret = sys_param_save_to_factory((void *)&sys_param_sidxdidx_configinfo_packing);
    bts_comm_applcmd_callback_assert(ret == retOK, out, "savefactory", "factory save fail\n\r");
    krs_memclearitem(sys_param_sidxdidx_configinfo_packing_factory);
    ret = sys_param_load_from_factory((void *)&sys_param_sidxdidx_configinfo_packing_factory);
    bts_comm_applcmd_callback_assert(ret == retOK, out, "savefactory", "factory load fail\n\r");


    if(sys_param_sidxdidx_configinfo_packing.param_version == sys_param_sidxdidx_configinfo_packing_factory.param_version)
    {

    	krs_memcopy((void*)&sys_param_sidxdidx_configinfo_packing, (void*)&sys_param_sidxdidx_configinfo_packing_factory, sizeof(sys_param_sidxdidx_configinfo_packing));

        //if(mtd_app_store(mtdapp) == retOK)
        if(!ret)
        {
            packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q}", "savefactory", "OK");
            bts_comm_applcmd_callback_log(
                "bts_comm_applcmd_callback_mtdapp_savefactory success\n\r");
            return retOK;
        }
        else
        {
            packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, param:%Q}", "savefactory", "ERR",
                                         "mtd_app_load_default fail");
            bts_comm_applcmd_callback_log(
                "bts_comm_applcmd_callback_mtdapp_savefactory fail\n\r");
            return retFail;
        }
    }
    return retFail;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_mtdapp_loadfactory
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *out description
 * \param1 *packet description
 * \return0 int32_t description
 * modification date : 2020.09.08
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_mtdapp_loadfactory(json_out_t *out,
                                                       bts_comm_applcmd_packet_t *packet)
{
    /*
        4.5b load parameters from factory parameters
                req  : {"cmd":"loadfactory"}
                +resp: {"cmd":"loadfactory", "resp":"OK"}
                -resp: {"cmd":"loadfactory", "resp":"ERR", "param":"load factory fail"}
    */
	int32_t ret;
    //ret = sys_param_load_from_factory((void *)&sys_param_sidxdidx_configinfo_packing_factory);
    ret = sys_param_load_from_factory((void *)&sys_param_sidxdidx_configinfo_packing);
    bts_comm_applcmd_callback_assert(ret == retOK, out, "loadfactory", "factory load fail\n\r");

    if(ret == retOK)
    {
        //krs_memcopy((void*)&sys_param_sidxdidx_configinfo_packing, (void*)&sys_param_sidxdidx_configinfo_packing_factory, sizeof(sys_param_sidxdidx_configinfo_packing));

        //if(mtd_app_store(mtdapp) == retOK)
        if(sys_param_save_to_file(SYS_PARAM_FILE_PATH_APP, &sys_param_sidxdidx_configinfo_packing) == retOK)
        {
            packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q}", "loadfactory", "OK");
            bts_comm_applcmd_callback_log(
                    "bts_comm_applcmd_callback_mtdapp_loadfactory success\n\r");
            return retOK;
        }
        else
        {
            packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, param:%Q}", "loadfactory", "ERR",
                                    "mtdapp_load_default fail");
            bts_comm_applcmd_callback_log(
                    "bts_comm_applcmd_callback_mtdapp_loadfactory fail\n\r");
            return retFail;
        }
    }
    return retFail;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_mtdapp_factoryinit
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *out description
 * \param1 *packet description
 * \return0 int32_t description
 * modification date : 2020.09.08
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_mtdapp_factoryinit(json_out_t *out,
                                                       bts_comm_applcmd_packet_t *packet)
{
    /*
        4.5b factory init
                req  : {"cmd":"factoryinit"}
                +resp: {"cmd":"factoryinit", "resp":"OK"}
                -resp: {"cmd":"factoryinit", "resp":"ERR", "param":"factory init fail"}
    */
    int32_t len;
    char_t command[32] = "";
    int32_t ret;


    // packet->rxbuffptr
    // packet->rxsize
    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s}", command);
    bts_comm_applcmd_callback_assert(len == 1, out, "factoryinit",
                                       "factoryinit command not found\n\r");

    ret = sys_param_factoryinit();
    bts_comm_applcmd_callback_assert(ret == retOK, out, "factoryinit",
                                       "sys_param_factoryinit fail\n\r");

    packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q}", "savefactory", "OK");
    bts_comm_applcmd_callback_log("factoryinit success\n\r");
    return retOK;

//    mtdapp->default_dataptr = (void*)&sys_param_sidxdidx_configinfo_packing_default;
//    mtdapp->default_data_size = sizeof(sys_param_sidxdidx_configinfo_packing_default);
//    if(mtd_app_load_default(mtdapp) == retOK)
//    {
//        packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q}", "savefactory", "OK");
//        bts_comm_applcmd_callback_log("factoryinit success\n\r");
//        return retOK;
//    }
//    else
//    {
//        packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, param:%Q}", "savefactory", "ERR",
//                                     "mtd_app_load_default fail");
//        bts_comm_applcmd_callback_log("factoryinit fail\n\r");
//        return retFail;
//    }

    return retFail;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_reportip
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2018.12.27
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_reportip(json_out_t *out, bts_comm_applcmd_packet_t *packet)
{
    /*
        req  : {"cmd":"reportip"}
        +resp: {"cmd":"reportip", "resp":"OK", "param":{"ip":"192.168...."}}
        -resp: {"cmd":"reportip", "resp":"ERR", "param":"unknown ip"}
    */
    int32_t len;


    len = sys_param_common_comm_ethernet_config_t_dump(
        "", bts_comm_applcmd_callback_jsonbuff,
        (void *)&sys_param_sidxdidx_configinfo_packing.sid0did0_systembase_config.setup
            .eth_default);
    bts_comm_applcmd_callback_assert(len > 0, out, "{reportip", "json dump fail");
    bts_comm_applcmd_callback_log("eth_default: %.*s\n\r", len,
                                    bts_comm_applcmd_callback_jsonbuff);
    packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, param:", "reportip", "OK");
    packet->txsize += json_printer_buf(out, bts_comm_applcmd_callback_jsonbuff, len);
    packet->txsize += json_printer_buf(out, "}", 1);

    return retOK;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_setip
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2018.12.27
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_setip(json_out_t *out, bts_comm_applcmd_packet_t *packet)
{
    /*
        req  : {"cmd":"setip", "param":{"ip":"192.168.10.150", "nm":"255.255.255.0",
       "gw":"192.168.10.1"..., "dhcp":0}} +resp: {"cmd":"setip", "resp":"OK",
       "param":{"ip":"192.168.10.150", "nm":"255.255.255.0", "gw":"192.168.10.1"...}} -resp:
       {"cmd":"setip", "resp":"ERR", "param":"save fail"}
    */
    int32_t len;
    char_t command[32] = "";
    json_token_t t;

    // packet->rxbuffptr
    // packet->rxsize
    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s, param:%T}", command,
                     &t);
    bts_comm_applcmd_callback_assert(len == 2, out, "setip", "no command or param available\n\r");

    len = sys_param_common_comm_ethernet_config_t_loads(
        (char *)t.ptr, t.len,
        (void *)&sys_param_sidxdidx_configinfo_packing.sid0did0_systembase_config.setup
            .eth_default);
    bts_comm_applcmd_callback_assert(len > 0, out, "setip", "ip load fail\n\r");

    //bts_comm_applcmd_callback_assert(mtd_app_store(mtdapp) == retOK, out, "setip",
    //                                   "setip save fail\n\r");
    bts_comm_applcmd_callback_assert(retOK, out, "setip", "setip save fail\n\r");

    bts_comm_applcmd_callback_log("setip save complete\n\r");

    len = sys_param_common_comm_ethernet_config_t_dump(
        "", bts_comm_applcmd_callback_jsonbuff,
        (void *)&sys_param_sidxdidx_configinfo_packing.sid0did0_systembase_config.setup
            .eth_default);
    bts_comm_applcmd_callback_assert(len > 0, out, "setip", "json dump fail\n\r");

    packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, param:", command, "OK");
    packet->txsize += json_printer_buf(out, bts_comm_applcmd_callback_jsonbuff, len);
    packet->txsize += json_printer_buf(out, "}", 1);
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_defaultip
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2018.12.27
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_defaultip(json_out_t *out, bts_comm_applcmd_packet_t *packet)
{
    int32_t len;
    // packet->rxbuffptr
    // packet->rxsize
    // packet->txbuffptr
    // packet->txsize

    SYS_PARAM_ETHDEFAULT = ethernet_config_factorydefault;
    // for competable
    krs_memcopy(SYS_PARAM_NETWORK.ip, SYS_PARAM_ETHDEFAULT.ip, sizeof(SYS_PARAM_NETWORK.ip));
    krs_memcopy(SYS_PARAM_NETWORK.gw, SYS_PARAM_ETHDEFAULT.gw, sizeof(SYS_PARAM_NETWORK.gw));


    //bts_comm_applcmd_callback_assert(mtd_app_store(mtdapp) == retOK, out, "defaultip",
    //                                   "defaultip save fail\n\r");

    bts_comm_applcmd_callback_log("defaultip save complete\n\r");

    len = sys_param_common_comm_ethernet_config_t_dump("", bts_comm_applcmd_callback_jsonbuff,
                                                       (void *)&SYS_PARAM_ETHDEFAULT);
    bts_comm_applcmd_callback_assert(len > 0, out, "defaultip", "json dump fail\n\r");

    packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, param:", "defaultip", "OK");
    packet->txsize += json_printer_buf(out, bts_comm_applcmd_callback_jsonbuff, len);
    packet->txsize += json_printer_buf(out, "}", 1);
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_scan
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2020.02.10
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_scan(json_out_t *out, bts_comm_applcmd_packet_t *packet)
{
    /*
     *         4.7.4 scan : broadcast only
                req : {"cmd":"scan"}
                +resp: {"cmd":"scan", "resp":"OK", "param":{"devuid":xxxxx, "serialnumber":xxxxx,
     "eth":{...}}}
     */
    int32_t len;
    // packet->rxbuffptr
    // packet->rxsize
    // packet->txbuffptr
    // packet->txsize
    char devuid_buff[20];
    system_devuid_str(devuid_buff, sizeof(devuid_buff));

    krs_log("devuid : %s\n\r", devuid_buff);

    len = sys_param_common_comm_ethernet_config_t_dump(
        "", bts_comm_applcmd_callback_jsonbuff,
        (void *)&sys_param_sidxdidx_configinfo_packing.sid0did0_systembase_config.setup
            .eth_default);

    packet->txsize = json_printf(
        out, "{cmd:%Q, resp:%Q, param:{devuid:%Q, serialnumber:%Q, eth:", "scan", "OK", devuid_buff,
        (void *)&sys_param_sidxdidx_configinfo_packing.sid0did0_systembase_config.setup.sensortype
            .serialnumber);

    packet->txsize += json_printer_buf(out, bts_comm_applcmd_callback_jsonbuff, len);
    packet->txsize += json_printer_buf(out, "}}", 2);

    //bts_comm_applcmd_callback_log("scan: %.*s\n", packet->txsize, packet->txbuffptr);

    return retOK;
}

/******************************************************************************
 * function name : bts_comm_applcmd_callback_recover
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2020.02.10
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_recover(json_out_t *out, bts_comm_applcmd_packet_t *packet)
{
    /*
     *         4.7.3 recover : broadcast only, no response code
                req : {"cmd":"recover", "param":{"devuid":<devuid>, "serialnumber":xxxxx,
     "ip":"192.168.10.150", "nm":"255.255.255.0", "gw":"192.168.10.1"..., "dhcp":0}} +resp :
     {"cmd":"recover", "resp":"OK"}
     */
    int32_t len;
    char_t command[32] = "";
    json_token_t t;
    json_token_t te;
    char serialnumberbuff[SYS_PARAM_STRLEN_MAX] = "";
    char devuid_buff[20] = "";
    char devuid_buff_received[20] = "";

    system_devuid_str(devuid_buff, sizeof(devuid_buff));

    // packet->rxbuffptr
    // packet->rxsize
    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s, param:%T}", command,
                     &t);
    bts_comm_applcmd_callback_assert(len == 2, out, "recover",
                                       "no command or param available\n\r");

    bts_comm_applcmd_callback_log("param token : %.*s\n\r", t.len, t.ptr);

    len = json_scanf((const char *)t.ptr, t.len, "{devuid:%s, serialnumber:%s, eth:%T}",
                     devuid_buff_received, serialnumberbuff, &te);

    bts_comm_applcmd_callback_log("eth token : %.*s\n\r", te.len, te.ptr);

    krs_log("recover : devuid is %s, received devuid is %s\n\r", devuid_buff, devuid_buff_received);
    krs_log("recover : serialnumber is %s\n\r", serialnumberbuff);
    krs_log("recover : eth info is : %.*s\n\r", te.len, te.ptr);


    if(sys_param_match_string(devuid_buff, devuid_buff_received) == retOK)
    {
        krs_log("recover accepted\n\r");
        // 1. set serial number
        strncpy((void *)&sys_param_sidxdidx_configinfo_packing.sid0did0_systembase_config.setup
                    .sensortype.serialnumber,
                serialnumberbuff, SYS_PARAM_STRLEN_MAX);
        // 2. set ip
        len = sys_param_common_comm_ethernet_config_t_loads(
            (char *)te.ptr, te.len,
            (void *)&sys_param_sidxdidx_configinfo_packing.sid0did0_systembase_config.setup
                .eth_default);

        //mtd_app_store(mtdapp);

        packet->txsize =
            json_printf(out, "{cmd:%Q, resp:%Q, param:{devuid:%Q}}", "recover", "OK", devuid_buff);
    }
    else
    {
        packet->txsize = 0;
    }
    return retOK;
}

/******************************************************************************
 * function name : bts_comm_applcmd_callback_memory_write_array
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2018.12.27
 *****************************************************************************/
void bts_comm_applcmd_callback_memory_write_array(char *str, int len, void *pvParam_local);
void bts_comm_applcmd_callback_memory_write_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    json_token_t t;
    uint8_t *bytebuffptr = (uint8_t *)pvParam_local;
    bts_comm_applcmd_callback_log("Parsing array: %.*s\n", len, str);

    for(i = 0; json_scanf_array_elem(str, len, "", i, &t) > 0; i++)
    {
        bts_comm_applcmd_callback_log("Index %ld, token [%.*s]\n", i, t.len, t.ptr);
        json_scanf((char *)t.ptr, t.len, "%d", bytebuffptr[i]);
    }
}
int32_t bts_comm_applcmd_callback_memory_write(json_out_t *out,
                                                 bts_comm_applcmd_packet_t *packet)
{
    uint32_t address;
    uint32_t size;
    int32_t len;
    uint8_t databuff[256] = {0};

    char_t command[32] = "";
    json_token_t t;


    // packet->rxbuffptr
    // packet->rxsize
    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s, param:%T}", command,
                     &t);
    bts_comm_applcmd_callback_assert(len == 2, out, "mwr", "no command or param available\n\r");

    len = json_scanf((const char *)t.ptr, t.len, "{address:%d, size:%d, bytes:%M}", &address, &size,
                     bts_comm_applcmd_callback_memory_write_array, (void *)databuff);
    bts_comm_applcmd_callback_assert(len > 0, out, "mwr", "json load fail\n\r");

    krs_memcopy((void *)address, (void *)databuff, size);
    packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q}", "mwr", "OK");
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_memory_read
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2018.12.27
 *****************************************************************************/
int32_t bts_comm_applcmd_callback_memory_read(json_out_t *out,
                                                bts_comm_applcmd_packet_t *packet)
{
    uint32_t address;
    uint32_t size;
    int32_t len;
    uint8_t databuff[256] = {0};

    char_t command[32] = "";
    json_token_t t;


    // packet->rxbuffptr
    // packet->rxsize
    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s, param:%T}", command,
                     &t);
    bts_comm_applcmd_callback_assert(len == 2, out, "mrd", "no command or param available\n\r");

    len = json_scanf((const char *)t.ptr, t.len, "{address:%d, size:%d}", &address, &size);
    bts_comm_applcmd_callback_assert(len > 0, out, "mrd", "json load fail\n\r");

    if(size > 256)
        size = 256;

    krs_memcopy((void *)databuff, (void *)address, size);
    packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, param:%M}", "mrd", "OK", json_printf_array,
                                 databuff, size, 1, "%d");
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_flash_cache_write
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2019.08.28
 *****************************************************************************/
/*
4.10 fwr : flash cache write by address
            req  : {"cmd":"fwr", "param":{"address":12345, "size":4, "encoding":<"base64","array">,
"bytes":[0]}} +resp: {"cmd":"fwr", "resp":"OK"} -resp: {"cmd":"fwr", "resp":"ERR", "param":"invalid
address"}
*/
void bts_comm_applcmd_callback_flash_cache_write_array(char *str, int len, void *pvParam_local);
void bts_comm_applcmd_callback_flash_cache_write_array(char *str, int len, void *pvParam_local)
{
    int32_t i;
    json_token_t t;
    uint8_t *bytebuffptr = (uint8_t *)pvParam_local;
    // bts_comm_applcmd_callback_log("Parsing array: %.*s\n", len, str);

    for(i = 0; json_scanf_array_elem(str, len, "", i, &t) > 0; i++)
    {
        // bts_comm_applcmd_callback_log("Index %ld, token [%.*s]\n", i, t.len, t.ptr);
        json_scanf((char *)t.ptr, t.len, "%d", &bytebuffptr[i]);
    }
}
void bts_comm_applcmd_callback_flash_cache_write_b64(char *str, int len, void *pvParam_local);
void bts_comm_applcmd_callback_flash_cache_write_b64(char *str, int len, void *pvParam_local)
{
    uint8_t *bytebuffptr = (uint8_t *)pvParam_local;
    // bts_comm_applcmd_callback_log("Parsing base64 binary: %.*s\n", len, str);
    krs_base64_decode((uint8_t *)str, (size_t)len, bytebuffptr, (size_t)5000);
}

int32_t bts_comm_applcmd_callback_flash_cache_write(json_out_t *out,
                                                      bts_comm_applcmd_packet_t *packet)
{
    uint32_t address;
    uint32_t size;
    int32_t len;
    uint8_t databuff[5000];

    char_t command[32];
    char_t encoding[32];
    json_token_t t;


    // packet->rxbuffptr
    // packet->rxsize
    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s, param:%T}", command,
                     &t);
    bts_comm_applcmd_callback_assert(len == 2, out, "fwr", "no command or param available\n\r");

    len = json_scanf((const char *)t.ptr, t.len, "{address:%d, size:%d, encoding:%s}", &address,
                     &size, encoding);
    bts_comm_applcmd_callback_assert(len > 0, out, "fwr",
                                       "json load fail, address, size, encoding\n\r");
    if(sys_param_match_string(encoding, "base64") == retOK)
    {
        len = json_scanf((const char *)t.ptr, t.len, "{bytes:%M}",
                         bts_comm_applcmd_callback_flash_cache_write_b64, (void *)databuff);
    }
    else
    {
        len = json_scanf((const char *)t.ptr, t.len, "{bytes:%M}",
                         bts_comm_applcmd_callback_flash_cache_write_array, (void *)databuff);
    }
    bts_comm_applcmd_callback_assert(len > 0, out, "fwr", "json load fail\n\r");


    bts_comm_applcmd_callback_log("flash_cache_addr: 0x%08X\n\r", address);
    bts_comm_applcmd_callback_log("flash_cache_size: 0x%08X\n\r", size);

    //bts_comm_applcmd_callback_assert(((address >= 0) && (address <= sizeof(mtd_cache))), out,
    //                                   "fwr", "invalid address\n\r");
    bts_comm_applcmd_callback_assert(((size > 0) && (size <= sizeof(databuff))), out, "fwr",
                                       "invalid size\n\r");
    //krs_memcopy(&mtd_cache[address], (void *)databuff, size);

    packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q}", "fwr", "OK");
    return retOK;
}

/******************************************************************************
 * function name : bts_comm_applcmd_callback_flash_cache_read
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2019.08.28
 *****************************************************************************/
/*
4.11 frd: flash cache read by address
        req  : {"cmd":"frd", "param":{"address":12345, "size":4, "encoding":<"base64","array">}
        +resp: {"cmd":"frd", "resp":"OK", "param":{"address":12345, "size":4,
"encoding":<"base64","array">, "bytes":[0]}} -resp: {"cmd":"frd", "resp":"ERR", "param":"invalid
address"}
*/
int32_t bts_comm_applcmd_callback_flash_cache_read(json_out_t *out,
                                                     bts_comm_applcmd_packet_t *packet)
{
    uint32_t address;
    uint32_t size;
    int32_t len;
    uint8_t databuff[5000] = {0};
    uint8_t b64buff[6144];
    int32_t b64size;
    char_t command[32] = "";
    char_t encoding[32] = "";

    json_token_t t;


    // packet->rxbuffptr
    // packet->rxsize
    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s, param:%T}", command,
                     &t);
    bts_comm_applcmd_callback_assert(len == 2, out, "frd", "no command or param available\n\r");

    len = json_scanf((const char *)t.ptr, t.len, "{address:%d, size:%d, encoding:%s}", &address,
                     &size, encoding);
    bts_comm_applcmd_callback_assert(len > 0, out, "frd", "json load fail\n\r");

    bts_comm_applcmd_callback_log("flash_cache_addr: 0x%08X\n\r", address);
    bts_comm_applcmd_callback_log("flash_cache_size: 0x%08X\n\r", size);

    //bts_comm_applcmd_callback_assert(((address >= 0) && (address <= sizeof(mtd_cache))), out,
    //                                   "fwr", "invalid address\n\r");
    bts_comm_applcmd_callback_assert(((size > 0) && (size <= sizeof(databuff))), out, "fwr",
                                       "invalid size\n\r");

    if(size > 4096)
        size = 4096;

    //krs_memcopy((void *)databuff, (void *)&mtd_cache[address], size);

    packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q, param:", "frd", "OK");

    if(sys_param_match_string(encoding, "base64") == retOK)
    {
        b64size = krs_base64_encode(databuff, size, b64buff, sizeof(b64buff));
        bts_comm_applcmd_callback_log("base64 len : %d, %.*s\n\r", b64size, b64size, b64buff);
        packet->txsize += json_printf(out, "{address:%d, size:%d, encoding:%Q, bytes:%Q}", address,
                                      size, encoding, b64buff);
    }
    else
    {
        strncpy(encoding, "array", sizeof(encoding));
        packet->txsize += json_printf(out, "{address:%d, size:%d, encoding:%Q, bytes:%M}", address,
                                      size, encoding, json_printf_array, databuff, size, 1, "%d");
    }
    packet->txsize += json_printer_buf(out, "}", 1);
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_flash_cache_store
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2019.08.28
 *****************************************************************************/
/*
4.12 fst : flash cache store
        req  : {"cmd":"fst", "param":{"address":12345, "size":4}
        +resp: {"cmd":"fst", "resp":"OK"}
        -resp: {"cmd":"fst", "resp":"ERR", "param":"invalid address"}
        -resp: {"cmd":"fst", "resp":"PENDING", "param":{"job":"erase", "address":12345}}
        -resp: {"cmd":"fst", "resp":"PENDING", "param":{"job":"write", "address":12345}}
*/
int32_t bts_comm_applcmd_callback_flash_cache_store(json_out_t *out,
                                                      bts_comm_applcmd_packet_t *packet)
{
    uint32_t address;
    uint32_t size;
    uint32_t remainsize;
    uint32_t offset;
    int32_t len;
    int32_t ret;
    f32_t progress;
    f32_t totalsize;

    char_t command[32] = "";
    json_token_t t;


    // packet->rxbuffptr
    // packet->rxsize
    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s, param:%T}", command,
                     &t);
    bts_comm_applcmd_callback_assert(len == 2, out, "fst", "no command or param available\n\r");

    len = json_scanf((const char *)t.ptr, t.len, "{address:%d, size:%d}", &address, &size);
    bts_comm_applcmd_callback_assert(len > 0, out, "fst", "json load fail\n\r");

    bts_comm_applcmd_callback_log("flash_cache_addr: 0x%08X\n\r", address);
    bts_comm_applcmd_callback_log("flash_cache_size: 0x%08X\n\r", size);

    //bts_comm_applcmd_callback_assert(((address >= 0) && (address <= sizeof(mtd_cache))), out,
    //                                   "fst", "invalid address\n\r");
    //bts_comm_applcmd_callback_assert(((size > 0) && (size <= sizeof(mtd_cache))), out, "fst",
    //                                   "invalid size\n\r");

    remainsize = size;
    totalsize = (f32_t)size;
    offset = 0;
    progress = 0;
    while(remainsize > 0)
    {
        if(remainsize <= 65536)
        {
            size = remainsize;
        }
        else
        {
            size = 65536;
        }

        //ret = mtdapp->mtd->memdrv.mtd_lowlevel_erase(address + offset, size);
        ret = retFail;
        bts_comm_applcmd_callback_assert(ret == retOK, out, "fst", "flash erase fail\n\r");
        bts_comm_applcmd_callback_log("flash_erase success\n\r");

        //ret = mtdapp->mtd->memdrv.mtd_lowlevel_write((uint8_t *)&mtd_cache[address + offset],
        //                                             (uint32_t)(address + offset), (size_t)size);
        ret = retFail;
        bts_comm_applcmd_callback_assert(ret == retOK, out, "fst", "flash store fail\n\r");

        remainsize -= size;
        offset += size;

        progress = 100.0f * (f32_t)offset / totalsize;
        krs_log("flash_write progress : %.1f%%\n\r", progress);

        json_out_t commandrespout =
            JSON_OUT_BUF(packet->txbuffptr, bts_COMM_APPLCMD_CALLBACK_JSONBUFFSIZE);
        packet->txsize = json_printf(&commandrespout, "{cmd:%Q, resp:%Q, param:{progress:%.1f}}",
                                     "fst", "RCRP", progress);
        bts_comm_applcmd_sendresponse(packet);
    }

    bts_comm_applcmd_callback_log("flash_write success\n\r");

    packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q}", "fst", "OK");
    return retOK;
}

/******************************************************************************
 * function name : bts_comm_applcmd_callback_flash_cache_load
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2019.08.28
 *****************************************************************************/
/*
4.12 fld : flash cache load
        req  : {"cmd":"fld", "param":{"address":12345, "size":4, "cs":"md5"}
        +resp: {"cmd":"fld", "resp":"OK", "param":{"cs":"md5", "value":[]}}
        -resp: {"cmd":"fld", "resp":"ERR", "param":"invalid address"}
*/
int32_t bts_comm_applcmd_callback_flash_cache_load(json_out_t *out,
                                                     bts_comm_applcmd_packet_t *packet)
{
    uint32_t address;
    uint32_t size;
    int32_t len;
    int32_t ret;
    uint8_t cstype[32];
    uint8_t md5_cs[BTS_MD5_CHECKSUM_SIZE];
    char_t command[32] = "";
    json_token_t t;


    // packet->rxbuffptr
    // packet->rxsize
    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s, param:%T}", command,
                     &t);
    bts_comm_applcmd_callback_assert(len == 2, out, "fld", "no command or param available\n\r");

    len = json_scanf((const char *)t.ptr, t.len, "{address:%d, size:%d, cs:%s}", &address, &size,
                     &cstype);
    bts_comm_applcmd_callback_assert(len > 0, out, "fld", "json load fail\n\r");

    bts_comm_applcmd_callback_log("addr: 0x%08X\n\r", address);
    bts_comm_applcmd_callback_log("size: 0x%08X\n\r", size);

    //bts_comm_applcmd_callback_assert(((address >= 0) && (address <= sizeof(mtd_cache))), out,
    //                                   "fld", "invalid address\n\r");
    //bts_comm_applcmd_callback_assert(((size > 0) && (size <= sizeof(mtd_cache))), out, "fld",
    //                                   "invalid size\n\r");

    //ret = mtdapp->mtd->memdrv.mtd_lowlevel_read((uint8_t *)&mtd_cache[address], (uint32_t)address,
    //                                            (size_t)size);
    ret = retFail;
    bts_comm_applcmd_callback_assert(ret == retOK, out, "fld", "flash load fail\n\r");

    bts_comm_applcmd_callback_log("flash_read success\n\r");

    if(sys_param_match_string((char *)cstype, "md5") == retOK)
    {
        //bts_md5((uint8_t *)&mtd_cache[address], size, md5_cs);
        if(bts_COMM_CALLBACK_LOG_EN != 0)
            krs_log_arruint8X(md5_cs, BTS_MD5_CHECKSUM_SIZE);
        packet->txsize =
            json_printf(out, "{cmd:%Q, resp:%Q, param:{cs:%Q, value:%M}}", "fld", "OK", cstype,
                        json_printf_array, md5_cs, BTS_MD5_CHECKSUM_SIZE, 1, "%d");
    }
    else
    {
        packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q}", "fld", "OK");
    }
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_applcmd_callback_flash_cache_calchecksum
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2019.08.28
 *****************************************************************************/
/*
4.12 fst : flash cache cal checksum
        req  : {"cmd":"fcs", "param":{"address":12345, "size":4, load:<true,false>,"cs":<"md5">}
        +resp: {"cmd":"fcs", "resp":"OK", "param":{"md5":"<hexdecimal value>"}}
        -resp: {"cmd":"fcs", "resp":"ERR", "param":"invalid address"}
*/
int32_t bts_comm_applcmd_callback_flash_cache_calchecksum(json_out_t *out,
                                                            bts_comm_applcmd_packet_t *packet)
{
    uint32_t address;
    uint32_t size;
    int32_t len;
    int32_t ret;
    uint8_t cstype[32];
    uint8_t md5_cs[BTS_MD5_CHECKSUM_SIZE];
    char_t command[32] = "";
    uint8_t load_enable;
    json_token_t t;

    load_enable = 0;
    // packet->rxbuffptr
    // packet->rxsize
    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s, param:%T}", command,
                     &t);
    bts_comm_applcmd_callback_assert(len == 2, out, command, "no command or param available\n\r");

    len = json_scanf((const char *)t.ptr, t.len, "{address:%d, size:%d, load:%B, cs:%s}", &address,
                     &size, &load_enable, &cstype);
    bts_comm_applcmd_callback_assert(len > 0, out, command, "json load fail\n\r");

    bts_comm_applcmd_callback_log("addr: 0x%08X\n\r", address);
    bts_comm_applcmd_callback_log("size: 0x%08X\n\r", size);

    //bts_comm_applcmd_callback_assert(((address >= 0) && (address <= sizeof(mtd_cache))), out,
    //                                   command, "invalid address\n\r");
    //bts_comm_applcmd_callback_assert(((size > 0) && (size <= sizeof(mtd_cache))), out, command,
    //                                   "invalid size\n\r");

    if(load_enable != 0)
    {
        //ret = mtdapp->mtd->memdrv.mtd_lowlevel_read((uint8_t *)&mtd_cache[address],
        //                                            (uint32_t)address, (size_t)size);
        ret = retFail;
        bts_comm_applcmd_callback_assert(ret == retOK, out, command, "flash load fail\n\r");
        bts_comm_applcmd_callback_log("flash_read success\n\r");
    }

    if(sys_param_match_string((char *)cstype, "md5") == retOK)
    {
        //bts_md5((uint8_t *)&mtd_cache[address], size, md5_cs);
        krs_log_arruint8X(md5_cs, BTS_MD5_CHECKSUM_SIZE);
        packet->txsize =
            json_printf(out, "{cmd:%Q, resp:%Q, param:{cs:%Q, value:%M}}", command, "OK", cstype,
                        json_printf_array, md5_cs, BTS_MD5_CHECKSUM_SIZE, 1, "%d");
    }
    else
    {
        packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q}", command, "OK");
    }
    return retOK;
}

/******************************************************************************
 * function name : bts_comm_applcmd_callback_reset
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *out description
 * \param1 *packet description
 * \return int32_t description
 * modification date : 2019.03.08
 *****************************************************************************/
/*
        5.1 reset : reset
                req  : {"cmd":"reset"}
                +resp: {"cmd":"reset", "resp":"OK"}
                -resp: {"cmd":"reset", "resp":"ERR", "param":"busy state"}
 */
int32_t bts_comm_applcmd_callback_reset(json_out_t *out, bts_comm_applcmd_packet_t *packet)
{
    int32_t len;
    char_t command[32] = "";


    // packet->rxbuffptr
    // packet->rxsize
    len = json_scanf((const char *)packet->rxbuffptr, packet->rxsize, "{cmd:%s}", command);
    bts_comm_applcmd_callback_assert(len == 1, out, "reset", "no command or param available\n\r");

    //taskmgr_request_system_restart();
    krs_log("reset not executed.\n");
    packet->txsize = json_printf(out, "{cmd:%Q, resp:%Q}", "reset", "OK");
    return retOK;
}

/* end of file */
