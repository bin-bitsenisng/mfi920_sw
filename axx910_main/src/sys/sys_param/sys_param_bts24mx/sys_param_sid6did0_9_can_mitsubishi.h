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
                /*baudrate=*/500000,
                /*baudratefd=*/2000000,
                /*samplepoint=*/75,
                /*listenonlymode_en=*/1, // 0:normal, 1:listen only
                /*acceptfilter_en*/ {1, 1, 0, 0},
                /*acceptfilter_id*/ {0x00000214, 0x00000215, 0x00000000, 0x00000000},
                /*acceptfilter_mask*/ {0x000007FF, 0x000007FF, 0x00000000, 0x00000000},
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
                {1, can_sig_id_vehicle_speed, 0x214, "vehicle_speed",'U', 'M', 0, 16, 0.00768f, 0.0f, 0.0f, 255.0f, "kph"},   // MITSUBISH Triton L200
                {1, can_sig_id_wheel_speed_fl, 0x214, "wheel_speed_fl",'U', 'M', 0, 16, 0.00768f, 0.0f, 0.0f, 255.0f, "kph"}, // MITSUBISH Triton L200
                {1, can_sig_id_wheel_speed_fr, 0x214, "wheel_speed_fr",'U', 'M', 0, 16, 0.00768f, 0.0f, 0.0f, 255.0f, "kph"}, // MITSUBISH Triton L200
                {1, can_sig_id_wheel_speed_rl, 0x215, "wheel_speed_rl",'U', 'M', 0, 16, 0.00768f, 0.0f, 0.0f, 255.0f, "kph"}, // MITSUBISH Triton L200
                {1, can_sig_id_wheel_speed_rr, 0x215, "wheel_speed_rr",'U', 'M', 0, 16, 0.00768f, 0.0f, 0.0f, 255.0f, "kph"}, // MITSUBISH Triton L200
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
