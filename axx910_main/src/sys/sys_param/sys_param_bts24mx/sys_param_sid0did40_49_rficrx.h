/******************************************************************/
/* SID:0x00, DID:40~49 rfic rx setup  */
/******************************************************************/
/******************************************************************/
/* SID:0x00, DID:40 rfic rx setup  */
/******************************************************************/
{
    /*.sid =*/0,
    /*.did =*/40,
    /*.setup*/ {
        /*.rficrx_sel=*/6, // 1:bgt24ar4, 1:bgt24ar4, 2:bgt24mtr11,3:bgt24atr11,4:bgt24ltr11,5:bgt24mtr12,6:ums24,7:adi24,8:bgt60t2r4,9:bgt60t1r3,10:awr1243
    },
},

/******************************************************************/
/* SID:0x00, DID:41 rfic bgt24ar4 rx setup  */
/******************************************************************/
{
    /*.sid =*/0,
    /*.did =*/41,
    /*.setup*/ {
        /*.EN_12=*/1,
        /*.LG1_12_6db=*/1,
        /*.HG1_12_12db=*/0,
        /*.LG2_12_6db=*/1,
        /*.MG2_12_12db=*/0,
        /*.HG2_12_18db=*/0,
        /*.EN_34=*/1,
        /*.LG1_34_6db=*/1,
        /*.HG1_34_12db=*/0,
        /*.LG2_34_6db=*/1,
        /*.MG2_34_12db=*/0,
        /*.HG2_34_18db=*/0,

        /*.IFTEST4=*/0, // Activates test signal for IF channel 4
        /*.IFTEST3=*/0, // Activates test signal for IF channel 3
        /*.IFTEST2=*/0, // Activates test signal for IF channel 2
        /*.IFTEST1=*/0, // Activates test signal for IF channel 1
        /*.PC1=*/1,     // Test bit
        /*.PC2=*/1,     // Test bit
        /*.EN_RF14=*/0, // Test bit
        /*.EN_RF23=*/0, // Test bit
        /*.DIS_DIV=*/1, // Test bit
        /*.DIS_LO=*/1,  // Test bit

        /*.AMUX_SEL0=*/0,    // Sets analog multiplexer
        /*.AMUX_SEL1=*/1,    // Sets analog multiplexer
        /*.AMUX_SEL2=*/0,    // Sets analog multiplexer
        /*.SAT_FLAG_HIZ=*/1, // Sets sat flag output into high impedance state and enables

        /*.SENSOR_SEL0=*/0, // Selects power sensor signal
        /*.SENSOR_SEL1=*/0, // Selects power sensor signal

        /*.DCO_0=*/0, // Test bit
        /*.DCO_1=*/0, // Test bit
        /*.DCO_2=*/0, // Test bit
        /*.DCO_3=*/0, // Test bit
    },
},
