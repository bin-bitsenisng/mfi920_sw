/***********************************************************************
| Project Name: 
|    File Name: bts_comm_appl_ai_object.c
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
| 2021.04.21   0.0  mhkim   Creation;
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

#include "inference.h"
/* declare global variables */


bts_comm_appl_ai_objectpacket_t bts_comm_appl_ai_objectpacket;
uint8_t pid_ai_object_packetbuff[16 + sizeof(bts_comm_appl_ai_objectpacket_t)];
uint32_t pid_ai_object_packetsize = 0;


/* declare static variables */


/* static function prototypes */

/* functions */

// ai_object


/******************************************************************************
 * function name : bts_comm_appl_ai_object_init
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
void bts_comm_appl_ai_object_init(void)
{
    krs_memclearitem(bts_comm_appl_ai_objectpacket);
    krs_memclear(pid_ai_object_packetbuff);
    pid_ai_object_packetsize = 0;
}


/******************************************************************************
 * function name : bts_comm_appl_pid_ai_object_packetbuild
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
void bts_comm_appl_pid_ai_object_packetbuild(void)
{
	static int32_t apppkt_skipcnt = 0;
    int32_t i = 0;
    int32_t objidx=0;
    uint32_t ai_object_packetsize=0;
#if bts_COMM_APPL_PACKETSIZE_DEBUG == 1
    int32_t packetsize = 0;
#endif
    //imu_flip_status_t flipside = imu_flip_status_upside;

    krs_memclearitem(bts_comm_appl_ai_objectpacket.objects);

	//flipside = imu_drv_get_flip_status();

	objidx = 0;
    for(i = 0; i < ai_object[0].Ai_num_of_class; i++)
    {
        bts_comm_appl_ai_objectpacket.objects[i].class_id = ai_object[i].Ai_class_id;
        bts_comm_appl_ai_objectpacket.objects[i].confidence = ai_object[i].Ai_confidence;
        bts_comm_appl_ai_objectpacket.objects[i].height = ai_object[i].Ai_height;
        bts_comm_appl_ai_objectpacket.objects[i].width = ai_object[i].Ai_width;
        bts_comm_appl_ai_objectpacket.objects[i].x_location = ai_object[i].Ai_x_location;
        bts_comm_appl_ai_objectpacket.objects[i].y_location = ai_object[i].Ai_y_location;
/*
        printf("class_id: %d\n", bts_comm_appl_ai_objectpacket.objects[i].class_id);
        printf("confidence: %f\n", bts_comm_appl_ai_objectpacket.objects[i].confidence);
        printf("height: %d\n", bts_comm_appl_ai_objectpacket.objects[i].height);
        printf("width: %d\n", bts_comm_appl_ai_objectpacket.objects[i].width);
        printf("x_location: %d\n", bts_comm_appl_ai_objectpacket.objects[i].x_location);
        printf("y_location: %d\n", bts_comm_appl_ai_objectpacket.objects[i].y_location);*/
    }
    bts_comm_appl_ai_objectpacket.count = bts_COMM_APPL_AI_OBJECT_MAX;
    bts_comm_appl_ai_objectpacket.active_count = ai_object[0].Ai_num_of_class;
    ai_object_packetsize = 4 + sizeof(bts_comm_appl_ai_object_t)*ai_object[0].Ai_num_of_class;


    pid_ai_object_packetsize = (uint32_t)bts_commpacket_make_dto_packet(pid_ai_object_packetbuff,
                                                                       bts_comm_pid_ai_object,
                                                                       0,
                                                                       0,
                                                                       (uint32_t)(bts_comm_get_timestamp() / 100UL),
                                                                       (uint8_t *)&bts_comm_appl_ai_objectpacket,
																	   ai_object_packetsize);

    for(i=0;i<SYS_PARAM_APP_PACKET_MAX;i++)
    {
    	//if(SYS_PARAM_SENSORTYPE.pid_ai_object_en == 1 && SYS_PARAM_APPPKT_PORTS[i].port_en > 0 && SYS_PARAM_APPPKT_PORTS[i].pid_ai_object_en ==1 && (apppkt_skipcnt % SYS_PARAM_APPPKT_PORTS[i].port_en == 0))
        if(SYS_PARAM_SENSORTYPE.pid_object_en == 1 && SYS_PARAM_APPPKT_PORTS[i].port_en > 0 && SYS_PARAM_APPPKT_PORTS[i].pid_object_en ==1 && (apppkt_skipcnt % SYS_PARAM_APPPKT_PORTS[i].port_en == 0))
    	{
    		bts_comm_appdata_push(&bts_comm_apppacket_info[i], (uint8_t *)pid_ai_object_packetbuff, pid_ai_object_packetsize);
    	}
    }
    apppkt_skipcnt++;

#if bts_COMM_APPL_PACKETSIZE_DEBUG == 1
    krs_log("pid_ai_object packetsize : %d\n\r", pid_ai_object_packetsize);
#endif
}


/******************************************************************************
 * function name : bts_comm_appl_pid_ai_object_packetsend
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
void bts_comm_appl_pid_ai_object_packetsend(void)
{
	if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[bts_comm_pid_ai_object])==retOK)
	{
		if(bts_comm_daqinfo_is_start(bts_comm_pid_ai_object) == retOK)
		{
			bts_comm_addpacket(pid_ai_object_packetbuff, pid_ai_object_packetsize, NULL);
		}
	}
}

/* end of file */
