/**************************************************************************************
-------------------------------------   include   -------------------------------------
**************************************************************************************/
#include "Trk_Main.h"
#include "Trk_Clustering.h"

/**************************************************************************************
-------------------------------------   define   --------------------------------------
**************************************************************************************/


/**************************************************************************************
* ------------------------------   global variables   ------------------------------- *
**************************************************************************************/
DbscanParam_t dbscan_param[TRK_CLST_DBSCAN_NUM_REGION];

/**************************************************************************************
* -----------------------------   function prototypes   ----------------------------- *
**************************************************************************************/
static void Clst_vDbscanParamInit(void);
static void Clst_vMeasClstInit(void);
static void Clst_vDBSCAN_Regional(void);
static int16_t Clst_vDBSCAN(int16_t cluster_idx, DbscanParam_t param);
static void Clst_vExtractClstProperties(void);
static void Clst_vRegionQuery(int16_t i_meas, int16_t *neighbor_cnt, int16_t *neighbor, DbscanParam_t param);
static void Clst_vExpandCluster(int16_t i_meas, int16_t cluster_idx, int16_t *neighbor_cnt, int16_t *neighbor, DbscanParam_t param);
static float32_t Clst_vCalcDist(int16_t idx_1, int16_t idx_2);


/**************************************************************************************
* ------------------------------   global functions   ------------------------------- *
**************************************************************************************/
void Clst_vMeasClustering(void)
{
	Clst_vDbscanParamInit();
    Clst_vMeasClstInit();

    Clst_vDBSCAN_Regional();

    Clst_vExtractClstProperties();

}


/**************************************************************************************
* ------------------------------   static functions   ------------------------------- *
**************************************************************************************/
void Clst_vDbscanParamInit(void)
{
	if (TRK_CLST_DBSCAN_NUM_REGION > 0)
	{
		dbscan_param[0].region_idx			= 0;
		dbscan_param[0].range_min			= TRK_CLST_DBSCAN_RANGE_MIN_REGION_0;
		dbscan_param[0].range_max			= TRK_CLST_DBSCAN_RANGE_MAX_REGION_0;
		dbscan_param[0].dbscan_eps			= TRK_CLST_DBSCAN_EPS_0;
		dbscan_param[0].dbscan_min_pts		= TRK_CLST_DBSCAN_MINPTS_0;
		dbscan_param[0].max_diff_rangerate	= TRK_CLST_MAX_DIFF_RANGERATE_0;
		dbscan_param[0].max_num_neighbor	= TRK_CLST_NUM_NEIGHBOR_MAX_0;
	}

	if (TRK_CLST_DBSCAN_NUM_REGION > 1)
	{
		dbscan_param[1].region_idx			= 1;
		dbscan_param[1].range_min			= TRK_CLST_DBSCAN_RANGE_MIN_REGION_1;
		dbscan_param[1].range_max			= TRK_CLST_DBSCAN_RANGE_MAX_REGION_1;
		dbscan_param[1].dbscan_eps			= TRK_CLST_DBSCAN_EPS_1;
		dbscan_param[1].dbscan_min_pts		= TRK_CLST_DBSCAN_MINPTS_1;
		dbscan_param[1].max_diff_rangerate	= TRK_CLST_MAX_DIFF_RANGERATE_1;
		dbscan_param[1].max_num_neighbor	= TRK_CLST_NUM_NEIGHBOR_MAX_1;
	}

	if (TRK_CLST_DBSCAN_NUM_REGION > 2)
	{
		dbscan_param[2].region_idx			= 2;
		dbscan_param[2].range_min			= TRK_CLST_DBSCAN_RANGE_MIN_REGION_2;
		dbscan_param[2].range_max			= TRK_CLST_DBSCAN_RANGE_MAX_REGION_2;
		dbscan_param[2].dbscan_eps			= TRK_CLST_DBSCAN_EPS_2;
		dbscan_param[2].dbscan_min_pts		= TRK_CLST_DBSCAN_MINPTS_2;
		dbscan_param[2].max_diff_rangerate	= TRK_CLST_MAX_DIFF_RANGERATE_2;
		dbscan_param[2].max_num_neighbor	= TRK_CLST_NUM_NEIGHBOR_MAX_2;
	}
}

void Clst_vMeasClstInit(void)
{
    int16_t i_clst, i_meas;

    gMsclCnt = 0;

    for (i_clst = 0; i_clst < TRK_NUM_CLUSTER_MAX; i_clst++)
    {
        gMeasClst[i_clst].s16Idx          = -1;
        gMeasClst[i_clst].State           = INVALID_CLST;
        gMeasClst[i_clst].MovState        = STATIONARY;
        gMeasClst[i_clst].s16AssoClstIdx  = -1;
        gMeasClst[i_clst].f32AssoClstCost = TRK_INIT_ASSO_COST;

        for (i_meas = 0; i_meas < TRK_CLST_NUM_NEIGHBOR_MAX; i_meas++)
        {
            gMeasClst[i_clst].MeasIdx[i_meas] = -1;
            gMeasClst[i_clst].CoreIdx[i_meas] = -1;
        }
        gMeasClst[i_clst].MeasNum = 0;
        gMeasClst[i_clst].CoreNum = 0;
        
        /* init distribution */
        gMeasClst[i_clst].Xpos.f32Mean			= 0.0f;
        gMeasClst[i_clst].Xpos.f32StdDev		= 0.0f;
        gMeasClst[i_clst].Xpos.f32Min			= 0.0f;
        gMeasClst[i_clst].Xpos.f32Max			= 0.0f;

        gMeasClst[i_clst].Ypos.f32Mean			= 0.0f;
        gMeasClst[i_clst].Ypos.f32StdDev		= 0.0f;
        gMeasClst[i_clst].Ypos.f32Min			= 0.0f;
        gMeasClst[i_clst].Ypos.f32Max			= 0.0f;

        gMeasClst[i_clst].Range.f32Mean			= 0.0f;
        gMeasClst[i_clst].Range.f32StdDev		= 0.0f;
        gMeasClst[i_clst].Range.f32Min			= 0.0f;
        gMeasClst[i_clst].Range.f32Max			= 0.0f;

        gMeasClst[i_clst].RangeRate.f32Mean		= 0.0f;
        gMeasClst[i_clst].RangeRate.f32StdDev	= 0.0f;
        gMeasClst[i_clst].RangeRate.f32Min		= 0.0f;
        gMeasClst[i_clst].RangeRate.f32Max		= 0.0f;

        gMeasClst[i_clst].AziAng.f32Mean		= 0.0f;
        gMeasClst[i_clst].AziAng.f32StdDev		= 0.0f;
        gMeasClst[i_clst].AziAng.f32Min			= 0.0f;
        gMeasClst[i_clst].AziAng.f32Max			= 0.0f;

        gMeasClst[i_clst].EleAng.f32Mean		= 0.0f;
        gMeasClst[i_clst].EleAng.f32StdDev		= 0.0f;
        gMeasClst[i_clst].EleAng.f32Min			= 0.0f;
        gMeasClst[i_clst].EleAng.f32Max			= 0.0f;

        gMeasClst[i_clst].Power.f32Mean			= 0.0f;
        gMeasClst[i_clst].Power.f32StdDev		= 0.0f;
        gMeasClst[i_clst].Power.f32Min			= 0.0f;
        gMeasClst[i_clst].Power.f32Max			= 0.0f;

		/* Wheel detection */
		gMeasClst[i_clst].ReflectType			= REFLECT_TYPE_UNKNOWN;

		/* vision object matching */
		gMeasClst[i_clst].MatchVisionObjIdx		= -1;
		gMeasClst[i_clst].AzimuthOverlapRatio	= 0.0f;
    }

}


void Clst_vDBSCAN_Regional(void)
{
	int16_t cluster_idx;
	int16_t region_idx;

	cluster_idx = -1;
	for (region_idx = 0; region_idx < TRK_CLST_DBSCAN_NUM_REGION; region_idx++)
	{
		cluster_idx = Clst_vDBSCAN(cluster_idx, dbscan_param[region_idx]);
	}

}


int16_t Clst_vDBSCAN(int16_t cluster_idx, DbscanParam_t param)
{
	int16_t region_idx, i_meas, j_meas;
	int16_t i_n;
	int16_t neighbor_cnt;
	int16_t neighbor[TRK_CLST_NUM_NEIGHBOR_MAX];

	for (i_meas = 0; i_meas < gMeasCnt; i_meas++)
	{
		if ((gMeasData[i_meas].u8Cluster_visited == 0)
			&& _trk_isbound(gMeasData[i_meas].f32Range_rdr, param.range_min, param.range_max)
			)
		{
			/* initialize */
			gMeasData[i_meas].u8Cluster_visited = 1;
			neighbor_cnt = 0;
			for (i_n = 0; i_n < param.max_num_neighbor; i_n++)
			{
				neighbor[i_n] = -1;
			}

			/* find neighbor */
			Clst_vRegionQuery(i_meas, &neighbor_cnt, neighbor, param);

			if (neighbor_cnt < param.dbscan_min_pts)
			{
				gMeasData[i_meas].Cluster_PtsStat = NOISE_PTS;
				gMeasData[i_meas].s16Cluster_idx = -1;
			}
			else
			{
				cluster_idx++;
				if (TRK_NUM_CLUSTER_MAX <= cluster_idx)
				{
					break;
				}

				gMeasData[i_meas].Cluster_PtsStat = CORE_PTS;
				gMeasData[i_meas].s16Cluster_idx = cluster_idx;
				Clst_vExpandCluster(i_meas, cluster_idx, &neighbor_cnt, neighbor, param);

				/* Allocate cluster data */
				gMeasClst[cluster_idx].s16Idx = cluster_idx;
				gMeasClst[cluster_idx].State = VALID_CLST;
				gMeasClst[cluster_idx].MeasNum = neighbor_cnt;

				for (j_meas = 0; j_meas < neighbor_cnt; j_meas++)
				{
					gMeasClst[cluster_idx].MovState = gMeasData[neighbor[j_meas]].MovState;

					if (gMeasClst[cluster_idx].MovState == STATIONARY)
						break;
				}

				for (j_meas = 0; j_meas < neighbor_cnt; j_meas++)
				{
					gMeasClst[cluster_idx].MeasIdx[j_meas] = neighbor[j_meas];

					if (gMeasData[neighbor[j_meas]].Cluster_PtsStat == CORE_PTS)
					{
						gMeasClst[cluster_idx].CoreIdx[gMeasClst[cluster_idx].CoreNum] = neighbor[j_meas];
						gMeasClst[cluster_idx].CoreNum++;
					}
				}
			}
		}
	}

	gMsclCnt = (TRK_NUM_CLUSTER_MAX <= cluster_idx) ? TRK_NUM_CLUSTER_MAX : (cluster_idx + 1);
}


void Clst_vRegionQuery(int16_t i_meas, int16_t *neighbor_cnt, int16_t *neighbor, DbscanParam_t param)
{
    int16_t i_n;
    int16_t n_cnt;
    float32_t dist;
    float32_t diff_rangerate;
	float32_t range_min;
	float32_t range_max;

	range_min = param.range_min - TRK_CLST_DBSCAN_NEIGHBOR_RANGE_MARGIN;
	range_max = param.range_max + TRK_CLST_DBSCAN_NEIGHBOR_RANGE_MARGIN;

    n_cnt = 0;
    for (i_n = 0; i_n < gMeasCnt; i_n++)
    {
		if (_trk_isbound(gMeasData[i_meas].f32Range_rdr, range_min, range_max))
		{
			dist            = Clst_vCalcDist(i_meas, i_n);
			diff_rangerate  = _sp_abs(gMeasData[i_meas].f32RangeRate_comp - gMeasData[i_n].f32RangeRate_comp);

			if ((dist < param.dbscan_eps) && (diff_rangerate < param.max_diff_rangerate))
			{
				neighbor[n_cnt] = i_n;
				n_cnt = (n_cnt < param.max_num_neighbor)? (n_cnt + 1): param.max_num_neighbor;

				/* error exception */
				if (param.max_num_neighbor <= n_cnt)
				{
					break;
				}
			}
			}
    }

    /* out */
    *neighbor_cnt = n_cnt;  

}


float32_t Clst_vCalcDist(int16_t idx_1, int16_t idx_2)
{
    float32_t pts1_posx, pts1_posy;
    float32_t pts2_posx, pts2_posy;
    float32_t euc_dist;

    pts1_posx = gMeasData[idx_1].f32PosX;
    pts1_posy = gMeasData[idx_1].f32PosY;
    pts2_posx = gMeasData[idx_2].f32PosX;
    pts2_posy = gMeasData[idx_2].f32PosY;

    euc_dist = _sp_hypotf((pts1_posx - pts2_posx), (pts1_posy - pts2_posy));
    
    return euc_dist;

}


void Clst_vExpandCluster(int16_t i_meas, int16_t cluster_idx, int16_t *neighbor_cnt, int16_t *neighbor, DbscanParam_t param)
{
    int16_t i_n, i_nn, i_tmp;
    int16_t k_n;
    int16_t n_idx;
    int16_t n_cnt;
    int16_t n_neighbor[TRK_CLST_NUM_NEIGHBOR_MAX];
    int16_t n_neighbor_cnt;

    n_cnt = *neighbor_cnt;
    k_n = 0;

    while(1)
    {
        n_idx = neighbor[k_n];

        if(gMeasData[n_idx].u8Cluster_visited == 0)
        {
            gMeasData[n_idx].u8Cluster_visited = 1;

			n_neighbor_cnt = 0;
			for (i_nn = 0; i_nn < param.max_num_neighbor; i_nn++)
			{
				n_neighbor[i_nn] = -1;
			}
            Clst_vRegionQuery(n_idx, &n_neighbor_cnt, n_neighbor, param);
            
            if(param.dbscan_min_pts <= n_neighbor_cnt)
            {
                gMeasData[n_idx].Cluster_PtsStat = CORE_PTS;
                gMeasData[n_idx].s16Cluster_idx  = cluster_idx;
                
                for(i_nn = 0; i_nn < n_neighbor_cnt; i_nn++)
                {
                    i_tmp = i_nn + n_cnt;
					if (i_tmp < param.max_num_neighbor)
                    {
						if (gMeasData[n_neighbor[i_nn]].s16Cluster_idx == -1)
						{
							neighbor[n_cnt] = n_neighbor[i_nn];
							n_cnt++;
						}
                    }
                    else
                    {
                        break;
                    }
                }

                *neighbor_cnt = n_cnt;
            }
        }
        
        if (n_cnt < param.max_num_neighbor)
        {
            for (i_n = 0; i_n < n_cnt; i_n++)
            {
                i_tmp = neighbor[i_n];

                if(gMeasData[i_tmp].s16Cluster_idx == -1)
                {
                    gMeasData[i_tmp].Cluster_PtsStat   = BORDER_PTS;
                    gMeasData[i_tmp].s16Cluster_idx    = cluster_idx;   
                }
            }
        }
        else
        {
            break;
        }

        /* break condition for while(1)*/
		k_n++;
        if ((n_cnt <= k_n) || (param.max_num_neighbor <= k_n))
        {
            break;
        }
    }

}


void Clst_vExtractClstProperties(void)
{
    int16_t i_meas, i_mscl;
	int16_t reflect_type;
	float32_t reflect_type_voting;
    float32_t posx_sum, posy_sum, range_sum, rangerate_sum, rangerate_rdr_sum, azi_sum, ele_sum, pow_sum;
	float32_t posx_diff, posy_diff, posxy_diffsum;
    float32_t posx_diffsum, posy_diffsum, range_diffsum, rangerate_diffsum, rangerate_rdr_diffsum, azi_diffsum, ele_diffsum, pow_diffsum;
    float32_t min_posx, max_posx;
    float32_t min_posy, max_posy;
    float32_t min_range, max_range;
    float32_t min_rangerate, max_rangerate;
	float32_t min_rangerate_rdr, max_rangerate_rdr;
    float32_t min_aziang, max_aziang;
    float32_t min_eleang, max_eleang;
    float32_t min_power, max_power;
	

    /* Calculate represent values */
    for (i_mscl = 0; i_mscl < gMsclCnt; i_mscl++)
    {
        /* Calculate average & minimum range */
        posx_sum			= 0.0f;
        posy_sum			= 0.0f;
        range_sum			= 0.0f;
        rangerate_sum		= 0.0f;
		rangerate_rdr_sum	= 0.0f;
        azi_sum				= 0.0f;
        ele_sum				= 0.0f;
        pow_sum				= 0.0f;

        min_posx			= 1000.0f;
        max_posx			= 0.0f;
        min_posy			= 1000.0f;
        max_posy			= 0.0f;
        min_range			= 1000.0f;
        max_range			= 0.0f;
		min_rangerate		= 1000.0f;
		max_rangerate		= -1000.0f;
		min_rangerate_rdr	= 1000.0f;
		max_rangerate_rdr	= -1000.0f;
        min_aziang			= 180.0;
        max_aziang			= -180.0f;
        min_eleang			= 180.0f;
        max_eleang			= -180.0f;
        min_power			= 1000.0f;
        max_power			= 0.0f;

        for (i_meas = 0; i_meas < gMeasClst[i_mscl].MeasNum; i_meas++)
        {
            posx_sum			+= gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32PosX;
            posy_sum			+= gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32PosY;
            range_sum			+= gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32Range_rdr;
            rangerate_sum		+= gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32RangeRate_comp;
			rangerate_rdr_sum	+= gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32RangeRate_rdr;
            azi_sum				+= gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32AziAng;
            ele_sum				+= gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32EleAng;
            pow_sum				+= gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32Pow_dB;
            
            max_posx			= (gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32PosX > max_posx)? gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32PosX : max_posx;
            min_posx			= (gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32PosX < min_posx)? gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32PosX : min_posx;
            max_posy			= (gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32PosY > max_posy)? gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32PosY : max_posy;
            min_posy			= (gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32PosY < min_posy)? gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32PosY : min_posy;
            max_range			= (gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32Range_rdr > max_range)? gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32Range_rdr : max_range;
            min_range			= (gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32Range_rdr < min_range)? gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32Range_rdr : min_range;
            max_rangerate		= (gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32RangeRate_comp > max_rangerate)? gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32RangeRate_comp : max_rangerate;
            min_rangerate		= (gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32RangeRate_comp < min_rangerate)? gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32RangeRate_comp : min_rangerate;
			max_rangerate_rdr	= (gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32RangeRate_rdr > max_rangerate_rdr) ? gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32RangeRate_rdr : max_rangerate_rdr;
			min_rangerate_rdr	= (gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32RangeRate_rdr < min_rangerate_rdr) ? gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32RangeRate_rdr : min_rangerate_rdr;
            max_aziang			= (gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32AziAng > max_aziang)? gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32AziAng : max_aziang;
            min_aziang			= (gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32AziAng < min_aziang)? gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32AziAng : min_aziang;
            max_eleang			= (gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32EleAng > max_eleang)? gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32EleAng : max_eleang;
            min_eleang			= (gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32EleAng < min_eleang)? gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32EleAng : min_eleang;
            max_power			= (gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32Pow_dB > max_power)? gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32Pow_dB : max_power;
            min_power			= (gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32Pow_dB < min_power)? gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32Pow_dB : min_power;
        }
        gMeasClst[i_mscl].Xpos.f32Mean			= posx_sum / gMeasClst[i_mscl].MeasNum;
        gMeasClst[i_mscl].Ypos.f32Mean			= posy_sum / gMeasClst[i_mscl].MeasNum;
        gMeasClst[i_mscl].Range.f32Mean			= range_sum / gMeasClst[i_mscl].MeasNum;
        gMeasClst[i_mscl].RangeRate.f32Mean		= rangerate_sum / gMeasClst[i_mscl].MeasNum;
		gMeasClst[i_mscl].RangeRate_rdr.f32Mean = rangerate_rdr_sum / gMeasClst[i_mscl].MeasNum;
        gMeasClst[i_mscl].AziAng.f32Mean		= azi_sum / gMeasClst[i_mscl].MeasNum;
        gMeasClst[i_mscl].EleAng.f32Mean		= ele_sum / gMeasClst[i_mscl].MeasNum;
        gMeasClst[i_mscl].Power.f32Mean			= pow_sum / gMeasClst[i_mscl].MeasNum;
        
        gMeasClst[i_mscl].Xpos.f32Max			= max_posx;
        gMeasClst[i_mscl].Xpos.f32Min			= min_posx;
        gMeasClst[i_mscl].Ypos.f32Max			= max_posy;
        gMeasClst[i_mscl].Ypos.f32Min			= min_posy;
        gMeasClst[i_mscl].Range.f32Max			= max_range;
        gMeasClst[i_mscl].Range.f32Min			= min_range;
        gMeasClst[i_mscl].RangeRate.f32Max		= max_rangerate;
        gMeasClst[i_mscl].RangeRate.f32Min		= min_rangerate;
		gMeasClst[i_mscl].RangeRate_rdr.f32Max	= max_rangerate_rdr;
		gMeasClst[i_mscl].RangeRate_rdr.f32Min	= min_rangerate_rdr;
        gMeasClst[i_mscl].AziAng.f32Max			= max_aziang;
        gMeasClst[i_mscl].AziAng.f32Min			= min_aziang;
        gMeasClst[i_mscl].EleAng.f32Max			= max_eleang;
        gMeasClst[i_mscl].EleAng.f32Min			= min_eleang;
        gMeasClst[i_mscl].Power.f32Max			= max_power;
        gMeasClst[i_mscl].Power.f32Min			= min_power;

        /* Calculate variance */
		posxy_diffsum			= 0.0f;
        posx_diffsum			= 0.0f;
        posy_diffsum			= 0.0f;
        range_diffsum			= 0.0f;
        rangerate_diffsum		= 0.0f;
		rangerate_rdr_diffsum	= 0.0f;
        azi_diffsum				= 0.0f;
        ele_diffsum				= 0.0f;
        pow_diffsum				= 0.0f;

        for (i_meas = 0; i_meas < gMeasClst[i_mscl].MeasNum; i_meas++)
        {
			posx_diff				= gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32PosX - gMeasClst[i_mscl].Xpos.f32Mean;
			posy_diff				= gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32PosY - gMeasClst[i_mscl].Ypos.f32Mean;
			posxy_diffsum			+= posx_diff * posy_diff;
            posx_diffsum			+= _sp_pow2(posx_diff);
            posy_diffsum			+= _sp_pow2(posy_diff);
            range_diffsum			+= _sp_pow2(gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32Range_rdr - gMeasClst[i_mscl].Range.f32Mean);
            rangerate_diffsum		+= _sp_pow2(gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32RangeRate_comp - gMeasClst[i_mscl].RangeRate.f32Mean);
			rangerate_rdr_diffsum	+= _sp_pow2(gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32RangeRate_rdr - gMeasClst[i_mscl].RangeRate_rdr.f32Mean);
            azi_diffsum				+= _sp_pow2(gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32AziAng - gMeasClst[i_mscl].AziAng.f32Mean);
            ele_diffsum				+= _sp_pow2(gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32EleAng - gMeasClst[i_mscl].EleAng.f32Mean);
            pow_diffsum				+= _sp_pow2(gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].f32Pow_dB - gMeasClst[i_mscl].Power.f32Mean);
        }
        gMeasClst[i_mscl].Xpos.f32StdDev			= _sp_sqrtf(posx_diffsum / gMeasClst[i_mscl].MeasNum);
        gMeasClst[i_mscl].Ypos.f32StdDev			= _sp_sqrtf(posy_diffsum / gMeasClst[i_mscl].MeasNum);
        gMeasClst[i_mscl].Range.f32StdDev			= _sp_sqrtf(range_diffsum / gMeasClst[i_mscl].MeasNum);
        gMeasClst[i_mscl].RangeRate.f32StdDev		= _sp_sqrtf(rangerate_diffsum / gMeasClst[i_mscl].MeasNum);
		gMeasClst[i_mscl].RangeRate_rdr.f32StdDev	= _sp_sqrtf(rangerate_rdr_diffsum / gMeasClst[i_mscl].MeasNum);
        gMeasClst[i_mscl].AziAng.f32StdDev			= _sp_sqrtf(azi_diffsum / gMeasClst[i_mscl].MeasNum);
        gMeasClst[i_mscl].EleAng.f32StdDev			= _sp_sqrtf(ele_diffsum / gMeasClst[i_mscl].MeasNum);
        gMeasClst[i_mscl].Power.f32StdDev			= _sp_sqrtf(pow_diffsum / gMeasClst[i_mscl].MeasNum);
        if (posx_diffsum < TRK_APPROXIMATE_ZERO)
        {
            gMeasClst[i_mscl].RotationAngle = (posxy_diffsum > 0.0f) ?  90.0f : -90.0f;
        }
        else
        {
            gMeasClst[i_mscl].RotationAngle = _trk_atandf(posxy_diffsum / posx_diffsum);
        }
	    
		i_meas = 0;
		while ((i_meas < gMeasClst[i_mscl].MeasNum) && gMeasClst[i_mscl].MovState == STATIONARY)
		{
			gMeasClst[i_mscl].MovState = gMeasData[gMeasClst[i_mscl].MeasIdx[i_meas]].MovState;
			i_meas++;
		}
    }

}