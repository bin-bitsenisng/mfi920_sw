/************************************************************************
| Project Name: bts_comm_appl_common
|    File Name: bts_comm_appl_common.c
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
| 2018.06.26   0.0   SKJ   Creation;
|***********************************************************************/

/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"

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

/* declare global variables */

/* declare static variables */
// temp gps data

/* static function prototypes */

/* functions */

// object


/******************************************************************************
 * function name : bts_comm_appl_common_init
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
void bts_comm_appl_common_init(void)
{


}


int32_t bts_comm_appl_common_check_activated(bts_comm_daqinfo_t *daqinfoptr)
{
	if(daqinfoptr == NULL)
	{
		return retFail;
	}

	if(daqinfoptr->enable != 0)
	{
		if(daqinfoptr->ref_enable != NULL)
		{
			if(*(daqinfoptr->ref_enable)!=0)
			{
				return retOK;
			}
		}
	}
	return retFail;
}


/******************************************************************************
 * function name : bts_comm_appl_common_get_daqinfo
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
int32_t bts_comm_appl_common_get_daqinfo(char_t *desbuffer, uint32_t buffersize)
{
	int32_t i,rawpid;
    int32_t err = 0;


    struct jWriteControl jwcontrol;
    struct jWriteControl *jwc = &jwcontrol;

    jwOpen(jwc, desbuffer, buffersize, JW_OBJECT, JW_COMPACT);

    // 1. "pidlist"
    jwObj_array(jwc, "pidlist");
    rawpid=bts_comm_pid_raw;
    for(i=0;i<bts_comm_pid_max;i++)
    {
    	if(bts_comm_daqinfo[i].pidtype == bts_comm_pidtype_end) break;
    	if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[i])==retOK)
    	{
			if(bts_comm_daqinfo[i].pid < bts_comm_pid_raw )
			{
				jwArr_int32(jwc,bts_comm_daqinfo[i].pid);
			}
			else
			{
				jwArr_int32(jwc,rawpid++);
			}
    	}
    }
    jwEnd(jwc);

    jwObj_array(jwc, "pidnames");
    for(i=0;i<bts_comm_pid_max;i++)
    {
    	if(bts_comm_daqinfo[i].pidtype == bts_comm_pidtype_end) break;
    	if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[i])==retOK)
    	{
    		jwArr_string(jwc, bts_comm_daqinfo[i].pidname);
    	}
    }
    jwEnd(jwc);

    jwObj_object(jwc, "pidtype");
		jwObj_array(jwc, "appl");
		for(i=0;i<bts_comm_pid_max;i++)
		{
			if(bts_comm_daqinfo[i].pidtype == bts_comm_pidtype_end) break;
			if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[i])==retOK)
			{
				if(bts_comm_daqinfo[i].pidtype == bts_comm_pidtype_appl)
				{
					jwArr_int32(jwc, bts_comm_daqinfo[i].pid);
				}
			}
		}
		jwEnd(jwc);
		jwObj_array(jwc, "raw");
		rawpid=bts_comm_pid_raw;
		for(i=0;i<bts_comm_pid_max;i++)
		{
			if(bts_comm_daqinfo[i].pidtype == bts_comm_pidtype_end) break;
			if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[i])==retOK)
			{
				if(bts_comm_daqinfo[i].pidtype == bts_comm_pidtype_raw && bts_comm_daqinfo[i].pid == bts_comm_pid_raw)
				{
					jwArr_int32(jwc,rawpid++);
				}
			}
		}
		jwEnd(jwc);
    jwEnd(jwc);

    jwObj_object(jwc, "pidinfo");
    	rawpid=bts_comm_pid_raw;
    	for(i=0;i<bts_comm_pid_max;i++)
    	{
    		if(bts_comm_daqinfo[i].pidtype == bts_comm_pidtype_end) break;
    		if(bts_comm_appl_common_check_activated(&bts_comm_daqinfo[i])==retOK)
    		{
				if(bts_comm_daqinfo[i].pidtype == bts_comm_pidtype_raw && bts_comm_daqinfo[i].pid == bts_comm_pid_raw)
				{
					jwObj_object(jwc, bts_comm_daqinfo[i].pidname);
					jwObj_string(jwc, "type", "raw");
					jwObj_string(jwc, "symbol", bts_comm_daqinfo[i].symbol);
					jwObj_int32(jwc, "size", bts_comm_daqinfo[i].bytesize);
					jwObj_string(jwc, "format", bts_comm_daqinfo[i].fmt);
					jwEnd(jwc);
				}
    		}
    	}
    jwEnd(jwc);

    err = jwClose(jwc);
    if(err == JWRITE_OK)
    {
        return jwLen(jwc);
    }
    else
    {
        krs_log("bts_comm_appl_common_get_daqinfo : %s JSON_Err : %ld : %s\n\r", "", err, jwErrorToString(err));
        return 0;
    }
}


/* end of file */
