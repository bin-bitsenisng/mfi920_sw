/************************************************************************
| Project Name: bts_comm_appl_status
|    File Name: bts_comm_appl_status.c
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
//#include "rsp_task.h"
#include "daq_thread.h"
//#include "snr_task.h"
#include "sys_param.h"

/* final include module header */
#include "bts_comm.h"
#include "bts_comm_appl.h"
#include "bts_comm_appl_status.h"
#include "bts_comm_cmd.h"
#include "bts_comm_packet.h"
#include "bts_comm_status.h"

/* declare global variables */
uint8_t pid_status_packetbuff[16 + bts_COMM_APPL_DATASET_JSON_BUFFER_SIZE];
uint32_t pid_status_packetsize = 0;

/* declare static variables */
// temp gps data
char_t *gps_data = "$GNGGA,050839.000,3726.2834,N,12710.0301,E,1,5,2.53,310.7,M,20.0,M,,*49 \
                $GPGSA,A,3,02,06,12,28,17,,,,,,,,2.70,2.53,0.96*07 \
                $GLGSA,A,3,,,,,,,,,,,,,2.70,2.53,0.96*10 \
                $GPGSV,3,1,12,19,79,348,17,17,74,111,18,06,57,307,39,23,31,091,13*79 \
                $GPGSV,3,2,12,09,30,126,,02,20,279,24,12,18,317,36,28,17,184,28*7F \
                $GPGSV,3,3,12,22,07,046,,01,03,079,,193,,,,38,,,*43 \
                $GLGSV,1,1,01,84,44,083,*53 \
                $GNRMC,050839.000,A,3726.2834,N,12710.0301,E,0.76,279.99,290817,,,A*75 \
                $GNVTG,279.99,T,,M,0.76,N,1.41,K,A*2A";

/* static function prototypes */

/* functions */

// object


/******************************************************************************
 * function name : bts_comm_appl_status_init
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
void bts_comm_appl_status_init(void)
{
    krs_memclear(pid_status_packetbuff);
    pid_status_packetsize = 0;
}


/******************************************************************************
 * function name : bts_comm_appl_pid_status_packetbuild
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
void bts_comm_appl_pid_status_packetbuild(void)
{
	static int32_t apppkt_skipcnt = 0;
	int32_t i;
    int32_t len = 0;

    len = bts_comm_appl_status_get_info(bts_comm_appl_dataset_json_buffer,
                                          sizeof(bts_comm_appl_dataset_json_buffer));
    if(len > 0)
    {
#if bts_COMM_APPL_JSON_DEBUG == 1
        krs_log("STATUS : \n\r%s\n\r", bts_comm_appl_dataset_json_buffer);
#endif
        pid_status_packetsize = (uint32_t)bts_commpacket_make_dto_packet(pid_status_packetbuff,
                                                                          bts_comm_pid_status,
                                                                          0,
                                                                          0,
                                                                          (uint32_t)(bts_comm_get_timestamp() / 100UL),
                                                                          (uint8_t *)&bts_comm_appl_dataset_json_buffer,
                                                                          len);

        for(i=0;i<SYS_PARAM_APP_PACKET_MAX;i++)
        {
        	if(SYS_PARAM_SENSORTYPE.pid_status_en == 1 && SYS_PARAM_APPPKT_PORTS[i].port_en > 0 && SYS_PARAM_APPPKT_PORTS[i].pid_status_en ==1 && (apppkt_skipcnt % SYS_PARAM_APPPKT_PORTS[i].port_en == 0))
        	{
        		bts_comm_appdata_push(&bts_comm_apppacket_info[i], (uint8_t *)pid_status_packetbuff, pid_status_packetsize);
        	}
        }
        apppkt_skipcnt++;

#if bts_COMM_APPL_PACKETSIZE_DEBUG == 1
        krs_log("pid_status packetsize : %d\n\r", pid_status_packetsize);
#endif
    }
}



uint32_t bts_comm_appl_system_status_packetbuild(uint8_t *destbuff, size_t buffsize, char_t *jsonbuff, size_t len)
{
	uint32_t packetsize = 0;

	if(buffsize < (len+9))
	{
		krs_log("destbuff size is too small\n\r");
		return 0;
	}
	packetsize = bts_commpacket_make_cro_packet(destbuff, IR24XCOMMCMD_GET_STATUS, (uint8_t*)jsonbuff, len);
    return packetsize;
}

/******************************************************************************
 * function name : bts_comm_appl_pid_status_packetsend
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
void bts_comm_appl_pid_status_packetsend(void)
{
	if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[bts_comm_pid_status])==retOK)
	{
		if(bts_comm_daqinfo_is_start(bts_comm_pid_status) == retOK)
		{
			bts_comm_addpacket(pid_status_packetbuff, pid_status_packetsize, NULL);
		}
	}
}


/******************************************************************************
 * function name : bts_comm_appl_status_get_info
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *desbuffer description
 * \return int32_t description
 * modification date : 2017.09.22
 *****************************************************************************/
int32_t bts_comm_appl_status_get_info(char_t *desbuffer, uint32_t buffsize)
{
	//gps_drv_data_t bts_comm_gpsdata;
    uint32_t i;
    uint32_t status_len=0;
    uint32_t status_len_aligend=0;

    /////////////////////////
    //printf("[WARNING] Make it alive.\n");
    /////////////////////////

    appljson_pid0_status_data.scanindex = (int32_t)daq_scanindex;
/*
    appljson_pid0_status_data.timestamp.timestamp_s = ((f64_t)rsp_timestamp_us) / 1000000.0f;
    appljson_pid0_status_data.timestamp.rsp_timestamp_us = rsp_timestamp_us;
    appljson_pid0_status_data.timestamp.net_timestamp_us = os_time_us();
    appljson_pid0_status_data.timestamp.rsp_cycletime = rsp_cycletime_s;

    appljson_pid0_status_data.position.pitch = imu_data.pitch;
    appljson_pid0_status_data.position.yaw = imu_data.yaw;
    appljson_pid0_status_data.position.roll = imu_data.roll;
    appljson_pid0_status_data.position.altitude =imu_data.altidude_m;

    appljson_pid0_status_data.ecuinfo.temp_core = xadc_drv_cpu_electrical_info.dietemperature;
    appljson_pid0_status_data.ecuinfo.temp_rfm = 0.0f;
    appljson_pid0_status_data.ecuinfo.vin = xadc_drv_cpu_electrical_info.pwr24v;
    appljson_pid0_status_data.ecuinfo.v5 = xadc_drv_cpu_electrical_info.pwr5v;
    appljson_pid0_status_data.ecuinfo.v1_5 = xadc_drv_cpu_electrical_info.vccddr;
    appljson_pid0_status_data.ecuinfo.v1_0 = xadc_drv_cpu_electrical_info.vccint;

    appljson_pid0_status_data.gps.status = 0;
    appljson_pid0_status_data.gps.data[0] = 0;

    if(snr_gps_data_queue != NULL)
    {
		//if(os_queue_take(snr_gps_data_queue, &bts_comm_gpsdata, 0) == os_retOK)
        if(GetQueue(&snr_gps_data_queue, &bts_comm_gpsdata) == os_retOK)
		{
			if(bts_comm_gpsdata.len < 1024)
			{
				appljson_pid0_status_data.gps.status = 1;
				strncpy(appljson_pid0_status_data.gps.data, (char_t *)bts_comm_gpsdata.buff, krs_min(bts_comm_gpsdata.len, 1024));
				//krs_log("commGPS:\n\r%.*s\n\r", bts_comm_gpsdata.len, bts_comm_gpsdata.buff);
			}
			else
			{
				appljson_pid0_status_data.gps.status = 0;
				appljson_pid0_status_data.gps.data[0] = 0;
			}
		}
    }
    */
    status_len = sys_param_pid0_status_data_t_dump("", desbuffer, &appljson_pid0_status_data);

    // 4byte align and zero padding
    status_len_aligend = krs_size_align(status_len, 4);
    for(i=status_len;i<status_len_aligend;i++)
    {
    	desbuffer[i]=0;
    }
    return status_len_aligend;
}


/* end of file */
