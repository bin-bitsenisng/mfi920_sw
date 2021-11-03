/************************************************************************
| Project Name: bts_comm_appl_object
|    File Name: bts_comm_appl_object.c
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


#include "bts_comm_appl_its.h"

#include "Sp_Main.h"
/* declare global variables */


bts_comm_appl_objectpacket_t bts_comm_appl_objectpacket;
uint8_t pid_object_packetbuff[16 + sizeof(bts_comm_appl_objectpacket_t)];
uint32_t pid_object_packetsize = 0;


/* declare static variables */


/* static function prototypes */

/* functions */

// object


/******************************************************************************
 * function name : bts_comm_appl_object_init
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
void bts_comm_appl_object_init(void)
{
    krs_memclearitem(bts_comm_appl_objectpacket);
    krs_memclear(pid_object_packetbuff);
    pid_object_packetsize = 0;
}


/******************************************************************************
 * function name : bts_comm_appl_pid_object_packetbuild
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
void bts_comm_appl_pid_object_packetbuild(void)
{
	static int32_t apppkt_skipcnt = 0;
    int32_t i = 0;
    int32_t objidx=0;
    uint32_t object_packetsize=0;
#if bts_COMM_APPL_PACKETSIZE_DEBUG == 1
    int32_t packetsize = 0;
#endif
    //imu_flip_status_t flipside = imu_flip_status_upside;

    krs_memclearitem(bts_comm_appl_objectpacket.objects);

	//flipside = imu_drv_get_flip_status();

	objidx = 0;
    for(i = 0; i < bts_COMM_APPL_OBJECT_MAX; i++)
    {
    	if(Sp_ObjectOut[i].f32Range_m > 0.01f)
    	{
			bts_comm_appl_objectpacket.objects[objidx].id = (uint16_t)i;
			bts_comm_appl_objectpacket.objects[objidx].modtype = Sp_ObjectOut[i].u8ModType;
			bts_comm_appl_objectpacket.objects[objidx].range = Sp_ObjectOut[i].f32Range_m;

			bts_comm_appl_objectpacket.objects[objidx].azi_angle = Sp_ObjectOut[i].f32AziAng_deg;
			bts_comm_appl_objectpacket.objects[objidx].ele_angle = Sp_ObjectOut[i].f32EleAng_deg;
			/*
			if(flipside == imu_flip_status_upside)
			{
				bts_comm_appl_objectpacket.objects[objidx].angle = Sp_ObjectOut[i].f32AziAng_deg;
			}
			else
			{
				bts_comm_appl_objectpacket.objects[objidx].angle = -Sp_ObjectOut[i].f32AziAng_deg;
			}*/
			bts_comm_appl_objectpacket.objects[objidx].vel = Sp_ObjectOut[i].f32Velocity_mps;
			bts_comm_appl_objectpacket.objects[objidx].power = (uint8_t)Sp_ObjectOut[i].f32Power_dB;
			objidx++;
    	}
    }
    bts_comm_appl_objectpacket.count = bts_COMM_APPL_OBJECT_MAX;
    bts_comm_appl_objectpacket.active_count = objidx;
    object_packetsize = 4 + sizeof(bts_comm_appl_object_t)*objidx;


    pid_object_packetsize = (uint32_t)bts_commpacket_make_dto_packet(pid_object_packetbuff,
                                                                       bts_comm_pid_object,
                                                                       0,
                                                                       0,
                                                                       (uint32_t)(bts_comm_get_timestamp() / 100UL),
                                                                       (uint8_t *)&bts_comm_appl_objectpacket,
																	   object_packetsize);

    for(i=0;i<SYS_PARAM_APP_PACKET_MAX;i++)
    {
    	if(SYS_PARAM_SENSORTYPE.pid_object_en == 1 && SYS_PARAM_APPPKT_PORTS[i].port_en > 0 && SYS_PARAM_APPPKT_PORTS[i].pid_object_en ==1 && (apppkt_skipcnt % SYS_PARAM_APPPKT_PORTS[i].port_en == 0))
    	{
    		bts_comm_appdata_push(&bts_comm_apppacket_info[i], (uint8_t *)pid_object_packetbuff, pid_object_packetsize);
    	}
    }
    apppkt_skipcnt++;

#if bts_COMM_APPL_PACKETSIZE_DEBUG == 1
    krs_log("pid_object packetsize : %d\n\r", pid_object_packetsize);
#endif
}


/******************************************************************************
 * function name : bts_comm_appl_pid_object_packetsend
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
void bts_comm_appl_pid_object_packetsend(void)
{
	if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[bts_comm_pid_object])==retOK)
	{
		if(bts_comm_daqinfo_is_start(bts_comm_pid_object) == retOK)
		{
			bts_comm_addpacket(pid_object_packetbuff, pid_object_packetsize, NULL);
		}
	}
}

/* end of file */
