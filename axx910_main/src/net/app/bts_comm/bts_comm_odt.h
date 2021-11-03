/************************************************************************
| Project Name: bts_comm_odt
|    File Name: bts_comm_odt.h
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
#ifndef bts_COMM_ODT_H__
#define bts_COMM_ODT_H__


#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"
#include "bts_comm_cmd.h"
#include "bts_comm_packet.h"
#include "bts_comm_status.h"
//#include "krs_lib.h"


/* module specific types  */
typedef int32_t bts_comm_odt_ret_t;


/* define structure for this module */
typedef struct
{
    int32_t moduleinfo;
    int32_t version;
} bts_comm_odt_info_t;


typedef enum {
    bts_comm_datatype_INT8,
    bts_comm_datatype_UINT8,
    bts_comm_datatype_INT16,
    bts_comm_datatype_UINT16,
    bts_comm_datatype_INT32,
    bts_comm_datatype_UINT32,
    bts_comm_datatype_INT64,
    bts_comm_datatype_UINT64,
    bts_comm_datatype_F32,
    bts_comm_datatype_F64,
    bts_comm_datatype_END
} bts_comm_datatype_t;


typedef struct
{
    uint32_t addr;
    uint32_t size;      // byte stream size
    char_t name[64];    // pid name
    char_t symbol[64];  // analyzer tool symbol
    char_t format[64];  // var datatype formatting
    uint8_t pidtype[8]; // appl/raw
} bts_comm_odt_entry_t;


typedef struct
{
    bts_comm_odt_entry_t *odt_entry;
    uint8_t pidnum; // pid number
    bts_comm_datatype_t type;
    bts_comm_daqmodestatus_t status;
    bts_comm_status_start_stop_synch_mode_t start_stop_synch_mode;
} bts_comm_odt_t;


/* declare extern global variables */
extern uint8_t bts_comm_odt_datatype_size[bts_comm_datatype_END];
extern const char_t *bts_comm_odt_datatype_nametable[bts_comm_datatype_END];
extern bts_comm_odt_t bts_comm_odt_table[bts_COMM_ODT_MAX];

/* declare extern global functions */
extern bts_comm_odt_ret_t bts_comm_odt_init(void);
extern bts_comm_odt_ret_t bts_comm_odt_add(bts_comm_odt_t *odttable, uint32_t odtcnt);
extern bts_comm_odt_ret_t bts_comm_odt_table_print(bts_comm_odt_t *odttable);
extern bts_comm_odt_ret_t bts_comm_odt_print(bts_comm_odt_t *odt);
extern bts_comm_odt_ret_t
bts_comm_set_odt_properties(bts_comm_odt_t *odttable, uint8_t pid,
                              bts_comm_daqmodestatus_t *pdaqmodestatus);
extern bts_comm_odt_ret_t
bts_comm_set_odt_start_stop_mode(bts_comm_odt_t *odttable, uint8_t pid,
                                   bts_comm_status_start_stop_synch_mode_t mode);
extern bts_comm_odt_t *bts_comm_odt_search_pid(bts_comm_odt_t *odttable, uint8_t pidnum);


#ifdef __cplusplus
}
#endif
#endif // bts_COMM_ODT_H__
