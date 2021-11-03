#/************************************************************************
 | Project Name: AFI910
 |    File Name: reshape.cu
 |  Description: detailed Description
 |-----------------------------------------------------------------------
 |               A U T H O R   I D E N T I T Y
 |-----------------------------------------------------------------------
 | Initials     Name                      Company                        
 | --------     ---------------------     -------------------------------
 | MHKIM        Myoungha Kim              bitsensing Corporation
 |-----------------------------------------------------------------------
 |              R E V I S I O N   H I S T O R Y
 |-----------------------------------------------------------------------
 | Date         Ver  Author  Description                                 
 | ----------  ----  ------  --------------------------------------------
 | 2021.03.12  0.0   mhkim   Creation;
 |***********************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include "cublas_v2.h"
#include "cuda_runtime.h"

#include "Sp_Parameters.h"

#define NUM_RX_PER_ARRAY     4
#define NUM_RX_ARRAY         4

#define NUM_RM_RX_PER_ARRAY  4
#define NUM_RM_RX_ARRAY      4

__global__ void lms_mode_reshape(int16_t* dst, int16_t* src)
{
    __shared__ uint16_t cache[SP_NUM_SAMPLES * NUM_RX_PER_ARRAY];
    __shared__ uint16_t reshaped_cache[SP_NUM_SAMPLES * NUM_RX_PER_ARRAY];
    int ti = threadIdx.x;
    int thread_size = blockDim.x;
    int input_tile_offset = NUM_RX_PER_ARRAY * SP_NUM_SAMPLES * (blockIdx.x + gridDim.x * blockIdx.y + gridDim.x * gridDim.y * blockIdx.z);

    for(int i = 0; i < NUM_RX_PER_ARRAY; i++)
    {
        cache[i*thread_size + ti] = src[input_tile_offset + i*thread_size + ti];
    }

    __syncthreads();

    for(int i = 0; i < NUM_RX_PER_ARRAY; i++)
    {
        reshaped_cache[i*thread_size + ti] = cache[NUM_RX_PER_ARRAY * ti + i];
    }

    __syncthreads();

    for(int i = 0; i < NUM_RX_PER_ARRAY; i++)
    {
        dst[thread_size * (blockIdx.y + (gridDim.y * (3 - i)) + (gridDim.y * NUM_RX_PER_ARRAY * blockIdx.z) + (gridDim.y * NUM_RX_PER_ARRAY * gridDim.z * blockIdx.x)) + ti]\
        = reshaped_cache[i*thread_size + ti];
    }    
}

__global__ void ref_mode_reshape(int16_t* dst, int16_t* src)
{
    __shared__ uint16_t cache[SP_RM_NUM_SAMPLES * NUM_RM_RX_PER_ARRAY];
    __shared__ uint16_t reshaped_cache[SP_RM_NUM_SAMPLES * NUM_RM_RX_PER_ARRAY];
    int ti = threadIdx.x;
    int thread_size = blockDim.x;
    int input_tile_offset = NUM_RM_RX_PER_ARRAY * SP_RM_NUM_SAMPLES * (blockIdx.x + gridDim.x * blockIdx.y + gridDim.x * gridDim.y * blockIdx.z);

    for(int i = 0; i < NUM_RM_RX_PER_ARRAY; i++)
    {
        cache[i*thread_size + ti] = src[input_tile_offset + i*thread_size + ti];
    }

    __syncthreads();

    for(int i = 0; i < NUM_RM_RX_PER_ARRAY; i++)
    {
        reshaped_cache[i*thread_size + ti] = cache[NUM_RX_PER_ARRAY * ti + i];
    }

    __syncthreads();

    for(int i = 0; i < NUM_RM_RX_PER_ARRAY; i++)
    {
        dst[thread_size * (blockIdx.y + (gridDim.y * (3 - i)) + (gridDim.y * NUM_RM_RX_PER_ARRAY * blockIdx.z) + (gridDim.y * NUM_RM_RX_PER_ARRAY * gridDim.z * blockIdx.x)) + ti]\
        = reshaped_cache[i*thread_size + ti];
    }    
}

void cudamalloc_data(int16_t* daq_rm_data, int16_t* daq_lr_data, int16_t* daq_mr_data, int16_t* daq_sr_data,   \
                       int16_t* rm_reshaped_data, int16_t* lr_reshaped_data, int16_t* mr_reshaped_data, int16_t* sr_reshaped_data)
{
    cudaMallocManaged((void**)&daq_lr_data, sizeof(int16_t) * SP_NUM_SAMPLES * SP_NUM_CHIRPS * SP_NUM_TX * SP_NUM_RX);
    cudaMallocManaged((void**)&daq_mr_data, sizeof(int16_t) * SP_NUM_SAMPLES * SP_NUM_CHIRPS * SP_NUM_TX * SP_NUM_RX);
    cudaMallocManaged((void**)&daq_sr_data, sizeof(int16_t) * SP_NUM_SAMPLES * SP_NUM_CHIRPS * SP_NUM_TX * SP_NUM_RX);
    cudaMallocManaged((void**)&daq_rm_data, sizeof(int16_t) * SP_RM_NUM_SAMPLES * SP_RM_NUM_CHIRPS * SP_RM_NUM_TX * SP_NUM_RX);   
}

void reshape_raw_data(int16_t* daq_data, int16_t* daq_reshaped_rm_data, int16_t* daq_reshaped_lr_data, int16_t* daq_reshaped_mr_data, int16_t* daq_reshaped_sr_data)
{
    struct timeval startTime, endTime;
    double diffTime;

    dim3 lms_mode_dimGrid(SP_NUM_TX, SP_NUM_CHIRPS, NUM_RX_ARRAY);
    dim3 ref_mode_dimGrid(SP_RM_NUM_TX, SP_RM_NUM_CHIRPS, NUM_RM_RX_ARRAY);

    gettimeofday(&startTime, NULL);

    ref_mode_reshape<<<ref_mode_dimGrid, SP_RM_NUM_SAMPLES>>>(daq_reshaped_rm_data, \
                                                                daq_data);
    lms_mode_reshape<<<lms_mode_dimGrid, SP_NUM_SAMPLES>>>(daq_reshaped_lr_data, \
                                                                daq_data + SP_RM_NUM_SAMPLES * SP_RM_NUM_CHIRPS * SP_RM_NUM_TX * SP_NUM_RX);
    lms_mode_reshape<<<lms_mode_dimGrid, SP_NUM_SAMPLES>>>(daq_reshaped_mr_data, \
                                                                daq_data + SP_RM_NUM_SAMPLES * SP_RM_NUM_CHIRPS * SP_RM_NUM_TX * SP_NUM_RX + SP_NUM_SAMPLES * SP_NUM_CHIRPS * SP_NUM_TX * SP_NUM_RX);
    lms_mode_reshape<<<lms_mode_dimGrid, SP_NUM_SAMPLES>>>(daq_reshaped_sr_data, \
                                                                daq_data + SP_RM_NUM_SAMPLES * SP_RM_NUM_CHIRPS * SP_RM_NUM_TX * SP_NUM_RX + SP_NUM_SAMPLES * SP_NUM_CHIRPS * SP_NUM_TX * SP_NUM_RX * 2);

    cudaStreamAttachMemAsync(NULL, daq_reshaped_rm_data, 0, cudaMemAttachHost);
    cudaStreamAttachMemAsync(NULL, daq_reshaped_lr_data, 0, cudaMemAttachHost);
    cudaStreamAttachMemAsync(NULL, daq_reshaped_mr_data, 0, cudaMemAttachHost);
    cudaStreamAttachMemAsync(NULL, daq_reshaped_sr_data, 0, cudaMemAttachHost);

    /*
    ref_mode_reshape<<<ref_mode_dimGrid, SP_RM_NUM_SAMPLES>>>(rm_reshaped_data, daq_rm_data);
    lms_mode_reshape<<<lms_mode_dimGrid, SP_NUM_SAMPLES>>>(lr_reshaped_data, daq_lr_data);
    lms_mode_reshape<<<lms_mode_dimGrid, SP_NUM_SAMPLES>>>(mr_reshaped_data, daq_mr_data);
    lms_mode_reshape<<<lms_mode_dimGrid, SP_NUM_SAMPLES>>>(sr_reshaped_data, daq_sr_data);
    
    cudaStreamAttachMemAsync(NULL, rm_reshaped_data, 0, cudaMemAttachGlobal);
    cudaStreamAttachMemAsync(NULL, lr_reshaped_data, 0, cudaMemAttachGlobal);
    cudaStreamAttachMemAsync(NULL, mr_reshaped_data, 0, cudaMemAttachGlobal);
    cudaStreamAttachMemAsync(NULL, sr_reshaped_data, 0, cudaMemAttachGlobal);
*/
	cudaStreamSynchronize(NULL);

    gettimeofday(&endTime, NULL);
    diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
    //printf("gpu 5D reshape(): %lf s\n", diffTime);     
}

/*
int main(void)
{
    struct timeval startTime, endTime;
    double diffTime;

    uint16_t* lr_input_data;
    uint16_t* mr_input_data;
    uint16_t* sr_input_data;
    uint16_t* rm_input_data;
    cudaMallocManaged((void**)&lr_input_data, sizeof(uint16_t) * NUM_RX_PER_ARRAY * NUM_SAMPLES * NUM_TX * NUM_CHIRPS * NUM_RX_ARRAY);
    cudaMallocManaged((void**)&mr_input_data, sizeof(uint16_t) * NUM_RX_PER_ARRAY * NUM_SAMPLES * NUM_TX * NUM_CHIRPS * NUM_RX_ARRAY);
    cudaMallocManaged((void**)&sr_input_data, sizeof(uint16_t) * NUM_RX_PER_ARRAY * NUM_SAMPLES * NUM_TX * NUM_CHIRPS * NUM_RX_ARRAY);
    cudaMallocManaged((void**)&rm_input_data, sizeof(uint16_t) * NUM_RM_RX_PER_ARRAY * NUM_RM_SAMPLES * NUM_RM_TX * NUM_RM_CHIRPS * NUM_RM_RX_ARRAY);

    uint16_t* lr_cpu_reshaped_data = (uint16_t*)malloc(sizeof(uint16_t) * NUM_RX_PER_ARRAY * NUM_SAMPLES * NUM_TX * NUM_CHIRPS * NUM_RX_ARRAY);
    uint16_t* mr_cpu_reshaped_data = (uint16_t*)malloc(sizeof(uint16_t) * NUM_RX_PER_ARRAY * NUM_SAMPLES * NUM_TX * NUM_CHIRPS * NUM_RX_ARRAY);
    uint16_t* sr_cpu_reshaped_data = (uint16_t*)malloc(sizeof(uint16_t) * NUM_RX_PER_ARRAY * NUM_SAMPLES * NUM_TX * NUM_CHIRPS * NUM_RX_ARRAY);
    uint16_t* rm_cpu_reshaped_data = (uint16_t*)malloc(sizeof(uint16_t) * NUM_RM_RX_PER_ARRAY * NUM_RM_SAMPLES * NUM_RM_TX * NUM_RM_CHIRPS * NUM_RM_RX_ARRAY);
    
    uint16_t* lr_gpu_reshaped_data;
    uint16_t* mr_gpu_reshaped_data;
    uint16_t* sr_gpu_reshaped_data;
    uint16_t* rm_gpu_reshaped_data;
    cudaMallocManaged((void**)&lr_gpu_reshaped_data, sizeof(uint16_t) * NUM_RX_PER_ARRAY * NUM_SAMPLES * NUM_TX * NUM_CHIRPS * NUM_RX_ARRAY);
    cudaMallocManaged((void**)&mr_gpu_reshaped_data, sizeof(uint16_t) * NUM_RX_PER_ARRAY * NUM_SAMPLES * NUM_TX * NUM_CHIRPS * NUM_RX_ARRAY);
    cudaMallocManaged((void**)&sr_gpu_reshaped_data, sizeof(uint16_t) * NUM_RX_PER_ARRAY * NUM_SAMPLES * NUM_TX * NUM_CHIRPS * NUM_RX_ARRAY);
    cudaMallocManaged((void**)&rm_gpu_reshaped_data, sizeof(uint16_t) * NUM_RM_RX_PER_ARRAY * NUM_RM_SAMPLES * NUM_RM_TX * NUM_RM_CHIRPS * NUM_RM_RX_ARRAY);

    // 초기화
    srand(time(NULL));
    for(int i = 0; i < NUM_RX_ARRAY; i++)
    {
        for(int j = 0; j < NUM_CHIRPS; j++)
        {
            for(int k = 0; k < NUM_TX; k++)
            {
                for(int m = 0; m < NUM_SAMPLES; m++)
                {
                    for(int n = 0; n < NUM_RX_PER_ARRAY; n++)
                    {
                        lr_input_data[i * NUM_CHIRPS * NUM_TX * NUM_SAMPLES * NUM_RX_PER_ARRAY + j * NUM_TX * NUM_SAMPLES * NUM_RX_PER_ARRAY +    \
                                        k * NUM_SAMPLES * NUM_RX_PER_ARRAY + m * NUM_RX_PER_ARRAY + n] = rand() % 100;
                        mr_input_data[i * NUM_CHIRPS * NUM_TX * NUM_SAMPLES * NUM_RX_PER_ARRAY + j * NUM_TX * NUM_SAMPLES * NUM_RX_PER_ARRAY +    \
                                        k * NUM_SAMPLES * NUM_RX_PER_ARRAY + m * NUM_RX_PER_ARRAY + n] = rand() % 100;
                        sr_input_data[i * NUM_CHIRPS * NUM_TX * NUM_SAMPLES * NUM_RX_PER_ARRAY + j * NUM_TX * NUM_SAMPLES * NUM_RX_PER_ARRAY +    \
                                        k * NUM_SAMPLES * NUM_RX_PER_ARRAY + m * NUM_RX_PER_ARRAY + n] = rand() % 100;
                    }
                }
            }
        }
    }

    for(int i = 0; i < NUM_RM_RX_ARRAY; i++)
    {
        for(int j = 0; j < NUM_RM_CHIRPS; j++)
        {
            for(int k = 0; k < NUM_RM_TX; k++)
            {
                for(int m = 0; m < NUM_RM_SAMPLES; m++)
                {
                    for(int n = 0; n < NUM_RM_RX_PER_ARRAY; n++)
                    {
                        rm_input_data[i * NUM_RM_CHIRPS * NUM_RM_TX * NUM_RM_SAMPLES * NUM_RM_RX_PER_ARRAY + j * NUM_RM_TX * NUM_RM_SAMPLES * NUM_RM_RX_PER_ARRAY +    \
                                        k * NUM_RM_SAMPLES * NUM_RM_RX_PER_ARRAY + m * NUM_RM_RX_PER_ARRAY + n] = rand() % 100;
                    }
                }
            }
        }
    }

    gettimeofday(&startTime, NULL);

    for(int i = 0; i < NUM_RX_ARRAY; i++)
    {
        for(int j = 0; j < NUM_CHIRPS; j++)
        {
            for(int k = 0; k < NUM_TX; k++)
            {
                for(int m = 0; m < NUM_SAMPLES; m++)
                {
                    for(int n = 0; n < NUM_RX_PER_ARRAY; n++)
                    {
                        lr_cpu_reshaped_data[k * NUM_RX_ARRAY * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + i * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + n * NUM_CHIRPS * NUM_SAMPLES + j * NUM_SAMPLES + m]
                        = lr_input_data[i * NUM_CHIRPS * NUM_TX * NUM_SAMPLES * NUM_RX_PER_ARRAY + j * NUM_TX * NUM_SAMPLES * NUM_RX_PER_ARRAY + k * NUM_SAMPLES * NUM_RX_PER_ARRAY + m * NUM_RX_PER_ARRAY + n];
                        mr_cpu_reshaped_data[k * NUM_RX_ARRAY * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + i * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + n * NUM_CHIRPS * NUM_SAMPLES + j * NUM_SAMPLES + m]
                        = mr_input_data[i * NUM_CHIRPS * NUM_TX * NUM_SAMPLES * NUM_RX_PER_ARRAY + j * NUM_TX * NUM_SAMPLES * NUM_RX_PER_ARRAY + k * NUM_SAMPLES * NUM_RX_PER_ARRAY + m * NUM_RX_PER_ARRAY + n];
                        sr_cpu_reshaped_data[k * NUM_RX_ARRAY * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + i * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + n * NUM_CHIRPS * NUM_SAMPLES + j * NUM_SAMPLES + m]
                        = sr_input_data[i * NUM_CHIRPS * NUM_TX * NUM_SAMPLES * NUM_RX_PER_ARRAY + j * NUM_TX * NUM_SAMPLES * NUM_RX_PER_ARRAY + k * NUM_SAMPLES * NUM_RX_PER_ARRAY + m * NUM_RX_PER_ARRAY + n];
                    }
                }
            }
        }
    }

    for(int i = 0; i < NUM_RM_RX_ARRAY; i++)
    {
        for(int j = 0; j < NUM_RM_CHIRPS; j++)
        {
            for(int k = 0; k < NUM_RM_TX; k++)
            {
                for(int m = 0; m < NUM_RM_SAMPLES; m++)
                {
                    for(int n = 0; n < NUM_RM_RX_PER_ARRAY; n++)
                    {
                        rm_cpu_reshaped_data[k * NUM_RM_RX_ARRAY * NUM_RM_RX_PER_ARRAY * NUM_RM_CHIRPS * NUM_RM_SAMPLES + i * NUM_RM_RX_PER_ARRAY * NUM_RM_CHIRPS * NUM_RM_SAMPLES + n * NUM_RM_CHIRPS * NUM_RM_SAMPLES + j * NUM_RM_SAMPLES + m]
                        = rm_input_data[i * NUM_RM_CHIRPS * NUM_RM_TX * NUM_RM_SAMPLES * NUM_RM_RX_PER_ARRAY + j * NUM_RM_TX * NUM_RM_SAMPLES * NUM_RM_RX_PER_ARRAY + k * NUM_RM_SAMPLES * NUM_RM_RX_PER_ARRAY + m * NUM_RM_RX_PER_ARRAY + n];
                    }
                }
            }
        }
    }

    gettimeofday(&endTime, NULL);
    diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
    printf("cpu 5D reshape(): %lf s\n", diffTime);

    dim3 lms_mode_dimGrid(NUM_TX, NUM_CHIRPS, NUM_RX_ARRAY);
    dim3 ref_mode_dimGrid(NUM_RM_TX, NUM_RM_CHIRPS, NUM_RM_RX_ARRAY);

    gettimeofday(&startTime, NULL);

    lms_mode_reshape<<<lms_mode_dimGrid, NUM_SAMPLES>>>(lr_gpu_reshaped_data, lr_input_data);
    lms_mode_reshape<<<lms_mode_dimGrid, NUM_SAMPLES>>>(mr_gpu_reshaped_data, mr_input_data);
    lms_mode_reshape<<<lms_mode_dimGrid, NUM_SAMPLES>>>(sr_gpu_reshaped_data, sr_input_data);
    ref_mode_reshape<<<ref_mode_dimGrid, NUM_RM_SAMPLES>>>(rm_gpu_reshaped_data, rm_input_data);
    
    cudaStreamAttachMemAsync(NULL, lr_gpu_reshaped_data, 0, cudaMemAttachGlobal);
    cudaStreamAttachMemAsync(NULL, mr_gpu_reshaped_data, 0, cudaMemAttachGlobal);
    cudaStreamAttachMemAsync(NULL, sr_gpu_reshaped_data, 0, cudaMemAttachGlobal);
    cudaStreamAttachMemAsync(NULL, rm_gpu_reshaped_data, 0, cudaMemAttachGlobal);
	cudaStreamSynchronize(NULL);

    gettimeofday(&endTime, NULL);
    diffTime = endTime.tv_sec + endTime.tv_usec / 1000000.0 - startTime.tv_sec - startTime.tv_usec / 1000000.0;
    printf("gpu 5D reshape(): %lf s\n", diffTime);

    for(int k = 0; k < NUM_TX; k++)
    {
        for(int i = 0; i < NUM_RX_ARRAY; i++)
        {
            for(int n = 0; n < NUM_RX_PER_ARRAY; n++)
            {
                for(int j = 0; j < NUM_CHIRPS; j++)
                {
                    for(int m = 0; m < NUM_SAMPLES; m++)
                    {
                        if(lr_cpu_reshaped_data[k * NUM_RX_ARRAY * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + i * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + n * NUM_CHIRPS * NUM_SAMPLES + j * NUM_SAMPLES + m]\
                             != lr_gpu_reshaped_data[k * NUM_RX_ARRAY * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + i * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + n * NUM_CHIRPS * NUM_SAMPLES + j * NUM_SAMPLES + m] ||
                            mr_cpu_reshaped_data[k * NUM_RX_ARRAY * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + i * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + n * NUM_CHIRPS * NUM_SAMPLES + j * NUM_SAMPLES + m]\
                             != mr_gpu_reshaped_data[k * NUM_RX_ARRAY * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + i * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + n * NUM_CHIRPS * NUM_SAMPLES + j * NUM_SAMPLES + m] ||
                            sr_cpu_reshaped_data[k * NUM_RX_ARRAY * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + i * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + n * NUM_CHIRPS * NUM_SAMPLES + j * NUM_SAMPLES + m]\
                             != sr_gpu_reshaped_data[k * NUM_RX_ARRAY * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + i * NUM_RX_PER_ARRAY * NUM_CHIRPS * NUM_SAMPLES + n * NUM_CHIRPS * NUM_SAMPLES + j * NUM_SAMPLES + m])
                        {
                            //printf("gpu reshape failed.. [%d][%d][%d][%d][%d] cpu data: %d, gpu data: %d\n", k, i, n, j, m,
                            printf("lms_mode gpu reshape failed.. \n");
                            goto EXIT;
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < NUM_RM_RX_ARRAY; i++)
    {
        for(int j = 0; j < NUM_RM_CHIRPS; j++)
        {
            for(int k = 0; k < NUM_RM_TX; k++)
            {
                for(int m = 0; m < NUM_RM_SAMPLES; m++)
                {
                    for(int n = 0; n < NUM_RM_RX_PER_ARRAY; n++)
                    {
                        if(rm_cpu_reshaped_data[k * NUM_RM_RX_ARRAY * NUM_RM_RX_PER_ARRAY * NUM_RM_CHIRPS * NUM_RM_SAMPLES + i * NUM_RM_RX_PER_ARRAY * NUM_RM_CHIRPS * NUM_RM_SAMPLES + n * NUM_RM_CHIRPS * NUM_RM_SAMPLES + j * NUM_RM_SAMPLES + m]\
                            != rm_gpu_reshaped_data[k * NUM_RM_RX_ARRAY * NUM_RM_RX_PER_ARRAY * NUM_RM_CHIRPS * NUM_RM_SAMPLES + i * NUM_RM_RX_PER_ARRAY * NUM_RM_CHIRPS * NUM_RM_SAMPLES + n * NUM_RM_CHIRPS * NUM_RM_SAMPLES + j * NUM_RM_SAMPLES + m])
                        {
                           //printf("gpu reshape failed.. [%d][%d][%d][%d][%d] cpu data: %d, gpu data: %d\n", k, i, n, j, m,
                           printf("ref_mode gpu reshape failed.. \n");
                           goto EXIT;
                        }
                    }
                }
            }
        }
    }

EXIT:

    cudaFree(lr_input_data);
    cudaFree(mr_input_data);
    cudaFree(sr_input_data);
    cudaFree(rm_input_data);
    free(lr_cpu_reshaped_data);
    free(mr_cpu_reshaped_data);
    free(sr_cpu_reshaped_data);
    free(rm_cpu_reshaped_data);
    cudaFree(lr_gpu_reshaped_data);
    cudaFree(mr_gpu_reshaped_data);
    cudaFree(sr_gpu_reshaped_data);
    cudaFree(rm_gpu_reshaped_data);
}*/