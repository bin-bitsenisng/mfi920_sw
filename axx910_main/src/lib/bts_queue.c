/************************************************************************
| Project Name: bts_queue
|    File Name: bts_queue.c
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
/* include system primitive types */
#include "bts.h"

/* include system driver header */
#include "os.h"

/* include system bsp header */


/* include system application header */


/* final include module header */
#include "bts_queue.h"


/* declare global variables */

/* declare static variables */

uint32_t bts_queue_get_buffpoolindex(bts_queue_t *inst);


#if BTS_QUEUE_UNITTEST == 1
#include "taskmgr.h"
#define POOLSIZE 1024
#define POOLDEPTH 128
uint8_t quepoolbuff[POOLDEPTH][POOLSIZE] KRS_ALIGN(32);
bts_queue_t queuetest;
uint8_t testputbuff[4096];
uint8_t testgetbuff[4096];
void bts_queue_unittest_producer_task(void *param);
void bts_queue_unittest_consumer_task(void *param);
void bts_queue_unittest(void)
{
	int32_t i;
	uint32_t sendsizelist[7]={512,1024,1100,2000,3000,4000,4096};

	krs_log("init bts_queue\n\r");
    bts_queue_init(&queuetest, (uint8_t*)quepoolbuff, POOLSIZE, POOLDEPTH);

    krs_log("create unittest task\n\r");

    for(i = 0; i < 4096; i++)
    {
        testputbuff[i] = (uint8_t)i;
    }


    xTaskCreate( bts_queue_unittest_consumer_task,				/* The function that implements the task. */
    				"consumer", 								/* The text name assigned to the task - for debug only as it is not used by the kernel. */
    				TASKMGR_SCHD_TASK_STACKSIZE, 			/* The size of the stack to allocate to the task. */
    				NULL, 								/* The parameter passed to the task - not used in this case. */
    				3, 	/* The priority assigned to the task. */
    				NULL );


    for(i=0;i<7;i++)
    {
		xTaskCreate( bts_queue_unittest_producer_task,				/* The function that implements the task. */
						"producer", 								/* The text name assigned to the task - for debug only as it is not used by the kernel. */
						TASKMGR_SCHD_TASK_STACKSIZE, 			/* The size of the stack to allocate to the task. */
						sendsizelist[i], 								/* The parameter passed to the task - not used in this case. */
						2, 	/* The priority assigned to the task. */
						NULL );
    }
    while(1)
    {
    	os_sleep(1000);
    }
}

void bts_queue_unittest_producer_task(void *param)
{
	uint32_t size=0;
	size = (uint32_t)param;
	krs_log("bts_queue_unittest_producer_task send size %d start\n\r", size);
	for(;;)
	{
		bts_queue_put(&queuetest, &testputbuff[0], size, 1000);   // 1, 50
	}
}



void bts_queue_unittest_consumer_task(void *param)
{
    int32_t len;
    int32_t i;
	krs_log("bts_queue_unittest_consumer_task start\n\r");
	for(;;)
	{
		krs_memclear(testgetbuff);
		len = bts_queue_get(&queuetest, testgetbuff, sizeof(testgetbuff), os_max_delay);
		if(len)
		{
			krs_log("que get idx:%3d, len:%4d\n\r",bts_queue_get_buffpoolindex(&queuetest), len);
			//krs_log_arruint8X(testgetbuff, len);
		}
		else
		{
			krs_log("que empty or timeout\n\r");
		}
	}
}


#endif
/* static function prototypes */


/* global functions */
/******************************************************************************
 * function name : bts_queue_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *inst description
 * \param1 *buffpool description
 * \param2 poolsize description
 * \param3 poolcount description
 * \return int32_t description
 * modification date : 2019.07.02
 *****************************************************************************/
int32_t bts_queue_init(bts_queue_t *inst, uint8_t *buffpool, uint32_t poolsize, uint32_t poolcount)
{
    krs_memset(inst, 0x00, sizeof(bts_queue_t));
    // create buff pool
    if(poolsize % 4 != 0)
    {
        krs_log("que buffpool not aligned 4\n\r");
        return retFail;
    }
    inst->buffpool = buffpool;
    inst->poolcount= poolcount;
    inst->poolindex=0;
    inst->incount = 0;
    inst->outcount = 0;
    inst->poolsize = poolsize;
    inst->buffpoolsize=poolsize*poolcount;
    //os_queue_create(inst->que, poolcount, sizeof(queue_item_t));
    InitQueue(&inst->que, poolcount);
    bts_queue_reset(inst);
    return retOK;
}


/******************************************************************************
 * function name : bts_queue_reset
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *inst description
 * \return int32_t description
 * modification date : 2019.07.02
 *****************************************************************************/
void bts_queue_reset(bts_queue_t *inst)
{
	os_enter_critical();
    inst->poolindex = 0;
    inst->incount = 0;
    inst->outcount = 0;
    os_exit_critical();
    //os_queue_reset(inst->que);
    ResetQueue(&inst->que);
}

/******************************************************************************
 * function name : bts_queue_put
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *inst description
 * \param1 *srcbuff description
 * \param2 size description
 * \param3 timeout description
 * \return int32_t description
 * modification date : 2019.07.02
 *****************************************************************************/
int32_t bts_queue_put(bts_queue_t *inst, uint8_t *srcbuff, size_t size, uint32_t timeout)
{
    int32_t remain_poolcount = 0;
    int32_t need_poolcount = 0;
    uint32_t current_poolindex=0;
    queue_item_t item;
    // get current buffer address

    krs_memclearitem(item);

    remain_poolcount = inst->poolcount - GetQueueSize(&inst->que);//os_queue_len(inst->que);

    os_enter_critical();
		if(size % inst->poolsize == 0)
		{
			need_poolcount = size / inst->poolsize;
		}
		else
		{
			need_poolcount = (size / inst->poolsize) + 1;
		}

		// check poolindex linearity
		if((inst->poolindex + need_poolcount) > inst->poolcount)
		{
			//krs_log("buffpool index rewind for linear space\n\r");
			//krs_log("old remain_poolcount is %d\n\r",remain_poolcount);
			remain_poolcount -= ((inst->poolindex + need_poolcount) - inst->poolcount);
			inst->poolindex = 0;
			//krs_log("new remain_poolcount is %d\n\r",remain_poolcount);
		}
		current_poolindex = inst->poolindex;

		// poolindex update for multiple input
		inst->poolindex = (inst->poolindex + need_poolcount) % inst->poolcount;
	os_exit_critical();

    // copy
    if(remain_poolcount > need_poolcount)
    {
        item.buffptr = &inst->buffpool[current_poolindex * inst->poolsize];
        item.size = size;
        krs_memcopy(item.buffptr, srcbuff, size);
        // update queue
        //if(os_queue_give(inst->que, &item, timeout) == os_retOK)
        if(PutQueue(&inst->que, &item) == os_retOK)
        {
            os_enter_critical();
            inst->totalsize += size;
            //inst->poolindex = (inst->poolindex + need_poolcount) % inst->poolcount;
            inst->incount += need_poolcount;
            os_exit_critical();
            return retOK;
        }
        else
        {
            //krs_log("que is timeout\n\r");
        }
    }
    else
    {
        //krs_log("que is full\n\r");
    }
    return retFail;
}

/******************************************************************************
 * function name : bts_queue_get
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *inst description
 * \param1 *desbuff description
 * \param2 size description
 * \param3 timeout description
 * \return int32_t description
 * modification date : 2019.07.02
 *****************************************************************************/
int32_t bts_queue_get(bts_queue_t *inst, uint8_t *desbuff, size_t size, uint32_t timeout)
{
	int32_t ret=0;
	queue_item_t item;
    if(bts_queue_peek(inst, &item, timeout) == retOK)
    {
    	if(item.size > size)
    	{
    		krs_log("destbuff size is too short\n\r");
    		ret = 0;
    	}
    	else
    	{
    		ret = item.size;
    		krs_memcopy(desbuff, item.buffptr, item.size);
    		bts_queue_remove(inst);
    	}
    }
    else
    {
    	ret = 0;
    }
    return ret;
}

/******************************************************************************
 * function name : bts_queue_peek
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *inst description
 * \param1 *itemptr description
 * \param2 timeout description
 * \return int32_t description
 * modification date : 2019.07.02
 *****************************************************************************/
int32_t bts_queue_peek(bts_queue_t *inst, queue_item_t *itemptr, uint32_t timeout)
{
    //if(os_queue_peek(inst->que, itemptr, timeout) == os_retOK)
    if(PeekQueue(&inst->que, itemptr) == os_retOK)
    {
        return retOK;
    }
    return retFail;
}


/******************************************************************************
 * function name : bts_queue_remove
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *inst description
 * \return int32_t description
 * modification date : 2019.07.02
 *****************************************************************************/
int32_t bts_queue_remove(bts_queue_t *inst)
{
    queue_item_t item;
    //if(os_queue_take(inst->que, &item, 0) == os_retOK)
    if(GetQueue(&inst->que, &item) == os_retOK)
    {
    	os_enter_critical();
        inst->totalsize -= item.size;
        if((item.size % inst->poolsize)==0)
        {
        	inst->outcount += ((item.size / inst->poolsize));
        }
        else
        {
        	inst->outcount += ((item.size / inst->poolsize) + 1);
        }
        os_exit_critical();
        return retOK;
    }
    return retFail;
}


/******************************************************************************
 * function name : bts_queue_len
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *inst description
 * \return int32_t description
 * modification date : 2019.07.02
 *****************************************************************************/
int32_t bts_queue_len(bts_queue_t *inst)
{
    //return os_queue_len(inst->que);
    return GetQueueSize(&inst->que);
}





/******************************************************************************
 * function name : bts_queue_size
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *inst description
 * \return int32_t description
 * modification date : 2019.07.02
 *****************************************************************************/
int32_t bts_queue_size(bts_queue_t *inst)
{
    return inst->totalsize;
}


/* static functions */
/******************************************************************************
 * function name : bts_queue_get_buffpoolindex
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *inst description
 * \return int32_t description
 * modification date : 2019.07.02
 *****************************************************************************/
uint32_t bts_queue_get_buffpoolindex(bts_queue_t *inst)
{
	uint32_t idx;
	os_enter_critical();
	idx = inst->poolindex;
	os_exit_critical();
	return idx;
}

//---------------------------------------------------
