/************************************************************************
| Project Name: bts_log
|    File Name: bts_log.h
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
#ifndef BTS_LOG_H__
#define BTS_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

/* include system primitive types */
#include "bts.h"
#include "bts_log_cfg.h"

/* module specific types  */
typedef enum {
    bts_log_type_disable,
    bts_log_type_error,
    bts_log_type_warning,
    bts_log_type_info,
    bts_log_type_debug,
    bts_log_type_end,
} bts_log_type_t;


typedef enum {
    bts_log_dtype_uint8,
    bts_log_dtype_int8,
    bts_log_dtype_uint16,
    bts_log_dtype_int16,
    bts_log_dtype_uint32,
    bts_log_dtype_int32,
    bts_log_dtype_uint64,
    bts_log_dtype_int64,
    bts_log_dtype_f32,
    bts_log_dtype_f64,
    bts_log_dtype_char,
    bts_log_dtype_string,
    bts_log_dtype_end
} bts_log_dtype_t;

typedef enum {
    bts_log_disp_decimal,
    bts_log_disp_hex,
    bts_log_disp_bin,
} bts_log_disp_t;

/* define structure for this module */


/* declare extern global variables */

/* declare extern global functions */
extern void bts_log_init(void);
extern void bts_log_task_init(void);
extern void bts_log_header(bts_log_type_t type, const char *file, const char *function, int line);

//#define bts_log xil_printf
#define bts_log bts_log_print
#define bts_logk xil_printf

extern void bts_log_print(const char *fmt, ...);
extern void bts_log_flush(void);
extern void bts_log_array_range(bts_log_disp_t dptype, bts_log_dtype_t dtype, void *ptr,
                                int32_t len, int32_t frontlen, int32_t backlen);

#define bts_log_debug_header() bts_log_header(bts_log_type_debug,__FILE__,__FUNCTION__,__LINE__)
#define bts_log_info_header() bts_log_header(bts_log_type_info,__FILE__,__FUNCTION__,__LINE__)
#define bts_log_warning_header() bts_log_header(bts_log_type_warning,__FILE__,__FUNCTION__,__LINE__)
#define bts_log_error_header() bts_log_header(bts_log_type_error,__FILE__,__FUNCTION__,__LINE__)
#define bts_debug(fmt,...) bts_log_debug_header(), bts_log(fmt,##__VA_ARGS__)
#define bts_info(fmt,...) bts_log_info_header(), bts_log(fmt,##__VA_ARGS__)
#define bts_warning(fmt,...) bts_log_warning_header(), bts_log(fmt,##__VA_ARGS__)
#define bts_error(fmt,...) bts_log_error_header(), bts_log(fmt,##__VA_ARGS__)

#define bts_array_int8_base10(ptr, len) bts_log_debug_header(), bts_log_array_range(bts_log_disp_decimal, bts_log_dtype_int8, (void*)ptr, len, BTS_LOG_ARRAY_FRONTLEN,BTS_LOG_ARRAY_BACKLEN);
#define bts_array_uint8_base10(ptr, len) bts_log_debug_header(), bts_log_array_range(bts_log_disp_decimal, bts_log_dtype_uint8, (void*)ptr, len, BTS_LOG_ARRAY_FRONTLEN,BTS_LOG_ARRAY_BACKLEN);
#define bts_array_uint8_base16(ptr, len) bts_log_debug_header(), bts_log_array_range(bts_log_disp_hex, bts_log_dtype_uint8, (void*)ptr, len, BTS_LOG_ARRAY_FRONTLEN,BTS_LOG_ARRAY_BACKLEN);
#define bts_array_uint8_base16_nh(ptr, len) bts_log_array_range(bts_log_disp_hex, bts_log_dtype_uint8, (void*)ptr, len, BTS_LOG_ARRAY_FRONTLEN,BTS_LOG_ARRAY_BACKLEN);

#define bts_array_int16_base10(ptr, len) bts_log_debug_header(), bts_log_array_range(bts_log_disp_decimal, bts_log_dtype_int16, (void*)ptr, len, BTS_LOG_ARRAY_FRONTLEN,BTS_LOG_ARRAY_BACKLEN);
#define bts_array_uint16_base10(ptr, len) bts_log_debug_header(), bts_log_array_range(bts_log_disp_decimal, bts_log_dtype_uint16, (void*)ptr, len, BTS_LOG_ARRAY_FRONTLEN,BTS_LOG_ARRAY_BACKLEN);
#define bts_array_uint16_base16(ptr, len) bts_log_debug_header(), bts_log_array_range(bts_log_disp_hex, bts_log_dtype_uint16, (void*)ptr, len, BTS_LOG_ARRAY_FRONTLEN,BTS_LOG_ARRAY_BACKLEN);

#define bts_array_int32_base10(ptr, len) bts_log_debug_header(), bts_log_array_range(bts_log_disp_decimal, bts_log_dtype_int32, (void*)ptr, len, BTS_LOG_ARRAY_FRONTLEN,BTS_LOG_ARRAY_BACKLEN);
#define bts_array_uint32_base10(ptr, len) bts_log_debug_header(), bts_log_array_range(bts_log_disp_decimal, bts_log_dtype_uint32, (void*)ptr, len, BTS_LOG_ARRAY_FRONTLEN,BTS_LOG_ARRAY_BACKLEN);
#define bts_array_uint32_base16(ptr, len) bts_log_debug_header(), bts_log_array_range(bts_log_disp_hex, bts_log_dtype_uint32, (void*)ptr, len, BTS_LOG_ARRAY_FRONTLEN,BTS_LOG_ARRAY_BACKLEN);

#define bts_array_f32(ptr, len) bts_log_debug_header(), bts_log_array_range(bts_log_disp_decimal, bts_log_dtype_f32, (void*)ptr, len, BTS_LOG_ARRAY_FRONTLEN,BTS_LOG_ARRAY_BACKLEN);
#define bts_array_f64(ptr, len) bts_log_debug_header(), bts_log_array_range(bts_log_disp_decimal, bts_log_dtype_f64, (void*)ptr, len, BTS_LOG_ARRAY_FRONTLEN,BTS_LOG_ARRAY_BACKLEN);


extern int32_t bts_log_read(char *buff, size_t size, uint32_t timeoutms);

#ifdef __cplusplus
}
#endif

#endif // BTS_LOG_H__
