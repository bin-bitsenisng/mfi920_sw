/************************************************************************
| Project Name: bts_comm_status
|    File Name: bts_comm_status.h
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
#ifndef bts_COMM_STATUS_H__
#define bts_COMM_STATUS_H__
#ifdef __cplusplus
extern "C" {
#endif


/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "bts.h"

#include "bts_comm_cfg.h"
#include "bts_comm_cmd.h"
#include "bts_comm_packet.h"

#include "os.h"
/* module specific types  */
typedef enum {
    bts_comm_status_disconnected,
    bts_comm_status_connected,
    bts_comm_status_disconnectrequested
} bts_comm_status_connect_t;

typedef enum {
    bts_comm_status_connectmode_normal,
    bts_comm_status_connectmode_userdefined
} bts_comm_status_connectmode_t;

typedef enum {
    bts_comm_status_start_stop_synch_mode_stop_all = 0,
    bts_comm_status_start_stop_synch_mode_start_selected = 1,
    bts_comm_status_start_stop_synch_mode_stop_selected = 2,
    bts_comm_status_start_stop_synch_mode_max
} bts_comm_status_start_stop_synch_mode_t;


typedef enum {
    bts_comm_status_daq_idle = 0,
    bts_comm_status_daq_active = 0x04
} bts_comm_status_daq_t;


typedef enum {
    bts_comm_status_stim_idle = 0,
    bts_comm_status_stim_active = 0x08
} bts_comm_status_stim_t;

typedef enum { bts_comm_status_cmd_idle, bts_comm_status_cmd_busy } bts_comm_status_cmd_t;

typedef enum {
    bts_comm_status_pgm_idle = 0,
    bts_comm_status_pgm_active = 0x10
} bts_comm_status_pgm_t;

typedef enum {
    bts_comm_status_calpag_idle = 0,
    bts_comm_status_calpag_active = 0x01
} bts_comm_status_calpag_t;
typedef enum {
    bts_comm_status_securityaceess_lock,
    bts_comm_status_securityaceess_seedkey,
    bts_comm_status_securityaceess_unlock
} bts_comm_status_securityaccess_t;

typedef enum {
    bts_comm_event_0,
    bts_comm_event_1,
    bts_comm_event_2,
    bts_comm_event_3,
    bts_comm_event_4,
    bts_comm_event_5,
    bts_comm_event_max
} bts_comm_event_type_t;

typedef enum {
    bts_comm_param_commodebasic_byteorder_le = 0x00,
    bts_comm_param_commodebasic_byteorder_be = 0x01,
    bts_comm_param_commodebasic_addrgr_byte = 0x00,
    bts_comm_param_commodebasic_addrgr_word = 0x02,
    bts_comm_param_commodebasic_addrgr_dword = 0x04,
    bts_comm_param_commodebasic_slaveblockmode_none = 0x00,
    bts_comm_param_commodebasic_slaveblockmode_available = 0x40,
    bts_comm_param_commodebasic_optional_nond = 0x00,
    bts_comm_param_commodebasic_optional_available = 0x80
} bts_comm_param_commodebasic_t;


typedef enum {
    bts_comm_param_getdaqprocessorinfo_keybyte_optimisation_default = 0,
    bts_comm_param_getdaqprocessorinfo_keybyte_optimisation_odttype16 = 1,
    bts_comm_param_getdaqprocessorinfo_keybyte_optimisation_odttype32 = 2,
    bts_comm_param_getdaqprocessorinfo_keybyte_optimisation_odttype64 = 3,
    bts_comm_param_getdaqprocessorinfo_keybyte_optimisation_odttypealignment = 4,
    bts_comm_param_getdaqprocessorinfo_keybyte_optimisation_maxentrysize = 5,
    bts_comm_param_getdaqprocessorinfo_keybyte_address_extension_odt = 0x10,
    bts_comm_param_getdaqprocessorinfo_keybyte_address_extension_daq = 0x20,


    bts_comm_param_getdaqprocessorinfo_keybyte_identification_absolute_odtnumber = 0x00,
    bts_comm_param_getdaqprocessorinfo_keybyte_identification_relodt_absdaq_byte = 0x40,
    bts_comm_param_getdaqprocessorinfo_keybyte_identification_relodt_absdaq_word = 0x80,
    bts_comm_param_getdaqprocessorinfo_keybyte_identification_relodt_absdaq_wordaligned = 0xC0,
    bts_comm_param_getdaqprocessorinfo_keybyte_identification_field_type0 = 0x40,
    bts_comm_param_getdaqprocessorinfo_keybyte_identification_field_type1 = 0x80
} bts_comm_get_daq_processor_info_daq_key_byte_t;


typedef enum {
    bts_comm_param_getdaqprocessorinfo_daq_config_type = 0x01,
    bts_comm_param_getdaqprocessorinfo_prescaler_supported = 0x02,
    bts_comm_param_getdaqprocessorinfo_resume_supported = 0x04,
    bts_comm_param_getdaqprocessorinfo_bit_stim_supported = 0x08,
    bts_comm_param_getdaqprocessorinfo_timestamp_supported = 0x10,
    bts_comm_param_getdaqprocessorinfo_pid_off_supported = 0x20,
    bts_comm_param_getdaqprocessorinfo_overload_msb = 0x40,
    bts_comm_param_getdaqprocessorinfo_overload_event = 0x80
} bts_comm_get_param_daqprocessor_daq_properties_t;


typedef enum {
    bts_comm_param_setdaqlistmode_alternating = 0x01,
    bts_comm_param_setdaqlistmode_direction = 0x02,
    bts_comm_param_setdaqlistmode_timestamp = 0x10,
    bts_comm_param_setdaqlistmode_pid_off = 0x20
} bts_comm_param_setdaqlistmode_t;


typedef enum {
    bts_comm_param_getdaqlistmode_selected = 0x01,
    bts_comm_param_getdaqlistmode_direction = 0x02,
    bts_comm_param_getdaqlistmode_timestamp = 0x10,
    bts_comm_param_getdaqlistmode_pid_off = 0x20,
    bts_comm_param_getdaqlistmode_running = 0x40,
    bts_comm_param_getdaqlistmode_resume = 0x80
} bts_comm_param_getdaqlistmode_t;


typedef enum {
    bts_comm_param_getdaqlistinfo_daqlistproperties_predefined = 0x01,
    bts_comm_param_getdaqlistinfo_daqlistproperties_event_fixed = 0x02,
    bts_comm_param_getdaqlistinfo_daqlistproperties_daq = 0x04,
    bts_comm_param_getdaqlistinfo_daqlistproperties_stim = 0x08
} bts_comm_param_getdaqlistinfo_daqlistproperties_t;

typedef enum {
    bts_comm_param_getdaqeventinfo_daqeventproperties_daq = 0x04,
    bts_comm_param_getdaqeventinfo_daqeventproperties_stim = 0x08,
    bts_comm_param_getdaqeventinfo_daqeventproperties_consistency_daq = 0x40,
    bts_comm_param_getdaqeventinfo_daqeventproperties_consistency_event = 0x80
} bts_comm_param_getdaqeventinfo_daqeventproperties_t;


typedef enum {
    bts_comm_param_getdaqresolutioninfo_timestampmode_size0 = 0x01,
    bts_comm_param_getdaqresolutioninfo_timestampmode_size1 = 0x02,
    bts_comm_param_getdaqresolutioninfo_timestampmode_size2 = 0x04,
    bts_comm_param_getdaqresolutioninfo_timestampmode_notimestamp = 0x00,
    bts_comm_param_getdaqresolutioninfo_timestampmode_size_byte = 0x01,
    bts_comm_param_getdaqresolutioninfo_timestampmode_size_word = 0x02,
    bts_comm_param_getdaqresolutioninfo_timestampmode_size_dword = 0x04,

    bts_comm_param_getdaqresolutioninfo_timestampmode_fixed = 0x08,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit0 = 0x10,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit1 = 0x20,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit2 = 0x40,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit3 = 0x80,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit_1ns = 0x00,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit_10ns = 0x10,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit_100ns = 0x20,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit_1us = 0x30,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit_10us = 0x40,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit_100us = 0x50,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit_1ms = 0x60,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit_10ms = 0x70,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit_100ms = 0x80,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit_1s = 0x90,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit_1ps = 0xA0,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit_10ps = 0xB0,
    bts_comm_param_getdaqresolutioninfo_timestampmode_unit_100ps = 0xC0

} bts_comm_param_getdaqresolutioninfo_timestampmode_t;


typedef struct
{
    uint16_t daqnumber;
    uint8_t odtnumber;
    uint8_t odtentrynumber;
} bts_comm_daq_ptr_t;


typedef enum {
    bts_comm_odt_status_disable,
    bts_comm_odt_status_event,
    bts_comm_odt_status_sync
} bts_comm_odt_status_t;


typedef struct
{
    uint8_t mode;
    uint16_t event_channel;
    uint8_t prescaler;
    uint8_t priority;
    bts_comm_odt_status_t odtstatus;
} bts_comm_daqmodestatus_t;


typedef struct
{
    // status connection
    bts_comm_status_connect_t connect;
    bts_comm_status_connectmode_t connectmode;
    // status resouce
    bts_comm_status_calpag_t calpag;
    bts_comm_status_daq_t daq;
    bts_comm_status_stim_t stim;
    bts_comm_status_pgm_t pgm;
    bts_comm_status_start_stop_synch_mode_t globalstartstopmode;
    bts_comm_status_cmd_t cmd;
    bts_comm_status_securityaccess_t access_lock;
    // resource variable
    uint8_t resource;

    // mta
    uint32_t mta_address;
    uint8_t mta_address_extention;

    bts_comm_daq_ptr_t daqptr;

    // timeout control
    uint32_t connection_currtime;
    uint32_t connection_elapstime;

} bts_comm_status_info_t;

/* define structure for this module */


extern bts_comm_status_info_t bts_comm_status;
extern os_sem_t sem_bts_comm_status_daq_start;


#define Ir24xCommStatusReset() krs_memset(&bts_comm_status, 0, sizeof(bts_comm_status))
// xcp is connect or disconnect?

#define Ir24xCommGetIsConnected() (bts_comm_status.connect == bts_comm_status_connected)
#define Ir24xCommGetIsDisconnectRequested() \
    (bts_comm_status.connect == bts_comm_status_disconnectrequested)
#define Ir24xCommSetConnectMode(x) bts_comm_status.connect = (x)
#define Ir24xCommSetConnected() bts_comm_status.connect = bts_comm_status_connected
#define Ir24xCommSetDisconnected() bts_comm_status.connect = bts_comm_status_disconnected
#define Ir24xCommSetDisconnectRequested() \
    bts_comm_status.connect = bts_comm_status_disconnectrequested


#define Ir24xCommGetIsConnectModeNormal() \
    (bts_comm_status.connectmode == bts_comm_status_connectmode_normal)
#define Ir24xCommGetIsConnectModeUserDefined() \
    (bts_comm_status.connectmode == bts_comm_status_connectmode_userdefined)
#define Ir24xCommSetConnectModeNormal() \
    bts_comm_status.connectmode = bts_comm_status_connectmode_normal
#define Ir24xCommSetConnectModeUserDefined() \
    bts_comm_status.connect_mode = bts_comm_status_connectmode_userdefined


#define Ir24xCommGetStartStopSynchMode() bts_comm_status.globalstartstopmode
#define Ir24xCommSetStartStopSynchMode(x) bts_comm_status.globalstartstopmode = (x)
#define Ir24xCommSetStartStopSynchModeStart() \
    Ir24xCommSetStartStopSynchMode(bts_comm_status_start_stop_synch_mode_start_selected)
#define Ir24xCommGetIsStartStopSynchModeStart() \
    (Ir24xCommGetStartStopSynchMode() == bts_comm_status_start_stop_synch_mode_start_selected)
#define Ir24xCommSetStartStopSynchModeStop() \
    Ir24xCommSetStartStopSynchMode(bts_comm_status_start_stop_synch_mode_stop_all)
#define Ir24xCommGetIsStartStopSynchModeStopAll() \
    (Ir24xCommGetStartStopSynchMode() == bts_comm_status_start_stop_synch_mode_stop_all)


#define Ir24xCommGetIsDaqStatusActive() (bts_comm_status.daq == bts_comm_status_daq_active)
#define Ir24xCommSetDaqStatusIdle() bts_comm_status.daq = bts_comm_status_daq_idle
#define Ir24xCommSetDaqStatusActive() bts_comm_status.daq = bts_comm_status_daq_active

#define Ir24xCommGetIsStimStatusActive() (bts_comm_status.stim == bts_comm_status_stim_active)
#define Ir24xCommSetStimStatusIdle() bts_comm_status.stim = bts_comm_status_stim_idle
#define Ir24xCommSetStimStatusActive() bts_comm_status.stim = bts_comm_status_stim_active

#define Ir24xCommSetDaqPtr(daq, odt, entry)   \
    bts_comm_status.daqptr.daqnumber = daq; \
    bts_comm_status.daqptr.odtnumber = odt; \
    bts_comm_status.daqptr.odtentrynumber = entry
#define Ir24xCommGetDaqPtrDaqNumber() bts_comm_status.daqptr.daqnumber
#define Ir24xCommGetDaqPtrOdtNumber() bts_comm_status.daqptr.odtnumber

// resource
#define Ir24xCommSetResource(calpag, daq, stim, pgm) \
    bts_comm_status.resource = ((calpag) | (daq) | (stim) | (pgm))
#define Ir24xCommGetResource() bts_comm_status.resource


// MTA
#define Ir24xCommSetMta(ext, addr)          \
    bts_comm_status.mta_address = (addr); \
    bts_comm_status.mta_address_extention = (ext)
#define Ir24xCommGetMta() bts_comm_status.mta_address
#define Ir24xCommGetMtaExt() bts_comm_status.mta_address_extention

/* declare global variables */

/* declare extern global variables */

/* declare extern global functions */
extern void bts_comm_status_init(void);

#ifdef __cplusplus
}
#endif
#endif /* bts_COMM_STATUS_H__ */
