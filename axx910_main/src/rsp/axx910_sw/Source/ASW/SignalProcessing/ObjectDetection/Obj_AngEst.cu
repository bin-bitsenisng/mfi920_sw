/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Obj_Main.h"
#include "Pre_Main.h"
#include "Obj_AngEst.h"
#include "Obj_Parameters.h"
#include "cublas_v2.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#ifdef LINUX
#include <sys/time.h>
#include "print_common.h"
#endif
/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/
#define MAX_NUM_OF_GPU_THREAD	1024

/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/
#ifdef CUDA_ACC
cuComplex* ch_fft_lr;
cuComplex* ch_fft_mr;
cuComplex* ch_fft_sr;

cuComplex* cmplx_element;

cuComplex* cmplx_sum_lr;
cuComplex* cmplx_sum_mr;
cuComplex* cmplx_sum_sr;

float32_t* temp_aps_lr;
float32_t* temp_aps_mr;
float32_t* temp_aps_sr;


//float32_t* temp_aps2;
#endif

cublasHandle_t cublas_handler;

/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
#ifdef CUDA_ACC
static void Obj_vAngleEstimation_LR(Cuda_PeakData_t *PeakData, MultiMod_t CurMod);
static void Obj_vAngleEstimation_MR(Cuda_PeakData_t *PeakData, MultiMod_t CurMod);
static void Obj_vAngleEstimation_SR(Cuda_PeakData_t *PeakData, MultiMod_t CurMod);
#else
//static void Obj_vAngleEstimation_LR(PeakData_t *PeakData, MultiMod_t CurMod);
//static void Obj_vAngleEstimation_MR(PeakData_t *PeakData, MultiMod_t CurMod);
//static void Obj_vAngleEstimation_SR(PeakData_t *PeakData, MultiMod_t CurMod);
#endif
//static void Obj_vAngleEstimation_Ref(RefPeakData_t * PeakData);

static cmplxf32_t Obj_cf32GetPhaseDiff(const cmplxf32_t a, const cmplxf32_t b);
//static cmplxf32_t Obj_cf32DivPhase(const cmplxf32_t a, const cmplxf32_t b);
static void Obj_vAryRemov(cmplxf32_t temp_peak_fft[], cmplxf32_t temp_ch_fft[]);
static void Obj_vAryPaste(cmplxf32_t temp_peak_fft[], cmplxf32_t temp_ch_fft[]);

/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/

__global__ void cal_temp_aps(float32_t* temp_aps, cuComplex* cmplx_sum, float32_t ch_norm_factor)
{
	int ti = threadIdx.x;
	int bd = blockDim.x * blockIdx.x;

	temp_aps[bd + ti] = (cmplx_sum[bd + ti].x * cmplx_sum[bd + ti].x + cmplx_sum[bd + ti].y * cmplx_sum[bd + ti].y) * ch_norm_factor;
}

void Obj_vAngEst(void)
{
#ifdef LINUX
	struct timeval startTime, endTime;
	double diffTime;
#endif   

#ifdef LINUX
	gettimeofday(&startTime, NULL);
#endif

#ifdef LINUX
	gettimeofday(&endTime, NULL);
	diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
	//TRACE_TIME_MSG("Obj_vAngleEstimation_Ref(&gRM_PeakData): %lf s\n", diffTime);
#endif	

#ifdef LINUX
	gettimeofday(&startTime, NULL);
#endif

	Obj_vAngleEstimation_LR(&gLR_PeakData, LR_MOD);

#ifdef LINUX
	gettimeofday(&endTime, NULL);
	diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
	//TRACE_TIME_MSG("Obj_vAngleEstimation(&gLR_PeakData, LR_MOD)(): %lf s\n", diffTime);
#endif

#ifdef LINUX
	gettimeofday(&startTime, NULL);
#endif

	Obj_vAngleEstimation_MR(&gMR_PeakData, MR_MOD);

#ifdef LINUX
	gettimeofday(&endTime, NULL);
	diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
	//TRACE_TIME_MSG("Obj_vAngleEstimation(&gMR_PeakData, MR_MOD)(): %lf s\n", diffTime);
#endif	

#ifdef LINUX
	gettimeofday(&startTime, NULL);
#endif

	Obj_vAngleEstimation_SR(&gSR_PeakData, SR_MOD);

#ifdef LINUX
	gettimeofday(&endTime, NULL);
	diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
	//TRACE_TIME_MSG("Obj_vAngleEstimation(&gSR_PeakData, SR_MOD)(): %lf s\n", diffTime);
#endif
}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
#ifdef CUDA_ACC
static void Obj_vAngleEstimation_LR(Cuda_PeakData_t *PeakData, MultiMod_t CurMod)
#else
static void Obj_vAngleEstimation(PeakData_t *PeakData, MultiMod_t CurMod)
#endif 
{
#ifdef LINUX
	struct timeval startTime, endTime;
	double diffTime;
#endif  

	uint16_t i, azi_idx, ele_idx, rx, tx, ch, j, ii, k;


	float32_t temp_abs_sum;
	float32_t aps_sll_th[OBJ_NUM_PEAK_HARM_MAX][OBJ_CO_NUM_HARMONICS_MAX];

	float32_t num_azi, den_azi, dazi;
	float32_t num_ele, den_ele, dele;
	float32_t ch_norm_factor;

	float32_t Peak_Candi[OBJ_AE_CANDI_NUM_TARGET_MAX];
	int16_t Peak_azi_idx[OBJ_AE_CANDI_NUM_TARGET_MAX];
	int16_t Peak_ele_idx[OBJ_AE_CANDI_NUM_TARGET_MAX];
	int16_t Peak_flg[OBJ_AE_CANDI_NUM_TARGET_MAX];
	int16_t Peak_near_flg[OBJ_AE_CANDI_NUM_TARGET_MAX];

	int16_t peak_cnt;
	int16_t ang_cnt;

	float32_t temp_peak;
	int16_t temp_azi_idx;
	int16_t temp_ele_idx;
	int16_t temp_peak_flg;

	int16_t temp_peak_azi_idx, temp_peak_ele_idx;

	cmplxf32_t temp_fft[OBJ_AE_NUM_CH_PARALLE];

	ch_norm_factor = _sp_pow2(1.0f / OBJ_AE_NUM_CH);

	int16_t azi_num_aps_step;
	int16_t ele_num_aps_step;
	float32_t sll_th;
	float32_t aps_multi_th;
	float32_t azi_aps_step_size;
	float32_t ele_aps_step_size;
	float32_t chirp_interval;
	float32_t tdm_comp_constant;
	uint32_t temp_index;
	uint32_t pre_temp_index;
	int16_t  num_azi_ele;


	float32_t azi_offset, ele_offset;
	float32_t azi_diff, ele_diff;

	int16_t temp_peak_cnt;
	float32_t peak_azi_temp_idx[OBJ_AE_NUM_PEAK_TARGET_MAX];
	float32_t peak_ele_temp_idx[OBJ_AE_NUM_PEAK_TARGET_MAX];


	azi_num_aps_step = OBJ_AE_AZI_LR_NUM_APS_STEPS;
	ele_num_aps_step = OBJ_AE_ELE_LR_NUM_APS_STEPS;
	sll_th = OBJ_AE_LR_APS_SLL_TH;
	aps_multi_th = OBJ_AE_LR_MULTI_TARGET_TH;
	azi_aps_step_size = OBJ_AE_AZI_LR_APS_STEP_SIZE;
	ele_aps_step_size = OBJ_AE_ELE_LR_APS_STEP_SIZE;
	chirp_interval = SP_LR_CHIRP_INTERVAL;

	num_azi_ele = azi_num_aps_step * ele_num_aps_step;

#ifdef LINUX
	gettimeofday(&startTime, NULL);
#endif

	for (i = 0; i < PeakData->s16PhCnt; i++)
	{
		for (k = 0; k < 1; k++)
		{
#if (OBJ_HEXA_ARRAY_ON==1)

#ifdef CUDA_ACC
			Obj_vAryRemov(PeakData->cf32PhFFTData[i], (cmplxf32_t*)ch_fft_lr + i * OBJ_AE_NUM_CH);
#else
			Obj_vAryRemov(PeakData->cf32PhFFTData[i], ch_fft[i][k]);
#endif

#else

#endif
			if (PeakData->rdu16phFreqIdx[i].D == 0)
			{
				temp_abs_sum = _sp_pow2(PeakData->f32PhSllPow[i]*0.5f);
			}
			else
			{
				temp_abs_sum = _sp_pow2(PeakData->f32PhSllPow[i]);
			}

			aps_sll_th[i][k] = (temp_abs_sum* (float32_t)OBJ_AE_NUM_CH) * sll_th * ch_norm_factor;
		}
	}

	cuComplex alpha;
	cuComplex beta;
	alpha.x = 1.0; alpha.y = 0.0;
	beta.x = 0.0; beta.y = 0.0;

	for (i = 0; i < PeakData->s16PhCnt; i++)
	{
		for (k = 0; k < 1; k++)
		{
#ifndef CUDA_ACC
			for (ele_idx = 0; ele_idx < ele_num_aps_step; ele_idx++)
			{
				for (azi_idx = 0; azi_idx < azi_num_aps_step; azi_idx++)
				{
					cmplx_sum.real = 0.0f;
					cmplx_sum.imag = 0.0f;
					for (ch = 0; ch < OBJ_AE_NUM_CH; ch++)
					{
						cmplx_sum.real += (ch_fft[i][k][ch].real * PeakData->cf32SteerVec[ele_idx * azi_num_aps_step + azi_idx][ch].real) + (ch_fft[i][k][ch].imag * PeakData->cf32SteerVec[ele_idx * azi_num_aps_step + azi_idx][ch].imag);
						cmplx_sum.imag += (ch_fft[i][k][ch].imag * PeakData->cf32SteerVec[ele_idx * azi_num_aps_step + azi_idx][ch].real) - (ch_fft[i][k][ch].real * PeakData->cf32SteerVec[ele_idx * azi_num_aps_step + azi_idx][ch].imag);
					}
					temp_aps[i][k][ele_idx][azi_idx] = ((cmplx_sum.real * cmplx_sum.real) + (cmplx_sum.imag * cmplx_sum.imag)) * ch_norm_factor;
				}
			}
#else
			cublasCgemv(cublas_handler, CUBLAS_OP_T, OBJ_AE_NUM_CH, num_azi_ele, &alpha, (cuComplex*)PeakData->cf32SteerVec, OBJ_AE_NUM_CH, \
				ch_fft_lr + OBJ_AE_NUM_CH * (i), 1, &beta, cmplx_sum_lr + num_azi_ele * (i), 1);
#endif
		}
	}


#ifdef CUDA_ACC
	cal_temp_aps << < (uint32_t)(PeakData->s16PhCnt * num_azi_ele / MAX_NUM_OF_GPU_THREAD) + 1, \
		MAX_NUM_OF_GPU_THREAD >> > (temp_aps_lr, cmplx_sum_lr, ch_norm_factor);
#ifdef LINUX
	(cudaStreamAttachMemAsync(NULL, temp_aps_lr, 0, cudaMemAttachHost));
#else
	(cudaStreamAttachMemAsync(NULL, temp_aps_lr, 0, cudaMemAttachGlobal));
#endif
	(cudaStreamSynchronize(NULL));
#endif

	for (i = 0; i < PeakData->s16PhCnt; i++)
	{
		for (k = 0; k < 1; k++)
		{
			peak_cnt = 0;
			temp_peak_azi_idx = 0;
			temp_peak_ele_idx = 0;
			
			for (ele_idx = 1; ele_idx < ele_num_aps_step - 1; ele_idx++)
			{
				_sp_cnt_break(peak_cnt, OBJ_AE_CANDI_NUM_TARGET_MAX);
				for (azi_idx = 1; azi_idx < azi_num_aps_step - 1; azi_idx++)
				{
					_sp_cnt_break(peak_cnt, OBJ_AE_CANDI_NUM_TARGET_MAX);
					temp_index = i * num_azi_ele + ele_idx * azi_num_aps_step;

#if (OBJ_AE_ADD_OBJ_ENABLE == 1)
					if ((temp_aps_lr[temp_index + azi_idx] > aps_sll_th[i][k]))
#else
					if ((temp_aps_lr[temp_index + azi_idx] > aps_sll_th[i][k])
						&& (temp_aps_lr[temp_index + azi_idx] > temp_aps_lr[temp_index + azi_idx - 1])
						&& (temp_aps_lr[temp_index + azi_idx] > temp_aps_lr[temp_index + azi_idx + 1])
						&& (temp_aps_lr[temp_index + azi_idx] > temp_aps_lr[temp_index - azi_num_aps_step + azi_idx])
						&& (temp_aps_lr[temp_index + azi_idx] > temp_aps_lr[temp_index + azi_num_aps_step + azi_idx]))
#endif
					{
						_sp_cnt_break(peak_cnt, OBJ_AE_CANDI_NUM_TARGET_MAX);

						Peak_Candi[peak_cnt] = temp_aps_lr[temp_index + azi_idx];
						Peak_azi_idx[peak_cnt] = azi_idx;
						Peak_ele_idx[peak_cnt] = ele_idx;

#if (OBJ_AE_ADD_OBJ_ENABLE == 1)
						if ((temp_aps_lr[temp_index + azi_idx] > temp_aps_lr[temp_index + azi_idx - 1])
							&& (temp_aps_lr[temp_index + azi_idx] > temp_aps_lr[temp_index + azi_idx + 1])
							&& (temp_aps_lr[temp_index + azi_idx] > temp_aps_lr[temp_index - azi_num_aps_step + azi_idx])
							&& (temp_aps_lr[temp_index + azi_idx] > temp_aps_lr[temp_index + azi_num_aps_step + azi_idx]))
						{
							Peak_flg[peak_cnt] = 1U;
						}
						else
						{
							Peak_flg[peak_cnt] = 0U;
						}
#else
						Peak_flg[peak_cnt] = 1U;
#endif
						peak_cnt++;
					}
				}
			}

			for (ii = 0; ii < peak_cnt; ++ii)
			{
				for (j = ii + 1; j < peak_cnt; ++j)
				{

					if (Peak_Candi[ii] < Peak_Candi[j])
					{
						temp_peak = Peak_Candi[ii];
						Peak_Candi[ii] = Peak_Candi[j];
						Peak_Candi[j] = temp_peak;

						temp_azi_idx = Peak_azi_idx[ii];
						Peak_azi_idx[ii] = Peak_azi_idx[j];
						Peak_azi_idx[j] = temp_azi_idx;

						temp_ele_idx = Peak_ele_idx[ii];
						Peak_ele_idx[ii] = Peak_ele_idx[j];
						Peak_ele_idx[j] = temp_ele_idx;

						temp_peak_flg = Peak_flg[ii];
						Peak_flg[ii] = Peak_flg[j];
						Peak_flg[j] = temp_peak_flg;
					}
				}
			}

			temp_peak_cnt = 0;
			for (j = 0; j < peak_cnt; j++)
			{
				if (Peak_flg[j] == 1)
				{
					_sp_cnt_break(temp_peak_cnt, OBJ_AE_NUM_PEAK_TARGET_MAX);
					peak_azi_temp_idx[temp_peak_cnt] = Peak_azi_idx[j];
					peak_ele_temp_idx[temp_peak_cnt] = Peak_ele_idx[j];
					temp_peak_cnt++;
				}
			}

			for (j = 0; j < peak_cnt; j++)
			{
				for (ii = 0; ii < temp_peak_cnt; ii++)
				{
					azi_diff = _sp_pow2(_sp_abs(peak_azi_temp_idx[ii] - Peak_azi_idx[j]));
					ele_diff = _sp_pow2(_sp_abs(peak_ele_temp_idx[ii] - Peak_ele_idx[j]));

					if (_sp_sqrtf(azi_diff + ele_diff) < 4.0f)
					{
						Peak_near_flg[j] = 1;
					}
				}
			}

			ang_cnt = 0;
			PeakData->s16AngCnt[i][k] = 0;
			if (peak_cnt > 0)
			{
				for (j = 0; j < peak_cnt; j++)
				{
					if ((Peak_Candi[j] > aps_multi_th*Peak_Candi[0])
						&& (Peak_near_flg[j] == 1))
					{

						_sp_cnt_break(ang_cnt, OBJ_AE_NUM_TARGET_MAX);
						temp_index = i * num_azi_ele;

						num_azi = temp_aps_lr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] + 1] - temp_aps_lr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] - 1];
						den_azi = temp_aps_lr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] + 1] - (2.0f * temp_aps_lr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j]]) + temp_aps_lr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] - 1];

						num_ele = temp_aps_lr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] + azi_num_aps_step] - temp_aps_lr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] - azi_num_aps_step];
						den_ele = temp_aps_lr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] + azi_num_aps_step] - (2.0f * temp_aps_lr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j]]) + temp_aps_lr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] - azi_num_aps_step];

						dazi = 0.5f * azi_aps_step_size;
						dele = 0.5f * ele_aps_step_size;

						azi_offset = (num_azi / den_azi) * dazi;
						ele_offset = (num_ele / den_ele) * dele;
						
						if (_sp_abs(azi_offset) < 1.0f)
						{
							PeakData->f32AziAngle[i][k][ang_cnt] = PeakData->f32AziAngTable[Peak_azi_idx[j]] + azi_offset;
						}
						else
						{
							PeakData->f32AziAngle[i][k][ang_cnt] = PeakData->f32AziAngTable[Peak_azi_idx[j]];
						}

						if (_sp_abs(ele_offset) < 2.0f)
						{
							PeakData->f32EleAngle[i][k][ang_cnt] = PeakData->f32EleAngTable[Peak_ele_idx[j]] + ele_offset;
						}
						else
						{
							PeakData->f32EleAngle[i][k][ang_cnt] = PeakData->f32EleAngTable[Peak_ele_idx[j]];
						}

						PeakData->f32Power[i][k][ang_cnt] = 10.0f*_sp_log10f(temp_aps_lr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j]]);

						if (Peak_flg[j] == 1U)
						{
							PeakData->s16TrackFlag[i][k][ang_cnt] = 1;
						}
						else
						{
							PeakData->s16TrackFlag[i][k][ang_cnt] = 0;
						}
						ang_cnt++;
					}
				}
			}
			else
			{
				PeakData->f32AziAngle[i][k][0] = OBJ_AE_FAILURE_ANGLE;
				PeakData->f32EleAngle[i][k][0] = OBJ_AE_FAILURE_ANGLE;
				PeakData->f32Power[i][k][0] = 0.0f;
			}

			PeakData->s16AngCnt[i][k] = ang_cnt;

			/* for Debug */
#ifdef WIN32
			for (ele_idx = 0; ele_idx < ele_num_aps_step; ele_idx++)
			{
				for (azi_idx = 0; azi_idx < azi_num_aps_step; azi_idx++)
				{
					PeakData->f32APS[i][ele_idx * azi_num_aps_step + azi_idx] = temp_aps_lr[i * num_azi_ele + ele_idx * azi_num_aps_step + azi_idx];
				}
			}
#endif
		}
	}
}

#ifdef CUDA_ACC
static void Obj_vAngleEstimation_MR(Cuda_PeakData_t *PeakData, MultiMod_t CurMod)
#else
static void Obj_vAngleEstimation_MR(PeakData_t *PeakData, MultiMod_t CurMod)
#endif 
{
#ifdef LINUX
	struct timeval startTime, endTime;
	double diffTime;
#endif  

	uint16_t i, azi_idx, ele_idx, rx, tx, ch, j, ii, k;


	float32_t temp_abs_sum;
	float32_t aps_sll_th[OBJ_NUM_PEAK_HARM_MAX][OBJ_CO_NUM_HARMONICS_MAX];

	float32_t num_azi, den_azi, dazi;
	float32_t num_ele, den_ele, dele;
	float32_t ch_norm_factor;

	float32_t Peak_Candi[OBJ_AE_CANDI_NUM_TARGET_MAX];
	int16_t Peak_azi_idx[OBJ_AE_CANDI_NUM_TARGET_MAX];
	int16_t Peak_ele_idx[OBJ_AE_CANDI_NUM_TARGET_MAX];
	int16_t Peak_flg[OBJ_AE_CANDI_NUM_TARGET_MAX];
	int16_t Peak_near_flg[OBJ_AE_CANDI_NUM_TARGET_MAX];

	int16_t peak_cnt;
	int16_t ang_cnt;

	float32_t temp_peak;
	int16_t temp_azi_idx;
	int16_t temp_ele_idx;
	int16_t temp_peak_azi_idx;
	int16_t temp_peak_ele_idx;
	int16_t temp_peak_flg;

	cmplxf32_t temp_fft[OBJ_AE_NUM_CH_PARALLE];

	ch_norm_factor = _sp_pow2(1.0f / OBJ_AE_NUM_CH);

	int16_t azi_num_aps_step;
	int16_t ele_num_aps_step;
	float32_t sll_th;
	float32_t aps_multi_th;
	float32_t azi_aps_step_size;
	float32_t ele_aps_step_size;
	float32_t chirp_interval;
	float32_t tdm_comp_constant;
	uint32_t temp_index;
	uint32_t pre_temp_index;
	int16_t num_azi_ele;

	float32_t azi_offset, ele_offset;
	float32_t azi_diff, ele_diff;
	
	int16_t temp_peak_cnt;
	float32_t peak_azi_temp_idx[OBJ_AE_NUM_PEAK_TARGET_MAX];
	float32_t peak_ele_temp_idx[OBJ_AE_NUM_PEAK_TARGET_MAX];



	azi_num_aps_step = OBJ_AE_AZI_MR_NUM_APS_STEPS;
	ele_num_aps_step = OBJ_AE_ELE_MR_NUM_APS_STEPS;
	sll_th = OBJ_AE_MR_APS_SLL_TH;
	aps_multi_th = OBJ_AE_MR_MULTI_TARGET_TH;
	azi_aps_step_size = OBJ_AE_AZI_MR_APS_STEP_SIZE;
	ele_aps_step_size = OBJ_AE_ELE_MR_APS_STEP_SIZE;
	chirp_interval = SP_MR_CHIRP_INTERVAL;

	num_azi_ele = azi_num_aps_step * ele_num_aps_step;

#ifdef LINUX
	gettimeofday(&startTime, NULL);
#endif

	for (i = 0; i < PeakData->s16PhCnt; i++)
	{

		for (k = 0; k < 1; k++)
		{

#if (OBJ_HEXA_ARRAY_ON==1)

#ifdef CUDA_ACC
			Obj_vAryRemov(PeakData->cf32PhFFTData[i], (cmplxf32_t*)ch_fft_mr + i * OBJ_AE_NUM_CH);
#else
			Obj_vAryRemov(PeakData->cf32PhFFTData[i], ch_fft[i][k]);
#endif

#else

#ifdef CUDA_ACC
			Obj_vAryPaste(temp_fft[i][k], (cmplxf32_t*)ch_fft + i * OBJ_AE_NUM_CH);
#else
			Obj_vAryPaste(temp_fft[i][k], ch_fft[i][k]);
#endif

#endif
			if (PeakData->rdu16phFreqIdx[i].D == 0)
			{
				temp_abs_sum = _sp_pow2(PeakData->f32PhSllPow[i] * 0.5f);
			}
			else
			{
				temp_abs_sum = _sp_pow2(PeakData->f32PhSllPow[i]);
			}
			aps_sll_th[i][k] = (temp_abs_sum * (float32_t)OBJ_AE_NUM_CH) * sll_th * ch_norm_factor;
		}
	}

	cuComplex alpha;
	cuComplex beta;
	alpha.x = 1.0; alpha.y = 0.0;
	beta.x = 0.0; beta.y = 0.0;

	for (i = 0; i < PeakData->s16PhCnt; i++)
	{
		for (k = 0; k < 1; k++)
		{
			cublasCgemv(cublas_handler, CUBLAS_OP_T, OBJ_AE_NUM_CH, num_azi_ele, &alpha, (cuComplex*)PeakData->cf32SteerVec, OBJ_AE_NUM_CH, \
				ch_fft_mr + OBJ_AE_NUM_CH * (i), 1, &beta, cmplx_sum_mr + num_azi_ele * i, 1);

		}
	}


#ifdef CUDA_ACC
	cal_temp_aps << < (uint32_t)(PeakData->s16PhCnt* num_azi_ele / MAX_NUM_OF_GPU_THREAD) + 1, MAX_NUM_OF_GPU_THREAD >> > (temp_aps_mr, cmplx_sum_mr, ch_norm_factor);
#ifdef LINUX
	(cudaStreamAttachMemAsync(NULL, temp_aps_mr, 0, cudaMemAttachHost));
#else
	(cudaStreamAttachMemAsync(NULL, temp_aps_mr, 0, cudaMemAttachGlobal));
#endif
	(cudaStreamSynchronize(NULL));
#endif


	for (i = 0; i < PeakData->s16PhCnt; i++)
	{
		for (k = 0; k < 1; k++)
		{
			peak_cnt = 0;
			temp_peak_azi_idx = 0;
			temp_peak_ele_idx = 0;

			for (ele_idx = 1; ele_idx < ele_num_aps_step - 1; ele_idx++)
			{
				_sp_cnt_break(peak_cnt, OBJ_AE_CANDI_NUM_TARGET_MAX);
				for (azi_idx = 1; azi_idx < azi_num_aps_step - 1; azi_idx++)
				{

					_sp_cnt_break(peak_cnt, OBJ_AE_CANDI_NUM_TARGET_MAX);

					temp_index = i * num_azi_ele + ele_idx * azi_num_aps_step;

#if (OBJ_AE_ADD_OBJ_ENABLE == 1)
					if ((temp_aps_mr[temp_index + azi_idx] > aps_sll_th[i][k]))
#else
					if ((temp_aps_mr[temp_index + azi_idx] > aps_sll_th[i][k])
						&& (temp_aps_mr[temp_index + azi_idx] > temp_aps_mr[temp_index + azi_idx - 1])
						&& (temp_aps_mr[temp_index + azi_idx] > temp_aps_mr[temp_index + azi_idx + 1])
						&& (temp_aps_mr[temp_index + azi_idx] > temp_aps_mr[temp_index - azi_num_aps_step + azi_idx])
						&& (temp_aps_mr[temp_index + azi_idx] > temp_aps_mr[temp_index + azi_num_aps_step + azi_idx]))
#endif
					{
						_sp_cnt_break(peak_cnt, OBJ_AE_CANDI_NUM_TARGET_MAX);

						Peak_Candi[peak_cnt] = temp_aps_mr[temp_index + azi_idx];
						Peak_azi_idx[peak_cnt] = azi_idx;
						Peak_ele_idx[peak_cnt] = ele_idx;

#if (OBJ_AE_ADD_OBJ_ENABLE == 1)
						if ((temp_aps_mr[temp_index + azi_idx] > temp_aps_mr[temp_index + azi_idx - 1])
							&& (temp_aps_mr[temp_index + azi_idx] > temp_aps_mr[temp_index + azi_idx + 1])
							&& (temp_aps_mr[temp_index + azi_idx] > temp_aps_mr[temp_index - azi_num_aps_step + azi_idx])
							&& (temp_aps_mr[temp_index + azi_idx] > temp_aps_mr[temp_index + azi_num_aps_step + azi_idx]))
						{
							Peak_flg[peak_cnt] = 1U;
						}
						else
						{
							Peak_flg[peak_cnt] = 0U;
						}
#else
						Peak_flg[peak_cnt] = 1U;
#endif
						peak_cnt++;
					}
				}
			}

			for (ii = 0; ii < peak_cnt; ++ii)
			{
				for (j = ii + 1; j < peak_cnt; ++j)
				{

					if (Peak_Candi[ii] < Peak_Candi[j])
					{
						temp_peak = Peak_Candi[ii];
						Peak_Candi[ii] = Peak_Candi[j];
						Peak_Candi[j] = temp_peak;

						temp_azi_idx = Peak_azi_idx[ii];
						Peak_azi_idx[ii] = Peak_azi_idx[j];
						Peak_azi_idx[j] = temp_azi_idx;

						temp_ele_idx = Peak_ele_idx[ii];
						Peak_ele_idx[ii] = Peak_ele_idx[j];
						Peak_ele_idx[j] = temp_ele_idx;

						temp_peak_flg = Peak_flg[ii];
						Peak_flg[ii] = Peak_flg[j];
						Peak_flg[j] = temp_peak_flg;
					}
				}
			}

			temp_peak_cnt = 0;
			for( j = 0 ; j < peak_cnt; j++)
			{
				if (Peak_flg[j] == 1)
				{
					_sp_cnt_break(temp_peak_cnt, OBJ_AE_NUM_PEAK_TARGET_MAX);
					peak_azi_temp_idx[temp_peak_cnt] = Peak_azi_idx[j];
					peak_ele_temp_idx[temp_peak_cnt] = Peak_ele_idx[j];
					temp_peak_cnt++;
				}
			}

			for (j = 0; j < peak_cnt; j++)
			{
				for (ii = 0; ii < temp_peak_cnt; ii++)
				{
					azi_diff = _sp_pow2(_sp_abs(peak_azi_temp_idx[ii] - Peak_azi_idx[j]));
					ele_diff = _sp_pow2(_sp_abs(peak_ele_temp_idx[ii] - Peak_ele_idx[j]));

					if (_sp_sqrtf(azi_diff + ele_diff) < 4.0f)
					{
						Peak_near_flg[j] = 1;
					}
				}
			}

			ang_cnt = 0;
			PeakData->s16AngCnt[i][k] = 0;
			if (peak_cnt > 0)
			{
				for (j = 0; j < peak_cnt; j++)
				{
					if ((Peak_Candi[j] > aps_multi_th*Peak_Candi[0]) 
						&& (Peak_near_flg[j] == 1))
					{

						_sp_cnt_break(ang_cnt, OBJ_AE_NUM_TARGET_MAX);
						temp_index = i * ele_num_aps_step*azi_num_aps_step;

						num_azi = temp_aps_mr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] + 1] - temp_aps_mr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] - 1];
						den_azi = temp_aps_mr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] + 1] - (2.0f * temp_aps_mr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j]]) + temp_aps_mr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] - 1];

						num_ele = temp_aps_mr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] + azi_num_aps_step] - temp_aps_mr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] - azi_num_aps_step];
						den_ele = temp_aps_mr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] + azi_num_aps_step] - (2.0f * temp_aps_mr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j]]) + temp_aps_mr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] - azi_num_aps_step];

						dazi = 0.5f * azi_aps_step_size;
						dele = 0.5f * ele_aps_step_size;

						azi_offset = (num_azi / den_azi) * dazi;
						ele_offset = (num_ele / den_ele) * dele;
						
						if (_sp_abs(azi_offset) < 1.0f)
						{
							PeakData->f32AziAngle[i][k][ang_cnt] = PeakData->f32AziAngTable[Peak_azi_idx[j]] + azi_offset;
						}
						else
						{
							PeakData->f32AziAngle[i][k][ang_cnt] = PeakData->f32AziAngTable[Peak_azi_idx[j]];
						}

						if (_sp_abs(ele_offset) < 2.0f)
						{
							PeakData->f32EleAngle[i][k][ang_cnt] = PeakData->f32EleAngTable[Peak_ele_idx[j]] + ele_offset;
						}
						else
						{
							PeakData->f32EleAngle[i][k][ang_cnt] = PeakData->f32EleAngTable[Peak_ele_idx[j]];
						}

						PeakData->f32Power[i][k][ang_cnt] = 10.0f*_sp_log10f(temp_aps_mr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j]]);

						if (Peak_flg[j] == 1U)
						{
							PeakData->s16TrackFlag[i][k][ang_cnt] = 1;
						}
						else
						{
							PeakData->s16TrackFlag[i][k][ang_cnt] = 0;
						}

						ang_cnt++;
					}
				}
			}
			else
			{
				PeakData->f32AziAngle[i][k][0] = OBJ_AE_FAILURE_ANGLE;
				PeakData->f32EleAngle[i][k][0] = OBJ_AE_FAILURE_ANGLE;
				PeakData->f32Power[i][k][0] = 0.0f;
			}

			PeakData->s16AngCnt[i][k] = ang_cnt;

			/* for Debug */
#ifdef WIN32
			for (ele_idx = 0; ele_idx < ele_num_aps_step; ele_idx++)
			{
				for (azi_idx = 0; azi_idx < azi_num_aps_step; azi_idx++)
				{
					PeakData->f32APS[i][ele_idx * azi_num_aps_step + azi_idx] = temp_aps_mr[i * num_azi_ele + ele_idx * azi_num_aps_step + azi_idx];
				}
			}
#endif
		}
	}

}

#ifdef CUDA_ACC
static void Obj_vAngleEstimation_SR(Cuda_PeakData_t *PeakData, MultiMod_t CurMod)
#else
static void Obj_vAngleEstimation_SR(PeakData_t *PeakData, MultiMod_t CurMod)
#endif 
{
#ifdef LINUX
	struct timeval startTime, endTime;
	double diffTime;
#endif  

	uint16_t i, azi_idx, ele_idx, rx, tx, ch, j, ii, k;


	float32_t temp_abs_sum;
	float32_t aps_sll_th[OBJ_NUM_PEAK_HARM_MAX][OBJ_CO_NUM_HARMONICS_MAX];

#ifndef CUDA_ACC
	cmplxf32_t ch_fft[OBJ_NUM_PEAK_MAX][OBJ_CO_NUM_HARMONICS_MAX][OBJ_AE_NUM_CH_PARALLE];
	cmplxf32_t cmplx_sum;
	float32_t temp_aps[OBJ_NUM_PEAK_MAX][OBJ_CO_NUM_HARMONICS_MAX][OBJ_AE_ELE_NUM_APS_STEPS_MAX][OBJ_AE_AZI_NUM_APS_STEPS_MAX];
#endif

	float32_t num_azi, den_azi, dazi;
	float32_t num_ele, den_ele, dele;
	float32_t ch_norm_factor;

	float32_t Peak_Candi[OBJ_AE_CANDI_NUM_TARGET_MAX];
	int16_t Peak_azi_idx[OBJ_AE_CANDI_NUM_TARGET_MAX];
	int16_t Peak_ele_idx[OBJ_AE_CANDI_NUM_TARGET_MAX];
	int16_t Peak_flg[OBJ_AE_CANDI_NUM_TARGET_MAX];
	int16_t Peak_near_flg[OBJ_AE_CANDI_NUM_TARGET_MAX];

	int16_t peak_cnt;
	int16_t ang_cnt;

	float32_t temp_peak;
	int16_t temp_azi_idx;
	int16_t temp_ele_idx;
	int16_t temp_peak_azi_idx;
	int16_t temp_peak_ele_idx;
	int16_t temp_peak_flg;


	cmplxf32_t temp_fft[OBJ_AE_NUM_CH_PARALLE];

	ch_norm_factor = _sp_pow2(1.0f / OBJ_AE_NUM_CH);

	int16_t azi_num_aps_step;
	int16_t ele_num_aps_step;
	float32_t sll_th;
	float32_t aps_multi_th;
	float32_t azi_aps_step_size;
	float32_t ele_aps_step_size;
	float32_t chirp_interval;
	float32_t tdm_comp_constant;
	uint32_t temp_index;
	uint32_t pre_temp_index;

	int16_t num_azi_ele;

	float32_t azi_offset, ele_offset;
	float32_t azi_diff, ele_diff;

	int16_t temp_peak_cnt;
	float32_t peak_azi_temp_idx[OBJ_AE_NUM_PEAK_TARGET_MAX];
	float32_t peak_ele_temp_idx[OBJ_AE_NUM_PEAK_TARGET_MAX];

	azi_num_aps_step = OBJ_AE_AZI_SR_NUM_APS_STEPS;
	ele_num_aps_step = OBJ_AE_ELE_SR_NUM_APS_STEPS;
	sll_th = OBJ_AE_SR_APS_SLL_TH;
	aps_multi_th = OBJ_AE_SR_MULTI_TARGET_TH;
	azi_aps_step_size = OBJ_AE_AZI_SR_APS_STEP_SIZE;
	ele_aps_step_size = OBJ_AE_ELE_SR_APS_STEP_SIZE;
	chirp_interval = SP_SR_CHIRP_INTERVAL;

	num_azi_ele = azi_num_aps_step * ele_num_aps_step;

#ifdef LINUX
	gettimeofday(&startTime, NULL);
#endif

	for (i = 0; i < PeakData->s16PhCnt; i++)
	{

		for (k = 0; k < 1; k++)
		{

#if (OBJ_HEXA_ARRAY_ON==1)

#ifdef CUDA_ACC
			Obj_vAryRemov(PeakData->cf32PhFFTData[i], (cmplxf32_t*)ch_fft_sr + i * OBJ_AE_NUM_CH);
#else
			Obj_vAryRemov(PeakData->cf32PhFFTData[i], ch_fft[i][k]);
#endif

#else

#ifdef CUDA_ACC
			Obj_vAryPaste(temp_fft[i][k], (cmplxf32_t*)ch_fft + i * OBJ_AE_NUM_CH);
#else
			Obj_vAryPaste(temp_fft[i][k], ch_fft[i][k]);
#endif

#endif
			
			if (PeakData->rdu16phFreqIdx[i].D == 0)
			{
				temp_abs_sum = _sp_pow2(PeakData->f32PhSllPow[i] * 0.5f);
			}
			else
			{
				temp_abs_sum = _sp_pow2(PeakData->f32PhSllPow[i]);
			}

			aps_sll_th[i][k] = (temp_abs_sum * (float32_t)OBJ_AE_NUM_CH) * sll_th * ch_norm_factor;
		}
	}

	cuComplex alpha;
	cuComplex beta;
	alpha.x = 1.0; alpha.y = 0.0;
	beta.x = 0.0; beta.y = 0.0;

	for (i = 0; i < PeakData->s16PhCnt; i++)
	{
		for (k = 0; k < 1; k++)
		{
			cublasCgemv(cublas_handler, CUBLAS_OP_T, OBJ_AE_NUM_CH, num_azi_ele, &alpha, (cuComplex*)PeakData->cf32SteerVec, OBJ_AE_NUM_CH, \
				ch_fft_sr + OBJ_AE_NUM_CH * i, 1, &beta, cmplx_sum_sr + num_azi_ele * i, 1);
		}
	}


#ifdef CUDA_ACC
	cal_temp_aps << < (uint32_t)(PeakData->s16PhCnt *num_azi_ele / MAX_NUM_OF_GPU_THREAD) + 1, MAX_NUM_OF_GPU_THREAD >> > (temp_aps_sr, cmplx_sum_sr, ch_norm_factor);
#ifdef LINUX
	(cudaStreamAttachMemAsync(NULL, temp_aps_sr, 0, cudaMemAttachHost));
#else
	(cudaStreamAttachMemAsync(NULL, temp_aps_sr, 0, cudaMemAttachGlobal));
#endif
	(cudaStreamSynchronize(NULL));
#endif


	for (i = 0; i < PeakData->s16PhCnt; i++)
	{
		for (k = 0; k < 1; k++)
		{
			peak_cnt = 0;
			temp_peak_azi_idx = 0;
			temp_peak_ele_idx = 0;
			for (ele_idx = 1; ele_idx < ele_num_aps_step - 1; ele_idx++)
			{
				_sp_cnt_break(peak_cnt, OBJ_AE_CANDI_NUM_TARGET_MAX);
				for (azi_idx = 1; azi_idx < azi_num_aps_step - 1; azi_idx++)
				{
					_sp_cnt_break(peak_cnt, OBJ_AE_CANDI_NUM_TARGET_MAX);
					temp_index = i * num_azi_ele + ele_idx * azi_num_aps_step;

#if (OBJ_AE_ADD_OBJ_ENABLE == 1)
					if ((temp_aps_sr[temp_index + azi_idx] > aps_sll_th[i][k]))
#else
					if ((temp_aps_sr[temp_index + azi_idx] > aps_sll_th[i][k])
						&& (temp_aps_sr[temp_index + azi_idx] > temp_aps_sr[temp_index + azi_idx - 1])
						&& (temp_aps_sr[temp_index + azi_idx] > temp_aps_sr[temp_index + azi_idx + 1])
						&& (temp_aps_sr[temp_index + azi_idx] > temp_aps_sr[temp_index - azi_num_aps_step + azi_idx])
						&& (temp_aps_sr[temp_index + azi_idx] > temp_aps_sr[temp_index + azi_num_aps_step + azi_idx]))
#endif
					{
						_sp_cnt_break(peak_cnt, OBJ_AE_CANDI_NUM_TARGET_MAX);

						Peak_Candi[peak_cnt] = temp_aps_sr[temp_index + azi_idx];
						Peak_azi_idx[peak_cnt] = azi_idx;
						Peak_ele_idx[peak_cnt] = ele_idx;

#if (OBJ_AE_ADD_OBJ_ENABLE == 1)
						if ((temp_aps_sr[temp_index + azi_idx] > temp_aps_sr[temp_index + azi_idx - 1])
							&& (temp_aps_sr[temp_index + azi_idx] > temp_aps_sr[temp_index + azi_idx + 1])
							&& (temp_aps_sr[temp_index + azi_idx] > temp_aps_sr[temp_index - azi_num_aps_step + azi_idx])
							&& (temp_aps_sr[temp_index + azi_idx] > temp_aps_sr[temp_index + azi_num_aps_step + azi_idx]))
						{
							Peak_flg[peak_cnt] = 1U;
						}
						else
						{
							Peak_flg[peak_cnt] = 0U;
						}
#else
						Peak_flg[peak_cnt] = 1U;
#endif
						peak_cnt++;
					}
				}
			}

			for (ii = 0; ii < peak_cnt; ++ii)
			{
				for (j = ii + 1; j < peak_cnt; ++j)
				{

					if (Peak_Candi[ii] < Peak_Candi[j])
					{
						temp_peak = Peak_Candi[ii];
						Peak_Candi[ii] = Peak_Candi[j];
						Peak_Candi[j] = temp_peak;

						temp_azi_idx = Peak_azi_idx[ii];
						Peak_azi_idx[ii] = Peak_azi_idx[j];
						Peak_azi_idx[j] = temp_azi_idx;

						temp_ele_idx = Peak_ele_idx[ii];
						Peak_ele_idx[ii] = Peak_ele_idx[j];
						Peak_ele_idx[j] = temp_ele_idx;

						temp_peak_flg = Peak_flg[ii];
						Peak_flg[ii] = Peak_flg[j];
						Peak_flg[j] = temp_peak_flg;
					}
				}
			}


			temp_peak_cnt = 0;
			for (j = 0; j < peak_cnt; j++)
			{
				if (Peak_flg[j] == 1)
				{
					_sp_cnt_break(temp_peak_cnt, OBJ_AE_NUM_PEAK_TARGET_MAX);
					peak_azi_temp_idx[temp_peak_cnt] = Peak_azi_idx[j];
					peak_ele_temp_idx[temp_peak_cnt] = Peak_ele_idx[j];
					temp_peak_cnt++;
				}
			}

			for (j = 0; j < peak_cnt; j++)
			{
				for (ii = 0; ii < temp_peak_cnt; ii++)
				{
					azi_diff = _sp_pow2(_sp_abs(peak_azi_temp_idx[ii] - Peak_azi_idx[j]));
					ele_diff = _sp_pow2(_sp_abs(peak_ele_temp_idx[ii] - Peak_ele_idx[j]));

					if (_sp_sqrtf(azi_diff + ele_diff) < 4.0f)
					{
						Peak_near_flg[j] = 1;
					}
				}
			}

			ang_cnt = 0;
			PeakData->s16AngCnt[i][k] = 0;
			if (peak_cnt > 0)
			{
				for (j = 0; j < peak_cnt; j++)
				{
					if ((Peak_Candi[j] > aps_multi_th*Peak_Candi[0])
						&& (Peak_near_flg[j] == 1))
					{

						_sp_cnt_break(ang_cnt, OBJ_AE_NUM_TARGET_MAX);
						temp_index = i * num_azi_ele;

						num_azi = temp_aps_sr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] + 1] - temp_aps_sr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] - 1];
						den_azi = temp_aps_sr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] + 1] - (2.0f * temp_aps_sr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j]]) + temp_aps_sr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] - 1];

						num_ele = temp_aps_sr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] + azi_num_aps_step] - temp_aps_sr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] - azi_num_aps_step];
						den_ele = temp_aps_sr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] + azi_num_aps_step] - (2.0f * temp_aps_sr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j]]) + temp_aps_sr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j] - azi_num_aps_step];

						dazi = 0.5f * azi_aps_step_size;
						dele = 0.5f * ele_aps_step_size;

						azi_offset = (num_azi / den_azi) * dazi;
						ele_offset = (num_ele / den_ele) * dele;

						if (_sp_abs(azi_offset) < 1.0f)
						{
							PeakData->f32AziAngle[i][k][ang_cnt] = PeakData->f32AziAngTable[Peak_azi_idx[j]] + azi_offset;
						}
						else
						{
							PeakData->f32AziAngle[i][k][ang_cnt] = PeakData->f32AziAngTable[Peak_azi_idx[j]];
						}

						if (_sp_abs(ele_offset) < 2.0f)
						{
							PeakData->f32EleAngle[i][k][ang_cnt] = PeakData->f32EleAngTable[Peak_ele_idx[j]] + ele_offset;
						}
						else
						{
							PeakData->f32EleAngle[i][k][ang_cnt] = PeakData->f32EleAngTable[Peak_ele_idx[j]];
						}

						PeakData->f32Power[i][k][ang_cnt] = 10.0f*_sp_log10f(temp_aps_sr[temp_index + Peak_ele_idx[j] * azi_num_aps_step + Peak_azi_idx[j]]);

						if (Peak_flg[j] == 1U)
						{
							PeakData->s16TrackFlag[i][k][ang_cnt] = 1;
						}
						else
						{
							PeakData->s16TrackFlag[i][k][ang_cnt] = 0;
						}

						ang_cnt++;
					}
				}
			}
			else
			{
				PeakData->f32AziAngle[i][k][0] = OBJ_AE_FAILURE_ANGLE;
				PeakData->f32EleAngle[i][k][0] = OBJ_AE_FAILURE_ANGLE;
				PeakData->f32Power[i][k][0] = 0.0f;
			}

			PeakData->s16AngCnt[i][k] = ang_cnt;

			/* for Debug */
#ifdef WIN32
			for (ele_idx = 0; ele_idx < ele_num_aps_step; ele_idx++)
			{
				for (azi_idx = 0; azi_idx < azi_num_aps_step; azi_idx++)
				{
					PeakData->f32APS[i][ele_idx * azi_num_aps_step + azi_idx] = temp_aps_sr[i * num_azi_ele + ele_idx * azi_num_aps_step + azi_idx];
				}
			}
#endif
		}
	}

}


static cmplxf32_t Obj_cf32GetPhaseDiff(const cmplxf32_t a, const cmplxf32_t b)
{
	cmplxf32_t c;
	float32_t temp_mag;

	c.real = (a.real * b.real) + (a.imag * b.imag);
	c.imag = (a.imag * b.real) - (a.real * b.imag);
	temp_mag = _sp_sqrtf((c.real * c.real) + (c.imag * c.imag));

	c.real = c.real / temp_mag;
	c.imag = c.imag / temp_mag;

	return c;
}

static void Obj_vAryRemov(cmplxf32_t temp_peak_fft[], cmplxf32_t temp_ch_fft[])
{
	int16_t remov_ch_idx[OBJ_AE_NUM_CH_REMOV] = OBJ_AE_CH_REMOV_IDX;
	int16_t temp_idx;
	int16_t ch;
	int16_t cnt = 0;
	int16_t cnt_rmv = 0;

	for (ch = 0; ch < OBJ_AE_NUM_CH_PARALLE; ch++)
	{
		temp_idx = remov_ch_idx[cnt_rmv];
		if (temp_idx == ch)
		{
			cnt_rmv += 1;
		}
		else
		{
			temp_ch_fft[cnt].real = temp_peak_fft[ch].real;
			temp_ch_fft[cnt].imag = temp_peak_fft[ch].imag;
			cnt += 1;
		}
	}
}

static void Obj_vAryPaste(cmplxf32_t temp_peak_fft[], cmplxf32_t temp_ch_fft[])
{
	int16_t ch;

	for (ch = 0; ch < OBJ_AE_NUM_CH_PARALLE; ch++)
	{
		temp_ch_fft[ch].real = temp_peak_fft[ch].real;
		temp_ch_fft[ch].imag = temp_peak_fft[ch].imag;
	}
}

void alloc_peak_data_gpu_mem(void)
{
#ifdef CUDA_ACC
	size_t sizeOfcf32SteerVec_lr = OBJ_AE_ELE_LR_NUM_APS_STEPS * OBJ_AE_AZI_LR_NUM_APS_STEPS * OBJ_AE_NUM_CH * sizeof(cmplxf32_t);
	size_t sizeOfcf32SteerVec_mr = OBJ_AE_ELE_MR_NUM_APS_STEPS * OBJ_AE_AZI_MR_NUM_APS_STEPS  * OBJ_AE_NUM_CH * sizeof(cmplxf32_t);
	size_t sizeOfcf32SteerVec_sr = OBJ_AE_ELE_SR_NUM_APS_STEPS * OBJ_AE_AZI_SR_NUM_APS_STEPS  * OBJ_AE_NUM_CH * sizeof(cmplxf32_t);

	(cudaMallocManaged((void**)&(gLR_PeakData.cf32SteerVec), sizeOfcf32SteerVec_lr));
	(cudaMallocManaged((void**)&(gMR_PeakData.cf32SteerVec), sizeOfcf32SteerVec_mr));
	(cudaMallocManaged((void**)&(gSR_PeakData.cf32SteerVec), sizeOfcf32SteerVec_sr));


	/*
	size_t sizeOfch_fft = OBJ_NUM_CANDIDATE_OBJ * OBJ_CO_NUM_HARMONICS_MAX * OBJ_AE_NUM_CH * sizeof(cmplxf32_t);
	(cudaMallocManaged((void**)&ch_fft, sizeOfch_fft));

	size_t sizeOfcmplx_sum = (OBJ_CO_NUM_HARMONICS_MAX * OBJ_NUM_CANDIDATE_OBJ * OBJ_AE_AZI_NUM_APS_STEPS_MAX * OBJ_AE_ELE_NUM_APS_STEPS_MAX / MAX_NUM_OF_GPU_THREAD + 1) * MAX_NUM_OF_GPU_THREAD * sizeof(cmplxf32_t);
	(cudaMallocManaged((void**)&cmplx_sum, sizeOfcmplx_sum));

	size_t sizeOftemp_aps = (OBJ_CO_NUM_HARMONICS_MAX * OBJ_NUM_CANDIDATE_OBJ * OBJ_AE_AZI_NUM_APS_STEPS_MAX * OBJ_AE_ELE_NUM_APS_STEPS_MAX / MAX_NUM_OF_GPU_THREAD + 1) * MAX_NUM_OF_GPU_THREAD * sizeof(float32_t);
	(cudaMallocManaged((void**)&temp_aps, sizeOftemp_aps));
	*/

	size_t sizeOfch_fft_lr = OBJ_NUM_PEAK_HARM_LR * OBJ_AE_NUM_CH * sizeof(cmplxf32_t);
	size_t sizeOfch_fft_mr = OBJ_NUM_PEAK_HARM_MR * OBJ_AE_NUM_CH * sizeof(cmplxf32_t);
	size_t sizeOfch_fft_sr = OBJ_NUM_PEAK_HARM_SR * OBJ_AE_NUM_CH * sizeof(cmplxf32_t);

	(cudaMallocManaged((void**)&ch_fft_lr, sizeOfch_fft_lr));
	(cudaMallocManaged((void**)&ch_fft_mr, sizeOfch_fft_mr));
	(cudaMallocManaged((void**)&ch_fft_sr, sizeOfch_fft_sr));

	size_t sizeOfcmplx_sum_lr = (OBJ_NUM_PEAK_HARM_LR * OBJ_AE_AZI_LR_NUM_APS_STEPS * OBJ_AE_ELE_LR_NUM_APS_STEPS / MAX_NUM_OF_GPU_THREAD + 1) * MAX_NUM_OF_GPU_THREAD * sizeof(cmplxf32_t);
	size_t sizeOfcmplx_sum_mr = (OBJ_NUM_PEAK_HARM_MR * OBJ_AE_AZI_MR_NUM_APS_STEPS * OBJ_AE_ELE_MR_NUM_APS_STEPS / MAX_NUM_OF_GPU_THREAD + 1) * MAX_NUM_OF_GPU_THREAD * sizeof(cmplxf32_t);
	size_t sizeOfcmplx_sum_sr = (OBJ_NUM_PEAK_HARM_SR * OBJ_AE_AZI_SR_NUM_APS_STEPS * OBJ_AE_ELE_SR_NUM_APS_STEPS / MAX_NUM_OF_GPU_THREAD + 1) * MAX_NUM_OF_GPU_THREAD * sizeof(cmplxf32_t);

	(cudaMallocManaged((void**)&cmplx_sum_lr, sizeOfcmplx_sum_lr));
	(cudaMallocManaged((void**)&cmplx_sum_mr, sizeOfcmplx_sum_mr));
	(cudaMallocManaged((void**)&cmplx_sum_sr, sizeOfcmplx_sum_sr));


	size_t sizeOftemp_aps_lr = (OBJ_NUM_PEAK_HARM_LR * OBJ_AE_AZI_LR_NUM_APS_STEPS * OBJ_AE_ELE_LR_NUM_APS_STEPS / MAX_NUM_OF_GPU_THREAD + 1) * MAX_NUM_OF_GPU_THREAD * sizeof(float32_t);
	size_t sizeOftemp_aps_mr = (OBJ_NUM_PEAK_HARM_MR * OBJ_AE_AZI_MR_NUM_APS_STEPS * OBJ_AE_ELE_MR_NUM_APS_STEPS / MAX_NUM_OF_GPU_THREAD + 1) * MAX_NUM_OF_GPU_THREAD * sizeof(float32_t);
	size_t sizeOftemp_aps_sr = (OBJ_NUM_PEAK_HARM_SR * OBJ_AE_AZI_SR_NUM_APS_STEPS * OBJ_AE_ELE_SR_NUM_APS_STEPS / MAX_NUM_OF_GPU_THREAD + 1) * MAX_NUM_OF_GPU_THREAD * sizeof(float32_t);

	(cudaMallocManaged((void**)&temp_aps_lr, sizeOftemp_aps_lr));
	(cudaMallocManaged((void**)&temp_aps_mr, sizeOftemp_aps_mr));
	(cudaMallocManaged((void**)&temp_aps_sr, sizeOftemp_aps_sr));


	cublasCreate(&cublas_handler);
#endif
}


