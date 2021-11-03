#include "rsp_main.h"

int16_t Sim_RM_TimeData[SP_NUM_RX][SP_RM_NUM_CHIRPS * SP_RM_NUM_SAMPLES];
int16_t Sim_LR_TimeData[SP_NUM_RX][SP_NUM_TX * SP_NUM_CHIRPS * SP_NUM_SAMPLES];
int16_t Sim_MR_TimeData[SP_NUM_RX][SP_NUM_TX * SP_NUM_CHIRPS * SP_NUM_SAMPLES];
int16_t Sim_SR_TimeData[SP_NUM_RX][SP_NUM_TX * SP_NUM_CHIRPS * SP_NUM_SAMPLES];

void InitRSP(void)
{
    Sp_vSysInit();
}

void MainRSP(void)
{
    Sp_vMain();
}