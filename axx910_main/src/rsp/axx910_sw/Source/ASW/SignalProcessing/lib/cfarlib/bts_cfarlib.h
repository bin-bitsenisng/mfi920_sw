#ifndef _BTS_CFARLIB_H_
#define _BTS_CFARLIB_H_

/**************************************************************************************
-------------------------------------   include   -------------------------------------
**************************************************************************************/
#include <stdint.h>
#include <stdio.h>

/**************************************************************************************
-------------------------------------   define   --------------------------------------
**************************************************************************************/
#define CFARLIB_CFARCELL_MAX			32
#define CFARLIB_CFAREXTSCELL_MAX		1500

/**************************************************************************************
----------------------------------   Data Struct   ------------------------------------
**************************************************************************************/
#ifndef float32_t
typedef float   float32_t;
typedef double  float64_t;
#endif


typedef enum
{
	CA_CFAR = 0,
	CAGO_CFAR,
	CASO_CFAR,
	GOS_CFAR,
	GOSGO_CFAR,
	GOSSO_CFAR,

} CfarType_t;


typedef enum
{
	EXTENSION_OFF = 0,
	RANGE_EXTENSION,
	DOPP_EXTENSION,

} Extension_t;


typedef struct
{
	CfarType_t eCfarType;
	Extension_t eExtsType;
	uint16_t u16NumCells;	
	uint8_t u8GuardCells;
	uint8_t u8RefCells;
	uint8_t u8ExtsSize;
	uint8_t u8KthOrder;
	float32_t f32Alpha;
	float32_t f32BaseTh;
	float32_t f32AccumSum[CFARLIB_CFAREXTSCELL_MAX];
} CfarCfg_t;


/**************************************************************************************
--------------------------------   global variables   ---------------------------------
**************************************************************************************/


/**************************************************************************************
-------------------------------   function prototypes   -------------------------------
**************************************************************************************/
extern void cfarlib_vCA_cfar_range(float32_t* cfarIn, uint8_t* cfarOut, CfarCfg_t* cfg, float32_t* accumSum, uint16_t acnt, float32_t* cfarTh, uint16_t offset);
extern void cfarlib_vCA_cfar_doppler(float32_t* cfarIn, uint8_t* cfarOut, CfarCfg_t* cfg, float32_t* accumSum, uint16_t acnt, float32_t* cfarTh, uint16_t offset, float32_t ri_norm);
extern void cfarlib_vOS_cfar_doppler(float32_t* cfarIn, uint8_t* cfarOut, CfarCfg_t* cfg, float32_t* cfarTh);

extern uint16_t cfarlib_u16Spectrum_Extns(float32_t* PowIn, float32_t* PowOut, CfarCfg_t* cfg);
extern uint16_t cfarlib_u16Spectrum_Trunc(uint8_t* ExtCfarOut, uint8_t* cfarOut, CfarCfg_t* cfg, float32_t* ExtcfarTh, float32_t* cfarTh);

/**************************************************************************************
--------------------------------------   Macro   --------------------------------------
**************************************************************************************/
#define _cfarlib_abs(a)		(((a)>=(0))?(a):(-(a)))
#define _cfarlib_min(a,b)	(((a)<(b))?(a):(b))
#define _cfarlib_max(a,b)	(((a)>(b))?(a):(b))


#endif
