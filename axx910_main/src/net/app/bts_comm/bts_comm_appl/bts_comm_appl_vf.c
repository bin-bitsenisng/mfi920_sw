/************************************************************************
| Project Name: bts_comm_appl
|    File Name: bts_comm_appl.c
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


#include "bts_comm_appl_vf.h"
/* declare global variables */

/* declare static variables */
// temp gps data
#if SYS_APP_TYPE == SYS_APP_TYPE_VF
uint8_t pid_app_vf_packetbuff[16 + bts_COMM_APPL_DATASET_JSON_BUFFER_SIZE];
uint32_t pid_app_vf_packetsize = 0;

extern sys_param_pid9_vf_data_t vf_data_out;
bts_comm_appl_raw_vf_t bts_comm_appl_raw_vf;
bts_comm_appl_raw_vf_t bts_comm_appl_raw_vf_window;
#endif
/* static function prototypes */

/* functions */

// object


/******************************************************************************
 * function name : bts_comm_appl_init
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
void bts_comm_appl_vf_init(void)
{
#if SYS_APP_TYPE == SYS_APP_TYPE_VF
    krs_memclear(pid_app_vf_packetbuff);
    pid_app_vf_packetsize = 0;
    krs_memclearitem(bts_comm_appl_raw_vf);
    krs_memclearitem(bts_comm_appl_raw_vf_window);
#endif
}



/******************************************************************************
 * function name : bts_comm_appl_pid_app_vf_packetbuild
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
void bts_comm_appl_pid_app_vf_packetbuild(void)
{
#if SYS_APP_TYPE == SYS_APP_TYPE_VF
	static int32_t apppkt_skipcnt = 0;
	int32_t i;
    int32_t len = 0;
    int32_t packetsize = 0;

    if(vf_data_stackidx > SYS_PARAM_VF_SERVER.server_sendstack_size)
    {
    	len = sys_param_pid9_vf_data_t_dump("", bts_comm_appl_dataset_json_buffer, &vf_data_out);
    	vf_data_stackidx = 0;
    }
    else
    {
    	len = 0;
    }

    pid_app_vf_packetsize = 0;
    if(len > 0)
    {
#if bts_COMM_APPL_JSON_DEBUG == 1
        krs_log("STATUS : \n\r%s\n\r", bts_comm_appl_dataset_json_buffer);
#endif
        pid_app_vf_packetsize = (uint32_t)bts_commpacket_make_dto_packet(pid_app_vf_packetbuff,
                                                                            bts_comm_pid_app_vf,
                                                                            0,
                                                                            0,
                                                                            (uint32_t)(bts_comm_get_timestamp() / 100UL),
                                                                            (uint8_t *)&bts_comm_appl_dataset_json_buffer,
                                                                            len);
        for(i=0;i<SYS_PARAM_APP_PACKET_MAX;i++)
        {
            if(SYS_PARAM_SENSORTYPE.pid_status_en == 1 && SYS_PARAM_APPPKT_PORTS[i].port_en > 0 && SYS_PARAM_APPPKT_PORTS[i].pid_status_en ==1 && (apppkt_skipcnt % SYS_PARAM_APPPKT_PORTS[i].port_en == 0))
            {
                bts_comm_appdata_push(&bts_comm_apppacket_info[i], (uint8_t *)pid_app_vf_packetbuff, pid_app_vf_packetsize);
            }
        }
        apppkt_skipcnt++;

#if bts_COMM_APPL_PACKETSIZE_DEBUG == 1
        krs_log("pid_app_vf packetsize : %d\n\r", pid_app_vf_packetsize);
#endif
    }
#endif
}




/******************************************************************************
 * function name : bts_comm_appl_pid_app_vf_packetsend
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
void bts_comm_appl_pid_app_vf_packetsend(void)
{
#if SYS_APP_TYPE == SYS_APP_TYPE_VF
	if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[bts_comm_pid_app_vf])==retOK)
	{
		if(bts_comm_daqinfo_is_start(bts_comm_pid_app_vf) == retOK)
		{
			bts_comm_addpacket(pid_app_vf_packetbuff, pid_app_vf_packetsize, NULL);
		}
	}
#endif
}





/******************************************************************************
 * function name : bts_comm_appl_raw_app_vf_precallback
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
 * modification date : 2018.07.27
 *****************************************************************************/
void bts_comm_appl_raw_app_vf_precallback(void *pvparam, size_t size)
{
#if SYS_APP_TYPE == SYS_APP_TYPE_VF
    bts_comm_appl_raw_vf_t *vf_raw_ptr =  (bts_comm_appl_raw_vf_t *)pvparam;
    static int32_t currentpos = 0;
    int32_t headpos = 0;
    int32_t i;
    // input
    // TrackOut
    // vf_data_out

    bts_comm_appl_raw_vf_window.dat[currentpos] = vf_data_out.dat[0];
    bts_comm_appl_raw_vf_window.war[currentpos] = vf_data_out.war[0];
    bts_comm_appl_raw_vf_window.det[currentpos] = vf_data_out.det[0];
    bts_comm_appl_raw_vf_window.sw[currentpos] = vf_data_out.sw[0];


    for(i = 0; i < 128; i++)
    {
        headpos = (i + currentpos + 1) % 128;
        vf_raw_ptr->dat[i] = bts_comm_appl_raw_vf_window.dat[headpos];
        vf_raw_ptr->war[i] = bts_comm_appl_raw_vf_window.war[headpos];
        vf_raw_ptr->det[i] = bts_comm_appl_raw_vf_window.det[headpos];
        vf_raw_ptr->sw[i] = bts_comm_appl_raw_vf_window.sw[headpos];
    }
    currentpos = (currentpos + 1) % 128;
#endif
}


/* end of file */
