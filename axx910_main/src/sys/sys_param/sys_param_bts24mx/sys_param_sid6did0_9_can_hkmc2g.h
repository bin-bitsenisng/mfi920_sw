/******************************************************************/
/* SID:0x06, DID:0  CAN Communication Setup                      */
/******************************************************************/
{
    /*.sid =*/6,
    /*.did =*/0,
    /*.setup*/
    {
        /*.channel_count=*/1,
        /*.channel[]=*/{
            {
                /*cantype=*/0, // 0:ZYNQ_PSCAN, 1:ZYNQ_PLCAN, 2:ZYNQ_PLCANFD, 3:MCP2517FD_CAN, 4:MCP2517FD_CANFD
                /*baudrate=*/500000,
                /*baudratefd=*/2000000,
                /*samplepoint=*/75,
                /*listenonlymode_en=*/1, // 0:normal, 1:listen only
                /*acceptfilter_en*/ {1, 1, 1, 1},
                /*acceptfilter_id*/ {0x000004F1, 0x00000386, 0x000002B0, 0x00000220},
                /*acceptfilter_mask*/ {0x000007FF, 0x000007FF, 0x000007FF, 0x000007FF},
            },
        },
    },
},
    /******************************************************************/
    /* SID:0x06, DID:1  CAN Signal Setup                              */
    /******************************************************************/
    {
        /*.sid =*/6,
        /*.did =*/1,
        /*.setup*/
        {

            /*signal*/
            {
                //en, sigid,    msgid,            name, type, byteorder, bitpos, length,     factor,   offset,     min,    max,  unit
                {0, can_sig_id_vehicle_speed, 0x4F1, "vehicle_speed", 'U', 'I', 48, 8, 1.0f, 0.0f, 0.0f, 255.0f, "kph"},          // HKMC 2G CLU11
                {1, can_sig_id_wheel_speed_fl, 0x386, "wheel_speed_fl", 'U', 'I', 0, 14, 0.03125f, 0.0f, 0.0f, 511.969f, "kph"},  // HKMC 2G WHL_SPD11
                {1, can_sig_id_wheel_speed_fr, 0x386, "wheel_speed_fr", 'U', 'I', 16, 14, 0.03125f, 0.0f, 0.0f, 511.969f, "kph"}, // HKMC 2G WHL_SPD11
                {1, can_sig_id_wheel_speed_rl, 0x386, "wheel_speed_rl", 'U', 'I', 32, 14, 0.03125f, 0.0f, 0.0f, 511.969f, "kph"}, // HKMC 2G WHL_SPD11
                {1, can_sig_id_wheel_speed_rr, 0x386, "wheel_speed_rr", 'U', 'I', 48, 14, 0.03125f, 0.0f, 0.0f, 511.969f, "kph"}, // HKMC 2G WHL_SPD11
                {1, can_sig_id_steerangle, 0x2B0, "steerangle", 'S', 'I', 0, 16, 0.1f, 0.0f, -3276.8f, 3276.7f, "deg"},           // HKMC 2G SAS11
                {1, can_sig_id_steeranglespeed, 0x2B0, "steeranglespeed", 'U', 'I', 16, 8, 4.0f, 0.0f, 0.0f, 1016.0f, "deg"},     // HKMC 2G SAS11
                {1, can_sig_id_yawrate, 0x220, "yawrate", 'U', 'I', 40, 13, 0.01f, -40.96f, -40.95f, 40.96f, "deg/s"},            // HKMC 2G ESP12
                {1, can_sig_id_longaccel, 0x220, "longaccel", 'U', 'I', 13, 11, 0.01f, -10.24f, -10.23f, 10.24f, "m/s^2"},        // HKMC 2G ESP12
                {1, can_sig_id_lataccel, 0x220, "lataccel", 'U', 'I', 0, 11, 0.01f, 10.23f, -10.23f, 10.24f, "m/s^2"},          // HKMC 2G ESP12
            },

        },
    },
    /******************************************************************/
    /* SID:0x06, DID:2  CAN TX Message Setup                          */
    /******************************************************************/
    {
        /*.sid =*/6,
        /*.did =*/2,
        /*.setup*/
        {
            // en, start_id, count
            /*status=*/{0, 0x101, 1},
            /*object=*/{0, 0x600, 128},
            /*track=*/{0, 0x500, 64},
            /*extioctrl=*/{0, 0x100, 1},
        },
    },
