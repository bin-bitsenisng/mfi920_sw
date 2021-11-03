/************************************************************************
 | Project Name: KRS24
 |    File Name: sys_param_cfg.h
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
 | 2014.12.02   0.0   SKJ   Creation;
 |***********************************************************************/

#ifndef SYS_PARAM_CFG_H__
#define SYS_PARAM_CFG_H__

#include "sys_config.h"

#ifdef __cplusplus
extern "C" {
#endif


#define SYS_PARAM_JSON_UNITTEST_EN 0
/* defination for module configuration parameters */
#define SYS_PARAM_JSON_BUFFER_SIZE (64*1024)

#define SYS_PARAM_LOG_ENABLE 0
#define SYS_PARAM_ASSERT_ENABLE 0
#define SYS_PARAM_JSON_PRETTY_EN 0
#define SYS_PARAM_FROMFILE_EN SYS_SPIFFS_EN
#define SYS_PARAM_FROMFILE_LINUX_EN 1

#ifdef __cplusplus
}
#endif

#endif /* SYS_PARAM_CFG_H__ */
