/************************************************************************
| Project Name: bts_comm_appl_raw
|    File Name: bts_comm_appl_raw.h
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
| 2018.06.26   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef bts_COMM_APPL_IMAGE_H__
#define bts_COMM_APPL_IMAGE_H__


#ifdef __cplusplus
extern "C" {
#endif

/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"

/* module specific types  */
#define bts_COMM_APPL_IMAGE_SIZE_MAX	2*1024*1024		// 2Mbytes

typedef enum
{
	IMAGE_FORMAT_JPEG = 0,
	IMAGE_FORMAT_RAW,
	IMAGE_FORMAT_NUM
} bts_comm_appl_image_format_t;


/* define structure for this module */
typedef struct
{
    uint32_t height;
    uint32_t width;
    uint32_t format;
    uint32_t size;
} bts_comm_appl_image_info_t;

typedef struct
{
    bts_comm_appl_image_info_t image_info;
    uint8_t image_data[bts_COMM_APPL_IMAGE_SIZE_MAX];
} bts_comm_appl_imagepacket_t;

/* declare extern global variables */
extern bts_comm_appl_imagepacket_t bts_comm_appl_imagepacket;

/* declare extern global functions */
extern void bts_comm_appl_image_init(void);
extern void bts_comm_appl_pid_image_packetbuild(void);
extern void bts_comm_appl_pid_image_packetsend(void);
#ifdef __cplusplus
}
#endif
#endif // bts_COMM_APPL_IMAGE_H__
