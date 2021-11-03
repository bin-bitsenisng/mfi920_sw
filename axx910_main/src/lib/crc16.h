/************************************************************************
| Project Name: crc16
|    File Name: crc16.h
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
| 2019.03.26   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef CRC16_H__
#define CRC16_H__

#ifdef __cplusplus
extern "C" {
#endif

/* include system primitive types */
#include "bts.h"


/* module specific types  */


/* define structure for this module */


/* declare extern global variables */

/* declare extern global functions */
extern uint16_t crc16_ccitt(uint8_t *buf, uint32_t len);


#ifdef __cplusplus
}
#endif

#endif // CRC16_H__

