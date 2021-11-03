/* periodic.c
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
#include "adar690x_regs.h"
#include "adar690x_fw.h"
#include <stdio.h>

static adi_dm_err_t bist_powerdetectors(void)
{
    adi_dm_err_t res;

    comment("-->> Entering function bist_powerdetectors");

    res = adi_dm_power_detector_offset();
    if (res != ADI_DM_SUCCESS)
        return res;

    if (adi_dm_call_fw_tx_pwr_chk) {
        /* BIST19: Tx output transmit power check */
        comment("ADI_ADAR690x_FW_TX_PWR_CHK");
        res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_TX_PWR_CHK);
        if (res != ADI_DM_SUCCESS)
            return res;
        if (adi_dm_active_digimmics > 1) {
            res = adi_dm_cascaded_tx_pwr_chk();
            if (res != ADI_DM_SUCCESS)
                return res;
        }
    }

    if (adi_dm_call_fw_tx_output_load_monitor_chk) {
        /* BIST54: Tx output load monitor check */
        comment("ADI_ADAR690x_FW_TX_LOAD_CHK");
        res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_TX_LOAD_CHK);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    if (adi_dm_call_fw_tx_isolation_monitor_chk) {
        /* BIST53: Tx isolation monitor check */
        comment("ADI_ADAR690x_FW_TX_ISOL_CHK");
        res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_TX_ISOL_CHK);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    if (adi_dm_call_fw_rxchain_diag_chk) {
        /* BIST15: rx chain diagnostic check */
        /* BIST18: LO chain output monitor */
        comment("ADI_ADAR690x_FW_RX_CHAIN_CHK");
        res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_RX_CHAIN_CHK);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    if (adi_dm_call_fw_pwr_det_rat_chk) {
        /* BIST44: Power detector rationality check */
        comment("ADI_ADAR690x_FW_PWR_DET_FAULT_CHK");
        res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_PWR_DET_FAULT_CHK);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    res = adi_dm_power_detector_clear();
    if (res != ADI_DM_SUCCESS)
        return res;

    comment("-->> Leaving function bist_powerdetectors");
    return ADI_DM_SUCCESS;
}

adi_dm_err_t adi_dm_PeriodicCalibration(const adi_dm_periodic_calibration_t * p)
{
    adi_dm_err_t res;
    adi_dm_temp_change_t t;
    const bool run_lochain_cal = !p->no_lochain_cal && adi_dm_call_fw_lochain_cal;
    const bool run_rx_gain_cal = !p->no_rxgain_cal && adi_dm_call_fw_rxgain_cal;
    const bool run_pa_adj_cal = !p->no_pa_adj_cal && adi_dm_call_fw_txpa_adj;
    const bool run_hpf_cal = !p->no_hpf_cal && adi_dm_call_fw_hpf_cal;
    const bool run_adcpll_align = !p->no_adcpll_align && adi_dm_call_fw_adcpll_align;
    comment("-->> Entering function adi_dm_PeriodicCalibration");

    /* Some CALs & BISTs require temperature measurement */
    if (run_rx_gain_cal || run_lochain_cal || run_pa_adj_cal || run_hpf_cal || p->run_checks) {
        /* Measuring temperature ADI_ADAR690x_FW_TEMP_MEASURE */
        res = adi_dm_get_temp_change(&t);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    if (!p->no_rfpll_bow_cal && adi_dm_call_fw_rfpll_bow_cal) {
        comment("ADI_ADAR690x_FW_RFPLL_BOW_CAL");
        res = adi_dm_CallFW(ADI_DM_MASTER, ADI_ADAR690x_FW_RFPLL_BOW_CAL);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    if (run_lochain_cal) {
        if (t.max_lochain_change_c > 20.0F) {
            const bool should_change_freq = adi_dm_saved_ramp_start_freq_hz != adi_dm_saved_max_ramp_freq_hz;

            if (should_change_freq) {
                comment("ADI_ADAR690x_FW_RFPLL_LOCK maximum ramp freq");
                res = adi_dm_CallFWU64(ADI_DM_MASTER, ADI_ADAR690x_FW_RFPLL_LOCK, adi_dm_saved_max_ramp_freq_hz);
                if (res != ADI_DM_SUCCESS)
                    return res;
            }

            comment("ADI_ADAR690x_FW_LOCHAIN_CAL");
            res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_LOCHAIN_CAL);
            if (res != ADI_DM_SUCCESS)
                return res;

            res = adi_dm_baseline_lochain_change(&t);
            if (res != ADI_DM_SUCCESS)
                return res;

            if (should_change_freq) {
                comment("ADI_ADAR690x_FW_RFPLL_LOCK ramp start frequency");
                res = adi_dm_CallFWU64(ADI_DM_MASTER, ADI_ADAR690x_FW_RFPLL_LOCK, adi_dm_saved_ramp_start_freq_hz);
                if (res != ADI_DM_SUCCESS)
                    return res;
            }

        }
    }

    if (run_pa_adj_cal) {
        if (t.max_tx_change_c > 10.0F) {
            comment("ADI_ADAR690x_FW_TXPA_ADJ");
            res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_TXPA_ADJ);
            if (res != ADI_DM_SUCCESS)
                return res;
            res = adi_dm_baseline_tx_change(&t);
            if (res != ADI_DM_SUCCESS)
                return res;
        }
    }

    if (adi_dm_call_fw_adc_phase_cal) {
        if (t.max_rx_change2_c > 30.0F) {
            comment("ADI_ADAR690x_FW_ADC_PHASE_CAL");
            res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_ADC_PHASE_CAL);
            if (res != ADI_DM_SUCCESS) {
                return res;
            }
            res = adi_dm_baseline_rx_change2(&t);
            if (res != ADI_DM_SUCCESS)
                return res;
        }
    }

    if (run_rx_gain_cal || run_hpf_cal) {
        if (t.max_rx_change_c > 20.0F) {
            if (run_hpf_cal) {
                comment("ADI_ADAR690x_FW_HPF_CAL");
                res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_HPF_CAL);
                if (res != ADI_DM_SUCCESS) {
                    return res;
                }
            }
            if (run_rx_gain_cal) {
                comment("ADI_ADAR690x_FW_RXGAIN_CAL");
                res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_RXGAIN_CAL);
                if (res != ADI_DM_SUCCESS)
                    return res;
            }
            res = adi_dm_baseline_rx_change(&t);
            if (res != ADI_DM_SUCCESS)
                return res;
        }
    }

    if (p->run_checks) {
        if (p->run_rfpll_period_chk && adi_dm_call_fw_rfpll_period_chk) {
            /* BIST103c: RFPLL period check */
            /* has to be called before ADI_ADAR690x_FW_RX_CHAIN_CHK which clobbers the RFPLL period counter */
            comment("ADI_ADAR690x_FW_RFPLL_PERIOD_CHK");
            res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_RFPLL_PERIOD_CHK);
            if (res != ADI_DM_SUCCESS)
                return res;
        }

        if (adi_dm_call_fw_aux_diag_chk) {
            /* BIST32: Auxadc diagnostic check */
            comment("ADI_ADAR690x_FW_AUXADC_DIAG_CHK");
            res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_AUXADC_DIAG_CHK);
            if (res != ADI_DM_SUCCESS)
                return res;
        }

        if (adi_dm_call_fw_pwr_sup_chk) {
            /* BIST03: check internal power supplies */
            comment("ADI_ADAR690x_FW_PWR_SUP_CHK ");
            res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_PWR_SUP_CHK);
            if (res != ADI_DM_SUCCESS)
                return res;
        }

        if (adi_dm_call_fw_rx_filter_chk) {
            /* BIST67: Decimation filter diagnostic check */
            comment("ADI_ADAR690x_FW_RX_FILTER_CHK  ");
            res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_RX_FILTER_CHK);
            if (res != ADI_DM_SUCCESS)
                return res;
        }

        if (adi_dm_rx_overflow_chk) {
            /* BIST10: Decimation filter overflow check */
            comment("ADI_ADAR690x_FW_RX_OVERFLOW_CHK ");
            res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_RX_OVERFLOW_CHK);
            if (res != ADI_DM_SUCCESS)
                return res;
        }

        /* BIST routines having Power Detector Measurement requirement */
        if (p->run_power_checks) {
            res = bist_powerdetectors();
            if (res != ADI_DM_SUCCESS)
                return res;
        }

        if (adi_dm_call_fw_rx_baseband_chk) {
            /* BIST11: RX baseband check */
            comment("ADI_ADAR690x_FW_RX_BASEBAND_CHK");
            res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_RX_BASEBAND_CHK);
            if (res != ADI_DM_SUCCESS)
                return res;
        }

        if (adi_dm_check_ram_crc) {
            /* BIST42, BIST102: Check groups set up in adi_dm_LockConfig. */
            res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_STS_CRC_PASS, 0);
            if (res != ADI_DM_SUCCESS)
                return res;
            res = adi_dm_Write(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_STS_CRC_FAIL, 0);
            if (res != ADI_DM_SUCCESS)
                return res;
            comment("ADI_ADAR690x_FW_CRC_CHK");
            res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_CRC_CHK);
            if (res != ADI_DM_SUCCESS) {
#ifndef __SILENT
                uint32_t v = 0;
                (void) adi_dm_Read(ADI_DM_MASTER, ADI_ADAR690x_STS_CRC_PASS, &v);
                printf("ADI_ADAR690x_STS_CRC_PASS = %08X\n", v);
                (void) adi_dm_Read(ADI_DM_MASTER, ADI_ADAR690x_STS_CRC_FAIL, &v);
                printf("ADI_ADAR690x_STS_CRC_FAIL = %08X\n", v);
#endif
                return res;
            }
        }

        if (adi_dm_check_spi_counters) {
            /* BIST05f, BIST05g: compare host and device frame counters */
            res = adi_dm_spi_counter_check();
            if (res != ADI_DM_SUCCESS) {
                return res;
            }
        }
    }

    if (p->run_power_checks) {
        res = adi_dm_power_detector_enable();
        if (res != ADI_DM_SUCCESS)
            return res;
    }
    if (run_adcpll_align) {
        /* combined align and BIST56 */
        comment("ADI_ADAR690x_FW_ADCPLL_ALIGN");
        res = adi_dm_CallFW(ADI_DM_ALL_DIGIMMICS, ADI_ADAR690x_FW_ADCPLL_ALIGN);
        if (res != ADI_DM_SUCCESS)
            return res;
    }

    comment("-->> Exiting function adi_dm_PeriodicCalibration");
    return ADI_DM_SUCCESS;
}
