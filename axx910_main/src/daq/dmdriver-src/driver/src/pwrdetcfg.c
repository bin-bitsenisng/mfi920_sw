/* pwrdetcfg.c
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
#include <string.h>
#include <stdio.h>

adi_dm_err_t adi_dm_CalcPwrDetCfg(adi_dm_burst_profile_t * p, adi_dm_power_detector_meas_task_t * out)
{
    adi_dm_num_t dm_num;
    uint32_t i;

    memset(out, 0, sizeof(*out));
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        uint32_t active_tx = 0;
        bool active_combinations[8] = { false, false, false, false, false, false, false, false };
        if (p->tx_overlay_len > 0) {
            for (i = 0; i < p->tx_overlay_len; i++) {
                uint32_t patt = p->tx_overlay[dm_num][i].tx_pattern;
                active_tx |= patt;
                active_combinations[patt] = true;
            }
        } else {
            for (i = 0; i < p->num_ramps_in_seq; i++) {
                uint32_t patt = p->ramp_profile[i].dm[dm_num].tx_pattern;
                active_tx |= patt;
                active_combinations[patt] = true;
            }
        }
        for (i = 0; i < ADI_DM_NUM_TX; i++) {
            if ((active_tx & (1u << i)) != 0) {
                out->dm[dm_num].tx_active[i] = true;
            }
        }
        
        if (active_combinations[0]) {   /* TX0, TX1 & TX2 inactive */
            out->dm[dm_num].tx0_inactive_when_all_inactive = true;
            out->dm[dm_num].tx1_inactive_when_all_inactive = true;
            out->dm[dm_num].tx2_inactive_when_all_inactive = true;
        }
        
        if (active_combinations[1]) {   /* TX0 active, TX1 & TX2 inactive */
            out->dm[dm_num].tx1_inactive_when_tx0_active = true;
            out->dm[dm_num].tx2_inactive_when_tx0_active = true;
        }
        if (active_combinations[2]) {   /* TX1 active, TX0 & TX2 inactive */
            out->dm[dm_num].tx0_inactive_when_tx1_active = true;
            out->dm[dm_num].tx2_inactive_when_tx1_active = true;
        }
        if (active_combinations[3]) {   /* TX0 & TX1 active, TX2 inactive */
            out->dm[dm_num].tx2_inactive_when_tx0_tx1_active = true;
        }
        if (active_combinations[4]) {   /* TX2 active, TX0 & TX1 inactive */
            out->dm[dm_num].tx0_inactive_when_tx2_active = true;
            out->dm[dm_num].tx1_inactive_when_tx2_active = true;
        }
        if (active_combinations[5]) {   /* TX0, TX2 active, TX1 inactive */
            out->dm[dm_num].tx1_inactive_when_tx0_tx2_active = true;
        }
        if (active_combinations[6]) {   /* TX1, TX2 active, TX0 inactive */
            out->dm[dm_num].tx0_inactive_when_tx1_tx2_active = true;
        }
    }
    return ADI_DM_SUCCESS;
}
