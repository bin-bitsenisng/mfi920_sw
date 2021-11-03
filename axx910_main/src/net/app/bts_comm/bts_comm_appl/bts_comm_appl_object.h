/************************************************************************
| Project Name: bts_comm_appl_object
|    File Name: bts_comm_appl_object.h
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
#ifndef bts_COMM_APPL_OBJECT_H__
#define bts_COMM_APPL_OBJECT_H__


#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"
#include "rsp_main.h"
/* module specific types  */
//#define bts_COMM_APPL_OBJECT_MAX SYS_RSP_OBJECT_MAX
#define bts_COMM_APPL_OBJECT_MAX SP_NUM_OBJECT_MAX


/* define structure for this module */
typedef struct
{
    uint16_t id;
    uint8_t modtype;
    uint8_t reserved;
    f32_t range;
    f32_t azi_angle;
    f32_t ele_angle;
    f32_t vel;
    f32_t power;
} bts_comm_appl_object_t;

typedef struct
{
    uint16_t count;
    uint16_t active_count;
    bts_comm_appl_object_t objects[bts_COMM_APPL_OBJECT_MAX];
} bts_comm_appl_objectpacket_t;


/* declare extern global variables */
extern bts_comm_appl_objectpacket_t bts_comm_appl_objectpacket;

/* declare extern global functions */
extern void bts_comm_appl_object_init(void);
extern void bts_comm_appl_pid_object_packetbuild(void);
extern void bts_comm_appl_pid_object_packetsend(void);

#ifdef __cplusplus
}
#endif
#endif // bts_COMM_APPL_OBJECT_H__
