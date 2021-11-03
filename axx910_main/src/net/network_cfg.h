/************************************************************************
 | Project Name: KRS24
 |    File Name: network_cfg.h
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

#ifndef NETWORK_CFG_H__
#define NETWORK_CFG_H__

//#include "taskmgr_cfg.h"
#include "sys_param.h"

#ifdef __cplusplus
extern "C" {
#endif


/* defination for module configuration parameters */
#define NETWORK_CFG_ETH_GEM0 0
#define NETWORK_CFG_ETH_GEM1 1

#define NETWORK_CFG_ETH_CHANNEL NETWORK_CFG_ETH_GEM0

/****** Network configuration settings - only used when the lwIP example is
built.  See the page that documents this demo on the http://www.FreeRTOS.org
website for more information. ***********************************************/

/* The priority for the task that unblocked by the MAC interrupt to process
received packets. */
//#define configMAC_INPUT_TASK_PRIORITY		TASKMGR_NET_ETHSTACK_TASK_PRIORITY

/* The priority of the task that runs the lwIP stack. */
//#define configLWIP_TASK_PRIORITY			TASKMGR_NET_ETHSTACK_TASK_PRIORITY

/* The priority of the task that uses lwIP sockets to provide a simple command
line interface. */
#define configCLI_TASK_PRIORITY				( tskIDLE_PRIORITY + 1 )

/* DHCP or Static IP */
#define NETWORK_CFG_DHCP	0//0 //1 // 0
/* MAC address configuration. */
#define configMAC_ADDR0	0x90
#define configMAC_ADDR1	0xE2
#define configMAC_ADDR2	0xFC
#define configMAC_ADDR3	0x80
#define configMAC_ADDR4	0x00
#define configMAC_ADDR5	0x00
#define configMAC_ADDRSTR "90:E2:FC:80:00:00"

/* IP address configuration. */
#define configIP_ADDR0		192
#define configIP_ADDR1		168
#define configIP_ADDR2		10
#define configIP_ADDR3		150

/* Netmask configuration. */
#define configNET_MASK0		255
#define configNET_MASK1		255
#define configNET_MASK2		255
#define configNET_MASK3		0

/* gateway configuration. */
#define configGW_ADDR0		192
#define configGW_ADDR1		168
#define configGW_ADDR2		10
#define configGW_ADDR3		1

#define NETWORK_DEFAULT_IP 		SYS_PARAM_ETHDEFAULT_IP // "192.168.10.100"
#define NETWORK_DEFAULT_MASK 	SYS_PARAM_ETHDEFAULT_NM //"255.255.255.0"
#define NETWORK_DEFAULT_GW		SYS_PARAM_ETHDEFAULT_GW //"192.168.10.1"
#define NETWORK_DEFAULT_DNS		SYS_PARAM_ETHDEFAULT_DNS // "208.67.222.222"	// OpenDNS address
#define NETWORK_DEFAULT_MAC     SYS_PARAM_ETHDEFAULT_MAC

#ifdef __cplusplus
}
#endif
#endif /* NETWORK_CFG_H__ */
