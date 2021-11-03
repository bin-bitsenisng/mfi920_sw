/* example_init.c
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
#include "bts_application.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/***********************************************
* Initial part of the example common to both
* example_product, and example_syscal.
* Construct application parameters and
* initialize devices to initial configuration.
************************************************
*/

/* parameter to example_init */
typedef struct {
    adi_dm_power_up_t power_up;
#if LVDS_PART == 1
    adi_dm_lvds_setup_t lvds;
#else
    adi_dm_mipi_setup_t mipi;
#endif
    adi_dm_afe_setup_t afe;
    adi_dm_tx_setup_t tx;
} bts_afi910_init_t;

static bts_afi910_init_t bts_afi910_init_p;
static platform_data_plane_init_t data_plane_p;
static adi_dm_burst_profile_t burst_profiles[NUM_BURST_PROFILES];
static adi_dm_ramp_profile_t ramp_profiles[NUM_BURST_PROFILES][MAX_NUM_RAMPS_IN_SEQ];
static adi_dm_tx_overlay_t tx_overlay[ADI_DM_NUM_DIGIMMIC][MAX_TX_OVERLAY_LEN];

static int physical_mmic_num[] = {1, 2, 0, 3};

static void bts_afi910_calc_dma_ramp_parameters(bts_afi910_config_t * p);

void bts_afi910_init(bts_afi910_config_t * p)
{
    adi_dm_afe_setup_t default_afe_setup;
    adi_dm_tx_setup_t default_tx_setup;
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    uint32_t tx;
    int i;
    uint32_t addr,val;

    /***********************************
    * Part 1: compute parameters
    ************************************
    */
    /* Compute ramp parameters.
     * This uses the driver function adi_dm_CalcRamp to compute low level
     * ramp profiles as well as filling in other parameter stuctures.
     * However it could be run entirely offline reducing runtime overhead.
     */
    bts_afi910_calc_dma_ramp_parameters(p);

    /* Initialize drivers etc. on the host platform */
    platform_init();

    /* initialize the driver */
    adi_dm_InitDriver();
    
    /* Power up and initialize the device. */
    res = adi_dm_PowerUp(&bts_afi910_init_p.power_up);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_PowerUp", res, __FILE__, __LINE__);
    }

    /* Initialize dataport. */
#if LVDS_PART == 1
    res = adi_dm_LvdsSetup(&example_init_p.lvds);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_LvdsSetup", res, __FILE__, __LINE__);
    }
#else
    res = adi_dm_MipiSetup(&bts_afi910_init_p.mipi);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_MipiSetup", res, __FILE__, __LINE__);
    }
#endif
    // platform_mipi_vc_id_change(p->cur_bp_idx);
    //platform mipi driver init
    platform_mipi_init();



    /***********************************************
     * Part 3: Store burst profiles in device memory.
     ***********************************************
     *
     * 'Burst profile' is the driver name for the data to be loaded to the RAMP_GEN
     * registers by DMA during a burst, and the DMA descriptors to drive the process.
     * Each burst profile consists of a sequence of ramp profiles and a repeat count.
     * The ramp count passed to adi_dm_DmaRampSetup should equal the length of the
     * sequence times the repeat count of the burst profile.
     *
     * Multiple burst profiles can be stored in device memory. At any time the DMA
     * engine is configured to load only one but it is relatively cheap to change
     * the DMA engine setup.
     *
     * As burst profiles are stored, device memory allocation is tracked through
     * the 'device_mem_handle', an inout parameter which should be 0 on the first
     * call to adi_dm_BurstProfileSetup. Each call returns an identifier word
     * which will be used to refer to the burst profile in subsequent calls.
     */
    p->device_mem_handle = 0;
    for (i = 0; i < p->num_burst_profiles; i++) {
        res = bts_afi910_rfic_dma_setup(&burst_profiles[i], &p->device_mem_handle, &p->bp[i].dma.bpid);         // <== In this function, uDMA in RFIC is set.
        printf("%d RFIC burstprofile setup complete!!\n",i);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_BurstProfileSetup", res, __FILE__, __LINE__);
        }
    }



    /* Power up default afe settings for comparison below */
    memset(&default_afe_setup, 0, sizeof(default_afe_setup));
    default_afe_setup.rx_channels = 0;
    default_afe_setup.hpf_fc = ADI_DM_HPF_FC_1_MHZ;
    default_afe_setup.hpf_gain = ADI_DM_HPF_GAIN_6_DB;
    default_afe_setup.pga_gain = ADI_DM_PGA_GAIN_0_DB;
    default_afe_setup.adc_gain = ADI_DM_ADC_GAIN_0_DB;

    if (memcmp(&p->bp[p->cur_bp_idx].afe, &default_afe_setup, sizeof(adi_dm_afe_setup_t)) != 0) {
        /* Reconfigure AFE.
         * If default configuration of max gain for all RX channels
         * is acceptable, this call can be omitted.
         */
        res = adi_dm_AfeSetup(&p->bp[p->cur_bp_idx].afe);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_AfeSetup", res, __FILE__, __LINE__);
        }
    }

    /* Power up default tx settings for comparison below */
    memset(&default_tx_setup, 0, sizeof(default_tx_setup));
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        default_tx_setup.dm[dm_num].tx_enable = 7;      /* enable all Tx */
        for (tx = 0; tx < ADI_DM_NUM_TX; tx++) {
            default_tx_setup.dm[dm_num].pa_gain_backoff_db[tx] = 0;
        }
    }

    if (memcmp(&p->bp[p->cur_bp_idx].tx, &default_tx_setup, sizeof(adi_dm_afe_setup_t)) != 0) {
        /* Power down TX channels that will not be used
         * or alter Tx power. If default configuration of
         * all TX channels fully powered is acceptable,
         * this call can be omitted.
         */
        res = adi_dm_TxSetup(&p->bp[p->cur_bp_idx].tx);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_TxSetup", res, __FILE__, __LINE__);
        }
    }

    /* Configure RFPLL and DMA registers for first burst profile */
    res = bts_afi910_DmaRampSetup(&p->bp[p->cur_bp_idx].dma);       // <== initial DMA channel setting is here
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_DmaRampSetup", res, __FILE__, __LINE__);
    }
    
    /* initialise RFPLL period estimate. */
    res = adi_dm_WriteRfpllPeriod(&p->bp[p->cur_bp_idx].rfpllperiod);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_WriteRfpllPeriod", res, __FILE__, __LINE__);
    }
    
    /* Do whatever is needed for host to receive data.
     * Not strictly necessary host receives data during syscal
     * but this might be an assumption of the platform code.
     */
    platform_data_plane_init(&data_plane_p);
}

/***********************************************
* Calculate parameters for the examples.
************************************************
*/

static void bts_afi910_calc_dma_ramp_parameters(bts_afi910_config_t * p)
{
    adi_dm_err_t res;
    adi_dm_ramp_shape_t shape;
    adi_dm_calc_rfpll_period_t calc_rfpll_period;
    adi_dm_actual_ramp_shape_t actual[NUM_BURST_PROFILES];
    adi_dm_ramp_profile_t profile[NUM_BURST_PROFILES];
    adi_dm_ramp_config_t config[NUM_BURST_PROFILES];
    adi_dm_num_t dm_num;
    uint32_t i, tx, ii;

    memset(p, 0, sizeof(*p));
    printf("D_MODE_PROFILE1_NUM : %d, L_MODE_PROFILE1_NUM : %d, M_MODE_PROFILE1_NUM : %d, S_MODE_PROFILE1_NUM : %d\n",D_MODE_PROFILE1_NUM,L_MODE_PROFILE1_NUM,M_MODE_PROFILE1_NUM,S_MODE_PROFILE1_NUM);

    p->cycle_time_us = 0;
    p->offtime_sleep_us = 0;

    p->num_burst_profiles = TOTAL_BURST_NUM;

    /* High level 4 Mode profiles are set... */
    memset(&shape, 0, sizeof(shape));
    shape.slope0_time_us = D_MODE_RAMP_TIME_US;
    shape.slope1_time_us = 0;
    shape.delay0_time_us = 0;
    shape.delay1_time_us = 0;
    shape.delay2_time_us = D_MODE_RAMP_END_DELAY_US;
    shape.ramp_bw_Mhz = D_MODE_RAMP_BANDWIDTH_MHZ;
    shape.num_samples = D_MODE_NUM_SAMPLES_PER_RAMP;
    shape.sample_start_time_us = D_MODE_SAMPLES_START_TIME_US;     /* Place sample window in slope0 as far right as possible */
    shape.pga_shunt_en = true;          // In driver 3.3.4 version, enable pga_shunt is forced.
    shape.pga_shunt_start_del_us = 0;   /* Chose default value. */
    shape.pga_shunt_stop_del_us = 0;    /* Chose default value. */
    shape.filter_valid_delay = FILTER_VALID_DELAY;
    shape.decim_ratio = DECIMATION_FACTOR;
    shape.ref_freq_hz = REF_FREQ_HZ;
    res = adi_dm_CalcRamp(&shape, &profile[D_MODE_PROFILE1_NUM], &config[D_MODE_PROFILE1_NUM], &actual[D_MODE_PROFILE1_NUM]);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_CalcRamp", res, __FILE__, __LINE__);
    }

    /* The global variables burst_loop_p and burst_profiles
     * contain the ramp configuration for the DMA example.
     */
    

    /* From this point, */
    {
        // D-MODE consists of one ramp profile.  =>> see tx_overlaysetting in example_init.c when tx_overlay length is greater than 0
        burst_profiles[D_MODE_BURST_NUM].num_ramps_in_seq = D_MODE_NUM_RAMPS_IN_SEQ;
        burst_profiles[D_MODE_BURST_NUM].num_seq_in_burst = D_MODE_NUM_SEQ_IN_BURST; //to satisfy all possible power down measurements in adi_dm_PowerDetectorMeasTask, set minimum burst size to be 228.
        burst_profiles[D_MODE_BURST_NUM].tx_overlay_len = D_MODE_TX_OVERLAY_LEN;

        burst_profiles[D_MODE_BURST_NUM].ramp_profile = ramp_profiles[D_MODE_BURST_NUM];
        burst_profiles[D_MODE_BURST_NUM].ramp_profile[D_MODE_PROFILE1_NUM] = profile[D_MODE_PROFILE1_NUM];
        burst_profiles[D_MODE_BURST_NUM].ramp_profile[D_MODE_PROFILE1_NUM].dm[ADI_DM_MASTER].tx_pattern = 1; /* Tx0 */


        /* Now specify the ramp_config associated with the burst.
        * adi_dm_CalcRamp provides a reasonable set of default values
        * in its config output parameter.  Note config[0] and config[1] should
        * have the same values as only one can be used  for the burst.
        */
        p->bp[D_MODE_BURST_NUM].dma.ramp_config = config[D_MODE_PROFILE1_NUM];
        p->bp[D_MODE_BURST_NUM].dma.ramp_config.ramp_count = burst_profiles[D_MODE_BURST_NUM].num_ramps_in_seq * burst_profiles[D_MODE_BURST_NUM].num_seq_in_burst;

        /* Finally provide the firmware parameters.
        * ramp_bw_Mhz should be set to the maximum bandwidth of all the ramps.
        */
        // p->bp[0].rfpll.ramp_bw_Mhz = fmaxf(actual[0].ramp_bw_Mhz, actual[1].ramp_bw_Mhz);
        p->bp[D_MODE_BURST_NUM].rfpll.ramp_bw_Mhz = actual[D_MODE_PROFILE1_NUM].ramp_bw_Mhz;
        p->bp[D_MODE_BURST_NUM].rfpll.ramp_start_freq_hz = D_MODE_RAMP_START_FREQ_HZ;
    
        res = adi_dm_CalcPwrDetCfg(&burst_profiles[D_MODE_BURST_NUM], &p->bp[D_MODE_BURST_NUM].pwrdet);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_CalcPwrDetCfg", res, __FILE__, __LINE__);
        }

        memset(&calc_rfpll_period, 0, sizeof(calc_rfpll_period));
        calc_rfpll_period.burst_profile = &burst_profiles[D_MODE_BURST_NUM];
        calc_rfpll_period.ramp_start_freq_hz = p->bp[D_MODE_BURST_NUM].rfpll.ramp_start_freq_hz;
        res = adi_dm_CalcRfpllPeriod(&calc_rfpll_period, &p->bp[D_MODE_BURST_NUM].rfpllperiod);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_CalcRfpllPeriod", res, __FILE__, __LINE__);
        }

        // AFE Parameters
        p->bp[D_MODE_BURST_NUM].afe.rx_channels = 0;       // Zero means set for all Rx channels
        p->bp[D_MODE_BURST_NUM].afe.hpf_fc = HPF_FC;
        p->bp[D_MODE_BURST_NUM].afe.hpf_gain = HPF_GAIN;
        p->bp[D_MODE_BURST_NUM].afe.pga_gain = PGA_GAIN;
        p->bp[D_MODE_BURST_NUM].afe.adc_gain = ADC_GAIN;

        // Tx parameters, See exmaple_init.c second profile tx setup.
        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            p->bp[D_MODE_BURST_NUM].tx.dm[dm_num].tx_enable = 7;   /* enable all Tx */
            for (tx = 0; tx < ADI_DM_NUM_TX; tx++) {
                p->bp[D_MODE_BURST_NUM].tx.dm[dm_num].pa_gain_backoff_db[tx] = PA_GAIN_BACKOFF_DB;
            }
        }
    }
    /* To this point, make a function. */
    printf("D-Mode Profile structure is save!!\n");


    memset(&shape, 0, sizeof(shape));
    shape.slope0_time_us = L_MODE_RAMP_TIME_US;
    shape.slope1_time_us = 0;
    shape.delay0_time_us = 0;
    shape.delay1_time_us = 0;
    shape.delay2_time_us = L_MODE_RAMP_END_DELAY_US;
    shape.ramp_bw_Mhz = L_MODE_RAMP_BANDWIDTH_MHZ;
    shape.num_samples = L_MODE_NUM_SAMPLES_PER_RAMP;
    shape.sample_start_time_us = L_MODE_SAMPLES_START_TIME_US;     /* Place sample window in slope0 as far right as possible */
    shape.pga_shunt_en = true;
    shape.pga_shunt_start_del_us = 0;   /* Chose default value. */
    shape.pga_shunt_stop_del_us = 0;    /* Chose default value. */
    shape.filter_valid_delay = FILTER_VALID_DELAY;
    shape.decim_ratio = DECIMATION_FACTOR;
    shape.ref_freq_hz = REF_FREQ_HZ;
    res = adi_dm_CalcRamp(&shape, &profile[L_MODE_PROFILE1_NUM], &config[L_MODE_PROFILE1_NUM], &actual[L_MODE_PROFILE1_NUM]);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_CalcRamp", res, __FILE__, __LINE__);
    }

    {
        // L-MODE consists of one ramp profile.  =>> see tx_overlaysetting in example_init.c when tx_overlay length is greater than 0
        burst_profiles[L_MODE_BURST_NUM].num_ramps_in_seq = L_MODE_NUM_RAMPS_IN_SEQ;
        burst_profiles[L_MODE_BURST_NUM].num_seq_in_burst = L_MODE_NUM_SEQ_IN_BURST; //to satisfy all possible power down measurements in adi_dm_PowerDetectorMeasTask, set minimum burst size to be 228.
        burst_profiles[L_MODE_BURST_NUM].tx_overlay_len = L_MODE_TX_OVERLAY_LEN;

        burst_profiles[L_MODE_BURST_NUM].ramp_profile = ramp_profiles[L_MODE_BURST_NUM];
        burst_profiles[L_MODE_BURST_NUM].ramp_profile[L_MODE_PROFILE1_NUM] = profile[L_MODE_PROFILE1_NUM];

        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            burst_profiles[L_MODE_BURST_NUM].tx_overlay[dm_num] = tx_overlay[dm_num];
        }
        
        for (i = 0; i < burst_profiles[L_MODE_BURST_NUM].tx_overlay_len; i++) {
            int tx = i % ADI_DM_NUM_TX;
            adi_dm_num_t dm_num = (i / ADI_DM_NUM_TX) % adi_dm_active_digimmics;
            burst_profiles[L_MODE_BURST_NUM].tx_overlay[physical_mmic_num[dm_num]][i].tx_pattern = 1U << (2-tx);      // 2-tx is used for reverse TX sequence (0,1,2 -> 2,1,0)
        }
        /* Now specify the ramp_config associated with the burst.
        * adi_dm_CalcRamp provides a reasonable set of default values
        * in its config output parameter.  Note config[0] and config[1] should
        * have the same values as only one can be used  for the burst.
        */
        p->bp[L_MODE_BURST_NUM].dma.ramp_config = config[L_MODE_PROFILE1_NUM];
        p->bp[L_MODE_BURST_NUM].dma.ramp_config.ramp_count = burst_profiles[L_MODE_BURST_NUM].num_ramps_in_seq * burst_profiles[L_MODE_BURST_NUM].num_seq_in_burst;
        /* Finally provide the firmware parameters.
        * ramp_bw_Mhz should be set to the maximum bandwidth of all the ramps.
        */
        // p->bp[0].rfpll.ramp_bw_Mhz = fmaxf(actual[0].ramp_bw_Mhz, actual[1].ramp_bw_Mhz);
        p->bp[L_MODE_BURST_NUM].rfpll.ramp_bw_Mhz = actual[L_MODE_PROFILE1_NUM].ramp_bw_Mhz;
        p->bp[L_MODE_BURST_NUM].rfpll.ramp_start_freq_hz = L_MODE_RAMP_START_FREQ_HZ;
        
        res = adi_dm_CalcPwrDetCfg(&burst_profiles[L_MODE_BURST_NUM], &p->bp[L_MODE_BURST_NUM].pwrdet);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_CalcPwrDetCfg", res, __FILE__, __LINE__);
        }

        memset(&calc_rfpll_period, 0, sizeof(calc_rfpll_period));
        calc_rfpll_period.burst_profile = &burst_profiles[L_MODE_BURST_NUM];
        calc_rfpll_period.ramp_start_freq_hz = p->bp[L_MODE_BURST_NUM].rfpll.ramp_start_freq_hz;
        res = adi_dm_CalcRfpllPeriod(&calc_rfpll_period, &p->bp[L_MODE_BURST_NUM].rfpllperiod);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_CalcRfpllPeriod", res, __FILE__, __LINE__);
        }

        // AFE Parameters
        p->bp[L_MODE_BURST_NUM].afe.rx_channels = 0;       // Zero means set for all Rx channels
        p->bp[L_MODE_BURST_NUM].afe.hpf_fc = HPF_FC;
        p->bp[L_MODE_BURST_NUM].afe.hpf_gain = HPF_GAIN;
        p->bp[L_MODE_BURST_NUM].afe.pga_gain = PGA_GAIN;
        p->bp[L_MODE_BURST_NUM].afe.adc_gain = ADC_GAIN;

        // Tx parameters, See exmaple_init.c second profile tx setup.
        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            p->bp[L_MODE_BURST_NUM].tx.dm[dm_num].tx_enable = 7;   /* enable all Tx */
            for (tx = 0; tx < ADI_DM_NUM_TX; tx++) {
                p->bp[L_MODE_BURST_NUM].tx.dm[dm_num].pa_gain_backoff_db[tx] = PA_GAIN_BACKOFF_DB;
            }
        }
    }   

memset(&shape, 0, sizeof(shape));
    shape.slope0_time_us = M_MODE_RAMP_TIME_US;
    shape.slope1_time_us = 0;
    shape.delay0_time_us = 0;
    shape.delay1_time_us = 0;
    shape.delay2_time_us = M_MODE_RAMP_END_DELAY_US;
    shape.ramp_bw_Mhz = M_MODE_RAMP_BANDWIDTH_MHZ;
    shape.num_samples = M_MODE_NUM_SAMPLES_PER_RAMP;
    shape.sample_start_time_us = M_MODE_SAMPLES_START_TIME_US;     /* Place sample window in slope0 as far right as possible */
    shape.pga_shunt_en = true;
    shape.pga_shunt_start_del_us = 0;   /* Chose default value. */
    shape.pga_shunt_stop_del_us = 0;    /* Chose default value. */
    shape.filter_valid_delay = FILTER_VALID_DELAY;
    shape.decim_ratio = DECIMATION_FACTOR;
    shape.ref_freq_hz = REF_FREQ_HZ;
    res = adi_dm_CalcRamp(&shape, &profile[M_MODE_PROFILE1_NUM], &config[M_MODE_PROFILE1_NUM], &actual[M_MODE_PROFILE1_NUM]);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_CalcRamp", res, __FILE__, __LINE__);
    }
    {
        
        // M-MODE consists of one ramp profile.  =>> see tx_overlaysetting in example_init.c when tx_overlay length is greater than 0
        burst_profiles[M_MODE_BURST_NUM].num_ramps_in_seq = M_MODE_NUM_RAMPS_IN_SEQ;
        burst_profiles[M_MODE_BURST_NUM].num_seq_in_burst = M_MODE_NUM_SEQ_IN_BURST; //to satisfy all possible power down measurements in adi_dm_PowerDetectorMeasTask, set minimum burst size to be 228.
        burst_profiles[M_MODE_BURST_NUM].tx_overlay_len = M_MODE_TX_OVERLAY_LEN;

        burst_profiles[M_MODE_BURST_NUM].ramp_profile = ramp_profiles[M_MODE_BURST_NUM];
        burst_profiles[M_MODE_BURST_NUM].ramp_profile[M_MODE_PROFILE1_NUM] = profile[M_MODE_PROFILE1_NUM];

        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            burst_profiles[M_MODE_BURST_NUM].tx_overlay[dm_num] = tx_overlay[dm_num];
        }
        
        for (i = 0; i < burst_profiles[M_MODE_BURST_NUM].tx_overlay_len; i++) {
            int tx = i % ADI_DM_NUM_TX;
            adi_dm_num_t dm_num = (i / ADI_DM_NUM_TX) % adi_dm_active_digimmics;
            // uint32_t phase = (i * 8) % 128; /* 8 * 2.8125 = 22.5 */
            burst_profiles[M_MODE_BURST_NUM].tx_overlay[physical_mmic_num[dm_num]][i].tx_pattern = 1U << (2-tx);
            // if (tx == 0) {
            //     burst_profiles[L_MODE_BURST_NUM].tx_overlay[dm_num][i].pa0_phase = phase;
            // } else if (tx == 1) {
            //     burst_profiles[L_MODE_BURST_NUM].tx_overlay[dm_num][i].pa1_phase = phase;
            // } else {
            //     burst_profiles[L_MODE_BURST_NUM].tx_overlay[dm_num][i].pa2_phase = phase;
            // }
        }
        /* Now specify the ramp_config associated with the burst.
        * adi_dm_CalcRamp provides a reasonable set of default values
        * in its config output parameter.  Note config[0] and config[1] should
        * have the same values as only one can be used  for the burst.
        */
        p->bp[M_MODE_BURST_NUM].dma.ramp_config = config[M_MODE_PROFILE1_NUM];
        p->bp[M_MODE_BURST_NUM].dma.ramp_config.ramp_count = burst_profiles[M_MODE_BURST_NUM].num_ramps_in_seq * burst_profiles[M_MODE_BURST_NUM].num_seq_in_burst;
        /* Finally provide the firmware parameters.
        * ramp_bw_Mhz should be set to the maximum bandwidth of all the ramps.
        */
        // p->bp[0].rfpll.ramp_bw_Mhz = fmaxf(actual[0].ramp_bw_Mhz, actual[1].ramp_bw_Mhz);
        p->bp[M_MODE_BURST_NUM].rfpll.ramp_bw_Mhz = actual[M_MODE_PROFILE1_NUM].ramp_bw_Mhz;
        p->bp[M_MODE_BURST_NUM].rfpll.ramp_start_freq_hz = M_MODE_RAMP_START_FREQ_HZ;
        
        res = adi_dm_CalcPwrDetCfg(&burst_profiles[M_MODE_BURST_NUM], &p->bp[M_MODE_BURST_NUM].pwrdet);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_CalcPwrDetCfg", res, __FILE__, __LINE__);
        }

        memset(&calc_rfpll_period, 0, sizeof(calc_rfpll_period));
        calc_rfpll_period.burst_profile = &burst_profiles[M_MODE_BURST_NUM];
        calc_rfpll_period.ramp_start_freq_hz = p->bp[M_MODE_BURST_NUM].rfpll.ramp_start_freq_hz;
        res = adi_dm_CalcRfpllPeriod(&calc_rfpll_period, &p->bp[M_MODE_BURST_NUM].rfpllperiod);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_CalcRfpllPeriod", res, __FILE__, __LINE__);
        }

        // AFE Parameters
        p->bp[M_MODE_BURST_NUM].afe.rx_channels = 0;       // Zero means set for all Rx channels
        p->bp[M_MODE_BURST_NUM].afe.hpf_fc = HPF_FC;
        p->bp[M_MODE_BURST_NUM].afe.hpf_gain = HPF_GAIN;
        p->bp[M_MODE_BURST_NUM].afe.pga_gain = PGA_GAIN;
        p->bp[M_MODE_BURST_NUM].afe.adc_gain = ADC_GAIN;

        // Tx parameters, See exmaple_init.c second profile tx setup.
        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            p->bp[M_MODE_BURST_NUM].tx.dm[dm_num].tx_enable = 7;   /* enable all Tx */
            for (tx = 0; tx < ADI_DM_NUM_TX; tx++) {
                p->bp[M_MODE_BURST_NUM].tx.dm[dm_num].pa_gain_backoff_db[tx] = PA_GAIN_BACKOFF_DB;
            }
        }
    }
    memset(&shape, 0, sizeof(shape));
    shape.slope0_time_us = S_MODE_RAMP_TIME_US;
    shape.slope1_time_us = 0;
    shape.delay0_time_us = 0;
    shape.delay1_time_us = 0;
    shape.delay2_time_us = S_MODE_RAMP_END_DELAY_US;
    shape.ramp_bw_Mhz = S_MODE_RAMP_BANDWIDTH_MHZ;
    shape.num_samples = S_MODE_NUM_SAMPLES_PER_RAMP;
    shape.sample_start_time_us = S_MODE_SAMPLES_START_TIME_US;     /* Place sample window in slope0 as far right as possible */
    shape.pga_shunt_en = true;
    shape.pga_shunt_start_del_us = 0;   /* Chose default value. */
    shape.pga_shunt_stop_del_us = 0;    /* Chose default value. */
    shape.filter_valid_delay = FILTER_VALID_DELAY;
    shape.decim_ratio = DECIMATION_FACTOR;
    shape.ref_freq_hz = REF_FREQ_HZ;
    res = adi_dm_CalcRamp(&shape, &profile[S_MODE_PROFILE1_NUM], &config[S_MODE_PROFILE1_NUM], &actual[S_MODE_PROFILE1_NUM]);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_CalcRamp", res, __FILE__, __LINE__);
    }
    
    {
        
        // S-MODE consists of one ramp profile.  =>> see tx_overlaysetting in example_init.c when tx_overlay length is greater than 0
        burst_profiles[S_MODE_BURST_NUM].num_ramps_in_seq = S_MODE_NUM_RAMPS_IN_SEQ;
        burst_profiles[S_MODE_BURST_NUM].num_seq_in_burst = S_MODE_NUM_SEQ_IN_BURST; //to satisfy all possible power down measurements in adi_dm_PowerDetectorMeasTask, set minimum burst size to be 228.
        burst_profiles[S_MODE_BURST_NUM].tx_overlay_len = S_MODE_TX_OVERLAY_LEN;

        burst_profiles[S_MODE_BURST_NUM].ramp_profile = ramp_profiles[S_MODE_BURST_NUM];
        burst_profiles[S_MODE_BURST_NUM].ramp_profile[S_MODE_PROFILE1_NUM] = profile[S_MODE_PROFILE1_NUM];

        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            burst_profiles[S_MODE_BURST_NUM].tx_overlay[dm_num] = tx_overlay[dm_num];
        }
        
        for (i = 0; i < burst_profiles[S_MODE_BURST_NUM].tx_overlay_len; i++) {
            int tx = i % ADI_DM_NUM_TX;
            adi_dm_num_t dm_num = (i / ADI_DM_NUM_TX) % adi_dm_active_digimmics;
            // uint32_t phase = (i * 8) % 128; /* 8 * 2.8125 = 22.5 */
            burst_profiles[S_MODE_BURST_NUM].tx_overlay[physical_mmic_num[dm_num]][i].tx_pattern = 1U << (2-tx);
            // if (tx == 0) {
            //     burst_profiles[L_MODE_BURST_NUM].tx_overlay[dm_num][i].pa0_phase = phase;
            // } else if (tx == 1) {
            //     burst_profiles[L_MODE_BURST_NUM].tx_overlay[dm_num][i].pa1_phase = phase;
            // } else {
            //     burst_profiles[L_MODE_BURST_NUM].tx_overlay[dm_num][i].pa2_phase = phase;
            // }
        }
        /* Now specify the ramp_config associated with the burst.
        * adi_dm_CalcRamp provides a reasonable set of default values
        * in its config output parameter.  Note config[0] and config[1] should
        * have the same values as only one can be used  for the burst.
        */
        p->bp[S_MODE_BURST_NUM].dma.ramp_config = config[S_MODE_PROFILE1_NUM];
        p->bp[S_MODE_BURST_NUM].dma.ramp_config.ramp_count = burst_profiles[S_MODE_BURST_NUM].num_ramps_in_seq * burst_profiles[S_MODE_BURST_NUM].num_seq_in_burst;
        /* Finally provide the firmware parameters.
        * ramp_bw_Mhz should be set to the maximum bandwidth of all the ramps.
        */
        // p->bp[0].rfpll.ramp_bw_Mhz = fmaxf(actual[0].ramp_bw_Mhz, actual[1].ramp_bw_Mhz);
        p->bp[S_MODE_BURST_NUM].rfpll.ramp_bw_Mhz = actual[S_MODE_PROFILE1_NUM].ramp_bw_Mhz;
        p->bp[S_MODE_BURST_NUM].rfpll.ramp_start_freq_hz = S_MODE_RAMP_START_FREQ_HZ;
        
        res = adi_dm_CalcPwrDetCfg(&burst_profiles[S_MODE_BURST_NUM], &p->bp[S_MODE_BURST_NUM].pwrdet);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_CalcPwrDetCfg", res, __FILE__, __LINE__);
        }

        memset(&calc_rfpll_period, 0, sizeof(calc_rfpll_period));
        calc_rfpll_period.burst_profile = &burst_profiles[S_MODE_BURST_NUM];
        calc_rfpll_period.ramp_start_freq_hz = p->bp[S_MODE_BURST_NUM].rfpll.ramp_start_freq_hz;
        res = adi_dm_CalcRfpllPeriod(&calc_rfpll_period, &p->bp[S_MODE_BURST_NUM].rfpllperiod);
        if (res != ADI_DM_SUCCESS) {
            platform_error("adi_dm_CalcRfpllPeriod", res, __FILE__, __LINE__);
        }

        // AFE Parameters
        p->bp[S_MODE_BURST_NUM].afe.rx_channels = 0;       // Zero means set for all Rx channels
        p->bp[S_MODE_BURST_NUM].afe.hpf_fc = HPF_FC;
        p->bp[S_MODE_BURST_NUM].afe.hpf_gain = HPF_GAIN;
        p->bp[S_MODE_BURST_NUM].afe.pga_gain = PGA_GAIN;
        p->bp[S_MODE_BURST_NUM].afe.adc_gain = ADC_GAIN;

        // Tx parameters, See exmaple_init.c second profile tx setup.
        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            p->bp[S_MODE_BURST_NUM].tx.dm[dm_num].tx_enable = 7;   /* enable all Tx */
            for (tx = 0; tx < ADI_DM_NUM_TX; tx++) {
                p->bp[S_MODE_BURST_NUM].tx.dm[dm_num].pa_gain_backoff_db[tx] = PA_GAIN_BACKOFF_DB;
            }
        }
    }

    memcpy(p->burst_profiles, burst_profiles, sizeof(adi_dm_burst_profile_t)*4);

    /* The pattern of bursts to be generated by example_dma_ramp or example_tasklist. */
    /* There has to be at least 1 burst. */
    p->burst_pattern = "0123";
    p->pattern_repeat_count = 0;
    
    /* These are internal variables of example_burst_loop. */
    p->cur_bp_idx = p->burst_pattern[0] - '0';
    p->counter = 0;
    p->repeat_counter = 0;
    platform_profile_change(p->cur_bp_idx);
    

    /* These are a handy place to keep parameters for platform side */
    // data_plane_p.num_ramps = p->bp[0].dma.ramp_config.ramp_count;
    // data_plane_p.num_samples = shape.num_samples;
    // data_plane_p.num_channels = ADI_DM_NUM_RX * adi_dm_active_digimmics;


    /* Setup other parameters.
     * Included here because some of them relate to above parameters.
     */
    memset(&bts_afi910_init_p, 0, sizeof(bts_afi910_init_t));

    /* A number of firmware parameters are passed to adi_dm_PowerUp
     * including those describing the ramp discoved above. Set these
     * appropriately for the first burst.
     */
    bts_afi910_init_p.power_up.ramp_bw_Mhz = p->bp[p->cur_bp_idx].rfpll.ramp_bw_Mhz;
    bts_afi910_init_p.power_up.ramp_start_freq_hz = p->bp[p->cur_bp_idx].rfpll.ramp_start_freq_hz;

    /* Other firmware parameters are also set by adi_dm_PowerUp */
    bts_afi910_init_p.power_up.ref_freq_hz = REF_FREQ_HZ;          /* the same parameter passed to adi_dm_MipiSetup and adi_dm_CalcRamp */
    bts_afi910_init_p.power_up.rfpll_loop_bw_hz = RFPLL_LOOP_BW_HZ;

    /* Pointers to firmware held in application memory */
    //example_init_p.power_up.firmware_image = adar690x_ICCMRAM_bin;
    bts_afi910_init_p.power_up.firmware_image = (const uint32_t *)&adar690x_ICCMRAM_bin[0];
    bts_afi910_init_p.power_up.firmware_sz = adar690x_ICCMRAM_bin_len;
    //example_init_p.power_up.firmware_constants_image = adar690x_DCCMRAM_bin;
    bts_afi910_init_p.power_up.firmware_constants_image = (const uint32_t *)&adar690x_DCCMRAM_bin[0];
    bts_afi910_init_p.power_up.firmware_constants_sz = adar690x_DCCMRAM_bin_len;

    /* is_lo_right parameter to adi_dm describes board layout */ // reverted value????
#if ADI_DM_NUM_DIGIMMIC == 2
    bts_afi910_init_p_p.power_up.is_lo_right[ADI_DM_MASTER] = true;  /* Configure as per your board. */
    bts_afi910_init_p_p.power_up.is_lo_right[ADI_DM_SLAVE1] = false; /* Configure as per your board. */
#elif ADI_DM_NUM_DIGIMMIC == 4 
    bts_afi910_init_p.power_up.is_lo_right[ADI_DM_MASTER] = false; /* Configure as per your board. */
    bts_afi910_init_p.power_up.is_lo_right[ADI_DM_SLAVE1] = false; /* Configure as per your board. */
    bts_afi910_init_p.power_up.is_lo_right[ADI_DM_SLAVE2] = true;  /* Configure as per your board. */
    bts_afi910_init_p.power_up.is_lo_right[ADI_DM_SLAVE3] = true;  /* Configure as per your board. */
    
#endif
    /* timing_comp_setting parameter also describes board layout */
#if BIST == 1
    /* Describe how the GPIO7 and GPIO9 pins of each device are connected
     * for BIST56 ramp timing comparison.
     */
#if ADI_DM_NUM_DIGIMMIC == 2
    bts_afi910_init_p_p.power_up.timing_comp_setting[ADI_DM_MASTER] = ADI_DM_TIMING_COMP_GPIO7_ONLY; /* Configure as per your board. */
    bts_afi910_init_p_p.power_up.timing_comp_setting[ADI_DM_SLAVE1] = ADI_DM_TIMING_COMP_GPIO9_ONLY; /* Configure as per your board. */
#elif ADI_DM_NUM_DIGIMMIC == 4
    // bts_afi910_init_p.power_up.timing_comp_setting[ADI_DM_MASTER] = ADI_DM_TIMING_COMP_GPIO7_ONLY; /* Configure as per your board. */
    // bts_afi910_init_p.power_up.timing_comp_setting[ADI_DM_SLAVE1] = ADI_DM_TIMING_COMP_GPIO9_ONLY; /* Configure as per your board. */
    // bts_afi910_init_p.power_up.timing_comp_setting[ADI_DM_SLAVE2] = ADI_DM_TIMING_COMP_GPIO7_GPIO9;        /* Configure as per your board. */
    // bts_afi910_init_p.power_up.timing_comp_setting[ADI_DM_SLAVE3] = ADI_DM_TIMING_COMP_GPIO7_GPIO9;        /* Configure as per your board. */
    bts_afi910_init_p.power_up.timing_comp_setting[ADI_DM_MASTER] = ADI_DM_TIMING_COMP_DISABLED; //ADI_DM_TIMING_COMP_GPIO7_ONLY; /* Configure as per your board. */
    bts_afi910_init_p.power_up.timing_comp_setting[ADI_DM_SLAVE1] = ADI_DM_TIMING_COMP_DISABLED; //ADI_DM_TIMING_COMP_GPIO9_ONLY; /* Configure as per your board. */
    bts_afi910_init_p.power_up.timing_comp_setting[ADI_DM_SLAVE2] = ADI_DM_TIMING_COMP_DISABLED; //ADI_DM_TIMING_COMP_GPIO7_GPIO9;        /* Configure as per your board. */
    bts_afi910_init_p.power_up.timing_comp_setting[ADI_DM_SLAVE3] = ADI_DM_TIMING_COMP_DISABLED; //ADI_DM_TIMING_COMP_GPIO7_GPIO9;        /* Configure as per your board. */
#endif
#endif

    /* Dataport parameters */
#if LVDS_PART == 1
    bts_afi910_init_p.lvds.lvds_clk = LVDS_CLK;
    bts_afi910_init_p.lvds.filter_output_bitwidth = ADI_DM_OUTPUT_BITWIDTH_16;
    bts_afi910_init_p.lvds.dual_fs_mode = false;
    bts_afi910_init_p.lvds.fs_active_low = false;
    bts_afi910_init_p.lvds.streaming_mode_1 = false;
    bts_afi910_init_p.lvds.ls_byte_first = false;
    bts_afi910_init_p.lvds.ls_bit_first = false;
    bts_afi910_init_p.lvds.id_wc_en = false;       /* This adds additional 2 words (16 bits each) header + WC at start of every ramp data */
    bts_afi910_init_p.lvds.status_en = false;      /* This adds additional 2 words (16 bits each) of status data at end of every ramp data */
    bts_afi910_init_p.lvds.crc32_en = false;       /* This adds additional 2 words (16 bits each) CRC data at end of every ramp data after status if enabled */
#else
    bts_afi910_init_p.mipi.ref_freq_hz = REF_FREQ_HZ;      /* the same parameter passed to adi_dm_PowerUp and adi_dm_CalcRamp */
    bts_afi910_init_p.mipi.mipi_clk = MIPI_CLK;
    bts_afi910_init_p.mipi.num_lanes = ADI_DM_2_MIPI_LANES;
    bts_afi910_init_p.mipi.mipi_data_type = ADI_DM_RAW12;
    bts_afi910_init_p.mipi.filter_output_bitwidth = ADI_DM_OUTPUT_BITWIDTH_12;
    bts_afi910_init_p.mipi.continuous_clock = true;
    bts_afi910_init_p.mipi.ls_byte_first = true;
    bts_afi910_init_p.mipi.byte_interleaving = false;
    bts_afi910_init_p.mipi.status_en = false;      /* This adds additional 2 words (16 bits each) of status data at end of every ramp data */
    bts_afi910_init_p.mipi.crc32_en = false;       /* This adds additional 2 words (16 bits each) CRC data at end of every ramp data after status if enabled */
#endif

}