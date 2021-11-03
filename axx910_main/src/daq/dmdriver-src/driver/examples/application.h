/* application.h
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

#ifndef APPLICATION_H
#define APPLICATION_H

#include "adi_dmdriver.h"
#include "platform.h"           /* Platform specific defines.
                                 * Must at least contain declarations for
                                 * adar690x_ICCMRAM_bin, adar690x_DCCMRAM_bin,
                                 * adar690x_ICCMRAM_bin_len and adar690x_DCCMRAM_bin_len.
                                 */

#define BIST 0                  /* enable bist checks. See example_burst_loop.c */
#define TASKLIST 0              /* use the example tasklist instead of PeriodicCalibrations */

#define KHZ(x) ((x) * 1000)
#define MHZ(x) ((x) * 1000000)
#define GHZ(x) ((x) * 1000000000ULL)

#define REF_FREQ_HZ MHZ(80)
#define RFPLL_LOOP_BW_HZ KHZ(500)
#define DECIMATION_FACTOR 24
#define FILTER_VALID_DELAY 92

#define NUM_BURST_PROFILES 2
#define NUM_RAMPS_IN_SEQ 2
#define NUM_SEQ_IN_BURST 128
#define TX_OVERLAY_LEN 16
#define NUM_RAMPS (NUM_RAMPS_IN_SEQ*NUM_SEQ_IN_BURST)

#define RAMP_START_FREQ_HZ_1 GHZ(77.5)
#define RAMP_BANDWIDTH_MHZ_1 3000.0f
#define RAMP_START_FREQ_HZ_2 GHZ(77)
#define RAMP_BANDWIDTH_MHZ_2 750.0f
#define RAMP_TIME_US 30.0f
#define NUM_SAMPLES_PER_RAMP 1024

#define OFFTIME_US 4000
#define OFFTIME_SLEEP_US 2000

#define HPF_FC ADI_DM_HPF_FC_125_KHZ
#define HPF_GAIN ADI_DM_HPF_GAIN_6_DB
#define PGA_GAIN ADI_DM_PGA_GAIN_0_DB
#define ADC_GAIN ADI_DM_ADC_GAIN_0_DB
#define PA_GAIN_BACKOFF_DB 0

#if LVDS_PART == 1
#define LVDS_CLK ADI_DM_ADCCLK_DIV_1_5
#else
#define MIPI_CLK ADI_DM_MIPI_CLK_1200MHZ
#endif

#define MANUAL_SLEEP 0
#define AUTO_SLEEP 0
#define TIMEOUT_NS 2000000000UL

/* configuration and global data used in all examples */
typedef struct {
    uint32_t cycle_time_us;
    uint32_t offtime_sleep_us;
    uint8_t syscalrx[ADI_DM_NUM_DIGIMMIC][ADI_DM_SYSCAL_RX_SIZE];
    uint32_t device_mem_handle;
    int num_burst_profiles;
    struct {
        /* settings for a particular use case */
        adi_dm_dma_ramp_setup_t dma;
        adi_dm_rfpll_reconfig_t rfpll;
        adi_dm_afe_setup_t afe;
        adi_dm_tx_setup_t tx;
        /* fw parameters for bist related to use case */
        adi_dm_power_detector_meas_task_t pwrdet;
        adi_dm_write_rfpll_period_t rfpllperiod;
        uint8_t syscaltx[ADI_DM_NUM_DIGIMMIC][ADI_DM_SYSCAL_TX_SIZE];
    } bp[NUM_BURST_PROFILES];
    char *burst_pattern;        /* used in loop burst_loop control */
    int pattern_repeat_count;   /* used in loop burst_loop control */
    int cur_bp_idx;
    int counter;
    int repeat_counter;
} example_config_t;

/* parameters to platform_data_plane_init */
typedef struct {
    uint32_t num_ramps;
    uint32_t num_samples;
    uint32_t num_channels;
} platform_data_plane_init_t;

/* These functions are part of the example. */
void example_syscal(void);
void example_dma_ramp(void);
void example_tasklist(void);
void example_init(example_config_t * p);
void example_switch_config(example_config_t * p, uint32_t next_bp_idx);
void example_burst_loop(example_config_t * p);

/* These functions are used for loop control in exampl_burst_loop and example_tasklist */
bool burst_loop_should_exit(example_config_t * p);
int get_next_burst_profile(example_config_t * p);

/* These functions contain platform specific code in addition to the HAL. */
void platform_init(void);
void platform_data_plane_init(platform_data_plane_init_t * p);
void platform_error(const char *, adi_dm_err_t, const char *, unsigned);
void platform_prep_host_for_trigger(void);
void platform_start_timer(uint32_t wait_time_us);
void platform_wait_for_timer(void);

#endif                          /*APPLICATION_H */
