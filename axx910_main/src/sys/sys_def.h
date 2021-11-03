/************************************************************************
 | Project Name: KRS24
 |    File Name: sys_def.h
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
 | 2014.12.02   0.0   SKJ   Creation;
 |***********************************************************************/

#ifndef SYS_DEF_H__
#define SYS_DEF_H__

/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"


/* module specific types  */


/* define structure for this module */
#define SYS_RADAR_VERSION_BEV10	10
#define SYS_RADAR_VERSION_BEV23	23
#define SYS_RADAR_VERSION_BEV24 24
#define SYS_RADAR_VERSION_BEV25 25
#define SYS_RADAR_VERSION_BEV30 30
#define SYS_RADAR_VERSION_BEV31 31

#define SYS_LOGGER_VERSION_V01  1

/* declare extern global variables */
#define SYS_NETWORK_ETH_STACK_LWIP			0
#define SYS_NETWORK_ETH_STACK_FREERTOSTCP	1
#define SYS_NETWORK_ETH_STACK_LINUX 	    2

/* Application type */
#define SYS_APP_TYPE_LOGGER 0x05
#define SYS_APP_TYPE_ITS 0x08
#define SYS_APP_TYPE_VF 0x09
#define SYS_APP_TYPE_FCW 0x0A
#define SYS_APP_TYPE_LEVELMETER 0x0B
#define SYS_APP_TYPE_MARINE 0x0C
#define SYS_APP_TYPE_FI 0x01


/* CAN Network */
#define SYS_APP_CANDB_TYPE_HKMC1G 0
#define SYS_APP_CANDB_TYPE_HKMC2G 1
#define SYS_APP_CANDB_TYPE_J1939 2
#define SYS_APP_CANDB_TYPE_MITSUBISHI 3

/* declare extern global functions */

#endif /* SYS_DEF_H__ */
