
/************************************************************************
| Project Name: bts_comm_appl_canlog
|    File Name: bts_comm_appl_canlog.h
|  Description: file detailed description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------
| SKJ          SONG KYEONG JIN           Bitsensing
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description
| ----------  ----  ------  --------------------------------------------
| 2019.08.28   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef bts_COMM_APPL_CANLOG_H__
#define bts_COMM_APPL_CANLOG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"
//#include "can_drv.h"
//#include "can_sig.h"

/* module specific types  */
/*
typedef struct
{
    f64_t timestamp_s;
    uint32_t msgcount;
    uint32_t msgsize;
    can_drv_msg_t msgs[4096];
} pid_canlogpacket_t;*/
/* define structure for this module */


/* declare extern global variables */

/* declare extern global functions */
extern void bts_comm_appl_canlog_init(void);
extern void bts_comm_appl_pid_canlog_packetbuild(void);
extern void bts_comm_appl_pid_canlog_packetsend(void);


#ifdef __cplusplus
}
#endif

#endif // bts_COMM_APPL_CANLOG_H__

