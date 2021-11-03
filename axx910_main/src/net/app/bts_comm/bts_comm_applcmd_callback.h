/************************************************************************
| Project Name: bts_comm_appl_udpcallback
|    File Name: bts_comm_appl_udpcallback.h
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
#ifndef bts_COMM_APPL_UDPCALLBACK_H__
#define bts_COMM_APPL_UDPCALLBACK_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* include system primitive types */
#include "bts.h"

#include "bts_comm.h"
#include "bts_comm_appl.h"
//#include "mtd_app.h"
#include "os.h"
#include "sys_param.h"
#include "krs_lib.h"

/* module specific types  */


/* define structure for this module */
#define bts_COMM_CALLBACK_LOG_EN SYS_PARAM_CONSOLELOG.bts_log_module_comm_appl_callback_en

#if bts_COMM_CALLBACK_DEBUG == 1
#define bts_comm_applcmd_callback_log \
    if(bts_COMM_CALLBACK_LOG_EN != 0) \
    krs_log
#else
#define bts_comm_applcmd_callback_log krs_log_dummy
#endif



    typedef enum
    {
        bts_comm_applcmd_session_normal,
        bts_comm_applcmd_session_security,
        bts_comm_applcmd_session_all,
    } bts_comm_applcmd_sessiontype_t;

    typedef enum
    {
    	bts_comm_applcmd_conntype_udp_unicast,
		bts_comm_applcmd_conntype_udp_broadcast,
		bts_comm_applcmd_conntype_tcp,
    } bts_comm_applcmd_conntype_t;


    typedef struct
    {
        bts_comm_applcmd_conntype_t conntype;
        eth_socket_t *psock;
        eth_sockaddr_in_t *premote;
    }bts_comm_applcmd_conn_t;

    typedef struct
    {
        char_t *rxbuffptr;
        int32_t rxsize;
        char_t *txbuffptr;
        int32_t txsize;
        os_time_t rxtimestamp;
        int32_t txen;
        bts_comm_applcmd_conn_t conn;
    } bts_comm_applcmd_packet_t;

    typedef int32_t (*bts_comm_applcmd_callback_t)(json_out_t *jsonout, bts_comm_applcmd_packet_t *);

    typedef struct
    {
        char_t command[32];
        bts_comm_applcmd_sessiontype_t sessiontype;
        bts_comm_applcmd_callback_t callback;
    } bts_comm_applcmd_dispatch_table_t;


    /* declare extern global variables */

    /* declare extern global functions */
    extern int32_t bts_comm_applcmd_callback_dispactch(bts_comm_applcmd_packet_t *packet);


#ifdef __cplusplus
}
#endif

#endif // bts_COMM_APPL_UDPCALLBACK_H__
