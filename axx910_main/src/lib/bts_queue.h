/************************************************************************
| Project Name: bts_queue
|    File Name: bts_queue.h
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
| 2019.07.02   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef BTS_QUEUE_H__
#define BTS_QUEUE_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* include system primitive types */
#include "bts.h"
#include "os.h"
#include "linked_queue.h"

    /* module specific types  */
#define BTS_QUEUE_UNITTEST 0

    /* define structure for this module */
    typedef struct
    {
        uint8_t *buffpool;
        uint32_t poolsize;
        uint32_t poolcount;
        uint32_t incount;
        uint32_t outcount;
        uint32_t buffpoolsize;
        uint32_t poolindex;
        uint32_t totalsize;
        //os_queue_t que;
        LINKED_QUEUE que;
        os_sem_t sem_lock;
    } bts_queue_t;

    /* declare extern global variables */

    /* declare extern global functions */
    extern int32_t bts_queue_init(bts_queue_t *inst, uint8_t *buffpool, uint32_t poolsize, uint32_t poolcount);
    extern void bts_queue_reset(bts_queue_t *inst);
    extern int32_t bts_queue_put(bts_queue_t *inst, uint8_t *srcbuff, size_t size, uint32_t timeout);
    extern int32_t bts_queue_get(bts_queue_t *inst, uint8_t *desbuff, size_t size, uint32_t timeout);
    extern int32_t bts_queue_peek(bts_queue_t *inst, queue_item_t *itemptr, uint32_t timeout);
    extern int32_t bts_queue_remove(bts_queue_t *inst);
    extern int32_t bts_queue_len(bts_queue_t *inst);
    extern int32_t bts_queue_size(bts_queue_t *inst);

#if BTS_QUEUE_UNITTEST == 1
    extern void bts_queue_unittest(void);
#endif

#ifdef __cplusplus
}
#endif

#endif // BTS_QUEUE_H__
