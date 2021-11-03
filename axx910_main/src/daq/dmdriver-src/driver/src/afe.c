/* afe.c
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
#include "adar690x_fw.h"
#include <stdio.h>

enum {
    max_rx = ADI_DM_NUM_RX * ADI_DM_NUM_DIGIMMIC,
    rx_channel_mask = (1 << ADI_DM_NUM_RX) - 1
};

adi_dm_err_t adi_dm_AfeSetup(const adi_dm_afe_setup_t * p)
{
    uint32_t rx_channels = p->rx_channels;
    uint32_t hpf_ctrl0_addr, pga_ctrl0_addr;
    uint32_t mask, bits;
    uint32_t rx_chan;
    adi_dm_num_t dm_num;
    adi_dm_err_t res;

    comment("---> Entering function adi_dm_AfeSetup");

    /* Check firmware parameters. */
    if (adi_dm_check_fw_config && (p->hpf_fc < ADI_ADAR690x_MIN_HPF_FC_RX_CHAN0 || p->hpf_fc > ADI_ADAR690x_MAX_HPF_FC_RX_CHAN0)) {
        comment("ERROR: Bad hpf_fc");
        return ADI_DM_PARAMETER_ERROR;
    }
    if (adi_dm_check_fw_config && (p->hpf_gain < ADI_ADAR690x_MIN_HPF_GAIN_RX_CHAN0 || p->hpf_gain > ADI_ADAR690x_MAX_HPF_GAIN_RX_CHAN0)) {
        comment("ERROR: Bad hpf_gain");
        return ADI_DM_PARAMETER_ERROR;
    }
    if (adi_dm_check_fw_config && (p->pga_gain < ADI_ADAR690x_MIN_PGA_GAIN_RX_CHAN0 || p->pga_gain > ADI_ADAR690x_MAX_PGA_GAIN_RX_CHAN0)) {
        comment("ERROR: Bad pga_gain");
        return ADI_DM_PARAMETER_ERROR;
    }
    if (adi_dm_check_fw_config && (p->adc_gain < ADI_ADAR690x_MIN_ADC_GAIN_RX_CHAN0 || p->adc_gain > ADI_ADAR690x_MAX_ADC_GAIN_RX_CHAN0)) {
        comment("ERROR: Bad adc_gain");
        return ADI_DM_PARAMETER_ERROR;
    }

    if (rx_channels == 0) {
        /* set bits for all channels */
        rx_channels = (1 << max_rx) - 1;
    }

    for (rx_chan = 0; rx_chan < max_rx; rx_chan++) {
        if ((rx_channels & (1 << rx_chan)) != 0) {
            uint8_t dm_num = rx_chan / ADI_DM_NUM_RX;
            switch (rx_chan % ADI_DM_NUM_RX) {
            case 0:
            default:
                hpf_ctrl0_addr = REG_AFE0_HPF_CTRL0;
                pga_ctrl0_addr = REG_AFE0_PGA_CTRL0;
                break;
            case 1:
                hpf_ctrl0_addr = REG_AFE1_HPF_CTRL0;
                pga_ctrl0_addr = REG_AFE1_PGA_CTRL0;
                break;
            case 2:
                hpf_ctrl0_addr = REG_AFE2_HPF_CTRL0;
                pga_ctrl0_addr = REG_AFE2_PGA_CTRL0;
                break;
            case 3:
                hpf_ctrl0_addr = REG_AFE3_HPF_CTRL0;
                pga_ctrl0_addr = REG_AFE3_PGA_CTRL0;
                break;
            }
            printf("channel %d\n", rx_chan);
            mask = ~0u;
            bits = 0u;
            mask &= ~BITM_AFE_HPF_CTRL0_HPF_BYPASS;
            bits |= (p->hpf_bypass << BITP_AFE_HPF_CTRL0_HPF_BYPASS) & BITM_AFE_HPF_CTRL0_HPF_BYPASS;
            res = adi_dm_RMW(dm_num, hpf_ctrl0_addr, mask, bits);
            if (res != ADI_DM_SUCCESS)
                return res;

            mask = ~0u;
            bits = 0u;
            mask &= ~BITM_AFE_PGA_CTRL0_PGA_MUX;
            bits |= (p->pga_mux << BITP_AFE_PGA_CTRL0_PGA_MUX) & BITM_AFE_PGA_CTRL0_PGA_MUX;
            res = adi_dm_RMW(dm_num, pga_ctrl0_addr, mask, bits);
            if (res != ADI_DM_SUCCESS)
                return res;
        }
    }

    /* Call calibrations. */
    if (p->rx_channels == 0) {
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_HPF_FC_RX_CHAN0, p->hpf_fc);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_HPF_FC_RX_CHAN1, p->hpf_fc);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_HPF_FC_RX_CHAN2, p->hpf_fc);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_HPF_FC_RX_CHAN3, p->hpf_fc);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_HPF_GAIN_RX_CHAN0, p->hpf_gain);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_HPF_GAIN_RX_CHAN1, p->hpf_gain);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_HPF_GAIN_RX_CHAN2, p->hpf_gain);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_HPF_GAIN_RX_CHAN3, p->hpf_gain);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_PGA_GAIN_RX_CHAN0, p->pga_gain);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_PGA_GAIN_RX_CHAN1, p->pga_gain);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_PGA_GAIN_RX_CHAN2, p->pga_gain);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_PGA_GAIN_RX_CHAN3, p->pga_gain);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_ADC_GAIN_RX_CHAN0, p->adc_gain);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_ADC_GAIN_RX_CHAN1, p->adc_gain);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_ADC_GAIN_RX_CHAN2, p->adc_gain);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_ADC_GAIN_RX_CHAN3, p->adc_gain);
        if (res != ADI_DM_SUCCESS)
            return res;

        if (adi_dm_call_fw_pga_cal) {
            comment("ADI_ADAR690x_FW_PGA_CAL");
            res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_PGA_CAL);
            if (res != ADI_DM_SUCCESS) {
                return res;
            }
        }

        if (adi_dm_call_fw_hpf_cal && !p->hpf_bypass) {
            comment("ADI_ADAR690x_FW_HPF_CAL");
            res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_HPF_CAL);
            if (res != ADI_DM_SUCCESS) {
                return res;
            }
        }

    } else {
        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            uint32_t rx_channels = (p->rx_channels >> (dm_num * ADI_DM_NUM_RX)) & rx_channel_mask;
            if (rx_channels != 0) {
                bool any_chan_hpf_bypassed = false;
                for (rx_chan = 0; rx_chan < ADI_DM_NUM_RX && !any_chan_hpf_bypassed; rx_chan++) {
                    uint32_t val;
                    uint32_t addr = REG_AFE0_HPF_CTRL0 + rx_chan * (REG_AFE1_HPF_CTRL0 - REG_AFE0_HPF_CTRL0);
                    res = adi_dm_Read(dm_num, addr, &val);
                    if (res != ADI_DM_SUCCESS)
                        return res;
                    any_chan_hpf_bypassed = any_chan_hpf_bypassed || (val & BITM_AFE_HPF_CTRL0_HPF_BYPASS) != 0;
                }
                for (rx_chan = 0; rx_chan < ADI_DM_NUM_RX; rx_chan++) {
                    if ((rx_channels & (1 << rx_chan)) != 0) {
                        res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_HPF_FC_RX_CHAN0 + 4 * rx_chan, p->hpf_fc);
                        if (res != ADI_DM_SUCCESS)
                            return res;
                        res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_HPF_GAIN_RX_CHAN0 + 4 * rx_chan, p->hpf_gain);
                        if (res != ADI_DM_SUCCESS)
                            return res;
                        res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_PGA_GAIN_RX_CHAN0 + 4 * rx_chan, p->pga_gain);
                        if (res != ADI_DM_SUCCESS)
                            return res;
                        res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_ADC_GAIN_RX_CHAN0 + 4 * rx_chan, p->adc_gain);
                        if (res != ADI_DM_SUCCESS)
                            return res;
                    }
                }
            

                if (adi_dm_call_fw_pga_cal) {
                    comment("ADI_ADAR690x_FW_PGA_CAL");
                    res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_PGA_CAL);
                    if (res != ADI_DM_SUCCESS) {
                        return res;
                    }
                }

                if (adi_dm_call_fw_hpf_cal && !any_chan_hpf_bypassed) {
                    comment("ADI_ADAR690x_FW_HPF_CAL_SINGLE_CHAN");
                    res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_HPF_CAL_SINGLE_CHAN);
                    if (res != ADI_DM_SUCCESS) {
                        return res;
                    }
                }

            }
        }

    }

    comment("---> Exiting function adi_dm_AfeSetup");
    return ADI_DM_SUCCESS;
}
