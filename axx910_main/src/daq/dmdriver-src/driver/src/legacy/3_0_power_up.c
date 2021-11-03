/* 3_0_power_up.c
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

uint32_t adi_dm_3_0_decim_ratio;
uint32_t adi_dm_3_0_dma_mem_limit;

adi_dm_err_t adi_dm_3_0_PowerUp(adi_dm_3_0_power_up_t * p)
{
    adi_dm_power_up_t s;
    memset(&s, 0, sizeof(s));
    s.power_part_only = p->power_part_only;
    s.is_standalone_master = p->is_cascaded && !p->is_slave && (ADI_DM_NUM_DIGIMMIC == 1);
    s.is_standalone_slave = p->is_cascaded && p->is_slave;
    if (p->is_cascaded) {
        memcpy(s.is_lo_right, p->is_lo_right, sizeof(s.is_lo_right));
    }
    s.firmware_image = (const uint32_t *) p->firmware_image;
    s.firmware_sz = (uint32_t) p->firmware_sz;
    s.firmware_constants_image = (const uint32_t *) p->firmware_constants_image;
    s.firmware_constants_sz = (uint32_t) p->firmware_constants_sz;
    s.ref_freq_hz = p->ref_freq_hz;
    s.rfpll_loop_bw_hz = p->rfpll_lbw_hz;
    s.ramp_start_freq_hz = (uint64_t) (p->ramp_start_freq_ghz * 1e9);
    s.ramp_bw_Mhz = p->ramp_bw_mhz;
    adi_dm_3_0_decim_ratio = p->decim_factor;
    adi_dm_3_0_dma_mem_limit = 0;

    return adi_dm_PowerUp(&s);
}
