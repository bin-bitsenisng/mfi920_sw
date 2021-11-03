/************************************************************************
 | Project Name: KRS24
 |    File Name: krs_macro.h
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

#ifndef KRS_MACRO_H__
#define KRS_MACRO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include <stdio.h>
#include <string.h>
#include <assert.h> 

#ifdef WIN32
#include <assert.h>
#else
//#include "xil_printf.h"
#endif

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define KRS_MEMMAP(sec) __attribute__((section(sec)))
#define KRS_WEAK __attribute__((weak))
#define krs_memclear(x) (void) memset((void*)(x), 0x00, sizeof(x))
#define krs_memnclear(x,n) (void)memset((void*)(x), 0x00, (n))
#define krs_memclearitem(x) (void) memset((void*)(&x), 0x00, sizeof(x))
#define krs_memcopy8(des, src, count) (void) memcpy((void*)(des), (void*)(src), (count))
#define krs_memcopy16(des, src, count) (void) memcpy((void*)(des), (void*)(src), ((count)*2))
#define krs_memcopy64(des, src, count) krs_memory_copy64((void*)(des), (void*)(src), (count))
#define krs_memset(des, val, count) (void) memset((void*)(des), (uint8_t)(val), (count))

#define krs_memcopy krs_memcopy8
#define krs_dma_memcopy(des, src, count) dma_drv_memcopy((void*)(des), (void*)(src), (count))
#define krs_dma_memcopy_start(ch, des, src, count) dma_drv_memcopy_start(ch,(void*)(des), (void*)(src), (count))
#define krs_dma_memcopy_end(ch) dma_drv_memcopy_end(ch)

#define krs_memcmp memcmp
/* performance */
#define krs_timeit(ret,msg, statement) {timer_timemeasurement_t timeit; timer_drv_start(&timeit); {statement}; (ret) = timer_drv_stop(&timeit); krs_log("krs_timeit:%s execution time is %.3fms\n\r", msg, (f32_t)(((f64_t)(ret))/1000.0f));} 

#define BTS_MEMMAP KRS_MEMMAP
#define BTS_WEAK KRS_WEAK
#define bts_memclear krs_memclear
#define bts_memnclear krs_memnclear
#define bts_memclearitem krs_memclearitem
#define bts_memcopy8 krs_memcopy8
#define bts_memcopy16 krs_memcopy16
#define bts_memcopy64 krs_memcopy64
#define bts_memset krs_memset
#define bts_memcopy krs_memcopy
#define bts_dma_memcopy krs_dma_memcopy
#define bts_dma_memcopy_start krs_dma_memcopy_start
#define bts_dma_memcopy_end krs_dma_memcopy_end
#define bts_memcmp krs_memcmp
#define bts_timeit krs_timeit


/* declare extern global variables */

#ifdef WIN32
#define krs_assert( x ) assert(x)
#define krs_check( x ) if( (x) == 0) return retFail
#define krs_debugcheck( x, fmt, ...) if((x)==0) {krs_log(fmt"\r\n",##__VA_ARGS__); return retFail;}
#else
//extern void vAssertCalled( const char * pcFile, unsigned long ulLine );
//#define krs_assert( x ) if( ( x ) == 0 ) vAssertCalled( __FILE__, __LINE__ );
#define krs_assert( x ) assert( x )
#define krs_check( x ) if( (x) == 0) return retFail
#define krs_debugcheck( x, fmt, ...) if((x)==0) {krs_log(fmt"\r\n",##__VA_ARGS__); return retFail;}
#endif

#define bts_assert krs_assert
#define bts_check krs_check
#define bts_debugcheck krs_debugcheck


#define krs_endian_swap16(x)    ((((x)&0xFF)<<8)|(((x)>>8)&0xFF))
#define krs_endian_swap32(x)    ((krs_endian_swap16((x)&0xFFFF)<<16) | (krs_endian_swap16(((x)>>16)&0xFFFF)))
#define bts_endian_swap16 krs_endian_swap16
#define bts_endian_swap32 krs_endian_swap32


/* bound */
#define krs_bound(min, x, max) ((x)<(min)? (min):((x)>(max)?(max):(x)))
#define krs_min(a,b) ((a)<(b)? (a):(b))
#define krs_max(a,b) ((a)>=(b)? (a):(b))

#define krs_s8bound(x) ((int8_t)krs_bound(-128.0f, (x), 127.0f))
#define krs_u8bound(x) ((uint8_t)krs_min((x), 255.0f))
#define krs_s16bound(x) ((int16_t)krs_bound(-32768.0f, (x), 32767.0f))
#define krs_u16bound(x) ((uint16_t)krs_min((x), 65536.0f))

#define bts_bound krs_bound
#define bts_min krs_min
#define bts_max krs_max
#define bts_s8bound krs_s8bound
#define bts_u8bound krs_u8bound
#define bts_s16bound krs_s16bound
#define bts_u16bound krs_u16bound


/* declare extern global functions */
extern void krs_memory_copy64(void *des, void* src, size_t size);


/* align */
#define KRS_ALIGN(x) __attribute__ ((aligned ((x))))
#define krs_size_align(size, align)  ((((size)%(align)) == 0) ?  (size): ((size) + ((align)-((size)%(align)))))
#define BTS_ALIGN KRS_ALIGN
#define bts_size_align krs_size_align


/* log */
#define krs_log_enable 1
#define krs_log_level 0 // 0:debug, 1:info, 2:error,
#define bts_log_enable 1

#ifdef WIN32
#define krs_log_printf  printf
#else
#define krs_log_printf  printf // xil_printf
#endif

#define krs_log_dummy   krs_macro_dummy_printf

#if krs_log_enable == 1
    #define krs_log printf//bts_debug //krs_log_printf //logger_printf
#define krs_log_rb(fmt, ...)    bts_debug("\x1b[31m" fmt "\x1b[0m", ##__VA_ARGS__)
#define krs_log_gb(fmt, ...)    bts_debug("\x1b[32m" fmt "\x1b[0m", ##__VA_ARGS__)
#define krs_log_yb(fmt, ...)    bts_debug("\x1b[33m" fmt "\x1b[0m", ##__VA_ARGS__)
#define krs_log_bb(fmt, ...)    bts_debug("\x1b[34m" fmt "\x1b[0m", ##__VA_ARGS__)
#define krs_log_mb(fmt, ...)    bts_debug("\x1b[35m" fmt "\x1b[0m", ##__VA_ARGS__)
#define krs_log_cb(fmt, ...)    bts_debug("\x1b[36m" fmt "\x1b[0m", ##__VA_ARGS__)
#define krs_log_by(fmt, ...)    bts_debug("\x1b[1m\x1b[7m" fmt "\x1b[0m", ##__VA_ARGS__)

    #define krs_logq logger_printf
#else
    #define krs_log krs_log_dummy
    #define krs_logq krs_log_dummy
#endif

#if bts_log_enable == 0
#if krs_log_level < 1
    #define krs_log_debug krs_log("[DEBUG](%8.3fms)[%16s(%d)]|",(f32_t)timer_drv_gettime_us()/1000.0f,__FILE__,__LINE__);krs_log
#else
    #define krs_log_debug krs_log_dummy
#endif

#if krs_log_level < 2
    #define krs_log_info krs_log("[INFO ](%8.3fms)[%16s(%d)]|",(f32_t)timer_drv_gettime_us()/1000.0f,__FILE__,__LINE__);krs_log
#else
    #define krs_log_info krs_log_dummy
#endif

#if krs_log_level < 3
    #define krs_log_error krs_log("[ERROR](%8.3fms)[%16s(%d)]|",(f32_t)timer_drv_gettime_us()/1000.0f,__FILE__,__LINE__);krs_log
#else
    #define krs_log_error krs_log_dummy
#endif
#else
#include "bts_log_cfg.h"
#include "bts_log.h"
#define krs_log_print bts_log_print
#define krs_log_error bts_error
#define krs_log_warning bts_warning
#define krs_log_info bts_info
#define krs_log_debug bts_debug

#define krs_log_arrint8D bts_array_int8_base10
#define krs_log_arruint8D bts_array_uint8_base10
#define krs_log_arruint8X bts_array_uint8_base16
#define krs_log_arruint8X_nh bts_array_uint8_base16_nh
#define krs_log_arruint8X_fmt(addr,size,fmt,...) krs_log(fmt, ##__VA_ARGS__),krs_log_arruint8X_nh(addr,size)
#define krs_log_arruint8X_fmt_dummy(addr,size,fmt,...) krs_log_dummy(fmt, ##__VA_ARGS__)
#define krs_log_arrint16D bts_array_int16_base10
#define krs_log_arruint16D bts_array_uint16_base10
#define krs_log_arruint16X bts_array_uint16_base16

#define krs_log_arrint32D bts_array_int32_base10
#define krs_log_arruint32D bts_array_uint32_base10
#define krs_log_arruint32X bts_array_uint32_base16

#define krs_log_arrf32 bts_array_f32
#define krs_log_arrf64 bts_array_f64

#endif


extern void krs_macro_dummy_printf( const char_t* s, ... );

#define krs_mem(addr,offset) (*((uint8_t*)(addr) + (offset)))
#define krs_u8mem(addr) krs_mem(addr,0)
#define krs_u16mem(addr) (krs_mem(addr,0) | (krs_mem(addr,1)<<8))
#define krs_u32mem(addr) (krs_mem(addr,0) | (krs_mem(addr,1)<<8)| (krs_mem(addr,2)<<16)| (krs_mem(addr,3)<<24))

#define krs_setmem(addr,offset,data)    (*((uint8_t*)(addr)+(offset))) = ((data)&0xFF)
#define krs_u8setmem(addr, data)   krs_setmem((addr),0,(data))
#define krs_u16setmem(addr, data)   krs_setmem((addr),0,(data)); krs_setmem((addr),1,(data)>>8)
#define krs_u32setmem(addr, data)   krs_setmem((addr),0,(data)); krs_setmem((addr),1,(data)>>8); krs_setmem((addr),2,(data)>>16); krs_setmem((addr),3,(data)>>24)
extern void krs_reverse_u8array(uint8_t *array, int32_t number);


#define krs_unused_param(x)          {if((x) != 0U){/* Do Nothing */}}



#ifdef __cplusplus
}
#endif

#endif /* KRS_MACRO_H__ */
