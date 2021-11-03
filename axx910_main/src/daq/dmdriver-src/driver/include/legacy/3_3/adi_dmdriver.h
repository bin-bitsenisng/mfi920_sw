/* adi_dmdriver_3_3.h
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

/** @file
 * Public C interface to the driver
 */

#ifndef ADI_DMDRIVER_3_3_H__
#define ADI_DMDRIVER_3_3_H__

#include <legacy/3_3_3/adi_dmdriver.h>

/**
 * Ramp Configuration.
 * Data type with the common parameters to adi_dm_BuiltinMimoSetup() and adi_dm_DmaRampSetup()
 * which are mainly written to fields of RFPLL_RAMP_CONFIG registers.
 */
typedef struct {
    unsigned ramp_count:12;         /**< Number of ramps in burst. */

    unsigned pga_shunt_en:1;        /**< Enable PGA Shunt signal to power off PGA during slope1*/
    uint8_t pga_shunt_start_del;    /**< Time in ref clocks before slope1 to power off PGA */
    uint8_t pga_shunt_stop_del;     /**< Time in ref clocks after slope1 to power on PGA */

    unsigned filter_decim_ratio:9;  /**< Decimation Ratio. */
    unsigned filter_valid_delay:9;  /**< Number of samples to suppress at start of ramp. */
    struct {
        unsigned vga_sync_data_valid:1;     /**< Synchronize VGA gain activation with data valid signal */
        unsigned vga_on_patt:6;             /**< Bitset with parts of ramp where VGAs are enabled */
        unsigned pa_off_time:5;             /**< Time between PAs Activated and Deactivated, in REF_CLK cycles */

        unsigned vga_gauss_dis:1;           /**< Disable VGA Gain Gaussian Shape */
        unsigned vga_gain_steps:3;          /**< Number of steps in VGA gain shape is 2^vga_gain_steps. */
        unsigned vga_gain_step_div:6;       /**< Time of each step in VGA gain shape, in REF_CLK cycles */

        unsigned phase_mod_en:1;            /**< Enable phase modulation during ramp generation */
        unsigned phase_delay_en:1;          /**< Start phase modulation with data_valid */

        uint8_t ramp_status_0;              /**< Control STAT0 signal. See "Ramp Status Pins" subsection of @cite hrm. */
        uint8_t ramp_status_1;              /**< Control STAT1 signal. See "Ramp Status Pins" subsection of @cite hrm. */
        uint8_t ramp_status_2;              /**< Control STAT2 signal. See "Ramp Status Pins" subsection of @cite hrm. */
    } dm[ADI_DM_NUM_DIGIMMIC];
} adi_dm_3_3_ramp_config_t;

/**
 * Calculate ramp profile from high level parameters.
 *
 * Deprecated because this function writes to the ramp_status_x bitfields within
 * RAMP_CONFIG8 which the FW needs to configure for BIST56.
 *
 * @param[in] in Required timings and other parameters for the ramp.
 * @param[out] ramp_profile Ramp profile shape fields are filled in, other fields are zeroed.
 * @param[out] ramp_config Ramp config shape fields are filled in, other fields are zeroed.
 * @param[out] actual Actual values for timings etc. corresponding to the generated values.
 * @return ADI_DM_SUCCESS for success, an error code for errors
 *
 * @see adi_dm_BuiltinMimoSetup
 * @see adi_dm_BurstProfileSetup
 */
adi_dm_err_t adi_dm_3_3_CalcRamp(const adi_dm_ramp_shape_t * in, adi_dm_ramp_profile_t * ramp_profile, adi_dm_3_3_ramp_config_t * ramp_config, adi_dm_actual_ramp_shape_t * actual);

/**
 * @em IN parameter to adi_dm_BuiltinMimoSetup()
 *
 * Register values for ramp generation using built-in MIMO mode.
 * See "Built-in MIMO Mode" subsection of @cite hrm.
 *
 * @see adi_dm_BuiltinMimoSetup
 */
typedef struct {
    adi_dm_3_3_ramp_config_t ramp_config;       /**< Burst invariant ramp configuration. */
    adi_dm_ramp_profile_t ramp_profile;     /**< Ramp parameters. */
    unsigned mimo_seq_len:2;                /**< Length of MIMO sequences. See "Built-in MIMO Mode" subsection of @cite hrm */
    struct {
        unsigned mimo_seq_val:12;           /**< Tx and phase pattern for each device. See "Built-in MIMO Mode" subsection of @cite hrm */
    } dm[ADI_DM_NUM_DIGIMMIC];
} adi_dm_3_3_builtin_mimo_setup_t;

/**
 * Register writes for ramp generation using built-in MIMO mode.
 *
 * Deprecated because this function writes to the ramp_status_x bitfields within
 * RAMP_CONFIG8 which the FW needs to configure for BIST56.
 *
 * @param[in] p parameters. See ::adi_dm_builtin_mimo_setup_t.
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_3_3_BuiltinMimoSetup(const adi_dm_3_3_builtin_mimo_setup_t * p);

/**
 * @em IN parameter to adi_dm_DmaRampSetup()
 *
 * Register writes for ramp generation using DMA,
 * including writing ramp_config registers and initialization of DMA controller.
 * See "DMA Interfacing" subsection of @cite hrm.
 *
 * @see adi_dm_DmaRampSetup
 */
typedef struct {
    adi_dm_3_3_ramp_config_t ramp_config;   /**< Burst invariant ramp configuration. */
    uint32_t bpid;                      /**< Select first profile to use, from adi_dm_BurstProfileSetup(). */
} adi_dm_3_3_dma_ramp_setup_t;

/**
 * Register writes for ramp generation using DMA.
 *
 * Deprecated because this function writes to the ramp_status_x bitfields within
 * RAMP_CONFIG8 which the FW needs to configure for BIST56.
 *
 * @param[in] p parameters. See ::adi_dm_dma_ramp_setup_t.
 * @return ADI_DM_SUCCESS for success, an error code for errors.
 */
adi_dm_err_t adi_dm_3_3_DmaRampSetup(const adi_dm_3_3_dma_ramp_setup_t * p);

/* Including this header links to legacy functions.
 */
#ifndef ADI_DM_NO_LEGACY_REDEF


#define adi_dm_ramp_config_t adi_dm_3_3_ramp_config_t
#define adi_dm_builtin_mimo_setup_t adi_dm_3_3_builtin_mimo_setup_t
#define adi_dm_BuiltinMimoSetup adi_dm_3_3_BuiltinMimoSetup
#define adi_dm_dma_ramp_setup_t adi_dm_3_3_dma_ramp_setup_t
#define adi_dm_DmaRampSetup adi_dm_3_3_DmaRampSetup

#endif


#endif                          /* ADI_DMDRIVER_3_3_H__ */
