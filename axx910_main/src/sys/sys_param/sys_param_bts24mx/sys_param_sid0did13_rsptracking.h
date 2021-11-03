/******************************************************************/
/* SID:0x00, DID:13  rsp traking (rsp.trk) setup   */
/******************************************************************/
/*.sid0did11_certification_config =*/
{
    /*.sid =*/0,
    /*.did =*/13,
    /*.setup =*/
    {
        /*.posttune =*/
        {
            /*.LongGate1=*/8.0f,
            /*.LongGate2=*/14.0f,
            /*.LongGate3=*/14.0f,
            /*.LongGateByVel_Gain=*/6.0f,
            /*.MotorCycle_PowTh=*/22.0f,
            /*.MotorCycle_PowTh2=*/20.0f,
            /*.MotorCycleByRange_Gain=*/14.0f,
            /*.TrackOutFilter=*/1, //jsint32_t TrackOutFilter; // 0:New + Verified, 1: Verified only, 2: All
            /*.tbd8=*/0.0f,
            /*.tbd9=*/0.0f,
            /*.tbd10=*/0.0f,
            /*.tbd11=*/0.0f,
            /*.tbd12=*/0.0f,
            /*.tbd13=*/0.0f,
            /*.tbd14=*/0.0f,
            /*.tbd15=*/0.0f,
        },
		/*.trktune = */
		{
			/*.s16Pt_New2Vrf=*/7,		// 7
			/*.s16Pt_Max=*/30,			// 30
			/*.s16Pt_New_Upd=*/2,		// 2
			/*.s16Pt_New_Coast=*/1,	// 1
			/*.s16Pt_Vrf_Upd=*/4,		// 4
			/*.s16Pt_Vrf_Coast=*/1,	// 1
			/*.f32Pt_NearRange=*/20.0f,
			/*.s16Pt_Vrf_Upd_Near=*/4,	// 4
			/*.s16Pt_Vrf_Coast_Near=*/1,	// 1
			/*.f32R_GateByEle_W=*/0.0f,
			/*.f32V_GateByEle_W=*/0.0f,
		},
    },
},



