/************************************************************************
 | Project Name: KRS24
 |    File Name: krs_base_return.h
 |  Description: detailed Description
 |-----------------------------------------------------------------------
 |               A U T H O R   I D E N T I T Y
 |-----------------------------------------------------------------------
 | Initials     Name                      Company
 | --------     ---------------------     -------------------------------
 | SKJ          SONG KYEONG JIN           KRS Corporation
 |-----------------------------------------------------------------------
 |              R E V I S I O N   H I S T O R Y
 |-----------------------------------------------------------------------
 | Date         Ver  Author  Description
 | ----------  ----  ------  --------------------------------------------
 | 2014.12.02   0.0   SKJ   Creation;
 |***********************************************************************/

#ifndef KRS_BASE_RETURN_H__
#define KRS_BASE_RETURN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* minimize include in here for make lower reentered cross reference */
/* include system primitive types */
#include "krs_basetype.h"

/* module specific types  */
typedef enum
{
    retOK = 0,
    retFail = 1
}bts_base_return_type_t;

typedef int32_t bts_ret_t;
/* define structure for this module */


/* declare extern global variables */


/* declare extern global functions */


#ifdef __cplusplus
}
#endif

#endif /* KRS_BASE_RETURN_H__ */
