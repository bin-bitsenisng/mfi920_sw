/************************************************************************
| Project Name: bts
|    File Name: bts.h
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
| 2020.03.27   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef BTS_H__
#define BTS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* include system primitive types */
#include "krs_basetype.h"
#include "krs_base_return.h"
#include "bts_compilerhal.h"
#include <time.h>
#include <math.h>
#include <sys/time.h>
/* module specific types  */


typedef struct
{
	f64_t sys_timestamp;  //since 1970.01.01
    struct timeval tv;
    struct tm ts;
}bts_datetime_t;

/* define structure for this module */


/* declare extern global variables */

/* declare extern global functions */
extern bts_ret_t bts_init(void);
extern void bts_datetime_init(f64_t sys_timestamp);
bts_ret_t bts_datetime_update(f64_t sys_timestamp);
extern int32_t bts_datetime_getstr(const char *fmt, char *buff, size_t buffsize, uint8_t ms_en, uint8_t us_en);
extern void bts_datetime_print(void);
extern bts_ret_t bts_datetime_settime(f64_t new_servertimestamp);
extern f64_t bts_datetime_settime_from_datetime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec, int32_t nanosec);
extern f64_t bts_datetime_gettime(void);
extern f64_t bts_datetime_make_timestamp(struct tm *tptr);

#ifdef __cplusplus
}
#endif

#endif // BTS_H__
