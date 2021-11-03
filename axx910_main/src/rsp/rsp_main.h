#ifndef _RSP_WRAPPER_H_
#define _RSP_WRAPPER_H_

#include "Pre_Main.h"
#include "Obj_Main.h"
#include "os.h"

void InitRSP(void);
void MainRSP(void);

extern f32_t rsp_cycletime_s;
extern os_time_t rsp_timestamp_us;

extern int16_t Sim_RM_TimeData[SP_NUM_RX][SP_RM_NUM_CHIRPS * SP_RM_NUM_SAMPLES];
extern int16_t Sim_LR_TimeData[SP_NUM_RX][SP_NUM_TX * SP_NUM_CHIRPS * SP_NUM_SAMPLES];
extern int16_t Sim_MR_TimeData[SP_NUM_RX][SP_NUM_TX * SP_NUM_CHIRPS * SP_NUM_SAMPLES];
extern int16_t Sim_SR_TimeData[SP_NUM_RX][SP_NUM_TX * SP_NUM_CHIRPS * SP_NUM_SAMPLES];

#endif