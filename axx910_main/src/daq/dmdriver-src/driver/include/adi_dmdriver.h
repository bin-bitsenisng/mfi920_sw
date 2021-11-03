/* adi_dmdriver.h
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

#ifndef __ADI_DMDRIVER_H__
#define __ADI_DMDRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#ifdef _MSC_VER
#define inline __inline
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/** Possible error codes */
// typedef enum {
//     ADI_DM_SUCCESS = 0, /**< ok */
//     ADI_DM_FAIL = -1,           /**< Generic failure code */
//     ADI_DM_TIMEDOUT = -2,       /**< Operation took too long */
//     ADI_DM_PARAMETER_ERROR = -3,        /**< Parameter validation failed */
//     ADI_DM_FIRMWARE_ERROR = -4, /**< Firmware signalled an error condition */
//     ADI_DM_SPI_SCRATCHPAD_ERROR = -5,  /**< A test write to SPI failed on power up. Often indicates DigiMMIC is not powered. */
//     ADI_DM_MISC_SCRATCHPAD_ERROR = -6,  /**< A test write to the register file failed on power up. */
//     ADI_DM_SPI_CRC_ERROR = -7,  /**< SPI read failed CRC check. */
//     ADI_DM_SPI_COUNTER_ERROR = -8,  /**< SPI frame counter mismatch. */
//     ADI_DM_CASCADED_TX_PWR_CHK_ERROR = -9,  /**< BIST19 failure comparing between cascaded devices */
// } adi_dm_err_t;
#define ADI_DM_SUCCESS 0 /**< ok */
#define ADI_DM_FAIL -1           /**< Generic failure code */
#define ADI_DM_TIMEDOUT -2       /**< Operation took too long */
#define ADI_DM_PARAMETER_ERROR -3        /**< Parameter validation failed */
#define ADI_DM_FIRMWARE_ERROR -4 /**< Firmware signalled an error condition */
#define ADI_DM_SPI_SCRATCHPAD_ERROR -5  /**< A test write to SPI failed on power up. Often indicates DigiMMIC is not powered. */
#define ADI_DM_MISC_SCRATCHPAD_ERROR -6  /**< A test write to the register file failed on power up. */
#define ADI_DM_SPI_CRC_ERROR -7  /**< SPI read failed CRC check. */
#define ADI_DM_SPI_COUNTER_ERROR -8  /**< SPI frame counter mismatch. */
#define ADI_DM_CASCADED_TX_PWR_CHK_ERROR -9  /**< BIST19 failure comparing between cascaded devices */
typedef int adi_dm_err_t;

/** Names for GPIO pins */
typedef enum {
    ADI_DM_RESETB,
    ADI_DM_GPIO0,
    ADI_DM_GPIO1,
    ADI_DM_FAULT0B,
    ADI_DM_FAULT1,
    ADI_DM_TRIG,
    ADI_DM_PWDNB,
    ADI_DM_GPIO6,
    ADI_DM_GPIO7,
    ADI_DM_GPIO8,
    ADI_DM_GPIO9,
    ADI_DM_GPIO10,
    ADI_DM_GPIO11,
    ADI_DM_NUM_GPIO
} adi_dm_gpio_t;

#include "adi_dmhal.h"

/** @name Driver initialization
 */
/**@{*/

/** Initialize driver and host side, do not touch device */
void adi_dm_InitDriver(void);

/** Release any resources used by driver */
void adi_dm_FiniDriver(void);

/** Return a string denoting driver release or "unreleased" */
const char *adi_dm_DriverVersion(void);

/**}*/

/**
 * @name Low-level
 * This is the low-level API.
 * All functions take a @c dm_num parameter specifying which DigiMMIC to use.
 * Valid values for this is the contiguous range from ADI_DM_MASTER (0) to (ADI_DM_NUM_DIGIMMIC - 1) inclusive.
 */
/**@{*/

// typedef enum {
//     ADI_DM_MASTER = 0,  /**< DigiMMIC number for the master DigiMMIC in a cascade */
//     ADI_DM_SLAVE1 = 1,  /**< First slave in a cascade */
//     ADI_DM_SLAVE2 = 2,  /**< Second slave in a cascade */
//     ADI_DM_SLAVE3 = 3,  /**< Third slave in a cascade */
//     ADI_DM_ALL_DIGIMMICS = 0xFF /**< Pseudo-DigiMMIC number to address @em all DigiMMICs, master and slaves, in a cascade */
// } adi_dm_num_t;
#define ADI_DM_MASTER 0  /**< DigiMMIC number for the master DigiMMIC in a cascade */
#define ADI_DM_SLAVE1 1  /**< First slave in a cascade */
#define ADI_DM_SLAVE2 2  /**< Second slave in a cascade */
#define ADI_DM_SLAVE3 3  /**< Third slave in a cascade */
#define ADI_DM_ALL_DIGIMMICS 0xFF /**< Pseudo-DigiMMIC number to address @em all DigiMMICs, master and slaves, in a cascade */
typedef int adi_dm_num_t;

/**
 * Number of devices actively controlled by the driver.
 *
 * Must be a number between 1 and ADI_DM_NUM_DIGIMMIC inclusive.
 * Must be set before calling  #adi_dm_InitDriver.
 */
extern adi_dm_num_t adi_dm_active_digimmics;

/**
 * Write a word to the DigiMMIC address space, checking for CRC error.
 *
 * Access to SPI registers is supported by special rules for addresses in the
 * range 0 to 255. If the address is in the range 0 to 255 the low 8-bits of
 * value are written to the address using a byte SPI write. Otherwise the
 * address must be modulo 4 and all 32-bits of value are written using a
 * 4-byte SPI write.
 *
 * @param[in] dm_num DigiMMIC to write to. If @c dm_num is ADI_DM_ALL_DIGIMMICS, a write is broadcast to all DigiMMICs.
 * @param[in] addr Address to write to in the DigiMMIC address space.
 * @param[in] value 32-bit value to write.
 * @return ADI_DM_SUCCESS for success, an error code for errors.
 */
adi_dm_err_t adi_dm_Write(adi_dm_num_t dm_num, uint32_t addr, uint32_t value);

adi_dm_err_t adi_dm_Write_Optimize(adi_dm_num_t dm_num, uint32_t addr, uint32_t value);

/**
 * Read a word from the DigiMMIC address space, checking for CRC error.
 *
 * Access to SPI registers is supported by special rules for addresses in the
 * range 0 to 255. If the address is in the range 0 to 255 a byte is read from
 * the address over SPI and zero extended before assigning to value. Otherwise
 * the address must be modulo 4, 4-bytes are read over SPI and assigned to value.
 *
 * @param[in] dm_num DigiMMIC to read from. @c dm_num may not be ADI_DM_ALL_DIGIMMICS.
 * @param[in] addr Address to read from in the DigiMMIC address space.
 * @param[out] value The 32-bit value read.
 * @returns ADI_DM_SUCCESS for success, an error code for errors including ADI_DM_SPI_CRC_ERROR for CRC error.
 */
adi_dm_err_t adi_dm_Read(adi_dm_num_t dm_num, uint32_t addr, uint32_t * value);

/**
 * Read, modify, write a word in the DigiMMIC address space, checking for CRC error.
 *
 * The effect is similar to the following (on the DigiMMIC):
 * @code{.c}
 * uint32_t reg = *addr;
 * reg &= mask;
 * reg |= bits;
 * *addr = reg;
 * @endcode
 *
 * @param[in] dm_num DigiMMIC to read from and write to. If @c dm_num is ADI_DM_ALL_DIGIMMICS, the read-modify-wite is performed on all DigiMMICs.
 * @param[in] addr Address in the DigiMMIC address space.
 * @param[in] mask Bitmask and-ed with value read from DigiMMIC address space.
 * @param[in] bits Bits or-ed with masked value prior to writing back to the DigiMMIC address space.
 * @returns ADI_DM_SUCCESS for success, an error code for errors including ADI_DM_SPI_CRC_ERROR for CRC error.
 */
adi_dm_err_t adi_dm_RMW(adi_dm_num_t dm_num, uint32_t addr, uint32_t mask, uint32_t bits);

/**
 * Write a memory region in the DigiMMIC address space, checking for CRC error.
 *
 * @param[in] dm_num DigiMMIC to write to. If @c dm_num is ADI_DM_ALL_DIGIMMICS, a write is broadcast to all DigiMMICs.
 * @param[in] addr Address to write to in the DigiMMIC address space.
 * @param[in] sz Size of block written the DigiMMICs. Must be a multiple of 4 bytes.
 * @param[in] data Block of data written to the DigiMMICs.
 * @returns ADI_DM_SUCCESS for success, an error code for errors.
 */
adi_dm_err_t adi_dm_BlockWrite(adi_dm_num_t dm_num, uint32_t addr, size_t sz, const void *data);

/**
 *  Read a memory region in the DigiMMIC address space, checking for CRC error.
 *
 * @param[in] dm_num DigiMMIC to read from. @c dm_num may not be ADI_DM_ALL_DIGIMMICS.
 * @param[in] addr Address to read fromin the DigiMMIC address space.
 * @param[in] sz Size of block to read from the DigiMMIC. Must be a multiple of 4 bytes.
 * @param[in] data Block of data read from the DigiMMIC.
 * @returns ADI_DM_SUCCESS for success, an error code for errors including ADI_DM_SPI_CRC_ERROR for CRC error.
 */
adi_dm_err_t adi_dm_BlockRead(adi_dm_num_t dm_num, uint32_t addr, size_t sz, void *data);

/**
 * Execute a firmware task. With arbitrary parameters.
 *
 * @param[in] dm_num The DigiMMIC on which to run the task. If @c dm_num is ADI_DM_ALL_DIGIMMICS, task is executed on all DigiMMICs.
 * @param[in] sz Length of data in bytes.
 * @param[in] data The firmware command and parameters. Should be of a length that is written with one SPI frame.
 * @return ADI_DM_SUCCESS for success, an error code for errors.
 *
 * Hardware faults can be ignored by defining adi_dm_fault_status0_mask,
 * adi_dm_fault_status1_mask and  adi_dm_fault_status2_mask in the user application.
 */
adi_dm_err_t adi_dm_BlockCallFW(adi_dm_num_t dm_num, size_t sz, const void *data);

/**
 * Execute a firmware task. No parameters.
 *
 * @param[in] dm_num The DigiMMIC on which to run the task. If @c dm_num is ADI_DM_ALL_DIGIMMICS, task is executed on all DigiMMICs.
 * @param[in] cmd The firmware command to execute.
 * @return ADI_DM_SUCCESS for success, an error code for errors.
 *
 * Hardware faults can be ignored by defining adi_dm_fault_status0_mask,
 * adi_dm_fault_status1_mask and  adi_dm_fault_status2_mask in the user application.
 */
static inline adi_dm_err_t adi_dm_CallFW(adi_dm_num_t dm_num, uint32_t cmd)
{
    return adi_dm_BlockCallFW(dm_num, sizeof(cmd), &cmd);
}

/**
 * Execute a firmware task. Two parameters.
 *
 * @param[in] dm_num The DigiMMIC on which to run the task. If @c dm_num is ADI_DM_ALL_DIGIMMICS, task is executed on all DigiMMICs.
 * @param[in] cmd The firmware command to execute.
 * @return ADI_DM_SUCCESS for success, an error code for errors.
 *
 * Hardware faults can be ignored by defining adi_dm_fault_status0_mask,
 * adi_dm_fault_status1_mask and  adi_dm_fault_status2_mask in the user application.
 */
static inline adi_dm_err_t adi_dm_CallFW2(adi_dm_num_t dm_num, uint32_t cmd, uint32_t p1, uint32_t p2)
{
    uint32_t params[4];         /* 16-byte frame */
    params[0] = cmd | (2 << 16);
    params[1] = p1;
    params[2] = p2;
    params[3] = 0;
    return adi_dm_BlockCallFW(dm_num, sizeof(params), &params);
}

static inline adi_dm_err_t adi_dm_CallFWU64(adi_dm_num_t dm_num, uint32_t cmd, uint64_t p)
{
    return adi_dm_CallFW2(dm_num, cmd, ((uint32_t *) & p)[0], ((uint32_t *) & p)[1]);
}

extern uint32_t adi_dm_sw_fault0_mask;
extern uint32_t adi_dm_sw_fault1_mask;
extern uint32_t adi_dm_sw_fault2_mask;
extern uint32_t adi_dm_sw_fault3_mask;
extern uint32_t adi_dm_fault_status0_mask;
extern uint32_t adi_dm_fault_status1_mask;
extern uint32_t adi_dm_fault_status2_mask;

/**
 * Control function of an IO pad.
 * Selects the function of the named pad as described in "Input/Output Pad Control and General-Purpose Input/Output" @cite hrm
 *
 * @param[in] dm_num The DigiMMIC to which the IO pad belongs. If @c dm_num is ADI_DM_ALL_DIGIMMICS, task is executed in parallel on all DigiMMICs.
 * @param[in] pin Ihe IO pad to change function.
 * @param[in] fer FER value from Table 52 in @cite hrm.
 * @param[in] mux MUX value from Table 52 in @cite hrm.
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_PinMux(adi_dm_num_t dm_num, adi_dm_gpio_t pin, uint8_t fer, uint8_t mux);

/**@}*/

/**
 * @name Typed memory access
 * These are convenience functions for memory access.
 * They are not strictly required,
 * but may avoid errors in customer code.
 *
 * The following data types (other than uint32_t) are supported:
 *
 * - uint64_t
 * - float
 * - double
 */
/**@{*/

/**
 * Write uint64_t to the DigiMMIC address space, checking for CRC errors.
 *
 * @param[in] dm_num DigiMMIC to write to. If @c dm_num is ADI_DM_ALL_DIGIMMICS, a write is broadcast to all DigiMMICs.
 * @param[in] addr Address to write to in the DigiMMIC address space.
 * @param[in] value 64-bit unsigned integer value to write.
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
static inline adi_dm_err_t adi_dm_WriteU64(adi_dm_num_t dm_num, uint32_t addr, uint64_t value)
{
    uint32_t block[2];
    block[0] = (uint32_t) (value >> 0);
    block[1] = (uint32_t) (value >> 32);
    return adi_dm_BlockWrite(dm_num, addr, 8, block);
}

/**
 * Write float to the DigiMMIC address space, checking for CRC errors.
 *
 * @param[in] dm_num DigiMMIC to write to. If @c dm_num is ADI_DM_ALL_DIGIMMICS, a write is broadcast to all DigiMMICs.
 * @param[in] addr Address to write to in the DigiMMIC address space.
 * @param[in] value The 32-bit floating-point value to write.
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
static inline adi_dm_err_t adi_dm_WriteF32(adi_dm_num_t dm_num, uint32_t addr, float value)
{
    return adi_dm_Write(dm_num, addr, *(uint32_t *) & value);
}

/**
 * Read float from the DigiMMIC address space, checking for CRC errors.
 *
 * @param[in] dm_num DigiMMIC to read from. @c dm_num may not be ADI_DM_ALL_DIGIMMICS.
 * @param[in] addr Address to read from in the DigiMMIC address space.
 * @param[out] value The 32-bit floating-point value read.
 * @returns ADI_DM_SUCCESS for success, an error code for errors including ADI_DM_SPI_CRC_ERROR for CRC error.
 */
static inline adi_dm_err_t adi_dm_ReadF32(adi_dm_num_t dm_num, uint32_t addr, float *value)
{
    uint32_t u32;
    adi_dm_err_t res = adi_dm_Read(dm_num, addr, &u32);
    if (res == ADI_DM_SUCCESS) {
        *value = *(float *) &u32;
    }
    return res;
}

/**
 * Read uint64_t value from the DigiMMIC address space, checking for CRC errors.
 *
 * @param[in] dm_num DigiMMIC to read from. @c dm_num may not be ADI_DM_ALL_DIGIMMICS.
 * @param[in] addr Address to read from in the DigiMMIC address space.
 * @param[out] value The 64-bit unsigned integer value read.
 * @returns ADI_DM_SUCCESS for success, an error code for errors including ADI_DM_SPI_CRC_ERROR for CRC error.
 */
static inline adi_dm_err_t adi_dm_ReadU64(adi_dm_num_t dm_num, uint32_t addr, uint64_t * value)
{
    uint32_t block[2];
    adi_dm_err_t res = adi_dm_BlockRead(dm_num, addr, 8, &block);
    if (res == ADI_DM_SUCCESS) {
        uint64_t result = block[1];
        result <<= 32;
        result |= block[0];
        *value = result;
    }
    return res;
}

/**
 * Read double from the DigiMMIC address space, checking for CRC errors
 *
 * @param[in] dm_num DigiMMIC to read from. @c dm_num may not be ADI_DM_ALL_DIGIMMICS.
 * @param[in] addr Address to read from in the DigiMMIC address space.
 * @param[out] value The 64-bit floating-point value read.
 * @returns ADI_DM_SUCCESS for success, an error code for errors including ADI_DM_SPI_CRC_ERROR for CRC error.
 */
static inline adi_dm_err_t adi_dm_ReadF64(adi_dm_num_t dm_num, uint32_t addr, double *value)
{
    uint64_t u64;
    adi_dm_err_t res = adi_dm_ReadU64(dm_num, addr, &u64);
    if (res == ADI_DM_SUCCESS) {
        *value = *(double *) &u64;
    }
    return res;
}

/**
 * Write double to the DigiMMIC address space, checking for CRC errors.
 *
 * @param[in] dm_num DigiMMIC to write to. If @c dm_num is ADI_DM_ALL_DIGIMMICS, a write is broadcast to all DigiMMICs.
 * @param[in] addr Address to write to in the DigiMMIC address space.
 * @param[in] value The 64-bit floating-point value to write.
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
static inline adi_dm_err_t adi_dm_WriteF64(adi_dm_num_t dm_num, uint32_t addr, double value)
{
    return adi_dm_WriteU64(dm_num, addr, *(uint64_t *) & value);
}

/**@}*/

/**
 * @name High-level
 * This is the high-level API.
 */
/**@{*/

#define ADI_DM_NUM_TX 3     /** Number of Tx channels on each part. */
#define ADI_DM_NUM_RX 4     /** Number of Rx channels on each part. */

/**
 * Enumeration for high pass filter (HPF) corner frequency
 */
typedef enum {
    ADI_DM_HPF_FC_125_KHZ = 0,
    ADI_DM_HPF_FC_250_KHZ = 1,
    ADI_DM_HPF_FC_500_KHZ = 2,
    ADI_DM_HPF_FC_1_MHZ = 3,
    ADI_DM_HPF_FC_2_MHZ = 4,
    ADI_DM_HPF_FC_4_MHZ = 5,
    ADI_DM_HPF_FC_8_MHZ = 6
} adi_dm_hpf_fc_t;

/**
 * Enumeration for high pass filter (HPF) gain
 */
typedef enum {
    ADI_DM_HPF_GAIN_6_DB = 0,
    ADI_DM_HPF_GAIN_12_DB = 1,
    ADI_DM_HPF_GAIN_18_DB = 2
} adi_dm_hpf_gain_t;

/**
 * Enumeration for programmable gain amplifier (PGA) in RX channel
 */
typedef enum {
    ADI_DM_PGA_GAIN_0_DB = 0,
    ADI_DM_PGA_GAIN_6_DB = 1,
    ADI_DM_PGA_GAIN_12_DB = 2,
    ADI_DM_PGA_GAIN_18_DB = 3,
    ADI_DM_PGA_GAIN_24_DB = 4
} adi_dm_pga_gain_t;

/**
 * Enumeration for programmable gain amplifier (PGA) in RX channel
 */
typedef enum {
    ADI_DM_ADC_GAIN_0_DB = 0,
    ADI_DM_ADC_GAIN_3_DB = 2
} adi_dm_adc_gain_t;

/**
 * Enumeration for programmable gain amplifier (PGA) input
 */
typedef enum {
    ADI_DM_PGA_MUX_HPF_OUTPUT = 0,
    ADI_DM_PGA_MUX_HPF_INPUT = 1,
    ADI_DM_PGA_MUX_DISCONNECTED = 2
} adi_dm_pga_mux_t;

/**
 * Ramp Profile.
 * Data type equivalent to contents of the RAMPGEN registers across a cascade of DigiMMICs.
 * Fields describing the shape of the ramp are common across cascaded devices.
 * Other fields are duplicated for each device.
 */
typedef struct {
    unsigned del_0:22;        /**< Delay before starting the first slope of the ramp */
    unsigned del_1:20;        /**< Delay between the two slopes of the ramp */
    unsigned del_2:22;        /**< Delay before starting the next ramp */

    uint32_t ramp_steps_0;    /**< Number of steps for the first slope of the ramp */
    uint32_t ramp_steps_1;    /**< Number of steps for the second slope of the ramp */

    int32_t ramp_dev_0;       /**< Change in frequency at each step of the first slope */
    int32_t ramp_dev_1;       /**< Change in frequency at each step of the second slope */

    uint16_t afe_start_off_time;    /**< Time for which the ADC is off after the start of the ramp, in AFE_CLK cycles */
    uint16_t afe_ramp_time;         /**< Total ramp time, in AFE_CLK cycles */
    unsigned num_samples:13;        /**< Number of ADC samples to take per ramp */

    struct {
        unsigned tx_pattern:3;      /**< Transmitters to enable for the ramp. A bitset. */

        unsigned ramp_stat_bit_0:1; /**< See "Ramp Status Pins" subsection of @cite hrm. */
        unsigned ramp_stat_bit_1:1; /**< See "Ramp Status Pins" subsection of @cite hrm. */
        unsigned ramp_stat_bit_2:1; /**< See "Ramp Status Pins" subsection of @cite hrm. */

        unsigned pa0_phase:7;       /**< Initial phase index for Tx0. */
        unsigned pa1_phase:7;       /**< Initial phase index for Tx1. */
        unsigned pa2_phase:7;       /**< Initial phase index for Tx2. */

        unsigned phase_step:5;      /**< If non-zero, delay before incrementing phase, in AFE_CLK cycles. */

        unsigned pa0_phase_dev:7;   /**< Increment to phase index for Tx0 each phase step. */
        unsigned pa1_phase_dev:7;   /**< Increment to phase index for Tx1 each phase step. */
        unsigned pa2_phase_dev:7;   /**< Increment to phase index for Tx2 each phase step. */
    } dm[ADI_DM_NUM_DIGIMMIC];
} adi_dm_ramp_profile_t;

/**
 * Tx Overlay.
 * Data type equivalent to the contents of the RAMP_GEN_TX register used for the tx_overlay
 * field of ::adi_dm_burst_profile_t.  A denser encoding of a burst profile which only differs
 * in these elements can be achieved by specifying many tx_overlays rather than many ramp_profiles
 */
typedef struct {
    unsigned pa0_phase:7;       /**< Initial phase index for Tx0. */
    unsigned pa1_phase:7;       /**< Initial phase index for Tx1. */
    unsigned pa2_phase:7;       /**< Initial phase index for Tx2. */

    unsigned tx_pattern:3;      /**< Transmitters to enable for the ramp. A bitset. */

    unsigned phase_step:5;      /**< If non-zero, delay before incrementing phase, in AFE_CLK cycles. */

    unsigned ramp_stat_bit_0:1; /**< See "Ramp Status Pins" subsection of @cite hrm. */
    unsigned ramp_stat_bit_1:1; /**< See "Ramp Status Pins" subsection of @cite hrm. */
    unsigned ramp_stat_bit_2:1; /**< See "Ramp Status Pins" subsection of @cite hrm. */
} adi_dm_tx_overlay_t;

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

    } dm[ADI_DM_NUM_DIGIMMIC];
} adi_dm_ramp_config_t;

/**
 * Burst Profile.
 * Data type corresponding to the burst description that gets stored in memory for a DMA generated burst.
 * Note that in order to accomodate adi_dm_PowerDetectorMeasTask, the minimum
 * number of ramps in a burst should be 228.
 */
typedef struct {
    uint32_t num_ramps_in_seq;                  /**< Number of ramps in a sequence and number of elements in ramp array. */
    uint32_t num_seq_in_burst;                  /**< Number of sequences in a burst. */
    adi_dm_ramp_profile_t *ramp_profile;        /**< Array of ramp profiles. */
    uint32_t tx_overlay_len;                    /**< Length of tx_overlay array. Zero for no array. */
    adi_dm_tx_overlay_t *tx_overlay[ADI_DM_NUM_DIGIMMIC];  /**< Array of bit fields to overlay ramp_gen_tx register. per device */
} adi_dm_burst_profile_t;

/**
 * Effective enumeration for CLKOUTCTRL clock selection.
 * Value must be one of the following.
 *
 * * ::ADI_DM_REF_CLK_DIV_2
 * * ::ADI_DM_REF_CLK_DIV_4
 * * ::ADI_DM_REF_CLK_DIV
 */
typedef uint8_t adi_dm_clkoutctrl_t;

#define ADI_DM_REF_CLK_DIV_2 0U /**< Set CLKOUT pin to ref_clk / 2. @see adi_dm_clkoutctrl_t. */
#define ADI_DM_REF_CLK_DIV_4 1U /**< Set CLKOUT pin to ref_clk / 4. @see adi_dm_clkoutctrl_t. */
#define ADI_DM_REF_CLK_DIV 2U /**< Set CLKOUT pin to ref_clk. @see adi_dm_clkoutctrl_t. */

/**
 * Values for ADI_ADAR690x_CFG_TIMING_COMP_EN setting for BIST56.
 * This BIST ensures ramp timings on cascaded devices are consistent.
 * The check compares STAT1 monitor input on GPIO7 has the same timing as local ramp.
 * The input some from STAT0 signal output on GPIO9 of the neighbour device.
 * The recommended board layout connects GPIO9 with GPIO7 in a chain,
 * leaving one device with GPIO7 unconnected and another, at the other
 * end of the chain, with GPIO9 unconnected. These values tell the driver how
 * the GPIO7 and GPIO9 pins of each device are connected.
 *
 * Value must be one of the following.
 *
 * * ::ADI_DM_TIMING_COMP_DISABLED
 * * ::ADI_DM_TIMING_COMP_GPIO7_GPIO9
 * * ::ADI_DM_TIMING_COMP_GPIO7_ONLY
 * * ::ADI_DM_TIMING_COMP_GPIO9_ONLY
 */
typedef uint8_t adi_dm_timing_comp_setting_t;

#define ADI_DM_TIMING_COMP_DISABLED 0U /**< Disabled. @see adi_dm_timing_comp_setting_t. */
#define ADI_DM_TIMING_COMP_GPIO7_GPIO9 1U /**< GPIO7 and GPIO9 connected. @see adi_dm_timing_comp_setting_t. */
#define ADI_DM_TIMING_COMP_GPIO7_ONLY 2U /**< Only GPIO7 connected. @see adi_dm_timing_comp_setting_t. */
#define ADI_DM_TIMING_COMP_GPIO9_ONLY 3U /**< Only GPIO9 connected. @see adi_dm_timing_comp_setting_t. */

/**
 * @em IN parameter to @c adi_dm_PowerUp
 *
 * @see adi_dm_PowerUp
 */
typedef struct {
    bool power_part_only;       /**< Power up the part but do not initialize it. Exits after RTWO power up. */
    bool power_part_load_files_only;       /**< Power up the part and load the firmware but do not initialize it */
    bool is_standalone_master;  /**< Execute init sequence for cascaded master. Only applies if driver built for a single DigiMMIC. */
    bool is_standalone_slave;   /**< Execute init sequence for cascaded slave. Only applies if driver built for a single DigiMMIC. */

    bool is_lo_right[ADI_DM_NUM_DIGIMMIC];  /**< Setting of lo_left_right for each device. */
    adi_dm_timing_comp_setting_t timing_comp_setting[ADI_DM_NUM_DIGIMMIC]; /**< ADI_ADAR690x_CFG_TIMING_COMP_EN setting.
                                                                            * This BIST ensures ramp timings on cascaded devices
                                                                            * are consitent by comparing local ramp time with STAT1
                                                                            * monitor input which is generated by another device's
                                                                            * STAT0 output. The recommended wiring connects leaves
                                                                            * one device's input unconnected so the comparator
                                                                            * should be disabled on that device.
                                                                            */

    const uint32_t *firmware_image;             /**< Firmware code image in host memory. */
    uint32_t firmware_sz;                       /**< Size of firmware code image. */
    const uint32_t *firmware_constants_image;   /**< Firmware constants image in host memory. */
    uint32_t firmware_constants_sz;             /**< Size of firmware constants. */

    uint32_t ref_freq_hz;           /**< Reference clock */
    uint32_t rfpll_loop_bw_hz;      /**< RF PLL Loop Bandwidth */
    uint64_t ramp_start_freq_hz;    /**< Tx output frequency at start of burst */
    float ramp_bw_Mhz;              /**< Maximum ramp bandwidth */

    bool enable_clkhost;             /**< Enable the CLKHOST pin. */
    adi_dm_clkoutctrl_t clkoutctrl; /**< Signal on CLKHOST pin if enabled. See "Reference input Section" in @cite hrm. */
} adi_dm_power_up_t;

/**
 * Power up device.
 *
 * @param[in] p parameters see ::adi_dm_power_up_t.
 * @return ADI_DM_SUCCESS on success, an error code on failure,
 */
adi_dm_err_t adi_dm_PowerUp(const adi_dm_power_up_t * p);

/**
 * Power down device.
 *
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_PowerDown(void);

#define ADI_DM_OUTPUT_BITWIDTH_16 0U /**< Set filter_output_bitwidth to 16. @see ::adi_dm_lvds_setup_t and ::adi_dm_mipi_setup_t. */
#define ADI_DM_OUTPUT_BITWIDTH_14 1U /**< Set filter_output_bitwidth to 14. @see ::adi_dm_lvds_setup_t and ::adi_dm_mipi_setup_t. */
#define ADI_DM_OUTPUT_BITWIDTH_12 2U /**< Set filter_output_bitwidth to 12. @see ::adi_dm_lvds_setup_t and ::adi_dm_mipi_setup_t. */

/**
 * Effective enumeration for LVDS clock selection.
 * Value must be one of the following.
 *
 * * ::ADI_DM_ADCCLK_DIV_1_5
 * * ::ADI_DM_ADCCLK_DIV_2
 * * ::ADI_DM_ADCCLK_DIV_3
 * * ::ADI_DM_ADCCLK_DIV_4
 * * ::ADI_DM_ADCCLK_DIV_6
 * * ::ADI_DM_ADCCLK_DIV_8
 */
typedef uint8_t adi_dm_lvds_clk_t;

#define ADI_DM_ADCCLK_DIV_6 1U /**< Set lvds_clk to ADCCLK / 6. @see adi_dm_lvds_clk_t. */
#define ADI_DM_ADCCLK_DIV_1_5 2U /**< Set lvds_clk to ADCCLK / 1.5. @see adi_dm_lvds_clk_t. */
#define ADI_DM_ADCCLK_DIV_2 3U /**< Set lvds_clk to ADCCLK / 2. @see adi_dm_lvds_clk_t. */
#define ADI_DM_ADCCLK_DIV_3 4U /**< Set lvds_clk to ADCCLK / 3. @see adi_dm_lvds_clk_t. */
#define ADI_DM_ADCCLK_DIV_4 5U /**< Set lvds_clk to ADCCLK / 4. @see adi_dm_lvds_clk_t. */
#define ADI_DM_ADCCLK_DIV_8 6U /**< Set lvds_clk to ADCCLK / 8. @see adi_dm_lvds_clk_t. */

/**
 * @em IN parameter to @c adi_dm_LvdsSetup
 *
 * @see adi_dm_LvdsSetup
 */
typedef struct {
    bool crc32_en;                  /**< Enable CRC32 field. See "CRC32" in "LVDS Data Frame Content" in @cite hrm. */
    bool status_en;                 /**< Enable status field. See "Status Data" in "LVDS Data Frame Content" in @cite hrm. */
    unsigned filter_output_bitwidth:2;  /**< Bits per sample. Must be one of
                                         * ::ADI_DM_OUTPUT_BITWIDTH_16,
                                         * ::ADI_DM_OUTPUT_BITWIDTH_14, or
                                         * ::ADI_DM_OUTPUT_BITWIDTH_12
                                         */

    bool dual_fs_mode;              /**< Select dual frame sync mode. See "LVDS Data Framing" in @cite hrm. */
    bool fs_active_low;             /**< Frame sync active low. See "LVDS Data Framing" in @cite hrm. */
    bool streaming_mode_1;          /**< Select streaming mode 1. See "LVDS Streaming Modes" in @cite hrm. */
    bool payload_dis;               /**< Disable transmission of RX channel data. See "Rx Channel Data" in "LVDS Data Frame Content" in @cite hrm. */
    bool id_wc_en;                  /**< Enable dataid and word count fields. See "Data ID and Byte Count" in "LVDS Data Frame Content" in @cite hrm. */
    bool ls_byte_first;             /**< Send least significant byte first. See "LVDS Data Formatting" in @cite hrm. */
    bool ls_bit_first;              /**< Send least significant bit first. See "LVDS Data Formatting" in @cite hrm. */
    adi_dm_lvds_clk_t lvds_clk;     /**< Select lvds_clk. See "LVDS Clock selection ..." in @cite hrm. */

    struct {
        uint8_t userval0;           /**< Appears in rx0 status field. See "Status Data" in "LVDS Data Frame Content" in @cite hrm. */
        uint8_t userval1;           /**< Appears in rx1 status field. See "Status Data" in "LVDS Data Frame Content" in @cite hrm. */
        uint8_t userval2;           /**< Appears in rx2 status field. See "Status Data" in "LVDS Data Frame Content" in @cite hrm. */
        uint8_t userval3;           /**< Appears in rx3 status field. See "Status Data" in "LVDS Data Frame Content" in @cite hrm. */

        uint8_t dataid0;            /**< Appears in rx0 dataid field. See "Data ID and Byte Count" in "LVDS Data Frame Content" in @cite hrm. */
        uint8_t dataid1;            /**< Appears in rx1 dataid field. See "Data ID and Byte Count" in "LVDS Data Frame Content" in @cite hrm. */
        uint8_t dataid2;            /**< Appears in rx2 dataid field. See "Data ID and Byte Count" in "LVDS Data Frame Content" in @cite hrm. */
        uint8_t dataid3;            /**< Appears in rx3 dataid field. See "Data ID and Byte Count" in "LVDS Data Frame Content" in @cite hrm. */
    } dm[ADI_DM_NUM_DIGIMMIC];
} adi_dm_lvds_setup_t;

/**
 * Dataport configuration for LVDS parts.
 *
 * @param[in] p parameters. See ::adi_dm_lvds_setup_t
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_LvdsSetup(const adi_dm_lvds_setup_t * p);


/**
 * Effective enumeration for MIPI clock selection.
 * Value must be one of the following.
 *
 * * ::ADI_DM_MIPI_CLK_80MHZ
 * * ::ADI_DM_MIPI_CLK_650MHZ
 * * ::ADI_DM_MIPI_CLK_800MHZ
 * * ::ADI_DM_MIPI_CLK_1000MHZ
 * * ::ADI_DM_MIPI_CLK_1200MHZ
 */
typedef uint32_t adi_dm_mipi_clk_t;

#define ADI_DM_MIPI_CLK_1200MHZ 0UL /**< Set mipi_clk to 1.2 GHz. See ::adi_dm_mipi_clk_t. */
#define ADI_DM_MIPI_CLK_1000MHZ 1UL /**< Set mipi_clk to 1.0 GHz. See ::adi_dm_mipi_clk_t. */
#define ADI_DM_MIPI_CLK_800MHZ 2UL /**< Set mipi_clk to 800 MHz. See ::adi_dm_mipi_clk_t. */
#define ADI_DM_MIPI_CLK_80MHZ 3UL /**< Set mipi_clk to 80 MHz. See ::adi_dm_mipi_clk_t. */
#define ADI_DM_MIPI_CLK_650MHZ 4UL /**< Set mipi_clk to 650 MHz. See ::adi_dm_mipi_clk_t. */
#define ADI_DM_MIPI_CLK_NUM 5UL /**< Used to check ::adi_dm_mipi_clk_t range. */

/**
 * Effective enumeration for number of MIPI lanes to enable.
 * Value must be one of the following.
 *
 * * ::ADI_DM_4_MIPI_LANES
 * * ::ADI_DM_2_MIPI_LANES
 * * ::ADI_DM_1_MIPI_LANE
 */
typedef uint32_t adi_dm_num_mipi_lanes_t;

#define ADI_DM_1_MIPI_LANE 0UL /**< Enable 1 lane. See ::adi_dm_num_mipi_lanes_t. */
#define ADI_DM_2_MIPI_LANES 1UL /**< Enable 2 lanes. See ::adi_dm_num_mipi_lanes_t. */
#define ADI_DM_4_MIPI_LANES 2UL /**< Enable 4 lanes. See ::adi_dm_num_mipi_lanes_t. */

/**
 * Effective enumeration for payload MIPI data type.
 * Value must be one of the following.
 *
 * * ::ADI_DM_YUV422_8B
 * * ::ADI_DM_RGB444
 * * ::ADI_DM_RGB555
 * * ::ADI_DM_RGB565
 * * ::ADI_DM_RAW6
 * * ::ADI_DM_RAW7
 * * ::ADI_DM_RAW8
 * * ::ADI_DM_RAW12
 * * ::ADI_DM_RAW14
 */
typedef uint32_t adi_dm_mipi_data_type_t;

#define ADI_DM_YUV422_8B 0x1EUL /**< YUV422_8B. See ::adi_dm_mipi_data_type_t. */
#define ADI_DM_RGB444 0x20UL /**< RGB444. See ::adi_dm_mipi_data_type_t. */
#define ADI_DM_RGB555 0x21UL /**< RGB555. See ::adi_dm_mipi_data_type_t. */
#define ADI_DM_RGB565 0x22UL /**< RGB565. See ::adi_dm_mipi_data_type_t. */
#define ADI_DM_RAW6 0x28UL /**< RAW6. See ::adi_dm_mipi_data_type_t. */
#define ADI_DM_RAW7 0x29UL /**< RAW7. See ::adi_dm_mipi_data_type_t. */
#define ADI_DM_RAW8 0x2AUL /**< RAW8. See ::adi_dm_mipi_data_type_t. */
#define ADI_DM_RAW12 0x2CUL /**< RAW12. See ::adi_dm_mipi_data_type_t. */
#define ADI_DM_RAW14 0x2DUL /**< RAW14. See ::adi_dm_mipi_data_type_t. */

/**
 * @em IN parameter to @c adi_dm_MipiSetup
 *
 * @see adi_dm_MipiSetup
 */
typedef struct {
    bool crc32_en;                  /**< Enable CRC32 field. See "CRC32" in "Data Frame Content" in @cite hrm. */
    bool status_en;                 /**< Enable status field. See "Status word" in "Data Frame Content" in @cite hrm. */
    unsigned filter_output_bitwidth:2;  /**< Bits per sample. Must be one of
                                         * ::ADI_DM_OUTPUT_BITWIDTH_16,
                                         * ::ADI_DM_OUTPUT_BITWIDTH_14, or
                                         * ::ADI_DM_OUTPUT_BITWIDTH_12
                                         */

    uint32_t ref_freq_hz;           /**< Reference frequency, in hertz. The same value passed to adi_dm_PowerUp(). */
    adi_dm_mipi_clk_t mipi_clk;     /**< MIPI CSI-2 clock. */
    bool continuous_clock;          /**< Continuous clock mode */
    adi_dm_num_mipi_lanes_t num_lanes;
    adi_dm_mipi_data_type_t mipi_data_type;
    bool ls_byte_first;             /**< Send least significant byte first. See "Data Interleaving & Byte Order (endianness)" in @cite hrm. */
    bool byte_interleaving;         /**< See "Data Interleaving & Byte Order (endianness)" in @cite hrm. */

    struct {
        uint8_t userval0;           /**< Appears in rx0 status field. See "Status Data" in "MIPI Data Frame Content" in @cite hrm. */
        uint8_t userval1;           /**< Appears in rx1 status field. See "Status Data" in "MIPI Data Frame Content" in @cite hrm. */
        uint8_t userval2;           /**< Appears in rx2 status field. See "Status Data" in "MIPI Data Frame Content" in @cite hrm. */
        uint8_t userval3;           /**< Appears in rx3 status field. See "Status Data" in "MIPI Data Frame Content" in @cite hrm. */
    } dm[ADI_DM_NUM_DIGIMMIC];
} adi_dm_mipi_setup_t;

/**
 * Dataport configuration for MIPI parts.
 *
 * @param[in] p parameters. See ::adi_dm_mipi_setup_t
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_MipiSetup(const adi_dm_mipi_setup_t * p);

/**
 * @em IN parameter to @c adi_dm_AfeSetup
 *
 * @see adi_dm_AfeSetup
 */
typedef struct {
    uint32_t rx_channels;       /**< If zero, settings are applied to all RX channels.
                                 * If non-zero, settings are applied to RX channels for
                                 * which a bit is set. In a multi-device system the first
                                 * 4 bits correspond to the 4 Rx channels of ADI_DM_MASTER,
                                 * the next 4 to the channels for ADI_DM_SLAVE1 etc. So,
                                 * for instance, if `rx_channels` is 0x21 then, as bits 0
                                 * and 5 are set, the settings are applied to ADI_DM_MASTER Rx0
                                 * and ADI_DM_SLAVE1 Rx1.
                                 */
    adi_dm_hpf_fc_t hpf_fc;     /**< High pass filter (HPF) corner frequency */
    adi_dm_hpf_gain_t hpf_gain; /**< High pass filter (HPF) gain */
    bool hpf_bypass;            /**< If true, high pass filter (HPF) is bypassed, otherwise it is enabled */
    adi_dm_pga_mux_t pga_mux;   /** Selects input to programmable gain amplifier (PGA) */
    adi_dm_pga_gain_t pga_gain; /** programmable gain amplifier (PGA) gain. */
    adi_dm_adc_gain_t adc_gain; /** ADC gain. */
} adi_dm_afe_setup_t;

/**
 * Analog front end (AFE) configuration.
 *
 * @param[in] p parameters. See ::adi_dm_afe_setup_t.
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_AfeSetup(const adi_dm_afe_setup_t * p);

/**
 * @em IN parameter to @c adi_dm_TxSetup
 *
 * Alters firmware parameters for Tc=x channels.
 *
 * @see adi_dm_TxSetup
 */
typedef struct {
    struct {
        unsigned tx_enable:3;   /**< Bitset. Enable Tx channel for which corresponding bit is set. */
        unsigned continuous_pa:3;  /**< Continuous Tx. Bitset. Put Tx channel for which corresponding bit is set into continuous mode. */
        int32_t pa_gain_backoff_db[ADI_DM_NUM_TX];  /**< Tx gain setting specified as negative number of dB to add to max power. A value between 0 and -10. */
    } dm[ADI_DM_NUM_DIGIMMIC];
} adi_dm_tx_setup_t;

/**
 * Transmitter path (Tx) configuration.
 *
 * @param[in] p parameters. See ::adi_dm_tx_setup_t.
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_TxSetup(const adi_dm_tx_setup_t * p);

/**
 * High level description of ramp shape input to adi_dm_CalcRamp()
 *
 * @see adi_dm_CalcRamp
 */
typedef struct {
    float slope0_time_us;           /**< Time for first slope of ramp, in microseconds. */
    float slope1_time_us;           /**< Time for second slope of ramp, in microseconds. */
    float delay0_time_us;           /**< Time for delay before `slope0`, in microseconds. */
    float delay1_time_us;           /**< Time for delay between `slope0` and `slope1`, in microseconds. */
    float delay2_time_us;           /**< Time for delay after `slope1`, in microseconds. */
    float ramp_bw_Mhz;              /**< Difference between frequency of `delay1` and `delay0`, in megahertz. */

    uint32_t num_samples;           /**< Number of samples. */
    float sample_start_time_us;     /**<
                                     * Time to start sampling, measured from start of `delay0` in microseconds.
                                     * This time includes the decimation filter group delay. See `filter_valid_delay`.
                                     * When `sample_start_time_us` is zero `afe_init_del` is calculated by placing
                                     * the sample window as far right in `slope0` as possible.
                                     */

    bool pga_shunt_en;              /**<
                                     * Enable PGA Shunt. See @cite hrm "Frequency Ramp" subsection.
                                     * Note this value must be the same for every ramp in a burst.
                                     */
    float pga_shunt_start_del_us;   /**<
                                     * Start delay for PGA Shunt, in microseconds.
                                     * If `pga_shunt_en` is true and this is zero
                                     * a default value is returned.
                                     * Note this value must be the same for every ramp in a burst.
                                     */
    float pga_shunt_stop_del_us;    /**<
                                     * Stop delay for PGA Shunt, in microseconds.
                                     * If `pga_shunt_en` is true and this is zero
                                     * a default value is returned.
                                     * Note this value must be the same for every ramp in a burst.
                                     */


    uint32_t filter_valid_delay;    /**<
                                     * Decimation filter group delay. See @cite hrm "Frequency Ramp" subsection.
                                     * If this is zero, a default value is returned.
                                     * Note this value must be the same for every ramp in a burst.
                                     */

    uint32_t decim_ratio;           /**<
                                     * Decimation ratio. See @cite hrm "Decimation filter" subsection.
                                     * Must be one of 24, 32, 48, 64, 96, 128, 192 or 256.
                                     */

    uint32_t ref_freq_hz;           /**< Reference frequency, in hertz. Must be a value in the range 40 MHz to 80 MHz */

    unsigned ramp_count:12;         /**< Copied through to adi_dm_CalcRamp() ramp_config output parameter. */
} adi_dm_ramp_shape_t;

/**
 * High level description of ramp shape output by adi_dm_CalcRamp()
 *
 * @see adi_dm_CalcRamp
 */
typedef struct {
    float slope0_time_us;           /**< Actual time for first slope of ramp, in microseconds. */
    float slope1_time_us;           /**< Actual time for second slope of ramp, in microseconds. */
    float delay0_time_us;           /**< Actual time for delay before `slope0`, in microseconds. */
    float delay1_time_us;           /**< Actual time for delay between `slope0` and `slope1`, in microseconds. */
    float delay2_time_us;           /**< Actual time for delay after `slope1`, in microseconds. */
    float ramp_bw_Mhz;              /**< Actual difference between frequency of `delay1` and `delay0`, in megahertz. */

    float afe_start_off_time_us;        /**< Duration of `afe_stat_off_time` in microseconds. */
    float filter_valid_delay_time_us;   /**< Duration of `filter_valid_delay` in microseconds. */
    float sample_time_us;               /**< Duration of the sampling period in microseconds. */

    float sample_start_time_us;     /**< Actual time to start sampling. */

    float afe_ramp_time_us;         /**< Ramp time calculated from AFE clk */

    bool pga_shunt_en;              /**< PGA Shunt enabled. */
    float pga_shunt_start_del_us;   /**< Actual start delay for PGA Shunt, in microseconds. */
    float pga_shunt_stop_del_us;    /**< Actual stop delay for PGA Shunt, in microseconds. */

    float afe_freq_Mhz;             /**< AFE CLK frequency, in megahertz. */
    float sample_rate_Mhz;          /**< Sample rate in megahertz. */
} adi_dm_actual_ramp_shape_t;

/**
 * Calculate ramp profile from high level parameters.
 * Although this function is hardware-independent,
 * it is part of the driver library so it can be called by user code.
 * It is also strictly optional as the hardware-level parameters can just be passed from user code to
 * @c adi_dm_BuiltinMimoSetup and @c adi_dm_BurstProfileSetup.
 * This is by design.
 *
 * @note
 * Because of hardware limitations, the ramp profile may not @em exactly match what was requested.
 * In particular, the "Ramp Generator - AFE Timing" subsection of @cite hrm states that
 * > "the duration of each ramp must be an integer multiple of the CLK and AFE_CLK periods."
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
adi_dm_err_t adi_dm_CalcRamp(const adi_dm_ramp_shape_t * in, adi_dm_ramp_profile_t * ramp_profile, adi_dm_ramp_config_t * ramp_config, adi_dm_actual_ramp_shape_t * actual);

#define ADI_DM_BITP_MIMO_SEQ_VAL_PAT0 0             /**< Bit position of active antennas during sequence step 0 */
#define ADI_DM_BITM_MIMO_SEQ_VAL_PAT0 0x7           /**< Bit mask of active antennas during sequence step 0 */
#define ADI_DM_BITP_MIMO_SEQ_VAL_PHASE0 3           /**< Bit position of phase during sequence step 0 */
#define ADI_DM_BITM_MIMO_SEQ_VAL_PHASE0 0x8         /**< Bit mask of phase during sequence step 0 */
#define ADI_DM_BITP_MIMO_SEQ_VAL_PAT1 4             /**< Bit position of active antennas during sequence step 1 */
#define ADI_DM_BITM_MIMO_SEQ_VAL_PAT1 0x70          /**< Bit mask of active antennas during sequence step 1 */
#define ADI_DM_BITP_MIMO_SEQ_VAL_PHASE1 7           /**< Bit position of phase during sequence step 1 */
#define ADI_DM_BITM_MIMO_SEQ_VAL_PHASE1 0x80        /**< Bit mask of phase during sequence step 1 */
#define ADI_DM_BITP_MIMO_SEQ_VAL_PAT2 8             /**< Bit position of active antennas during sequence step 2 */
#define ADI_DM_BITM_MIMO_SEQ_VAL_PAT2 0x700         /**< Bit mask of active antennas during sequence step 2 */
#define ADI_DM_BITP_MIMO_SEQ_VAL_PHASE2 11          /**< Bit position of phase during sequence step 2 */
#define ADI_DM_BITM_MIMO_SEQ_VAL_PHASE2 0x800       /**< Bit mask of phase during sequence step 2 */

/**
 * @em IN parameter to adi_dm_BuiltinMimoSetup()
 *
 * Register values for ramp generation using built-in MIMO mode.
 * See "Built-in MIMO Mode" subsection of @cite hrm.
 *
 * @see adi_dm_BuiltinMimoSetup
 */
typedef struct {
    adi_dm_ramp_config_t ramp_config;       /**< Burst invariant ramp configuration. */
    adi_dm_ramp_profile_t ramp_profile;     /**< Ramp parameters. */
    unsigned mimo_seq_len:2;                /**< Length of MIMO sequences. See "Built-in MIMO Mode" subsection of @cite hrm */
    struct {
        unsigned mimo_seq_val:12;           /**< Tx and phase pattern for each device. See "Built-in MIMO Mode" subsection of @cite hrm */
    } dm[ADI_DM_NUM_DIGIMMIC];
} adi_dm_builtin_mimo_setup_t;

/**
 * Register writes for ramp generation using built-in MIMO mode.
 *
 * See "Built-in MIMO Mode" subsection of @cite hrm.
 *
 * @param[in] p parameters. See ::adi_dm_builtin_mimo_setup_t.
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_BuiltinMimoSetup(const adi_dm_builtin_mimo_setup_t * p);

/**
 * Memory writes for ramp generation using DMA.
 *
 * See "DMA Interfacing" subsection of @cite hrm.
 *
 * @param[in] p Burst Profile to be written to memory.
 * @param[in,out] dma_mem_limit Pass in 0 for first burst profile. Pass in returned dma_mem_limit for subsequent profiles.
 * @param[out] bpid "Burst Profile Identifier" identifies this profile to adi_dm_DmaRampSetup() and adi_dm_SelectBurstProfile().
 * @return ADI_DM_SUCCESS for success, an error code for errors.
 */
adi_dm_err_t adi_dm_BurstProfileSetup(const adi_dm_burst_profile_t * p, uint32_t * dma_mem_limit, uint32_t * bpid);

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
    adi_dm_ramp_config_t ramp_config;   /**< Burst invariant ramp configuration. */
    uint32_t bpid;                      /**< Select first profile to use, from adi_dm_BurstProfileSetup(). */
} adi_dm_dma_ramp_setup_t;

/**
 * Register writes for ramp generation using DMA.
 *
 * See "DMA Interfacing" subsection of @cite hrm.
 *
 * @param[in] p parameters. See ::adi_dm_dma_ramp_setup_t.
 * @return ADI_DM_SUCCESS for success, an error code for errors.
 */
adi_dm_err_t adi_dm_DmaRampSetup(const adi_dm_dma_ramp_setup_t * p);

/**
 * Select the burst profile to use for subsequent bursts.
 *
 * Requires adi_dm_DmaRampSetup() to have been called. Used to select a profile
 * to replace the one passed to adi_dm_DmaRampSetup().
 * Only needs to be called if the current burst profile changes.
 *
 * @param[in] bpid "Burst Profile Identifier" identifies selected profile, from adi_dm_BurstProfileSetup().
 * @return ADI_DM_SUCCESS for success, an ADI_DM_PARAMETER_ERROR if insufficient memory
 */
adi_dm_err_t adi_dm_SelectBurstProfile(uint32_t bpid);

/**
 * Issue software trigger for a single burst. Return immediately.
 *
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_Trigger(void);

/**
 * @em IN parameter to @c adi_dm_PeriodicCalibration
 *
 * @see adi_dm_PeriodicCalibration
 */
typedef struct {
    bool no_rfpll_bow_cal;      /**< Do not run ::ADI_ADAR690x_FW_RFPLL_BOW_CAL */
    bool no_lochain_cal;        /**< Do not run ::ADI_ADAR690x_FW_LOCHAIN_CAL */
    bool no_adcpll_align;       /**< Do not run ::ADI_ADAR690x_FW_ADCPLL_ALIGN */
    bool no_rxgain_cal;         /**< Do not run ::ADI_ADAR690x_FW_RXGAIN_CAL */
    bool no_adc_phase_cal;      /**< Do not run ::ADI_ADAR690x_FW_ADC_PHASE_CAL */
    bool no_pa_adj_cal;         /**< Do not run ::ADI_ADAR690x_FW_TXPA_ADJ */
    bool no_hpf_cal;            /**< Do not run ::ADI_ADAR690x_FW_HPF_CAL */
    bool run_checks;            /**< Run built-in-self-test (BIST) tasks to check for proper functioning of device.
                                 * See adi_dm_LockConfig() */
    bool run_power_checks;      /**< Run BISTs that require power detection during burst.
                                 * Needs `run_checks` to be set also. See adi_dm_PowerDetectorMeasTask()
                                 * and adi_dm_WriteSysCalTx() */
    bool run_rfpll_period_chk;  /**< Run BISTs that require adi_dm_WriteRfpllPeriod() to have been called.
                                 * Needs `run_checks` to be set also. */
} adi_dm_periodic_calibration_t;

/**
 * Perform periodic firmware (re-)calibration as recommended by @cite frm.
 *
 * @param[in] p parameters. See ::adi_dm_periodic_calibration_t.
 * @return ADI_DM_SUCCESS for success, an ADI_DM_PARAMETER_ERROR if insufficient memory
 */
adi_dm_err_t adi_dm_PeriodicCalibration(const adi_dm_periodic_calibration_t * p);

/**
 * @em IN parameter to adi_dm_RfpllReconfig()
 *
 * @see adi_dm_RfpllReconfig
 */

typedef struct {
    uint64_t ramp_start_freq_hz;    /**< Tx output frequency at start of burst */
    float ramp_bw_Mhz;              /**< Maximum ramp bandwidth */
} adi_dm_rfpll_reconfig_t;

/**
 * Reconfigure RFPLL.
 *
 * Calls the firmware calibrations recommended by @cite frm when one of
 * the ramp start frequency or ramp bandwidth is changed.
 *
 * @param[in] p parameters, See ::adi_dm_rfpll_reconfig_t.
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_RfpllReconfig(const adi_dm_rfpll_reconfig_t * p);

/**
 * Set the RFPLL lock frequency.
 *
 * Sets the ramp start frequency and calls the firmware command to set the
 * RFPLL's frequency accordingly.
 *
 * @param[in] ramp_start_freq_hz, the ramp start frequency in Hertz
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_RfpllLock(uint64_t ramp_start_freq_hz);

/**
 * Setup for checks that configuration does not change by accident.
 *
 * Must be called if checks are to be run by adi_dm_PeriodicCalibration().
 * i.e. if `run_checks` member of ::adi_dm_periodic_calibration_t is set true.
 * Must only be called after all setup is complete.
 *
 * @return ADI_DM_SUCCESS for success, an error code for errors
 *
 * @see adi_dm_UnlockConfig
 */
adi_dm_err_t adi_dm_LockConfig(void);

/**
 * Tear down for checks that configuration does not change by accident.
 *
 * Must be called after adi_dm_LockConfig() before changing configuration.
 * Note adi_dm_PeriodicCalibration() must not be called with `run_checks`
 * member of ::adi_dm_periodic_calibration_t is set true when configuration
 * is 'unlocked'.
 *
 * @return ADI_DM_SUCCESS for success, an error code for errors
 *
 * @see adi_dm_UnlockConfig
 */
adi_dm_err_t adi_dm_UnlockConfig(void);

/**@}*/

/**
 * @name Miscellaneous
 * These functions provide functionality which does not quite
 * fit into the other categories.
 */
/**@{*/

/**
 * Calculate a CRC/checksum.
 *
 * @note
 * This is not the standard IEEE CRC32 but it does do the same computation as LVDS dataport.
 *
 * @param[in] p Pointer to start of data.
 * @param[in] n Length of data.
 * @param[in] step Step to next sample in the channel in bytes. For instance 4*2 for a buffer in transmission order.
 * @return The CRC/checksum.
 */
uint32_t adi_dm_Crc32ADI(uint8_t * p, int n, int step);

/**
 * @em IN parameter to @c adi_dm_MaskFaults
 *
 * @see adi_dm_MaskFaults
 */
typedef struct {
    uint32_t fault_status0_mask;    /** Bits set correspond to faults to ignore in REG_FAULTCTL_FAULT_STATUS0. */
    uint32_t fault_status1_mask;    /** Bits set correspond to faults to ignore in REG_FAULTCTL_FAULT_STATUS1. */
    uint32_t fault_status2_mask;    /** Bits set correspond to faults to ignore in REG_FAULTCTL_FAULT_STATUS2. */
    uint32_t sw_fault0_mask;        /** Bits set correspond to faults to ignore in REG_FAULTCTL_SOFTWARE_FAULT_0. */
    uint32_t sw_fault1_mask;        /** Bits set correspond to faults to ignore in REG_FAULTCTL_SOFTWARE_FAULT_1. */
    uint32_t sw_fault2_mask;        /** Bits set correspond to faults to ignore in REG_FAULTCTL_SOFTWARE_FAULT_2. */
    uint32_t sw_fault3_mask;        /** Bits set correspond to faults to ignore in REG_FAULTCTL_SOFTWARE_FAULT_3. */
} adi_dm_mask_faults_t;

/**
 * Ignore faults triggered by hardware or software errors.
 * Faults that are not ignored may cause any driver function to return early with ADI_DM_FIRMWARE_ERROR.
 *
 * @param[in] p Input parameters.
 * @return ADI_DM_SUCCESS for success, and an error code on failure.
 */
adi_dm_err_t adi_dm_MaskFaults(adi_dm_mask_faults_t * p);

/**
 * @em IN parameter to @c adi_dm_TemperatureGet
 *
 * @see adi_dm_TemperatureGet
 */
typedef struct {
    struct {
        float tx_temp_c[ADI_DM_NUM_TX];  /** Temperature at each Tx in Celsius. */
        float rx_temp_c[ADI_DM_NUM_RX];  /** Temperature at each Rx in Celsius. */
        float lochain_temp_c;    /** Temperature at local oscillator chain in Celsius. */
    } dm[ADI_DM_NUM_DIGIMMIC];
} adi_dm_temperature_t;

/**
 * Get temperature of parts.
 *
 * @param[out] out Temperatures read from parts.
 * @return ADI_DM_SUCCESS for success, and an error code on failure.
 */
adi_dm_err_t adi_dm_TemperatureGet(adi_dm_temperature_t * out);

/**
 * Set test mode on LVDS devices. In this mode all data transmitted over the dataport
 * is replaced by a known test pattern. The rest of the part should be programmed as normal
 * and ramps triggered by calling adi_dm_Trigger() but all data transmitted will be replaced
 * by the test pattern.
 *
 * @param[in] pat The test pattern to be used. A separate 16-bit value for each channel of each device.
 * @return ADI_DM_SUCCESS for success, and an error code on failure.
 */
adi_dm_err_t adi_dm_SetLvdsTestPattern(uint16_t pat[ADI_DM_NUM_DIGIMMIC][ADI_DM_NUM_RX]);

/**
 * Unset test mode on LVDS devices.
 *
 * @return ADI_DM_SUCCESS for success, and an error code on failure.
 */
adi_dm_err_t adi_dm_ClearLvdsTestPattern(void);

/**
 * Enter low power state suitable for sleep between bursts.
 *
 * @return ADI_DM_SUCCESS for success, and an error code on failure.
 */
adi_dm_err_t adi_dm_ManualSleep(void);

/**
 * Exit the low power state suitable for sleep between bursts.
 *
 * @return ADI_DM_SUCCESS for success, and an error code on failure.
 */
adi_dm_err_t adi_dm_ManualWake(void);

/**
 * @em IN parameter to @c adi_dm_PowerDetectorMeasTask
 *
 * @see adi_dm_PowerDetectorMeasTask
 */
typedef struct {
    struct {
        /* tx_active booleans indicate that the associated channels are active at
         * some point during the burst and not necessarily on every chirp
         */
        bool tx_active[ADI_DM_NUM_TX];  /** Tx channels active during bursts for Power detector measurements. */
        unsigned tx0_inactive_when_all_inactive:1;      /* Enable TX0 coupled power detector measurement when TX1 and TX2 is inactive */
        unsigned tx0_inactive_when_tx1_active:1;        /* Enable TX0 coupled power detector measurement when TX1 is active and TX2 is inactive */
        unsigned tx0_inactive_when_tx2_active:1;        /* Enable TX0 coupled power detector measurement when TX1 is inactive and TX2 is active */
        unsigned tx0_inactive_when_tx1_tx2_active:1;    /* Enable TX0 coupled power detector measurement when both TX1 and TX2 are active */
        unsigned tx1_inactive_when_all_inactive:1;      /* Enable TX1 coupled power detector measurement when TX1 and TX2 is inactive */
        unsigned tx1_inactive_when_tx0_active:1;        /* Enable TX1 coupled power detector measurement when TX0 is active and TX2 is inactive */
        unsigned tx1_inactive_when_tx2_active:1;        /* Enable TX1 coupled power detector measurement when TX0 is inactive and TX2 is active */
        unsigned tx1_inactive_when_tx0_tx2_active:1;    /* Enable TX1 coupled power detector measurement when both TX0 and TX2 are active */
        unsigned tx2_inactive_when_all_inactive:1;      /* Enable TX2 coupled power detector measurement when TX1 and TX2 is inactive */
        unsigned tx2_inactive_when_tx0_active:1;        /* Enable TX2 coupled power detector measurement when TX1 is inactive and TX2 is active */
        unsigned tx2_inactive_when_tx1_active:1;        /* Enable TX2 coupled power detector measurement when TX1 is active and TX2 is inactive */
        unsigned tx2_inactive_when_tx0_tx1_active:1;    /* Enable TX2 coupled power detector measurement when both TX1 and TX2 are active */
    } dm[ADI_DM_NUM_DIGIMMIC];
} adi_dm_power_detector_meas_task_t;

/**
 * Configures Power Detector Measurement tasks and sets measurement for next burst.
 *
 * Must be called before trigger if power checks are to be run by adi_dm_PeriodicCalibration().
 * i.e. if `run_power_checks` member of ::adi_dm_periodic_calibration_t is set true.
 * Cannot be used with adi_dm_BuiltinMimoSetup()
 *
 * @param[in] p containing Power detector measurement configuration.
 * @return ADI_DM_SUCCESS for success, and an error code on failure.
 *
 * @see adi_dm_CalcPwrDetCfg
 */
adi_dm_err_t adi_dm_PowerDetectorMeasTask(adi_dm_power_detector_meas_task_t * p);

/**
 * Calculate power detector configuration for a burst, required by
 * BIST15: Rx chain diagnostic check,
 * BIST18: LO chain output monitor,
 * BIST19: Tx output transmit power check,
 * BIST44: Power detector rationality check,
 * BIST53: Tx isolation monitor check, and
 * BIST54: Tx output load monitor check.
 *
 * @param[in] p burst profile for which the expected count is being calculated.
 * @param[out] out rfpll_period_low_limit, rfpll_period_high_limit set to limits for the expected RFPLL period count.
 * @return ADI_DM_SUCCESS for success, and an error code on failure.
 *
 * @see adi_dm_PowerDetectorMeasTask
 */
adi_dm_err_t adi_dm_CalcPwrDetCfg(adi_dm_burst_profile_t * p, adi_dm_power_detector_meas_task_t * out);

/**
 * @em IN parameter to @c adi_dm_WriteRfpllPeriod
 * @em OUT parameter to @c adi_dm_CalcRfpllPeriod
 *
 * @see adi_dm_WriteRfpllPeriod, adi_dm_CalcRfpllPeriod
 */
typedef struct {
    uint32_t rfpll_period_low_limit; /**< Low limit for BIST103c: RFPLL period check */
    uint32_t rfpll_period_high_limit; /**< High limit for BIST103c: RFPLL period check */
} adi_dm_write_rfpll_period_t;

/**
 * Calculate expected RFPLL period count for a burst, required by BIST103c 'RFPLL period check'.
 * It is assumed this has been called if adi_dm_PeriodicCalibration() is called with
 * `run_rfpll_period_chk` member of ::adi_dm_periodic_calibration_t set true.
 *
 * @param[in] p estimated RFPLL period limits based upon current burst.
 * @return ADI_DM_SUCCESS for success, and an error code on failure.
 *
 * @see adi_dm_CalcRfpllPeriod
 */
adi_dm_err_t adi_dm_WriteRfpllPeriod(adi_dm_write_rfpll_period_t * p);

/**
 * @em IN parameter to @c adi_dm_CalcRfpllPeriod
 *
 * @see adi_dm_CalcRfpllPeriod
 */
typedef struct {
    adi_dm_burst_profile_t *burst_profile; /**< Burst for which RFPLL period is to be calculated. */
    uint64_t ramp_start_freq_hz; /**< Start frequency of burst. */
} adi_dm_calc_rfpll_period_t;

/**
 * Calculate expected RFPLL period count for a burst, required by BIST103c 'RFPLL period check'
 *
 * @param[in] p burst profile and frequency for which the expected count is being calculated.
 * @param[out] out expected limits of RFPLL period counter for this burst.
 * @return ADI_DM_SUCCESS for success, and an error code on failure.
 *
 * @see adi_dm_WriteRfpllPeriod
 */
adi_dm_err_t adi_dm_CalcRfpllPeriod(adi_dm_calc_rfpll_period_t * p, adi_dm_write_rfpll_period_t * out);

/**
 * Set system calibration mode
 *
 * Used to enable or disable system calibration mode.
 * This function should be called after adi_dm_PowerUp.
 *
 * @param[in] enable_sys_cal Boolean to enable system calibration
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_SetSysCal(bool enable_sys_cal);

#define ADI_DM_SYSCAL_TX_SIZE 24 /**< Dimension for BIST54 t0 measurements. @see adi_dm_power_up_t0_data_t */
#define ADI_DM_SYSCAL_RX_SIZE 24 /**< Dimension for BIST15 t0 measurements. @see adi_dm_power_up_t0_data_t */

/**
 * Write RX System Calibration values
 *
 * Used to write system calibration values which were obtained during system
 * calibration.
 * This function should be called after adi_dm_PowerUp.
 *
 * @param[in] in Input system calibration values
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_WriteSysCalRx(const uint8_t in[ADI_DM_NUM_DIGIMMIC][ADI_DM_SYSCAL_RX_SIZE]);

/**
 * Write TX System Calibration values
 *
 * Used to write system calibration values which were obtained during system
 * calibration.
 * This function should be called after adi_dm_PowerUp.
 *
 * @param[in] in Input system calibration values
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_WriteSysCalTx(const uint8_t in[ADI_DM_NUM_DIGIMMIC][ADI_DM_SYSCAL_TX_SIZE]);

/**
 * Read RX System Calibration values
 *
 * Used to read system calibration values obtained during system calibration.
 * Refer to system calibration example on how to use this function.
 *
 * @param[out] out Output system calibration values
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_ReadSysCalRx(uint8_t out[ADI_DM_NUM_DIGIMMIC][ADI_DM_SYSCAL_RX_SIZE]);

/**
 * Read TX System Calibration values
 *
 * Used to read system calibration values obtained during system calibration.
 * Refer to system calibration example on how to use this function.
 *
 * @param[out] out Output system calibration values
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_ReadSysCalTx(uint8_t out[ADI_DM_NUM_DIGIMMIC][ADI_DM_SYSCAL_TX_SIZE]);

/**
 * Send PWDNb interrupt
 *
 * Abort either ramp or tasklist,
 * returning as-soon-as-possible to a known state.
 *
 *  @return ADI_DM_SUCCESS for success, and an error code on failure.
 */
adi_dm_err_t adi_dm_PwndnInterrupt(void);

/**
 * Execute a tasklist
 *
 * Execute a list of firmware tasks with a single SPI command
 * and wait until execution completes.
 * The list must be in the have been added by adi_dm_TasklistPoolSetup()
 *
 * @param[in] dm_num Device on to run the tasklist. If ::ADI_DM_ALL_DIGIMMICS run on all active devices.
 * @param[in] listno Index of list in in tasklist pool.
 * @return ADI_DM_SUCCESS for success, and an error code on failure.
 * 
 * @see adi_dm_TasklistPoolSetup, adi_dm_TasklistNoBlock
 */
adi_dm_err_t adi_dm_Tasklist(adi_dm_num_t dm_num, uint8_t listno);

/**
 * Execute a tasklist without blocking
 *
 * Initiates execution a list of firmware tasks with a single SPI command
 * without waiting until execution completes.
 * The list must be in the have been added by adi_dm_TasklistPoolSetup()
 *
 * @param[in] dm_num Device on to run the tasklist. If ::ADI_DM_ALL_DIGIMMICS run on all active devices.
 * @param[in] listno Index of list in in tasklist pool.
 * @return ADI_DM_SUCCESS for success, and an error code on failure.
 *
 * @see adi_dm_TasklistPoolSetup, adi_dm_Tasklist
 */
adi_dm_err_t adi_dm_TasklistNoBlock(adi_dm_num_t dm_num, uint8_t listno);

/**
 * @em IN parameter to @c adi_dm_TasklistPoolSetup
 *
 * The @em tasklists array contains @em num_tasklists tasklists for each device.
 * The @em tasklist_length array gives the length of each tasklist on each device.
 *
 * The underlying representation of a tasklist is the machine representation:
 *
 * * A tasklist consist of a tasklist control word followed by a number of tasks.
 * * Tasklist control word is a uint32_t encoded:
 *   * bit 31: WDTOUT control
 *     * 0 does not pulse at beginning of tasklist.
 *     * 1 pulses at beginning of tasklist.
 *   * bits 30:16 reserved.
 *   * bits 15:0 number of tasks.
 * * A task is a task control word followed by a variable number of parameters
 *   and the watchdog timer window.
 *   * Task control word is a uint32_t encoded:
 *     * bit 31: WDTOUT configuration. ()
 *       * 0: no WDTOUT.
 *       * 1: pulse WDTOUT.
 *       * This bit along with 16bit task ID acts as future key for the task.
 *         Watchdog key = (task control word <<1)|(task control word >>31)
 *         If LSB of the key is set, WDTOUT is pulsed out on servicing the watchdog.
 *     * bits 30:20 reserved.
 *     * bits 19:16 number of dynamic parameter words.
 *     * bits 15:0 Task ID. The 16 cmd id defined in ::adar690x_fw.h.
 *   * params: as many uint32_t as specified in the task control word.
 *     * If no dynamic parameters are specified the parameters are read from
 *       the configuration section, othewise the right number of parameters
 *       for the task must be provided. Currently this must be deduced from
 *       examples of firmware calls with parameter in the driver.
 *   * uint32_t: Min cycles for watchdog timer
 *   * uint32_t: Max cycles for watchdog timer
 *
 * This is somewhat low level. See examples/tasklist_util.c for a more
 * abstract interface to building this data structure.
 *
 * @see adi_dm_TasklistPoolSetup
 */
typedef struct {
    uint32_t num_tasklists;         /**< Number of tasklists to setup */
    uint32_t **tasklists[ADI_DM_NUM_DIGIMMIC];  /**< Array of arrays containing tasklist in memory format. */
    uint32_t *tasklist_length[ADI_DM_NUM_DIGIMMIC];  /**< Array of arrays giving the number of words in each tasklist. */
} adi_dm_tasklist_pool_setup_t;

/**
 * Create a tasklist pool.
 *
 * Copies all tasklists down to device. Must be called after all calls to
 * adi_dm_BurstProfileSetup().
 *
 * @param[in] p Tasklists to be written to memory.
 * @param[in,out] dma_mem_limit The same conventions as adi_dm_BurstProfileSetup().
 * @return ADI_DM_SUCCESS for success, an error code for errors.
 */
adi_dm_err_t adi_dm_TasklistPoolSetup(const adi_dm_tasklist_pool_setup_t * p, uint32_t * dma_mem_limit);

/**@}*/

#ifdef __cplusplus
}
#endif

#endif                          /* __ADI_DMDRIVER_H__ */
