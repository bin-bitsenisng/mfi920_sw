/************************************************************************
 | Project Name: KRS24
 |    File Name: app.c
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
#include "app_cfg.h"

/* include system driver header */


/* include system bsp header */
#include "if.h"

/* include system application header */


/* final include module header */
#include "app.h"


/* declare global variables */
// server declare


/* declare static variables */


/* static function prototypes */
void app_launch_app_threads(void);
void app_print_headers(void);
/* functions */
/***************************************************
 * function name : app_init
 * description : module init function
 * input param : void
 * return : retOk or retFail
 * TODO :
 ***************************************************/
app_ret_t app_init(void)
{
    /* module init code here*/
    return retOK;
}



app_ret_t app_osinit(void)
{
    /* module init code here*/
	app_print_headers();
    app_launch_app_threads();
    return retOK;
}



/***************************************************
 * function name : app_launch_app_threads
 * description : module init function
 * input param : void
 * return : retOk or retFail
 * TODO :
 ***************************************************/
void app_launch_app_threads(void)
{
/* start webserver thread */
#if APP_INCLUDE_LOGGER_FINDECU_SERVER == 1
    logger_findecu_init();
#endif

#if APP_INCLUDE_LOGGER_SERVER == 1
    logger_init();
#endif

#if APP_INCLUDE_LOGPRINT_SERVER == 1
    logger_print_init();
#endif

#if APP_INCLUDE_COMM_APPL_SERVER == 1
    bts_comm_appl_init();
#endif

#if APP_INCLUDE_TRACE == 1
	vTraceEnable(TRC_START_AWAIT_HOST);
#endif
}




/***************************************************
 * function name : app_print_headers
 * description : module init function
 * input param : void
 * return : retOk or retFail
 * TODO :
 ***************************************************/
void app_print_headers(void)
{
#if APP_INCLUDE_LOGGER_SERVER == 1
    logger_print_header();
#endif
    printf("\r\n");
}


/* end of file */
