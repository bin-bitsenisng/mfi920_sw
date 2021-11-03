/************************************************************************
 | Project Name: KRS24
 |    File Name: os.c
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

/* include system primitive types */
#include "bts.h"
#include "os_cfg.h"

/* include system driver header */


/* include system bsp header */
#if !defined(WIN32) && !defined(LINUX)
#include "xil_cache.h"
#include "xil_exception.h"
#include "xil_mmu.h"
#include "xparameters.h"
#include "xscugic.h"
#include "xstatus.h"
#include "xtime_l.h"
#include "xttcps.h"
#endif
/* include system application header */
#include "timestamp.h"

/* final include module header */
//#include "drivers.h"
#include "network.h"
#include "os.h"
#include "sys/time.h"

/* declare global variables */
os_time_t os_time_start = 0;
/* declare static variables */
//static SemaphoreHandle_t sem_os_usleep_complete[XPAR_XTTCPS_NUM_INSTANCES] = {NULL};
// static SemaphoreHandle_t sem_os_usleep_ttc_resource = NULL;
// traceLabel xTickTraceUserEvent;
//portBASE_TYPE xTraceRunning = pdTRUE;

/* static function prototypes */
//BaseType_t os_usleep_expired_handler(void *CallBackRef);


/* functions */

/******************************************************************************
 * function name : os_preinit
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 void description
 * \return0 int32_t description
 * modification date : 2020.09.09
 *****************************************************************************/
int32_t os_preinit(void)
{
    uint32_t i;
    /* module init code here*/
    system_init();

    network_init();


    // sem_os_usleep_ttc_resource = xSemaphoreCreateCounting(TTC_DRV_MAX_CHANNEL, 0);
    /*for(i = 0; i < XPAR_XTTCPS_NUM_INSTANCES; i++)
    {
        sem_os_usleep_complete[i] = xSemaphoreCreateBinary();
    }
    Xil_DCacheEnable();
    return retOK;*/
}


/******************************************************************************
 * function name : os_time_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 starttimestamp description
 * \return0 void description
 * modification date : 2020.09.09
 *****************************************************************************/
void os_time_init(f64_t starttimestamp)
{

    //XTime_SetTime((uint64_t)(starttimestamp * TIMER_DRV_COUNTS_PER_SECOND_F));
}



/******************************************************************************
 * function name : os_uswait
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 timer_drv_usleep description
 * \return0 void description
 * modification date : 2020.09.09
 *****************************************************************************/
void os_uswait(uint32_t waitus)
{
    //timer_drv_usleep(waitus);
    usleep(waitus);
}



/******************************************************************************
 * function name : os_sleep
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 delayms description
 * \return0 void description
 * modification date : 2020.09.09
 *****************************************************************************/
void os_sleep(uint32_t delayms)
{
    // vTaskDelayUntil( &xoswaketime, delayms ); // 50ms blocking
    /*if(os_is_running() == os_retOK)
    {
        vTaskDelay(delayms);
    }
    else
    {
        os_uswait(delayms * 1000);
    }*/
    usleep(delayms*1000);
}



/******************************************************************************
 * function name : os_time_us
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 void description
 * \return0 os_time_t description
 * modification date : 2020.09.09
 *****************************************************************************/
os_time_t os_time_us(void)
{
#ifndef WIN32
    /*XTime tCurrent;
    XTime_GetTime(&tCurrent);
    return ((os_time_t)(TIMER_DRV_COUNTS_TO_USECOND_U64(tCurrent)));*/
    /*struct timeval curr_time;
    gettimeofday(&curr_time, NULL);
    return curr_time.tv_usec + curr_time.tv_sec*1000000;*/
    return GetTimeStamp();
#else
    return timer_drv_gettime_us();
#endif
}

/******************************************************************************
 * function name : os_timeout_reset
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *currtime description
 * \return0 int32_t description
 * modification date : 2020.09.09
 *****************************************************************************/
int32_t os_timeout_reset(os_time_t *currtime)
{
    os_time_t ctime;

    ctime = os_time_us();
    os_enter_critical();
    *currtime = ctime;
    os_exit_critical();
    return retOK;
}

/******************************************************************************
 * function name : os_timeout_expired
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *currtime description
 * \param1 timeoutus description
 * \return0 int32_t description
 * modification date : 2020.09.09
 *****************************************************************************/
int32_t os_timeout_expired(os_time_t *currtime, os_time_t timeoutus)
{
    os_time_t ctime;

    os_enter_critical();
    ctime = *currtime;
    os_exit_critical();

    if((os_time_us() - ctime) > timeoutus)
        return retOK;
    else
        return retFail;
}


/******************************************************************************
 * function name : os_timeout_ms_reset
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *currtime_ms description
 * \return0 int32_t description
 * modification date : 2020.09.09
 *****************************************************************************/
int32_t os_timeout_ms_reset(os_time_ms_t *currtime_ms)
{
    *currtime_ms = os_time_ms();
    return retOK;
}

/******************************************************************************
 * function name : os_timeout_ms_expired
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *currtime_ms description
 * \param1 timeout_ms description
 * \return0 int32_t description
 * modification date : 2020.09.09
 *****************************************************************************/
int32_t os_timeout_ms_expired(os_time_ms_t *currtime_ms, os_time_ms_t timeout_ms)
{
    if(os_time_ms() - *currtime_ms > timeout_ms)
        return retOK;
    else
        return retFail;
}



/******************************************************************************
 * function name : os_usleep
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 delayus description
 * \return0 void description
 * modification date : 2020.09.09
 *****************************************************************************/
void os_usleep(uint32_t delayus)
{
/*    ttc_drv_channel_t channel;

    // current_task_handle is used for identifier

    channel = ttc_drv_get_free_channel();


    // 1. init usleep complete semaphore

    // 2. ttc setup

    ttc_drv_setup_timer(channel, delayus, os_usleep_expired_handler,
                        sem_os_usleep_complete[channel]);

    ttc_drv_start_timer(channel);
    // 3. get usleep complete semaphore
    xSemaphoreTake(sem_os_usleep_complete[channel], portMAX_DELAY);
*/
    usleep(delayus);

    // 4. set default ttc config.
}


/******************************************************************************
 * function name : os_usleep_expired_handler
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *CallBackRef description
 * \return0 BaseType_t description
 * modification date : 2020.09.09
 *****************************************************************************/
/*BaseType_t os_usleep_expired_handler(void *CallBackRef)
{
    ttc_drv_instance_t *ttc_drv_instance_ptr;
    static BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;
    // find channel using task handle
    ttc_drv_instance_ptr = (ttc_drv_instance_t *)CallBackRef;
    xSemaphoreGiveFromISR(ttc_drv_instance_ptr->sem_complete, &xHigherPriorityTaskWoken);
    return (xHigherPriorityTaskWoken);
}*/

/******************************************************************************
 * function name : os_dcache_invalidate
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 addr description
 * \param1 Xil_DCacheInvalidateRange description
 * \return0 void description
 * modification date : 2020.09.09
 *****************************************************************************/
void os_dcache_invalidate(uint32_t addr, size_t size)
{
//    Xil_DCacheInvalidateRange(addr, size);
}


/******************************************************************************
 * function name : os_set_uncached_memory
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 addr description
 * \param1 size description
 * \return0 int32_t description
 * modification date : 2020.09.09
 *****************************************************************************/
int32_t os_set_uncached_memory(uint32_t addr, size_t size)
{/*
    uint32_t i;
    if(addr % (1024 * 1024))
    {
        krs_log("addr must be 1MB align\n\r");
        return retFail;
    }
    if(size % (1024 * 1024))
    {
        krs_log("size must be 1MB align\n\r");
        return retFail;
    }

    for(i = 0; i < size / (1024 * 1024); i++)
    {
        Xil_SetTlbAttributes((uint32_t)(addr + (i * (1024 * 1024))), 0x1c02); // addr, attr
    }
    return retOK;*/
}


/* end of file */
