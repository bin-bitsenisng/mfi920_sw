/* pmic_rw.c
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
#include <inttypes.h>

void adi_pmic_Write(uint8_t pmic_num, uint32_t addr, uint32_t value)
{
    int_fast16_t bytes;

    comment("STIM: PMICWRITE 0x%08X 0x%08X", addr, value);
    if ((addr & ~0xff) == 0) {
        bytes = 1;
    } else {
        if (addr % 4 != 0)
            adi_dm_Log("ERROR: adi_pmic_Write (addr %% 4 != 0) addr=%08" PRIx32 "\n", addr);
        bytes = 4;
    }
    adi_dm_WriteSPI(pmic_num, addr, bytes, &value);
}

uint32_t adi_pmic_Read(uint8_t pmic_num, uint32_t addr)
{
    uint32_t value;
    int_fast16_t bytes;
    adi_dm_err_t res;

    if ((addr & ~0xff) == 0) {
        bytes = 1;
    } else {
        if (addr % 4 != 0)
            adi_dm_Log("ERROR: adi_pmic_Read (addr %% 4 != 0) addr=%08" PRIx32 "\n", addr);
        bytes = 4;
    }
    res = adi_dm_ReadSPI(pmic_num, addr, bytes, &value);
    if (res != ADI_DM_SUCCESS)
        adi_dm_Log("ERROR: adi_pmic_Read SPI CRC Error addr=%08" PRIx32 "\n", addr);
    return value;
}
