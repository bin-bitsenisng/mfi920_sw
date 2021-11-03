#include <linux/spi/spidev.h>


__uint64_t miso_7[7] = {0};
__uint64_t miso_10[10] = {0};
__uint64_t miso_22[22] = {0};


/*
next_bp_idx : 0(R mode)
[Select : 2, 6개]
1)[7]MOSI : 0x00, 0x09, 0x00, 0x00, 0x80, 0x0C, 0x02
2)[7]MOSI : 0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43
3)[10]MOSI : 0x00, 0x10, 0x60, 0x03, 0x00, 0x00, 0xC8, 0x42, 0xB9, 0x75
4)[10]MOSI : 0x00, 0x08, 0x60, 0x03, 0x00, 0x56, 0xC4, 0x64, 0x97, 0x7B
5)[10]MOSI : 0x00, 0x0C, 0x60, 0x03, 0x12, 0x00, 0x00, 0x00, 0x69, 0x8D
6)[10]MOSI : 0x00, 0x00, 0x08, 0x03, 0x0C, 0x03, 0x00, 0x00, 0x29, 0xA5
[Select : 7, 14개]
1)[7]MOSI : 0x00, 0x09, 0x00, 0x00, 0xF0, 0x21, 0xC3
2)[7]MOSI : 0x00, 0x08, 0x00, 0x00, 0x02, 0x8E, 0x28
3)[10]MOSI : 0x00, 0x60, 0x00, 0x03, 0x00, 0x02, 0x00, 0x00, 0x3A, 0x8C
4)[7]MOSI : 0x00, 0x09, 0x00, 0x00, 0x80, 0x0C, 0x02
5)[7]MOSI : 0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43
6)[22]MOSI : 0x00, 0x00, 0x84, 0x0F, 0x00, 0x87, 0x00, 0x80, 0x0C, 0x85, 0x00, 0x80, 0xB4, 0x80, 0x00, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x30, 0xE3
7)[7]MOSI : 0x00, 0x09, 0x00, 0x00, 0xF0, 0x21, 0xC3
8)[7]MOSI : 0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43
9)[10]MOSI : 0x00, 0x14, 0x10, 0x03, 0x03, 0x00, 0x00, 0x00, 0xB1, 0x9E
10)[10]MOSI : 0x00, 0x00, 0x40, 0x03, 0x00, 0x01, 0x00, 0x00, 0x2C, 0x70
11)[10]MOSI : 0x00, 0x04, 0x40, 0x03, 0x2C, 0x00, 0x00, 0x00, 0xCD, 0x9F
12)[10]MOSI : 0x00, 0x08, 0x40, 0x03, 0x01, 0x01, 0x00, 0x00, 0x9D, 0x75
13)[10]MOSI : 0x00, 0x0C, 0x40, 0x03, 0x02, 0x01, 0x00, 0x00, 0x3E, 0x90
14)[10]MOSI : 0x00, 0x10, 0x40, 0x03, 0x03, 0x01, 0x00, 0x00, 0x72, 0x2F
===============================================================================
*/
__uint64_t R_2_1[7] = {0x00, 0x09, 0x00, 0x00, 0x80, 0x0C, 0x02};
__uint64_t R_2_2[7] = {0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43};
__uint64_t R_2_3[10] = {0x00, 0x10, 0x60, 0x03, 0x00, 0x00, 0xC8, 0x42, 0xB9, 0x75};
__uint64_t R_2_4[10] = {0x00, 0x08, 0x60, 0x03, 0x00, 0x56, 0xC4, 0x64, 0x97, 0x7B};
__uint64_t R_2_5[10] = {0x00, 0x0C, 0x60, 0x03, 0x12, 0x00, 0x00, 0x00, 0x69, 0x8D};
__uint64_t R_2_6[10] = {0x00, 0x00, 0x08, 0x03, 0x0C, 0x03, 0x00, 0x00, 0x29, 0xA5};

__uint64_t R_7_1[7] = {0x00, 0x09, 0x00, 0x00, 0xF0, 0x21, 0xC3};
__uint64_t R_7_2[7] = {0x00, 0x08, 0x00, 0x00, 0x02, 0x8E, 0x28};
__uint64_t R_7_3[10] = {0x00, 0x60, 0x00, 0x03, 0x00, 0x02, 0x00, 0x00, 0x3A, 0x8C};
__uint64_t R_7_4[7] = {0x00, 0x09, 0x00, 0x00, 0x80, 0x0C, 0x02};
__uint64_t R_7_5[7] = {0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43};
__uint64_t R_7_6[22] = {0x00, 0x00, 0x84, 0x0F, 0x00, 0x87, 0x00, 0x80, 0x0C, 0x85, 0x00, 0x80, 0xB4, 0x80, 0x00, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x30, 0xE3};
__uint64_t R_7_7[7] = {0x00, 0x09, 0x00, 0x00, 0xF0, 0x21, 0xC3};
__uint64_t R_7_8[7] = {0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43};
__uint64_t R_7_9[10] = {0x00, 0x14, 0x10, 0x03, 0x03, 0x00, 0x00, 0x00, 0xB1, 0x9E};
__uint64_t R_7_10[10] = {0x00, 0x00, 0x40, 0x03, 0x00, 0x01, 0x00, 0x00, 0x2C, 0x70};
__uint64_t R_7_11[10] = {0x00, 0x04, 0x40, 0x03, 0x2C, 0x00, 0x00, 0x00, 0xCD, 0x9F};
__uint64_t R_7_12[10] = {0x00, 0x08, 0x40, 0x03, 0x01, 0x01, 0x00, 0x00, 0x9D, 0x75};
__uint64_t R_7_13[10] = {0x00, 0x0C, 0x40, 0x03, 0x02, 0x01, 0x00, 0x00, 0x3E, 0x90};
__uint64_t R_7_14[10] = {0x00, 0x10, 0x40, 0x03, 0x03, 0x01, 0x00, 0x00, 0x72, 0x2F};


/*****************************************************************************************************************************************/
/*
next_bp_idx : 1(L mode)
[Select : 2, 6개]
1)[7]MOSI : 0x00, 0x09, 0x00, 0x00, 0x80, 0x0C, 0x02
2)[7]MOSI : 0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43
3)[10]MOSI : 0x00, 0x10, 0x60, 0x03, 0x00, 0x00, 0x48, 0x43, 0x35, 0x95
4)[10]MOSI : 0x00, 0x08, 0x60, 0x03, 0x00, 0x56, 0xC4, 0x64, 0x97, 0x7B
5)[10]MOSI : 0x00, 0x0C, 0x60, 0x03, 0x12, 0x00, 0x00, 0x00, 0x69, 0x8D
6)[10]MOSI : 0x00, 0x00, 0x08, 0x03, 0x0C, 0x03, 0x00, 0x00, 0x29, 0xA5
[Select : 7, 14개]
1)[7]MOSI : 0x00, 0x09, 0x00, 0x00, 0xF0, 0x21, 0xC3
2)[7]MOSI : 0x00, 0x08, 0x00, 0x00, 0x02, 0x8E, 0x28
3)[10]MOSI : 0x00, 0x60, 0x00, 0x03, 0x80, 0x01, 0x00, 0x00, 0x19, 0x7A
4)[7]MOSI : 0x00, 0x09, 0x00, 0x00, 0x80, 0x0C, 0x02
5)[7]MOSI : 0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43
6)[22]MOSI : 0x00, 0x00, 0x84, 0x0F, 0x98, 0x87, 0x00, 0x80, 0x0C, 0x85, 0x00, 0x80, 0xB4, 0x80, 0x00, 0x8A, 0x00, 0x00, 0x00, 0x00, 0xE3, 0xD0
7)[7]MOSI : 0x00, 0x09, 0x00, 0x00, 0xF0, 0x21, 0xC3
8)[7]MOSI : 0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43
9)[10]MOSI : 0x00, 0x14, 0x10, 0x03, 0x03, 0x00, 0x00, 0x00, 0xB1, 0x9E
10)[10]MOSI : 0x00, 0x00, 0x40, 0x03, 0x40, 0x01, 0x00, 0x00, 0x19, 0xC0
11)[10]MOSI : 0x00, 0x04, 0x40, 0x03, 0x6C, 0x00, 0x00, 0x00, 0xF8, 0x2F
12)[10]MOSI : 0x00, 0x08, 0x40, 0x03, 0x41, 0x01, 0x00, 0x00, 0xA8, 0xC5
13)[10]MOSI : 0x00, 0x0C, 0x40, 0x03, 0x42, 0x01, 0x00, 0x00, 0x0B, 0x20
14)[10]MOSI : 0x00, 0x10, 0x40, 0x03, 0x43, 0x01, 0x00, 0x00, 0x47, 0x9F

Add
Select : 7,
MOSI : 00 00 40 03 40 01 00 00 19 C0 
MISO : 00 00 00 00 00 00 00 00 00 00 
Select : 7,
MOSI : 00 04 40 03 6C 00 00 00 F8 2F 
MISO : 00 00 00 00 00 00 00 00 00 00 
Select : 7,
MOSI : 00 08 40 03 41 01 00 00 A8 C5 
MISO : 00 00 00 00 00 00 00 00 00 00 
Select : 7,
MOSI : 00 0C 40 03 42 01 00 00 0B 20 
MISO : 00 00 00 00 00 00 00 00 00 00 
Select : 7,
MOSI : 00 10 40 03 43 01 00 00 47 9F 
MISO : 00 00 00 00 00 00 00 00 00 00 
Select : 7,
MOSI : 00 00 40 03 40 01 00 00 19 C0 
MISO : 00 00 00 00 00 00 00 00 00 00 
Select : 7,
MOSI : 00 04 40 03 6C 00 00 00 F8 2F 
MISO : 00 00 00 00 00 00 00 00 00 00 
Select : 7,
MOSI : 00 08 40 03 41 01 00 00 A8 C5 
MISO : 00 00 00 00 00 00 00 00 00 00 
Select : 7,
MOSI : 00 0C 40 03 42 01 00 00 0B 20 
MISO : 00 00 00 00 00 00 00 00 00 00 
Select : 7,
MOSI : 00 10 40 03 43 01 00 00 47 9F 
MISO : 00 00 00 00 00 00 00 00 00 00 
===============================================================================
*/
__uint64_t L_2_1[7] = {0x00, 0x09, 0x00, 0x00, 0x80, 0x0C, 0x02};
__uint64_t L_2_2[7] = {0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43};
__uint64_t L_2_3[10] = {0x00, 0x10, 0x60, 0x03, 0x00, 0x00, 0x48, 0x43, 0x35, 0x95};
__uint64_t L_2_4[10] = {0x00, 0x08, 0x60, 0x03, 0x00, 0x56, 0xC4, 0x64, 0x97, 0x7B};
__uint64_t L_2_5[10] = {0x00, 0x0C, 0x60, 0x03, 0x12, 0x00, 0x00, 0x00, 0x69, 0x8D};
__uint64_t L_2_6[10] = {0x00, 0x00, 0x08, 0x03, 0x0C, 0x03, 0x00, 0x00, 0x29, 0xA5};

__uint64_t L_7_1[7] = {0x00, 0x09, 0x00, 0x00, 0xF0, 0x21, 0xC3};
__uint64_t L_7_2[7] = {0x00, 0x08, 0x00, 0x00, 0x02, 0x8E, 0x28};
__uint64_t L_7_3[10] = {0x00, 0x60, 0x00, 0x03, 0x80, 0x01, 0x00, 0x00, 0x19, 0x7A};
__uint64_t L_7_4[7] = {0x00, 0x09, 0x00, 0x00, 0x80, 0x0C, 0x02};
__uint64_t L_7_5[7] = {0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43};
__uint64_t L_7_6[22] = {0x00, 0x00, 0x84, 0x0F, 0x98, 0x87, 0x00, 0x80, 0x0C, 0x85, 0x00, 0x80, 0xB4, 0x80, 0x00, 0x8A, 0x00, 0x00, 0x00, 0x00, 0xE3, 0xD0};
__uint64_t L_7_7[7] = {0x00, 0x09, 0x00, 0x00, 0xF0, 0x21, 0xC3};
__uint64_t L_7_8[7] = {0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43};
__uint64_t L_7_9[10] = {0x00, 0x14, 0x10, 0x03, 0x03, 0x00, 0x00, 0x00, 0xB1, 0x9E};
__uint64_t L_7_10[10] = {0x00, 0x00, 0x40, 0x03, 0x40, 0x01, 0x00, 0x00, 0x19, 0xC0};
__uint64_t L_7_11[10] = {0x00, 0x04, 0x40, 0x03, 0x6C, 0x00, 0x00, 0x00, 0xF8, 0x2F};
__uint64_t L_7_12[10] = {0x00, 0x08, 0x40, 0x03, 0x41, 0x01, 0x00, 0x00, 0xA8, 0xC5};
__uint64_t L_7_13[10] = {0x00, 0x0C, 0x40, 0x03, 0x42, 0x01, 0x00, 0x00, 0x0B, 0x20};
__uint64_t L_7_14[10] = {0x00, 0x10, 0x40, 0x03, 0x43, 0x01, 0x00, 0x00, 0x47, 0x9F};
// __uint64_t L_7_15[10] = {0x00, 0x00, 0x40, 0x03, 0x40, 0x01, 0x00, 0x00, 0x19, 0xC0};
// __uint64_t L_7_16[10] = {0x00, 0x04, 0x40, 0x03, 0x6C, 0x00, 0x00, 0x00, 0xF8, 0x2F};
// __uint64_t L_7_17[10] = {0x00, 0x08, 0x40, 0x03, 0x41, 0x01, 0x00, 0x00, 0xA8, 0xC5};
// __uint64_t L_7_18[10] = {0x00, 0x0C, 0x40, 0x03, 0x42, 0x01, 0x00, 0x00, 0x0B, 0x20};
// __uint64_t L_7_19[10] = {0x00, 0x10, 0x40, 0x03, 0x43, 0x01, 0x00, 0x00, 0x47, 0x9F};
// __uint64_t L_7_20[10] = {0x00, 0x00, 0x40, 0x03, 0x40, 0x01, 0x00, 0x00, 0x19, 0xC0};
// __uint64_t L_7_21[10] = {0x00, 0x04, 0x40, 0x03, 0x6C, 0x00, 0x00, 0x00, 0xF8, 0x2F};
// __uint64_t L_7_22[10] = {0x00, 0x08, 0x40, 0x03, 0x41, 0x01, 0x00, 0x00, 0xA8, 0xC5};
// __uint64_t L_7_23[10] = {0x00, 0x0C, 0x40, 0x03, 0x42, 0x01, 0x00, 0x00, 0x0B, 0x20};
// __uint64_t L_7_24[10] = {0x00, 0x10, 0x40, 0x03, 0x43, 0x01, 0x00, 0x00, 0x47, 0x9F};


/*
next_bp_idx : 2(M mode)
[Select : 2, 6개]
1)[7]MOSI : 0x00, 0x09, 0x00, 0x00, 0x80, 0x0C, 0x02
2)[7]MOSI : 0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43
3)[10]MOSI : 0x00, 0x10, 0x60, 0x03, 0x00, 0x00, 0xFA, 0x43, 0xB5, 0x57
4)[10]MOSI : 0x00, 0x08, 0x60, 0x03, 0x00, 0x56, 0xC4, 0x64, 0x97, 0x7B
5)[10]MOSI : 0x00, 0x0C, 0x60, 0x03, 0x12, 0x00, 0x00, 0x00, 0x69, 0x8D
6)[10]MOSI : 0x00, 0x00, 0x08, 0x03, 0x0C, 0x03, 0x00, 0x00, 0x29, 0xA5
[Select : 7, 11개]
1)[7]MOSI : 0x00, 0x09, 0x00, 0x00, 0x80, 0x0C, 0x02
2)[7]MOSI : 0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43
3)[10]MOSI : 0x00, 0x00, 0x84, 0x03, 0xB0, 0x88, 0x00, 0x80, 0x74, 0xAA
4)[7]MOSI : 0x00, 0x09, 0x00, 0x00, 0xF0, 0x21, 0xC3
5)[7]MOSI : 0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43
6)[10]MOSI : 0x00, 0x14, 0x10, 0x03, 0x03, 0x00, 0x00, 0x00, 0xB1, 0x9E
7)[10]MOSI : 0x00, 0x00, 0x40, 0x03, 0x40, 0x01, 0x00, 0x00, 0x19, 0xC0
8)[10]MOSI : 0x00, 0x04, 0x40, 0x03, 0x6C, 0x00, 0x00, 0x00, 0xF8, 0x2F
9)[10]MOSI : 0x00, 0x08, 0x40, 0x03, 0x41, 0x01, 0x00, 0x00, 0xA8, 0xC5
10)[10]MOSI : 0x00, 0x0C, 0x40, 0x03, 0x42, 0x01, 0x00, 0x00, 0x0B, 0x20
11)[10]MOSI : 0x00, 0x10, 0x40, 0x03, 0x43, 0x01, 0x00, 0x00, 0x47, 0x9F
===============================================================================
*/
__uint64_t M_2_1[7] = {0x00, 0x09, 0x00, 0x00, 0x80, 0x0C, 0x02};
__uint64_t M_2_2[7] = {0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43};
__uint64_t M_2_3[10] = {0x00, 0x10, 0x60, 0x03, 0x00, 0x00, 0xFA, 0x43, 0xB5, 0x57};
__uint64_t M_2_4[10] = {0x00, 0x08, 0x60, 0x03, 0x00, 0x56, 0xC4, 0x64, 0x97, 0x7B};
__uint64_t M_2_5[10] = {0x00, 0x0C, 0x60, 0x03, 0x12, 0x00, 0x00, 0x00, 0x69, 0x8D};
__uint64_t M_2_6[10] = {0x00, 0x00, 0x08, 0x03, 0x0C, 0x03, 0x00, 0x00, 0x29, 0xA5};

__uint64_t M_7_1[7] = {0x00, 0x09, 0x00, 0x00, 0x80, 0x0C, 0x02};
__uint64_t M_7_2[7] = {0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43};
__uint64_t M_7_3[10] = {0x00, 0x00, 0x84, 0x03, 0xB0, 0x88, 0x00, 0x80, 0x74, 0xAA};
__uint64_t M_7_4[7] = {0x00, 0x09, 0x00, 0x00, 0xF0, 0x21, 0xC3};
__uint64_t M_7_5[7] = {0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43};
__uint64_t M_7_6[10] = {0x00, 0x14, 0x10, 0x03, 0x03, 0x00, 0x00, 0x00, 0xB1, 0x9E};
__uint64_t M_7_7[10] = {0x00, 0x00, 0x40, 0x03, 0x40, 0x01, 0x00, 0x00, 0x19, 0xC0};
__uint64_t M_7_8[10] = {0x00, 0x04, 0x40, 0x03, 0x6C, 0x00, 0x00, 0x00, 0xF8, 0x2F};
__uint64_t M_7_9[10] = {0x00, 0x08, 0x40, 0x03, 0x41, 0x01, 0x00, 0x00, 0xA8, 0xC5};
__uint64_t M_7_10[10] = {0x00, 0x0C, 0x40, 0x03, 0x42, 0x01, 0x00, 0x00, 0x0B, 0x20};
__uint64_t M_7_11[10] = {0x00, 0x10, 0x40, 0x03, 0x43, 0x01, 0x00, 0x00, 0x47, 0x9F};



/*
next_bp_idx : 3(S mode)
[Select : 2 6개]
1)[7]MOSI : 0x00, 0x09, 0x00, 0x00, 0x80, 0x0C, 0x02
2)[7]MOSI : 0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43
3)[10]MOSI : 0x00, 0x10, 0x60, 0x03, 0x00, 0x80, 0xBB, 0x44, 0x59, 0x9F
4)[10]MOSI : 0x00, 0x08, 0x60, 0x03, 0x00, 0x56, 0xC4, 0x64, 0x97, 0x7B
5)[10]MOSI : 0x00, 0x0C, 0x60, 0x03, 0x12, 0x00, 0x00, 0x00, 0x69, 0x8D
6)[10]MOSI : 0x00, 0x00, 0x08, 0x03, 0x0C, 0x03, 0x00, 0x00, 0x29, 0xA5
[Select : 7, 11개]
1)[7]MOSI : 0x00, 0x09, 0x00, 0x00, 0x80, 0x0C, 0x02
2)[7]MOSI : 0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43
3)[10]MOSI : 0x00, 0x00, 0x84, 0x03, 0xC8, 0x89, 0x00, 0x80, 0x68, 0x6A
4)[7]MOSI : 0x00, 0x09, 0x00, 0x00, 0xF0, 0x21, 0xC3
5)[7]MOSI : 0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43
6)[10]MOSI : 0x00, 0x14, 0x10, 0x03, 0x03, 0x00, 0x00, 0x00, 0xB1, 0x9E
7)[10]MOSI : 0x00, 0x00, 0x40, 0x03, 0x40, 0x01, 0x00, 0x00, 0x19, 0xC0
8)[10]MOSI : 0x00, 0x04, 0x40, 0x03, 0x6C, 0x00, 0x00, 0x00, 0xF8, 0x2F
9)[10]MOSI : 0x00, 0x08, 0x40, 0x03, 0x41, 0x01, 0x00, 0x00, 0xA8, 0xC5
10)[10]MOSI : 0x00, 0x0C, 0x40, 0x03, 0x42, 0x01, 0x00, 0x00, 0x0B, 0x20
11)[10]MOSI : 0x00, 0x10, 0x40, 0x03, 0x43, 0x01, 0x00, 0x00, 0x47, 0x9F
===============================================================================
*/
__uint64_t S_2_1[7] = {0x00, 0x09, 0x00, 0x00, 0x80, 0x0C, 0x02};
__uint64_t S_2_2[7] = {0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43};
__uint64_t S_2_3[10] = {0x00, 0x10, 0x60, 0x03, 0x00, 0x80, 0xBB, 0x44, 0x59, 0x9F};
__uint64_t S_2_4[10] = {0x00, 0x08, 0x60, 0x03, 0x00, 0x56, 0xC4, 0x64, 0x97, 0x7B};
__uint64_t S_2_5[10] = {0x00, 0x0C, 0x60, 0x03, 0x12, 0x00, 0x00, 0x00, 0x69, 0x8D};
__uint64_t S_2_6[10] = {0x00, 0x00, 0x08, 0x03, 0x0C, 0x03, 0x00, 0x00, 0x29, 0xA5};

__uint64_t S_7_1[7] = {0x00, 0x09, 0x00, 0x00, 0x80, 0x0C, 0x02};
__uint64_t S_7_2[7] = {0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43};
__uint64_t S_7_3[10] = {0x00, 0x00, 0x84, 0x03, 0xC8, 0x89, 0x00, 0x80, 0x68, 0x6A};
__uint64_t S_7_4[7] = {0x00, 0x09, 0x00, 0x00, 0xF0, 0x21, 0xC3};
__uint64_t S_7_5[7] = {0x00, 0x08, 0x00, 0x00, 0x00, 0x3F, 0x43};
__uint64_t S_7_6[10] = {0x00, 0x14, 0x10, 0x03, 0x03, 0x00, 0x00, 0x00, 0xB1, 0x9E};
__uint64_t S_7_7[10] = {0x00, 0x00, 0x40, 0x03, 0x40, 0x01, 0x00, 0x00, 0x19, 0xC0};
__uint64_t S_7_8[10] = {0x00, 0x04, 0x40, 0x03, 0x6C, 0x00, 0x00, 0x00, 0xF8, 0x2F};
__uint64_t S_7_9[10] = {0x00, 0x08, 0x40, 0x03, 0x41, 0x01, 0x00, 0x00, 0xA8, 0xC5};
__uint64_t S_7_10[10] = {0x00, 0x0C, 0x40, 0x03, 0x42, 0x01, 0x00, 0x00, 0x0B, 0x20};
__uint64_t S_7_11[10] = {0x00, 0x10, 0x40, 0x03, 0x43, 0x01, 0x00, 0x00, 0x47, 0x9F};


/* R Mode */
struct spi_ioc_transfer R_2_tr[6] = 
{
    {
        .tx_buf = (unsigned long)R_2_1,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)R_2_2,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)R_2_3,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)R_2_4,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)R_2_5,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)R_2_6,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
};

struct spi_ioc_transfer R_7_tr[14] = 
{
    {
        .tx_buf = (unsigned long)R_7_1,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)R_7_2,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)R_7_3,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)R_7_4,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)R_7_5,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)R_7_6,
        .rx_buf = (unsigned long)miso_22,
        .len = 22,
    },
    {
        .tx_buf = (unsigned long)R_7_7,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)R_7_8,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)R_7_9,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
        
    },
    {
        .tx_buf = (unsigned long)R_7_10,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)R_7_11,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)R_7_12,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)R_7_13,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)R_7_14,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
};

struct spi_ioc_transfer R_7_tr_1[9] = 
{
    {
        .tx_buf = (unsigned long)R_7_1,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)R_7_2,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)R_7_3,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)R_7_4,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)R_7_5,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)R_7_6,
        .rx_buf = (unsigned long)miso_22,
        .len = 22,
    },
    {
        .tx_buf = (unsigned long)R_7_7,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)R_7_8,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)R_7_9,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
        
    },
};

struct spi_ioc_transfer R_7_tr_2[5] = 
{
    {
        .tx_buf = (unsigned long)R_7_10,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)R_7_11,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)R_7_12,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)R_7_13,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)R_7_14,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
};



/* L Mode */
struct spi_ioc_transfer L_2_tr[6] = 
{
    {
        .tx_buf = (unsigned long)L_2_1,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)L_2_2,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)L_2_3,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)L_2_4,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)L_2_5,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)L_2_6,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
};

struct spi_ioc_transfer L_7_tr[14] = 
{
    {
        .tx_buf = (unsigned long)L_7_1,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)L_7_2,
        .rx_buf = (unsigned long)miso_7,    
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)L_7_3,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)L_7_4,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)L_7_5,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)L_7_6,
        .rx_buf = (unsigned long)miso_22,
        .len = 22,
        
    },
    {
        .tx_buf = (unsigned long)L_7_7,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)L_7_8,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)L_7_9,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
            {
        .tx_buf = (unsigned long)L_7_10,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)L_7_11,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)L_7_12,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)L_7_13,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)L_7_14,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
};

struct spi_ioc_transfer L_7_tr_1[9] = 
{
    {
        .tx_buf = (unsigned long)L_7_1,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)L_7_2,
        .rx_buf = (unsigned long)miso_7,    
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)L_7_3,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)L_7_4,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)L_7_5,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)L_7_6,
        .rx_buf = (unsigned long)miso_22,
        .len = 22,
        
    },
    {
        .tx_buf = (unsigned long)L_7_7,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)L_7_8,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)L_7_9,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
};

struct spi_ioc_transfer L_7_tr_2[5] = 
{
    {
        .tx_buf = (unsigned long)L_7_10,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)L_7_11,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)L_7_12,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)L_7_13,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)L_7_14,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
};


/* M Mode */
struct spi_ioc_transfer M_2_tr[6] = 
{
    {
        .tx_buf = (unsigned long)M_2_1,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)M_2_2,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)M_2_3,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)M_2_4,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)M_2_5,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
            {
        .tx_buf = (unsigned long)M_2_6,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
};

struct spi_ioc_transfer M_7_tr[11] = 
{
    {
        .tx_buf = (unsigned long)M_7_1,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)M_7_2,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)M_7_3,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)M_7_4,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)M_7_5,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)M_7_6,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)M_7_7,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)M_7_8,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)M_7_9,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)M_7_10,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)M_7_11,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
};



struct spi_ioc_transfer M_7_tr_1[6] = 
{
    {
        .tx_buf = (unsigned long)M_7_1,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)M_7_2,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)M_7_3,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)M_7_4,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)M_7_5,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)M_7_6,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
};

struct spi_ioc_transfer M_7_tr_2[5] = 
{
    {
        .tx_buf = (unsigned long)M_7_7,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)M_7_8,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)M_7_9,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)M_7_10,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)M_7_11,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
};

/* S Mode */
struct spi_ioc_transfer S_2_tr[6] = 
{
    {
        .tx_buf = (unsigned long)S_2_1,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)S_2_2,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)S_2_3,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)S_2_4,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)S_2_5,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)S_2_6,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    }
};

struct spi_ioc_transfer S_7_tr[11] = 
{
    {
        .tx_buf = (unsigned long)S_7_1,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)S_7_2,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)S_7_3,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)S_7_4,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)S_7_5,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)S_7_6,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)S_7_7,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)S_7_8,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)S_7_9,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)S_7_10,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)S_7_11,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
        
    },
};

struct spi_ioc_transfer S_7_tr_1[6] = 
{
    {
        .tx_buf = (unsigned long)S_7_1,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)S_7_2,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)S_7_3,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)S_7_4,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)S_7_5,
        .rx_buf = (unsigned long)miso_7,
        .len = 7,
    },
    {
        .tx_buf = (unsigned long)S_7_6,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
};

struct spi_ioc_transfer S_7_tr_2[5] = 
{
    {
        .tx_buf = (unsigned long)S_7_7,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)S_7_8,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)S_7_9,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)S_7_10,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
    },
    {
        .tx_buf = (unsigned long)S_7_11,
        .rx_buf = (unsigned long)miso_10,
        .len = 10,
        
    },
};