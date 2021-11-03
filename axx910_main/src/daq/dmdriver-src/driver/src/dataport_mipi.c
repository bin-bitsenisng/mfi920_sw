/* dataport_mipi.c
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

#include <inttypes.h>
#include <stdio.h>
#include "adi_dmdriver.h"
#include "adar690x_regs.h"
#include "localdefs.h"


typedef struct {
    uint32_t phy0_tst_ctrl0;
    uint32_t phy0_tst_ctrl1;
    uint32_t phy_if_cfg;
} phystate_t;

static const uint32_t mipi_freq_hz[ADI_DM_MIPI_CLK_NUM] = {
    1200000000UL, 1000000000UL, 800000000UL, 80000000UL, 650000000UL
};

static const uint32_t get_t_hs_prepare_max_data_lane[ADI_DM_MIPI_CLK_NUM] = {
    0x43, 0x39, 0x2F, 0x09, 0x24
};

static const uint32_t get_t_hs_prepare_max_clk_lane[ADI_DM_MIPI_CLK_NUM] = {
    0x3E, 0x34, 0x29, 0x03, 0x1F
};

static const uint32_t get_phy_stop_wait_time[ADI_DM_MIPI_CLK_NUM] = {
    0x2A, 0x25, 0x1F, 0x0D, 0x1B
};

static const uint32_t get_hsfreqrange[ADI_DM_MIPI_CLK_NUM] = {
    0x2B, 0x2A, 0x29, 0x00, 0x08
};

static const uint32_t get_vcorange[ADI_DM_MIPI_CLK_NUM] = {
    6, 5, 4, 0, 3
};

static const uint32_t get_icpctrl[ADI_DM_MIPI_CLK_NUM] = {
    11, 11, 6, 1, 6
};

static const uint32_t get_lpfctrl[ADI_DM_MIPI_CLK_NUM] = {
    8, 16, 4, 2, 4
};

static adi_dm_err_t init_mipi_dphy(adi_dm_mipi_clk_t mipi_clk, uint32_t ref_freq_hz, phystate_t *);
static adi_dm_err_t mipi_test_code_seq(int test_code, phystate_t *);
static adi_dm_err_t mipi_testdata_seq(int test_data, phystate_t *);
static void m_n_calc(uint32_t mipi_freq_hz, uint32_t ref_freq_hz, int *m, int *n);
static int gcd(int a, int b);
static int floorf_local(float a);
static int roundf_local(float a);

adi_dm_err_t adi_dm_MipiSetup(const adi_dm_mipi_setup_t * p)
{
    uint32_t v, b, m, fldval;
    adi_dm_num_t dm_num;
    adi_dm_err_t res;

    phystate_t phystate = {
        .phy0_tst_ctrl0 = REG_MIPICSI2_PHY0_TST_CTRL0_RESET,
        .phy0_tst_ctrl0 = REG_MIPICSI2_PHY0_TST_CTRL0_RESET,
        .phy_if_cfg = REG_MIPICSI2_PHY_IF_CFG_RESET,
    };

    printf("-->> Entering function adi_dm_MipiSetup\n");

    printf("Set to MIPI transmission mode, enable the mipi_buffer memory\n");
    printf("*** Misc. config for memory controller, inc crc seed is 0 ***\n");
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
        printf("*** crc poly is 0x82608EDB ***\n");
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_DATA_PORT_DATA_PORT_CRC32_POLY, 0x82608EDB);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    if (p->filter_output_bitwidth == ADI_DM_OUTPUT_BITWIDTH_16) {
        printf("*** Configuring Sample Size to 16 ***\n");
    } else if (p->filter_output_bitwidth == ADI_DM_OUTPUT_BITWIDTH_14) {
        printf("*** Configuring Sample Size to 14 ***\n");
    } else if (p->filter_output_bitwidth == ADI_DM_OUTPUT_BITWIDTH_12) {
        printf("*** Configuring Sample Size to 12 ***\n");
    } else {
        printf("ERROR: invalid filter_output_bitwidth\n");
        return ADI_DM_PARAMETER_ERROR;
    }
    m = ~BITM_MISC_MISC_FILTER_CTRL_FILTER_OUTPUT_BITWIDTH;
    b = p->filter_output_bitwidth << BITP_MISC_MISC_FILTER_CTRL_FILTER_OUTPUT_BITWIDTH;
    res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_MISC_MISC_FILTER_CTRL, m, b);
    if (res != ADI_DM_SUCCESS)
        return res;

    if (!((p->ref_freq_hz >= 40000000UL && p->ref_freq_hz <= 80000000UL))) {
        /* Generally only reference clocks in the range 40 to 80 MHz are supported.
         */
        printf("ERROR: Reference Clock Frequency [%" PRIu32 "] is not in range [40MHz:80Hz]\n", p->ref_freq_hz);
        return ADI_DM_PARAMETER_ERROR;
    }
    if (((p->ref_freq_hz / 2) < 28000000UL) && ((p->ref_freq_hz / 2) > 16000000UL)) {
        printf("Set mipi_pll_div_sel to 0x0\n");
        fldval = 0;
    } else if (((p->ref_freq_hz / 4) < 28000000UL) && ((p->ref_freq_hz / 4) > 16000000UL)) {
        printf("Set mipi_pll_div_sel to 0x1\n");
        fldval = 1;
    } else {
        /* The MIPI reference clock can be 17 <= Freq <= 27 MHz. It can be
         * derived from reference clock by dividing by 2 or 4, so that
         * translates to 34 to 54 MHz or 68 to 108 MHz. Generally only
         * reference clocks in the range 40 to 80 MHz are supported.
         */
        printf("ERROR: Reference Clock Frequency [%u] is not in range [40MHz:56Hz] or [64MHz:80Hz]\n", p->ref_freq_hz);
        return ADI_DM_PARAMETER_ERROR;
    }
    m = ~BITM_MISC_MISC_CLK_CTRL_MIPI_PLL_DIV_SEL;
    b = fldval << BITP_MISC_MISC_CLK_CTRL_MIPI_PLL_DIV_SEL;
    res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_MISC_MISC_CLK_CTRL, m, b);
    if (res != ADI_DM_SUCCESS)
        return res;

    if (p->mipi_clk >= ADI_DM_MIPI_CLK_NUM) {
        printf("ERROR: MIPI Clock Frequency is not [80MHz, 650MHz, 800MHz, 1000MHz, 1200MHz]\n");
        return ADI_DM_PARAMETER_ERROR;
    }

    phystate.phy0_tst_ctrl0 |= BITM_MIPICSI2_PHY0_TST_CTRL0_PHY0_TESTCLR;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_PHY0_TST_CTRL0, phystate.phy0_tst_ctrl0);
    if (res != ADI_DM_SUCCESS)
        return res;
    phystate.phy0_tst_ctrl0 &= ~BITM_MIPICSI2_PHY0_TST_CTRL0_PHY0_TESTCLR;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_PHY0_TST_CTRL0, phystate.phy0_tst_ctrl0);
    if (res != ADI_DM_SUCCESS)
        return res;

    res = init_mipi_dphy(p->mipi_clk, p->ref_freq_hz, &phystate);
    if (res != ADI_DM_SUCCESS)
        return res;
    printf("*** Setting MIPI output transmission frequency to be %u Hz***\n", mipi_freq_hz[p->mipi_clk]);

    uint32_t lane_en_num = 0;
    switch (p->num_lanes) {
    case ADI_DM_1_MIPI_LANE:
        printf("*** Configure number of DPHY data lanes to 1 ***\n");
        lane_en_num = 0;
        break;
    case ADI_DM_2_MIPI_LANES:
        printf("*** Configure number of DPHY data lanes to 2 ***\n");
        lane_en_num = 1;
        break;
    case ADI_DM_4_MIPI_LANES:
        printf("*** Configure number of DPHY data lanes to 4 ***\n");
        lane_en_num = 3;
        break;
    default:
        printf("ERROR: lane_en_num is not [1, 2, 4]\n");
        return ADI_DM_PARAMETER_ERROR;
    }
    phystate.phy_if_cfg &= ~BITM_MIPICSI2_PHY_IF_CFG_LANE_EN_NUM;
    phystate.phy_if_cfg |= (lane_en_num << BITP_MIPICSI2_PHY_IF_CFG_LANE_EN_NUM) & BITM_MIPICSI2_PHY_IF_CFG_LANE_EN_NUM;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_PHY_IF_CFG, phystate.phy_if_cfg);
    if (res != ADI_DM_SUCCESS)
        return res;

    uint32_t mipicsi2_csi2_resetn = REG_MIPICSI2_CSI2_RESETN_RESET | BITM_MIPICSI2_CSI2_RESETN_CSI2_RESETN_RW;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_CSI2_RESETN, mipicsi2_csi2_resetn);
    if (res != ADI_DM_SUCCESS)
        return res;

    if (p->continuous_clock) {
        printf("*** Setting MIPI continuous clock mode ***\n");
        v = REG_MIPICSI2_LPCLK_CTRL_RESET | BITM_MIPICSI2_LPCLK_CTRL_PHY_TXREQCLKHS_CON;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_LPCLK_CTRL, v);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    printf("*** ACTIVE PHASE ***\n");
    printf("*** PAYLOAD field enabled ***\n");
    printf("*** STATUS field %s ***\n", p->status_en ? "enabled" : "disabled");
    printf("*** DMA field disabled ***\n");
    printf("*** CRC field %s ***\n", p->crc32_en ? "enabled" : "disabled");
    printf("*** %s interleaving enabled ***\n", p->byte_interleaving ? "byte" : "sample");
    printf("*** %s first transmission ***\n", p->ls_byte_first ? "LS_byte" : "MS_byte");
    printf("*** word count value is inferred by hardware ***\n");
    printf("*** transmission start on dphy ready set to 0 ***\n");
    v = 0;
    if (p->ls_byte_first)
        v |= BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_ENDIANNESS;
    if (p->byte_interleaving)
        v |= BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_BYTE_OR_SAMPLE_INTERLEAVING;
    v |= BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_ACT_PH_RX_PAYLOAD_EN;
    if (p->status_en)
        v |= BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_ACT_PH_STATUS_EN;
    if (p->crc32_en)
        v |= BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_ACT_PH_CRC32_EN;
    v &= ~BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_DPHY_READY_OVERRIDE_EN;
    v |= BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_AUTO_CONFIG_WC;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG, v);
    if (res != ADI_DM_SUCCESS)
        return res;

    printf("*** Packet 0 as Frame start packet ***\n");
    v = 0;
    v |= 0x0 << BITP_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_DATA_TYPE;
    v |= 0x0 << BITP_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_VC_ID;
    v |= 0x1 << BITP_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_WC;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG, v);
    if (res != ADI_DM_SUCCESS)
        return res;

    if ((p->mipi_data_type != ADI_DM_RAW6)
        && (p->mipi_data_type != ADI_DM_RAW7)
        && (p->mipi_data_type != ADI_DM_RAW8)
        && (p->mipi_data_type != ADI_DM_RAW12)
        && (p->mipi_data_type != ADI_DM_RAW14)
        && (p->mipi_data_type != ADI_DM_RGB444)
        && (p->mipi_data_type != ADI_DM_RGB555)
        && (p->mipi_data_type != ADI_DM_RGB565)
        && (p->mipi_data_type != ADI_DM_YUV422_8B)) {
        printf("ERROR: mipi_data_type %02x is not supported\n", p->mipi_data_type);
        return ADI_DM_PARAMETER_ERROR;
    }
    v = 0;
    v |= (p->mipi_data_type << BITP_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_DATA_TYPE) & BITM_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_DATA_TYPE;
    v |= 0x0 << BITP_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_VC_ID;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG, v);
    if (res != ADI_DM_SUCCESS)
        return res;

    printf("*** Packet 2 as Frame end packet ***\n");
    v = 0;
    v |= 0x1 << BITP_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_DATA_TYPE;
    v |= 0x0 << BITP_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_VC_ID;
    v |= 0x1 << BITP_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_WC;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG, v);
    if (res != ADI_DM_SUCCESS)
        return res;

    printf("*** Packet 3 as Line start packet ***\n");
    v = 0;
    v |= 0x2 << BITP_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_DATA_TYPE;
    v |= 0x0 << BITP_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_VC_ID;
    v |= 0x1 << BITP_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_WC;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPI_CSI2_LINE_START_DATA_ID_WC_REG, v);
    if (res != ADI_DM_SUCCESS)
        return res;

    printf("*** Packet 4 as line end packet ***\n");
    v = 0;
    v |= 0x3 << BITP_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_DATA_TYPE;
    v |= 0x0 << BITP_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_VC_ID;
    v |= 0x1 << BITP_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_WC;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPI_CSI2_LINE_END_DATA_ID_WC_REG, v);
    if (res != ADI_DM_SUCCESS)
        return res;

    printf("*** CRC Poly left at default value ***\n");
    /* TODO: set DATA_PORT_DATA_PORT_CTL_REG_CRC32_SEED_SEL and DATA_PORT_DATA_PORT_CRC32_POLY_CRC32_POLY from params */

    printf("*** Auto configuration for all packets except packet1, enable all the packets ***\n");
    v = 0;
    v |= BITM_MIPI_CSI2_PKT_CTL_REG_FRAME_START_PKT_ACT_PH_EN;
    v |= BITM_MIPI_CSI2_PKT_CTL_REG_DATA_PKT_ACT_PH_EN;
    v |= BITM_MIPI_CSI2_PKT_CTL_REG_FRAME_END_PKT_ACT_PH_EN;
    v |= BITM_MIPI_CSI2_PKT_CTL_REG_LINE_START_PKT_ACT_PH_EN;
    v |= BITM_MIPI_CSI2_PKT_CTL_REG_LINE_END_PKT_ACT_PH_EN;
    // v |= BITM_MIPI_CSI2_PKT_CTL_REG_AUTO_CONFIG_FS;
    // v |= BITM_MIPI_CSI2_PKT_CTL_REG_AUTO_CONFIG_FE;
    // v |= BITM_MIPI_CSI2_PKT_CTL_REG_AUTO_CONFIG_LS;
    // v |= BITM_MIPI_CSI2_PKT_CTL_REG_AUTO_CONFIG_LE;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPI_CSI2_PKT_CTL_REG, v);
    if (res != ADI_DM_SUCCESS)
        return res;

    printf("*** Disable DMA ***\n");
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPI_CSI2_DMA_DATA_CNT_REG, 0);
    if (res != ADI_DM_SUCCESS)
        return res;

    if (p->status_en) {
        for (dm_num = 0; dm_num < adi_dm_active_digimmics; dm_num++) {
            printf("*** Setting the value of UserValue on rx channel0 (0x%02X), rx channel1 (0x%02X) ***\n", p->dm[dm_num].userval0, p->dm[dm_num].userval1);
            printf("*** Setting the value of UserValue on rx channel2 (0x%02X), rx channel3 (0x%02X) ***\n", p->dm[dm_num].userval2, p->dm[dm_num].userval3);
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

    printf("-->> Exiting function adi_dm_MipiSetup\n");
    return ADI_DM_SUCCESS;
}

adi_dm_err_t init_mipi_dphy(adi_dm_mipi_clk_t mipi_clk, uint32_t ref_freq_hz, phystate_t * phystate)
{
    adi_dm_err_t res;

    printf("--> Entering function init_mipi_dphy\n");
    int hsfreqrange = 0;        //MHz
    int vcorange = 0;
    int icpctrl = 0;
    int lpfctrl = 0;
    int n = 0;
    int m = 0;
    int m_8_5 = 0;
    int m_4_0 = 0;
    int vco = 0;
    int lpf = 0;
    int t_hs_prepare_max = 0;
    int t_hs_prepare_max_clk_lane = 0;
    int mipi_phy_stop_wait_time = 0;

    m_n_calc(mipi_freq_hz[mipi_clk], ref_freq_hz, &m, &n);

    //Test code to configure HS RX control of Lane0 (table 9.6)
    res = mipi_test_code_seq(0x44, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;
    //programming hsfreqrange according to table 5.1
    hsfreqrange = get_hsfreqrange[mipi_clk];
    hsfreqrange = hsfreqrange << 1;
    //{0,hsfreqrange,0}
    res = mipi_testdata_seq(hsfreqrange, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;

    //Test code to configure PLL input and loop divider ratios control (table 9.6)
    res = mipi_test_code_seq(0x19, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;
    //Bypass the PLL loop and input divider default values
    res = mipi_testdata_seq(0x30, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;

    //Test code to configure PLL input divider ratio (table 9.6)
    res = mipi_test_code_seq(0x17, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;
    //programming n value
    //{1'b0,n}
    res = mipi_testdata_seq(n, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;

    //Test code to configure HS TX clk lane Tclk-post(table 9.6)
    res = mipi_test_code_seq(0x65, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;
    res = mipi_testdata_seq(0x3F, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;

    // t_hs_prepare_max_data_lane
    res = mipi_test_code_seq(0x71, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;
    t_hs_prepare_max = get_t_hs_prepare_max_data_lane[mipi_clk];
    t_hs_prepare_max |= 0x80;
    res = mipi_testdata_seq(t_hs_prepare_max, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;

    // t_hs_prepare_max_clk_lane
    res = mipi_test_code_seq(0x61, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;
    t_hs_prepare_max_clk_lane = get_t_hs_prepare_max_clk_lane[mipi_clk];
    t_hs_prepare_max_clk_lane |= 0x80;
    res = mipi_testdata_seq(t_hs_prepare_max_clk_lane, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;

    //Test code to configure PLL loop divider ratio(table 9.6)
    res = mipi_test_code_seq(0x18, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;
    //programming m value set0
    m_4_0 = (m & 0x1F);
    // {1'b0,1'b00,m[4:0]}
    res = mipi_testdata_seq(m_4_0, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;
    //programming m value set1
    m_8_5 = ((m & 0x1E0) >> 5) | 0x80;
    // {1'b1,1'b000,m[8:5]}
    res = mipi_testdata_seq(m_8_5, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;

    vcorange = get_vcorange[mipi_clk];
    vcorange = vcorange << 3;
    vco = vcorange | 0x81;
    //PLL Bias Current Selector/Filter Capacitance Control/VCO Control
    res = mipi_test_code_seq(0x10, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;
    res = mipi_testdata_seq(vco, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;

    //PLL CP Control / PLL Lock Bypass for Initialization and for ULP
    icpctrl = get_icpctrl[mipi_clk];
    res = mipi_test_code_seq(0x11, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;
    res = mipi_testdata_seq(icpctrl, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;

    lpfctrl = get_lpfctrl[mipi_clk];
    lpf = (lpfctrl) | 0xC0;
    //PLL LPF and CP Control
    res = mipi_test_code_seq(0x12, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;
    res = mipi_testdata_seq(lpf, phystate);
    if (res != ADI_DM_SUCCESS)
        return res;

    phystate->phy0_tst_ctrl0 &= ~BITM_MIPICSI2_PHY0_TST_CTRL0_PHY0_TESTCLK;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_PHY0_TST_CTRL0, phystate->phy0_tst_ctrl0);
    if (res != ADI_DM_SUCCESS)
        return res;

    uint32_t mipicsi2_phy_rstz = REG_MIPICSI2_PHY_RSTZ_RESET;
    mipicsi2_phy_rstz |= BITM_MIPICSI2_PHY_RSTZ_PHY_ENABLECLK;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_PHY_RSTZ, mipicsi2_phy_rstz);
    if (res != ADI_DM_SUCCESS)
        return res;

    mipicsi2_phy_rstz |= BITM_MIPICSI2_PHY_RSTZ_PHY_SHUTDOWNZ;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_PHY_RSTZ, mipicsi2_phy_rstz);
    if (res != ADI_DM_SUCCESS)
        return res;

    mipicsi2_phy_rstz |= BITM_MIPICSI2_PHY_RSTZ_PHY_RSTZ;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_PHY_RSTZ, mipicsi2_phy_rstz);
    if (res != ADI_DM_SUCCESS)
        return res;

    mipi_phy_stop_wait_time = get_phy_stop_wait_time[mipi_clk];
    phystate->phy_if_cfg &= ~BITM_MIPICSI2_PHY_IF_CFG_PHY_STOP_WAIT_TIME;
    phystate->phy_if_cfg |= (mipi_phy_stop_wait_time << BITP_MIPICSI2_PHY_IF_CFG_PHY_STOP_WAIT_TIME) & BITM_MIPICSI2_PHY_IF_CFG_PHY_STOP_WAIT_TIME;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_PHY_IF_CFG, phystate->phy_if_cfg);
    if (res != ADI_DM_SUCCESS)
        return res;

    printf("--> Leaving function init_mipi_dphy\n");
    return ADI_DM_SUCCESS;
}

static adi_dm_err_t mipi_test_code_seq(int test_code, phystate_t * phystate)
{
    adi_dm_err_t res;

    printf("--> Entering mipi_test_code_seq 0x%02x\n", test_code);
    phystate->phy0_tst_ctrl0 &= ~BITM_MIPICSI2_PHY0_TST_CTRL0_PHY0_TESTCLK;
    phystate->phy0_tst_ctrl0 |= (0x1 << BITP_MIPICSI2_PHY0_TST_CTRL0_PHY0_TESTCLK) & BITM_MIPICSI2_PHY0_TST_CTRL0_PHY0_TESTCLK;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_PHY0_TST_CTRL0, phystate->phy0_tst_ctrl0);
    if (res != ADI_DM_SUCCESS)
        return res;

    phystate->phy0_tst_ctrl1 &= ~BITM_MIPICSI2_PHY0_TST_CTRL1_PHY0_TESTDIN;
    phystate->phy0_tst_ctrl1 |= (test_code << BITP_MIPICSI2_PHY0_TST_CTRL1_PHY0_TESTDIN) & BITM_MIPICSI2_PHY0_TST_CTRL1_PHY0_TESTDIN;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_PHY0_TST_CTRL1, phystate->phy0_tst_ctrl1);
    if (res != ADI_DM_SUCCESS)
        return res;

    phystate->phy0_tst_ctrl1 |= BITM_MIPICSI2_PHY0_TST_CTRL1_PHY0_TESTEN;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_PHY0_TST_CTRL1, phystate->phy0_tst_ctrl1);
    if (res != ADI_DM_SUCCESS)
        return res;

    phystate->phy0_tst_ctrl0 &= ~BITM_MIPICSI2_PHY0_TST_CTRL0_PHY0_TESTCLK;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_PHY0_TST_CTRL0, phystate->phy0_tst_ctrl0);
    if (res != ADI_DM_SUCCESS)
        return res;

    phystate->phy0_tst_ctrl1 &= ~BITM_MIPICSI2_PHY0_TST_CTRL1_PHY0_TESTEN;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_PHY0_TST_CTRL1, phystate->phy0_tst_ctrl1);
    if (res != ADI_DM_SUCCESS)
        return res;
    printf("--> Exiting mipi_test_code_seq\n");
    return ADI_DM_SUCCESS;
}

static adi_dm_err_t mipi_testdata_seq(int test_data, phystate_t * phystate)
{
    adi_dm_err_t res;

    printf("--> Entering mipi_testdata_seq 0x%02x\n", test_data);
    if ((phystate->phy0_tst_ctrl0 & BITM_MIPICSI2_PHY0_TST_CTRL0_PHY0_TESTCLK) != 0x0) {
        phystate->phy0_tst_ctrl0 &= ~BITM_MIPICSI2_PHY0_TST_CTRL0_PHY0_TESTCLK;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_PHY0_TST_CTRL0, phystate->phy0_tst_ctrl0);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    phystate->phy0_tst_ctrl1 &= ~BITM_MIPICSI2_PHY0_TST_CTRL1_PHY0_TESTDIN;
    phystate->phy0_tst_ctrl1 |= (test_data << BITP_MIPICSI2_PHY0_TST_CTRL1_PHY0_TESTDIN) & BITM_MIPICSI2_PHY0_TST_CTRL1_PHY0_TESTDIN;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_PHY0_TST_CTRL1, phystate->phy0_tst_ctrl1);
    if (res != ADI_DM_SUCCESS)
        return res;

    phystate->phy0_tst_ctrl0 &= ~BITM_MIPICSI2_PHY0_TST_CTRL0_PHY0_TESTCLK;
    phystate->phy0_tst_ctrl0 |= (0x1 << BITP_MIPICSI2_PHY0_TST_CTRL0_PHY0_TESTCLK) & BITM_MIPICSI2_PHY0_TST_CTRL0_PHY0_TESTCLK;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPICSI2_PHY0_TST_CTRL0, phystate->phy0_tst_ctrl0);
    if (res != ADI_DM_SUCCESS)
        return res;
    printf("--> Exiting mipi_testdata_seq\n");
    return ADI_DM_SUCCESS;
}

static void m_n_calc(uint32_t mipi_freq_hz, uint32_t ref_freq_hz, int *m, int *n)
{
    float required_clock = (float) mipi_freq_hz / 1e6f;
    float reference_clock = (float) ref_freq_hz / 1e6f;
    float input = required_clock / reference_clock;
    int integral = floorf_local(input);
    float frac = input - integral;
    int M, N, change_mn_flag, factor;
    const int precision = 1000; // This is the accuracy.
    printf("*** GCD Function called ***\n");
    int gcd_ = gcd(roundf_local(frac * precision), precision);
    int denominator = precision / gcd_;
    int numerator = roundf_local(frac * precision) / gcd_;

    printf("*** required_clock = %f reference_clock = %f inp = %f, intergral = %d , gcd_ = %d ,frac = %f ***\n", required_clock, reference_clock, input, integral, gcd_, frac);

    numerator = numerator + (integral * denominator);

    //Due to the use of a "by 2 pre-scaler," the range of the feedback
    //multiplication value M is limited to even division numbers.
    if ((numerator % 2) != 0) {
        numerator = numerator * 2;
        denominator = denominator * 2;
    }

    *m = numerator - 1;
    *n = denominator - 1;

    printf("*** denominator = %d , numerator = %d ***\n", denominator, numerator);

    change_mn_flag = 0;
    factor = 1;
    N = *n + 1;
    while (!((40 >= reference_clock / N) && (reference_clock / N >= 5))) {
        N = N * 2;
        change_mn_flag = 1;
    }

    if (change_mn_flag == 1) {
        change_mn_flag = 0;
        factor = N / denominator;
        M = (factor * numerator);
        *m = M - 1;
        *n = N - 1;
        printf("*** MN changed ***\n");
    }

    printf("*** m = %d , n = %d factor = %d ***\n", *m + 1, *n + 1, factor);
}

static int gcd(int a, int b)
{
    if (a == 0) {
        return b;
    } else if (b == 0) {
        return a;
    }
    if (a < b) {
        return gcd(a, b % a);
    } else {
        return gcd(b, a % b);
    }
}

static int floorf_local(float a)
{
    return (int) (a);
}

static int roundf_local(float a)
{
    return (int) (a + 0.5);
}
