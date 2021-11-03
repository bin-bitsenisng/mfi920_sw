/************************************************************************
| Project Name: bts_comm_service
|    File Name: bts_comm_service.c
|  Description: file detailed description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------
| JJUNE        PARK JUN SEONG            Bitsensing
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description
| ----------  ----  ------  --------------------------------------------
| 2018.12.21   0.0   JJUNE   Creation;
|***********************************************************************/


/* include system primitive types */
#include "bts.h"

/* include system driver header */


/* include system bsp header */


/* include system application header */
//#include "drivers.h"
//#include "taskmgr.h"
#include "thread_manager.h"

/* final include module header */
#include "bts_comm.h"
#include "bts_comm_appl.h"
#include "bts_comm_callback.h"
#include "bts_comm_cfg.h"
#include "bts_comm_odt.h"
#include "bts_comm_status.h"
#include "bts_comm_service.h"
#include "os.h"
#include "sys_param.h"
//#include "mtd_app.h"
#include "eth.h"

int32_t bts_comm_service_network_config(void* pvParam);

//extern os_sem_t sem_restart_flag;
//extern os_sem_t sem_disconnected_socket;
//extern uint8_t restart_flag;

bts_comm_service_table_t bts_comm_service_table[] = {
	{0, 3, bts_comm_service_network_config},
};

int32_t bts_comm_service_callfunc(uint32_t sid, uint32_t did, void* pvParam)
{
	uint16_t idx;
	for(idx=0;idx<SYS_PARAM_SERVICE_TABLE_MAX;idx++)
	{
		if((sid == bts_comm_service_table[idx].sid) && (did == bts_comm_service_table[idx].did))
		{
			bts_comm_service_table[idx].service_func(pvParam);
		}
	}

	return 0;
}

int32_t bts_comm_service_network_config(void* pvParam)
{
	sys_param_sid0did3_network_config_t* network_cfg = (sys_param_sid0did3_network_config_t*)pvParam;

	uint32_t ipaddr, gwaddr;
	uint8_t ipaddr_b[4], gwaddr_b[4];

	// SYS_PARAM_LOGICCONTROL.flag_ip_change_check = true;

	if ((strcmp(sys_param_sidxdidx_configinfo_packing.sid0did0_systembase_config.setup.eth_default.ip, network_cfg->setup.ip) != 0)
	  ||(strcmp(sys_param_sidxdidx_configinfo_packing.sid0did0_systembase_config.setup.eth_default.gw, network_cfg->setup.gw) != 0))
	{

		ipaddr = eth_get_ipaddr_fromstring(network_cfg->setup.ip);
		gwaddr = eth_get_ipaddr_fromstring(network_cfg->setup.gw);
		ipaddr_b[0] = eth_ip4_addr1(ipaddr);
		ipaddr_b[1] = eth_ip4_addr2(ipaddr);
		ipaddr_b[2] = eth_ip4_addr3(ipaddr);
		ipaddr_b[3] = eth_ip4_addr4(ipaddr);
		gwaddr_b[0] = eth_ip4_addr1(gwaddr);
		gwaddr_b[1] = eth_ip4_addr2(gwaddr);
		gwaddr_b[2] = eth_ip4_addr3(gwaddr);
		gwaddr_b[3] = eth_ip4_addr4(gwaddr);

		if((ipaddr_b[0] == gwaddr_b[0]) && (ipaddr_b[1] == gwaddr_b[1]) && (ipaddr_b[2] == gwaddr_b[2]))
		{
			restart_flag = true;
			int cnt = 0;

			cnt = strlen(network_cfg->setup.ip);

			krs_memcopy(&sys_param_sidxdidx_configinfo_packing.sid0did0_systembase_config.setup.eth_default.ip, &network_cfg->setup.ip, cnt);

			cnt = strlen(network_cfg->setup.gw);
			krs_memcopy(&sys_param_sidxdidx_configinfo_packing.sid0did0_systembase_config.setup.eth_default.gw, &network_cfg->setup.gw, cnt);

			//krs_log_debug("give restart sem\n");
			os_sem_give(sem_restart_flag);
		}
		else
		{
			krs_log_info("Check IP and Gateway address for configuration\n");
		}

	}

	return 0;
}



/* end of file */
