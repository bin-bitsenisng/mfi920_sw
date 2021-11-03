/************************************************************************
| Project Name: bts_comm_cfg
|    File Name: bts_comm_cfg.h
|  Description: file detailed description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------
| SKJ          SONG KYEONG JIN           Lobeye
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description
| ----------  ----  ------  --------------------------------------------
| 2017.09.11   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef bts_COMM_CFG_H__
#define bts_COMM_CFG_H__


#ifdef __cplusplus
extern "C" {
#endif

// bts_comm_appl
#define bts_COMM_APPL_DEBUG 0
#define bts_COMM_APPLCMD_EN 1
#define bts_COMM_APPL_UDP_DEBUG 1
#define bts_COMM_APPLCMD_CALLBACK_JSONBUFFSIZE (64*1024)

// packet config
#define bts_COMM_CROPACKET_PARSE_DEBUG 0
#define bts_COMM_DTOPACKET_PARSE_DEBUG 0
#define bts_COMM_CALLBACK_DEBUG 1


// protocol config
#define bts_COMM_MAX_CRO (16 * 1024 * 1024)
#define bts_COMM_MAX_DTO (16 * 1024 * 1024)


// odt config
#define bts_COMM_ODT_MAX 192


// comm config
#define bts_COMM_TX_DEBUG 0
#define bts_COMM_RX_DEBUG 1
#define bts_COMM_TX_MSGQUEUE_SIZE 16
#define bts_COMM_RX_MSGQUEUE_SIZE 8
//#define bts_COMM_TX_BUFFER_SIZE ((1024+128) * 1024 + 1*1024*1024) // add image buffer
#define bts_COMM_TX_BUFFER_SIZE ((1024+512) * 1024 + 1*1024*1024) // add image buffer
#define bts_COMM_RX_BUFFER_SIZE (1024 * 1024)



// appl comm config


#define bts_COMM_APPL_TCPCONNECT_TIMEOUT 60000*60
#define bts_COMM_APPL_UDPCONNECT_TIMEOUT 60000
#define bts_COMM_APPL_TCPSEND_TIMEOUT 10000
#define bts_COMM_APPL_UDPSEND_TIMEOUT 10000
#define bts_COMM_APPL_TCPRECEIVE_TIMEOUT 10000
//#define bts_COMM_APPL_COMMAND_TIMEOUT 5000


#define bts_COMM_APPLCMD_TCP_LOCAL_PORT 4544
#define bts_COMM_APPLCMD_UDP_LOCAL_UNICAST_PORT 4544
#define bts_COMM_APPLCMD_UDP_LOCAL_BROADCAST_PORT 4545


#define bts_COMM_APPL_DAQ_TCP_PORT 4545
#define bts_COMM_APPL_APPDATA_TCP_PORT 4546
#define bts_COMM_APPL_PROTOCOL_TIMEOUT 60000

#define bts_COMM_APPL_CONSOLE_UDP_PORT 4543

#define bts_COMM_DEBUG 0
#define bts_COMM_DEBUG_VERBOSE 0
#define bts_COMM_APPL_PACKETSIZE_DEBUG 0
#define bts_COMM_APPL_JSON_DEBUG 0
#define bts_COMM_APPL_PERFORMANCE_LOG_DEBUG 0
#define bts_COMM_APPL_IMAGE_TESTMODE 0
#define bts_COMM_APPL_IMAGE_DEBUG 0

#ifdef __cplusplus
}
#endif
#endif // bts_COMM_CFG_H__
