#ifndef _THREAD_MANAGER_H
#define _THREAD_MANAGER_H

#ifdef __cplusplus
#include "cam_thread.h"
#include "can_thread.h"
#include "daq_thread.h"
#include "inf_thread.h"
#include "net_thread.h"
#include "rsp_thread.h"
#include "trk_thread.h"

#endif

#include "main_argument.h"
#include "os.h"

extern os_sem_t sem_restart_flag;
extern os_sem_t sem_disconnected_socket;
extern uint8_t restart_flag;

void StartThreads(MainArgument* main_argument);

#endif