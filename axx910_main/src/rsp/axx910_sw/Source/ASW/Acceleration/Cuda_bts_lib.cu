#ifdef CUDA_ACC

#ifdef WIN32
extern "C" {
#include "Cuda_bts_lib.cuh"
}
#else
#include "Cuda_bts_lib.cuh"
#endif
#include "device_launch_parameters.h"
#include <iostream>
#include <chrono>
#include <cufft.h>
#include <cublas_v2.h>
#include <cuda_runtime_api.h>
#include <cuda_runtime.h>
using namespace std;
void Init_cuda_for_rm(void);
void Init_cuda_for_lms_mode(void);
void windowing_2d(uint32_t num_tx, uint32_t num_rx, uint32_t num_chirps, uint32_t num_samples, int16_t * input, cufftReal * output, float32_t * wincoeff);

cublasHandle_t cublas_handle;

// direct fft2d 
cufftHandle rm_plan_direct_2d_fft;
cufftHandle plan_direct_2d_fft;

cufftReal* lr_windowed_1d_data;
cufftReal* mr_windowed_1d_data;
cufftReal* sr_windowed_1d_data;
cufftReal* rm_windowed_1d_data;

extern float32_t Sim_PowSpectrum[OBJ_NUM_FFT_R][OBJ_NUM_FFT_D];

/********************/
/* CUDA ERROR CHECK */
/********************/
#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char* file, int line, bool abort = true)
{
	if (code != cudaSuccess)
	{
		fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
		if (abort) { getchar(); exit(code); }
	}
}

/*********************/
/* CUFFT ERROR CHECK */
/*********************/
static const char* _cudaGetErrorEnum(cufftResult error)
{
	switch (error)
	{
	case CUFFT_SUCCESS:
		return "CUFFT_SUCCESS";

	case CUFFT_INVALID_PLAN:
		return "CUFFT_INVALID_PLAN";

	case CUFFT_ALLOC_FAILED:
		return "CUFFT_ALLOC_FAILED";

	case CUFFT_INVALID_TYPE:
		return "CUFFT_INVALID_TYPE";

	case CUFFT_INVALID_VALUE:
		return "CUFFT_INVALID_VALUE";

	case CUFFT_INTERNAL_ERROR:
		return "CUFFT_INTERNAL_ERROR";

	case CUFFT_EXEC_FAILED:
		return "CUFFT_EXEC_FAILED";

	case CUFFT_SETUP_FAILED:
		return "CUFFT_SETUP_FAILED";

	case CUFFT_INVALID_SIZE:
		return "CUFFT_INVALID_SIZE";

	case CUFFT_UNALIGNED_DATA:
		return "CUFFT_UNALIGNED_DATA";
	}

	return "<unknown>";
}

#define cufftSafeCall(err)      __cufftSafeCall(err, __FILE__, __LINE__)
inline void __cufftSafeCall(cufftResult err, const char* file, const int line)
{
	if (CUFFT_SUCCESS != err) {
		fprintf(stderr, "CUFFT error in file '%s', line %d\n %s\nerror %d: %s\nterminating!\n", __FILE__, __LINE__, err, \
			_cudaGetErrorEnum(err)); \
			cudaDeviceReset(); assert(0); \
	}
}

/**********************/
/* CUBLAS ERROR CHECK */
/**********************/
static const char* _cudaCublasGetErrorEnum(cublasStatus_t error)
{
	switch (error)
	{
	case CUBLAS_STATUS_SUCCESS:
		return "CUBLAS_STATUS_SUCCESS";

	case CUBLAS_STATUS_NOT_INITIALIZED:
		return "CUBLAS_STATUS_NOT_INITIALIZED";

	case CUBLAS_STATUS_ALLOC_FAILED:
		return "CUBLAS_STATUS_ALLOC_FAILED";

	case CUBLAS_STATUS_INVALID_VALUE:
		return "CUBLAS_STATUS_INVALID_VALUE";

	case CUBLAS_STATUS_ARCH_MISMATCH:
		return "CUBLAS_STATUS_ARCH_MISMATCH";

	case CUBLAS_STATUS_MAPPING_ERROR:
		return "CUBLAS_STATUS_MAPPING_ERROR";

	case CUBLAS_STATUS_EXECUTION_FAILED:
		return "CUBLAS_STATUS_EXECUTION_FAILED";

	case CUBLAS_STATUS_INTERNAL_ERROR:
		return "CUBLAS_STATUS_INTERNAL_ERROR";

	case CUBLAS_STATUS_NOT_SUPPORTED:
		return "CUBLAS_STATUS_NOT_SUPPORTED";

	case CUBLAS_STATUS_LICENSE_ERROR:
		return "CUBLAS_STATUS_LICENSE_ERROR";
	}

	return "<unknown>";
}

#define cublasSafeCall(err)      __cublasSafeCall(err, __FILE__, __LINE__)
inline void __cublasSafeCall(cublasStatus_t err, const char* file, const int line)
{
	if (CUBLAS_STATUS_SUCCESS != err) {
		fprintf(stderr, "Cublas error in file '%s', line %d\n %s\nerror %d: %s\nterminating!\n", __FILE__, __LINE__, err, \
			_cudaCublasGetErrorEnum(err)); \
			cudaDeviceReset(); assert(0); \
	}
}

__global__ void cal_mag2D(cmplxf32_t* src, float* dst, int src_column_size)
{
	int ti = threadIdx.x;
	int bi = blockIdx.x;
	int src_index = gridDim.x * src_column_size*(blockIdx.y * gridDim.z + blockIdx.z) + (bi * src_column_size) + ti;
	int dst_index = gridDim.x*blockDim.x*(blockIdx.y*gridDim.z + blockIdx.z) + bi + ti * gridDim.x;
	dst[dst_index] = (src[src_index].real) * (src[src_index].real) + (src[src_index].imag) * (src[src_index].imag);
}
__global__ void sum_mag(int txrx_size, int offset, float* src, float* dst)
{
	int ti = threadIdx.x;
	int bi = blockIdx.x;
	int bd = blockDim.x * (bi + offset);
	int arr_size = blockDim.x * (gridDim.x + offset);
	int index = bd + ti;

	for (int i = 0; i < txrx_size; i++)
	{
		dst[index] += src[arr_size * i + index];
	}

	dst[index] = sqrt(dst[index]);
}

__global__ void cal_nci(cmplxf32_t* src, float* dst, int offset, int num_tx, int num_rx) // src : cf32fftData_2D, dst : chrips x samples
{
	int ti = threadIdx.x;
	int ci = blockIdx.x;
	int dst_index = 0;
	int src_index = 0;
	dst_index = blockDim.x*ci + ti;
	for (int txrx = 0; txrx < num_tx*num_rx; txrx++) {
		src_index = (gridDim.x * blockDim.x)*(txrx)+ci * blockDim.x + ti;
		dst[dst_index] += (src[src_index].real) * (src[src_index].real) + (src[src_index].imag) * (src[src_index].imag);
	}
	// sqrt
	dst[dst_index] = sqrt(dst[dst_index]);
}
__global__ void transpose_nci(float* src, float* dst, int offset)
{
	int ti = threadIdx.x;
	int ci = blockIdx.x + offset;
	int dst_index = blockDim.x*ci + ti;
	int src_index = ti * (gridDim.x + offset + 1) + ci;
	dst[dst_index] = src[src_index];
}
__global__ void window_2d_coeff_mul(int16_t* src, cufftReal* dst, float32_t* coeff)
{
	int ti = threadIdx.x;
	int bi = blockIdx.x;
	int index = bi * blockDim.x + ti;

	dst[index] = (float32_t)(src[index]) * coeff[index];
}

void windowing_2d(uint32_t num_tx, uint32_t num_rx, uint32_t num_chirps, uint32_t num_samples, int16_t* input, cufftReal* output, float32_t* wincoeff)
{
	for (int tx = 0; tx < num_tx; tx++)
	{
		for (int rx = 0; rx < num_rx; rx++)
		{
			window_2d_coeff_mul << <num_chirps, num_samples >> > (input + tx * num_rx * num_samples * num_chirps + rx * num_samples * num_chirps, \
				output + tx * num_rx * num_samples * num_chirps + rx * num_samples * num_chirps, \
				wincoeff);
		}
	}
}
#ifdef WIN32
extern "C"
#endif
int fft_2d_cuda(void)
{
	// 2D Windowing
	windowing_2d(SP_NUM_TX, SP_NUM_RX, SP_NUM_CHIRPS, SP_NUM_SAMPLES, gLR_PreData.s16adcData, lr_windowed_1d_data, gLR_PreWindow.cf32WinCoeffMap);
	windowing_2d(SP_NUM_TX, SP_NUM_RX, SP_NUM_CHIRPS, SP_NUM_SAMPLES, gMR_PreData.s16adcData, mr_windowed_1d_data, gMR_PreWindow.cf32WinCoeffMap);
	windowing_2d(SP_NUM_TX, SP_NUM_RX, SP_NUM_CHIRPS, SP_NUM_SAMPLES, gSR_PreData.s16adcData, sr_windowed_1d_data, gSR_PreWindow.cf32WinCoeffMap);
	windowing_2d(SP_RM_NUM_TX, SP_NUM_RX, SP_RM_NUM_CHIRPS, SP_RM_NUM_SAMPLES, gRM_PreData.s16adcData, rm_windowed_1d_data, gRM_PreWindow.cf32WinCoeffMap);

	gpuErrchk(cudaStreamSynchronize(NULL));

	// 2D FFT
	int src_index = 0;
	int dst_index = 0;
	for (int tx = 0; tx < SP_RM_NUM_TX; tx++) {
		for (int rx = 0; rx < SP_NUM_RX; rx++) {
			src_index = SP_RM_NUM_SAMPLES * SP_RM_NUM_CHIRPS*(tx * SP_NUM_RX + rx);
			dst_index = (SP_RM_NUM_SAMPLES *0.5 + 1) * SP_RM_NUM_CHIRPS*(tx * SP_NUM_RX + rx);
			cufftSafeCall(cufftExecR2C(rm_plan_direct_2d_fft, (cufftReal*)(rm_windowed_1d_data + src_index), (cufftComplex*)(gRM_PreData.cf32fftData_2D + dst_index)));
		}
	}
	for (int tx = 0; tx < SP_NUM_TX; tx++) {
		for (int rx = 0; rx < SP_NUM_RX; rx++) {
			src_index = SP_NUM_SAMPLES * SP_NUM_CHIRPS*(tx * SP_NUM_RX + rx);
			dst_index = (SP_NUM_SAMPLES*0.5 + 1)*SP_NUM_CHIRPS*(tx * SP_NUM_RX + rx);
			cufftSafeCall(cufftExecR2C(plan_direct_2d_fft, (cufftReal*)(lr_windowed_1d_data + src_index), (cufftComplex*)(gLR_PreData.cf32fftData_2D + dst_index)));
			cufftSafeCall(cufftExecR2C(plan_direct_2d_fft, (cufftReal*)(mr_windowed_1d_data + src_index), (cufftComplex*)(gMR_PreData.cf32fftData_2D + dst_index)));
			cufftSafeCall(cufftExecR2C(plan_direct_2d_fft, (cufftReal*)(sr_windowed_1d_data + src_index), (cufftComplex*)(gSR_PreData.cf32fftData_2D + dst_index)));
		}
	}

#ifdef LINUX
	gpuErrchk(cudaStreamAttachMemAsync(NULL, gLR_PreData.cf32fftData_2D, 0, cudaMemAttachHost));
	gpuErrchk(cudaStreamAttachMemAsync(NULL, gMR_PreData.cf32fftData_2D, 0, cudaMemAttachHost));
	gpuErrchk(cudaStreamAttachMemAsync(NULL, gSR_PreData.cf32fftData_2D, 0, cudaMemAttachHost));
	gpuErrchk(cudaStreamAttachMemAsync(NULL, gRM_PreData.cf32fftData_2D, 0, cudaMemAttachHost));
#else
	gpuErrchk(cudaStreamAttachMemAsync(NULL, gLR_PreData.cf32fftData_2D, 0, cudaMemAttachGlobal));
	gpuErrchk(cudaStreamAttachMemAsync(NULL, gMR_PreData.cf32fftData_2D, 0, cudaMemAttachGlobal));
	gpuErrchk(cudaStreamAttachMemAsync(NULL, gSR_PreData.cf32fftData_2D, 0, cudaMemAttachGlobal));
	gpuErrchk(cudaStreamAttachMemAsync(NULL, gRM_PreData.cf32fftData_2D, 0, cudaMemAttachGlobal));
#endif
	gpuErrchk(cudaStreamSynchronize(NULL));

	return 0;
}


#ifdef WIN32
extern "C"
#endif
void Init_cuda(void)
{
	Init_cuda_for_rm();
	Init_cuda_for_lms_mode();

	cublasSafeCall(cublasCreate(&cublas_handle));
}

void Init_cuda_for_rm(void)
{
	// Reference Mode
	size_t rm_sizeOfs16adcData = SP_RM_NUM_CHIRPS * SP_RM_NUM_TX * SP_NUM_RX * SP_RM_NUM_SAMPLES * sizeof(int16_t);
	size_t rm_sizeOfWindowed1dData = SP_RM_NUM_CHIRPS * SP_RM_NUM_TX * SP_NUM_RX * SP_RM_NUM_FFT_R * sizeof(cmplxf32_t);
	size_t rm_sizeOfcf32fftData_2D = (SP_RM_NUM_FFT_R *0.5 + 1) * SP_RM_NUM_TX * SP_NUM_RX * SP_RM_NUM_FFT_D * sizeof(cmplxf32_t);
	gpuErrchk(cudaMallocManaged((void**)&(gRM_PreData.s16adcData), rm_sizeOfs16adcData));
	gpuErrchk(cudaMallocManaged((void**)&rm_windowed_1d_data, rm_sizeOfWindowed1dData));
	gpuErrchk(cudaMallocManaged((void**)&(gRM_PreData.cf32fftData_2D), rm_sizeOfcf32fftData_2D));
	size_t rm_sizeOfcf32WinCoeffMap = SP_RM_NUM_FFT_R * SP_RM_NUM_FFT_D * sizeof(float32_t);
	gpuErrchk(cudaMallocManaged((void**)&(gRM_PreWindow.cf32WinCoeffMap), rm_sizeOfcf32WinCoeffMap));
	size_t rm_sizeOfgPhaseCal = SP_RM_NUM_TX * SP_NUM_RX * sizeof(cmplxf32_t);
	gpuErrchk(cudaMallocManaged((void**)&gPhaseCal.f32RM_PhaseCal, rm_sizeOfgPhaseCal));
	size_t rm_sizeOff32PowSpectrum = SP_RM_NUM_FFT_R_HALF * SP_RM_NUM_FFT_D * sizeof(float32_t);
	gpuErrchk(cudaMallocManaged((void**)&(gRM_BeamData.f32PowSpectrum), rm_sizeOff32PowSpectrum));
	size_t rm_sizeOff32PowSpectrum_temp = (SP_RM_NUM_FFT_R_HALF + 1) * SP_RM_NUM_FFT_D * sizeof(float32_t);
	gpuErrchk(cudaMallocManaged((void**)&(gRM_BeamData.f32PowSpectrum_temp), rm_sizeOff32PowSpectrum_temp));

	cufftSafeCall(cufftPlan2d(&rm_plan_direct_2d_fft, SP_RM_NUM_FFT_D, SP_RM_NUM_SAMPLES, CUFFT_R2C));
}

void Init_cuda_for_lms_mode(void)
{
	// LMS Mode
	size_t sizeOfs16adcData = SP_NUM_CHIRPS * SP_NUM_TX * SP_NUM_RX * SP_NUM_SAMPLES * sizeof(int16_t);
	size_t sizeOfWindowed1dData = SP_NUM_CHIRPS * SP_NUM_TX * SP_NUM_RX * SP_NUM_FFT_R * sizeof(cufftReal);
	size_t sizeOfcf32fftData_2D = (SP_NUM_FFT_R*0.5 + 1) * SP_NUM_TX * SP_NUM_RX * SP_NUM_FFT_D * sizeof(cmplxf32_t);
	gpuErrchk(cudaMallocManaged((void**)&(gLR_PreData.s16adcData), sizeOfs16adcData));
	gpuErrchk(cudaMallocManaged((void**)&(gMR_PreData.s16adcData), sizeOfs16adcData));
	gpuErrchk(cudaMallocManaged((void**)&(gSR_PreData.s16adcData), sizeOfs16adcData));
	gpuErrchk(cudaMallocManaged((void**)&lr_windowed_1d_data, sizeOfWindowed1dData));
	gpuErrchk(cudaMallocManaged((void**)&mr_windowed_1d_data, sizeOfWindowed1dData));
	gpuErrchk(cudaMallocManaged((void**)&sr_windowed_1d_data, sizeOfWindowed1dData));
	gpuErrchk(cudaMallocManaged((void**)&(gLR_PreData.cf32fftData_2D), sizeOfcf32fftData_2D));
	gpuErrchk(cudaMallocManaged((void**)&(gMR_PreData.cf32fftData_2D), sizeOfcf32fftData_2D));
	gpuErrchk(cudaMallocManaged((void**)&(gSR_PreData.cf32fftData_2D), sizeOfcf32fftData_2D));

	size_t sizeOfcf32WinCoeffMap = SP_NUM_FFT_R * SP_NUM_FFT_D * sizeof(float32_t);
	gpuErrchk(cudaMallocManaged((void**)&(gLR_PreWindow.cf32WinCoeffMap), sizeOfcf32WinCoeffMap));
	gpuErrchk(cudaMallocManaged((void**)&(gMR_PreWindow.cf32WinCoeffMap), sizeOfcf32WinCoeffMap));
	gpuErrchk(cudaMallocManaged((void**)&(gSR_PreWindow.cf32WinCoeffMap), sizeOfcf32WinCoeffMap));

	size_t sizeOfgPhaseCal = SP_NUM_TX * SP_NUM_RX * sizeof(cmplxf32_t);
	gpuErrchk(cudaMallocManaged((void**)&gPhaseCal.f32LR_PhaseCal, sizeOfgPhaseCal));
	gpuErrchk(cudaMallocManaged((void**)&gPhaseCal.f32MR_PhaseCal, sizeOfgPhaseCal));
	gpuErrchk(cudaMallocManaged((void**)&gPhaseCal.f32SR_PhaseCal, sizeOfgPhaseCal));

	size_t sizeOff32PowSpectrum_temp = (SP_NUM_FFT_R_HALF + 1) * SP_NUM_FFT_D * sizeof(float32_t);
	gpuErrchk(cudaMallocManaged((void**)&(gLR_BeamData.f32PowSpectrum_temp), sizeOff32PowSpectrum_temp));
	gpuErrchk(cudaMallocManaged((void**)&(gMR_BeamData.f32PowSpectrum_temp), sizeOff32PowSpectrum_temp));
	gpuErrchk(cudaMallocManaged((void**)&(gSR_BeamData.f32PowSpectrum_temp), sizeOff32PowSpectrum_temp));

	size_t sizeOff32PowSpectrum = SP_NUM_FFT_R_HALF * SP_NUM_FFT_D * sizeof(float32_t);
	gpuErrchk(cudaMallocManaged((void**)&(gLR_BeamData.f32PowSpectrum), sizeOff32PowSpectrum));
	gpuErrchk(cudaMallocManaged((void**)&(gMR_BeamData.f32PowSpectrum), sizeOff32PowSpectrum));
	gpuErrchk(cudaMallocManaged((void**)&(gSR_BeamData.f32PowSpectrum), sizeOff32PowSpectrum));

	cufftSafeCall(cufftPlan2d(&plan_direct_2d_fft, SP_NUM_FFT_D, SP_NUM_SAMPLES, CUFFT_R2C));
}

#ifdef WIN32
extern "C"
#endif
void Obj_vNCI_cuda(uint32_t num_tx, uint32_t num_rx, uint32_t num_fft_r_half, uint32_t num_fft_d, uint32_t nci_range_init_idx, Cuda_PreData_t * PreData, Cuda_BeamData_t * BeamData)
{
	int offset = nci_range_init_idx;
	cal_nci << <num_fft_r_half + 1, num_fft_d >> > (PreData->cf32fftData_2D, BeamData->f32PowSpectrum_temp, offset, num_tx, num_rx);	
	transpose_nci << <num_fft_r_half - offset, num_fft_d >> > (BeamData->f32PowSpectrum_temp, BeamData->f32PowSpectrum, offset);
#ifdef LINUX
	gpuErrchk(cudaStreamAttachMemAsync(NULL, BeamData->f32PowSpectrum, 0, cudaMemAttachHost));
#else
	gpuErrchk(cudaStreamAttachMemAsync(NULL, BeamData->f32PowSpectrum, 0, cudaMemAttachGlobal));
#endif
	gpuErrchk(cudaStreamSynchronize(NULL));

}

#endif