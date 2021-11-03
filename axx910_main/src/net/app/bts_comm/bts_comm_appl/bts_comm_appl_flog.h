/************************************************************************
| Project Name: bts_comm_appl_flog
|    File Name: bts_comm_appl_flog.h
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
| 2019.04.13   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef bts_COMM_APPL_FLOG_H__
#define bts_COMM_APPL_FLOG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"

/* module specific types  */


/* define structure for this module */
typedef struct
{
    f32_t emmcfreerate;
    uint32_t filenumber;
    uint32_t eventflag;
    uint32_t flog_status;
}comm_appl_floginfo_t;


/* declare extern global variables */
extern comm_appl_floginfo_t raw_app_flog;

/* declare extern global functions */
extern void bts_comm_appl_flog_init(void);
extern void bts_comm_appl_raw_app_flog_precallback(void *pvparam, size_t size);


#ifdef __cplusplus
}
#endif

#endif // bts_COMM_APPL_FLOG_H__
