/************************************************************************
| Project Name: bts_comm_appl_flog
|    File Name: bts_comm_appl_flog.c
|  Description: file detailed description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------
| SKJ          SONG KYEONG JIN           Bitsensing
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description
| ----------  ----  ------  --------------------------------------------
| 2019.08.21   0.0   SKJ   Creation;
|***********************************************************************/

/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"
#include <string.h>

/* include system driver header */
//#include "drivers.h"
#include "krs_lib.h"

/* include system bsp header */
#include "os.h"

/* include system application header */
#include "sys_param.h"

/* final include module header */
#include "bts_comm.h"
#include "bts_comm_appl.h"
#include "bts_comm_cmd.h"
#include "bts_comm_packet.h"
#include "bts_comm_status.h"


#include "bts_comm_appl_flog.h"

//#include "flog_task.h"
/* declare global variables */
#if SYS_APP_TYPE == SYS_APP_TYPE_FCW
comm_appl_floginfo_t raw_app_flog;
#endif

/* declare static variables */
// temp gps data

/* static function prototypes */

/* functions */

// object


/******************************************************************************
 * function name : bts_comm_appl_its_init
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
 * modification date : 2018.06.26
 *****************************************************************************/
void bts_comm_appl_flog_init(void)
{
#if SYS_APP_TYPE == SYS_APP_TYPE_FCW
	krs_memclearitem(raw_app_flog);
#endif
}


/******************************************************************************
 * function name : bts_comm_appl_raw_app_flog_precallback
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
 * modification date : 2019.04.13
 *****************************************************************************/
void bts_comm_appl_raw_app_flog_precallback(void *pvparam, size_t size)
{
#if SYS_APP_TYPE == SYS_APP_TYPE_FCW
	comm_appl_floginfo_t *p = (comm_appl_floginfo_t *)pvparam;

    p->emmcfreerate= 0.0f;
    p->filenumber= flog_filenumber;
    p->eventflag = rsp_appl_fcw_eventflag;
    p->flog_status = flog_status;

#endif
}


/* end of file */
