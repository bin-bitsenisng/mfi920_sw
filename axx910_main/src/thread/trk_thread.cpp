/***********************************************************************
| Project Name: 
|    File Name: trk_thread.cpp
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
| 2021.05.11   0.0  mhkim   Creation;
|***********************************************************************/

#include <thread>
#include <queue>
#include <unistd.h>

#include "trk_thread.h"
#include "print_common.h"
#include "Sp_Main.h"
#include "Trk_Main.h"

#include "bts_comm.h"

#include <sys/time.h>

extern std::queue<int32_t> g_trk_work_queue;

void StartTRKthread(void)
{
    
}

void ServiceTRK(void)
{
    struct timeval startTime, endTime;
    double diffTime;

    TRACE_SYS_MSG("TRK Thread starts.\n");

	while(1)
	{
        if(!g_trk_work_queue.empty())
        {
            if(g_trk_work_queue.size() > 1)
            {
                TRACE_ERR_MSG("[WARNING] trk queue size is over 1.. it is %d\n", g_trk_work_queue.size());
            }
            TRACE_SYS_MSG("TRK queue pop ...\n");
            g_trk_work_queue.pop();
                        
            gettimeofday(&startTime, NULL);

            bts_comm_event_send();
            
            Trk_vMain();
	        Sp_vTrackOut();

            bts_comm_event_build(0, NULL);

            gettimeofday(&endTime, NULL);
            diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
            //TRACE_TIME_MSG("RSP thread 1 cycle takes %lf ms\n", diffTime*1000);
            printf("TRK thread 1 cycle takes %lf ms\n", diffTime*1000);
        }

        usleep(1000);
	}

	TRACE_SYS_MSG("RSP Thread Finished.\n");
}
