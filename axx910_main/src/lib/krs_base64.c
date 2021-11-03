/************************************************************************
| Project Name: krs_base64
|    File Name: krs_base64.c
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

/*
 * Base64 encoding/decoding (RFC1341)
 * Copyright (c) 2005-2011, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 */


/* include system primitive types */
#include "bts.h"


/* include system driver header */

/* include system bsp header */
#include "os.h"

/* include system application header */

/* final include module header */


/* declare static variables */


/* static function prototypes */


/* functions */
#include "krs_base64.h"

static const uint8_t base64_table[65] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
 * base64_encode - Base64 encode
 * @src: Data to be encoded
 * @len: Length of the data to be encoded
 * @out_len: Pointer to output length variable, or %NULL if not used
 * Returns: Allocated buffer of out_len bytes of encoded data,
 * or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer. Returned buffer is
 * nul terminated to make it easier to use as a C string. The nul terminator is
 * not included in out_len.
 */
int32_t krs_base64_encode(uint8_t *src, size_t len, uint8_t *out, size_t outsize)
{
    uint8_t *pos;
    const uint8_t *end, *in;
    size_t olen;
    int line_len;
    int32_t out_len = 0;

    olen = len * 4 / 3 + 4; /* 3-byte blocks to 4-byte */
    olen += olen / 72;      /* line feeds */
    olen++;                 /* nul termination */
    if(olen < len)
        return -1; /* integer overflow */

    if(olen > outsize)
        return -1;

    if(out == NULL)
        return -1;

    end = src + len;
    in = src;
    pos = out;
    line_len = 0;
    while(end - in >= 3)
    {
        *pos++ = base64_table[in[0] >> 2];
        *pos++ = base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
        *pos++ = base64_table[((in[1] & 0x0f) << 2) | (in[2] >> 6)];
        *pos++ = base64_table[in[2] & 0x3f];
        in += 3;
        line_len += 4;
        if(line_len >= 72)
        {
            *pos++ = '\n';
            line_len = 0;
        }
    }

    if(end - in)
    {
        *pos++ = base64_table[in[0] >> 2];
        if(end - in == 1)
        {
            *pos++ = base64_table[(in[0] & 0x03) << 4];
            *pos++ = '=';
        }
        else
        {
            *pos++ = base64_table[((in[0] & 0x03) << 4) |
                                  (in[1] >> 4)];
            *pos++ = base64_table[(in[1] & 0x0f) << 2];
        }
        *pos++ = '=';
        line_len += 4;
    }

    if(line_len)
        *pos++ = '\n';

    *pos = '\0';

    return (pos - out);
}

/**
 * base64_decode - Base64 decode
 * @src: Data to be decoded
 * @len: Length of the data to be decoded
 * @out_len: Pointer to output length variable
 * Returns: Allocated buffer of out_len bytes of decoded data,
 * or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer.
 */
int32_t krs_base64_decode(uint8_t *src, size_t len, uint8_t *out, size_t outsize)
{
    uint8_t dtable[256], *pos, block[4], tmp;
    size_t i, count, olen;
    int pad = 0;

    krs_memset(dtable, 0x80, 256);
    for(i = 0; i < sizeof(base64_table) - 1; i++)
        dtable[base64_table[i]] = (uint8_t)i;
    dtable['='] = 0;

    count = 0;
    for(i = 0; i < len; i++)
    {
        if(dtable[src[i]] != 0x80)
            count++;
    }

    if(count == 0 || count % 4)
        return -1;

    olen = count / 4 * 3;
    if(olen > outsize)
        return -1;

    pos = out;

    if(out == NULL)
        return -1;

    count = 0;
    for(i = 0; i < len; i++)
    {
        tmp = dtable[src[i]];
        if(tmp == 0x80)
            continue;

        if(src[i] == '=')
            pad++;
        block[count] = tmp;
        count++;
        if(count == 4)
        {
            *pos++ = (block[0] << 2) | (block[1] >> 4);
            *pos++ = (block[1] << 4) | (block[2] >> 2);
            *pos++ = (block[2] << 6) | block[3];
            count = 0;
            if(pad)
            {
                if(pad == 1)
                    pos--;
                else if(pad == 2)
                    pos -= 2;
                else
                {
                    /* Invalid padding */
                    return -1;
                }
                break;
            }
        }
    }

    return (pos - out);
}
/* end of file */
