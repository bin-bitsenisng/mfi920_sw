/************************************************************************
| Project Name: bts_comm_appl_rs485
|    File Name: bts_comm_appl_rs485.h
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
#ifndef bts_COMM_APPL_RS485_H__
#define bts_COMM_APPL_RS485_H__

#ifdef __cplusplus
extern "C" {
#endif

/* include system primitive types */
#include "bts.h"
#include "rsp_main.h"

#define SYS_RSP_TRACK_MAX SP_NUM_TRACK_MAX

/* module specific types  */


/* define structure for this module */
typedef struct
{
    f64_t f64timestamp_s;
    uint32_t u32scanindex;
    uint32_t tbd;
}vcomm_rs485_ts_t;

typedef struct
{
    int16_t s16yaw;        // 0.0 ~ 360.0
    int16_t s16roll;
    int16_t s16pitch;
    int16_t s16altitude;
}vcomm_rs485_sensor_t;


typedef struct
{
    f32_t f32pos_lat;
    f32_t f32pos_lng;
    f32_t f32pos_north_angle; // 0.0 ~ 360.0
    uint8_t u8pos_height;   // 0.0 ~ 25.5 m
    int8_t s8pos_ang_azi;   // -12.8 ~ +12.7 deg
    int8_t s8pos_ang_ele;   // -12.8 ~ +12.7 deg
    uint8_t tbd;
}vcomm_rs485_pos_t;


typedef struct
{
    f32_t f32latitude;
    f32_t f32longitude;
    int16_t s16speed_kph_10;
    int16_t s16altitude_m_10;
    uint16_t u16utc_ms;
    uint8_t u8utc_sec;
    uint8_t u8utc_min;
    uint8_t u8utc_hour;
    uint8_t u8utc_day;
    uint8_t u8utc_month;
    uint8_t u8utc_year;
}vcomm_rs485_gps_t;


typedef struct
{
    // 1
    uint32_t tid:6;     // 0~63
    uint32_t status: 2; //
    // 1
    uint32_t tlen:8;
    // 2
    uint32_t ttlc: 16;  // 4

    // 4
    uint32_t xpos: 13;  // -409.6 ~ 409.5 m
    uint32_t xvel: 15;  // -163.84 ~ +163.83 m/s
    uint32_t movstate: 2; //
    uint32_t updstate: 2; //

    // 4
    uint32_t ypos: 13;  // -409.6 ~ 409.5 m
    uint32_t yvel: 15;  // -163.84 ~ +163.83 m/s
    uint32_t lane: 4; // 0,1,2,3,x,x,x,x

    // 4
    uint32_t xacc: 12;  // -20.48 ~ ~20.47
    uint32_t yacc: 12;  // -20.48 ~ ~20.47
    uint32_t pwrdb: 8;  // 0.0 ~ 127.0 dBm, factor 0.5
}vcomm_rs485_track_t;


typedef struct
{
    uint8_t u8tcnt;
    uint8_t tbd[3];
    vcomm_rs485_track_t track[SYS_RSP_TRACK_MAX];
}vcomm_rs485_tracks_t;

typedef struct
{
    vcomm_rs485_ts_t ts;        // 16 bytes
    vcomm_rs485_sensor_t snr;   // 8 bytes
    vcomm_rs485_pos_t pos;  // 16 bytes
    vcomm_rs485_gps_t gps; // 20 bytes
    vcomm_rs485_tracks_t tracks;
}vcomm_rs485_app_t;

/* declare extern global variables */
extern vcomm_rs485_app_t rs485_app_data;
extern uint8_t rs485_app_data_txbuff[16+sizeof(rs485_app_data)];
extern uint32_t rs485_app_data_packetsize;
/* declare extern global functions */
extern void bts_comm_appl_rs485_init(void);
extern void bts_comm_appl_rs485_packetbuild(void);
extern void bts_comm_appl_rs485_packetsend(void);


#ifdef __cplusplus
}
#endif

#endif // bts_COMM_APPL_RS485_H__
