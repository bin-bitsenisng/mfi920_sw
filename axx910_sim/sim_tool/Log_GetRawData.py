
import os
import sys
import h5py
import numpy as np
from struct import pack, unpack, calcsize, iter_unpack
from pprint import pprint
import cv2
from pathlib import *
import datetime
import pandas as pd
from ctypes import *
from collections import namedtuple
from multiprocessing import Pool

import Log_CanToH5

dtypetable = {
    'b': np.int8,
    'B': np.uint8,
    'h': np.int16,
    'H': np.uint16,
    'i': np.int32,
    'I': np.uint32,
    'l': np.int32,
    #'L': np.uint32,
    'L': np.uint64,  # temporary, from python unpackstring, L means uint32 but Logger system's 'L' is 1000
    'q': np.int64,
    'Q': np.uint64,
    'f': np.float32,
    'd': np.float64
}

ko2en_translate_table = {
    '전방': 'Front',
    '레이더': 'Radar',
    '레이다': 'Radar',
    '카메라': 'Cam',
    '후방': 'Rear',
}


class _IMAGE_INFO(Structure):
    _fields_ = [('height', c_uint),
                ('width', c_uint),
                ('type', c_uint),
                ('size', c_uint), ]


def remove_ko(fname):
    for k, v in ko2en_translate_table.items():
        if k in fname:
            fname = fname.replace(k, v)
    return fname


class rawfile_to_hdf5:
    def __init__(self, channel, **opts):

        self.opts = {
            'RadarType': 'MRR, SRR, ROBOT',
        }
        self.opts.update(opts)

        self.pcan_ch = channel

        self.CanToH5 = Log_CanToH5.CanToH5(RadarType=opts['RadarType'])


    def get_data_from_raw_file(self, fnamepath, h5file):
        """
        * file header(92byte)
        device name(string) : 50byte
        device kind(string) : 10byte
        start date-time(string) : 14byte
        end date-time(string) : 14byte
        data count(int) : 4byte
        """
        rawdata_header = {}
        with fnamepath.open(mode='rb') as f:
            rawdata_header['devicename'] = unpack('50s', f.read(50))[0].decode('utf-8').strip()
            rawdata_header['devicekind'] = unpack('10s', f.read(10))[0].decode('utf-8').strip()
            rawdata_header['startdatetime'] = unpack('14s', f.read(14))[0].decode('utf-8').strip()
            rawdata_header['enddatetime'] = unpack('14s', f.read(14))[0].decode('utf-8').strip()
            rawdata_header['datacount'] = unpack('i', f.read(4))[0]

            """
            ========================== 1 frame ==========================
            * data-header(20 byte)
            frame number(int) : 4byte
            frame data size(int) : 4byte  (앞부분 8byte를 제외한 frame의 전체사이즈)
            current time(long) : 8byte
            canLog data count(int) : 4byte
    
            -----------------canLog data count 만큼 반복 -----------------
             *canLog data
             can Log Data Size(short) : 2byte (dlc데이터를 제외한 Log 데이터 사이즈로 time과 data사이에 추가적인 데이터가 들어갈수 있음. 현재값은 20)
             channel(byte) : 1byte
             id(int) : 4byte
             dlc(byte) : 1byte
             flag(int) : 4byte
             time(double) : 8byte
             data(byte[]) : dlc 사이즈만큼
            -----------------canLog data count 만큼 반복 -----------------
            ========================== 1 frame ==========================
            """
            h5grp = h5file.create_group('DataInfo')
            dset = h5grp.create_dataset("initScan", data=1, dtype='uint32')
            dset = h5grp.create_dataset("finScan", data=rawdata_header['datacount'], dtype='uint32')

            for scan in range(rawdata_header['datacount']):
                framenumber, totalsize, currenttime, logdatacount = unpack('iiqi', f.read(20))
                # timestamp_raw, framedatasize, currenttime, logdatacount = unpack('=diqi', f.read(24))
                grpname = 'SCAN_{:05d}'.format(scan + 1)
                h5grp = h5file.create_group(grpname)

                canid_list = []
                data_list = []
                for idx in range(logdatacount):
                    # logdatasize, channel, canid, dlc, flag, time = unpack('HBlBld', f.read(20))
                    logdatasize, channel = unpack('HB', f.read(3))
                    canid, dlc = unpack('LB', f.read(5))
                    flag = unpack('L', f.read(4))
                    time = unpack('d', f.read(8))
                    # print(channel, canid, dlc, time)
                    can_msg = f.read(dlc)
                    data = int.from_bytes(can_msg, byteorder='little', signed=False)

                    if channel == self.pcan_ch:
                        canid_list.append(canid)
                        data_list.append(data)

                    if channel != self.pcan_ch and (canid == 0x500):
                        canid_list.append(0x1000 + canid)
                        data_list.append(data)

                self.CanToH5.convert(canid_list, data_list, h5grp)

        return rawdata_header


    def get_image_from_cam_file(self, fnamepath, h5file):
        """
        ------.cam--------------
        * file header(92byte)
        device name(string) : 50byte
        device kind(string) : 10byte
        start date-time(string) : 14byte
        end date-time(string) : 14byte
        data count(int) : 4byte
        webcam type(int) : 4byte
        width(int) : 4byte
        height(int) : 4byte
        """
        camdata_header = {}
        with fnamepath.open(mode='rb') as f:
            camdata_header['devicename'] = unpack('50s', f.read(50))[0].decode('utf-8').strip()
            camdata_header['devicekind'] = unpack('10s', f.read(10))[0].decode('utf-8').strip()
            camdata_header['startdate'] = unpack('14s', f.read(14))[0].decode('utf-8').strip()
            camdata_header['enddate'] = unpack('14s', f.read(14))[0].decode('utf-8').strip()
            camdata_header['datacount'] = unpack('i', f.read(4))[0]
            camdata_header['webcamtype'] = unpack('i', f.read(4))[0]
            camdata_header['width'] = unpack('i', f.read(4))[0]
            camdata_header['height'] = unpack('i', f.read(4))[0]

            """
            ========================== 1 frame ==========================
            * data-header(16 byte)
            frame number(int) : 4byte
            total data size(int) : 4byte  (앞부분 8byte를 제외한 1frame의 전체사이즈)
            current time(long) : 8byte
            
            * webcam data
              jpeg (byte[]) : jpeg데이터   (total data size - 8이 jpeg의 데이터길이)
            ========================== 1 frame ==========================
            """
            for scan in range(camdata_header['datacount']):
                framenumber, datasize, currenttime = unpack('iiq', f.read(16))
                jpgsize = datasize - 8
                jpgbuff = f.read(jpgsize)

                grpname = 'SCAN_{:05d}'.format(scan + 1)
                if grpname in h5file.keys():
                    h5grp = h5file[grpname]
                    jpglen = len(jpgbuff)
                    image = h5grp.create_dataset('image_0', (jpglen,), dtype=np.uint8)
                    image[:] = np.frombuffer(jpgbuff, dtype=np.uint8)

        return camdata_header


    def get_logfiles_info(self, rootdir):
        gtdatadir = rootdir
        outdirname = 'OUT'

        rdafnames = list(Path(rootdir).glob('./**/*.rda'))
        rawfnames = list(Path(rootdir).glob('./**/*.dat'))
        rawidxfnames = [Path(rawfname.parent, rawfname.stem + '.idx') for rawfname in rawfnames]
        camfnames = list(Path(rootdir).glob('./**/*.cam'))
        camidxfnames = [Path(camfname.parent, camfname.stem + '.idx') for camfname in camfnames]
        outdirpaths = [Path(rootdir, s.parent, outdirname) for s in rdafnames]

        gtdatadirpath = Path(gtdatadir)

        logfnameinfolist = []
        for i in range(len(rdafnames)):

            print('rda file : ', rdafnames[i])
            print('raw file : ', rawfnames[i])
            print('raw index file : ', rawidxfnames[i])
            if camfnames != []:
                print('cam (jpeg steam) file : ', camfnames[i])
                print('cam index file : ', camidxfnames[i])
            else:
                camfnames = [None]
                camidxfnames = [None]
            print('output directory : ', str(outdirpaths[i].resolve()))

            logfnameinfo = dict(rootdir=rootdir,
                                rdafname=rdafnames[i],
                                rawfname=rawfnames[i],
                                rawidxfname=rawidxfnames[i],
                                camfname=camfnames[i],
                                camidxfname=camidxfnames[i],
                                gtdatadirpath=gtdatadirpath,
                                outdirpath=outdirpaths[i],
                                display=len(rdafnames))

            print(logfnameinfo)
            logfnameinfolist.append(logfnameinfo)

        return logfnameinfo


    def convert_dat_to_hdf5(self, rootdir):

        logfnameinfo = self.get_logfiles_info(rootdir)
        outputpath = Path(logfnameinfo['outdirpath'])
        outputpath.mkdir(exist_ok=True)
        hdf5fpath = Path(outputpath, remove_ko(logfnameinfo['rawfname'].stem) + '.h5')

        h5file = h5py.File(str(hdf5fpath.resolve()), 'w')

        rawdatinfo = self.get_data_from_raw_file(logfnameinfo['rawfname'], h5file)
        print('rawdatinfo:')
        pprint(rawdatinfo)

        if logfnameinfo['camfname'] is not None:
            caminfo = self.get_image_from_cam_file(logfnameinfo['camfname'], h5file)
            print('caminfo:')
            pprint(caminfo)
        else:
            caminfo = []

        if len(caminfo):
            cam_enabled = True
        else:
            print('No Cam data')
            cam_enabled = False


if __name__ == '__main__':
    from tkinter import filedialog, Tk
    max_scan_count = 0
    # folder_selected = 'C:/work/LoggingData/test/test_00001_191209_181246'
    folder_selected = ''
    if not folder_selected:
        root = Tk()
        root.withdraw()
        folder_selected = filedialog.askdirectory(initialdir='./')
        print(folder_selected)

    if folder_selected.strip():
        rootdir = folder_selected
    else:
        rootdir = './'

        raw2h5 = rawfile_to_hdf5(1, RadarType='MRR')
        raw2h5.convert_dat_to_hdf5(rootdir)

    # sys.exit()

    # pool = Pool(os.cpu_count() - 1)
    # with tqdm(total=len(logfnameinfolist)) as pbar:
    #     for _ in tqdm(pool.imap_unordered(convert_ra_to_hdf5_at_group, logfnameinfolist)):
    #         pbar.update()
    # pool.close()
    # pool.join()
