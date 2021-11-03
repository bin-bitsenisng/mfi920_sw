/************************************************************************
| Project Name: bts_comm_appl_vf
|    File Name: bts_comm_appl_vf.h
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
#ifndef bts_COMM_APPL_VF_H__
#define bts_COMM_APPL_VF_H__


#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"

/* module specific types  */
typedef struct
{
    uint8_t dat[128];
    uint8_t war[128];
    uint8_t det[128];
    uint8_t sw[128];
} bts_comm_appl_raw_vf_t;

/* define structure for this module */


/* declare extern global variables */
extern bts_comm_appl_raw_vf_t bts_comm_appl_raw_vf;
extern bts_comm_appl_raw_vf_t bts_comm_appl_raw_vf_window;
/* declare extern global functions */
extern void bts_comm_appl_vf_init(void);
extern void bts_comm_appl_pid_app_vf_packetbuild(void);
extern void bts_comm_appl_pid_app_vf_packetsend(void);
extern void bts_comm_appl_raw_app_vf_precallback(void *pvparam, size_t size);

#ifdef __cplusplus
}
#endif
#endif // bts_COMM_APPL_VF_H__
