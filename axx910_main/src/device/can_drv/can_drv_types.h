/************************************************************************
| Project Name: can_drv_types
|    File Name: can_drv_types.h
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
| 2018.10.22   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef CAN_DRV_TYPES_H__
#define CAN_DRV_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

/* include system primitive types */
#include "bts.h"
#include "can_drv_cfg.h"

/* module specific types  */


/* define structure for this module */
typedef enum
{
	can_drv_com_sigendian_little=0,
	can_drv_com_sigendian_I = 0,
	can_drv_com_sigendian_intel = 0,
	can_drv_com_sigendian_big = 1,
	can_drv_com_sigendian_M = 1,
	can_drv_com_sigendian_motorola = 1
}can_drv_com_sigendian_t;


typedef enum
{
	can_drv_opmode_normal,
	can_drv_opmode_listenonly
}can_drv_opmode_t;

typedef struct
{
    uint8_t len; // byte size
    uint8_t dev_id;
    uint8_t ch_id;
    uint8_t dlc;
    uint32_t timestamp;
    uint32_t id;
    union64_t buff;
} can_drv_msg_t;

typedef union
{
	uint32_t R;
	struct{
    uint32_t rtr : 1;
    uint32_t id17_0 : 18;
    uint32_t ide : 1;
    uint32_t str_rtr : 1;
    uint32_t id28_18 : 11;
	};
}can_drv_zynq_canps_id_t;

typedef struct
{
    uint32_t rtr : 1;
    uint32_t id17_0 : 18;
    uint32_t ide : 1;
    uint32_t str_rtr : 1;
    uint32_t id28_18 : 11;
    uint32_t ts : 16;
    uint32_t reserved : 12;
    uint32_t dlc : 4;
    uint32_t dataword1 : 32;
    uint32_t dataword2 : 32;
} can_drv_zynq_canps_msg_t;


/* declare extern global variables */

/* declare extern global functions */


#ifdef __cplusplus
}
#endif

#endif // CAN_DRV_TYPES_H__
