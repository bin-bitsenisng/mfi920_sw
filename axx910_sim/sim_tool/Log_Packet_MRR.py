import ctypes



class SpInfo_BitField(ctypes.LittleEndianStructure):
    _fields_ = [
        ("CurrentPRF", ctypes.c_uint32, 2),
        ("CycleTime", ctypes.c_uint32, 14),
        ("SMPLNum", ctypes.c_uint32, 16),

        ("PeakCnt", ctypes.c_uint32, 8),
        ("reserved0", ctypes.c_uint32, 24),

        ("VehicleSpeed", ctypes.c_uint32, 16),
        ("YawRate", ctypes.c_int32, 16),

        ("PathRadius", ctypes.c_int32, 16),
        ("reserved1", ctypes.c_int32, 16),

        ("ScanCount", ctypes.c_uint32, 32),
        ("reserved2", ctypes.c_uint32, 32),

        ("ChirpLength", ctypes.c_uint32, 32),
        ("ChirpCnt", ctypes.c_uint32, 32),

        ("reserved3", ctypes.c_uint32, 8),
        ("ChannelDtype", ctypes.c_uint32, 8),
        ("ChannelTxCnt", ctypes.c_uint32, 8),
        ("ChannelRxCnt", ctypes.c_uint32, 8),

    ]

class SpInfo_Packet(ctypes.Union):
    _fields_ = [("bits", SpInfo_BitField),
                ("dword", ctypes.c_uint64*4)]


class Object_BitField(ctypes.LittleEndianStructure):
    _fields_ = [
        ("RedundancyCheck", ctypes.c_uint32, 2),
        ("ModType", ctypes.c_uint32, 2),
        ("Range", ctypes.c_uint32, 14),
        ("Velocity", ctypes.c_int32, 14),

        ("AziAng", ctypes.c_int32, 14),
        ("EleAng", ctypes.c_int32, 10),
        ("Power", ctypes.c_uint32, 8),
    ]

class Object_Packet(ctypes.Union):
    _fields_ = [("bits", Object_BitField),
                ("dword", ctypes.c_uint64)]

class Track_BitField(ctypes.LittleEndianStructure):
    _fields_ = [
        ("RedundancyCheck", ctypes.c_uint32, 2),
        ("Status", ctypes.c_uint32, 2),
        ("UpdState", ctypes.c_uint32, 1),
        ("MoveStatus", ctypes.c_uint32, 2),
        ("PosX", ctypes.c_int32, 13),
        ("PosY", ctypes.c_int32, 12),

        ("VelX", ctypes.c_int32, 11),
        ("VelY", ctypes.c_int32, 10),
        ("Power", ctypes.c_uint32, 11),

        ("AccX", ctypes.c_int32, 9),
        ("AccY", ctypes.c_int32, 8),
        ("Width", ctypes.c_uint32, 6),
        ("Length", ctypes.c_uint32, 9),

        ("HeadingAngle", ctypes.c_int32, 9),
        ("AliveAge", ctypes.c_uint32, 8),
        ("reserved", ctypes.c_uint32, 15),
    ]

class Track_Packet(ctypes.Union):
    _fields_ = [("bits", Track_BitField),
                ("dword", ctypes.c_uint64*2)]


class MimoFFT_BitField(ctypes.LittleEndianStructure):
    _fields_ = [

        ("FFT_Tx1Ch0_real", ctypes.c_int32, 16),
        ("FFT_Tx1Ch0_imag", ctypes.c_int32, 16),

        ("FFT_Tx1Ch1_real", ctypes.c_int32, 16),
        ("FFT_Tx1Ch1_imag", ctypes.c_int32, 16),

        ("FFT_Tx1Ch2_real", ctypes.c_int32, 16),
        ("FFT_Tx1Ch2_imag", ctypes.c_int32, 16),

        ("FFT_Tx1Ch3_real", ctypes.c_int32, 16),
        ("FFT_Tx1Ch3_imag", ctypes.c_int32, 16),

        ("FFT_Tx2Ch0_real", ctypes.c_int32, 16),
        ("FFT_Tx2Ch0_imag", ctypes.c_int32, 16),

        ("FFT_Tx2Ch1_real", ctypes.c_int32, 16),
        ("FFT_Tx2Ch1_imag", ctypes.c_int32, 16),

        ("FFT_Tx2Ch2_real", ctypes.c_int32, 16),
        ("FFT_Tx2Ch2_imag", ctypes.c_int32, 16),

        ("FFT_Tx2Ch3_real", ctypes.c_int32, 16),
        ("FFT_Tx2Ch3_imag", ctypes.c_int32, 16),
    ]

class FFTData_Packet(ctypes.Union):
    _fields_ = [("bits", MimoFFT_BitField),
                ("dword", ctypes.c_uint64*4)]

class PeakIndex_BitField(ctypes.LittleEndianStructure):
    _fields_ = [
        ("FreqIndex_R", ctypes.c_int32, 16),
        ("FreqIndex_D", ctypes.c_int32, 16),
        ("EstFreqIdx_R", ctypes.c_int32, 16),
        ("EstFreqIdx_D", ctypes.c_int32, 16),
    ]

class PeakIndex_Packet(ctypes.Union):
    _fields_ = [("bits", PeakIndex_BitField),
                ("dword", ctypes.c_uint64)]

class FRW_BitField(ctypes.LittleEndianStructure):
    _fields_ = [

        ("FCWLvl", ctypes.c_uint32, 8),
        ("FVSA", ctypes.c_uint32, 8),
        ("CIPV", ctypes.c_uint32, 8),
        ("CIPS", ctypes.c_uint32, 8),

        ("FVSAIdx", ctypes.c_uint32, 8),
        ("PosX", ctypes.c_uint32, 11),
        ("TTC", ctypes.c_uint32, 6),
        ("reserved", ctypes.c_uint32, 7),
    ]

class FRW_Packet(ctypes.Union):
    _fields_ = [("bits", FRW_BitField),
                ("dword", ctypes.c_uint64)]

if __name__ == '__main__':

    SpInfo_Test = SpInfo_Packet()
    print(SpInfo_Packet.bits.size)
    print(SpInfo_Packet.dword.size)

    Object_Test = Object_Packet()
    print(Object_Packet.bits.size)
    print(Object_Packet.dword.size)

    Track_Test = Track_Packet()
    print(Track_Packet.bits.size)
    print(Track_Packet.dword.size)

