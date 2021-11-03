/* spicmd.c
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

//****************************************************************************//
/* The code that unpacks words into bytes for SPI is inherently little endian
 * irrespective of host architecture so only that mode is supported.
 * Only SIOM is supported currently.
 * LSBFIRST depends upon host SPI implementation. Set ADI_DM_SPI_IS_LSBFIRST as
 * required.
 */

// adi_dm_spistate_t adi_dm_spistate[ADI_DM_NUM_SPI_SLAVES];
adi_dm_spistate_t adi_dm_spistate[8];

static inline uint8_t spi_write_cmd(int endian)
{
    return 0 << 7 |             /* write */
        endian << 4 |           /* endianness */
        0 << 1 |                /* SIOM */
        0 << 0;                 /* write */
}

static inline uint8_t spi_read_cmd(int endian)
{
    return 1 << 7 |             /* read */
        endian << 4 |           /* endianness */
        0 << 1 |                /* SIOM */
        1 << 0;                 /* read */
}

static uint8_t len_code(int_fast16_t len)
{
    uint8_t len_code = len_1;

    switch (len) {
    case 1:
        len_code = len_1;
        break;
    case 4:
        len_code = len_4;
        break;
    case 16:
        len_code = len_16;
        break;
    case 64:
        len_code = len_64;
        break;
    default:
        adi_dm_Log("ERROR: spi_write_dev_chunk bad len %" PRIdFAST32 "\n", len);
    }
    return len_code;
}

static uint8_t reverse_bits(uint8_t b)
{
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

void adi_dm_spi_crc(uint8_t slave, uint8_t * data, int_fast16_t * plen)
{
    uint8_t *p = data;
    int_fast16_t len = *plen;
    uint16_t i, j, c, bit;
    uint16_t crc = adi_dm_spistate[slave].crc_seed;
    uint16_t poly = adi_dm_spistate[slave].crc_poly | 1;

    for (i = 0; i < len; i++) {
        c = (uint16_t) * p++;

        for (j = 0x80; j; j >>= 1) {
            bit = crc & 0x8000;
            crc <<= 1;
            if (c & j)
                bit ^= 0x8000;
            if (bit)
                crc ^= poly;
        }
    }
    crc &= 0xFFFF;
    data[len++] = (crc >> 8) & 0xFF;
    data[len++] = (crc >> 0) & 0xFF;
    if (adi_dm_spistate[slave].lsbfirst) {
        /* SPI CRC calculation always ignores
        * lsbfirst setting so always reverse if host
        * is lsbfirst
        */
        data[len - 2] = reverse_bits(data[len - 2]);
        data[len - 1] = reverse_bits(data[len - 1]);
    }
    *plen = len;
}

static inline void incr_read_count(uint8_t slave)
{
    adi_dm_spistate[slave].read_count++;
}

static inline void incr_write_count(uint8_t slave)
{
    adi_dm_spistate[slave].write_count++;
}

static void spi_write_reg8or9(uint8_t slave, uint32_t addr, uint8_t data)
{
    uint8_t mosi[7];
    uint8_t miso[ARRAY_SIZE(mosi)];
    int_fast16_t bytes = 0;

    if (slave < ADI_DM_FIRST_PMIC_SPI_SLAVE || slave == 7) {
        /*Little Endian */
        mosi[bytes++] = spi_write_cmd(0);
        // currently only litte-endian supported
        mosi[bytes++] = addr & 0xff;
        mosi[bytes++] = (addr >> 8) & 0xff;
        mosi[bytes++] = len_1;
    } else {
        /* PMIC is Big Endian */
        mosi[bytes++] = spi_write_cmd(1);
        mosi[bytes++] = (addr >> 8) & 0xff;
        mosi[bytes++] = addr & 0xff;
        mosi[bytes++] = 0x00;
        //mosi[bytes++] = data;
    }
    mosi[bytes++] = data;
    if (!adi_dm_spistate[slave].crc_disabled)
        adi_dm_spi_crc(slave, mosi, &bytes);
    if (adi_dm_spistate[slave].lsbfirst != ADI_DM_SPI_IS_LSBFIRST) {
        for (int_fast16_t i = 0; i < bytes; i++)
            mosi[i] = reverse_bits(mosi[i]);
    }
    adi_dm_SPI(slave, mosi, miso, bytes);
    incr_write_count(slave);
}

static inline void set_regs8and9(uint8_t slave, uint32_t addr)
{
    // if (addr != 8 && addr != 9 && adi_dm_spistate[slave].reg8and9 != ((addr >> 16) & 0xffff)) {
    //     spi_write_reg8or9(slave, 9, (addr >> 24) & 0xff);
    //     spi_write_reg8or9(slave, 8, (addr >> 16) & 0xff);
    //     adi_dm_spistate[slave].reg8and9 = ((addr >> 16) & 0xffff);
    // }

    int miss_flag = 0;
    if(slave != 7)  // select a chip
    {
        if (addr != 8 && addr != 9 && adi_dm_spistate[slave].reg8and9 != ((addr >> 16) & 0xffff)) {
            spi_write_reg8or9(slave, 9, (addr >> 24) & 0xff);
            spi_write_reg8or9(slave, 8, (addr >> 16) & 0xff);
            adi_dm_spistate[slave].reg8and9 = ((addr >> 16) & 0xffff);
        }
    }
    else        // select all chip
    {
        if (addr != 8 && addr != 9) {
            for (int ii=0; ii <ADI_DM_NUM_DIGIMMIC; ii++)
                if(adi_dm_spistate[ii].reg8and9 != ((addr >> 16) & 0xffff))
                    miss_flag=1; 

            if(miss_flag)
            {
                spi_write_reg8or9(slave, 9, (addr >> 24) & 0xff);
                spi_write_reg8or9(slave, 8, (addr >> 16) & 0xff);
                for (int ii=0; ii <ADI_DM_NUM_DIGIMMIC; ii++)
                    adi_dm_spistate[ii].reg8and9 = ((addr >> 16) & 0xffff);
                adi_dm_spistate[slave].reg8and9 = ((addr >> 16) & 0xffff);
            }
        }
    }
}

static inline void putU32(uint8_t slave, uint32_t value, uint8_t * out)
{
    if (slave < ADI_DM_FIRST_PMIC_SPI_SLAVE || slave == 7) {
        out[0] = (uint8_t) (value >> 0);
        out[1] = (uint8_t) (value >> 8);
        out[2] = (uint8_t) (value >> 16);
        out[3] = (uint8_t) (value >> 24);
    } else {
        /* PMIC is Big Endian */
        out[0] = (uint8_t) (value >> 24);
        out[1] = (uint8_t) (value >> 16);
        out[2] = (uint8_t) (value >> 8);
        out[3] = (uint8_t) (value >> 0);
    }

}

static inline uint32_t getU32(uint8_t slave, uint8_t * in)
{
    if (slave < ADI_DM_FIRST_PMIC_SPI_SLAVE) {
        return ((uint32_t) in[0]) | ((uint32_t) in[1] << 8) | ((uint32_t) in[2] << 16) | ((uint32_t) in[3] << 24);
    } else {
        /* PMIC is Big Endian */
        return ((uint32_t) in[3]) | ((uint32_t) in[2] << 8) | ((uint32_t) in[1] << 16) | ((uint32_t) in[0] << 24);
    }
}

void adi_dm_WriteSPI(uint8_t slave, uint32_t addr, int_fast16_t chunk_len, const uint32_t * data)
{
    uint8_t mosi[70];
    uint8_t miso[ARRAY_SIZE(mosi)];
    int_fast16_t bytes = 0;

    if (adi_dm_spistate[slave].lsbfirst != ADI_DM_SPI_IS_LSBFIRST)
        comment("adi_dm_WriteSPI with inconsistent lsbfirst setting");
    if (chunk_len > 4 && !adi_dm_spistate[slave].addrasc)
        comment("adi_dm_WriteSPI with inconsistent addrasc setting");
    set_regs8and9(slave, addr);
    if (slave < ADI_DM_FIRST_PMIC_SPI_SLAVE || slave == 7) {
        mosi[bytes++] = spi_write_cmd(0);
        mosi[bytes++] = (addr >> 0) & 0xff;
        mosi[bytes++] = (addr >> 8) & 0xff;
        mosi[bytes++] = len_code(chunk_len);
    } else {
        /* PMIC is Big Endian */
        chunk_len = 4;
        mosi[bytes++] = spi_write_cmd(1);
        mosi[bytes++] = (addr >> 8) & 0xff;
        mosi[bytes++] = (addr >> 0) & 0xff;
        mosi[bytes++] = 0x00;
    }

    if (chunk_len == 1) {
        mosi[bytes++] = data[0];
    } else {
        int_fast16_t n = chunk_len / 4;
        for (int_fast16_t i = 0; i < n; i++) {
            putU32(slave, data[i], &mosi[bytes]);
            bytes += 4;
        }
    }
    if (!adi_dm_spistate[slave].crc_disabled)
        adi_dm_spi_crc(slave, mosi, &bytes);
    adi_dm_SPI(slave, mosi, miso, bytes);
    incr_write_count(slave);
    if (chunk_len == 1) {
        if (addr == 1) {
            if ((data[0] & 0x70) == 0x50) {
                adi_dm_spistate[slave].crc_disabled = true;
            } else {
                adi_dm_spistate[slave].crc_disabled = false;
            }
        }
    }
}

adi_dm_err_t adi_dm_ReadSPI(uint8_t slave, uint32_t addr, int_fast16_t chunk_len, uint32_t * data)
{
    uint8_t mosi[70];
    uint8_t miso[ARRAY_SIZE(mosi)];
    int_fast16_t bytes = 0;
    adi_dm_err_t res = ADI_DM_SUCCESS;

    if (adi_dm_spistate[slave].lsbfirst != ADI_DM_SPI_IS_LSBFIRST)
        comment("adi_dm_ReadSPI with inconsistent lsbfirst setting");
    if (chunk_len > 4 && !adi_dm_spistate[slave].addrasc)
        comment("adi_dm_ReadSPI with inconsistent addrasc setting");
    set_regs8and9(slave, addr);
    if (slave < ADI_DM_FIRST_PMIC_SPI_SLAVE) {
        mosi[bytes++] = spi_read_cmd(0);
        mosi[bytes++] = (addr >> 0) & 0xff;
        mosi[bytes++] = (addr >> 8) & 0xff;
        mosi[bytes++] = len_code(chunk_len);
    } else {
        /* PMIC is Big Endian */
        chunk_len = 4;
        mosi[bytes++] = spi_read_cmd(1);
        mosi[bytes++] = (addr >> 8) & 0xff;
        mosi[bytes++] = (addr >> 0) & 0xff;
        mosi[bytes++] = 0x00;
    }
    int_fast16_t bytes_in = bytes;
    for (int_fast16_t i = 0; i < chunk_len; i++)
        mosi[bytes++] = 0;
    if (!adi_dm_spistate[slave].crc_disabled) {
        mosi[bytes++] = 0;
        mosi[bytes++] = 0;
    }
    adi_dm_SPI(slave, mosi, miso, bytes);
    incr_read_count(slave);
    if (!adi_dm_spistate[slave].crc_disabled) {
        // check crc
        bytes -= 2;
        for (int_fast16_t i = bytes_in; i < bytes; i++)
            mosi[i] = miso[i];
        adi_dm_spi_crc(slave, mosi, &bytes);
        adi_dm_spistate[slave].read_crc_error = false;
        adi_dm_spistate[slave].read_crc = (miso[bytes - 2] << 8) | miso[bytes - 1];
        if (miso[bytes - 2] != mosi[bytes - 2] || miso[bytes - 1] != mosi[bytes - 1]) {
            adi_dm_spistate[slave].read_crc_error = true;
            res = ADI_DM_SPI_CRC_ERROR;
        }
    }
    if (chunk_len == 1) {
        data[0] = miso[bytes_in++];
    } else {
        int_fast16_t n = chunk_len / 4;
        for (int_fast16_t i = 0; i < n; i++) {
            data[i] = getU32(slave, &miso[bytes_in]);
            bytes_in += 4;
        }
    }
    return res;
}

void adi_dm_ResetSPIConnection(uint8_t slave)
{
    adi_dm_spistate[slave].lsbfirst = false;
    adi_dm_spistate[slave].addrasc = false;
    adi_dm_spistate[slave].crc_disabled = false;
    adi_dm_spistate[slave].reg8and9 = 0;
    adi_dm_spistate[slave].read_crc_error = false;
    adi_dm_spistate[slave].read_crc = 0;
    adi_dm_spistate[slave].write_count = 0;
    adi_dm_spistate[slave].read_count = 0;
    adi_dm_spistate[slave].crc_poly = 0x90D9;
    adi_dm_spistate[slave].crc_seed = 0x5555;
}

void adi_dm_InitSPIConnection(uint8_t slave, bool disable_crc)
{
    uint8_t config_a = 0;
    uint8_t config_b = 0;
    uint8_t mosi[10];
    uint8_t miso[ARRAY_SIZE(mosi)];

    adi_dm_ResetSPIConnection(slave);
    adi_dm_spistate[slave].lsbfirst = ADI_DM_SPI_IS_LSBFIRST;
    adi_dm_spistate[slave].addrasc = true;      // required for block read/write
    adi_dm_spistate[slave].crc_disabled = disable_crc;
    adi_dm_spistate[slave].reg8and9 = 0;
    config_a |= (adi_dm_spistate[slave].lsbfirst << 6) | (adi_dm_spistate[slave].lsbfirst << 1);
    config_a |= (adi_dm_spistate[slave].addrasc << 5) | (adi_dm_spistate[slave].addrasc << 2);
    if (adi_dm_spistate[slave].crc_disabled) {
        config_b |= 5 << 4;     /* disable CRC */
    }
    // Set digiMMIC SPI into the desired state.
    // Assume SPI is currently in reset state.
    // (There is no way I know of forcing SPI into known state without reset,
    // due to CRC. adi_dm_init_spi() is called just after power cycling so this
    // is a reasonable assumption.)
    if (config_a != 0) {
        int_fast16_t bytes = 0;

        if (slave < ADI_DM_FIRST_PMIC_SPI_SLAVE  || slave == 7) {
            mosi[bytes++] = spi_write_cmd(0);
            mosi[bytes++] = 0;  /* config_a low */
            mosi[bytes++] = 0;  /* config_a high */
            mosi[bytes++] = 0;  /* len_1 */
            mosi[bytes++] = config_a;   /* symetric so no need to reverse */
        } else {
            /* PMIC is Big Endian */
            mosi[bytes++] = spi_write_cmd(1);
            mosi[bytes++] = 0;  /* config_a low */
            mosi[bytes++] = 0;  /* config_a high */
            mosi[bytes++] = 0;  /* len_1 */
            mosi[bytes++] = config_a;   /* symetric so no need to reverse */
        }
        adi_dm_spi_crc(slave, mosi, &bytes);
        if (slave == ADI_DM_DIGIMMIC_MASTER_SPI_ADDR)
            comment("STIM: SPIWRITE 0x%02X 0x%02X%02X 0x%02X 0x%08X 0x%02X%02X", mosi[0], mosi[2], mosi[1], mosi[3], mosi[4], mosi[5], mosi[6]);
        adi_dm_SPI(slave, mosi, miso, bytes);
        incr_write_count(slave);
    }
    if (config_b != 0) {
        int_fast16_t bytes = 0;

        if (slave < ADI_DM_FIRST_PMIC_SPI_SLAVE  || slave == 7) {
            mosi[bytes++] = spi_write_cmd(0);
            mosi[bytes++] = 1;  /* config_b low */
            mosi[bytes++] = 0;  /* config_b high */
            mosi[bytes++] = 0;  /* len_1 */
            mosi[bytes++] = config_b;
        } else {
            /* PMIC is Big Endian */
            mosi[bytes++] = spi_write_cmd(1);
            mosi[bytes++] = 0;  /* config_b low */
            mosi[bytes++] = 1;  /* config_b high */
            mosi[bytes++] = 0;  /* len_1 */
            mosi[bytes++] = config_b;
        }
        adi_dm_spi_crc(slave, mosi, &bytes);
        if (slave == ADI_DM_DIGIMMIC_MASTER_SPI_ADDR)
            comment("STIM: SPIWRITE 0x%02X 0x%02X%02X 0x%02X 0x%08X 0x%02X%02X", mosi[0], mosi[2], mosi[1], mosi[3], mosi[4], mosi[5], mosi[6]);
        adi_dm_SPI(slave, mosi, miso, bytes);
        incr_write_count(slave);
    }
}
