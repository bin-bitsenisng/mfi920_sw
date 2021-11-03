/* localdefs.h
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
 * @note
 * This is a private header file.
 * You should not depend on it.
 * Details may change without notice in future releases.
 */

#ifndef __LOCALDEFS_H__
#define __LOCALDEFS_H__

#include "adar690x_fw.h"

#define ARRAY_SIZE(x) (sizeof(x)) / sizeof((x[0]))

#ifdef __SILENT
#define comment(...)
#else
#define comment(...) adi_dm_Log( __VA_ARGS__ )
#endif

#define SAWTOOTH_PGA_SHUNT_TRAIL_DEL 0.1F

#define DMA_AREA_HEADER_SIZE 0x6CUL
#define DMA_MEMORY_START (ADI_ADAR690x_DMA_AREA_BASE+DMA_AREA_HEADER_SIZE)
#define DMA_MEMORY_SIZE (ADI_ADAR690x_DMA_AREA_SIZE-DMA_AREA_HEADER_SIZE)
#define DMA_WORD_SIZE 4
#define DMA_CHAN_CTRL_SIZE (4 * DMA_WORD_SIZE)
#define DMA_RAMP_PROFILE_SIZE (9 * DMA_WORD_SIZE)
#define DMA_RAMPGEN_CHAN_NO 0
#define DMA_RAMPGEN_CHAN_SRC_PTR (ADI_ADAR690x_DMA_BASE_POINTER + DMA_RAMPGEN_CHAN_NO * 16)

#define UDMA_CTRL_CFG_DSTINC_WORD 0x80000000
#define UDMA_CTRL_CFG_DSTINC_NOINCR 0xC0000000
#define UDMA_CTRL_CFG_SRCINC_WORD 0x08000000
#define UDMA_CTRL_CFG_SRCINC_NOINCR 0x0C000000
#define UDMA_CTRL_CFG_SRC_SIZE_WORD 0x02000000
#define UDMA_CTRL_CFG_R_POWER_X1 (0 << 14)
#define UDMA_CTRL_CFG_R_POWER_X4 (2 << 14)
#define UDMA_CTRL_CFG_R_POWER_X8 (3 << 14)
#define UDMA_CTRL_CFG_R_POWER_X16 (4 << 14)
#define UDMA_CTRL_CFG_R_POWER_X32 (5 << 14)
#define UDMA_CTRL_CFG_TRANSFERS(x) (((x)-1)<<4)
#define UDMA_CTRL_CFG_CYC_CTRL_BASIC 0x00000001
#define UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_PRI  0x00000004
#define UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_ALT  0x00000005

/*
 * Use the very pessimistic timeout of 2 seconds for all adi_dm_WaitGPIO calls.
 */
#define TIMEOUT 2000000000UL

/**
 * Write ramp_config registers.
 *
 * @param[in] p parameters. See ::adi_dm_ramp_config_t.
 * @param[in] builtin_mimo additional parameters for builtin mimo mode. NULL if not in that mode.
 * @return ADI_DM_SUCCESS for success, an error code for errors
 */
adi_dm_err_t adi_dm_ramp_config(const adi_dm_ramp_config_t * p, const adi_dm_builtin_mimo_setup_t * builtin_mimo);

/**
* Enables Power Detector Measurement task for next burst.
*
* @return ADI_DM_SUCCESS for success, and an error code on failure.
*/
adi_dm_err_t adi_dm_power_detector_enable();

/**
* Measures Power Detector Measurement offsets.
*
* @return ADI_DM_SUCCESS for success, and an error code on failure.
*/
adi_dm_err_t adi_dm_power_detector_offset();

/**
* Clears Power Detector Measurement values.
*
* @return ADI_DM_SUCCESS for success, and an error code on failure.
*/
adi_dm_err_t adi_dm_power_detector_clear();

/** Reset the shadow copy of dm_num state to initial values */
void adi_dm_reset_shadow_state(adi_dm_num_t dm_num);

/** Initialize connection to dm_num */
adi_dm_err_t adi_dm_init_spi_connection(adi_dm_num_t dm_num, bool disable_crc);

/** get local spi read frame count */
uint16_t adi_dm_local_spi_reads(adi_dm_num_t dm_num);
/** get local spi write frame count */
uint16_t adi_dm_local_spi_writes(adi_dm_num_t dm_num);
/** set local spi write and read frame count to 0 */
void adi_dm_reset_local_spi_counters(adi_dm_num_t dm_num);
/** read local SPI CRC poly and init values */
void adi_dm_get_local_spi_crc_poly(adi_dm_num_t dm_num, uint16_t * crc_poly, uint16_t * crc_seed);
/** change local SPI CRC poly and init values */
void adi_dm_set_local_spi_crc_poly(adi_dm_num_t dm_num, uint16_t crc_poly, uint16_t crc_seed);
/* compute SPI crc - only global for access from example */
void adi_dm_spi_crc(uint8_t slave, uint8_t * data, int_fast16_t * plen);

/** Check the diver's count of SPI frames against the device's */
adi_dm_err_t adi_dm_spi_counter_check(void);

typedef struct {
    float absolute;
    float max_tx_change_c;
    float max_rx_change_c;
    float max_rx_change2_c;
    float max_lochain_change_c;
} adi_dm_temp_change_t;

typedef struct {
    float baseline_tx_temp_c;
    float baseline_rx_temp_c;
    float baseline_rx_temp2_c;
    float baseline_lochain_temp_c;
} adi_dm_saved_temp_t;

/** read temperature values from firmware status table without  */
adi_dm_err_t adi_dm_read_temps(adi_dm_saved_temp_t * out);

/** get maximum changes in temperature since last baseline */
adi_dm_err_t adi_dm_get_temp_change(adi_dm_temp_change_t * out);

/** save tx temperatures as new baseline */
adi_dm_err_t adi_dm_baseline_tx_change(adi_dm_temp_change_t * in);

/** save rx temperatures as new baseline */
adi_dm_err_t adi_dm_baseline_rx_change(adi_dm_temp_change_t * in);

/** save rx temperatures as new baseline in second cache */
adi_dm_err_t adi_dm_baseline_rx_change2(adi_dm_temp_change_t * in);

/** save lochain temperatures as new baseline */
adi_dm_err_t adi_dm_baseline_lochain_change(adi_dm_temp_change_t * in);

/** perform comparisons between devices for BIST19 on cacaded devices */
adi_dm_err_t adi_dm_cascaded_tx_pwr_chk(void);

/** non-blocking firmware call */
adi_dm_err_t adi_dm_call_fw_no_block(adi_dm_num_t dm_num, size_t sz, const void *data, int *start_out, int *finish_out);

/** global containing old temperatures used and updated by baseline functions */
extern adi_dm_saved_temp_t adi_dm_saved_temps;

/** globals containing saved ramp frequencies */
extern uint64_t adi_dm_saved_max_ramp_freq_hz;
extern uint64_t adi_dm_saved_ramp_start_freq_hz;
extern int64_t adi_dm_saved_ramp_bw_hz;

/**
 * Function to help decode a bpid. For debug mainly.
 */
adi_dm_err_t adi_dm_decode_bpid(uint32_t bpid, uint32_t * ramp_profiles, uint32_t * num_ramp_profiles, uint32_t * tx_overlay, uint32_t * tx_overlay_len);

/* standard set of blocks to power down when sleeping or when powered down */
#define POWER_BLOCKS \
        (ADI_ADAR690x_BITM_POWER_RX0 \
        | ADI_ADAR690x_BITM_POWER_RX1 \
        | ADI_ADAR690x_BITM_POWER_RX2 \
        | ADI_ADAR690x_BITM_POWER_RX3 \
        | ADI_ADAR690x_BITM_POWER_AFE0 \
        | ADI_ADAR690x_BITM_POWER_AFE1 \
        | ADI_ADAR690x_BITM_POWER_AFE2 \
        | ADI_ADAR690x_BITM_POWER_AFE3 \
        | ADI_ADAR690x_BITM_POWER_TX0 \
        | ADI_ADAR690x_BITM_POWER_TX1 \
        | ADI_ADAR690x_BITM_POWER_TX2 \
        | ADI_ADAR690x_BITM_POWER_RFPLL \
        | ADI_ADAR690x_BITM_POWER_LO \
        | ADI_ADAR690x_BITM_POWER_LOAMP \
        | ADI_ADAR690x_BITM_POWER_AUXADC)

extern bool adi_dm_call_fw_adcpll_align;
extern bool adi_dm_call_fw_rfpll_bow_cal;
extern bool adi_dm_call_fw_lochain_cal;
extern bool adi_dm_call_fw_flash_adc_cal;
extern bool adi_dm_call_fw_adc_phase_cal;
extern bool adi_dm_call_fw_hpf_cal;
extern bool adi_dm_call_fw_pga_cal;
extern bool adi_dm_call_fw_pwr_sup_chk;
extern bool adi_dm_call_fw_tx_pwr_chk;
extern bool adi_dm_call_fw_aux_diag_chk;
extern bool adi_dm_call_fw_rxgain_cal;
extern bool adi_dm_call_fw_txpa_cal;
extern bool adi_dm_call_fw_txpa_adj;
extern bool adi_dm_check_fw_config;
extern bool adi_dm_check_spi_counters;
extern bool adi_dm_check_rom_crc;
extern bool adi_dm_check_ram_crc;
extern bool adi_dm_call_fw_rx_baseband_chk;
extern bool adi_dm_check_fabric_crc;
extern bool adi_dm_check_adcpll;
extern bool adi_dm_check_rfpll;
extern bool adi_dm_call_fw_tx_output_load_monitor_chk;
extern bool adi_dm_call_fw_rx_baseband_latent_chk;
extern bool adi_dm_call_fw_rx_filter_chk;
extern bool adi_dm_check_spi_crc;
extern bool adi_dm_rx_overflow_chk;
extern bool adi_dm_call_fw_tx_isolation_monitor_chk;
extern bool adi_dm_call_fw_pwr_det_rat_chk;
extern bool adi_dm_call_fw_rxchain_diag_chk;
extern bool adi_dm_call_fw_time_comp_en_chk;
extern bool adi_dm_call_fw_rfpll_period_chk;
extern bool adi_dm_wdt_chk_enable;
extern bool adi_dm_enable_trigger_pin;
extern bool adi_dm_enable_trigger_pin_on_program;

/**@}*/
#endif                          /* __LOCALDEFS_H__ */
