import sys
from PyQt5 import QtWidgets
import numpy as np
import QtDesign.FFTChMag_UI as QtUI



app = QtWidgets.QApplication(sys.argv)
NumCh = 4
ChTag = ['Ch1', 'Ch2', 'Ch3', 'Ch4']


class FFTChMag_UI:
    def __init__(self, DataIdx, **opts):

        self.opts = {
            'title': '',
        }
        self.opts.update(opts)
        self.DataIdx = DataIdx

        self.Form = QtWidgets.QWidget()
        self.UI_Form = QtUI.Ui_Form()
        self.UI_Form.setupUi(self.Form)

        self.PlotTemplate1_R = []
        self.PlotTemplate1_D = []
        self.DataPlot1_R = []
        self.DataPlot1_D = []

        self.PlotTemplate2_R = []
        self.PlotTemplate2_D = []
        self.DataPlot2_R = []
        self.DataPlot2_D = []

        self.FreqIdx1_R = -1
        self.FreqIdx1_D = -1
        self.FreqIdx2_R = -1
        self.FreqIdx2_D = -1

        self.Data1 = [[]] * NumCh
        self.Data2 = [[]] * NumCh

        self.Data1_FFT_imag = [[]] * NumCh
        self.Data1_FFT_real = [[]] * NumCh
        self.Data2_FFT_imag = [[]] * NumCh
        self.Data2_FFT_real = [[]] * NumCh

        self.FFTChMag_R = [[0 for cols in range(256)] for rows in range(NumCh)]
        self.FFTChMag_D = [[0 for cols in range(128)] for rows in range(NumCh)]


        for idx in range(NumCh):
            self.PlotTemplate1_R.append(self.UI_Form.graphicsView_R.addPlot(title=self.opts['title'] + '(Range) - ' + ChTag[idx]))
            self.PlotTemplate1_D.append(self.UI_Form.graphicsView_D.addPlot(title=self.opts['title'] + '(Doppler) - ' + ChTag[idx]))
            self.UI_Form.graphicsView_R.nextRow()
            self.UI_Form.graphicsView_D.nextRow()

            self.PlotTemplate2_R.append(self.UI_Form.graphicsView_R_2.addPlot(title=self.opts['title'] + '(Range) - ' + ChTag[idx]))
            self.PlotTemplate2_D.append(self.UI_Form.graphicsView_D_2.addPlot(title=self.opts['title'] + '(Doppler) - ' + ChTag[idx]))
            self.UI_Form.graphicsView_R_2.nextRow()
            self.UI_Form.graphicsView_D_2.nextRow()

        for idx in range(NumCh):
            self.DataPlot1_R.append(self.PlotTemplate1_R[idx].plot(pen='y'))
            self.DataPlot1_D.append(self.PlotTemplate1_D[idx].plot(pen='g'))
            self.DataPlot2_R.append(self.PlotTemplate2_R[idx].plot(pen='y'))
            self.DataPlot2_D.append(self.PlotTemplate2_D[idx].plot(pen='g'))

        self.UI_Form.pushButton.clicked.connect(self.SetIndex)
        self.UI_Form.pushButton_2.clicked.connect(self.SetIndex)
        self.UI_Form.tabWidget.currentChanged.connect(self.pltData)



    def SetIndex(self):
        if self.UI_Form.tabWidget.currentIndex() == 0:
            EditIdx_R = self.UI_Form.lineEdit_R.text()
            EditIdx_D = self.UI_Form.lineEdit_D.text()
            if EditIdx_R.isdigit():
                self.FreqIdx1_R = int(EditIdx_R)
            if EditIdx_D.isdigit():
                self.FreqIdx1_D = int(EditIdx_D)

        elif self.UI_Form.tabWidget.currentIndex() == 1:
            EditIdx_R = self.UI_Form.lineEdit_R_2.text()
            EditIdx_D = self.UI_Form.lineEdit_D_2.text()
            if EditIdx_R.isdigit():
                self.FreqIdx2_R = int(EditIdx_R)
            if EditIdx_D.isdigit():
                self.FreqIdx2_D = int(EditIdx_D)

        self.pltData()


    def SetData(self, ScanData):
        if ScanData[self.DataIdx] is not None:
            self.Data1_FFT_real[0] = ScanData[self.DataIdx]['s16LR_FFT_Data_Ch0_real'].value
            self.Data1_FFT_imag[0] = ScanData[self.DataIdx]['s16LR_FFT_Data_Ch0_imag'].value
            self.Data1_FFT_real[1] = ScanData[self.DataIdx]['s16LR_FFT_Data_Ch1_real'].value
            self.Data1_FFT_imag[1] = ScanData[self.DataIdx]['s16LR_FFT_Data_Ch1_imag'].value
            self.Data1_FFT_real[2] = ScanData[self.DataIdx]['s16LR_FFT_Data_Ch2_real'].value
            self.Data1_FFT_imag[2] = ScanData[self.DataIdx]['s16LR_FFT_Data_Ch2_imag'].value
            self.Data1_FFT_real[3] = ScanData[self.DataIdx]['s16LR_FFT_Data_Ch3_real'].value
            self.Data1_FFT_imag[3] = ScanData[self.DataIdx]['s16LR_FFT_Data_Ch3_imag'].value

            self.Data2_FFT_real[0] = ScanData[self.DataIdx]['s16SR_FFT_Data_Ch0_real'].value
            self.Data2_FFT_imag[0] = ScanData[self.DataIdx]['s16SR_FFT_Data_Ch0_imag'].value
            self.Data2_FFT_real[1] = ScanData[self.DataIdx]['s16SR_FFT_Data_Ch1_real'].value
            self.Data2_FFT_imag[1] = ScanData[self.DataIdx]['s16SR_FFT_Data_Ch1_imag'].value
            self.Data2_FFT_real[2] = ScanData[self.DataIdx]['s16SR_FFT_Data_Ch2_real'].value
            self.Data2_FFT_imag[2] = ScanData[self.DataIdx]['s16SR_FFT_Data_Ch2_imag'].value
            self.Data2_FFT_real[3] = ScanData[self.DataIdx]['s16SR_FFT_Data_Ch3_real'].value
            self.Data2_FFT_imag[3] = ScanData[self.DataIdx]['s16SR_FFT_Data_Ch3_imag'].value

            self.pltData()


    def pltData(self):

        if self.UI_Form.tabWidget.currentIndex() == 0:
            selectedPlot_R = self.DataPlot1_R
            selectedPlot_D = self.DataPlot1_D
            FreqIdx_R = self.FreqIdx1_R
            FreqIdx_D = self.FreqIdx1_D
            FFT_real = self.Data1_FFT_real
            FFT_imag = self.Data1_FFT_imag
        elif self.UI_Form.tabWidget.currentIndex() == 1:
            selectedPlot_R = self.DataPlot2_R
            selectedPlot_D = self.DataPlot2_D
            FreqIdx_R = self.FreqIdx2_R
            FreqIdx_D = self.FreqIdx2_D
            FFT_real = self.Data2_FFT_real
            FFT_imag = self.Data2_FFT_imag


        for idx in range(len(FFT_real)):
            if 0 <= FreqIdx_D < len(FFT_real[0][0]):
                xData = np.linspace(0, len(FFT_real[idx])-1, len(FFT_real[idx]))
                for m in range(len(FFT_real[idx])-1):
                    self.FFTChMag_R[idx][m] = np.sqrt((FFT_real[idx][m, FreqIdx_D] ** 2) + (FFT_imag[idx][m, FreqIdx_D] ** 2))
                Data = self.FFTChMag_R
                yData = Data[idx]

            else:
                xData = []
                yData = []

            selectedPlot_R[idx].setData(x=xData, y=yData)

            if 0 <= FreqIdx_R < len(FFT_real[0]):
                xData = np.linspace(0, len(FFT_real[idx][0])-1, len(FFT_real[idx][0]))
                for m in range(len(FFT_real[idx][0])-1):
                    self.FFTChMag_D[idx][m] = np.sqrt((FFT_real[idx][FreqIdx_R, m] ** 2) + (FFT_imag[idx][FreqIdx_R, m] ** 2))
                Data = self.FFTChMag_D
                yData = Data[idx]
            else:
                xData = []
                yData = []

            selectedPlot_D[idx].setData(x=xData, y=yData)

