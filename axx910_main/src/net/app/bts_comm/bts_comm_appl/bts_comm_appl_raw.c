/************************************************************************
| Project Name: bts_comm_appl_raw
|    File Name: bts_comm_appl_raw.c
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

/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"
#include <string.h>

/* include system driver header */
//#include "drivers.h"
#include "krs_lib.h"

/* include system bsp header */
#include "os.h"

/* include system application header */
#include "sys_param.h"

/* final include module header */
#include "bts_comm.h"
#include "bts_comm_appl.h"
#include "bts_comm_cmd.h"
#include "bts_comm_packet.h"
#include "bts_comm_status.h"
//#include "rsp_task.h"
//#include "rsm_task.h"
#include "daq_thread.h"
#include "imu.h"

#include "bts_comm_appl_raw.h"
/* declare global variables */
bts_comm_appl_performance_t bts_comm_appl_performance;
bts_comm_sysinfo_t bts_comm_sysinfo;


/* declare static variables */




extern sys_param_pid9_vf_data_t vf_data_out;
extern f32_t schd_task_scanframerate;
/* static function prototypes */

/* functions */

// object


/******************************************************************************
 * function name : bts_comm_appl_raw_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return void description
 * modification date : 2018.06.26
 *****************************************************************************/
void bts_comm_appl_raw_init(void)
{
    krs_memclearitem(bts_comm_sysinfo);
    krs_memclearitem(bts_comm_appl_performance);
    //krs_memclearitem(xadc_drv_cpu_electrical_info);
}

/******************************************************************************
 * function name : bts_comm_appl_pid_raw_packetbuild_and_send
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return void description
 * modification date : 2018.07.27
 *****************************************************************************/
void bts_comm_appl_pid_raw_packetbuild_and_send(void)
{
    static int32_t i;
    int32_t pidraw;
    int32_t packetsize;

    pidraw = bts_comm_pid_raw;
    for(i=0;i<bts_comm_pid_max;i++)
    {
        if(bts_comm_daqinfo[i].pidtype >= bts_comm_pidtype_end) break;
        if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[i])==retOK)
        {
			if((bts_comm_daqinfo[i].pidtype == bts_comm_pidtype_raw) && (bts_comm_daqinfo[i].start != 0))
			{
				if(bts_comm_daqinfo[i].pid >= bts_comm_pid_raw )
				{
					if(bts_comm_daqinfo[i].precallback != NULL)
					{
						bts_comm_daqinfo[i].precallback(bts_comm_daqinfo[i].pvParam, bts_comm_daqinfo[i].bytesize);
					}
					packetsize = bts_comm_add_dto_msg(bts_comm_daqinfo[i].bytesize, pidraw, 0, bts_comm_daqinfo[i].pvParam);


					if(bts_comm_daqinfo[i].postcallback != NULL)
					{
						bts_comm_daqinfo[i].postcallback(bts_comm_daqinfo[i].pvParam, bts_comm_daqinfo[i].bytesize);
					}
			#if bts_COMM_APPL_PACKETSIZE_DEBUG == 1
					krs_log("pid%02X packetsize : %d\n\r", bts_comm_pid_raw + pidraw, packetsize);
			#else
					krs_unused_param(packetsize);
			#endif
					pidraw++;
				}
			}
        }
    }
}





/******************************************************************************
 * function name : bts_comm_appl_raw_sysinfo_precallback
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *pvparam description
 * \param1 size description
 * \return void description
 * modification date : 2018.07.30
 *****************************************************************************/
void bts_comm_appl_raw_sysinfo_precallback(void *pvparam, size_t size)
{
    bts_comm_sysinfo_t *p = (bts_comm_sysinfo_t *)pvparam;

    p->scanindex = (uint32_t)daq_scanindex;
    p->pitch = imu_data.pitch;
    p->yaw = imu_data.yaw;
    p->roll = imu_data.roll;
    p->height = imu_data.altidude_m;
    p->ax = imu_data.ax;
    p->ay = imu_data.ay;
    p->az = imu_data.az;
    p->cycletime_s = rsp_cycletime_s;
    p->timestamp_s = ((f64_t)rsp_timestamp_us)/1000000.0f;
}




/******************************************************************************
 * function name : bts_comm_appl_raw_cpu_time_precallback
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *pvparam description
 * \param1 size description
 * \return void description
 * modification date : 2018.07.30
 *****************************************************************************/
void bts_comm_appl_raw_cpu_time_precallback(void *pvparam, size_t size)
{
    bts_comm_appl_performance_t *pv = (bts_comm_appl_performance_t *)pvparam;
/*
    pv->scanrate_fps = schd_task_scanframerate;
    pv->mod_memcopy = timeit_mod_memcopy.f32msec;
    pv->rsp = timeit_rsp.f32msec;
    pv->rsp_import = timeit_rsp_import.f32msec;
    pv->rsp_scaninit = timeit_rsp_scaninit.f32msec;
    pv->rsp_pre = timeit_rsp_pre.f32msec;
    pv->rsp_obj = timeit_rsp_obj.f32msec;
    pv->rsp_trk = timeit_rsp_trk.f32msec;
    pv->rsp_appmain = timeit_rsp_appmain.f32msec;
    pv->rsp_export = timeit_rsp_export.f32msec;
    pv->app = timeit_app.f32msec;*/
}



/* end of file */
