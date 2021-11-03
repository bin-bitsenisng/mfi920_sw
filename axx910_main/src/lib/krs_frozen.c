/************************************************************************
| Project Name: krs_frozen
|    File Name: krs_frozen.c
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
| 2018.06.22   0.0   SKJ   Creation;
|***********************************************************************/

/* include system primitive types */
#include "bts.h"


/* include system driver header */
#include "frozen/frozen.h"
/* include system bsp header */
#include <errno.h>


/* include system application header */

/* final include module header */
#include "krs_frozen.h"
/* declare static variables */

/* static function prototypes */
extern int frozen_unittest(void);
/* functions */

/******************************************************************************
 * function name : krs_frozen_lib_init
 * \brief Description of this fuction
 *
 * detailed decription of this function line 0
 * detailed decription of this function line 1
 * detailed decription of this function line 2 ..
 *
 * Returns retOK if successful, retFail otherwise.
 *
 * \param0 void description
 * \return void description
 * modification date : 2018.06.22
 *****************************************************************************/
void krs_frozen_lib_init(void)
{
#if KRS_FROZEN_LIB_UNITTEST == 1
    int32_t ret;
    ret = frozen_unittest();
    krs_log("FROZEN(json library) Unittest %s\n\r", (ret==0)? "Success":"Fail");
#endif
}


#ifdef __zynq__
#ifdef __cplusplus
extern "C" {
	__attribute__((weak)) sint32 _unlink(char8 *path);
}
#endif
/*
 * unlink -- since we have no file system,
 *           we just return an error.
 */
__attribute__((weak)) sint32 _unlink(char8 *path)
{
  (void) path;
  errno = EIO;
  return (-1);
}
#endif


// The file IO used by the frozen library is not supported on the system, so it overrides the function used for the removal.

/* end of file */
