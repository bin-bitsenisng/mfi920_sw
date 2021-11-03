/* pmic_driver.c
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

#include "adi_pmic_driver.h"
#include "localdefs.h"

#define CHIP_INFO                       0x0008UL
#define QA_WD_CTRL                      0x8094UL
#define QA_WD_WINDOW                    0x8098UL
#define QA_WD_STATUS                    0x80A4UL
#define QA_WD_ANSWER                    0x0020UL
#define QA_WD_TOKEN                     0x0024UL

#define VM0_VM1_OFFSET                  0x03UL      /** < offset to the vm0 and vm1 bits */
#define QA_WD_FAULT_COUNTER_OFFSET      0x02UL      /** < offset to the fault counter bits in the QA watchdog status register */
#define QA_WD_BAD_ANSWER_OFFSET         0x01UL      /** < offset to the bad answer bits in the QA watchdog status register */
#define QA_WD_SINGLE_FAIL_OFFSET        0x00UL      /** < offset to the single fail bits in the QA watchdog status register */
#define QA_WD_EN_CTRL_OFFSET            0x01UL      /** < offset to the enable bits in the QA watchdog control register */
#define QA_WD_PRE_SCALE_OFFSET          0x01UL      /** < offset to the pre scale bits in the QA watchdog control register */
#define QA_WD_FAULT_THRESHOLD_OFFSET    0x03UL      /** < offset to the fault threshold bits in the QA watchdog control register */
#define QA_WD_LOCK_OFFSET               0x07UL      /** < offset to the lock bits in the QA watchdog control register */
#define QA_WD_FAST_WINDOW_OFFSET        0x10UL      /** < offset to the fast window bits in the QA watchdog window register */
#define BUCK1_DVS_INTERVAL_OFFSET       0x02UL      /** < offset to Buck1 DVS Interval */
#define BUCK4_DVS_INTERVAL_OFFSET       0x00UL      /** < offset to Buck4 DVS Interval */
#define FS_ENABLE_OFFSET                0x09UL      /** < offset to Frequency spread enable bit */
#define FS_SD_OFFSET                    0x06UL      /** < offset to Frequency spread sweep depth bits */
#define FS_SF_OFFSET                    0x03UL      /** < offset to Frequency spread sweep freq bits */
#define FS_SYNC_EN_OFFSET               0x02UL      /** < offset to Frequency spread sync enable bit */
#define FS_SYNC_DIV_OFFSET              0x01UL      /** < offset to Frequency spread sync div bit */

#define VM0_VM1_BIT_MASK                0x07UL      /** < bit mask for VM0 VM1 */
#define VOUT_BIT_MASK                   0x07UL      /** < bit mask for vout */
#define FB_BIT_MASK                     0x0FUL      /** < bit mask for FeedBack registers */
#define WARN_WINDOW_BIT_MASK            0x03UL      /** < bit mask for Warn Windows registers */
#define QA_WD_FAULT_COUNTER_BIT_MASK    0x07UL      /** < bit mask for fault counter */
#define QA_WD_BAD_ANSWER_BIT_MASK       0x01UL      /** < bit mask for bad answer counter */
#define QA_WD_SINGLE_FAIL_BIT_MASK      0x01UL      /** < bit mask for single fail */
#define QA_WD_EN_CTRL_BIT_MASK          0x01UL      /** < bit mask for fault threshold */
#define QA_WD_PRE_SCALE_BIT_MASK        0x03UL      /** < bit mask for pre scale */
#define QA_WD_FAULT_THRESHOLD_BIT_MASK  0x0FUL      /** < bit mask for fault threshold */
#define QA_WD_LOCK_BIT_MASK             0x01UL      /** < bit mask for lock bit */
#define QA_WD_SLOW_WINDOW_BIT_MASK      0xFFFFUL    /** < bit mask for slow window */
#define QA_WD_FAST_WINDOW_BIT_MASK      0xFFFFUL    /** < bit mask for fast window */
#define BUCK1_DVS_INTERVAL_MASK         0x0CUL      /** < bit mask for Buck1 DVS Interval */
#define BUCK4_DVS_INTERVAL_MASK         0x03UL      /** < bit mask for Buck4 DVS Interval */
#define FS_ENABLE_MASK                  0x200UL     /** < bit mask for Frequency Spread Enable */
#define FS_SD_MASK                      0x1C0UL     /** < bit mask for Frequency Spread sweep depth */
#define FS_SF_MASK                      0x38UL      /** < bit mask for Frequency Spread sweep freq */
#define FS_SYNC_EN_MASK                 0x04UL      /** < bit mask for Frequency Spread sync Enable */
#define FS_SYNC_DIV_MASK                0x02UL      /** < bit mask for Frequency Spread sync pin */

#define BUCK_ONE_LOWER_LIMIT            800UL       /** <Lower Limit of 800mV can be selected for BUCK1 volatge */
#define BUCK_ONE_UPPER_LIMIT            1400UL      /** <Upper Limit of 1400mV can be selected for BUCK1 volatge */

#define CHIP_ID                         0x5140

/**
* Unlocks the pmic by writing the unlock key to the unlock address
*
* @param[in] unlock - true to unlock the PMIC, false to lock it
* @param[in] addr_unlock - the unlock address
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
static adi_pmic_err_t adi_pmic_unlock(uint8_t pmic_num, bool unlock, uint32_t addr_unlock);

/**
* Set the warning thresholds for the correct voltage supply for either the warning window or the fault window
*
* @param[in] address - The address of either the fault register or the warn register
* @param[in] voltage - The voltage to change
* @param[in] thresholdLevel - window percentages for thereshold levels
* @param[in] blankTime - Voltage monitor blank time
* @return ADI_PMIC_SUCCESS (0) for success, ADI_PMIC_FAIL on failure
*/
static adi_pmic_err_t adi_pmic_warn_fault_window(uint8_t pmic_num,uint32_t address, uint32_t voltage, adi_pmic_threshold_values_t thresholdLevel, adi_pmic_blank_times_t blankTime);

/**
* Locks/Unlocks all the registers of QA watchdog. If locked then user can not write to
* any of the registers except QA_WD_ANSWER and QA_WD_TOKEN
*
* @param[in] lock - true to lock QA WDT and false to unlock
*/
static adi_pmic_err_t adi_pmic_qa_wd_unlock(uint8_t pmic_num, bool unlock);

/**
* Set the fast and slow window for the QA watchdog timer
* @param[in] fast_window - Set the fast window for the QA watchdog
* @param[in] slow_window - Set the slow window for the QA watchdog
*/
static adi_pmic_err_t adi_pmic_set_qa_wd_slow_fast_window(uint8_t pmic_num,uint32_t fast_window, uint32_t slow_window);

/**
* Set the control window for the QA Watchdog timer
* @param[in] fault - Set the fault threshold of the QA watchdog
* @param[in] pre_scale - Set the scale factor for the QA watchdog
* @param[in] enable - QA watchdog enable
*/
static adi_pmic_err_t adi_pmic_set_qa_wd_ctrl(uint8_t pmic_num,uint32_t fault, uint32_t pre_scale, uint32_t enable);

/**
* Write the answer from the token read back, down to the QA watchdog
* @param[out] answer - 32 bit answer
*/
static adi_pmic_err_t adi_pmic_WriteQaWdAnswer(uint8_t pmic_num,uint32_t answer);

/**
* Read the token number that the user also has to calculate from the QA watchdog
* @param[out] token - number between 0 and 15
*/
static adi_pmic_err_t adi_pmic_ReadQaWdToken(uint8_t pmic_num,uint32_t * token);

/**
* Unlock the PMIC and the QA watchdog timer
* @param[out] unlock - true : unlock, false  : lock
*/
static adi_pmic_err_t adi_pmic_enable(uint8_t pmic_num, bool unlock);

/****************************** FUNCTIONS ******************************/
adi_pmic_err_t adi_pmic_ReadChipId(uint8_t pmic_num, uint32_t * id)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t reg = 0x00UL;
    uint32_t chip = 0x00UL;

    comment("---> Entering function adi_pmic_ReadChipId");

    if (id == NULL) {
        error_code = ADI_PMIC_FAIL;
        comment("---> Chip Id Pointer = NULL");
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        reg = adi_pmic_Read(pmic_num, CHIP_INFO);
        chip = reg & 0xFFFFUL;

        *id = chip;
    }

    comment("---> Exiting function adi_pmic_ReadChipId");

    return error_code;
}

adi_pmic_err_t adi_pmic_SetQaWdCtrl(uint8_t pmic_num, adi_pmic_qa_ctrl_t ctrl)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;

    comment("---> Entering function adi_pmic_SetupQaWindow");

    error_code = adi_pmic_enable(pmic_num, true);

    if (error_code == ADI_PMIC_SUCCESS) {
        adi_pmic_set_qa_wd_ctrl(pmic_num, ctrl.fault_threshold, ctrl.pre_scale, ctrl.enable);
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        adi_pmic_set_qa_wd_slow_fast_window(pmic_num, ctrl.fast_window, ctrl.slow_window);
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        error_code = adi_pmic_enable(pmic_num, false);
    }

    comment("---> Exiting function adi_pmic_SetupQaWindow");

    return error_code;
}

adi_pmic_err_t adi_pmic_GetQaWdCtrl(uint8_t pmic_num, adi_pmic_qa_ctrl_t * ctrl)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t reg = 0x00UL;

    comment("---> Entering function adi_pmic_GetQaWdCtrl");

    if (ctrl == NULL) {
        error_code = ADI_PMIC_FAIL;
        comment("---> QA watchdog Ctrl Pointer = NULL");
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        /* Read back contents of control register and populate the structure */
        reg = adi_pmic_Read(pmic_num, QA_WD_CTRL);
        ctrl->enable = (uint32_t) (reg & QA_WD_EN_CTRL_BIT_MASK);
        ctrl->pre_scale = (uint32_t) ((reg >> QA_WD_PRE_SCALE_OFFSET) & QA_WD_PRE_SCALE_BIT_MASK);
        ctrl->fault_threshold = (uint32_t) ((reg >> QA_WD_FAULT_THRESHOLD_OFFSET) & QA_WD_FAULT_THRESHOLD_BIT_MASK);
        reg = adi_pmic_Read(pmic_num, QA_WD_WINDOW);
        ctrl->slow_window = (uint32_t) (reg & QA_WD_SLOW_WINDOW_BIT_MASK);
        ctrl->fast_window = (uint32_t) ((reg >> QA_WD_FAST_WINDOW_OFFSET) & QA_WD_FAST_WINDOW_BIT_MASK);
    }

    comment("---> Exiting function adi_pmic_GetQaWdCtrl");
    return error_code;
}

adi_pmic_err_t adi_pmic_SetFreqSpreadCfg(uint8_t pmic_num, adi_pmic_freq_config_t cfg)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t reg = 0x00UL;
    uint32_t readback = 0x00UL;

    comment("---> Entering function adi_pmic_SetFreqSpreadCfg");

    error_code = adi_pmic_enable(pmic_num, true);

    if ((cfg.sweep_depth >= ADI_PMIC_SWEEP_DEPTH_INVALID) || (cfg.sweep_freq >= ADI_PMIC_SWEEP_FREQ_INVALID)) {
        error_code = ADI_PMIC_PARAMETER_ERROR;
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        reg = (cfg.enable & ~FS_ENABLE_MASK) << FS_ENABLE_OFFSET;
        reg |= (cfg.sweep_depth & ~FS_SD_MASK) << FS_SD_OFFSET;
        reg |= (cfg.sweep_freq & ~FS_SF_MASK) << FS_SF_OFFSET;
        reg |= (cfg.sync_en & ~FS_SYNC_EN_MASK) << FS_SYNC_EN_OFFSET;
        reg |= (cfg.sync_div & ~FS_SYNC_DIV_MASK) << FS_SYNC_DIV_OFFSET;
        reg |= cfg.sync_dir;
    }

    /* Write this value down to the PMIC */
    adi_pmic_Write(pmic_num, ADI_PMIC_FREQ_CONFIG, reg);

    /* Read back and compare the values to ensure successful read write */
    readback = adi_pmic_Read(pmic_num, ADI_PMIC_FREQ_CONFIG);
    if (reg != readback) {
        error_code = ADI_PMIC_FAIL;
        comment("---> ERROR: Read value and Write values are different");
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        error_code = adi_pmic_enable(pmic_num, false);
    }

    comment("---> Exiting function adi_pmic_SetFreqSpreadCfg");
    return error_code;
}

adi_pmic_err_t adi_pmic_GetFreqSpreadCfg(uint8_t pmic_num, adi_pmic_freq_config_t * cfg)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t reg = 0x00UL;

    comment("---> Entering function adi_pmic_GetFreqSpreadCfg");

    error_code = adi_pmic_enable(pmic_num, true);

    if (error_code == ADI_PMIC_SUCCESS) {
        reg = adi_pmic_Read(pmic_num, ADI_PMIC_FREQ_CONFIG);

        cfg->enable = ((reg & FS_ENABLE_MASK) >> FS_ENABLE_OFFSET);
        cfg->sweep_depth = ((reg & FS_SD_MASK) >> FS_SD_OFFSET);
        cfg->sweep_freq = ((reg & FS_SF_MASK) >> FS_SF_OFFSET);
        cfg->sync_en = ((reg & FS_SYNC_EN_MASK) >> FS_SYNC_EN_OFFSET);
        cfg->sync_div = ((reg & FS_SYNC_DIV_MASK) >> FS_SYNC_DIV_OFFSET);
        cfg->sync_dir = reg & 0x01UL;
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        error_code = adi_pmic_enable(pmic_num, false);
    }

    comment("---> Exiting function adi_pmic_GetFreqSpreadCfg");
    return error_code;
}

adi_pmic_err_t adi_pmic_GetQaWdStatus(uint8_t pmic_num, adi_pmic_qa_status_t * status)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t reg = 0x00UL;

    comment("---> Entering function adi_pmic_GetWdStatus");

    if (status == NULL) {
        error_code = ADI_PMIC_FAIL;
        comment("---> QA watchdog Status Pointer = NULL");
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        /* Read back contents of status register and populate the structure */
        reg = adi_pmic_Read(pmic_num, QA_WD_STATUS);
        status->fault_counter = (uint32_t) ((reg >> QA_WD_FAULT_COUNTER_OFFSET) & QA_WD_FAULT_COUNTER_BIT_MASK);
        status->bad_answer = (uint32_t) ((reg >> QA_WD_BAD_ANSWER_OFFSET) & QA_WD_BAD_ANSWER_BIT_MASK);
        status->single_fail = (uint32_t) (reg & QA_WD_SINGLE_FAIL_BIT_MASK);
    }

    comment("---> Exiting function adi_pmic_GetWdStatus");
    return error_code;
}

adi_pmic_err_t adi_pmic_ServiceQaWatchdog(uint8_t pmic_num)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    static const uint32_t qa_wdt_lookup[] = {
        0x000FF0FF, 0xE3EC131C, 0x9B946B64, 0x78778887,
        0x5659A6A9, 0xB5BA454A, 0xCDC23D32, 0x2E21DED1,
        0x2D22DDD2, 0xCEC13E31, 0xB6B94649, 0x555AA5AA,
        0x7B748B84, 0x98976867, 0xE0EF101F, 0x030CF3FC
    };
    uint32_t token = 0x00;
    uint32_t answer = 0x00;

    comment("---> Entering function adi_pmic_ServiceQaQatchdog");

    /* Read back the token */
    error_code = adi_pmic_ReadQaWdToken(pmic_num, &token);

    if (error_code == ADI_PMIC_SUCCESS) {
        /* Calculate the Answer based on the Token returned */
        answer = qa_wdt_lookup[token];

        /* Write the answer down to the PMIC to service the QA qatchdog */
        error_code = adi_pmic_WriteQaWdAnswer(pmic_num, answer);
    }

    comment("---> Exiting function adi_pmic_ServiceQaQatchdog");
    return error_code;

}

adi_pmic_err_t adi_pmic_SetLdoOneTwoVout(uint8_t pmic_num, adi_pmic_ldo_selection_t ldo, adi_pmic_ldo_1_2_voltages_t vout)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t read_reg = 0xFFUL;
    uint32_t reg = 0x00UL;

    comment("---> Entering function adi_pmic_SetLdoOneTwoVout");

    error_code = adi_pmic_enable(pmic_num, true);

    if (error_code == ADI_PMIC_SUCCESS) {
        if (ldo == ADI_PMIC_LDO_ONE) {
            reg = ADI_PMIC_LDO_ONE_ADDRESS;
        } else if (ldo == ADI_PMIC_LDO_TWO) {
            reg = ADI_PMIC_LDO_TWO_ADDRESS;
        } else {
            comment("ERROR: INVALID LDO ADDRESS");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        if (vout >= ADI_PMIC_LDO_1_2_INVALID) {
            comment("ERROR: INVALID LDO SETTING");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        adi_pmic_Write(pmic_num, reg, vout);
        read_reg = adi_pmic_Read(pmic_num, reg);
        comment("Readback value is: %x", read_reg);

        if (read_reg != vout) {
            comment("ERROR: Readback is not the same as value written down");
            error_code = ADI_PMIC_FAIL;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        error_code = adi_pmic_enable(pmic_num, false);
    }

    comment("---> Exiting function adi_pmic_SetLdoOneTwoVout");
    return error_code;
}

adi_pmic_err_t adi_pmic_GetLdoOneTwoVout(uint8_t pmic_num, adi_pmic_ldo_selection_t ldo, adi_pmic_ldo_1_2_voltages_t * vout)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t reg = 0x00UL;

    comment("---> Entering function adi_pmic_GetLdoOneTwoVout");

    if (vout == NULL) {
        error_code = ADI_PMIC_FAIL;
        comment("---> Vout Pointer = NULL");
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        if (ldo == ADI_PMIC_LDO_ONE) {
            reg = ADI_PMIC_LDO_ONE_ADDRESS;
        } else if (ldo == ADI_PMIC_LDO_TWO) {
            reg = ADI_PMIC_LDO_TWO_ADDRESS;
        } else {
            comment("ERROR: INVALID LDO SELECTED");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        *vout = adi_pmic_Read(pmic_num, reg);
    }

    comment("---> Exiting function adi_pmic_GetLdoOneTwoVout");

    return error_code;
}

adi_pmic_err_t adi_pmic_SetLdoThreeFourFiveVout(uint8_t pmic_num, adi_pmic_ldo_selection_t ldo, adi_pmic_ldo_3_4_5_voltages_t vout)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t read_reg = 0xFFUL;
    uint32_t reg = 0x00UL;

    comment("---> Entering function adi_pmic_SetLdoThreeFourFiveVout");

    error_code = adi_pmic_enable(pmic_num, true);

    if (error_code == ADI_PMIC_SUCCESS) {
        if (ldo == ADI_PMIC_LDO_THREE) {
            reg = ADI_PMIC_LDO_THREE_ADDRESS;
        } else if (ldo == ADI_PMIC_LDO_FOUR) {
            reg = ADI_PMIC_LDO_FOUR_ADDRESS;
        } else if (ldo == ADI_PMIC_LDO_FIVE) {
            reg = ADI_PMIC_LDO_FIVE_ADDRESS;
        } else {
            comment("ERROR: INVALID LDO SELECTED");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        if (vout >= ADI_PMIC_LDO_3_4_5_INVALID) {
            comment("ERROR: INVALID LDO VOUT SET");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        adi_pmic_Write(pmic_num, reg, vout);
        read_reg = adi_pmic_Read(pmic_num, reg);
        comment("Readback value is: %x", read_reg);

        if (read_reg != vout) {
            comment("ERROR: Readback is not the same as value written down");
            error_code = ADI_PMIC_FAIL;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        error_code = adi_pmic_enable(pmic_num, false);
    }

    comment("---> Exiting function adi_pmic_SetLdoThreeFourFiveVout");

    return error_code;
}

adi_pmic_err_t adi_pmic_GetLdoThreeFourFiveVout(uint8_t pmic_num, adi_pmic_ldo_selection_t ldo, adi_pmic_ldo_3_4_5_voltages_t * vout)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t reg = 0x00UL;

    comment("---> Entering function adi_pmic_GetLdoThreeFourFiveVout");

    if (vout == NULL) {
        error_code = ADI_PMIC_FAIL;
        comment("---> Vout Pointer = NULL");
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        if (ldo == ADI_PMIC_LDO_THREE) {
            reg = ADI_PMIC_LDO_THREE_ADDRESS;
        } else if (ldo == ADI_PMIC_LDO_FOUR) {
            reg = ADI_PMIC_LDO_FOUR_ADDRESS;
        } else if (ldo == ADI_PMIC_LDO_FIVE) {
            reg = ADI_PMIC_LDO_FIVE_ADDRESS;
        } else {
            comment("ERROR: INVALID LDO SELECTED");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        *vout = adi_pmic_Read(pmic_num, reg);
    }

    comment("---> Exiting function adi_pmic_GetLdoThreeFourFiveVout");

    return error_code;
}

adi_pmic_err_t adi_pmic_SetLdoSixSevenVout(uint8_t pmic_num, adi_pmic_ldo_selection_t ldo, adi_pmic_ldo_6_7_voltages_t vout)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t read_reg = 0xFFUL;
    uint32_t reg = 0x00UL;

    comment("---> Entering function adi_pmic_SetLdoSixSevenVout");

    error_code = adi_pmic_enable(pmic_num, true);

    if (error_code == ADI_PMIC_SUCCESS) {
        if (ldo == ADI_PMIC_LDO_SIX) {
            reg = ADI_PMIC_LDO_SIX_ADDRESS;
        } else if (ldo == ADI_PMIC_LDO_SEVEN) {
            reg = ADI_PMIC_LDO_SEVEN_ADDRESS;
        } else {
            comment("ERROR: INVALID LDO ADDRESS");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        if (vout >= ADI_PMIC_LDO_6_7_INVALID) {
            comment("ERROR: INVALID LDO SETTING");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        adi_pmic_Write(pmic_num, reg, vout);
        read_reg = adi_pmic_Read(pmic_num, reg);
        comment("Readback value is: %x", read_reg);

        if (read_reg != vout) {
            comment("ERROR: Readback is not the same as value written down");
            error_code = ADI_PMIC_FAIL;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        error_code = adi_pmic_enable(pmic_num, false);
    }

    comment("---> Exiting function adi_pmic_SetLdoSixSevenVout");
    return error_code;
}

adi_pmic_err_t adi_pmic_GetLdoSixSevenVout(uint8_t pmic_num, adi_pmic_ldo_selection_t ldo, adi_pmic_ldo_6_7_voltages_t * vout)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t reg = 0x00UL;

    comment("---> Entering function adi_pmic_GetLdoSixSevenVout");

    if (vout == NULL) {
        error_code = ADI_PMIC_FAIL;
        comment("---> Vout Pointer = NULL");
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        if (ldo == ADI_PMIC_LDO_SIX) {
            reg = ADI_PMIC_LDO_SIX_ADDRESS;
        } else if (ldo == ADI_PMIC_LDO_SEVEN) {
            reg = ADI_PMIC_LDO_SEVEN_ADDRESS;
        } else {
            comment("ERROR: INVALID LDO SELECTED");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        *vout = adi_pmic_Read(pmic_num, reg);
    }

    comment("---> Exiting function adi_pmic_GetLdoSixSevenVout");

    return error_code;
}

adi_pmic_err_t adi_pmic_SetBuckOneVout(uint8_t pmic_num, uint32_t vout)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t read_reg = 0xFFUL;
    uint32_t regValue = 0x00;

    comment("---> Entering function adi_pmic_SetBuckOneVout");

    error_code = adi_pmic_enable(pmic_num, true);

    if (error_code == ADI_PMIC_SUCCESS) {
        if (vout > BUCK_ONE_UPPER_LIMIT) {
            comment("ERROR: INVALID UPPER BUCK1 SETTING FOR C1 PMIC");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        } else if (vout < BUCK_ONE_LOWER_LIMIT) {
            comment("ERROR: INVALID LOWER BUCK1 SETTING FOR C1 PMIC");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        }
    }
    //Remove any decimal points as steps of 10mv are required
    regValue = (uint32_t) ((vout) / 10UL) * 10UL;
    regValue = (regValue - 800UL) / 10UL;

    if (error_code == ADI_PMIC_SUCCESS) {
        /* The address and data are valid so write to the PMIC */
        adi_pmic_Write(pmic_num, ADI_PMIC_BUCK_ONE_VOUT_SETTING_ADDRESS, regValue);
        read_reg = (adi_pmic_Read(pmic_num, ADI_PMIC_BUCK_ONE_VOUT_SETTING_ADDRESS)) & 0x3FUL;
        comment("Readback value is: %x", read_reg);

        if (read_reg != regValue) {
            comment("ERROR: Readback is not the same as value written down");
            error_code = ADI_PMIC_FAIL;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        error_code = adi_pmic_enable(pmic_num, false);
    }

    comment("---> Exiting function adi_pmic_SetBuckOneVout");

    return error_code;
}

adi_pmic_err_t adi_pmic_GetBuckOneVout(uint8_t pmic_num, uint32_t * vout)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;

    comment("---> Entering function adi_pmic_GetBuckOneVout");

    if (vout == NULL) {
        error_code = ADI_PMIC_FAIL;
        comment("---> Vout Pointer = NULL");
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        *vout = (adi_pmic_Read(pmic_num, ADI_PMIC_BUCK_ONE_VOUT_ADDRESS) & 0x3FUL);
        // Convert it to mV and return it
        *vout = (*vout * 10UL) + 800UL;
    }

    comment("---> Exiting function adi_pmic_GetBuckOneVout");

    return error_code;
}

adi_pmic_err_t adi_pmic_SetBuckFourVout(uint8_t pmic_num, adi_pmic_buck_4_voltages_t vout)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t read_reg = 0xFFUL;

    comment("---> Entering function adi_pmic_SetBuckFourVout");

    error_code = adi_pmic_enable(pmic_num, true);

    if (error_code == ADI_PMIC_SUCCESS) {
        if (vout >= ADI_PMIC_BUCK_4_INVALID) {
            comment("ERROR: INVALID BUCK4 SETTING FOR C1 PMIC");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        /* The address and data are valid so write to the PMIC */
        adi_pmic_Write(pmic_num, ADI_PMIC_BUCK_FOUR_ADDRESS, vout);
        read_reg = adi_pmic_Read(pmic_num, ADI_PMIC_BUCK_FOUR_ADDRESS);
        comment("Readback value is: %x", read_reg);

        if (read_reg != vout) {
            comment("ERROR: Readback is not the same as value written down");
            error_code = ADI_PMIC_FAIL;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        error_code = adi_pmic_enable(pmic_num, false);
    }

    comment("---> Exiting function adi_pmic_SetBuckFourVout");

    return error_code;
}

adi_pmic_err_t adi_pmic_GetBuckFourVout(uint8_t pmic_num, adi_pmic_buck_4_voltages_t * vout)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;

    comment("---> Entering function adi_pmic_GetBuckFourVout");

    if (vout == NULL) {
        error_code = ADI_PMIC_FAIL;
        comment("---> Vout Pointer = NULL");
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        *vout = adi_pmic_Read(pmic_num, ADI_PMIC_BUCK_FOUR_ADDRESS);
    }

    comment("---> Exiting function adi_pmic_GetBuckFourVout");

    return error_code;
}

adi_pmic_err_t adi_pmic_SetBuckDVS(uint8_t pmic_num, adi_pmic_buck_sel_t sel, adi_pmic_dvs_interval_times_t interval)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t reg = 0x00UL;
    uint32_t x = 0x00UL;
    uint32_t y = 0x00UL;
    uint32_t mask = 0x00;
    uint32_t shift = 0x00;

    comment("---> Entering function adi_pmic_SetBuckDVS");

    error_code = adi_pmic_enable(pmic_num, true);

    if (error_code == ADI_PMIC_SUCCESS) {
        if (sel >= ADI_PMIC_INVALID_BUCK) {
            comment("ERROR: INVALID BUCK SELECTED");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        if (interval >= ADI_PMIC_INVALID_INTERVAL) {
            comment("ERROR: INVALID BUCK INTERVAL TIME SELECTED");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        reg = adi_pmic_Read(pmic_num, ADI_PMIC_BUCK_DVS_ADDRESS);
        if (sel == ADI_PMIC_BUCK1) {
            mask = BUCK1_DVS_INTERVAL_MASK;
            shift = BUCK1_DVS_INTERVAL_OFFSET;
        } else {
            mask = BUCK4_DVS_INTERVAL_MASK;
            shift = BUCK4_DVS_INTERVAL_OFFSET;
        }

        reg = adi_pmic_Read(pmic_num, ADI_PMIC_BUCK_DVS_ADDRESS);
        x = reg & (~(mask << shift));
        y = x | (interval << shift);
        adi_pmic_Write(pmic_num, ADI_PMIC_BUCK_DVS_ADDRESS, y);
    }

    /* Read back and compare the values to ensure successful read write */
    reg = adi_pmic_Read(pmic_num, ADI_PMIC_BUCK_DVS_ADDRESS);
    if (reg != y) {
        comment("ERROR: READ BACK VALUE NOT THE SAME AS WRITE VALUE");
        error_code = ADI_PMIC_FAIL;
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        error_code = adi_pmic_enable(pmic_num, false);
    }

    comment("---> Exiting function adi_pmic_SetBuckDVS");

    return error_code;
}

adi_pmic_err_t adi_pmic_GetBuckDVS(uint8_t pmic_num, adi_pmic_buck_sel_t sel, adi_pmic_dvs_interval_times_t * interval)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t reg = 0x00UL;

    comment("---> Entering function adi_pmic_GetBuckDVS");

    if (interval == NULL) {
        error_code = ADI_PMIC_FAIL;
        comment("---> interval Pointer = NULL");
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        reg = adi_pmic_Read(pmic_num, ADI_PMIC_BUCK_DVS_ADDRESS);
        if (sel == ADI_PMIC_BUCK1) {
            *interval = (reg & BUCK1_DVS_INTERVAL_MASK) >> BUCK1_DVS_INTERVAL_OFFSET;
        } else {
            *interval = reg & BUCK4_DVS_INTERVAL_MASK;
        }
    }

    comment("---> Exiting function adi_pmic_GetBuckDVS");

    return error_code;
}

adi_pmic_err_t adi_pmic_SetWarnFaultWindow(uint8_t pmic_num, adi_pmic_voltages_t voltage, adi_pmic_warn_fault_settings_t cfg)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t address = 0x00UL;

    comment("---> Entering function adi_pmic_SetWarnFaultWindow");

    error_code = adi_pmic_enable(pmic_num, true);

    switch (cfg.warnWindow) {
    case ADI_PMIC_FAULT_WINDOW:
        address = ADI_PMIC_FAULT_WINDOW_ADDRESS;
        break;
    case ADI_PMIC_WARN_WINDOW:
        address = ADI_PMIC_WARN_WINDOW_ADDRESS;
        break;
    default:
        comment("ERROR: INVALID WINDOW SELECTED");
        error_code = ADI_PMIC_PARAMETER_ERROR;
        break;
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        if (voltage >= ADI_PMIC_INVALID_VOLTAGE) {
            comment("ERROR: INVALID WINDOW SELECTED");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        if (cfg.blankTime >= ADI_PMIC_INVALID_BLANK_TIME) {
            comment("ERROR: INVALID BLANK TIME SELECTED");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        if (cfg.thresholdLevels >= ADI_PMIC_INVALID_THRESHOLD) {
            comment("ERROR: INVALID THRESHOLD LEVELS SELECTED");
            error_code = ADI_PMIC_PARAMETER_ERROR;
        }
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        error_code = adi_pmic_warn_fault_window(pmic_num, address, voltage, cfg.thresholdLevels, cfg.blankTime);
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        error_code = adi_pmic_enable(pmic_num, false);
    }

    comment("---> Exiting function adi_pmic_SetWarnFaultWindow");

    return error_code;
}

adi_pmic_err_t adi_pmic_GetWarnFaultWindow(uint8_t pmic_num, adi_pmic_voltages_t voltage, adi_pmic_warn_fault_settings_t * cfg)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t address = 0x00UL;
    uint32_t shift_bits = 0x00UL;
    uint32_t reg = 0x00UL;
    uint32_t x = 0x00UL;
    uint32_t voltage_blank_time_addr = 0x00UL;

    comment("---> Entering function adi_pmic_GetWarnFaultWindow");

    error_code = adi_pmic_enable(pmic_num, true);

    switch (cfg->warnWindow) {
    case ADI_PMIC_FAULT_WINDOW:
        address = ADI_PMIC_FAULT_WINDOW_ADDRESS;
        break;
    case ADI_PMIC_WARN_WINDOW:
        address = ADI_PMIC_WARN_WINDOW_ADDRESS;
        break;
    default:
        comment("ERROR: INVALID WINDOW SELECTED");
        error_code = ADI_PMIC_PARAMETER_ERROR;
        break;
    }

    reg = adi_pmic_Read(pmic_num, address);
    x = (reg >> (voltage * 2UL)) & WARN_WINDOW_BIT_MASK;
    cfg->thresholdLevels = x;

    switch ((uint32_t) voltage) {
    case ADI_PMIC_VM1:
        shift_bits = 24UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME0_ADDRESS;
        break;
    case ADI_PMIC_VM0:
        shift_bits = 20UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME0_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK12:
        shift_bits = 16UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME0_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK11:
        shift_bits = 24UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME1_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK10:
        shift_bits = 20UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME1_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK9:
        shift_bits = 16UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME1_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK8:
        shift_bits = 12UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME1_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK7:
        shift_bits = 8UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME1_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK6:
        shift_bits = 4UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME1_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK5:
        shift_bits = 0UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME1_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK4:
        shift_bits = 12UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME0_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK3:
        shift_bits = 8UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME0_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK2:
        shift_bits = 4UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME0_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK1:
        shift_bits = 0UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME0_ADDRESS;
        break;
    default:
        error_code = ADI_PMIC_FAIL;
        break;
    }

    reg = adi_pmic_Read(pmic_num, voltage_blank_time_addr);
    /* Clear the bits that we are interested in */
    cfg->blankTime = (reg >> shift_bits) & FB_BIT_MASK;


    if (error_code == ADI_PMIC_SUCCESS) {
        error_code = adi_pmic_enable(pmic_num, false);
    }

    comment("---> Exiting function adi_pmic_GetWarnFaultWindow");

    return error_code;
}

/******************************** STATIC FUNCTIONS ********************************/
static adi_pmic_err_t adi_pmic_set_qa_wd_slow_fast_window(uint8_t pmic_num, uint32_t fast_window, uint32_t slow_window)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t reg = 0x00UL;
    uint32_t readback = 0x00UL;

    comment("---> Entering function adi_pmic_set_qa_wd_slow_fast_window");

    reg = (fast_window & QA_WD_FAST_WINDOW_BIT_MASK) << QA_WD_FAST_WINDOW_OFFSET;
    reg |= (slow_window & QA_WD_SLOW_WINDOW_BIT_MASK);
    adi_pmic_Write(pmic_num, QA_WD_WINDOW, reg);

    readback = adi_pmic_Read(pmic_num, QA_WD_WINDOW);
    if (reg != readback) {
        error_code = ADI_PMIC_FAIL;
    }

    comment("---> Exiting function adi_pmic_set_qa_wd_slow_fast_window");
    return error_code;
}

static adi_pmic_err_t adi_pmic_set_qa_wd_ctrl(uint8_t pmic_num, uint32_t fault, uint32_t pre_scale, uint32_t enable)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t reg = 0x00UL;
    uint32_t readback = 0x00UL;

    comment("---> Entering function adi_pmic_set_qa_wd_ctrl");

    reg = (fault & QA_WD_FAULT_THRESHOLD_BIT_MASK) << QA_WD_FAULT_THRESHOLD_OFFSET;
    reg |= (pre_scale & QA_WD_PRE_SCALE_BIT_MASK) << QA_WD_PRE_SCALE_OFFSET;
    reg |= (enable & QA_WD_EN_CTRL_OFFSET);
    adi_pmic_Write(pmic_num, QA_WD_CTRL, reg);

    readback = adi_pmic_Read(pmic_num, QA_WD_CTRL);
    if (reg != readback) {
        error_code = ADI_PMIC_FAIL;
    }

    comment("---> Exiting function adi_pmic_set_qa_wd_ctrl");
    return error_code;
}

static adi_pmic_err_t adi_pmic_warn_fault_window(uint8_t pmic_num, uint32_t address, uint32_t voltage, adi_pmic_threshold_values_t thresholdLevel, adi_pmic_blank_times_t blankTime)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t shift_bits = 0x00UL;
    uint32_t voltage_blank_time_addr = 0x00UL;
    adi_pmic_blank_times_t new_blank_time = blankTime;
    uint32_t reg = 0x00UL;
    uint32_t x = 0x00UL;
    uint32_t y = 0x00UL;
    uint32_t bitOffset = voltage * 0x2UL;

    comment("---> Entering function adi_pmic_warn_fault_window");

    comment("bitOffset = %x", bitOffset);
    comment("thresholdLevel = %x", thresholdLevel);
    comment("blankTime = %x", new_blank_time);

    /* Read back the contents of the address 0x8038 (warn) or 0x803C (fault) */
    reg = adi_pmic_Read(pmic_num, address);

    /* Clear the 2 bits that we are interested in */
    x = reg & (~(WARN_WINDOW_BIT_MASK << bitOffset));

    /* Now 'or' the new bits in with the current contents of the register */
    y = x | (thresholdLevel << bitOffset);

    adi_pmic_Write(pmic_num, address, x | y);

    switch ((uint32_t) voltage) {
    case ADI_PMIC_VM1:
        shift_bits = 24UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME0_ADDRESS;
        break;
    case ADI_PMIC_VM0:
        shift_bits = 20UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME0_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK12:
        shift_bits = 16UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME0_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK11:
        shift_bits = 24UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME1_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK10:
        shift_bits = 20UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME1_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK9:
        shift_bits = 16UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME1_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK8:
        shift_bits = 12UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME1_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK7:
        shift_bits = 8UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME1_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK6:
        shift_bits = 4UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME1_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK5:
        shift_bits = 0UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME1_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK4:
        shift_bits = 12UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME0_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK3:
        shift_bits = 8UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME0_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK2:
        shift_bits = 4UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME0_ADDRESS;
        break;
    case ADI_PMIC_FEEDBACK1:
        shift_bits = 0UL;
        voltage_blank_time_addr = ADI_PMIC_VOLTAGE_BLANK_TIME0_ADDRESS;
        break;
    default:
        error_code = ADI_PMIC_FAIL;
        break;
    }

    /* Write to PMIC  addreses */
    reg = adi_pmic_Read(pmic_num,voltage_blank_time_addr);
    /* Clear the bits that we are interested in */
    x = reg & (~(FB_BIT_MASK << shift_bits));

    /* Now 'or' the new bits in with the current contents of the register */
    y = x | (new_blank_time << shift_bits);
    adi_pmic_Write(pmic_num, voltage_blank_time_addr, y);

    comment("Value at address %x: 0x%x", address, adi_pmic_Read(pmic_num, address));
    comment("voltage_blank_time_addr is 0x%x", adi_pmic_Read(pmic_num, voltage_blank_time_addr));

    comment("---> Exiting function adi_pmic_warn_fault_window");

    return error_code;
}

static adi_pmic_err_t adi_pmic_enable(uint8_t pmic_num, bool unlock)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;

    comment("---> Entering function adi_pmic_enable");

    /* Unlock the PMIC */
    if (unlock == true) {
        adi_pmic_unlock(pmic_num, unlock, ADI_PMIC_UNLOCK_ADDRESS);
        adi_pmic_qa_wd_unlock(pmic_num, unlock);
    } else {
        adi_pmic_qa_wd_unlock(pmic_num, unlock);
        adi_pmic_unlock(pmic_num, unlock, ADI_PMIC_UNLOCK_ADDRESS);
    }

    comment("---> Exiting function adi_pmic_enable");
    return error_code;
}

static adi_pmic_err_t adi_pmic_qa_wd_unlock(uint8_t pmic_num, bool unlock)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t reg = 0x00UL;
    uint32_t x = 0x00UL;
    uint32_t y = 0x00UL;
    uint32_t val = 0x01UL;

    comment("---> Entering function adi_pmic_qa_wd_unlock");

    if (unlock == true) {
        val = 0x00;
    }

    /* Set the QA_WD_LOCK */
    reg = adi_pmic_Read(pmic_num, QA_WD_CTRL);
    x = reg & (~(QA_WD_LOCK_BIT_MASK << QA_WD_LOCK_OFFSET));
    y = x | (val << QA_WD_LOCK_OFFSET);
    adi_pmic_Write(pmic_num, QA_WD_CTRL, y);

    reg = adi_pmic_Read(pmic_num, QA_WD_CTRL);
    if (((reg >> QA_WD_LOCK_OFFSET) & QA_WD_LOCK_BIT_MASK) != val) {
        error_code = ADI_PMIC_FAIL;
        if (unlock == true) {
            comment("---> ERROR Unlocking QA WDT");
        } else {
            comment("---> ERROR Locking QA WDT");
        }
    }
    comment("---> Exiting function adi_pmic_qa_wd_unlock");
    return error_code;
}

static adi_pmic_err_t adi_pmic_unlock(uint8_t pmic_num, bool unlock, uint32_t addr_unlock)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t read_key = 0x00UL;
    uint32_t unlock_key = 0x00UL;

    comment("---> Entering function adi_pmic_unlock");

    if (unlock == true) {
        unlock_key = ADI_PMIC_UNLOCK_KEY;
    }

    /* Write down the unlock key */
    adi_pmic_Write(pmic_num, addr_unlock, unlock_key);
    /* For sanity check read back the key */
    read_key = adi_pmic_Read(pmic_num, addr_unlock);

    /* If they are not the same report an error. */
    if (read_key != unlock_key) {
        comment("ERROR: unlock/lock PMIC failure");
        error_code = ADI_PMIC_FAIL;
    } else {
        comment("PMIC Unlocked/Locked");
    }

    comment("---> Exiting function adi_pmic_unlock");

    return error_code;
}

static adi_pmic_err_t adi_pmic_ReadQaWdToken(uint8_t pmic_num, uint32_t * token)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;

    comment("---> Entering function adi_pmic_ReadQaWdToken");

    if (token == NULL) {
        error_code = ADI_PMIC_FAIL;
        comment("---> QA watchdog Token Pointer = NULL");
    }

    if (error_code == ADI_PMIC_SUCCESS) {
        *token = adi_pmic_Read(pmic_num, QA_WD_TOKEN);
    }

    comment("---> Exiting function adi_pmic_ReadQaWdToken");
    return error_code;
}

static adi_pmic_err_t adi_pmic_WriteQaWdAnswer(uint8_t pmic_num, uint32_t answer)
{
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;

    comment("---> Entering function adi_pmic_WriteQaWdAnswer");

    adi_pmic_Write(pmic_num, QA_WD_ANSWER, answer);

    comment("---> Exiting function adi_pmic_WriteQaWdAnswer");
    return error_code;
}
