/************************************************************************
 | Project Name: 
 |    File Name: eth_linuxsock.c
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

/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"
#include "sys_config.h"
#include "os.h"
#include "eth_cfg.h"

#include <net/if.h>
#include <net/if.h>
#include <linux/sockios.h>
#include <netinet/in.h>
#include <asm/types.h>
#include <linux/if_ether.h>

/* include system driver header */
#include "network_cfg.h"
#include "eth.h"
#if SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LINUX

/* include system bsp header */
#include <stdlib.h>

/* include system application header */

/* final include module header */
# include "eth_linuxsock.h"

//#define inet_ntop(__af,__src,__dst,__size)   ipaddr_ntoa_r((__src),(__dst),(__size))

/* declare global variables */
struct sockaddr_in server_netif;

/* declare static variables */

eth_ret_t eth_linux_init(void);
void eth_linux_get_ip_info(uint8_t *destbuff);
uint32_t eth_linux_get_local_ip_addr(void);
uint32_t eth_linux_get_broadcast_ip_addr(void);
eth_socket_t eth_linux_open_udpserver_socket(uint16_t usPort, os_time_ms_t sendtimeout);
eth_socket_t eth_linux_open_udpclient_socket(TickType_t sendtimeout);
int32_t eth_linux_open_tcpserver_socket(uint16_t usPort,
                                              eth_socket_t *listensocket,
                                              eth_socket_t *connectsocket,
                                              os_time_ms_t conntimeout, os_time_ms_t sendtimeout,
                                              os_time_ms_t rcvtimeout);
int32_t eth_linux_close_tcpserver_socket(eth_socket_t *listensocket,
                                               eth_socket_t *connectsocket, os_time_t rcvtimeout);                                          
int32_t eth_linux_open_tcpclient_socket(char *ipaddrstr, uint16_t port,
                                              eth_socket_t *connectsocket, os_time_ms_t sendtimeout,
                                              os_time_ms_t rcvtimeout);
int32_t eth_linux_close_tcpclient_socket(eth_socket_t *connectsocket, os_time_t rcvtimeout);
int32_t eth_linux_shutdown(eth_socket_t consock);

/* static function prototypes */
void dhcp_timer_thread(void *pvParameters);
//void eth_vStatusCallback( struct netif *pxNetIf );
//void eth_linux_tcpip_init_done(void *p);
//void eth_linux_ipnetwork_event_hook(eth_networkevent_t eNetworkEvent);
struct timeval eth_linux_ms2time(uint32_t time_ms);

#define ifreq_offsetof(x)  offsetof(struct ifreq, x)

/* functions */

int32_t eth_linux_init(void)
{
    struct sockaddr_in net_addr;
    char system_string[100] = {0};

    /* module init code here*/
#if LWIP_DHCP==1
	int mscnt = 0;
#else
#endif
	
#if LWIP_DHCP==0

    //system("sudo ifconfig eth0 down");
    sprintf(system_string, "sudo ifconfig eth0 %s netmask %s", NETWORK_DEFAULT_IP, NETWORK_DEFAULT_MASK);
    //system(system_string);
    krs_log("ip,netamsk setting cmd: %s\n", system_string);
    memset(system_string, 0, 100);
/*
    struct ifreq ifr;
    struct sockaddr_in sai;
    int sockfd;                     
    int selector;
    unsigned char mask;
    char *p;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ);
    memset(&sai, 0, sizeof(struct sockaddr));

    sai.sin_family = AF_INET;
    sai.sin_port = 0;
    sai.sin_addr.s_addr = inet_addr("192.168.10.151");

    p = (char *) &sai;
    memcpy( (((char *)&ifr + ifreq_offsetof(ifr_addr) )),
                    p, sizeof(struct sockaddr));

    ioctl(sockfd, SIOCSIFADDR, &ifr);
    ioctl(sockfd, SIOCGIFFLAGS, &ifr);

    ifr.ifr_flags |= IFF_UP | IFF_RUNNING;

    ioctl(sockfd, SIOCSIFFLAGS, &ifr);
    close(sockfd);
*/

    sprintf(system_string, "sudo route add default gw %s", NETWORK_DEFAULT_GW);
    //system(system_string);
    krs_log("gw setting cmd: %s\n", system_string);

/*
    if(eth_get_macaddr_fromstring(ucMACAddress, NETWORK_DEFAULT_MAC) != retOK)
	{
		ucMACAddress[0] = configMAC_ADDR0;
		ucMACAddress[1] = configMAC_ADDR1;
		ucMACAddress[2] = configMAC_ADDR2;
		ucMACAddress[3] = configMAC_ADDR3;
		ucMACAddress[4] = configMAC_ADDR4;
		ucMACAddress[5] = configMAC_ADDR5;
	}
*/

    eth_get_macaddr_fromhw(ucMACAddress);

    krs_log("MAC Address: ");
    for(int i = 0; i < 6; i++)
    {
        krs_log("%02X ", ucMACAddress[i]);
    }
    krs_log("\n");

#else
	ipaddr.addr = 0;
	gw.addr = 0;
	netmask.addr = 0;
#endif


    /* Add network interface to the netif_list, and set it as default */

    /* specify that the network if is up */

    /* start packet receive thread - required for lwIP operation */

#if LWIP_DHCP==1
    dhcp_start(netif);
    sys_thread_new("dhcp_timer_thread", (void(*)(void*))dhcp_timer_thread, netif, configMINIMAL_STACK_SIZE*2, TASKMGR_NET_ETHSTACK_TASK_PRIORITY);

    while (1) {
    	vTaskDelay(DHCP_FINE_TIMER_MSECS / portTICK_RATE_MS);

		if (server_netif.ip_addr.addr) {
			printf("DHCP request success\r\n");
			eth_print_ip_settings(&(server_netif.ip_addr), &(server_netif.netmask), &(server_netif.gw));

			/* print all application headers */
			//print_headers();
			/* now we can start application threads */
			//launch_app_threads();
			break;
		}
		mscnt += DHCP_FINE_TIMER_MSECS;
		if (mscnt >= 10000) {
			printf("ERROR: DHCP request timed out\r\n");
			printf("Configuring default IP of %d.%d.%d.%d\r\n",configIP_ADDR0,configIP_ADDR1,configIP_ADDR2,configIP_ADDR3);
			IP4_ADDR(&(server_netif.ip_addr),  configIP_ADDR0, configIP_ADDR1,   configIP_ADDR2, configIP_ADDR3);
			IP4_ADDR(&(server_netif.netmask), configNET_MASK0, configNET_MASK1, configNET_MASK2,  configNET_MASK3);
			IP4_ADDR(&(server_netif.gw),      configGW_ADDR0, configGW_ADDR1,   configGW_ADDR2,  configGW_ADDR3);
			eth_print_ip_settings(&(server_netif.ip_addr), &(server_netif.netmask), &(server_netif.gw));
			/* print all application headers */
			//print_headers();
			//launch_app_threads();
			break;
		}
	}
#else

#endif

    return retOK;
}

void eth_linux_get_ip_info(uint8_t *destbuff)
{
    // Add if it is needed.

    /*
	struct netif *netif;
	//&(server_netif.ip_addr), &(server_netif.netmask), &(server_netif.gw)
	netif = &server_netif;

    destbuff[0] = ip4_addr1(&netif->ip_addr);
    destbuff[1] = ip4_addr2(&netif->ip_addr);
    destbuff[2] = ip4_addr3(&netif->ip_addr);
    destbuff[3] = ip4_addr4(&netif->ip_addr);
    destbuff[4] = ip4_addr1(&netif->netmask);
    destbuff[5] = ip4_addr2(&netif->netmask);
    destbuff[6] = ip4_addr3(&netif->netmask);
    destbuff[7] = ip4_addr4(&netif->netmask);
    destbuff[8] = ip4_addr1(&netif->gw);
    destbuff[9] = ip4_addr2(&netif->gw);
    destbuff[10] = ip4_addr3(&netif->gw);
    destbuff[11] = ip4_addr4(&netif->gw);*/
}


uint32_t eth_linux_get_local_ip_addr(void)
{
	return (uint32_t)server_netif.sin_addr.s_addr;
}

uint32_t eth_linux_get_broadcast_ip_addr(void)
{
    // Add if it is needed.

    /*
	ip_addr_t ip;
	ip.addr = eth_get_local_ip_addr();
	ip.addr |= 0xFF000000;
	eth_print_ip("Broadcast IP: ", ip.addr, 0);
	return ntohl(ip.addr);
    */
}


eth_socket_t eth_linux_open_udpserver_socket(uint16_t usPort, os_time_ms_t sendtimeout)
{
    eth_sockaddr_in_t xBindAddress;
    eth_socket_t xServerSocket;
    struct timeval xSendTimeOut = eth_linux_ms2time(sendtimeout);


    xServerSocket = eth_socket(ETH_AF_INET, ETH_SOCK_DGRAM, ETH_IPPROTO_UDP);
    if(xServerSocket < 0)
    {
    	return -1;
    }

	/* Set to non-blocking sends with a timeout of zero as the socket might
	also be used for debug prints which should not block. */
    if(usPort == bts_COMM_APPLCMD_UDP_LOCAL_UNICAST_PORT)
        eth_setsockopt(xServerSocket, ETH_SOL_SOCKET, ETH_SO_SNDTIMEO, &xSendTimeOut, sizeof(xSendTimeOut));
    else if(usPort == bts_COMM_APPLCMD_UDP_LOCAL_BROADCAST_PORT)
	    eth_setsockopt(xServerSocket, ETH_SOL_SOCKET, ETH_SO_BROADCAST, &xSendTimeOut, sizeof(xSendTimeOut));
	// TODO : receive timeout???

	/* Zero out the server structure. */
	memset((void *)&xBindAddress, 0x00, sizeof(xBindAddress));

	/* Set family and port. */
	xBindAddress.sin_family = ETH_AF_INET;
	xBindAddress.sin_port = eth_htons(usPort);
	xBindAddress.sin_addr.s_addr = eth_htonl(ETH_INADDR_ANY);


	int reuse = 1;
	if (eth_setsockopt(xServerSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0)
	{
		//xil_printf("setsockopt(SO_REUSEADDR) failed\n\r");
	}



	/* Bind the address to the socket. */
	if(eth_bind(xServerSocket, (eth_sockaddr_t *)&xBindAddress, sizeof(xBindAddress)) < 0)
	{
		eth_close(xServerSocket);
		return -1;
	}

    return xServerSocket;
}


eth_socket_t eth_linux_open_udpclient_socket(TickType_t sendtimeout)
{
    eth_socket_t xClientSocket;
    struct timeval xSendTimeOut = eth_linux_ms2time(sendtimeout);


    xClientSocket = eth_socket(ETH_AF_INET, ETH_SOCK_DGRAM, ETH_IPPROTO_UDP);
    if(xClientSocket < 0)
    {
    	return -1;
    }

	eth_setsockopt(xClientSocket, ETH_SOL_SOCKET, ETH_SO_SNDTIMEO, &xSendTimeOut, sizeof(xSendTimeOut));


    return xClientSocket;
}




int32_t eth_linux_open_tcpserver_socket(uint16_t usPort,
                                              eth_socket_t *listensocket,
                                              eth_socket_t *connectsocket,
                                              os_time_ms_t conntimeout, os_time_ms_t sendtimeout,
                                              os_time_ms_t rcvtimeout)
{
    eth_sockaddr_in_t xBindAddress;
    eth_sockaddr_in_t xClient;
    socklen_t xSize = sizeof(xClient);
//    TickType_t xReceiveTimeOut = portMAX_DELAY;
//    TickType_t xSendTimeOut = portMAX_DELAY;
    struct timeval xReceiveTimeOut;
    struct timeval xSendTimeOut;
    //BaseType_t xBacklog = 5;
    //BaseType_t ret;
	int32_t xBacklog = 5;
    int32_t ret;
    int32_t reuse = 1;


    if(*listensocket < 0)
    {
        *listensocket = eth_socket(ETH_AF_INET, ETH_SOCK_STREAM, ETH_IPPROTO_TCP);
        //*listensocket = eth_socket(ETH_AF_INET, ETH_SOCK_STREAM, 0);

        if(*listensocket < 0)
        {
            krs_log("open_tcpserver_socket socket open fail.\n\r");
            return retFail;
        }

        /* Set a time out so accept() will just wait for a connection. */
        xReceiveTimeOut = eth_linux_ms2time(conntimeout);
        eth_setsockopt(*listensocket, ETH_SOL_SOCKET, ETH_SO_RCVTIMEO, &xReceiveTimeOut, sizeof(xReceiveTimeOut));
        eth_setsockopt(*listensocket, ETH_SOL_SOCKET, ETH_SO_SNDTIMEO, &xReceiveTimeOut, sizeof(xReceiveTimeOut));


    	if (eth_setsockopt(*listensocket, ETH_SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0)
    	{
    		krs_log("setsockopt(SO_REUSEADDR) failed\n\r");
    	}

        /* Bind the socket to the port that the client task will send to, then
        listen for incoming connections. */
        xBindAddress.sin_family = ETH_AF_INET;
        xBindAddress.sin_port = eth_htons(usPort);
        xBindAddress.sin_addr.s_addr = htonl(ETH_INADDR_ANY);

        ret = eth_bind(*listensocket, (eth_sockaddr_t*)&xBindAddress, sizeof(xBindAddress));
        if(ret < 0)
        {
            krs_log("open_tcpserver_socket port %d bind error : %ld\n\r", usPort, ret);
            eth_print_errmsg(ret);
            eth_close(*listensocket);
            *listensocket = -1;
            os_sleep(200);
            return retFail;
        }

        ret = eth_listen(*listensocket, xBacklog);
        if(ret < 0)
        {
            //krs_log("open_tcpserver_socket socket listen error\n\r");
            eth_close(*listensocket);
            *listensocket = -1;
            return retFail;
        }
    }
    krs_log("tcpserver listen socket : 0x%08lX\n\r", (uint32_t)*listensocket);

    *connectsocket = eth_accept(*listensocket, (eth_sockaddr_t*)&xClient, &xSize);
    //krs_log("tcpserver connectsocket : 0x%08lX\n\r", (uint32_t)*connectsocket);
    if(*connectsocket < 0)
    {
        krs_log("tcpserver_socket connected socket is invalid or timeout: %d, close listening socket\n\r",
                (int32_t)(*connectsocket));
        eth_print_errmsg((int32_t)*connectsocket);
        eth_close(*listensocket); // TODO ???
        *listensocket = -1;
        *connectsocket = -1;
        return retFail;
    }

    krs_log("tcpserver_socket connectsocket: 0x%08lX\n\r",(uint32_t)(*connectsocket));

    xReceiveTimeOut = eth_linux_ms2time(rcvtimeout);
    xSendTimeOut = eth_linux_ms2time(sendtimeout);
    //eth_setsockopt(*connectsocket, ETH_SOL_SOCKET, ETH_SO_RCVTIMEO, &xReceiveTimeOut, sizeof(xReceiveTimeOut));
    eth_setsockopt(*connectsocket, ETH_SOL_SOCKET, ETH_SO_SNDTIMEO, &xSendTimeOut, sizeof(xSendTimeOut));
    return retOK;
}


int32_t eth_linux_close_tcpserver_socket(eth_socket_t *listensocket,
                                               eth_socket_t *connectsocket, os_time_t rcvtimeout)
{
    os_time_ms_t xTimeOnEntering;
    uint8_t flushbuff[1024];
    int32_t xReturned;
    
/*  // 목적이 무엇이었을지..?
    xTimeOnEntering = os_time_ms();
    do
    {
        xReturned =
            eth_recv(*connectsocket,  // The socket being received from.
                     &(flushbuff[0]), // The buffer into which the received data will be written.
                     1024, // The size of the buffer provided to receive the data.
                     0);

        if(xReturned < 0)
        {
            break;
        }

    } while((os_time_ms() - xTimeOnEntering) < rcvtimeout);
*/

    //eth_shutdown(*connectsocket, SHUT_RD);
    eth_close(*connectsocket);
    eth_close(*listensocket);
    *connectsocket = -1;
    *listensocket = -1;
    return retOK;
}



int32_t eth_linux_open_tcpclient_socket(char *ipaddrstr, uint16_t port,
                                              eth_socket_t *connectsocket, os_time_ms_t sendtimeout,
                                              os_time_ms_t rcvtimeout)
{
    eth_sockaddr_in_t xServerAddress;
    struct timeval xReceiveTimeOut;
    struct timeval xSendTimeOut;




    *connectsocket = eth_socket(ETH_AF_INET, ETH_SOCK_STREAM, ETH_IPPROTO_TCP);
    if(*connectsocket < 0)
    {
        krs_log("open_tcpclient_socket socket open fail.\n\r");
        return retFail;
    }

    xReceiveTimeOut = eth_linux_ms2time(rcvtimeout);
	xSendTimeOut = eth_linux_ms2time(sendtimeout);
    eth_setsockopt(*connectsocket, ETH_SOL_SOCKET, ETH_SO_RCVTIMEO, &xReceiveTimeOut, sizeof(xReceiveTimeOut));
    eth_setsockopt(*connectsocket, ETH_SOL_SOCKET, ETH_SO_SNDTIMEO, &xSendTimeOut, sizeof(xSendTimeOut));


    /* Server Address */
    xServerAddress.sin_family = ETH_AF_INET;
    xServerAddress.sin_port = eth_htons(port);
    xServerAddress.sin_addr.s_addr = eth_inet_addr(ipaddrstr);

    if(eth_connect(*connectsocket, (eth_sockaddr_t *)&xServerAddress, sizeof(xServerAddress)) == 0)
    {
        return retOK;
    }
    eth_close(*connectsocket);
    *connectsocket = -1;
    return retFail;
}

int32_t eth_linux_close_tcpclient_socket(eth_socket_t *connectsocket, os_time_t rcvtimeout)
{
    os_time_ms_t xTimeOnEntering;
    uint8_t flushbuff[1024];
    int32_t xReturned;

    //eth_shutdown(*connectsocket, SHUT_RDWR);


    /* Expect FreeRTOS_recv() to return an error once the shutdown is
    complete. */
    xTimeOnEntering = os_time_ms();
    do
    {
        xReturned =
            eth_recv(*connectsocket,  /* The socket being received from. */
                     &(flushbuff[0]), /* The buffer into which the received data will be written. */
					 1024, /* The size of the buffer provided to receive the data. */
                     0);

        if(xReturned < 0)
        {
            break;
        }

    } while((os_time_ms() - xTimeOnEntering) < rcvtimeout);

    eth_close(*connectsocket);
    *connectsocket = -1;
    return retOK;
}

int32_t eth_linux_shutdown(eth_socket_t consock)
{
    os_time_ms_t xTimeOnShutdown;
    uint8_t pucRxBuffer[1024];
    /* Initiate a shutdown in case it has not already been initiated. */
    eth_shutdown(consock, SHUT_RDWR);

    /* Wait for the shutdown to take effect, indicated by FreeRTOS_recv()
    returning an error. */
    xTimeOnShutdown = os_time_ms();
    do
    {
        if(eth_recv(consock, pucRxBuffer, 1024, 0) < 0)
        {
            break;
        }
    } while((os_time_ms() - xTimeOnShutdown) < 5000);
    return 0;
}

void dhcp_timer_thread(void *pvParameters)
{
#if LWIP_DHCP==1
	os_time_ms_t mscnt=0;
    while (1)
    {
        os_sleep(DHCP_FINE_TIMER_MSECS / portTICK_RATE_MS);

        dhcp_fine_tmr();
        mscnt += DHCP_FINE_TIMER_MSECS;
        if (mscnt >= DHCP_COARSE_TIMER_SECS*1000) {
            dhcp_coarse_tmr();
            mscnt = 0;
        }
    }
#endif
}


/*
void eth_vStatusCallback( struct netif *pxNetIf )
{
char pcMessage[20];
struct in_addr* pxIPAddress;

	if( netif_is_up( pxNetIf ) != 0 )
	{
		krs_log("Network is up\n\r");

		strcpy( pcMessage, "IP=" );
		pxIPAddress = ( struct in_addr* ) &( pxNetIf->ip_addr );
		strcat( pcMessage, inet_ntoa( ( *pxIPAddress ) ) );
		krs_log("%s\n\r",pcMessage );
	}
	else
	{
		krs_log("Network is down\n\r");
	}
}
*/
struct timeval eth_linux_ms2time(uint32_t time_ms)
{
    struct timeval tv;
    uint64_t sec = 0;

    tv.tv_sec = time_ms/1000;
    tv.tv_usec = (time_ms%1000)*1000;
    return tv;
}


#endif // #if SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LWIP

/* end of file */
