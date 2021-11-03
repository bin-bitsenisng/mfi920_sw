/************************************************************************
| Project Name: can_sig
|    File Name: can_sig.c
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
#include "can_sig.h"
#include "can_sig_cfg.h"

/* declare global variables */


can_sig_data_t can_sig_data;

/* declare static variables */

/* static function prototypes */


/* global functions */
/******************************************************************************
 * function name : can_sig_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 void description
 * \return0 void description
 * modification date : 2020.03.27
 *****************************************************************************/
void can_sig_init(void) {}


/******************************************************************************
 * function name : can_sig_osinit
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 void description
 * \return0 void description
 * modification date : 2020.03.27
 *****************************************************************************/
void can_sig_osinit(void) { krs_memclearitem(can_sig_data); }


/******************************************************************************
 * function name : can_sig_getsignal
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *srcbuff description
 * \param1 *destdata description
 * \param2 *siginfo description
 * \return int32_t description
 * modification date : 2019.04.03
 *****************************************************************************/
int32_t can_sig_getsignal(uint8_t *srcbuff, f32_t *destdata, sys_param_cansignal_t *siginfo)
{
    uint32_t u32data = 0;
    int32_t s32data = 0;
    f32_t f32data = 0.0f;
    can_drv_com_sigendian_t endian;

    if(siginfo->byteorder == 'M')
    {
        endian = can_drv_com_sigendian_big;
    }
    else
    {
        endian = can_drv_com_sigendian_little;
    }
    if(can_sig_getsignal_raw(srcbuff, &u32data, endian, (int16_t)siginfo->bitpos,
                             (uint8_t)siginfo->length) == retOK)
    {
        if(siginfo->type == 'U')
        {
            f32data = ((f32_t)u32data) * siginfo->factor + siginfo->offset;
        }
        else
        {
            s32data = ((int32_t)(u32data << (32 - siginfo->length))) >> siginfo->length;
            f32data = ((f32_t)s32data) * siginfo->factor + siginfo->offset;
        }
        *destdata = krs_bound(siginfo->min, f32data, siginfo->max);
        return retOK;
    }
    else
    {
        krs_log("get signal fail\n\r");
        *destdata = 0.0f;
    }
    return retFail;
}


/******************************************************************************
 * function name : can_sig_getsignal_raw
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *srcBuf description
 * \param1 *dstData description
 * \param2 endian description
 * \param3 startBit description
 * \param4 bitSize description
 * \return int32_t description
 * modification date : 2019.04.03
 *****************************************************************************/
int32_t can_sig_getsignal_raw(uint8_t *srcBuf, uint32_t *dstData, can_drv_com_sigendian_t endian,
                              int16_t startBit, uint8_t bitSize)
{
    int16_t idx, idxStep;
    uint8_t bitPosition, remainingBits, processedBits, bitMask, unpacked_byte;
    uint32_t resData = 0;

    idx = startBit / 8;
    bitPosition = startBit % 8;
    remainingBits = bitSize;
    if(endian == can_drv_com_sigendian_little)
    {
        idxStep = 1;
    }
    else if(endian == can_drv_com_sigendian_big)
    {
        idxStep = -1;
    }
    else
    {
        idxStep = 0;
        krs_log("CAN:unknown signal endian\n\r");
        return retFail;
    }

    /* Extract signal from source buffer */
    do
    {
        if(remainingBits >= (8 - bitPosition))
        {
            processedBits = bitSize - remainingBits;
            unpacked_byte = srcBuf[idx] >> bitPosition;
            resData |= ((uint32_t)unpacked_byte) << processedBits;
            remainingBits -= (8 - bitPosition);
            idx += idxStep;
            bitPosition = 0;
        }
        else
        {
            bitMask = (0xff >> (8 - remainingBits)) << bitPosition;
            processedBits = bitSize - remainingBits;
            unpacked_byte = (srcBuf[idx] & bitMask) >> bitPosition;
            resData |= ((uint32_t)unpacked_byte) << processedBits;
            remainingBits = 0;
        }
    } while(remainingBits > 0);
    *dstData = resData;

    return retOK;
}


/* static functions */


//---------------------------------------------------
