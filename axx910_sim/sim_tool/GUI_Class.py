# Coordinate Transformation
from TransRect import TransRect
from GUI_SubFunc import *
from GUI_KeyState import *
from GUI_BirdView import *
from GUI_DrawInfo import *
from GUI_DataParsing import *
import ColorTable as Color
import Qt_ObjInfo as QtObj
import io
import h5py
import numpy as np

pygame.font.init()
pygame.mixer.quit()
SH_Image = pygame.image.load('./Image/cam_BG.JPG')
TitleFont1 = pygame.font.Font('./font/Typo_SsangmunDongStencil.ttf', 20)
SubTitleFont1 = pygame.font.Font('./font/Typo_SsangmunDongStencil.ttf', 16)

ObjInfo_GUI = QtObj.ObjInfo_UI()

class RadarToolGUI:
    def __init__(self, Win_View_Size, Win_CAM_size, Screen_Size):

        self.WinViewSize = Win_View_Size
        self.WinCAMSize = Win_CAM_size
        self.WinMainSize = Win_View_Size[0]+Win_CAM_size[0], Win_View_Size[1]
        self.ScreenSize = Screen_Size
        self.WinTitle = []

        self.DisplaySurf = pygame.display.set_mode(self.WinMainSize, pygame.RESIZABLE)

        self.RadarTool_KeyState1 = RadarToolKeyState()
        self.RadarTool_KeyState2 = RadarToolKeyState()
        self.RadarTool_KeyState3 = RadarToolKeyState()

        self.Mode = 1
        self.Display = self.RadarTool_Display1
        self.KeyState = self.RadarTool_KeyState1
        self.FullScreen = False

        self.ViewPos = []
        self.ViewSize = []
        self.View_Surf = []
        self.TR_View = []
        self.SelectedData = [dict()] * 1

        for idx in range(len(self.SelectedData)):
            self.SelectedData[idx]['SimObj']        = []
            self.SelectedData[idx]['SimTrklet']     = []
            self.SelectedData[idx]['SimTrk']        = []
            self.SelectedData[idx]['SimRef']        = []
            self.SelectedData[idx]['RefObj']        = []
            self.SelectedData[idx]['RefTrklet']     = []
            self.SelectedData[idx]['RefTrk']        = []
            self.SelectedData[idx]['LogObj']        = []
            self.SelectedData[idx]['LogTrklet']     = []
            self.SelectedData[idx]['LogTrk']        = []

        self.CAM_Pos = []
        self.CAM_Surf = []

        self.Info_Pos = []
        self.Info_Surf = []

        self.LogInfo_Pos = []
        self.LogInfo_Surf = []

        self.WinTitle = 'Simulation'
        self.DisplayChange(self.DisplaySurf)



    def VideoResizeEvent(self, event, SimData, RefData, LogData, ScanIndex):
        if not self.FullScreen:
            self.DisplaySurf = pygame.display.set_mode(event.size, pygame.RESIZABLE)
        self.DisplayChange(self.DisplaySurf)
        self.Display(self.DisplaySurf, SimData, RefData, LogData, ScanIndex)


    def ModeChange(self, mode):
        if mode == 1:
            self.Mode = 1
            self.DisplayChange(self.DisplaySurf)
            self.Display = self.RadarTool_Display1
            self.KeyState = self.RadarTool_KeyState1
        elif mode == 2:
            self.Mode = 2
            self.DisplayChange(self.DisplaySurf)
            self.Display = self.RadarTool_Display2
            self.KeyState = self.RadarTool_KeyState2
        elif mode == 3:
            self.Mode = 3
            self.DisplayChange(self.DisplaySurf)
            self.Display = self.RadarTool_Display2
            self.KeyState = self.RadarTool_KeyState3
        elif mode == 12:
            if not self.FullScreen:
                self.DisplaySurf = pygame.display.set_mode(self.ScreenSize, pygame.FULLSCREEN)
                self.FullScreen = not self.FullScreen
            else:
                self.DisplaySurf = pygame.display.set_mode(self.WinMainSize, pygame.RESIZABLE)
                self.FullScreen = not self.FullScreen




    def DisplayChange(self, screen):

        temp_WinSize = screen.get_size()
        temp_LogInfoSize = int(temp_WinSize[0]-self.WinCAMSize[0]), 100
        temp_ViewSize = temp_LogInfoSize[0], (temp_WinSize[1] - temp_LogInfoSize[1])
        R = (1, 0, 0, -1)

        self.ViewPos = []
        self.ViewSize = []
        self.View_Surf = []
        self.TR_View = []
        self.CAM_Pos = []
        self.CAM_Surf = []
        self.Info_Pos = []
        self.Info_Surf = []
        self.LogInfo_Pos = []
        self.LogInfo_Surf = []
        temp_InfoSize = []


        if self.Mode == 1:
            PhysRect = GetTRInput((-50, 350), (60, 0))
            self.ViewSize.append((temp_ViewSize[0], temp_ViewSize[1]))
            self.ViewPos.append((0, 0))
            self.View_Surf.append(pygame.Surface(self.ViewSize[0]))
            self.TR_View.append(TransRect(PhysRect, (0, 0, self.ViewSize[0][0], self.ViewSize[0][1]), R))

            self.CAM_Pos.append((temp_ViewSize[0], 0))
            self.CAM_Surf.append(pygame.Surface(self.WinCAMSize))

            temp_InfoSize.append((self.WinCAMSize[0], int(temp_WinSize[1] - self.WinCAMSize[1])))
            self.Info_Pos.append((temp_ViewSize[0], self.WinCAMSize[1]))
            self.Info_Surf.append(pygame.Surface(temp_InfoSize[0]))

            self.LogInfo_Pos = (self.ViewPos[0][0], temp_ViewSize[1])
            self.LogInfo_Surf = pygame.Surface(temp_LogInfoSize)

        else:
            PhysRect = GetTRInput((-50, 400), (50, 0))
            self.ViewSize.append((int(temp_ViewSize[0] / 2), temp_ViewSize[1]))
            self.ViewSize.append((int(temp_ViewSize[0] / 2), temp_ViewSize[1]))

            self.ViewPos.append((self.ViewSize[0][0], 0))
            self.ViewPos.append((0, 0))

            for idx in range(len(self.ViewSize)):
                self.View_Surf.append(pygame.Surface(self.ViewSize[idx]))
                self.TR_View.append(TransRect(PhysRect, (0, 0, self.ViewSize[idx][0], self.ViewSize[idx][1]), R))

            self.CAM_Pos.append((temp_ViewSize[0], 0))
            self.CAM_Surf.append(pygame.Surface(self.WinCAMSize))

            temp_InfoSize.append((self.WinCAMSize[0], int(temp_WinSize[1] - self.WinCAMSize[1])))
            self.Info_Pos.append((temp_ViewSize[0], self.WinCAMSize[1]))
            self.Info_Surf.append(pygame.Surface(temp_InfoSize[0]))

            self.LogInfo_Pos = (self.ViewPos[0][1], temp_ViewSize[1])
            self.LogInfo_Surf = pygame.Surface(temp_LogInfoSize)


    def RadarTool_Display1(self, screen, SimData, RefData, LogData, ScanIndex):
        pygame.display.set_caption(self.WinTitle)
        # screen.fill(Color.white)

        RangeFoV = 0, 0, 300
        AngFoV = 0, 45

        View_Surf = self.View_Surf
        TR_View = self.TR_View


        View_Surf[0].fill(Color.black)

        # Mouse Action
        if self.KeyState.MouseDrag_on or self.KeyState.MouseLeftUp_on:
            TR_View = self.MouseDragEvent(View_Surf, TR_View)
            self.KeyState.MouseLeftUp_on = False

        if self.KeyState.MouseRightDown_on:
            self.KeyState.MouseRightDown_on = False
            rect = self.KeyState.MouseRightDown_pos + (0, 0)
            SelView, rect = GetMouseWinPos(rect, self.ViewPos, self.ViewSize)
            if SelView != -1:
                if not self.KeyState.Key_o:
                    self.SelectedData[0]['SimObj'], self.SelectedData[0]['SimTrklet'], self.SelectedData[0]['SimTrk'] = self.TargetSelectEvent(TR_View[0], rect, SimData[0], 0)
                if self.KeyState.Key_r:
                    self.SelectedData[0]['SimObj'], self.SelectedData[0]['SimTrklet'], self.SelectedData[0]['SimTrk'] = self.TargetSelectEvent(TR_View[0], rect, SimData[0], 1)

        # Draw Plane
        pygame.draw.rect(View_Surf[0], Color.white, View_Surf[0].get_rect(), 2)
        DrawGrid(View_Surf[0], TR_View[0], self.KeyState.Key_g)
        DrawFoVAng(View_Surf[0], TR_View[0], RangeFoV, AngFoV, color.yellow)

        # Text
        label = TitleFont1.render(self.WinTitle, 1, Color.white)
        View_Surf[0].blit(label, (40, 20))
        label = TitleFont1.render(('Scan: % d' % ScanIndex), 1, Color.aqua)
        View_Surf[0].blit(label, (40, 50))

        if not self.KeyState.Key_o:
            label_obj = SubTitleFont1.render('Obj On', 1, Color.tan)
        else:
            label_obj = SubTitleFont1.render('Obj Off', 1, Color.tan)
        View_Surf[0].blit(label_obj, (40, 80))

        if self.KeyState.Key_r:
            label_obj = SubTitleFont1.render('Ref Obj On', 1, Color.tan)
        else:
            label_obj = SubTitleFont1.render('Ref Obj Off', 1, Color.tan)
        View_Surf[0].blit(label_obj, (40, 120))

        if self.KeyState.Key_f:
            label_obj = SubTitleFont1.render('fil Obj On', 1, Color.tan)
        else:
            label_obj = SubTitleFont1.render('fil Obj Off', 1, Color.tan)
        View_Surf[0].blit(label_obj, (160, 120))

        if self.KeyState.Key_l:
            label_obj = SubTitleFont1.render('/Trklet On', 1, Color.tan)
        else:
            label_obj = SubTitleFont1.render('/Trklet Off', 1, Color.tan)
        View_Surf[0].blit(label_obj, (105, 80))

        if not self.KeyState.Key_t:
            label_obj = SubTitleFont1.render('/Trk On', 1, Color.tan)
        else:
            label_obj = SubTitleFont1.render('/Trk Off', 1, Color.tan)
        View_Surf[0].blit(label_obj, (200, 80))

        if self.KeyState.Key_n:
            label_obj = SubTitleFont1.render('/NewTrk On', 1, Color.tan)
        else:
            label_obj = SubTitleFont1.render('/NewTrk Off', 1, Color.tan)
        View_Surf[0].blit(label_obj, (270, 80))

        # Draw Simulation Data
        for idx in range(len(SimData)):
            if SimData[idx] is not None:
                DrawBirdView(View_Surf[0], TR_View[0], self.KeyState, SimData[idx], self.SelectedData[idx]['SimObj'], self.SelectedData[idx]['SimTrk'], idx)

        # BirdEye View Blit
        screen.blit(View_Surf[0], self.ViewPos[0])


        # Information Window
        for idx in range(len(self.Info_Surf)):
            pygame.draw.rect(self.Info_Surf[idx], Color.white, self.Info_Surf[idx].get_rect(), 2)
            if SimData[idx] is not None:
                DrawSelectedTargetInfo(self.Info_Surf[idx], SimData[idx], RefData[idx], self.SelectedData[idx])
            screen.blit(self.Info_Surf[idx], self.Info_Pos[idx])

        # LoggingData Information
        pygame.draw.rect(self.LogInfo_Surf, Color.white, self.LogInfo_Surf.get_rect(), 2)
        for idx in range(len(SimData)):
            if SimData[idx] is not None:
                DrawLogInfo(self.LogInfo_Surf, SimData[idx])
                break
        screen.blit(self.LogInfo_Surf, self.LogInfo_Pos)

        # CAM setting
        if (1):
            if 'image' in SimData[0]:
                imagebuffer = SimData[0]['image'].value
                #print(imagebuffer)
                fsub = io.BytesIO(imagebuffer)
                img = pygame.image.load(fsub, 'jpg')

            else:
                img = SH_Image
            pygame.draw.rect(self.CAM_Surf[0], Color.white, self.CAM_Surf[0].get_rect(), 2)
            self.CAM_Surf[0].blit(pygame.transform.scale(img, self.WinCAMSize), (0, 0))
            screen.blit(self.CAM_Surf[0], self.CAM_Pos[0])



    def RadarTool_Display2(self, screen, SimData, RefData, LogData, ScanIndex):
        pygame.display.set_caption(self.WinTitle)
        # screen.fill(Color.white)

        RangeFoV = 0, 0, 100
        AngFoV = 0, 20

        View_Surf = self.View_Surf
        TR_View = self.TR_View

        if self.Mode == 2:
            DispRefData = RefData
            DebugInfo_On = True
        else:
            DispRefData = LogData
            DebugInfo_On = False


        for idx in range(len(View_Surf)):
            View_Surf[idx].fill(Color.black)

        # Mouse Action
        if self.KeyState.MouseDrag_on or self.KeyState.MouseLeftUp_on:
            TR_View = self.MouseDragEvent(View_Surf, TR_View)
            self.KeyState.MouseLeftUp_on = False

        if self.KeyState.MouseRightDown_on:
            self.KeyState.MouseRightDown_on = False
            rect = self.KeyState.MouseRightDown_pos + (0, 0)
            SelView, rect = GetMouseWinPos(rect, self.ViewPos, self.ViewSize)
            if SelView != -1:
                if SelView == 0:
                    self.SelectedData[0]['SimObj'], self.SelectedData[0]['SimTrklet'], self.SelectedData[0]['SimTrk'] = self.TargetSelectEvent(TR_View[SelView], rect, SimData[0], 0)
                elif SelView == 1:
                    if self.Mode == 2: # Reference Mode
                        self.SelectedData[0]['RefObj'], self.SelectedData[0]['RefTrklet'], self.SelectedData[0]['RefTrk'] = self.TargetSelectEvent(TR_View[SelView], rect, DispRefData[0], 0)
                    else : # Logging Mode
                        self.SelectedData[0]['LogObj'], self.SelectedData[0]['LogTrklet'], self.SelectedData[0]['LogTrk'] = self.TargetSelectEvent(TR_View[SelView], rect, DispRefData[0], 0)

        # Draw Plane
        for idx in range(len(View_Surf)):
            pygame.draw.rect(View_Surf[idx], Color.white, View_Surf[idx].get_rect(), 2)
            DrawGrid(View_Surf[idx], TR_View[idx], self.KeyState.Key_g)
            DrawFoVAng(View_Surf[idx], TR_View[idx], RangeFoV, AngFoV)

        # Text
        label = TitleFont1.render('Simulation', 1, Color.white)
        View_Surf[0].blit(label, (40, 20))
        label = TitleFont1.render(('Scan: % d' % ScanIndex), 1, Color.aqua)
        View_Surf[0].blit(label, (40, 50))

        label = TitleFont1.render('Reference', 1, Color.white)
        View_Surf[1].blit(label, (40, 20))
        if self.Mode == 2:
            label = TitleFont1.render('Prev Simulation', 1, Color.aquamarine)
        else:
            label = TitleFont1.render('Logging', 1, Color.aquamarine)
        View_Surf[1].blit(label, (40, 50))


        # Draw Simulation Data
        for idx in range(len(SimData)):
            if SimData[idx] is not None:
                DrawBirdView(View_Surf[0], TR_View[0], self.KeyState, SimData[idx], self.SelectedData[idx]['SimObj'], self.SelectedData[idx]['SimTrk'], 0)
            if DispRefData[idx] is not None:
                if self.Mode == 2:
                    DrawBirdView(View_Surf[1], TR_View[1], self.KeyState, DispRefData[idx], self.SelectedData[idx]['RefObj'], self.SelectedData[idx]['RefTrk'], 0)
                else:
                    DrawBirdView_Log(View_Surf[1], TR_View[1], self.KeyState, DispRefData[idx], self.SelectedData[idx]['LogObj'], self.SelectedData[idx]['LogTrk'], 0)

        # BirdEye View Blit
        for idx in range(len(View_Surf)):
            screen.blit(View_Surf[idx], self.ViewPos[idx])


        # Information Window
        for idx in range(len(self.Info_Surf)):
            pygame.draw.rect(self.Info_Surf[idx], Color.white, self.Info_Surf[idx].get_rect(), 2)
            if SimData[idx] is not None:
                DrawSelectedTargetInfo(self.Info_Surf[idx], SimData[idx], DispRefData[idx], self.SelectedData[idx])
            screen.blit(self.Info_Surf[idx], self.Info_Pos[idx])

        # LoggingData Information
        pygame.draw.rect(self.LogInfo_Surf, Color.white, self.LogInfo_Surf.get_rect(), 2)
        for idx in range(len(SimData)):
            if SimData[idx] is not None:
                DrawLogInfo(self.LogInfo_Surf, SimData[idx])
                break
        screen.blit(self.LogInfo_Surf, self.LogInfo_Pos)

        # CAM setting

        if 'image' in SimData[0]:
            imagebuffer = SimData[0]['image'].value
            fsub = io.BytesIO(imagebuffer)
            img = pygame.image.load(fsub, 'jpg')

        else:
            img = SH_Image

        pygame.draw.rect(self.CAM_Surf[0], Color.white, self.CAM_Surf[0].get_rect(), 2)
        self.CAM_Surf[0].blit(pygame.transform.scale(img, self.WinCAMSize), (0, 0))
        screen.blit(self.CAM_Surf[0], self.CAM_Pos[0])


    def MouseDragEvent(self, View_Surf, TR_View):

        if (abs(self.KeyState.MouseDrag_size[0]) > 20) and (abs(self.KeyState.MouseDrag_size[1]) > 20):
            MouseDrag_rect = self.KeyState.MouseLeftDown_pos[0], self.KeyState.MouseLeftDown_pos[1],\
                             self.KeyState.MouseDrag_size[0], self.KeyState.MouseDrag_size[1]

            SelView, MouseDrag_rect = GetMouseWinPos(MouseDrag_rect, self.ViewPos, self.ViewSize)

            if self.KeyState.MouseDrag_on:
                colorL = (0xFF, 0xAA, 0xAA)
                # pygame.draw.rect(View_Surf[SelView], colorL, MouseDrag_rect, 1)
                for surf in View_Surf:
                    pygame.draw.rect(surf, colorL, MouseDrag_rect, 1)

            if self.KeyState.MouseLeftUp_on:
                if MouseDrag_rect[2] > 0 and MouseDrag_rect[3] > 0:  # (left upper) to (right lower)
                    p1 = TR_View[SelView].getPointD2P((MouseDrag_rect[0], MouseDrag_rect[1]))
                    p2 = TR_View[SelView].getSizeD2P((MouseDrag_rect[2], MouseDrag_rect[3]))
                    # print p1, p2
                    if (abs(p2[0]) > 0.3) and (abs(p2[1]) > 0.3):
                        #TR_View[SelView].UpdateScaleOffset(p1 + p2)
                        for tr_rect in TR_View:
                            tr_rect.UpdateScaleOffset(p1 + p2)
                else:
                    #TR_View[SelView].UpdateScaleOffsetOriginal()
                    for tr_rect in TR_View:
                        tr_rect.UpdateScaleOffsetOriginal()

        return TR_View


    def TargetSelectEvent(self, TR, rect, DataSet, obj_mode, DebugInfo_On = True):

        if DataSet is not None:
            if obj_mode == 0:
                Obj_Info = DataSet['Sim_ObjInfo'].value
                ObjInfo = Obj_Info
            elif obj_mode == 1:
                ObjRefInfo = DataSet['Sim_REF_ObjInfo'].value
                ObjInfo = ObjRefInfo
            elif obj_mode == 2:
                ObjfilInfo = DataSet['Sim_FilObjInfo'].value
                ObjInfo = ObjfilInfo
            else:
                pass

            TrkInfo = DataSet['Sim_TrkInfo'].value
            if DataSet['Sim_TrkletInfo'].value is not None:
                TrkletInfo = DataSet['Sim_TrkletInfo'].value
            else:
                TrkletInfo = None
        else:
            ObjInfo = None
            ObjRefInfo = None
            ObjfilInfo = None
            TrkInfo = None
            TrkletInfo = None

        SelectedObj = []
        SelectedRefObj = []
        SelectedTrklet = []
        SelectedTrk = []
        NewTrackEnable = self.KeyState.Key_n
        p1 = TR.getPointD2P((rect[0], rect[1]))     # mouse position
        g1 = TR.getSizeD2P((40, 40))
        g2 = TR.getSizeD2P((60, 60))
        g3 = TR.getSizeD2P((30, 30))

        Temp_ObjMin = math.sqrt((g3[0] ** 2) + (g3[1] ** 2))
        Temp_TrkletMin = math.sqrt((g3[0] ** 2) + (g3[1] ** 2))
        Temp_TrkMin = math.sqrt((g3[0] ** 2) + (g3[1] ** 2))
        NearestObj = None
        NearestRefObj = None
        NearestTrklet = None
        NearestTrk = None

        if ObjInfo is not None:
            for idx in range(len(ObjInfo)):
                if ObjInfo[idx][0] != 0:
                    if (self.Mode == 3) :
                        ObjDict = ObjectDataParsing_Log(ObjInfo[idx])
                    else:
                        ObjDict = ObjectDataParsing(ObjInfo[idx])

                    R = ObjDict['R']
                    AziAng = ObjDict['AziAng']
                    PosX = R * math.cos(AziAng / 180 * math.pi)
                    PosY = - R * math.sin(AziAng / 180 * math.pi)
                    phys_pos = PosY, PosX

                    if (abs(phys_pos[0] - p1[0]) < abs(g1[0])) and (abs(phys_pos[1] - p1[1]) < abs(g1[1])):
                        SelectedObj.append(idx)
                        temp_Dist = math.sqrt((phys_pos[0] - p1[0])**2 + (phys_pos[1] - p1[1])**2)
                        if temp_Dist < Temp_ObjMin:
                            Temp_ObjMin = temp_Dist
                            NearestObj = idx

        '''
        if ObjRefInfo is not None:
            for idx in range(len(ObjRefInfo)):
                if ObjRefInfo[idx][0] != 0:
                    if (self.Mode == 3) :
                        ObjDict = ObjectDataParsing_Log(ObjRefInfo[idx])
                    else:
                        ObjDict = ObjectDataParsing(ObjRefInfo[idx])

                    R = ObjDict['R']
                    AziAng = ObjDict['AziAng']
                    PosX = R * math.cos(AziAng / 180 * math.pi)
                    PosY = - R * math.sin(AziAng / 180 * math.pi)
                    phys_pos = PosY, PosX

                    if (abs(phys_pos[0] - p1[0]) < abs(g1[0])) and (abs(phys_pos[1] - p1[1]) < abs(g1[1])):
                        SelectedRefObj.append(idx)
                        temp_Dist = math.sqrt((phys_pos[0] - p1[0])**2 + (phys_pos[1] - p1[1])**2)
                        if temp_Dist < Temp_ObjMin:
                            Temp_ObjMin = temp_Dist
                            NearestRefObj = idx
        '''

        if TrkletInfo is not None:
            for idx in range(len(TrkletInfo)):
                if TrkletInfo[idx][0] != 0:
                    if TrkletInfo[idx] is not None:
                        TrkletDict = TrackletDataParsing(TrkletInfo[idx])
                        Tkl_Status = TrkletDict['Status']
                        Tkl_PosX = TrkletDict['PosX']
                        Tkl_PosY = TrkletDict['PosY']
                        phys_pos = Tkl_PosY, Tkl_PosX

                        if (Tkl_Status == 1 and NewTrackEnable) or (Tkl_Status > 1):
                            if (abs(phys_pos[0] - p1[0]) < abs(g2[0])) and (abs(phys_pos[1] - p1[1]) < abs(g2[1])):
                                SelectedTrklet.append(idx)
                                #print('SelectEvent Trklet idx : %d', (idx))
                                temp_Dist = math.sqrt((phys_pos[0] - p1[0])**2 + (phys_pos[1] - p1[1]) ** 2)
                                if temp_Dist < Temp_TrkletMin:
                                    Temp_TrkletMin = temp_Dist
                                    NearestTrklet = idx

        if TrkInfo is not None:
            for idx in range(len(TrkInfo)):
                if (self.Mode == 3):
                    TrkDict = TrackDataParsing_Log(TrkInfo[idx])
                else:
                    TrkDict = TrackDataParsing(TrkInfo[idx])

                Status = TrkDict['Status']
                PosX = TrkDict['PosX']
                PosY = TrkDict['PosY']
                phys_pos = PosY, PosX

                if (Status == 1 and NewTrackEnable) or (Status == 2):
                    if (abs(phys_pos[0] - p1[0]) < abs(g2[0])) and (abs(phys_pos[1] - p1[1]) < abs(g2[1])):
                        SelectedTrk.append(idx)
                        temp_Dist = math.sqrt((phys_pos[0] - p1[0])**2 + (phys_pos[1] - p1[1])**2)
                        if temp_Dist < Temp_TrkMin:
                            Temp_TrkMin = temp_Dist
                            NearestTrk = idx


        if DebugInfo_On is True:
            if NearestObj is not None:
                ObjInfo_GUI.SetObjInfo(ObjInfo[NearestObj], DataSet)
            elif NearestRefObj is not None:
                ObjInfo_GUI.SetObjInfo(ObjRefInfo[NearestRefObj], DataSet)

            # if NearestTrk is not None:
                # QtTrk.SetTrkInfo(TrkInfo[NearestTrk], DataSet)

        # h5 저장
        if NearestObj is not None:
            h5file = h5py.File('Cur_objinfo' + '.h5', "w")
            Peak_num = ObjInfo[NearestObj][10]
            Scan_idx = DataSet.name
            R_idx = ObjInfo[NearestObj][8]
            D_idx = ObjInfo[NearestObj][9]
            mode = ObjInfo[NearestObj][6]
            vel = ObjInfo[NearestObj][1]


            group_name = 'data'
            h5grp = h5file.create_group(group_name)
            h5grp.create_dataset("Peak", data=Peak_num, dtype='int16')
            h5grp.create_dataset("Scan_idx", data=Scan_idx)
            h5grp.create_dataset("R_idx", data=R_idx, dtype='int16')
            h5grp.create_dataset("D_idx", data=D_idx, dtype='int16')
            h5grp.create_dataset("mode", data=mode, dtype='int16')
            h5grp.create_dataset("vel", data=vel, dtype='float32')

            print('ObjInfo[NearestObj]', ObjInfo[NearestObj][10])
            print('Scan_idx', DataSet.name)


        return SelectedObj, SelectedTrklet, SelectedTrk