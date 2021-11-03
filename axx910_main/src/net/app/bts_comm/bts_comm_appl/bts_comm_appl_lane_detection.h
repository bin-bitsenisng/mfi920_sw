/***********************************************************************
| Project Name: 
|    File Name: bts_comm_appl_lane_detection.h
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
| 2021.06.07   0.0  mhkim   Creation;
|***********************************************************************/

#ifndef bts_COMM_APPL_LANE_DETECTION_H__
#define bts_COMM_APPL_LANE_DETECTION_H__


#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"
#include "lane_data_output.h"


/* define structure for this module */
typedef struct
{
	float max_left_lane_range;
	float max_right_lane_range;
	float polyfit_on_left_lane[3];
	float polyfit_on_right_lane[3];
} bts_comm_appl_lane_detection_packet_t;


/* declare extern global variables */
extern bts_comm_appl_lane_detection_packet_t bts_comm_appl_lane_detection_packet;

/* declare extern global functions */
extern void bts_comm_appl_object_init(void);
extern void bts_comm_appl_pid_object_packetbuild(void);
extern void bts_comm_appl_pid_object_packetsend(void);

#ifdef __cplusplus
}
#endif
#endif // bts_COMM_APPL_OBJECT_H__
