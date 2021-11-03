/* 3_0_calc_ramp.c
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
#include <string.h>

adi_dm_err_t adi_dm_3_0_CalcRamp(adi_dm_3_0_calc_ramp_t * in, adi_dm_3_0_sys_profile_t * out)
{
    const uint32_t filter_valid_delay = 92;     /* 3.0 used a fixed value */

    adi_dm_err_t res;
    adi_dm_ramp_shape_t shape;
    adi_dm_ramp_profile_t profile;
    adi_dm_ramp_config_t config;
    adi_dm_actual_ramp_shape_t actual;
    uint32_t filter_valid_delay_time_afe;
    uint32_t afe_on_time;
    float filter_valid_delay_time_us;
    double adcpll_freq_mhz, freq_afe_clk;
    uint32_t decim_factor_24_32;
    adi_dm_num_t dm_num;
    bool fast_ramp_mode;

    decim_factor_24_32 = (in->decim_factor % 24 == 0) ? 24 : 32;
    adcpll_freq_mhz = in->adcpll_freq_hz / 1e6;
    freq_afe_clk = adcpll_freq_mhz / decim_factor_24_32;
    filter_valid_delay_time_afe = filter_valid_delay * (in->decim_factor / decim_factor_24_32);
    filter_valid_delay_time_us = (float) (filter_valid_delay_time_afe / freq_afe_clk);

    memset(&shape, 0, sizeof(shape));
    shape.slope0_time_us = in->slope0_time_us;
    shape.slope1_time_us = in->slope1_time_us;
    shape.delay0_time_us = in->delay0_time_us;
    shape.delay1_time_us = in->delay1_time_us;
    shape.delay2_time_us = in->delay2_time_us;
    shape.ramp_bw_Mhz = in->ramp_bw_mhz;
    shape.num_samples = in->num_samples;
    if (in->sample_start_time_us == 0.0F) {
        shape.sample_start_time_us = 0.0F;
    } else {
        shape.sample_start_time_us = in->sample_start_time_us + filter_valid_delay_time_us;
    }
    shape.pga_shunt_en = in->pga_shunt_en;
    shape.pga_shunt_start_del_us = in->pga_shunt_start_del_us;
    shape.pga_shunt_stop_del_us = in->pga_shunt_stop_del_us;
    shape.filter_valid_delay = filter_valid_delay;
    shape.decim_ratio = in->decim_factor;
    shape.ref_freq_hz = in->ref_freq_hz;

    res = adi_dm_CalcRamp(&shape, &profile, &config, &actual);

    afe_on_time = (profile.num_samples + filter_valid_delay) * (in->decim_factor / decim_factor_24_32);
    fast_ramp_mode = (profile.del_0 == 0 && profile.del_1 == 0 && profile.del_2 == 0 && profile.ramp_steps_1 == 1);

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        out->ramp[dm_num].del0_steps = profile.del_0;
        out->ramp[dm_num].slp0_steps = profile.ramp_steps_0;
        out->ramp[dm_num].del1_steps = profile.del_1;
        out->ramp[dm_num].vga_gain = in->vga_gain;
        out->ramp[dm_num].pa_pwr_con = in->pa_power;
        out->ramp[dm_num].slp1_steps = profile.ramp_steps_1;
        out->ramp[dm_num].del2_steps = profile.del_2;
        out->ramp[dm_num].slp0_dev = profile.ramp_dev_0;
        out->ramp[dm_num].slp1_dev = profile.ramp_dev_1;
        out->ramp[dm_num].tx_pattern = (in->tx_select >> (6 * dm_num)) & 0x7;
        out->ramp[dm_num].pa_on_patt = 0x3E;
        out->ramp[dm_num].dma_on_patt = 1;
        out->ramp[dm_num].ramp_stat_bit_0 = 0;
        out->ramp[dm_num].ramp_stat_bit_1 = 0;
        out->ramp[dm_num].ramp_stat_bit_2 = 0;
        out->ramp[dm_num].afe_start_off_time = profile.afe_start_off_time;
        out->ramp[dm_num].num_samples = profile.num_samples;
        out->ramp[dm_num].afe_on_time = afe_on_time;
        out->ramp[dm_num].afe_ramp_time = profile.afe_ramp_time;
        out->ramp[dm_num].pa0_phase = in->pa_phase[3 * dm_num + 0];
        out->ramp[dm_num].pa1_phase = in->pa_phase[3 * dm_num + 1];
        out->ramp[dm_num].pa2_phase = in->pa_phase[3 * dm_num + 2];
        out->ramp[dm_num].pa0_phase_dev = in->pa_phase_dev[3 * dm_num + 0];
        out->ramp[dm_num].pa1_phase_dev = in->pa_phase_dev[3 * dm_num + 1];
        out->ramp[dm_num].pa2_phase_dev = in->pa_phase_dev[3 * dm_num + 2];
        out->ramp[dm_num].phase_step = in->pa_phase_step[dm_num];
        out->ramp[dm_num].del0_actual_time_us = actual.delay0_time_us;
        out->ramp[dm_num].del1_actual_time_us = actual.delay1_time_us;
        out->ramp[dm_num].del2_actual_time_us = actual.delay2_time_us;
        out->ramp[dm_num].slp0_actual_time_us = actual.slope0_time_us;
        out->ramp[dm_num].slp1_actual_time_us = actual.slope1_time_us;
        out->ramp[dm_num].afe_start_off_time_us = actual.afe_start_off_time_us;
        out->ramp[dm_num].afe_on_time_us = (float) (afe_on_time / freq_afe_clk);;
        out->ramp[dm_num].afe_ramp_time_us = actual.afe_ramp_time_us;
        out->ramp[dm_num].afe_clk_rate_Mhz = actual.afe_freq_Mhz;
        out->ramp[dm_num].filter_valid_delay_time_us = actual.filter_valid_delay_time_us;
        out->ramp[dm_num].rfpll_detail.ramp_bw = actual.ramp_bw_Mhz * 1e6F;
        out->ramp[dm_num].rfpll_detail.mimo_seq_val = in->mimo_seq_val;
        out->ramp[dm_num].rfpll_detail.mimo_seq_len = in->mimo_seq_len;
        out->ramp[dm_num].rfpll_detail.ramp_time_us = actual.afe_ramp_time_us;
        out->ramp[dm_num].rfpll_detail.fast_ramp_mode = fast_ramp_mode;
        out->ramp[dm_num].rfpll_detail.pga_shunt_en = config.pga_shunt_en;
        out->ramp[dm_num].rfpll_detail.pga_shunt_start_del = config.pga_shunt_start_del;
        out->ramp[dm_num].rfpll_detail.pga_shunt_stop_del = config.pga_shunt_stop_del;
    }
    return res;
}
