/************************************************************************
 | Project Name: KRS24
 |    File Name: eth.h
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

#ifndef ETH_H__
#define ETH_H__
#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "os.h"
#include "sys_config.h"
#include "eth_cfg.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#if SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LWIP
#include "eth_lwip.h"
#elif SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_FREERTOSTCP
/* FreeRTOS+TCP includes. */
#include "eth_freertostcp.h"
#elif SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LINUX
#include "eth_linuxsock.h"
#else

#endif

#include "eth_datatype.h"


/* module specific types  */
typedef int32_t eth_ret_t;

typedef enum
{
	eth_commtype_UDP,
	eth_commtype_TCP
} eth_commtype_t;

/* define structure for this module */


// mapping BSD socket API
#if SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LWIP
#define eth_inet_ntoa eth_lwip_inet_ntoa


#define eth_socket eth_lwip_socket
#define eth_bind eth_lwip_bind
#define eth_listen eth_lwip_listen
#define eth_connect eth_lwip_connect
#define eth_accept eth_lwip_accept
#define eth_send eth_lwip_send
//#define eth_recv(sock, buff, len, timeout) eth_lwip_recv(sock, buff, len, (timeout == 0)? MSG_DONTWAIT: 0)
#define eth_recv(sock, buff, len, timeout) eth_lwip_recv(sock, buff, len, 0)
#define eth_sendto eth_lwip_sendto
#define eth_recvfrom eth_lwip_recvfrom
#define eth_close eth_lwip_close
#define eth_shutdown eth_lwip_shutdown
#define eth_gethostbyname eth_lwip_gethostbyname
#define eth_gethostbyaddr eth_lwip_gethostbyaddr
#define eth_select eth_lwip_select
#define eth_poll eth_lwip_poll
#define eth_getsockopt eth_lwip_getsockopt
#define eth_setsockopt eth_lwip_setsockopt
#define eth_shutdown eth_lwip_shutdown

#define eth_inet_addr inet_addr
#define ETH_AF_INET AF_INET
#define ETH_INADDR_ANY INADDR_ANY
#define ETH_SOCK_STREAM SOCK_STREAM
#define ETH_IPPROTO_TCP IPPROTO_TCP
//#define ETH_SO_WIN_PROPERTIES SO_WIN_PROPERTIES
//#define ETH_INVALID_SOCKET INVALID_SOCKET
#define ETH_SO_RCVTIMEO SO_RCVTIMEO
#define ETH_SO_SNDTIMEO SO_SNDTIMEO
#define ETH_SOL_SOCKET SOL_SOCKET//0


#elif SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_FREERTOSTCP
#define eth_inet_ntoa( ulIPAddress, pucBuffer )									\
								sprintf( ( char * ) ( pucBuffer ), "%u.%u.%u.%u",			\
									( ( unsigned ) ( ( ulIPAddress ) & 0xffUL ) ),			\
									( ( unsigned ) ( ( ( ulIPAddress ) >> 8 ) & 0xffUL ) ),	\
									( ( unsigned ) ( ( ( ulIPAddress ) >> 16 ) & 0xffUL ) ),\
									( ( unsigned ) ( ( ulIPAddress ) >> 24 ) ) )


#define eth_socket eth_freertostcp_socket
#define eth_bind eth_freertostcp_bind
#define eth_listen eth_freertostcp_listen
#define eth_connect eth_freertostcp_connect
#define eth_accept eth_freertostcp_accept
#define eth_send eth_freertostcp_send
#define eth_recv eth_freertostcp_recv
#define eth_sendto eth_freertostcp_sendto
#define eth_recvfrom eth_freertostcp_recvfrom
#define eth_close eth_freertostcp_close
#define eth_shutdown eth_freertostcp_shutdown
#define eth_gethostbyname eth_freertostcp_gethostbyname
#define eth_gethostbyaddr eth_freertostcp_gethostbyaddr
#define eth_getsockopt eth_freertostcp_getsockopt
#define eth_setsockopt eth_freertostcp_setsockopt
#define eth_shutdown eth_freertostcp_shutdown
#define eth_select eth_freertostcp_select
#define eth_poll eth_freertostcp_poll
#define eth_fd_set eth_freertostcp_fd_set
#define eth_fd_clr eth_freertostcp_fd_clr
#define eth_fd_isset eth_freertostcp_fd_isset


#define ETH_AF_INET FREERTOS_AF_INET
#define ETH_SOCK_STREAM FREERTOS_SOCK_STREAM
#define ETH_IPPROTO_TCP FREERTOS_IPPROTO_TCP
#define ETH_SO_WIN_PROPERTIES FREERTOS_SO_WIN_PROPERTIES
#define ETH_INVALID_SOCKET FREERTOS_INVALID_SOCKET
#define ETH_SO_RCVTIMEO FREERTOS_SO_RCVTIMEO
#define ETH_SO_SNDTIMEO FREERTOS_SO_SNDTIMEO
#define ETH_INVALID_SOCKET FREERTOS_INVALID_SOCKET
#define ETH_INADDR_ANY	((unsigned long int) 0x00000000)
#define ETH_SOL_SOCKET SOL_SOCKET

#elif SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LINUX
#define eth_inet_ntoa inet_ntoa

#define eth_socket socket
#define eth_bind bind
#define eth_listen listen
#define eth_connect connect
#define eth_accept accept
#define eth_send send
//#define eth_recv(sock, buff, len, timeout) eth_lwip_recv(sock, buff, len, (timeout == 0)? MSG_DONTWAIT: 0)
#define eth_recv(sock, buff, len, timeout) recv(sock, buff, len, 0)
#define eth_sendto sendto
#define eth_recvfrom recvfrom
#define eth_close close
#define eth_shutdown shutdown
#define eth_gethostbyname gethostbyname
#define eth_gethostbyaddr gethostbyaddr
#define eth_select select
#define eth_poll poll
#define eth_getsockopt getsockopt
#define eth_setsockopt setsockopt

#define eth_inet_addr inet_addr
#define ETH_AF_INET AF_INET
#define ETH_INADDR_ANY INADDR_ANY
#define ETH_SOCK_STREAM SOCK_STREAM
#define ETH_IPPROTO_TCP IPPROTO_TCP
//#define ETH_SO_WIN_PROPERTIES SO_WIN_PROPERTIES
//#define ETH_INVALID_SOCKET INVALID_SOCKET
#define ETH_SO_RCVTIMEO SO_RCVTIMEO
#define ETH_SO_SNDTIMEO SO_SNDTIMEO
#define ETH_SO_BROADCAST SO_BROADCAST
#define ETH_SOL_SOCKET SOL_SOCKET//0

#endif




// krs api
#if SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LWIP
#define eth_get_ip_info eth_lwip_get_ip_info
#define eth_get_local_ip_addr eth_lwip_get_local_ip_addr
#define eth_get_broadcast_ip_addr eth_lwip_get_broadcast_ip_addr
#define eth_open_udpserver_socket eth_lwip_open_udpserver_socket
#define eth_open_udpclient_socket eth_lwip_open_udpclient_socket
#define eth_open_tcpserver_socket eth_lwip_open_tcpserver_socket
#define eth_close_tcpserver_socket eth_lwip_close_tcpserver_socket
#define eth_open_tcpclient_socket eth_lwip_open_tcpclient_socket
#define eth_close_tcpclient_socket eth_lwip_close_tcpclient_socket




#elif SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_FREERTOSTCP
#define eth_get_ip_info eth_freertostcp_get_ip_info
#define eth_get_local_ip_addr eth_freertostcp_get_local_ip_addr
#define eth_get_broadcast_ip_addr eth_freertos_get_broadcast_ip_addr
#define eth_open_udpserver_socket eth_freertostcp_open_udpserver_socket
#define eth_open_udpclient_socket eth_freertostcp_open_udpclient_socket
#define eth_open_tcpserver_socket eth_freertostcp_open_tcpserver_socket
#define eth_close_tcpserver_socket eth_freertostcp_close_tcpserver_socket
#define eth_open_tcpclient_socket eth_freertostcp_open_tcpclient_socket
#define eth_close_tcpclient_socket eth_freertostcp_close_tcpclient_socket

#elif SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LINUX
#define eth_get_ip_info eth_linux_get_ip_info
#define eth_get_local_ip_addr eth_linux_get_local_ip_addr
#define eth_get_broadcast_ip_addr eth_linux_get_broadcast_ip_addr
#define eth_open_udpserver_socket eth_linux_open_udpserver_socket
#define eth_open_udpclient_socket eth_linux_open_udpclient_socket
#define eth_open_tcpserver_socket eth_linux_open_tcpserver_socket
#define eth_close_tcpserver_socket eth_linux_close_tcpserver_socket
#define eth_open_tcpclient_socket eth_linux_open_tcpclient_socket
#define eth_close_tcpclient_socket eth_linux_close_tcpclient_socket

#endif





/* declare extern global variables */
extern uint8_t ucMACAddress[6];
extern os_sem_t sem_ipaddr_cfg_complete;


/* declare extern global functions */
extern eth_ret_t eth_init(void);
extern eth_ret_t eth_osinit(void);
extern void eth_print_ip(char *msg, uint32_t ip ,uint16_t port);
extern void eth_print_errmsg(int32_t errcode);
extern uint32_t eth_is_setup_complete(void);
extern int32_t eth_get_ipaddr_aton(const char *cp, uint32_t *addr);
extern void eth_get_ipaddr_ntoa(uint32_t ip, char *dest, uint32_t buflen);
extern uint32_t eth_get_ipaddr_fromstring(const char *cp);
extern int32_t eth_get_macaddr_fromstring(uint8_t *mac_addr, const char *macstr);
extern int32_t eth_get_macaddr_fromhw(uint8_t *mac_addr);
extern int32_t eth_errcheck_timeout(int32_t errcode);
extern void eth_link_undefined_callback(void *param);
extern void eth_link_up_callback(void *param);
extern void eth_link_down_callback(void *param);
extern void eth_link_negotiating_callback(void *param);
extern const char *eth_strerr(err_t err);
extern int32_t eth_link_isvalid(void);
extern void eth_print_ip_settings(uint32_t ip, uint32_t mask, uint32_t gw);
#ifdef __cplusplus
}
#endif
#endif /* ETH_H__ */
