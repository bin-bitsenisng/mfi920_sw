import ctypes



class SpInfo_BitField(ctypes.LittleEndianStructure):
    _fields_ = [
        ("CurrentPRF", ctypes.c_uint32, 2),
        ("CycleTime", ctypes.c_uint32, 14),
        ("SMPLNum", ctypes.c_uint32, 16),

        ("PeakCnt_LR", ctypes.c_uint32, 8),
        ("PeakCnt_SR", ctypes.c_uint32, 8),
        ("reserved0", ctypes.c_uint32, 16),

        ("VehicleSpeed", ctypes.c_int32, 16),
        ("YawRate", ctypes.c_int32, 16),

        ("reserved1", ctypes.c_uint32, 32),
    ]

class SpInfo_Packet(ctypes.Union):
    _fields_ = [("bits", SpInfo_BitField),
                ("dword", ctypes.c_uint64*2)]


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
        ("Status", ctypes.c_uint32, 3),
        ("MoveStatus", ctypes.c_uint32, 2),
        ("PosX", ctypes.c_int32, 13),
        ("PosY", ctypes.c_int32, 12),

        ("VelX", ctypes.c_int32, 11),
        ("VelY", ctypes.c_int32, 10),
        ("TrackPower", ctypes.c_uint32, 11),

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

class SimoFFT_BitField(ctypes.LittleEndianStructure):
    _fields_ = [

        ("FFT_Ch0_real", ctypes.c_int32, 16),
        ("FFT_Ch0_imag", ctypes.c_int32, 16),

        ("FFT_Ch1_real", ctypes.c_int32, 16),
        ("FFT_Ch1_imag", ctypes.c_int32, 16),

        ("FFT_Ch2_real", ctypes.c_int32, 16),
        ("FFT_Ch2_imag", ctypes.c_int32, 16),

        ("FFT_Ch3_real", ctypes.c_int32, 16),
        ("FFT_Ch3_imag", ctypes.c_int32, 16),
    ]

class LR_FFTData_Packet(ctypes.Union):
    _fields_ = [("bits", MimoFFT_BitField),
                ("dword", ctypes.c_uint64*4)]

class SR_FFTData_Packet(ctypes.Union):
    _fields_ = [("bits", MimoFFT_BitField),
                ("dword", ctypes.c_uint64*2)]


class PeakIndex_BitField(ctypes.LittleEndianStructure):
    _fields_ = [
        ("FreqIndex_R", ctypes.c_int32, 16),
        ("FreqIndex_D", ctypes.c_int32, 16),
        ("EstFreqIdx_R", ctypes.c_int32, 16),
        ("EstFreqIdx_D", ctypes.c_int32, 16),
    ]

class LR_PeakIndex_Packet(ctypes.Union):
    _fields_ = [("bits", PeakIndex_BitField),
                ("dword", ctypes.c_uint64)]

class SR_PeakIndex_Packet(ctypes.Union):
    _fields_ = [("bits", PeakIndex_BitField),
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

