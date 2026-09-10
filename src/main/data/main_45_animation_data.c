#include "common.h"
#include "func_tables.h"

void (*D_800FF888[3])() = { func_8009216C, func_80065B24, func_80065B30 };
void (*D_800FF894[1])() = { func_80065B6C };
s8 D_800FF898[4] = { -56, 12, 39, 86 };
u8 D_800FF89C[20] = {
    0,
    1,
    2,
    1,
    2,
    0,
    3,
    3,
    2,
    1,
    0,
    1,
    0,
    2,
    4,
    3,
    3,
    0xFF,
    0,
    0,
};
u8 D_800FF8B0[8] = { 0x11, 0x22, 0x44, 0x08, 0, 0, 0, 0 };

union AnimationStep D_800FF8B8[] = { { 0x00000101 } };
union AnimationStep D_800FF8BC[] = { { 0x01000101 } };
union AnimationStep D_800FF8C0[] = { { 0x02000101 } };
union AnimationStep D_800FF8C4[] = {
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x06FD0101 },
};
union AnimationStep D_800FF8D4[] = {
    { 0x03010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x06FD0101 },
};
union AnimationStep D_800FF8E4[] = { { 0x07000101 } };
union AnimationStep D_800FF8E8[] = { { 0x0A000101 } };
union AnimationStep D_800FF8EC[] = { { 0x0B000101 } };
union AnimationStep D_800FF8F0[] = { { 0x0C000101 } };
union AnimationStep D_800FF8F4[] = { { 0x0D000101 } };
union AnimationStep D_800FF8F8[] = { { 0x0E000101 } };
union AnimationStep D_800FF8FC[] = { { 0x0F000101 } };
union AnimationStep D_800FF900[] = { { 0x10000101 } };
union AnimationStep D_800FF904[] = { { 0x11000101 } };
union AnimationStep D_800FF908[] = { { 0x12000101 } };
union AnimationStep D_800FF90C[] = { { 0x13000101 } };
union AnimationStep D_800FF910[] = { { 0x14000101 } };
union AnimationStep D_800FF914[] = { { 0x15000101 } };

union AnimationStep* D_800FF918[19] = {
    D_800FF8B8,
    D_800FF8BC,
    D_800FF8C0,
    D_800FF8C4,
    D_800FF8D4,
    D_800FF8E4,
    D_800FF8E8,
    D_800FF8EC,
    D_800FF8F0,
    D_800FF8F4,
    D_800FF8F8,
    D_800FF8FC,
    D_800FF900,
    D_800FF904,
    D_800FF908,
    D_800FF90C,
    D_800FF910,
    D_800FF914,
    NULL,
};
