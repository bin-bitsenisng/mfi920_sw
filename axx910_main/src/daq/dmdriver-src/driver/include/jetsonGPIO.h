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


#ifndef JETSONGPIO_H_
#define JETSONGPIO_H_

#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/time.h>

 /****************************************************************
 * Constants
 ****************************************************************/
 
#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define MAX_BUF 64

typedef unsigned int jetsonGPIO ;
typedef unsigned int pinDirection ;
typedef unsigned int pinValue ;

enum pinDirections {
	inputPin  = 0,
	outputPin = 1
} ;

enum pinValues {
    low = 0,
    high = 1,
    off = 0,  // synonym for things like lights
    on = 1
}  ;

enum jetsonXavierGPIONumber {      
    gpio_id_CONN_FE_PWR_EN = 417,   //CONN_FE_PWR_EN
    gpio_id_CONN_RFIC_nRST = 266,   //CONN_RFIC_nRST < == this pin is inverted...
    gpio_id_CONN_RFIC_nPWDN = 413,  //CONN_RFIC_nPWDN < == need...
    gpio_id_CONN_RFIC_TRIG = 409,   //CONN_RFIC_TRIG < == need...
    gpio_id_CONN_FE_IRQ1 = 264,     //CONN_RFIC_IRQ0 < == need to check
    gpio_id_CONN_FE_IRQ2 = 265,     //CONN_RFIC_IRQ1 < == need to check
    gpio_id_CONN_GPIO0 = 267,       //CONN_GPIO0
    gpio_id_CONN_GPIO1 = 424,       //CONN_GPIO0
    gpio_id_CONN_GPIO2 = 418,       //CONN_GPIO0
    gpio_id_CONN_GPIO3 = 446,       //CONN_GPIO0
    gpio_id_CONN_GPIO4 = 447,       //CONN_GPIO0
    gpio_id_CONN_GPIO5 = 448,       //CONN_GPIO0
    gpio_id_CONN_CPLD_TMS = 476,    //CONN_CPLD_TMS
    gpio_id_CONN_CPLD_TCK = 477,    //CONN_CPLD_TCK
    gpio_id_CONN_CPLD_TDI = 478,    //CONN_CPLD_TDI
    gpio_id_CONN_CPLD_TDO = 479,    //CONN_CPLD_TDO
    gpio_id_CONN_CPLD_nCLR = 427,   //CONN_CPLD_nCLR
    gpio_id_CONN_CPLD_OE = 428,     //CONN_CPLD_OE
    gpio_id_LED_RED = 442,          //LED_RED
    gpio_id_LED_GREEN = 443,        //LED_GREEN
    gpio_id_LED_BLUE = 444,         //LED_BLUE
} ;

int gpioExport ( jetsonGPIO gpio ) ;
int gpioUnexport ( jetsonGPIO gpio ) ;
int gpioSetDirection ( jetsonGPIO, pinDirection out_flag ) ;
int gpioSetValue ( jetsonGPIO gpio, pinValue value ) ;
int gpioGetValue ( jetsonGPIO gpio, unsigned int *value ) ;
int gpioSetEdge ( jetsonGPIO gpio, char *edge ) ;
int gpioOpen ( jetsonGPIO gpio ) ;
int gpioClose ( int fileDescriptor ) ;
int gpioActiveLow ( jetsonGPIO gpio, unsigned int value ) ;



#endif // JETSONGPIO_H_
