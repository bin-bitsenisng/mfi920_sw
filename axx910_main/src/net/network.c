/************************************************************************
 | Project Name: KRS24
 |    File Name: network.c
 |  Description: detailed Description
 |-----------------------------------------------------------------------
 |               A U T H O R   I D E N T I T Y
 |-----------------------------------------------------------------------
 | Initials     Name                      Company
 | --------     ---------------------     -------------------------------
 | SKJ          SONG KYEONG JIN           KRS Corporation
 |-----------------------------------------------------------------------
 |              R E V I S I O N   H I S T O R Y
 |-----------------------------------------------------------------------
 | Date         Ver  Author  Description
 | ----------  ----  ------  --------------------------------------------
 | 2015.01.14   0.0   SKJ   Creation;
 |***********************************************************************/

/* include system primitive types */
#include "network_cfg.h"

/* include system driver header */


/* include system bsp header */


/* include system application header */
#include "app/app.h"

/* final include module header */
# include "network.h"


/* declare global variables */
uint8_t network_up_flag=0;

/* declare static variables */


/* static function prototypes */

/* functions */
/***************************************************
 * function name : network_init
 * description : module init function
 * input param : void
 * return : retOk or retFail
 * TODO :
 ***************************************************/
network_ret_t network_init(void)
{
    /* module init code here*/
	network_up_flag = 0;
#if SYS_NETWORK_ETH_STACK == SYS_NETWORK_ETH_STACK_LINUX
	network_up_flag = 1;
#endif

	//if_init();
	app_init();
    return retOK;
}

network_ret_t network_osinit(void)
{
    /* module init code here*/
	if_osinit();

    return retOK;
}



network_ret_t network_osappinit(void)
{
	while(if_osinit_complete() != retOK)
	{
		krs_log("network interface is not initialized, wait.\n\r");
		os_sleep(2000);
	}
	app_osinit();
    return retOK;
}



/* end of file */
