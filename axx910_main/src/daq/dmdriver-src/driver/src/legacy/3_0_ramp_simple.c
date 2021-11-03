/* 3_0_ramp_simple.c
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
#include <string.h>

extern uint32_t adi_dm_3_0_decim_ratio; /* set by adi_dm_3_0_PowerUp */

adi_dm_err_t adi_dm_3_0_RampSetupSimple(adi_dm_3_0_ramp_setup_simple_t * p)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    adi_dm_3_3_builtin_mimo_setup_t s;
    uint64_t new_ramp_start_freq_hz, old_ramp_start_freq_hz;
    float new_ramp_bw_Mhz, old_ramp_bw_Mhz;

    /* Configure builtin MIMO mode. */
    (void) memset(&s, 0, sizeof(s));
    s.ramp_config.ramp_count = p->ramp_count;
    if (p->sys.ramp[ADI_DM_MASTER].rfpll_detail.pga_shunt_en) {
        s.ramp_config.pga_shunt_en = 1U;
        s.ramp_config.pga_shunt_start_del = p->sys.ramp[ADI_DM_MASTER].rfpll_detail.pga_shunt_start_del;
        s.ramp_config.pga_shunt_stop_del = p->sys.ramp[ADI_DM_MASTER].rfpll_detail.pga_shunt_stop_del;
    } else {
        s.ramp_config.pga_shunt_en = 0U;
    }
    s.ramp_config.filter_decim_ratio = adi_dm_3_0_decim_ratio;  /* Set in power_up */
    s.ramp_config.filter_valid_delay = 92;      /* fixed value used in 3.0 */

    s.ramp_profile.del_0 = p->sys.ramp[ADI_DM_MASTER].del0_steps;
    s.ramp_profile.del_1 = p->sys.ramp[ADI_DM_MASTER].del1_steps;
    s.ramp_profile.del_2 = p->sys.ramp[ADI_DM_MASTER].del2_steps;
    s.ramp_profile.ramp_steps_0 = p->sys.ramp[ADI_DM_MASTER].slp0_steps;
    s.ramp_profile.ramp_steps_1 = p->sys.ramp[ADI_DM_MASTER].slp1_steps;
    s.ramp_profile.ramp_dev_0 = p->sys.ramp[ADI_DM_MASTER].slp0_dev;
    s.ramp_profile.ramp_dev_1 = p->sys.ramp[ADI_DM_MASTER].slp1_dev;
    s.ramp_profile.afe_start_off_time = p->sys.ramp[ADI_DM_MASTER].afe_start_off_time;
    s.ramp_profile.afe_ramp_time = p->sys.ramp[ADI_DM_MASTER].afe_ramp_time;
    s.ramp_profile.num_samples = p->sys.ramp[ADI_DM_MASTER].num_samples;

    s.mimo_seq_len = p->sys.ramp[ADI_DM_MASTER].rfpll_detail.mimo_seq_len;

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        s.ramp_config.dm[dm_num].vga_sync_data_valid = 0U;
        s.ramp_config.dm[dm_num].vga_on_patt = p->sys.ramp[dm_num].pa_on_patt;
        s.ramp_config.dm[dm_num].pa_off_time = 0U;
        s.ramp_config.dm[dm_num].vga_gauss_dis = 1U;
        s.ramp_config.dm[dm_num].vga_gain_steps = 7U;
        s.ramp_config.dm[dm_num].vga_gain_step_div = 2U;
        s.ramp_config.dm[dm_num].ramp_status_0 = 0U;
        s.ramp_config.dm[dm_num].ramp_status_1 = 0U;
        s.ramp_config.dm[dm_num].ramp_status_2 = 0U;

        s.ramp_profile.dm[dm_num].tx_pattern = p->sys.ramp[dm_num].tx_pattern;  /* top 3 bits ignored in 3.0 too */
        s.ramp_profile.dm[dm_num].ramp_stat_bit_0 = p->sys.ramp[dm_num].ramp_stat_bit_0;
        s.ramp_profile.dm[dm_num].ramp_stat_bit_1 = p->sys.ramp[dm_num].ramp_stat_bit_1;
        s.ramp_profile.dm[dm_num].ramp_stat_bit_2 = p->sys.ramp[dm_num].ramp_stat_bit_2;
        s.ramp_profile.dm[dm_num].pa0_phase = p->sys.ramp[dm_num].pa0_phase;
        s.ramp_profile.dm[dm_num].pa1_phase = p->sys.ramp[dm_num].pa1_phase;
        s.ramp_profile.dm[dm_num].pa2_phase = p->sys.ramp[dm_num].pa2_phase;
        s.ramp_profile.dm[dm_num].phase_step = p->sys.ramp[dm_num].phase_step;
        s.ramp_profile.dm[dm_num].pa0_phase_dev = p->sys.ramp[dm_num].pa0_phase_dev;
        s.ramp_profile.dm[dm_num].pa1_phase_dev = p->sys.ramp[dm_num].pa1_phase_dev;
        s.ramp_profile.dm[dm_num].pa2_phase_dev = p->sys.ramp[dm_num].pa2_phase_dev;

        s.dm[dm_num].mimo_seq_val = p->sys.ramp[dm_num].rfpll_detail.mimo_seq_val;
    }

    res = adi_dm_3_3_BuiltinMimoSetup(&s);
    if (res != ADI_DM_SUCCESS)
        return res;

    /* Check whether we are changing start frequency or ramp bandwidth. */
    new_ramp_start_freq_hz = (uint64_t) (p->ramp_start_freq_ghz * 1e9);
    old_ramp_start_freq_hz = adi_dm_3_2_ReadU64(ADI_DM_MASTER, ADI_ADAR690x_CFG_RAMP_START_FREQ_HZ);
    new_ramp_bw_Mhz = p->sys.ramp[ADI_DM_MASTER].rfpll_detail.ramp_bw / 1e6F;
    old_ramp_bw_Mhz = adi_dm_3_2_ReadF32(ADI_DM_MASTER, ADI_ADAR690x_CFG_RAMP_BW_MHZ);

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
