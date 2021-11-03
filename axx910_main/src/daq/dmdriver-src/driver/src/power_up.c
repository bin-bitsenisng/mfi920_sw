/* power_up.c
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
#include "host_dev.h"

extern host_device_handle_t * host_dev_p;

static adi_dm_err_t power_part_only(uint8_t dm_num, const adi_dm_power_up_t * p, bool is_slave)
{
    adi_dm_err_t res;

    printf("-->> Entering function power_part_only\n");

    //-- POWER SUPPLIES ----------------------------------------------------

    res = adi_dm_PowerUpSupplies(dm_num);
    if (res != ADI_DM_SUCCESS)
        return res;
    /* Boot mode 0x2 as firmware will be downloaded */
    // adi_dm_WriteGPIO(dm_num, ADI_DM_GPIO0, false);
    // adi_dm_WriteGPIO(dm_num, ADI_DM_GPIO6, true);
    // adi_dm_DelayNS(6000000);
    // adi_dm_WriteGPIO(dm_num, ADI_DM_RESETB, true);
    // adi_dm_WriteGPIO(dm_num, ADI_DM_PWDNB, true);

    /* initialise internal state */
    adi_dm_reset_shadow_state(dm_num);
    /* connect to the device */
    res = adi_dm_init_spi_connection(dm_num, false);
    if (res != ADI_DM_SUCCESS)
        return res;

    printf("*** Test write to SPI scratchpad ***\n");
    uint32_t spi_testval = 0xa5;
    res = adi_dm_Write(dm_num, REG_SPI_SPI_SCRATCHPAD, spi_testval);
    if (res != ADI_DM_SUCCESS)
        return res;
    uint32_t spi_scratch;
    res = adi_dm_Read(dm_num, REG_SPI_SPI_SCRATCHPAD, &spi_scratch);
    if (res == ADI_DM_SPI_CRC_ERROR) {
        /* When DigiMMIC is not powered it looks like a CRC error */
        return ADI_DM_SPI_SCRATCHPAD_ERROR;
    } else if (res != ADI_DM_SUCCESS) {
        return res;
    }
    if (spi_scratch != spi_testval) {
        printf("*** Cannot write to digiMMIC SPI ***\n");
        return ADI_DM_SPI_SCRATCHPAD_ERROR;
    }

    /* BIST05k: On power up the radar processor should assign a 1 hot enumeration value to each digiMMIC */
    printf("*** Setting the value of device_enum_id (%d) ***\n", dm_num);
    res = adi_dm_Write(dm_num, REG_SPI_SPI_DEVICEENUMID, 1 << dm_num);
    if (res != ADI_DM_SUCCESS)
        return res;

    uint32_t v = 0xF;           /* disable CLKOUT */
    if (p->enable_clkhost) {
        v = (p->clkoutctrl << BITP_SPI_SPI_DEVICECONFIGAUX_S_CLKOUTCTRL) & BITM_SPI_SPI_DEVICECONFIGAUX_S_CLKOUTCTRL;
    }
    printf("** Set CLKOUTCTRL **\n");
    res = adi_dm_Write(dm_num, REG_SPI_SPI_DEVICECONFIGAUX_S, v);
    if (res != ADI_DM_SUCCESS)
        return res;

    printf("*** Enable clocks to MCU ***\n");
    uint32_t deviceconfg = REG_SPI_SPI_DEVICECONFG_RESET;
    deviceconfg |= BITM_SPI_SPI_DEVICECONFG_RTWO_PUP;
    res = adi_dm_Write(dm_num, REG_SPI_SPI_DEVICECONFG, deviceconfg);
    if (res != ADI_DM_SUCCESS)
        return res;
    printf("*** Wait for RESETOUT ***\n");
    res = adi_dm_WaitGPIO(dm_num, ADI_DM_GPIO8, true, TIMEOUT);
    if (res != ADI_DM_SUCCESS)
        return res;

    printf("*** Test write to MISC scratchpad ***\n");
    uint32_t testval = 0x12345678;
    res = adi_dm_Write(dm_num, REG_MISC_MISC_SCRATCHPAD_0, testval);
    if (res != ADI_DM_SUCCESS)
        return res;
    uint32_t scratch;
    res = adi_dm_Read(dm_num, REG_MISC_MISC_SCRATCHPAD_0, &scratch);
    if (res != ADI_DM_SUCCESS)
        return res;
    if (scratch != testval) {
        printf("*** Cannot write to Register File ***\n");
        return ADI_DM_MISC_SCRATCHPAD_ERROR;
    }

    if (adi_dm_check_spi_crc) {
        /* BIST68: check SPI CRC works by trying an alternative seed and poly */
        uint16_t old_poly, old_seed, new_poly, new_seed;
        adi_dm_get_local_spi_crc_poly(dm_num, &old_poly, &old_seed);
        new_poly = ~old_poly | 1;
        new_seed = ~old_seed;
        printf("try alternate spi crc seed=%04X and poly=%04X\n", new_seed, new_poly);
        res = adi_dm_Write(dm_num, REG_MISC_MISC_SPI_CRC_0, (new_seed << 16) | new_poly);
        if (res != ADI_DM_SUCCESS)
            return res;
        adi_dm_set_local_spi_crc_poly(dm_num, new_poly, new_seed);
        /* Read back scratchpad expecting no error */
        res = adi_dm_Read(dm_num, REG_MISC_MISC_SCRATCHPAD_0, &scratch);
        if (res == ADI_DM_SPI_CRC_ERROR || scratch != testval) {
            printf("*** Cannot change CRC Seed amd poly ***\n");
            return ADI_DM_FAIL;
        } else if (res != ADI_DM_SUCCESS) {
            return res;
        }
        printf("restore original spi crc seed and poly\n");
        res = adi_dm_Write(dm_num, REG_MISC_MISC_SPI_CRC_0, (old_seed << 16) | old_poly);
        if (res != ADI_DM_SUCCESS)
            return res;
        adi_dm_set_local_spi_crc_poly(dm_num, old_poly, old_seed);
    }

    printf("** Configure for master or slave **\n");
    if (is_slave) {
        uint32_t deviceconfgaux = REG_SPI_SPI_DEVICECONFGAUX_RESET;
        deviceconfgaux |= BITM_SPI_SPI_DEVICECONFGAUX_MSTR_SLAVE;
        res = adi_dm_Write(dm_num, REG_SPI_SPI_DEVICECONFGAUX, deviceconfgaux);
        if (res != ADI_DM_SUCCESS)
            return res;
    }
    if (p->is_lo_right[dm_num]) {
        uint32_t hwenginectrl = REG_MISC_MISC_HW_ENGINE_CTRL_RESET;
        hwenginectrl |= BITM_MISC_MISC_HW_ENGINE_CTRL_LO_LEFT_LO_RIGHT;
        res = adi_dm_Write(dm_num, REG_MISC_MISC_HW_ENGINE_CTRL, hwenginectrl);
        if (res != ADI_DM_SUCCESS)
            return res;
    }
    printf("-->> Exiting function power_part_only\n");
    return ADI_DM_SUCCESS;
}

static adi_dm_err_t download_firmware(const adi_dm_power_up_t * p)
{
    int dm_num;
    adi_dm_err_t res;
    uint8_t fw_version_tag, fw_version_major, fw_version_minor, fw_version_patch;
    uint32_t iccm_addr, dccm_addr;
    const uint8_t *image_bytes;

    printf("-->> Entering function download_firmware\n");

    if (!p->firmware_image || !p->firmware_sz || !p->firmware_constants_image || !p->firmware_constants_sz) {
        printf("ERROR: firmware image missing\n");
        return ADI_DM_PARAMETER_ERROR;
    }
    if (p->firmware_sz < ADI_ADAR690x_OFF_FW_VERSION + 4) {
        printf("ERROR: firmware image too small\n");
        return ADI_DM_PARAMETER_ERROR;
    }
    
    image_bytes = (const uint8_t *) p->firmware_image;
    fw_version_tag = image_bytes[ADI_ADAR690x_OFF_FW_VERSION + 0];
    fw_version_major = image_bytes[ADI_ADAR690x_OFF_FW_VERSION + 1];
    fw_version_minor = image_bytes[ADI_ADAR690x_OFF_FW_VERSION + 2];
    fw_version_patch = image_bytes[ADI_ADAR690x_OFF_FW_VERSION + 3];
    printf("*** Firmware revision: %c.%X.%X.%X ***\n", fw_version_tag, fw_version_major, fw_version_minor, fw_version_patch);
    if (p->firmware_sz < ADI_ADAR690x_OFF_FW_ICCM_LOAD_ADDR + 4 || p->firmware_sz < ADI_ADAR690x_OFF_FW_DCCM_LOAD_ADDR + 4) {
        printf("ERROR: firmware image too small\n");
        return ADI_DM_PARAMETER_ERROR;
    }

    /* after 1.8.0 load addresses were encoded in the ICCM image in big endian format */
    dccm_addr = image_bytes[ADI_ADAR690x_OFF_FW_DCCM_LOAD_ADDR + 0] << 24;
    dccm_addr |= image_bytes[ADI_ADAR690x_OFF_FW_DCCM_LOAD_ADDR + 1] << 16;
    dccm_addr |= image_bytes[ADI_ADAR690x_OFF_FW_DCCM_LOAD_ADDR + 2] << 8;
    dccm_addr |= image_bytes[ADI_ADAR690x_OFF_FW_DCCM_LOAD_ADDR + 3] << 0;
    iccm_addr = image_bytes[ADI_ADAR690x_OFF_FW_ICCM_LOAD_ADDR + 0] << 24;
    iccm_addr |= image_bytes[ADI_ADAR690x_OFF_FW_ICCM_LOAD_ADDR + 1] << 16;
    iccm_addr |= image_bytes[ADI_ADAR690x_OFF_FW_ICCM_LOAD_ADDR + 2] << 8;
    iccm_addr |= image_bytes[ADI_ADAR690x_OFF_FW_ICCM_LOAD_ADDR + 3] << 0;

    printf("Loading firmware\n");

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        // Wait for handshake
        res = adi_dm_WaitGPIO(dm_num, ADI_DM_GPIO11, false, TIMEOUT);
        if (res != ADI_DM_SUCCESS)
            return res;
        adi_dm_DelayNS(10000);
        res = adi_dm_WaitGPIO(dm_num, ADI_DM_GPIO11, false, TIMEOUT);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    res = adi_dm_BlockWrite(ADI_DM_ALL_DIGIMMICS, dccm_addr, p->firmware_constants_sz, p->firmware_constants_image);
    if (res != ADI_DM_SUCCESS)
        return res;
    res = adi_dm_BlockWrite(ADI_DM_ALL_DIGIMMICS, iccm_addr, p->firmware_sz, p->firmware_image);
    if (res != ADI_DM_SUCCESS)
        return res;

    /* Instruct MCU to boot from RAM */
    printf("ADI_ADAR690x_FW_BOOTPARSE_CMD\n");
    res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_BOOTPARSE);
    if (res != ADI_DM_SUCCESS) {
        return res;
    }

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        uint32_t scratch;
        res = adi_dm_Read(dm_num, REG_MISC_MISC_SCRATCHPAD_0, &scratch);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
        if (scratch != 0x10019001) {
            printf("*** Firmware not ready ***\n");
            return ADI_DM_MISC_SCRATCHPAD_ERROR;
        }

        printf("*** Release BMODE pins ***\n");
        adi_dm_ReleaseGPIO(dm_num, ADI_DM_GPIO0);
        adi_dm_ReleaseGPIO(dm_num, ADI_DM_GPIO6);
    }

    printf("-->> Exiting function download_firmware\n");
    return ADI_DM_SUCCESS;
}

static adi_dm_err_t firmware_initializations(uint8_t dm_num, const adi_dm_power_up_t * p, bool is_slave, uint32_t cascaded)
{
    adi_dm_err_t res;
    int64_t ramp_bw_hz = (int64_t) p->ramp_bw_Mhz * 1000000LL;
    uint64_t max_ramp_freq_hz, min_ramp_freq_hz;

    printf("-->> Entering function firmware_initializations\n");

    if (ramp_bw_hz >= 0) {
        max_ramp_freq_hz = (uint64_t) ((int64_t) p->ramp_start_freq_hz + ramp_bw_hz);
        min_ramp_freq_hz = p->ramp_start_freq_hz;
    } else {
        max_ramp_freq_hz = p->ramp_start_freq_hz;
        min_ramp_freq_hz = (uint64_t) ((int64_t) p->ramp_start_freq_hz + ramp_bw_hz);
    }

    if (adi_dm_check_fw_config && (min_ramp_freq_hz < ADI_ADAR690x_MIN_RAMP_START_FREQ_HZ || max_ramp_freq_hz > ADI_ADAR690x_MAX_RAMP_START_FREQ_HZ)) {
        printf("ERROR: ramp parameters out of range Min : %ld, Max : %ld\n",min_ramp_freq_hz, max_ramp_freq_hz);
        return ADI_DM_PARAMETER_ERROR;
    }

    adi_dm_saved_max_ramp_freq_hz = max_ramp_freq_hz;
    adi_dm_saved_ramp_bw_hz = ramp_bw_hz;
    adi_dm_saved_ramp_start_freq_hz = p->ramp_start_freq_hz;

    /*-- Firmware initialization sequence  -------------------------------*/

    printf("Write parameters to firmware configuration table\n");
    if (cascaded != 0UL) {
        res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_CASCADED, cascaded);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    /* set default HPF corner frequency to 1 MHz */
    res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_HPF_FC_RX_CHAN0, ADI_DM_HPF_FC_1_MHZ);
    if (res != ADI_DM_SUCCESS)
        return res;
    res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_HPF_FC_RX_CHAN1, ADI_DM_HPF_FC_1_MHZ);
    if (res != ADI_DM_SUCCESS)
        return res;
    res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_HPF_FC_RX_CHAN2, ADI_DM_HPF_FC_1_MHZ);
    if (res != ADI_DM_SUCCESS)
        return res;
    res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_HPF_FC_RX_CHAN3, ADI_DM_HPF_FC_1_MHZ);
    if (res != ADI_DM_SUCCESS)
        return res;

    if (!is_slave) {
        if (adi_dm_check_fw_config && (p->rfpll_loop_bw_hz < ADI_ADAR690x_MIN_RFPLL_LOOP_BW_HZ || p->rfpll_loop_bw_hz > ADI_ADAR690x_MAX_RFPLL_LOOP_BW_HZ)) {
            printf("ERROR: Bad rfpll_loop_bw_hz\n");
            return ADI_DM_PARAMETER_ERROR;
        }
        res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_RFPLL_LOOP_BW_HZ, p->rfpll_loop_bw_hz);
        if (res != ADI_DM_SUCCESS)
            return res;
        /* range checked above */
        res = adi_dm_WriteU64(dm_num, ADI_ADAR690x_CFG_RAMP_START_FREQ_HZ, max_ramp_freq_hz);
        if (res != ADI_DM_SUCCESS)
            return res;
    }
    /* range checked above */
    res = adi_dm_WriteF32(dm_num, ADI_ADAR690x_CFG_RAMP_BW_MHZ, p->ramp_bw_Mhz);
    if (res != ADI_DM_SUCCESS)
        return res;
    res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_PWR_TX0, 0);
    if (res != ADI_DM_SUCCESS)
        return res;
    res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_PWR_TX1, 0);
    if (res != ADI_DM_SUCCESS)
        return res;
    res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_PWR_TX2, 0);
    if (res != ADI_DM_SUCCESS)
        return res;
    /* prevent LOCHAIN_CAL on slaves attempting to synchronize with master */
    res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_LOCHAIN_MST_SLV_SYNC, 0);
    if (res != ADI_DM_SUCCESS)
        return res;
    if (adi_dm_call_fw_time_comp_en_chk) {
        /* BIST56: enable timing comparators of DMs with GPIO7 (stat1 monitor)
         * connected to another device's GPIO9. These settings describe how GPIO7
         * and GPIO9 of the different devices are connected.
         */
        if (cascaded != 0UL && p->timing_comp_setting[dm_num] != ADI_DM_TIMING_COMP_DISABLED) {
            if (p->timing_comp_setting[dm_num] > ADI_DM_TIMING_COMP_GPIO9_ONLY) {
                printf("ERROR: Bad timing_comp_setting\n");
                return ADI_DM_PARAMETER_ERROR;
            }
            res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_TIMING_COMP_EN, p->timing_comp_setting[dm_num]);
            if (res != ADI_DM_SUCCESS)
                return res;
        }
    }

    /* Write the power down request to the config section location for the POWER_MANAGE task */
    res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_POWER_MANAGE, ADI_ADAR690x_BITM_POWER_DOWN_REQUEST | POWER_BLOCKS);
    if (res != ADI_DM_SUCCESS)
        return res;

    /* BIST62: Set of blocks to power down on receiving PWDN interrupt. Powering down
     * same blocks as sleep mode ensures recovery from interrupt in a known state - sleeping.
     */
    res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_PWRDN_INTERRUPT, POWER_BLOCKS);
    if (res != ADI_DM_SUCCESS)
        return res;
    /* BIST03: Mark all tx enabled in parameter to ADI_ADAR690x_FW_PWR_SUP_CHK.
     */
    res = adi_dm_RMW(dm_num, ADI_ADAR690x_CFG_PWR_SUP_CHK, 0xFFFFF8FF, 0x00000700);
    if (res != ADI_DM_SUCCESS)
        return res;
    /* Enable BIST18: LO chain output monitor, and BIST15: rx chain diagnostic check
     * by ADI_ADAR690x_FW_RX_CHAIN_CHK call.
     */
    res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_RX_CHAIN_CHK, 0x3);
    if (res != ADI_DM_SUCCESS)
        return res;

    printf("ADI_ADAR690x_FW_CAL_READ\n");
    res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_CAL_READ);
    if (res != ADI_DM_SUCCESS)
        return res;

    if (!is_slave) {
        printf("ADI_ADAR690x_FW_RFPLL_INIT\n");
        res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_RFPLL_INIT);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    printf("ADI_ADAR690x_FW_CHIP_INIT\n");
    res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_CHIP_INIT);
    if (res != ADI_DM_SUCCESS) {
        return res;
    }

    /*-- Bist checks -----------------------------------------------------*/

    if (adi_dm_check_adcpll) {
        /* BIST60: ADC_PLL LOL Check */
        printf("ADI_ADAR690x_FW_ADCPLL_CHK\n");
        res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_ADCPLL_CHK);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
    }

    if (adi_dm_check_rfpll && dm_num == ADI_DM_MASTER) {
        /* BIST61: RF_PLL LOL Check */
        printf("ADI_ADAR690x_FW_RFPLL_CHK\n");
        res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_RFPLL_CHK);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
    }

    if (adi_dm_check_fabric_crc) {
        /* BIST63: Fabric CRC */
        printf("ADI_ADAR690x_FW_CRC_CALC_CHK (check fabric CRC)\n");
        res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_CRC_CALC_CHK);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
    }

    if (adi_dm_check_rom_crc) {
        /* BIST40: ROM CRC
         * ROM CRCs need to be checked once per power cycle against golden CRC in
         * the firmware binary. ICCM ROM and DCCM ROM are checked in
         * ADI_ADAR690x_FW_BOOTPARSE. DDS ROM (13) and SSB ROM (14) are checked here.
         */
        res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_CRC_GROUP_SELECT, 0x80006000);
        if (res != ADI_DM_SUCCESS)
            return res;
        printf("ADI_ADAR690x_FW_CRC_CHK (check DSS ROM and SSB ROM)\n");
        res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_CRC_CHK);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
    }

    if (adi_dm_rx_overflow_chk) {
        /* BIST10 decimation filter overflow chk
         * This is a warning that the decimation filter has overflowed a user
         * set limit so application can take appropriate action, such as reducing
         * tx power levels. So the choice of threshold is an application decision.
         * It is set to 90% if AFE capability here but this is can be changed to
         * as appropriate for the application.
         * 0x73328CCE represents 90% of the upper max and 90% or the lower max
         * 90% of 0x7FFF = 0x7332
         * i.e. 0x7332 << BITP_AFE_FLT_DATALIM_UPPER_LIMIT
         * | 0x8CCE << BITP_AFE_FLT_DATALIM_LOWER_LIMIT
         */
        const uint32_t bist10_threshold = 0x73328CCE;
        res = adi_dm_Write(dm_num, REG_AFE0_FLT_DATALIM, bist10_threshold);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
        res = adi_dm_Write(dm_num, REG_AFE1_FLT_DATALIM, bist10_threshold);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
        res = adi_dm_Write(dm_num, REG_AFE2_FLT_DATALIM, bist10_threshold);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
        res = adi_dm_Write(dm_num, REG_AFE3_FLT_DATALIM, bist10_threshold);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
    }


    /*--------------------------------------------------------------------*/

    printf("-->> Exiting function firmware_initializations\n");
    return ADI_DM_SUCCESS;
}

static adi_dm_err_t firmware_calibrations(uint8_t dm_num, const adi_dm_power_up_t * p, bool is_slave)
{
    adi_dm_err_t res;

    printf("-->> Entering function firmware_calibrations\n");

    if (adi_dm_call_fw_flash_adc_cal) {
        printf("ADI_ADAR690x_FW_FLASH_ADC_CAL\n");
        res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_FLASH_ADC_CAL);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    if (adi_dm_call_fw_lochain_cal) {
        /* Should be run at maximum RFPLL in a ramp
         * Max RFPLL ramp frequency is already set in firmware_initializations */
        printf("ADI_ADAR690x_FW_LOCHAIN_CAL\n");
        res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_LOCHAIN_CAL);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    if (adi_dm_call_fw_rxgain_cal) {
        printf("ADI_ADAR690x_FW_RXGAIN_CAL\n");
        res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_RXGAIN_CAL);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    if (adi_dm_call_fw_adc_phase_cal) {
        printf("ADI_ADAR690x_FW_ADC_PHASE_CAL\n");
        res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_ADC_PHASE_CAL);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
    }

    if (adi_dm_call_fw_pga_cal) {
        printf("ADI_ADAR690x_FW_PGA_CAL\n");
        res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_PGA_CAL);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
    }

    if (adi_dm_call_fw_hpf_cal) {
        printf("ADI_ADAR690x_FW_HPF_CAL\n");
        res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_HPF_CAL);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
    }

    if (adi_dm_call_fw_txpa_cal) {
        printf("ADI_ADAR690x_FW_TXPA_CAL\n");
        res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_TXPA_CAL);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    /*-- Bist checks -----------------------------------------------------*/

    if (adi_dm_call_fw_rx_baseband_latent_chk) {
        /* BIST58: Rx Baseband Latent Fault Detect */
        printf("ADI_ADAR690x_FW_RX_BASEBAND_LATENT_CHK\n");
        res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_RX_BASEBAND_LATENT_CHK);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
    }

    printf("-->> Exiting function firmware_calibrations\n");
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_initial_firmware_tasks(const adi_dm_power_up_t * p, bool first_dm_is_slave, bool cascaded)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    bool is_slave;

    printf("-->> Entering function adi_dm_initial_firmware_tasks\n");

    is_slave = first_dm_is_slave;
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        res = firmware_initializations(dm_num, p, is_slave, cascaded);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
        is_slave = true;
    }

    res = adi_dm_read_temps(&adi_dm_saved_temps);
    if (res != ADI_DM_SUCCESS)
        return res;

    is_slave = first_dm_is_slave;
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        res = firmware_calibrations(dm_num, p, is_slave);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
        is_slave = true;
    }

    if (!first_dm_is_slave) {
        if (adi_dm_call_fw_adcpll_align) {
            printf("ADI_ADAR690x_FW_ADCPLL_ALIGN\n");
            res = adi_dm_CallFW(ADI_DM_MASTER, ADI_ADAR690x_FW_ADCPLL_ALIGN);
            // res = adi_dm_CallFW(ADI_DM_MASTER, 0x309);
            if (res != ADI_DM_SUCCESS)
                return res;
        }

        if (p->ramp_bw_Mhz > 0.0F) {
            printf("Set RFPLL lock frequency to ramp start frequency\n");
            /* range checked in firmware_initializations */
            res = adi_dm_WriteU64(ADI_DM_MASTER, ADI_ADAR690x_CFG_RAMP_START_FREQ_HZ, p->ramp_start_freq_hz);
            if (res != ADI_DM_SUCCESS)
                return res;
        }

        printf("ADI_ADAR690x_FW_RFPLL_RAMP_SETUP\n");
        res = adi_dm_CallFW(ADI_DM_MASTER, ADI_ADAR690x_FW_RFPLL_RAMP_SETUP);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    printf("-->> Exiting function adi_dm_initial_firmware_tasks\n");
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_PowerUp(const adi_dm_power_up_t * p)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    bool is_slave, first_dm_is_slave;
    uint32_t cascaded;

    printf("-->> Entering function adi_dm_PowerUp\n");

    if (adi_dm_active_digimmics > 1UL) {
        cascaded = 1UL;
        first_dm_is_slave = false;
        if (p->is_standalone_master || p->is_standalone_slave) {
            printf("ERROR: is_standalone_master and is_standalone_slave only supported for single DigiMMIC\n");
            return ADI_DM_PARAMETER_ERROR;
        }
    } else {
        if (p->is_standalone_master || p->is_standalone_slave) {
            cascaded = 1UL;
        } else {
            cascaded = 0UL;
        }
        if (p->is_standalone_slave) {
            first_dm_is_slave = true;
        } else {
            first_dm_is_slave = false;
        }
    }

    // res = adi_dm_PowerDown();
    // if (res != ADI_DM_SUCCESS)
    //     return res;
    host_rfic_power_up(host_dev_p);


    is_slave = first_dm_is_slave;
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        res = power_part_only(dm_num, p, is_slave);
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
        is_slave = true;
    }
    if (p->power_part_only) {
        printf("-->> Exiting function adi_dm_PowerUp early per request\n");
        return ADI_DM_SUCCESS;
    }

    // host_spi_speed_change(host_dev_p);
    res = download_firmware(p);
    if (res != ADI_DM_SUCCESS) {
        return res;
    }

    /* initialize ADCPLL even if not doing the full rf setup */
    if (adi_dm_check_fw_config && (p->ref_freq_hz < ADI_ADAR690x_MIN_REF_FREQ_HZ || p->ref_freq_hz > ADI_ADAR690x_MAX_REF_FREQ_HZ)) {
        printf("ERROR: Bad ref_freq_hz\n");
        return ADI_DM_PARAMETER_ERROR;
    }
    res = adi_dm_Write(dm_num, ADI_ADAR690x_CFG_REF_FREQ_HZ, p->ref_freq_hz);
    if (res != ADI_DM_SUCCESS)
        return res;
    printf("ADI_ADAR690x_FW_ADCPLL_INIT\n");
    res = adi_dm_CallFW(dm_num, ADI_ADAR690x_FW_ADCPLL_INIT);
    if (res != ADI_DM_SUCCESS)
        return res;

    if (adi_dm_check_spi_counters) {
        /* BIST05f, BIST05g: compare host and device frame counters after file downloads */
        res = adi_dm_spi_counter_check();
        if (res != ADI_DM_SUCCESS) {
            return res;
        }
    }

    if (p->power_part_load_files_only) {
        printf("-->> Exiting function adi_dm_PowerUp early per request\n");
        return ADI_DM_SUCCESS;
    }

    res = adi_dm_initial_firmware_tasks(p, first_dm_is_slave, cascaded);
    if (res != ADI_DM_SUCCESS) {
        return res;
    }

    printf("-->> Exiting function adi_dm_PowerUp\n");
    return ADI_DM_SUCCESS;
}
