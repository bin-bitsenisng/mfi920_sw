import pygame
import ColorTable as Color
from GUI_DataParsing import *


pygame.init()
pygame.font.init()
InfoFont1 = pygame.font.Font('./font/210 Haesol R.ttf', 20)
InfoFont2 = pygame.font.Font('./font/210 Haesol R.ttf', 16)
InfoFont3 = pygame.font.Font('./font/210 Haesol R.ttf', 16)
BGImage = pygame.image.load('./Image/Wise+Gray+Dark+Tone.JPG')



def DrawSelectedTargetInfo(screen, SimData, RefData, SelData):

    DY = 17
    X_ORG = 10
    Y_ORG = 5
    screen.blit(pygame.transform.scale(BGImage, screen.get_size()), (0, 0))

    if SimData is not None:

        Sim_ObjInfo = SimData['Sim_ObjInfo'].value
        Sim_TrkInfo = SimData['Sim_TrkInfo'].value
        if SimData['Sim_TrkletInfo'].value is not None:
            Sim_TrkletInfo = SimData['Sim_TrkletInfo'].value
        else:
            Sim_TrkletInfo = None

        pos = [X_ORG, Y_ORG]
        # ------------------
        pos[1] += DY
        display = '========== [SIM] SELECTED TARGET =========='
        label = InfoFont2.render(display, 1, Color.goldenrod)
        screen.blit(label, tuple(pos))

        # Selected Track
        pos[1] += DY
        display = 'Idx | Stat | Mov | PosX | PosY | VelX | VelY | HAng | Len | Wid | AssCnt(O) | AssCnt(L)'
        label = InfoFont3.render(display, 1, Color.blue)
        screen.blit(label, tuple(pos))

        colorL = Color.white
        for idx in range(len(SelData['SimTrk'])):
            pos[1] += DY
            TrkDict = TrackDataParsing(Sim_TrkInfo[SelData['SimTrk'][idx]])
            display = GetTrkDataStr(TrkDict)
            label = InfoFont3.render(display, 1, colorL)
            screen.blit(label, tuple(pos))


        # Selected Tracklet
        #if SimData['Sim_TrkletInfo'].value is not None:
        pos[1] += DY
        display = '---'
        label = InfoFont2.render(display, 1, Color.goldenrod)
        screen.blit(label, tuple(pos))

        pos[1] += DY
        display = 'Idx | Stat | Mov | PosX | PosY | VelX | VelY | ObjIdx | TrkIdx'
        label = InfoFont3.render(display, 1, Color.blue)
        screen.blit(label, tuple(pos))

        colorL = Color.white
        for idx in range(len(SelData['SimTrklet'])):
            pos[1] += DY
            TrkletDict = TrackletDataParsing(Sim_TrkletInfo[SelData['SimTrklet'][idx]])
            display = GetTrkletDataStr(TrkletDict)
            label = InfoFont3.render(display, 1, colorL)
            screen.blit(label, tuple(pos))


        # ------------------
        pos[1] += DY
        display = '========== NEAREST OBJECT =========='
        label = InfoFont2.render(display, 1, Color.goldenrod)
        screen.blit(label, tuple(pos))

        # Selected Object
        pos[1] += DY
        display = 'B) Range / Vel  / Azi / Freq_Idx / Pow  / Ele / RCS / NumTrk / Prob'
        label = InfoFont3.render(display, 1, Color.navy)
        screen.blit(label, tuple(pos))

        colorL = Color.white
        for idx in range(len(SelData['SimObj'])):
            pos[1] += DY

            ObjDict = ObjectDataParsing(Sim_ObjInfo[SelData['SimObj'][idx]])
            display = GetObjDataStr(ObjDict)
            label = InfoFont3.render(display, 1, colorL)
            screen.blit(label, tuple(pos))


    '''
    if RefData is not None:
        Ref_ObjInfo = RefData['Sim_ObjInfo'].value
        Ref_TrkInfo = RefData['Sim_TrkInfo'].value

        # ------------------
        pos[1] += DY
        display = '========== [REF] SELECTED TARGET =========='
        label = InfoFont2.render(display, 1, Color.goldenrod)
        screen.blit(label, tuple(pos))

        # Selected Track
        pos[1] += DY
        display = 'Idx | Stat | Mov | PosX | PosY | VelX | VelY | HAng | Len | Wid | AssCnt'
        label = InfoFont3.render(display, 1, Color.blue)
        screen.blit(label, tuple(pos))

        colorL = Color.white
        for idx in range(len(SelData['RefTrk'])):
            pos[1] += DY

            TrkDict = TrackDataParsing(Ref_TrkInfo[SelData['RefTrk'][idx]])
            display = GetTrkDataStr(TrkDict)
            label = InfoFont3.render(display, 1, colorL)
            screen.blit(label, tuple(pos))

        # Selected Object
        pos[1] += DY
        display = 'B) Range / Vel  / Azi / Freq_Idx / Pow  / Ele / RCS / NumTrk / Prob'
        label = InfoFont3.render(display, 1, Color.navy)
        screen.blit(label, tuple(pos))

        colorL = Color.white
        for idx in range(len(SelData['RefObj'])):
            pos[1] += DY

            ObjDict = ObjectDataParsing(Ref_ObjInfo[SelData['RefObj'][idx]])
            display = GetObjDataStr(ObjDict)
            label = InfoFont3.render(display, 1, colorL)
            screen.blit(label, tuple(pos))
    '''


def GetTrkDataStr(TrkDict):

    TrkInfo = (TrkDict['TrkIdx'], TrkDict['Status'], TrkDict['MovStat'],
               TrkDict['PosX'], TrkDict['PosY'], TrkDict['VelX'], TrkDict['VelY'],
               TrkDict['HeadingAng'], TrkDict['Length'], TrkDict['Width'], TrkDict['AssoObjCnt'], TrkDict['AssoTklCnt'])
    display = '%03d | %03d | %03d | %3.1f | %3.1f | %3.1f | %3.1f | %d | %3.1f | %3.1f | %03d | %03d' % TrkInfo

    return display


def GetTrkletDataStr(TrkletDict):

    TrkletInfo = (TrkletDict['TrkletIdx'], TrkletDict['Status'], TrkletDict['MovStat'],
                  TrkletDict['PosX'], TrkletDict['PosY'], TrkletDict['VelX'], TrkletDict['VelY'],
                  TrkletDict['AssoObjIdx'], TrkletDict['GroupTrkIdx'])
    display = '%03d | %03d | %03d | %3.1f | %3.1f | %3.1f | %3.1f | %03d | %03d'  % TrkletInfo

    return display


def GetObjDataStr(ObjDict):

    if ObjDict['Beam'] == 0:
        str_Beam = 'C'
    elif ObjDict['Beam'] == 1:
        str_Beam = 'L'
    elif ObjDict['Beam'] == 2:
        str_Beam = 'R'
    elif ObjDict['Beam'] == 3:
        str_Beam = 'L2'
    elif ObjDict['Beam'] == 4:
        str_Beam = 'R2'

    ObjInfo = (ObjDict['R'], ObjDict['V'], ObjDict['AziAng'], ObjDict['IdxR'], ObjDict['IdxD'], ObjDict['Pow'], ObjDict['EleAng'], ObjDict['RCS'], ObjDict['NumTrk'], ObjDict['TargetProb'])
    display = '%1d-' % ObjDict['Chirp'] + str_Beam + '> %3.1f / %3.2f / %2.1f / [%3d,%3d] / %2.1f / %2.1f / %2.1f / %1d / %2.2f' % ObjInfo

    return display


def DrawLogInfo(screen, SimInfo):

    screen.fill(Color.black)

    # --- Signal Processing Information ---
    DY = 17
    X_ORG = 15
    Y_ORG = 5
    pos = [X_ORG, Y_ORG]

    display = '[ LoggingData Information ]'
    label = InfoFont1.render(display, 1, Color.goldenrod)
    screen.blit(label, tuple(pos))

    # ------------------
    pos[1] += DY
    display = 'Sample Number : #%04s' % hex(int(SimInfo['Sim_SampleNumber'].value))
    label = InfoFont2.render(display, 1, Color.white)
    screen.blit(label, tuple(pos))

    # ------------------
    pos[1] += DY
    Sp_NowProcess = SimInfo['Sim_CurrentPRF'].value
    if Sp_NowProcess == 0:
        display = 'PRF 1st'
        label = InfoFont2.render(display, 1, Color.aqua)
    else:
        display = 'PRF 2nd'
        label = InfoFont2.render(display, 1, Color.tomato)
    screen.blit(label, tuple(pos))

    # ------------------
    pos[1] += DY
    display = 'Radar ScanIdx : %1d' % (SimInfo['Sim_RadarScanIdx'].value)
    label = InfoFont2.render(display, 1, Color.white)
    screen.blit(label, tuple(pos))

    # ------------------
    pos[1] += DY
    display = 'Cycle Time : %3d msec' % (SimInfo['Sim_CycleTime'].value * 0.1)
    label = InfoFont2.render(display, 1, Color.white)
    screen.blit(label, tuple(pos))

