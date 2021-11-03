/* temperature.c
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

adi_dm_err_t adi_dm_TemperatureGet(adi_dm_temperature_t * out)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;

    comment("-->> Entering function adi_dm_TemperatureGet");

    comment("ADI_ADAR690x_FW_TEMP_MEASURE");
    res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_TEMP_MEASURE);
    if (res != ADI_DM_SUCCESS)
        return res;

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        res = adi_dm_ReadF32(dm_num, ADI_ADAR690x_STS_TX0_TEMP, &out->dm[dm_num].tx_temp_c[0]);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_ReadF32(dm_num, ADI_ADAR690x_STS_TX1_TEMP, &out->dm[dm_num].tx_temp_c[1]);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_ReadF32(dm_num, ADI_ADAR690x_STS_TX2_TEMP, &out->dm[dm_num].tx_temp_c[2]);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_ReadF32(dm_num, ADI_ADAR690x_STS_RX0_TEMP, &out->dm[dm_num].rx_temp_c[0]);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_ReadF32(dm_num, ADI_ADAR690x_STS_RX1_TEMP, &out->dm[dm_num].rx_temp_c[1]);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_ReadF32(dm_num, ADI_ADAR690x_STS_RX2_TEMP, &out->dm[dm_num].rx_temp_c[2]);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_ReadF32(dm_num, ADI_ADAR690x_STS_RX3_TEMP, &out->dm[dm_num].rx_temp_c[3]);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_ReadF32(dm_num, ADI_ADAR690x_STS_LOCHAIN_TEMP, &out->dm[dm_num].lochain_temp_c);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    comment("-->> Exiting function adi_dm_TemperatureGet");

    return res;
}
