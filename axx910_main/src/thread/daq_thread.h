#ifndef _DAQ_THREAD_H_
#define _DAQ_THREAD_H_

// 이런식으로 해도 됨..?
#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

#include "Pre_Main.h"
#include "Sp_Parameters.h"
#include "main_argument.h"

void StartDAQthread(void);
void ServiceDAQ(MainArgument* main_argument);

extern int16_t rearranged_daq_data[SP_NUM_CHIRPS*SP_NUM_TX*SP_NUM_RX*SP_NUM_SAMPLES];

extern uint64_t daq_scanindex;

#ifdef __cplusplus
}
#endif

#endif