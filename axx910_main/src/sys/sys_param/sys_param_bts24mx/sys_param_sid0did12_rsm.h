/******************************************************************/
/* SID:0x00, DID: 12 , radar rf signal modulation(RSM) setup      */
/******************************************************************/
/*.sid0did11_certification_config =*/
{
    /*.sid =*/0,
    /*.did =*/12,
    /*.setup =*/
    {
        /*.mode =*/0, //0:normal, 1:flat_low, 2: flat_mid, 3: flat_high, 4: flat_userfreq,  5:radiation_off
        /*.userfreq = */ 24.15f,
        /*.scanrate = */ SYS_DEFAULT_SCANRATE,    // 10,15,20,25,30
        /*.daq_sampledelay=*/16 // sample
    },
},
