/************************************************************************
| Project Name: bts_comm_appl_rs485
|    File Name: bts_comm_appl_rs485.c
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
| 2019.12.26   0.0   SKJ   Creation;
|***********************************************************************/


/* include system primitive types */
#include "bts.h"
#include <string.h>
#include "bts_comm_cfg.h"
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

//#include "rsm_task.h"
#include "bts_comm_appl_its.h"
#include "bts_comm_appl_rs485.h"
/* declare global variables */
#if SYS_RS485_ENABLE == 1
vcomm_rs485_app_t rs485_app_data;
uint8_t rs485_app_data_txbuff[16+sizeof(rs485_app_data)];
uint32_t rs485_app_data_packetsize;
#endif


/* declare static variables */
// temp gps data

/* static function prototypes */

/* functions */

// object


/******************************************************************************
 * function name : bts_comm_appl_rs485_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 void description
 * \return0 void description
 * modification date : 2019.12.26
 *****************************************************************************/
void bts_comm_appl_rs485_init(void)
{
#if SYS_RS485_ENABLE == 1
    krs_memclearitem(rs485_app_data);
    krs_memclear(rs485_app_data_txbuff);
    rs485_app_data_packetsize = 0;
#endif
}



/******************************************************************************
 * function name : bts_comm_appl_rs485_packetbuild
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 void description
 * \return0 void description
 * modification date : 2019.12.26
 *****************************************************************************/
void bts_comm_appl_rs485_packetbuild(void)
{
#if SYS_RS485_ENABLE == 1
    int32_t i;
    int32_t trkidx = 0;
    size_t txsize;
    f32_t sumofchartime;
    f32_t chartime;

    chartime = (f32_t)((1 / (f64_t)rs485.uartinst->baudrate) * 10.0f);

    // ts
    rs485_app_data.ts.u32scanindex = (int32_t)rsm_scanindex;
    rs485_app_data.ts.f64timestamp_s = ((f64_t)rsp_timestamp_us) / 1000000.0f;
    rs485_app_data.ts.tbd = 0;
    // snr
    rs485_app_data.snr.s16yaw = (int16_t)(imu_data.yaw * 10.0f);
    rs485_app_data.snr.s16roll = (int16_t)(imu_data.roll * 10.0f);
    rs485_app_data.snr.s16pitch = (int16_t)(imu_data.pitch * 10.0f);
    // pos

    rs485_app_data.pos.f32pos_lat = (f32_t)SYS_PARAM_LOCATION.location.latitude;
    rs485_app_data.pos.f32pos_lng = (f32_t)SYS_PARAM_LOCATION.location.longitude;
    rs485_app_data.pos.f32pos_north_angle = (f32_t)krs_bound(0.0f, SYS_PARAM_LOCATION.location.direction, 359.999f); // 0.0 ~ 360.0
    rs485_app_data.pos.u8pos_height = krs_u8bound(SYS_PARAM_RSP_INSTALL.height * 10.0f); // 0.0 ~ 25.5 m
    rs485_app_data.pos.s8pos_ang_azi = krs_s8bound(SYS_PARAM_RSP_INSTALL.azi_angle * 10.0f); // -12.8 ~ +12.7 deg
    rs485_app_data.pos.s8pos_ang_ele = krs_s8bound(SYS_PARAM_RSP_INSTALL.ele_angle * 10.0f); // -12.8 ~ +12.7 deg
    rs485_app_data.pos.tbd = 0;

    // gps
    if(gps_drv_data.flagDataReady == 1)
    {
        rs485_app_data.gps.f32latitude = gps_drv_data.latitude;
        rs485_app_data.gps.f32longitude = gps_drv_data.longitude;
        rs485_app_data.gps.s16speed_kph_10 = krs_s16bound(gps_drv_data.speed * 10.0f);
        rs485_app_data.gps.s16altitude_m_10 = krs_s16bound(gps_drv_data.altitude * 10.0f);
        rs485_app_data.gps.u16utc_ms = 0;
        rs485_app_data.gps.u8utc_sec = gps_drv_data.UTCSec;
        rs485_app_data.gps.u8utc_min = gps_drv_data.UTCMin;
        rs485_app_data.gps.u8utc_hour = gps_drv_data.UTCHour;
        rs485_app_data.gps.u8utc_day = gps_drv_data.UTCDay;
        rs485_app_data.gps.u8utc_month = gps_drv_data.UTCMonth;
        rs485_app_data.gps.u8utc_year = gps_drv_data.UTCYear;
    }
    else
    {
        rs485_app_data.gps.f32latitude = 0;
        rs485_app_data.gps.f32longitude = 0;
        rs485_app_data.gps.s16speed_kph_10 = 0;
        rs485_app_data.gps.s16altitude_m_10 = 0;
        rs485_app_data.gps.u16utc_ms = 0;
        rs485_app_data.gps.u8utc_sec = 0;
        rs485_app_data.gps.u8utc_min = 0;
        rs485_app_data.gps.u8utc_hour = 0;
        rs485_app_data.gps.u8utc_day = 0;
        rs485_app_data.gps.u8utc_month = 0;
        rs485_app_data.gps.u8utc_year = 0;
    }
    txsize = (sizeof(vcomm_rs485_app_t) - sizeof(vcomm_rs485_tracks_t));
    sumofchartime = chartime * txsize;
    // track
    // krs_memclearitem(rs485_app_data.tracks);
    trkidx = 0;
    for(i = 0; i < SYS_RSP_TRACK_MAX; i++)
    {
        if(Sp_Track_Out[i].Status == VERIFIED_TARGET)
        {
            rs485_app_data.tracks.track[trkidx].tid = (uint8_t)i;
            rs485_app_data.tracks.track[trkidx].status = Sp_Track_Out[i].Status;

            rs485_app_data.tracks.track[trkidx].tlen = krs_u8bound(Sp_Track_Out[i].f32Length * 10.0f); // 0.0m~25.5m

            rs485_app_data.tracks.track[trkidx].ttlc = (int16_t)Sp_Track_Out[i].f32TTLC_msec;

            rs485_app_data.tracks.track[trkidx].xpos = (int16_t)krs_bound(-4096.0f, Sp_Track_Out[i].f32PosX * 10.0f, 4095.0f);
            rs485_app_data.tracks.track[trkidx].xvel = (int16_t)krs_bound(-163.84f, Sp_Track_Out[i].f32VelX * 100.0f, 163.83f);
            rs485_app_data.tracks.track[trkidx].movstate = Sp_Track_Out[i].MovState;
            rs485_app_data.tracks.track[trkidx].updstate = Sp_Track_Out[i].UpdState;


            rs485_app_data.tracks.track[trkidx].ypos = (int16_t)krs_bound(-4096.0f, Sp_Track_Out[i].f32PosY * 10.0f, 4095.0f);
            rs485_app_data.tracks.track[trkidx].yvel = (int16_t)krs_bound(-163.84f, Sp_Track_Out[i].f32VelY * 100.0f, 163.83f);
            rs485_app_data.tracks.track[trkidx].lane = (uint8_t)(Sp_Track_Out[i].s16LaneNum);

            rs485_app_data.tracks.track[trkidx].xacc = 0;
            rs485_app_data.tracks.track[trkidx].yacc = 0;
            rs485_app_data.tracks.track[trkidx].pwrdb = krs_u8bound(Sp_Track_Out[i].f32Pow_dB * 2.0f); // 0.0db~127.0db

            trkidx++;

            sumofchartime += chartime * sizeof(vcomm_rs485_track_t);
            if(sumofchartime > 0.045f)
            {
                break;
            }
        }
    }
    rs485_app_data.tracks.u8tcnt = trkidx;

    txsize += (4 + sizeof(vcomm_rs485_track_t) * rs485_app_data.tracks.u8tcnt);

    rs485_app_data_packetsize = (uint32_t)bts_commpacket_make_dto_packet(
        rs485_app_data_txbuff, 2, 0, 0, (uint32_t)(rs485_app_data.ts.f64timestamp_s * 10000.0f),
        (uint8_t *)&rs485_app_data, txsize);
#endif
}



/******************************************************************************
 * function name : bts_comm_appl_rs485_packetsend
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 void description
 * \return0 void description
 * modification date : 2019.12.26
 *****************************************************************************/
void bts_comm_appl_rs485_packetsend(void)
{

}


/* end of file */
