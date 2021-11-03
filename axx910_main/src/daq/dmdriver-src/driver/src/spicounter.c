/* spicounter.c
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
#include <string.h>

adi_dm_err_t adi_dm_spi_counter_check(void)
{
    adi_dm_num_t dm_num;
    adi_dm_err_t res;
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        uint16_t device_reads, device_writes;
        uint16_t local_reads, local_writes;
        uint8_t v[8];
        uint32_t w;

        local_reads = adi_dm_local_spi_reads(dm_num);
        res = adi_dm_BlockRead(dm_num, REG_SPI_SPI_RDFRAMECNT_LSB, 8, v);
        if (res != ADI_DM_SUCCESS)
            return res;
        local_writes = adi_dm_local_spi_writes(dm_num);

        device_reads = (v[0] & 0xFF) | (v[1] & 0xFF) << 8;
        device_writes = (v[4] & 0xFF) | (v[5] & 0xFF) << 8;

        if (device_reads != local_reads || device_writes != local_writes) {
            comment("ERROR: SPI frame count mismatch (dm=%d) reads got %u, reads expected %u, writes got %u, writes expected %u", dm_num, device_reads, local_reads, device_writes, local_writes);
            return ADI_DM_SPI_COUNTER_ERROR;
        }

        res = adi_dm_Read(dm_num, REG_SPI_SPI_DEVICECONFGAUX, &w);
        if (res != ADI_DM_SUCCESS)
            return res;
        /* zero frame counters */
        res = adi_dm_Write(dm_num, REG_SPI_SPI_DEVICECONFGAUX, (w & 0x3) | 0xB4);
        if (res != ADI_DM_SUCCESS)
            return res;
        /* enable counting again */
        res = adi_dm_Write(dm_num, REG_SPI_SPI_DEVICECONFGAUX, w);
        if (res != ADI_DM_SUCCESS)
            return res;
        adi_dm_reset_local_spi_counters(dm_num);
    }
    return ADI_DM_SUCCESS;
}
