/************************************************************************
| Project Name: AFI910
|    File Name: can.h
|  Description: detailed Description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company                        
| --------     ---------------------     -------------------------------
| 11010        Heungsun Yoon             bitsensing Corporation
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description                                 
| ----------  ----  ------  --------------------------------------------
| 2021.03.15   0.0  11010   Creation;
|***********************************************************************/

#ifndef _CAN_H_
#define _CAN_H_

#ifdef __cplusplus
extern "C" {
#endif

/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "can_cfg.h"

/* include system bsp header */
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>


#include <linux/can.h>
#include <linux/can/raw.h>

/* module specific types  */
typedef int32_t can_ret_t;

/* define structure for this module */
typedef struct {
    int32_t moduleinfo;
    int32_t version;
} can_info_t;

typedef struct {
    int socketInd;
    struct sockaddr_can sAddr;
    struct ifreq ifr;
} can_handler_t;

/* declare extern global variables */

/* declare extern global functions */
extern can_ret_t can_init(void);
extern can_ret_t can_osinit(void);
extern can_ret_t can_read(void);

#ifdef __cplusplus
}
#endif

#endif //_CAN_H_