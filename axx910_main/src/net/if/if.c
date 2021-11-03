/************************************************************************
 | Project Name: KRS24
 |    File Name: if.c
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
#include "bts.h"
#include "if_cfg.h"

/* include system driver header */
#include "eth/eth.h"

/* include system bsp header */


/* include system application header */


/* final include module header */
# include "if.h"


/* declare global variables */


/* declare static variables */


/* static function prototypes */

/* functions */
/***************************************************
 * function name : if_init
 * description : module init function
 * input param : void
 * return : retOk or retFail
 * TODO :
 ***************************************************/
if_ret_t if_init(void)
{
	//eth_init();
	//can_init();
	//uart_init();
    return retOK;
}


if_ret_t if_osinit(void)
{
	eth_osinit();
	//can_osinit();
	//uart_osinit();
	return retOK;
}


if_ret_t if_osinit_complete(void)
{
	return eth_is_setup_complete();
}

/* end of file */
