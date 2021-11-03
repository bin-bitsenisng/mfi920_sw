/************************************************************************
 | Project Name: AFI910
 |    File Name: inf_thread.cpp
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
 | 2021.02.01  0.0   mhkim   Creation;
 |***********************************************************************/

#include "inf_thread.h"
#include "inf_thread_cfg.h"

#include "inference.h"
#include "print_common.h"

void StartINFthread(void)
{
    //InitInference();

}

void ServiceINF(void)
{
    TRACE_SYS_MSG("INF Thread starts.\n");

    //StartINFthread();

    while(1)
    {
        //Inference();
    }
}