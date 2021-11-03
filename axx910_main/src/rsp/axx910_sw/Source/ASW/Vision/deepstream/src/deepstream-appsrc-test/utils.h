#include "gst/gst.h"

//#define CREATE_ELEMENT(ADDR_ELEMENT, FACTORY_NAME, NAME) {\
//    if ( get_element (&(ADDR_ELEMENT), (FACTORY_NAME), (NAME)) == -1 )\
//        return -1;\
//}
//
//#define GET_STATIC_PAD(PAD, ELEMENT, PADNAME) {\
//    PAD = gst_element_get_static_pad ((ELEMENT), (PADNAME));\
//    if (!(PAD)) {\
//        g_printerr ("%s pad failed. Exiting.\n", (PADNAME));\
//        return -1;\
//    }\
//}
//
//#define GET_REQUEST_PAD(PAD, ELEMENT, PADNAME) {\
//    PAD = gst_element_get_request_pad ((ELEMENT), (PADNAME));\
//    if (!(PAD)) {\
//        g_printerr ("%s pad failed. Exiting.\n", (PADNAME));\
//        return -1;\
//    }\
//}

//#define GET_STATIC_PAD(ADDR_PAD, BIN, ELENAME, PADNAME) {\
//    ADDR_PAD = gst_element_get_static_pad (\
//        gst_bin_get_by_name (BIN, ELENAME), PADNAME);\
//    if (!ADDR_PAD) {\
//        g_printerr ("%s pad failed. Exiting.\n", PADNAME);\
//        return -1;\
//    }
//
//#define GET_REQUEST_PAD(ADDR_PAD, BIN, ELENAME, PADNAME) {\
//    ADDR_PAD = gst_element_get_request_pad (\
//        gst_bin_get_by_name (BIN, ELENAME),\
//        PADNAME);\
//    if (!ADDR_PAD) {\
//        g_printerr ("%s pad failed. Exiting.\n", PADNAME);\
//        return -1;\
//    }

#define LINK_PAD(SRCPAD, SINKPAD) {\
    if (gst_pad_link ((SRCPAD), (SINKPAD)) != (GST_PAD_LINK_OK)) {\
        g_printerr ("Failed to link. Exiting.\n");\
        return -1;\
    }\
}
