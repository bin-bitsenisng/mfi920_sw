/* adi_dmdriver_3_0.h
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

/*
 * Header file to provide compatibility with 3.0 driver API
 */

#ifndef ADI_DMDRIVER_3_0_H__
#define ADI_DMDRIVER_3_0_H__

#include <legacy/3_2/adi_dmdriver.h>
#include <legacy/3_3/adi_dmdriver.h>

/**
 * Max channels supported by driver.
 * Only single DigiMMIC supported.
 */
typedef enum {
    ADI_DM_3_0_MAX_RX = 4 * ADI_DM_NUM_DIGIMMIC,  /**< Number of Rx channels */
    ADI_DM_3_0_MAX_TX = 3 * ADI_DM_NUM_DIGIMMIC   /**< Number of Tx channels */
} adi_dm_3_0_channel_limits_t;

/**
 * @name MIMO value
 * These definitions support the bitfields in the "value" part of MIMO sequences.
 * A MIMO sequence is from 0 to 3 elements, each specifying the antennas to Tx on and
 * an optional 180 degree phase shift.
 *
 * @note
 * This feature is only supported in single-DigiMMIC configurations.
 * Because of this,
 * there is no need to present a "one giant DigiMMIC" view by widening bitfields.
 * We are left with essentially the layout of the bitfield in the hardware register.
 *
 * <em>Example snippet</em>:
 * @snippet example_ramp.c Setting up MIMO
 */
typedef enum {
    BITP_MIMO_SEQ_VAL_PATTERN0 = 0,     /**< Bit position of active antennas during sequence step 0 */
    BITM_MIMO_SEQ_VAL_PATTERN0 = 0x7,           /**< Bit mask of active antennas during sequence step 0 */
    BITP_NARROW_MIMO_SEQ_VAL_PHASE0 = 3,       /**< Bit position of phase during sequence step 0 */
    BITM_MIMO_SEQ_VAL_PHASE0 = 0x8,     /**< Bit mask of phase during sequence step 0 */
    BITP_MIMO_SEQ_VAL_PATTERN1 = 4,     /**< Bit position of active antennas during sequence step 1 */
    BITM_MIMO_SEQ_VAL_PATTERN1 = 0x70,          /**< Bit mask of active antennas during sequence step 1 */
    BITP_MIMO_SEQ_VAL_PHASE1 = 7,       /**< Bit position of phase during sequence step 1 */
    BITM_MIMO_SEQ_VAL_PHASE1 = 0x80,            /**< Bit mask of phase during sequence step 1 */
    BITP_MIMO_SEQ_VAL_PATTERN2 = 8,     /**< Bit position of active antennas during sequence step 2 */
    BITM_MIMO_SEQ_VAL_PATTERN2 = 0x700,         /**< Bit mask of active antennas during sequence step 2 */
    BITP_MIMO_SEQ_VAL_PHASE2 = 11,      /**< Bit position of phase during sequence step 2 */
    BITM_MIMO_SEQ_VAL_PHASE2 = 0x800,           /**< Bit mask of phase during sequence step 2 */
} adi_dm_3_0_mimo_seq_val_t;

/**
 * Global ramp configuration values destined to be written
 * to rfpll.rfpll_ramp_config registers and passed as
 * firmware parameters.
 *
 * The structure is embedded in @c adi_dm_ramp_profile_t
 * so there may be many copies in the data structure
 * describing a burst. Typically all copies should have
 * the same values, although @c adi_dm_ConfigRfpllForBurstProfile
 * and @c adi_dm_RampSetupMulti will chose the largest ramp_bw.
 * 
 * For backward compatibility, in this version of the driver the
 * data structure is based upon the B3 silicon parameters
 * and some fields are ignored.
 */
typedef struct {
    float ramp_bw;      /**< Difference between start and ending frequency in Hz */
    uint32_t mimo_seq_val;      /**< Sequence of up to 3 states (each transmitter on/off & phase). @see adi_dm_mimo_seq_val_t and "Built-in MIMO Mode" subsection of @cite hrm */
    uint32_t mimo_seq_len;      /**< Length of MIMO sequence. See "Built-in MIMO Mode" subsection of @cite hrm. "0" disables MIMO, in which case @c tx_pattern is used instead. */
    float ramp_time_us; /**< Minimum overall ramp time. Ignored in C1 driver. */
    bool fast_ramp_mode;        /**< Are slope1_time_us, and all delays, == 0? Ignored in C1 driver. */
    bool pga_shunt_en;   /**< Enable PGA Shunt signal to power off PGA during slope1*/
    uint8_t pga_shunt_start_del;  /**< Time in ref clocks before slope1 to power off PGA */
    uint8_t pga_shunt_stop_del;  /**< Time in ref clocks after slope1 to power on PGA */
} adi_dm_3_0_rfpll_detail_t;

/**
 * Ramp Profile.
 * This is a representation in C of the RAMPGEN register block.
 *
 * For backward compatibility, in this version of the driver the
 * data structure is based upon the B3 silicon RAMPGEN registers
 * and some fields which are no longer in C1 RAMPGEN are copied
 * into their new locations in the C1 register file. These fields
 * must have the same values on all cascaded digiMMICs for the
 * entire burst.
 */
typedef struct {
    unsigned del0_steps:22;        /**< Delay before starting the first slope of the ramp */
    uint32_t slp0_steps;        /**< Number of steps for the first slope of the ramp */
    unsigned del1_steps:20;        /**< Delay between the two slopes of the ramp */

    unsigned vga_gain:6;        /**< Setting for the variable gain amplifier. Copied to all tx_vga.vga_gain by C1 driver. */
    unsigned pa_pwr_con:7;      /**< Power amplifier power control. Copied to all tx_config.pa_pwr_con by C1 driver. */

    uint32_t slp1_steps;        /**< Number of steps for the second slope of the ramp */
    unsigned del2_steps:22;        /**< Delay before starting the next ramp */
    int32_t slp0_dev;  /**< How much to change frequency by at each step of the first slope */
    int32_t slp1_dev;  /**< How much to change frequency by at each step of the second slope */

    unsigned tx_pattern:6;      /**< Bottom 3 bits are bitmask of Tx antennas to switch on; top 3 bits ignored in C1 driver. See "Transmit Output Power and Phase Control" subsection of @cite hrm . Ignored in MIMO mode. */
    unsigned pa_on_patt:6;      /**< Indicate at which stages of the ramp profile the PAs are active. C1 driver copies this value to vga_on_patt. See "Transmit Output Power and Phase Control" subsection of @cite hrm. */
    unsigned dma_on_patt:6;     /**< Indicate when the DMA can program the next ramp profile. Field ignored in C1 driver. */

    unsigned ramp_stat_bit_0:1; /**< STAT0 pin that can be used to retrieve the status of the ramp during operation. See "Ramp Status Pins" subsection of @cite hrm. */
    unsigned ramp_stat_bit_1:1; /**< STAT1 pin that can be used to retrieve the status of the ramp during operation. See "Ramp Status Pins" subsection of @cite hrm. */
    unsigned ramp_stat_bit_2:1; /**< STAT2 pin that can be used to retrieve the status of the ramp during operation. See "Ramp Status Pins" subsection of @cite hrm. */

    uint16_t afe_start_off_time;     /**< Time for which the ADC is off after the start of the ramp, in AFE_CLK cycles */
    unsigned num_samples:13;    /**< Number of ADC samples to take per ramp */
    uint16_t afe_on_time;       /**< Time for which the ADC is on during a ramp, in AFE_CLK cycles */
    uint16_t afe_ramp_time;     /**< Total ramp time, in AFE_CLK cycles */

    unsigned pa0_phase:7;       /**< Starting phase offset for Tx0 */
    unsigned pa1_phase:7;       /**< Starting phase offset for Tx1 */
    unsigned pa2_phase:7;       /**< Starting phase offset for Tx2 */

    unsigned pa0_phase_dev:7;   /**< How much to increment Tx0 phase by per step */
    unsigned pa1_phase_dev:7;   /**< How much to increment Tx1 phase by per step */
    unsigned pa2_phase_dev:7;   /**< How much to increment Tx2 phase by per step */

    unsigned phase_step:5;      /**< How many ADC clock cycles between phase increments */

    float del0_actual_time_us;                  /**< Actual delay0 time as calculated in microseconds */
    float del1_actual_time_us;                  /**< Actual delay1 time as calculated in microseconds */
    float del2_actual_time_us;                  /**< Actual delay2 time as calculated in microseconds */
    float slp0_actual_time_us;                  /**< Actual slope0 time as calculated in microseconds */
    float slp1_actual_time_us;                  /**< Actual slope1 time as calculated in microseconds */

    float afe_start_off_time_us;        /**< Actual afe start time as calculated in microseconds */
    float afe_on_time_us;               /**< Actual afe on time as calculated in microseconds */
    float afe_ramp_time_us;             /**< Actual afe ramp time as calculated in microseconds */
    float afe_clk_rate_Mhz;             /**< Actual afe clk rate time as calculated in Mhz */
    float filter_valid_delay_time_us;   /**< Actual time of filter_valid_delay in microseconds */

    adi_dm_3_0_rfpll_detail_t rfpll_detail; /**< High-level representation of ramp */
} adi_dm_3_0_ramp_profile_t;

/**
 * System Profile.
 * This is a representation of the RAMPGEN register blocks for all DigiMMIC chips in the system.
 */
typedef struct {
    adi_dm_3_0_ramp_profile_t ramp[ADI_DM_NUM_DIGIMMIC]; /**< Array of detailed ramp profiles, one for each DigiMMIC in the system */
} adi_dm_3_0_sys_profile_t;

/**
 * @em IN parameter to @c adi_dm_PowerUp
 *
 * @note
 * You can default to a version of the ARC firmware that was tested for
 * compatibility with this version of the driver by passing
 * NULL for @c firmware_*image and 0 for @c firmware_*_sz .
 *
 * @see adi_dm_PowerUp
 */
typedef struct {
    bool spi_crc_disable;       /**< Use CRC on SPI */
    bool power_part_only;       /**< Power up the part but do not initialize it */

    uint8_t *firmware_image;    /**< Firmware code image in host memory. */
    size_t firmware_sz; /**< Size of firmware code image. */
    uint8_t *firmware_constants_image;    /**< Firmware constants image in host memory. */
    size_t firmware_constants_sz; /**< Size of firmware constants. */
    uint32_t dccm_addr;         /**< Address on DigiMMIC to download @c firmware_constants_image to, or 0 for default. Only effective for firmware prior to 1.8.0. */

    uint32_t ref_freq_hz;       /**< Reference clock */
    uint32_t rfpll_lbw_hz;      /**< RF PLL Loop Bandwidth */

    double ramp_start_freq_ghz;  /**< Desired ramp start frequency (GHz) */
    float ramp_bw_mhz;     /**< Maximum difference between start and ending frequency across all ramps */

    uint32_t decim_factor;      /**< Decimation factor */

    bool is_lvds_part;          /**< "true" for LVDS, "false" for MIPI */

    bool is_cascaded;   /**< Is this a cascaded DigiMMIC system? */
    bool is_slave;      /**< Is this DigiMMIC a slave? *NB*: in the cascaded case where one DigiMMIC is the master and the others slaves, you should pass in @c false here. */
    bool is_lo_right[ADI_DM_NUM_DIGIMMIC];   /**< Is LO right? */
} adi_dm_3_0_power_up_t;

/**
 * Power up device.
 *
 * @param[in] p parameters
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_3_0_PowerUp(adi_dm_3_0_power_up_t * p);

/**
 * @em IN parameter to @c adi_dm_DataportSetupLVDS
 *
 * @see adi_dm_DataportSetupLVDS
 */
typedef struct {
    uint32_t num_samples;       /**< Number of samples to Rx */
    double clk_div;     /**< Select ADCCLK/clk_div as LVDS clock. Valid values are {6, 1.5, 2, 3, 4, 8}. */
    bool ls_bit_first;  /**< "true" if the least-significant bit is first */
    bool ls_byte_first; /**< "true" if the least-significant byte is first */
    uint32_t streaming_mode;    /**< Streaming mode. Must be 1 or 2. */
    bool id_wc_en;      /**< Enable data ID and word count field during data transmission */
    bool status_en;     /**< Enable status data field during data transmission */
    bool crc_en;        /**< Enable CRC field during data transmission */
    bool dual_fs_mode;  /**< Selects dual framing mode */
    uint32_t lane0_id;  /**< Data ID value for data provided by Rx channel 0 */
    uint32_t lane1_id;  /**< Data ID value for data provided by Rx channel 1 */
    uint32_t lane2_id;  /**< Data ID value for data provided by Rx channel 2 */
    uint32_t lane3_id;  /**< Data ID value for data provided by Rx channel 3 */
} adi_dm_3_0_dataport_setup_lvds_t;

/**
 * Dataport configuration for LVDS parts.
 *
 * @param[in] p parameters
 * @return ADI_DM_SUCCESS for success, an error code for errors
 *
 * <em>Example snippet</em>:
 * @snippet example_init.c Setup LVDS
 */
adi_dm_err_t adi_dm_3_0_DataportSetupLVDS(adi_dm_3_0_dataport_setup_lvds_t * p);

/**
 * @em IN parameter to @c adi_dm_DataportSetupMIPI
 *
 * @see adi_dm_DataportSetupMIPI
 */
typedef struct {
    uint32_t num_samples;       /**< Number of samples to Rx */
    uint32_t mipi_freq_hz;      /**< MIPI clock frequency. Must be between `MHZ(80)` & `MHZ(1200)`. */
    uint32_t lane_en_num;       /**< Number of DPHY data lanes */
    bool ls_byte_first; /**< Least-significant byte is first */
    bool sample_byte_interleaving;      /**< "true" for byte interleaving; "false" for sample interleaving */
    adi_dm_mipi_data_type_t mipi_data_type;     /**< Packet 1 data type */
    bool status_en;     /**< Is status field of packet 1 enabled? */
    bool crc_en;        /**< Is CRC32 field for packet 1 enabled? */
    uint32_t ref_freq_hz;  /**< Reference clock frequency. Must be between `MHZ(40)` & `MHZ(80)` */
} adi_dm_3_0_dataport_setup_mipi_t;

/**
 * Dataport configuration for MIPI parts.
 *
 * @param[in] p parameters
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_3_0_DataportSetupMIPI(adi_dm_3_0_dataport_setup_mipi_t * p);

/**
 * @em IN parameter to @c adi_dm_CalcRamp
 *
 * @see adi_dm_CalcRamp
 */
typedef struct {
    float slope0_time_us;    /**< Time for first slope of ramp */
    float slope1_time_us;    /**< Time for second slope of ramp */
    float delay0_time_us;          /**< Time for delay0, before slope 0 of ramp */
    float delay1_time_us;          /**< Time for delay1, between slope 0 and slope 1 of ramp */
    float delay2_time_us;          /**< Time for delay2, after slope 1 of ramp */
    float sample_start_time_us;    /**< Time to start sampling measured from start of delay0. When this is 0 afe_init_del is calculted by placing the sample window as far right in slope0 as possible. */
    bool pga_shunt_en;                  /**< pga shunt enable if it is set to true, otherwise enable */
    float pga_shunt_start_del_us;          /**< pga shunt start delay in micro sec */
    float pga_shunt_stop_del_us;     /**< pga shunt stop delay in micro sec */
    float ramp_bw_mhz;     /**< Difference between start and ending frequency */
    uint32_t mimo_seq_val;      /**< Sequence of up to 3 states (each transmitter on/off & phase). @see adi_dm_mimo_seq_val_t and "Built-in MIMO Mode" subsection of @cite hrm */
    uint32_t mimo_seq_len;      /**< Length of MIMO sequence. See "Built-in MIMO Mode" subsection of  of @cite hrm. "0" disables MIMO. */
    uint32_t num_samples; /**< Number of samples per ramp */
    uint32_t tx_select;    /**<
                            * Bitmap of Tx antennas to enable.
                            * In particular, this is a concatenation of @c ADI_DM_NUM_DIGIMMIC 6-bit fields.
                            * In each 6-bit field, the bottom 3 bits control whether an antenna is enabled,
                            * and the top 3 bits are ignored in the C1 driver.
                            * Only used when <tt>mimo_seq_len == 0</tt>.
                            */
    uint32_t pa_phase[3 * ADI_DM_NUM_DIGIMMIC]; /**< Starting phase offset for Tx antennas */
    uint32_t pa_phase_dev[3 * ADI_DM_NUM_DIGIMMIC];     /**< Phase deviation for Tx antennas */
    uint32_t pa_phase_step[ADI_DM_NUM_DIGIMMIC];     /**< Phase modulator step common for all antennas */
    uint32_t vga_gain;  /**< Setting of Tx variable gain amplifier */
    uint32_t pa_power;  /**< Setting of Tx power amplifier. Valid values are 127 for full and 101 for half. */
    uint32_t decim_factor;      /**< Decimation factor. This is only used for calculations. It is not stored to a register. It must be the same value that was passed to @ref adi_dm_PowerUp. */
    uint32_t ref_freq_hz;          /**< Reference frequency */
    double adcpll_freq_hz;   /**< Actual ADCPLL frequency */
} adi_dm_3_0_calc_ramp_t;

/**
 * Calculate ramp profile from high level parameters.
 * Although this function is hardware-independent,
 * it is part of the driver library so it can be called by user code.
 * It is also strictly optional as the hardware-level parameters can just be passed from user code to
 * @c adi_dm_RampSetupSimple and @c adi_dm_RampSetupMulti .
 * This is by design.
 *
 * @note
 * Because of hardware limitations, the ramp profile may not @em exactly match what was requested.
 * In particular, the "Ramp Generator - AFE Timing" subsection of @cite hrm states that
 * > "the duration of each ramp must be an integer multiple of the CLK and AFE_CLK periods."
 *
 * @param[in] in high-level ramp parameters
 * @param[out] out array of detailed ramp profiles, one for each DigiMMIC in the system, suitable for input to @c adi_dm_RampSetupSimple or @c adi_dm_RampSetupMulti. This memory must be allocated by the caller.
 * @return ADI_DM_SUCCESS for success, an error code for errors
 *
 * <em>Example snippet</em>:
 * @snippet example_ramp.c Calculate ramp profile
 *
 * @see adi_dm_RampSetupSimple
 * @see adi_dm_RampSetupMulti
 */
adi_dm_err_t adi_dm_3_0_CalcRamp(adi_dm_3_0_calc_ramp_t * in, adi_dm_3_0_sys_profile_t * out);

/**
 * @em IN parameter to @c adi_dm_RampSetupSimple
 *
 * @see adi_dm_RampSetupSimple
 */
typedef struct {
    adi_dm_3_0_sys_profile_t sys; /**< The ramp profiles for each DigiMMIC */
    uint32_t ramp_count;        /**< Number of times ramp is transmitted for burst. See "Built-in MIMO Mode" and "DMA Interfacing" subsections of @cite hrm for details. */

    float ramp_start_freq_ghz; /**< Start frequency */

    uint32_t ref_freq_hz;  /**< Reference clock frequency */
} adi_dm_3_0_ramp_setup_simple_t;

/**
 * Configure Rampgen, Tx and RFPLL for burst with single ramp profile.
 *
 * When using this function to load Rampgen, the @c simple_ramp parameter should be set true for #adi_dm_TriggerBurst and #adi_dm_TriggerMutiburst.
 *
 * @param[in] p ramp profile
 * @return ADI_DM_SUCCESS for success, an error code for errors
 *
 * <em>Example snippet</em>:
 * @snippet example_ramp.c Setup simple ramp
 */
adi_dm_err_t adi_dm_3_0_RampSetupSimple(adi_dm_3_0_ramp_setup_simple_t * p);

/**
 * @em IN parameter to @c adi_dm_RampSetupMulti
 *
 * @see adi_dm_RampSetupMulti
 */
typedef struct {
    uint32_t num_ramps_in_seq;        /**< Number of ramp profiles in array */
    adi_dm_3_0_sys_profile_t *sys; /**< Sequence of system profiles for Tx */
    uint32_t num_seq_in_burst;      /**< Number of times sequence in @c ramp is transmitted for one burst */

    float ramp_start_freq_ghz; /**< Start frequency */

    uint32_t ref_freq_hz;  /**< Reference clock frequency */
} adi_dm_3_0_ramp_setup_multi_t;

/**
 * Configure Rampgen, Tx and RFPLL for burst with a repeating sequence of ramp profiles.
 * This is a more friendly interface to the DMA hardware.
 *
 * @param[in] p ramp profiles. *NB*: `p->num_seq_in_burst` must be >= 1.
 * @return ADI_DM_SUCCESS for success, an error code for errors
 *
 * <em>Example snippet</em>:
 * @snippet example_ramp.c Configure DMA
 */
adi_dm_err_t adi_dm_3_0_RampSetupMulti(adi_dm_3_0_ramp_setup_multi_t * p);

/**
 * A 'burst profile' is a sequence of ramp profiles and a repeat count,
 * with associated DMA descriptors. When adi_dm_TriggerBurst or adi_dm_TriggerMultiburst
 * the current burst profile is loaded to the RAMPGEN by DMA during the burst.
 */
typedef struct {
    uint32_t num_ramps_in_seq;        /**< Number of ramp profiles in array */
    adi_dm_3_0_sys_profile_t *sys; /**< Sequence of system profiles for Tx */
    uint32_t num_seq_in_burst;      /**< Number of times sequence in @c ramp is transmitted for one burst */
} adi_dm_3_0_burst_profile_t;

/**
 * Store new 'burst profile' describing the burst to be triggered by @c adi_dm_ramp_reconfig_multi.
 * This is added to those already in memory, and becomes the new current burst profile.
 *
 * @param[in] p Parameter from which to derive the burst profile.
 * @param[out] bpid Identifier denoting this burst profile in memory to pass to adi_dm_SetCurrentBurstProfile.
 * @return ADI_DM_SUCCESS for success, an ADI_DM_PARAMETER_ERROR if insufficient memory
 */
adi_dm_err_t adi_dm_3_0_StoreBurstProfile(adi_dm_3_0_burst_profile_t * p, uint32_t * bpid);

/**
 * Get the identifier for current burst profile.
 *
 * @param[out] bpid Identifier denoting the current burst profile in memory.
 * @return ADI_DM_SUCCESS for success, an ADI_DM_PARAMMETER_ERROR if no burst profile configured
 */
adi_dm_err_t adi_dm_3_0_GetCurrentBurstProfileId(uint32_t * bpid);

/**
 * Set the current burst profile
 *
 * @param[in] bpid Identifier denoting the desired burst profile in memory.
 * @return ADI_DM_SUCCESS for success, and ADI_DM_PARAMMETER_ERROR if bpid invalid
 */
adi_dm_err_t adi_dm_3_0_SetCurrentBurstProfile(uint32_t bpid);

/**
 * Configure RFPLL for a particular burst profile.
 *
 * This functon may need to be called each time the current burst profile is changed
 * either by adi_dm_StoreBurstProfile or adi_dm_SetCurrentBurstProfile. However it need
 * not be called if the resultant RFPLL configuration will be the same.
 *
 * The following parameters determine whether the RFPLL configuration will be the same.
 * -  p->num_ramps_in_seq * p->num_seq_in_burst
 * -  min(p->sys[...].[ADI_DM_MASTER].rfpll_detail.pa_on_patt)
 * -  max(p->sys[...].[ADI_DM_MASTER].rfpll_detail.ramp_bw)
 * -  and(p->sys[...].[ADI_DM_MASTER].rfpll_detail.pga_shunt_en)
 * -  min(p->sys[...].[ADI_DM_MASTER].rfpll_detail.pga_shunt_start_del) if pga_shunt_en
 * -  min(p->sys[...].[ADI_DM_MASTER].rfpll_detail.pga_shunt_stop_del) if pga_shunt_en)
 * -  ramp_start_freq_ghz
 * -  ref_freq_hz
 *
 * If the set of burst profles used are crafted such that none of these parameters
 * change then this function only needs to be called once.
 *
 * @param[in] p The burst profile from which to derive the configuration.
 * @param[in] ref_freq_hz Reference clock (Hz).
 * @param[in] ramp_start_freq_ghz Desired ramp start frequency (GHz).
 * @return ADI_DM_SUCCESS for success, and an error code on failure
 */
adi_dm_err_t adi_dm_3_0_ConfigRfpllForBurstProfile(adi_dm_3_0_burst_profile_t * p, uint32_t ref_freq_hz, float ramp_start_freq_ghz);

/**
 * Change RFPLL frequency.
 *
 * @param[in] ramp_start_freq_ghz Frequency to lock RFPLL to
 * @param[in] ramp_bw_mhz Ramp bandwidth. Note that this is signed, when slope0 is falling (i.e. V-shaped ramps) it should be negative.
 * @return ADI_DM_SUCCESS for success, and an error code on failure
 */
adi_dm_err_t adi_dm_3_0_SetRfpllFreq(float ramp_start_freq_ghz, float ramp_bw_mhz);

/**
 * @em IN parameter to @c adi_dm_TriggerBurst
 *
 * @see adi_dm_TriggerBurst
 */
typedef struct {
    void (*prep_host_for_trigger) (void);       /**< Function pointer that will be called to reset host between bursts, e.g. to re-initialize DMA */
    bool simple_ramp;       /** Rampgen registers loaded by #adi_dm_RampSetupSimple, otherwise start DMA to load.  */
    bool calibrate_only;    /** Only run calibrations in preparation for a burst but do not trigger. Useful when using external trigger. */
    bool no_lochain_cal;    /** Do not run LOCHAIN_CAL calibration between bursts. */
} adi_dm_3_0_trigger_burst_t;

/**
 * Trigger a single burst. Return immediately.
 *
 * @param[in] p parameters
 * @return ADI_DM_SUCCESS for success, an error code for errors
 *
 * <em>Example snippet</em>:
 * @snippet example_ramp.c Trigger ramps
 */
adi_dm_err_t adi_dm_3_0_TriggerBurst(adi_dm_3_0_trigger_burst_t * p);

/**
 * @em IN parameter to @c adi_dm_TriggerMultiburst
 *
 * @see adi_dm_TriggerMultiburst
 * @see adi_dm_TriggerBurst
 */
typedef struct {
    uint32_t offtime_us;        /**< Idle time between each burst */
    uint32_t offtime_sleep_us;  /**< Initial part of the Idle time during which the DigiMMIC is to sleep  */
    bool run_till_counter_expires;      /**< Operate in mode where we call @c adi_dm_TriggerBurst @c count times */
    uint32_t count;     /**< Number of iterations for *run_till_counter_expires* mode */
     bool(*halt_requested) (void);      /**< Function pointer called to query whether Tx loop should stop. This can be used for an early exit. */
    void (*prep_host_for_trigger) (void);       /**< Function pointer called to reset host between bursts, e.g. to re-initialize DMA */
    bool simple_ramp;   /** Rampgen registers loaded by #adi_dm_RampSetupSimple, otherwise start DMA to load. */
    bool no_lochain_cal;    /** Do not run LOCHAIN_CAL calibration between bursts. */
    bool manual_sleep;  /**< Use explicit firmware commands rather than automatic to sleep part during offtime. */
} adi_dm_3_0_trigger_multiburst_t;

/**
 * Trigger a repeated sequence of bursts.
 *
 * @note
 * This feature is orthogonal to whether or not DMA is used to vary the
 * ramp profile within each burst.
 *
 * @param[in] p parameters
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_3_0_TriggerMultiburst(adi_dm_3_0_trigger_multiburst_t * p);

/**
 * Enumeration listing ramp profile fields. @see adi_dm_3_0_ModifyRampProfile
 */
typedef enum {
    adi_dm_3_0_del0_steps,
    adi_dm_3_0_slp0_steps,
    adi_dm_3_0_del1_steps,
    adi_dm_3_0_vga_gain,
    adi_dm_3_0_pa_pwr_con,
    adi_dm_3_0_slp1_steps,
    adi_dm_3_0_del2_steps,
    adi_dm_3_0_slp0_dev,
    adi_dm_3_0_slp1_dev,
    adi_dm_3_0_tx_pattern,
    adi_dm_3_0_pa_on_patt,
    adi_dm_3_0_dma_on_patt,
    adi_dm_3_0_ramp_stat_bit_0,
    adi_dm_3_0_ramp_stat_bit_1,
    adi_dm_3_0_ramp_stat_bit_2,
    adi_dm_3_0_afe_start_off_time,
    adi_dm_3_0_num_samples,
    adi_dm_3_0_afe_on_time,
    adi_dm_3_0_afe_ramp_time,
    adi_dm_3_0_pa0_phase,
    adi_dm_3_0_pa1_phase,
    adi_dm_3_0_pa2_phase,
    adi_dm_3_0_pa0_phase_dev,
    adi_dm_3_0_pa1_phase_dev,
    adi_dm_3_0_pa2_phase_dev,
    adi_dm_3_0_phase_step
} adi_dm_3_0_ramp_profile_field_t;

/**
 * Modify a ramp profile set up by adi_dm_RampSetupMulti
 * 
 * Deprecated because it is unsafe to modify individual parameters in isolation.
 * In particular changing ramp bandwidth requires rerunning RFPLL configuration.
 * See adi_dm_RfpllReconfig().
 *
 * @param[in] dm_num DigiMMIC number to write to, starting at 0. If @c dm_num is 255, a write is broadcast to all DigiMMICs.
 * @param[in] bpid Id of burst profile to update in list of profiles passed to adi_dm_RampSetupMulti or adi_dm_NewBurstProfile, or 0 for first burst.
 * @param[in] rampidx Index of ramp profile to update in list of profiles passed to adi_dm_RampSetupMulti.
 * @param[in] field Field of the profile to update.
 * @param[in] new_value New value to be written to the DigiMMIC.
 * @return ADI_DM_SUCCESS for success, and an error code on failure
 */
adi_dm_err_t adi_dm_3_0_ModifyRampProfile(adi_dm_num_t dm_num, uint32_t bpid, uint32_t rampidx, adi_dm_3_0_ramp_profile_field_t field, uint32_t new_value);

/**
 * Read actual ADCLL frequency from firmware status table.
 * Requires adi_dm_PowerUp to have downloded and initialized firmware.
 *
 * Deprecated because adi_dm_CalcRamp() now calculates this value in
 * order to run offline. Consequently the driver does not use this value.
 * The routine just depends upon public interfaces so can be incorporated
 * into the application if necessary.
 * 
 * @return value read from the firmware status table.
 */
double adi_dm_3_0_ReadAdcpllFreqHz(void);

/*
 * These declarations previously appeared in adi_dmdriver.h.
 * Currently the definitions are in the library but they need to be removed
 * as the files provide an alternative source for the firmware.
 */
extern const unsigned char adar690x_ICCMRAM_bin[], adar690x_DCCMRAM_bin[];
extern const unsigned int adar690x_ICCMRAM_bin_len, adar690x_DCCMRAM_bin_len;

/* Defines to including this header links to legacy functions.
 */
#ifndef ADI_DM_NO_LEGACY_REDEF

#define ADI_DM_MAX_RX ADI_DM_3_0_MAX_RX
#define ADI_DM_MAX_TX ADI_DM_3_0_MAX_TX
#define adi_dm_channel_limits_t adi_dm_3_0_channel_limits_t
#define adi_dm_mimo_seq_val_t adi_dm_3_0_mimo_seq_val_t
#define adi_dm_rfpll_detail_t adi_dm_3_0_rfpll_detail_t
#define adi_dm_ramp_profile_t adi_dm_3_0_ramp_profile_t
#define adi_dm_sys_profile_t adi_dm_3_0_sys_profile_t
#define adi_dm_power_up_t adi_dm_3_0_power_up_t
#define adi_dm_PowerUp adi_dm_3_0_PowerUp
#define adi_dm_dataport_setup_lvds_t adi_dm_3_0_dataport_setup_lvds_t
#define adi_dm_DataportSetupLVDS adi_dm_3_0_DataportSetupLVDS
#define adi_dm_dataport_setup_mipi_t adi_dm_3_0_dataport_setup_mipi_t
#define adi_dm_DataportSetupMIPI adi_dm_3_0_DataportSetupMIPI
#define adi_dm_calc_ramp_t adi_dm_3_0_calc_ramp_t
#define adi_dm_CalcRamp adi_dm_3_0_CalcRamp
#define adi_dm_ramp_setup_simple_t adi_dm_3_0_ramp_setup_simple_t
#define adi_dm_RampSetupSimple adi_dm_3_0_RampSetupSimple
#define adi_dm_ramp_setup_multi_t adi_dm_3_0_ramp_setup_multi_t
#define adi_dm_RampSetupMulti adi_dm_3_0_RampSetupMulti
#define adi_dm_burst_profile_t adi_dm_3_0_burst_profile_t
#define adi_dm_StoreBurstProfile adi_dm_3_0_StoreBurstProfile
#define adi_dm_GetCurrentBurstProfileId adi_dm_3_0_GetCurrentBurstProfileId
#define adi_dm_SetCurrentBurstProfile adi_dm_3_0_SetCurrentBurstProfile
#define adi_dm_ConfigRfpllForBurstProfile adi_dm_3_0_ConfigRfpllForBurstProfile
#define adi_dm_SetRfpllFreq adi_dm_3_0_SetRfpllFreq
#define adi_dm_trigger_burst_t adi_dm_3_0_trigger_burst_t
#define adi_dm_TriggerBurst adi_dm_3_0_TriggerBurst
#define adi_dm_trigger_multiburst_t adi_dm_3_0_trigger_multiburst_t
#define adi_dm_TriggerMultiburst adi_dm_3_0_TriggerMultiburst
#define adi_dm_del0_steps adi_dm_3_0_del0_steps
#define adi_dm_slp0_steps adi_dm_3_0_slp0_steps
#define adi_dm_del1_steps adi_dm_3_0_del1_steps
#define adi_dm_vga_gain adi_dm_3_0_vga_gain
#define adi_dm_pa_pwr_con adi_dm_3_0_pa_pwr_con
#define adi_dm_slp1_steps adi_dm_3_0_slp1_steps
#define adi_dm_del2_steps adi_dm_3_0_del2_steps
#define adi_dm_slp0_dev adi_dm_3_0_slp0_dev
#define adi_dm_slp1_dev adi_dm_3_0_slp1_dev
#define adi_dm_tx_pattern adi_dm_3_0_tx_pattern
#define adi_dm_pa_on_patt adi_dm_3_0_pa_on_patt
#define adi_dm_dma_on_patt adi_dm_3_0_dma_on_patt
#define adi_dm_ramp_stat_bit_0 adi_dm_3_0_ramp_stat_bit_0
#define adi_dm_ramp_stat_bit_1 adi_dm_3_0_ramp_stat_bit_1
#define adi_dm_ramp_stat_bit_2 adi_dm_3_0_ramp_stat_bit_2
#define adi_dm_afe_start_off_time adi_dm_3_0_afe_start_off_time
#define adi_dm_num_samples adi_dm_3_0_num_samples
#define adi_dm_afe_on_time adi_dm_3_0_afe_on_time
#define adi_dm_afe_ramp_time adi_dm_3_0_afe_ramp_time
#define adi_dm_pa0_phase adi_dm_3_0_pa0_phase
#define adi_dm_pa1_phase adi_dm_3_0_pa1_phase
#define adi_dm_pa2_phase adi_dm_3_0_pa2_phase
#define adi_dm_pa0_phase_dev adi_dm_3_0_pa0_phase_dev
#define adi_dm_pa1_phase_dev adi_dm_3_0_pa1_phase_dev
#define adi_dm_pa2_phase_dev adi_dm_3_0_pa2_phase_dev
#define adi_dm_phase_step adi_dm_3_0_phase_step
#define adi_dm_ramp_profile_field_t adi_dm_3_0_ramp_profile_field_t
#define adi_dm_ModifyRampProfile adi_dm_3_0_ModifyRampProfile
#define adi_dm_ReadAdcpllFreqHz adi_dm_3_0_ReadAdcpllFreqHz

#endif

#endif                          /* ADI_DMDRIVER_3_0_H__ */
