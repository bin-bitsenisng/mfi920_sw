#include "config_bbox.h"

#ifndef __NVGSTDS_APP_H__
#define __NVGSTDS_APP_H__

#ifdef __cplusplus
extern "C"
{
#endif

struct _AppCtx {
    int argc;
    char **argv;
    BboxConfig bbox_config;
    GMainContext *context;
    int cnt;
    gboolean timeout;
    int ThreadReturnValue;
    gboolean quit; 
    GMainLoop *loop;
};

typedef struct _AppCtx AppCtx;

#ifdef __cplusplus
}
#endif

#endif