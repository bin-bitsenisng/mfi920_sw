/* adar690x_regs.h
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

#ifndef __ADAR609X_REGS_H__
#define __ADAR609X_REGS_H__

#include "ADAR690x.h"

#define BITP_MISC_MISC_FILTER_CTRL_FILTER_OUTPUT_BITWIDTH 10    /*  Output Bit Width Select */
#define BITM_MISC_MISC_FILTER_CTRL_FILTER_OUTPUT_BITWIDTH 0x00000C00    /*  Output Bit Width Select */

#define BITP_MISC_MISC_FILTER_CTRL_FILTER_DECIM_RATIO  0        /*  Filter Decimation Ratio */
#define BITM_MISC_MISC_FILTER_CTRL_FILTER_DECIM_RATIO 0x000001FF        /*  Filter Decimation Ratio */

#define REG_RF_ADPLL_RFPLL_RAMP_CONFIG0_RESET 0x00000000        /*      Reset Value for RFPLL_RAMP_CONFIG0  */
#define REG_RF_ADPLL_RFPLL_RAMP_CONFIG0      0xF0020058 /*  RF_ADPLL RAMP_CONFIG0 */

#define REG_AFE0_FLT_DATALIM      0xF0012058    /*  AFE0 FLT_DATALIM */
#define REG_AFE1_FLT_DATALIM      0xF0013058    /*  AFE1 FLT_DATALIM */
#define REG_AFE2_FLT_DATALIM      0xF0014058    /*  AFE2 FLT_DATALIM */
#define REG_AFE3_FLT_DATALIM      0xF0015058    /*  AFE3 FLT_DATALIM */

#define BITP_AFE_FLT_DATALIM_LOWER_LIMIT 0      /*  Filter_data_lower_limit */
#define BITP_AFE_FLT_DATALIM_UPPER_LIMIT 16     /*  Filter_data_upper_limit */

#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG0_VGA_SYNC_DATA_VALID 18 /*  Set That VGA Gain Activation/Deactivation is Synchronous with Data Valid */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG0_VGA_SYNC_DATA_VALID 0x00040000 /*  Set That VGA Gain Activation/Deactivation is Synchronous with Data Valid */

#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_ON_PATT 20 /*  VGA Enable Pattern {DEL2,SLP1,DEL1,SLP0,DEL0,INIT} */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_ON_PATT 0x03F00000 /*  VGA Enable Pattern {DEL2,SLP1,DEL1,SLP0,DEL0,INIT} */

/* FW fault status bit positions and masks. Documented in Table 6 in FRM. */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_ICCM_DCCM_CRC 0  /* Instruction Closely Coupled Memory (ICCM) or Data Closely Couple Memory (DCCM) cyclic redundancy check (CRC) */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_INVALID_BOOT_MODE 1      /* Invalid boot mode flag */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_INVALID_PATCH_IDENTIFIER 2       /* Invalid patch identifier */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_INVALID_PATCH_CODE_CRC 3 /* Patch code CRC */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_INVALID_PATCH_LENGTH 4   /* Invalid patch length */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_INVALID_FUNCTION_PATCH_ADDRESS 5 /* Invalid function patch address. */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_UNDEFINED_INTERRUPT_TRIGGERED 6  /* Undefined interrupt triggered. */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_INVALID_GPIO11_SET 8     /* Invalid attempt to set GPIO11 pin (FW_BUSY) as input */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_INVALID_NUM_INTERRUPTS 9 /* Invalid number of interrupts */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_MCU_INTERNAL_EXCEPTION 10        /* Microcontroller unit (MCU) internal exception */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_NULL_PARAM_CHECK 12      /* Null parameter checks failed */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_INVALID_SPI_COMMAND 13   /* Invalid serial peripheral interface (SPI) command */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_ADCPLL_FAIL 16   /* ADCPLL lock fail or invalid ADCPLL configuration inputs */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_RFPLL_FAIL 17    /* RFPLL lock fail or invalid RFPLL configuration inputs */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_AUXADC_CONVERSION 18     /* Auxiliary ADC conversion */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_LO_CAL 19        /* Local oscillator (LO) calibration */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_FLASH_ADC_CAL 20 /* Flash ADC calibration */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_HPF_CAL 21       /* High-pass filter (HPF) calibration */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_ADC_PHASE_CAL 22 /* ADC phase calibration */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_PGA_CAL 23       /* PGA calibration */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_ADC_SYNC 24      /* ADC sync */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_LO_AMP_CAL 25    /* Local oscillator (LO) amplifier calibration */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_PA_CAL 26        /* Power amplifier (PA) calibration */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_CHIP_INIT 27     /* Chip initialization */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_OTP_RW 28        /* One-Time programmable (OTP) read/write */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_TEMP_SENSE_CAL 29        /* Temperature sensor calibration */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_POWER_SUPPLY_CHECK 0     /* Power supply check */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_RX_SIGNAL_CHAIN 1        /* Receive signal chain gain and linearity */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_LO_OP_POWER 4    /* Local Oscillator output power */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_TX_OP_POWER 5    /* Transmit output power */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_AUX_ADC_ACCURACY 7       /* Auxiliary ADC accuracy */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_WDT_INIT 8       /* WDT init failure */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_WDT 9    /* WDT failure */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_PWR_DETECTOR 10  /* Power Detector Rationality Check */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_TEMP_CHECK 11    /* Temperature out-of-range or channel-channel temperature out-of-range */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_TX_ISOLATION_MON 13      /* Tx Isolation Monitor check */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_TX_OP_LOAD 14    /* Transmit output load */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_CHIRP_TIME_COMP 15       /* Chirp Timing Comparator check */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_RX_AFE_DIAG 16   /* RX AFE Diagnostic check */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_ADC_PLL_LOL 17   /* ADC PLL Loss of lock diagnostic check */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_RF_PLL_LOL 18    /* RF PLL Loss of lock diagnostic check */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_INIT_HW_CRC 19   /* Initial hardware engine CRC computation */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_DECI_FLT_DIAG 20 /* Decimation Filter Diagnostic check */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_CRC_CHECK 21     /* CRC check */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_RF_PLL_PERIOD_COUNTER 23 /* RF ADPLL Period Counter */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_FAULTCTL_FAULT1 30       /* FaultCtl_Fault1 set */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_FAULTCTL_FAULT0B 31      /* FaultCtl_Fault0b set */
#define BITP_FAULTCTL_SOFTWARE_FAULT_2_AFE0_FILT_LESS_THAN_LOWER_LIM 0  /* AFE0 Filter Data less than safe lower limit */
#define BITP_FAULTCTL_SOFTWARE_FAULT_2_AFE0_FILT_MORE_THAN_UPPER_LIM 1  /* AFE0 Filter Data more than safe upper limit */
#define BITP_FAULTCTL_SOFTWARE_FAULT_2_AFE1_FILT_LESS_THAN_LOWER_LIM 2  /* AFE1 Filter Data less than safe lower limit */
#define BITP_FAULTCTL_SOFTWARE_FAULT_2_AFE1_FILT_MORE_THAN_UPPER_LIM 3  /* AFE1 Filter Data more than safe upper limit */
#define BITP_FAULTCTL_SOFTWARE_FAULT_2_AFE2_FILT_LESS_THAN_LOWER_LIM 4  /* AFE2 Filter Data less than safe lower limit */
#define BITP_FAULTCTL_SOFTWARE_FAULT_2_AFE2_FILT_MORE_THAN_UPPER_LIM 5  /* AFE2 Filter Data more than safe upper limit */
#define BITP_FAULTCTL_SOFTWARE_FAULT_2_AFE3_FILT_LESS_THAN_LOWER_LIM 6  /* AFE3 Filter Data less than safe lower limit */
#define BITP_FAULTCTL_SOFTWARE_FAULT_2_AFE3_FILT_MORE_THAN_UPPER_LIM 7  /* AFE3 Filter Data more than safe upper limit */
#define BITP_FAULTCTL_SOFTWARE_FAULT_3_CHIRP_SEQ_FILE_PARSE 0   /* Chirp Sequencing Configuration File parsing failure due to invalid values */
#define BITP_FAULTCTL_SOFTWARE_FAULT_3_SINGLE_BURST_EXEC 1      /* Single burst execution failure */
#define BITP_FAULTCTL_SOFTWARE_FAULT_3_FW_BUSY_PAUSE_CNT_EXP 2  /* Firmware busy at pause counter expiry in scheduler mode */
#define BITP_FAULTCTL_SOFTWARE_FAULT_3_SINGLE_DOMAIN_EXEC 3     /* Single domain execution failure */
#define BITP_FAULTCTL_SOFTWARE_FAULT_3_PWR_DOWN_INT 5   /* Power down interrupt */
#define BITP_FAULTCTL_SOFTWARE_FAULT_3_CHIRP_SEQ_FILE_NOT_AVAIL_PARSED 6        /* Chirp Sequencing Configuration File not available/parsed */
#define BITP_FAULTCTL_SOFTWARE_FAULT_3_FW_BUSY 7        /* Firmware busy fault. Occurs when a firmware command is received and the internal MCU is busy. */
#define BITP_FAULTCTL_SOFTWARE_FAULT_3_SINGLE_CYCLE_EXEC 8      /* Single cycle execution failure */
#define BITP_FAULTCTL_SOFTWARE_FAULT_3_SYNC_TASK 9      /* Synchronization task failure */
#define BITP_FAULTCTL_SOFTWARE_FAULT_3_EXT_TEST_TONE 14 /* External mode test tone failure */
#define BITP_FAULTCTL_SOFTWARE_FAULT_3_REM_TIMING_COMP_RST 15   /* Remote timing comparator reset failure */
#define BITP_FAULTCTL_SOFTWARE_FAULT_3_PWR_DET_MEAS 16  /* Power Detector measurement failure */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_ICCM_DCCM_CRC 0x00000001 /* Instruction Closely Coupled Memory (ICCM) or Data Closely Couple Memory (DCCM) cyclic redundancy check (CRC) */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_INVALID_BOOT_MODE 0x00000002     /* Invalid boot mode flag */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_INVALID_PATCH_IDENTIFIER 0x00000004
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_INVALID_PATCH_CODE_CRC 0x00000008
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_INVALID_PATCH_LENGTH 0x00000010
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_INVALID_FUNCTION_PATCH_ADDRESS 0x00000020
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_UNDEFINED_INTERRUPT_TRIGGERED 0x00000040
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_INVALID_GPIO11_SET 0x00000100    /* Invalid attempt to set GPIO11 pin (FW_BUSY) as input */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_INVALID_NUM_INTERRUPTS 0x00000200        /* Invalid number of interrupts */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_MCU_INTERNAL_EXCEPTION 0x00000400        /* Microcontroller unit (MCU) internal exception */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_NULL_PARAM_CHECK 0x00001000      /* Null parameter checks failed */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_INVALID_SPI_COMMAND 0x00002000   /* Invalid serial peripheral interface (SPI) command */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_ADCPLL_FAIL 0x00010000   /* ADCPLL lock fail or invalid ADCPLL configuration inputs */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_RFPLL_FAIL 0x00020000    /* RFPLL lock fail or invalid RFPLL configuration inputs */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_AUXADC_CONVERSION 0x00040000     /* Auxiliary ADC conversion */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_LO_CAL 0x00080000        /* Local oscillator (LO) calibration */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_FLASH_ADC_CAL 0x00100000 /* Flash ADC calibration */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_HPF_CAL 0x00200000       /* High-pass filter (HPF) calibration */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_ADC_PHASE_CAL 0x00400000 /* ADC phase calibration */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_PGA_CAL 0x00800000       /* PGA calibration */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_ADC_SYNC 0x01000000      /* ADC sync */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_LO_AMP_CAL 0x02000000    /* Local oscillator (LO) amplifier calibration */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_PA_CAL 0x04000000        /* Power amplifier (PA) calibration */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_CHIP_INIT 0x08000000     /* Chip initialization */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_OTP_RW 0x10000000        /* One-Time programmable (OTP) read/write */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_TEMP_SENSE_CAL 0x20000000        /* Temperature sensor calibration */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_POWER_SUPPLY_CHECK 0x00000001    /* Power supply check */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_RX_SIGNAL_CHAIN 0x00000002       /* Receive signal chain */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_LO_OP_POWER 0x00000010   /* Local Oscillator output power */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_TX_OP_POWER 0x00000020   /* Transmit output power */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_AUX_ADC_ACCURACY 0x00000080      /* Auxiliary ADC accuracy */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_WDT_INIT 0x00000100      /* WDT init failure */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_WDT 0x00000200   /* WDT failure */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_PWR_DETECTOR 0x00000400  /* Power Detector Rationality Check */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_TEMP_CHECK 0x00000800    /* Temperature out-of-range or channel-channel temperature out-of-range */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_TX_ISOLATION_MON 0x00002000      /* Tx Isolation Monitor check */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_TX_OP_LOAD 0x00004000    /* Transmit output load */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_CHIRP_TIME_COMP 0x00008000       /* Chirp Timing Comparator check */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_RX_AFE_DIAG 0x00010000   /* RX AFE Diagnostic check */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_ADC_PLL_LOL 0x00020000   /* ADC PLL Loss of lock diagnostic check */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_RF_PLL_LOL 0x00040000    /* RF PLL Loss of lock diagnostic check */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_INIT_HW_CRC 0x00080000   /* Initial hardware engine CRC computation */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_DECI_FLT_DIAG 0x00100000 /* Decimation Filter Diagnostic check */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_CRC_CHECK 0x00200000     /* CRC check */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_RF_PLL_PERIOD_COUNTER 0x00800000 /* RF ADPLL Period Counter */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_FAULTCTL_FAULT1 0x40000000       /* FaultCtl_Fault1 set */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_FAULTCTL_FAULT0B 0x80000000      /* FaultCtl_Fault0b set */
#define BITM_FAULTCTL_SOFTWARE_FAULT_2_AFE0_FILT_LESS_THAN_LOWER_LIM 0x00000001 /* AFE0 Filter Data less than safe lower limit */
#define BITM_FAULTCTL_SOFTWARE_FAULT_2_AFE0_FILT_MORE_THAN_UPPER_LIM 0x00000002 /* AFE0 Filter Data more than safe upper limit */
#define BITM_FAULTCTL_SOFTWARE_FAULT_2_AFE1_FILT_LESS_THAN_LOWER_LIM 0x00000004 /* AFE1 Filter Data less than safe lower limit */
#define BITM_FAULTCTL_SOFTWARE_FAULT_2_AFE1_FILT_MORE_THAN_UPPER_LIM 0x00000008 /* AFE1 Filter Data more than safe upper limit */
#define BITM_FAULTCTL_SOFTWARE_FAULT_2_AFE2_FILT_LESS_THAN_LOWER_LIM 0x00000010 /* AFE2 Filter Data less than safe lower limit */
#define BITM_FAULTCTL_SOFTWARE_FAULT_2_AFE2_FILT_MORE_THAN_UPPER_LIM 0x00000020 /* AFE2 Filter Data more than safe upper limit */
#define BITM_FAULTCTL_SOFTWARE_FAULT_2_AFE3_FILT_LESS_THAN_LOWER_LIM 0x00000040 /* AFE3 Filter Data less than safe lower limit */
#define BITM_FAULTCTL_SOFTWARE_FAULT_2_AFE3_FILT_MORE_THAN_UPPER_LIM 0x00000080 /* AFE3 Filter Data more than safe upper limit */
#define BITM_FAULTCTL_SOFTWARE_FAULT_3_CHIRP_SEQ_FILE_PARSE 0x00000001  /* Chirp Sequencing Configuration File parsing failure due to invalid values */
#define BITM_FAULTCTL_SOFTWARE_FAULT_3_SINGLE_BURST_EXEC 0x00000002     /* Single burst execution failure */
#define BITM_FAULTCTL_SOFTWARE_FAULT_3_FW_BUSY_PAUSE_CNT_EXP 0x00000004 /* Firmware busy at pause counter expiry in scheduler mode */
#define BITM_FAULTCTL_SOFTWARE_FAULT_3_SINGLE_DOMAIN_EXEC 0x00000008    /* Single domain execution failure */
#define BITM_FAULTCTL_SOFTWARE_FAULT_3_PWR_DOWN_INT 0x00000020  /* Power down interrupt */
#define BITM_FAULTCTL_SOFTWARE_FAULT_3_CHIRP_SEQ_FILE_NOT_AVAIL_PARSED 0x00000040       /* Chirp Sequencing Configuration File not available/parsed */
#define BITM_FAULTCTL_SOFTWARE_FAULT_3_FW_BUSY 0x00000080       /* Firmware busy fault. Occurs when a firmware command is received and the internal MCU is busy. */
#define BITM_FAULTCTL_SOFTWARE_FAULT_3_SINGLE_CYCLE_EXEC 0x00000100     /* Single cycle execution failure */
#define BITM_FAULTCTL_SOFTWARE_FAULT_3_SYNC_TASK 0x00000200     /* Synchronization task failure */
#define BITM_FAULTCTL_SOFTWARE_FAULT_3_EXT_TEST_TONE 0x00004000 /* External mode test tone failure */
#define BITM_FAULTCTL_SOFTWARE_FAULT_3_REM_TIMING_COMP_RST 0x00008000   /* Remote timing comparator reset failure */
#define BITM_FAULTCTL_SOFTWARE_FAULT_3_PWR_DET_MEAS 0x00010000  /* Power Detector measurement failure */

#endif                          // __ADAR609X_REGS_H__
