/************************************************************************
| Project Name: can_sig
|    File Name: can_sig.h
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
| 2019.04.03   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef CAN_SIG_H__
#define CAN_SIG_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* include system primitive types */
#include "bts.h"
#include "can_drv_types.h"
#include "sys_param.h"

/* module specific types  */


/* define structure for this module */
typedef enum
{
    can_sig_id_vehicle_speed,
    can_sig_id_wheel_speed_fl,
    can_sig_id_wheel_speed_fr,
    can_sig_id_wheel_speed_rl,
    can_sig_id_wheel_speed_rr,
    can_sig_id_steerangle,
    can_sig_id_steeranglespeed,
    can_sig_id_yawrate,
    can_sig_id_longaccel,
    can_sig_id_lataccel,
} can_sig_id_t;


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
} can_sig_data_t;


/* declare extern global variables */
extern can_sig_data_t can_sig_data;
/* declare extern global functions */
extern void can_sig_init(void);
extern void can_sig_osinit(void);
extern int32_t can_sig_getsignal(uint8_t *srcbuff, f32_t *destdata,
                                 sys_param_cansignal_t *siginfo);
extern int32_t can_sig_getsignal_raw(uint8_t *srcBuf, uint32_t *dstData,
                                     can_drv_com_sigendian_t endian, int16_t startBit,
                                     uint8_t bitSize);


#ifdef __cplusplus
}
#endif

#endif // CAN_SIG_H__
