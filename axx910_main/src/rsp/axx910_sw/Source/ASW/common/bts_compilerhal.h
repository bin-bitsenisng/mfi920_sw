/************************************************************************
| Project Name: bts_compilerhal
|    File Name: bts_compilerhal.h
|  Description: file detailed description
|-----------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------
| SKJ          SONG KYEONG JIN           Lobeye
|-----------------------------------------------------------------------
|              R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------
| Date         Ver  Author  Description
| ----------  ----  ------  --------------------------------------------
| 2020.04.06   0.0   SKJ   Creation;
|***********************************************************************/
#ifndef BTS_COMPILERHAL_H__
#define BTS_COMPILERHAL_H__

#ifdef WIN32


#endif

#ifdef __GNUC__
    #if defined(COMPILER_UNUSEDFUNCTION_START)
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wunused-function"
        #undef COMPILER_UNUSEDFUNCTION_START
    #endif

    #if defined(COMPILER_UNUSEDFUNCTION_STOP)
        #pragma GCC diagnostic pop
        #undef COMPILER_UNUSEDFUNCTION_STOP
    #endif
#endif

#endif // BTS_COMPILERHAL_H__
