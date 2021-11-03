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
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdint.h>
#include "adi_dmdriver.h"
#include "bts_application.h"
#include "host_dev.h"
#include "adar690x_fw.h"
#include "../src/ADAR690x.h"
#include "reshape.cuh"
#include "Pre_Main.h"

extern host_device_handle_t * host_dev_p;

#define CLEAR(x) memset(&(x), 0, sizeof(x))


uint16_t temp_data_buf[D_MODE_TOTAL_NUM_SAMPLE*ADI_DM_NUM_RX];
uint16_t temp_sample_buf[D_MODE_TOTAL_NUM_SAMPLE*ADI_DM_NUM_RX];
static unsigned int d_mode_len_byte_per_chip = D_MODE_NUM_SAMPLES_PER_RAMP * D_MODE_NUM_RAMPS * NUM_RX_PER_CHIP * 2; //*2 means that 1 sample = 2 bytes.
static unsigned int l_mode_len_byte_per_chip = L_MODE_NUM_SAMPLES_PER_RAMP * L_MODE_NUM_RAMPS * NUM_RX_PER_CHIP * 2; //*2 means that 1 sample = 2 bytes.

static const uint8_t digimmics[] = {
    ADI_DM_DIGIMMIC_MASTER_SPI_ADDR,
    ADI_DM_DIGIMMIC_SPI_SLAVE1,
    ADI_DM_DIGIMMIC_SPI_SLAVE2,
    ADI_DM_DIGIMMIC_SPI_SLAVE3,
};

static const uint8_t inv_digimmics[] = {
    ADI_DM_DIGIMMIC_SPI_SLAVE1,
    ADI_DM_DIGIMMIC_SPI_SLAVE2,
    ADI_DM_DIGIMMIC_MASTER_SPI_ADDR,
    ADI_DM_DIGIMMIC_SPI_SLAVE3,
};

uint64_t GetTimeStamp(void);

float conv_float32_to_dec(uint32_t val)
{
    float ret;

    memcpy(&ret, &val, sizeof(uint32_t));

    return ret;
};

double conv_float64_to_dec(uint64_t val)
{
    double ret;

    memcpy(&ret, &val, sizeof(uint64_t));

    return ret;
};

void platform_init(void)
{
    extern bool adi_dm_check_spi_counters;

    // host_pheriph_deinit(host_dev_p);
    host_pheriph_init(host_dev_p);

    /* disable the SPI frame counter check so we don't need to fake the device counters in the dummy hal */
    adi_dm_check_spi_counters = false;
    adi_dm_ResetSPIConnection(7);
    adi_dm_InitSPIConnection(7,false);
}

void platform_data_plane_init(platform_data_plane_init_t * p)
{
}

void platform_error(const char *fn, adi_dm_err_t res, const char *file, unsigned line)
{
    uint8_t device_num;

    uint32_t addr, val;
    uint64_t hzval = 0;
       
    fprintf(stderr, "%s returned %d at \"%s\":%u\n", fn, res, file, line);

    // for(int ii = 0; ii < 4; ii++){

    //     device_num = inv_digimmics[ii];
    //     printf("<<======= %d device selected =======>>\n", ii);
    //     addr = ADI_ADAR690x_STS_BASE + 0x248;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("VDD_DCO(LDO5) : The value of the register(0x%08X) is : %f\n", addr, conv_float32_to_dec(val));
        
    //     addr = ADI_ADAR690x_STS_BASE + 0x24C;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("AVDD_0V9(LDO4) : The value of the register(0x%08X) is : %f\n", addr, conv_float32_to_dec(val));

    //     addr = ADI_ADAR690x_STS_BASE + 0x258;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("DVDD_0V9(LDO3) : The value of the register(0x%08X) is : %f\n", addr, conv_float32_to_dec(val));

    //     addr = ADI_ADAR690x_STS_BASE + 0x264;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("AVDD_1V8(LDO2) : The value of the register(0x%08X) is : %f\n", addr, conv_float32_to_dec(val));

    //     addr = ADI_ADAR690x_STS_BASE + 0x274;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("VDDIO_1V8(LDO1) : The value of the register(0x%08X) is : %f\n", addr, conv_float32_to_dec(val));

    //     addr = ADI_ADAR690x_STS_BASE + 0x27C;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("VDDIO(LDO1) : The value of the register(0x%08X) is : %f\n", addr, conv_float32_to_dec(val));

    //     addr = ADI_ADAR690x_STS_BASE + 0x0;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("TEMP_TX0 : The value of the register(0x%08X) is : %f\n", addr, conv_float32_to_dec(val));
    //     addr = ADI_ADAR690x_STS_BASE + 0x4;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("TEMP_TX1 : The value of the register(0x%08X) is : %f\n", addr, conv_float32_to_dec(val));
    //     addr = ADI_ADAR690x_STS_BASE + 0x8;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("TEMP_TX2 : The value of the register(0x%08X) is : %f\n", addr, conv_float32_to_dec(val));

    //     addr = ADI_ADAR690x_STS_BASE + 0xC;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("TEMP_RX0 : The value of the register(0x%08X) is : %f\n", addr, conv_float32_to_dec(val));
    //     addr = ADI_ADAR690x_STS_BASE + 0x10;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("TEMP_RX1 : The value of the register(0x%08X) is : %f\n", addr, conv_float32_to_dec(val));
    //     addr = ADI_ADAR690x_STS_BASE + 0x14;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("TEMP_RX2 : The value of the register(0x%08X) is : %f\n", addr, conv_float32_to_dec(val));
    //     addr = ADI_ADAR690x_STS_BASE + 0x18;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("TEMP_RX3 : The value of the register(0x%08X) is : %f\n", addr, conv_float32_to_dec(val));

    //     addr = ADI_ADAR690x_STS_BASE + 0x1C;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("TEMP_LO : The value of the register(0x%08X) is : %f\n", addr, conv_float32_to_dec(val));

    //     hzval=0;
    //     addr = ADI_ADAR690x_STS_BASE + 0x4B8;
    //     adi_dm_Read(device_num, addr, &val);
    //     hzval = hzval + val;
    //     addr = ADI_ADAR690x_STS_BASE + 0x4B8+0x4;
    //     adi_dm_Read(device_num, addr, &val);
    //     hzval = hzval + val*0x100000000;
    //     printf("ADCPLL_FREQ : The value of the register(0x%08X) is : %f MHz\n", addr, conv_float64_to_dec(hzval)/1000000);

    //     hzval=0;
    //     addr = ADI_ADAR690x_STS_BASE + 0x4D0;
    //     adi_dm_Read(device_num, addr, &val);
    //     hzval = hzval + val;
    //     addr = ADI_ADAR690x_STS_BASE + 0x4D0+0x4;
    //     adi_dm_Read(device_num, addr, &val);
    //     hzval = hzval + val*0x100000000;
    //     printf("RFPLL_FREQ : The value of the register(0x%08X) is : %f MHz\n", addr, conv_float64_to_dec(hzval)/1000000);

    //     addr = ADI_ADAR690x_STS_BASE + 0x550;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("nSM32DiffPwrSupp : The value of the register(0x%08X) is : 0x%X\n", addr, (val));
    //     addr = ADI_ADAR690x_STS_BASE + 0x554;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("nSM32SingPwrSupp : The value of the register(0x%08X) is : 0x%X\n", addr, (val));
    //     addr = ADI_ADAR690x_STS_BASE + 0x558;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("nSM32ResMeas : The value of the register(0x%08X) is : 0x%X\n", addr, (val));
    //     addr = ADI_ADAR690x_STS_BASE + 0x55C;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("nSM32tol : The value of the register(0x%08X) is : 0x%X\n", addr, (val));

    //     addr = 0x80006C8C;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("Otp_table.nSM320p5V[0] : The value of the register(0x%08X) is : 0x%X\n", addr, (val));
    //     addr = 0x80006C90;
    //     adi_dm_Read(device_num, addr, &val);
    //     printf("Otp_table.nSM320p5V[1] : The value of the register(0x%08X) is : 0x%X\n", addr, (val));
    // }
    for (int ii = 0; ii < 4; ii++){
        // addr = 0xF0004030;
        // adi_dm_Read(ii, addr, &val);
        // printf("The value of the register(0x%08X) is : 0x%08X\n",addr,val);
        // addr = 0xF0005110;
        // adi_dm_Read(ii, addr, &val);
        // printf("The value of the register(0x%08X) is : 0x%08X\n",addr,val);
        // addr = 0xF0005A04;
        // adi_dm_Read(ii, addr, &val);
        // printf("The value of the register(0x%08X) is : 0x%08X\n",addr,val);
        // addr = 0xF0012010;
        // adi_dm_Read(ii, addr, &val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ii ,addr,val);
        // addr = 0xF0012088;
        // adi_dm_Read(ii, addr, &val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ii ,addr,val);
        // addr = 0xF0013088;
        // adi_dm_Read(ii, addr, &val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ii ,addr,val);
        // addr = 0xF0014088;
        // adi_dm_Read(ii, addr, &val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ii ,addr,val);
        // addr = 0xF0015088;
        // adi_dm_Read(ii, addr, &val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ii ,addr,val);
        addr = 0xF0008008;
        adi_dm_Read(ii, addr, &val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ii ,addr,val);
        addr = 0xF000800C;
        adi_dm_Read(ii, addr, &val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ii ,addr,val);
        // addr = 0xF0008010;
        // adi_dm_Read(ii, addr, &val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ii ,addr,val);
        addr = 0xF0012080;
        adi_dm_Read(ii, addr, &val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ii ,addr,val);
        addr = 0xF0013080;
        adi_dm_Read(ii, addr, &val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ii ,addr,val);
        addr = 0xF0014080;
        adi_dm_Read(ii, addr, &val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ii ,addr,val);
        addr = 0xF0015080;
        adi_dm_Read(ii, addr, &val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ii ,addr,val);
    }
    
    host_pheriph_deinit(host_dev_p);
    exit(1);
}

void platform_prep_host_for_trigger(void)
{
}

void platform_start_timer(uint32_t wait_time_us)
{
}

void platform_wait_for_timer(void)
{
}

void platform_hw_trigger(void)
{
    host_rfic_hw_trigger(host_dev_p);
}

void platform_mipi_init(void)
{
    host_mipi_open(host_dev_p);
    host_mipi_init(host_dev_p);
}

void platform_mipi_cap_start(void)
{
    host_mipi_capt_start(host_dev_p);
}

void platform_mipi_capture(int curr_mode)
{   
    host_dev_p->curr_profile = curr_mode;
    // printf("In platform_mipi_capture => curr_profile : %d, curr_mode : %d\n",host_dev_p->curr_profile,curr_mode);
    host_mipi_read_frame(host_dev_p);
}

void platform_mipi_cap_stop(void)
{
    host_mipi_capt_stop(host_dev_p);
}

void platform_buff_change(void)
{
    if(host_dev_p->buf_num == 0)
        host_dev_p->buf_num = 1;
    else
        host_dev_p->buf_num = 0;

    
    // return host_dev_p->buf_num;
}

void platform_profile_change(int profile_num)
{
    //printf("change profile from %d ",host_dev_p->curr_profile);
    host_dev_p->curr_profile = profile_num;
    //printf("to %d\n",host_dev_p->curr_profile);

}

adi_dm_err_t platform_fault_check(void)
{
    int res;
    for (int i = 0; i < 4; i++)
    {
        // Check status.
        uint32_t hw_fault1;
        res = adi_dm_Read(i, REG_FAULTCTL_FAULT_STATUS1_0, &hw_fault1);
        if (res != ADI_DM_SUCCESS)
            return res;
        bool sw_fault = (hw_fault1 & BITM_FAULTCTL_FAULT_STATUS1_0_SOFTWARE_FAULT) != 0;
        if (sw_fault) {
            uint32_t sw_fault0;
            res = adi_dm_Read(i, REG_FAULTCTL_SOFTWARE_FAULT_0, &sw_fault0);
            if (res != ADI_DM_SUCCESS)
                return res;
            sw_fault0 &= ~adi_dm_sw_fault0_mask;
            if (sw_fault0 != 0) {
                printf("REG_FAULTCTL_SOFTWARE_FAULT_0: 0x%08X\n", sw_fault0);
                return ADI_DM_FIRMWARE_ERROR;
            }
            uint32_t sw_fault1;
            res = adi_dm_Read(i, REG_FAULTCTL_SOFTWARE_FAULT_1, &sw_fault1);
            if (res != ADI_DM_SUCCESS)
                return res;
            sw_fault1 &= ~adi_dm_sw_fault1_mask;
            if (sw_fault1 != 0) {
                printf("REG_FAULTCTL_SOFTWARE_FAULT_1: 0x%08X\n", sw_fault1);
                return ADI_DM_FIRMWARE_ERROR;
            }
            uint32_t sw_fault2;
            res = adi_dm_Read(i, REG_FAULTCTL_SOFTWARE_FAULT_2, &sw_fault2);
            if (res != ADI_DM_SUCCESS)
                return res;
            sw_fault2 &= ~adi_dm_sw_fault2_mask;
            if (sw_fault2 != 0) {
                printf("REG_FAULTCTL_SOFTWARE_FAULT_2: 0x%08X\n", sw_fault2);
                return ADI_DM_FIRMWARE_ERROR;
            }
            uint32_t sw_fault3;
            res = adi_dm_Read(i, REG_FAULTCTL_SOFTWARE_FAULT_3, &sw_fault3);
            if (res != ADI_DM_SUCCESS)
                return res;
            sw_fault3 &= ~adi_dm_sw_fault3_mask;
            if (sw_fault3 != 0) {
                printf("REG_FAULTCTL_SOFTWARE_FAULT_3: 0x%08X\n", sw_fault3);
                return ADI_DM_FIRMWARE_ERROR;
            }
        }
        uint32_t hw_fault0;
        res = adi_dm_Read(i, REG_FAULTCTL_FAULT_STATUS0_0, &hw_fault0);
        if (res != ADI_DM_SUCCESS)
            return res;
        hw_fault0 &= ~adi_dm_fault_status0_mask;
        if (hw_fault0 != 0) {
            printf("REG_FAULTCTL_FAULT_STATUS0_0: 0x%08X\n", hw_fault0);
            return ADI_DM_FIRMWARE_ERROR;
        }
        hw_fault1 &= ~adi_dm_fault_status1_mask;
        if (hw_fault1 != 0) {
            printf("REG_FAULTCTL_FAULT_STATUS1_0: 0x%08X\n", hw_fault1);
            return ADI_DM_FIRMWARE_ERROR;
        }
        uint32_t hw_fault2;
        res = adi_dm_Read(i, REG_FAULTCTL_FAULT_STATUS2_0, &hw_fault2);
        if (res != ADI_DM_SUCCESS)
            return res;
        hw_fault2 &= ~adi_dm_fault_status2_mask;
        if (hw_fault2 != 0) {
            printf("REG_FAULTCTL_FAULT_STATUS2_0: 0x%08X\n", hw_fault2);
            return ADI_DM_FIRMWARE_ERROR;
        }
    }

    return ADI_DM_SUCCESS;
}

void platform_save_data(int frame_cnt)
{   
    int fd_buff = -1;
    int num;
    //Set file name
    time_t tm_time;
    struct tm *st_time;
    char filename[100];
    char filenamech[10];
    uint8_t b_num;
    int tot_byte;

    b_num = host_dev_p->buf_num;
    tot_byte = (d_mode_len_byte_per_chip + l_mode_len_byte_per_chip*3)*4;

    CLEAR(filename);


    time(&tm_time);
    st_time = localtime(&tm_time);
    strftime(filename, 100, "/mnt/ssd/%Y%m%d_%0l%M%S", st_time);
    sprintf(filenamech,"_%03d.raw",frame_cnt);

    strcat(filename,filenamech);
    //fprintf(stderr, "%s\n", filename);

    fd_buff = open(filename, O_CREAT| O_WRONLY | O_TRUNC, 0644);
    if (fd_buff == -1)
    {
        perror("Open");
        exit(1);
    }

    if (write(fd_buff, host_dev_p->data_buf[b_num], tot_byte) != tot_byte)
    {
        perror("Write");
    }

    close(fd_buff);
}

void platform_reshape_data(void)
{   

    int ii, jj;
    int dest_idx;
    int rx_ch_offset, tx_ch_offset, tx_chirp_offset;
    int off_set_addr=0;
    int d_mode_bytesize_per_chip = D_MODE_TOTAL_NUM_SAMPLE*ADI_DM_NUM_RX*2;
    int l_mode_bytesize_per_chip = L_MODE_TOTAL_NUM_SAMPLE*ADI_DM_NUM_RX*2;
    int d_mode_samplesize_per_chip = D_MODE_TOTAL_NUM_SAMPLE*ADI_DM_NUM_RX;
    int l_mode_samplesize_per_chip = L_MODE_TOTAL_NUM_SAMPLE*ADI_DM_NUM_RX;
    uint64_t start, stop;
        

    // start = GetTimeStamp();
    // D-MODE DATA RESHAPE
    for(jj=0; jj<ADI_DM_NUM_DIGIMMIC; jj++ )
    {
        memcpy(temp_data_buf, host_dev_p->data_buf+off_set_addr, d_mode_bytesize_per_chip);
        for(ii=0; ii<d_mode_samplesize_per_chip; ii++)
        {
            rx_ch_offset =( ii % ADI_DM_NUM_RX)*D_MODE_TOTAL_NUM_SAMPLE;
            dest_idx = ii/ADI_DM_NUM_RX + rx_ch_offset;
            temp_sample_buf[dest_idx] = temp_data_buf[ii];
        }
        memcpy(host_dev_p->data_buf+off_set_addr,temp_sample_buf,d_mode_bytesize_per_chip);
        off_set_addr += d_mode_samplesize_per_chip;
    }
    // L,M,S-MODE DATA RESHAPE
    for(jj=0; jj<ADI_DM_NUM_DIGIMMIC*3; jj++ )      // Do 3 times for L,M,S-MODE
    {
        memcpy(temp_data_buf, host_dev_p->data_buf+off_set_addr, l_mode_bytesize_per_chip);
        for(ii=0; ii<l_mode_samplesize_per_chip; ii++)
        {
            rx_ch_offset =(ii % ADI_DM_NUM_RX)*L_MODE_TOTAL_NUM_SAMPLE;
            tx_ch_offset = ((ii / (L_MODE_NUM_SAMPLES_PER_RAMP * ADI_DM_NUM_RX)) % 12) * L_MODE_NUM_SAMPLES_PER_RAMP*32;
            tx_chirp_offset = ii / (L_MODE_NUM_SAMPLES_PER_RAMP * ADI_DM_NUM_RX * 12) * L_MODE_NUM_SAMPLES_PER_RAMP;
            dest_idx = (ii/(ADI_DM_NUM_RX))- (ii / 4096 * 1024) + rx_ch_offset + tx_ch_offset + tx_chirp_offset;
            temp_sample_buf[dest_idx] = temp_data_buf[ii];
        }
        memcpy(host_dev_p->data_buf+off_set_addr, temp_sample_buf, l_mode_bytesize_per_chip);
        off_set_addr += l_mode_samplesize_per_chip;
    }
    // stop = GetTimeStamp();
    // printf("ordering time : %ld\n",stop-start);
}

void platform_gpu_reshape_data(void)
{
    reshape_raw_data(host_dev_p->data_buf[host_dev_p->buf_num], gRM_PreData.s16adcData, gLR_PreData.s16adcData, gMR_PreData.s16adcData, gSR_PreData.s16adcData);
}

void platform_print_data(void)
{
    for(int ii = 0; ii < 1024; ii++)
        printf("%d ",host_dev_p->data_buf[ii]);
    printf("\n");

}

int platform_mipi_vc_id_change(int profile_num)
{
    uint32_t v,vc_id;
    int res;

    if(profile_num == 0)
        vc_id = 0;
    else
        vc_id = 1;

    // printf("*** Packet 0(Frame start packet) vc-id change ***\n");
    v = 0;
    v |= 0x0 << BITP_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_DATA_TYPE;
    v |= vc_id << BITP_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_VC_ID;
    v |= 0x1 << BITP_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_WC;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG, v);
    if (res != ADI_DM_SUCCESS)
        return res;
    // printf("*** Packet 1(Data packet) vc-id change ***\n");
    v = 0;
    v |= (ADI_DM_RAW12 << BITP_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_DATA_TYPE) & BITM_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_DATA_TYPE;
    v |= vc_id << BITP_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_VC_ID;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG, v);
    if (res != ADI_DM_SUCCESS)
        return res;

    // printf("*** Packet 2(Frame end packet) vc-id change ***\n");
    v = 0;
    v |= 0x1 << BITP_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_DATA_TYPE;
    v |= vc_id << BITP_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_VC_ID;
    v |= 0x1 << BITP_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_WC;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG, v);
    if (res != ADI_DM_SUCCESS)
        return res;

    // printf("*** Packet 3(Line start packet) vc-id change ***\n");
    v = 0;
    v |= 0x2 << BITP_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_DATA_TYPE;
    v |= vc_id << BITP_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_VC_ID;
    v |= 0x1 << BITP_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_WC;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPI_CSI2_LINE_START_DATA_ID_WC_REG, v);
    if (res != ADI_DM_SUCCESS)
        return res;

    // printf("*** Packet 4(Line end packet) vc-id change ***\n");
    v = 0;
    v |= 0x3 << BITP_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_DATA_TYPE;
    v |= vc_id << BITP_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_VC_ID;
    v |= 0x1 << BITP_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_WC;
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MIPI_CSI2_LINE_END_DATA_ID_WC_REG, v);
    if (res != ADI_DM_SUCCESS)
        return res;

}



uint64_t GetTimeStamp() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*(uint64_t)1000000+tv.tv_usec;
}
