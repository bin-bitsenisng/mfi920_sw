/************************************************************************
 | Project Name: KRS24
 |    File Name: app_cfg.h
 |  Description: detailed Description
 |-----------------------------------------------------------------------
 |               A U T H O R   I D E N T I T Y
 |-----------------------------------------------------------------------
 | Initials     Name                      Company
 | --------     ---------------------     -------------------------------
 | SKJ          SONG KYEONG JIN           KRS Corporation
 |-----------------------------------------------------------------------
 |              R E V I S I O N   H I S T O R Y
 |-----------------------------------------------------------------------
 | Date         Ver  Author  Description
 | ----------  ----  ------  --------------------------------------------
 | 2015.01.14   0.0   SKJ   Creation;
 |***********************************************************************/

#ifndef APP_CFG_H__
#define APP_CFG_H__


#define APP_THREAD_STACKSIZE 2048 // Empirically chosen

#define APP_INCLUDE_LOGGER_FINDECU_SERVER 0
#define APP_INCLUDE_LOGGER_SERVER 0
#define APP_INCLUDE_COMM_APPL_SERVER 1
#define APP_INCLUDE_LOGPRINT_SERVER 0
#define APP_INCLUDE_DIAG_SERVER 0
#define APP_INCLUDE_MESSAGE_CLIENT 0


#define APP_INCLUDE_TRACE 0

#define APP_INCLUDE_CMD_SERVER 0
#define APP_INCLUDE_WEB_SERVER 0
#define APP_INCLUDE_ECHO_SERVER 0
#define APP_INCLUDE_TFTP_SERVER 0
#define APP_INCLUDE_TXPERF_CLIENT 0
#define APP_INCLUDE_RXPERF_SERVER 0
#define APP_INCLUDE_UTXPERF_CLIENT 0
#define APP_INCLUDE_URXPERF_SERVER 0
#define APP_INCLUDE_COMMAND_SERVER 0



#endif /* APP_CFG_H__ */
