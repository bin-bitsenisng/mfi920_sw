/************************************************************************
| Project Name: bts_comm_appl_its
|    File Name: bts_comm_appl_its.c
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
| 2018.06.26   0.0   SKJ   Creation;
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

#include "App_Main.h"

#include "bts_comm_appl_its.h"
/* declare global variables */
uint8_t pid_app_its_packetbuff[16 + bts_COMM_APPL_DATASET_JSON_BUFFER_SIZE];
uint32_t pid_app_its_packetsize = 0;

bts_comm_appl_raw_app_its_t raw_app_its;
bts_comm_appl_raw_app_its_installinfo_t raw_app_installinfo;

extern sys_param_sidxdidx_configinfo_packing_t sys_param_sidxdidx_configinfo_packing;

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
void bts_comm_appl_its_init(void)
{
    krs_memclear(pid_app_its_packetbuff);
    pid_app_its_packetsize = 0;
    krs_memclearitem(raw_app_its);
    krs_memclearitem(raw_app_installinfo);
}


/******************************************************************************
 * function name : bts_comm_appl_pid_app_its_packetbuild
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
 * modification date : 2019.08.22
 *****************************************************************************/
void bts_comm_appl_pid_app_its_packetbuild(void)
{
#if SYS_APP_TYPE == SYS_APP_TYPE_ITS
	static int32_t apppkt_skipcnt = 0;
	int32_t i;
    int32_t len = 0;

    len = sys_param_pid8_its_data_t_dump("", bts_comm_appl_dataset_json_buffer, &sys_param_pid8_its_data);

    if(len > 0)
    {
#if bts_COMM_APPL_JSON_DEBUG == 1
        krs_log("STATUS : \n\r%s\n\r", bts_comm_appl_dataset_json_buffer);
#endif
        pid_app_its_packetsize = (uint32_t)bts_commpacket_make_dto_packet(pid_app_its_packetbuff,
        																	bts_comm_pid_app_its,
                                                                            0,
                                                                            0,
                                                                            (uint32_t)(bts_comm_get_timestamp() / 100UL),
                                                                            (uint8_t *)&bts_comm_appl_dataset_json_buffer,
                                                                            len);
        //bts_comm_appdata_push((uint8_t *)pid_app_its_packetbuff, pid_app_its_packetsize);
        for(i=0;i<SYS_PARAM_APP_PACKET_MAX;i++)
        {
        	if(SYS_PARAM_SENSORTYPE.pid_app_its_en == 1 && SYS_PARAM_APPPKT_PORTS[i].port_en > 0 && SYS_PARAM_APPPKT_PORTS[i].pid_app_its_en == 1 && (apppkt_skipcnt % SYS_PARAM_APPPKT_PORTS[i].port_en == 0))
        	{
        		bts_comm_appdata_push(&bts_comm_apppacket_info[i], (uint8_t *)pid_app_its_packetbuff, pid_app_its_packetsize);
        	}
        }
        apppkt_skipcnt++;
#if bts_COMM_APPL_PACKETSIZE_DEBUG == 1
        krs_log("pid_app_its packetsize : %d\n\r", pid_app_its_packetsize);
#endif
    }
#endif
}


/******************************************************************************
 * function name : bts_comm_appl_pid_app_its_packetsend
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
void bts_comm_appl_pid_app_its_packetsend(void)
{
#if SYS_APP_TYPE == SYS_APP_TYPE_ITS
	if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[bts_comm_pid_app_its])==retOK)
	{
		if(bts_comm_daqinfo_is_start(bts_comm_pid_app_its) == retOK)
		{
			bts_comm_addpacket(pid_app_its_packetbuff, pid_app_its_packetsize, NULL);
		}
	}
#endif
}


/******************************************************************************
 * function name : bts_comm_appl_raw_app_its_precallback
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
void bts_comm_appl_raw_app_its_precallback(void *pvparam, size_t size)
{
    bts_comm_appl_raw_app_its_t *p = (bts_comm_appl_raw_app_its_t *)pvparam;
/*	p->autoalignment_on = TrafficAlignment.info_alignment.autoalignment_on;
	p->s16StackCnt = TrafficAlignment.info_alignment.s16StackCnt;
	p->u32num_track_autoalignment = TrafficAlignment.info_alignment.u32num_track_autoalignment;
	p->status_autoalignment = TrafficAlignment.info_alignment.status_autoalignment;
	p->prv_autoalignment_on = TrafficAlignment.info_alignment.prv_autoalignment_on;
	p->f32AlignedAngle = TrafficAlignment.info_alignment.f32AlignedAngle;*/
}

/******************************************************************************
 * function name : bts_comm_appl_raw_app_its_install_precallback
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
void bts_comm_appl_raw_app_its_install_precallback(void *pvparam, size_t size)
{
    bts_comm_appl_raw_app_its_installinfo_t *p = (bts_comm_appl_raw_app_its_installinfo_t *)pvparam;
   /* p->angle_azi = RadarInstInfo.f32AziAng;
    p->angle_ele = RadarInstInfo.f32EleAng;
    p->height_m = RadarInstInfo.f32Height;*/
}


/* end of file */
