/* adar690x_fw.h
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
 * Public C interface to the firmware
 */

#ifndef __ADAR690X_FW_H__
#define __ADAR690X_FW_H__

/* constants based on FRM 1.3 and Firmware T_3_3_A */
/* Commands: cannot be run as tasks */
#define ADI_ADAR690x_CMD_CONFIG_COMPLETE 0xF001 /**< Install/uninstall scheduler configuration file */
#define ADI_ADAR690x_CMD_TASKLIST 0xF003 /**< Execute a tasklist from scheduler file */

/* Table 1 from FRM */
#define ADI_ADAR690x_FW_BOOTPARSE 0x101 /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_ADCPLL_INIT 0x201 /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_ADCPLL_MUX_OUT 0x203 /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_RFPLL_INIT 0x301 /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_RFPLL_MUX_OUT 0x303 /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_RFPLL_LOCK 0x304 /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_RAMP_TRIG 0x30A /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_CHIP_INIT 0xF01 /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_TEMP_MEASURE 0x1001 /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_CAL_READ 0x1101 /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_ADCPLL_ALIGN 0x1501 /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_POWER_MANAGE 0x1701 /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_RMW 0x1901 /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_MEAS_PWR_DET 0x1E01 /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_MEAS_PWR_DET_OFF 0x1E02 /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_MEAS_PWR_DET_CLR 0x1E03 /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_EXT_TRIG_EN 0x1F01 /**< See Table 1 in @cite frm. */
#define ADI_ADAR690x_FW_EXT_TRIG_DIS 0x1F02 /**< See Table 1 in @cite frm. */

/* Table 2 from FRM */
#define ADI_ADAR690x_FW_RFPLL_BOW_CAL 0x307 /**< See Table 2 in @cite frm. */
#define ADI_ADAR690x_FW_RFPLL_RAMP_SETUP 0x30C /**< See Table 2 in @cite frm. */
#define ADI_ADAR690x_FW_LOCHAIN_CAL 0x602 /**< See Table 2 in @cite frm. */
#define ADI_ADAR690x_FW_FLASH_ADC_CAL 0x705 /**< See Table 2 in @cite frm. */
#define ADI_ADAR690x_FW_HPF_CAL 0x805 /**< See Table 2 in @cite frm. */
#define ADI_ADAR690x_FW_HPF_CAL_SINGLE_CHAN 0x806 /**< Undocumented internal function. */
#define ADI_ADAR690x_FW_ADC_PHASE_CAL 0xA05 /**< See Table 2 in @cite frm. */
#define ADI_ADAR690x_FW_PGA_CAL 0xB05 /**< See Table 2 in @cite frm. */
#define ADI_ADAR690x_FW_TXPA_CAL 0xC01 /**< See Table 2 in @cite frm. */
#define ADI_ADAR690x_FW_TXPA_ADJ 0xC02 /**< See Table 2 in @cite frm. */
#define ADI_ADAR690x_FW_RXGAIN_CAL 0x1801 /**< See Table 2 in @cite frm. */

/* Table 3 from FRM */
#define ADI_ADAR690x_FW_PWR_SUP_CHK 0xD01 /**< See Table 3 in @cite frm. */
#define ADI_ADAR690x_FW_CRC_CHK 0xD02 /**< See Table 3 in @cite frm. */
#define ADI_ADAR690x_FW_RX_BASEBAND_CHK  0xD03 /**< See Table 3 in @cite frm. */
#define ADI_ADAR690x_FW_RX_CHAIN_CHK 0xD04 /**< See Table 3 in @cite frm. */
#define ADI_ADAR690x_FW_TX_PWR_CHK 0xD06 /**< See Table 3 in @cite frm. */
#define ADI_ADAR690x_FW_AUXADC_DIAG_CHK 0xD07 /**< See Table 3 in @cite frm. */
#define ADI_ADAR690x_FW_PWR_DET_FAULT_CHK 0xD0B /**< See Table 3 in @cite frm. */
#define ADI_ADAR690x_FW_TX_ISOL_CHK 0xD0E /**< See Table 3 in @cite frm. */
#define ADI_ADAR690x_FW_TX_LOAD_CHK 0xD0F /**< See Table 3 in @cite frm. */
#define ADI_ADAR690x_FW_RX_BASEBAND_LATENT_CHK 0xD12 /**< See Table 3 in @cite frm. */
#define ADI_ADAR690x_FW_ADCPLL_CHK 0xD13 /**< See Table 3 in @cite frm. */
#define ADI_ADAR690x_FW_RFPLL_CHK 0xD14 /**< See Table 3 in @cite frm. */
#define ADI_ADAR690x_FW_CRC_CALC_CHK 0xD15 /**< See Table 3 in @cite frm. */
#define ADI_ADAR690x_FW_RX_FILTER_CHK 0xD16 /**< See Table 3 in @cite frm. */
#define ADI_ADAR690x_FW_RX_OVERFLOW_CHK 0xD17 /**< See Table 3 in @cite frm. */
#define ADI_ADAR690x_FW_RFPLL_PERIOD_CHK 0xD19 /**< See Table 3 in @cite frm. */

/* Cycle times */
#define ADI_ADAR690x_MINCYC_BOOTPARSE 226170 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_BOOTPARSE */
#define ADI_ADAR690x_MAXCYC_BOOTPARSE 226170 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_BOOTPARSE */
#define ADI_ADAR690x_MINCYC_ADCPLL_INIT 347774 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_ADCPLL_INIT */
#define ADI_ADAR690x_MAXCYC_ADCPLL_INIT 7784856 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_ADCPLL_INIT */
#define ADI_ADAR690x_MINCYC_ADCPLL_MUX_OUT 1685 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_ADCPLL_MUX_OUT */
#define ADI_ADAR690x_MAXCYC_ADCPLL_MUX_OUT 1693 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_ADCPLL_MUX_OUT */
#define ADI_ADAR690x_MINCYC_RFPLL_INIT 388013 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_RFPLL_INIT */
#define ADI_ADAR690x_MAXCYC_RFPLL_INIT 8260402 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_RFPLL_INIT */
#define ADI_ADAR690x_MINCYC_RFPLL_MUX_OUT 1704 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_RFPLL_MUX_OUT */
#define ADI_ADAR690x_MAXCYC_RFPLL_MUX_OUT 1713 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_RFPLL_MUX_OUT */
#define ADI_ADAR690x_MINCYC_RFPLL_LOCK 45935 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_RFPLL_LOCK */
#define ADI_ADAR690x_MAXCYC_RFPLL_LOCK 88802 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_RFPLL_LOCK */
#define ADI_ADAR690x_MINCYC_RAMP_TRIG 1571 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_RAMP_TRIG */
#define ADI_ADAR690x_MAXCYC_RAMP_TRIG 1571 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_RAMP_TRIG */
#define ADI_ADAR690x_MINCYC_CHIP_INIT 222952 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_CHIP_INIT */
#define ADI_ADAR690x_MAXCYC_CHIP_INIT 222952 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_CHIP_INIT */
#define ADI_ADAR690x_MINCYC_TEMP_MEASURE 55328 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_TEMP_MEASURE */
#define ADI_ADAR690x_MAXCYC_TEMP_MEASURE 55328 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_TEMP_MEASURE */
#define ADI_ADAR690x_MINCYC_CAL_READ 37766 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_CAL_READ */
#define ADI_ADAR690x_MAXCYC_CAL_READ 37766 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_CAL_READ */
#define ADI_ADAR690x_MINCYC_ADCPLL_ALIGN 0 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_ADCPLL_ALIGN */
#define ADI_ADAR690x_MAXCYC_ADCPLL_ALIGN 0 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_ADCPLL_ALIGN */
#define ADI_ADAR690x_MINCYC_POWER_MANAGE 228479 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_POWER_MANAGE */
#define ADI_ADAR690x_MAXCYC_POWER_MANAGE 228479 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_POWER_MANAGE */
#define ADI_ADAR690x_MINCYC_RMW 1650 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_RMW */
#define ADI_ADAR690x_MAXCYC_RMW 1650 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_RMW */
#define ADI_ADAR690x_MINCYC_MEAS_PWR_DET 0 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_MEAS_PWR_DET */
#define ADI_ADAR690x_MAXCYC_MEAS_PWR_DET 0 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_MEAS_PWR_DET */
#define ADI_ADAR690x_MINCYC_MEAS_PWR_DET_OFF 50624 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_MEAS_PWR_DET_OFF */
#define ADI_ADAR690x_MAXCYC_MEAS_PWR_DET_OFF 50624 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_MEAS_PWR_DET_OFF */
#define ADI_ADAR690x_MINCYC_MEAS_PWR_DET_CLR 1988 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_MEAS_PWR_DET_CLR */
#define ADI_ADAR690x_MAXCYC_MEAS_PWR_DET_CLR 1988 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_MEAS_PWR_DET_CLR */
#define ADI_ADAR690x_MINCYC_EXT_TRIG_EN 2277 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_EXT_TRIG_EN */
#define ADI_ADAR690x_MAXCYC_EXT_TRIG_EN 2277 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_EXT_TRIG_EN */
#define ADI_ADAR690x_MINCYC_EXT_TRIG_DIS 2277 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_EXT_TRIG_DIS */
#define ADI_ADAR690x_MAXCYC_EXT_TRIG_DIS 2277 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_EXT_TRIG_DIS */
#define ADI_ADAR690x_MINCYC_RFPLL_BOW_CAL 69353 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_RFPLL_BOW_CAL */
#define ADI_ADAR690x_MAXCYC_RFPLL_BOW_CAL 111609 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_RFPLL_BOW_CAL */
#define ADI_ADAR690x_MINCYC_RFPLL_RAMP_SETUP 187343 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_RFPLL_RAMP_SETUP */
#define ADI_ADAR690x_MAXCYC_RFPLL_RAMP_SETUP 382398 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_RFPLL_RAMP_SETUP */
#define ADI_ADAR690x_MINCYC_LOCHAIN_CAL 375766 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_LOCHAIN_CAL */
#define ADI_ADAR690x_MAXCYC_LOCHAIN_CAL 375766 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_LOCHAIN_CAL */
#define ADI_ADAR690x_MINCYC_FLASH_ADC_CAL 173965 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_FLASH_ADC_CAL */
#define ADI_ADAR690x_MAXCYC_FLASH_ADC_CAL 173965 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_FLASH_ADC_CAL */
#define ADI_ADAR690x_MINCYC_HPF_CAL 223669 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_HPF_CAL */
#define ADI_ADAR690x_MAXCYC_HPF_CAL 384914 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_HPF_CAL */
#define ADI_ADAR690x_MINCYC_HPF_CAL_SINGLE_CHAN 0 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_HPF_CAL_SINGLE_CHAN */
#define ADI_ADAR690x_MAXCYC_HPF_CAL_SINGLE_CHAN 0 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_HPF_CAL_SINGLE_CHAN */
#define ADI_ADAR690x_MINCYC_ADC_PHASE_CAL 175759 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_ADC_PHASE_CAL */
#define ADI_ADAR690x_MAXCYC_ADC_PHASE_CAL 175759 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_ADC_PHASE_CAL */
#define ADI_ADAR690x_MINCYC_PGA_CAL 28941 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_PGA_CAL */
#define ADI_ADAR690x_MAXCYC_PGA_CAL 28941 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_PGA_CAL */
#define ADI_ADAR690x_MINCYC_TXPA_CAL 438563 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_TXPA_CAL */
#define ADI_ADAR690x_MAXCYC_TXPA_CAL 438563 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_TXPA_CAL */
#define ADI_ADAR690x_MINCYC_TXPA_ADJ 438563 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_TXPA_ADJ */
#define ADI_ADAR690x_MAXCYC_TXPA_ADJ 438563 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_TXPA_ADJ */
#define ADI_ADAR690x_MINCYC_RXGAIN_CAL 1962 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_RXGAIN_CAL */
#define ADI_ADAR690x_MAXCYC_RXGAIN_CAL 1962 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_RXGAIN_CAL */
#define ADI_ADAR690x_MINCYC_PWR_SUP_CHK 5341 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_PWR_SUP_CHK */
#define ADI_ADAR690x_MAXCYC_PWR_SUP_CHK 74929 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_PWR_SUP_CHK */
#define ADI_ADAR690x_MINCYC_CRC_CHK 800 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_CRC_CHK */
#define ADI_ADAR690x_MAXCYC_CRC_CHK 400550 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_CRC_CHK */
#define ADI_ADAR690x_MINCYC_RX_BASEBAND_CHK  701027 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_RX_BASEBAND_CHK  */
#define ADI_ADAR690x_MAXCYC_RX_BASEBAND_CHK  798531 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_RX_BASEBAND_CHK  */
#define ADI_ADAR690x_MINCYC_RX_CHAIN_CHK 430846 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_RX_CHAIN_CHK */
#define ADI_ADAR690x_MAXCYC_RX_CHAIN_CHK 527713 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_RX_CHAIN_CHK */
#define ADI_ADAR690x_MINCYC_TX_PWR_CHK 35780 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_TX_PWR_CHK */
#define ADI_ADAR690x_MAXCYC_TX_PWR_CHK 35780 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_TX_PWR_CHK */
#define ADI_ADAR690x_MINCYC_AUXADC_DIAG_CHK 9283 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_AUXADC_DIAG_CHK */
#define ADI_ADAR690x_MAXCYC_AUXADC_DIAG_CHK 9283 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_AUXADC_DIAG_CHK */
#define ADI_ADAR690x_MINCYC_PWR_DET_FAULT_CHK 20799 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_PWR_DET_FAULT_CHK */
#define ADI_ADAR690x_MAXCYC_PWR_DET_FAULT_CHK 20799 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_PWR_DET_FAULT_CHK */
#define ADI_ADAR690x_MINCYC_TX_ISOL_CHK 26608 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_TX_ISOL_CHK */
#define ADI_ADAR690x_MAXCYC_TX_ISOL_CHK 26608 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_TX_ISOL_CHK */
#define ADI_ADAR690x_MINCYC_TX_LOAD_CHK 55730 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_TX_LOAD_CHK */
#define ADI_ADAR690x_MAXCYC_TX_LOAD_CHK 55730 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_TX_LOAD_CHK */
#define ADI_ADAR690x_MINCYC_RX_BASEBAND_LATENT_CHK 353504 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_RX_BASEBAND_LATENT_CHK */
#define ADI_ADAR690x_MAXCYC_RX_BASEBAND_LATENT_CHK 353504 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_RX_BASEBAND_LATENT_CHK */
#define ADI_ADAR690x_MINCYC_ADCPLL_CHK 202665 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_ADCPLL_CHK */
#define ADI_ADAR690x_MAXCYC_ADCPLL_CHK 202665 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_ADCPLL_CHK */
#define ADI_ADAR690x_MINCYC_RFPLL_CHK 219808 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_RFPLL_CHK */
#define ADI_ADAR690x_MAXCYC_RFPLL_CHK 219808 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_RFPLL_CHK */
#define ADI_ADAR690x_MINCYC_CRC_CALC_CHK 475 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_CRC_CALC_CHK */
#define ADI_ADAR690x_MAXCYC_CRC_CALC_CHK 475 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_CRC_CALC_CHK */
#define ADI_ADAR690x_MINCYC_RX_FILTER_CHK 7078 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_RX_FILTER_CHK */
#define ADI_ADAR690x_MAXCYC_RX_FILTER_CHK 7078 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_RX_FILTER_CHK */
#define ADI_ADAR690x_MINCYC_RX_OVERFLOW_CHK 248 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_RX_OVERFLOW_CHK */
#define ADI_ADAR690x_MAXCYC_RX_OVERFLOW_CHK 248 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_RX_OVERFLOW_CHK */
#define ADI_ADAR690x_MINCYC_RFPLL_PERIOD_CHK 238 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_RFPLL_PERIOD_CHK */
#define ADI_ADAR690x_MAXCYC_RFPLL_PERIOD_CHK 238 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_RFPLL_PERIOD_CHK */
#define ADI_ADAR690x_MINCYC_CONFIG_COMPLETE 0 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_CONFIG_COMPLETE */
#define ADI_ADAR690x_MAXCYC_CONFIG_COMPLETE 0 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_CONFIG_COMPLETE */
#define ADI_ADAR690x_MINCYC_TASKLIST 0 /**< Minimum cycle time for @ref ADI_ADAR690x_FW_TASKLIST */
#define ADI_ADAR690x_MAXCYC_TASKLIST 0 /**< Maximum cycle time for @ref ADI_ADAR690x_FW_TASKLIST */

/* Offsets in ICCM file */
#define ADI_ADAR690x_OFF_FW_ICCM_LOAD_ADDR  0x1FDF4 /**< Offset of ICCM file load address in ICCM file. */
#define ADI_ADAR690x_OFF_FW_DCCM_LOAD_ADDR  0x1FDF8 /**< Offset of DCCM file load address in ICCM file. */
#define ADI_ADAR690x_OFF_FW_VERSION 0x1FDFC /**< Offset of firmware version in ICCM file. */

#define ADI_ADAR690x_DMA_BASE_POINTER 0x80008400UL /**< See **DMA (DIRECT MEMORY ACCESS)** in @cite frm. */
#define ADI_ADAR690x_DMA_AREA_BASE 0x80008600UL /**< See **DMA (DIRECT MEMORY ACCESS)** in @cite frm. */
#define ADI_ADAR690x_DMA_AREA_SIZE 14848UL /**< See **DMA (DIRECT MEMORY ACCESS)** in @cite frm. */

#define ADI_ADAR690x_CFG_SPI_CMD 0x80000800 /**< See **SENDING COMMANDS OVER SPI** in @cite frm. */
#define ADI_ADAR690x_CFG_BASE 0x80006000 /**< See **CONFIGURATION TABLE** in @cite frm. */
#define ADI_ADAR690x_STS_BASE 0x80004800 /**< See **STATUS TABLE** @cite frm. */

/* Table 4 from FRM */
#define ADI_ADAR690x_CFG_REF_FREQ_HZ (ADI_ADAR690x_CFG_BASE+0x0) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_RFPLL_LOOP_BW_HZ (ADI_ADAR690x_CFG_BASE+0x4) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_RAMP_START_FREQ_HZ (ADI_ADAR690x_CFG_BASE+0x8) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_RAMP_BW_MHZ (ADI_ADAR690x_CFG_BASE+0x10) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_CASCADED (ADI_ADAR690x_CFG_BASE+0x20) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_POWER_DOWN_AUTO_US (ADI_ADAR690x_CFG_BASE+0x24) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_HPF_FC_RX_CHAN0 (ADI_ADAR690x_CFG_BASE+0x28) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_HPF_FC_RX_CHAN1 (ADI_ADAR690x_CFG_BASE+0x2C) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_HPF_FC_RX_CHAN2 (ADI_ADAR690x_CFG_BASE+0x30) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_HPF_FC_RX_CHAN3 (ADI_ADAR690x_CFG_BASE+0x34) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_HPF_GAIN_RX_CHAN0 (ADI_ADAR690x_CFG_BASE+0x38) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_HPF_GAIN_RX_CHAN1 (ADI_ADAR690x_CFG_BASE+0x3C) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_HPF_GAIN_RX_CHAN2 (ADI_ADAR690x_CFG_BASE+0x40) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_HPF_GAIN_RX_CHAN3 (ADI_ADAR690x_CFG_BASE+0x44) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_PGA_GAIN_RX_CHAN0 (ADI_ADAR690x_CFG_BASE+0x48) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_PGA_GAIN_RX_CHAN1 (ADI_ADAR690x_CFG_BASE+0x4C) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_PGA_GAIN_RX_CHAN2 (ADI_ADAR690x_CFG_BASE+0x50) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_PGA_GAIN_RX_CHAN3 (ADI_ADAR690x_CFG_BASE+0x54) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_PWR_TX0 (ADI_ADAR690x_CFG_BASE+0x5C) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_PWR_TX1 (ADI_ADAR690x_CFG_BASE+0x60) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_PWR_TX2 (ADI_ADAR690x_CFG_BASE+0x64) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_CRC_USER_AREA_ADDR (ADI_ADAR690x_CFG_BASE+0x68) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_CRC_USER_AREA_COUNT (ADI_ADAR690x_CFG_BASE+0x6C) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_TIMING_COMP_EN (ADI_ADAR690x_CFG_BASE+0x70) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_VDDIO_MIN_VOLT (ADI_ADAR690x_CFG_BASE+0x88) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_VDDIO_MAX_VOLT (ADI_ADAR690x_CFG_BASE+0xB4) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_ADC_GAIN_RX_CHAN0 (ADI_ADAR690x_CFG_BASE+0xDC) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_ADC_GAIN_RX_CHAN1 (ADI_ADAR690x_CFG_BASE+0xE0) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_ADC_GAIN_RX_CHAN2 (ADI_ADAR690x_CFG_BASE+0xE4) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_ADC_GAIN_RX_CHAN3 (ADI_ADAR690x_CFG_BASE+0xE8) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_PWR_SUP_CHK (ADI_ADAR690x_CFG_BASE+0xEC) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_PAT_SEL_TEST_TONE (ADI_ADAR690x_CFG_BASE+0x100) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_CHANNEL_SEL_TEST_TONE (ADI_ADAR690x_CFG_BASE+0x104) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_POWER_MANAGE (ADI_ADAR690x_CFG_BASE+0x108) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_CONTINUOUS_PA (ADI_ADAR690x_CFG_BASE+0x10C) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_PWRDN_INTERRUPT (ADI_ADAR690x_CFG_BASE+0x110) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_MEAS_REL_GAIN_MISMATCH_0 (ADI_ADAR690x_CFG_BASE+0x13C) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_MEAS_REL_GAIN_MISMATCH_1 (ADI_ADAR690x_CFG_BASE+0x140) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_MEAS_REL_GAIN_MISMATCH_2 (ADI_ADAR690x_CFG_BASE+0x144) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_MEAS_REL_GAIN_MISMATCH_3 (ADI_ADAR690x_CFG_BASE+0x148) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_MEAS_REL_GAIN_MISMATCH_4 (ADI_ADAR690x_CFG_BASE+0x14C) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_MEAS_REL_GAIN_MISMATCH_5 (ADI_ADAR690x_CFG_BASE+0x150) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_OP_PWR_TX0 (ADI_ADAR690x_CFG_BASE+0x154) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_OP_PWR_TX1 (ADI_ADAR690x_CFG_BASE+0x158) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_OP_PWR_TX2 (ADI_ADAR690x_CFG_BASE+0x15C) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_TX_LOAD_T0_TX0 (ADI_ADAR690x_CFG_BASE+0x16C) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_TX_LOAD_T0_TX1 (ADI_ADAR690x_CFG_BASE+0x170) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_TX_LOAD_T0_TX2 (ADI_ADAR690x_CFG_BASE+0x174) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_RFPLL_PERIOD_LOW_LIM (ADI_ADAR690x_CFG_BASE+0x180) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_RFPLL_PERIOD_HIGH_LIM (ADI_ADAR690x_CFG_BASE+0x184) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_RX_CHAIN_CHK (ADI_ADAR690x_CFG_BASE+0x19C) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_PWR_DET_MEAS (ADI_ADAR690x_CFG_BASE+0x1A0) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_SYS_CAL_ENABLE (ADI_ADAR690x_CFG_BASE+0x1A4) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_DMA_OFFSETS_SEL (ADI_ADAR690x_CFG_BASE+0x1A8) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_LOCHAIN_MST_SLV_SYNC (ADI_ADAR690x_CFG_BASE+0x1B0) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_CRC_GROUP_SELECT (ADI_ADAR690x_CFG_BASE+0x304) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_CRC_SIGNATURE_SELECT (ADI_ADAR690x_CFG_BASE+0x308) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_CONFIG_BLOCK_LEN (ADI_ADAR690x_CFG_BASE+0x30C) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_CFG_CONFIG_BLOCK_CRC (ADI_ADAR690x_CFG_BASE+0x310) /**< See Table 4 in @cite frm. */

#define ADI_ADAR690x_MIN_REF_FREQ_HZ (40000000UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_REF_FREQ_HZ (80000000UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_RFPLL_LOOP_BW_HZ (100000UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_RFPLL_LOOP_BW_HZ (1000000UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_RAMP_START_FREQ_HZ (76000000000ULL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_RAMP_START_FREQ_HZ (81000000000ULL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_RAMP_BW_MHZ (-5000.0F) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_RAMP_BW_MHZ (5000.0F) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_CASCADED (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_CASCADED (1UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_POWER_DOWN_AUTO_US (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_POWER_DOWN_AUTO_US (1000000UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_HPF_FC_RX_CHAN0 (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_HPF_FC_RX_CHAN0 (6UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_HPF_FC_RX_CHAN1 (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_HPF_FC_RX_CHAN1 (6UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_HPF_FC_RX_CHAN2 (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_HPF_FC_RX_CHAN2 (6UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_HPF_FC_RX_CHAN3 (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_HPF_FC_RX_CHAN3 (6UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_HPF_GAIN_RX_CHAN0 (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_HPF_GAIN_RX_CHAN0 (2UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_HPF_GAIN_RX_CHAN1 (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_HPF_GAIN_RX_CHAN1 (2UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_HPF_GAIN_RX_CHAN2 (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_HPF_GAIN_RX_CHAN2 (2UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_HPF_GAIN_RX_CHAN3 (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_HPF_GAIN_RX_CHAN3 (2UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_PGA_GAIN_RX_CHAN0 (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_PGA_GAIN_RX_CHAN0 (3UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_PGA_GAIN_RX_CHAN1 (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_PGA_GAIN_RX_CHAN1 (3UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_PGA_GAIN_RX_CHAN2 (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_PGA_GAIN_RX_CHAN2 (3UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_PGA_GAIN_RX_CHAN3 (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_PGA_GAIN_RX_CHAN3 (3UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_PWR_TX0 (-10L) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_PWR_TX0 (0L) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_PWR_TX1 (-10L) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_PWR_TX1 (0L) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_PWR_TX2 (-10L) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_PWR_TX2 (0L) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_TIMING_COMP_EN (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_TIMING_COMP_EN (1UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_ADC_GAIN_RX_CHAN0 (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_ADC_GAIN_RX_CHAN0 (3UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_ADC_GAIN_RX_CHAN1 (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_ADC_GAIN_RX_CHAN1 (3UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_ADC_GAIN_RX_CHAN2 (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_ADC_GAIN_RX_CHAN2 (3UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_ADC_GAIN_RX_CHAN3 (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_ADC_GAIN_RX_CHAN3 (3UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_PAT_SEL_TEST_TONE (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_PAT_SEL_TEST_TONE (63UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_CHANNEL_SEL_TEST_TONE (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_CHANNEL_SEL_TEST_TONE (15UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_SYS_CAL_ENABLE (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_SYS_CAL_ENABLE (1UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MIN_DMA_OFFSETS_SEL (0UL) /**< See Table 4 in @cite frm. */
#define ADI_ADAR690x_MAX_DMA_OFFSETS_SEL (2UL) /**< See Table 4 in @cite frm. */

/* Table 5 from FRM */
#define ADI_ADAR690x_STS_TX0_TEMP (ADI_ADAR690x_STS_BASE+0x0) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_TX1_TEMP (ADI_ADAR690x_STS_BASE+0x4) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_TX2_TEMP (ADI_ADAR690x_STS_BASE+0x8) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_RX0_TEMP (ADI_ADAR690x_STS_BASE+0xC) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_RX1_TEMP (ADI_ADAR690x_STS_BASE+0x10) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_RX2_TEMP (ADI_ADAR690x_STS_BASE+0x14) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_RX3_TEMP (ADI_ADAR690x_STS_BASE+0x18) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_LOCHAIN_TEMP (ADI_ADAR690x_STS_BASE+0x1C) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_TX_LOAD_T0_TX0 (ADI_ADAR690x_STS_BASE+0x34) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_TX_LOAD_T0_TX1 (ADI_ADAR690x_STS_BASE+0x38) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_TX_LOAD_T0_TX2 (ADI_ADAR690x_STS_BASE+0x3C) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_RX_SIGCHAIN_MISMATCH_0 (ADI_ADAR690x_STS_BASE+0x214) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_RX_SIGCHAIN_MISMATCH_1 (ADI_ADAR690x_STS_BASE+0x218) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_RX_SIGCHAIN_MISMATCH_2 (ADI_ADAR690x_STS_BASE+0x21C) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_RX_SIGCHAIN_MISMATCH_3 (ADI_ADAR690x_STS_BASE+0x220) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_RX_SIGCHAIN_MISMATCH_4 (ADI_ADAR690x_STS_BASE+0x224) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_RX_SIGCHAIN_MISMATCH_5 (ADI_ADAR690x_STS_BASE+0x228) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_OP_PWR_TX0 (ADI_ADAR690x_STS_BASE+0x230) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_OP_PWR_TX1 (ADI_ADAR690x_STS_BASE+0x234) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_OP_PWR_TX2 (ADI_ADAR690x_STS_BASE+0x238) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_VDD_DCO_PWR_SUP_VOLT (ADI_ADAR690x_STS_BASE+0x248) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_AVDD_09P_PWR_SUP_VOLT (ADI_ADAR690x_STS_BASE+0x24C) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_DVDD_09P_PWR_SUP_VOLT (ADI_ADAR690x_STS_BASE+0x258) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_AVDD_1P8_PWR_SUP_VOLT (ADI_ADAR690x_STS_BASE+0x264) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_VDDIO_1P8_PWR_SUP_VOLT (ADI_ADAR690x_STS_BASE+0x274) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_VDDIO_PWR_SUP_VOLT (ADI_ADAR690x_STS_BASE+0x27C) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_CRC_PASS (ADI_ADAR690x_STS_BASE+0x3D4) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_CRC_FAIL (ADI_ADAR690x_STS_BASE+0x3D8) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP0 (ADI_ADAR690x_STS_BASE+0x3FC) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP1 (ADI_ADAR690x_STS_BASE+0x400) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP2 (ADI_ADAR690x_STS_BASE+0x404) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP3 (ADI_ADAR690x_STS_BASE+0x408) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP4 (ADI_ADAR690x_STS_BASE+0x40C) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP5 (ADI_ADAR690x_STS_BASE+0x410) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP6 (ADI_ADAR690x_STS_BASE+0x414) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP7 (ADI_ADAR690x_STS_BASE+0x418) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP8 (ADI_ADAR690x_STS_BASE+0x41C) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP9 (ADI_ADAR690x_STS_BASE+0x420) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP10 (ADI_ADAR690x_STS_BASE+0x424) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP11 (ADI_ADAR690x_STS_BASE+0x428) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP12 (ADI_ADAR690x_STS_BASE+0x42C) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP13 (ADI_ADAR690x_STS_BASE+0x430) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP14 (ADI_ADAR690x_STS_BASE+0x434) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP15 (ADI_ADAR690x_STS_BASE+0x438) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_COMPUTED_CRC_GROUP16 (ADI_ADAR690x_STS_BASE+0x43C) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_ADCPLL_FREQ_HZ (ADI_ADAR690x_STS_BASE+0x4B8) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_RFPLL_FREQ_HZ (ADI_ADAR690x_STS_BASE+0x4D0) /**< See Table 5 in @cite frm. */
#define ADI_ADAR690x_STS_DMA_OFFSETS_LUT (ADI_ADAR690x_STS_BASE+0xE1C) /**< See Table 5 in @cite frm. */

/* Power Detector task bit positions */
#define ADI_ADAR690x_BITP_PWR_DET_MEAS_LO 0 /**< See **ADI_ADAR690x_FW_MEAS_PWR_DET** in @cite frm */
#define ADI_ADAR690x_BITP_PWR_DET_MEAS_TXACTIVECOUPLED 1 /**< See **ADI_ADAR690x_FW_MEAS_PWR_DET** in @cite frm */
#define ADI_ADAR690x_BITP_PWR_DET_MEAS_TXACTIVEREFLECTED 4 /**< See **ADI_ADAR690x_FW_MEAS_PWR_DET** in @cite frm */
#define ADI_ADAR690x_BITP_PWR_DET_MEAS_CLRPREV 19 /**< See **ADI_ADAR690x_FW_MEAS_PWR_DET** in @cite frm */
#define ADI_ADAR690x_BITP_PWR_DET_MEAS_PDMEASPERCHIRP 20 /**< See **ADI_ADAR690x_FW_MEAS_PWR_DET** in @cite frm */

/* Bit definitions for ADI_ADAR690x_CFG_POWER_MANAGE */
#define ADI_ADAR690x_BITP_POWER_RX0 0 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_RX1 1 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_RX2 2 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_RX3 3 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_AFE0 8 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_AFE1 9 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_AFE2 10 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_AFE3 11 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_TX0 16 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_TX1 17 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_TX2 18 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_RFPLL 20 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_LO 22 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_LOAMP 23 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_AUXADC 24 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_DATAPORT 25 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_PERMANENT 27 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_DOWN_REQUEST 29 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_RESTORE_REQUEST 30 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_POWER_UP_REQUEST 31 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_CONTINUOUS_PA_TX0 0 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_CONTINUOUS_PA_TX1 1 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITP_CONTINUOUS_PA_TX2 2 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_RX0 0x00000001 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_RX1 0x00000002 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_RX2 0x00000004 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_RX3 0x00000008 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_AFE0 0x00000100 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_AFE1 0x00000200 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_AFE2 0x00000400 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_AFE3 0x00000800 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_TX0 0x00010000 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_TX1 0x00020000 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_TX2 0x00040000 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_RFPLL 0x00100000 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_LO 0x00400000 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_LOAMP 0x00800000 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_AUXADC 0x01000000 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_DATAPORT 0x02000000 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_PERMANENT 0x08000000 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_DOWN_REQUEST 0x20000000 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_RESTORE_REQUEST 0x40000000 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_POWER_UP_REQUEST 0x80000000 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_CONTINUOUS_PA_TX0 0x00000001 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_CONTINUOUS_PA_TX1 0x00000002 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */
#define ADI_ADAR690x_BITM_CONTINUOUS_PA_TX2 0x00000004 /**< See **ADI_ADAR690x_CFG_POWER_MANAGE** in @cite frm */

#endif                          /* __ADAR690X_FW_H__ */
