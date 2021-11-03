/******************************************************************/
/* SID:0x06, DID:0  CAN Communication Setup                      */
/******************************************************************/
{
    /*.sid =*/6,
    /*.did =*/0,
    /*.setup*/
    {
        /*.channel_count=*/1,
        /*.channel[]=*/
        {

            {
                /*cantype=*/0, // 0:ZYNQ_PSCAN, 1:ZYNQ_PLCAN, 2:ZYNQ_PLCANFD, 3:MCP2517FD_CAN, 4:MCP2517FD_CANFD
                /*baudrate=*/250000,
                /*baudratefd=*/2000000,
                /*samplepoint=*/75,
                /*listenonlymode_en=*/1, // 0:normal, 1:listen only
                /*acceptfilter_en*/ {1, 1, 1, 0},
                /*acceptfilter_id*/ {0x80FE6C00, 0x80FEBF00, 0x80F00900, 0x00000000},
                /*acceptfilter_mask*/ {0x80FFFF00, 0x80FFFF00, 0x80FFFF00, 0x00000000},
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
                {1, can_sig_id_vehicle_speed, 0x80FE6C00, "vehicle_speed_tco1", 'U', 'I', 48, 16, 0.00390625f, 0.0f, 0.0f, 250.996f, "kph"}, // J1939 TCO1
                //{1, can_sig_id_vehicle_speed, 0x80FE6C00, "vehicle_speed", 'U', 'I', 48, 16, 0.00390625f, 0.0f, 0.0f, 250.996f, "kph"},      // J1939 TCO1
                {1, can_sig_id_wheel_speed_fl, 0x80FEBF00, "wheel_speed_fl", 'U', 'I', 0, 16, 0.00390625f, 0.0f, 0.0f, 250.996f},       // J1939 EBC2
                {1, can_sig_id_wheel_speed_fr, 0x80FEBF00, "wheel_speed_fr", 'U', 'I', 0, 16, 0.00390625f, 0.0f, 0.0f, 250.996f},       // J1939 EBC2
                {1, can_sig_id_wheel_speed_rl, 0x80FEBF00, "wheel_speed_rl", 'U', 'I', 0, 16, 0.00390625f, 0.0f, 0.0f, 250.996f},       // J1939 EBC2
                {1, can_sig_id_wheel_speed_rr, 0x80FEBF00, "wheel_speed_rr", 'U', 'I', 0, 16, 0.00390625f, 0.0f, 0.0f, 250.996f},       // J1939 EBC2
                {1, can_sig_id_steerangle, 0x80F00900, "steerangle", 'U', 'I', 0, 16, 0.0009765625f, -31.374, -31.374f, 31.374, "rad"}, // J1939 VDC2
                {1, can_sig_id_yawrate, 0x80F00900, "yawrate", 'U', 'I', 24, 16, 0.0001220703125f, -3.92f, -3.92f, 3.926f, "rad/s"},    // J1939 VDC2
                {1, can_sig_id_longaccel, 0x80F00900, "longaccel", 'U', 'I', 56, 8, 0.1f, -12.25f, -12.25f, 12.25f, "m/s^2"},           // J1939 VDC2
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
