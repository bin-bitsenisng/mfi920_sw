#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <gst/gst.h>

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