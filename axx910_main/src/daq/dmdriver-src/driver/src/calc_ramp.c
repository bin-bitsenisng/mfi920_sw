/* calc_ramp.c
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

#include "adi_dmdriver.h"
#include "localdefs.h"
#include <math.h>
#include <string.h>
#include <stdio.h>


static int ceil_local(float value, int significance);
static int frac_calc(int a, int b);
static double calc_adcpll_freq_hz(double ref_freq_hz);

adi_dm_err_t adi_dm_CalcRamp(const adi_dm_ramp_shape_t * in, adi_dm_ramp_profile_t * ramp_profile, adi_dm_ramp_config_t * ramp_config, adi_dm_actual_ramp_shape_t * actual)
{
    adi_dm_num_t dm_num;
    const float slope0_time_us = in->slope0_time_us;
    const float slope1_time_us = in->slope1_time_us;
    const float delay0_time_us = in->delay0_time_us;
    const float delay1_time_us = in->delay1_time_us;
    const float delay2_time_us = in->delay2_time_us;
    float ramp_bw_Mhz = in->ramp_bw_Mhz;
    const uint32_t num_samples = in->num_samples;
    const float sample_start_time_us = in->sample_start_time_us;
    bool pga_shunt_en = in->pga_shunt_en;
    float pga_shunt_start_del_us = in->pga_shunt_start_del_us;
    float pga_shunt_stop_del_us = in->pga_shunt_stop_del_us;
    const uint32_t filter_valid_delay = in->filter_valid_delay;
    const uint32_t decim_ratio = in->decim_ratio;
    const uint32_t ref_freq_hz = in->ref_freq_hz;

    const double max_bw_mhz = 50.0;
    double adcpll_freq = calc_adcpll_freq_hz(ref_freq_hz);
    double initial_ramp_bw_mhz = fabs(ramp_bw_Mhz);
    double ramp_bw_mhz_loop = initial_ramp_bw_mhz;
    double slope0_dev_f;
    uint32_t slope0_steps, slope1_steps;
    int32_t slope1_dev, slope0_dev;
    int afe_init_del;
    double BW_Diff = 0;
    uint32_t slope0_dev_orig = 0;
    uint32_t slope1_steps_new = 0;
    int32_t slope0_dev_pos_loop = 0;
    int32_t slope0_dev_neg_loop = 0;
    int data_valid_time = 0;
    int decim_factor_24_32 = (decim_ratio % 24 == 0) ? 24 : 32;
    double freq_ref_mhz;
    if (ref_freq_hz == 0) {
        comment("ERROR: reference frequency set to 0");
        return ADI_DM_PARAMETER_ERROR;
    }
    freq_ref_mhz = ref_freq_hz / 1e6F;
    int adcpll_int = (int) (8 * adcpll_freq / ref_freq_hz);
    double adcpll_freq_mhz = (float) (adcpll_freq / 1e6);
    double freq_afe_clk = adcpll_freq_mhz / decim_factor_24_32;

    int frac = frac_calc(adcpll_int, 8 * decim_factor_24_32);
    /*
     * e.g. if adcpll_int is 128 & decim_factor is 24,
     * then frac is 3 because (8*24)/128 == 192/128 == 3/2.
     *
     * The number of steps in a ramp must be a multiple of this.
     */

    double ramp_time_us = slope0_time_us + slope1_time_us + delay0_time_us + delay1_time_us + delay2_time_us;       // total times of one ramp
    int num_steps_ref_ramp = ceil_local((float) (ramp_time_us * freq_ref_mhz), frac);                               // total steps of one ramp (dividied by t_ref : 80MHz)
    int num_steps_slope1 = (int) floor(slope1_time_us * freq_ref_mhz);                                              // # of steps of each ramp component
    int num_steps_delay0 = (int) floor(delay0_time_us * freq_ref_mhz);
    int num_steps_delay1 = (int) floor(delay1_time_us * freq_ref_mhz);
    int num_steps_slope0 = (int) floor(slope0_time_us * freq_ref_mhz);
    /* All remaining steps are assigned to up ramp */
    int num_steps_delay2 = num_steps_ref_ramp - num_steps_slope0 - num_steps_slope1 - num_steps_delay0 - num_steps_delay1;  // total steps - sum of steps of 4 ramp components above (to avoid number mismatch caused from floor functions)
    int num_steps_afe_ramp = num_steps_ref_ramp * adcpll_int / decim_factor_24_32 / 8;                              // AFE total steps (divided by t_adc : 53.33MHz or 40MHz)


    printf("ramp_time_us : %f\n",ramp_time_us);
    printf("num_steps_slope1 : %d, num_steps_delay0 : %d, num_steps_delay1 : %d, num_steps_slope0 : %d, num_steps_delay2 : %d, num_steps_afe_ramp : %d\n",num_steps_slope1, num_steps_delay0, num_steps_delay1, num_steps_slope0, num_steps_delay2,num_steps_afe_ramp);
    printf("num_steps_ref_ramp : %d, adcpll_int : %d\n",num_steps_ref_ramp, adcpll_int);

    if (ramp_time_us == slope0_time_us) {
        slope0_steps = num_steps_ref_ramp - 1;
        num_steps_slope0 = slope0_steps;
        slope0_dev = (int32_t) floorf((float) (ramp_bw_mhz_loop * (1 << 22) / freq_ref_mhz / (num_steps_ref_ramp - 1)));
        slope1_steps = (in->ramp_bw_Mhz == 0) ? 2 : 1;  /* 0 is a special case for FMCW mode */
        num_steps_slope1 = slope1_steps;
        slope1_dev = -slope0_dev * (num_steps_ref_ramp - slope1_steps);
    } else {
        if (num_steps_slope1 == 0) {
            /* min of 1  ref clock should be given to slope1 */
            num_steps_slope1 = (in->ramp_bw_Mhz == 0) ? 2 : 1;  /* 0 is a special case for FMCW mode */
            num_steps_slope0 -= num_steps_slope1;
        }

        slope0_steps = num_steps_slope0;
        slope1_steps = num_steps_slope1;
        ramp_bw_mhz_loop = initial_ramp_bw_mhz;

        slope0_dev_f = (ramp_bw_mhz_loop * (1 << 22) / (freq_ref_mhz * slope0_steps));      // (1<<22) 2^25/8
        slope0_dev_orig = (uint32_t) floorf((float) slope0_dev_f);
        slope0_dev = slope0_dev_orig;
        slope1_steps_new = slope1_steps;

        printf("slope0_dev :%d, slope0_steps : %d, slope1_steps : %d, result : %d\n",slope0_dev,slope0_steps,slope1_steps,(slope0_dev * slope0_steps) % slope1_steps);
        if ((slope0_dev * slope0_steps) % slope1_steps) {           // what does this code want to check....??
            int pos_check = 0;
            int neg_check = 0;
            uint32_t slope1_steps_pos = slope1_steps;
            uint32_t slope1_steps_neg = slope1_steps;
            uint32_t slope1_steps_increment = 0;
            do {
                int loop = 0;
                ramp_bw_mhz_loop = initial_ramp_bw_mhz;
                slope0_dev_pos_loop = slope0_dev_orig;
                slope0_dev_neg_loop = slope0_dev_orig;
                do {
                    slope0_dev_pos_loop++;
                    slope0_dev_neg_loop--;
                    pos_check = ((slope0_dev_pos_loop * slope0_steps) % slope1_steps_new);
                    neg_check = ((slope0_dev_neg_loop * slope0_steps) % slope1_steps_new);
                    loop++;

                } while ((neg_check || pos_check) && (loop < (1 << 4)));
                if (!pos_check) {
                    ramp_bw_mhz_loop = slope0_dev_pos_loop * freq_ref_mhz * slope0_steps / (1 << 22);
                    slope1_dev = -((slope0_dev_pos_loop * (int32_t) slope0_steps) / (int32_t) slope1_steps_new);
                    slope1_steps = slope1_steps_new;
                    if (ramp_bw_mhz_loop >= initial_ramp_bw_mhz) {
                        BW_Diff = ramp_bw_mhz_loop - initial_ramp_bw_mhz;
                    } else {
                        BW_Diff = initial_ramp_bw_mhz - ramp_bw_mhz_loop;
                    }
                }
                if (!neg_check) {
                    ramp_bw_mhz_loop = slope0_dev_neg_loop * freq_ref_mhz * slope0_steps / (1 << 22);
                    slope1_dev = -((slope0_dev_neg_loop * (int32_t) slope0_steps) / (int32_t) slope1_steps_new);
                    slope1_steps = slope1_steps_new;
                    if (ramp_bw_mhz_loop >= initial_ramp_bw_mhz) {
                        BW_Diff = ramp_bw_mhz_loop - initial_ramp_bw_mhz;
                    } else {
                        BW_Diff = initial_ramp_bw_mhz - ramp_bw_mhz_loop;
                    }
                }

                slope1_steps_increment++;

                if (slope1_steps_increment % 2) {
                    slope1_steps_neg--;
                    slope1_steps_new = slope1_steps_neg;
                } else {
                    slope1_steps_pos++;
                    slope1_steps_new = slope1_steps_pos;
                }
            } while (BW_Diff < max_bw_mhz && (neg_check || pos_check) && (slope1_steps >= 1));
            num_steps_slope0 = slope0_steps;
            num_steps_slope1 = slope1_steps;
        } else {
            slope1_dev = -((slope0_dev * (int32_t) slope0_steps) / (int32_t) slope1_steps);
        }

        slope0_dev_f = (ramp_bw_mhz_loop * (1 << 22) / (freq_ref_mhz * slope0_steps));
        slope0_dev = (uint32_t) floorf((float) slope0_dev_f);

        if (((slope0_dev * slope0_steps) % slope1_steps)) {
            comment("Cannot fit ramp to meet criteria set!");
            return ADI_DM_PARAMETER_ERROR;
        }
        if (ramp_bw_Mhz < 0) {
            ramp_bw_Mhz = -1 * ((float) ramp_bw_mhz_loop);
        } else {
            ramp_bw_Mhz = (float) ramp_bw_mhz_loop;
        }
    }

    num_steps_delay2 = num_steps_ref_ramp - num_steps_slope0 - num_steps_slope1 - num_steps_delay0 - num_steps_delay1;
    num_steps_ref_ramp = num_steps_delay0 + num_steps_slope0 + num_steps_delay1 + num_steps_slope1 + num_steps_delay2;

    data_valid_time = num_samples * decim_ratio / decim_factor_24_32;
    num_steps_afe_ramp = num_steps_ref_ramp * adcpll_int / decim_factor_24_32 / 8;

    uint32_t data_valid_extra_time = filter_valid_delay * decim_ratio / decim_factor_24_32;
    data_valid_time += data_valid_extra_time;

    printf("<original> num_steps_ref_ramp : %d, num_steps_afe_ramp : %d, num_steps_delay2 : %d\n",num_steps_ref_ramp,num_steps_afe_ramp,num_steps_delay2);
    while (((num_steps_ref_ramp * adcpll_int) % decim_factor_24_32 != 0) || ((num_steps_ref_ramp * adcpll_int / decim_factor_24_32) % 8 != 0) || num_steps_delay2 < 0) {
        num_steps_delay2 += 1;
        num_steps_ref_ramp = num_steps_delay0 + num_steps_slope0 + num_steps_delay1 + num_steps_slope1 + num_steps_delay2;
        num_steps_afe_ramp = num_steps_ref_ramp * adcpll_int / decim_factor_24_32 / 8;
    }
    printf("<new> num_steps_ref_ramp : %d, num_steps_afe_ramp : %d, num_steps_delay2 : %d\n",num_steps_ref_ramp,num_steps_afe_ramp,num_steps_delay2);
    if (!pga_shunt_en) {
        float sample_time_us = (float) ((double) num_samples * (decim_ratio / decim_factor_24_32) / freq_afe_clk);
        if (delay0_time_us + slope0_time_us > sample_start_time_us + sample_time_us) {
            /* It is now recommended that pga_shunt is always enabled.
             * Force this but not if user has specified sampling after end of slope0.
             */
            comment("forcing pga_shunt enabled");
            pga_shunt_en = true;
            pga_shunt_start_del_us = 0;
            pga_shunt_stop_del_us = 0;
        }
    }

    uint32_t pga_shunt_start_del_ref = 0, pga_shunt_stop_del_ref = 0;
    if (pga_shunt_en) {
        uint32_t min_pga_shunt_start_del_ref = 10;      /* recommend min for 80 MHz (which is now only supported ref) */
        uint32_t min_pga_shunt_stop_del_ref = 120;      /* recommend min for 80 MHz (which is now only supported ref) */
        if (pga_shunt_start_del_us == 0.0f) {
            pga_shunt_start_del_ref = min_pga_shunt_start_del_ref;
            pga_shunt_stop_del_ref = min_pga_shunt_stop_del_ref;
        } else {
            pga_shunt_start_del_ref = (uint32_t) ceilf(pga_shunt_start_del_us * (float) freq_ref_mhz);
            pga_shunt_stop_del_ref = (uint32_t) ceilf(pga_shunt_stop_del_us * (float) freq_ref_mhz);
            if (pga_shunt_start_del_ref > 255) {
                pga_shunt_start_del_ref = 255;
            }
            if (pga_shunt_stop_del_ref > 255) {
                pga_shunt_stop_del_ref = 255;
            }
            if (pga_shunt_start_del_ref < min_pga_shunt_start_del_ref) {
                comment("ERROR: pga_shunt_start_del_ref less than %d", min_pga_shunt_start_del_ref);
                return ADI_DM_PARAMETER_ERROR;
            }
            if (pga_shunt_stop_del_ref < min_pga_shunt_stop_del_ref) {
                comment("ERROR: pga_shunt_stop_del_ref less than %d", min_pga_shunt_stop_del_ref);
                return ADI_DM_PARAMETER_ERROR;
            }
        }
    }
    pga_shunt_start_del_us = pga_shunt_start_del_ref / (float) freq_ref_mhz;
    pga_shunt_stop_del_us = pga_shunt_stop_del_ref / (float) freq_ref_mhz;
    printf("sample_start_time_us : %f , data_valid_extra_time : %d, data_valid_extra_time_us : %f\n",sample_start_time_us,data_valid_extra_time, data_valid_extra_time / (freq_ref_mhz * adcpll_int / decim_factor_24_32 / 8));
    if (sample_start_time_us != 0) {
        /* sample_start_time includes filter_valid_delay */
        // float afe_init_time_in_us = sample_start_time_us - data_valid_extra_time;
        float afe_init_time_in_us = sample_start_time_us - data_valid_extra_time / (freq_ref_mhz * adcpll_int / decim_factor_24_32 / 8); // modified..... Unit is not matched... in original code above...

        int afe_init_del_ref_steps = 0;
        afe_init_del_ref_steps = (int) round(afe_init_time_in_us * (float) freq_ref_mhz);
        afe_init_del = afe_init_del_ref_steps * adcpll_int / decim_factor_24_32 / 8;
    } else {
        int num_steps_afe_slope0 = (num_steps_delay0 + num_steps_slope0) * adcpll_int / decim_factor_24_32 / 8;
        int trailoff_afe = 0;
        if (pga_shunt_en) {
            trailoff_afe = (int) ceilf((float) (pga_shunt_start_del_ref / freq_ref_mhz * freq_afe_clk)) + 1;
            /* + 1 ensures data_valid_time and pga_shunt_start_del do not overlap or touch */
        }
        if (trailoff_afe < 4) {
            trailoff_afe = 4;
        }
        afe_init_del = num_steps_afe_slope0 - data_valid_time - trailoff_afe;
    }

    /* Error checking to see if it is possible to capture N number of samples within Ramp Up and Down times or not */
    if (afe_init_del < 0) {
        printf("ERROR: afe_start_off_time less than zero(afe_init_del value : %d)\n",afe_init_del);
        return ADI_DM_PARAMETER_ERROR;
    }
    if (afe_init_del + data_valid_time > num_steps_afe_ramp) {
        printf("ERROR: afe_start_off_time(%d) + data_valid_time(%d) exceeds afe ramp time(%d)\n",afe_init_del,data_valid_time,num_steps_afe_ramp);
        return ADI_DM_PARAMETER_ERROR;
    }

    if (pga_shunt_en) {
        int pga_shunt_stop_del_afe = (int) ceilf((float) (pga_shunt_stop_del_us / freq_afe_clk));

        if (pga_shunt_stop_del_afe > afe_init_del) {
            comment("ERROR: loss of valid AFE data due to shunt en");
            return ADI_DM_PARAMETER_ERROR;
        }
    }

    /* check against documented limits */
    if ((decim_factor_24_32 == 24 && afe_init_del < 72) || (decim_factor_24_32 == 32 && afe_init_del < 52)) {
        printf("ERROR: afe_start_off_time less than recommended minimum(afe_init_del value : %d)\n",afe_init_del);
        return ADI_DM_PARAMETER_ERROR;
    }
    if (filter_valid_delay < 60) {
        printf("ERROR: filter_valid_delay less than recommended minimum(filter_valid_delay value : %d)\n",filter_valid_delay);
        return ADI_DM_PARAMETER_ERROR;
    }

    if (ramp_bw_Mhz < 0) {
        slope0_dev = slope0_dev * -1;
        slope1_dev = slope1_dev * -1;
    }

    (void) memset(ramp_profile, 0, sizeof(*ramp_profile));

    ramp_profile->del_0 = num_steps_delay0;
    ramp_profile->del_1 = num_steps_delay1;
    ramp_profile->del_2 = num_steps_delay2;
    ramp_profile->ramp_steps_0 = num_steps_slope0;
    ramp_profile->ramp_steps_1 = num_steps_slope1;
    ramp_profile->ramp_dev_0 = slope0_dev;
    ramp_profile->ramp_dev_1 = slope1_dev;
    ramp_profile->afe_start_off_time = afe_init_del;
    ramp_profile->afe_ramp_time = num_steps_afe_ramp;
    ramp_profile->num_samples = num_samples;

    /* check bitfields did not overflow */
    if (ramp_profile->afe_start_off_time != afe_init_del) {
        comment("ERROR: afe_start_off_time overflowed");
        return ADI_DM_PARAMETER_ERROR;
    }
    if (ramp_profile->afe_ramp_time != num_steps_afe_ramp) {
        comment("ERROR: afe_ramp_time overflowed");
        return ADI_DM_PARAMETER_ERROR;
    }
    if (ramp_profile->del_0 != num_steps_delay0) {
        comment("ERROR: del_0 overflowed");
        return ADI_DM_PARAMETER_ERROR;
    }
    if (ramp_profile->del_1 != num_steps_delay1) {
        comment("ERROR: del_1 overflowed");
        return ADI_DM_PARAMETER_ERROR;
    }
    if (ramp_profile->del_2 != num_steps_delay2) {
        comment("ERROR: del_2 overflowed");
        return ADI_DM_PARAMETER_ERROR;
    }

    (void) memset(ramp_config, 0, sizeof(*ramp_config));

    if (pga_shunt_en) {
        ramp_config->pga_shunt_en = 1U;
        ramp_config->pga_shunt_start_del = pga_shunt_start_del_ref;
        ramp_config->pga_shunt_stop_del = pga_shunt_stop_del_ref;
    } else {
        ramp_config->pga_shunt_en = 0U;
        ramp_config->pga_shunt_start_del = 0U;
        ramp_config->pga_shunt_stop_del = 0U;
    }
    ramp_config->ramp_count = in->ramp_count;
    ramp_config->filter_decim_ratio = decim_ratio;
    ramp_config->filter_valid_delay = filter_valid_delay;
    for (dm_num = ADI_DM_MASTER; dm_num < adi_dm_active_digimmics; dm_num++) {
        ramp_config->dm[dm_num].vga_on_patt = 0x3E;     /* enable vga throughout ramp */
        ramp_config->dm[dm_num].vga_gauss_dis = 1U;
        ramp_config->dm[dm_num].vga_gain_steps = 7U;
        ramp_config->dm[dm_num].vga_gain_step_div = 2U;
    }

    /* check bitfields did not overflow */
    if (pga_shunt_en && (ramp_config->pga_shunt_start_del != pga_shunt_start_del_ref)) {
        comment("ERROR: pga_shunt_start_del overflowed");
        return ADI_DM_PARAMETER_ERROR;
    }
    if (pga_shunt_en && (ramp_config->pga_shunt_stop_del != pga_shunt_stop_del_ref)) {
        comment("ERROR: pga_shunt_stop_del overflowed");
        return ADI_DM_PARAMETER_ERROR;
    }

    (void) memset(actual, 0, sizeof(*actual));

    actual->slope0_time_us = (float) (num_steps_slope0 / freq_ref_mhz);
    actual->slope1_time_us = (float) (num_steps_slope1 / freq_ref_mhz);
    actual->delay0_time_us = (float) (num_steps_delay0 / freq_ref_mhz);
    actual->delay1_time_us = (float) (num_steps_delay1 / freq_ref_mhz);
    actual->delay2_time_us = (float) (num_steps_delay2 / freq_ref_mhz);
    actual->ramp_bw_Mhz = ramp_bw_Mhz;
    actual->afe_start_off_time_us = (float) (afe_init_del / freq_afe_clk);
    actual->filter_valid_delay_time_us = (float) (data_valid_extra_time / freq_afe_clk);
    actual->sample_time_us = (float) ((double) num_samples * (decim_ratio / decim_factor_24_32) / freq_afe_clk);
    actual->sample_start_time_us = actual->afe_start_off_time_us + actual->filter_valid_delay_time_us;
    actual->afe_ramp_time_us = (float) (num_steps_afe_ramp / freq_afe_clk);
    if (pga_shunt_en) {
        actual->pga_shunt_en = true;
        actual->pga_shunt_start_del_us = (float) (pga_shunt_start_del_ref / freq_ref_mhz);
        actual->pga_shunt_stop_del_us = (float) (pga_shunt_stop_del_ref / freq_ref_mhz);
    } else {
        actual->pga_shunt_en = false;
        actual->pga_shunt_start_del_us = 0.0f;
        actual->pga_shunt_stop_del_us = 0.0f;
    }
    actual->afe_freq_Mhz = (float) freq_afe_clk;
    actual->sample_rate_Mhz = (float) (freq_afe_clk / (decim_ratio / decim_factor_24_32));

    return ADI_DM_SUCCESS;
}

/**
 * Special-purpose function to calculate a ceiling mod some "significance".
 * "Significance" is how high the next ceiling is,
 * related to the modulus function.
 * For the ISO C @c ceil() function, it is 1.
 *
 * For example
 * @code{.c}
 * ceil_local(3.14, 4) == 4
 * ceil_local(2.78, 4) == 4
 * ceil_local(12.34, 4) == 16
 * @endcode
 *
 * @param[in] value input value
 * @param[in] significance 
 * @return function result, as above
 */
static int ceil_local(float value, int significance)
{
    int value_int;

    value_int = (int) ceil(value);
    if ((value_int % significance) != 0)
        return ((int) (value_int / significance) * significance) + significance;
    else
        return (int) value_int;
}

/**
 * Calculate numerator of simplified equivalent to b/a.
 *
 * @param[in] a original denominator
 * @param[in] b original numerator
 * @return numerator for simplified equivalent to b/a
 */
static int frac_calc(int a, int b)
{
    int temp_a = a, temp_b = b, temp_mod;

    /* This is Euclid's algorithm: */
    while (temp_b != 0) {
        temp_mod = temp_a % temp_b;
        temp_a = temp_b;
        temp_b = temp_mod;
    }
    /* temp_a is now the GCD of a and b */
    return b / temp_a;
}

static double calc_adcpll_freq_hz(double ref_freq_hz)
{
    const double min_adcpll_freq_hz = 10180e6;
    const double max_adcpll_freq_hz = 10810e6;
    const double ratio = min_adcpll_freq_hz / ref_freq_hz;
    uint32_t adcpll_int;
    uint32_t i = 8;
    do {
        adcpll_int = ceil_local((float) ratio, i);
        i /= 2UL;
    }
    while (adcpll_int * ref_freq_hz > max_adcpll_freq_hz);
    return ref_freq_hz * adcpll_int / 8;
}
