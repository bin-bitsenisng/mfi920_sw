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

#include "adi_dmdriver.h"
#include "bts_application.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <mqueue.h>
#include <unistd.h>
#include <errno.h>

/***********************************************
* Example using DMA to configure ramp gen registers.
************************************************
*/

/* The alternative method of configuring ramp gen
 * registers has been deprecated. This example
 * should be contrasted with example_tasklist.c which
 * uses tasklists intead of adi_dm_PeriodicCalibration.
 */

extern uint8_t example_syscal_rx[ADI_DM_NUM_DIGIMMIC][ADI_DM_SYSCAL_RX_SIZE];
extern uint8_t example_syscal_tx[NUM_BURST_PROFILES][ADI_DM_NUM_DIGIMMIC][ADI_DM_SYSCAL_RX_SIZE];
extern mqd_t mqd; 

void *bts_afi910_modulation(void *)
{
    bts_afi910_config_t afi910_configs;
    adi_dm_err_t res;
    int ii;
    uint32_t addr, val;
    int t_val;
    unsigned int prio;
    int rettt;


    /***********************************
    * Part 1: initialize the device
    ************************************
    */
    /* This part is split out into a separate example
     * because it is common to all three examples.
     */

    /* 1a: Common initialization */
    bts_afi910_init(&afi910_configs);

#if BIST == 1
    /* 1b: Load system calibration data from on board non-volatile memory
     */
    /* This example assumes that the example_syscal_rx, example_syscal_tx variables
     * contain a copy of the t0 measurement data obtained during system calibration.
     * as can be seen in the example_syscal.c file.
     * This data is board specific and should come from non-volatile memory on the board
     * written during system calibration whe the board comes off the production line.
     * For the purposes of these examples the variables written by the example_syscal example
     * are used, assuming example_syscal has run before this example.
     */
    /* Copy t0 data from variables set by example_syscal */
    memcpy(afi910_configs.syscalrx, example_syscal_rx, sizeof(afi910_configs.syscalrx));
    for (ii = 0; ii < afi910_configs.num_burst_profiles; ii++) {
        memcpy(afi910_configs.bp[ii].syscaltx, example_syscal_tx[ii], sizeof(afi910_configs.bp[ii].syscaltx));
    }

    /* 1c: Write system calibration  data to the devices.
     * Rx t0 data only needs to be written hre.
     * Tx t0 data is written each time the burst profile changes.
     */
    res = adi_dm_WriteSysCalRx(afi910_configs.syscalrx);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_WriteSysCalRx", res, __FILE__, __LINE__);
    }

    res = adi_dm_WriteSysCalTx(afi910_configs.bp[afi910_configs.cur_bp_idx].syscaltx);
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_WriteSysCalTx", res, __FILE__, __LINE__);
    }
#endif


    /***********************************************
    * Part 2: Loop triggering bursts
    ***********************************************
    */
    /* The measurement loop is in another example. */
    bts_afi910_burst_loop(&afi910_configs);


    /***********************************************
    * Part 3: Finalization
    ***********************************************
    */
    /* Power down the device. */
    res = adi_dm_PowerDown();
    if (res != ADI_DM_SUCCESS) {
        platform_error("adi_dm_PowerDown", res, __FILE__, __LINE__);
    }

    /* Release any resource used by the diver. */
    adi_dm_Log("---> Exiting example_dma_ramp");
    adi_dm_FiniDriver();
}


void *bts_afi910_get_data(void *)
{
    int qval = 2;
    int rettt;
    int frame_cnt = 0;
    
    while(1)
    {
        rettt = mq_receive(mqd, (char *)&qval, 1, NULL);
        printf("=== %d frame save done.\n",frame_cnt);
        platform_save_data(frame_cnt++);
    }

}