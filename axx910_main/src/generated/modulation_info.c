//*****************************************************************  
//  Project Name:  IR24X 
//     File Name:  modulation_info.c
//   Description:  auto generated file. do not modify!
// ----------------------------------------------------------------
//           C O D E    G E N E R A T O R    I N F O R M A T I O N 
// ----------------------------------------------------------------
//     Generator: codegen.exe
//       Version: 0.0.1
//          Time: Mon Oct 12 15:37:38 2020
//    Datafile 0: ..\commondata\modulation_info.yaml
//    Datafile 1: ..\commondata\modulation_info_new.yaml
//    Datafile 2: ..\commondata\xcp_odt_info.yaml
//            ID: CAED29EA-8726-4383-8EA0-6E19855D34DB
// 
// ----------------------------------------------------------------
//           U S E R    I N F O R M A T I O N
// ----------------------------------------------------------------
// Computer Name: SSONGDESKTOP
//     User Name: user
//     Directory: D:\Workdir\BTS24MX_LWIP2\ir24x_sw\ir24x_main\prebuild\modulation_info
// 
// ----------------------------------------------------------------
//           P R O J E C T    S U M M A R Y
// ----------------------------------------------------------------               
//*****************************************************************
/* include system primitive types */
#include "bts.h"


/* include system driver header */


/* include system bsp header */


/* include system application header */


/* final include module header */
# include "modulation_info.h"



/* declare global variables */
modulation_chriptype_t modulation_info_default_chirptype = MODULATION_CHIRPTYPE_0_ITS_IR24X;

uint32_t modulation_info_table_count = MODULATION_CHIRPTYPE_MAX;
modulation_info_table_t modulation_info_table = {0};

modulation_info_table_t *pmodulation_info_table[MODULATION_CHIRPTYPE_MAX]=
{
     &modulation_info_table_modulation_chirptype_0_its_ir24x,
     &modulation_info_table_modulation_chirptype_1_its_ir24x_longfirst,
     &modulation_info_table_modulation_chirptype_2_its_kc,
     &modulation_info_table_modulation_chirptype_3_vf_16k,
     &modulation_info_table_modulation_chirptype_3_vf_1k,
     &modulation_info_table_modulation_chirptype_3_vf_2k,
     &modulation_info_table_modulation_chirptype_3_vf_4k,
     &modulation_info_table_modulation_chirptype_3_vf_8k,
     &modulation_info_table_modulation_chirptype_4_vf_1kx16,
     &modulation_info_table_modulation_chirptype_4_vf_2kx8,
     &modulation_info_table_modulation_chirptype_5_marine,
     &modulation_info_table_modulation_chirptype_6_marine_longfirst,
     &modulation_info_table_modulation_chirptype_7_slow24ghz,
     &modulation_info_table_modulation_chirptype_8_freqmoving,
     &modulation_info_table_modulation_chirptype_9_79daq,
     &modulation_info_table
};


modulation_info_table_t modulation_info_table_modulation_chirptype_0_its_ir24x=
{
    "ITS modulation",
    1,  // group repeat
    2,  // active group count
    0.0, // frequency moving step GHz
    {
        {
            1, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     10.24,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_TRIANGULAR
            },
            {   // sample count, buffer offset, sample frequency
                4096, 8192, 400.64104
            }
        },
        {
            1, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     20.48,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_TRIANGULAR
            },
            {   // sample count, buffer offset, sample frequency
                8192, 16384, 400.64104
            }
        }
    }
};



modulation_info_table_t modulation_info_table_modulation_chirptype_1_its_ir24x_longfirst=
{
    "ITS modulation",
    1,  // group repeat
    2,  // active group count
    0.0, // frequency moving step GHz
    {
        {
            1, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     20.48,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_TRIANGULAR
            },
            {   // sample count, buffer offset, sample frequency
                8192, 16384, 400.64104
            }
        },
        {
            1, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     10.24,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_TRIANGULAR
            },
            {   // sample count, buffer offset, sample frequency
                4096, 8192, 400.64104
            }
        }
    }
};



modulation_info_table_t modulation_info_table_modulation_chirptype_2_its_kc=
{
    "ITS modulation",
    1,  // group repeat
    3,  // active group count
    0.0, // frequency moving step GHz
    {
        {
            1, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     5.12,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_TRIANGULAR
            },
            {   // sample count, buffer offset, sample frequency
                2048, 4096, 400.64104
            }
        },
        {
            1, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     10.24,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_TRIANGULAR
            },
            {   // sample count, buffer offset, sample frequency
                4096, 8192, 400.64104
            }
        },
        {
            1, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     20.48,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_TRIANGULAR
            },
            {   // sample count, buffer offset, sample frequency
                8192, 16384, 400.64104
            }
        }
    }
};



modulation_info_table_t modulation_info_table_modulation_chirptype_3_vf_16k=
{
    "VF modulation 16K sample",
    1,  // group repeat
    1,  // active group count
    0.0, // frequency moving step GHz
    {
        {
            1, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     40.96,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_SAWTOOTH
            },
            {   // sample count, buffer offset, sample frequency
                16384, 32768, 400.64104
            }
        }
    }
};



modulation_info_table_t modulation_info_table_modulation_chirptype_3_vf_1k=
{
    "VF modulation 1K sample",
    1,  // group repeat
    1,  // active group count
    0.0, // frequency moving step GHz
    {
        {
            1, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     2.56,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_SAWTOOTH
            },
            {   // sample count, buffer offset, sample frequency
                1024, 2048, 400.64104
            }
        }
    }
};



modulation_info_table_t modulation_info_table_modulation_chirptype_3_vf_2k=
{
    "VF modulation 2K sample",
    1,  // group repeat
    1,  // active group count
    0.0, // frequency moving step GHz
    {
        {
            1, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     5.12,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_SAWTOOTH
            },
            {   // sample count, buffer offset, sample frequency
                2048, 4096, 400.64104
            }
        }
    }
};



modulation_info_table_t modulation_info_table_modulation_chirptype_3_vf_4k=
{
    "VF modulation 4K sample",
    1,  // group repeat
    1,  // active group count
    0.0, // frequency moving step GHz
    {
        {
            1, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     10.24,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_SAWTOOTH
            },
            {   // sample count, buffer offset, sample frequency
                4096, 8192, 400.64104
            }
        }
    }
};



modulation_info_table_t modulation_info_table_modulation_chirptype_3_vf_8k=
{
    "VF modulation 8K sample",
    1,  // group repeat
    1,  // active group count
    0.0, // frequency moving step GHz
    {
        {
            1, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     20.48,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_SAWTOOTH
            },
            {   // sample count, buffer offset, sample frequency
                8192, 16384, 400.64104
            }
        }
    }
};



modulation_info_table_t modulation_info_table_modulation_chirptype_4_vf_1kx16=
{
    "VF modulation 1k sample x 16",
    1,  // group repeat
    1,  // active group count
    0.0, // frequency moving step GHz
    {
        {
            16, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     2.56,    0.0,    0.0,      32.0,      10.0,      PLL_DRV_MODULATION_TYPE_SAWTOOTH
            },
            {   // sample count, buffer offset, sample frequency
                1024, 2048, 400.64104
            }
        }
    }
};



modulation_info_table_t modulation_info_table_modulation_chirptype_4_vf_2kx8=
{
    "VF modulation 2k sample x 8",
    1,  // group repeat
    1,  // active group count
    0.0, // frequency moving step GHz
    {
        {
            8, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     5.12,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_SAWTOOTH
            },
            {   // sample count, buffer offset, sample frequency
                2048, 4096, 400.64104
            }
        }
    }
};



modulation_info_table_t modulation_info_table_modulation_chirptype_5_marine=
{
    "Marine Radar modulation",
    1,  // group repeat
    2,  // active group count
    0.0, // frequency moving step GHz
    {
        {
            1, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     20.48,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_TRIANGULAR
            },
            {   // sample count, buffer offset, sample frequency
                8192, 16384, 400.64104
            }
        },
        {
            1, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     40.96,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_TRIANGULAR
            },
            {   // sample count, buffer offset, sample frequency
                16384, 32768, 400.64104
            }
        }
    }
};



modulation_info_table_t modulation_info_table_modulation_chirptype_6_marine_longfirst=
{
    "Marine Radar modulation",
    1,  // group repeat
    2,  // active group count
    0.0, // frequency moving step GHz
    {
        {
            1, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     40.96,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_TRIANGULAR
            },
            {   // sample count, buffer offset, sample frequency
                16384, 32768, 400.64104
            }
        },
        {
            1, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          187.5,     20.48,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_TRIANGULAR
            },
            {   // sample count, buffer offset, sample frequency
                8192, 16384, 400.64104
            }
        }
    }
};



modulation_info_table_t modulation_info_table_modulation_chirptype_7_slow24ghz=
{
    "slow chirp mode 1",
    32,  // group repeat
    1,  // active group count
    0.0, // frequency moving step GHz
    {
        {
            8, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                24.15,          200.0,     5.12,    0.0,    0.0,      32.0,      0.0,      PLL_DRV_MODULATION_TYPE_SAWTOOTH
            },
            {   // sample count, buffer offset, sample frequency
                2048, 4096, 400.64104
            }
        }
    }
};



modulation_info_table_t modulation_info_table_modulation_chirptype_8_freqmoving=
{
    "center freq moving chirp",
    4,  // group repeat
    1,  // active group count
    0.025, // frequency moving step GHz
    {
        {
            8, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                23.6,          200.0,     5.12,    0.0,    0.0,      32.0,      10.0,      PLL_DRV_MODULATION_TYPE_TRIANGULAR
            },
            {   // sample count, buffer offset, sample frequency
                2048, 4096, 400.64104
            }
        }
    }
};



modulation_info_table_t modulation_info_table_modulation_chirptype_9_79daq=
{
    "fast chirp mode for 79ghz radar",
    1,  // group repeat
    1,  // active group count
    0.0, // frequency moving step GHz
    {
        {
            1024, // chirp repeat
            {   // centerfreq,  bandwith,   time,   offset, interval,   refclk,  vco_drive_strength   type
                79.0,          2000.0,     0.018,    0.0,    0.002,      40.0,      50.0,      PLL_DRV_MODULATION_TYPE_SAWTOOTH
            },
            {   // sample count, buffer offset, sample frequency
                2048, 4194304, 111000.0
            }
        }
    }
};




/* declare static variables */


/* static function prototypes */

/* functions */

/* end of file */

