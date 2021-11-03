#ifndef _SP_MAIN_H_
#define _SP_MAIN_H_
#ifdef __cplusplus
extern "C" {
#endif
/**************************************************************************************
-------------------------------------   include   -------------------------------------
**************************************************************************************/
/* Standard Include Files. */
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "Sp_TypeDef.h"
#include "Sp_Parameters.h"
#include "rsp_lib.h"


/**************************************************************************************
-------------------------------------   define   --------------------------------------
**************************************************************************************/
#ifndef LINUX
#define AI_OBJECT_MAX_SIZE             300
#endif

/**************************************************************************************
----------------------------------   Data Struct   ------------------------------------
**************************************************************************************/
typedef enum
{
	PRF_1ST = 0,
} MultiPRF_t;

typedef enum
{
	LR_MOD = 0,
	MR_MOD = 1,
	SR_MOD = 2,
	RM_MOD = 3,
} MultiMod_t;

typedef struct
{
	uint8_t u8ModType;
	float32_t f32Range_m;
	float32_t f32Velocity_mps;
	float32_t f32AziAng_deg;
	float32_t f32EleAng_deg;
	float32_t f32Power_dB;

} SpObjectOut_t;


typedef struct
{
	int8_t s8Idx;
	uint8_t u8Status;
	uint8_t u8UpdState;
	uint8_t u8MovState;
	uint8_t u16AliveAge;
	float32_t f32PosX_m;
	float32_t f32PosY_m;
	float32_t f32RefPosX_m;
	float32_t f32RefPosY_m;
	float32_t f32VelX_mps;
	float32_t f32VelY_mps;
	float32_t f32HeadingAng_deg;
	float32_t f32Power_dB;
	float32_t f32Width_m;
	float32_t f32Length_m;
	uint32_t u32ObjClass;
	uint32_t u32FusionType;
	float32_t f32PosZ;
	float32_t f32Height;

} SpTrackOut_t;


typedef struct
{
	float32_t f32PosX;
	float32_t f32PosY;
	float32_t f32PosZ;
	float32_t f32Reverse;
	float32_t f32AziAng;
	float32_t f32EleAng;

} RadarInst_t;


typedef struct
{
    uint8_t u8PRFType;
    uint16_t u16SMPLNum;
    uint16_t u16CycleTime;
	int16_t s16LRPeakCnt;
	int16_t s16MRPeakCnt;
	int16_t s16SRPeakCnt;

} SpLogInfo_t;


typedef struct
{
	float32_t f32VehSpeed_mps;
	float32_t f32YawRate_degps;
	float32_t f32SteerAng_deg;
	float32_t f32PathRadius;

} EgoMotionInfo_t;


#ifndef LINUX

typedef struct
{
	float32_t vehicle_speed;
	float32_t wheel_speed_fl;
	float32_t wheel_speed_fr;
	float32_t wheel_speed_rl;
	float32_t wheel_speed_rr;
	float32_t steerangle;
	float32_t steeranglespeed;
	float32_t yawrate;
	float32_t longaccel;
	float32_t lataccel;

} can_sig_data_t;


typedef struct
{
	uint32_t Ai_num_of_class;
	uint32_t Ai_class_id;
	float Ai_confidence;
	uint32_t Ai_height;
	uint32_t Ai_width;
	uint32_t Ai_x_location;
	uint32_t Ai_y_location;
} ai_object_t;

#endif



/**************************************************************************************
--------------------------------   global variables   ---------------------------------
**************************************************************************************/
extern MultiPRF_t gSpCurPRF;
extern MultiMod_t gSpCurMod;
extern float32_t gSpCycleTime;
extern int16_t gInitScanFlag;
extern SpObjectOut_t Sp_ObjectOut[SP_NUM_OBJECT_MAX];
extern SpTrackOut_t Sp_TrackOut[SP_NUM_TRACK_MAX];
extern RadarInst_t gRadarInstInfo;
extern SpLogInfo_t Sp_LogInfo;

#ifndef LINUX
extern can_sig_data_t	  can_sig_data;
extern ai_object_t		  ai_object[AI_OBJECT_MAX_SIZE];
#endif

/**************************************************************************************
-------------------------------   function prototypes   -------------------------------
**************************************************************************************/
extern void Sp_vSysInit(void);
extern void Sp_vMain(void);
extern void Sp_vTrackOut(void);

/**************************************************************************************
--------------------------------------   Macro   --------------------------------------
**************************************************************************************/
#define _sp_abs(x)                 ((x) < 0 ? (-(x)) : (x))
#define _sp_sign(x)                ((x) < 0 ? (-1) : (1))
#define _sp_max(a,b)               (((a)>(b))?(a):(b))
#define _sp_min(a,b)               (((a)<(b))?(a):(b))
#define _sp_bound(x, x_min, x_max) (((x)<(x_min))?(x_min):(((x)>(x_max))?(x_max):(x)))
#define _sp_pow2(x)                ((x)*(x))
#define _sp_pow3(x)                ((x)*(x)*(x))

#define _sp_roundf(x)              roundf((x))
#define _sp_sqrtf(x)               sqrtf((x))
#define _sp_hypotf(x,y)            sqrtf(((x)*(x)) + ((y)*(y)))
#define _sp_sinf(x)                sinf((x))
#define _sp_cosf(x)                cosf((x))
#define _sp_tanf(x)                tanf((x))
#define _sp_sindf(x)               sinf(((x)*0.017453292519943f))
#define _sp_cosdf(x)               cosf(((x)*0.017453292519943f))
#define _sp_tandf(x)               tanf(((x)*0.017453292519943f))
#define _sp_asinf(x)               asinf((x))
#define _sp_acosf(x)               acosf((x))
#define _sp_asindf(x)              (asinf((x))*57.295779513082323f)
#define _sp_acosdf(x)              (acosf((x))*57.295779513082323f)
#define _sp_atanf(x)               atanf((x))
#define _sp_atan2f(y,x)            atan2f((y),(x))
#define _sp_atan2df(y,x)           (atan2f((y),(x))*57.295779513082323f)
#define _sp_expf(x)                expf((x))
#define _sp_exp2f(x)               exp2f((x))
#define _sp_log2f(x)               log2f((x))
#define _sp_log10f(x)              log10f((x))
#define _sp_atand(x)		       (atanf((x))*57.295779513082323f)

#define _sp_cnt_break(cnt,th)		if((cnt)>=(th)) {break;}

#ifdef __cplusplus
}
#endif
#endif

