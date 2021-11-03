//*****************************************************************
//  Project Name:  IR24X
//     File Name:  gpio_drv_info.h
//   Description:  auto generated file. do not modify!
// ----------------------------------------------------------------
//           C O D E    G E N E R A T O R    I N F O R M A T I O N
// ----------------------------------------------------------------
//     Generator: codegen.exe
//       Version: 0.0.1
//          Time: Mon Oct 12 15:37:39 2020
//    Datafile 0: gpio_drv_info_ir24m.yaml
//    Datafile 1: gpio_drv_info_ir24s.yaml
//    Datafile 2: gpio_drv_info_ir24x.yaml
//    Datafile 3: gpio_drv_info_lelogger.yaml
//            ID: 34B89165-34F8-4347-B253-4F49D447D51
//
// ----------------------------------------------------------------
//           U S E R    I N F O R M A T I O N
// ----------------------------------------------------------------
// Computer Name: SSONGDESKTOP
//     User Name: user
//     Directory: D:\Workdir\BTS24MX_LWIP2\ir24x_sw\ir24x_main\prebuild\gpio_info
//
// ----------------------------------------------------------------
//           P R O J E C T    S U M M A R Y
// ----------------------------------------------------------------
//*****************************************************************
#ifndef GPIO_DRV_INFO_H__
#define GPIO_DRV_INFO_H__

/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "gpio_drv_cfg.h"
#include "gpio_drv_dtypes.h"
#include "system.h"

#include "gpio_drv_axi/gpio_drv_axi.h"
#include "gpio_drv_info.h"
#include "gpio_drv_ps/gpio_drv_ps.h"

/* module specific types  */
typedef enum
{
// gpio_drv_info_ir24m.yaml
#if SYS_SYSTEM_VERSION >= SYS_RADAR_VERSION_BEV31
    gpio_id_AL_INTRDY,
    gpio_id_BT_EN,
    gpio_id_CAM_PWDN,
    gpio_id_CAM_PWR_EN,
    gpio_id_CAM_STROBE,
    gpio_id_CAM_nRESET,
    gpio_id_FE_SHDN,
    gpio_id_FE_TX_EN,
    gpio_id_GETH_LED0,
    gpio_id_GETH_LED1,
    gpio_id_GETH_nRESET,
    gpio_id_GPS_RESETN,
    gpio_id_GPS_TIMEPULSE,
    gpio_id_IOMUXSEL0,
    gpio_id_LEDB,
    gpio_id_LEDG,
    gpio_id_LEDR,
    gpio_id_LORA_RESETN,
    gpio_id_MMC_nRESET,
    gpio_id_MT_INT,
    gpio_id_PL_DEBUG16_P135,
    gpio_id_PL_DEBUG17_P136,
    gpio_id_PL_DEBUG18_P137,
    gpio_id_PL_DEBUG19_P138,
    gpio_id_PL_DEBUG20_P139,
    gpio_id_PL_DEBUG21_P140,
    gpio_id_PL_DEBUG22_P141,
    gpio_id_PL_DEBUG23_P142,
    gpio_id_PL_DEBUG24_P147,
    gpio_id_PL_DEBUG25_P148,
    gpio_id_PL_DEBUG26_P149,
    gpio_id_PL_DEBUG27_P150,
    gpio_id_PL_DEBUG28_P151,
    gpio_id_PL_DEBUG29_P152,
    gpio_id_PL_DEBUG30_P153,
    gpio_id_PL_DEBUG31_P154,
    gpio_id_PS_DEBUG0,
    gpio_id_PS_DEBUG1,
    gpio_id_PS_DEBUG2,
    gpio_id_RS485_DE,
    gpio_id_RS485_nRE,
    gpio_id_SSRA,
    gpio_id_SSRB,
    gpio_id_WDG_CLEAR,
    gpio_id_WL_EN,
    gpio_id_WL_IRQ,
#endif // SYS_SYSTEM_VERSION >= SYS_RADAR_VERSION_BEV31
// gpio_drv_info_ir24s.yaml
#if(SYS_SYSTEM_VERSION >= SYS_RADAR_VERSION_BEV23) && (SYS_SYSTEM_VERSION <= SYS_RADAR_VERSION_BEV25)
    gpio_id_FE_GPIO11,
    gpio_id_FE_GPIO12,
    gpio_id_FE_GPIO13,
    gpio_id_FE_GPIO14,
    gpio_id_FE_SHDN,
    gpio_id_FE_TX_EN,
    gpio_id_GETH_LED0,
    gpio_id_GETH_LED1,
    gpio_id_GETH_nRESET,
    gpio_id_GPS_RESETN,
    gpio_id_GPS_TIMEPULSE,
    gpio_id_IOMUXSEL0,
    gpio_id_LEDB,
    gpio_id_LEDG,
    gpio_id_LEDR,
    gpio_id_LORA_RESETN,
    gpio_id_PL_DEBUG16,
    gpio_id_PL_DEBUG17,
    gpio_id_PL_DEBUG18,
    gpio_id_PL_DEBUG19,
    gpio_id_PL_DEBUG20,
    gpio_id_PL_DEBUG21,
    gpio_id_PL_DEBUG22,
    gpio_id_PL_DEBUG23,
    gpio_id_PL_DEBUG24,
    gpio_id_PL_DEBUG25,
    gpio_id_PL_DEBUG26,
    gpio_id_PL_DEBUG27,
    gpio_id_PL_DEBUG28,
    gpio_id_PL_DEBUG29,
    gpio_id_PL_DEBUG30,
    gpio_id_PL_DEBUG31,
    gpio_id_PS_DEBUG0,
    gpio_id_PS_DEBUG1,
    gpio_id_PS_DEBUG2,
    gpio_id_RS485_DE,
    gpio_id_RS485_nRE,
    gpio_id_SCANRATE_10FPS_EN,
    gpio_id_SCANRATE_15FPS_EN,
    gpio_id_SCANRATE_20FPS_EN,
    gpio_id_SCANRATE_25FPS_EN,
    gpio_id_SCANRATE_30FPS_EN,
    gpio_id_SCANRATE_TIMER_EN,
    gpio_id_SSRA,
    gpio_id_SSRB,
    gpio_id_SSRC,
    gpio_id_SSRD,
    gpio_id_WDG_CLEAR,
#endif // (SYS_SYSTEM_VERSION >= SYS_RADAR_VERSION_BEV23) && (SYS_SYSTEM_VERSION <= SYS_RADAR_VERSION_BEV25)
// gpio_drv_info_ir24x.yaml
#if SYS_SYSTEM_VERSION == SYS_RADAR_VERSION_BEVX10
    gpio_id_BE_VIO02,
    gpio_id_BE_VIO03,
    gpio_id_BE_VIO07,
    gpio_id_BE_VIO16,
    gpio_id_BE_VIO17,
    gpio_id_BE_VIO18,
    gpio_id_BE_VIO19,
    gpio_id_BE_VIO22,
    gpio_id_BE_VIO23,
    gpio_id_FE_PWR_EN,
    gpio_id_FE_TX_EN,
    gpio_id_GPS_RESETN,
    gpio_id_LEDB,
    gpio_id_LEDG,
    gpio_id_LEDR,
    gpio_id_LORA_RESETN,
    gpio_id_PL_DEBUG0,
    gpio_id_PL_DEBUG1,
    gpio_id_PL_DEBUG2,
    gpio_id_PL_DEBUG3,
    gpio_id_PL_DEBUG4,
    gpio_id_PL_DEBUG5,
    gpio_id_PL_DEBUG6,
    gpio_id_PL_DEBUG7,
    gpio_id_PS_DEBUG0,
    gpio_id_RS485_DE,
    gpio_id_RS485_nRE,
    gpio_id_SSRA,
    gpio_id_SSRB,
    gpio_id_SSRC,
    gpio_id_SSRD,
    gpio_id_WDG_CLEAR,
    gpio_id_WIFI_HIBN,
    gpio_id_WIFI_RESETN,
#endif // SYS_SYSTEM_VERSION == SYS_RADAR_VERSION_BEVX10
// gpio_drv_info_lelogger.yaml
#if(SYS_SYSTEM_VERSION == SYS_LOGGER_VERSION_V01)
    gpio_id_EQ_RX_DE0,
    gpio_id_EQ_RX_DE1,
    gpio_id_EQ_RX_DIS,
    gpio_id_EQ_RX_LOS,
    gpio_id_EQ_RX_POL,
    gpio_id_EQ_RX_SWG,
    gpio_id_EQ_TX_DE0,
    gpio_id_EQ_TX_DE1,
    gpio_id_EQ_TX_DIS,
    gpio_id_EQ_TX_LOS,
    gpio_id_EQ_TX_POL,
    gpio_id_EQ_TX_SWG,
    gpio_id_LED,
    gpio_id_LEDB_CH0,
    gpio_id_LEDB_CH1,
    gpio_id_LEDB_CH2,
    gpio_id_LEDB_CH3,
    gpio_id_LEDG_CH0,
    gpio_id_LEDG_CH1,
    gpio_id_LEDG_CH2,
    gpio_id_LEDG_CH3,
    gpio_id_LEDR_CH0,
    gpio_id_LEDR_CH1,
    gpio_id_LEDR_CH2,
    gpio_id_LEDR_CH3,
    gpio_id_aurora_reset,
    gpio_id_channel_up,
    gpio_id_crc_pass_fail_n,
    gpio_id_crc_valid,
    gpio_id_device_dna_high,
    gpio_id_device_dna_low,
    gpio_id_device_dna_read_done,
    gpio_id_device_dna_read_enable,
    gpio_id_frame_err,
    gpio_id_hard_err,
    gpio_id_lane_up,
    gpio_id_pll_not_locked_out,
    gpio_id_rx_resetdone_out,
    gpio_id_soft_err,
    gpio_id_tx_lock,
    gpio_id_tx_resetdone_out,
#endif // (SYS_SYSTEM_VERSION == SYS_LOGGER_VERSION_V01)
    gpio_id_MAX
} gpio_id_t;


typedef struct
{
    gpio_id_t id;
    int8_t name[32];
    void *gpioinst;
    gpio_info_type_t gpiotype;
    gpio_direction_t direction;
    gpio_enable_t enable;
    uint8_t pinnum;
    uint8_t defaultval;
    gpio_inttype_t inttype;
    gpio_isr_handler isrhandler;
} gpio_info_t;


/* declare extern global variables */
// gpio_drv_info_ir24m.yaml
#if SYS_SYSTEM_VERSION >= SYS_RADAR_VERSION_BEV31
extern gpio_ps_object_t gpio_ps; //XPAR_XGPIOPS_0_DEVICE_ID
#endif                           // SYS_SYSTEM_VERSION >= SYS_RADAR_VERSION_BEV31
// gpio_drv_info_ir24s.yaml
#if(SYS_SYSTEM_VERSION >= SYS_RADAR_VERSION_BEV23) && (SYS_SYSTEM_VERSION <= SYS_RADAR_VERSION_BEV25)
extern gpio_axi_object_t gpio0_axi; //XPAR_GPIO_0_DEVICE_ID
extern gpio_axi_object_t gpio1_axi; //XPAR_GPIO_1_DEVICE_ID
extern gpio_axi_object_t gpio2_axi; //XPAR_GPIO_2_DEVICE_ID
extern gpio_ps_object_t gpio_ps;    //XPAR_XGPIOPS_0_DEVICE_ID
#endif                              // (SYS_SYSTEM_VERSION >= SYS_RADAR_VERSION_BEV23) && (SYS_SYSTEM_VERSION <= SYS_RADAR_VERSION_BEV25)
// gpio_drv_info_ir24x.yaml
#if SYS_SYSTEM_VERSION == SYS_RADAR_VERSION_BEVX10
extern gpio_axi_object_t gpio0_axi; //XPAR_GPIO_0_DEVICE_ID
extern gpio_ps_object_t gpio_ps;    //XPAR_XGPIOPS_0_DEVICE_ID
#endif                              // SYS_SYSTEM_VERSION == SYS_RADAR_VERSION_BEVX10
// gpio_drv_info_lelogger.yaml
#if(SYS_SYSTEM_VERSION == SYS_LOGGER_VERSION_V01)
extern gpio_axi_object_t gpio0_axi; //XPAR_GPIO_0_DEVICE_ID
extern gpio_axi_object_t gpio1_axi; //XPAR_DEVICEDNA_AXI_GPIO_DNA_CONTROL_DEVICE_ID
extern gpio_axi_object_t gpio2_axi; //XPAR_DEVICEDNA_AXI_GPIO_DNA_READER_DEVICE_ID
extern gpio_axi_object_t gpio3_axi; //XPAR_AXI_GPIO_BOARDCONTROL_DEVICE_ID
extern gpio_ps_object_t gpio_ps;    //XPAR_XGPIOPS_0_DEVICE_ID
#endif                              // (SYS_SYSTEM_VERSION == SYS_LOGGER_VERSION_V01)

extern gpio_info_t gpio_info_table[];


/* declare extern global functions */
extern void gpio_drv_info_init(void);
extern void gpio_drv_info_unittest(void);
#endif /* GPIO_DRV_INFO_H__ */
