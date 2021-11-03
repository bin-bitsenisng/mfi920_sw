/************************************************************************
 | Project Name: KRS24
 |    File Name: network.h
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

#ifndef NETWORK_H__
#define NETWORK_H__
#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "network_cfg.h"

#include "app/app.h"
#include "if/if.h"

/* module specific types  */
typedef int32_t network_ret_t;


/* define structure for this module */
typedef struct{
    int32_t moduleinfo;
    int32_t version;
}network_info_t;


/* declare extern global variables */
extern uint8_t network_up_flag;

/* declare extern global functions */
extern network_ret_t network_init(void);
extern network_ret_t network_osinit(void);
extern network_ret_t network_osappinit(void);

#ifdef __cplusplus
}
#endif
#endif /* NETWORK_H__ */
