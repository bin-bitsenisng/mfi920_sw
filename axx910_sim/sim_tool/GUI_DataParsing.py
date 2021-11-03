def TrackDataParsing(TrkInfo):
    dic = dict()
    dic['Status'] = int(TrkInfo[0])
    dic['AliveAge'] = int(TrkInfo[1])
    dic['StatusAge'] = int(TrkInfo[2])
    dic['PosX'] = TrkInfo[3]
    dic['PosY'] = TrkInfo[4]
    dic['VelX'] = TrkInfo[5]
    dic['VelY'] = TrkInfo[6]
    dic['POW'] = TrkInfo[7]
    dic['HeadingAng'] = TrkInfo[8]
    dic['HeadingAngRate'] = TrkInfo[9]
    dic['Length'] = TrkInfo[10]
    dic['Width'] = TrkInfo[11]
    dic['RefPosX'] = TrkInfo[12]
    dic['RefPosY'] = TrkInfo[13]
    dic['AssoObjCnt'] = TrkInfo[14]
    dic['AssoTklCnt'] = TrkInfo[15]
    dic['MergFlag'] = TrkInfo[16]
    dic['MovStat'] = int(TrkInfo[17])
    dic['TrkIdx'] = TrkInfo[18]
    dic['AssoGateX'] = TrkInfo[19]
    dic['AssoGateY'] = TrkInfo[20]
    dic['VelX_Hist'] = TrkInfo[21]
    dic['VelY_Hist'] = TrkInfo[22]

    return dic


def TrackletDataParsing(TrkletInfo):
    dic = dict()
    dic['Status'] = int(TrkletInfo[0])
    dic['AliveAge'] = int(TrkletInfo[1])
    dic['StatusAge'] = int(TrkletInfo[2])
    dic['NewTrkScore'] = int(TrkletInfo[3])
    dic['PosX'] = TrkletInfo[4]
    dic['PosY'] = TrkletInfo[5]
    dic['VelX'] = TrkletInfo[6]
    dic['VelY'] = TrkletInfo[7]
    dic['AccX'] = TrkletInfo[8]
    dic['AccY'] = TrkletInfo[9]
    dic['AzRate'] = TrkletInfo[10]
    dic['MovStat'] = int(TrkletInfo[11])
    dic['MovStatCnt'] = int(TrkletInfo[12])
    dic['POW'] = TrkletInfo[13]
    dic['AssoObjIdx'] = int(TrkletInfo[14])
    dic['GroupTrkIdx'] = int(TrkletInfo[15])
    dic['GroupInConstCnt'] = int(TrkletInfo[16])
    dic['TrkletIdx'] = int(TrkletInfo[17])
    dic['VelMsmtX'] = int(TrkletInfo[18])
    dic['VelMsmtY'] = int(TrkletInfo[19])

    return dic


def ObjectDataParsing(ObjInfo):
    dic = dict()
    dic['R'] = ObjInfo[0]
    dic['V'] = ObjInfo[1]
    dic['AziAng'] = ObjInfo[2]
    dic['EleAng'] = ObjInfo[3]
    dic['Pow'] = ObjInfo[4]
    dic['RCS'] = ObjInfo[5]
    dic['Chirp'] = int(ObjInfo[6])
    dic['Beam'] = int(ObjInfo[7])
    dic['IdxR'] = int(ObjInfo[8])
    dic['IdxD'] = int(ObjInfo[9])
    dic['MergeIdx'] = int(ObjInfo[10])
    dic['NumTrk'] = int(ObjInfo[11])
    dic['GFStep'] = int(ObjInfo[12])
    dic['NoiseVar'] = ObjInfo[13]
    dic['TargetProb'] = ObjInfo[14]
    dic['HarmIdx'] = ObjInfo[15]
    dic['MeasIdx'] = int(ObjInfo[16])
    dic['TklIdx'] = int(ObjInfo[17])
    dic['TrkIdx'] = int(ObjInfo[18])

    dic['Pre_azi_angle'] = int(ObjInfo[19])
    dic['Pre_azi_power'] = int(ObjInfo[20])
    dic['SidelobePower'] = int(ObjInfo[21])

    return dic

def ObjectDataParsing_Log(ObjInfo):
    dic = dict()
    dic['R'] = ObjInfo[0]
    dic['AziAng'] = ObjInfo[1]
    dic['V'] = ObjInfo[2]

    return dic
    

def TrackDataParsing_Log(TrkInfo):
    dic = dict()
    dic['TrkIdx'] = TrkInfo[0]
    dic['Status'] = int(TrkInfo[1])
    dic['UpdStat'] = int(TrkInfo[2])
    dic['MovStat'] = int(TrkInfo[3])
    dic['AliveAge'] = int(TrkInfo[4])
    dic['PosX'] = TrkInfo[5]
    dic['PosY'] = TrkInfo[6]
    dic['RefPosX'] = TrkInfo[7]
    dic['RefPosY'] = TrkInfo[8]
    dic['VelX'] = TrkInfo[9]
    dic['VelY'] = TrkInfo[10]
    dic['HeadingAng'] = TrkInfo[11]
    dic['POW'] = TrkInfo[12]
    dic['Width'] = TrkInfo[13]
    dic['Length'] = TrkInfo[14]

    return dic