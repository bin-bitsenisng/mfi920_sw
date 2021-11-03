//*****************************************************************
//  Project Name:  IR24X
//     File Name:  xcp_odt_info.c
//   Description:  auto generated file. do not modify!
// ----------------------------------------------------------------
//           C O D E    G E N E R A T O R    I N F O R M A T I O N
// ----------------------------------------------------------------
//     Generator: codegen.exe
//       Version: 0.0.1
//          Time: Thu Jan 31 13:56:56 2019
//    Datafile 0: ..\commondata\modulation_info.yaml
//    Datafile 1: ..\commondata\modulation_info_new.yaml
//    Datafile 2: ..\commondata\xcp_odt_info.yaml
//            ID: C60BDE29-B8C3-4652-A7A0-A095B8B71874
//
// ----------------------------------------------------------------
//           U S E R    I N F O R M A T I O N
// ----------------------------------------------------------------
// Computer Name: DESKTOP-5TB7JBS
//     User Name: ellli
//     Directory: D:\Workdir\IR24X_TempWork\ir24x_main\prebuild\xcp_odt_info
//
// ----------------------------------------------------------------
//           P R O J E C T    S U M M A R Y
// ----------------------------------------------------------------
//*****************************************************************
/* include system primitive types */
#include "bts.h"
#include "xcp_cfg.h"

/* include system driver header */


/* include system bsp header */


/* include system application header */
#include "taskmgr.h"

/* final include module header */
#include "modulation.h"
#include "modulation_info.h"
#include "xcp.h"
#include "xcp_odt.h"
#include "xcp_odt_info.h"


const char_t *xcp_id_table[8] =
    {
        /*idtype 0 , ascii_text */ "krs24main",
        /*idtype 1 , asap_filename */ "krs24main",
        /*idtype 2 , asap_filenameext */ "krs24main.a2l",
        /*idtype 3 , asap_filenameurl */ "https://www.intellobe.com/dev/krs24/a2l/krs24main.a2l",
        /*idtype 4 , asap_file */ "asap_file contents",
        /*idtype 5 , user_be_version */ "2.0",
        /*idtype 6 , user_rfm_version */ "2.5",
        /*idtype 7 , user_ecu_serialnumber */ "00000001"};


xcp_odt_daq_entry_t xcp_odt_daqinfo_resume_odt_table_pid0[5] =
    {
        {(uint32_t)mod_daq_datainfolist, (uint32_t)sizeof(mod_daq_datainfolist), xcp_datatype_UINT8},    // DAQ0 : mod_daq_datainfolist
        {(uint32_t)mod_daq_buffer_address_table, (uint32_t)4, xcp_datatype_UINT32},                      // DAQ1 : mod_daq_buffer_address_table
        {(uint32_t)&modulation_info_table, (uint32_t)sizeof(modulation_info_table), xcp_datatype_UINT8}, // DAQ2 : modulation_info_table
        {(uint32_t)&modulation_chirp_type, (uint32_t)1, xcp_datatype_UINT8},                             // DAQ3 : modulation_chirp_type
        {(uint32_t)&modulation_scan_count, (uint32_t)1, xcp_datatype_UINT32}                             // DAQ4 : modulation_scan_count
};

xcp_odt_daq_entry_t xcp_odt_daqinfo_resume_odt_table_pid1[4] =
    {
        {(uint32_t)&imu_system_pitch, (uint32_t)1, xcp_datatype_INT16}, // DAQ0 : imu_system_pitch
        {(uint32_t)&imu_system_yaw, (uint32_t)1, xcp_datatype_INT16},   // DAQ1 : imu_system_yaw
        {(uint32_t)&imu_system_roll, (uint32_t)1, xcp_datatype_INT16},  // DAQ2 : imu_system_roll
        {(uint32_t)&imu_system_height, (uint32_t)1, xcp_datatype_INT16} // DAQ3 : imu_system_height
};


/* modulation_chirptype_0_its_ir24x odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_0_its_ir24x_ch0[2] = {
    {(uint32_t)&mod_daq_buffer[0][0x00000000], 4096, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[0][0x00002000], 8191, xcp_datatype_INT16}  // DAQ1
};
/* modulation_chirptype_0_its_ir24x odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_0_its_ir24x_ch1[2] = {
    {(uint32_t)&mod_daq_buffer[1][0x00000000], 4096, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[1][0x00002000], 8191, xcp_datatype_INT16}  // DAQ1
};
/* modulation_chirptype_0_its_ir24x odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_0_its_ir24x_ch2[2] = {
    {(uint32_t)&mod_daq_buffer[2][0x00000000], 4096, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[2][0x00002000], 8191, xcp_datatype_INT16}  // DAQ1
};
/* modulation_chirptype_0_its_ir24x odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_0_its_ir24x_ch3[2] = {
    {(uint32_t)&mod_daq_buffer[3][0x00000000], 4096, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[3][0x00002000], 8191, xcp_datatype_INT16}  // DAQ1
};
/* modulation_chirptype_1_its_ir24x_longfirst odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_1_its_ir24x_longfirst_ch0[2] = {
    {(uint32_t)&mod_daq_buffer[0][0x00000000], 8191, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[0][0x00004000], 4096, xcp_datatype_INT16}  // DAQ1
};
/* modulation_chirptype_1_its_ir24x_longfirst odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_1_its_ir24x_longfirst_ch1[2] = {
    {(uint32_t)&mod_daq_buffer[1][0x00000000], 8191, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[1][0x00004000], 4096, xcp_datatype_INT16}  // DAQ1
};
/* modulation_chirptype_1_its_ir24x_longfirst odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_1_its_ir24x_longfirst_ch2[2] = {
    {(uint32_t)&mod_daq_buffer[2][0x00000000], 8191, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[2][0x00004000], 4096, xcp_datatype_INT16}  // DAQ1
};
/* modulation_chirptype_1_its_ir24x_longfirst odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_1_its_ir24x_longfirst_ch3[2] = {
    {(uint32_t)&mod_daq_buffer[3][0x00000000], 8191, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[3][0x00004000], 4096, xcp_datatype_INT16}  // DAQ1
};
/* modulation_chirptype_2_its_kc odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_2_its_kc_ch0[3] = {
    {(uint32_t)&mod_daq_buffer[0][0x00000000], 2048, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[0][0x00001000], 4096, xcp_datatype_INT16}, // DAQ1
    {(uint32_t)&mod_daq_buffer[0][0x00003000], 8191, xcp_datatype_INT16}  // DAQ2
};
/* modulation_chirptype_2_its_kc odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_2_its_kc_ch1[3] = {
    {(uint32_t)&mod_daq_buffer[1][0x00000000], 2048, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[1][0x00001000], 4096, xcp_datatype_INT16}, // DAQ1
    {(uint32_t)&mod_daq_buffer[1][0x00003000], 8191, xcp_datatype_INT16}  // DAQ2
};
/* modulation_chirptype_2_its_kc odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_2_its_kc_ch2[3] = {
    {(uint32_t)&mod_daq_buffer[2][0x00000000], 2048, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[2][0x00001000], 4096, xcp_datatype_INT16}, // DAQ1
    {(uint32_t)&mod_daq_buffer[2][0x00003000], 8191, xcp_datatype_INT16}  // DAQ2
};
/* modulation_chirptype_2_its_kc odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_2_its_kc_ch3[3] = {
    {(uint32_t)&mod_daq_buffer[3][0x00000000], 2048, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[3][0x00001000], 4096, xcp_datatype_INT16}, // DAQ1
    {(uint32_t)&mod_daq_buffer[3][0x00003000], 8191, xcp_datatype_INT16}  // DAQ2
};
/* modulation_chirptype_3_slow24ghz odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_3_slow24ghz_ch0[32] = {
    {(uint32_t)&mod_daq_buffer[0][0x00000000], 16384, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[0][0x00008000], 16384, xcp_datatype_INT16}, // DAQ1
    {(uint32_t)&mod_daq_buffer[0][0x00010000], 16384, xcp_datatype_INT16}, // DAQ2
    {(uint32_t)&mod_daq_buffer[0][0x00018000], 16384, xcp_datatype_INT16}, // DAQ3
    {(uint32_t)&mod_daq_buffer[0][0x00020000], 16384, xcp_datatype_INT16}, // DAQ4
    {(uint32_t)&mod_daq_buffer[0][0x00028000], 16384, xcp_datatype_INT16}, // DAQ5
    {(uint32_t)&mod_daq_buffer[0][0x00030000], 16384, xcp_datatype_INT16}, // DAQ6
    {(uint32_t)&mod_daq_buffer[0][0x00038000], 16384, xcp_datatype_INT16}, // DAQ7
    {(uint32_t)&mod_daq_buffer[0][0x00040000], 16384, xcp_datatype_INT16}, // DAQ8
    {(uint32_t)&mod_daq_buffer[0][0x00048000], 16384, xcp_datatype_INT16}, // DAQ9
    {(uint32_t)&mod_daq_buffer[0][0x00050000], 16384, xcp_datatype_INT16}, // DAQ10
    {(uint32_t)&mod_daq_buffer[0][0x00058000], 16384, xcp_datatype_INT16}, // DAQ11
    {(uint32_t)&mod_daq_buffer[0][0x00060000], 16384, xcp_datatype_INT16}, // DAQ12
    {(uint32_t)&mod_daq_buffer[0][0x00068000], 16384, xcp_datatype_INT16}, // DAQ13
    {(uint32_t)&mod_daq_buffer[0][0x00070000], 16384, xcp_datatype_INT16}, // DAQ14
    {(uint32_t)&mod_daq_buffer[0][0x00078000], 16384, xcp_datatype_INT16}, // DAQ15
    {(uint32_t)&mod_daq_buffer[0][0x00080000], 16384, xcp_datatype_INT16}, // DAQ16
    {(uint32_t)&mod_daq_buffer[0][0x00088000], 16384, xcp_datatype_INT16}, // DAQ17
    {(uint32_t)&mod_daq_buffer[0][0x00090000], 16384, xcp_datatype_INT16}, // DAQ18
    {(uint32_t)&mod_daq_buffer[0][0x00098000], 16384, xcp_datatype_INT16}, // DAQ19
    {(uint32_t)&mod_daq_buffer[0][0x000A0000], 16384, xcp_datatype_INT16}, // DAQ20
    {(uint32_t)&mod_daq_buffer[0][0x000A8000], 16384, xcp_datatype_INT16}, // DAQ21
    {(uint32_t)&mod_daq_buffer[0][0x000B0000], 16384, xcp_datatype_INT16}, // DAQ22
    {(uint32_t)&mod_daq_buffer[0][0x000B8000], 16384, xcp_datatype_INT16}, // DAQ23
    {(uint32_t)&mod_daq_buffer[0][0x000C0000], 16384, xcp_datatype_INT16}, // DAQ24
    {(uint32_t)&mod_daq_buffer[0][0x000C8000], 16384, xcp_datatype_INT16}, // DAQ25
    {(uint32_t)&mod_daq_buffer[0][0x000D0000], 16384, xcp_datatype_INT16}, // DAQ26
    {(uint32_t)&mod_daq_buffer[0][0x000D8000], 16384, xcp_datatype_INT16}, // DAQ27
    {(uint32_t)&mod_daq_buffer[0][0x000E0000], 16384, xcp_datatype_INT16}, // DAQ28
    {(uint32_t)&mod_daq_buffer[0][0x000E8000], 16384, xcp_datatype_INT16}, // DAQ29
    {(uint32_t)&mod_daq_buffer[0][0x000F0000], 16384, xcp_datatype_INT16}, // DAQ30
    {(uint32_t)&mod_daq_buffer[0][0x000F8000], 16384, xcp_datatype_INT16}  // DAQ31
};
/* modulation_chirptype_3_slow24ghz odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_3_slow24ghz_ch1[32] = {
    {(uint32_t)&mod_daq_buffer[1][0x00000000], 16384, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[1][0x00008000], 16384, xcp_datatype_INT16}, // DAQ1
    {(uint32_t)&mod_daq_buffer[1][0x00010000], 16384, xcp_datatype_INT16}, // DAQ2
    {(uint32_t)&mod_daq_buffer[1][0x00018000], 16384, xcp_datatype_INT16}, // DAQ3
    {(uint32_t)&mod_daq_buffer[1][0x00020000], 16384, xcp_datatype_INT16}, // DAQ4
    {(uint32_t)&mod_daq_buffer[1][0x00028000], 16384, xcp_datatype_INT16}, // DAQ5
    {(uint32_t)&mod_daq_buffer[1][0x00030000], 16384, xcp_datatype_INT16}, // DAQ6
    {(uint32_t)&mod_daq_buffer[1][0x00038000], 16384, xcp_datatype_INT16}, // DAQ7
    {(uint32_t)&mod_daq_buffer[1][0x00040000], 16384, xcp_datatype_INT16}, // DAQ8
    {(uint32_t)&mod_daq_buffer[1][0x00048000], 16384, xcp_datatype_INT16}, // DAQ9
    {(uint32_t)&mod_daq_buffer[1][0x00050000], 16384, xcp_datatype_INT16}, // DAQ10
    {(uint32_t)&mod_daq_buffer[1][0x00058000], 16384, xcp_datatype_INT16}, // DAQ11
    {(uint32_t)&mod_daq_buffer[1][0x00060000], 16384, xcp_datatype_INT16}, // DAQ12
    {(uint32_t)&mod_daq_buffer[1][0x00068000], 16384, xcp_datatype_INT16}, // DAQ13
    {(uint32_t)&mod_daq_buffer[1][0x00070000], 16384, xcp_datatype_INT16}, // DAQ14
    {(uint32_t)&mod_daq_buffer[1][0x00078000], 16384, xcp_datatype_INT16}, // DAQ15
    {(uint32_t)&mod_daq_buffer[1][0x00080000], 16384, xcp_datatype_INT16}, // DAQ16
    {(uint32_t)&mod_daq_buffer[1][0x00088000], 16384, xcp_datatype_INT16}, // DAQ17
    {(uint32_t)&mod_daq_buffer[1][0x00090000], 16384, xcp_datatype_INT16}, // DAQ18
    {(uint32_t)&mod_daq_buffer[1][0x00098000], 16384, xcp_datatype_INT16}, // DAQ19
    {(uint32_t)&mod_daq_buffer[1][0x000A0000], 16384, xcp_datatype_INT16}, // DAQ20
    {(uint32_t)&mod_daq_buffer[1][0x000A8000], 16384, xcp_datatype_INT16}, // DAQ21
    {(uint32_t)&mod_daq_buffer[1][0x000B0000], 16384, xcp_datatype_INT16}, // DAQ22
    {(uint32_t)&mod_daq_buffer[1][0x000B8000], 16384, xcp_datatype_INT16}, // DAQ23
    {(uint32_t)&mod_daq_buffer[1][0x000C0000], 16384, xcp_datatype_INT16}, // DAQ24
    {(uint32_t)&mod_daq_buffer[1][0x000C8000], 16384, xcp_datatype_INT16}, // DAQ25
    {(uint32_t)&mod_daq_buffer[1][0x000D0000], 16384, xcp_datatype_INT16}, // DAQ26
    {(uint32_t)&mod_daq_buffer[1][0x000D8000], 16384, xcp_datatype_INT16}, // DAQ27
    {(uint32_t)&mod_daq_buffer[1][0x000E0000], 16384, xcp_datatype_INT16}, // DAQ28
    {(uint32_t)&mod_daq_buffer[1][0x000E8000], 16384, xcp_datatype_INT16}, // DAQ29
    {(uint32_t)&mod_daq_buffer[1][0x000F0000], 16384, xcp_datatype_INT16}, // DAQ30
    {(uint32_t)&mod_daq_buffer[1][0x000F8000], 16384, xcp_datatype_INT16}  // DAQ31
};
/* modulation_chirptype_3_slow24ghz odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_3_slow24ghz_ch2[32] = {
    {(uint32_t)&mod_daq_buffer[2][0x00000000], 16384, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[2][0x00008000], 16384, xcp_datatype_INT16}, // DAQ1
    {(uint32_t)&mod_daq_buffer[2][0x00010000], 16384, xcp_datatype_INT16}, // DAQ2
    {(uint32_t)&mod_daq_buffer[2][0x00018000], 16384, xcp_datatype_INT16}, // DAQ3
    {(uint32_t)&mod_daq_buffer[2][0x00020000], 16384, xcp_datatype_INT16}, // DAQ4
    {(uint32_t)&mod_daq_buffer[2][0x00028000], 16384, xcp_datatype_INT16}, // DAQ5
    {(uint32_t)&mod_daq_buffer[2][0x00030000], 16384, xcp_datatype_INT16}, // DAQ6
    {(uint32_t)&mod_daq_buffer[2][0x00038000], 16384, xcp_datatype_INT16}, // DAQ7
    {(uint32_t)&mod_daq_buffer[2][0x00040000], 16384, xcp_datatype_INT16}, // DAQ8
    {(uint32_t)&mod_daq_buffer[2][0x00048000], 16384, xcp_datatype_INT16}, // DAQ9
    {(uint32_t)&mod_daq_buffer[2][0x00050000], 16384, xcp_datatype_INT16}, // DAQ10
    {(uint32_t)&mod_daq_buffer[2][0x00058000], 16384, xcp_datatype_INT16}, // DAQ11
    {(uint32_t)&mod_daq_buffer[2][0x00060000], 16384, xcp_datatype_INT16}, // DAQ12
    {(uint32_t)&mod_daq_buffer[2][0x00068000], 16384, xcp_datatype_INT16}, // DAQ13
    {(uint32_t)&mod_daq_buffer[2][0x00070000], 16384, xcp_datatype_INT16}, // DAQ14
    {(uint32_t)&mod_daq_buffer[2][0x00078000], 16384, xcp_datatype_INT16}, // DAQ15
    {(uint32_t)&mod_daq_buffer[2][0x00080000], 16384, xcp_datatype_INT16}, // DAQ16
    {(uint32_t)&mod_daq_buffer[2][0x00088000], 16384, xcp_datatype_INT16}, // DAQ17
    {(uint32_t)&mod_daq_buffer[2][0x00090000], 16384, xcp_datatype_INT16}, // DAQ18
    {(uint32_t)&mod_daq_buffer[2][0x00098000], 16384, xcp_datatype_INT16}, // DAQ19
    {(uint32_t)&mod_daq_buffer[2][0x000A0000], 16384, xcp_datatype_INT16}, // DAQ20
    {(uint32_t)&mod_daq_buffer[2][0x000A8000], 16384, xcp_datatype_INT16}, // DAQ21
    {(uint32_t)&mod_daq_buffer[2][0x000B0000], 16384, xcp_datatype_INT16}, // DAQ22
    {(uint32_t)&mod_daq_buffer[2][0x000B8000], 16384, xcp_datatype_INT16}, // DAQ23
    {(uint32_t)&mod_daq_buffer[2][0x000C0000], 16384, xcp_datatype_INT16}, // DAQ24
    {(uint32_t)&mod_daq_buffer[2][0x000C8000], 16384, xcp_datatype_INT16}, // DAQ25
    {(uint32_t)&mod_daq_buffer[2][0x000D0000], 16384, xcp_datatype_INT16}, // DAQ26
    {(uint32_t)&mod_daq_buffer[2][0x000D8000], 16384, xcp_datatype_INT16}, // DAQ27
    {(uint32_t)&mod_daq_buffer[2][0x000E0000], 16384, xcp_datatype_INT16}, // DAQ28
    {(uint32_t)&mod_daq_buffer[2][0x000E8000], 16384, xcp_datatype_INT16}, // DAQ29
    {(uint32_t)&mod_daq_buffer[2][0x000F0000], 16384, xcp_datatype_INT16}, // DAQ30
    {(uint32_t)&mod_daq_buffer[2][0x000F8000], 16384, xcp_datatype_INT16}  // DAQ31
};
/* modulation_chirptype_3_slow24ghz odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_3_slow24ghz_ch3[32] = {
    {(uint32_t)&mod_daq_buffer[3][0x00000000], 16384, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[3][0x00008000], 16384, xcp_datatype_INT16}, // DAQ1
    {(uint32_t)&mod_daq_buffer[3][0x00010000], 16384, xcp_datatype_INT16}, // DAQ2
    {(uint32_t)&mod_daq_buffer[3][0x00018000], 16384, xcp_datatype_INT16}, // DAQ3
    {(uint32_t)&mod_daq_buffer[3][0x00020000], 16384, xcp_datatype_INT16}, // DAQ4
    {(uint32_t)&mod_daq_buffer[3][0x00028000], 16384, xcp_datatype_INT16}, // DAQ5
    {(uint32_t)&mod_daq_buffer[3][0x00030000], 16384, xcp_datatype_INT16}, // DAQ6
    {(uint32_t)&mod_daq_buffer[3][0x00038000], 16384, xcp_datatype_INT16}, // DAQ7
    {(uint32_t)&mod_daq_buffer[3][0x00040000], 16384, xcp_datatype_INT16}, // DAQ8
    {(uint32_t)&mod_daq_buffer[3][0x00048000], 16384, xcp_datatype_INT16}, // DAQ9
    {(uint32_t)&mod_daq_buffer[3][0x00050000], 16384, xcp_datatype_INT16}, // DAQ10
    {(uint32_t)&mod_daq_buffer[3][0x00058000], 16384, xcp_datatype_INT16}, // DAQ11
    {(uint32_t)&mod_daq_buffer[3][0x00060000], 16384, xcp_datatype_INT16}, // DAQ12
    {(uint32_t)&mod_daq_buffer[3][0x00068000], 16384, xcp_datatype_INT16}, // DAQ13
    {(uint32_t)&mod_daq_buffer[3][0x00070000], 16384, xcp_datatype_INT16}, // DAQ14
    {(uint32_t)&mod_daq_buffer[3][0x00078000], 16384, xcp_datatype_INT16}, // DAQ15
    {(uint32_t)&mod_daq_buffer[3][0x00080000], 16384, xcp_datatype_INT16}, // DAQ16
    {(uint32_t)&mod_daq_buffer[3][0x00088000], 16384, xcp_datatype_INT16}, // DAQ17
    {(uint32_t)&mod_daq_buffer[3][0x00090000], 16384, xcp_datatype_INT16}, // DAQ18
    {(uint32_t)&mod_daq_buffer[3][0x00098000], 16384, xcp_datatype_INT16}, // DAQ19
    {(uint32_t)&mod_daq_buffer[3][0x000A0000], 16384, xcp_datatype_INT16}, // DAQ20
    {(uint32_t)&mod_daq_buffer[3][0x000A8000], 16384, xcp_datatype_INT16}, // DAQ21
    {(uint32_t)&mod_daq_buffer[3][0x000B0000], 16384, xcp_datatype_INT16}, // DAQ22
    {(uint32_t)&mod_daq_buffer[3][0x000B8000], 16384, xcp_datatype_INT16}, // DAQ23
    {(uint32_t)&mod_daq_buffer[3][0x000C0000], 16384, xcp_datatype_INT16}, // DAQ24
    {(uint32_t)&mod_daq_buffer[3][0x000C8000], 16384, xcp_datatype_INT16}, // DAQ25
    {(uint32_t)&mod_daq_buffer[3][0x000D0000], 16384, xcp_datatype_INT16}, // DAQ26
    {(uint32_t)&mod_daq_buffer[3][0x000D8000], 16384, xcp_datatype_INT16}, // DAQ27
    {(uint32_t)&mod_daq_buffer[3][0x000E0000], 16384, xcp_datatype_INT16}, // DAQ28
    {(uint32_t)&mod_daq_buffer[3][0x000E8000], 16384, xcp_datatype_INT16}, // DAQ29
    {(uint32_t)&mod_daq_buffer[3][0x000F0000], 16384, xcp_datatype_INT16}, // DAQ30
    {(uint32_t)&mod_daq_buffer[3][0x000F8000], 16384, xcp_datatype_INT16}  // DAQ31
};
/* modulation_chirptype_4_freqmoving odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_4_freqmoving_ch0[4] = {
    {(uint32_t)&mod_daq_buffer[0][0x00000000], 16384, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[0][0x00008000], 16384, xcp_datatype_INT16}, // DAQ1
    {(uint32_t)&mod_daq_buffer[0][0x00010000], 16384, xcp_datatype_INT16}, // DAQ2
    {(uint32_t)&mod_daq_buffer[0][0x00018000], 16384, xcp_datatype_INT16}  // DAQ3
};
/* modulation_chirptype_4_freqmoving odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_4_freqmoving_ch1[4] = {
    {(uint32_t)&mod_daq_buffer[1][0x00000000], 16384, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[1][0x00008000], 16384, xcp_datatype_INT16}, // DAQ1
    {(uint32_t)&mod_daq_buffer[1][0x00010000], 16384, xcp_datatype_INT16}, // DAQ2
    {(uint32_t)&mod_daq_buffer[1][0x00018000], 16384, xcp_datatype_INT16}  // DAQ3
};
/* modulation_chirptype_4_freqmoving odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_4_freqmoving_ch2[4] = {
    {(uint32_t)&mod_daq_buffer[2][0x00000000], 16384, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[2][0x00008000], 16384, xcp_datatype_INT16}, // DAQ1
    {(uint32_t)&mod_daq_buffer[2][0x00010000], 16384, xcp_datatype_INT16}, // DAQ2
    {(uint32_t)&mod_daq_buffer[2][0x00018000], 16384, xcp_datatype_INT16}  // DAQ3
};
/* modulation_chirptype_4_freqmoving odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_4_freqmoving_ch3[4] = {
    {(uint32_t)&mod_daq_buffer[3][0x00000000], 16384, xcp_datatype_INT16}, // DAQ0
    {(uint32_t)&mod_daq_buffer[3][0x00008000], 16384, xcp_datatype_INT16}, // DAQ1
    {(uint32_t)&mod_daq_buffer[3][0x00010000], 16384, xcp_datatype_INT16}, // DAQ2
    {(uint32_t)&mod_daq_buffer[3][0x00018000], 16384, xcp_datatype_INT16}  // DAQ3
};
/* modulation_chirptype_5_79daq odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_5_79daq_ch0[1] = {
    {(uint32_t)&mod_daq_buffer[0][0x00000000], 2097152, xcp_datatype_INT16} // DAQ0
};
/* modulation_chirptype_5_79daq odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_5_79daq_ch1[1] = {
    {(uint32_t)&mod_daq_buffer[1][0x00000000], 2097152, xcp_datatype_INT16} // DAQ0
};
/* modulation_chirptype_5_79daq odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_5_79daq_ch2[1] = {
    {(uint32_t)&mod_daq_buffer[2][0x00000000], 2097152, xcp_datatype_INT16} // DAQ0
};
/* modulation_chirptype_5_79daq odt table */

xcp_odt_daq_entry_t xcp_odt_daqinfo_modulation_chirptype_5_79daq_ch3[1] = {
    {(uint32_t)&mod_daq_buffer[3][0x00000000], 2097152, xcp_datatype_INT16} // DAQ0
};

/***************************************************
 * function name : xcp_odt_info_set_resume_odtlist
 * description : set resume odtlist
 * input param : void
 * return : void
 * TODO :
 ***************************************************/
void xcp_odt_info_set_resume_odtlist(void)
{
    xcp_odt_add(xcp_odt_daqinfo_resume_odt_table_pid0, xcp_odt_daqinfo_resume_odt_table_pid0_cnt); // PID0
    xcp_odt_add(xcp_odt_daqinfo_resume_odt_table_pid1, xcp_odt_daqinfo_resume_odt_table_pid1_cnt); // PID1
}


/* end of file */
