/* 3_0_dataport_lvds.c
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

adi_dm_err_t adi_dm_3_0_DataportSetupLVDS(adi_dm_3_0_dataport_setup_lvds_t * p)
{
    adi_dm_num_t dm_num;
    adi_dm_3_2_lvds_setup_t s;

    memset(&s, 0, sizeof(s));
    s.crc32_en = p->crc_en;
    s.status_en = p->status_en;
    s.filter_output_bitwidth = ADI_DM_OUTPUT_BITWIDTH_16;
    s.dual_fs_mode = p->dual_fs_mode;
    s.fs_active_low = false;
    s.streaming_mode_1 = (p->streaming_mode != 2);
    s.payload_dis = false;
    s.id_wc_en = p->id_wc_en;
    s.ls_byte_first = p->ls_byte_first;
    s.ls_bit_first = p->ls_bit_first;
    if (p->clk_div == 1.5)
        s.lvds_clk = ADI_DM_ADCCLK_DIV_1_5;
    else if (p->clk_div == 2.0)
        s.lvds_clk = ADI_DM_ADCCLK_DIV_2;
    else if (p->clk_div == 3.0)
        s.lvds_clk = ADI_DM_ADCCLK_DIV_3;
    else if (p->clk_div == 4.0)
        s.lvds_clk = ADI_DM_ADCCLK_DIV_4;
    else if (p->clk_div == 6.0)
        s.lvds_clk = ADI_DM_ADCCLK_DIV_6;
    else if (p->clk_div == 8.0)
        s.lvds_clk = ADI_DM_ADCCLK_DIV_8;
    else {
        comment("ERROR: invalid clock_div [%1.2f] not in [1.5, 2.0, 3.0, 4.0, 6.0, 8.0]", p->clk_div);
        return ADI_DM_PARAMETER_ERROR;
    }
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        s.dm[dm_num].userval0 = 0;
        s.dm[dm_num].userval1 = 0;
        s.dm[dm_num].userval2 = 0;
        s.dm[dm_num].userval3 = 0;
        s.dm[dm_num].device_enum_id = 0;
        s.dm[dm_num].dataid0 = p->lane0_id;
        s.dm[dm_num].dataid1 = p->lane1_id;
        s.dm[dm_num].dataid2 = p->lane2_id;
        s.dm[dm_num].dataid3 = p->lane3_id;
    }

    return adi_dm_3_2_LvdsSetup(&s);
}
