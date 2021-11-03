import pygame
import math

import ColorTable as color
from GUI_DataParsing import *
from GUI_KeyState import *

pygame.init()
pygame.font.init()
myFont1 = pygame.font.Font('./font/210 Haesol R.ttf', 24)
myFont2 = pygame.font.Font('./font/210 Haesol R.ttf', 20)
myFont3 = pygame.font.Font('./font/210 Haesol R.ttf', 22)
myFont4 = pygame.font.Font('./font/210 Haesol R.ttf', 12)
BGImage = pygame.image.load('./Image/Wise+Gray+Dark+Tone.JPG')
CAR_Image = pygame.image.load('./Image/CAR1.JPG')

ColorTable = [[]] * 5
a = ColorTable[0]
ColorTable[0] = [color.aquamarine, color.mistyrose, color.gray]
ColorTable[1] = [color.greenyellow, color.mistyrose, color.gray]
ColorTable[2] = [color.orangered, color.mistyrose, color.gray]
ColorTable[3] = [color.blueviolet, color.mistyrose, color.gray]
ColorTable[4] = [color.blueviolet, color.mistyrose, color.rosybrown]


def DrawBirdView(screen, TR_View, KeyState, SimData, SelObj, SelTrk, NumPlot=0):
    SimDict = dict()
    # Data Import
    ObjInfo = SimData['Sim_ObjInfo'].value
    ObjInfo_Ref = SimData['Sim_REF_ObjInfo'].value
    ObjInfo_fil = SimData['Sim_FilObjInfo'].value
    TrkletInfo = SimData['Sim_TrkletInfo'].value
    TrkInfo = SimData['Sim_TrkInfo'].value

    if 'Sim_NumLane' in SimData:
        TrafficInfo = dict()
        TrafficInfo['NumLane'] = SimData['Sim_NumLane'].value
        TrafficInfo['NumLaneStep'] = SimData['Sim_NumLaneStep'].value
        TrafficInfo['LeftLane_X'] = SimData['Sim_LeftLane_X'].value
        TrafficInfo['LeftLane_Y'] = SimData['Sim_LeftLane_Y'].value
        TrafficInfo['RightLane_X'] = SimData['Sim_RightLane_X'].value
        TrafficInfo['RightLane_Y'] = SimData['Sim_RightLane_Y'].value

        DrawTrafficLane(screen, TR_View, TrafficInfo)

    # Draw reference

    '''
    if not KeyState.Key_r:
        if 'Sim_Ref_BBox' and 'Sim_Ref_Vel' in SimData:
            DrawReference(screen, TR_View, KeyState, SimData['Sim_Ref_BBox'].value, SimData['Sim_Ref_Vel'].value)
    '''

    # Draw Draw Object / Tracklet / Track / Connection
    if not KeyState.Key_o:
        DrawObject(screen, TR_View, KeyState, ObjInfo, SelObj, ColorTable[NumPlot])

    if KeyState.Key_r:
        DrawObject(screen, TR_View, KeyState, ObjInfo_Ref, SelObj, ColorTable[NumPlot])

    if KeyState.Key_f:
        DrawObject(screen, TR_View, KeyState, ObjInfo_fil, SelObj, ColorTable[NumPlot])

    if KeyState.Key_l:
        DrawTracklet(screen, TR_View, KeyState, TrkletInfo)
    if not KeyState.Key_t:
        DrawTrack(screen, TR_View, KeyState, TrkInfo, SelTrk)
    if KeyState.Key_c:
        DrawConnection(screen, TR_View, KeyState, ObjInfo, TrkletInfo, TrkInfo)


def DrawBirdView_Log(screen, TR_View, KeyState, LogData, SelObj, SelTrk, NumPlot=0):
    # Data Import
    ObjInfo = LogData['Sim_ObjInfo'].value
    TrkInfo = LogData['Sim_TrkInfo'].value

    # Draw Object / Track
    if not KeyState.Key_o:
        DrawObject_Log(screen, TR_View, KeyState, ObjInfo, SelObj, ColorTable[NumPlot])

    if not KeyState.Key_t:
        DrawTrack_Log(screen, TR_View, KeyState, TrkInfo, SelTrk)


def DrawObject(screen, TR_View, KeyState, ObjInfo, SelObj, ObjColor):
    Obj_h, Obj_w = TR_View.getSizeD2P((5, -3))
    StatVel = 2.0

    # Draw Object
    for idx in range(len(ObjInfo)):
        if ObjInfo[idx][0] != 0:
            ObjDict = ObjectDataParsing(ObjInfo[idx])
            R = ObjDict['R']
            V = ObjDict['V']
            AziAng = ObjDict['AziAng']
            EleAng = ObjDict['EleAng']
            MeasIdx = ObjDict['Chirp']
            RIdx = ObjDict['IdxR']
            DIdx = ObjDict['IdxD']

            # PosX = R * math.cos(AziAng / 180 * math.pi) * math.cos(EleAng / 180 * math.pi)
            # PosY = - R * math.sin(AziAng / 180 * math.pi) * math.cos(EleAng / 180 * math.pi)
            PosZ = R * math.sin(EleAng / 180 * math.pi)

            PosX = R * math.cos(AziAng / 180 * math.pi)
            PosY = - R * math.sin(AziAng / 180 * math.pi)
            # PosY = R * math.sin(AziAng / 180 * math.pi)
            PosZ = R * math.sin(EleAng / 180 * math.pi)

            phys_pos = PosY, PosX

            VelX = V / math.cos(AziAng / 180 * math.pi)
            # VelY = V / math.sin(AziAng / 180 * math.pi)

            if (EleAng >= -1) and (EleAng < 1):
                # colorL = ObjColor[0]
                colorL = color.blue
                lwidth = 1
            elif (EleAng >= 1) and (EleAng < 6):
                # colorL = ObjColor[1]
                colorL = color.yellow
                lwidth = 1
            elif (EleAng >= 6):
                # colorL = ObjColor[2]
                colorL = color.red
                lwidth = 1
            else:
                # colorL = ObjColor[0]
                colorL = color.darkgray
                lwidth = 1

            '''
            if VelX >= StatVel:  # Moving
                colorT = color.darkgray
                colorL = ObjColor[0]
                lwidth = 2

            elif VelX <= -StatVel:  # OnComming
                colorT = color.darkgray
                #colorL = ObjColor[1]
                colorL = color.yellow
                lwidth = 2

            elif abs(VelX) >= 30:
                #colorT = color.darkgray
                colorL = colorT = color.red
                lwidth = 2
            else:
                colorT = color.darkgray
                colorL = ObjColor[2]
                lwidth = 2
            '''

            disp_pos = TR_View.getPointP2D(phys_pos)
            disp_off = TR_View.getSizeP2D((Obj_h, Obj_w))
            disp_pos = disp_pos[0] - disp_off[0] / 2, disp_pos[1] - disp_off[1] / 2

            # Display Measurement Idx
            if KeyState.Key_i:
                if (MeasIdx != -1.0):
                    label = myFont4.render('%d [%d %d]' % (MeasIdx, RIdx, DIdx), True, color.lightgrey)
                    screen.blit(label, (disp_pos[0], disp_pos[1] + 0.5))

            pygame.draw.rect(screen, colorL, disp_pos + disp_off, lwidth)

            # display velocity vector
            msmt_pos = TR_View.getPointP2D(phys_pos)
            PosX = (R + V) * math.cos(AziAng / 180 * math.pi)
            PosY = (R + V) * math.sin(AziAng / 180 * math.pi)
            phys_pos = PosY, PosX
            msmt_pos_end = TR_View.getPointP2D(phys_pos)
            # pygame.draw.line(screen, color.white, msmt_pos, msmt_pos_end, 1)

            # Selected Object
            for idx2 in range(len(SelObj)):
                if idx == SelObj[idx2]:
                    disp_pos = (disp_pos[0] - lwidth, disp_pos[1] + lwidth)
                    disp_off = (disp_off[0] + (2 * lwidth), disp_off[1] - (2 * lwidth))
                    pygame.draw.rect(screen, color.maroon, disp_pos + disp_off, lwidth)

            # object text
            # label = myFont2.render('%d' % idx, 1, colorT)
            # screen.blit(label, (disp_pos[0], disp_pos[1]-15) )


def DrawTracklet(screen, TR_View, KeyState, TrkletInfo):
    NewTrkletEnable = KeyState.Key_n
    offset_len = 0.5

    for idx in range(len(TrkletInfo)):
        TrkletDict = TrackletDataParsing(TrkletInfo[idx])
        TrkletIdx = TrkletDict['TrkletIdx']
        Status = TrkletDict['Status']
        PosX = TrkletDict['PosX']
        PosY = TrkletDict['PosY']
        VelX = TrkletDict['VelX']
        VelY = TrkletDict['VelY']
        MovStat = TrkletDict['MovStat']
        AssoObjIdx = TrkletDict['AssoObjIdx']
        GroupTrkIdx = TrkletDict['GroupTrkIdx']

        # if (Status == 1 and NewTrkletEnable) or (Status >= 2):
        #    if (MovStat == 1) or (MovStat == 2):  # Moving (1 : Moving / 2 : Stopped)
        if (Status == 3):
            colorL = color.lightcoral
        else:
            colorL = color.firebrick

        colorT = color.slategray
        ref_radius = 4

        Trklet_pos = (PosY, PosX)
        TrkletPos = TR_View.getPointP2D(Trklet_pos)

        pygame.draw.circle(screen, colorL, TrkletPos, ref_radius)

        if KeyState.Key_i:
            label = myFont3.render('%d' % (TrkletIdx), True, colorT)
            screen.blit(label, (TrkletPos[0], TrkletPos[1] + offset_len))

        # display velocity vector
        Trklet_pos = (PosY, PosX)
        disp_pos_VelEnd = TR_View.getPointP2D((PosY + VelY, PosX + VelX))
        pygame.draw.line(screen, color.orangered, TrkletPos, disp_pos_VelEnd, 1)

        # display velocity vector
        Trklet_pos = (PosY, PosX)
        disp_pos_VelMsmtEnd = TR_View.getPointP2D((PosY + TrkletDict['VelMsmtY'], PosX + TrkletDict['VelMsmtX']))
        pygame.draw.line(screen, color.orange, TrkletPos, disp_pos_VelMsmtEnd, 1)

        # Display Tracklet status age
        if KeyState.Key_a:
            label = myFont2.render('%d' % (TrkletDict['StatusAge']), True, colorL)
            screen.blit(label, (TrkletPos[0], TrkletPos[1] + 0.5))


def DrawReference(screen, TR_View, KeyState, Ref_BBox, Ref_Vel):
    BBox0 = TR_View.getPointP2D((Ref_BBox[1][0], Ref_BBox[0][0]))
    BBox1 = TR_View.getPointP2D((Ref_BBox[1][1], Ref_BBox[0][1]))
    BBox2 = TR_View.getPointP2D((Ref_BBox[1][2], Ref_BBox[0][2]))
    BBox3 = TR_View.getPointP2D((Ref_BBox[1][3], Ref_BBox[0][3]))

    Center_x = (Ref_BBox[0][0] + Ref_BBox[0][2]) * 0.5
    Center_y = (Ref_BBox[1][0] + Ref_BBox[1][2]) * 0.5
    CenterPt_disp = TR_View.getPointP2D((Center_y, Center_x))
    VectorEnd_disp = TR_View.getPointP2D((Center_y + Ref_Vel[1], Center_x + Ref_Vel[0]))

    lwidth = 2
    lcolor = color.red

    pygame.draw.polygon(screen, lcolor, [BBox0, BBox1, BBox2, BBox3], lwidth)
    pygame.draw.line(screen, lcolor, CenterPt_disp, VectorEnd_disp, lwidth)


def DrawTrack(screen, TR_View, KeyState, TrkInfo, SelTrk):
    # Draw Configuration
    NewTrackEnable = KeyState.Key_n

    for idx in range(len(TrkInfo)):
        TrkDict = TrackDataParsing(TrkInfo[idx])
        TrkIdx = TrkDict['TrkIdx']
        Status = TrkDict['Status']
        AliveAge = TrkDict['AliveAge']
        StatusAge = TrkDict['StatusAge']
        MovState = TrkDict['MovStat']
        PosX = TrkDict['PosX']
        PosY = TrkDict['PosY']
        VelX = TrkDict['VelX']
        VelY = TrkDict['VelY']
        HeadingAng = TrkDict['HeadingAng']
        HeadingAngRate = TrkDict['HeadingAngRate']
        Pow = TrkDict['POW']
        Length = TrkDict['Length']
        Width = TrkDict['Width']
        RefPosX = TrkDict['RefPosX']
        RefPosY = TrkDict['RefPosY']
        MergeFlag = TrkDict['MergFlag']
        AssoGateX = TrkDict['AssoGateX']
        AssoGateY = TrkDict['AssoGateY']

        if (Status == 1 and NewTrackEnable) or (Status >= 2):

            if (MovState == 1) or (MovState == 2):  # Moving (1 : Moving / 2 : Stopped)
                colorT = color.white
                colorL = color.yellow
                lwidth = 1
                ref_radius = 4

                # Draw Track
                rotate_pos_x = PosX * math.cos(HeadingAng * math.pi / 180.) + PosY * math.sin(
                    HeadingAng * math.pi / 180.)
                rotate_pos_y = -PosX * math.sin(HeadingAng * math.pi / 180.) + PosY * math.cos(
                    HeadingAng * math.pi / 180.)

                BBox_X = (rotate_pos_x + (Length / 2)) * math.cos(HeadingAng * math.pi / 180.) - (
                        rotate_pos_y + (Width / 2)) * math.sin(HeadingAng * math.pi / 180.)
                BBox_Y = (rotate_pos_x + (Length / 2)) * math.sin(HeadingAng * math.pi / 180.) + (
                        rotate_pos_y + (Width / 2)) * math.cos(HeadingAng * math.pi / 180.)
                BBox0 = TR_View.getPointP2D((BBox_Y, BBox_X))

                BBox_X = (rotate_pos_x + (Length / 2)) * math.cos(HeadingAng * math.pi / 180.) - (
                        rotate_pos_y - (Width / 2)) * math.sin(HeadingAng * math.pi / 180.)
                BBox_Y = (rotate_pos_x + (Length / 2)) * math.sin(HeadingAng * math.pi / 180.) + (
                        rotate_pos_y - (Width / 2)) * math.cos(HeadingAng * math.pi / 180.)
                BBox1 = TR_View.getPointP2D((BBox_Y, BBox_X))

                BBox_X = (rotate_pos_x - (Length / 2)) * math.cos(HeadingAng * math.pi / 180.) - (
                        rotate_pos_y - (Width / 2)) * math.sin(HeadingAng * math.pi / 180.)
                BBox_Y = (rotate_pos_x - (Length / 2)) * math.sin(HeadingAng * math.pi / 180.) + (
                        rotate_pos_y - (Width / 2)) * math.cos(HeadingAng * math.pi / 180.)
                BBox2 = TR_View.getPointP2D((BBox_Y, BBox_X))

                BBox_X = (rotate_pos_x - (Length / 2)) * math.cos(HeadingAng * math.pi / 180.) - (
                        rotate_pos_y + (Width / 2)) * math.sin(HeadingAng * math.pi / 180.)
                BBox_Y = (rotate_pos_x - (Length / 2)) * math.sin(HeadingAng * math.pi / 180.) + (
                        rotate_pos_y + (Width / 2)) * math.cos(HeadingAng * math.pi / 180.)
                BBox3 = TR_View.getPointP2D((BBox_Y, BBox_X))

                RefPos = TR_View.getPointP2D((RefPosY, RefPosX))

                # display velocity vector
                disp_pos_VelEnd = TR_View.getPointP2D((RefPosY + VelY, RefPosX + VelX))
                # pygame.draw.line(screen, color.yellow, RefPos, disp_pos_VelEnd, 2)

                # display velocity vector from trajectory
                if TrkDict['StatusAge'] >= 10:
                    disp_pos_VelHistEnd = TR_View.getPointP2D(
                        (RefPosY + TrkDict['VelY_Hist'], RefPosX + TrkDict['VelX_Hist']))
                    # pygame.draw.line(screen, color.red, RefPos, disp_pos_VelHistEnd, 2)

                # pygame.draw.polygon(screen, colorL, [BBox0, BBox1, BBox2, BBox3], lwidth)
                # pygame.draw.circle(screen, colorL, RefPos, ref_radius)

                phys_pos = PosY, PosX
                disp_pos = TR_View.getPointP2D(phys_pos)
                disp_off = TR_View.getSizeP2D((Width, -Length))
                disp_pos = disp_pos[0] - disp_off[0] / 2, disp_pos[1] - disp_off[1] / 2

                # Display Info
                if KeyState.Key_i:
                    label = myFont1.render('%d' % (TrkIdx), True, colorT)
                    screen.blit(label, (disp_pos[0], disp_pos[1] + disp_off[1]))

                # Display Track status age
                if KeyState.Key_a:
                    label = myFont2.render('%d' % (TrkDict['StatusAge']), True, colorL)
                    screen.blit(label, (disp_pos[0], disp_pos[1] + 0.5))

                # Selected Track
                for idx2 in range(len(SelTrk)):
                    if idx == SelTrk[idx2]:
                        BBox0 = (BBox0[0] - lwidth, BBox0[1] - lwidth)
                        BBox1 = (BBox1[0] + lwidth, BBox1[1] - lwidth)
                        BBox2 = (BBox2[0] + lwidth, BBox2[1] + lwidth)
                        BBox3 = (BBox3[0] - lwidth, BBox3[1] + lwidth)
                        pygame.draw.polygon(screen, color.maroon, [BBox0, BBox1, BBox2, BBox3], lwidth)

                # Track Gate
                if KeyState.Key_m:
                    lwidth = 1

                    if Status == 1:
                        disp_pos = TR_View.getPointP2D(phys_pos)
                        disp_off = TR_View.getSizeP2D((2 * AssoGateY, -2 * AssoGateX))
                        if disp_off[1] == 0:
                            print(disp_off)
                        disp_pos = disp_pos[0] - disp_off[0] / 2, disp_pos[1] - disp_off[1] / 2
                        pygame.draw.ellipse(screen, colorL, disp_pos + disp_off, lwidth)
                    else:
                        BBox_X = (rotate_pos_x + AssoGateX) * math.cos(HeadingAng * math.pi / 180.) - (
                                rotate_pos_y + AssoGateY) * math.sin(HeadingAng * math.pi / 180.)
                        BBox_Y = (rotate_pos_x + AssoGateX) * math.sin(HeadingAng * math.pi / 180.) + (
                                rotate_pos_y + AssoGateY) * math.cos(HeadingAng * math.pi / 180.)
                        BBox0 = TR_View.getPointP2D((BBox_Y, BBox_X))

                        BBox_X = (rotate_pos_x + AssoGateX) * math.cos(HeadingAng * math.pi / 180.) - (
                                rotate_pos_y - AssoGateY) * math.sin(HeadingAng * math.pi / 180.)
                        BBox_Y = (rotate_pos_x + AssoGateX) * math.sin(HeadingAng * math.pi / 180.) + (
                                rotate_pos_y - AssoGateY) * math.cos(HeadingAng * math.pi / 180.)
                        BBox1 = TR_View.getPointP2D((BBox_Y, BBox_X))

                        BBox_X = (rotate_pos_x - AssoGateX) * math.cos(HeadingAng * math.pi / 180.) - (
                                rotate_pos_y - AssoGateY) * math.sin(HeadingAng * math.pi / 180.)
                        BBox_Y = (rotate_pos_x - AssoGateX) * math.sin(HeadingAng * math.pi / 180.) + (
                                rotate_pos_y - AssoGateY) * math.cos(HeadingAng * math.pi / 180.)
                        BBox2 = TR_View.getPointP2D((BBox_Y, BBox_X))

                        BBox_X = (rotate_pos_x - AssoGateX) * math.cos(HeadingAng * math.pi / 180.) - (
                                rotate_pos_y + AssoGateY) * math.sin(HeadingAng * math.pi / 180.)
                        BBox_Y = (rotate_pos_x - AssoGateX) * math.sin(HeadingAng * math.pi / 180.) + (
                                rotate_pos_y + AssoGateY) * math.cos(HeadingAng * math.pi / 180.)
                        BBox3 = TR_View.getPointP2D((BBox_Y, BBox_X))

                        pygame.draw.polygon(screen, colorL, [BBox0, BBox1, BBox2, BBox3], lwidth)

            else:
                colorT = color.white
                colorL = color.gray
                lwidth = 1
                ref_radius = 1


def DrawTrack_Log(screen, TR_View, KeyState, TrkInfo, SelTrk):
    # Draw Configuration
    NewTrackEnable = KeyState.Key_n

    for idx in range(len(TrkInfo)):
        TrkDict_log = TrackDataParsing_Log(TrkInfo[idx])
        TrkIdx = TrkDict_log['TrkIdx']
        Status = TrkDict_log['Status']
        UpdStat = TrkDict_log['UpdStat']
        MovState = TrkDict_log['MovStat']
        AliveAge = TrkDict_log['AliveAge']
        PosX = TrkDict_log['PosX']
        PosY = TrkDict_log['PosY']
        RefPosX = TrkDict_log['RefPosX']
        RefPosY = TrkDict_log['RefPosY']
        VelX = TrkDict_log['VelX']
        VelY = TrkDict_log['VelY']
        HeadingAng = TrkDict_log['HeadingAng']
        Pow = TrkDict_log['POW']
        Width = TrkDict_log['Width']
        Length = TrkDict_log['Length']

        if (Status == 1 and NewTrackEnable) or (Status == 2):

            if (MovState == 1) or (MovState == 2):  # Moving (1 : Moving / 2 : Stopped)
                colorT = color.white
                colorL = color.yellow
                lwidth = 2
            else:
                colorT = color.white
                colorL = color.gray
                lwidth = 1

            # Draw Track
            rotate_pos_x = PosX * math.cos(HeadingAng * math.pi / 180.) + PosY * math.sin(
                HeadingAng * math.pi / 180.)
            rotate_pos_y = -PosX * math.sin(HeadingAng * math.pi / 180.) + PosY * math.cos(
                HeadingAng * math.pi / 180.)

            BBox_X = (rotate_pos_x + (Length / 2)) * math.cos(HeadingAng * math.pi / 180.) - (
                    rotate_pos_y + (Width / 2)) * math.sin(HeadingAng * math.pi / 180.)
            BBox_Y = (rotate_pos_x + (Length / 2)) * math.sin(HeadingAng * math.pi / 180.) + (
                    rotate_pos_y + (Width / 2)) * math.cos(HeadingAng * math.pi / 180.)
            BBox0 = TR_View.getPointP2D((BBox_Y, BBox_X))

            BBox_X = (rotate_pos_x + (Length / 2)) * math.cos(HeadingAng * math.pi / 180.) - (
                    rotate_pos_y - (Width / 2)) * math.sin(HeadingAng * math.pi / 180.)
            BBox_Y = (rotate_pos_x + (Length / 2)) * math.sin(HeadingAng * math.pi / 180.) + (
                    rotate_pos_y - (Width / 2)) * math.cos(HeadingAng * math.pi / 180.)
            BBox1 = TR_View.getPointP2D((BBox_Y, BBox_X))

            BBox_X = (rotate_pos_x - (Length / 2)) * math.cos(HeadingAng * math.pi / 180.) - (
                    rotate_pos_y - (Width / 2)) * math.sin(HeadingAng * math.pi / 180.)
            BBox_Y = (rotate_pos_x - (Length / 2)) * math.sin(HeadingAng * math.pi / 180.) + (
                    rotate_pos_y - (Width / 2)) * math.cos(HeadingAng * math.pi / 180.)
            BBox2 = TR_View.getPointP2D((BBox_Y, BBox_X))

            BBox_X = (rotate_pos_x - (Length / 2)) * math.cos(HeadingAng * math.pi / 180.) - (
                    rotate_pos_y + (Width / 2)) * math.sin(HeadingAng * math.pi / 180.)
            BBox_Y = (rotate_pos_x - (Length / 2)) * math.sin(HeadingAng * math.pi / 180.) + (
                    rotate_pos_y + (Width / 2)) * math.cos(HeadingAng * math.pi / 180.)
            BBox3 = TR_View.getPointP2D((BBox_Y, BBox_X))

            if (MovState == 1) or (MovState == 2):
                ref_radius = 4
            else:
                ref_radius = 1

            RefPos = TR_View.getPointP2D((RefPosY, RefPosX))

            phys_pos = PosY, PosX
            disp_pos = TR_View.getPointP2D(phys_pos)
            disp_off = TR_View.getSizeP2D((Width, -Length))
            disp_pos = disp_pos[0] - disp_off[0] / 2, disp_pos[1] - disp_off[1] / 2

            pygame.draw.polygon(screen, colorL, [BBox0, BBox1, BBox2, BBox3], lwidth)
            pygame.draw.circle(screen, colorL, RefPos, ref_radius)

            if (MovState == 1) or (MovState == 2):
                # Display Info
                label = myFont1.render('%d' % (TrkIdx), True, colorT)
                screen.blit(label, (disp_pos[0], disp_pos[1] + disp_off[1]))


def DrawObject_Log(screen, TR_View, KeyState, ObjInfo, SelObj, ObjColor):
    Obj_h, Obj_w = TR_View.getSizeD2P((5, -3))
    StatVel = 2.0

    # Draw Object
    for idx in range(len(ObjInfo)):
        if ObjInfo[idx][0] != 0:
            ObjDict = ObjectDataParsing_Log(ObjInfo[idx])
            R = ObjDict['R']
            V = ObjDict['V']
            AziAng = ObjDict['AziAng']

            PosX = R * math.cos(AziAng / 180 * math.pi)
            PosY = R * math.sin(AziAng / 180 * math.pi)
            phys_pos = PosY, PosX

            VelX = V / math.cos(AziAng / 180 * math.pi)
            # VelY = V / math.sin(AziAng / 180 * math.pi)

            if VelX >= StatVel:  # Moving
                colorT = color.darkgray
                colorL = ObjColor[0]
                lwidth = 2

            elif VelX <= -StatVel:  # OnComming
                colorT = color.darkgray
                # colorL = ObjColor[1]
                colorL = color.yellow
                lwidth = 2

            else:
                colorT = color.darkgray
                colorL = ObjColor[2]
                lwidth = 2

            disp_pos = TR_View.getPointP2D(phys_pos)
            disp_off = TR_View.getSizeP2D((Obj_h, Obj_w))
            disp_pos = disp_pos[0] - disp_off[0] / 2, disp_pos[1] - disp_off[1] / 2

            pygame.draw.rect(screen, colorL, disp_pos + disp_off, lwidth)


def DrawConnection(screen, TR_View, KeyState, ObjInfo, TrkletInfo, TrkInfo):
    NewTrkletEnable = KeyState.Key_n
    offset_len = 0.5

    # (Object <=> Trklet) and (Object <=> Track)
    for idx in range(len(ObjInfo)):

        if ObjInfo[idx][0] != 0:

            ObjDict = ObjectDataParsing(ObjInfo[idx])
            Obj_R = ObjDict['R']
            Obj_AziAng = ObjDict['AziAng']
            Obj_TklNum = ObjDict['TklIdx']
            Obj_TrkNum = ObjDict['TrkIdx']

            Obj_PosX = Obj_R * math.cos(Obj_AziAng / 180 * math.pi)
            Obj_PosY = Obj_R * math.sin(Obj_AziAng / 180 * math.pi)
            Obj_pos = TR_View.getPointP2D((Obj_PosY, Obj_PosX))

            # (Object <=> Trklet)
            if (Obj_TklNum != -1.0):
                TklDict = TrackletDataParsing(TrkletInfo[Obj_TklNum])
                Tkl_Status = TklDict['Status']
                Tkl_MovStat = TklDict['MovStat']
                Tkl_PosX = TklDict['PosX']
                Tkl_PosY = TklDict['PosY']

                Tkl_pos = TR_View.getPointP2D((Tkl_PosY, Tkl_PosX))

                if (Tkl_Status == 1 and NewTrkletEnable) or (Tkl_Status >= 2):
                    if (Tkl_MovStat == 1) or (Tkl_MovStat == 2):
                        pygame.draw.line(screen, color.darkgreen, Obj_pos, Tkl_pos)

            # (Object <=> Track)
            if (Obj_TrkNum != -1.0):
                TrkDict = TrackDataParsing(TrkInfo[Obj_TrkNum])
                Trk_Status = TrkDict['Status']
                Trk_MovStat = TrkDict['MovStat']
                Trk_PosX = TrkDict['PosX']
                Trk_PosY = TrkDict['PosY']

                Trk_pos = TR_View.getPointP2D((Trk_PosY, Trk_PosX))

                if (Trk_Status == 1 and NewTrkletEnable) or (Trk_Status >= 2):
                    if (Trk_MovStat == 1) or (Trk_MovStat == 2):
                        pygame.draw.line(screen, color.dodgerblue, Obj_pos, Trk_pos)
                        pygame.draw.circle(screen, color.darkorange, Trk_pos, 1)

    # (Tracklet <=> Track)
    for idx in range(len(TrkletInfo)):
        TklDict = TrackletDataParsing(TrkletInfo[idx])
        Tkl_Status = TklDict['Status']
        Tkl_MovStat = TklDict['MovStat']
        Tkl_PosX = TklDict['PosX']
        Tkl_PosY = TklDict['PosY']
        Tkl_GroupTrkIdx = TklDict['GroupTrkIdx']

        Tkl_pos = TR_View.getPointP2D((Tkl_PosY, Tkl_PosX))

        if (Tkl_GroupTrkIdx != -1.0):
            TrkDict = TrackDataParsing(TrkInfo[Tkl_GroupTrkIdx])
            Trk_PosX = TrkDict['PosX']
            Trk_PosY = TrkDict['PosY']

            Trk_pos = TR_View.getPointP2D((Trk_PosY, Trk_PosX))

            if (Tkl_Status == 1 and NewTrkletEnable) or (Tkl_Status >= 2):
                if (Tkl_MovStat == 1) or (Tkl_MovStat == 2):
                    pygame.draw.line(screen, color.hotpink, Tkl_pos, Trk_pos)
                    pygame.draw.circle(screen, color.darkorange, Trk_pos, 1)


def DrawGrid(screen, TR_View, BG_Image=False):
    temp_WinSize = TR_View.DispRect[2], TR_View.DispRect[3]
    LeftTop_Pos = TR_View.PhysRect[0], TR_View.PhysRect[1]
    RightBottom_Pos = TR_View.PhysRect[0] + TR_View.PhysRect[2], TR_View.PhysRect[1] + TR_View.PhysRect[3]

    # for adaptive scaling for longitudinal lines
    dw = TR_View.getSizeD2P((40, -40))
    dx = max(1, int(dw[0]))  # minimum resolution : 1
    dy = max(1, int(dw[1]))
    if (dy % 2 == 1) and (dy > 1) and (dy != 5):
        dy -= 1
    if dy > 5:
        dy = 10

    # Image
    if BG_Image:
        screen.blit(pygame.transform.scale(BGImage, temp_WinSize), (0, 0))

    # Color
    colorL = color.darkgray
    colorT = color.lightslategray

    # Lateral Lines
    for i in range(RightBottom_Pos[1], LeftTop_Pos[1], dy):
        p1 = TR_View.getPointP2D((LeftTop_Pos[0], i))
        p2 = TR_View.getPointP2D((RightBottom_Pos[0], i))
        pt = TR_View.getPointP2D((-4, i))

        pygame.draw.line(screen, colorL, p1, p2, 1)
        label = myFont1.render(str(i), 1, colorT)
        screen.blit(label, (5, pt[1]))

    # Longitudinal Lines
    for i in range(0, RightBottom_Pos[0], dx):
        p1 = TR_View.getPointP2D((i, RightBottom_Pos[1]))
        p2 = TR_View.getPointP2D((i, LeftTop_Pos[1]))
        pt = TR_View.getPointP2D((i, 10))
        pygame.draw.line(screen, colorL, p1, p2, 1)
        label = myFont1.render(str(i * 1), 1, colorT)
        screen.blit(label, (pt[0], temp_WinSize[1] - 20))

    for i in range(0, LeftTop_Pos[0], -dx):
        p1 = TR_View.getPointP2D((i, RightBottom_Pos[1]))
        p2 = TR_View.getPointP2D((i, LeftTop_Pos[1]))
        pt = TR_View.getPointP2D((i, 10))
        pygame.draw.line(screen, colorL, p1, p2, 1)
        label = myFont1.render(str(i * 1), 1, colorT)
        screen.blit(label, (pt[0], temp_WinSize[1] - 20))

    # Center Line
    p1 = TR_View.getPointP2D((LeftTop_Pos[0], 0))
    p2 = TR_View.getPointP2D((RightBottom_Pos[0], 0))
    pygame.draw.line(screen, color.darkgray, p1, p2, 2)

    p1 = TR_View.getPointP2D((0, LeftTop_Pos[1]))
    p2 = TR_View.getPointP2D((0, RightBottom_Pos[1]))
    pygame.draw.line(screen, color.darkgray, p1, p2, 2)

    # Car Image
    p1 = TR_View.getPointP2D((-1, 0))
    s1 = TR_View.getSizeP2D((2, -5))
    screen.blit(pygame.transform.scale(CAR_Image, s1), p1)


def DrawTrafficLane(screen, TR_View, TrafficInfo):
    lane_color = color.aliceblue

    for lane in range(TrafficInfo['NumLane'][0]):
        linesL = []
        linesR = []

        step_len = TrafficInfo['NumLaneStep'][lane]
        drawL_Y = TrafficInfo['LeftLane_X'][lane][:step_len[0]]
        drawL_X = TrafficInfo['LeftLane_Y'][lane][:step_len[0]]
        drawR_Y = TrafficInfo['RightLane_X'][lane][:step_len[0]]
        drawR_X = TrafficInfo['RightLane_Y'][lane][:step_len[0]]

        for idx in range(len(drawL_Y)):
            pL = TR_View.getPointP2D((drawL_X[idx], drawL_Y[idx]))
            pR = TR_View.getPointP2D((drawR_X[idx], drawR_Y[idx]))

            linesL.append(pL)
            linesR.append(pR)

        pygame.draw.lines(screen, lane_color, False, linesL, 3)
        pygame.draw.lines(screen, lane_color, False, linesR, 3)

    return


def DrawFoVAng(screen, TR_View, RangeFoV, AngFoV, Color=False):
    if not Color:
        colorL = (0xd4, 0xaa, 0x00)
    else:
        colorL = Color

    temp_Pos = RangeFoV[0], RangeFoV[1]
    temp_R = RangeFoV[2]
    temp_BeamAng = AngFoV[0]
    temp_Ang1 = AngFoV[1] + temp_BeamAng
    temp_Ang2 = -AngFoV[1] + temp_BeamAng

    p1 = TR_View.getPointP2D((temp_Pos[0], temp_Pos[1]))
    p2 = TR_View.getPointP2D((temp_R * math.sin(temp_Ang1 * math.pi / 180.) + temp_Pos[0],
                              temp_R * math.cos(temp_Ang1 * math.pi / 180.) + temp_Pos[1]))
    pygame.draw.line(screen, colorL, p1, p2, 1)

    p1 = TR_View.getPointP2D((temp_Pos[0], temp_Pos[1]))
    p2 = TR_View.getPointP2D((temp_R * math.sin(temp_Ang2 * math.pi / 180.) + temp_Pos[0],
                              temp_R * math.cos(temp_Ang2 * math.pi / 180.) + temp_Pos[1]))
    pygame.draw.line(screen, colorL, p1, p2, 1)

    p1 = TR_View.getPointP2D((-temp_R + temp_Pos[0], temp_R + temp_Pos[1]))
    p2 = TR_View.getSizeP2D((temp_R * 2, -temp_R * 2))
    pygame.draw.arc(screen, colorL, p1 + p2, (90. - temp_Ang1) * math.pi / 180.,
                    ((90. - temp_Ang2 + 1.) * math.pi) / 180., 1)
