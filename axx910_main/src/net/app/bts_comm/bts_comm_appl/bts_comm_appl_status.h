/************************************************************************
| Project Name: bts_comm_appl_status
|    File Name: bts_comm_appl_status.h
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
| 2018.06.26   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef bts_COMM_APPL_STATUS_H__
#define bts_COMM_APPL_STATUS_H__


#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"

/* module specific types  */


/* define structure for this module */


/* declare extern global variables */


/* declare extern global functions */
extern void bts_comm_appl_status_init(void);
extern void bts_comm_appl_pid_status_packetbuild(void);
extern void bts_comm_appl_pid_status_packetsend(void);
extern int32_t bts_comm_appl_status_get_info(char_t *desbuffer, uint32_t buffsize);
extern uint32_t bts_comm_appl_system_status_packetbuild(uint8_t *destbuff, size_t buffsize, char_t *jsonbuff, size_t len);
#ifdef __cplusplus
}
#endif
#endif // bts_COMM_APPL_STATUS_H__
