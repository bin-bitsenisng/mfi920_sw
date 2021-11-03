#include <thread>
#include <unistd.h>

#include "net_thread.h"
#include "net_thread_cfg.h"
#include "print_common.h"

#include "network.h"

void InitNet(void)
{
	//network_init();
	network_osinit();
	network_osappinit();
}

void StartNETthread(void)
{
	//std::thread net_thread(ServiceNET); 
	//net_thread.join();	
}

void ServiceNET(void)
{
	TRACE_SYS_MSG("NET Thread starts.\n");

	while(1)
	{
		sleep(1);
	}
}