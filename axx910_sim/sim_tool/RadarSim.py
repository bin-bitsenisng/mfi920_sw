import sys, os
from PyQt5 import QtWidgets
import h5py

import QtDesign.RadarSim_UI as RUI
import FileDragDrop as FDD
import Log_GetRawData


app = QtWidgets.QApplication(sys.argv)
Form = QtWidgets.QMainWindow()
RadarUI = RUI.Ui_MainWindow()



def ConnectWidget():
    LoadPath()

    # Connect Functions #
    RadarUI.toolButton_Path1.clicked.connect(getPath_SW)
    RadarUI.toolButton_Path2.clicked.connect(getPath_Data)

    RadarUI.toolButton_AddPath1.clicked.connect(AddPath_SW)
    RadarUI.toolButton_AddPath2.clicked.connect(AddPath_Data)

    RadarUI.toolButton_DelPath1.clicked.connect(DelPath_SW)
    RadarUI.toolButton_DelPath2.clicked.connect(DelPath_Data)

    RadarUI.pushButton_Save.clicked.connect(SavePath)
    RadarUI.pushButton_Load.clicked.connect(LoadPath)

    RadarUI.listWidget_SW.itemClicked.connect(listClicked_SW)
    RadarUI.listWidget_Data.itemClicked.connect(listClicked_Data)

    RadarUI.pushButton_Sim.clicked.connect(RadarSimulation)
    RadarUI.pushButton_MultiSim.clicked.connect(MultiSimulation)
    RadarUI.pushButton_GUI.clicked.connect(RadarGui)
    RadarUI.pushButton_HDF5.clicked.connect(DataToHDF5)


def getPath_SW():
    fPath = QtWidgets.QFileDialog.getExistingDirectory()

    RadarUI.lineEdit_SW_Path.setText(fPath)


def getPath_Data():
    #fPath = QtWidgets.QFileDialog.getExistingDirectory(directory='C://LoggingData')
    fPath = QtWidgets.QFileDialog.getExistingDirectory(directory='C://')
    RadarUI.lineEdit_Data_Path.setText(fPath)

def AddPath_SW():
    fPath = RadarUI.lineEdit_SW_Path.text()
    if fPath == '' or fPath.isspace(): return
    RadarUI.listWidget_SW.addItem(fPath)


def AddPath_Data():
    fPath = RadarUI.lineEdit_Data_Path.text()
    InitScan = RadarUI.lineEdit_InitScan.text()
    LastScan = RadarUI.lineEdit_LastScan.text()
    if fPath == '' or fPath.isspace(): return
    if InitScan.isdigit() and LastScan.isdigit() and (int(InitScan) <= int(LastScan)):
        RadarUI.listWidget_Data.addItem(fPath + ',' + InitScan + ',' + LastScan)


def DelPath_SW():
    listItems = RadarUI.listWidget_SW.selectedItems()
    if not listItems: return
    for item in listItems:
        RadarUI.listWidget_SW.takeItem(RadarUI.listWidget_SW.row(item))


def DelPath_Data():
    listItems = RadarUI.listWidget_Data.selectedItems()
    if not listItems: return
    for item in listItems:
        RadarUI.listWidget_Data.takeItem(RadarUI.listWidget_Data.row(item))


def SavePath():
    paths = []
    for idx in range(RadarUI.listWidget_SW.count()):
        if idx != RadarUI.listWidget_SW.count():
            paths.append(RadarUI.listWidget_SW.item(idx).text() + "\n")
        else:
            paths.append(RadarUI.listWidget_SW.item(idx).text())

    file = open('RadarSW_Path.txt', 'w')
    file.writelines(paths)
    file.close()

    paths = []
    for idx in range(RadarUI.listWidget_Data.count()):
        if idx != RadarUI.listWidget_Data.count():
            paths.append(RadarUI.listWidget_Data.item(idx).text() + "\n")
        else:
            paths.append(RadarUI.listWidget_Data.item(idx).text())

    file = open('LogData_Path.txt', 'w')
    file.writelines(paths)
    file.close()


def LoadPath():
    RadarUI.listWidget_SW.clear()

    if not os.path.isfile("RadarSW_Path.txt"):
        file = open('RadarSW_Path.txt', 'w')
        file.close()
    if not os.path.isfile("LogData_Path.txt"):
        file = open('LogData_Path.txt', 'w')
        file.close()

    file = open('RadarSW_Path.txt', 'r')
    paths = file.read().splitlines()
    for path in paths:
        item = QtWidgets.QListWidgetItem()
        item.setText(path)
        RadarUI.listWidget_SW.addItem(item)
    file.close()

    RadarUI.listWidget_Data.clear()
    file = open('LogData_Path.txt', 'r')
    paths = file.read().splitlines()
    for path in paths:
        item = QtWidgets.QListWidgetItem()
        item.setText(path)
        RadarUI.listWidget_Data.addItem(item)
    file.close()


def listClicked_SW(item):
    RadarUI.lineEdit_SW_Path.setText(item.text())


def listClicked_Data(item):
    ItemText = item.text()
    ListText = ItemText.split(",")
    RadarUI.lineEdit_Data_Path.setText(ListText[0])
    RadarUI.lineEdit_InitScan.setText(ListText[1])
    RadarUI.lineEdit_LastScan.setText(ListText[2])


def RadarSimulation():
    SW_Path = RadarUI.lineEdit_SW_Path.text()
    LogDataPath = RadarUI.lineEdit_Data_Path.text()

    PeakMode = RadarUI.lineEdit_PeakMode.text()

    if PeakMode is None:
        PeakMode = str(0)

    if (SW_Path != '') and (LogDataPath != ''):
        InitScan = RadarUI.lineEdit_InitScan.text()
        LastScan = RadarUI.lineEdit_LastScan.text()
        Resim_Path = SW_Path + "/axx910_sim/rsp_sim/x64/Debug/rsp_sim.exe"
        ResimInfo_Path = SW_Path + "/axx910_sim/rsp_sim/rsp_sim/SimFileInfo.ini"
        LogDataPath = LogDataPath + "/OUT"

        for root, dirs, files in os.walk(LogDataPath):
            for file in files:
                ext = file.split('.')[-1]

                if ext == 'h5':
                    print('Logging Data FileName : ' + file)
                    SimFile = SW_Path + '/axx910_sim/sim_tool/' + 'SimResult.h5'
                    LogFile = LogDataPath + '/' + file

                    if InitScan == '0':
                        InitScan = '1'

                    if LastScan == '0':
                        LogH5 = h5py.File(LogFile, 'r')
                        LastScan = str(len(LogH5['/'].values()) - 1)

                    MakeResimInfo(ResimInfo_Path, SimFile, LogFile, InitScan, LastScan, PeakMode)

                    exitcode = os.system(Resim_Path+" "+ResimInfo_Path)

                    LogPathfile = open('LogInfo.ini', 'w')
                    LogPathfile.writelines(LogDataPath)
                    LogPathfile.close()

                    print(Resim_Path)
                    if exitcode is 3:
                        print('Simulation was fail.')
                        sys.exit()
        RadarGui()


def RadarGui():
    exitcode = os.system("GUI_Main.py")
    if exitcode is 3:
        print('Display fail.')
        sys.exit()


def MultiSimulation():

    SW_Path = RadarUI.lineEdit_SW_Path.text()
    MultiSimDir = SW_Path + '/axx910_sim/sim_tool/MultiSimResult/'
    if not os.path.exists(MultiSimDir):
        os.makedirs(MultiSimDir)

    if SW_Path != '':
        for idx in range(RadarUI.listWidget_Data.count()):
            ItemText = RadarUI.listWidget_Data.item(idx).text()
            ListText = ItemText.split(",")
            LogDataPath = ListText[0]
            InitScan = ListText[1]
            LastScan = ListText[2]
            Resim_Path = SW_Path + "/axx910_sim/rsp_sim/x64/Debug/rsp_sim.exe"
            ResimInfo_Path = SW_Path + "/axx910_sim/rsp_sim/rsp_sim/SimFileInfo.ini"

            for root, dirs, files in os.walk(LogDataPath):
                for file in files:
                    ext = file.split('.')[1]

                    if ext == 'h5':
                        print('Logging FileName :' + file)
                        SimFile = MultiSimDir + 'SimResult_' + file
                        LogFile = LogDataPath + '/' + file
                        MakeResimInfo(ResimInfo_Path, SimFile, LogFile, InitScan, LastScan)

                        exitcode = os.system(Resim_Path + " " + ResimInfo_Path)
                        print('')

                        LogPathfile = open('LogInfo.ini', 'w')
                        LogPathfile.writelines(LogDataPath)
                        LogPathfile.close()

                        if exitcode is 3:
                            print('Simulation was fail.')
                            sys.exit()

        print('=========== Simulation Completed!!! ===========')


def DataToHDF5():
    LogDataPath = RadarUI.lineEdit_Data_Path.text()
    radartype = 'AFI'
    if LogDataPath != '':
        if radartype == 'MRR':
            raw2h5 = Log_GetRawData.rawfile_to_hdf5(1, RadarType=radartype)
            raw2h5.convert_dat_to_hdf5(LogDataPath)
        elif radartype == 'AFI':
            import Log_RawH5toH5
            raw2h5 = Log_RawH5toH5.RawH5ToH5(RadarType = radartype)
            raw2h5.convert(LogDataPath)
        elif radartype == 'ATM':
            import Log_RawH5toH5
            raw2h5 = Log_RawH5toH5.RawH5ToH5(RadarType=radartype)
            raw2h5.convert(LogDataPath)
        else:
            print('Error : Select RadarType')
            pass
        print('=========== Converting Completed!!! ===========')


def MakeResimInfo(ResimInfoPath, SimFile, LogFile, InitScan, LastScan, PeakMode):

    resiminfofile = open(ResimInfoPath, 'w')
    resiminfostr = '[FileInfo]\n'
    resiminfostr += 'SimResultFname=' + SimFile + '\n'
    resiminfostr += '\n'
    resiminfostr += '[DataInfo]\n'
    resiminfostr += 'LoggingDataFname=' + LogFile + '\n'
    resiminfostr += '\n'
    resiminfostr += '[SimInfo]\n'
    resiminfostr += 'InitialScan=' + InitScan + '\n'
    resiminfostr += 'FinalScan=' + LastScan + '\n'
    resiminfostr += '\n'
    resiminfostr += '[LogModInfo]\n'
    resiminfostr += 'peakMode=' + PeakMode + '\n'

    resiminfofile.write(resiminfostr)
    resiminfofile.close()


# MAIN
if __name__ == '__main__':
    RadarUI.setupUi(Form)
    FDD.lineEdit_DnD(RadarUI.lineEdit_SW_Path)
    FDD.lineEdit_DnD(RadarUI.lineEdit_Data_Path)
    FDD.listWidget_DnD(RadarUI.listWidget_SW)
    FDD.listWidget_DnD(RadarUI.listWidget_Data, ",0,0")
    ConnectWidget()
    Form.show()
    sys.exit(app.exec_())

