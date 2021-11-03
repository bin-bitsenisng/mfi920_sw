/************************************************************************
| Project Name: bts_comm_appl_track
|    File Name: bts_comm_appl_track.c
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
#include "imu.h"

#include "bts_comm_appl_its.h"

#include "Sp_Main.h"
/* declare global variables */
bts_comm_appl_track_status_t trackstatus;
bts_comm_appl_trackpacket_t bts_comm_appl_trackpacket;
uint8_t pid_track_packetbuff[16 + sizeof(bts_comm_appl_trackpacket_t)];
uint32_t pid_track_packetsize = 0;
/* declare static variables */
// temp gps data

/* static function prototypes */

/* functions */

// object


/******************************************************************************
 * function name : bts_comm_appl_track_init
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
void bts_comm_appl_track_init(void)
{
    krs_memclear(pid_track_packetbuff);
    pid_track_packetsize = 0;
}


/******************************************************************************
 * function name : bts_comm_appl_pid_track_packetbuild
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
void bts_comm_appl_pid_track_packetbuild(void)
{
	static int32_t apppkt_skipcnt = 0;
    int32_t i = 0;
    uint32_t timestamp_100us;
    uint32_t trkidx=0;
    uint8_t trackouten=0;
    imu_flip_status_t flipside = imu_flip_status_upside;
    krs_memclearitem(bts_comm_appl_trackpacket.tracks);
    uint32_t track_packetsize=0;

    //flipside = imu_drv_get_flip_status();

    trkidx = 0;

    for(i = 0; i < bts_COMM_APPL_TRACK_MAX; i++)
    {
        trackstatus.R = 0;
        trackouten = 0;
        if(SYS_PARAM_RSPTRK_POSTTUNE.TrackOutFilter == 0)
        {	// NewTrack + VerifiedTrack
        	if(Sp_TrackOut[i].u8Status != NOT_TARGET)
        	{
        		trackouten = 1;
        	}
        }
        else if(SYS_PARAM_RSPTRK_POSTTUNE.TrackOutFilter == 1)
        {	// Verified Track Only
        	if(Sp_TrackOut[i].u8Status == VERIFIED_TARGET)
        	{
        		trackouten = 1;
        	}
        }
        else if(SYS_PARAM_RSPTRK_POSTTUNE.TrackOutFilter == 2)
        {
        	if((Sp_TrackOut[i].u8Status == VERIFIED_TARGET) && (Sp_TrackOut[i].u8MovState != STATIONARY))
        	{
        		trackouten = 1;
        	}
        }
        else
        {
        	// all
        	trackouten = 1;
        }

        if(trackouten != 0)
        {
            trackstatus.Bit.status = Sp_TrackOut[i].u8Status;
            trackstatus.Bit.reserved = 1;
            trackstatus.Bit.update = Sp_TrackOut[i].u8UpdState;
            trackstatus.Bit.move = Sp_TrackOut[i].u8MovState;


			bts_comm_appl_trackpacket.tracks[trkidx].ypos = Sp_TrackOut[i].f32PosY_m;
			bts_comm_appl_trackpacket.tracks[trkidx].yvel = (f32_t)(Sp_TrackOut[i].f32VelY_mps);

        	if(flipside == imu_flip_status_upside)
        	{
        		bts_comm_appl_trackpacket.tracks[trkidx].xpos = Sp_TrackOut[i].f32PosX_m;
        		bts_comm_appl_trackpacket.tracks[trkidx].xvel = (f32_t)(Sp_TrackOut[i].f32VelX_mps);
        	}
        	else
        	{
        		bts_comm_appl_trackpacket.tracks[trkidx].xpos = -Sp_TrackOut[i].f32PosX_m;
        		bts_comm_appl_trackpacket.tracks[trkidx].xvel = -(f32_t)(Sp_TrackOut[i].f32VelX_mps);
        	}

            bts_comm_appl_trackpacket.tracks[trkidx].idx = (uint8_t)Sp_TrackOut[i].s8Idx;
        	//bts_comm_appl_trackpacket.tracks[trkidx].status = (uint8_t)Sp_TrackOut[i].u8Status;
            bts_comm_appl_trackpacket.tracks[trkidx].status = (Sp_TrackOut[i].u8MovState << 6) + \
                                                                (Sp_TrackOut[i].u8UpdState << 4) + Sp_TrackOut[i].u8Status;
            bts_comm_appl_trackpacket.tracks[trkidx].aliveage = (uint16_t)Sp_TrackOut[i].u16AliveAge;

            bts_comm_appl_trackpacket.tracks[trkidx].refxpos = (f32_t)(Sp_TrackOut[i].f32RefPosX_m);
			bts_comm_appl_trackpacket.tracks[trkidx].refypos = (f32_t)Sp_TrackOut[i].f32RefPosY_m;
						
			bts_comm_appl_trackpacket.tracks[trkidx].headang = (f32_t)(Sp_TrackOut[i].f32HeadingAng_deg);
			bts_comm_appl_trackpacket.tracks[trkidx].power = (f32_t)(Sp_TrackOut[i].f32Power_dB);
            bts_comm_appl_trackpacket.tracks[trkidx].width = (f32_t)(Sp_TrackOut[i].f32Width_m);
			bts_comm_appl_trackpacket.tracks[trkidx].length = (f32_t)(Sp_TrackOut[i].f32Length_m);
            bts_comm_appl_trackpacket.tracks[trkidx].fusion_class = (f32_t)(Sp_TrackOut[i].u32ObjClass);
            bts_comm_appl_trackpacket.tracks[trkidx].fusion_type = (f32_t)(Sp_TrackOut[i].u32FusionType);
            bts_comm_appl_trackpacket.tracks[trkidx].zpos = (f32_t)(Sp_TrackOut[i].f32PosZ);
            bts_comm_appl_trackpacket.tracks[trkidx].height = (f32_t)(Sp_TrackOut[i].f32Height);
            
			trkidx++;
        }
    }
    bts_comm_appl_trackpacket.count = bts_COMM_APPL_TRACK_MAX;
    bts_comm_appl_trackpacket.active_count = trkidx;

    track_packetsize =  4+sizeof(bts_comm_appl_track_t)*trkidx;
    timestamp_100us = (uint32_t)(bts_comm_get_timestamp() / 100UL);
    pid_track_packetsize = (uint32_t)bts_commpacket_make_dto_packet(pid_track_packetbuff,
                                                                                 bts_comm_pid_track,
                                                                                 0,
                                                                                 0,
                                                                                 timestamp_100us,
                                                                                 (uint8_t *)&bts_comm_appl_trackpacket,
																				 track_packetsize);


    for(i=0;i<SYS_PARAM_APP_PACKET_MAX;i++)
    {
    	if(SYS_PARAM_SENSORTYPE.pid_track_en == 1 && SYS_PARAM_APPPKT_PORTS[i].port_en > 0 && SYS_PARAM_APPPKT_PORTS[i].pid_track_en ==1 && (apppkt_skipcnt % SYS_PARAM_APPPKT_PORTS[i].port_en == 0))
    	{
    		bts_comm_appdata_push(&bts_comm_apppacket_info[i], (uint8_t *)pid_track_packetbuff, pid_track_packetsize);
    	}
    }
    apppkt_skipcnt++;

#if bts_COMM_APPL_PACKETSIZE_DEBUG == 1
    krs_log("pid_track packetsize : %d\n\r", pid_track_packetsize);
#endif

}


/******************************************************************************
 * function name : bts_comm_appl_pid_track_packetsend
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
void bts_comm_appl_pid_track_packetsend(void)
{
	if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[bts_comm_pid_track])==retOK)
	{
		if(bts_comm_daqinfo_is_start(bts_comm_pid_track) == retOK)
		{
			bts_comm_addpacket(pid_track_packetbuff, pid_track_packetsize, NULL);
		}
	}
}


/* end of file */
