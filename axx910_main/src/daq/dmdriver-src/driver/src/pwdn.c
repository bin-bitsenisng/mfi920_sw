/* pwdn.c
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

adi_dm_err_t adi_dm_PwndnInterrupt(void)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;

    comment("---> Entering function adi_dm_PwndnInterrupt");

    /* 1. BIST62: Redundantly used PWDNb and SPI powdn to bring device
     *    to known state.
     * 2. Wait for device to respond.
     */

    /* Drive 0 on PWDNb.
     * NOTE:  For this to actually interrupt the device
     * adi_dm_PinMux(ADI_DM_ALL_DIGIMMICS, ADI_DM_PWDNB, 1, 0);
     * must have been called from user application.
     */
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        adi_dm_WriteGPIO(dm_num, ADI_DM_PWDNB, false);
    }
    /* write PWDN pattern to SPI */
    (void) adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_SPI_SPI_POWERDOWN, 5);

    /* If GPIO11 is low when device is interrupted it gets set high by
     * the interrupt routine on the device. Wait for it to low again.
     */
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        res = adi_dm_WaitGPIO(dm_num, ADI_DM_GPIO11, false, TIMEOUT);
        if (res != ADI_DM_SUCCESS)
            return res;
        /* Do it twice in case we caught the low before GPIO went high. */
        res = adi_dm_WaitGPIO(dm_num, ADI_DM_GPIO11, false, TIMEOUT);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    /* A this point device should be in sleep mode with
     * Fault 5 in REG_FAULTCTL_SOFTWARE_FAULT_0 register set.
     * Other faults may be set.
     */

    /* clear PWDN pattern to SPI */
    (void) adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_SPI_SPI_POWERDOWN, 0);
    /* Stop driving PWDNb */
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        adi_dm_ReleaseGPIO(dm_num, ADI_DM_PWDNB);
    }
    comment("---> Exiting function adi_dm_PwndnInterrupt");
    return ADI_DM_SUCCESS;
}
