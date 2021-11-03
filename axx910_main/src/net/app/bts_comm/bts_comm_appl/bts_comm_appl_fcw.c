/************************************************************************
| Project Name: bts_comm_appl_fcw
|    File Name: bts_comm_appl_fcw.c
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
#include "can_sig.h"

/* final include module header */
#include "bts_comm.h"
#include "bts_comm_appl.h"
#include "bts_comm_cmd.h"
#include "bts_comm_packet.h"
#include "bts_comm_status.h"


#include "bts_comm_appl_fcw.h"

//#include "can_sig.h"
//#include "flog_task.h"
/* declare global variables */
#if (SYS_APP_TYPE == SYS_APP_TYPE_FCW) || (SYS_APP_TYPE == SYS_APP_TYPE_FI)
comm_appl_fcwinfo_t comm_appl_fcwinfo;
extern sys_param_sidxdidx_configinfo_packing_t sys_param_sidxdidx_configinfo_packing;
uint8_t pid_app_fcw_packetbuff[16 + sizeof(comm_appl_fcwinfo_t)];
uint32_t pid_app_fcw_packetsize = 0;
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
void bts_comm_appl_fcw_init(void)
{
#if (SYS_APP_TYPE == SYS_APP_TYPE_FCW) || (SYS_APP_TYPE == SYS_APP_TYPE_FI)
    krs_memclearitem(comm_appl_fcwinfo);
    krs_memclear(pid_app_fcw_packetbuff);
    pid_app_fcw_packetsize = 0;
#endif
}


/******************************************************************************
 * function name : bts_comm_appl_pid_app_fcw_packetbuild
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
void bts_comm_appl_pid_app_fcw_packetbuild(void)
{
#if (SYS_APP_TYPE == SYS_APP_TYPE_FCW) || (SYS_APP_TYPE == SYS_APP_TYPE_FI)
	static int32_t apppkt_skipcnt = 0;
	int32_t i;

	comm_appl_fcwinfo.vehicle_speed = (can_sig_data.wheel_speed_fl + can_sig_data.wheel_speed_fr + can_sig_data.wheel_speed_rl + can_sig_data.wheel_speed_rr)/4.0f ;
    //comm_appl_fcwinfo.vehicle_speed = can_sig_data.vehicle_speed;
    comm_appl_fcwinfo.wheel_speed_fl = can_sig_data.wheel_speed_fl;
    comm_appl_fcwinfo.wheel_speed_fr = can_sig_data.wheel_speed_fr;
    comm_appl_fcwinfo.wheel_speed_rl = can_sig_data.wheel_speed_rl;
    comm_appl_fcwinfo.wheel_speed_rr = can_sig_data.wheel_speed_rr;
    comm_appl_fcwinfo.steerangle = can_sig_data.steerangle;
    comm_appl_fcwinfo.steeranglespeed = can_sig_data.steeranglespeed;
    comm_appl_fcwinfo.yawrate = can_sig_data.yawrate;
    comm_appl_fcwinfo.longaccel = can_sig_data.longaccel;
    comm_appl_fcwinfo.lataccel = can_sig_data.lataccel;
    comm_appl_fcwinfo.eventflag = 0;

    pid_app_fcw_packetsize = (uint32_t)bts_commpacket_make_dto_packet(pid_app_fcw_packetbuff,
                                                                        bts_comm_pid_app_fcw,
                                                                        0,
                                                                        0,
                                                                        (uint32_t)(bts_comm_get_timestamp() / 100UL),
                                                                        (uint8_t *)&comm_appl_fcwinfo,
                                                                        sizeof(comm_appl_fcwinfo));


    for(i=0;i<SYS_PARAM_APP_PACKET_MAX;i++)
    {
    	if(SYS_PARAM_SENSORTYPE.pid_app_fcw_en == 1 &&SYS_PARAM_APPPKT_PORTS[i].port_en > 0 && SYS_PARAM_APPPKT_PORTS[i].pid_app_fcw_en == 1 && (apppkt_skipcnt % SYS_PARAM_APPPKT_PORTS[i].port_en == 0))
    	{
    		bts_comm_appdata_push(&bts_comm_apppacket_info[i], (uint8_t *)pid_app_fcw_packetbuff, pid_app_fcw_packetsize);
    	}
    }
    apppkt_skipcnt++;
#if bts_COMM_APPL_PACKETSIZE_DEBUG == 1
    krs_log("pid_app_fcw packetsize : %d\n\r", pid_app_fcw_packetsize);
#endif
#endif
}



/******************************************************************************
 * function name : bts_comm_appl_pid_app_fcw_packetsend
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
void bts_comm_appl_pid_app_fcw_packetsend(void)
{
#if (SYS_APP_TYPE == SYS_APP_TYPE_FCW) || (SYS_APP_TYPE == SYS_APP_TYPE_FI)
	if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[bts_comm_pid_app_fcw])==retOK)
	{
		if(bts_comm_daqinfo_is_start(bts_comm_pid_app_fcw) == retOK)
		{
			bts_comm_addpacket(pid_app_fcw_packetbuff, pid_app_fcw_packetsize, NULL);
		}
	}
#endif
}



/******************************************************************************
 * function name : bts_comm_appl_raw_app_fcw_precallback
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *pvparam description
 * \param1 size description
 * \return void description
 * modification date : 2019.08.22
 *****************************************************************************/
void bts_comm_appl_raw_app_fcw_precallback(void *pvparam, size_t size)
{
#if (SYS_APP_TYPE == SYS_APP_TYPE_FCW) || (SYS_APP_TYPE == SYS_APP_TYPE_FI)
    comm_appl_fcwinfo_t *p = (comm_appl_fcwinfo_t *)pvparam;
	p->vehicle_speed = (can_sig_data.wheel_speed_fl + can_sig_data.wheel_speed_fr + can_sig_data.wheel_speed_rl + can_sig_data.wheel_speed_rr)/4.0f ;
    //comm_appl_fcwinfo.vehicle_speed = can_sig_data.vehicle_speed;
    p->wheel_speed_fl = can_sig_data.wheel_speed_fl;
    p->wheel_speed_fr = can_sig_data.wheel_speed_fr;
    p->wheel_speed_rl = can_sig_data.wheel_speed_rl;
    p->wheel_speed_rr = can_sig_data.wheel_speed_rr;
    p->steerangle = can_sig_data.steerangle;
    p->steeranglespeed = can_sig_data.steeranglespeed;
    p->yawrate = can_sig_data.yawrate;
    p->longaccel = can_sig_data.longaccel;
    p->lataccel = can_sig_data.lataccel;
    p->eventflag = 0;//rsp_appl_fcw_eventflag;
#endif
}


/* end of file */
