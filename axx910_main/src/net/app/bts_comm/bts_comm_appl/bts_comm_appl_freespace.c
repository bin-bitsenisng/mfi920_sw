/***********************************************************************
| Project Name: 
|    File Name: bts_comm_appl_freespace.c
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
| 2021.06.04   0.0  mhkim   Creation;
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
#include "imu.h"

#include "Trk_Main.h"
/* declare global variables */
bts_comm_appl_freespace_packet_t bts_comm_appl_freespace_packet;
uint8_t pid_freespace_packetbuff[16 + sizeof(bts_comm_appl_freespace_packet_t)];
uint32_t pid_freespace_packetsize = 0;
/* declare static variables */
// temp gps data

/* static function prototypes */

/* functions */

// object


/******************************************************************************
 * function name : bts_comm_appl_freespace_init
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
 * modification date : 2021.06.04
 *****************************************************************************/
void bts_comm_appl_freespace_init(void)
{
    krs_memclear(pid_freespace_packetbuff);
    pid_freespace_packetsize = 0;
}


/******************************************************************************
 * function name : bts_comm_appl_pid_freespace_packetbuild
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
 * modification date : 2021.06.04
 *****************************************************************************/
void bts_comm_appl_pid_freespace_packetbuild(void)
{
	static int32_t apppkt_skipcnt = 0;
    int32_t i = 0;
    uint32_t timestamp_100us;
    krs_memclearitem(bts_comm_appl_freespace_packet.free_range);
    uint32_t freespace_packetsize=0;

    bts_comm_appl_freespace_packet.num_of_angle = bts_COMM_APPL_FREESPACE_NUM_OF_ANGLE;
    for(i = 0; i < bts_COMM_APPL_FREESPACE_NUM_OF_ANGLE; i++)
    {
        bts_comm_appl_freespace_packet.free_range[i] = gFreespaceOut.fFreeRange[i];
    }

    freespace_packetsize =  sizeof(bts_comm_appl_freespace_packet_t);
    timestamp_100us = (uint32_t)(bts_comm_get_timestamp() / 100UL);
    pid_freespace_packetsize = (uint32_t)bts_commpacket_make_dto_packet(pid_freespace_packetbuff,
                                                                                 bts_comm_pid_freespace,
                                                                                 0,
                                                                                 0,
                                                                                 timestamp_100us,
                                                                                 (uint8_t *)&bts_comm_appl_freespace_packet,
																				 freespace_packetsize);


    for(i=0;i<SYS_PARAM_APP_PACKET_MAX;i++)
    {
    	if(SYS_PARAM_SENSORTYPE.pid_track_en == 1 && SYS_PARAM_APPPKT_PORTS[i].port_en > 0 && SYS_PARAM_APPPKT_PORTS[i].pid_track_en ==1 && (apppkt_skipcnt % SYS_PARAM_APPPKT_PORTS[i].port_en == 0))
    	{
    		bts_comm_appdata_push(&bts_comm_apppacket_info[i], (uint8_t *)pid_freespace_packetbuff, pid_freespace_packetsize);
    	}
    }
    apppkt_skipcnt++;

#if bts_COMM_APPL_PACKETSIZE_DEBUG == 1
    krs_log("pid_freespace packetsize : %d\n\r", pid_freespace_packetsize);
#endif

}


/******************************************************************************
 * function name : bts_comm_appl_pid_freespace_packetsend
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
 * modification date : 2021.06.04
 *****************************************************************************/
void bts_comm_appl_pid_freespace_packetsend(void)
{
	if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[bts_comm_pid_freespace])==retOK)
	{
		if(bts_comm_daqinfo_is_start(bts_comm_pid_freespace) == retOK)
		{
			bts_comm_addpacket(pid_freespace_packetbuff, pid_freespace_packetsize, NULL);
		}
	}
}


/* end of file */
