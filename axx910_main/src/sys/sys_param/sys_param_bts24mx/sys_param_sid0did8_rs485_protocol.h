/******************************************************************/
/* SID:0x00, DID: 8 , rs485 protocol setup */
/******************************************************************/
/*.sys_param_sid0did8_rs485_protocol_config_t =*/
{
    /*.sid =*/0,
    /*.did =*/8,
    /*.setup =*/
    {
        /*.commtype=*/0,  // 0: half duplex rs485, 1:full duplex rs485, 2: half duplex uart, full duplex uart
        /*.highspeed_en=*/0, // 0: baudrate_default, 1:baudrate_high
        /*.baudrate_default=*/115200, // 115200
        /*.baudrate_high=*/230400, // 921600
        /*.packettype=*/2, //bit[0]: 0:binary, 1:ascii,  bit[1]: 0:frame_encoding_disable, 1:frame_encoding_enable, bit[2]: 0:json disable, 1:json enable
        /*.tbd0=*/0,
        /*.tbd1=*/0,
        /*.tbd2=*/0,
        /*.tbd3=*/0,
    },
},
