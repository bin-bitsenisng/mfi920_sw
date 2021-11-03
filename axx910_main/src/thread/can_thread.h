/************************************************************************
| Project Name: AFI910
|    File Name: can_thread.h
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

#ifndef _CAN_THREAD_H_
#define _CAN_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif

void InitCan(void);
void StartCANthread(void);
void ServiceCAN(void);

#ifdef __cplusplus
}
#endif

#endif //_CAN_THREAD_H_