#ifndef _TIMESTAMP_H_
#define _TIMESTAMP_H_

#include <unistd.h>
#include <sys/time.h>
#include <stdint.h>

void InitTime(void);

#ifdef __cplusplus
extern "C" {
#endif
uint64_t GetTimeStamp(void);
#ifdef __cplusplus
}
#endif

#endif