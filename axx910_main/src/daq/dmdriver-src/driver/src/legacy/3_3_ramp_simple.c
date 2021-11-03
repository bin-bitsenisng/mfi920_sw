/* 3_3_ramp_simple.c
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
#include "3_3_local_helper.h"
#include "../localdefs.h"
#include "../adar690x_regs.h"
#include <string.h>

adi_dm_err_t adi_dm_write_ramp_config8(const adi_dm_3_3_ramp_config_t * p)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    uint32_t mask, bits;
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        /* ramp_config8 */
        mask = ~UINT32_C(0);
        bits = UINT32_C(0);
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STATUS_2;
        bits |= (p->dm[dm_num].ramp_status_2 << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STATUS_2) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STATUS_2;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STATUS_1;
        bits |= (p->dm[dm_num].ramp_status_1 << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STATUS_1) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STATUS_1;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STATUS_0;
        bits |= (p->dm[dm_num].ramp_status_0 << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STATUS_0) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STATUS_0;
        res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_RF_ADPLL_RFPLL_RAMP_CONFIG8, mask, bits);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_3_3_BuiltinMimoSetup(const adi_dm_3_3_builtin_mimo_setup_t * p)
{
    adi_dm_err_t res;
    const adi_dm_ramp_config_t c = adi_dm_convert_ramp_config(&p->ramp_config);
    const adi_dm_builtin_mimo_setup_t t = {
        .ramp_config = c,
        .ramp_profile = p->ramp_profile
    };

    res = adi_dm_BuiltinMimoSetup(&t);
    if (res != ADI_DM_SUCCESS) {
        return res;
    }

    res = adi_dm_write_ramp_config8(&p->ramp_config);
    if (res != ADI_DM_SUCCESS) {
        return res;
    }

    return ADI_DM_SUCCESS;
}
