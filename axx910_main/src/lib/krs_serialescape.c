/************************************************************************
| Project Name: krs_serialescape
|    File Name: krs_serialescape.c
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
/* include system primitive types */
#include "bts.h"

/* include system driver header */


/* include system bsp header */


/* include system application header */


/* final include module header */
#include "krs_serialescape.h"

/* declare global variables */

/* declare static variables */

/* static function prototypes */


/* global functions */
int32_t krs_serialescape(uint8_t fs, uint8_t fe, uint8_t *destbuff, size_t destsize, uint8_t *srcbuff, size_t srcsize)
{
    int32_t i;
    int32_t txindex = 0;

    txindex = 0;

    for(i = 0; i < srcsize; i++)
    {
    	destbuff[txindex++] = srcbuff[i];
        if((srcbuff[i] == fs || srcbuff[i] == fe))
        {
            destbuff[txindex++] = srcbuff[i];
        }

        if(txindex >= destsize)
        {
            krs_log("destbuff size overflow, txindex:%d, destsize:%d\n\r", txindex, destsize);
            return 0;
        }
    }
    return txindex;
}


/* static functions */


//---------------------------------------------------
