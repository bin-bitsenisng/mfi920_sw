/*************************************************

File name: cuda_fft.cu
Author: David
Description: CUDA based Range & Doppler FFT including windowing
주의사항: raw data의 배열이 다음과 같다고 가정함. rawdata[SP_NUM_TX][SP_NUM_RX][SP_NUM_CHIRPS][SP_NUM_SAMPLES]

*************************************************/

#include <iostream>
#include <chrono>
#include <cufft.h>
#include <cublas_v2.h>
#include <cublasXt.h>
#include <cuda_runtime_api.h>
#include <cuda_runtime.h>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
//#include<io.h>
#include <assert.h>
using namespace std;
#include "device_launch_parameters.h"

#define SP_PI				3.141592653589793f

#define SP_NUM_CHIRPS		32//64
#define SP_NUM_TX			12//2
#define SP_NUM_RX			16//8
#define SP_NUM_SAMPLES		1024//1024

#define SP_NUM_FFT_R        SP_NUM_SAMPLES
#define SP_NUM_FFT_R_HALF   (SP_NUM_FFT_R / 2)
#define SP_NUM_FFT_D        SP_NUM_CHIRPS

#define BATCH_SIZE_F_1D		SP_NUM_CHIRPS * SP_NUM_TX * SP_NUM_RX
#define BATCH_SIZE_S_1D		SP_NUM_FFT_R_HALF * SP_NUM_TX * SP_NUM_RX

uint16_t* s16adcData;
cufftComplex* windowed_1d_data;
cufftComplex* cf32fftData_1D;
cufftComplex* windowed_2d_data;
cufftComplex* transposed_data;
cufftComplex* cf32fftData_2D;

cufftComplex* cf32WinCoeff1D;
float* f32WinCoeff2D;

cufftHandle plan_first_1d_fft;
cufftHandle plan_second_1d_fft;
cublasHandle_t cublas_handle;

/********************/
/* CUDA ERROR CHECK */
/********************/
#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, char *file, int line, bool abort=true)
{
    if (code != cudaSuccess) 
    {
        fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
        if (abort) { getchar(); exit(code); }
    }
}

/*********************/
/* CUFFT ERROR CHECK */
/*********************/
static const char *_cudaGetErrorEnum(cufftResult error)
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
inline void __cufftSafeCall(cufftResult err, const char *file, const int line)
{
    if( CUFFT_SUCCESS != err) {
        fprintf(stderr, "CUFFT error in file '%s', line %d\n %s\nerror %d: %s\nterminating!\n",__FILE__, __LINE__,err, \
                           _cudaGetErrorEnum(err)); \
        cudaDeviceReset(); assert(0); \
    }
}

/**********************/
/* CUBLAS ERROR CHECK */
/**********************/
static const char *_cudaCublasGetErrorEnum(cublasStatus_t error)
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
inline void __cublasSafeCall(cublasStatus_t err, const char *file, const int line)
{
    if( CUBLAS_STATUS_SUCCESS != err) {
        fprintf(stderr, "Cublas error in file '%s', line %d\n %s\nerror %d: %s\nterminating!\n",__FILE__, __LINE__,err, \
                           _cudaCublasGetErrorEnum(err)); \
        cudaDeviceReset(); assert(0); \
    }
}

__global__ void window_1d_coeff_mul(uint16_t* src, cufftComplex* dst, cufftComplex* coeff)
{
	int ti = threadIdx.x;
	int bi = blockIdx.x;
	int offset = bi * blockDim.x;

	dst[offset + ti].x = (float)(src[offset + ti]) * coeff[ti].x;
	dst[offset + ti].y = 0.0f;
}

__global__ void window_2d_coeff_mul(cufftComplex* src, cufftComplex* dst, int size, float* coeff)
{
	int ti = threadIdx.x;
	int bi = blockIdx.x;
	int dst_offset = bi*size;
	int src_offset = dst_offset*2;

	dst[dst_offset + ti].x = src[src_offset + ti].x * coeff[bi];
	dst[dst_offset + ti].y = src[src_offset + ti].y * coeff[bi];
}

int FFT_2d_cuda(void)
{	
	chrono::system_clock::time_point time_start, time_end, total_time_start, total_time_end;

	// Init temporal input data	
	for (int tx = 0; tx < SP_NUM_TX; tx++)
	{
		for (int rx = 0; rx < SP_NUM_RX; rx++)
		{
			for (int di = 0; di < SP_NUM_CHIRPS; di++)
			{
				for (int ri = 0; ri < SP_NUM_SAMPLES; ri++)
				{
					s16adcData[SP_NUM_CHIRPS*SP_NUM_SAMPLES*(tx*SP_NUM_RX+rx) + SP_NUM_SAMPLES*di + ri] = (ri + rx + tx + di) * 10;
				}
			}
		}
	}

	total_time_start = chrono::system_clock::now();
	
	// time_start = chrono::system_clock::now();
	// First Windowing
	window_1d_coeff_mul<<<SP_NUM_CHIRPS*SP_NUM_TX*SP_NUM_RX, SP_NUM_SAMPLES>>>(s16adcData, windowed_1d_data, cf32WinCoeff1D);

	// cudaStreamAttachMemAsync(NULL, windowed_1d_data, 0, cudaMemAttachHost);
	// cudaStreamSynchronize(NULL);	
	// time_end = chrono::system_clock::now();
	// cout << "First Windowing takes " << chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() << " us" << endl << endl;

#ifdef DATA_LOG
	cudaStreamAttachMemAsync(NULL, windowed_1d_data, 0, cudaMemAttachHost);
	cudaStreamSynchronize(NULL);

	printf("windowed 1d data..\n");

	for(int tx = 0; tx < SP_NUM_TX; tx++)
	{
		for(int rx = 0; rx < SP_NUM_RX; rx++)
		{
			for (int di = 0; di < SP_NUM_CHIRPS; di++)
			{
				for (int ri = 0; ri < SP_NUM_SAMPLES; ri++)
				{
					printf("[%f, %f]\n", windowed_1d_data[SP_NUM_CHIRPS*SP_NUM_SAMPLES*(tx*SP_NUM_RX+rx) + SP_NUM_SAMPLES*di + ri].x, \
										windowed_1d_data[SP_NUM_CHIRPS*SP_NUM_SAMPLES*(tx*SP_NUM_RX+rx) + SP_NUM_SAMPLES*di + ri].y);
				}
				printf("\n");
			}
		}
	}
#endif

	// time_start = chrono::system_clock::now();
	// First 1D fft
	cufftSafeCall(cufftExecC2C(plan_first_1d_fft, windowed_1d_data, cf32fftData_1D, CUFFT_FORWARD));
	// cudaStreamAttachMemAsync(NULL, cf32fftData_1D, 0, cudaMemAttachHost);
	// cudaStreamSynchronize(NULL);
	// time_end = chrono::system_clock::now();
	// cout << "First FFT takes " << chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() << " us" << endl << endl;
	
#ifdef DATA_LOG
	// Prefetch 'fft_1d_result' to CPU as just to check data
	cudaStreamAttachMemAsync(NULL, cf32fftData_1D, 0, cudaMemAttachHost);
	cudaStreamSynchronize(NULL);

	printf("fft_1d_result..\n");

	for(int tx = 0; tx < SP_NUM_TX; tx++)
	{
		for(int rx = 0; rx < SP_NUM_RX; rx++)
		{
			for (int di = 0; di < SP_NUM_CHIRPS; di++)
			{
				for (int ri = 0; ri < SP_NUM_SAMPLES; ri++)
				{
					printf("[%f, %f]\n", cf32fftData_1D[SP_NUM_CHIRPS*SP_NUM_SAMPLES*(tx*SP_NUM_RX+rx) + SP_NUM_SAMPLES*di + ri].x, \
									cf32fftData_1D[SP_NUM_CHIRPS*SP_NUM_SAMPLES*(tx*SP_NUM_RX+rx) + SP_NUM_SAMPLES*di + ri].y);
				}
				printf("\n");
			}
		}
	}
#endif

	// time_start = chrono::system_clock::now();
	// Second Windowing
	window_2d_coeff_mul<<<SP_NUM_FFT_D*SP_NUM_TX*SP_NUM_RX, SP_NUM_FFT_R_HALF>>>(cf32fftData_1D, windowed_2d_data, SP_NUM_FFT_R_HALF, f32WinCoeff2D);

	// cudaStreamAttachMemAsync(NULL, windowed_2d_data, 0, cudaMemAttachHost);
	// cudaStreamSynchronize(NULL);
	// time_end = chrono::system_clock::now();
	// cout << "Second Windowing takes " << chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() << " us" << endl << endl;

#ifdef DATA_LOG
	// Prefetch 'windowed_2d_data' to CPU as just to check data
	cudaStreamAttachMemAsync(NULL, windowed_2d_data, 0, cudaMemAttachHost);
	cudaStreamSynchronize(NULL);

	printf("windowed_2d_data..\n");
	for(int tx = 0; tx < SP_NUM_TX; tx++)
	{
		for(int rx = 0; rx < SP_NUM_RX; rx++)
		{
			for (int di = 0; di < SP_NUM_FFT_D; di++)
			{
				for (int ri = 0; ri < SP_NUM_FFT_R_HALF; ri++)
				{
					printf("[%f, %f]\n", windowed_2d_data[SP_NUM_FFT_D*SP_NUM_FFT_R_HALF*(tx*SP_NUM_RX+rx) + di*SP_NUM_FFT_R_HALF + ri].x, \
											windowed_2d_data[SP_NUM_FFT_D*SP_NUM_FFT_R_HALF*(tx*SP_NUM_RX+rx) + di*SP_NUM_FFT_R_HALF + ri].y);
				}
				printf("\n");
			}
		}
	}
#endif

	// Transpose
	cuComplex alpha;
	cuComplex beta;
	alpha.x = 1.0; alpha.y = 0.0;
	beta.x = 0.0; beta.y = 0.0;

	//time_start = chrono::system_clock::now();
	for(int tx = 0; tx < SP_NUM_TX; tx++)
	{
		for(int rx = 0; rx < SP_NUM_RX; rx++)
		{
			cublasSafeCall(cublasCgeam(cublas_handle, CUBLAS_OP_T, CUBLAS_OP_N, SP_NUM_CHIRPS, SP_NUM_FFT_R_HALF, &alpha, windowed_2d_data + SP_NUM_FFT_D*SP_NUM_FFT_R_HALF*(tx*SP_NUM_RX+rx), SP_NUM_FFT_R_HALF, &beta, NULL, SP_NUM_CHIRPS, transposed_data + SP_NUM_FFT_D*SP_NUM_FFT_R_HALF*(tx*SP_NUM_RX+rx), SP_NUM_CHIRPS));
		}
	}
	// cudaStreamAttachMemAsync(NULL, transposed_data, 0, cudaMemAttachHost);
	// cudaStreamSynchronize(NULL);
	// time_end = chrono::system_clock::now();
	// cout << "Transpose takes " << chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() << " us" << endl << endl;

#ifdef DATA_LOG
	// Prefetch 'transposed_data' to CPU as just to check data	
	cudaStreamAttachMemAsync(NULL, transposed_data, 0, cudaMemAttachHost);
	cudaStreamSynchronize(NULL);

	printf("transposed_data..\n");
	for(int tx = 0; tx < SP_NUM_TX; tx++)
	{
		for(int rx = 0; rx < SP_NUM_RX; rx++)
		{
			for (int di = 0; di < SP_NUM_FFT_R_HALF; di++)
			{
				for (int ri = 0; ri < SP_NUM_FFT_D; ri++)
				{
					printf("[%f, %f]\n", transposed_data[SP_NUM_FFT_R_HALF*SP_NUM_FFT_D*(tx*SP_NUM_RX+rx) + di*SP_NUM_FFT_D + ri].x, \
											transposed_data[SP_NUM_FFT_R_HALF*SP_NUM_FFT_D*(tx*SP_NUM_RX+rx) + di*SP_NUM_FFT_D + ri].y);
				}
				printf("\n");
			}
		}
	}
#endif

	// time_start = chrono::system_clock::now();
	// Second 1D fft 
	cufftSafeCall(cufftExecC2C(plan_second_1d_fft, transposed_data, cf32fftData_2D, CUFFT_FORWARD));

	gpuErrchk(cudaStreamAttachMemAsync(NULL, cf32fftData_2D, 0, cudaMemAttachHost));
	gpuErrchk(cudaStreamSynchronize(NULL));

	//time_end = chrono::system_clock::now();
	//cout << "Second FFT takes " << chrono::duration_cast<chrono::microseconds>(time_end - time_start).count() << " us" << endl << endl;
	total_time_end = chrono::system_clock::now();	
	cout << "2D FFT All takes " << chrono::duration_cast<chrono::microseconds>(total_time_end - total_time_start).count() << " us" << endl;

#ifdef DATA_LOG
	printf("2D FFT result..\n");
	for (int tx = 0; tx < SP_NUM_TX; tx++)
	{
		for (int rx = 0; rx < SP_NUM_RX; rx++)
		{
			for (int di = 0; di < SP_NUM_FFT_R_HALF; di++)
			{
				for (int ri = 0; ri < SP_NUM_FFT_D; ri++)
				{
					printf("[%f, %f]\n", cf32fftData_2D[SP_NUM_FFT_R_HALF*SP_NUM_FFT_D*(tx*SP_NUM_RX+rx) + di*SP_NUM_FFT_D + ri].x, \
										cf32fftData_2D[SP_NUM_FFT_R_HALF*SP_NUM_FFT_D*(tx*SP_NUM_RX+rx) + di*SP_NUM_FFT_D + ri].y);
				}
				printf("\n");
			}
		}
	}
#endif

    return 0;
}

void Init_cuda(void)
{
	size_t sizeOfs16adcData = SP_NUM_CHIRPS*SP_NUM_TX*SP_NUM_RX*SP_NUM_SAMPLES*sizeof(int16_t); // Radar raw data
	size_t sizeOfWindowed1dData = SP_NUM_CHIRPS*SP_NUM_TX*SP_NUM_RX*SP_NUM_FFT_R*sizeof(cufftComplex); // Windowed raw data	
	size_t sizeOfcf32fftData_1D = SP_NUM_CHIRPS*SP_NUM_TX*SP_NUM_RX*SP_NUM_FFT_R*sizeof(cufftComplex); // Result of first(range) FFT data
	size_t sizeOfWindowed2dData = SP_NUM_FFT_R_HALF*SP_NUM_TX*SP_NUM_RX*SP_NUM_FFT_D*sizeof(cufftComplex); // Windowed range FFT data
	size_t sizeOfTransposedData = SP_NUM_FFT_R_HALF*SP_NUM_TX*SP_NUM_RX*SP_NUM_FFT_D*sizeof(cufftComplex); // Transposed windowed range FFT data
	size_t sizeOfcf32fftData_2D = SP_NUM_FFT_R_HALF*SP_NUM_TX*SP_NUM_RX*SP_NUM_FFT_D*sizeof(cufftComplex); // Final result of second(doppler) FFT data
	gpuErrchk(cudaMallocManaged((void**)&s16adcData, sizeOfs16adcData));
	gpuErrchk(cudaMallocManaged((void**)&windowed_1d_data, sizeOfWindowed1dData));
	gpuErrchk(cudaMallocManaged((void**)&cf32fftData_1D, sizeOfcf32fftData_1D));
	gpuErrchk(cudaMallocManaged((void**)&windowed_2d_data, sizeOfWindowed2dData));
	gpuErrchk(cudaMallocManaged((void**)&transposed_data, sizeOfTransposedData));
	gpuErrchk(cudaMallocManaged((void**)&cf32fftData_2D, sizeOfcf32fftData_2D));

    size_t sizeOfcf32WinCoeff1D = SP_NUM_FFT_R*sizeof(cufftComplex); // Hamming window coefficient for raw data
    size_t sizeOff32WinCoeff2D = SP_NUM_TX*SP_NUM_RX*SP_NUM_FFT_D*sizeof(float); // Hamming window coefficient for range FFT data
    gpuErrchk(cudaMallocManaged((void**)&cf32WinCoeff1D, sizeOfcf32WinCoeff1D));
    gpuErrchk(cudaMallocManaged((void**)&f32WinCoeff2D, sizeOff32WinCoeff2D));

    cufftSafeCall(cufftPlan1d(&plan_first_1d_fft, SP_NUM_SAMPLES, CUFFT_C2C, BATCH_SIZE_F_1D));
	cufftSafeCall(cufftPlan1d(&plan_second_1d_fft, SP_NUM_FFT_D, CUFFT_C2C, BATCH_SIZE_S_1D));
	
	cublasSafeCall(cublasCreate(&cublas_handle));
}

void Gen_wincoeff(void) // SP_CAL_SAMPLE_NUM == 0xF014 case cannot be covered.
{
	int16_t idx;
	float phi;
	float temp_coef;
	float norm_factor;

	norm_factor = 1.0f / 2048.0f;
	phi = 2.0f * SP_PI / (float)(SP_NUM_FFT_R - 1);

	for (idx = 0; idx < SP_NUM_FFT_R; idx++)
	{
		/* Hamming window */
		temp_coef = 0.53836f - (0.46164f * cosf(phi * (float)idx));

		cf32WinCoeff1D[idx].x = temp_coef * norm_factor;
	}

	phi = 2.0f * SP_PI / (float)(SP_NUM_FFT_D - 1);
	for (int txrx = 0; txrx < SP_NUM_TX*SP_NUM_RX; txrx++)
	{	
		for (idx = 0; idx < SP_NUM_FFT_D; idx++)
		{
			f32WinCoeff2D[txrx*SP_NUM_FFT_D + idx] = 0.53836f - (0.46164f * cosf(phi * (float)idx));
		}
	}
}

int main(void)
{
	Init_cuda();
	Gen_wincoeff();

	while(1)
	{
		FFT_2d_cuda();
		//usleep(30000);
		usleep(50000);
	}
}
