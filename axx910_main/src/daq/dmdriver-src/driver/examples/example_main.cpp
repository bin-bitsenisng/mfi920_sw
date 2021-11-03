/* Copyright (c) 2018-2020 Analog Devices Inc. All rights reserved
*
* Clear BSD license
* -----------------
* Redistribution and use in source and binary forms, with or without
* modification, are permitted (subject to the limitations in the disclaimer
* below) provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice,
*   this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright notice,
*   this list of conditions and the following disclaimer in the documentation
*   and/or other materials provided with the distribution.
*
* * Neither the name of Analog Devices, Inc. nor the names of its contributors
*   may be used to endorse or promote products derived from this software
*   without specific prior written permission.
*
* NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
* THIS LICENSE.  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
* NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
* OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
// #include "application.h"
#include "bts_application.h"
#include "host_dev.h"
#include <pthread.h>
#include <mqueue.h>
#include <errno.h>

host_device_handle_t host_dev;
host_device_handle_t * host_dev_p;
mqd_t mqd;

/* Run both examples by default */
#define EXAMPLE_WITH_PERIODIC_CAL
// #define EXAMPLE_WITH_TASKLISTS
 
// int main_orig()
// {
//     host_dev_p = &host_dev;
// #ifdef EXAMPLE_WITH_PERIODIC_CAL
//     /* Example showing System Calibration (end of line factory calibration) */
//     // example_syscal();

    
//     bts_afi910_main();
//     /* Example that uses DMA to load RAMPGEN registers. */
//     // example_dma_ramp();
    
// #endif

// #ifdef EXAMPLE_WITH_TASKLISTS
//     /* Example using tasklists to implement periodic calibration */
//     example_tasklist();
// #endif
//     host_pheriph_deinit(host_dev_p);
//     return 0;
// }

int main()
{
    host_dev_p = &host_dev;

    pthread_t p_thread[2];
    int thr_id;
    int status;
    int test;
    struct mq_attr attr;
    attr.mq_flags = 1;
    attr.mq_maxmsg = 1;
    attr.mq_msgsize = 1;
    

    mqd = mq_open("/afi910_queue", O_RDWR | O_CREAT, 0666, &attr);
    printf("MQD return : %d(%d)\n",mqd,errno);



    thr_id = pthread_create(&p_thread[0], NULL, bts_afi910_modulation, NULL);
    if(thr_id <0)
    {
        printf("bts_afi910_modulation Thread Create FAIL...\n");
        exit(0);
    }

    thr_id = pthread_create(&p_thread[1], NULL, bts_afi910_get_data, NULL);
    if(thr_id <0)
    {
        printf("bts_afi910_get_data Thread Create FAIL...\n");
        exit(0);
    }

    pthread_join(p_thread[0], (void **)&status);
    pthread_join(p_thread[1], (void **)&status);
}