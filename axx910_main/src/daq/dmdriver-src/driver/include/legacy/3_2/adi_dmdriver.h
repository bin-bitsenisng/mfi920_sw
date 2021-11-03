/* adi_dmdriver_3_2.h
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

#ifndef ADI_DMDRIVER_3_2_H__
#define ADI_DMDRIVER_3_2_H__

#include <legacy/3_3/adi_dmdriver.h>
#include <legacy/3_3_3/adi_dmdriver.h>

/**
 * Write a word to the DigiMMIC address space.
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
 */
static inline void adi_dm_3_2_Write(adi_dm_num_t dm_num, uint32_t addr, uint32_t value)
{
    adi_dm_err_t res = adi_dm_Write(dm_num, addr, value);
    if (res != 0)
        adi_dm_Log("ERROR: adi_dm_3_2_Write res = %d\n", res);
}

/**
 * Read a word from the DigiMMIC address space.
 *
 * Access to SPI registers is supported by special rules for addresses in the
 * range 0 to 255. If the address is in the range 0 to 255 a byte is read from
 * the address over SPI and zero extended before assigning to value. Otherwise
 * the address must be modulo 4, 4-bytes are read over SPI and assigned to value.
 *
 * @param[in] dm_num DigiMMIC to read from. @c dm_num may not be ADI_DM_ALL_DIGIMMICS.
 * @param[in] addr Address to read from in the DigiMMIC address space.
 * @returns The 32-bit value read.
 */
static inline uint32_t adi_dm_3_2_Read(adi_dm_num_t dm_num, uint32_t addr)
{
    uint32_t value = 0xcccccccc;
    adi_dm_err_t res = adi_dm_Read(dm_num, addr, &value);
    if (res != 0)
        adi_dm_Log("ERROR: adi_dm_3_2_Read res = %d\n", res);
    return value;
}

/**
 * Read, modify, write a word in the DigiMMIC address space.
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
 */
static inline void adi_dm_3_2_RMW(adi_dm_num_t dm_num, uint32_t addr, uint32_t mask, uint32_t bits)
{
    adi_dm_err_t res = adi_dm_RMW(dm_num, addr, mask, bits);
    if (res != 0)
        adi_dm_Log("ERROR: adi_dm_3_2_RMR res = %d\n", res);
}

/**
 * Write a memory region in the DigiMMIC address space.
 *
 * @param[in] dm_num DigiMMIC to write to. If @c dm_num is ADI_DM_ALL_DIGIMMICS, a write is broadcast to all DigiMMICs.
 * @param[in] addr Address to write to in the DigiMMIC address space.
 * @param[in] sz Size of block written the DigiMMICs. Must be a multiple of 4 bytes.
 * @param[in] data Block of data written to the DigiMMICs.
 */
static inline void adi_dm_3_2_BlockWrite(adi_dm_num_t dm_num, uint32_t addr, size_t sz, const void *data)
{
    adi_dm_err_t res = adi_dm_BlockWrite(dm_num, addr, sz, data);
    if (res != 0)
        adi_dm_Log("ERROR: adi_dm_3_2_BlockWrite res = %d\n", res);
}

/**
 *  Read a memory region in the DigiMMIC address space.
 *
 * @param[in] dm_num DigiMMIC to read from. @c dm_num may not be ADI_DM_ALL_DIGIMMICS.
 * @param[in] addr Address to read fromin the DigiMMIC address space.
 * @param[in] sz Size of block to read from the DigiMMIC. Must be a multiple of 4 bytes.
 * @param[in] data Block of data read from the DigiMMIC.
 */
static inline void adi_dm_3_2_BlockRead(adi_dm_num_t dm_num, uint32_t addr, size_t sz, void *data)
{
    adi_dm_err_t res = adi_dm_BlockRead(dm_num, addr, sz, data);
    if (res != 0)
        adi_dm_Log("ERROR: adi_dm_3_2_BlockRead res = %d\n", res);
}

/**
 * Write uint64_t to the DigiMMIC address space.
 *
 * @param[in] dm_num DigiMMIC to write to. If @c dm_num is ADI_DM_ALL_DIGIMMICS, a write is broadcast to all DigiMMICs.
 * @param[in] addr Address to write to in the DigiMMIC address space.
 * @param[in] value 64-bit unsigned integer value to write.
 */
static inline void adi_dm_3_2_WriteU64(adi_dm_num_t dm_num, uint32_t addr, uint64_t value)
{
    uint32_t block[2];
    block[0] = (uint32_t) (value >> 0);
    block[1] = (uint32_t) (value >> 32);
    adi_dm_3_2_BlockWrite(dm_num, addr, 8, block);
}

/**
 * Write float to the DigiMMIC address space.
 *
 * @param[in] dm_num DigiMMIC to write to. If @c dm_num is ADI_DM_ALL_DIGIMMICS, a write is broadcast to all DigiMMICs.
 * @param[in] addr Address to write to in the DigiMMIC address space.
 * @param[in] value The 32-bit floating-point value to write.
 */
static inline void adi_dm_3_2_WriteF32(adi_dm_num_t dm_num, uint32_t addr, float value)
{
    adi_dm_3_2_Write(dm_num, addr, *(uint32_t *) & value);
}

/**
 * Read float from the DigiMMIC address space.
 *
 * @param[in] dm_num DigiMMIC to read from. @c dm_num may not be ADI_DM_ALL_DIGIMMICS.
 * @param[in] addr Address to read from in the DigiMMIC address space.
 * @returns The 32-bit floating-point value read.
 */
static inline float adi_dm_3_2_ReadF32(adi_dm_num_t dm_num, uint32_t addr)
{
    uint32_t u32 = adi_dm_3_2_Read(dm_num, addr);
    float value = *(float *) &u32;
    return value;
}

/**
 * Read uint64_t value from the DigiMMIC address space.
 *
 * @param[in] dm_num DigiMMIC to read from. @c dm_num may not be ADI_DM_ALL_DIGIMMICS.
 * @param[in] addr Address to read from in the DigiMMIC address space.
 * @returns The 64-bit unsigned integer value read.
 */
static inline uint64_t adi_dm_3_2_ReadU64(adi_dm_num_t dm_num, uint32_t addr)
{
    uint32_t block[2];
    adi_dm_3_2_BlockRead(dm_num, addr, 8, &block);
    uint64_t result = block[1];
    result <<= 32;
    result |= block[0];
    return result;
}

/**
 * Read double from the DigiMMIC address space
 *
 * @param[in] dm_num DigiMMIC to read from. @c dm_num may not be ADI_DM_ALL_DIGIMMICS.
 * @param[in] addr Address to read from in the DigiMMIC address space.
 * @returns The 64-bit floating-point value read.
 */
static inline double adi_dm_3_2_ReadF64(adi_dm_num_t dm_num, uint32_t addr)
{
    uint64_t u64 = adi_dm_3_2_ReadU64(dm_num, addr);
    double value = *(double *) &u64;
    return value;
}

/**
 * Write double to the DigiMMIC address space.
 *
 * @param[in] dm_num DigiMMIC to write to. If @c dm_num is ADI_DM_ALL_DIGIMMICS, a write is broadcast to all DigiMMICs.
 * @param[in] addr Address to write to in the DigiMMIC address space.
 * @param[in] value The 64-bit floating-point value to write.
 */
static inline void adi_dm_3_2_WriteF64(adi_dm_num_t dm_num, uint32_t addr, double value)
{
    adi_dm_3_2_WriteU64(dm_num, addr, *(uint64_t *) & value);
}

/**
 * @em IN parameter to @c adi_dm_3_2_LvdsSetup
 *
 * @see adi_dm_3_2_LvdsSetup
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
        unsigned device_enum_id:6;      /**< Appears in status field of all channels. See "LVDS Data Frame Content" in @cite hrm. */

        uint8_t dataid0;            /**< Appears in rx0 dataid field. See "Data ID and Byte Count" in "LVDS Data Frame Content" in @cite hrm. */
        uint8_t dataid1;            /**< Appears in rx1 dataid field. See "Data ID and Byte Count" in "LVDS Data Frame Content" in @cite hrm. */
        uint8_t dataid2;            /**< Appears in rx2 dataid field. See "Data ID and Byte Count" in "LVDS Data Frame Content" in @cite hrm. */
        uint8_t dataid3;            /**< Appears in rx3 dataid field. See "Data ID and Byte Count" in "LVDS Data Frame Content" in @cite hrm. */
    } dm[ADI_DM_NUM_DIGIMMIC];
} adi_dm_3_2_lvds_setup_t;

/**
 * Dataport configuration for LVDS parts.
 *
 * @param[in] p parameters. See ::adi_dm_lvds_setup_t
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_3_2_LvdsSetup(const adi_dm_3_2_lvds_setup_t * p);


/**
 * @em IN parameter to @c adi_dm_3_2_MipiSetup
 *
 * @see adi_dm_3_2_MipiSetup
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
        uint8_t userval0;           /**< Appears in rx0 status field. See "Status Data" in "LVDS Data Frame Content" in @cite hrm. */
        uint8_t userval1;           /**< Appears in rx1 status field. See "Status Data" in "LVDS Data Frame Content" in @cite hrm. */
        uint8_t userval2;           /**< Appears in rx2 status field. See "Status Data" in "LVDS Data Frame Content" in @cite hrm. */
        uint8_t userval3;           /**< Appears in rx3 status field. See "Status Data" in "LVDS Data Frame Content" in @cite hrm. */
        unsigned device_enum_id:6;      /**< Appears in status field of all channels. See "LVDS Data Frame Content" in @cite hrm. */
    } dm[ADI_DM_NUM_DIGIMMIC];
} adi_dm_3_2_mipi_setup_t;

/**
 * Dataport configuration for MIPI parts.
 *
 * @param[in] p parameters. See ::adi_dm_mipi_setup_t
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_3_2_MipiSetup(const adi_dm_3_2_mipi_setup_t * p);

/* Defines to including this header links to legacy functions.
 */
#ifndef ADI_DM_NO_LEGACY_REDEF

#define adi_dm_Write adi_dm_3_2_Write
#define adi_dm_Read adi_dm_3_2_Read
#define adi_dm_RMW adi_dm_3_2_RMW
#define adi_dm_BlockWrite adi_dm_3_2_BlockWrite
#define adi_dm_BlockRead adi_dm_3_2_BlockRead
#define adi_dm_WriteU64 adi_dm_3_2_WriteU64
#define adi_dm_WriteF32 adi_dm_3_2_WriteF32
#define adi_dm_ReadF32 adi_dm_3_2_ReadF32
#define adi_dm_ReadU64 adi_dm_3_2_ReadU64
#define adi_dm_ReadF64 adi_dm_3_2_ReadF64
#define adi_dm_WriteF64 adi_dm_3_2_WriteF64
#define adi_dm_lvds_setup_t adi_dm_3_2_lvds_setup_t
#define adi_dm_LvdsSetup adi_dm_3_2_LvdsSetup
#define adi_dm_mipi_setup_t adi_dm_3_2_mipi_setup_t
#define adi_dm_MipiSetup adi_dm_3_2_MipiSetup

#endif

#endif                          /* ADI_DMDRIVER_3_0_H__ */
