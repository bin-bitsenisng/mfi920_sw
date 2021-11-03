    /******************************************************************/
    /* SID: 9, DID: 0 , Virtual Fence reflector setup */
    /******************************************************************/
    /*.sid9did0_vf_reflector_config =*/
    {
        /*.sid =*/9,
        /*.did =*/0,
        /*.setup =*/
        {
            /*.reflector_type =*/"corner",
            /*.reflector_distance =*/3.0f, // meter
            /*.reflectorradius =*/0.5f,    // // meter
        },
    },
    /******************************************************************/
    /* SID: 9, DID: 1 , Virtual Fence destination server setup */
    /******************************************************************/
    /*.sid9did1_vf_server_config =*/
    {
        /*.sid =*/9,
        /*.did =*/1,
        /*.setup =*/
        {
            /*.server_ip =*/"192.168.10.11",
            /*.server_port =*/4549,            //:4564,
            /*.server_access_timeout =*/10000, //: 10000, // milisecond
            /*.server_access_retry_cnt =*/3,   //: 3,
			/*.server_sendstack_size =*/0,     //: 0
            /*.rs485_access_timeout =*/1000,   //: 1000, // milisecond
            /*.rs485_access_retry_cnt =*/3,    //: 0
        },
    },
    /******************************************************************/
    /* SID: 9, DID: 2 , Virtual Fence relay setup */
    /******************************************************************/
    /*.sid9did2_vf_relay_config =*/
    {
        /*.sid =*/9,
        /*.did =*/2,
        /*.setup =*/
        {
            /*.relay_cnt =*/4,                               //;                              //:4,
            /*.relay_enable =*/{1, 1, 0, 0},                 //[SYS_PARAM_VF_RELAYCNT_MAX]; //:[0,0,0,0],
            /*.relay_type =*/{"NO", "NO", "NO", "NO"},       //["NO","NO","NO","NO"], // "NO" or "NC"
            /*.relay_on_time_ms =*/{1000, 2000, 1000, 1000}, //[SYS_PARAM_VF_RELAYCNT_MAX];    //:
                                                             //[0,0,0,0], // 0~60000ms
            /*.relay_on_event_type =*/{1, 2, 2, 2},          //[SYS_PARAM_VF_RELAYCNT_MAX]; //:[0,0,0,0], //
                                                             //0:normal, 1:caution, 2:warning, 3:error
        },
    },
    /******************************************************************/
    /* SID: 9, DID: 3 , UI setup */
    /******************************************************************/
    /*.sid9did3_vf_ui_config =*/
    {
        /*.sid =*/9,
        /*.did =*/3,
        /*.setup =*/
        {
            /*.th_normal=*/60.0f,  //:100,
            /*.th_caution=*/50.0f, //:80,
            /*.th_warning=*/40.0f, //:68,
            /*.marker=*/65.0f,     //:130
        },
    },
