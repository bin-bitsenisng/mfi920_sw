/************************************************************************
 | Project Name: KRS24
 |    File Name: if.h
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

#ifndef IF_H__
#define IF_H__
#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "if_cfg.h"


//#include "can/can.h"
#include "eth/eth.h"
//#include "uart/uart.h"
/* module specific types  */
typedef int32_t if_ret_t;


/* define structure for this module */
typedef struct{
    int32_t moduleinfo;
    int32_t version;
}if_info_t;


/* declare extern global variables */


/* declare extern global functions */
extern if_ret_t if_init(void);
extern if_ret_t if_osinit(void);
extern if_ret_t if_osinit_complete(void);
#ifdef __cplusplus
}
#endif
#endif /* IF_H__ */
