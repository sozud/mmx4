#include "common.h"
#include "func_tables.h"

void (*D_800FFA1C[3])() = { func_8009216C, func_800672D8, func_800672EC };

union AnimationStep D_800FFA28[] = { { 0x00010001 }, { 0x01FF0001 } };
union AnimationStep D_800FFA30[] = { { 0x02010001 }, { 0x03FF0101 } };
union AnimationStep D_800FFA38[] = { { 0x0A010001 }, { 0x0BFF0101 } };
union AnimationStep D_800FFA40[] = { { 0x0E010001 }, { 0x0FFF0101 } };
union AnimationStep D_800FFA48[] = { { 0x04010001 }, { 0x05FF0101 } };
union AnimationStep D_800FFA50[] = { { 0x0C010001 }, { 0x0DFF0101 } };
union AnimationStep D_800FFA58[] = {
    { 0x10010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13FD0002 },
};
union AnimationStep D_800FFA68[] = {
    { 0x14010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x17010002 },
    { 0x18010003 },
    { 0x19010004 },
    { 0x1A000005 },
};
union AnimationStep D_800FFA84[] = { { 0x1B000001 } };
union AnimationStep D_800FFA88[] = { { 0x1C000001 } };
union AnimationStep D_800FFA8C[] = { { 0x1D000001 } };
union AnimationStep D_800FFA90[] = { { 0x1E000001 } };
union AnimationStep D_800FFA94[] = { { 0x1F000001 } };

union AnimationStep* D_800FFA98[13] = {
    D_800FFA28,
    D_800FFA30,
    D_800FFA38,
    D_800FFA40,
    D_800FFA48,
    D_800FFA50,
    D_800FFA58,
    D_800FFA68,
    D_800FFA84,
    D_800FFA88,
    D_800FFA8C,
    D_800FFA90,
    D_800FFA94,
};

s8 D_800FFACC[4] = { -9, -9, 23, 18 };
u8 D_800FFAD0[4] = { 0, 7, 13, 24 };
u8 D_800FFAD4[4] = { 0, 0, 11, 11 };
u16 D_800FFAD8[4] = { 0x40, 0x50, 0x60, 0x70 };
u8 D_800FFAE0[8] = { 8, 9, 10, 11, 12 };
