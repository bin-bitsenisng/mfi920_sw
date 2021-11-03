/************************************************************************
| Project Name: krs_fifo
|    File Name: krs_fifo.h
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
#ifndef KRS_FIFO_H__
#define KRS_FIFO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "bts.h"

/******************************************************************************
global data types and structures
******************************************************************************/

typedef struct
{
    uint32_t length;
    uint8_t *buffer;
    uint32_t head;
    uint32_t tail;
} fifo_t;


/******************************************************************************
prototypes of export functions
******************************************************************************/
extern void fifo_create(fifo_t *p, uint8_t *buffer, uint32_t bytes);
extern uint8_t fifo_full(fifo_t *p);
extern uint8_t fifo_empty(fifo_t *p);
extern uint32_t fifo_filled_bytes(fifo_t *p);
extern uint32_t fifo_fill(fifo_t *q, const void *p, uint32_t bytes);
extern uint32_t fifo_copy(void *q, uint32_t bytes, fifo_t *p);
extern uint32_t fifo_bring(void *q, uint32_t bytes, fifo_t *p);

#define fifo_init(fifoinst, buffer) fifo_create(&(fifoinst), (uint8_t*)(buffer), sizeof(buffer))

#ifdef __cplusplus
}
#endif
#endif // KRS_FIFO_H__
/******************************************************************************
End of File
******************************************************************************/