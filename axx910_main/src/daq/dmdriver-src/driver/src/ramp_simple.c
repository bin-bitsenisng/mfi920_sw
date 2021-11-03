/* ramp_simple.c
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
#include <string.h>

adi_dm_err_t write_rampgen_regs(const adi_dm_ramp_profile_t * p)
{
    adi_dm_num_t dm_num;
    adi_dm_err_t res;

    comment("-->> Entering function write_rampgen_regs");

    //-- Set rampgen registers ---------------------------------------------

    comment("Set rampgen registers");

    // relying on bitfield sizes in adi_dm_ramp_profile_t to ensure
    // register bitfields do not overflow

    uint32_t rampgen_ramp_gen_del01 = 0;
    rampgen_ramp_gen_del01 |= p->del_0 << BITP_RAMPGEN_RAMP_GEN_DEL01_DEL_0;
    rampgen_ramp_gen_del01 |= (p->del_1 & 0x3FF) << BITP_RAMPGEN_RAMP_GEN_DEL01_DEL_1;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_RAMPGEN_RAMP_GEN_DEL01, rampgen_ramp_gen_del01);
    if (res != ADI_DM_SUCCESS)
        return res;

    uint32_t rampgen_ramp_gen_del12 = 0;
    rampgen_ramp_gen_del12 |= ((p->del_1 >> 10) & 0x3FF) << BITP_RAMPGEN_RAMP_GEN_DEL12_DEL_1;
    rampgen_ramp_gen_del12 |= p->del_2 << BITP_RAMPGEN_RAMP_GEN_DEL12_DEL_2;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_RAMPGEN_RAMP_GEN_DEL12, rampgen_ramp_gen_del12);
    if (res != ADI_DM_SUCCESS)
        return res;

    uint32_t rampgen_ramp_gen_step1 = p->ramp_steps_1;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_RAMPGEN_RAMP_GEN_STEP1, rampgen_ramp_gen_step1);
    if (res != ADI_DM_SUCCESS)
        return res;

    uint32_t rampgen_ramp_gen_step0 = p->ramp_steps_0;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_RAMPGEN_RAMP_GEN_STEP0, rampgen_ramp_gen_step0);
    if (res != ADI_DM_SUCCESS)
        return res;

    uint32_t rampgen_ramp_gen_dev0 = p->ramp_dev_0;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_RAMPGEN_RAMP_GEN_DEV0, rampgen_ramp_gen_dev0);
    if (res != ADI_DM_SUCCESS)
        return res;

    uint32_t rampgen_ramp_gen_dev1 = p->ramp_dev_1;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_RAMPGEN_RAMP_GEN_DEV1, rampgen_ramp_gen_dev1);
    if (res != ADI_DM_SUCCESS)
        return res;

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        uint32_t rampgen_ramp_gen_tx = 0;
        rampgen_ramp_gen_tx |= p->dm[dm_num].pa0_phase << BITP_RAMPGEN_RAMP_GEN_TX_PA0_PHASE;
        rampgen_ramp_gen_tx |= p->dm[dm_num].pa1_phase << BITP_RAMPGEN_RAMP_GEN_TX_PA1_PHASE;
        rampgen_ramp_gen_tx |= p->dm[dm_num].pa2_phase << BITP_RAMPGEN_RAMP_GEN_TX_PA2_PHASE;
        rampgen_ramp_gen_tx |= p->dm[dm_num].tx_pattern << BITP_RAMPGEN_RAMP_GEN_TX_TX_PATTERN;
        rampgen_ramp_gen_tx |= p->dm[dm_num].phase_step << BITP_RAMPGEN_RAMP_GEN_TX_PHASE_STEP;
        rampgen_ramp_gen_tx |= p->dm[dm_num].ramp_stat_bit_0 << BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_0;
        rampgen_ramp_gen_tx |= p->dm[dm_num].ramp_stat_bit_1 << BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_1;
        rampgen_ramp_gen_tx |= p->dm[dm_num].ramp_stat_bit_2 << BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_2;
        res = adi_dm_Write(dm_num, REG_RAMPGEN_RAMP_GEN_TX, rampgen_ramp_gen_tx);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    uint32_t rampgen_ramp_gen_afecnt = 0;
    rampgen_ramp_gen_afecnt |= p->afe_start_off_time << BITP_RAMPGEN_RAMP_GEN_AFECNT_AFE_START_OFF_TIME;
    rampgen_ramp_gen_afecnt |= p->afe_ramp_time << BITP_RAMPGEN_RAMP_GEN_AFECNT_AFE_RAMP_TIME;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_RAMPGEN_RAMP_GEN_AFECNT, rampgen_ramp_gen_afecnt);
    if (res != ADI_DM_SUCCESS)
        return res;

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        uint32_t rampgen_ramp_gen_phase_mod = 0;
        rampgen_ramp_gen_phase_mod |= p->dm[dm_num].pa0_phase_dev << BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA0_PHASE_DEV;
        rampgen_ramp_gen_phase_mod |= p->dm[dm_num].pa1_phase_dev << BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA1_PHASE_DEV;
        rampgen_ramp_gen_phase_mod |= p->dm[dm_num].pa2_phase_dev << BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA2_PHASE_DEV;
        rampgen_ramp_gen_phase_mod |= p->num_samples << BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_NUM_SAMPLES;
        res = adi_dm_Write(dm_num, REG_RAMPGEN_RAMP_GEN_PHASE_MOD, rampgen_ramp_gen_phase_mod);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    comment("-->> Exiting function write_rampgen_regs");
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_BuiltinMimoSetup(const adi_dm_builtin_mimo_setup_t * p)
{
    adi_dm_err_t res;

    comment("-->> Entering function adi_dm_BuiltinMimoSetup");

    res = write_rampgen_regs(&p->ramp_profile);
    if (res != ADI_DM_SUCCESS) {
        return res;
    }

    res = adi_dm_ramp_config(&p->ramp_config, p);
    if (res != ADI_DM_SUCCESS) {
        return res;
    }

    if (adi_dm_enable_trigger_pin_on_program) {
        /* BIST49 explicit control of when external trigger is allowed
         * for compatible with past APIs the trig pin is enabled as soon
         * as the ramp is programmed.
         */
        comment("ADI_ADAR690x_FW_EXT_TRIG_EN");
        res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_EXT_TRIG_EN);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    comment("-->> Exiting function adi_dm_BuiltinMimoSetup");
    return ADI_DM_SUCCESS;
}
