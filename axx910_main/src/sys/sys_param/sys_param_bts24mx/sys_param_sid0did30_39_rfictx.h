/******************************************************************/
/* SID:0x00, DID:30~39 rfic tx setup  */
/******************************************************************/
/******************************************************************/
/* SID:0x00, DID:30 rfic tx setup  */
/******************************************************************/
{
    /*.sid =*/0,
    /*.did =*/30,
    /*.setup*/ {
        /*.rfictx_sel=*/6, // 0:bgt24at2, 1:bgt24ar4, 2:bgt24mtr11, 3:bgt24atr11, 4:bgt24ltr11, 5:bgt24mtr12, 6:ums24, 7:adi24, 8:bgt60t2r4, 9:bgt60t1r3, 10:awr1243
    },
},

/******************************************************************/
/* SID:0x00, DID:31 rfic bgt24at2 tx setup  */
/******************************************************************/
{
    /*.sid =*/0,
    /*.did =*/31,
    /*.setup*/ {
        // TX1 setting
        /*.TX1_A=*/63,     // 0~63
        /*.TX1_SPI_ON=*/1, // 0:dis, 1:en
        /*.TX1_EN_DAC=*/1, // 0:dis, 1:en
        /*.TX1_SEL1=*/1,   // 0: via ext pin, 1: via spi
        /*.PH1_SPI_ON=*/0, // 0: 0, 1:180
                           // TX2 setting
        /*.TX2_A=*/0,      // 0~63
        /*.TX2_SPI_ON=*/0, // 0:dis, 1:en
        /*.TX2_EN_DAC=*/0, // 0:dis, 1:en
        /*.TX2_SEL1=*/1,   // 0: via ext pin, 1: via spi
        /*.PH2_SPI_ON=*/0, // 0: 0, 1:180
                           // LO setting
        /*.LO_A=*/63,
        /*.LO_SPI_ON=*/1,
        /*.LO_EN_DAC=*/1,
        /*.LO_SEL1=*/0, // LO_SEL[1:0]: "00": via ext pin, "01": spi, "1X": auto with TX1_ON or TX2_ON
        /*.LO_SEL0=*/1,
        /*.PHLO_SPI_ON=*/0,
        // VCO setting
        /*.VCO_A=*/0,
        /*.EN_DAC_VCO=*/0,
        /*.EN_VCO=*/1,
        /*.EN_BUF2=*/0,
        /*.EN_BUF1=*/1,
        // Phase control select setting
        /*.PH_SEL1=*/0, // 0: ext pin, 1: spi
        // AMUX setting
        /*.AMUX1_SEL1=*/0,
        /*.AMUX1_SEL0=*/0,
        /*.AMUX2_SEL2=*/0,
        /*.AMUX2_SEL1=*/0,
        /*.AMUX2_SEL0=*/0,
        /*.AMUX3_SEL1=*/0,
        /*.AMUX3_SEL0=*/0,
        // divider setting
        /*.EN_DIV=*/1,
        /*.SEL_DIVBUF=*/1,
        /*.SEL_DIV=*/0,
        /*.DIS_DIVOUT=*/0,
    },
},
