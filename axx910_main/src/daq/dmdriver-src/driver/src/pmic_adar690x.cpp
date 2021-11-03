/* pmic_adar690x.c
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
#include <string.h>

adi_pmic_err_t adi_pmic_PowerADAR690x(uint8_t pmic_num)
{
    /* The recommended settings for powering the supplies
     * to an ADAR690x device.
     */
    adi_pmic_err_t error_code = ADI_PMIC_SUCCESS;
    uint32_t chipId = 0x00;
    adi_pmic_qa_ctrl_t ctrl;

    comment("---> Entering function adi_pmic_PowerADAR690x");

    adi_dm_ResetSPIConnection(pmic_num);
    error_code = adi_pmic_ReadChipId(pmic_num, &chipId);
    if (error_code == ADI_PMIC_SUCCESS && !((chipId == 0x5140) || (chipId == 0x5141))) {
        error_code = ADI_PMIC_FAIL;
        comment("unexpected chip id %x", chipId);
    }
    if (error_code == ADI_PMIC_SUCCESS) {
        comment("PMIC Chip Detected");
        memset(&ctrl, 0, sizeof(ctrl));
        ctrl.pre_scale = 0x02;
        ctrl.fault_threshold = 0x04;
        ctrl.slow_window = 0x1E85;
        ctrl.fast_window = 0x00;
        ctrl.enable = 0x00;
        error_code = adi_pmic_SetQaWdCtrl(pmic_num, ctrl);
    }
    if (error_code == ADI_PMIC_SUCCESS) {
        error_code = adi_pmic_SetLdoThreeFourFiveVout(pmic_num, ADI_PMIC_LDO_FIVE, ADI_PMIC_1P08_V);
    }
    if (error_code == ADI_PMIC_SUCCESS) {
        error_code = adi_pmic_SetLdoThreeFourFiveVout(pmic_num, ADI_PMIC_LDO_FOUR, ADI_PMIC_1P01_V);
    }
    if (error_code == ADI_PMIC_SUCCESS) {
        error_code = adi_pmic_SetLdoThreeFourFiveVout(pmic_num, ADI_PMIC_LDO_THREE, ADI_PMIC_0P94_V);
    }
    if (error_code == ADI_PMIC_SUCCESS) {
        error_code = adi_pmic_SetLdoOneTwoVout(pmic_num, ADI_PMIC_LDO_TWO, ADI_PMIC_1P98_V);
    }

    comment("---> Exiting function adi_pmic_PowerADAR690x");

    return error_code;
}
