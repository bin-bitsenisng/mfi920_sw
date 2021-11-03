/************************************************************************
| Project Name: bts_comm
|    File Name: bts_comm.c
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

#include <stdarg.h>
#include <stdio.h>
/* include system driver header */


/* include system bsp header */


/* include system application header */
//#include "drivers.h"
#include "os.h"
//#include "taskmgr.h"

/* final include module header */
#include "bts_comm.h"
#include "bts_comm_appl.h"
#include "bts_comm_callback.h"
#include "bts_comm_cfg.h"
#include "bts_comm_odt.h"
//#include "bts_comm_odt_info.h"
#include "bts_comm_status.h"
//#include "modulation.h"
//#include "vcomm_task.h"

/* declare static variables */


/* static function prototypes */


// bts_comm send/receive packet queue
uint8_t bts_comm_tx_buffer[bts_COMM_TX_MSGQUEUE_SIZE][bts_COMM_TX_BUFFER_SIZE] KRS_ALIGN(32);
uint32_t bts_comm_tx_buffer_index = 0;
uint32_t bts_comm_tx_pingpongindex = 0;
os_sem_t sem_bts_comm_addmsg;

//os_queue_t bts_comm_tx_queue_handle;
LINKED_QUEUE bts_comm_tx_queue_handle;



// timestamp
os_time_t bts_comm_time_baseus = 0;
os_time_t bts_comm_time_currentus = 0;
os_time_t bts_comm_timeout_protocol = 0;

uint8_t bts_comm_send_request=0;

//#define XCP_ODTLIST_UNITTEST


bts_comm_ret_t bts_comm_command_dispatch(bts_comm_packet_t *packetptr);
uint32_t bts_comm_getdata_by_odtlist(uint8_t *dest, krslist_t *odtlistptr);
int32_t bts_comm_cmd_make_positive_response(uint8_t *resbuff, uint8_t *databuff, uint16_t size);


os_sem_t sem_bts_comm_disconnect_request;


/* functions */

/******************************************************************************
 * function name : bts_comm_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return bts_comm_ret_t description
 * modification date : 2017.10.11
 *****************************************************************************/
bts_comm_ret_t bts_comm_init(void)
{
    // timestamp init
    //bts_comm_time_base = timer_drv_gettime_us();
	bts_comm_reset_timestamp(0);

    /* module init for odt list*/
    /* bts_comm packet buffer init */
    krs_memclear(bts_comm_tx_buffer);
    bts_comm_tx_buffer_index = 0;
    bts_comm_tx_pingpongindex = 0;
    os_sem_init(sem_bts_comm_addmsg);
    os_sem_give(sem_bts_comm_addmsg);

    bts_comm_send_request = 0;

    // create queue handle
    //os_queue_create(bts_comm_tx_queue_handle, bts_COMM_TX_MSGQUEUE_SIZE,
    //                sizeof(bts_comm_queue_t));
    InitQueue(&bts_comm_tx_queue_handle, bts_COMM_TX_MSGQUEUE_SIZE);

    // resource init
    bts_comm_status_init();


    /* odt init */ // odt no use
    //bts_comm_odt_init();

    os_timeout_reset(&bts_comm_timeout_protocol);
    os_sem_init(sem_bts_comm_disconnect_request);


    return retOK;
}


/******************************************************************************
 * function name : bts_comm_reset
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return bts_comm_ret_t description
 * modification date : 2017.10.11
 *****************************************************************************/
bts_comm_ret_t bts_comm_reset(void)
{
    //krs_log("bts_comm reset: rx/rx queue reset, tx/rx buffer index rest\n\r");
    // 1. reset tx rx queue and it's state
    //os_queue_reset(bts_comm_tx_queue_handle);
    ResetQueue(&bts_comm_tx_queue_handle);
    bts_comm_tx_buffer_index = 0;
    bts_comm_tx_pingpongindex = 0;

    // 2. reset bts_comm status all
    bts_comm_status_init();
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_command
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return bts_comm_ret_t description
 * modification date : 2017.10.11
 *****************************************************************************/
bts_comm_ret_t bts_comm_command(uint8_t *cmdbuff, int32_t size)
{
    bts_comm_packet_t rxpacketinfo;


    // 1. Check integrity of received data.

#if bts_COMM_RX_DEBUG == 1
	krs_log("************************************\n\r");
	krs_log("*** bts_comm_command: Rx packet ****\n\r");
	krs_log("************************************\n\r");
	krs_log("bts_comm_command : \n\r");
	krs_log("length : %d\n\r", size);
	krs_log("data : ");
	for(int i=0;i<size;i++)
	{
		printf("%02X",cmdbuff[i]);
	}
	printf("(");
	for(int i=0;i<size;i++)
	{
		printf("%c",cmdbuff[i]);
	}
	printf(")\n\r");
#endif

	bts_commpacket_parse_cro_packet(&rxpacketinfo, cmdbuff);

	// 2. Determine whether the received packet is CTO or DTO.
	if(rxpacketinfo.cro.header.u8pid >= 0xC0)
	{
		// CTO processing
		// 4. If it is CTO packet, execute bts_comm_command_dispatch command processing.
		bts_comm_command_dispatch(&rxpacketinfo);
		//bts_comm_send();
		os_timeout_reset(&bts_comm_timeout_protocol);
	}
	else
	{
		// STIM processing
		// 3. If the received packet is a DTO, write it to the STIM queue.
	}

	// timeout update


	// timeout check
	if(!Ir24xCommGetIsStartStopSynchModeStart())
	{
		if(os_timeout_expired(&bts_comm_timeout_protocol, bts_COMM_APPL_PROTOCOL_TIMEOUT*1000) == retOK)
			return retFail;
	}
	else
	{
		os_timeout_reset(&bts_comm_timeout_protocol);
	}

    return retOK;
}




/******************************************************************************
 * function name : bts_comm_get_timestamp
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return uint32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
void bts_comm_set_timestamp(os_time_t currentus)
{
	bts_comm_time_currentus = currentus;
}




/******************************************************************************
 * function name : bts_comm_get_timestamp
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return uint32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
os_time_t bts_comm_get_timestamp(void)
{
    return (bts_comm_time_currentus-bts_comm_time_baseus);
}


/******************************************************************************
 * function name : bts_comm_reset_timestamp
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return uint32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
void bts_comm_reset_timestamp(os_time_t basetimeus)
{
	bts_comm_time_baseus = basetimeus;
}


/******************************************************************************
 * function name : bts_comm_addmsg
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *msg description
 * \param1 length description
 * \param2 packettype description
 * \param3 pid description
 * \param4 index description
 * \return uint32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
uint32_t bts_comm_addmsg(void *msg, uint32_t length, bts_comm_packet_type_t packettype,
                           uint8_t pid, uint16_t index, uint32_t *peekaddr)
{
    uint32_t packetsize;
    uint32_t timestamp_100us;

#if bts_COMM_TX_DEBUG == 1
    krs_log("bts_comm_tx_buffer_index:%d\n\r", bts_comm_tx_buffer_index);
#endif

    struct timespec temp_timespec;  \
    temp_timespec.tv_sec = 0;   \
    temp_timespec.tv_nsec = (os_max_delay)*1000000;  \

    os_sem_take(sem_bts_comm_addmsg, temp_timespec);


    if(packettype == bts_comm_packet_type_dto)
    {
    	timestamp_100us = (uint32_t)(bts_comm_get_timestamp()/100UL);
        //krs_log("bts_comm_tx_pingpongindex: %d\n", bts_comm_tx_pingpongindex);
        //krs_log("bts_comm_tx_buffer_index: %d\n", bts_comm_tx_buffer_index);
        //krs_log("pid: %d\n", pid);
        //krs_log("index: %d\n", index);
        //krs_log("length: %d\n", length);
        packetsize = (uint32_t)bts_commpacket_make_dto_packet(
            &bts_comm_tx_buffer[bts_comm_tx_pingpongindex][bts_comm_tx_buffer_index], pid, 0,
            index, timestamp_100us, (uint8_t *)msg, length);
    }
    else
    {
        packetsize = (uint32_t)bts_commpacket_make_cro_packet(
            &bts_comm_tx_buffer[bts_comm_tx_pingpongindex][bts_comm_tx_buffer_index], pid,
            (uint8_t *)msg, length);
    }

    if(peekaddr != NULL)
    {
    	*peekaddr = (uint32_t)(&bts_comm_tx_buffer[bts_comm_tx_pingpongindex][bts_comm_tx_buffer_index]);
    }
    bts_comm_tx_buffer_index += packetsize;

    os_sem_give(sem_bts_comm_addmsg);

    return packetsize;
}


/******************************************************************************
 * function name : bts_comm_addpacket
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetbuff description
 * \param1 packetsize description
 * \param2 *peekaddr description
 * \return uint32_t description
 * modification date : 2019.08.22
 *****************************************************************************/
uint32_t bts_comm_addpacket(void *packetbuff, uint32_t packetsize, uint32_t *peekaddr)
{
	if(packetsize > 0)
	{
		krs_memcopy(&bts_comm_tx_buffer[bts_comm_tx_pingpongindex][bts_comm_tx_buffer_index], packetbuff, packetsize);

		if(peekaddr != NULL)
		{
			*peekaddr = (uint32_t)(&bts_comm_tx_buffer[bts_comm_tx_pingpongindex][bts_comm_tx_buffer_index]);
		}
		bts_comm_tx_buffer_index += packetsize;
	}
    return packetsize;
}

/******************************************************************************
 * function name : bts_comm_send
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return uint32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
uint32_t bts_comm_send(void)
{
    //bts_comm_queue_t txque;
    queue_item_t txque;
//krs_log("PutQueue..!!\n");
    //os_safe(txque.bufferptr = (void *)&bts_comm_tx_buffer[bts_comm_tx_pingpongindex][0];
    //        txque.size = bts_comm_tx_buffer_index;
    //        bts_comm_tx_pingpongindex =
    //            (bts_comm_tx_pingpongindex + 1) % bts_COMM_TX_MSGQUEUE_SIZE;
    //        bts_comm_tx_buffer_index = 0;);
    os_safe(txque.buffptr = (void *)&bts_comm_tx_buffer[bts_comm_tx_pingpongindex][0];
            txque.size = bts_comm_tx_buffer_index;
            bts_comm_tx_pingpongindex =
                (bts_comm_tx_pingpongindex + 1) % bts_COMM_TX_MSGQUEUE_SIZE;
            bts_comm_tx_buffer_index = 0;);

    //if(os_queue_give(bts_comm_tx_queue_handle, &txque, bts_COMM_APPL_PROTOCOL_TIMEOUT))
    if(PutQueue(&bts_comm_tx_queue_handle, &txque) == os_retOK)
    {
#if bts_COMM_TX_DEBUG == 1
        krs_log(">%ld\n", txque.size);
#endif
        return txque.size;
    }
    else
    {
        krs_log_error("bts_comm_send Tx Queue fail\n\r");
        bts_comm_reset();
        return 0;
    }
}


uint32_t bts_comm_get_current_tx_buffer_index(void)
{
	uint32_t size;

	os_safe_assign(size, bts_comm_tx_buffer_index);
	return size;
}


int32_t bts_comm_to_add_possible(uint32_t sizetosend)
{
	if((bts_comm_get_current_tx_buffer_index() + sizetosend) < bts_COMM_TX_BUFFER_SIZE)
	{
		return retOK;
	}
	else
	{
		return retFail;
	}
}



uint32_t bts_comm_get_packet_count_from_txqueue(void)
{
	//return os_queue_len(bts_comm_tx_queue_handle);
    return GetQueueSize(&bts_comm_tx_queue_handle);
}

/******************************************************************************
 * function name : bts_comm_get_packets_from_txqueue
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *pp description
 * \param1 waitms description
 * \return uint32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
//uint32_t bts_comm_get_packets_from_txqueue(bts_comm_queue_t *pp, TickType_t waitms)
uint32_t bts_comm_get_packets_from_txqueue(queue_item_t *pp, TickType_t waitms)
{
    //if(os_queue_take(bts_comm_tx_queue_handle, pp, (TickType_t)waitms)==os_retOK)
    if(GetQueue(&bts_comm_tx_queue_handle, pp) == os_retOK)
    {
        return retOK;
    }
    return retFail;
}


/******************************************************************************
 * function name : bts_comm_flush_txqueue
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
void bts_comm_flush_txqueue(void)
{
    //os_queue_reset(bts_comm_tx_queue_handle);
    ResetQueue(&bts_comm_tx_queue_handle);
    bts_comm_tx_buffer_index = 0;
    bts_comm_tx_pingpongindex = 0;
}





/******************************************************************************
 * function name : bts_comm_event
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 event description
 * \return bts_comm_ret_t description
 * modification date : 2017.10.11
 *****************************************************************************/
bts_comm_ret_t bts_comm_event_build(bts_comm_event_type_t event, void *pvParameters)
{
    static uint8_t sync_flag = 0;
    struct timespec temp_timespec;  \
    temp_timespec.tv_sec = 0;   \
    temp_timespec.tv_nsec = 0;  \


    //	if(event<bts_comm_event_max)
    //	{
    //		//bts_commeventinfo.odt_event_table[event];
    //	}
    //	else
    //	{
    //
    //	}
    // 1. Make sure that DAQ is enabled in XcpSession. Or return.

    // 2. Check whether event is within bts_comm_event_max, or return.

    // 3. Get the odtlist number registered in the event. You can register by pid of all odtlist.

    // 4. Verify that the corresponding odtlist is a list with daq enabled. Or skip it.

    // 5. Processing related to Timing

    // 6. STIM processing, if STIM is enabled and Stim packet is in queue, take it out and process
    // it. all.

    // 7. DAQ processing If DAQ is enabled, take out DAQ packet if it is in queue. all.

    // 8. Processing the Timestamp

    // 9. Send DTO or SendDtoFromQueue
    // schd_task_scan_endchek();
    if(Ir24xCommGetIsStartStopSynchModeStopAll())
    {
        sync_flag = 0;
        Ir24xCommSetDaqStatusIdle();
    }

    bts_comm_appl_packetbuild(pvParameters);

    if(Ir24xCommGetIsStartStopSynchModeStart())
    {
        if(os_sem_take(sem_bts_comm_status_daq_start, temp_timespec) == os_retOK)
        {
            krs_log("AFI910 COMM DAQ mode established\n\r");
            sync_flag = 1;
            bts_comm_reset_timestamp((os_time_t)os_time_us());
        }

        if(sync_flag == 1)
        {
        	bts_comm_appl_send(pvParameters);
        	bts_comm_send_request = 1;
        }
    }
    return retOK;
}



/******************************************************************************
 * function name : bts_comm_event_send
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
 * modification date : 2019.09.03
 *****************************************************************************/
int32_t bts_comm_event_send(void)
{
	if(bts_comm_send_request == 1)
	{
		bts_comm_send_request = 0;
		bts_comm_send();
	}

	//vcomm_rs485_appdata_send();
	return retOK;
}


/******************************************************************************
 * function name : bts_comm_command_dispatch
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packetptr description
 * \return bts_comm_ret_t description
 * modification date : 2017.10.11
 *****************************************************************************/
bts_comm_ret_t bts_comm_command_dispatch(bts_comm_packet_t *packetptr)
{
    int32_t i;
    bts_comm_ret_t ret;

    // bts_commpacket_parse_cto_packet(packetptr->u8buffer, &pid, databuff);
    for(i = 0; bts_comm_cmd_table[i].pid != 0; i++)
    {
        if(packetptr->cro.header.u8pid == bts_comm_cmd_table[i].pid)
        {
            if(bts_comm_cmd_table[i].callback)
            {
                ret = bts_comm_cmd_table[i].callback(packetptr);
                return ret;
            }
        }
    }
    bts_comm_send_error(IR24XCOMMRESP_ERR_CMD_UNKNOWN);
    return retFail;
}


/******************************************************************************
 * function name : bts_comm_send_event
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 evcode description
 * \return bts_comm_ret_t description
 * modification date : 2017.10.11
 *****************************************************************************/
bts_comm_ret_t bts_comm_send_event(bts_comm_resp_t evcode)
{
    uint8_t txbuff[2];

    txbuff[0] = evcode;
    bts_comm_add_cro_msg(1, IR24XCOMMRESP_EV, txbuff);
    bts_comm_send();
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_send_error
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 errorcode description
 * \return bts_comm_ret_t description
 * modification date : 2017.10.11
 *****************************************************************************/
bts_comm_ret_t bts_comm_send_error(bts_comm_resp_t errorcode)
{
    uint8_t txbuff[2];

    txbuff[0] = errorcode;
    bts_comm_add_cro_msg(1, IR24XCOMMRESP_ERR, txbuff);
    bts_comm_send();
    return retOK;
}




bts_comm_ret_t bts_comm_send_errormsg(char *errmsg)
{
    bts_comm_add_cro_msg(1, IR24XCOMMRESP_ERR, errmsg);
    bts_comm_send();
    return retOK;
}

bts_comm_ret_t bts_comm_send_error_async(eth_socket_t sock, bts_comm_resp_t errorcode)
{
    uint32_t trasmitted_size;
    uint8_t txerr[16];

    uint8_t errcode = IR24XCOMMRESP_ERR_CMD_SYNTAX;
    trasmitted_size = (uint32_t)bts_commpacket_make_cro_packet(
    txerr, IR24XCOMMRESP_ERR, (uint8_t *)&errcode, 1);

    eth_send(sock, txerr, trasmitted_size, 0);
    return retOK;
}

bts_comm_ret_t bts_comm_send_errormsg_async(eth_socket_t sock, char *errmsg, uint32_t len_msg)
{
    uint32_t trasmitted_size;
    uint8_t txerr[64];
    trasmitted_size = (uint32_t)bts_commpacket_make_cro_packet(
    txerr, IR24XCOMMRESP_ERR, (uint8_t *)errmsg, len_msg);

    eth_send(sock, txerr, trasmitted_size, 0);
    return retOK;
}


/* end of file */
