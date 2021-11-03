/***********************************************************************
| Project Name: 
|    File Name: bts_comm_appl_ai_object.h
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

#ifndef bts_COMM_APPL_AI_OBJECT_H__
#define bts_COMM_APPL_AI_OBJECT_H__


#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"
#include "rsp_main.h"
/* module specific types  */
#define bts_COMM_APPL_AI_OBJECT_MAX SYS_AI_OBJECT_MAX


/* define structure for this module */
typedef struct
{
    uint32_t class_id;
    f32_t confidence;
    uint32_t height;
    uint32_t width;
    uint32_t x_location;
    uint32_t y_location;
} bts_comm_appl_ai_object_t;


typedef struct
{
    uint16_t count;
    uint16_t active_count;
    bts_comm_appl_ai_object_t objects[bts_COMM_APPL_AI_OBJECT_MAX];
} bts_comm_appl_ai_objectpacket_t;


/* declare extern global variables */
extern bts_comm_appl_ai_objectpacket_t bts_comm_appl_ai_objectpacket;

/* declare extern global functions */
extern void bts_comm_appl_ai_object_init(void);
extern void bts_comm_appl_pid_ai_object_packetbuild(void);
extern void bts_comm_appl_pid_ai_object_packetsend(void);

#ifdef __cplusplus
}
#endif
#endif // bts_COMM_APPL_AI_OBJECT_H__
