import sys
from PyQt5 import QtWidgets, QtGui, QtCore
import QtDesign.ObjGhost_UI as QtUI
from GUI_DataParsing import *
import ColorTable

app = QtWidgets.QApplication(sys.argv)


class ObjGhost_UI:
    def __init__(self, DataIdx, **opts):

        self.opts = {
            'title': '',
        }
        self.opts.update(opts)
        self.DataIdx = DataIdx

        self.Form = QtWidgets.QWidget()
        self.UI_Form = QtUI.Ui_Form()
        self.UI_Form.setupUi(self.Form)

        self.UI_Form.tabWidget.currentChanged.connect(self.setTableWidgetData)

        self.ObjDict = ObjectDataParsing([0]*22)

    def SetData(self, ScanData):
        if ScanData[self.DataIdx] is not None:
            FilObjInfo = ScanData[self.DataIdx]['Sim_FilObjInfo'].value
            self.GhostCnt = ScanData[self.DataIdx]['Sim_OutFilObjCnt'].value

            for key in self.ObjDict:
                self.ObjDict[key] = []

            for idx in range(len(FilObjInfo)):
                for key in self.ObjDict:
                    tempDict = ObjectDataParsing(FilObjInfo[idx])
                    self.ObjDict[key].append(tempDict[key])

            self.setTableWidgetData()


    def setTableWidgetData(self):
        self.UI_Form.tableWidget.clearContents()
        self.UI_Form.tableWidget_2.clearContents()
        self.UI_Form.tableWidget_3.clearContents()

        self.setTableCellData()

        self.UI_Form.tableWidget.resizeColumnsToContents()
        self.UI_Form.tableWidget.resizeRowsToContents()

        self.UI_Form.tableWidget_2.resizeColumnsToContents()
        self.UI_Form.tableWidget_2.resizeRowsToContents()

        self.UI_Form.tableWidget_3.resizeColumnsToContents()
        self.UI_Form.tableWidget_3.resizeRowsToContents()


    def setTableCellData(self):

        LR_Cnt = 0
        MR_Cnt = 0
        SR_Cnt = 0
        for idx in range(self.GhostCnt[0]):
            if (self.ObjDict['Chirp'][idx] == 0) :
                LR_Cnt += 1
            elif (self.ObjDict['Chirp'][idx] == 1) :
                MR_Cnt += 1
            elif (self.ObjDict['Chirp'][idx] == 2):
                SR_Cnt += 1

        self.UI_Form.tableWidget.setRowCount(LR_Cnt)
        self.UI_Form.tableWidget.setColumnCount(12)
        self.UI_Form.tableWidget_2.setRowCount(MR_Cnt)
        self.UI_Form.tableWidget_2.setColumnCount(12)
        self.UI_Form.tableWidget_3.setRowCount(SR_Cnt)
        self.UI_Form.tableWidget_3.setColumnCount(12)

        LR_Cnt = 0
        MR_Cnt = 0
        SR_Cnt = 0

        for idx in range(self.GhostCnt[0]):

            R = QtWidgets.QTableWidgetItem("%s m" % format(self.ObjDict['R'][idx], ".2f"))
            V = QtWidgets.QTableWidgetItem("%s m/s" % format(self.ObjDict['V'][idx], ".2f"))
            AziAng = QtWidgets.QTableWidgetItem("%s deg" % format(self.ObjDict['AziAng'][idx], ".2f"))
            EleAng = QtWidgets.QTableWidgetItem("%s deg" % format(self.ObjDict['EleAng'][idx], ".2f"))
            Pow = QtWidgets.QTableWidgetItem("%s dB" % format(self.ObjDict['Pow'][idx], ".2f"))
            RCS = QtWidgets.QTableWidgetItem("%s dBsm" % format(self.ObjDict['RCS'][idx], ".2f"))
            FreqIdx = QtWidgets.QTableWidgetItem("[ %s, %s ]" % (str(self.ObjDict['IdxR'][idx]), str(self.ObjDict['IdxD'][idx])))
            MergeIdx = QtWidgets.QTableWidgetItem("%s" % str(self.ObjDict['MergeIdx'][idx]))
            TrkNum = QtWidgets.QTableWidgetItem("%s" % str(self.ObjDict['NumTrk'][idx]))

            if self.ObjDict['Chirp'][idx] == 0:
                Chirp = QtWidgets.QTableWidgetItem("LR (%s)" % str(self.ObjDict['Chirp'][idx]))
            elif self.ObjDict['Chirp'][idx] == 1:
                Chirp = QtWidgets.QTableWidgetItem("MR (%s)" % str(self.ObjDict['Chirp'][idx]))
            elif self.ObjDict['Chirp'][idx] == 2:
                Chirp = QtWidgets.QTableWidgetItem("SR (%s)" % str(self.ObjDict['Chirp'][idx]))


            if self.ObjDict['Beam'][idx] == 0:
                Beam = QtWidgets.QTableWidgetItem("Center (%s)" % str(self.ObjDict['Beam'][idx]))
            elif self.ObjDict['Beam'][idx] == 1:
                Beam = QtWidgets.QTableWidgetItem("Left (%s)" % str(self.ObjDict['Beam'][idx]))
            elif self.ObjDict['Beam'][idx] == 2:
                Beam = QtWidgets.QTableWidgetItem("Right (%s)" % str(self.ObjDict['Beam'][idx]))
            elif self.ObjDict['Beam'][idx] == 3:
                Beam = QtWidgets.QTableWidgetItem("Left2 (%s)" % str(self.ObjDict['Beam'][idx]))
            else:
                Beam = QtWidgets.QTableWidgetItem("Right2 (%s)" % str(self.ObjDict['Beam'][idx]))



            if self.ObjDict['GFStep'][idx] == 0:
                GFStep = QtWidgets.QTableWidgetItem("NOT GHOST")
                Beam.setBackground(QtGui.QColor(204, 255, 51))
                R.setBackground(QtGui.QColor(204, 255, 51))
                V.setBackground(QtGui.QColor(204, 255, 51))
                AziAng.setBackground(QtGui.QColor(204, 255, 51))
                EleAng.setBackground(QtGui.QColor(204, 255, 51))
                Pow.setBackground(QtGui.QColor(204, 255, 51))
                RCS.setBackground(QtGui.QColor(204, 255, 51))
                FreqIdx.setBackground(QtGui.QColor(204, 255, 51))
                MergeIdx.setBackground(QtGui.QColor(204, 255, 51))
                TrkNum.setBackground(QtGui.QColor(204, 255, 51))
                GFStep.setBackground(QtGui.QColor(204, 255, 51))
            elif self.ObjDict['GFStep'][idx] == 1:
                GFStep = QtWidgets.QTableWidgetItem("FOV FILTER")
                Beam.setBackground(QtGui.QColor(255, 204, 204))
                R.setBackground(QtGui.QColor(255, 204, 204))
                V.setBackground(QtGui.QColor(255, 204, 204))
                AziAng.setBackground(QtGui.QColor(255, 204, 204))
                EleAng.setBackground(QtGui.QColor(255, 204, 204))
                Pow.setBackground(QtGui.QColor(255, 204, 204))
                RCS.setBackground(QtGui.QColor(255, 204, 204))
                FreqIdx.setBackground(QtGui.QColor(255, 204, 204))
                MergeIdx.setBackground(QtGui.QColor(255, 204, 204))
                TrkNum.setBackground(QtGui.QColor(255, 204, 204))
                GFStep.setBackground(QtGui.QColor(255, 204, 204))
            elif self.ObjDict['GFStep'][idx] == 2:
                GFStep = QtWidgets.QTableWidgetItem("HW NOISE")
                Beam.setBackground(QtGui.QColor(204, 255, 255))
                R.setBackground(QtGui.QColor(204, 255, 255))
                V.setBackground(QtGui.QColor(204, 255, 255))
                AziAng.setBackground(QtGui.QColor(204, 255, 255))
                EleAng.setBackground(QtGui.QColor(204, 255, 255))
                Pow.setBackground(QtGui.QColor(204, 255, 255))
                RCS.setBackground(QtGui.QColor(204, 255, 255))
                FreqIdx.setBackground(QtGui.QColor(204, 255, 255))
                MergeIdx.setBackground(QtGui.QColor(204, 255, 255))
                TrkNum.setBackground(QtGui.QColor(204, 255, 255))
                GFStep.setBackground(QtGui.QColor(204, 255, 255))
            elif self.ObjDict['GFStep'][idx] == 3:
                GFStep = QtWidgets.QTableWidgetItem("AMBIGUOUS VEL")
                Beam.setBackground(QtGui.QColor(204, 200, 255))
                R.setBackground(QtGui.QColor(204, 200, 255))
                V.setBackground(QtGui.QColor(204, 200, 255))
                AziAng.setBackground(QtGui.QColor(204, 200, 255))
                EleAng.setBackground(QtGui.QColor(204, 200, 255))
                Pow.setBackground(QtGui.QColor(204, 200, 255))
                RCS.setBackground(QtGui.QColor(204, 200, 255))
                FreqIdx.setBackground(QtGui.QColor(204, 200, 255))
                MergeIdx.setBackground(QtGui.QColor(204, 200, 255))
                TrkNum.setBackground(QtGui.QColor(204, 200, 255))
                GFStep.setBackground(QtGui.QColor(204, 200, 255))

            # Setting Text Alignment

            Chirp.setTextAlignment(QtCore.Qt.AlignCenter)
            Beam.setTextAlignment(QtCore.Qt.AlignCenter)
            R.setTextAlignment(QtCore.Qt.AlignCenter)
            V.setTextAlignment(QtCore.Qt.AlignCenter)
            AziAng.setTextAlignment(QtCore.Qt.AlignCenter)
            EleAng.setTextAlignment(QtCore.Qt.AlignCenter)
            Pow.setTextAlignment(QtCore.Qt.AlignCenter)
            RCS.setTextAlignment(QtCore.Qt.AlignCenter)
            FreqIdx.setTextAlignment(QtCore.Qt.AlignCenter)
            MergeIdx.setTextAlignment(QtCore.Qt.AlignCenter)
            TrkNum.setTextAlignment(QtCore.Qt.AlignCenter)
            GFStep.setTextAlignment(QtCore.Qt.AlignCenter)

            if (self.ObjDict['Chirp'][idx] == 0):
                self.UI_Form.tableWidget.setItem(LR_Cnt, 0, Chirp)
                self.UI_Form.tableWidget.setItem(LR_Cnt, 1, Beam)
                self.UI_Form.tableWidget.setItem(LR_Cnt, 2, R)
                self.UI_Form.tableWidget.setItem(LR_Cnt, 3, V)
                self.UI_Form.tableWidget.setItem(LR_Cnt, 4, AziAng)
                self.UI_Form.tableWidget.setItem(LR_Cnt, 5, EleAng)
                self.UI_Form.tableWidget.setItem(LR_Cnt, 6, Pow)
                self.UI_Form.tableWidget.setItem(LR_Cnt, 7, RCS)
                self.UI_Form.tableWidget.setItem(LR_Cnt, 8, FreqIdx)
                self.UI_Form.tableWidget.setItem(LR_Cnt, 9, MergeIdx)
                self.UI_Form.tableWidget.setItem(LR_Cnt, 10, TrkNum)
                self.UI_Form.tableWidget.setItem(LR_Cnt, 11, GFStep)
                LR_Cnt += 1

            elif (self.ObjDict['Chirp'][idx] == 1):
                self.UI_Form.tableWidget_2.setItem(MR_Cnt, 0, Chirp)
                self.UI_Form.tableWidget_2.setItem(MR_Cnt, 1, Beam)
                self.UI_Form.tableWidget_2.setItem(MR_Cnt, 2, R)
                self.UI_Form.tableWidget_2.setItem(MR_Cnt, 3, V)
                self.UI_Form.tableWidget_2.setItem(MR_Cnt, 4, AziAng)
                self.UI_Form.tableWidget_2.setItem(MR_Cnt, 5, EleAng)
                self.UI_Form.tableWidget_2.setItem(MR_Cnt, 6, Pow)
                self.UI_Form.tableWidget_2.setItem(MR_Cnt, 7, RCS)
                self.UI_Form.tableWidget_2.setItem(MR_Cnt, 8, FreqIdx)
                self.UI_Form.tableWidget_2.setItem(MR_Cnt, 9, MergeIdx)
                self.UI_Form.tableWidget_2.setItem(MR_Cnt, 10, TrkNum)
                self.UI_Form.tableWidget_2.setItem(MR_Cnt, 11, GFStep)
                MR_Cnt += 1

            elif (self.ObjDict['Chirp'][idx] == 2):
                self.UI_Form.tableWidget_3.setItem(SR_Cnt, 0, Chirp)
                self.UI_Form.tableWidget_3.setItem(SR_Cnt, 1, Beam)
                self.UI_Form.tableWidget_3.setItem(SR_Cnt, 2, R)
                self.UI_Form.tableWidget_3.setItem(SR_Cnt, 3, V)
                self.UI_Form.tableWidget_3.setItem(SR_Cnt, 4, AziAng)
                self.UI_Form.tableWidget_3.setItem(SR_Cnt, 5, EleAng)
                self.UI_Form.tableWidget_3.setItem(SR_Cnt, 6, Pow)
                self.UI_Form.tableWidget_3.setItem(SR_Cnt, 7, RCS)
                self.UI_Form.tableWidget_3.setItem(SR_Cnt, 8, FreqIdx)
                self.UI_Form.tableWidget_3.setItem(SR_Cnt, 9, MergeIdx)
                self.UI_Form.tableWidget_3.setItem(SR_Cnt, 10, TrkNum)
                self.UI_Form.tableWidget_3.setItem(SR_Cnt, 11, GFStep)
                SR_Cnt += 1


