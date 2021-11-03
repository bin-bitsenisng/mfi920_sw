/* tasklist_util.h
* Copyright (c) 2019-2020 Analog Devices Inc. All rights reserved
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

#ifndef TASKLIST_UTIL_H
#define TASKLIST_UTIL_H

#include "adi_dmdriver.h"

typedef struct {
    uint32_t taskid;
    uint32_t min_cycles;
    uint32_t max_cycles;
} taskdesc_t;

extern const taskdesc_t adcpll_align;
extern const taskdesc_t ramp_trig;
extern const taskdesc_t rfpll_bow_cal;
extern const taskdesc_t temp_measure;
extern const taskdesc_t rfpll_lock;
extern const taskdesc_t lochain_cal;
extern const taskdesc_t txpa_adj;
extern const taskdesc_t adc_phase_cal;
extern const taskdesc_t hpf_cal;
extern const taskdesc_t rxgain_cal;
extern const taskdesc_t rmw;
extern const taskdesc_t rfpll_ramp_setup;
extern const taskdesc_t pga_cal;
extern const taskdesc_t power_manage;
extern const taskdesc_t txpa_cal;

/* Parameters to tasklist_builder_t type */
enum {
    NUM_TASKLISTS = 10,
    TASKSPACE_SIZE = 500        /* number of words in all tasklists, max across all devices */
};

typedef struct {
    adi_dm_tasklist_pool_setup_t setup;
    uint32_t taskspace[ADI_DM_NUM_DIGIMMIC][TASKSPACE_SIZE];
    uint32_t taskspace_index[ADI_DM_NUM_DIGIMMIC];
    uint32_t num_tasks_in_tasklist[ADI_DM_NUM_DIGIMMIC];
    uint32_t *tasklists_space[ADI_DM_NUM_DIGIMMIC][NUM_TASKLISTS];
    uint32_t tasklist_length_space[ADI_DM_NUM_DIGIMMIC][NUM_TASKLISTS];
} tasklist_builder_t;

extern void start_building_tasklists(tasklist_builder_t * b);
extern void start_tasklist(uint32_t tasklist_no, tasklist_builder_t * b);
extern void finish_tasklist(tasklist_builder_t * b);
extern void add_task(adi_dm_num_t dm_num, taskdesc_t task, tasklist_builder_t * b);
extern void add_task2(adi_dm_num_t dm_num, taskdesc_t task, uint32_t param0, uint32_t param1, tasklist_builder_t * b);
extern void add_task3(adi_dm_num_t dm_num, taskdesc_t task, uint32_t param0, uint32_t param1, uint32_t param3, tasklist_builder_t * b);
extern void add_tasku64(adi_dm_num_t dm_num, taskdesc_t task, uint64_t paramu64, tasklist_builder_t * b);

#endif                          /*TASKLIST_UTIL_H */
