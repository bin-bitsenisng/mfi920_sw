/************************************************************************
| Project Name: bts_comm_appl_common
|    File Name: bts_comm_appl_common.h
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
#ifndef bts_COMM_APPL_COMMON_H__
#define bts_COMM_APPL_COMMON_H__


#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"

/* module specific types  */





/* declare extern global variables */
extern int32_t scanindex;


/* declare extern global functions */
extern void bts_comm_appl_common_init(void);
extern int32_t bts_comm_appl_common_get_daqinfo(char_t *desbuffer, uint32_t buffersize);
extern int32_t bts_comm_appl_common_check_activated(bts_comm_daqinfo_t *daqinfoptr);

#ifdef __cplusplus
}
#endif
#endif // bts_COMM_APPL_COMMON_H__
