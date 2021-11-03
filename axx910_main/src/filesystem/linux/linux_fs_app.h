/************************************************************************
 | Project Name: 
 |    File Name: linux_fs_app.h
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

#ifndef _LINUX_FS_APP_H_
#define _LINUX_FS_APP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "linux_fs_app_cfg.h"
#include "sys_param.h"

int32_t linux_fs_app_init(void);
uint32_t write_sys_param_to_file(char* filename, sys_param_sidxdidx_configinfo_packing_t* writedata, int writeSize);

#ifdef __cplusplus
}
#endif

#endif