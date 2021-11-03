/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Obj_Main.h"
#include "Obj_CalRV.h"


/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
static void Obj_vGetRefPeakInfo(RefPeakData_t* PeakData);
static void Obj_vAngleEstimation_Ref(RefPeakData_t * PeakData);
static void Obj_vAngleEstimation_Pre(Cuda_PeakData_t * PeakData, MultiMod_t CurMod);
static void Obj_vMultiAngExtraction(float32_t AngTable[], float32_t Angle[], float32_t Pow[], int16_t* Cnt, float32_t APS[], int16_t Max_idx, float32_t APS_Th, int16_t azi_num_aps_step);

#ifdef CUDA_ACC
static void Obj_vCalculationRV(Cuda_PeakData_t* PeakData, RefPeakData_t* RefPeak, MultiMod_t CurMod);
#else
static void Obj_vCalculationRV(PeakData_t* PeakData, RefPeakData_t* RefPeak, MultiMod_t CurMod);
#endif

/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Obj_vCalcRV(void)
{
	Obj_vGetRefPeakInfo(&gRM_PeakData);

	Obj_vAngleEstimation_Ref(&gRM_PeakData);
	Obj_vAngleEstimation_Pre(&gLR_PeakData, LR_MOD);
	Obj_vAngleEstimation_Pre(&gMR_PeakData, MR_MOD);
	Obj_vAngleEstimation_Pre(&gSR_PeakData, SR_MOD);

	Obj_vCalculationRV(&gLR_PeakData, &gRM_PeakData, LR_MOD);
	Obj_vCalculationRV(&gMR_PeakData, &gRM_PeakData, MR_MOD);
	Obj_vCalculationRV(&gSR_PeakData, &gRM_PeakData, SR_MOD);
}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
static void Obj_vGetRefPeakInfo(RefPeakData_t* PeakData)
{
	int16_t i;
	float32_t delta_r, delta_v;
	float32_t interv_vel;
	float32_t err_comp_factor;
	float32_t temp_r, temp_v;

	delta_r = OBJ_CO_RM_DELTA_R;
	delta_v = OBJ_CO_RM_DELTA_V;
	interv_vel = OBJ_CO_RM_INTERVAL_V;
	err_comp_factor = OBJ_CO_RM_R_ERR_FACTOR;

	for (i = 0; i < PeakData->s16PeakCnt; i++)
	{
		temp_r = (PeakData->rdf32EstFreqIdx[i].R * delta_r);

		if (PeakData->rdu16FreqIdx[i].D < OBJ_CO_RM_NEG_VEL_IDX)
		{
			temp_v = (PeakData->rdf32EstFreqIdx[i].D * delta_v);
		}
		else
		{
			temp_v = (PeakData->rdf32EstFreqIdx[i].D * delta_v) - interv_vel;
		}

		PeakData->f32Range[i] = temp_r + (temp_v * err_comp_factor);
		PeakData->f32Velocity[i] = temp_v;
	}

}

#ifdef CUDA_ACC
static void Obj_vCalculationRV(Cuda_PeakData_t* PeakData, RefPeakData_t* RefPeak, MultiMod_t CurMod)
#else
static void Obj_vCalculationRV(PeakData_t* PeakData, RefPeakData_t* RefPeak, MultiMod_t CurMod)
#endif
{
	int16_t i, j, k, m, ii;
	int16_t harmonic_cnt;
	float32_t delta_r, delta_v;
	float32_t r_margin;

	float32_t interv_vel;
	float32_t err_comp_factor;
	float32_t ref_vel[OBJ_NUM_RM_PEAK_MAX];
	float32_t temp_r, temp_v, temp_ang, ref_temp_ang, temp_pow;
	float32_t temp_q;
	float32_t est_vel;
	int16_t match_flag;
	int16_t peak_harm_num_max;
	cmplxf32_t f32_PhaseCal[SP_NUM_TX][SP_NUM_RX];

	float32_t chirp_interval, tdm_comp_constant;
	cmplxf32_t tdm_cmp_temp;
	cmplxf32_t temp_fft_peak;
	int16_t rx, tx;
	int16_t cnt;
	
	float32_t ang_margin;


	switch (CurMod)
	{
	case LR_MOD:
		delta_r = OBJ_CO_LR_DELTA_R;
		delta_v = OBJ_CO_LR_DELTA_V;
		interv_vel = OBJ_CO_LR_INTERVAL_V;
		err_comp_factor = OBJ_CO_LR_R_ERR_FACTOR;
		peak_harm_num_max = OBJ_NUM_PEAK_HARM_LR;
		chirp_interval = SP_LR_CHIRP_INTERVAL;
		memcpy(f32_PhaseCal, gPhaseCal.f32LR_PhaseCal, SP_NUM_TX*SP_NUM_RX * sizeof(cmplxf32_t));
		break;

	case MR_MOD:
		delta_r = OBJ_CO_MR_DELTA_R;
		delta_v = OBJ_CO_MR_DELTA_V;
		interv_vel = OBJ_CO_MR_INTERVAL_V;
		err_comp_factor = OBJ_CO_MR_R_ERR_FACTOR;
		peak_harm_num_max = OBJ_NUM_PEAK_HARM_MR;
		chirp_interval = SP_MR_CHIRP_INTERVAL;
		memcpy(f32_PhaseCal, gPhaseCal.f32MR_PhaseCal, SP_NUM_TX*SP_NUM_RX * sizeof(cmplxf32_t));
		break;

	case SR_MOD:
		delta_r = OBJ_CO_SR_DELTA_R;
		delta_v = OBJ_CO_SR_DELTA_V;
		interv_vel = OBJ_CO_SR_INTERVAL_V;
		err_comp_factor = OBJ_CO_SR_R_ERR_FACTOR;
		peak_harm_num_max = OBJ_NUM_PEAK_HARM_SR;
		chirp_interval = SP_SR_CHIRP_INTERVAL;
		memcpy(f32_PhaseCal, gPhaseCal.f32SR_PhaseCal, SP_NUM_TX*SP_NUM_RX * sizeof(cmplxf32_t));
		break;

	default:
		delta_r = 0.0f;
		delta_v = 0.0f;
		interv_vel = 1.0f;
		err_comp_factor = 0.0f;
		break;
	}

	for (i = 0; i < RefPeak->s16PeakCnt; i++)
	{
		ref_vel[i] = fmodf(RefPeak->f32Velocity[i], interv_vel);
	}

	/* Calculation Range & Velocity */
	for (i = 0; i < PeakData->s16PeakCnt; i++)
	{
		temp_r = (PeakData->rdf32EstFreqIdx[i].R * delta_r);    //(RefPeak->f32Velocity[i] * err_comp_factor);
		temp_v = (PeakData->rdf32EstFreqIdx[i].D * delta_v);

		if (temp_r > 0.0f && temp_r <= 45.0f)
		{
			ang_margin = 2.0f;
		}
		else if (temp_r > 45.0f && temp_r <= 90.0f)
		{
			ang_margin = 3.0f;
		}
		else if (temp_r > 90.0f)
		{
			ang_margin = 6.0f;
		}
		else
		{

		}

		for (ii = 0; ii < PeakData->s16PreAngCnt[i]; ii++)
		{
			temp_ang = PeakData->f32PreAziAngle[i][ii];
			temp_pow = PeakData->f32PrePower[i][ii];
			
			harmonic_cnt = 0;
			PeakData->s16HarmonicCnt[i] = 0;
			for (j = 0; j < RefPeak->s16PeakCnt; j++)
			{
				for (m = 0; m < RefPeak->s16AngCnt[j]; m++)
				{
					ref_temp_ang = RefPeak->f32AziAngle[j][m];

					if ((_sp_abs(RefPeak->f32Range[j] - temp_r) < 2.0f)
						&& (_sp_abs(ref_temp_ang - temp_ang) < ang_margin)
						&& ((_sp_abs(ref_vel[j] - temp_v) < 2.0f) || (_sp_abs((ref_vel[j] + interv_vel) - temp_v) < 2.0f) || (_sp_abs((ref_vel[j] - interv_vel) - temp_v) < 2.0f)))
					{
						temp_q = floorf(RefPeak->f32Velocity[j] / interv_vel);
						for (k = -1; k < 2; k++)
						{
							est_vel = ((temp_q + k) * interv_vel) + temp_v;
							if (_sp_abs(est_vel - RefPeak->f32Velocity[j]) < (0.5f * interv_vel))
							{
								break;
							}
						}

						if (harmonic_cnt == 0)
						{
							PeakData->f32Range[i][harmonic_cnt] = temp_r + (est_vel * err_comp_factor);
							PeakData->f32Velocity[i][harmonic_cnt] = est_vel;
							PeakData->f32MatPreAziAngle[i][harmonic_cnt] = temp_ang;
							PeakData->f32MatPrePower[i][harmonic_cnt] = temp_pow;
							harmonic_cnt++;
						}
						else
						{
							match_flag = 0;
							for (k = 0; k < harmonic_cnt; k++)
							{
								if (_sp_abs(est_vel - PeakData->f32Velocity[i][k]) < (0.5f * interv_vel))
								{
									match_flag = 1;
									break;
								}
							}

							if (match_flag == 0)
							{
								PeakData->f32Range[i][harmonic_cnt] = temp_r + (est_vel * err_comp_factor);
								PeakData->f32Velocity[i][harmonic_cnt] = est_vel;
								PeakData->f32MatPreAziAngle[i][harmonic_cnt] = temp_ang;
								PeakData->f32MatPrePower[i][harmonic_cnt] = temp_pow;
								harmonic_cnt++;
							}
						}
						PeakData->s16HarmonicCnt[i] = harmonic_cnt;
					}
				}
				_sp_cnt_break(harmonic_cnt, 2);
			}
			_sp_cnt_break(harmonic_cnt, 2);
		}
	}

	/* 속도 보정 Peak  */
	tdm_comp_constant = (4.0f * SP_PI / SP_LAMDA * chirp_interval);

	cnt = 0;
	for (i = 0; i < PeakData->s16PeakCnt; i++)
	{
		_sp_cnt_break(cnt, peak_harm_num_max);
		for (k = 0; k < PeakData->s16HarmonicCnt[i]; k++)
		{
			_sp_cnt_break(cnt, peak_harm_num_max);

			for (tx = 0; tx < OBJ_NUM_TX; tx++)
			{
				tdm_cmp_temp.real = _sp_cosf(PeakData->f32Velocity[i][k] * (float32_t)tx * tdm_comp_constant);
				tdm_cmp_temp.imag = _sp_sinf(PeakData->f32Velocity[i][k] * (float32_t)tx * tdm_comp_constant);

				for (rx = 0; rx < OBJ_NUM_RX; rx++)
				{
					_obj_cmplx_mul(temp_fft_peak, PeakData->cf32FFTData[i][tx][rx], f32_PhaseCal[tx][rx]);
					PeakData->cf32PhFFTData[cnt][tx*OBJ_NUM_RX + rx].real = (temp_fft_peak.real) * (tdm_cmp_temp.real) + (temp_fft_peak.imag) * (tdm_cmp_temp.imag);
					PeakData->cf32PhFFTData[cnt][tx*OBJ_NUM_RX + rx].imag = (temp_fft_peak.imag) * (tdm_cmp_temp.real) - (temp_fft_peak.real) * (tdm_cmp_temp.imag);
				}
			}
			PeakData->rdu16phFreqIdx[cnt].R = PeakData->rdu16FreqIdx[i].R;
			PeakData->rdu16phFreqIdx[cnt].D = PeakData->rdu16FreqIdx[i].D;

			PeakData->f32PhRange[cnt][0] = PeakData->f32Range[i][k];
			PeakData->f32PhVelocity[cnt][0] = PeakData->f32Velocity[i][k];

			PeakData->f32PhPreAziAngle[cnt][0] = PeakData->f32MatPreAziAngle[i][k];
			PeakData->f32PhPrePower[cnt][0] = PeakData->f32MatPrePower[i][k];
			PeakData->f32PhSllPow[cnt] = PeakData->f32SllPow[i];
			cnt++;
		}
	}
	PeakData->s16PhCnt = cnt;
}




static void Obj_vAngleEstimation_Pre(Cuda_PeakData_t *PeakData, MultiMod_t CurMod)
{
	uint16_t i, j, ch;
	cmplxf32_t temp_ch_fft[OBJ_AE_RM_NUM_CH];
	cmplxf32_t ch_fft_temp[OBJ_AE_RM_NUM_CH];
	cmplxf32_t ch_fft[OBJ_AE_RM_NUM_CH];

	float32_t temp_abs_sum;
	cmplxf32_t cmplx_sum;
	cmplxf32_t temp_cal;

	float32_t aps_sll_th;
	float32_t temp_aps_pre[OBJ_AE_PRE_AZI_NUM_APS_STEPS_MAX];
	float32_t aps_max;
	int16_t aps_maxidx;
	float32_t num, den, dx;
	float32_t ch_norm_factor;

	ch_norm_factor = _sp_pow2(1.0f / OBJ_AE_RM_NUM_CH);

	cmplxf32_t temp_PhaseCal[OBJ_AE_RM_NUM_CH];
	int16_t azi_num_step;
	switch (CurMod)
	{
	case LR_MOD:

		memcpy(temp_PhaseCal, gPhaseCal.f32LR_PhaseCal[6], SP_NUM_RX * sizeof(cmplxf32_t));
		azi_num_step = OBJ_AE_PRE_AZI_LR_NUM_APS_STEPS;
		break;

	case MR_MOD:

		memcpy(temp_PhaseCal, gPhaseCal.f32MR_PhaseCal[6], SP_NUM_RX * sizeof(cmplxf32_t));
		azi_num_step = OBJ_AE_PRE_AZI_MR_NUM_APS_STEPS;
		break;

	case SR_MOD:
		memcpy(temp_PhaseCal, gPhaseCal.f32SR_PhaseCal[6], SP_NUM_RX * sizeof(cmplxf32_t));
		azi_num_step = OBJ_AE_PRE_AZI_SR_NUM_APS_STEPS;
		break;

	default:
		break;
	}

	for (i = 0; i < PeakData->s16PeakCnt; i++)
	{
		for (ch = 0; ch < OBJ_AE_RM_NUM_CH; ch++)
		{
			_obj_cmplx_mul(ch_fft[ch], PeakData->cf32FFTData[i][6][ch], temp_PhaseCal[ch]);
		}

		temp_abs_sum = 0.0f;
		for (ch = 0; ch < OBJ_AE_RM_NUM_CH; ch++)
		{
			temp_abs_sum += (ch_fft[ch].real * ch_fft[ch].real) + (ch_fft[ch].imag * ch_fft[ch].imag);
		}

		aps_sll_th = (temp_abs_sum * (float32_t)OBJ_AE_RM_NUM_CH) * (0.025f) * ch_norm_factor;

		for (j = 0; j < azi_num_step; j++)
		{
			cmplx_sum.real = 0.0f;
			cmplx_sum.imag = 0.0f;
			for (ch = 0; ch < OBJ_AE_RM_NUM_CH; ch++)
			{
				cmplx_sum.real += (ch_fft[ch].real * PeakData->cf32PreSteerVec[j][ch].real) + (ch_fft[ch].imag * PeakData->cf32PreSteerVec[j][ch].imag);
				cmplx_sum.imag += (ch_fft[ch].imag * PeakData->cf32PreSteerVec[j][ch].real) - (ch_fft[ch].real * PeakData->cf32PreSteerVec[j][ch].imag);
			}
			temp_aps_pre[j] = ((cmplx_sum.real * cmplx_sum.real) + (cmplx_sum.imag * cmplx_sum.imag)) * ch_norm_factor;
		}

		aps_max = temp_aps_pre[0];
		aps_maxidx = 0;
		for (j = 1; j < azi_num_step; j++)
		{
			if (temp_aps_pre[j] > aps_max)
			{
				aps_max = temp_aps_pre[j];
				aps_maxidx = j;
			}
		}

		PeakData->s16PreAngCnt[i] = 0;
		if (aps_max > aps_sll_th)
		{
			if ((aps_maxidx > 0) && (aps_maxidx < (azi_num_step - 1)))
			{
				num = temp_aps_pre[aps_maxidx + 1] - temp_aps_pre[aps_maxidx - 1];
				den = temp_aps_pre[aps_maxidx + 1] - (2.0f * temp_aps_pre[aps_maxidx]) + temp_aps_pre[aps_maxidx - 1];
				dx = 0.5f * OBJ_AE_AZI_RM_APS_STEP_SIZE;

				PeakData->f32PreAziAngle[i][0] = PeakData->f32PreAziAngTable[aps_maxidx] + ((num / den) * dx);
				//PeakData->f32EleAngle[i] = 0.0f;
				PeakData->f32PrePower[i][0] = 10.0f*_sp_log10f(aps_max);
				PeakData->s16PreAngCnt[i]++;
			}
			Obj_vMultiAngExtraction(PeakData->f32PreAziAngTable, &PeakData->f32PreAziAngle[i][0], &PeakData->f32PrePower[i][0], &PeakData->s16PreAngCnt[i], temp_aps_pre, aps_maxidx, aps_sll_th, azi_num_step);
		}
		else
		{
			PeakData->f32PreAziAngle[i][0] = OBJ_AE_FAILURE_ANGLE;
			PeakData->f32PrePower[i][0] = 0.0f;
		}
	}
}


static void Obj_vAngleEstimation_Ref(RefPeakData_t *PeakData)
{
	uint16_t i, j, ch;
	cmplxf32_t temp_ch_fft[OBJ_AE_RM_NUM_CH];
	cmplxf32_t ch_fft_temp[OBJ_AE_RM_NUM_CH];
	cmplxf32_t ch_fft[OBJ_AE_RM_NUM_CH];

	float32_t temp_abs_sum;
	cmplxf32_t cmplx_sum;
	cmplxf32_t temp_cal;

	float32_t aps_sll_th;
	float32_t temp_aps_ref[OBJ_AE_AZI_RM_NUM_APS_STEPS];
	float32_t aps_max;
	int16_t aps_maxidx;
	float32_t num, den, dx;
	float32_t ch_norm_factor;

	ch_norm_factor = _sp_pow2(1.0f / OBJ_AE_RM_NUM_CH);

	for (i = 0; i < PeakData->s16PeakCnt; i++)
	{
		for (ch = 0; ch < OBJ_AE_RM_NUM_CH; ch++)
		{
			_obj_cmplx_mul(ch_fft[ch], PeakData->cf32FFTData[i][0][ch], gPhaseCal.f32RM_PhaseCal[0][ch]);
		}

		temp_abs_sum = 0.0f;
		for (ch = 0; ch < OBJ_AE_RM_NUM_CH; ch++)
		{
			temp_abs_sum += (ch_fft[ch].real * ch_fft[ch].real) + (ch_fft[ch].imag * ch_fft[ch].imag);
		}
		aps_sll_th = (temp_abs_sum * (float32_t)OBJ_AE_RM_NUM_CH) * OBJ_AE_RM_APS_SLL_TH * ch_norm_factor;

		for (j = 0; j < OBJ_AE_AZI_RM_NUM_APS_STEPS; j++)
		{
			cmplx_sum.real = 0.0f;
			cmplx_sum.imag = 0.0f;
			for (ch = 0; ch < OBJ_AE_RM_NUM_CH; ch++)
			{
				cmplx_sum.real += (ch_fft[ch].real * PeakData->cf32SteerVec[j][ch].real) + (ch_fft[ch].imag * PeakData->cf32SteerVec[j][ch].imag);
				cmplx_sum.imag += (ch_fft[ch].imag * PeakData->cf32SteerVec[j][ch].real) - (ch_fft[ch].real * PeakData->cf32SteerVec[j][ch].imag);
			}
			temp_aps_ref[j] = ((cmplx_sum.real * cmplx_sum.real) + (cmplx_sum.imag * cmplx_sum.imag)) * ch_norm_factor;

		}

		aps_max = temp_aps_ref[0];
		aps_maxidx = 0;
		for (j = 1; j < OBJ_AE_AZI_RM_NUM_APS_STEPS; j++)
		{
			if (temp_aps_ref[j] > aps_max)
			{
				aps_max = temp_aps_ref[j];
				aps_maxidx = j;
			}
		}

		PeakData->s16AngCnt[i] = 0;
		if (aps_max > aps_sll_th)
		{
			if ((aps_maxidx > 0) && (aps_maxidx < (OBJ_AE_AZI_RM_NUM_APS_STEPS - 1)))
			{
				num = temp_aps_ref[aps_maxidx + 1] - temp_aps_ref[aps_maxidx - 1];
				den = temp_aps_ref[aps_maxidx + 1] - (2.0f * temp_aps_ref[aps_maxidx]) + temp_aps_ref[aps_maxidx - 1];
				dx = 0.5f * OBJ_AE_AZI_RM_APS_STEP_SIZE;


				PeakData->f32AziAngle[i][0] = PeakData->f32AziAngTable[aps_maxidx] + ((num / den) * dx);
				//PeakData->f32EleAngle[i] = 0.0f;
				PeakData->f32Power[i][0] = 10.0f*_sp_log10f(aps_max);
				PeakData->s16AngCnt[i]++;
			}
			Obj_vMultiAngExtraction(PeakData->f32AziAngTable, &PeakData->f32AziAngle[i][0], &PeakData->f32Power[i][0], &PeakData->s16AngCnt[i], temp_aps_ref, aps_maxidx, aps_sll_th, OBJ_AE_AZI_RM_NUM_APS_STEPS);
		}
		else
		{
			PeakData->f32AziAngle[i][0] = OBJ_AE_FAILURE_ANGLE;
			PeakData->f32Power[i][0] = 0.0f;
		}
	}

}

static void Obj_vMultiAngExtraction(float32_t AngTable[], float32_t Angle[], float32_t Pow[], int16_t* Cnt, float32_t APS[], int16_t Max_idx, float32_t APS_Th, int16_t azi_num_aps_step)
{
	int16_t i, j;
	float32_t Convex_Pow[OBJ_AE_RM_NUM_TARGET_MAX];
	int16_t Convex_idx[OBJ_AE_RM_NUM_TARGET_MAX];
	int16_t temp_Cnt;

	float32_t temp_Min;
	int16_t temp_Min_idx;
	float32_t num, den, dx;

	Convex_Pow[0] = APS[Max_idx];
	Convex_idx[0] = Max_idx;
	temp_Cnt = (*Cnt);
	for (i = 1; i < (azi_num_aps_step - 1); i++)
	{
		if ((i != Max_idx)
			&& (APS[i] > APS[i - 1]) && (APS[i] > APS[i + 1])
			&& (APS[i] > (OBJ_AE_RM_MULTI_TARGET_TH * APS[Max_idx])) && (APS[i] > APS_Th))
		{
			if (temp_Cnt < OBJ_AE_RM_NUM_TARGET_MAX)
			{
				Convex_Pow[temp_Cnt] = APS[i];
				Convex_idx[temp_Cnt] = i;
				temp_Cnt++;
			}
			else
			{
				temp_Min = Convex_Pow[0];
				temp_Min_idx = 0;
				for (j = 1; j < OBJ_AE_RM_NUM_TARGET_MAX; j++)
				{
					if (Convex_Pow[j] < temp_Min)
					{
						temp_Min = Convex_Pow[j];
						temp_Min_idx = j;
					}
				}

				if (APS[i] > temp_Min)
				{
					Convex_Pow[temp_Min_idx] = APS[i];
					Convex_idx[temp_Min_idx] = i;
				}
			}
		}
	}

	dx = 0.5f * OBJ_AE_AZI_RM_APS_STEP_SIZE;
	for (i = (*Cnt); i < temp_Cnt; i++)
	{
		num = APS[Convex_idx[i] + 1] - APS[Convex_idx[i] - 1];
		den = APS[Convex_idx[i] + 1] + (2.0f * APS[Convex_idx[i]]) + APS[Convex_idx[i] - 1];

		if (_sp_abs(den) > 0.000001f)
		{
			Angle[i] = AngTable[Convex_idx[i]] - ((num / den) * dx);
		}
		else
		{
			Angle[i] = AngTable[Convex_idx[i]];
		}

		Pow[i] = 10.0f * _sp_log10f(Convex_Pow[i]);
	}
	(*Cnt) = temp_Cnt;
}


