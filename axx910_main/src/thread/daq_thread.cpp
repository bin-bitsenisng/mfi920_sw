#include <thread>
#include <mutex>
#include <queue>
#include <unistd.h>
#include "opencv2/opencv.hpp"

#include "daq_thread.h"
#include "daq_thread_cfg.h"
#include "print_common.h"
#include "device_ctrl.h"
#include "main_argument.h"
#include "hdf5_ctrl.h"

#include "rsp_main.h"
#include "Sp_Main.h"

#include "adi_dmdriver.h"
#include "bts_application.h"
#include "host_dev.h"
#include <mqueue.h>

extern std::mutex g_mutex_for_radar_raw_data;
extern std::queue<int32_t> g_rsp_work_queue;

extern Cuda_PreData_t gPreData;

int16_t* daq_rm_data;
int16_t* daq_lr_data;
int16_t* daq_mr_data;
int16_t* daq_sr_data;

uint64_t daq_scanindex = 0;

host_device_handle_t host_dev;
host_device_handle_t * host_dev_p;
mqd_t mqd;
extern uint8_t example_syscal_rx[ADI_DM_NUM_DIGIMMIC][ADI_DM_SYSCAL_RX_SIZE];
extern uint8_t example_syscal_tx[NUM_BURST_PROFILES][ADI_DM_NUM_DIGIMMIC][ADI_DM_SYSCAL_TX_SIZE];

static void RearrangeRadarRawData(cv::Mat daq_data);
static void RearrangeH5RadarSimData(void);

extern DEVICE_LIST devices;

void StartDAQthread(void)
{
	//std::thread daq_thread(ServiceDAQ); 

	//daq_thread.join();
}

void ServiceDAQ(MainArgument* main_argument)
{
	bts_afi910_config_t afi910_configs;
	adi_dm_err_t res;
	int32_t daq_counter = 0;

	host_dev_p = &host_dev;

	TRACE_SYS_MSG("DAQ Thread starts.\n");
	
	bts_afi910_init(&afi910_configs);

#if BIST == 1
    /* 1b: Load system calibration data from on board non-volatile memory
     */
    /* This example assumes that the example_syscal_rx, example_syscal_tx variables
     * contain a copy of the t0 measurement data obtained during system calibration.
     * as can be seen in the example_syscal.c file.
     * This data is board specific and should come from non-volatile memory on the board
     * written during system calibration whe the board comes off the production line.
     * For the purposes of these examples the variables written by the example_syscal example
     * are used, assuming example_syscal has run before this example.
     */
    /* Copy t0 data from variables set by example_syscal */
    memcpy(afi910_configs.syscalrx, example_syscal_rx, sizeof(afi910_configs.syscalrx));
    for (ii = 0; ii < afi910_configs.num_burst_profiles; ii++) {
        memcpy(afi910_configs.bp[ii].syscaltx, example_syscal_tx[ii], sizeof(afi910_configs.bp[ii].syscaltx));
    }

    /* 1c: Write system calibration  data to the devices.
     * Rx t0 data only needs to be written hre.
     * Tx t0 data is written each time the burst profile changes.
     */
    res = adi_dm_WriteSysCalRx(afi910_configs.syscalrx);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_WriteSysCalRx", res, __FILE__, __LINE__);
    }

    res = adi_dm_WriteSysCalTx(afi910_configs.bp[afi910_configs.cur_bp_idx].syscaltx);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_WriteSysCalTx", res, __FILE__, __LINE__);
    }
#endif
	
	if(!strcmp(main_argument->execution_mode, SIMULATION_MODE))
	{
		daq_rm_data = (uint16_t*)malloc(sizeof(uint16_t) * SP_RM_NUM_TX * SP_NUM_RX * SP_RM_NUM_CHIRPS * SP_RM_NUM_SAMPLES);
		daq_lr_data = (uint16_t*)malloc(sizeof(uint16_t) * SP_NUM_TX * SP_NUM_RX * SP_NUM_CHIRPS * SP_NUM_SAMPLES);
		daq_mr_data = (uint16_t*)malloc(sizeof(uint16_t) * SP_NUM_TX * SP_NUM_RX * SP_NUM_CHIRPS * SP_NUM_SAMPLES);
		daq_sr_data = (uint16_t*)malloc(sizeof(uint16_t) * SP_NUM_TX * SP_NUM_RX * SP_NUM_CHIRPS * SP_NUM_SAMPLES);

		while(1)
		{
			if(daq_scanindex + 1 > main_argument->final_scan_num)
			{
				TRACE_SYS_MSG("Simulation Finished.\n");
				
				free(daq_rm_data);
				free(daq_lr_data);
				free(daq_mr_data);
				free(daq_sr_data);

				return;
			}
			else
			{
				//TRACE_SYS_MSG("Simulation Scan Number: %d\n", daq_scanindex + 1);
				printf("\n\nSimulation Scan Number: %d\n", daq_scanindex + 1);
				ReadScanGroup(main_argument->sim_input_file_name, daq_scanindex + 1);
				RearrangeH5RadarSimData();
				g_rsp_work_queue.push(daq_counter++);
				TRACE_SYS_MSG("DAQ queue push ...\n");
				sleep(1);
				//sleep(3);
			}			
			//daq_scanindex++;
		}
	}
	else
	{
		bts_afi910_burst_loop(&afi910_configs);
		/*
		CaptureRadar(&(devices.radar_device));
		//daq_rm_data;
		//daq_lr_data;
		//daq_mr_data;
		//daq_sr_data; => dobble buffering 해서 데이터 저장.
		usleep(150000); // original target 100 ms

		
		//g_mutex_for_radar_raw_data.lock();
		//RearrangeRadarRawData(devices.radar_device.radar_raw_data);
		//g_mutex_for_radar_raw_data.unlock();
		
		g_rsp_work_queue.push(daq_counter++);
		TRACE_SYS_MSG("DAQ queue push ...\n");
		*/
	}
	
	/* Power down the device. */
    res = adi_dm_PowerDown();
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_PowerDown", res, __FILE__, __LINE__);
    }

    /* Release any resource used by the diver. */
    adi_dm_Log("---> Exiting example_dma_ramp");
    adi_dm_FiniDriver();

	TRACE_SYS_MSG("DAQ Thread Finished.\n");
}

static void RearrangeH5RadarSimData(void)
{
	memcpy(daq_rm_data, Sim_RM_TimeData, 2 * SP_RM_NUM_TX * SP_NUM_RX * SP_RM_NUM_CHIRPS * SP_RM_NUM_SAMPLES);
	memcpy(daq_lr_data, Sim_LR_TimeData, 2 * SP_NUM_TX * SP_NUM_RX * SP_NUM_CHIRPS * SP_NUM_SAMPLES);
	memcpy(daq_mr_data, Sim_MR_TimeData, 2 * SP_NUM_TX * SP_NUM_RX * SP_NUM_CHIRPS * SP_NUM_SAMPLES);
	memcpy(daq_sr_data, Sim_SR_TimeData, 2 * SP_NUM_TX * SP_NUM_RX * SP_NUM_CHIRPS * SP_NUM_SAMPLES);
}
