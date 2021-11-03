#ifndef _TRK_MAIN_H_
#define _TRK_MAIN_H_
#ifdef __cplusplus
extern "C" {
#endif
#define TRK_SIMULATION_MODE		0

/**************************************************************************************
-------------------------------------   include   -------------------------------------
**************************************************************************************/
#if TRK_SIMULATION_MODE
#include "../Mex/Mex_Main.h"
#else
#include "Sp_Main.h"
#endif
#include "Trk_Parameters.h"
#include "Trk_Freespace.h"


/**************************************************************************************
-------------------------------------   define   --------------------------------------
**************************************************************************************/


/**************************************************************************************
----------------------------------   Data Struct   ------------------------------------
**************************************************************************************/
typedef enum
{
	INVALID = 0,
	NEW_TRACK = 1,
	UPDATED_TRACK = 2,
	COASTED_TRACK = 3

} TrkStatus_t;


typedef enum
{
	INVALID_CLST = 0,
	VALID_CLST = 1,
	ASSO_CLST = 2

} ClstStatus_t;


typedef enum
{
	NOISE_PTS = 0,
	CORE_PTS = 1,
	BORDER_PTS = 2

} ClstPtsStatus_t;


typedef enum
{
	NOT_TARGET = 0,
	NEW_TARGET = 1,
	VERIFIED_TARGET = 2

} TrkOutStatus_t;


typedef enum
{
	REF_FRONT_LEFT = 0,
	REF_FRONT = 1,
	REF_FRONT_RIGHT = 2,
	REF_RIGHT = 3,
	REF_REAR_RIGHT = 4,
	REF_REAR = 5,
	REF_REAR_LEFT = 6,
	REF_LEFT = 7,
	REF_CENTER = 8,
	REF_INVALID = 9

} RefPosition_t;


typedef enum
{
	COASTING = 0,
	UPDATED = 1

} TrkOutUpdState_t;


typedef enum
{
	STATIONARY = 0,
	PRECEDING = 1,
	ONCOMING = 2,
	STOPPED = 3,
	MOV_STATE_TOTAL = 4

} MovState_t;


typedef enum
{
	REFLECT_TYPE_UNKNOWN = 0,
	REFLECT_TYPE_STATIONARY = 1,
	REFLECT_TYPE_BODY = 2,
	REFLECT_TYPE_WHEEL = 3,
	REFLECT_TYPE_TOTAL = 4

} ReflectType_t;


typedef enum
{
	OBJCLASS_BIKE = 0,
	OBJCLASS_BUS = 1,
	OBJCLASS_CAR = 2,
	OBJCLASS_MOTOR = 3,
	OBJCLASS_PEDESTRIAN = 4,
	OBJCLASS_RIDER = 5,
	OBJCLASS_TRAFFIC_LIGHT = 6,
	OBJCLASS_TRAFFIC_SIGN = 7,
	OBJCLASS_TRAIN = 8,
	OBJCLASS_TRUCK = 9,
	OBJCLASS_UNKNOWN = 10

} ObjectClass_t;


typedef enum
{
	SF_DEFAULT = 0,
	SF_RADAR_ONLY = 1,
	SF_VISION_ONLY = 2,
	SF_FUSION_MOVING = 3,
	SF_FUSION_STATIONARY = 4

} FusionState_t;


typedef enum
{
	RB_ERROR_NONE = 0,
	RB_ERROR_INIT = 1,
	RB_ERROR_UNDER_ACT_SPD = 2,
	RB_ERROR_LON_NUM_MEAS = 3,
	RB_ERROR_LOW_NUM_INLIER = 4,
	RB_ERROR_SMALL_INLIER = 5

} RoadBoundaryErrorType_t;


typedef struct
{
	float32_t f32VehSpeed_can;		// mps
	float32_t f32VehSpeed_comp;
	float32_t f32YawRate_can;		// dps
	float32_t f32YawRate_comp;
	float32_t f32SteerAng_deg;
	float32_t f32WheelAng_deg;
	float32_t f32PathRadius;

	float32_t f32VelX;
	float32_t f32VelY;
	float32_t f32DeltaYaw_deg;
	float32_t f32wheelfl;
	float32_t f32wheelfr;
	float32_t f32wheelrl;
	float32_t f32wheelrr;

	float32_t prev_VehSpeed;
	float32_t prev_YawRate;
	float32_t prev_SteerAngle;
	int8_t	  init_flag;
} TrkEgoMotionInfo_t;


typedef struct
{
	float32_t F[2][2];
	float32_t F_Trs[2][2];

	float32_t H[2][2];
	float32_t H_Trs[2][2];

	float32_t I[2][2];

	float32_t Qx[2][2];
	float32_t Qy[2][2];

} KalmanParam_t;


typedef struct
{
	uint32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;

} BoundingBox_t;


typedef struct
{
	float32_t	f32Mean;
	float32_t	f32StdDev;
	float32_t 	f32Min;
	float32_t	f32Max;

} Distribution_t;


typedef struct
{
	float32_t f32StateX[2];
	float32_t f32StateY[2];

	float32_t f32Ref_PosX;
	float32_t f32Ref_PosY;

	float32_t f32BoundingBoxX[4];
	float32_t f32BoundingBoxY[4];

	float32_t f32Length;
	float32_t f32Width;
	float32_t f32StateHeading[2];
	float32_t f32StateSpeed[2];

} TrkState_t;


typedef struct
{
	float32_t Px[2][2];
	float32_t Py[2][2];

	float32_t Kx[2][2];
	float32_t Ky[2][2];

	float32_t Rx[2][2];
	float32_t Ry[2][2];

} KalmanData_t;


typedef struct
{
	int16_t   s16ObjNum;
	uint8_t   u8ModType;

	float32_t f32Range3d_rdr;
	float32_t f32Range_rdr;

	float32_t f32RangeRate3d_rdr;
	float32_t f32RangeRate_rdr;
	float32_t f32RangeRate_comp;

	float32_t f32AziAng_rdr;
	float32_t f32AziAng;
	float32_t f32EleAng_rdr;
	float32_t f32EleAng;

	float32_t f32PosX;
	float32_t f32PosY;
	float32_t f32PosZ;
	
	float32_t f32Pow_dB;
	MovState_t MovState;

	ClstPtsStatus_t Cluster_PtsStat;
	int16_t 	 	s16Cluster_idx;
	uint8_t 	 	u8Cluster_visited;
	
	ReflectType_t ReflectType;
	int16_t ReflectTypeProb;	/* >0: body, <0: wheel, 0: unknown */
	int16_t nUpMeas; // 

	uint8_t rb_flag;

} MeasData_t;


typedef struct
{
	int16_t region_idx;

	float32_t range_min;
	float32_t range_max;

	float32_t dbscan_eps;
	int16_t dbscan_min_pts;

	float32_t max_diff_rangerate;
	int16_t max_num_neighbor;

} DbscanParam_t;

typedef struct
{
	int16_t			s16Idx;
	ClstStatus_t	State;
	MovState_t		MovState;

	int16_t			MeasIdx[TRK_CLST_NUM_NEIGHBOR_MAX];
	int16_t			CoreIdx[TRK_CLST_NUM_NEIGHBOR_MAX];
	int16_t			MeasNum;
	int16_t			CoreNum;

	Distribution_t	Xpos;
	Distribution_t	Ypos;
	Distribution_t	Range;
	Distribution_t	RangeRate;
	Distribution_t	RangeRate_rdr;
	Distribution_t	AziAng;
	Distribution_t  EleAng;
	Distribution_t	Power;
	float32_t		RotationAngle;

	int16_t			s16AssoClstIdx;
	float32_t		f32AssoClstCost;

	ReflectType_t	ReflectType;

	/* vision object matching */
	int16_t			MatchVisionObjIdx;
	float32_t		AzimuthOverlapRatio;


} MeasClst_t;


typedef struct
{
	TrkStatus_t Status;
	MovState_t MovState;
	
	uint16_t u16AliveAge;
	uint16_t u16StatusAge;
	int16_t s16NewTrkTrans_Score;
	int16_t s16MoveStateCnt;

	float32_t f32PredStateX[2];
	float32_t f32PredStateY[2];
	float32_t f32UpdStateX[2];
	float32_t f32UpdStateY[2];
	float32_t f32AccelX;
	float32_t f32AccelY;

	KalmanData_t Kalman;
	
	int16_t	  s16AssoMeasClstCnt;
	int16_t   s16AssoMeasClstIdx[TRK_NUM_MEAS_CLST_ASSOCIATION_MAX];

	int16_t	  s16AssoMeasNoisePtCnt;
	int16_t   s16AssoMeasNoisePtIdx[TRK_NUM_MEAS_NOISEPT_ASSOCIATION_MAX];

	int16_t   s16GroupTrkIdx;
	int16_t   s16GroupInconsistentCnt;

	float32_t f32Mean_Range;
	float32_t f32Std_Range;
	float32_t f32Mean_RangeRate;
	float32_t f32Std_RangeRate;
	float32_t f32Mean_Azimuth;
	float32_t f32Std_Azimuth;
	float32_t f32Mean_Xpos;
	float32_t f32Std_Xpos;
	float32_t f32Mean_Ypos;
	float32_t f32Std_Ypos;
	float32_t f32Mean_Pow_dB;
	float32_t f32Std_Pow_dB;
	float32_t f32MaxPow_dB;

	/* Stationary vision object matching */
	uint16_t MatchVision0bjIdx;

} ClstData_t;


typedef struct
{
	TrkStatus_t Status;
	uint16_t u16AliveAge;
	uint16_t u16StatusAge;

	TrkState_t PredState;
	TrkState_t UpdState;
	TrkState_t MeasState;
	float32_t f32PosZ;
	float32_t f32Height;

	float32_t f32AccX;
	float32_t f32AccY;

	RefPosition_t RefPt;
	MovState_t MovState;

	int16_t s16GroupClstCnt;
	int16_t s16GroupClstIdx[TRK_NUM_GROUP_CLST_MAX];

	uint8_t u8Merging_Flag;

	float32_t Ph[2][2];
	float32_t Kh[2];

	float32_t f32Pow_dB;
	float32_t f32MaxPow_dB;

	uint8_t ghost_flag;

	/* Sensor Fusion */
	/* sensor fusion - Update by vision object */
	FusionState_t fusion_state;
	int16_t FusionAge;

	/* sensor fusion - azimuth correction */
	BoundingBox_t bbox_img;	/* x, y, width, height */
	float32_t radar_obj_gnd_img[3];
	float32_t vision_obj_gnd_img[3];
	float32_t bbox_overlap_ratio;
	int16_t match_vision_obj_idx;
	float32_t tl_delta[2];

	/* sensor fusion - class decision */
	ObjectClass_t obj_class;
	float32_t obj_class_cnt[TRK_SENSOR_FUSION_CLASS_TYPE_MAX];
	float32_t obj_class_prob;

} TrackData_t;


typedef struct
{
	TrkOutStatus_t Status;
	TrkOutUpdState_t UpdState;
	TrkState_t TrkState;
	MovState_t MovState;
	uint16_t  u16AliveAge;
	float32_t f32PosX;
	float32_t f32VelX;
	float32_t f32PosY;
	float32_t f32VelY;
	float32_t f32RefPosX;
	float32_t f32RefPosY;
	float32_t f32Width;
	float32_t f32Length;
	float32_t f32Pow_dB;
	float32_t f32MaxPow_dB;
	float32_t f32HeadingAng;
	int16_t s16UpdPoint;
	uint32_t u32ObjClass;
	uint32_t u32FusionType;
	float32_t f32PosZ;
	float32_t f32Height;

} TrackOut_t;


typedef struct
{
	/* Input data from inference */
	int16_t			obj_id;
	ObjectClass_t	class_id;
	float32_t		confidence;
	BoundingBox_t	bbox_img;

	float32_t		bbox_corner_wld[2][4]; /* [left/right][x/y] */
	FusionState_t	fusion_state;
	int16_t			match_radar_obj_idx;

	/* azimuth range */
	Distribution_t	AziAng;

	/* measurement cluster matching */
	int16_t			MatchMeasClstIdx;
	float32_t		AzimuthOverlapRatio;

} VisionObjData_t;


typedef struct
{
	/* Image size: width, height */
	int32_t image_size[2];

	/* Intrinsic */
	float32_t K[3][3];

	/* Radial distrotion coefficient */
	float32_t k1;
	float32_t k2;
	float32_t k3;
	
	/* Tangential distortion coefficient */
	float32_t p1;
	float32_t p2;
	
	/* Extrinsic */
	float32_t R[3][3];	/* Roatation matrix */
	float32_t t[3];		/* Translation vector */

	/* Projection matrix (wld2img) */
	float32_t P[3][4];

	/* Homography matrix (img2wld) */
	float32_t H[3][3];

} CameraParam_t;


typedef struct
{
	/*  
	* @ Angle Resol : 1deg	,
	* @ array index - [0]: -45 [1]:-44, ...[45]: 0, , [89]: 45 deg
	*/	

	int32_t fFreeRange[90]; 	
	
} FreeSpaceOut_t;


typedef struct
{
	float32_t quad_coef[3];
	float32_t rb_conf[TRK_RB_CONF_MAP_NUM_BIN];	/* x directional probability map of inliers of road boundary */
	float32_t rb_y_pos[TRK_RB_CONF_MAP_NUM_BIN];
	float32_t rb_y_min[TRK_RB_CONF_MAP_NUM_BIN];

	int32_t rb_x_min;
	int32_t rb_x_max;
	
	int32_t meas_filter[TRK_NUM_MEAS_MAX];
	int32_t n_meas_filter;

	int32_t inliers[TRK_NUM_MEAS_MAX];
	int32_t n_inliers;

	RoadBoundaryErrorType_t error_flag;
	int32_t pass_sampling_cnt;

} RoadBoundary_t;


/**************************************************************************************
--------------------------------   global variables   ---------------------------------
**************************************************************************************/
extern float32_t			gTrkCycleTime;
extern int16_t				gMeasCnt;
extern TrkEgoMotionInfo_t 	gTrkEgoMotionInfo;
extern KalmanParam_t		KalmanParam;
extern MeasData_t 			gMeasData[TRK_NUM_MEAS_MAX];
extern MeasClst_t 			gMeasClst[TRK_NUM_CLUSTER_MAX];
extern ClstData_t			gClstData[TRK_NUM_CLUSTER_MAX];
extern TrackData_t 			gTrackData[TRK_NUM_TRACK_MAX];
extern TrackOut_t 			gTrackOut[TRK_NUM_TRACK_MAX];
extern VisionObjData_t		gVisionObj[TRK_NUM_TRACK_MAX];
extern int16_t				gVisionObjCnt;
extern CameraParam_t		gCameraParam;
extern int16_t				gMsclCnt;
extern FreeSpaceOut_t		gFreespaceOut;
extern RoadBoundary_t		gRoadBoundary[2];

/**************************************************************************************
-------------------------------   function prototypes   -------------------------------
**************************************************************************************/
extern void Trk_vMain(void);
extern void Trk_vSysInit(void);

extern void MatInv3x3(float32_t src[][3], float32_t dst[][3]);
extern void img2wld(float32_t img[3], float32_t wld[3], float32_t H[][3]);
extern void wld2img(float32_t wld[4], float32_t img[3], float32_t P[][4]);

/**************************************************************************************
--------------------------------------   Macro   --------------------------------------
**************************************************************************************/

#define RotateX(x,y,a)						( ((x)*cosf((a)*0.017453292519943f)) - ((y)*sinf((a)*0.017453292519943f)))
#define RotateY(x,y,a)						( ((x)*sinf((a)*0.017453292519943f)) + ((y)*cosf((a)*0.017453292519943f)))
#define NegRotateX(x,y,a)					( ((x)*cosf((a)*0.017453292519943f)) + ((y)*sinf((a)*0.017453292519943f)))
#define NegRotateY(x,y,a)					(-((x)*sinf((a)*0.017453292519943f)) + ((y)*cosf((a)*0.017453292519943f)))

#define _trk_abs(x)							((x) < 0 ? (-(x)) : (x))
#define _trk_bound(x, x_min, x_max)			( ( (x) < (x_min) ) ? (x_min) : ( ( (x) > (x_max) ) ? (x_max) : (x) ) )
#define _trk_isbound(x, x_min, x_max)		( ( (x) < (x_min) ) ? 0 : ( ((x) > (x_max)) ? 0 : 1 ) )
#define _trk_max(a,b)						( ( (a) > (b)) ? (a) : (b) )
#define _trk_min(a,b)						( ( (a) < (b)) ? (a) : (b) )
#define _trk_roundf(x)						(roundf(x))
#define _trk_pow2(x)						((x)*(x))
#define _trk_sqrtf(x)						sqrtf((x))
#define _trk_hypotf(x,y)					sqrtf( ((x)*(x)) + ((y)*(y)) )

#define _trk_deg2rad(a)						( (a) * TRK_DEG2RAD )
#define _trk_rad2deg(a)						( (a) * TRK_RAD2DEG )
#define _trk_sinf(x)						( sinf( (x) ) )
#define _trk_sindf(x)						( sinf( (x) * TRK_DEG2RAD ) )
#define _trk_cosf(x)						( cosf( (x) ) )
#define _trk_cosdf(x)						( cosf( (x) * TRK_DEG2RAD ) )
#define _trk_atandf(x)						( atanf( (x) ) * TRK_RAD2DEG )
#define _trk_atan2f(y,x)					( atan2f( (y), (x) ) )
#define _trk_atan2df(y,x)					( atan2f( (y), (x) ) * TRK_RAD2DEG )

#define val2bin(val, min, max, size)		( ((val) == (max)) ? (size - 1) : roundf((val - min) / (max - min) * size) )
#define bin2val(bin, min, max, size)		(bin / size * (max - min) + min)

/* Matrix operation */
#define MatInit_3x3(a)						a[0][0] = 0;\
											a[0][1] = 0;\
											a[0][2] = 0;\
											a[1][0] = 0;\
											a[1][1] = 0;\
											a[1][2] = 0;\
											a[2][0] = 0;\
											a[2][1] = 0;\
											a[2][2] = 0;\

#define MatMul_3x3and3x3(a, b, c)			c[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0];\
											c[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1] + a[0][2]*b[2][1];\
											c[0][2] = a[0][0]*b[0][2] + a[0][1]*b[1][2] + a[0][2]*b[2][2];\
											c[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0] + a[1][2]*b[2][0];\
											c[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1];\
											c[1][2] = a[1][0]*b[0][2] + a[1][1]*b[1][2] + a[1][2]*b[2][2];\
											c[2][0] = a[2][0]*b[0][0] + a[2][1]*b[1][0] + a[2][2]*b[2][0];\
											c[2][1] = a[2][0]*b[0][1] + a[2][1]*b[1][1] + a[2][2]*b[2][1];\
											c[2][2] = a[2][0]*b[0][2] + a[2][1]*b[1][2] + a[2][2]*b[2][2];\

#define MatMul_3x3and3x2(a, b, c)			c[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0];\
											c[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1] + a[0][2]*b[2][1];\
											c[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0] + a[1][2]*b[2][0];\
											c[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1];\
											c[2][0] = a[2][0]*b[0][0] + a[2][1]*b[1][0] + a[2][2]*b[2][0];\
											c[2][1] = a[2][0]*b[0][1] + a[2][1]*b[1][1] + a[2][2]*b[2][1];\

#define MatMul_3x3and3x1(a, b, c)			c[0] = a[0][0]*b[0] + a[0][1]*b[1] + a[0][2]*b[2];\
											c[1] = a[1][0]*b[0] + a[1][1]*b[1] + a[1][2]*b[2];\
											c[2] = a[2][0]*b[0] + a[2][1]*b[1] + a[2][2]*b[2];\

#define MatMul_3x3and3x4(a, b, c)			c[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0];\
											c[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1] + a[0][2]*b[2][1];\
											c[0][2] = a[0][0]*b[0][2] + a[0][1]*b[1][2] + a[0][2]*b[2][2];\
											c[0][3] = a[0][0]*b[0][3] + a[0][1]*b[1][3] + a[0][2]*b[2][3];\
											c[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0] + a[1][2]*b[2][0];\
											c[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1];\
											c[1][2] = a[1][0]*b[0][2] + a[1][1]*b[1][2] + a[1][2]*b[2][2];\
											c[1][3] = a[1][0]*b[0][3] + a[1][1]*b[1][3] + a[1][2]*b[2][3];\
											c[2][0] = a[2][0]*b[0][0] + a[2][1]*b[1][0] + a[2][2]*b[2][0];\
											c[2][1] = a[2][0]*b[0][1] + a[2][1]*b[1][1] + a[2][2]*b[2][1];\
											c[2][2] = a[2][0]*b[0][2] + a[2][1]*b[1][2] + a[2][2]*b[2][2];\
											c[2][3] = a[2][0]*b[0][3] + a[2][1]*b[1][3] + a[2][2]*b[2][3];\

#define MatMul_3x4and4x1(a, b, c)			c[0] = a[0][0]*b[0] + a[0][1]*b[1] + a[0][2]*b[2] + a[0][3]*b[3];\
											c[1] = a[1][0]*b[0] + a[1][1]*b[1] + a[1][2]*b[2] + a[1][3]*b[3];\
											c[2] = a[2][0]*b[0] + a[2][1]*b[1] + a[2][2]*b[2] + a[2][3]*b[3];\

#define MatMul_3x2and2x3(a, b, c)			c[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0];\
											c[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1];\
											c[0][2] = a[0][0]*b[0][2] + a[0][1]*b[1][2];\
											c[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0];\
											c[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1];\
											c[1][2] = a[1][0]*b[0][2] + a[1][1]*b[1][2];\
											c[2][0] = a[2][0]*b[0][0] + a[2][1]*b[1][0];\
											c[2][1] = a[2][0]*b[0][1] + a[2][1]*b[1][1];\
											c[2][2] = a[2][0]*b[0][2] + a[2][1]*b[1][2];\

#define MatMul_3x2and2x2(a, b, c)			c[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0];\
											c[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1];\
											c[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0];\
											c[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1];\
											c[2][0] = a[2][0]*b[0][0] + a[2][1]*b[1][0];\
											c[2][1] = a[2][0]*b[0][1] + a[2][1]*b[1][1];\

#define MatMul_3x2and2x1(a, b, c)			c[0] = a[0][0]*b[0] + a[0][1]*b[1];\
											c[1] = a[1][0]*b[0] + a[1][1]*b[1];\
											c[2] = a[2][0]*b[0] + a[2][1]*b[1];\

#define MatMul_2x3and3x3(a, b, c)			c[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0];\
											c[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1] + a[0][2]*b[2][1];\
											c[0][2] = a[0][0]*b[0][2] + a[0][1]*b[1][2] + a[0][2]*b[2][2];\
											c[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0] + a[1][2]*b[2][0];\
											c[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1];\
											c[1][2] = a[1][0]*b[0][2] + a[1][1]*b[1][2] + a[1][2]*b[2][2];\

#define MatMul_2x3and3x2(a, b, c)			c[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0] + a[0][2]*b[2][0];\
											c[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1] + a[0][2]*b[2][1];\
											c[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0] + a[1][2]*b[2][0];\
											c[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1] + a[1][2]*b[2][1];\

#define MatMul_2x2and2x2(a, b, c)			c[0][0] = a[0][0]*b[0][0] + a[0][1]*b[1][0];\
											c[0][1] = a[0][0]*b[0][1] + a[0][1]*b[1][1];\
											c[1][0] = a[1][0]*b[0][0] + a[1][1]*b[1][0];\
											c[1][1] = a[1][0]*b[0][1] + a[1][1]*b[1][1];\

#define MatMul_2x2and2x1(a, b, c)			c[0] = a[0][0]*b[0] + a[0][1]*b[1];\
											c[1] = a[1][0]*b[0] + a[1][1]*b[1];\

#define MatAdd_3x3(a, b, c)					c[0][0] = a[0][0] + b[0][0];\
											c[0][1] = a[0][1] + b[0][1];\
											c[0][2] = a[0][2] + b[0][2];\
											c[1][0] = a[1][0] + b[1][0];\
											c[1][1] = a[1][1] + b[1][1];\
											c[1][2] = a[1][2] + b[1][2];\
											c[2][0] = a[2][0] + b[2][0];\
											c[2][1] = a[2][1] + b[2][1];\
											c[2][2] = a[2][2] + b[2][2];\

#define MatAdd_3x1(a, b, c)					c[0] = a[0] + b[0];\
											c[1] = a[1] + b[1];\
											c[2] = a[2] + b[2];\

#define MatAdd_2x2(a, b, c)					c[0][0] = a[0][0] + b[0][0];\
											c[0][1] = a[0][1] + b[0][1];\
											c[1][0] = a[1][0] + b[1][0];\
											c[1][1] = a[1][1] + b[1][1];\

#define MatAdd_2x1(a, b, c)					c[0] = a[0] + b[0];\
											c[1] = a[1] + b[1];\

#define MatSub_2x1(a, b, c)					c[0] = a[0] - b[0];\
											c[1] = a[1] - b[1];\

#define MatSub_3x3(a, b, c)					c[0][0] = a[0][0] - b[0][0];\
											c[0][1] = a[0][1] - b[0][1];\
											c[0][2] = a[0][2] - b[0][2];\
											c[1][0] = a[1][0] - b[1][0];\
											c[1][1] = a[1][1] - b[1][1];\
											c[1][2] = a[1][2] - b[1][2];\
											c[2][0] = a[2][0] - b[2][0];\
											c[2][1] = a[2][1] - b[2][1];\
											c[2][2] = a[2][2] - b[2][2];\

#define MatSub_2x2(a, b, c)					c[0][0] = a[0][0] - b[0][0];\
											c[0][1] = a[0][1] - b[0][1];\
											c[1][0] = a[1][0] - b[1][0];\
											c[1][1] = a[1][1] - b[1][1];\

#define MatTranspose_3x3(a, b)				b[0][0] = a[0][0];\
											b[0][1] = a[1][0];\
											b[0][2] = a[2][0];\
											b[1][0] = a[0][1];\
											b[1][1] = a[1][1];\
											b[1][2] = a[2][1];\
											b[2][0] = a[0][2];\
											b[2][1] = a[1][2];\
											b[2][2] = a[2][2];\

#define MatTranspose_2x2(a, b)				b[0][0] = a[0][0];\
											b[0][1] = a[1][0];\
											b[1][0] = a[0][1];\
											b[1][1] = a[1][1];\

#define MatTranspose_2x3(a, b)				b[0][0] = a[0][0];\
											b[0][1] = a[1][0];\
											b[1][0] = a[0][1];\
											b[1][1] = a[1][1];\
											b[2][0] = a[0][2];\
											b[2][1] = a[1][2];\

#define MatInverse_2x2(a, b)				b[0][0] =  a[1][1] / ((a[0][0]*a[1][1]) - (a[0][1]*a[1][0]));\
											b[0][1] = -a[0][1] / ((a[0][0]*a[1][1]) - (a[0][1]*a[1][0]));\
											b[1][0] = -a[1][0] / ((a[0][0]*a[1][1]) - (a[0][1]*a[1][0]));\
											b[1][1] =  a[0][0] / ((a[0][0]*a[1][1]) - (a[0][1]*a[1][0]));\

#define MatCopy_3x3(a, b)					b[0][0] = a[0][0];\
											b[0][1] = a[0][1];\
											b[0][2] = a[0][2];\
											b[1][0] = a[1][0];\
											b[1][1] = a[1][1];\
											b[1][2] = a[1][2];\
											b[2][0] = a[2][0];\
											b[2][1] = a[2][1];\
											b[2][2] = a[2][2];\

#define MatCopy_2x2(a, b)					b[0][0] = a[0][0];\
											b[0][1] = a[0][1];\
											b[1][0] = a[1][0];\
											b[1][1] = a[1][1];\

#define MatConcat_3x3_3x1(a, b, c)			c[0][0] = a[0][0];\
											c[0][1] = a[0][1];\
											c[0][2] = a[0][2];\
											c[0][3] = b[0];\
											c[1][0] = a[1][0];\
											c[1][1] = a[1][1];\
											c[1][2] = a[1][2];\
											c[1][3] = b[1]; \
											c[2][0] = a[2][0];\
											c[2][1] = a[2][1];\
											c[2][2] = a[2][2];\
											c[2][3] = b[2];\

#define MatRotX(rad, rot)					rot[0][0] = 1.0f;\
											rot[0][1] = 0.0f;\
											rot[0][2] = 0.0f;\
											rot[1][0] = 0.0f;\
											rot[1][1] = cosf(rad);\
											rot[1][2] = -sinf(rad);\
											rot[2][0] = 0.0f;\
											rot[2][1] = sinf(rad);\
											rot[2][2] = cosf(rad);\

#define MatRotY(rad, rot)					rot[0][0] = cosf(rad);\
											rot[0][1] = 0.0f;\
											rot[0][2] = sinf(rad);\
											rot[1][0] = 0.0f;\
											rot[1][1] = 1.0f;\
											rot[1][2] = 0.0f;\
											rot[2][0] = -sinf(rad);\
											rot[2][1] = 0.0f;\
											rot[2][2] = cosf(rad);\

#define MatRotZ(rad, rot)					rot[0][0] = cosf(rad);\
											rot[0][1] = -sinf(rad);\
											rot[0][2] = 0.0f;\
											rot[1][0] = sinf(rad);\
											rot[1][1] = cosf(rad);\
											rot[1][2] = 0.0f;\
											rot[2][0] = 0.0f;\
											rot[2][1] = 0.0f;\
											rot[2][2] = 1.0f;\

#define MatRot2x2(rad, rot)					rot[0][0] = cosf(rad);\
											rot[0][1] = -sinf(rad);\
											rot[1][0] = sinf(rad);\
											rot[1][1] = cosf(rad);\

#define MatAbs2x1(src, dst)					dst[0] = _trk_abs(src[0]);\
											dst[1] = _trk_abs(src[1]);\

#ifdef __cplusplus
}
#endif

#endif