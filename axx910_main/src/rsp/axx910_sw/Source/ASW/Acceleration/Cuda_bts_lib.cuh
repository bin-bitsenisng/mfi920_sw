#ifndef _CUDA_BTS_LIB_CUH_
#define _CUDA_BTS_LIB_CUH_
#ifdef __cplusplus
extern "C" {
#endif

#ifdef CUDA_ACC

#include "Obj_Main.h"
#include "Pre_Main.h"


	/**************************************************************************************
	----------------------------------   Data Struct   ------------------------------------
	**************************************************************************************/


	/**************************************************************************************
	-------------------------------------   define   --------------------------------------
	**************************************************************************************/
#define RM_BATCH_SIZE_F_1D		SP_RM_NUM_CHIRPS * SP_RM_NUM_TX * SP_NUM_RX
#define RM_BATCH_SIZE_S_1D		SP_RM_NUM_FFT_R_HALF * SP_RM_NUM_TX * SP_NUM_RX

#define BATCH_SIZE_F_1D		SP_NUM_CHIRPS * SP_NUM_TX * SP_NUM_RX
#define BATCH_SIZE_S_1D		SP_NUM_FFT_R_HALF * SP_NUM_TX * SP_NUM_RX

	/**************************************************************************************
	-------------------------------   function prototypes   -------------------------------
	**************************************************************************************/

	int fft_2d_cuda(void);

	void Init_cuda(void);
	void Obj_vNCI_cuda(uint32_t num_tx, uint32_t num_rx, uint32_t num_fft_r_half, uint32_t num_fft_d, uint32_t nci_range_init_idx, Cuda_PreData_t* PreData, Cuda_BeamData_t* BeamData);

	/**************************************************************************************
	--------------------------------   global variables   ---------------------------------
	**************************************************************************************/

#endif

#ifdef __cplusplus
}
#endif

#endif