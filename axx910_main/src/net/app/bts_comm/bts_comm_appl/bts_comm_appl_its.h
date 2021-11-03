/************************************************************************
| Project Name: bts_comm_appl_its
|    File Name: bts_comm_appl_its.h
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
#ifndef bts_COMM_APPL_ITS_H__
#define bts_COMM_APPL_ITS_H__


#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"

/* module specific types  */


/* define structure for this module */

typedef struct
{
	uint32_t autoalignment_on;
	uint32_t s16StackCnt;
	uint32_t u32num_track_autoalignment;
	uint32_t status_autoalignment;
	uint32_t prv_autoalignment_on;
	float32_t f32AlignedAngle;
}bts_comm_appl_raw_app_its_t;


typedef struct
{
    f32_t angle_azi;
    f32_t angle_ele;
    f32_t height_m;
}bts_comm_appl_raw_app_its_installinfo_t;



/* declare extern global variables */
extern bts_comm_appl_raw_app_its_t raw_app_its;
extern bts_comm_appl_raw_app_its_installinfo_t  raw_app_installinfo;

/* declare extern global functions */
extern void bts_comm_appl_its_init(void);
extern void bts_comm_appl_pid_app_its_packetbuild(void);
extern void bts_comm_appl_pid_app_its_packetsend(void);
extern void bts_comm_appl_raw_app_its_precallback(void *pvparam, size_t size);
extern void bts_comm_appl_raw_app_its_install_precallback(void *pvparam, size_t size);

#ifdef __cplusplus
}
#endif
#endif // bts_COMM_APPL_ITS_H__
