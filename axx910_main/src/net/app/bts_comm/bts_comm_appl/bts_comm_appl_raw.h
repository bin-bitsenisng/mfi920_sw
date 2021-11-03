/************************************************************************
| Project Name: bts_comm_appl_raw
|    File Name: bts_comm_appl_raw.h
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
#ifndef bts_COMM_APPL_RAW_H__
#define bts_COMM_APPL_RAW_H__


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
    uint32_t scanindex;
    f32_t pitch;
    f32_t yaw;
    f32_t roll;
    f32_t height;
    f32_t ax;
    f32_t ay;
    f32_t az;
    f64_t timestamp_s;
    f32_t cycletime_s;
} bts_comm_sysinfo_t;

typedef struct
{
    f32_t scanrate_fps;
    f32_t mod_memcopy;
    f32_t rsp;
    f32_t rsp_import;
    f32_t rsp_scaninit;
    f32_t rsp_pre;
    f32_t rsp_obj;
    f32_t rsp_trk;
    f32_t rsp_appmain;
    f32_t rsp_export;
    f32_t app;
} bts_comm_appl_performance_t;










/* declare extern global variables */
extern bts_comm_appl_performance_t bts_comm_appl_performance;
extern bts_comm_sysinfo_t bts_comm_sysinfo;



/* declare extern global functions */
extern void bts_comm_appl_raw_init(void);
extern void bts_comm_appl_pid_raw_packetbuild_and_send(void);

// callback
extern void bts_comm_appl_raw_sysinfo_precallback(void *pvparam, size_t size);
extern void bts_comm_appl_raw_cpu_time_precallback(void *pvparam, size_t size);




#ifdef __cplusplus
}
#endif
#endif // bts_COMM_APPL_RAW_H__
