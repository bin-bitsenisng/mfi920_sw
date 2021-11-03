import sys
from PyQt5 import QtWidgets
import numpy as np
import pyqtgraph as pg
import QtDesign.PowerSpectrum_UI as QtUI



app = QtWidgets.QApplication(sys.argv)
BeamTag = ['LRR','MRR','SRR']
RefTag = ['Ref']
class PowSpec_UI:
    def __init__(self, DataIdx, **opts):

        self.opts = {
            'title': '',
        }
        self.opts.update(opts)
        self.DataIdx = DataIdx      # Radar Index

        self.Form = QtWidgets.QWidget()
        self.UI_Form = QtUI.Ui_Form()
        self.UI_Form.setupUi(self.Form)

        self.PlotTemplate1_R = []
        self.PlotTemplate1_D = []
        self.DataPlot1_R = []
        self.DataPlot1_D = []
        self.CFAR_BaseTh_Plot1_R = []
        self.CFAR_BaseTh_Plot1_D = []
        self.CFAR_Th_Plot1_R = []
        self.CFAR_Th_Plot1_D = []

        self.CFAR_Out_Plot1_R = []
        self.CFAR_Out_Plot1_D = []
        self.CFAR_Peak_Plot1_R = []
        self.CFAR_Peak_Plot1_D = []

        self.FreqIdx_R = -1
        self.FreqIdx_D = -1

        self.RadarIdx = -5
        self.RadarIdx_Ref = -5


        self.Ref_PowSpec = [[]]
        self.Ref_CFAR_BaseTh = [[]]
        self.Ref_CFAR_Th_R = [[]]
        self.Ref_CFAR_Th_D = [[]]
        self.Ref_CFAR_Out_R = [[]]
        self.Ref_CFAR_Out_D = [[]]
        self.Ref_CFAR_PeakCnt = [[]]
        self.Ref_CFAR_Peak_FreqIdx_R = [[]]
        self.Ref_CFAR_Peak_FreqIdx_D = [[]]

        self.PowSpec = [[]] * len(BeamTag)
        self.CFAR_BaseTh = [[]] * len(BeamTag)
        self.CFAR_Th_R = [[]] * len(BeamTag)
        self.CFAR_Th_D = [[]] * len(BeamTag)
        self.CFAR_Out_R = [[]] * len(BeamTag)
        self.CFAR_Out_D = [[]] * len(BeamTag)
        self.CFAR_PeakCnt = [[]] * len(BeamTag)
        self.CFAR_Peak_FreqIdx_R = [[]] * len(BeamTag)
        self.CFAR_Peak_FreqIdx_D = [[]] * len(BeamTag)


        self.PlotTemplate1_R.append(self.UI_Form.graphicsView_R.addPlot(title=self.opts['title'] + '(Range)'))
        self.PlotTemplate1_D.append(self.UI_Form.graphicsView_D.addPlot(title=self.opts['title'] + '(Doppler)'))

        self.DataPlot1_R.append(self.PlotTemplate1_R[0].plot(pen='y'))
        self.DataPlot1_D.append(self.PlotTemplate1_D[0].plot(pen='g'))

        self.CFAR_BaseTh_Plot1_R.append(self.PlotTemplate1_R[0].plot(pen=pg.mkPen(color=(255,0,0,200), width=3.0)))
        self.CFAR_BaseTh_Plot1_D.append(self.PlotTemplate1_D[0].plot(pen=pg.mkPen(color=(255,0,0,200), width=3.0)))

        self.CFAR_Th_Plot1_R.append(self.PlotTemplate1_R[0].plot(pen='c'))
        self.CFAR_Th_Plot1_D.append(self.PlotTemplate1_D[0].plot(pen='c'))

        self.CFAR_Out_Plot1_R.append(self.PlotTemplate1_R[0].plot(pen=None, symbol='x', symbolBrush='b', symbolPen='w'))
        self.CFAR_Out_Plot1_D.append(self.PlotTemplate1_D[0].plot(pen=None, symbol='x', symbolBrush='b', symbolPen='w'))

        self.CFAR_Peak_Plot1_R.append(self.PlotTemplate1_R[0].plot(pen=None, symbol='o', symbolBrush='r', symbolPen='w'))
        self.CFAR_Peak_Plot1_D.append(self.PlotTemplate1_D[0].plot(pen=None, symbol='o', symbolBrush='r', symbolPen='w'))

        self.ref_sig = 0
        self.det_sig = 0

        self.UI_Form.pushButton.clicked.connect(self.Ref_Index)
        self.UI_Form.pushButton2.clicked.connect(self.LRR_Index)
        self.UI_Form.pushButton3.clicked.connect(self.MRR_Index)
        self.UI_Form.pushButton4.clicked.connect(self.SRR_Index)

        self.UI_Form.tabWidget.currentChanged.connect(self.pltData)



    def LRR_Index(self):
        self.RadarIdx = 0
        EditIdx_R = self.UI_Form.lineEdit_R.text()
        EditIdx_D = self.UI_Form.lineEdit_D.text()
        if EditIdx_D.isdigit():
            self.FreqIdx_D = int(EditIdx_D)
        if EditIdx_R.isdigit():
            self.FreqIdx_R = int(EditIdx_R)

        self.pltData()

    def MRR_Index(self):
        self.RadarIdx = 1
        EditIdx_R = self.UI_Form.lineEdit_R.text()
        EditIdx_D = self.UI_Form.lineEdit_D.text()
        if EditIdx_D.isdigit():
            self.FreqIdx_D = int(EditIdx_D)
        if EditIdx_R.isdigit():
            self.FreqIdx_R = int(EditIdx_R)

        self.pltData()

    def SRR_Index(self):
        self.RadarIdx = 2
        EditIdx_R = self.UI_Form.lineEdit_R.text()
        EditIdx_D = self.UI_Form.lineEdit_D.text()
        if EditIdx_D.isdigit():
            self.FreqIdx_D = int(EditIdx_D)
        if EditIdx_R.isdigit():
            self.FreqIdx_R = int(EditIdx_R)

        self.pltData()

    def Ref_Index(self):
        self.RadarIdx_Ref = 0
        EditIdx_R = self.UI_Form.lineEdit_R.text()
        EditIdx_D = self.UI_Form.lineEdit_D.text()
        if EditIdx_R.isdigit():
            self.FreqIdx_R = int(EditIdx_R)
        if EditIdx_D.isdigit():
            self.FreqIdx_D = int(EditIdx_D)

        self.pltData()



    def SetData(self, ScanData):

        if ScanData[self.DataIdx] is not None:
            # Ref Mode
            self.Ref_PowSpec[0] = ScanData[self.DataIdx]['Sim_RM_PowSpectrum'].value
            self.Ref_CFAR_BaseTh[0] = ScanData[self.DataIdx]['Sim_RM_BaseTh'].value
            self.Ref_CFAR_Th_R[0] = ScanData[self.DataIdx]['Sim_RM_RangeCfarTh'].value
            self.Ref_CFAR_Th_D[0] = ScanData[self.DataIdx]['Sim_RM_DoppCfarTh'].value
            self.Ref_CFAR_Out_R[0] = ScanData[self.DataIdx]['Sim_RM_RangeCfarOut'].value
            self.Ref_CFAR_Out_D[0] = ScanData[self.DataIdx]['Sim_RM_DoppCfarOut'].value
            self.Ref_CFAR_PeakCnt[0] = ScanData[self.DataIdx]['Sim_RM_PeakCnt'].value
            self.Ref_CFAR_Peak_FreqIdx_R[0] = ScanData[self.DataIdx]['Sim_RM_PeakData'].value[:, 0]
            self.Ref_CFAR_Peak_FreqIdx_D[0] = ScanData[self.DataIdx]['Sim_RM_PeakData'].value[:, 1]

            # Long Range Mode
            self.PowSpec[0] = ScanData[self.DataIdx]['Sim_LR_PowSpectrum'].value
            self.CFAR_BaseTh[0] = ScanData[self.DataIdx]['Sim_LR_BaseTh'].value
            self.CFAR_Th_R[0] = ScanData[self.DataIdx]['Sim_LR_RangeCfarTh'].value
            self.CFAR_Th_D[0] = ScanData[self.DataIdx]['Sim_LR_DoppCfarTh'].value
            self.CFAR_Out_R[0] = ScanData[self.DataIdx]['Sim_LR_RangeCfarOut'].value
            self.CFAR_Out_D[0] = ScanData[self.DataIdx]['Sim_LR_DoppCfarOut'].value
            self.CFAR_PeakCnt[0] = ScanData[self.DataIdx]['Sim_LR_PeakCnt'].value
            self.CFAR_Peak_FreqIdx_R[0] = ScanData[self.DataIdx]['Sim_LR_PeakData'].value[:, 0]
            self.CFAR_Peak_FreqIdx_D[0] = ScanData[self.DataIdx]['Sim_LR_PeakData'].value[:, 1]

            # Middle Range Mode
            self.PowSpec[1] = ScanData[self.DataIdx]['Sim_MR_PowSpectrum'].value
            self.CFAR_BaseTh[1] = ScanData[self.DataIdx]['Sim_MR_BaseTh'].value
            self.CFAR_Th_R[1] = ScanData[self.DataIdx]['Sim_MR_RangeCfarTh'].value
            self.CFAR_Th_D[1] = ScanData[self.DataIdx]['Sim_MR_DoppCfarTh'].value
            self.CFAR_Out_R[1] = ScanData[self.DataIdx]['Sim_MR_RangeCfarOut'].value
            self.CFAR_Out_D[1] = ScanData[self.DataIdx]['Sim_MR_DoppCfarOut'].value
            self.CFAR_PeakCnt[1] = ScanData[self.DataIdx]['Sim_MR_PeakCnt'].value
            self.CFAR_Peak_FreqIdx_R[1] = ScanData[self.DataIdx]['Sim_MR_PeakData'].value[:, 0]
            self.CFAR_Peak_FreqIdx_D[1] = ScanData[self.DataIdx]['Sim_MR_PeakData'].value[:, 1]

            # Short Range Mode
            self.PowSpec[2] = ScanData[self.DataIdx]['Sim_SR_PowSpectrum'].value
            self.CFAR_BaseTh[2] = ScanData[self.DataIdx]['Sim_SR_BaseTh'].value
            self.CFAR_Th_R[2] = ScanData[self.DataIdx]['Sim_SR_RangeCfarTh'].value
            self.CFAR_Th_D[2] = ScanData[self.DataIdx]['Sim_SR_DoppCfarTh'].value
            self.CFAR_Out_R[2] = ScanData[self.DataIdx]['Sim_SR_RangeCfarOut'].value
            self.CFAR_Out_D[2] = ScanData[self.DataIdx]['Sim_SR_DoppCfarOut'].value
            self.CFAR_PeakCnt[2] = ScanData[self.DataIdx]['Sim_SR_PeakCnt'].value
            self.CFAR_Peak_FreqIdx_R[2] = ScanData[self.DataIdx]['Sim_SR_PeakData'].value[:, 0]
            self.CFAR_Peak_FreqIdx_D[2] = ScanData[self.DataIdx]['Sim_SR_PeakData'].value[:, 1]

            self.pltData()


    def pltData(self):

        selectedPlot1_R = self.DataPlot1_R
        selectedPlot1_D = self.DataPlot1_D
        selectedPlot2_R = self.CFAR_BaseTh_Plot1_R
        selectedPlot2_D = self.CFAR_BaseTh_Plot1_D
        selectedPlot3_R = self.CFAR_Th_Plot1_R
        selectedPlot3_D = self.CFAR_Th_Plot1_D
        selectedPlot4_R = self.CFAR_Out_Plot1_R
        selectedPlot4_D = self.CFAR_Out_Plot1_D
        selectedPlot5_R = self.CFAR_Peak_Plot1_R
        selectedPlot5_D = self.CFAR_Peak_Plot1_D


        radarIdx = self.RadarIdx

        radarIdx_ref = self.RadarIdx_Ref

        FreqIdx_R = self.FreqIdx_R
        FreqIdx_D = self.FreqIdx_D



        PowSpec = self.PowSpec
        CFAR_Th_R = self.CFAR_Th_R
        CFAR_Th_D = self.CFAR_Th_D
        CFAR_Out_R = self.CFAR_Out_R
        CFAR_Out_D = self.CFAR_Out_D
        CFAR_PeakCnt = self.CFAR_PeakCnt
        CFAR_Peak_FreqIdx_R = self.CFAR_Peak_FreqIdx_R
        CFAR_Peak_FreqIdx_D = self.CFAR_Peak_FreqIdx_D
        CFAR_BaseTh = self.CFAR_BaseTh

        Ref_PowSpec = self.Ref_PowSpec
        Ref_CFAR_Th_R = self.Ref_CFAR_Th_R
        Ref_CFAR_Th_D = self.Ref_CFAR_Th_D
        Ref_CFAR_Out_R = self.Ref_CFAR_Out_R
        Ref_CFAR_Out_D = self.Ref_CFAR_Out_D
        Ref_CFAR_PeakCnt = self.Ref_CFAR_PeakCnt
        Ref_CFAR_Peak_FreqIdx_R = self.Ref_CFAR_Peak_FreqIdx_R
        Ref_CFAR_Peak_FreqIdx_D = self.Ref_CFAR_Peak_FreqIdx_D
        Ref_CFAR_BaseTh = self.Ref_CFAR_BaseTh

        if radarIdx >=0:
            self.RadarIdx = -5
            if BeamTag[radarIdx] == 'LRR':
                print('LRR')

                idx = 0
                xData = []
                yData = []
                BaseTh_yData = []
                x_CFAR_Th = []
                y_CFAR_Th = []
                x_CFAR_Out = []
                y_CFAR_Out = []
                CFAR_PeakIdx = []
                CFAR_PeakVal = []

                if PowSpec[idx] is not None:
                    size_D = len(PowSpec[idx][0])
                    if 0 <= FreqIdx_R < len(PowSpec[idx]):
                        xData = np.linspace(0, len(PowSpec[idx][0]) - 1, len(PowSpec[idx][0]))
                        yData = PowSpec[idx][FreqIdx_R]
                        BaseTh_yData = np.zeros(size_D) + CFAR_BaseTh[idx]
                        for m in range(size_D):
                            if CFAR_Th_D[idx][FreqIdx_R, m] > 0:
                                x_CFAR_Th.append(m)
                                y_CFAR_Th.append(CFAR_Th_D[idx][FreqIdx_R, m])
                            if CFAR_Out_D[idx][FreqIdx_R, m] == 1:
                                x_CFAR_Out.append(m)
                                y_CFAR_Out.append(PowSpec[idx][FreqIdx_R, m])
                        for m in range(CFAR_PeakCnt[idx][0]):
                            temp_idx_R = int(CFAR_Peak_FreqIdx_R[idx][m])
                            temp_idx_D = int(CFAR_Peak_FreqIdx_D[idx][m])
                            if temp_idx_R == FreqIdx_R:
                                CFAR_PeakIdx.append(temp_idx_D)
                                CFAR_PeakVal.append(PowSpec[idx][temp_idx_R, temp_idx_D])

                selectedPlot1_R[0].setData(xData, yData)
                selectedPlot2_R[0].setData(xData, BaseTh_yData)
                selectedPlot3_R[0].setData(x_CFAR_Th, y_CFAR_Th)
                selectedPlot4_R[0].setData(x_CFAR_Out, y_CFAR_Out)
                selectedPlot5_R[0].setData(CFAR_PeakIdx, CFAR_PeakVal)

                xData = []
                yData = []
                BaseTh_yData = []
                x_CFAR_Th = []
                y_CFAR_Th = []
                x_CFAR_Out = []
                y_CFAR_Out = []
                CFAR_PeakIdx = []
                CFAR_PeakVal = []

                if PowSpec[idx] is not None:
                    size_R = len(PowSpec[idx])
                    if 0 <= FreqIdx_D < len(PowSpec[idx][0]):
                        xData = np.linspace(0, len(PowSpec[idx]) - 1, len(PowSpec[idx]))
                        yData = PowSpec[idx][:, FreqIdx_D]
                        BaseTh_yData = np.zeros(size_R) + CFAR_BaseTh[idx]
                        for m in range(size_R):
                            if CFAR_Th_R[idx][m, FreqIdx_D] > 0:
                                x_CFAR_Th.append(m)
                                y_CFAR_Th.append(CFAR_Th_R[idx][m, FreqIdx_D])
                            if CFAR_Out_R[idx][m, FreqIdx_D] == 1:
                                x_CFAR_Out.append(m)
                                y_CFAR_Out.append(PowSpec[idx][m, FreqIdx_D])
                        for m in range(CFAR_PeakCnt[idx][0]):
                            temp_idx_R = int(CFAR_Peak_FreqIdx_R[idx][m])
                            temp_idx_D = int(CFAR_Peak_FreqIdx_D[idx][m])
                            if temp_idx_D == FreqIdx_D:
                                CFAR_PeakIdx.append(temp_idx_R)
                                CFAR_PeakVal.append(PowSpec[idx][temp_idx_R, temp_idx_D])

                selectedPlot1_D[0].setData(xData, yData)
                selectedPlot2_D[0].setData(xData, BaseTh_yData)
                selectedPlot3_D[0].setData(x_CFAR_Th, y_CFAR_Th)
                selectedPlot4_D[0].setData(x_CFAR_Out, y_CFAR_Out)
                selectedPlot5_D[0].setData(CFAR_PeakIdx, CFAR_PeakVal)

            elif BeamTag[radarIdx] == 'MRR':
                print('MRR')

                idx = 1
                xData = []
                yData = []
                BaseTh_yData = []
                x_CFAR_Th = []
                y_CFAR_Th = []
                x_CFAR_Out = []
                y_CFAR_Out = []
                CFAR_PeakIdx = []
                CFAR_PeakVal = []

                if PowSpec[idx] is not None:
                    size_D = len(PowSpec[idx][0])
                    if 0 <= FreqIdx_R < len(PowSpec[idx]):
                        xData = np.linspace(0, len(PowSpec[idx][0]) - 1, len(PowSpec[idx][0]))
                        yData = PowSpec[idx][FreqIdx_R]
                        BaseTh_yData = np.zeros(size_D) + CFAR_BaseTh[idx]
                        for m in range(size_D):
                            if CFAR_Th_D[idx][FreqIdx_R, m] > 0:
                                x_CFAR_Th.append(m)
                                y_CFAR_Th.append(CFAR_Th_D[idx][FreqIdx_R, m])
                            if CFAR_Out_D[idx][FreqIdx_R, m] == 1:
                                x_CFAR_Out.append(m)
                                y_CFAR_Out.append(PowSpec[idx][FreqIdx_R, m])
                        for m in range(CFAR_PeakCnt[idx][0]):
                            temp_idx_R = int(CFAR_Peak_FreqIdx_R[idx][m])
                            temp_idx_D = int(CFAR_Peak_FreqIdx_D[idx][m])
                            if temp_idx_R == FreqIdx_R:
                                CFAR_PeakIdx.append(temp_idx_D)
                                CFAR_PeakVal.append(PowSpec[idx][temp_idx_R, temp_idx_D])

                selectedPlot1_R[0].setData(xData, yData)
                selectedPlot2_R[0].setData(xData, BaseTh_yData)
                selectedPlot3_R[0].setData(x_CFAR_Th, y_CFAR_Th)
                selectedPlot4_R[0].setData(x_CFAR_Out, y_CFAR_Out)
                selectedPlot5_R[0].setData(CFAR_PeakIdx, CFAR_PeakVal)

                xData = []
                yData = []
                BaseTh_yData = []
                x_CFAR_Th = []
                y_CFAR_Th = []
                x_CFAR_Out = []
                y_CFAR_Out = []
                CFAR_PeakIdx = []
                CFAR_PeakVal = []

                if PowSpec[idx] is not None:
                    size_R = len(PowSpec[idx])
                    if 0 <= FreqIdx_D < len(PowSpec[idx][0]):
                        xData = np.linspace(0, len(PowSpec[idx]) - 1, len(PowSpec[idx]))
                        yData = PowSpec[idx][:, FreqIdx_D]
                        BaseTh_yData = np.zeros(size_R) + CFAR_BaseTh[idx]
                        for m in range(size_R):
                            if CFAR_Th_R[idx][m, FreqIdx_D] > 0:
                                x_CFAR_Th.append(m)
                                y_CFAR_Th.append(CFAR_Th_R[idx][m, FreqIdx_D])
                            if CFAR_Out_R[idx][m, FreqIdx_D] == 1:
                                x_CFAR_Out.append(m)
                                y_CFAR_Out.append(PowSpec[idx][m, FreqIdx_D])
                        for m in range(CFAR_PeakCnt[idx][0]):
                            temp_idx_R = int(CFAR_Peak_FreqIdx_R[idx][m])
                            temp_idx_D = int(CFAR_Peak_FreqIdx_D[idx][m])
                            if temp_idx_D == FreqIdx_D:
                                CFAR_PeakIdx.append(temp_idx_R)
                                CFAR_PeakVal.append(PowSpec[idx][temp_idx_R, temp_idx_D])

                selectedPlot1_D[0].setData(xData, yData)
                selectedPlot2_D[0].setData(xData, BaseTh_yData)
                selectedPlot3_D[0].setData(x_CFAR_Th, y_CFAR_Th)
                selectedPlot4_D[0].setData(x_CFAR_Out, y_CFAR_Out)
                selectedPlot5_D[0].setData(CFAR_PeakIdx, CFAR_PeakVal)


            elif BeamTag[radarIdx] == 'SRR':
                print('SRR')

                xData = []
                yData = []
                BaseTh_yData = []
                x_CFAR_Th = []
                y_CFAR_Th = []
                x_CFAR_Out = []
                y_CFAR_Out = []
                CFAR_PeakIdx = []
                CFAR_PeakVal = []

                idx = 2
                if PowSpec[idx] is not None:
                    size_D = len(PowSpec[idx][0])
                    if 0 <= FreqIdx_R < len(PowSpec[idx]):
                        xData = np.linspace(0, len(PowSpec[idx][0]) - 1, len(PowSpec[idx][0]))
                        yData = PowSpec[idx][FreqIdx_R]
                        BaseTh_yData = np.zeros(size_D) + CFAR_BaseTh[idx]
                        for m in range(size_D):
                            if CFAR_Th_D[idx][FreqIdx_R, m] > 0:
                                x_CFAR_Th.append(m)
                                y_CFAR_Th.append(CFAR_Th_D[idx][FreqIdx_R, m])
                            if CFAR_Out_D[idx][FreqIdx_R, m] == 1:
                                x_CFAR_Out.append(m)
                                y_CFAR_Out.append(PowSpec[idx][FreqIdx_R, m])
                        for m in range(CFAR_PeakCnt[idx][0]):
                            temp_idx_R = int(CFAR_Peak_FreqIdx_R[idx][m])
                            temp_idx_D = int(CFAR_Peak_FreqIdx_D[idx][m])
                            if temp_idx_R == FreqIdx_R:
                                CFAR_PeakIdx.append(temp_idx_D)
                                CFAR_PeakVal.append(PowSpec[idx][temp_idx_R, temp_idx_D])

                selectedPlot1_R[0].setData(xData, yData)
                selectedPlot2_R[0].setData(xData, BaseTh_yData)
                selectedPlot3_R[0].setData(x_CFAR_Th, y_CFAR_Th)
                selectedPlot4_R[0].setData(x_CFAR_Out, y_CFAR_Out)
                selectedPlot5_R[0].setData(CFAR_PeakIdx, CFAR_PeakVal)

                xData = []
                yData = []
                BaseTh_yData = []
                x_CFAR_Th = []
                y_CFAR_Th = []
                x_CFAR_Out = []
                y_CFAR_Out = []
                CFAR_PeakIdx = []
                CFAR_PeakVal = []

                if PowSpec[idx] is not None:
                    size_R = len(PowSpec[idx])
                    if 0 <= FreqIdx_D < len(PowSpec[idx][0]):
                        xData = np.linspace(0, len(PowSpec[idx]) - 1, len(PowSpec[idx]))
                        yData = PowSpec[idx][:, FreqIdx_D]
                        BaseTh_yData = np.zeros(size_R) + CFAR_BaseTh[idx]
                        for m in range(size_R):
                            if CFAR_Th_R[idx][m, FreqIdx_D] > 0:
                                x_CFAR_Th.append(m)
                                y_CFAR_Th.append(CFAR_Th_R[idx][m, FreqIdx_D])
                            if CFAR_Out_R[idx][m, FreqIdx_D] == 1:
                                x_CFAR_Out.append(m)
                                y_CFAR_Out.append(PowSpec[idx][m, FreqIdx_D])
                        for m in range(CFAR_PeakCnt[idx][0]):
                            temp_idx_R = int(CFAR_Peak_FreqIdx_R[idx][m])
                            temp_idx_D = int(CFAR_Peak_FreqIdx_D[idx][m])
                            if temp_idx_D == FreqIdx_D:
                                CFAR_PeakIdx.append(temp_idx_R)
                                CFAR_PeakVal.append(PowSpec[idx][temp_idx_R, temp_idx_D])

                selectedPlot1_D[0].setData(xData, yData)
                selectedPlot2_D[0].setData(xData, BaseTh_yData)
                selectedPlot3_D[0].setData(x_CFAR_Th, y_CFAR_Th)
                selectedPlot4_D[0].setData(x_CFAR_Out, y_CFAR_Out)
                selectedPlot5_D[0].setData(CFAR_PeakIdx, CFAR_PeakVal)

        if radarIdx_ref >= 0:
            self.RadarIdx_Ref = -5
            if RefTag[radarIdx_ref] == 'Ref':
                print('Ref')

                xData = []
                yData = []
                BaseTh_yData = []
                x_CFAR_Th = []
                y_CFAR_Th = []
                x_CFAR_Out = []
                y_CFAR_Out = []
                CFAR_PeakIdx = []
                CFAR_PeakVal = []

                idx = 0

                if Ref_PowSpec[idx] is not None:
                    size_D = len(Ref_PowSpec[idx][0])

                    if 0 <= FreqIdx_R < len(Ref_PowSpec[idx]):
                        xData = np.linspace(0, len(Ref_PowSpec[idx][0]) - 1, len(Ref_PowSpec[idx][0]))
                        yData = Ref_PowSpec[idx][FreqIdx_R]
                        BaseTh_yData = np.zeros(size_D) + Ref_CFAR_BaseTh[idx]
                        for m in range(size_D):
                            if Ref_CFAR_Th_D[idx][FreqIdx_R, m] > 0:
                                x_CFAR_Th.append(m)
                                y_CFAR_Th.append(Ref_CFAR_Th_D[idx][FreqIdx_R, m])
                            if Ref_CFAR_Out_D[idx][FreqIdx_R, m] == 1:
                                x_CFAR_Out.append(m)
                                y_CFAR_Out.append(Ref_PowSpec[idx][FreqIdx_R, m])
                        for m in range(Ref_CFAR_PeakCnt[idx][0]):
                            temp_idx_R = int(Ref_CFAR_Peak_FreqIdx_R[idx][m])
                            temp_idx_D = int(Ref_CFAR_Peak_FreqIdx_D[idx][m])
                            if temp_idx_R == FreqIdx_R:
                                CFAR_PeakIdx.append(temp_idx_D)
                                CFAR_PeakVal.append(Ref_PowSpec[idx][temp_idx_R, temp_idx_D])

                selectedPlot1_R[0].setData(xData, yData)
                selectedPlot2_R[0].setData(xData, BaseTh_yData)
                selectedPlot3_R[0].setData(x_CFAR_Th, y_CFAR_Th)
                selectedPlot4_R[0].setData(x_CFAR_Out, y_CFAR_Out)
                selectedPlot5_R[0].setData(CFAR_PeakIdx, CFAR_PeakVal)

                xData = []
                yData = []
                BaseTh_yData = []
                x_CFAR_Th = []
                y_CFAR_Th = []
                x_CFAR_Out = []
                y_CFAR_Out = []
                CFAR_PeakIdx = []
                CFAR_PeakVal = []

                if Ref_PowSpec[idx] is not None:
                    size_R = len(Ref_PowSpec[idx])

                    if 0 <= FreqIdx_D < len(Ref_PowSpec[idx][0]):
                        xData = np.linspace(0, len(Ref_PowSpec[idx]) - 1, len(Ref_PowSpec[idx]))
                        yData = Ref_PowSpec[idx][:, FreqIdx_D]
                        BaseTh_yData = np.zeros(size_R) + Ref_CFAR_BaseTh[idx]
                        for m in range(size_R):
                            if Ref_CFAR_Th_R[idx][m, FreqIdx_D] > 0:
                                x_CFAR_Th.append(m)
                                y_CFAR_Th.append(Ref_CFAR_Th_R[idx][m, FreqIdx_D])
                            if Ref_CFAR_Out_R[idx][m, FreqIdx_D] == 1:
                                x_CFAR_Out.append(m)
                                y_CFAR_Out.append(Ref_PowSpec[idx][m, FreqIdx_D])
                        for m in range(CFAR_PeakCnt[idx][0]):
                            temp_idx_R = int(Ref_CFAR_Peak_FreqIdx_R[idx][m])
                            temp_idx_D = int(Ref_CFAR_Peak_FreqIdx_D[idx][m])
                            if temp_idx_D == FreqIdx_D:
                                CFAR_PeakIdx.append(temp_idx_R)
                                CFAR_PeakVal.append(Ref_PowSpec[idx][temp_idx_R, temp_idx_D])

                selectedPlot1_D[0].setData(xData, yData)
                selectedPlot2_D[0].setData(xData, BaseTh_yData)
                selectedPlot3_D[0].setData(x_CFAR_Th, y_CFAR_Th)
                selectedPlot4_D[0].setData(x_CFAR_Out, y_CFAR_Out)
                selectedPlot5_D[0].setData(CFAR_PeakIdx, CFAR_PeakVal)




