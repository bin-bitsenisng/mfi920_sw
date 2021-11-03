#include "timestamp.h"
#include "timestamp_cfg.h"

uint64_t g_base_time;

void InitTime(void)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    g_base_time = tv.tv_sec*(uint64_t)1000000 + tv.tv_usec;
}

uint64_t GetTimeStamp(void)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (tv.tv_sec*(uint64_t)1000000 + tv.tv_usec - g_base_time)/100;
}