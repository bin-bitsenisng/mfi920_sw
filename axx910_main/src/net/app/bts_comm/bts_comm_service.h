/************************************************************************
| Project Name: bts_comm_service
|    File Name: bts_comm_service.c
|  Description: file detailed description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------
| JJUNE        PARK JUN SEONG            Bitsensing
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description
| ----------  ----  ------  --------------------------------------------
| 2018.12.21   0.0   JJUNE   Creation;
|***********************************************************************/

#ifndef bts_COMM_SERVICE_H__
#define bts_COMM_SERVICE_H__
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
#define SYS_PARAM_SERVICE_TABLE_MAX (sizeof(bts_comm_service_table) / sizeof(bts_comm_service_table_t))

/* define structure for this module */
typedef int32_t (*bts_comm_service_func)(void* pvParam);
/* declare global variables */
typedef struct
{
    uint32_t sid;
    uint32_t did;
    bts_comm_service_func service_func;
} bts_comm_service_table_t;


/* declare extern global variables */
extern bts_comm_service_table_t bts_comm_service_table[];


/* declare extern global functions */
extern int32_t bts_comm_service_callfunc(uint32_t sid, uint32_t did, void* pvParam);

#ifdef __cplusplus
}
#endif
#endif /* bts_COMM_CALLBACK_H__ */
