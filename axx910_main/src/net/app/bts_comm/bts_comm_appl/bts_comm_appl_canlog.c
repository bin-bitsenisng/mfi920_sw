/************************************************************************
| Project Name: bts_comm_appl_canlog
|    File Name: bts_comm_appl_canlog.c
|  Description: file detailed description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------
| SKJ          SONG KYEONG JIN           Bitsensing
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description
| ----------  ----  ------  --------------------------------------------
| 2019.04.13   0.0   SKJ   Creation;
|***********************************************************************/

/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"
#include <string.h>

/* include system driver header */
//#include "drivers.h"
#include "krs_lib.h"

/* include system bsp header */
#include "os.h"

/* include system application header */
#include "sys_param.h"

/* final include module header */
#include "bts_comm.h"
#include "bts_comm_appl.h"
#include "bts_comm_cmd.h"
#include "bts_comm_packet.h"
#include "bts_comm_status.h"


#include "bts_comm_appl_canlog.h"

#include "bts_comm_cfg.h"
//#include "can_drv.h"
//#include "can_sig.h"
//#include "vcomm_task.h"


/* declare global variables */
#if SYS_CAN_ENABLE == 1
pid_canlogpacket_t canlogpacket;

uint8_t pid_canlog_packetbuff[16 + 4 + sizeof(can_drv_msg_t)*4096];
uint32_t pid_canlog_packetsize = 0;
#endif
/* declare static variables */
// temp gps data

/* static function prototypes */

/* functions */

// object


/******************************************************************************
 * function name : bts_comm_appl_its_init
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
 * modification date : 2018.06.26
 *****************************************************************************/
void bts_comm_appl_canlog_init(void)
{
#if SYS_CAN_ENABLE == 1
    krs_memclearitem(canlogpacket);
    krs_memclear(pid_canlog_packetbuff);
    pid_canlog_packetsize = 0;
#endif
}


/******************************************************************************
 * function name : bts_comm_appl_pid_canlog_packetbuild
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
 * modification date : 2019.04.13
 *****************************************************************************/
void bts_comm_appl_pid_canlog_packetbuild(void)
{
#if SYS_CAN_ENABLE == 1
	static int32_t apppkt_skipcnt = 0;
    int32_t i;
    uint32_t msgsize=0;
    int32_t ret;



    //canlogpacket.msgcount = os_queue_len(que_vcomm_canrawdata);
    canlogpacket.msgcount = GetQueueSize(&que_vcomm_canrawdata);
    canlogpacket.timestamp_s = ((f64_t)rsp_timestamp_us) / 1000000.0f;
    for(i=0;i<canlogpacket.msgcount;i++)
    {
        //ret = os_queue_take(que_vcomm_canrawdata, &canlogpacket.msgs[i], 0);
        ret = GetQueue(&que_vcomm_canrawdata, &canlogpacket.msgs[i]);
        if(ret != os_retOK)
        {
            canlogpacket.msgcount = i;
            break;
        }
    }

    if(canlogpacket.msgcount == 0)
    {
    	pid_canlog_packetsize = 0;
    	return;
    }

    canlogpacket.msgsize = 16 + sizeof(can_drv_msg_t)*canlogpacket.msgcount;


    pid_canlog_packetsize = (uint32_t)bts_commpacket_make_dto_packet(pid_canlog_packetbuff,
                                                                        bts_comm_pid_canlog,
                                                                        0,
                                                                        0,
                                                                        (uint32_t)(bts_comm_get_timestamp() / 100UL),
                                                                        (uint8_t *)&canlogpacket,
																		canlogpacket.msgsize);


    for(i=0;i<SYS_PARAM_APP_PACKET_MAX;i++)
    {
    	if(SYS_PARAM_SENSORTYPE.pid_canlog_en == 1 &&SYS_PARAM_APPPKT_PORTS[i].port_en > 0 && SYS_PARAM_APPPKT_PORTS[i].pid_canlog_en == 1&& (apppkt_skipcnt % SYS_PARAM_APPPKT_PORTS[i].port_en == 0))
    	{
    		bts_comm_appdata_push(&bts_comm_apppacket_info[i], (uint8_t *)pid_canlog_packetbuff, pid_canlog_packetsize);
    	}
    }
    apppkt_skipcnt++;
#if bts_COMM_APPL_PACKETSIZE_DEBUG == 1
    krs_log("pid_canlog packetsize : %d\n\r", pid_canlog_packetsize);
#endif
#endif
}



/******************************************************************************
 * function name : bts_comm_appl_pid_canlog_packetsend
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
 * modification date : 2018.06.26
 *****************************************************************************/
void bts_comm_appl_pid_canlog_packetsend(void)
{
#if SYS_CAN_ENABLE == 1
	if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[bts_comm_pid_canlog])==retOK)
	{
		if(bts_comm_daqinfo_is_start(bts_comm_pid_canlog) == retOK)
		{
			bts_comm_addpacket(pid_canlog_packetbuff, pid_canlog_packetsize, NULL);
		}
	}
#endif
}



/* end of file */
