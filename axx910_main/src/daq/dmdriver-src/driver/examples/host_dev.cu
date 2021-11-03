/************************************************************************
 | Project Name: AFI910
|    File Name: jetsonGPIO.h
|  Description: detailed Description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------
| sykang       KANG SOO YEON             Bitsensing
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description
| ----------  ----  ------  --------------------------------------------
| 2020.10.15   0.0   sykang   Creation;
|***********************************************************************/

#include "host_dev.h"
#include "stdio.h"
#include "adi_dmdriver.h"
#include "adi_pmic_driver.h"
#include "bts_application.h"
#include <zmq.hpp>
#include <string.h>
#include <sys/select.h>
#include "reshape.cuh"
#include "timestamp.h"

#define CLEAR(x) memset(&(x), 0, sizeof(x))
#define REQ_BUFF_NUM 6
#define NUM_MIPI_CH 8
#define SPI_SPEED_FOR_PMIC 10000000
#define SPI_SPEED_FOR_RFIC 50000000


struct mipi_buffer_t
{
    void *start;
    size_t length;
};

//static enum io_method io_mode = IO_METHOD_MMAP;
static enum io_method io_mode = IO_METHOD_USERPTR;
struct mipi_buffer_t buffers[NUM_MIPI_CH][REQ_BUFF_NUM];
static unsigned int n_buffers;
static int mipi_ch_2_rfic_num[] = {1, 0, 3, 2,};
static unsigned int d_mode_len_byte_per_chip = D_MODE_NUM_SAMPLES_PER_RAMP * D_MODE_NUM_RAMPS * NUM_RX_PER_CHIP * 2; //*2 means that 1 sample = 2 bytes.
static unsigned int l_mode_len_byte_per_chip = L_MODE_NUM_SAMPLES_PER_RAMP * L_MODE_NUM_RAMPS * NUM_RX_PER_CHIP * 2; //*2 means that 1 sample = 2 bytes.


int  host_mipi_capt_stop(host_device_handle_t *host);
void host_mipi_close(host_device_handle_t *host);
void host_data_buf_init(host_device_handle_t *host);

extern zmq::socket_t daq_memcpy_socket;
extern zmq::message_t daq_memcpy_request;
daq_memcpy_info daq_memcpy_info_inst; 
void host_pheriph_init(host_device_handle_t *host){

   char temp_device_name[MAX_LENGTH] = "/dev/spidev0.0";

   printf(">>>> INIT HOST PROCESSOR <<<<\n");

   host->host_fe_pwr_en_pin   = gpio_id_CONN_FE_PWR_EN;
   host->host_rfic_nrst       = gpio_id_CONN_RFIC_nRST;
   host->host_rfic_npwdn      = gpio_id_CONN_RFIC_nPWDN;
   host->host_rfic_trig       = gpio_id_CONN_RFIC_TRIG;
   host->host_rfic_irq1       = gpio_id_CONN_FE_IRQ1;
   host->host_rfic_irq2       = gpio_id_CONN_FE_IRQ2;
   host->host_gpio0           = gpio_id_CONN_GPIO0;
   host->host_gpio1           = gpio_id_CONN_GPIO1;
   host->host_gpio2           = gpio_id_CONN_GPIO2;
   host->host_gpio3           = gpio_id_CONN_GPIO3;
   host->host_gpio4           = gpio_id_CONN_GPIO4;
   host->host_gpio5           = gpio_id_CONN_GPIO5;
   host->host_cpld_tms        = gpio_id_CONN_CPLD_TMS;
   host->host_cpld_tck        = gpio_id_CONN_CPLD_TCK;
   host->host_cpld_tdi        = gpio_id_CONN_CPLD_TDI;
   host->host_cpld_tdo        = gpio_id_CONN_CPLD_TDO;
   host->host_cpld_nclr       = gpio_id_CONN_CPLD_nCLR;
   host->host_cpld_oe         = gpio_id_CONN_CPLD_OE;
   host->host_led_red         = gpio_id_LED_RED;
   host->host_led_green       = gpio_id_LED_GREEN;
   host->host_led_blue        = gpio_id_LED_BLUE;


   strcpy(host->device_name, temp_device_name);
   host->spi_tr.tx_buf        = (unsigned long)host->mosi;
   host->spi_tr.rx_buf        = (unsigned long)host->miso;
   host->spi_tr.delay_usecs   = 0;
   host->spi_tr.bits_per_word = 8;
   host->spi_tr.speed_hz      = 10000000;
   host->handle_spi           = open(temp_device_name, O_RDWR);

   // set GPIOs
   gpioExport(host->host_fe_pwr_en_pin);
   gpioExport(host->host_rfic_nrst);
   gpioExport(host->host_rfic_npwdn);
   gpioExport(host->host_rfic_trig);
   gpioExport(host->host_rfic_irq1);
   gpioExport(host->host_rfic_irq2);
   gpioExport(host->host_gpio0);
   gpioExport(host->host_gpio1);
   gpioExport(host->host_gpio2); 
   gpioExport(host->host_gpio3); 
   gpioExport(host->host_gpio4);
   gpioExport(host->host_gpio5); 
   gpioExport(host->host_cpld_tms);
   gpioExport(host->host_cpld_tck);
   gpioExport(host->host_cpld_tdi);
   gpioExport(host->host_cpld_tdo);
   gpioExport(host->host_cpld_nclr);
   gpioExport(host->host_cpld_oe);
   gpioExport(host->host_led_red);
   gpioExport(host->host_led_green);
   gpioExport(host->host_led_blue);
   
   gpioSetDirection(host->host_fe_pwr_en_pin, outputPin);
   gpioSetDirection(host->host_rfic_nrst, outputPin);
   gpioSetDirection(host->host_rfic_npwdn, outputPin);
   gpioSetDirection(host->host_rfic_trig, outputPin);
   gpioSetDirection(host->host_rfic_irq1, inputPin);
   gpioSetDirection(host->host_rfic_irq2, inputPin);
   gpioSetDirection(host->host_gpio0, outputPin);
   gpioSetDirection(host->host_gpio1, outputPin);
   gpioSetDirection(host->host_gpio2, outputPin); 
   gpioSetDirection(host->host_gpio3, outputPin); 
   gpioSetDirection(host->host_gpio4, outputPin);
   gpioSetDirection(host->host_gpio5, outputPin); 
   gpioSetDirection(host->host_cpld_tms, outputPin);
   gpioSetDirection(host->host_cpld_tck, outputPin);
   gpioSetDirection(host->host_cpld_tdi, outputPin);
   gpioSetDirection(host->host_cpld_tdo, outputPin);
   gpioSetDirection(host->host_cpld_nclr, outputPin);
   gpioSetDirection(host->host_cpld_oe, outputPin);
   gpioSetDirection(host->host_led_red, outputPin);
   gpioSetDirection(host->host_led_green, outputPin);
   gpioSetDirection(host->host_led_blue, outputPin);

   gpioSetValue(host->host_led_blue, off);
   gpioSetValue(host->host_led_green, on);
   gpioSetValue(host->host_cpld_oe, on);
   gpioSetValue(host->host_cpld_nclr, on);

}

void host_spi_speed_change(host_device_handle_t *host){
   close(host->handle_spi);
   host->spi_tr.tx_buf        = (unsigned long)host->mosi;
   host->spi_tr.rx_buf        = (unsigned long)host->miso;
   host->spi_tr.delay_usecs   = 0;
   host->spi_tr.bits_per_word = 8;
   host->spi_tr.speed_hz      = 25000000;
   host->handle_spi           = open(host->device_name, O_RDWR);

}

void host_pheriph_deinit(host_device_handle_t *host){

   gpioSetValue(host->host_led_blue, on);
   gpioSetValue(host->host_led_green, off);

   gpioUnexport(host->host_fe_pwr_en_pin);
   gpioUnexport(host->host_rfic_nrst);
   gpioUnexport(host->host_rfic_npwdn);
   gpioUnexport(host->host_rfic_trig);
   gpioUnexport(host->host_rfic_irq1);
   gpioUnexport(host->host_rfic_irq2);
   gpioUnexport(host->host_gpio0);
   gpioUnexport(host->host_gpio1);
   gpioUnexport(host->host_gpio2); 
   gpioUnexport(host->host_gpio3); 
   gpioUnexport(host->host_gpio4);
   gpioUnexport(host->host_gpio5); 
   gpioUnexport(host->host_cpld_tms);
   gpioUnexport(host->host_cpld_tck);
   gpioUnexport(host->host_cpld_tdi);
   gpioUnexport(host->host_cpld_tdo);
   gpioUnexport(host->host_cpld_nclr);
   gpioUnexport(host->host_cpld_oe);
   gpioUnexport(host->host_led_red);
   gpioUnexport(host->host_led_green);
   gpioUnexport(host->host_led_blue);

   close(host->handle_spi);

   printf(">>>> DEINIT HOST PROCESSOR <<<<\n");

   host_mipi_capt_stop(host);
   host_mipi_close(host);
}

void host_rfic_power_up(host_device_handle_t *host){
   gpioSetValue(host->host_fe_pwr_en_pin, on);
   usleep(100000);
   gpioSetValue(host->host_rfic_npwdn, on);
   gpioSetValue(host->host_rfic_nrst, on);


   adi_pmic_PowerADAR690x(FIRST_PMIC);
   adi_pmic_PowerADAR690x(SECOND_PMIC);

}

void host_rfic_hard_reset(host_device_handle_t *host){     // rfic_nrst pin is associated with clk in CPLD...
   gpioSetValue(host->host_rfic_nrst, on);            // use soft reset using SPI.
   usleep(100000);
   gpioSetValue(host->host_rfic_nrst, off);
}

void print_spi_transaction(__u8 *miso, __u8 *mosi, __u32 length, __u8 slave)
{
	int i;
   printf("Select : %d,\n",slave);
	printf("MOSI : ");
	for (i = 0; i < length; i++)
		printf("%.2X ", mosi[i]);

   printf("\nMISO : ");
   for (i = 0; i < length; i++)
		printf("%.2X ", miso[i]);
   printf("\n");
}

void host_rfic_hw_trigger(host_device_handle_t *host){     // rfic_nrst pin is associated with clk in CPLD...
   gpioSetValue(host->host_rfic_trig, on);                 // use soft reset using SPI.
   usleep(10);
   gpioSetValue(host->host_rfic_trig, off);
}


static void errno_exit(const char *s)
{
    fprintf(stderr, "%s error %d, %s", s, errno, strerror(errno));
    printf("\n");
    exit(EXIT_FAILURE);
}

static int xioctl(int fh, int request, void *arg)
{
   int r;

   do
   {
      r = ioctl(fh, request, arg);
   } while (-1 == r && EINTR == errno);

   return r;
}


void host_mipi_open(host_device_handle_t *host)
{
   int ii;
   struct stat st;
   
   host->host_mipi_dev_name[0] = "/dev/video0";
   host->host_mipi_dev_name[1] = "/dev/video1";
   host->host_mipi_dev_name[2] = "/dev/video2";
   host->host_mipi_dev_name[3] = "/dev/video3";
   host->host_mipi_dev_name[4] = "/dev/video4";
   host->host_mipi_dev_name[5] = "/dev/video5";
   host->host_mipi_dev_name[6] = "/dev/video6";
   host->host_mipi_dev_name[7] = "/dev/video7";

   for (ii = HOST_MIPI_CH0_VCID0; ii < HOST_NUM_MIPI_CH; ii++)
   {
      if (-1 == stat(host->host_mipi_dev_name[ii], &st))
      {
         fprintf(stderr, "Cannot identify '%s': %d, %s\n", host->host_mipi_dev_name[ii], errno, strerror(errno));
         exit(EXIT_FAILURE);
      }

      if (!S_ISCHR(st.st_mode))
      {
         fprintf(stderr, "%s is no devicen", host->host_mipi_dev_name[ii]);
         exit(EXIT_FAILURE);
      }

      printf("open %s\n",host->host_mipi_dev_name[ii]);
      host->host_mipi_rfic_dev[ii] = open(host->host_mipi_dev_name[ii], O_RDWR /* required */ | O_NONBLOCK, 0);

      if (-1 == host->host_mipi_rfic_dev[ii])
      {
         fprintf(stderr, "Cannot open '%s': %d, %s\n", host->host_mipi_dev_name[ii], errno, strerror(errno));
         exit(EXIT_FAILURE);
      }
   }
   host_data_buf_init(host);   
}

void host_data_buf_init(host_device_handle_t *host)
{
   int total_len;
   int ii, jj;

   unsigned int page_size;

   total_len = (d_mode_len_byte_per_chip + 3*l_mode_len_byte_per_chip)*4;

   page_size = getpagesize ();
   total_len = (total_len + page_size - 1) & ~(page_size - 1);

   //host->data_buf[0] = (uint16_t *)calloc(total_len/2, sizeof(uint16_t));
   //host->data_buf[1] = (uint16_t *)calloc(total_len/2, sizeof(uint16_t));
   cudaMallocManaged((void**)&host->data_buf[0], total_len/2 * sizeof(uint16_t), cudaMemAttachHost);
   cudaMallocManaged((void**)&host->data_buf[1], total_len/2 * sizeof(uint16_t), cudaMemAttachHost);
   //cudaMallocManaged((void**)&host->data_buf[0], total_len/2 * sizeof(uint16_t), cudaMemAttachGlobal);
   //cudaMallocManaged((void**)&host->data_buf[1], total_len/2 * sizeof(uint16_t), cudaMemAttachGlobal);
   // host->data_buf = calloc(total_len/2, sizeof(uint16_t));
   for(ii = 0; ii < 4; ii++)
      host->sample_offset[ii] = mipi_ch_2_rfic_num[ii] * d_mode_len_byte_per_chip/2;
   for(jj = 0; jj < 3; jj++)
      for(ii = 0; ii < 4; ii++)
         host->sample_offset[4 + 4*jj + ii] = (d_mode_len_byte_per_chip/2*4) + (l_mode_len_byte_per_chip/2*4)*jj + mipi_ch_2_rfic_num[ii] * l_mode_len_byte_per_chip/2;
   for(ii=0;ii<16;ii++)
      printf("offset[%d] : %d\n", ii,  host->sample_offset[ii]);


}


static void host_init_mmap(host_device_handle_t *host, int num_device)
{
   struct v4l2_requestbuffers req;

   CLEAR(req);

   req.count = REQ_BUFF_NUM;
   req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
   req.memory = V4L2_MEMORY_MMAP;

   if (-1 == xioctl(host->host_mipi_rfic_dev[num_device], VIDIOC_REQBUFS, &req))  //  Initiate Memory Mapping, User Pointer I/O or DMA buffer I/O
   {
      if (EINVAL == errno)
      {
         fprintf(stderr, "%s does not support memory mapping\n", host->host_mipi_dev_name[num_device]);
         exit(EXIT_FAILURE);
      }
      else
      {
         errno_exit("VIDIOC_REQBUFS");
      }
   }

   if (req.count < 2)
   {
      fprintf(stderr, "Insufficient buffer memory on %s\n", host->host_mipi_dev_name[num_device]);
      exit(EXIT_FAILURE);
   }

   for (n_buffers = 0; n_buffers < req.count; ++n_buffers)
   {
      struct v4l2_buffer buf;

      CLEAR(buf);

      buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      buf.memory = V4L2_MEMORY_MMAP;
      buf.index = n_buffers;

      if (-1 == xioctl(host->host_mipi_rfic_dev[num_device], VIDIOC_QUERYBUF, &buf))
         errno_exit("VIDIOC_QUERYBUF");

      buffers[num_device][n_buffers].length = buf.length;
      buffers[num_device][n_buffers].start =
         mmap(NULL /* start anywhere */,
               buf.length,
               PROT_READ | PROT_WRITE /* required */,
               MAP_SHARED /* recommended */,
               host->host_mipi_rfic_dev[num_device], buf.m.offset);

      printf("device_num : %d, buff_ind : %d, buff_len : %d, buff_addr : 0x%X\n",num_device, buf.index, buf.length, buffers[num_device][n_buffers].start);

      if (MAP_FAILED == buffers[num_device][n_buffers].start)
         errno_exit("mmap");
   }
}

static void host_init_userptr(host_device_handle_t *host, int num_device)
{
   struct v4l2_requestbuffers req;

   CLEAR(req);

   //req.count = REQ_BUFF_NUM / 3;
   req.count = REQ_BUFF_NUM;
   req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
   req.memory = V4L2_MEMORY_USERPTR;

   if (-1 == xioctl(host->host_mipi_rfic_dev[num_device], VIDIOC_REQBUFS, &req))
   {
      if (EINVAL == errno)
      {
         fprintf(stderr, "%s does not support user pointer i/o\n", host->host_mipi_dev_name[num_device]);
         exit(EXIT_FAILURE);
      }
      else
      {
         errno_exit("VIDIOC_REQBUFS");
      }
   }


}


void host_mipi_init(host_device_handle_t *host)
{
   struct v4l2_capability cap;
   struct v4l2_cropcap cropcap;
   struct v4l2_crop crop;
   struct v4l2_format fmt;
   unsigned int min;

   for(int ii = HOST_MIPI_CH0_VCID0; ii < HOST_NUM_MIPI_CH; ii++)
   {
      if (-1 == xioctl(host->host_mipi_rfic_dev[ii], VIDIOC_QUERYCAP, &cap))  // Query device capability
      {
         if (EINVAL == errno)
         {
            fprintf(stderr, "%s is no V4L2 device\n", host->host_mipi_dev_name[ii]);
            exit(EXIT_FAILURE);
         }
         else
         {
            errno_exit("VIDIOC_QUERYCAP");
         }
      }
      if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))  // check video capture capability
      {
         fprintf(stderr, "%s is no video capture device\n", host->host_mipi_dev_name[ii]);
         exit(EXIT_FAILURE);
      }
      printf("open mipi device\n");
      /* Select video input, video standard and tune here. */

      CLEAR(cropcap);

      cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

      if (0 == xioctl(host->host_mipi_rfic_dev[ii], VIDIOC_CROPCAP, &cropcap)) // Information about the video cropping and scaling abilities
      {
         crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
         crop.c = cropcap.defrect; /* reset to default */

         if (-1 == xioctl(host->host_mipi_rfic_dev[ii], VIDIOC_S_CROP, &crop)) //Get(VIDIOC_G_CROP) or set(VIDIOC_S_CROP) the current cropping rectangle
         {
            switch (errno)
            {
            case EINVAL:
                  /* Cropping not supported. */
                  break;
            default:
                  /* Errors ignored. */
                  break;
            }
         }
      }
      else
      {
         /* Errors ignored. */
      }

      CLEAR(fmt);

      fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

      fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_Y12;
      // fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

      if (ii % 2 == 0) 
      {
         fmt.fmt.pix.width = D_MODE_NUM_SAMPLES_PER_RAMP*4;
         fmt.fmt.pix.height = D_MODE_NUM_RAMPS;
      }
      else
      {
         fmt.fmt.pix.width = L_MODE_NUM_SAMPLES_PER_RAMP*4;
         fmt.fmt.pix.height = L_MODE_NUM_RAMPS;
      }

      if (-1 == xioctl(host->host_mipi_rfic_dev[ii], VIDIOC_S_FMT, &fmt))  //Get(VIDIOC_G_FMT) or set(VIDIOC_S_FMT) the data format, try(VIDIOC_TRY_FMT) a format
         errno_exit("VIDIOC_S_FMT");


      fprintf(stderr, "****************************\n");
      fprintf(stderr, "radar_mode=%d \n", host->curr_profile);
      fprintf(stderr, "fmt.fmt.pix.width=%d \n", fmt.fmt.pix.width);
      fprintf(stderr, "fmt.fmt.pix.height=%d \n", fmt.fmt.pix.height);
      fprintf(stderr, "****************************\n");

      /* Buggy driver paranoia. */
      min = fmt.fmt.pix.width * 2;
      if (fmt.fmt.pix.bytesperline < min)
         fmt.fmt.pix.bytesperline = min;
      min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
      if (fmt.fmt.pix.sizeimage < min)
         fmt.fmt.pix.sizeimage = min;

      switch (io_mode)
      {
      case IO_METHOD_MMAP:
         host_init_mmap(host, ii);
         break;
      case IO_METHOD_USERPTR:
         host_init_userptr(host,ii);
         break;
      }
   }
}

void host_mipi_capt_start(host_device_handle_t *host)
{
   unsigned int i, cnt;
   enum v4l2_buf_type type;

   int jump_data_num_per_mode = 0;
   int jump_data_num_per_chip = 0;
  
   switch (io_mode)
   {
   case IO_METHOD_MMAP:
      for(int jj = HOST_MIPI_CH0_VCID0; jj < HOST_NUM_MIPI_CH; jj++)
      {
         for (i = 0; i < n_buffers; ++i)
         {
            struct v4l2_buffer buf;

            CLEAR(buf);
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            buf.index = i;

            if (-1 == xioctl(host->host_mipi_rfic_dev[jj], VIDIOC_QBUF, &buf))
                  errno_exit("VIDIOC_QBUF");
         }
         type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
         if (-1 == xioctl(host->host_mipi_rfic_dev[jj], VIDIOC_STREAMON, &type))
            errno_exit("VIDIOC_STREAMON");
      }
      break;

   case IO_METHOD_USERPTR:
      cnt = 0;

      for(int jj = HOST_MIPI_CH0_VCID0; jj < HOST_NUM_MIPI_CH; jj++)
      {
         printf("userptr setting : %d\n",jj);
         if(jj % 2 == 0)    // D mode
         {
            jump_data_num_per_mode = 0;
            jump_data_num_per_chip = D_MODE_TOTAL_NUM_SAMPLE*NUM_RX_PER_CHIP;

            for(int ii = 0; ii < REQ_BUFF_NUM; ii++){
               struct v4l2_buffer buf;
               CLEAR(buf);
               buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
               buf.memory = V4L2_MEMORY_USERPTR;
               buf.index = ii;
               buf.m.userptr = (unsigned long)(&host->data_buf[ii % 2][jump_data_num_per_mode + mipi_ch_2_rfic_num[jj / 2] * jump_data_num_per_chip]);
               //buf.m.userptr = (unsigned long)(host->data_buf + host->sample_offset[cnt]);
               //buf.m.userptr = (unsigned long)(host->data_buf[ii % 2]);
               buf.length = d_mode_len_byte_per_chip;

               if (-1 == xioctl(host->host_mipi_rfic_dev[jj], VIDIOC_QBUF, &buf))
                  errno_exit("VIDIOC_QBUF");
            }
            cnt++;
         }
         if(jj % 2 == 1)    // LMS Mode
         {
            for(int ii = 0; ii < REQ_BUFF_NUM; ii++){
               if(ii % 3 == 0) // L mode
               {
                  jump_data_num_per_mode = D_MODE_TOTAL_NUM_SAMPLE*TOTAL_NUM_RX;
                  jump_data_num_per_chip = L_MODE_TOTAL_NUM_SAMPLE*NUM_RX_PER_CHIP;
               }
               else if(ii % 3 == 1) // M mode
               {
                  jump_data_num_per_mode = (D_MODE_TOTAL_NUM_SAMPLE + L_MODE_TOTAL_NUM_SAMPLE) * TOTAL_NUM_RX;
                  jump_data_num_per_chip = M_MODE_TOTAL_NUM_SAMPLE*NUM_RX_PER_CHIP;
               }
               else if(ii % 3 == 2) // S mode
               {
                  jump_data_num_per_mode = (D_MODE_TOTAL_NUM_SAMPLE + L_MODE_TOTAL_NUM_SAMPLE + M_MODE_TOTAL_NUM_SAMPLE) * TOTAL_NUM_RX;
                  jump_data_num_per_chip = S_MODE_TOTAL_NUM_SAMPLE*NUM_RX_PER_CHIP;
               }

               struct v4l2_buffer buf;
               CLEAR(buf);
               buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
               buf.memory = V4L2_MEMORY_USERPTR;
               buf.index = ii;
               buf.m.userptr = (unsigned long)(&host->data_buf[ii / 3][jump_data_num_per_mode + mipi_ch_2_rfic_num[(jj - 1) / 2] * jump_data_num_per_chip]);
               //buf.m.userptr = (unsigned long)(host->data_buf[ii / 3]);
               buf.length = l_mode_len_byte_per_chip;

               if (-1 == xioctl(host->host_mipi_rfic_dev[jj], VIDIOC_QBUF, &buf))
                  errno_exit("VIDIOC_QBUF");
            }
            cnt++;
         }
         type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
         if (-1 == xioctl(host->host_mipi_rfic_dev[jj], VIDIOC_STREAMON, &type))
            errno_exit("VIDIOC_STREAMON");
      }
      break;

   }
}

static void write_files(int ch_num, const void *p, int size)
{
   int fd_buff = -1;
   int num;
   //Set file name
   time_t tm_time;
   struct tm *st_time;
   char filenanem[100];
   char filenamech[10];

   CLEAR(filenanem);

   time(&tm_time);
   st_time = localtime(&tm_time);
   strftime(filenanem, 100, "/mnt/ssd/%Y%m%d_%0l%M%S", st_time);
   // sprintf(filenamech, "_ch%d.raw",ch_num);
   // strcat(filenanem,filenamech);

   //fprintf(stderr, "%s\n", filenanem);

   fd_buff = open(filenanem, O_CREAT| O_WRONLY | O_TRUNC, 0644);
   if (fd_buff == -1)
   {
      perror("Open");
      exit(1);
   }

   if (write(fd_buff, p, size) != size)
   {
      perror("Write");
   }

   close(fd_buff);
}

static void process_image(int ch_num, const void *p, int size)
{
   // int out_buf;
   // if (out_buf)
   //    fwrite(p, size, 1, stdout);

   fflush(stderr);
   fprintf(stderr, ". size=%d \n", size);
   write_files(ch_num, p, size);
   fflush(stdout);
}

static int host_read_frame(host_device_handle_t *host)
{
   struct v4l2_buffer buf;
   unsigned int i;
   int ret;
   static int jump_data_num_per_mode;
   static int jump_data_num_per_chip;
   uint8_t b_num;

   b_num = host->buf_num;

   // jump_data_num = 0;
   // printf("host->curr_profile in host_read_frame : %d\n",host->curr_profile);

   switch(host->curr_profile)
   {
      case(D_MODE_BURST_NUM):
      {
         jump_data_num_per_mode = 0;
         jump_data_num_per_chip = D_MODE_TOTAL_NUM_SAMPLE*NUM_RX_PER_CHIP*2; // *2 for 2byte data
         //memset(host->data_buf[b_num], 0, d_mode_len_byte_per_chip + l_mode_len_byte_per_chip * 3);
         break;
      }
      case(L_MODE_BURST_NUM):
      {
         jump_data_num_per_mode += D_MODE_TOTAL_NUM_SAMPLE*TOTAL_NUM_RX*2;
         jump_data_num_per_chip =  L_MODE_TOTAL_NUM_SAMPLE*NUM_RX_PER_CHIP*2;
         break;
      }
      case(M_MODE_BURST_NUM):
      {
         jump_data_num_per_mode += L_MODE_TOTAL_NUM_SAMPLE*TOTAL_NUM_RX*2;
         jump_data_num_per_chip =  M_MODE_TOTAL_NUM_SAMPLE*NUM_RX_PER_CHIP*2;
         break;
      }
      case(S_MODE_BURST_NUM):
      {
         jump_data_num_per_mode += M_MODE_TOTAL_NUM_SAMPLE*TOTAL_NUM_RX*2;
         jump_data_num_per_chip =  S_MODE_TOTAL_NUM_SAMPLE*NUM_RX_PER_CHIP*2;
         break;
      }
   }

   switch (io_mode)
   {
   case IO_METHOD_MMAP:

      CLEAR(buf);

      buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      buf.memory = V4L2_MEMORY_MMAP;
      for(int ii = 0; ii < 4; ii++){
         if(host->curr_profile ==0)
            ret = xioctl(host->host_mipi_rfic_dev[2*ii], VIDIOC_DQBUF, &buf);
         else
            ret = xioctl(host->host_mipi_rfic_dev[2*ii+1], VIDIOC_DQBUF, &buf);

         if (-1 == ret)   // Exchange a buffer with the driver
         {
            switch (errno)
            {
            case EAGAIN:
                  return 0;
            case EIO:
                  /* Could ignore EIO, see spec. */

                  /* fall through */

            default:
                  errno_exit("VIDIOC_DQBUF");
            }
         }
         // assert(buf.index < n_buffers);
         
         /* copy from temp buffer to main data buffer */
         /*
         if(host->curr_profile == 0)
         {
            //memcpy((host->data_buf[b_num]) + (jump_data_num_per_mode + mipi_ch_2_rfic_num[ii] * jump_data_num_per_chip)/2, buffers[2*ii][buf.index].start, buf.bytesused);
            daq_memcpy_info_inst.dst = (void*)((host->data_buf[b_num]) + (jump_data_num_per_mode + mipi_ch_2_rfic_num[ii] * jump_data_num_per_chip)/2);
            daq_memcpy_info_inst.src = buffers[2*ii][buf.index].start;
            daq_memcpy_info_inst.copy_size = buf.bytesused;
            daq_memcpy_socket.send(&daq_memcpy_info_inst, sizeof(daq_memcpy_info_inst));
            //printf("[SEND] dst: 0x%x, src: 0x%x, size: %d\n", (uint32_t*)daq_memcpy_info_inst.dst, (uint32_t*)daq_memcpy_info_inst.src, daq_memcpy_info_inst.copy_size);
         }
         else
         {
            //memcpy((host->data_buf[b_num]) + (jump_data_num_per_mode + mipi_ch_2_rfic_num[ii] * jump_data_num_per_chip)/2, buffers[2*ii+1][buf.index].start, buf.bytesused);
            daq_memcpy_info_inst.dst = (void*)((host->data_buf[b_num]) + (jump_data_num_per_mode + mipi_ch_2_rfic_num[ii] * jump_data_num_per_chip)/2);
            daq_memcpy_info_inst.src = buffers[2*ii+1][buf.index].start;
            daq_memcpy_info_inst.copy_size = buf.bytesused;
            daq_memcpy_socket.send(&daq_memcpy_info_inst, sizeof(daq_memcpy_info_inst));
            //printf("[SEND] dst: 0x%x, src: 0x%x, size: %d\n", (uint32_t*)daq_memcpy_info_inst.dst, (uint32_t*)daq_memcpy_info_inst.src, daq_memcpy_info_inst.copy_size);
         }*/
           
         // process_image(ii, buffers[buf.index].start, buf.bytesused);
         //printf("ch:%d, ret: %d, size: %d, buf_idx: %d, jump_addr: %d, buff_addr: 0x%X\n",ii,ret,buf.bytesused,buf.index, jump_data_num_per_mode + mipi_ch_2_rfic_num[ii] * jump_data_num_per_chip,buffers[ii][buf.index].start);
         if(host->curr_profile ==0)
            ret = xioctl(host->host_mipi_rfic_dev[2*ii], VIDIOC_QBUF, &buf);
         else
            ret = xioctl(host->host_mipi_rfic_dev[2*ii+1], VIDIOC_QBUF, &buf);
         if (-1 == ret)
            errno_exit("VIDIOC_QBUF");
      }
      break;
   case IO_METHOD_USERPTR:
      CLEAR(buf);

      buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
      buf.memory = V4L2_MEMORY_USERPTR;
      for(int ii = 0; ii < 4; ii++)
      {  
         if(host->curr_profile ==0)
            ret = xioctl(host->host_mipi_rfic_dev[2*ii], VIDIOC_DQBUF, &buf);
         else
            ret = xioctl(host->host_mipi_rfic_dev[2*ii+1], VIDIOC_DQBUF, &buf);
         if (-1 == ret)
         {
            switch (errno)
            {
            case EAGAIN:
               return 0;

            case EIO:
               /* Could ignore EIO, see spec. */

               /* fall through */

            default:
               errno_exit("VIDIOC_DQBUF");
            }
         }
         //printf("ch:%d, ret : %d, size : %d, buf_idx : %d, buff_addr : 0x%X\n",ii,ret,buf.bytesused,buf.index, buf.m.userptr);
         if(host->curr_profile ==0)
            ret = xioctl(host->host_mipi_rfic_dev[2*ii], VIDIOC_QBUF, &buf);
         else
            ret = xioctl(host->host_mipi_rfic_dev[2*ii+1], VIDIOC_QBUF, &buf);
         if (-1 == ret)
               errno_exit("VIDIOC_QBUF");
      }
      break;
   }

   return 1;
}


int host_mipi_read_frame(host_device_handle_t *host)
{
   fd_set fdx[HOST_NUM_MIPI_CH];
   struct timeval tv;
   int rx[HOST_NUM_MIPI_CH];
   int isdone = 0;
   int idx = 0;
   int chk = 0;
   int ii = 0;
   int flag;

   for(ii =0; ii<HOST_NUM_MIPI_CH; ii++)
   {  
      FD_ZERO(&fdx[ii]);  
   }
   
   /* Timeout. */
   tv.tv_sec = 5;
   tv.tv_usec = 0;
   flag = 0;
   // printf("host->curr_profile in host_mipi_read_frame : %d \n",host->curr_profile);

   while(flag == 0)
   {
      if(host->curr_profile == 0)
      {
         FD_SET(host->host_mipi_rfic_dev[HOST_MIPI_CH0_VCID0], &fdx[HOST_MIPI_CH0_VCID0]);
         FD_SET(host->host_mipi_rfic_dev[HOST_MIPI_CH1_VCID0], &fdx[HOST_MIPI_CH1_VCID0]);
         FD_SET(host->host_mipi_rfic_dev[HOST_MIPI_CH2_VCID0], &fdx[HOST_MIPI_CH2_VCID0]);
         FD_SET(host->host_mipi_rfic_dev[HOST_MIPI_CH3_VCID0], &fdx[HOST_MIPI_CH3_VCID0]);
         host_rfic_hw_trigger(host);
         // usleep(10);
         rx[HOST_MIPI_CH0_VCID0] = select(host->host_mipi_rfic_dev[HOST_MIPI_CH0_VCID0]+1, &fdx[HOST_MIPI_CH0_VCID0], NULL, NULL, &tv);
         rx[HOST_MIPI_CH1_VCID0] = select(host->host_mipi_rfic_dev[HOST_MIPI_CH1_VCID0]+1, &fdx[HOST_MIPI_CH1_VCID0], NULL, NULL, &tv);
         rx[HOST_MIPI_CH2_VCID0] = select(host->host_mipi_rfic_dev[HOST_MIPI_CH2_VCID0]+1, &fdx[HOST_MIPI_CH2_VCID0], NULL, NULL, &tv);
         rx[HOST_MIPI_CH3_VCID0] = select(host->host_mipi_rfic_dev[HOST_MIPI_CH3_VCID0]+1, &fdx[HOST_MIPI_CH3_VCID0], NULL, NULL, &tv);
         if ((-1 == rx[HOST_MIPI_CH0_VCID0]) || (-1 == rx[HOST_MIPI_CH1_VCID0]) || (-1 == rx[HOST_MIPI_CH2_VCID0]) || (-1 == rx[HOST_MIPI_CH3_VCID0]) )
         {
            if (EINTR == errno)
            errno_exit("select");
         }

         if ((0 == rx[HOST_MIPI_CH0_VCID0]) || (0 == rx[HOST_MIPI_CH1_VCID0]) || (0 == rx[HOST_MIPI_CH2_VCID0]) || (0 == rx[HOST_MIPI_CH3_VCID0]) )
         {
            fprintf(stderr, "select timeout\n");
            exit(EXIT_FAILURE);
         }
         flag = FD_ISSET(host->host_mipi_rfic_dev[HOST_MIPI_CH0_VCID0], &fdx[HOST_MIPI_CH0_VCID0]) &
                FD_ISSET(host->host_mipi_rfic_dev[HOST_MIPI_CH1_VCID0], &fdx[HOST_MIPI_CH1_VCID0]) &
                FD_ISSET(host->host_mipi_rfic_dev[HOST_MIPI_CH2_VCID0], &fdx[HOST_MIPI_CH2_VCID0]) &
                FD_ISSET(host->host_mipi_rfic_dev[HOST_MIPI_CH3_VCID0], &fdx[HOST_MIPI_CH3_VCID0]);
      }
      else
      {
         FD_SET(host->host_mipi_rfic_dev[HOST_MIPI_CH0_VCID1], &fdx[HOST_MIPI_CH0_VCID1]);
         FD_SET(host->host_mipi_rfic_dev[HOST_MIPI_CH1_VCID1], &fdx[HOST_MIPI_CH1_VCID1]);
         FD_SET(host->host_mipi_rfic_dev[HOST_MIPI_CH2_VCID1], &fdx[HOST_MIPI_CH2_VCID1]);
         FD_SET(host->host_mipi_rfic_dev[HOST_MIPI_CH3_VCID1], &fdx[HOST_MIPI_CH3_VCID1]);
         host_rfic_hw_trigger(host);
         // usleep(10);
         rx[HOST_MIPI_CH0_VCID1] = select(host->host_mipi_rfic_dev[HOST_MIPI_CH0_VCID1]+1, &fdx[HOST_MIPI_CH0_VCID1], NULL, NULL, &tv);
         rx[HOST_MIPI_CH1_VCID1] = select(host->host_mipi_rfic_dev[HOST_MIPI_CH1_VCID1]+1, &fdx[HOST_MIPI_CH1_VCID1], NULL, NULL, &tv);
         rx[HOST_MIPI_CH2_VCID1] = select(host->host_mipi_rfic_dev[HOST_MIPI_CH2_VCID1]+1, &fdx[HOST_MIPI_CH2_VCID1], NULL, NULL, &tv);
         rx[HOST_MIPI_CH3_VCID1] = select(host->host_mipi_rfic_dev[HOST_MIPI_CH3_VCID1]+1, &fdx[HOST_MIPI_CH3_VCID1], NULL, NULL, &tv);
         if ((-1 == rx[HOST_MIPI_CH0_VCID1]) || (-1 == rx[HOST_MIPI_CH1_VCID1]) || (-1 == rx[HOST_MIPI_CH2_VCID1]) || (-1 == rx[HOST_MIPI_CH3_VCID1]) )
         {
            if (EINTR == errno)
            errno_exit("select");
         }

         if ((0 == rx[HOST_MIPI_CH0_VCID1]) || (0 == rx[HOST_MIPI_CH1_VCID1]) || (0 == rx[HOST_MIPI_CH2_VCID1]) || (0 == rx[HOST_MIPI_CH3_VCID1]) )
         {
            fprintf(stderr, "select timeout\n");
            exit(EXIT_FAILURE);
         }
         flag = FD_ISSET(host->host_mipi_rfic_dev[HOST_MIPI_CH0_VCID1], &fdx[HOST_MIPI_CH0_VCID1]) &
                FD_ISSET(host->host_mipi_rfic_dev[HOST_MIPI_CH1_VCID1], &fdx[HOST_MIPI_CH1_VCID1]) &
                FD_ISSET(host->host_mipi_rfic_dev[HOST_MIPI_CH2_VCID1], &fdx[HOST_MIPI_CH2_VCID1]) &
                FD_ISSET(host->host_mipi_rfic_dev[HOST_MIPI_CH3_VCID1], &fdx[HOST_MIPI_CH3_VCID1]);
      }
   }

   host_read_frame(host);

   /* EAGAIN - continue select loop. */
}

int host_mipi_capt_stop(host_device_handle_t *host)
{
   enum v4l2_buf_type type;
   type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

   for(int jj = HOST_MIPI_CH0_VCID0; jj < HOST_NUM_MIPI_CH; jj++)
   {
      if (-1 == xioctl(host->host_mipi_rfic_dev[jj], VIDIOC_STREAMOFF, &type))
         errno_exit("VIDIOC_STREAMOFF");
   }
}

void host_mipi_close(host_device_handle_t *host)
{
   int ii;
   struct stat st;
   int ret;
   

   for (ii = HOST_MIPI_CH0_VCID0; ii < HOST_NUM_MIPI_CH; ii++)
   {
      ret = close(host->host_mipi_rfic_dev[ii]);
      if (-1 == ret)
         errno_exit("close");
   }
}