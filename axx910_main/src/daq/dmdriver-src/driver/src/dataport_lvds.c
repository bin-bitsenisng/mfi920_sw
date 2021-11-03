/* dataport_lvds.c
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

adi_dm_err_t adi_dm_LvdsSetup(const adi_dm_lvds_setup_t * p)
{
    uint32_t v;
    adi_dm_err_t res;
    adi_dm_num_t dm_num;

    comment("-->> Entering function adi_dm_DataportSetupLVDS");
    if (p->streaming_mode_1 && p->id_wc_en) {
        /* because we don't have the num_ramps parameter to calculate WC */
        comment("ERROR: id_wc_en not supported with streaming mode 1");
        return ADI_DM_PARAMETER_ERROR;
    }
    /* Enable LVDS_FS on GPIO 6. */
    res = adi_dm_PinMux(ADI_DM_ALL_DIGIMMICS, ADI_DM_GPIO6, 1, 1);
    if (res != ADI_DM_SUCCESS)
        return res;

    uint32_t bits = 0;
    switch (p->lvds_clk) {
    case ADI_DM_ADCCLK_DIV_6:
        comment("*** Setting LVDS clock to be ADCPLL clock divided by 6 ***");
        bits = ENUM_MISC_MISC_CLK_CTRL_ADCCLK_BY_6;
        break;
    case ADI_DM_ADCCLK_DIV_1_5:
        comment("*** Setting LVDS clock to be ADCPLL clock divided by 1.5 ***");
        bits = ENUM_MISC_MISC_CLK_CTRL_ADCCLK_BY_1P5;
        break;
    case ADI_DM_ADCCLK_DIV_2:
        comment("*** Setting LVDS clock to be ADCPLL clock divided by 2 ***");
        bits = ENUM_MISC_MISC_CLK_CTRL_ADCCLK_BY_2;
        break;
    case ADI_DM_ADCCLK_DIV_3:
        comment("*** Setting LVDS clock to be ADCPLL clock divided by 3 ***");
        bits = ENUM_MISC_MISC_CLK_CTRL_ADCCLK_BY_3;
        break;
    case ADI_DM_ADCCLK_DIV_4:
        comment("*** Setting LVDS clock to be ADCPLL clock divided by 4 ***");
        bits = ENUM_MISC_MISC_CLK_CTRL_ADCCLK_BY_4;
        break;
    case ADI_DM_ADCCLK_DIV_8:
        comment("*** Setting LVDS clock to be ADCPLL clock divided by 8 ***");
        bits = ENUM_MISC_MISC_CLK_CTRL_ADCCLK_BY_8;
        break;
    default:
        comment("ERROR: invalid lvds_clk");
        return ADI_DM_PARAMETER_ERROR;
    }
    uint32_t mask = ~BITM_MISC_MISC_CLK_CTRL_LVDS_CLK_SEL;
    res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_MISC_MISC_CLK_CTRL, mask, bits);
    if (res != ADI_DM_SUCCESS)
        return res;

    if (p->filter_output_bitwidth == ADI_DM_OUTPUT_BITWIDTH_16) {
        comment("*** Configuring Sample Size to 16 ***");
    } else if (p->filter_output_bitwidth == ADI_DM_OUTPUT_BITWIDTH_14) {
        comment("*** Configuring Sample Size to 14 ***");
    } else if (p->filter_output_bitwidth == ADI_DM_OUTPUT_BITWIDTH_12) {
        comment("*** Configuring Sample Size to 12 ***");
    } else {
        comment("ERROR: invalid filter_output_bitwidth");
        return ADI_DM_PARAMETER_ERROR;
    }
    mask = ~BITM_MISC_MISC_FILTER_CTRL_FILTER_OUTPUT_BITWIDTH;
    bits = p->filter_output_bitwidth << BITP_MISC_MISC_FILTER_CTRL_FILTER_OUTPUT_BITWIDTH;
    res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_MISC_MISC_FILTER_CTRL, mask, bits);
    if (res != ADI_DM_SUCCESS)
        return res;

    comment("*** DataPort config for memory controller ***");
    comment("*** Setting crc seed to zero ***");
    v = REG_DATA_PORT_DATA_PORT_CTL_REG_RESET;
    v = ENUM_DATA_PORT_DATA_PORT_CTL_REG_TRANSMIT_MODE | (v & ~BITM_DATA_PORT_DATA_PORT_CTL_REG_DATA_PORT_MODE_SEL);
    v = ENUM_DATA_PORT_DATA_PORT_CTL_REG_MEM_ACC_ENABLE | (v & ~BITM_DATA_PORT_DATA_PORT_CTL_REG_DATA_PORT_MEM_ACCESS_ENABLE);
    v = ENUM_DATA_PORT_DATA_PORT_CTL_REG_MEM_SHUTDOWN_DISABLE | (v & ~BITM_DATA_PORT_DATA_PORT_CTL_REG_DATA_PORT_MEM_SD);
    v = ENUM_DATA_PORT_DATA_PORT_CTL_REG_MEM_SLEEP_DISABLE | (v & ~BITM_DATA_PORT_DATA_PORT_CTL_REG_DATA_PORT_MEM_SLP);
    v = ENUM_DATA_PORT_DATA_PORT_CTL_REG_CRC32_ZERO_SEED | (v & ~BITM_DATA_PORT_DATA_PORT_CTL_REG_CRC32_SEED_SEL);
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_DATA_PORT_DATA_PORT_CTL_REG, v);
    if (res != ADI_DM_SUCCESS)
        return res;

    if (p->crc32_en) {
        /* ensure poly is set to default value */
        comment("*** crc poly is 0x82608EDB ***");
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_DATA_PORT_DATA_PORT_CRC32_POLY, 0x82608EDB);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    if (p->id_wc_en) {
        for (dm_num = 0; dm_num < adi_dm_active_digimmics; dm_num++) {
            comment("*** Setting the value of data id on rx channel0 (0x%02X), rx channel1 (0x%02X) ***", p->dm[dm_num].dataid0, p->dm[dm_num].dataid1);
            comment("*** Setting the value of data id on rx channel2 (0x%02X), rx channel3 (0x%02X) ***", p->dm[dm_num].dataid2, p->dm[dm_num].dataid3);
            uint32_t lvds_lvds_data_id_reg = REG_LVDS_LVDS_DATA_ID_REG_RESET;
            lvds_lvds_data_id_reg &= ~BITM_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL0;
            lvds_lvds_data_id_reg |= (p->dm[dm_num].dataid0 << BITP_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL0) & BITM_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL0;
            lvds_lvds_data_id_reg &= ~BITM_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL1;
            lvds_lvds_data_id_reg |= (p->dm[dm_num].dataid1 << BITP_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL1) & BITM_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL1;
            lvds_lvds_data_id_reg &= ~BITM_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL2;
            lvds_lvds_data_id_reg |= (p->dm[dm_num].dataid2 << BITP_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL2) & BITM_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL2;
            lvds_lvds_data_id_reg &= ~BITM_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL3;
            lvds_lvds_data_id_reg |= (p->dm[dm_num].dataid3 << BITP_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL3) & BITM_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL3;
            res = adi_dm_Write(dm_num, REG_LVDS_LVDS_DATA_ID_REG, lvds_lvds_data_id_reg);
            if (res != ADI_DM_SUCCESS)
                return res;
        }
    }

    if (p->status_en) {
        for (dm_num = 0; dm_num < adi_dm_active_digimmics; dm_num++) {
            comment("*** Setting the value of UserValue on rx channel0 (0x%02X), rx channel1 (0x%02X) ***", p->dm[dm_num].userval0, p->dm[dm_num].userval1);
            comment("*** Setting the value of UserValue on rx channel2 (0x%02X), rx channel3 (0x%02X) ***", p->dm[dm_num].userval2, p->dm[dm_num].userval3);
            uint32_t data_port_userval_reg = REG_DATA_PORT_DATA_PORT_USERVAL_REG_RESET;
            data_port_userval_reg &= ~BITM_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX0;
            data_port_userval_reg |= (p->dm[dm_num].userval0 << BITP_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX0) & BITM_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX0;
            data_port_userval_reg &= ~BITM_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX1;
            data_port_userval_reg |= (p->dm[dm_num].userval1 << BITP_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX1) & BITM_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX1;
            data_port_userval_reg &= ~BITM_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX2;
            data_port_userval_reg |= (p->dm[dm_num].userval2 << BITP_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX2) & BITM_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX2;
            data_port_userval_reg &= ~BITM_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX3;
            data_port_userval_reg |= (p->dm[dm_num].userval3 << BITP_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX3) & BITM_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX3;
            res = adi_dm_Write(dm_num, REG_DATA_PORT_DATA_PORT_USERVAL_REG, data_port_userval_reg);
            if (res != ADI_DM_SUCCESS)
                return res;
        }
    }

    int lvds_streaming_mode_sel = 0;
    if (p->streaming_mode_1) {
        comment("*** Stream mode 1 ***");
        lvds_streaming_mode_sel = 1;
    } else {
        comment("*** Stream mode 2 ***");
        lvds_streaming_mode_sel = 0;
    }
    comment("*** DATA_ID field %s ***", p->id_wc_en ? "enabled" : "disabled");
    comment("*** BYTE_COUNT field %s ***", p->id_wc_en ? "enabled" : "disabled");
    comment("*** PAYLOAD field %s ***", !p->payload_dis ? "enabled" : "disabled");
    comment("*** STATUS field %s ***", p->status_en ? "enabled" : "disabled");
    comment("*** DMA field disabled ***");
    comment("*** CRC field %s ***", p->crc32_en ? "enabled" : "disabled");
    comment("*** Single Tx field disabled ***");
    comment("*** Configure %s-bit  first transmission ***", p->ls_bit_first ? "LS" : "MS");
    comment("*** Configure %s_byte first transmission ***", p->ls_byte_first ? "LS" : "MS");
    comment("*** %s framing mode ***", p->dual_fs_mode ? "Dual FS" : "Default");
    uint32_t lvds_lvds_ctl_reg = REG_LVDS_LVDS_CTL_REG_RESET;
    lvds_lvds_ctl_reg &= ~BITM_LVDS_LVDS_CTL_REG_LVDS_STREAMING_MODE_SEL;
    lvds_lvds_ctl_reg |= (lvds_streaming_mode_sel << BITP_LVDS_LVDS_CTL_REG_LVDS_STREAMING_MODE_SEL) & BITM_LVDS_LVDS_CTL_REG_LVDS_STREAMING_MODE_SEL;
    lvds_lvds_ctl_reg &= ~BITM_LVDS_LVDS_CTL_REG_LVDS_INACT_PH_TX_EN;
    lvds_lvds_ctl_reg &= ~BITM_LVDS_LVDS_CTL_REG_LVDS_1CH_TX_MODE_EN;
    lvds_lvds_ctl_reg &= ~BITM_LVDS_LVDS_CTL_REG_LVDS_1CH_TX_MODE_EN;
    if (p->id_wc_en)
        lvds_lvds_ctl_reg |= BITM_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_DATA_ID_WC_FIELD_EN;
    else
        lvds_lvds_ctl_reg &= ~BITM_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_DATA_ID_WC_FIELD_EN;
    if (!p->payload_dis)
        lvds_lvds_ctl_reg |= BITM_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_RX_CH_FIELD_EN;
    else
        lvds_lvds_ctl_reg &= ~BITM_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_RX_CH_FIELD_EN;
    if (p->status_en)
        lvds_lvds_ctl_reg |= BITM_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_STATUS_FIELD_EN;
    else
        lvds_lvds_ctl_reg &= ~BITM_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_STATUS_FIELD_EN;
    lvds_lvds_ctl_reg &= ~BITM_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_DMA_DATA_FIELD_EN;
    if (p->crc32_en)
        lvds_lvds_ctl_reg |= BITM_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_CRC_FIELD_EN;
    else
        lvds_lvds_ctl_reg &= ~BITM_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_CRC_FIELD_EN;
    lvds_lvds_ctl_reg &= ~BITM_LVDS_LVDS_CTL_REG_LVDS_1CH_TX_MODE_EN;
    if (p->ls_bit_first)
        lvds_lvds_ctl_reg |= BITM_LVDS_LVDS_CTL_REG_LSBIT_MSBIT_SEL;
    else
        lvds_lvds_ctl_reg &= ~BITM_LVDS_LVDS_CTL_REG_LSBIT_MSBIT_SEL;
    if (p->ls_byte_first)
        lvds_lvds_ctl_reg |= BITM_LVDS_LVDS_CTL_REG_LSBYTE_MSBYTE_SEL;
    else
        lvds_lvds_ctl_reg &= ~BITM_LVDS_LVDS_CTL_REG_LSBYTE_MSBYTE_SEL;
    if (p->dual_fs_mode)
        lvds_lvds_ctl_reg |= BITM_LVDS_LVDS_CTL_REG_FRAMING_MODE;
    else
        lvds_lvds_ctl_reg &= ~BITM_LVDS_LVDS_CTL_REG_FRAMING_MODE;
    if (p->fs_active_low)
        lvds_lvds_ctl_reg |= BITM_LVDS_LVDS_CTL_REG_FRAME_SYNC_POLARITY;
    else
        lvds_lvds_ctl_reg &= ~BITM_LVDS_LVDS_CTL_REG_FRAME_SYNC_POLARITY;
    lvds_lvds_ctl_reg |= BITM_LVDS_LVDS_CTL_REG_AUTO_CONFIG_WC;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_LVDS_LVDS_CTL_REG, lvds_lvds_ctl_reg);
    if (res != ADI_DM_SUCCESS)
        return res;

    comment("*** LVDS Port enabled ***");
    uint32_t lvds_data_pipe_ctl = REG_LVDS_DATA_PIPE_CTL_RESET;
    lvds_data_pipe_ctl |= BITM_LVDS_DATA_PIPE_CTL_LVDSEN;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_LVDS_DATA_PIPE_CTL, lvds_data_pipe_ctl);
    if (res != ADI_DM_SUCCESS)
        return res;

    comment("-->> Exiting function adi_dm_DataportSetupLVDS");
    return ADI_DM_SUCCESS;
}

uint32_t adi_dm_Crc32ADI(uint8_t * p, int n, int step)
{
    const uint32_t poly = 0x04c11db7;   // default polynomial
    const uint32_t seed = 0;    // default seed
    uint32_t crc = seed;
    for (int sample = 0; sample < n; sample++) {
        uint16_t inp = p[0] | p[1] << 8;
        for (int j = 15; j >= 0; j--) {
            uint32_t bit = ((inp >> j) ^ (crc >> 31)) & 1;
            uint32_t mask = (uint32_t) - (int32_t) bit;
            crc = ((crc << 1) ^ (poly & mask)) | bit;
        }
        p += step;
    }
    return crc;
}
