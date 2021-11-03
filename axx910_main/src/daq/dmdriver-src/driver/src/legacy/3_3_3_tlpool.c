/* 3_3_3_tlpool.c
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
#include "legacy/3_3_3/adi_dmdriver.h"
#include "../localdefs.h"

#define ELS 1000
#define TLS 10

static uint32_t space[ELS];
static uint32_t spaceindex;

static uint32_t *tls[ADI_DM_NUM_DIGIMMIC][TLS];

static void put_word(uint32_t val)
{
    if (spaceindex < ELS) {
        space[spaceindex] = val;
        spaceindex++;
    }
}

adi_dm_err_t adi_dm_3_3_3_TasklistPoolSetup(const adi_dm_3_3_3_tasklist_pool_setup_t * p, uint32_t * dma_mem_limit)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    uint32_t i, j, k;
    adi_dm_tasklist_pool_setup_t pool;

    comment("---> Entering function adi_dm_3_3_3_TasklistPoolSetup");

    if (p->num_tasklists > TLS) {
        /* Overflowed our static memory. */
        return ADI_DM_PARAMETER_ERROR;
    }
    pool.num_tasklists = p->num_tasklists;
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        pool.tasklists[dm_num] = tls[dm_num];
    }

    spaceindex = 0;
    for (i = 0; i < pool.num_tasklists; i++) {
        uint32_t list_start = spaceindex;
        uint32_t num_tasks = 0;
        for (j = 0; p->tasklists[i][j] != 0; j++) {
            uint32_t params = (p->tasklists[i][j] >> 16) & 0xF;
            for (k = 0; k < params; k++) {
                j++;
            }
            num_tasks++;
        }
        put_word(num_tasks);    /* tasklist control word */
        for (j = 0; p->tasklists[i][j] != 0; j++) {
            uint32_t tcw = p->tasklists[i][j];
            uint32_t params = (tcw >> 16) & 0xF;
            put_word(tcw);
            for (k = 0; k < params; k++) {
                j++;
                put_word(p->tasklists[i][j]);
            }
            put_word(0);
            put_word(0xFFFFFFFF);
        }
        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            pool.tasklists[dm_num][i] = &space[list_start];
            pool.tasklist_length[dm_num][i] = spaceindex - list_start;
        }
    }

    res = adi_dm_TasklistPoolSetup(&pool, dma_mem_limit);
    if (res != ADI_DM_SUCCESS) {
        return res;
    }

    comment("---> Exiting function adi_dm_3_3_3_TasklistPoolSetup");

    return ADI_DM_SUCCESS;
}
