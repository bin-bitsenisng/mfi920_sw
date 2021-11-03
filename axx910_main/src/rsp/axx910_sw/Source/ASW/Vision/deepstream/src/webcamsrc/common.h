#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <gst/gst.h>
#include "gstnvdsmeta.h"

typedef struct
{
        gint               border_width      ;
        NvOSD_ColorParams  border_color      ;
        GHashTable        *border_color_table;
} BboxConfig;

#define CHECK_ERROR(error) \
    if (error) { \
        g_print ("%s", error->message); \
        goto done; \
    }

#define NVGSTDS_ERR_MSG_V(msg, ...) \
    g_print("** ERROR: <%s:%d>: " msg "\n", __func__, __LINE__, ##__VA_ARGS__)
#define NVGSTDS_WARN_MSG_V(msg, ...) \
    g_print("** WARN: <%s:%d>: " msg "\n", __func__, __LINE__, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif