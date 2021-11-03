/* set_rfpll_freq.c
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

#include "adi_dmdriver.h"
#include "adar690x_fw.h"
#include "localdefs.h"

adi_dm_err_t adi_dm_RfpllLock(uint64_t ramp_start_freq_hz)
{
    adi_dm_err_t res;
    int64_t ramp_bw_hz = adi_dm_saved_ramp_bw_hz;
    uint64_t max_ramp_freq_hz, min_ramp_freq_hz;
    comment("--> Entering function adi_dm_RfpllLock");

    if (ramp_bw_hz >= 0) {
        max_ramp_freq_hz = (uint64_t) ((int64_t) ramp_start_freq_hz + ramp_bw_hz);
        min_ramp_freq_hz = ramp_start_freq_hz;
    } else {
        max_ramp_freq_hz = ramp_start_freq_hz;
        min_ramp_freq_hz = (uint64_t) ((int64_t) ramp_start_freq_hz + ramp_bw_hz);
    }
    if (adi_dm_check_fw_config && (min_ramp_freq_hz < ADI_ADAR690x_MIN_RAMP_START_FREQ_HZ || max_ramp_freq_hz > ADI_ADAR690x_MAX_RAMP_START_FREQ_HZ)) {
        comment("ERROR: ramp parameters out of range");
        return ADI_DM_PARAMETER_ERROR;
    }

    res = adi_dm_WriteU64(ADI_DM_MASTER, ADI_ADAR690x_CFG_RAMP_START_FREQ_HZ, ramp_start_freq_hz);
    if (res != ADI_DM_SUCCESS)
        return res;

    comment("ADI_ADAR690x_FW_RFPLL_LOCK");
    res = adi_dm_CallFW(ADI_DM_MASTER, ADI_ADAR690x_FW_RFPLL_LOCK);
    if (res != ADI_DM_SUCCESS)
        return res;

    adi_dm_saved_max_ramp_freq_hz = max_ramp_freq_hz;
    adi_dm_saved_ramp_start_freq_hz = ramp_start_freq_hz;

    comment("--> Leaving function adi_dm_RfpllLock");
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_RfpllReconfig(const adi_dm_rfpll_reconfig_t * p)
{
    adi_dm_err_t res;
    int64_t ramp_bw_hz = (int64_t) p->ramp_bw_Mhz * 1000000LL;

    // comment("--> Entering function adi_dm_RfpllReconfig");

    if (ramp_bw_hz == adi_dm_saved_ramp_bw_hz) {
        res = adi_dm_RfpllLock(p->ramp_start_freq_hz);
        if (res != ADI_DM_SUCCESS)
            return res;
    } else {
        uint64_t max_ramp_freq_hz, min_ramp_freq_hz;

        if (ramp_bw_hz >= 0) {
            max_ramp_freq_hz = (uint64_t) ((int64_t) p->ramp_start_freq_hz + ramp_bw_hz);
            min_ramp_freq_hz = p->ramp_start_freq_hz;
        } else {
            max_ramp_freq_hz = p->ramp_start_freq_hz;
            min_ramp_freq_hz = (uint64_t) ((int64_t) p->ramp_start_freq_hz + ramp_bw_hz);
        }
        if (adi_dm_check_fw_config && (min_ramp_freq_hz < ADI_ADAR690x_MIN_RAMP_START_FREQ_HZ || max_ramp_freq_hz > ADI_ADAR690x_MAX_RAMP_START_FREQ_HZ)) {
            comment("ERROR: ramp parameters out of range");
            return ADI_DM_PARAMETER_ERROR;
        }

        res = adi_dm_WriteF32(ADI_DM_MASTER, ADI_ADAR690x_CFG_RAMP_BW_MHZ, p->ramp_bw_Mhz);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_WriteU64(ADI_DM_MASTER, ADI_ADAR690x_CFG_RAMP_START_FREQ_HZ, p->ramp_start_freq_hz);
        if (res != ADI_DM_SUCCESS)
            return res;

        // comment("ADI_ADAR690x_FW_RFPLL_RAMP_SETUP");
        res = adi_dm_CallFW(ADI_DM_MASTER, ADI_ADAR690x_FW_RFPLL_RAMP_SETUP);
        if (res != ADI_DM_SUCCESS)
            return res;

        adi_dm_saved_max_ramp_freq_hz = max_ramp_freq_hz;
        adi_dm_saved_ramp_bw_hz = ramp_bw_hz;
        adi_dm_saved_ramp_start_freq_hz = p->ramp_start_freq_hz;
    }
    // comment("--> Leaving function adi_dm_RfpllReconfig");
    return ADI_DM_SUCCESS;
}
