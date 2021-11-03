/************************************************************************
 | Project Name: KRS24
 |    File Name: system.h
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

#ifndef SYSTEM_H__
#define SYSTEM_H__

/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "system_cfg.h"
#include "sys_param.h"

/* module specific types  */
typedef int32_t system_ret_t;


/* define structure for this module */
typedef struct{
    int32_t moduleinfo;
    int32_t version;
}system_info_t;


/* declare extern global variables */
extern const sys_param_common_comm_ethernet_config_t ethernet_config_factorydefault;


/* declare extern global functions */
extern system_ret_t system_init(void);
extern int32_t system_swbuild_date(void);
extern int32_t system_swbuild_time(void);
extern uint64_t system_devuid(void);
extern int32_t system_devuid_str(char *buff, size_t buffsize);
extern uint64_t system_devuid_fromstr(char *buff, size_t buffsize);
extern int32_t system_get_status_to_json(char_t *buff, size_t buffsize);
#endif /* SYSTEM_H__ */
