/* Copyright (c) 2019-2020 Analog Devices Inc. All rights reserved
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
#include <string.h>
#include "adi_dmdriver.h"
#include "host_dev.h"
#include "adi_pmic_driver.h"
#include "spi_optimized.h"

extern "C" void adi_dm_spi_crc(uint8_t slave, uint8_t * data, int_fast16_t * plen);

extern host_device_handle_t * host_dev_p;

static uint32_t scratchpad_reads = 0;

static const uint8_t digimmics[] = {
    ADI_DM_DIGIMMIC_MASTER_SPI_ADDR,
    ADI_DM_DIGIMMIC_SPI_SLAVE1,
    ADI_DM_DIGIMMIC_SPI_SLAVE2,
    ADI_DM_DIGIMMIC_SPI_SLAVE3,
};

double adi_dm_ReadAdcpllFreqHz(void)
{
    /* This is defined in the driver read actual value calculated by firmware.
     * But that requires running firmware to work.
     * Return ADCPLL Frequency fot ref clock of 80 Hz. In this example.
     */
    return 1.28e9;
}

adi_dm_err_t adi_dm_WaitGPIO(uint8_t dm_num, adi_dm_gpio_t hPin, bool bValue, uint32_t nTimeoutNS)
{
    // uint8_t mosi[4] = {0,};
    // uint8_t miso[4] = {0,};
    // uint16_t tmp_miso_val;
    // uint8_t tmp_chk_val;
    unsigned int chk_val=1;
    int count=0;
    int ret;
    // printf("adi_dm_WaitGPIO(%u, %d, %d, %u)\n", dm_num, hPin, bValue, nTimeoutNS);
    // printf("# of selected device : %d \n",slave);
    // temp_dev_num = slave;
    
    /* Read FW_BUSY from cpld SPI block */
    // gpioSetValue(host_dev_p->host_gpio0, 1);
    // gpioSetValue(host_dev_p->host_gpio1, 1);
    // gpioSetValue(host_dev_p->host_gpio2, 1);
    // usleep(1);

    // host_dev_p->spi_tr.tx_buf = (unsigned long)mosi;
    // host_dev_p->spi_tr.rx_buf = (unsigned long)miso;
    // host_dev_p->spi_tr.len = 4;
    
    
    // if(hPin == ADI_DM_GPIO11)  // FW_BUSY 
    // {
    //     while(chk_val)          // Active High
    //     {
    //         ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(1), &(host_dev_p->spi_tr));
    //         // print_spi_transaction(miso, mosi, host_dev_p->spi_tr.len);
            
    //         tmp_miso_val = miso[2]*0x100 + miso[3];
    //         tmp_chk_val = ((tmp_miso_val) & ((0x000F)<<(4*digimmics[dm_num])))>>(4*digimmics[dm_num]);
    //         // printf("slave : %X, val : %X, tmp_val : %X\n", (0x000F)<<(4*digimmics[dm_num])&tmp_miso_val, chk_val, tmp_miso_val);
    //         chk_val = tmp_chk_val & 0x01;
    //         count++;
    //         if(count > nTimeoutNS)
    //         {
    //             return ADI_DM_TIMEDOUT;
    //         }
    //         usleep(1);
    //     }
    // }
    // else
    //     printf("adi_dm_WaitGPIO(%u, %d, %d, %u)\n", dm_num, hPin, bValue, nTimeoutNS);
    //     usleep(10000);

    /* Read FW_BUSY from the cpld IRQ1 pin */       // check cpld firmware, if an error is occur at this point.
                                                    // All FW_BUSY(GPIO11) pins of RFICs should be tied to CPLD_IRQ1(in schmatic. in this code, host->rfic_irq2)
    if(hPin == ADI_DM_GPIO11)
    {
        while(chk_val)
        {
            ret = gpioGetValue(host_dev_p->host_rfic_irq2, &chk_val);
            count++;
            if(count > nTimeoutNS)
            {
                return ADI_DM_TIMEDOUT;
            }
            usleep(1);
        }
    }

    return ADI_DM_SUCCESS;
}

void adi_dm_WriteGPIO(uint8_t dm_num, adi_dm_gpio_t hPin, bool bValue)
{
    printf("adi_dm_WriteGPIO(%u, %d, %d)\n", dm_num, hPin, bValue);
}

void adi_dm_ReleaseGPIO(uint8_t dm_num, adi_dm_gpio_t hPin)
{
    printf("adi_dm_ReleaseGPIO(%u, %d)\n", dm_num, hPin);
}

void adi_dm_DelayNS(uint32_t nTimeNS)
{
    usleep(nTimeNS/1000);
    // printf("adi_dm_DelayuS(%d)\n", nTimeNS);
}

void adi_dm_SPI(uint8_t slave, uint8_t mosi[], uint8_t miso[], uint32_t count)
{
    /* Parse the scratchpad reads at start of adi_dm_PowerUp
     * and return the expected response to avoid exiting the
     * example early.
     */
    //extern void adi_dm_spi_crc(uint8_t slave, uint8_t * data, int_fast16_t * plen);
    int ret, temp_dev_num;
    const uint32_t tracing_limit = 14;
    static const uint8_t pat1[] = { 129, 10, 0, 0, 0 };
    static const uint8_t rep1[] = { 204, 204, 204, 204, 165 };
    static const uint8_t pat2[] = { 129, 32, 112, 3, 0, 0, 0, 0 };
    static const uint8_t rep2[] = { 204, 204, 204, 204, 120, 86, 52, 18 };
    static const uint8_t rep3[] = { 204, 204, 204, 204, 0x01, 0x90, 0x01, 0x10 };
    int bytes_written = 0;
    // if (count >= sizeof(pat1) && !memcmp(mosi, pat1, sizeof(pat1))) {
    //     memcpy(miso, rep1, sizeof(rep1));
    //     bytes_written = sizeof(rep1);
    // } else if (count >= sizeof(pat2) && !memcmp(mosi, pat2, sizeof(pat2))) {
	// 	scratchpad_reads++;
    //     if (scratchpad_reads <= 2) {
    //         memcpy(miso, rep2, sizeof(rep2));
    //         bytes_written = sizeof(rep2);
    //     } else {
    //         memcpy(miso, rep3, sizeof(rep3));
    //         bytes_written = sizeof(rep3);
    //     }
    // }
    memset(miso + bytes_written, 0, count - bytes_written);
    if (mosi[0] & 0x80) {
        /* add a valid crc to all read responses */
        //uint32_t bytes = count - 2;
        int_fast16_t bytes = count - 2;
        memcpy(miso, mosi, 4);
        adi_dm_spi_crc(slave, miso, &bytes);
    }

    // printf("adi_dm_SPI(%u, ", slave);
    // for (uint32_t i = 0; i < count && i < tracing_limit; i++) {
    //     printf("%02X", mosi[i]);
    // }
    // if (tracing_limit < count)
    //     printf("...");
    // printf(", %u)\n", count);

    // printf("# of selected device : %d \n",slave);
    temp_dev_num = slave;
    gpioSetValue(host_dev_p->host_gpio0, temp_dev_num&0b1);
    gpioSetValue(host_dev_p->host_gpio1, (temp_dev_num&0b10)>>1);
    gpioSetValue(host_dev_p->host_gpio2, (temp_dev_num&0b100)>>2);
    usleep(1);

    host_dev_p->spi_tr.tx_buf = (unsigned long)mosi;
    host_dev_p->spi_tr.rx_buf = (unsigned long)miso;
    host_dev_p->spi_tr.len = count;
    ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(1), &(host_dev_p->spi_tr));
    // usleep(10);
    // print_spi_transaction(miso, mosi, host_dev_p->spi_tr.len, slave);
}

//SPI optimize
void adi_dm_SPI_optimize(uint8_t slave, uint32_t bp_idx)
{
    uint8_t mosi[10];
    uint8_t miso[10];
    uint32_t count;
    
    /* Parse the scratchpad reads at start of adi_dm_PowerUp
     * and return the expected response to avoid exiting the
     * example early.
     */
    //extern void adi_dm_spi_crc(uint8_t slave, uint8_t * data, int_fast16_t * plen);
    int ret, temp_dev_num;
    // const uint32_t tracing_limit = 14;
    // static const uint8_t pat1[] = { 129, 10, 0, 0, 0 };
    // static const uint8_t rep1[] = { 204, 204, 204, 204, 165 };
    // static const uint8_t pat2[] = { 129, 32, 112, 3, 0, 0, 0, 0 };
    // static const uint8_t rep2[] = { 204, 204, 204, 204, 120, 86, 52, 18 };
    // static const uint8_t rep3[] = { 204, 204, 204, 204, 0x01, 0x90, 0x01, 0x10 };
    // int bytes_written = 0;
    // if (count >= sizeof(pat1) && !memcmp(mosi, pat1, sizeof(pat1))) {
    //     memcpy(miso, rep1, sizeof(rep1));
    //     bytes_written = sizeof(rep1);
    // } else if (count >= sizeof(pat2) && !memcmp(mosi, pat2, sizeof(pat2))) {
	// 	scratchpad_reads++;
    //     if (scratchpad_reads <= 2) {
    //         memcpy(miso, rep2, sizeof(rep2));
    //         bytes_written = sizeof(rep2);
    //     } else {
    //         memcpy(miso, rep3, sizeof(rep3));
    //         bytes_written = sizeof(rep3);
    //     }
    // }
    
    // memset(miso + bytes_written, 0, count - bytes_written);
    // if (mosi[0] & 0x80) {
    //     /* add a valid crc to all read responses */
    //     //uint32_t bytes = count - 2;
    //     int_fast16_t bytes = count - 2;
    //     memcpy(miso, mosi, 4);
    //     adi_dm_spi_crc(slave, miso, &bytes);
    // }

    // printf("adi_dm_SPI(%u, ", slave);
    // for (uint32_t i = 0; i < count && i < tracing_limit; i++) {
    //     printf("%02X", mosi[i]);
    // }
    // if (tracing_limit < count)
    //     printf("...");
    // printf(", %u)\n", count);

    //printf("[SYKANG] # bp_idx : %d # of selected device : %d \n", bp_idx, slave);
    temp_dev_num = slave;
    gpioSetValue(host_dev_p->host_gpio0, temp_dev_num&0b1);
    gpioSetValue(host_dev_p->host_gpio1, (temp_dev_num&0b10)>>1);
    gpioSetValue(host_dev_p->host_gpio2, (temp_dev_num&0b100)>>2);
    usleep(1);

    host_dev_p->spi_tr.tx_buf = (unsigned long)mosi;
    host_dev_p->spi_tr.rx_buf = (unsigned long)miso;
    host_dev_p->spi_tr.len = count;

    if( temp_dev_num == 2)
    {
        switch(bp_idx)
        {
            //R mode
            case(0):
            {
                ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(6), &R_2_tr);
                break;
            }
            //L mode
            case(1):
            {
                ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(6), &L_2_tr);
                break;
            }
            //M mode
            case(2):
            {
                ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(6), &M_2_tr);
                break;
            }
            //S mode
            case(3):
            {
                ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(6), &S_2_tr);
                break;
            }
        }

    }
    else if( temp_dev_num == 7 )
    {
        switch(bp_idx)
        {
            //R mode
            case(0):
            {
                //ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(14), &R_7_tr);
                ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(9), &R_7_tr_1);
                break;
            }
            //L mode
            case(1):
            {
                //ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(14), &L_7_tr);
                ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(9), &L_7_tr_1);
                break;
            }
            //M mode
            case(2):
            {
                //ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(11), &M_7_tr);
                ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(6), &M_7_tr_1);
                break;
            }
            //S mode
            case(3):
            {
                //ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(11), &S_7_tr);
                ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(6), &S_7_tr_1);
                break;
            }
        }
    }

    //ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(1), &(host_dev_p->spi_tr));
    // usleep(10);
    //print_spi_transaction(miso, mosi, host_dev_p->spi_tr.len, slave);
}

//SPI optimize
void adi_dm_SPI_VID_optimize(uint8_t slave, uint32_t bp_idx)
{
    uint8_t mosi[10];
    uint8_t miso[10];
    uint32_t count;
    
    /* Parse the scratchpad reads at start of adi_dm_PowerUp
     * and return the expected response to avoid exiting the
     * example early.
     */
    //extern void adi_dm_spi_crc(uint8_t slave, uint8_t * data, int_fast16_t * plen);
    int ret, temp_dev_num;
    // const uint32_t tracing_limit = 14;
    // static const uint8_t pat1[] = { 129, 10, 0, 0, 0 };
    // static const uint8_t rep1[] = { 204, 204, 204, 204, 165 };
    // static const uint8_t pat2[] = { 129, 32, 112, 3, 0, 0, 0, 0 };
    // static const uint8_t rep2[] = { 204, 204, 204, 204, 120, 86, 52, 18 };
    // static const uint8_t rep3[] = { 204, 204, 204, 204, 0x01, 0x90, 0x01, 0x10 };
    // int bytes_written = 0;
    // if (count >= sizeof(pat1) && !memcmp(mosi, pat1, sizeof(pat1))) {
    //     memcpy(miso, rep1, sizeof(rep1));
    //     bytes_written = sizeof(rep1);
    // } else if (count >= sizeof(pat2) && !memcmp(mosi, pat2, sizeof(pat2))) {
	// 	scratchpad_reads++;
    //     if (scratchpad_reads <= 2) {
    //         memcpy(miso, rep2, sizeof(rep2));
    //         bytes_written = sizeof(rep2);
    //     } else {
    //         memcpy(miso, rep3, sizeof(rep3));
    //         bytes_written = sizeof(rep3);
    //     }
    // }
    
    // memset(miso + bytes_written, 0, count - bytes_written);
    // if (mosi[0] & 0x80) {
    //     /* add a valid crc to all read responses */
    //     //uint32_t bytes = count - 2;
    //     int_fast16_t bytes = count - 2;
    //     memcpy(miso, mosi, 4);
    //     adi_dm_spi_crc(slave, miso, &bytes);
    // }

    // printf("adi_dm_SPI(%u, ", slave);
    // for (uint32_t i = 0; i < count && i < tracing_limit; i++) {
    //     printf("%02X", mosi[i]);
    // }
    // if (tracing_limit < count)
    //     printf("...");
    // printf(", %u)\n", count);

    temp_dev_num = slave;
    gpioSetValue(host_dev_p->host_gpio0, temp_dev_num&0b1);
    gpioSetValue(host_dev_p->host_gpio1, (temp_dev_num&0b10)>>1);
    gpioSetValue(host_dev_p->host_gpio2, (temp_dev_num&0b100)>>2);
    usleep(1);

    host_dev_p->spi_tr.tx_buf = (unsigned long)mosi;
    host_dev_p->spi_tr.rx_buf = (unsigned long)miso;
    host_dev_p->spi_tr.len = count;

    if( temp_dev_num == 2)
    {
        switch(bp_idx)
        {
            //R mode
            case(0):
            {
                ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(6), &R_2_tr);
                break;
            }
            //L mode
            case(1):
            {
                ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(6), &L_2_tr);
                break;
            }
            //M mode
            case(2):
            {
                ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(6), &M_2_tr);
                break;
            }
            //S mode
            case(3):
            {
                ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(6), &S_2_tr);
                break;
            }
        }

    }
    else if( temp_dev_num == 7 )
    {
        switch(bp_idx)
        {
            //R mode
            case(0):
            {
                //ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(14), &R_7_tr);
                ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(5), &R_7_tr_2);
                break;
            }
            //L mode
            case(1):
            {
                //ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(14), &L_7_tr);
                ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(5), &L_7_tr_2);
                break;
            }
            //M mode
            case(2):
            {
                //ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(11), &M_7_tr);
                ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(5), &M_7_tr_2);
                break;
            }
            //S mode
            case(3):
            {
                //ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(11), &S_7_tr);
                ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(5), &S_7_tr_2);
                break;
            }
        }
    }

    //ret = ioctl(host_dev_p->handle_spi, SPI_IOC_MESSAGE(1), &(host_dev_p->spi_tr));
    // usleep(10);
    //print_spi_transaction(miso, mosi, host_dev_p->spi_tr.len, slave);
}

void adi_dm_Log(const char *msg, ...)
{
    if (strncmp(msg, "STIM", 4))
        printf("adi_dm_Log(%s, ...)\n", msg);
}

adi_dm_err_t adi_dm_PowerUpSupplies(uint8_t dm_num)
{
    printf("adi_dm_PowerUpSupplies(%u)\n", dm_num);
    scratchpad_reads = 0;
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_PowerDownSupplies(uint8_t dm_num)
{
    printf("adi_dm_PowerDownSupplies(%u)\n", dm_num);
	scratchpad_reads = 0;
    return ADI_DM_SUCCESS;
}