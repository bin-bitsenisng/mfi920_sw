/* Copyright (c) 2018-2020 Analog Devices Inc. All rights reserved
*
* Clear BSD license
* -----------------
* Redistribution and use in source and binary forms, with or without
* modification, are permitted (subject to the limitations in the disclaimer
* below) provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice,
*   this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright notice,
*   this list of conditions and the following disclaimer in the documentation
*   and/or other materials provided with the distribution.
*
* * Neither the name of Analog Devices, Inc. nor the names of its contributors
*   may be used to endorse or promote products derived from this software
*   without specific prior written permission.
*
* NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
* THIS LICENSE.  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
* NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "adi_dmdriver.h"
#include "adar690x_fw.h"
#include "bts_application.h"
#include <string.h>
#include <stdio.h>
#include <mqueue.h>
#include <queue>
#include <thread>
#include <zmq.hpp>
#include "host_dev.h"
#include "../src/ADAR690x.h"
#include "../src/localdefs.h"
#include "../src/adar690x_regs.h"

#include "print_common.h"

#include "bts_comm.h"
#include "radar_cfg.h"

void bts_afi910_packet_send_loop(void);

extern std::queue<int32_t> g_inference_request_queue;
extern std::queue<int32_t> g_rsp_work_queue;
extern uint32_t g_rsp_working_flag;

extern mqd_t mqd;

zmq::context_t packet_send_context(1);
zmq::socket_t packet_send_socket(packet_send_context, zmq::socket_type::push);
zmq::message_t packet_send_request;
/***********************************************
* Example implementation of the measurement loop
* used in both DMA and builtin-MIMO examples.
************************************************
*/

void bts_afi910_burst_loop(bts_afi910_config_t * p)
{
    struct timeval startTime, endTime, curr_time;
    double diffTime, total_diffTime;

    adi_dm_err_t res;
    bool done;
    adi_dm_periodic_calibration_t periodic;
    int bp_idx = p->cur_bp_idx;
    uint32_t addr, val;
    int frame_cnt = 0;
    int rettt;
    int qval;

#if AUTO_SLEEP == 1
    adi_dm_num_t dm_num;
#endif
/*
    std::thread daq_memcpy_thread(bts_afi910_daq_memcpy_loop);
    usleep(100000);
    daq_memcpy_socket.connect(DAQ_MEMCPY_BIND_STRING);
*/
    std::thread packet_send_thread(bts_afi910_packet_send_loop);
    usleep(100000);
    packet_send_socket.connect(PACKET_SEND_BIND_STRING);

    memset(&periodic, 0, sizeof(periodic));

    /* Enable RAMPON on GPIO8 to detect end of bursts in the loop below. */
    res = adi_dm_PinMux(ADI_DM_MASTER, ADI_DM_GPIO8, 1, 1);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_PinMux", res, __FILE__, __LINE__);
    }
    res = adi_dm_PinMux(ADI_DM_MASTER, ADI_DM_GPIO10, 1, 1);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_PinMux", res, __FILE__, __LINE__);
    }

    addr = 0xF0020078;
    adi_dm_Read(ADI_DM_MASTER, addr, &val);
    printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_MASTER ,addr,val);
    val = val & 0xFFFF00FF;
    // val = val + 0x00008400;      // STAT1 High during Slope0
    val = val + 0x0000BE00;         // STAT1 High during whole mode;
    adi_dm_Write(ADI_DM_MASTER,addr,val);

#if DECIMATION_FILTER_ENABLE == 1    
    addr = 0xF0012048;
    adi_dm_Read(ADI_DM_MASTER, addr, &val);
    printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_MASTER ,addr,val);
    val = 0x00801900;
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS,addr,val);
#endif

    res = adi_dm_Write(ADI_DM_MASTER, ADI_ADAR690x_CFG_POWER_DOWN_AUTO_US, p->offtime_sleep_us);
#if AUTO_SLEEP == 1
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_POWER_DOWN_AUTO_US, p->offtime_sleep_us);
    if (res != ADI_DM_SUCCESS)
        return res;
#endif

#if BIST == 1
    /* run_checks:
     *   Must be true to run any BISTs as part of adi_dm_PeriodicCalibration.
     * run_rfpll_period_chk:
     *   Run the rfpll period bist as part of the periodic calibration.
     *   Requires adi_dm_WriteRfpllPeriod to have been called before burst.
     * run_power_checks
     *   Run bist power checks as part of the periodic calibration.
     *   Requires adi_dm_PowerDetectorMeasTask and adi_dm_WriteSyscalTx
     *   to have been called before burst.
     */
    periodic.run_checks = true;
    periodic.run_rfpll_period_chk = true;
    periodic.run_power_checks = true;

    /* Configure Power Measurement task for BISTs */
    res = adi_dm_PowerDetectorMeasTask(&p->bp[p->cur_bp_idx].pwrdet);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_PowerDetectorMeasTask", res, __FILE__, __LINE__);
    }
    /* Enable checks that configuration does not change by accident */
    res = adi_dm_LockConfig();
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_LockConfig", res, __FILE__, __LINE__);
    }
#endif

    /* Do whatever is needed to prepare the host side to receive the next burst. */
    platform_prep_host_for_trigger();
    platform_mipi_cap_start();
    usleep(500000);

    done = false;
    while (!done) {
        if(bp_idx == 0)
            gettimeofday(&startTime, NULL);
        
        /* Start measuring cycle time (time from start of one ramp busrt
         * to start of next).
         */
        platform_start_timer(p->cycle_time_us);

#if HARDWARE_TRIGGER == 1
        /* If using hardware triggers, application is ready
         * for TRIG input at this point.
         */
        // platform_hw_trigger();
#else
        /* Issue software trigger. */
        res = adi_dm_Trigger();
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_Trigger", res, __FILE__, __LINE__);
        }
#endif

        /* As the driver API is concerned with control this example
         * does not contain code to receive or process data.
         * Presumably that is happening in another thread.
         */

        /* Wait for burst completion signalled by RAMPON going low.
         * There may be better host side ways of detecting this,
         * such as noticing all data received.
         */
        // res = adi_dm_WaitGPIO(ADI_DM_MASTER, ADI_DM_GPIO8, false, TIMEOUT_NS);
        // if (res != ADI_DM_SUCCESS) {
        //     platform_error("adi_dm_WaitGPIO", res, __FILE__, __LINE__);
        // }

        /* Firmware may run a task on ramp completion indicated by GPIO11 going high.
         * The delay between GPIO8 going low and GPIO11 going high is about 1 us.
         * Wait sufficient time to avoid race conditions with other GPIO11 detection.
         */
        // printf("bp_idx : %d", bp_idx);
        
        switch(bp_idx)
        {
            case(0):
            {
                g_inference_request_queue.push(frame_cnt);
                //packet_send_socket.send(packet_send_request);
                //printf("inference requested time: %lf\n", curr_time.tv_sec + curr_time.tv_usec / 1000000.0);                
                platform_buff_change();
                platform_mipi_capture(bp_idx);
                break;
            }
            case(1):
            {
                platform_mipi_capture(bp_idx);
                break;
            }
            case(2):
            {
                platform_mipi_capture(bp_idx);
                break;
            }
            case(3):
            {
                platform_mipi_capture(bp_idx);
                //platform_gpu_reshape_data();
                while(g_rsp_working_flag == 1);
                g_rsp_work_queue.push(frame_cnt++);
                TRACE_SYS_MSG("\n===========================================================\nDAQ queue push ...\n");
                // platform_reshape_data();
                // platform_save_data(frame_cnt++);
                //rettt = mq_send(mqd, (char *)&qval,1,1);
                //usleep(2000);

                break;
            }
        }

#if MANUAL_SLEEP == 1
        /* tell part to power down */
        res = adi_dm_ManualSleep();
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_ManualSleep", res, __FILE__, __LINE__);
        }
        /* measure sleep time locally */
        adi_dm_DelayNS(p->offtime_sleep_us * 1000);
        /* tell part to power up */
        res = adi_dm_ManualWake();
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_ManualWake", res, __FILE__, __LINE__);
        }
#elif AUTO_SLEEP == 1
        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            /* wait for power down period indicated on GPIO11 */
            res = adi_dm_WaitGPIO(dm_num, ADI_DM_GPIO11, false, timeout_ns);
            if (res != ADI_DM_SUCCESS) {
                platform_error("adi_dm_WaitGPIO", res, __FILE__, __LINE__);
            }
            /* repeat in case first wait caught low before going high */
            res = adi_dm_WaitGPIO(dm_num, ADI_DM_GPIO11, false, timeout_ns);
            if (res != ADI_DM_SUCCESS) {
                platform_error("adi_dm_WaitGPIO", res, __FILE__, __LINE__);
            }
        }
#endif
        /* See if application wants to exit.
         * This depends upon some control plane logic
         * represented by this call.
         */
        done = bts_afi910_burst_loop_should_exit(p);
        if (!done) {
            /* Prepare for next burst */


            /* Possibly change burst profile,
             * which is another control plane decision.
             */
            int next_bp_idx = bts_afi190_get_next_burst_profile(p);
            if (next_bp_idx != bp_idx) {
                /* There are various thing that may need to be changed
                 * on changing burst profile. As this is a property of the
                 * application configuration it may be possible to organise
                 * things so the application does not need to make all these checks
                 * at runtime.
                 */
#if BIST == 1
                /* Disable checks that configuration is not changed by accident */
                res = adi_dm_UnlockConfig();
                if (res != ADI_DM_SUCCESS) {
                    platform_error("adi_dm_UnlockConfig", res, __FILE__, __LINE__);
                }
#endif

#if SPI_OPTIMIZED == 1
                bts_afi910_switch_config_spioptimize(p, next_bp_idx);
#else
                bts_afi910_switch_config(p, next_bp_idx);
#endif

#if BIST == 1
                /* Re-configure Power Measurement task for BISTs */
                res = adi_dm_PowerDetectorMeasTask(&p->bp[p->cur_bp_idx].pwrdet);
                if (res != ADI_DM_SUCCESS) {
                    platform_error("adi_dm_PowerDetectorMeasTask", res, __FILE__, __LINE__);
                }
                /* Enable checks that configuration does not change by accident */
                res = adi_dm_LockConfig();
                if (res != ADI_DM_SUCCESS) {
                    platform_error("adi_dm_LockConfig", res, __FILE__, __LINE__);
                }
#endif
                bp_idx = p->cur_bp_idx;
            }
            /* Run the recommended recalibrations. */
            // res = adi_dm_PeriodicCalibration(&periodic);
            // if (res != ADI_DM_SUCCESS) {
            //     platform_error("adi_dm_PeriodicCalibration", res, __FILE__, __LINE__);
            // }

            /* Do whatever is needed to prepare the host side to receive the next burst. */
            platform_prep_host_for_trigger();
            /* Wait until offtime is done and it is time for next trigger. */
            platform_wait_for_timer();
        }

        if(bp_idx == 0)
        {
            gettimeofday(&endTime, NULL);
            diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
            
            if((uint32_t)(diffTime*1000000) < RADAR_CFG_CYCLE_TIME_US) // hrtimer 고려해보기.
            {
                usleep((uint32_t)(RADAR_CFG_CYCLE_TIME_US - diffTime*1000000));
            }

            gettimeofday(&endTime, NULL);
            total_diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
            //TRACE_TIME_MSG("DAQ thread 1 cycle takes %lf ms\n", diffTime * 1000);
            //printf("Real / Total DAQ thread 1 cycle takes %lf ms\t%lf ms\n", diffTime * 1000, total_diffTime * 1000);
            //printf("DAQ thread 1 cycle takes %lf ms\n", diffTime * 1000);
            //printf("cycle_time 1 cycle takes %lf ms\n", total_diffTime * 1000);
        }        
    }

#if BIST == 1
    /* Disable checks that configuration is not changed by accident */
    res = adi_dm_UnlockConfig();
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_UnlockConfig", res, __FILE__, __LINE__);
    }
#endif
}

void bts_afi910_packet_send_loop(void)
{
    zmq::context_t packet_send_server_context(1);
    zmq::socket_t packet_send_server_socket(packet_send_server_context, zmq::socket_type::pull);
    zmq::message_t packet_send_cli_request;
    daq_memcpy_info daq_memcpy_info_inst;
            
    packet_send_server_socket.bind(PACKET_SEND_BIND_STRING);
    
    while(1)
    {
        packet_send_server_socket.recv(&packet_send_cli_request);
        bts_comm_event_send();
    }
}

// void bts_afi910_burst_loop_tak(bts_afi910_config_t * p)
// {
//     uint32_t temp_val, temp_addr;
//     adi_dm_err_t res;
//     bool done;
//     adi_dm_periodic_calibration_t periodic;
//     int bp_idx = p->cur_bp_idx;
//     uint32_t addr, val;
// #if AUTO_SLEEP == 1
//     adi_dm_num_t dm_num;
// #endif
//     int cnt_burst=0;
//     int chan = 0;

//     memset(&periodic, 0, sizeof(periodic));

//     /* Enable RAMPON on GPIO8 to detect end of bursts in the loop below. */
//     res = adi_dm_PinMux(ADI_DM_MASTER, ADI_DM_GPIO8, 1, 1);
//     if (res != ADI_DM_SUCCESS) {
//         platform_error("adi_dm_PinMux", res, __FILE__, __LINE__);
//     }
//     res = adi_dm_PinMux(ADI_DM_MASTER, ADI_DM_GPIO10, 1, 1);
//     if (res != ADI_DM_SUCCESS) {
//         platform_error("adi_dm_PinMux", res, __FILE__, __LINE__);
//     }

//     // GPIO10 -> RAMP_SLOPE0 ON
//     addr = 0xF0020078;
//     adi_dm_Read(ADI_DM_MASTER, addr, &val);
//     printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_MASTER ,addr,val);
//     val = val & 0xFFFF00FF;
//     val = val + 0x00008400;
//     adi_dm_Write(ADI_DM_MASTER,addr,val);

//     res = adi_dm_Write(ADI_DM_MASTER, ADI_ADAR690x_CFG_POWER_DOWN_AUTO_US, p->offtime_sleep_us);
// #if AUTO_SLEEP == 1
//     res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_POWER_DOWN_AUTO_US, p->offtime_sleep_us);
//     if (res != ADI_DM_SUCCESS)
//         return res;
// #endif

// #if BIST == 1
//     /* run_checks:
//      *   Must be true to run any BISTs as part of adi_dm_PeriodicCalibration.
//      * run_rfpll_period_chk:
//      *   Run the rfpll period bist as part of the periodic calibration.
//      *   Requires adi_dm_WriteRfpllPeriod to have been called before burst.
//      * run_power_checks
//      *   Run bist power checks as part of the periodic calibration.
//      *   Requires adi_dm_PowerDetectorMeasTask and adi_dm_WriteSyscalTx
//      *   to have been called before burst.
//      */
//     periodic.run_checks = true;
//     periodic.run_rfpll_period_chk = true;
//     periodic.run_power_checks = true;

//     /* Configure Power Measurement task for BISTs */
//     res = adi_dm_PowerDetectorMeasTask(&p->bp[p->cur_bp_idx].pwrdet);
//     if (res != ADI_DM_SUCCESS) {
//         platform_error("adi_dm_PowerDetectorMeasTask", res, __FILE__, __LINE__);
//     }
//     /* Enable checks that configuration does not change by accident */
//     res = adi_dm_LockConfig();
//     if (res != ADI_DM_SUCCESS) {
//         platform_error("adi_dm_LockConfig", res, __FILE__, __LINE__);
//     }
// #endif

//     /* Do whatever is needed to prepare the host side to receive the next burst. */
//     platform_prep_host_for_trigger();
//     platform_mipi_cap_start();
//     usleep(500000);

//     res = platform_fault_check();
//         if (res != ADI_DM_SUCCESS) {platform_error("FALUT_CHECK ERROR", res, __FILE__, __LINE__);}
//         else{printf("Error check : OK\n");}

//     // bts_rfic_read_udma_reg(2);
//     done = false;
//     adi_dm_Write(ADI_DM_ALL_DIGIMMICS, 0xF0020060, 1024);
//     test_rfic_udma(p);

//     res = platform_fault_check();
//         if (res != ADI_DM_SUCCESS) {platform_error("FALUT_CHECK ERROR", res, __FILE__, __LINE__);}
//         else{printf("Error check : OK\n");}

//     bts_rfic_read_mipi_reg(2);
//     bts_rfic_read_rfpll_reg(2);
//     bts_rfic_read_ramp_gen_reg(2);
//     bts_rfic_read_misc_reg(2);
//     bts_rfic_read_fw_cfg_reg(2);
//     bts_rfic_read_udma_reg(2);
//     bts_rfic_read_mipicsi2_reg(2);
//     bts_rfic_read_afe_reg(2);
    
//     uint8_t current_mode = 0;
//     while (!done) {
//         /* Start measuring cycle time (time from start of one ramp busrt
//          * to start of next).
//          */
        
//         platform_start_timer(p->cycle_time_us);

// #if HARDWARE_TRIGGER == 1
//         /* If using hardware triggers, application is ready
//          * for TRIG input at this point.
//          */
//         // platform_hw_trigger();
// #else
//         /* Issue software trigger. */
//         res = adi_dm_Trigger();
//         if (res != ADI_DM_SUCCESS) {
//             platform_error("adi_dm_Trigger", res, __FILE__, __LINE__);
//         }
// #endif

//         /* As the driver API is concerned with control this example
//          * does not contain code to receive or process data.
//          * Presumably that is happening in another thread.
//          */

//         /* Wait for burst completion signalled by RAMPON going low.
//          * There may be better host side ways of detecting this,
//          * such as noticing all data received.
//          */
//         // res = adi_dm_WaitGPIO(ADI_DM_MASTER, ADI_DM_GPIO8, false, TIMEOUT_NS);
//         // if (res != ADI_DM_SUCCESS) {
//         //     platform_error("adi_dm_WaitGPIO", res, __FILE__, __LINE__);
//         // }

//         /* Firmware may run a task on ramp completion indicated by GPIO11 going high.
//          * The delay between GPIO8 going low and GPIO11 going high is about 1 us.
//          * Wait sufficient time to avoid race conditions with other GPIO11 detection.
//          */
        
//         printf("<========================= %d burst ===========================>\n",cnt_burst);
//         printf("current_mode : %d\n", current_mode);

//         switch(current_mode)
//         {
//             case(0):
//             {   
                
//                 platform_mipi_capture(current_mode);
//                 usleep(200000);
//                 bts_rfic_udma_mode_change();
//                 usleep(100000);
//                 adi_dm_Write(ADI_DM_ALL_DIGIMMICS, 0xF0020060, 384);
//                 current_mode++;
//                 break;
//             }
//             case(1):
//             {

//                 platform_mipi_capture(current_mode);
//                 usleep(1000000);
//                 bts_rfic_udma_mode_change();
//                 usleep(100000);
//                 adi_dm_Write(ADI_DM_ALL_DIGIMMICS, 0xF0020060, 384);
//                 current_mode++;
//                 break;
//             }
//             case(2):
//             {
                
//                 platform_mipi_capture(current_mode);
//                 usleep(1000000);
//                 bts_rfic_udma_mode_change();
//                 usleep(100000);
//                 adi_dm_Write(ADI_DM_ALL_DIGIMMICS, 0xF0020060, 384);
//                 current_mode++;
//                 break;
//             }
//             case(3):
//             {
                
//                 platform_mipi_capture(current_mode);
//                 usleep(1000000);
//                 bts_rfic_udma_reload();
//                 usleep(1000000);
//                 adi_dm_Write(ADI_DM_ALL_DIGIMMICS, 0xF0020060, 1024);
//                 current_mode = 0;
//                 platform_save_data();
//                 cnt_burst++;
//                 break;
//             }
//         }
//     bts_rfic_read_mipi_reg(2);
//     bts_rfic_read_rfpll_reg(2);
//     bts_rfic_read_ramp_gen_reg(2);
//     bts_rfic_read_misc_reg(2);
//     bts_rfic_read_fw_cfg_reg(2);
//     bts_rfic_read_udma_reg(2);
//     bts_rfic_read_mipicsi2_reg(2);
//     bts_rfic_read_afe_reg(2);

//         res = platform_fault_check();
//         if (res != ADI_DM_SUCCESS) {
//             temp_addr = 0xF0005028;
//             adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, temp_addr, &temp_val);
//             printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,temp_addr,temp_val);
//             adi_dm_Read(ADI_DM_DIGIMMIC_SPI_SLAVE1, temp_addr, &temp_val);
//             printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_SPI_SLAVE1 ,temp_addr,temp_val);
//             adi_dm_Read(ADI_DM_DIGIMMIC_SPI_SLAVE2, temp_addr, &temp_val);
//             printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_SPI_SLAVE2 ,temp_addr,temp_val);
//             adi_dm_Read(ADI_DM_DIGIMMIC_SPI_SLAVE3, temp_addr, &temp_val);
//             printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_SPI_SLAVE3 ,temp_addr,temp_val);
//             platform_error("FALUT_CHECK ERROR", res, __FILE__, __LINE__);
//         }
//         else
//             printf("Error check : OK\n");
//             // temp_addr = 0xF0005180;
//             // adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADD   R, temp_addr, &temp_val);
//             // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,temp_addr,temp_val);
//             // adi_dm_Read(ADI_DM_DIGIMMIC_SPI_SLAVE1, temp_addr, &temp_val);
//             // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_SPI_SLAVE1 ,temp_addr,temp_val);
//             // adi_dm_Read(ADI_DM_DIGIMMIC_SPI_SLAVE2, temp_addr, &temp_val);
//             // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_SPI_SLAVE2 ,temp_addr,temp_val);
//             // adi_dm_Read(ADI_DM_DIGIMMIC_SPI_SLAVE3, temp_addr, &temp_val);
//             // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_SPI_SLAVE3 ,temp_addr,temp_val);

        
// #if MANUAL_SLEEP == 1
//         /* tell part to power down */
//         res = adi_dm_ManualSleep();
//         if (res != ADI_DM_SUCCESS) {
//             platform_error("adi_dm_ManualSleep", res, __FILE__, __LINE__);
//         }
//         /* measure sleep time locally */
//         adi_dm_DelayNS(p->offtime_sleep_us * 1000);
//         /* tell part to power up */
//         res = adi_dm_ManualWake();
//         if (res != ADI_DM_SUCCESS) {
//             platform_error("adi_dm_ManualWake", res, __FILE__, __LINE__);
//         }
// #elif AUTO_SLEEP == 1
//         for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
//             /* wait for power down period indicated on GPIO11 */
//             res = adi_dm_WaitGPIO(dm_num, ADI_DM_GPIO11, false, timeout_ns);
//             if (res != ADI_DM_SUCCESS) {
//                 platform_error("adi_dm_WaitGPIO", res, __FILE__, __LINE__);
//             }
//             /* repeat in case first wait caught low before going high */
//             res = adi_dm_WaitGPIO(dm_num, ADI_DM_GPIO11, false, timeout_ns);
//             if (res != ADI_DM_SUCCESS) {
//                 platform_error("adi_dm_WaitGPIO", res, __FILE__, __LINE__);
//             }
//         }
// #endif

//         /* See if application wants to exit.
//          * This depends upon some control plane logic
//          * represented by this call.
//          */
//         // done = bts_afi910_burst_loop_should_exit(p);
//         // if (!done) {
//             /* Prepare for next burst */

//             /* Possibly change burst profile,
//              * which is another control plane decision.
//              */
//             // int next_bp_idx = bts_afi190_get_next_burst_profile(p);
//             // if (next_bp_idx != bp_idx) {
//                 /* There are various thing that may need to be changed
//                  * on changing burst profile. As this is a property of the
//                  * application configuration it may be possible to organise
//                  * things so the application does not need to make all these checks
//                  * at runtime.
//                  */
// #if BIST == 1
//                 /* Disable checks that configuration is not changed by accident */
//                 res = adi_dm_UnlockConfig();
//                 if (res != ADI_DM_SUCCESS) {
//                     platform_error("adi_dm_UnlockConfig", res, __FILE__, __LINE__);
//                 }
// #endif
//                 // bts_afi910_switch_config(p, next_bp_idx);
// #if BIST == 1
//                 /* Re-configure Power Measurement task for BISTs */
//                 res = adi_dm_PowerDetectorMeasTask(&p->bp[p->cur_bp_idx].pwrdet);
//                 if (res != ADI_DM_SUCCESS) {
//                     platform_error("adi_dm_PowerDetectorMeasTask", res, __FILE__, __LINE__);
//                 }
//                 /* Enable checks that configuration does not change by accident */
//                 res = adi_dm_LockConfig();
//                 if (res != ADI_DM_SUCCESS) {
//                     platform_error("adi_dm_LockConfig", res, __FILE__, __LINE__);
//                 }
// #endif
//                 // bp_idx = p->cur_bp_idx;
//             // }
//             /* Run the recommended recalibrations. */
//             // res = adi_dm_PeriodicCalibration(&periodic);
//             // if (res != ADI_DM_SUCCESS) {
//             //     platform_error("adi_dm_PeriodicCalibration", res, __FILE__, __LINE__);
//             // }

//             /* Do whatever is needed to prepare the host side to receive the next burst. */
//             platform_prep_host_for_trigger();
//             /* Wait until offtime is done and it is time for next trigger. */
//             platform_wait_for_timer();
//         // }
//     }

// #if BIST == 1
//     /* Disable checks that configuration is not changed by accident */
//     res = adi_dm_UnlockConfig();
//     if (res != ADI_DM_SUCCESS) {
//         platform_error("adi_dm_UnlockConfig", res, __FILE__, __LINE__);
//     }
// #endif
// }

void bts_afi910_switch_config_orig(bts_afi910_config_t * p, uint32_t next_bp_idx)
{
    adi_dm_err_t res;
    uint32_t bp_idx = p->cur_bp_idx;

    if (memcmp(&p->bp[next_bp_idx].rfpll, &p->bp[bp_idx].rfpll, sizeof(adi_dm_rfpll_reconfig_t)) != 0) {
        /* If ramp start frequency, or ramp bandwidth parameter change,
         * perform firmware recalibration.
         */
        res = adi_dm_RfpllReconfig(&p->bp[next_bp_idx].rfpll);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_RfpllReconfig", res, __FILE__, __LINE__);
        }
    }
    if (memcmp(&p->bp[next_bp_idx].dma.ramp_config, &p->bp[bp_idx].dma.ramp_config, sizeof(adi_dm_ramp_config_t)) == 0) {
        /* RAMP_CONFIG registers do not have to change. So just set the DMA
         * Ideally arrange that this is all that is needed as it only takes two SPI writes.
         */
        res = adi_dm_SelectBurstProfile(p->bp[next_bp_idx].dma.bpid);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_SelectBurstProfile", res, __FILE__, __LINE__);
        }
    } else {
        /* RAMP_CONFIG registers do need to change.
         * This call updates the registers as well as changing the burst profile.
         */
        res = adi_dm_DmaRampSetup(&p->bp[next_bp_idx].dma);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_DmaRampSetup", res, __FILE__, __LINE__);
        }
    }
    if (memcmp(&p->bp[next_bp_idx].afe, &p->bp[bp_idx].afe, sizeof(adi_dm_afe_setup_t)) != 0) {
        /* AFE settings are to change */
        res = adi_dm_AfeSetup(&p->bp[next_bp_idx].afe);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_AfeSetup", res, __FILE__, __LINE__);
        }
    }
    if (memcmp(&p->bp[next_bp_idx].tx, &p->bp[bp_idx].tx, sizeof(adi_dm_tx_setup_t)) != 0) {
        /* TX settings are to change. */
        res = adi_dm_TxSetup(&p->bp[next_bp_idx].tx);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_AfeSetup", res, __FILE__, __LINE__);
        }
    }
#if BIST == 1
    if (memcmp(&p->bp[next_bp_idx].rfpllperiod, &p->bp[bp_idx].rfpllperiod, sizeof(adi_dm_write_rfpll_period_t)) != 0) {
        /* RFPLL period estimate has changed. */
        res = adi_dm_WriteRfpllPeriod(&p->bp[next_bp_idx].rfpllperiod);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_WriteRfpllPeriod", res, __FILE__, __LINE__);
        }
    }
    if (memcmp(&p->bp[next_bp_idx].syscaltx, &p->bp[bp_idx].syscaltx, sizeof(p->bp[bp_idx].syscaltx)) != 0) {
        /* New TX system calibration values needed for this usecase. */
        res = adi_dm_WriteSysCalTx(p->bp[next_bp_idx].syscaltx);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_WriteSysCalTx", res, __FILE__, __LINE__);
        }
    }
#endif
    p->cur_bp_idx = next_bp_idx;
    platform_profile_change(next_bp_idx);
    platform_mipi_vc_id_change(next_bp_idx);
}

bool bts_afi910_burst_loop_should_exit(bts_afi910_config_t * p)
{
    /* p->burst_pattern is a string of burst numbers */
    // printf("burst counter : %d, burst_pattern : %d, repeat_counter : %d\n",p->counter,p->burst_pattern[p->counter]-'0', p->repeat_counter);
    bool res = false;
    p->counter++;
    if (p->burst_pattern[p->counter] == 0) {            // 0 means NULL
        p->counter = 0;
        p->repeat_counter++;
        if(p->pattern_repeat_count != 0){
            if (p->repeat_counter >= p->pattern_repeat_count) {
                res = true;
            }
        }
    }
    return res;
}

int bts_afi190_get_next_burst_profile(bts_afi910_config_t * p)
{
    /* p->burst_pattern is a string of burst numbers in ASCII */
    return p->burst_pattern[p->counter] - '0';
}


adi_dm_err_t bts_dm_SelectBurstProfile(uint32_t bpid)
{
    adi_dm_err_t res;

    // printf("-->> Entering function adi_dm_SelectBurstProfile\n");
    /* the burst profile 'identifier' is just the channel src_ptr */
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, DMA_RAMPGEN_CHAN_SRC_PTR, bpid);
    if (res != ADI_DM_SUCCESS)
        return res;
    /* having changed the pointer, load primary channel control and then RAMPGEN with a software DMA request */
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 3 << DMA_RAMPGEN_CHAN_NO);
    if (res != ADI_DM_SUCCESS)
        return res;
    // printf("-->> Exiting function adi_dm_SelectBurstProfile\b");
    return ADI_DM_SUCCESS;
}



void bts_afi910_switch_config(bts_afi910_config_t * p, uint32_t next_bp_idx)
{
    adi_dm_err_t res;
    uint32_t bp_idx = p->cur_bp_idx;

    if (memcmp(&p->bp[next_bp_idx].rfpll, &p->bp[bp_idx].rfpll, sizeof(adi_dm_rfpll_reconfig_t)) != 0) {
        /* If ramp start frequency, or ramp bandwidth parameter change,
         * perform firmware recalibration.
         */
        res = adi_dm_RfpllReconfig(&p->bp[next_bp_idx].rfpll);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_RfpllReconfig", res, __FILE__, __LINE__);
        }
    }
    if (memcmp(&p->bp[next_bp_idx].dma.ramp_config, &p->bp[bp_idx].dma.ramp_config, sizeof(adi_dm_ramp_config_t)) == 0) {
        /* RAMP_CONFIG registers do not have to change. So just set the DMA
         * Ideally arrange that this is all that is needed as it only takes two SPI writes.
         */
        res = bts_dm_SelectBurstProfile(p->bp[next_bp_idx].dma.bpid);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_SelectBurstProfile", res, __FILE__, __LINE__);
        }
    } else {
        /* RAMP_CONFIG registers do need to change.
         * This call updates the registers as well as changing the burst profile.
         */
        res = bts_dm_DmaRampSetup(&p->bp[next_bp_idx].dma);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_DmaRampSetup", res, __FILE__, __LINE__);
        }
    }
    // if (memcmp(&p->bp[next_bp_idx].afe, &p->bp[bp_idx].afe, sizeof(adi_dm_afe_setup_t)) != 0) {
    //     /* AFE settings are to change */
    //     res = adi_dm_AfeSetup(&p->bp[next_bp_idx].afe);
    //     if (res != ADI_DM_SUCCESS) {
    //         platform_error("adi_dm_AfeSetup", res, __FILE__, __LINE__);
    //     }
    // }
    // if (memcmp(&p->bp[next_bp_idx].tx, &p->bp[bp_idx].tx, sizeof(adi_dm_tx_setup_t)) != 0) {
    //     /* TX settings are to change. */
    //     res = adi_dm_TxSetup(&p->bp[next_bp_idx].tx);
    //     if (res != ADI_DM_SUCCESS) {
    //         platform_error("adi_dm_AfeSetup", res, __FILE__, __LINE__);
    //     }
    // }

    p->cur_bp_idx = next_bp_idx;
    platform_profile_change(next_bp_idx);
    platform_mipi_vc_id_change(next_bp_idx);
}

void bts_afi910_switch_config_spioptimize(bts_afi910_config_t * p, uint32_t next_bp_idx)
{
    adi_dm_err_t res;
    uint32_t bp_idx = p->cur_bp_idx;

    // if (memcmp(&p->bp[next_bp_idx].rfpll, &p->bp[bp_idx].rfpll, sizeof(adi_dm_rfpll_reconfig_t)) != 0) {
    //     /* If ramp start frequency, or ramp bandwidth parameter change,
    //      * perform firmware recalibration.
    //      */
    //     //printf("[SYKANG] 11111111 \n");
    //     res = adi_dm_RfpllReconfig(&p->bp[next_bp_idx].rfpll);
    //     if (res != ADI_DM_SUCCESS) {
    //         platform_error("adi_dm_RfpllReconfig", res, __FILE__, __LINE__);
    //     }
    // }

    adi_dm_SPI_optimize(2, next_bp_idx);
    //usleep(1000);
    
    
    if (memcmp(&p->bp[next_bp_idx].dma.ramp_config, &p->bp[bp_idx].dma.ramp_config, sizeof(adi_dm_ramp_config_t)) == 0) {
        /* RAMP_CONFIG registers do not have to change. So just set the DMA
         * Ideally arrange that this is all that is needed as it only takes two SPI writes.
         */
        // res = bts_dm_SelectBurstProfile(p->bp[next_bp_idx].dma.bpid);
        // if (res != ADI_DM_SUCCESS) {
        //     platform_error("adi_dm_SelectBurstProfile", res, __FILE__, __LINE__);
        // }
        //printf("[SYKANG] CALL next_bp_idx = %d \n", next_bp_idx);
        adi_dm_SPI_optimize(7, next_bp_idx);

        p->cur_bp_idx = next_bp_idx;
        platform_profile_change(next_bp_idx);
        //platform_mipi_vc_id_change(next_bp_idx);
        adi_dm_SPI_VID_optimize(7,next_bp_idx);
    } else {
        /* RAMP_CONFIG registers do need to change.
         * This call updates the registers as well as changing the burst profile.
         */
        res = bts_dm_DmaRampSetup(&p->bp[next_bp_idx].dma);
        
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_DmaRampSetup", res, __FILE__, __LINE__);
        }
        //adi_dm_SPI_optimize(7, next_bp_idx);
        
        p->cur_bp_idx = next_bp_idx;
        platform_profile_change(next_bp_idx);
        platform_mipi_vc_id_change(next_bp_idx);
        //adi_dm_SPI_VID_optimize(7,next_bp_idx);
    }
    //usleep(1);
    //adi_dm_SPI_optimize(7, next_bp_idx);

    // p->cur_bp_idx = next_bp_idx;
    // platform_profile_change(next_bp_idx);
    // platform_mipi_vc_id_change(next_bp_idx);
    //adi_dm_SPI_VID_optimize(7,next_bp_idx);
}