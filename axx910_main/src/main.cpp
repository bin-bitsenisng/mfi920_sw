#include "main_argument.h"
#include "time/timestamp.h"
#include "device_ctrl.h"
#include "thread_manager.h"
#include "rsp_main.h"
#include "print_common.h"
#include "linux_fs_app.h"
#include "inference.h"

#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"

#include "sys_param.h"
#include "sys_param_jsontype.h"
#include "sys_param_jsontype_dump.h"
#include "sys_param_jsontype_info.h"
#include "sys_param_jsontype_load.h"
#include "sys_param_cfg.h"



int main(int argc, char *argv[])
{
    MainArgument main_argument;

    if(InitMainArgument(argc, argv, &main_argument) == PARSING_FAIL)
    {
        TRACE_SYS_MSG("Argument Parsing Fail..\n");
        return 0;
    }
    else
    {   
        TRACE_SYS_MSG("Argument Parsing Success!\n");
    }

    linux_fs_app_init();
    
    bts_init();
    os_preinit();
    InitRSP();
    InitTime();
    //InitInference();
    InitNet();
    
    StartThreads(&main_argument);
    
    while(1);
    
    return 0;
}

