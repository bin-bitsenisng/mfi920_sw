/************************************************************************
| Project Name: bts_log
|    File Name: bts_log.c
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
| 2018.08.09   0.0   SKJ   Creation;
|***********************************************************************/

/* include system primitive types */
#include "bts.h"

/* include system driver header */
#include "bts_log.h"
#include "bts_log_cfg.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* include system bsp header */
#include "os.h"

/* include system application header */
#ifndef SYS_CONSOLE_BAUDRATE
#define SYS_CONSOLE_BAUDRATE 921600
#endif

#if SYS_CONSOLE_BAUDRATE != 115200 && !defined(WIN32)
#include "uart_drv.h"
uart_drv_t console_uart;
#endif
#if BTS_LOG_WDGSUPPORT == 1
#include "wdg_drv.h"
#define BTS_LOG_WDGCLEAR() wdg_drv_clear()
#else
#define BTS_LOG_WDGCLEAR()
#endif

/* final include module header */

/* declare global variables */
#ifndef WIN32
#include "taskmgr_cfg.h"
#ifndef TASKMGR_BTSLOG_TASK_PRIORITY
#define TASKMGR_BTSLOG_TASK_PRIORITY 1
#endif

os_stream_t stream_console;
os_task_t bts_log_task_handle;
#endif

uint8_t bts_log_task_init_flag = 0;


#if BTS_LOG_MULTICORE_SUPPORT_EN == 1 && XPAR_CPU_ID == 0
os_stream_t stream_console_from_cpu1;
#endif




/* declare static variables */
const char *bts_log_type_table[bts_log_type_end] = {"", "[ERROR]", "[WARNG]", "[INFO ]", "[DEBUG]"};
const char *bts_log_space_table = "                                                  ";

char consolebuffer[BTS_LOG_STREAMBUFFER_SIZE / 4];
os_time_t bts_log_starttime = 0;


/* static function prototypes */
void bts_log_task(void *Parameters);
int32_t bts_log_buffer_remain_percentage(void);


/* functions */
/******************************************************************************
 * function name : bts_log_init
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
void bts_log_init(void)
{
    bts_log_task_init_flag = 0;
    bts_log_starttime = os_time_us();
    krs_memclear(consolebuffer);

#if SYS_CONSOLE_BAUDRATE != 115200 && XPAR_CPU_ID == 0 && !defined(WIN32)
    uart_drv_uartinit(&console_uart, SYS_CONSOLE_BAUDRATE, uart_drv_type_PS, uart_drv_devid_CONSOLE,
                      0, 0);
#endif


    // make default bts_log configuration
#if BTS_LOG_CFG_FROM_SYS_PARAM == 1
    BTS_LOG_GLOBAL_LEVEL = bts_log_type_debug;
    BTS_LOG_OPT_LOGTYPE_EN = 0;
    BTS_LOG_OPT_TIME_EN = 1;
    BTS_LOG_OPT_DIFFTIME_EN = 1;
    BTS_LOG_OPT_FILE_EN = 1;
    BTS_LOG_OPT_FUNCTION_EN = 1;
    BTS_LOG_OPT_LINE_EN = 1;
    BTS_LOG_ARRAY_FRONTLEN = 8;
    BTS_LOG_ARRAY_BACKLEN = 8;
#endif
}


/******************************************************************************
 * function name : bts_log_task_init
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
void bts_log_task_init(void)
{
#ifndef WIN32
    os_stream_create(stream_console, BTS_LOG_STREAMBUFFER_SIZE, 128);
#if BTS_LOG_FREERTOS_SUPPORT_EN == 1
    /* module init code here*/
    /* Start the schedular task as described in the comments at the top of this     file. */
    os_task_create(bts_log_task,   /* The function that implements the task. */
                   "bts_log_task", /* The text name assigned to the task - for debug only as it is
                                      not used by the kernel. */
                   configMINIMAL_STACK_SIZE * 2, /* The size of the stack to allocate to the task.
                                                  */
                   NULL, /* The parameter passed to the task - not used in this case. */
                   TASKMGR_BTSLOG_TASK_PRIORITY, /* The priority assigned to the task. */
                   &bts_log_task_handle); /* The task handle is not required, so NULL is passed. */
#endif
#endif
}


/******************************************************************************
 * function name : bts_log_buffer_remain_percentage
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 void description
 * \return0 int32_t description
 * modification date : 2020.03.27
 *****************************************************************************/
int32_t bts_log_buffer_remain_percentage(void)
{
#ifndef WIN32
    int32_t remain;
    if(stream_console != NULL)
    {
        remain = (os_stream_freespace(stream_console) * 100) / BTS_LOG_STREAMBUFFER_SIZE;
        return (100 - remain);
    }
#endif
    return 0;
}


/******************************************************************************
 * function name : bts_log
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 type description
 * \param1 *file description
 * \param2 line description
 * \param3 *fmt description
 * \param4 ... description
 * \return void description
 * modification date : 2018.08.09
 *****************************************************************************/
void bts_log_header(bts_log_type_t type, const char *file, const char *function, int line)
{
    char consoleheaderbuffer[100];
    uint32_t day, hour, min, sec, msec, usec;
    int32_t filelen, filepos;
    int32_t fctlen, fctpos;
    int32_t offset = 0;
    os_time_t timestampus;
    static os_time_t timestampus_pre = 0;
    os_time_t difftimestampus = 0;


    offset = 0;

    // log level
    if(BTS_LOG_GLOBAL_LEVEL < type)
        return;
    // log type
    if(BTS_LOG_OPT_LOGTYPE_EN)
    {
        if(type > bts_log_type_debug)
            type = bts_log_type_debug;
        offset += snprintf(&consoleheaderbuffer[offset], sizeof(consoleheaderbuffer) - offset, "%s",
                           bts_log_type_table[type]);
        // bts_log("%s", bts_log_type_table[type]);
    }

    // log queue depth
    if(BTS_LOG_OPT_LOG_QEUDEPTH_EN)
    {
        offset += snprintf(&consoleheaderbuffer[offset], sizeof(consoleheaderbuffer) - offset,
                           "[%2d%%]", (int)bts_log_buffer_remain_percentage());
        // bts_log("[%2d%]",(bts_log_queue_count()*100)/BTS_LOG_MESSAGEQUE_DEPTH);
    }
    // time
    timestampus = os_time_us() - bts_log_starttime;
    if(BTS_LOG_OPT_TIME_EN)
    {
        usec = timestampus % 1000;
        msec = timestampus / 1000;
        sec = msec / 1000;
        min = sec / 60;
        hour = min / 60;
        day = hour / 24;
        // [001-03:45:35.013_024]
#if BTS_LOG_OPT_DAYTIME_EN == 1
        offset += snprintf(&consoleheaderbuffer[offset], sizeof(consoleheaderbuffer) - offset,
                           "[%03d-%02d:%02d:%02d.%03d_%03d]", (int)day, (int)(hour % 24),
                           (int)(min % 60), (int)(sec % 60), (int)(msec % 1000), (int)usec);
#else
#if BTS_LOG_OPT_TIME_US_EN == 1
        offset += snprintf(&consoleheaderbuffer[offset], sizeof(consoleheaderbuffer) - offset,
                           "[%02d:%02d:%02d.%03d_%03d]", hour % 24, min % 60, sec % 60, msec % 1000,
                           usec);
#else
        offset += snprintf(&consoleheaderbuffer[offset], sizeof(consoleheaderbuffer) - offset,
                           "[%02d:%02d:%02d.%03d]", hour % 24, min % 60, sec % 60, msec % 1000);
#endif
#endif
        // bts_log("[%03d-%02d:%02d:%02d.%03d_%03d]", day, hour % 24, min % 60, sec % 60, msec %
        // 1000, usec);
    }
    if(BTS_LOG_OPT_DIFFTIME_EN)
    {
        difftimestampus = timestampus - timestampus_pre;
        usec = difftimestampus % 1000;
        msec = difftimestampus / 1000;
        sec = msec / 1000;
        offset += snprintf(&consoleheaderbuffer[offset], sizeof(consoleheaderbuffer) - offset,
                           "[%d.%03d_%03d]", (int)sec, (int)(msec % 1000), (int)usec);
        // bts_log("[%+d.%03d_%03d]", sec, msec % 1000,usec);
        timestampus_pre = timestampus;
    }
    // file
    if(BTS_LOG_OPT_FILE_EN)
    {
        filelen = strlen(file);
        if(filelen > BTS_LOG_FILE_LEN_MAX)
        {
            filepos = filelen - BTS_LOG_FILE_LEN_MAX;
        }
        else
        {
            filepos = 0;
        }
        offset += snprintf(&consoleheaderbuffer[offset], sizeof(consoleheaderbuffer) - offset,
                           "[~%-.*s]", BTS_LOG_FILE_LEN_MAX, &file[filepos]);
        // bts_log("[~%-.*s]", BTS_LOG_FILE_LEN_MAX, &file[filepos]);
    }
    // function
    if(BTS_LOG_OPT_FUNCTION_EN)
    {
        fctlen = strlen(function);
        if(fctlen > BTS_LOG_FUNCTION_LEN_MAX)
        {
            fctpos = fctlen - BTS_LOG_FUNCTION_LEN_MAX;
            offset += snprintf(&consoleheaderbuffer[offset], sizeof(consoleheaderbuffer) - offset,
                               "[~%-.*s]", BTS_LOG_FUNCTION_LEN_MAX, &function[fctpos]);
            // bts_log("[~%-.*s]", BTS_LOG_FUNCTION_LEN_MAX, &function[fctpos]);
        }
        else
        {
            fctpos = 0;
            offset +=
                snprintf(&consoleheaderbuffer[offset], sizeof(consoleheaderbuffer) - offset, "[ ");
            offset +=
                snprintf(&consoleheaderbuffer[offset], sizeof(consoleheaderbuffer) - offset, "%.*s",
                         (int)(BTS_LOG_FUNCTION_LEN_MAX - fctlen), bts_log_space_table);
            offset += snprintf(&consoleheaderbuffer[offset], sizeof(consoleheaderbuffer) - offset,
                               "%-.*s]", BTS_LOG_FUNCTION_LEN_MAX, &function[fctpos]);
            //          bts_log("[ ");
            //          bts_log("%.*s", BTS_LOG_FUNCTION_LEN_MAX - fctlen, bts_log_space_table);
            //          bts_log("%-.*s]", BTS_LOG_FUNCTION_LEN_MAX, &function[fctpos]);
        }
    }
    // line
    if(BTS_LOG_OPT_LINE_EN)
    {
        offset += snprintf(&consoleheaderbuffer[offset], sizeof(consoleheaderbuffer) - offset,
                           "[%4d]", line);
        // bts_log("[%4d]", line);
    }

    consoleheaderbuffer[offset] = 0;
    bts_log("%s|", consoleheaderbuffer);
    // bts_log("| ");
}

/******************************************************************************
 * function name : bts_log_print
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *fmt description
 * \param1 ... description
 * \return void description
 * modification date : 2018.08.09
 *****************************************************************************/
void bts_log_print(const char *fmt, ...)
{
    int32_t len;
    va_list args;
    // message

    if(BTS_LOG_GLOBAL_LEVEL == bts_log_type_disable)
    {
        return;
    }

    va_start(args, fmt);
    len = vsnprintf(consolebuffer, sizeof(consolebuffer), fmt, args);
#if BTS_LOG_FREERTOS_SUPPORT_EN == 1
    if((os_is_running() == os_retOK) && bts_log_task_init_flag == 1)
    {
        if(len != 0 && len < os_stream_freespace(stream_console))
        {
            if(os_stream_write(stream_console, consolebuffer, len, 0) != os_retOK)
            {
                // timeout or buffer full
            }
        }
        else
        {
            // flushing buffer
            bts_log_flush();
        }
    }
    else
    {
        // vprintf(fmt, args);
        printf("%.*s", (int)len, consolebuffer);
    }
#else
    vprintf(fmt, args);
#endif

    va_end(args);
}


/******************************************************************************
 * function name : bts_log_task
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *Parameters description
 * \return0 void description
 * modification date : 2020.03.27
 *****************************************************************************/
void bts_log_task(void *Parameters)
{
#if BTS_LOG_FREERTOS_SUPPORT_EN == 1
    uint32_t ret;
    char csbuff[256 + 2];
    bts_log_task_init_flag = 1;

    for(;;)
    {
        ret = os_stream_read(stream_console, csbuff, 256, os_max_delay);
        if(ret != 0)
        {
            csbuff[ret] = 0x00;
            printf("%s", csbuff);
        }
    }
#endif
}


/******************************************************************************
 * function name : bts_log_flush
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
void bts_log_flush(void)
{
#if BTS_LOG_FREERTOS_SUPPORT_EN == 1
    uint32_t ret;
    char csbuff[128 + 2];
    os_suspendall();
    do
    {
        ret = os_stream_read(stream_console, csbuff, 128, 1);
        if(ret != 0)
        {
            csbuff[ret] = 0x00;
            printf("%s", csbuff);
        }

        BTS_LOG_WDGCLEAR();

    } while(ret);
    os_resumeall();
#endif
}


/******************************************************************************
 * function name : bts_log_array_range
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 dptype description
 * \param1 dtype description
 * \param2 *ptr description
 * \param3 len description
 * \param4 frontlen description
 * \param5 backlen description
 * \return void description
 * modification date : 2018.08.09
 *****************************************************************************/
void bts_log_array_range(bts_log_disp_t dptype, bts_log_dtype_t dtype, void *ptr, int32_t len,
                         int32_t frontlen, int32_t backlen)
{
    int32_t i;

    if(len > (frontlen + backlen))
    {
        backlen = len - backlen;
    }
    else
    {
        frontlen = len;
        backlen = 0;
    }

    bts_log_print("[");
    switch(dtype)
    {
        case bts_log_dtype_uint8:
            for(i = 0; i < frontlen; i++)
                bts_log_print("%02X ", ((uint8_t *)ptr)[i]);
            if(backlen != 0)
            {
                bts_log_print("~~//~~ ");
                for(i = backlen; i < len; i++)
                    bts_log_print("%02X ", ((uint8_t *)ptr)[i]);
            }
            break;
        case bts_log_dtype_int8:
            for(i = 0; i < frontlen; i++)
                bts_log_print("%02X ", ((int8_t *)ptr)[i]);
            if(backlen != 0)
            {
                bts_log_print("~~//~~ ");
                for(i = backlen; i < len; i++)
                    bts_log_print("%02X ", ((int8_t *)ptr)[i]);
            }
            break;
        case bts_log_dtype_uint16:
            for(i = 0; i < frontlen; i++)
                bts_log_print("%04X ", ((uint16_t *)ptr)[i]);
            if(backlen != 0)
            {
                bts_log_print("~~//~~ ");
                for(i = backlen; i < len; i++)
                    bts_log_print("%04X ", ((uint16_t *)ptr)[i]);
            }
            break;
        case bts_log_dtype_int16:
            for(i = 0; i < frontlen; i++)
                bts_log_print("%04X ", ((int16_t *)ptr)[i]);
            if(backlen != 0)
            {
                bts_log_print("~~//~~ ");
                for(i = backlen; i < len; i++)
                    bts_log_print("%04X ", ((int16_t *)ptr)[i]);
            }
            break;
        case bts_log_dtype_uint32:
            for(i = 0; i < frontlen; i++)
                bts_log_print("%08lX ", ((uint32_t *)ptr)[i]);
            if(backlen != 0)
            {
                bts_log_print("~~//~~ ");
                for(i = backlen; i < len; i++)
                    bts_log_print("%08lX ", ((uint32_t *)ptr)[i]);
            }
            break;
        case bts_log_dtype_int32:
            for(i = 0; i < frontlen; i++)
                bts_log_print("%08lX ", ((int32_t *)ptr)[i]);
            if(backlen != 0)
            {
                bts_log_print("~~//~~ ");
                for(i = backlen; i < len; i++)
                    bts_log_print("%08lX ", ((int32_t *)ptr)[i]);
            }
            break;
        case bts_log_dtype_uint64:
            for(i = 0; i < frontlen; i++)
                bts_log_print("%016llX ", ((uint64_t *)ptr)[i]);
            if(backlen != 0)
            {
                bts_log_print("~~//~~ ");
                for(i = backlen; i < len; i++)
                    printf("%016llX ", ((uint64_t *)ptr)[i]);
            }
            break;
        case bts_log_dtype_int64:
            for(i = 0; i < frontlen; i++)
                bts_log_print("%016llX ", ((int64_t *)ptr)[i]);
            if(backlen != 0)
            {
                bts_log_print("~~//~~ ");
                for(i = backlen; i < len; i++)
                    bts_log_print("%016llX ", ((int64_t *)ptr)[i]);
            }
            break;
        case bts_log_dtype_f32:
            for(i = 0; i < frontlen; i++)
                bts_log_print("%f ", ((f32_t *)ptr)[i]);
            if(backlen != 0)
            {
                bts_log_print("~~//~~ ");
                for(i = backlen; i < len; i++)
                    bts_log_print("%f ", ((f32_t *)ptr)[i]);
            }
            break;
        case bts_log_dtype_f64:
            for(i = 0; i < frontlen; i++)
                bts_log_print("%lf ", ((f64_t *)ptr)[i]);
            if(backlen != 0)
            {
                bts_log_print("~~//~~ ");
                for(i = backlen; i < len; i++)
                    bts_log_print("%lf ", ((f64_t *)ptr)[i]);
            }
            break;
        case bts_log_dtype_char:
            for(i = 0; i < frontlen; i++)
                bts_log_print("%c ", ((char *)ptr)[i]);
            if(backlen != 0)
            {
                bts_log_print("~~//~~ ");
                for(i = backlen; i < len; i++)
                    bts_log_print("%c ", ((char *)ptr)[i]);
            }
            break;
        case bts_log_dtype_string:
            for(i = 0; i < frontlen; i++)
                bts_log_print("'%s' ", ((char *)ptr)[i]);
            if(backlen != 0)
            {
                bts_log_print("~~//~~ ");
                for(i = backlen; i < len; i++)
                    bts_log_print("'%s' ", ((char *)ptr)[i]);
            }
            break;

        default:
            break;
    }

    bts_log_print("]\n\r");
}


/******************************************************************************
 * function name : _close
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 fd description
 * \return0 int32_t description
 * modification date : 2020.03.27
 *****************************************************************************/
int32_t _close(int32_t fd)
{
    (void)fd;
    return (0);
}


/******************************************************************************
 * function name : _read
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 fd description
 * \param1 *buf description
 * \param2 nbytes description
 * \return0 int32_t description
 * modification date : 2020.03.27
 *****************************************************************************/
int32_t _read(int32_t fd, int8_t *buf, int32_t nbytes)
{
#ifdef STDIN_BASEADDRESS
    int32_t i;
    int32_t numbytes = 0;
    int8_t *LocalBuf = buf;

    (void)fd;
    if(LocalBuf != NULL)
    {
        for(i = 0; i < nbytes; i++)
        {
            numbytes++;
            *(LocalBuf + i) = inbyte();
            if((*(LocalBuf + i) == '\n') || (*(LocalBuf + i) == '\r'))
            {
                break;
            }
        }
    }

    return numbytes;
#else
    (void)fd;
    (void)buf;
    (void)nbytes;
    return 0;
#endif
}


/******************************************************************************
 * function name : _write
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 fd description
 * \param1 *buf description
 * \param2 nbytes description
 * \return0 int32_t description
 * modification date : 2020.03.27
 *****************************************************************************/
int32_t _write(int32_t fd, int8_t *buf, int32_t nbytes)
{

#ifdef STDOUT_BASEADDRESS
    int32_t i;
    int8_t *LocalBuf = buf;

    (void)fd;
    for(i = 0; i < nbytes; i++)
    {
        if(LocalBuf != NULL)
        {
            LocalBuf += i;
        }
        if(LocalBuf != NULL)
        {
            if(*LocalBuf == '\n')
            {
                outbyte('\r');
            }
            outbyte(*LocalBuf);
        }
        if(LocalBuf != NULL)
        {
            LocalBuf -= i;
        }
    }
    return (nbytes);
#else
    (void)fd;
    (void)buf;
    (void)nbytes;
    return 0;
#endif
}


/* end of file */
