/* decode_bpid.c
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
#include "localdefs.h"
#include "adar690x_regs.h"

/* out of bounds */
static bool oob(uint32_t val, uint32_t incr)
{
    if (val + incr < DMA_MEMORY_START || val + incr > DMA_MEMORY_START + DMA_MEMORY_SIZE) {
        return true;
    }
    if (val % 4 != 0) {
        return true;
    }
    return false;
}

/**
 * unofficial API for decoding bpid and returning pointers into the burst profile
 */
adi_dm_err_t adi_dm_decode_bpid(uint32_t bpid, uint32_t * ramp_profiles_param, uint32_t * num_ramp_profiles_param, uint32_t * tx_overlay_param, uint32_t * tx_overlay_len_param)
{
    adi_dm_err_t res;
    uint32_t tasks;
    if (ramp_profiles_param != NULL) {
        *ramp_profiles_param = 0;
    }
    if (num_ramp_profiles_param != NULL) {
        *num_ramp_profiles_param = 0;
    }
    if (tx_overlay_param != NULL) {
        *tx_overlay_param = 0;
    }
    if (tx_overlay_len_param != NULL) {
        *tx_overlay_len_param = 0;
    }

    if (bpid == 0) {
        tasks = DMA_MEMORY_START;
    } else {
        if (oob(bpid, -44)) {
            return ADI_DM_PARAMETER_ERROR;
        }
        uint32_t ch0_tasks = bpid - 44;
        uint32_t last_word_golden_prim123;
        res = adi_dm_Read(ADI_DM_MASTER, ch0_tasks, &last_word_golden_prim123);
        if (res != ADI_DM_SUCCESS)
            return res;
        uint32_t ch0_task0_ctl;
        res = adi_dm_Read(ADI_DM_MASTER, ch0_tasks + 8, &ch0_task0_ctl);
        if (res != ADI_DM_SUCCESS)
            return res;
        int32_t ch0_task0_n_minus_1 = (ch0_task0_ctl >> 4) & 0x3ff;
        int32_t off = ch0_task0_n_minus_1 * 4;
        if (oob(last_word_golden_prim123, -off)) {
            return ADI_DM_PARAMETER_ERROR;
        }
        uint32_t golden_prim_1 = last_word_golden_prim123 - off;
        uint32_t last_word_task0_1;
        res = adi_dm_Read(ADI_DM_MASTER, golden_prim_1, &last_word_task0_1);
        if (res != ADI_DM_SUCCESS)
            return res;
        if (oob(last_word_task0_1, -28)) {
            return ADI_DM_PARAMETER_ERROR;
        }
        tasks = last_word_task0_1 - 28;
    }

    uint32_t last_word_first_ramp_profile;
    res = adi_dm_Read(ADI_DM_MASTER, tasks, &last_word_first_ramp_profile);
    if (res != ADI_DM_SUCCESS)
        return res;
    if (oob(last_word_first_ramp_profile, -4 * 8)) {
        return ADI_DM_PARAMETER_ERROR;
    }
    uint32_t ramp_profiles = last_word_first_ramp_profile - 4 * 8;
    /*
     * dma area contains
     * tasks (2*num_profiles * ctrl_size), golden_prim_1s (num_profiles * ctrl_size), ramp_profiles
     */
    if (ramp_profiles <= tasks) {
        return ADI_DM_PARAMETER_ERROR;
    }
    uint32_t diff = ramp_profiles - tasks;
    if (diff % (3 * 4 * 4) != 0) {
        return ADI_DM_PARAMETER_ERROR;
    }
    uint32_t num_ramp_profiles = diff / (3 * 4 * 4);
    uint32_t ramp_profiles_size = num_ramp_profiles * (9 * 4);
    uint32_t golden_prim0_size = 4 * 4;
    uint32_t ch23_mask_size = 4;
    uint32_t ch0_tasks_size = 3 * 4 * 4;
    uint32_t rest_of_basic_dma_area = golden_prim0_size + ramp_profiles_size + ch23_mask_size + ch0_tasks_size;
    if (oob(ramp_profiles, rest_of_basic_dma_area)) {
        return ADI_DM_PARAMETER_ERROR;
    }

    uint32_t tx_overlay = 0;
    uint32_t tx_overlay_len = 0;
    uint32_t ch0_task1 = ramp_profiles + rest_of_basic_dma_area - 8 * 4;
    if (oob(ch0_task1, 4)) {
        return ADI_DM_PARAMETER_ERROR;
    }
    uint32_t ch0_task1_dst;
    res = adi_dm_Read(ADI_DM_MASTER, ch0_task1 + 4, &ch0_task1_dst);
    if (res != ADI_DM_SUCCESS)
        return res;
    if (ch0_task1_dst == REG_UDMA_RMSK_CLR) {
        /* if ch0_task1 clears RMSK we have a tx_overlay array */
        uint32_t extra_dma_area = ramp_profiles + rest_of_basic_dma_area;
        uint32_t golden_prim123_size = 3 * 4 * 4;
        uint32_t ch3_tasks_size = 2 * 4 * 4;
        uint32_t fixed_extra_dma_area_size = golden_prim123_size + ch3_tasks_size;
        if (oob(extra_dma_area, fixed_extra_dma_area_size)) {
            return ADI_DM_PARAMETER_ERROR;
        }
        tx_overlay = extra_dma_area + fixed_extra_dma_area_size;
        uint32_t golden_prim2 = extra_dma_area + 4 * 4;
        uint32_t golden_prim2_ctl;
        res = adi_dm_Read(ADI_DM_MASTER, golden_prim2 + 2 * 4, &golden_prim2_ctl);
        if (res != ADI_DM_SUCCESS)
            return res;
        uint32_t golden_prim2_n_minus_1 = (golden_prim2_ctl >> 4) & 0x3ff;
        tx_overlay_len = golden_prim2_n_minus_1 + 1;
        if (tx_overlay_len == 0) {
            return ADI_DM_PARAMETER_ERROR;
        }
        if (oob(tx_overlay, tx_overlay_len * 4)) {
            return ADI_DM_PARAMETER_ERROR;
        }
    }

    if (ramp_profiles_param != NULL) {
        *ramp_profiles_param = ramp_profiles;
    }
    if (num_ramp_profiles_param != NULL) {
        *num_ramp_profiles_param = num_ramp_profiles;
    }
    if (tx_overlay_param != NULL) {
        *tx_overlay_param = tx_overlay;
    }
    if (tx_overlay_len_param != NULL) {
        *tx_overlay_len_param = tx_overlay_len;
    }
    return ADI_DM_SUCCESS;
}
