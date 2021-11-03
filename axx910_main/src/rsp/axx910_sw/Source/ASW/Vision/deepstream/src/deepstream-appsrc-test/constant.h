#ifndef __BTS_DEEPSTREAM_APPSRC_TEST_CONSTANT__
#define __BTS_DEEPSTREAM_APPSRC_TEST_CONSTANT__



#define MAX_DISPLAY_LEN 64

#define PGIE_CLASS_ID_VEHICLE 0
#define PGIE_CLASS_ID_PERSON 2

#define CUSTOM_PTS 1

/* Muxer batch formation timeout, for e.g. 40 millisec. Should ideally be set
 * based on the fastest source's framerate. */
#define MUXER_BATCH_TIMEOUT_USEC 33000

  

#endif