/************************************************************************
 | Project Name: KRS24
 |    File Name: bts_comm_callback.h
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
 | 2015.11.16   0.0   SKJ   Creation;
 |***********************************************************************/

#ifndef bts_COMM_CALLBACK_H__
#define bts_COMM_CALLBACK_H__
#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"
#include "bts_comm_cmd.h"
#include "bts_comm_odt.h"
#include "bts_comm_packet.h"
#include "bts_comm_status.h"
#include "os.h"
/* module specific types  */


/* define structure for this module */
typedef int32_t (*bts_comm_cmd_callback)(bts_comm_packet_t *pp);
/* declare global variables */
typedef struct
{
    bts_comm_cmd_t pid;
    bts_comm_cmd_callback callback;
} bts_comm_cmd_table_t;


/* declare extern global variables */
extern bts_comm_cmd_table_t bts_comm_cmd_table[];


/* declare extern global functions */


#ifdef __cplusplus
}
#endif
#endif /* bts_COMM_CALLBACK_H__ */
