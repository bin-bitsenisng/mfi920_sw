/************************************************************************
 | Project Name: KRS24
 |    File Name: rsp_lib.h
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

#ifndef RSP_LIB_H__
#define RSP_LIB_H__

/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "rsp_lib_cfg.h"

#include "NE10.h"

/* module specific types  */
typedef int32_t rsp_lib_ret_t;


/* define structure for this module */
typedef struct{
    int32_t moduleinfo;
    int32_t version;
}rsp_lib_info_t;


/* declare extern global variables */



#define RSP_LIB_OPT_MODE_C 0
#define RSP_LIB_OPT_MODE_NEON 1
#define RSP_LIB_OPT_MODE_ASM 2

#ifdef WIN32
#define RSP_LIB_OPT_MODE  RSP_LIB_OPT_MODE_C
#else
#define RSP_LIB_OPT_MODE  RSP_LIB_OPT_MODE_NEON
#endif

#if RSP_LIB_OPT_MODE == RSP_LIB_OPT_MODE_C
#define rsp_lib_mulc_f32(des, src, val, cnt) ne10_mulc_float_c((ne10_float32_t*)(des), (ne10_float32_t*)src, val, cnt)
#define rsp_lib_mul_f32(dst, src1,src2,cnt) ne10_mul_float_c ((ne10_float32_t*)dst, (ne10_float32_t*)src1, (ne10_float32_t*)src2, cnt)

#elif RSP_LIB_OPT_MODE == RSP_LIB_OPT_MODE_NEON
#define rsp_lib_mulc_f32(des, src, val, cnt) ne10_mulc_float_neon((ne10_float32_t*)(des), (ne10_float32_t*)src, val, cnt)
#define rsp_lib_mul_f32(dst, src1, src2, cnt) ne10_mul_float_neon ((ne10_float32_t*)dst, (ne10_float32_t*)src1, (ne10_float32_t*)src2, cnt)

#elif RSP_LIB_OPT_MODE == RSP_LIB_OPT_MODE_ASM
#define rsp_lib_mulc_f32(des, src, val, cnt) ne10_mulc_float_asm((ne10_float32_t*)(des), (ne10_float32_t*)src, val, cnt)
#define rsp_lib_mul_f32(dst, src1,src2,cnt) ne10_mul_float_asm ((ne10_float32_t*)dst, (ne10_float32_t*)src1, (ne10_float32_t*)src2, cnt)


#else
#error "undefined RSP_LIB_OPT_MODE"
#endif


#define rsp_lib_fft_c2c_1d_f32(d,s,l) rsp_lib_fft_c2c_1d_float32((ne10_fft_cpx_float32_t *)(d),(ne10_fft_cpx_float32_t *)(s),(int32_t)(l))



#define RSP_LIB_DSP_NEON 0
#define RSP_LIB_DSP_C 1






/* declare extern global functions */
extern rsp_lib_ret_t rsp_lib_init(void);
extern void rsp_lib_HannWindow(f32_t *Window,int32_t size);
extern void rsp_lib_HammingWindow(f32_t *Window,int32_t size);
extern void rsp_lib_BlackmanWindow(f32_t *Window,int32_t size);
extern void rsp_lib_BlackmanHarrisWindow(f32_t *Window,int32_t size);
extern void rsp_lib_fft_c2c_1d_float32(ne10_fft_cpx_float32_t *dst, ne10_fft_cpx_float32_t *src, int32_t fftlen);


#endif /* RSP_LIB_H__ */
