/************************************************************************
| Project Name: sys_param_bts24mx_sid0did0
|    File Name: sys_param_bts24mx_sid0did0.h
|  Description: file detailed description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------
| SKJ          SONG KYEONG JIN           Bitsensing
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description
| ----------  ----  ------  --------------------------------------------
| 2019.05.26   0.0   SKJ   Creation;
|***********************************************************************/

    /******************************************************************/
    /* SID:0x00, DID:0x00 , system base setup */
    /******************************************************************/
    /*.sid0did0_system_config =*/
    {
        /*.sid =*/0,
        /*.did =*/0,
        /*.setup =*/
        {
                /*.swupdate=*/{
                    /*.swupdate_request=*/0, //::{0:"update_complete", 1:"swupdate_request"}
                    /*.swupdate_type=*/0,  //::{0:"tcp", 1:"udp",3:"can",4:"canfd",5:"uart",6:"rs485"}
                    /*.swupdate_count=*/0,
                    /*.swupdate_timestamp=*/0.0f, // unix timestamp in second
                },
            /*.consolelog = */ {
                /*.bts_log_level = */ 5, /* 0:disable, 1:error, 2:warning, 3:info, 4:debug*/
                /*.bts_log_opt_type_en = */ 0,
                /*.bts_log_opt_time_en = */ 1,
                /*.bts_log_opt_difftime_en = */ 1,
                /*.bts_log_opt_file_en = */ 1,
                /*.bts_log_opt_line_en = */ 1,
                /*.bts_log_opt_function_en = */ 0,
                /*.bts_log_module_comm_packet_en = */ 0,
                /*.bts_log_module_comm_appl_callback_en = */ 1,
                /*.bts_log_array_frontlen = */ 8,
                /*.bts_log_array_backlen = */ 8,
				/*.bts_log_cpu_usage=*/0,
			    /*.bts_log_opt_datetime_en=*/1,
			    /*.bts_log_opt_datetime_ms_en=*/1,
			    /*.bts_log_opt_datetime_us_en=*/1,
				/*.bts_log_opt_gps_en=*/0,
            },
			/*.consoleudp = */
			{
				/*.en = */ 1,
				/*.ip = */ "255.255.255.255",
				/*.port = */ 4543,
			},

            /*.sensortype = */
            {
				/*.type =*/SYS_SENSOR_TYPE,
				/*.serialnumber =*/"00000000",
				/*.opmode_its_en =*/SYS_APP_TYPE == SYS_APP_TYPE_ITS,
				/*.opmode_vf_en =*/SYS_APP_TYPE == SYS_APP_TYPE_VF,
				/*.opmode_fcw_en = */SYS_APP_TYPE == SYS_APP_TYPE_FCW,
				/*.opmode_lm_en =*/SYS_APP_TYPE == SYS_APP_TYPE_LEVELMETER,

				/* pid_status_en = */ SYS_PID_STATUS_EN,
				/* pid_object_en = */ SYS_PID_OBJECT_EN,
				/* pid_track_en = */ SYS_PID_TRACK_EN,
				/* pid_image_en = */ SYS_PID_IMAGE_EN,
				/* pid_imagsp_en = */ SYS_PID_IMAGSP_EN,
				/* pid_logger_en = */ SYS_PID_LOGGER_EN,
				/* pid_canlog_en = */ SYS_PID_CANLOG_EN,
				/* pid_sensor_en = */ SYS_PID_SENSOR_EN,

				/* pid_app_its_en = */ SYS_PID_APP_ITS_EN,
				/* pid_app_vf_en = */ SYS_PID_APP_VF_EN,
				/* pid_app_fcw_en = */ SYS_PID_APP_FCW_EN,
				/* pid_app_lm_en = */ SYS_PID_APP_LM_EN,

				/* raw_chirp_en = */ 1, //SYS_RAW_CHIRP_EN,
				/* raw_chirp0_en = */ 0, //SYS_RAW_CHIRP0_EN,
				/* raw_chirp1_en = */ 0, //SYS_RAW_CHIRP1_EN,
				/* raw_chirp2_en = */ 0, //SYS_RAW_CHIRP2_EN,
				/* raw_chirp3_en = */ 0, //SYS_RAW_CHIRP3_EN,


				/* raw_app_en = */ SYS_RAW_APP_EN,
				/* raw_app_its_en = */ SYS_RAW_APP_ITS_EN,
				/* raw_app_vf_en = */ SYS_RAW_APP_VF_EN,
				/* raw_app_fcw_en = */ SYS_RAW_APP_FCW_EN,
				/* raw_app_lm_en = */ SYS_RAW_APP_LM_EN,
				/* raw_app_install_en = */ SYS_RAW_APP_INSTALL_EN,
				/* raw_app_flog_en = */ SYS_RAW_APP_FLOG_EN,

				/* raw_mon_en = */ 0, //SYS_RAW_MON_EN,
				/* raw_mon_power_en = */ 0, //SYS_RAW_MON_POWER_EN,
				/* raw_mon_time_en = */ 0, //SYS_RAW_MON_TIME_EN,
				/* raw_mon_task_en = */ 0, //SYS_RAW_MON_TASK_EN,
            },
            /*.eth_default = */
            {
                /*.ip=*/SYS_IP_BASE, //"192.168.10.150",
                /*.nm=*/SYS_NM_BASE, //"255.255.255.0",
                /*.gw=*/SYS_GW_BASE, //"192.168.10.1",
                /*.mac=*/SYS_MACADDR_BASE,
                /*.dns=*/"208.67.222.222",
                /*.linkspeed=*/0, // 1000, 100, 10, 0(auto)
                /*.dhcp_en =  */ 0,
            },
            /*.syscontrol = */
            {
                /*.restart_en=*/1,
                /*.restart_timeout_s*/ 600,
            },
            /*.logiccontrol = */
            {
                /*.logic_start_scan_offset=*/10,
            },
        },
    },
