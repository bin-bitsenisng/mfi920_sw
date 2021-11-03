/* ramp_multi.c
 * Copyright (c) 2018-2020 Analog Devices Inc. All rights reserved
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

/** @file
 * Support constructing a burst from many different ramp profiles using DMA.
 *
 * The supported scheme uses a single DMA channel in scatter-gather mode
 * to load every RAMPGEN register on each ramp.
 */

#include "../include/adi_dmdriver.h"
#include "../src/localdefs.h"
#include "../src/adar690x_regs.h"
#include "bts_application.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define UDMA_CTRL_CFG_DSTINC_WORD 0x80000000
#define UDMA_CTRL_CFG_DSTINC_NOINCR 0xC0000000
#define UDMA_CTRL_CFG_SRCINC_WORD 0x08000000
#define UDMA_CTRL_CFG_SRCINC_NOINCR 0x0C000000
#define UDMA_CTRL_CFG_SRC_SIZE_WORD 0x02000000
#define UDMA_CTRL_CFG_R_POWER_X1 (0 << 14)
#define UDMA_CTRL_CFG_R_POWER_X4 (2 << 14)
#define UDMA_CTRL_CFG_R_POWER_X8 (3 << 14)
#define UDMA_CTRL_CFG_R_POWER_X16 (4 << 14)
#define UDMA_CTRL_CFG_R_POWER_X32 (5 << 14)
#define UDMA_CTRL_CFG_TRANSFERS(x) (((x)-1)<<4)
#define UDMA_CTRL_CFG_CYC_CTRL_BASIC 0x00000001
#define UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_PRI  0x00000004
#define UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_ALT  0x00000005
#define UDMA_CTRL_CFG_CYC_CTRL_PERI_SCATTER_GATHER_PRI  0x00000006
#define UDMA_CTRL_CFG_CYC_CTRL_PERI_SCATTER_GATHER_ALT  0x00000007

typedef struct {
    uint32_t src_addr;
    uint32_t dest_addr;
    uint32_t udma_ch_cfg;
    uint32_t reserved;
} bts_afi910_rfic_udma_ch_set_t;

static void put_word(uint32_t * addr, uint32_t value);
static adi_dm_err_t put_flush(void);
static void put_init(adi_dm_num_t);
static void put_ramp_profile(uint32_t * addr, adi_dm_ramp_profile_t * ramp);
static adi_dm_err_t overwite_slave_ramp_profiles(uint32_t * addr, adi_dm_ramp_profile_t * ramp);
static adi_dm_err_t initialize_dma_chan(uint32_t channel_no, uint32_t fldval);


// temp test functions...
void test_rfic_udma_test0(void);
void test_rfic_udma_test1(void);
void test_rfic_udma_test2(void);
void test_rfic_udma_test3(void);
void bts_rfic_udma_init(void);
void bts_rfic_udma_scan_all(int select_device, int final_addr);
void bts_rfic_udma_set(bts_afi910_config_t * p);
adi_dm_err_t bts_rfic_udma_ch_put(int select_device, uint32_t* addr, bts_afi910_rfic_udma_ch_set_t ch_setting);

/*
 * DMA is used to load the RAMPGEN registers during the burst. Each set of
 * values to be loaded is stored in memory in a structure called a Ramp Profile.
 * The DMA scheme loads a ramp profile to the RAMPGEN block as the previous
 * ramp is transmitted.
 *
 * Loading the full set of RAMPGEN registers, is optionally followed by a
 * load of the RAMP_GEN_TX register. This enables better use of memory
 * when the only difference between ramp profiles is the tx or phase pattern.
 *
 * A single DMA channel is used to load Ramp profiles to the RAMPGEN registers.
 * This channel is configured in memory scatter-gather mode and triggered by the
 * rg_dma_en signal. When triggered, the first task loads the RAMPGEN registers
 * with their new values and the second task loads a new value into the primary
 * channel control data structure for the same channel. This new value sets the
 * channel up to load the next ramp. The tasks associated with the final ramp
 * profile sets up the channel control for the first ramp so repetition can
 * continue indefinitely.
 *
 * The optional load to the RAMP_GEN_TX is managed by an additional two channels.
 * One is configured in Basic mode and triggered by the dma_done signal of the
 * above channel. Each time this channel is triggered one word is written to
 * RAMP_GEN_TX and the source pointer incremented. The second additional channel
 * resets the first and is triggered by the first channel's dma_done signal
 * once the last tx_overlay word has been transferred. The reset channel is configured
 * in memory scatter gather mode, with the first task overwriting the primary channel
 * control data for the first channel and the second task overwritting its own primary
 * channel control data.
 *
 * One last DMA channel is used to switch between burst profiles. This is triggered
 * by software and is configured in memory scatter-gather mode. The first task loads
 * the primary channel control data for all the other channels, the second enables
 * or disables the optional channels that load RAMP_GEN_TX, and the third task
 * reloads the primary channel control data for this channel.
 *
 * In summary, the extended scheme, with assigned channel numbers looks like this.
 *
 * * Channel 0, loads D, L, M, S-Mode Profiles
 *   * Triggered by software
 *   * Peripheral scatter-gather:
 *     * task 0: loads D-Mode Profiles
 *     * task 1: loads L-Mode Profiles
 *     * task 2: loads M-Mode Profiles
 *     * task 3: loads S-Mode Profiles
 * * Channel 1, changes D, L, M, S-Mode MIPI VC-ID
 *   * Triggered by software
 *   * Peripheral scatter-gather:
 *     * task 0: Changes D-Mode VC-ID 0
 *     * task 1: Changes L-Mode VC-ID 1 
 *     * task 2: Changes M-Mode VC-ID 1
 *     * task 3: Changes S-Mode VC-ID 1
 * * Channel 2, changes RAMP_GEN_TX
 *   * Triggered by dma_done[1]
 *   * Basic mode
 *     * Load 1 word to RAMP_GEN_TX, arbitrate
 * * Channel 3, resets channel 0, 1, 2
 *   * Triggered by dma_done[2]
 *   * Memory scatter-gather:
 *     * task 0: loads channel 0, 1, 2 primary channel control
 */

/*
 * Initialise memory resident data used to drive the DMA
 */
// you can find the original code of this dma_setup function in 'ramp_multi.c'
adi_dm_err_t bts_afi910_rfic_dma_setup(const adi_dm_burst_profile_t * p, uint32_t * dma_mem_limit, uint32_t * bpid)
{
    adi_dm_err_t res;

    printf("num_seq_in_burst : %d, bpid : %d\n",p->num_seq_in_burst, *bpid);
    if (p->num_seq_in_burst < 1) {
        return ADI_DM_PARAMETER_ERROR;
    }
    if (bpid == NULL) {
        return ADI_DM_PARAMETER_ERROR;
    }

    /*
     * As discussed above the substantive part of the data structure
     * is a sequence of ramp profiles which may be repeated.
     */
    int num_ramp_profiles = p->num_ramps_in_seq;
    int tx_overlay_words = p->tx_overlay_len;

    const uint32_t word_size = DMA_WORD_SIZE;
    const uint32_t chan_ctrl_size = DMA_CHAN_CTRL_SIZE;
    const uint32_t tasks_size = 2 * DMA_CHAN_CTRL_SIZE;
    const uint32_t ramp_profile_size = DMA_RAMP_PROFILE_SIZE;

    if (*dma_mem_limit == 0) {
        *dma_mem_limit = DMA_MEMORY_START;
    }
    /*
     * Calculate addresses with the channel control data structure
     * pointed at by the dma base pointer. We just use channel 0 in
     * scatter gather mode.
     */
    uint32_t prim_chan_ctrl = DMA_RAMPGEN_CHAN_SRC_PTR + chan_ctrl_size;        // uDMA CH1
    uint32_t last_word_prim_chan_ctrl = prim_chan_ctrl + chan_ctrl_size - word_size;
    uint32_t last_word_alt_chan_ctrl = last_word_prim_chan_ctrl + 0x100;
    
    uint32_t prim_ch0_ctrl = DMA_RAMPGEN_CHAN_SRC_PTR;                          // uDMA CH0
    uint32_t last_word_prim_ch0_ctrl = prim_ch0_ctrl + chan_ctrl_size - word_size;
    uint32_t last_word_alt_ch0_ctrl = last_word_prim_ch0_ctrl + 0x100;
    uint32_t prim_ch2_ctrl = DMA_RAMPGEN_CHAN_SRC_PTR + (2 * chan_ctrl_size);   // uDMA CH2
    uint32_t last_word_prim_ch2_ctrl = prim_ch2_ctrl + chan_ctrl_size - word_size;
    uint32_t prim_ch3_ctrl = DMA_RAMPGEN_CHAN_SRC_PTR + (3 * chan_ctrl_size);   // uDMA CH3
    uint32_t last_word_prim_ch3_ctrl = prim_ch3_ctrl + chan_ctrl_size - word_size;
    uint32_t last_word_alt_ch3_ctrl = last_word_prim_ch3_ctrl + 0x100;
    /*
     * Calculate addresses in the burst profile area for this burst profile
     */
    uint32_t burst_profile = *dma_mem_limit;
    uint32_t tasks = burst_profile;
    uint32_t last_word_first_tasks = tasks + tasks_size - word_size;
    uint32_t golden_prim_chan_ctrl = tasks + num_ramp_profiles * tasks_size;
    uint32_t ramp_profiles = golden_prim_chan_ctrl + num_ramp_profiles * chan_ctrl_size;
    
    uint32_t last_word_first_golden_prim_chan_ctrl = golden_prim_chan_ctrl + chan_ctrl_size - word_size;
    uint32_t golden_prim_ch0_ctrl = ramp_profiles + num_ramp_profiles * ramp_profile_size;

    uint32_t ch23_mask = golden_prim_ch0_ctrl + chan_ctrl_size;
    uint32_t last_word_golden_prim_ch0_ctrl = ch23_mask - word_size;
    uint32_t ch0_tasks = ch23_mask + word_size;
    uint32_t end_ch0_tasks = ch0_tasks + 3 * chan_ctrl_size;
    uint32_t end_of_burst_profile = end_ch0_tasks;

    uint32_t golden_prim_ch123_ctrl = end_of_burst_profile;
    uint32_t ch3_tasks = end_of_burst_profile;
    uint32_t tx_overlay_data = end_of_burst_profile;

    uint32_t last_word_golden_ch123_ctrl = last_word_first_golden_prim_chan_ctrl;
    uint32_t last_word_prim_ch123_ctrl = last_word_prim_chan_ctrl;
    uint32_t golden_ch123_xfers = chan_ctrl_size / word_size;
    printf("tx_overlay_words : 0x%X, \n", tx_overlay_words);
    if (tx_overlay_words > 0) {
        /* add a task to ch0 to init two more channels */
        golden_prim_ch123_ctrl = end_ch0_tasks;
        ch3_tasks = golden_prim_ch123_ctrl + 3 * chan_ctrl_size;
        tx_overlay_data = ch3_tasks + 2 * chan_ctrl_size;
        end_of_burst_profile = tx_overlay_data + tx_overlay_words * word_size;
        last_word_golden_ch123_ctrl = ch3_tasks - word_size;
        last_word_prim_ch123_ctrl = last_word_prim_ch3_ctrl;
        golden_ch123_xfers = (3 * chan_ctrl_size) / word_size;
    }

    uint32_t last_word_tx_overlay_data = end_of_burst_profile - word_size;
    uint32_t last_word_ch0_tasks = end_ch0_tasks - word_size;
    uint32_t last_word_ch3_tasks = tx_overlay_data - word_size;
    uint32_t last_word_golden_prim_ch2_ctrl = golden_prim_ch123_ctrl + (2 * chan_ctrl_size) - word_size;
    uint32_t last_word_golden_prim_ch3_ctrl = golden_prim_ch123_ctrl + (3 * chan_ctrl_size) - word_size;
    comment("-->> Entering function adi_dm_BurstProfileSetup");

    /*
     * Check data fits and record that space is in use.
     */
    if (end_of_burst_profile > DMA_MEMORY_START + DMA_MEMORY_SIZE) {
        comment("ERROR: not enough space for burst profile");
        return ADI_DM_PARAMETER_ERROR;
    }
    *dma_mem_limit = end_of_burst_profile;

    /*
     * Initialize the burst profile data structure
     */
    uint32_t loc = burst_profile;
    put_init(ADI_DM_ALL_DIGIMMICS);
    /*
     * First section is task data structures for scatter gather
     */
    printf("Loc : 0x%X\n",loc);
    assert(loc == tasks);
    for (int i = 0; i < num_ramp_profiles; i++) {
        uint32_t this_ramp = i;
        uint32_t next_ramp = (i + 1) % num_ramp_profiles;
        uint32_t last_word_of_ramp_profile = ramp_profiles + (this_ramp + 1) * ramp_profile_size - word_size;
        uint32_t last_word_next_golden_prim_chan_ctrl = golden_prim_chan_ctrl + (next_ramp + 1) * chan_ctrl_size - word_size;
        /* task0: transfer profile to rampgen */
        put_word(&loc, last_word_of_ramp_profile);      /* src_ptr */
        put_word(&loc, REG_RAMPGEN_RAMP_GEN_PHASE_MOD); /* dst_ptr = last word of rampgen */
        put_word(&loc, UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_ALT | UDMA_CTRL_CFG_DSTINC_WORD        /* increment dst_ptr */
                 | UDMA_CTRL_CFG_SRCINC_WORD    /* increment src_ptr */
                 | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                 | UDMA_CTRL_CFG_R_POWER_X16    /* arbitrate after 16 transfers */
                 | UDMA_CTRL_CFG_TRANSFERS(9)); /* total transfers */
        put_word(&loc, 0);
        /* task1: transfer primary channel control for next ramp */
        put_word(&loc, last_word_next_golden_prim_chan_ctrl);   /* src_ptr */
        put_word(&loc, last_word_prim_chan_ctrl);       /* dest_ptr */
        put_word(&loc, UDMA_CTRL_CFG_CYC_CTRL_BASIC | UDMA_CTRL_CFG_DSTINC_WORD /* increment dst_ptr */
                 | UDMA_CTRL_CFG_SRCINC_WORD    /* increment src_ptr */
                 | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                 | UDMA_CTRL_CFG_R_POWER_X4     /* arbitrate after 4 transfers */
                 | UDMA_CTRL_CFG_TRANSFERS(4)); /* total transfers */
        put_word(&loc, 0);
    }
    printf("Loc : 0x%X\n",loc);
    /*
     * Second section is golden copies of primary channel control data
     */
    assert(loc == golden_prim_chan_ctrl);
    for (int i = 0; i < num_ramp_profiles; i++) {
        uint32_t this_ramp = i;
        uint32_t last_word_of_tasks = tasks + (this_ramp + 1) * tasks_size - word_size;

        /* golden primary channel control structure */
        put_word(&loc, last_word_of_tasks);     /* src_ptr */
        put_word(&loc, last_word_alt_chan_ctrl);        /* dst_ptr */
        put_word(&loc, UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_PRI | UDMA_CTRL_CFG_DSTINC_WORD        /* increment dst_ptr */
                 | UDMA_CTRL_CFG_SRCINC_WORD    /* increment src_ptr */
                 | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                 | UDMA_CTRL_CFG_R_POWER_X4     /* arbitrate after 4 transfers */
                 | UDMA_CTRL_CFG_TRANSFERS(8)); /* total transfers */
        put_word(&loc, 0);
    }
    printf("Loc : 0x%X\n",loc);
    /*
     * Third section is ramp profiles
     */
    assert(loc == ramp_profiles);
    for (int i = 0; i < num_ramp_profiles; i++) {
        put_ramp_profile(&loc, &p->ramp_profile[i]);
    }
    printf("Loc : 0x%X\n",loc);
    /*
     * Control for ch 0
     */
    /* golden ch 0 control */
    assert(loc == golden_prim_ch0_ctrl);
    put_word(&loc, last_word_ch0_tasks);        /* src_ptr */
    put_word(&loc, last_word_alt_ch0_ctrl);     /* dst_ptr */
    put_word(&loc, UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_PRI | UDMA_CTRL_CFG_DSTINC_WORD    /* increment dst_ptr */
             | UDMA_CTRL_CFG_SRCINC_WORD        /* increment src_ptr */
             | UDMA_CTRL_CFG_SRC_SIZE_WORD      /* transfer 4 bytes at a time */
             | UDMA_CTRL_CFG_R_POWER_X4 /* arbitrate after 4 transfers */
             | UDMA_CTRL_CFG_TRANSFERS(12));    /* total transfers (3 tasks) */
    put_word(&loc, 0);
    printf("Loc : 0x%X\n",loc);
    /*
     * A mask to disable channels 2 and 3
     */
    assert(loc == ch23_mask);
    put_word(&loc, 0xc);

    assert(loc == ch0_tasks);
    /* task 0 loads primary control for channels 1,2 & 3 */
    put_word(&loc, last_word_golden_ch123_ctrl);        /* src_ptr */
    put_word(&loc, last_word_prim_ch123_ctrl);  /* dst_ptr */
    put_word(&loc, UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_ALT | UDMA_CTRL_CFG_DSTINC_WORD    /* increment dst_ptr */
             | UDMA_CTRL_CFG_SRCINC_WORD        /* increment src_ptr */
             | UDMA_CTRL_CFG_SRC_SIZE_WORD      /* transfer 4 bytes at a time */
             | UDMA_CTRL_CFG_R_POWER_X16        /* arbitrate after 16 transfers */
             | UDMA_CTRL_CFG_TRANSFERS(golden_ch123_xfers));    /* total transfers */
    put_word(&loc, 0);
    /* task 1 enables channels */
    put_word(&loc, ch23_mask);  /* src_ptr */
    if (tx_overlay_words > 0) {
        /* unmask ch2 and 3 */
        put_word(&loc, REG_UDMA_RMSK_CLR);      /* dst_ptr */
    } else {
        /* mask ch2 and 3 */
        put_word(&loc, REG_UDMA_RMSK_SET);      /* dst_ptr */
    }
    put_word(&loc, UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_ALT | UDMA_CTRL_CFG_DSTINC_NOINCR  /* don't increment dst_ptr */
             | UDMA_CTRL_CFG_SRCINC_NOINCR      /* don't increment src_ptr */
             | UDMA_CTRL_CFG_SRC_SIZE_WORD      /* transfer 4 bytes at a time */
             | UDMA_CTRL_CFG_R_POWER_X1 /* arbitrate after 4 transfers */
             | UDMA_CTRL_CFG_TRANSFERS(1));     /* total transfers */
    put_word(&loc, 0);
    /* task 2 reloads the primary channel */
    put_word(&loc, last_word_golden_prim_ch0_ctrl);     /* src_ptr */
    put_word(&loc, last_word_prim_ch0_ctrl);    /* dest_ptr */
    put_word(&loc, UDMA_CTRL_CFG_CYC_CTRL_BASIC | UDMA_CTRL_CFG_DSTINC_WORD     /* increment dst_ptr */
             | UDMA_CTRL_CFG_SRCINC_WORD        /* increment src_ptr */
             | UDMA_CTRL_CFG_SRC_SIZE_WORD      /* transfer 4 bytes at a time */
             | UDMA_CTRL_CFG_R_POWER_X4 /* arbitrate after 4 transfers */
             | UDMA_CTRL_CFG_TRANSFERS(4));     /* total transfers */
    put_word(&loc, 0);
    printf("Loc : 0x%X\n",loc);
    if (tx_overlay_words > 0) {
        assert(loc == golden_prim_ch123_ctrl);

        /* golden ch 1 control - copy of first task that loads a ramp profile */
        put_word(&loc, last_word_first_tasks);  /* src_ptr */
        put_word(&loc, last_word_alt_chan_ctrl);        /* dst_ptr */
        put_word(&loc, UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_PRI | UDMA_CTRL_CFG_DSTINC_WORD        /* increment dst_ptr */
                 | UDMA_CTRL_CFG_SRCINC_WORD    /* increment src_ptr */
                 | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                 | UDMA_CTRL_CFG_R_POWER_X4     /* arbitrate after 4 transfers */
                 | UDMA_CTRL_CFG_TRANSFERS(8)); /* total transfers (2 tasks) */
        put_word(&loc, 0);

        /* golden ch 2 control - loads RAMPGEN_TX register */
        put_word(&loc, last_word_tx_overlay_data);      /* src_ptr */
        put_word(&loc, REG_RAMPGEN_RAMP_GEN_TX);        /* dst_ptr */
        put_word(&loc, UDMA_CTRL_CFG_CYC_CTRL_BASIC | UDMA_CTRL_CFG_DSTINC_NOINCR       /* don't increment dst_ptr */
                 | UDMA_CTRL_CFG_SRCINC_WORD    /* increment src_ptr */
                 | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                 | UDMA_CTRL_CFG_R_POWER_X1     /* arbitrate after 1 transfers */
                 | UDMA_CTRL_CFG_TRANSFERS(tx_overlay_words));  /* total transfers (3 tasks) */
        put_word(&loc, 0);

        /* golden ch 3 control - reloads ch 2 */
        put_word(&loc, last_word_ch3_tasks);    /* src_ptr */
        put_word(&loc, last_word_alt_ch3_ctrl); /* dst_ptr */
        put_word(&loc, UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_PRI | UDMA_CTRL_CFG_DSTINC_WORD        /* increment dst_ptr */
                 | UDMA_CTRL_CFG_SRCINC_WORD    /* increment src_ptr */
                 | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                 | UDMA_CTRL_CFG_R_POWER_X4     /* arbitrate after 4 transfers */
                 | UDMA_CTRL_CFG_TRANSFERS(8)); /* total transfers (2 tasks) */
        put_word(&loc, 0);

        assert(loc == ch3_tasks);
        /* ch3, task 0 reloads prim_ch2_ctrl */
        put_word(&loc, last_word_golden_prim_ch2_ctrl); /* src_ptr */
        put_word(&loc, last_word_prim_ch2_ctrl);        /* dst_ptr */
        put_word(&loc, UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_ALT | UDMA_CTRL_CFG_DSTINC_WORD        /* increment dst_ptr */
                 | UDMA_CTRL_CFG_SRCINC_WORD    /* increment src_ptr */
                 | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                 | UDMA_CTRL_CFG_R_POWER_X4     /* arbitrate after 4 transfers */
                 | UDMA_CTRL_CFG_TRANSFERS(4)); /* total transfers */
        put_word(&loc, 0);
        /* task 2 reloads the primary channel control for self */
        put_word(&loc, last_word_golden_prim_ch3_ctrl); /* src_ptr */
        put_word(&loc, last_word_prim_ch3_ctrl);        /* dest_ptr */
        put_word(&loc, UDMA_CTRL_CFG_CYC_CTRL_BASIC | UDMA_CTRL_CFG_DSTINC_WORD /* increment dst_ptr */
                 | UDMA_CTRL_CFG_SRCINC_WORD    /* increment src_ptr */
                 | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                 | UDMA_CTRL_CFG_R_POWER_X4     /* arbitrate after 4 transfers */
                 | UDMA_CTRL_CFG_TRANSFERS(4)); /* total transfers */
        put_word(&loc, 0);
        printf("Loc : 0x%X\n",loc);
    }

    res = put_flush();
    if (res != ADI_DM_SUCCESS)
        return res;
    assert(tx_overlay_words > 0 || loc == *dma_mem_limit);

    if (adi_dm_active_digimmics > 0) {
        /*
         * For a cascaded configuration now overwrite on individual
         * slaves those parts of the ramp profile that differ from master.
         */
        loc = ramp_profiles;
        for (int i = 0; i < num_ramp_profiles; i++) {
            res = overwite_slave_ramp_profiles(&loc, &p->ramp_profile[i]);
            if (res != ADI_DM_SUCCESS)
                return res;
        }
        assert(loc == golden_prim_ch0_ctrl);
    }

    /* tx_overlay data is written seperately for each device */
    if (tx_overlay_words > 0) {
        for (adi_dm_num_t dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            loc = tx_overlay_data;
            put_init(dm_num);
            for (int i = 0; i < tx_overlay_words; i++) {
                uint32_t tx = (p->tx_overlay[dm_num][i].pa0_phase << BITP_RAMPGEN_RAMP_GEN_TX_PA0_PHASE)
                    | (p->tx_overlay[dm_num][i].pa1_phase << BITP_RAMPGEN_RAMP_GEN_TX_PA1_PHASE)
                    | (p->tx_overlay[dm_num][i].pa2_phase << BITP_RAMPGEN_RAMP_GEN_TX_PA2_PHASE)
                    | (p->tx_overlay[dm_num][i].tx_pattern << BITP_RAMPGEN_RAMP_GEN_TX_TX_PATTERN)
                    | (p->tx_overlay[dm_num][i].phase_step << BITP_RAMPGEN_RAMP_GEN_TX_PHASE_STEP)
                    | (p->tx_overlay[dm_num][i].ramp_stat_bit_0 << BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_0)
                    | (p->tx_overlay[dm_num][i].ramp_stat_bit_1 << BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_1)
                    | (p->tx_overlay[dm_num][i].ramp_stat_bit_2 << BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_2);
                put_word(&loc, tx);
            }
            res = put_flush();
            if (res != ADI_DM_SUCCESS)
                return res;
            assert(loc == end_of_burst_profile);
        }
    }
    *bpid = last_word_ch0_tasks;

    /* assumption made in adi_dm_3_0_ModifyRampProfile */
    assert(ramp_profile_size == DMA_RAMP_PROFILE_SIZE);

    comment("-->> Exiting function adi_dm_BurstProfileSetup");
    return ADI_DM_SUCCESS;
}

adi_dm_err_t bts_afi910_DmaRampSetup(const adi_dm_dma_ramp_setup_t * p)
{
    adi_dm_err_t res;
    const uint32_t word_size = DMA_WORD_SIZE;
    const uint32_t chan_ctrl_size = DMA_CHAN_CTRL_SIZE;
    uint32_t prim_chan_ctrl = DMA_RAMPGEN_CHAN_SRC_PTR;
    uint32_t xfers = 12;
    uint32_t last_word_prim_chan_ctrl = prim_chan_ctrl + chan_ctrl_size - word_size;
    uint32_t last_word_alt_chan_ctrl = last_word_prim_chan_ctrl + 0x100;

    comment("-->> Entering function bts_afi910_DmaRampSetup");

    res = bts_afi910_ramp_config(&p->ramp_config, NULL);
    if (res != ADI_DM_SUCCESS) {
        return res;
    }
    /*
     * Initialize primary channel control data in scatter gather mode.
     */
    uint32_t loc = prim_chan_ctrl;
    put_init(ADI_DM_ALL_DIGIMMICS);
    put_word(&loc, p->bpid);    /* src_ptr */
    put_word(&loc, last_word_alt_chan_ctrl);    /* dst_ptr */
    put_word(&loc, UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_PRI | UDMA_CTRL_CFG_DSTINC_WORD    /* increment dst_ptr */
             | UDMA_CTRL_CFG_SRCINC_WORD        /* increment src_ptr */
             | UDMA_CTRL_CFG_SRC_SIZE_WORD      /* transfer 4 bytes at a time */
             | UDMA_CTRL_CFG_R_POWER_X4 /* arbitrate after 4 transfers */
             | UDMA_CTRL_CFG_TRANSFERS(xfers)); /* total transfers */
    put_word(&loc, 0);
    res = put_flush();
    if (res != ADI_DM_SUCCESS)
        return res;

    res = initialize_dma_chan(DMA_RAMPGEN_CHAN_NO, 11 /* a chan we never enable */ );
    if (res != ADI_DM_SUCCESS)
        return res;
    res = initialize_dma_chan(DMA_RAMPGEN_CHAN_NO + 1, DMA_RAMPGEN_CHAN_NO + 1);        /* triggered by rg_dma_en */
    if (res != ADI_DM_SUCCESS)
        return res;
    res = initialize_dma_chan(DMA_RAMPGEN_CHAN_NO + 2, DMA_RAMPGEN_CHAN_NO + 1);        /* triggered by dma_done[1] */
    if (res != ADI_DM_SUCCESS)
        return res;
    res = initialize_dma_chan(DMA_RAMPGEN_CHAN_NO + 3, DMA_RAMPGEN_CHAN_NO + 2);        /* triggered by dma_done[2] */
    /* Issue software request to load primary channel control and then first ramp profile */
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 3 << DMA_RAMPGEN_CHAN_NO);
    if (res != ADI_DM_SUCCESS)
        return res;

    if (adi_dm_enable_trigger_pin_on_program) {
        /* BIST49 explicit control of when external trigger is allowed
         * for compatible with past APIs the trig pin is enabled as soon
         * as the ramp is programmed.
         */
        comment("ADI_ADAR690x_FW_EXT_TRIG_EN");
        res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_EXT_TRIG_EN);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    comment("-->> Exiting function bts_afi910_DmaRampSetup");

    return ADI_DM_SUCCESS;
}

/** Store a Ramp Profile in all DigiMMICs' memories */
static void put_ramp_profile(uint32_t * addr, adi_dm_ramp_profile_t * ramp)
{
    /*
     * A Ramp Profile is just a memory resident copy of the RAMPGEN registers
     * padded to 9 words.
     */
    uint32_t del01 = (ramp->del_0 << BITP_RAMPGEN_RAMP_GEN_DEL01_DEL_0)
        | ((ramp->del_1 & 0x3FF) << BITP_RAMPGEN_RAMP_GEN_DEL01_DEL_1);
    uint32_t del12 = ((ramp->del_1 >> 10) & 0x3FF) << BITP_RAMPGEN_RAMP_GEN_DEL12_DEL_1 | (ramp->del_2 << BITP_RAMPGEN_RAMP_GEN_DEL12_DEL_2);
    uint32_t step1 = ramp->ramp_steps_1;
    uint32_t step0 = ramp->ramp_steps_0;
    uint32_t dev0 = ramp->ramp_dev_0;
    uint32_t dev1 = ramp->ramp_dev_1;
    uint32_t tx = (ramp->dm[ADI_DM_MASTER].pa0_phase << BITP_RAMPGEN_RAMP_GEN_TX_PA0_PHASE)
        | (ramp->dm[ADI_DM_MASTER].pa1_phase << BITP_RAMPGEN_RAMP_GEN_TX_PA1_PHASE)
        | (ramp->dm[ADI_DM_MASTER].pa2_phase << BITP_RAMPGEN_RAMP_GEN_TX_PA2_PHASE)
        | (ramp->dm[ADI_DM_MASTER].tx_pattern << BITP_RAMPGEN_RAMP_GEN_TX_TX_PATTERN)
        | (ramp->dm[ADI_DM_MASTER].phase_step << BITP_RAMPGEN_RAMP_GEN_TX_PHASE_STEP)
        | (ramp->dm[ADI_DM_MASTER].ramp_stat_bit_0 << BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_0)
        | (ramp->dm[ADI_DM_MASTER].ramp_stat_bit_1 << BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_1)
        | (ramp->dm[ADI_DM_MASTER].ramp_stat_bit_2 << BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_2);
    uint32_t afecnt = (ramp->afe_start_off_time << BITP_RAMPGEN_RAMP_GEN_AFECNT_AFE_START_OFF_TIME)
        | (ramp->afe_ramp_time << BITP_RAMPGEN_RAMP_GEN_AFECNT_AFE_RAMP_TIME);
    uint32_t phase_mod = (ramp->dm[ADI_DM_MASTER].pa2_phase_dev << BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA2_PHASE_DEV)
        | (ramp->dm[ADI_DM_MASTER].pa1_phase_dev << BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA1_PHASE_DEV)
        | (ramp->dm[ADI_DM_MASTER].pa0_phase_dev << BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA0_PHASE_DEV)
        | (ramp->num_samples << BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_NUM_SAMPLES);
    put_word(addr, del01);
    put_word(addr, del12);
    put_word(addr, step1);
    put_word(addr, step0);
    put_word(addr, dev0);
    put_word(addr, dev1);
    put_word(addr, tx);
    put_word(addr, afecnt);
    put_word(addr, phase_mod);
}

/** Store those parts of each slave's ramp profile that differ from master */
static adi_dm_err_t overwite_slave_ramp_profiles(uint32_t * addr, adi_dm_ramp_profile_t * ramp)
{
    adi_dm_err_t res;
    uint32_t master_tx = (ramp->dm[ADI_DM_MASTER].pa0_phase << BITP_RAMPGEN_RAMP_GEN_TX_PA0_PHASE)
        | (ramp->dm[ADI_DM_MASTER].pa1_phase << BITP_RAMPGEN_RAMP_GEN_TX_PA1_PHASE)
        | (ramp->dm[ADI_DM_MASTER].pa2_phase << BITP_RAMPGEN_RAMP_GEN_TX_PA2_PHASE)
        | (ramp->dm[ADI_DM_MASTER].tx_pattern << BITP_RAMPGEN_RAMP_GEN_TX_TX_PATTERN)
        | (ramp->dm[ADI_DM_MASTER].phase_step << BITP_RAMPGEN_RAMP_GEN_TX_PHASE_STEP)
        | (ramp->dm[ADI_DM_MASTER].ramp_stat_bit_0 << BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_0)
        | (ramp->dm[ADI_DM_MASTER].ramp_stat_bit_1 << BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_1)
        | (ramp->dm[ADI_DM_MASTER].ramp_stat_bit_2 << BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_2);
    uint32_t master_phase_mod = (ramp->dm[ADI_DM_MASTER].pa2_phase_dev << BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA2_PHASE_DEV)
        | (ramp->dm[ADI_DM_MASTER].pa1_phase_dev << BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA1_PHASE_DEV)
        | (ramp->dm[ADI_DM_MASTER].pa0_phase_dev << BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA0_PHASE_DEV)
        | (ramp->num_samples << BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_NUM_SAMPLES);
    for (int dm_slave = ADI_DM_SLAVE1; dm_slave < adi_dm_active_digimmics; dm_slave++) {
        uint32_t slave_tx = (ramp->dm[dm_slave].pa0_phase << BITP_RAMPGEN_RAMP_GEN_TX_PA0_PHASE)
            | (ramp->dm[dm_slave].pa1_phase << BITP_RAMPGEN_RAMP_GEN_TX_PA1_PHASE)
            | (ramp->dm[dm_slave].pa2_phase << BITP_RAMPGEN_RAMP_GEN_TX_PA2_PHASE)
            | (ramp->dm[dm_slave].tx_pattern << BITP_RAMPGEN_RAMP_GEN_TX_TX_PATTERN)
            | (ramp->dm[dm_slave].phase_step << BITP_RAMPGEN_RAMP_GEN_TX_PHASE_STEP)
            | (ramp->dm[dm_slave].ramp_stat_bit_0 << BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_0)
            | (ramp->dm[dm_slave].ramp_stat_bit_1 << BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_1)
            | (ramp->dm[dm_slave].ramp_stat_bit_2 << BITP_RAMPGEN_RAMP_GEN_TX_RAMP_STAT_BIT_2);
        uint32_t slave_phase_mod = (ramp->dm[dm_slave].pa2_phase_dev << BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA2_PHASE_DEV)
            | (ramp->dm[dm_slave].pa1_phase_dev << BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA1_PHASE_DEV)
            | (ramp->dm[dm_slave].pa0_phase_dev << BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_PA0_PHASE_DEV)
            | (ramp->num_samples << BITP_RAMPGEN_RAMP_GEN_PHASE_MOD_NUM_SAMPLES);
        if (slave_tx != master_tx) {
            res = adi_dm_Write(dm_slave, *addr + (REG_RAMPGEN_RAMP_GEN_TX - REG_RAMPGEN_RAMP_GEN_DEL01), slave_tx);
            if (res != ADI_DM_SUCCESS)
                return res;
        }
        if (slave_phase_mod != master_phase_mod) {
            res = adi_dm_Write(dm_slave, *addr + (REG_RAMPGEN_RAMP_GEN_PHASE_MOD - REG_RAMPGEN_RAMP_GEN_DEL01), slave_phase_mod);
            if (res != ADI_DM_SUCCESS)
                return res;
        }
    }
    *addr += DMA_RAMP_PROFILE_SIZE;
    return ADI_DM_SUCCESS;
}

static uint32_t put_buf[16];
static uint32_t put_index = 0;
static uint32_t put_addr = 0;
static adi_dm_num_t put_dm_num;
static adi_dm_err_t put_res;

static void put_init(adi_dm_num_t dm_num)
{
    put_index = 0;
    put_addr = 0;
    put_dm_num = dm_num;
    put_res = ADI_DM_SUCCESS;
}

static adi_dm_err_t put_flush(void)
{
    if (put_res == ADI_DM_SUCCESS) {
        put_res = adi_dm_BlockWrite(put_dm_num, put_addr, put_index * 4, put_buf);
    }
    put_index = 0;
    put_addr = 0;
    return put_res;
}

static void put_word(uint32_t * addr, uint32_t value)
{
    uint32_t next_addr = put_addr + put_index * 4;
    if (put_index >= ARRAY_SIZE(put_buf) || (put_index > 0 && *addr != next_addr))
        (void) put_flush();
    if (put_index == 0)
        put_addr = *addr;

    // printf("put dm : %03d, put word : addr = 0x%08X, val = 0x%08X\n", put_dm_num, *addr, value);
    put_buf[put_index] = value;
    put_index += 1;
    *addr += 4;
    
}

static adi_dm_err_t initialize_dma_chan(uint32_t channel_no, uint32_t fldval)
{
    adi_dm_err_t res;

    comment("-->> Entering function initialize_dma_controller");

    printf("Enabling DMA channel %d for RAMP_GEN\n", channel_no);
    /* disable the channel in case it is enabled */
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_EN_CLR, 1 << channel_no);
    if (res != ADI_DM_SUCCESS)
        return res;
    /* set DMA trigger for channel to ramp_dma_en_sync */
    uint32_t regoff, bitoff;
    if (channel_no < 8) {
        regoff = 0;
        bitoff = 4 * channel_no;
    } else {
        regoff = REG_MISC_MISC_UDMA_REQ_MUX_SEL_1 - REG_MISC_MISC_UDMA_REQ_MUX_SEL_0;
        bitoff = 4 * (channel_no - 8);
    }
    res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_MISC_MISC_UDMA_REQ_MUX_SEL_0 + regoff, ~(0xf << bitoff), fldval << bitoff);
    if (res != ADI_DM_SUCCESS)
        return res;
    /* clear alt when done, so channel is ready to use primary descriptor */
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_CHNL_CLEAR_ALT_AT_DONE_SET, 1 << channel_no);
    if (res != ADI_DM_SUCCESS)
        return res;
    /* don't clear en when done, so channel is enabled for next trigger */
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_CHNL_DONT_CLEAR_EN_AT_DONE_SET, 1 << channel_no);
    if (res != ADI_DM_SUCCESS)
        return res;
    /* enable the channel */
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_EN_SET, 1 << channel_no);
    if (res != ADI_DM_SUCCESS)
        return res;

    comment("-->> Exiting function initialize_dma_controller");
    return ADI_DM_SUCCESS;
}



adi_dm_err_t bts_afi910_ramp_config(const adi_dm_ramp_config_t * p, const adi_dm_builtin_mimo_setup_t * builtin_mimo)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    uint32_t mask, bits;

    comment("--> Entering function bts_afi910_ramp_config");

    /* Set misc_filter_ctrl */
    mask = ~UINT32_C(0);
    bits = UINT32_C(0);
    mask &= ~BITM_MISC_MISC_FILTER_CTRL_FILTER_DECIM_RATIO;
    bits |= p->filter_decim_ratio << BITP_MISC_MISC_FILTER_CTRL_FILTER_DECIM_RATIO;
    res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_MISC_MISC_FILTER_CTRL, mask, bits);
    if (res != ADI_DM_SUCCESS)
        return res;

    /* Set misc_filter_ctrl_1 */
    mask = ~UINT32_C(0);
    bits = UINT32_C(0);
    mask &= ~BITM_MISC_MISC_FILTER_CTRL_1_FILTER_VALID_DELAY;
    bits |= p->filter_valid_delay << BITP_MISC_MISC_FILTER_CTRL_1_FILTER_VALID_DELAY;
    res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_MISC_MISC_FILTER_CTRL_1, mask, bits);
    if (res != ADI_DM_SUCCESS)
        return res;

    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        /* ramp_config3 */
        mask = ~UINT32_C(0);
        bits = UINT32_C(0);
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_EN;
        bits |= (p->pga_shunt_en << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_EN) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_EN;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_START_DEL;
        bits |= (p->pga_shunt_start_del << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_START_DEL) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_START_DEL;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_STOP_DEL;
        bits |= (p->pga_shunt_stop_del << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_STOP_DEL) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_STOP_DEL;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_VGA_GAUSS_DIS;
        bits |= (p->dm[dm_num].vga_gauss_dis << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_VGA_GAUSS_DIS) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_VGA_GAUSS_DIS;
        res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_RF_ADPLL_RFPLL_RAMP_CONFIG3, mask, bits);
        if (res != ADI_DM_SUCCESS)
            return res;

        /* ramp_config2 */
        mask = ~UINT32_C(0);
        bits = UINT32_C(0);
        if (builtin_mimo == NULL) {
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ;
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ_LEN;
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_MODE_EN;
        } else {
            uint32_t mimo_seq_val, mimo_seq_len;
            if (builtin_mimo->mimo_seq_len > 0) {
                mimo_seq_val = builtin_mimo->dm[dm_num].mimo_seq_val;
                mimo_seq_len = builtin_mimo->mimo_seq_len;
            } else {
                mimo_seq_val = builtin_mimo->ramp_profile.dm[dm_num].tx_pattern;
                mimo_seq_len = 1UL;
            }
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ;
            bits |= (mimo_seq_val << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ;
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ_LEN;
            bits |= (mimo_seq_len << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ_LEN) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ_LEN;
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_MODE_EN;
            bits |= BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_MODE_EN;
        }
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_RAMP_COUNT;
        bits |= (p->ramp_count << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG2_RAMP_COUNT) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_RAMP_COUNT;
        res = adi_dm_RMW(dm_num, REG_RF_ADPLL_RFPLL_RAMP_CONFIG2, mask, bits);
        if (res != ADI_DM_SUCCESS)
            return res;

        /* ramp_config1 */
        mask = ~UINT32_C(0);
        bits = UINT32_C(0);
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_ON_PATT;
        bits |= (p->dm[dm_num].vga_on_patt << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_ON_PATT) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_ON_PATT;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_DELAY_EN;
        bits |= (p->dm[dm_num].phase_delay_en << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_DELAY_EN) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_DELAY_EN;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_MOD_EN;
        bits |= (p->dm[dm_num].phase_mod_en << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_MOD_EN) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_MOD_EN;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA_OFF_TIME;
        bits |= (p->dm[dm_num].pa_off_time << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA_OFF_TIME) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA_OFF_TIME;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEPS;
        bits |= (p->dm[dm_num].vga_gain_steps << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEPS) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEPS;
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEP_DIV;
        bits |= (p->dm[dm_num].vga_gain_step_div << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEP_DIV) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEP_DIV;
        res = adi_dm_RMW(dm_num, REG_RF_ADPLL_RFPLL_RAMP_CONFIG1, mask, bits);
        if (res != ADI_DM_SUCCESS)
            return res;

        /* ramp_config0 */
        mask = ~UINT32_C(0);
        bits = UINT32_C(0);
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG0_VGA_SYNC_DATA_VALID;
        bits |= (p->dm[dm_num].vga_sync_data_valid << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG0_VGA_SYNC_DATA_VALID) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG0_VGA_SYNC_DATA_VALID;
        res = adi_dm_RMW(dm_num, REG_RF_ADPLL_RFPLL_RAMP_CONFIG0, mask, bits);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    comment("--> Leaving function bts_afi910_ramp_config");
    return ADI_DM_SUCCESS;
}

uint32_t dma_pri_addr[16];      // RFIC has 16 uDMA channel, 
uint32_t dma_alt_addr[16];
uint32_t dma_pri_end_ptr[16];
uint32_t dma_alt_end_ptr[16];

void test_rfic_udma_set_read(int device, int channel)
{
    uint32_t val[8] = {0,};
    printf("Contents of uDMA channel %d\n",channel);

    adi_dm_Read(device, dma_pri_addr[channel], &val[0]);
    adi_dm_Read(device, dma_pri_addr[channel]+0x00000004, &val[1]);
    adi_dm_Read(device, dma_pri_addr[channel]+0x00000008, &val[2]);
    adi_dm_Read(device, dma_pri_addr[channel]+0x0000000C, &val[3]);
    adi_dm_Read(device, dma_alt_addr[channel], &val[4]);
    adi_dm_Read(device, dma_alt_addr[channel]+0x00000004, &val[5]);
    adi_dm_Read(device, dma_alt_addr[channel]+0x00000008, &val[6]);
    adi_dm_Read(device, dma_alt_addr[channel]+0x0000000C, &val[7]);
    printf("Device : %d => PRI. SRC_PTR  : 0x%08X\n", device, val[0]);
    printf("Device : %d => PRI. DEST_PTR : 0x%08X\n", device, val[1]);
    printf("Device : %d => PRI. UDMA_CFG : 0x%08X\n", device, val[2]);
    printf("Device : %d => PRI. RESERVED : 0x%08X\n", device, val[3]);
    printf("Device : %d => ALT. SRC_PTR  : 0x%08X\n", device, val[4]);
    printf("Device : %d => ALT. DEST_PTR : 0x%08X\n", device, val[5]);
    printf("Device : %d => ALT. UDMA_CFG : 0x%08X\n", device, val[6]);
    printf("Device : %d => ALT. RESERVED : 0x%08X\n", device, val[7]);
}



void bts_rfic_read_ramp_gen_reg(int chan)
{
    uint32_t temp_addr, temp_val;

    temp_addr = 0xF0020200;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RAMP_GEN_DEL01  is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RAMP_GEN_DEL12  is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RAMP_GEN_STEP1  is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RAMP_GEN_STEP0  is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RAMP_GEN_DEV0   is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RAMP_GEN_DEV1   is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RAMP_GEN_TX     is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RAMP_GEN_AFECNT is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RAMP_GEN_PH_MOD is : 0x%08X\n",chan ,temp_val);

}
void bts_rfic_read_rfpll_reg(int chan)
{
    uint32_t temp_addr, temp_val;

    temp_addr = 0xF0020058;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RFPLL_RAMP_CONFIG0     is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RFPLL_RAMP_CONFIG1     is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RFPLL_RAMP_CONFIG2     is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RFPLL_RAMP_CONFIG3     is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RFPLL_RAMP_CONFIG4     is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RFPLL_RAMP_CONFIG6     is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RFPLL_RAMP_CONFIG7     is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RFPLL_RAMP_CONFIG8     is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RFPLL_STAT             is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RFPLL_FAULT_STAT       is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register RFPLL_RAMP_FAULT_STAT  is : 0x%08X\n",chan ,temp_val);

}
void bts_rfic_read_mipi_reg(int chan)
{
    uint32_t temp_addr, temp_val;

    temp_addr = 0xF0004000;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register CSI2_FRAME_START_DATA      is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register CSI2_DATA_FRAME_DATA       is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register CSI2_FRAME_END_DATA        is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register CSI2_LINE_START_DATA       is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register CSI2_LINE_END_DATA         is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register CSI2_PKT_CTL               is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register CSI2_DATA_FRAME_FIELD_CTL  is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register CSI2_DMA_DATA_CNT          is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register CSI2_IRQ_EN                is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register CSI2_FAULT_EN              is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register DPHY_ESC_MODE_DATA         is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register DPHY_TEST_MODE_CTRL        is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register CSI2_STAT_REG              is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register CSI2_ECC_SB_ERR            is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register CSI2_ECC_DB_ERR            is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register CSI2_BUFF_ADDR             is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register CSI2_RUN_CTL               is : 0x%08X\n",chan ,temp_val);
    temp_addr = temp_addr + 4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register CSI2_DPHY_TEST_STAT        is : 0x%08X\n",chan ,temp_val);   
}
void bts_rfic_read_misc_reg(int chan)
{
    uint32_t temp_addr, temp_val;

    temp_addr = 0xF0017000;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_SPI_CRC0              is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0017018;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_CLK_CTRL              is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0017020;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_SCRATCHPAD0           is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0017024;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_SCRATCHPAD1           is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0017034;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_FILTER_CTRL           is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0017038;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_UDMA_REQ_MUS_SEL0     is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF001703C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_UDMA_REQ_MUS_SEL1     is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF001705C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_PWRDN                 is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0017070;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_HW_ENGINE_CTRL        is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0017074;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_FILTER_CTRL1          is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0017080;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_SPI_CRC1              is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0017084;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_BOOT_STATUS           is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0017088;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_LINE_SHIFT_ERR        is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF001708C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_DEVICE_ENUM_ID        is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0017098;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_CHIP_MODE             is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00170A0;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_SPI_DEVICE_REV        is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00170A4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MISC_PART_MANUF_ID         is : 0x%08X\n",chan ,temp_val);
}
void bts_rfic_read_udma_reg(int chan)
{
    uint32_t temp_addr, temp_val;

    temp_addr = 0xF0001000;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_STAT                      is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001004;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_CFG                       is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001014;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_SWREQ                     is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001020;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_RMSK_SET                  is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001024;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_RMSK_CLR                  is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001028;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_EN_SET                    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF000102C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_EN_CLR                    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001030;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_ALT_SET                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001034;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_ALT_CLR                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001038;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_PRI_SET                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF000103C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_PRI_CLR                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001048;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_ERR_CHNL_CLR              is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF000104C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_ERR_CLR                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001050;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_INVALIDDESC_CLR           is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001800;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_BS_SET                    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001804;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_BS_CLR                    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001810;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_SRCADDR_SET               is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001814;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_SRCADDR_CLR               is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001818;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_DSTADDR_SET               is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF000181C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_DSTADDR_CLR               is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001820;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_CH_CLR_ALT_AT_DONE_SET    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001824;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_CH_CLR_ALT_AT_DONE_CLR    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001828;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_CH_DONT_CLR_AT_DONE_SET   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF000182C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_CH_DONT_CLR_AT_DONE_CLR   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0001FE0;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register UDMA_REVID                     is : 0x%08X\n",chan ,temp_val);

}
void bts_rfic_read_mipicsi2_reg(int chan)
{
    uint32_t temp_addr, temp_val;

    temp_addr = 0xF0005000;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_VERSION                          is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005004;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_CSI2_RESETN                      is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005020;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_ST_MAIN                      is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005024;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_ST_VPG                       is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005028;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_ST_IDI                       is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005030;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_STPHY                        is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005040;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_MASK_N_VPG                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005044;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_FORCE_VPG                    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005048;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_MASK_N_IDI                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF000504C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_FORCE_IDI                    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005058;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_MASK_N_PHY                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF000505c;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_FORCE_PHY                    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005080;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_VPG_CTRL                         is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005084;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_VPG_STATUS                       is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005088;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_VPG_MODE_CFG                     is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF000508C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_VPG_PKT_CFG                      is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005090;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_VPG_PKT_SIZE                     is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005094;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_VPG_HSA_TIME                     is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005098;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_VPG_HBP_TIME                     is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF000509C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_VPG_HLINE_TIME                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00050A0;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_VSA_LINES                        is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00050A4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_VBP_LINES                        is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00050A8;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_VFP_LINES                        is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00050AC;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_ACT_LINES                        is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00050B0;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_MAX_FRAME_NUM                    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00050B4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_START_LINE_NUM                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00050B8;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_STEP_LINE_NUM                    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00050E0;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_PHY_RSTZ                         is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00050E4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_PHY_IF_CFG                       is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00050E8;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_LPCLK_CTRL                       is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00050EC;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_PHY_ULPS_CTRL                    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00050F0;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_CLKMGR_CFG                       is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00050F4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_PHY_TX_TRIGGERS                  is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00050F8;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_PHY_CAL                          is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF00050FC;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_TO_CNT_CFG                       is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005110;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_PHY_STATUS                       is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005114;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_PHY0_TST_CTRL0                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005118;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_PHY0_TST_CTRL1                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005180;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_IDI_FIFO_STATUS                  is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A00;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_ST_FAP_VPG                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A04;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_ST_FAP_IDI                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A0C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_ST_FAP_PHY                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A20;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_MASK_FAP_N_VPG               is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A24;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_FORCE_FAP_VPG                is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A28;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_MASK_FAP_N_IDI               is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A2C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_FORCE_FAP_IDI                is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A38;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_MASK_FAP_N_PHY               is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A3C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_FORCE_FAP_PHY                is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A64;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_IDI_AP_STATUS                    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A68;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_LANE_MGR_AP_STATUS               is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A6C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_PHY_IF_CTRL_AP_STATUS            is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A70;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_REG_BANK_AP_STATUS               is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A78;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_IDI_FIFOCTRL_AP_STATUS           is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A7C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_PKT_BUILDER_AP_STATSU            is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A80;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_ERR_HANDLER_AP_STATUS            is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A84;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_FIFO_ADAPTER_AP_STATUS           is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A88;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_ELASTBUF_AP_STATUS               is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A8C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_ECF_AP_STATUS                    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A90;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_CMU_AP_STATUS                    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A94;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_AMBAAPBINTF_AP_STATUS            is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005A98;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_CHANNEL_SEL_AP_STATUS            is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005AC8;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_MASK_N_IDI_AP_STATUS             is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005ACC;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_FORCE_IDI_AP_STATUS              is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005AD0;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_MASK_N_LANE_MGR_AP_STATUS        is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005AD4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_FORCE_LANE_MGR_AP_STATUS         is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005AD8;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_MASK_N_PHJY_IF_CTRL_AP_STATUS    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005ADC;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_FORCE_PHY_IF_CTRL_AP_STATUS      is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005AE0;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_MASK_N_REG_BANK_AP_STATUS        is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005AE4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_FORCE_REG_BANK_AP_STATUS         is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005AF0;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_MASK_N_IDI_FIFOCTRL_AP_STATUS    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005AF4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_FORCE_IDI_FIFOCTRL_AP_STATUS     is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005AF8;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_MASK_N_PKT_BUILDER_AP_STATUS     is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005AFC;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_FORCE_PKT_BUILDER_AP_STATUS      is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005B00;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_MASK_N_ERR_HANDLER_AP_STATUS     is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005B04;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_FORCE_ERR_HANDLER_AP_STATUS      is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005B08;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_MASK_N_FIFO_ADAPTER_AP_STATUS    is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005B0C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_FORCE_FIFO_ADAPTER_AP_STATUS     is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005B10;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_MASK_N_ELASTBUF_AP_STATUS        is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005B14;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_FORCE_ELASTBUF_AP_STATUS         is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005B18;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_MASK_N_ECF_AP_STATUS             is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005B1C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_FORCE_ECF_AP_STATUS              is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005B20;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_MASK_N_CMU_AP_STATUS             is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005B24;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_FORCE_CMU_AP_STATUS              is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005B28;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_MASK_N_AMBAAPBINTF_AP_STATUS     is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005B2C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_FORCE_AMBAAPBINTF_AP_STATUS      is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005B30;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_MASK_N_CHANNEL_SEL_AP_STATUS     is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005B34;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_FORCE_CHANNEL_SEL_AP_STATUS      is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005F00;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_ST_DIAG_MAIN                 is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005F04;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_ST_DIAG0                     is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005F10;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_MASK_N_DIAG0                 is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005F14;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_INT_FORCE_DIAG0                  is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005F20;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_PLDP_ECC_SYNDOUT                 is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005F24;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_CL_BCM_SYNC                      is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005F28;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_CL_BCM23ACK_PPIAPB               is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005F2C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_CL_BCM23ACK_IDIAPB               is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005F34;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_HDDP_ECC_SYNDOUT                 is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005F40;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_ERR_INJ_CTRL                     is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005F44;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_ERR_INJ_STATUS                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005F48;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_ERR_INJ_CHK_MASK                 is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005F4C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_ERR_INJ_DH32_MASK                is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005F50;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_ERR_INJ_DL32_MASK                is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005F60;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_IDI_RAM_ERR_LOG_AP               is : 0x%08X\n",chan ,temp_val);
    temp_addr = 0xF0005F64;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register MCSI2_IDI_RAM_ERR_ADDR_AP              is : 0x%08X\n",chan ,temp_val);

}
void bts_rfic_read_fw_cfg_reg(int chan)
{
    uint32_t temp_addr, temp_val;
    uint32_t base_addr = 0x80006000;

    temp_addr = base_addr + 0x00;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_REF_FREQ_HZ                 is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x04;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_RF_PLL_LF_BW_HZ             is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x08;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_RAMP_START_FREQ_HZ0         is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x0C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_RAMP_START_FREQ_HZ1         is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x10;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_RAMP_BW_MHZ                 is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x20;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_CASCADED                    is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x24;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_PD_AUTO                     is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x28;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_HPF_FC_RX_CHAN0             is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x2C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_HPF_FC_RX_CHAN1             is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x30;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_HPF_FC_RX_CHAN2             is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x34;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_HPF_FC_RX_CHAN3             is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x38;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_HPF_GAIN_RX_CHAN0           is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x3C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_HPF_GAIN_RX_CHAN1           is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x40;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_HPF_GAIN_RX_CHAN2           is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x44;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_HPF_GAIN_RX_CHAN3           is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x48;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_PGA_GAIN_RX_CHAN0           is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x4C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_PGA_GAIN_RX_CHAN1           is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x50;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_PGA_GAIN_RX_CHAN2           is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x54;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_PGA_GAIN_RX_CHAN3           is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x5C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_PWR_TX0                     is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x60;          
    adi_dm_Read(chan, temp_addr, &temp_val);            
    printf("In #%d device, the value of the register FW_CFG_PWR_TX1                     is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x64;          
    adi_dm_Read(chan, temp_addr, &temp_val);            
    printf("In #%d device, the value of the register FW_CFG_PWR_TX2                     is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x68;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_CRC_USR_AREA_ADDR           is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x6C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_CRC_USR_AREA_CNT            is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x88;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_VDDIO_MIN_V                 is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0xB4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_VDDIO_MAX_V                 is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0xDC;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_ADC_GAIN_RX_CHAN0           is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0xE0;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_ADC_GAIN_RX_CHAN1           is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0xE4;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_ADC_GAIN_RX_CHAN2           is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0xE8;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_ADC_GAIN_RX_CHAN3           is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x100;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_PAT_SEL_TEST_TONE           is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x104;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_CHAN_SEL_TEST_TONE          is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x108;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_POWER_MANAGE                is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x10C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_CONTINUOUS_PA               is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x13C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_MEAS_REL_GAIN_MISMATCH_0    is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x140;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_MEAS_REL_GAIN_MISMATCH_1    is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x144;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_MEAS_REL_GAIN_MISMATCH_2    is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x148;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_MEAS_REL_GAIN_MISMATCH_3    is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x14C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_MEAS_REL_GAIN_MISMATCH_4    is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x150;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_MEAS_REL_GAIN_MISMATCH_5    is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x154;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_OP_PWR_TX0                  is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x158;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_OP_PWR_TX1                  is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x15C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_OP_PWR_TX2                  is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x180;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_RFPLL_REIOD_LOW_LIM         is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x184;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_RFPLL_REIOD_HIGH_LIM        is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x19C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_RF_CHAIN_CHK                is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x1A0;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_PWR_DET_MEAS                is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x1A8;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_DMA_OFFSETS_SEL             is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x304;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_CRC_GROUP_SEL               is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x308;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_CRC_SIGNATURE_SEL           is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x30C;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_BLOCK_LEN                   is : 0x%08X\n",chan ,temp_val);
    temp_addr = base_addr + 0x310;
    adi_dm_Read(chan, temp_addr, &temp_val);
    printf("In #%d device, the value of the register FW_CFG_BLOCK_CRC                   is : 0x%08X\n",chan ,temp_val);
    
}

void bts_rfic_read_afe_reg(int chan)
{
    int ii;
    uint32_t temp_addr, temp_val;

    for(ii = 0; ii < 4; ii++)
    {
        temp_addr = 0xF0012000 + ii*0x00001000;
        adi_dm_Read(chan, temp_addr, &temp_val);
        printf("In #%d device, the value of the register AFE#%d, HPF_CTRL0          is : 0x%08X\n", chan, ii, temp_val);
        temp_addr = 0xF0012008 + ii*0x00001000;
        adi_dm_Read(chan, temp_addr, &temp_val);
        printf("In #%d device, the value of the register AFE#%d, PGA_CTRL0          is : 0x%08X\n", chan, ii, temp_val);
        temp_addr = 0xF0012010 + ii*0x00001000;
        adi_dm_Read(chan, temp_addr, &temp_val);
        printf("In #%d device, the value of the register AFE#%d, PKDET1_CTRL        is : 0x%08X\n", chan, ii, temp_val);
        temp_addr = 0xF0012014 + ii*0x00001000;
        adi_dm_Read(chan, temp_addr, &temp_val);
        printf("In #%d device, the value of the register AFE#%d, PKDET2_CTRL        is : 0x%08X\n", chan, ii, temp_val);
        temp_addr = 0xF001201C + ii*0x00001000;
        adi_dm_Read(chan, temp_addr, &temp_val);
        printf("In #%d device, the value of the register AFE#%d, ADC_MAIN_CTRL      is : 0x%08X\n", chan, ii, temp_val);
        temp_addr = 0xF0012040 + ii*0x00001000;
        adi_dm_Read(chan, temp_addr, &temp_val);
        printf("In #%d device, the value of the register AFE#%d, ADC_PKDET_CTRL     is : 0x%08X\n", chan, ii, temp_val);
        temp_addr = 0xF0012048 + ii*0x00001000;
        adi_dm_Read(chan, temp_addr, &temp_val);
        printf("In #%d device, the value of the register AFE#%d, AFECTRL            is : 0x%08X\n", chan, ii, temp_val);
        temp_addr = 0xF0012058 + ii*0x00001000;
        adi_dm_Read(chan, temp_addr, &temp_val);
        printf("In #%d device, the value of the register AFE#%d, FLT_DATALIM        is : 0x%08X\n", chan, ii, temp_val);
        temp_addr = 0xF0012080 + ii*0x00001000;
        adi_dm_Read(chan, temp_addr, &temp_val);
        printf("In #%d device, the value of the register AFE#%d, PKDET_OUT          is : 0x%08X\n", chan, ii, temp_val);
        temp_addr = 0xF0012084 + ii*0x00001000;
        adi_dm_Read(chan, temp_addr, &temp_val);
        printf("In #%d device, the value of the register AFE#%d, FLT_SAFE_LIMIT     is : 0x%08X\n", chan, ii, temp_val);
        temp_addr = 0xF0012088 + ii*0x00001000;
        adi_dm_Read(chan, temp_addr, &temp_val);
        printf("In #%d device, the value of the register AFE#%d, FLT_STATUS         is : 0x%08X\n", chan, ii, temp_val);
    }
    

}


void bts_rfic_udma_mode_change(void)
{
    uint32_t temp_addr, temp_val;

    // bts_rfic_read_ramp_gen_reg(0);
    // bts_rfic_read_rfpll_reg(0);
    // bts_rfic_read_mipi_reg(0);
    // printf("\n");
    // bts_rfic_read_ramp_gen_reg(1);  
    // bts_rfic_read_rfpll_reg(1);
    // bts_rfic_read_mipi_reg(1);
    // printf("\n");
    // bts_rfic_read_ramp_gen_reg(2);  
    // bts_rfic_read_rfpll_reg(2);
    // bts_rfic_read_mipi_reg(2);
    // printf("\n");
    // bts_rfic_read_ramp_gen_reg(3);  
    // bts_rfic_read_rfpll_reg(3);
    // bts_rfic_read_mipi_reg(3);

    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000003); //trig 0, 1ch
    // usleep(100);
    // adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000002); //trig 0, 1ch  

}
void bts_rfic_udma_reload(void)
{
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000010); //trig 4ch
    bts_rfic_udma_mode_change();
}

void test_rfic_udma(bts_afi910_config_t * p)
{
    printf("Welcome to rfic udma test function...\n");
    int ii, res;         // temp index for loops

    uint32_t dma_pri_start = ADI_ADAR690x_DMA_BASE_POINTER;
    uint32_t dma_set_size = DMA_CHAN_CTRL_SIZE;
    uint32_t dma_word_size = DMA_WORD_SIZE;
    uint32_t dma_pri_alt_offset = 0x00000100;
    uint32_t area_start = ADI_ADAR690x_DMA_AREA_BASE;

    for(ii = 0; ii < 16; ii++)
    {
        dma_pri_addr[ii] = dma_pri_start + ii * dma_set_size;
        dma_alt_addr[ii] = dma_pri_addr[ii] + dma_pri_alt_offset;
        dma_pri_end_ptr[ii] = dma_pri_addr[ii] + dma_set_size - dma_word_size;
        dma_alt_end_ptr[ii] = dma_alt_addr[ii] + dma_set_size - dma_word_size;
        printf("CH%d Pri.addr : 0x%X, Alt.addr : 0x%X, Pri.end_ptr : 0x%X, Alt.end_ptr : 0x%X\n", ii, dma_pri_addr[ii],dma_alt_addr[ii],dma_pri_end_ptr[ii],dma_alt_end_ptr[ii]);
    }
    // list here tast functions.
    // test_rfic_udma_test0();
    // test_rfic_udma_test1();
    // test_rfic_udma_test2();
    // test_rfic_udma_test3();


    bts_rfic_udma_init();
    res = platform_fault_check();
        if (res != ADI_DM_SUCCESS) {platform_error("FALUT_CHECK ERROR", res, __FILE__, __LINE__);}
        else{printf("Error check : OK\n");}

    bts_rfic_udma_set(p);
    res = platform_fault_check();
        if (res != ADI_DM_SUCCESS) {platform_error("FALUT_CHECK ERROR", res, __FILE__, __LINE__);}
        else{printf("Error check : OK\n");}
}

void bts_rfic_udma_init(void)
{
    printf("Enter the bts_rfic_udma_init functions...\n");
    uint32_t temp_val;
    uint32_t temp_addr;

    // DMA configuration setting
    temp_addr = REG_UDMA_CFG;
    temp_val  = 0x00000001;     // uDMA enable
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, temp_addr, temp_val);

    temp_addr = REG_UDMA_EN_CLR;
    temp_val  = 0x0000FFFF;     // off all DMA Channels for setting
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, temp_addr, temp_val);

    // alt clear set
    temp_addr = REG_UDMA_RMSK_CLR;
    temp_val  = 0x0000001F;     // DMA CH 0, 1, 2, 3 are enabled
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, temp_addr, temp_val);

    // alt clear set
    temp_addr = REG_UDMA_CHNL_CLEAR_ALT_AT_DONE_SET;
    temp_val  = 0x0000001F;     // DMA CH 0, 1, 2, 3 are enabled
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, temp_addr, temp_val);

    temp_addr = REG_UDMA_CHNL_CLEAR_ALT_AT_DONE_CLR;
    temp_val  = 0x0000FFE0;     // off other DMA Channels
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, temp_addr, temp_val);

    // dont clear set
    temp_addr = REG_UDMA_CHNL_DONT_CLEAR_EN_AT_DONE_SET;
    temp_val  = 0x0000001F;     // DMA CH 0, 1, 2, 3 don't clear set
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, temp_addr, temp_val);

    temp_addr = REG_UDMA_CHNL_DONT_CLEAR_EN_AT_DONE_CLR;
    temp_val  = 0x0000FFE0;     // clear off other DMA Channels
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, temp_addr, temp_val);


    // Trigger mux set  (refer to ADAR690x Hardware Reference Manual)
    // CH0 : SW_trigger(CH 10, Never used...)
    // CH1 : SW_trigger(CH 10, Never used...)
    // CH2 : CH3 dma_done
    // CH3 : rg_dma_en
    // CH4 : SW_trigger(CH10, Never used...)
    // CH5~CH16 : disabled...
    temp_val =  0x000A3E88;
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MISC_MISC_UDMA_REQ_MUX_SEL_0, temp_val);
    temp_val =  0x00000000;
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MISC_MISC_UDMA_REQ_MUX_SEL_1, temp_val);

    // DMA channel Enable set
    temp_addr = REG_UDMA_EN_SET;
    temp_val  = 0x00000013;     // DMA CH 0, 1, 2, 3, 4 are enabled
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, temp_addr, temp_val);

    // DMA configuration setting
    temp_addr = REG_UDMA_CFG;
    temp_val  = 0x00000001;     // uDMA enable
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, temp_addr, temp_val);

    printf("Exit the bts_rfic_udma_init functions...\n");
}

void bts_rfic_udma_set(bts_afi910_config_t * p)
{
    int ii, jj; // temp index for loop
    int res;

    uint32_t temp_addr, tx_array_start_addr;
    uint32_t temp_val;
    uint32_t ch1_pri_cfg_temp, ch2_pri_cfg_temp, ch3_pri_cfg_temp;
    uint32_t ch1_alt1_cfg_temp, ch1_alt2_cfg_temp;
    uint32_t ch2_alt1_cfg_temp;
    uint16_t d_mode_tx_pattern, lms_mode_tx_pattern[12];
    uint8_t  d_vc_id, lms_vc_id;
    uint32_t d_mode_vc_id_data[5]   = {0,};     // 5 is for (FS, Data, FE, LS and LE)
    uint32_t lms_mode_vc_id_data[5] = {0,};     // 5 is for (FS, Data, FE, LS and LE)

    bts_afi910_rfic_udma_ch_set_t temp_ch_set;

    /* Data store for uDMA operations.
     * And, I will not use any variables to express adress and values.
     * If you want to know organization of the uDMA, please, refer to excel sheet */
    // CH4 primary : Load CH4 Alternate set1
    // CH4 : Task1(Alt.1) - Reload initial CH0~3 primary uDMA setting
    temp_addr = dma_pri_addr[4];
    temp_ch_set.src_addr    = 0x8000894C;
    temp_ch_set.dest_addr   = 0x8000854C;
    temp_ch_set.udma_ch_cfg = UDMA_CTRL_CFG_DSTINC_WORD    /* increment dst_ptr */
                            | UDMA_CTRL_CFG_SRCINC_WORD    /* increment src_ptr */
                            | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                            | UDMA_CTRL_CFG_R_POWER_X4     /* arbitrate after 4 transfers */
                            | UDMA_CTRL_CFG_TRANSFERS(4)   /* total transfers 4(1 tasks) */
                            | UDMA_CTRL_CFG_CYC_CTRL_PERI_SCATTER_GATHER_PRI; //0x8A008036;
    temp_ch_set.reserved    = 0x00000000;                  /* Last word of Channel set is always 0 */
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    /* From here, Ingredients of uDMA are stored in mem space in RFIC(start from 0x80008600) */
    // CH0 Alternate Set1 : Load D-MODE uDMA Primary set for CH1, 2, 3
    temp_addr = 0x80008600;                                // Set memory location
    temp_ch_set.src_addr    = 0x8000866C;
    temp_ch_set.dest_addr   = 0x8000843C;
    temp_ch_set.udma_ch_cfg = UDMA_CTRL_CFG_DSTINC_WORD    /* increment dst_ptr */
                            | UDMA_CTRL_CFG_SRCINC_WORD    /* increment src_ptr */
                            | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                            | UDMA_CTRL_CFG_R_POWER_X16    /* arbitrate after 4 transfers */
                            | UDMA_CTRL_CFG_TRANSFERS(12)  /* total transfers 4(1 tasks) */
                            | UDMA_CTRL_CFG_CYC_CTRL_PERI_SCATTER_GATHER_ALT; //0x8A0100B7;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH0 Alternate Set2 : Load L-MODE uDMA Primary set for CH1, 2, 3 (udma_ch_cfg is equal to CH0 Alt Set1)
    temp_ch_set.src_addr    = 0x8000869C;
    temp_ch_set.dest_addr   = 0x8000843C;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH0 Alternate Set3 : Load M-MODE uDMA Primary set for CH1, 2, 3 (udma_ch_cfg is equal to CH0 Alt Set1)
    temp_ch_set.src_addr    = 0x800086CC;
    temp_ch_set.dest_addr   = 0x8000843C;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH0 Alternate Set3 : Load M-MODE uDMA Primary set for CH1, 2, 3 (udma_ch_cfg is equal to CH0 Alt Set1)
    temp_ch_set.src_addr    = 0x800086FC;
    temp_ch_set.dest_addr   = 0x8000843C;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);


printf("\n");
    /* ============ D-MODE CH1, 2 and 3 primary set will be stored. ============*/
    // CH1 Primary : Load CH1 Alternate Set1, 2
    // CH1 Task1(Alt.1) - Load D-Mode Ramp Profile
    // CH1 Task2(Alt.2) - Load D-Mode VC-ID of MIPI
    temp_ch_set.src_addr    = 0x8000871C;
    temp_ch_set.dest_addr   = 0x8000851C;
    temp_ch_set.udma_ch_cfg = UDMA_CTRL_CFG_DSTINC_WORD    /* increment dst_ptr */
                            | UDMA_CTRL_CFG_SRCINC_WORD    /* increment src_ptr */
                            | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                            | UDMA_CTRL_CFG_R_POWER_X4     /* arbitrate after 4 transfers */
                            | UDMA_CTRL_CFG_TRANSFERS(8)   /* total transfers 8(2 tasks) */
                            | UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_PRI; //0x8A008074;
    ch1_pri_cfg_temp        = temp_ch_set.udma_ch_cfg;      // it will be used again for L,M,S-MODE
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH2 Primary : Load CH2 Alternate Set1
    // CH2 Task1(Alt.1) - Load CH3 Primary set when CH3 primary task is done
    temp_ch_set.src_addr    = 0x8000878C;
    temp_ch_set.dest_addr   = 0x8000852C;
    temp_ch_set.udma_ch_cfg = UDMA_CTRL_CFG_DSTINC_WORD    /* increment dst_ptr */
                            | UDMA_CTRL_CFG_SRCINC_WORD    /* increment src_ptr */
                            | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                            | UDMA_CTRL_CFG_R_POWER_X4     /* arbitrate after 4 transfers */
                            | UDMA_CTRL_CFG_TRANSFERS(4)   /* total transfers 4(1 task) */
                            | UDMA_CTRL_CFG_CYC_CTRL_PERI_SCATTER_GATHER_PRI; //0x8A008036;
    ch2_pri_cfg_temp        = temp_ch_set.udma_ch_cfg;      // it will be used again for L,M,S-MODE
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH3 Primary : Load TX pattern for D-MODE
    temp_ch_set.src_addr    = 0x8000886C;
    temp_ch_set.dest_addr   = 0xF0020218;
    temp_ch_set.udma_ch_cfg = UDMA_CTRL_CFG_DSTINC_NOINCR  /* increment dst_ptr */
                            | UDMA_CTRL_CFG_SRCINC_WORD  /* increment src_ptr */
                            | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                            | UDMA_CTRL_CFG_R_POWER_X1     /* arbitrate after 4 transfers */
                            | UDMA_CTRL_CFG_TRANSFERS(8)   /* total transfers 8 */
                            | UDMA_CTRL_CFG_CYC_CTRL_BASIC; //0xCA000071;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    /* ============ L-MODE CH1, 2 and 3 primary set will be stored. ============*/
    // CH1 Primary : Load CH1 Alternate Set1, 2
    // CH1 Task1(Alt.1) - Load L-Mode Ramp Profile
    // CH1 Task2(Alt.2) - Load L-Mode VC-ID of MIPI
    temp_ch_set.src_addr    = 0x8000873C;
    temp_ch_set.dest_addr   = 0x8000851C;
    temp_ch_set.udma_ch_cfg = ch1_pri_cfg_temp;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH2 Primary : Load CH2 Alternate Set1
    // CH2 Task1(Alt.1) - Load CH3 Primary set when CH3 primary task is done
    temp_ch_set.src_addr    = 0x8000879C;
    temp_ch_set.dest_addr   = 0x8000852C;
    temp_ch_set.udma_ch_cfg = ch2_pri_cfg_temp;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH3 Primary : Load TX pattern for L-MODE
    temp_ch_set.src_addr    = 0x8000889C;
    temp_ch_set.dest_addr   = 0xF0020218;
    temp_ch_set.udma_ch_cfg = UDMA_CTRL_CFG_DSTINC_NOINCR  /* increment dst_ptr */
                            | UDMA_CTRL_CFG_SRCINC_NOINCR  /* increment src_ptr */
                            | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                            | UDMA_CTRL_CFG_R_POWER_X1     /* arbitrate after 4 transfers */
                            | UDMA_CTRL_CFG_TRANSFERS(12)   /* total transfers 12 */
                            | UDMA_CTRL_CFG_CYC_CTRL_BASIC; //0xCA0000B1;
    ch3_pri_cfg_temp        = temp_ch_set.udma_ch_cfg;      // it will be used again for M,S-MODE
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    /* ============ M-MODE CH1, 2 and 3 primary set will be stored. ============*/
    // CH1 Primary : Load CH1 Alternate Set1, 2
    // CH1 Task1(Alt.1) - Load M-Mode Ramp Profile
    // CH1 Task2(Alt.2) - Load M-Mode VC-ID of MIPI
    temp_ch_set.src_addr    = 0x8000875C;
    temp_ch_set.dest_addr   = 0x8000851C;
    temp_ch_set.udma_ch_cfg = ch1_pri_cfg_temp;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH2 Primary : Load CH2 Alternate Set1
    // CH2 Task1(Alt.1) - Load CH3 Primary set when CH3 primary task is done
    temp_ch_set.src_addr    = 0x800087AC;
    temp_ch_set.dest_addr   = 0x8000852C;
    temp_ch_set.udma_ch_cfg = ch2_pri_cfg_temp;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH3 Primary : Load TX pattern for M-MODE
    temp_ch_set.src_addr    = 0x8000889C;
    temp_ch_set.dest_addr   = 0xF0020218;
    temp_ch_set.udma_ch_cfg = ch3_pri_cfg_temp;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    /* ============ S-MODE CH1, 2 and 3 primary set will be stored. ============*/
    // CH1 Primary : Load CH1 Alternate Set1, 2
    // CH1 Task1(Alt.1) - Load S-Mode Ramp Profile
    // CH1 Task2(Alt.2) - Load S-Mode VC-ID of MIPI
    temp_ch_set.src_addr    = 0x8000877C;
    temp_ch_set.dest_addr   = 0x8000851C;
    temp_ch_set.udma_ch_cfg = ch1_pri_cfg_temp;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH2 Primary : Load CH2 Alternate Set1
    // CH2 Task1(Alt.1) - Load CH3 Primary set when CH3 primary task is done
    temp_ch_set.src_addr    = 0x800087BC;
    temp_ch_set.dest_addr   = 0x8000852C;
    temp_ch_set.udma_ch_cfg = ch2_pri_cfg_temp;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH3 Primary : Load TX pattern for S-MODE
    temp_ch_set.src_addr    = 0x8000889C;
    temp_ch_set.dest_addr   = 0xF0020218;
    temp_ch_set.udma_ch_cfg = ch3_pri_cfg_temp;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);




printf("\n");
    /* ============ D-MODE CH1 alternate set will be stored. ============*/
    // CH1 Task1(Alt.1) - Load D-Mode Ramp Profile
    temp_ch_set.src_addr    = 0x800087E0;
    temp_ch_set.dest_addr   = 0xF0020220;       // End addr of ramp profile generation register
    temp_ch_set.udma_ch_cfg = UDMA_CTRL_CFG_DSTINC_WORD    /* increment dst_ptr */
                            | UDMA_CTRL_CFG_SRCINC_WORD    /* increment src_ptr */
                            | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                            | UDMA_CTRL_CFG_R_POWER_X16    /* arbitrate after 16 transfers */
                            | UDMA_CTRL_CFG_TRANSFERS(9)   /* total transfers 9(ramp profile) */
                            | UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_ALT; //0x8A010085;
    ch1_alt1_cfg_temp        = temp_ch_set.udma_ch_cfg;      // it will be used again for L,M,S-MODE
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH1 Task2(Alt.2) - Load D-Mode VC-ID of MIPI
    temp_ch_set.src_addr    = 0x800088B0;
    temp_ch_set.dest_addr   = 0xF0004010;       // End addr of MIPI (FS,DATA,FE,LS and LE) setting register
    temp_ch_set.udma_ch_cfg = UDMA_CTRL_CFG_DSTINC_WORD    /* increment dst_ptr */
                            | UDMA_CTRL_CFG_SRCINC_WORD    /* increment src_ptr */
                            | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                            | UDMA_CTRL_CFG_R_POWER_X8    /* arbitrate after 16 transfers */
                            | UDMA_CTRL_CFG_TRANSFERS(5)   /* total transfers 9(ramp profile) */
                            | UDMA_CTRL_CFG_CYC_CTRL_BASIC; //0x8A00C041;
    ch1_alt2_cfg_temp        = temp_ch_set.udma_ch_cfg;      // it will be used again for L,M,S-MODE
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    /* ============ L-MODE CH1 alternate set will be stored. ============*/
    // CH1 Task1(Alt.1) - Load L-Mode Ramp Profile
    temp_ch_set.src_addr    = 0x80008804;
    temp_ch_set.dest_addr   = 0xF0020220;       // End addr of ramp profile generation register
    temp_ch_set.udma_ch_cfg = ch1_alt1_cfg_temp;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH1 Task2(Alt.2) - Load L-Mode VC-ID of MIPI
    temp_ch_set.src_addr    = 0x800088C4;
    temp_ch_set.dest_addr   = 0xF0004010;       // End addr of MIPI (FS,DATA,FE,LS and LE) setting register
    temp_ch_set.udma_ch_cfg = ch1_alt2_cfg_temp;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    /* ============ M-MODE CH1 alternate set will be stored. ============*/
    // CH1 Task1(Alt.1) - Load M-Mode Ramp Profile
    temp_ch_set.src_addr    = 0x80008828;
    temp_ch_set.dest_addr   = 0xF0020220;       // End addr of ramp profile generation register
    temp_ch_set.udma_ch_cfg = ch1_alt1_cfg_temp;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH1 Task2(Alt.2) - Load M-Mode VC-ID of MIPI
    temp_ch_set.src_addr    = 0x800088D8;
    temp_ch_set.dest_addr   = 0xF0004010;       // End addr of MIPI (FS,DATA,FE,LS and LE) setting register
    temp_ch_set.udma_ch_cfg = ch1_alt2_cfg_temp;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    /* ============ S-MODE CH1 alternate set will be stored. ============*/
    // CH1 Task1(Alt.1) - Load S-Mode Ramp Profile
    temp_ch_set.src_addr    = 0x8000884C;
    temp_ch_set.dest_addr   = 0xF0020220;       // End addr of ramp profile generation register
    temp_ch_set.udma_ch_cfg = ch1_alt1_cfg_temp;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH1 Task2(Alt.2) - Load S-Mode VC-ID of MIPI
    temp_ch_set.src_addr    = 0x800088EC;
    temp_ch_set.dest_addr   = 0xF0004010;       // End addr of MIPI (FS,DATA,FE,LS and LE) setting register
    temp_ch_set.udma_ch_cfg = ch1_alt2_cfg_temp;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);


    /* ============ CH2 alternate set will be stored. ============*/
    // CH2 Task1(Alt.1) - Reload CH3 Primary udma_ch_cfg for D-MODE for repeat CH3 again...
    temp_ch_set.src_addr    = 0x80008668;
    temp_ch_set.dest_addr   = 0x80008438;       // CH3 primary udma_ch_cfg register
    temp_ch_set.udma_ch_cfg = UDMA_CTRL_CFG_DSTINC_NOINCR  /* increment dst_ptr */
                            | UDMA_CTRL_CFG_SRCINC_NOINCR  /* increment src_ptr */
                            | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                            | UDMA_CTRL_CFG_R_POWER_X1     /* arbitrate after 16 transfers */
                            | UDMA_CTRL_CFG_TRANSFERS(128)  /* total transfers 128(128 * 8 = 1024 ramps) */
                            | UDMA_CTRL_CFG_CYC_CTRL_PERI_SCATTER_GATHER_ALT; //0xCE0007F7;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH2 Task1(Alt.1) - Reload CH3 Primary udma_ch_cfg for L-MODE for repeat CH3 again...
    temp_ch_set.src_addr    = 0x80008698;
    temp_ch_set.dest_addr   = 0x80008438;       // CH3 primary udma_ch_cfg register
    temp_ch_set.udma_ch_cfg = UDMA_CTRL_CFG_DSTINC_NOINCR  /* increment dst_ptr */
                            | UDMA_CTRL_CFG_SRCINC_NOINCR  /* increment src_ptr */
                            | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                            | UDMA_CTRL_CFG_R_POWER_X1     /* arbitrate after 16 transfers */
                            | UDMA_CTRL_CFG_TRANSFERS(32)  /* total transfers 32(32 * 12 = 384 ramps) */
                            | UDMA_CTRL_CFG_CYC_CTRL_PERI_SCATTER_GATHER_ALT; //0xCE0007F7;
    ch1_alt2_cfg_temp        = temp_ch_set.udma_ch_cfg;      // it will be used again for M,S-MODE
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH2 Task1(Alt.1) - Reload CH3 Primary udma_ch_cfg for M-MODE for repeat CH3 again...
    temp_ch_set.src_addr    = 0x800086C8;
    temp_ch_set.dest_addr   = 0x80008438;       // CH3 primary udma_ch_cfg register
    temp_ch_set.udma_ch_cfg = ch1_alt2_cfg_temp;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH2 Task1(Alt.1) - Reload CH3 Primary udma_ch_cfg for S-MODE for repeat CH3 again...
    temp_ch_set.src_addr    = 0x800086F8;
    temp_ch_set.dest_addr   = 0x80008438;       // CH3 primary udma_ch_cfg register
    temp_ch_set.udma_ch_cfg = ch1_alt2_cfg_temp;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);


printf("\n");
    /* ============ D, L, M and S MODE ramp profile will be stored. ============*/
    for (ii = D_MODE_BURST_NUM; ii < TOTAL_BURST_NUM; ii++) {
        put_ramp_profile(&temp_addr, &p->burst_profiles[ii].ramp_profile[0]);        // 0 for each mode has only one profile
        put_flush();
    }
    


printf("\n");
    /* ============ D, L, M and S MODE ramp profile will be stored. ============*/
    // RFIC reference device number is following the schematic. 
    // ex)RFIC0 = 0, RFIC1 = 1 so on...
    d_mode_tx_pattern = 0b000000100000;         // turn on TX6 (TX3 of RFIC1)
    for(ii=0; ii<12; ii++)
    {
        lms_mode_tx_pattern[ii] = (1 << ii);    // turn on TXs arbitrary
    }
    
    // Save D-MODE TX patter
    tx_array_start_addr = temp_addr;    // mark current address
    for(jj = 0; jj < 4; jj++)
    {
        temp_addr = tx_array_start_addr;    // reload marked address
        put_init(jj);                       // select RFICs(from 0 to 3, it is differ to )
        temp_val = ((d_mode_tx_pattern >> (3*jj)) & 0b111 ) << 21;
        for(ii = 0; ii < 8; ii++)
        {
            put_word(&temp_addr, temp_val);
        }
        put_flush();
    }
    
    // save L,M,S-MODE TX patterns
    tx_array_start_addr = temp_addr;        // mark current address
    for(jj = 0; jj < 4; jj++)
    {
        temp_addr = tx_array_start_addr;    // reload marked address
        put_init(jj);                       // select RFICs(from 0 to 3, it is differ to )
        for(ii = 0; ii < 12; ii++)
        {
            temp_val = ((lms_mode_tx_pattern[ii] >> (3*jj)) & 0b111) << 21;
            put_word(&temp_addr, temp_val);
        }
        put_flush();
    }
    


printf("\n");
    /* ============ D, L, M and S MODE MIPI VCID data will be stored. ============*/
    // make D-MODE MIPI VCID data
    d_vc_id = 0;
    d_mode_vc_id_data[0] |= 0x0 << BITP_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_DATA_TYPE;
    d_mode_vc_id_data[0] |= d_vc_id << BITP_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_VC_ID;
    d_mode_vc_id_data[0] |= 0x1 << BITP_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_WC;

    d_mode_vc_id_data[1] |= (ADI_DM_RAW12 << BITP_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_DATA_TYPE) & BITM_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_DATA_TYPE;
    d_mode_vc_id_data[1] |= d_vc_id << BITP_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_VC_ID;

    d_mode_vc_id_data[2] |= 0x1 << BITP_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_DATA_TYPE;
    d_mode_vc_id_data[2] |= d_vc_id << BITP_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_VC_ID;
    d_mode_vc_id_data[2] |= 0x1 << BITP_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_WC;

    d_mode_vc_id_data[3] |= 0x2 << BITP_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_DATA_TYPE;
    d_mode_vc_id_data[3] |= d_vc_id << BITP_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_VC_ID;
    d_mode_vc_id_data[3] |= 0x1 << BITP_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_WC;

    d_mode_vc_id_data[4] |= 0x3 << BITP_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_DATA_TYPE;
    d_mode_vc_id_data[4] |= d_vc_id << BITP_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_VC_ID;
    d_mode_vc_id_data[4] |= 0x1 << BITP_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_WC;

    // make L,M,S-MODE MIPI VCID data
    lms_vc_id = 1;
    lms_mode_vc_id_data[0] |= 0x0 << BITP_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_DATA_TYPE;
    lms_mode_vc_id_data[0] |= lms_vc_id << BITP_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_VC_ID;
    lms_mode_vc_id_data[0] |= 0x1 << BITP_MIPI_CSI2_FRAME_START_DATA_ID_WC_REG_FRAME_START_PKT_WC;

    lms_mode_vc_id_data[1] |= (ADI_DM_RAW12 << BITP_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_DATA_TYPE) & BITM_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_DATA_TYPE;
    lms_mode_vc_id_data[1] |= lms_vc_id << BITP_MIPI_CSI2_DATA_FRAME_DATA_ID_WC_REG_DATA_PKT_VC_ID;

    lms_mode_vc_id_data[2] |= 0x1 << BITP_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_DATA_TYPE;
    lms_mode_vc_id_data[2] |= lms_vc_id << BITP_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_VC_ID;
    lms_mode_vc_id_data[2] |= 0x1 << BITP_MIPI_CSI2_FRAME_END_DATA_ID_WC_REG_FRAME_END_PKT_WC;

    lms_mode_vc_id_data[3] |= 0x2 << BITP_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_DATA_TYPE;
    lms_mode_vc_id_data[3] |= lms_vc_id << BITP_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_VC_ID;
    lms_mode_vc_id_data[3] |= 0x1 << BITP_MIPI_CSI2_LINE_START_DATA_ID_WC_REG_LINE_START_PKT_WC;

    lms_mode_vc_id_data[4] |= 0x3 << BITP_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_DATA_TYPE;
    lms_mode_vc_id_data[4] |= lms_vc_id << BITP_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_VC_ID;
    lms_mode_vc_id_data[4] |= 0x1 << BITP_MIPI_CSI2_LINE_END_DATA_ID_WC_REG_LINE_END_PKT_WC;


    put_init(ADI_DM_ALL_DIGIMMICS);
    // Save D-MODE MIPI VCID data
    for(ii = 0; ii < 5; ii++)
    {
        put_word(&temp_addr, d_mode_vc_id_data[ii]);
        
    }
    put_flush();
    // Save L,M,S-MODE MIPI VCID data
    for(jj = 0; jj < 3; jj++)
    {
        for(ii = 0; ii < 5; ii++)
        {
            put_word(&temp_addr, lms_mode_vc_id_data[ii]);
            
        }
    }
    put_flush();
printf("\n");
    /* ============ DMA golden(initial) setting for CH0, 1, 2, 3, 4 will be stored ============*/
    // CH0 golden setting
    temp_ch_set.src_addr    = 0x8000863C;       // CH0 Alt setting data address in mem space
    temp_ch_set.dest_addr   = 0x8000850C;       // CH0 Alt register
    temp_ch_set.udma_ch_cfg = UDMA_CTRL_CFG_DSTINC_WORD     /* increment dst_ptr */
                            | UDMA_CTRL_CFG_SRCINC_WORD     /* increment src_ptr */
                            | UDMA_CTRL_CFG_SRC_SIZE_WORD  /* transfer 4 bytes at a time */
                            | UDMA_CTRL_CFG_R_POWER_X4     /* arbitrate after 4 transfers */
                            | UDMA_CTRL_CFG_TRANSFERS(16)  /* total transfers 16 (4 tasks) */
                            | UDMA_CTRL_CFG_CYC_CTRL_PERI_SCATTER_GATHER_PRI; //0x8A0080F6;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH1 golden setting
    temp_ch_set.src_addr    = 0x8000871C;       // CH1 Alt setting data address in mem space
    temp_ch_set.dest_addr   = 0x8000851C;       // CH1 Alt register
    temp_ch_set.udma_ch_cfg = UDMA_CTRL_CFG_DSTINC_WORD     /* increment dst_ptr */
                            | UDMA_CTRL_CFG_SRCINC_WORD     /* increment src_ptr */
                            | UDMA_CTRL_CFG_SRC_SIZE_WORD   /* transfer 4 bytes at a time */
                            | UDMA_CTRL_CFG_R_POWER_X4      /* arbitrate after 4 transfers */
                            | UDMA_CTRL_CFG_TRANSFERS(8)    /* total transfers 8(2 tasks) */
                            | UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_PRI; //0x8A008074;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH2 golden setting
    temp_ch_set.src_addr    = 0x8000878C;       // CH2 Alt setting data address in mem space
    temp_ch_set.dest_addr   = 0x8000852C;       // CH2 Alt register
    temp_ch_set.udma_ch_cfg = UDMA_CTRL_CFG_DSTINC_WORD     /* increment dst_ptr */
                            | UDMA_CTRL_CFG_SRCINC_WORD     /* increment src_ptr */
                            | UDMA_CTRL_CFG_SRC_SIZE_WORD   /* transfer 4 bytes at a time */
                            | UDMA_CTRL_CFG_R_POWER_X4      /* arbitrate after 4 transfers */
                            | UDMA_CTRL_CFG_TRANSFERS(4)    /* total transfers 4(1 task) */
                            | UDMA_CTRL_CFG_CYC_CTRL_PERI_SCATTER_GATHER_PRI; //0x8A008036;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH3 golden setting
    temp_ch_set.src_addr    = 0x8000886C;       // mem space in which TX pattern is stored
    temp_ch_set.dest_addr   = 0xF0020218;       // TX Pattern in Ramp Profile
    temp_ch_set.udma_ch_cfg = UDMA_CTRL_CFG_DSTINC_NOINCR   /* increment dst_ptr */
                            | UDMA_CTRL_CFG_SRCINC_WORD     /* increment src_ptr */
                            | UDMA_CTRL_CFG_SRC_SIZE_WORD   /* transfer 4 bytes at a time */
                            | UDMA_CTRL_CFG_R_POWER_X1      /* arbitrate after 4 transfers */
                            | UDMA_CTRL_CFG_TRANSFERS(8)    /* total transfers 8(8 TX Pattern) */
                            | UDMA_CTRL_CFG_CYC_CTRL_BASIC; //0xCA000071;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    // CH4 golden setting
    temp_ch_set.src_addr    = 0x8000894C;       // CH2 Alt setting data address in mem space
    temp_ch_set.dest_addr   = 0x8000854C;       // CH2 Alt register
    temp_ch_set.udma_ch_cfg = UDMA_CTRL_CFG_DSTINC_WORD     /* increment dst_ptr */
                            | UDMA_CTRL_CFG_SRCINC_WORD     /* increment src_ptr */
                            | UDMA_CTRL_CFG_SRC_SIZE_WORD   /* transfer 4 bytes at a time */
                            | UDMA_CTRL_CFG_R_POWER_X4      /* arbitrate after 4 transfers */
                            | UDMA_CTRL_CFG_TRANSFERS(4)    /* total transfers 4(1 task) */
                            | UDMA_CTRL_CFG_CYC_CTRL_PERI_SCATTER_GATHER_PRI; //0x8A008036;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

printf("\n");
    /* ============ CH4 alternate setting to reload CH0, 1, 2, 3, 4 will be stored ============*/
    // CH4 alternate setting
    temp_ch_set.src_addr    = 0x8000893C;       // CH2 Alt setting data address in mem space
    temp_ch_set.dest_addr   = 0x8000844C;       // CH2 Alt register
    temp_ch_set.udma_ch_cfg = UDMA_CTRL_CFG_DSTINC_WORD     /* increment dst_ptr */
                            | UDMA_CTRL_CFG_SRCINC_WORD     /* increment src_ptr */
                            | UDMA_CTRL_CFG_SRC_SIZE_WORD   /* transfer 4 bytes at a time */
                            | UDMA_CTRL_CFG_R_POWER_X32      /* arbitrate after 4 transfers */
                            | UDMA_CTRL_CFG_TRANSFERS(20)    /* total transfers 4(1 task) */
                            | UDMA_CTRL_CFG_CYC_CTRL_PERI_SCATTER_GATHER_ALT; //0x8A014137;
    bts_rfic_udma_ch_put(ADI_DM_ALL_DIGIMMICS, &temp_addr, temp_ch_set);

    
    res = platform_fault_check();
    if (res != ADI_DM_SUCCESS) {
        platform_error("FALUT_CHECK ERROR", res, __FILE__, __LINE__);
    }
    else
        printf("Error check : OK\n");

    
    ////////////////////// Initial LOADING CH0, 1, 2, 3, 4 /////////////////////
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000010); //trig 4ch


    bts_rfic_read_ramp_gen_reg(0);
    printf("\n");
    bts_rfic_read_ramp_gen_reg(1);
    printf("\n");
    bts_rfic_read_ramp_gen_reg(2);
    printf("\n");
    bts_rfic_read_ramp_gen_reg(3);

    res = platform_fault_check();
    if (res != ADI_DM_SUCCESS) {
        platform_error("FALUT_CHECK ERROR", res, __FILE__, __LINE__);
    }
    else
        printf("Error check : OK\n");
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000003); //trig 4ch
    res = platform_fault_check();
    if (res != ADI_DM_SUCCESS) {
        // temp_addr = 0xF0001048;
        // adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, temp_addr, &temp_val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,temp_addr,temp_val);
        // adi_dm_Read(ADI_DM_DIGIMMIC_SPI_SLAVE1, temp_addr, &temp_val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_SPI_SLAVE1 ,temp_addr,temp_val);
        // adi_dm_Read(ADI_DM_DIGIMMIC_SPI_SLAVE2, temp_addr, &temp_val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_SPI_SLAVE2 ,temp_addr,temp_val);
        // adi_dm_Read(ADI_DM_DIGIMMIC_SPI_SLAVE3, temp_addr, &temp_val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_SPI_SLAVE3 ,temp_addr,temp_val);
        // temp_addr = temp_addr+4;
        // adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, temp_addr, &temp_val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,temp_addr,temp_val);
        // adi_dm_Read(ADI_DM_DIGIMMIC_SPI_SLAVE1, temp_addr, &temp_val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_SPI_SLAVE1 ,temp_addr,temp_val);
        // adi_dm_Read(ADI_DM_DIGIMMIC_SPI_SLAVE2, temp_addr, &temp_val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_SPI_SLAVE2 ,temp_addr,temp_val);
        // adi_dm_Read(ADI_DM_DIGIMMIC_SPI_SLAVE3, temp_addr, &temp_val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_SPI_SLAVE3 ,temp_addr,temp_val);
        // temp_addr = temp_addr+4;
        // adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, temp_addr, &temp_val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,temp_addr,temp_val);
        // adi_dm_Read(ADI_DM_DIGIMMIC_SPI_SLAVE1, temp_addr, &temp_val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_SPI_SLAVE1 ,temp_addr,temp_val);
        // adi_dm_Read(ADI_DM_DIGIMMIC_SPI_SLAVE2, temp_addr, &temp_val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_SPI_SLAVE2 ,temp_addr,temp_val);
        // adi_dm_Read(ADI_DM_DIGIMMIC_SPI_SLAVE3, temp_addr, &temp_val);
        // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_SPI_SLAVE3 ,temp_addr,temp_val);
        platform_error("FALUT_CHECK ERROR", res, __FILE__, __LINE__);
    }
    else
        printf("Error check : OK\n");


    /* uDMA Channel Test Viewer (will be removed later) */
    // printf("\n");
    // for(ii = 0; ii < 5; ii++)
    //     test_rfic_udma_set_read(0, ii);


    // adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000003); //trig 0, 1ch
    // printf("\n");
    // for(ii = 0; ii < 5; ii++)
    //     test_rfic_udma_set_read(0, ii);
    
    // adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0xF0004010, &temp_val);
    // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0xF0004010,temp_val);
    // adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0xF0020210, &temp_val);
    // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0xF0020210,temp_val);

    // adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000003); //trig 0, 1ch
    // printf("\n");
    // for(ii = 0; ii < 5; ii++)
    //     test_rfic_udma_set_read(0, ii);

    // adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0xF0004010, &temp_val);
    // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0xF0004010,temp_val);
    // adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0xF0020210, &temp_val);
    // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0xF0020210,temp_val);

    // adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000003); //trig 0, 1ch
    // printf("\n");
    // for(ii = 0; ii < 5; ii++)
    //     test_rfic_udma_set_read(0, ii);

    // adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0xF0004010, &temp_val);
    // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0xF0004010,temp_val);
    // adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0xF0020210, &temp_val);
    // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0xF0020210,temp_val);

    // adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000003); //trig 0, 1ch
    // printf("\n");
    // for(ii = 0; ii < 5; ii++)
    //     test_rfic_udma_set_read(0, ii);

    // adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0xF0004010, &temp_val);
    // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0xF0004010,temp_val);
    // adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0xF0020210, &temp_val);
    // printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0xF0020210,temp_val);

    // adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000010); //trig 4ch
    // printf("\n");
    // for(ii = 0; ii < 5; ii++)
    //     test_rfic_udma_set_read(0, ii);
    bts_rfic_udma_scan_all(0,0x8000894C);
}

void bts_rfic_udma_scan_all(int select_device, int final_addr)
{
    uint32_t temp_addr, temp_val;

    temp_addr = 0x80008600;
    while(temp_addr <= final_addr)
    {
        adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, temp_addr, &temp_val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,temp_addr,temp_val);
        temp_addr = temp_addr + 4;
    }
}

adi_dm_err_t bts_rfic_udma_ch_put(int select_device, uint32_t* addr, bts_afi910_rfic_udma_ch_set_t ch_setting)
{
    adi_dm_err_t ret;
    put_init(select_device);
    put_word(addr, ch_setting.src_addr   );
    put_word(addr, ch_setting.dest_addr  );
    put_word(addr, ch_setting.udma_ch_cfg);
    put_word(addr, ch_setting.reserved   );
    ret = put_flush();
    return ret;
}

//testing....

void test_rfic_udma_test0(void) // test basic uDMA operation (Peripheral Scatter-Gather DMA)
{
    int ii;         // temp index for loops
    uint32_t write_addr;
    uint32_t temp_val;
    uint32_t temp_addr;

    bts_afi910_rfic_udma_ch_set_t ch0_pri, ch0_alt_task0, ch0_alt_task1;

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0);
    
    // Set ch0 uDMA
    ch0_pri.src_addr    = 0x8000861C;
    ch0_pri.dest_addr   = 0x8000850C;
    ch0_pri.udma_ch_cfg = 0x8A008076;
    ch0_pri.reserved    = 0x00000000;

    ch0_alt_task0.src_addr    = 0x8000861C;
    ch0_alt_task0.dest_addr   = 0x8000862C;
    ch0_alt_task0.udma_ch_cfg = 0x8A008037;
    ch0_alt_task0.reserved    = 0x00000000;

    ch0_alt_task1.src_addr    = 0x8000860C;
    ch0_alt_task1.dest_addr   = 0x8000862C;
    ch0_alt_task1.udma_ch_cfg = 0x8A008037;
    ch0_alt_task1.reserved    = 0x00000000;
    
    put_init(ADI_DM_ALL_DIGIMMICS);

    write_addr = 0x80008400;
    put_word(&write_addr, ch0_pri.src_addr);
    put_word(&write_addr, ch0_pri.dest_addr);
    put_word(&write_addr, ch0_pri.udma_ch_cfg);
    put_word(&write_addr, ch0_pri.reserved);

    write_addr = 0x80008600;
    put_word(&write_addr, ch0_alt_task0.src_addr);
    put_word(&write_addr, ch0_alt_task0.dest_addr);
    put_word(&write_addr, ch0_alt_task0.udma_ch_cfg);
    put_word(&write_addr, ch0_alt_task0.reserved);

    put_word(&write_addr, ch0_alt_task1.src_addr);
    put_word(&write_addr, ch0_alt_task1.dest_addr);
    put_word(&write_addr, ch0_alt_task1.udma_ch_cfg);
    put_word(&write_addr, ch0_alt_task1.reserved);    

    put_flush();

    // read uDMA software request reg
    temp_addr = 0x80001014;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",0 ,temp_addr,temp_val);

    // write uDMA software request reg
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000001);

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0);
    
    printf("check for memory area I wrote before in Master device\n");
    for(ii =0; ii < 16; ii++)
    {
        adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0x80008600+ii*4, &temp_val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0x80008600+ii*4,temp_val);
    }

    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000001);

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0);


    printf("check for memory area I wrote before in Master device\n");
    for(ii =0; ii < 16; ii++)
    {
        adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0x80008600+ii*4, &temp_val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0x80008600+ii*4,temp_val);
    }


}


void test_rfic_udma_test1(void) // test Alt setting & Trigger operation (Peripheral Scatter-Gather DMA)
{
    int ii;         // temp index for loops
    uint32_t write_addr;
    uint32_t temp_val;
    uint32_t temp_addr;
    uint32_t udma_mux0, udma_mux1;

    bts_afi910_rfic_udma_ch_set_t ch0_pri, ch0_alt_task0, ch0_alt_task1, ch1_pri;

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0);
    
    // Set ch0 uDMA
    ch0_pri.src_addr    = 0x8000861C;
    ch0_pri.dest_addr   = 0x8000850C;
    ch0_pri.udma_ch_cfg = 0x8A008074;
    ch0_pri.reserved    = 0x00000000;

    ch0_alt_task0.src_addr    = 0x8000860C;
    ch0_alt_task0.dest_addr   = 0x8000862C;
    ch0_alt_task0.udma_ch_cfg = 0x8A008031;
    ch0_alt_task0.reserved    = 0x00000000;

    ch0_alt_task1.src_addr    = 0x8000861C;
    ch0_alt_task1.dest_addr   = 0x8000862C;
    ch0_alt_task1.udma_ch_cfg = 0x8A008031;
    ch0_alt_task1.reserved    = 0x00000000;

    ch1_pri.src_addr    = 0x8000862C;
    ch1_pri.dest_addr   = 0x8000863C;
    ch1_pri.udma_ch_cfg = 0x8A008031;
    ch1_pri.reserved    = 0x00000000;
    
    put_init(ADI_DM_ALL_DIGIMMICS);

    write_addr = 0x80008400;
    put_word(&write_addr, ch0_pri.src_addr);
    put_word(&write_addr, ch0_pri.dest_addr);
    put_word(&write_addr, ch0_pri.udma_ch_cfg);
    put_word(&write_addr, ch0_pri.reserved);

    put_word(&write_addr, ch1_pri.src_addr);
    put_word(&write_addr, ch1_pri.dest_addr);
    put_word(&write_addr, ch1_pri.udma_ch_cfg);
    put_word(&write_addr, ch1_pri.reserved);

    write_addr = 0x80008600;
    put_word(&write_addr, ch0_alt_task0.src_addr);
    put_word(&write_addr, ch0_alt_task0.dest_addr);
    put_word(&write_addr, ch0_alt_task0.udma_ch_cfg);
    put_word(&write_addr, ch0_alt_task0.reserved);

    put_word(&write_addr, ch0_alt_task1.src_addr);
    put_word(&write_addr, ch0_alt_task1.dest_addr);
    put_word(&write_addr, ch0_alt_task1.udma_ch_cfg);
    put_word(&write_addr, ch0_alt_task1.reserved);    

    put_flush();

    // read uDMA peripheral Trigger mux reg
    temp_addr = REG_MISC_MISC_UDMA_REQ_MUX_SEL_0;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",0 ,temp_addr,temp_val);
    udma_mux0 = temp_val;
    temp_addr = REG_MISC_MISC_UDMA_REQ_MUX_SEL_1;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",0 ,temp_addr,temp_val);
    udma_mux1 = temp_val;
    // change uDMA peripheral Trigger setting
    udma_mux0 = udma_mux0 & 0xFFFFFF0F;  // Set Channel 1 trigger = dma_done[0;
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MISC_MISC_UDMA_REQ_MUX_SEL_0, udma_mux0);
    // check uDMA peripheral Trigger mux reg
    temp_addr = REG_MISC_MISC_UDMA_REQ_MUX_SEL_0;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",0 ,temp_addr,temp_val);
    temp_addr = REG_MISC_MISC_UDMA_REQ_MUX_SEL_1;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",0 ,temp_addr,temp_val);






    temp_addr = REG_UDMA_CHNL_DONT_CLEAR_EN_AT_DONE_SET;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of REG_UDMA_CHNL_DONT_CLEAR_EN_AT_DONE_SET is : 0x%08X\n",0 ,temp_val);
    temp_val = 0x00000002;
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_CHNL_DONT_CLEAR_EN_AT_DONE_SET, temp_val);

    temp_addr = REG_UDMA_EN_SET;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of REG_UDMA_EN_SET is : 0x%08X\n",0 ,temp_val);
    temp_val = 0x00000002;
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_EN_SET, temp_val);


    printf("check for memory area I wrote before in Master device\n");
    for(ii =0; ii < 16; ii++)
    {
        adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0x80008600+ii*4, &temp_val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0x80008600+ii*4,temp_val);
    }

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 1);
    // write uDMA software request reg
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000001);

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0);
    
    printf("check for memory area I wrote before in Master device\n");
    for(ii =0; ii < 16; ii++)
    {
        adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0x80008600+ii*4, &temp_val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0x80008600+ii*4,temp_val);
    }

    // temp_addr = 0x80008418;
    // adi_dm_Write(ADI_DM_ALL_DIGIMMICS, temp_addr, ch1_pri.udma_ch_cfg);

    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000001);

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0);


    printf("check for memory area I wrote before in Master device\n");
    for(ii =0; ii < 16; ii++)
    {
        adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0x80008600+ii*4, &temp_val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0x80008600+ii*4,temp_val);
    }

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 1);

    temp_addr = REG_UDMA_ERR_CLR;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of REG_UDMA_ERR_CLR is : 0x%08X\n",0 ,temp_val);

    temp_addr = REG_UDMA_ERRCHNL_CLR;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of REG_UDMA_ERRCHNL_CLR is : 0x%08X\n",0 ,temp_val);

    temp_addr = REG_UDMA_INVALIDDESC_CLR;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of REG_UDMA_INVALIDDESC_CLR is : 0x%08X\n",0 ,temp_val);


}


void test_rfic_udma_test2(void) // uDMA Priority test (Peripheral Scatter-Gather DMA)
{
    int ii;         // temp index for loops
    uint32_t write_addr;
    uint32_t temp_val;
    uint32_t temp_addr;
    uint32_t udma_mux0, udma_mux1;

    bts_afi910_rfic_udma_ch_set_t ch0_pri, ch0_alt_task0, ch0_alt_task1, ch1_pri;

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0);
    
    // Set ch0 uDMA
    ch0_pri.src_addr    = 0x8000861C;
    ch0_pri.dest_addr   = 0x8000850C;
    ch0_pri.udma_ch_cfg = 0x8A008076;
    ch0_pri.reserved    = 0x00000000;

    ch0_alt_task0.src_addr    = 0x8000860C;
    ch0_alt_task0.dest_addr   = 0x8000862C;
    ch0_alt_task0.udma_ch_cfg = 0x8A008031;
    ch0_alt_task0.reserved    = 0x00000000;

    ch0_alt_task1.src_addr    = 0x8000861C;
    ch0_alt_task1.dest_addr   = 0x8000862C;
    ch0_alt_task1.udma_ch_cfg = 0x8A008031;
    ch0_alt_task1.reserved    = 0x00000000;

    ch1_pri.src_addr    = 0x8000862C;
    ch1_pri.dest_addr   = 0x8000863C;
    ch1_pri.udma_ch_cfg = 0x8A008031;
    ch1_pri.reserved    = 0x00000000;
    
    put_init(ADI_DM_ALL_DIGIMMICS);

    write_addr = 0x80008400;
    put_word(&write_addr, ch0_pri.src_addr);
    put_word(&write_addr, ch0_pri.dest_addr);
    put_word(&write_addr, ch0_pri.udma_ch_cfg);
    put_word(&write_addr, ch0_pri.reserved);

    put_word(&write_addr, ch1_pri.src_addr);
    put_word(&write_addr, ch1_pri.dest_addr);
    put_word(&write_addr, ch1_pri.udma_ch_cfg);
    put_word(&write_addr, ch1_pri.reserved);

    write_addr = 0x80008600;
    put_word(&write_addr, ch0_alt_task0.src_addr);
    put_word(&write_addr, ch0_alt_task0.dest_addr);
    put_word(&write_addr, ch0_alt_task0.udma_ch_cfg);
    put_word(&write_addr, ch0_alt_task0.reserved);

    put_word(&write_addr, ch0_alt_task1.src_addr);
    put_word(&write_addr, ch0_alt_task1.dest_addr);
    put_word(&write_addr, ch0_alt_task1.udma_ch_cfg);
    put_word(&write_addr, ch0_alt_task1.reserved);    

    put_flush();

    // read uDMA peripheral Trigger mux reg
    temp_addr = REG_MISC_MISC_UDMA_REQ_MUX_SEL_0;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",0 ,temp_addr,temp_val);
    udma_mux0 = temp_val;
    temp_addr = REG_MISC_MISC_UDMA_REQ_MUX_SEL_1;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",0 ,temp_addr,temp_val);
    udma_mux1 = temp_val;
    // change uDMA peripheral Trigger setting
    udma_mux0 =  0xFFFFFFFF;  // Set Channel 1 trigger = dma_done[0;
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MISC_MISC_UDMA_REQ_MUX_SEL_0, udma_mux0);
    // check uDMA peripheral Trigger mux reg
    temp_addr = REG_MISC_MISC_UDMA_REQ_MUX_SEL_0;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",0 ,temp_addr,temp_val);
    temp_addr = REG_MISC_MISC_UDMA_REQ_MUX_SEL_1;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",0 ,temp_addr,temp_val);




    printf("check for memory area I wrote before in Master device\n");
    for(ii =0; ii < 16; ii++)
    {
        adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0x80008600+ii*4, &temp_val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0x80008600+ii*4,temp_val);
    }

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 1);
    // write uDMA software request reg
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000003);

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0);
    
    printf("check for memory area I wrote before in Master device\n");
    for(ii =0; ii < 16; ii++)
    {
        adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0x80008600+ii*4, &temp_val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0x80008600+ii*4,temp_val);
    }

    temp_addr = 0x80008418;
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, temp_addr, ch1_pri.udma_ch_cfg);

    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000003);

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0);


    printf("check for memory area I wrote before in Master device\n");
    for(ii =0; ii < 16; ii++)
    {
        adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0x80008600+ii*4, &temp_val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0x80008600+ii*4,temp_val);
    }

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 1);

    temp_addr = REG_UDMA_ERR_CLR;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of REG_UDMA_ERR_CLR is : 0x%08X\n",0 ,temp_val);

    temp_addr = REG_UDMA_ERRCHNL_CLR;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of REG_UDMA_ERRCHNL_CLR is : 0x%08X\n",0 ,temp_val);

    temp_addr = REG_UDMA_INVALIDDESC_CLR;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of REG_UDMA_INVALIDDESC_CLR is : 0x%08X\n",0 ,temp_val);


}


void test_rfic_udma_test3(void) // uDMA config test(src_inc = none)
{
    int ii;         // temp index for loops
    uint32_t write_addr;
    uint32_t temp_val;
    uint32_t temp_addr;
    uint32_t udma_mux0, udma_mux1;

    bts_afi910_rfic_udma_ch_set_t ch0_pri, ch0_alt_task0, ch0_alt_task1, ch1_pri;

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0);
    
    // Set ch0 uDMA
    ch0_pri.src_addr    = 0x80008618;
    ch0_pri.dest_addr   = 0x8000850C;
    ch0_pri.udma_ch_cfg = 0x8E008076;
    ch0_pri.reserved    = 0x00000000;

    ch0_alt_task0.src_addr    = 0x8000860C;
    ch0_alt_task0.dest_addr   = 0x8000862C;
    ch0_alt_task0.udma_ch_cfg = 0x8A008031;
    ch0_alt_task0.reserved    = 0x00000000;

    ch0_alt_task1.src_addr    = 0x8000861C;
    ch0_alt_task1.dest_addr   = 0x8000862C;
    ch0_alt_task1.udma_ch_cfg = 0x8A008031;
    ch0_alt_task1.reserved    = 0x00000000;

    ch1_pri.src_addr    = 0x8000862C;
    ch1_pri.dest_addr   = 0x8000863C;
    ch1_pri.udma_ch_cfg = 0x8A008031;
    ch1_pri.reserved    = 0x00000000;
    
    put_init(ADI_DM_ALL_DIGIMMICS);

    write_addr = 0x80008400;
    put_word(&write_addr, ch0_pri.src_addr);
    put_word(&write_addr, ch0_pri.dest_addr);
    put_word(&write_addr, ch0_pri.udma_ch_cfg);
    put_word(&write_addr, ch0_pri.reserved);

    put_word(&write_addr, ch1_pri.src_addr);
    put_word(&write_addr, ch1_pri.dest_addr);
    put_word(&write_addr, ch1_pri.udma_ch_cfg);
    put_word(&write_addr, ch1_pri.reserved);

    write_addr = 0x80008600;
    put_word(&write_addr, ch0_alt_task0.src_addr);
    put_word(&write_addr, ch0_alt_task0.dest_addr);
    put_word(&write_addr, ch0_alt_task0.udma_ch_cfg);
    put_word(&write_addr, ch0_alt_task0.reserved);

    put_word(&write_addr, ch0_alt_task1.src_addr);
    put_word(&write_addr, ch0_alt_task1.dest_addr);
    put_word(&write_addr, ch0_alt_task1.udma_ch_cfg);
    put_word(&write_addr, ch0_alt_task1.reserved);    

    put_flush();

    // read uDMA peripheral Trigger mux reg
    temp_addr = REG_MISC_MISC_UDMA_REQ_MUX_SEL_0;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",0 ,temp_addr,temp_val);
    udma_mux0 = temp_val;
    temp_addr = REG_MISC_MISC_UDMA_REQ_MUX_SEL_1;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",0 ,temp_addr,temp_val);
    udma_mux1 = temp_val;
    // change uDMA peripheral Trigger setting
    udma_mux0 =  0xFFFFFFFF;  // Set Channel 1 trigger = dma_done[0;
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_MISC_MISC_UDMA_REQ_MUX_SEL_0, udma_mux0);
    // check uDMA peripheral Trigger mux reg
    temp_addr = REG_MISC_MISC_UDMA_REQ_MUX_SEL_0;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",0 ,temp_addr,temp_val);
    temp_addr = REG_MISC_MISC_UDMA_REQ_MUX_SEL_1;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",0 ,temp_addr,temp_val);




    printf("check for memory area I wrote before in Master device\n");
    for(ii =0; ii < 16; ii++)
    {
        adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0x80008600+ii*4, &temp_val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0x80008600+ii*4,temp_val);
    }

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 1);
    // write uDMA software request reg
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000001);

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0);
    
    printf("check for memory area I wrote before in Master device\n");
    for(ii =0; ii < 16; ii++)
    {
        adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0x80008600+ii*4, &temp_val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0x80008600+ii*4,temp_val);
    }

    temp_addr = 0x80008418;
    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, temp_addr, ch1_pri.udma_ch_cfg);

    adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 0x00000001);

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0);


    printf("check for memory area I wrote before in Master device\n");
    for(ii =0; ii < 16; ii++)
    {
        adi_dm_Read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 0x80008600+ii*4, &temp_val);
        printf("In #%d device, the value of the register(0x%08X) is : 0x%08X\n",ADI_DM_DIGIMMIC_MASTER_SPI_ADDR ,0x80008600+ii*4,temp_val);
    }

    test_rfic_udma_set_read(ADI_DM_DIGIMMIC_MASTER_SPI_ADDR, 1);

    temp_addr = REG_UDMA_ERR_CLR;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of REG_UDMA_ERR_CLR is : 0x%08X\n",0 ,temp_val);

    temp_addr = REG_UDMA_ERRCHNL_CLR;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of REG_UDMA_ERRCHNL_CLR is : 0x%08X\n",0 ,temp_val);

    temp_addr = REG_UDMA_INVALIDDESC_CLR;
    adi_dm_Read(0, temp_addr, &temp_val);
    printf("In #%d device, the value of REG_UDMA_INVALIDDESC_CLR is : 0x%08X\n",0 ,temp_val);


}


adi_dm_err_t bts_dm_ramp_config(const adi_dm_ramp_config_t * p, const adi_dm_builtin_mimo_setup_t * builtin_mimo)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    uint32_t mask, bits;

    // printf("--> Entering function adi_dm_ramp_config\n");

    // /* Set misc_filter_ctrl */
    // mask = ~UINT32_C(0);
    // bits = UINT32_C(0);
    // mask &= ~BITM_MISC_MISC_FILTER_CTRL_FILTER_DECIM_RATIO;
    // bits |= p->filter_decim_ratio << BITP_MISC_MISC_FILTER_CTRL_FILTER_DECIM_RATIO;
    // res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_MISC_MISC_FILTER_CTRL, mask, bits);
    // if (res != ADI_DM_SUCCESS)
    //     return res;

    // /* Set misc_filter_ctrl_1 */
    // mask = ~UINT32_C(0);
    // bits = UINT32_C(0);
    // mask &= ~BITM_MISC_MISC_FILTER_CTRL_1_FILTER_VALID_DELAY;
    // bits |= p->filter_valid_delay << BITP_MISC_MISC_FILTER_CTRL_1_FILTER_VALID_DELAY;
    // res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_MISC_MISC_FILTER_CTRL_1, mask, bits);
    // if (res != ADI_DM_SUCCESS)
    //     return res;

    // for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        /* ramp_config3 */
        // mask = ~UINT32_C(0);
        // bits = UINT32_C(0);
        // mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_EN;
        // bits |= (p->pga_shunt_en << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_EN) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_EN;
        // mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_START_DEL;
        // bits |= (p->pga_shunt_start_del << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_START_DEL) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_START_DEL;
        // mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_STOP_DEL;
        // bits |= (p->pga_shunt_stop_del << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_STOP_DEL) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_PGA_SHUNT_STOP_DEL;
        // mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_VGA_GAUSS_DIS;
        // bits |= (p->dm[dm_num].vga_gauss_dis << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG3_VGA_GAUSS_DIS) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG3_VGA_GAUSS_DIS;
        // res = adi_dm_RMW(ADI_DM_ALL_DIGIMMICS, REG_RF_ADPLL_RFPLL_RAMP_CONFIG3, mask, bits);
        // if (res != ADI_DM_SUCCESS)
        //     return res;

        /* ramp_config2 */
        mask = ~UINT32_C(0);
        bits = UINT32_C(0);
        if (builtin_mimo == NULL) {
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ;
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ_LEN;
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_MODE_EN;
        } else {
            uint32_t mimo_seq_val, mimo_seq_len;
            if (builtin_mimo->mimo_seq_len > 0) {
                mimo_seq_val = builtin_mimo->dm[ADI_DM_MASTER].mimo_seq_val;
                mimo_seq_len = builtin_mimo->mimo_seq_len;
            } else {
                mimo_seq_val = builtin_mimo->ramp_profile.dm[ADI_DM_MASTER].tx_pattern;
                mimo_seq_len = 1UL;
            }
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ;
            bits |= (mimo_seq_val << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ;
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ_LEN;
            bits |= (mimo_seq_len << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ_LEN) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_SEQ_LEN;
            mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_MODE_EN;
            bits |= BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_MIMO_MODE_EN;
        }
        mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_RAMP_COUNT;
        bits |= (p->ramp_count << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG2_RAMP_COUNT) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG2_RAMP_COUNT;
        // res = adi_dm_RMW(dm_num, REG_RF_ADPLL_RFPLL_RAMP_CONFIG2, mask, bits);
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_RF_ADPLL_RFPLL_RAMP_CONFIG2, bits);
        if (res != ADI_DM_SUCCESS)
            return res;

        /* ramp_config1 */
        // mask = ~UINT32_C(0);
        // bits = UINT32_C(0);
        // mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_ON_PATT;
        // bits |= (p->dm[dm_num].vga_on_patt << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_ON_PATT) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_ON_PATT;
        // mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_DELAY_EN;
        // bits |= (p->dm[dm_num].phase_delay_en << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_DELAY_EN) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_DELAY_EN;
        // mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_MOD_EN;
        // bits |= (p->dm[dm_num].phase_mod_en << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_MOD_EN) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PHASE_MOD_EN;
        // mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA_OFF_TIME;
        // bits |= (p->dm[dm_num].pa_off_time << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA_OFF_TIME) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_PA_OFF_TIME;
        // mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEPS;
        // bits |= (p->dm[dm_num].vga_gain_steps << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEPS) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEPS;
        // mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEP_DIV;
        // bits |= (p->dm[dm_num].vga_gain_step_div << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEP_DIV) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG1_VGA_GAIN_STEP_DIV;
        // res = adi_dm_RMW(dm_num, REG_RF_ADPLL_RFPLL_RAMP_CONFIG1, mask, bits);
        // if (res != ADI_DM_SUCCESS)
        //     return res;

        /* ramp_config0 */
        // mask = ~UINT32_C(0);
        // bits = UINT32_C(0);
        // mask &= ~BITM_RF_ADPLL_RFPLL_RAMP_CONFIG0_VGA_SYNC_DATA_VALID;
        // bits |= (p->dm[dm_num].vga_sync_data_valid << BITP_RF_ADPLL_RFPLL_RAMP_CONFIG0_VGA_SYNC_DATA_VALID) & BITM_RF_ADPLL_RFPLL_RAMP_CONFIG0_VGA_SYNC_DATA_VALID;
        // res = adi_dm_RMW(dm_num, REG_RF_ADPLL_RFPLL_RAMP_CONFIG0, mask, bits);
        // if (res != ADI_DM_SUCCESS)
        //     return res;
    // }

    // printf("--> Leaving function adi_dm_ramp_config\n");
    return ADI_DM_SUCCESS;
}



adi_dm_err_t bts_dm_DmaRampSetup(const adi_dm_dma_ramp_setup_t * p)
{
    adi_dm_err_t res;
    const uint32_t word_size = DMA_WORD_SIZE;
    const uint32_t chan_ctrl_size = DMA_CHAN_CTRL_SIZE;
    uint32_t prim_chan_ctrl = DMA_RAMPGEN_CHAN_SRC_PTR;
    uint32_t xfers = 12;
    uint32_t last_word_prim_chan_ctrl = prim_chan_ctrl + chan_ctrl_size - word_size;
    uint32_t last_word_alt_chan_ctrl = last_word_prim_chan_ctrl + 0x100;

    // printf("-->> Entering function adi_dm_DmaRampSetup\n");

    res = bts_dm_ramp_config(&p->ramp_config, NULL);
    if (res != ADI_DM_SUCCESS) {
        return res;
    }
    /*
     * Initialize primary channel control data in scatter gather mode.
     */
    uint32_t loc = prim_chan_ctrl;
    put_init(ADI_DM_ALL_DIGIMMICS);
    put_word(&loc, p->bpid);    /* src_ptr */
    put_word(&loc, last_word_alt_chan_ctrl);    /* dst_ptr */
    put_word(&loc, UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_PRI | UDMA_CTRL_CFG_DSTINC_WORD    /* increment dst_ptr */
             | UDMA_CTRL_CFG_SRCINC_WORD        /* increment src_ptr */
             | UDMA_CTRL_CFG_SRC_SIZE_WORD      /* transfer 4 bytes at a time */
             | UDMA_CTRL_CFG_R_POWER_X4 /* arbitrate after 4 transfers */
             | UDMA_CTRL_CFG_TRANSFERS(xfers)); /* total transfers */
    put_word(&loc, 0);
    res = put_flush();
    if (res != ADI_DM_SUCCESS)
        return res;

    // res = initialize_dma_chan(DMA_RAMPGEN_CHAN_NO, 11 /* a chan we never enable */ );
    // if (res != ADI_DM_SUCCESS)
    //     return res;
    // res = initialize_dma_chan(DMA_RAMPGEN_CHAN_NO + 1, DMA_RAMPGEN_CHAN_NO + 1);        /* triggered by rg_dma_en */
    // if (res != ADI_DM_SUCCESS)
    //     return res;
    // res = initialize_dma_chan(DMA_RAMPGEN_CHAN_NO + 2, DMA_RAMPGEN_CHAN_NO + 1);        /* triggered by dma_done[1] */
    // if (res != ADI_DM_SUCCESS)
    //     return res;
    // res = initialize_dma_chan(DMA_RAMPGEN_CHAN_NO + 3, DMA_RAMPGEN_CHAN_NO + 2);        /* triggered by dma_done[2] */
    /* Issue software request to load primary channel control and then first ramp profile */
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 3 << DMA_RAMPGEN_CHAN_NO);
    if (res != ADI_DM_SUCCESS)
        return res;

    // if (adi_dm_enable_trigger_pin_on_program) {
    //     /* BIST49 explicit control of when external trigger is allowed
    //      * for compatible with past APIs the trig pin is enabled as soon
    //      * as the ramp is programmed.
    //      */
    //     printf("ADI_ADAR690x_FW_EXT_TRIG_EN\n");
    //     res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_EXT_TRIG_EN);
    //     if (res != ADI_DM_SUCCESS)
    //         return res;
    // }

    // printf("-->> Exiting function adi_dm_DmaRampSetup\n");

    return ADI_DM_SUCCESS;
}

adi_dm_err_t bts_dm_DmaRampSetup_optimize(const adi_dm_dma_ramp_setup_t * p)
{
    adi_dm_err_t res;
    const uint32_t word_size = DMA_WORD_SIZE;
    const uint32_t chan_ctrl_size = DMA_CHAN_CTRL_SIZE;
    uint32_t prim_chan_ctrl = DMA_RAMPGEN_CHAN_SRC_PTR;
    uint32_t xfers = 12;
    uint32_t last_word_prim_chan_ctrl = prim_chan_ctrl + chan_ctrl_size - word_size;
    uint32_t last_word_alt_chan_ctrl = last_word_prim_chan_ctrl + 0x100;

    struct timeval startTime, endTime;
    double diffTime;

    struct timeval startTime_rampconfig, endTime_rampconfig;
    double diffTime_rampconfig;

    struct timeval startTime_write, endTime_write;
    double diffTime_write;

    gettimeofday(&startTime, NULL);

    // printf("-->> Entering function adi_dm_DmaRampSetup\n");

    gettimeofday(&startTime_rampconfig, NULL);
    res = bts_dm_ramp_config(&p->ramp_config, NULL);
    if (res != ADI_DM_SUCCESS) {
        return res;
    }
    gettimeofday(&endTime_rampconfig, NULL);
    diffTime_rampconfig = endTime_rampconfig.tv_sec + endTime_rampconfig.tv_usec / 1000000.0 - startTime_rampconfig.tv_sec - startTime_rampconfig.tv_usec / 1000000.0;
    //printf("\t1) bts_dm_ramp_config takes %lf ms\n", diffTime_rampconfig * 1000);
    //printf("==============111111111111111111111========================== \n");
    /*
     * Initialize primary channel control data in scatter gather mode.
     */
    uint32_t loc = prim_chan_ctrl;
    put_init(ADI_DM_ALL_DIGIMMICS);
    put_word(&loc, p->bpid);    /* src_ptr */
    put_word(&loc, last_word_alt_chan_ctrl);    /* dst_ptr */
    put_word(&loc, UDMA_CTRL_CFG_CYC_CTRL_MEM_SCATTER_GATHER_PRI | UDMA_CTRL_CFG_DSTINC_WORD    /* increment dst_ptr */
             | UDMA_CTRL_CFG_SRCINC_WORD        /* increment src_ptr */
             | UDMA_CTRL_CFG_SRC_SIZE_WORD      /* transfer 4 bytes at a time */
             | UDMA_CTRL_CFG_R_POWER_X4 /* arbitrate after 4 transfers */
             | UDMA_CTRL_CFG_TRANSFERS(xfers)); /* total transfers */
    put_word(&loc, 0);
    res = put_flush();
    if (res != ADI_DM_SUCCESS)
        return res;
   // printf("==============222222222222222222222222222222========================== \n");

    // res = initialize_dma_chan(DMA_RAMPGEN_CHAN_NO, 11 /* a chan we never enable */ );
    // if (res != ADI_DM_SUCCESS)
    //     return res;
    // res = initialize_dma_chan(DMA_RAMPGEN_CHAN_NO + 1, DMA_RAMPGEN_CHAN_NO + 1);        /* triggered by rg_dma_en */
    // if (res != ADI_DM_SUCCESS)
    //     return res;
    // res = initialize_dma_chan(DMA_RAMPGEN_CHAN_NO + 2, DMA_RAMPGEN_CHAN_NO + 1);        /* triggered by dma_done[1] */
    // if (res != ADI_DM_SUCCESS)
    //     return res;
    // res = initialize_dma_chan(DMA_RAMPGEN_CHAN_NO + 3, DMA_RAMPGEN_CHAN_NO + 2);        /* triggered by dma_done[2] */
    /* Issue software request to load primary channel control and then first ramp profile */
    gettimeofday(&startTime_write, NULL);
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 3 << DMA_RAMPGEN_CHAN_NO);
    if (res != ADI_DM_SUCCESS)
        return res;
    //printf("==============3333333333333333333333333333333========================== \n");
    gettimeofday(&endTime_write, NULL);
    diffTime_write = endTime_write.tv_sec + endTime_write.tv_usec / 1000000.0 - startTime_write.tv_sec - startTime_write.tv_usec / 1000000.0;
    //printf("\t2) adi_dm_Write takes %lf ms\n", diffTime_write * 1000);
    // if (adi_dm_enable_trigger_pin_on_program) {
    //     /* BIST49 explicit control of when external trigger is allowed
    //      * for compatible with past APIs the trig pin is enabled as soon
    //      * as the ramp is programmed.
    //      */
    //     printf("ADI_ADAR690x_FW_EXT_TRIG_EN\n");
    //     res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_EXT_TRIG_EN);
    //     if (res != ADI_DM_SUCCESS)
    //         return res;
    // }

    // printf("-->> Exiting function adi_dm_DmaRampSetup\n");
    gettimeofday(&endTime, NULL);
    diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
    //printf("\t3) bts_dm_DmaRampSetup_optimize takes %lf ms\n", diffTime * 1000);
    return ADI_DM_SUCCESS;
}