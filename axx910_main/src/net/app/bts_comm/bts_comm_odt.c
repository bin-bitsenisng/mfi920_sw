/************************************************************************
| Project Name: bts_comm_odt
|    File Name: bts_comm_odt.c
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
#include "bts_comm_cfg.h"
#include "krs_lib.h"

/* include system driver header */


/* include system bsp header */
#include "os.h"

/* include system application header */
#include "drivers.h"
#include "taskmgr.h"

/* final include module header */
#include "bts_comm.h"
#include "bts_comm_odt.h"
#include "modulation.h"


uint8_t bts_comm_odt_datatype_size[bts_comm_datatype_END] = {1, 1, 2, 2, 4, 4, 8, 8, 4, 8};
const char_t bts_comm_odt_format_table[bts_comm_datatype_END] = {'b', 'B', 'h', 'H', 'i',
                                                                     'I', 'l', 'L', 'f', 'd'};


/* declare static variables */
//#define XCP_ODT_UNITTEST

/* static function prototypes */
bts_comm_odt_t bts_comm_odt_table[bts_COMM_ODT_MAX];


/* functions */

/******************************************************************************
 * function name : bts_comm_odt_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return bts_comm_odt_ret_t description
 * modification date : 2017.09.22
 *****************************************************************************/
bts_comm_odt_ret_t bts_comm_odt_init(void)
{
    /* module init code here*/
    krs_memclear(bts_comm_odt_table);

    /* init odt table*/

    /* print odt table */
    bts_comm_odt_table_print(bts_comm_odt_table);


    return retOK;
}


/******************************************************************************
 * function name : bts_comm_odt_table_print
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *odttable description
 * \return bts_comm_odt_ret_t description
 * modification date : 2017.09.22
 *****************************************************************************/
bts_comm_odt_ret_t bts_comm_odt_table_print(bts_comm_odt_t *odttable)
{
    uint32_t i;

    for(i = 0; i < bts_COMM_ODT_MAX; i++)
    {
        bts_comm_odt_print(&odttable[i]);
    }
    return retOK;
}


/******************************************************************************
 * function name : bts_comm_odt_print
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *odt description
 * \return bts_comm_odt_ret_t description
 * modification date : 2017.09.22
 *****************************************************************************/
bts_comm_odt_ret_t bts_comm_odt_print(bts_comm_odt_t *odt)
{
    bts_comm_odt_t *odtptr;
    bts_comm_odt_entry_t *entryptr;

    odtptr = odt;
    if(odtptr->odt_entry != NULL)
    {
        entryptr = odtptr->odt_entry;
        krs_log("=== PID:0x%02X ======\n\r", odtptr->pidnum);
        krs_log("name:%s  symbol:%s  format:%s\n\r", entryptr->name, entryptr->symbol,
                entryptr->format);
        krs_log("pidtype:%s  datatype:%c\n\r", entryptr->pidtype,
                bts_comm_odt_format_table[odtptr->type]);
        krs_log("mode:0x%02X, eventchannel:0x%04X, prescaler:%d, priority:%d odtstatus:%d\n\r",
                odtptr->status.mode, odtptr->status.event_channel, odtptr->status.prescaler,
                odtptr->status.priority, odtptr->status.odtstatus);
        krs_log("start_stop_mode : %d\n\r", odtptr->start_stop_synch_mode);
    }

    return retOK;
}


/******************************************************************************
 * function name : bts_comm_set_odt_properties
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 **odttable description
 * \param1 pid description
 * \param2 *pdaqmodestatus description
 * \return bts_comm_odt_ret_t description
 * modification date : 2017.09.22
 *****************************************************************************/
bts_comm_odt_ret_t bts_comm_set_odt_properties(bts_comm_odt_t *odttable, uint8_t pid,
                                                   bts_comm_daqmodestatus_t *pdaqmodestatus)
{
    //    bts_comm_odt_t *odtptr;
    //
    //    if(krslist_empty(odtlistptr))
    //    {
    //      krs_log("XCP ODT Table is empty\n\r");
    //        return retOK;
    //    }
    //    odtptr = bts_comm_odt_search_pid(odtlistptr, pid);
    //    if(odtptr != NULL)
    //    {
    //      krs_memcopy(&odtptr->status, pdaqmodestatus, sizeof(bts_comm_daqmodestatus_t));
    //      return retOK;
    //    }
    return retFail;
}


/***************************************************
 * function name : bts_comm_set_odt_start_stop_mode
 * description : module init function
 * input param : void
 * return : retOk or retFail
 * TODO :
 ***************************************************/
bts_comm_odt_ret_t
bts_comm_set_odt_start_stop_mode(bts_comm_odt_t *odttable, uint8_t pid,
                                   bts_comm_status_start_stop_synch_mode_t mode)
{
    bts_comm_odt_t *odtptr;

    odtptr = bts_comm_odt_search_pid(odttable, pid);
    if(odtptr != NULL)
    {
        odtptr->start_stop_synch_mode = mode;
        return retOK;
    }
    return retFail;
}


/******************************************************************************
 * function name : *bts_comm_odt_search_pid
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *odtlistptr description
 * \param1 pidnum description
 * \return bts_comm_odt_t description
 * modification date : 2017.09.12
 *****************************************************************************/
bts_comm_odt_t *bts_comm_odt_search_pid(bts_comm_odt_t *odttable, uint8_t pidnum)
{
    if(pidnum >= bts_COMM_ODT_MAX)
    {
        krs_log("pidnumber 0x%02X is over bts_COMM_ODT_MAX(0x%02X)\n\r", pidnum,
                bts_COMM_ODT_MAX);
        return NULL;
    }
    return &odttable[pidnum];
}


/* end of file */
