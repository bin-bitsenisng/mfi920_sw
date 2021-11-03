/************************************************************************
 | Project Name: KRS24
 |    File Name: krs_basetype.h
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
 | 2014.12.02   0.0   SKJ   Creation;
 |***********************************************************************/

#ifndef KRS_BASETYPE_H__
#define KRS_BASETYPE_H__


#ifdef __cplusplus
extern "C" {
#endif

/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include <stdint.h>

#if defined(WIN32) || defined(LINUX)
#include <stdio.h>
#else
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;
#endif
typedef char char_t;
typedef unsigned char bool_t;


typedef float f32_t;
typedef double f64_t;


/* module specific types  */
typedef union union16{
  uint16_t  W;
  uint8_t   B[2];
}union16_t;


typedef union union32{
  uint32_t  L;
  uint16_t  W[2];
  uint8_t   B[4];
}union32_t;

typedef union union64{
  uint64_t  Q;
  uint32_t	L[2];
  uint16_t	W[4];
  uint8_t	B[8];
  int64_t  sQ;
  int32_t	sL[2];
  int16_t	sW[4];
  int8_t	sB[8];
}union64_t;

typedef union
{
    uint8_t R;
    struct
    {
        uint8_t bit0	:1;
        uint8_t bit1	:1;
        uint8_t bit2	:1;
        uint8_t bit3	:1;
        uint8_t bit4	:1;
        uint8_t bit5	:1;
        uint8_t bit6	:1;
        uint8_t bit7	:1;
    }B;
}ubit8_t;


typedef union
{
    uint16_t R;
    struct
    {
        uint8_t bit0	:1;
        uint8_t bit1	:1;
        uint8_t bit2	:1;
        uint8_t bit3	:1;
        uint8_t bit4	:1;
        uint8_t bit5	:1;
        uint8_t bit6	:1;
        uint8_t bit7	:1;

        uint8_t bit8	:1;
        uint8_t bit9	:1;
        uint8_t bit10	:1;
        uint8_t bit11	:1;
        uint8_t bit12	:1;
        uint8_t bit13	:1;
        uint8_t bit14	:1;
        uint8_t bit15	:1;
    }B;
}ubit16_t;




typedef union
{
    uint32_t R;
    struct
    {
        uint32_t bit0	:1;
        uint32_t bit1	:1;
        uint32_t bit2	:1;
        uint32_t bit3	:1;
        uint32_t bit4	:1;
        uint32_t bit5	:1;
        uint32_t bit6	:1;
        uint32_t bit7	:1;

        uint32_t bit8	:1;
        uint32_t bit9	:1;
        uint32_t bit10	:1;
        uint32_t bit11	:1;
        uint32_t bit12	:1;
        uint32_t bit13	:1;
        uint32_t bit14	:1;
        uint32_t bit15	:1;

        uint32_t bit16	:1;
        uint32_t bit17	:1;
        uint32_t bit18	:1;
        uint32_t bit19	:1;
        uint32_t bit20	:1;
        uint32_t bit21	:1;
        uint32_t bit22	:1;
        uint32_t bit23	:1;

        uint32_t bit24	:1;
        uint32_t bit25	:1;
        uint32_t bit26	:1;
        uint32_t bit27	:1;
        uint32_t bit28	:1;
        uint32_t bit29	:1;
        uint32_t bit30	:1;
        uint32_t bit31	:1;
    }B;
}ubit32_t;



/* define structure for this module */
//#ifndef WIN32
#include "krs_macro.h"
//#endif
/* declare extern global variables */


/* declare extern global functions */


#ifdef __cplusplus
}
#endif

#endif /* KRS_BASETYPE_H__ */
