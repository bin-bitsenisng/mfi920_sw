/* rfpllperiod.c
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
#include "adi_dmdriver.h"
#include "localdefs.h"
#include <math.h>
#include <string.h>

static double calc_rfpll_period_for_ramp(uint64_t ramp_start_freq_hz, adi_dm_ramp_profile_t * ramp, bool first_ramp, uint32_t num_ramps)
{
    const uint32_t ref_freq_hz = 80000000;
    /* Due to the settling time of the RFPLL,
     * a compensation factor was added to the slope1 calculation
     */
    const double settling_time_factor = 0.3 * (ref_freq_hz - 40e6) / 40e6 + 0.2;

    uint32_t discarded_steps_delay0;
    uint32_t discarded_steps_slope0;
    double expected_initial_rfpll_fcw;
    double expected_end_rfpll_fcw;
    double expected_counter_slope0;
    double expected_counter_slope0_first_ramp;
    double expected_counter_slope1;
    double expected_counter_delay0;
    double expected_counter_delay0_first_ramp;
    double expected_counter_delay1;
    double expected_counter_delay2;
    double expected_counter_burst;

    if (first_ramp) {
        /* RFPLL period counter is not updated in the first 7 clocks, so they have
         * to be discarded.
         */
        if (ramp->del_0 > 7) {
            discarded_steps_delay0 = 7;
            discarded_steps_slope0 = 0;
        } else {
            discarded_steps_delay0 = ramp->del_0;
            discarded_steps_slope0 = 7 - ramp->del_0;
        }
    } else {
        discarded_steps_delay0 = 0;
        discarded_steps_slope0 = 0;
    }

    expected_initial_rfpll_fcw = (double) ramp_start_freq_hz / 8.0 / ref_freq_hz;
    expected_end_rfpll_fcw = expected_initial_rfpll_fcw + (double) ramp->ramp_dev_0 * ramp->ramp_steps_0 / pow(2.0, 25.0);

    expected_counter_slope0 = expected_initial_rfpll_fcw * ramp->ramp_steps_0 + (double) ramp->ramp_dev_0 * ramp->ramp_steps_0 * (ramp->ramp_steps_0 + 1) / 2.0 / pow(2.0, 25.0);
    expected_counter_slope0_first_ramp = expected_initial_rfpll_fcw * (ramp->ramp_steps_0 - discarded_steps_slope0) + (double) ramp->ramp_dev_0 * (ramp->ramp_steps_0 - discarded_steps_slope0) * (ramp->ramp_steps_0 + discarded_steps_slope0 + 1) / 2.0 / pow(2.0, 25.0);

    expected_counter_slope1 = expected_end_rfpll_fcw * ramp->ramp_steps_1 + (double) ramp->ramp_dev_1 * ramp->ramp_steps_1 * (ramp->ramp_steps_1 + 1) / 2.0 / pow(2.0, 25.0) - (double) ramp->ramp_dev_1 * settling_time_factor / 2.0 / pow(2.0, 25.0);

    expected_counter_delay0 = expected_initial_rfpll_fcw * ramp->del_0;
    expected_counter_delay0_first_ramp = expected_initial_rfpll_fcw * (ramp->del_0 - discarded_steps_delay0);
    expected_counter_delay1 = expected_end_rfpll_fcw * ramp->del_1;
    expected_counter_delay2 = expected_initial_rfpll_fcw * ramp->del_2;

    expected_counter_burst = expected_counter_delay0_first_ramp + expected_counter_slope0_first_ramp + expected_counter_delay0 * (num_ramps - 1) + expected_counter_slope0 * (num_ramps - 1) + expected_counter_slope1 * num_ramps + expected_counter_delay1 * num_ramps + expected_counter_delay2 * num_ramps;

    return expected_counter_burst;
}

adi_dm_err_t adi_dm_CalcRfpllPeriod(adi_dm_calc_rfpll_period_t * p, adi_dm_write_rfpll_period_t * out)
{
    double expected_count = 0;
    uint32_t r;
    memset(out, 0, sizeof(*out));
    for (r = 0; r < p->burst_profile->num_ramps_in_seq; r++) {
        expected_count += calc_rfpll_period_for_ramp(p->ramp_start_freq_hz, &p->burst_profile->ramp_profile[r], r == 0, p->burst_profile->num_seq_in_burst);
    }
    /* BIST103c: checks rfpll period estimate for burst with within 1% of estimate. */
    out->rfpll_period_high_limit = (uint32_t) (expected_count * (1.0 + 0.01));
    out->rfpll_period_low_limit = (uint32_t) (expected_count * (1.0 - 0.01));
    return ADI_DM_SUCCESS;
}
