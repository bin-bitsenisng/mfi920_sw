/***********************************************************************
| Project Name: 
|    File Name: bts_comm_appl_freespace.h
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
| 2021.06.04   0.0  mhkim   Creation;
|***********************************************************************/

#ifndef bts_COMM_APPL_FREESPACE_H__
#define bts_COMM_APPL_FREESPACE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"

#include "Trk_Main.h"

/* module specific types  */
#define bts_COMM_APPL_FREESPACE_NUM_OF_ANGLE 90//TRK_NUM_TRACK_MAX
/* define structure for this module */
typedef struct
{
    uint32_t num_of_angle;
    uint32_t free_range[bts_COMM_APPL_FREESPACE_NUM_OF_ANGLE];
} bts_comm_appl_freespace_packet_t;

/* declare extern global variables */
extern bts_comm_appl_freespace_packet_t bts_comm_appl_freespace_packet;

/* declare extern global functions */
extern void bts_comm_appl_freespace_init(void);
extern void bts_comm_appl_pid_freespace_packetbuild(void);
extern void bts_comm_appl_pid_freespace_packetsend(void);

#ifdef __cplusplus
}
#endif
#endif // bts_COMM_APPL_FREESPACE_H__
