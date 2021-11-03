import sys
from PyQt5 import QtWidgets
import ColorTable as Color

import QtDesign.ObjInfo_UI as QtUI
import GUI_DataParsing as DataPar
import matplotlib.pyplot as plt
import matplotlib
import numpy as np

#matplotlib.use('Qt5Agg')
jet = plt.get_cmap('jet')
app = QtWidgets.QApplication(sys.argv)

class ObjInfo_UI:
    def __init__(self):

        self.Form = QtWidgets.QWidget()
        self.ObjUI = QtUI.Ui_Form()
        self.ObjUI.setupUi(self.Form)
        self.SelectedView = self.ObjUI.graphicsView

        self.APS_Data = []
        self.ObjDict = dict()

        #self.Form2 = QtWidgets.QWidget()
        #self.ObjUI2 = QtUI.Ui_Form()
        #self.ObjUI2.setupUi(self.Form2)

        #self.ObjUI2.graphicsView.plotItem.setTitle(title="Angular Power Spectrum")
        #self.ObjUI2.graphicsView.plotItem.setLabel("bottom", "Angle", units="degree")
        #self.ObjUI2.graphicsView.plotItem.showGrid(x=True, y=True)
        #self.APS_plot2 = self.ObjUI2.graphicsView.plotItem.plot()
        #self.APS_plot2.getViewBox().invertX(True)
        #self.APS_plot2.setPen(Color.aqua, width=1)



    def SetObjInfo(self, ObjInfo, DataSet):

        self.ObjDict = DataPar.ObjectDataParsing(ObjInfo)

        if self.ObjDict['Chirp'] == 0:
            str_Chirp = 'Long Range (%d)' % self.ObjDict['Chirp']
            APS = DataSet['Sim_LR_APS'].value[self.ObjDict['MergeIdx']]

            AziAngleTable = DataSet['Sim_LR_AziAngleTable'].value
            EleAngleTable = DataSet['Sim_LR_EleAngleTable'].value

            OBJ_AE_NUM_APS_AZI_STEPS = len(AziAngleTable)
            OBJ_AE_NUM_APS_ELE_STEPS = len(EleAngleTable)

        elif self.ObjDict['Chirp'] == 1:
            str_Chirp = 'Middle Range (%d)' % self.ObjDict['Chirp']
            APS = DataSet['Sim_MR_APS'].value[self.ObjDict['MergeIdx']]

            AziAngleTable = DataSet['Sim_MR_AziAngleTable'].value
            EleAngleTable = DataSet['Sim_MR_EleAngleTable'].value

            OBJ_AE_NUM_APS_AZI_STEPS = len(AziAngleTable)
            OBJ_AE_NUM_APS_ELE_STEPS = len(EleAngleTable)

        elif self.ObjDict['Chirp'] == 2:
            str_Chirp = 'Short Range (%d)' % self.ObjDict['Chirp']
            APS = DataSet['Sim_SR_APS'].value[self.ObjDict['MergeIdx']]

            AziAngleTable = DataSet['Sim_SR_AziAngleTable'].value
            EleAngleTable = DataSet['Sim_SR_EleAngleTable'].value

            OBJ_AE_NUM_APS_AZI_STEPS = len(AziAngleTable)
            OBJ_AE_NUM_APS_ELE_STEPS = len(EleAngleTable)



        if (self.ObjDict['Chirp'] == 0) or (self.ObjDict['Chirp'] == 1) or (self.ObjDict['Chirp'] == 2):

            self.ObjUI.lineEdit_chirp_type.setText(str_Chirp)
            self.ObjUI.lineEdit_range.setText('%3.2f m' % self.ObjDict['R'])
            self.ObjUI.lineEdit_velocity.setText('%3.2f m/s' % self.ObjDict['V'])
            self.ObjUI.lineEdit_azimuth.setText('%2.1f deg' % self.ObjDict['AziAng'])
            self.ObjUI.lineEdit_elevation.setText('%2.1f deg' % self.ObjDict['EleAng'])
            self.ObjUI.lineEdit_power.setText('%2.1f dB' % self.ObjDict['Pow'])
            self.ObjUI.lineEdit_rcs.setText('%2.1f dBsm' % self.ObjDict['RCS'])
            self.ObjUI.lineEdit_freq_idx.setText('<%3d, %3d>' % (self.ObjDict['IdxR'], self.ObjDict['IdxD']))
            self.ObjUI.lineEdit_noise_variance.setText('%3.1f' % self.ObjDict['NoiseVar'])
            self.ObjUI.lineEdit_pre_azi_angle.setText('%3.1f deg' % self.ObjDict['Pre_azi_angle'])
            self.ObjUI.lineEdit_pre_azi_power.setText('%3.2f dB' % self.ObjDict['Pre_azi_power'])
            self.ObjUI.lineEdit_sidelobe_power.setText('%3.1f dB' % self.ObjDict['SidelobePower'])

            #if self.ObjDict['HarmIdx'] == 0:
            #   temp_APS = APS[0:OBJ_AE_NUM_APS_AZI_STEPS*OBJ_AE_NUM_APS_ELE_STEPS]
            #elif self.ObjDict['HarmIdx'] == 1:
            #    temp_APS = APS[OBJ_AE_NUM_APS_AZI_STEPS * OBJ_AE_NUM_APS_ELE_STEPS:len(APS)]

            temp_APS = APS[0:OBJ_AE_NUM_APS_AZI_STEPS*OBJ_AE_NUM_APS_ELE_STEPS]
            APS = np.reshape(temp_APS, (OBJ_AE_NUM_APS_ELE_STEPS, OBJ_AE_NUM_APS_AZI_STEPS))

            self.APS_Data = APS

            Data = self.APS_Data

            self.SelectedView.canvas.ax.clear()
            self.SelectedView.canvas.ax.imshow(Data, cmap=jet, extent=[AziAngleTable[0], AziAngleTable[-1], EleAngleTable[-1], EleAngleTable[0]])
            self.SelectedView.canvas.ax.set_xlabel('AziAngle')
            self.SelectedView.canvas.ax.set_ylabel('EleAngle')

            #self.SelectedView.canvas.ax.set_ylim([EleAngleTable[0], EleAngleTable[-1]])
            #self.SelectedView.canvas.ax.set_xlim([AziAngleTable[0], AziAngleTable[-1]])

            #SelectedView.canvas.ax.set_ylim([16, -16])
            #SelectedView.canvas.ax.axis([10, -10, 16, -16])
            self.SelectedView.canvas.ax.axis(option='auto')
            self.SelectedView.canvas.draw()
            self.Form.close()
            self.Form.show()

        else:

            str_Chirp = 'Ref Range (%d)' % self.ObjDict['Chirp']
            APS = DataSet['Sim_RM_APS'].value[self.ObjDict['MergeIdx']]
            AziAngleTable = DataSet['Sim_RM_AziAngleTable'].value

            self.ObjUI.lineEdit_chirp_type.setText(str_Chirp)
            self.ObjUI.lineEdit_range.setText('%3.2f m' % self.ObjDict['R'])
            self.ObjUI.lineEdit_velocity.setText('%3.2f m/s' % self.ObjDict['V'])
            self.ObjUI.lineEdit_azimuth.setText('%2.1f deg' % self.ObjDict['AziAng'])
            self.ObjUI.lineEdit_elevation.setText('%2.1f deg' % self.ObjDict['EleAng'])
            self.ObjUI.lineEdit_power.setText('%2.1f dB' % self.ObjDict['Pow'])
            self.ObjUI.lineEdit_rcs.setText('%2.1f dBsm' % self.ObjDict['RCS'])
            self.ObjUI.lineEdit_freq_idx.setText('<%3d, %3d>' % (self.ObjDict['IdxR'], self.ObjDict['IdxD']))
            self.ObjUI.lineEdit_noise_variance.setText('%3.1f' % self.ObjDict['NoiseVar'])
            self.ObjUI.lineEdit_pre_azi_angle.setText('0')
            self.ObjUI.lineEdit_pre_azi_power.setText('0')
            self.ObjUI.lineEdit_sidelobe_power.setText('0')

            Data = np.empty((0, len(AziAngleTable)), float)

            Data = np.append(Data, np.array([APS]), axis=0)
            #Data = np.append(Data, np.array([APS]), axis=0)

            self.SelectedView.canvas.ax.clear()
            self.SelectedView.canvas.ax.imshow(Data, cmap=jet, extent=[AziAngleTable[0], AziAngleTable[-1], 0, 1])
            self.SelectedView.canvas.ax.axis(option='auto')
            self.SelectedView.canvas.draw()
            
            self.Form.close()
            self.Form.show()









