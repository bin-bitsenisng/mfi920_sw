/* syscal.c
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
#include "adar690x_regs.h"
#include "adar690x_fw.h"

adi_dm_err_t adi_dm_WriteSysCalTx(const uint8_t in[ADI_DM_NUM_DIGIMMIC][ADI_DM_SYSCAL_TX_SIZE])
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;

    comment("-->> Entering function adi_dm_WriteSysCalTx");

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        res = adi_dm_BlockWrite(dm_num, ADI_ADAR690x_CFG_OP_PWR_TX0, 12, in[dm_num]);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
        res = adi_dm_BlockWrite(dm_num, ADI_ADAR690x_CFG_TX_LOAD_T0_TX0, 12, in[dm_num] + 12);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
    }

    comment("-->> Exiting function adi_dm_WriteSysCalTx");
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_WriteSysCalRx(const uint8_t in[ADI_DM_NUM_DIGIMMIC][ADI_DM_SYSCAL_RX_SIZE])
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;

    comment("-->> Entering function adi_dm_WriteSysCalRx");

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        res = adi_dm_BlockWrite(dm_num, ADI_ADAR690x_CFG_MEAS_REL_GAIN_MISMATCH_0, ADI_DM_SYSCAL_RX_SIZE, in[dm_num]);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
    }

    comment("-->> Exiting function adi_dm_WriteSysCalRx");
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_ReadSysCalTx(uint8_t out[ADI_DM_NUM_DIGIMMIC][ADI_DM_SYSCAL_TX_SIZE])
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;

    comment("-->> Entering function adi_dm_ReadSysCalTx");

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        res = adi_dm_BlockRead(dm_num, ADI_ADAR690x_STS_OP_PWR_TX0, 12, out[dm_num]);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
        res = adi_dm_BlockRead(dm_num, ADI_ADAR690x_STS_TX_LOAD_T0_TX0, 12, out[dm_num] + 12);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
    }

    comment("-->> Exiting function adi_dm_ReadSysCalTx");
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_ReadSysCalRx(uint8_t out[ADI_DM_NUM_DIGIMMIC][ADI_DM_SYSCAL_RX_SIZE])
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;

    comment("-->> Entering function adi_dm_ReadSysCalRx");

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        res = adi_dm_BlockRead(dm_num, ADI_ADAR690x_STS_RX_SIGCHAIN_MISMATCH_0, ADI_DM_SYSCAL_RX_SIZE, out[dm_num]);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
    }

    comment("-->> Exiting function adi_dm_ReadSysCalRx");
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_SetSysCal(bool enable_sys_cal)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    comment("-->> Entering function adi_dm_SetSysCal");

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_SYS_CAL_ENABLE, (uint32_t) enable_sys_cal);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }

    }

    comment("-->> Exiting function adi_dm_SetSysCal");
    return ADI_DM_SUCCESS;
}
