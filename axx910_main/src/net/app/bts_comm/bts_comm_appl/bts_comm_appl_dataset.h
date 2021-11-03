/************************************************************************
| Project Name: bts_comm_appl_dataset
|    File Name: bts_comm_appl_dataset.h
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
#ifndef bts_COMM_APPL_DATASET_H__
#define bts_COMM_APPL_DATASET_H__


#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"
#include "bts_comm_cfg.h"

#include "sys_param.h"

/* module specific types  */
#define bts_COMM_APPL_DATASET_JSON_BUFFER_SIZE SYS_PARAM_JSON_BUFFER_SIZE

/* define structure for this module */
typedef enum
{
    bts_comm_pidtype_appl,
    bts_comm_pidtype_raw,
	bts_comm_pidtype_end
}bts_comm_pidtype_t;

typedef enum
{
    bts_comm_pid_status = 0x00,
    bts_comm_pid_object = 0x01,
    bts_comm_pid_track = 0x02,
    bts_comm_pid_image = 0x03,
	bts_comm_pid_imagsp = 0x04,
    bts_comm_pid_logger = 0x05,
	bts_comm_pid_canlog = 0x06,
	bts_comm_pid_sensor = 0x07,
    bts_comm_pid_app_its = 0x08,
    bts_comm_pid_app_vf = 0x09,
	bts_comm_pid_app_fcw= 0x0A,
	bts_comm_pid_app_lm= 0x0B,	// level meter
    bts_comm_pid_ai_object = 0x0C,
    bts_comm_pid_lane_detection = 0x0D,
    bts_comm_pid_freespace = 0x0E,
	bts_comm_pid_raw = 0x10,
    bts_comm_pid_max = 0xBF

}bts_comm_pid_appl_t;

/* define structure for this module */
typedef struct
{
    int32_t enable;
    uint8_t *ref_enable;
    int32_t start;
    bts_comm_pid_appl_t pid;
    char_t *pidname;
    bts_comm_pidtype_t pidtype;
    void (*precallback)(void*, size_t size);
    void (*postcallback)(void*, size_t size);
    void *pvParam;
    size_t bytesize;
    char_t *symbol;
    char_t *fmt;
}bts_comm_daqinfo_t;
#define DAQINFO_APPL(en,ref_en, pid, name) {(en),(uint8_t *)(ref_en), 0, pid, name, bts_comm_pidtype_appl, NULL, NULL, NULL, 0, "",""}
#define DAQINFO_RAW(en, ref_en, name, addr, size , fmt, precallback) {(en),(uint8_t *)(ref_en), 0,bts_comm_pid_raw, name, bts_comm_pidtype_raw, precallback, NULL, addr, size, name, fmt}
#define DAQINFO_RAW_COUNT(en,ref_en, name, item, count , type, precallback) {(en),(uint8_t *)(ref_en), 0,bts_comm_pid_raw, name, bts_comm_pidtype_raw, precallback, NULL, (void*)&(item), count*sizeof(typeof(item)), name, STR((count)) type}
#define DAQINFO_RAW_TYPE(en, ref_en, name, item, type) DAQINFO_RAW_COUNT(en,ref_en, name, item, sizeof(item)/sizeof(typeof(item)), type, NULL)
#define DAQINFO_RAW_ITEM(en, ref_en, name, item, symbol, fmt, precallback) {(en),(uint8_t *)(ref_en), 0, bts_comm_pid_raw, name, bts_comm_pidtype_raw, precallback, NULL, (void*)&(item), sizeof(item), symbol,fmt}
#define DAQINFO_END() {0,0, 0,bts_comm_pid_max, "", bts_comm_pidtype_end, NULL, NULL, NULL, 0, "",  ""}
/* declare extern global variables */
extern char_t bts_comm_appl_dataset_json_buffer[bts_COMM_APPL_DATASET_JSON_BUFFER_SIZE];
extern sys_param_pid0_status_data_t appljson_pid0_status_data;
extern bts_comm_daqinfo_t bts_comm_daqinfo[bts_comm_pid_max];
extern uint8_t bts_comm_daqinfo_pid2index_lut[bts_comm_pid_max];
extern uint8_t bts_comm_daqinfo_index2pid_lut[bts_comm_pid_max];

/* declare extern global functions */
extern void bts_comm_appl_dataset_init(void);
extern int32_t bts_comm_daqinfo_is_start(bts_comm_pid_appl_t pid);
extern int32_t bts_comm_appl_dataset_set_daqstartstop(uint8_t *activatelist, int32_t len);
#ifdef __cplusplus
}
#endif
#endif // bts_COMM_APPL_DATASET_H__
