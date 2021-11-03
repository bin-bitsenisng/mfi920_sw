/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "bts_cfarlib.h"

/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/
#if WIN32
#define CFAR_TH_ENABLE		0
#else
#define CFAR_TH_ENABLE		0
#endif

/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
static float32_t cfarlib_f32threshold(float32_t* input, int16_t index, uint8_t refCells, uint8_t extsCells, uint8_t guardCells, float32_t normFactor);

/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void cfarlib_vCA_cfar_range(float32_t* cfarIn, uint8_t* cfarOut, CfarCfg_t* cfg, float32_t* accumSum, uint16_t acnt, float32_t* cfarTh, uint16_t offset)
{
	uint16_t i, j;

	float32_t sum_left, sum_right, threshold;

	// front part accum sum	
	accumSum[0] = 0.f; // for safety
	for (i = 1; i < cfg->u8ExtsSize + 1; i++)
	{
		accumSum[i] = accumSum[i - 1] + cfarIn[(cfg->u8ExtsSize + 1 - i) * acnt];
	}

	// forward direction accum sum
	for (i = cfg->u8ExtsSize + 1, j = 0; i < cfg->u8ExtsSize + cfg->u16NumCells; i++, j++)
	{
		accumSum[i] = accumSum[i - 1] + cfarIn[(j)*acnt];
	}

	// end part accum sum
	for (i = cfg->u8ExtsSize + cfg->u16NumCells, j = 0; i < 2 * cfg->u8ExtsSize + cfg->u16NumCells + 1; i++, j++)
	{
		accumSum[i] = accumSum[i - 1] + cfarIn[(cfg->u16NumCells - 1 - j) * acnt];
	}

	// threshold calc.
	for (i = 0; i < cfg->u16NumCells; i++)
	{
		if ((i != 0) && (i != (cfg->u16NumCells - 1)))
		{
			if ((cfarIn[i * acnt] > cfg->f32BaseTh)
				&& ((cfarIn[i * acnt] > cfarIn[(i - 1) * acnt]) && (cfarIn[i * acnt] > cfarIn[(i + 1) * acnt])))
			{
				threshold = cfarlib_f32threshold(accumSum, i, cfg->u8RefCells, cfg->u8ExtsSize, cfg->u8GuardCells, cfg->f32Alpha);
				cfarOut[offset + i] = (uint8_t)(cfarIn[i * acnt] > threshold);
				cfarTh[i] = threshold;
			}
			else
			{
				cfarOut[offset + i] = (uint8_t)0;
				cfarTh[i] = 0.f;
			}
		}
		else if (i == 0)
		{
			if ((cfarIn[0] > cfg->f32BaseTh) && (cfarIn[0] > cfarIn[acnt]))
			{
				threshold = cfarlib_f32threshold(accumSum, i, cfg->u8RefCells, cfg->u8ExtsSize, cfg->u8GuardCells, cfg->f32Alpha);
				cfarOut[offset] = (uint8_t)(cfarIn[0] > threshold);
				cfarTh[0] = threshold;
			}
			else
			{
				cfarOut[offset] = (uint8_t)0;
				cfarTh[0] = 0.f;
			}
		}
		else if (i == (cfg->u16NumCells - 1))
		{
			if ((cfarIn[i * acnt] > cfg->f32BaseTh) && ((cfarIn[i * acnt] > cfarIn[(i - 1) * acnt])))
			{
				threshold = cfarlib_f32threshold(accumSum, i, cfg->u8RefCells, cfg->u8ExtsSize, cfg->u8GuardCells, cfg->f32Alpha);
				cfarOut[offset + i] = (uint8_t)(cfarIn[i * acnt] > threshold);
				cfarTh[i] = threshold;
			}
			else
			{
				cfarOut[offset + i] = (uint8_t)0;
				cfarTh[i] = 0.f;
			}
		}
	}
}

void cfarlib_vCA_cfar_doppler(float32_t* cfarIn, uint8_t* cfarOut, CfarCfg_t* cfg, float32_t* accumSum, uint16_t acnt, float32_t* cfarTh, uint16_t offset, float32_t ri_norm)
{
	uint16_t i, j;
	uint16_t num_grd = (uint16_t)cfg->u8GuardCells;
	uint16_t num_ref = (uint16_t)cfg->u8RefCells;

	float32_t sum_left, sum_right, threshold;
	float32_t base_weight_th;
	
	float32_t alpha = 0.0f;
	float32_t base_th = 0.0f;;

	if ( (ri_norm > 0.50f) && (ri_norm <= 0.60f))
	{
		alpha = (0.85f)*(cfg->f32Alpha);
		base_th = (0.95f)*(cfg->f32BaseTh);
	}
	else if ((ri_norm > 0.60f) && (ri_norm <= 0.70f))
	{
		alpha = (0.80f)*(cfg->f32Alpha);
		base_th = (0.90f)*(cfg->f32BaseTh);
	}
	else if ((ri_norm > 0.70f) && (ri_norm <= 0.90f))
	{
		alpha = (0.70f)*(cfg->f32Alpha);
		base_th = (0.85f)*(cfg->f32BaseTh);
	}
	else if ((ri_norm > 0.90f) && (ri_norm <= 1.00f))
	{
		alpha = (0.60f)*(cfg->f32Alpha);
		base_th = (0.80f)*(cfg->f32BaseTh);
	}
	else
	{
		alpha = cfg->f32Alpha;
		base_th = cfg->f32BaseTh;
	}
	

	// front part accum sum	
	accumSum[0] = 0.f;
	for (i = 1; i < cfg->u8ExtsSize + 1; i++)
	{
		accumSum[i] = accumSum[i - 1] + cfarIn[acnt - (cfg->u8ExtsSize) - 1 + i];
	}

	// forward direction accum sum
	for (i = cfg->u8ExtsSize + 1, j = 0; i < cfg->u8ExtsSize + cfg->u16NumCells + 1; i++, j++)
	{
		accumSum[i] = accumSum[i - 1] + cfarIn[j];
	}

	// end part accum sum
	for (i = cfg->u8ExtsSize + cfg->u16NumCells + 1, j = 0; i < 2 * cfg->u8ExtsSize + cfg->u16NumCells + 1; i++, j++)
	{
		accumSum[i] = accumSum[i - 1] + cfarIn[j];
	}

	// threshold calc.
	for (i = 0; i < cfg->u16NumCells; i++)
	{
		if ((i != 0) && (i != (cfg->u16NumCells - 1)))
		{
			if ((cfarIn[i] > base_th)
				&& ((cfarIn[i] > cfarIn[(i - 1)]) && (cfarIn[i] > cfarIn[(i + 1)])))
			{
				threshold = cfarlib_f32threshold(accumSum, i, cfg->u8RefCells, cfg->u8ExtsSize, cfg->u8GuardCells, alpha);
				cfarOut[i] = (uint8_t)(cfarIn[i] > threshold);
				cfarTh[i] = threshold;
			}
			else
			{
				cfarOut[i] = (uint8_t)0;
				cfarTh[i] = 0.f;
			}
		}
		else if (i == 0)
		{
			base_weight_th = 1.20f * cfg->f32BaseTh;
			if ((cfarIn[0] > base_weight_th)
				&& ((cfarIn[0] > cfarIn[cfg->u16NumCells - 1]) && (cfarIn[0] > cfarIn[1])))
			{

				threshold = cfarlib_f32threshold(accumSum, i, cfg->u8RefCells, cfg->u8ExtsSize, cfg->u8GuardCells, alpha);
				cfarOut[0] = (uint8_t)(cfarIn[0] > threshold);
				cfarTh[0] = threshold;
			}
			else
			{
				cfarOut[0] = (uint8_t)0;
				cfarTh[0] = 0.f;
			}
		}
		else if (i == (cfg->u16NumCells - 1))
		{
			if ((cfarIn[i] > base_th)
				&& ((cfarIn[cfg->u16NumCells - 1] > cfarIn[cfg->u16NumCells - 2]) && (cfarIn[cfg->u16NumCells - 1] > cfarIn[0])))
			{
				threshold = cfarlib_f32threshold(accumSum, i, cfg->u8RefCells, cfg->u8ExtsSize, cfg->u8GuardCells, alpha);
				cfarOut[i] = (uint8_t)(cfarIn[i] > threshold);
				cfarTh[i] = threshold;
			}
			else
			{
				cfarOut[i] = (uint8_t)0;
				cfarTh[i] = 0.f;
			}
		}
	}
}




void cfarlib_vOS_cfar_doppler(float32_t* cfarIn, uint8_t* cfarOut, CfarCfg_t* cfg, float32_t* cfarTh)
{
	uint16_t i, j;
	
	float32_t threshold;
	float32_t base_weight_th;
	float32_t alpha = 0.0f;
	float32_t est_val = 0.0f;

	uint8_t temp_array_len = (uint8_t)cfg->u16NumCells;
	uint8_t temp_order = cfg->u8KthOrder;
	float32_t input_array[CFARLIB_CFARCELL_MAX] = { 0 };
	float32_t temp_array;

	for (i = 0; i < temp_array_len; i++)
	{
		input_array[i] = cfarIn[i];
	}


	/* Sorting */
	for (int16_t ii = 0; ii < temp_array_len; ++ii)
	{
		for (int16_t j = ii + 1; j < temp_array_len; ++j)
		{

			if (input_array[ii] < input_array[j])
			{
				temp_array = input_array[ii];
				input_array[ii] = input_array[j];
				input_array[j] = temp_array;
			}
		}
	}

	est_val = input_array[temp_order];
	threshold = (est_val * cfg->f32Alpha);
	
	// threshold calc.
	for (i = 0; i < cfg->u16NumCells; i++)
	{
		if ((i != 0) && (i != (cfg->u16NumCells - 1)))
		{
			if ((cfarIn[i] > cfg->f32BaseTh)
				&& ((cfarIn[i] > cfarIn[(i - 1)]) && (cfarIn[i] > cfarIn[(i + 1)])))
			{
				cfarOut[i] = (uint8_t)(cfarIn[i] > threshold);
				cfarTh[i] = threshold;
			}
			else
			{
				cfarOut[i] = (uint8_t)0;
				cfarTh[i] = 0.f;
			}
		}
		else if (i == 0)
		{
			base_weight_th = 1.20f * cfg->f32BaseTh;
			if ((cfarIn[0] > base_weight_th)
				&& ((cfarIn[0] > cfarIn[cfg->u16NumCells - 1]) && (cfarIn[0] > cfarIn[1])))
			{
				cfarOut[0] = (uint8_t)(cfarIn[0] > threshold);
				cfarTh[0] = threshold;
			}
			else
			{
				cfarOut[0] = (uint8_t)0;
				cfarTh[0] = 0.f;
			}
		}
		else if (i == (cfg->u16NumCells - 1))
		{
			if ((cfarIn[i] > cfg->f32BaseTh)
				&& ((cfarIn[cfg->u16NumCells - 1] > cfarIn[cfg->u16NumCells - 2]) && (cfarIn[cfg->u16NumCells - 1] > cfarIn[0])))
			{
				cfarOut[i] = (uint8_t)(cfarIn[i] > threshold);
				cfarTh[i] = threshold;
			}
			else
			{
				cfarOut[i] = (uint8_t)0;
				cfarTh[i] = 0.f;
			}
		}
	}
}

static float32_t cfarlib_f32threshold(float32_t* input, int16_t index, uint8_t refCells, uint8_t extsCells, uint8_t guardCells, float32_t normFactor)
{
	float32_t sum_left, sum_right, threshold;
	sum_left = input[refCells + index] - input[index];
	sum_right = input[refCells + extsCells + guardCells + 1 + index] - input[extsCells + guardCells + 1 + index];
	threshold = (sum_left + sum_right) * normFactor;
	return threshold;
}



static float32_t cfarlib_f32Sort(float32_t* input, uint8_t len)
{
	uint8_t i, j, k;
	uint8_t temp_order = 30;
	uint8_t ref_cell_idx = 0;
	uint8_t temp_array_len = len;
	float32_t input_array[CFARLIB_CFARCELL_MAX] = { 0 };
	float32_t temp_array;

	/*
	for (i = 0; i < temp_array_len; i++)
	{
		printf("i : %d, %f\n", i, input[i]);
	}
	*/

	for (i = 0; i < temp_array_len; i++)
	{
		input_array[i] = input[i];
	}

	for (int16_t ii = 0; ii < temp_array_len; ++ii)
	{
		for (int16_t j = ii + 1; j < temp_array_len; ++j)
		{

			if (input_array[ii] < input_array[j])
			{
				temp_array = input_array[ii];
				input_array[ii] = input_array[j];
				input_array[j] = temp_array;

			}
		}
	}



	/*
	for (i = 0; i < temp_array_len; i++)
	{
		printf("i : %d, %f\n", i, input_array[i]);
	}
	*/

	float32_t  a = 3.0f;
	//return input_array[temp_order];
	return a;
}