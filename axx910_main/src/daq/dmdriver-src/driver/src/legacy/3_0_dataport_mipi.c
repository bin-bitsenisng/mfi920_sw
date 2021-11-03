/* 3_0_dataport_mipi.c
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
#include "../localdefs.h"
#include <string.h>

bool adi_dm_3_0_mipi_continuous_clock = false;

adi_dm_err_t adi_dm_3_0_DataportSetupMIPI(adi_dm_3_0_dataport_setup_mipi_t * p)
{
    adi_dm_num_t dm_num;
    adi_dm_3_2_mipi_setup_t s;

    memset(&s, 0, sizeof(s));
    s.crc32_en = p->crc_en;
    s.status_en = p->status_en;
    s.filter_output_bitwidth = ADI_DM_OUTPUT_BITWIDTH_16;
    s.ref_freq_hz = p->ref_freq_hz;
    s.continuous_clock = adi_dm_3_0_mipi_continuous_clock;
    switch (p->mipi_freq_hz) {
    case 80000000:
        s.mipi_clk = ADI_DM_MIPI_CLK_80MHZ;
        break;
    case 800000000:
        s.mipi_clk = ADI_DM_MIPI_CLK_800MHZ;
        break;
    case 1000000000:
        s.mipi_clk = ADI_DM_MIPI_CLK_1000MHZ;
        break;
    case 1200000000:
        s.mipi_clk = ADI_DM_MIPI_CLK_1200MHZ;
        break;
    default:
        comment("ERROR: MIPI Clock Frequency [%u] is not [80MHz, 800MHz, 1000MHz, 1200MHz]", p->mipi_freq_hz);
        return ADI_DM_PARAMETER_ERROR;
    }
    switch (p->lane_en_num) {
    case 1:
        s.num_lanes = ADI_DM_1_MIPI_LANE;
        break;
    case 2:
        s.num_lanes = ADI_DM_2_MIPI_LANES;
        break;
    case 4:
        s.num_lanes = ADI_DM_4_MIPI_LANES;
        break;
    default:
        comment("ERROR: lane_en_num is not [1, 2, 4]");
        return ADI_DM_PARAMETER_ERROR;
    }
    s.mipi_data_type = p->mipi_data_type;
    s.ls_byte_first = p->ls_byte_first;
    s.byte_interleaving = p->sample_byte_interleaving;
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        s.dm[dm_num].userval0 = 0;
        s.dm[dm_num].userval1 = 0;
        s.dm[dm_num].userval2 = 0;
        s.dm[dm_num].userval3 = 0;
        s.dm[dm_num].device_enum_id = 0;
    }

    return adi_dm_3_2_MipiSetup(&s);
}
