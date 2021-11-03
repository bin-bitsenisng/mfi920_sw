/* temp_change.c
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
#include "localdefs.h"
#include "adar690x_fw.h"

adi_dm_err_t adi_dm_get_temp_change(adi_dm_temp_change_t * out)
{
    adi_dm_err_t res;

    comment("-->> Entering function adi_dm_get_temp_change");

    /* call on all devices as it also checks temperature did not go out of range */
    res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_TEMP_MEASURE);
    if (res != ADI_DM_SUCCESS)
        return res;

    /* Use RX2 sensor on master to decide when to run calibrations.
     * This is consistently the hottest sensor in a system, cascaded or otherwise.
     */
    res = adi_dm_ReadF32(ADI_DM_MASTER, ADI_ADAR690x_STS_RX2_TEMP, &out->absolute);
    if (res != ADI_DM_SUCCESS)
        return res;

    out->max_tx_change_c = out->absolute - adi_dm_saved_temps.baseline_tx_temp_c;
    out->max_rx_change_c = out->absolute - adi_dm_saved_temps.baseline_rx_temp_c;
    out->max_rx_change2_c = out->absolute - adi_dm_saved_temps.baseline_rx_temp2_c;
    out->max_lochain_change_c = out->absolute - adi_dm_saved_temps.baseline_lochain_temp_c;

    comment("-->> Exiting function adi_dm_get_temp_change");

    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_baseline_tx_change(adi_dm_temp_change_t * in)
{
    comment("-->> Entering function adi_dm_baseline_tx_change");

    adi_dm_saved_temps.baseline_tx_temp_c = in->absolute;

    comment("-->> Exiting function adi_dm_baseline_tx_change");

    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_baseline_rx_change(adi_dm_temp_change_t * in)
{
    comment("-->> Entering function adi_dm_baseline_rx_change");

    adi_dm_saved_temps.baseline_rx_temp_c = in->absolute;

    comment("-->> Exiting function adi_dm_baseline_rx_change");

    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_baseline_rx_change2(adi_dm_temp_change_t * in)
{
    comment("-->> Entering function adi_dm_baseline_rx_change2");

    adi_dm_saved_temps.baseline_rx_temp2_c = in->absolute;

    comment("-->> Exiting function adi_dm_baseline_rx_change2");

    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_baseline_lochain_change(adi_dm_temp_change_t * in)
{
    comment("-->> Entering function adi_dm_baseline_lochain_change");

    adi_dm_saved_temps.baseline_lochain_temp_c = in->absolute;

    comment("-->> Exiting function adi_dm_baseline_lochain_change");

    return ADI_DM_SUCCESS;
}
