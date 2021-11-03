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
#include <math.h>
#include <stdio.h>

static void burst(example_config_t * p);

/***********************************************
* Example of t0 end-of-line system calibration.
************************************************
* This example illustrates the process for 'end
* of line system calibration' to collect t0 (time zero)
* measurements at the end of the systems production
* line.
*/

/* variables in which t0 measurements are saved.
 * example_burst_loop.c reads them from these vars.
 */
uint8_t example_syscal_rx[ADI_DM_NUM_DIGIMMIC][ADI_DM_SYSCAL_RX_SIZE];
uint8_t example_syscal_tx[NUM_BURST_PROFILES][ADI_DM_NUM_DIGIMMIC][ADI_DM_SYSCAL_TX_SIZE];

/* variables defined in driver to control whether the t0 measurements are taken */

extern bool adi_dm_call_fw_rxchain_diag_chk;    /* BIST15: rx chain diagnostic check */
extern bool adi_dm_call_fw_tx_pwr_chk;  /* BIST19: Tx output transmit power monitor */
extern bool adi_dm_call_fw_pwr_det_rat_chk;     /* BIST44: power detector rationality check */
extern bool adi_dm_call_fw_tx_output_load_monitor_chk;  /* BIST54: Tx output load monitor check */

void example_syscal(void)
{
    example_config_t configs;
    adi_dm_err_t res;
    int i;

    /* Common initialization */
    example_init(&configs);
    adi_dm_Log("---> Entering example_syscal");

    /* These control whether the tasks that do t0 measurement are run.
     * Turn all off for now as they also compare agains t0 measurements
     * in non system calibration mode.
     */
    adi_dm_call_fw_rxchain_diag_chk = false;    /* BIST15: rx chain diagnostic check */
    adi_dm_call_fw_tx_pwr_chk = false;  /* BIST19: Tx output transmit power monitor */
    adi_dm_call_fw_pwr_det_rat_chk = false;     /* BIST44: power detector rationality check */
    adi_dm_call_fw_tx_output_load_monitor_chk = false;  /* BIST54: Tx output load monitor check */

    /* Sets system calibration mode which changes behaviour of
     * tasks used to do t0 measurement.
     */
    res = adi_dm_SetSysCal(true);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_SetSysCal", res, __FILE__, __LINE__);
    }

    adi_dm_call_fw_rxchain_diag_chk = true;

    /* t0 rx chain measurements can be taken now as they
     * depend upon PLL initialization and Rx chain
     * calibrations performed in adi_dm_PowerUp.
     * Use the BIST15: 'rx chain diagnostic check' task
     * to perform the measurement.
     */
    res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_RX_CHAIN_CHK);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_CallFW(ADI_ADAR690x_FW_RX_CHAIN_CHK)", res, __FILE__, __LINE__);
    }

    adi_dm_call_fw_rxchain_diag_chk = false;

    /* Save rx chain measurements */
    res = adi_dm_ReadSysCalRx(example_syscal_rx);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_ReadSysCalRx", res, __FILE__, __LINE__);
    }
    
    /* Now ready to start Tx measurements
     * These have to be made for each user configuration.
     */
    for (i = 0; i < configs.num_burst_profiles; i++) {
        if (i != 0) {
            example_switch_config(&configs, i);
        }
        printf("------------------------- Start %d burst --------------------------\n",i);

        /* BIST19, BIST54 t0 measurements taken at default power */
        adi_dm_call_fw_tx_pwr_chk = true;
        adi_dm_call_fw_tx_output_load_monitor_chk = true;

        burst(&configs);

        adi_dm_call_fw_tx_pwr_chk = false;
        adi_dm_call_fw_tx_output_load_monitor_chk = false;

        /* Save tx chain measurements for this config */
        res = adi_dm_ReadSysCalTx(example_syscal_tx[i]);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_ReadSysCalTx", res, __FILE__, __LINE__);
        }
    }

    /* After this point, system calibration is complete.
     * For neatness reset state.
     */
    adi_dm_call_fw_rxchain_diag_chk = true;     /* BIST15: rx chain diagnostic check */
    adi_dm_call_fw_tx_pwr_chk = true;   /* BIST19: Tx output transmit power monitor */
    adi_dm_call_fw_pwr_det_rat_chk = true;      /* BIST44: power detector rationality check */
    adi_dm_call_fw_tx_output_load_monitor_chk = true;   /* BIST54: Tx output load monitor check */

    res = adi_dm_SetSysCal(false);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_SetSysCal", res, __FILE__, __LINE__);
    }

    /* Power down the device. */
    res = adi_dm_PowerDown();
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_PowerDown", res, __FILE__, __LINE__);
    }

    adi_dm_Log("---> Exiting example_syscal");
    /* Release any resource used by the diver. */
    adi_dm_FiniDriver();
}

/***********************************************
* Trigger single burst for t0 measurement
************************************************
*/

static void burst(example_config_t * p)
{
    adi_dm_err_t res;
    adi_dm_periodic_calibration_t periodic;

    memset(&periodic, 0, sizeof(periodic));

    /* Enable RAMPON on GPIO8 to detect end of burst below. */
    res = adi_dm_PinMux(ADI_DM_MASTER, ADI_DM_GPIO8, 1, 1);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_PinMux", res, __FILE__, __LINE__);
    }

    /* Configure Power Measurement task for BISTs */
    res = adi_dm_PowerDetectorMeasTask(&p->bp[p->cur_bp_idx].pwrdet);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_PowerDetectorMeasTask", res, __FILE__, __LINE__);
    }
    /* run bist power checks as part of the periodic calibration. */
    /* this is needed for the t0 measurements which are power checks */
    periodic.run_power_checks = true;
    /* Enable checks that configuration does not change by accident */
    res = adi_dm_LockConfig();
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_LockConfig", res, __FILE__, __LINE__);
    }
    /* run bist checks as part of the periodic calibration. */
    periodic.run_checks = true;

    /* Do whatever is needed to prepare the host side to receive the next burst. */
    platform_prep_host_for_trigger();

    /* Issue software trigger. */
    res = adi_dm_Trigger();
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_Trigger", res, __FILE__, __LINE__);
    }

    /* Wait for burst completion signalled by RAMPON going low.
     * There may be better host side ways of detecting this,
     * such as noticing all data received.
     */
    res = adi_dm_WaitGPIO(ADI_DM_MASTER, ADI_DM_GPIO8, false, TIMEOUT_NS);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_WaitGPIO", res, __FILE__, __LINE__);
    }

    /* Firmware may run a task on ramp completion indicated by GPIO11 going high.
     * The delay between GPIO8 going low and GPIO11 going high is about 1 us.
     * Wait sufficient time to avoid race conditions with other GPIO11 detection.
     */
    adi_dm_DelayNS(1200);


    /* Run the recommended recalibrations. */
    res = adi_dm_PeriodicCalibration(&periodic);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_PeriodicCalibration", res, __FILE__, __LINE__);
    }

    /* Disable checks that configuration is not changed by accident */
    res = adi_dm_UnlockConfig();
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_UnlockConfig", res, __FILE__, __LINE__);
    }






}
