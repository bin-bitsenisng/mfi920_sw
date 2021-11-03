/************************************************************************
 | Project Name: KRS24
 |    File Name: krs_clist.c
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
 | 2015.11.04   0.0   SKJ   copy from simclist project;
 |***********************************************************************/

/* include system primitive types */
#include "bts.h"


/* include system driver header */

/* include system bsp header */
#include "os.h"

/* include system application header */
#include "krs_lib.h"

/* final include module header */
#include "krs_clist.h"

/* declare static variables */


/* static function prototypes */

/* functions */


/***************************************************
 * function name : krs_clist_unittest1
 * description : module init function
 * input param : void
 * return : retOk or retFail
 * TODO :
 ***************************************************/
krs_clist_ret_t krs_clist_unittest1(void)
{
    krslist_t mylist; /* declare a list */
    int userval;


    krslist_init(&mylist); /* initialize the list */

    userval = 10;


    krslist_append(&mylist, &userval); /* add an element to the list */

    krs_log("The list now holds %u elements.\n\r", krslist_size(&mylist)); /* get the size of the list */

    krs_log("Your number was: %d\n\r",
            *(int *)krslist_get_at(&mylist, 0)); /* extract the first element of the list */

    krslist_destroy(&mylist);

    return 0;
}


krs_clist_ret_t krs_clist_unittest2(void)
{
    list_t l;
    int i;
    krslist_init(&l);

    /* request to store copies, and provide the metric function */
    krslist_attrcopy(&l, list_meter_int32_t, 1);

    krs_log("Give numbers. Terminate with one negative.\n\r");
    for(i = 10; i != 0; i--)
        krslist_append(&l, &i);

    /* setting the comparator, so the list can sort, find the min, max etc */
    krslist_attrcomparator(&l, list_comparator_int32_t);
    krslist_sort(&l, -1); /* sorting the list in descending (-1) order */

    /* printing out the result */
    krs_log("Sorted values:\n\r");

    krslist_iter_start(&l); /* starting an iteration "session" */
    while(krslist_iter_hasnext(&l))
    {                                                    /* tell whether more values available */
        krs_log("%d\n\r", *(int *)krslist_iter_next(&l)); /* get the next value */
    }
    krslist_iter_stop(&l); /* starting the iteration "session" */

    krslist_destroy(&l);

    return 0;
}

/* end of file */
