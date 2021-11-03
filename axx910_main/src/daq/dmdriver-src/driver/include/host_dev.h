/************************************************************************
 | Project Name: AFI910
 |    File Name: jetsonGPIO.h
 |  Description: detailed Description
 |-----------------------------------------------------------------------
 |               A U T H O R   I D E N T I T Y
 |-----------------------------------------------------------------------
 | Initials     Name                      Company
 | --------     ---------------------     -------------------------------
 | Hong         HONG JONGTAK              Bitsensing
 |-----------------------------------------------------------------------
 |              R E V I S I O N   H I S T O R Y
 |-----------------------------------------------------------------------
 | Date         Ver  Author  Description
 | ----------  ----  ------  --------------------------------------------
 | 2020.10.15   0.0   Hong   Creation;
 |***********************************************************************/


#ifndef HOST_DEV_H_
#define HOST_DEV_H_

#include "jetsonGPIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <getopt.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <linux/spi/spidev.h>
#include <linux/videodev2.h>


#define MAX_LENGTH 64
#define FIRST_PMIC 4
#define SECOND_PMIC 5

#define PACKET_SEND_BIND_STRING "ipc:///tmp/packet_send_ipc"

enum host_mipi_ch
{
    HOST_MIPI_CH0_VCID0 = 0,
    HOST_MIPI_CH0_VCID1,
    HOST_MIPI_CH1_VCID0,
    HOST_MIPI_CH1_VCID1,
    HOST_MIPI_CH2_VCID0,
    HOST_MIPI_CH2_VCID1,
    HOST_MIPI_CH3_VCID0,
    HOST_MIPI_CH3_VCID1,
    HOST_NUM_MIPI_CH,
};

enum io_method
{
    IO_METHOD_READ,
    IO_METHOD_MMAP,
    IO_METHOD_USERPTR,
};

// struct mipi_buffer_t
// {
//     void *start;
//     size_t length;
// };

typedef struct {
    enum jetsonXavierGPIONumber host_fe_pwr_en_pin;
    enum jetsonXavierGPIONumber host_rfic_nrst;
    enum jetsonXavierGPIONumber host_rfic_npwdn;
    enum jetsonXavierGPIONumber host_rfic_trig;
    enum jetsonXavierGPIONumber host_rfic_irq1;
    enum jetsonXavierGPIONumber host_rfic_irq2;
    enum jetsonXavierGPIONumber host_gpio0;
    enum jetsonXavierGPIONumber host_gpio1;
    enum jetsonXavierGPIONumber host_gpio2;
    enum jetsonXavierGPIONumber host_gpio3;
    enum jetsonXavierGPIONumber host_gpio4;
    enum jetsonXavierGPIONumber host_gpio5;
    enum jetsonXavierGPIONumber host_cpld_tms;
    enum jetsonXavierGPIONumber host_cpld_tck;
    enum jetsonXavierGPIONumber host_cpld_tdi;
    enum jetsonXavierGPIONumber host_cpld_tdo;
    enum jetsonXavierGPIONumber host_cpld_nclr;
    enum jetsonXavierGPIONumber host_cpld_oe;
    enum jetsonXavierGPIONumber host_led_red;
    enum jetsonXavierGPIONumber host_led_green;
    enum jetsonXavierGPIONumber host_led_blue;
    char *host_mipi_dev_name[HOST_NUM_MIPI_CH];
    int  host_mipi_rfic_dev[HOST_NUM_MIPI_CH];

    // struct mipi_buffer_t data_buffers[HOST_NUM_MIPI_CH];

    int  curr_profile;

    __u8 miso[MAX_LENGTH];
	__u8 mosi[MAX_LENGTH];
	struct spi_ioc_transfer spi_tr;
    char device_name[MAX_LENGTH];
	int handle_spi;
    int16_t* data_buf[2];
    __u8   buf_num;
    int sample_offset[16];    // num of adi chips(4) * num of modes(4).

} host_device_handle_t;

typedef struct {
    void* dst;
    void* src;
    uint32_t copy_size;
} daq_memcpy_info;


void host_pheriph_init(host_device_handle_t *host);
void host_pheriph_deinit(host_device_handle_t *host);
void host_rfic_power_up(host_device_handle_t *host);
void host_rfic_hard_reset(host_device_handle_t *host);
void print_spi_transaction(__u8 *miso, __u8 *mosi, __u32 length, __u8 slave);
void host_rfic_hw_trigger(host_device_handle_t *host);
void host_mipi_open(host_device_handle_t *host);
void host_mipi_init(host_device_handle_t *host);
void host_mipi_capt_start(host_device_handle_t *host);
int  host_mipi_read_frame(host_device_handle_t *host);
int  host_mipi_capt_stop(host_device_handle_t *host);
void host_spi_speed_change(host_device_handle_t *host);
#endif // HOST_DEV_H_
