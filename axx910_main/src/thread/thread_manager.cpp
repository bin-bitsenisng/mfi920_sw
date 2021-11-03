#include <mutex>
#include <queue>
#include <thread>
#include <iostream>

#include "thread_manager.h"
#include "thread_manager_cfg.h"

#include "device_ctrl.h"

#include "Pre_Main.h"

extern Cuda_PreData_t gPreData;

std::mutex g_mutex_for_radar_raw_data;
std::mutex g_mutex_for_image_data;
std::queue<int32_t> g_rsp_work_queue;
std::queue<int32_t> g_trk_work_queue;
std::queue<int32_t> g_inference_request_queue;
uint32_t g_rsp_working_flag = 0;

os_sem_t sem_restart_flag;
os_sem_t sem_disconnected_socket;
uint8_t restart_flag = 0;

DEVICE_LIST devices;

/*
extern void ServiceNET(void);
extern void ServiceDAQ(void);
extern void ServiceRSP(void);
*/
void StartThreads(MainArgument* main_argument)
{
    //std::thread net_thread(ServiceNET);
    //std::thread inf_thread(ServiceINF);
    std::thread rsp_thread(ServiceRSP, main_argument);
    std::thread trk_thread(ServiceTRK);
    std::thread daq_thread(ServiceDAQ, main_argument);
    std::thread can_thread(ServiceCAN);
    std::thread cam_thread(ServiceCAM);

    //net_thread.join();
    //inf_thread.join();
    rsp_thread.join();
    daq_thread.join();
    can_thread.join();
    cam_thread.join();

}