/******************************************************************/
/* SID:0x00, DID: 7 , junction box setup */
/******************************************************************/
/*.sid0did7_jctbox_config =*/
{
    /*.sid =*/0,
    /*.did =*/7,
    /*.setup =*/
    {
        /*.commtype=*/3,  // 0: none, 1: can, 2:ssr_uart, 3: rs485
        /*.highspeed_en=*/0, // 0: baudrate_default, 1:baudrate_high
        /*.baudrate_default=*/9600, // ssr_uart:600, rs485:9600, can:500000
        /*.baudrate_high=*/115200, // ssr_uart:600, rs485:115200, can:500000
        /*.packettype=*/0, // 0: shortbinary, 1:byte, 2:binary, 3:json
        /*.tbd0=*/0,
        /*.tbd1=*/0,
        /*.tbd2=*/0,
        /*.tbd3=*/0,
    },
},
