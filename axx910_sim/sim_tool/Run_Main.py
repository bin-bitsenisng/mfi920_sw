import sys, os
from pathlib import *
from PyQt5 import QtWidgets
import cv2
import threading
from PyQt5 import QtGui
import numpy as np
import h5py
from datetime import datetime
import time
import copy

sys.path.append('./QtDesign')
import QtDesign.RunROA_UI as QtUI
import Log_CanFDComm as pcanComm
import Log_CanToH5
import GUI_DataParsing as Parsing

PcanNum = 0
CAN_EN = True
num_seat = 3
plt_len = 100

app = QtWidgets.QApplication(sys.argv)
Form = QtWidgets.QMainWindow()
ROA_UI = QtUI.Ui_MainWindow()
ROA_UI.setupUi(Form)

last_cam = 0
for idx in range(10):
    cap = cv2.VideoCapture(idx)
    ret, frame = cap.read()
    if ret:
        last_cam = idx


class RunGUIClass:
    def __init__(self):
        self.cam = cv2.VideoCapture(last_cam)
        self.cam.set(cv2.CAP_PROP_FRAME_WIDTH, 1024)
        self.cam.set(cv2.CAP_PROP_FRAME_HEIGHT, 768)

        if CAN_EN is True:
            self.pcan = pcanComm.pcanComm(PcanNum)
            self.CanToH5 = Log_CanToH5.CanToH5(RadarType='MRR')

        self.xData = np.linspace(0, plt_len - 1, plt_len)
        self.yData = np.zeros((num_seat * 2, plt_len))
        self.data_plt = []
        self.logfilepath = []
        self.CurImg = []

    def __del__(self):
        if hasattr(self, 'cam_th'):
            self.cam_th.kill()
            self.cam_th.join()
        if hasattr(self, 'th'):
            self.th.kill()
            self.th.join()

    def ConnectWidget(self):

        # Connect Functions #
        ROA_UI.startButton.clicked.connect(self.startButton)
        ROA_UI.pushButton_Logging.clicked.connect(self.loggingButton)


    def startButton(self):

        if ROA_UI.startButton.isChecked():
            plt_template = []
            plt_template.append(ROA_UI.graphicsView_breath_L.addPlot(title='breath rate - Left'))
            plt_template.append(ROA_UI.graphicsView_heart_L.addPlot(title='heart rate - Left'))
            plt_template.append(ROA_UI.graphicsView_breath_C.addPlot(title='breath rate - Center'))
            plt_template.append(ROA_UI.graphicsView_heart_C.addPlot(title='heart rate - Center'))
            plt_template.append(ROA_UI.graphicsView_breath_R.addPlot(title='breath rate - Right'))
            plt_template.append(ROA_UI.graphicsView_heart_R.addPlot(title='heart rate - Right'))

            font = QtGui.QFont()
            font.setPixelSize(16)

            for idx in range(num_seat * 2):
                # plt_template[idx].setXRange(0, plt_len, padding=0)
                plt_template[idx].setContentsMargins(-20, 0, 0, 0)
                # plt_template[idx].setLabel('left', "value", units='rpm')
                # plt_template[idx].hideAxis('left')
                plt_template[idx].hideAxis('bottom')
                plt_template[idx].getAxis("left").tickFont = font
                plt_template[idx].getAxis("left").setStyle(tickTextOffset=0)
                plt_template[idx].setMouseEnabled(x=False, y=False)

            self.data_plt = []
            for idx in range(num_seat):
                self.data_plt.append(plt_template[idx * 2].plot(pen='y'))
                self.data_plt.append(plt_template[(idx * 2) + 1].plot(pen='r'))

            self.cam_th = threading.Thread(target=self.run_cam)
            self.cam_th.daemon = True
            self.cam_th.start()

            if CAN_EN is True:
                self.th = threading.Thread(target=self.run)
                self.th.daemon = True
                self.th.start()

        else:
            ROA_UI.graphicsView_breath_L.clear()
            ROA_UI.graphicsView_heart_L.clear()
            ROA_UI.graphicsView_breath_C.clear()
            ROA_UI.graphicsView_heart_C.clear()
            ROA_UI.graphicsView_breath_R.clear()
            ROA_UI.graphicsView_heart_R.clear()


    def loggingButton(self):

        if ROA_UI.startButton.isChecked():
            logpath = Path(datetime.now().strftime("./rec/MOD620_LoggingData_%y%m%d_%H%M%S"))
            logpath.mkdir(parents=True,  exist_ok=True)
            self.logfilepath = Path(logpath, 'MOD620_LoggingData.h5')

            ROA_UI.pushButton_Logging.setEnabled(False)


    def run_cam(self):

        # test
        if CAN_EN is False:
            ROA_UI.label_left.setPixmap(QtGui.QPixmap(":/ROA_Prefix/human1.png"))
            ROA_UI.label_center.setPixmap(QtGui.QPixmap(":/ROA_Prefix/human2.png"))
            ROA_UI.label_right.setPixmap(QtGui.QPixmap(":/ROA_Prefix/human3.png"))

        while ROA_UI.startButton.isChecked():
            retval, cvimg = self.cam.read()

            if retval is True:
                cvimg = cv2.flip(cvimg, 1)
                is_success, buffer = cv2.imencode(".jpg", cvimg)
                cvimg = cv2.cvtColor(cvimg, cv2.COLOR_BGR2RGB)
                h, w, c = cvimg.shape
                qImg = QtGui.QImage(cvimg.data, w, h, w * c, QtGui.QImage.Format_RGB888)
                pixmap = QtGui.QPixmap.fromImage(qImg)
                ROA_UI.label_video.setPixmap(pixmap)
                if is_success:
                    self.CurImg = buffer

        ROA_UI.label_video.setPixmap(QtGui.QPixmap(":/ROA_Prefix/bitsensing_CI_좌우조합형_컬러타입_1.png"))

        # test
        ROA_UI.label_left.setText("L")
        ROA_UI.label_center.setText("C")
        ROA_UI.label_right.setText("R")

    def run(self):

        seat_image_label = []
        seat_image_label.append(ROA_UI.label_left)
        seat_image_label.append(ROA_UI.label_center)
        seat_image_label.append(ROA_UI.label_right)
        image_path = []
        image_path.append(":/ROA_Prefix/human1.png")
        image_path.append(":/ROA_Prefix/human2.png")
        image_path.append(":/ROA_Prefix/human3.png")
        image_tag = []
        image_tag.append("L")
        image_tag.append("C")
        image_tag.append("R")

        prev_data = []
        next_data = []
        prev_data_img = []
        next_data_img = []
        prev_scan_cnt = 0
        next_data_cnt = 0

        num_prev_scan = ROA_UI.lineEdit_prev_scan.text()
        num_next_scan = ROA_UI.lineEdit_next_scan.text()
        if num_prev_scan.isdigit() and num_next_scan.isdigit():
            num_prev_scan = int(num_prev_scan)
            num_next_scan = int(num_next_scan)
            ROA_UI.lineEdit_prev_scan.setEnabled(False)
            ROA_UI.lineEdit_next_scan.setEnabled(False)

        else:
            ROA_UI.startButton.setChecked(False)
            ROA_UI.graphicsView_breath_L.clear()
            ROA_UI.graphicsView_heart_L.clear()
            ROA_UI.graphicsView_breath_C.clear()
            ROA_UI.graphicsView_heart_C.clear()
            ROA_UI.graphicsView_breath_R.clear()
            ROA_UI.graphicsView_heart_R.clear()

        while ROA_UI.startButton.isChecked():
            self.pcan.recv(0x001, 0x400, False)

            CanID = self.pcan.ID
            CanData = self.pcan.RxBuff
            RadarScanIdx = self.pcan.scanIndex
            RadarCanTime = self.pcan.scanTime

            self.CanToH5.convert(CanID, CanData)

            if not ROA_UI.pushButton_Logging.isEnabled():
                if next_data_cnt < num_next_scan:
                    next_data_cnt += 1
                    candata = copy.deepcopy(self.CanToH5.data)
                    imgdata = copy.deepcopy(self.CurImg)
                    next_data.append(candata)
                    next_data_img.append(imgdata)
                    print(f'Current Logging Scan : {next_data_cnt:05d} scan')
                else:
                    a1 = time.time()

                    h5file = h5py.File(str(self.logfilepath.resolve()), "a")
                    for idx in range(len(prev_data)):
                        group_name = 'SCAN_{:05d}'.format(idx + 1)
                        h5grp = h5file.create_group(group_name)

                        h5grp.create_dataset("Sim_SampleNumber", data=prev_data[idx]['SampleNum'], dtype='uint16')
                        h5grp.create_dataset("Sim_CycleTime", data=prev_data[idx]['CycleTime'], dtype='int16')
                        h5grp.create_dataset("Sim_ROAInfo", data=prev_data[idx]['ROAInfo'], dtype='int16')
                        h5grp.create_dataset("Sim_TimeData", data=prev_data[idx]['TimeData'], dtype='uint16')
                        h5grp.create_dataset("image_0", data=prev_data_img[idx], dtype='uint8')

                    for idx in range(len(next_data)):
                        group_name = 'SCAN_{:05d}'.format(len(prev_data) + idx + 1)
                        h5grp = h5file.create_group(group_name)

                        h5grp.create_dataset("Sim_SampleNumber", data=next_data[idx]['SampleNum'], dtype='uint16')
                        h5grp.create_dataset("Sim_CycleTime", data=next_data[idx]['CycleTime'], dtype='int16')
                        h5grp.create_dataset("Sim_ROAInfo", data=next_data[idx]['ROAInfo'], dtype='int16')
                        h5grp.create_dataset("Sim_TimeData", data=next_data[idx]['TimeData'], dtype='uint16')
                        h5grp.create_dataset("image_0", data=next_data_img[idx], dtype='uint8')

                    prev_scan_cnt = 0
                    prev_data = []
                    prev_data_img = []
                    h5file.close()
                    ROA_UI.pushButton_Logging.setEnabled(True)

                    a2 = time.time()
                    print(a2 - a1)

            else:
                next_data_cnt = 0
                next_data = []
                next_data_img = []
                candata = copy.deepcopy(self.CanToH5.data)
                imgdata = copy.deepcopy(self.CurImg)
                prev_data.append(candata)
                prev_data_img.append(imgdata)
                if prev_scan_cnt < num_prev_scan:
                    prev_scan_cnt += 1
                else:
                    prev_data.pop(0)
                    prev_data_img.pop(0)


            data_dict = []
            for idx in range(num_seat):
                data_dict.append(Parsing.ROADataParsing(self.CanToH5.data['ROAInfo'][idx]))

                if data_dict[idx]['presence'] == 1:
                    seat_image_label[idx].setPixmap(QtGui.QPixmap(image_path[idx]))
                else:
                    seat_image_label[idx].setText(image_tag[idx])

            # plot
            for idx in range(num_seat):
                b_idx = 2 * idx
                h_idx = (2 * idx) + 1

                self.yData[b_idx] = np.roll(self.yData[b_idx], -1)
                self.yData[b_idx][-1] = data_dict[idx]['breath_rate']
                if ROA_UI.startButton.isChecked():
                    self.data_plt[b_idx].setData(x=self.xData, y=self.yData[b_idx])

                self.yData[h_idx] = np.roll(self.yData[h_idx], -1)
                self.yData[h_idx][-1] = data_dict[idx]['heart_rate']
                if ROA_UI.startButton.isChecked():
                    self.data_plt[h_idx].setData(x=self.xData, y=self.yData[h_idx])

        ROA_UI.pushButton_Logging.setEnabled(True)
        ROA_UI.lineEdit_prev_scan.setEnabled(True)
        ROA_UI.lineEdit_next_scan.setEnabled(True)


# MAIN
if __name__ == '__main__':
    RunGUI = RunGUIClass()
    RunGUI.ConnectWidget()
    Form.show()
    sys.exit(app.exec_())