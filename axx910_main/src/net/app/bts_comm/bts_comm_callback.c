/************************************************************************
| Project Name: bts_comm_callback
|    File Name: bts_comm_callback.c
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
| 2017.09.11   0.0   SKJ   Creation;
|***********************************************************************/


/* include system primitive types */
#include "bts.h"

/* include system driver header */


/* include system bsp header */


/* include system application header */
//#include "drivers.h"
//#include "taskmgr.h"
#include "thread_manager.h"
#include "system.h"

/* final include module header */
#include "bts_comm.h"
#include "bts_comm_appl.h"
#include "bts_comm_callback.h"
#include "bts_comm_cfg.h"
#include "bts_comm_odt.h"
#include "bts_comm_status.h"
#include "bts_comm_service.h"
//#include "modulation.h"
//#include "mtd_app.h"
#include "os.h"
#include "sys_param.h"


#define bts_COMM_CALLBACK_LOG_EN SYS_PARAM_CONSOLELOG.bts_log_module_comm_appl_callback_en

#if bts_COMM_CALLBACK_DEBUG == 1
#define bts_comm_callback_log krs_log        /*\
    if(bts_COMM_CALLBACK_LOG_EN != 0) \
    krs_log*/
#else
#define bts_comm_callback_log krs_log_dummy
#endif


extern os_sem_t sem_disconnected_socket;
extern uint8_t restart_flag;

void bts_comm_negative_response(int32_t sid, int32_t did, char_t *msg);


int32_t bts_comm_callback_connect(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_disconnect(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_get_status(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_get_daq_list_info(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_read_data_by_id(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_write_data_by_id(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_mtdapp_save_clear(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_mtdapp_format(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_mtdapp_save(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_start_stop_daq_list(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_start_stop_synch(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_sync(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_user_command(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_user_command_client_present(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_user_command_flash_block_update(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_user_command_flash_cache_update(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_user_command_flash_cache_store(bts_comm_packet_t *packetptr);
int32_t bts_comm_callback_reset(bts_comm_packet_t *packetptr);


bts_comm_cmd_table_t bts_comm_cmd_table[] = {
    {IR24XCOMMCMD_CONNECT, bts_comm_callback_connect},
    {IR24XCOMMCMD_DISCONNECT, bts_comm_callback_disconnect},
    {IR24XCOMMCMD_GET_STATUS, bts_comm_callback_get_status},
    {IR24XCOMMCMD_GET_DAQ_LIST_INFO, bts_comm_callback_get_daq_list_info},
    {IR24XCOMMCMD_USER_CMD, bts_comm_callback_user_command},
    {IR24XCOMMCMD_GET_CAL_PAGE, bts_comm_callback_read_data_by_id},
    {IR24XCOMMCMD_SET_CAL_PAGE, bts_comm_callback_write_data_by_id},
    {IR24XCOMMCMD_COPY_CAL_PAGE, bts_comm_callback_mtdapp_save_clear},

    {IR24XCOMMCMD_SHORT_UPLOAD, bts_comm_callback_read_data_by_id},
    {IR24XCOMMCMD_SHORT_DOWNLOAD, bts_comm_callback_write_data_by_id},
    {IR24XCOMMCMD_PROGRAM_FORMAT, bts_comm_callback_mtdapp_format},
    {IR24XCOMMCMD_PROGRAM, bts_comm_callback_mtdapp_save},
	{IR24XCOMMCMD_PROGRAM_RESET, bts_comm_callback_reset},
    {IR24XCOMMCMD_START_STOP_DAQ_LIST, bts_comm_callback_start_stop_daq_list},
    {IR24XCOMMCMD_START_STOP_SYNCH, bts_comm_callback_start_stop_synch},
    {IR24XCOMMCMD_SYNCH, bts_comm_callback_sync},
    {IR24XCOMMCMD_END, NULL}};
/* declare static variables */


static char bts_comm_callback_jsonbuff[SYS_PARAM_JSON_BUFFER_SIZE];

/* static function prototypes */

/******************************************************************************
 * function name : bts_comm_callback_connect
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetptr description
 * \return int32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
int32_t bts_comm_callback_connect(bts_comm_packet_t *packetptr)
{
    uint8_t txbuff[8];


    // uint8_t *cmdbuff = (uint8_t *)packetptr->cro.databuffptr;

    krs_assert(packetptr->cro.header.u8pid > IR24XCOMMCMD_END);

    bts_comm_callback_log("bts_comm_connect\n\r");


    // flushing txqueue
    bts_comm_flush_txqueue();

    Ir24xCommSetConnected();
    bts_comm_send_cro(0, IR24XCOMMRESP_RES, txbuff);

    return (retOK);
}


/******************************************************************************
 * function name : bts_comm_callback_disconnect
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetptr description
 * \return int32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
int32_t bts_comm_callback_disconnect(bts_comm_packet_t *packetptr)
{
    uint8_t txbuff[2];

    krs_assert(packetptr->cro.header.u8pid > IR24XCOMMCMD_END);

    bts_comm_callback_log("bts_comm_disconnect\n\r");

    //mtd_app_store(mtdapp);


    Ir24xCommSetDisconnectRequested();

    bts_comm_send_cro(0, IR24XCOMMRESP_RES, txbuff);


    if(restart_flag == true)
    {
        os_sem_give(sem_disconnected_socket);
    }


    return (retOK);

    // error list
    // bts_comm_send_error(IR24XCOMMRESP_ERR_CMD_BUSY);
    // bts_comm_send_error(IR24XCOMMRESP_ERR_PGM_ACTIVE);
}


/******************************************************************************
 * function name : bts_comm_callback_get_status
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *packetptr description
 * \return0 int32_t description
 * modification date : 2020.04.06
 *****************************************************************************/
int32_t bts_comm_callback_get_status(bts_comm_packet_t *packetptr)
{
    int32_t len;

    krs_assert(packetptr->cro.header.u8pid > IR24XCOMMCMD_END);
    bts_comm_callback_log("bts_comm_callback_get_status\n\r");

    /* device unique ID */
    len = system_get_status_to_json(bts_comm_callback_jsonbuff,
                                    sizeof(bts_comm_callback_jsonbuff));

    if(len == 0)
    {
        bts_comm_callback_log("sys_param_systeminfo_t_dump fail\n\r");
        bts_comm_send_error(IR24XCOMMRESP_ERR_DAQ_CONFIG);
        bts_comm_negative_response(IR24XCOMMCMD_GET_STATUS, 0,
                                     "sys_param_systeminfo_t_dump fail");
        return retOK;
    }
    else
    {
    //    bts_comm_callback_log("json data len : %ld\n\r", len);
    //    bts_comm_callback_log("json data : %.*s\n\r", (int)len,
    //                            (const char *)bts_comm_callback_jsonbuff);
        bts_comm_send_cro(len, IR24XCOMMRESP_RES, bts_comm_callback_jsonbuff);
    }

    return retOK;
}


// This command is used to synchronize command execution after timeout conditions. The
// SYNCH command will always have a negative response with the error code
// ERR_CMD_SYNCH. There is no other command using this error code, therefore the
// response to a SYNCH command may be distinguished from the response to any other
// command
/******************************************************************************
 * function name : bts_comm_callback_sync
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetptr description
 * \return int32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
int32_t bts_comm_callback_sync(bts_comm_packet_t *packetptr)
{
    // uint8_t *cmdbuff = (uint8_t *)packetptr->cro.databuffptr;
    bts_comm_status_start_stop_synch_mode_t synchmode_restore;

    krs_assert(packetptr->cro.header.u8pid > IR24XCOMMCMD_END);

    bts_comm_callback_log("bts_comm_sync\n\r");


    synchmode_restore = Ir24xCommGetStartStopSynchMode();

    os_safe(Ir24xCommSetStartStopSynchModeStop(); Ir24xCommSetDaqStatusIdle(););

    bts_comm_flush_txqueue();
    os_sleep(100);

    os_safe(Ir24xCommSetDaqStatusActive(); Ir24xCommSetStartStopSynchMode(synchmode_restore););


    bts_comm_send_event(IR24XCOMMRESP_ERR_CMD_SYNCH);

    os_sem_give(sem_bts_comm_status_daq_start);

    return (retOK);

    // error list
    // bts_comm_send_error(IR24XCOMMRESP_ERR_CMD_SYNCH);
    // bts_comm_send_error(IR24XCOMMRESP_ERR_CMD_UNKNOWN);
}


/******************************************************************************
 * function name : bts_comm_callback_start_stop_daq_list
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetptr description
 * \return int32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
int32_t bts_comm_callback_start_stop_daq_list(bts_comm_packet_t *packetptr)
{
    int32_t ret;
    uint8_t txbuff[2];
    uint8_t *cmdbuff = (uint8_t *)packetptr->cro.databuffptr;
    uint32_t datalen = packetptr->cro.datasize;

    krs_assert(packetptr->cro.header.u8pid > IR24XCOMMCMD_END);

    bts_comm_callback_log("bts_comm_start_stop_daq_list\n\r");


    ret = bts_comm_appl_dataset_set_daqstartstop(cmdbuff, datalen);
    if(ret == retOK)
    {
        bts_comm_send_cro(0, IR24XCOMMRESP_RES, txbuff);
    }
    else
    {
        bts_comm_send_error(IR24XCOMMRESP_ERR_OUT_OF_RANGE);
    }


    return (retOK);
    // error list
    // bts_comm_send_error(IR24XCOMMRESP_ERR_CMD_BUSY);
    // bts_comm_send_error(IR24XCOMMRESP_ERR_PGM_ACTIVE);
    // bts_comm_send_error(IR24XCOMMRESP_ERR_CMD_SYNTAX);
    // bts_comm_send_error(IR24XCOMMRESP_ERR_OUT_OF_RANGE);
    // bts_comm_send_error(IR24XCOMMRESP_ERR_ACCESS_LOCKED);
    // bts_comm_send_error(IR24XCOMMRESP_ERR_MODE_NOT_VALID);
    // bts_comm_send_error(IR24XCOMMRESP_ERR_DAQ_CONFIG);
    // bts_comm_send_error(IR24XCOMMRESP_ERR_RESOURCE_TEMPORARY_NOT_ACCESSIBLE);
}


/******************************************************************************
 * function name : bts_comm_callback_start_stop_synch
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetptr description
 * \return int32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
int32_t bts_comm_callback_start_stop_synch(bts_comm_packet_t *packetptr)
{
    uint8_t txbuff[2];

    uint8_t *cmdbuff = (uint8_t *)packetptr->cro.databuffptr;

    krs_assert(packetptr->cro.header.u8pid > IR24XCOMMCMD_END);

    bts_comm_callback_log("bts_comm_start_stop_synch\n\r");

    // set to sync mode
    os_safe(
        if(cmdbuff[0] < bts_comm_status_start_stop_synch_mode_max) {
            Ir24xCommSetStartStopSynchMode(cmdbuff[0]);
        } else { Ir24xCommSetStartStopSynchModeStop(); });

    // TX queue Clear if stop request received.
    if(Ir24xCommGetIsStartStopSynchModeStopAll())
    {
        bts_comm_callback_log("bts_comm_callback_start_stop_synch: tx queue flushing.\n\r");
        bts_comm_flush_txqueue();
        os_sleep(10);
    }


    bts_comm_callback_log("Ir24xCommGetStartStopSynchMode() : %d\n\r",
                            Ir24xCommGetStartStopSynchMode());
    // send positive response
    bts_comm_send_cro(0, IR24XCOMMRESP_RES, txbuff);


    return (retOK);
    // error list
    // bts_comm_send_error(IR24XCOMMRESP_ERR_CMD_BUSY);
    // bts_comm_send_error(IR24XCOMMRESP_ERR_PGM_ACTIVE);
    // bts_comm_send_error(IR24XCOMMRESP_ERR_CMD_SYNTAX);
    // bts_comm_send_error(IR24XCOMMRESP_ERR_ACCESS_LOCKED);
    // bts_comm_send_error(IR24XCOMMRESP_ERR_MODE_NOT_VALID);
    // bts_comm_send_error(IR24XCOMMRESP_ERR_DAQ_CONFIG);
    // bts_comm_send_error(IR24XCOMMRESP_ERR_RESOURCE_TEMPORARY_NOT_ACCESSIBLE);
}


/******************************************************************************
 * function name : bts_comm_callback_get_daq_list_info
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetptr description
 * \return int32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
int32_t bts_comm_callback_get_daq_list_info(bts_comm_packet_t *packetptr)
{
    int32_t len;

    krs_assert(packetptr->cro.header.u8pid > IR24XCOMMCMD_END);

    bts_comm_callback_log("bts_comm_callback_get_daq_list_info\n\r");

    len = bts_comm_appl_common_get_daqinfo(bts_comm_callback_jsonbuff,
                                             sizeof(bts_comm_callback_jsonbuff));
    if(len == 0)
    {
        bts_comm_callback_log("generating daqinfo is fail\n\r");
        bts_comm_send_error(IR24XCOMMRESP_ERR_DAQ_CONFIG);
    }
    else
    {

#if bts_COMM_CALLBACK_DEBUG == 1
        //bts_comm_callback_log("daq_list_info json len is %ld\n\r", len);
        //bts_comm_callback_log("%.*s\n\r", len, bts_comm_callback_jsonbuff);
        //cJSON* jsonbuff = cJSON_Parse(bts_comm_callback_jsonbuff);
        //bts_comm_callback_log("%s\n", cJSON_Print(jsonbuff));
#endif
        bts_comm_send_cro(len, IR24XCOMMRESP_RES, bts_comm_callback_jsonbuff);
    }


    return retOK;
}


/******************************************************************************
 * function name : bts_comm_callback_read_data_by_id
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetptr description
 * \return int32_t description
 * modification date : 2018.08.09
 *****************************************************************************/
int32_t bts_comm_callback_read_data_by_id(bts_comm_packet_t *packetptr)
{
    uint8_t *cmdbuff = (uint8_t *)packetptr->cro.databuffptr;
    int32_t datalen = (int32_t)packetptr->cro.datasize;
    int32_t ret;
    int32_t sid;
    int32_t did;
    int32_t len;
    sys_param_jsontype_info_t *jsoninfo;


    krs_assert(packetptr->cro.header.u8pid > IR24XCOMMCMD_END);

#if bts_COMM_CALLBACK_DEBUG == 1
    bts_comm_callback_log("bts_comm_callback_read_data_by_id:\n\r");
    //bts_comm_callback_log("%.*s\n\r", datalen, (const char *)cmdbuff);
    //cJSON* jsonbuff = cJSON_Parse(cmdbuff);
    //bts_comm_callback_log("%s\n", cJSON_Print(jsonbuff));
#endif

    ret = json_scanf((const char *)cmdbuff, datalen, "{sid:%d, did:%d}", &sid, &did);

#if bts_COMM_CALLBACK_DEBUG == 1
    bts_comm_callback_log("json_scanf conversion count:%d\n\r", ret);
#endif

    if(ret != 2)
    {
        bts_comm_callback_log("bts_comm_callback_read_data_by_id: no sid or did\n\r");
        bts_comm_negative_response(-1, -1, "no sid or did");
        return retOK;
    }

#if bts_COMM_CALLBACK_DEBUG == 1
    bts_comm_callback_log("received : sid:%d, did:%d\n\r", sid, did);
#endif

    jsoninfo = sys_param_jsontype_info_find(sid, did, -1);
    if(jsoninfo == NULL)
    {
        bts_comm_callback_log("not supported sid:%ld, did:%ld\n\r", sid, did);
        bts_comm_negative_response(sid, did, "not supported sid or did");
        return retOK;
    }

    bts_comm_callback_log("bts_comm_callback_read_data_by_id: %.*s\n\r",

                            (int)jsoninfo->type_name_len, jsoninfo->type_name);

    len = jsoninfo->dumpfunc("", bts_comm_callback_jsonbuff, jsoninfo->pvParam);
    //len = jsoninfo->dumpfunc("", bts_comm_callback_jsonbuff, jsoninfo->pvParamDefault);

    if(len == 0)
    {
        bts_comm_callback_log("bts_comm_callback_read_data_by_id: %s dump fail\n\r",
                                jsoninfo->type_name);
        bts_comm_negative_response(sid, did, "json dump error");
        return retOK;
    }
    else
    {
#if bts_COMM_CALLBACK_DEBUG == 1
        bts_comm_callback_log("json dump length is %d\n\r", len);
#endif
        bts_comm_send_cro(len, IR24XCOMMRESP_RES, bts_comm_callback_jsonbuff);
    }

    return retOK;
}


/******************************************************************************
 * function name : bts_comm_callback_write_data_by_id
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetptr description
 * \return int32_t description
 * modification date : 2018.08.09
 *****************************************************************************/
int32_t bts_comm_callback_write_data_by_id(bts_comm_packet_t *packetptr)
{
    uint8_t *cmdbuff = (uint8_t *)packetptr->cro.databuffptr;
    int32_t datalen = (int32_t)packetptr->cro.datasize;
    int32_t ret;
    int32_t sid;
    int32_t did;
    int32_t len;
    sys_param_jsontype_info_t *jsoninfo;

    krs_assert(packetptr->cro.header.u8pid > IR24XCOMMCMD_END);


    bts_comm_callback_log("bts_comm_callback_write_data_by_id: %dbytes received\n\r", datalen);
    //bts_comm_callback_log("%.*s\n\r", datalen, (const char *)cmdbuff);
    //cJSON* jsonbuff = cJSON_Parse(cmdbuff);
    //bts_comm_callback_log("%s\n", cJSON_Print(jsonbuff));

    ret = json_scanf((const char *)cmdbuff, datalen, "{sid:%d, did:%d}", &sid, &did);
    if(ret != 2)
    {
        bts_comm_callback_log("bts_comm_callback_write_data_by_id: no sid or did\n\r");
        bts_comm_negative_response(-1, -1, "no sid or did");
        return retOK;
    }
    // eth_receive error
    bts_comm_callback_log("received : sid:%d, did:%d\n\r", sid, did);

    jsoninfo = sys_param_jsontype_info_find(sid, did, -1);
    if(jsoninfo == NULL)
    {
        bts_comm_callback_log("ID finding is fail [sid:%d, did:%d]\n\r", sid, did);
        bts_comm_negative_response(sid, did, "json load error");
        return retOK;
    }

    len = jsoninfo->loadfunc((char *)cmdbuff, datalen, jsoninfo->pvParam);
    if(len == 0)
    {
        bts_comm_callback_log("json to %s is fail\n\r", jsoninfo->type_name);
        bts_comm_negative_response(sid, did, "json load error");
        return retOK;
    }

    if(sid == 8)
    {
        //if(mtd_app_store(mtdapp) == retOK)
        {
            // mtd_app_print_record(mtdapp);
            bts_comm_callback_log("save sid8 config data success\n\r");
        }
    }

    bts_comm_service_callfunc(sid, did, jsoninfo->pvParam);

    bts_comm_callback_log("bts_comm_callback_write_data_by_id success\n\r");
    bts_comm_send_cro(0, IR24XCOMMRESP_RES, bts_comm_callback_jsonbuff);

    return retOK;
}


/******************************************************************************
 * function name : bts_comm_negative_response
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 sid description
 * \param1 did description
 * \param2 *msg description
 * \return void description
 * modification date : 2018.08.09
 *****************************************************************************/
void bts_comm_negative_response(int32_t sid, int32_t did, char_t *msg)
{
    int32_t len = 0;
    sys_param_comm_negative_response_t resp;
    resp.sid = sid;
    resp.did = did;
    strncpy(resp.error, msg, sizeof(resp.error) - 1);
    len = sys_param_comm_negative_response_t_dump("", bts_comm_callback_jsonbuff, &resp);
    bts_comm_send_cro(len, IR24XCOMMRESP_ERR, bts_comm_callback_jsonbuff);
}


/******************************************************************************
 * function name : bts_comm_callback_mtdapp_format
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetptr description
 * \return int32_t description
 * modification date : 2018.08.09
 *****************************************************************************/
int32_t bts_comm_callback_mtdapp_format(bts_comm_packet_t *packetptr)
{
    //if(mtd_app_load_default(mtdapp) == retOK)
    if(retFail)
    {
        bts_comm_send_cro(0, IR24XCOMMRESP_RES, bts_comm_callback_jsonbuff);
    }
    else
    {
        bts_comm_send_error(IR24XCOMMRESP_ERR_GENERIC);
    }
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_callback_mtdapp_save
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetptr description
 * \return int32_t description
 * modification date : 2018.08.09
 *****************************************************************************/
int32_t bts_comm_callback_mtdapp_save(bts_comm_packet_t *packetptr)
{
    //if(mtd_app_store(mtdapp) == retOK)
    if(retFail)
    {
        bts_comm_send_cro(0, IR24XCOMMRESP_RES, bts_comm_callback_jsonbuff);
    }
    else
    {
        bts_comm_send_error(IR24XCOMMRESP_ERR_GENERIC);
    }
    return retOK;
}



/******************************************************************************
 * function name : bts_comm_callback_reset
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetptr description
 * \return int32_t description
 * modification date : 2020.09.02
 *****************************************************************************/
int32_t bts_comm_callback_reset(bts_comm_packet_t *packetptr)
{
	//taskmgr_request_system_restart();
    bts_comm_callback_log("bts_comm_callback_reset() called, but nothing doing.\n");
	return retOK;
}



/******************************************************************************
 * function name : bts_comm_callback_mtdapp_save_clear
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetptr description
 * \return int32_t description
 * modification date : 2018.08.09
 *****************************************************************************/
int32_t bts_comm_callback_mtdapp_save_clear(bts_comm_packet_t *packetptr)
{
    uint8_t *cmdbuff = (uint8_t *)packetptr->cro.databuffptr;
    int32_t datalen = (int32_t)packetptr->cro.datasize;
    int32_t ret;
    char_t mtdcmd[32] = {0};


    krs_assert(packetptr->cro.header.u8pid > IR24XCOMMCMD_END);


    bts_comm_callback_log("bts_comm_callback_mtdapp_save_clear:\n\r");
    bts_comm_callback_log("%.*s\n\r", datalen, (const char *)cmdbuff);

    ret = json_scanf((const char *)cmdbuff, datalen, "{cmd:%32s}", mtdcmd);

    bts_comm_callback_log("json_scanf conversion count:%d\n\r", ret);

    if(ret != 1)
    {
        bts_comm_callback_log("bts_comm_callback_mtdapp_save_clear: no cmd\n\r");
        bts_comm_send_error(IR24XCOMMRESP_ERR_GENERIC);
        return retOK;
    }
    bts_comm_callback_log("bts_comm_callback_mtdapp_save_clear: received cmd:%s\n\r", mtdcmd);

    if(sys_param_match_string(mtdcmd, "erase") == retOK)
    {
        //if(mtd_app_load_default(mtdapp) == retOK)
        if(retFail)
        {
            bts_comm_send_cro(0, IR24XCOMMRESP_RES, bts_comm_callback_jsonbuff);
            bts_comm_callback_log(
                "bts_comm_callback_mtdapp_save_clear: clear and load default success\n\r");
        }
        else
        {
            bts_comm_send_error(IR24XCOMMRESP_ERR_GENERIC);
            bts_comm_callback_log("bts_comm_callback_mtdapp_save_clear: clear fail\n\r");
        }
    }
    else if(sys_param_match_string(mtdcmd, "save") == retOK)
    {
        //if(mtd_app_store(mtdapp) == retOK)
        if(retFail)
        {
            bts_comm_send_cro(0, IR24XCOMMRESP_RES, bts_comm_callback_jsonbuff);
            bts_comm_callback_log("bts_comm_callback_mtdapp_save_clear: save success\n\r");
        }
        else
        {
            bts_comm_send_error(IR24XCOMMRESP_ERR_GENERIC);
            bts_comm_callback_log("bts_comm_callback_mtdapp_save_clear: save fail\n\r");
        }
    }
    else
    {
        bts_comm_send_error(IR24XCOMMRESP_ERR_CMD_SYNTAX);
        bts_comm_callback_log("bts_comm_callback_mtdapp_save_clear: not supported cmd\n\r");
    }
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_callback_user_command
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetptr description
 * \return int32_t description
 * modification date : 2018.08.09
 *****************************************************************************/
int32_t bts_comm_callback_user_command(bts_comm_packet_t *packetptr)
{
    int32_t ret = retOK;
    uint8_t *cmdbuff = (uint8_t *)packetptr->cro.databuffptr;

    krs_assert(packetptr->cro.header.u8pid > IR24XCOMMCMD_END);
    bts_comm_callback_log("bts_comm_callback_user_command\n\r");

    if(cmdbuff[0] == IR24XCOMMCMD_USER_CMD_CLIENT_PRESENT)
    {
        ret = bts_comm_callback_user_command_client_present(packetptr);
    }
    else if(cmdbuff[0] == IR24XCOMMCMD_USER_CMD_FLASH_BLOCK_UPDATE)
    {
        ret = bts_comm_callback_user_command_flash_block_update(packetptr);
    }
    else if(cmdbuff[0] == IR24XCOMMCMD_USER_CMD_FLASH_CACHE_UPDATE)
    {
        ret = bts_comm_callback_user_command_flash_cache_update(packetptr);
    }
    else if(cmdbuff[0] == IR24XCOMMCMD_USER_CMD_FLASH_CACHE_STORE)
    {
        ret = bts_comm_callback_user_command_flash_cache_store(packetptr);
    }
    else
    {
        bts_comm_send_error(IR24XCOMMRESP_ERR_CMD_UNKNOWN);
    }
    return ret;
}


/******************************************************************************
 * function name : bts_comm_callback_user_command_client_present
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetptr description
 * \return int32_t description
 * modification date : 2018.08.09
 *****************************************************************************/
int32_t bts_comm_callback_user_command_client_present(bts_comm_packet_t *packetptr)
{
    uint8_t txbuff[2];
    uint8_t *cmdbuff = (uint8_t *)packetptr->cro.databuffptr;
    bts_comm_callback_log("bts_comm_callback_user_command_client_present\n\r");
    if(cmdbuff[1] == 0x01)
    {
        bts_comm_send_cro(0, IR24XCOMMRESP_RES, txbuff);
    }
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_callback_user_command_flash_block_update
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetptr description
 * \return int32_t description
 * modification date : 2018.08.09
 *****************************************************************************/
int32_t bts_comm_callback_user_command_flash_block_update(bts_comm_packet_t *packetptr)
{
    uint8_t txbuff[2];

    uint8_t *cmdbuff = (uint8_t *)packetptr->cro.databuffptr;
    int32_t datalen = (int32_t)packetptr->cro.datasize;
    uint8_t checkcode[2] = {0};
    uint32_t flash_block_addr = 0;
    uint32_t flash_block_size = 0;
    uint8_t *flash_block_data = NULL;
    // 8     9     10     11  12       16         20
    //       0      1     2   3456     789-10     11
    // pid [usrcmd, 0x55,0xAA, addr(4), length(4), data~
    bts_comm_callback_log("bts_comm_callback_user_command_flash_block_update\n\r");
    krs_log_arruint8X(packetptr->cro.databuffptr, 32);
    checkcode[0] = cmdbuff[1];
    checkcode[1] = cmdbuff[2];
    flash_block_addr = krs_u32mem(&cmdbuff[3]);
    flash_block_size = krs_u32mem(&cmdbuff[3 + 4]);
    flash_block_data = &cmdbuff[3 + 4 + 4];
    bts_comm_callback_log("flash_block_addr: 0x%08X\n\r", flash_block_addr);
    bts_comm_callback_log("flash_block_size: 0x%08X\n\r", flash_block_size);
    bts_comm_callback_log("datalen: 0x%08X\n\r", datalen);

    if(checkcode[0] != 0x55 || checkcode[1] != 0xAA)
    {
        bts_comm_callback_log("flash_unlock fail\n\r");
        bts_comm_send_error(IR24XCOMMRESP_ERR_ACCESS_LOCKED);
        return retOK;
    }

    //if(mtdapp->mtd->memdrv.mtd_lowlevel_erase(flash_block_addr, flash_block_size) != retOK)
    if(retFail)
    {
        bts_comm_callback_log("flash_erase fail\n\r");
        bts_comm_send_error(IR24XCOMMRESP_ERR_WRITE_PROTECTED);
        return retOK;
    }
    bts_comm_callback_log("flash_erase success\n\r");

    //if(mtdapp->mtd->memdrv.mtd_lowlevel_write((uint8_t *)flash_block_data,
    //                                          (uint32_t)flash_block_addr,
    //                                          (size_t)flash_block_size) != retOK)
    if(retFail)
    {
        bts_comm_callback_log("flash_write fail\n\r");
        bts_comm_send_error(IR24XCOMMRESP_ERR_WRITE_PROTECTED);
        return retOK;
    }
    bts_comm_callback_log("flash_write success\n\r");
    bts_comm_send_cro(0, IR24XCOMMRESP_RES, txbuff);
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_callback_user_command_flash_cache_update
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *packetptr description
 * \return0 int32_t description
 * modification date : 2020.04.06
 *****************************************************************************/
int32_t bts_comm_callback_user_command_flash_cache_update(bts_comm_packet_t *packetptr)
{
    uint8_t txbuff[2];
    uint8_t *cmdbuff = (uint8_t *)packetptr->cro.databuffptr;
    int32_t datalen = (int32_t)packetptr->cro.datasize;
    uint8_t checkcode[2] = {0};
    uint32_t flash_block_addr = 0;
    uint32_t flash_block_size = 0;
    uint8_t *flash_block_data = NULL;
    // 8     9     10     11  12       16         20
    //       0      1     2   3456     789-10     11
    // pid [usrcmd, 0x55,0xAA, addr(4), length(4), data~
    bts_comm_callback_log("bts_comm_callback_user_command_flash_cache_update\n\r");
    krs_log_arruint8X(packetptr->cro.databuffptr, 32);
    checkcode[0] = cmdbuff[1];
    checkcode[1] = cmdbuff[2];
    flash_block_addr = krs_u32mem(&cmdbuff[3]);
    flash_block_size = krs_u32mem(&cmdbuff[3 + 4]);
    flash_block_data = &cmdbuff[3 + 4 + 4];
    bts_comm_callback_log("flash_cache_block_addr: 0x%08X\n\r", flash_block_addr);
    bts_comm_callback_log("flash_cache_block_size: 0x%08X\n\r", flash_block_size);
    bts_comm_callback_log("datalen: 0x%08X\n\r", datalen);

    if(checkcode[0] != 0x55 || checkcode[1] != 0xAA)
    {
        bts_comm_callback_log("flash_cache_unlock fail\n\r");
        bts_comm_send_error(IR24XCOMMRESP_ERR_ACCESS_LOCKED);
        return retOK;
    }

    // krs_memset(&mtd_cache[flash_block_addr], 0xFF, flash_block_size);
    //krs_memcopy(&mtd_cache[flash_block_addr], flash_block_data, flash_block_size);
    bts_comm_callback_log("flash_cache update fail\n\r");

    bts_comm_callback_log("flash_cache update success\n\r");
    bts_comm_send_cro(0, IR24XCOMMRESP_RES, txbuff);
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_callback_user_command_flash_cache_store
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *packetptr description
 * \return0 int32_t description
 * modification date : 2020.04.06
 *****************************************************************************/
int32_t bts_comm_callback_user_command_flash_cache_store(bts_comm_packet_t *packetptr)
{
    uint8_t txbuff[2];
    uint8_t *cmdbuff = (uint8_t *)packetptr->cro.databuffptr;
    int32_t datalen = (int32_t)packetptr->cro.datasize;
    uint8_t checkcode[2] = {0};
    uint32_t flash_block_addr = 0;
    uint32_t flash_block_size = 0;
    // 8     9     10     11  12       16
    //       0      1     2   3456     789-10
    // pid [usrcmd, 0x55,0xAA, addr(4), length(4)
    bts_comm_callback_log("bts_comm_callback_user_command_flash_cache_store\n\r");
    krs_log_arruint8X(packetptr->cro.databuffptr, 32);
    checkcode[0] = cmdbuff[1];
    checkcode[1] = cmdbuff[2];
    flash_block_addr = krs_u32mem(&cmdbuff[3]);
    flash_block_size = krs_u32mem(&cmdbuff[3 + 4]);
    bts_comm_callback_log("flash_cache_block_addr: 0x%08X\n\r", flash_block_addr);
    bts_comm_callback_log("flash_cache_block_size: 0x%08X\n\r", flash_block_size);
    bts_comm_callback_log("datalen: 0x%08X\n\r", datalen);


    if(checkcode[0] != 0x55 || checkcode[1] != 0xAA)
    {
        bts_comm_callback_log("flash_cache_unlock fail\n\r");
        bts_comm_send_error(IR24XCOMMRESP_ERR_ACCESS_LOCKED);
        return retOK;
    }

    //if(mtdapp->mtd->memdrv.mtd_lowlevel_erase(flash_block_addr, flash_block_size) != retOK)
    if(retFail)
    {
        bts_comm_callback_log("flash_erase fail\n\r");
        bts_comm_send_error(IR24XCOMMRESP_ERR_WRITE_PROTECTED);
        return retOK;
    }
    bts_comm_callback_log("flash_erase success\n\r");

    //if(mtdapp->mtd->memdrv.mtd_lowlevel_write((uint8_t *)&mtd_cache[flash_block_addr],
    //                                          (uint32_t)flash_block_addr,
    //                                          (size_t)flash_block_size) != retOK)
    if(retFail)
    {
        bts_comm_callback_log("flash_write fail\n\r");
        bts_comm_send_error(IR24XCOMMRESP_ERR_WRITE_PROTECTED);
        return retOK;
    }
    bts_comm_callback_log("flash_write success\n\r");
    bts_comm_send_cro(0, IR24XCOMMRESP_RES, txbuff);
    return retOK;
}


/* end of file */
