import os, sys
import shutil
import pygame
import h5py

import GUI_Class as UIC
from pyqtgraph.Qt import QtGui
import parametertree as pTree


pygame.init()
pygame.mixer.quit()
app = QtGui.QApplication([])
desktop_widget = app.desktop()
primary_screen = desktop_widget.primaryScreen()
screen_rect = desktop_widget.screenGeometry(primary_screen)
SCREEN_SIZE = screen_rect.width(), screen_rect.height()
WIN_VIEW_SIZE = int(SCREEN_SIZE[0]*0.2), int(SCREEN_SIZE[1]*0.64)
WIN_CAM_SIZE = 900, 600

######### Global Variable ##########
# Scan Index
ScanIndexMax = 0
ScanIndexMin = 0
ScanIndexCur = 0

# Loop
LOOP_BASIC = 1
LOOP_FAST = 20
LOOP_PLAY = 1

PLAY_ON = False


def ReadH5File(File, File_name, IsFileFlag):
    for idx in range(len(File_name)):
        if File_name[idx] is not None:
            if os.path.isfile(File_name[idx]):
                File[idx] = (h5py.File(File_name[idx], 'r'))
                if IsFileFlag == -1:
                    IsFileFlag = idx
        else:
            File[idx] = None


def GetSimScanData(h5File, ScanData, GroupName):
    for idx in range(len(SimFile)):
        if h5File[idx] is not None:
            ScanData[idx] = h5File[idx][GroupName]
        else:
            ScanData[idx] = None


def GetLogScanData(h5File, ScanData, GroupName):
    for idx in range(len(LogPaths)):
        if h5File[idx] is not None:
            ScanData[idx] = h5File[idx][GroupName]
        else:
            ScanData[idx] = None


############ GUI_Class ############
Radar_GUI = UIC.RadarToolGUI(WIN_VIEW_SIZE, WIN_CAM_SIZE, SCREEN_SIZE)
GUI_Tree = pTree.ParamTree()


############ MAIN ############
if __name__ == '__main__':

    ########### Data Loading ###########
    SimFileName = []
    if len(sys.argv) == 2:
        SimFileName.append(sys.argv[1])
    else:
        SimFileName.append("SimResult.h5")

    RefFileName = []
    RefFileName.append("SimResult_Ref.h5")

    LogFileName = []
    file = open('LogInfo.ini', 'r')
    LogPaths = file.read().splitlines()
    file.close()

    for LogFile in os.listdir(LogPaths[0]):
        if LogFile.endswith(".h5"):
            FileName = LogPaths[0] + "\\" + LogFile
            LogFileName.append(FileName)

    SimFile = [None] * len(SimFileName)
    RefFile = [None] * len(RefFileName)
    LogFile = [None] * len(LogFileName)
    IsFileIdx = -1

    ReadH5File(SimFile, SimFileName, IsFileIdx)
    ReadH5File(RefFile, RefFileName, IsFileIdx)
    ReadH5File(LogFile, LogFileName, IsFileIdx)

    ScanIndexOld = 0
    keys1 = pygame.key.get_pressed()
    keys2 = pygame.key.get_pressed()
    temp_cnt = 0

    ScanIndexMin = SimFile[IsFileIdx]['DataInfo']['initScan'].value[0]
    ScanIndexMax = SimFile[IsFileIdx]['DataInfo']['finScan'].value[0] - 1
    ScanIndexCur = ScanIndexMin

    SimScanData = [None] * len(SimFile)
    RefScanData = [None] * len(RefFile)
    LogScanData = [None] * len(LogFile)

    LogPathfile = open('LogInfo.ini', 'r')
    LogPath = LogPathfile.read()
    LogPathfile.close()

    while True:
        if ScanIndexOld != ScanIndexCur:
            GroupName = 'SCAN_{:05d}'.format(ScanIndexCur)
            GetSimScanData(SimFile, SimScanData, GroupName)
            GetLogScanData(LogFile, LogScanData, GroupName)
            temp = SimScanData[0].name
            if Radar_GUI.Mode == 2:
                GetSimScanData(RefFile, RefScanData, GroupName)

            Radar_GUI.Display(Radar_GUI.DisplaySurf, SimScanData, RefScanData, LogScanData, ScanIndexCur)

            if PLAY_ON:
                pygame.time.delay(40)

            pygame.display.update()
            GUI_Tree.SetData(SimScanData)
        else:
            pygame.time.delay(100)

        ScanIndexOld = ScanIndexCur


        # Key Input Event
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

            elif event.type == pygame.VIDEORESIZE:
                Radar_GUI.VideoResizeEvent(event, SimScanData, RefScanData, LogScanData, ScanIndexCur)

            # KeyBoard Event
            elif event.type == pygame.KEYDOWN:

                if event.key == pygame.K_F1:
                    Radar_GUI.ModeChange(1)
                elif event.key == pygame.K_F2:
                    Radar_GUI.ModeChange(2)
                #elif event.key == pygame.K_F3:
                #    Radar_GUI.ModeChange(3)
                elif event.key == pygame.K_F8:
                    for idx in range(len(SimFileName)):
                        if os.path.isfile(SimFileName[idx]):
                            shutil.copy(SimFileName[idx], RefFileName[idx])
                    print('Reference Simulation Data Saved!')
                elif event.key == pygame.K_F10:
                    Radar_GUI = UIC.RadarToolGUI(WIN_VIEW_SIZE, WIN_CAM_SIZE, SCREEN_SIZE)
                    ScanIndexCur = ScanIndexMin
                elif event.key == pygame.K_F12:
                    Radar_GUI.ModeChange(12)

                # Move
                elif event.key == pygame.K_LEFT:  # Left
                    if ScanIndexCur - LOOP_BASIC > ScanIndexMin:
                        ScanIndexCur -= LOOP_BASIC
                    else:
                        ScanIndexCur = ScanIndexMin
                elif event.key == pygame.K_RIGHT:  # Right
                    if ScanIndexCur + LOOP_BASIC < ScanIndexMax:
                        ScanIndexCur += LOOP_BASIC
                    else:
                        ScanIndexCur = ScanIndexMax
                elif event.key == pygame.K_UP:  # Up
                    if ScanIndexCur + LOOP_FAST < ScanIndexMax:
                        ScanIndexCur += LOOP_FAST
                    else:
                        ScanIndexCur = ScanIndexMax
                elif event.key == pygame.K_DOWN:  # Down
                    if ScanIndexCur - LOOP_FAST > ScanIndexMin:
                        ScanIndexCur -= LOOP_FAST
                    else:
                        ScanIndexCur = ScanIndexMin
                elif event.key == pygame.K_SPACE:  # Play
                    PLAY_ON = not PLAY_ON

                else:
                    Radar_GUI.KeyState.KeyEvent(event.key)

                    if (event.key == pygame.K_1)\
                            or (event.key == pygame.K_2)\
                            or (event.key == pygame.K_3)\
                            or (event.key == pygame.K_4)\
                            or (event.key == pygame.K_5)\
                            or (event.key == pygame.K_6)\
                            or (event.key == pygame.K_7)\
                            or (event.key == pygame.K_8)\
                            or (event.key == pygame.K_9)\
                            or (event.key == pygame.K_0):

                        if ((Radar_GUI.Mode == 2) or (Radar_GUI.Mode == 3))\
                                and (Radar_GUI.KeyState.Key_Num >= 1) and (Radar_GUI.KeyState.Key_Num <= 2):
                            Radar_GUI.ModeChange(3)
                        elif Radar_GUI.Mode == 3:
                            Radar_GUI.ModeChange(2)

                Radar_GUI.Display(Radar_GUI.DisplaySurf, SimScanData, RefScanData, LogScanData, ScanIndexCur)

            # Mouse Event
            elif (event.type == pygame.MOUSEBUTTONUP) or (event.type == pygame.MOUSEBUTTONDOWN)\
                    or ((event.type == pygame.MOUSEMOTION) and (Radar_GUI.KeyState.MouseLeftDown_on)):
                Radar_GUI.KeyState.MouseEvent(event)

                Radar_GUI.Display(Radar_GUI.DisplaySurf, SimScanData, RefScanData, LogScanData, ScanIndexCur)

            pygame.display.update()



        # Key Pressing
        keys1 = pygame.key.get_pressed()
        if keys1==keys2:
            if keys1[pygame.K_RIGHT]:
                temp_cnt += 1
                input_key = pygame.K_RIGHT
            elif keys1[pygame.K_LEFT]:
                temp_cnt += 1
                input_key = pygame.K_LEFT
            elif keys1[pygame.K_UP]:
                temp_cnt += 1
                input_key = pygame.K_UP
            elif keys1[pygame.K_DOWN]:
                temp_cnt += 1
                input_key = pygame.K_DOWN
            else:
                temp_cnt = 0
        else:
            temp_cnt = 0

        if temp_cnt > 30000:
            pygame.event.post(pygame.event.Event(pygame.KEYDOWN, key=input_key))

        keys2 = keys1


        if PLAY_ON:
            if ScanIndexCur + LOOP_BASIC < ScanIndexMax:
                ScanIndexCur += LOOP_PLAY
            else:
                ScanIndexCur = ScanIndexMax
                PLAY_ON = False




