/************************************************************************
 | Project Name: KRS24
 |    File Name: sys_config.h
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

#ifndef SYS_CONFIG_H__
#define SYS_CONFIG_H__

/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"


/* module specific types  */
#include "sys_def.h"
#include "sys_build_defs.h"


#define __AFI910_BE10__ 1

#ifdef __IR24S_BE25__
#define SYS_APP_TYPE SYS_APP_TYPE_VF //SYS_APP_TYPE_VF//SYS_APP_TYPE_ITS // SYS_APP_TYPE_FCW
#define SYS_SYSTEM_VERSION SYS_RADAR_VERSION_BEV25
#endif
#ifdef __IR24M_BE31__
#define SYS_APP_TYPE SYS_APP_TYPE_ITS
//#define SYS_APP_TYPE SYS_APP_TYPE_VF
//#define SYS_APP_TYPE SYS_APP_TYPE_FCW
//#define SYS_APP_TYPE SYS_APP_TYPE_MARINE
#define SYS_SYSTEM_VERSION SYS_RADAR_VERSION_BEV31
#endif
#ifdef __AFI910_BE10__
//#define SYS_APP_TYPE SYS_APP_TYPE_ITS
//#define SYS_APP_TYPE SYS_APP_TYPE_VF
//#define SYS_APP_TYPE SYS_APP_TYPE_FCW
//#define SYS_APP_TYPE SYS_APP_TYPE_MARINE
#define SYS_APP_TYPE SYS_APP_TYPE_FI
#define SYS_SYSTEM_VERSION SYS_RADAR_VERSION_BEV10
#endif


/* SW Version rule */
/*
1. Product Series
	AIR --> A
	mini --> M
2. Applications
	TM : Traffic Monitoring
	FI : 4(Four)-D Imaging
	CW : Collision Warning
	VF : Virtual Fense
	VS : Vital Sign
	FR : Front Radar
	CR : Corner Radar
	OD : Occupant Detection
	FD : Fall Detection
	AR : Autonomous Robot
	MR : Marine Radar
	LM : Level Meter
3. Center Frequency
	24GHz : 2
	60GHz : 6
	77GHz : 7
	79GHz : 9
4.Generation
	Gen x.x : xx?? ???
	Generation???? 10, 20 ... ?????? ????
5. Sample type
	F????, A???? (DV - Design Validation ???? ??), B???? (PV - Product Validation ???? ??) ?? ???? --> 'ATM220F'
         ???? ?????? ??? ??, ATM220A-01, ATM220A-02 ?? ????
*/

#include "sys_swversion.h"
#define SYS_SERIES "A"
#define SYS_CENTER_FREQ "9"
#define SYS_GENERATION "10"


#if SYS_APP_TYPE == SYS_APP_TYPE_ITS
#define SYS_APPLICATION "TM"
#include "sys_config/sys_config_its.h"

#elif SYS_APP_TYPE == SYS_APP_TYPE_VF
#define SYS_APPLICATION "VF"
#include "sys_config/sys_config_vf.h"

#elif SYS_APP_TYPE == SYS_APP_TYPE_FCW
#define SYS_APPLICATION "CW"
#include "sys_config/sys_config_fcw_atec.h"
//#include "sys_config/sys_config_fcw_vn.h"

#elif SYS_APP_TYPE == SYS_APP_TYPE_LEVELMETER
#define SYS_APPLICATION "LM"
#include "sys_config/sys_config_lm.h"

#elif SYS_APP_TYPE == SYS_APP_TYPE_MARINE
#define SYS_APPLICATION "MR"
#include "sys_config/sys_config_marine.h"

#elif SYS_APP_TYPE == SYS_APP_TYPE_FI
#define SYS_APPLICATION "FI"
#include "sys_config/sys_config_fi.h"

#else
#error "SYS_APP_TYPE is not defined"
#endif

#define SYS_DEVUID_TEMP		0
#define SYS_SW_VERSION    SYS_SERIES SYS_APPLICATION SYS_CENTER_FREQ SYS_GENERATION "_v" SYS_SW_VERSION_MAJOR "." SYS_SW_VERSION_MINOR "." SYS_SW_VERSION_REVISION ":" SYS_SW_VERSION_BUILDNUMBER
//#define SYS_SW_VERSION    "AVF210_v1.1.1"
#define SYS_FALLBACK_EN   0 // 0:normal application, 1:fallback image application (only comm enable, not used fpga resource)
#define SYS_SPIFFS_EN 0
#define SYS_CONNTIMEOUT 300.0 	// if any network activity within SYS_TIMEOUT, system will be reset
/* declare extern global functions */


/* declare extern global variables */

#define SYS_CONSOLE_BAUDRATE 921600

#define SYS_IP_DEFAULT_LABTEST 0
#define SYS_IP_DEFAULT_ZEROCITY 1
#define SYS_IP_DEFAULT_LIVINGLAB 2
#define SYS_IP_DEFAULT_WONJU 3
#define SYS_IP_DEFAULT_PANGYO1 4

#define SYS_IP_DEFAULT SYS_IP_DEFAULT_LABTEST


#if SYS_IP_DEFAULT == SYS_IP_DEFAULT_LABTEST
#define SYS_IP_BASE "192.168.10.150"
#define SYS_NM_BASE "255.255.255.0"
#define SYS_GW_BASE "192.168.10.1"
#define SYS_MACADDR_BASE "90:E2:FC:80:00:00"
#elif SYS_IP_DEFAULT == SYS_IP_DEFAULT_ZEROCITY
#define SYS_IP_BASE "172.20.50.59"
#define SYS_NM_BASE "255.255.255.0"
#define SYS_GW_BASE "172.20.50.254"
#define SYS_MACADDR_BASE "90:E2:FC:81:00:00"
#elif SYS_IP_DEFAULT == SYS_IP_DEFAULT_LIVINGLAB
#define SYS_IP_BASE "10.10.10.145"
#define SYS_NM_BASE "255.255.255.0"
#define SYS_GW_BASE "10.10.10.1"
#define SYS_MACADDR_BASE "90:E2:FC:82:00:00"
#elif SYS_IP_DEFAULT == SYS_IP_DEFAULT_WONJU
#define SYS_IP_BASE "192.168.0.29"
#define SYS_NM_BASE "255.255.255.0"
#define SYS_GW_BASE "192.168.0.1"
#define SYS_MACADDR_BASE "90:E2:FC:83:00:00"
#elif SYS_IP_DEFAULT == SYS_IP_DEFAULT_PANGYO1
#define SYS_IP_BASE "192.168.2.29"
#define SYS_NM_BASE "255.255.255.0"
#define SYS_GW_BASE "192.168.2.1"
#define SYS_MACADDR_BASE "90:E2:FC:84:00:00"
#else
#endif

#define SYS_NETWORK_ETH_STACK SYS_NETWORK_ETH_STACK_LINUX
//#define SYS_NETWORK_ETH_STACK SYS_NETWORK_ETH_STACK_LWIP
//#define SYS_NETWORK_ETH_STACK SYS_NETWORK_ETH_STACK_FREERTOSTCP

#define SYS_APP_CANDB_TYPE SYS_APP_CANDB_TYPE_HKMC2G// SYS_APP_CANDB_TYPE_HKMC1G// SYS_APP_CANDB_TYPE_HKMC2G// SYS_APP_CANDB_TYPE_J1939// SYS_APP_CANDB_TYPE_MITSUBISHI


/* Debugging */
#define SYS_DEBUG 0

#if SYS_DEBUG == 1
#define SYS_CONSOLE_BUFFER_EN  1	// debugging : 0 normal:1
#define SYS_ASSERT_RESET_EN    0  	// debugging : 0 normal:1
#define SYS_WDG_EN 			   0
#else
#define SYS_CONSOLE_BUFFER_EN  1	// debugging : 0 normal:1
#define SYS_ASSERT_RESET_EN    1  	// debugging : 0 normal:1
#define SYS_WDG_EN 			   1
#endif

#define SYS_WDG_EXPIRED_TIME 60000 // 5000ms
#endif /* SYS_CONFIG_H__ */
