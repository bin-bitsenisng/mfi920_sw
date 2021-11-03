/***********************************************************************
| Project Name: 
|    File Name: bts_comm_appl_lane_detection.c
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
| 2021.06.07   0.0  mhkim   Creation;
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

#include "lane_data_output.h"
/* declare global variables */


bts_comm_appl_lane_detection_packet_t bts_comm_appl_lane_detection_packet;
uint8_t pid_lane_detection_packetbuff[16 + sizeof(bts_comm_appl_lane_detection_packet_t)];
uint32_t pid_lane_detection_packetsize = 0;


/* declare static variables */


/* static function prototypes */

/* functions */

// lane_detection


/******************************************************************************
 * function name : bts_comm_appl_lane_detection_init
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
void bts_comm_appl_lane_detection_init(void)
{
    krs_memclearitem(bts_comm_appl_lane_detection_packet);
    krs_memclear(pid_lane_detection_packetbuff);
    pid_lane_detection_packetsize = 0;
}


/******************************************************************************
 * function name : bts_comm_appl_pid_lane_detection_packetbuild
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
void bts_comm_appl_pid_lane_detection_packetbuild(void)
{
	static int32_t apppkt_skipcnt = 0;
    int i = 0;
    uint32_t lane_detection_packetsize=0;
#if bts_COMM_APPL_PACKETSIZE_DEBUG == 1
    int32_t packetsize = 0;
#endif

    bts_comm_appl_lane_detection_packet.max_left_lane_range = lane_data_output.max_left_lane_range;
    bts_comm_appl_lane_detection_packet.max_right_lane_range = lane_data_output.max_right_lane_range;
    for(i = 0; i < 3; i++)
    {
        bts_comm_appl_lane_detection_packet.polyfit_on_left_lane[i] = lane_data_output.polyfit_on_left_lane[i];
        bts_comm_appl_lane_detection_packet.polyfit_on_right_lane[i] = lane_data_output.polyfit_on_right_lane[i];
    }    
    	
    lane_detection_packetsize = sizeof(bts_comm_appl_lane_detection_packet_t);

    pid_lane_detection_packetsize = (uint32_t)bts_commpacket_make_dto_packet(pid_lane_detection_packetbuff,
                                                                       bts_comm_pid_lane_detection,
                                                                       0,
                                                                       0,
                                                                       (uint32_t)(bts_comm_get_timestamp() / 100UL),
                                                                       (uint8_t *)&bts_comm_appl_lane_detection_packet,
																	   lane_detection_packetsize);

    for(i=0;i<SYS_PARAM_APP_PACKET_MAX;i++)
    {
    	if(SYS_PARAM_SENSORTYPE.pid_object_en == 1 && SYS_PARAM_APPPKT_PORTS[i].port_en > 0 && SYS_PARAM_APPPKT_PORTS[i].pid_object_en ==1 && (apppkt_skipcnt % SYS_PARAM_APPPKT_PORTS[i].port_en == 0))
    	{
    		bts_comm_appdata_push(&bts_comm_apppacket_info[i], (uint8_t *)pid_lane_detection_packetbuff, pid_lane_detection_packetsize);
    	}
    }
    apppkt_skipcnt++;

#if bts_COMM_APPL_PACKETSIZE_DEBUG == 1
    krs_log("pid_lane_detection packetsize : %d\n\r", pid_lane_detection_packetsize);
#endif
}


/******************************************************************************
 * function name : bts_comm_appl_pid_lane_detection_packetsend
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
void bts_comm_appl_pid_lane_detection_packetsend(void)
{
	if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[bts_comm_pid_lane_detection])==retOK)
	{
		if(bts_comm_daqinfo_is_start(bts_comm_pid_lane_detection) == retOK)
		{
			bts_comm_addpacket(pid_lane_detection_packetbuff, pid_lane_detection_packetsize, NULL);
		}
	}
}

/* end of file */
