import os
import logging
import logging.handlers
import datetime
import CanLibs.canlib as canlib
import time

_PCAN_CH_ = 0
ResTimMax = 5000


class pcanComm:
    def __init__(self, canch=1):

        foldername = os.getcwd()
        filename = datetime.datetime.now().strftime('%Y%m%d_%H%M%S')
        LoggingDir = foldername + '/CanLoggingData/CanData/'

        '''
        if not os.path.exists(LoggingDir):
            os.makedirs(LoggingDir)
        logfile = LoggingDir + filename + '_PCAN.asc'

        # ascii logger(EOL_BY_CAN type)
        self.pcan_asc = logging.getLogger('__PCAN_ASC__')
        self.pcan_asc_format = logging.Formatter('%(message)s')  # create file Handler
        self.pcan_asc_handler = logging.handlers.RotatingFileHandler(logfile, maxBytes=(10 * 1024 * 1024),
                                                                     backupCount=10)
        self.pcan_asc_handler.setLevel(logging.DEBUG)
        self.pcan_asc_handler.setFormatter(self.pcan_asc_format)
        self.pcan_asc.addHandler(self.pcan_asc_handler)
        self.pcan_asc.setLevel(logging.DEBUG)
        '''

        self.canch = canch

        self.cl = canlib.canlib()
        num_channels = self.cl.getNumberOfChannels()
        print("Found %d channels" % num_channels)
        for ch in range(0, num_channels):
            print("%d. %s (%s / %s)" % (ch, self.cl.getChannelData_Name(ch),
                                        self.cl.getChannelData_EAN(ch),
                                        self.cl.getChannelData_Serial(ch)))

        self.handle = self.cl.openChannel(self.canch, canlib.canOPEN_CAN_FD)
        print("Using channel %d: %s, EAN: %s" % (self.canch, self.handle.getChannelData_Name(),
                                                 self.handle.getChannelData_EAN()))

        self.handle.setBusOutputControl(canlib.canDRIVER_NORMAL)
        self.handle.setBusParams(canlib.canFD_BITRATE_1M_80P)
        self.handle.setBusParamsFd(canlib.canFD_BITRATE_4M_80P)
        self.handle.busOn()

        self.scanIndex = 0
        self.scanTime = 0
        self.ID = []
        self.RxBuff = []


    def flush_rx_buffer(self):
        self.handle.ioCtl_flush_rx_buffer()


    def send(self, _id, _dlc, _buff):
        _flag = 0
        _txbuff = [0] * 8
        _txbuff[0:_dlc] = _buff[0:_dlc]
        self.handle.write(_id, _txbuff[0:_dlc], _flag, _dlc)

        _time = self.handle.readTimer()
        self.pcan_asc.debug("%012.06f  %d %03X Tx d %d  %02X %02X %02X %02X %02X %02X %02X %02X"
                            % (_time / 1000, self.canch, _id, _dlc, _txbuff[0], _txbuff[1], _txbuff[2], _txbuff[3],
                               _txbuff[4], _txbuff[5], _txbuff[6], _txbuff[7]))


    def recv(self, initCanID=0x001, finCanID=0x400, DebugOn=True):

        initflag = 0
        self.scanIndex = 0
        self.scanTime = 0
        self.ID = []
        self.RxBuff = []


        while True:
            tic = time.time()
            (can_id, can_msg, can_dlc, can_flg, can_time) = self.handle.read(ResTimMax)
            toc = time.time()
            if (toc - tic) > 0.1:
                print('time check:', (toc - tic))
                print('CAN ID :', can_id)

            if DebugOn:
                self.can_debug(can_id, can_msg, can_dlc, can_time)

            if can_id == initCanID:
                initflag = 1
                # scanIndex = int.from_bytes(_rxbuff[0:2], byteorder='little', signed=False)  # 2-byte
                # print(scanIndex)
                self.scanTime = can_time

                self.ID.append(can_id)
                Data64bit = int.from_bytes(can_msg, byteorder='little', signed=False)
                self.RxBuff.append(Data64bit)

            if initflag == 1:
                self.ID.append(can_id)
                Data64bit = int.from_bytes(can_msg, byteorder='little', signed=False)
                self.RxBuff.append(Data64bit)

                if can_id == finCanID:
                    #return (ID, RxBuff, 0, scanTime)
                    return



    def can_debug(self, _id, _msg, _dlc, _time):

        if _dlc == 8:
            self.pcan_asc.debug("%012.06f  %d %03X Rx d %2d  "
                                "%02X %02X %02X %02X %02X %02X %02X %02X"
                                % (_time / 1000, self.canch, _id, _dlc,
                                   _msg[0], _msg[1], _msg[2], _msg[3], _msg[4], _msg[5], _msg[6], _msg[7],
                                   ))

        elif _dlc == 16:
            self.pcan_asc.debug("%012.06f  %d %03X Rx d %2d  "
                                "%02X %02X %02X %02X %02X %02X %02X %02X "
                                "%02X %02X %02X %02X %02X %02X %02X %02X"
                                % (_time / 1000, self.canch, _id, _dlc,
                                   _msg[0], _msg[1], _msg[2], _msg[3], _msg[4], _msg[5], _msg[6], _msg[7],
                                   _msg[8], _msg[9], _msg[10], _msg[11], _msg[12], _msg[13], _msg[14], _msg[15],
                                   ))

        elif _dlc == 24:
            self.pcan_asc.debug("%012.06f  %d %03X Rx d %2d  "
                                "%02X %02X %02X %02X %02X %02X %02X %02X "
                                "%02X %02X %02X %02X %02X %02X %02X %02X "
                                "%02X %02X %02X %02X %02X %02X %02X %02X"
                                % (_time / 1000, self.canch, _id, _dlc,
                                   _msg[0], _msg[1], _msg[2], _msg[3], _msg[4], _msg[5], _msg[6], _msg[7],
                                   _msg[8], _msg[9], _msg[10], _msg[11], _msg[12], _msg[13], _msg[14], _msg[15],
                                   _msg[16], _msg[17], _msg[18], _msg[19], _msg[20], _msg[21], _msg[22], _msg[23],
                                   ))

        elif _dlc == 32:
            self.pcan_asc.debug("%012.06f  %d %03X Rx d %2d  "
                                "%02X %02X %02X %02X %02X %02X %02X %02X "
                                "%02X %02X %02X %02X %02X %02X %02X %02X "
                                "%02X %02X %02X %02X %02X %02X %02X %02X "
                                "%02X %02X %02X %02X %02X %02X %02X %02X"
                                % (_time / 1000, self.canch, _id, _dlc,
                                   _msg[0], _msg[1], _msg[2], _msg[3], _msg[4], _msg[5], _msg[6], _msg[7],
                                   _msg[8], _msg[9], _msg[10], _msg[11], _msg[12], _msg[13], _msg[14], _msg[15],
                                   _msg[16], _msg[17], _msg[18], _msg[19], _msg[20], _msg[21], _msg[22], _msg[23],
                                   _msg[24], _msg[25], _msg[26], _msg[27], _msg[28], _msg[29], _msg[30], _msg[31],
                                   ))

        elif _dlc == 48:
            self.pcan_asc.debug("%012.06f  %d %03X Rx d %2d  "
                                "%02X %02X %02X %02X %02X %02X %02X %02X "
                                "%02X %02X %02X %02X %02X %02X %02X %02X "
                                "%02X %02X %02X %02X %02X %02X %02X %02X "
                                "%02X %02X %02X %02X %02X %02X %02X %02X "
                                "%02X %02X %02X %02X %02X %02X %02X %02X "
                                "%02X %02X %02X %02X %02X %02X %02X %02X"
                                % (_time / 1000, self.canch, _id, _dlc,
                                   _msg[0], _msg[1], _msg[2], _msg[3], _msg[4], _msg[5], _msg[6], _msg[7],
                                   _msg[8], _msg[9], _msg[10], _msg[11], _msg[12], _msg[13], _msg[14], _msg[15],
                                   _msg[16], _msg[17], _msg[18], _msg[19], _msg[20], _msg[21], _msg[22], _msg[23],
                                   _msg[24], _msg[25], _msg[26], _msg[27], _msg[28], _msg[29], _msg[30], _msg[31],
                                   _msg[32], _msg[33], _msg[34], _msg[35], _msg[36], _msg[37], _msg[38], _msg[39],
                                   _msg[40], _msg[41], _msg[42], _msg[43], _msg[44], _msg[45], _msg[46], _msg[47],
                                   ))

        else:
            pass


if __name__ == '__main__':
    import keyboard

    pcan = pcanComm(_PCAN_CH_)
    pcan.flush_rx_buffer()

    while True:
        if keyboard.is_pressed('q'):  # if key 'q' is pressed
            break  # finishing the loop
        else:
            pass

        pcan.recv(0x4E0, 0x2FF)

