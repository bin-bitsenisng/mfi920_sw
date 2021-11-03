/* callfw.c
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

#include <stdio.h>
#include "adi_dmdriver.h"
#include "localdefs.h"
#include "adar690x_regs.h"
#include "adar690x_fw.h"

adi_dm_err_t adi_dm_call_fw_no_block(adi_dm_num_t dm_num, size_t sz, const void *data, int *start_out, int *finish_out)
{
    int start, finish, i;
    adi_dm_err_t res;

    // printf("CallFW 0x%X at dm_num %d\n", *(uint32_t *) data, dm_num);

    if (dm_num >= adi_dm_active_digimmics || dm_num == 7) {
        start = adi_dm_active_digimmics - 1;
        finish = ADI_DM_MASTER;
    } else {
        start = dm_num;
        finish = dm_num;
    }
    if (start_out != NULL) {
        *start_out = start;
    }
    if (finish_out != NULL) {
        *finish_out = finish;
    }

    for (i = start; i >= finish; i--) {
        // Check GPIO11 is not high. Might happen if powered down.
        res = adi_dm_WaitGPIO(i, ADI_DM_GPIO11, false, TIMEOUT);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    /* Issue command */
    /* ADI_DM_ALL_DIGIMMICS is expanded here so we write to slaves
     * before master because there are some commands that syncronise
     * by waiting on the slave util master signals go.
     * For inststance ADI_ADAR690x_FW_ADCPLL_ALIGN (0x1501) and
     * ADI_ADAR690x_FW_LOCHAIN_CAL when parameter set.
     */
    if (sz <= ADI_DM_MAX_DATA_BYTES_PER_SPI_COMMAND) {
        for (i = start; i >= finish; i--) {
            res = adi_dm_BlockWrite(i, ADI_ADAR690x_CFG_SPI_CMD, sz, data);
            if (res != ADI_DM_SUCCESS)
                return res;
        }
    } else {
        /* If the blocks needs to be split up, write in reverse order
         * so write to ADI_ADAR690x_CFG_SPI_CMD, which triggers the
         * command, occurs after parameters have been written.
         */
        int32_t chunk_len = 4;  /* sz must be multiple of 4 */
        int32_t curr_addr = ADI_ADAR690x_CFG_SPI_CMD + sz;
        uint8_t *curr_data = (uint8_t *) data + sz;
        int32_t sz_left = sz;
        while (sz_left > 0) {
            curr_addr -= chunk_len;
            curr_data -= chunk_len;
            sz_left -= chunk_len;
            for (i = start; i >= finish; i--) {
                res = adi_dm_BlockWrite(i, curr_addr, sz_left, curr_data);
                if (res != ADI_DM_SUCCESS)
                    return res;
            }
        }
    }
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_BlockCallFW(adi_dm_num_t dm_num, size_t sz, const void *data)
{
    int start, finish, i;
    adi_dm_err_t res;

    res = adi_dm_call_fw_no_block(dm_num, sz, data, &start, &finish);
    if (res != ADI_DM_SUCCESS)
        return res;

    
        // Wait for GPIO11 to go low.
        res = adi_dm_WaitGPIO(i, ADI_DM_GPIO11, false, TIMEOUT);
        if (res != ADI_DM_SUCCESS)
            return res;
        // Do it twice in case we caught the low before GPIO went high.
        adi_dm_DelayNS(100000);
        res = adi_dm_WaitGPIO(i, ADI_DM_GPIO11, false, TIMEOUT);
        if (res != ADI_DM_SUCCESS)
            return res;
    // for (i = start; i >= finish; i--) {
    //     // Check status.
    //     uint32_t hw_fault1;
    //     res = adi_dm_Read(i, REG_FAULTCTL_FAULT_STATUS1_0, &hw_fault1);
    //     if (res != ADI_DM_SUCCESS)
    //         return res;
    //     bool sw_fault = (hw_fault1 & BITM_FAULTCTL_FAULT_STATUS1_0_SOFTWARE_FAULT) != 0;
    //     if (sw_fault) {
    //         uint32_t sw_fault0;
    //         res = adi_dm_Read(i, REG_FAULTCTL_SOFTWARE_FAULT_0, &sw_fault0);
    //         if (res != ADI_DM_SUCCESS)
    //             return res;
    //         sw_fault0 &= ~adi_dm_sw_fault0_mask;
    //         if (sw_fault0 != 0) {
    //             printf("REG_FAULTCTL_SOFTWARE_FAULT_0: 0x%08X\n", sw_fault0);
    //             return ADI_DM_FIRMWARE_ERROR;
    //         }
    //         uint32_t sw_fault1;
    //         res = adi_dm_Read(i, REG_FAULTCTL_SOFTWARE_FAULT_1, &sw_fault1);
    //         if (res != ADI_DM_SUCCESS)
    //             return res;
    //         sw_fault1 &= ~adi_dm_sw_fault1_mask;
    //         if (sw_fault1 != 0) {
    //             printf("REG_FAULTCTL_SOFTWARE_FAULT_1: 0x%08X\n", sw_fault1);
    //             return ADI_DM_FIRMWARE_ERROR;
    //         }
    //         uint32_t sw_fault2;
    //         res = adi_dm_Read(i, REG_FAULTCTL_SOFTWARE_FAULT_2, &sw_fault2);
    //         if (res != ADI_DM_SUCCESS)
    //             return res;
    //         sw_fault2 &= ~adi_dm_sw_fault2_mask;
    //         if (sw_fault2 != 0) {
    //             printf("REG_FAULTCTL_SOFTWARE_FAULT_2: 0x%08X\n", sw_fault2);
    //             return ADI_DM_FIRMWARE_ERROR;
    //         }
    //         uint32_t sw_fault3;
    //         res = adi_dm_Read(i, REG_FAULTCTL_SOFTWARE_FAULT_3, &sw_fault3);
    //         if (res != ADI_DM_SUCCESS)
    //             return res;
    //         sw_fault3 &= ~adi_dm_sw_fault3_mask;
    //         if (sw_fault3 != 0) {
    //             printf("REG_FAULTCTL_SOFTWARE_FAULT_3: 0x%08X\n", sw_fault3);
    //             return ADI_DM_FIRMWARE_ERROR;
    //         }
    //     }
    //     uint32_t hw_fault0;
    //     res = adi_dm_Read(i, REG_FAULTCTL_FAULT_STATUS0_0, &hw_fault0);
    //     if (res != ADI_DM_SUCCESS)
    //         return res;
    //     hw_fault0 &= ~adi_dm_fault_status0_mask;
    //     if (hw_fault0 != 0) {
    //         printf("REG_FAULTCTL_FAULT_STATUS0_0: 0x%08X\n", hw_fault0);
    //         return ADI_DM_FIRMWARE_ERROR;
    //     }
    //     hw_fault1 &= ~adi_dm_fault_status1_mask;
    //     if (hw_fault1 != 0) {
    //         printf("REG_FAULTCTL_FAULT_STATUS1_0: 0x%08X\n", hw_fault1);
    //         return ADI_DM_FIRMWARE_ERROR;
    //     }
    //     uint32_t hw_fault2;
    //     res = adi_dm_Read(i, REG_FAULTCTL_FAULT_STATUS2_0, &hw_fault2);
    //     if (res != ADI_DM_SUCCESS)
    //         return res;
    //     hw_fault2 &= ~adi_dm_fault_status2_mask;
    //     if (hw_fault2 != 0) {
    //         printf("REG_FAULTCTL_FAULT_STATUS2_0: 0x%08X\n", hw_fault2);
    //         return ADI_DM_FIRMWARE_ERROR;
    //     }
    // }
    return ADI_DM_SUCCESS;
}
