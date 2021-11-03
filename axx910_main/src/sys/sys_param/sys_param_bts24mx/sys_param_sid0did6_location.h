/******************************************************************/
/* SID:0x00, DID:0x06 , location setup */
/******************************************************************/
/*.sid0did2_location_config =*/
{
    /*.sid =*/0,
    /*.did =*/6,
    /*.setup =*/
    {
        /*location*/ {
            /*.type =*/"wgs84",
            /*.latitude =*/37.436786f,
            /*.longitude =*/127.169831f,
            /*.direction =*/0.0f, // 0.0 : north, 90:east, 180:south, 270:west
            /*.gps_update_en =*/0,
        },
        /*gps*/ {
            /*.en =*/SYS_GPS_ENABLE,
            /*.manufacture =*/"ublox",
            /*.default_baudrate =*/9600,
            /*.baudrate =*/115200,
            /*.rate =*/10,        // Hz
            /*.dgps_en =*/1,     //
            /*.swfilter_en =*/0, //
        },
    },
},
