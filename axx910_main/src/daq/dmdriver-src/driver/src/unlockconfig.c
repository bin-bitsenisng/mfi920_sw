/* lockconfig.c
 * Copyright (c) 2019-2020 Analog Devices Inc. All rights reserved
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
#include "adi_dmdriver.h"
#include "localdefs.h"
#include "adar690x_fw.h"

adi_dm_err_t adi_dm_UnlockConfig(void)
{
    comment("--> Entering function adi_dm_UNLockConfig");
    adi_dm_err_t res;
    if (adi_dm_call_fw_tx_pwr_chk || adi_dm_call_fw_tx_output_load_monitor_chk || adi_dm_call_fw_rxchain_diag_chk || adi_dm_call_fw_tx_isolation_monitor_chk || adi_dm_call_fw_pwr_det_rat_chk) {
        res = adi_dm_power_detector_clear();
        if (res != ADI_DM_SUCCESS)
            return res;
    }
    if (adi_dm_enable_trigger_pin) {
        /* BIST49 explicit control of when external trigger is allowed */
        /* as configuration is about to change it is no longer allowed */
        comment("ADI_ADAR690x_FW_EXT_TRIG_DIS");
        res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_EXT_TRIG_DIS);
        if (res != ADI_DM_SUCCESS)
            return res;
    }
    if (adi_dm_check_ram_crc) {
        /* BIST102 recommends ensuring no stale signature is left lying around.
         * As configuration is about to change clear signature CRC.
         */
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_STS_COMPUTED_CRC_GROUP0, 0);
        if (res != ADI_DM_SUCCESS)
            return res;
    }
    comment("--> Exiting function adi_dm_UNLockConfig");
    return ADI_DM_SUCCESS;
}
