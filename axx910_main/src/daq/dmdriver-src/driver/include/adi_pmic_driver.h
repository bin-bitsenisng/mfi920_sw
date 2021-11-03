/* adi_pmic_driver.h
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
* Public C interface to the pmic driver
*/

#ifndef __ADI_PMIC_DRIVER_H__
#define __ADI_PMIC_DRIVER_H__

#include "adi_dmdriver.h"

#define ADI_PMIC_UNLOCK_KEY                     0x5F6A8C3DUL

#define ADI_PMIC_UNLOCK_ADDRESS                 0x001CUL
#define ADI_PMIC_FREQ_CONFIG                    0x8008UL
#define ADI_PMIC_BUCK_ONE_VOUT_SETTING_ADDRESS  0x800CUL
#define ADI_PMIC_BUCK_ONE_VOUT_ADDRESS          0x8010UL
#define ADI_PMIC_BUCK_FOUR_ADDRESS              0x8014UL
#define ADI_PMIC_BUCK_DVS_ADDRESS               0x8018UL
#define ADI_PMIC_LDO_ONE_ADDRESS                0x801CUL
#define ADI_PMIC_LDO_TWO_ADDRESS                0x8020UL
#define ADI_PMIC_LDO_THREE_ADDRESS              0x8024UL
#define ADI_PMIC_LDO_FOUR_ADDRESS               0x8028UL
#define ADI_PMIC_LDO_FIVE_ADDRESS               0x802CUL
#define ADI_PMIC_LDO_SIX_ADDRESS                0x8030UL
#define ADI_PMIC_LDO_SEVEN_ADDRESS              0x8034UL
#define ADI_PMIC_WARN_WINDOW_ADDRESS            0x8038UL
#define ADI_PMIC_FAULT_WINDOW_ADDRESS           0x803CUL
#define ADI_PMIC_VOLTAGE_BLANK_TIME0_ADDRESS    0x80B8UL
#define ADI_PMIC_VOLTAGE_BLANK_TIME1_ADDRESS    0x80BCUL

/** List of LDO's that the user can change */
#define ADI_PMIC_LDO_ONE            1UL     /** < Select LDO 1 */
#define ADI_PMIC_LDO_TWO            2UL     /** < Select LDO 2 */
#define ADI_PMIC_LDO_THREE          3UL     /** < Select LDO 3 */
#define ADI_PMIC_LDO_FOUR           4UL     /** < Select LDO 4 */
#define ADI_PMIC_LDO_FIVE           5UL     /** < Select LDO 5 */
#define ADI_PMIC_LDO_SIX            6UL     /** < Select LDO 6 */
#define ADI_PMIC_LDO_SEVEN          7UL     /** < Select LDO 7 */
typedef uint32_t adi_pmic_ldo_selection_t;

/** Possible voltage settings for LDO1 and LDO2*/
#define ADI_PMIC_1P76_V             0UL     /** < Set the LDO1 Land LDO2 voltage to 1.76V */
#define ADI_PMIC_1P80_V             1UL     /** < Set the LDO1 Land LDO2 voltage to 1.80V */
#define ADI_PMIC_1P85_V             2UL     /** < Set the LDO1 Land LDO2 voltage to 1.85V */
#define ADI_PMIC_1P89_V             3UL     /** < Set the LDO1 Land LDO2 voltage to 1.89V */
#define ADI_PMIC_1P94_V             4UL     /** < Set the LDO1 Land LDO2 voltage to 1.94V */
#define ADI_PMIC_1P98_V             5UL     /** < Set the LDO1 Land LDO2 voltage to 1.98V */
#define ADI_PMIC_2P03_V             6UL     /** < Set the LDO1 Land LDO2 voltage to 2.03V */
#define ADI_PMIC_2P07_V             7UL     /** < Set the LDO1 Land LDO2 voltage to 2.07V */
#define ADI_PMIC_LDO_1_2_INVALID    8UL     /** < Maximum value that the user can enter for LDO1 and LDO2 */
typedef uint32_t adi_pmic_ldo_1_2_voltages_t;

/** Possible voltage settings for LDO3, LDO4 and LDO5*/
#define ADI_PMIC_0P86_V             0UL     /** < Set the LDO3, LDO4 and LDO5 voltage to 0.86V */
#define ADI_PMIC_0P90_V             1UL     /** < Set the LDO3, LDO4 and LDO5 voltage to 0.90V */
#define ADI_PMIC_0P94_V             2UL     /** < Set the LDO3, LDO4 and LDO5 voltage to 0.94V */
#define ADI_PMIC_0P97_V             3UL     /** < Set the LDO3, LDO4 and LDO5 voltage to 0.97V */
#define ADI_PMIC_1P01_V             4UL     /** < Set the LDO3, LDO4 and LDO5 voltage to 1.01V */
#define ADI_PMIC_1P04_V             5UL     /** < Set the LDO3, LDO4 and LDO5 voltage to 1.04V */
#define ADI_PMIC_1P08_V             6UL     /** < Set the LDO3, LDO4 and LDO5 voltage to 1.08V */
#define ADI_PMIC_1P12_V             7UL     /** < Set the LDO3, LDO4 and LDO5 voltage to 1.12V */
#define ADI_PMIC_LDO_3_4_5_INVALID  8UL     /** < Maximum value that the user can enter for LDO3, LDO4 and LDO5 */
typedef uint32_t adi_pmic_ldo_3_4_5_voltages_t;

/** Possible voltage settings for LDO6 and LDO7*/
#define ADI_PMIC_3P20_V             0UL     /** < Set the LDO6 Land LDO7 voltage to 3.20V */
#define ADI_PMIC_3P30_V             1UL     /** < Set the LDO6 Land LDO7 voltage to 3.30V */
#define ADI_PMIC_3P35_V             2UL     /** < Set the LDO6 Land LDO7 voltage to 3.35V */
#define ADI_PMIC_3P40_V             3UL     /** < Set the LDO6 Land LDO7 voltage to 3.40V */
#define ADI_PMIC_LDO_6_7_INVALID    4UL     /** < Maximum value that the user can enter for LDO61 and LDO7 */
typedef uint32_t adi_pmic_ldo_6_7_voltages_t;

/** Possible voltage settings for Buck4*/
#define ADI_PMIC_OP55_V             0UL     /** < Set the Buck4 voltage to 0.55V */
#define ADI_PMIC_OP60_V             1UL     /** < Set the Buck4 voltage to 0.60V */
#define ADI_PMIC_OP65_V             2UL     /** < Set the Buck4 voltage to 0.65V */
#define ADI_PMIC_OP70_V             3UL     /** < Set the Buck4 voltage to 0.70V */
#define ADI_PMIC_OP75_V             4UL     /** < Set the Buck4 voltage to 0.75V */
#define ADI_PMIC_OP80_V             5UL     /** < Set the Buck4 voltage to 0.80V */
#define ADI_PMIC_OP85_V             6UL     /** < Set the Buck4 voltage to 0.85V */
#define ADI_PMIC_OP90_V             7UL     /** < Set the Buck4 voltage to 0.90V */
#define ADI_PMIC_OP95_V             8UL     /** < Set the Buck4 voltage to 0.95V */
#define ADI_PMIC_1P00_V             9UL     /** < Set the Buck4 voltage to 1.00V */
#define ADI_PMIC_1P05_V             10UL    /** < Set the Buck4 voltage to 1.05V */
#define ADI_PMIC_1P10_V             11UL    /** < Set the Buck4 voltage to 1.10V */
#define ADI_PMIC_1P15_V             12UL    /** < Set the Buck4 voltage to 1.15V */
#define ADI_PMIC_1P20_V             13UL    /** < Set the Buck4 voltage to 1.20V */
#define ADI_PMIC_BUCK_4_INVALID     14UL    /** < Maximum value that the user can enter for voltages for PMIC */
typedef uint32_t adi_pmic_buck_4_voltages_t;

/** Warn/Fault Window Offset bits */
#define ADI_PMIC_FB1_WARN_WINDOW_OFFSET     0UL /** < Offset into register for PMIC to set the FB1 warn/fault threshold */
#define ADI_PMIC_FB2_WARN_WINDOW_OFFSET     2UL /** < Offset into register for PMIC to set the FB2 warn/fault threshold */
#define ADI_PMIC_FB3_WARN_WINDOW_OFFSET     4UL /** < Offset into register for PMIC to set the FB3 warn/fault threshold */
#define ADI_PMIC_FB4_WARN_WINDOW_OFFSET     6UL /** < Offset into register for PMIC to set the FB4 warn/fault threshold */
#define ADI_PMIC_FB5_WARN_WINDOW_OFFSET     8UL /** < Offset into register for PMIC to set the FB5 warn/fault threshold */
#define ADI_PMIC_FB6_WARN_WINDOW_OFFSET     10UL/** < Offset into register for PMIC to set the FB6 warn/fault threshold */
#define ADI_PMIC_FB7_WARN_WINDOW_OFFSET     12UL/** < Offset into register for PMIC to set the FB7 warn/fault threshold */
#define ADI_PMIC_FB8_WARN_WINDOW_OFFSET     14UL/** < Offset into register for PMIC to set the FB8 warn/fault threshold */
#define ADI_PMIC_FB9_WARN_WINDOW_OFFSET     16UL/** < Offset into register for PMIC to set the FB9 warn/fault threshold */
#define ADI_PMIC_FB10_WARN_WINDOW_OFFSET    18UL/** < Offset into register for PMIC to set the FB10 warn/fault threshold */
#define ADI_PMIC_FB11_WARN_WINDOW_OFFSET    20UL/** < Offset into register for PMIC to set the FB11 warn/fault threshold */
#define ADI_PMIC_FB12_WARN_WINDOW_OFFSET    22UL/** < Offset into register for PMIC to set the FB12 warn/fault threshold */
#define ADI_PMIC_VM0_WARN_WINDOW_OFFSET     24UL/** < Offset into register for PMIC to set the VM0 warn/fault threshold */
#define ADI_PMIC_VM1_WARN_WINDOW_OFFSET     26UL/** < Offset into register for PMIC to set the VM1 warn/fault threshold */
#define ADI_PMIC_INVALID_WINDOW_OFFSET      27UL/** < Max offset into register for PMIC to set the warn/fault thresholds */
typedef uint32_t adi_pmic_warn_fault_offset_t;

/** Valid Thresholds for Warn/Fault Windows */
#define ADI_PMIC_4_PERCENT  0UL     /** < If the output volatge exceeds 4%, a warn/fault event is triggered */
#define ADI_PMIC_5_PERCENT  1UL     /** < If the output volatge exceeds 5%, a warn/fault event is triggered */
#define ADI_PMIC_6_PERCENT  2UL     /** < If the output volatge exceeds 6%, a warn/fault event is triggered */
#define ADI_PMIC_8_PERCENT  3UL     /** < If the output volatge exceeds 8%, a warn/fault event is triggered */
#define ADI_PMIC_INVALID_THRESHOLD  4UL /** < Maximum value that the user can enter for % for fault/warn windows */
typedef uint32_t adi_pmic_threshold_values_t;

/** Blank Times for Warn Fault Windows */
#define ADI_PMIC_16_US      0UL     /** < Blank time setting of 16us */
#define ADI_PMIC_32_US      1UL     /** < Blank time setting of 32us */
#define ADI_PMIC_48_US      2UL     /** < Blank time setting of 48us */
#define ADI_PMIC_64_US      3UL     /** < Blank time setting of 64us */
#define ADI_PMIC_80_US      4UL     /** < Blank time setting of 80us */
#define ADI_PMIC_96_US      5UL     /** < Blank time setting of 96us */
#define ADI_PMIC_112_US     6UL     /** < Blank time setting of 112us */
#define ADI_PMIC_128_US     7UL     /** < Blank time setting of 128us */
#define ADI_PMIC_144_US     8UL     /** < Blank time setting of 144us */
#define ADI_PMIC_160_US     9UL     /** < Blank time setting of 160us */
#define ADI_PMIC_176_US     10UL    /** < Blank time setting of 176us */
#define ADI_PMIC_192_US     11UL    /** < Blank time setting of 192us */
#define ADI_PMIC_208_US     12UL    /** < Blank time setting of 208us */
#define ADI_PMIC_240_US     13UL    /** < Blank time setting of 240us */
#define ADI_PMIC_288_US     14UL    /** < Blank time setting of 288us */
#define ADI_PMIC_352_US     15UL    /** < Blank time setting of 352us */
#define ADI_PMIC_INVALID_BLANK_TIME      16UL    /** < Maximum value that the user can enter for Blank time for PMIC */
typedef uint32_t adi_pmic_blank_times_t;

/** Possible Buck Choices*/
#define ADI_PMIC_BUCK1      1UL     /** < Select Buck1 to modify settings for */
#define ADI_PMIC_BUCK4      2UL     /** < Select Buck4 to modify settings for */
#define ADI_PMIC_INVALID_BUCK   3UL /** < Maximum value that the user can enter for Buck selection */
typedef uint32_t adi_pmic_buck_sel_t;

/** Output DVS Interval Times*/
#define ADI_PMIC_INTERVAL_TIME_10US 0UL     /** < 10us Dynamic Voltage Scaling Interval Time */
#define ADI_PMIC_INTERVAL_TIME_20US 1UL     /** < 20us Dynamic Voltage Scaling Interval Time */
#define ADI_PMIC_INTERVAL_TIME_30US 2UL     /** < 30us Dynamic Voltage Scaling Interval Time */
#define ADI_PMIC_INTERVAL_TIME_40US 3UL     /** < 40us Dynamic Voltage Scaling Interval Time */
#define ADI_PMIC_INVALID_INTERVAL   4UL     /** < Maximum value that the user can enter for DVS interval time */
typedef uint32_t adi_pmic_dvs_interval_times_t;

/** Sweep Depth of the Frequency Spread Spectrum */
#define ADI_PMIC_SWEEP_DEPTH_2_PERCENT  0UL /** < 2% Sweep Depth of the Frequecny Spread Spectrum */
#define ADI_PMIC_SWEEP_DEPTH_4_PERCENT  1UL /** < 4% Sweep Depth of the Frequecny Spread Spectrum */
#define ADI_PMIC_SWEEP_DEPTH_6_PERCENT  2UL /** < 6% Sweep Depth of the Frequecny Spread Spectrum */
#define ADI_PMIC_SWEEP_DEPTH_8_PERCENT  3UL /** < 8% Sweep Depth of the Frequecny Spread Spectrum */
#define ADI_PMIC_SWEEP_DEPTH_10_PERCENT 4UL /** < 10% Sweep Depth of the Frequecny Spread Spectrum */
#define ADI_PMIC_SWEEP_DEPTH_INVALID    5UL /** < Maximum value that the user can enter for Sweep Depth */
typedef uint32_t adi_pmic_sweep_depth_t;

/** Sweep Frequency of the Frequency Spread Spectrum */
#define ADI_PMIC_SWEEP_FREQ_5_KHz       0UL /** < 5KHz Sweep Freq of the Frequecny Spread Spectrum */
#define ADI_PMIC_SWEEP_FREQ_10_42_KHz   1UL /** < 10.42KHz Sweep Freq of the Frequecny Spread Spectrum */
#define ADI_PMIC_SWEEP_FREQ_15_63_KHz   2UL /** < 15.63KHz Sweep Freq of the Frequecny Spread Spectrum */
#define ADI_PMIC_SWEEP_FREQ_20_83_KHz   3UL /** < 20.83KHz Sweep Freq of the Frequecny Spread Spectrum */
#define ADI_PMIC_SWEEP_FREQ_25_KHz      4UL /** < 25KHz Sweep Freq of the Frequecny Spread Spectrum */
#define ADI_PMIC_SWEEP_FREQ_31_25_KHz   5UL /** < 31.25KHz Sweep Freq of the Frequecny Spread Spectrum */
#define ADI_PMIC_SWEEP_FREQ_41_67_KHz   6UL /** < 41.67KHz Sweep Freq of the Frequecny Spread Spectrum */
#define ADI_PMIC_SWEEP_FREQ_62_5_KHz    7UL /** < 62.5KHz Sweep Freq of the Frequecny Spread Spectrum */
#define ADI_PMIC_SWEEP_FREQ_INVALID     8UL /** < Maximum value that the user can enter for Sweep Freq */
typedef uint32_t adi_pmic_sweep_freq_t;

/** Possible PMIC Error Codes */
typedef enum {
    ADI_PMIC_SUCCESS = 0,                   /**< ok */
    ADI_PMIC_FAIL = -1,                     /**< Generic failure code */
    ADI_PMIC_PARAMETER_ERROR = -3,          /**< Parameter validation failed */
} adi_pmic_err_t;

/** QA Watchdog timer status register */
typedef struct {
    uint32_t fault_counter;                  /**< The current number of QA watchdog fault counter */
    uint32_t bad_answer;                     /**< A flag to indicate a bad answer to the QA watchdog */
    uint32_t single_fail;                    /**< A flag to indicate a bad watchdog feed to QA watchdog */
} adi_pmic_qa_status_t;

/** QA Watchdog timer control register */
typedef struct {
    uint32_t fast_window;                   /**< Set the fast window of the QA watchdog */
    uint32_t slow_window;                   /**< Set the slow window of the QA watchdog */
    uint32_t fault_threshold;               /**< If the fault counter >= fault threshold, a fault event happens */
    uint32_t pre_scale;                     /**< Set the scale factor which is used to caluclate the fast and slow windows */
    uint32_t enable;                        /**< Enable or disable the QA watchdog */
} adi_pmic_qa_ctrl_t;

/** Freq Spread Spectrum config register */
typedef struct {
    uint32_t enable;                        /**< Enable the Frequency Spread Spectrum 0:Disable; 1:Enabled */
    adi_pmic_sweep_depth_t sweep_depth;     /**< Sweep Depth */
    adi_pmic_sweep_freq_t sweep_freq;       /**< Sweep Freq */
    uint32_t sync_en;                       /**< Enable Sync Function 0:Disabled; 1:Enabled and pin direction determined by sync_dir*/
    uint32_t sync_div;                      /**< Setting frequency on SYNC Pin when it configured as output 0:fsw; 1:fsw/5 */
    uint32_t sync_dir;                      /**< Setting SYNC Pin Direction 0: Input; 1: Output */
} adi_pmic_freq_config_t;

#define ADI_PMIC_FAULT_WINDOW    0x00UL     /** <Define for setting the Fault window */
#define ADI_PMIC_WARN_WINDOW     0x01UL     /** <Define for setting the warn window */
typedef uint32_t adi_pmic_warn_fault_window_t;

#define ADI_PMIC_FEEDBACK1       0x00UL
#define ADI_PMIC_FEEDBACK2       0x01UL
#define ADI_PMIC_FEEDBACK3       0x02UL
#define ADI_PMIC_FEEDBACK4       0x03UL
#define ADI_PMIC_FEEDBACK5       0x04UL
#define ADI_PMIC_FEEDBACK6       0x05UL
#define ADI_PMIC_FEEDBACK7       0x06UL
#define ADI_PMIC_FEEDBACK8       0x07UL
#define ADI_PMIC_FEEDBACK9       0x08UL
#define ADI_PMIC_FEEDBACK10      0x09UL
#define ADI_PMIC_FEEDBACK11      0x0AUL
#define ADI_PMIC_FEEDBACK12      0x0BUL
#define ADI_PMIC_VM0             0x0CUL
#define ADI_PMIC_VM1             0x0DUL
#define ADI_PMIC_INVALID_VOLTAGE 0x0EUL
typedef uint32_t adi_pmic_voltages_t;

/** Warn/Fault Window setup */
typedef struct {
    adi_pmic_warn_fault_window_t warnWindow;        /** <Modify the warn window or the fault window 0: faultwindow; 1: warnWindow */
    adi_pmic_threshold_values_t thresholdLevels;    /** <The threshold to set the window to */
    adi_pmic_blank_times_t blankTime;               /** <The blank time to set the window to */
} adi_pmic_warn_fault_settings_t;

/****************************** FUNCTIONS ******************************/

/**
* The recommended sequence for powering up an ADAR6901/2 device.
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
adi_pmic_err_t adi_pmic_PowerADAR690x(uint8_t pmic_num);

/**
* Read the ID of the PMIC
*/
adi_pmic_err_t adi_pmic_ReadChipId(uint8_t pmic_num, uint32_t * id);

/**
* Set the ctrl register of the QA WDT
* @param[in] ctrl - structure of the ctrl register for the QA WDT
*/
adi_pmic_err_t adi_pmic_SetQaWdCtrl(uint8_t pmic_num, adi_pmic_qa_ctrl_t ctrl);

/**
* Get the ctrl register of the QA WDT
* @param[in] ctrl - structure of the ctrl register for the QA WDT
*/
adi_pmic_err_t adi_pmic_GetQaWdCtrl(uint8_t pmic_num, adi_pmic_qa_ctrl_t * ctrl);

/**
* Get the status of the QA Watchdog
* @param[out] status - structure of the current state of the QA WDT
*/
adi_pmic_err_t adi_pmic_GetQaWdStatus(uint8_t pmic_num, adi_pmic_qa_status_t * status);

/**
* Service the QA watchdog. The processor calls this functions which reads
* the token and writes back the answer
*/
adi_pmic_err_t adi_pmic_ServiceQaWatchdog(uint8_t pmic_num);

/**
* Set the voltage level for LOD1 and LDO2
*
* @param[in] ldo - the ldo enum
* @param[in] vout - the selected voltage
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
adi_pmic_err_t adi_pmic_SetLdoOneTwoVout(uint8_t pmic_num, adi_pmic_ldo_selection_t ldo, adi_pmic_ldo_1_2_voltages_t vout);

/**
* Get the voltage level for LOD1 and LDO2
*
* @param[in] ldo - the ldo enum
* @param[out] vout - the selected voltage
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
adi_pmic_err_t adi_pmic_GetLdoOneTwoVout(uint8_t pmic_num, adi_pmic_ldo_selection_t ldo, adi_pmic_ldo_1_2_voltages_t * vout);

/**
* Set the voltage level for LOD3, LDO4 and LDO5
*
* @param[in] ldo - the ldo enum
* @param[in] vout - the selected voltage
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
adi_pmic_err_t adi_pmic_SetLdoThreeFourFiveVout(uint8_t pmic_num, adi_pmic_ldo_selection_t ldo, adi_pmic_ldo_3_4_5_voltages_t vout);

/**
* Get the voltage level for LOD3, LDO4 and LDO5
*
* @param[in] ldo - the ldo enum
* @param[out] vout - the selected voltage
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
adi_pmic_err_t adi_pmic_GetLdoThreeFourFiveVout(uint8_t pmic_num, adi_pmic_ldo_selection_t ldo, adi_pmic_ldo_3_4_5_voltages_t * vout);

/**
* Set the voltage level for LOD6 and LDO7
*
* @param[in] ldo - the ldo enum
* @param[in] vout - the selected voltage
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
adi_pmic_err_t adi_pmic_SetLdoSixSevenVout(uint8_t pmic_num, adi_pmic_ldo_selection_t ldo, adi_pmic_ldo_6_7_voltages_t vout);

/**
* Get the voltage level for LOD6 and LDO7
*
* @param[in] ldo - the ldo enum
* @param[out] vout - the selected voltage
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
adi_pmic_err_t adi_pmic_GetLdoSixSevenVout(uint8_t pmic_num, adi_pmic_ldo_selection_t ldo, adi_pmic_ldo_6_7_voltages_t * vout);

/**
* Set the voltage level for Buck1
*
* @param[in] vout - the selected voltage
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
adi_pmic_err_t adi_pmic_SetBuckOneVout(uint8_t pmic_num, uint32_t vout);

/**
* Get the voltage level for Buck1
*
* @param[out] vout - the selected voltage
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
adi_pmic_err_t adi_pmic_GetBuckOneVout(uint8_t pmic_num, uint32_t * vout);

/**
* Set the voltage level for Buck4
*
* @param[in] vout - the selected voltage
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
adi_pmic_err_t adi_pmic_SetBuckFourVout(uint8_t pmic_num, adi_pmic_buck_4_voltages_t vout);

/**
* Get the voltage level for Buck4
*
* @param[out] vout - the selected voltage
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
adi_pmic_err_t adi_pmic_GetBuckFourVout(uint8_t pmic_num, adi_pmic_buck_4_voltages_t * vout);

/**
* Set the warning thresholds for the voltage supply
*
* @param[in] faultwindowOffset - The offset into the register to get the correct voltage supply
* @param[in] thresholdlevel - window percentages for threshold levels
* @param[in] blankTime - Voltage monitor blank time
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
/*adi_pmic_err_t adi_pmic_SetWarnWindow(adi_pmic_warn_fault_offset_t warnWindowOffset,
                                      adi_pmic_threshold_values_t thresholdlevel, 
                                      adi_pmic_blank_times_t blankTime);*/

adi_pmic_err_t adi_pmic_SetWarnFaultWindow(uint8_t pmic_num, adi_pmic_voltages_t voltage, adi_pmic_warn_fault_settings_t cfg);
/**
* Get the warning thresholds register value
*
* @param[out] res - The contents of the Warn Window register
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
adi_pmic_err_t adi_pmic_GetWarnFaultWindow(uint8_t pmic_num, adi_pmic_voltages_t voltage, adi_pmic_warn_fault_settings_t * cfg);

/**
* Set the DVS interval time for either Buck1 or BUCK4
*
* @param[in] sel - which buck to select
* @param[in] interval - the interval time in US
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
adi_pmic_err_t adi_pmic_SetBuckDVS(uint8_t pmic_num, adi_pmic_buck_sel_t sel, adi_pmic_dvs_interval_times_t interval);

/**
* Get the DVS interval time for either Buck1 or BUCK4
*
* @param[in] sel - which buck to select
* @param[in] interval - the interval time in US
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
adi_pmic_err_t adi_pmic_GetBuckDVS(uint8_t pmic_num, adi_pmic_buck_sel_t sel, adi_pmic_dvs_interval_times_t * interval);

/**
* Set the config register for the Frequency Spread Sprectrum
*
* @param[in] cfg - the config structure
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
adi_pmic_err_t adi_pmic_SetFreqSpreadCfg(uint8_t pmic_num, adi_pmic_freq_config_t cfg);

/**
* Get the config register for the Frequency Spread Sprectrum
*
* @param[out] cfg - the config structure
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
adi_pmic_err_t adi_pmic_GetFreqSpreadCfg(uint8_t pmic_num, adi_pmic_freq_config_t * cfg);

/**
 * Write a word to the PMIC address space.
 *
 * @param[in] addr 32-bit address to write to in the PMIC address space
 * @param[in] value 32-bit value to write
 *
 */
void adi_pmic_Write(uint8_t pmic_num, uint32_t addr, uint32_t value);

/**
 * Read a word from the PMIC address space.
 *
 * @param[in] addr 32-bit address to write to in the PMIC address space
 * @param[out] value 32-bit value to write
 */
uint32_t adi_pmic_Read(uint8_t pmic_num, uint32_t addr);

#endif                          /* __ADI_PMIC_DRIVER_H__ */
