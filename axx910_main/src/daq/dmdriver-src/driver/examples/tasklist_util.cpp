/* Copyright (c) 2018-2020 Analog Devices Inc. All rights reserved
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

#include "tasklist_util.h"
#include "adar690x_fw.h"
#include "application.h"
#include <string.h>

const taskdesc_t adcpll_align = { ADI_ADAR690x_FW_ADCPLL_ALIGN, ADI_ADAR690x_MINCYC_ADCPLL_ALIGN, ADI_ADAR690x_MAXCYC_ADCPLL_ALIGN };
const taskdesc_t ramp_trig = { ADI_ADAR690x_FW_RAMP_TRIG, ADI_ADAR690x_MINCYC_RAMP_TRIG, ADI_ADAR690x_MAXCYC_RAMP_TRIG };
const taskdesc_t rfpll_bow_cal = { ADI_ADAR690x_FW_RFPLL_BOW_CAL, ADI_ADAR690x_MINCYC_RFPLL_BOW_CAL, ADI_ADAR690x_MAXCYC_RFPLL_BOW_CAL };
const taskdesc_t temp_measure = { ADI_ADAR690x_FW_TEMP_MEASURE, ADI_ADAR690x_MINCYC_TEMP_MEASURE, ADI_ADAR690x_MAXCYC_TEMP_MEASURE };
const taskdesc_t rfpll_lock = { ADI_ADAR690x_FW_RFPLL_LOCK, ADI_ADAR690x_MINCYC_RFPLL_LOCK, ADI_ADAR690x_MAXCYC_RFPLL_LOCK };
const taskdesc_t lochain_cal = { ADI_ADAR690x_FW_LOCHAIN_CAL, ADI_ADAR690x_MINCYC_LOCHAIN_CAL, ADI_ADAR690x_MAXCYC_LOCHAIN_CAL };
const taskdesc_t txpa_adj = { ADI_ADAR690x_FW_TXPA_ADJ, ADI_ADAR690x_MINCYC_TXPA_ADJ, ADI_ADAR690x_MAXCYC_TXPA_ADJ };
const taskdesc_t adc_phase_cal = { ADI_ADAR690x_FW_ADC_PHASE_CAL, ADI_ADAR690x_MINCYC_ADC_PHASE_CAL, ADI_ADAR690x_MAXCYC_ADC_PHASE_CAL };
const taskdesc_t hpf_cal = { ADI_ADAR690x_FW_HPF_CAL, ADI_ADAR690x_MINCYC_HPF_CAL, ADI_ADAR690x_MAXCYC_HPF_CAL };
const taskdesc_t rxgain_cal = { ADI_ADAR690x_FW_RXGAIN_CAL, ADI_ADAR690x_MINCYC_RXGAIN_CAL, ADI_ADAR690x_MAXCYC_RXGAIN_CAL };
const taskdesc_t rmw = { ADI_ADAR690x_FW_RMW, ADI_ADAR690x_MINCYC_RMW, ADI_ADAR690x_MAXCYC_RMW };
const taskdesc_t rfpll_ramp_setup = { ADI_ADAR690x_FW_RFPLL_RAMP_SETUP, ADI_ADAR690x_MINCYC_RFPLL_RAMP_SETUP, ADI_ADAR690x_MAXCYC_RFPLL_RAMP_SETUP };
const taskdesc_t pga_cal = { ADI_ADAR690x_FW_PGA_CAL, ADI_ADAR690x_MINCYC_PGA_CAL, ADI_ADAR690x_MAXCYC_PGA_CAL };
const taskdesc_t power_manage = { ADI_ADAR690x_FW_POWER_MANAGE, ADI_ADAR690x_MINCYC_POWER_MANAGE, ADI_ADAR690x_MAXCYC_POWER_MANAGE };
const taskdesc_t txpa_cal = { ADI_ADAR690x_FW_TXPA_CAL, ADI_ADAR690x_MINCYC_TXPA_CAL, ADI_ADAR690x_MAXCYC_TXPA_CAL };

void start_building_tasklists(tasklist_builder_t * b)
{
    adi_dm_num_t dm_num;

    memset(b, 0, sizeof(*b));
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        b->setup.tasklists[dm_num] = b->tasklists_space[dm_num];
        b->setup.tasklist_length[dm_num] = b->tasklist_length_space[dm_num];
    }
}

void start_tasklist(uint32_t tasklist_no, tasklist_builder_t * b)
{
    adi_dm_num_t dm_num;
    if (tasklist_no != b->setup.num_tasklists) {
        /* Check that TL_ enum matches actual tasklist number. */
        platform_error("tasklist constructed out of order", 0, __FILE__, __LINE__);
    }
    if (b->setup.num_tasklists >= NUM_TASKLISTS) {
        platform_error("NUM_TASKLISTS too small", 0, __FILE__, __LINE__);
    }
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        if (b->taskspace_index[dm_num] >= TASKSPACE_SIZE) {
            platform_error("TASKSPACE_SIZE too small", 0, __FILE__, __LINE__);
        }
        b->setup.tasklists[dm_num][b->setup.num_tasklists] = &b->taskspace[dm_num][b->taskspace_index[dm_num]];
        b->setup.tasklists[dm_num][b->setup.num_tasklists][0] = 0;      /* tasklist control word */
        b->taskspace_index[dm_num]++;
        b->setup.tasklist_length[dm_num][b->setup.num_tasklists] = 1;
        b->num_tasks_in_tasklist[dm_num] = 0;
    }
}

void append_task_array(adi_dm_num_t dm_num_in, uint32_t length, const uint32_t array[], tasklist_builder_t * b)
{
    adi_dm_num_t first, last, dm_num;
    if (dm_num_in == ADI_DM_ALL_DIGIMMICS) {
        first = ADI_DM_MASTER;
        last = adi_dm_active_digimmics;
    } else {
        first = dm_num_in;
        last = dm_num_in + 1;
    }
    for (dm_num = first; dm_num < last; dm_num++) {
        uint32_t i;
        if (b->taskspace_index[dm_num] + length > TASKSPACE_SIZE) {
            platform_error("TASKSPACE_SIZE too small", 0, __FILE__, __LINE__);
        }
        for (i = 0; i < length; i++) {
            b->taskspace[dm_num][b->taskspace_index[dm_num]] = array[i];
            b->taskspace_index[dm_num]++;
            b->setup.tasklist_length[dm_num][b->setup.num_tasklists]++;
        }
        b->num_tasks_in_tasklist[dm_num]++;
    }
}

void finish_tasklist(tasklist_builder_t * b)
{
    adi_dm_num_t dm_num;
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        /* write the tasklist control word */
        b->setup.tasklists[dm_num][b->setup.num_tasklists][0] = b->num_tasks_in_tasklist[dm_num];
    }
    b->setup.num_tasklists++;
}

void add_task(adi_dm_num_t dm_num, taskdesc_t task, tasklist_builder_t * b)
{
    uint32_t a[3];
    a[0] = task.taskid;
    a[1] = task.min_cycles;     /* window min for watchdog timer */
    a[2] = task.max_cycles;     /* window max for watchdog timer */

    append_task_array(dm_num, sizeof(a) / sizeof(a[0]), a, b);
}

void add_task2(adi_dm_num_t dm_num, taskdesc_t task, uint32_t param0, uint32_t param1, tasklist_builder_t * b)
{
    uint32_t a[5];
    a[0] = task.taskid | (2 << 16);     /* num params encoded in top half of taskid word */
    a[1] = param0;              /* as many parameters as coded above */
    a[2] = param1;
    a[3] = task.min_cycles;     /* window min for watchdog timer */
    a[4] = task.max_cycles;     /* window max for watchdog timer */

    append_task_array(dm_num, sizeof(a) / sizeof(a[0]), a, b);
}

void add_task3(adi_dm_num_t dm_num, taskdesc_t task, uint32_t param0, uint32_t param1, uint32_t param2, tasklist_builder_t * b)
{
    uint32_t a[6];
    a[0] = task.taskid | (3 << 16);     /* num params encoded in top half of taskid word */
    a[1] = param0;              /* as many parameters as coded above */
    a[2] = param1;
    a[3] = param2;
    a[4] = task.min_cycles;     /* window min for watchdog timer */
    a[5] = task.max_cycles;     /* window max for watchdog timer */

    append_task_array(dm_num, sizeof(a) / sizeof(a[0]), a, b);
}

void add_tasku64(adi_dm_num_t dm_num, taskdesc_t task, uint64_t paramu64, tasklist_builder_t * b)
{
    uint32_t param0 = paramu64 & 0xFFFFFFFF;
    uint32_t param1 = (paramu64 >> 32) & 0xFFFFFFFF;
    add_task2(dm_num, task, param0, param1, b);
}
