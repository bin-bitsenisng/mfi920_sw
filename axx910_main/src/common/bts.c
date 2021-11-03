/************************************************************************
| Project Name: bts
|    File Name: bts.c
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
| 2020.09.08   0.0   SKJ   Creation;
|***********************************************************************/
/* include system primitive types */
#include "bts.h"
#include "os.h"
/* include system driver header */

/* include system bsp header */

/* include system application header */

/* final include module header */

/* declare global variables */
bts_datetime_t bts_systime;
/* declare static variables */

/* static function prototypes */
void bts_datetime_unittest(void);
void bts_datetime_unittest(void)
{
	char_t buff[64];

	struct timeval tv;
	struct tm ts;
	f64_t servertimestamp;
	f64_t timestamp;

	servertimestamp=1577836800.0;

	tv.tv_sec = (time_t)servertimestamp;
	tv.tv_usec = (suseconds_t)((servertimestamp - floor(servertimestamp))*1000000.0);
	ts = *localtime((time_t*)&tv.tv_sec);

	strftime(buff, sizeof(buff), "%Y-%m-%d:%H:%M:%S", &ts);

	timestamp = bts_datetime_make_timestamp(&ts);

	bts_log("servertimestamp:%lf, tv_sec:%ld, tv_usec:%ld, strftime:%s, mktime:%lf\n\r", servertimestamp,tv.tv_sec, tv.tv_usec, buff, timestamp);
}
/* functions */



/******************************************************************************
 * function name : bts_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 void description
 * \return0 bts_ret_t description
 * modification date : 2020.09.09
 *****************************************************************************/
bts_ret_t bts_init(void)
{
    bts_datetime_init(1577836800.0); // 2020.01.01:00:00:00.000

    bts_log_init();
    //bts_datetime_print();
    //bts_datetime_unittest();

    return retOK;
}

/******************************************************************************
 * function name : bts_datetime_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 sys_timestamp description
 * \return0 void description
 * modification date : 2020.09.09
 *****************************************************************************/
void bts_datetime_init(f64_t sys_timestamp)
{
    krs_memclearitem(bts_systime);
    bts_datetime_settime(sys_timestamp);
}


/******************************************************************************
 * function name : bts_datetime_update
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 sys_timestamp description
 * \return0 bts_ret_t description
 * modification date : 2020.09.09
 *****************************************************************************/
bts_ret_t bts_datetime_update(f64_t sys_timestamp)
{
    bts_systime.sys_timestamp = sys_timestamp;	// sec unit
    bts_systime.tv.tv_sec = (time_t)(sys_timestamp);
    bts_systime.tv.tv_usec = (suseconds_t)((sys_timestamp - floor(sys_timestamp))*1000000.0);
    bts_systime.ts = *localtime((time_t*)&bts_systime.tv.tv_sec);
    return retOK;
}



/******************************************************************************
 * function name : bts_datetime_getstr
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *fmt description
 * \param1 *buff description
 * \param2 buffsize description
 * \param3 ms_en description
 * \param4 us_en description
 * \return0 int32_t description
 * modification date : 2020.09.09
 *****************************************************************************/
int32_t bts_datetime_getstr(const char *fmt, char *buff, size_t buffsize, uint8_t ms_en,
                            uint8_t us_en)
{
    int32_t n;
    uint32_t ms;
    uint32_t us;
    f64_t timestamp_s;
    timestamp_s = bts_datetime_gettime();
    n = strftime(buff, buffsize, fmt, &bts_systime.ts);


    if(ms_en != 0)
    {
    	us = ((uint32_t)((timestamp_s - floor(timestamp_s)) * 1000000.0));
    	ms = us/1000;
    	if(us_en != 0)
    	{
    		n += snprintf(&buff[n], buffsize - n, ".%03d_%03d", ms, us%1000);
    	}
    	else
    	{
    		n += snprintf(&buff[n], buffsize - n, ".%03d", ms);
    	}
    }


    return n;
}

/******************************************************************************
 * function name : bts_datetime_settime
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 new_servertimestamp description
 * \return0 bts_ret_t description
 * modification date : 2020.09.09
 *****************************************************************************/
bts_ret_t bts_datetime_settime(f64_t new_servertimestamp)
{
	os_enter_critical();
    os_time_init(new_servertimestamp);
    bts_datetime_update(new_servertimestamp);
    os_exit_critical();
    return retOK;
}


f64_t bts_datetime_settime_from_datetime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec, int32_t nanosec)
{
	// bts_datetime_settime_from_datetime(2020,9,21,22,55,10,10000)
	f64_t servertimestamp;
	struct tm ts;
	ts.tm_year = year-1900;
	ts.tm_mon = month-1;
	ts.tm_mday = day;
	ts.tm_hour = hour;
	ts.tm_min = min;
	ts.tm_sec = sec;

	servertimestamp = bts_datetime_make_timestamp(&ts) + ((f64_t)nanosec/1000000000.0);
	bts_datetime_settime(servertimestamp);
	return servertimestamp;
}

/******************************************************************************
 * function name : bts_datetime_gettime
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 return description
 * \return0 f64_t description
 * modification date : 2020.09.09
 *****************************************************************************/
f64_t bts_datetime_gettime(void)
{
	f64_t timestamp_s;
	timestamp_s = ((f64_t)(os_time_us()) / 1000000.0);
	bts_datetime_update(timestamp_s);
    return timestamp_s;
}



/******************************************************************************
 * function name : bts_datetime_print
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 void description
 * \return0 void description
 * modification date : 2020.09.09
 *****************************************************************************/
void bts_datetime_print(void)
{
    char buff[40];
    bts_datetime_getstr("%Y-%m-%d:%H:%M:%S", buff, sizeof(buff), 1, 1);
    bts_log("System date time is %s\n\r", buff);
}


/******************************************************************************
 * function name : bts_datetime_make_timestamp
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *tptr description
 * \return0 f64_t description
 * modification date : 2020.09.09
 *****************************************************************************/
f64_t bts_datetime_make_timestamp(struct tm *tptr)
{
    time_t t;
    t = mktime(tptr);
    return (f64_t)t;
}


/******************************************************************************
 * function name : *gmtime_r
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *pxTime description
 * \param1 *tmStruct description
 * \return struct tm description
 * modification date : 2019.08.22
 *****************************************************************************/
// struct tm *gmtime_r(const time_t *pxTime, struct tm *tmStruct)
//{
//    /* Dummy time functions to keep the file system happy in the absence of
//    target support. */
//    memcpy(tmStruct, gmtime(pxTime), sizeof(*tmStruct));
//    return tmStruct;
//}


// do #warning _gettimeofday_r is just stubbed out here.
// struct timezone;
// struct timeval;
/******************************************************************************
 * function name : _gettimeofday_r
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *x description
 * \param1 *y description
 * \param2 *ptimezone description
 * \return int description
 * modification date : 2019.08.22
 *****************************************************************************/
// int _gettimeofday_r(struct _reent *x, struct timeval *y, struct timezone *ptimezone)
//{
//    (void)x;
//    (void)y;
//    (void)ptimezone;
//
//    return 0;
//}


/* end of file */
