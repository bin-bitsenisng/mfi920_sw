/* pd_measure.c
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

#include "adi_dmdriver.h"
#include "localdefs.h"
#include "adar690x_fw.h"
#include <math.h>

#define BITP_LO 0
#define BITP_TX_ACTIVE_COUPLED 1
#define BITP_TX_ACTIVE_REFLECTED 4
#define BITM_MEAS_TX0_INACTIVE_REFLECTED_ALL_INACTIVE (1 << 7)
#define BITM_MEAS_TX0_INACTIVE_REFLECTED_TX1_ACTIVE (1 << 8)
#define BITM_MEAS_TX0_INACTIVE_REFLECTED_TX2_ACTIVE (1 << 9)
#define BITM_MEAS_TX0_INACTIVE_REFLECTED_TX1_TX2_ACTIVE (1 << 10)
#define BITM_MEAS_TX1_INACTIVE_REFLECTED_ALL_INACTIVE (1 << 11)
#define BITM_MEAS_TX1_INACTIVE_REFLECTED_TX0_ACTIVE (1 << 12)
#define BITM_MEAS_TX1_INACTIVE_REFLECTED_TX2_ACTIVE (1 << 13)
#define BITM_MEAS_TX1_INACTIVE_REFLECTED_TX0_TX2_ACTIVE (1 << 14)
#define BITM_MEAS_TX2_INACTIVE_REFLECTED_ALL_INACTIVE (1 << 15)
#define BITM_MEAS_TX2_INACTIVE_REFLECTED_TX0_ACTIVE (1 << 16)
#define BITM_MEAS_TX2_INACTIVE_REFLECTED_TX1_ACTIVE (1 << 17)
#define BITM_MEAS_TX2_INACTIVE_REFLECTED_TX0_TX1_ACTIVE (1 << 18)
#define BITP_CLR_PREV 19
#define BITM_CLR_PREV (1 << BITP_CLR_PREV)
#define BITP_PDMEASPERCHIRP 20
#define BITM_PDMEASPERCHIRP (1 << BITP_PDMEASPERCHIRP)
#define TX_MSK ((1 << ADI_DM_NUM_TX) - 1)     /** Number of Tx channels on each part. */
#define TX0_MSK 1
#define TX1_MSK 2
#define TX2_MSK 4

static uint32_t saved_pd_task_cfg[ADI_DM_NUM_DIGIMMIC];

adi_dm_err_t adi_dm_power_detector_enable()
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    comment("ADI_ADAR690x_FW_MEAS_PWR_DET");
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_MEAS_PWR_DET);
        if (res != ADI_DM_SUCCESS)
            return res;
    }
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_power_detector_offset()
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    comment("ADI_ADAR690x_FW_MEAS_PWR_DET_OFF");
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_MEAS_PWR_DET_OFF);
        if (res != ADI_DM_SUCCESS)
            return res;
    }
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_power_detector_clear()
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    comment("ADI_ADAR690x_FW_MEAS_PWR_DET_CLR");
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_MEAS_PWR_DET_CLR);
        if (res != ADI_DM_SUCCESS)
            return res;
    }
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_PowerDetectorMeasTask(adi_dm_power_detector_meas_task_t * p)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    uint8_t tx_num;
    uint8_t tx_active = 0;
    uint32_t pd_task_cfg = 0x00000000;

    comment("-->> Entering function adi_dm_PowerDetectorMeasConfig");
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {

        pd_task_cfg = 0x00000000;
        tx_active = 0;
        for (tx_num = 0; tx_num < ADI_DM_NUM_TX; tx_num++) {
            if (p->dm[dm_num].tx_active[tx_num]) {
                tx_active |= 1 << tx_num;
            }
        }

        if (adi_dm_call_fw_rxchain_diag_chk)
            pd_task_cfg |= 1 << BITP_LO;
        if (adi_dm_call_fw_tx_pwr_chk)
            pd_task_cfg |= tx_active << BITP_TX_ACTIVE_COUPLED;
        if (adi_dm_call_fw_tx_output_load_monitor_chk || adi_dm_call_fw_pwr_det_rat_chk) {
            pd_task_cfg |= tx_active << BITP_TX_ACTIVE_COUPLED;
            pd_task_cfg |= tx_active << BITP_TX_ACTIVE_REFLECTED;
        }
        if (adi_dm_call_fw_tx_isolation_monitor_chk) {
            if (p->dm[dm_num].tx0_inactive_when_all_inactive)
                pd_task_cfg |= BITM_MEAS_TX0_INACTIVE_REFLECTED_ALL_INACTIVE;
            if (p->dm[dm_num].tx0_inactive_when_tx1_active)
                pd_task_cfg |= BITM_MEAS_TX0_INACTIVE_REFLECTED_TX1_ACTIVE;
            if (p->dm[dm_num].tx0_inactive_when_tx2_active)
                pd_task_cfg |= BITM_MEAS_TX0_INACTIVE_REFLECTED_TX2_ACTIVE;
            if (p->dm[dm_num].tx0_inactive_when_tx1_tx2_active)
                pd_task_cfg |= BITM_MEAS_TX0_INACTIVE_REFLECTED_TX1_TX2_ACTIVE;
            if (p->dm[dm_num].tx1_inactive_when_all_inactive)
                pd_task_cfg |= BITM_MEAS_TX1_INACTIVE_REFLECTED_ALL_INACTIVE;
            if (p->dm[dm_num].tx1_inactive_when_tx0_active)
                pd_task_cfg |= BITM_MEAS_TX1_INACTIVE_REFLECTED_TX0_ACTIVE;
            if (p->dm[dm_num].tx1_inactive_when_tx2_active)
                pd_task_cfg |= BITM_MEAS_TX1_INACTIVE_REFLECTED_TX2_ACTIVE;
            if (p->dm[dm_num].tx1_inactive_when_tx0_tx2_active)
                pd_task_cfg |= BITM_MEAS_TX1_INACTIVE_REFLECTED_TX0_TX2_ACTIVE;
            if (p->dm[dm_num].tx2_inactive_when_all_inactive)
                pd_task_cfg |= BITM_MEAS_TX2_INACTIVE_REFLECTED_ALL_INACTIVE;
            if (p->dm[dm_num].tx2_inactive_when_tx1_active)
                pd_task_cfg |= BITM_MEAS_TX2_INACTIVE_REFLECTED_TX1_ACTIVE;
            if (p->dm[dm_num].tx2_inactive_when_tx0_active)
                pd_task_cfg |= BITM_MEAS_TX2_INACTIVE_REFLECTED_TX0_ACTIVE;
            if (p->dm[dm_num].tx2_inactive_when_tx0_tx1_active)
                pd_task_cfg |= BITM_MEAS_TX2_INACTIVE_REFLECTED_TX0_TX1_ACTIVE;

        }
        pd_task_cfg |= BITM_PDMEASPERCHIRP;
        pd_task_cfg |= BITM_CLR_PREV;

        printf("pd_task_cfg = %x of dm = %d\n", pd_task_cfg, dm_num);

        res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_PWR_DET_MEAS, pd_task_cfg);
        if (res != ADI_DM_SUCCESS)
            return res;
        saved_pd_task_cfg[dm_num] = pd_task_cfg;
    }

    res = adi_dm_power_detector_enable();
    if (res != ADI_DM_SUCCESS)
        return res;
    comment("-->> Exiting function adi_dm_PowerDetectorMeasConfig");

    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_cascaded_tx_pwr_chk(void)
{
    /* BIST19: Tx output transmit power check accross devices */
    adi_dm_num_t dm_num;
    adi_dm_err_t res;
    struct {
        float tx_pwr[ADI_DM_NUM_TX];
    } dm[ADI_DM_NUM_DIGIMMIC];

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        res = adi_dm_BlockRead(dm_num, ADI_ADAR690x_STS_OP_PWR_TX0, ADI_DM_NUM_TX * 4, dm[dm_num].tx_pwr);
        if (res != ADI_DM_SUCCESS)
            return res;
    }
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        uint32_t tx;
        uint32_t pd_task_cfg = saved_pd_task_cfg[dm_num];
        for (tx = 0; tx < ADI_DM_NUM_TX; tx++) {
            bool tx_active = (pd_task_cfg & (1 << (tx + BITP_TX_ACTIVE_COUPLED))) != 0;
            if (tx_active) {
                float tx_db = 10.0f * log10f(dm[dm_num].tx_pwr[tx]);
                adi_dm_num_t other_dm;
                for (other_dm = ADI_DM_MASTER; other_dm < adi_dm_active_digimmics; other_dm++) {
                    if (other_dm != dm_num) {
                        uint32_t other_tx;
                        uint32_t other_pd_task_cfg = saved_pd_task_cfg[other_dm];
                        for (other_tx = 0; other_tx < ADI_DM_NUM_TX; other_tx++) {
                            bool other_tx_active = (other_pd_task_cfg & (1 << (other_tx + BITP_TX_ACTIVE_COUPLED))) != 0;
                            if (other_tx_active) {
                                float other_tx_db = 10.0f * log10f(dm[other_dm].tx_pwr[other_tx]);
                                float threshold = fabsf(tx_db - other_tx_db);
                                if (threshold > 3.0f) {
                                    return ADI_DM_CASCADED_TX_PWR_CHK_ERROR;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return ADI_DM_SUCCESS;
}
