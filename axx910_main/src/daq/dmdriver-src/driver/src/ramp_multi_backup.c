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

#include "adi_dmdriver.h"
#include "localdefs.h"
#include "adar690x_regs.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

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

static void put_word(uint32_t * addr, uint32_t value);
static adi_dm_err_t put_flush(void);
static void put_init(adi_dm_num_t);
static void put_ramp_profile(uint32_t * addr, adi_dm_ramp_profile_t * ramp);
static adi_dm_err_t overwite_slave_ramp_profiles(uint32_t * addr, adi_dm_ramp_profile_t * ramp);
static adi_dm_err_t initialize_dma_chan(uint32_t channel_no, uint32_t fldval);

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
 * * Channel 0, switches burst profiles
 *   * Triggered by software
 *   * Memory scatter-gather:
 *     * task 0: loads channel 1,2,3 primary channel control
 *     * task 1: enables or disables channels 2 and 3
 *     * task 2: loads channel 0 primary channel control
 * * Channel 1, loads ramp profiles
 *   * Triggered by software and rg_dma_en
 *   * Memory scatter-gather:
 *     * task 0.0: loads RAMPGEN registers, from ramp profile 0
 *     * task 0.1: loads channel 1 primary channel control for task 1.0
 *     * ...
 *     * task n.0: loads RAMPGEN registers, from ramp profile n
 *     * task n.1: loads channel 1 primary channel control for task 0.0
 * * Channel 2, loads RAMP_GEN_TX
 *   * Triggered by dma_done[1]
 *   * Basic mode
 *     * Load 1 word to RAMP_GEN_TX, arbitrate
 * * Channel 3, resets channel 2
 *   * Triggered by dma_done[2]
 *   * Memory scatter-gather:
 *     * task 0: loads channel 2 primary channel control
 *     * task 1: loads channel 3 primary channel control
 */

/**
 * Initialise memory resident data used to drive the DMA
 */
adi_dm_err_t adi_dm_BurstProfileSetup(const adi_dm_burst_profile_t * p, uint32_t * dma_mem_limit, uint32_t * bpid)
{
    adi_dm_err_t res;

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
    uint32_t prim_chan_ctrl = DMA_RAMPGEN_CHAN_SRC_PTR + chan_ctrl_size;
    uint32_t last_word_prim_chan_ctrl = prim_chan_ctrl + chan_ctrl_size - word_size;
    uint32_t last_word_alt_chan_ctrl = last_word_prim_chan_ctrl + 0x100;

    uint32_t prim_ch0_ctrl = DMA_RAMPGEN_CHAN_SRC_PTR;
    uint32_t last_word_prim_ch0_ctrl = prim_ch0_ctrl + chan_ctrl_size - word_size;
    uint32_t last_word_alt_ch0_ctrl = last_word_prim_ch0_ctrl + 0x100;
    uint32_t prim_ch2_ctrl = DMA_RAMPGEN_CHAN_SRC_PTR + (2 * chan_ctrl_size);
    uint32_t last_word_prim_ch2_ctrl = prim_ch2_ctrl + chan_ctrl_size - word_size;
    uint32_t prim_ch3_ctrl = DMA_RAMPGEN_CHAN_SRC_PTR + (3 * chan_ctrl_size);
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
    /*
     * Third section is ramp profiles
     */
    assert(loc == ramp_profiles);
    for (int i = 0; i < num_ramp_profiles; i++) {
        put_ramp_profile(&loc, &p->ramp_profile[i]);
    }

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

adi_dm_err_t adi_dm_DmaRampSetup(const adi_dm_dma_ramp_setup_t * p)
{
    adi_dm_err_t res;
    const uint32_t word_size = DMA_WORD_SIZE;
    const uint32_t chan_ctrl_size = DMA_CHAN_CTRL_SIZE;
    uint32_t prim_chan_ctrl = DMA_RAMPGEN_CHAN_SRC_PTR;
    uint32_t xfers = 12;
    uint32_t last_word_prim_chan_ctrl = prim_chan_ctrl + chan_ctrl_size - word_size;
    uint32_t last_word_alt_chan_ctrl = last_word_prim_chan_ctrl + 0x100;

    comment("-->> Entering function adi_dm_DmaRampSetup");

    res = adi_dm_ramp_config(&p->ramp_config, NULL);
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

    comment("-->> Exiting function adi_dm_DmaRampSetup");

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

/**
 * Set the current burst profile
 */
adi_dm_err_t adi_dm_SelectBurstProfile(uint32_t bpid)
{
    adi_dm_err_t res;

    comment("-->> Entering function adi_dm_SelectBurstProfile");
    /* the burst profile 'identifier' is just the channel src_ptr */
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, DMA_RAMPGEN_CHAN_SRC_PTR, bpid);
    if (res != ADI_DM_SUCCESS)
        return res;
    /* having changed the pointer, load primary channel control and then RAMPGEN with a software DMA request */
    res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, REG_UDMA_SWREQ, 3 << DMA_RAMPGEN_CHAN_NO);
    if (res != ADI_DM_SUCCESS)
        return res;
    comment("-->> Exiting function adi_dm_SelectBurstProfile");
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_TasklistPoolSetup(const adi_dm_tasklist_pool_setup_t * p, uint32_t * dma_mem_limit)
{
    adi_dm_err_t res;
    adi_dm_num_t dm_num;
    uint32_t pool_addr, highest_addr_accross_devices, i, j;
    uint32_t checksum, data_checksummed;

    comment("---> Entering function adi_dm_TasklistPoolSetup");

    if (*dma_mem_limit == 0) {
        *dma_mem_limit = DMA_MEMORY_START;
    }

    /* Calculate space . */
    pool_addr = *dma_mem_limit;
    highest_addr_accross_devices = pool_addr;
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        uint32_t addr = pool_addr;
        for (i = 0; i < p->num_tasklists; i++) {
            addr += p->tasklist_length[dm_num][i] * 4;
        }
        if (addr > highest_addr_accross_devices)
            highest_addr_accross_devices = addr;
    }
    /* Check data fits and record that space is in use. */
    if (highest_addr_accross_devices > DMA_MEMORY_START + DMA_MEMORY_SIZE) {
        comment("ERROR: not enough space for tasklist pool");
        return ADI_DM_PARAMETER_ERROR;
    }
    *dma_mem_limit = highest_addr_accross_devices;

    /* Write the entire tasklist pool */
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        uint32_t addr = pool_addr;
        put_init(dm_num);
        for (i = 0; i < p->num_tasklists; i++) {
            for (j = 0; j < p->tasklist_length[dm_num][i]; j++) {
                put_word(&addr, p->tasklists[dm_num][i][j]);
            }
        }
        /* Fill in rest of scheduler file with zeros */
        while (addr < highest_addr_accross_devices) {
            put_word(&addr, 0);
        }
        res = put_flush();
        if (res != ADI_DM_SUCCESS)
            return res;

        /* Fill in DMA area header.
         * There is obviously more functionality in the firmware than has been exposed,
         * or probably ever will be. This header contains pointers to various pools.
         * The only pool we actually use is the tasklist pool.
         * The header contains checksums used to check the integrity of the memory
         * we call the DMA area. The DMA structures above are also covered by the
         * checksums. Consequently:
         *   1. All calls to adi_dm_BurstProfileSetup should happen before adi_dm_TasklistPoolSetup.
         *   2. adi_dm_TasklistPoolSetup 'locks' memory by calculating checksums and calling ADI_ADAR690x_CMD_CONFIG_COMPLETE.
         *   4. Attempting to call a tasklist will fail unless ADI_ADAR690x_CMD_CONFIG_COMPLETE has been called.
         *   3. To 'unlock' memory and start again call (ADI_ADAR690x_CMD_CONFIG_COMPLETE|(1<<16)).
         */
        put_init(dm_num);
        addr = ADI_ADAR690x_DMA_AREA_BASE;

        put_word(&addr, 0xAD690);       /* magic */
        put_word(&addr, 1);     /* version */
        put_word(&addr, (highest_addr_accross_devices - ADI_ADAR690x_DMA_AREA_BASE) - 0x1C);    /* size of checksummed area */
        checksum = addr;
        put_word(&addr, 0);     /* checksum 0 */
        put_word(&addr, 0);     /* checksum 1 */
        put_word(&addr, 0);     /* checksum 2 */
        put_word(&addr, 0);     /* checksum 3 */
        data_checksummed = addr;
        assert(data_checksummed - ADI_ADAR690x_DMA_AREA_BASE == 0x1C);
        put_word(&addr, 0);     /* reserved 0 */
        put_word(&addr, 0);     /* reserved 1 */
        put_word(&addr, 0);     /* reserved 2 */
        put_word(&addr, 0);     /* reserved 3 */

        put_word(&addr, 0);     /* offset domain pool */
        put_word(&addr, 0);     /* num domains */
        put_word(&addr, 0);     /* offset cycle pool */
        put_word(&addr, 0);     /* num cycles */
        put_word(&addr, pool_addr - ADI_ADAR690x_DMA_AREA_BASE);        /* offset tasklist pool */
        put_word(&addr, p->num_tasklists);      /* num tasklists */
        put_word(&addr, 0);     /* offset burst pool */
        put_word(&addr, 0);     /* num bursts */
        put_word(&addr, 0);     /* offset profile pool */
        put_word(&addr, 0);     /* num profiles */
        put_word(&addr, 0);     /* offset overlay pool */
        put_word(&addr, 0);     /* num overlay structures */
        put_word(&addr, 0);     /* offset config register pool */
        put_word(&addr, 0);     /* num config registers */
        put_word(&addr, 0);     /* offset status register pool */
        put_word(&addr, 0);     /* num status registers */
        assert(addr <= DMA_MEMORY_START);
        res = put_flush();
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    /* Compute checksums using ADI_ADAR690x_FW_CRC_CHK
     * This incorporates all memory used for tasklists and
     * burst profiles in the downloaded scheduler file image.
     */
    do {
        uint32_t block_start = data_checksummed;
        uint32_t block_size = 4096;     /* crc block size */
        if (block_start + block_size > highest_addr_accross_devices) {
            block_size = highest_addr_accross_devices - block_start;
        }
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_CRC_USER_AREA_ADDR, block_start);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_CRC_USER_AREA_COUNT, block_size / 4);
        if (res != ADI_DM_SUCCESS)
            return res;
        res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CFG_CRC_GROUP_SELECT, 2);
        if (res != ADI_DM_SUCCESS)
            return res;
        comment("ADI_ADAR690x_FW_CRC_CHK");
        res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_CRC_CHK);
        if (res != ADI_DM_SUCCESS)
            return res;
        for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
            uint32_t crc;
            res = adi_dm_Read(dm_num, ADI_ADAR690x_STS_COMPUTED_CRC_GROUP1, &crc);
            if (res != ADI_DM_SUCCESS)
                return res;
            res = adi_dm_Write(dm_num, checksum, crc);
            if (res != ADI_DM_SUCCESS)
                return res;
        }
        checksum += 4;
        data_checksummed += block_size;
    } while (data_checksummed < highest_addr_accross_devices);

    /* Finally register the scheduler file just created on the fly */
    comment("ADI_ADAR690x_CMD_CONFIG_COMPLETE");
    res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_CMD_CONFIG_COMPLETE);
    if (res != ADI_DM_SUCCESS) {
        return res;
    }

    comment("---> Exiting function adi_dm_TasklistPoolSetup");

    return ADI_DM_SUCCESS;
}
