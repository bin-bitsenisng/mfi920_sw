/************************************************************************
| Project Name: sys_param_jsontype
|    File Name: sys_param_jsontype.c
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
| 2018.07.19   0.0f   SKJ   Creation;
|***********************************************************************/

#include "bts.h"
#include "sys_param_jsontype.h"


/******************************************************************/
/* Packing Config data set  */
/******************************************************************/
sys_param_sidxdidx_configinfo_packing_t sys_param_sidxdidx_configinfo_packing;
sys_param_sidxdidx_configinfo_packing_t sys_param_sidxdidx_configinfo_packing_factory;
sys_param_pid0_status_data_t sys_param_pid0_status_data;
sys_param_pid8_its_data_t sys_param_pid8_its_data;
sys_param_pid9_vf_data_t sys_param_pid9_vf_data;

//sys_param_array_test_t sys_param_array_test;

//sys_param_array_test_t sys_param_array_test_default={
//    /* .arr1d = */ {
//        /* .array_bool_1d = */ {1,1,1,1},
//        /* .array_int32_1d = */ {1,2,3,4},
//        /* .array_int64_1d = */ {1,2,3,4},
//        /* .array_f32_1d = */ {1.1f,2.2f,3.3f,4.4f},
//        /* .array_f64_1d = */ {1.1f,2.2f,3.3f,4.4f},
//        /* .string_1d = */ "1d",
//    },
//
//    /* .arr2d = */ {
//        /* .array_bool_2d = */ {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}},
//        /* .array_int32_2d = */ {{1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}},
//        /* .array_int64_2d = */ {{1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}},
//        /* .array_f32_2d = */ {{1.1f,2.2f,3.3f,4.4f},{1.1f,2.2f,3.3f,4.4f},{1.1f,2.2f,3.3f,4.4f},{1.1f,2.2f,3.3f,4.4f}},
//        /* .array_f64_2d = */ {{1.1f,2.2f,3.3f,4.4f},{1.1f,2.2f,3.3f,4.4f},{1.1f,2.2f,3.3f,4.4f},{1.1f,2.2f,3.3f,4.4f}},
//        /* .string_2d = */ {"2d0","2d1","2d2","2d3"},
//	},
//
//    /* .arrobj1d = */ {
//        {
//            /* .array_bool_1d = */ {1,1,1,1},
//            /* .array_int32_1d = */ {1,2,3,4},
//            /* .array_int64_1d = */ {1,2,3,4},
//            /* .array_f32_1d = */ {1.1f,2.2f,3.3f,4.4f},
//            /* .array_f64_1d = */ {1.1f,2.2f,3.3f,4.4f},
//            /* .string_1d = */ "ob1",
//        },
//
//
//        {
//            /* .array_bool_1d = */ {1,1,1,1},
//            /* .array_int32_1d = */ {1,2,3,4},
//            /* .array_int64_1d = */ {1,2,3,4},
//            /* .array_f32_1d = */ {1.1f,2.2f,3.3f,4.4f},
//            /* .array_f64_1d = */ {1.1f,2.2f,3.3f,4.4f},
//            /* .string_1d = */ "ob2",
//        },
//    },
//};

