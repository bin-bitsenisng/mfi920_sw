#include <thread>
#include <mutex>
#include <queue>

#include "rsp_thread.h"
#include "net_thread.h"
#include "net_thread_cfg.h"
#include "print_common.h"
#include "rsp_main.h"
#include "device_ctrl.h"
#include "timestamp.h"

#include "host_dev.h"
#include "reshape.cuh"
#include "Pre_Main.h"
#include "Sp_Parameters.h"

#include "bts_comm.h"

#include <sys/time.h>

extern host_device_handle_t * host_dev_p;

extern std::queue<int32_t> g_rsp_work_queue;
extern std::queue<int32_t> g_trk_work_queue;
extern uint32_t g_rsp_working_flag;
f32_t rsp_cycletime_s;
os_time_t rsp_timestamp_us;
extern int16_t* daq_rm_data;
extern int16_t* daq_lr_data;
extern int16_t* daq_mr_data;
extern int16_t* daq_sr_data;

extern uint64_t daq_scanindex;

static void CopyRadarData(int16_t* daq_rm_data, int16_t* daq_lr_data, int16_t* daq_mr_data, int16_t* daq_sr_data);

void StartRSPthread(void)
{
    
}

void ServiceRSP(MainArgument* main_argument)
{
    struct timeval startTime, endTime;
    double diffTime;

    TRACE_SYS_MSG("RSP Thread starts.\n");

    rsp_timestamp_us = 0;

	while(1)
	{
        if(!g_rsp_work_queue.empty())
        {
            if(g_rsp_work_queue.size() > 1)
            {
                TRACE_ERR_MSG("[WARNING] rsp queue size is over 1.. it is %d\n", g_rsp_work_queue.size());
            }
            TRACE_SYS_MSG("RSP queue pop ...\n");
            g_rsp_work_queue.pop();
            g_rsp_working_flag = 1;
            
            if(!strcmp(main_argument->execution_mode, SIMULATION_MODE))
            {
                CopyRadarData(daq_rm_data, daq_lr_data, daq_mr_data, daq_sr_data);
            }
            
            gettimeofday(&startTime, NULL);
            rsp_cycletime_s = (f32_t)((f64_t)(GetTimeStamp() - rsp_timestamp_us) / 1000000.0f);
            rsp_timestamp_us = GetTimeStamp();
            
            //bts_comm_event_send();
            if(!strcmp(main_argument->execution_mode, REALTIME_MODE))
            {
                reshape_raw_data(host_dev_p->data_buf[host_dev_p->buf_num], gRM_PreData.s16adcData, gLR_PreData.s16adcData, gMR_PreData.s16adcData, gSR_PreData.s16adcData);
            }
            
            MainRSP();
            
            daq_scanindex++;

            //bts_comm_event_build(0, NULL);

            gettimeofday(&endTime, NULL);
            diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
            //TRACE_TIME_MSG("RSP thread 1 cycle takes %lf ms\n", diffTime*1000);
            printf("RSP thread 1 cycle takes %lf ms\n", diffTime*1000);

            g_rsp_working_flag = 0;

            g_trk_work_queue.push(daq_scanindex);
        }

        usleep(1000);
	}

	TRACE_SYS_MSG("RSP Thread Finished.\n");
}

static void CopyRadarData(int16_t* daq_rm_data, int16_t* daq_lr_data, int16_t* daq_mr_data, int16_t* daq_sr_data)
{
	//memcpy(gPreData.s16adcData, daq_data, 2*SP_NUM_TX*SP_NUM_RX*SP_NUM_CHIRPS*SP_NUM_SAMPLES);
    memcpy(gRM_PreData.s16adcData, daq_rm_data, 2*SP_RM_NUM_TX*SP_NUM_RX*SP_RM_NUM_CHIRPS*SP_RM_NUM_SAMPLES);
    memcpy(gLR_PreData.s16adcData, daq_lr_data, 2*SP_NUM_TX*SP_NUM_RX*SP_NUM_CHIRPS*SP_NUM_SAMPLES);
    memcpy(gMR_PreData.s16adcData, daq_mr_data, 2*SP_NUM_TX*SP_NUM_RX*SP_NUM_CHIRPS*SP_NUM_SAMPLES);
    memcpy(gSR_PreData.s16adcData, daq_sr_data, 2*SP_NUM_TX*SP_NUM_RX*SP_NUM_CHIRPS*SP_NUM_SAMPLES);
}