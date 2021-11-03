/************************************************************************
 | Project Name: KRS24
 |    File Name: krs_clist.h
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
 | 2015.11.05   0.0   SKJ   Creation;
 |***********************************************************************/

#ifndef KRS_CLIST_H__
#define KRS_CLIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "bts.h"
#include "simclist/simclist.h"
/* module specific types  */
typedef int32_t krs_clist_ret_t;

typedef list_t krslist_t;

#define krslist_init list_init
#define krslist_destroy list_destroy

#define krslist_append list_append
#define krslist_prepend list_prepend
#define krslist_pop list_fetch
#define krslist_get_at list_get_at
#define krslist_get_max list_get_max
#define krslist_get_min list_get_min
#define krslist_extract list_extract_at
#define krslist_insert list_insert_at
#define krslist_delete list_delete
#define krslist_delete_at list_delete_at
#define krslist_delete_range list_delete_range
#define krslist_clear list_clear
#define krslist_empty list_empty
#define krslist_locate list_locate
#define krslist_size list_size

#define krslist_concat list_concat
#define krslist_sort list_sort
#define krslist_iter_start list_iterator_start
#define krslist_iter_hasnext list_iterator_hasnext
#define krslist_iter_next list_iterator_next
#define krslist_iter_stop list_iterator_stop

#define krslist_attrcopy list_attributes_copy
#define krslist_attrcomparator list_attributes_comparator


extern krs_clist_ret_t krs_clist_unittest1(void);
extern krs_clist_ret_t krs_clist_unittest2(void);


#ifdef __cplusplus
}
#endif
#endif /* KRS_CLIST_H__ */
