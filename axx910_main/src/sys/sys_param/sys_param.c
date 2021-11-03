/************************************************************************
 | Project Name: KRS24
 |    File Name: sys_param.c
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
#include "sys_param_cfg.h"

/* include system driver header */


/* include system bsp header */


/* include system application header */


/* final include module header */
//#include "filesystem.h"
#include "linux_fs_app_cfg.h"
#include "sys_param.h"
#include "linux_fs.h"

/* declare global variables */
int8_t sys_param_jsonbuff[65536 * 2];

/* declare static variables */


/* static function prototypes */

/* functions */
/******************************************************************************
 * function name : sys_param_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return int32_t description
 * modification date : 2019.09.06
 *****************************************************************************/
int32_t sys_param_init(void)
{
    /* module init code here*/
    return retOK;
}


/******************************************************************************
 * function name : sys_param_get_typename_hash
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 *str description
 * \param1 n description
 * \return uint32_t description
 * modification date : 2019.09.06
 *****************************************************************************/
uint32_t sys_param_get_typename_hash(char *str, size_t n)
{
    uint32_t hash = 5381;
    uint32_t c;

    c = (uint32_t)(*str++);
    while(c)
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        if(--n <= 0)
            break;
        c = (uint32_t)(*str++);
    }
    return hash;
}

/******************************************************************************
 * function name : sys_param_load_from_default
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 filename description
 * \param1 *param description
 * \return int32_t description
 * modification date : 2019.09.06
 *****************************************************************************/
int32_t sys_param_load_from_default(void)
{
    int32_t* dest;
    dest = memcpy(&sys_param_sidxdidx_configinfo_packing, &sys_param_sidxdidx_configinfo_packing_default, sizeof(sys_param_sidxdidx_configinfo_packing_t));

    if(dest != NULL)
        return retOK;
    else
        return retFail;
}

/******************************************************************************
 * function name : sys_param_load_from_file
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 filename description
 * \param1 *param description
 * \return int32_t description
 * modification date : 2019.09.06
 *****************************************************************************/
int32_t sys_param_load_from_file(const char *filename, void *param)
{
#if SYS_PARAM_FROMFILE_EN == 1
    int32_t len;
    int32_t err;
    int32_t readsize;
    spiffs_file fd = fs_spiffs_open(filename, SPIFFS_RDWR, 0);

    len = 0;
    while(!fs_spiffs_eof(fd))
    {
        readsize = fs_spiffs_read(fd, &sys_param_jsonbuff[len], 1024);
        krs_log("read:%d, len:%d\n\r", readsize, len);

        if(readsize < 0)
        {
            err = fs_spiffs_errno();
            krs_log("spiffs read error %d, %s\n\r", err, fs_spiffs_errtext(err));
            break;
        }
        len += readsize;
    }
    fs_spiffs_close(fd);
    krs_log_gb("%s read size is %d\n\r", filename, len);

    // krs_log("%.*s\n\r", len, sys_param_jsonbuff);

    len = sys_param_sidxdidx_configinfo_packing_t_loads((char *)sys_param_jsonbuff, len, param);

    krs_debugcheck(len != 0, "json load from %s is fail", filename);

#elif SYS_PARAM_FROMFILE_LINUX_EN == 1
    int32_t len;
    int8_t* temp_data_pointer;

    temp_data_pointer = ReadFile(filename, &len);

    memcpy(sys_param_jsonbuff, temp_data_pointer, len);
    //krs_log_gb("%s read size is %d\n\r", filename, len);

    len = sys_param_sidxdidx_configinfo_packing_t_loads((char *)sys_param_jsonbuff, len, param); 
    krs_debugcheck(len != 0, "json load from %s is fail\n", filename);

#endif
    return retOK;
}


/******************************************************************************
 * function name : sys_param_save_to_file
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 filename description
 * \param1 *param description
 * \return int32_t description
 * modification date : 2019.09.06
 *****************************************************************************/
int32_t sys_param_save_to_file(const char *filename, void *param)
{
#if SYS_PARAM_FROMFILE_EN == 1
    int32_t len;
    int32_t err;
    int32_t ret;
    spiffs_file fd;
    len = sys_param_sidxdidx_configinfo_packing_t_dump("", (char *)sys_param_jsonbuff, param);
    krs_debugcheck(len > 0, "sys_param_save_to_file: json dump fail");

    // backup file remove

    fd = fs_spiffs_open("backup.jsn", SPIFFS_RDWR, 0);
    if(fd > 0)
    {
        ret = fs_spiffs_fremove(fd);
        krs_log_gb("backup.jsn remove : %d, %s\n\r", ret, fs_spiffs_errtext(ret));
        fs_spiffs_close(fd);
    }
    // backup current filename
    ret = fs_spiffs_rename(filename, "backup.jsn");
    krs_log_gb("current %s file rename as backup.jsn : %d, %s\n\r", filename, ret,
               fs_spiffs_errtext(ret));
    // write new filename
    krs_log_gb("json dump success, json length is %d\n\r", len);
    fd = fs_spiffs_open(filename, SPIFFS_CREAT | SPIFFS_TRUNC | SPIFFS_RDWR, 0);
    krs_log_gb("json file open : %s\n\r", filename);

    if(fs_spiffs_write(fd, sys_param_jsonbuff, len) < 0)
    {
        err = fs_spiffs_errno();
        krs_log("spiffs write %s error, errcode=%d, errtext=%s\n\r", filename, err,
                fs_spiffs_errtext(err));
        return retFail;
    }
    fs_spiffs_close(fd);

#elif SYS_PARAM_FROMFILE_LINUX_EN == 1
    int32_t ret;
    int32_t len;
    len = sys_param_sidxdidx_configinfo_packing_t_dump("", (char *)sys_param_jsonbuff, param);
    ret = WriteFile(filename, sys_param_jsonbuff, len);

    return ret;

#endif
    return retOK;
}


/******************************************************************************
 * function name : sys_param_factoryinit
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 void description
 * \return0 int32_t description
 * modification date : 2020.09.08
 *****************************************************************************/
int32_t sys_param_factoryinit(void)
{
    int32_t ret;

    // backup file remove
    //ret = mtd_erase_section(mtd_dev_spiflash, mtd_sections_factory);
    //ret = retFail;
    //krs_debugcheck(ret == retOK, "erasing mtd_sections_factory section is fail");

    //ret = mtd_blankcheck_section(mtd_dev_spiflash, mtd_sections_factory, 0, 0);
    ret = remove(SYS_PARAM_FILE_PATH_FACTORY);
    krs_debugcheck(ret == retOK, "blankchecking mtd_sections_factory section is fail");
    //return retOK;
    return ret;
}


/******************************************************************************
 * function name : sys_param_save_to_factory
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *param description
 * \return0 int32_t description
 * modification date : 2020.09.08
 *****************************************************************************/
int32_t sys_param_save_to_factory(void *param)
{
    int32_t len;
    int32_t ret;
    int32_t i;

    //insert array terminator
    for(i=0;i<SYS_PARAM_RSPCFG_RXCHANNEL_MAX;i++)
    {
    	sys_param_sidxdidx_configinfo_packing.sid0did10_rsp_eol_config.setup.azibeampattern_up[SYS_PARAM_RSPCFG_AZIBPNUM][i] = SYS_PARAM_F32_ARR_END_VALUE;
    	sys_param_sidxdidx_configinfo_packing.sid0did10_rsp_eol_config.setup.azibeamphase_up[SYS_PARAM_RSPCFG_AZIBPNUM][i] = SYS_PARAM_F32_ARR_END_VALUE;
    	sys_param_sidxdidx_configinfo_packing.sid0did10_rsp_eol_config.setup.azibeampattern_dn[SYS_PARAM_RSPCFG_AZIBPNUM][i] = SYS_PARAM_F32_ARR_END_VALUE;
    	sys_param_sidxdidx_configinfo_packing.sid0did10_rsp_eol_config.setup.azibeamphase_dn[SYS_PARAM_RSPCFG_AZIBPNUM][i] = SYS_PARAM_F32_ARR_END_VALUE;
    }


    len = sys_param_sidxdidx_configinfo_packing_t_dump("", (char *)sys_param_jsonbuff, param);
    sys_param_jsonbuff[len]=0;
    krs_debugcheck(len > 0, "sys_param_save_to_factory: json dump fail");

    //ret = sys_param_factoryinit();
    //ret = retOK;
    //krs_debugcheck(ret == retOK, "factory section init fail");

    //ret = mtd_write_section(mtd_dev_spiflash, mtd_sections_factory, 0, sys_param_jsonbuff, len+1);
    ret = WriteFile(SYS_PARAM_FILE_PATH_FACTORY, sys_param_jsonbuff, len);
    krs_debugcheck(ret == retOK, "writing mtd_sections_factory section is fail");

    return ret;
}


/******************************************************************************
 * function name : sys_param_load_from_factory
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * \param0 *param description
 * \return0 int32_t description
 * modification date : 2020.09.08
 *****************************************************************************/
int32_t sys_param_load_from_factory(void *param)
{
    int32_t len;
    int32_t ret;
    uint32_t read_size;
    char* fp;

    //ret = mtd_read_section(mtd_dev_spiflash, mtd_sections_factory, 0, sys_param_jsonbuff,
    //                       sizeof(sys_param_jsonbuff));
    fp = ReadFile(SYS_PARAM_FILE_PATH_FACTORY, &read_size);
    if(fp == NULL)
    {
        return retFail;
    }
    
    memcpy(sys_param_jsonbuff, fp, read_size);
    ret = retOK;
    krs_debugcheck(ret == retOK, "reading mtd_sections_factory section is fail");
    krs_debugcheck(sys_param_jsonbuff[0] != 0xFF, "mtd_sections_factory section is blank or none");

    len = strlen((const char *)sys_param_jsonbuff);
    len = sys_param_sidxdidx_configinfo_packing_t_loads((char *)sys_param_jsonbuff, len, param);
    krs_debugcheck(len > 0, "json load from factory is fail");
    
    return retOK;
}


void sys_param_wdg_clear(void)
{
	//wdg_drv_clear();
}

/* end of file */
