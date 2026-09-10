#include "common.h"

union AnimationStep D_800F3000[10] = {
    { .packed = 0x00010004 },
    { .packed = 0x01010004 },
    { .packed = 0x02010002 },
    { .packed = 0x03010004 },
    { .packed = 0x04010004 },
    { .packed = 0x05010004 },
    { .packed = 0x06010004 },
    { .packed = 0x07010004 },
    { .packed = 0x08010003 },
    { .packed = 0x09000003 },
};
union AnimationStep D_800F3028[11] = {
    { .packed = 0x0A010002 },
    { .packed = 0x0B010002 },
    { .packed = 0x0A010002 },
    { .packed = 0x0B010002 },
    { .packed = 0x0A010002 },
    { .packed = 0x0B010002 },
    { .packed = 0x0C010003 },
    { .packed = 0x0D010003 },
    { .packed = 0x0E010003 },
    { .packed = 0x0F010003 },
    { .packed = 0x10000003 },
};
union AnimationStep D_800F3054[10] = {
    { .packed = 0x11010002 },
    { .packed = 0x12010002 },
    { .packed = 0x11010002 },
    { .packed = 0x12010002 },
    { .packed = 0x11010002 },
    { .packed = 0x12010002 },
    { .packed = 0x13010003 },
    { .packed = 0x14010003 },
    { .packed = 0x15010003 },
    { .packed = 0x16000003 },
};
union AnimationStep* D_800F307C[3] = { D_800F3028, D_800F3054, D_800F3000 };
s16 D_800F3088[16] = { -30, -26, -21, -18, -14, -10, -7, -3, 3, 7, 10, 14, 18, 21, 26, 30 };
s16 D_800F30A8[16] = { -22, -19, -17, -13, -10, -7, -4, -2, 2, 4, 7, 10, 13, 17, 19, 22 };
