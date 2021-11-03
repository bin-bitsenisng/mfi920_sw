/************************************************************************
 | Project Name: KRS24
 |    File Name: rsp_lib_cfg.h
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

#ifndef RSP_LIB_CFG_H__
#define RSP_LIB_CFG_H__

/* defination for module configuration parameters */

#define NE10_ENABLE_HF
#define NE10_ENABLE_MATH
#define NE10_ENABLE_DSP
//#define NE10_UNROLL_LEVEL 1




#ifndef WIN32
#define ENABLE_NE10_FIR_FLOAT_NEON
#define ENABLE_NE10_FIR_DECIMATE_FLOAT_NEON
#define ENABLE_NE10_FIR_INTERPOLATE_FLOAT_NEON
#define ENABLE_NE10_FIR_LATTICE_FLOAT_NEON
#define ENABLE_NE10_FIR_SPARSE_FLOAT_NEON
#define ENABLE_NE10_IIR_LATTICE_FLOAT_NEON
#endif


#ifdef WIN32
#define __attribute__(x) 
#define asm(x) 

#ifndef M_PI
#define M_PI		3.14159265358979323846f
#endif

#endif

#endif /* RSP_LIB_CFG_H__ */
