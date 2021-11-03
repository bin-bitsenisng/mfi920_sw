/**************************************************************************************
* -----------------------------------   include   ----------------------------------- *
**************************************************************************************/
#include "Trk_Main.h"


/**************************************************************************************
* -----------------------------------   define   ------------------------------------ *
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/


/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
static float32_t Trk_vCalc1dAreaOverlapRatio(Distribution_t range1, Distribution_t range2);
static float32_t Trk_vCalc2dAreaOverlapRatio(BoundingBox_t bbox1, BoundingBox_t bbox2);


/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/

void Trk_vSensorFusionObjectMatching(void)
{
#if TRK_SENSOR_FUSION_OBJECT_MATCHING
	float32_t rdr_3d_bbox_corner_wld[8][4];	/* [8corners][x/y/z/1] */
	float32_t rdr_3d_bbox_corner_img[8][3];	/* [8corners][x/y/1] */
	float32_t bbox_max[2];
	float32_t bbox_min[2];
	float32_t iou;
	float32_t iou_max;
	int16_t i_robj;
	int16_t i_robj2;
	int16_t i_corner;
	int16_t i_vobj;
	int16_t i_vobj_match;


	for (i_robj = 0; i_robj < TRK_NUM_TRACK_MAX; i_robj++)
	{
		if (gTrackData[i_robj].Status != INVALID)
		{
			/* Get 4 corners */
			for (i_corner = 0; i_corner < 4; i_corner++)
			{
				rdr_3d_bbox_corner_wld[i_corner][0] = gTrackData[i_robj].PredState.f32BoundingBoxX[i_corner];
				rdr_3d_bbox_corner_wld[i_corner][1] = gTrackData[i_robj].PredState.f32BoundingBoxY[i_corner];
				rdr_3d_bbox_corner_wld[i_corner][2] = 0;
				rdr_3d_bbox_corner_wld[i_corner][3] = 1;

				rdr_3d_bbox_corner_wld[i_corner + 4][0] = rdr_3d_bbox_corner_wld[i_corner][0];
				rdr_3d_bbox_corner_wld[i_corner + 4][1] = rdr_3d_bbox_corner_wld[i_corner][1];
				rdr_3d_bbox_corner_wld[i_corner + 4][2] = TRK_INIT_HEIGHT_MOVING;
				rdr_3d_bbox_corner_wld[i_corner + 4][3] = 1;
			}


			/* Project radar object to image plane*/
			bbox_max[0] = 0;
			bbox_max[1] = 0;
			bbox_min[0] = TRK_IMAGE_WIDTH;
			bbox_min[1] = TRK_IMAGE_HEIGHT;

			for (i_corner = 0; i_corner < 8; i_corner++)
			{
				wld2img(rdr_3d_bbox_corner_wld[i_corner], rdr_3d_bbox_corner_img[i_corner], gCameraParam.P);

				if (rdr_3d_bbox_corner_img[i_corner][0] > bbox_max[0])
				{
					bbox_max[0] = rdr_3d_bbox_corner_img[i_corner][0];
				}

				if (rdr_3d_bbox_corner_img[i_corner][1] > bbox_max[1])
				{
					bbox_max[1] = rdr_3d_bbox_corner_img[i_corner][1];
				}

				if (rdr_3d_bbox_corner_img[i_corner][0] < bbox_min[0])
				{
					bbox_min[0] = rdr_3d_bbox_corner_img[i_corner][0];
				}

				if (rdr_3d_bbox_corner_img[i_corner][1] < bbox_min[1])
				{
					bbox_min[1] = rdr_3d_bbox_corner_img[i_corner][1];
				}
			}


			/* Image bounding box of radar object */
			gTrackData[i_robj].bbox_img.x = bbox_min[0];
			gTrackData[i_robj].bbox_img.y = bbox_min[1];
			gTrackData[i_robj].bbox_img.w = bbox_max[0] - bbox_min[0] + 1;
			gTrackData[i_robj].bbox_img.h = bbox_max[1] - bbox_min[1] + 1;


			/* Vision object matching using bounding box overlap ratio */
			iou_max = 0;
			i_vobj_match = -1;
			for (i_vobj = 0; i_vobj < gVisionObjCnt; i_vobj++)
			{
				iou = Trk_vCalc2dAreaOverlapRatio(gTrackData[i_robj].bbox_img, gVisionObj[i_vobj].bbox_img);

				if ((iou > iou_max) && (iou > TRK_SENSOR_FUSION_ASSO_IOU_THERSHOLD))
				{
					if (gVisionObj[i_vobj].match_radar_obj_idx == -1)
					{
						iou_max = iou;
						i_vobj_match = i_vobj;
					}
					else
					{
						if (iou > gTrackData[gVisionObj[i_vobj].match_radar_obj_idx].bbox_overlap_ratio)
						{
							iou_max = iou;
							i_vobj_match = i_vobj;
						}
					}
				}
			}

			if (i_vobj_match != -1)
			{
				i_robj2 = gVisionObj[i_vobj_match].match_radar_obj_idx;
				if (i_robj2 != -1)
				{
					if (iou_max > gTrackData[i_robj2].bbox_overlap_ratio)
					{
						gTrackData[i_robj2].fusion_state = SF_RADAR_ONLY;
						gTrackData[i_robj2].match_vision_obj_idx = -1;
						gTrackData[i_robj2].FusionAge = 0;
					}
				}

				gTrackData[i_robj].fusion_state = SF_FUSION_MOVING;
				gTrackData[i_robj].match_vision_obj_idx = i_vobj_match;
				gTrackData[i_robj].bbox_overlap_ratio = iou_max;
				gTrackData[i_robj].FusionAge++;

				gVisionObj[i_vobj_match].match_radar_obj_idx = i_robj;
			}
		}
	}
#endif
}

void Trk_vSensorFusionClusterMatching(void)
{
#if TRK_SENSOR_FUSION_CLUSTER_MATCHING_STATIONARY
	int16_t i_mscl;
	int16_t i_vobj;
	float32_t azimuth_overlap_ratio;

	int16_t best_match_mscl_idx;
	float32_t best_match_overlap;

	/* Find azimuth range of vision object */
	for (i_vobj = 0; i_vobj < gVisionObjCnt; i_vobj++)
	{
		/* Minimum azimuth */
		gVisionObj[i_vobj].AziAng.f32Min = _trk_atan2df(gVisionObj[i_vobj].bbox_corner_wld[1][1], gVisionObj[i_vobj].bbox_corner_wld[1][0]);
		/* Maximum azimuth */
		gVisionObj[i_vobj].AziAng.f32Max = _trk_atan2df(gVisionObj[i_vobj].bbox_corner_wld[0][1], gVisionObj[i_vobj].bbox_corner_wld[0][0]);
	}

	for (i_vobj = 0; i_vobj < gVisionObjCnt; i_vobj++)
	{
		if (gVisionObj[i_vobj].match_radar_obj_idx != -1)
		{
			best_match_overlap = 0.0f;
			best_match_mscl_idx = -1;
			for (i_mscl = 0; i_mscl < gMsclCnt; i_mscl++)
			{
				azimuth_overlap_ratio = Trk_vCalc1dAreaOverlapRatio(gMeasClst[i_mscl].AziAng, gVisionObj[i_vobj].AziAng);

				if ((azimuth_overlap_ratio > TRK_SENSOR_FUSION_CLUSTER_MATCHING_OVERLAP_THRESHOLD)
					&& (azimuth_overlap_ratio > best_match_overlap))
				{
					best_match_overlap = azimuth_overlap_ratio;
					best_match_mscl_idx = i_mscl;
				}
			}

			if (best_match_mscl_idx != -1)
			{
				if (gMeasClst[best_match_mscl_idx].MatchVisionObjIdx != -1)
				{
					gVisionObj[gMeasClst[best_match_mscl_idx].MatchVisionObjIdx].MatchMeasClstIdx = -1;
				}

				gVisionObj[i_vobj].MatchMeasClstIdx = best_match_mscl_idx;
				gVisionObj[i_vobj].AzimuthOverlapRatio = best_match_overlap;

				gMeasClst[best_match_mscl_idx].MatchVisionObjIdx = i_vobj;
				gMeasClst[best_match_mscl_idx].AzimuthOverlapRatio = best_match_overlap;
			}
		}
	}
#endif
}


void Trk_vSensorFusionAzimuthCorrection(TrackData_t *TrackData)
{
#if TRK_SENSOR_FUSION_AZ_COR
	float32_t rdr_3d_bbox_corner_wld[8][4];	/* [8corners][x/y/z/1] */
	float32_t rdr_3d_bbox_corner_img[8][3];	/* [8corners][x/y/1] */
	float32_t rdr_bbox_bottom_img[2][2];	/* [left/right][x/y] */
	float32_t bbox_min[2];
	float32_t bbox_max[2];
	float32_t dist;
	float32_t min_dist;
	float32_t vision_obj_gnd_img[3];		/* x, y, 1 */
	float32_t vision_obj_gnd_wld[3];
	float32_t vision_obj_gnd_wld_range;
	float32_t vision_obj_gnd_wld_azimuth;
	float32_t radar_obj_gnd_wld[3];
	float32_t radar_obj_gnd_wld_range;
	float32_t radar_obj_gnd_wld_azimuth;
	float32_t radar_obj_gnd_wld_az_cor[2]; /* x, y pos corrected toward vision azimuth */
	float32_t vahinishing_point_wld[4];
	float32_t vahinishing_point_img[3];
	float32_t tl_delta[2];	/* translating object (x, y) */
	float32_t iou;
	int16_t min_dir;
	int16_t min_corner;
	int16_t i_vobj;
	int16_t i_dir;
	int16_t i_corner;
	int16_t idx;
	int16_t i_tkl;
	uint8_t flag_inside_az_cor_area;
	uint8_t flag_below_vanishing_point;

	TrkState_t *TrkState;


	TrkState = &(TrackData->UpdState);

	//if (TrackData->fusion_state != RADAR_ONLY)
	{
		/* Get 4 corners */
		rdr_3d_bbox_corner_wld[0][0] = TrkState->f32BoundingBoxX[0];
		rdr_3d_bbox_corner_wld[0][1] = TrkState->f32BoundingBoxY[0];
		rdr_3d_bbox_corner_wld[0][2] = 0;
		rdr_3d_bbox_corner_wld[0][3] = 1;

		rdr_3d_bbox_corner_wld[1][0] = TrkState->f32BoundingBoxX[1];
		rdr_3d_bbox_corner_wld[1][1] = TrkState->f32BoundingBoxY[1];
		rdr_3d_bbox_corner_wld[1][2] = 0;
		rdr_3d_bbox_corner_wld[1][3] = 1;

		rdr_3d_bbox_corner_wld[2][0] = TrkState->f32BoundingBoxX[2];
		rdr_3d_bbox_corner_wld[2][1] = TrkState->f32BoundingBoxY[2];
		rdr_3d_bbox_corner_wld[2][2] = 0;
		rdr_3d_bbox_corner_wld[2][3] = 1;

		rdr_3d_bbox_corner_wld[3][0] = TrkState->f32BoundingBoxX[3];
		rdr_3d_bbox_corner_wld[3][1] = TrkState->f32BoundingBoxY[3];
		rdr_3d_bbox_corner_wld[3][2] = 0;
		rdr_3d_bbox_corner_wld[3][3] = 1;


		for (i_corner = 0; i_corner < 4; i_corner++)
		{
			rdr_3d_bbox_corner_wld[i_corner + 4][0] = rdr_3d_bbox_corner_wld[i_corner][0];
			rdr_3d_bbox_corner_wld[i_corner + 4][1] = rdr_3d_bbox_corner_wld[i_corner][1];
			rdr_3d_bbox_corner_wld[i_corner + 4][2] = TRK_SF_OBJECT_INIT_HEIGHT;
			rdr_3d_bbox_corner_wld[i_corner + 4][3] = 1;
		}


		/* Project radar object to image plane*/
		bbox_max[0] = 0;
		bbox_max[1] = 0;
		bbox_min[0] = TRK_IMAGE_WIDTH;
		bbox_min[1] = TRK_IMAGE_HEIGHT;

		for (i_corner = 0; i_corner < 8; i_corner++)
		{
			wld2img(rdr_3d_bbox_corner_wld[i_corner], rdr_3d_bbox_corner_img[i_corner], gCameraParam.P);

			if (rdr_3d_bbox_corner_img[i_corner][0] < bbox_min[0])
			{
				bbox_min[0] = rdr_3d_bbox_corner_img[i_corner][0];
			}

			if (rdr_3d_bbox_corner_img[i_corner][1] < bbox_min[1])
			{
				bbox_min[1] = rdr_3d_bbox_corner_img[i_corner][1];
			}

			if (rdr_3d_bbox_corner_img[i_corner][0] > bbox_max[0])
			{
				bbox_max[0] = rdr_3d_bbox_corner_img[i_corner][0];
			}

			if (rdr_3d_bbox_corner_img[i_corner][1] > bbox_max[1])
			{
				bbox_max[1] = rdr_3d_bbox_corner_img[i_corner][1];
			}
		}


		/* Image bounding box of radar object */
		TrackData->bbox_img.x = bbox_min[0];
		TrackData->bbox_img.y = bbox_min[1];
		TrackData->bbox_img.w = bbox_max[0] - bbox_min[0] + 1;
		TrackData->bbox_img.h = bbox_max[1] - bbox_min[1] + 1;


		/* Find a ground point */
		if (_trk_isbound((TrkState->f32BoundingBoxY[0] + TrkState->f32BoundingBoxY[2]) * 0.5,
			TRK_SENSOR_FUSION_AZ_COR_GND_USE_MID_BOX_AREA_YPOS_MIN,
			TRK_SENSOR_FUSION_AZ_COR_GND_USE_MID_BOX_AREA_YPOS_MAX))
		{
			TrackData->radar_obj_gnd_img[0] = TrackData->bbox_img.x + TrackData->bbox_img.w * 0.5;
			TrackData->radar_obj_gnd_img[1] = TrackData->bbox_img.y + TrackData->bbox_img.h;
			TrackData->radar_obj_gnd_img[2] = 1;

			MatMul_3x3and3x1(gCameraParam.H, TrackData->radar_obj_gnd_img, radar_obj_gnd_wld);
			radar_obj_gnd_wld[0] = radar_obj_gnd_wld[0] / (radar_obj_gnd_wld[2] + TRK_APPROXIMATE_ZERO);
			radar_obj_gnd_wld[1] = radar_obj_gnd_wld[1] / (radar_obj_gnd_wld[2] + TRK_APPROXIMATE_ZERO);

			min_dir = 2;
		}
		else
		{
			rdr_bbox_bottom_img[0][0] = TrackData->bbox_img.x;
			rdr_bbox_bottom_img[0][1] = TrackData->bbox_img.y + TrackData->bbox_img.h - 1;
			rdr_bbox_bottom_img[1][0] = TrackData->bbox_img.x + TrackData->bbox_img.w - 1;
			rdr_bbox_bottom_img[1][1] = TrackData->bbox_img.y + TrackData->bbox_img.h - 1;

			min_dist = TRK_IMAGE_WIDTH;
			min_dir = -1;
			min_corner = -1;

			for (i_dir = 0; i_dir < 2; i_dir++)
			{
				for (i_corner = 0; i_corner < 4; i_corner++)
				{
					dist = _trk_hypotf(rdr_bbox_bottom_img[i_dir][0] - rdr_3d_bbox_corner_img[i_corner][0], rdr_bbox_bottom_img[i_dir][1] - rdr_3d_bbox_corner_img[i_corner][1]);
					if (dist < min_dist)
					{
						min_dist = dist;
						min_dir = i_dir;
						min_corner = i_corner;
					}
				}
			}

			/* for debugging */
			TrackData->radar_obj_gnd_img[0] = rdr_3d_bbox_corner_img[min_corner][0];
			TrackData->radar_obj_gnd_img[1] = rdr_3d_bbox_corner_img[min_corner][1];

			/* Check azimuth correction available */
			radar_obj_gnd_wld[0] = rdr_3d_bbox_corner_wld[min_corner][0];
			radar_obj_gnd_wld[1] = rdr_3d_bbox_corner_wld[min_corner][1];

		}
	}


	/* Checking azimuth correction available area */
	if ((_trk_isbound(radar_obj_gnd_wld[1], TRK_SENSOR_FUSION_AZ_COR_AREA_LEFT_YPOS_MIN, TRK_SENSOR_FUSION_AZ_COR_AREA_LEFT_YPOS_MAX)
		&& _trk_isbound(radar_obj_gnd_wld[0], TRK_SENSOR_FUSION_AZ_COR_AREA_LEFT_XPOS_MIN, TRK_SENSOR_FUSION_AZ_COR_AREA_LEFT_XPOS_MAX))
		|| (_trk_isbound(radar_obj_gnd_wld[1], TRK_SENSOR_FUSION_AZ_COR_AREA_FRONT_YPOS_MIN, TRK_SENSOR_FUSION_AZ_COR_AREA_FRONT_YPOS_MAX)
			&& _trk_isbound(radar_obj_gnd_wld[0], TRK_SENSOR_FUSION_AZ_COR_AREA_FRONT_XPOS_MIN, TRK_SENSOR_FUSION_AZ_COR_AREA_FRONT_XPOS_MAX))
		|| (_trk_isbound(radar_obj_gnd_wld[1], TRK_SENSOR_FUSION_AZ_COR_AREA_RIGHT_YPOS_MIN, TRK_SENSOR_FUSION_AZ_COR_AREA_RIGHT_YPOS_MAX)
			&& _trk_isbound(radar_obj_gnd_wld[0], TRK_SENSOR_FUSION_AZ_COR_AREA_RIGHT_XPOS_MIN, TRK_SENSOR_FUSION_AZ_COR_AREA_RIGHT_XPOS_MAX)))
	{
		flag_inside_az_cor_area = 1;
	}
	else
	{
		flag_inside_az_cor_area = 0;
	}

	if (TrackData->fusion_state != SF_RADAR_ONLY)
	{
		/* Azimuth correction */
		i_vobj = TrackData->match_vision_obj_idx;


		/* Find vanishing point */
		vahinishing_point_wld[0] = 1000000;
		vahinishing_point_wld[1] = 0;
		vahinishing_point_wld[2] = 0;
		vahinishing_point_wld[3] = 1;

		wld2img(vahinishing_point_wld, vahinishing_point_img, gCameraParam.P);

		if (gVisionObj[i_vobj].bbox_img.y + gVisionObj[i_vobj].bbox_img.h - 1 > vahinishing_point_img[1] + TRK_SENSOR_FUSION_AZ_COR_VANISHING_POINT_IMG_Y_MARGIN)
		{
			flag_below_vanishing_point = 1;
		}
		else
		{
			flag_below_vanishing_point = 0;
		}


		/* Get vision object ground point */
		if (min_dir == 0)	/* 0: LEFT, 1: RIGHT, 2: MIDDLE */
		{
			/* left side of bbox */
			TrackData->vision_obj_gnd_img[0] = gVisionObj[i_vobj].bbox_img.x;
			TrackData->vision_obj_gnd_img[1] = gVisionObj[i_vobj].bbox_img.y + gVisionObj[i_vobj].bbox_img.h - 1;
			TrackData->vision_obj_gnd_img[2] = 1;
		}
		else if (min_dir == 1)
		{
			/* right side of bbox */
			TrackData->vision_obj_gnd_img[0] = gVisionObj[i_vobj].bbox_img.x + gVisionObj[i_vobj].bbox_img.w - 1;
			TrackData->vision_obj_gnd_img[1] = gVisionObj[i_vobj].bbox_img.y + gVisionObj[i_vobj].bbox_img.h - 1;
			TrackData->vision_obj_gnd_img[2] = 1;
		}
		else
		{
			TrackData->vision_obj_gnd_img[0] = gVisionObj[i_vobj].bbox_img.x + (gVisionObj[i_vobj].bbox_img.w - 1) * 0.5;
			TrackData->vision_obj_gnd_img[1] = gVisionObj[i_vobj].bbox_img.y + gVisionObj[i_vobj].bbox_img.h - 1;
			TrackData->vision_obj_gnd_img[2] = 1;
		}

		MatMul_3x3and3x1(gCameraParam.H, TrackData->vision_obj_gnd_img, vision_obj_gnd_wld);
		vision_obj_gnd_wld[0] = vision_obj_gnd_wld[0] / (vision_obj_gnd_wld[2] + TRK_APPROXIMATE_ZERO);
		vision_obj_gnd_wld[1] = vision_obj_gnd_wld[1] / (vision_obj_gnd_wld[2] + TRK_APPROXIMATE_ZERO);


		/* Correction radar object toward the azimuth of vision object ground point */
		vision_obj_gnd_wld_range = _trk_hypotf(vision_obj_gnd_wld[1], vision_obj_gnd_wld[0]);
		vision_obj_gnd_wld_azimuth = _trk_atan2f(vision_obj_gnd_wld[1], vision_obj_gnd_wld[0]);

		radar_obj_gnd_wld_range = _trk_hypotf(radar_obj_gnd_wld[0], radar_obj_gnd_wld[1]);
		radar_obj_gnd_wld_azimuth = _trk_atan2f(radar_obj_gnd_wld[1], radar_obj_gnd_wld[0]);

		if (TrackData->fusion_state == SF_FUSION_MOVING)
		{
			radar_obj_gnd_wld_az_cor[0] = radar_obj_gnd_wld_range * _trk_cosf(vision_obj_gnd_wld_azimuth);
			radar_obj_gnd_wld_az_cor[1] = radar_obj_gnd_wld_range * _trk_sinf(vision_obj_gnd_wld_azimuth);
		}
		else
		{
			/* Vision only case */
			radar_obj_gnd_wld_az_cor[0] = vision_obj_gnd_wld_range * _trk_cosf(vision_obj_gnd_wld_azimuth);
			radar_obj_gnd_wld_az_cor[1] = vision_obj_gnd_wld_range * _trk_sinf(vision_obj_gnd_wld_azimuth);
		}

		if ((flag_inside_az_cor_area == 1) && (flag_below_vanishing_point == 1))
		{
			TrackData->tl_delta[0] = radar_obj_gnd_wld_az_cor[0] - radar_obj_gnd_wld[0];
			TrackData->tl_delta[1] = radar_obj_gnd_wld_az_cor[1] - radar_obj_gnd_wld[1];

			/* Translate radar object */
			TrkState->f32StateX[0] = TrkState->f32StateX[0] + TrackData->tl_delta[0] * TRK_SENSOR_FUSION_AZ_COR_POS_GAIN;
			TrkState->f32StateY[0] = TrkState->f32StateY[0] + TrackData->tl_delta[1] * TRK_SENSOR_FUSION_AZ_COR_POS_GAIN;
			TrkState->f32Ref_PosX = TrkState->f32Ref_PosX + TrackData->tl_delta[0] * TRK_SENSOR_FUSION_AZ_COR_POS_GAIN;
			TrkState->f32Ref_PosY = TrkState->f32Ref_PosY + TrackData->tl_delta[1] * TRK_SENSOR_FUSION_AZ_COR_POS_GAIN;
			TrkState->f32BoundingBoxX[0] = TrkState->f32BoundingBoxX[0] + TrackData->tl_delta[0] * TRK_SENSOR_FUSION_AZ_COR_POS_GAIN;
			TrkState->f32BoundingBoxX[1] = TrkState->f32BoundingBoxX[1] + TrackData->tl_delta[0] * TRK_SENSOR_FUSION_AZ_COR_POS_GAIN;
			TrkState->f32BoundingBoxX[2] = TrkState->f32BoundingBoxX[2] + TrackData->tl_delta[0] * TRK_SENSOR_FUSION_AZ_COR_POS_GAIN;
			TrkState->f32BoundingBoxX[3] = TrkState->f32BoundingBoxX[3] + TrackData->tl_delta[0] * TRK_SENSOR_FUSION_AZ_COR_POS_GAIN;
			TrkState->f32BoundingBoxY[0] = TrkState->f32BoundingBoxY[0] + TrackData->tl_delta[1] * TRK_SENSOR_FUSION_AZ_COR_POS_GAIN;
			TrkState->f32BoundingBoxY[1] = TrkState->f32BoundingBoxY[1] + TrackData->tl_delta[1] * TRK_SENSOR_FUSION_AZ_COR_POS_GAIN;
			TrkState->f32BoundingBoxY[2] = TrkState->f32BoundingBoxY[2] + TrackData->tl_delta[1] * TRK_SENSOR_FUSION_AZ_COR_POS_GAIN;
			TrkState->f32BoundingBoxY[3] = TrkState->f32BoundingBoxY[3] + TrackData->tl_delta[1] * TRK_SENSOR_FUSION_AZ_COR_POS_GAIN;

#if TRK_SENSOR_FUSION_AZ_COR_TKL
			for (idx = 0; idx < TrackData->s16GroupClstCnt; idx++)
			{
				i_tkl = TrackData->s16GroupClstIdx[idx];

				gClstData[i_tkl].f32UpdStateX[0] = gClstData[i_tkl].f32UpdStateX[0] + TrackData->tl_delta[0] * TRK_SENSOR_FUSION_AZ_COR_POS_GAIN;
				gClstData[i_tkl].f32UpdStateY[0] = gClstData[i_tkl].f32UpdStateY[0] + TrackData->tl_delta[1] * TRK_SENSOR_FUSION_AZ_COR_POS_GAIN;
			}
#endif
		}
		else
		{
			TrackData->tl_delta[0] = 0;
			TrackData->tl_delta[1] = 0;
		}
	}
	else
	{
		/* No correction when radar only */
		TrackData->tl_delta[0] = 0;
		TrackData->tl_delta[1] = 0;
	}
#endif
}


void Trk_vSensorFusionClassDecision(void)
{
#if TRK_SENSOR_FUSION_OBJECT_CLASS_DECISION
	ObjectClass_t vision_obj_class;
	ObjectClass_t i_class;
	int16_t i_obj;
	int16_t cnt_max;
	int16_t cnt_all;

	for (i_obj = 0; i_obj < TRK_NUM_TRACK_MAX; i_obj++)
	{
		if (gTrackData[i_obj].Status != INVALID)
		{
			if (gTrackData[i_obj].match_vision_obj_idx != -1)
			{
				/* Get class from associated vision object*/
				vision_obj_class = gVisionObj[gTrackData[i_obj].match_vision_obj_idx].class_id;

				if ((vision_obj_class < 0) || (vision_obj_class >= TRK_SENSOR_FUSION_CLASS_TYPE_MAX))
				{
					vision_obj_class = OBJCLASS_UNKNOWN;
				}

#if TRK_SENSOR_FUSION_CLASS_METHOD != 1
				gTrackData[i_obj].obj_class = vision_obj_class;
				gTrackData[i_obj].obj_class_prob = 1;
#else

				/* Old class attenuation */
				for (i_class = 0; i_class < TRK_SENSOR_FUSION_CLASS_TYPE_MAX; i_class++)
				{
					gTrackData[i_obj].obj_class_cnt[i_class] *= TRK_SENSOR_FUSION_CLASS_OLD_DATA_ATTENUATION_FACTOR;
				}

				gTrackData[i_obj].obj_class_cnt[vision_obj_class]++;

				cnt_max = 0;
				cnt_all = 0;
				for (i_class = 0; i_class < TRK_SENSOR_FUSION_CLASS_TYPE_MAX; i_class++)
				{
					if (gTrackData[i_obj].obj_class_cnt[i_class] > cnt_max)
					{
						cnt_max = gTrackData[i_obj].obj_class_cnt[i_class];
						cnt_all += cnt_max;
						gTrackData[i_obj].obj_class = i_class;
					}
				}

				if (cnt_all != 0)
				{
					gTrackData[i_obj].obj_class_prob = (float32_t)cnt_max / cnt_all;
				}
			}
		}
#endif
	}
#endif
}



/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/



static float32_t Trk_vCalc1dAreaOverlapRatio(Distribution_t range1, Distribution_t range2)
{
	Distribution_t overall;
	Distribution_t overlap;
	float32_t overlap_ratio;

	overlap.f32Min = _trk_max(range1.f32Min, range2.f32Min);
	overlap.f32Max = _trk_min(range1.f32Max, range2.f32Max);

	if (overlap.f32Min > overlap.f32Max)
	{
		return 0.0f;
	}

	overall.f32Max = _trk_max(range1.f32Max, range2.f32Max);
	overall.f32Min = _trk_min(range1.f32Min, range2.f32Min);

	overlap_ratio = (overlap.f32Max - overlap.f32Min) / (overall.f32Max - overall.f32Min);

	return overlap_ratio;
}


/* Calculate the Intersection over Union(IoU) of two bounding boxes. */
static float32_t Trk_vCalc2dAreaOverlapRatio(BoundingBox_t bbox1, BoundingBox_t bbox2)
{
	float32_t x_left;
	float32_t x_right;
	float32_t y_top;
	float32_t y_bottom;
	float32_t intersection_area;
	float32_t iou;

	x_left = _trk_max(bbox1.x, bbox2.x);
	y_top = _trk_max(bbox1.y, bbox2.y);
	x_right = _trk_min(bbox1.x + bbox1.w - 1, bbox2.x + bbox2.w - 1);
	y_bottom = _trk_min(bbox1.y + bbox1.h - 1, bbox2.y + bbox2.h - 1);

	if ((x_right < x_left) || (y_bottom < y_top))
	{
		return 0.0;
	}

	/* The intersection of two axis - aligned bounding boxes is always an axis - aligned bounding box */
	intersection_area = (x_right - x_left) * (y_bottom - y_top);

	/* Compute the intersection over union by taking the intersection area and dividing it by the sum of prediction + ground-truth areas - the interesection area */
	iou = intersection_area / ((bbox1.w * bbox1.h) + (bbox2.w * bbox2.h) - intersection_area + TRK_APPROXIMATE_ZERO);

	return iou;


}
