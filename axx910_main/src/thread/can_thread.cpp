/************************************************************************
| Project Name: AFI910
|    File Name: can_thread_cfg.h
|  Description: detailed Description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company                        
| --------     ---------------------     -------------------------------
| 11010        Heungsun Yoon             bitsensing Corporation
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description                                 
| ----------  ----  ------  --------------------------------------------
| 2021.03.15   0.0  11010   Creation;
|***********************************************************************/

#include <thread>
#include <unistd.h>

#include "can_thread.h"
#include "can_thread_cfg.h"
#include "print_common.h"

#include "can.h"

void InitCan(void)
{
    can_init();
}

void StartCANthread(void)
{
    // std::thread can_thread(ServiceCAN);
    // can_thread.join();
}

void ServiceCAN(void)
{
    InitCan();
    TRACE_SYS_MSG("CAN Thread starts.\n");

    while (1) {
        can_read();
    }
}