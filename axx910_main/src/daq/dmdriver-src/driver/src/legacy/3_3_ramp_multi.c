/* 3_3_ramp_multi.c
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

/** @file
 * Support constructing a burst from many different ramp profiles using DMA.
 *
 * The supported scheme uses a single DMA channel in scatter-gather mode
 * to load every RAMPGEN register on each ramp.
 */

#define ADI_DM_NO_LEGACY_REDEF 1
#include "legacy/3_3/adi_dmdriver.h"
#include "3_3_local_helper.h"
#include "adar690x_fw.h"
#include <string.h>

extern adi_dm_err_t adi_dm_write_ramp_config8(const adi_dm_3_3_ramp_config_t * p);

adi_dm_err_t adi_dm_3_3_DmaRampSetup(const adi_dm_3_3_dma_ramp_setup_t * p)
{
    adi_dm_err_t res;

    const adi_dm_ramp_config_t c = adi_dm_convert_ramp_config(&p->ramp_config);
    const adi_dm_dma_ramp_setup_t s = {
        .ramp_config = c,
        .bpid = p->bpid
    };

    res = adi_dm_write_ramp_config8(&p->ramp_config);
    if (res != ADI_DM_SUCCESS) {
        return res;
    }

    res = adi_dm_DmaRampSetup(&s);
    if (res != ADI_DM_SUCCESS) {
        return res;
    }

    return ADI_DM_SUCCESS;
}
