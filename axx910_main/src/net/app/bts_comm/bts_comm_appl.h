/************************************************************************
| Project Name: bts_comm_appl
|    File Name: bts_comm_appl.h
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
| 2017.09.11   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef bts_COMM_APPL_H__
#define bts_COMM_APPL_H__


#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"
#include "bts_queue.h"
#include "bts_comm_appl_dataset.h"
#include "bts_comm_appl_common.h"
#include "bts_comm_appl_status.h"
#include "bts_comm_appl_object.h"
#include "bts_comm_appl_track.h"
#include "bts_comm_appl_image.h"
#include "bts_comm_appl_canlog.h"
#include "bts_comm_appl_its.h"
#include "bts_comm_appl_vf.h"
#include "bts_comm_appl_fcw.h"
#include "bts_comm_appl_raw.h"
#include "bts_comm_appl_flog.h"
#include "bts_comm_appl_rs485.h"
#include "bts_comm_appl_ai_object.h"
#include "bts_comm_appl_lane_detection.h"
#include "bts_comm_appl_freespace.h"

/* module specific types  */
typedef int32_t bts_comm_appl_ret_t;


/* define structure for this module */
typedef struct
{
    int32_t moduleinfo;
    int32_t version;
} bts_comm_appl_info_t;

typedef struct
{
	uint8_t buffpool[1024][1024] KRS_ALIGN(32);
	int32_t id;
	bts_queue_t bq;
	uint32_t connected;
}bts_comm_apppacket_info_t;


/* declare extern global variables */
//extern os_task_t comm_appl_task_handle;
//extern os_task_t comm_appl_rx_task_handle;
//extern os_task_t comm_appl_tx_task_handle;
//extern os_task_t comm_apppacket_task_handle[SYS_PARAM_APPPKT_MAX];
extern pthread_t comm_appl_task_handle;
extern pthread_t comm_appl_rx_task_handle;
extern pthread_t comm_appl_tx_task_handle;
extern pthread_t comm_apppacket_task_handle[SYS_PARAM_APPPKT_MAX];

extern bts_comm_apppacket_info_t bts_comm_apppacket_info[SYS_PARAM_APPPKT_MAX];

/* declare extern global functions */
extern void bts_comm_appl_init(void);
extern void bts_comm_appl_task(void *pvParameters);
extern int32_t bts_comm_appl_send(void *pvParameters);
extern void bts_comm_appdata_push(bts_comm_apppacket_info_t *inst, uint8_t *srcbuff, size_t size);
extern int32_t bts_comm_appl_packetbuild(void *pvParameters);


#ifdef __cplusplus
}
#endif
#endif // bts_COMM_APPL_H__
