/* tx_ramp.c
 * Copyright (c) 2018 Analog Devices Inc. All rights reserved
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

adi_dm_err_t adi_dm_TxSetup(const adi_dm_tx_setup_t * p)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    int i;
    const uint32_t tx_mask = (1 << ADI_DM_NUM_TX) - 1;

    comment("-->> Entering function adi_dm_TxSetup");

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        uint32_t tx_enable = p->dm[dm_num].tx_enable;
        uint32_t tx_disable = tx_enable ^ tx_mask;
        uint32_t continuous_pa = p->dm[dm_num].continuous_pa & tx_enable;

        comment("tx_enable = %d, continuous_pa = %d", p->dm[dm_num].tx_enable, p->dm[dm_num].continuous_pa);
        for (i = 0; i < ADI_DM_NUM_TX; i++) {
            comment("pa_gain_backoff_db[%d] = %d", i, p->dm[dm_num].pa_gain_backoff_db[i]);
            if (adi_dm_check_fw_config && (p->dm[dm_num].pa_gain_backoff_db[i] < ADI_ADAR690x_MIN_PWR_TX0 || p->dm[dm_num].pa_gain_backoff_db[i] > ADI_ADAR690x_MAX_PWR_TX0)) {
                comment("ERROR: Bad pa_gain_backoff_db");
                return ADI_DM_PARAMETER_ERROR;
            }
            res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_PWR_TX0 + i * 4, p->dm[dm_num].pa_gain_backoff_db[i]);
            if (res != ADI_DM_SUCCESS)
                return res;
        }
        if (tx_enable) {
            uint32_t arg0 = ADI_ADAR690x_BITM_POWER_UP_REQUEST | ADI_ADAR690x_BITM_POWER_PERMANENT | (tx_enable << ADI_ADAR690x_BITP_POWER_TX0);
            uint32_t arg1 = continuous_pa << ADI_ADAR690x_BITP_CONTINUOUS_PA_TX0;
            comment("ADI_ADAR690x_FW_POWER_MANAGE 0x%08X 0x%08X", arg0, arg1);
            res = adi_dm_CallFW2(dm_num, ADI_ADAR690x_FW_POWER_MANAGE, arg0, arg1);
            if (res != ADI_DM_SUCCESS)
                return res;
        }
        if (tx_disable) {
            uint32_t arg0 = ADI_ADAR690x_BITM_POWER_DOWN_REQUEST | ADI_ADAR690x_BITM_POWER_PERMANENT | (tx_disable << ADI_ADAR690x_BITP_POWER_TX0);
            uint32_t arg1 = 0;
            comment("ADI_ADAR690x_FW_POWER_MANAGE 0x%08X 0x%08X", arg0, arg1);
            res = adi_dm_CallFW2(dm_num, ADI_ADAR690x_FW_POWER_MANAGE, arg0, arg1);
            if (res != ADI_DM_SUCCESS)
                return res;
        }

        /* if no tx channels are enabled, don't attempt to run the PA cal */
        if (adi_dm_call_fw_txpa_cal && tx_enable) {
            comment("ADI_ADAR690x_FW_TXPA_CAL");
            res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_TXPA_CAL);
            if (res != ADI_DM_SUCCESS)
                return res;
        }

        /* modify the parameter for BIST03 */
        res = adi_dm_RMW(dm_num, ADI_ADAR690x_CFG_PWR_SUP_CHK, 0xFFFFF8FF, tx_enable << 8);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    comment("-->> Exiting function adi_dm_TxSetup");
    return ADI_DM_SUCCESS;
}
