/************************************************************************
| Project Name: bts_comm_packet
|    File Name: bts_comm_packet.h
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
#ifndef bts_COMM_PACKET_H__
#define bts_COMM_PACKET_H__


#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"

/* module specific types  */
typedef int32_t bts_comm_packet_ret_t;


/* define structure for this module */
typedef struct
{
    int32_t moduleinfo;
    int32_t version;
} bts_comm_packet_info_t;


typedef struct
{
    uint32_t u32sync;
    uint32_t u24len;
    uint8_t u8ctr;
    uint8_t u8pid;
    uint8_t u8option;
    uint16_t u16index;
    uint32_t u32timestamp;
} bts_comm_dto_header_t;

typedef struct
{
	uint32_t u32sync;
    uint32_t u24len;
    uint8_t u8ctr;
    uint8_t u8pid;
} bts_comm_cro_header_t;


typedef struct
{
    bts_comm_dto_header_t header;
    uint8_t *databuffptr;
    uint32_t datasize;
} bts_comm_packet_dto_t;


typedef struct
{
    bts_comm_cro_header_t header;
    uint8_t *databuffptr;
    uint32_t datasize;
} bts_comm_packet_cro_t;


typedef union {
    bts_comm_packet_cro_t cro;
    bts_comm_packet_dto_t dto;
} bts_comm_packet_t;


typedef enum { bts_comm_packet_type_cro, bts_comm_packet_type_dto } bts_comm_packet_type_t;

//
// CRO Packet :  [ SYNC(4) | LEN(3),CTR(1) | PID(1) | Data(n) ]
//  SYNC = "<<<<"
//  LEN = len(Pid) + len(Data)
// DTO Packet :  [ SYNC(4) | LEN(3),CTR(1) | PID(1),Option(1),Index(2) | timestamp(4) | Data(n) ]
//  SYNC = "<<<<"
//  LEN = len(pid) + len(option) + len(index) + len(timestamp) + len(Data)

#define bts_COMMPACKET_SYNCSIZE 4
#define bts_COMMPACKET_CRO_HEADERSIZE 4
#define bts_COMMPACKET_DTO_HEADERSIZE 12
#define bts_COMMPACKET_CRO_SYNCHEADERSIZE (bts_COMMPACKET_SYNCSIZE + bts_COMMPACKET_CRO_HEADERSIZE)
#define bts_COMMPACKET_DTO_SYNCHEADERSIZE (bts_COMMPACKET_SYNCSIZE + bts_COMMPACKET_DTO_HEADERSIZE)
#define bts_COMMPACKET_CRO_SYNCHEADERPID_SIZE (bts_COMMPACKET_CRO_SYNCHEADERSIZE + 1)
#define bts_COMMPACKET_DTO_SYNCHEADEREXT_SIZE (bts_COMMPACKET_DTO_SYNCHEADERSIZE)
// header

#define bts_commget_header_u32sync(rxbuff) (uint32_t)((uint32_t)(rxbuff)[0] | (uint32_t)(rxbuff[1])<<8 | (uint32_t)(rxbuff)[2]<<16 | (uint32_t)(rxbuff)[3]<<24)

#define bts_commget_header_u16len_l(rxbuff) \
    ((uint32_t)((((uint16_t)(rxbuff)[4+0]) & 0xFF) | ((((uint16_t)(rxbuff)[4+1]) << 8) & 0xFF00)))
#define bts_commget_header_u8len_h(rxbuff) ((uint32_t)((rxbuff)[4+2]) & 0xFF)
#define bts_commget_header_u24len(rxbuff) \
    ((uint32_t)(bts_commget_header_u8len_h(rxbuff) << 16) + bts_commget_header_u16len_l(rxbuff))
#define bts_commget_header_u8ctr(rxbuff) ((uint16_t)(((rxbuff)[4+3]) & 0xFF))

// cro/dto common
#define bts_commget_packet_u8pid(rxbuff) ((uint8_t)(rxbuff)[4+4])

// cro
#define bts_commget_cropacket_u8data(rxbuff, x) ((uint8_t)(rxbuff)[4+5 + (x)])
#define bts_commget_cropacket_u8databuff(rxbuff) ((uint8_t *)&rxbuff[4+5])

// dto
#define bts_commget_dtopacket_u8option(rxbuff) ((uint8_t)(rxbuff)[4+5])
#define bts_commget_dtopacket_u16index(rxbuff) \
    ((uint16_t)((((uint16_t)(rxbuff)[4+6]) & 0xFF) | ((((uint16_t)(rxbuff)[4+7]) << 8) & 0xFF00)))
#define bts_commget_dtopacket_u32timestamp(rxbuff)                                           \
    ((uint32_t)((((uint32_t)(rxbuff)[4+8]) & 0xFF) | ((((uint32_t)(rxbuff)[4+9]) << 8) & 0xFF00) | \
                ((((uint32_t)(rxbuff)[4+10]) << 16) & 0xFF0000) |                                \
                ((((uint32_t)(rxbuff)[4+11]) << 24) & 0xFF000000)))
#define bts_commget_dtopacket_u8data(rxbuff, x) ((uint8_t)(rxbuff)[4+12 + (x)])
#define bts_commget_dtopacket_u8databuff(rxbuff) ((uint8_t *)&rxbuff[4+12])


// header
#define bts_commset_header_u32sync(txbuff) txbuff[0]='<';txbuff[1]='<';txbuff[2]='<';txbuff[3]='<'

#define bts_commset_header_u24len(txbuff, x) \
    txbuff[4+0] = ((x)&0xFF);                    \
    txbuff[4+1] = (((x) >> 8) & 0xFF);           \
    txbuff[4+2] = (((x) >> 16) & 0xFF)
#define bts_commset_header_u8ctr(txbuff, x) txbuff[4+3] = (x);

// common
#define bts_commset_packet_u8pid(txbuff, x) txbuff[4+4] = (x)


// cro
#define bts_commset_cropacket_u8data(txbuff, i, x) txbuff[4+5 + i] = (x)
#define bts_commset_cropacket_u8databuff(txbuff, databuff, size) \
    krs_memcopy(&txbuff[4+5], databuff, size)


// dto
#define bts_commset_dtopacket_u8option(txbuff, x) txbuff[4+5] = (x)
#define bts_commset_dtopacket_u16index(txbuff, x) \
    txbuff[4+6] = (x);                                \
    txbuff[4+7] = ((x) >> 8)
#define bts_commset_dtopacket_u32timestamp(txbuff, x) \
    txbuff[4+8] = (x);                                    \
    txbuff[4+9] = ((x) >> 8);                             \
    txbuff[4+10] = ((x) >> 16);                           \
    txbuff[4+11] = ((x) >> 24)
#define bts_commset_dtopacket_u8data(txbuff, i, x) txbuff[4+12 + i] = (x)
#define bts_commset_dtopacket_u8databuff(txbuff, databuff, size) \
    krs_memcopy(&txbuff[4+12], databuff, size)

#define bts_commset_dtopacket_u8databuff_dma(txbuff, databuff, size) \
    krs_dma_memcopy(&txbuff[4+12], databuff, size)


#define bts_commset_dtopacket_u16data(txbuff, i, x) \
    txbuff[4+12 + ((i)*2)] = (x);                       \
    txbuff[4+12 + ((i)*2) + 1] = (x) >> 8
#define bts_commset_cropacket_u16data(txbuff, i, x) \
    txbuff[4+5 + ((i)*2)] = (x);                        \
    txbuff[4+5 + ((i)*2) + 1] = (x) >> 8
#define bts_commset_dtopacket_u32data(txbuff, i, x) \
    txbuff[4+12 + ((i)*4)] = (x);                       \
    txbuff[4+12 + ((i)*4) + 1] = (x) >> 8;              \
    txbuff[4+12 + ((i)*4) + 2] = (x) >> 16;             \
    txbuff[4+12 + ((i)*4) + 3] = (x) >> 24
#define bts_commset_cropacket_u32data(txbuff, i, x) \
    txbuff[4+5 + ((i)*4)] = (x);                        \
    txbuff[4+5 + ((i)*4) + 1] = (x) >> 8;               \
    txbuff[4+5 + ((i)*4) + 2] = (x) >> 16;              \
    txbuff[4+5 + ((i)*4) + 3] = (x) >> 24


#define bts_commget32datafromintelfmt(addr)                                 \
    ((((uint32_t)*addr) & 0xFF) | ((((uint32_t) * (addr + 1)) & 0xFF) << 8) | \
     ((((uint32_t) * (addr + 2)) & 0xFF) << 16) | ((((uint32_t) * (addr + 3)) & 0xFF) << 24))
#define bts_commget16datafronintelfmt(addr) \
    ((((uint16_t)*addr) & 0xFF) | ((((uint16_t) * (addr + 1)) & 0xFF) << 8))
#define bts_commgetdtodataaddr(i) &(rxbuff)[4+12 + (i)]
/* declare extern global variables */


/* declare extern global functions */
extern uint32_t bts_commpacket_make_cro_packet(uint8_t *desbuff, uint8_t pid, uint8_t *databuff,
                                                 uint32_t size);
extern uint32_t bts_commpacket_make_dto_packet(uint8_t *desbuff, uint8_t pid, uint8_t option,
                                                 uint16_t index, uint32_t timestamp,
                                                 uint8_t *databuff, uint32_t size);
extern uint32_t bts_commpacket_parse_packets(bts_comm_packet_t *packet, uint8_t *rxbuff, size_t size);
extern uint32_t bts_commpacket_parse_cro_packet(bts_comm_packet_t *packet, uint8_t *rxbuff);
extern uint32_t bts_commpacket_parse_dto_packet(bts_comm_packet_t *packet, uint8_t *rxbuff);
#ifdef __cplusplus
}
#endif
#endif // bts_COMM_PACKET_H__
