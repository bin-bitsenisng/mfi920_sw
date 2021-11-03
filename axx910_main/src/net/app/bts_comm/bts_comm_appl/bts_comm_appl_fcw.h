/************************************************************************
| Project Name: bts_comm_appl_fcw
|    File Name: bts_comm_appl_fcw.h
|  Description: file detailed description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------
| SKJ          SONG KYEONG JIN           Bitsensing
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description
| ----------  ----  ------  --------------------------------------------
| 2019.04.13   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef bts_COMM_APPL_FCW_H__
#define bts_COMM_APPL_FCW_H__

#ifdef __cplusplus
extern "C" {
#endif

/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"

/* module specific types  */


/* define structure for this module */
typedef struct
{
	f32_t vehicle_speed;
	f32_t wheel_speed_fl;
	f32_t wheel_speed_fr;
	f32_t wheel_speed_rl;
	f32_t wheel_speed_rr;
	f32_t steerangle;
	f32_t steeranglespeed;
	f32_t yawrate;
	f32_t longaccel;
	f32_t lataccel;
	uint32_t eventflag;
}comm_appl_fcwinfo_t;


/* declare extern global variables */
extern comm_appl_fcwinfo_t comm_appl_fcwinfo;

/* declare extern global functions */
extern void bts_comm_appl_fcw_init(void);
extern void bts_comm_appl_pid_app_fcw_packetbuild(void);
extern void bts_comm_appl_pid_app_fcw_packetsend(void);
extern void bts_comm_appl_raw_app_fcw_precallback(void *pvparam, size_t size);

#ifdef __cplusplus
}
#endif

#endif // bts_COMM_APPL_FCW_H__
