#ifndef _OBJ_PARAMETERS_H_
#define _OBJ_PARAMETERS_H_


/**************************************************************************************
-------------------------------------   define   --------------------------------------
**************************************************************************************/
/* Data Length */
#define OBJ_NUM_TX															SP_NUM_TX																/*		12		*/	
#define OBJ_NUM_RX															SP_NUM_RX																/*		16		*/	
#define OBJ_RM_NUM_TX														SP_RM_NUM_TX														/*		1		*/	

#define OBJ_NUM_FFT_R														SP_NUM_FFT_R_HALF													/*		512	*/
#define OBJ_NUM_FFT_D														SP_NUM_FFT_D															/*		32		*/		

#define OBJ_RM_NUM_FFT_R													SP_RM_NUM_FFT_R_HALF											/*		256	*/
#define OBJ_RM_NUM_FFT_D													SP_RM_NUM_FFT_D													/*		512	*/

#define  OBJ_MAX_NUM_FFT_R												_sp_max(OBJ_NUM_FFT_R, OBJ_RM_NUM_FFT_R)	
#define  OBJ_MAX_NUM_FFT_D												_sp_max(OBJ_NUM_FFT_D, OBJ_RM_NUM_FFT_D)

/* Peak Data */
#define OBJ_NUM_RM_PEAK_MAX											512
#define OBJ_NUM_LR_PEAK_MAX												512
#define OBJ_NUM_MR_PEAK_MAX											512
#define OBJ_NUM_SR_PEAK_MAX												512
#define OBJ_NUM_PEAK_MAX													_sp_max(_sp_max(OBJ_NUM_LR_PEAK_MAX, OBJ_NUM_MR_PEAK_MAX), OBJ_NUM_SR_PEAK_MAX)


#define OBJ_NUM_HARM_MAX												48

#define OBJ_NUM_PEAK_HARM_LR											(OBJ_NUM_LR_PEAK_MAX +OBJ_NUM_HARM_MAX)									
#define OBJ_NUM_PEAK_HARM_MR											(OBJ_NUM_MR_PEAK_MAX + OBJ_NUM_HARM_MAX)
#define OBJ_NUM_PEAK_HARM_SR											(OBJ_NUM_SR_PEAK_MAX  +OBJ_NUM_HARM_MAX)


#define OBJ_NUM_PEAK_HARM_MAX										(OBJ_NUM_PEAK_MAX + OBJ_NUM_HARM_MAX)

/* NCI */
#define OBJ_NCI_RANGE_INIT_IDX_RM										1
#define OBJ_NCI_RANGE_INIT_IDX											3

/* CFAR */
/* RM */
#define OBJ_CFAR_RM_NUM_GUARD_CELL_R								2
#define OBJ_CFAR_RM_NUM_REF_CELL_HALF_R							8
#define OBJ_CFAR_RM_NUM_EXTEN_CELL_R								(OBJ_CFAR_RM_NUM_GUARD_CELL_R + OBJ_CFAR_RM_NUM_REF_CELL_HALF_R)
#define OBJ_CFAR_RM_OSCFAR_KTH_ORDER_R							8
#define OBJ_CFAR_RM_THRESHOLD_ALPHA_R								2.5f
#define OBJ_CFAR_RM_BASE_THRESHOLD_R								150.0f	  ///30.0f //8000.0f

#define OBJ_CFAR_RM_NUM_GUARD_CELL_D								4
#define OBJ_CFAR_RM_NUM_REF_CELL_HALF_D							16
#define OBJ_CFAR_RM_NUM_EXTEN_CELL_D								(OBJ_CFAR_RM_NUM_GUARD_CELL_D + OBJ_CFAR_RM_NUM_REF_CELL_HALF_D)
#define OBJ_CFAR_RM_THRESHOLD_ALPHA_D								2.5f
#define OBJ_CFAR_RM_BASE_THRESHOLD_D								25.0f		//30.0f  //12000.0f

#define OBJ_CFAR_RM_R_IDX_MIN											1
#define OBJ_CFAR_RM_R_IDX_MAX											255


/* LR */
#define OBJ_CFAR_LR_NUM_GUARD_CELL_R								2
#define OBJ_CFAR_LR_NUM_REF_CELL_HALF_R								16
#define OBJ_CFAR_LR_NUM_EXTEN_CELL_R									(OBJ_CFAR_LR_NUM_GUARD_CELL_R + OBJ_CFAR_LR_NUM_REF_CELL_HALF_R)
#define OBJ_CFAR_LR_OSCFAR_KTH_ORDER_R								16
#define OBJ_CFAR_LR_THRESHOLD_ALPHA_R								1.5f
#define OBJ_CFAR_LR_BASE_THRESHOLD_R									500.0f //30.0f  //8000.0f

#define OBJ_CFAR_LR_NUM_GUARD_CELL_D								2
#define OBJ_CFAR_LR_NUM_REF_CELL_HALF_D							8
#define OBJ_CFAR_LR_NUM_EXTEN_CELL_D									OBJ_CFAR_LR_NUM_GUARD_CELL_D		// (OBJ_CFAR_LR_NUM_GUARD_CELL_D + OBJ_CFAR_LR_NUM_REF_CELL_HALF_D)
#define OBJ_CFAR_LR_OSCFAR_KTH_ORDER_D								28
#define OBJ_CFAR_LR_THRESHOLD_ALPHA_D								1.50f
#define OBJ_CFAR_LR_BASE_THRESHOLD_D								23.0f	//30.0f  //12000.0f

#define OBJ_CFAR_LR_R_IDX_MIN												40
#define OBJ_CFAR_LR_R_IDX_MAX											500

/* MR */
#define OBJ_CFAR_MR_NUM_GUARD_CELL_R								2
#define OBJ_CFAR_MR_NUM_REF_CELL_HALF_R							8
#define OBJ_CFAR_MR_NUM_EXTEN_CELL_R								(OBJ_CFAR_MR_NUM_REF_CELL_HALF_R)
#define OBJ_CFAR_MR_OSCFAR_KTH_ORDER_R							8
#define OBJ_CFAR_MR_THRESHOLD_ALPHA_R								2.5f
#define OBJ_CFAR_MR_BASE_THRESHOLD_R								500.0f			

#define OBJ_CFAR_MR_NUM_GUARD_CELL_D								2
#define OBJ_CFAR_MR_NUM_REF_CELL_HALF_D							8
#define OBJ_CFAR_MR_NUM_EXTEN_CELL_D								(OBJ_CFAR_MR_NUM_GUARD_CELL_D)
#define OBJ_CFAR_MR_OSCFAR_KTH_ORDER_D							28
#define OBJ_CFAR_MR_THRESHOLD_ALPHA_D								1.5f
#define OBJ_CFAR_MR_BASE_THRESHOLD_D								25.0f			

#define OBJ_CFAR_MR_R_IDX_MIN											12				/* min 3 */
#define OBJ_CFAR_MR_R_IDX_MAX											500			/* max 512 */

/* SR */
#define OBJ_CFAR_SR_NUM_GUARD_CELL_R								2
#define OBJ_CFAR_SR_NUM_REF_CELL_HALF_R							16
#define OBJ_CFAR_SR_NUM_EXTEN_CELL_R									(OBJ_CFAR_SR_NUM_REF_CELL_HALF_R)
#define OBJ_CFAR_SR_OSCFAR_KTH_ORDER_R								16
#define OBJ_CFAR_SR_THRESHOLD_ALPHA_R								2.2f
#define OBJ_CFAR_SR_BASE_THRESHOLD_R								500.0f		

#define OBJ_CFAR_SR_NUM_GUARD_CELL_D								2
#define OBJ_CFAR_SR_NUM_REF_CELL_HALF_D							8
#define OBJ_CFAR_SR_NUM_EXTEN_CELL_D								(OBJ_CFAR_SR_NUM_GUARD_CELL_D)
#define OBJ_CFAR_SR_OSCFAR_KTH_ORDER_D							28
#define OBJ_CFAR_SR_THRESHOLD_ALPHA_D								1.50f
#define OBJ_CFAR_SR_BASE_THRESHOLD_D								28.0f		

#define OBJ_CFAR_SR_R_IDX_MIN												4
#define OBJ_CFAR_SR_R_IDX_MAX											500

#define OBJ_CFAR_NUM_EXTEN_CELL_R_MAX								_sp_max(_sp_max(OBJ_CFAR_LR_NUM_EXTEN_CELL_R, OBJ_CFAR_MR_NUM_EXTEN_CELL_R), OBJ_CFAR_SR_NUM_EXTEN_CELL_R)
#define OBJ_CFAR_NUM_EXTEN_CELL_D_MAX								_sp_max(_sp_max(OBJ_CFAR_LR_NUM_EXTEN_CELL_D, OBJ_CFAR_MR_NUM_EXTEN_CELL_D), OBJ_CFAR_SR_NUM_EXTEN_CELL_D)

/* Frequency Estimation */
#define OBJ_FE_HAMMING_SCALE_VAL										1.216f
#define OBJ_FE_HANNING_SCALE_VAL										1.356f
#define OBJ_FE_CORRECTION_VAL_R											OBJ_FE_HAMMING_SCALE_VAL
#define OBJ_FE_CORRECTION_VAL_D											OBJ_FE_HAMMING_SCALE_VAL

/* Angle Estimation */
#define OBJ_AE_RM_NUM_CH													SP_NUM_RX
#define OBJ_AE_RM_CH_POS													{0.00f , 0.65f, 1.30f, 1.95f, 2.60f, 3.25f, 3.90f, 4.55f, 5.20f, 5.85f, 6.50f, 7.15f, 7.80f, 8.45f, 9.10f, 9.75f}

#define OBJ_AE_NUM_CH_PARALLE											192
#define OBJ_AE_CH_POS_Y_PARALLE											{0.00f , 0.65f , 1.30f , 1.95f , 2.60f , 3.25f , 3.90f , 4.55f , 5.20f , 5.85f , 6.50f , 7.15f , 7.80f , 8.45f , 9.10f , 9.75f , 1.30f , 1.95f , 2.60f , 3.25f , 3.90f , 4.55f , 5.20f , 5.85f , 6.50f , 7.15f , 7.80f , 8.45f , 9.10f , 9.75f , 10.40f , 11.05f , 2.60f , 3.25f , 3.90f , 4.55f , 5.20f , 5.85f , 6.50f , 7.15f , 7.80f , 8.45f , 9.10f , 9.75f , 10.40f , 11.05f , 11.70f , 12.35f , 3.90f , 4.55f , 5.20f , 5.85f , 6.50f , 7.15f , 7.80f , 8.45f , 9.10f , 9.75f , 10.40f , 11.05f , 11.70f , 12.35f , 13.00f , 13.65f , 5.20f , 5.85f , 6.50f , 7.15f , 7.80f , 8.45f , 9.10f , 9.75f , 10.40f , 11.05f , 11.70f , 12.35f , 13.00f , 13.65f , 14.30f , 14.95f , 6.50f , 7.15f , 7.80f , 8.45f , 9.10f , 9.75f , 10.40f , 11.05f , 11.70f , 12.35f , 13.00f , 13.65f , 14.30f , 14.95f , 15.60f , 16.25f , 10.40f , 11.05f , 11.70f , 12.35f , 13.00f , 13.65f , 14.30f , 14.95f , 15.60f , 16.25f , 16.90f , 17.55f , 18.20f , 18.85f , 19.50f , 20.15f , 11.70f , 12.35f , 13.00f , 13.65f , 14.30f , 14.95f , 15.60f , 16.25f , 16.90f , 17.55f , 18.20f , 18.85f , 19.50f , 20.15f , 20.80f , 21.45f , 13.00f , 13.65f , 14.30f , 14.95f , 15.60f , 16.25f , 16.90f , 17.55f , 18.20f , 18.85f , 19.50f , 20.15f , 20.80f , 21.45f , 22.10f , 22.75f , 14.30f , 14.95f , 15.60f , 16.25f , 16.90f , 17.55f , 18.20f , 18.85f , 19.50f , 20.15f , 20.80f , 21.45f , 22.10f , 22.75f , 23.40f , 24.05f , 15.60f , 16.25f , 16.90f , 17.55f , 18.20f , 18.85f , 19.50f , 20.15f , 20.80f , 21.45f , 22.10f , 22.75f , 23.40f , 24.05f , 24.70f , 25.35f , 16.90f , 17.55f , 18.20f , 18.85f , 19.50f , 20.15f , 20.80f , 21.45f , 22.10f , 22.75f , 23.40f , 24.05f , 24.70f , 25.35f , 26.00f , 26.65f}
#define OBJ_AE_CH_POS_Z_PARALLE											{0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f}

//#define OBJ_AE_NUM_CH_HEXA												162
//#define OBJ_AE_CH_POS_Y_HEXA											{5.85f , 6.50f , 7.15f , 7.80f , 8.45f , 9.10f , 9.75f , 4.55f , 5.20f , 5.85f , 6.50f , 7.15f , 7.80f , 8.45f , 9.10f , 9.75f , 10.40f , 11.05f , 3.25f , 3.90f , 4.55f , 5.20f , 5.85f , 6.50f , 7.15f , 7.80f , 8.45f , 9.10f , 9.75f , 10.40f , 11.05f , 11.70f , 12.35f , 3.90f , 4.55f , 5.20f , 5.85f , 6.50f , 7.15f , 7.80f , 8.45f , 9.10f , 9.75f , 10.40f , 11.05f , 11.70f , 12.35f , 13.00f , 13.65f , 5.20f , 5.85f , 6.50f , 7.15f , 7.80f , 8.45f , 9.10f , 9.75f , 10.40f , 11.05f , 11.70f , 12.35f , 13.00f , 13.65f , 14.30f , 14.95f , 6.50f , 7.15f , 7.80f , 8.45f , 9.10f , 9.75f , 10.40f , 11.05f , 11.70f , 12.35f , 13.00f , 13.65f , 14.30f , 14.95f , 15.60f , 16.25f , 10.40f , 11.05f , 11.70f , 12.35f , 13.00f , 13.65f , 14.30f , 14.95f , 15.60f , 16.25f , 16.90f , 17.55f , 18.20f , 18.85f , 19.50f , 20.15f , 11.70f , 12.35f , 13.00f , 13.65f , 14.30f , 14.95f , 15.60f , 16.25f , 16.90f , 17.55f , 18.20f , 18.85f , 19.50f , 20.15f , 20.80f , 21.45f , 13.00f , 13.65f , 14.30f , 14.95f , 15.60f , 16.25f , 16.90f , 17.55f , 18.20f , 18.85f , 19.50f , 20.15f , 20.80f , 21.45f , 22.10f , 22.75f , 14.30f , 14.95f , 15.60f , 16.25f , 16.90f , 17.55f , 18.20f , 18.85f , 19.50f , 20.15f , 20.80f , 21.45f , 22.10f , 22.75f , 23.40f , 15.60f , 16.25f , 16.90f , 17.55f , 18.20f , 18.85f , 19.50f , 20.15f , 20.80f , 21.45f , 22.10f , 16.90f , 17.55f , 18.20f , 18.85f , 19.50f , 20.15f , 20.80f }
//#define OBJ_AE_CH_POS_Z_HEXA											{0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 0.00f , 0.90f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 1.80f , 2.70f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f}


#define OBJ_AE_NUM_CH_HEXA												104
#define OBJ_AE_CH_POS_Y_HEXA												{7.80f , 8.45f , 9.10f , 9.75f , 9.10f , 9.75f , 10.40f , 11.05f , 2.60f , 3.25f , 3.90f , 4.55f , 5.20f , 5.85f , 6.50f , 7.15f , 7.80f , 8.45f , 9.10f , 9.75f , 10.40f , 11.05f , 11.70f , 12.35f , 3.90f , 4.55f , 5.20f , 5.85f , 6.50f , 7.15f , 7.80f , 8.45f , 9.10f , 9.75f , 10.40f , 11.05f , 11.70f , 12.35f , 13.00f , 13.65f , 11.70f , 12.35f , 13.00f , 13.65f , 14.30f , 14.95f , 13.00f , 13.65f , 14.30f , 14.95f , 15.60f , 16.25f , 10.40f , 11.05f , 11.70f , 12.35f , 11.70f , 12.35f , 13.00f , 13.65f , 13.00f , 13.65f , 14.30f , 14.95f , 15.60f , 16.25f , 16.90f , 17.55f , 18.20f , 18.85f , 19.50f , 20.15f , 20.80f , 21.45f , 22.10f , 22.75f , 14.30f , 14.95f , 15.60f , 16.25f , 16.90f , 17.55f , 18.20f , 18.85f , 19.50f , 20.15f , 20.80f , 21.45f , 22.10f , 22.75f , 23.40f , 24.05f , 15.60f , 16.25f , 16.90f , 17.55f , 18.20f , 18.85f , 16.90f , 17.55f , 18.20f , 18.85f , 19.50f , 20.15f}
#define OBJ_AE_CH_POS_Z_HEXA												{0.00f , 0.90f , 0.00f , 0.90f , 1.80f , 2.70f , 1.80f , 2.70f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f , 0.00f , 0.90f , 0.00f , 0.90f , 1.80f , 2.70f , 1.80f , 2.70f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 3.60f , 4.50f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 5.40f , 6.30f , 7.20f , 8.10f , 7.20f , 8.10f , 7.20f , 8.10f , 9.00f , 9.90f , 9.00f , 9.90f , 9.00f , 9.90f}

#define OBJ_HEXA_ARRAY_ON													1

#if (OBJ_HEXA_ARRAY_ON == 1)
#define OBJ_AE_NUM_CH														OBJ_AE_NUM_CH_HEXA							
#define OBJ_AE_CH_POS_Y														OBJ_AE_CH_POS_Y_HEXA
#define OBJ_AE_CH_POS_Z														OBJ_AE_CH_POS_Z_HEXA	

#else
#define OBJ_AE_NUM_CH														OBJ_AE_NUM_CH_PARALLE								
#define OBJ_AE_CH_POS_Y														OBJ_AE_CH_POS_Y_PARALLE
#define OBJ_AE_CH_POS_Z														OBJ_AE_CH_POS_Z_PARALLE
#endif

#define OBJ_AE_NUM_CH_REMOV											(OBJ_AE_NUM_CH_PARALLE-OBJ_AE_NUM_CH_HEXA)

#define OBJ_AE_CH_REMOV_IDX												{0,1,2,3,4,5,6,7,8,9,10,11,16,17,18,19,20,21,22,23,24,25,26,27,64,65,66,67,68,69,70,71,72,73,80,81,82,83,84,85,86,87,88,89,100,101,102,103,104,105,106,107,108,109,110,111,116,117,118,119,120,121,122,123,124,125,126,127,166,167,168,169,170,171,172,173,174,175,182,183,184,185,186,187,188,189,190,191}

/* RM */
#define OBJ_AE_AZI_RM_NUM_APS_STEPS									63									/*-46.5 ~ 46.5 */
#define OBJ_AE_AZI_RM_APS_STEP_SIZE										1.5f
#define OBJ_AE_RM_APS_SLL_TH												0.2f
#define OBJ_AE_RM_NUM_TARGET_MAX									2
#define OBJ_AE_RM_MULTI_TARGET_TH										0.5f

/* LR */

#define OBJ_AE_PRE_AZI_LR_NUM_APS_STEPS								23									/* -11.5 - 11.5 */
#define OBJ_AE_PRE_AZI_LR_APS_STEP_SIZE								OBJ_AE_AZI_RM_APS_STEP_SIZE

#define OBJ_AE_AZI_LR_NUM_APS_STEPS									33									/* -10.0 - 10.0 */
#define OBJ_AE_ELE_LR_NUM_APS_STEPS									15									/* -15.0 - 15.0 */
#define OBJ_AE_AZI_LR_APS_STEP_SIZE										1.0f
#define OBJ_AE_ELE_LR_APS_STEP_SIZE										2.0f
#define OBJ_AE_LR_APS_SLL_TH												0.2f
#define OBJ_AE_LR_NUM_TARGET_MAX										10
#define OBJ_AE_LR_MULTI_TARGET_TH										0.75f

/* MR */

#define OBJ_AE_PRE_AZI_MR_NUM_APS_STEPS							43									/* -31.5 - 31.5 */						
#define OBJ_AE_PRE_AZI_MR_APS_STEP_SIZE								OBJ_AE_AZI_RM_APS_STEP_SIZE					

#define OBJ_AE_AZI_MR_NUM_APS_STEPS									61									/* -30.0 - 30.0 */
#define OBJ_AE_ELE_MR_NUM_APS_STEPS									15									/* -14.0 - 14.0 */

#define OBJ_AE_AZI_MR_APS_STEP_SIZE										1.0f
#define OBJ_AE_ELE_MR_APS_STEP_SIZE										2.0f
#define OBJ_AE_MR_APS_SLL_TH												0.2f
#define OBJ_AE_MR_NUM_TARGET_MAX									10
#define OBJ_AE_MR_MULTI_TARGET_TH										0.75f

/* SR */
#define OBJ_AE_PRE_AZI_SR_NUM_APS_STEPS								63									/* -46.5 - 46.5 */
#define OBJ_AE_PRE_AZI_SR_APS_STEP_SIZE								OBJ_AE_AZI_RM_APS_STEP_SIZE

#define OBJ_AE_AZI_SR_NUM_APS_STEPS									91									/* -45 - 45 */
#define OBJ_AE_ELE_SR_NUM_APS_STEPS									15									/* -14 - 14 */

#define OBJ_AE_AZI_SR_APS_STEP_SIZE										1.0f
#define OBJ_AE_ELE_SR_APS_STEP_SIZE										2.0f
#define OBJ_AE_SR_APS_SLL_TH												0.2f
#define OBJ_AE_SR_NUM_TARGET_MAX										10
#define OBJ_AE_SR_MULTI_TARGET_TH										0.75f


#define OBJ_AE_PRE_AZI_NUM_APS_STEPS_MAX							_sp_max(_sp_max(OBJ_AE_PRE_AZI_LR_NUM_APS_STEPS, OBJ_AE_PRE_AZI_MR_NUM_APS_STEPS), OBJ_AE_PRE_AZI_SR_NUM_APS_STEPS)
#define OBJ_AE_AZI_NUM_APS_STEPS_MAX								_sp_max(_sp_max(OBJ_AE_AZI_LR_NUM_APS_STEPS, OBJ_AE_AZI_MR_NUM_APS_STEPS), OBJ_AE_AZI_SR_NUM_APS_STEPS)
#define OBJ_AE_ELE_NUM_APS_STEPS_MAX								_sp_max(_sp_max(OBJ_AE_ELE_LR_NUM_APS_STEPS, OBJ_AE_ELE_MR_NUM_APS_STEPS), OBJ_AE_ELE_SR_NUM_APS_STEPS)

#define OBJ_AE_NUM_TARGET_MAX											_sp_max(_sp_max(OBJ_AE_LR_NUM_TARGET_MAX, OBJ_AE_MR_NUM_TARGET_MAX), OBJ_AE_SR_NUM_TARGET_MAX)

#define OBJ_AE_REF_NUM_TARGET_MAX									2

#define OBJ_AE_CANDI_NUM_TARGET_MAX								(OBJ_AE_NUM_TARGET_MAX*2)						
#define OBJ_AE_NUM_PEAK_TARGET_MAX									5								

#define OBJ_AE_FAILURE_ANGLE												1000.0f

/* Calc Object */

#define OBJ_NUM_RM_CANDIDATE_OBJ									(OBJ_NUM_RM_PEAK_MAX*OBJ_AE_RM_NUM_TARGET_MAX)
#define OBJ_CO_NUM_HARMONICS_MAX									1
#define OBJ_NUM_CANDIDATE_OBJ											(OBJ_NUM_PEAK_HARM_MAX*OBJ_CO_NUM_HARMONICS_MAX)

/* LR */
#define OBJ_CO_LR_MU															(SP_LR_BANDWIDTH / SP_SWEEP_TIME)
#define OBJ_CO_LR_MOD_TIME												(SP_NUM_CHIRPS * SP_LR_CHIRP_INTERVAL)
#define OBJ_CO_LR_DELTA_R													(SP_LIGHT_SPEED / (2.0f * SP_LR_BANDWIDTH))															/* c/(2*B) */
#define OBJ_CO_LR_DELTA_V													(SP_LAMDA / (2.0f * SP_LR_CHIRP_INTERVAL * (float32_t)(OBJ_NUM_TX*SP_NUM_FFT_D)))		/* lambda / (2*Tc2c*N) */
#define OBJ_CO_LR_INTERVAL_V												(OBJ_CO_LR_DELTA_V * (float32_t)SP_NUM_FFT_D)
#define OBJ_CO_LR_R_ERR_FACTOR											((SP_LIGHT_SPEED / (OBJ_CO_LR_MU * SP_LAMDA)) + OBJ_CO_LR_MOD_TIME)

/* MR */
#define OBJ_CO_MR_MU														(SP_MR_BANDWIDTH / SP_SWEEP_TIME)
#define OBJ_CO_MR_MOD_TIME												(SP_NUM_CHIRPS * SP_MR_CHIRP_INTERVAL)
#define OBJ_CO_MR_DELTA_R													(SP_LIGHT_SPEED / (2.0f * SP_MR_BANDWIDTH))															/* c/(2*B) */
#define OBJ_CO_MR_DELTA_V													(SP_LAMDA / (2.0f * SP_MR_CHIRP_INTERVAL * (float32_t)(OBJ_NUM_TX*SP_NUM_FFT_D)))	/* lambda / (2*Tc2c*N) */
#define OBJ_CO_MR_INTERVAL_V												(OBJ_CO_MR_DELTA_V * (float32_t)SP_NUM_FFT_D)
#define OBJ_CO_MR_R_ERR_FACTOR											(SP_LIGHT_SPEED / (OBJ_CO_MR_MU * SP_LAMDA))

/* SR */
#define OBJ_CO_SR_MU															(SP_SR_BANDWIDTH / SP_SWEEP_TIME)
#define OBJ_CO_SR_MOD_TIME												(SP_NUM_CHIRPS * SP_SR_CHIRP_INTERVAL)
#define OBJ_CO_SR_DELTA_R													(SP_LIGHT_SPEED / (2.0f * SP_SR_BANDWIDTH))															/* c/(2*B) */
#define OBJ_CO_SR_DELTA_V													(SP_LAMDA / (2.0f * SP_SR_CHIRP_INTERVAL * (float32_t)(OBJ_NUM_TX*SP_NUM_FFT_D)))		/* lambda / (2*Tc2c*N) */
#define OBJ_CO_SR_INTERVAL_V												(OBJ_CO_SR_DELTA_V * (float32_t)SP_NUM_FFT_D)
#define OBJ_CO_SR_R_ERR_FACTOR											((SP_LIGHT_SPEED / (OBJ_CO_SR_MU * SP_LAMDA)) - OBJ_CO_SR_MOD_TIME)

/* Reference Modulation */
#define OBJ_CO_RM_NEG_VEL_IDX											((SP_RM_NUM_FFT_D / 2) - 16)																					/* 480 * 0.3867 = 185.xx kph */
#define OBJ_CO_RM_MU														(SP_RM_BANDWIDTH / SP_RM_SWEEP_TIME)
#define OBJ_CO_RM_MOD_TIME												(SP_RM_NUM_CHIRPS * SP_RM_CHIRP_INTERVAL)
#define OBJ_CO_RM_DELTA_R													(SP_LIGHT_SPEED / (2.0f * SP_RM_BANDWIDTH))															/* c/(2*B) */
#define OBJ_CO_RM_DELTA_V													(SP_LAMDA / (2.0f * SP_RM_CHIRP_INTERVAL * (float32_t)(SP_RM_NUM_FFT_D)))					/* lambda / (2*Tc2c*N) */
#define OBJ_CO_RM_INTERVAL_V												(OBJ_CO_RM_DELTA_V * (float32_t)SP_RM_NUM_FFT_D)
#define OBJ_CO_RM_R_ERR_FACTOR											((SP_LIGHT_SPEED / (OBJ_CO_RM_MU * SP_LAMDA)) + ((0.5f * OBJ_CO_RM_MOD_TIME) + OBJ_CO_LR_MOD_TIME + (0.5f * OBJ_CO_MR_MOD_TIME)))

/* Object Out */
#define OBJ_NUM_OBJECT_MAX												SP_NUM_OBJECT_MAX																							/* 1024*4 */
#define OBJ_NUM_RM_OBJECT_MAX											(OBJ_NUM_RM_PEAK_MAX*OBJ_AE_RM_NUM_TARGET_MAX)

#define OBJ_NUM_FILETERD_OBJ_MAX										(SP_NUM_OBJECT_MAX*2)																						/* 1024 */
#define OBJ_AE_ADD_OBJ_ENABLE											1  /* 1: Enable, 0 Disable */

#endif

