/* 3_3_local_helper.h
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
#include "legacy/3_3/adi_dmdriver.h"

static inline adi_dm_ramp_config_t adi_dm_convert_ramp_config(const adi_dm_3_3_ramp_config_t * ramp_config)
{
    adi_dm_num_t dm_num;
    adi_dm_ramp_config_t p = {
        .ramp_count = ramp_config->ramp_count,
        .pga_shunt_en = ramp_config->pga_shunt_en,
        .pga_shunt_start_del = ramp_config->pga_shunt_start_del,
        .pga_shunt_stop_del = ramp_config->pga_shunt_stop_del,
        .filter_decim_ratio = ramp_config->filter_decim_ratio,
        .filter_valid_delay = ramp_config->filter_valid_delay
    };

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        p.dm[dm_num].vga_sync_data_valid = ramp_config->dm[dm_num].vga_sync_data_valid;
        p.dm[dm_num].vga_on_patt = ramp_config->dm[dm_num].vga_on_patt;
        p.dm[dm_num].pa_off_time = ramp_config->dm[dm_num].pa_off_time;
        p.dm[dm_num].vga_gauss_dis = ramp_config->dm[dm_num].vga_gauss_dis;
        p.dm[dm_num].vga_gain_steps = ramp_config->dm[dm_num].vga_gain_steps;
        p.dm[dm_num].vga_gain_step_div = ramp_config->dm[dm_num].vga_gain_step_div;
        p.dm[dm_num].phase_mod_en = ramp_config->dm[dm_num].phase_mod_en;
        p.dm[dm_num].phase_delay_en = ramp_config->dm[dm_num].phase_delay_en;
    }
    return p;
}
