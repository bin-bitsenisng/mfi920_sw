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

#ifndef BTS_APPLICATION_H
#define BTS_APPLICATION_H

#include "adi_dmdriver.h"
#include "platform.h"           /* Platform specific defines.
								 * Must at least contain declarations for
								 * adar690x_ICCMRAM_bin, adar690x_DCCMRAM_bin,
								 * adar690x_ICCMRAM_bin_len and adar690x_DCCMRAM_bin_len.
								 */

#define HARDWARE_TRIGGER 1
#define BIST 0                  /* enable bist checks. See example_burst_loop.c */
#define TASKLIST 0              /* use the example tasklist instead of PeriodicCalibrations */

#define SPI_OPTIMIZED 0

#define KHZ(x) ((x) * 1000)
#define MHZ(x) ((x) * 1000000)
#define GHZ(x) ((x) * 1000000000ULL)

								 // RFPLL setup -- Do NOT Change. If you want to change these values, ask to a platform engineer.
#define REF_FREQ_HZ MHZ(80)
#define RFPLL_LOOP_BW_HZ KHZ(500)

// ADC setup -- Do NOT Change. If you want to change these values, ask to a platform engineer.
#define DECIMATION_FACTOR 24            // 24 for 53.333MHz
#define FILTER_VALID_DELAY 92           // Number of discarded samples in front of a ramp

/* Device
 * Master (3rd IC in schematic) : 0
 * Slave1 (1st IC in schematic) : 1
 * Slave2 (2nd IC in schematic) : 2
 * Slave3 (4th IC in schematic) : 3
 * ADC Sample Freq : 53.333MHz
 */

enum busrt_name_num {
	D_MODE_BURST_NUM = 0,
	L_MODE_BURST_NUM,
	M_MODE_BURST_NUM,
	S_MODE_BURST_NUM,
	TOTAL_BURST_NUM
};

// enum profile_name_num{
//     D_MODE_PROFILE1_NUM = 0,
//     L_MODE_PROFILE1_NUM,
//     M_MODE_PROFILE1_NUM,
//     S_MODE_PROFILE1_NUM,
//     TOTAL_PROFILE_NUM
// };
#define D_MODE_PROFILE1_NUM 0
#define L_MODE_PROFILE1_NUM 0
#define M_MODE_PROFILE1_NUM 0
#define S_MODE_PROFILE1_NUM 0
#define TOTAL_NUM_RX 16
#define NUM_RX_PER_CHIP 4
// enum profile_num{
//     NUM_PROFILE1 = 0,
//     NUM_PROFILE2,
//     NUM_PROFILE3, // ....
//     MAX_NUM_PROFILES
// };
#define ADD_MARGIN_TIME 2.0f
#define NUM_BURST_PROFILES TOTAL_BURST_NUM
// D-MODE burst profile setup
#define D_MODE_NUM_PROFILES 1
#define D_MODE_NUM_RAMPS_IN_SEQ 1
#define D_MODE_NUM_SEQ_IN_BURST 512
#define D_MODE_NUM_RAMPS (D_MODE_NUM_RAMPS_IN_SEQ*D_MODE_NUM_SEQ_IN_BURST)
#define D_MODE_ON_TX_DEVICE 0           // 0 : Master
#define D_MODE_ON_TX_NUM 0
#define D_MODE_TX_OVERLAY_LEN 0

#define D_MODE_RAMP_START_FREQ_HZ GHZ(78.9303)
#define D_MODE_RAMP_BANDWIDTH_MHZ 139.5f
#define D_MODE_RAMP_TIME_US 11.4f + ADD_MARGIN_TIME
#define D_MODE_RAMP_END_DELAY_US 5.0f-ADD_MARGIN_TIME
#define D_MODE_NUM_SAMPLES_PER_RAMP 512
#define D_MODE_SAMPLES_START_TIME_US 3.5f
#define D_MODE_TOTAL_NUM_SAMPLE (D_MODE_NUM_RAMPS*D_MODE_NUM_SAMPLES_PER_RAMP)

// L-MODE burst profile setup
#define L_MODE_NUM_PROFILES 1
#define L_MODE_NUM_RAMPS_IN_SEQ 1
#define L_MODE_NUM_SEQ_IN_BURST 32*12
#define L_MODE_NUM_RAMPS (L_MODE_NUM_RAMPS_IN_SEQ*L_MODE_NUM_SEQ_IN_BURST)
#define L_MODE_TX_OVERLAY_LEN 12

#define L_MODE_RAMP_START_FREQ_HZ GHZ(78.84)
#define L_MODE_RAMP_BANDWIDTH_MHZ 311.0f
#define L_MODE_RAMP_TIME_US 21.9f + ADD_MARGIN_TIME
#define L_MODE_RAMP_END_DELAY_US 5.0f-ADD_MARGIN_TIME
#define L_MODE_NUM_SAMPLES_PER_RAMP 1024
#define L_MODE_SAMPLES_START_TIME_US 3.5f
#define L_MODE_TOTAL_NUM_SAMPLE (L_MODE_NUM_RAMPS*L_MODE_NUM_SAMPLES_PER_RAMP)

// M-MODE burst profile setup
#define M_MODE_NUM_PROFILES 1
#define M_MODE_NUM_RAMPS_IN_SEQ 1
#define M_MODE_NUM_SEQ_IN_BURST 32*12
#define M_MODE_NUM_RAMPS (M_MODE_NUM_RAMPS_IN_SEQ*M_MODE_NUM_SEQ_IN_BURST)
#define M_MODE_TX_OVERLAY_LEN 12

//#define M_MODE_RAMP_START_FREQ_HZ GHZ(78.533495)
//#define M_MODE_RAMP_BANDWIDTH_MHZ 933.01f
#define M_MODE_RAMP_START_FREQ_HZ GHZ(78.45)
#define M_MODE_RAMP_BANDWIDTH_MHZ 1094.7f

#define M_MODE_RAMP_TIME_US 21.9f + ADD_MARGIN_TIME
#define M_MODE_RAMP_END_DELAY_US 5.0f-ADD_MARGIN_TIME
#define M_MODE_NUM_SAMPLES_PER_RAMP 1024
#define M_MODE_SAMPLES_START_TIME_US 3.5f
#define M_MODE_TOTAL_NUM_SAMPLE (M_MODE_NUM_RAMPS*M_MODE_NUM_SAMPLES_PER_RAMP)

// S-MODE burst profile setup
#define S_MODE_NUM_PROFILES 1
#define S_MODE_NUM_RAMPS_IN_SEQ 1
#define S_MODE_NUM_SEQ_IN_BURST 32*12
#define S_MODE_NUM_RAMPS (S_MODE_NUM_RAMPS_IN_SEQ*S_MODE_NUM_SEQ_IN_BURST)
#define S_MODE_TX_OVERLAY_LEN 12

#define S_MODE_RAMP_START_FREQ_HZ GHZ(78.067)
#define S_MODE_RAMP_BANDWIDTH_MHZ 1866.0f
#define S_MODE_RAMP_TIME_US 21.9f + ADD_MARGIN_TIME
#define S_MODE_RAMP_END_DELAY_US 5.0f-ADD_MARGIN_TIME
#define S_MODE_NUM_SAMPLES_PER_RAMP 1024
#define S_MODE_SAMPLES_START_TIME_US 3.5f
#define S_MODE_TOTAL_NUM_SAMPLE (S_MODE_NUM_RAMPS*S_MODE_NUM_SAMPLES_PER_RAMP)

// Get max values
#define MAX_NUM_RAMPS_IN_SEQ 12
#define MAX_TX_OVERLAY_LEN 12

#define SCAN_TIME_US 1000000

#define OFFTIME_US 4000
#define OFFTIME_SLEEP_US 2000

#define HPF_FC ADI_DM_HPF_FC_1_MHZ
#define HPF_GAIN ADI_DM_HPF_GAIN_12_DB
#define PGA_GAIN ADI_DM_PGA_GAIN_0_DB
#define ADC_GAIN ADI_DM_ADC_GAIN_3_DB
#define PA_GAIN_BACKOFF_DB 0

#if LVDS_PART == 1
#define LVDS_CLK ADI_DM_ADCCLK_DIV_1_5
#else
#define MIPI_CLK ADI_DM_MIPI_CLK_1200MHZ
#endif

#define MANUAL_SLEEP 0
#define AUTO_SLEEP 0
#define TIMEOUT_NS 2000000000UL

#define DECIMATION_FILTER_ENABLE 0

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
	adi_dm_burst_profile_t burst_profiles[TOTAL_BURST_NUM];
} bts_afi910_config_t;



/* parameters to platform_data_plane_init */
typedef struct {
	uint32_t num_ramps;
	uint32_t num_samples;
	uint32_t num_channels;
} platform_data_plane_init_t;

/* These functions are part of the example. */
void example_syscal(void);
void example_dma_ramp(void);
void *bts_afi910_modulation(void *);
void *bts_afi910_get_data(void *);
void example_tasklist(void);
// void example_init(example_config_t * p);
void bts_afi910_init(bts_afi910_config_t * p);
void bts_afi910_switch_config(bts_afi910_config_t * p, uint32_t next_bp_idx);
void bts_afi910_switch_config_spioptimize(bts_afi910_config_t * p, uint32_t next_bp_idx);
void bts_afi910_burst_loop(bts_afi910_config_t * p);
// void example_switch_config(example_config_t * p, uint32_t next_bp_idx);
// void example_burst_loop(example_config_t * p);

/* These functions are used for loop control in exampl_burst_loop and example_tasklist */
bool bts_afi910_burst_loop_should_exit(bts_afi910_config_t * p);
int  bts_afi190_get_next_burst_profile(bts_afi910_config_t * p);
// bool burst_loop_should_exit(example_config_t * p);
// int get_next_burst_profile(example_config_t * p);

adi_dm_err_t bts_afi910_rfic_dma_setup(const adi_dm_burst_profile_t * p, uint32_t * dma_mem_limit, uint32_t * bpid);
adi_dm_err_t bts_afi910_DmaRampSetup(const adi_dm_dma_ramp_setup_t * p);
adi_dm_err_t bts_afi910_ramp_config(const adi_dm_ramp_config_t * p, const adi_dm_builtin_mimo_setup_t * builtin_mimo);
adi_dm_err_t adi_dm_BurstProfileSetup(const adi_dm_burst_profile_t * p, uint32_t * dma_mem_limit, uint32_t * bpid);
/* some functions modified from dm-driver is declared here */


/* These functions contain platform specific code in addition to the HAL. */
void platform_init(void);
void platform_data_plane_init(platform_data_plane_init_t * p);
void platform_error(const char *, adi_dm_err_t, const char *, unsigned);
void platform_prep_host_for_trigger(void);
void platform_start_timer(uint32_t wait_time_us);
void platform_wait_for_timer(void);
void platform_hw_trigger(void);
void platform_mipi_init(void);
void platform_mipi_cap_start(void);
void platform_mipi_capture(int curr_mode);
void platform_mipi_cap_stop(void);
void platform_profile_change(int profile_num);
int  platform_mipi_vc_id_change(int profile_num);
void platform_reshape_data(void);
void platform_gpu_reshape_data(void);
void platform_save_data(int frame_cnt);//, int reshape_mode);
void platform_print_data(void);
void platform_buff_change(void);
adi_dm_err_t platform_fault_check(void);

void test_rfic_udma(bts_afi910_config_t * p);
void bts_rfic_udma_reload(void);
void bts_rfic_udma_mode_change(void);
void bts_rfic_read_mipi_reg(int chan);
void bts_rfic_read_rfpll_reg(int chan);
void bts_rfic_read_ramp_gen_reg(int chan);
void bts_rfic_read_misc_reg(int chan);
void bts_rfic_read_fw_cfg_reg(int chan);
void bts_rfic_read_udma_reg(int chan);
void bts_rfic_read_mipicsi2_reg(int chan);
void bts_rfic_read_afe_reg(int chan);
adi_dm_err_t bts_dm_DmaRampSetup(const adi_dm_dma_ramp_setup_t * p);
adi_dm_err_t bts_dm_DmaRampSetup_optimize(const adi_dm_dma_ramp_setup_t * p);

void *cam_init_check(void *);
#endif                          /*BTS_APPLICATION_H */