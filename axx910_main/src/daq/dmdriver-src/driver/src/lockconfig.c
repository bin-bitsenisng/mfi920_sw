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

adi_dm_err_t adi_dm_LockConfig(void)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;

    comment("--> Entering function adi_dm_LockConfig");
    if (adi_dm_check_ram_crc) {
        /* BIST42: Detect bit errors on memory mapped registers using precomputed CRC.
         * BIST102: CRC of volatile memory CRCs to trap stray writes and provide a signature for the configuration.
         * Now configuration is complete we can compute the golden CRCs and signature.
         * The signature will consist of all RAM groups: 10 (OTP copy), 9 (ICCM), 7 (Config block), MMR Groups: 6 ... 1.
         *
         * We use the swiss army knife CRC checker command ADI_ADAR690x_FW_CRC_CHK.
         * This computes or checks memory CRCs according to the bitset in ADI_ADAR690x_CFG_CRC_GROUP_SELECT.
         *
         * bit 31 controls whether we are checking (1) or calculating (0)
         * bits 1 .. 16 select memory regions to CRC
         * bit/group no | details
         * -------------|-------------
         * 1            | user defined ...USER_AREA.. vars define
         * 2            | Dataport, MISC, GPIO, FAULTCTL registers
         * 3            | TX, LOGEN, RX, AFE registers
         * 4            | RFPLL registers
         * 5            | undocumented registers
         * 6            | WDT, more RFPLL, ADCPLL, ADC registers
         * 7            | Firmware CFG section to CONFIG_BLOCK_LEN, gloden CRC in CRC_CHK
         * 8            | reserved for future use
         * 9            | Instruction code in RAM
         * 10           | Copy of OTP in RAM - Golden CRC computed in CAL_READ
         * 11           | ICCM ROM - checked by BOOTPARSE at power up
         * 12           | DCCM ROM - checked by BOOTPARSE at power up
         * 13           | DSS ROM - checked in adi_dm_PowerUp against golden CRC in ICCM file
         * 14           | SSB ROM - checked in adi_dm_PowerUp against golden CRC in ICCM file
         * 15           | reserved for future use
         * 16           | reserved for future use
         *
         * The variable ADI_ADAR690x_CFG_CRC_SIGNATURE_SELECT says which of the above CRCs should be included in
         * the signature which is CRC of CRCs.
         *
         * Having computed the golden CRCs here we set the two variables, ADI_ADAR690x_CFG_CRC_GROUP_SELECT and
         * ADI_ADAR690x_CFG_CRC_SIGNATURE_SELECT, up so calls to CRC_CHK in adi_dm_PeriodicCalibration check against
         * these golden CRCs.
         */
        const uint32_t components = 0x6F7;      /* RAM groups and signature, but not 3 which includes Tx that we change */
        const uint32_t signature_components = components & ~0x1;        /* exclude signature (group 0) from signature calculation */
        const uint32_t crc_components = components & ~0x400;    /* exclude group 10 who's CRC is computed in CAL_READ */
        const uint32_t crc_check = components | 0x80000000;     /* include check bit (31) to enable crc checking */

        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_CRC_SIGNATURE_SELECT, signature_components);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_CRC_GROUP_SELECT, crc_components);
        if (res != ADI_DM_SUCCESS)
            return res;
        comment("ADI_ADAR690x_FW_CRC_CHK compute golden CRCs");
        res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_CRC_CHK);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
        /* Copy config block CRCs to golden location. */
        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            uint32_t crc;
            res = adi_dm_Read(dm_num, ADI_ADAR690x_STS_COMPUTED_CRC_GROUP7, &crc);
            if (res != ADI_DM_SUCCESS)
                return res;
            res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_CONFIG_BLOCK_CRC, crc);
            if (res != ADI_DM_SUCCESS)
                return res;
        }
        /* Set up variable for checking signature */
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_CRC_GROUP_SELECT, crc_check);
        if (res != ADI_DM_SUCCESS)
            return res;
        /* check for good measure */
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_STS_CRC_PASS, 0);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_STS_CRC_FAIL, 0);
        if (res != ADI_DM_SUCCESS)
            return res;
        comment("ADI_ADAR690x_FW_CRC_CHK check signature");
        res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_CRC_CHK);
        if (res != ADI_DM_SUCCESS) {
#ifndef __SILENT
            uint32_t v = 0;
            (void) adi_dm_Read(ADI_DM_MASTER, ADI_ADAR690x_STS_CRC_PASS, &v);
            comment("ADI_ADAR690x_STS_CRC_PASS = %08X", v);
            (void) adi_dm_Read(ADI_DM_MASTER, ADI_ADAR690x_STS_CRC_FAIL, &v);
            comment("ADI_ADAR690x_STS_CRC_FAIL = %08X", v);
#endif
            return res;
        }
    }
    if (adi_dm_check_spi_counters) {
        /* BIST05f, BIST05g: compare host and device frame counters */
        res = adi_dm_spi_counter_check();
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
    }
    if (adi_dm_enable_trigger_pin) {
        /* BIST49 explicit control of when external trigger is allowed */
        comment("ADI_ADAR690x_FW_EXT_TRIG_EN");
        res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_EXT_TRIG_EN);
        if (res != ADI_DM_SUCCESS)
            return res;
    }
    if (adi_dm_call_fw_adcpll_align && adi_dm_active_digimmics > 1) {
        /* BIST56: enable check that ramps accross cascaded devices are synchronized.
         * Must be enabled before each burst.
         */
        comment("ADI_ADAR690x_FW_ADCPLL_ALIGN(Internal)");
        // res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_ADCPLL_ALIGN);
        res = adi_dm_CallFW(ADI_DM_MASTER, 0x309);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    comment("--> Exiting function adi_dm_LockConfig");
    return ADI_DM_SUCCESS;
}
