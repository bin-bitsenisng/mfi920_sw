/******************************************************************/
/* SID:0x00, DID:0x04 , systeminfo setup                          */
/******************************************************************/
{
    /*.sid =*/0,
    /*.did =*/4,
    /*.setup =*/
    {
        /*.sys=*/{
            /*.ver =*/SYS_SENSOR_TYPE,
            /*.date =*/SYS_BUILD_DATE SYS_BUILD_TIME,
            /*.spec =*/SYS_APP_NAME,
        },

        /*.sw=*/{
            /*.ver =*/SYS_SW_VERSION,
            /*.date =*/SYS_BUILD_DATE SYS_BUILD_TIME,
            /*.spec =*/SYS_APP_NAME,
        },
        /*.be=*/{
            /*.ver =*/SYS_HW_BE_VERSION,
            /*.date =*/SYS_HW_BE_DATE,
            /*.spec =*/"",
        },
        /*.fe=*/{
            /*.ver =*/SYS_HW_FE_VERSION,
            /*.date =*/SYS_HW_FE_DATE,
            /*.spec =*/"1G1tx4rx",
        },
        /*.housing=*/{
            /*.ver =*/SYS_HW_FE_VERSION,
            /*.date =*/SYS_HW_FE_DATE,
            /*.spec =*/"",
        },
        /*.cable=*/{
            /*.ver =*/SYS_HW_FE_VERSION,
            /*.date =*/SYS_HW_FE_DATE,
            /*.spec =*/"gth/rs485",
        },
        /*.protocol=*/{
            /*.ver =*/SYS_PROTOCOL_VERSION,
            /*.date =*/SYS_PROTOCOL_DATE,
            /*.spec =*/"daq_tcp/cmd_udp/cmd_tcp",
        },
        /*.customer=*/{
            /*.ver =*/SYS_CUSTOMER_VERSION,
            /*.date =*/SYS_CUSTOMER_DATE,
            /*.spec =*/SYS_CUSTOMER_SPEC,
        },
    },
},
