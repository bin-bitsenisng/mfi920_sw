/* sleep.c
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

#include "adi_dmdriver.h"
#include "adar690x_fw.h"
#include "localdefs.h"

adi_dm_err_t adi_dm_ManualSleep(void)
{
    adi_dm_err_t res;

    comment("-->> Entering function adi_dm_ManualSleep");

    /* Use the default parameters in ADI_ADAR690x_CFG_POWER_MANAGE
     * which was configured s the appropriate power down command in
     * adi_dm_PowerUp
     */
    comment("ADI_ADAR690x_FW_POWER_MANAGE");
    res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_POWER_MANAGE);
    if (res != ADI_DM_SUCCESS)
        return res;

    comment("-->> Exiting function adi_dm_ManualSleep");
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_ManualWake(void)
{
    adi_dm_err_t res;
    uint32_t arg0 = ADI_ADAR690x_BITM_POWER_UP_REQUEST | ADI_ADAR690x_BITM_POWER_RESTORE_REQUEST;

    comment("-->> Entering function adi_dm_ManualWake");

    /* Restore the blocks previously powered down */
    comment("ADI_ADAR690x_FW_POWER_MANAGE 0x%08X 0x%08X", arg0, 0);
    res = adi_dm_CallFW2(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_POWER_MANAGE, arg0, 0);
    if (res != ADI_DM_SUCCESS)
        return res;

    comment("-->> Exiting function adi_dm_ManualWake");
    return ADI_DM_SUCCESS;
}
