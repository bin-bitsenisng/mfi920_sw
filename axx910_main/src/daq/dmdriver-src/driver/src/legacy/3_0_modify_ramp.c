/* 3_0_modify_ramp.c
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
#include "../adar690x_regs.h"

#define IDX_RAMPGEN_RAMP_GEN_DEL01 (REG_RAMPGEN_RAMP_GEN_DEL01 - REG_RAMPGEN_RAMP_GEN_DEL01)
#define IDX_RAMPGEN_RAMP_GEN_DEL12 (REG_RAMPGEN_RAMP_GEN_DEL12 - REG_RAMPGEN_RAMP_GEN_DEL01)
#define IDX_RAMPGEN_RAMP_GEN_STEP1 (REG_RAMPGEN_RAMP_GEN_STEP1 - REG_RAMPGEN_RAMP_GEN_DEL01)
#define IDX_RAMPGEN_RAMP_GEN_STEP0 (REG_RAMPGEN_RAMP_GEN_STEP0 - REG_RAMPGEN_RAMP_GEN_DEL01)
#define IDX_RAMPGEN_RAMP_GEN_DEV0 (REG_RAMPGEN_RAMP_GEN_DEV0 - REG_RAMPGEN_RAMP_GEN_DEL01)
#define IDX_RAMPGEN_RAMP_GEN_DEV1 (REG_RAMPGEN_RAMP_GEN_DEV1 - REG_RAMPGEN_RAMP_GEN_DEL01)
#define IDX_RAMPGEN_RAMP_GEN_TX (REG_RAMPGEN_RAMP_GEN_TX - REG_RAMPGEN_RAMP_GEN_DEL01)
#define IDX_RAMPGEN_RAMP_GEN_AFECNT (REG_RAMPGEN_RAMP_GEN_AFECNT - REG_RAMPGEN_RAMP_GEN_DEL01)
#define IDX_RAMPGEN_RAMP_GEN_PHASE_MOD (REG_RAMPGEN_RAMP_GEN_PHASE_MOD - REG_RAMPGEN_RAMP_GEN_DEL01)

adi_dm_err_t adi_dm_3_0_ModifyRampProfile(adi_dm_num_t dm_num, uint32_t bpid, uint32_t profile_idx, adi_dm_3_0_ramp_profile_field_t field, uint32_t value)
{
    uint32_t offset = 0;
    bool is_rmw = false;
    bool is_rmw2 = false;
    uint32_t mask;
    uint32_t pos;
    uint32_t offset2;
    uint32_t mask2;
    uint32_t pos2;
    uint32_t shift2;
    switch (field) {
    case adi_dm_3_0_del0_steps:
        offset = IDX_RAMPGEN_RAMP_GEN_DEL01;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_DEL01_DEL_0;
        pos = BITP_RAMPGEN_RAMP_GEN_DEL01_DEL_0;
        break;
    case adi_dm_3_0_slp0_steps:
        offset = IDX_RAMPGEN_RAMP_GEN_STEP0;
        break;
    case adi_dm_3_0_del1_steps:
        offset = IDX_RAMPGEN_RAMP_GEN_DEL01;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_DEL01_DEL_1;
        pos = BITP_RAMPGEN_RAMP_GEN_DEL01_DEL_1;
        is_rmw2 = true;
        offset2 = IDX_RAMPGEN_RAMP_GEN_DEL12;
        mask2 = BITM_RAMPGEN_RAMP_GEN_DEL12_DEL_1;
        pos2 = BITP_RAMPGEN_RAMP_GEN_DEL12_DEL_1;
        shift2 = 10;
        break;
    case adi_dm_3_0_slp1_steps:
        offset = IDX_RAMPGEN_RAMP_GEN_STEP1;
        break;
    case adi_dm_3_0_del2_steps:
        offset = IDX_RAMPGEN_RAMP_GEN_DEL12;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_DEL12_DEL_2;
        pos = BITP_RAMPGEN_RAMP_GEN_DEL12_DEL_2;
        break;
    case adi_dm_3_0_slp0_dev:
        offset = IDX_RAMPGEN_RAMP_GEN_DEV0;
        break;
    case adi_dm_3_0_slp1_dev:
        offset = IDX_RAMPGEN_RAMP_GEN_DEV1;
        break;
    case adi_dm_3_0_tx_pattern:
        offset = IDX_RAMPGEN_RAMP_GEN_TX;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_TX_TX_PATTERN;
        pos = BITP_RAMPGEN_RAMP_GEN_TX_TX_PATTERN;
        break;
    case adi_dm_3_0_ramp_stat_bit_0:
        offset = IDX_RAMPGEN_RAMP_GEN_TX;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_0;
        pos = BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_0;
        break;
    case adi_dm_3_0_ramp_stat_bit_1:
        offset = IDX_RAMPGEN_RAMP_GEN_TX;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_1;
        pos = BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_1;
        break;
    case adi_dm_3_0_ramp_stat_bit_2:
        offset = IDX_RAMPGEN_RAMP_GEN_TX;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_2;
        pos = BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_2;
        break;
    case adi_dm_3_0_afe_start_off_time:
        offset = IDX_RAMPGEN_RAMP_GEN_AFECNT;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_AFECNT_AFE_START_OFF_TIME;
        pos = BITP_RAMPGEN_RAMP_GEN_AFECNT_AFE_START_OFF_TIME;
        break;
    case adi_dm_3_0_num_samples:
        offset = IDX_RAMPGEN_RAMP_GEN_PHASE_MOD;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_PHASE_MOD_NUM_SAMPLES;
        pos = BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_NUM_SAMPLES;
        break;
    case adi_dm_3_0_afe_ramp_time:
        offset = IDX_RAMPGEN_RAMP_GEN_AFECNT;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_AFECNT_AFE_RAMP_TIME;
        pos = BITP_RAMPGEN_RAMP_GEN_AFECNT_AFE_RAMP_TIME;
        break;
    case adi_dm_3_0_pa0_phase:
        offset = IDX_RAMPGEN_RAMP_GEN_TX;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_TX_PA0_PHASE;
        pos = BITP_RAMPGEN_RAMP_GEN_TX_PA0_PHASE;
        break;
    case adi_dm_3_0_pa1_phase:
        offset = IDX_RAMPGEN_RAMP_GEN_TX;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_TX_PA1_PHASE;
        pos = BITP_RAMPGEN_RAMP_GEN_TX_PA1_PHASE;
        break;
    case adi_dm_3_0_pa2_phase:
        offset = IDX_RAMPGEN_RAMP_GEN_TX;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_TX_PA2_PHASE;
        pos = BITP_RAMPGEN_RAMP_GEN_TX_PA2_PHASE;
        break;
    case adi_dm_3_0_pa0_phase_dev:
        offset = IDX_RAMPGEN_RAMP_GEN_PHASE_MOD;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_PHASE_MOD_PA0_PHASE_DEV;
        pos = BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA0_PHASE_DEV;
        break;
    case adi_dm_3_0_pa1_phase_dev:
        offset = IDX_RAMPGEN_RAMP_GEN_PHASE_MOD;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_PHASE_MOD_PA1_PHASE_DEV;
        pos = BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA1_PHASE_DEV;
        break;
    case adi_dm_3_0_pa2_phase_dev:
        offset = IDX_RAMPGEN_RAMP_GEN_PHASE_MOD;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_PHASE_MOD_PA2_PHASE_DEV;
        pos = BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA2_PHASE_DEV;
        break;
    case adi_dm_3_0_phase_step:
        offset = IDX_RAMPGEN_RAMP_GEN_TX;
        is_rmw = true;
        mask = BITM_RAMPGEN_RAMP_GEN_TX_PHASE_STEP;
        pos = BITP_RAMPGEN_RAMP_GEN_TX_PHASE_STEP;
        break;
    default:
        return ADI_DM_PARAMETER_ERROR;
    }

    uint32_t base, num_profiles;
    adi_dm_err_t res = adi_dm_decode_bpid(bpid, &base, &num_profiles, NULL, NULL);
    if (res != ADI_DM_SUCCESS)
        return res;
    if (profile_idx >= num_profiles)
        return ADI_DM_PARAMETER_ERROR;
    uint32_t addr = base + (profile_idx * DMA_RAMP_PROFILE_SIZE) + offset;
    if (is_rmw) {
        adi_dm_3_2_RMW(dm_num, addr, ~mask, (value << pos) & mask);
        if (is_rmw2) {
            uint32_t addr2 = base + (profile_idx * DMA_RAMP_PROFILE_SIZE) + offset2;
            adi_dm_3_2_RMW(dm_num, addr2, ~mask2, ((value >> shift2) << pos2) & mask2);
        }
    } else {
        adi_dm_3_2_Write(dm_num, addr, value);
    }
    return ADI_DM_SUCCESS;
}
