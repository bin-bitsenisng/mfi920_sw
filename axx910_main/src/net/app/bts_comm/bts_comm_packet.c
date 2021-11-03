/************************************************************************
| Project Name: bts_comm_packet
|    File Name: bts_comm_packet.c
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
| 2017.10.11   0.0   SKJ   Creation;
|***********************************************************************/


/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"

/* include system driver header */


/* include system bsp header */


/* include system application header */


/* final include module header */
#include "sys_param.h"
#include "bts_comm_cmd.h"
#include "bts_comm_packet.h"


/* declare global variables */
#define bts_COMM_PACKET_LOG_EN SYS_PARAM_CONSOLELOG.bts_log_module_comm_packet_en
#if bts_COMM_CROPACKET_PARSE_DEBUG == 1
#define bts_comm_cropacket_log if(bts_COMM_PACKET_LOG_EN) krs_log
#else
#define bts_comm_cropacket_log krs_log_dummy
#endif

/* declare static variables */
uint8_t bts_comm_packet_cro_counter = 0;
uint8_t bts_comm_packet_dto_counter = 0;

/* static function prototypes */

/* functions */

/******************************************************************************
 * function name : bts_commpacket_make_cro_packet
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *desbuff description
 * \param1 pid description
 * \param2 *databuff description
 * \param3 size description
 * \return uint32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
uint32_t bts_commpacket_make_cro_packet(uint8_t *desbuff, uint8_t pid, uint8_t *databuff,
                                          uint32_t size)
{
    uint32_t len;

    len = size + 1;
    bts_commset_header_u32sync(desbuff);
    bts_commset_header_u24len(desbuff, len);
    bts_commset_header_u8ctr(desbuff, bts_comm_packet_cro_counter++);
    bts_commset_packet_u8pid(desbuff, pid);
    if(databuff != NULL && size != 0)
    {
        bts_commset_cropacket_u8databuff(desbuff, databuff, size);
    }
    return (size + bts_COMMPACKET_CRO_SYNCHEADERPID_SIZE);
}

/******************************************************************************
 * function name : bts_commpacket_make_dto_packet
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *desbuff description
 * \param1 pid description
 * \param2 option description
 * \param3 index description
 * \param4 timestamp description
 * \param5 *databuff description
 * \param6 size description
 * \return uint32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
uint32_t bts_commpacket_make_dto_packet(uint8_t *desbuff, uint8_t pid, uint8_t option,
                                          uint16_t index, uint32_t timestamp, uint8_t *databuff,
                                          uint32_t size)
{
    uint32_t len;

    len = size + 8;
    bts_commset_header_u32sync(desbuff);
    bts_commset_header_u24len(desbuff, len);
    bts_commset_header_u8ctr(desbuff, bts_comm_packet_dto_counter++);
    bts_commset_packet_u8pid(desbuff, pid);
    bts_commset_dtopacket_u8option(desbuff, option);
    bts_commset_dtopacket_u16index(desbuff, index);
    bts_commset_dtopacket_u32timestamp(desbuff, timestamp);
    if(databuff != NULL)
    {
#if 0
    	if(size > 1024)
    	{
    		bts_commset_dtopacket_u8databuff_dma(desbuff, databuff, size);
    	}
    	else
    	{
    bts_commset_dtopacket_u8databuff(desbuff, databuff, size);
    	}
#else
    	bts_commset_dtopacket_u8databuff(desbuff, databuff, size);
#endif
    }
    return (size + bts_COMMPACKET_DTO_SYNCHEADEREXT_SIZE);
}


/******************************************************************************
 * function name : bts_commpacket_parse_packet
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packet description
 * \param1 *rxbuff description
 * \return uint32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
uint32_t bts_commpacket_parse_packets(bts_comm_packet_t *packet, uint8_t *rxbuff, size_t size)
{
	size_t remain = size;
	int32_t idx=0;
	size_t datalen;
	uint8_t pid;

	idx=0;
	while(remain>0)
	{
		if(remain >= (bts_COMM_MAX_CRO - bts_COMMPACKET_CRO_SYNCHEADERPID_SIZE))
		{
			krs_log_error("bts_commpacket_parse_packets: invalid remain length %d\n\r", remain);
			return retFail;
		}
		pid = bts_commget_packet_u8pid(&rxbuff[idx]);
		if(pid >= 0xC0)
		{
			datalen = bts_commpacket_parse_cro_packet(packet, &rxbuff[idx]) + bts_COMMPACKET_CRO_SYNCHEADERPID_SIZE;
		}
		else
		{
			datalen = bts_commpacket_parse_dto_packet(packet, &rxbuff[idx]) + bts_COMMPACKET_DTO_SYNCHEADEREXT_SIZE;
		}
		remain -=datalen;
		idx += datalen;
	}
	return retOK;
}

/******************************************************************************
 * function name : bts_commpacket_parse_cro_packet
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packet description
 * \param1 *rxbuff description
 * \return uint32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
uint32_t bts_commpacket_parse_cro_packet(bts_comm_packet_t *packet, uint8_t *rxbuff)
{
    uint32_t datalen = 0;
    uint32_t len;
    uint32_t sync=0;
    uint8_t ctr;

    sync = bts_commget_header_u32sync(rxbuff);
    len = bts_commget_header_u24len(rxbuff);
    ctr = bts_commget_header_u8ctr(rxbuff);
    if(len >= (bts_COMM_MAX_CRO - bts_COMMPACKET_CRO_SYNCHEADERPID_SIZE))
    {
    	krs_log_error("afi910 COMM: len=%ld is invalid packet length\n\r", len);
        return (int32_t)0;
    }
    packet->cro.header.u32sync = sync;
    packet->cro.header.u24len = len;
    packet->cro.header.u8ctr = ctr;
    packet->cro.header.u8pid = bts_commget_packet_u8pid(rxbuff);
    packet->cro.databuffptr = bts_commget_cropacket_u8databuff(rxbuff);
    packet->cro.datasize = len - 1;
    datalen = packet->cro.datasize;

    if(bts_COMM_PACKET_LOG_EN)
    {
		krs_log_debug("bts_comm CRO PKT Header [sync:%s][len:%ld][ctr:%ld][pid:0x%02X]:\n\r", (sync == 0x3C3C3C3C)? "<<<<":"None", len, ctr, packet->cro.header.u8pid);
		krs_log_debug("bts_comm CRO PKT PDU(%ld):\n\r", datalen);
		krs_log_arruint8X(packet->cro.databuffptr, datalen);
    }
    return datalen;
}


/******************************************************************************
 * function name : bts_commpacket_parse_dto_packet
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *packet description
 * \param1 *rxbuff description
 * \return uint32_t description
 * modification date : 2017.10.11
 *****************************************************************************/
uint32_t bts_commpacket_parse_dto_packet(bts_comm_packet_t *packet, uint8_t *rxbuff)
{
    uint32_t datalen = 0;
    uint32_t len;
    uint8_t ctr;
    uint32_t sync=0;

    sync = bts_commget_header_u32sync(rxbuff);
    len = bts_commget_header_u24len(rxbuff);
    ctr = bts_commget_header_u8ctr(rxbuff);

    packet->dto.header.u32sync = sync;
    packet->dto.header.u24len = len;
    packet->dto.header.u8ctr = ctr;
    packet->dto.header.u8pid = bts_commget_packet_u8pid(rxbuff);
    packet->dto.header.u8option = bts_commget_dtopacket_u8option(rxbuff);
    packet->dto.header.u16index = bts_commget_dtopacket_u16index(rxbuff);
    packet->dto.header.u32timestamp = bts_commget_dtopacket_u32timestamp(rxbuff);
    packet->dto.databuffptr = bts_commget_dtopacket_u8databuff(rxbuff);
    packet->dto.datasize = len - 8;


#if bts_COMM_DTOPACKET_PARSE_DEBUG != 0
    uint32_t i;
    krs_log("--- bts_comm dto packet---\n\r");
    krs_log("header sync: %s\n\r", (sync == 0x3C3C3C3C)? "<<<<":"None");
    krs_log("header len: 0x%06X, %d bytes\n\r", len, len);
    krs_log("header ctr: 0x%02X\n\r", ctr);
    krs_log("packet pid: 0x%02X\n\r", packet->dto.header.u8pid);
    krs_log("packet option: 0x%02X\n\r", packet->dto.header.u8option);
    krs_log("header daq: 0x%04X\n\r", packet->dto.header.u16index);
    krs_log("header timestamp: 0x%08X\n\r", packet->dto.header.u32timestamp);
    datalen = packet->dto.datasize;
    if(datalen > 0)
    {
        krs_log("packet data size: %d bytes\n\r", datalen);
        krs_log("packet data:");
#if bts_COMM_DTOPACKET_PARSE_DEBUG == 1
        if(datalen > 24)
        {
            for(i = 0; i < 16; i++)
            {
                krs_log("%02X ", packet->dto.databuffptr[i]);
            }
            krs_log("\n\r~\n\r");
            for(i = datalen - 8; i < datalen; i++)
            {
                krs_log("%02X ", packet->dto.databuffptr[i]);
            }
        }
        else
        {
            for(i = 0; i < datalen; i++)
            {
                krs_log("%02X ", packet->dto.databuffptr[i]);
            }
        }

#elif bts_COMM_DTOPACKET_PARSE_DEBUG == 2
        for(i = 0; i < datalen; i++)
        {
            if(i > 64 && i < (datalen - 8))
            {
                if(i % 16 == 0)
                {
                    krs_log(".");
                }
                continue;
            }
            krs_log("%02X ", packet->dto.databuffptr[i]);
            if(i % 16 == 0 && i != 0)
            {
                krs_log("\n\r\t");
            }
        }
#endif
        krs_log("\n\r");
    }
    else
    {
        krs_log("packet data: None\n\r");
    }
    krs_log("\n\r");
#endif
    return datalen;
}


/* end of file */
