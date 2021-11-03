/************************************************************************
| Project Name: krs_serialescape
|    File Name: krs_serialescape.h
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
| 2019.04.03   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef KRS_SERIALESCAPE_H__
#define KRS_SERIALESCAPE_H__

#ifdef __cplusplus
extern "C" {
#endif

/* include system primitive types */
#include "bts.h"


/* module specific types  */


/* define structure for this module */


/* declare extern global variables */

/* declare extern global functions */
extern int32_t krs_serialescape(uint8_t fs, uint8_t fe, uint8_t *destbuff, size_t destsize, uint8_t *srcbuff, size_t srcsize);


#ifdef __cplusplus
}
#endif

#endif // KRS_SERIALESCAPE_H__
