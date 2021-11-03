import sys
from PyQt5 import QtWidgets
import ColorTable as Color
import numpy as np
import QtDesign.ObjAPS_UI as QtUI
import matplotlib.pyplot as plt

jet = plt.get_cmap('jet')



app = QtWidgets.QApplication(sys.argv)
RadarTag = ['LRR', 'MRR', 'SRR']

class ObjAPS_UI:
    def __init__(self, DataIdx, **opts):

        self.opts = {
            'title': '',
        }
        self.opts.update(opts)
        self.DataIdx = DataIdx

        self.Form = QtWidgets.QWidget()
        #self.UI_Form = QtUI.Ui_Form()
        #self.UI_Form.setupUi(self.Form)

        self.ObjUI = QtUI.Ui_Form()
        self.ObjUI.setupUi(self.Form)

        #self.UI_Form.graphicsView.plotItem.setLabel("bottom", "Angle", units="degree")
        #self.UI_Form.graphicsView.plotItem.showGrid(x=True, y=True)
        #self.APS_plot = self.UI_Form.graphicsView.plotItem.plot()
        #self.APS_plot.setPen(Color.aqua, width=1)

        self.SelectedView = self.ObjUI.graphicsView

        self.FreqIdx_D = -1
        self.FreqIdx_R = -1
        self.RadarIdx = -1
        self.harm_idx = -1

        self.LR_AziAngleTable = []
        self.MR_AziAngleTable = []
        self.SR_AziAngleTable = []

        self.LR_EleAngleTable = []
        self.MR_EleAngleTable = []
        self.SR_EleAngleTable = []



        self.APS = [[]] * len(RadarTag)


        self.LR_PeakCnt = []
        self.MR_PeakCnt = []
        self.SR_PeakCnt = []

        self.Peak_FreqIdx_R = [[]] * len(RadarTag)
        self.Peak_FreqIdx_D = [[]] * len(RadarTag)

        self.ObjUI.pushButton_LRR.clicked.connect(self.LRR_Index)
        self.ObjUI.pushButton_MRR.clicked.connect(self.MRR_Index)
        self.ObjUI.pushButton_SRR.clicked.connect(self.SRR_Index)

        self.SelectedView = self.ObjUI.graphicsView


    def LRR_Index(self):
        self.RadarIdx = 0
        EditIdx_D = self.ObjUI.lineEdit_D.text()
        EditIdx_R = self.ObjUI.lineEdit_R.text()

        harm_idx = self.ObjUI.lineEdit.text()
        if harm_idx is not None:
            if harm_idx.isdigit():
                self.harm_idx = int(harm_idx)
        else:
            self.harm_idx = 0

        if EditIdx_D.isdigit():
            self.FreqIdx_D = int(EditIdx_D)
        if EditIdx_R.isdigit():
            self.FreqIdx_R = int(EditIdx_R)

        self.pltData()

    def MRR_Index(self):
        self.RadarIdx = 1
        EditIdx_D = self.ObjUI.lineEdit_D.text()
        EditIdx_R = self.ObjUI.lineEdit_R.text()

        harm_idx = self.ObjUI.lineEdit.text()
        if harm_idx is not None:
            if harm_idx.isdigit():
                self.harm_idx = int(harm_idx)
        else:
            self.harm_idx = 0

        if EditIdx_D.isdigit():
            self.FreqIdx_D = int(EditIdx_D)
        if EditIdx_R.isdigit():
            self.FreqIdx_R = int(EditIdx_R)

        self.pltData()



    def SRR_Index(self):
        self.RadarIdx = 2
        EditIdx_D = self.ObjUI.lineEdit_D.text()
        EditIdx_R = self.ObjUI.lineEdit_R.text()

        harm_idx = self.ObjUI.lineEdit.text()
        if harm_idx.isdigit():
            self.harm_idx = int(harm_idx)

        if EditIdx_D.isdigit():
            self.FreqIdx_D = int(EditIdx_D)
        if EditIdx_R.isdigit():
            self.FreqIdx_R = int(EditIdx_R)

        self.pltData()


    def SetData(self, ScanData):

        if ScanData[self.DataIdx] is not None:
            self.LR_AziAngleTable = ScanData[self.DataIdx]['Sim_LR_AziAngleTable'].value
            self.MR_AziAngleTable = ScanData[self.DataIdx]['Sim_MR_AziAngleTable'].value
            self.SR_AziAngleTable = ScanData[self.DataIdx]['Sim_SR_AziAngleTable'].value

            self.LR_EleAngleTable = ScanData[self.DataIdx]['Sim_LR_EleAngleTable'].value
            self.MR_EleAngleTable = ScanData[self.DataIdx]['Sim_MR_EleAngleTable'].value
            self.SR_EleAngleTable = ScanData[self.DataIdx]['Sim_SR_EleAngleTable'].value


            self.APS[0] = ScanData[self.DataIdx]['Sim_LR_APS'].value
            self.APS[1] = ScanData[self.DataIdx]['Sim_MR_APS'].value
            self.APS[2] = ScanData[self.DataIdx]['Sim_SR_APS'].value

            self.LR_PeakCnt = ScanData[self.DataIdx]['Sim_LR_PeakCnt'].value
            self.MR_PeakCnt = ScanData[self.DataIdx]['Sim_MR_PeakCnt'].value
            self.SR_PeakCnt = ScanData[self.DataIdx]['Sim_SR_PeakCnt'].value


            self.Peak_FreqIdx_R[0] = ScanData[self.DataIdx]['Sim_LR_PeakData'].value[:, 0]
            self.Peak_FreqIdx_D[0] = ScanData[self.DataIdx]['Sim_LR_PeakData'].value[:, 1]

            self.Peak_FreqIdx_R[1] = ScanData[self.DataIdx]['Sim_MR_PeakData'].value[:, 0]
            self.Peak_FreqIdx_D[1] = ScanData[self.DataIdx]['Sim_MR_PeakData'].value[:, 1]

            self.Peak_FreqIdx_R[2] = ScanData[self.DataIdx]['Sim_SR_PeakData'].value[:, 0]
            self.Peak_FreqIdx_D[2] = ScanData[self.DataIdx]['Sim_SR_PeakData'].value[:, 1]

            self.pltData()


    def pltData(self):
        FreqIdx_D = self.FreqIdx_D
        FreqIdx_R = self.FreqIdx_R
        radarIdx = self.RadarIdx
        harm_idx = self.harm_idx



        if RadarTag[radarIdx] == 'LRR':
            
            PeakCnt_Data = self.LR_PeakCnt
            Peak_FreqIdx_D_Data = self.Peak_FreqIdx_D[0]
            Peak_FreqIdx_R_Data = self.Peak_FreqIdx_R[0]

            Azi_step_size = len(self.LR_AziAngleTable)
            Ele_step_size = len(self.LR_EleAngleTable)


            if PeakCnt_Data == 0:
                print('Peak Cnt 0 Signal')
            else:
                for idx in range(PeakCnt_Data[0]):

                    if (FreqIdx_D == Peak_FreqIdx_D_Data[idx]) & (FreqIdx_R == Peak_FreqIdx_R_Data[idx]):

                        if (harm_idx == 0):
                            temp_APS = self.APS[0][idx, 0:Azi_step_size*Ele_step_size]



                        else:
                            temp_APS = self.APS[0][idx, 21*33:1386]


                        temp_APS = np.reshape(temp_APS, (Ele_step_size, Azi_step_size))
                        self.SelectedView.canvas.ax.clear()
                        self.SelectedView.canvas.ax.imshow(temp_APS, cmap=jet, extent=[self.LR_AziAngleTable[0], self.LR_AziAngleTable[-1], self.LR_EleAngleTable[-1], self.LR_EleAngleTable[0]])
                        self.SelectedView.canvas.ax.set_xlabel('AziAngle')
                        self.SelectedView.canvas.ax.set_ylabel('EleAngle')
                        self.SelectedView.canvas.ax.axis(option='auto')
                        self.SelectedView.canvas.draw()

                        break
                    else:
                        print('Wait')

        elif RadarTag[radarIdx] == 'MRR':
            print('MRR')
            PeakCnt_Data = self.MR_PeakCnt
            Peak_FreqIdx_D_Data = self.Peak_FreqIdx_D[1]
            Peak_FreqIdx_R_Data = self.Peak_FreqIdx_R[1]

            Azi_step_size = len(self.MR_AziAngleTable)
            Ele_step_size = len(self.MR_EleAngleTable)

            if PeakCnt_Data == 0:
                print('Peak Cnt 0 Signal')
            else:
                for idx in range(PeakCnt_Data[0]):

                    if (FreqIdx_D == Peak_FreqIdx_D_Data[idx]) & (FreqIdx_R == Peak_FreqIdx_R_Data[idx]):

                        if (harm_idx == 0):
                            temp_APS = self.APS[1][idx, 0:Azi_step_size*Ele_step_size]
                        else:
                            temp_APS = self.APS[1][idx, Azi_step_size*Ele_step_size:len(self.APS[1][idx, :])]

                        temp_APS = np.reshape(temp_APS, (Ele_step_size, Azi_step_size))

                        self.SelectedView.canvas.ax.clear()
                        self.SelectedView.canvas.ax.imshow(temp_APS, cmap=jet,
                                                           extent=[self.MR_AziAngleTable[0], self.MR_AziAngleTable[-1],
                                                                   self.MR_EleAngleTable[-1], self.MR_EleAngleTable[0]])
                        self.SelectedView.canvas.ax.set_xlabel('AziAngle')
                        self.SelectedView.canvas.ax.set_ylabel('EleAngle')
                        self.SelectedView.canvas.ax.axis(option='auto')
                        self.SelectedView.canvas.draw()

                        break
                    else:
                        print('Wait')

        elif RadarTag[radarIdx] == 'SRR':
            print('SRR')
            PeakCnt_Data = self.SR_PeakCnt
            Peak_FreqIdx_D_Data = self.Peak_FreqIdx_D[2]
            Peak_FreqIdx_R_Data = self.Peak_FreqIdx_R[2]

            Azi_step_size = len(self.SR_AziAngleTable)
            Ele_step_size = len(self.SR_EleAngleTable)

            if PeakCnt_Data == 0:
                print('Peak Cnt 0 Signal')
            else:
                for idx in range(PeakCnt_Data[0]):

                    if (FreqIdx_D == Peak_FreqIdx_D_Data[idx]) & (FreqIdx_R == Peak_FreqIdx_R_Data[idx]):

                        if (harm_idx == 0):
                            temp_APS = self.APS[2][idx, 0:Azi_step_size*Ele_step_size]
                        else:
                            temp_APS = self.APS[2][idx, Azi_step_size*Ele_step_size:len(self.APS[2][idx, :])]

                        temp_APS = np.reshape(temp_APS, (Ele_step_size, Azi_step_size))

                        self.SelectedView.canvas.ax.clear()
                        self.SelectedView.canvas.ax.imshow(temp_APS, cmap=jet,
                                                           extent=[self.SR_AziAngleTable[0], self.SR_AziAngleTable[-1],
                                                                   self.SR_EleAngleTable[-1], self.SR_EleAngleTable[0]])
                        self.SelectedView.canvas.ax.set_xlabel('AziAngle')
                        self.SelectedView.canvas.ax.set_ylabel('EleAngle')
                        self.SelectedView.canvas.ax.axis(option='auto')
                        self.SelectedView.canvas.draw()
                        break
                    else:
                        print('Wait')