//*****************************************************************
//  Project Name:  IR24X
//     File Name:  gpio_drv_info.c
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
/* include system primitive types */
#include "gpio_drv_info.h"
#include "bts.h"
#include "os.h"
#include "system.h"

/* include system driver header */
#include "gpio_drv.h"
/* include system bsp header */


/* include system application header */


/* final include module header */

/* declare global variables */
// gpio_drv_info_ir24m.yaml
#if SYS_SYSTEM_VERSION >= SYS_RADAR_VERSION_BEV31


gpio_ps_object_t gpio_ps; //XPAR_XGPIOPS_0_DEVICE_ID


BTS_WEAK void gpio_isr_handler_AL_INTRDY(void *param);
BTS_WEAK void gpio_isr_handler_BT_EN(void *param);
BTS_WEAK void gpio_isr_handler_CAM_PWDN(void *param);
BTS_WEAK void gpio_isr_handler_CAM_PWR_EN(void *param);
BTS_WEAK void gpio_isr_handler_CAM_STROBE(void *param);
BTS_WEAK void gpio_isr_handler_CAM_nRESET(void *param);
BTS_WEAK void gpio_isr_handler_FE_SHDN(void *param);
BTS_WEAK void gpio_isr_handler_FE_TX_EN(void *param);
BTS_WEAK void gpio_isr_handler_GETH_LED0(void *param);
BTS_WEAK void gpio_isr_handler_GETH_LED1(void *param);
BTS_WEAK void gpio_isr_handler_GETH_nRESET(void *param);
BTS_WEAK void gpio_isr_handler_GPS_RESETN(void *param);
BTS_WEAK void gpio_isr_handler_GPS_TIMEPULSE(void *param);
BTS_WEAK void gpio_isr_handler_IOMUXSEL0(void *param);
BTS_WEAK void gpio_isr_handler_LEDB(void *param);
BTS_WEAK void gpio_isr_handler_LEDG(void *param);
BTS_WEAK void gpio_isr_handler_LEDR(void *param);
BTS_WEAK void gpio_isr_handler_LORA_RESETN(void *param);
BTS_WEAK void gpio_isr_handler_MMC_nRESET(void *param);
BTS_WEAK void gpio_isr_handler_MT_INT(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG16_P135(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG17_P136(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG18_P137(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG19_P138(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG20_P139(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG21_P140(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG22_P141(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG23_P142(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG24_P147(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG25_P148(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG26_P149(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG27_P150(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG28_P151(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG29_P152(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG30_P153(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG31_P154(void *param);
BTS_WEAK void gpio_isr_handler_PS_DEBUG0(void *param);
BTS_WEAK void gpio_isr_handler_PS_DEBUG1(void *param);
BTS_WEAK void gpio_isr_handler_PS_DEBUG2(void *param);
BTS_WEAK void gpio_isr_handler_RS485_DE(void *param);
BTS_WEAK void gpio_isr_handler_RS485_nRE(void *param);
BTS_WEAK void gpio_isr_handler_SSRA(void *param);
BTS_WEAK void gpio_isr_handler_SSRB(void *param);
BTS_WEAK void gpio_isr_handler_WDG_CLEAR(void *param);
BTS_WEAK void gpio_isr_handler_WL_EN(void *param);
BTS_WEAK void gpio_isr_handler_WL_IRQ(void *param);


gpio_info_t gpio_info_table[] =
    {
        // id               name,           axi or ps,          direction,          enable,   pinnum, defaultval, inten, inttype, isrhandler
        {gpio_id_AL_INTRDY, "AL_INTRDY", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_in, gpio_enable, 49, 1, gpio_inttype_none, gpio_isr_handler_AL_INTRDY},
        {gpio_id_BT_EN, "BT_EN", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 40, 0, gpio_inttype_none, gpio_isr_handler_BT_EN},
        {gpio_id_CAM_PWDN, "CAM_PWDN", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 67, 0, gpio_inttype_none, gpio_isr_handler_CAM_PWDN},
        {gpio_id_CAM_PWR_EN, "CAM_PWR_EN", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 65, 0, gpio_inttype_none, gpio_isr_handler_CAM_PWR_EN},
        {gpio_id_CAM_STROBE, "CAM_STROBE", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_in, gpio_enable, 68, 0, gpio_inttype_none, gpio_isr_handler_CAM_STROBE},
        {gpio_id_CAM_nRESET, "CAM_nRESET", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 66, 0, gpio_inttype_none, gpio_isr_handler_CAM_nRESET},
        {gpio_id_FE_SHDN, "FE_SHDN", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 54, 0, gpio_inttype_none, gpio_isr_handler_FE_SHDN},
        {gpio_id_FE_TX_EN, "FE_TX_EN", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 63, 1, gpio_inttype_none, gpio_isr_handler_FE_TX_EN},
        {gpio_id_GETH_LED0, "GETH_LED0", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_in, gpio_enable, 50, 0, gpio_inttype_none, gpio_isr_handler_GETH_LED0},
        {gpio_id_GETH_LED1, "GETH_LED1", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_in, gpio_enable, 51, 0, gpio_inttype_none, gpio_isr_handler_GETH_LED1},
        {gpio_id_GETH_nRESET, "GETH_nRESET", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 45, 1, gpio_inttype_none, gpio_isr_handler_GETH_nRESET},
        {gpio_id_GPS_RESETN, "GPS_RESETN", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 62, 1, gpio_inttype_none, gpio_isr_handler_GPS_RESETN},
        {gpio_id_GPS_TIMEPULSE, "GPS_TIMEPULSE", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_in, gpio_enable, 61, 0, gpio_inttype_none, gpio_isr_handler_GPS_TIMEPULSE},
        {gpio_id_IOMUXSEL0, "IOMUXSEL0", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 86, 0, gpio_inttype_none, gpio_isr_handler_IOMUXSEL0},
        {gpio_id_LEDB, "LEDB", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 59, 0, gpio_inttype_none, gpio_isr_handler_LEDB},
        {gpio_id_LEDG, "LEDG", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 58, 0, gpio_inttype_none, gpio_isr_handler_LEDG},
        {gpio_id_LEDR, "LEDR", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 57, 0, gpio_inttype_none, gpio_isr_handler_LEDR},
        {gpio_id_LORA_RESETN, "LORA_RESETN", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 64, 1, gpio_inttype_none, gpio_isr_handler_LORA_RESETN},
        {gpio_id_MMC_nRESET, "MMC_nRESET", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 46, 1, gpio_inttype_none, gpio_isr_handler_MMC_nRESET},
        {gpio_id_MT_INT, "MT_INT", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_in, gpio_enable, 48, 1, gpio_inttype_none, gpio_isr_handler_MT_INT},
        {gpio_id_PL_DEBUG16_P135, "PL_DEBUG16_P135", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 70, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG16_P135},
        {gpio_id_PL_DEBUG17_P136, "PL_DEBUG17_P136", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 71, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG17_P136},
        {gpio_id_PL_DEBUG18_P137, "PL_DEBUG18_P137", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 72, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG18_P137},
        {gpio_id_PL_DEBUG19_P138, "PL_DEBUG19_P138", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 73, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG19_P138},
        {gpio_id_PL_DEBUG20_P139, "PL_DEBUG20_P139", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 74, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG20_P139},
        {gpio_id_PL_DEBUG21_P140, "PL_DEBUG21_P140", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 75, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG21_P140},
        {gpio_id_PL_DEBUG22_P141, "PL_DEBUG22_P141", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 76, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG22_P141},
        {gpio_id_PL_DEBUG23_P142, "PL_DEBUG23_P142", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 77, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG23_P142},
        {gpio_id_PL_DEBUG24_P147, "PL_DEBUG24_P147", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 78, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG24_P147},
        {gpio_id_PL_DEBUG25_P148, "PL_DEBUG25_P148", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 79, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG25_P148},
        {gpio_id_PL_DEBUG26_P149, "PL_DEBUG26_P149", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 80, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG26_P149},
        {gpio_id_PL_DEBUG27_P150, "PL_DEBUG27_P150", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 81, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG27_P150},
        {gpio_id_PL_DEBUG28_P151, "PL_DEBUG28_P151", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 82, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG28_P151},
        {gpio_id_PL_DEBUG29_P152, "PL_DEBUG29_P152", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 83, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG29_P152},
        {gpio_id_PL_DEBUG30_P153, "PL_DEBUG30_P153", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 84, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG30_P153},
        {gpio_id_PL_DEBUG31_P154, "PL_DEBUG31_P154", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 85, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG31_P154},
        {gpio_id_PS_DEBUG0, "PS_DEBUG0", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 7, 0, gpio_inttype_none, gpio_isr_handler_PS_DEBUG0},
        {gpio_id_PS_DEBUG1, "PS_DEBUG1", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 8, 0, gpio_inttype_none, gpio_isr_handler_PS_DEBUG1},
        {gpio_id_PS_DEBUG2, "PS_DEBUG2", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 9, 0, gpio_inttype_none, gpio_isr_handler_PS_DEBUG2},
        {gpio_id_RS485_DE, "RS485_DE", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 56, 1, gpio_inttype_none, gpio_isr_handler_RS485_DE},
        {gpio_id_RS485_nRE, "RS485_nRE", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 55, 1, gpio_inttype_none, gpio_isr_handler_RS485_nRE},
        {gpio_id_SSRA, "SSRA", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 60, 1, gpio_inttype_none, gpio_isr_handler_SSRA},
        {gpio_id_SSRB, "SSRB", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 69, 1, gpio_inttype_none, gpio_isr_handler_SSRB},
        {gpio_id_WDG_CLEAR, "WDG_CLEAR", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 0, 0, gpio_inttype_none, gpio_isr_handler_WDG_CLEAR},
        {gpio_id_WL_EN, "WL_EN", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 41, 0, gpio_inttype_none, gpio_isr_handler_WL_EN},
        {gpio_id_WL_IRQ, "WL_IRQ", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_in, gpio_enable, 44, 0, gpio_inttype_none, gpio_isr_handler_WL_IRQ},
};

/* declare static variables */


/* static function prototypes */


/* functions */
void gpio_drv_info_unittest(void)
{
    /* INPUT port gpio_id_AL_INTRDY, gpio_ps GPIO port 49, read test */
    printf("gpio_id_AL_INTRDY value is %ld\n", gpio_drv_read(gpio_id_AL_INTRDY));

    /* OUTPUT port gpio_id_BT_EN, gpio_ps GPIO port 40, clear/set/clear test */
    gpio_drv_write(gpio_id_BT_EN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_BT_EN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_BT_EN, 0);

    /* OUTPUT port gpio_id_CAM_PWDN, gpio_ps GPIO port 67, clear/set/clear test */
    gpio_drv_write(gpio_id_CAM_PWDN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_CAM_PWDN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_CAM_PWDN, 0);

    /* OUTPUT port gpio_id_CAM_PWR_EN, gpio_ps GPIO port 65, clear/set/clear test */
    gpio_drv_write(gpio_id_CAM_PWR_EN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_CAM_PWR_EN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_CAM_PWR_EN, 0);

    /* INPUT port gpio_id_CAM_STROBE, gpio_ps GPIO port 68, read test */
    printf("gpio_id_CAM_STROBE value is %ld\n", gpio_drv_read(gpio_id_CAM_STROBE));

    /* OUTPUT port gpio_id_CAM_nRESET, gpio_ps GPIO port 66, clear/set/clear test */
    gpio_drv_write(gpio_id_CAM_nRESET, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_CAM_nRESET, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_CAM_nRESET, 0);

    /* OUTPUT port gpio_id_FE_SHDN, gpio_ps GPIO port 54, clear/set/clear test */
    gpio_drv_write(gpio_id_FE_SHDN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_FE_SHDN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_FE_SHDN, 0);

    /* OUTPUT port gpio_id_FE_TX_EN, gpio_ps GPIO port 63, clear/set/clear test */
    gpio_drv_write(gpio_id_FE_TX_EN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_FE_TX_EN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_FE_TX_EN, 0);

    /* INPUT port gpio_id_GETH_LED0, gpio_ps GPIO port 50, read test */
    printf("gpio_id_GETH_LED0 value is %ld\n", gpio_drv_read(gpio_id_GETH_LED0));

    /* INPUT port gpio_id_GETH_LED1, gpio_ps GPIO port 51, read test */
    printf("gpio_id_GETH_LED1 value is %ld\n", gpio_drv_read(gpio_id_GETH_LED1));

    /* OUTPUT port gpio_id_GETH_nRESET, gpio_ps GPIO port 45, clear/set/clear test */
    gpio_drv_write(gpio_id_GETH_nRESET, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_GETH_nRESET, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_GETH_nRESET, 0);

    /* OUTPUT port gpio_id_GPS_RESETN, gpio_ps GPIO port 62, clear/set/clear test */
    gpio_drv_write(gpio_id_GPS_RESETN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_GPS_RESETN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_GPS_RESETN, 0);

    /* INPUT port gpio_id_GPS_TIMEPULSE, gpio_ps GPIO port 61, read test */
    printf("gpio_id_GPS_TIMEPULSE value is %ld\n", gpio_drv_read(gpio_id_GPS_TIMEPULSE));

    /* OUTPUT port gpio_id_IOMUXSEL0, gpio_ps GPIO port 86, clear/set/clear test */
    gpio_drv_write(gpio_id_IOMUXSEL0, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_IOMUXSEL0, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_IOMUXSEL0, 0);

    /* OUTPUT port gpio_id_LEDB, gpio_ps GPIO port 59, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDB, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDB, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDB, 0);

    /* OUTPUT port gpio_id_LEDG, gpio_ps GPIO port 58, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDG, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDG, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDG, 0);

    /* OUTPUT port gpio_id_LEDR, gpio_ps GPIO port 57, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDR, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDR, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDR, 0);

    /* OUTPUT port gpio_id_LORA_RESETN, gpio_ps GPIO port 64, clear/set/clear test */
    gpio_drv_write(gpio_id_LORA_RESETN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LORA_RESETN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LORA_RESETN, 0);

    /* OUTPUT port gpio_id_MMC_nRESET, gpio_ps GPIO port 46, clear/set/clear test */
    gpio_drv_write(gpio_id_MMC_nRESET, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_MMC_nRESET, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_MMC_nRESET, 0);

    /* INPUT port gpio_id_MT_INT, gpio_ps GPIO port 48, read test */
    printf("gpio_id_MT_INT value is %ld\n", gpio_drv_read(gpio_id_MT_INT));

    /* OUTPUT port gpio_id_PL_DEBUG16_P135, gpio_ps GPIO port 70, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG16_P135, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG16_P135, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG16_P135, 0);

    /* OUTPUT port gpio_id_PL_DEBUG17_P136, gpio_ps GPIO port 71, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG17_P136, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG17_P136, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG17_P136, 0);

    /* OUTPUT port gpio_id_PL_DEBUG18_P137, gpio_ps GPIO port 72, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG18_P137, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG18_P137, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG18_P137, 0);

    /* OUTPUT port gpio_id_PL_DEBUG19_P138, gpio_ps GPIO port 73, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG19_P138, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG19_P138, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG19_P138, 0);

    /* OUTPUT port gpio_id_PL_DEBUG20_P139, gpio_ps GPIO port 74, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG20_P139, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG20_P139, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG20_P139, 0);

    /* OUTPUT port gpio_id_PL_DEBUG21_P140, gpio_ps GPIO port 75, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG21_P140, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG21_P140, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG21_P140, 0);

    /* OUTPUT port gpio_id_PL_DEBUG22_P141, gpio_ps GPIO port 76, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG22_P141, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG22_P141, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG22_P141, 0);

    /* OUTPUT port gpio_id_PL_DEBUG23_P142, gpio_ps GPIO port 77, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG23_P142, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG23_P142, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG23_P142, 0);

    /* OUTPUT port gpio_id_PL_DEBUG24_P147, gpio_ps GPIO port 78, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG24_P147, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG24_P147, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG24_P147, 0);

    /* OUTPUT port gpio_id_PL_DEBUG25_P148, gpio_ps GPIO port 79, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG25_P148, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG25_P148, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG25_P148, 0);

    /* OUTPUT port gpio_id_PL_DEBUG26_P149, gpio_ps GPIO port 80, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG26_P149, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG26_P149, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG26_P149, 0);

    /* OUTPUT port gpio_id_PL_DEBUG27_P150, gpio_ps GPIO port 81, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG27_P150, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG27_P150, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG27_P150, 0);

    /* OUTPUT port gpio_id_PL_DEBUG28_P151, gpio_ps GPIO port 82, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG28_P151, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG28_P151, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG28_P151, 0);

    /* OUTPUT port gpio_id_PL_DEBUG29_P152, gpio_ps GPIO port 83, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG29_P152, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG29_P152, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG29_P152, 0);

    /* OUTPUT port gpio_id_PL_DEBUG30_P153, gpio_ps GPIO port 84, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG30_P153, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG30_P153, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG30_P153, 0);

    /* OUTPUT port gpio_id_PL_DEBUG31_P154, gpio_ps GPIO port 85, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG31_P154, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG31_P154, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG31_P154, 0);

    /* OUTPUT port gpio_id_PS_DEBUG0, gpio_ps GPIO port 7, clear/set/clear test */
    gpio_drv_write(gpio_id_PS_DEBUG0, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PS_DEBUG0, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PS_DEBUG0, 0);

    /* OUTPUT port gpio_id_PS_DEBUG1, gpio_ps GPIO port 8, clear/set/clear test */
    gpio_drv_write(gpio_id_PS_DEBUG1, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PS_DEBUG1, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PS_DEBUG1, 0);

    /* OUTPUT port gpio_id_PS_DEBUG2, gpio_ps GPIO port 9, clear/set/clear test */
    gpio_drv_write(gpio_id_PS_DEBUG2, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PS_DEBUG2, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PS_DEBUG2, 0);

    /* OUTPUT port gpio_id_RS485_DE, gpio_ps GPIO port 56, clear/set/clear test */
    gpio_drv_write(gpio_id_RS485_DE, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_RS485_DE, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_RS485_DE, 0);

    /* OUTPUT port gpio_id_RS485_nRE, gpio_ps GPIO port 55, clear/set/clear test */
    gpio_drv_write(gpio_id_RS485_nRE, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_RS485_nRE, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_RS485_nRE, 0);

    /* OUTPUT port gpio_id_SSRA, gpio_ps GPIO port 60, clear/set/clear test */
    gpio_drv_write(gpio_id_SSRA, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRA, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRA, 0);

    /* OUTPUT port gpio_id_SSRB, gpio_ps GPIO port 69, clear/set/clear test */
    gpio_drv_write(gpio_id_SSRB, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRB, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRB, 0);

    /* OUTPUT port gpio_id_WDG_CLEAR, gpio_ps GPIO port 0, clear/set/clear test */
    gpio_drv_write(gpio_id_WDG_CLEAR, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_WDG_CLEAR, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_WDG_CLEAR, 0);

    /* OUTPUT port gpio_id_WL_EN, gpio_ps GPIO port 41, clear/set/clear test */
    gpio_drv_write(gpio_id_WL_EN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_WL_EN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_WL_EN, 0);

    /* INPUT port gpio_id_WL_IRQ, gpio_ps GPIO port 44, read test */
    printf("gpio_id_WL_IRQ value is %ld\n", gpio_drv_read(gpio_id_WL_IRQ));
}


BTS_WEAK void gpio_isr_handler_AL_INTRDY(void *param) {}
BTS_WEAK void gpio_isr_handler_BT_EN(void *param) {}
BTS_WEAK void gpio_isr_handler_CAM_PWDN(void *param) {}
BTS_WEAK void gpio_isr_handler_CAM_PWR_EN(void *param) {}
BTS_WEAK void gpio_isr_handler_CAM_STROBE(void *param) {}
BTS_WEAK void gpio_isr_handler_CAM_nRESET(void *param) {}
BTS_WEAK void gpio_isr_handler_FE_SHDN(void *param) {}
BTS_WEAK void gpio_isr_handler_FE_TX_EN(void *param) {}
BTS_WEAK void gpio_isr_handler_GETH_LED0(void *param) {}
BTS_WEAK void gpio_isr_handler_GETH_LED1(void *param) {}
BTS_WEAK void gpio_isr_handler_GETH_nRESET(void *param) {}
BTS_WEAK void gpio_isr_handler_GPS_RESETN(void *param) {}
BTS_WEAK void gpio_isr_handler_GPS_TIMEPULSE(void *param) {}
BTS_WEAK void gpio_isr_handler_IOMUXSEL0(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDB(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDG(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDR(void *param) {}
BTS_WEAK void gpio_isr_handler_LORA_RESETN(void *param) {}
BTS_WEAK void gpio_isr_handler_MMC_nRESET(void *param) {}
BTS_WEAK void gpio_isr_handler_MT_INT(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG16_P135(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG17_P136(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG18_P137(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG19_P138(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG20_P139(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG21_P140(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG22_P141(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG23_P142(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG24_P147(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG25_P148(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG26_P149(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG27_P150(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG28_P151(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG29_P152(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG30_P153(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG31_P154(void *param) {}
BTS_WEAK void gpio_isr_handler_PS_DEBUG0(void *param) {}
BTS_WEAK void gpio_isr_handler_PS_DEBUG1(void *param) {}
BTS_WEAK void gpio_isr_handler_PS_DEBUG2(void *param) {}
BTS_WEAK void gpio_isr_handler_RS485_DE(void *param) {}
BTS_WEAK void gpio_isr_handler_RS485_nRE(void *param) {}
BTS_WEAK void gpio_isr_handler_SSRA(void *param) {}
BTS_WEAK void gpio_isr_handler_SSRB(void *param) {}
BTS_WEAK void gpio_isr_handler_WDG_CLEAR(void *param) {}
BTS_WEAK void gpio_isr_handler_WL_EN(void *param) {}
BTS_WEAK void gpio_isr_handler_WL_IRQ(void *param) {}

#endif // SYS_SYSTEM_VERSION >= SYS_RADAR_VERSION_BEV31
// gpio_drv_info_ir24s.yaml
#if(SYS_SYSTEM_VERSION >= SYS_RADAR_VERSION_BEV23) && (SYS_SYSTEM_VERSION <= SYS_RADAR_VERSION_BEV25)


gpio_axi_object_t gpio0_axi; //XPAR_GPIO_0_DEVICE_ID
gpio_axi_object_t gpio1_axi; //XPAR_GPIO_1_DEVICE_ID
gpio_axi_object_t gpio2_axi; //XPAR_GPIO_2_DEVICE_ID
gpio_ps_object_t gpio_ps;    //XPAR_XGPIOPS_0_DEVICE_ID


BTS_WEAK void gpio_isr_handler_FE_GPIO11(void *param);
BTS_WEAK void gpio_isr_handler_FE_GPIO12(void *param);
BTS_WEAK void gpio_isr_handler_FE_GPIO13(void *param);
BTS_WEAK void gpio_isr_handler_FE_GPIO14(void *param);
BTS_WEAK void gpio_isr_handler_FE_SHDN(void *param);
BTS_WEAK void gpio_isr_handler_FE_TX_EN(void *param);
BTS_WEAK void gpio_isr_handler_GETH_LED0(void *param);
BTS_WEAK void gpio_isr_handler_GETH_LED1(void *param);
BTS_WEAK void gpio_isr_handler_GETH_nRESET(void *param);
BTS_WEAK void gpio_isr_handler_GPS_RESETN(void *param);
BTS_WEAK void gpio_isr_handler_GPS_TIMEPULSE(void *param);
BTS_WEAK void gpio_isr_handler_IOMUXSEL0(void *param);
BTS_WEAK void gpio_isr_handler_LEDB(void *param);
BTS_WEAK void gpio_isr_handler_LEDG(void *param);
BTS_WEAK void gpio_isr_handler_LEDR(void *param);
BTS_WEAK void gpio_isr_handler_LORA_RESETN(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG16(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG17(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG18(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG19(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG20(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG21(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG22(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG23(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG24(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG25(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG26(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG27(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG28(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG29(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG30(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG31(void *param);
BTS_WEAK void gpio_isr_handler_PS_DEBUG0(void *param);
BTS_WEAK void gpio_isr_handler_PS_DEBUG1(void *param);
BTS_WEAK void gpio_isr_handler_PS_DEBUG2(void *param);
BTS_WEAK void gpio_isr_handler_RS485_DE(void *param);
BTS_WEAK void gpio_isr_handler_RS485_nRE(void *param);
BTS_WEAK void gpio_isr_handler_SCANRATE_10FPS_EN(void *param);
BTS_WEAK void gpio_isr_handler_SCANRATE_15FPS_EN(void *param);
BTS_WEAK void gpio_isr_handler_SCANRATE_20FPS_EN(void *param);
BTS_WEAK void gpio_isr_handler_SCANRATE_25FPS_EN(void *param);
BTS_WEAK void gpio_isr_handler_SCANRATE_30FPS_EN(void *param);
BTS_WEAK void gpio_isr_handler_SCANRATE_TIMER_EN(void *param);
BTS_WEAK void gpio_isr_handler_SSRA(void *param);
BTS_WEAK void gpio_isr_handler_SSRB(void *param);
BTS_WEAK void gpio_isr_handler_SSRC(void *param);
BTS_WEAK void gpio_isr_handler_SSRD(void *param);
BTS_WEAK void gpio_isr_handler_WDG_CLEAR(void *param);


gpio_info_t gpio_info_table[] =
    {
        // id               name,           axi or ps,          direction,          enable,   pinnum, defaultval, inten, inttype, isrhandler
        {gpio_id_FE_GPIO11, "FE_GPIO11", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 11, 0, gpio_inttype_none, gpio_isr_handler_FE_GPIO11},
        {gpio_id_FE_GPIO12, "FE_GPIO12", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 12, 0, gpio_inttype_none, gpio_isr_handler_FE_GPIO12},
        {gpio_id_FE_GPIO13, "FE_GPIO13", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 13, 0, gpio_inttype_none, gpio_isr_handler_FE_GPIO13},
        {gpio_id_FE_GPIO14, "FE_GPIO14", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 14, 0, gpio_inttype_none, gpio_isr_handler_FE_GPIO14},
        {gpio_id_FE_SHDN, "FE_SHDN", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 0, 0, gpio_inttype_none, gpio_isr_handler_FE_SHDN},
        {gpio_id_FE_TX_EN, "FE_TX_EN", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 9, 1, gpio_inttype_none, gpio_isr_handler_FE_TX_EN},
        {gpio_id_GETH_LED0, "GETH_LED0", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_in, gpio_enable, 50, 0, gpio_inttype_none, gpio_isr_handler_GETH_LED0},
        {gpio_id_GETH_LED1, "GETH_LED1", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_in, gpio_enable, 51, 0, gpio_inttype_none, gpio_isr_handler_GETH_LED1},
        {gpio_id_GETH_nRESET, "GETH_nRESET", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 45, 1, gpio_inttype_none, gpio_isr_handler_GETH_nRESET},
        {gpio_id_GPS_RESETN, "GPS_RESETN", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 8, 1, gpio_inttype_none, gpio_isr_handler_GPS_RESETN},
        {gpio_id_GPS_TIMEPULSE, "GPS_TIMEPULSE", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 7, 0, gpio_inttype_none, gpio_isr_handler_GPS_TIMEPULSE},
        {gpio_id_IOMUXSEL0, "IOMUXSEL0", (void *)&gpio1_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 0, 0, gpio_inttype_none, gpio_isr_handler_IOMUXSEL0},
        {gpio_id_LEDB, "LEDB", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 5, 0, gpio_inttype_none, gpio_isr_handler_LEDB},
        {gpio_id_LEDG, "LEDG", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 4, 0, gpio_inttype_none, gpio_isr_handler_LEDG},
        {gpio_id_LEDR, "LEDR", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 3, 0, gpio_inttype_none, gpio_isr_handler_LEDR},
        {gpio_id_LORA_RESETN, "LORA_RESETN", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 10, 1, gpio_inttype_none, gpio_isr_handler_LORA_RESETN},
        {gpio_id_PL_DEBUG16, "PL_DEBUG16", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 16, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG16},
        {gpio_id_PL_DEBUG17, "PL_DEBUG17", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 17, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG17},
        {gpio_id_PL_DEBUG18, "PL_DEBUG18", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 18, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG18},
        {gpio_id_PL_DEBUG19, "PL_DEBUG19", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 19, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG19},
        {gpio_id_PL_DEBUG20, "PL_DEBUG20", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 20, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG20},
        {gpio_id_PL_DEBUG21, "PL_DEBUG21", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 21, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG21},
        {gpio_id_PL_DEBUG22, "PL_DEBUG22", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 22, 1, gpio_inttype_none, gpio_isr_handler_PL_DEBUG22},
        {gpio_id_PL_DEBUG23, "PL_DEBUG23", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 23, 1, gpio_inttype_none, gpio_isr_handler_PL_DEBUG23},
        {gpio_id_PL_DEBUG24, "PL_DEBUG24", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 24, 1, gpio_inttype_none, gpio_isr_handler_PL_DEBUG24},
        {gpio_id_PL_DEBUG25, "PL_DEBUG25", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 25, 1, gpio_inttype_none, gpio_isr_handler_PL_DEBUG25},
        {gpio_id_PL_DEBUG26, "PL_DEBUG26", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 26, 1, gpio_inttype_none, gpio_isr_handler_PL_DEBUG26},
        {gpio_id_PL_DEBUG27, "PL_DEBUG27", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 27, 1, gpio_inttype_none, gpio_isr_handler_PL_DEBUG27},
        {gpio_id_PL_DEBUG28, "PL_DEBUG28", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 28, 1, gpio_inttype_none, gpio_isr_handler_PL_DEBUG28},
        {gpio_id_PL_DEBUG29, "PL_DEBUG29", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 29, 1, gpio_inttype_none, gpio_isr_handler_PL_DEBUG29},
        {gpio_id_PL_DEBUG30, "PL_DEBUG30", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 30, 1, gpio_inttype_none, gpio_isr_handler_PL_DEBUG30},
        {gpio_id_PL_DEBUG31, "PL_DEBUG31", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 31, 1, gpio_inttype_none, gpio_isr_handler_PL_DEBUG31},
        {gpio_id_PS_DEBUG0, "PS_DEBUG0", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 7, 0, gpio_inttype_none, gpio_isr_handler_PS_DEBUG0},
        {gpio_id_PS_DEBUG1, "PS_DEBUG1", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 8, 0, gpio_inttype_none, gpio_isr_handler_PS_DEBUG1},
        {gpio_id_PS_DEBUG2, "PS_DEBUG2", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 9, 0, gpio_inttype_none, gpio_isr_handler_PS_DEBUG2},
        {gpio_id_RS485_DE, "RS485_DE", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 2, 1, gpio_inttype_none, gpio_isr_handler_RS485_DE},
        {gpio_id_RS485_nRE, "RS485_nRE", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 1, 1, gpio_inttype_none, gpio_isr_handler_RS485_nRE},
        {gpio_id_SCANRATE_10FPS_EN, "SCANRATE_10FPS_EN", (void *)&gpio2_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 4, 0, gpio_inttype_none, gpio_isr_handler_SCANRATE_10FPS_EN},
        {gpio_id_SCANRATE_15FPS_EN, "SCANRATE_15FPS_EN", (void *)&gpio2_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 3, 0, gpio_inttype_none, gpio_isr_handler_SCANRATE_15FPS_EN},
        {gpio_id_SCANRATE_20FPS_EN, "SCANRATE_20FPS_EN", (void *)&gpio2_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 2, 0, gpio_inttype_none, gpio_isr_handler_SCANRATE_20FPS_EN},
        {gpio_id_SCANRATE_25FPS_EN, "SCANRATE_25FPS_EN", (void *)&gpio2_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 1, 0, gpio_inttype_none, gpio_isr_handler_SCANRATE_25FPS_EN},
        {gpio_id_SCANRATE_30FPS_EN, "SCANRATE_30FPS_EN", (void *)&gpio2_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 0, 0, gpio_inttype_none, gpio_isr_handler_SCANRATE_30FPS_EN},
        {gpio_id_SCANRATE_TIMER_EN, "SCANRATE_TIMER_EN", (void *)&gpio2_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 5, 0, gpio_inttype_none, gpio_isr_handler_SCANRATE_TIMER_EN},
        {gpio_id_SSRA, "SSRA", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 6, 1, gpio_inttype_none, gpio_isr_handler_SSRA},
        {gpio_id_SSRB, "SSRB", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 15, 1, gpio_inttype_none, gpio_isr_handler_SSRB},
        {gpio_id_SSRC, "SSRC", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 22, 1, gpio_inttype_none, gpio_isr_handler_SSRC},
        {gpio_id_SSRD, "SSRD", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 23, 1, gpio_inttype_none, gpio_isr_handler_SSRD},
        {gpio_id_WDG_CLEAR, "WDG_CLEAR", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 0, 0, gpio_inttype_none, gpio_isr_handler_WDG_CLEAR},
};

/* declare static variables */


/* static function prototypes */


/* functions */
void gpio_drv_info_unittest(void)
{
    /* INPUT port gpio_id_FE_GPIO11, gpio0_axi GPIO port 11, read test */
    printf("gpio_id_FE_GPIO11 value is %ld\n", gpio_drv_read(gpio_id_FE_GPIO11));

    /* INPUT port gpio_id_FE_GPIO12, gpio0_axi GPIO port 12, read test */
    printf("gpio_id_FE_GPIO12 value is %ld\n", gpio_drv_read(gpio_id_FE_GPIO12));

    /* INPUT port gpio_id_FE_GPIO13, gpio0_axi GPIO port 13, read test */
    printf("gpio_id_FE_GPIO13 value is %ld\n", gpio_drv_read(gpio_id_FE_GPIO13));

    /* INPUT port gpio_id_FE_GPIO14, gpio0_axi GPIO port 14, read test */
    printf("gpio_id_FE_GPIO14 value is %ld\n", gpio_drv_read(gpio_id_FE_GPIO14));

    /* OUTPUT port gpio_id_FE_SHDN, gpio0_axi GPIO port 0, clear/set/clear test */
    gpio_drv_write(gpio_id_FE_SHDN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_FE_SHDN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_FE_SHDN, 0);

    /* OUTPUT port gpio_id_FE_TX_EN, gpio0_axi GPIO port 9, clear/set/clear test */
    gpio_drv_write(gpio_id_FE_TX_EN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_FE_TX_EN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_FE_TX_EN, 0);

    /* INPUT port gpio_id_GETH_LED0, gpio_ps GPIO port 50, read test */
    printf("gpio_id_GETH_LED0 value is %ld\n", gpio_drv_read(gpio_id_GETH_LED0));

    /* INPUT port gpio_id_GETH_LED1, gpio_ps GPIO port 51, read test */
    printf("gpio_id_GETH_LED1 value is %ld\n", gpio_drv_read(gpio_id_GETH_LED1));

    /* OUTPUT port gpio_id_GETH_nRESET, gpio_ps GPIO port 45, clear/set/clear test */
    gpio_drv_write(gpio_id_GETH_nRESET, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_GETH_nRESET, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_GETH_nRESET, 0);

    /* OUTPUT port gpio_id_GPS_RESETN, gpio0_axi GPIO port 8, clear/set/clear test */
    gpio_drv_write(gpio_id_GPS_RESETN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_GPS_RESETN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_GPS_RESETN, 0);

    /* INPUT port gpio_id_GPS_TIMEPULSE, gpio0_axi GPIO port 7, read test */
    printf("gpio_id_GPS_TIMEPULSE value is %ld\n", gpio_drv_read(gpio_id_GPS_TIMEPULSE));

    /* OUTPUT port gpio_id_IOMUXSEL0, gpio1_axi GPIO port 0, clear/set/clear test */
    gpio_drv_write(gpio_id_IOMUXSEL0, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_IOMUXSEL0, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_IOMUXSEL0, 0);

    /* OUTPUT port gpio_id_LEDB, gpio0_axi GPIO port 5, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDB, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDB, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDB, 0);

    /* OUTPUT port gpio_id_LEDG, gpio0_axi GPIO port 4, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDG, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDG, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDG, 0);

    /* OUTPUT port gpio_id_LEDR, gpio0_axi GPIO port 3, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDR, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDR, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDR, 0);

    /* OUTPUT port gpio_id_LORA_RESETN, gpio0_axi GPIO port 10, clear/set/clear test */
    gpio_drv_write(gpio_id_LORA_RESETN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LORA_RESETN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LORA_RESETN, 0);

    /* INPUT port gpio_id_PL_DEBUG16, gpio0_axi GPIO port 16, read test */
    printf("gpio_id_PL_DEBUG16 value is %ld\n", gpio_drv_read(gpio_id_PL_DEBUG16));

    /* INPUT port gpio_id_PL_DEBUG17, gpio0_axi GPIO port 17, read test */
    printf("gpio_id_PL_DEBUG17 value is %ld\n", gpio_drv_read(gpio_id_PL_DEBUG17));

    /* INPUT port gpio_id_PL_DEBUG18, gpio0_axi GPIO port 18, read test */
    printf("gpio_id_PL_DEBUG18 value is %ld\n", gpio_drv_read(gpio_id_PL_DEBUG18));

    /* INPUT port gpio_id_PL_DEBUG19, gpio0_axi GPIO port 19, read test */
    printf("gpio_id_PL_DEBUG19 value is %ld\n", gpio_drv_read(gpio_id_PL_DEBUG19));

    /* INPUT port gpio_id_PL_DEBUG20, gpio0_axi GPIO port 20, read test */
    printf("gpio_id_PL_DEBUG20 value is %ld\n", gpio_drv_read(gpio_id_PL_DEBUG20));

    /* INPUT port gpio_id_PL_DEBUG21, gpio0_axi GPIO port 21, read test */
    printf("gpio_id_PL_DEBUG21 value is %ld\n", gpio_drv_read(gpio_id_PL_DEBUG21));

    /* INPUT port gpio_id_PL_DEBUG22, gpio0_axi GPIO port 22, read test */
    printf("gpio_id_PL_DEBUG22 value is %ld\n", gpio_drv_read(gpio_id_PL_DEBUG22));

    /* INPUT port gpio_id_PL_DEBUG23, gpio0_axi GPIO port 23, read test */
    printf("gpio_id_PL_DEBUG23 value is %ld\n", gpio_drv_read(gpio_id_PL_DEBUG23));

    /* INPUT port gpio_id_PL_DEBUG24, gpio0_axi GPIO port 24, read test */
    printf("gpio_id_PL_DEBUG24 value is %ld\n", gpio_drv_read(gpio_id_PL_DEBUG24));

    /* INPUT port gpio_id_PL_DEBUG25, gpio0_axi GPIO port 25, read test */
    printf("gpio_id_PL_DEBUG25 value is %ld\n", gpio_drv_read(gpio_id_PL_DEBUG25));

    /* INPUT port gpio_id_PL_DEBUG26, gpio0_axi GPIO port 26, read test */
    printf("gpio_id_PL_DEBUG26 value is %ld\n", gpio_drv_read(gpio_id_PL_DEBUG26));

    /* INPUT port gpio_id_PL_DEBUG27, gpio0_axi GPIO port 27, read test */
    printf("gpio_id_PL_DEBUG27 value is %ld\n", gpio_drv_read(gpio_id_PL_DEBUG27));

    /* INPUT port gpio_id_PL_DEBUG28, gpio0_axi GPIO port 28, read test */
    printf("gpio_id_PL_DEBUG28 value is %ld\n", gpio_drv_read(gpio_id_PL_DEBUG28));

    /* INPUT port gpio_id_PL_DEBUG29, gpio0_axi GPIO port 29, read test */
    printf("gpio_id_PL_DEBUG29 value is %ld\n", gpio_drv_read(gpio_id_PL_DEBUG29));

    /* INPUT port gpio_id_PL_DEBUG30, gpio0_axi GPIO port 30, read test */
    printf("gpio_id_PL_DEBUG30 value is %ld\n", gpio_drv_read(gpio_id_PL_DEBUG30));

    /* INPUT port gpio_id_PL_DEBUG31, gpio0_axi GPIO port 31, read test */
    printf("gpio_id_PL_DEBUG31 value is %ld\n", gpio_drv_read(gpio_id_PL_DEBUG31));

    /* OUTPUT port gpio_id_PS_DEBUG0, gpio_ps GPIO port 7, clear/set/clear test */
    gpio_drv_write(gpio_id_PS_DEBUG0, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PS_DEBUG0, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PS_DEBUG0, 0);

    /* OUTPUT port gpio_id_PS_DEBUG1, gpio_ps GPIO port 8, clear/set/clear test */
    gpio_drv_write(gpio_id_PS_DEBUG1, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PS_DEBUG1, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PS_DEBUG1, 0);

    /* OUTPUT port gpio_id_PS_DEBUG2, gpio_ps GPIO port 9, clear/set/clear test */
    gpio_drv_write(gpio_id_PS_DEBUG2, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PS_DEBUG2, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PS_DEBUG2, 0);

    /* OUTPUT port gpio_id_RS485_DE, gpio0_axi GPIO port 2, clear/set/clear test */
    gpio_drv_write(gpio_id_RS485_DE, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_RS485_DE, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_RS485_DE, 0);

    /* OUTPUT port gpio_id_RS485_nRE, gpio0_axi GPIO port 1, clear/set/clear test */
    gpio_drv_write(gpio_id_RS485_nRE, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_RS485_nRE, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_RS485_nRE, 0);

    /* OUTPUT port gpio_id_SCANRATE_10FPS_EN, gpio2_axi GPIO port 4, clear/set/clear test */
    gpio_drv_write(gpio_id_SCANRATE_10FPS_EN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_SCANRATE_10FPS_EN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_SCANRATE_10FPS_EN, 0);

    /* OUTPUT port gpio_id_SCANRATE_15FPS_EN, gpio2_axi GPIO port 3, clear/set/clear test */
    gpio_drv_write(gpio_id_SCANRATE_15FPS_EN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_SCANRATE_15FPS_EN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_SCANRATE_15FPS_EN, 0);

    /* OUTPUT port gpio_id_SCANRATE_20FPS_EN, gpio2_axi GPIO port 2, clear/set/clear test */
    gpio_drv_write(gpio_id_SCANRATE_20FPS_EN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_SCANRATE_20FPS_EN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_SCANRATE_20FPS_EN, 0);

    /* OUTPUT port gpio_id_SCANRATE_25FPS_EN, gpio2_axi GPIO port 1, clear/set/clear test */
    gpio_drv_write(gpio_id_SCANRATE_25FPS_EN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_SCANRATE_25FPS_EN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_SCANRATE_25FPS_EN, 0);

    /* OUTPUT port gpio_id_SCANRATE_30FPS_EN, gpio2_axi GPIO port 0, clear/set/clear test */
    gpio_drv_write(gpio_id_SCANRATE_30FPS_EN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_SCANRATE_30FPS_EN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_SCANRATE_30FPS_EN, 0);

    /* OUTPUT port gpio_id_SCANRATE_TIMER_EN, gpio2_axi GPIO port 5, clear/set/clear test */
    gpio_drv_write(gpio_id_SCANRATE_TIMER_EN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_SCANRATE_TIMER_EN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_SCANRATE_TIMER_EN, 0);

    /* OUTPUT port gpio_id_SSRA, gpio0_axi GPIO port 6, clear/set/clear test */
    gpio_drv_write(gpio_id_SSRA, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRA, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRA, 0);

    /* OUTPUT port gpio_id_SSRB, gpio0_axi GPIO port 15, clear/set/clear test */
    gpio_drv_write(gpio_id_SSRB, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRB, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRB, 0);

    /* OUTPUT port gpio_id_SSRC, gpio0_axi GPIO port 22, clear/set/clear test */
    gpio_drv_write(gpio_id_SSRC, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRC, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRC, 0);

    /* OUTPUT port gpio_id_SSRD, gpio0_axi GPIO port 23, clear/set/clear test */
    gpio_drv_write(gpio_id_SSRD, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRD, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRD, 0);

    /* OUTPUT port gpio_id_WDG_CLEAR, gpio_ps GPIO port 0, clear/set/clear test */
    gpio_drv_write(gpio_id_WDG_CLEAR, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_WDG_CLEAR, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_WDG_CLEAR, 0);
}


BTS_WEAK void gpio_isr_handler_FE_GPIO11(void *param) {}
BTS_WEAK void gpio_isr_handler_FE_GPIO12(void *param) {}
BTS_WEAK void gpio_isr_handler_FE_GPIO13(void *param) {}
BTS_WEAK void gpio_isr_handler_FE_GPIO14(void *param) {}
BTS_WEAK void gpio_isr_handler_FE_SHDN(void *param) {}
BTS_WEAK void gpio_isr_handler_FE_TX_EN(void *param) {}
BTS_WEAK void gpio_isr_handler_GETH_LED0(void *param) {}
BTS_WEAK void gpio_isr_handler_GETH_LED1(void *param) {}
BTS_WEAK void gpio_isr_handler_GETH_nRESET(void *param) {}
BTS_WEAK void gpio_isr_handler_GPS_RESETN(void *param) {}
BTS_WEAK void gpio_isr_handler_GPS_TIMEPULSE(void *param) {}
BTS_WEAK void gpio_isr_handler_IOMUXSEL0(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDB(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDG(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDR(void *param) {}
BTS_WEAK void gpio_isr_handler_LORA_RESETN(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG16(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG17(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG18(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG19(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG20(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG21(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG22(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG23(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG24(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG25(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG26(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG27(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG28(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG29(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG30(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG31(void *param) {}
BTS_WEAK void gpio_isr_handler_PS_DEBUG0(void *param) {}
BTS_WEAK void gpio_isr_handler_PS_DEBUG1(void *param) {}
BTS_WEAK void gpio_isr_handler_PS_DEBUG2(void *param) {}
BTS_WEAK void gpio_isr_handler_RS485_DE(void *param) {}
BTS_WEAK void gpio_isr_handler_RS485_nRE(void *param) {}
BTS_WEAK void gpio_isr_handler_SCANRATE_10FPS_EN(void *param) {}
BTS_WEAK void gpio_isr_handler_SCANRATE_15FPS_EN(void *param) {}
BTS_WEAK void gpio_isr_handler_SCANRATE_20FPS_EN(void *param) {}
BTS_WEAK void gpio_isr_handler_SCANRATE_25FPS_EN(void *param) {}
BTS_WEAK void gpio_isr_handler_SCANRATE_30FPS_EN(void *param) {}
BTS_WEAK void gpio_isr_handler_SCANRATE_TIMER_EN(void *param) {}
BTS_WEAK void gpio_isr_handler_SSRA(void *param) {}
BTS_WEAK void gpio_isr_handler_SSRB(void *param) {}
BTS_WEAK void gpio_isr_handler_SSRC(void *param) {}
BTS_WEAK void gpio_isr_handler_SSRD(void *param) {}
BTS_WEAK void gpio_isr_handler_WDG_CLEAR(void *param) {}

#endif // (SYS_SYSTEM_VERSION >= SYS_RADAR_VERSION_BEV23) && (SYS_SYSTEM_VERSION <= SYS_RADAR_VERSION_BEV25)
// gpio_drv_info_ir24x.yaml
#if SYS_SYSTEM_VERSION == SYS_RADAR_VERSION_BEVX10


gpio_axi_object_t gpio0_axi; //XPAR_GPIO_0_DEVICE_ID
gpio_ps_object_t gpio_ps;    //XPAR_XGPIOPS_0_DEVICE_ID


BTS_WEAK void gpio_isr_handler_BE_VIO02(void *param);
BTS_WEAK void gpio_isr_handler_BE_VIO03(void *param);
BTS_WEAK void gpio_isr_handler_BE_VIO07(void *param);
BTS_WEAK void gpio_isr_handler_BE_VIO16(void *param);
BTS_WEAK void gpio_isr_handler_BE_VIO17(void *param);
BTS_WEAK void gpio_isr_handler_BE_VIO18(void *param);
BTS_WEAK void gpio_isr_handler_BE_VIO19(void *param);
BTS_WEAK void gpio_isr_handler_BE_VIO22(void *param);
BTS_WEAK void gpio_isr_handler_BE_VIO23(void *param);
BTS_WEAK void gpio_isr_handler_FE_PWR_EN(void *param);
BTS_WEAK void gpio_isr_handler_FE_TX_EN(void *param);
BTS_WEAK void gpio_isr_handler_GPS_RESETN(void *param);
BTS_WEAK void gpio_isr_handler_LEDB(void *param);
BTS_WEAK void gpio_isr_handler_LEDG(void *param);
BTS_WEAK void gpio_isr_handler_LEDR(void *param);
BTS_WEAK void gpio_isr_handler_LORA_RESETN(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG0(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG1(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG2(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG3(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG4(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG5(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG6(void *param);
BTS_WEAK void gpio_isr_handler_PL_DEBUG7(void *param);
BTS_WEAK void gpio_isr_handler_PS_DEBUG0(void *param);
BTS_WEAK void gpio_isr_handler_RS485_DE(void *param);
BTS_WEAK void gpio_isr_handler_RS485_nRE(void *param);
BTS_WEAK void gpio_isr_handler_SSRA(void *param);
BTS_WEAK void gpio_isr_handler_SSRB(void *param);
BTS_WEAK void gpio_isr_handler_SSRC(void *param);
BTS_WEAK void gpio_isr_handler_SSRD(void *param);
BTS_WEAK void gpio_isr_handler_WDG_CLEAR(void *param);
BTS_WEAK void gpio_isr_handler_WIFI_HIBN(void *param);
BTS_WEAK void gpio_isr_handler_WIFI_RESETN(void *param);


gpio_info_t gpio_info_table[] =
    {
        // id               name,           axi or ps,          direction,          enable,   pinnum, defaultval, inten, inttype, isrhandler
        {gpio_id_BE_VIO02, "BE_VIO02", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 2, 0, gpio_inttype_none, gpio_isr_handler_BE_VIO02},
        {gpio_id_BE_VIO03, "BE_VIO03", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 3, 0, gpio_inttype_none, gpio_isr_handler_BE_VIO03},
        {gpio_id_BE_VIO07, "BE_VIO07", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 7, 0, gpio_inttype_none, gpio_isr_handler_BE_VIO07},
        {gpio_id_BE_VIO16, "BE_VIO16", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 16, 0, gpio_inttype_none, gpio_isr_handler_BE_VIO16},
        {gpio_id_BE_VIO17, "BE_VIO17", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 17, 0, gpio_inttype_none, gpio_isr_handler_BE_VIO17},
        {gpio_id_BE_VIO18, "BE_VIO18", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 18, 0, gpio_inttype_none, gpio_isr_handler_BE_VIO18},
        {gpio_id_BE_VIO19, "BE_VIO19", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 19, 0, gpio_inttype_none, gpio_isr_handler_BE_VIO19},
        {gpio_id_BE_VIO22, "BE_VIO22", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 22, 0, gpio_inttype_none, gpio_isr_handler_BE_VIO22},
        {gpio_id_BE_VIO23, "BE_VIO23", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 23, 0, gpio_inttype_none, gpio_isr_handler_BE_VIO23},
        {gpio_id_FE_PWR_EN, "FE_PWR_EN", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 0, 1, gpio_inttype_none, gpio_isr_handler_FE_PWR_EN},
        {gpio_id_FE_TX_EN, "FE_TX_EN", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 1, 1, gpio_inttype_none, gpio_isr_handler_FE_TX_EN},
        {gpio_id_GPS_RESETN, "GPS_RESETN", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 12, 1, gpio_inttype_none, gpio_isr_handler_GPS_RESETN},
        {gpio_id_LEDB, "LEDB", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 6, 0, gpio_inttype_none, gpio_isr_handler_LEDB},
        {gpio_id_LEDG, "LEDG", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 5, 0, gpio_inttype_none, gpio_isr_handler_LEDG},
        {gpio_id_LEDR, "LEDR", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 4, 0, gpio_inttype_none, gpio_isr_handler_LEDR},
        {gpio_id_LORA_RESETN, "LORA_RESETN", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 15, 1, gpio_inttype_none, gpio_isr_handler_LORA_RESETN},
        {gpio_id_PL_DEBUG0, "PL_DEBUG0", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 24, 1, gpio_inttype_none, gpio_isr_handler_PL_DEBUG0},
        {gpio_id_PL_DEBUG1, "PL_DEBUG1", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 25, 1, gpio_inttype_none, gpio_isr_handler_PL_DEBUG1},
        {gpio_id_PL_DEBUG2, "PL_DEBUG2", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 26, 1, gpio_inttype_none, gpio_isr_handler_PL_DEBUG2},
        {gpio_id_PL_DEBUG3, "PL_DEBUG3", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 27, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG3},
        {gpio_id_PL_DEBUG4, "PL_DEBUG4", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 28, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG4},
        {gpio_id_PL_DEBUG5, "PL_DEBUG5", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 29, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG5},
        {gpio_id_PL_DEBUG6, "PL_DEBUG6", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 30, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG6},
        {gpio_id_PL_DEBUG7, "PL_DEBUG7", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 31, 0, gpio_inttype_none, gpio_isr_handler_PL_DEBUG7},
        {gpio_id_PS_DEBUG0, "PS_DEBUG0", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 7, 0, gpio_inttype_none, gpio_isr_handler_PS_DEBUG0},
        {gpio_id_RS485_DE, "RS485_DE", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 21, 0, gpio_inttype_none, gpio_isr_handler_RS485_DE},
        {gpio_id_RS485_nRE, "RS485_nRE", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 20, 1, gpio_inttype_none, gpio_isr_handler_RS485_nRE},
        {gpio_id_SSRA, "SSRA", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 8, 0, gpio_inttype_none, gpio_isr_handler_SSRA},
        {gpio_id_SSRB, "SSRB", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 9, 0, gpio_inttype_none, gpio_isr_handler_SSRB},
        {gpio_id_SSRC, "SSRC", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 10, 0, gpio_inttype_none, gpio_isr_handler_SSRC},
        {gpio_id_SSRD, "SSRD", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 11, 0, gpio_inttype_none, gpio_isr_handler_SSRD},
        {gpio_id_WDG_CLEAR, "WDG_CLEAR", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 0, 0, gpio_inttype_none, gpio_isr_handler_WDG_CLEAR},
        {gpio_id_WIFI_HIBN, "WIFI_HIBN", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 14, 1, gpio_inttype_none, gpio_isr_handler_WIFI_HIBN},
        {gpio_id_WIFI_RESETN, "WIFI_RESETN", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 13, 1, gpio_inttype_none, gpio_isr_handler_WIFI_RESETN},
};

/* declare static variables */


/* static function prototypes */


/* functions */
void gpio_drv_info_unittest(void)
{
    /* INPUT port gpio_id_BE_VIO02, gpio0_axi GPIO port 2, read test */
    printf("gpio_id_BE_VIO02 value is %ld\n", gpio_drv_read(gpio_id_BE_VIO02));

    /* INPUT port gpio_id_BE_VIO03, gpio0_axi GPIO port 3, read test */
    printf("gpio_id_BE_VIO03 value is %ld\n", gpio_drv_read(gpio_id_BE_VIO03));

    /* INPUT port gpio_id_BE_VIO07, gpio0_axi GPIO port 7, read test */
    printf("gpio_id_BE_VIO07 value is %ld\n", gpio_drv_read(gpio_id_BE_VIO07));

    /* INPUT port gpio_id_BE_VIO16, gpio0_axi GPIO port 16, read test */
    printf("gpio_id_BE_VIO16 value is %ld\n", gpio_drv_read(gpio_id_BE_VIO16));

    /* INPUT port gpio_id_BE_VIO17, gpio0_axi GPIO port 17, read test */
    printf("gpio_id_BE_VIO17 value is %ld\n", gpio_drv_read(gpio_id_BE_VIO17));

    /* INPUT port gpio_id_BE_VIO18, gpio0_axi GPIO port 18, read test */
    printf("gpio_id_BE_VIO18 value is %ld\n", gpio_drv_read(gpio_id_BE_VIO18));

    /* INPUT port gpio_id_BE_VIO19, gpio0_axi GPIO port 19, read test */
    printf("gpio_id_BE_VIO19 value is %ld\n", gpio_drv_read(gpio_id_BE_VIO19));

    /* INPUT port gpio_id_BE_VIO22, gpio0_axi GPIO port 22, read test */
    printf("gpio_id_BE_VIO22 value is %ld\n", gpio_drv_read(gpio_id_BE_VIO22));

    /* INPUT port gpio_id_BE_VIO23, gpio0_axi GPIO port 23, read test */
    printf("gpio_id_BE_VIO23 value is %ld\n", gpio_drv_read(gpio_id_BE_VIO23));

    /* OUTPUT port gpio_id_FE_PWR_EN, gpio0_axi GPIO port 0, clear/set/clear test */
    gpio_drv_write(gpio_id_FE_PWR_EN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_FE_PWR_EN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_FE_PWR_EN, 0);

    /* OUTPUT port gpio_id_FE_TX_EN, gpio0_axi GPIO port 1, clear/set/clear test */
    gpio_drv_write(gpio_id_FE_TX_EN, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_FE_TX_EN, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_FE_TX_EN, 0);

    /* INPUT port gpio_id_GPS_RESETN, gpio0_axi GPIO port 12, read test */
    printf("gpio_id_GPS_RESETN value is %ld\n", gpio_drv_read(gpio_id_GPS_RESETN));

    /* OUTPUT port gpio_id_LEDB, gpio0_axi GPIO port 6, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDB, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDB, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDB, 0);

    /* OUTPUT port gpio_id_LEDG, gpio0_axi GPIO port 5, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDG, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDG, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDG, 0);

    /* OUTPUT port gpio_id_LEDR, gpio0_axi GPIO port 4, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDR, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDR, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDR, 0);

    /* INPUT port gpio_id_LORA_RESETN, gpio0_axi GPIO port 15, read test */
    printf("gpio_id_LORA_RESETN value is %ld\n", gpio_drv_read(gpio_id_LORA_RESETN));

    /* OUTPUT port gpio_id_PL_DEBUG0, gpio0_axi GPIO port 24, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG0, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG0, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG0, 0);

    /* OUTPUT port gpio_id_PL_DEBUG1, gpio0_axi GPIO port 25, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG1, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG1, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG1, 0);

    /* OUTPUT port gpio_id_PL_DEBUG2, gpio0_axi GPIO port 26, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG2, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG2, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG2, 0);

    /* OUTPUT port gpio_id_PL_DEBUG3, gpio0_axi GPIO port 27, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG3, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG3, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG3, 0);

    /* OUTPUT port gpio_id_PL_DEBUG4, gpio0_axi GPIO port 28, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG4, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG4, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG4, 0);

    /* OUTPUT port gpio_id_PL_DEBUG5, gpio0_axi GPIO port 29, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG5, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG5, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG5, 0);

    /* OUTPUT port gpio_id_PL_DEBUG6, gpio0_axi GPIO port 30, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG6, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG6, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG6, 0);

    /* OUTPUT port gpio_id_PL_DEBUG7, gpio0_axi GPIO port 31, clear/set/clear test */
    gpio_drv_write(gpio_id_PL_DEBUG7, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG7, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PL_DEBUG7, 0);

    /* OUTPUT port gpio_id_PS_DEBUG0, gpio_ps GPIO port 7, clear/set/clear test */
    gpio_drv_write(gpio_id_PS_DEBUG0, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_PS_DEBUG0, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_PS_DEBUG0, 0);

    /* OUTPUT port gpio_id_RS485_DE, gpio0_axi GPIO port 21, clear/set/clear test */
    gpio_drv_write(gpio_id_RS485_DE, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_RS485_DE, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_RS485_DE, 0);

    /* OUTPUT port gpio_id_RS485_nRE, gpio0_axi GPIO port 20, clear/set/clear test */
    gpio_drv_write(gpio_id_RS485_nRE, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_RS485_nRE, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_RS485_nRE, 0);

    /* OUTPUT port gpio_id_SSRA, gpio0_axi GPIO port 8, clear/set/clear test */
    gpio_drv_write(gpio_id_SSRA, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRA, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRA, 0);

    /* OUTPUT port gpio_id_SSRB, gpio0_axi GPIO port 9, clear/set/clear test */
    gpio_drv_write(gpio_id_SSRB, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRB, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRB, 0);

    /* OUTPUT port gpio_id_SSRC, gpio0_axi GPIO port 10, clear/set/clear test */
    gpio_drv_write(gpio_id_SSRC, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRC, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRC, 0);

    /* OUTPUT port gpio_id_SSRD, gpio0_axi GPIO port 11, clear/set/clear test */
    gpio_drv_write(gpio_id_SSRD, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRD, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_SSRD, 0);

    /* OUTPUT port gpio_id_WDG_CLEAR, gpio_ps GPIO port 0, clear/set/clear test */
    gpio_drv_write(gpio_id_WDG_CLEAR, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_WDG_CLEAR, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_WDG_CLEAR, 0);

    /* INPUT port gpio_id_WIFI_HIBN, gpio0_axi GPIO port 14, read test */
    printf("gpio_id_WIFI_HIBN value is %ld\n", gpio_drv_read(gpio_id_WIFI_HIBN));

    /* INPUT port gpio_id_WIFI_RESETN, gpio0_axi GPIO port 13, read test */
    printf("gpio_id_WIFI_RESETN value is %ld\n", gpio_drv_read(gpio_id_WIFI_RESETN));
}


BTS_WEAK void gpio_isr_handler_BE_VIO02(void *param) {}
BTS_WEAK void gpio_isr_handler_BE_VIO03(void *param) {}
BTS_WEAK void gpio_isr_handler_BE_VIO07(void *param) {}
BTS_WEAK void gpio_isr_handler_BE_VIO16(void *param) {}
BTS_WEAK void gpio_isr_handler_BE_VIO17(void *param) {}
BTS_WEAK void gpio_isr_handler_BE_VIO18(void *param) {}
BTS_WEAK void gpio_isr_handler_BE_VIO19(void *param) {}
BTS_WEAK void gpio_isr_handler_BE_VIO22(void *param) {}
BTS_WEAK void gpio_isr_handler_BE_VIO23(void *param) {}
BTS_WEAK void gpio_isr_handler_FE_PWR_EN(void *param) {}
BTS_WEAK void gpio_isr_handler_FE_TX_EN(void *param) {}
BTS_WEAK void gpio_isr_handler_GPS_RESETN(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDB(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDG(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDR(void *param) {}
BTS_WEAK void gpio_isr_handler_LORA_RESETN(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG0(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG1(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG2(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG3(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG4(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG5(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG6(void *param) {}
BTS_WEAK void gpio_isr_handler_PL_DEBUG7(void *param) {}
BTS_WEAK void gpio_isr_handler_PS_DEBUG0(void *param) {}
BTS_WEAK void gpio_isr_handler_RS485_DE(void *param) {}
BTS_WEAK void gpio_isr_handler_RS485_nRE(void *param) {}
BTS_WEAK void gpio_isr_handler_SSRA(void *param) {}
BTS_WEAK void gpio_isr_handler_SSRB(void *param) {}
BTS_WEAK void gpio_isr_handler_SSRC(void *param) {}
BTS_WEAK void gpio_isr_handler_SSRD(void *param) {}
BTS_WEAK void gpio_isr_handler_WDG_CLEAR(void *param) {}
BTS_WEAK void gpio_isr_handler_WIFI_HIBN(void *param) {}
BTS_WEAK void gpio_isr_handler_WIFI_RESETN(void *param) {}

#endif // SYS_SYSTEM_VERSION == SYS_RADAR_VERSION_BEVX10
// gpio_drv_info_lelogger.yaml
#if(SYS_SYSTEM_VERSION == SYS_LOGGER_VERSION_V01)


gpio_axi_object_t gpio0_axi; //XPAR_GPIO_0_DEVICE_ID
gpio_axi_object_t gpio1_axi; //XPAR_DEVICEDNA_AXI_GPIO_DNA_CONTROL_DEVICE_ID
gpio_axi_object_t gpio2_axi; //XPAR_DEVICEDNA_AXI_GPIO_DNA_READER_DEVICE_ID
gpio_axi_object_t gpio3_axi; //XPAR_AXI_GPIO_BOARDCONTROL_DEVICE_ID
gpio_ps_object_t gpio_ps;    //XPAR_XGPIOPS_0_DEVICE_ID


BTS_WEAK void gpio_isr_handler_EQ_RX_DE0(void *param);
BTS_WEAK void gpio_isr_handler_EQ_RX_DE1(void *param);
BTS_WEAK void gpio_isr_handler_EQ_RX_DIS(void *param);
BTS_WEAK void gpio_isr_handler_EQ_RX_LOS(void *param);
BTS_WEAK void gpio_isr_handler_EQ_RX_POL(void *param);
BTS_WEAK void gpio_isr_handler_EQ_RX_SWG(void *param);
BTS_WEAK void gpio_isr_handler_EQ_TX_DE0(void *param);
BTS_WEAK void gpio_isr_handler_EQ_TX_DE1(void *param);
BTS_WEAK void gpio_isr_handler_EQ_TX_DIS(void *param);
BTS_WEAK void gpio_isr_handler_EQ_TX_LOS(void *param);
BTS_WEAK void gpio_isr_handler_EQ_TX_POL(void *param);
BTS_WEAK void gpio_isr_handler_EQ_TX_SWG(void *param);
BTS_WEAK void gpio_isr_handler_LED(void *param);
BTS_WEAK void gpio_isr_handler_LEDB_CH0(void *param);
BTS_WEAK void gpio_isr_handler_LEDB_CH1(void *param);
BTS_WEAK void gpio_isr_handler_LEDB_CH2(void *param);
BTS_WEAK void gpio_isr_handler_LEDB_CH3(void *param);
BTS_WEAK void gpio_isr_handler_LEDG_CH0(void *param);
BTS_WEAK void gpio_isr_handler_LEDG_CH1(void *param);
BTS_WEAK void gpio_isr_handler_LEDG_CH2(void *param);
BTS_WEAK void gpio_isr_handler_LEDG_CH3(void *param);
BTS_WEAK void gpio_isr_handler_LEDR_CH0(void *param);
BTS_WEAK void gpio_isr_handler_LEDR_CH1(void *param);
BTS_WEAK void gpio_isr_handler_LEDR_CH2(void *param);
BTS_WEAK void gpio_isr_handler_LEDR_CH3(void *param);
BTS_WEAK void gpio_isr_handler_aurora_reset(void *param);
BTS_WEAK void gpio_isr_handler_channel_up(void *param);
BTS_WEAK void gpio_isr_handler_crc_pass_fail_n(void *param);
BTS_WEAK void gpio_isr_handler_crc_valid(void *param);
BTS_WEAK void gpio_isr_handler_device_dna_high(void *param);
BTS_WEAK void gpio_isr_handler_device_dna_low(void *param);
BTS_WEAK void gpio_isr_handler_device_dna_read_done(void *param);
BTS_WEAK void gpio_isr_handler_device_dna_read_enable(void *param);
BTS_WEAK void gpio_isr_handler_frame_err(void *param);
BTS_WEAK void gpio_isr_handler_hard_err(void *param);
BTS_WEAK void gpio_isr_handler_lane_up(void *param);
BTS_WEAK void gpio_isr_handler_pll_not_locked_out(void *param);
BTS_WEAK void gpio_isr_handler_rx_resetdone_out(void *param);
BTS_WEAK void gpio_isr_handler_soft_err(void *param);
BTS_WEAK void gpio_isr_handler_tx_lock(void *param);
BTS_WEAK void gpio_isr_handler_tx_resetdone_out(void *param);


gpio_info_t gpio_info_table[] =
    {
        // id               name,           axi or ps,          direction,          enable,   pinnum, defaultval, inten, inttype, isrhandler
        {gpio_id_EQ_RX_DE0, "EQ_RX_DE0", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 14, 0, gpio_inttype_none, gpio_isr_handler_EQ_RX_DE0},
        {gpio_id_EQ_RX_DE1, "EQ_RX_DE1", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 17, 0, gpio_inttype_none, gpio_isr_handler_EQ_RX_DE1},
        {gpio_id_EQ_RX_DIS, "EQ_RX_DIS", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 22, 0, gpio_inttype_none, gpio_isr_handler_EQ_RX_DIS},
        {gpio_id_EQ_RX_LOS, "EQ_RX_LOS", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 23, 0, gpio_inttype_none, gpio_isr_handler_EQ_RX_LOS},
        {gpio_id_EQ_RX_POL, "EQ_RX_POL", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 15, 0, gpio_inttype_none, gpio_isr_handler_EQ_RX_POL},
        {gpio_id_EQ_RX_SWG, "EQ_RX_SWG", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 16, 0, gpio_inttype_none, gpio_isr_handler_EQ_RX_SWG},
        {gpio_id_EQ_TX_DE0, "EQ_TX_DE0", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 20, 0, gpio_inttype_none, gpio_isr_handler_EQ_TX_DE0},
        {gpio_id_EQ_TX_DE1, "EQ_TX_DE1", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 19, 0, gpio_inttype_none, gpio_isr_handler_EQ_TX_DE1},
        {gpio_id_EQ_TX_DIS, "EQ_TX_DIS", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 12, 0, gpio_inttype_none, gpio_isr_handler_EQ_TX_DIS},
        {gpio_id_EQ_TX_LOS, "EQ_TX_LOS", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 13, 0, gpio_inttype_none, gpio_isr_handler_EQ_TX_LOS},
        {gpio_id_EQ_TX_POL, "EQ_TX_POL", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 21, 0, gpio_inttype_none, gpio_isr_handler_EQ_TX_POL},
        {gpio_id_EQ_TX_SWG, "EQ_TX_SWG", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 18, 0, gpio_inttype_none, gpio_isr_handler_EQ_TX_SWG},
        {gpio_id_LED, "LED", (void *)&gpio_ps, gpio_info_type_ps, gpio_direction_out, gpio_enable, 7, 0, gpio_inttype_none, gpio_isr_handler_LED},
        {gpio_id_LEDB_CH0, "LEDB_CH0", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 2, 1, gpio_inttype_none, gpio_isr_handler_LEDB_CH0},
        {gpio_id_LEDB_CH1, "LEDB_CH1", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 5, 1, gpio_inttype_none, gpio_isr_handler_LEDB_CH1},
        {gpio_id_LEDB_CH2, "LEDB_CH2", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 8, 1, gpio_inttype_none, gpio_isr_handler_LEDB_CH2},
        {gpio_id_LEDB_CH3, "LEDB_CH3", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 11, 1, gpio_inttype_none, gpio_isr_handler_LEDB_CH3},
        {gpio_id_LEDG_CH0, "LEDG_CH0", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 1, 1, gpio_inttype_none, gpio_isr_handler_LEDG_CH0},
        {gpio_id_LEDG_CH1, "LEDG_CH1", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 4, 1, gpio_inttype_none, gpio_isr_handler_LEDG_CH1},
        {gpio_id_LEDG_CH2, "LEDG_CH2", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 7, 1, gpio_inttype_none, gpio_isr_handler_LEDG_CH2},
        {gpio_id_LEDG_CH3, "LEDG_CH3", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 10, 1, gpio_inttype_none, gpio_isr_handler_LEDG_CH3},
        {gpio_id_LEDR_CH0, "LEDR_CH0", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 0, 1, gpio_inttype_none, gpio_isr_handler_LEDR_CH0},
        {gpio_id_LEDR_CH1, "LEDR_CH1", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 3, 1, gpio_inttype_none, gpio_isr_handler_LEDR_CH1},
        {gpio_id_LEDR_CH2, "LEDR_CH2", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 6, 1, gpio_inttype_none, gpio_isr_handler_LEDR_CH2},
        {gpio_id_LEDR_CH3, "LEDR_CH3", (void *)&gpio3_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 9, 1, gpio_inttype_none, gpio_isr_handler_LEDR_CH3},
        {gpio_id_aurora_reset, "aurora_reset", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 32, 0, gpio_inttype_none, gpio_isr_handler_aurora_reset},
        {gpio_id_channel_up, "channel_up", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 0, 0, gpio_inttype_none, gpio_isr_handler_channel_up},
        {gpio_id_crc_pass_fail_n, "crc_pass_fail_n", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 1, 0, gpio_inttype_none, gpio_isr_handler_crc_pass_fail_n},
        {gpio_id_crc_valid, "crc_valid", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 2, 0, gpio_inttype_none, gpio_isr_handler_crc_valid},
        {gpio_id_device_dna_high, "device_dna_high", (void *)&gpio2_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 32, 0, gpio_inttype_none, gpio_isr_handler_device_dna_high},
        {gpio_id_device_dna_low, "device_dna_low", (void *)&gpio2_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 0, 0, gpio_inttype_none, gpio_isr_handler_device_dna_low},
        {gpio_id_device_dna_read_done, "device_dna_read_done", (void *)&gpio1_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 32, 0, gpio_inttype_none, gpio_isr_handler_device_dna_read_done},
        {gpio_id_device_dna_read_enable, "device_dna_read_enable", (void *)&gpio1_axi, gpio_info_type_axi, gpio_direction_out, gpio_enable, 0, 0, gpio_inttype_none, gpio_isr_handler_device_dna_read_enable},
        {gpio_id_frame_err, "frame_err", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 3, 0, gpio_inttype_none, gpio_isr_handler_frame_err},
        {gpio_id_hard_err, "hard_err", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 4, 0, gpio_inttype_none, gpio_isr_handler_hard_err},
        {gpio_id_lane_up, "lane_up", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 5, 0, gpio_inttype_none, gpio_isr_handler_lane_up},
        {gpio_id_pll_not_locked_out, "pll_not_locked_out", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 6, 0, gpio_inttype_none, gpio_isr_handler_pll_not_locked_out},
        {gpio_id_rx_resetdone_out, "rx_resetdone_out", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 7, 0, gpio_inttype_none, gpio_isr_handler_rx_resetdone_out},
        {gpio_id_soft_err, "soft_err", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 8, 0, gpio_inttype_none, gpio_isr_handler_soft_err},
        {gpio_id_tx_lock, "tx_lock", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 9, 0, gpio_inttype_none, gpio_isr_handler_tx_lock},
        {gpio_id_tx_resetdone_out, "tx_resetdone_out", (void *)&gpio0_axi, gpio_info_type_axi, gpio_direction_in, gpio_enable, 10, 0, gpio_inttype_none, gpio_isr_handler_tx_resetdone_out},
};

/* declare static variables */


/* static function prototypes */


/* functions */
void gpio_drv_info_unittest(void)
{
    /* OUTPUT port gpio_id_EQ_RX_DE0, gpio3_axi GPIO port 14, clear/set/clear test */
    gpio_drv_write(gpio_id_EQ_RX_DE0, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_RX_DE0, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_RX_DE0, 0);

    /* OUTPUT port gpio_id_EQ_RX_DE1, gpio3_axi GPIO port 17, clear/set/clear test */
    gpio_drv_write(gpio_id_EQ_RX_DE1, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_RX_DE1, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_RX_DE1, 0);

    /* OUTPUT port gpio_id_EQ_RX_DIS, gpio3_axi GPIO port 22, clear/set/clear test */
    gpio_drv_write(gpio_id_EQ_RX_DIS, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_RX_DIS, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_RX_DIS, 0);

    /* INPUT port gpio_id_EQ_RX_LOS, gpio3_axi GPIO port 23, read test */
    printf("gpio_id_EQ_RX_LOS value is %ld\n", gpio_drv_read(gpio_id_EQ_RX_LOS));

    /* OUTPUT port gpio_id_EQ_RX_POL, gpio3_axi GPIO port 15, clear/set/clear test */
    gpio_drv_write(gpio_id_EQ_RX_POL, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_RX_POL, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_RX_POL, 0);

    /* OUTPUT port gpio_id_EQ_RX_SWG, gpio3_axi GPIO port 16, clear/set/clear test */
    gpio_drv_write(gpio_id_EQ_RX_SWG, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_RX_SWG, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_RX_SWG, 0);

    /* OUTPUT port gpio_id_EQ_TX_DE0, gpio3_axi GPIO port 20, clear/set/clear test */
    gpio_drv_write(gpio_id_EQ_TX_DE0, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_TX_DE0, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_TX_DE0, 0);

    /* OUTPUT port gpio_id_EQ_TX_DE1, gpio3_axi GPIO port 19, clear/set/clear test */
    gpio_drv_write(gpio_id_EQ_TX_DE1, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_TX_DE1, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_TX_DE1, 0);

    /* OUTPUT port gpio_id_EQ_TX_DIS, gpio3_axi GPIO port 12, clear/set/clear test */
    gpio_drv_write(gpio_id_EQ_TX_DIS, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_TX_DIS, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_TX_DIS, 0);

    /* INPUT port gpio_id_EQ_TX_LOS, gpio3_axi GPIO port 13, read test */
    printf("gpio_id_EQ_TX_LOS value is %ld\n", gpio_drv_read(gpio_id_EQ_TX_LOS));

    /* OUTPUT port gpio_id_EQ_TX_POL, gpio3_axi GPIO port 21, clear/set/clear test */
    gpio_drv_write(gpio_id_EQ_TX_POL, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_TX_POL, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_TX_POL, 0);

    /* OUTPUT port gpio_id_EQ_TX_SWG, gpio3_axi GPIO port 18, clear/set/clear test */
    gpio_drv_write(gpio_id_EQ_TX_SWG, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_TX_SWG, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_EQ_TX_SWG, 0);

    /* OUTPUT port gpio_id_LED, gpio_ps GPIO port 7, clear/set/clear test */
    gpio_drv_write(gpio_id_LED, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LED, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LED, 0);

    /* OUTPUT port gpio_id_LEDB_CH0, gpio3_axi GPIO port 2, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDB_CH0, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDB_CH0, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDB_CH0, 0);

    /* OUTPUT port gpio_id_LEDB_CH1, gpio3_axi GPIO port 5, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDB_CH1, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDB_CH1, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDB_CH1, 0);

    /* OUTPUT port gpio_id_LEDB_CH2, gpio3_axi GPIO port 8, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDB_CH2, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDB_CH2, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDB_CH2, 0);

    /* OUTPUT port gpio_id_LEDB_CH3, gpio3_axi GPIO port 11, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDB_CH3, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDB_CH3, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDB_CH3, 0);

    /* OUTPUT port gpio_id_LEDG_CH0, gpio3_axi GPIO port 1, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDG_CH0, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDG_CH0, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDG_CH0, 0);

    /* OUTPUT port gpio_id_LEDG_CH1, gpio3_axi GPIO port 4, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDG_CH1, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDG_CH1, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDG_CH1, 0);

    /* OUTPUT port gpio_id_LEDG_CH2, gpio3_axi GPIO port 7, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDG_CH2, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDG_CH2, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDG_CH2, 0);

    /* OUTPUT port gpio_id_LEDG_CH3, gpio3_axi GPIO port 10, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDG_CH3, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDG_CH3, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDG_CH3, 0);

    /* OUTPUT port gpio_id_LEDR_CH0, gpio3_axi GPIO port 0, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDR_CH0, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDR_CH0, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDR_CH0, 0);

    /* OUTPUT port gpio_id_LEDR_CH1, gpio3_axi GPIO port 3, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDR_CH1, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDR_CH1, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDR_CH1, 0);

    /* OUTPUT port gpio_id_LEDR_CH2, gpio3_axi GPIO port 6, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDR_CH2, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDR_CH2, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDR_CH2, 0);

    /* OUTPUT port gpio_id_LEDR_CH3, gpio3_axi GPIO port 9, clear/set/clear test */
    gpio_drv_write(gpio_id_LEDR_CH3, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDR_CH3, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_LEDR_CH3, 0);

    /* OUTPUT port gpio_id_aurora_reset, gpio0_axi GPIO port 32, clear/set/clear test */
    gpio_drv_write(gpio_id_aurora_reset, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_aurora_reset, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_aurora_reset, 0);

    /* INPUT port gpio_id_channel_up, gpio0_axi GPIO port 0, read test */
    printf("gpio_id_channel_up value is %ld\n", gpio_drv_read(gpio_id_channel_up));

    /* INPUT port gpio_id_crc_pass_fail_n, gpio0_axi GPIO port 1, read test */
    printf("gpio_id_crc_pass_fail_n value is %ld\n", gpio_drv_read(gpio_id_crc_pass_fail_n));

    /* INPUT port gpio_id_crc_valid, gpio0_axi GPIO port 2, read test */
    printf("gpio_id_crc_valid value is %ld\n", gpio_drv_read(gpio_id_crc_valid));

    /* INPUT port gpio_id_device_dna_high, gpio2_axi GPIO port 32, read test */
    printf("gpio_id_device_dna_high value is %ld\n", gpio_drv_read(gpio_id_device_dna_high));

    /* INPUT port gpio_id_device_dna_low, gpio2_axi GPIO port 0, read test */
    printf("gpio_id_device_dna_low value is %ld\n", gpio_drv_read(gpio_id_device_dna_low));

    /* INPUT port gpio_id_device_dna_read_done, gpio1_axi GPIO port 32, read test */
    printf("gpio_id_device_dna_read_done value is %ld\n", gpio_drv_read(gpio_id_device_dna_read_done));

    /* OUTPUT port gpio_id_device_dna_read_enable, gpio1_axi GPIO port 0, clear/set/clear test */
    gpio_drv_write(gpio_id_device_dna_read_enable, 0);
    os_sleep(1);
    gpio_drv_write(gpio_id_device_dna_read_enable, 1);
    os_sleep(1);
    gpio_drv_write(gpio_id_device_dna_read_enable, 0);

    /* INPUT port gpio_id_frame_err, gpio0_axi GPIO port 3, read test */
    printf("gpio_id_frame_err value is %ld\n", gpio_drv_read(gpio_id_frame_err));

    /* INPUT port gpio_id_hard_err, gpio0_axi GPIO port 4, read test */
    printf("gpio_id_hard_err value is %ld\n", gpio_drv_read(gpio_id_hard_err));

    /* INPUT port gpio_id_lane_up, gpio0_axi GPIO port 5, read test */
    printf("gpio_id_lane_up value is %ld\n", gpio_drv_read(gpio_id_lane_up));

    /* INPUT port gpio_id_pll_not_locked_out, gpio0_axi GPIO port 6, read test */
    printf("gpio_id_pll_not_locked_out value is %ld\n", gpio_drv_read(gpio_id_pll_not_locked_out));

    /* INPUT port gpio_id_rx_resetdone_out, gpio0_axi GPIO port 7, read test */
    printf("gpio_id_rx_resetdone_out value is %ld\n", gpio_drv_read(gpio_id_rx_resetdone_out));

    /* INPUT port gpio_id_soft_err, gpio0_axi GPIO port 8, read test */
    printf("gpio_id_soft_err value is %ld\n", gpio_drv_read(gpio_id_soft_err));

    /* INPUT port gpio_id_tx_lock, gpio0_axi GPIO port 9, read test */
    printf("gpio_id_tx_lock value is %ld\n", gpio_drv_read(gpio_id_tx_lock));

    /* INPUT port gpio_id_tx_resetdone_out, gpio0_axi GPIO port 10, read test */
    printf("gpio_id_tx_resetdone_out value is %ld\n", gpio_drv_read(gpio_id_tx_resetdone_out));
}


BTS_WEAK void gpio_isr_handler_EQ_RX_DE0(void *param) {}
BTS_WEAK void gpio_isr_handler_EQ_RX_DE1(void *param) {}
BTS_WEAK void gpio_isr_handler_EQ_RX_DIS(void *param) {}
BTS_WEAK void gpio_isr_handler_EQ_RX_LOS(void *param) {}
BTS_WEAK void gpio_isr_handler_EQ_RX_POL(void *param) {}
BTS_WEAK void gpio_isr_handler_EQ_RX_SWG(void *param) {}
BTS_WEAK void gpio_isr_handler_EQ_TX_DE0(void *param) {}
BTS_WEAK void gpio_isr_handler_EQ_TX_DE1(void *param) {}
BTS_WEAK void gpio_isr_handler_EQ_TX_DIS(void *param) {}
BTS_WEAK void gpio_isr_handler_EQ_TX_LOS(void *param) {}
BTS_WEAK void gpio_isr_handler_EQ_TX_POL(void *param) {}
BTS_WEAK void gpio_isr_handler_EQ_TX_SWG(void *param) {}
BTS_WEAK void gpio_isr_handler_LED(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDB_CH0(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDB_CH1(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDB_CH2(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDB_CH3(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDG_CH0(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDG_CH1(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDG_CH2(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDG_CH3(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDR_CH0(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDR_CH1(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDR_CH2(void *param) {}
BTS_WEAK void gpio_isr_handler_LEDR_CH3(void *param) {}
BTS_WEAK void gpio_isr_handler_aurora_reset(void *param) {}
BTS_WEAK void gpio_isr_handler_channel_up(void *param) {}
BTS_WEAK void gpio_isr_handler_crc_pass_fail_n(void *param) {}
BTS_WEAK void gpio_isr_handler_crc_valid(void *param) {}
BTS_WEAK void gpio_isr_handler_device_dna_high(void *param) {}
BTS_WEAK void gpio_isr_handler_device_dna_low(void *param) {}
BTS_WEAK void gpio_isr_handler_device_dna_read_done(void *param) {}
BTS_WEAK void gpio_isr_handler_device_dna_read_enable(void *param) {}
BTS_WEAK void gpio_isr_handler_frame_err(void *param) {}
BTS_WEAK void gpio_isr_handler_hard_err(void *param) {}
BTS_WEAK void gpio_isr_handler_lane_up(void *param) {}
BTS_WEAK void gpio_isr_handler_pll_not_locked_out(void *param) {}
BTS_WEAK void gpio_isr_handler_rx_resetdone_out(void *param) {}
BTS_WEAK void gpio_isr_handler_soft_err(void *param) {}
BTS_WEAK void gpio_isr_handler_tx_lock(void *param) {}
BTS_WEAK void gpio_isr_handler_tx_resetdone_out(void *param) {}

#endif // (SYS_SYSTEM_VERSION == SYS_LOGGER_VERSION_V01)


/******************************************************************************
 * function name : gpio_drv_info_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return void description
 * modification date : 2018.01.30
 *****************************************************************************/
void gpio_drv_info_init(void)
{
    // init for gpio driver
// gpio_drv_info_ir24m.yaml
#if SYS_SYSTEM_VERSION >= SYS_RADAR_VERSION_BEV31
    gpio_drv_ps_init(&gpio_ps, XPAR_XGPIOPS_0_DEVICE_ID);
#endif // SYS_SYSTEM_VERSION >= SYS_RADAR_VERSION_BEV31
// gpio_drv_info_ir24s.yaml
#if(SYS_SYSTEM_VERSION >= SYS_RADAR_VERSION_BEV23) && (SYS_SYSTEM_VERSION <= SYS_RADAR_VERSION_BEV25)
    gpio_drv_axi_init(&gpio0_axi, XPAR_GPIO_0_DEVICE_ID);
    gpio_drv_axi_init(&gpio1_axi, XPAR_GPIO_1_DEVICE_ID);
    gpio_drv_axi_init(&gpio2_axi, XPAR_GPIO_2_DEVICE_ID);
    gpio_drv_ps_init(&gpio_ps, XPAR_XGPIOPS_0_DEVICE_ID);
#endif // (SYS_SYSTEM_VERSION >= SYS_RADAR_VERSION_BEV23) && (SYS_SYSTEM_VERSION <= SYS_RADAR_VERSION_BEV25)
// gpio_drv_info_ir24x.yaml
#if SYS_SYSTEM_VERSION == SYS_RADAR_VERSION_BEVX10
    gpio_drv_axi_init(&gpio0_axi, XPAR_GPIO_0_DEVICE_ID);
    gpio_drv_ps_init(&gpio_ps, XPAR_XGPIOPS_0_DEVICE_ID);
#endif // SYS_SYSTEM_VERSION == SYS_RADAR_VERSION_BEVX10
// gpio_drv_info_lelogger.yaml
#if(SYS_SYSTEM_VERSION == SYS_LOGGER_VERSION_V01)
    gpio_drv_axi_init(&gpio0_axi, XPAR_GPIO_0_DEVICE_ID);
    gpio_drv_axi_init(&gpio1_axi, XPAR_DEVICEDNA_AXI_GPIO_DNA_CONTROL_DEVICE_ID);
    gpio_drv_axi_init(&gpio2_axi, XPAR_DEVICEDNA_AXI_GPIO_DNA_READER_DEVICE_ID);
    gpio_drv_axi_init(&gpio3_axi, XPAR_AXI_GPIO_BOARDCONTROL_DEVICE_ID);
    gpio_drv_ps_init(&gpio_ps, XPAR_XGPIOPS_0_DEVICE_ID);
#endif // (SYS_SYSTEM_VERSION == SYS_LOGGER_VERSION_V01)
}

/* end of file */
