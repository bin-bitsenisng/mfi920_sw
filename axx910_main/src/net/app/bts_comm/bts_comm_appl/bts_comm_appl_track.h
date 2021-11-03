/************************************************************************
| Project Name: bts_comm_appl_track
|    File Name: bts_comm_appl_track.h
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
#ifndef bts_COMM_APPL_TRACK_H__
#define bts_COMM_APPL_TRACK_H__


#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"

#include "Trk_Main.h"

/* module specific types  */
//#define bts_COMM_APPL_TRACK_MAX N_Track_Max
#define bts_COMM_APPL_TRACK_MAX TRK_NUM_TRACK_MAX
/* define structure for this module */
typedef struct
{
    int8_t idx;
    uint8_t status;
    uint16_t aliveage;
    f32_t xpos;
    f32_t ypos;
    f32_t refxpos;
    f32_t refypos;
    f32_t xvel;
    f32_t yvel;
    f32_t headang;
    f32_t power;
    f32_t width;
    f32_t length;
    uint32_t fusion_class;
    uint32_t fusion_type;
    f32_t zpos;
    f32_t height;
} bts_comm_appl_track_t;


typedef struct
{
    uint16_t count;
    uint16_t active_count;
    bts_comm_appl_track_t tracks[bts_COMM_APPL_TRACK_MAX];
} bts_comm_appl_trackpacket_t;


typedef union {
    struct
    {
        uint8_t status : 2;
        uint8_t reserved : 2;
        uint8_t update : 2;
        uint8_t move : 2;
    } Bit;
    uint8_t R;
} bts_comm_appl_track_status_t;

/* declare extern global variables */
extern bts_comm_appl_track_status_t trackstatus;
extern bts_comm_appl_trackpacket_t bts_comm_appl_trackpacket;

/* declare extern global functions */
extern void bts_comm_appl_track_init(void);
extern void bts_comm_appl_pid_track_packetbuild(void);
extern void bts_comm_appl_pid_track_packetsend(void);

#ifdef __cplusplus
}
#endif
#endif // bts_COMM_APPL_TRACK_H__
