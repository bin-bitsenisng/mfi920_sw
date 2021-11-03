/************************************************************************
| Project Name: eth_datatype
|    File Name: eth_datatype.h
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
| 2017.06.01   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef ETH_DATATYPE_H__
#define ETH_DATATYPE_H__


#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "sys_config.h"
#include "eth_cfg.h"



/* module specific types  */



// mapping BSD socket API
#if SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LWIP
typedef struct sockaddr_in eth_sockaddr_in_t;
typedef struct sockaddr eth_sockaddr_t;
#define eth_socklen_t socklen_t
#define eth_ipaddr_t ip_addr_t
#define eth_socket_t int32_t
#define eth_ntohl   lwip_ntohl
#define eth_htonl   lwip_htonl
#define eth_htons   lwip_htons

#define ETH_AF_INET AF_INET
#define ETH_AF_INET6 AF_INET6
#define ETH_SOCK_DGRAM SOCK_DGRAM
#define ETH_IPPROTO_UDP IPPROTO_UDP

#define ETH_SOCK_STREAM SOCK_STREAM
#define ETH_IPPROTO_TCP IPPROTO_TCP
#elif SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_FREERTOSTCP
typedef  struct freertos_sockaddr eth_sockaddr_in_t;
typedef struct freertos_sockaddr eth_sockaddr_t;
#define eth_socklen_t socklen_t
#define eth_ipaddr_t uint32_t
#define eth_socket_t Socket_t
#define eth_ntohl   FreeRTOS_ntohl
#define eth_htonl   FreeRTOS_htonl
#define eth_htons   FreeRTOS_htons
#define eth_ntohs	FreeRTOS_ntohs



#define ETH_AF_INET FREERTOS_AF_INET
#define ETH_AF_INET6 FREERTOS_AF_INET6
#define ETH_SOCK_DGRAM FREERTOS_SOCK_DGRAM
#define ETH_IPPROTO_UDP FREERTOS_IPPROTO_UDP

#define ETH_SOCK_STREAM FREERTOS_SOCK_STREAM
#define ETH_IPPROTO_TCP FREERTOS_IPPROTO_TCP

#elif SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LINUX
typedef  struct sockaddr_in eth_sockaddr_in_t;
typedef struct sockaddr_t eth_sockaddr_t;
#define eth_socklen_t socklen_t
#define eth_ipaddr_t uint32_t
#define eth_socket_t int32_t
#define eth_ntohl   ntohl
#define eth_htonl   htonl
#define eth_htons   htons
#define eth_ntohs	ntohs

#define ETH_AF_INET AF_INET
#define ETH_AF_INET6 AF_INET6
#define ETH_SOCK_DGRAM SOCK_DGRAM
#define ETH_IPPROTO_UDP IPPROTO_UDP

#define ETH_SOCK_STREAM SOCK_STREAM
#define ETH_IPPROTO_TCP IPPROTO_TCP

#endif

#define eth_ip4_addr1(x) ((uint8_t)(((x) >> 24) & 0xFF))
#define eth_ip4_addr2(x) ((uint8_t)(((x) >> 16) & 0xFF))
#define eth_ip4_addr3(x) ((uint8_t)(((x) >> 8) & 0xFF))
#define eth_ip4_addr4(x) ((uint8_t)(((x) >> 0) & 0xFF))

/** 255.255.255.255 */
#define ETH_IPADDR_NONE         ((uint32_t)0xffffffffUL)
/** 127.0.0.1 */
#define ETH_IPADDR_LOOPBACK     ((uint32_t)0x7f000001UL)
/** 0.0.0.0 */
#define ETH_IPADDR_ANY          ((uint32_t)0x00000000UL)
/** 255.255.255.255 */
#define ETH_IPADDR_BROADCAST    ((uint32_t)0xffffffffUL)


typedef enum
{
    eth_networkevent_undef,
    eth_networkevent_up,
    eth_networkevent_down,
    eth_networkevent_negotiating,
}eth_networkevent_t;

/* declare extern global variables */

/* declare extern global functions */


#ifdef __cplusplus
}
#endif

#endif // ETH_DATATYPE_H__

