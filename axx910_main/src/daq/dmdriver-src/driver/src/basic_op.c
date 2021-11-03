/* basic_op.c
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
#include "spistate.h"
#include <inttypes.h>
#include <string.h>


/**
 * Mapping from "DigiMMIC number" to SPI slave address.
 *
 * @note
 * Unfortunately, the master/slave terms are used in two different contexts:
 * cascaded DigiMMICs and the SPI bus.
 * There is not necessarily any connection between these.
 * Here, @c ADI_DM_DIGIMMIC_MASTER is the master of the DigiMMIC cascade,
 * but from the SPI point of view it is just another slave
 * (as are all of the following DigiMMICs).
 */
static const uint8_t digimmics[] = {
    ADI_DM_DIGIMMIC_MASTER_SPI_ADDR,
    ADI_DM_DIGIMMIC_SPI_SLAVE1,
    ADI_DM_DIGIMMIC_SPI_SLAVE2,
    ADI_DM_DIGIMMIC_SPI_SLAVE3,
};

adi_dm_err_t adi_dm_init_spi_connection(adi_dm_num_t dm_num, bool disable_crc)
{
    adi_dm_InitSPIConnection(digimmics[dm_num], disable_crc);
    return ADI_DM_SUCCESS;
}

void adi_dm_reset_shadow_state(adi_dm_num_t dm_num)
{
    adi_dm_ResetSPIConnection(digimmics[dm_num]);
}

adi_dm_err_t adi_dm_Write(adi_dm_num_t dm_num, uint32_t addr, uint32_t value)
{
    int start, finish, i;
    int_fast16_t bytes;

    comment("STIM: MEMWRITE 0x%08X 0x%08X", addr, value);
    if ((addr & ~0xff) == 0) {
        bytes = 1;
    } else {
        if (addr % 4 != 0)
            adi_dm_Log("ERROR: adi_dm_Write (addr %% 4 != 0) addr=%08" PRIx32 "\n", addr);
        bytes = 4;
    }
    // if (dm_num >= adi_dm_active_digimmics) {
    //     start = ADI_DM_MASTER;
    //     finish = adi_dm_active_digimmics;
    // } else {
    //     start = dm_num;
    //     finish = dm_num + 1;
    // }
    // for (i = start; i < finish; i++) {
    //     adi_dm_WriteSPI(digimmics[i], addr, bytes, &value);
    // }
    /* we will write all RFIC at once */
    if (dm_num >= adi_dm_active_digimmics) {
        adi_dm_WriteSPI(7, addr, bytes, &value);
    } else {
        start = dm_num;
        finish = dm_num + 1;
        for (i = start; i < finish; i++) {
            adi_dm_WriteSPI(digimmics[i], addr, bytes, &value);
        }
    }
    

    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_Read(adi_dm_num_t dm_num, uint32_t addr, uint32_t * value)
{
    int_fast16_t bytes;
    adi_dm_err_t res;

    if (dm_num >= adi_dm_active_digimmics) {
        comment("ERROR: adi_dm_Read from multiple devices", addr, value);
        return ADI_DM_PARAMETER_ERROR;
    }
    if ((addr & ~0xff) == 0) {
        bytes = 1;
    } else {
        if (addr % 4 != 0)
            adi_dm_Log("ERROR: adi_dm_Read (addr %% 4 != 0) addr=%08" PRIx32 "\n", addr);
        bytes = 4;
    }
    res = adi_dm_ReadSPI(digimmics[dm_num], addr, bytes, value);
    if (res != ADI_DM_SUCCESS)
        return res;
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_RMW(adi_dm_num_t dm_num, uint32_t addr, uint32_t mask, uint32_t bits)
{
    int start, finish, i;
    uint32_t value;
    int_fast16_t bytes;
    adi_dm_err_t res;

    comment("STIM: MEMRMW 0x%08X 0x%08X 0x%08X", addr, mask, bits);
    if ((addr & ~0xff) == 0) {
        bytes = 1;
    } else {
        if (addr % 4 != 0) {
            comment("ERROR: adi_dm_RMW (addr %% 4 != 0) addr=%08" PRIx32 "\n", addr);
            return ADI_DM_PARAMETER_ERROR;
        }
        bytes = 4;
    }
    if (dm_num >= adi_dm_active_digimmics) {
        start = ADI_DM_MASTER;
        finish = adi_dm_active_digimmics;
    } else {
        start = dm_num;
        finish = dm_num + 1;
    }
    for (i = start; i < finish; i++) {
        res = adi_dm_ReadSPI(digimmics[i], addr, bytes, &value);
        if (res != ADI_DM_SUCCESS)
            return res;
        value &= mask;
        value |= bits;
        adi_dm_WriteSPI(digimmics[i], addr, bytes, &value);
    }
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_BlockWrite(adi_dm_num_t dm_num, uint32_t orig_addr, size_t orig_sz, const void *vdata)
{
    const uint8_t *orig_data = vdata;
    int start, finish, i;
    size_t sz_left;
    const uint8_t *curr_data;
    uint32_t curr_addr;
    uint32_t buf[16];

    if (orig_addr % 4 != 0) {
        comment("ERROR: adi_dm_BlockWrite (orig_addr %% 4 != 0) orig_addr=%08" PRIx32 "\n", orig_addr);
        return ADI_DM_PARAMETER_ERROR;
    }

    if (dm_num >= adi_dm_active_digimmics) {
        start = ADI_DM_MASTER;
        finish = adi_dm_active_digimmics;
        sz_left = orig_sz;
        curr_data = orig_data;
        curr_addr = orig_addr;
        while (sz_left > 0) {
            int_fast16_t chunk_len = 4;

            if (ADI_DM_MAX_DATA_BYTES_PER_SPI_COMMAND >= 64 && sz_left >= 64)
                chunk_len = 64;
            else if (ADI_DM_MAX_DATA_BYTES_PER_SPI_COMMAND >= 16 && sz_left >= 16)
                chunk_len = 16;
// #ifndef __SILENT
//             comment("STIM+ BLKWRITE 0x%08X", curr_addr);
//             for (int pos = 0; pos < chunk_len; pos++)
//                 comment("STIM+  0x%02X", curr_data[pos]);
//             comment("STIM: ");
// #endif
            memcpy(buf, curr_data, chunk_len);  // ensures data is suitably aligned
            // adi_dm_WriteSPI(digimmics[i], curr_addr, chunk_len, buf);
            adi_dm_WriteSPI(7, curr_addr, chunk_len, buf);
            sz_left -= chunk_len;
            curr_addr += chunk_len;
            curr_data += chunk_len;
        }
    } else {
        start = dm_num;
        finish = dm_num + 1;
        for (i = start; i < finish; i++) {
            sz_left = orig_sz;
            curr_data = orig_data;
            curr_addr = orig_addr;
            while (sz_left > 0) {
                int_fast16_t chunk_len = 4;

                if (ADI_DM_MAX_DATA_BYTES_PER_SPI_COMMAND >= 64 && sz_left >= 64)
                    chunk_len = 64;
                else if (ADI_DM_MAX_DATA_BYTES_PER_SPI_COMMAND >= 16 && sz_left >= 16)
                    chunk_len = 16;
    // #ifndef __SILENT
    //             comment("STIM+ BLKWRITE 0x%08X", curr_addr);
    //             for (int pos = 0; pos < chunk_len; pos++)
    //                 comment("STIM+  0x%02X", curr_data[pos]);
    //             comment("STIM: ");
    // #endif
                memcpy(buf, curr_data, chunk_len);  // ensures data is suitably aligned
                adi_dm_WriteSPI(digimmics[i], curr_addr, chunk_len, buf);
                // adi_dm_WriteSPI(7, curr_addr, chunk_len, buf);
                sz_left -= chunk_len;
                curr_addr += chunk_len;
                curr_data += chunk_len;
            }
        }
    }

    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_BlockRead(adi_dm_num_t dm_num, uint32_t addr_in, size_t sz_in, void *data_in)
{
    uint32_t addr = addr_in;
    size_t sz = sz_in;
    uint8_t *data = data_in;
    uint32_t buf[16];

    if (addr % 4 != 0)
        adi_dm_Log("ERROR: adi_dm_BlockRead (addr %% 4 != 0) addr=%08" PRIx32 "\n", addr);
    // SPI commands to do the writes
    while (sz > 0) {
        adi_dm_err_t res;
        int_fast16_t chunk_len = 4;

        if (ADI_DM_MAX_DATA_BYTES_PER_SPI_COMMAND >= 64 && sz >= 64)
            chunk_len = 64;
        else if (ADI_DM_MAX_DATA_BYTES_PER_SPI_COMMAND >= 16 && sz >= 16)
            chunk_len = 16;
        res = adi_dm_ReadSPI(digimmics[dm_num], addr, chunk_len, buf);
        if (res != ADI_DM_SUCCESS)
            return res;
        memcpy(data, buf, chunk_len);
        sz -= chunk_len;
        addr += chunk_len;
        data += chunk_len;
    }
    return ADI_DM_SUCCESS;
}

uint16_t adi_dm_local_spi_reads(adi_dm_num_t dm_num)
{
    return adi_dm_spistate[digimmics[dm_num]].read_count;
}

uint16_t adi_dm_local_spi_writes(adi_dm_num_t dm_num)
{
    return adi_dm_spistate[digimmics[dm_num]].write_count;
}

void adi_dm_reset_local_spi_counters(adi_dm_num_t dm_num)
{
    adi_dm_spistate[digimmics[dm_num]].read_count = 0;
    adi_dm_spistate[digimmics[dm_num]].write_count = 0;
}

void adi_dm_set_local_spi_crc_poly(adi_dm_num_t dm_num, uint16_t crc_poly, uint16_t crc_seed)
{
    adi_dm_spistate[digimmics[dm_num]].crc_poly = crc_poly;
    adi_dm_spistate[digimmics[dm_num]].crc_seed = crc_seed;
}

void adi_dm_get_local_spi_crc_poly(adi_dm_num_t dm_num, uint16_t * crc_poly, uint16_t * crc_seed)
{
    *crc_poly = adi_dm_spistate[digimmics[dm_num]].crc_poly;
    *crc_seed = adi_dm_spistate[digimmics[dm_num]].crc_seed;
}
