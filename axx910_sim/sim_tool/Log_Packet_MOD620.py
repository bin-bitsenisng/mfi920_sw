import ctypes



class SpInfo_BitField(ctypes.LittleEndianStructure):
    _fields_ = [
        ("SMPLNum", ctypes.c_uint32, 16),
        ("CycleTime", ctypes.c_uint32, 16),

        ("reserved0", ctypes.c_uint32, 16),
        ("reserved1", ctypes.c_uint32, 16),
    ]

class SpInfo_Packet(ctypes.Union):
    _fields_ = [("bits", SpInfo_BitField),
                ("dword", ctypes.c_uint64)]


class FFTData_BitField(ctypes.LittleEndianStructure):
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

class FFTData_Packet(ctypes.Union):
    _fields_ = [("bits", FFTData_BitField),
                ("dword", ctypes.c_uint64*2)]


class ROA_BitField(ctypes.LittleEndianStructure):
    _fields_ = [

        ("presence", ctypes.c_uint32, 1),
        ("type", ctypes.c_uint32, 3),
        ("apnea_flag", ctypes.c_uint32, 1),
        ("power", ctypes.c_uint32, 8),
        ("reserved0", ctypes.c_uint32, 19),

        ("breath_rate", ctypes.c_uint32, 8),
        ("heart_rate", ctypes.c_uint32, 8),
        ("reserved1", ctypes.c_uint32, 16),
    ]

class ROA_Packet(ctypes.Union):
    _fields_ = [("bits", ROA_BitField),
                ("dword", ctypes.c_uint64)]


# Chssis CAN DB
class WHL_SPD_BitField(ctypes.LittleEndianStructure):
    _fields_ = [

        ("WHL_SPD_FL", ctypes.c_uint32, 16),
        ("WHL_SPD_FR", ctypes.c_uint32, 16),
        ("WHL_SPD_RL", ctypes.c_uint32, 16),
        ("WHL_SPD_RR", ctypes.c_uint32, 16),
    ]

class WHL_SPD_Packet(ctypes.Union):
    _fields_ = [("bits", WHL_SPD_BitField),
                ("dword", ctypes.c_uint64)]


class Gear_BitField(ctypes.LittleEndianStructure):
    _fields_ = [

        ("reserved0", ctypes.c_uint32, 32),
        ("G_SEL_DISP", ctypes.c_uint32, 4),
        ("GEAR_TYPE", ctypes.c_uint32, 4),
        ("reserved1", ctypes.c_uint32, 24),
    ]

class Gear_Packet(ctypes.Union):
    _fields_ = [("bits", Gear_BitField),
                ("dword", ctypes.c_uint64)]


if __name__ == '__main__':

    SpInfo_Test = SpInfo_Packet()
    print(SpInfo_Packet.bits.size)
    print(SpInfo_Packet.dword.size)

