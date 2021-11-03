/* pin_mux.c
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

adi_dm_err_t adi_dm_PinMux(adi_dm_num_t dm_num, adi_dm_gpio_t gpio_enum, uint8_t fer, uint8_t mux)
{
    adi_dm_err_t res;
    int32_t pin = gpio_enum - ADI_DM_GPIO0;
    if (pin < 0 || pin > 15)
        return ADI_DM_PARAMETER_ERROR;
    if (!fer) {
        res = adi_dm_Write(dm_num, REG_PORTA_FER_CLR, 1 << pin);
        if (res != ADI_DM_SUCCESS)
            return res;
    } else {
        res = adi_dm_Write(dm_num, REG_PORTA_FER_SET, 1 << pin);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_RMW(dm_num, REG_PORTA_MUX, ~(3 << (2 * pin)), (mux & 3) << (2 * pin));
        if (res != ADI_DM_SUCCESS)
            return res;
    }
    return ADI_DM_SUCCESS;
}
