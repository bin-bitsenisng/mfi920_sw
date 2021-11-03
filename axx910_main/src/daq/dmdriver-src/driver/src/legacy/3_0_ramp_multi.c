/* 3_0_ramp_multi.c
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
#include "3_3_local_helper.h"
#include "adar690x_fw.h"
#include "../localdefs.h"
#include <string.h>
#include <stdlib.h>

extern adi_dm_err_t adi_dm_write_ramp_config8(const adi_dm_3_3_ramp_config_t * p);
extern uint32_t adi_dm_3_0_decim_ratio; /* set by adi_dm_3_0_PowerUp */

extern uint32_t adi_dm_3_0_dma_mem_limit;

adi_dm_err_t adi_dm_3_0_RampSetupMulti(adi_dm_3_0_ramp_setup_multi_t * p)
{
    adi_dm_err_t res;
    uint32_t bpid;
    adi_dm_3_0_burst_profile_t bp = {
        .num_ramps_in_seq = p->num_ramps_in_seq,
        .num_seq_in_burst = p->num_seq_in_burst,
        .sys = p->sys,
    };

    res = adi_dm_3_0_ConfigRfpllForBurstProfile(&bp, p->ref_freq_hz, p->ramp_start_freq_ghz);
    if (res != ADI_DM_SUCCESS)
        return res;

    adi_dm_3_0_dma_mem_limit = 0;
    res = adi_dm_3_0_StoreBurstProfile(&bp, &bpid);
    if (res != ADI_DM_SUCCESS)
        return res;

    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_3_0_StoreBurstProfile(adi_dm_3_0_burst_profile_t * p, uint32_t * bpid)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    adi_dm_burst_profile_t s;
    uint32_t i;
    bool first_burst_profile = (adi_dm_3_0_dma_mem_limit == 0);

    /* adi_dm_BurstProfileSetup writes the profile to device memory */
    (void) memset(&s, 0, sizeof(s));
    s.ramp_profile = calloc(p->num_ramps_in_seq, sizeof(*s.ramp_profile));
    if (s.ramp_profile == NULL) {
        return ADI_DM_FAIL;
    }
    for (i = 0UL; i < p->num_ramps_in_seq; i++) {
        s.ramp_profile[i].del_0 = p->sys[i].ramp[ADI_DM_MASTER].del0_steps;
        s.ramp_profile[i].del_1 = p->sys[i].ramp[ADI_DM_MASTER].del1_steps;
        s.ramp_profile[i].del_2 = p->sys[i].ramp[ADI_DM_MASTER].del2_steps;
        s.ramp_profile[i].ramp_steps_0 = p->sys[i].ramp[ADI_DM_MASTER].slp0_steps;
        s.ramp_profile[i].ramp_steps_1 = p->sys[i].ramp[ADI_DM_MASTER].slp1_steps;
        s.ramp_profile[i].ramp_dev_0 = p->sys[i].ramp[ADI_DM_MASTER].slp0_dev;
        s.ramp_profile[i].ramp_dev_1 = p->sys[i].ramp[ADI_DM_MASTER].slp1_dev;
        s.ramp_profile[i].afe_start_off_time = p->sys[i].ramp[ADI_DM_MASTER].afe_start_off_time;
        s.ramp_profile[i].afe_ramp_time = p->sys[i].ramp[ADI_DM_MASTER].afe_ramp_time;
        s.ramp_profile[i].num_samples = p->sys[i].ramp[ADI_DM_MASTER].num_samples;
        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            s.ramp_profile[i].dm[dm_num].tx_pattern = p->sys[i].ramp[dm_num].tx_pattern;        /* top 3 bits ignored in 3.0 too */
            s.ramp_profile[i].dm[dm_num].ramp_stat_bit_0 = p->sys[i].ramp[dm_num].ramp_stat_bit_0;
            s.ramp_profile[i].dm[dm_num].ramp_stat_bit_1 = p->sys[i].ramp[dm_num].ramp_stat_bit_1;
            s.ramp_profile[i].dm[dm_num].ramp_stat_bit_2 = p->sys[i].ramp[dm_num].ramp_stat_bit_2;
            s.ramp_profile[i].dm[dm_num].pa0_phase = p->sys[i].ramp[dm_num].pa0_phase;
            s.ramp_profile[i].dm[dm_num].pa1_phase = p->sys[i].ramp[dm_num].pa1_phase;
            s.ramp_profile[i].dm[dm_num].pa2_phase = p->sys[i].ramp[dm_num].pa2_phase;
            s.ramp_profile[i].dm[dm_num].phase_step = p->sys[i].ramp[dm_num].phase_step;
            s.ramp_profile[i].dm[dm_num].pa0_phase_dev = p->sys[i].ramp[dm_num].pa0_phase_dev;
            s.ramp_profile[i].dm[dm_num].pa1_phase_dev = p->sys[i].ramp[dm_num].pa1_phase_dev;
            s.ramp_profile[i].dm[dm_num].pa2_phase_dev = p->sys[i].ramp[dm_num].pa2_phase_dev;
        }
    }
    s.num_ramps_in_seq = p->num_ramps_in_seq;
    s.num_seq_in_burst = p->num_seq_in_burst;
    res = adi_dm_BurstProfileSetup(&s, &adi_dm_3_0_dma_mem_limit, bpid);
    free(s.ramp_profile);
    if (res != ADI_DM_SUCCESS)
        return res;

    if (!first_burst_profile) {
        /* 3.0 used to make the last stored profile current */
        res = adi_dm_SelectBurstProfile(*bpid);
        if (res != ADI_DM_SUCCESS)
            return res;
    } else {
        /* 3.0 used to initialize DMA controller on first profile */
        adi_dm_3_3_dma_ramp_setup_t t;

        (void) memset(&t, 0, sizeof(t));

        t.ramp_config.ramp_count = p->num_ramps_in_seq * p->num_seq_in_burst;
        if (p->sys[0].ramp[ADI_DM_MASTER].rfpll_detail.pga_shunt_en) {
            t.ramp_config.pga_shunt_en = 1U;
            t.ramp_config.pga_shunt_start_del = p->sys[0].ramp[ADI_DM_MASTER].rfpll_detail.pga_shunt_start_del;
            t.ramp_config.pga_shunt_stop_del = p->sys[0].ramp[ADI_DM_MASTER].rfpll_detail.pga_shunt_stop_del;
        } else {
            t.ramp_config.pga_shunt_en = 0U;
            t.ramp_config.pga_shunt_start_del = 0U;
            t.ramp_config.pga_shunt_stop_del = 0U;
        }
        t.ramp_config.filter_decim_ratio = adi_dm_3_0_decim_ratio;
        t.ramp_config.filter_valid_delay = 92;  /* fixed value used in 3.0 */

        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            t.ramp_config.dm[dm_num].vga_sync_data_valid = 0U;
            t.ramp_config.dm[dm_num].vga_on_patt = p->sys[0].ramp[dm_num].pa_on_patt;
            t.ramp_config.dm[dm_num].pa_off_time = 0U;
            t.ramp_config.dm[dm_num].vga_gauss_dis = 1U;
            t.ramp_config.dm[dm_num].vga_gain_steps = 7U;
            t.ramp_config.dm[dm_num].vga_gain_step_div = 2U;
            t.ramp_config.dm[dm_num].ramp_status_0 = 0U;
            t.ramp_config.dm[dm_num].ramp_status_1 = 0U;
            t.ramp_config.dm[dm_num].ramp_status_2 = 0U;
        }
        t.bpid = *bpid;

        res = adi_dm_3_3_DmaRampSetup(&t);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_3_0_GetCurrentBurstProfileId(uint32_t * bpid)
{
    uint32_t src_ptr;
    if (bpid == NULL)
        return ADI_DM_PARAMETER_ERROR;  /* null pointer */
    if (adi_dm_3_0_dma_mem_limit == 0UL)
        return ADI_DM_PARAMETER_ERROR;  /* no burst profile in memory */
    /* the burst profile 'identifier' the channel src_ptr to restore */
    src_ptr = adi_dm_3_2_Read(ADI_DM_MASTER, DMA_RAMPGEN_CHAN_SRC_PTR);
    if (src_ptr < DMA_MEMORY_START || src_ptr >= adi_dm_3_0_dma_mem_limit) {
        return ADI_DM_PARAMETER_ERROR;  /* something went wrong */
    }
    /* the bpid is just the src_ptr when tx_overlay is supported */
    *bpid = src_ptr;
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_3_0_SetCurrentBurstProfile(uint32_t bpid)
{
    return adi_dm_SelectBurstProfile(bpid);
}

adi_dm_err_t adi_dm_3_0_ConfigRfpllForBurstProfile(adi_dm_3_0_burst_profile_t * p, uint32_t ref_freq_hz, float ramp_start_freq_ghz)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    uint64_t new_ramp_start_freq_hz, old_ramp_start_freq_hz;
    float new_ramp_bw_Mhz, old_ramp_bw_Mhz;
    uint32_t i;
    adi_dm_3_3_ramp_config_t legacy_ramp_config;

    /* 3.0 used to bundle writing legacy_ramp_config with rerunning firmware cals */
    (void) memset(&legacy_ramp_config, 0, sizeof(legacy_ramp_config));

    legacy_ramp_config.ramp_count = p->num_ramps_in_seq * p->num_seq_in_burst;
    if (p->sys[0].ramp[ADI_DM_MASTER].rfpll_detail.pga_shunt_en) {
        legacy_ramp_config.pga_shunt_en = 1U;
        legacy_ramp_config.pga_shunt_start_del = p->sys[0].ramp[ADI_DM_MASTER].rfpll_detail.pga_shunt_start_del;
        legacy_ramp_config.pga_shunt_stop_del = p->sys[0].ramp[ADI_DM_MASTER].rfpll_detail.pga_shunt_stop_del;
    } else {
        legacy_ramp_config.pga_shunt_en = 0U;
        legacy_ramp_config.pga_shunt_start_del = 0U;
        legacy_ramp_config.pga_shunt_stop_del = 0U;
    }
    legacy_ramp_config.filter_decim_ratio = adi_dm_3_0_decim_ratio;
    legacy_ramp_config.filter_valid_delay = 92; /* fixed value used in 3.0 */

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        legacy_ramp_config.dm[dm_num].vga_sync_data_valid = 0U;
        legacy_ramp_config.dm[dm_num].vga_on_patt = p->sys[0].ramp[dm_num].pa_on_patt;
        legacy_ramp_config.dm[dm_num].pa_off_time = 0U;
        legacy_ramp_config.dm[dm_num].vga_gauss_dis = 1U;
        legacy_ramp_config.dm[dm_num].vga_gain_steps = 7U;
        legacy_ramp_config.dm[dm_num].vga_gain_step_div = 2U;
        legacy_ramp_config.dm[dm_num].ramp_status_0 = 0U;
        legacy_ramp_config.dm[dm_num].ramp_status_1 = 0U;
        legacy_ramp_config.dm[dm_num].ramp_status_2 = 0U;
    }

    adi_dm_ramp_config_t ramp_config = adi_dm_convert_ramp_config(&legacy_ramp_config);
    res = adi_dm_ramp_config(&ramp_config, NULL);
    if (res != ADI_DM_SUCCESS)
        return res;

    /* Reconfigure RFPLL if necessary. */
    new_ramp_start_freq_hz = (uint64_t) (ramp_start_freq_ghz * 1e9);
    old_ramp_start_freq_hz = adi_dm_3_2_ReadU64(ADI_DM_MASTER, ADI_ADAR690x_CFG_RAMP_START_FREQ_HZ);

    new_ramp_bw_Mhz = p->sys[0].ramp[ADI_DM_MASTER].rfpll_detail.ramp_bw / 1e6F;
    old_ramp_bw_Mhz = adi_dm_3_2_ReadF32(ADI_DM_MASTER, ADI_ADAR690x_CFG_RAMP_BW_MHZ);
    for (i = 0; i < p->num_ramps_in_seq; i++) {
        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            float ramp_bw_Mhz = p->sys[i].ramp[dm_num].rfpll_detail.ramp_bw / 1e6F;
            if (ramp_bw_Mhz > new_ramp_bw_Mhz) {
                new_ramp_bw_Mhz = ramp_bw_Mhz;
            }
        }
    }
    if (new_ramp_start_freq_hz != old_ramp_start_freq_hz || new_ramp_bw_Mhz != old_ramp_bw_Mhz) {
        adi_dm_rfpll_reconfig_t t;
        t.ramp_start_freq_hz = new_ramp_start_freq_hz;
        t.ramp_bw_Mhz = new_ramp_bw_Mhz;

        res = adi_dm_RfpllReconfig(&t);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    return ADI_DM_SUCCESS;
}
