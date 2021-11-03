/************************************************************************
 | Project Name: 
 |    File Name: imu.h
 |  Description: detailed Description
 |-----------------------------------------------------------------------
 |               A U T H O R   I D E N T I T Y
 |-----------------------------------------------------------------------
 | Initials     Name                      Company                        
 | --------     ---------------------     -------------------------------
 | MHKIM        Myoungha Kim              bitsensing Corporation
 |-----------------------------------------------------------------------
 |              R E V I S I O N   H I S T O R Y
 |-----------------------------------------------------------------------
 | Date         Ver  Author  Description                                 
 | ----------  ----  ------  --------------------------------------------
 | 2021.01.27  0.0   mhkim   Creation;
 |***********************************************************************/

#ifndef _IMU_H_
#define _IMU_H_

#include "bts.h"
#include "imu_device_cfg.h"

#ifdef IMU_DRV_DEBUG_ENABLE
#define IMU_DRV_LOG krs_log
#else
#define IMU_DRV_LOG krs_log_dummy
#endif


/* module specific types  */
typedef int32_t imu_drv_ret_t;


typedef enum
{
    imu_flip_status_upside,
    imu_flip_status_downside
}imu_flip_status_t;


typedef struct
{
    f32_t ax;
    f32_t ay;
    f32_t az;
    f32_t gx;
    f32_t gy;
    f32_t gz;
    f32_t mx;
    f32_t my;
    f32_t mz;

	f32_t pitch;
	f32_t yaw;
	f32_t roll;
	f32_t q[4]; // quoternion vector
	f32_t temperature_degc;
	f32_t pressure_hpa;
	f32_t altidude_m;
}imu_data_t;


/* define structure for this module */


/* declare extern global variables */
extern imu_data_t imu_data;

/* declare extern global functions */
extern int32_t imu_drv_init(void);
extern int32_t imu_drv_osinit(void);
extern int32_t imu_drv_sensorcalibration(void);
extern int32_t imu_drv_main(void);
extern imu_flip_status_t imu_drv_get_flip_status(void);


#endif