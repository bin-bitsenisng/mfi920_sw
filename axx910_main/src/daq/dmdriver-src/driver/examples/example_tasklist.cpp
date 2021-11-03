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

#include "adi_dmdriver.h"
#include "adar690x_fw.h"
#include "application.h"
#include "tasklist_util.h"
#include <string.h>
#include <math.h>
#include <assert.h>

#include "../src/adar690x_regs.h"
#include "../src/localdefs.h"

/***********************************************
* Example using tasklists instead of adi_dm_PeriodicCal
************************************************
*/

/* This example has the same functionality as example_dma_ramp
 * with BIST==0, HARDWARE_TRIGGER==0 and AUTO_SLEEP==0.
 */

static void setup_tasklist_pool(example_config_t * p);
static void example_tasklist_loop(example_config_t * p);

/* The top level of the example
 * has the same structure as example_dma_ramp
 */

void example_tasklist(void)
{
    example_config_t configs;
    adi_dm_err_t res;

    /***********************************
    * Part 1: initialize the device
    ************************************
    */
    /* This part is split out into a separate example
     * because it is common to all three examples.
     */

    /* 1a: Common initialization */
    example_init(&configs);
    adi_dm_Log("---> In example_tasklist");

    /* Skip 1b and 1c.
     * As BIST is not supported in this example
     * no need for t0 system calibration data.
     */

    /* 1d: write required tasklists to device memory.
     */
    setup_tasklist_pool(&configs);

    /***********************************************
    * Part 2: Loop triggering bursts
    ***********************************************
    */
    example_tasklist_loop(&configs);

    /***********************************************
    * Part 3: Finalization
    ***********************************************
    */
    /* Power down the device. */
    res = adi_dm_PowerDown();
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_PowerDown", res, __FILE__, __LINE__);
    }

    /* Release any resource used by the diver. */
    adi_dm_Log("---> Exiting example_tasklist");
    adi_dm_FiniDriver();
}

/* Names for our tasklist indexes */
enum {
    TL_TRIGGER,
    TL_MEASURE_TEMP,
    TL_NO_CAL,
    TL_LOCHAIN_CAL_BP0,
    TL_LOCHAIN_CAL_BP1,
    TL_TXPA_ADJ_CAL,
    TL_ADC_PHASE_CAL,
    TL_RX_CAL,
    TL_SWITCH_TO_BP0,
    TL_SWITCH_TO_BP1,
};

static const uint32_t tl_lochain_cal[] = { TL_LOCHAIN_CAL_BP0, TL_LOCHAIN_CAL_BP1 };
static const uint32_t tl_switch_to_bp[] = { TL_SWITCH_TO_BP0, TL_SWITCH_TO_BP1 };

static void setup_tasklist_pool(example_config_t * p)
{
    adi_dm_err_t res;
    int bp;
    /* tasklist_builder_t is implemented by the code in tasklist_util.c
     * this could go on the stack but is declared static as embedded stacks
     * are often quire small.
     */
    static tasklist_builder_t b;

    start_building_tasklists(&b);

    /* Tasklists are lists of commands stored on the device which can be
     * called with a single SPI command. The tasklist command identifies
     * a list by its index. The tasklist command can be broadcast to all
     * devices so we think of the lists on the different devices, which
     * may not be identical, as acting together as one composite command.
     * See the lochain tasklist below as an example of a tasklist that is
     * not identical on all devices.
     *
     * Many calibrations should only be run when temperature has changed
     * more than some threshold. This cannot be represented in the tasklist
     * itself so we select a tasklist with the right calibration based upon
     * the temperature. We never run more than one temperature dependent
     * calibration per offtime and have split up the other tasks from
     * adi_dm_PeriodicCalibration in to tasklist too. Splitting the tasks
     * accross offtimes also reduces the processing time per offtime.
     *
     * We run two tasklists per offtime. One to wake  and trigger the
     * next burst the other to recalibrate and sleep.
     */

    /* tasklist to trigger next burst */
    start_tasklist(TL_TRIGGER, &b);
    add_task(ADI_DM_ALL_DIGIMMICS, adcpll_align, &b);
    add_task(ADI_DM_MASTER, ramp_trig, &b);
    finish_tasklist(&b);

    /* tasklists to recalibrate
     * Always run RFPLL_BOW_CAL.
     * Read temperature once every 6 offtimes,
     * and either measure temperature or
     * run a temperature dependent calibration if needed
     * in each of the 5 other offtimes.
     */
    /* stage 0: measure temperature */
    start_tasklist(TL_MEASURE_TEMP, &b);
    add_task(ADI_DM_ALL_DIGIMMICS, rfpll_bow_cal, &b);
    add_task(ADI_DM_ALL_DIGIMMICS, temp_measure, &b);
    finish_tasklist(&b);

    /* stage 1: read the temperature
     * tasklist for no recalibration needed
     */
    start_tasklist(TL_NO_CAL, &b);
    add_task(ADI_DM_ALL_DIGIMMICS, rfpll_bow_cal, &b);
    finish_tasklist(&b);

    /* stage 2: recalibrate LO chain */
    /* LO chain calibration depends on burst configuration
     * as it locks the RFPLL. So a different tasklist is
     * generated for each burst profile.
     */
    for (bp = 0; bp < p->num_burst_profiles; bp++) {
        uint64_t ramp_start_freq_hz = p->bp[bp].rfpll.ramp_start_freq_hz;
        float ramp_bw_Mhz = p->bp[bp].rfpll.ramp_bw_Mhz;
        uint64_t max_ramp_freq_hz;

        if (ramp_bw_Mhz >= 0.0F) {
            int64_t ramp_bw_hz = (int64_t) ramp_bw_Mhz * 1000000LL;
            max_ramp_freq_hz = (uint64_t) ((int64_t) ramp_start_freq_hz + ramp_bw_hz);
        } else {
            max_ramp_freq_hz = ramp_start_freq_hz;
        }

        assert(bp < sizeof(tl_lochain_cal) / sizeof(tl_lochain_cal[0]));
        start_tasklist(tl_lochain_cal[bp], &b);
        add_task(ADI_DM_ALL_DIGIMMICS, rfpll_bow_cal, &b);
        if (max_ramp_freq_hz > ramp_start_freq_hz) {
            add_tasku64(ADI_DM_MASTER, rfpll_lock, max_ramp_freq_hz, &b);
        }
        add_task(ADI_DM_ALL_DIGIMMICS, lochain_cal, &b);
        if (max_ramp_freq_hz > ramp_start_freq_hz) {
            add_tasku64(ADI_DM_MASTER, rfpll_lock, ramp_start_freq_hz, &b);
        }
        finish_tasklist(&b);
    }

    /* stage 3: run TXPA_ADJ if necessary */
    start_tasklist(TL_TXPA_ADJ_CAL, &b);
    add_task(ADI_DM_ALL_DIGIMMICS, rfpll_bow_cal, &b);
    add_task(ADI_DM_ALL_DIGIMMICS, txpa_adj, &b);
    finish_tasklist(&b);

    /* stage 4: run ADC_PHASE_CAL is necessary */
    start_tasklist(TL_ADC_PHASE_CAL, &b);
    add_task(ADI_DM_ALL_DIGIMMICS, rfpll_bow_cal, &b);
    add_task(ADI_DM_ALL_DIGIMMICS, adc_phase_cal, &b);
    finish_tasklist(&b);

    /* stage 5: run rx recalibration if needed */
    start_tasklist(TL_RX_CAL, &b);
    add_task(ADI_DM_ALL_DIGIMMICS, rfpll_bow_cal, &b);
    add_task(ADI_DM_ALL_DIGIMMICS, hpf_cal, &b);
    add_task(ADI_DM_ALL_DIGIMMICS, rxgain_cal, &b);
    finish_tasklist(&b);

    /* Switching to another burst profile can also be done
     * by tasklist.
     */
    for (bp = 0; bp < p->num_burst_profiles; bp++) {
        uint64_t ramp_start_freq_hz = p->bp[bp].rfpll.ramp_start_freq_hz;
        uint32_t ramp_start_freq_hz_lo = (uint32_t) (ramp_start_freq_hz & 0xFFFFFFFF);
        uint32_t ramp_start_freq_hz_hi = (uint32_t) ((ramp_start_freq_hz >> 32) & 0xFFFFFFFF);
        uint32_t ramp_bw_Mhz = *(uint32_t *) & p->bp[bp].rfpll.ramp_bw_Mhz;
        adi_dm_ramp_config_t *ramp_config = &p->bp[bp].dma.ramp_config;
        adi_dm_afe_setup_t *afe_setup = &p->bp[bp].afe;
        adi_dm_tx_setup_t *tx_setup = &p->bp[bp].tx;
        uint32_t mask, bits;
        adi_dm_num_t dm_num;

        assert(bp < sizeof(tl_switch_to_bp) / sizeof(tl_switch_to_bp[0]));
        start_tasklist(tl_switch_to_bp[bp], &b);

        /* example_switch_config as a set of tasklists,
         * taking the pessimistic view we have to change everything.
         */
        /* adi_dm_RfpllReconfig */
        /* rmw task = read-modify-write */
        add_task3(ADI_DM_MASTER, rmw, ADI_ADAR690x_CFG_RAMP_BW_MHZ, ramp_bw_Mhz, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_MASTER, rmw, ADI_ADAR690x_CFG_RAMP_START_FREQ_HZ, ramp_start_freq_hz_lo, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_MASTER, rmw, ADI_ADAR690x_CFG_RAMP_START_FREQ_HZ + 4, ramp_start_freq_hz_hi, 0xFFFFFFFF, &b);
        add_task(ADI_DM_MASTER, rfpll_ramp_setup, &b);
        /* adi_dm_DmaRampSetup */
        /* switch burst profile */
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, DMA_RAMPGEN_CHAN_SRC_PTR, p->bp[bp].dma.bpid, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, REG_UDMA_SWREQ, 3 << DMA_RAMPGEN_CHAN_NO, 0xFFFFFFFF, &b);
        /* adi_dm_ramp_config (rest of adi_dm_DmaRampSetup has already run) */
        /* Set misc_filter_ctrl */
        mask = 0;
        bits = 0;
        mask |= BITM_MISC_MISC_FILTER_CTRL_FILTER_DECIM_RATIO;
        bits |= ramp_config->filter_decim_ratio << BITP_MISC_MISC_FILTER_CTRL_FILTER_DECIM_RATIO;
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, REG_MISC_MISC_FILTER_CTRL, bits, mask, &b);
        /* Set misc_filter_ctrl_1 */
        mask = 0;
        bits = 0;
        mask |= BITM_MISC_MISC_FILTER_CTRL_1_FILTER_VALID_DELAY;
        bits |= ramp_config->filter_valid_delay << BITP_MISC_MISC_FILTER_CTRL_1_FILTER_VALID_DELAY;
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, REG_MISC_MISC_FILTER_CTRL_1, bits, mask, &b);
        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            /* ramp_config3 */
            mask = 0;
            bits = 0;
            mask |= BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_EN;
            bits |= (ramp_config->pga_shunt_en << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_EN) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_EN;
            mask |= BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_START_DEL;
            bits |= (ramp_config->pga_shunt_start_del << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_START_DEL) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_START_DEL;
            mask |= BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_STOP_DEL;
            bits |= (ramp_config->pga_shunt_stop_del << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_STOP_DEL) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_STOP_DEL;
            mask |= BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_VGA_GAUSS_DIS;
            bits |= (ramp_config->dm[dm_num].vga_gauss_dis << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_VGA_GAUSS_DIS) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_VGA_GAUSS_DIS;
            add_task3(dm_num, rmw, REG_RF_ADPLL_RFPLL_RAMP_CONFIG3, bits, mask, &b);
            /* ramp_config2 */
            mask = 0;
            bits = 0;
            mask |= BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_RAMP_COUNT;
            bits |= (ramp_config->ramp_count << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG2_RAMP_COUNT) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_RAMP_COUNT;
            add_task3(dm_num, rmw, REG_RF_ADPLL_RFPLL_RAMP_CONFIG2, bits, mask, &b);
            /* ramp_config1 */
            mask = 0;
            bits = 0;
            mask |= BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_ON_PATT;
            bits |= (ramp_config->dm[dm_num].vga_on_patt << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_ON_PATT) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_ON_PATT;
            mask |= BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_DELAY_EN;
            bits |= (ramp_config->dm[dm_num].phase_delay_en << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_DELAY_EN) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_DELAY_EN;
            mask |= BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_MOD_EN;
            bits |= (ramp_config->dm[dm_num].phase_mod_en << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_MOD_EN) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_MOD_EN;
            mask |= BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA_OFF_TIME;
            bits |= (ramp_config->dm[dm_num].pa_off_time << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA_OFF_TIME) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA_OFF_TIME;
            mask |= BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEPS;
            bits |= (ramp_config->dm[dm_num].vga_gain_steps << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEPS) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEPS;
            mask |= BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEP_DIV;
            bits |= (ramp_config->dm[dm_num].vga_gain_step_div << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEP_DIV) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEP_DIV;
            add_task3(dm_num, rmw, REG_RF_ADPLL_RFPLL_RAMP_CONFIG1, bits, mask, &b);
            /* ramp_config0 */
            mask = 0;
            bits = 0;
            mask |= BITM_RF_ADPLL_RFPLL_RAMP_CONFIG0_VGA_SYNC_DATA_VALID;
            bits |= (ramp_config->dm[dm_num].vga_sync_data_valid << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG0_VGA_SYNC_DATA_VALID) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG0_VGA_SYNC_DATA_VALID;
            add_task3(dm_num, rmw, REG_RF_ADPLL_RFPLL_RAMP_CONFIG0, bits, mask, &b);
        }
        /* adi_dm_AfeSetup (assuming all channels are set the same and only gains changing) */
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, ADI_ADAR690x_CFG_HPF_FC_RX_CHAN0, afe_setup->hpf_fc, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, ADI_ADAR690x_CFG_HPF_GAIN_RX_CHAN0, afe_setup->hpf_gain, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, ADI_ADAR690x_CFG_PGA_GAIN_RX_CHAN0, afe_setup->pga_gain, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, ADI_ADAR690x_CFG_ADC_GAIN_RX_CHAN0, afe_setup->adc_gain, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, ADI_ADAR690x_CFG_HPF_FC_RX_CHAN1, afe_setup->hpf_fc, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, ADI_ADAR690x_CFG_HPF_GAIN_RX_CHAN1, afe_setup->hpf_gain, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, ADI_ADAR690x_CFG_PGA_GAIN_RX_CHAN1, afe_setup->pga_gain, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, ADI_ADAR690x_CFG_ADC_GAIN_RX_CHAN1, afe_setup->adc_gain, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, ADI_ADAR690x_CFG_HPF_FC_RX_CHAN2, afe_setup->hpf_fc, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, ADI_ADAR690x_CFG_HPF_GAIN_RX_CHAN2, afe_setup->hpf_gain, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, ADI_ADAR690x_CFG_PGA_GAIN_RX_CHAN2, afe_setup->pga_gain, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, ADI_ADAR690x_CFG_ADC_GAIN_RX_CHAN2, afe_setup->adc_gain, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, ADI_ADAR690x_CFG_HPF_FC_RX_CHAN3, afe_setup->hpf_fc, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, ADI_ADAR690x_CFG_HPF_GAIN_RX_CHAN3, afe_setup->hpf_gain, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, ADI_ADAR690x_CFG_PGA_GAIN_RX_CHAN3, afe_setup->pga_gain, 0xFFFFFFFF, &b);
        add_task3(ADI_DM_ALL_DIGIMMICS, rmw, ADI_ADAR690x_CFG_ADC_GAIN_RX_CHAN3, afe_setup->adc_gain, 0xFFFFFFFF, &b);
        add_task(ADI_DM_ALL_DIGIMMICS, pga_cal, &b);
        add_task(ADI_DM_ALL_DIGIMMICS, hpf_cal, &b);
        /* adi_dm_TxSetup */
        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            int i;
            const uint32_t tx_mask = (1 << ADI_DM_NUM_TX) - 1;
            uint32_t tx_enable = tx_setup->dm[dm_num].tx_enable;
            uint32_t tx_disable = tx_enable ^ tx_mask;
            uint32_t continuous_pa = tx_setup->dm[dm_num].continuous_pa & tx_enable;
            for (i = 0; i < ADI_DM_NUM_TX; i++) {
                add_task3(dm_num, rmw, ADI_ADAR690x_CFG_PWR_TX0 + i * 4, tx_setup->dm[dm_num].pa_gain_backoff_db[i], 0xFFFFFFFF, &b);
            }
            if (tx_enable) {
                uint32_t arg0 = ADI_ADAR690x_BITM_POWER_UP_REQUEST | ADI_ADAR690x_BITM_POWER_PERMANENT | (tx_enable << ADI_ADAR690x_BITP_POWER_TX0);
                uint32_t arg1 = continuous_pa << ADI_ADAR690x_BITP_CONTINUOUS_PA_TX0;
                add_task2(dm_num, power_manage, arg0, arg1, &b);
            }
            if (tx_disable) {
                uint32_t arg0 = ADI_ADAR690x_BITM_POWER_DOWN_REQUEST | ADI_ADAR690x_BITM_POWER_PERMANENT | (tx_disable << ADI_ADAR690x_BITP_POWER_TX0);
                uint32_t arg1 = 0;
                add_task2(dm_num, power_manage, arg0, arg1, &b);
            }
            if (tx_enable) {
                add_task(dm_num, txpa_cal, &b);
            }
            add_task3(dm_num, rmw, ADI_ADAR690x_CFG_PWR_SUP_CHK, tx_enable << 8, 0x700, &b);
        }
        finish_tasklist(&b);
    }

    res = adi_dm_TasklistPoolSetup(&b.setup, &p->device_mem_handle);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_TasklistPoolSetup", res, __FILE__, __LINE__);
    }
}

/* The tasklist version od the steady-state code.
 * Compare with example_burst_loop.
 */
static void example_tasklist_loop(example_config_t * p)
{
    float lo_chain_temp, txpa_adj_temp, adc_phase_temp, rx_cal_temp;
    float current_temp;
    adi_dm_err_t res;
    bool done;
    uint32_t stage = 0;

    /* Read initial temperature. This will have been calculated in CHIP_INIT
     * called from adi_dm_PowerUp().
     */
    res = adi_dm_ReadF32(ADI_DM_MASTER, ADI_ADAR690x_STS_RX2_TEMP, &current_temp);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_ReadF32(ADI_ADAR690x_STS_RX2_TEMP)", res, __FILE__, __LINE__);
    }
    lo_chain_temp = current_temp;
    txpa_adj_temp = current_temp;
    adc_phase_temp = current_temp;
    rx_cal_temp = current_temp;

    /* Enable RAMPON on GPIO8 to detect end of bursts in the loop below. */
    res = adi_dm_PinMux(ADI_DM_MASTER, ADI_DM_GPIO8, 1, 1);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_PinMux", res, __FILE__, __LINE__);
    }

    /* Synchronize LOCHAIN_CAL on slaves with master
     * so when TL_LOCHAIN_CAL is run the slaves wait
     * until the master has changed rf frequency.
     */
    /* Value format:
     * * Bit 0: enable master/slave sync
     * * Bit 1 to 7: master delay in us
     * * Bit 8 to 15: slave timeout in us
     */
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_LOCHAIN_MST_SLV_SYNC, 0x4003);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_Write", res, __FILE__, __LINE__);
    }

    done = false;
    while (!done) {
        /* Start measuring cycle time (time from start of one ramp busrt
         * to start of next).
         */
        platform_start_timer(p->cycle_time_us);

        /* kick off next burst */
        res = adi_dm_Tasklist(ADI_DM_ALL_DIGIMMICS, TL_TRIGGER);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_Tasklist(TL_TRIGGER)", res, __FILE__, __LINE__);
        }

        /* wait for burst completion */
        res = adi_dm_WaitGPIO(ADI_DM_MASTER, ADI_DM_GPIO8, false, TIMEOUT_NS);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_WaitGPIO", res, __FILE__, __LINE__);
        }
        adi_dm_DelayNS(1200);

        done = burst_loop_should_exit(p);
        if (!done) {
            /* select tasklist to run in offtime */
            uint32_t offtime_tasklist;

            int next_bp_idx = get_next_burst_profile(p);
            if (next_bp_idx != p->cur_bp_idx) {
                /* Setup the next burst profile. */
                offtime_tasklist = tl_switch_to_bp[next_bp_idx];
                p->cur_bp_idx = next_bp_idx;
            } else {
                /* Normally we step through the 6 stages selecting
                 * tasklist based on stage and temperature.
                 */
                switch (stage) {
                case 0:
                    /* measure temperatue */
                    offtime_tasklist = TL_MEASURE_TEMP;
                    break;
                case 1:
                    /* Read back temperature:
                     * Use RX2 sensor on master to decide when to run calibrations.
                     * This is consistently the hottest sensor in a system, cascaded or otherwise.
                     */
                    res = adi_dm_ReadF32(ADI_DM_MASTER, ADI_ADAR690x_STS_RX2_TEMP, &current_temp);
                    if (res != ADI_DM_SUCCESS) {
                        platform_error("adi_dm_ReadF32(ADI_ADAR690x_STS_RX2_TEMP)", res, __FILE__, __LINE__);
                    }
                    /* run tasks required for every offtime */
                    offtime_tasklist = TL_NO_CAL;
                    break;
                case 2:
                    if (fabsf(current_temp - lo_chain_temp) > 20.0f) {
                        offtime_tasklist = tl_lochain_cal[p->cur_bp_idx];
                        lo_chain_temp = current_temp;
                    } else {
                        offtime_tasklist = TL_NO_CAL;
                    }
                    break;
                case 3:
                    if (fabsf(current_temp - txpa_adj_temp) > 10.0f) {
                        offtime_tasklist = TL_TXPA_ADJ_CAL;
                        txpa_adj_temp = current_temp;
                    } else {
                        offtime_tasklist = TL_NO_CAL;
                    }
                    break;
                case 4:
                    if (fabsf(current_temp - adc_phase_temp) > 30.0f) {
                        offtime_tasklist = TL_ADC_PHASE_CAL;
                        adc_phase_temp = current_temp;
                    } else {
                        offtime_tasklist = TL_NO_CAL;
                    }
                    break;
                case 5:
                    if (fabsf(current_temp - rx_cal_temp) > 20.0f) {
                        offtime_tasklist = TL_RX_CAL;
                        rx_cal_temp = current_temp;
                    } else {
                        offtime_tasklist = TL_NO_CAL;
                    }
                    break;
                default:
                    platform_error("coding error", 0, __FILE__, __LINE__);
                }
                stage = (stage + 1) % 6;
            }
            res = adi_dm_Tasklist(ADI_DM_ALL_DIGIMMICS, offtime_tasklist);
            if (res != ADI_DM_SUCCESS) {
                platform_error("adi_dm_Tasklist(offtime_tasklist)", res, __FILE__, __LINE__);
            }

            /* Do whatever is needed to prepare the host side to receive the next burst. */
            platform_prep_host_for_trigger();
            /* Wait until offtime is done and it is time for next trigger. */
            platform_wait_for_timer();
        }
    }
}
