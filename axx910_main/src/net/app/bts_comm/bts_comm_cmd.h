/************************************************************************
| Project Name: bts_comm_cmd
|    File Name: bts_comm_cmd.h
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
#ifndef bts_COMM_CMD_H__
#define bts_COMM_CMD_H__


#ifdef __cplusplus
extern "C" {
#endif

/* defination for module configuration parameters */
//###### COMMAND ####################
//# Master -> Slave
//# standard command
typedef enum {
    IR24XCOMMCMD_CONNECT = 0xFF,             //# optional : No Connect
    IR24XCOMMCMD_DISCONNECT = 0xFE,          //# optional : No DisConnect
    IR24XCOMMCMD_GET_STATUS = 0xFD,          //# optional : No
    IR24XCOMMCMD_SYNCH = 0xFC,               //# optional : No	Sync
    IR24XCOMMCMD_GET_COMM_MODE_INFO = 0xFB,  //# optional : Yes
    IR24XCOMMCMD_GET_ID = 0xFA,              //# optional : Yes
    IR24XCOMMCMD_SET_REQUEST = 0xF9,         //# optional : Yes
    IR24XCOMMCMD_GET_SEED = 0xF8,            //# optional : Yes
    IR24XCOMMCMD_UNLOCK = 0xF7,              //# optional : Yes
    IR24XCOMMCMD_SET_MTA = 0xF6,             //# optional : Yes
    IR24XCOMMCMD_UPLOAD = 0xF5,              //# optional : Yes
    IR24XCOMMCMD_SHORT_UPLOAD = 0xF4,        //# optional : Yes ReadById
    IR24XCOMMCMD_BUILD_CHECKSUM = 0xF3,      //# optional : Yes
    IR24XCOMMCMD_TRANSPORT_LAYER_CMD = 0xF2, //# optional : Yes
    IR24XCOMMCMD_USER_CMD = 0xF1,            //# optional : Yes ClientPresent
	IR24XCOMMCMD_USER_CMD_CLIENT_PRESENT = 0x00,
	IR24XCOMMCMD_USER_CMD_FLASH_BLOCK_UPDATE = 0x10,
	IR24XCOMMCMD_USER_CMD_FLASH_CACHE_UPDATE = 0x11,
	IR24XCOMMCMD_USER_CMD_FLASH_CACHE_STORE  = 0x12,

    //# calibraiton command
    IR24XCOMMCMD_DOWNLOAD = 0xF0,       //# optional : No
    IR24XCOMMCMD_DOWNLOAD_NEXT = 0xEF,  //# optional : Yes
    IR24XCOMMCMD_DOWNLOAD_MAX = 0xEE,   //# optional : Yes
    IR24XCOMMCMD_SHORT_DOWNLOAD = 0xED, //# optional : Yes WriteById
    IR24XCOMMCMD_MODIFY_BITS = 0xEC,    //# optional : Yes

    //# standard command
    IR24XCOMMCMD_SET_CAL_PAGE = 0xEB,           //# optional : No WriteById
    IR24XCOMMCMD_GET_CAL_PAGE = 0xEA,           //# optional : No ReadById
    IR24XCOMMCMD_GET_PAG_PROCESSOR_INFO = 0xE9, //# optional : Yes
    IR24XCOMMCMD_GET_SEGMENT_INFO = 0xE8,       //# optional : Yes
    IR24XCOMMCMD_GET_PAGE_INFO = 0xE7,          //# optional : Yes
    IR24XCOMMCMD_SET_SEGMENT_MODE = 0xE6,       //# optional : Yes
    IR24XCOMMCMD_GET_SEGMENT_MODE = 0xE5,       //# optional : Yes
    IR24XCOMMCMD_COPY_CAL_PAGE = 0xE4,          //# optional : Yes RoutineControl

    //# periodic data exchange -basic
    IR24XCOMMCMD_SET_DAQ_PTR = 0xE2,             //# optional : No
    IR24XCOMMCMD_WRITE_DAQ = 0xE1,               //# optional : No
    IR24XCOMMCMD_SET_DAQ_LIST_MODE = 0xE0,       //# optional : No
    IR24XCOMMCMD_START_STOP_DAQ_LIST = 0xDE,     //# optional : No
    IR24XCOMMCMD_START_STOP_SYNCH = 0xDD,        //# optional : No
    IR24XCOMMCMD_WRITE_DAQ_MULTIPLE = 0xC7,      //# optional : Yes
    IR24XCOMMCMD_READ_DAQ = 0xDB,                //# optional : Yes
    IR24XCOMMCMD_GET_DAQ_CLOCK = 0xDC,           //# optional : Yes
    IR24XCOMMCMD_GET_DAQ_PROCESSOR_INFO = 0xDA,  //# optional : Yes
    IR24XCOMMCMD_GET_DAQ_RESOLUTION_INFO = 0xD9, //# optional : Yes
    IR24XCOMMCMD_GET_DAQ_LIST_INFO = 0xD8,       //# optional : Yes
    IR24XCOMMCMD_GET_DAQ_EVENT_INFO = 0xD7,      //# optional : Yes

    //# periodic data exchange - static configuration
    IR24XCOMMCMD_CLEAR_DAQ_LIST = 0xE3, //# optional : No
    // IR24XCOMMCMD_GET_DAQ_LIST_INFO = 0xD8, //# optional : Yes

    //# periodic data exchange - dynamic configuration
    IR24XCOMMCMD_FREE_DAQ = 0xD6,        //# optional : Yes
    IR24XCOMMCMD_ALLOC_DAQ = 0xD5,       //# optional : Yes
    IR24XCOMMCMD_ALLOC_ODT = 0xD4,       //# optional : Yes
    IR24XCOMMCMD_ALLOC_ODT_ENTRY = 0xD3, //# optional : Yes

    //# flash programming
    IR24XCOMMCMD_PROGRAM_START = 0xD2,          //# optional : No
    IR24XCOMMCMD_PROGRAM_CLEAR = 0xD1,          //# optional : No
    IR24XCOMMCMD_PROGRAM = 0xD0,                //# optional : No
    IR24XCOMMCMD_PROGRAM_RESET = 0xCF,          //# optional : No
    IR24XCOMMCMD_GET_PGM_PROCESSOR_INFO = 0xCE, //# optional : Yes
    IR24XCOMMCMD_GET_SECTOR_INFO = 0xCD,        //# optional : Yes
    IR24XCOMMCMD_PROGRAM_PREPARE = 0xCC,        //# optional : Yes
    IR24XCOMMCMD_PROGRAM_FORMAT = 0xCB,         //# optional : Yes
    IR24XCOMMCMD_PROGRAM_NEXT = 0xCA,           //# optional : Yes
    IR24XCOMMCMD_PROGRAM_MAX = 0xC9,            //# optional : Yes
    IR24XCOMMCMD_PROGRAM_VERIFY = 0xC8,         //# optional : Yes
    IR24XCOMMCMD_END = 0xC0
} bts_comm_cmd_t;


typedef enum {
    // positive response code
    IR24XCOMMRESP_RES = 0xFF,
    // error response code
    IR24XCOMMRESP_ERR = 0xFE,
    IR24XCOMMRESP_ERR_CMD_SYNCH = 0x00,   //  Command processor synchronization.
    IR24XCOMMRESP_ERR_CMD_BUSY = 0x10,    // Command was not executed.
    IR24XCOMMRESP_ERR_DAQ_ACTIVE = 0x11,  // Command rejected because DAQ is running.
    IR24XCOMMRESP_ERR_PGM_ACTIVE = 0x12,  // Command rejected because PGM is running.
    IR24XCOMMRESP_ERR_CMD_UNKNOWN = 0x20, // Unknown command or not implemented optional command.
    IR24XCOMMRESP_ERR_CMD_SYNTAX = 0x21,  // Command syntax invalid.
    IR24XCOMMRESP_ERR_OUT_OF_RANGE =
        0x22, // Command syntax valid but command parameter(s) out of range.
    IR24XCOMMRESP_ERR_WRITE_PROTECTED = 0x23,   // The memory location is write protected.
    IR24XCOMMRESP_ERR_ACCESS_DENIED = 0x24,     // The memory location is not accessible.
    IR24XCOMMRESP_ERR_ACCESS_LOCKED = 0x25,     // Access denied,  Seed & Key is required.
    IR24XCOMMRESP_ERR_PAGE_NOT_VALID = 0x26,    // Selected page not available.
    IR24XCOMMRESP_ERR_MODE_NOT_VALID = 0x27,    // Selected page mode not available .
    IR24XCOMMRESP_ERR_SEGMENT_NOT_VALID = 0x28, // Selected segment not valid.
    IR24XCOMMRESP_ERR_SEQUENCE = 0x29,          // Sequence error.
    IR24XCOMMRESP_ERR_DAQ_CONFIG = 0x2A,        // DAQ configuration not valid.
    IR24XCOMMRESP_ERR_MEMORY_OVERFLOW = 0x30,   // Memory overflow error.
    IR24XCOMMRESP_ERR_GENERIC = 0x31,           // Generic error.
    IR24XCOMMRESP_ERR_VERIFY = 0x32, // The slave internal program verify routine  detects an error.
    IR24XCOMMRESP_ERR_RESOURCE_TEMPORARY_NOT_ACCESSIBLE =
        0x33, //  Access to the requested resource is  temporary not possible.
    // event response code
    IR24XCOMMRESP_EV = 0xFD,
    IR24XCOMMRESP_EV_RESUME_MODE = 0x00,
    IR24XCOMMRESP_EV_CLEAR_DAQ = 0x01,
    IR24XCOMMRESP_EV_STORE_DAQ = 0x02,
    IR24XCOMMRESP_EV_STORE_CAL = 0x03,
    IR24XCOMMRESP_EV_CMD_PENDING = 0x05,
    IR24XCOMMRESP_EV_DAQ_OVERLOAD = 0x06,
    IR24XCOMMRESP_EV_SESSION_TERMINATED = 0x07,
    IR24XCOMMRESP_EV_TIME_SYNC = 0x08,
    IR24XCOMMRESP_EV_STIM_TIMEOUT = 0x09,
    IR24XCOMMRESP_EV_SLEEP = 0x0A,
    IR24XCOMMRESP_EV_WAKE_UP = 0x0B,
    IR24XCOMMRESP_EV_USER = 0xFE,
    IR24XCOMMRESP_EV_TRANSPORT = 0xFF,
    // serv response code
    IR24XCOMMRESP_SERV = 0xFC,
    IR24XCOMMRESP_SERV_RESET = 0x00,
    IR24XCOMMRESP_SERV_TEXT = 0x01
} bts_comm_resp_t;


#ifdef __cplusplus
}
#endif
#endif // bts_COMM_CMD_H__
