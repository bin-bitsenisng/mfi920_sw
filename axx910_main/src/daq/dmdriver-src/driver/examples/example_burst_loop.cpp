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
#include "application.h"
#include <string.h>
#include <stdio.h>


/***********************************************
* Example implementation of the measurement loop
* used in both DMA and builtin-MIMO examples.
************************************************
*/

void example_burst_loop(example_config_t * p)
{
    adi_dm_err_t res;
    bool done;
    adi_dm_periodic_calibration_t periodic;
    int bp_idx = p->cur_bp_idx;
#if AUTO_SLEEP == 1
    adi_dm_num_t dm_num;
#endif

    memset(&periodic, 0, sizeof(periodic));

    /* Enable RAMPON on GPIO8 to detect end of bursts in the loop below. */
    res = adi_dm_PinMux(ADI_DM_MASTER, ADI_DM_GPIO8, 1, 1);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_PinMux", res, __FILE__, __LINE__);
    }
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

    done = false;
    while (!done) {
        /* Start measuring cycle time (time from start of one ramp busrt
         * to start of next).
         */
        platform_start_timer(p->cycle_time_us);

#if HARDWARE_TRIGGER == 1
        /* If using hardware triggers, application is ready
         * for TRIG input at this point.
         */
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
        adi_dm_DelayNS(500000000);
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
        done = burst_loop_should_exit(p);
        if (!done) {
            /* Prepare for next burst */

            /* Possibly change burst profile,
             * which is another control plane decision.
             */
            int next_bp_idx = get_next_burst_profile(p);
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
                // example_switch_config(p, next_bp_idx);
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
    }

#if BIST == 1
    /* Disable checks that configuration is not changed by accident */
    res = adi_dm_UnlockConfig();
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_UnlockConfig", res, __FILE__, __LINE__);
    }
#endif
}

void example_switch_config(example_config_t * p, uint32_t next_bp_idx)
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
}

bool burst_loop_should_exit(example_config_t * p)
{
    /* p->burst_pattern is a string of burst numbers */
    printf("burst counter : %d, burst_pattern : %d, repeat_counter : %d\n",p->counter,p->burst_pattern[p->counter]-'0', p->repeat_counter);
    bool res = false;
    p->counter++;
    if (p->burst_pattern[p->counter] == 0) {            // 0 means NULL
        p->counter = 0;
        p->repeat_counter++;
        if (p->repeat_counter >= p->pattern_repeat_count) {
            res = true;
        }
    }
    return res;
}

int get_next_burst_profile(example_config_t * p)
{
    /* p->burst_pattern is a string of burst numbers in ASCII */
    return p->burst_pattern[p->counter] - '0';
}
