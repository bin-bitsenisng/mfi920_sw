/************************************************************************
 | Project Name: KRS24
 |    File Name: os.h
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

#ifndef OS_H__
#define OS_H__


#ifdef __cplusplus
extern "C" {
#endif

/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "os_cfg.h"
#include "semaphore.h"
#include "linked_queue.h"

// Datatype
#include <time.h>
typedef uint64_t os_time_t;
typedef uint32_t os_time_ms_t;

typedef struct linked_queue LINKED_QUEUE;

/* Kernel includes. */
#ifndef WIN32
/*
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "queue.h"
#include "stream_buffer.h"
#include "message_buffer.h"*/


/*Kernel config include*/
//#include "FreeRTOSConfig.h"
/* module specific types  */

//#include "le_trace.h"

#ifdef LINUX // temporal method
#define TickType_t uint32_t
#define err_t int8_t
#define vTaskDelay(delay) usleep((delay)*1000)
#endif

#ifdef LINUX
#define os_enter_critical()
#define os_exit_critical()
#define os_safe_assign(d,s) d=(s);
#define os_safe(statement) statement


#define os_retOK    0
#define os_retFail  1

#define os_True     1
#define os_False	0


#define os_malloc	malloc
#define os_free		free

#define os_max_delay 0xffffffffUL

#define os_start_isr()
#define os_end_isr()
#define os_interrupt_disable()
#define os_interrupt_enable()
#else
#define os_enter_critical() taskENTER_CRITICAL()
#define os_exit_critical()	taskEXIT_CRITICAL()
#define os_safe_assign(d,s)  os_enter_critical(); d=(s); os_exit_critical()
#define os_safe(statement) os_enter_critical(); statement os_exit_critical()


#define os_retOK pdPASS
#define os_retFail pdFAIL

#define os_True 	pdTRUE
#define os_False	 pdFALSE



#define os_malloc	pvPortMalloc
#define os_free		vPortFree

#define os_max_delay portMAX_DELAY

#define os_start_isr() BaseType_t xHigherPriorityTaskWoken; xHigherPriorityTaskWoken = pdFALSE
#define os_end_isr() if(xHigherPriorityTaskWoken) portYIELD_FROM_ISR(xHigherPriorityTaskWoken)
#define os_interrupt_disable() taskDISABLE_INTERRUPTS()
#define os_interrupt_enable() taskENABLE_INTERRUPTS()
#endif



/* semaphore */
#define os_sem_t	sem_t
#define os_sem_init(sem) sem_init(&sem, 0, 1)
#define os_sem_give(sem) sem_post(&(sem))
//#define os_sem_give_recursive(sem) xSemaphoreTakeRecursive((sem))
//#define os_sem_give_isr(sem) xSemaphoreGiveFromISR((sem), (&xHigherPriorityTaskWoken))
#define os_sem_take(sem, timeout)   sem_timedwait(&(sem), &timeout) 
//#define os_sem_take_isr(sem) xSemaphoreTakeFromISR((sem), (&xHigherPriorityTaskWoken))
//#define os_sem_take_recursive(sem, timeout) xSemaphoreTakeRecursive((sem), (timeout))

//
#define os_is_running() os_retOK
//#define os_suspendall() vTaskSuspendAll()
//#define os_resumeall() xTaskResumeAll()

/* message queue */
/*
#define os_queue_t QueueHandle_t
#define os_queue_create(handle, qdepth, elementsize) handle=xQueueCreate(qdepth, elementsize)
#define os_queue_reset(hnd) xQueueReset(hnd)
#define os_queue_give(hnd, ptr, timeout) xQueueSendToBack(hnd, ptr, timeout)
#define os_queue_take(hnd, ptr, timeout) xQueueReceive(hnd, ptr, timeout)
#define os_queue_give_isr(handle, ptr) xQueueSendToBackFromISR(handle, ptr, &xHigherPriorityTaskWoken)
#define os_queue_take_isr(handle, ptr) xQueueReceiveFromISR(handle, ptr, &xHigherPriorityTaskWoken)
#define os_queue_peek(hnd, ptr, timeout) xQueuePeek(hnd, ptr, timeout)
#define os_queue_peek_isr(hnd, ptr) xQueuePeekFromISR(hnd, ptr, &xHigherPriorityTaskWoken)
#define os_queue_len(hnd) uxQueueMessagesWaiting(hnd)
*/
/*
#define os_queue_t LINKED_QUEUE //QueueHandle_t
#define os_queue_create(hnd, qdepth, elementsize) InitQueue(&hnd, qdepth) //handle=xQueueCreate(qdepth, elementsize)
#define os_queue_reset(hnd) ResetQueue(&hnd) //xQueueReset(hnd)
#define os_queue_give(hnd, ptr, timeout) PutQueue(&hnd, &ptr) //xQueueSendToBack(hnd, ptr, timeout)
#define os_queue_take(hnd, ptr, timeout) GetQueue(&hnd, &ptr) //xQueueReceive(hnd, ptr, timeout)
#define os_queue_peek(hnd, ptr, timeout) PeekQueue(&hnd, &ptr) //xQueuePeek(hnd, ptr, timeout)
#define os_queue_len(hnd) GetQueueSize(&hnd) //uxQueueMessagesWaiting(hnd)
*/

/* define structure for this module */
/* task handle */
#define os_task_t //TaskHandle_t
#define os_task_create //xTaskCreate
#define os_task_suspendall() //vTaskSuspendAll()
#define os_task_resumeall() //xTaskResumeAll()
#define os_tasknoti_set(handle, lvalue) //xTaskNotify((handle),(lvalue),eSetBits)
#define os_tasknoti_overwrite(handle, lvalue) //xTaskNotify((handle),(lvalue),eSetValueWithOverwrite)

#define os_tasknoti_wait //xTaskNotifyWait
#define os_tasknoti_give(taskhandle) //xTaskNotifyGive(taskhandle)
#define os_tasknoti_init(taskhandle) //taskhandle = xTaskGetCurrentTaskHandle()
#define os_tasknoti_take(timeout)  //ulTaskNotifyTake(pdTRUE, (timeout))
#define os_tasknoti_start_isr(taskhandle) //static BaseType_t xHigherPriorityTaskWoken; xHigherPriorityTaskWoken = pdFALSE; krs_assert(taskhandle!=NULL)
#define os_tasknoti_end_isr(taskhandle) //vTaskNotifyGiveFromISR( taskhandle, &xHigherPriorityTaskWoken ); /*taskhandle = NULL;*/ portYIELD_FROM_ISR(xHigherPriorityTaskWoken)

/*
#define os_task_status_t TaskStatus_t
#define os_task_getcurrenthnd() xTaskGetCurrentTaskHandle()
#define os_task_getinfo(hnd, taskstatus) vTaskGetInfo(hnd, &taskstatus, pdFALSE, eInvalid)
*/
/*
#define os_msgbuff_t MessageBufferHandle_t
#define os_msgbuff_create(hnd, buffsize) hnd = xMessageBufferCreate(buffsize)
#define os_msgbuff_write(hnd, buff, size, timeout) xMessageBufferSend(hnd, buff, size, timeout)
#define os_msgbuff_write_isr(hnd, buff, size) xMessageBufferSendFromISR(hnd,buff,size, &xHigherPriorityTaskWoken)
#define os_msgbuff_read(hnd, buff, size, timeout) xMessageBufferReceive(hnd, buff, size, timeout)
#define os_msgbuff_read_isr(hnd, buff, size) xMessageBufferReceiveFromISR(hnd,buff,size, &xHigherPriorityTaskWoken)
#define os_msgbuff_isfull(hnd) xMessageBufferIsFull(hn)
#define os_msgbuff_isempty(hnd) xMessageBufferIsEmpty(hnd)
#define os_msgbuff_freespace(hnd) xMessageBufferSpaceAvailable(hnd)
#define os_msgbuff_nextlen(hnd) xMessageBufferNextLengthBytes(hnd)
#define os_msgbuff_reset(hnd) xMessageBufferReset(hnd)*/

/* stream buffer */

#define os_stream_t int//StreamBufferHandle_t
#define os_stream_create(hnd, buffsize, waitsize) //hnd = xStreamBufferCreate(buffsize, waitsize)
#define os_stream_write(hnd, buff, size, timeout) //xStreamBufferSend(hnd, buff, size, timeout)
#define os_stream_write_isr(hnd, buff, size) //xStreamBufferSendFromISR(hnd, buff, size, &xHigherPriorityTaskWoken)
#define os_stream_read(hnd, buff, size, timeout) //xStreamBufferReceive(hnd, buff, size, timeout)
#define os_stream_read_isr(hnd, buff, size) //xStreamBufferReceiveFromISR(hnd, buff, size, &xHigherPriorityTaskWoken)
#define os_stream_isfull(hnd) //xStreamBufferIsFull(hnd)
#define os_stream_isempty(hnd) //xStreamBufferIsEmpty(hnd)
#define os_stream_freespace(hnd) //xStreamBufferSpacesAvailable(hnd)
#define os_stream_remainsize(hnd) //xStreamBufferBytesAvailable(hnd)
#define os_stream_setwaitsize(hnd, waitsize) //xStreamBufferSetTriggerLevel(hnd, waitsize)
#define os_stream_reset(hnd) //xStreamBufferReset(hnd)


/* declare extern global variables */


/* declare extern global functions */
extern void os_time_init(f64_t starttimestamp);
extern int32_t os_preinit(void);
extern void os_sleep(uint32_t delayms);
extern void os_usleep(uint32_t delayus);
extern void os_uswait(uint32_t waitus);
extern os_time_t os_time_us(void);


//#define os_time_ms()	(f64_t)(os_time_us()/1000.0lf)
//#define os_time()  (f64_t)(os_time_us()/1000000.0lf)
#define os_time_ms()	(f64_t)(os_time_us()/(double)1000.0)
#define os_time()  (f64_t)(os_time_us()/(double)1000000.0)
//#define os_wait_until(curr, wtime) vTaskDelayUntil((curr),(wtime))
//#define os_get_interrupt_instance() prvGetInterruptControllerInstance()


extern int32_t os_timeout_reset(os_time_t *currtime);
extern int32_t os_timeout_expired(os_time_t *currtime, os_time_t timeoutus);
extern int32_t os_timeout_ms_reset(os_time_ms_t *currtime_ms);
extern int32_t os_timeout_ms_expired(os_time_ms_t *currtime_ms, os_time_ms_t timeoutms);
extern void os_dcache_invalidate(uint32_t addr, size_t size);
extern int32_t os_set_uncached_memory(uint32_t addr, size_t size);


#else
#include "timer_drv.h"
#define os_time_us() timer_drv_gettime_us()
#endif




#ifdef __cplusplus
}
#endif

#endif /* OS_H__ */
