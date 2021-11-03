import numpy as np
import h5py
import os
from pathlib import *
import struct
import time
from numpy.core.fromnumeric import reshape

ko2en_translate_table = {
    '전방': 'Front',
    '레이더': 'Radar',
    '레이다': 'Radar',
    '카메라': 'Cam',
    '후방': 'Rear',
}


def remove_ko(fname):
    for k, v in ko2en_translate_table.items():
        if k in fname:
            fname = fname.replace(k, v)
    return fname

class RawH5ToH5:
    def __init__(self, **opts):

        self.opts = {
            'RadarType': 'AFI,ATM',
        }
        self.opts.update(opts)

        # Raw Data
        self.RadarScanIdx = []
        self.SampleNumber = []
        self.CycleTime = []
        self.gSpCurPRF = []
        self.Sim_TimeData = []
        self.Sim_TimeData_Raw = []

        self.Can = []
        self.Image = []
        self.Object = []
        self.Measurement = []

        self.AI = []
        self.nci_lr_mode = []
        self.nci_mr_mode = []
        self.nci_sr_mode = []
        self.nci_ref_mode = []

        self.lr_fft_peak_data_cf32FFTData = []
        self.lr_fft_peak_data_rdf32EstFreqIdx = []
        self.lr_fft_peak_data_rdu16FreqIdx = []
        self.lr_fft_peak_data_s16PeakCnt = []

        self.sr_fft_peak_data_cf32FFTData = []
        self.sr_fft_peak_data_rdf32EstFreqIdx = []
        self.sr_fft_peak_data_rdu16FreqIdx = []

        self.mr_fft_peak_data_cf32FFTData = []
        self.mr_fft_peak_data_rdf32EstFreqIdx = []
        self.mr_fft_peak_data_rdu16FreqIdx = []

        self.rm_fft_peak_data_cf32FFTData = []
        self.rm_fft_peak_data_rdf32EstFreqIdx = []
        self.rm_fft_peak_data_rdu16FreqIdx = []

        # Convert Data
        self.LR_PeakCnt = []
        self.MR_PeakCnt = []
        self.SR_PeakCnt = []
        self.LR_PeakData = []
        self.MR_PeakData = []
        self.SR_PeakData = []
        self.RM_PeakCnt = []
        self.RM_PeakData = []

        self.nci_lr_mode_convert = []
        self.nci_lr_mode_convert_reshape = []
        self.nci_mr_mode_convert = []
        self.nci_mr_mode_convert_reshape = []
        self.nci_sr_mode_convert = []
        self.nci_sr_mode_convert_reshape = []
        self.nci_RM_mode_convert = []
        self.nci_RM_mode_convert_reshape = []
        self.nci_ref_mode_convert = []
        self.nci_ref_mode_convert_reshape = []

        if opts['RadarType'] == 'AFI':
            self.convert = self.AFI_Convert
        elif opts['RadarType'] == 'ATM':
            self.convert = self.ATM_Convert
        else:
            pass

    def AFI_Convert(self, rootdir):

        start_time = time.time()

        num_Tx = 12
        num_Rx = 16

        num_sample_RM = 256
        num_chirp_RM = 512
        num_sample = 512
        num_chirp = 32

        num_peak_data = 2+2+num_Rx*num_Tx*2     # Freq Idx 2, Est Freq Idx 2, FFT Data Rx * Tx * 2(real.imag)
        num_rm_peak_data = 2+2+num_Rx*1*2       # Freq Idx 2, Est Freq Idx 2, FFT Data Rx * Tx * 2(real.imag)

        outdir = ''.join([rootdir+'\\OUT'])
        outputpath = Path(outdir)
        outputpath.mkdir(exist_ok=True)
       
        rawh5names = list((Path(rootdir).glob('./*.h5')))

        hdf5fpath_raw = Path(rootdir, remove_ko(rawh5names)[0].stem + '.h5')
        hdf5fpath_convert = Path(outputpath, remove_ko(rawh5names)[0].stem + '_parsing.h5')
        
        h5file_raw = h5py.File(str(hdf5fpath_raw.resolve()), 'r')
        h5file = h5py.File(str(hdf5fpath_convert.resolve()), 'w')

        h5grp = h5file.create_group('DataInfo')
        dset = h5grp.create_dataset("initScan", data=1, dtype='uint32')
        dset = h5grp.create_dataset("finScan", data=h5file_raw.keys().__len__(), dtype='uint32')

        grpname_temp = 'SCAN_{:05d}'.format(0)

        num_lr_peak_cnt = int(np.size(h5file_raw[grpname_temp + '/lr_fft_peak_data_rdu16FreqIdx'])/4)
        num_mr_peak_cnt = int(np.size(h5file_raw[grpname_temp + '/mr_fft_peak_data_rdu16FreqIdx'])/4)
        num_sr_peak_cnt = int(np.size(h5file_raw[grpname_temp + '/sr_fft_peak_data_rdu16FreqIdx'])/4)
        num_rm_peak_cnt = int(np.size(h5file_raw[grpname_temp + '/rm_fft_peak_data_rdu16FreqIdx'])/4)


        print('MAX RM_peak Cnt : ', num_rm_peak_cnt)
        print('MAX LR_peak Cnt : ', num_lr_peak_cnt)
        print('MAX MR_peak Cnt : ', num_mr_peak_cnt)
        print('MAX SR_peak Cnt : ', num_sr_peak_cnt)



        self.LR_PeakCnt = 0
        self.LR_PeakData = np.zeros([num_lr_peak_cnt, num_peak_data])
        self.MR_PeakCnt = 0
        self.MR_PeakData = np.zeros([num_mr_peak_cnt, num_peak_data])
        self.SR_PeakCnt = 0
        self.SR_PeakData = np.zeros([num_sr_peak_cnt, num_peak_data])
        self.RM_PeakCnt = 0
        self.RM_PeakData = np.zeros([num_rm_peak_cnt, num_rm_peak_data])

        self.RadarScanIdx = 0
        self.SampleNumber = 0
        self.CycleTime = 0

        self.nci_ref_mode_convert = np.zeros(num_sample_RM * num_chirp_RM, dtype='float32')
        self.nci_ref_mode_convert_reshape = np.zeros([num_sample_RM, num_chirp_RM])
        self.nci_lr_mode_convert = np.zeros(num_sample * num_chirp, dtype='float32')
        self.nci_lr_mode_convert_reshape = np.zeros([num_sample, num_chirp])
        self.nci_mr_mode_convert = np.zeros(num_sample * num_chirp, dtype='float32')
        self.nci_mr_mode_convert_reshape = np.zeros([num_sample, num_chirp])
        self.nci_sr_mode_convert = np.zeros(num_sample * num_chirp, dtype='float32')
        self.nci_sr_mode_convert_reshape = np.zeros([num_sample, num_chirp])


        start_time = time.time()

        for scan in range(0, h5file_raw.keys().__len__()-10):
        #for scan in range(0, 1200):

            grpname = 'SCAN_{:05d}'.format(scan)
            grpname_w = 'SCAN_{:05d}'.format(scan+1)
            print(grpname)

            self.Can = h5file_raw[grpname + '/Can']
            self.Image = h5file_raw[grpname + '/Image']

            self.Measurement = h5file_raw[grpname + '/Measurement']
            self.Object = h5file_raw[grpname + '/Object']

            if h5file_raw[grpname + '/webcam'] is not None:
                self.webcam = h5file_raw[grpname + '/webcam']

            if h5file_raw[grpname + '/AI'] is not None:
                self.AI = h5file_raw[grpname + '/AI']


            self.nci_ref_mode = h5file_raw[grpname + '/nci_ref_mode']
            self.nci_lr_mode = h5file_raw[grpname + '/nci_lr_mode']
            self.nci_mr_mode = h5file_raw[grpname + '/nci_mr_mode']
            self.nci_sr_mode = h5file_raw[grpname + '/nci_sr_mode']


            self.nci_ref_mode = (self.nci_ref_mode)
            self.nci_lr_mode = (self.nci_lr_mode)
            self.nci_mr_mode = (self.nci_mr_mode)
            self.nci_sr_mode = (self.nci_sr_mode)

            self.lr_fft_peak_data_cf32FFTData = h5file_raw[grpname + '/lr_fft_peak_data_cf32FFTData']
            self.lr_fft_peak_data_rdf32EstFreqIdx = h5file_raw[grpname + '/lr_fft_peak_data_rdf32EstFreqIdx']
            self.lr_fft_peak_data_rdu16FreqIdx = h5file_raw[grpname + '/lr_fft_peak_data_rdu16FreqIdx']
            self.LR_PeakCnt = int.from_bytes(h5file_raw[grpname + '/lr_fft_peak_data_s16PeakCnt'][0:2], byteorder='little', signed=True)

            self.sr_fft_peak_data_cf32FFTData = h5file_raw[grpname + '/sr_fft_peak_data_cf32FFTData']
            self.sr_fft_peak_data_rdf32EstFreqIdx = h5file_raw[grpname + '/sr_fft_peak_data_rdf32EstFreqIdx']
            self.sr_fft_peak_data_rdu16FreqIdx = h5file_raw[grpname + '/sr_fft_peak_data_rdu16FreqIdx']
            self.SR_PeakCnt = int.from_bytes(h5file_raw[grpname + '/sr_fft_peak_data_s16PeakCnt'][0:2], byteorder='little', signed=True)

            self.mr_fft_peak_data_cf32FFTData = h5file_raw[grpname + '/mr_fft_peak_data_cf32FFTData']
            self.mr_fft_peak_data_rdf32EstFreqIdx = h5file_raw[grpname + '/mr_fft_peak_data_rdf32EstFreqIdx']
            self.mr_fft_peak_data_rdu16FreqIdx = h5file_raw[grpname + '/mr_fft_peak_data_rdu16FreqIdx']
            self.MR_PeakCnt = int.from_bytes(h5file_raw[grpname + '/mr_fft_peak_data_s16PeakCnt'][0:2], byteorder='little', signed=True)

            self.rm_fft_peak_data_cf32FFTData = h5file_raw[grpname + '/rm_fft_peak_data_cf32FFTData']
            self.rm_fft_peak_data_rdf32EstFreqIdx = h5file_raw[grpname + '/rm_fft_peak_data_rdf32EstFreqIdx']
            self.rm_fft_peak_data_rdu16FreqIdx = h5file_raw[grpname + '/rm_fft_peak_data_rdu16FreqIdx']
            self.RM_PeakCnt = int.from_bytes(h5file_raw[grpname + '/rm_fft_peak_data_s16PeakCnt'][0:2], byteorder='little', signed=True)
            
            length_data = int(self.nci_lr_mode.__len__()/4)
            format_float = '<' + str(length_data) + 'f'       
            self.nci_lr_mode_convert = np.array(struct.unpack(format_float, self.nci_lr_mode[:]))
            self.nci_mr_mode_convert = np.array(struct.unpack(format_float, self.nci_mr_mode[:]))
            self.nci_sr_mode_convert = np.array(struct.unpack(format_float, self.nci_sr_mode[:]))

            length_data = int(self.nci_ref_mode.__len__()/4)
            format_float = '<' + str(length_data) + 'f'
            self.nci_ref_mode_convert = np.array(struct.unpack(format_float, self.nci_ref_mode[:]))
            
            lr_fft_peak_data_rdu16FreqIdx_temp = np.array(struct.unpack('<'+str(num_lr_peak_cnt*2)+'H', self.lr_fft_peak_data_rdu16FreqIdx[:]))
            lr_fft_peak_data_rdf32EstFreqIdx_temp = np.array(struct.unpack('<'+str(num_lr_peak_cnt*2)+'f', self.lr_fft_peak_data_rdf32EstFreqIdx[:]))
            mr_fft_peak_data_rdu16FreqIdx_temp = np.array(struct.unpack('<'+str(num_mr_peak_cnt*2)+'H', self.mr_fft_peak_data_rdu16FreqIdx[:]))
            mr_fft_peak_data_rdf32EstFreqIdx_temp = np.array(struct.unpack('<'+str(num_mr_peak_cnt*2)+'f', self.mr_fft_peak_data_rdf32EstFreqIdx[:]))
            sr_fft_peak_data_rdu16FreqIdx_temp = np.array(struct.unpack('<'+str(num_sr_peak_cnt*2)+'H', self.sr_fft_peak_data_rdu16FreqIdx[:]))
            sr_fft_peak_data_rdf32EstFreqIdx_temp = np.array(struct.unpack('<'+str(num_sr_peak_cnt*2)+'f', self.sr_fft_peak_data_rdf32EstFreqIdx[:]))
            rm_fft_peak_data_rdu16FreqIdx_temp = np.array(struct.unpack('<'+str(num_rm_peak_cnt*2)+'H', self.rm_fft_peak_data_rdu16FreqIdx[:]))
            rm_fft_peak_data_rdf32EstFreqIdx_temp = np.array(struct.unpack('<'+str(num_rm_peak_cnt*2)+'f', self.rm_fft_peak_data_rdf32EstFreqIdx[:]))

            lr_fft_peak_data_cf32FFTData_temp = np.array(struct.unpack('<'+str(num_Tx*num_Rx*num_lr_peak_cnt*2)+'f', self.lr_fft_peak_data_cf32FFTData[:]))
            mr_fft_peak_data_cf32FFTData_temp = np.array(struct.unpack('<'+str(num_Tx*num_Rx*num_mr_peak_cnt*2)+'f', self.mr_fft_peak_data_cf32FFTData[:]))
            sr_fft_peak_data_cf32FFTData_temp = np.array(struct.unpack('<'+str(num_Tx*num_Rx*num_sr_peak_cnt*2)+'f', self.sr_fft_peak_data_cf32FFTData[:]))
            rm_fft_peak_data_cf32FFTData_temp = np.array(struct.unpack('<'+str(num_Rx*num_rm_peak_cnt*2)+'f', self.rm_fft_peak_data_cf32FFTData[:]))

            lr_rdu16FreqIdx=np.reshape(lr_fft_peak_data_rdu16FreqIdx_temp,(num_lr_peak_cnt,2))
            lr_rdf32FreqIdx=np.reshape(lr_fft_peak_data_rdf32EstFreqIdx_temp,(num_lr_peak_cnt,2))
            lr_fftdata=np.reshape(lr_fft_peak_data_cf32FFTData_temp,(num_lr_peak_cnt,num_Tx*num_Rx*2))
            self.LR_PeakData = np.concatenate((lr_rdu16FreqIdx,lr_rdf32FreqIdx,lr_fftdata),axis=1)
            
            mr_rdu16FreqIdx=np.reshape(mr_fft_peak_data_rdu16FreqIdx_temp,(num_mr_peak_cnt,2))
            mr_rdf32FreqIdx=np.reshape(mr_fft_peak_data_rdf32EstFreqIdx_temp,(num_mr_peak_cnt,2))
            mr_fftdata=np.reshape(mr_fft_peak_data_cf32FFTData_temp,(num_mr_peak_cnt,num_Tx*num_Rx*2))
            self.MR_PeakData = np.concatenate((mr_rdu16FreqIdx,mr_rdf32FreqIdx,mr_fftdata),axis=1)

            sr_rdu16FreqIdx=np.reshape(sr_fft_peak_data_rdu16FreqIdx_temp,(num_sr_peak_cnt,2))
            sr_rdf32FreqIdx=np.reshape(sr_fft_peak_data_rdf32EstFreqIdx_temp,(num_sr_peak_cnt,2))
            sr_fftdata=np.reshape(sr_fft_peak_data_cf32FFTData_temp,(num_sr_peak_cnt,num_Tx*num_Rx*2))
            self.SR_PeakData = np.concatenate((sr_rdu16FreqIdx,sr_rdf32FreqIdx,sr_fftdata),axis=1)

            rm_rdu16FreqIdx=np.reshape(rm_fft_peak_data_rdu16FreqIdx_temp,(num_rm_peak_cnt,2))
            rm_rdf32FreqIdx=np.reshape(rm_fft_peak_data_rdf32EstFreqIdx_temp,(num_rm_peak_cnt,2))
            rm_fftdata=np.reshape(rm_fft_peak_data_cf32FFTData_temp,(num_rm_peak_cnt,num_Rx*2))
            self.RM_PeakData = np.concatenate((rm_rdu16FreqIdx,rm_rdf32FreqIdx,rm_fftdata),axis=1)

            h5grp = h5file.create_group(grpname_w)

            self.nci_lr_mode_convert_reshape = self.nci_lr_mode_convert.reshape(num_sample, num_chirp)
            self.nci_mr_mode_convert_reshape = self.nci_mr_mode_convert.reshape(num_sample, num_chirp)
            self.nci_sr_mode_convert_reshape = self.nci_sr_mode_convert.reshape(num_sample, num_chirp)
            self.nci_ref_mode_convert_reshape = self.nci_ref_mode_convert.reshape(num_sample_RM, num_chirp_RM)
            

            if "Sim_TrkInfo" in h5grp:
                dset = h5grp["Can"]
                dset[...] = self.Can
                dset = h5grp["image"]
                dset[...] = self.Image
                dset = h5grp["AI"]
                dset[...] = self.AI
                dset = h5grp["Measurement"]
                dset[...] = self.Measurement
                dset = h5grp["Object"]
                dset[...] = self.Object

                dset = h5grp["nci_ref_mode"]
                dset[...] = self.nci_ref_mode_convert_reshape
                dset = h5grp["nci_lr_mode"]
                dset[...] = self.nci_lr_mode_convert_reshape
                dset = h5grp["nci_mr_mode"]
                dset[...] = self.nci_mr_mode_convert_reshape
                dset = h5grp["nci_sr_mode"]
                dset[...] = self.nci_sr_mode_convert_reshape

                dset = h5grp["Sim_RM_PeakData"]
                dset[...] = self.RM_PeakData
                dset = h5grp["Sim_RM_PeakCnt"]
                dset[...] = self.RM_PeakCnt

                dset = h5grp["Sim_LR_PeakData"]
                dset[...] = self.LR_PeakData
                dset = h5grp["Sim_LR_PeakCnt"]
                dset[...] = self.LR_PeakCnt

                dset = h5grp["Sim_MR_PeakData"]
                dset[...] = self.MR_PeakData
                dset = h5grp["Sim_MR_PeakCnt"]
                dset[...] = self.MR_PeakCnt

                dset = h5grp["Sim_SR_PeakData"]
                dset[...] = self.SR_PeakData
                dset = h5grp["Sim_SR_PeakCnt"]
                dset[...] = self.SR_PeakCnt

                dset = h5grp["Sim_SampleNumber"]
                dset[...] = self.SampleNumber
                dset = h5grp["Sim_CycleTime"]
                dset[...] = self.CycleTime
            else:
                dset = h5grp.create_dataset("Can", data=self.Can, dtype='float32')
                dset = h5grp.create_dataset("image", data=self.Image, dtype='uint8')
                dset = h5grp.create_dataset("Measurement", data=self.Measurement, dtype='float32')
                dset = h5grp.create_dataset("Object", data=self.Object, dtype='float32')

                if self.AI is not None:
                    dset = h5grp.create_dataset("AI", data=self.AI, dtype='float32')

                if self.webcam is not None:
                    dset = h5grp.create_dataset("webcam", data=self.webcam, dtype='uint8')



                dset = h5grp.create_dataset("Sim_RM_PowSpectrum", data=self.nci_ref_mode_convert_reshape, dtype='float32')
                dset = h5grp.create_dataset("Sim_LR_PowSpectrum", data=self.nci_lr_mode_convert_reshape, dtype='float32')
                dset = h5grp.create_dataset("Sim_MR_PowSpectrum", data=self.nci_mr_mode_convert_reshape, dtype='float32')
                dset = h5grp.create_dataset("Sim_SR_PowSpectrum", data=self.nci_sr_mode_convert_reshape, dtype='float32')

                dset = h5grp.create_dataset("Sim_RM_PeakCnt", data=self.RM_PeakCnt, dtype='int16')
                dset = h5grp.create_dataset("Sim_RM_PeakData", data=self.RM_PeakData, dtype='float32')

                dset = h5grp.create_dataset("Sim_LR_PeakCnt", data=self.LR_PeakCnt, dtype='int16')
                dset = h5grp.create_dataset("Sim_LR_PeakData", data=self.LR_PeakData, dtype='float32')
                dset = h5grp.create_dataset("Sim_SR_PeakCnt", data=self.SR_PeakCnt, dtype='int16')
                dset = h5grp.create_dataset("Sim_SR_PeakData", data=self.SR_PeakData, dtype='float32')
                dset = h5grp.create_dataset("Sim_MR_PeakCnt", data=self.MR_PeakCnt, dtype='int16')
                dset = h5grp.create_dataset("Sim_MR_PeakData", data=self.MR_PeakData, dtype='float32')

                dset = h5grp.create_dataset("Sim_SampleNumber", data=self.SampleNumber, dtype='uint16')
                dset = h5grp.create_dataset("Sim_CycleTime", data=self.CycleTime, dtype='int16')

        print(f' Time : {time.time() - start_time}')
        print(f'{remove_ko(rawh5names)[0].stem} Converting End')
            


    def ATM_Convert(self, rootdir):

        num_Tx = 2
        num_Rx = 8

        num_sample = 1024
        num_chirp = 64
        outdir = ''.join([rootdir+'\\OUT'])
        outputpath = Path(outdir)
        outputpath.mkdir(exist_ok=True)

        rawh5names = list((Path(rootdir).glob('./*.h5')))

        '''
        for file_number in range(0,rawh5names.__len__()):
            hdf5fpath_raw = Path(outputpath, remove_ko(rawh5names)[file_number].stem + '.h5')
            hdf5fpath_convert = Path(outputpath, remove_ko(rawh5names)[file_number].stem + '_parsing.h5')
        '''

        hdf5fpath_raw = Path(rootdir, remove_ko(rawh5names)[0].stem + '.h5')
        hdf5fpath_convert = Path(outputpath, remove_ko(rawh5names)[0].stem + '_parsing.h5')

        h5file_raw = h5py.File(str(hdf5fpath_raw.resolve()), 'r')
        h5file = h5py.File(str(hdf5fpath_convert.resolve()), 'w')

        h5grp = h5file.create_group('DataInfo')
        dset = h5grp.create_dataset("initScan", data=1, dtype='uint32')
        dset = h5grp.create_dataset("finScan", data=h5file_raw.keys().__len__(), dtype='uint32')

        self.RadarScanIdx = 0
        self.SampleNumber = 0
        self.CycleTime = 0
        self.AI = np.zeros(300, 6)
        self.Sim_TimeData = np.zeros(num_sample*num_chirp*num_Tx*num_Rx) # 2 : for 16bit
        self.Sim_TimeData_Raw = np.zeros(num_sample*num_chirp*num_Tx*num_Rx*2)


        for scan in range(0, h5file_raw.keys().__len__()):
            # for scan in range(0, 1):
            grpname = 'SCAN_{:05d}'.format(scan)

            self.AI = h5file_raw[grpname + '/AI']
            self.Image = h5file_raw[grpname + '/Image']
            self.Measurement = h5file_raw[grpname + '/Measurement']
            self.Object = h5file_raw[grpname + '/Object']
            self.gSpCurPRF = h5file_raw[grpname + '/gSpCurPRF']

            self.Sim_TimeData_Raw = h5file_raw[grpname + '/Sim_TimeData']

            for Idx in range(0, num_sample*num_chirp*num_Tx*num_Rx):
                self.Sim_TimeData[Idx] = int.from_bytes(
                    self.Sim_TimeData_Raw[2*Idx: 2*Idx+2], byteorder='little', signed=True)

            h5grp = h5file.create_group(grpname)

            if "Sim_TrkInfo" in h5grp:
                dset = h5grp["AI"]
                dset[...] = self.AI
                dset = h5grp["Image"]
                dset[...] = self.Image
                dset = h5grp["Measurement"]
                dset[...] = self.Measurement
                dset = h5grp["Object"]
                dset[...] = self.Object
                dset = h5grp["Sim_TimeData"]
                dset[...] = self.Sim_TimeData
                dset = h5grp["gSpCurPRF"]
                dset[...] = self.gSpCurPRF

            else:
                dset = h5grp.create_dataset("Can", data=self.AI, dtype='float32')
                dset = h5grp.create_dataset("Image", data=self.Image, dtype='uint8')
                dset = h5grp.create_dataset("Measurement", data=self.Measurement, dtype='float32')
                dset = h5grp.create_dataset("Object", data=self.Object, dtype='float32')
                dset = h5grp.create_dataset("Sim_TimeData", data=self.Sim_TimeData, dtype='int16')
                dset = h5grp.create_dataset("gSpCurPRF", data=self.gSpCurPRF, dtype='uint8')

    def SignedConvert(self, x, bitLen):
        if x >= (1 << (bitLen-1)):
            x -= (1 << bitLen)

        return x

if __name__ == '__main__':
    TestClass = RawH5ToH5(RadarType='AFI')
    rootdir = 'E:\\Logging_Data\\2. AFI910\\210601_FieldTest\\0601_test3'
    TestClass.AFI_Convert(rootdir)

