/************************************************************************
 | Project Name: KRS24
 |    File Name: rsp_lib.c
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
#include "rsp_lib_cfg.h"
#include <math.h>
/* include system driver header */


/* include system bsp header */


/* include system application header */


/* final include module header */
# include "rsp_lib.h"


/* declare global variables */


/* declare static variables */
ne10_fft_cfg_float32_t rsp_lib_fftcfg_32K;
ne10_fft_cfg_float32_t rsp_lib_fftcfg_16K;
ne10_fft_cfg_float32_t rsp_lib_fftcfg_8K;
ne10_fft_cfg_float32_t rsp_lib_fftcfg_4K;
ne10_fft_cfg_float32_t rsp_lib_fftcfg_2K;
ne10_fft_cfg_float32_t rsp_lib_fftcfg_1K;
ne10_fft_cfg_float32_t rsp_lib_fftcfg_512;
ne10_fft_cfg_float32_t rsp_lib_fftcfg_256;
ne10_fft_cfg_float32_t rsp_lib_fftcfg_128;
ne10_fft_cfg_float32_t rsp_lib_fftcfg_64;
ne10_fft_cfg_float32_t rsp_lib_fftcfg_32;

/* static function prototypes */



/* functions */
/***************************************************
 * function name : rsp_lib_init
 * description : module init function
 * input param : void
 * return : retOk or retFail
 * TODO :
 ***************************************************/
rsp_lib_ret_t rsp_lib_init(void)
{
    /* module init code here*/
#ifdef WIN32
	ne10_init_dsp(RSP_LIB_DSP_C);
#else
	ne10_init_dsp(RSP_LIB_DSP_NEON); // Ne10 with neon
#endif

	rsp_lib_fftcfg_32K = ne10_fft_alloc_c2c_float32(32768);
	rsp_lib_fftcfg_16K = ne10_fft_alloc_c2c_float32(16384);
	rsp_lib_fftcfg_8K = ne10_fft_alloc_c2c_float32(8192);
	rsp_lib_fftcfg_4K = ne10_fft_alloc_c2c_float32(4096);
	rsp_lib_fftcfg_2K = ne10_fft_alloc_c2c_float32(2048);
	rsp_lib_fftcfg_1K = ne10_fft_alloc_c2c_float32(1024);
	rsp_lib_fftcfg_512 = ne10_fft_alloc_c2c_float32(512);
	rsp_lib_fftcfg_256 = ne10_fft_alloc_c2c_float32(256);
	rsp_lib_fftcfg_128 = ne10_fft_alloc_c2c_float32(128);
	rsp_lib_fftcfg_64 = ne10_fft_alloc_c2c_float32(64);
	rsp_lib_fftcfg_32 = ne10_fft_alloc_c2c_float32(32);

    return retOK;
}

/* end of file */



// Calculate a Hann window function
void rsp_lib_HannWindow(f32_t *Window,int32_t size)
{

    int32_t ii;

    for (ii = 0; ii < size; ii++) {
        Window[ii] = (f32_t)( 0.5f * (1.0f - cosf((2.0f * M_PI * (f32_t)ii) / (f32_t)(size -1))));
    }
}

// Calculate a Hamming window function
void rsp_lib_HammingWindow(f32_t *Window,int32_t size)
{

    int32_t ii;
    const f32_t a0 = 0.35875f;
    const f32_t b0 = 0.48829f;

    for (ii = 0; ii < size; ii++) {
        Window[ii] = (f32_t)(a0 - b0 * (cosf((2.0f * M_PI * (f32_t)ii) / ((f32_t)size -1))) );
    }
}

// Calculate a Blackman window function
void rsp_lib_BlackmanWindow(f32_t *Window,int32_t size)
{

    int32_t ii;
    const f32_t a0 = (7938.0f/18608.0f);
    const f32_t a1 = (9240.0f/18608.0f);
    const f32_t a2 = (1430.0f/18608.0f);

    for (ii = 0; ii < size; ii++) {
        Window[ii] = (f32_t)(a0 - a1 * (cosf((2 * M_PI * (f32_t)ii) / (f32_t)(size -1))) + a2 * (cosf((4 * M_PI * (f32_t)ii) / (f32_t)(size -1))) );
    }
}

// Calculate a Blackman-Harris window function
void rsp_lib_BlackmanHarrisWindow(f32_t *Window,int32_t size)
{

    int32_t ii;
    const f32_t a0 = 0.35875f;
    const f32_t a1 = 0.48829f;
    const f32_t a2 = 0.14128f;
    const f32_t a3 = 0.01168f;

    for (ii = 0; ii < size; ii++) {
        Window[ii] = (f32_t)(a0 - a1 * (cosf((2 * M_PI * (f32_t)ii) / (f32_t)(size -1))) + a2 * (cosf((4 * M_PI * (f32_t)ii) / (f32_t)(size -1))) - a3 * (cosf((6 * M_PI * (f32_t)ii) / (f32_t)(size -1))));
    }
}



void rsp_lib_fft_c2c_1d_float32(ne10_fft_cpx_float32_t *dst, ne10_fft_cpx_float32_t *src, int32_t fftlen)
{
	switch(fftlen)
	{
	case	32768: ne10_fft_c2c_1d_float32(dst, src, rsp_lib_fftcfg_32K, 0); break;
	case	16384: ne10_fft_c2c_1d_float32(dst, src, rsp_lib_fftcfg_16K, 0); break;
	case	8192: ne10_fft_c2c_1d_float32(dst, src, rsp_lib_fftcfg_8K, 0); break;
	case	4096: ne10_fft_c2c_1d_float32(dst, src, rsp_lib_fftcfg_4K, 0); break;
	case	2048: ne10_fft_c2c_1d_float32(dst, src, rsp_lib_fftcfg_2K, 0); break;
	case	1024: ne10_fft_c2c_1d_float32(dst, src, rsp_lib_fftcfg_1K, 0); break;
	case	512: ne10_fft_c2c_1d_float32(dst, src, rsp_lib_fftcfg_512, 0); break;
	case	256: ne10_fft_c2c_1d_float32(dst, src, rsp_lib_fftcfg_256, 0); break;
	case	128: ne10_fft_c2c_1d_float32(dst, src, rsp_lib_fftcfg_128, 0); break;
	case	64: ne10_fft_c2c_1d_float32(dst, src, rsp_lib_fftcfg_64, 0); break;
	case	32: ne10_fft_c2c_1d_float32(dst, src, rsp_lib_fftcfg_32, 0); break;
	default: break;
	}
}


