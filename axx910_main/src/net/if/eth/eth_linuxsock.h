/************************************************************************
 | Project Name: 
 |    File Name: eth_linuxsock.h
 |  Description: detailed Description
 |-----------------------------------------------------------------------
 |               A U T H O R   I D E N T I T Y
 |-----------------------------------------------------------------------
 | Initials     Name                      Company                        
 | --------     ---------------------     -------------------------------
 | MHKIM        Myoungha Kim              bitsensing Corporation
 |-----------------------------------------------------------------------
 |              R E V I S I O N   H I S T O R Y
 |-----------------------------------------------------------------------
 | Date         Ver  Author  Description                                 
 | ----------  ----  ------  --------------------------------------------
 | 2021.01.22  0.0   mhkim   Creation;
 |***********************************************************************/

#ifndef _ETH_LINUXSOCK_H__
#define _ETH_LINUXSOCK_H__
#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "eth.h"
#include "eth_cfg.h"
#include "eth_datatype.h"

#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"

/* module specific types  */
typedef int32_t eth_ret_t;

/* define structure for this module */
/*
typedef struct{
    int32_t moduleinfo;
    int32_t version;
}eth_info_t;
*/

/* declare extern global variables */
extern struct sockaddr_in server_netif;

/* declare extern global functions */
extern eth_ret_t eth_linux_init(void);
extern void eth_linux_get_ip_info(uint8_t *destbuff);
extern uint32_t eth_linux_get_local_ip_addr(void);
extern uint32_t eth_linux_get_broadcast_ip_addr(void);
extern eth_socket_t eth_linux_open_udpserver_socket(uint16_t usPort, os_time_ms_t sendtimeout);
extern eth_socket_t eth_linux_open_udpclient_socket(TickType_t sendtimeout);
extern int32_t eth_linux_open_tcpserver_socket(uint16_t usPort,
                                              eth_socket_t *listensocket,
                                              eth_socket_t *connectsocket,
                                              os_time_ms_t conntimeout, os_time_ms_t sendtimeout,
                                              os_time_ms_t rcvtimeout);
extern int32_t eth_linux_close_tcpserver_socket(eth_socket_t *listensocket,
                                               eth_socket_t *connectsocket, os_time_t rcvtimeout);                                          
extern int32_t eth_linux_open_tcpclient_socket(char *ipaddrstr, uint16_t port,
                                              eth_socket_t *connectsocket, os_time_ms_t sendtimeout,
                                              os_time_ms_t rcvtimeout);
extern int32_t eth_linux_close_tcpclient_socket(eth_socket_t *connectsocket, os_time_t rcvtimeout);
extern int32_t eth_linux_shutdown(eth_socket_t consock);
#ifdef __cplusplus
}
#endif
#endif /* ETH_H__ */
