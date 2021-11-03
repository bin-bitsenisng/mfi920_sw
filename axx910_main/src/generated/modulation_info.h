//*****************************************************************  
//  Project Name:  IR24X 
//     File Name:  modulation_info.h
//   Description:  auto generated file. do not modify!
// ----------------------------------------------------------------
//           C O D E    G E N E R A T O R    I N F O R M A T I O N 
// ----------------------------------------------------------------
//     Generator: codegen.exe
//       Version: 0.0.1
//          Time: Mon Oct 12 15:37:38 2020
//    Datafile 0: ..\commondata\modulation_info.yaml
//    Datafile 1: ..\commondata\modulation_info_new.yaml
//    Datafile 2: ..\commondata\xcp_odt_info.yaml
//            ID: CAED29EA-8726-4383-8EA0-6E19855D34DB
// 
// ----------------------------------------------------------------
//           U S E R    I N F O R M A T I O N
// ----------------------------------------------------------------
// Computer Name: SSONGDESKTOP
//     User Name: user
//     Directory: D:\Workdir\BTS24MX_LWIP2\ir24x_sw\ir24x_main\prebuild\modulation_info
// 
// ----------------------------------------------------------------
//           P R O J E C T    S U M M A R Y
// ----------------------------------------------------------------               
//*****************************************************************
# ifndef MODULATION_INFO_H__
# define MODULATION_INFO_H__

/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"

#include "modulation_cfg.h"
#include "drivers.h"

#define MODULATION_INFO_TABLE_MAX   MODULATION_MAX_COUNT


/* module specific types  */
typedef enum
{
    MODULATION_CHIRPTYPE_0_ITS_IR24X,
    MODULATION_CHIRPTYPE_1_ITS_IR24X_LONGFIRST,
    MODULATION_CHIRPTYPE_2_ITS_KC,
    MODULATION_CHIRPTYPE_3_VF_16K,
    MODULATION_CHIRPTYPE_3_VF_1K,
    MODULATION_CHIRPTYPE_3_VF_2K,
    MODULATION_CHIRPTYPE_3_VF_4K,
    MODULATION_CHIRPTYPE_3_VF_8K,
    MODULATION_CHIRPTYPE_4_VF_1KX16,
    MODULATION_CHIRPTYPE_4_VF_2KX8,
    MODULATION_CHIRPTYPE_5_MARINE,
    MODULATION_CHIRPTYPE_6_MARINE_LONGFIRST,
    MODULATION_CHIRPTYPE_7_SLOW24GHZ,
    MODULATION_CHIRPTYPE_8_FREQMOVING,
    MODULATION_CHIRPTYPE_9_79DAQ,
    MODULATION_CHIRPTYPE_USER,
    MODULATION_CHIRPTYPE_MAX
}modulation_chriptype_t;



typedef struct
{
    uint32_t    samplecount;
    uint32_t    buffersize;
    f32_t       sampling_frequency;
}modulation_daq_info_t;

typedef struct
{
    uint32_t repeat;
    pll_drv_modulation_info_t   modulation_pll_info;
    modulation_daq_info_t       modulation_daq_info;
}modulation_chirpinfo_t;

typedef struct
{
    const char_t chirpname[MODULATION_NAME_MAX];
    uint32_t repeat_group;
    uint32_t modulation_group_count;
    f32_t   frequency_step;
    modulation_chirpinfo_t modulation_group[MODULATION_MAX_GROUP_COUNT];
}modulation_info_table_t;


/* declare extern global variables */
#define modulation_chirpcount() (modulation_info_table_count)

extern uint32_t modulation_info_table_count;
extern modulation_info_table_t modulation_info_table;
extern modulation_chriptype_t modulation_info_default_chirptype;
extern modulation_info_table_t *pmodulation_info_table[MODULATION_CHIRPTYPE_MAX];

/* chirp infomation table */
extern modulation_info_table_t modulation_info_table_modulation_chirptype_0_its_ir24x;
extern modulation_info_table_t modulation_info_table_modulation_chirptype_1_its_ir24x_longfirst;
extern modulation_info_table_t modulation_info_table_modulation_chirptype_2_its_kc;
extern modulation_info_table_t modulation_info_table_modulation_chirptype_3_vf_16k;
extern modulation_info_table_t modulation_info_table_modulation_chirptype_3_vf_1k;
extern modulation_info_table_t modulation_info_table_modulation_chirptype_3_vf_2k;
extern modulation_info_table_t modulation_info_table_modulation_chirptype_3_vf_4k;
extern modulation_info_table_t modulation_info_table_modulation_chirptype_3_vf_8k;
extern modulation_info_table_t modulation_info_table_modulation_chirptype_4_vf_1kx16;
extern modulation_info_table_t modulation_info_table_modulation_chirptype_4_vf_2kx8;
extern modulation_info_table_t modulation_info_table_modulation_chirptype_5_marine;
extern modulation_info_table_t modulation_info_table_modulation_chirptype_6_marine_longfirst;
extern modulation_info_table_t modulation_info_table_modulation_chirptype_7_slow24ghz;
extern modulation_info_table_t modulation_info_table_modulation_chirptype_8_freqmoving;
extern modulation_info_table_t modulation_info_table_modulation_chirptype_9_79daq;



/* declare extern global functions */
# endif /* MODULATION_INFO_H__ */