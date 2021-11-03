/************************************************************************
| Project Name: bts_comm
|    File Name: bts_comm.h
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
#ifndef bts_COMM_H__
#define bts_COMM_H__
#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"

#include "bts_comm_cfg.h"
#include "bts_comm_cmd.h"
#include "bts_comm_odt.h"
#include "bts_comm_packet.h"
#include "bts_comm_status.h"

#include "if/eth/eth.h"

#include "os.h"
#include "bts_queue.h"
/* module specific types  */
typedef int32_t bts_comm_ret_t;


typedef struct
{
    uint8_t *bufferptr;
    uint32_t size;
} bts_comm_queue_t;


typedef struct
{
   uint8_t buffpool[1024][1024];
   bts_queue_t bq;
}bts_comm_data_queue_t;


/* define structure for this module */

#define bts_comm_get_datatype_size(x) (bts_comm_odt_datatype_size[(x)])
#define bts_comm_get_datatype_name(x) (bts_comm_odt_datatype_nametable[(x)])


/* declare extern global variables */
extern bts_comm_data_queue_t bts_comm_commandque KRS_ALIGN(1024*1024);
//extern os_queue_t bts_comm_tx_queue_handle;
extern LINKED_QUEUE bts_comm_tx_queue_handle;
//extern std::queue<bts_comm_queue_t> bts_comm_tx_queue_handle;
//extern QueueHandle_t bts_comm_rx_queue_handle;
extern os_sem_t sem_bts_comm_disconnect_request;
extern os_time_t bts_comm_timeout_protocol;
extern uint8_t bts_comm_send_request;

/* declare extern global functions */
extern bts_comm_ret_t bts_comm_init(void);
extern bts_comm_ret_t bts_comm_command(uint8_t *cmdbuff, int32_t size);
extern bts_comm_ret_t bts_comm_reset(void);
extern bts_comm_ret_t bts_comm_printf(const char *msg, ...);
extern bts_comm_ret_t bts_comm_event_build(bts_comm_event_type_t event, void *pvParameters);
extern int32_t bts_comm_event_send(void);
extern uint32_t bts_comm_addmsg(void *msg, uint32_t length, bts_comm_packet_type_t packettype,
        uint8_t pid, uint16_t index, uint32_t *peekaddr);
extern uint32_t bts_comm_addpacket(void *packetbuff, uint32_t packetsize, uint32_t *peekaddr);
extern uint32_t bts_comm_send(void);
extern uint32_t bts_comm_get_current_tx_buffer_index(void);
extern int32_t bts_comm_to_add_possible(uint32_t sizetosend);

#define bts_comm_add_dto_msg(len, pid, index, msg) \
    bts_comm_addmsg((msg), (len), bts_comm_packet_type_dto, (pid), (index),(NULL))

#define bts_comm_add_dto_msg_peek(len, pid, index, msg, peekaddr) \
    bts_comm_addmsg((msg), (len), bts_comm_packet_type_dto, (pid), (index),(peekaddr))

#define bts_comm_add_dto_item(pid, item) bts_comm_add_dto_msg((sizeof(item)), (pid), (0), &(item))

#define bts_comm_add_cro_msg(len, pid, msg) \
    bts_comm_addmsg((msg), (len), bts_comm_packet_type_cro, (pid), (0), (NULL))
#define bts_comm_send_cro(len, pid, msg) bts_comm_add_cro_msg(len, pid, msg), bts_comm_send();


extern uint32_t bts_comm_get_packet_count_from_txqueue(void);
//extern uint32_t bts_comm_get_packets_from_txqueue(bts_comm_queue_t *pp, TickType_t waitms);
extern uint32_t bts_comm_get_packets_from_txqueue(queue_item_t *pp, TickType_t waitms);
extern void bts_comm_flush_txqueue(void);
extern bts_comm_ret_t bts_comm_put_packet_to_rxqueue(void *msg, uint16_t length);
extern uint32_t bts_comm_receive(bts_comm_queue_t *pp, TickType_t waitms);


extern bts_comm_ret_t bts_comm_send_event(bts_comm_resp_t evcode);
extern bts_comm_ret_t bts_comm_send_error(bts_comm_resp_t errorcode);
extern bts_comm_ret_t bts_comm_send_errormsg(char *errmsg);
extern bts_comm_ret_t bts_comm_send_error_async(eth_socket_t sock, bts_comm_resp_t errorcode);
extern bts_comm_ret_t bts_comm_send_errormsg_async(eth_socket_t sock, char *errmsg, uint32_t len_msg);

extern void bts_comm_set_timestamp(os_time_t currentus);
extern os_time_t bts_comm_get_timestamp(void);
extern void bts_comm_reset_timestamp(os_time_t basetimeus);

#ifdef __cplusplus
}
#endif
#endif /* bts_COMM_H__ */
