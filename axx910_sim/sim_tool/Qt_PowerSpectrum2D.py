import sys
from PyQt5 import QtWidgets
import numpy as np
import QtDesign.PowerSpectrum2D_UI as QtUI
import matplotlib.pyplot as plt
import matplotlib
#matplotlib.use('Qt5Agg')


jet = plt.get_cmap('jet')
app = QtWidgets.QApplication(sys.argv)


class PowSpec2D_UI:
    def __init__(self, DataIdx, **opts):

        self.opts = {
            'title': '',
        }
        self.opts.update(opts)
        self.DataIdx = DataIdx

        self.Form = QtWidgets.QWidget()
        self.UI_Form = QtUI.Ui_Form()
        self.UI_Form.setupUi(self.Form)
        self.Form.setWindowTitle(self.opts['title'])

        self.UI_Form.tabWidget.currentChanged.connect(self.pltData)

        self.Data1 = []
        self.Data2 = []
        self.Data3 = []
        self.Data4 = []

        self.Data5 = []
        self.Data6 = []
        self.Data7 = []
        self.Data8 = []

        self.Data9 = []
        self.Data10 = []
        self.Data11 = []
        self.Data12 = []



    def SetData(self, ScanData):
        if ScanData[self.DataIdx] is not None:
            self.Data1 = ScanData[self.DataIdx]['Sim_LR_PowSpectrum'].value
            self.Data2 = ScanData[self.DataIdx]['Sim_MR_PowSpectrum'].value
            self.Data3 = ScanData[self.DataIdx]['Sim_SR_PowSpectrum'].value
            self.Data4 = ScanData[self.DataIdx]['Sim_RM_PowSpectrum'].value

            self.Data5 = ScanData[self.DataIdx]['Sim_LR_PowSpectrum_log'].value
            self.Data6 = ScanData[self.DataIdx]['Sim_MR_PowSpectrum_log'].value
            self.Data7 = ScanData[self.DataIdx]['Sim_SR_PowSpectrum_log'].value
            self.Data8 = ScanData[self.DataIdx]['Sim_RM_PowSpectrum_log'].value

            self.Data9 = ScanData[self.DataIdx]['Sim_LR_PowSpectrum_mask'].value
            self.Data10 = ScanData[self.DataIdx]['Sim_MR_PowSpectrum_mask'].value
            self.Data11 = ScanData[self.DataIdx]['Sim_SR_PowSpectrum_mask'].value
            self.Data12 = ScanData[self.DataIdx]['Sim_RM_PowSpectrum_mask'].value

            self.pltData()


    def pltData(self):
        if self.UI_Form.tabWidget.currentIndex() == 0:
            SelectedView = self.UI_Form.graphicsView
            Data = self.Data1
            Data = np.transpose(Data)
        elif self.UI_Form.tabWidget.currentIndex() == 1:
            SelectedView = self.UI_Form.graphicsView_2
            Data = self.Data2
            Data = np.transpose(Data)
        elif self.UI_Form.tabWidget.currentIndex() == 2:
            SelectedView = self.UI_Form.graphicsView_3
            Data = self.Data3
            Data = np.transpose(Data)
        elif self.UI_Form.tabWidget.currentIndex() == 3:
            SelectedView = self.UI_Form.graphicsView_4
            Data = self.Data4
            Data = np.transpose(Data)
        elif self.UI_Form.tabWidget.currentIndex() == 4:
            SelectedView = self.UI_Form.graphicsView_5
            Data = self.Data5
            Data = np.transpose(Data)
        elif self.UI_Form.tabWidget.currentIndex() == 5:
            SelectedView = self.UI_Form.graphicsView_6
            Data = self.Data6
            Data = np.transpose(Data)
        elif self.UI_Form.tabWidget.currentIndex() == 6:
            SelectedView = self.UI_Form.graphicsView_7
            Data = self.Data7
            Data = np.transpose(Data)
        elif self.UI_Form.tabWidget.currentIndex() == 7:
            SelectedView = self.UI_Form.graphicsView_8
            Data = self.Data8
            Data = np.transpose(Data)
        elif self.UI_Form.tabWidget.currentIndex() == 8:
            SelectedView = self.UI_Form.graphicsView_9
            Data = self.Data9
            Data = np.transpose(Data)
        elif self.UI_Form.tabWidget.currentIndex() == 9:
            SelectedView = self.UI_Form.graphicsView_10
            Data = self.Data10
            Data = np.transpose(Data)
        elif self.UI_Form.tabWidget.currentIndex() == 10:
            SelectedView = self.UI_Form.graphicsView_11
            Data = self.Data11
            Data = np.transpose(Data)
        elif self.UI_Form.tabWidget.currentIndex() == 11:
            SelectedView = self.UI_Form.graphicsView_12
            Data = self.Data12
            Data = np.transpose(Data)



        #SelectedView.canvas.ax.clear()
        SelectedView.canvas.ax.imshow(Data, cmap=jet)
        #mpldatacursor.datacursor(hover=True, bbox=dict(alpha=1, fc='w'),
        #                         formatter='x = {i}\ny = {j}\nz = {z:.02g}'.format)
        SelectedView.canvas.draw()




