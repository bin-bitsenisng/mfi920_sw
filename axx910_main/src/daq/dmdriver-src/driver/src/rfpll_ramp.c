/* rfpll_ramp.c
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
#include "adar690x_regs.h"

adi_dm_err_t adi_dm_ramp_config(const adi_dm_ramp_config_t * p, const adi_dm_builtin_mimo_setup_t * builtin_mimo)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    uint32_t mask, bits;

    comment("--> Entering function adi_dm_ramp_config");

    /* Set misc_filter_ctrl */
    mask = ~UINT32_C(0);
    bits = UINT32_C(0);
    mask &= ~BITM_MISC_MISC_FILTER_CTRL_FILTER_DECIM_RATIO;
    bits |= p->filter_decim_ratio << BITP_MISC_MISC_FILTER_CTRL_FILTER_DECIM_RATIO;
    res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_MISC_MISC_FILTER_CTRL, mask, bits);
    if (res != ADI_DM_SUCCESS)
        return res;

    /* Set misc_filter_ctrl_1 */
    mask = ~UINT32_C(0);
    bits = UINT32_C(0);
    mask &= ~BITM_MISC_MISC_FILTER_CTRL_1_FILTER_VALID_DELAY;
    bits |= p->filter_valid_delay << BITP_MISC_MISC_FILTER_CTRL_1_FILTER_VALID_DELAY;
    res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_MISC_MISC_FILTER_CTRL_1, mask, bits);
    if (res != ADI_DM_SUCCESS)
        return res;

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        /* ramp_config3 */
        mask = ~UINT32_C(0);
        bits = UINT32_C(0);
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_EN;
        bits |= (p->pga_shunt_en << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_EN) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_EN;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_START_DEL;
        bits |= (p->pga_shunt_start_del << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_START_DEL) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_START_DEL;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_STOP_DEL;
        bits |= (p->pga_shunt_stop_del << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_STOP_DEL) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_STOP_DEL;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_VGA_GAUSS_DIS;
        bits |= (p->dm[dm_num].vga_gauss_dis << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_VGA_GAUSS_DIS) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_VGA_GAUSS_DIS;
        res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_RF_ADPLL_RFPLL_RAMP_CONFIG3, mask, bits);
        if (res != ADI_DM_SUCCESS)
            return res;

        /* ramp_config2 */
        mask = ~UINT32_C(0);
        bits = UINT32_C(0);
        if (builtin_mimo == NULL) {
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ;
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ_LEN;
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_MODE_EN;
        } else {
            uint32_t mimo_seq_val, mimo_seq_len;
            if (builtin_mimo->mimo_seq_len > 0) {
                mimo_seq_val = builtin_mimo->dm[dm_num].mimo_seq_val;
                mimo_seq_len = builtin_mimo->mimo_seq_len;
            } else {
                mimo_seq_val = builtin_mimo->ramp_profile.dm[dm_num].tx_pattern;
                mimo_seq_len = 1UL;
            }
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ;
            bits |= (mimo_seq_val << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ;
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ_LEN;
            bits |= (mimo_seq_len << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ_LEN) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ_LEN;
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_MODE_EN;
            bits |= BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_MODE_EN;
        }
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_RAMP_COUNT;
        bits |= (p->ramp_count << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG2_RAMP_COUNT) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_RAMP_COUNT;
        res = adi_dm_RMW(dm_num, REG_RF_ADPLL_RFPLL_RAMP_CONFIG2, mask, bits);
        if (res != ADI_DM_SUCCESS)
            return res;

        /* ramp_config1 */
        mask = ~UINT32_C(0);
        bits = UINT32_C(0);
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_ON_PATT;
        bits |= (p->dm[dm_num].vga_on_patt << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_ON_PATT) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_ON_PATT;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_DELAY_EN;
        bits |= (p->dm[dm_num].phase_delay_en << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_DELAY_EN) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_DELAY_EN;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_MOD_EN;
        bits |= (p->dm[dm_num].phase_mod_en << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_MOD_EN) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_MOD_EN;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA_OFF_TIME;
        bits |= (p->dm[dm_num].pa_off_time << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA_OFF_TIME) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA_OFF_TIME;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEPS;
        bits |= (p->dm[dm_num].vga_gain_steps << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEPS) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEPS;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEP_DIV;
        bits |= (p->dm[dm_num].vga_gain_step_div << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEP_DIV) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEP_DIV;
        res = adi_dm_RMW(dm_num, REG_RF_ADPLL_RFPLL_RAMP_CONFIG1, mask, bits);
        if (res != ADI_DM_SUCCESS)
            return res;

        /* ramp_config0 */
        mask = ~UINT32_C(0);
        bits = UINT32_C(0);
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG0_VGA_SYNC_DATA_VALID;
        bits |= (p->dm[dm_num].vga_sync_data_valid << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG0_VGA_SYNC_DATA_VALID) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG0_VGA_SYNC_DATA_VALID;
        res = adi_dm_RMW(dm_num, REG_RF_ADPLL_RFPLL_RAMP_CONFIG0, mask, bits);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    comment("--> Leaving function adi_dm_ramp_config");
    return ADI_DM_SUCCESS;
}
