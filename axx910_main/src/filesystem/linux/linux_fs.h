/************************************************************************
 | Project Name: 
 |    File Name: linux_fs.h
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

#ifndef _LINUX_FS_H_
#define _LINUX_FS_H_

#include "bts.h"
#include "os.h"

#ifdef __cplusplus
extern "C" {
#endif

char* ReadFile(char* filename, int* readSize);
uint32_t WriteFile(char* filename, char* writedata, int writeSize);

#ifdef __cplusplus
}
#endif

#endif