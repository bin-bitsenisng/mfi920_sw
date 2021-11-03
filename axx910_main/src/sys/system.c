/************************************************************************
 | Project Name: KRS24
 |    File Name: system.c
 |  Description: detailed Description
 |-----------------------------------------------------------------------
 |               A U T H O R   I D E N T I T Y
 |-----------------------------------------------------------------------
 | Initials     Name                      Company
 | --------     ---------------------     -------------------------------
 | SKJ          SONG KYEONG JIN           KRS Corporation
 |-----------------------------------------------------------------------
 |              R E V I S I O N   H I S T O R Y
 |-----------------------------------------------------------------------
 | Date         Ver  Author  Description
 | ----------  ----  ------  --------------------------------------------
 | 2014.12.02   0.0   SKJ   Creation;
 |***********************************************************************/

/* include system primitive types */
#include "bts.h"
#include "sys_build_defs.h"
#include "sys_param.h"
#include "system_cfg.h"
/* include system driver header */


/* include system bsp header */


/* include system application header */


/* final include module header */
#include "system.h"
//#include "drivers.h"

/* declare global variables */

/* declare static variables */
sys_param_system_status_t system_status;

const sys_param_common_comm_ethernet_config_t ethernet_config_factorydefault = {
    /*.ip=*/"192.168.10.150",
    /*.nm=*/"255.255.255.0",
    /*.gw=*/"192.168.10.1",
    /*.mac=*/"02:01:02:03:04:05", // x2:xx:xx:xx:xx:xx
    /*.dns=*/"208.67.222.222",
    /*.linkspeed=*/0, // 1000, 100, 10, 0(auto)
    /*.dhcp_en =  */ 0};


/* static function prototypes */
int32_t pre_macro_date_to_int(const char *str_pre_macro_date);
int32_t pre_macro_time_to_int(const char *str_pre_macro_time);
/* functions */

/******************************************************************************
 * function name : system_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 void description
 * \return0 system_ret_t description
 * modification date : 2019.11.28
 *****************************************************************************/
system_ret_t system_init(void)
{
    /* module init code here*/
	krs_log("\n"
	           " ___       _                                                   \n"
	           "(  _`\\  _ ( )_                            _                   \n"
	           "| (_) )(_)| ,_)  ___    __    ___    ___ (_)  ___     __       \n"
	           "|  _ <'| || |  /',__) /'__`\\/' _ `\\/',__)| |/' _ `\\ /'_ `\\ \n"
	           "| (_) )| || |_ \\__, \\(  ___/| ( ) |\\__, \\| || ( ) |( (_) | \n"
	           "(____/'(_)`\\__)(____/`\\____)(_) (_)(____/(_)(_) (_)`\\__  |  \n"
	           "                                                   ( )_) |     \n"
	           "                                                    \\___/'    \n");
    krs_log("SW Version : %s\n\r", SYS_SW_VERSION);
    krs_log("DEV UID : 0x%016llX\n\r",system_devuid());
    krs_log("HW BE Version: %s\n\r", SYS_HW_BE_VERSION);
    krs_log("HW RFM Version: %s\n\r", SYS_HW_FE_VERSION);
    krs_log("SW Build Date: %s : %s\n\r", SYS_BUILD_DATE, SYS_BUILD_TIME);
    return retOK;
}

/******************************************************************************
 * function name : system_swbuild_date
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 void description
 * \return0 int32_t description
 * modification date : 2019.11.28
 *****************************************************************************/
int32_t system_swbuild_date(void) { return pre_macro_date_to_int(SYS_BUILD_DATE); }

/******************************************************************************
 * function name : system_swbuild_time
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 void description
 * \return0 int32_t description
 * modification date : 2019.11.28
 *****************************************************************************/
int32_t system_swbuild_time(void) { return pre_macro_time_to_int(SYS_BUILD_TIME); }


uint64_t system_devuid(void)
{
	//return ip_drv_get_device_uid();
    return SYS_DEVUID_TEMP;
}

int32_t system_devuid_str(char *buff, size_t buffsize)
{
	union64_t devuid;
	if(buffsize < 16)
	{
		return retFail;
	}
	devuid.Q = system_devuid();
	//snprintf(buff, buffsize, "%08X%08X", devuid.L[1], devuid.L[0]);
	snprintf(buff, buffsize, "%016llX", devuid.Q);
	return retOK;
}


uint64_t system_devuid_fromstr(char *buff, size_t buffsize)
{
	uint64_t devuid;
	if(buffsize < 16)
	{
		return retFail;
	}
	sscanf(buff, "%llX", &devuid);
	return devuid;
}


int32_t system_get_status_to_json(char_t *buff, size_t buffsize)
{
    int32_t jsonsize;


    if(buffsize < SYS_PARAM_JSON_BUFFER_SIZE)
    {
        krs_log("buffsize is less than SYS_PARAM_JSON_BUFFER_SIZE\n\r");
        return 0;
    }

    krs_memclearitem(system_status);

    /* device unique ID */
    system_devuid_str(system_status.devuid, sizeof(system_status.devuid));
    /* device serial number */
    strncpy(system_status.serialnumber, SYS_PARAM_SENSORTYPE.serialnumber, SYS_PARAM_STRLEN_MAX);
    /* device sw informations */
    strncpy(system_status.swappname, SYS_APP_NAME, SYS_PARAM_STRLEN_MAX);
    strncpy(system_status.swversion, SYS_SW_VERSION, SYS_PARAM_STRLEN_MAX);
    system_status.swdate = system_swbuild_date();
    system_status.swtime = system_swbuild_time();

    system_status.sid0did0_systembase_config = SYS_PARAM.sid0did0_systembase_config;
    system_status.sid0did1_datetime_config = SYS_PARAM.sid0did1_datetime_config;
    system_status.sid0did2_security_config = SYS_PARAM.sid0did2_security_config;
    system_status.sid0did4_infra_config = SYS_PARAM.sid0did4_infra_config;
    system_status.sid0did5_serialnumber_config = SYS_PARAM.sid0did5_serialnumber_config;
    system_status.sid0did6_location_config = SYS_PARAM.sid0did6_location_config;
    system_status.sid0did8_rs485_protocol_config = SYS_PARAM.sid0did8_rs485_protocol_config;
    system_status.sid0did10_rsp_eol_config = SYS_PARAM.sid0did10_rsp_eol_config;
    system_status.sid0did11_rsp_install_config = SYS_PARAM.sid0did11_rsp_install_config;
    system_status.sid0did12_rsm_config = SYS_PARAM.sid0did12_rsm_config;
    system_status.sid0did13_rsptrk_config = SYS_PARAM.sid0did13_rsptrk_config;
    system_status.sid0did200_app_packet_config = SYS_PARAM.sid0did200_app_packet_config;
    system_status.sid8did0_its_config = SYS_PARAM.sid8did0_its_config;
    system_status.sid8did1_its_relay_config = SYS_PARAM.sid8did1_its_relay_config;
    system_status.sid8did2_its_align_config = SYS_PARAM.sid8did2_its_align_config;
    system_status.sid8did10_its_testmode_config = SYS_PARAM.sid8did10_its_testmode_config;


    jsonsize = sys_param_system_status_t_dump("", buff, (void*)&system_status);

    return jsonsize;
}

/******************************************************************************
 * function name : pre_macro_date_to_int
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *str_pre_macro_date description
 * \return0 int32_t description
 * modification date : 2019.11.28
 *****************************************************************************/
int32_t pre_macro_date_to_int(const char *str_pre_macro_date)
{
    const int comfile_date_len = 12;

    // error check
    if(NULL == str_pre_macro_date || comfile_date_len - 1 != strlen(str_pre_macro_date))
        return 0;

    const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

    char s_month[5] = {
        0,
    };
    int iyear = 0, iday = 0;

    sscanf(str_pre_macro_date, "%s %d %d", s_month, &iday, &iyear);
    int imonth = (strstr(month_names, s_month) - month_names) / 3 + 1;

    // 2010 12 01
    return 10000 * iyear + 100 * imonth + iday;
}


/******************************************************************************
 * function name : pre_macro_time_to_int
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *str_pre_macro_time description
 * \return0 int32_t description
 * modification date : 2019.11.28
 *****************************************************************************/
int32_t pre_macro_time_to_int(const char *str_pre_macro_time)
{
    const int comfile_time_len = 9;

    if(NULL == str_pre_macro_time || comfile_time_len - 1 != strlen(str_pre_macro_time))
        return 0;

    int ihour = 0, iminute = 0, isec = 0;
    sscanf(str_pre_macro_time, "%d:%d:%d", &ihour, &iminute, &isec);

    // 030511
    return ihour * 10000 + iminute * 100 + isec;
}





/* end of file */
