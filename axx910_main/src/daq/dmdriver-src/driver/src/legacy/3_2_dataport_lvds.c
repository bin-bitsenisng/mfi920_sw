/* 3_2_dataport_lvds.c
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
#include "legacy/3_2/adi_dmdriver.h"
#include "../localdefs.h"
#include "../adar690x_regs.h"
#include <string.h>

adi_dm_err_t adi_dm_3_2_LvdsSetup(const adi_dm_3_2_lvds_setup_t * p)
{
    adi_dm_num_t dm_num;
    adi_dm_lvds_setup_t s;

    /* the only difference in 3.2.1 is adi_dm_LvdsSetup
     * does not set device_enum_id because this is set in PowerUp
     * as recommended is safety manual. Overwite with user value
     * here for compatibility with past.
     */
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        comment("*** Setting the value of device_enum_id (0x%02X) ***", p->dm[dm_num].device_enum_id);
        adi_dm_3_2_Write(dm_num, REG_SPI_SPI_DEVICEENUMID, p->dm[dm_num].device_enum_id);
    }

    memset(&s, 0, sizeof(s));
    s.crc32_en = p->crc32_en;
    s.status_en = p->status_en;
    s.filter_output_bitwidth = p->filter_output_bitwidth;
    s.dual_fs_mode = p->dual_fs_mode;
    s.fs_active_low = p->fs_active_low;;
    s.streaming_mode_1 = p->streaming_mode_1;
    s.payload_dis = p->payload_dis;
    s.id_wc_en = p->id_wc_en;
    s.ls_byte_first = p->ls_byte_first;
    s.ls_bit_first = p->ls_bit_first;
    s.lvds_clk = p->lvds_clk;
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        s.dm[dm_num].userval0 = p->dm[dm_num].userval0;
        s.dm[dm_num].userval1 = p->dm[dm_num].userval1;
        s.dm[dm_num].userval2 = p->dm[dm_num].userval2;
        s.dm[dm_num].userval3 = p->dm[dm_num].userval3;
        s.dm[dm_num].dataid0 = p->dm[dm_num].dataid0;
        s.dm[dm_num].dataid1 = p->dm[dm_num].dataid1;
        s.dm[dm_num].dataid2 = p->dm[dm_num].dataid2;
        s.dm[dm_num].dataid3 = p->dm[dm_num].dataid3;
    }

    return adi_dm_LvdsSetup(&s);
}
