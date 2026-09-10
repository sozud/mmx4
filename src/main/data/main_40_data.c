#include "common.h"
#include "func_tables.h"

void (*D_800FE9B0[3])() = { func_80061918, func_80061AA8, func_80061D90 };
void (*D_800FE9BC[3])() = { func_80061AE4, func_80061B58, func_80061D18 };

s8 D_800FE9C8[4] = { -32, -32, 64, 80 };
s8 D_800FE9CC[4] = { -16, -48, 32, 96 };
s8 D_800FE9D0[4] = { -16, -32, 32, 64 };
s8 D_800FE9D4[4] = { -40, -48, 80, 96 };
s8 D_800FE9D8[4] = { -104, -24, -48, 48 };
s8 D_800FE9DC[4] = { -40, -48, 80, 96 };
s8 D_800FE9E0[4] = { -32, -24, 64, 48 };

union AnimationStep D_800FE9E4[] = { { 0x00000001 } };
union AnimationStep D_800FE9E8[] = { { 0x01000001 } };
union AnimationStep D_800FE9EC[] = { { 0x02000001 } };
union AnimationStep D_800FE9F0[] = { { 0x03000001 } };
union AnimationStep D_800FE9F4[] = { { 0x04000001 } };
union AnimationStep D_800FE9F8[] = { { 0x05000001 } };

union AnimationStep* D_800FE9FC[6] = {
    D_800FE9E4,
    D_800FE9E8,
    D_800FE9EC,
    D_800FE9F0,
    D_800FE9F4,
    D_800FE9F8,
};
u8 D_800FEA14[8] = { 0, 1, 2, 1, 0, 2, 0, 0 };
u8 D_800FEA1C[8] = { 1, 2, 3, 4, 5, 2, 4, 0 };

s8* D_800FEA24[7] = {
    D_800FE9C8,
    D_800FE9CC,
    D_800FE9D0,
    D_800FE9D4,
    D_800FE9D8,
    D_800FE9DC,
    D_800FE9E0,
};
union AnimationStep** D_800FEA40[7] = {
    NULL,
    D_800FE9FC,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

s8 D_800FEA5C[12] = { -16, -32, -40, -48, -104, -24, -40, -48, -32, -24, 0, 0 };
u8 D_800FEA68[16] = { 32, 48, 3, 80, 80, 6, 208, 32, 8, 64, 32, 5, 64, 32, 5, 0 };
