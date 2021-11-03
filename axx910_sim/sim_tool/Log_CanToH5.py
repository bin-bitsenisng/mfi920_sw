import numpy as np



class CanToH5:
    def __init__(self, **opts):

        self.opts = {
            'RadarType': 'MRR, SRR',
        }
        self.opts.update(opts)

        self.VehInfo = []
        self.ObjInfo = []
        self.TrkInfo = []
        self.PeakCnt = []
        self.PeakData = []
        self.CurrentPRF = []
        self.RadarScanIdx = []
        self.SampleNumber = []
        self.CycleTime = []
        self.CalData = []
        self.FRWInfo = []

        if opts['RadarType'] == 'MRR':
            self.convert = self.MRR_Convert
        elif opts['RadarType'] == 'SRR':
            self.convert = self.SRR_Convert
        else:
            pass


    def MRR_Convert(self, CanID, CanData, h5grp):
        import Log_Packet_MRR as Pack

        SpInfo_ID = 0x001
        Object_ID = 0x100
        Track_ID = 0x200
        PeakIdx_ID = 0x300
        PeakFFT_ID = 0x320
        FRW_ID = 0x400
        CalFFT_ID = 0x600

        NumObjSig = 8
        NumTrkSig = 4
        NumPeakSig = 2

        Num_Object = 64
        Num_Track = 16
        NumPeak = 64

        VehInfoSize = 4
        ObjInfoSize = (Num_Object, 20)
        TrkInfoSize = (Num_Track, 20)
        PeakDataSize = (NumPeak, 20)
        CalDataSize = 16
        FRWInfoSize = 8


        self.VehInfo = np.zeros(VehInfoSize)
        self.ObjInfo = np.zeros(ObjInfoSize)
        self.TrkInfo = np.zeros(TrkInfoSize)
        self.PeakCnt = 0
        self.PeakData = np.zeros(PeakDataSize)
        self.CurrentPRF = 0
        self.RadarScanIdx = 0
        self.SampleNumber = 0
        self.CycleTime = 0
        self.CalData = np.zeros(CalDataSize)
        self.FRWInfo = np.zeros(FRWInfoSize)

        SpInfo = Pack.SpInfo_Packet()
        Object = Pack.Object_Packet()
        Track = Pack.Track_Packet()
        PeakIdx = Pack.PeakIndex_Packet()
        FFTData = Pack.FFTData_Packet()
        CalFFTData = Pack.FFTData_Packet()
        FRWInfo = Pack.FRW_Packet()


        for idx in range(0, len(CanID)):
            ID = CanID[idx]
            RxBuff = CanData[idx]

            if ID == SpInfo_ID:
                SpInfo.dword[0] = RxBuff
                SpInfo.dword[1] = RxBuff >> (64)
                SpInfo.dword[2] = RxBuff >> (64*2)
                SpInfo.dword[3] = RxBuff >> (64*3)

                self.CurrentPRF = SpInfo.bits.CurrentPRF
                self.RadarScanIdx = 0
                self.SampleNumber = SpInfo.bits.SMPLNum
                self.CycleTime = SpInfo.bits.CycleTime

                self.PeakCnt = SpInfo.bits.PeakCnt

                self.VehInfo[0] = SpInfo.bits.VehicleSpeed
                self.VehInfo[1] = SpInfo.bits.YawRate
                self.VehInfo[2] = 0
                self.VehInfo[3] = SpInfo.bits.PathRadius

            if Object_ID <= ID < (Object_ID + (Num_Object / NumObjSig)):
                for idx in range(NumObjSig):
                    obj_idx = ((ID - Object_ID) * NumObjSig) + idx
                    Object.dword = RxBuff >> (64 * idx)

                    self.ObjInfo[obj_idx][0] = Object.bits.Range
                    self.ObjInfo[obj_idx][1] = Object.bits.Velocity
                    self.ObjInfo[obj_idx][2] = Object.bits.AziAng
                    self.ObjInfo[obj_idx][3] = Object.bits.EleAng
                    self.ObjInfo[obj_idx][4] = Object.bits.Power
                    self.ObjInfo[obj_idx][5] = 0
                    self.ObjInfo[obj_idx][6] = Object.bits.ModType
                    self.ObjInfo[obj_idx][7] = 0
                    self.ObjInfo[obj_idx][8] = 0
                    self.ObjInfo[obj_idx][9] = obj_idx
                    self.ObjInfo[obj_idx][10] = 0
                    self.ObjInfo[obj_idx][11] = -1

            if Track_ID <= ID < (Track_ID + (Num_Track / NumTrkSig)):
                for idx in range(NumTrkSig):
                    trk_idx = ((ID - Track_ID) * NumTrkSig) + idx
                    Track.dword[0] = RxBuff >> (64 * (2*idx))
                    Track.dword[1] = RxBuff >> (64 * (2*idx+1))

                    self.TrkInfo[trk_idx][0] = Track.bits.Status
                    self.TrkInfo[trk_idx][1] = Track.bits.UpdState
                    self.TrkInfo[trk_idx][2] = Track.bits.MoveStatus
                    self.TrkInfo[trk_idx][3] = Track.bits.PosX
                    self.TrkInfo[trk_idx][4] = Track.bits.PosY
                    self.TrkInfo[trk_idx][5] = Track.bits.VelX
                    self.TrkInfo[trk_idx][6] = Track.bits.VelY
                    self.TrkInfo[trk_idx][7] = Track.bits.Power
                    self.TrkInfo[trk_idx][8] = Track.bits.HeadingAngle
                    self.TrkInfo[trk_idx][9] = Track.bits.AliveAge
                    self.TrkInfo[trk_idx][10] = Track.bits.Width
                    self.TrkInfo[trk_idx][11] = Track.bits.Length


            if PeakIdx_ID <= ID < (PeakIdx_ID + (NumPeak / 8)):
                for idx in range(8):
                    peak_idx = ((ID - PeakIdx_ID) * 8) + idx
                    PeakIdx.dword = RxBuff >> (64 * idx)

                    self.PeakData[peak_idx][0] = PeakIdx.bits.FreqIndex_R
                    self.PeakData[peak_idx][1] = PeakIdx.bits.FreqIndex_D
                    self.PeakData[peak_idx][2] = PeakIdx.bits.EstFreqIdx_R
                    self.PeakData[peak_idx][3] = PeakIdx.bits.EstFreqIdx_D

            if PeakFFT_ID <= ID < (PeakFFT_ID + (NumPeak / NumPeakSig)):
                for idx in range(NumPeakSig):
                    peak_idx = ((ID - PeakFFT_ID) * NumPeakSig) + idx
                    FFTData.dword[0] = RxBuff >> (64 * (4*idx))
                    FFTData.dword[1] = RxBuff >> (64 * (4*idx+1))
                    FFTData.dword[2] = RxBuff >> (64 * (4*idx+2))
                    FFTData.dword[3] = RxBuff >> (64 * (4*idx+3))

                    self.PeakData[peak_idx][4] = FFTData.bits.FFT_Tx1Ch0_real
                    self.PeakData[peak_idx][5] = FFTData.bits.FFT_Tx1Ch0_imag
                    self.PeakData[peak_idx][6] = FFTData.bits.FFT_Tx1Ch1_real
                    self.PeakData[peak_idx][7] = FFTData.bits.FFT_Tx1Ch1_imag
                    self.PeakData[peak_idx][8] = FFTData.bits.FFT_Tx1Ch2_real
                    self.PeakData[peak_idx][9] = FFTData.bits.FFT_Tx1Ch2_imag
                    self.PeakData[peak_idx][10] = FFTData.bits.FFT_Tx1Ch3_real
                    self.PeakData[peak_idx][11] = FFTData.bits.FFT_Tx1Ch3_imag

                    self.PeakData[peak_idx][12] = FFTData.bits.FFT_Tx2Ch0_real
                    self.PeakData[peak_idx][13] = FFTData.bits.FFT_Tx2Ch0_imag
                    self.PeakData[peak_idx][14] = FFTData.bits.FFT_Tx2Ch1_real
                    self.PeakData[peak_idx][15] = FFTData.bits.FFT_Tx2Ch1_imag
                    self.PeakData[peak_idx][16] = FFTData.bits.FFT_Tx2Ch2_real
                    self.PeakData[peak_idx][17] = FFTData.bits.FFT_Tx2Ch2_imag
                    self.PeakData[peak_idx][18] = FFTData.bits.FFT_Tx2Ch3_real
                    self.PeakData[peak_idx][19] = FFTData.bits.FFT_Tx2Ch3_imag

            if ID == CalFFT_ID:
                CalFFTData.dword[0] = RxBuff
                CalFFTData.dword[1] = RxBuff >> 64
                CalFFTData.dword[2] = RxBuff >> (64*2)
                CalFFTData.dword[3] = RxBuff >> (64*3)

                self.CalData[0] = CalFFTData.bits.FFT_Tx1Ch0_real
                self.CalData[1] = CalFFTData.bits.FFT_Tx1Ch0_imag
                self.CalData[2] = CalFFTData.bits.FFT_Tx1Ch1_real
                self.CalData[3] = CalFFTData.bits.FFT_Tx1Ch1_imag
                self.CalData[4] = CalFFTData.bits.FFT_Tx1Ch2_real
                self.CalData[5] = CalFFTData.bits.FFT_Tx1Ch2_imag
                self.CalData[6] = CalFFTData.bits.FFT_Tx1Ch3_real
                self.CalData[7] = CalFFTData.bits.FFT_Tx1Ch3_imag

                self.CalData[8] = CalFFTData.bits.FFT_Tx2Ch0_real
                self.CalData[9] = CalFFTData.bits.FFT_Tx2Ch0_imag
                self.CalData[10] = CalFFTData.bits.FFT_Tx2Ch1_real
                self.CalData[11] = CalFFTData.bits.FFT_Tx2Ch1_imag
                self.CalData[12] = CalFFTData.bits.FFT_Tx2Ch2_real
                self.CalData[13] = CalFFTData.bits.FFT_Tx2Ch2_imag
                self.CalData[14] = CalFFTData.bits.FFT_Tx2Ch3_real
                self.CalData[15] = CalFFTData.bits.FFT_Tx2Ch3_imag

            if ID == FRW_ID:
                FRWInfo.dword = RxBuff

                self.FRWInfo[0] = FRWInfo.bits.FCWLvl
                self.FRWInfo[1] = FRWInfo.bits.FVSA
                self.FRWInfo[2] = FRWInfo.bits.CIPV
                self.FRWInfo[3] = FRWInfo.bits.CIPS
                self.FRWInfo[4] = FRWInfo.bits.FVSAIdx
                self.FRWInfo[5] = FRWInfo.bits.PosX
                self.FRWInfo[6] = FRWInfo.bits.TTC
                self.FRWInfo[7] = 0

        if "Sim_TrkInfo" in h5grp:
            dset = h5grp["Sim_VehInfo"]
            dset[...] = self.VehInfo
            dset = h5grp["Sim_ObjInfo"]
            dset[...] = self.ObjInfo
            dset = h5grp["Sim_TrkInfo"]
            dset[...] = self.TrkInfo

            dset = h5grp["Sim_PeakCnt"]
            dset[...] = self.PeakCnt
            dset = h5grp["Sim_PeakData"]
            dset[...] = self.PeakData

            dset = h5grp["Sim_CurrentPRF"]
            dset[...] = self.CurrentPRF
            dset = h5grp["Sim_RadarScanIdx"]
            dset[...] = self.RadarScanIdx
            dset = h5grp["Sim_SampleNumber"]
            dset[...] = self.SampleNumber
            dset = h5grp["Sim_CycleTime"]
            dset[...] = self.CycleTime

            dset = h5grp["CalData_FFT"]
            dset[...] = self.CalData


        else:
            dset = h5grp.create_dataset("Sim_VehInfo", data=self.VehInfo, dtype='int16')
            dset = h5grp.create_dataset("Sim_ObjInfo", data=self.ObjInfo, dtype='int16')
            dset = h5grp.create_dataset("Sim_TrkInfo", data=self.TrkInfo, dtype='int16')

            dset = h5grp.create_dataset("Sim_PeakCnt", data=self.PeakCnt, dtype='int16')
            dset = h5grp.create_dataset("Sim_PeakData", data=self.PeakData, dtype='int16')

            dset = h5grp.create_dataset("Sim_CurrentPRF", data=self.CurrentPRF, dtype='int16')
            dset = h5grp.create_dataset("Sim_RadarScanIdx", data=self.RadarScanIdx, dtype='int16')
            dset = h5grp.create_dataset("Sim_SampleNumber", data=self.SampleNumber, dtype='uint16')
            dset = h5grp.create_dataset("Sim_CycleTime", data=self.CycleTime, dtype='int16')

            dset = h5grp.create_dataset("CalData_FFT", data=self.CalData, dtype='int16')



    def SRR_Convert(self, CanID, CanData, h5grp):
        import Log_Packet_SRR as Pack

        SpInfo_ID = 0x001
        Object_ID = 0x100
        Track_ID = 0x200
        LR_PeakIdx_ID = 0x300
        SR_PeakIdx_ID = 0x340
        LR_PeakFFT_ID = 0x380
        SR_PeakFFT_ID = 0x3C0
        LR_CalFFT_ID = 0x600
        SR_CalFFT_ID = 0x601

        NumObjSig = 8
        NumTrkSig = 4
        NumPeakSig_LR = 2
        NumPeakSig_SR = 4

        Num_Object = 96
        Num_Track = 32
        NumPeak_LR = 64
        NumPeak_SR = 64


        VehInfoSize = 4
        ObjInfoSize = (Num_Object, 20)
        TrkInfoSize = (Num_Track, 20)
        LR_PeakDataSize = (NumPeak_LR, 20)
        SR_PeakDataSize = (NumPeak_SR, 20)
        LR_CalDataSize = 16
        SR_CalDataSize = 16

        self.VehInfo = np.zeros(VehInfoSize)
        self.ObjInfo = np.zeros(ObjInfoSize)
        self.TrkInfo = np.zeros(TrkInfoSize)
        self.LR_PeakCnt = 0
        self.SR_PeakCnt = 0
        self.LR_PeakData = np.zeros(LR_PeakDataSize)
        self.SR_PeakData = np.zeros(SR_PeakDataSize)
        self.CurrentPRF = 0
        self.RadarScanIdx = 0
        self.SampleNumber = 0
        self.CycleTime = 0
        self.LR_CalData = np.zeros(LR_CalDataSize)
        self.SR_CalData = np.zeros(SR_CalDataSize)

        SpInfo = Pack.SpInfo_Packet()
        Object = Pack.Object_Packet()
        Track = Pack.Track_Packet()
        LR_PeakIdx = Pack.LR_PeakIndex_Packet()
        SR_PeakIdx = Pack.SR_PeakIndex_Packet()
        LR_FFTData = Pack.LR_FFTData_Packet()
        SR_FFTData = Pack.SR_FFTData_Packet()
        LR_CalData = Pack.LR_FFTData_Packet()
        SR_CalData = Pack.SR_FFTData_Packet()


        for idx in range(0, len(CanID)):
            ID = CanID[idx]
            RxBuff = CanData[idx]

            if ID == SpInfo_ID:
                SpInfo.dword[0] = RxBuff
                SpInfo.dword[1] = RxBuff >> 64

                self.CurrentPRF = SpInfo.bits.CurrentPRF
                self.RadarScanIdx = SpInfo.bits.VehSpdKph
                self.SampleNumber = SpInfo.bits.SMPLNum
                self.CycleTime = SpInfo.bits.CycleTime

                self.LR_PeakCnt = SpInfo.bits.PeakCnt_LR
                self.SR_PeakCnt = SpInfo.bits.PeakCnt_SR

                self.VehInfo[0] = SpInfo.bits.VehicleSpeed
                self.VehInfo[1] = SpInfo.bits.YawRate
                self.VehInfo[2] = 0
                self.VehInfo[3] = 0

            if Object_ID <= ID <= (Object_ID + (Num_Object / NumObjSig)):
                for idx in range(NumObjSig):
                    obj_idx = ((ID - Object_ID) * NumObjSig) + idx
                    Object.dword[idx] = RxBuff >> (64 * idx)

                    self.ObjInfo[obj_idx][0] = Object.bits.Range
                    self.ObjInfo[obj_idx][1] = Object.bits.Velocity
                    self.ObjInfo[obj_idx][2] = Object.bits.AziAng
                    self.ObjInfo[obj_idx][3] = Object.bits.EleAng
                    self.ObjInfo[obj_idx][4] = Object.bits.Power
                    self.ObjInfo[obj_idx][5] = 0
                    self.ObjInfo[obj_idx][6] = Object.bits.ModType
                    self.ObjInfo[obj_idx][7] = 0
                    self.ObjInfo[obj_idx][8] = 0
                    self.ObjInfo[obj_idx][9] = obj_idx
                    self.ObjInfo[obj_idx][10] = 0
                    self.ObjInfo[obj_idx][11] = -1


            if Track_ID <= ID <= (Track_ID + (Num_Track / NumTrkSig)):
                for idx in range(NumTrkSig):
                    trk_idx = ((ID - Track_ID) * NumTrkSig) + idx
                    Track.dword[idx] = RxBuff >> (64 * idx)

                    self.TrkInfo[trk_idx][0] = Track.bits.Status
                    self.TrkInfo[trk_idx][1] = Track.bits.UpdState
                    self.TrkInfo[trk_idx][2] = Track.bits.MoveStatus
                    self.TrkInfo[trk_idx][3] = Track.bits.PosX
                    self.TrkInfo[trk_idx][4] = Track.bits.PosY
                    self.TrkInfo[trk_idx][5] = Track.bits.VelX
                    self.TrkInfo[trk_idx][6] = Track.bits.VelY
                    self.TrkInfo[trk_idx][7] = Track.bits.Power
                    self.TrkInfo[trk_idx][8] = Track.bits.HeadingAngle
                    self.TrkInfo[trk_idx][9] = Track.bits.AliveAge
                    self.TrkInfo[trk_idx][10] = Track.bits.Width
                    self.TrkInfo[trk_idx][11] = Track.bits.Length


            if LR_PeakIdx_ID <= ID <= (LR_PeakIdx_ID + (NumPeak_LR / 8)):
                for idx in range(8):
                    peak_idx = ((ID - LR_PeakIdx_ID) * 8) + idx
                    LR_PeakIdx.dword[idx] = RxBuff >> (64 * idx)

                    self.LR_PeakData[peak_idx][0] = LR_PeakIdx.bits.FreqIndex_R
                    self.LR_PeakData[peak_idx][1] = LR_PeakIdx.bits.FreqIndex_D
                    self.LR_PeakData[peak_idx][2] = LR_PeakIdx.bits.EstFreqIndex_R
                    self.LR_PeakData[peak_idx][3] = LR_PeakIdx.bits.EstFreqIndex_D

            if LR_PeakFFT_ID <= ID <= (LR_PeakFFT_ID + (NumPeak_LR / NumPeakSig_LR)):
                for idx in range(NumPeakSig_LR):
                    peak_idx = ((ID - LR_PeakFFT_ID) * NumPeakSig_LR) + idx
                    LR_FFTData.dword[idx] = RxBuff >> (64 * idx)

                    self.LR_PeakData[peak_idx][4] = LR_FFTData.bits.FFT_Tx1Ch0_real
                    self.LR_PeakData[peak_idx][5] = LR_FFTData.bits.FFT_Tx1Ch0_imag
                    self.LR_PeakData[peak_idx][6] = LR_FFTData.bits.FFT_Tx1Ch1_real
                    self.LR_PeakData[peak_idx][7] = LR_FFTData.bits.FFT_Tx1Ch1_imag
                    self.LR_PeakData[peak_idx][8] = LR_FFTData.bits.FFT_Tx1Ch2_real
                    self.LR_PeakData[peak_idx][9] = LR_FFTData.bits.FFT_Tx1Ch2_imag
                    self.LR_PeakData[peak_idx][10] = LR_FFTData.bits.FFT_Tx1Ch3_real
                    self.LR_PeakData[peak_idx][11] = LR_FFTData.bits.FFT_Tx1Ch3_imag

                    self.LR_PeakData[peak_idx][12] = LR_FFTData.bits.FFT_Tx2Ch0_real
                    self.LR_PeakData[peak_idx][13] = LR_FFTData.bits.FFT_Tx2Ch0_imag
                    self.LR_PeakData[peak_idx][14] = LR_FFTData.bits.FFT_Tx2Ch1_real
                    self.LR_PeakData[peak_idx][15] = LR_FFTData.bits.FFT_Tx2Ch1_imag
                    self.LR_PeakData[peak_idx][16] = LR_FFTData.bits.FFT_Tx2Ch2_real
                    self.LR_PeakData[peak_idx][17] = LR_FFTData.bits.FFT_Tx2Ch2_imag
                    self.LR_PeakData[peak_idx][18] = LR_FFTData.bits.FFT_Tx2Ch3_real
                    self.LR_PeakData[peak_idx][19] = LR_FFTData.bits.FFT_Tx2Ch3_imag


            if SR_PeakIdx_ID <= ID <= (SR_PeakIdx_ID + (NumPeak_SR / 8)):
                for idx in range(8):
                    peak_idx = ((ID - SR_PeakIdx_ID) * 8) + idx
                    SR_PeakIdx.dword[idx] = RxBuff >> (64 * idx)

                    self.SR_PeakData[peak_idx][0] = SR_PeakIdx.bits.FreqIndex_R
                    self.SR_PeakData[peak_idx][1] = SR_PeakIdx.bits.FreqIndex_D
                    self.SR_PeakData[peak_idx][2] = SR_PeakIdx.bits.EstFreqIndex_R
                    self.SR_PeakData[peak_idx][3] = SR_PeakIdx.bits.EstFreqIndex_D

            if SR_PeakFFT_ID <= ID <= (SR_PeakFFT_ID + (NumPeak_SR / NumPeakSig_SR)):
                for idx in range(NumPeakSig_SR):
                    peak_idx = ((ID - SR_PeakFFT_ID) * NumPeakSig_SR) + idx
                    SR_FFTData.dword[idx] = RxBuff >> (64 * idx)

                    self.SR_PeakData[peak_idx][4] = SR_FFTData.bits.FFT_Tx1Ch0_real
                    self.SR_PeakData[peak_idx][5] = SR_FFTData.bits.FFT_Tx1Ch0_imag
                    self.SR_PeakData[peak_idx][6] = SR_FFTData.bits.FFT_Tx1Ch1_real
                    self.SR_PeakData[peak_idx][7] = SR_FFTData.bits.FFT_Tx1Ch1_imag
                    self.SR_PeakData[peak_idx][8] = SR_FFTData.bits.FFT_Tx1Ch2_real
                    self.SR_PeakData[peak_idx][9] = SR_FFTData.bits.FFT_Tx1Ch2_imag
                    self.SR_PeakData[peak_idx][10] = SR_FFTData.bits.FFT_Tx1Ch3_real
                    self.SR_PeakData[peak_idx][11] = SR_FFTData.bits.FFT_Tx1Ch3_imag

                    self.SR_PeakData[peak_idx][12] = SR_FFTData.bits.FFT_Tx2Ch0_real
                    self.SR_PeakData[peak_idx][13] = SR_FFTData.bits.FFT_Tx2Ch0_imag
                    self.SR_PeakData[peak_idx][14] = SR_FFTData.bits.FFT_Tx2Ch1_real
                    self.SR_PeakData[peak_idx][15] = SR_FFTData.bits.FFT_Tx2Ch1_imag
                    self.SR_PeakData[peak_idx][16] = SR_FFTData.bits.FFT_Tx2Ch2_real
                    self.SR_PeakData[peak_idx][17] = SR_FFTData.bits.FFT_Tx2Ch2_imag
                    self.SR_PeakData[peak_idx][18] = SR_FFTData.bits.FFT_Tx2Ch3_real
                    self.SR_PeakData[peak_idx][19] = SR_FFTData.bits.FFT_Tx2Ch3_imag


            if ID == LR_CalFFT_ID:
                LR_CalData.dword[0] = RxBuff
                LR_CalData.dword[1] = RxBuff >> 64
                LR_CalData.dword[2] = RxBuff >> (64*2)
                LR_CalData.dword[3] = RxBuff >> (64*3)

                self.LR_CalData[0] = LR_CalData.bits.FFT_Tx1Ch0_real
                self.LR_CalData[1] = LR_FFTData.bits.FFT_Tx1Ch0_imag
                self.LR_CalData[2] = LR_FFTData.bits.FFT_Tx1Ch1_real
                self.LR_CalData[3] = LR_FFTData.bits.FFT_Tx1Ch1_imag
                self.LR_CalData[4] = LR_FFTData.bits.FFT_Tx1Ch2_real
                self.LR_CalData[5] = LR_FFTData.bits.FFT_Tx1Ch2_imag
                self.LR_CalData[6] = LR_FFTData.bits.FFT_Tx1Ch3_real
                self.LR_CalData[7] = LR_FFTData.bits.FFT_Tx1Ch3_imag

                self.LR_CalData[8] = LR_FFTData.bits.FFT_Tx2Ch0_real
                self.LR_CalData[9] = LR_FFTData.bits.FFT_Tx2Ch0_imag
                self.LR_CalData[10] = LR_FFTData.bits.FFT_Tx2Ch1_real
                self.LR_CalData[11] = LR_FFTData.bits.FFT_Tx2Ch1_imag
                self.LR_CalData[12] = LR_FFTData.bits.FFT_Tx2Ch2_real
                self.LR_CalData[13] = LR_FFTData.bits.FFT_Tx2Ch2_imag
                self.LR_CalData[14] = LR_FFTData.bits.FFT_Tx2Ch3_real
                self.LR_CalData[15] = LR_FFTData.bits.FFT_Tx2Ch3_imag

            if ID == SR_CalFFT_ID:
                SR_CalData.dword[0] = RxBuff
                SR_CalData.dword[1] = RxBuff >> 64
                SR_CalData.dword[2] = RxBuff >> (64*2)
                SR_CalData.dword[3] = RxBuff >> (64*3)

                self.SR_CalData[0] = SR_CalData.bits.FFT_Tx1Ch0_real
                self.SR_CalData[1] = SR_FFTData.bits.FFT_Tx1Ch0_imag
                self.SR_CalData[2] = SR_FFTData.bits.FFT_Tx1Ch1_real
                self.SR_CalData[3] = SR_FFTData.bits.FFT_Tx1Ch1_imag
                self.SR_CalData[4] = SR_FFTData.bits.FFT_Tx1Ch2_real
                self.SR_CalData[5] = SR_FFTData.bits.FFT_Tx1Ch2_imag
                self.SR_CalData[6] = SR_FFTData.bits.FFT_Tx1Ch3_real
                self.SR_CalData[7] = SR_FFTData.bits.FFT_Tx1Ch3_imag

                self.SR_CalData[8] = SR_FFTData.bits.FFT_Tx2Ch0_real
                self.SR_CalData[9] = SR_FFTData.bits.FFT_Tx2Ch0_imag
                self.SR_CalData[10] = SR_FFTData.bits.FFT_Tx2Ch1_real
                self.SR_CalData[11] = SR_FFTData.bits.FFT_Tx2Ch1_imag
                self.SR_CalData[12] = SR_FFTData.bits.FFT_Tx2Ch2_real
                self.SR_CalData[13] = SR_FFTData.bits.FFT_Tx2Ch2_imag
                self.SR_CalData[14] = SR_FFTData.bits.FFT_Tx2Ch3_real
                self.SR_CalData[15] = SR_FFTData.bits.FFT_Tx2Ch3_imag


        if "Sim_TrkInfo" in h5grp:
            dset = h5grp["Sim_VehInfo"]
            dset[...] = self.VehInfo
            dset = h5grp["Sim_ObjInfo"]
            dset[...] = self.ObjInfo
            dset = h5grp["Sim_TrkInfo"]
            dset[...] = self.TrkInfo

            dset = h5grp["Sim_LR_PeakCnt"]
            dset[...] = self.LR_PeakCnt
            dset = h5grp["Sim_SR_PeakCnt"]
            dset[...] = self.SR_PeakCnt
            dset = h5grp["Sim_LR_PeakData"]
            dset[...] = self.LR_PeakData
            dset = h5grp["Sim_SR_PeakData"]
            dset[...] = self.SR_PeakData

            dset = h5grp["Sim_CurrentPRF"]
            dset[...] = self.CurrentPRF
            dset = h5grp["Sim_RadarScanIdx"]
            dset[...] = self.RadarScanIdx
            dset = h5grp["Sim_SampleNumber"]
            dset[...] = self.SampleNumber
            dset = h5grp["Sim_CycleTime"]
            dset[...] = self.CycleTime

            dset = h5grp["CalData_FFT_LR"]
            dset[...] = self.LR_CalData
            dset = h5grp["CalData_FFT_SR"]
            dset[...] = self.SR_CalData

        else:
            dset = h5grp.create_dataset("Sim_VehInfo", data=self.VehInfo, dtype='int16')
            dset = h5grp.create_dataset("Sim_ObjInfo", data=self.ObjInfo, dtype='int16')
            dset = h5grp.create_dataset("Sim_TrkInfo", data=self.TrkInfo, dtype='int16')

            dset = h5grp.create_dataset("Sim_LR_PeakCnt", data=self.LR_PeakCnt, dtype='int16')
            dset = h5grp.create_dataset("Sim_SR_PeakCnt", data=self.SR_PeakCnt, dtype='int16')
            dset = h5grp.create_dataset("Sim_LR_PeakData", data=self.LR_PeakData, dtype='int16')
            dset = h5grp.create_dataset("Sim_SR_PeakData", data=self.SR_PeakData, dtype='int16')

            dset = h5grp.create_dataset("Sim_CurrentPRF", data=self.CurrentPRF, dtype='int16')
            dset = h5grp.create_dataset("Sim_RadarScanIdx", data=self.RadarScanIdx, dtype='int16')
            dset = h5grp.create_dataset("Sim_SampleNumber", data=self.SampleNumber, dtype='int16')
            dset = h5grp.create_dataset("Sim_CycleTime", data=self.CycleTime, dtype='int16')

            dset = h5grp.create_dataset("CalData_FFT_LR", data=self.LR_CalData, dtype='int16')
            dset = h5grp.create_dataset("CalData_FFT_SR", data=self.SR_CalData, dtype='int16')


    def SignedConvert(self, x, bitLen):
        if x >= (1 << (bitLen-1)):
            x -= (1 << bitLen)

        return x



if __name__ == '__main__':
    import Log_Packet_SRR as Pack
    import os
    import h5py


    curfolder = os.getcwd()
    filename = '/logdummy.h5'
    logfile = curfolder + filename
    h5dummyf = h5py.File(logfile, 'w')
    GroupName = 'SCAN_'
    GroupName += ('%05d' % 1)
    grp = h5dummyf.create_group(GroupName)

    TestClass = CanToH5(RadarType='SRR')
    TestClass.convert([0x600], [10], grp)

