/************************************************************************
 | Project Name: 
 |    File Name: linux_fs_app.c
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
 | 2021.01.30  0.0   mhkim   Creation;
 |***********************************************************************/

#include "linux_fs_app_cfg.h"
#include "linux_fs_app.h"
#include "linux_fs.h"

int32_t linux_fs_app_init(void)
{
    int32_t ret;

    // app file이 없으면, load from default
    if(access(SYS_PARAM_FILE_PATH_APP, 0) == -1)
    {
        ret = sys_param_load_from_default();
    }
    else // app file이 있으면
    {
        ret = sys_param_load_from_file(SYS_PARAM_FILE_PATH_APP, &sys_param_sidxdidx_configinfo_packing);
    }

    return ret;
}
