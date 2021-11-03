/************************************************************************
 | Project Name: KRS24
 |    File Name: app.h
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
 | 2015.01.14   0.0   SKJ   Creation;
 |***********************************************************************/

#ifndef APP_H__
#define APP_H__
#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "app_cfg.h"


#include "bts_comm.h"
#include "bts_comm_appl.h"
/* module specific types  */
typedef int32_t app_ret_t;


/* define structure for this module */
typedef struct{
    int32_t moduleinfo;
    int32_t version;
}app_info_t;


/* declare extern global variables */


/* declare extern global functions */
extern app_ret_t app_init(void);
extern app_ret_t app_osinit(void);

#ifdef __cplusplus
}
#endif
#endif /* APP_H__ */
