    /******************************************************************/
    /* SID: 10, DID: 0 , FCW Forward Collision Warning application setup */
    /******************************************************************/
    /*.sid10did0_fcw_config =*/
    {
        /*.sid =*/10,
        /*.did =*/0,
        /*.setup =*/
        {
            /*.vehicle_type=*/1,    // 0:HKMC1G, 1:HKMC2G, 2:J1939bus, 3: Toyota pickup
            /*.startup_light_en=*/1,  // 1, check for junctionbox initial check
            /*.startup_light_ontime=*/3000, // 3000
            /*.alert_led_en=*/1,   //0:disable, 1:enable
            /*.alert_spk_en=*/1,    //0:disable, 1:enable
            /*.alert_ssr_en=*/1,    //0:disable, 1:enable
            /*.alert_ledcolor_caution=*/0xFFFFFF, // RGB
            /*.alert_ledcolor_warning=*/0xC8C8C8, // RGB
            /*.alert_ledcolor_normal=*/0x808080,  // RGB
            /*.alert_blink_period=*/2000,    // ms
            /*.alert_update_period=*/165,   // ms
			/*.alert_blocking_period=*/140, // ms
            /*.vehiclespeed_adj_ratio=*/1.0f ,
            /*.ttc_low_sec=*/1.7f,
            /*.ttc_high_sec=*/3.0f,
            /*.ttc_egospeed_low_kph=*/10.8f,
            /*.ttc_egospeed_high_kph=*/57.6f,
            /*.ttc_level1_ratio=*/1.0f,
            /*.ttc_level2_ratio=*/0.7f,
            /*.lane_left_m=*/ -1.25f,
            /*.lane_right_m=*/ 1.25f,
            /*.lane_range_m=*/ 30.0f ,
            /*.egospeed_min_kph=*/ 7.2f,
            /*.oncomming_th_kph=*/ -5.4f,
        },
    },
    /******************************************************************/
    /* SID: 10, DID: 1 , FCW Forward Collision Warning application test */
    /******************************************************************/
    /*.sid10did0_fcw_config =*/
    {
        /*.sid =*/10,
        /*.did =*/1,
        /*.setup =*/
        {
			/*.test_fcw_event_level1=*/0,
			/*.test_fcw_event_level2=*/0,
			/*.test_jctbox_led=*/0,
			/*.test_jctbox_spk=*/0,
			/*.test_jctbox_ssr=*/0,
			/*.test_tbd0=*/0,
			/*.test_tbd1=*/0,
			/*.test_tbd2=*/0,
			/*.test_tbd3=*/0,
			/*.test_tbd4=*/0,
        },
    },
