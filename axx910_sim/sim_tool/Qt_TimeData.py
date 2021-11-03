import sys
from PyQt5 import QtWidgets
import numpy as np
import QtDesign.TimeData_UI as QtUI



app = QtWidgets.QApplication(sys.argv)
ChTag = ['Ch1', 'Ch2', 'Ch3']


class TimeData_UI:
    def __init__(self, DataIdx, **opts):

        self.opts = {
            'title': '',
        }
        self.opts.update(opts)
        self.DataIdx = DataIdx

        self.Form = QtWidgets.QWidget()
        self.UI_Form = QtUI.Ui_Form()
        self.UI_Form.setupUi(self.Form)

        self.PlotTemplate = []
        self.DataPlot = []

        self.Data1_1 = [[]] * len(ChTag)

        for idx in range(len(ChTag)):
            self.PlotTemplate.append(self.UI_Form.graphicsView_0.addPlot(title=self.opts['title'] + ' - ' + ChTag[idx]))
            self.UI_Form.graphicsView_0.nextRow()

        for idx in range(len(ChTag)):
            self.DataPlot.append(self.PlotTemplate[idx].plot(pen='y'))

        self.UI_Form.tabWidget.currentChanged.connect(self.pltData)


    def SetData(self, ScanData=[]):
        if ScanData[self.DataIdx] != []:
            self.Data1_1 = ScanData[self.DataIdx]['Sim_TimeData'].value
            self.pltData()


    def pltData(self):

        if self.UI_Form.tabWidget.currentIndex() == 0:
            selectedPlot = self.DataPlot
            Data = self.Data1_1

        for idx in range(len(Data)):
            xData = np.linspace(0, len(Data[idx])-1, len(Data[idx]))
            yData = Data[idx]
            selectedPlot[idx].setData(x=xData, y=yData)

