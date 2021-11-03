/************************************************************************
| Project Name: bts_comm_status
|    File Name: bts_comm_status.c
|  Description: file detailed description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------
| SKJ          SONG KYEONG JIN           Lobeye
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description
| ----------  ----  ------  --------------------------------------------
| 2017.10.11   0.0   SKJ   Creation;
|***********************************************************************/


/* include system primitive types */
#include "bts.h"

/* include system driver header */


/* include system bsp header */


/* include system application header */
//#include "drivers.h"
//#include "taskmgr.h"

/* final include module header */
#include "bts_comm_cfg.h"
#include "bts_comm.h"
#include "bts_comm_odt.h"
#include "bts_comm_status.h"
//#include "modulation.h"
#include "os.h"



bts_comm_status_info_t bts_comm_status;
/* declare static variables */
os_sem_t sem_bts_comm_status_daq_start;

/* static function prototypes */

/******************************************************************************
 * function name : bts_comm_status_init
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
 * modification date : 2017.10.11
 *****************************************************************************/
void bts_comm_status_init(void)
{
    // clear all bts_comm_status
    Ir24xCommStatusReset();

    // set default state
    Ir24xCommSetDisconnected();
    Ir24xCommSetConnectModeNormal();
    Ir24xCommSetStartStopSynchModeStop();
    os_sem_init(sem_bts_comm_status_daq_start);
}



/* end of file */
