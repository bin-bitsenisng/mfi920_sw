/* 3_0_multiburst.c
 * Copyright (c) 2018-2020 Analog Devices Inc. All rights reserved
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

#define ADI_DM_NO_LEGACY_REDEF 1
#include "legacy/3_0/adi_dmdriver.h"
#include "adar690x_fw.h"
#include "../localdefs.h"
#include <string.h>

static bool null_halt(void)
{
    return false;
}

adi_dm_err_t adi_dm_3_0_TriggerMultiburst(adi_dm_3_0_trigger_multiburst_t * p)
{
    adi_dm_err_t res;
    const uint32_t offtime_us = p->offtime_us;
    const uint32_t offtime_sleep_us = p->offtime_sleep_us;
    const bool manual_sleep = p->manual_sleep;
    const uint32_t remaning_offtime_us = offtime_us - offtime_sleep_us;
    const bool run_till_counter_expires = p->run_till_counter_expires;
    bool(*const halt_requested) (void) = p->halt_requested ? p->halt_requested : null_halt;
    void (*const prep_host_for_trigger) (void) = p->prep_host_for_trigger;
    uint32_t counter = p->count;
    bool counter_expired = false;
    adi_dm_periodic_calibration_t periodic;

    memset(&periodic, 0, sizeof(periodic));
    periodic.no_rfpll_bow_cal = false;
    periodic.no_lochain_cal = p->no_lochain_cal;
    periodic.no_adcpll_align = false;

    if (offtime_sleep_us != 0 && offtime_sleep_us > (offtime_us - 2000)) {
        /* This check is to ensure there is at least 2ms of offtime
         * after powering up for RFPLL to settle. When offtime_sleep_us is 0
         * there is no powering up and no need for the check.
         */
        comment("ERROR: Bad offtime_sleep_us");
        return ADI_DM_PARAMETER_ERROR;
    }

    /* enable RAMPON on GPIO8 to detect end of bursts */
    res = adi_dm_PinMux(ADI_DM_MASTER, ADI_DM_GPIO8, 1, 1);
    if (res != ADI_DM_SUCCESS)
        return res;

    if (offtime_sleep_us) {
        if (manual_sleep) {
            /* ensure automatic power down is disabled */
            adi_dm_3_2_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_POWER_DOWN_AUTO_US, 0);
        } else {
            /* enable automatic power down */
            adi_dm_3_2_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_POWER_DOWN_AUTO_US, offtime_sleep_us);
        }
    }

    while (!counter_expired && !halt_requested()) {
        res = adi_dm_PeriodicCalibration(&periodic);
        if (res != ADI_DM_SUCCESS)
            return res;

        if (prep_host_for_trigger)
            prep_host_for_trigger();

        res = adi_dm_Trigger();
        if (res != ADI_DM_SUCCESS)
            return res;

        /* wait for burst end on GPIO8 */
        res = adi_dm_WaitGPIO(ADI_DM_MASTER, ADI_DM_GPIO8, false, TIMEOUT);
        if (res != ADI_DM_SUCCESS)
            return res;
        /* repeat in case first wait caught low before going high */
        res = adi_dm_WaitGPIO(ADI_DM_MASTER, ADI_DM_GPIO8, false, TIMEOUT);
        if (res != ADI_DM_SUCCESS)
            return res;
        /* Firmware may run a task on ramp completion indicated by GPIO11 going high.
         * The delay between GPIO8 going low and GPIO11 going high is about 1 us.
         * Wait sufficient time to avoid race conditions with other GPIO11 detection.
         */
        adi_dm_DelayNS(1200);
        if (offtime_sleep_us) {
            if (manual_sleep) {
                /* tell part to power down */
                res = adi_dm_ManualSleep();
                if (res != ADI_DM_SUCCESS)
                    return res;
                /* measure sleep time locally */
                adi_dm_DelayNS(offtime_sleep_us * 1000);
                /* tell part to power up */
                res = adi_dm_ManualWake();
                if (res != ADI_DM_SUCCESS)
                    return res;
            } else {
                adi_dm_num_t dm_num;
                for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
                    /* wait for power down period indicated on GPIO11 */
                    res = adi_dm_WaitGPIO(dm_num, ADI_DM_GPIO11, false, TIMEOUT);
                    if (res != ADI_DM_SUCCESS)
                        return res;
                    /* repeat in case first wait caught low before going high */
                    res = adi_dm_WaitGPIO(dm_num, ADI_DM_GPIO11, false, TIMEOUT);
                    if (res != ADI_DM_SUCCESS)
                        return res;
                }
            }
        }
        adi_dm_DelayNS(remaning_offtime_us * 1000);
        if (run_till_counter_expires)
            counter_expired = (--counter) == 0;
    }
    if (offtime_sleep_us && !manual_sleep) {
        /* ensure automatic power down is disabled */
        adi_dm_3_2_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_POWER_DOWN_AUTO_US, 0);
    }
    return ADI_DM_SUCCESS;
}
