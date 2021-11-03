/* lvdstestpat.c
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
#include "adar690x_regs.h"
#include "localdefs.h"

adi_dm_err_t adi_dm_SetLvdsTestPattern(uint16_t pat[ADI_DM_NUM_DIGIMMIC][ADI_DM_NUM_RX])
{
    const uint32_t bit_map[] = { 25UL, 24UL, 17UL, 16UL, 9UL, 8UL, 1UL, 0UL };
    int32_t msb, rx, j;
    adi_dm_num_t dm_num;
    adi_dm_err_t res;

    comment("--> Entering function adi_dm_SetLvdsTestPattern");

    comment("set LVDS test mode");
    res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_LVDS_LVDS_CTL_REG, ~BITM_LVDS_LVDS_CTL_REG_TEST_PATTERN_EN, BITM_LVDS_LVDS_CTL_REG_TEST_PATTERN_EN);
    if (res != ADI_DM_SUCCESS)
        return res;

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        for (msb = 1; msb >= 0; msb--) {
            uint32_t v = 0;
            for (j = 7; j >= 0; j--) {
                uint16_t bit_num = 8 * msb + j;
                for (rx = 0; rx < ADI_DM_NUM_RX; rx++) {
                    if ((pat[dm_num][rx] & (1 << bit_num)) != 0) {
                        v |= 1U << (bit_map[j] + 2 * rx);
                    }
                }
            }
            if (msb == 1) {
                res = adi_dm_Write(dm_num, REG_DATA_PORT_DATA_PORT_USERVAL_REG, v);
                if (res != ADI_DM_SUCCESS)
                    return res;
            } else {
                res = adi_dm_Write(dm_num, REG_DATA_PORT_LVDS_TEST_PATTERN_MSB, v);
                if (res != ADI_DM_SUCCESS)
                    return res;
            }
        }
    }

    comment("--> Exiting function adi_dm_SetLvdsTestPattern");
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_ClearLvdsTestPattern(void)
{
    adi_dm_err_t res;
    comment("--> Entering function adi_dm_ClearLvdsTestPattern");

    comment("clear LVDS test mode");
    res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_LVDS_LVDS_CTL_REG, ~BITM_LVDS_LVDS_CTL_REG_TEST_PATTERN_EN, 0);
    if (res != ADI_DM_SUCCESS)
        return res;

    comment("--> Exiting function adi_dm_ClearLvdsTestPattern");
    return ADI_DM_SUCCESS;
}
