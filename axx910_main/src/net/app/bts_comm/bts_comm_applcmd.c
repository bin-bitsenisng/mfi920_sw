/************************************************************************
| Project Name: bts_comm_applcmd
|    File Name: bts_comm_applcmd.c
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
| 2018.12.27   0.0   SKJ   Creation;
|***********************************************************************/


/* include system primitive types */
#include "bts.h"
#include <string.h>

#include "bts_comm_cfg.h"


#if bts_COMM_APPLCMD_EN == 1
/* include system driver header */
//#include "drivers.h"
#include "if.h"
#include "if/eth/eth.h"
#include "if/eth/eth_datatype.h"
#include "krs_lib.h"

/* include system bsp header */
#include "os.h"

/* include system application header */
#include "sys_param.h"

//#include "modulation.h"
#include "rsp_main.h"
//#include "rsp_task.h"
//#include "schd_task.h"
#include "thread_manager_cfg.h"
#include <sched.h>
//#include "snr_task.h"

/* final include module header */
#include "bts_comm.h"
#include "bts_comm_appl.h"
#include "bts_comm_applcmd.h"
#include "bts_comm_applcmd_callback.h"
#include "bts_comm_cmd.h"
#include "bts_comm_packet.h"
#include "bts_comm_status.h"
//#include "mtd_app.h"


#define bts_COMM_APPLCMD_LOG_EN SYS_PARAM_CONSOLELOG.bts_log_module_comm_appl_callback_en

#if bts_COMM_CALLBACK_DEBUG == 1
#define bts_comm_applcmd_log \
    if(bts_COMM_APPLCMD_LOG_EN != 0) \
    krs_log
#else
#define bts_comm_applcmd_log krs_log_dummy
#endif



/* declare global variables */
//os_task_t task_comm_applcmd_udptask;
//os_task_t task_comm_applcmd_udpbroadcasttask;
//os_task_t task_comm_applcmd_tcptask;
//os_task_t task_comm_console_udptask;
pthread_t task_comm_applcmd_udptask;
pthread_t task_comm_applcmd_udpbroadcasttask;
pthread_t task_comm_applcmd_tcptask;
pthread_t task_comm_console_udptask;

uint8_t udp_rxbuff[bts_COMM_APPLCMD_CALLBACK_JSONBUFFSIZE];
uint8_t udp_txbuff[bts_COMM_APPLCMD_CALLBACK_JSONBUFFSIZE];
uint8_t tcp_rxbuff[bts_COMM_APPLCMD_CALLBACK_JSONBUFFSIZE];
uint8_t tcp_txbuff[bts_COMM_APPLCMD_CALLBACK_JSONBUFFSIZE];
uint8_t udp_console_txbuff[1460];

/* static function prototypes */
void bts_comm_applcmd_udp_task(void *pvParameters);
void bts_comm_applcmd_tcp_task(void *pvParameters);
void bts_comm_console_udp_task(void *pvParameters);
int32_t bts_comm_applcmd_sendresponse(bts_comm_applcmd_packet_t *pkt);
bts_ret_t bts_comm_send_wake_on_lan_packet(char_t *macstr);
/* functions */

// object


/******************************************************************************
 * function name : bts_comm_applcmd_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return void description
 * modification date : 2018.12.27
 *****************************************************************************/
void bts_comm_applcmd_init(void)
{
    /* module init code here*/
/*	os_task_create(bts_comm_applcmd_udp_task, "cmdudpu", TASKMGR_NET_APP_TASK_STACKSIZE, (void*)bts_COMM_APPLCMD_UDP_LOCAL_UNICAST_PORT,
                TASKMGR_NET_COMM_APPLCMD_TASK_PRIORITY, &task_comm_applcmd_udptask);
	os_task_create(bts_comm_applcmd_udp_task, "cmdudpb", TASKMGR_NET_APP_TASK_STACKSIZE, (void*)bts_COMM_APPLCMD_UDP_LOCAL_BROADCAST_PORT,
                TASKMGR_NET_COMM_APPLCMD_TASK_PRIORITY, &task_comm_applcmd_udpbroadcasttask);
	os_task_create(bts_comm_applcmd_tcp_task, "cmdtcp", TASKMGR_NET_APP_TASK_STACKSIZE, 0,
    		TASKMGR_NET_COMM_APPLCMD_TASK_PRIORITY, &task_comm_applcmd_tcptask);
	os_task_create(bts_comm_console_udp_task, "consoleudp", TASKMGR_NET_APP_TASK_STACKSIZE, (void*)bts_COMM_APPL_CONSOLE_UDP_PORT,
    		TASKMGR_NET_COMM_APPLCMD_TASK_PRIORITY, &task_comm_console_udptask);*/

	pthread_attr_t thread_attr;
	struct sched_param param;
	
	pthread_attr_init(&thread_attr);
	pthread_attr_getschedparam(&thread_attr, &param);
	param.sched_priority = TASKMGR_NET_COMM_APPLCMD_TASK_PRIORITY;
	pthread_attr_setschedparam(&thread_attr, &param);
	
	pthread_create(&task_comm_applcmd_udptask, &thread_attr, bts_comm_applcmd_udp_task, (void*)bts_COMM_APPLCMD_UDP_LOCAL_UNICAST_PORT);
	pthread_create(&task_comm_applcmd_udpbroadcasttask, &thread_attr, bts_comm_applcmd_udp_task, (void*)bts_COMM_APPLCMD_UDP_LOCAL_BROADCAST_PORT);
	pthread_create(&task_comm_applcmd_tcptask, &thread_attr, bts_comm_applcmd_tcp_task, NULL);
}



/******************************************************************************
 * function name : bts_comm_applcmd_udp_task
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *pvParameters description
 * \return void description
 * modification date : 2018.12.27
 *****************************************************************************/
void bts_comm_applcmd_udp_task(void *pvParameters)
{
    eth_socket_t sockfd;
    eth_sockaddr_in_t xClient;
    eth_socklen_t xClientLength = sizeof(xClient);
    bts_comm_applcmd_packet_t packet={0};
    char_t clientip[16]="";
    int32_t n;
    int32_t rxsize = 0;
    int32_t termination_request=0;
    int32_t rxcomplete = 0;
    uint16_t port;


    port = (uint16_t)((uint32_t)pvParameters);

    krs_log("bts_comm_applcmd_udp_task start, port is %d\n\r", port);


    while(eth_is_setup_complete() != retOK)
        ;



    for(;;)
    {
    	if(eth_link_isvalid()==retFail)
    	{
    		os_sleep(1000);
    		continue;
    	}

        sockfd = eth_open_udpserver_socket(port, bts_COMM_APPL_UDPCONNECT_TIMEOUT);
        if(sockfd == 0)
        {
            krs_log("bts_comm_applcmd_udp_task: UDP socket fail.\n\r");
            continue;
        }


        for(;;)
        {
        	bts_comm_applcmd_log("bts_comm_applcmd_udp_task: waiting sid/did read/write request.\n\r");
        	termination_request = 0;
        	rxcomplete = 0;
        	rxsize = 0;
        	do
        	{
        		n = eth_recvfrom(sockfd, (void *)&udp_rxbuff[rxsize], (sizeof(udp_rxbuff)-rxsize), 0, (eth_sockaddr_t*)&xClient, &xClientLength);
        		packet.rxtimestamp = os_time_us();
        		bts_comm_applcmd_log("bts_comm_applcmd_udp_task: eth_udp_recv %d bytes\n\r", n);

				if(n <= 0)
				{
					termination_request = 1;
					break;
				}

				rxsize += n;

				if(udp_rxbuff[rxsize-1] == 0 || (rxsize >=sizeof(udp_rxbuff)))
				{
					rxcomplete = 1;
					bts_comm_applcmd_log("bts_comm_applcmd_udp_task: rxcomplete\n\r");
					//rsm_task_wdg_clear();
				}

        	}while(rxcomplete == 0);

        	if(termination_request == 1)
        	{
        		bts_comm_applcmd_log("bts_comm_applcmd_udp_task: eth_udp_recv error or timeout.\n\r");
        		break;
        	}

            bts_comm_applcmd_log("bts_comm_applcmd_udp_task: %ld byte received.\n\r", n);
            eth_get_ipaddr_ntoa(xClient.sin_addr.s_addr, clientip, sizeof(clientip));
            bts_comm_applcmd_log("message from %s:%d\n\r", clientip, xClient.sin_port);
            bts_comm_applcmd_log("%.*s\n\r", rxsize, (const char *)udp_rxbuff);

            // response with broadcast?
            if(port == bts_COMM_APPLCMD_UDP_LOCAL_BROADCAST_PORT)
            {
            	xClient.sin_addr.s_addr = 0xFFFFFFFF; //eth_get_broadcast_ip_addr();
            	packet.conn.conntype = bts_comm_applcmd_conntype_udp_broadcast;
            }
            else
            {
            	packet.conn.conntype = bts_comm_applcmd_conntype_udp_unicast;
            }
            // callback dispatch
            packet.conn.premote = &xClient;
            packet.conn.psock = &sockfd;
            packet.rxbuffptr = (char_t *)udp_rxbuff;
            packet.rxsize = rxsize;
            packet.txbuffptr = (char_t *)udp_txbuff;
            packet.txsize = 0;
            packet.txen = 0;

            bts_comm_applcmd_callback_dispactch(&packet);

            bts_comm_applcmd_sendresponse(&packet);

            bts_comm_applcmd_log("bts_comm_applcmd_udp_task send complete\n\r",n);
        }
        eth_close(sockfd);
    }
}





/******************************************************************************
 * function name : bts_comm_applcmd_tcp_task
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *pvParameters description
 * \return void description
 * modification date : 2019.11.25
 *****************************************************************************/
void bts_comm_applcmd_tcp_task(void *pvParameters)
{
	eth_socket_t listensocket;
	eth_socket_t connectsocket;
    bts_comm_applcmd_packet_t packet={0};
    int32_t n;
    int32_t rxsize = 0;
    int32_t termination_request=0;
    int32_t rxcomplete = 0;
    int32_t ret;



    krs_log("bts_comm_applcmd_tcp_task start.\n\r");

    while(eth_is_setup_complete() != retOK);

    listensocket = -1;
    connectsocket = -1;
    for(;;)
    {
    	if(eth_link_isvalid()==retFail)
    	{
    		os_sleep(1000);
    		continue;
    	}

    	ret = eth_open_tcpserver_socket(bts_COMM_APPLCMD_TCP_LOCAL_PORT,
    												  &listensocket,
    	                                              &connectsocket,
													  bts_COMM_APPL_TCPCONNECT_TIMEOUT, bts_COMM_APPL_TCPSEND_TIMEOUT,
													  bts_COMM_APPL_TCPRECEIVE_TIMEOUT);

    	if(ret != retOK)
        {
    		bts_comm_applcmd_log("bts_comm_applcmd_tcp_task: TCP server open fail.\n\r");
            continue;
        }

    	bts_comm_applcmd_log("bts_comm_applcmd_tcp_task: TCP server open success.\n\r");

        for(;;)
        {
        	bts_comm_applcmd_log("bts_comm_applcmd_tcp_task: waiting sid/did read/write request.\n\r");
        	termination_request = 0;
        	rxcomplete = 0;
        	rxsize = 0;
        	do
        	{
        		bts_comm_applcmd_log("bts_comm_applcmd_tcp_task: connectsocket : 0x%08X\n\r", connectsocket);

        		n = eth_recv(connectsocket, (void *)&tcp_rxbuff[rxsize], (sizeof(tcp_rxbuff)-rxsize), 0);
        		bts_comm_applcmd_log("bts_comm_applcmd_tcp_task: eth_recv %d bytes\n\r", n);

				if(n < 0)
				{
					termination_request = 1;
					break;
				}

				if(n==0)
				{
					bts_comm_applcmd_log("bts_comm_applcmd_tcp_task receive timeout\n\r");
					continue;
				}


				rxsize += n;

				if(tcp_rxbuff[rxsize-1] == 0 || (rxsize >=sizeof(tcp_rxbuff)))
				{
					rxcomplete = 1;
					bts_comm_applcmd_log("bts_comm_applcmd_tcp_task: rxcomplete\n\r");
					//rsm_task_wdg_clear();
				}

        	}while(rxcomplete == 0);

        	if(termination_request == 1)
        	{
        		bts_comm_applcmd_log("bts_comm_applcmd_tcp_task: eth_recv error or timeout.\n\r");
        		break;
        	}

            bts_comm_applcmd_log("bts_comm_applcmd_tcp_task: %ld byte received.\n\r", n);
            bts_comm_applcmd_log("%.*s\n\r", rxsize, (const char *)tcp_rxbuff);




            // callback dispatch
            packet.conn.premote = NULL;
            packet.conn.psock = &connectsocket;
            packet.conn.conntype = bts_comm_applcmd_conntype_tcp;
            packet.rxbuffptr = (char_t *)tcp_rxbuff;
            packet.rxsize = rxsize;
            packet.txbuffptr = (char_t *)tcp_txbuff;
            packet.txsize = 0;
            packet.txen = 0;

            bts_comm_applcmd_callback_dispactch(&packet);

            bts_comm_applcmd_sendresponse(&packet);
            bts_comm_applcmd_log("bts_comm_applcmd_tcp_task send complete\n\r",n);
        }

        eth_close_tcpserver_socket(&listensocket,&connectsocket,bts_COMM_APPL_TCPRECEIVE_TIMEOUT);
    }

}



int32_t bts_comm_applcmd_sendresponse(bts_comm_applcmd_packet_t *pkt)
{
    int32_t remainsize=0;
    int32_t txsize=0;
    int32_t offset=0;
    int32_t n;

    pkt->txbuffptr[pkt->txsize++] = 0;
    bts_comm_applcmd_log("pkt->txsize:%d, pkt->txbuffptr:%.*s\n\r", pkt->txsize, pkt->txsize, pkt->txbuffptr);
    remainsize = pkt->txsize;
    offset = 0;

    while(remainsize > 0)
    {
        txsize = remainsize;
        if(pkt->conn.conntype == bts_comm_applcmd_conntype_tcp)
        {
            n = eth_send(*pkt->conn.psock, (void *)&pkt->txbuffptr[offset], txsize, 0);
            bts_comm_applcmd_log("bts_comm_applcmd_tcp_task send %dbytes\n\r",n);
        }
        else
        {
            if(remainsize > 1400)
            {
                txsize = 1400;
            }
            n = eth_sendto(*pkt->conn.psock, (void *)&pkt->txbuffptr[offset], txsize, 0, pkt->conn.premote, (socklen_t)sizeof(eth_sockaddr_in_t));
            bts_comm_applcmd_log("bts_comm_applcmd_udp_task send %dbytes\n\r",n);
        }
        remainsize -=n;
        offset +=n;
    }
    return retOK;
}



void bts_comm_console_udp_task(void *pvParameters)
{
    eth_socket_t sockfd;
    eth_sockaddr_in_t xServer;
    uint16_t port;
    int32_t n;
    int32_t txsize;

    port = (uint16_t)((uint32_t)pvParameters);
    krs_log("bts_comm_console_udp_task start, port is %d\n\r", port);
    while(eth_is_setup_complete() != retOK);

    for(;;)
    {
    	if(eth_link_isvalid()==retFail)
    	{
    		os_sleep(1000);
    		continue;
    	}

    	if(SYS_PARAM_CONSOLEUDP.en != 1)
    	{
    		os_sleep(1000);
    		continue;
    	}


        sockfd = eth_open_udpclient_socket(bts_COMM_APPL_UDPCONNECT_TIMEOUT);
        if(sockfd == 0)
        {
            krs_log("bts_comm_console_udp_task: UDP socket fail.\n\r");
            continue;
        }


        for(;;)
        {
        	memset(&xServer, 0, sizeof(eth_sockaddr_in_t));
        	xServer.sin_family = AF_INET;
        	xServer.sin_port = eth_htons(SYS_PARAM_CONSOLEUDP.port);
        	xServer.sin_addr.s_addr = eth_inet_addr(SYS_PARAM_CONSOLEUDP.ip);

        	txsize = bts_log_read(udp_console_txbuff, 1400, 1000);
        	if(txsize > 0)
        	{
        		n = eth_sendto(sockfd, udp_console_txbuff, txsize, 0, (eth_sockaddr_t*)&xServer, (socklen_t)sizeof(xServer));
        		if(n<=0)
        		{
        			break;
        		}
        	}
        	if(SYS_PARAM_CONSOLEUDP.en != 1)
        	{
        		break;
        	}
        }
        eth_close(sockfd);
    }
}


bts_ret_t bts_comm_send_wake_on_lan_packet(char_t *macstr)
{
	uint8_t magicpacket[6*17];
	uint8_t targetmac[6];
	uint8_t i;
	eth_socket_t sockfd;
	eth_sockaddr_in_t xServer;
	int32_t n;

	bts_comm_applcmd_log("send wol packet\n\r");
	if(eth_get_macaddr_fromstring(targetmac, macstr) != retOK)
	{
		bts_comm_applcmd_log("send wol packet : parsing macstring to mac was fail\n\r");
		return retFail;
	}

	// build WOL magic packet
	for(i=0;i<6;i++)
	{
		magicpacket[i]=0xFF;
	}
	for(i=0;i<16;i++)
	{
		krs_memcopy(&magicpacket[6 + i*6], targetmac, 6);
	}

	bts_comm_applcmd_log("send wol packet to udp with 255.255.255.255:7\n\r");
	sockfd = eth_open_udpclient_socket(bts_COMM_APPL_UDPCONNECT_TIMEOUT);
	bts_comm_applcmd_log("wol socket is 0x%08X\n\r", sockfd);
	memset(&xServer, 0, sizeof(eth_sockaddr_in_t));
	xServer.sin_family = AF_INET;
	xServer.sin_port = eth_htons(7);
	xServer.sin_addr.s_addr = eth_inet_addr("192.168.10.255");
	n=eth_sendto(sockfd, magicpacket, sizeof(magicpacket), 0, (eth_sockaddr_t*)&xServer, (socklen_t)sizeof(xServer));
	bts_comm_applcmd_log("sent wol packet size is %dbytes\n\r", n);
	eth_close(sockfd);
	if(n!=sizeof(magicpacket))
	{
		bts_comm_applcmd_log("sent wol packet fail\n\r");
		return retFail;
	}
	return retOK;
}

#endif // #if bts_COMM_APPLCMD_EN == 1


/* end of file */
