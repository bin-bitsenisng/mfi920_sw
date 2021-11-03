/* ================================================================================

     Project      :   ADAR690x
     File         :   ADAR690x.h
     Description  :   Register Definitions

     Date         :   Jan 20, 2020

     Copyright (c) 2020 Analog Devices, Inc.  All Rights Reserved.
     This software is proprietary and confidential to Analog Devices, Inc. and
     its licensors.

     This file was auto-generated. Do not make local changes to this file.

   ================================================================================ */

#ifndef _DEF_ADAR690X_H
#define _DEF_ADAR690X_H

#if defined(_LANGUAGE_C) || (defined(__GNUC__) && !defined(__ASSEMBLER__))
#include <stdint.h>
#endif /* _LANGUAGE_C */

#ifndef __ADI_GENERATED_DEF_HEADERS__
#define __ADI_GENERATED_DEF_HEADERS__    1
#endif

#define __ADI_HAS_ADC_ADPLL__      1
#define __ADI_HAS_AFE__            1
#define __ADI_HAS_ARC__            1
#define __ADI_HAS_DATA_PORT__      1
#define __ADI_HAS_DDS__            1
#define __ADI_HAS_MIPICSI2__       1
#define __ADI_HAS_FFT__            1
#define __ADI_HAS_FabricCRC__      1
#define __ADI_HAS_FaultCtl__       1
#define __ADI_HAS_PORTA0__         1
#define __ADI_HAS_PORTA__          1
#define __ADI_HAS_PORTB1__         1
#define __ADI_HAS_PORTB__          1
#define __ADI_HAS_Goertzel__       1
#define __ADI_HAS_AuxADC__         1
#define __ADI_HAS_RF_HISTOGRAM__   1
#define __ADI_HAS_LOGEN__          1
#define __ADI_HAS_LVDS__           1
#define __ADI_HAS_MIPI__           1
#define __ADI_HAS_OTPC__           1
#define __ADI_HAS_PINT__           1
#define __ADI_HAS_ADC_PLLRAM__     1
#define __ADI_HAS_RAMPGEN__        1
#define __ADI_HAS_RF_ADPLL__       1
#define __ADI_HAS_RF_RTWO__        1
#define __ADI_HAS_ADC_RTWO__       1
#define __ADI_HAS_RX__             1
#define __ADI_HAS_SPI__            1
#define __ADI_HAS_TESTTONEGEN__    1
#define __ADI_HAS_TX__             1
#define __ADI_HAS_TX_PHASE_LUT__   1
#define __ADI_HAS_TX_PHASE_MOD_MEM__ 1
#define __ADI_HAS_WDT_10__         1
#define __ADI_HAS_WDT_1__          1
#define __ADI_HAS_WDT1__           1
#define __ADI_HAS_WDT__            1
#define __ADI_HAS_misc__           1
#define __ADI_HAS_uDMA__           1

/* ============================================================================================================================
        digiMMIC SPI Register Map
   ============================================================================================================================ */

/* ============================================================================================================================
        SPI
   ============================================================================================================================ */
#define REG_SPI_SPI_INTERFACECONFIGA_RESET   0x00000000            /*      Reset Value for SPI_InterfaceConfigA  */
#define REG_SPI_SPI_INTERFACECONFIGA         0x00000000            /*  SPI Interface config register A */
#define REG_SPI_SPI_INTERFACECONFIGB_RESET   0x00000000            /*      Reset Value for SPI_InterfaceConfigB  */
#define REG_SPI_SPI_INTERFACECONFIGB         0x00000001            /*  SPI Interface config register B */
#define REG_SPI_SPI_DEVICECONFG_RESET        0x00000000            /*      Reset Value for SPI_DeviceConfg  */
#define REG_SPI_SPI_DEVICECONFG              0x00000002            /*  SPI Device config register */
#define REG_SPI_SPI_SCRATCHPADAUX_RESET      0x00000000            /*      Reset Value for SPI_ScratchPadAux  */
#define REG_SPI_SPI_SCRATCHPADAUX            0x00000003            /*  SPI Scratch Pad register */
#define REG_SPI_SPI_PRODUCTIDL_RESET         0x0000001A            /*      Reset Value for SPI_ProductIdL  */
#define REG_SPI_SPI_PRODUCTIDL               0x00000004            /*  SPI Product ID lower byte register */
#define REG_SPI_SPI_PRODUCTIDU_RESET         0x00000000            /*      Reset Value for SPI_ProductIdU  */
#define REG_SPI_SPI_PRODUCTIDU               0x00000005            /*  SPI Product ID upper byte register */
#define REG_SPI_SPI_CHIPGRADE_RESET          0x00000002            /*      Reset Value for SPI_ChipGrade  */
#define REG_SPI_SPI_CHIPGRADE                0x00000006            /*  SPI Product grade and chip grade */
#define REG_SPI_SPI_CHIPTYPE_RESET           0x00000001            /*      Reset Value for SPI_ChipType  */
#define REG_SPI_SPI_CHIPTYPE                 0x00000007            /*  SPI Chip Type register */
#define REG_SPI_SPI_DEVICEINDEXA_RESET       0x00000000            /*      Reset Value for SPI_DeviceIndexA  */
#define REG_SPI_SPI_DEVICEINDEXA             0x00000008            /*  SPI Device Index A register */
#define REG_SPI_SPI_DEVICEINDEXB_RESET       0x00000000            /*      Reset Value for SPI_DeviceIndexB  */
#define REG_SPI_SPI_DEVICEINDEXB             0x00000009            /*  SPI Device Index B register */
#define REG_SPI_SPI_SCRATCHPAD_RESET         0x00000000            /*      Reset Value for SPI_ScratchPad  */
#define REG_SPI_SPI_SCRATCHPAD               0x0000000A            /*  SPI Scratch Pad register */
#define REG_SPI_SPI_REV_RESET                0x00000001            /*      Reset Value for SPI_Rev  */
#define REG_SPI_SPI_REV                      0x0000000B            /*  SPI SPI Revision register */
#define REG_SPI_SPI_VENDORIDL_RESET          0x00000056            /*      Reset Value for SPI_VendorIDL  */
#define REG_SPI_SPI_VENDORIDL                0x0000000C            /*  SPI Vendor ID Lower byte register */
#define REG_SPI_SPI_VENDORIDU_RESET          0x00000004            /*      Reset Value for SPI_VendorIDU  */
#define REG_SPI_SPI_VENDORIDU                0x0000000D            /*  SPI Vendor ID upper byte register */
#define REG_SPI_SPI_DEVICECONFGAUX_RESET     0x00000000            /*      Reset Value for SPI_DeviceConfgAux  */
#define REG_SPI_SPI_DEVICECONFGAUX           0x0000000E            /*  SPI Auxiliary device config register */
#define REG_SPI_SPI_RDFRAMECNT_LSB_RESET     0x00000000            /*      Reset Value for SPI_RdFrameCnt_LSB  */
#define REG_SPI_SPI_RDFRAMECNT_LSB           0x00000010            /*  SPI SPI read frame count register LSB */
#define REG_SPI_SPI_RDFRAMECNT_MSB_RESET     0x00000000            /*      Reset Value for SPI_RdFrameCnt_MSB  */
#define REG_SPI_SPI_RDFRAMECNT_MSB           0x00000011            /*  SPI SPI read frame count register MSB */
#define REG_SPI_SPI_WRFRAMECNT_LSB_RESET     0x00000000            /*      Reset Value for SPI_WrFrameCnt_LSB  */
#define REG_SPI_SPI_WRFRAMECNT_LSB           0x00000014            /*  SPI SPI write frame count register LSB */
#define REG_SPI_SPI_WRFRAMECNT_MSB_RESET     0x00000000            /*      Reset Value for SPI_WrFrameCnt_MSB  */
#define REG_SPI_SPI_WRFRAMECNT_MSB           0x00000015            /*  SPI SPI write frame count register MSB */
#define REG_SPI_SPI_STATUS_RESET             0x00000000            /*      Reset Value for SPI_Status  */
#define REG_SPI_SPI_STATUS                   0x00000018            /*  SPI SPI write frame count register LSB */
#define REG_SPI_SPI_DEVICEENUMID_RESET       0x00000000            /*      Reset Value for SPI_DeviceEnumID  */
#define REG_SPI_SPI_DEVICEENUMID             0x00000019            /*  SPI Indicates digiMMIC enumeration ID */
#define REG_SPI_SPI_DEVICECONFIGAUX_S_RESET  0x00000000            /*      Reset Value for SPI_DeviceConfigAux_S  */
#define REG_SPI_SPI_DEVICECONFIGAUX_S        0x0000001A            /*  SPI Secondary Auxiliary device config register */
#define REG_SPI_SPI_POWERDOWN_RESET          0x00000000            /*      Reset Value for SPI_Powerdown  */
#define REG_SPI_SPI_POWERDOWN                0x0000001B            /*  SPI Implements power down funtionality of digiMMIC. */
#define REG_SPI_SPI_AUX_SYSRST_0_RESET       0x00000000            /*      Reset Value for SPI_Aux_Sysrst_0  */
#define REG_SPI_SPI_AUX_SYSRST_0             0x0000001C            /*  SPI Auxiliary R/W register for PTE */
#define REG_SPI_SPI_AUX_SYSRST_1_RESET       0x00000000            /*      Reset Value for SPI_Aux_Sysrst_1  */
#define REG_SPI_SPI_AUX_SYSRST_1             0x0000001D            /*  SPI Auxiliary R/W register for PTE */
#define REG_SPI_SPI_AUX_SYSRST_2_RESET       0x00000000            /*      Reset Value for SPI_Aux_Sysrst_2  */
#define REG_SPI_SPI_AUX_SYSRST_2             0x0000001E            /*  SPI Auxiliary R/W register for PTE */
#define REG_SPI_SPI_AUX_SYSRST_3_RESET       0x00000000            /*      Reset Value for SPI_Aux_Sysrst_3  */
#define REG_SPI_SPI_AUX_SYSRST_3             0x0000001F            /*  SPI Auxiliary R/W register for PTE */
#define REG_SPI_SPI_AUX_HWRST_0_RESET        0x00000000            /*      Reset Value for SPI_Aux_Hwrst_0  */
#define REG_SPI_SPI_AUX_HWRST_0              0x00000020            /*  SPI Auxiliary R/W register for PTE */
#define REG_SPI_SPI_AUX_HWRST_1_RESET        0x00000000            /*      Reset Value for SPI_Aux_Hwrst_1  */
#define REG_SPI_SPI_AUX_HWRST_1              0x00000021            /*  SPI Auxiliary R/W register for PTE */
#define REG_SPI_SPI_AUX_HWRST_2_RESET        0x00000000            /*      Reset Value for SPI_Aux_Hwrst_2  */
#define REG_SPI_SPI_AUX_HWRST_2              0x00000022            /*  SPI Auxiliary R/W register for PTE */
#define REG_SPI_SPI_AUX_HWRST_3_RESET        0x00000000            /*      Reset Value for SPI_Aux_Hwrst_3  */
#define REG_SPI_SPI_AUX_HWRST_3              0x00000023            /*  SPI Auxiliary R/W register for PTE */
#define REG_SPI_SPI_STATUS_AUX_0_RESET       0x00000000            /*      Reset Value for SPI_Status_Aux_0  */
#define REG_SPI_SPI_STATUS_AUX_0             0x00000024            /*  SPI Auxiliary Status register from MISC */
#define REG_SPI_SPI_STATUS_AUX_1_RESET       0x00000000            /*      Reset Value for SPI_Status_Aux_1  */
#define REG_SPI_SPI_STATUS_AUX_1             0x00000025            /*  SPI Auxiliary Status register from MISC */
#define REG_SPI_SPI_STATUS_AUX_2_RESET       0x00000000            /*      Reset Value for SPI_Status_Aux_2  */
#define REG_SPI_SPI_STATUS_AUX_2             0x00000026            /*  SPI Auxiliary Status register from MISC */
#define REG_SPI_SPI_STATUS_AUX_3_RESET       0x00000000            /*      Reset Value for SPI_Status_Aux_3  */
#define REG_SPI_SPI_STATUS_AUX_3             0x00000027            /*  SPI Auxiliary Status register from MISC */

/* ============================================================================================================================
        SPI Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_INTERFACECONFIGA             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_INTERFACECONFIGA_SRSTLEFT  7            /*  1: Resets entire chip excluding SPI */
#define BITP_SPI_SPI_INTERFACECONFIGA_LSBFIRSTLEFT  6            /*  Bit order select */
#define BITP_SPI_SPI_INTERFACECONFIGA_ADDRASCLEFT  5            /*  Enables address ascension */
#define BITP_SPI_SPI_INTERFACECONFIGA_BIGENDLEFT  4            /*  Endianess select */
#define BITP_SPI_SPI_INTERFACECONFIGA_BIGENDRIGHT  3            /*  Endianess select */
#define BITP_SPI_SPI_INTERFACECONFIGA_ADDRASCRIGHT  2            /*  Enables address ascension */
#define BITP_SPI_SPI_INTERFACECONFIGA_LSBFIRSTRIGHT  1            /*  Bit order select */
#define BITP_SPI_SPI_INTERFACECONFIGA_SRSTRIGHT  0            /*  1: Resets entire chip excluding SPI */
#define BITM_SPI_SPI_INTERFACECONFIGA_SRSTLEFT 0x00000080    /*  1: Resets entire chip excluding SPI */
#define BITM_SPI_SPI_INTERFACECONFIGA_LSBFIRSTLEFT 0x00000040    /*  Bit order select */
#define BITM_SPI_SPI_INTERFACECONFIGA_ADDRASCLEFT 0x00000020    /*  Enables address ascension */
#define BITM_SPI_SPI_INTERFACECONFIGA_BIGENDLEFT 0x00000010    /*  Endianess select */
#define BITM_SPI_SPI_INTERFACECONFIGA_BIGENDRIGHT 0x00000008    /*  Endianess select */
#define BITM_SPI_SPI_INTERFACECONFIGA_ADDRASCRIGHT 0x00000004    /*  Enables address ascension */
#define BITM_SPI_SPI_INTERFACECONFIGA_LSBFIRSTRIGHT 0x00000002    /*  Bit order select */
#define BITM_SPI_SPI_INTERFACECONFIGA_SRSTRIGHT 0x00000001    /*  1: Resets entire chip excluding SPI */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_INTERFACECONFIGB             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_INTERFACECONFIGB_SOSI    7            /*  0: Start first bit on MOSI. 1: Start first bit on MISO */
#define BITP_SPI_SPI_INTERFACECONFIGB_CRCDIS  4            /*  Write 101 to disable */
#define BITP_SPI_SPI_INTERFACECONFIGB_SRST2   3            /*  1:Resets entire chip including SPI */
#define BITP_SPI_SPI_INTERFACECONFIGB_SRST1   2            /*  1:Resets entire chip including SPI */
#define BITP_SPI_SPI_INTERFACECONFIGB_DIOM    0            /*  Indicates if SPI is in DIOM or SIOM */
#define BITM_SPI_SPI_INTERFACECONFIGB_SOSI   0x00000080    /*  0: Start first bit on MOSI. 1: Start first bit on MISO */
#define BITM_SPI_SPI_INTERFACECONFIGB_CRCDIS 0x00000070    /*  Write 101 to disable */
#define BITM_SPI_SPI_INTERFACECONFIGB_SRST2  0x00000008    /*  1:Resets entire chip including SPI */
#define BITM_SPI_SPI_INTERFACECONFIGB_SRST1  0x00000004    /*  1:Resets entire chip including SPI */
#define BITM_SPI_SPI_INTERFACECONFIGB_DIOM   0x00000001    /*  Indicates if SPI is in DIOM or SIOM */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_DEVICECONFG                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_DEVICECONFG_PRTCLCOMPLERR  7            /*  Indicates one of the protocol errors */
#define BITP_SPI_SPI_DEVICECONFG_BUSERR       6            /*  Indicates Bus Error */
#define BITP_SPI_SPI_DEVICECONFG_WRERR        5            /*  1: Indicates AHB write operation failure */
#define BITP_SPI_SPI_DEVICECONFG_RDERR        4            /*  1: Indicates AHB read operation failure */
#define BITP_SPI_SPI_DEVICECONFG_INDEXDISABLE  2            /*  Disables device index and restricts host access within SPI configuration address space */
#define BITP_SPI_SPI_DEVICECONFG_OPERATINGMODE  1            /*  Indicates Operating Mode */
#define BITP_SPI_SPI_DEVICECONFG_RTWO_PUP     0            /*  Indicates RTWO PUP done */
#define BITM_SPI_SPI_DEVICECONFG_PRTCLCOMPLERR 0x00000080    /*  Indicates one of the protocol errors */
#define BITM_SPI_SPI_DEVICECONFG_BUSERR      0x00000040    /*  Indicates Bus Error */
#define BITM_SPI_SPI_DEVICECONFG_WRERR       0x00000020    /*  1: Indicates AHB write operation failure */
#define BITM_SPI_SPI_DEVICECONFG_RDERR       0x00000010    /*  1: Indicates AHB read operation failure */
#define BITM_SPI_SPI_DEVICECONFG_INDEXDISABLE 0x0000000C    /*  Disables device index and restricts host access within SPI configuration address space */
#define BITM_SPI_SPI_DEVICECONFG_OPERATINGMODE 0x00000002    /*  Indicates Operating Mode */
#define BITM_SPI_SPI_DEVICECONFG_RTWO_PUP    0x00000001    /*  Indicates RTWO PUP done */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_SCRATCHPADAUX                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_SCRATCHPADAUX_SCRATCHPADAUX  0            /*  Used to test reads/writes by software */
#define BITM_SPI_SPI_SCRATCHPADAUX_SCRATCHPADAUX 0x000000FF    /*  Used to test reads/writes by software */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_PRODUCTIDL                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_PRODUCTIDL_PRODUCTIDL    0            /*  Indicates Product ID lower byte */
#define BITM_SPI_SPI_PRODUCTIDL_PRODUCTIDL   0x000000FF    /*  Indicates Product ID lower byte */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_PRODUCTIDU                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_PRODUCTIDU_PRODUCTIDU    0            /*  Indicates Product ID upper byte */
#define BITM_SPI_SPI_PRODUCTIDU_PRODUCTIDU   0x000000FF    /*  Indicates Product ID upper byte */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_CHIPGRADE                    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_CHIPGRADE_PRODUCTGRADE   4            /*  Indicates Product Grade */
#define BITP_SPI_SPI_CHIPGRADE_DEVICEREVISION  0            /*  Indicates Device Revision */
#define BITM_SPI_SPI_CHIPGRADE_PRODUCTGRADE  0x000000F0    /*  Indicates Product Grade */
#define BITM_SPI_SPI_CHIPGRADE_DEVICEREVISION 0x0000000F    /*  Indicates Device Revision */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_CHIPTYPE                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_CHIPTYPE_CHIPTYPE        0            /*  Indicates chip type. */
#define BITM_SPI_SPI_CHIPTYPE_CHIPTYPE       0x000000FF    /*  Indicates chip type. */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_DEVICEINDEXA                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_DEVICEINDEXA_SECONDMSBYTEADDR  0            /*  Contains second most significant address byte */
#define BITM_SPI_SPI_DEVICEINDEXA_SECONDMSBYTEADDR 0x000000FF    /*  Contains second most significant address byte */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_DEVICEINDEXB                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_DEVICEINDEXB_MSBYTEADDR  0            /*  Contains most significant address byte */
#define BITM_SPI_SPI_DEVICEINDEXB_MSBYTEADDR 0x000000FF    /*  Contains most significant address byte */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_SCRATCHPAD                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_SCRATCHPAD_SCRATCHPAD    0            /*  Used to test reads/writes by software */
#define BITM_SPI_SPI_SCRATCHPAD_SCRATCHPAD   0x000000FF    /*  Used to test reads/writes by software */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_REV                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_REV_SPIREVISION          0            /*  SPI revision */
#define BITM_SPI_SPI_REV_SPIREVISION         0x000000FF    /*  SPI revision */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_VENDORIDL                    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_VENDORIDL_VENDORIDL      0            /*  Indicates Vendor ID lower byte (0x56) */
#define BITM_SPI_SPI_VENDORIDL_VENDORIDL     0x000000FF    /*  Indicates Vendor ID lower byte (0x56) */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_VENDORIDU                    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_VENDORIDU_VENDORIDH      0            /*  Indicates Vendor ID high byte (0x04) */
#define BITM_SPI_SPI_VENDORIDU_VENDORIDH     0x000000FF    /*  Indicates Vendor ID high byte (0x04) */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_DEVICECONFGAUX               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_DEVICECONFGAUX_CLRRDFRAMECTR  5            /*  Resets contents of read frame counter to 0 */
#define BITP_SPI_SPI_DEVICECONFGAUX_CLRWRFRAMECTR  2            /*  Resets contents of write frame counter to 0 */
#define BITP_SPI_SPI_DEVICECONFGAUX_MSTR_SLAVE  0            /*  Indicates whether digimmic is master or slave */
#define BITM_SPI_SPI_DEVICECONFGAUX_CLRRDFRAMECTR 0x000000E0    /*  Resets contents of read frame counter to 0 */
#define BITM_SPI_SPI_DEVICECONFGAUX_CLRWRFRAMECTR 0x0000001C    /*  Resets contents of write frame counter to 0 */
#define BITM_SPI_SPI_DEVICECONFGAUX_MSTR_SLAVE 0x00000003    /*  Indicates whether digimmic is master or slave */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_RDFRAMECNT_LSB               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_RDFRAMECNT_LSB_SPI_RDFRAMECNT_LSB  0            /*  Indicates LS byte of SPI read frame counter */
#define BITM_SPI_SPI_RDFRAMECNT_LSB_SPI_RDFRAMECNT_LSB 0x000000FF    /*  Indicates LS byte of SPI read frame counter */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_RDFRAMECNT_MSB               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_RDFRAMECNT_MSB_SPI_RDFRAMECNT_MSB  0            /*  Indicates MS byte of SPI read frame counter */
#define BITM_SPI_SPI_RDFRAMECNT_MSB_SPI_RDFRAMECNT_MSB 0x000000FF    /*  Indicates MS byte of SPI read frame counter */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_WRFRAMECNT_LSB               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_WRFRAMECNT_LSB_SPI_WRFRAMECNT_LSB  0            /*  Indicates LS byte of SPI write frame counter */
#define BITM_SPI_SPI_WRFRAMECNT_LSB_SPI_WRFRAMECNT_LSB 0x000000FF    /*  Indicates LS byte of SPI write frame counter */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_WRFRAMECNT_MSB               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_WRFRAMECNT_MSB_SPI_WRFRAMECNT_MSB  0            /*  Indicates MS byte of SPI write frame counter */
#define BITM_SPI_SPI_WRFRAMECNT_MSB_SPI_WRFRAMECNT_MSB 0x000000FF    /*  Indicates MS byte of SPI write frame counter */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_STATUS                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_STATUS_RDCNTOVF          1            /*  Indicates read counter overflow */
#define BITP_SPI_SPI_STATUS_WRCNTOVF          0            /*  Indicates write counter overflow */
#define BITM_SPI_SPI_STATUS_RDCNTOVF         0x00000002    /*  Indicates read counter overflow */
#define BITM_SPI_SPI_STATUS_WRCNTOVF         0x00000001    /*  Indicates write counter overflow */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_DEVICEENUMID                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_DEVICEENUMID_DEVICEENUMID  0            /*  Indicates digiMMIC enumeration ID */
#define BITM_SPI_SPI_DEVICEENUMID_DEVICEENUMID 0x0000003F    /*  Indicates digiMMIC enumeration ID */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_DEVICECONFIGAUX_S            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_DEVICECONFIGAUX_S_EN_SPI_RDCNTR  6            /*  Enables SPI read counter to increment */
#define BITP_SPI_SPI_DEVICECONFIGAUX_S_EN_SPI_WRCNTR  4            /*  Enables SPI write counter to increment */
#define BITP_SPI_SPI_DEVICECONFIGAUX_S_CLKOUTCTRL  0            /*  Select for CLOCKHOST control */
#define BITM_SPI_SPI_DEVICECONFIGAUX_S_EN_SPI_RDCNTR 0x000000C0    /*  Enables SPI read counter to increment */
#define BITM_SPI_SPI_DEVICECONFIGAUX_S_EN_SPI_WRCNTR 0x00000030    /*  Enables SPI write counter to increment */
#define BITM_SPI_SPI_DEVICECONFIGAUX_S_CLKOUTCTRL 0x0000000F    /*  Select for CLOCKHOST control */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_POWERDOWN                    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_POWERDOWN_SPI_GP_POWERDOWN  3            /*  Provides additional powerdown modes */
#define BITP_SPI_SPI_POWERDOWN_SPI_PWDNB      0            /*  Implements power down functionality of digiMMIC. */
#define BITM_SPI_SPI_POWERDOWN_SPI_GP_POWERDOWN 0x00000078    /*  Provides additional powerdown modes */
#define BITM_SPI_SPI_POWERDOWN_SPI_PWDNB     0x00000007    /*  Implements power down functionality of digiMMIC. */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_AUX_SYSRST_0                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_AUX_SYSRST_0_AUX_SYSRST_0  0            /*  Used to test reads/writes by PTE. Resets to 0 on system reset */
#define BITM_SPI_SPI_AUX_SYSRST_0_AUX_SYSRST_0 0x000000FF    /*  Used to test reads/writes by PTE. Resets to 0 on system reset */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_AUX_SYSRST_1                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_AUX_SYSRST_1_AUX_SYSRST_1  0            /*  Used to test reads/writes by PTE. Resets to 0 on system reset */
#define BITM_SPI_SPI_AUX_SYSRST_1_AUX_SYSRST_1 0x000000FF    /*  Used to test reads/writes by PTE. Resets to 0 on system reset */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_AUX_SYSRST_2                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_AUX_SYSRST_2_AUX_SYSRST_2  0            /*  Used to test reads/writes by PTE. Resets to 0 on system reset */
#define BITM_SPI_SPI_AUX_SYSRST_2_AUX_SYSRST_2 0x000000FF    /*  Used to test reads/writes by PTE. Resets to 0 on system reset */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_AUX_SYSRST_3                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_AUX_SYSRST_3_AUX_SYSRST_3  0            /*  Used to test reads/writes by PTE. Resets to 0 on system reset */
#define BITM_SPI_SPI_AUX_SYSRST_3_AUX_SYSRST_3 0x000000FF    /*  Used to test reads/writes by PTE. Resets to 0 on system reset */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_AUX_HWRST_0                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_AUX_HWRST_0_AUX_HWRST_0  3            /*  Used to test reads/writes by PTE. Resets to 0 on hardware reset (system reset has no effect) */
#define BITP_SPI_SPI_AUX_HWRST_0_PTE_TESTMODE  0            /*  101 : Indicates PTE test mode */
#define BITM_SPI_SPI_AUX_HWRST_0_AUX_HWRST_0 0x000000F8    /*  Used to test reads/writes by PTE. Resets to 0 on hardware reset (system reset has no effect) */
#define BITM_SPI_SPI_AUX_HWRST_0_PTE_TESTMODE 0x00000007    /*  101 : Indicates PTE test mode */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_AUX_HWRST_1                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_AUX_HWRST_1_AUX_HWRST_1  0            /*  Used to test reads/writes by PTE. Resets to 0 on hardware reset (system reset has no effect) */
#define BITM_SPI_SPI_AUX_HWRST_1_AUX_HWRST_1 0x000000FF    /*  Used to test reads/writes by PTE. Resets to 0 on hardware reset (system reset has no effect) */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_AUX_HWRST_2                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_AUX_HWRST_2_AUX_HWRST_2  0            /*  Used to test reads/writes by PTE. Resets to 0 on hardware reset (system reset has no effect) */
#define BITM_SPI_SPI_AUX_HWRST_2_AUX_HWRST_2 0x000000FF    /*  Used to test reads/writes by PTE. Resets to 0 on hardware reset (system reset has no effect) */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_AUX_HWRST_3                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_AUX_HWRST_3_AUX_HWRST_3  0            /*  Used to test reads/writes by PTE. Resets to 0 on hardware reset (system reset has no effect) */
#define BITM_SPI_SPI_AUX_HWRST_3_AUX_HWRST_3 0x000000FF    /*  Used to test reads/writes by PTE. Resets to 0 on hardware reset (system reset has no effect) */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_STATUS_AUX_0                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_STATUS_AUX_0_STATUS_AUX0  0            /*  Captures auxiliary status from system controller */
#define BITM_SPI_SPI_STATUS_AUX_0_STATUS_AUX0 0x000000FF    /*  Captures auxiliary status from system controller */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_STATUS_AUX_1                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_STATUS_AUX_1_STATUS_AUX1  0            /*  Captures auxiliary status from system controller */
#define BITM_SPI_SPI_STATUS_AUX_1_STATUS_AUX1 0x000000FF    /*  Captures auxiliary status from system controller */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_STATUS_AUX_2                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_STATUS_AUX_2_STATUS_AUX2  0            /*  Captures auxiliary status from system controller */
#define BITM_SPI_SPI_STATUS_AUX_2_STATUS_AUX2 0x000000FF    /*  Captures auxiliary status from system controller */

/* -------------------------------------------------------------------------------------------------------------------------
          SPI_SPI_STATUS_AUX_3                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_SPI_SPI_STATUS_AUX_3_STATUS_AUX3  0            /*  Captures auxiliary status from system controller */
#define BITM_SPI_SPI_STATUS_AUX_3_STATUS_AUX3 0x000000FF    /*  Captures auxiliary status from system controller */


/* ============================================================================================================================
        Digimmic Udma Register Map
   ============================================================================================================================ */

/* ============================================================================================================================
        uDMA
   ============================================================================================================================ */
#define REG_UDMA_STAT_RESET                  0x000F0000            /*      Reset Value for STAT  */
#define REG_UDMA_STAT                        0xF0001000            /*  uDMA Dma Status */
#define REG_UDMA_CFG_RESET                   0x00000000            /*      Reset Value for CFG  */
#define REG_UDMA_CFG                         0xF0001004            /*  uDMA Dma Configuration */
#define REG_UDMA_PDBPTR_RESET                0x00000000            /*      Reset Value for PDBPTR  */
#define REG_UDMA_PDBPTR                      0xF0001008            /*  uDMA Dma Channel Primary Control Data Base Pointer */
#define REG_UDMA_ADBPTR_RESET                0x00000100            /*      Reset Value for ADBPTR  */
#define REG_UDMA_ADBPTR                      0xF000100C            /*  uDMA Dma Channel Alternate Control Data Base Pointer */
#define REG_UDMA_SWREQ_RESET                 0x00000000            /*      Reset Value for SWREQ  */
#define REG_UDMA_SWREQ                       0xF0001014            /*  uDMA Dma Channel Software Request */
#define REG_UDMA_RMSK_SET_RESET              0x00000000            /*      Reset Value for RMSK_SET  */
#define REG_UDMA_RMSK_SET                    0xF0001020            /*  uDMA Dma Channel Request Mask Set */
#define REG_UDMA_RMSK_CLR_RESET              0x00000000            /*      Reset Value for RMSK_CLR  */
#define REG_UDMA_RMSK_CLR                    0xF0001024            /*  uDMA Dma Channel Request Mask Clear */
#define REG_UDMA_EN_SET_RESET                0x00000000            /*      Reset Value for EN_SET  */
#define REG_UDMA_EN_SET                      0xF0001028            /*  uDMA Dma Channel Enable Set */
#define REG_UDMA_EN_CLR_RESET                0x00000000            /*      Reset Value for EN_CLR  */
#define REG_UDMA_EN_CLR                      0xF000102C            /*  uDMA Dma Channel Enable Clear */
#define REG_UDMA_ALT_SET_RESET               0x00000000            /*      Reset Value for ALT_SET  */
#define REG_UDMA_ALT_SET                     0xF0001030            /*  uDMA Dma Channel Primary-Alternate Set */
#define REG_UDMA_ALT_CLR_RESET               0x00000000            /*      Reset Value for ALT_CLR  */
#define REG_UDMA_ALT_CLR                     0xF0001034            /*  uDMA Dma Channel Primary-Alternate Clear */
#define REG_UDMA_PRI_SET_RESET               0x00000000            /*      Reset Value for PRI_SET  */
#define REG_UDMA_PRI_SET                     0xF0001038            /*  uDMA Dma Channel Priority Set */
#define REG_UDMA_PRI_CLR_RESET               0x00000000            /*      Reset Value for PRI_CLR  */
#define REG_UDMA_PRI_CLR                     0xF000103C            /*  uDMA Dma Channel Priority Clear */
#define REG_UDMA_ERRCHNL_CLR_RESET           0x00000000            /*      Reset Value for ERRCHNL_CLR  */
#define REG_UDMA_ERRCHNL_CLR                 0xF0001048            /*  uDMA Dma per Channel Error Clear */
#define REG_UDMA_ERR_CLR_RESET               0x00000000            /*      Reset Value for ERR_CLR  */
#define REG_UDMA_ERR_CLR                     0xF000104C            /*  uDMA Dma Bus Error Clear */
#define REG_UDMA_INVALIDDESC_CLR_RESET       0x00000000            /*      Reset Value for INVALIDDESC_CLR  */
#define REG_UDMA_INVALIDDESC_CLR             0xF0001050            /*  uDMA Dma per Channel Invalid Descriptor Clear */
#define REG_UDMA_BS_SET_RESET                0x00000000            /*      Reset Value for BS_SET  */
#define REG_UDMA_BS_SET                      0xF0001800            /*  uDMA Dma Channel Bytes Swap Enable Set */
#define REG_UDMA_BS_CLR_RESET                0x00000000            /*      Reset Value for BS_CLR  */
#define REG_UDMA_BS_CLR                      0xF0001804            /*  uDMA Dma Channel Bytes Swap Enable Clear */
#define REG_UDMA_SRCADDR_SET_RESET           0x00000000            /*      Reset Value for SRCADDR_SET  */
#define REG_UDMA_SRCADDR_SET                 0xF0001810            /*  uDMA Dma Channel Source Address Decrement Enable Set */
#define REG_UDMA_SRCADDR_CLR_RESET           0x00000000            /*      Reset Value for SRCADDR_CLR  */
#define REG_UDMA_SRCADDR_CLR                 0xF0001814            /*  uDMA Dma Channel Source Address Decrement Enable Clear */
#define REG_UDMA_DSTADDR_SET_RESET           0x00000000            /*      Reset Value for DSTADDR_SET  */
#define REG_UDMA_DSTADDR_SET                 0xF0001818            /*  uDMA Dma Channel Destination Address Decrement Enable Set */
#define REG_UDMA_DSTADDR_CLR_RESET           0x00000000            /*      Reset Value for DSTADDR_CLR  */
#define REG_UDMA_DSTADDR_CLR                 0xF000181C            /*  uDMA Dma Channel Destination Address Decrement Enable Clear */
#define REG_UDMA_CHNL_CLEAR_ALT_AT_DONE_SET_RESET 0x00000000            /*      Reset Value for CHNL_CLEAR_ALT_AT_DONE_SET  */
#define REG_UDMA_CHNL_CLEAR_ALT_AT_DONE_SET  0xF0001820            /*  uDMA Dma Channel Alternate Status Clear at Done SetRegister */
#define REG_UDMA_CHNL_CLEAR_ALT_AT_DONE_CLR_RESET 0x00000000            /*      Reset Value for CHNL_CLEAR_ALT_AT_DONE_CLR  */
#define REG_UDMA_CHNL_CLEAR_ALT_AT_DONE_CLR  0xF0001824            /*  uDMA Dma Channel Alternate Status Clear at Done ClrRegister */
#define REG_UDMA_CHNL_DONT_CLEAR_EN_AT_DONE_SET_RESET 0x00000000            /*      Reset Value for CHNL_DONT_CLEAR_EN_AT_DONE_SET  */
#define REG_UDMA_CHNL_DONT_CLEAR_EN_AT_DONE_SET 0xF0001828            /*  uDMA Dma Channel Dont Clear Enable at Done SetRegister */
#define REG_UDMA_CHNL_DONT_CLEAR_EN_AT_DONE_CLR_RESET 0x00000000            /*      Reset Value for CHNL_DONT_CLEAR_EN_AT_DONE_CLR  */
#define REG_UDMA_CHNL_DONT_CLEAR_EN_AT_DONE_CLR 0xF000182C            /*  uDMA Dma Channel Dont Clear Enable at Done ClearRegister */
#define REG_UDMA_REVID_RESET                 0x00000003            /*      Reset Value for REVID  */
#define REG_UDMA_REVID                       0xF0001FE0            /*  uDMA Dma Controller Revision Id */

/* ============================================================================================================================
        uDMA Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_STAT                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_STAT_CHANM1                16            /*  Number of Available Dma Channels Minus 1 */
#define BITP_UDMA_STAT_MEN                    0            /*  Enable Status of the Controller */
#define BITM_UDMA_STAT_CHANM1                0x001F0000    /*  Number of Available Dma Channels Minus 1 */
#define BITM_UDMA_STAT_MEN                   0x00000001    /*  Enable Status of the Controller */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_CFG                             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_CFG_MEN                     0            /*  Controller Enable */
#define BITM_UDMA_CFG_MEN                    0x00000001    /*  Controller Enable */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_PDBPTR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_PDBPTR_ADDR                 9            /*  Pointer to the Base Address of the Primary Data Structure */
#define BITM_UDMA_PDBPTR_ADDR                0xFFFFFE00    /*  Pointer to the Base Address of the Primary Data Structure */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_ADBPTR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_ADBPTR_ADDR                 0            /*  Base Address of the Alternate Data Structure */
#define BITM_UDMA_ADBPTR_ADDR                0xFFFFFFFF    /*  Base Address of the Alternate Data Structure */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_SWREQ                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_SWREQ_CHAN                  0            /*  Generate Software Request */
#define BITM_UDMA_SWREQ_CHAN                 0x0000FFFF    /*  Generate Software Request */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_RMSK_SET                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_RMSK_SET_CHAN               0            /*  Mask Requests from Dma Channels */
#define BITM_UDMA_RMSK_SET_CHAN              0x0000FFFF    /*  Mask Requests from Dma Channels */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_RMSK_CLR                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_RMSK_CLR_CHAN               0            /*  Clear Request Mask Set Bits */
#define BITM_UDMA_RMSK_CLR_CHAN              0x0000FFFF    /*  Clear Request Mask Set Bits */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_EN_SET                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_EN_SET_CHAN                 0            /*  Enable Dma Channels */
#define BITM_UDMA_EN_SET_CHAN                0x0000FFFF    /*  Enable Dma Channels */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_EN_CLR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_EN_CLR_CHAN                 0            /*  Disable Dma Channels */
#define BITM_UDMA_EN_CLR_CHAN                0x0000FFFF    /*  Disable Dma Channels */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_ALT_SET                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_ALT_SET_CHAN                0            /*  Control Struct Status / Select Alt Struct */
#define BITM_UDMA_ALT_SET_CHAN               0x0000FFFF    /*  Control Struct Status / Select Alt Struct */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_ALT_CLR                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_ALT_CLR_CHAN                0            /*  Select Primary Data Struct */
#define BITM_UDMA_ALT_CLR_CHAN               0x0000FFFF    /*  Select Primary Data Struct */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_PRI_SET                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_PRI_SET_CHAN                0            /*  Configure Channel for High Priority */
#define BITM_UDMA_PRI_SET_CHAN               0x0000FFFF    /*  Configure Channel for High Priority */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_PRI_CLR                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_PRI_CLR_CHPRICLR            0            /*  Configure Channel for Default Priority Level */
#define BITM_UDMA_PRI_CLR_CHPRICLR           0x0000FFFF    /*  Configure Channel for Default Priority Level */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_ERRCHNL_CLR                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_ERRCHNL_CLR_CHAN            0            /*  Per Channel Bus Error Status/ per Channel Bus Error Clear */
#define BITM_UDMA_ERRCHNL_CLR_CHAN           0x0000FFFF    /*  Per Channel Bus Error Status/ per Channel Bus Error Clear */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_ERR_CLR                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_ERR_CLR_CHAN                0            /*  Bus Error Status */
#define BITM_UDMA_ERR_CLR_CHAN               0x00000001    /*  Bus Error Status */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_INVALIDDESC_CLR                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_INVALIDDESC_CLR_CHAN        0            /*  Per Channel Invalid Descriptor Status/ Clear */
#define BITM_UDMA_INVALIDDESC_CLR_CHAN       0x0000FFFF    /*  Per Channel Invalid Descriptor Status/ Clear */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_BS_SET                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_BS_SET_CHAN                 0            /*  Byte Swap Status */
#define BITM_UDMA_BS_SET_CHAN                0x0000FFFF    /*  Byte Swap Status */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_BS_CLR                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_BS_CLR_CHAN                 0            /*  Disable Byte Swap */
#define BITM_UDMA_BS_CLR_CHAN                0x0000FFFF    /*  Disable Byte Swap */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_SRCADDR_SET                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_SRCADDR_SET_CHAN            0            /*  Source Address Decrement Status / Configure */
#define BITM_UDMA_SRCADDR_SET_CHAN           0x0000FFFF    /*  Source Address Decrement Status / Configure */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_SRCADDR_CLR                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_SRCADDR_CLR_CHAN            0            /*  Disable Source Address Decrement */
#define BITM_UDMA_SRCADDR_CLR_CHAN           0x0000FFFF    /*  Disable Source Address Decrement */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_DSTADDR_SET                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_DSTADDR_SET_CHAN            0            /*  Destination Address Decrement */
#define BITM_UDMA_DSTADDR_SET_CHAN           0x0000FFFF    /*  Destination Address Decrement */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_DSTADDR_CLR                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_DSTADDR_CLR_CHAN            0            /*  Disable Destination Address Decrement */
#define BITM_UDMA_DSTADDR_CLR_CHAN           0x0000FFFF    /*  Disable Destination Address Decrement */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_CHNL_CLEAR_ALT_AT_DONE_SET      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_CHNL_CLEAR_ALT_AT_DONE_SET_CHNL_CLEAR_ALT_AT_DONE_SET  0            /*  Channel Alternate Status Cleared at Done */
#define BITM_UDMA_CHNL_CLEAR_ALT_AT_DONE_SET_CHNL_CLEAR_ALT_AT_DONE_SET 0x0000FFFF    /*  Channel Alternate Status Cleared at Done */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_CHNL_CLEAR_ALT_AT_DONE_CLR      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_CHNL_CLEAR_ALT_AT_DONE_CLR_CHNL_CLEAR_ALT_AT_DONE_CLR  0            /*  Channel Alternate Status Not Cleared at Done */
#define BITM_UDMA_CHNL_CLEAR_ALT_AT_DONE_CLR_CHNL_CLEAR_ALT_AT_DONE_CLR 0x0000FFFF    /*  Channel Alternate Status Not Cleared at Done */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_CHNL_DONT_CLEAR_EN_AT_DONE_SET  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_CHNL_DONT_CLEAR_EN_AT_DONE_SET_CHNL_DONT_CLEAR_EN_AT_DONE_SET  0            /*  Channel Enable Not Cleared at Done */
#define BITM_UDMA_CHNL_DONT_CLEAR_EN_AT_DONE_SET_CHNL_DONT_CLEAR_EN_AT_DONE_SET 0x0000FFFF    /*  Channel Enable Not Cleared at Done */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_CHNL_DONT_CLEAR_EN_AT_DONE_CLR  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_CHNL_DONT_CLEAR_EN_AT_DONE_CLR_CHNL_DONT_CLEAR_EN_AT_DONE_CLR  0            /*  Channel Enable  Cleared at Done */
#define BITM_UDMA_CHNL_DONT_CLEAR_EN_AT_DONE_CLR_CHNL_DONT_CLEAR_EN_AT_DONE_CLR 0x0000FFFF    /*  Channel Enable  Cleared at Done */

/* -------------------------------------------------------------------------------------------------------------------------
          uDMA_REVID                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_UDMA_REVID_VALUE                 0            /*  Dma Controller Revision Id */
#define BITM_UDMA_REVID_VALUE                0x000000FF    /*  Dma Controller Revision Id */


/* ============================================================================================================================
        The General-Purpose Input/Output Port
   ============================================================================================================================ */

/* ============================================================================================================================
        PORTA
   ============================================================================================================================ */
#define REG_PORTA_ST_EN_RESET                0x00000000            /*      Reset Value for ST_EN  */
#define REG_PORTA_ST_EN                      0xF0002000            /*  PORTA GPIO Schmitt Trigger Enable */
#define REG_PORTA_SLRATE_SEL_RESET           0x00000000            /*      Reset Value for SLRATE_SEL  */
#define REG_PORTA_SLRATE_SEL                 0xF0002004            /*  PORTA GPIO Slew rate control enable */
#define REG_PORTA_DS_SEL_L_RESET             0x00924924            /*      Reset Value for DS_SEL_L  */
#define REG_PORTA_DS_SEL_L                   0xF0002008            /*  PORTA GPIO Drive strength - pads 7:0 */
#define REG_PORTA_DS_SEL_H_RESET             0x00924924            /*      Reset Value for DS_SEL_H  */
#define REG_PORTA_DS_SEL_H                   0xF000200C            /*  PORTA GPIO Drive strength - pads 15:8 */
#define REG_PORTA_PU_SEL_RESET               0x00000080            /*      Reset Value for PU_SEL  */
#define REG_PORTA_PU_SEL                     0xF0002010            /*  PORTA GPIO Pull up select */
#define REG_PORTA_PD_SEL_RESET               0x00000000            /*      Reset Value for PD_SEL  */
#define REG_PORTA_PD_SEL                     0xF0002014            /*  PORTA GPIO Pull down select */
#define REG_PORTA_FER_RESET                  0x0000FFFF            /*      Reset Value for FER  */
#define REG_PORTA_FER                        0xF0002040            /*  PORTA GPIO Function Enable Register (FER) */
#define REG_PORTA_DATA                       0xF0002044            /*  PORTA GPIO Data Register */
#define REG_PORTA_DIR_RESET                  0x00000000            /*      Reset Value for DIR  */
#define REG_PORTA_DIR                        0xF0002048            /*  PORTA GPIO Direction Register */
#define REG_PORTA_INEN_RESET                 0x0000FFFF            /*      Reset Value for INEN  */
#define REG_PORTA_INEN                       0xF000204C            /*  PORTA GPIO Input Enable Register */
#define REG_PORTA_MUX_RESET                  0x00000000            /*      Reset Value for MUX  */
#define REG_PORTA_MUX                        0xF0002050            /*  PORTA GPIO Multiplexer Control Register (MCR) */
#define REG_PORTA_DATA_TGL_RESET             0x00000000            /*      Reset Value for DATA_TGL  */
#define REG_PORTA_DATA_TGL                   0xF0002054            /*  PORTA Port x GPIO Output Toggle Register */
#define REG_PORTA_POL_RESET                  0x00000000            /*      Reset Value for POL  */
#define REG_PORTA_POL                        0xF0002058            /*  PORTA GPIO Polarity Invert Register */
#define REG_PORTA_LOCK_RESET                 0x00000000            /*      Reset Value for LOCK  */
#define REG_PORTA_LOCK                       0xF000205C            /*  PORTA GPIO Lock Register */
#define REG_PORTA_FER_SET_RESET              0x0000FFFF            /*      Reset Value for FER_SET  */
#define REG_PORTA_FER_SET                    0xF0002080            /*  PORTA GPIO Function Enable Set Register */
#define REG_PORTA_FER_CLR_RESET              0x0000FFFF            /*      Reset Value for FER_CLR  */
#define REG_PORTA_FER_CLR                    0xF0002084            /*  PORTA GPIO Function Enable Clear Register */
#define REG_PORTA_DATA_SET_RESET             0x00000000            /*      Reset Value for DATA_SET  */
#define REG_PORTA_DATA_SET                   0xF0002088            /*  PORTA GPIO Data Set Register */
#define REG_PORTA_DATA_CLR_RESET             0x00000000            /*      Reset Value for DATA_CLR  */
#define REG_PORTA_DATA_CLR                   0xF000208C            /*  PORTA GPIO Data Clear Register */
#define REG_PORTA_DIR_SET_RESET              0x00000000            /*      Reset Value for DIR_SET  */
#define REG_PORTA_DIR_SET                    0xF0002090            /*  PORTA GPIO Direction Set Register */
#define REG_PORTA_DIR_CLR_RESET              0x00000000            /*      Reset Value for DIR_CLR  */
#define REG_PORTA_DIR_CLR                    0xF0002094            /*  PORTA GPIO Direction Clear Register */
#define REG_PORTA_INEN_SET_RESET             0x0000FFFF            /*      Reset Value for INEN_SET  */
#define REG_PORTA_INEN_SET                   0xF0002098            /*  PORTA GPIO Input Enable Set Register */
#define REG_PORTA_INEN_CLR_RESET             0x0000FFFF            /*      Reset Value for INEN_CLR  */
#define REG_PORTA_INEN_CLR                   0xF000209C            /*  PORTA GPIO Input Enable Clear Register */
#define REG_PORTA_POL_SET_RESET              0x00000000            /*      Reset Value for POL_SET  */
#define REG_PORTA_POL_SET                    0xF00020A0            /*  PORTA GPIO Polarity Invert Set Register */
#define REG_PORTA_POL_CLR_RESET              0x00000000            /*      Reset Value for POL_CLR  */
#define REG_PORTA_POL_CLR                    0xF00020A4            /*  PORTA GPIO Polarity Invert Clear Register */

/* ============================================================================================================================
        PORTA Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_ST_EN                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_ST_EN_ST15                15            /*  Schmidt Trigger Pin F */
#define BITP_PORTA_ST_EN_ST14                14            /*  Schmidt Trigger Pin E */
#define BITP_PORTA_ST_EN_ST13                13            /*  Schmidt Trigger Pin D */
#define BITP_PORTA_ST_EN_ST12                12            /*  Schmidt Trigger Pin C */
#define BITP_PORTA_ST_EN_ST11                11            /*  Schmidt Trigger Pin B */
#define BITP_PORTA_ST_EN_ST10                10            /*  Schmidt Trigger Pin A */
#define BITP_PORTA_ST_EN_ST9                  9            /*  Schmidt Trigger Pin 9 */
#define BITP_PORTA_ST_EN_ST8                  8            /*  Schmidt Trigger Pin 8 */
#define BITP_PORTA_ST_EN_ST7                  7            /*  Schmidt Trigger Pin 7 */
#define BITP_PORTA_ST_EN_ST6                  6            /*  Schmidt Trigger Pin 6 */
#define BITP_PORTA_ST_EN_ST5                  5            /*  Schmidt Trigger Pin 5 */
#define BITP_PORTA_ST_EN_ST4                  4            /*  Schmidt Trigger Pin 4 */
#define BITP_PORTA_ST_EN_ST3                  3            /*  Schmidt Trigger Pin 3 */
#define BITP_PORTA_ST_EN_ST2                  2            /*  Schmidt Trigger Pin 2 */
#define BITP_PORTA_ST_EN_ST1                  1            /*  Schmidt Trigger Pin 1 */
#define BITP_PORTA_ST_EN_ST0                  0            /*  Schmidt Trigger Pin 0 */
#define BITM_PORTA_ST_EN_ST15                0x00008000    /*  Schmidt Trigger Pin F */
#define BITM_PORTA_ST_EN_ST14                0x00004000    /*  Schmidt Trigger Pin E */
#define BITM_PORTA_ST_EN_ST13                0x00002000    /*  Schmidt Trigger Pin D */
#define BITM_PORTA_ST_EN_ST12                0x00001000    /*  Schmidt Trigger Pin C */
#define BITM_PORTA_ST_EN_ST11                0x00000800    /*  Schmidt Trigger Pin B */
#define BITM_PORTA_ST_EN_ST10                0x00000400    /*  Schmidt Trigger Pin A */
#define BITM_PORTA_ST_EN_ST9                 0x00000200    /*  Schmidt Trigger Pin 9 */
#define BITM_PORTA_ST_EN_ST8                 0x00000100    /*  Schmidt Trigger Pin 8 */
#define BITM_PORTA_ST_EN_ST7                 0x00000080    /*  Schmidt Trigger Pin 7 */
#define BITM_PORTA_ST_EN_ST6                 0x00000040    /*  Schmidt Trigger Pin 6 */
#define BITM_PORTA_ST_EN_ST5                 0x00000020    /*  Schmidt Trigger Pin 5 */
#define BITM_PORTA_ST_EN_ST4                 0x00000010    /*  Schmidt Trigger Pin 4 */
#define BITM_PORTA_ST_EN_ST3                 0x00000008    /*  Schmidt Trigger Pin 3 */
#define BITM_PORTA_ST_EN_ST2                 0x00000004    /*  Schmidt Trigger Pin 2 */
#define BITM_PORTA_ST_EN_ST1                 0x00000002    /*  Schmidt Trigger Pin 1 */
#define BITM_PORTA_ST_EN_ST0                 0x00000001    /*  Schmidt Trigger Pin 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_SLRATE_SEL                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_SLRATE_SEL_SL15           15            /*  Slew rate control for pinF */
#define BITP_PORTA_SLRATE_SEL_SL14           14            /*  Slew rate control for pinE */
#define BITP_PORTA_SLRATE_SEL_SL13           13            /*  Slew rate control for pinD */
#define BITP_PORTA_SLRATE_SEL_SL12           12            /*  Slew rate control for pinC */
#define BITP_PORTA_SLRATE_SEL_SL11           11            /*  Slew rate control for pinB */
#define BITP_PORTA_SLRATE_SEL_SL10           10            /*  Slew rate control for pinA */
#define BITP_PORTA_SLRATE_SEL_SL9             9            /*  Slew rate control for pin9 */
#define BITP_PORTA_SLRATE_SEL_SL8             8            /*  Slew rate control for pin8 */
#define BITP_PORTA_SLRATE_SEL_SL7             7            /*  Slew rate control for pin7 */
#define BITP_PORTA_SLRATE_SEL_SL6             6            /*  Slew rate control for pin6 */
#define BITP_PORTA_SLRATE_SEL_SL5             5            /*  Slew rate control for pin5 */
#define BITP_PORTA_SLRATE_SEL_SL4             4            /*  Slew rate control for pin4 */
#define BITP_PORTA_SLRATE_SEL_SL3             3            /*  Slew rate control for pin3 */
#define BITP_PORTA_SLRATE_SEL_SL2             2            /*  Slew rate control for pin2 */
#define BITP_PORTA_SLRATE_SEL_SL1             1            /*  Slew Rate Control Pin 1 */
#define BITP_PORTA_SLRATE_SEL_SL0             0            /*  Slew Rate Control Pin 0 */
#define BITM_PORTA_SLRATE_SEL_SL15           0x00008000    /*  Slew rate control for pinF */
#define BITM_PORTA_SLRATE_SEL_SL14           0x00004000    /*  Slew rate control for pinE */
#define BITM_PORTA_SLRATE_SEL_SL13           0x00002000    /*  Slew rate control for pinD */
#define BITM_PORTA_SLRATE_SEL_SL12           0x00001000    /*  Slew rate control for pinC */
#define BITM_PORTA_SLRATE_SEL_SL11           0x00000800    /*  Slew rate control for pinB */
#define BITM_PORTA_SLRATE_SEL_SL10           0x00000400    /*  Slew rate control for pinA */
#define BITM_PORTA_SLRATE_SEL_SL9            0x00000200    /*  Slew rate control for pin9 */
#define BITM_PORTA_SLRATE_SEL_SL8            0x00000100    /*  Slew rate control for pin8 */
#define BITM_PORTA_SLRATE_SEL_SL7            0x00000080    /*  Slew rate control for pin7 */
#define BITM_PORTA_SLRATE_SEL_SL6            0x00000040    /*  Slew rate control for pin6 */
#define BITM_PORTA_SLRATE_SEL_SL5            0x00000020    /*  Slew rate control for pin5 */
#define BITM_PORTA_SLRATE_SEL_SL4            0x00000010    /*  Slew rate control for pin4 */
#define BITM_PORTA_SLRATE_SEL_SL3            0x00000008    /*  Slew rate control for pin3 */
#define BITM_PORTA_SLRATE_SEL_SL2            0x00000004    /*  Slew rate control for pin2 */
#define BITM_PORTA_SLRATE_SEL_SL1            0x00000002    /*  Slew Rate Control Pin 1 */
#define BITM_PORTA_SLRATE_SEL_SL0            0x00000001    /*  Slew Rate Control Pin 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_DS_SEL_L                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_DS_SEL_L_DS7              21            /*  Drive strength control for pin7 */
#define BITP_PORTA_DS_SEL_L_DS6              18            /*  Drive strength control for pin6 */
#define BITP_PORTA_DS_SEL_L_DS5              15            /*  Drive strength control for pin5 */
#define BITP_PORTA_DS_SEL_L_DS4              12            /*  Drive strength control for pin4 */
#define BITP_PORTA_DS_SEL_L_DS3               9            /*  Drive strength control for pin3 */
#define BITP_PORTA_DS_SEL_L_DS2               6            /*  Drive strength control for pin2 */
#define BITP_PORTA_DS_SEL_L_DS1               3            /*  Drive Strength Control Pin 1 */
#define BITP_PORTA_DS_SEL_L_DS0               0            /*  Drive Strength Control Pin 0 */
#define BITM_PORTA_DS_SEL_L_DS7              0x00E00000    /*  Drive strength control for pin7 */
#define BITM_PORTA_DS_SEL_L_DS6              0x001C0000    /*  Drive strength control for pin6 */
#define BITM_PORTA_DS_SEL_L_DS5              0x00038000    /*  Drive strength control for pin5 */
#define BITM_PORTA_DS_SEL_L_DS4              0x00007000    /*  Drive strength control for pin4 */
#define BITM_PORTA_DS_SEL_L_DS3              0x00000E00    /*  Drive strength control for pin3 */
#define BITM_PORTA_DS_SEL_L_DS2              0x000001C0    /*  Drive strength control for pin2 */
#define BITM_PORTA_DS_SEL_L_DS1              0x00000038    /*  Drive Strength Control Pin 1 */
#define BITM_PORTA_DS_SEL_L_DS0              0x00000007    /*  Drive Strength Control Pin 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_DS_SEL_H                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_DS_SEL_H_DS15             21            /*  Drive strength control for pinF */
#define BITP_PORTA_DS_SEL_H_DS14             18            /*  Drive strength control for pinE */
#define BITP_PORTA_DS_SEL_H_DS13             15            /*  Drive strength control for pinD */
#define BITP_PORTA_DS_SEL_H_DS12             12            /*  Drive strength control for pinC */
#define BITP_PORTA_DS_SEL_H_DS11              9            /*  Drive strength control for pinB */
#define BITP_PORTA_DS_SEL_H_DS10              6            /*  Drive strength control for pin10 */
#define BITP_PORTA_DS_SEL_H_DS9               3            /*  Drive strength control for pin9 */
#define BITP_PORTA_DS_SEL_H_DS8               0            /*  Drive strength control for pin8 */
#define BITM_PORTA_DS_SEL_H_DS15             0x00E00000    /*  Drive strength control for pinF */
#define BITM_PORTA_DS_SEL_H_DS14             0x001C0000    /*  Drive strength control for pinE */
#define BITM_PORTA_DS_SEL_H_DS13             0x00038000    /*  Drive strength control for pinD */
#define BITM_PORTA_DS_SEL_H_DS12             0x00007000    /*  Drive strength control for pinC */
#define BITM_PORTA_DS_SEL_H_DS11             0x00000E00    /*  Drive strength control for pinB */
#define BITM_PORTA_DS_SEL_H_DS10             0x000001C0    /*  Drive strength control for pin10 */
#define BITM_PORTA_DS_SEL_H_DS9              0x00000038    /*  Drive strength control for pin9 */
#define BITM_PORTA_DS_SEL_H_DS8              0x00000007    /*  Drive strength control for pin8 */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_PU_SEL                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_PU_SEL_PU15               15            /*  Pullup control for pinF */
#define BITP_PORTA_PU_SEL_PU14               14            /*  Pullup control for pinE */
#define BITP_PORTA_PU_SEL_PU13               13            /*  Pullup control for pinD */
#define BITP_PORTA_PU_SEL_PU12               12            /*  Pullup control for pinC */
#define BITP_PORTA_PU_SEL_PU11               11            /*  Pullup control for pinB */
#define BITP_PORTA_PU_SEL_PU10               10            /*  Pullup control for pinA */
#define BITP_PORTA_PU_SEL_PU9                 9            /*  Pullup control for pin9 */
#define BITP_PORTA_PU_SEL_PU8                 8            /*  Pullup control for pin8 */
#define BITP_PORTA_PU_SEL_PU7                 7            /*  Pullup control for pin7 */
#define BITP_PORTA_PU_SEL_PU6                 6            /*  Pullup control for pin6 */
#define BITP_PORTA_PU_SEL_PU5                 5            /*  Pullup control for pin5 */
#define BITP_PORTA_PU_SEL_PU4                 4            /*  Pullup control for pin4 */
#define BITP_PORTA_PU_SEL_PU3                 3            /*  Pullup control for pin3 */
#define BITP_PORTA_PU_SEL_PU2                 2            /*  Pullup control for pin2 */
#define BITP_PORTA_PU_SEL_PU1                 1            /*  Pullup Control Pin 1 */
#define BITP_PORTA_PU_SEL_PU0                 0            /*  Pullup Control Pin 0 */
#define BITM_PORTA_PU_SEL_PU15               0x00008000    /*  Pullup control for pinF */
#define BITM_PORTA_PU_SEL_PU14               0x00004000    /*  Pullup control for pinE */
#define BITM_PORTA_PU_SEL_PU13               0x00002000    /*  Pullup control for pinD */
#define BITM_PORTA_PU_SEL_PU12               0x00001000    /*  Pullup control for pinC */
#define BITM_PORTA_PU_SEL_PU11               0x00000800    /*  Pullup control for pinB */
#define BITM_PORTA_PU_SEL_PU10               0x00000400    /*  Pullup control for pinA */
#define BITM_PORTA_PU_SEL_PU9                0x00000200    /*  Pullup control for pin9 */
#define BITM_PORTA_PU_SEL_PU8                0x00000100    /*  Pullup control for pin8 */
#define BITM_PORTA_PU_SEL_PU7                0x00000080    /*  Pullup control for pin7 */
#define BITM_PORTA_PU_SEL_PU6                0x00000040    /*  Pullup control for pin6 */
#define BITM_PORTA_PU_SEL_PU5                0x00000020    /*  Pullup control for pin5 */
#define BITM_PORTA_PU_SEL_PU4                0x00000010    /*  Pullup control for pin4 */
#define BITM_PORTA_PU_SEL_PU3                0x00000008    /*  Pullup control for pin3 */
#define BITM_PORTA_PU_SEL_PU2                0x00000004    /*  Pullup control for pin2 */
#define BITM_PORTA_PU_SEL_PU1                0x00000002    /*  Pullup Control Pin 1 */
#define BITM_PORTA_PU_SEL_PU0                0x00000001    /*  Pullup Control Pin 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_PD_SEL                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_PD_SEL_PD15               15            /*  Pulldown control for pinF */
#define BITP_PORTA_PD_SEL_PD14               14            /*  Pulldown control for pinE */
#define BITP_PORTA_PD_SEL_PD13               13            /*  Pulldown control for pinD */
#define BITP_PORTA_PD_SEL_PD12               12            /*  Pulldown control for pinC */
#define BITP_PORTA_PD_SEL_PD11               11            /*  Pulldown control for pinB */
#define BITP_PORTA_PD_SEL_PD10               10            /*  Pulldown control for pinA */
#define BITP_PORTA_PD_SEL_PD9                 9            /*  Pulldown control for pin9 */
#define BITP_PORTA_PD_SEL_PD8                 8            /*  Pulldown control for pin8 */
#define BITP_PORTA_PD_SEL_PD7                 7            /*  Pulldown control for pin7 */
#define BITP_PORTA_PD_SEL_PD6                 6            /*  Pulldown control for pin6 */
#define BITP_PORTA_PD_SEL_PD5                 5            /*  Pulldown control for pin5 */
#define BITP_PORTA_PD_SEL_PD4                 4            /*  Pulldown control for pin4 */
#define BITP_PORTA_PD_SEL_PD3                 3            /*  Pulldown control for pin3 */
#define BITP_PORTA_PD_SEL_PD2                 2            /*  Pulldown control for pin2 */
#define BITP_PORTA_PD_SEL_PD1                 1            /*  Pulldown Control for Pin1 */
#define BITP_PORTA_PD_SEL_PD0                 0            /*  Pulldown Control for Pin 0 */
#define BITM_PORTA_PD_SEL_PD15               0x00008000    /*  Pulldown control for pinF */
#define BITM_PORTA_PD_SEL_PD14               0x00004000    /*  Pulldown control for pinE */
#define BITM_PORTA_PD_SEL_PD13               0x00002000    /*  Pulldown control for pinD */
#define BITM_PORTA_PD_SEL_PD12               0x00001000    /*  Pulldown control for pinC */
#define BITM_PORTA_PD_SEL_PD11               0x00000800    /*  Pulldown control for pinB */
#define BITM_PORTA_PD_SEL_PD10               0x00000400    /*  Pulldown control for pinA */
#define BITM_PORTA_PD_SEL_PD9                0x00000200    /*  Pulldown control for pin9 */
#define BITM_PORTA_PD_SEL_PD8                0x00000100    /*  Pulldown control for pin8 */
#define BITM_PORTA_PD_SEL_PD7                0x00000080    /*  Pulldown control for pin7 */
#define BITM_PORTA_PD_SEL_PD6                0x00000040    /*  Pulldown control for pin6 */
#define BITM_PORTA_PD_SEL_PD5                0x00000020    /*  Pulldown control for pin5 */
#define BITM_PORTA_PD_SEL_PD4                0x00000010    /*  Pulldown control for pin4 */
#define BITM_PORTA_PD_SEL_PD3                0x00000008    /*  Pulldown control for pin3 */
#define BITM_PORTA_PD_SEL_PD2                0x00000004    /*  Pulldown control for pin2 */
#define BITM_PORTA_PD_SEL_PD1                0x00000002    /*  Pulldown Control for Pin1 */
#define BITM_PORTA_PD_SEL_PD0                0x00000001    /*  Pulldown Control for Pin 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_FER                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_FER_PX15                  15            /*  Port x Bit 15 Mode */
#define BITP_PORTA_FER_PX14                  14            /*  Port x Bit 14 Mode */
#define BITP_PORTA_FER_PX13                  13            /*  Port x Bit 13 Mode */
#define BITP_PORTA_FER_PX12                  12            /*  Port x Bit 12 Mode */
#define BITP_PORTA_FER_PX11                  11            /*  Port x Bit 11 Mode */
#define BITP_PORTA_FER_PX10                  10            /*  Port x Bit 10 Mode */
#define BITP_PORTA_FER_PX9                    9            /*  Port x Bit 9 Mode */
#define BITP_PORTA_FER_PX8                    8            /*  Port x Bit 8 Mode */
#define BITP_PORTA_FER_PX7                    7            /*  Port x Bit 7 Mode */
#define BITP_PORTA_FER_PX6                    6            /*  Port x Bit 6 Mode */
#define BITP_PORTA_FER_PX5                    5            /*  Port x Bit 5 Mode */
#define BITP_PORTA_FER_PX4                    4            /*  Port x Bit 4 Mode */
#define BITP_PORTA_FER_PX3                    3            /*  Port x Bit 3 Mode */
#define BITP_PORTA_FER_PX2                    2            /*  Port x Bit 2 Mode */
#define BITP_PORTA_FER_PX1                    1            /*  Port x Bit 1 Mode */
#define BITP_PORTA_FER_PX0                    0            /*  Port x Bit 0 Mode */
#define BITM_PORTA_FER_PX15                  0x00008000    /*  Port x Bit 15 Mode */
#define BITM_PORTA_FER_PX14                  0x00004000    /*  Port x Bit 14 Mode */
#define BITM_PORTA_FER_PX13                  0x00002000    /*  Port x Bit 13 Mode */
#define BITM_PORTA_FER_PX12                  0x00001000    /*  Port x Bit 12 Mode */
#define BITM_PORTA_FER_PX11                  0x00000800    /*  Port x Bit 11 Mode */
#define BITM_PORTA_FER_PX10                  0x00000400    /*  Port x Bit 10 Mode */
#define BITM_PORTA_FER_PX9                   0x00000200    /*  Port x Bit 9 Mode */
#define BITM_PORTA_FER_PX8                   0x00000100    /*  Port x Bit 8 Mode */
#define BITM_PORTA_FER_PX7                   0x00000080    /*  Port x Bit 7 Mode */
#define BITM_PORTA_FER_PX6                   0x00000040    /*  Port x Bit 6 Mode */
#define BITM_PORTA_FER_PX5                   0x00000020    /*  Port x Bit 5 Mode */
#define BITM_PORTA_FER_PX4                   0x00000010    /*  Port x Bit 4 Mode */
#define BITM_PORTA_FER_PX3                   0x00000008    /*  Port x Bit 3 Mode */
#define BITM_PORTA_FER_PX2                   0x00000004    /*  Port x Bit 2 Mode */
#define BITM_PORTA_FER_PX1                   0x00000002    /*  Port x Bit 1 Mode */
#define BITM_PORTA_FER_PX0                   0x00000001    /*  Port x Bit 0 Mode */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_DATA                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_DATA_PX15                 15            /*  Port x Bit 15 Data */
#define BITP_PORTA_DATA_PX14                 14            /*  Port x Bit 14 Data */
#define BITP_PORTA_DATA_PX13                 13            /*  Port x Bit 13 Data */
#define BITP_PORTA_DATA_PX12                 12            /*  Port x Bit 12 Data */
#define BITP_PORTA_DATA_PX11                 11            /*  Port x Bit 11 Data */
#define BITP_PORTA_DATA_PX10                 10            /*  Port x Bit 10 Data */
#define BITP_PORTA_DATA_PX9                   9            /*  Port x Bit 9 Data */
#define BITP_PORTA_DATA_PX8                   8            /*  Port x Bit 8 Data */
#define BITP_PORTA_DATA_PX7                   7            /*  Port x Bit 7 Data */
#define BITP_PORTA_DATA_PX6                   6            /*  Port x Bit 6 Data */
#define BITP_PORTA_DATA_PX5                   5            /*  Port x Bit 5 Data */
#define BITP_PORTA_DATA_PX4                   4            /*  Port x Bit 4 Data */
#define BITP_PORTA_DATA_PX3                   3            /*  Port x Bit 3 Data */
#define BITP_PORTA_DATA_PX2                   2            /*  Port x Bit 2 Data */
#define BITP_PORTA_DATA_PX1                   1            /*  Port x Bit 1 Data */
#define BITP_PORTA_DATA_PX0                   0            /*  Port x Bit 0 Data */
#define BITM_PORTA_DATA_PX15                 0x00008000    /*  Port x Bit 15 Data */
#define BITM_PORTA_DATA_PX14                 0x00004000    /*  Port x Bit 14 Data */
#define BITM_PORTA_DATA_PX13                 0x00002000    /*  Port x Bit 13 Data */
#define BITM_PORTA_DATA_PX12                 0x00001000    /*  Port x Bit 12 Data */
#define BITM_PORTA_DATA_PX11                 0x00000800    /*  Port x Bit 11 Data */
#define BITM_PORTA_DATA_PX10                 0x00000400    /*  Port x Bit 10 Data */
#define BITM_PORTA_DATA_PX9                  0x00000200    /*  Port x Bit 9 Data */
#define BITM_PORTA_DATA_PX8                  0x00000100    /*  Port x Bit 8 Data */
#define BITM_PORTA_DATA_PX7                  0x00000080    /*  Port x Bit 7 Data */
#define BITM_PORTA_DATA_PX6                  0x00000040    /*  Port x Bit 6 Data */
#define BITM_PORTA_DATA_PX5                  0x00000020    /*  Port x Bit 5 Data */
#define BITM_PORTA_DATA_PX4                  0x00000010    /*  Port x Bit 4 Data */
#define BITM_PORTA_DATA_PX3                  0x00000008    /*  Port x Bit 3 Data */
#define BITM_PORTA_DATA_PX2                  0x00000004    /*  Port x Bit 2 Data */
#define BITM_PORTA_DATA_PX1                  0x00000002    /*  Port x Bit 1 Data */
#define BITM_PORTA_DATA_PX0                  0x00000001    /*  Port x Bit 0 Data */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_DIR                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_DIR_PX15                  15            /*  Port x Bit 15 Direction */
#define BITP_PORTA_DIR_PX14                  14            /*  Port x Bit 14 Direction */
#define BITP_PORTA_DIR_PX13                  13            /*  Port x Bit 13 Direction */
#define BITP_PORTA_DIR_PX12                  12            /*  Port x Bit 12 Direction */
#define BITP_PORTA_DIR_PX11                  11            /*  Port x Bit 11 Direction */
#define BITP_PORTA_DIR_PX10                  10            /*  Port x Bit 10 Direction */
#define BITP_PORTA_DIR_PX9                    9            /*  Port x Bit 9 Direction */
#define BITP_PORTA_DIR_PX8                    8            /*  Port x Bit 8 Direction */
#define BITP_PORTA_DIR_PX7                    7            /*  Port x Bit 7 Direction */
#define BITP_PORTA_DIR_PX6                    6            /*  Port x Bit 6 Direction */
#define BITP_PORTA_DIR_PX5                    5            /*  Port x Bit 5 Direction */
#define BITP_PORTA_DIR_PX4                    4            /*  Port x Bit 4 Direction */
#define BITP_PORTA_DIR_PX3                    3            /*  Port x Bit 3 Direction */
#define BITP_PORTA_DIR_PX2                    2            /*  Port x Bit 2 Direction */
#define BITP_PORTA_DIR_PX1                    1            /*  Port x Bit 1 Direction */
#define BITP_PORTA_DIR_PX0                    0            /*  Port x Bit 0 Direction */
#define BITM_PORTA_DIR_PX15                  0x00008000    /*  Port x Bit 15 Direction */
#define BITM_PORTA_DIR_PX14                  0x00004000    /*  Port x Bit 14 Direction */
#define BITM_PORTA_DIR_PX13                  0x00002000    /*  Port x Bit 13 Direction */
#define BITM_PORTA_DIR_PX12                  0x00001000    /*  Port x Bit 12 Direction */
#define BITM_PORTA_DIR_PX11                  0x00000800    /*  Port x Bit 11 Direction */
#define BITM_PORTA_DIR_PX10                  0x00000400    /*  Port x Bit 10 Direction */
#define BITM_PORTA_DIR_PX9                   0x00000200    /*  Port x Bit 9 Direction */
#define BITM_PORTA_DIR_PX8                   0x00000100    /*  Port x Bit 8 Direction */
#define BITM_PORTA_DIR_PX7                   0x00000080    /*  Port x Bit 7 Direction */
#define BITM_PORTA_DIR_PX6                   0x00000040    /*  Port x Bit 6 Direction */
#define BITM_PORTA_DIR_PX5                   0x00000020    /*  Port x Bit 5 Direction */
#define BITM_PORTA_DIR_PX4                   0x00000010    /*  Port x Bit 4 Direction */
#define BITM_PORTA_DIR_PX3                   0x00000008    /*  Port x Bit 3 Direction */
#define BITM_PORTA_DIR_PX2                   0x00000004    /*  Port x Bit 2 Direction */
#define BITM_PORTA_DIR_PX1                   0x00000002    /*  Port x Bit 1 Direction */
#define BITM_PORTA_DIR_PX0                   0x00000001    /*  Port x Bit 0 Direction */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_INEN                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_INEN_PX15                 15            /*  Port x Bit 15 Input Enable */
#define BITP_PORTA_INEN_PX14                 14            /*  Port x Bit 14 Input Enable */
#define BITP_PORTA_INEN_PX13                 13            /*  Port x Bit 13 Input Enable */
#define BITP_PORTA_INEN_PX12                 12            /*  Port x Bit 12 Input Enable */
#define BITP_PORTA_INEN_PX11                 11            /*  Port x Bit 11 Input Enable */
#define BITP_PORTA_INEN_PX10                 10            /*  Port x Bit 10 Input Enable */
#define BITP_PORTA_INEN_PX9                   9            /*  Port x Bit 9 Input Enable */
#define BITP_PORTA_INEN_PX8                   8            /*  Port x Bit 8 Input Enable */
#define BITP_PORTA_INEN_PX7                   7            /*  Port x Bit 7 Input Enable */
#define BITP_PORTA_INEN_PX6                   6            /*  Port x Bit 6 Input Enable */
#define BITP_PORTA_INEN_PX5                   5            /*  Port x Bit 5 Input Enable */
#define BITP_PORTA_INEN_PX4                   4            /*  Port x Bit 4 Input Enable */
#define BITP_PORTA_INEN_PX3                   3            /*  Port x Bit 3 Input Enable */
#define BITP_PORTA_INEN_PX2                   2            /*  Port x Bit 2 Input Enable */
#define BITP_PORTA_INEN_PX1                   1            /*  Port x Bit 1 Input Enable */
#define BITP_PORTA_INEN_PX0                   0            /*  Port x Bit 0 Input Enable */
#define BITM_PORTA_INEN_PX15                 0x00008000    /*  Port x Bit 15 Input Enable */
#define BITM_PORTA_INEN_PX14                 0x00004000    /*  Port x Bit 14 Input Enable */
#define BITM_PORTA_INEN_PX13                 0x00002000    /*  Port x Bit 13 Input Enable */
#define BITM_PORTA_INEN_PX12                 0x00001000    /*  Port x Bit 12 Input Enable */
#define BITM_PORTA_INEN_PX11                 0x00000800    /*  Port x Bit 11 Input Enable */
#define BITM_PORTA_INEN_PX10                 0x00000400    /*  Port x Bit 10 Input Enable */
#define BITM_PORTA_INEN_PX9                  0x00000200    /*  Port x Bit 9 Input Enable */
#define BITM_PORTA_INEN_PX8                  0x00000100    /*  Port x Bit 8 Input Enable */
#define BITM_PORTA_INEN_PX7                  0x00000080    /*  Port x Bit 7 Input Enable */
#define BITM_PORTA_INEN_PX6                  0x00000040    /*  Port x Bit 6 Input Enable */
#define BITM_PORTA_INEN_PX5                  0x00000020    /*  Port x Bit 5 Input Enable */
#define BITM_PORTA_INEN_PX4                  0x00000010    /*  Port x Bit 4 Input Enable */
#define BITM_PORTA_INEN_PX3                  0x00000008    /*  Port x Bit 3 Input Enable */
#define BITM_PORTA_INEN_PX2                  0x00000004    /*  Port x Bit 2 Input Enable */
#define BITM_PORTA_INEN_PX1                  0x00000002    /*  Port x Bit 1 Input Enable */
#define BITM_PORTA_INEN_PX0                  0x00000001    /*  Port x Bit 0 Input Enable */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_MUX                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_MUX_MUX15                 30            /*  Mux for Port x Bit 15 */
#define BITP_PORTA_MUX_MUX14                 28            /*  Mux for Port x Bit 14 */
#define BITP_PORTA_MUX_MUX13                 26            /*  Mux for Port x Bit 13 */
#define BITP_PORTA_MUX_MUX12                 24            /*  Mux for Port x Bit 12 */
#define BITP_PORTA_MUX_MUX11                 22            /*  Mux for Port x Bit 11 */
#define BITP_PORTA_MUX_MUX10                 20            /*  Mux for Port x Bit 10 */
#define BITP_PORTA_MUX_MUX9                  18            /*  Mux for Port x Bit 9 */
#define BITP_PORTA_MUX_MUX8                  16            /*  Mux for Port x Bit 8 */
#define BITP_PORTA_MUX_MUX7                  14            /*  Mux for Port x Bit 7 */
#define BITP_PORTA_MUX_MUX6                  12            /*  Mux for Port x Bit 6 */
#define BITP_PORTA_MUX_MUX5                  10            /*  Mux for Port x Bit 5 */
#define BITP_PORTA_MUX_MUX4                   8            /*  Mux for Port x Bit 4 */
#define BITP_PORTA_MUX_MUX3                   6            /*  Mux for Port x Bit 3 */
#define BITP_PORTA_MUX_MUX2                   4            /*  Mux for Port x Bit 2 */
#define BITP_PORTA_MUX_MUX1                   2            /*  Mux for Port x Bit 1 */
#define BITP_PORTA_MUX_MUX0                   0            /*  Mux for Port x Bit 0 */
#define BITM_PORTA_MUX_MUX15                 0xC0000000    /*  Mux for Port x Bit 15 */
#define BITM_PORTA_MUX_MUX14                 0x30000000    /*  Mux for Port x Bit 14 */
#define BITM_PORTA_MUX_MUX13                 0x0C000000    /*  Mux for Port x Bit 13 */
#define BITM_PORTA_MUX_MUX12                 0x03000000    /*  Mux for Port x Bit 12 */
#define BITM_PORTA_MUX_MUX11                 0x00C00000    /*  Mux for Port x Bit 11 */
#define BITM_PORTA_MUX_MUX10                 0x00300000    /*  Mux for Port x Bit 10 */
#define BITM_PORTA_MUX_MUX9                  0x000C0000    /*  Mux for Port x Bit 9 */
#define BITM_PORTA_MUX_MUX8                  0x00030000    /*  Mux for Port x Bit 8 */
#define BITM_PORTA_MUX_MUX7                  0x0000C000    /*  Mux for Port x Bit 7 */
#define BITM_PORTA_MUX_MUX6                  0x00003000    /*  Mux for Port x Bit 6 */
#define BITM_PORTA_MUX_MUX5                  0x00000C00    /*  Mux for Port x Bit 5 */
#define BITM_PORTA_MUX_MUX4                  0x00000300    /*  Mux for Port x Bit 4 */
#define BITM_PORTA_MUX_MUX3                  0x000000C0    /*  Mux for Port x Bit 3 */
#define BITM_PORTA_MUX_MUX2                  0x00000030    /*  Mux for Port x Bit 2 */
#define BITM_PORTA_MUX_MUX1                  0x0000000C    /*  Mux for Port x Bit 1 */
#define BITM_PORTA_MUX_MUX0                  0x00000003    /*  Mux for Port x Bit 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_DATA_TGL                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_DATA_TGL_PX15             15            /*  Port x Bit 15 Toggle */
#define BITP_PORTA_DATA_TGL_PX14             14            /*  Port x Bit 14 Toggle */
#define BITP_PORTA_DATA_TGL_PX13             13            /*  Port x Bit 13 Toggle */
#define BITP_PORTA_DATA_TGL_PX12             12            /*  Port x Bit 12 Toggle */
#define BITP_PORTA_DATA_TGL_PX11             11            /*  Port x Bit 11 Toggle */
#define BITP_PORTA_DATA_TGL_PX10             10            /*  Port x Bit 10 Toggle */
#define BITP_PORTA_DATA_TGL_PX9               9            /*  Port x Bit 9 Toggle */
#define BITP_PORTA_DATA_TGL_PX8               8            /*  Port x Bit 8 Toggle */
#define BITP_PORTA_DATA_TGL_PX7               7            /*  Port x Bit 7 Toggle */
#define BITP_PORTA_DATA_TGL_PX6               6            /*  Port x Bit 6 Toggle */
#define BITP_PORTA_DATA_TGL_PX5               5            /*  Port x Bit 5 Toggle */
#define BITP_PORTA_DATA_TGL_PX4               4            /*  Port x Bit 4 Toggle */
#define BITP_PORTA_DATA_TGL_PX3               3            /*  Port x Bit 3 Toggle */
#define BITP_PORTA_DATA_TGL_PX2               2            /*  Port x Bit 2 Toggle */
#define BITP_PORTA_DATA_TGL_PX1               1            /*  Port x Bit 1 Toggle */
#define BITP_PORTA_DATA_TGL_PX0               0            /*  Port x Bit 0 Toggle */
#define BITM_PORTA_DATA_TGL_PX15             0x00008000    /*  Port x Bit 15 Toggle */
#define BITM_PORTA_DATA_TGL_PX14             0x00004000    /*  Port x Bit 14 Toggle */
#define BITM_PORTA_DATA_TGL_PX13             0x00002000    /*  Port x Bit 13 Toggle */
#define BITM_PORTA_DATA_TGL_PX12             0x00001000    /*  Port x Bit 12 Toggle */
#define BITM_PORTA_DATA_TGL_PX11             0x00000800    /*  Port x Bit 11 Toggle */
#define BITM_PORTA_DATA_TGL_PX10             0x00000400    /*  Port x Bit 10 Toggle */
#define BITM_PORTA_DATA_TGL_PX9              0x00000200    /*  Port x Bit 9 Toggle */
#define BITM_PORTA_DATA_TGL_PX8              0x00000100    /*  Port x Bit 8 Toggle */
#define BITM_PORTA_DATA_TGL_PX7              0x00000080    /*  Port x Bit 7 Toggle */
#define BITM_PORTA_DATA_TGL_PX6              0x00000040    /*  Port x Bit 6 Toggle */
#define BITM_PORTA_DATA_TGL_PX5              0x00000020    /*  Port x Bit 5 Toggle */
#define BITM_PORTA_DATA_TGL_PX4              0x00000010    /*  Port x Bit 4 Toggle */
#define BITM_PORTA_DATA_TGL_PX3              0x00000008    /*  Port x Bit 3 Toggle */
#define BITM_PORTA_DATA_TGL_PX2              0x00000004    /*  Port x Bit 2 Toggle */
#define BITM_PORTA_DATA_TGL_PX1              0x00000002    /*  Port x Bit 1 Toggle */
#define BITM_PORTA_DATA_TGL_PX0              0x00000001    /*  Port x Bit 0 Toggle */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_POL                            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_POL_PX15                  15            /*  Port x Bit 15 Polarity Invert */
#define BITP_PORTA_POL_PX14                  14            /*  Port x Bit 14 Polarity Invert */
#define BITP_PORTA_POL_PX13                  13            /*  Port x Bit 13 Polarity Invert */
#define BITP_PORTA_POL_PX12                  12            /*  Port x Bit 12 Polarity Invert */
#define BITP_PORTA_POL_PX11                  11            /*  Port x Bit 11 Polarity Invert */
#define BITP_PORTA_POL_PX10                  10            /*  Port x Bit 10 Polarity Invert */
#define BITP_PORTA_POL_PX9                    9            /*  Port x Bit 9 Polarity Invert */
#define BITP_PORTA_POL_PX8                    8            /*  Port x Bit 8 Polarity Invert */
#define BITP_PORTA_POL_PX7                    7            /*  Port x Bit 7 Polarity Invert */
#define BITP_PORTA_POL_PX6                    6            /*  Port x Bit 6 Polarity Invert */
#define BITP_PORTA_POL_PX5                    5            /*  Port x Bit 5 Polarity Invert */
#define BITP_PORTA_POL_PX4                    4            /*  Port x Bit 4 Polarity Invert */
#define BITP_PORTA_POL_PX3                    3            /*  Port x Bit 3 Polarity Invert */
#define BITP_PORTA_POL_PX2                    2            /*  Port x Bit 2 Polarity Invert */
#define BITP_PORTA_POL_PX1                    1            /*  Port x Bit 1 Polarity Invert */
#define BITP_PORTA_POL_PX0                    0            /*  Port x Bit 0 Polarity Invert */
#define BITM_PORTA_POL_PX15                  0x00008000    /*  Port x Bit 15 Polarity Invert */
#define BITM_PORTA_POL_PX14                  0x00004000    /*  Port x Bit 14 Polarity Invert */
#define BITM_PORTA_POL_PX13                  0x00002000    /*  Port x Bit 13 Polarity Invert */
#define BITM_PORTA_POL_PX12                  0x00001000    /*  Port x Bit 12 Polarity Invert */
#define BITM_PORTA_POL_PX11                  0x00000800    /*  Port x Bit 11 Polarity Invert */
#define BITM_PORTA_POL_PX10                  0x00000400    /*  Port x Bit 10 Polarity Invert */
#define BITM_PORTA_POL_PX9                   0x00000200    /*  Port x Bit 9 Polarity Invert */
#define BITM_PORTA_POL_PX8                   0x00000100    /*  Port x Bit 8 Polarity Invert */
#define BITM_PORTA_POL_PX7                   0x00000080    /*  Port x Bit 7 Polarity Invert */
#define BITM_PORTA_POL_PX6                   0x00000040    /*  Port x Bit 6 Polarity Invert */
#define BITM_PORTA_POL_PX5                   0x00000020    /*  Port x Bit 5 Polarity Invert */
#define BITM_PORTA_POL_PX4                   0x00000010    /*  Port x Bit 4 Polarity Invert */
#define BITM_PORTA_POL_PX3                   0x00000008    /*  Port x Bit 3 Polarity Invert */
#define BITM_PORTA_POL_PX2                   0x00000004    /*  Port x Bit 2 Polarity Invert */
#define BITM_PORTA_POL_PX1                   0x00000002    /*  Port x Bit 1 Polarity Invert */
#define BITM_PORTA_POL_PX0                   0x00000001    /*  Port x Bit 0 Polarity Invert */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_LOCK                           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_LOCK_LOCK                 31            /*  Lock */
#define BITP_PORTA_LOCK_POLAR                 5            /*  Polarity Lock */
#define BITP_PORTA_LOCK_INEN                  4            /*  Input Enable Lock */
#define BITP_PORTA_LOCK_DIR                   3            /*  Direction Lock */
#define BITP_PORTA_LOCK_DATA                  2            /*  Data, TGL Lock */
#define BITP_PORTA_LOCK_MUX                   1            /*  Function Multiplexer Lock */
#define BITP_PORTA_LOCK_FER                   0            /*  Function Enable Lock */
#define BITM_PORTA_LOCK_LOCK                 0x80000000    /*  Lock */
#define BITM_PORTA_LOCK_POLAR                0x00000020    /*  Polarity Lock */
#define BITM_PORTA_LOCK_INEN                 0x00000010    /*  Input Enable Lock */
#define BITM_PORTA_LOCK_DIR                  0x00000008    /*  Direction Lock */
#define BITM_PORTA_LOCK_DATA                 0x00000004    /*  Data, TGL Lock */
#define BITM_PORTA_LOCK_MUX                  0x00000002    /*  Function Multiplexer Lock */
#define BITM_PORTA_LOCK_FER                  0x00000001    /*  Function Enable Lock */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_FER_SET                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_FER_SET_PX15              15            /*  Port x Bit 15 Mode Set */
#define BITP_PORTA_FER_SET_PX14              14            /*  Port x Bit 14 Mode Set */
#define BITP_PORTA_FER_SET_PX13              13            /*  Port x Bit 13 Mode Set */
#define BITP_PORTA_FER_SET_PX12              12            /*  Port x Bit 12 Mode Set */
#define BITP_PORTA_FER_SET_PX11              11            /*  Port x Bit 11 Mode Set */
#define BITP_PORTA_FER_SET_PX10              10            /*  Port x Bit 10 Mode Set */
#define BITP_PORTA_FER_SET_PX9                9            /*  Port x Bit 9 Mode Set */
#define BITP_PORTA_FER_SET_PX8                8            /*  Port x Bit 8 Mode Set */
#define BITP_PORTA_FER_SET_PX7                7            /*  Port x Bit 7 Mode Set */
#define BITP_PORTA_FER_SET_PX6                6            /*  Port x Bit 6 Mode Set */
#define BITP_PORTA_FER_SET_PX5                5            /*  Port x Bit 5 Mode Set */
#define BITP_PORTA_FER_SET_PX4                4            /*  Port x Bit 4 Mode Set */
#define BITP_PORTA_FER_SET_PX3                3            /*  Port x Bit 3 Mode Set */
#define BITP_PORTA_FER_SET_PX2                2            /*  Port x Bit 2 Mode Set */
#define BITP_PORTA_FER_SET_PX1                1            /*  Port x Bit 1 Mode Set */
#define BITP_PORTA_FER_SET_PX0                0            /*  Port x Bit 0 Mode Set */
#define BITM_PORTA_FER_SET_PX15              0x00008000    /*  Port x Bit 15 Mode Set */
#define BITM_PORTA_FER_SET_PX14              0x00004000    /*  Port x Bit 14 Mode Set */
#define BITM_PORTA_FER_SET_PX13              0x00002000    /*  Port x Bit 13 Mode Set */
#define BITM_PORTA_FER_SET_PX12              0x00001000    /*  Port x Bit 12 Mode Set */
#define BITM_PORTA_FER_SET_PX11              0x00000800    /*  Port x Bit 11 Mode Set */
#define BITM_PORTA_FER_SET_PX10              0x00000400    /*  Port x Bit 10 Mode Set */
#define BITM_PORTA_FER_SET_PX9               0x00000200    /*  Port x Bit 9 Mode Set */
#define BITM_PORTA_FER_SET_PX8               0x00000100    /*  Port x Bit 8 Mode Set */
#define BITM_PORTA_FER_SET_PX7               0x00000080    /*  Port x Bit 7 Mode Set */
#define BITM_PORTA_FER_SET_PX6               0x00000040    /*  Port x Bit 6 Mode Set */
#define BITM_PORTA_FER_SET_PX5               0x00000020    /*  Port x Bit 5 Mode Set */
#define BITM_PORTA_FER_SET_PX4               0x00000010    /*  Port x Bit 4 Mode Set */
#define BITM_PORTA_FER_SET_PX3               0x00000008    /*  Port x Bit 3 Mode Set */
#define BITM_PORTA_FER_SET_PX2               0x00000004    /*  Port x Bit 2 Mode Set */
#define BITM_PORTA_FER_SET_PX1               0x00000002    /*  Port x Bit 1 Mode Set */
#define BITM_PORTA_FER_SET_PX0               0x00000001    /*  Port x Bit 0 Mode Set */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_FER_CLR                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_FER_CLR_PX15              15            /*  Port x Bit 15 Mode Clear */
#define BITP_PORTA_FER_CLR_PX14              14            /*  Port x Bit 14 Mode Clear */
#define BITP_PORTA_FER_CLR_PX13              13            /*  Port x Bit 13 Mode Clear */
#define BITP_PORTA_FER_CLR_PX12              12            /*  Port x Bit 12 Mode Clear */
#define BITP_PORTA_FER_CLR_PX11              11            /*  Port x Bit 11 Mode Clear */
#define BITP_PORTA_FER_CLR_PX10              10            /*  Port x Bit 10 Mode Clear */
#define BITP_PORTA_FER_CLR_PX9                9            /*  Port x Bit 9 Mode Clear */
#define BITP_PORTA_FER_CLR_PX8                8            /*  Port x Bit 8 Mode Clear */
#define BITP_PORTA_FER_CLR_PX7                7            /*  Port x Bit 7 Mode Clear */
#define BITP_PORTA_FER_CLR_PX6                6            /*  Port x Bit 6 Mode Clear */
#define BITP_PORTA_FER_CLR_PX5                5            /*  Port x Bit 5 Mode Clear */
#define BITP_PORTA_FER_CLR_PX4                4            /*  Port x Bit 4 Mode Clear */
#define BITP_PORTA_FER_CLR_PX3                3            /*  Port x Bit 3 Mode Clear */
#define BITP_PORTA_FER_CLR_PX2                2            /*  Port x Bit 2 Mode Clear */
#define BITP_PORTA_FER_CLR_PX1                1            /*  Port x Bit 1 Mode Clear */
#define BITP_PORTA_FER_CLR_PX0                0            /*  Port x Bit 0 Mode Clear */
#define BITM_PORTA_FER_CLR_PX15              0x00008000    /*  Port x Bit 15 Mode Clear */
#define BITM_PORTA_FER_CLR_PX14              0x00004000    /*  Port x Bit 14 Mode Clear */
#define BITM_PORTA_FER_CLR_PX13              0x00002000    /*  Port x Bit 13 Mode Clear */
#define BITM_PORTA_FER_CLR_PX12              0x00001000    /*  Port x Bit 12 Mode Clear */
#define BITM_PORTA_FER_CLR_PX11              0x00000800    /*  Port x Bit 11 Mode Clear */
#define BITM_PORTA_FER_CLR_PX10              0x00000400    /*  Port x Bit 10 Mode Clear */
#define BITM_PORTA_FER_CLR_PX9               0x00000200    /*  Port x Bit 9 Mode Clear */
#define BITM_PORTA_FER_CLR_PX8               0x00000100    /*  Port x Bit 8 Mode Clear */
#define BITM_PORTA_FER_CLR_PX7               0x00000080    /*  Port x Bit 7 Mode Clear */
#define BITM_PORTA_FER_CLR_PX6               0x00000040    /*  Port x Bit 6 Mode Clear */
#define BITM_PORTA_FER_CLR_PX5               0x00000020    /*  Port x Bit 5 Mode Clear */
#define BITM_PORTA_FER_CLR_PX4               0x00000010    /*  Port x Bit 4 Mode Clear */
#define BITM_PORTA_FER_CLR_PX3               0x00000008    /*  Port x Bit 3 Mode Clear */
#define BITM_PORTA_FER_CLR_PX2               0x00000004    /*  Port x Bit 2 Mode Clear */
#define BITM_PORTA_FER_CLR_PX1               0x00000002    /*  Port x Bit 1 Mode Clear */
#define BITM_PORTA_FER_CLR_PX0               0x00000001    /*  Port x Bit 0 Mode Clear */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_DATA_SET                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_DATA_SET_PX15             15            /*  Port x Bit 15 Data Set */
#define BITP_PORTA_DATA_SET_PX14             14            /*  Port x Bit 14 Data Set */
#define BITP_PORTA_DATA_SET_PX13             13            /*  Port x Bit 13 Data Set */
#define BITP_PORTA_DATA_SET_PX12             12            /*  Port x Bit 12 Data Set */
#define BITP_PORTA_DATA_SET_PX11             11            /*  Port x Bit 11 Data Set */
#define BITP_PORTA_DATA_SET_PX10             10            /*  Port x Bit 10 Data Set */
#define BITP_PORTA_DATA_SET_PX9               9            /*  Port x Bit 9 Data Set */
#define BITP_PORTA_DATA_SET_PX8               8            /*  Port x Bit 8 Data Set */
#define BITP_PORTA_DATA_SET_PX7               7            /*  Port x Bit 7 Data Set */
#define BITP_PORTA_DATA_SET_PX6               6            /*  Port x Bit 6 Data Set */
#define BITP_PORTA_DATA_SET_PX5               5            /*  Port x Bit 5 Data Set */
#define BITP_PORTA_DATA_SET_PX4               4            /*  Port x Bit 4 Data Set */
#define BITP_PORTA_DATA_SET_PX3               3            /*  Port x Bit 3 Data Set */
#define BITP_PORTA_DATA_SET_PX2               2            /*  Port x Bit 2 Data Set */
#define BITP_PORTA_DATA_SET_PX1               1            /*  Port x Bit 1 Data Set */
#define BITP_PORTA_DATA_SET_PX0               0            /*  Port x Bit 0 Data Set */
#define BITM_PORTA_DATA_SET_PX15             0x00008000    /*  Port x Bit 15 Data Set */
#define BITM_PORTA_DATA_SET_PX14             0x00004000    /*  Port x Bit 14 Data Set */
#define BITM_PORTA_DATA_SET_PX13             0x00002000    /*  Port x Bit 13 Data Set */
#define BITM_PORTA_DATA_SET_PX12             0x00001000    /*  Port x Bit 12 Data Set */
#define BITM_PORTA_DATA_SET_PX11             0x00000800    /*  Port x Bit 11 Data Set */
#define BITM_PORTA_DATA_SET_PX10             0x00000400    /*  Port x Bit 10 Data Set */
#define BITM_PORTA_DATA_SET_PX9              0x00000200    /*  Port x Bit 9 Data Set */
#define BITM_PORTA_DATA_SET_PX8              0x00000100    /*  Port x Bit 8 Data Set */
#define BITM_PORTA_DATA_SET_PX7              0x00000080    /*  Port x Bit 7 Data Set */
#define BITM_PORTA_DATA_SET_PX6              0x00000040    /*  Port x Bit 6 Data Set */
#define BITM_PORTA_DATA_SET_PX5              0x00000020    /*  Port x Bit 5 Data Set */
#define BITM_PORTA_DATA_SET_PX4              0x00000010    /*  Port x Bit 4 Data Set */
#define BITM_PORTA_DATA_SET_PX3              0x00000008    /*  Port x Bit 3 Data Set */
#define BITM_PORTA_DATA_SET_PX2              0x00000004    /*  Port x Bit 2 Data Set */
#define BITM_PORTA_DATA_SET_PX1              0x00000002    /*  Port x Bit 1 Data Set */
#define BITM_PORTA_DATA_SET_PX0              0x00000001    /*  Port x Bit 0 Data Set */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_DATA_CLR                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_DATA_CLR_PX15             15            /*  Port x Bit 15 Data Clear */
#define BITP_PORTA_DATA_CLR_PX14             14            /*  Port x Bit 14 Data Clear */
#define BITP_PORTA_DATA_CLR_PX13             13            /*  Port x Bit 13 Data Clear */
#define BITP_PORTA_DATA_CLR_PX12             12            /*  Port x Bit 12 Data Clear */
#define BITP_PORTA_DATA_CLR_PX11             11            /*  Port x Bit 11 Data Clear */
#define BITP_PORTA_DATA_CLR_PX10             10            /*  Port x Bit 10 Data Clear */
#define BITP_PORTA_DATA_CLR_PX9               9            /*  Port x Bit 9 Data Clear */
#define BITP_PORTA_DATA_CLR_PX8               8            /*  Port x Bit 8 Data Clear */
#define BITP_PORTA_DATA_CLR_PX7               7            /*  Port x Bit 7 Data Clear */
#define BITP_PORTA_DATA_CLR_PX6               6            /*  Port x Bit 6 Data Clear */
#define BITP_PORTA_DATA_CLR_PX5               5            /*  Port x Bit 5 Data Clear */
#define BITP_PORTA_DATA_CLR_PX4               4            /*  Port x Bit 4 Data Clear */
#define BITP_PORTA_DATA_CLR_PX3               3            /*  Port x Bit 3 Data Clear */
#define BITP_PORTA_DATA_CLR_PX2               2            /*  Port x Bit 2 Data Clear */
#define BITP_PORTA_DATA_CLR_PX1               1            /*  Port x Bit 1 Data Clear */
#define BITP_PORTA_DATA_CLR_PX0               0            /*  Port x Bit 0 Data Clear */
#define BITM_PORTA_DATA_CLR_PX15             0x00008000    /*  Port x Bit 15 Data Clear */
#define BITM_PORTA_DATA_CLR_PX14             0x00004000    /*  Port x Bit 14 Data Clear */
#define BITM_PORTA_DATA_CLR_PX13             0x00002000    /*  Port x Bit 13 Data Clear */
#define BITM_PORTA_DATA_CLR_PX12             0x00001000    /*  Port x Bit 12 Data Clear */
#define BITM_PORTA_DATA_CLR_PX11             0x00000800    /*  Port x Bit 11 Data Clear */
#define BITM_PORTA_DATA_CLR_PX10             0x00000400    /*  Port x Bit 10 Data Clear */
#define BITM_PORTA_DATA_CLR_PX9              0x00000200    /*  Port x Bit 9 Data Clear */
#define BITM_PORTA_DATA_CLR_PX8              0x00000100    /*  Port x Bit 8 Data Clear */
#define BITM_PORTA_DATA_CLR_PX7              0x00000080    /*  Port x Bit 7 Data Clear */
#define BITM_PORTA_DATA_CLR_PX6              0x00000040    /*  Port x Bit 6 Data Clear */
#define BITM_PORTA_DATA_CLR_PX5              0x00000020    /*  Port x Bit 5 Data Clear */
#define BITM_PORTA_DATA_CLR_PX4              0x00000010    /*  Port x Bit 4 Data Clear */
#define BITM_PORTA_DATA_CLR_PX3              0x00000008    /*  Port x Bit 3 Data Clear */
#define BITM_PORTA_DATA_CLR_PX2              0x00000004    /*  Port x Bit 2 Data Clear */
#define BITM_PORTA_DATA_CLR_PX1              0x00000002    /*  Port x Bit 1 Data Clear */
#define BITM_PORTA_DATA_CLR_PX0              0x00000001    /*  Port x Bit 0 Data Clear */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_DIR_SET                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_DIR_SET_PX15              15            /*  Port x Bit 15 Direction Set */
#define BITP_PORTA_DIR_SET_PX14              14            /*  Port x Bit 14 Direction Set */
#define BITP_PORTA_DIR_SET_PX13              13            /*  Port x Bit 13 Direction Set */
#define BITP_PORTA_DIR_SET_PX12              12            /*  Port x Bit 12 Direction Set */
#define BITP_PORTA_DIR_SET_PX11              11            /*  Port x Bit 11 Direction Set */
#define BITP_PORTA_DIR_SET_PX10              10            /*  Port x Bit 10 Direction Set */
#define BITP_PORTA_DIR_SET_PX9                9            /*  Port x Bit 9 Direction Set */
#define BITP_PORTA_DIR_SET_PX8                8            /*  Port x Bit 8 Direction Set */
#define BITP_PORTA_DIR_SET_PX7                7            /*  Port x Bit 7 Direction Set */
#define BITP_PORTA_DIR_SET_PX6                6            /*  Port x Bit 6 Direction Set */
#define BITP_PORTA_DIR_SET_PX5                5            /*  Port x Bit 5 Direction Set */
#define BITP_PORTA_DIR_SET_PX4                4            /*  Port x Bit 4 Direction Set */
#define BITP_PORTA_DIR_SET_PX3                3            /*  Port x Bit 3 Direction Set */
#define BITP_PORTA_DIR_SET_PX2                2            /*  Port x Bit 2 Direction Set */
#define BITP_PORTA_DIR_SET_PX1                1            /*  Port x Bit 1 Direction Set */
#define BITP_PORTA_DIR_SET_PX0                0            /*  Port x Bit 0 Direction Set */
#define BITM_PORTA_DIR_SET_PX15              0x00008000    /*  Port x Bit 15 Direction Set */
#define BITM_PORTA_DIR_SET_PX14              0x00004000    /*  Port x Bit 14 Direction Set */
#define BITM_PORTA_DIR_SET_PX13              0x00002000    /*  Port x Bit 13 Direction Set */
#define BITM_PORTA_DIR_SET_PX12              0x00001000    /*  Port x Bit 12 Direction Set */
#define BITM_PORTA_DIR_SET_PX11              0x00000800    /*  Port x Bit 11 Direction Set */
#define BITM_PORTA_DIR_SET_PX10              0x00000400    /*  Port x Bit 10 Direction Set */
#define BITM_PORTA_DIR_SET_PX9               0x00000200    /*  Port x Bit 9 Direction Set */
#define BITM_PORTA_DIR_SET_PX8               0x00000100    /*  Port x Bit 8 Direction Set */
#define BITM_PORTA_DIR_SET_PX7               0x00000080    /*  Port x Bit 7 Direction Set */
#define BITM_PORTA_DIR_SET_PX6               0x00000040    /*  Port x Bit 6 Direction Set */
#define BITM_PORTA_DIR_SET_PX5               0x00000020    /*  Port x Bit 5 Direction Set */
#define BITM_PORTA_DIR_SET_PX4               0x00000010    /*  Port x Bit 4 Direction Set */
#define BITM_PORTA_DIR_SET_PX3               0x00000008    /*  Port x Bit 3 Direction Set */
#define BITM_PORTA_DIR_SET_PX2               0x00000004    /*  Port x Bit 2 Direction Set */
#define BITM_PORTA_DIR_SET_PX1               0x00000002    /*  Port x Bit 1 Direction Set */
#define BITM_PORTA_DIR_SET_PX0               0x00000001    /*  Port x Bit 0 Direction Set */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_DIR_CLR                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_DIR_CLR_PX15              15            /*  Port x Bit 15 Direction Clear */
#define BITP_PORTA_DIR_CLR_PX14              14            /*  Port x Bit 14 Direction Clear */
#define BITP_PORTA_DIR_CLR_PX13              13            /*  Port x Bit 13 Direction Clear */
#define BITP_PORTA_DIR_CLR_PX12              12            /*  Port x Bit 12 Direction Clear */
#define BITP_PORTA_DIR_CLR_PX11              11            /*  Port x Bit 11 Direction Clear */
#define BITP_PORTA_DIR_CLR_PX10              10            /*  Port x Bit 10 Direction Clear */
#define BITP_PORTA_DIR_CLR_PX9                9            /*  Port x Bit 9 Direction Clear */
#define BITP_PORTA_DIR_CLR_PX8                8            /*  Port x Bit 8 Direction Clear */
#define BITP_PORTA_DIR_CLR_PX7                7            /*  Port x Bit 7 Direction Clear */
#define BITP_PORTA_DIR_CLR_PX6                6            /*  Port x Bit 6 Direction Clear */
#define BITP_PORTA_DIR_CLR_PX5                5            /*  Port x Bit 5 Direction Clear */
#define BITP_PORTA_DIR_CLR_PX4                4            /*  Port x Bit 4 Direction Clear */
#define BITP_PORTA_DIR_CLR_PX3                3            /*  Port x Bit 3 Direction Clear */
#define BITP_PORTA_DIR_CLR_PX2                2            /*  Port x Bit 2 Direction Clear */
#define BITP_PORTA_DIR_CLR_PX1                1            /*  Port x Bit 1 Direction Clear */
#define BITP_PORTA_DIR_CLR_PX0                0            /*  Port x Bit 0 Direction Clear */
#define BITM_PORTA_DIR_CLR_PX15              0x00008000    /*  Port x Bit 15 Direction Clear */
#define BITM_PORTA_DIR_CLR_PX14              0x00004000    /*  Port x Bit 14 Direction Clear */
#define BITM_PORTA_DIR_CLR_PX13              0x00002000    /*  Port x Bit 13 Direction Clear */
#define BITM_PORTA_DIR_CLR_PX12              0x00001000    /*  Port x Bit 12 Direction Clear */
#define BITM_PORTA_DIR_CLR_PX11              0x00000800    /*  Port x Bit 11 Direction Clear */
#define BITM_PORTA_DIR_CLR_PX10              0x00000400    /*  Port x Bit 10 Direction Clear */
#define BITM_PORTA_DIR_CLR_PX9               0x00000200    /*  Port x Bit 9 Direction Clear */
#define BITM_PORTA_DIR_CLR_PX8               0x00000100    /*  Port x Bit 8 Direction Clear */
#define BITM_PORTA_DIR_CLR_PX7               0x00000080    /*  Port x Bit 7 Direction Clear */
#define BITM_PORTA_DIR_CLR_PX6               0x00000040    /*  Port x Bit 6 Direction Clear */
#define BITM_PORTA_DIR_CLR_PX5               0x00000020    /*  Port x Bit 5 Direction Clear */
#define BITM_PORTA_DIR_CLR_PX4               0x00000010    /*  Port x Bit 4 Direction Clear */
#define BITM_PORTA_DIR_CLR_PX3               0x00000008    /*  Port x Bit 3 Direction Clear */
#define BITM_PORTA_DIR_CLR_PX2               0x00000004    /*  Port x Bit 2 Direction Clear */
#define BITM_PORTA_DIR_CLR_PX1               0x00000002    /*  Port x Bit 1 Direction Clear */
#define BITM_PORTA_DIR_CLR_PX0               0x00000001    /*  Port x Bit 0 Direction Clear */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_INEN_SET                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_INEN_SET_PX15             15            /*  Port x Bit 15 Input Enable Set */
#define BITP_PORTA_INEN_SET_PX14             14            /*  Port x Bit 14 Input Enable Set */
#define BITP_PORTA_INEN_SET_PX13             13            /*  Port x Bit 13 Input Enable Set */
#define BITP_PORTA_INEN_SET_PX12             12            /*  Port x Bit 12 Input Enable Set */
#define BITP_PORTA_INEN_SET_PX11             11            /*  Port x Bit 11 Input Enable Set */
#define BITP_PORTA_INEN_SET_PX10             10            /*  Port x Bit 10 Input Enable Set */
#define BITP_PORTA_INEN_SET_PX9               9            /*  Port x Bit 9 Input Enable Set */
#define BITP_PORTA_INEN_SET_PX8               8            /*  Port x Bit 8 Input Enable Set */
#define BITP_PORTA_INEN_SET_PX7               7            /*  Port x Bit 7 Input Enable Set */
#define BITP_PORTA_INEN_SET_PX6               6            /*  Port x Bit 6 Input Enable Set */
#define BITP_PORTA_INEN_SET_PX5               5            /*  Port x Bit 5 Input Enable Set */
#define BITP_PORTA_INEN_SET_PX4               4            /*  Port x Bit 4 Input Enable Set */
#define BITP_PORTA_INEN_SET_PX3               3            /*  Port x Bit 3 Input Enable Set */
#define BITP_PORTA_INEN_SET_PX2               2            /*  Port x Bit 2 Input Enable Set */
#define BITP_PORTA_INEN_SET_PX1               1            /*  Port x Bit 1 Input Enable Set */
#define BITP_PORTA_INEN_SET_PX0               0            /*  Port x Bit 0 Input Enable Set */
#define BITM_PORTA_INEN_SET_PX15             0x00008000    /*  Port x Bit 15 Input Enable Set */
#define BITM_PORTA_INEN_SET_PX14             0x00004000    /*  Port x Bit 14 Input Enable Set */
#define BITM_PORTA_INEN_SET_PX13             0x00002000    /*  Port x Bit 13 Input Enable Set */
#define BITM_PORTA_INEN_SET_PX12             0x00001000    /*  Port x Bit 12 Input Enable Set */
#define BITM_PORTA_INEN_SET_PX11             0x00000800    /*  Port x Bit 11 Input Enable Set */
#define BITM_PORTA_INEN_SET_PX10             0x00000400    /*  Port x Bit 10 Input Enable Set */
#define BITM_PORTA_INEN_SET_PX9              0x00000200    /*  Port x Bit 9 Input Enable Set */
#define BITM_PORTA_INEN_SET_PX8              0x00000100    /*  Port x Bit 8 Input Enable Set */
#define BITM_PORTA_INEN_SET_PX7              0x00000080    /*  Port x Bit 7 Input Enable Set */
#define BITM_PORTA_INEN_SET_PX6              0x00000040    /*  Port x Bit 6 Input Enable Set */
#define BITM_PORTA_INEN_SET_PX5              0x00000020    /*  Port x Bit 5 Input Enable Set */
#define BITM_PORTA_INEN_SET_PX4              0x00000010    /*  Port x Bit 4 Input Enable Set */
#define BITM_PORTA_INEN_SET_PX3              0x00000008    /*  Port x Bit 3 Input Enable Set */
#define BITM_PORTA_INEN_SET_PX2              0x00000004    /*  Port x Bit 2 Input Enable Set */
#define BITM_PORTA_INEN_SET_PX1              0x00000002    /*  Port x Bit 1 Input Enable Set */
#define BITM_PORTA_INEN_SET_PX0              0x00000001    /*  Port x Bit 0 Input Enable Set */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_INEN_CLR                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_INEN_CLR_PX15             15            /*  Port x Bit 15 Input Enable Clear */
#define BITP_PORTA_INEN_CLR_PX14             14            /*  Port x Bit 14 Input Enable Clear */
#define BITP_PORTA_INEN_CLR_PX13             13            /*  Port x Bit 13 Input Enable Clear */
#define BITP_PORTA_INEN_CLR_PX12             12            /*  Port x Bit 12 Input Enable Clear */
#define BITP_PORTA_INEN_CLR_PX11             11            /*  Port x Bit 11 Input Enable Clear */
#define BITP_PORTA_INEN_CLR_PX10             10            /*  Port x Bit 10 Input Enable Clear */
#define BITP_PORTA_INEN_CLR_PX9               9            /*  Port x Bit 9 Input Enable Clear */
#define BITP_PORTA_INEN_CLR_PX8               8            /*  Port x Bit 8 Input Enable Clear */
#define BITP_PORTA_INEN_CLR_PX7               7            /*  Port x Bit 7 Input Enable Clear */
#define BITP_PORTA_INEN_CLR_PX6               6            /*  Port x Bit 6 Input Enable Clear */
#define BITP_PORTA_INEN_CLR_PX5               5            /*  Port x Bit 5 Input Enable Clear */
#define BITP_PORTA_INEN_CLR_PX4               4            /*  Port x Bit 4 Input Enable Clear */
#define BITP_PORTA_INEN_CLR_PX3               3            /*  Port x Bit 3 Input Enable Clear */
#define BITP_PORTA_INEN_CLR_PX2               2            /*  Port x Bit 2 Input Enable Clear */
#define BITP_PORTA_INEN_CLR_PX1               1            /*  Port x Bit 1 Input Enable Clear */
#define BITP_PORTA_INEN_CLR_PX0               0            /*  Port x Bit 0 Input Enable Clear */
#define BITM_PORTA_INEN_CLR_PX15             0x00008000    /*  Port x Bit 15 Input Enable Clear */
#define BITM_PORTA_INEN_CLR_PX14             0x00004000    /*  Port x Bit 14 Input Enable Clear */
#define BITM_PORTA_INEN_CLR_PX13             0x00002000    /*  Port x Bit 13 Input Enable Clear */
#define BITM_PORTA_INEN_CLR_PX12             0x00001000    /*  Port x Bit 12 Input Enable Clear */
#define BITM_PORTA_INEN_CLR_PX11             0x00000800    /*  Port x Bit 11 Input Enable Clear */
#define BITM_PORTA_INEN_CLR_PX10             0x00000400    /*  Port x Bit 10 Input Enable Clear */
#define BITM_PORTA_INEN_CLR_PX9              0x00000200    /*  Port x Bit 9 Input Enable Clear */
#define BITM_PORTA_INEN_CLR_PX8              0x00000100    /*  Port x Bit 8 Input Enable Clear */
#define BITM_PORTA_INEN_CLR_PX7              0x00000080    /*  Port x Bit 7 Input Enable Clear */
#define BITM_PORTA_INEN_CLR_PX6              0x00000040    /*  Port x Bit 6 Input Enable Clear */
#define BITM_PORTA_INEN_CLR_PX5              0x00000020    /*  Port x Bit 5 Input Enable Clear */
#define BITM_PORTA_INEN_CLR_PX4              0x00000010    /*  Port x Bit 4 Input Enable Clear */
#define BITM_PORTA_INEN_CLR_PX3              0x00000008    /*  Port x Bit 3 Input Enable Clear */
#define BITM_PORTA_INEN_CLR_PX2              0x00000004    /*  Port x Bit 2 Input Enable Clear */
#define BITM_PORTA_INEN_CLR_PX1              0x00000002    /*  Port x Bit 1 Input Enable Clear */
#define BITM_PORTA_INEN_CLR_PX0              0x00000001    /*  Port x Bit 0 Input Enable Clear */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_POL_SET                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_POL_SET_PX15              15            /*  Port x Bit 15 Polarity Invert Set */
#define BITP_PORTA_POL_SET_PX14              14            /*  Port x Bit 14 Polarity Invert Set */
#define BITP_PORTA_POL_SET_PX13              13            /*  Port x Bit 13 Polarity Invert Set */
#define BITP_PORTA_POL_SET_PX12              12            /*  Port x Bit 12 Polarity Invert Set */
#define BITP_PORTA_POL_SET_PX11              11            /*  Port x Bit 11 Polarity Invert Set */
#define BITP_PORTA_POL_SET_PX10              10            /*  Port x Bit 10 Polarity Invert Set */
#define BITP_PORTA_POL_SET_PX9                9            /*  Port x Bit 9 Polarity Invert Set */
#define BITP_PORTA_POL_SET_PX8                8            /*  Port x Bit 8 Polarity Invert Set */
#define BITP_PORTA_POL_SET_PX7                7            /*  Port x Bit 7 Polarity Invert Set */
#define BITP_PORTA_POL_SET_PX6                6            /*  Port x Bit 6 Polarity Invert Set */
#define BITP_PORTA_POL_SET_PX5                5            /*  Port x Bit 5 Polarity Invert Set */
#define BITP_PORTA_POL_SET_PX4                4            /*  Port x Bit 4 Polarity Invert Set */
#define BITP_PORTA_POL_SET_PX3                3            /*  Port x Bit 3 Polarity Invert Set */
#define BITP_PORTA_POL_SET_PX2                2            /*  Port x Bit 2 Polarity Invert Set */
#define BITP_PORTA_POL_SET_PX1                1            /*  Port x Bit 1 Polarity Invert Set */
#define BITP_PORTA_POL_SET_PX0                0            /*  Port x Bit 0 Polarity Invert Set */
#define BITM_PORTA_POL_SET_PX15              0x00008000    /*  Port x Bit 15 Polarity Invert Set */
#define BITM_PORTA_POL_SET_PX14              0x00004000    /*  Port x Bit 14 Polarity Invert Set */
#define BITM_PORTA_POL_SET_PX13              0x00002000    /*  Port x Bit 13 Polarity Invert Set */
#define BITM_PORTA_POL_SET_PX12              0x00001000    /*  Port x Bit 12 Polarity Invert Set */
#define BITM_PORTA_POL_SET_PX11              0x00000800    /*  Port x Bit 11 Polarity Invert Set */
#define BITM_PORTA_POL_SET_PX10              0x00000400    /*  Port x Bit 10 Polarity Invert Set */
#define BITM_PORTA_POL_SET_PX9               0x00000200    /*  Port x Bit 9 Polarity Invert Set */
#define BITM_PORTA_POL_SET_PX8               0x00000100    /*  Port x Bit 8 Polarity Invert Set */
#define BITM_PORTA_POL_SET_PX7               0x00000080    /*  Port x Bit 7 Polarity Invert Set */
#define BITM_PORTA_POL_SET_PX6               0x00000040    /*  Port x Bit 6 Polarity Invert Set */
#define BITM_PORTA_POL_SET_PX5               0x00000020    /*  Port x Bit 5 Polarity Invert Set */
#define BITM_PORTA_POL_SET_PX4               0x00000010    /*  Port x Bit 4 Polarity Invert Set */
#define BITM_PORTA_POL_SET_PX3               0x00000008    /*  Port x Bit 3 Polarity Invert Set */
#define BITM_PORTA_POL_SET_PX2               0x00000004    /*  Port x Bit 2 Polarity Invert Set */
#define BITM_PORTA_POL_SET_PX1               0x00000002    /*  Port x Bit 1 Polarity Invert Set */
#define BITM_PORTA_POL_SET_PX0               0x00000001    /*  Port x Bit 0 Polarity Invert Set */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTA_POL_CLR                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTA_POL_CLR_PX15              15            /*  Port x Bit 15 Polarity Invert Clear */
#define BITP_PORTA_POL_CLR_PX14              14            /*  Port x Bit 14 Polarity Invert Clear */
#define BITP_PORTA_POL_CLR_PX13              13            /*  Port x Bit 13 Polarity Invert Clear */
#define BITP_PORTA_POL_CLR_PX12              12            /*  Port x Bit 12 Polarity Invert Clear */
#define BITP_PORTA_POL_CLR_PX11              11            /*  Port x Bit 11 Polarity Invert Clear */
#define BITP_PORTA_POL_CLR_PX10              10            /*  Port x Bit 10 Polarity Invert Clear */
#define BITP_PORTA_POL_CLR_PX9                9            /*  Port x Bit 9 Polarity Invert Clear */
#define BITP_PORTA_POL_CLR_PX8                8            /*  Port x Bit 8 Polarity Invert Clear */
#define BITP_PORTA_POL_CLR_PX7                7            /*  Port x Bit 7 Polarity Invert Clear */
#define BITP_PORTA_POL_CLR_PX6                6            /*  Port x Bit 6 Polarity Invert Clear */
#define BITP_PORTA_POL_CLR_PX5                5            /*  Port x Bit 5 Polarity Invert Clear */
#define BITP_PORTA_POL_CLR_PX4                4            /*  Port x Bit 4 Polarity Invert Clear */
#define BITP_PORTA_POL_CLR_PX3                3            /*  Port x Bit 3 Polarity Invert Clear */
#define BITP_PORTA_POL_CLR_PX2                2            /*  Port x Bit 2 Polarity Invert Clear */
#define BITP_PORTA_POL_CLR_PX1                1            /*  Port x Bit 1 Polarity Invert Clear */
#define BITP_PORTA_POL_CLR_PX0                0            /*  Port x Bit 0 Polarity Invert Clear */
#define BITM_PORTA_POL_CLR_PX15              0x00008000    /*  Port x Bit 15 Polarity Invert Clear */
#define BITM_PORTA_POL_CLR_PX14              0x00004000    /*  Port x Bit 14 Polarity Invert Clear */
#define BITM_PORTA_POL_CLR_PX13              0x00002000    /*  Port x Bit 13 Polarity Invert Clear */
#define BITM_PORTA_POL_CLR_PX12              0x00001000    /*  Port x Bit 12 Polarity Invert Clear */
#define BITM_PORTA_POL_CLR_PX11              0x00000800    /*  Port x Bit 11 Polarity Invert Clear */
#define BITM_PORTA_POL_CLR_PX10              0x00000400    /*  Port x Bit 10 Polarity Invert Clear */
#define BITM_PORTA_POL_CLR_PX9               0x00000200    /*  Port x Bit 9 Polarity Invert Clear */
#define BITM_PORTA_POL_CLR_PX8               0x00000100    /*  Port x Bit 8 Polarity Invert Clear */
#define BITM_PORTA_POL_CLR_PX7               0x00000080    /*  Port x Bit 7 Polarity Invert Clear */
#define BITM_PORTA_POL_CLR_PX6               0x00000040    /*  Port x Bit 6 Polarity Invert Clear */
#define BITM_PORTA_POL_CLR_PX5               0x00000020    /*  Port x Bit 5 Polarity Invert Clear */
#define BITM_PORTA_POL_CLR_PX4               0x00000010    /*  Port x Bit 4 Polarity Invert Clear */
#define BITM_PORTA_POL_CLR_PX3               0x00000008    /*  Port x Bit 3 Polarity Invert Clear */
#define BITM_PORTA_POL_CLR_PX2               0x00000004    /*  Port x Bit 2 Polarity Invert Clear */
#define BITM_PORTA_POL_CLR_PX1               0x00000002    /*  Port x Bit 1 Polarity Invert Clear */
#define BITM_PORTA_POL_CLR_PX0               0x00000001    /*  Port x Bit 0 Polarity Invert Clear */


/* ============================================================================================================================
        The General-Purpose Input/Output Port
   ============================================================================================================================ */

/* ============================================================================================================================
        PORTB
   ============================================================================================================================ */
#define REG_PORTB_ST_EN_RESET                0x00000000            /*      Reset Value for ST_EN  */
#define REG_PORTB_ST_EN                      0xF0002100            /*  PORTB GPIO Schmitt Trigger Enable */
#define REG_PORTB_SLRATE_SEL_RESET           0x00000000            /*      Reset Value for SLRATE_SEL  */
#define REG_PORTB_SLRATE_SEL                 0xF0002104            /*  PORTB GPIO Slew rate control enable */
#define REG_PORTB_DS_SEL_L_RESET             0x00924924            /*      Reset Value for DS_SEL_L  */
#define REG_PORTB_DS_SEL_L                   0xF0002108            /*  PORTB GPIO Drive strength - pads 7:0 */
#define REG_PORTB_DS_SEL_H_RESET             0x00924924            /*      Reset Value for DS_SEL_H  */
#define REG_PORTB_DS_SEL_H                   0xF000210C            /*  PORTB GPIO Drive strength - pads 15:8 */
#define REG_PORTB_PU_SEL_RESET               0x00000002            /*      Reset Value for PU_SEL  */
#define REG_PORTB_PU_SEL                     0xF0002110            /*  PORTB GPIO Pull up select */
#define REG_PORTB_PD_SEL_RESET               0x00000000            /*      Reset Value for PD_SEL  */
#define REG_PORTB_PD_SEL                     0xF0002114            /*  PORTB GPIO Pull down select */

/* ============================================================================================================================
        PORTB Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          PORTB_ST_EN                          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTB_ST_EN_ST15                15            /*  Schmidt Trigger Pin F */
#define BITP_PORTB_ST_EN_ST14                14            /*  Schmidt Trigger Pin E */
#define BITP_PORTB_ST_EN_ST13                13            /*  Schmidt Trigger Pin D */
#define BITP_PORTB_ST_EN_ST12                12            /*  Schmidt Trigger Pin C */
#define BITP_PORTB_ST_EN_ST11                11            /*  Schmidt Trigger Pin B */
#define BITP_PORTB_ST_EN_ST10                10            /*  Schmidt Trigger Pin A */
#define BITP_PORTB_ST_EN_ST9                  9            /*  Schmidt Trigger Pin 9 */
#define BITP_PORTB_ST_EN_ST8                  8            /*  Schmidt Trigger Pin 8 */
#define BITP_PORTB_ST_EN_ST7                  7            /*  Schmidt Trigger Pin 7 */
#define BITP_PORTB_ST_EN_ST6                  6            /*  Schmidt Trigger Pin 6 */
#define BITP_PORTB_ST_EN_ST5                  5            /*  Schmidt Trigger Pin 5 */
#define BITP_PORTB_ST_EN_ST4                  4            /*  Schmidt Trigger Pin 4 */
#define BITP_PORTB_ST_EN_ST3                  3            /*  Schmidt Trigger Pin 3 */
#define BITP_PORTB_ST_EN_ST2                  2            /*  Schmidt Trigger Pin 2 */
#define BITP_PORTB_ST_EN_ST1                  1            /*  Schmidt Trigger TMS */
#define BITP_PORTB_ST_EN_ST0                  0            /*  Schmidt Trigger CLKHOST */
#define BITM_PORTB_ST_EN_ST15                0x00008000    /*  Schmidt Trigger Pin F */
#define BITM_PORTB_ST_EN_ST14                0x00004000    /*  Schmidt Trigger Pin E */
#define BITM_PORTB_ST_EN_ST13                0x00002000    /*  Schmidt Trigger Pin D */
#define BITM_PORTB_ST_EN_ST12                0x00001000    /*  Schmidt Trigger Pin C */
#define BITM_PORTB_ST_EN_ST11                0x00000800    /*  Schmidt Trigger Pin B */
#define BITM_PORTB_ST_EN_ST10                0x00000400    /*  Schmidt Trigger Pin A */
#define BITM_PORTB_ST_EN_ST9                 0x00000200    /*  Schmidt Trigger Pin 9 */
#define BITM_PORTB_ST_EN_ST8                 0x00000100    /*  Schmidt Trigger Pin 8 */
#define BITM_PORTB_ST_EN_ST7                 0x00000080    /*  Schmidt Trigger Pin 7 */
#define BITM_PORTB_ST_EN_ST6                 0x00000040    /*  Schmidt Trigger Pin 6 */
#define BITM_PORTB_ST_EN_ST5                 0x00000020    /*  Schmidt Trigger Pin 5 */
#define BITM_PORTB_ST_EN_ST4                 0x00000010    /*  Schmidt Trigger Pin 4 */
#define BITM_PORTB_ST_EN_ST3                 0x00000008    /*  Schmidt Trigger Pin 3 */
#define BITM_PORTB_ST_EN_ST2                 0x00000004    /*  Schmidt Trigger Pin 2 */
#define BITM_PORTB_ST_EN_ST1                 0x00000002    /*  Schmidt Trigger TMS */
#define BITM_PORTB_ST_EN_ST0                 0x00000001    /*  Schmidt Trigger CLKHOST */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTB_SLRATE_SEL                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTB_SLRATE_SEL_SL15           15            /*  Slew rate control for pinF */
#define BITP_PORTB_SLRATE_SEL_SL14           14            /*  Slew rate control for pinE */
#define BITP_PORTB_SLRATE_SEL_SL13           13            /*  Slew rate control for pinD */
#define BITP_PORTB_SLRATE_SEL_SL12           12            /*  Slew rate control for pinC */
#define BITP_PORTB_SLRATE_SEL_SL11           11            /*  Slew rate control for pinB */
#define BITP_PORTB_SLRATE_SEL_SL10           10            /*  Slew rate control for pinA */
#define BITP_PORTB_SLRATE_SEL_SL9             9            /*  Slew rate control for pin9 */
#define BITP_PORTB_SLRATE_SEL_SL8             8            /*  Slew rate control for pin8 */
#define BITP_PORTB_SLRATE_SEL_SL7             7            /*  Slew rate control for pin7 */
#define BITP_PORTB_SLRATE_SEL_SL6             6            /*  Slew rate control for pin6 */
#define BITP_PORTB_SLRATE_SEL_SL5             5            /*  Slew rate control for pin5 */
#define BITP_PORTB_SLRATE_SEL_SL4             4            /*  Slew rate control for pin4 */
#define BITP_PORTB_SLRATE_SEL_SL3             3            /*  Slew rate control for pin3 */
#define BITP_PORTB_SLRATE_SEL_SL2             2            /*  Slew rate control for pin2 */
#define BITP_PORTB_SLRATE_SEL_SL1             1            /*  Slew Rate Control TMS */
#define BITP_PORTB_SLRATE_SEL_SL0             0            /*  Slew Rate Control CLKHOST */
#define BITM_PORTB_SLRATE_SEL_SL15           0x00008000    /*  Slew rate control for pinF */
#define BITM_PORTB_SLRATE_SEL_SL14           0x00004000    /*  Slew rate control for pinE */
#define BITM_PORTB_SLRATE_SEL_SL13           0x00002000    /*  Slew rate control for pinD */
#define BITM_PORTB_SLRATE_SEL_SL12           0x00001000    /*  Slew rate control for pinC */
#define BITM_PORTB_SLRATE_SEL_SL11           0x00000800    /*  Slew rate control for pinB */
#define BITM_PORTB_SLRATE_SEL_SL10           0x00000400    /*  Slew rate control for pinA */
#define BITM_PORTB_SLRATE_SEL_SL9            0x00000200    /*  Slew rate control for pin9 */
#define BITM_PORTB_SLRATE_SEL_SL8            0x00000100    /*  Slew rate control for pin8 */
#define BITM_PORTB_SLRATE_SEL_SL7            0x00000080    /*  Slew rate control for pin7 */
#define BITM_PORTB_SLRATE_SEL_SL6            0x00000040    /*  Slew rate control for pin6 */
#define BITM_PORTB_SLRATE_SEL_SL5            0x00000020    /*  Slew rate control for pin5 */
#define BITM_PORTB_SLRATE_SEL_SL4            0x00000010    /*  Slew rate control for pin4 */
#define BITM_PORTB_SLRATE_SEL_SL3            0x00000008    /*  Slew rate control for pin3 */
#define BITM_PORTB_SLRATE_SEL_SL2            0x00000004    /*  Slew rate control for pin2 */
#define BITM_PORTB_SLRATE_SEL_SL1            0x00000002    /*  Slew Rate Control TMS */
#define BITM_PORTB_SLRATE_SEL_SL0            0x00000001    /*  Slew Rate Control CLKHOST */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTB_DS_SEL_L                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTB_DS_SEL_L_DS7              21            /*  Drive strength control for pin7 */
#define BITP_PORTB_DS_SEL_L_DS6              18            /*  Drive strength control for pin6 */
#define BITP_PORTB_DS_SEL_L_DS5              15            /*  Drive strength control for pin5 */
#define BITP_PORTB_DS_SEL_L_DS4              12            /*  Drive strength control for pin4 */
#define BITP_PORTB_DS_SEL_L_DS3               9            /*  Drive strength control for pin3 */
#define BITP_PORTB_DS_SEL_L_DS2               6            /*  Drive strength control for pin2 */
#define BITP_PORTB_DS_SEL_L_DS1               3            /*  Drive Strength Control TMS */
#define BITP_PORTB_DS_SEL_L_DS0               0            /*  Drive Strength Control CLKHOST */
#define BITM_PORTB_DS_SEL_L_DS7              0x00E00000    /*  Drive strength control for pin7 */
#define BITM_PORTB_DS_SEL_L_DS6              0x001C0000    /*  Drive strength control for pin6 */
#define BITM_PORTB_DS_SEL_L_DS5              0x00038000    /*  Drive strength control for pin5 */
#define BITM_PORTB_DS_SEL_L_DS4              0x00007000    /*  Drive strength control for pin4 */
#define BITM_PORTB_DS_SEL_L_DS3              0x00000E00    /*  Drive strength control for pin3 */
#define BITM_PORTB_DS_SEL_L_DS2              0x000001C0    /*  Drive strength control for pin2 */
#define BITM_PORTB_DS_SEL_L_DS1              0x00000038    /*  Drive Strength Control TMS */
#define BITM_PORTB_DS_SEL_L_DS0              0x00000007    /*  Drive Strength Control CLKHOST */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTB_DS_SEL_H                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTB_DS_SEL_H_DS15             21            /*  Drive strength control for pinF */
#define BITP_PORTB_DS_SEL_H_DS14             18            /*  Drive strength control for pinE */
#define BITP_PORTB_DS_SEL_H_DS13             15            /*  Drive strength control for pinD */
#define BITP_PORTB_DS_SEL_H_DS12             12            /*  Drive strength control for pinC */
#define BITP_PORTB_DS_SEL_H_DS11              9            /*  Drive strength control for pinB */
#define BITP_PORTB_DS_SEL_H_DS10              6            /*  Drive strength control for pin10 */
#define BITP_PORTB_DS_SEL_H_DS9               3            /*  Drive strength control for pin9 */
#define BITP_PORTB_DS_SEL_H_DS8               0            /*  Drive strength control for pin8 */
#define BITM_PORTB_DS_SEL_H_DS15             0x00E00000    /*  Drive strength control for pinF */
#define BITM_PORTB_DS_SEL_H_DS14             0x001C0000    /*  Drive strength control for pinE */
#define BITM_PORTB_DS_SEL_H_DS13             0x00038000    /*  Drive strength control for pinD */
#define BITM_PORTB_DS_SEL_H_DS12             0x00007000    /*  Drive strength control for pinC */
#define BITM_PORTB_DS_SEL_H_DS11             0x00000E00    /*  Drive strength control for pinB */
#define BITM_PORTB_DS_SEL_H_DS10             0x000001C0    /*  Drive strength control for pin10 */
#define BITM_PORTB_DS_SEL_H_DS9              0x00000038    /*  Drive strength control for pin9 */
#define BITM_PORTB_DS_SEL_H_DS8              0x00000007    /*  Drive strength control for pin8 */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTB_PU_SEL                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTB_PU_SEL_PU15               15            /*  Pullup control for pinF */
#define BITP_PORTB_PU_SEL_PU14               14            /*  Pullup control for pinE */
#define BITP_PORTB_PU_SEL_PU13               13            /*  Pullup control for pinD */
#define BITP_PORTB_PU_SEL_PU12               12            /*  Pullup control for pinC */
#define BITP_PORTB_PU_SEL_PU11               11            /*  Pullup control for pinB */
#define BITP_PORTB_PU_SEL_PU10               10            /*  Pullup control for pinA */
#define BITP_PORTB_PU_SEL_PU9                 9            /*  Pullup control for pin9 */
#define BITP_PORTB_PU_SEL_PU8                 8            /*  Pullup control for pin8 */
#define BITP_PORTB_PU_SEL_PU7                 7            /*  Pullup control for pin7 */
#define BITP_PORTB_PU_SEL_PU6                 6            /*  Pullup control for pin6 */
#define BITP_PORTB_PU_SEL_PU5                 5            /*  Pullup control for pin5 */
#define BITP_PORTB_PU_SEL_PU4                 4            /*  Pullup control for pin4 */
#define BITP_PORTB_PU_SEL_PU3                 3            /*  Pullup control for pin3 */
#define BITP_PORTB_PU_SEL_PU2                 2            /*  Pullup control for pin2 */
#define BITP_PORTB_PU_SEL_PU1                 1            /*  Pullup Control TMS */
#define BITP_PORTB_PU_SEL_PU0                 0            /*  Pullup Control CLKHOST */
#define BITM_PORTB_PU_SEL_PU15               0x00008000    /*  Pullup control for pinF */
#define BITM_PORTB_PU_SEL_PU14               0x00004000    /*  Pullup control for pinE */
#define BITM_PORTB_PU_SEL_PU13               0x00002000    /*  Pullup control for pinD */
#define BITM_PORTB_PU_SEL_PU12               0x00001000    /*  Pullup control for pinC */
#define BITM_PORTB_PU_SEL_PU11               0x00000800    /*  Pullup control for pinB */
#define BITM_PORTB_PU_SEL_PU10               0x00000400    /*  Pullup control for pinA */
#define BITM_PORTB_PU_SEL_PU9                0x00000200    /*  Pullup control for pin9 */
#define BITM_PORTB_PU_SEL_PU8                0x00000100    /*  Pullup control for pin8 */
#define BITM_PORTB_PU_SEL_PU7                0x00000080    /*  Pullup control for pin7 */
#define BITM_PORTB_PU_SEL_PU6                0x00000040    /*  Pullup control for pin6 */
#define BITM_PORTB_PU_SEL_PU5                0x00000020    /*  Pullup control for pin5 */
#define BITM_PORTB_PU_SEL_PU4                0x00000010    /*  Pullup control for pin4 */
#define BITM_PORTB_PU_SEL_PU3                0x00000008    /*  Pullup control for pin3 */
#define BITM_PORTB_PU_SEL_PU2                0x00000004    /*  Pullup control for pin2 */
#define BITM_PORTB_PU_SEL_PU1                0x00000002    /*  Pullup Control TMS */
#define BITM_PORTB_PU_SEL_PU0                0x00000001    /*  Pullup Control CLKHOST */

/* -------------------------------------------------------------------------------------------------------------------------
          PORTB_PD_SEL                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_PORTB_PD_SEL_PD15               15            /*  Pulldown control for pinF */
#define BITP_PORTB_PD_SEL_PD14               14            /*  Pulldown control for pinE */
#define BITP_PORTB_PD_SEL_PD13               13            /*  Pulldown control for pinD */
#define BITP_PORTB_PD_SEL_PD12               12            /*  Pulldown control for pinC */
#define BITP_PORTB_PD_SEL_PD11               11            /*  Pulldown control for pinB */
#define BITP_PORTB_PD_SEL_PD10               10            /*  Pulldown control for pinA */
#define BITP_PORTB_PD_SEL_PD9                 9            /*  Pulldown control for pin9 */
#define BITP_PORTB_PD_SEL_PD8                 8            /*  Pulldown control for pin8 */
#define BITP_PORTB_PD_SEL_PD7                 7            /*  Pulldown control for pin7 */
#define BITP_PORTB_PD_SEL_PD6                 6            /*  Pulldown control for pin6 */
#define BITP_PORTB_PD_SEL_PD5                 5            /*  Pulldown control for pin5 */
#define BITP_PORTB_PD_SEL_PD4                 4            /*  Pulldown control for pin4 */
#define BITP_PORTB_PD_SEL_PD3                 3            /*  Pulldown control for pin3 */
#define BITP_PORTB_PD_SEL_PD2                 2            /*  Pulldown control for pin2 */
#define BITP_PORTB_PD_SEL_PD1                 1            /*  Pulldown Control for TMS */
#define BITP_PORTB_PD_SEL_PD0                 0            /*  Pulldown Control for CLKHOST */
#define BITM_PORTB_PD_SEL_PD15               0x00008000    /*  Pulldown control for pinF */
#define BITM_PORTB_PD_SEL_PD14               0x00004000    /*  Pulldown control for pinE */
#define BITM_PORTB_PD_SEL_PD13               0x00002000    /*  Pulldown control for pinD */
#define BITM_PORTB_PD_SEL_PD12               0x00001000    /*  Pulldown control for pinC */
#define BITM_PORTB_PD_SEL_PD11               0x00000800    /*  Pulldown control for pinB */
#define BITM_PORTB_PD_SEL_PD10               0x00000400    /*  Pulldown control for pinA */
#define BITM_PORTB_PD_SEL_PD9                0x00000200    /*  Pulldown control for pin9 */
#define BITM_PORTB_PD_SEL_PD8                0x00000100    /*  Pulldown control for pin8 */
#define BITM_PORTB_PD_SEL_PD7                0x00000080    /*  Pulldown control for pin7 */
#define BITM_PORTB_PD_SEL_PD6                0x00000040    /*  Pulldown control for pin6 */
#define BITM_PORTB_PD_SEL_PD5                0x00000020    /*  Pulldown control for pin5 */
#define BITM_PORTB_PD_SEL_PD4                0x00000010    /*  Pulldown control for pin4 */
#define BITM_PORTB_PD_SEL_PD3                0x00000008    /*  Pulldown control for pin3 */
#define BITM_PORTB_PD_SEL_PD2                0x00000004    /*  Pulldown control for pin2 */
#define BITM_PORTB_PD_SEL_PD1                0x00000002    /*  Pulldown Control for TMS */
#define BITM_PORTB_PD_SEL_PD0                0x00000001    /*  Pulldown Control for CLKHOST */


/* ============================================================================================================================
        digiMMIC MIPI External Interface Bridge Register Map
   ============================================================================================================================ */

/* ============================================================================================================================
        MIPI
   ============================================================================================================================ */
#define REG_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_RESET 0x00000000            /*      Reset Value for CSI2_FRAME_START_DATA_ID_WC_REG  */
#define REG_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG 0xF0004000            /*  MIPI Frame Start Packet Data ID and Word Count Register */
#define REG_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_RESET 0x00000000            /*      Reset Value for CSI2_DATA_FRAME_DATA_ID_WC_REG  */
#define REG_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG 0xF0004004            /*  MIPI Data Packet Data Format and Word Count Register */
#define REG_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_RESET 0x00000001            /*      Reset Value for CSI2_FRAME_END_DATA_ID_WC_REG  */
#define REG_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG 0xF0004008            /*  MIPI Frame End Packet Data ID and Word Count Register */
#define REG_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_RESET 0x00000002            /*      Reset Value for CSI2_LINE_START_DATA_ID_WC_REG  */
#define REG_MIPI_CSI2_LINE_START_DATA_ID_WC_REG 0xF000400C            /*  MIPI Line Start Packet Data ID and Word Count Register */
#define REG_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_RESET 0x00000003            /*      Reset Value for CSI2_LINE_END_DATA_ID_WC_REG  */
#define REG_MIPI_CSI2_LINE_END_DATA_ID_WC_REG 0xF0004010            /*  MIPI Line End Packet Data ID and Word Count Register */
#define REG_MIPI_CSI2_PKT_CTL_REG_RESET      0x00000000            /*      Reset Value for CSI2_PKT_CTL_REG  */
#define REG_MIPI_CSI2_PKT_CTL_REG            0xF0004014            /*  MIPI Packet Control Register */
#define REG_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_RESET 0x00000000            /*      Reset Value for CSI2_DATA_FRAME_FIELD_CTL_REG  */
#define REG_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG 0xF0004018            /*  MIPI Data Packet Field Control Register */
#define REG_MIPI_CSI2_DMA_DATA_CNT_REG_RESET 0x00000000            /*      Reset Value for CSI2_DMA_DATA_CNT_REG  */
#define REG_MIPI_CSI2_DMA_DATA_CNT_REG       0xF000401C            /*  MIPI DMA Field Data Count Value in Bytes */
#define REG_MIPI_CSI2_IRQ_EN_REG_RESET       0x00000000            /*      Reset Value for CSI2_IRQ_EN_REG  */
#define REG_MIPI_CSI2_IRQ_EN_REG             0xF0004020            /*  MIPI Interrupt Enable Register for Status bits in Status Register */
#define REG_MIPI_CSI2_FAULT_EN_REG_RESET     0x1F800000            /*      Reset Value for CSI2_FAULT_EN_REG  */
#define REG_MIPI_CSI2_FAULT_EN_REG           0xF0004024            /*  MIPI Fault Enable Register for Status bits in Status Register */
#define REG_MIPI_DPHY_ESC_MODE_DATA_REG_RESET 0x00000000            /*      Reset Value for DPHY_ESC_MODE_DATA_REG  */
#define REG_MIPI_DPHY_ESC_MODE_DATA_REG      0xF0004028            /*  MIPI DPHY Escape Mode Data Register */
#define REG_MIPI_DPHY_TEST_MODE_CTRL_REG_RESET 0x00001000            /*      Reset Value for DPHY_TEST_MODE_CTRL_REG  */
#define REG_MIPI_DPHY_TEST_MODE_CTRL_REG     0xF000402C            /*  MIPI DPHY Test Mode Control Register */
#define REG_MIPI_CSI2_STAT_REG_RESET         0x00000000            /*      Reset Value for CSI2_STAT_REG  */
#define REG_MIPI_CSI2_STAT_REG               0xF0004030            /*  MIPI Status Register */
#define REG_MIPI_CSI2_ECC_SB_ERROR_REG_RESET 0x00000000            /*      Reset Value for CSI2_ECC_SB_ERROR_REG  */
#define REG_MIPI_CSI2_ECC_SB_ERROR_REG       0xF0004034            /*  MIPI Single Bit Error Status Register */
#define REG_MIPI_CSI2_ECC_DB_ERROR_REG_RESET 0x00000000            /*      Reset Value for CSI2_ECC_DB_ERROR_REG  */
#define REG_MIPI_CSI2_ECC_DB_ERROR_REG       0xF0004038            /*  MIPI Double Bit Error Status Register */
#define REG_MIPI_CSI2_BUFFER_ADDR_RESET      0x00000000            /*      Reset Value for CSI2_BUFFER_ADDR  */
#define REG_MIPI_CSI2_BUFFER_ADDR            0xF000403C            /*  MIPI CSI2 Controller Buffer Address */
#define REG_MIPI_CSI2_RUN_CTL_REG_RESET      0x00000000            /*      Reset Value for CSI2_RUN_CTL_REG  */
#define REG_MIPI_CSI2_RUN_CTL_REG            0xF0004040            /*  MIPI CSI2 Run Control Register */
#define REG_MIPI_DPHY_TEST_MODE_STAT_REG_RESET 0x00000000            /*      Reset Value for DPHY_TEST_MODE_STAT_REG  */
#define REG_MIPI_DPHY_TEST_MODE_STAT_REG     0xF0004044            /*  MIPI DPHY Test Mode Status Register */

/* ============================================================================================================================
        MIPI Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_CSI2_FRAME_START_DATA_ID_WC_REG Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_WC  8            /*  Frame Start Packet Word Count Value */
#define BITP_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_VC_ID  6            /*  Frame Start Packet Virtual Channel Identifier */
#define BITP_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_DATA_TYPE  0            /*  Frame Start Packet Data Type */
#define BITM_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_WC 0x00FFFF00    /*  Frame Start Packet Word Count Value */
#define BITM_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_VC_ID 0x000000C0    /*  Frame Start Packet Virtual Channel Identifier */
#define BITM_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_DATA_TYPE 0x0000003F    /*  Frame Start Packet Data Type */
#define ENUM_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FR_START 0x00000000            /*  frame_start_pkt_data_type: Frame Start Code */
#define ENUM_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FR_END 0x00000001            /*  frame_start_pkt_data_type: Frame End Code */
#define ENUM_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_LINE_START 0x00000002            /*  frame_start_pkt_data_type: Line Start Code */
#define ENUM_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_LINE_END 0x00000003            /*  frame_start_pkt_data_type: Line End Code */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_WC  8            /*  Data Packet Word Count Value */
#define BITP_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_VC_ID  6            /*  Data Packet Virtual Channel Identifier */
#define BITP_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_DATA_TYPE  0            /*  CSI2 Data Packet Data Type */
#define BITM_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_WC 0x00FFFF00    /*  Data Packet Word Count Value */
#define BITM_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_VC_ID 0x000000C0    /*  Data Packet Virtual Channel Identifier */
#define BITM_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_DATA_TYPE 0x0000003F    /*  CSI2 Data Packet Data Type */
#define ENUM_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_YUV422 0x0000001E            /*  data_pkt_data_type: Data Type Code for YUV422 */
#define ENUM_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_RGB444 0x00000020            /*  data_pkt_data_type: Data Type Code for RGB444 */
#define ENUM_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_RGB555 0x00000021            /*  data_pkt_data_type: Data Type Code for RGB555 */
#define ENUM_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_RGB565 0x00000022            /*  data_pkt_data_type: Data Type Code for RGB565 */
#define ENUM_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_RAW6 0x00000028            /*  data_pkt_data_type: Data Type Code for RAW6 */
#define ENUM_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_RAW7 0x00000029            /*  data_pkt_data_type: Data Type Code for RAW7 */
#define ENUM_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_RAW8 0x0000002A            /*  data_pkt_data_type: Data Type Code for RAW8 */
#define ENUM_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_RAW12 0x0000002C            /*  data_pkt_data_type: Data Type Code for RAW12 */
#define ENUM_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_RAW14 0x0000002D            /*  data_pkt_data_type: Data Type Code for RAW14 */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_CSI2_FRAME_END_DATA_ID_WC_REG   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_WC  8            /*  Frame End Packet Word Count Value */
#define BITP_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_VC_ID  6            /*  Frame End Packet Virtual Channel Identifier */
#define BITP_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_DATA_TYPE  0            /*  Frame End Packet Data Type */
#define BITM_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_WC 0x00FFFF00    /*  Frame End Packet Word Count Value */
#define BITM_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_VC_ID 0x000000C0    /*  Frame End Packet Virtual Channel Identifier */
#define BITM_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_DATA_TYPE 0x0000003F    /*  Frame End Packet Data Type */
#define ENUM_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FR_START 0x00000000            /*  frame_end_pkt_data_type: Frame Start Code */
#define ENUM_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FR_END 0x00000001            /*  frame_end_pkt_data_type: Frame End Code */
#define ENUM_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_LINE_START 0x00000002            /*  frame_end_pkt_data_type: Line Start Code */
#define ENUM_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_LINE_END 0x00000003            /*  frame_end_pkt_data_type: Line End Code */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_CSI2_LINE_START_DATA_ID_WC_REG  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_WC  8            /*  Line Start Packet Word Count Value */
#define BITP_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_VC_ID  6            /*  Line Start Packet Virtual Channel Identifier */
#define BITP_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_DATA_TYPE  0            /*  Line Start Packet Data Type */
#define BITM_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_WC 0x00FFFF00    /*  Line Start Packet Word Count Value */
#define BITM_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_VC_ID 0x000000C0    /*  Line Start Packet Virtual Channel Identifier */
#define BITM_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_DATA_TYPE 0x0000003F    /*  Line Start Packet Data Type */
#define ENUM_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_FR_START 0x00000000            /*  line_start_pkt_data_type: Frame Start Code */
#define ENUM_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_FR_END 0x00000001            /*  line_start_pkt_data_type: Frame End Code */
#define ENUM_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START 0x00000002            /*  line_start_pkt_data_type: Line Start Code */
#define ENUM_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_END 0x00000003            /*  line_start_pkt_data_type: Line End Code */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_CSI2_LINE_END_DATA_ID_WC_REG    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_WC  8            /*  Line End Packet Word Count Value */
#define BITP_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_VC_ID  6            /*  Line End Packet Virtual Channel Identifier */
#define BITP_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_DATA_TYPE  0            /*  Line End Packet Data Type */
#define BITM_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_WC 0x00FFFF00    /*  Line End Packet Word Count Value */
#define BITM_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_VC_ID 0x000000C0    /*  Line End Packet Virtual Channel Identifier */
#define BITM_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_DATA_TYPE 0x0000003F    /*  Line End Packet Data Type */
#define ENUM_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_FR_START 0x00000000            /*  line_end_pkt_data_type: Frame Start Code */
#define ENUM_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_FR_END 0x00000001            /*  line_end_pkt_data_type: Frame End Code */
#define ENUM_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_START 0x00000002            /*  line_end_pkt_data_type: Line Start Code */
#define ENUM_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END 0x00000003            /*  line_end_pkt_data_type: Line End Code */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_CSI2_PKT_CTL_REG                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_CSI2_PKT_CTL_REG_AUTO_CONFIG_LE 19            /*  Enable Auto Configuration for Line End */
#define BITP_MIPI_CSI2_PKT_CTL_REG_AUTO_CONFIG_LS 18            /*  Enable Auto Configuration for Line Start */
#define BITP_MIPI_CSI2_PKT_CTL_REG_AUTO_CONFIG_FE 17            /*  Enable Auto Configuration for Frame End */
#define BITP_MIPI_CSI2_PKT_CTL_REG_AUTO_CONFIG_FS 16            /*  Enable Auto Configuration for Frame Start */
#define BITP_MIPI_CSI2_PKT_CTL_REG_LINE_END_PKT_INACT_PH_EN 12            /*  Line End Packet Inactive Phase Enable */
#define BITP_MIPI_CSI2_PKT_CTL_REG_LINE_START_PKT_INACT_PH_EN 11            /*  Line Start Packet Inactive Phase Enable */
#define BITP_MIPI_CSI2_PKT_CTL_REG_FRAME_END_PKT_INACT_PH_EN 10            /*  Frame End Packet Inactive Phase Enable */
#define BITP_MIPI_CSI2_PKT_CTL_REG_DATA_PKT_INACT_PH_EN  9            /*  Data Packet Inactive Phase Enable */
#define BITP_MIPI_CSI2_PKT_CTL_REG_FRAME_START_PKT_INACT_PH_EN  8            /*  Frame Start Packet Inactive Phase Enable */
#define BITP_MIPI_CSI2_PKT_CTL_REG_LINE_END_PKT_ACT_PH_EN  4            /*  Line End Packet Active Phase Enable */
#define BITP_MIPI_CSI2_PKT_CTL_REG_LINE_START_PKT_ACT_PH_EN  3            /*  Line Start Packet Active Phase Enable */
#define BITP_MIPI_CSI2_PKT_CTL_REG_FRAME_END_PKT_ACT_PH_EN  2            /*  Frame End Packet Active Phase Enable */
#define BITP_MIPI_CSI2_PKT_CTL_REG_DATA_PKT_ACT_PH_EN  1            /*  Data Packet Active Phase Enable */
#define BITP_MIPI_CSI2_PKT_CTL_REG_FRAME_START_PKT_ACT_PH_EN  0            /*  Frame Start Packet Active Phase Enable */
#define BITM_MIPI_CSI2_PKT_CTL_REG_AUTO_CONFIG_LE 0x00080000    /*  Enable Auto Configuration for Line End */
#define BITM_MIPI_CSI2_PKT_CTL_REG_AUTO_CONFIG_LS 0x00040000    /*  Enable Auto Configuration for Line Start */
#define BITM_MIPI_CSI2_PKT_CTL_REG_AUTO_CONFIG_FE 0x00020000    /*  Enable Auto Configuration for Frame End */
#define BITM_MIPI_CSI2_PKT_CTL_REG_AUTO_CONFIG_FS 0x00010000    /*  Enable Auto Configuration for Frame Start */
#define BITM_MIPI_CSI2_PKT_CTL_REG_LINE_END_PKT_INACT_PH_EN 0x00001000    /*  Line End Packet Inactive Phase Enable */
#define BITM_MIPI_CSI2_PKT_CTL_REG_LINE_START_PKT_INACT_PH_EN 0x00000800    /*  Line Start Packet Inactive Phase Enable */
#define BITM_MIPI_CSI2_PKT_CTL_REG_FRAME_END_PKT_INACT_PH_EN 0x00000400    /*  Frame End Packet Inactive Phase Enable */
#define BITM_MIPI_CSI2_PKT_CTL_REG_DATA_PKT_INACT_PH_EN 0x00000200    /*  Data Packet Inactive Phase Enable */
#define BITM_MIPI_CSI2_PKT_CTL_REG_FRAME_START_PKT_INACT_PH_EN 0x00000100    /*  Frame Start Packet Inactive Phase Enable */
#define BITM_MIPI_CSI2_PKT_CTL_REG_LINE_END_PKT_ACT_PH_EN 0x00000010    /*  Line End Packet Active Phase Enable */
#define BITM_MIPI_CSI2_PKT_CTL_REG_LINE_START_PKT_ACT_PH_EN 0x00000008    /*  Line Start Packet Active Phase Enable */
#define BITM_MIPI_CSI2_PKT_CTL_REG_FRAME_END_PKT_ACT_PH_EN 0x00000004    /*  Frame End Packet Active Phase Enable */
#define BITM_MIPI_CSI2_PKT_CTL_REG_DATA_PKT_ACT_PH_EN 0x00000002    /*  Data Packet Active Phase Enable */
#define BITM_MIPI_CSI2_PKT_CTL_REG_FRAME_START_PKT_ACT_PH_EN 0x00000001    /*  Frame Start Packet Active Phase Enable */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_DPHY_READY_OVERRIDE_EN 20            /*  Start transmission by overriding DPHY ready signal */
#define BITP_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_AUTO_CONFIG_WC 19            /*  Enable auto configuration of Word Count field in Long packet */
#define BITP_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_ENDIANNESS 18            /*  Selects LS byte or MS byte first in a data unit */
#define BITP_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_BYTE_OR_SAMPLE_INTERLEAVING 17            /*  Selects byte interleaved or sample interleaved formatting */
#define BITP_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_1CH_TX_MODE_EN 16            /*  Enables Single Channel Transmission Mode */
#define BITP_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_INACT_PH_CRC32_EN 12            /*  Enables CRC32 field for inactive phase transmission */
#define BITP_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_INACT_PH_DMA_DATA_EN 11            /*  Enables DMA Data for inactive phase transmission */
#define BITP_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_INACT_PH_STATUS_EN 10            /*  Enables Status Field for inactive phase transmission */
#define BITP_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_INACT_PH_TX_EN  8            /*  Enables Inactive Phase Transmission Mode */
#define BITP_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_ACT_PH_CRC32_EN  4            /*  Enables CRC32 field for active phase transmission */
#define BITP_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_ACT_PH_DMA_DATA_EN  3            /*  Enables DMA Data for active phase transmission */
#define BITP_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_ACT_PH_STATUS_EN  2            /*  Enables Status Field for active phase transmission */
#define BITP_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_ACT_PH_RX_PAYLOAD_EN  1            /*  Enables RX Channel Data for active phase transmission */
#define BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_DPHY_READY_OVERRIDE_EN 0x00100000    /*  Start transmission by overriding DPHY ready signal */
#define BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_AUTO_CONFIG_WC 0x00080000    /*  Enable auto configuration of Word Count field in Long packet */
#define BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_ENDIANNESS 0x00040000    /*  Selects LS byte or MS byte first in a data unit */
#define BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_BYTE_OR_SAMPLE_INTERLEAVING 0x00020000    /*  Selects byte interleaved or sample interleaved formatting */
#define BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_1CH_TX_MODE_EN 0x00010000    /*  Enables Single Channel Transmission Mode */
#define BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_INACT_PH_CRC32_EN 0x00001000    /*  Enables CRC32 field for inactive phase transmission */
#define BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_INACT_PH_DMA_DATA_EN 0x00000800    /*  Enables DMA Data for inactive phase transmission */
#define BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_INACT_PH_STATUS_EN 0x00000400    /*  Enables Status Field for inactive phase transmission */
#define BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_INACT_PH_TX_EN 0x00000100    /*  Enables Inactive Phase Transmission Mode */
#define BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_ACT_PH_CRC32_EN 0x00000010    /*  Enables CRC32 field for active phase transmission */
#define BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_ACT_PH_DMA_DATA_EN 0x00000008    /*  Enables DMA Data for active phase transmission */
#define BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_ACT_PH_STATUS_EN 0x00000004    /*  Enables Status Field for active phase transmission */
#define BITM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_CSI2_ACT_PH_RX_PAYLOAD_EN 0x00000002    /*  Enables RX Channel Data for active phase transmission */
#define ENUM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_AUTO_CONFIG_WC_DISABLE 0x00000000            /*  auto_config_wc: Enable software configuration of Word Count for Long packet */
#define ENUM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_AUTO_CONFIG_WC_ENABLE 0x00080000            /*  auto_config_wc: Enable hardware configuration of Word Count for Long packet */
#define ENUM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_MS_BYTE_FIRST 0x00000000            /*  endianness: MS byte first (Big Endian) */
#define ENUM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_LS_BYTE_FIRST 0x00040000            /*  endianness: LS Byte first (Little Endian) */
#define ENUM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_SAMPLE_INTERLEAVING_SEL 0x00000000            /*  byte_or_sample_interleaving: Selects sample interleaving format */
#define ENUM_MIPI_CSI2_DATA_FRAME_FIELD_CTL_REG_BYTE_INTERLEAVING_SEL 0x00020000            /*  byte_or_sample_interleaving: Selects byte interleaving format */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_CSI2_DMA_DATA_CNT_REG           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_CSI2_DMA_DATA_CNT_REG_CSI2_DMA_TRIGGER_EVENT 16            /*  CSI2 DMA Trigger Event */
#define BITP_MIPI_CSI2_DMA_DATA_CNT_REG_CSI2_DMA_DATA_COUNT  0            /*  CSI2 DMA Data Count Value in Bytes */
#define BITM_MIPI_CSI2_DMA_DATA_CNT_REG_CSI2_DMA_TRIGGER_EVENT 0x00010000    /*  CSI2 DMA Trigger Event */
#define BITM_MIPI_CSI2_DMA_DATA_CNT_REG_CSI2_DMA_DATA_COUNT 0x0000FFFF    /*  CSI2 DMA Data Count Value in Bytes */
#define ENUM_MIPI_CSI2_DMA_DATA_CNT_REG_MIPI_RX_START 0x00000000            /*  csi2_dma_trigger_event: DMA Trigger on RX Data Start */
#define ENUM_MIPI_CSI2_DMA_DATA_CNT_REG_MIPI_RX_END 0x00010000            /*  csi2_dma_trigger_event: DMA Trigger on RX Data End */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_CSI2_IRQ_EN_REG                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_CSI2_IRQ_EN_REG_CSI2_CHIRP_IGNORED_INT_EN 28            /*  Enables interrupt for chirp ignored at CSI2 Interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_CSI2_FRAME_FIFO_OVERFLOW_INT_EN 27            /*  Enables interrupt for CSI2 data frame FIFO overflow */
#define BITP_MIPI_CSI2_IRQ_EN_REG_CSI2_FIFO_ECC_ADDR_ERR_INT_EN 26            /*  Enables interrupt for CSI2 FIFO ECC Address Error */
#define BITP_MIPI_CSI2_IRQ_EN_REG_CSI2_FIFO_ECC_MB_ERR_INT_EN 25            /*  Enables interrupt for CSI2 FIFO Multi Bit Error */
#define BITP_MIPI_CSI2_IRQ_EN_REG_CSI2_FIFO_ECC_SB_ERR_INT_EN 24            /*  Enables interrupt for CSI2 FIFO Single Bit Error */
#define BITP_MIPI_CSI2_IRQ_EN_REG_CSI2_WC_MISMATCH_INT_EN 23            /*  Enables interrupt for CSI2 Word Count Mismatch */
#define BITP_MIPI_CSI2_IRQ_EN_REG_INACT_PH_RX_INT_EN 21            /*  Enables interrupt for Inactive Phase RX Start */
#define BITP_MIPI_CSI2_IRQ_EN_REG_ACT_PH_RX_INT_EN 20            /*  Enables interrupt for Active Phase RX Start */
#define BITP_MIPI_CSI2_IRQ_EN_REG_EOT_LE_AT_DPHY_INT_EN 19            /*  Enables interrupt for EoT of Line End at DPHY interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_EOT_LS_AT_DPHY_INT_EN 18            /*  Enables interrupt for EoT of Line Start at DPHY interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_EOT_FE_AT_DPHY_INT_EN 17            /*  Enables interrupt for EoT of Frame End at DPHY interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_EOT_LP_AT_DPHY_INT_EN 16            /*  Enables interrupt for EoT of Long packet at DPHY interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_EOT_FS_AT_DPHY_INT_EN 15            /*  Enables interrupt for EoT of Frame Start at DPHY interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_SOT_LE_AT_DPHY_INT_EN 14            /*  Enables interrupt for SoT of Line End at DPHY interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_SOT_LS_AT_DPHY_INT_EN 13            /*  Enables interrupt for SoT of Line Start at DPHY interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_SOT_FE_AT_DPHY_INT_EN 12            /*  Enables interrupt for SoT of Frame End at DPHY interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_SOT_LP_AT_DPHY_INT_EN 11            /*  Enables interrupt for SoT of Long packet at DPHY interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_SOT_FS_AT_DPHY_INT_EN 10            /*  Enables interrupt for SoT of Frame Start at DPHY interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_EOT_LE_AT_CSI2_INT_EN  9            /*  Enables interrupt for EoT of Line End at CSI2 Interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_EOT_LS_AT_CSI2_INT_EN  8            /*  Enables interrupt for EoT of Line Start at CSI2 Interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_EOT_FE_AT_CSI2_INT_EN  7            /*  Enables interrupt for EoT of Frame End at CSI2 Interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_EOT_LP_AT_CSI2_INT_EN  6            /*  Enables interrupt for EoT of Long packet at CSI2 Interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_EOT_FS_AT_CSI2_INT_EN  5            /*  Enables interrupt for EoT of Frame Start at CSI2 Interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_SOT_LE_AT_CSI2_INT_EN  4            /*  Enables interrupt for SoT of Line End at CSI2 Interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_SOT_LS_AT_CSI2_INT_EN  3            /*  Enables interrupt for SoT of Line Start at CSI2 Interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_SOT_FE_AT_CSI2_INT_EN  2            /*  Enables interrupt for SoT of Frame End at CSI2 Interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_SOT_LP_AT_CSI2_INT_EN  1            /*  Enables interrupt for SoT of Long packet at CSI2 Interface */
#define BITP_MIPI_CSI2_IRQ_EN_REG_SOT_FS_AT_CSI2_INT_EN  0            /*  Enables interrupt for SoT of Frame Start at CSI2 Interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_CSI2_CHIRP_IGNORED_INT_EN 0x10000000    /*  Enables interrupt for chirp ignored at CSI2 Interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_CSI2_FRAME_FIFO_OVERFLOW_INT_EN 0x08000000    /*  Enables interrupt for CSI2 data frame FIFO overflow */
#define BITM_MIPI_CSI2_IRQ_EN_REG_CSI2_FIFO_ECC_ADDR_ERR_INT_EN 0x04000000    /*  Enables interrupt for CSI2 FIFO ECC Address Error */
#define BITM_MIPI_CSI2_IRQ_EN_REG_CSI2_FIFO_ECC_MB_ERR_INT_EN 0x02000000    /*  Enables interrupt for CSI2 FIFO Multi Bit Error */
#define BITM_MIPI_CSI2_IRQ_EN_REG_CSI2_FIFO_ECC_SB_ERR_INT_EN 0x01000000    /*  Enables interrupt for CSI2 FIFO Single Bit Error */
#define BITM_MIPI_CSI2_IRQ_EN_REG_CSI2_WC_MISMATCH_INT_EN 0x00800000    /*  Enables interrupt for CSI2 Word Count Mismatch */
#define BITM_MIPI_CSI2_IRQ_EN_REG_INACT_PH_RX_INT_EN 0x00200000    /*  Enables interrupt for Inactive Phase RX Start */
#define BITM_MIPI_CSI2_IRQ_EN_REG_ACT_PH_RX_INT_EN 0x00100000    /*  Enables interrupt for Active Phase RX Start */
#define BITM_MIPI_CSI2_IRQ_EN_REG_EOT_LE_AT_DPHY_INT_EN 0x00080000    /*  Enables interrupt for EoT of Line End at DPHY interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_EOT_LS_AT_DPHY_INT_EN 0x00040000    /*  Enables interrupt for EoT of Line Start at DPHY interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_EOT_FE_AT_DPHY_INT_EN 0x00020000    /*  Enables interrupt for EoT of Frame End at DPHY interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_EOT_LP_AT_DPHY_INT_EN 0x00010000    /*  Enables interrupt for EoT of Long packet at DPHY interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_EOT_FS_AT_DPHY_INT_EN 0x00008000    /*  Enables interrupt for EoT of Frame Start at DPHY interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_SOT_LE_AT_DPHY_INT_EN 0x00004000    /*  Enables interrupt for SoT of Line End at DPHY interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_SOT_LS_AT_DPHY_INT_EN 0x00002000    /*  Enables interrupt for SoT of Line Start at DPHY interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_SOT_FE_AT_DPHY_INT_EN 0x00001000    /*  Enables interrupt for SoT of Frame End at DPHY interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_SOT_LP_AT_DPHY_INT_EN 0x00000800    /*  Enables interrupt for SoT of Long packet at DPHY interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_SOT_FS_AT_DPHY_INT_EN 0x00000400    /*  Enables interrupt for SoT of Frame Start at DPHY interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_EOT_LE_AT_CSI2_INT_EN 0x00000200    /*  Enables interrupt for EoT of Line End at CSI2 Interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_EOT_LS_AT_CSI2_INT_EN 0x00000100    /*  Enables interrupt for EoT of Line Start at CSI2 Interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_EOT_FE_AT_CSI2_INT_EN 0x00000080    /*  Enables interrupt for EoT of Frame End at CSI2 Interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_EOT_LP_AT_CSI2_INT_EN 0x00000040    /*  Enables interrupt for EoT of Long packet at CSI2 Interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_EOT_FS_AT_CSI2_INT_EN 0x00000020    /*  Enables interrupt for EoT of Frame Start at CSI2 Interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_SOT_LE_AT_CSI2_INT_EN 0x00000010    /*  Enables interrupt for SoT of Line End at CSI2 Interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_SOT_LS_AT_CSI2_INT_EN 0x00000008    /*  Enables interrupt for SoT of Line Start at CSI2 Interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_SOT_FE_AT_CSI2_INT_EN 0x00000004    /*  Enables interrupt for SoT of Frame End at CSI2 Interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_SOT_LP_AT_CSI2_INT_EN 0x00000002    /*  Enables interrupt for SoT of Long packet at CSI2 Interface */
#define BITM_MIPI_CSI2_IRQ_EN_REG_SOT_FS_AT_CSI2_INT_EN 0x00000001    /*  Enables interrupt for SoT of Frame Start at CSI2 Interface */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_CSI2_FAULT_EN_REG               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_CSI2_FAULT_EN_REG_CSI2_CHIRP_IGNORED_FAULT_EN 28            /*  Enables fault for chirp ignored at CSI2 Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_CSI2_FRAME_FIFO_OVERFLOW_FAULT_EN 27            /*  Enables fault for CSI2 data frame FIFO overflow */
#define BITP_MIPI_CSI2_FAULT_EN_REG_CSI2_FIFO_ECC_ADDR_ERR_FAULT_EN 26            /*  Enables fault for CSI2 FIFO ECC Address Error */
#define BITP_MIPI_CSI2_FAULT_EN_REG_CSI2_FIFO_ECC_MB_ERR_FAULT_EN 25            /*  Enables fault for CSI2 FIFO Multi Bit Error */
#define BITP_MIPI_CSI2_FAULT_EN_REG_CSI2_FIFO_ECC_SB_ERR_FAULT_EN 24            /*  Enables fault for CSI2 FIFO Single Bit Error */
#define BITP_MIPI_CSI2_FAULT_EN_REG_CSI2_WC_MISMATCH_FAULT_EN 23            /*  Enables Fault for CSI2 Word Count Mismatch */
#define BITP_MIPI_CSI2_FAULT_EN_REG_INACT_PH_RX_FAULT_EN 21            /*  Enables fault for Inactive Phase RX Start */
#define BITP_MIPI_CSI2_FAULT_EN_REG_ACT_PH_RX_FAULT_EN 20            /*  Enables fault for Active Phase RX Start */
#define BITP_MIPI_CSI2_FAULT_EN_REG_EOT_LE_AT_DPHY_FAULT_EN 19            /*  Enables fault for EoT of Line End at DPHY Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_EOT_LS_AT_DPHY_FAULT_EN 18            /*  Enables fault for EoT of Line Start at DPHY Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_EOT_FE_AT_DPHY_FAULT_EN 17            /*  Enables fault for EoT of Frame End at DPHY Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_EOT_LP_AT_DPHY_FAULT_EN 16            /*  Enables fault for EoT of Long packet at DPHY Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_EOT_FS_AT_DPHY_FAULT_EN 15            /*  Enables fault for EoT of Frame Start at DPHY Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_SOT_LE_AT_DPHY_FAULT_EN 14            /*  Enables fault for SoT of Line End at DPHY Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_SOT_LS_AT_DPHY_FAULT_EN 13            /*  Enables fault for SoT of Line Start at DPHY Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_SOT_FE_AT_DPHY_FAULT_EN 12            /*  Enables fault for SoT of Frame End at DPHY Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_SOT_LP_AT_DPHY_FAULT_EN 11            /*  Enables fault for SoT of Long packet at DPHY Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_SOT_FS_AT_DPHY_FAULT_EN 10            /*  Enables fault for SoT of Frame Start at DPHY Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_EOT_LE_AT_CSI2_FAULT_EN  9            /*  Enables fault for EoT of Line End at CSI2 Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_EOT_LS_AT_CSI2_FAULT_EN  8            /*  Enables fault for EoT of Line Start at CSI2 Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_EOT_FE_AT_CSI2_FAULT_EN  7            /*  Enables fault for EoT of Frame End at CSI2 Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_EOT_LP_AT_CSI2_FAULT_EN  6            /*  Enables fault for EoT of Long packet at CSI2 Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_EOT_FS_AT_CSI2_FAULT_EN  5            /*  Enables fault for EoT of Frame Start at CSI2 Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_SOT_LE_AT_CSI2_FAULT_EN  4            /*  Enables fault for SoT of Line End at CSI2 Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_SOT_LS_AT_CSI2_FAULT_EN  3            /*  Enables fault for SoT of Line Start at CSI2 Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_SOT_FE_AT_CSI2_FAULT_EN  2            /*  Enables fault for SoT of Frame End at CSI2 Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_SOT_LP_AT_CSI2_FAULT_EN  1            /*  Enables fault for SoT of Long packet at CSI2 Interface */
#define BITP_MIPI_CSI2_FAULT_EN_REG_SOT_FS_AT_CSI2_FAULT_EN  0            /*  Enables fault for SoT of Frame Start at CSI2 Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_CSI2_CHIRP_IGNORED_FAULT_EN 0x10000000    /*  Enables fault for chirp ignored at CSI2 Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_CSI2_FRAME_FIFO_OVERFLOW_FAULT_EN 0x08000000    /*  Enables fault for CSI2 data frame FIFO overflow */
#define BITM_MIPI_CSI2_FAULT_EN_REG_CSI2_FIFO_ECC_ADDR_ERR_FAULT_EN 0x04000000    /*  Enables fault for CSI2 FIFO ECC Address Error */
#define BITM_MIPI_CSI2_FAULT_EN_REG_CSI2_FIFO_ECC_MB_ERR_FAULT_EN 0x02000000    /*  Enables fault for CSI2 FIFO Multi Bit Error */
#define BITM_MIPI_CSI2_FAULT_EN_REG_CSI2_FIFO_ECC_SB_ERR_FAULT_EN 0x01000000    /*  Enables fault for CSI2 FIFO Single Bit Error */
#define BITM_MIPI_CSI2_FAULT_EN_REG_CSI2_WC_MISMATCH_FAULT_EN 0x00800000    /*  Enables Fault for CSI2 Word Count Mismatch */
#define BITM_MIPI_CSI2_FAULT_EN_REG_INACT_PH_RX_FAULT_EN 0x00200000    /*  Enables fault for Inactive Phase RX Start */
#define BITM_MIPI_CSI2_FAULT_EN_REG_ACT_PH_RX_FAULT_EN 0x00100000    /*  Enables fault for Active Phase RX Start */
#define BITM_MIPI_CSI2_FAULT_EN_REG_EOT_LE_AT_DPHY_FAULT_EN 0x00080000    /*  Enables fault for EoT of Line End at DPHY Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_EOT_LS_AT_DPHY_FAULT_EN 0x00040000    /*  Enables fault for EoT of Line Start at DPHY Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_EOT_FE_AT_DPHY_FAULT_EN 0x00020000    /*  Enables fault for EoT of Frame End at DPHY Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_EOT_LP_AT_DPHY_FAULT_EN 0x00010000    /*  Enables fault for EoT of Long packet at DPHY Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_EOT_FS_AT_DPHY_FAULT_EN 0x00008000    /*  Enables fault for EoT of Frame Start at DPHY Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_SOT_LE_AT_DPHY_FAULT_EN 0x00004000    /*  Enables fault for SoT of Line End at DPHY Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_SOT_LS_AT_DPHY_FAULT_EN 0x00002000    /*  Enables fault for SoT of Line Start at DPHY Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_SOT_FE_AT_DPHY_FAULT_EN 0x00001000    /*  Enables fault for SoT of Frame End at DPHY Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_SOT_LP_AT_DPHY_FAULT_EN 0x00000800    /*  Enables fault for SoT of Long packet at DPHY Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_SOT_FS_AT_DPHY_FAULT_EN 0x00000400    /*  Enables fault for SoT of Frame Start at DPHY Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_EOT_LE_AT_CSI2_FAULT_EN 0x00000200    /*  Enables fault for EoT of Line End at CSI2 Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_EOT_LS_AT_CSI2_FAULT_EN 0x00000100    /*  Enables fault for EoT of Line Start at CSI2 Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_EOT_FE_AT_CSI2_FAULT_EN 0x00000080    /*  Enables fault for EoT of Frame End at CSI2 Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_EOT_LP_AT_CSI2_FAULT_EN 0x00000040    /*  Enables fault for EoT of Long packet at CSI2 Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_EOT_FS_AT_CSI2_FAULT_EN 0x00000020    /*  Enables fault for EoT of Frame Start at CSI2 Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_SOT_LE_AT_CSI2_FAULT_EN 0x00000010    /*  Enables fault for SoT of Line End at CSI2 Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_SOT_LS_AT_CSI2_FAULT_EN 0x00000008    /*  Enables fault for SoT of Line Start at CSI2 Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_SOT_FE_AT_CSI2_FAULT_EN 0x00000004    /*  Enables fault for SoT of Frame End at CSI2 Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_SOT_LP_AT_CSI2_FAULT_EN 0x00000002    /*  Enables fault for SoT of Long packet at CSI2 Interface */
#define BITM_MIPI_CSI2_FAULT_EN_REG_SOT_FS_AT_CSI2_FAULT_EN 0x00000001    /*  Enables fault for SoT of Frame Start at CSI2 Interface */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_DPHY_ESC_MODE_DATA_REG          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_DPHY_ESC_MODE_DATA_REG_DPHY_TXDATAESC_L3 24            /*  DPHY Escape Mode TX Data for Lane3 */
#define BITP_MIPI_DPHY_ESC_MODE_DATA_REG_DPHY_TXDATAESC_L2 16            /*  DPHY Escape Mode TX Data for Lane2 */
#define BITP_MIPI_DPHY_ESC_MODE_DATA_REG_DPHY_TXDATAESC_L1  8            /*  DPHY Escape Mode TX Data for Lane1 */
#define BITP_MIPI_DPHY_ESC_MODE_DATA_REG_DPHY_TXDATAESC_L0  0            /*  DPHY Escape Mode TX Data for Lane0 */
#define BITM_MIPI_DPHY_ESC_MODE_DATA_REG_DPHY_TXDATAESC_L3 0xFF000000    /*  DPHY Escape Mode TX Data for Lane3 */
#define BITM_MIPI_DPHY_ESC_MODE_DATA_REG_DPHY_TXDATAESC_L2 0x00FF0000    /*  DPHY Escape Mode TX Data for Lane2 */
#define BITM_MIPI_DPHY_ESC_MODE_DATA_REG_DPHY_TXDATAESC_L1 0x0000FF00    /*  DPHY Escape Mode TX Data for Lane1 */
#define BITM_MIPI_DPHY_ESC_MODE_DATA_REG_DPHY_TXDATAESC_L0 0x000000FF    /*  DPHY Escape Mode TX Data for Lane0 */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_DPHY_TEST_MODE_CTRL_REG         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_MASTERSLAVEZ 12            /*  DPHY Master/Slave Configuration */
#define BITP_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_TXVALIDESC_L3 11            /*  DPHY Escape Mode TX Valid for Lane3 */
#define BITP_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_TXVALIDESC_L2 10            /*  DPHY Escape Mode TX Valid for Lane2 */
#define BITP_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_TXVALIDESC_L1  9            /*  DPHY Escape Mode TX Valid for Lane1 */
#define BITP_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_TXVALIDESC_L0  8            /*  DPHY Escape Mode TX Valid for Lane0 */
#define BITP_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_TXLPDTESC_L3  7            /*  DPHY Escape Mode TX Low Power for Lane3 */
#define BITP_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_TXLPDTESC_L2  6            /*  DPHY Escape Mode TX Low Power for Lane2 */
#define BITP_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_TXLPDTESC_L1  5            /*  DPHY Escape Mode TX Low Power for Lane1 */
#define BITP_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_TXLPDTESC_L0  4            /*  DPHY Escape Mode TX Low Power for Lane0 */
#define BITP_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_BASEDIR_L3  3            /*  DPHY Base Direction for Lane3 */
#define BITP_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_BASEDIR_L2  2            /*  DPHY Base Direction for Lane2 */
#define BITP_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_BASEDIR_L1  1            /*  DPHY Base Direction for Lane1 */
#define BITP_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_BASEDIR_L0  0            /*  DPHY Base Direction for Lane0 */
#define BITM_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_MASTERSLAVEZ 0x00001000    /*  DPHY Master/Slave Configuration */
#define BITM_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_TXVALIDESC_L3 0x00000800    /*  DPHY Escape Mode TX Valid for Lane3 */
#define BITM_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_TXVALIDESC_L2 0x00000400    /*  DPHY Escape Mode TX Valid for Lane2 */
#define BITM_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_TXVALIDESC_L1 0x00000200    /*  DPHY Escape Mode TX Valid for Lane1 */
#define BITM_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_TXVALIDESC_L0 0x00000100    /*  DPHY Escape Mode TX Valid for Lane0 */
#define BITM_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_TXLPDTESC_L3 0x00000080    /*  DPHY Escape Mode TX Low Power for Lane3 */
#define BITM_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_TXLPDTESC_L2 0x00000040    /*  DPHY Escape Mode TX Low Power for Lane2 */
#define BITM_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_TXLPDTESC_L1 0x00000020    /*  DPHY Escape Mode TX Low Power for Lane1 */
#define BITM_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_TXLPDTESC_L0 0x00000010    /*  DPHY Escape Mode TX Low Power for Lane0 */
#define BITM_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_BASEDIR_L3 0x00000008    /*  DPHY Base Direction for Lane3 */
#define BITM_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_BASEDIR_L2 0x00000004    /*  DPHY Base Direction for Lane2 */
#define BITM_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_BASEDIR_L1 0x00000002    /*  DPHY Base Direction for Lane1 */
#define BITM_MIPI_DPHY_TEST_MODE_CTRL_REG_DPHY_BASEDIR_L0 0x00000001    /*  DPHY Base Direction for Lane0 */
#define ENUM_MIPI_DPHY_TEST_MODE_CTRL_REG_SLAVE 0x00000000            /*  dphy_masterslavez: Slave-side D-PHY Configuration */
#define ENUM_MIPI_DPHY_TEST_MODE_CTRL_REG_MASTER 0x00001000            /*  dphy_masterslavez: Master-side D-PHY Configuration */
#define ENUM_MIPI_DPHY_TEST_MODE_CTRL_REG_TX_L3 0x00000000            /*  dphy_basedir_l3: TX Configuration */
#define ENUM_MIPI_DPHY_TEST_MODE_CTRL_REG_RX_L3 0x00000008            /*  dphy_basedir_l3: RX Configuration */
#define ENUM_MIPI_DPHY_TEST_MODE_CTRL_REG_TX_L2 0x00000000            /*  dphy_basedir_l2: TX Configuration */
#define ENUM_MIPI_DPHY_TEST_MODE_CTRL_REG_RX_L2 0x00000004            /*  dphy_basedir_l2: RX Configuration */
#define ENUM_MIPI_DPHY_TEST_MODE_CTRL_REG_TX_L1 0x00000000            /*  dphy_basedir_l1: TX Configuration */
#define ENUM_MIPI_DPHY_TEST_MODE_CTRL_REG_RX_L1 0x00000002            /*  dphy_basedir_l1: RX Configuration */
#define ENUM_MIPI_DPHY_TEST_MODE_CTRL_REG_TX_L0 0x00000000            /*  dphy_basedir_l0: TX Configuration */
#define ENUM_MIPI_DPHY_TEST_MODE_CTRL_REG_RX_L0 0x00000001            /*  dphy_basedir_l0: RX Configuration */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_CSI2_STAT_REG                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_CSI2_STAT_REG_CSI2_CHIRP_IGNORED_STAT 28            /*  Indicates chirp ignored at CSI2 Interface */
#define BITP_MIPI_CSI2_STAT_REG_CSI2_FRAME_FIFO_OVERFLOW_STAT 27            /*  Indicates CSI2 data frame FIFO overflow */
#define BITP_MIPI_CSI2_STAT_REG_CSI2_FIFO_ECC_ADDR_ERR 26            /*  Indicates CSI2 FIFO ECC Address Error */
#define BITP_MIPI_CSI2_STAT_REG_CSI2_FIFO_ECC_MB_ERR 25            /*  Indicates CSI2 FIFO Multi Bit ECC error */
#define BITP_MIPI_CSI2_STAT_REG_CSI2_FIFO_ECC_SB_ERR 24            /*  Indicates CSI2 FIFO Single Bit ECC error */
#define BITP_MIPI_CSI2_STAT_REG_CSI2_WC_MISMATCH_STAT 23            /*  Indicates CSI2 Word Count Mismatch */
#define BITP_MIPI_CSI2_STAT_REG_DMA_ALLOWED  22            /*  DMA data over AHB interface allowed */
#define BITP_MIPI_CSI2_STAT_REG_INACT_PH_RX_STAT 21            /*  Indicates Inactive Phase RX Start */
#define BITP_MIPI_CSI2_STAT_REG_ACT_PH_RX_STAT 20            /*  Indicates Active Phase RX Start */
#define BITP_MIPI_CSI2_STAT_REG_EOT_LE_AT_DPHY_STAT 19            /*  Indicates EoT of Line End at DPHY interface */
#define BITP_MIPI_CSI2_STAT_REG_EOT_LS_AT_DPHY_STAT 18            /*  Indicates EoT of Line Start at DPHY interface */
#define BITP_MIPI_CSI2_STAT_REG_EOT_FE_AT_DPHY_STAT 17            /*  Indicates EoT of Frame End at DPHY interface */
#define BITP_MIPI_CSI2_STAT_REG_EOT_LP_AT_DPHY_STAT 16            /*  Indicates EoT of Long packet at DPHY interface */
#define BITP_MIPI_CSI2_STAT_REG_EOT_FS_AT_DPHY_STAT 15            /*  Indicates EoT of Frame Start at DPHY interface */
#define BITP_MIPI_CSI2_STAT_REG_SOT_LE_AT_DPHY_STAT 14            /*  Indicates SoT of Line End at DPHY interface */
#define BITP_MIPI_CSI2_STAT_REG_SOT_LS_AT_DPHY_STAT 13            /*  Indicates SoT of Line Start at DPHY interface */
#define BITP_MIPI_CSI2_STAT_REG_SOT_FE_AT_DPHY_STAT 12            /*  Indicates SoT of Frame End at DPHY interface */
#define BITP_MIPI_CSI2_STAT_REG_SOT_LP_AT_DPHY_STAT 11            /*  Indicates SoT of Long packet at DPHY interface */
#define BITP_MIPI_CSI2_STAT_REG_SOT_FS_AT_DPHY_STAT 10            /*  Indicates SoT of Frame Start at DPHY interface */
#define BITP_MIPI_CSI2_STAT_REG_EOT_LE_AT_CSI2_STAT  9            /*  Indicates EoT of Line End at CSI2 interface */
#define BITP_MIPI_CSI2_STAT_REG_EOT_LS_AT_CSI2_STAT  8            /*  Indicates EoT of Line Start at CSI2 interface */
#define BITP_MIPI_CSI2_STAT_REG_EOT_FE_AT_CSI2_STAT  7            /*  Indicates EoT of Frame End at CSI2 interface */
#define BITP_MIPI_CSI2_STAT_REG_EOT_LP_AT_CSI2_STAT  6            /*  Indicates EoT of Long packet at CSI2 interface */
#define BITP_MIPI_CSI2_STAT_REG_EOT_FS_AT_CSI2_STAT  5            /*  Indicates EoT of Frame Start at CSI2 interface */
#define BITP_MIPI_CSI2_STAT_REG_SOT_LE_AT_CSI2_STAT  4            /*  Indicates SoT of Line End at CSI2 interface */
#define BITP_MIPI_CSI2_STAT_REG_SOT_LS_AT_CSI2_STAT  3            /*  Indicates SoT of Line Start at CSI2 interface */
#define BITP_MIPI_CSI2_STAT_REG_SOT_FE_AT_CSI2_STAT  2            /*  Indicates SoT of Frame End at CSI2 interface */
#define BITP_MIPI_CSI2_STAT_REG_SOT_LP_AT_CSI2_STAT  1            /*  Indicates SoT of Long packet at CSI2 interface */
#define BITP_MIPI_CSI2_STAT_REG_SOT_FS_AT_CSI2_STAT  0            /*  Indicates SoT of Frame Start at CSI2 interface */
#define BITM_MIPI_CSI2_STAT_REG_CSI2_CHIRP_IGNORED_STAT 0x10000000    /*  Indicates chirp ignored at CSI2 Interface */
#define BITM_MIPI_CSI2_STAT_REG_CSI2_FRAME_FIFO_OVERFLOW_STAT 0x08000000    /*  Indicates CSI2 data frame FIFO overflow */
#define BITM_MIPI_CSI2_STAT_REG_CSI2_FIFO_ECC_ADDR_ERR 0x04000000    /*  Indicates CSI2 FIFO ECC Address Error */
#define BITM_MIPI_CSI2_STAT_REG_CSI2_FIFO_ECC_MB_ERR 0x02000000    /*  Indicates CSI2 FIFO Multi Bit ECC error */
#define BITM_MIPI_CSI2_STAT_REG_CSI2_FIFO_ECC_SB_ERR 0x01000000    /*  Indicates CSI2 FIFO Single Bit ECC error */
#define BITM_MIPI_CSI2_STAT_REG_CSI2_WC_MISMATCH_STAT 0x00800000    /*  Indicates CSI2 Word Count Mismatch */
#define BITM_MIPI_CSI2_STAT_REG_DMA_ALLOWED  0x00400000    /*  DMA data over AHB interface allowed */
#define BITM_MIPI_CSI2_STAT_REG_INACT_PH_RX_STAT 0x00200000    /*  Indicates Inactive Phase RX Start */
#define BITM_MIPI_CSI2_STAT_REG_ACT_PH_RX_STAT 0x00100000    /*  Indicates Active Phase RX Start */
#define BITM_MIPI_CSI2_STAT_REG_EOT_LE_AT_DPHY_STAT 0x00080000    /*  Indicates EoT of Line End at DPHY interface */
#define BITM_MIPI_CSI2_STAT_REG_EOT_LS_AT_DPHY_STAT 0x00040000    /*  Indicates EoT of Line Start at DPHY interface */
#define BITM_MIPI_CSI2_STAT_REG_EOT_FE_AT_DPHY_STAT 0x00020000    /*  Indicates EoT of Frame End at DPHY interface */
#define BITM_MIPI_CSI2_STAT_REG_EOT_LP_AT_DPHY_STAT 0x00010000    /*  Indicates EoT of Long packet at DPHY interface */
#define BITM_MIPI_CSI2_STAT_REG_EOT_FS_AT_DPHY_STAT 0x00008000    /*  Indicates EoT of Frame Start at DPHY interface */
#define BITM_MIPI_CSI2_STAT_REG_SOT_LE_AT_DPHY_STAT 0x00004000    /*  Indicates SoT of Line End at DPHY interface */
#define BITM_MIPI_CSI2_STAT_REG_SOT_LS_AT_DPHY_STAT 0x00002000    /*  Indicates SoT of Line Start at DPHY interface */
#define BITM_MIPI_CSI2_STAT_REG_SOT_FE_AT_DPHY_STAT 0x00001000    /*  Indicates SoT of Frame End at DPHY interface */
#define BITM_MIPI_CSI2_STAT_REG_SOT_LP_AT_DPHY_STAT 0x00000800    /*  Indicates SoT of Long packet at DPHY interface */
#define BITM_MIPI_CSI2_STAT_REG_SOT_FS_AT_DPHY_STAT 0x00000400    /*  Indicates SoT of Frame Start at DPHY interface */
#define BITM_MIPI_CSI2_STAT_REG_EOT_LE_AT_CSI2_STAT 0x00000200    /*  Indicates EoT of Line End at CSI2 interface */
#define BITM_MIPI_CSI2_STAT_REG_EOT_LS_AT_CSI2_STAT 0x00000100    /*  Indicates EoT of Line Start at CSI2 interface */
#define BITM_MIPI_CSI2_STAT_REG_EOT_FE_AT_CSI2_STAT 0x00000080    /*  Indicates EoT of Frame End at CSI2 interface */
#define BITM_MIPI_CSI2_STAT_REG_EOT_LP_AT_CSI2_STAT 0x00000040    /*  Indicates EoT of Long packet at CSI2 interface */
#define BITM_MIPI_CSI2_STAT_REG_EOT_FS_AT_CSI2_STAT 0x00000020    /*  Indicates EoT of Frame Start at CSI2 interface */
#define BITM_MIPI_CSI2_STAT_REG_SOT_LE_AT_CSI2_STAT 0x00000010    /*  Indicates SoT of Line End at CSI2 interface */
#define BITM_MIPI_CSI2_STAT_REG_SOT_LS_AT_CSI2_STAT 0x00000008    /*  Indicates SoT of Line Start at CSI2 interface */
#define BITM_MIPI_CSI2_STAT_REG_SOT_FE_AT_CSI2_STAT 0x00000004    /*  Indicates SoT of Frame End at CSI2 interface */
#define BITM_MIPI_CSI2_STAT_REG_SOT_LP_AT_CSI2_STAT 0x00000002    /*  Indicates SoT of Long packet at CSI2 interface */
#define BITM_MIPI_CSI2_STAT_REG_SOT_FS_AT_CSI2_STAT 0x00000001    /*  Indicates SoT of Frame Start at CSI2 interface */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_CSI2_ECC_SB_ERROR_REG           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_CSI2_ECC_SB_ERROR_REG_CSI2_ECC_SB_ERR_SYNDROME 16            /*  CSI2 FIFO single bit ECC error syndrome */
#define BITP_MIPI_CSI2_ECC_SB_ERROR_REG_CSI2_FIFO_ECC_SB_ERR_ADDR  0            /*  SRAM FIFO address of single bit ECC error */
#define BITM_MIPI_CSI2_ECC_SB_ERROR_REG_CSI2_ECC_SB_ERR_SYNDROME 0x007F0000    /*  CSI2 FIFO single bit ECC error syndrome */
#define BITM_MIPI_CSI2_ECC_SB_ERROR_REG_CSI2_FIFO_ECC_SB_ERR_ADDR 0x00003FFF    /*  SRAM FIFO address of single bit ECC error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_CSI2_ECC_DB_ERROR_REG           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_CSI2_ECC_DB_ERROR_REG_CSI2_ECC_MB_ERR_SYNDROME 16            /*  CSI2 FIFO multi bit ECC error syndrome */
#define BITP_MIPI_CSI2_ECC_DB_ERROR_REG_CSI2_FIFO_ECC_MB_ERR_ADDR  0            /*  SRAM FIFO address of multi bit ECC error */
#define BITM_MIPI_CSI2_ECC_DB_ERROR_REG_CSI2_ECC_MB_ERR_SYNDROME 0x007F0000    /*  CSI2 FIFO multi bit ECC error syndrome */
#define BITM_MIPI_CSI2_ECC_DB_ERROR_REG_CSI2_FIFO_ECC_MB_ERR_ADDR 0x00003FFF    /*  SRAM FIFO address of multi bit ECC error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_CSI2_BUFFER_ADDR                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_CSI2_BUFFER_ADDR_CSI2_BUFFER_READ_ADDR 16            /*  CSI2 Controller Buffer Read Address */
#define BITP_MIPI_CSI2_BUFFER_ADDR_CSI2_BUFFER_WRITE_ADDR  0            /*  CSI2 Controller Buffer Write Address */
#define BITM_MIPI_CSI2_BUFFER_ADDR_CSI2_BUFFER_READ_ADDR 0x3FFF0000    /*  CSI2 Controller Buffer Read Address */
#define BITM_MIPI_CSI2_BUFFER_ADDR_CSI2_BUFFER_WRITE_ADDR 0x00003FFF    /*  CSI2 Controller Buffer Write Address */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_CSI2_RUN_CTL_REG                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_CSI2_RUN_CTL_REG_CSI2_INACT_PH_TX_TRIGGER  0            /*  CSI2 Inactive Phase Transmission Trigger */
#define BITM_MIPI_CSI2_RUN_CTL_REG_CSI2_INACT_PH_TX_TRIGGER 0x00000001    /*  CSI2 Inactive Phase Transmission Trigger */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPI_DPHY_TEST_MODE_STAT_REG         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPI_DPHY_TEST_MODE_STAT_REG_DPHY_TXREADYESC_L3  7            /*  DPHY Escape Mode TX Ready for Lane3 */
#define BITP_MIPI_DPHY_TEST_MODE_STAT_REG_DPHY_TXREADYESC_L2  6            /*  DPHY Escape Mode TX Ready for Lane2 */
#define BITP_MIPI_DPHY_TEST_MODE_STAT_REG_DPHY_TXREADYESC_L1  5            /*  DPHY Escape Mode TX Ready for Lane1 */
#define BITP_MIPI_DPHY_TEST_MODE_STAT_REG_DPHY_TXREADYESC_L0  4            /*  DPHY Escape Mode TX Ready for Lane0 */
#define BITP_MIPI_DPHY_TEST_MODE_STAT_REG_DPHY_TXREADYHS_L3  3            /*  DPHY HS Mode TX Ready for Lane3 */
#define BITP_MIPI_DPHY_TEST_MODE_STAT_REG_DPHY_TXREADYHS_L2  2            /*  DPHY HS Mode TX Ready for Lane2 */
#define BITP_MIPI_DPHY_TEST_MODE_STAT_REG_DPHY_TXREADYHS_L1  1            /*  DPHY HS Mode TX Ready for Lane1 */
#define BITP_MIPI_DPHY_TEST_MODE_STAT_REG_DPHY_TXREADYHS_L0  0            /*  DPHY HS Mode TX Ready for Lane0 */
#define BITM_MIPI_DPHY_TEST_MODE_STAT_REG_DPHY_TXREADYESC_L3 0x00000080    /*  DPHY Escape Mode TX Ready for Lane3 */
#define BITM_MIPI_DPHY_TEST_MODE_STAT_REG_DPHY_TXREADYESC_L2 0x00000040    /*  DPHY Escape Mode TX Ready for Lane2 */
#define BITM_MIPI_DPHY_TEST_MODE_STAT_REG_DPHY_TXREADYESC_L1 0x00000020    /*  DPHY Escape Mode TX Ready for Lane1 */
#define BITM_MIPI_DPHY_TEST_MODE_STAT_REG_DPHY_TXREADYESC_L0 0x00000010    /*  DPHY Escape Mode TX Ready for Lane0 */
#define BITM_MIPI_DPHY_TEST_MODE_STAT_REG_DPHY_TXREADYHS_L3 0x00000008    /*  DPHY HS Mode TX Ready for Lane3 */
#define BITM_MIPI_DPHY_TEST_MODE_STAT_REG_DPHY_TXREADYHS_L2 0x00000004    /*  DPHY HS Mode TX Ready for Lane2 */
#define BITM_MIPI_DPHY_TEST_MODE_STAT_REG_DPHY_TXREADYHS_L1 0x00000002    /*  DPHY HS Mode TX Ready for Lane1 */
#define BITM_MIPI_DPHY_TEST_MODE_STAT_REG_DPHY_TXREADYHS_L0 0x00000001    /*  DPHY HS Mode TX Ready for Lane0 */


/* ============================================================================================================================
        digiMMIC MIPI CSI2 Controller Register Map
   ============================================================================================================================ */

/* ============================================================================================================================
        MIPICSI2
   ============================================================================================================================ */
#define REG_MIPICSI2_VERSION_RESET           0x3131312A            /*      Reset Value for VERSION  */
#define REG_MIPICSI2_VERSION                 0xF0005000
#define REG_MIPICSI2_CSI2_RESETN_RESET       0x00000000            /*      Reset Value for CSI2_RESETN  */
#define REG_MIPICSI2_CSI2_RESETN             0xF0005004
#define REG_MIPICSI2_INT_ST_MAIN_RESET       0x00000000            /*      Reset Value for INT_ST_MAIN  */
#define REG_MIPICSI2_INT_ST_MAIN             0xF0005020
#define REG_MIPICSI2_INT_ST_VPG_RESET        0x00000000            /*      Reset Value for INT_ST_VPG  */
#define REG_MIPICSI2_INT_ST_VPG              0xF0005024
#define REG_MIPICSI2_INT_ST_IDI_RESET        0x00000000            /*      Reset Value for INT_ST_IDI  */
#define REG_MIPICSI2_INT_ST_IDI              0xF0005028
#define REG_MIPICSI2_INT_ST_PHY_RESET        0x00000000            /*      Reset Value for INT_ST_PHY  */
#define REG_MIPICSI2_INT_ST_PHY              0xF0005030
#define REG_MIPICSI2_INT_MASK_N_VPG_RESET    0x00000000            /*      Reset Value for INT_MASK_N_VPG  */
#define REG_MIPICSI2_INT_MASK_N_VPG          0xF0005040
#define REG_MIPICSI2_INT_FORCE_VPG_RESET     0x00000000            /*      Reset Value for INT_FORCE_VPG  */
#define REG_MIPICSI2_INT_FORCE_VPG           0xF0005044
#define REG_MIPICSI2_INT_MASK_N_IDI_RESET    0x00000000            /*      Reset Value for INT_MASK_N_IDI  */
#define REG_MIPICSI2_INT_MASK_N_IDI          0xF0005048
#define REG_MIPICSI2_INT_FORCE_IDI_RESET     0x00000000            /*      Reset Value for INT_FORCE_IDI  */
#define REG_MIPICSI2_INT_FORCE_IDI           0xF000504C
#define REG_MIPICSI2_INT_MASK_N_PHY_RESET    0x00000000            /*      Reset Value for INT_MASK_N_PHY  */
#define REG_MIPICSI2_INT_MASK_N_PHY          0xF0005058
#define REG_MIPICSI2_INT_FORCE_PHY_RESET     0x00000000            /*      Reset Value for INT_FORCE_PHY  */
#define REG_MIPICSI2_INT_FORCE_PHY           0xF000505C
#define REG_MIPICSI2_VPG_CTRL_RESET          0x00000000            /*      Reset Value for VPG_CTRL  */
#define REG_MIPICSI2_VPG_CTRL                0xF0005080
#define REG_MIPICSI2_VPG_STATUS_RESET        0x00000000            /*      Reset Value for VPG_STATUS  */
#define REG_MIPICSI2_VPG_STATUS              0xF0005084
#define REG_MIPICSI2_VPG_MODE_CFG_RESET      0x00000000            /*      Reset Value for VPG_MODE_CFG  */
#define REG_MIPICSI2_VPG_MODE_CFG            0xF0005088
#define REG_MIPICSI2_VPG_PKT_CFG_RESET       0x00000000            /*      Reset Value for VPG_PKT_CFG  */
#define REG_MIPICSI2_VPG_PKT_CFG             0xF000508C
#define REG_MIPICSI2_VPG_PKT_SIZE_RESET      0x00000000            /*      Reset Value for VPG_PKT_SIZE  */
#define REG_MIPICSI2_VPG_PKT_SIZE            0xF0005090
#define REG_MIPICSI2_VPG_HSA_TIME_RESET      0x00000000            /*      Reset Value for VPG_HSA_TIME  */
#define REG_MIPICSI2_VPG_HSA_TIME            0xF0005094
#define REG_MIPICSI2_VPG_HBP_TIME_RESET      0x00000000            /*      Reset Value for VPG_HBP_TIME  */
#define REG_MIPICSI2_VPG_HBP_TIME            0xF0005098
#define REG_MIPICSI2_VPG_HLINE_TIME_RESET    0x00000000            /*      Reset Value for VPG_HLINE_TIME  */
#define REG_MIPICSI2_VPG_HLINE_TIME          0xF000509C
#define REG_MIPICSI2_VPG_VSA_LINES_RESET     0x00000000            /*      Reset Value for VPG_VSA_LINES  */
#define REG_MIPICSI2_VPG_VSA_LINES           0xF00050A0
#define REG_MIPICSI2_VPG_VBP_LINES_RESET     0x00000000            /*      Reset Value for VPG_VBP_LINES  */
#define REG_MIPICSI2_VPG_VBP_LINES           0xF00050A4
#define REG_MIPICSI2_VPG_VFP_LINES_RESET     0x00000000            /*      Reset Value for VPG_VFP_LINES  */
#define REG_MIPICSI2_VPG_VFP_LINES           0xF00050A8
#define REG_MIPICSI2_VPG_ACT_LINES_RESET     0x00000000            /*      Reset Value for VPG_ACT_LINES  */
#define REG_MIPICSI2_VPG_ACT_LINES           0xF00050AC
#define REG_MIPICSI2_VPG_MAX_FRAME_NUM_RESET 0x00000000            /*      Reset Value for VPG_MAX_FRAME_NUM  */
#define REG_MIPICSI2_VPG_MAX_FRAME_NUM       0xF00050B0
#define REG_MIPICSI2_VPG_START_LINE_NUM_RESET 0x00000000            /*      Reset Value for VPG_START_LINE_NUM  */
#define REG_MIPICSI2_VPG_START_LINE_NUM      0xF00050B4
#define REG_MIPICSI2_VPG_STEP_LINE_NUM_RESET 0x00000000            /*      Reset Value for VPG_STEP_LINE_NUM  */
#define REG_MIPICSI2_VPG_STEP_LINE_NUM       0xF00050B8
#define REG_MIPICSI2_PHY_RSTZ_RESET          0x00000000            /*      Reset Value for PHY_RSTZ  */
#define REG_MIPICSI2_PHY_RSTZ                0xF00050E0
#define REG_MIPICSI2_PHY_IF_CFG_RESET        0x00000003            /*      Reset Value for PHY_IF_CFG  */
#define REG_MIPICSI2_PHY_IF_CFG              0xF00050E4
#define REG_MIPICSI2_LPCLK_CTRL_RESET        0x00000000            /*      Reset Value for LPCLK_CTRL  */
#define REG_MIPICSI2_LPCLK_CTRL              0xF00050E8
#define REG_MIPICSI2_PHY_ULPS_CTRL_RESET     0x00000000            /*      Reset Value for PHY_ULPS_CTRL  */
#define REG_MIPICSI2_PHY_ULPS_CTRL           0xF00050EC
#define REG_MIPICSI2_CLKMGR_CFG_RESET        0x00000000            /*      Reset Value for CLKMGR_CFG  */
#define REG_MIPICSI2_CLKMGR_CFG              0xF00050F0
#define REG_MIPICSI2_PHY_TX_TRIGGERS_RESET   0x00000000            /*      Reset Value for PHY_TX_TRIGGERS  */
#define REG_MIPICSI2_PHY_TX_TRIGGERS         0xF00050F4
#define REG_MIPICSI2_PHY_CAL_RESET           0x00000000            /*      Reset Value for PHY_CAL  */
#define REG_MIPICSI2_PHY_CAL                 0xF00050F8
#define REG_MIPICSI2_TO_CNT_CFG_RESET        0x00000000            /*      Reset Value for TO_CNT_CFG  */
#define REG_MIPICSI2_TO_CNT_CFG              0xF00050FC
#define REG_MIPICSI2_PHY_STATUS_RESET        0x00000003            /*      Reset Value for PHY_STATUS  */
#define REG_MIPICSI2_PHY_STATUS              0xF0005110
#define REG_MIPICSI2_PHY0_TST_CTRL0_RESET    0x00000001            /*      Reset Value for PHY0_TST_CTRL0  */
#define REG_MIPICSI2_PHY0_TST_CTRL0          0xF0005114
#define REG_MIPICSI2_PHY0_TST_CTRL1_RESET    0x00000000            /*      Reset Value for PHY0_TST_CTRL1  */
#define REG_MIPICSI2_PHY0_TST_CTRL1          0xF0005118
#define REG_MIPICSI2_IDI_FIFO_STATUS_RESET   0x00000000            /*      Reset Value for IDI_FIFO_STATUS  */
#define REG_MIPICSI2_IDI_FIFO_STATUS         0xF0005180
#define REG_MIPICSI2_INT_ST_FAP_VPG_RESET    0x00000000            /*      Reset Value for INT_ST_FAP_VPG  */
#define REG_MIPICSI2_INT_ST_FAP_VPG          0xF0005A00
#define REG_MIPICSI2_INT_ST_FAP_IDI_RESET    0x00000000            /*      Reset Value for INT_ST_FAP_IDI  */
#define REG_MIPICSI2_INT_ST_FAP_IDI          0xF0005A04
#define REG_MIPICSI2_INT_ST_FAP_PHY_RESET    0x00000000            /*      Reset Value for INT_ST_FAP_PHY  */
#define REG_MIPICSI2_INT_ST_FAP_PHY          0xF0005A0C
#define REG_MIPICSI2_INT_MASK_FAP_N_VPG_RESET 0x00000000            /*      Reset Value for INT_MASK_FAP_N_VPG  */
#define REG_MIPICSI2_INT_MASK_FAP_N_VPG      0xF0005A20
#define REG_MIPICSI2_INT_FORCE_FAP_VPG_RESET 0x00000000            /*      Reset Value for INT_FORCE_FAP_VPG  */
#define REG_MIPICSI2_INT_FORCE_FAP_VPG       0xF0005A24
#define REG_MIPICSI2_INT_MASK_FAP_N_IDI_RESET 0x00000000            /*      Reset Value for INT_MASK_FAP_N_IDI  */
#define REG_MIPICSI2_INT_MASK_FAP_N_IDI      0xF0005A28
#define REG_MIPICSI2_INT_FORCE_FAP_IDI_RESET 0x00000000            /*      Reset Value for INT_FORCE_FAP_IDI  */
#define REG_MIPICSI2_INT_FORCE_FAP_IDI       0xF0005A2C
#define REG_MIPICSI2_INT_MASK_FAP_N_PHY_RESET 0x00000000            /*      Reset Value for INT_MASK_FAP_N_PHY  */
#define REG_MIPICSI2_INT_MASK_FAP_N_PHY      0xF0005A38
#define REG_MIPICSI2_INT_FORCE_FAP_PHY_RESET 0x00000000            /*      Reset Value for INT_FORCE_FAP_PHY  */
#define REG_MIPICSI2_INT_FORCE_FAP_PHY       0xF0005A3C
#define REG_MIPICSI2_IDI_AP_STATUS_RESET     0x00000000            /*      Reset Value for IDI_AP_STATUS  */
#define REG_MIPICSI2_IDI_AP_STATUS           0xF0005A64
#define REG_MIPICSI2_LANE_MGR_AP_STATUS_RESET 0x00000000            /*      Reset Value for LANE_MGR_AP_STATUS  */
#define REG_MIPICSI2_LANE_MGR_AP_STATUS      0xF0005A68
#define REG_MIPICSI2_PHY_IF_CTRL_AP_STATUS_RESET 0x00000000            /*      Reset Value for PHY_IF_CTRL_AP_STATUS  */
#define REG_MIPICSI2_PHY_IF_CTRL_AP_STATUS   0xF0005A6C
#define REG_MIPICSI2_REG_BANK_AP_STATUS_RESET 0x00000000            /*      Reset Value for REG_BANK_AP_STATUS  */
#define REG_MIPICSI2_REG_BANK_AP_STATUS      0xF0005A70
#define REG_MIPICSI2_IDI_FIFOCTRL_AP_STATUS_RESET 0x00000000            /*      Reset Value for IDI_FIFOCTRL_AP_STATUS  */
#define REG_MIPICSI2_IDI_FIFOCTRL_AP_STATUS  0xF0005A78
#define REG_MIPICSI2_PKT_BUILDER_AP_STATUS_RESET 0x00000000            /*      Reset Value for PKT_BUILDER_AP_STATUS  */
#define REG_MIPICSI2_PKT_BUILDER_AP_STATUS   0xF0005A7C
#define REG_MIPICSI2_ERR_HANDLER_AP_STATUS_RESET 0x00000000            /*      Reset Value for ERR_HANDLER_AP_STATUS  */
#define REG_MIPICSI2_ERR_HANDLER_AP_STATUS   0xF0005A80
#define REG_MIPICSI2_FIFO_ADAPTER_AP_STATUS_RESET 0x00000000            /*      Reset Value for FIFO_ADAPTER_AP_STATUS  */
#define REG_MIPICSI2_FIFO_ADAPTER_AP_STATUS  0xF0005A84
#define REG_MIPICSI2_ELASTBUF_AP_STATUS_RESET 0x00000000            /*      Reset Value for ELASTBUF_AP_STATUS  */
#define REG_MIPICSI2_ELASTBUF_AP_STATUS      0xF0005A88
#define REG_MIPICSI2_ECF_AP_STATUS_RESET     0x00000000            /*      Reset Value for ECF_AP_STATUS  */
#define REG_MIPICSI2_ECF_AP_STATUS           0xF0005A8C
#define REG_MIPICSI2_CMU_AP_STATUS_RESET     0x00000000            /*      Reset Value for CMU_AP_STATUS  */
#define REG_MIPICSI2_CMU_AP_STATUS           0xF0005A90
#define REG_MIPICSI2_AMBAAPBINTF_AP_STATUS_RESET 0x00000000            /*      Reset Value for AMBAAPBINTF_AP_STATUS  */
#define REG_MIPICSI2_AMBAAPBINTF_AP_STATUS   0xF0005A94
#define REG_MIPICSI2_CHANNEL_SEL_AP_STATUS_RESET 0x00000000            /*      Reset Value for CHANNEL_SEL_AP_STATUS  */
#define REG_MIPICSI2_CHANNEL_SEL_AP_STATUS   0xF0005A98
#define REG_MIPICSI2_MASK_N_IDI_AP_STATUS_RESET 0x00000000            /*      Reset Value for MASK_N_IDI_AP_STATUS  */
#define REG_MIPICSI2_MASK_N_IDI_AP_STATUS    0xF0005AC8
#define REG_MIPICSI2_FORCE_IDI_AP_STATUS_RESET 0x00000000            /*      Reset Value for FORCE_IDI_AP_STATUS  */
#define REG_MIPICSI2_FORCE_IDI_AP_STATUS     0xF0005ACC
#define REG_MIPICSI2_MASK_N_LANE_MGR_AP_STATUS_RESET 0x00000000            /*      Reset Value for MASK_N_LANE_MGR_AP_STATUS  */
#define REG_MIPICSI2_MASK_N_LANE_MGR_AP_STATUS 0xF0005AD0
#define REG_MIPICSI2_FORCE_LANE_MGR_AP_STATUS_RESET 0x00000000            /*      Reset Value for FORCE_LANE_MGR_AP_STATUS  */
#define REG_MIPICSI2_FORCE_LANE_MGR_AP_STATUS 0xF0005AD4
#define REG_MIPICSI2_MASK_N_PHY_IF_CTRL_AP_STATUS_RESET 0x00000000            /*      Reset Value for MASK_N_PHY_IF_CTRL_AP_STATUS  */
#define REG_MIPICSI2_MASK_N_PHY_IF_CTRL_AP_STATUS 0xF0005AD8
#define REG_MIPICSI2_FORCE_PHY_IF_CTRL_AP_STATUS_RESET 0x00000000            /*      Reset Value for FORCE_PHY_IF_CTRL_AP_STATUS  */
#define REG_MIPICSI2_FORCE_PHY_IF_CTRL_AP_STATUS 0xF0005ADC
#define REG_MIPICSI2_MASK_N_REG_BANK_AP_STATUS_RESET 0x00000000            /*      Reset Value for MASK_N_REG_BANK_AP_STATUS  */
#define REG_MIPICSI2_MASK_N_REG_BANK_AP_STATUS 0xF0005AE0
#define REG_MIPICSI2_FORCE_REG_BANK_AP_STATUS_RESET 0x00000000            /*      Reset Value for FORCE_REG_BANK_AP_STATUS  */
#define REG_MIPICSI2_FORCE_REG_BANK_AP_STATUS 0xF0005AE4
#define REG_MIPICSI2_MASK_N_IDI_FIFOCTRL_AP_STATUS_RESET 0x00000000            /*      Reset Value for MASK_N_IDI_FIFOCTRL_AP_STATUS  */
#define REG_MIPICSI2_MASK_N_IDI_FIFOCTRL_AP_STATUS 0xF0005AF0
#define REG_MIPICSI2_FORCE_IDI_FIFOCTRL_AP_STATUS_RESET 0x00000000            /*      Reset Value for FORCE_IDI_FIFOCTRL_AP_STATUS  */
#define REG_MIPICSI2_FORCE_IDI_FIFOCTRL_AP_STATUS 0xF0005AF4
#define REG_MIPICSI2_MASK_N_PKT_BUILDER_AP_STATUS_RESET 0x00000000            /*      Reset Value for MASK_N_PKT_BUILDER_AP_STATUS  */
#define REG_MIPICSI2_MASK_N_PKT_BUILDER_AP_STATUS 0xF0005AF8
#define REG_MIPICSI2_FORCE_PKT_BUILDER_AP_STATUS_RESET 0x00000000            /*      Reset Value for FORCE_PKT_BUILDER_AP_STATUS  */
#define REG_MIPICSI2_FORCE_PKT_BUILDER_AP_STATUS 0xF0005AFC
#define REG_MIPICSI2_MASK_N_ERR_HANDLER_AP_STATUS_RESET 0x00000000            /*      Reset Value for MASK_N_ERR_HANDLER_AP_STATUS  */
#define REG_MIPICSI2_MASK_N_ERR_HANDLER_AP_STATUS 0xF0005B00
#define REG_MIPICSI2_FORCE_ERR_HANDLER_AP_STATUS_RESET 0x00000000            /*      Reset Value for FORCE_ERR_HANDLER_AP_STATUS  */
#define REG_MIPICSI2_FORCE_ERR_HANDLER_AP_STATUS 0xF0005B04
#define REG_MIPICSI2_MASK_N_FIFO_ADAPTER_AP_STATUS_RESET 0x00000000            /*      Reset Value for MASK_N_FIFO_ADAPTER_AP_STATUS  */
#define REG_MIPICSI2_MASK_N_FIFO_ADAPTER_AP_STATUS 0xF0005B08
#define REG_MIPICSI2_FORCE_FIFO_ADAPTER_AP_STATUS_RESET 0x00000000            /*      Reset Value for FORCE_FIFO_ADAPTER_AP_STATUS  */
#define REG_MIPICSI2_FORCE_FIFO_ADAPTER_AP_STATUS 0xF0005B0C
#define REG_MIPICSI2_MASK_N_ELASTBUF_AP_STATUS_RESET 0x00000000            /*      Reset Value for MASK_N_ELASTBUF_AP_STATUS  */
#define REG_MIPICSI2_MASK_N_ELASTBUF_AP_STATUS 0xF0005B10
#define REG_MIPICSI2_FORCE_ELASTBUF_AP_STATUS_RESET 0x00000000            /*      Reset Value for FORCE_ELASTBUF_AP_STATUS  */
#define REG_MIPICSI2_FORCE_ELASTBUF_AP_STATUS 0xF0005B14
#define REG_MIPICSI2_MASK_N_ECF_AP_STATUS_RESET 0x00000000            /*      Reset Value for MASK_N_ECF_AP_STATUS  */
#define REG_MIPICSI2_MASK_N_ECF_AP_STATUS    0xF0005B18
#define REG_MIPICSI2_FORCE_ECF_AP_STATUS_RESET 0x00000000            /*      Reset Value for FORCE_ECF_AP_STATUS  */
#define REG_MIPICSI2_FORCE_ECF_AP_STATUS     0xF0005B1C
#define REG_MIPICSI2_MASK_N_CMU_AP_STATUS_RESET 0x00000000            /*      Reset Value for MASK_N_CMU_AP_STATUS  */
#define REG_MIPICSI2_MASK_N_CMU_AP_STATUS    0xF0005B20
#define REG_MIPICSI2_FORCE_CMU_AP_STATUS_RESET 0x00000000            /*      Reset Value for FORCE_CMU_AP_STATUS  */
#define REG_MIPICSI2_FORCE_CMU_AP_STATUS     0xF0005B24
#define REG_MIPICSI2_MASK_N_AMBAAPBINTF_AP_STATUS_RESET 0x00000000            /*      Reset Value for MASK_N_AMBAAPBINTF_AP_STATUS  */
#define REG_MIPICSI2_MASK_N_AMBAAPBINTF_AP_STATUS 0xF0005B28
#define REG_MIPICSI2_FORCE_AMBAAPBINTF_AP_STATUS_RESET 0x00000000            /*      Reset Value for FORCE_AMBAAPBINTF_AP_STATUS  */
#define REG_MIPICSI2_FORCE_AMBAAPBINTF_AP_STATUS 0xF0005B2C
#define REG_MIPICSI2_MASK_N_CHANNEL_SEL_AP_STATUS_RESET 0x00000000            /*      Reset Value for MASK_N_CHANNEL_SEL_AP_STATUS  */
#define REG_MIPICSI2_MASK_N_CHANNEL_SEL_AP_STATUS 0xF0005B30
#define REG_MIPICSI2_FORCE_CHANNEL_SEL_AP_STATUS_RESET 0x00000000            /*      Reset Value for FORCE_CHANNEL_SEL_AP_STATUS  */
#define REG_MIPICSI2_FORCE_CHANNEL_SEL_AP_STATUS 0xF0005B34
#define REG_MIPICSI2_INT_ST_DIAG_MAIN_RESET  0x00000000            /*      Reset Value for INT_ST_DIAG_MAIN  */
#define REG_MIPICSI2_INT_ST_DIAG_MAIN        0xF0005F00
#define REG_MIPICSI2_INT_ST_DIAG0_RESET      0x00000000            /*      Reset Value for INT_ST_DIAG0  */
#define REG_MIPICSI2_INT_ST_DIAG0            0xF0005F04
#define REG_MIPICSI2_INT_MASK_N_DIAG0_RESET  0x00000000            /*      Reset Value for INT_MASK_N_DIAG0  */
#define REG_MIPICSI2_INT_MASK_N_DIAG0        0xF0005F10
#define REG_MIPICSI2_INT_FORCE_DIAG0_RESET   0x00000000            /*      Reset Value for INT_FORCE_DIAG0  */
#define REG_MIPICSI2_INT_FORCE_DIAG0         0xF0005F14
#define REG_MIPICSI2_PLDP_ECC_SYNDOUT_RESET  0x00000000            /*      Reset Value for PLDP_ECC_SYNDOUT  */
#define REG_MIPICSI2_PLDP_ECC_SYNDOUT        0xF0005F20
#define REG_MIPICSI2_CL_BCM_SYNC_RESET       0x00000000            /*      Reset Value for CL_BCM_SYNC  */
#define REG_MIPICSI2_CL_BCM_SYNC             0xF0005F24
#define REG_MIPICSI2_CL_BCM23ACK_PPIAPB_RESET 0x00000000            /*      Reset Value for CL_BCM23ACK_PPIAPB  */
#define REG_MIPICSI2_CL_BCM23ACK_PPIAPB      0xF0005F28
#define REG_MIPICSI2_CL_BCM23ACK_IDIAPB_RESET 0x00000000            /*      Reset Value for CL_BCM23ACK_IDIAPB  */
#define REG_MIPICSI2_CL_BCM23ACK_IDIAPB      0xF0005F2C
#define REG_MIPICSI2_HDDP_ECC_SYNDOUT_RESET  0x00000000            /*      Reset Value for HDDP_ECC_SYNDOUT  */
#define REG_MIPICSI2_HDDP_ECC_SYNDOUT        0xF0005F34
#define REG_MIPICSI2_ERR_INJ_CTRL_RESET      0x00000000            /*      Reset Value for ERR_INJ_CTRL  */
#define REG_MIPICSI2_ERR_INJ_CTRL            0xF0005F40
#define REG_MIPICSI2_ERR_INJ_STATUS_RESET    0x00000000            /*      Reset Value for ERR_INJ_STATUS  */
#define REG_MIPICSI2_ERR_INJ_STATUS          0xF0005F44
#define REG_MIPICSI2_ERR_INJ_CHK_MASK_RESET  0x00000000            /*      Reset Value for ERR_INJ_CHK_MASK  */
#define REG_MIPICSI2_ERR_INJ_CHK_MASK        0xF0005F48
#define REG_MIPICSI2_ERR_INJ_DH32_MASK_RESET 0x00000000            /*      Reset Value for ERR_INJ_DH32_MASK  */
#define REG_MIPICSI2_ERR_INJ_DH32_MASK       0xF0005F4C
#define REG_MIPICSI2_ERR_INJ_DL32_MASK_RESET 0x00000000            /*      Reset Value for ERR_INJ_DL32_MASK  */
#define REG_MIPICSI2_ERR_INJ_DL32_MASK       0xF0005F50
#define REG_MIPICSI2_IDI_RAM_ERR_LOG_AP_RESET 0x00000000            /*      Reset Value for IDI_RAM_ERR_LOG_AP  */
#define REG_MIPICSI2_IDI_RAM_ERR_LOG_AP      0xF0005F60
#define REG_MIPICSI2_IDI_RAM_ERR_ADDR_AP_RESET 0x00000000            /*      Reset Value for IDI_RAM_ERR_ADDR_AP  */
#define REG_MIPICSI2_IDI_RAM_ERR_ADDR_AP     0xF0005F64

/* ============================================================================================================================
        MIPICSI2 Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_VERSION                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_VERSION_VERSION         0            /*  DWC_mipicsi2_device version */
#define BITM_MIPICSI2_VERSION_VERSION        0xFFFFFFFF    /*  DWC_mipicsi2_device version */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_CSI2_RESETN                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_CSI2_RESETN_CSI2_RESETN_RW  0            /*  CSI2 Controller Active Low Reset */
#define BITM_MIPICSI2_CSI2_RESETN_CSI2_RESETN_RW 0x00000001    /*  CSI2 Controller Active Low Reset */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_ST_MAIN                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_ST_MAIN_INT_ST_PHY  3            /*  Status of INT_ST_PHY interrupt source group */
#define BITP_MIPICSI2_INT_ST_MAIN_INT_ST_IDI  1            /*  Status of INT_ST_IDI interrupt source group */
#define BITP_MIPICSI2_INT_ST_MAIN_INT_ST_VPG  0            /*  Status of INT_ST_VPG interrupt source group */
#define BITM_MIPICSI2_INT_ST_MAIN_INT_ST_PHY 0x00000008    /*  Status of INT_ST_PHY interrupt source group */
#define BITM_MIPICSI2_INT_ST_MAIN_INT_ST_IDI 0x00000002    /*  Status of INT_ST_IDI interrupt source group */
#define BITM_MIPICSI2_INT_ST_MAIN_INT_ST_VPG 0x00000001    /*  Status of INT_ST_VPG interrupt source group */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_ST_VPG                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_ST_VPG_VPG_PKT_LOST  0            /*  Packet lost of video pattern generator */
#define BITM_MIPICSI2_INT_ST_VPG_VPG_PKT_LOST 0x00000001    /*  Packet lost of video pattern generator */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_ST_IDI                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_ST_IDI_IDI_FIFO_OVERFLOW  9            /*  IDI FIFO Overflow error */
#define BITP_MIPICSI2_INT_ST_IDI_IDI_VC3_ERRL_SEQ  8            /*  Line sequence error for Virtual Channel 3 */
#define BITP_MIPICSI2_INT_ST_IDI_IDI_VC2_ERRL_SEQ  7            /*  Line sequence error for Virtual Channel 2 */
#define BITP_MIPICSI2_INT_ST_IDI_IDI_VC1_ERRL_SEQ  6            /*  Line sequence error for Virtual Channel 1 */
#define BITP_MIPICSI2_INT_ST_IDI_IDI_VC0_ERRL_SEQ  5            /*  Line sequence error for Virtual Channel 0 */
#define BITP_MIPICSI2_INT_ST_IDI_IDI_VC3_ERRF_SEQ  4            /*  Frame sequence error for Virtual Channel 3 */
#define BITP_MIPICSI2_INT_ST_IDI_IDI_VC2_ERRF_SEQ  3            /*  Frame sequence error for Virtual Channel 2 */
#define BITP_MIPICSI2_INT_ST_IDI_IDI_VC1_ERRF_SEQ  2            /*  Frame sequence error for Virtual Channel 1 */
#define BITP_MIPICSI2_INT_ST_IDI_IDI_VC0_ERRF_SEQ  1            /*  Frame sequence error for Virtual Channel 0 */
#define BITP_MIPICSI2_INT_ST_IDI_IDI_ERRWC    0            /*  IDI Word Count mismatch error */
#define BITM_MIPICSI2_INT_ST_IDI_IDI_FIFO_OVERFLOW 0x00000200    /*  IDI FIFO Overflow error */
#define BITM_MIPICSI2_INT_ST_IDI_IDI_VC3_ERRL_SEQ 0x00000100    /*  Line sequence error for Virtual Channel 3 */
#define BITM_MIPICSI2_INT_ST_IDI_IDI_VC2_ERRL_SEQ 0x00000080    /*  Line sequence error for Virtual Channel 2 */
#define BITM_MIPICSI2_INT_ST_IDI_IDI_VC1_ERRL_SEQ 0x00000040    /*  Line sequence error for Virtual Channel 1 */
#define BITM_MIPICSI2_INT_ST_IDI_IDI_VC0_ERRL_SEQ 0x00000020    /*  Line sequence error for Virtual Channel 0 */
#define BITM_MIPICSI2_INT_ST_IDI_IDI_VC3_ERRF_SEQ 0x00000010    /*  Frame sequence error for Virtual Channel 3 */
#define BITM_MIPICSI2_INT_ST_IDI_IDI_VC2_ERRF_SEQ 0x00000008    /*  Frame sequence error for Virtual Channel 2 */
#define BITM_MIPICSI2_INT_ST_IDI_IDI_VC1_ERRF_SEQ 0x00000004    /*  Frame sequence error for Virtual Channel 1 */
#define BITM_MIPICSI2_INT_ST_IDI_IDI_VC0_ERRF_SEQ 0x00000002    /*  Frame sequence error for Virtual Channel 0 */
#define BITM_MIPICSI2_INT_ST_IDI_IDI_ERRWC   0x00000001    /*  IDI Word Count mismatch error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_ST_PHY                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_ST_PHY_ERRCONTENTIONLP1  2            /*  Indicates LP1 contention error ErrContentionLP1 from Lane 0 */
#define BITP_MIPICSI2_INT_ST_PHY_ERRCONTENTIONLP0  1            /*  Indicates LP0 contention error ErrContentionLP0 from Lane 0 */
#define BITP_MIPICSI2_INT_ST_PHY_TO_HS_TX     0            /*  High speed transmission timeout counter reached */
#define BITM_MIPICSI2_INT_ST_PHY_ERRCONTENTIONLP1 0x00000004    /*  Indicates LP1 contention error ErrContentionLP1 from Lane 0 */
#define BITM_MIPICSI2_INT_ST_PHY_ERRCONTENTIONLP0 0x00000002    /*  Indicates LP0 contention error ErrContentionLP0 from Lane 0 */
#define BITM_MIPICSI2_INT_ST_PHY_TO_HS_TX    0x00000001    /*  High speed transmission timeout counter reached */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_MASK_N_VPG              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_MASK_N_VPG_MASK_VPG_PKT_LOST  0            /*  Mask for vpg_pkt_lost */
#define BITM_MIPICSI2_INT_MASK_N_VPG_MASK_VPG_PKT_LOST 0x00000001    /*  Mask for vpg_pkt_lost */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_FORCE_VPG               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_FORCE_VPG_FORCE_VPG_PKT_LOST  0            /*  Force for vpg_pkt_lost */
#define BITM_MIPICSI2_INT_FORCE_VPG_FORCE_VPG_PKT_LOST 0x00000001    /*  Force for vpg_pkt_lost */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_MASK_N_IDI              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_FIFO_OVERFLOW  9            /*  Mask for idi_fifo_overflow */
#define BITP_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_VC3_ERRL_SEQ  8            /*  Mask for idi_vc3_errl_seq */
#define BITP_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_VC2_ERRL_SEQ  7            /*  Mask for idi_vc2_errl_seq */
#define BITP_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_VC1_ERRL_SEQ  6            /*  Mask for idi_vc1_errl_seq */
#define BITP_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_VC0_ERRL_SEQ  5            /*  Mask for idi_vc0_errl_seq */
#define BITP_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_VC3_ERRF_SEQ  4            /*  Mask for idi_vc3_errf_seq */
#define BITP_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_VC2_ERRF_SEQ  3            /*  Mask for idi_vc2_errf_seq */
#define BITP_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_VC1_ERRF_SEQ  2            /*  Mask for idi_vc1_errf_seq */
#define BITP_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_VC0_ERRF_SEQ  1            /*  Mask for idi_vc0_errf_seq */
#define BITP_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_ERRWC  0            /*  Mask for idi_errwc */
#define BITM_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_FIFO_OVERFLOW 0x00000200    /*  Mask for idi_fifo_overflow */
#define BITM_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_VC3_ERRL_SEQ 0x00000100    /*  Mask for idi_vc3_errl_seq */
#define BITM_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_VC2_ERRL_SEQ 0x00000080    /*  Mask for idi_vc2_errl_seq */
#define BITM_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_VC1_ERRL_SEQ 0x00000040    /*  Mask for idi_vc1_errl_seq */
#define BITM_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_VC0_ERRL_SEQ 0x00000020    /*  Mask for idi_vc0_errl_seq */
#define BITM_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_VC3_ERRF_SEQ 0x00000010    /*  Mask for idi_vc3_errf_seq */
#define BITM_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_VC2_ERRF_SEQ 0x00000008    /*  Mask for idi_vc2_errf_seq */
#define BITM_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_VC1_ERRF_SEQ 0x00000004    /*  Mask for idi_vc1_errf_seq */
#define BITM_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_VC0_ERRF_SEQ 0x00000002    /*  Mask for idi_vc0_errf_seq */
#define BITM_MIPICSI2_INT_MASK_N_IDI_MASK_IDI_ERRWC 0x00000001    /*  Mask for idi_errwc */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_FORCE_IDI               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_FIFO_OVERFLOW  9            /*  Force for idi_fifo_overflow */
#define BITP_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_VC3_ERRL_SEQ  8            /*  Force for idi_vc3_errl_seq */
#define BITP_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_VC2_ERRL_SEQ  7            /*  Force for idi_vc2_errl_seq */
#define BITP_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_VC1_ERRL_SEQ  6            /*  Force for idi_vc1_errl_seq */
#define BITP_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_VC0_ERRL_SEQ  5            /*  Force for idi_vc0_errl_seq */
#define BITP_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_VC3_ERRF_SEQ  4            /*  Force for idi_vc3_errf_seq */
#define BITP_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_VC2_ERRF_SEQ  3            /*  Force for idi_vc2_errf_seq */
#define BITP_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_VC1_ERRF_SEQ  2            /*  Force for idi_vc1_errf_seq */
#define BITP_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_VC0_ERRF_SEQ  1            /*  Force for idi_vc0_errf_seq */
#define BITP_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_ERRWC  0            /*  Force for idi_errwc */
#define BITM_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_FIFO_OVERFLOW 0x00000200    /*  Force for idi_fifo_overflow */
#define BITM_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_VC3_ERRL_SEQ 0x00000100    /*  Force for idi_vc3_errl_seq */
#define BITM_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_VC2_ERRL_SEQ 0x00000080    /*  Force for idi_vc2_errl_seq */
#define BITM_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_VC1_ERRL_SEQ 0x00000040    /*  Force for idi_vc1_errl_seq */
#define BITM_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_VC0_ERRL_SEQ 0x00000020    /*  Force for idi_vc0_errl_seq */
#define BITM_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_VC3_ERRF_SEQ 0x00000010    /*  Force for idi_vc3_errf_seq */
#define BITM_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_VC2_ERRF_SEQ 0x00000008    /*  Force for idi_vc2_errf_seq */
#define BITM_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_VC1_ERRF_SEQ 0x00000004    /*  Force for idi_vc1_errf_seq */
#define BITM_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_VC0_ERRF_SEQ 0x00000002    /*  Force for idi_vc0_errf_seq */
#define BITM_MIPICSI2_INT_FORCE_IDI_FORCE_IDI_ERRWC 0x00000001    /*  Force for idi_errwc */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_MASK_N_PHY              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_MASK_N_PHY_MASK_ERRCONTENTIONLP1  2            /*  Mask for errcontentionlp1 */
#define BITP_MIPICSI2_INT_MASK_N_PHY_MASK_ERRCONTENTIONLP0  1            /*  Mask for errcontentionlp0 */
#define BITP_MIPICSI2_INT_MASK_N_PHY_MASK_TO_HS_TX  0            /*  Mask for to_hs_tx */
#define BITM_MIPICSI2_INT_MASK_N_PHY_MASK_ERRCONTENTIONLP1 0x00000004    /*  Mask for errcontentionlp1 */
#define BITM_MIPICSI2_INT_MASK_N_PHY_MASK_ERRCONTENTIONLP0 0x00000002    /*  Mask for errcontentionlp0 */
#define BITM_MIPICSI2_INT_MASK_N_PHY_MASK_TO_HS_TX 0x00000001    /*  Mask for to_hs_tx */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_FORCE_PHY               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_FORCE_PHY_FORCE_ERRCONTENTIONLP1  2            /*  Force for errcontentionlp1 */
#define BITP_MIPICSI2_INT_FORCE_PHY_FORCE_ERRCONTENTIONLP0  1            /*  Force for errcontentionlp0 */
#define BITP_MIPICSI2_INT_FORCE_PHY_FORCE_TO_HS_TX  0            /*  Force for to_hs_tx */
#define BITM_MIPICSI2_INT_FORCE_PHY_FORCE_ERRCONTENTIONLP1 0x00000004    /*  Force for errcontentionlp1 */
#define BITM_MIPICSI2_INT_FORCE_PHY_FORCE_ERRCONTENTIONLP0 0x00000002    /*  Force for errcontentionlp0 */
#define BITM_MIPICSI2_INT_FORCE_PHY_FORCE_TO_HS_TX 0x00000001    /*  Force for to_hs_tx */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_VPG_CTRL                    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_VPG_CTRL_VPG_EN         0            /*  Video pattern generator enable signal. Active High. */
#define BITM_MIPICSI2_VPG_CTRL_VPG_EN        0x00000001    /*  Video pattern generator enable signal. Active High. */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_VPG_STATUS                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_VPG_STATUS_VPG_ACTIVE   0            /*  Video pattern status */
#define BITM_MIPICSI2_VPG_STATUS_VPG_ACTIVE  0x00000001    /*  Video pattern status */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_VPG_MODE_CFG                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_VPG_MODE_CFG_VPG_ORIENTATION 16            /*  This field indicates the color bar orientation */
#define BITP_MIPICSI2_VPG_MODE_CFG_VPG_MODE   0            /*  Pattern Type */
#define BITM_MIPICSI2_VPG_MODE_CFG_VPG_ORIENTATION 0x00010000    /*  This field indicates the color bar orientation */
#define BITM_MIPICSI2_VPG_MODE_CFG_VPG_MODE  0x00000001    /*  Pattern Type */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_VPG_PKT_CFG                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_VPG_PKT_CFG_VPG_FRAME_NUM_MODE 11            /*  This field indicates the frame number mode */
#define BITP_MIPICSI2_VPG_PKT_CFG_VPG_LINE_NUM_MODE  9            /*  This field indicates line number mode */
#define BITP_MIPICSI2_VPG_PKT_CFG_VPG_HSYNC_PKT_EN  8            /*  This field indicates the line synchronization packets mode */
#define BITP_MIPICSI2_VPG_PKT_CFG_VPG_VC      6            /*  The Virtual Channel of video pattern packet */
#define BITP_MIPICSI2_VPG_PKT_CFG_VPG_DT      0            /*  The Data Type of video pattern packet */
#define BITM_MIPICSI2_VPG_PKT_CFG_VPG_FRAME_NUM_MODE 0x00000800    /*  This field indicates the frame number mode */
#define BITM_MIPICSI2_VPG_PKT_CFG_VPG_LINE_NUM_MODE 0x00000600    /*  This field indicates line number mode */
#define BITM_MIPICSI2_VPG_PKT_CFG_VPG_HSYNC_PKT_EN 0x00000100    /*  This field indicates the line synchronization packets mode */
#define BITM_MIPICSI2_VPG_PKT_CFG_VPG_VC     0x000000C0    /*  The Virtual Channel of video pattern packet */
#define BITM_MIPICSI2_VPG_PKT_CFG_VPG_DT     0x0000003F    /*  The Data Type of video pattern packet */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_VPG_PKT_SIZE                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_VPG_PKT_SIZE_VPG_PKT_SIZE  0            /*  The number of pixels in a single video pattern packet */
#define BITM_MIPICSI2_VPG_PKT_SIZE_VPG_PKT_SIZE 0x00003FFF    /*  The number of pixels in a single video pattern packet */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_VPG_HSA_TIME                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_VPG_HSA_TIME_VPG_HSA_TIME  0            /*  The configuration of horizontal synchronism active period in lane byte clock domain */
#define BITM_MIPICSI2_VPG_HSA_TIME_VPG_HSA_TIME 0x00000FFF    /*  The configuration of horizontal synchronism active period in lane byte clock domain */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_VPG_HBP_TIME                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_VPG_HBP_TIME_VPG_HBP_TIME  0            /*  The configuration of horizontal back porch period in lane byte clock domain */
#define BITM_MIPICSI2_VPG_HBP_TIME_VPG_HBP_TIME 0x00000FFF    /*  The configuration of horizontal back porch period in lane byte clock domain */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_VPG_HLINE_TIME              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_VPG_HLINE_TIME_VPG_HLINE_TIME  0            /*  Size of total line time(HSA+HBP+HACT+HFP) counted in lane byte clock domain */
#define BITM_MIPICSI2_VPG_HLINE_TIME_VPG_HLINE_TIME 0x00007FFF    /*  Size of total line time(HSA+HBP+HACT+HFP) counted in lane byte clock domain */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_VPG_VSA_LINES               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_VPG_VSA_LINES_VPG_VSA_LINES  0            /*  The vertical synchronism active period measured in number of horizontal lines */
#define BITM_MIPICSI2_VPG_VSA_LINES_VPG_VSA_LINES 0x000003FF    /*  The vertical synchronism active period measured in number of horizontal lines */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_VPG_VBP_LINES               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_VPG_VBP_LINES_VPG_VBP_LINES  0            /*  The vertical back porch period measured in number of horizontal lines */
#define BITM_MIPICSI2_VPG_VBP_LINES_VPG_VBP_LINES 0x000003FF    /*  The vertical back porch period measured in number of horizontal lines */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_VPG_VFP_LINES               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_VPG_VFP_LINES_VPG_VFP_LINES  0            /*  The vertical front porch period measured in number of horizontal lines */
#define BITM_MIPICSI2_VPG_VFP_LINES_VPG_VFP_LINES 0x000003FF    /*  The vertical front porch period measured in number of horizontal lines */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_VPG_ACT_LINES               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_VPG_ACT_LINES_VPG_ACT_LINES  0            /*  The vertical active period measured in number of horizontal lines */
#define BITM_MIPICSI2_VPG_ACT_LINES_VPG_ACT_LINES 0x00003FFF    /*  The vertical active period measured in number of horizontal lines */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_VPG_MAX_FRAME_NUM           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_VPG_MAX_FRAME_NUM_VPG_MAX_FRAME_NUM  0            /*  Define the max frame number under Frame Number Increments one mode */
#define BITM_MIPICSI2_VPG_MAX_FRAME_NUM_VPG_MAX_FRAME_NUM 0x0000FFFF    /*  Define the max frame number under Frame Number Increments one mode */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_VPG_START_LINE_NUM          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_VPG_START_LINE_NUM_VPG_START_LINE_NUM  0            /*  Start line number under Line Number Increments Arbitrary Value mode */
#define BITM_MIPICSI2_VPG_START_LINE_NUM_VPG_START_LINE_NUM 0x0000FFFF    /*  Start line number under Line Number Increments Arbitrary Value mode */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_VPG_STEP_LINE_NUM           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_VPG_STEP_LINE_NUM_VPG_STEP_LINE_NUM  0            /*  Step value for line number under Line Number Increments Arbitrary Value mode */
#define BITM_MIPICSI2_VPG_STEP_LINE_NUM_VPG_STEP_LINE_NUM 0x0000FFFF    /*  Step value for line number under Line Number Increments Arbitrary Value mode */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_PHY_RSTZ                    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_PHY_RSTZ_PHY_FORCEPLL   3            /*  PHY Force PLL */
#define BITP_MIPICSI2_PHY_RSTZ_PHY_ENABLECLK  2            /*  PHY Enable Clock */
#define BITP_MIPICSI2_PHY_RSTZ_PHY_RSTZ       1            /*  PHY Reset */
#define BITP_MIPICSI2_PHY_RSTZ_PHY_SHUTDOWNZ  0            /*  PHY Shutdown */
#define BITM_MIPICSI2_PHY_RSTZ_PHY_FORCEPLL  0x00000008    /*  PHY Force PLL */
#define BITM_MIPICSI2_PHY_RSTZ_PHY_ENABLECLK 0x00000004    /*  PHY Enable Clock */
#define BITM_MIPICSI2_PHY_RSTZ_PHY_RSTZ      0x00000002    /*  PHY Reset */
#define BITM_MIPICSI2_PHY_RSTZ_PHY_SHUTDOWNZ 0x00000001    /*  PHY Shutdown */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_PHY_IF_CFG                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_PHY_IF_CFG_PHY_STOP_WAIT_TIME  8            /*  PHY Stop Wait Time */
#define BITP_MIPICSI2_PHY_IF_CFG_LANE_EN_NUM  0            /*  Number of Lanes Enabled */
#define BITM_MIPICSI2_PHY_IF_CFG_PHY_STOP_WAIT_TIME 0x0000FF00    /*  PHY Stop Wait Time */
#define BITM_MIPICSI2_PHY_IF_CFG_LANE_EN_NUM 0x00000007    /*  Number of Lanes Enabled */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_LPCLK_CTRL                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_LPCLK_CTRL_PHY_TXREQCLKHS_CON  0            /*  Controls D-PHY txrequestclkhs signal */
#define BITM_MIPICSI2_LPCLK_CTRL_PHY_TXREQCLKHS_CON 0x00000001    /*  Controls D-PHY txrequestclkhs signal */
#define ENUM_MIPICSI2_LPCLK_CTRL_EN000       0x00000000            /*  phy_txreqclkhs_con: Non-continuous clock mode */
#define ENUM_MIPICSI2_LPCLK_CTRL_EN001       0x00000001            /*  phy_txreqclkhs_con: Continuous clock mode */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_PHY_ULPS_CTRL               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_PHY_ULPS_CTRL_PHY_TXEXITULPSLAN  3            /*  ULPS mode exit on all active data lanes */
#define BITP_MIPICSI2_PHY_ULPS_CTRL_PHY_TXREQULPSLAN  2            /*  ULPS mode request on all active data lanes */
#define BITP_MIPICSI2_PHY_ULPS_CTRL_PHY_TXEXITULPSCLK  1            /*  ULPS mode exit on clock lane */
#define BITP_MIPICSI2_PHY_ULPS_CTRL_PHY_TXREQULPSCLK  0            /*  ULPS mode request on clock lane */
#define BITM_MIPICSI2_PHY_ULPS_CTRL_PHY_TXEXITULPSLAN 0x00000008    /*  ULPS mode exit on all active data lanes */
#define BITM_MIPICSI2_PHY_ULPS_CTRL_PHY_TXREQULPSLAN 0x00000004    /*  ULPS mode request on all active data lanes */
#define BITM_MIPICSI2_PHY_ULPS_CTRL_PHY_TXEXITULPSCLK 0x00000002    /*  ULPS mode exit on clock lane */
#define BITM_MIPICSI2_PHY_ULPS_CTRL_PHY_TXREQULPSCLK 0x00000001    /*  ULPS mode request on clock lane */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_CLKMGR_CFG                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_CLKMGR_CFG_TO_CLK_DIVISION  8            /*  Time out clock division factor */
#define BITP_MIPICSI2_CLKMGR_CFG_TX_ESC_CLK_DIVISION  0            /*  TX Escape clock division factor */
#define BITM_MIPICSI2_CLKMGR_CFG_TO_CLK_DIVISION 0x0000FF00    /*  Time out clock division factor */
#define BITM_MIPICSI2_CLKMGR_CFG_TX_ESC_CLK_DIVISION 0x000000FF    /*  TX Escape clock division factor */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_PHY_TX_TRIGGERS             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_PHY_TX_TRIGGERS_TX_TRIGGERS_EN  7            /*  TX Trigger Enable */
#define BITP_MIPICSI2_PHY_TX_TRIGGERS_TX_TRIGGERS  0            /*  Activates trigger transmissions */
#define BITM_MIPICSI2_PHY_TX_TRIGGERS_TX_TRIGGERS_EN 0x00000080    /*  TX Trigger Enable */
#define BITM_MIPICSI2_PHY_TX_TRIGGERS_TX_TRIGGERS 0x00000003    /*  Activates trigger transmissions */
#define ENUM_MIPICSI2_PHY_TX_TRIGGERS_EN000  0x00000000            /*  tx_triggers: Trigger 0 active */
#define ENUM_MIPICSI2_PHY_TX_TRIGGERS_EN001  0x00000001            /*  tx_triggers: Trigger 1 active */
#define ENUM_MIPICSI2_PHY_TX_TRIGGERS_EN002  0x00000002            /*  tx_triggers: Trigger 2 active */
#define ENUM_MIPICSI2_PHY_TX_TRIGGERS_EN003  0x00000003            /*  tx_triggers: Trigger 3 active */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_PHY_CAL                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_PHY_CAL_PHY_CAL         0            /*  Controls calibration pin of D-PHY */
#define BITM_MIPICSI2_PHY_CAL_PHY_CAL        0x00000001    /*  Controls calibration pin of D-PHY */
#define ENUM_MIPICSI2_PHY_CAL_EN000          0x00000000            /*  phy_cal: No calibration */
#define ENUM_MIPICSI2_PHY_CAL_EN001          0x00000001            /*  phy_cal: High-speed transmit skew calibration is activated */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_TO_CNT_CFG                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_TO_CNT_CFG_HSTX_TO_CNT  0            /*  Configures timeout counter for high speed transmission timeout contention detection */
#define BITM_MIPICSI2_TO_CNT_CFG_HSTX_TO_CNT 0x0000FFFF    /*  Configures timeout counter for high speed transmission timeout contention detection */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_PHY_STATUS                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_PHY_STATUS_TXULPSACTIVENOT_L3 13            /*  TX Not ULPS Active of Data Lane3 */
#define BITP_MIPICSI2_PHY_STATUS_TXSTOPSTATE_L3 12            /*  TX Stop State of Data Lane3 */
#define BITP_MIPICSI2_PHY_STATUS_TXULPSACTIVENOT_L2 11            /*  TX Not ULPS Active of Data Lane2 */
#define BITP_MIPICSI2_PHY_STATUS_TXSTOPSTATE_L2 10            /*  TX Stop State of Data Lane2 */
#define BITP_MIPICSI2_PHY_STATUS_TXULPSACTIVENOT_L1  9            /*  TX Not ULPS Active of Data Lane1 */
#define BITP_MIPICSI2_PHY_STATUS_TXSTOPSTATE_L1  8            /*  TX Stop State of Data Lane1 */
#define BITP_MIPICSI2_PHY_STATUS_TXULPSACTIVENOT_L0  7            /*  TX Not ULPS Active of Data Lane0 */
#define BITP_MIPICSI2_PHY_STATUS_TXSTOPSTATE_L0  6            /*  TX Stop State of Data Lane0 */
#define BITP_MIPICSI2_PHY_STATUS_TXULPSACTIVENOT_CLK  5            /*  TX Not ULPS Active of Clock Lane */
#define BITP_MIPICSI2_PHY_STATUS_TXSTOPSTATE_CLK  4            /*  TX Stop State of Clock Lane */
#define BITP_MIPICSI2_PHY_STATUS_PLL_LOCK     3            /*  PHY PLL Lock Status */
#define BITP_MIPICSI2_PHY_STATUS_LANE_MAX_NUM  0            /*  Maximum Number of Lanes */
#define BITM_MIPICSI2_PHY_STATUS_TXULPSACTIVENOT_L3 0x00002000    /*  TX Not ULPS Active of Data Lane3 */
#define BITM_MIPICSI2_PHY_STATUS_TXSTOPSTATE_L3 0x00001000    /*  TX Stop State of Data Lane3 */
#define BITM_MIPICSI2_PHY_STATUS_TXULPSACTIVENOT_L2 0x00000800    /*  TX Not ULPS Active of Data Lane2 */
#define BITM_MIPICSI2_PHY_STATUS_TXSTOPSTATE_L2 0x00000400    /*  TX Stop State of Data Lane2 */
#define BITM_MIPICSI2_PHY_STATUS_TXULPSACTIVENOT_L1 0x00000200    /*  TX Not ULPS Active of Data Lane1 */
#define BITM_MIPICSI2_PHY_STATUS_TXSTOPSTATE_L1 0x00000100    /*  TX Stop State of Data Lane1 */
#define BITM_MIPICSI2_PHY_STATUS_TXULPSACTIVENOT_L0 0x00000080    /*  TX Not ULPS Active of Data Lane0 */
#define BITM_MIPICSI2_PHY_STATUS_TXSTOPSTATE_L0 0x00000040    /*  TX Stop State of Data Lane0 */
#define BITM_MIPICSI2_PHY_STATUS_TXULPSACTIVENOT_CLK 0x00000020    /*  TX Not ULPS Active of Clock Lane */
#define BITM_MIPICSI2_PHY_STATUS_TXSTOPSTATE_CLK 0x00000010    /*  TX Stop State of Clock Lane */
#define BITM_MIPICSI2_PHY_STATUS_PLL_LOCK    0x00000008    /*  PHY PLL Lock Status */
#define BITM_MIPICSI2_PHY_STATUS_LANE_MAX_NUM 0x00000007    /*  Maximum Number of Lanes */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_PHY0_TST_CTRL0              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_PHY0_TST_CTRL0_PHY0_TESTCLK  1            /*  PHY test interface clock signal */
#define BITP_MIPICSI2_PHY0_TST_CTRL0_PHY0_TESTCLR  0            /*  PHY test interface clear */
#define BITM_MIPICSI2_PHY0_TST_CTRL0_PHY0_TESTCLK 0x00000002    /*  PHY test interface clock signal */
#define BITM_MIPICSI2_PHY0_TST_CTRL0_PHY0_TESTCLR 0x00000001    /*  PHY test interface clear */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_PHY0_TST_CTRL1              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_PHY0_TST_CTRL1_PHY0_TESTEN 16            /*  PHY test interface operation selector */
#define BITP_MIPICSI2_PHY0_TST_CTRL1_PHY0_TESTDOUT  8            /*  PHY test interface 8-bit output data bus */
#define BITP_MIPICSI2_PHY0_TST_CTRL1_PHY0_TESTDIN  0            /*  PHY test interface 8-bit input data bus */
#define BITM_MIPICSI2_PHY0_TST_CTRL1_PHY0_TESTEN 0x00010000    /*  PHY test interface operation selector */
#define BITM_MIPICSI2_PHY0_TST_CTRL1_PHY0_TESTDOUT 0x0000FF00    /*  PHY test interface 8-bit output data bus */
#define BITM_MIPICSI2_PHY0_TST_CTRL1_PHY0_TESTDIN 0x000000FF    /*  PHY test interface 8-bit input data bus */
#define ENUM_MIPICSI2_PHY0_TST_CTRL1_EN000   0x00000000            /*  phy0_testen: Data write operation on rising edge of testclk signal */
#define ENUM_MIPICSI2_PHY0_TST_CTRL1_EN001   0x00010000            /*  phy0_testen: Address write operation on falling edge of testclk signal */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_IDI_FIFO_STATUS             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_IDI_FIFO_STATUS_IDI_PL_FIFO_FULL  3            /*  Indicates the payload FIFO full status of IDI interface */
#define BITP_MIPICSI2_IDI_FIFO_STATUS_IDI_HD_FIFO_FULL  2            /*  Indicates the header FIFO full status of IDI interface */
#define BITP_MIPICSI2_IDI_FIFO_STATUS_IDI_PL_FIFO_EMPTYZ  1            /*  Indicates the payload FIFO empty status of IDI interface */
#define BITP_MIPICSI2_IDI_FIFO_STATUS_IDI_HD_FIFO_EMPTYZ  0            /*  Indicates the header FIFO empty status of IDI interface */
#define BITM_MIPICSI2_IDI_FIFO_STATUS_IDI_PL_FIFO_FULL 0x00000008    /*  Indicates the payload FIFO full status of IDI interface */
#define BITM_MIPICSI2_IDI_FIFO_STATUS_IDI_HD_FIFO_FULL 0x00000004    /*  Indicates the header FIFO full status of IDI interface */
#define BITM_MIPICSI2_IDI_FIFO_STATUS_IDI_PL_FIFO_EMPTYZ 0x00000002    /*  Indicates the payload FIFO empty status of IDI interface */
#define BITM_MIPICSI2_IDI_FIFO_STATUS_IDI_HD_FIFO_EMPTYZ 0x00000001    /*  Indicates the header FIFO empty status of IDI interface */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_ST_FAP_VPG              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_ST_FAP_VPG_VPG_PKT_LOST  0            /*  Packet lost of video pattern generator */
#define BITM_MIPICSI2_INT_ST_FAP_VPG_VPG_PKT_LOST 0x00000001    /*  Packet lost of video pattern generator */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_ST_FAP_IDI              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_ST_FAP_IDI_IDI_FIFO_OVERFLOW  9            /*  IDI FIFO Overflow error */
#define BITP_MIPICSI2_INT_ST_FAP_IDI_IDI_VC3_ERRL_SEQ  8            /*  Line sequence error for Virtual Channel 3 */
#define BITP_MIPICSI2_INT_ST_FAP_IDI_IDI_VC2_ERRL_SEQ  7            /*  Line sequence error for Virtual Channel 2 */
#define BITP_MIPICSI2_INT_ST_FAP_IDI_IDI_VC1_ERRL_SEQ  6            /*  Line sequence error for Virtual Channel 1 */
#define BITP_MIPICSI2_INT_ST_FAP_IDI_IDI_VC0_ERRL_SEQ  5            /*  Line sequence error for Virtual Channel 0 */
#define BITP_MIPICSI2_INT_ST_FAP_IDI_IDI_VC3_ERRF_SEQ  4            /*  Frame sequence error for Virtual Channel 3 */
#define BITP_MIPICSI2_INT_ST_FAP_IDI_IDI_VC2_ERRF_SEQ  3            /*  Frame sequence error for Virtual Channel 2 */
#define BITP_MIPICSI2_INT_ST_FAP_IDI_IDI_VC1_ERRF_SEQ  2            /*  Frame sequence error for Virtual Channel 1 */
#define BITP_MIPICSI2_INT_ST_FAP_IDI_IDI_VC0_ERRF_SEQ  1            /*  Frame sequence error for Virtual Channel 0 */
#define BITP_MIPICSI2_INT_ST_FAP_IDI_IDI_ERRWC  0            /*  IDI Word Count mismatch error */
#define BITM_MIPICSI2_INT_ST_FAP_IDI_IDI_FIFO_OVERFLOW 0x00000200    /*  IDI FIFO Overflow error */
#define BITM_MIPICSI2_INT_ST_FAP_IDI_IDI_VC3_ERRL_SEQ 0x00000100    /*  Line sequence error for Virtual Channel 3 */
#define BITM_MIPICSI2_INT_ST_FAP_IDI_IDI_VC2_ERRL_SEQ 0x00000080    /*  Line sequence error for Virtual Channel 2 */
#define BITM_MIPICSI2_INT_ST_FAP_IDI_IDI_VC1_ERRL_SEQ 0x00000040    /*  Line sequence error for Virtual Channel 1 */
#define BITM_MIPICSI2_INT_ST_FAP_IDI_IDI_VC0_ERRL_SEQ 0x00000020    /*  Line sequence error for Virtual Channel 0 */
#define BITM_MIPICSI2_INT_ST_FAP_IDI_IDI_VC3_ERRF_SEQ 0x00000010    /*  Frame sequence error for Virtual Channel 3 */
#define BITM_MIPICSI2_INT_ST_FAP_IDI_IDI_VC2_ERRF_SEQ 0x00000008    /*  Frame sequence error for Virtual Channel 2 */
#define BITM_MIPICSI2_INT_ST_FAP_IDI_IDI_VC1_ERRF_SEQ 0x00000004    /*  Frame sequence error for Virtual Channel 1 */
#define BITM_MIPICSI2_INT_ST_FAP_IDI_IDI_VC0_ERRF_SEQ 0x00000002    /*  Frame sequence error for Virtual Channel 0 */
#define BITM_MIPICSI2_INT_ST_FAP_IDI_IDI_ERRWC 0x00000001    /*  IDI Word Count mismatch error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_ST_FAP_PHY              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_ST_FAP_PHY_ERRCONTENTIONLP1  2            /*  LP1 contention error from Lane0 */
#define BITP_MIPICSI2_INT_ST_FAP_PHY_ERRCONTENTIONLP0  1            /*  LP0 contention error from Lane0 */
#define BITP_MIPICSI2_INT_ST_FAP_PHY_TO_HS_TX  0            /*  High speed transmission timeout counter reached */
#define BITM_MIPICSI2_INT_ST_FAP_PHY_ERRCONTENTIONLP1 0x00000004    /*  LP1 contention error from Lane0 */
#define BITM_MIPICSI2_INT_ST_FAP_PHY_ERRCONTENTIONLP0 0x00000002    /*  LP0 contention error from Lane0 */
#define BITM_MIPICSI2_INT_ST_FAP_PHY_TO_HS_TX 0x00000001    /*  High speed transmission timeout counter reached */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_MASK_FAP_N_VPG          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_MASK_FAP_N_VPG_MASK_VPG_PKT_LOST  0            /*  Mask for vpg_pkt_lost */
#define BITM_MIPICSI2_INT_MASK_FAP_N_VPG_MASK_VPG_PKT_LOST 0x00000001    /*  Mask for vpg_pkt_lost */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_FORCE_FAP_VPG           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_FORCE_FAP_VPG_FORCE_VPG_PKT_LOST  0            /*  Force for vpg_pkt_lost */
#define BITM_MIPICSI2_INT_FORCE_FAP_VPG_FORCE_VPG_PKT_LOST 0x00000001    /*  Force for vpg_pkt_lost */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_MASK_FAP_N_IDI          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_FIFO_OVERFLOW  9            /*  Mask for idi_fifo_overflow */
#define BITP_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_VC3_ERRL_SEQ  8            /*  Mask for idi_vc3_errl_seq */
#define BITP_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_VC2_ERRL_SEQ  7            /*  Mask for idi_vc2_errl_seq */
#define BITP_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_VC1_ERRL_SEQ  6            /*  Mask for idi_vc1_errl_seq */
#define BITP_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_VC0_ERRL_SEQ  5            /*  Mask for idi_vc0_errl_seq */
#define BITP_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_VC3_ERRF_SEQ  4            /*  Mask for idi_vc3_errf_seq */
#define BITP_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_VC2_ERRF_SEQ  3            /*  Mask for idi_vc2_errf_seq */
#define BITP_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_VC1_ERRF_SEQ  2            /*  Mask for idi_vc1_errf_seq */
#define BITP_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_VC0_ERRF_SEQ  1            /*  Mask for idi_vc0_errf_seq */
#define BITP_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_ERRWC  0            /*  Mask for idi_errwc */
#define BITM_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_FIFO_OVERFLOW 0x00000200    /*  Mask for idi_fifo_overflow */
#define BITM_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_VC3_ERRL_SEQ 0x00000100    /*  Mask for idi_vc3_errl_seq */
#define BITM_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_VC2_ERRL_SEQ 0x00000080    /*  Mask for idi_vc2_errl_seq */
#define BITM_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_VC1_ERRL_SEQ 0x00000040    /*  Mask for idi_vc1_errl_seq */
#define BITM_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_VC0_ERRL_SEQ 0x00000020    /*  Mask for idi_vc0_errl_seq */
#define BITM_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_VC3_ERRF_SEQ 0x00000010    /*  Mask for idi_vc3_errf_seq */
#define BITM_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_VC2_ERRF_SEQ 0x00000008    /*  Mask for idi_vc2_errf_seq */
#define BITM_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_VC1_ERRF_SEQ 0x00000004    /*  Mask for idi_vc1_errf_seq */
#define BITM_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_VC0_ERRF_SEQ 0x00000002    /*  Mask for idi_vc0_errf_seq */
#define BITM_MIPICSI2_INT_MASK_FAP_N_IDI_MASK_IDI_ERRWC 0x00000001    /*  Mask for idi_errwc */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_FORCE_FAP_IDI           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_FIFO_OVERFLOW  9            /*  Force for idi_fifo_overflow */
#define BITP_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_VC3_ERRL_SEQ  8            /*  Force for idi_vc3_errl_seq */
#define BITP_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_VC2_ERRL_SEQ  7            /*  Force for idi_vc2_errl_seq */
#define BITP_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_VC1_ERRL_SEQ  6            /*  Force for idi_vc1_errl_seq */
#define BITP_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_VC0_ERRL_SEQ  5            /*  Force for idi_vc0_errl_seq */
#define BITP_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_VC3_ERRF_SEQ  4            /*  Force for idi_vc3_errf_seq */
#define BITP_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_VC2_ERRF_SEQ  3            /*  Force for idi_vc2_errf_seq */
#define BITP_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_VC1_ERRF_SEQ  2            /*  Force for idi_vc1_errf_seq */
#define BITP_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_VC0_ERRF_SEQ  1            /*  Force for idi_vc0_errf_seq */
#define BITP_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_ERRWC  0            /*  Force for idi_errwc */
#define BITM_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_FIFO_OVERFLOW 0x00000200    /*  Force for idi_fifo_overflow */
#define BITM_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_VC3_ERRL_SEQ 0x00000100    /*  Force for idi_vc3_errl_seq */
#define BITM_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_VC2_ERRL_SEQ 0x00000080    /*  Force for idi_vc2_errl_seq */
#define BITM_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_VC1_ERRL_SEQ 0x00000040    /*  Force for idi_vc1_errl_seq */
#define BITM_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_VC0_ERRL_SEQ 0x00000020    /*  Force for idi_vc0_errl_seq */
#define BITM_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_VC3_ERRF_SEQ 0x00000010    /*  Force for idi_vc3_errf_seq */
#define BITM_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_VC2_ERRF_SEQ 0x00000008    /*  Force for idi_vc2_errf_seq */
#define BITM_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_VC1_ERRF_SEQ 0x00000004    /*  Force for idi_vc1_errf_seq */
#define BITM_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_VC0_ERRF_SEQ 0x00000002    /*  Force for idi_vc0_errf_seq */
#define BITM_MIPICSI2_INT_FORCE_FAP_IDI_FORCE_IDI_ERRWC 0x00000001    /*  Force for idi_errwc */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_MASK_FAP_N_PHY          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_MASK_FAP_N_PHY_MASK_ERRCONTENTIONLP1  2            /*  Mask for errcontentionlp1 */
#define BITP_MIPICSI2_INT_MASK_FAP_N_PHY_MASK_ERRCONTENTIONLP0  1            /*  Mask for errcontentionlp0 */
#define BITP_MIPICSI2_INT_MASK_FAP_N_PHY_MASK_TO_HS_TX  0            /*  Mask for to_hs_tx */
#define BITM_MIPICSI2_INT_MASK_FAP_N_PHY_MASK_ERRCONTENTIONLP1 0x00000004    /*  Mask for errcontentionlp1 */
#define BITM_MIPICSI2_INT_MASK_FAP_N_PHY_MASK_ERRCONTENTIONLP0 0x00000002    /*  Mask for errcontentionlp0 */
#define BITM_MIPICSI2_INT_MASK_FAP_N_PHY_MASK_TO_HS_TX 0x00000001    /*  Mask for to_hs_tx */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_FORCE_FAP_PHY           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_FORCE_FAP_PHY_FORCE_ERRCONTENTIONLP1  2            /*  Force for errcontentionlp1 */
#define BITP_MIPICSI2_INT_FORCE_FAP_PHY_FORCE_ERRCONTENTIONLP0  1            /*  Force for errcontentionlp0 */
#define BITP_MIPICSI2_INT_FORCE_FAP_PHY_FORCE_TO_HS_TX  0            /*  Force for to_hs_tx */
#define BITM_MIPICSI2_INT_FORCE_FAP_PHY_FORCE_ERRCONTENTIONLP1 0x00000004    /*  Force for errcontentionlp1 */
#define BITM_MIPICSI2_INT_FORCE_FAP_PHY_FORCE_ERRCONTENTIONLP0 0x00000002    /*  Force for errcontentionlp0 */
#define BITM_MIPICSI2_INT_FORCE_FAP_PHY_FORCE_TO_HS_TX 0x00000001    /*  Force for to_hs_tx */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_IDI_AP_STATUS               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_IDI_AP_STATUS_INPUT_PARITY_ERROR  2            /*  Input parity check error */
#define BITP_MIPICSI2_IDI_AP_STATUS_REG_PARITY_ERROR  0            /*  Register parity check error */
#define BITM_MIPICSI2_IDI_AP_STATUS_INPUT_PARITY_ERROR 0x00000004    /*  Input parity check error */
#define BITM_MIPICSI2_IDI_AP_STATUS_REG_PARITY_ERROR 0x00000001    /*  Register parity check error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_LANE_MGR_AP_STATUS          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_LANE_MGR_AP_STATUS_REG_PARITY_ERROR  0            /*  Register parity check error */
#define BITM_MIPICSI2_LANE_MGR_AP_STATUS_REG_PARITY_ERROR 0x00000001    /*  Register parity check error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_PHY_IF_CTRL_AP_STATUS       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_PHY_IF_CTRL_AP_STATUS_SIG_PULSE_ERROR  1            /*  Single pulse check error */
#define BITP_MIPICSI2_PHY_IF_CTRL_AP_STATUS_REG_PARITY_ERROR  0            /*  Register parity check error */
#define BITM_MIPICSI2_PHY_IF_CTRL_AP_STATUS_SIG_PULSE_ERROR 0x00000002    /*  Single pulse check error */
#define BITM_MIPICSI2_PHY_IF_CTRL_AP_STATUS_REG_PARITY_ERROR 0x00000001    /*  Register parity check error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_REG_BANK_AP_STATUS          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_REG_BANK_AP_STATUS_SIG_PULSE_ERROR  1            /*  Single pulse check error */
#define BITP_MIPICSI2_REG_BANK_AP_STATUS_REG_PARITY_ERROR  0            /*  Register parity check error */
#define BITM_MIPICSI2_REG_BANK_AP_STATUS_SIG_PULSE_ERROR 0x00000002    /*  Single pulse check error */
#define BITM_MIPICSI2_REG_BANK_AP_STATUS_REG_PARITY_ERROR 0x00000001    /*  Register parity check error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_IDI_FIFOCTRL_AP_STATUS      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_IDI_FIFOCTRL_AP_STATUS_REG_PARITY_ERROR  0            /*  Register parity check error */
#define BITM_MIPICSI2_IDI_FIFOCTRL_AP_STATUS_REG_PARITY_ERROR 0x00000001    /*  Register parity check error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_PKT_BUILDER_AP_STATUS       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_PKT_BUILDER_AP_STATUS_REG_PARITY_ERROR  0            /*  Register parity check error */
#define BITM_MIPICSI2_PKT_BUILDER_AP_STATUS_REG_PARITY_ERROR 0x00000001    /*  Register parity check error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_ERR_HANDLER_AP_STATUS       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_ERR_HANDLER_AP_STATUS_DUPLICATE_ERROR  3            /*  Duplicate model check error */
#define BITM_MIPICSI2_ERR_HANDLER_AP_STATUS_DUPLICATE_ERROR 0x00000008    /*  Duplicate model check error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_FIFO_ADAPTER_AP_STATUS      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_FIFO_ADAPTER_AP_STATUS_REG_PARITY_ERROR  0            /*  Register parity check error */
#define BITM_MIPICSI2_FIFO_ADAPTER_AP_STATUS_REG_PARITY_ERROR 0x00000001    /*  Register parity check error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_ELASTBUF_AP_STATUS          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_ELASTBUF_AP_STATUS_DUPLICATE_ERROR  3            /*  Duplicate model check error */
#define BITM_MIPICSI2_ELASTBUF_AP_STATUS_DUPLICATE_ERROR 0x00000008    /*  Duplicate model check error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_ECF_AP_STATUS               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_ECF_AP_STATUS_REG_PARITY_ERROR  0            /*  Register parity check error */
#define BITM_MIPICSI2_ECF_AP_STATUS_REG_PARITY_ERROR 0x00000001    /*  Register parity check error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_CMU_AP_STATUS               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_CMU_AP_STATUS_REG_PARITY_ERROR  0            /*  Register parity check error */
#define BITM_MIPICSI2_CMU_AP_STATUS_REG_PARITY_ERROR 0x00000001    /*  Register parity check error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_AMBAAPBINTF_AP_STATUS       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_AMBAAPBINTF_AP_STATUS_INPUT_PARITY_ERROR  2            /*  Input parity check error */
#define BITP_MIPICSI2_AMBAAPBINTF_AP_STATUS_SIG_PULSE_ERROR  1            /*  Single pulse check error */
#define BITP_MIPICSI2_AMBAAPBINTF_AP_STATUS_REG_PARITY_ERROR  0            /*  Register parity check error */
#define BITM_MIPICSI2_AMBAAPBINTF_AP_STATUS_INPUT_PARITY_ERROR 0x00000004    /*  Input parity check error */
#define BITM_MIPICSI2_AMBAAPBINTF_AP_STATUS_SIG_PULSE_ERROR 0x00000002    /*  Single pulse check error */
#define BITM_MIPICSI2_AMBAAPBINTF_AP_STATUS_REG_PARITY_ERROR 0x00000001    /*  Register parity check error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_CHANNEL_SEL_AP_STATUS       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_CHANNEL_SEL_AP_STATUS_DUPLICATE_ERROR  3            /*  Duplicate model check error */
#define BITM_MIPICSI2_CHANNEL_SEL_AP_STATUS_DUPLICATE_ERROR 0x00000008    /*  Duplicate model check error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_MASK_N_IDI_AP_STATUS        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_MASK_N_IDI_AP_STATUS_MASK_INPUT_PARITY_ERROR  2            /*  Mask for input_parity_error */
#define BITP_MIPICSI2_MASK_N_IDI_AP_STATUS_MASK_REG_PARITY_ERROR  0            /*  Mask for reg_parity_error */
#define BITM_MIPICSI2_MASK_N_IDI_AP_STATUS_MASK_INPUT_PARITY_ERROR 0x00000004    /*  Mask for input_parity_error */
#define BITM_MIPICSI2_MASK_N_IDI_AP_STATUS_MASK_REG_PARITY_ERROR 0x00000001    /*  Mask for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_FORCE_IDI_AP_STATUS         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_FORCE_IDI_AP_STATUS_FORCE_INPUT_PARITY_ERROR  2            /*  Force for input_parity_error */
#define BITP_MIPICSI2_FORCE_IDI_AP_STATUS_FORCE_REG_PARITY_ERROR  0            /*  Force for reg_parity_error */
#define BITM_MIPICSI2_FORCE_IDI_AP_STATUS_FORCE_INPUT_PARITY_ERROR 0x00000004    /*  Force for input_parity_error */
#define BITM_MIPICSI2_FORCE_IDI_AP_STATUS_FORCE_REG_PARITY_ERROR 0x00000001    /*  Force for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_MASK_N_LANE_MGR_AP_STATUS   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_MASK_N_LANE_MGR_AP_STATUS_MASK_REG_PARITY_ERROR  0            /*  Mask for reg_parity_error */
#define BITM_MIPICSI2_MASK_N_LANE_MGR_AP_STATUS_MASK_REG_PARITY_ERROR 0x00000001    /*  Mask for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_FORCE_LANE_MGR_AP_STATUS    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_FORCE_LANE_MGR_AP_STATUS_FORCE_REG_PARITY_ERROR  0            /*  Force for reg_parity_error */
#define BITM_MIPICSI2_FORCE_LANE_MGR_AP_STATUS_FORCE_REG_PARITY_ERROR 0x00000001    /*  Force for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_MASK_N_PHY_IF_CTRL_AP_STATUS Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_MASK_N_PHY_IF_CTRL_AP_STATUS_MASK_SIG_PULSE_ERROR  1            /*  Mask for sig_pulse_error */
#define BITP_MIPICSI2_MASK_N_PHY_IF_CTRL_AP_STATUS_MASK_REG_PARITY_ERROR  0            /*  Mask for reg_parity_error */
#define BITM_MIPICSI2_MASK_N_PHY_IF_CTRL_AP_STATUS_MASK_SIG_PULSE_ERROR 0x00000002    /*  Mask for sig_pulse_error */
#define BITM_MIPICSI2_MASK_N_PHY_IF_CTRL_AP_STATUS_MASK_REG_PARITY_ERROR 0x00000001    /*  Mask for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_FORCE_PHY_IF_CTRL_AP_STATUS Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_FORCE_PHY_IF_CTRL_AP_STATUS_FORCE_SIG_PULSE_ERROR  1            /*  Force for sig_pulse_error */
#define BITP_MIPICSI2_FORCE_PHY_IF_CTRL_AP_STATUS_FORCE_REG_PARITY_ERROR  0            /*  Force for reg_parity_error */
#define BITM_MIPICSI2_FORCE_PHY_IF_CTRL_AP_STATUS_FORCE_SIG_PULSE_ERROR 0x00000002    /*  Force for sig_pulse_error */
#define BITM_MIPICSI2_FORCE_PHY_IF_CTRL_AP_STATUS_FORCE_REG_PARITY_ERROR 0x00000001    /*  Force for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_MASK_N_REG_BANK_AP_STATUS   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_MASK_N_REG_BANK_AP_STATUS_MASK_SIG_PULSE_ERROR  1            /*  Mask for sig_pulse_error */
#define BITP_MIPICSI2_MASK_N_REG_BANK_AP_STATUS_MASK_REG_PARITY_ERROR  0            /*  Mask for reg_parity_error */
#define BITM_MIPICSI2_MASK_N_REG_BANK_AP_STATUS_MASK_SIG_PULSE_ERROR 0x00000002    /*  Mask for sig_pulse_error */
#define BITM_MIPICSI2_MASK_N_REG_BANK_AP_STATUS_MASK_REG_PARITY_ERROR 0x00000001    /*  Mask for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_FORCE_REG_BANK_AP_STATUS    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_FORCE_REG_BANK_AP_STATUS_FORCE_SIG_PULSE_ERROR  1            /*  Force for sig_pulse_error */
#define BITP_MIPICSI2_FORCE_REG_BANK_AP_STATUS_FORCE_REG_PARITY_ERROR  0            /*  Force for reg_parity_error */
#define BITM_MIPICSI2_FORCE_REG_BANK_AP_STATUS_FORCE_SIG_PULSE_ERROR 0x00000002    /*  Force for sig_pulse_error */
#define BITM_MIPICSI2_FORCE_REG_BANK_AP_STATUS_FORCE_REG_PARITY_ERROR 0x00000001    /*  Force for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_MASK_N_IDI_FIFOCTRL_AP_STATUS Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_MASK_N_IDI_FIFOCTRL_AP_STATUS_MASK_REG_PARITY_ERROR  0            /*  Mask for reg_parity_error */
#define BITM_MIPICSI2_MASK_N_IDI_FIFOCTRL_AP_STATUS_MASK_REG_PARITY_ERROR 0x00000001    /*  Mask for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_FORCE_IDI_FIFOCTRL_AP_STATUS Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_FORCE_IDI_FIFOCTRL_AP_STATUS_FORCE_REG_PARITY_ERROR  0            /*  Force for reg_parity_error */
#define BITM_MIPICSI2_FORCE_IDI_FIFOCTRL_AP_STATUS_FORCE_REG_PARITY_ERROR 0x00000001    /*  Force for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_MASK_N_PKT_BUILDER_AP_STATUS Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_MASK_N_PKT_BUILDER_AP_STATUS_MASK_REG_PARITY_ERROR  0            /*  Mask for reg_parity_error */
#define BITM_MIPICSI2_MASK_N_PKT_BUILDER_AP_STATUS_MASK_REG_PARITY_ERROR 0x00000001    /*  Mask for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_FORCE_PKT_BUILDER_AP_STATUS Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_FORCE_PKT_BUILDER_AP_STATUS_FORCE_REG_PARITY_ERROR  0            /*  Force for reg_parity_error */
#define BITM_MIPICSI2_FORCE_PKT_BUILDER_AP_STATUS_FORCE_REG_PARITY_ERROR 0x00000001    /*  Force for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_MASK_N_ERR_HANDLER_AP_STATUS Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_MASK_N_ERR_HANDLER_AP_STATUS_MASK_DUPLICATE_ERROR  3            /*  Mask for duplicate_error */
#define BITM_MIPICSI2_MASK_N_ERR_HANDLER_AP_STATUS_MASK_DUPLICATE_ERROR 0x00000008    /*  Mask for duplicate_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_FORCE_ERR_HANDLER_AP_STATUS Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_FORCE_ERR_HANDLER_AP_STATUS_FORCE_DUPLICATE_ERROR  3            /*  Force for duplicate_error */
#define BITM_MIPICSI2_FORCE_ERR_HANDLER_AP_STATUS_FORCE_DUPLICATE_ERROR 0x00000008    /*  Force for duplicate_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_MASK_N_FIFO_ADAPTER_AP_STATUS Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_MASK_N_FIFO_ADAPTER_AP_STATUS_MASK_REG_PARITY_ERROR  0            /*  Mask for reg_parity_error */
#define BITM_MIPICSI2_MASK_N_FIFO_ADAPTER_AP_STATUS_MASK_REG_PARITY_ERROR 0x00000001    /*  Mask for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_FORCE_FIFO_ADAPTER_AP_STATUS Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_FORCE_FIFO_ADAPTER_AP_STATUS_FORCE_REG_PARITY_ERROR  0            /*  Force for reg_parity_error */
#define BITM_MIPICSI2_FORCE_FIFO_ADAPTER_AP_STATUS_FORCE_REG_PARITY_ERROR 0x00000001    /*  Force for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_MASK_N_ELASTBUF_AP_STATUS   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_MASK_N_ELASTBUF_AP_STATUS_MASK_DUPLICATE_ERROR  3            /*  Mask for duplicate_error */
#define BITM_MIPICSI2_MASK_N_ELASTBUF_AP_STATUS_MASK_DUPLICATE_ERROR 0x00000008    /*  Mask for duplicate_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_FORCE_ELASTBUF_AP_STATUS    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_FORCE_ELASTBUF_AP_STATUS_FORCE_DUPLICATE_ERROR  3            /*  Force for duplicate_error */
#define BITM_MIPICSI2_FORCE_ELASTBUF_AP_STATUS_FORCE_DUPLICATE_ERROR 0x00000008    /*  Force for duplicate_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_MASK_N_ECF_AP_STATUS        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_MASK_N_ECF_AP_STATUS_MASK_REG_PARITY_ERROR  0            /*  Mask for reg_parity_error */
#define BITM_MIPICSI2_MASK_N_ECF_AP_STATUS_MASK_REG_PARITY_ERROR 0x00000001    /*  Mask for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_FORCE_ECF_AP_STATUS         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_FORCE_ECF_AP_STATUS_FORCE_REG_PARITY_ERROR  0            /*  Force for reg_parity_error */
#define BITM_MIPICSI2_FORCE_ECF_AP_STATUS_FORCE_REG_PARITY_ERROR 0x00000001    /*  Force for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_MASK_N_CMU_AP_STATUS        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_MASK_N_CMU_AP_STATUS_MASK_REG_PARITY_ERROR  0            /*  Mask for reg_parity_error */
#define BITM_MIPICSI2_MASK_N_CMU_AP_STATUS_MASK_REG_PARITY_ERROR 0x00000001    /*  Mask for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_FORCE_CMU_AP_STATUS         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_FORCE_CMU_AP_STATUS_FORCE_REG_PARITY_ERROR  0            /*  Force for reg_parity_error */
#define BITM_MIPICSI2_FORCE_CMU_AP_STATUS_FORCE_REG_PARITY_ERROR 0x00000001    /*  Force for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_MASK_N_AMBAAPBINTF_AP_STATUS Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_MASK_N_AMBAAPBINTF_AP_STATUS_MASK_INPUT_PARITY_ERROR  2            /*  Mask for input_parity_error */
#define BITP_MIPICSI2_MASK_N_AMBAAPBINTF_AP_STATUS_MASK_SIG_PULSE_ERROR  1            /*  Mask for sig_pulse_error */
#define BITP_MIPICSI2_MASK_N_AMBAAPBINTF_AP_STATUS_MASK_REG_PARITY_ERROR  0            /*  Mask for reg_parity_error */
#define BITM_MIPICSI2_MASK_N_AMBAAPBINTF_AP_STATUS_MASK_INPUT_PARITY_ERROR 0x00000004    /*  Mask for input_parity_error */
#define BITM_MIPICSI2_MASK_N_AMBAAPBINTF_AP_STATUS_MASK_SIG_PULSE_ERROR 0x00000002    /*  Mask for sig_pulse_error */
#define BITM_MIPICSI2_MASK_N_AMBAAPBINTF_AP_STATUS_MASK_REG_PARITY_ERROR 0x00000001    /*  Mask for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_FORCE_AMBAAPBINTF_AP_STATUS Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_FORCE_AMBAAPBINTF_AP_STATUS_FORCE_INPUT_PARITY_ERROR  2            /*  Force for input_parity_error */
#define BITP_MIPICSI2_FORCE_AMBAAPBINTF_AP_STATUS_FORCE_SIG_PULSE_ERROR  1            /*  Force for sig_pulse_error */
#define BITP_MIPICSI2_FORCE_AMBAAPBINTF_AP_STATUS_FORCE_REG_PARITY_ERROR  0            /*  Force for reg_parity_error */
#define BITM_MIPICSI2_FORCE_AMBAAPBINTF_AP_STATUS_FORCE_INPUT_PARITY_ERROR 0x00000004    /*  Force for input_parity_error */
#define BITM_MIPICSI2_FORCE_AMBAAPBINTF_AP_STATUS_FORCE_SIG_PULSE_ERROR 0x00000002    /*  Force for sig_pulse_error */
#define BITM_MIPICSI2_FORCE_AMBAAPBINTF_AP_STATUS_FORCE_REG_PARITY_ERROR 0x00000001    /*  Force for reg_parity_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_MASK_N_CHANNEL_SEL_AP_STATUS Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_MASK_N_CHANNEL_SEL_AP_STATUS_MASK_DUPLICATE_ERROR  3            /*  Mask for duplicate_error */
#define BITM_MIPICSI2_MASK_N_CHANNEL_SEL_AP_STATUS_MASK_DUPLICATE_ERROR 0x00000008    /*  Mask for duplicate_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_FORCE_CHANNEL_SEL_AP_STATUS Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_FORCE_CHANNEL_SEL_AP_STATUS_FORCE_DUPLICATE_ERROR  3            /*  Force for duplicate_error */
#define BITM_MIPICSI2_FORCE_CHANNEL_SEL_AP_STATUS_FORCE_DUPLICATE_ERROR 0x00000008    /*  Force for duplicate_error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_ST_DIAG_MAIN            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_ST_DIAG_MAIN_INT_ST_FAP_PHY  4            /*  Status of INT_ST_PHY interrupt source group */
#define BITP_MIPICSI2_INT_ST_DIAG_MAIN_INT_ST_FAP_IDI  2            /*  Status of INT_ST_IDI interrupt source group */
#define BITP_MIPICSI2_INT_ST_DIAG_MAIN_INT_ST_FAP_VPG  1            /*  Status of INT_ST_VPG interrupt source group */
#define BITP_MIPICSI2_INT_ST_DIAG_MAIN_INT_ST_DIAG0  0            /*  Status of Internal Diagnosis interrupt source group 0 */
#define BITM_MIPICSI2_INT_ST_DIAG_MAIN_INT_ST_FAP_PHY 0x00000010    /*  Status of INT_ST_PHY interrupt source group */
#define BITM_MIPICSI2_INT_ST_DIAG_MAIN_INT_ST_FAP_IDI 0x00000004    /*  Status of INT_ST_IDI interrupt source group */
#define BITM_MIPICSI2_INT_ST_DIAG_MAIN_INT_ST_FAP_VPG 0x00000002    /*  Status of INT_ST_VPG interrupt source group */
#define BITM_MIPICSI2_INT_ST_DIAG_MAIN_INT_ST_DIAG0 0x00000001    /*  Status of Internal Diagnosis interrupt source group 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_ST_DIAG0                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_CHANNEL_SEL 20            /*  Internal Diagnosis error for channel select block */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_SYNC 19            /*  Internal Diagnosis error for synchronizer */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_HDDP_ECCMULERR 18            /*  Internal Diagnosis multiple-bit error for header datapath with ECC */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_HDDP_ECCERR 17            /*  Internal Diagnosis error for header datapath with ECC */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_PLDP_CRCERR 16            /*  Internal Diagnosis error for payload datapath with CRC */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_PLDP_ECCMULERR 15            /*  Internal Diagnosis multiple-bit error for payload datapath with ECC */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_PLDP_ECCERR 14            /*  Internal Diagnosis error for payload datapath with ECC */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_AMBAAPBINTF 13            /*  Internal Diagnosis error for APB interface */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_CMU 12            /*  Internal Diagnosis error for Clock Manager Unit */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_ECF 11            /*  Internal Diagnosis error for ERR correction functional block */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_ELASTBUF 10            /*  Internal Diagnosis error for Elasticity buffer */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_FIFO_ADAPTER  9            /*  Internal Diagnosis error for FIFO adapter */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_ERR_HANDLER  8            /*  Internal Diagnosis error for Error handler */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_PKT_BUILDER  7            /*  Internal Diagnosis error for Packet builder */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_IDI_CH_FIFO_CONTROL  6            /*  Internal Diagnosis error for IDI Channel FIFO control */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_REG_BANK  4            /*  Internal Diagnosis error for Register Bank */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_PHY_IF_CTRL  3            /*  Internal Diagnosis error for PHY interface control */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_LANE_MGR  2            /*  Internal Diagnosis error for Lane Management */
#define BITP_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_IDI  1            /*  Internal Diagnosis error for IDI interface */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_CHANNEL_SEL 0x00100000    /*  Internal Diagnosis error for channel select block */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_SYNC 0x00080000    /*  Internal Diagnosis error for synchronizer */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_HDDP_ECCMULERR 0x00040000    /*  Internal Diagnosis multiple-bit error for header datapath with ECC */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_HDDP_ECCERR 0x00020000    /*  Internal Diagnosis error for header datapath with ECC */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_PLDP_CRCERR 0x00010000    /*  Internal Diagnosis error for payload datapath with CRC */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_PLDP_ECCMULERR 0x00008000    /*  Internal Diagnosis multiple-bit error for payload datapath with ECC */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_PLDP_ECCERR 0x00004000    /*  Internal Diagnosis error for payload datapath with ECC */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_AMBAAPBINTF 0x00002000    /*  Internal Diagnosis error for APB interface */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_CMU 0x00001000    /*  Internal Diagnosis error for Clock Manager Unit */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_ECF 0x00000800    /*  Internal Diagnosis error for ERR correction functional block */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_ELASTBUF 0x00000400    /*  Internal Diagnosis error for Elasticity buffer */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_FIFO_ADAPTER 0x00000200    /*  Internal Diagnosis error for FIFO adapter */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_ERR_HANDLER 0x00000100    /*  Internal Diagnosis error for Error handler */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_PKT_BUILDER 0x00000080    /*  Internal Diagnosis error for Packet builder */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_IDI_CH_FIFO_CONTROL 0x00000040    /*  Internal Diagnosis error for IDI Channel FIFO control */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_REG_BANK 0x00000010    /*  Internal Diagnosis error for Register Bank */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_PHY_IF_CTRL 0x00000008    /*  Internal Diagnosis error for PHY interface control */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_LANE_MGR 0x00000004    /*  Internal Diagnosis error for Lane Management */
#define BITM_MIPICSI2_INT_ST_DIAG0_INT_ST_DIAG_IDI 0x00000002    /*  Internal Diagnosis error for IDI interface */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_MASK_N_DIAG0            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_CHANNEL_SEL 20            /*  Mask for diagnosis error of channel select block */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_SYNC 19            /*  Mask for diagnosis error of synchronizer */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_HDDP_ECCMULERR 18            /*  Mask for internal diagnosis multiple-bit error of header datapath with ECC */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_HDDP_ECCERR 17            /*  Mask for diagnosis error of header datapath with ECC */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_PLDP_CRCERR 16            /*  Mask for internal diagnosis error of payload datapath with CRC */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_PLDP_ECCMULERR 15            /*  Mask for internal diagnosis multiple-bit error of payload datapath with ECC */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_PLDP_ECCERR 14            /*  Mask for internal diagnosis error of payload datapath with ECC */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_AMBAAPBINTF 13            /*  Mask for internal diagnosis of ambaapbintf */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_CMU 12            /*  Mask for internal diagnosis of cmu */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_ECF 11            /*  Mask for internal diagnosis of ecf */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_ELASTBUF 10            /*  Mask for internal diagnosis of elastbuf */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_FIFO_ADAPTER  9            /*  Mask for internal diagnosis of fifo_adapter */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_ERR_HANDLER  8            /*  Mask for internal diagnosis of err_handler */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_PKT_BUILDER  7            /*  Mask for internal diagnosis of pkt_builder */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_IDI_CH_FIFO_CONTROL  6            /*  Mask for internal diagnosis of idi_ch_fifo_control */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_REG_BANK  4            /*  Mask for internal diagnosis of reg_bank */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_PHY_IF_CTRL  3            /*  Mask for internal diagnosis of phy_if_ctrl */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_LANE_MGR  2            /*  Mask for internal diagnosis of lane_mgr */
#define BITP_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_IDI  1            /*  Mask for internal diagnosis of id */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_CHANNEL_SEL 0x00100000    /*  Mask for diagnosis error of channel select block */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_SYNC 0x00080000    /*  Mask for diagnosis error of synchronizer */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_HDDP_ECCMULERR 0x00040000    /*  Mask for internal diagnosis multiple-bit error of header datapath with ECC */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_HDDP_ECCERR 0x00020000    /*  Mask for diagnosis error of header datapath with ECC */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_PLDP_CRCERR 0x00010000    /*  Mask for internal diagnosis error of payload datapath with CRC */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_PLDP_ECCMULERR 0x00008000    /*  Mask for internal diagnosis multiple-bit error of payload datapath with ECC */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_PLDP_ECCERR 0x00004000    /*  Mask for internal diagnosis error of payload datapath with ECC */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_AMBAAPBINTF 0x00002000    /*  Mask for internal diagnosis of ambaapbintf */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_CMU 0x00001000    /*  Mask for internal diagnosis of cmu */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_ECF 0x00000800    /*  Mask for internal diagnosis of ecf */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_ELASTBUF 0x00000400    /*  Mask for internal diagnosis of elastbuf */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_FIFO_ADAPTER 0x00000200    /*  Mask for internal diagnosis of fifo_adapter */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_ERR_HANDLER 0x00000100    /*  Mask for internal diagnosis of err_handler */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_PKT_BUILDER 0x00000080    /*  Mask for internal diagnosis of pkt_builder */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_IDI_CH_FIFO_CONTROL 0x00000040    /*  Mask for internal diagnosis of idi_ch_fifo_control */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_REG_BANK 0x00000010    /*  Mask for internal diagnosis of reg_bank */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_PHY_IF_CTRL 0x00000008    /*  Mask for internal diagnosis of phy_if_ctrl */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_LANE_MGR 0x00000004    /*  Mask for internal diagnosis of lane_mgr */
#define BITM_MIPICSI2_INT_MASK_N_DIAG0_MASK_N_DIAG_IDI 0x00000002    /*  Mask for internal diagnosis of id */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_INT_FORCE_DIAG0             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_CHANNEL_SEL 20            /*  Force for diagnosis error of channel select block */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_SYNC 19            /*  Force for diagnosis error of synchronizer */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_HDDP_ECCMULERR 18            /*  Force for internal diagnosis multiple-bit error of payload header with ECC */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_HDDP_ECCERR 17            /*  Force for diagnosis error of header datapath with ECC */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_PLDP_CRCERR 16            /*  Force for internal diagnosis error of payload datapath with crc */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_PLDP_ECCMULERR 15            /*  Force for internal diagnosis multiple-bit error of payload datapath with ECC */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_PLDP_ECCERR 14            /*  Force for internal diagnosis error of payload datapath with ECC */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_AMBAAPBINTF 13            /*  Force for internal diagnosis of ambaapbintf */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_CMU 12            /*  Force for internal diagnosis of cmu */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_ECF 11            /*  Force for internal diagnosis of ecf */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_ELASTBUF 10            /*  Force for internal diagnosis of elastbuf */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_FIFO_ADAPTER  9            /*  Force for internal diagnosis of fifo_adapter */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_ERR_HANDLER  8            /*  Force for internal diagnosis of err_handler */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_PKT_BUILDER  7            /*  Force for internal diagnosis of pkt_builder */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_IDI_CH_FIFO_CONTROL  6            /*  force for internal diagnosis of idi_ch_fifo_control */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_REG_BANK  4            /*  Force for internal diagnosis of reg_bank */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_PHY_IF_CTRL  3            /*  Force for internal diagnosis of phy_if_ctrl */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_LANE_MGR  2            /*  Force for internal diagnosis of lane_mgr */
#define BITP_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_IDI  1            /*  Force for internal diagnosis of id */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_CHANNEL_SEL 0x00100000    /*  Force for diagnosis error of channel select block */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_SYNC 0x00080000    /*  Force for diagnosis error of synchronizer */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_HDDP_ECCMULERR 0x00040000    /*  Force for internal diagnosis multiple-bit error of payload header with ECC */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_HDDP_ECCERR 0x00020000    /*  Force for diagnosis error of header datapath with ECC */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_PLDP_CRCERR 0x00010000    /*  Force for internal diagnosis error of payload datapath with crc */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_PLDP_ECCMULERR 0x00008000    /*  Force for internal diagnosis multiple-bit error of payload datapath with ECC */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_PLDP_ECCERR 0x00004000    /*  Force for internal diagnosis error of payload datapath with ECC */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_AMBAAPBINTF 0x00002000    /*  Force for internal diagnosis of ambaapbintf */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_CMU 0x00001000    /*  Force for internal diagnosis of cmu */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_ECF 0x00000800    /*  Force for internal diagnosis of ecf */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_ELASTBUF 0x00000400    /*  Force for internal diagnosis of elastbuf */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_FIFO_ADAPTER 0x00000200    /*  Force for internal diagnosis of fifo_adapter */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_ERR_HANDLER 0x00000100    /*  Force for internal diagnosis of err_handler */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_PKT_BUILDER 0x00000080    /*  Force for internal diagnosis of pkt_builder */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_IDI_CH_FIFO_CONTROL 0x00000040    /*  force for internal diagnosis of idi_ch_fifo_control */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_REG_BANK 0x00000010    /*  Force for internal diagnosis of reg_bank */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_PHY_IF_CTRL 0x00000008    /*  Force for internal diagnosis of phy_if_ctrl */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_LANE_MGR 0x00000004    /*  Force for internal diagnosis of lane_mgr */
#define BITM_MIPICSI2_INT_FORCE_DIAG0_FORCE_DIAG_IDI 0x00000002    /*  Force for internal diagnosis of id */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_PLDP_ECC_SYNDOUT            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_PLDP_ECC_SYNDOUT_PLDP_ECC_SYNDOUT  0            /*  Error syndrome output indicates the location of an payload error */
#define BITM_MIPICSI2_PLDP_ECC_SYNDOUT_PLDP_ECC_SYNDOUT 0x000000FF    /*  Error syndrome output indicates the location of an payload error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_CL_BCM_SYNC                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_CL_BCM_SYNC_CL_BCM_SYNC  0            /*  Check level for the synchronizing signal of BCM */
#define BITM_MIPICSI2_CL_BCM_SYNC_CL_BCM_SYNC 0x00000007    /*  Check level for the synchronizing signal of BCM */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_CL_BCM23ACK_PPIAPB          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_CL_BCM23ACK_PPIAPB_CL_BCM23ACK_PPITOAPB  0            /*  Check level for the ack signal of BCM23 from lanebyteclk to pclk */
#define BITM_MIPICSI2_CL_BCM23ACK_PPIAPB_CL_BCM23ACK_PPITOAPB 0x000000FF    /*  Check level for the ack signal of BCM23 from lanebyteclk to pclk */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_CL_BCM23ACK_IDIAPB          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_CL_BCM23ACK_IDIAPB_CL_BCM23ACK_IDITOAPB  0            /*  Check level for the ack signal of BCM23 from idiclk to pclk */
#define BITM_MIPICSI2_CL_BCM23ACK_IDIAPB_CL_BCM23ACK_IDITOAPB 0x000003FF    /*  Check level for the ack signal of BCM23 from idiclk to pclk */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_HDDP_ECC_SYNDOUT            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_HDDP_ECC_SYNDOUT_HDDP_ECC_SYNDOUT  0            /*  Error syndrome output indicates the location of an header error */
#define BITM_MIPICSI2_HDDP_ECC_SYNDOUT_HDDP_ECC_SYNDOUT 0x0000003F    /*  Error syndrome output indicates the location of an header error */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_ERR_INJ_CTRL                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_ERR_INJ_CTRL_ERR_INJ_EN  0            /*  Memory error Injection enable */
#define BITM_MIPICSI2_ERR_INJ_CTRL_ERR_INJ_EN 0x00000001    /*  Memory error Injection enable */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_ERR_INJ_STATUS              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_ERR_INJ_STATUS_ERR_INJ_END  0            /*  Memory error Inject start status */
#define BITM_MIPICSI2_ERR_INJ_STATUS_ERR_INJ_END 0x00000001    /*  Memory error Inject start status */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_ERR_INJ_CHK_MASK            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_ERR_INJ_CHK_MASK_ERR_INJ_CHK_MASK  0            /*  Error injection mask in check bits */
#define BITM_MIPICSI2_ERR_INJ_CHK_MASK_ERR_INJ_CHK_MASK 0x000000FF    /*  Error injection mask in check bits */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_ERR_INJ_DH32_MASK           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_ERR_INJ_DH32_MASK_ERR_INJ_DH32_MASK  0            /*  Error injection mask in data high 32bits */
#define BITM_MIPICSI2_ERR_INJ_DH32_MASK_ERR_INJ_DH32_MASK 0xFFFFFFFF    /*  Error injection mask in data high 32bits */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_ERR_INJ_DL32_MASK           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_ERR_INJ_DL32_MASK_ERR_INJ_DL32_MASK  0            /*  Error injection mask in data low 32bits */
#define BITM_MIPICSI2_ERR_INJ_DL32_MASK_ERR_INJ_DL32_MASK 0xFFFFFFFF    /*  Error injection mask in data low 32bits */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_IDI_RAM_ERR_LOG_AP          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_IDI_RAM_ERR_LOG_AP_NR_ADDR_LOG  0            /*  Number of logged addresses with errors */
#define BITM_MIPICSI2_IDI_RAM_ERR_LOG_AP_NR_ADDR_LOG 0x0000001F    /*  Number of logged addresses with errors */

/* -------------------------------------------------------------------------------------------------------------------------
          MIPICSI2_IDI_RAM_ERR_ADDR_AP         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MIPICSI2_IDI_RAM_ERR_ADDR_AP_ADDR_ERR  0            /*  Address of the first error */
#define BITM_MIPICSI2_IDI_RAM_ERR_ADDR_AP_ADDR_ERR 0x00003FFF    /*  Address of the first error */


/* ============================================================================================================================
        digiMMIC LVDS External Interface Bridge and PHY Register Map
   ============================================================================================================================ */

/* ============================================================================================================================
        LVDS
   ============================================================================================================================ */
#define REG_LVDS_LVDS_TXCTL_RESET            0x00040000            /*      Reset Value for LVDS_TXCTL  */
#define REG_LVDS_LVDS_TXCTL                  0xF0006018            /*  LVDS LVDS TX Control */
#define REG_LVDS_LVDS_TXSTAT_RESET           0x00000000            /*      Reset Value for LVDS_TXSTAT  */
#define REG_LVDS_LVDS_TXSTAT                 0xF000601C            /*  LVDS LVDS TX Status */
#define REG_LVDS_LVDS_TXCKDLY_RESET          0x00000000            /*      Reset Value for LVDS_TXCKDLY  */
#define REG_LVDS_LVDS_TXCKDLY                0xF0006020            /*  LVDS LVDS TX Clock Delay */
#define REG_LVDS_LVDS_TXCKDLY_STAT_RESET     0x00000000            /*      Reset Value for LVDS_TXCKDLY_STAT  */
#define REG_LVDS_LVDS_TXCKDLY_STAT           0xF0006024            /*  LVDS LVDS TX Clock Delay Status */
#define REG_LVDS_LVDS_TXFRMDLY_RESET         0x00000000            /*      Reset Value for LVDS_TXFRMDLY  */
#define REG_LVDS_LVDS_TXFRMDLY               0xF0006028            /*  LVDS LVDS TX Frame Delay */
#define REG_LVDS_LVDS_TXLNDLY_RESET          0x00000000            /*      Reset Value for LVDS_TXLNDLY  */
#define REG_LVDS_LVDS_TXLNDLY                0xF000602C            /*  LVDS LVDS TX Lane Delay */
#define REG_LVDS_LVDS_LFSR_POL_RESET         0x0000B400            /*      Reset Value for LVDS_LFSR_POL  */
#define REG_LVDS_LVDS_LFSR_POL               0xF0006030            /*  LVDS LVDS LFSR Polynomial */
#define REG_LVDS_LVDS_PADS_CTL_RESET         0x00000000            /*      Reset Value for LVDS_PADS_CTL  */
#define REG_LVDS_LVDS_PADS_CTL               0xF0006040            /*  LVDS LVDS Pads Control Register */
#define REG_LVDS_LVDS_PADS_STAT_RESET        0x00000000            /*      Reset Value for LVDS_PADS_STAT  */
#define REG_LVDS_LVDS_PADS_STAT              0xF0006044            /*  LVDS LVDS Pads Status Register */
#define REG_LVDS_DATA_PIPE_CTL_RESET         0x00000000            /*      Reset Value for DATA_PIPE_CTL  */
#define REG_LVDS_DATA_PIPE_CTL               0xF0006080            /*  LVDS Data Pipe Control Register */
#define REG_LVDS_DATA_PIPE_STAT_RESET        0x00000000            /*      Reset Value for DATA_PIPE_STAT  */
#define REG_LVDS_DATA_PIPE_STAT              0xF0006084            /*  LVDS Data Pipe Status Register */
#define REG_LVDS_LVDS_DATA_ID_REG_RESET      0x00000000            /*      Reset Value for LVDS_DATA_ID_REG  */
#define REG_LVDS_LVDS_DATA_ID_REG            0xF0006220            /*  LVDS Register for Data ID Value for all 4 RX data streams */
#define REG_LVDS_LVDS_WC_REG_RESET           0x00000000            /*      Reset Value for LVDS_WC_REG  */
#define REG_LVDS_LVDS_WC_REG                 0xF0006224            /*  LVDS Register for Byte Count value, same for all 4 LVDS data lanes */
#define REG_LVDS_LVDS_DMA_DATA_CNT_REG_RESET 0x00000000            /*      Reset Value for LVDS_DMA_DATA_CNT_REG  */
#define REG_LVDS_LVDS_DMA_DATA_CNT_REG       0xF0006228            /*  LVDS DMA data count in bytes */
#define REG_LVDS_LVDS_CTL_REG_RESET          0x00000000            /*      Reset Value for LVDS_CTL_REG  */
#define REG_LVDS_LVDS_CTL_REG                0xF000622C            /*  LVDS LVDS Control Register */
#define REG_LVDS_LVDS_IRQ_EN_REG_RESET       0x00000000            /*      Reset Value for LVDS_IRQ_EN_REG  */
#define REG_LVDS_LVDS_IRQ_EN_REG             0xF0006230            /*  LVDS This register enables the interrupts of LVDS subsystem */
#define REG_LVDS_LVDS_FAULT_EN_REG_RESET     0x00007C80            /*      Reset Value for LVDS_FAULT_EN_REG  */
#define REG_LVDS_LVDS_FAULT_EN_REG           0xF0006234            /*  LVDS LVDS Fault Enable Register */
#define REG_LVDS_LVDS_STAT_REG_RESET         0x00000000            /*      Reset Value for LVDS_STAT_REG  */
#define REG_LVDS_LVDS_STAT_REG               0xF0006238            /*  LVDS LVDS Status Register */
#define REG_LVDS_LVDS_ECC_SB_ERROR_REG_RESET 0x00000000            /*      Reset Value for LVDS_ECC_SB_ERROR_REG  */
#define REG_LVDS_LVDS_ECC_SB_ERROR_REG       0xF000623C            /*  LVDS Address and Bit position for single bit ECC errors */
#define REG_LVDS_LVDS_ECC_DB_ERROR_REG_RESET 0x00000000            /*      Reset Value for LVDS_ECC_DB_ERROR_REG  */
#define REG_LVDS_LVDS_ECC_DB_ERROR_REG       0xF0006240            /*  LVDS Address and Bit position for multi bit ECC errors */
#define REG_LVDS_LVDS_BUFFER_ADDR_RESET      0x00000000            /*      Reset Value for LVDS_BUFFER_ADDR  */
#define REG_LVDS_LVDS_BUFFER_ADDR            0xF0006244            /*  LVDS LVDS Controller Buffer Address */
#define REG_LVDS_LVDS_RUN_CTL_RESET          0x00000000            /*      Reset Value for LVDS_RUN_CTL  */
#define REG_LVDS_LVDS_RUN_CTL                0xF0006248            /*  LVDS LVDS Run Control Register */

/* ============================================================================================================================
        LVDS Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_TXCTL                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_TXCTL_SPARE1          21            /*  LVDS Spare1 */
#define BITP_LVDS_LVDS_TXCTL_FRAME_SYNC_POSITION 20            /*  Frame Sync Position */
#define BITP_LVDS_LVDS_TXCTL_SPARE0          19            /*  LVDS Spare0 */
#define BITP_LVDS_LVDS_TXCTL_PHY_TMODE_DATA_DELAY 17            /*  Coarse Data Delay for PHY Loopback Test Mode */
#define BITP_LVDS_LVDS_TXCTL_PHY_TMODE_CLK_DELAY 11            /*  Clock Delay for PHY Loopback Test Mode */
#define BITP_LVDS_LVDS_TXCTL_PHY_TMODE_COMP_EN  8            /*  PHY Loopback Test Mode Comparator Enable */
#define BITP_LVDS_LVDS_TXCTL_CTLSTATSEL       0            /*  TX Control Status Select */
#define BITM_LVDS_LVDS_TXCTL_SPARE1          0x00E00000    /*  LVDS Spare1 */
#define BITM_LVDS_LVDS_TXCTL_FRAME_SYNC_POSITION 0x00100000    /*  Frame Sync Position */
#define BITM_LVDS_LVDS_TXCTL_SPARE0          0x00080000    /*  LVDS Spare0 */
#define BITM_LVDS_LVDS_TXCTL_PHY_TMODE_DATA_DELAY 0x00060000    /*  Coarse Data Delay for PHY Loopback Test Mode */
#define BITM_LVDS_LVDS_TXCTL_PHY_TMODE_CLK_DELAY 0x0001F800    /*  Clock Delay for PHY Loopback Test Mode */
#define BITM_LVDS_LVDS_TXCTL_PHY_TMODE_COMP_EN 0x00000100    /*  PHY Loopback Test Mode Comparator Enable */
#define BITM_LVDS_LVDS_TXCTL_CTLSTATSEL      0x000000FF    /*  TX Control Status Select */
#define ENUM_LVDS_LVDS_TXCTL_SAMPLE_START_FS 0x00000000            /*  frame_sync_position: Frame Sync signals start of sample */
#define ENUM_LVDS_LVDS_TXCTL_SAMPLE_END_FS   0x00100000            /*  frame_sync_position: Frame Sync signals end of sample */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_TXSTAT                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_TXSTAT_PHY_TMODE_ERROR_POS 16            /*  PHY Loopback Test Mode Error Position */
#define BITP_LVDS_LVDS_TXSTAT_PHY_TMODE_EXPECTED_DATA 12            /*  PHY Loopback Test Mode Expected Data */
#define BITP_LVDS_LVDS_TXSTAT_PHY_TMODE_RECEIVED_DATA 10            /*  PHY Loopback Test Mode Received Data */
#define BITP_LVDS_LVDS_TXSTAT_PHY_TMODE_ERROR  9            /*  PHY Loopback Test Mode Error */
#define BITP_LVDS_LVDS_TXSTAT_TXTRNERR        8            /*  TX Training Error */
#define BITP_LVDS_LVDS_TXSTAT_LNSTAT          0            /*  TX LVDS Lane Status */
#define BITM_LVDS_LVDS_TXSTAT_PHY_TMODE_ERROR_POS 0xFFFF0000    /*  PHY Loopback Test Mode Error Position */
#define BITM_LVDS_LVDS_TXSTAT_PHY_TMODE_EXPECTED_DATA 0x00003000    /*  PHY Loopback Test Mode Expected Data */
#define BITM_LVDS_LVDS_TXSTAT_PHY_TMODE_RECEIVED_DATA 0x00000C00    /*  PHY Loopback Test Mode Received Data */
#define BITM_LVDS_LVDS_TXSTAT_PHY_TMODE_ERROR 0x00000200    /*  PHY Loopback Test Mode Error */
#define BITM_LVDS_LVDS_TXSTAT_TXTRNERR       0x00000100    /*  TX Training Error */
#define BITM_LVDS_LVDS_TXSTAT_LNSTAT         0x000000FF    /*  TX LVDS Lane Status */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_TXCKDLY                    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_TXCKDLY_CLKDIS         7            /*  TXCLK Disable */
#define BITP_LVDS_LVDS_TXCKDLY_CLKDLY         1            /*  TXCLK Delay */
#define BITP_LVDS_LVDS_TXCKDLY_TRAIN          0            /*  TXCLK Training */
#define BITM_LVDS_LVDS_TXCKDLY_CLKDIS        0x00000080    /*  TXCLK Disable */
#define BITM_LVDS_LVDS_TXCKDLY_CLKDLY        0x0000007E    /*  TXCLK Delay */
#define BITM_LVDS_LVDS_TXCKDLY_TRAIN         0x00000001    /*  TXCLK Training */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_TXCKDLY_STAT               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_TXCKDLY_STAT_TRAINERR  7            /*  Training Error */
#define BITP_LVDS_LVDS_TXCKDLY_STAT_TXCLKDLY  1            /*  TXCLK Delay */
#define BITP_LVDS_LVDS_TXCKDLY_STAT_TRAIN_STAT  0            /*  TX Train (Self Clear) */
#define BITM_LVDS_LVDS_TXCKDLY_STAT_TRAINERR 0x00000080    /*  Training Error */
#define BITM_LVDS_LVDS_TXCKDLY_STAT_TXCLKDLY 0x0000007E    /*  TXCLK Delay */
#define BITM_LVDS_LVDS_TXCKDLY_STAT_TRAIN_STAT 0x00000001    /*  TX Train (Self Clear) */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_TXFRMDLY                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_TXFRMDLY_TX1LVDSMD     4            /*  TX1 LVDS Mode */
#define BITP_LVDS_LVDS_TXFRMDLY_TXFRMDLY      0            /*  TX Frame Delay */
#define BITM_LVDS_LVDS_TXFRMDLY_TX1LVDSMD    0x00000030    /*  TX1 LVDS Mode */
#define BITM_LVDS_LVDS_TXFRMDLY_TXFRMDLY     0x0000000F    /*  TX Frame Delay */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_TXLNDLY                    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_TXLNDLY_LANE3         12            /*  TX Lane3 Delay */
#define BITP_LVDS_LVDS_TXLNDLY_LANE2          8            /*  TX Lane2 Delay */
#define BITP_LVDS_LVDS_TXLNDLY_LANE1          4            /*  TX Lane1 Delay */
#define BITP_LVDS_LVDS_TXLNDLY_LANE0          0            /*  TX Lane0 Delay */
#define BITM_LVDS_LVDS_TXLNDLY_LANE3         0x0000F000    /*  TX Lane3 Delay */
#define BITM_LVDS_LVDS_TXLNDLY_LANE2         0x00000F00    /*  TX Lane2 Delay */
#define BITM_LVDS_LVDS_TXLNDLY_LANE1         0x000000F0    /*  TX Lane1 Delay */
#define BITM_LVDS_LVDS_TXLNDLY_LANE0         0x0000000F    /*  TX Lane0 Delay */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_LFSR_POL                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_LFSR_POL_LFSRPOLY      0            /*  LVDS LFSR Polynomial[15:0] */
#define BITM_LVDS_LVDS_LFSR_POL_LFSRPOLY     0x0000FFFF    /*  LVDS LFSR Polynomial[15:0] */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_PADS_CTL                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_PADS_CTL_PHY_TMODE_EN 13            /*  PHY Loopback Test Mode Enable */
#define BITP_LVDS_LVDS_PADS_CTL_PHY_TMODE_MUX_SEL 11            /*  Selects the channel for loopback */
#define BITP_LVDS_LVDS_PADS_CTL_SHORTCIRCUITPROTECTIONDISABLE  7            /*  disables the short circuit protection */
#define BITP_LVDS_LVDS_PADS_CTL_RISEFALLCONFIG  4            /*  Increases rise/fall times of the LVDS driver output */
#define BITP_LVDS_LVDS_PADS_CTL_PWRDWN        0            /*  LVDS Power Down */
#define BITM_LVDS_LVDS_PADS_CTL_PHY_TMODE_EN 0x00002000    /*  PHY Loopback Test Mode Enable */
#define BITM_LVDS_LVDS_PADS_CTL_PHY_TMODE_MUX_SEL 0x00001800    /*  Selects the channel for loopback */
#define BITM_LVDS_LVDS_PADS_CTL_SHORTCIRCUITPROTECTIONDISABLE 0x00000080    /*  disables the short circuit protection */
#define BITM_LVDS_LVDS_PADS_CTL_RISEFALLCONFIG 0x00000070    /*  Increases rise/fall times of the LVDS driver output */
#define BITM_LVDS_LVDS_PADS_CTL_PWRDWN       0x00000001    /*  LVDS Power Down */
#define ENUM_LVDS_LVDS_PADS_CTL_CH0_SEL      0x00000000            /*  phy_tmode_mux_sel: Selects TX0 Channel for Loopback */
#define ENUM_LVDS_LVDS_PADS_CTL_CH1_SEL      0x00000800            /*  phy_tmode_mux_sel: Selects TX1 Channel for Loopback */
#define ENUM_LVDS_LVDS_PADS_CTL_CH2_SEL      0x00001000            /*  phy_tmode_mux_sel: Selects TX2 Channel for Loopback */
#define ENUM_LVDS_LVDS_PADS_CTL_CH3_SEL      0x00001800            /*  phy_tmode_mux_sel: Selects TX3 Channel for Loopback */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_PADS_STAT                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_PADS_STAT_PADSTAT      0            /*  LVDS Pads Status (T.B.D.) */
#define BITM_LVDS_LVDS_PADS_STAT_PADSTAT     0x000000FF    /*  LVDS Pads Status (T.B.D.) */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_DATA_PIPE_CTL                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_DATA_PIPE_CTL_LVDSEN        0            /*  LVDS Port Enable */
#define BITM_LVDS_DATA_PIPE_CTL_LVDSEN       0x00000001    /*  LVDS Port Enable */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_DATA_PIPE_STAT                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_DATA_PIPE_STAT_UNIMPERR    19            /*  Unimplemented 1 KB Region APB Error */
#define BITP_LVDS_DATA_PIPE_STAT_TXSLVERR    18            /*  TX DDE APB Slave Error */
#define BITP_LVDS_DATA_PIPE_STAT_RXSLVERR    17            /*  RX DDE APB Slave Error */
#define BITP_LVDS_DATA_PIPE_STAT_LVDSSLVERR  16            /*  LVDS Control APB Slave Error */
#define BITP_LVDS_DATA_PIPE_STAT_TXACK        9            /*  TXACK Asserted */
#define BITP_LVDS_DATA_PIPE_STAT_TXEN         8            /*  Transmitter Enabled */
#define BITP_LVDS_DATA_PIPE_STAT_RXACK        1            /*  RXACK Asserted */
#define BITP_LVDS_DATA_PIPE_STAT_RXEN         0            /*  Receiver Enabled */
#define BITM_LVDS_DATA_PIPE_STAT_UNIMPERR    0x00080000    /*  Unimplemented 1 KB Region APB Error */
#define BITM_LVDS_DATA_PIPE_STAT_TXSLVERR    0x00040000    /*  TX DDE APB Slave Error */
#define BITM_LVDS_DATA_PIPE_STAT_RXSLVERR    0x00020000    /*  RX DDE APB Slave Error */
#define BITM_LVDS_DATA_PIPE_STAT_LVDSSLVERR  0x00010000    /*  LVDS Control APB Slave Error */
#define BITM_LVDS_DATA_PIPE_STAT_TXACK       0x00000200    /*  TXACK Asserted */
#define BITM_LVDS_DATA_PIPE_STAT_TXEN        0x00000100    /*  Transmitter Enabled */
#define BITM_LVDS_DATA_PIPE_STAT_RXACK       0x00000002    /*  RXACK Asserted */
#define BITM_LVDS_DATA_PIPE_STAT_RXEN        0x00000001    /*  Receiver Enabled */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_DATA_ID_REG                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL3 24            /*  Data ID value for data provided by RX Channel3 or uC or DMA. This value appears on LVDS data lane3 */
#define BITP_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL2 16            /*  Data ID value for data provided by RX Channel2 or uC or DMA. This value appears on LVDS data lane2 */
#define BITP_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL1  8            /*  Data ID value for data provided by RX Channel1 or uC or DMA. This value appears on LVDS data lane1 */
#define BITP_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL0  0            /*  Data ID value for data provided by RX Channel0 or uC or DMA. This value appears on LVDS data lane0 */
#define BITM_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL3 0xFF000000    /*  Data ID value for data provided by RX Channel3 or uC or DMA. This value appears on LVDS data lane3 */
#define BITM_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL2 0x00FF0000    /*  Data ID value for data provided by RX Channel2 or uC or DMA. This value appears on LVDS data lane2 */
#define BITM_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL1 0x0000FF00    /*  Data ID value for data provided by RX Channel1 or uC or DMA. This value appears on LVDS data lane1 */
#define BITM_LVDS_LVDS_DATA_ID_REG_LVDS_DATA_ID_VAL0 0x000000FF    /*  Data ID value for data provided by RX Channel0 or uC or DMA. This value appears on LVDS data lane0 */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_WC_REG                     Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_WC_REG_LVDS_WORD_COUNT_VAL  0            /*  This value indicates the number of bytes of data. This value appears on all the four LVDS data lanes */
#define BITM_LVDS_LVDS_WC_REG_LVDS_WORD_COUNT_VAL 0x00FFFFFF    /*  This value indicates the number of bytes of data. This value appears on all the four LVDS data lanes */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_DMA_DATA_CNT_REG           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_DMA_DATA_CNT_REG_LVDS_DMA_TRIGGER_EVENT 16            /*  LVDS DMA Trigger Event */
#define BITP_LVDS_LVDS_DMA_DATA_CNT_REG_LVDS_DMA_DATA_COUNT  0            /*  LVDS DMA Data Count Value in Bytes */
#define BITM_LVDS_LVDS_DMA_DATA_CNT_REG_LVDS_DMA_TRIGGER_EVENT 0x00010000    /*  LVDS DMA Trigger Event */
#define BITM_LVDS_LVDS_DMA_DATA_CNT_REG_LVDS_DMA_DATA_COUNT 0x0000FFFF    /*  LVDS DMA Data Count Value in Bytes */
#define ENUM_LVDS_LVDS_DMA_DATA_CNT_REG_LVDS_RX_START 0x00000000            /*  lvds_dma_trigger_event: DMA Trigger on RX Data Start */
#define ENUM_LVDS_LVDS_DMA_DATA_CNT_REG_LVDS_RX_END 0x00010000            /*  lvds_dma_trigger_event: DMA Trigger on RX Data End */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_CTL_REG                    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_CTL_REG_TEST_PATTERN_EN 22            /*  LVDS Test Pattern Enable */
#define BITP_LVDS_LVDS_CTL_REG_AUTO_CONFIG_WC 21            /*  Enables auto configuration of word count value */
#define BITP_LVDS_LVDS_CTL_REG_LSBIT_MSBIT_SEL 20            /*  Selects LS-bit first or MS-bit first in each byte of data */
#define BITP_LVDS_LVDS_CTL_REG_LSBYTE_MSBYTE_SEL 19            /*  Selects LS byte first or MS byte first within a sample of data */
#define BITP_LVDS_LVDS_CTL_REG_FRAME_SYNC_POLARITY 18            /*  Enables active low frame sync polarity */
#define BITP_LVDS_LVDS_CTL_REG_FRAMING_MODE  17            /*  Enables dual frame sync mode */
#define BITP_LVDS_LVDS_CTL_REG_LVDS_STREAMING_MODE_SEL 16            /*  Enables Streaming Mode2 */
#define BITP_LVDS_LVDS_CTL_REG_LVDS_1CH_TX_MODE_EN 14            /*  Enables Single Channel Transmission Mode */
#define BITP_LVDS_LVDS_CTL_REG_LVDS_INACT_PH_CRC_FIELD_EN 13            /*  Enables CRC field for inactive phase transmission */
#define BITP_LVDS_LVDS_CTL_REG_LVDS_INACT_PH_DMA_DATA_FIELD_EN 12            /*  Enables DMA Data field for inactive phase transmission */
#define BITP_LVDS_LVDS_CTL_REG_LVDS_INACT_PH_STATUS_FIELD_EN 11            /*  Enables Status Data field for inactive phase transmission */
#define BITP_LVDS_LVDS_CTL_REG_LVDS_INACT_PH_DATA_ID_WC_FIELD_EN  9            /*  Enables Data ID and Word Count field for inactive phase transmission */
#define BITP_LVDS_LVDS_CTL_REG_LVDS_INACT_PH_TX_EN  8            /*  Enables Inactive Phase Transmission Mode */
#define BITP_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_CRC_FIELD_EN  5            /*  Enables CRC field for active phase transmission */
#define BITP_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_DMA_DATA_FIELD_EN  4            /*  Enables DMA Data field for active phase transmission */
#define BITP_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_STATUS_FIELD_EN  3            /*  Enables Status Data field for active phase transmission */
#define BITP_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_RX_CH_FIELD_EN  2            /*  Enables RX Channel data field for active phase transmission */
#define BITP_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_DATA_ID_WC_FIELD_EN  1            /*  Enables Data ID and Word Count field for active phase transmission */
#define BITM_LVDS_LVDS_CTL_REG_TEST_PATTERN_EN 0x01C00000    /*  LVDS Test Pattern Enable */
#define BITM_LVDS_LVDS_CTL_REG_AUTO_CONFIG_WC 0x00200000    /*  Enables auto configuration of word count value */
#define BITM_LVDS_LVDS_CTL_REG_LSBIT_MSBIT_SEL 0x00100000    /*  Selects LS-bit first or MS-bit first in each byte of data */
#define BITM_LVDS_LVDS_CTL_REG_LSBYTE_MSBYTE_SEL 0x00080000    /*  Selects LS byte first or MS byte first within a sample of data */
#define BITM_LVDS_LVDS_CTL_REG_FRAME_SYNC_POLARITY 0x00040000    /*  Enables active low frame sync polarity */
#define BITM_LVDS_LVDS_CTL_REG_FRAMING_MODE  0x00020000    /*  Enables dual frame sync mode */
#define BITM_LVDS_LVDS_CTL_REG_LVDS_STREAMING_MODE_SEL 0x00010000    /*  Enables Streaming Mode2 */
#define BITM_LVDS_LVDS_CTL_REG_LVDS_1CH_TX_MODE_EN 0x00004000    /*  Enables Single Channel Transmission Mode */
#define BITM_LVDS_LVDS_CTL_REG_LVDS_INACT_PH_CRC_FIELD_EN 0x00002000    /*  Enables CRC field for inactive phase transmission */
#define BITM_LVDS_LVDS_CTL_REG_LVDS_INACT_PH_DMA_DATA_FIELD_EN 0x00001000    /*  Enables DMA Data field for inactive phase transmission */
#define BITM_LVDS_LVDS_CTL_REG_LVDS_INACT_PH_STATUS_FIELD_EN 0x00000800    /*  Enables Status Data field for inactive phase transmission */
#define BITM_LVDS_LVDS_CTL_REG_LVDS_INACT_PH_DATA_ID_WC_FIELD_EN 0x00000200    /*  Enables Data ID and Word Count field for inactive phase transmission */
#define BITM_LVDS_LVDS_CTL_REG_LVDS_INACT_PH_TX_EN 0x00000100    /*  Enables Inactive Phase Transmission Mode */
#define BITM_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_CRC_FIELD_EN 0x00000020    /*  Enables CRC field for active phase transmission */
#define BITM_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_DMA_DATA_FIELD_EN 0x00000010    /*  Enables DMA Data field for active phase transmission */
#define BITM_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_STATUS_FIELD_EN 0x00000008    /*  Enables Status Data field for active phase transmission */
#define BITM_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_RX_CH_FIELD_EN 0x00000004    /*  Enables RX Channel data field for active phase transmission */
#define BITM_LVDS_LVDS_CTL_REG_LVDS_ACT_PH_DATA_ID_WC_FIELD_EN 0x00000002    /*  Enables Data ID and Word Count field for active phase transmission */
#define ENUM_LVDS_LVDS_CTL_REG_TEST_PTRN_DIS 0x00000000            /*  test_pattern_en: LVDS Test Pattern Disabled */
#define ENUM_LVDS_LVDS_CTL_REG_TEST_PTRN_EN  0x01C00000            /*  test_pattern_en: LVDS Test Pattern Enabled */
#define ENUM_LVDS_LVDS_CTL_REG_FS_ACTIVE_HIGH 0x00000000            /*  frame_sync_polarity: Active High Frame Sync */
#define ENUM_LVDS_LVDS_CTL_REG_FS_ACTIVE_LOW 0x00040000            /*  frame_sync_polarity: Active Low Frame Sync */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_IRQ_EN_REG                 Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_IRQ_EN_REG_LVDS_CHIRP_IGNORED_INT_EN 14            /*  Enables interrupt for chirp ignored at LVDS Interface */
#define BITP_LVDS_LVDS_IRQ_EN_REG_LVDS_FIFO_ECC_ADDR_ERR_INT_EN 13            /*  Enables interrupt for LVDS FIFO ECC Address Error */
#define BITP_LVDS_LVDS_IRQ_EN_REG_LVDS_FIFO_ECC_MB_ERR_INT_EN 12            /*  Enables interrupt for LVDS FIFO multi bit ECC error */
#define BITP_LVDS_LVDS_IRQ_EN_REG_LVDS_FIFO_ECC_SB_ERR_INT_EN 11            /*  Enables interrupt for LVDS FIFO single bit ECC error */
#define BITP_LVDS_LVDS_IRQ_EN_REG_LVDS_WC_MISMATCH_INT_EN 10            /*  Enables interrupt for LVDS word count mismatch */
#define BITP_LVDS_LVDS_IRQ_EN_REG_LVDS_ACT_PH_START_INT_EN  9            /*  Enables interrupt indicating start of active phase */
#define BITP_LVDS_LVDS_IRQ_EN_REG_LVDS_INACT_PH_START_INT_EN  8            /*  Enable interrupt indicating start of inactive phase */
#define BITP_LVDS_LVDS_IRQ_EN_REG_LVDS_FRAME_FIFO_OVERFLOW_INT_EN  7            /*  Enables interrupt for LVDS data frame FIFO overflow */
#define BITP_LVDS_LVDS_IRQ_EN_REG_LVDS_EOT_UC_DATA_AT_RX_EXT_IF_BRIDGE_INT_EN  5            /*  Enables interrupt for end of transmission of uC or DMA provided data at rx_ext_if_bridge */
#define BITP_LVDS_LVDS_IRQ_EN_REG_LVDS_SOT_UC_DATA_AT_RX_EXT_IF_BRIDGE_INT_EN  4            /*  Enables interrupt for start of transmission of uC or DMA provided data at rx_ext_if_bridge */
#define BITP_LVDS_LVDS_IRQ_EN_REG_LVDS_EOT_RX_CH_DATA_AT_RX_EXT_IF_BRIDGE_INT_EN  3            /*  Enables interrupt for end of transmission of RX channel data at rx_ext_if_bridge */
#define BITP_LVDS_LVDS_IRQ_EN_REG_LVDS_SOT_RX_CH_DATA_AT_RX_EXT_IF_BRIDGE_INT_EN  2            /*  Enables interrupt for start of transmission of RX channel data at rx_ext_if_bridge */
#define BITP_LVDS_LVDS_IRQ_EN_REG_LVDS_EOT_DATA_FRAME_AT_LVDS_CONTR_INT_EN  1            /*  Enables interrupt for end of transmission of a data frame at LVDS controller interface */
#define BITP_LVDS_LVDS_IRQ_EN_REG_LVDS_SOT_DATA_FRAME_AT_LVDS_CONTR_INT_EN  0            /*  Enables interrupt for start of transmission of a data frame at LVDS controller interface */
#define BITM_LVDS_LVDS_IRQ_EN_REG_LVDS_CHIRP_IGNORED_INT_EN 0x00004000    /*  Enables interrupt for chirp ignored at LVDS Interface */
#define BITM_LVDS_LVDS_IRQ_EN_REG_LVDS_FIFO_ECC_ADDR_ERR_INT_EN 0x00002000    /*  Enables interrupt for LVDS FIFO ECC Address Error */
#define BITM_LVDS_LVDS_IRQ_EN_REG_LVDS_FIFO_ECC_MB_ERR_INT_EN 0x00001000    /*  Enables interrupt for LVDS FIFO multi bit ECC error */
#define BITM_LVDS_LVDS_IRQ_EN_REG_LVDS_FIFO_ECC_SB_ERR_INT_EN 0x00000800    /*  Enables interrupt for LVDS FIFO single bit ECC error */
#define BITM_LVDS_LVDS_IRQ_EN_REG_LVDS_WC_MISMATCH_INT_EN 0x00000400    /*  Enables interrupt for LVDS word count mismatch */
#define BITM_LVDS_LVDS_IRQ_EN_REG_LVDS_ACT_PH_START_INT_EN 0x00000200    /*  Enables interrupt indicating start of active phase */
#define BITM_LVDS_LVDS_IRQ_EN_REG_LVDS_INACT_PH_START_INT_EN 0x00000100    /*  Enable interrupt indicating start of inactive phase */
#define BITM_LVDS_LVDS_IRQ_EN_REG_LVDS_FRAME_FIFO_OVERFLOW_INT_EN 0x00000080    /*  Enables interrupt for LVDS data frame FIFO overflow */
#define BITM_LVDS_LVDS_IRQ_EN_REG_LVDS_EOT_UC_DATA_AT_RX_EXT_IF_BRIDGE_INT_EN 0x00000020    /*  Enables interrupt for end of transmission of uC or DMA provided data at rx_ext_if_bridge */
#define BITM_LVDS_LVDS_IRQ_EN_REG_LVDS_SOT_UC_DATA_AT_RX_EXT_IF_BRIDGE_INT_EN 0x00000010    /*  Enables interrupt for start of transmission of uC or DMA provided data at rx_ext_if_bridge */
#define BITM_LVDS_LVDS_IRQ_EN_REG_LVDS_EOT_RX_CH_DATA_AT_RX_EXT_IF_BRIDGE_INT_EN 0x00000008    /*  Enables interrupt for end of transmission of RX channel data at rx_ext_if_bridge */
#define BITM_LVDS_LVDS_IRQ_EN_REG_LVDS_SOT_RX_CH_DATA_AT_RX_EXT_IF_BRIDGE_INT_EN 0x00000004    /*  Enables interrupt for start of transmission of RX channel data at rx_ext_if_bridge */
#define BITM_LVDS_LVDS_IRQ_EN_REG_LVDS_EOT_DATA_FRAME_AT_LVDS_CONTR_INT_EN 0x00000002    /*  Enables interrupt for end of transmission of a data frame at LVDS controller interface */
#define BITM_LVDS_LVDS_IRQ_EN_REG_LVDS_SOT_DATA_FRAME_AT_LVDS_CONTR_INT_EN 0x00000001    /*  Enables interrupt for start of transmission of a data frame at LVDS controller interface */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_FAULT_EN_REG               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_FAULT_EN_REG_LVDS_CHIRP_IGNORED_FAULT_EN 14            /*  Enables fault for chirp ignored at LVDS Interface */
#define BITP_LVDS_LVDS_FAULT_EN_REG_LVDS_FIFO_ECC_ADDR_ERR_FAULT_EN 13            /*  Enables fault for LVDS FIFO ECC Address Error */
#define BITP_LVDS_LVDS_FAULT_EN_REG_LVDS_FIFO_ECC_MB_ERR_FAULT_EN 12            /*  Enables fault for LVDS FIFO multi bit ECC error */
#define BITP_LVDS_LVDS_FAULT_EN_REG_LVDS_FIFO_ECC_SB_ERR_FAULT_EN 11            /*  Enables fault for LVDS FIFO single bit ECC error */
#define BITP_LVDS_LVDS_FAULT_EN_REG_LVDS_WC_MISMATCH_FAULT_EN 10            /*  Enables fault for LVDS word count mismatch */
#define BITP_LVDS_LVDS_FAULT_EN_REG_LVDS_ACT_PH_START_FAULT_EN  9            /*  Enables fault indicating start of active phase */
#define BITP_LVDS_LVDS_FAULT_EN_REG_LVDS_INACT_PH_START_FAULT_EN  8            /*  Enables fault indicating start of inactive phase */
#define BITP_LVDS_LVDS_FAULT_EN_REG_LVDS_FRAME_FIFO_OVERFLOW_FAULT_EN  7            /*  Enables fault for LVDS data frame FIFO overflow */
#define BITP_LVDS_LVDS_FAULT_EN_REG_LVDS_EOT_UC_DATA_AT_RX_EXT_IF_BRIDGE_FAULT_EN  5            /*  Enables fault for end of transmission of uC or DMA provided data at rx_ext_if_bridge */
#define BITP_LVDS_LVDS_FAULT_EN_REG_LVDS_SOT_UC_DATA_AT_RX_EXT_IF_BRIDGE_FAULT_EN  4            /*  Enables fault for start of transmission of uC or DMA provided data at rx_ext_if_bridge */
#define BITP_LVDS_LVDS_FAULT_EN_REG_LVDS_EOT_RX_CH_DATA_AT_RX_EXT_IF_BRIDGE_FAULT_EN  3            /*  Enables fault for end of transmission of RX channel data at rx_ext_if_bridge */
#define BITP_LVDS_LVDS_FAULT_EN_REG_LVDS_SOT_RX_CH_DATA_AT_RX_EXT_IF_BRIDGE_FAULT_EN  2            /*  Enables fault for start of transmission of RX channel data at rx_ext_if_bridge */
#define BITP_LVDS_LVDS_FAULT_EN_REG_LVDS_EOT_DATA_FRAME_AT_LVDS_CONTR_FAULT_EN  1            /*  Enables fault for end of transmission of a data frame at LVDS controller interface */
#define BITP_LVDS_LVDS_FAULT_EN_REG_LVDS_SOT_DATA_FRAME_AT_LVDS_CONTR_FAULT_EN  0            /*  Enables fault for start of transmission of a data frame at LVDS controller interface */
#define BITM_LVDS_LVDS_FAULT_EN_REG_LVDS_CHIRP_IGNORED_FAULT_EN 0x00004000    /*  Enables fault for chirp ignored at LVDS Interface */
#define BITM_LVDS_LVDS_FAULT_EN_REG_LVDS_FIFO_ECC_ADDR_ERR_FAULT_EN 0x00002000    /*  Enables fault for LVDS FIFO ECC Address Error */
#define BITM_LVDS_LVDS_FAULT_EN_REG_LVDS_FIFO_ECC_MB_ERR_FAULT_EN 0x00001000    /*  Enables fault for LVDS FIFO multi bit ECC error */
#define BITM_LVDS_LVDS_FAULT_EN_REG_LVDS_FIFO_ECC_SB_ERR_FAULT_EN 0x00000800    /*  Enables fault for LVDS FIFO single bit ECC error */
#define BITM_LVDS_LVDS_FAULT_EN_REG_LVDS_WC_MISMATCH_FAULT_EN 0x00000400    /*  Enables fault for LVDS word count mismatch */
#define BITM_LVDS_LVDS_FAULT_EN_REG_LVDS_ACT_PH_START_FAULT_EN 0x00000200    /*  Enables fault indicating start of active phase */
#define BITM_LVDS_LVDS_FAULT_EN_REG_LVDS_INACT_PH_START_FAULT_EN 0x00000100    /*  Enables fault indicating start of inactive phase */
#define BITM_LVDS_LVDS_FAULT_EN_REG_LVDS_FRAME_FIFO_OVERFLOW_FAULT_EN 0x00000080    /*  Enables fault for LVDS data frame FIFO overflow */
#define BITM_LVDS_LVDS_FAULT_EN_REG_LVDS_EOT_UC_DATA_AT_RX_EXT_IF_BRIDGE_FAULT_EN 0x00000020    /*  Enables fault for end of transmission of uC or DMA provided data at rx_ext_if_bridge */
#define BITM_LVDS_LVDS_FAULT_EN_REG_LVDS_SOT_UC_DATA_AT_RX_EXT_IF_BRIDGE_FAULT_EN 0x00000010    /*  Enables fault for start of transmission of uC or DMA provided data at rx_ext_if_bridge */
#define BITM_LVDS_LVDS_FAULT_EN_REG_LVDS_EOT_RX_CH_DATA_AT_RX_EXT_IF_BRIDGE_FAULT_EN 0x00000008    /*  Enables fault for end of transmission of RX channel data at rx_ext_if_bridge */
#define BITM_LVDS_LVDS_FAULT_EN_REG_LVDS_SOT_RX_CH_DATA_AT_RX_EXT_IF_BRIDGE_FAULT_EN 0x00000004    /*  Enables fault for start of transmission of RX channel data at rx_ext_if_bridge */
#define BITM_LVDS_LVDS_FAULT_EN_REG_LVDS_EOT_DATA_FRAME_AT_LVDS_CONTR_FAULT_EN 0x00000002    /*  Enables fault for end of transmission of a data frame at LVDS controller interface */
#define BITM_LVDS_LVDS_FAULT_EN_REG_LVDS_SOT_DATA_FRAME_AT_LVDS_CONTR_FAULT_EN 0x00000001    /*  Enables fault for start of transmission of a data frame at LVDS controller interface */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_STAT_REG                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_STAT_REG_LVDS_CHIRP_IGNORED_STAT 14            /*  Indicates chirp ignored at LVDS Interface */
#define BITP_LVDS_LVDS_STAT_REG_LVDS_FIFO_ECC_ADDR_ERR 13            /*  Indicates LVDS FIFO ECC Address Error */
#define BITP_LVDS_LVDS_STAT_REG_LVDS_FIFO_ECC_MB_ERR 12            /*  Indicates the LVDS FIFO multi bit ECC error */
#define BITP_LVDS_LVDS_STAT_REG_LVDS_FIFO_ECC_SB_ERR 11            /*  Indicates the LVDS FIFO single bit ECC error */
#define BITP_LVDS_LVDS_STAT_REG_LVDS_WC_MISMATCH_STAT 10            /*  Indicates LVDS Word Count Mismatch */
#define BITP_LVDS_LVDS_STAT_REG_LVDS_ACT_PH_START  9            /*  Indicates start of active phase */
#define BITP_LVDS_LVDS_STAT_REG_LVDS_INACT_PH_START  8            /*  Indicates start of inactive phase */
#define BITP_LVDS_LVDS_STAT_REG_LVDS_FRAME_FIFO_OVERFLOW_STAT  7            /*  Indicates LVDS data frame FIFO overflow */
#define BITP_LVDS_LVDS_STAT_REG_DMA_ALLOWED   6            /*  DMA data over AHB interface allowed */
#define BITP_LVDS_LVDS_STAT_REG_LVDS_EOT_UC_DATA_AT_RX_EXT_IF_BRIDGE_STAT  5            /*  Indicates whether end of transmission of data provide by uC or DMA  at rx_ext_if_bridge has occurred */
#define BITP_LVDS_LVDS_STAT_REG_LVDS_SOT_UC_DATA_AT_RX_EXT_IF_BRIDGE_STAT  4            /*  Indicates whether start of transmission of uC or DMA provided data at rx_ext_if_bridge has occurred */
#define BITP_LVDS_LVDS_STAT_REG_LVDS_EOT_RX_CH_DATA_AT_RX_EXT_IF_BRIDGE_STAT  3            /*  Indicates whether end of transmission of RX channel data at rx_ext_if_bridge has occurred */
#define BITP_LVDS_LVDS_STAT_REG_LVDS_SOT_RX_CH_DATA_AT_RX_EXT_IF_BRIDGE_STAT  2            /*  Indicates whether start of transmission of RX channel data at rx_ext_if_bridge has occurred */
#define BITP_LVDS_LVDS_STAT_REG_LVDS_EOT_DATA_FRAME_AT_LVDS_CONTR_STAT  1            /*  Indicates whether end of transmission of a data frame at LVDS controller interface has occurred */
#define BITP_LVDS_LVDS_STAT_REG_LVDS_SOT_DATA_FRAME_AT_LVDS_CONTR_STAT  0            /*  Indicates whether start of transmission of a data frame at LVDS controller interface has occurred */
#define BITM_LVDS_LVDS_STAT_REG_LVDS_CHIRP_IGNORED_STAT 0x00004000    /*  Indicates chirp ignored at LVDS Interface */
#define BITM_LVDS_LVDS_STAT_REG_LVDS_FIFO_ECC_ADDR_ERR 0x00002000    /*  Indicates LVDS FIFO ECC Address Error */
#define BITM_LVDS_LVDS_STAT_REG_LVDS_FIFO_ECC_MB_ERR 0x00001000    /*  Indicates the LVDS FIFO multi bit ECC error */
#define BITM_LVDS_LVDS_STAT_REG_LVDS_FIFO_ECC_SB_ERR 0x00000800    /*  Indicates the LVDS FIFO single bit ECC error */
#define BITM_LVDS_LVDS_STAT_REG_LVDS_WC_MISMATCH_STAT 0x00000400    /*  Indicates LVDS Word Count Mismatch */
#define BITM_LVDS_LVDS_STAT_REG_LVDS_ACT_PH_START 0x00000200    /*  Indicates start of active phase */
#define BITM_LVDS_LVDS_STAT_REG_LVDS_INACT_PH_START 0x00000100    /*  Indicates start of inactive phase */
#define BITM_LVDS_LVDS_STAT_REG_LVDS_FRAME_FIFO_OVERFLOW_STAT 0x00000080    /*  Indicates LVDS data frame FIFO overflow */
#define BITM_LVDS_LVDS_STAT_REG_DMA_ALLOWED  0x00000040    /*  DMA data over AHB interface allowed */
#define BITM_LVDS_LVDS_STAT_REG_LVDS_EOT_UC_DATA_AT_RX_EXT_IF_BRIDGE_STAT 0x00000020    /*  Indicates whether end of transmission of data provide by uC or DMA  at rx_ext_if_bridge has occurred */
#define BITM_LVDS_LVDS_STAT_REG_LVDS_SOT_UC_DATA_AT_RX_EXT_IF_BRIDGE_STAT 0x00000010    /*  Indicates whether start of transmission of uC or DMA provided data at rx_ext_if_bridge has occurred */
#define BITM_LVDS_LVDS_STAT_REG_LVDS_EOT_RX_CH_DATA_AT_RX_EXT_IF_BRIDGE_STAT 0x00000008    /*  Indicates whether end of transmission of RX channel data at rx_ext_if_bridge has occurred */
#define BITM_LVDS_LVDS_STAT_REG_LVDS_SOT_RX_CH_DATA_AT_RX_EXT_IF_BRIDGE_STAT 0x00000004    /*  Indicates whether start of transmission of RX channel data at rx_ext_if_bridge has occurred */
#define BITM_LVDS_LVDS_STAT_REG_LVDS_EOT_DATA_FRAME_AT_LVDS_CONTR_STAT 0x00000002    /*  Indicates whether end of transmission of a data frame at LVDS controller interface has occurred */
#define BITM_LVDS_LVDS_STAT_REG_LVDS_SOT_DATA_FRAME_AT_LVDS_CONTR_STAT 0x00000001    /*  Indicates whether start of transmission of a data frame at LVDS controller interface has occurred */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_ECC_SB_ERROR_REG           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_ECC_SB_ERROR_REG_LVDS_FIFO_ECC_SB_ERR_SYNDROME 16            /*  LVDS FIFO single bit ECC error syndrome */
#define BITP_LVDS_LVDS_ECC_SB_ERROR_REG_LVDS_FIFO_ECC_SB_ERR_ADDR  0            /*  LVDS FIFO single bit ECC error address */
#define BITM_LVDS_LVDS_ECC_SB_ERROR_REG_LVDS_FIFO_ECC_SB_ERR_SYNDROME 0x007F0000    /*  LVDS FIFO single bit ECC error syndrome */
#define BITM_LVDS_LVDS_ECC_SB_ERROR_REG_LVDS_FIFO_ECC_SB_ERR_ADDR 0x00003FFF    /*  LVDS FIFO single bit ECC error address */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_ECC_DB_ERROR_REG           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_ECC_DB_ERROR_REG_LVDS_FIFO_ECC_MB_ERR_SYNDROME 16            /*  LVDS FIFO multi bit ECC error syndrome */
#define BITP_LVDS_LVDS_ECC_DB_ERROR_REG_LVDS_FIFO_ECC_MB_ERR_ADDR  0            /*  LVDS FIFO multi bit ECC error address */
#define BITM_LVDS_LVDS_ECC_DB_ERROR_REG_LVDS_FIFO_ECC_MB_ERR_SYNDROME 0x007F0000    /*  LVDS FIFO multi bit ECC error syndrome */
#define BITM_LVDS_LVDS_ECC_DB_ERROR_REG_LVDS_FIFO_ECC_MB_ERR_ADDR 0x00003FFF    /*  LVDS FIFO multi bit ECC error address */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_BUFFER_ADDR                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_BUFFER_ADDR_LVDS_BUFFER_READ_ADDR 16            /*  LVDS Controller Buffer Read Address */
#define BITP_LVDS_LVDS_BUFFER_ADDR_LVDS_BUFFER_WRITE_ADDR  0            /*  LVDS Controller Buffer Write Address */
#define BITM_LVDS_LVDS_BUFFER_ADDR_LVDS_BUFFER_READ_ADDR 0x3FFF0000    /*  LVDS Controller Buffer Read Address */
#define BITM_LVDS_LVDS_BUFFER_ADDR_LVDS_BUFFER_WRITE_ADDR 0x00003FFF    /*  LVDS Controller Buffer Write Address */

/* -------------------------------------------------------------------------------------------------------------------------
          LVDS_LVDS_RUN_CTL                    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_LVDS_LVDS_RUN_CTL_LVDS_INACT_PH_TX_TRIGGER  0            /*  LVDS Inactive Phase Transmission Trigger */
#define BITM_LVDS_LVDS_RUN_CTL_LVDS_INACT_PH_TX_TRIGGER 0x00000001    /*  LVDS Inactive Phase Transmission Trigger */


/* ============================================================================================================================
        digiMMIC Data Port Register Map
   ============================================================================================================================ */

/* ============================================================================================================================
        DATA_PORT
   ============================================================================================================================ */
#define REG_DATA_PORT_DATA_PORT_CTL_REG_RESET 0x0000001C            /*      Reset Value for DATA_PORT_CTL_REG  */
#define REG_DATA_PORT_DATA_PORT_CTL_REG      0xF0007000            /*  DATA_PORT Data Port Control Register */
#define REG_DATA_PORT_DATA_PORT_USERVAL_REG_RESET 0x00000000            /*      Reset Value for DATA_PORT_USERVAL_REG  */
#define REG_DATA_PORT_DATA_PORT_USERVAL_REG  0xF000700C            /*  DATA_PORT Data Port Userval Register / Lower 32-bits of LVDS Test Pattern */
#define REG_DATA_PORT_DATA_PORT_CRC32_POLY_RESET 0x82608EDB            /*      Reset Value for DATA_PORT_CRC32_POLY  */
#define REG_DATA_PORT_DATA_PORT_CRC32_POLY   0xF0007010            /*  DATA_PORT Data Port CRC32 Polynomial */
#define REG_DATA_PORT_LVDS_TEST_PATTERN_MSB_RESET 0x00000000            /*      Reset Value for LVDS_TEST_PATTERN_MSB  */
#define REG_DATA_PORT_LVDS_TEST_PATTERN_MSB  0xF0007014            /*  DATA_PORT Upper 32-bits of LVDS Test Pattern */

/* ============================================================================================================================
        DATA_PORT Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          DATA_PORT_DATA_PORT_CTL_REG          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DATA_PORT_DATA_PORT_CTL_REG_CRC32_SEED_SEL  7            /*  Select Initial Seed for CRC32 Computation */
#define BITP_DATA_PORT_DATA_PORT_CTL_REG_DATA_PORT_MEM_SLP  4            /*  Data Port Memory Sleep Control */
#define BITP_DATA_PORT_DATA_PORT_CTL_REG_DATA_PORT_MEM_SD  3            /*  Data Port Memory Shutdown Control */
#define BITP_DATA_PORT_DATA_PORT_CTL_REG_DATA_PORT_MEM_ACCESS_ENABLE  2            /*  Data Port Memory Access Enable */
#define BITP_DATA_PORT_DATA_PORT_CTL_REG_DATA_PORT_MODE_SEL  0            /*  Select Data Port Functional Mode */
#define BITM_DATA_PORT_DATA_PORT_CTL_REG_CRC32_SEED_SEL 0x00000080    /*  Select Initial Seed for CRC32 Computation */
#define BITM_DATA_PORT_DATA_PORT_CTL_REG_DATA_PORT_MEM_SLP 0x00000010    /*  Data Port Memory Sleep Control */
#define BITM_DATA_PORT_DATA_PORT_CTL_REG_DATA_PORT_MEM_SD 0x00000008    /*  Data Port Memory Shutdown Control */
#define BITM_DATA_PORT_DATA_PORT_CTL_REG_DATA_PORT_MEM_ACCESS_ENABLE 0x00000004    /*  Data Port Memory Access Enable */
#define BITM_DATA_PORT_DATA_PORT_CTL_REG_DATA_PORT_MODE_SEL 0x00000003    /*  Select Data Port Functional Mode */
#define ENUM_DATA_PORT_DATA_PORT_CTL_REG_CRC32_ZERO_SEED 0x00000000            /*  crc32_seed_sel: Selects 0 as initial seed */
#define ENUM_DATA_PORT_DATA_PORT_CTL_REG_CRC32_MINUS_ONE_SEED 0x00000080            /*  crc32_seed_sel: Selects -1 as initial seed */
#define ENUM_DATA_PORT_DATA_PORT_CTL_REG_MEM_SLEEP_DISABLE 0x00000000            /*  data_port_mem_slp: Memory Sleep Disabled */
#define ENUM_DATA_PORT_DATA_PORT_CTL_REG_MEM_SLEEP_ENABLE 0x00000010            /*  data_port_mem_slp: Memory Sleep Enabled */
#define ENUM_DATA_PORT_DATA_PORT_CTL_REG_MEM_SHUTDOWN_DISABLE 0x00000000            /*  data_port_mem_sd: Memory Shutdown Disabled */
#define ENUM_DATA_PORT_DATA_PORT_CTL_REG_MEM_SHUTDOWN_ENABLE 0x00000008            /*  data_port_mem_sd: Memory Shutdown Enabled */
#define ENUM_DATA_PORT_DATA_PORT_CTL_REG_MEM_ACC_ENABLE 0x00000000            /*  data_port_mem_access_enable: Memory Access Enable */
#define ENUM_DATA_PORT_DATA_PORT_CTL_REG_MEM_ACC_DISABLE 0x00000004            /*  data_port_mem_access_enable: Memory Access Disable */
#define ENUM_DATA_PORT_DATA_PORT_CTL_REG_TRANSMIT_MODE 0x00000000            /*  data_port_mode_sel: Transmission Mode */
#define ENUM_DATA_PORT_DATA_PORT_CTL_REG_BUFFER_MODE 0x00000001            /*  data_port_mode_sel: Buffer Mode */
#define ENUM_DATA_PORT_DATA_PORT_CTL_REG_DEBUG_MODE 0x00000002            /*  data_port_mode_sel: Debug Access Mode */

/* -------------------------------------------------------------------------------------------------------------------------
          DATA_PORT_DATA_PORT_USERVAL_REG      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX3 24            /*  Data Port Userval Field for RX Channel 3 */
#define BITP_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX2 16            /*  Data Port Userval Field for RX Channel 2 */
#define BITP_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX1  8            /*  Data Port Userval Field for RX Channel 1 */
#define BITP_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX0  0            /*  Data Port Userval Field for RX Channel 0 */
#define BITM_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX3 0xFF000000    /*  Data Port Userval Field for RX Channel 3 */
#define BITM_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX2 0x00FF0000    /*  Data Port Userval Field for RX Channel 2 */
#define BITM_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX1 0x0000FF00    /*  Data Port Userval Field for RX Channel 1 */
#define BITM_DATA_PORT_DATA_PORT_USERVAL_REG_DATA_PORT_USERVAL_RX0 0x000000FF    /*  Data Port Userval Field for RX Channel 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          DATA_PORT_DATA_PORT_CRC32_POLY       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DATA_PORT_DATA_PORT_CRC32_POLY_CRC32_POLY  0            /*  Data Port CRC32 Polynomial, x^0 coefficient is implicitly 1 */
#define BITM_DATA_PORT_DATA_PORT_CRC32_POLY_CRC32_POLY 0xFFFFFFFF    /*  Data Port CRC32 Polynomial, x^0 coefficient is implicitly 1 */

/* -------------------------------------------------------------------------------------------------------------------------
          DATA_PORT_LVDS_TEST_PATTERN_MSB      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_DATA_PORT_LVDS_TEST_PATTERN_MSB_LVDS_TEST_PATTERN_MSB  0            /*  Upper 32-bits of LVDS Test Pattern */
#define BITM_DATA_PORT_LVDS_TEST_PATTERN_MSB_LVDS_TEST_PATTERN_MSB 0xFFFFFFFF    /*  Upper 32-bits of LVDS Test Pattern */


/* ============================================================================================================================
        
   ============================================================================================================================ */

/* ============================================================================================================================
        FaultCtl
   ============================================================================================================================ */
#define REG_FAULTCTL_FAULT_STATUS0_0_RESET   0x00000000            /*      Reset Value for fault_status0_0  */
#define REG_FAULTCTL_FAULT_STATUS0_0         0xF0008008            /*  FaultCtl Fault Status register 0 for fault0b pin */
#define REG_FAULTCTL_FAULT_STATUS1_0_RESET   0x00000000            /*      Reset Value for fault_status1_0  */
#define REG_FAULTCTL_FAULT_STATUS1_0         0xF000800C            /*  FaultCtl Fault Status register 1 for fault0b pin */
#define REG_FAULTCTL_FAULT_STATUS2_0_RESET   0x00000000            /*      Reset Value for fault_status2_0  */
#define REG_FAULTCTL_FAULT_STATUS2_0         0xF0008010            /*  FaultCtl Fault Status register 2 for fault0b pin */
#define REG_FAULTCTL_FAULT_STATUS0_1_RESET   0x00000000            /*      Reset Value for fault_status0_1  */
#define REG_FAULTCTL_FAULT_STATUS0_1         0xF0008014            /*  FaultCtl Fault Status register 0 for fault 1 pin */
#define REG_FAULTCTL_FAULT_STATUS1_1_RESET   0x00000000            /*      Reset Value for fault_status1_1  */
#define REG_FAULTCTL_FAULT_STATUS1_1         0xF0008018            /*  FaultCtl Fault Status register 1 for fault 1 pin */
#define REG_FAULTCTL_FAULT_STATUS2_1_RESET   0x00000000            /*      Reset Value for fault_status2_1  */
#define REG_FAULTCTL_FAULT_STATUS2_1         0xF000801C            /*  FaultCtl Fault Status register 2 for fault 1 pin */
#define REG_FAULTCTL_SOFTWARE_FAULT_CLR_0_RESET 0x00000000            /*      Reset Value for software_fault_clr_0  */
#define REG_FAULTCTL_SOFTWARE_FAULT_CLR_0    0xF0008020            /*  FaultCtl Software fault clear register 0 */
#define REG_FAULTCTL_SOFTWARE_FAULT_CLR_1_RESET 0x00000000            /*      Reset Value for software_fault_clr_1  */
#define REG_FAULTCTL_SOFTWARE_FAULT_CLR_1    0xF0008024            /*  FaultCtl Software fault clear register 1 */
#define REG_FAULTCTL_SOFTWARE_FAULT_CLR_2_RESET 0x00000000            /*      Reset Value for software_fault_clr_2  */
#define REG_FAULTCTL_SOFTWARE_FAULT_CLR_2    0xF0008028            /*  FaultCtl Software fault clear register 1 */
#define REG_FAULTCTL_SOFTWARE_FAULT_CLR_3_RESET 0x00000000            /*      Reset Value for software_fault_clr_3  */
#define REG_FAULTCTL_SOFTWARE_FAULT_CLR_3    0xF000802C            /*  FaultCtl Software fault clear register 1 */
#define REG_FAULTCTL_SOFTWARE_FAULT_SET_0_RESET 0x00000000            /*      Reset Value for software_fault_set_0  */
#define REG_FAULTCTL_SOFTWARE_FAULT_SET_0    0xF0008040            /*  FaultCtl Software fault set register 0 */
#define REG_FAULTCTL_SOFTWARE_FAULT_SET_1_RESET 0x00000000            /*      Reset Value for software_fault_set_1  */
#define REG_FAULTCTL_SOFTWARE_FAULT_SET_1    0xF0008044            /*  FaultCtl Software fault set register 1 */
#define REG_FAULTCTL_SOFTWARE_FAULT_SET_2_RESET 0x00000000            /*      Reset Value for software_fault_set_2  */
#define REG_FAULTCTL_SOFTWARE_FAULT_SET_2    0xF0008048            /*  FaultCtl Software fault set register 1 */
#define REG_FAULTCTL_SOFTWARE_FAULT_SET_3_RESET 0x00000000            /*      Reset Value for software_fault_set_3  */
#define REG_FAULTCTL_SOFTWARE_FAULT_SET_3    0xF000804C            /*  FaultCtl Software fault set register 1 */
#define REG_FAULTCTL_SOFTWARE_FAULT_0_RESET  0x00000000            /*      Reset Value for software_fault_0  */
#define REG_FAULTCTL_SOFTWARE_FAULT_0        0xF0008050            /*  FaultCtl Software fault register 0 */
#define REG_FAULTCTL_SOFTWARE_FAULT_1_RESET  0x00000000            /*      Reset Value for software_fault_1  */
#define REG_FAULTCTL_SOFTWARE_FAULT_1        0xF0008054            /*  FaultCtl Software fault register 1 */
#define REG_FAULTCTL_SOFTWARE_FAULT_2_RESET  0x00000000            /*      Reset Value for software_fault_2  */
#define REG_FAULTCTL_SOFTWARE_FAULT_2        0xF0008058            /*  FaultCtl Software fault register 2 */
#define REG_FAULTCTL_SOFTWARE_FAULT_3_RESET  0x00000000            /*      Reset Value for software_fault_3  */
#define REG_FAULTCTL_SOFTWARE_FAULT_3        0xF000805C            /*  FaultCtl Software fault register 3 */
#define REG_FAULTCTL_FAULT_MASK0_0_RESET     0xFC000000            /*      Reset Value for fault_mask0_0  */
#define REG_FAULTCTL_FAULT_MASK0_0           0xF0008060            /*  FaultCtl Fault mask register 0 */
#define REG_FAULTCTL_FAULT_MASK1_0_RESET     0x00000000            /*      Reset Value for fault_mask1_0  */
#define REG_FAULTCTL_FAULT_MASK1_0           0xF0008064            /*  FaultCtl Fault mask register 1 */
#define REG_FAULTCTL_FAULT_MASK2_0_RESET     0x00000000            /*      Reset Value for fault_mask2_0  */
#define REG_FAULTCTL_FAULT_MASK2_0           0xF0008068            /*  FaultCtl Mask register for fault_status2_0 */
#define REG_FAULTCTL_FAULT_MASK0_1_RESET     0xFC000000            /*      Reset Value for fault_mask0_1  */
#define REG_FAULTCTL_FAULT_MASK0_1           0xF000806C            /*  FaultCtl Fault mask register 0 */
#define REG_FAULTCTL_FAULT_MASK1_1_RESET     0x00000000            /*      Reset Value for fault_mask1_1  */
#define REG_FAULTCTL_FAULT_MASK1_1           0xF0008070            /*  FaultCtl Fault mask register 1 */
#define REG_FAULTCTL_FAULT_MASK2_1_RESET     0x00000000            /*      Reset Value for fault_mask2_1  */
#define REG_FAULTCTL_FAULT_MASK2_1           0xF0008074            /*  FaultCtl Mask register for fault_status2_1 */
#define REG_FAULTCTL_FAULT_SW_MASK_0_0_RESET 0x00000000            /*      Reset Value for fault_sw_mask_0_0  */
#define REG_FAULTCTL_FAULT_SW_MASK_0_0       0xF0008078            /*  FaultCtl Software mask register 0 for fault0b */
#define REG_FAULTCTL_FAULT_SW_MASK_1_0_RESET 0x00000000            /*      Reset Value for fault_sw_mask_1_0  */
#define REG_FAULTCTL_FAULT_SW_MASK_1_0       0xF000807C            /*  FaultCtl Software mask register 1 for fault0b */
#define REG_FAULTCTL_FAULT_SW_MASK_2_0_RESET 0x00000000            /*      Reset Value for fault_sw_mask_2_0  */
#define REG_FAULTCTL_FAULT_SW_MASK_2_0       0xF0008080            /*  FaultCtl Software mask register 1 for fault0b */
#define REG_FAULTCTL_FAULT_SW_MASK_3_0_RESET 0x00000000            /*      Reset Value for fault_sw_mask_3_0  */
#define REG_FAULTCTL_FAULT_SW_MASK_3_0       0xF0008084            /*  FaultCtl Software mask register 1 for fault0b */
#define REG_FAULTCTL_FAULT_SW_MASK_0_1_RESET 0x00000000            /*      Reset Value for fault_sw_mask_0_1  */
#define REG_FAULTCTL_FAULT_SW_MASK_0_1       0xF0008088            /*  FaultCtl Software mask register 0 for fault1 */
#define REG_FAULTCTL_FAULT_SW_MASK_1_1_RESET 0x00000000            /*      Reset Value for fault_sw_mask_1_1  */
#define REG_FAULTCTL_FAULT_SW_MASK_1_1       0xF000808C            /*  FaultCtl Software mask register 1 for fault1 */
#define REG_FAULTCTL_FAULT_SW_MASK_2_1_RESET 0x00000000            /*      Reset Value for fault_sw_mask_2_1  */
#define REG_FAULTCTL_FAULT_SW_MASK_2_1       0xF0008090            /*  FaultCtl Software mask register 1 for fault1 */
#define REG_FAULTCTL_FAULT_SW_MASK_3_1_RESET 0x00000000            /*      Reset Value for fault_sw_mask_3_1  */
#define REG_FAULTCTL_FAULT_SW_MASK_3_1       0xF0008094            /*  FaultCtl Software mask register 1 for fault1 */
#define REG_FAULTCTL_FAULT_CTRL_RESET        0x00000000            /*      Reset Value for fault_ctrl  */
#define REG_FAULTCTL_FAULT_CTRL              0xF0008098            /*  FaultCtl Fault control register */

/* ============================================================================================================================
        FaultCtl Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_STATUS0_0             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_STATUS0_0_AFE3_FAULT 31            /*  Combined AFE3 fault */
#define BITP_FAULTCTL_FAULT_STATUS0_0_AFE2_FAULT 30            /*  Combined AFE2 fault */
#define BITP_FAULTCTL_FAULT_STATUS0_0_AFE1_FAULT 29            /*  Combined AFE1 fault */
#define BITP_FAULTCTL_FAULT_STATUS0_0_AFE0_FAULT 28            /*  Combined AFE0 fault */
#define BITP_FAULTCTL_FAULT_STATUS0_0_LO_PG_1P8 27            /*  LO LDO PGOOD error (when low) */
#define BITP_FAULTCTL_FAULT_STATUS0_0_TX_PG_1P8 26            /*  TX LDO PGOOD error (when low) */
#define BITP_FAULTCTL_FAULT_STATUS0_0_FABRIC_PARITY_HADDR_ERR 25            /*  Fabric parity error */
#define BITP_FAULTCTL_FAULT_STATUS0_0_SPI_REG_INVALID_WRITE 24            /*  SPI invalid write fault */
#define BITP_FAULTCTL_FAULT_STATUS0_0_BUS_ACCESS_ERR 23            /*  SPI bus access error */
#define BITP_FAULTCTL_FAULT_STATUS0_0_FABRIC_CRC_ERR 22            /*  Fabric CRC error */
#define BITP_FAULTCTL_FAULT_STATUS0_0_DMA_LOCKSTEP_ERR 21            /*  DMA lockstep error */
#define BITP_FAULTCTL_FAULT_STATUS0_0_DMA_ERR 20            /*  DMA access error */
#define BITP_FAULTCTL_FAULT_STATUS0_0_LVDS_FAULT_RX_EXTIF_LVDS 19            /*  LVDS fault */
#define BITP_FAULTCTL_FAULT_STATUS0_0_MIPI_FAULT_RX_EXTIF_CSI2 18            /*  MIPI fault */
#define BITP_FAULTCTL_FAULT_STATUS0_0_WDT_FAULT 17            /*  WDT fault */
#define BITP_FAULTCTL_FAULT_STATUS0_0_DDS_ECC_DB_ERR 16            /*  DDS double bit ECC error */
#define BITP_FAULTCTL_FAULT_STATUS0_0_DDS_ECC_SB_ERR 15            /*  DDS single bit ECC error */
#define BITP_FAULTCTL_FAULT_STATUS0_0_OTP_FAULT_DED_OTPC 14            /*  OTP double error detect fault */
#define BITP_FAULTCTL_FAULT_STATUS0_0_SPI_REG_INVALID_LEN_FAULT 13            /*  SPI invalid len access fault */
#define BITP_FAULTCTL_FAULT_STATUS0_0_SPI_REG_INVALID_ADDR_ACC_FAULT 12            /*  SPI invalid address access fault */
#define BITP_FAULTCTL_FAULT_STATUS0_0_SPI_INTF_CNFG0_WRITE_FAULT 11            /*  SPI config write fault */
#define BITP_FAULTCTL_FAULT_STATUS0_0_SPI_LEN_ERR 10            /*  SPI length error */
#define BITP_FAULTCTL_FAULT_STATUS0_0_SPI_LEN_MSBYTE_FAULT  9            /*  SPI MSB fault */
#define BITP_FAULTCTL_FAULT_STATUS0_0_SPI_CMD_ERR  8            /*  SPI command error */
#define BITP_FAULTCTL_FAULT_STATUS0_0_ARC_LOCKSTEP_OUT  7            /*  ARC lockstep error */
#define BITP_FAULTCTL_FAULT_STATUS0_0_ARC_ECC_DCCM_ADDR_ERROR_R  6            /*  ARC DCCM adder ECC error */
#define BITP_FAULTCTL_FAULT_STATUS0_0_ARC_ECC_DCCM_SB_ERROR_R  5            /*  ARC DCCM single bit ECC error */
#define BITP_FAULTCTL_FAULT_STATUS0_0_ARC_ECC_DCCM_DB_ERROR_R  4            /*  ARC DCCM double bit ECC error */
#define BITP_FAULTCTL_FAULT_STATUS0_0_ARC_ECC_ICCM_ADDR_ERROR_R  3            /*  ARC ICCM address ECC error */
#define BITP_FAULTCTL_FAULT_STATUS0_0_ARC_ECC_ICCM_DB_ERROR_R  2            /*  ARC ICCM double bit ECC error */
#define BITP_FAULTCTL_FAULT_STATUS0_0_ARC_ECC_ICCM_SB_ERROR_R  1            /*  ARC ICCM single bit ECC error */
#define BITP_FAULTCTL_FAULT_STATUS0_0_ARC_WDT_EXT_TIMEOUT_R  0            /*  ARC WDT timeout */
#define BITM_FAULTCTL_FAULT_STATUS0_0_AFE3_FAULT 0x80000000    /*  Combined AFE3 fault */
#define BITM_FAULTCTL_FAULT_STATUS0_0_AFE2_FAULT 0x40000000    /*  Combined AFE2 fault */
#define BITM_FAULTCTL_FAULT_STATUS0_0_AFE1_FAULT 0x20000000    /*  Combined AFE1 fault */
#define BITM_FAULTCTL_FAULT_STATUS0_0_AFE0_FAULT 0x10000000    /*  Combined AFE0 fault */
#define BITM_FAULTCTL_FAULT_STATUS0_0_LO_PG_1P8 0x08000000    /*  LO LDO PGOOD error (when low) */
#define BITM_FAULTCTL_FAULT_STATUS0_0_TX_PG_1P8 0x04000000    /*  TX LDO PGOOD error (when low) */
#define BITM_FAULTCTL_FAULT_STATUS0_0_FABRIC_PARITY_HADDR_ERR 0x02000000    /*  Fabric parity error */
#define BITM_FAULTCTL_FAULT_STATUS0_0_SPI_REG_INVALID_WRITE 0x01000000    /*  SPI invalid write fault */
#define BITM_FAULTCTL_FAULT_STATUS0_0_BUS_ACCESS_ERR 0x00800000    /*  SPI bus access error */
#define BITM_FAULTCTL_FAULT_STATUS0_0_FABRIC_CRC_ERR 0x00400000    /*  Fabric CRC error */
#define BITM_FAULTCTL_FAULT_STATUS0_0_DMA_LOCKSTEP_ERR 0x00200000    /*  DMA lockstep error */
#define BITM_FAULTCTL_FAULT_STATUS0_0_DMA_ERR 0x00100000    /*  DMA access error */
#define BITM_FAULTCTL_FAULT_STATUS0_0_LVDS_FAULT_RX_EXTIF_LVDS 0x00080000    /*  LVDS fault */
#define BITM_FAULTCTL_FAULT_STATUS0_0_MIPI_FAULT_RX_EXTIF_CSI2 0x00040000    /*  MIPI fault */
#define BITM_FAULTCTL_FAULT_STATUS0_0_WDT_FAULT 0x00020000    /*  WDT fault */
#define BITM_FAULTCTL_FAULT_STATUS0_0_DDS_ECC_DB_ERR 0x00010000    /*  DDS double bit ECC error */
#define BITM_FAULTCTL_FAULT_STATUS0_0_DDS_ECC_SB_ERR 0x00008000    /*  DDS single bit ECC error */
#define BITM_FAULTCTL_FAULT_STATUS0_0_OTP_FAULT_DED_OTPC 0x00004000    /*  OTP double error detect fault */
#define BITM_FAULTCTL_FAULT_STATUS0_0_SPI_REG_INVALID_LEN_FAULT 0x00002000    /*  SPI invalid len access fault */
#define BITM_FAULTCTL_FAULT_STATUS0_0_SPI_REG_INVALID_ADDR_ACC_FAULT 0x00001000    /*  SPI invalid address access fault */
#define BITM_FAULTCTL_FAULT_STATUS0_0_SPI_INTF_CNFG0_WRITE_FAULT 0x00000800    /*  SPI config write fault */
#define BITM_FAULTCTL_FAULT_STATUS0_0_SPI_LEN_ERR 0x00000400    /*  SPI length error */
#define BITM_FAULTCTL_FAULT_STATUS0_0_SPI_LEN_MSBYTE_FAULT 0x00000200    /*  SPI MSB fault */
#define BITM_FAULTCTL_FAULT_STATUS0_0_SPI_CMD_ERR 0x00000100    /*  SPI command error */
#define BITM_FAULTCTL_FAULT_STATUS0_0_ARC_LOCKSTEP_OUT 0x00000080    /*  ARC lockstep error */
#define BITM_FAULTCTL_FAULT_STATUS0_0_ARC_ECC_DCCM_ADDR_ERROR_R 0x00000040    /*  ARC DCCM adder ECC error */
#define BITM_FAULTCTL_FAULT_STATUS0_0_ARC_ECC_DCCM_SB_ERROR_R 0x00000020    /*  ARC DCCM single bit ECC error */
#define BITM_FAULTCTL_FAULT_STATUS0_0_ARC_ECC_DCCM_DB_ERROR_R 0x00000010    /*  ARC DCCM double bit ECC error */
#define BITM_FAULTCTL_FAULT_STATUS0_0_ARC_ECC_ICCM_ADDR_ERROR_R 0x00000008    /*  ARC ICCM address ECC error */
#define BITM_FAULTCTL_FAULT_STATUS0_0_ARC_ECC_ICCM_DB_ERROR_R 0x00000004    /*  ARC ICCM double bit ECC error */
#define BITM_FAULTCTL_FAULT_STATUS0_0_ARC_ECC_ICCM_SB_ERROR_R 0x00000002    /*  ARC ICCM single bit ECC error */
#define BITM_FAULTCTL_FAULT_STATUS0_0_ARC_WDT_EXT_TIMEOUT_R 0x00000001    /*  ARC WDT timeout */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_STATUS1_0             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_STATUS1_0_APB_ACC_FAULT 31            /*  Access to APB outside digital when the clocks are shut-off */
#define BITP_FAULTCTL_FAULT_STATUS1_0_GOERTZEL_OV_UV_ERR 30            /*  Goertzel Overflow/Underflow error */
#define BITP_FAULTCTL_FAULT_STATUS1_0_FABRIC_PARITY_HRDATA_ERR 29            /*  Fabric hrdata parity */
#define BITP_FAULTCTL_FAULT_STATUS1_0_FABRIC_PARITY_HWDATA_ERR 28            /*  Fabric hwdata parity */
#define BITP_FAULTCTL_FAULT_STATUS1_0_MIPI_CSI2_DIAG_FAULT 27            /*  Diagnostic faults from MIPI csi2 */
#define BITP_FAULTCTL_FAULT_STATUS1_0_AFE3_UNDERFLOW_OVERFLOW 26            /*  Decimation filter channel 3 overflow/underflow fault */
#define BITP_FAULTCTL_FAULT_STATUS1_0_AFE2_UNDERFLOW_OVERFLOW 25            /*  Decimation filter channel 2 overflow/underflow fault */
#define BITP_FAULTCTL_FAULT_STATUS1_0_AFE1_UNDERFLOW_OVERFLOW 24            /*  Decimation filter channel 1 overflow/underflow fault */
#define BITP_FAULTCTL_FAULT_STATUS1_0_AFE0_UNDERFLOW_OVERFLOW 23            /*  Decimation filter channel 0 overflow/underflow fault */
#define BITP_FAULTCTL_FAULT_STATUS1_0_FFT_DB_ECC 22            /*  FFT RAM/ROM double-bit ECC error */
#define BITP_FAULTCTL_FAULT_STATUS1_0_FFT_SB_ECC 21            /*  FFT RAM/ROM Single bit ECC error */
#define BITP_FAULTCTL_FAULT_STATUS1_0_FFT_MAC_STATUS_ERR 20            /*  FFT mac underflow/overflow error */
#define BITP_FAULTCTL_FAULT_STATUS1_0_WDT_1_FAULT 19            /*  WDT_1 fault */
#define BITP_FAULTCTL_FAULT_STATUS1_0_AFE3_VAL_MORETHAN_ULIM 18            /*  AFE3 decimation filter output greater than upper limit */
#define BITP_FAULTCTL_FAULT_STATUS1_0_AFE3_VAL_LESSTHAN_LLIM 17            /*  AFE3 decimation filter output less than lower limit */
#define BITP_FAULTCTL_FAULT_STATUS1_0_AFE2_VAL_MORETHAN_ULIM 16            /*  AFE2 decimation filter output greater than upper limit */
#define BITP_FAULTCTL_FAULT_STATUS1_0_AFE2_VAL_LESSTHAN_LLIM 15            /*  AFE2 decimation filter output less than lower limit */
#define BITP_FAULTCTL_FAULT_STATUS1_0_AFE1_VAL_MORETHAN_ULIM 14            /*  AFE1 decimation filter output greater than upper limit */
#define BITP_FAULTCTL_FAULT_STATUS1_0_AFE1_VAL_LESSTHAN_LLIM 13            /*  AFE1 decimation filter output less than lower limit */
#define BITP_FAULTCTL_FAULT_STATUS1_0_AFE0_VAL_MORETHAN_ULIM 12            /*  AFE0 decimation filter output greater than upper limit */
#define BITP_FAULTCTL_FAULT_STATUS1_0_AFE0_VAL_LESSTHAN_LLIM 11            /*  AFE0 decimation filter output less than lower limit */
#define BITP_FAULTCTL_FAULT_STATUS1_0_STAT_MON_SAT_FAULT  9            /*  Timing comparator counter reaches pos/neg saturation */
#define BITP_FAULTCTL_FAULT_STATUS1_0_STAT1_MON_FAULT  8            /*  STAT mon fault */
#define BITP_FAULTCTL_FAULT_STATUS1_0_RFPLL_FAULT  7            /*  RFPLL fault */
#define BITP_FAULTCTL_FAULT_STATUS1_0_ADCPLL_FAULT  6            /*  ADCPLL fault */
#define BITP_FAULTCTL_FAULT_STATUS1_0_SOFTWARE_FAULT  5            /*  Combined software fault status */
#define BITP_FAULTCTL_FAULT_STATUS1_0_SPI_SCK_EDGE_CNT_ERR  4            /*  SPI SCK clock edge count error */
#define BITP_FAULTCTL_FAULT_STATUS1_0_SPI_BYTE_RCVD_CNT_ERR  3            /*  SPI byte received count error */
#define BITP_FAULTCTL_FAULT_STATUS1_0_SPI_CRC_FAIL  2            /*  SPI CRC check fail */
#define BITP_FAULTCTL_FAULT_STATUS1_0_SPI_ERR_STATUS  1            /*  SPI error */
#define BITP_FAULTCTL_FAULT_STATUS1_0_OTP_FAULT_SED_OTPC  0            /*  OTP single error detect fault */
#define BITM_FAULTCTL_FAULT_STATUS1_0_APB_ACC_FAULT 0x80000000    /*  Access to APB outside digital when the clocks are shut-off */
#define BITM_FAULTCTL_FAULT_STATUS1_0_GOERTZEL_OV_UV_ERR 0x40000000    /*  Goertzel Overflow/Underflow error */
#define BITM_FAULTCTL_FAULT_STATUS1_0_FABRIC_PARITY_HRDATA_ERR 0x20000000    /*  Fabric hrdata parity */
#define BITM_FAULTCTL_FAULT_STATUS1_0_FABRIC_PARITY_HWDATA_ERR 0x10000000    /*  Fabric hwdata parity */
#define BITM_FAULTCTL_FAULT_STATUS1_0_MIPI_CSI2_DIAG_FAULT 0x08000000    /*  Diagnostic faults from MIPI csi2 */
#define BITM_FAULTCTL_FAULT_STATUS1_0_AFE3_UNDERFLOW_OVERFLOW 0x04000000    /*  Decimation filter channel 3 overflow/underflow fault */
#define BITM_FAULTCTL_FAULT_STATUS1_0_AFE2_UNDERFLOW_OVERFLOW 0x02000000    /*  Decimation filter channel 2 overflow/underflow fault */
#define BITM_FAULTCTL_FAULT_STATUS1_0_AFE1_UNDERFLOW_OVERFLOW 0x01000000    /*  Decimation filter channel 1 overflow/underflow fault */
#define BITM_FAULTCTL_FAULT_STATUS1_0_AFE0_UNDERFLOW_OVERFLOW 0x00800000    /*  Decimation filter channel 0 overflow/underflow fault */
#define BITM_FAULTCTL_FAULT_STATUS1_0_FFT_DB_ECC 0x00400000    /*  FFT RAM/ROM double-bit ECC error */
#define BITM_FAULTCTL_FAULT_STATUS1_0_FFT_SB_ECC 0x00200000    /*  FFT RAM/ROM Single bit ECC error */
#define BITM_FAULTCTL_FAULT_STATUS1_0_FFT_MAC_STATUS_ERR 0x00100000    /*  FFT mac underflow/overflow error */
#define BITM_FAULTCTL_FAULT_STATUS1_0_WDT_1_FAULT 0x00080000    /*  WDT_1 fault */
#define BITM_FAULTCTL_FAULT_STATUS1_0_AFE3_VAL_MORETHAN_ULIM 0x00040000    /*  AFE3 decimation filter output greater than upper limit */
#define BITM_FAULTCTL_FAULT_STATUS1_0_AFE3_VAL_LESSTHAN_LLIM 0x00020000    /*  AFE3 decimation filter output less than lower limit */
#define BITM_FAULTCTL_FAULT_STATUS1_0_AFE2_VAL_MORETHAN_ULIM 0x00010000    /*  AFE2 decimation filter output greater than upper limit */
#define BITM_FAULTCTL_FAULT_STATUS1_0_AFE2_VAL_LESSTHAN_LLIM 0x00008000    /*  AFE2 decimation filter output less than lower limit */
#define BITM_FAULTCTL_FAULT_STATUS1_0_AFE1_VAL_MORETHAN_ULIM 0x00004000    /*  AFE1 decimation filter output greater than upper limit */
#define BITM_FAULTCTL_FAULT_STATUS1_0_AFE1_VAL_LESSTHAN_LLIM 0x00002000    /*  AFE1 decimation filter output less than lower limit */
#define BITM_FAULTCTL_FAULT_STATUS1_0_AFE0_VAL_MORETHAN_ULIM 0x00001000    /*  AFE0 decimation filter output greater than upper limit */
#define BITM_FAULTCTL_FAULT_STATUS1_0_AFE0_VAL_LESSTHAN_LLIM 0x00000800    /*  AFE0 decimation filter output less than lower limit */
#define BITM_FAULTCTL_FAULT_STATUS1_0_STAT_MON_SAT_FAULT 0x00000200    /*  Timing comparator counter reaches pos/neg saturation */
#define BITM_FAULTCTL_FAULT_STATUS1_0_STAT1_MON_FAULT 0x00000100    /*  STAT mon fault */
#define BITM_FAULTCTL_FAULT_STATUS1_0_RFPLL_FAULT 0x00000080    /*  RFPLL fault */
#define BITM_FAULTCTL_FAULT_STATUS1_0_ADCPLL_FAULT 0x00000040    /*  ADCPLL fault */
#define BITM_FAULTCTL_FAULT_STATUS1_0_SOFTWARE_FAULT 0x00000020    /*  Combined software fault status */
#define BITM_FAULTCTL_FAULT_STATUS1_0_SPI_SCK_EDGE_CNT_ERR 0x00000010    /*  SPI SCK clock edge count error */
#define BITM_FAULTCTL_FAULT_STATUS1_0_SPI_BYTE_RCVD_CNT_ERR 0x00000008    /*  SPI byte received count error */
#define BITM_FAULTCTL_FAULT_STATUS1_0_SPI_CRC_FAIL 0x00000004    /*  SPI CRC check fail */
#define BITM_FAULTCTL_FAULT_STATUS1_0_SPI_ERR_STATUS 0x00000002    /*  SPI error */
#define BITM_FAULTCTL_FAULT_STATUS1_0_OTP_FAULT_SED_OTPC 0x00000001    /*  OTP single error detect fault */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_STATUS2_0             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_STATUS2_0_ARC_ECC_EXCEPTION_ERR 20            /*  ARC ECC exception handler fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_SSB_ROM_ECC_ERR 19            /*  ECC error in SSB ROM memory */
#define BITP_FAULTCTL_FAULT_STATUS2_0_FW_RO_FAULT 18            /*  Firmware status register RO redundancy fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_FILTER_VALID_SYNC_FAULT 17            /*  Filter and Ramp valid fall edge out of sync fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_TIMING_COMP_RO_FAULT 16            /*  Timing comparator RO fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_SPI_STATUS_AUX_RO_FAULT 15            /*  SPI aux status fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_COMP_CHECK_FAULT 14            /*  Decimation filter BIST67 comparator fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_ARC_TRIPLE_FAULT 13            /*  ARC triple fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_PINT_RO_FAULT 12            /*  PINT RO fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_ADCPLL_RO_FAULT 11            /*  ADCPLL RO fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_AFE3_RO_FAULT 10            /*  AFE3 RO fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_AFE2_RO_FAULT  9            /*  AFE2 RO fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_AFE1_RO_FAULT  8            /*  AFE1 RO fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_AFE0_RO_FAULT  7            /*  AFE0 RO fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_DATAPORT_RO_FAULT  6            /*  Dataport RO fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_DDS_RO_FAULT  5            /*  DDS RO fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_GOERTZEL_RO_FAULT  4            /*  Goertzel HW engine RO fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_SYSCTL_RO_FAULT  3            /*  System controller RO fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_RFPLL_RO_FAULT  2            /*  RFPLL RO fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_OTPC_RO_FAULT  1            /*  OTPC RO fault */
#define BITP_FAULTCTL_FAULT_STATUS2_0_HADC_RO_FAULT  0            /*  HADC RO fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_ARC_ECC_EXCEPTION_ERR 0x00100000    /*  ARC ECC exception handler fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_SSB_ROM_ECC_ERR 0x00080000    /*  ECC error in SSB ROM memory */
#define BITM_FAULTCTL_FAULT_STATUS2_0_FW_RO_FAULT 0x00040000    /*  Firmware status register RO redundancy fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_FILTER_VALID_SYNC_FAULT 0x00020000    /*  Filter and Ramp valid fall edge out of sync fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_TIMING_COMP_RO_FAULT 0x00010000    /*  Timing comparator RO fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_SPI_STATUS_AUX_RO_FAULT 0x00008000    /*  SPI aux status fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_COMP_CHECK_FAULT 0x00004000    /*  Decimation filter BIST67 comparator fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_ARC_TRIPLE_FAULT 0x00002000    /*  ARC triple fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_PINT_RO_FAULT 0x00001000    /*  PINT RO fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_ADCPLL_RO_FAULT 0x00000800    /*  ADCPLL RO fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_AFE3_RO_FAULT 0x00000400    /*  AFE3 RO fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_AFE2_RO_FAULT 0x00000200    /*  AFE2 RO fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_AFE1_RO_FAULT 0x00000100    /*  AFE1 RO fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_AFE0_RO_FAULT 0x00000080    /*  AFE0 RO fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_DATAPORT_RO_FAULT 0x00000040    /*  Dataport RO fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_DDS_RO_FAULT 0x00000020    /*  DDS RO fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_GOERTZEL_RO_FAULT 0x00000010    /*  Goertzel HW engine RO fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_SYSCTL_RO_FAULT 0x00000008    /*  System controller RO fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_RFPLL_RO_FAULT 0x00000004    /*  RFPLL RO fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_OTPC_RO_FAULT 0x00000002    /*  OTPC RO fault */
#define BITM_FAULTCTL_FAULT_STATUS2_0_HADC_RO_FAULT 0x00000001    /*  HADC RO fault */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_STATUS0_1             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_STATUS0_1_AFE3_FAULT2 31            /*  afe3 fault */
#define BITP_FAULTCTL_FAULT_STATUS0_1_AFE2_FAULT2 30            /*  afe2 fault */
#define BITP_FAULTCTL_FAULT_STATUS0_1_AFE1_FAULT2 29            /*  afe1 fault */
#define BITP_FAULTCTL_FAULT_STATUS0_1_AFE0_FAULT2 28            /*  afe0 fault */
#define BITP_FAULTCTL_FAULT_STATUS0_1_LO_PG_1P8_2 27            /*  lo power good */
#define BITP_FAULTCTL_FAULT_STATUS0_1_TX_PG_1P8_2 26            /*  tx power good */
#define BITP_FAULTCTL_FAULT_STATUS0_1_FABRIC_PARITY_HADDR_ERR2 25            /*  fabric parity */
#define BITP_FAULTCTL_FAULT_STATUS0_1_SPI_REG_INVALID_WRITE2 24            /*  spi invalid write */
#define BITP_FAULTCTL_FAULT_STATUS0_1_BUS_ACCESS_ERR2 23            /*  bus access error */
#define BITP_FAULTCTL_FAULT_STATUS0_1_FABRIC_CRC_ERR2 22            /*  fabric crc error */
#define BITP_FAULTCTL_FAULT_STATUS0_1_DMA_LOCKSTEP_ERR2 21            /*  dma lockstep */
#define BITP_FAULTCTL_FAULT_STATUS0_1_DMA_ERR2 20            /*  dma fault */
#define BITP_FAULTCTL_FAULT_STATUS0_1_LVDS_FAULT_RX_EXTIF_LVDS2 19            /*  lvds fault */
#define BITP_FAULTCTL_FAULT_STATUS0_1_MIPI_FAULT_RX_EXTIF_CSI2_2 18            /*  mipi fault */
#define BITP_FAULTCTL_FAULT_STATUS0_1_WDT_FAULT2 17            /*  wdt fault */
#define BITP_FAULTCTL_FAULT_STATUS0_1_DDS_ECC_DB_ERR2 16            /*  dds db ecc error */
#define BITP_FAULTCTL_FAULT_STATUS0_1_DDS_ECC_SB_ERR2 15            /*  dds sb ecc error */
#define BITP_FAULTCTL_FAULT_STATUS0_1_OTP_FAULT_DED_OTPC2 14            /*  otpc ded fault */
#define BITP_FAULTCTL_FAULT_STATUS0_1_SPI_REG_INVALID_LEN_FAULT2 13            /*  spi invalid length error */
#define BITP_FAULTCTL_FAULT_STATUS0_1_SPI_REG_INVALID_ADDR_ACC_FAULT2 12            /*  spi invalid addr access error */
#define BITP_FAULTCTL_FAULT_STATUS0_1_SPI_INTF_CNFG0_WRITE_FAULT2 11            /*  spi interface config error */
#define BITP_FAULTCTL_FAULT_STATUS0_1_SPI_LEN_ERR2 10            /*  spi length error */
#define BITP_FAULTCTL_FAULT_STATUS0_1_SPI_LEN_MSBYTE_FAULT2  9            /*  spi msbyte len error */
#define BITP_FAULTCTL_FAULT_STATUS0_1_SPI_CMD_ERR2  8            /*  spi command error */
#define BITP_FAULTCTL_FAULT_STATUS0_1_ARC_LOCKSTEP_OUT2  7            /*  arc lockstep error */
#define BITP_FAULTCTL_FAULT_STATUS0_1_ARC_ECC_DCCM_ADDR_ERROR_R2  6            /*  arc dccm addr error */
#define BITP_FAULTCTL_FAULT_STATUS0_1_ARC_ECC_DCCM_SB_ERROR_R2  5            /*  arc dccm sb error */
#define BITP_FAULTCTL_FAULT_STATUS0_1_ARC_ECC_DCCM_DB_ERROR_R2  4            /*  arc dccm db error */
#define BITP_FAULTCTL_FAULT_STATUS0_1_ARC_ECC_ICCM_ADDR_ERROR_R2  3            /*  ARC ICCM ADDR ecc error */
#define BITP_FAULTCTL_FAULT_STATUS0_1_ARC_ECC_ICCM_DB_ERROR_R2  2            /*  ARC ICCM DB ERROR */
#define BITP_FAULTCTL_FAULT_STATUS0_1_ARC_ECC_ICCM_SB_ERROR_R2  1            /*  ARC ICCM SB error */
#define BITP_FAULTCTL_FAULT_STATUS0_1_ARC_WDT_EXT_TIMEOUT_R2  0            /*  ARC wdt external timeout */
#define BITM_FAULTCTL_FAULT_STATUS0_1_AFE3_FAULT2 0x80000000    /*  afe3 fault */
#define BITM_FAULTCTL_FAULT_STATUS0_1_AFE2_FAULT2 0x40000000    /*  afe2 fault */
#define BITM_FAULTCTL_FAULT_STATUS0_1_AFE1_FAULT2 0x20000000    /*  afe1 fault */
#define BITM_FAULTCTL_FAULT_STATUS0_1_AFE0_FAULT2 0x10000000    /*  afe0 fault */
#define BITM_FAULTCTL_FAULT_STATUS0_1_LO_PG_1P8_2 0x08000000    /*  lo power good */
#define BITM_FAULTCTL_FAULT_STATUS0_1_TX_PG_1P8_2 0x04000000    /*  tx power good */
#define BITM_FAULTCTL_FAULT_STATUS0_1_FABRIC_PARITY_HADDR_ERR2 0x02000000    /*  fabric parity */
#define BITM_FAULTCTL_FAULT_STATUS0_1_SPI_REG_INVALID_WRITE2 0x01000000    /*  spi invalid write */
#define BITM_FAULTCTL_FAULT_STATUS0_1_BUS_ACCESS_ERR2 0x00800000    /*  bus access error */
#define BITM_FAULTCTL_FAULT_STATUS0_1_FABRIC_CRC_ERR2 0x00400000    /*  fabric crc error */
#define BITM_FAULTCTL_FAULT_STATUS0_1_DMA_LOCKSTEP_ERR2 0x00200000    /*  dma lockstep */
#define BITM_FAULTCTL_FAULT_STATUS0_1_DMA_ERR2 0x00100000    /*  dma fault */
#define BITM_FAULTCTL_FAULT_STATUS0_1_LVDS_FAULT_RX_EXTIF_LVDS2 0x00080000    /*  lvds fault */
#define BITM_FAULTCTL_FAULT_STATUS0_1_MIPI_FAULT_RX_EXTIF_CSI2_2 0x00040000    /*  mipi fault */
#define BITM_FAULTCTL_FAULT_STATUS0_1_WDT_FAULT2 0x00020000    /*  wdt fault */
#define BITM_FAULTCTL_FAULT_STATUS0_1_DDS_ECC_DB_ERR2 0x00010000    /*  dds db ecc error */
#define BITM_FAULTCTL_FAULT_STATUS0_1_DDS_ECC_SB_ERR2 0x00008000    /*  dds sb ecc error */
#define BITM_FAULTCTL_FAULT_STATUS0_1_OTP_FAULT_DED_OTPC2 0x00004000    /*  otpc ded fault */
#define BITM_FAULTCTL_FAULT_STATUS0_1_SPI_REG_INVALID_LEN_FAULT2 0x00002000    /*  spi invalid length error */
#define BITM_FAULTCTL_FAULT_STATUS0_1_SPI_REG_INVALID_ADDR_ACC_FAULT2 0x00001000    /*  spi invalid addr access error */
#define BITM_FAULTCTL_FAULT_STATUS0_1_SPI_INTF_CNFG0_WRITE_FAULT2 0x00000800    /*  spi interface config error */
#define BITM_FAULTCTL_FAULT_STATUS0_1_SPI_LEN_ERR2 0x00000400    /*  spi length error */
#define BITM_FAULTCTL_FAULT_STATUS0_1_SPI_LEN_MSBYTE_FAULT2 0x00000200    /*  spi msbyte len error */
#define BITM_FAULTCTL_FAULT_STATUS0_1_SPI_CMD_ERR2 0x00000100    /*  spi command error */
#define BITM_FAULTCTL_FAULT_STATUS0_1_ARC_LOCKSTEP_OUT2 0x00000080    /*  arc lockstep error */
#define BITM_FAULTCTL_FAULT_STATUS0_1_ARC_ECC_DCCM_ADDR_ERROR_R2 0x00000040    /*  arc dccm addr error */
#define BITM_FAULTCTL_FAULT_STATUS0_1_ARC_ECC_DCCM_SB_ERROR_R2 0x00000020    /*  arc dccm sb error */
#define BITM_FAULTCTL_FAULT_STATUS0_1_ARC_ECC_DCCM_DB_ERROR_R2 0x00000010    /*  arc dccm db error */
#define BITM_FAULTCTL_FAULT_STATUS0_1_ARC_ECC_ICCM_ADDR_ERROR_R2 0x00000008    /*  ARC ICCM ADDR ecc error */
#define BITM_FAULTCTL_FAULT_STATUS0_1_ARC_ECC_ICCM_DB_ERROR_R2 0x00000004    /*  ARC ICCM DB ERROR */
#define BITM_FAULTCTL_FAULT_STATUS0_1_ARC_ECC_ICCM_SB_ERROR_R2 0x00000002    /*  ARC ICCM SB error */
#define BITM_FAULTCTL_FAULT_STATUS0_1_ARC_WDT_EXT_TIMEOUT_R2 0x00000001    /*  ARC wdt external timeout */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_STATUS1_1             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_STATUS1_1_APB_ACC_FAULT2 31            /*  APB access fault */
#define BITP_FAULTCTL_FAULT_STATUS1_1_GOERTZEL_OV_UV_ERR2 30            /*  Goertzel overflow/underflow error */
#define BITP_FAULTCTL_FAULT_STATUS1_1_FABRIC_PARITY_HRDATA_ERR2 29            /*  fabric parity hrdata error */
#define BITP_FAULTCTL_FAULT_STATUS1_1_FABRIC_PARITY_HWDATA_ERR2 28            /*  fabric parity hwdata error */
#define BITP_FAULTCTL_FAULT_STATUS1_1_MIPI_CSI2_DIAG_FAULT2 27            /*  mipi fault */
#define BITP_FAULTCTL_FAULT_STATUS1_1_AFE3_UNDERFLOW_OVERFLOW2 26            /*  afe3 underflow/overflow error */
#define BITP_FAULTCTL_FAULT_STATUS1_1_AFE2_UNDERFLOW_OVERFLOW2 25            /*  afe2 underflow/overflow error */
#define BITP_FAULTCTL_FAULT_STATUS1_1_AFE1_UNDERFLOW_OVERFLOW2 24            /*  afe1 underflow/overflow error */
#define BITP_FAULTCTL_FAULT_STATUS1_1_AFE0_UNDERFLOW_OVERFLOW2 23            /*  afe0 underflow/overflow error */
#define BITP_FAULTCTL_FAULT_STATUS1_1_FFT_DB_ECC2 22            /*  fft db error */
#define BITP_FAULTCTL_FAULT_STATUS1_1_FFT_SB_ECC2 21            /*  fft sb error */
#define BITP_FAULTCTL_FAULT_STATUS1_1_FFT_MAC_STATUS_ERR2 20            /*  fft mac error */
#define BITP_FAULTCTL_FAULT_STATUS1_1_WDT_1_FAULT2 19            /*  wdt 1 fault */
#define BITP_FAULTCTL_FAULT_STATUS1_1_AFE3_VAL_MORETHAN_ULIM2 18            /*  afe3 greater than lower threshold */
#define BITP_FAULTCTL_FAULT_STATUS1_1_AFE3_VAL_LESSTHAN_LLIM2 17            /*  afe3 lesser than lower threshold */
#define BITP_FAULTCTL_FAULT_STATUS1_1_AFE2_VAL_MORETHAN_ULIM2 16            /*  afe2 greater than upper threshold */
#define BITP_FAULTCTL_FAULT_STATUS1_1_AFE2_VAL_LESSTHAN_LLIM2 15            /*  afe2 lesser than lower threshold */
#define BITP_FAULTCTL_FAULT_STATUS1_1_AFE1_VAL_MORETHAN_ULIM2 14            /*  afe1 greater than upper threshold */
#define BITP_FAULTCTL_FAULT_STATUS1_1_AFE1_VAL_LESSTHAN_LLIM2 13            /*  afe1 lesser than lower threshold */
#define BITP_FAULTCTL_FAULT_STATUS1_1_AFE0_VAL_MORETHAN_ULIM2 12            /*  afe0 more than upper threshold */
#define BITP_FAULTCTL_FAULT_STATUS1_1_AFE0_VAL_LESSTHAN_LLIM2 11            /*  afe0 lesser than lower threshold */
#define BITP_FAULTCTL_FAULT_STATUS1_1_STAT_MON_SAT_FAULT2  9            /*  timing comparator saturation fault */
#define BITP_FAULTCTL_FAULT_STATUS1_1_STAT1_MON_FAULT2  8            /*  timing comparator fault */
#define BITP_FAULTCTL_FAULT_STATUS1_1_RFPLL_FAULT2  7            /*  rfpll fault */
#define BITP_FAULTCTL_FAULT_STATUS1_1_ADCPLL_FAULT2  6            /*  adcpll fault */
#define BITP_FAULTCTL_FAULT_STATUS1_1_SOFTWARE_FAULT2  5            /*  software fault */
#define BITP_FAULTCTL_FAULT_STATUS1_1_SPI_SCK_EDGE_CNT_ERR2  4            /*  spi sck edge count error */
#define BITP_FAULTCTL_FAULT_STATUS1_1_SPI_BYTE_RCVD_CNT_ERR2  3            /*  spi received byte count error */
#define BITP_FAULTCTL_FAULT_STATUS1_1_SPI_CRC_FAIL2  2            /*  spi crc error */
#define BITP_FAULTCTL_FAULT_STATUS1_1_SPI_ERR_STATUS2  1            /*  spi error status */
#define BITP_FAULTCTL_FAULT_STATUS1_1_OTP_FAULT_SED_OTPC2  0            /*  otpc sed error */
#define BITM_FAULTCTL_FAULT_STATUS1_1_APB_ACC_FAULT2 0x80000000    /*  APB access fault */
#define BITM_FAULTCTL_FAULT_STATUS1_1_GOERTZEL_OV_UV_ERR2 0x40000000    /*  Goertzel overflow/underflow error */
#define BITM_FAULTCTL_FAULT_STATUS1_1_FABRIC_PARITY_HRDATA_ERR2 0x20000000    /*  fabric parity hrdata error */
#define BITM_FAULTCTL_FAULT_STATUS1_1_FABRIC_PARITY_HWDATA_ERR2 0x10000000    /*  fabric parity hwdata error */
#define BITM_FAULTCTL_FAULT_STATUS1_1_MIPI_CSI2_DIAG_FAULT2 0x08000000    /*  mipi fault */
#define BITM_FAULTCTL_FAULT_STATUS1_1_AFE3_UNDERFLOW_OVERFLOW2 0x04000000    /*  afe3 underflow/overflow error */
#define BITM_FAULTCTL_FAULT_STATUS1_1_AFE2_UNDERFLOW_OVERFLOW2 0x02000000    /*  afe2 underflow/overflow error */
#define BITM_FAULTCTL_FAULT_STATUS1_1_AFE1_UNDERFLOW_OVERFLOW2 0x01000000    /*  afe1 underflow/overflow error */
#define BITM_FAULTCTL_FAULT_STATUS1_1_AFE0_UNDERFLOW_OVERFLOW2 0x00800000    /*  afe0 underflow/overflow error */
#define BITM_FAULTCTL_FAULT_STATUS1_1_FFT_DB_ECC2 0x00400000    /*  fft db error */
#define BITM_FAULTCTL_FAULT_STATUS1_1_FFT_SB_ECC2 0x00200000    /*  fft sb error */
#define BITM_FAULTCTL_FAULT_STATUS1_1_FFT_MAC_STATUS_ERR2 0x00100000    /*  fft mac error */
#define BITM_FAULTCTL_FAULT_STATUS1_1_WDT_1_FAULT2 0x00080000    /*  wdt 1 fault */
#define BITM_FAULTCTL_FAULT_STATUS1_1_AFE3_VAL_MORETHAN_ULIM2 0x00040000    /*  afe3 greater than lower threshold */
#define BITM_FAULTCTL_FAULT_STATUS1_1_AFE3_VAL_LESSTHAN_LLIM2 0x00020000    /*  afe3 lesser than lower threshold */
#define BITM_FAULTCTL_FAULT_STATUS1_1_AFE2_VAL_MORETHAN_ULIM2 0x00010000    /*  afe2 greater than upper threshold */
#define BITM_FAULTCTL_FAULT_STATUS1_1_AFE2_VAL_LESSTHAN_LLIM2 0x00008000    /*  afe2 lesser than lower threshold */
#define BITM_FAULTCTL_FAULT_STATUS1_1_AFE1_VAL_MORETHAN_ULIM2 0x00004000    /*  afe1 greater than upper threshold */
#define BITM_FAULTCTL_FAULT_STATUS1_1_AFE1_VAL_LESSTHAN_LLIM2 0x00002000    /*  afe1 lesser than lower threshold */
#define BITM_FAULTCTL_FAULT_STATUS1_1_AFE0_VAL_MORETHAN_ULIM2 0x00001000    /*  afe0 more than upper threshold */
#define BITM_FAULTCTL_FAULT_STATUS1_1_AFE0_VAL_LESSTHAN_LLIM2 0x00000800    /*  afe0 lesser than lower threshold */
#define BITM_FAULTCTL_FAULT_STATUS1_1_STAT_MON_SAT_FAULT2 0x00000200    /*  timing comparator saturation fault */
#define BITM_FAULTCTL_FAULT_STATUS1_1_STAT1_MON_FAULT2 0x00000100    /*  timing comparator fault */
#define BITM_FAULTCTL_FAULT_STATUS1_1_RFPLL_FAULT2 0x00000080    /*  rfpll fault */
#define BITM_FAULTCTL_FAULT_STATUS1_1_ADCPLL_FAULT2 0x00000040    /*  adcpll fault */
#define BITM_FAULTCTL_FAULT_STATUS1_1_SOFTWARE_FAULT2 0x00000020    /*  software fault */
#define BITM_FAULTCTL_FAULT_STATUS1_1_SPI_SCK_EDGE_CNT_ERR2 0x00000010    /*  spi sck edge count error */
#define BITM_FAULTCTL_FAULT_STATUS1_1_SPI_BYTE_RCVD_CNT_ERR2 0x00000008    /*  spi received byte count error */
#define BITM_FAULTCTL_FAULT_STATUS1_1_SPI_CRC_FAIL2 0x00000004    /*  spi crc error */
#define BITM_FAULTCTL_FAULT_STATUS1_1_SPI_ERR_STATUS2 0x00000002    /*  spi error status */
#define BITM_FAULTCTL_FAULT_STATUS1_1_OTP_FAULT_SED_OTPC2 0x00000001    /*  otpc sed error */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_STATUS2_1             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_STATUS2_1_ARC_ECC_EXCEPTION_ERR2 20            /*  arc ecc exception */
#define BITP_FAULTCTL_FAULT_STATUS2_1_SSB_ROM_ECC_ERR2 19            /*  ssb rom ecc */
#define BITP_FAULTCTL_FAULT_STATUS2_1_FW_RO_FAULT2 18            /*  fw ro fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_FILTER_VALID_SYNC_FAULT2 17            /*  filter valid sync fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_TIMING_COMP_RO_FAULT2 16            /*  timing comparator ro fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_SPI_STATUS_AUX_RO_FAULT2 15            /*  spi status aux fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_COMP_CHECK_FAULT2 14            /*  comp check fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_ARC_TRIPLE_FAULT2 13            /*  arc triple fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_PINT_RO_FAULT2 12            /*  pint ro fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_ADCPLL_RO_FAULT2 11            /*  adcpll ro fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_AFE3_RO_FAULT2 10            /*  afe3 ro fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_AFE2_RO_FAULT2  9            /*  afe2 ro fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_AFE1_RO_FAULT2  8            /*  afe1 ro fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_AFE0_RO_FAULT2  7            /*  afe0 ro fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_DATAPORT_RO_FAULT2  6            /*  dataport ro fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_DDS_RO_FAULT2  5            /*  dds ro fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_GOERTZEL_RO_FAULT2  4            /*  goertzel ro fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_SYSCTL_RO_FAULT2  3            /*  sysctl ro fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_RFPLL_RO_FAULT2  2            /*  rfpll ro fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_OTPC_RO_FAULT2  1            /*  otpc ro fault */
#define BITP_FAULTCTL_FAULT_STATUS2_1_HADC_RO_FAULT2  0            /*  hadc ro fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_ARC_ECC_EXCEPTION_ERR2 0x00100000    /*  arc ecc exception */
#define BITM_FAULTCTL_FAULT_STATUS2_1_SSB_ROM_ECC_ERR2 0x00080000    /*  ssb rom ecc */
#define BITM_FAULTCTL_FAULT_STATUS2_1_FW_RO_FAULT2 0x00040000    /*  fw ro fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_FILTER_VALID_SYNC_FAULT2 0x00020000    /*  filter valid sync fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_TIMING_COMP_RO_FAULT2 0x00010000    /*  timing comparator ro fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_SPI_STATUS_AUX_RO_FAULT2 0x00008000    /*  spi status aux fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_COMP_CHECK_FAULT2 0x00004000    /*  comp check fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_ARC_TRIPLE_FAULT2 0x00002000    /*  arc triple fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_PINT_RO_FAULT2 0x00001000    /*  pint ro fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_ADCPLL_RO_FAULT2 0x00000800    /*  adcpll ro fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_AFE3_RO_FAULT2 0x00000400    /*  afe3 ro fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_AFE2_RO_FAULT2 0x00000200    /*  afe2 ro fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_AFE1_RO_FAULT2 0x00000100    /*  afe1 ro fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_AFE0_RO_FAULT2 0x00000080    /*  afe0 ro fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_DATAPORT_RO_FAULT2 0x00000040    /*  dataport ro fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_DDS_RO_FAULT2 0x00000020    /*  dds ro fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_GOERTZEL_RO_FAULT2 0x00000010    /*  goertzel ro fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_SYSCTL_RO_FAULT2 0x00000008    /*  sysctl ro fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_RFPLL_RO_FAULT2 0x00000004    /*  rfpll ro fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_OTPC_RO_FAULT2 0x00000002    /*  otpc ro fault */
#define BITM_FAULTCTL_FAULT_STATUS2_1_HADC_RO_FAULT2 0x00000001    /*  hadc ro fault */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_SOFTWARE_FAULT_CLR_0        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_SOFTWARE_FAULT_CLR_0_SOFTWARE_FAULT_0  0            /*  Software fault clear register 0 */
#define BITM_FAULTCTL_SOFTWARE_FAULT_CLR_0_SOFTWARE_FAULT_0 0xFFFFFFFF    /*  Software fault clear register 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_SOFTWARE_FAULT_CLR_1        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_SOFTWARE_FAULT_CLR_1_SOFTWARE_FAULT_1  0            /*  Software fault clear register 1 */
#define BITM_FAULTCTL_SOFTWARE_FAULT_CLR_1_SOFTWARE_FAULT_1 0xFFFFFFFF    /*  Software fault clear register 1 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_SOFTWARE_FAULT_CLR_2        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_SOFTWARE_FAULT_CLR_2_SOFTWARE_FAULT_2  0            /*  Software fault clear register 2 */
#define BITM_FAULTCTL_SOFTWARE_FAULT_CLR_2_SOFTWARE_FAULT_2 0xFFFFFFFF    /*  Software fault clear register 2 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_SOFTWARE_FAULT_CLR_3        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_SOFTWARE_FAULT_CLR_3_SOFTWARE_FAULT_3  0            /*  Software Fault clear register 3 */
#define BITM_FAULTCTL_SOFTWARE_FAULT_CLR_3_SOFTWARE_FAULT_3 0xFFFFFFFF    /*  Software Fault clear register 3 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_SOFTWARE_FAULT_SET_0        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_SOFTWARE_FAULT_SET_0_SOFTWARE_FAULT_0  0            /*  Software fault set register 0 */
#define BITM_FAULTCTL_SOFTWARE_FAULT_SET_0_SOFTWARE_FAULT_0 0xFFFFFFFF    /*  Software fault set register 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_SOFTWARE_FAULT_SET_1        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_SOFTWARE_FAULT_SET_1_SOFTWARE_FAULT_1  0            /*  Software fault set register 1 */
#define BITM_FAULTCTL_SOFTWARE_FAULT_SET_1_SOFTWARE_FAULT_1 0xFFFFFFFF    /*  Software fault set register 1 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_SOFTWARE_FAULT_SET_2        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_SOFTWARE_FAULT_SET_2_SOFTWARE_FAULT_2  0            /*  Software fault set register 2 */
#define BITM_FAULTCTL_SOFTWARE_FAULT_SET_2_SOFTWARE_FAULT_2 0xFFFFFFFF    /*  Software fault set register 2 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_SOFTWARE_FAULT_SET_3        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_SOFTWARE_FAULT_SET_3_SOFTWARE_FAULT_3  0            /*  Software fault set register 3 */
#define BITM_FAULTCTL_SOFTWARE_FAULT_SET_3_SOFTWARE_FAULT_3 0xFFFFFFFF    /*  Software fault set register 3 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_SOFTWARE_FAULT_0            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_SOFTWARE_FAULT_0_SOFTWARE_FAULT_0  0            /*  Software fault register 0 */
#define BITM_FAULTCTL_SOFTWARE_FAULT_0_SOFTWARE_FAULT_0 0xFFFFFFFF    /*  Software fault register 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_SOFTWARE_FAULT_1            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_SOFTWARE_FAULT_1_SOFTWARE_FAULT_1  0            /*  Software fault register 1 */
#define BITM_FAULTCTL_SOFTWARE_FAULT_1_SOFTWARE_FAULT_1 0xFFFFFFFF    /*  Software fault register 1 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_SOFTWARE_FAULT_2            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_SOFTWARE_FAULT_2_SOFTWARE_FAULT_2  0            /*  Software fault register 2 */
#define BITM_FAULTCTL_SOFTWARE_FAULT_2_SOFTWARE_FAULT_2 0xFFFFFFFF    /*  Software fault register 2 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_SOFTWARE_FAULT_3            Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_SOFTWARE_FAULT_3_SOFTWARE_FAULT_3  0            /*  Software Fault register 3 */
#define BITM_FAULTCTL_SOFTWARE_FAULT_3_SOFTWARE_FAULT_3 0xFFFFFFFF    /*  Software Fault register 3 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_MASK0_0               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_MASK0_0_FAULT_MASK_VALUE_0_0  0            /*  fault mask for status_0_0 */
#define BITM_FAULTCTL_FAULT_MASK0_0_FAULT_MASK_VALUE_0_0 0xFFFFFFFF    /*  fault mask for status_0_0 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_MASK1_0               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_MASK1_0_FAULT_MASK_VALUE_1_0  0            /*  fault mask for status_1_0 */
#define BITM_FAULTCTL_FAULT_MASK1_0_FAULT_MASK_VALUE_1_0 0xFFFFFFFF    /*  fault mask for status_1_0 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_MASK2_0               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_MASK2_0_FAULT_MASK_VALUE_2_0  0            /*  fault mask for status_2_0 */
#define BITM_FAULTCTL_FAULT_MASK2_0_FAULT_MASK_VALUE_2_0 0xFFFFFFFF    /*  fault mask for status_2_0 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_MASK0_1               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_MASK0_1_FAULT_MASK_VALUE_0_1  0            /*  fault mask for status_0_1 */
#define BITM_FAULTCTL_FAULT_MASK0_1_FAULT_MASK_VALUE_0_1 0xFFFFFFFF    /*  fault mask for status_0_1 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_MASK1_1               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_MASK1_1_FAULT_MASK_VALUE_1_1  0            /*  fault mask for status_1_1 */
#define BITM_FAULTCTL_FAULT_MASK1_1_FAULT_MASK_VALUE_1_1 0xFFFFFFFF    /*  fault mask for status_1_1 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_MASK2_1               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_MASK2_1_FAULT_MASK_VALUE_2_1  0            /*  fault mask for status_2_1 */
#define BITM_FAULTCTL_FAULT_MASK2_1_FAULT_MASK_VALUE_2_1 0xFFFFFFFF    /*  fault mask for status_2_1 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_SW_MASK_0_0           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_SW_MASK_0_0_SW_MASK_0_0  0            /*  Software fault register 0 mask for fault0b */
#define BITM_FAULTCTL_FAULT_SW_MASK_0_0_SW_MASK_0_0 0xFFFFFFFF    /*  Software fault register 0 mask for fault0b */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_SW_MASK_1_0           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_SW_MASK_1_0_SW_MASK_1_0  0            /*  Software fault register 1 mask for fault0b */
#define BITM_FAULTCTL_FAULT_SW_MASK_1_0_SW_MASK_1_0 0xFFFFFFFF    /*  Software fault register 1 mask for fault0b */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_SW_MASK_2_0           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_SW_MASK_2_0_SW_MASK_2_0  0            /*  Software fault register 2 mask for fault0b */
#define BITM_FAULTCTL_FAULT_SW_MASK_2_0_SW_MASK_2_0 0xFFFFFFFF    /*  Software fault register 2 mask for fault0b */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_SW_MASK_3_0           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_SW_MASK_3_0_SW_MASK_3_0  0            /*  Software fault register 3 mask for fault0b */
#define BITM_FAULTCTL_FAULT_SW_MASK_3_0_SW_MASK_3_0 0xFFFFFFFF    /*  Software fault register 3 mask for fault0b */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_SW_MASK_0_1           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_SW_MASK_0_1_SW_MASK_0_1  0            /*  Software fault register 0 mask for fault1 */
#define BITM_FAULTCTL_FAULT_SW_MASK_0_1_SW_MASK_0_1 0xFFFFFFFF    /*  Software fault register 0 mask for fault1 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_SW_MASK_1_1           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_SW_MASK_1_1_SW_MASK_1_1  0            /*  Software fault register 1 mask for fault1 */
#define BITM_FAULTCTL_FAULT_SW_MASK_1_1_SW_MASK_1_1 0xFFFFFFFF    /*  Software fault register 1 mask for fault1 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_SW_MASK_2_1           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_SW_MASK_2_1_SW_MASK_2_1  0            /*  Software fault register 2 mask for fault1 */
#define BITM_FAULTCTL_FAULT_SW_MASK_2_1_SW_MASK_2_1 0xFFFFFFFF    /*  Software fault register 2 mask for fault1 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_SW_MASK_3_1           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_SW_MASK_3_1_SW_MASK_3_1  0            /*  Software fault register 3 mask for fault1 */
#define BITM_FAULTCTL_FAULT_SW_MASK_3_1_SW_MASK_3_1 0xFFFFFFFF    /*  Software fault register 3 mask for fault1 */

/* -------------------------------------------------------------------------------------------------------------------------
          FaultCtl_FAULT_CTRL                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_FAULTCTL_FAULT_CTRL_PRESCALER    1            /*  Prescaler for the COP mode clock frequency */
#define BITP_FAULTCTL_FAULT_CTRL_COP_MODE     0            /*  COP mode control bit */
#define BITM_FAULTCTL_FAULT_CTRL_PRESCALER   0x0001FFFE    /*  Prescaler for the COP mode clock frequency */
#define BITM_FAULTCTL_FAULT_CTRL_COP_MODE    0x00000001    /*  COP mode control bit */
#define ENUM_FAULTCTL_FAULT_CTRL_EN000       0x00000000            /*  cop_mode: Disable COP mode */
#define ENUM_FAULTCTL_FAULT_CTRL_EN001       0x00000001            /*  cop_mode: Enable COP mode */


/* ============================================================================================================================
        
   ============================================================================================================================ */

/* ============================================================================================================================
        AFE0
   ============================================================================================================================ */
#define REG_AFE0_HPF_CTRL0_RESET             0x00001018            /*      Reset Value for HPF_CTRL0  */
#define REG_AFE0_HPF_CTRL0                   0xF0012000            /*  AFE0 HPF Control 0 */
#define REG_AFE0_PGA_CTRL0_RESET             0x00000000            /*      Reset Value for PGA_CTRL0  */
#define REG_AFE0_PGA_CTRL0                   0xF0012008            /*  AFE0 PGA Control 0 */
#define REG_AFE0_PKDET1_CTRL_RESET           0x00000036            /*      Reset Value for PKDET1_CTRL  */
#define REG_AFE0_PKDET1_CTRL                 0xF0012010            /*  AFE0 PKDET1 Control */
#define REG_AFE0_PKDET2_CTRL_RESET           0x00000036            /*      Reset Value for PKDET2_CTRL  */
#define REG_AFE0_PKDET2_CTRL                 0xF0012014            /*  AFE0 PKDET2 Control */
#define REG_AFE0_ADC_MAIN_CTRL_RESET         0x004428C0            /*      Reset Value for ADC_MAIN_CTRL  */
#define REG_AFE0_ADC_MAIN_CTRL               0xF001201C            /*  AFE0 ADC Main Control */
#define REG_AFE0_AFE_CTRL_RESET              0x00001900            /*      Reset Value for AFE_CTRL  */
#define REG_AFE0_AFE_CTRL                    0xF0012048            /*  AFE0 AFE Control */
#define REG_AFE0_AFE_FILT_GAIN_RESET         0x00004000            /*      Reset Value for AFE_FILT_GAIN  */
#define REG_AFE0_AFE_FILT_GAIN               0xF0012060            /*  AFE0 AFE Filter Gain */
#define REG_AFE0_PKDET_OUT_RESET             0x00000000            /*      Reset Value for PKDET_OUT  */
#define REG_AFE0_PKDET_OUT                   0xF0012080            /*  AFE0 PKDET Out Control */
#define REG_AFE0_FLT_SAFE_LIMIT_RESET        0x7FFF8000            /*      Reset Value for FLT_SAFE_LIMIT  */
#define REG_AFE0_FLT_SAFE_LIMIT              0xF0012084            /*  AFE0 Filter Safe Limit Threshold */
#define REG_AFE0_FLT_STATUS_RESET            0x00000000            /*      Reset Value for FLT_STATUS  */
#define REG_AFE0_FLT_STATUS                  0xF0012088            /*  AFE0 Filter Overflow/underflow Status */

/* ============================================================================================================================
        AFE1
   ============================================================================================================================ */
#define REG_AFE1_HPF_CTRL0_RESET             0x00001018            /*      Reset Value for HPF_CTRL0  */
#define REG_AFE1_HPF_CTRL0                   0xF0013000            /*  AFE1 HPF Control 0 */
#define REG_AFE1_PGA_CTRL0_RESET             0x00000000            /*      Reset Value for PGA_CTRL0  */
#define REG_AFE1_PGA_CTRL0                   0xF0013008            /*  AFE1 PGA Control 0 */
#define REG_AFE1_PKDET1_CTRL_RESET           0x00000036            /*      Reset Value for PKDET1_CTRL  */
#define REG_AFE1_PKDET1_CTRL                 0xF0013010            /*  AFE1 PKDET1 Control */
#define REG_AFE1_PKDET2_CTRL_RESET           0x00000036            /*      Reset Value for PKDET2_CTRL  */
#define REG_AFE1_PKDET2_CTRL                 0xF0013014            /*  AFE1 PKDET2 Control */
#define REG_AFE1_ADC_MAIN_CTRL_RESET         0x004428C0            /*      Reset Value for ADC_MAIN_CTRL  */
#define REG_AFE1_ADC_MAIN_CTRL               0xF001301C            /*  AFE1 ADC Main Control */
#define REG_AFE1_AFE_CTRL_RESET              0x00001900            /*      Reset Value for AFE_CTRL  */
#define REG_AFE1_AFE_CTRL                    0xF0013048            /*  AFE1 AFE Control */
#define REG_AFE1_AFE_FILT_GAIN_RESET         0x00004000            /*      Reset Value for AFE_FILT_GAIN  */
#define REG_AFE1_AFE_FILT_GAIN               0xF0013060            /*  AFE1 AFE Filter Gain */
#define REG_AFE1_PKDET_OUT_RESET             0x00000000            /*      Reset Value for PKDET_OUT  */
#define REG_AFE1_PKDET_OUT                   0xF0013080            /*  AFE1 PKDET Out Control */
#define REG_AFE1_FLT_SAFE_LIMIT_RESET        0x7FFF8000            /*      Reset Value for FLT_SAFE_LIMIT  */
#define REG_AFE1_FLT_SAFE_LIMIT              0xF0013084            /*  AFE1 Filter Safe Limit Threshold */
#define REG_AFE1_FLT_STATUS_RESET            0x00000000            /*      Reset Value for FLT_STATUS  */
#define REG_AFE1_FLT_STATUS                  0xF0013088            /*  AFE1 Filter Overflow/underflow Status */

/* ============================================================================================================================
        AFE2
   ============================================================================================================================ */
#define REG_AFE2_HPF_CTRL0_RESET             0x00001018            /*      Reset Value for HPF_CTRL0  */
#define REG_AFE2_HPF_CTRL0                   0xF0014000            /*  AFE2 HPF Control 0 */
#define REG_AFE2_PGA_CTRL0_RESET             0x00000000            /*      Reset Value for PGA_CTRL0  */
#define REG_AFE2_PGA_CTRL0                   0xF0014008            /*  AFE2 PGA Control 0 */
#define REG_AFE2_PKDET1_CTRL_RESET           0x00000036            /*      Reset Value for PKDET1_CTRL  */
#define REG_AFE2_PKDET1_CTRL                 0xF0014010            /*  AFE2 PKDET1 Control */
#define REG_AFE2_PKDET2_CTRL_RESET           0x00000036            /*      Reset Value for PKDET2_CTRL  */
#define REG_AFE2_PKDET2_CTRL                 0xF0014014            /*  AFE2 PKDET2 Control */
#define REG_AFE2_ADC_MAIN_CTRL_RESET         0x004428C0            /*      Reset Value for ADC_MAIN_CTRL  */
#define REG_AFE2_ADC_MAIN_CTRL               0xF001401C            /*  AFE2 ADC Main Control */
#define REG_AFE2_AFE_CTRL_RESET              0x00001900            /*      Reset Value for AFE_CTRL  */
#define REG_AFE2_AFE_CTRL                    0xF0014048            /*  AFE2 AFE Control */
#define REG_AFE2_AFE_FILT_GAIN_RESET         0x00004000            /*      Reset Value for AFE_FILT_GAIN  */
#define REG_AFE2_AFE_FILT_GAIN               0xF0014060            /*  AFE2 AFE Filter Gain */
#define REG_AFE2_PKDET_OUT_RESET             0x00000000            /*      Reset Value for PKDET_OUT  */
#define REG_AFE2_PKDET_OUT                   0xF0014080            /*  AFE2 PKDET Out Control */
#define REG_AFE2_FLT_SAFE_LIMIT_RESET        0x7FFF8000            /*      Reset Value for FLT_SAFE_LIMIT  */
#define REG_AFE2_FLT_SAFE_LIMIT              0xF0014084            /*  AFE2 Filter Safe Limit Threshold */
#define REG_AFE2_FLT_STATUS_RESET            0x00000000            /*      Reset Value for FLT_STATUS  */
#define REG_AFE2_FLT_STATUS                  0xF0014088            /*  AFE2 Filter Overflow/underflow Status */

/* ============================================================================================================================
        AFE3
   ============================================================================================================================ */
#define REG_AFE3_HPF_CTRL0_RESET             0x00001018            /*      Reset Value for HPF_CTRL0  */
#define REG_AFE3_HPF_CTRL0                   0xF0015000            /*  AFE3 HPF Control 0 */
#define REG_AFE3_PGA_CTRL0_RESET             0x00000000            /*      Reset Value for PGA_CTRL0  */
#define REG_AFE3_PGA_CTRL0                   0xF0015008            /*  AFE3 PGA Control 0 */
#define REG_AFE3_PKDET1_CTRL_RESET           0x00000036            /*      Reset Value for PKDET1_CTRL  */
#define REG_AFE3_PKDET1_CTRL                 0xF0015010            /*  AFE3 PKDET1 Control */
#define REG_AFE3_PKDET2_CTRL_RESET           0x00000036            /*      Reset Value for PKDET2_CTRL  */
#define REG_AFE3_PKDET2_CTRL                 0xF0015014            /*  AFE3 PKDET2 Control */
#define REG_AFE3_ADC_MAIN_CTRL_RESET         0x004428C0            /*      Reset Value for ADC_MAIN_CTRL  */
#define REG_AFE3_ADC_MAIN_CTRL               0xF001501C            /*  AFE3 ADC Main Control */
#define REG_AFE3_AFE_CTRL_RESET              0x00001900            /*      Reset Value for AFE_CTRL  */
#define REG_AFE3_AFE_CTRL                    0xF0015048            /*  AFE3 AFE Control */
#define REG_AFE3_AFE_FILT_GAIN_RESET         0x00004000            /*      Reset Value for AFE_FILT_GAIN  */
#define REG_AFE3_AFE_FILT_GAIN               0xF0015060            /*  AFE3 AFE Filter Gain */
#define REG_AFE3_PKDET_OUT_RESET             0x00000000            /*      Reset Value for PKDET_OUT  */
#define REG_AFE3_PKDET_OUT                   0xF0015080            /*  AFE3 PKDET Out Control */
#define REG_AFE3_FLT_SAFE_LIMIT_RESET        0x7FFF8000            /*      Reset Value for FLT_SAFE_LIMIT  */
#define REG_AFE3_FLT_SAFE_LIMIT              0xF0015084            /*  AFE3 Filter Safe Limit Threshold */
#define REG_AFE3_FLT_STATUS_RESET            0x00000000            /*      Reset Value for FLT_STATUS  */
#define REG_AFE3_FLT_STATUS                  0xF0015088            /*  AFE3 Filter Overflow/underflow Status */

/* ============================================================================================================================
        AFE Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          AFE_HPF_CTRL0                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_HPF_CTRL0_HPF_BYPASS         6            /*  Hpf_bypass_enable */
#define BITP_AFE_HPF_CTRL0_HPF_FC             3            /*  HPF_corner_frequency */
#define BITP_AFE_HPF_CTRL0_HPF_GAIN           1            /*  Hpf_gain */
#define BITP_AFE_HPF_CTRL0_HPF_PUP            0            /*  Hpf_power_up */
#define BITM_AFE_HPF_CTRL0_HPF_BYPASS        0x00000040    /*  Hpf_bypass_enable */
#define BITM_AFE_HPF_CTRL0_HPF_FC            0x00000038    /*  HPF_corner_frequency */
#define BITM_AFE_HPF_CTRL0_HPF_GAIN          0x00000006    /*  Hpf_gain */
#define BITM_AFE_HPF_CTRL0_HPF_PUP           0x00000001    /*  Hpf_power_up */
#define ENUM_AFE_HPF_CTRL0_HPF_BYPASS_EN000  0x00000000            /*  hpf_bypass: HPF in normal operation */
#define ENUM_AFE_HPF_CTRL0_HPF_BYPASS_EN001  0x00000040            /*  hpf_bypass: HPF in by-pass (needed to set pga_mux accordingly) */
#define ENUM_AFE_HPF_CTRL0_HPF_FC_EN000      0x00000000            /*  hpf_fc: 125KHz fcorner */
#define ENUM_AFE_HPF_CTRL0_HPF_FC_EN001      0x00000008            /*  hpf_fc: 250KHz fcorner */
#define ENUM_AFE_HPF_CTRL0_HPF_FC_EN002      0x00000010            /*  hpf_fc: 500KHz fcorner */
#define ENUM_AFE_HPF_CTRL0_HPF_FC_EN003      0x00000018            /*  hpf_fc: 1MHz fcorner */
#define ENUM_AFE_HPF_CTRL0_HPF_FC_EN004      0x00000020            /*  hpf_fc: 2MHz fcorner */
#define ENUM_AFE_HPF_CTRL0_HPF_FC_EN005      0x00000028            /*  hpf_fc: 4MHz fcorner */
#define ENUM_AFE_HPF_CTRL0_HPF_FC_EN006      0x00000030            /*  hpf_fc: 8MHz fcorner */
#define ENUM_AFE_HPF_CTRL0_HPF_FC_EN007      0x00000038            /*  hpf_fc: 16MHz fcorner */
#define ENUM_AFE_HPF_CTRL0_HPF_GAIN_EN000    0x00000000            /*  hpf_gain: 6dB gain */
#define ENUM_AFE_HPF_CTRL0_HPF_GAIN_EN001    0x00000002            /*  hpf_gain: 12dB gain */
#define ENUM_AFE_HPF_CTRL0_HPF_GAIN_EN002    0x00000004            /*  hpf_gain: 18dB gain */
#define ENUM_AFE_HPF_CTRL0_HPF_GAIN_EN003    0x00000006            /*  hpf_gain: 18dB gain */
#define ENUM_AFE_HPF_CTRL0_HPF_PUP_EN000     0x00000000            /*  hpf_pup: HPF in Power Down mode (OFF) */
#define ENUM_AFE_HPF_CTRL0_HPF_PUP_EN001     0x00000001            /*  hpf_pup: HPF in Power Up mode (ON) */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_PGA_CTRL0                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_PGA_CTRL0_PGA_GAIN           6            /*  Pga_gain */
#define BITP_AFE_PGA_CTRL0_PGA_MUX            4            /*  Pga_mux */
#define BITP_AFE_PGA_CTRL0_PGA_PUP            0            /*  Pga_power_up */
#define BITM_AFE_PGA_CTRL0_PGA_GAIN          0x000001C0    /*  Pga_gain */
#define BITM_AFE_PGA_CTRL0_PGA_MUX           0x00000030    /*  Pga_mux */
#define BITM_AFE_PGA_CTRL0_PGA_PUP           0x00000001    /*  Pga_power_up */
#define ENUM_AFE_PGA_CTRL0_PGA_GAIN_EN000    0x00000000            /*  pga_gain: 0dB gain */
#define ENUM_AFE_PGA_CTRL0_PGA_GAIN_EN001    0x00000040            /*  pga_gain: 6dB gain */
#define ENUM_AFE_PGA_CTRL0_PGA_GAIN_EN002    0x00000080            /*  pga_gain: 12dB gain */
#define ENUM_AFE_PGA_CTRL0_PGA_GAIN_EN003    0x000000C0            /*  pga_gain: 18dB gain */
#define ENUM_AFE_PGA_CTRL0_PGA_MUX_EN00      0x00000000            /*  pga_mux: Selects_HPF_output_as_PGA_input */
#define ENUM_AFE_PGA_CTRL0_PGA_MUX_EN01      0x00000010            /*  pga_mux: Selects_HPF_input_as_PGA_input */
#define ENUM_AFE_PGA_CTRL0_PGA_MUX_EN02      0x00000020            /*  pga_mux: PGA_inputs_disconnected */
#define ENUM_AFE_PGA_CTRL0_PGA_MUX_EN03      0x00000030            /*  pga_mux: PGA_inputs_disconnected */
#define ENUM_AFE_PGA_CTRL0_PGA_PUP_EN000     0x00000000            /*  pga_pup: PGA in Power Down mode (OFF) */
#define ENUM_AFE_PGA_CTRL0_PGA_PUP_EN001     0x00000001            /*  pga_pup: PGA in Power Up mode (ON) */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_PKDET1_CTRL                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_PKDET1_CTRL_PKDET1_PUP       0            /*  Peak_detector1_power_up */
#define BITM_AFE_PKDET1_CTRL_PKDET1_PUP      0x00000001    /*  Peak_detector1_power_up */
#define ENUM_AFE_PKDET1_CTRL_PKDET1_PUP_EN000 0x00000000            /*  pkdet1_pup: Peak Detector 1 in Power Down mode (OFF) */
#define ENUM_AFE_PKDET1_CTRL_PKDET1_PUP_EN001 0x00000001            /*  pkdet1_pup: Peak Detector 1 in Power Up mode (ON) */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_PKDET2_CTRL                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_PKDET2_CTRL_PKDET2_PUP       0            /*  Peak_detector2_power_up */
#define BITM_AFE_PKDET2_CTRL_PKDET2_PUP      0x00000001    /*  Peak_detector2_power_up */
#define ENUM_AFE_PKDET2_CTRL_PKDET2_PUP_EN000 0x00000000            /*  pkdet2_pup: Peak Detector 2 in Power Down mode (OFF) */
#define ENUM_AFE_PKDET2_CTRL_PKDET2_PUP_EN001 0x00000001            /*  pkdet2_pup: Peak Detector 2 in Power Up mode (ON) */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_ADC_MAIN_CTRL                    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_ADC_MAIN_CTRL_ADC_IN_SEL     4            /*  ADC Input Selection */
#define BITP_AFE_ADC_MAIN_CTRL_ADC_GAIN       2            /*  ADC Gain */
#define BITP_AFE_ADC_MAIN_CTRL_ADC_RESETB     1            /*  Force Adc_resetb, Need to Enable Adc_dig_ctrl[0] First */
#define BITP_AFE_ADC_MAIN_CTRL_ADC_PDNB       0            /*  ADC Power Down Bar */
#define BITM_AFE_ADC_MAIN_CTRL_ADC_IN_SEL    0x00000030    /*  ADC Input Selection */
#define BITM_AFE_ADC_MAIN_CTRL_ADC_GAIN      0x0000000C    /*  ADC Gain */
#define BITM_AFE_ADC_MAIN_CTRL_ADC_RESETB    0x00000002    /*  Force Adc_resetb, Need to Enable Adc_dig_ctrl[0] First */
#define BITM_AFE_ADC_MAIN_CTRL_ADC_PDNB      0x00000001    /*  ADC Power Down Bar */
#define ENUM_AFE_ADC_MAIN_CTRL_ADC_IN_SEL_EN0 0x00000000            /*  adc_in_sel: Main input resistor connected */
#define ENUM_AFE_ADC_MAIN_CTRL_ADC_IN_SEL_EN1 0x00000010            /*  adc_in_sel: Test in (Aux 1) resistor connected */
#define ENUM_AFE_ADC_MAIN_CTRL_ADC_IN_SEL_EN2 0x00000020            /*  adc_in_sel: Siggen (Aux 2) resistor connected */
#define ENUM_AFE_ADC_MAIN_CTRL_ADC_IN_SEL_EN3 0x00000030            /*  adc_in_sel: Input Disconnected */
#define ENUM_AFE_ADC_MAIN_CTRL_ADC_GAIN_EN0  0x00000000            /*  adc_gain: Gain = 0dB */
#define ENUM_AFE_ADC_MAIN_CTRL_ADC_GAIN_EN1  0x00000004            /*  adc_gain: Gain = -3dB */
#define ENUM_AFE_ADC_MAIN_CTRL_ADC_GAIN_EN2  0x00000008            /*  adc_gain: Gain = 3dB */
#define ENUM_AFE_ADC_MAIN_CTRL_ADC_GAIN_EN3  0x0000000C            /*  adc_gain: Gain = -3dB */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_AFE_CTRL                         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_AFE_CTRL_FILTER_DISABLE     23            /*  Decimation_filter_disable */
#define BITM_AFE_AFE_CTRL_FILTER_DISABLE     0x00800000    /*  Decimation_filter_disable */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_AFE_FILT_GAIN                    Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_AFE_FILT_GAIN_FILTER_GAIN    0            /*  Programmable Gain For Decimation Filter in signed 2.14 format. Gain in dB is 20*log(Gain Value/2^14) */
#define BITM_AFE_AFE_FILT_GAIN_FILTER_GAIN   0x0000FFFF    /*  Programmable Gain For Decimation Filter in signed 2.14 format. Gain in dB is 20*log(Gain Value/2^14) */
#define ENUM_AFE_AFE_FILT_GAIN_GAIN2         0x00002013            /*  filter_gain: Provides -6dB gain */
#define ENUM_AFE_AFE_FILT_GAIN_GAIN3         0x00004000            /*  filter_gain: Provides 0dB gain */
#define ENUM_AFE_AFE_FILT_GAIN_GAIN1         0x00007FB2            /*  filter_gain: Provides 6dB gain */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_PKDET_OUT                        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_PKDET_OUT_ADC_OVERLOAD_FLAG 12            /*  ADC Overload Flag */
#define BITP_AFE_PKDET_OUT_ADC_PKDET_INT3_FLAG_STR  9            /*  ADC Peak Detect Integrator 3 Flag */
#define BITP_AFE_PKDET_OUT_ADC_PKDET_INT2_FLAG_STR  7            /*  ADC Peak Detect Integrator 2 Flag */
#define BITP_AFE_PKDET_OUT_ADC_PKDET_INT1_FLAG_STR  5            /*  ADC Peak Detect Integrator 1 Flag */
#define BITP_AFE_PKDET_OUT_PKDET2_OUT_STR     3            /*  Peak_detector2_strobed_with_adcclk_div8 */
#define BITP_AFE_PKDET_OUT_PKDET1_OUT_STR     1            /*  Peak_detector1_strobed_with_adcclk_div8 */
#define BITM_AFE_PKDET_OUT_ADC_OVERLOAD_FLAG 0x00001000    /*  ADC Overload Flag */
#define BITM_AFE_PKDET_OUT_ADC_PKDET_INT3_FLAG_STR 0x00000200    /*  ADC Peak Detect Integrator 3 Flag */
#define BITM_AFE_PKDET_OUT_ADC_PKDET_INT2_FLAG_STR 0x00000080    /*  ADC Peak Detect Integrator 2 Flag */
#define BITM_AFE_PKDET_OUT_ADC_PKDET_INT1_FLAG_STR 0x00000020    /*  ADC Peak Detect Integrator 1 Flag */
#define BITM_AFE_PKDET_OUT_PKDET2_OUT_STR    0x00000008    /*  Peak_detector2_strobed_with_adcclk_div8 */
#define BITM_AFE_PKDET_OUT_PKDET1_OUT_STR    0x00000002    /*  Peak_detector1_strobed_with_adcclk_div8 */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_FLT_SAFE_LIMIT                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_FLT_SAFE_LIMIT_FILTER_SAFE_ULIMIT 16            /*  Filter Data Safe Upper Limit */
#define BITP_AFE_FLT_SAFE_LIMIT_FILTER_SAFE_LLIMIT  0            /*  Filter Data Safe Lower Limit */
#define BITM_AFE_FLT_SAFE_LIMIT_FILTER_SAFE_ULIMIT 0xFFFF0000    /*  Filter Data Safe Upper Limit */
#define BITM_AFE_FLT_SAFE_LIMIT_FILTER_SAFE_LLIMIT 0x0000FFFF    /*  Filter Data Safe Lower Limit */

/* -------------------------------------------------------------------------------------------------------------------------
          AFE_FLT_STATUS                       Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_AFE_FLT_STATUS_FILTER_CIC_UNDERFLOW  7            /*  Underflow Detect at CIC Output */
#define BITP_AFE_FLT_STATUS_FILTER_CIC_OVERFLOW  6            /*  Overflow Detect at CIC Output */
#define BITP_AFE_FLT_STATUS_FILTER_GAIN_UNDERFLOW  5            /*  Underflow Detect During Gain Scaling */
#define BITP_AFE_FLT_STATUS_FILTER_GAIN_OVERFLOW  4            /*  Overflow Detect During Gain Scaling */
#define BITP_AFE_FLT_STATUS_FILTER_WINDTRUNC_UNDERFLOW  3            /*  Underflow Detect During Windowed Truncation */
#define BITP_AFE_FLT_STATUS_FILTER_WINDTRUNC_OVERFLOW  2            /*  Overflow Detect During Windowed Truncation */
#define BITP_AFE_FLT_STATUS_VAL_LESSTHAN_SAFE_LLIM  1            /*  Filter Data Less Than Safe Lower Limit */
#define BITP_AFE_FLT_STATUS_VAL_MORETHAN_SAFE_ULIM  0            /*  Filter Data More Than Safe Upper Limit */
#define BITM_AFE_FLT_STATUS_FILTER_CIC_UNDERFLOW 0x00000080    /*  Underflow Detect at CIC Output */
#define BITM_AFE_FLT_STATUS_FILTER_CIC_OVERFLOW 0x00000040    /*  Overflow Detect at CIC Output */
#define BITM_AFE_FLT_STATUS_FILTER_GAIN_UNDERFLOW 0x00000020    /*  Underflow Detect During Gain Scaling */
#define BITM_AFE_FLT_STATUS_FILTER_GAIN_OVERFLOW 0x00000010    /*  Overflow Detect During Gain Scaling */
#define BITM_AFE_FLT_STATUS_FILTER_WINDTRUNC_UNDERFLOW 0x00000008    /*  Underflow Detect During Windowed Truncation */
#define BITM_AFE_FLT_STATUS_FILTER_WINDTRUNC_OVERFLOW 0x00000004    /*  Overflow Detect During Windowed Truncation */
#define BITM_AFE_FLT_STATUS_VAL_LESSTHAN_SAFE_LLIM 0x00000002    /*  Filter Data Less Than Safe Lower Limit */
#define BITM_AFE_FLT_STATUS_VAL_MORETHAN_SAFE_ULIM 0x00000001    /*  Filter Data More Than Safe Upper Limit */


/* ============================================================================================================================
        Digimmic System Control Register Map
   ============================================================================================================================ */

/* ============================================================================================================================
        misc
   ============================================================================================================================ */
#define REG_MISC_MISC_SPI_CRC_0_RESET        0x555590D9            /*      Reset Value for misc_spi_crc_0  */
#define REG_MISC_MISC_SPI_CRC_0              0xF0017000            /*  misc Register Containing the Crc Polynomial and Crc Seed for Spi */
#define REG_MISC_MISC_CLK_CTRL_RESET         0x00000000            /*      Reset Value for misc_clk_ctrl  */
#define REG_MISC_MISC_CLK_CTRL               0xF0017018            /*  misc Clock Control Register */
#define REG_MISC_MISC_SCRATCHPAD_0_RESET     0x00000000            /*      Reset Value for misc_scratchpad_0  */
#define REG_MISC_MISC_SCRATCHPAD_0           0xF0017020            /*  misc Scratchpad Register 0 */
#define REG_MISC_MISC_SCRATCHPAD_1_RESET     0x00000000            /*      Reset Value for misc_scratchpad_1  */
#define REG_MISC_MISC_SCRATCHPAD_1           0xF0017024            /*  misc Scratchpad Register 1 */
#define REG_MISC_MISC_FILTER_CTRL_RESET      0x00000218            /*      Reset Value for misc_filter_ctrl  */
#define REG_MISC_MISC_FILTER_CTRL            0xF0017034            /*  misc Filter Control Register */
#define REG_MISC_MISC_UDMA_REQ_MUX_SEL_0_RESET 0x00000000            /*      Reset Value for misc_udma_req_mux_sel_0  */
#define REG_MISC_MISC_UDMA_REQ_MUX_SEL_0     0xF0017038            /*  misc Udma Peripheral Request Mux Select for Channels 0 to 7 */
#define REG_MISC_MISC_UDMA_REQ_MUX_SEL_1_RESET 0x00000000            /*      Reset Value for misc_udma_req_mux_sel_1  */
#define REG_MISC_MISC_UDMA_REQ_MUX_SEL_1     0xF001703C            /*  misc Udma Peripheral Request Mux Select for Channels 8 to 15 */
#define REG_MISC_MISC_PWRDN_RESET            0x00000000            /*      Reset Value for misc_pwrdn  */
#define REG_MISC_MISC_PWRDN                  0xF001705C            /*  misc Power Down and Clock Gate Control Register */
#define REG_MISC_MISC_HW_ENGINE_CTRL_RESET   0x00000000            /*      Reset Value for misc_hw_engine_ctrl  */
#define REG_MISC_MISC_HW_ENGINE_CTRL         0xF0017070            /*  misc Control for Fft Hardware Engine */
#define REG_MISC_MISC_FILTER_CTRL_1_RESET    0x0008002E            /*      Reset Value for misc_filter_ctrl_1  */
#define REG_MISC_MISC_FILTER_CTRL_1          0xF0017074            /*  misc Decimation Filter Control Register 1 */
#define REG_MISC_MISC_SPI_CRC_1_RESET        0x00000000            /*      Reset Value for misc_spi_crc_1  */
#define REG_MISC_MISC_SPI_CRC_1              0xF0017080            /*  misc Register Containing the 16-Bit Crc Checksum from Spi */
#define REG_MISC_MISC_BOOT_STATUS_RESET      0x00000000            /*      Reset Value for misc_boot_status  */
#define REG_MISC_MISC_BOOT_STATUS            0xF0017084            /*  misc Boot Status Register */
#define REG_MISC_MISC_LINE_SHIFT_ERROR_RESET 0x00000000            /*      Reset Value for misc_line_shift_error  */
#define REG_MISC_MISC_LINE_SHIFT_ERROR       0xF0017088            /*  misc Filter Diag Shift Error Register */
#define REG_MISC_MISC_DEVICE_ENUM_ID_RESET   0x00000000            /*      Reset Value for misc_device_enum_id  */
#define REG_MISC_MISC_DEVICE_ENUM_ID         0xF001708C            /*  misc Indicates Digimmic Enumeration Id */
#define REG_MISC_MISC_CHIP_MODE_RESET        0x00000010            /*      Reset Value for misc_chip_mode  */
#define REG_MISC_MISC_CHIP_MODE              0xF0017098            /*  misc Chip Mode Register */
#define REG_MISC_MISC_SPI_DEVICE_REV_RESET   0x00000002            /*      Reset Value for misc_spi_device_rev  */
#define REG_MISC_MISC_SPI_DEVICE_REV         0xF00170A0            /*  misc Spi Revid Register */
#define REG_MISC_MISC_PART_MANUFACTURE_ID_RESET 0x0281E0CB            /*      Reset Value for misc_part_manufacture_id  */
#define REG_MISC_MISC_PART_MANUFACTURE_ID    0xF00170A4            /*  misc Part Manufacture Id Register */

/* ============================================================================================================================
        misc Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_SPI_CRC_0                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_SPI_CRC_0_SPI_CRC_SEED 16            /*  Programmable SPI CRC Seed */
#define BITP_MISC_MISC_SPI_CRC_0_SPI_CRC_POLY  0            /*  Programmable CRC Polynomial */
#define BITM_MISC_MISC_SPI_CRC_0_SPI_CRC_SEED 0xFFFF0000    /*  Programmable SPI CRC Seed */
#define BITM_MISC_MISC_SPI_CRC_0_SPI_CRC_POLY 0x0000FFFF    /*  Programmable CRC Polynomial */

/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_CLK_CTRL                   Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_CLK_CTRL_MIPI_PLL_DIV_SEL 21            /*  Selects by 2 or by 4 Divided Clock */
#define BITP_MISC_MISC_CLK_CTRL_LVDS_CLK_SEL  3            /*  Lvds Clock Select */
#define BITP_MISC_MISC_CLK_CTRL_OTP_CLK_SEL   0            /*  Selects the Clock for Otp */
#define BITM_MISC_MISC_CLK_CTRL_MIPI_PLL_DIV_SEL 0x00200000    /*  Selects by 2 or by 4 Divided Clock */
#define BITM_MISC_MISC_CLK_CTRL_LVDS_CLK_SEL 0x000001F8    /*  Lvds Clock Select */
#define BITM_MISC_MISC_CLK_CTRL_OTP_CLK_SEL  0x00000003    /*  Selects the Clock for Otp */
#define ENUM_MISC_MISC_CLK_CTRL_REFCLK_BY2   0x00000000            /*  mipi_pll_div_sel: Selects REFCLK/2 as MIPI Config Clock */
#define ENUM_MISC_MISC_CLK_CTRL_REFCLK_BY4   0x00200000            /*  mipi_pll_div_sel: Selects REFCLK/4 as MIPI Config Clock */
#define ENUM_MISC_MISC_CLK_CTRL_ADCCLK_BY_6  0x00000008            /*  lvds_clk_sel: Selects ADCCLK/6 as LVDS clock */
#define ENUM_MISC_MISC_CLK_CTRL_ADCCLK_BY_1P5 0x00000010            /*  lvds_clk_sel: Selects ADCCLK/1.5 as LVDS clock */
#define ENUM_MISC_MISC_CLK_CTRL_ADCCLK_BY_2  0x00000020            /*  lvds_clk_sel: Selects ADCCLK/2 as LVDS clock */
#define ENUM_MISC_MISC_CLK_CTRL_ADCCLK_BY_3  0x00000040            /*  lvds_clk_sel: Selects ADCCLK/3 as LVDS clock */
#define ENUM_MISC_MISC_CLK_CTRL_ADCCLK_BY_4  0x00000080            /*  lvds_clk_sel: Selects ADCCLK/4 as LVDS clock */
#define ENUM_MISC_MISC_CLK_CTRL_ADCCLK_BY_8  0x00000100            /*  lvds_clk_sel: Selects ADCCLK/8 as LVDS clock */
#define ENUM_MISC_MISC_CLK_CTRL_HCLK_BY_4    0x00000000            /*  otp_clk_sel: hclk divided by 4 */
#define ENUM_MISC_MISC_CLK_CTRL_HCLK_BY_2    0x00000001            /*  otp_clk_sel: hclk divided by 2 */
#define ENUM_MISC_MISC_CLK_CTRL_HCLK_BY_1    0x00000002            /*  otp_clk_sel: hclk divided by 1 */

/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_SCRATCHPAD_0               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_SCRATCHPAD_0_SCRATCHPAD_0  0            /*  Software Scratch Pad Register */
#define BITM_MISC_MISC_SCRATCHPAD_0_SCRATCHPAD_0 0xFFFFFFFF    /*  Software Scratch Pad Register */

/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_SCRATCHPAD_1               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_SCRATCHPAD_1_SCRATCHPAD_1  0            /*  Software Scratch Pad Register */
#define BITM_MISC_MISC_SCRATCHPAD_1_SCRATCHPAD_1 0xFFFFFFFF    /*  Software Scratch Pad Register */

/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_FILTER_CTRL                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_FILTER_CTRL_FILTER_WINDOW_SELECT 12            /*  Selecting Filter Window */
#define BITP_MISC_MISC_FILTER_CTRL_FULLSCALE_CODE_EN  9            /*  Enable Filter Full Scale */
#define BITM_MISC_MISC_FILTER_CTRL_FILTER_WINDOW_SELECT 0x00007000    /*  Selecting Filter Window */
#define BITM_MISC_MISC_FILTER_CTRL_FULLSCALE_CODE_EN 0x00000200    /*  Enable Filter Full Scale */
#define ENUM_MISC_MISC_FILTER_CTRL_WINDOW_FROM_15TH_BIT 0x00000000            /*  filter_window_select: Window_From_15Th_Bit */
#define ENUM_MISC_MISC_FILTER_CTRL_WINDOW_FROM_14TH_BIT 0x00001000            /*  filter_window_select: Window_From_14Th_Bit */
#define ENUM_MISC_MISC_FILTER_CTRL_WINDOW_FROM_13TH_BIT 0x00002000            /*  filter_window_select: Window_From_13Th_Bit */
#define ENUM_MISC_MISC_FILTER_CTRL_WINDOW_FROM_12TH_BIT 0x00003000            /*  filter_window_select: Window_From_12Th_Bit */
#define ENUM_MISC_MISC_FILTER_CTRL_WINDOW_FROM_11TH_BIT 0x00004000            /*  filter_window_select: Window_From_11Th_Bit */

/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_UDMA_REQ_MUX_SEL_0         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_UDMA_REQ_MUX_SEL_0_UDMA_REQ_MUXSEL_CHAN7 28            /*  Udma Request Select Mux for Channel 7 */
#define BITP_MISC_MISC_UDMA_REQ_MUX_SEL_0_UDMA_REQ_MUXSEL_CHAN6 24            /*  Udma Request Select Mux for Channel 6 */
#define BITP_MISC_MISC_UDMA_REQ_MUX_SEL_0_UDMA_REQ_MUXSEL_CHAN5 20            /*  Udma Request Select Mux for Channel 5 */
#define BITP_MISC_MISC_UDMA_REQ_MUX_SEL_0_UDMA_REQ_MUXSEL_CHAN4 16            /*  Udma Request Select Mux for Channel 4 */
#define BITP_MISC_MISC_UDMA_REQ_MUX_SEL_0_UDMA_REQ_MUXSEL_CHAN3 12            /*  Udma Request Select Mux for Channel 3 */
#define BITP_MISC_MISC_UDMA_REQ_MUX_SEL_0_UDMA_REQ_MUXSEL_CHAN2  8            /*  Udma Request Select Mux for Channel 2 */
#define BITP_MISC_MISC_UDMA_REQ_MUX_SEL_0_UDMA_REQ_MUXSEL_CHAN1  4            /*  Udma Request Select Mux for Channel 1 */
#define BITP_MISC_MISC_UDMA_REQ_MUX_SEL_0_UDMA_REQ_MUXSEL_CHAN0  0            /*  Udma Request Select Mux for Channel 0 */
#define BITM_MISC_MISC_UDMA_REQ_MUX_SEL_0_UDMA_REQ_MUXSEL_CHAN7 0xF0000000    /*  Udma Request Select Mux for Channel 7 */
#define BITM_MISC_MISC_UDMA_REQ_MUX_SEL_0_UDMA_REQ_MUXSEL_CHAN6 0x0F000000    /*  Udma Request Select Mux for Channel 6 */
#define BITM_MISC_MISC_UDMA_REQ_MUX_SEL_0_UDMA_REQ_MUXSEL_CHAN5 0x00F00000    /*  Udma Request Select Mux for Channel 5 */
#define BITM_MISC_MISC_UDMA_REQ_MUX_SEL_0_UDMA_REQ_MUXSEL_CHAN4 0x000F0000    /*  Udma Request Select Mux for Channel 4 */
#define BITM_MISC_MISC_UDMA_REQ_MUX_SEL_0_UDMA_REQ_MUXSEL_CHAN3 0x0000F000    /*  Udma Request Select Mux for Channel 3 */
#define BITM_MISC_MISC_UDMA_REQ_MUX_SEL_0_UDMA_REQ_MUXSEL_CHAN2 0x00000F00    /*  Udma Request Select Mux for Channel 2 */
#define BITM_MISC_MISC_UDMA_REQ_MUX_SEL_0_UDMA_REQ_MUXSEL_CHAN1 0x000000F0    /*  Udma Request Select Mux for Channel 1 */
#define BITM_MISC_MISC_UDMA_REQ_MUX_SEL_0_UDMA_REQ_MUXSEL_CHAN0 0x0000000F    /*  Udma Request Select Mux for Channel 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_UDMA_REQ_MUX_SEL_1         Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_UDMA_REQ_MUX_SEL_1_UDMA_REQ_MUXSEL_CHAN15 28            /*  Udma Request Select Mux for Channel 15 */
#define BITP_MISC_MISC_UDMA_REQ_MUX_SEL_1_UDMA_REQ_MUXSEL_CHAN14 24            /*  Udma Request Select Mux for Channel 14 */
#define BITP_MISC_MISC_UDMA_REQ_MUX_SEL_1_UDMA_REQ_MUXSEL_CHAN13 20            /*  Udma Request Select Mux for Channel 13 */
#define BITP_MISC_MISC_UDMA_REQ_MUX_SEL_1_UDMA_REQ_MUXSEL_CHAN12 16            /*  Udma Request Select Mux for Channel 12 */
#define BITP_MISC_MISC_UDMA_REQ_MUX_SEL_1_UDMA_REQ_MUXSEL_CHAN11 12            /*  Udma Request Select Mux for Channel 11 */
#define BITP_MISC_MISC_UDMA_REQ_MUX_SEL_1_UDMA_REQ_MUXSEL_CHAN10  8            /*  Udma Request Select Mux for Channel 10 */
#define BITP_MISC_MISC_UDMA_REQ_MUX_SEL_1_UDMA_REQ_MUXSEL_CHAN9  4            /*  Udma Request Select Mux for Channel 9 */
#define BITP_MISC_MISC_UDMA_REQ_MUX_SEL_1_UDMA_REQ_MUXSEL_CHAN8  0            /*  Udma Request Select Mux for Channel 8 */
#define BITM_MISC_MISC_UDMA_REQ_MUX_SEL_1_UDMA_REQ_MUXSEL_CHAN15 0xF0000000    /*  Udma Request Select Mux for Channel 15 */
#define BITM_MISC_MISC_UDMA_REQ_MUX_SEL_1_UDMA_REQ_MUXSEL_CHAN14 0x0F000000    /*  Udma Request Select Mux for Channel 14 */
#define BITM_MISC_MISC_UDMA_REQ_MUX_SEL_1_UDMA_REQ_MUXSEL_CHAN13 0x00F00000    /*  Udma Request Select Mux for Channel 13 */
#define BITM_MISC_MISC_UDMA_REQ_MUX_SEL_1_UDMA_REQ_MUXSEL_CHAN12 0x000F0000    /*  Udma Request Select Mux for Channel 12 */
#define BITM_MISC_MISC_UDMA_REQ_MUX_SEL_1_UDMA_REQ_MUXSEL_CHAN11 0x0000F000    /*  Udma Request Select Mux for Channel 11 */
#define BITM_MISC_MISC_UDMA_REQ_MUX_SEL_1_UDMA_REQ_MUXSEL_CHAN10 0x00000F00    /*  Udma Request Select Mux for Channel 10 */
#define BITM_MISC_MISC_UDMA_REQ_MUX_SEL_1_UDMA_REQ_MUXSEL_CHAN9 0x000000F0    /*  Udma Request Select Mux for Channel 9 */
#define BITM_MISC_MISC_UDMA_REQ_MUX_SEL_1_UDMA_REQ_MUXSEL_CHAN8 0x0000000F    /*  Udma Request Select Mux for Channel 8 */

/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_PWRDN                      Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_PWRDN_AUXADC_CLK_GATE  7            /*  Auxadc Apb Clock Gating */
#define BITP_MISC_MISC_PWRDN_ADCPLL_CLK_GATE  6            /*  Adcpll Apb Clock Gating */
#define BITP_MISC_MISC_PWRDN_RFPLL_CLK_GATE   5            /*  Rfpll Apb Clock Gating */
#define BITP_MISC_MISC_PWRDN_PWRDN            0            /*  Power Down for Adc Clock Receivers */
#define BITM_MISC_MISC_PWRDN_AUXADC_CLK_GATE 0x00000080    /*  Auxadc Apb Clock Gating */
#define BITM_MISC_MISC_PWRDN_ADCPLL_CLK_GATE 0x00000040    /*  Adcpll Apb Clock Gating */
#define BITM_MISC_MISC_PWRDN_RFPLL_CLK_GATE  0x00000020    /*  Rfpll Apb Clock Gating */
#define BITM_MISC_MISC_PWRDN_PWRDN           0x00000003    /*  Power Down for Adc Clock Receivers */

/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_HW_ENGINE_CTRL             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_HW_ENGINE_CTRL_LO_LEFT_LO_RIGHT  5            /*  LO Left/Right */
#define BITM_MISC_MISC_HW_ENGINE_CTRL_LO_LEFT_LO_RIGHT 0x00000020    /*  LO Left/Right */
#define ENUM_MISC_MISC_HW_ENGINE_CTRL_LO_LEFT 0x00000000            /*  lo_left_lo_right: Select Left Lo In */
#define ENUM_MISC_MISC_HW_ENGINE_CTRL_LO_RIGHT 0x00000020            /*  lo_left_lo_right: Select Right Lo In */

/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_FILTER_CTRL_1              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_FILTER_CTRL_1_FILTER_NUMOFPOINTS  9            /*  Number of Decimated Clock Cycles Valid Stays High */
#define BITP_MISC_MISC_FILTER_CTRL_1_FILTER_VALID_DELAY  0            /*  Ramp Valid to Filter Data Valid Delay */
#define BITM_MISC_MISC_FILTER_CTRL_1_FILTER_NUMOFPOINTS 0x003FFE00    /*  Number of Decimated Clock Cycles Valid Stays High */
#define BITM_MISC_MISC_FILTER_CTRL_1_FILTER_VALID_DELAY 0x000001FF    /*  Ramp Valid to Filter Data Valid Delay */

/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_SPI_CRC_1                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_SPI_CRC_1_SPI_CRC_CKSUM  0            /*  Spi Crc Checksum */
#define BITM_MISC_MISC_SPI_CRC_1_SPI_CRC_CKSUM 0x0000FFFF    /*  Spi Crc Checksum */

/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_BOOT_STATUS                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_BOOT_STATUS_IO_LEVEL   8            /*  3P3 or 1P8 Io Level Indicator */
#define BITM_MISC_MISC_BOOT_STATUS_IO_LEVEL  0x00000100    /*  3P3 or 1P8 Io Level Indicator */
#define ENUM_MISC_MISC_BOOT_STATUS_IO_LEVEL_3P3 0x00000000            /*  io_level: 3P3 V Io Level */
#define ENUM_MISC_MISC_BOOT_STATUS_IO_LEVEL_1P8 0x00000100            /*  io_level: 1P8 V Io Level */

/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_LINE_SHIFT_ERROR           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_LINE_SHIFT_ERROR_CLKOUT_SEL 12            /*  Select for Clock Out Mux */
#define BITM_MISC_MISC_LINE_SHIFT_ERROR_CLKOUT_SEL 0x0000F000    /*  Select for Clock Out Mux */
#define ENUM_MISC_MISC_LINE_SHIFT_ERROR_REF_CLK_BY_2 0x00000000            /*  clkout_sel: Ref Clock by 2 */
#define ENUM_MISC_MISC_LINE_SHIFT_ERROR_REF_CLK_BY_4 0x00001000            /*  clkout_sel: Ref Clock by 4 */
#define ENUM_MISC_MISC_LINE_SHIFT_ERROR_REF_CLK 0x00002000            /*  clkout_sel: Ref Clock */
#define ENUM_MISC_MISC_LINE_SHIFT_ERROR_MIPI_BYTE_CLK_BY_32 0x00003000            /*  clkout_sel: MIPI Byte Clock by 32 */
#define ENUM_MISC_MISC_LINE_SHIFT_ERROR_MIPI_BYTE_CLK_BY_64 0x00004000            /*  clkout_sel: MIPI Byte Clock by 64 */
#define ENUM_MISC_MISC_LINE_SHIFT_ERROR_AFE0_ADC_BY_32 0x00005000            /*  clkout_sel: AFE0 ADC by 32 */
#define ENUM_MISC_MISC_LINE_SHIFT_ERROR_AFE1_ADC_BY_32 0x00006000            /*  clkout_sel: AFE1 ADC by 32 */
#define ENUM_MISC_MISC_LINE_SHIFT_ERROR_AFE2_ADC_BY_32 0x00007000            /*  clkout_sel: AFE2 ADC by 32 */
#define ENUM_MISC_MISC_LINE_SHIFT_ERROR_AFE3_ADC_BY_32 0x00008000            /*  clkout_sel: AFE3 ADC by 32 */
#define ENUM_MISC_MISC_LINE_SHIFT_ERROR_ADC_BY_48 0x00009000            /*  clkout_sel: ADC by 48 */
#define ENUM_MISC_MISC_LINE_SHIFT_ERROR_HCLK_BY_16 0x0000A000            /*  clkout_sel: HCLK by 16 */
#define ENUM_MISC_MISC_LINE_SHIFT_ERROR_CLKS_GATED 0x0000F000            /*  clkout_sel: Clocks Gated */

/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_DEVICE_ENUM_ID             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_DEVICE_ENUM_ID_DEVICE_ENUM_ID  0            /*  Indicates Digimmic Enumeration Id */
#define BITM_MISC_MISC_DEVICE_ENUM_ID_DEVICE_ENUM_ID 0x0000003F    /*  Indicates Digimmic Enumeration Id */

/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_CHIP_MODE                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_CHIP_MODE_SPI_RTWO_PUP  2            /*  Rtwo Power up */
#define BITP_MISC_MISC_CHIP_MODE_MSTR_SLV     0            /*  Digimmic Master/Slave */
#define BITM_MISC_MISC_CHIP_MODE_SPI_RTWO_PUP 0x00000004    /*  Rtwo Power up */
#define BITM_MISC_MISC_CHIP_MODE_MSTR_SLV    0x00000001    /*  Digimmic Master/Slave */
#define ENUM_MISC_MISC_CHIP_MODE_MASTER      0x00000000            /*  mstr_slv: sets digiMMIC in master mode */
#define ENUM_MISC_MISC_CHIP_MODE_SLAVE       0x00000001            /*  mstr_slv: sets digiMMIC in slave mode */

/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_SPI_DEVICE_REV             Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_SPI_DEVICE_REV_SPI_DEVICE_REV  0            /*  SPI Device Revision */
#define BITM_MISC_MISC_SPI_DEVICE_REV_SPI_DEVICE_REV 0x000000FF    /*  SPI Device Revision */

/* -------------------------------------------------------------------------------------------------------------------------
          misc_MISC_PART_MANUFACTURE_ID        Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_MISC_MISC_PART_MANUFACTURE_ID_PART_MANUFACTURE_ID  0            /*  Part Number and Manufacture Id */
#define BITM_MISC_MISC_PART_MANUFACTURE_ID_PART_MANUFACTURE_ID 0x0FFFFFFF    /*  Part Number and Manufacture Id */


/* ============================================================================================================================
        
   ============================================================================================================================ */

/* ============================================================================================================================
        RF_ADPLL
   ============================================================================================================================ */
#define REG_RF_ADPLL_RFPLL_RAMP_CONFIG1_RESET 0x00010000            /*      Reset Value for RFPLL_RAMP_CONFIG1  */
#define REG_RF_ADPLL_RFPLL_RAMP_CONFIG1      0xF002005C            /*  RF_ADPLL RAMP_CONFIG1 */
#define REG_RF_ADPLL_RFPLL_RAMP_CONFIG2_RESET 0x00000000            /*      Reset Value for RFPLL_RAMP_CONFIG2  */
#define REG_RF_ADPLL_RFPLL_RAMP_CONFIG2      0xF0020060            /*  RF_ADPLL MIMO_CONFIG */
#define REG_RF_ADPLL_RFPLL_RAMP_CONFIG3_RESET 0x00000000            /*      Reset Value for RFPLL_RAMP_CONFIG3  */
#define REG_RF_ADPLL_RFPLL_RAMP_CONFIG3      0xF0020064            /*  RF_ADPLL PGA_SHUNT_CONFIG */
#define REG_RF_ADPLL_RFPLL_RAMP_CONFIG4_RESET 0x00000000            /*      Reset Value for RFPLL_RAMP_CONFIG4  */
#define REG_RF_ADPLL_RFPLL_RAMP_CONFIG4      0xF0020068            /*  RF_ADPLL RAMP_INIT */
#define REG_RF_ADPLL_RFPLL_RAMP_CONFIG6_RESET 0x00000000            /*      Reset Value for RFPLL_RAMP_CONFIG6  */
#define REG_RF_ADPLL_RFPLL_RAMP_CONFIG6      0xF0020070            /*  RF_ADPLL RAMP_IDLE */
#define REG_RF_ADPLL_RFPLL_RAMP_CONFIG7_RESET 0x00000000            /*      Reset Value for RFPLL_RAMP_CONFIG7  */
#define REG_RF_ADPLL_RFPLL_RAMP_CONFIG7      0xF0020074            /*  RF_ADPLL RAMP_AFE_IDLE */
#define REG_RF_ADPLL_RFPLL_RAMP_CONFIG8_RESET 0x00000000            /*      Reset Value for RFPLL_RAMP_CONFIG8  */
#define REG_RF_ADPLL_RFPLL_RAMP_CONFIG8      0xF0020078            /*  RF_ADPLL STATUS_PINS */

/* ============================================================================================================================
        RF_ADPLL Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          RF_ADPLL_RFPLL_RAMP_CONFIG1          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA2_PHASE_MEM_EN 19            /*  Enable Phase Modulation Using PHASE_RAM Pattern in TX2 */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA1_PHASE_MEM_EN 18            /*  Enable Phase Modulation Using PHASE_RAM Pattern in TX1 */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA0_PHASE_MEM_EN 17            /*  Enable Phase Modulation Using PHASE_RAM Pattern in TX0 */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_MEM_SD 16            /*  SD Pin of PHASE_RAM */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_DELAY_EN 15            /*  Enable Phase Modulation Delay (Start with Data_valid) */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_MOD_EN 14            /*  Enable Phase Modulation During the Ramp Generation */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA_OFF_TIME  9            /*  Duration of the off Time Between PAs Activated and Deactivated */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEP_DIV  3            /*  The Duration of Each Step of the VGA_gain Shape is Tclk*vga_gain_step_div */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEPS  0            /*  The Number of Steps of the VGA_gain Shape is 2^vga_gain_steps */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA2_PHASE_MEM_EN 0x00080000    /*  Enable Phase Modulation Using PHASE_RAM Pattern in TX2 */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA1_PHASE_MEM_EN 0x00040000    /*  Enable Phase Modulation Using PHASE_RAM Pattern in TX1 */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA0_PHASE_MEM_EN 0x00020000    /*  Enable Phase Modulation Using PHASE_RAM Pattern in TX0 */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_MEM_SD 0x00010000    /*  SD Pin of PHASE_RAM */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_DELAY_EN 0x00008000    /*  Enable Phase Modulation Delay (Start with Data_valid) */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_MOD_EN 0x00004000    /*  Enable Phase Modulation During the Ramp Generation */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA_OFF_TIME 0x00003E00    /*  Duration of the off Time Between PAs Activated and Deactivated */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEP_DIV 0x000001F8    /*  The Duration of Each Step of the VGA_gain Shape is Tclk*vga_gain_step_div */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEPS 0x00000007    /*  The Number of Steps of the VGA_gain Shape is 2^vga_gain_steps */

/* -------------------------------------------------------------------------------------------------------------------------
          RF_ADPLL_RFPLL_RAMP_CONFIG2          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_MODE_EN 26            /*  MIMO Mode Enable for Ramp Generation */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ_LEN 24            /*  MIMO Sequence Length */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ 12            /*  MIMO Mode Sequence */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG2_RAMP_COUNT  0            /*  Number of Chirps Generated in Ramp Generation */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_MODE_EN 0x04000000    /*  MIMO Mode Enable for Ramp Generation */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ_LEN 0x03000000    /*  MIMO Sequence Length */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ 0x00FFF000    /*  MIMO Mode Sequence */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_RAMP_COUNT 0x00000FFF    /*  Number of Chirps Generated in Ramp Generation */

/* -------------------------------------------------------------------------------------------------------------------------
          RF_ADPLL_RFPLL_RAMP_CONFIG3          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_RAMP_SYNC_DIS 28            /*  Disable 'ramp_sync' Input. Ramps or ADC Synchronization Won't Start */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_VGA_GAUSS_DIS 27            /*  Disable VGA Gain Gaussian Shape */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_ADC_SYNC_DEL 23            /*  Select the Delay of the 'adc_sync' Signal Across the Devices */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_RAMP_SYNC_DEL 19            /*  Select the Delay of the 'ramp_sync' Signal Across the Devices */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_RAMP_DATA_VALID_SEL 18            /*  Select If 'ramp_data_valid' Comes from 0->Ramp Generator 1->Register Control */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_RAMP_DATA_VALID 17            /*  Ramp_data_valid Control Register */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_STOP_DEL  9            /*  PGA Shunt Activation Delay After Slope1 */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_START_DEL  1            /*  PGA Shunt Activation Delay Before Slope1 */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_EN  0            /*  Enable PGA Shunt Signal Generation */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_RAMP_SYNC_DIS 0x10000000    /*  Disable 'ramp_sync' Input. Ramps or ADC Synchronization Won't Start */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_VGA_GAUSS_DIS 0x08000000    /*  Disable VGA Gain Gaussian Shape */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_ADC_SYNC_DEL 0x03800000    /*  Select the Delay of the 'adc_sync' Signal Across the Devices */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_RAMP_SYNC_DEL 0x00380000    /*  Select the Delay of the 'ramp_sync' Signal Across the Devices */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_RAMP_DATA_VALID_SEL 0x00040000    /*  Select If 'ramp_data_valid' Comes from 0->Ramp Generator 1->Register Control */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_RAMP_DATA_VALID 0x00020000    /*  Ramp_data_valid Control Register */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_STOP_DEL 0x0001FE00    /*  PGA Shunt Activation Delay After Slope1 */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_START_DEL 0x000001FE    /*  PGA Shunt Activation Delay Before Slope1 */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_EN 0x00000001    /*  Enable PGA Shunt Signal Generation */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG3_ADC_SYNC_DEL_1 0x00000000            /*  adc_sync_del: Delay of ADC_sync is 1 Clock Cycle */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG3_ADC_SYNC_DEL_2 0x00800000            /*  adc_sync_del: Delay of ADC_sync is 2 Clock Cycle */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG3_ADC_SYNC_DEL_3 0x01000000            /*  adc_sync_del: Delay of ADC_sync is 3 Clock Cycle */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG3_ADC_SYNC_DEL_4 0x01800000            /*  adc_sync_del: Delay of ADC_sync is 4 Clock Cycle */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG3_ADC_SYNC_DEL_5 0x02000000            /*  adc_sync_del: Delay of ADC_sync is 5 Clock Cycle */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG3_ADC_SYNC_DEL_6 0x02800000            /*  adc_sync_del: Delay of ADC_sync is 6 Clock Cycles */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG3_ADC_SYNC_DEL_7 0x03000000            /*  adc_sync_del: Delay of ADC_sync is 7 Clock Cycles */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG3_ADC_SYNC_DEL_8 0x03800000            /*  adc_sync_del: Delay of ADC_sync is 8 Clock Cycles */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG3_RAMP_SYNC_DEL_1 0x00000000            /*  ramp_sync_del: Delay of Ramp_sync is 1 Clock Cycle */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG3_RAMP_SYNC_DEL_2 0x00080000            /*  ramp_sync_del: Delay of Ramp_sync is 2 Clock Cycles */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG3_RAMP_SYNC_DEL_3 0x00100000            /*  ramp_sync_del: Delay of Ramp_sync is 3 Clock Cycles */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG3_RAMP_SYNC_DEL_4 0x00180000            /*  ramp_sync_del: Delay of Ramp_sync is 4 Clock Cycles */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG3_RAMP_SYNC_DEL_5 0x00200000            /*  ramp_sync_del: Delay of Ramp_sync is 5 Clock Cycles */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG3_RAMP_SYNC_DEL_6 0x00280000            /*  ramp_sync_del: Delay of Ramp_sync is 6 Clock Cycles */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG3_RAMP_SYNC_DEL_7 0x00300000            /*  ramp_sync_del: Delay of Ramp_sync is 7 Clock Cycles */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG3_RAMP_SYNC_DEL_8 0x00380000            /*  ramp_sync_del: Delay of Ramp_sync is 8 Clock Cycles */

/* -------------------------------------------------------------------------------------------------------------------------
          RF_ADPLL_RFPLL_RAMP_CONFIG4          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG4_RAMP_SPARE 20            /*  Spare Bits for Ramp Stuff */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG4_RAMP_SPARE 0x0FF00000    /*  Spare Bits for Ramp Stuff */

/* -------------------------------------------------------------------------------------------------------------------------
          RF_ADPLL_RFPLL_RAMP_CONFIG6          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG6_RAMP_OFF_TIME  0            /*  IDLE Time Between Bursts of Ramps */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG6_RAMP_OFF_TIME 0xFFFFFFFF    /*  IDLE Time Between Bursts of Ramps */

/* -------------------------------------------------------------------------------------------------------------------------
          RF_ADPLL_RFPLL_RAMP_CONFIG7          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG7_AFE_OFF_TIME  0            /*  IDLE Time Between Bursts of Ramps (for Data_valid) */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG7_AFE_OFF_TIME 0xFFFFFFFF    /*  IDLE Time Between Bursts of Ramps (for Data_valid) */

/* -------------------------------------------------------------------------------------------------------------------------
          RF_ADPLL_RFPLL_RAMP_CONFIG8          Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG8_FREF_TO_MUXOUT_SEL 30            /*  Select FREF to MUXOUT */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG8_MUXOUT_MODE 24            /*  Muxout Control Bits */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STATUS_2 16            /*  Ramp Status Register for Pin RAMP_STAT_2 */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STATUS_1  8            /*  Ramp Status Register for Pin RAMP_STAT_1 */
#define BITP_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STATUS_0  0            /*  Ramp Status Register for Pin RAMP_STAT_0 */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG8_FREF_TO_MUXOUT_SEL 0xC0000000    /*  Select FREF to MUXOUT */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG8_MUXOUT_MODE 0x3F000000    /*  Muxout Control Bits */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STATUS_2 0x00FF0000    /*  Ramp Status Register for Pin RAMP_STAT_2 */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STATUS_1 0x0000FF00    /*  Ramp Status Register for Pin RAMP_STAT_1 */
#define BITM_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STATUS_0 0x000000FF    /*  Ramp Status Register for Pin RAMP_STAT_0 */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_FREF_SJ 0x00000000            /*  fref_to_muxout_sel: Output of SJ */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_FREF_DIV 0x40000000            /*  fref_to_muxout_sel: Output of Divider */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_FREF_DOUBLER 0x80000000            /*  fref_to_muxout_sel: Output of Doubler */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_FREF_LVLSHFT 0xC0000000            /*  fref_to_muxout_sel: Output of Level Shifter */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_OFF 0x00000000            /*  muxout_mode: Bring GND to muxout */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_GND 0x01000000            /*  muxout_mode: Bring GND to muxout */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_VDD 0x02000000            /*  muxout_mode: Bring VDD to muxout */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_FREFDIG 0x03000000            /*  muxout_mode: Reference clock that clocks the digital block */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_FREFOUT 0x04000000            /*  muxout_mode: Reference clock */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_BUBBLE_OUTER 0x05000000            /*  muxout_mode: Goes high when the a bubble is detected on the first/last 4 bits of TDC output */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_GARB_FRAC 0x06000000            /*  muxout_mode: Goes high when garbage is detected on TDC output */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_RTWO_PHASE_DIR 0x07000000            /*  muxout_mode: RTWO direction input applied to TDC decoder */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_FINE_TOGGLE 0x08000000            /*  muxout_mode: Goes high if the fine control (integer part) toggles after frequency acquisition */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_LOCK_RAMP 0x09000000            /*  muxout_mode: lock detect during ramp generation, indicates when phase error is settled */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_SPIKE_OV 0x0A000000            /*  muxout_mode: Goes high if sudden unwanted spike appears on the phase error; different from the skew induced glitches */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_NEG_GLITCH 0x0B000000            /*  muxout_mode: Goes high when negative glitch appears on the frequency error (1 LSB magnitude) due to skew mismatch in CKV path */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_POS_GLITCH 0x0C000000            /*  muxout_mode: Goes high when positive glitch appears on the frequency error (1 LSB magnitude) due to skew mismatch in CKV path */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_CLK 0x0D000000            /*  muxout_mode: CLK that the dig_top is running on; FREF or CKR */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_SD_CLK 0x0E000000            /*  muxout_mode: CLK that the sigma delta modulator at the fractional input of DCO is running on */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_NEG_GLITCH_CORR 0x0F000000            /*  muxout_mode: Goes high when negative glitch appears on the corrected frequency error (1 LSB magnitude) after first glitch correction; Due to TDC errors for eg */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_POS_GLITCH_CORR 0x10000000            /*  muxout_mode: Goes high when positive glitch appears on the corrected frequency error (1 LSB magnitude) after first glitch correction; Due to TDC errors for eg */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_BUBBLE_DETECT 0x11000000            /*  muxout_mode: Goes high when a bubble is detected on the TDC code and corrected */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_HISTO_CAL_BUSY 0x12000000            /*  muxout_mode: Histogram calibration active */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_BOWCAL_ACT 0x13000000            /*  muxout_mode: Bow calibration active */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_COMP 0x14000000            /*  muxout_mode: Ramp complete signal */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_AFE_CLK 0x15000000            /*  muxout_mode: AFE clock */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_PVT_ACQ 0x16000000            /*  muxout_mode: PVT acquisition signal; High during PVT mode */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_COARSE_ACQ 0x17000000            /*  muxout_mode: Coarse acquisition signal; High during coarse mode */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_FINE1_ACQ 0x18000000            /*  muxout_mode: Fine 1 acquisition signal; High during fine1 mode */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_FINE2_ACQ 0x19000000            /*  muxout_mode: Fine 2 acquisition signal; High during fine2 mode */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_OVFL_PVT 0x1A000000            /*  muxout_mode: overflow signal on phase error after PVT mode of acquisition */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_OVFL_COARSE 0x1B000000            /*  muxout_mode: overflow signal on phase error after coarse mode of acquisition */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_OVFL_FINE 0x1C000000            /*  muxout_mode: overflow signal on phase error after fine mode of acquisition */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_LOCK_FINE2 0x1D000000            /*  muxout_mode: lock detect signal */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_CORR1 0x1E000000            /*  muxout_mode: LSB of the correction signal from the first glitch correction circuit */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_CORR2 0x1F000000            /*  muxout_mode: LSB of the correction signal from the second glitch correction circuit */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_GLITCH1_FREEZE 0x20000000            /*  muxout_mode: freeze signal on phase error from the first glitch correction circuit */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_GLITCH2_FREEZE 0x21000000            /*  muxout_mode: freeze signal on phase error from the second glitch correction circuit */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_SPIKE_FREEZE 0x22000000            /*  muxout_mode: freeze signal on phase error due to spike detection */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_PHE_FREEZE 0x23000000            /*  muxout_mode: freeze signal on phase error due to glitch1, glitch2, spike, or garbage/outer bubble in TDC */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_GARB_FREEZE 0x24000000            /*  muxout_mode: freeze signal on phase error due to garbage/outer bubble in TDC */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_GARB_FREEZE_ACQ 0x25000000            /*  muxout_mode: freeze signal on phase error due to garbage/outer bubble in TDC during acquisition mode */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_GARB_FREEZE_TRACK 0x26000000            /*  muxout_mode: freeze signal on phase error due to garbage/outer bubble in TDC during tracking mode */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_LOL 0x27000000            /*  muxout_mode: Loss of lock */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STAT_0 0x28000000            /*  muxout_mode: ramp stat_0 */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_RAMP_STAT_ON 0x29000000            /*  muxout_mode: ramp_stat_on */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_DMA_EN 0x2A000000            /*  muxout_mode: DMA enable */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_PGA_SHUNT 0x2B000000            /*  muxout_mode: PGA shunt signal */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_DATA_VALID 0x2C000000            /*  muxout_mode: Ramp Data Valid */
#define ENUM_RF_ADPLL_RFPLL_RAMP_CONFIG8_GND2 0x2D000000            /*  muxout_mode: Bring GND to muxout */


/* ============================================================================================================================
        
   ============================================================================================================================ */

/* ============================================================================================================================
        RAMPGEN
   ============================================================================================================================ */
#define REG_RAMPGEN_RAMP_GEN_DEL01_RESET     0x00000000            /*      Reset Value for RAMP_GEN_DEL01  */
#define REG_RAMPGEN_RAMP_GEN_DEL01           0xF0020200            /*  RAMPGEN DEL01 */
#define REG_RAMPGEN_RAMP_GEN_DEL12_RESET     0x00000000            /*      Reset Value for RAMP_GEN_DEL12  */
#define REG_RAMPGEN_RAMP_GEN_DEL12           0xF0020204            /*  RAMPGEN DEL12 */
#define REG_RAMPGEN_RAMP_GEN_STEP1_RESET     0x00000000            /*      Reset Value for RAMP_GEN_STEP1  */
#define REG_RAMPGEN_RAMP_GEN_STEP1           0xF0020208            /*  RAMPGEN SLOPE1 */
#define REG_RAMPGEN_RAMP_GEN_STEP0_RESET     0x00000000            /*      Reset Value for RAMP_GEN_STEP0  */
#define REG_RAMPGEN_RAMP_GEN_STEP0           0xF002020C            /*  RAMPGEN SLOPE0 */
#define REG_RAMPGEN_RAMP_GEN_DEV0_RESET      0x00000000            /*      Reset Value for RAMP_GEN_DEV0  */
#define REG_RAMPGEN_RAMP_GEN_DEV0            0xF0020210            /*  RAMPGEN DEV0 */
#define REG_RAMPGEN_RAMP_GEN_DEV1_RESET      0x00000000            /*      Reset Value for RAMP_GEN_DEV1  */
#define REG_RAMPGEN_RAMP_GEN_DEV1            0xF0020214            /*  RAMPGEN DEV1 */
#define REG_RAMPGEN_RAMP_GEN_TX_RESET        0x00000000            /*      Reset Value for RAMP_GEN_TX  */
#define REG_RAMPGEN_RAMP_GEN_TX              0xF0020218            /*  RAMPGEN RAMP_PH */
#define REG_RAMPGEN_RAMP_GEN_AFECNT_RESET    0x00000000            /*      Reset Value for RAMP_GEN_AFECNT  */
#define REG_RAMPGEN_RAMP_GEN_AFECNT          0xF002021C            /*  RAMPGEN AFE_CNT */
#define REG_RAMPGEN_RAMP_GEN_PHASE_MOD_RESET 0x00000000            /*      Reset Value for RAMP_GEN_PHASE_MOD  */
#define REG_RAMPGEN_RAMP_GEN_PHASE_MOD       0xF0020220            /*  RAMPGEN RAMP_PH_MOD */

/* ============================================================================================================================
        RAMPGEN Register BitMasks, Positions & Enumerations 
   ============================================================================================================================ */
/* -------------------------------------------------------------------------------------------------------------------------
          RAMPGEN_RAMP_GEN_DEL01               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RAMPGEN_RAMP_GEN_DEL01_DEL_1    22            /*  Sets Duration for Delay 1 in Clock Cycles */
#define BITP_RAMPGEN_RAMP_GEN_DEL01_DEL_0     0            /*  Sets Duration for Delay 0 in Clock Cycles */
#define BITM_RAMPGEN_RAMP_GEN_DEL01_DEL_1    0xFFC00000    /*  Sets Duration for Delay 1 in Clock Cycles */
#define BITM_RAMPGEN_RAMP_GEN_DEL01_DEL_0    0x003FFFFF    /*  Sets Duration for Delay 0 in Clock Cycles */

/* -------------------------------------------------------------------------------------------------------------------------
          RAMPGEN_RAMP_GEN_DEL12               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RAMPGEN_RAMP_GEN_DEL12_DEL_2    10            /*  Sets Duration for Delay 2 in Clock Cycles */
#define BITP_RAMPGEN_RAMP_GEN_DEL12_DEL_1     0            /*  Sets Duration for Delay 1 in Clock Cycles */
#define BITM_RAMPGEN_RAMP_GEN_DEL12_DEL_2    0xFFFFFC00    /*  Sets Duration for Delay 2 in Clock Cycles */
#define BITM_RAMPGEN_RAMP_GEN_DEL12_DEL_1    0x000003FF    /*  Sets Duration for Delay 1 in Clock Cycles */

/* -------------------------------------------------------------------------------------------------------------------------
          RAMPGEN_RAMP_GEN_STEP1               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RAMPGEN_RAMP_GEN_STEP1_RAMP_STEPS_1  0            /*  Number of Steps in Slope 1 */
#define BITM_RAMPGEN_RAMP_GEN_STEP1_RAMP_STEPS_1 0xFFFFFFFF    /*  Number of Steps in Slope 1 */

/* -------------------------------------------------------------------------------------------------------------------------
          RAMPGEN_RAMP_GEN_STEP0               Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RAMPGEN_RAMP_GEN_STEP0_RAMP_STEPS_0  0            /*  Number of Steps in Slope 0 */
#define BITM_RAMPGEN_RAMP_GEN_STEP0_RAMP_STEPS_0 0xFFFFFFFF    /*  Number of Steps in Slope 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          RAMPGEN_RAMP_GEN_DEV0                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RAMPGEN_RAMP_GEN_DEV0_RAMP_DEV_0  0            /*  Ramp Deviation for Slope 0 */
#define BITM_RAMPGEN_RAMP_GEN_DEV0_RAMP_DEV_0 0xFFFFFFFF    /*  Ramp Deviation for Slope 0 */

/* -------------------------------------------------------------------------------------------------------------------------
          RAMPGEN_RAMP_GEN_DEV1                Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RAMPGEN_RAMP_GEN_DEV1_RAMP_DEV_1  0            /*  Ramp Deviation for Slope 1 */
#define BITM_RAMPGEN_RAMP_GEN_DEV1_RAMP_DEV_1 0xFFFFFFFF    /*  Ramp Deviation for Slope 1 */

/* -------------------------------------------------------------------------------------------------------------------------
          RAMPGEN_RAMP_GEN_TX                  Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_2 31            /*  Status Pin 2 Bit Value for Status Mode 11 */
#define BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_1 30            /*  Status Pin 1 Bit Value for Status Mode 11 */
#define BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_0 29            /*  Status Pin 0 Bit Value for Status Mode 11 */
#define BITP_RAMPGEN_RAMP_GEN_TX_PHASE_STEP  24            /*  Phase Modulation Step Divider */
#define BITP_RAMPGEN_RAMP_GEN_TX_TX_PATTERN  21            /*  TX Pattern Sequence */
#define BITP_RAMPGEN_RAMP_GEN_TX_PA2_PHASE   14            /*  PA2 Phase (pa2_phase*360/128 Degrees) */
#define BITP_RAMPGEN_RAMP_GEN_TX_PA1_PHASE    7            /*  PA1 Phase (pa1_phase*360/128 Degrees) */
#define BITP_RAMPGEN_RAMP_GEN_TX_PA0_PHASE    0            /*  PA0 Phase (pa0_phase*360/128 Degrees) */
#define BITM_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_2 0x80000000    /*  Status Pin 2 Bit Value for Status Mode 11 */
#define BITM_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_1 0x40000000    /*  Status Pin 1 Bit Value for Status Mode 11 */
#define BITM_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_0 0x20000000    /*  Status Pin 0 Bit Value for Status Mode 11 */
#define BITM_RAMPGEN_RAMP_GEN_TX_PHASE_STEP  0x1F000000    /*  Phase Modulation Step Divider */
#define BITM_RAMPGEN_RAMP_GEN_TX_TX_PATTERN  0x00E00000    /*  TX Pattern Sequence */
#define BITM_RAMPGEN_RAMP_GEN_TX_PA2_PHASE   0x001FC000    /*  PA2 Phase (pa2_phase*360/128 Degrees) */
#define BITM_RAMPGEN_RAMP_GEN_TX_PA1_PHASE   0x00003F80    /*  PA1 Phase (pa1_phase*360/128 Degrees) */
#define BITM_RAMPGEN_RAMP_GEN_TX_PA0_PHASE   0x0000007F    /*  PA0 Phase (pa0_phase*360/128 Degrees) */

/* -------------------------------------------------------------------------------------------------------------------------
          RAMPGEN_RAMP_GEN_AFECNT              Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RAMPGEN_RAMP_GEN_AFECNT_AFE_RAMP_TIME 16            /*  Ramp Duration in AFE Clock Cycles */
#define BITP_RAMPGEN_RAMP_GEN_AFECNT_AFE_START_OFF_TIME  0            /*  Offset for Data Valid High After Start of the Ramp */
#define BITM_RAMPGEN_RAMP_GEN_AFECNT_AFE_RAMP_TIME 0xFFFF0000    /*  Ramp Duration in AFE Clock Cycles */
#define BITM_RAMPGEN_RAMP_GEN_AFECNT_AFE_START_OFF_TIME 0x0000FFFF    /*  Offset for Data Valid High After Start of the Ramp */

/* -------------------------------------------------------------------------------------------------------------------------
          RAMPGEN_RAMP_GEN_PHASE_MOD           Pos/Masks         Description
   ------------------------------------------------------------------------------------------------------------------------- */
#define BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_NUM_SAMPLES 18            /*  Number of Samples per Chirp */
#define BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA2_PHASE_DEV 12            /*  Phase Modulation Deviation for PA2 */
#define BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA1_PHASE_DEV  6            /*  Phase Modulation Deviation for PA1 */
#define BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA0_PHASE_DEV  0            /*  Phase Modulation Deviation for PA0 */
#define BITM_RAMPGEN_RAMP_GEN_PHASE_MOD_NUM_SAMPLES 0x7FFC0000    /*  Number of Samples per Chirp */
#define BITM_RAMPGEN_RAMP_GEN_PHASE_MOD_PA2_PHASE_DEV 0x0003F000    /*  Phase Modulation Deviation for PA2 */
#define BITM_RAMPGEN_RAMP_GEN_PHASE_MOD_PA1_PHASE_DEV 0x00000FC0    /*  Phase Modulation Deviation for PA1 */
#define BITM_RAMPGEN_RAMP_GEN_PHASE_MOD_PA0_PHASE_DEV 0x0000003F    /*  Phase Modulation Deviation for PA0 */

/* ====================================================================================================
 *    Interrupt Definitions
 * ==================================================================================================== */
#define INTR_ARC_Reset                         0		/* ARC_Reset */
#define INTR_ARC_MemoryError                   1		/* ARC_MemoryError */
#define INTR_ARC_InstructionError              2		/* ARC_InstructionError */
#define INTR_ARC_EV_MachineCheck               3		/* ARC_EV_MachineCheck */
#define INTR_ARC_EV_ProtV                      6		/* ARC_EV_ProtV */
#define INTR_ARC_EV_PrivilegeV                 7		/* ARC_EV_PrivilegeV */
#define INTR_ARC_EV_SWI                        8		/* ARC_EV_SWI */
#define INTR_ARC_EV_Trap                       9		/* ARC_EV_Trap */
#define INTR_ARC_EV_Extension                 10		/* ARC_EV_Extension */
#define INTR_ARC_EV_DivZero                   11		/* ARC_EV_DivZero */
#define INTR_ARC_EV_Maligned                  13		/* ARC_EV_Maligned */
#define INTR_ARC_Timer0                       16		/* ARC_Timer0 */
#define INTR_ARC_Timer1                       17		/* ARC_Timer1 */
#define INTR_ARC_WDT                          18		/* ARC_WDT */
#define INTR_SPI_RX_DONE                      19		/* Indicates last location of the memory has been written */
#define INTR_SPI_TX_DONE                      20		/* Indicates last bit has been transmitted from SPI */
#define INTR_uDMA_CH0_DONE                    21		/* uDMA Channel 0 Done */
#define INTR_uDMA_CH1_DONE                    22		/* uDMA Channel 1 Done */
#define INTR_uDMA_CH2_DONE                    23		/* uDMA Channel 2 Done */
#define INTR_uDMA_CH3_DONE                    24		/* uDMA Channel 3 Done */
#define INTR_uDMA_CH4_DONE                    25		/* uDMA Channel 4 Done */
#define INTR_uDMA_CH5_DONE                    26		/* uDMA Channel 5 Done */
#define INTR_uDMA_CH6_DONE                    27		/* uDMA Channel 6 Done */
#define INTR_uDMA_CH7_DONE                    28		/* uDMA Channel 7 Done */
#define INTR_WDT_EXPIRY_ERR                   29		/* WDT_EXPIRY_ERR */
#define INTR_WDT_KEY_ERR                      30		/* WDT_KEY_ERR */
#define INTR_WDT_MIN_WINDOW_ERR               30		/* WDT_MIN_WINDOW_ERR */
#define INTR_WDT_PROGRAM_ERR                  30		/* WDT_PROGRAM_ERR */
#define INTR_MIPI_MIPI_STAT                   31		/* MIPI Status interrupt */
#define INTR_MIPI_CSI2_IRQ                    32		/* CSI2 IP interrupt signal */
#define INTR_OTPC_OTP_INT_ECC                 33		/* OTPC_OTP_INT_ECC */
#define INTR_OTPC_OTP_INT_BOOT                34		/* OTPC_OTP_INT_BOOT */
#define INTR_DDS_ECC_SB_ERR                   35		/* DDS_ECC_SB_ERR */
#define INTR_DDS_ECC_DB_ERR                   36		/* DDS_ECC_DB_ERR */
#define INTR_DDS_DATA_DONE                    37		/* DDS_DATA_DONE */
#define INTR_misc_dccm_write_int              38		/* misc_dccm_write_int */
#define INTR_FaultCtl_Fault1                  39		/* Dual Rail Active High Fault */
#define INTR_PINT_irq0                        40		/* Pin Interrupt Block */
#define INTR_PINT_irq1                        41		/* Pin Interrupt Block */
#define INTR_RAMPGEN_chirp_start              42		/* RAMPGEN_chirp_start */
#define INTR_RAMPGEN_last_chirp_start         43		/* RAMPGEN_last_chirp_start */
#define INTR_LVDS_lvds_stat                   44		/* LVDS status interrupt */
#define INTR_AuxADC_ADC_IRQ                   45		/* AuxADC Conversion Done */
#define INTR_AuxADC_MORE_THAN_ULIM            46		/* AuxADC More Than Upper Limit */
#define INTR_AuxADC_MORE_THAN_SULIM           47		/* AuxADC More Than Secondary Upper Limit */
#define INTR_AuxADC_MORE_THAN_LLIM            48		/* AuxADC Less Than Lower Limit */
#define INTR_AuxADC_MORE_THAN_SLLIM           49		/* AuxADC Less Than Secondary Lower Limit */
#define INTR_uDMA_CHAN_ERR                    50		/* Channel Error */
#define INTR_RAMPGEN_chirp_burst_complete     51		/* Ramp Generator Chirp Burst Complete */
#define INTR_AFE0_MORE_THAN_ULIM              52		/* High if AFE0 Data is Higher Than Upper Limit */
#define INTR_AFE0_LESS_THAN_LLIM              53		/* High if AFE0 Data is Lower Than Lower Limit */
#define INTR_AFE1_MORE_THAN_ULIM              54		/* High if AFE1 Data is Higher Than Upper Limit */
#define INTR_AFE1_LESS_THAN_LLIM              55		/* High if AFE1 Data is Lower Than Lower Limit */
#define INTR_AFE2_MORE_THAN_ULIM              56		/* High if AFE2 Data is Higher Than Upper Limit */
#define INTR_AFE2_LESS_THAN_LLIM              57		/* High if AFE2 Data is Lower Than Lower Limit */
#define INTR_AFE3_MORE_THAN_ULIM              58		/* High if AFE3 Data is Higher Than Upper Limit */
#define INTR_AFE3_LESS_THAN_LLIM              59		/* High if AFE3 Data is Lower Than Lower Limit */
#define INTR_PORTA_powerdown                  60		/* Powerdown Interrupt */
#define INTR_MIPICSI2_diag_irq                61		/* MIPI CSI2 Controller Diagnostic Interrupt */
#define INTR_uDMA_CH8_DONE                    62		/* uDMA Channel 8 Done */
#define INTR_uDMA_CH9_DONE                    63		/* uDMA Channel 9 Done */
#define INTR_uDMA_CH10_DONE                   64		/* uDMA Channel 10 Done */
#define INTR_uDMA_CH11_DONE                   65		/* uDMA Channel 11 Done */
#define INTR_uDMA_CH12_DONE                   66		/* uDMA Channel 12 Done */
#define INTR_uDMA_CH13_DONE                   67		/* uDMA Channel 13 Done */
#define INTR_uDMA_CH14_DONE                   68		/* uDMA Channel 14 Done */
#define INTR_uDMA_CH15_DONE                   69		/* uDMA Channel 15 Done */
#define INTR_WDT_1_EXPIRY_ERR                 70		/* WDT 1 Fault */
#define INTR_WDT_1_KEY_ERR                    70		/* WDT 1 Fault */
#define INTR_WDT_1_MIN_WINDOW_ERR             70		/* WDT 1 Fault */
#define INTR_WDT_1_PROGRAM_ERR                70		/* WDT 1 Fault */
#define INTR_Goertzel_bin_compute_complete    71		/* Goertzel Bin Computation Complete */
#define INTR_Goertzel_phase_compute_complete  72		/* Goertzel Phase Computation Complete */
#define INTR_FFT_dma_intr                     73		/* FFT DMA Interrupt */
#define INTR_FFT_mac_status_err               74		/* FFT MAC Status Error */
#define INTR_FFT_ecc_sb_err                   75		/* FFT ECC Single Bit Error */
#define INTR_FFT_ecc_db_err                   76		/* FFT ECC Double Bit Error */
#define INTR_AFE0_LESS_THAN_SAFELLIM          77		/* Decimation Filter Channel 0 Lower Safe Limit Check */
#define INTR_AFE0_MORE_THAN_SAFEULIM          77		/* Decimation Filter Channel 0 Upper Safe Limit Check */
#define INTR_AFE1_LESS_THAN_SAFELLIM          78		/* Decimation Filter Channel 1 Lower Safe Limit Check */
#define INTR_AFE1_MORE_THAN_SAFEULIM          78		/* Decimation Filter Channel 1 Upper Safe Limit Check */
#define INTR_AFE2_LESS_THAN_SAFELLIM          79		/* Decimation Filter Channel 2 Lower Safe Limit Check */
#define INTR_AFE2_MORE_THAN_SAFEULIM          79		/* Decimation Filter Channel 2 Upper Safe Limit Check */
#define INTR_AFE3_LESS_THAN_SAFELLIM          80		/* Decimation Filter Channel 3 Lower Safe Limit Check */
#define INTR_AFE3_MORE_THAN_SAFEULIM          80		/* Decimation Filter Channel 3 Upper Safe Limit Check */
#define INTR_AFE0_overflow_underflow_error    81		/* Decimation Filter Channel 0 Overflow/Underflow */
#define INTR_AFE1_overflow_underflow_error    82		/* Decimation Filter Channel 1 Overflow/Underflow */
#define INTR_AFE2_overflow_underflow_error    83		/* Decimation Filter Channel 2 Overflow/Underflow */
#define INTR_AFE3_overflow_underflow_error    84		/* Decimation Filter Channel 3 Overflow/Underflow */
#define INTR_DATA_PORT_START_DMA              85		/* Data Port DMA Request Interrupt */
#define INTR_DATA_PORT_BUFFER_MODE_DONE       86		/* Data Port Buffer Mode Done Interrupt */
#define INTR_FFT_fft_compute_done             87		/* FFT Compute Done */
#define INTR_Goertzel_overflow_underflow      88		/* Goertzel Overflow/Underflow */
#define INTR_FFT_noise_morethanlim            89		/* FFT Noise More Than Programmed Limit */
#define INTR_FaultCtl_Fault0b                 90		/* Dual Rail Active Low Redundant Fault */
#define INTR_OTPC_OTP_INT_IPS                 91		/* OTP Integrated Power Supply not Good */
#define INTR_RAMPGEN_STAT_ON                  92		/* Ramp Generator RAMP_ON Interrupt */
#define INTR_misc_filter_output_compare       93		/* Decimation Filter Comparator Check */
#define INTR_TESTTONEGEN_ECC_error            94		/* SSB sine and cosine memory ECC error. Interrupt generated when address ECC , DED, SED occurs for sine or cosine memories */
#define INTR_RF_ADPLL_FAULT                   95		/* Fault Signal from RFPLL */
#define INTR_RAMPGEN_STAT0                    96		/* Ramp Generator Status 1 */
#define INTR_RAMPGEN_STATUS2                  97		/* Ramp Generator Status 2 */
#define INTR_RAMPGEN_STAT2                    98		/* Ramp Generator Status 3 */
#define INTR_misc_MUXOUT                      99		/* MUXOUT */
#define INTR_ARC_CCM_sb_err                  100		/* Data Port DMA Request Interrupt */


/* ============================================================================
       Memory Map Macros
   ============================================================================ */


#endif	/* end ifndef _DEF_ADAR690X_H */
