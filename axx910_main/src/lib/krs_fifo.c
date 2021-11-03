/************************************************************************
| Project Name: krs_fifo
|    File Name: krs_fifo.c
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
| 2017.09.25   0.0   SKJ   Creation;
|***********************************************************************/

/* include system primitive types */
#include "bts.h"


/* include system driver header */

/* include system bsp header */
#include "os.h"

/* include system application header */

/* final include module header */
#include "krs_fifo.h"

/* declare static variables */


/* static function prototypes */
void fifo_unit_test(void);

/* functions */

/******************************************************************************
 * function name : fifo_create
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *p description
 * \param1 *buffer description
 * \param2 bytes description
 * \return void description
 * modification date : 2017.09.25
 *****************************************************************************/
void fifo_create(fifo_t *p, uint8_t *buffer, uint32_t bytes)
{
    p->length = bytes;
    p->buffer = buffer;
    p->head = 1;
    p->tail = 0;
}


/******************************************************************************
 * function name : fifo_full
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *p description
 * \return uint8_t description
 * modification date : 2017.09.25
 *****************************************************************************/
uint8_t fifo_full(fifo_t *p)
{
    if(p->head == p->tail)
    {
        return retOK;
    }
    else
    {
        return retFail;
    }
}


/******************************************************************************
 * function name : fifo_empty
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *p description
 * \return uint8_t description
 * modification date : 2017.09.25
 *****************************************************************************/
uint8_t fifo_empty(fifo_t *p)
{
    if(p->head == ((p->tail + 1) % p->length))
    {
        return retOK;
    }
    else
    {
        return retFail;
    }
}


/******************************************************************************
 * function name : fifo_fill
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *q description
 * \param1 *p description
 * \param2 bytes description
 * \return uint32_t description
 * modification date : 2017.09.25
 *****************************************************************************/
uint32_t fifo_fill(fifo_t *q, const void *p, uint32_t bytes)
{
    uint32_t count;
    const uint8_t *ptr = (const uint8_t *)p;

    for(count = 0; count < bytes; count++)
    {
        if(q->head == q->tail)
        {
            break;
        } /* fifo is full ? */
        q->buffer[q->head] = *ptr;
        ptr++;
        q->head = (q->head + 1) % q->length;
    }
    return count;
}


/******************************************************************************
 * function name : fifo_copy
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *q description
 * \param1 bytes description
 * \param2 *p description
 * \return uint32_t description
 * modification date : 2017.09.25
 *****************************************************************************/
uint32_t fifo_copy(void *q, uint32_t bytes, fifo_t *p)
{
    uint32_t count, tail_temp;

    uint8_t *ptr = (uint8_t *)q;
    tail_temp = p->tail;

    for(count = 0; count < bytes; count++)
    {
        if(p->head == ((tail_temp + 1) % p->length))
        {
            break;
        } /* fifo is empty ? */
        tail_temp = (tail_temp + 1) % p->length;
        *ptr = p->buffer[tail_temp];
        ptr++;
    }
    return count;
}


/******************************************************************************
 * function name : fifo_bring
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *q description
 * \param1 bytes description
 * \param2 *p description
 * \return uint32_t description
 * modification date : 2017.09.25
 *****************************************************************************/
uint32_t fifo_bring(void *q, uint32_t bytes, fifo_t *p)
{
    uint32_t count;
    uint8_t *ptr = (uint8_t *)q;

    for(count = 0; count < bytes; count++)
    {
        if(p->head == ((p->tail + 1) % p->length))
        {
            break;
        } /* fifo is empty ? */
        p->tail = (p->tail + 1) % p->length;
        *ptr = p->buffer[p->tail];
        ptr++;
    }
    return count;
}


/******************************************************************************
 * function name : fifo_filled_bytes
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *p description
 * \return uint32_t description
 * modification date : 2017.09.25
 *****************************************************************************/
uint32_t fifo_filled_bytes(fifo_t *p)
{
    if(p->head > p->tail)
    {
        return (p->head - p->tail - 1);
    }
    if(p->head == p->tail)
    {
        return p->length;
    }
    return ((p->head + p->length) - p->tail - 1);
}


/******************************************************************************
 * function name : fifo_unit_test
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
 * modification date : 2017.09.25
 *****************************************************************************/
void fifo_unit_test(void)
{
    uint8_t u8buff[32];
    fifo_t fifo;
    uint32_t temp;
    uint32_t temp1;

    fifo_create(&fifo, u8buff, 32);

    temp = 0x12345678;


    fifo_fill(&fifo, &temp, sizeof(temp));
    fifo_fill(&fifo, &temp, sizeof(temp));
    fifo_fill(&fifo, &temp, sizeof(temp));
    fifo_fill(&fifo, &temp, sizeof(temp));

    fifo_bring(&temp1, sizeof(temp), &fifo);
    fifo_bring(&temp1, sizeof(temp), &fifo);
    fifo_bring(&temp1, sizeof(temp), &fifo);
    fifo_bring(&temp1, sizeof(temp), &fifo);
}

/* end of file */
