/************************************************************************
 | Project Name: KRS24
 |    File Name: eth_cfg.h
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

#ifndef ETH_CFG_H__
#define ETH_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif

#if SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_FREERTOSTCP
#include "eth_freertostcp_cfg.h"
#elif SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LWIP
#include "eth_lwip_cfg.h"
#elif SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LINUX
#include "eth_linuxsock_cfg.h"
#endif // #if SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_FREERTOSTCP

#ifdef __cplusplus
}
#endif
#endif /* ETH_CFG_H__ */
