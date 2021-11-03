/* adi_dmdriver_3_3_3.h
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
 * Public C interface to the driver
 */

#ifndef ADI_DMDRIVER_3_3_3_H__
#define ADI_DMDRIVER_3_3_3_H__

#include <adi_dmdriver.h>

/**
 * @em IN parameter to @c adi_dm_TasklistPoolSetup
 *
 * @see adi_dm_TasklistPoolSetup
 */
typedef struct {
    uint32_t num_tasklists;         /** Number od tasklists to setup */
    uint32_t **tasklists;  /** Array of arrays of tasks. Each list is zero terminated */
} adi_dm_3_3_3_tasklist_pool_setup_t;

/**
 * Create a tasklist pool.
 *
 * Copies all tasklists down to device. Must be called after all calls to 
 * adi_dm_BurstProfileSetup().
 *
 * @param[in] p Tasklists to be written to memory.
 * @param[in,out] dma_mem_limit The same conventions as adi_dm_BurstProfileSetup().
 * @return ADI_DM_SUCCESS for success, an error code for errors.
 */
adi_dm_err_t adi_dm_3_3_3_TasklistPoolSetup(const adi_dm_3_3_3_tasklist_pool_setup_t * p, uint32_t * dma_mem_limit);

/* Including this header links to legacy functions.
 */
#ifndef ADI_DM_NO_LEGACY_REDEF


#define adi_dm_tasklist_pool_setup_t adi_dm_3_3_3_tasklist_pool_setup_t
#define adi_dm_TasklistPoolSetup adi_dm_3_3_3_TasklistPoolSetup

#endif


#endif                          /* ADI_DMDRIVER_3_3_3_H__ */
