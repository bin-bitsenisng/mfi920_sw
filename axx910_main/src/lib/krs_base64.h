/************************************************************************
| Project Name: krs_base64
|    File Name: krs_base64.h
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
| 2019.03.08   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef KRS_BASE64_H__
#define KRS_BASE64_H__

#ifdef __cplusplus
extern "C" {
#endif

/* include system primitive types */
#include "bts.h"


/* module specific types  */


/* define structure for this module */


/* declare extern global variables */

/* declare extern global functions */
extern int32_t krs_base64_encode(uint8_t *src, size_t len, uint8_t *out, size_t outsize);
extern int32_t krs_base64_decode(uint8_t *src, size_t len, uint8_t *out, size_t outsize);


#ifdef __cplusplus
}
#endif

#endif // KRS_BASE64_H__
