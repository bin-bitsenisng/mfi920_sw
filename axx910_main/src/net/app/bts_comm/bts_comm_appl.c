/************************************************************************
| Project Name: bts_comm_appl
|    File Name: bts_comm_appl.c
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
| 2017.10.11   0.0   SKJ   Creation;
|***********************************************************************/


/* include system primitive types */
#include "bts.h"
#include "bts_comm_applcmd.h"
#include <string.h>
#include <pthread.h>
#include <sched.h>

#include "bts_comm_cfg.h"

/* include system driver header */
//#include "drivers.h"
#include "if.h"
#include "if/eth/eth.h"
#include "if/eth/eth_datatype.h"
#include "krs_lib.h"

/* include system bsp header */
#include "os.h"

/* include system application header */
#include "system.h"
#include "sys_param.h"

//#include "modulation.h"
#include "rsp_main.h"
//#include "rsp_task.h"
#include "rsp_thread.h"
#include "thread_manager_cfg.h"
//#include "schd_task.h"
//#include "snr_task.h"


/* final include module header */
#include "bts_comm.h"
#include "bts_comm_appl.h"
#include "bts_comm_cmd.h"
#include "bts_comm_packet.h"
#include "bts_comm_status.h"

#include "bts_queue.h"
/* declare global variables */


//timer_timemeasurement_t frameratetimer;

/* declare static variables */
os_time_t bts_comm_appl_connection_timeout = 0;

/* static function prototypes */
//os_task_t comm_appl_task_handle;
//os_task_t comm_appl_rx_task_handle;
//os_task_t comm_appl_tx_task_handle;
//os_task_t comm_apppacket_task_handle[SYS_PARAM_APPPKT_MAX];
pthread_t comm_appl_task_handle;
pthread_t comm_appl_rx_task_handle;
pthread_t comm_appl_tx_task_handle;
pthread_t comm_apppacket_task_handle[SYS_PARAM_APPPKT_MAX];

static uint8_t cnt_image_msg;
eth_socket_t xConnectedSocket = -1;



/* functions */

// object


#define ETH_TCP_RECEIVE_BUFFER_SIZE bts_COMM_RX_BUFFER_SIZE
uint8_t bts_comm_eth_rxbuff[ETH_TCP_RECEIVE_BUFFER_SIZE];
uint8_t eth_receive_buffer[ETH_TCP_RECEIVE_BUFFER_SIZE];
fifo_t eth_receive_fifo;
uint8_t eth_receive_state;
int32_t eth_receive_remainsize = 0;
int32_t eth_receive_wrindex = 0;


void bts_comm_appl_tx_task(void *pvParameters);
void bts_comm_appl_rx_task(void *pvParameters);

void bts_comm_appl_eth_receive_reset(void);
int32_t bts_comm_appl_eth_receive(eth_socket_t tcpsd, uint8_t *desbuff, int32_t desbuffsize, int32_t rsize);
int32_t bts_comm_appl_get_commpacket(eth_socket_t tcpsd, uint8_t *desbuff, int32_t desbuffsize);
int32_t bts_comm_appl_loop(eth_socket_t tcpsd);


// app data task & queue
bts_comm_apppacket_info_t bts_comm_apppacket_info[SYS_PARAM_APPPKT_MAX];


void bts_comm_apppacket_task(void *pvParameters);


/******************************************************************************
 * function name : bts_comm_appl_init
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
 * modification date : 2017.10.11
 *****************************************************************************/
void bts_comm_appl_init(void)
{
	pthread_attr_t thread_attr;
	struct sched_param param;
    int32_t i;
    /* module init code here*/
    krs_memclear(bts_comm_eth_rxbuff);
    krs_memclear(eth_receive_buffer);
    krs_memclearitem(bts_comm_apppacket_info);


    bts_comm_appl_dataset_init();
    bts_comm_appl_common_init();
    bts_comm_appl_status_init();
    bts_comm_appl_object_init();
    bts_comm_appl_track_init();
    bts_comm_appl_image_init();
    //bts_comm_appl_canlog_init();
    bts_comm_appl_its_init();
    //bts_comm_appl_vf_init();
    //bts_comm_appl_fcw_init();
    //bts_comm_appl_flog_init();
    bts_comm_appl_raw_init();
    //bts_comm_appl_rs485_init();


    bts_comm_init();

    cnt_image_msg = 0;

    //os_task_create(bts_comm_appl_task, "appltcp", TASKMGR_NET_APP_TASK_STACKSIZE, 0,
    //            TASKMGR_NET_APP_APPLCOMM_TASK_PRIORITY, &comm_appl_task_handle);
	pthread_attr_init(&thread_attr);
	pthread_attr_getschedparam(&thread_attr, &param);
	param.sched_priority = TASKMGR_NET_APP_APPLCOMM_TASK_PRIORITY;
	pthread_attr_setschedparam(&thread_attr, &param);
	pthread_create(&comm_appl_task_handle, &thread_attr, bts_comm_appl_task, NULL);
	

    for(i = 0; i < SYS_PARAM_APPPKT_MAX; i++)
    {
        bts_comm_apppacket_info[i].id = i;
        bts_comm_apppacket_info[i].connected = 0;
        bts_queue_init(&bts_comm_apppacket_info[i].bq,
                       (uint8_t *)bts_comm_apppacket_info[i].buffpool, 1024, 1024);
        //os_task_create(bts_comm_apppacket_task, "apppacket", TASKMGR_NET_APP_TASK_STACKSIZE, (void *)&bts_comm_apppacket_info[i],
        //            TASKMGR_NET_APP_APPLCOMM_TASK_PRIORITY, &comm_apppacket_task_handle[i]);
		pthread_attr_init(&thread_attr);
		pthread_attr_getschedparam(&thread_attr, &param);
		param.sched_priority = TASKMGR_NET_APP_APPLCOMM_TASK_PRIORITY;
		pthread_attr_setschedparam(&thread_attr, &param);
		pthread_create(&comm_apppacket_task_handle[i], &thread_attr, bts_comm_apppacket_task, (void *)&bts_comm_apppacket_info[i]);
    }

#if bts_COMM_APPLCMD_EN == 1
    bts_comm_applcmd_init();
#endif
}


/******************************************************************************
 * function name : bts_comm_appl_task
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
 * modification date : 2017.10.11
 *****************************************************************************/
void bts_comm_appl_task(void *pvParameters)
{
	pthread_attr_t thread_attr;
	struct sched_param param;
	
	eth_socket_t xListeningSocket=0;
	eth_socket_t xConnectedSocket=0;

	int32_t ret;
	void* tx_task_ret_val;


    krs_log("AFI910 application comm start!\n\r");
    xListeningSocket = -1;
    xConnectedSocket = -1;
    for(;;)
    {
    	if(eth_link_isvalid()==retFail)
    	{
    		os_sleep(1000);
    		continue;
    	}

		krs_log("Wait for client accept..\n\r");
    	ret = eth_open_tcpserver_socket(bts_COMM_APPL_DAQ_TCP_PORT,
											&xListeningSocket,
											&xConnectedSocket,
											bts_COMM_APPL_TCPCONNECT_TIMEOUT,
											bts_COMM_APPL_TCPSEND_TIMEOUT,
											bts_COMM_APPL_TCPRECEIVE_TIMEOUT);
    	// watchdog........ is it needed?
		// rsm_task_wdg_clear();

    	if(ret != retOK)
        {
    		krs_log("bts_comm_appl_tcp_task: TCP server open fail.\n\r");
            continue;
        }
    	krs_log("bts_comm_appl_tcp_task: TCP server open success.\n\r");


		//os_task_create(bts_comm_appl_tx_task, "apptx", TASKMGR_NET_APP_TASK_STACKSIZE, (void *)&xConnectedSocket,
		//			TASKMGR_NET_APP_APPLCOMM_TXTASK_PRIORITY, &comm_appl_tx_task_handle);
		pthread_attr_init(&thread_attr);
		pthread_attr_getschedparam(&thread_attr, &param);
		param.sched_priority = TASKMGR_NET_APP_APPLCOMM_TXTASK_PRIORITY;
		pthread_attr_setschedparam(&thread_attr, &param);
		pthread_create(&comm_appl_tx_task_handle, &thread_attr, bts_comm_appl_tx_task, (void *)&xConnectedSocket);

        krs_log("enter afi910 appl comm service\n\r");
		// new connection prepare
		// rx buffer flush
		// bts_comm_appl_eth_receive_reset();
		// init timeout variable
		os_timeout_reset(&bts_comm_appl_connection_timeout);
		os_timeout_reset(&bts_comm_timeout_protocol);

		while(bts_comm_appl_loop(xConnectedSocket) == retOK)
		{
			// terminate check
			if(Ir24xCommGetIsDisconnectRequested())
			{
				Ir24xCommSetDisconnected();
				
				// xcp reset
				krs_log("afi910 appl comm termination request is accepted.\n\r");
				break;
			}
			//rsm_task_wdg_clear();
		}
        bts_comm_reset();
        // os_safe_assign(logger_task_active_flag, 0);
        krs_log("shutdown afi910 appl comm connect socket\n\r");
        eth_close_tcpserver_socket(&xListeningSocket,&xConnectedSocket,bts_COMM_APPL_TCPRECEIVE_TIMEOUT);
		//pthread_join(comm_appl_tx_task_handle, NULL);
		pthread_join(comm_appl_tx_task_handle, (void**)&tx_task_ret_val);
    }
}





/******************************************************************************
 * function name : bts_comm_apppacket_task
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
 * modification date : 2019.08.23
 *****************************************************************************/
void bts_comm_apppacket_task(void *pvParameters)
{
	char_t *jsonbuff=NULL;
	uint8_t *packetbuff=NULL;

	eth_socket_t xListeningSocket;
	eth_socket_t xConnectedSocketAppdata;
    bts_comm_apppacket_info_t *apppkt_inst = (bts_comm_apppacket_info_t *)pvParameters;
    char *apppkt_ip="";
    queue_item_t item;
    int32_t trasmitted_size;
    uint16_t apppkt_port;
    bool_t client_mode_en;
    bool_t enable;
    int32_t len;

    uint8_t tcpresprxbuff[32];

    bts_comm_packet_t rxpacketinfo;

    xListeningSocket = -1;
    xConnectedSocketAppdata = -1;
    for(;;)
    {
    	os_sleep(1000);
        apppkt_inst->connected = 0;
        apppkt_ip = SYS_PARAM_APPPKT_PORTS[apppkt_inst->id%SYS_PARAM_APPPKT_MAX].server_ip;
        apppkt_port = SYS_PARAM_APPPKT_PORTS[apppkt_inst->id%SYS_PARAM_APPPKT_MAX].port_num;
        enable = SYS_PARAM_APPPKT_PORTS[apppkt_inst->id%SYS_PARAM_APPPKT_MAX].port_en;
        client_mode_en = SYS_PARAM_APPPKT_PORTS[apppkt_inst->id%SYS_PARAM_APPPKT_MAX].client_mode_en;




    	if(enable == 0 || eth_link_isvalid()==retFail)
    	{
    		continue;
    	}

        krs_log("bts_comm_apppacket_task[id:%d][port:%d] %s start and %s\n\r",
        		apppkt_inst->id, apppkt_port,
    			client_mode_en ? "client mode":"server mode",
    			enable ? "enable":"disable");

    	if(client_mode_en == 0)
    	{
    		// Server Mode

    		if(eth_open_tcpserver_socket(apppkt_port,
    				&xListeningSocket,
    				&xConnectedSocketAppdata,
    				bts_COMM_APPL_TCPCONNECT_TIMEOUT,
					bts_COMM_APPL_TCPSEND_TIMEOUT,
					bts_COMM_APPL_TCPRECEIVE_TIMEOUT) == retFail)
    		{
    			//krs_log("bts_comm_apppacket_task[id:%d][port:%d] server mode open fail\n\r", apppkt_inst->id, apppkt_port);
    			continue;
    		}
    		//krs_log("bts_comm_apppacket_task[id:%d][port:%d] server mode open OK\n\r", apppkt_inst->id, apppkt_port);

    		// update server_request_info

    	}
    	else
    	{
    		// Client Mode
    		if(eth_open_tcpclient_socket( apppkt_ip,
    				apppkt_port,
    				&xConnectedSocketAppdata,
					bts_COMM_APPL_TCPSEND_TIMEOUT,
					bts_COMM_APPL_TCPRECEIVE_TIMEOUT) == retFail)
    		{
    			//krs_log("bts_comm_apppacket_task[id:%d][port:%d] client mode open fail\n\r", apppkt_inst->id, apppkt_port);
    			continue;
    		}

    		//krs_log("bts_comm_apppacket_task[id:%d][port:%d] client mode OK\n\r", apppkt_inst->id, apppkt_port);
    		packetbuff = (uint8_t *)os_malloc(SYS_PARAM_JSON_BUFFER_SIZE);
    		jsonbuff = (char_t *)os_malloc(SYS_PARAM_JSON_BUFFER_SIZE);
    		len = system_get_status_to_json(jsonbuff, SYS_PARAM_JSON_BUFFER_SIZE);
    		krs_log("server request data : %.*s\n\r", len, jsonbuff);


   			// send server set status with timeout 60.0s
    		len = bts_comm_appl_system_status_packetbuild(packetbuff, SYS_PARAM_JSON_BUFFER_SIZE, jsonbuff, len);
    		trasmitted_size = eth_send(xConnectedSocketAppdata, packetbuff, len, 0);
   			// receive response
    		os_free(jsonbuff);
    		os_free(packetbuff);

    		bts_comm_appl_get_commpacket(xConnectedSocketAppdata, tcpresprxbuff, sizeof(tcpresprxbuff));

    		bts_commpacket_parse_cro_packet(&rxpacketinfo, tcpresprxbuff);
			if(rxpacketinfo.cro.header.u8pid != IR24XCOMMRESP_RES)
			{
				continue;
			}
			krs_log("server access complete\n\r");
    	}

		krs_log("bts_comm_apppacket_task[id:%d][port:%d] enter appdata service, socket:0x%08lX\n\r", apppkt_inst->id, apppkt_port,xConnectedSocketAppdata);
		apppkt_inst->connected = 1;



		while(1)
		{
			if(bts_queue_peek(&apppkt_inst->bq, &item, 5000) == retOK)
			{
				trasmitted_size = eth_send(xConnectedSocketAppdata, item.buffptr, item.size, 0);
				if(trasmitted_size == item.size)
				{
					bts_queue_remove(&apppkt_inst->bq);
					//rsm_task_wdg_clear();
				}
				else
				{
					krs_log("bts_comm_apppacket_task[id:%d][port:%d] send timeout or disconnected : %d\n\r", apppkt_inst->id, apppkt_port, trasmitted_size);
					break;
				}
			}
		}
        apppkt_inst->connected = 0;
        bts_queue_reset(&apppkt_inst->bq);
    	if(client_mode_en == 0)
    	{
    		eth_close_tcpserver_socket(&xListeningSocket, &xConnectedSocketAppdata, bts_COMM_APPL_TCPRECEIVE_TIMEOUT);
    	}
    	else
    	{
    		eth_close_tcpclient_socket(&xConnectedSocketAppdata, bts_COMM_APPL_TCPRECEIVE_TIMEOUT);
    	}
    }
}


/******************************************************************************
 * function name : bts_comm_appdata_push
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *inst description
 * \param1 *srcbuff description
 * \param2 size description
 * \return void description
 * modification date : 2019.08.23
 *****************************************************************************/
void bts_comm_appdata_push(bts_comm_apppacket_info_t *apppkt_inst, uint8_t *srcbuff, size_t size)
{
    if(apppkt_inst->connected == 1)
    {
        if(bts_queue_put(&apppkt_inst->bq, srcbuff, size, 0) != retOK)
        {
            bts_queue_reset(&apppkt_inst->bq);
        }
    }
}


/******************************************************************************
 * function name : bts_comm_appl_rx_task
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
 * modification date : 2019.08.23
 *****************************************************************************/
void bts_comm_appl_rx_task(void *pvParameters)
{
    eth_socket_t tcpsd = (eth_socket_t)pvParameters;

    krs_log("bts_comm_appl_rx_task start\n\r");
    os_sleep(1000);
    krs_log("bts_comm_appl_rx_task terminate\n\r");

    os_tasknoti_set(comm_appl_task_handle, 0x01);

    krs_unused_param(tcpsd);
    //vTaskDelete(NULL);
}


/******************************************************************************
 * function name : bts_comm_appl_tx_task
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
 * modification date : 2019.08.23
 *****************************************************************************/
void bts_comm_appl_tx_task(void *pvParameters)
{
    eth_socket_t *xConnectedSocket = ((eth_socket_t *)pvParameters);
    int32_t trasmitted_size;
    int32_t remain_size;
    int32_t offset;
    //bts_comm_queue_t txqueinfo;
	queue_item_t txqueinfo;
	void* ret_val;

    krs_log("bts_comm_appl_tx_task start, connected socket is 0x%08X\n\r", *xConnectedSocket);


    while(1)
    {
        trasmitted_size = 0;
        if(*xConnectedSocket < 0)
        {
        	krs_log("invalid connected socket, bts_comm_appl_tx_task will be terminated\n\r");
        	break;
        }
        else
        {
            if(bts_comm_get_packets_from_txqueue(&txqueinfo, bts_COMM_APPL_TCPSEND_TIMEOUT / 5) == retOK)
            {
//#if(bts_COMM_DEBUG == 1) && (bts_COMM_DEBUG_VERBOSE == 1)
                //krs_log("bts_comm_get_packets_from_txqueue:[0x%08X]:%dbytes\n\r", txqueinfo.buffptr,
                //        txqueinfo.size);
                //krs_log("\n\r\n\r");
                //krs_log("*****************************************\n\r");
                //krs_log("*** bts_comm_appl_tx_task: Tx packet ****\n\r");
                //krs_log("*****************************************\n\r");
                //krs_log("length : %d\n\r", txqueinfo.size);
				//krs_log("data : ");				
				/*printf("(");
				for(int i=0;i<txqueinfo.size;i++)
				{
					printf("%c",txqueinfo.buffptr[i]);
				}*/				
				if(txqueinfo.size > 10)
				{/*
					cJSON* jsonbuff = cJSON_Parse(&txqueinfo.buffptr[9]);
    				krs_log("%s\n", cJSON_Print(jsonbuff));*/
				}
				//krs_log("\n\n\r");
				
//#endif
                remain_size = txqueinfo.size;
                trasmitted_size = 0;
                offset = 0;
                while(remain_size > 0)
                {                	
					if(*xConnectedSocket < 0)
						break;
					
					//trasmitted_size = eth_send(*xConnectedSocket, &txqueinfo.bufferptr[offset], remain_size, 0);
					trasmitted_size = eth_send(*xConnectedSocket, &txqueinfo.buffptr[offset], remain_size, MSG_NOSIGNAL);

                	if(trasmitted_size < 0)
					{
						krs_log("tcp tx error\n\r");
						eth_print_errmsg(trasmitted_size);
						*xConnectedSocket = -1;
						break;
					}
                	//rsm_task_wdg_clear();
                	remain_size -= trasmitted_size;
                	offset += trasmitted_size;
                }
                os_timeout_reset(&bts_comm_appl_connection_timeout);
            }
        }
    }

//  vTaskDelete(NULL);
	krs_log("bts_comm_appl_tx_task terminated.\n\r");
	pthread_exit(ret_val);
}


/******************************************************************************
 * function name : bts_comm_appl_eth_receive_reset
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
 * modification date : 2017.10.11
 *****************************************************************************/
void bts_comm_appl_eth_receive_reset(void)
{
    krs_memclear(eth_receive_buffer);
    fifo_create(&eth_receive_fifo, eth_receive_buffer, ETH_TCP_RECEIVE_BUFFER_SIZE);
    eth_receive_state = 0;
    eth_receive_remainsize = 0;
    eth_receive_wrindex = 0;
}


/******************************************************************************
 * function name : bts_comm_appl_eth_receive
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 tcpsd description
 * \param1 *desbuff description
 * \param2 rsize description
 * \return int32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
int32_t bts_comm_appl_eth_receive(eth_socket_t tcpsd, uint8_t *desbuff, int32_t desbuffsize, int32_t rsize)
{
	int32_t n;
    int32_t received_size = 0;
    int32_t remain_size = 0;


    if(tcpsd == 0)
    {
        krs_log("eth_receive tcp socket invalid tcpsd:0x%08lX\n\r", (uint32_t)tcpsd);
        return -1;
    }

    if(rsize > desbuffsize)
    {
    	krs_log("desbuffsize is small, must be greater than or equal rsize\n\r");
    	return -1;
    }

    received_size = 0;
    remain_size = rsize;
    while(remain_size > 0)
    {
    	n = eth_recv(tcpsd, &desbuff[received_size], remain_size, 0);
    	if(n > 0)
    	{
    		received_size += n;
    		remain_size -= n;
    	}
    	else
    	{
    		if(n != 0)
    		{
    			//krs_log("bts_comm_appl_loop: bts_comm_appl_get_commpacket error  %ld\n\r", received_size);
				krs_log("bts_comm_appl_loop: bts_comm_appl_get_commpacket error  %ld\n\r", n);
    			eth_print_errmsg(received_size);
    		}
    		return n;
    	}
    }

    if(rsize == received_size)
    {
    	return received_size;
    }
    else
    {
    	return 0;
    }


}


/******************************************************************************
 * function name : bts_comm_appl_get_commpacket
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 tcpsd description
 * \param1 *desbuff description
 * \return int32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
int32_t bts_comm_appl_get_commpacket(eth_socket_t tcpsd, uint8_t *desbuff, int32_t desbuffsize)
{
    int32_t ret = 0;
    int32_t headerlen = 0;
    uint32_t sync;

	// get header
	ret = bts_comm_appl_eth_receive(tcpsd, &desbuff[0], desbuffsize, 8);
	if(ret == 8)
	{
		headerlen = bts_commget_header_u24len(&desbuff[0]);
		sync = bts_commget_header_u32sync(desbuff);
		if(sync != 0x3C3C3C3C)
		{
			krs_log_error("mismatch sync feild 0x%08X\n\r", sync);
			return 0;
		}
	}
	else
	{
		return ret;
	}

	// get data
	ret = bts_comm_appl_eth_receive(tcpsd, &desbuff[8],desbuffsize-8,  headerlen);
	// krs_log("s1 ret-%d headerlen-%d\n", ret, headerlen);
	if(ret == headerlen)
	{
		return (headerlen + 8);
	}
	else
	{
		return ret;
	}
}


/******************************************************************************
 * function name : bts_comm_appl_loop
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 tcpsd description
 * \return int32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
int32_t bts_comm_appl_loop(eth_socket_t tcpsd)
{
    int32_t received_size;
    int32_t protocol_timeout;

#if bts_COMM_DEBUG == 1
    bts_comm_packet_t txpacketinfo;
#endif
    // uint32_t currtime;

    if(tcpsd < 0)
    {
        krs_log_error("bts_comm_appl_loop: tcpsd is null, socket error\n\r");
        return retFail;
    }




    received_size = bts_comm_appl_get_commpacket(tcpsd, bts_comm_eth_rxbuff, sizeof(bts_comm_eth_rxbuff));
#if(bts_COMM_DEBUG == 1) && (bts_COMM_DEBUG_VERBOSE == 2)
    krs_log("bts_comm_appl_loop eth_recv unblocking check\n\r");
#endif

    if(received_size > 0)
    {
#if bts_COMM_DEBUG == 1
        krs_log_info("bts_comm_appl_loop: received_size is %d\n\r", received_size);
#endif
        os_timeout_reset(&bts_comm_appl_connection_timeout);
        //rsm_task_wdg_clear();
        protocol_timeout = bts_comm_command(bts_comm_eth_rxbuff, received_size);
    }
    else
    {
    	if(eth_errcheck_timeout(received_size) == retOK)
    	{
        	if(Ir24xCommGetIsStartStopSynchModeStart())
        	{
        		os_timeout_reset(&bts_comm_appl_connection_timeout);
        	}

    	    if(os_timeout_expired(&bts_comm_appl_connection_timeout, bts_COMM_APPL_PROTOCOL_TIMEOUT) == retOK)
    	    {
    			bts_comm_send_error_async(tcpsd, IR24XCOMMRESP_ERR_CMD_SYNTAX);
    			os_sleep(500);
    			return retFail;
    	    }
    	}
    	else
    	{
#if bts_COMM_DEBUG == 1
    		krs_log_error("bts_comm_appl_loop: bts_comm_appl_get_commpacket error  %ld\n\r", received_size);
#endif
    		return retFail;
    	}
    }

    krs_unused_param(protocol_timeout);
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_appl_packetbuild
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *pvParameters description
 * \return int32_t description
 * modification date : 2019.08.22
 *****************************************************************************/
int32_t bts_comm_appl_packetbuild(void *pvParameters)
{
    bts_comm_set_timestamp(rsp_timestamp_us);

    bts_comm_appl_pid_status_packetbuild();
    bts_comm_appl_pid_object_packetbuild();
    bts_comm_appl_pid_track_packetbuild();
    bts_comm_appl_pid_image_packetbuild();
    bts_comm_appl_pid_canlog_packetbuild();
    bts_comm_appl_pid_app_its_packetbuild();
    bts_comm_appl_pid_app_vf_packetbuild();
    bts_comm_appl_pid_app_fcw_packetbuild();
    bts_comm_appl_rs485_packetbuild();
	bts_comm_appl_pid_ai_object_packetbuild();
	bts_comm_appl_pid_lane_detection_packetbuild();
	bts_comm_appl_pid_freespace_packetbuild();
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_appl_send
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return int32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
int32_t bts_comm_appl_send(void *pvParameters)
{
    bts_comm_appl_pid_status_packetsend();
    bts_comm_appl_pid_object_packetsend();
    bts_comm_appl_pid_track_packetsend();
    bts_comm_appl_pid_image_packetsend();
    bts_comm_appl_pid_canlog_packetsend();
    bts_comm_appl_pid_app_its_packetsend();
    bts_comm_appl_pid_app_vf_packetsend();
    bts_comm_appl_pid_app_fcw_packetsend();
    bts_comm_appl_pid_raw_packetbuild_and_send();
    bts_comm_appl_rs485_packetsend();
	bts_comm_appl_pid_ai_object_packetsend();
	bts_comm_appl_pid_lane_detection_packetsend();
	bts_comm_appl_pid_freespace_packetsend();
	return retOK;
}


/* end of file */
