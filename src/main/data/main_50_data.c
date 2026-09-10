#include "common.h"

u8 D_800FFBD8[4] = { 0xE0, 0xE0, 0x40, 0x50 };
u8 D_800FFBDC[8] = { 0, 1, 2, 1, 0, 2, 0, 0 };
u8 D_800FFBE4[8] = { 7, 8, 9, 7, 9, 8, 0, 0 };

union AnimationStep D_800FFBEC[1] = { { 0x00000101 } };
union AnimationStep D_800FFBF0[1] = { { 0x01000001 } };
union AnimationStep D_800FFBF4[1] = { { 0x02000001 } };
union AnimationStep D_800FFBF8[1] = { { 0x03000001 } };
union AnimationStep D_800FFBFC[1] = { { 0x04000001 } };
union AnimationStep D_800FFC00[1] = { { 0x05000001 } };
union AnimationStep D_800FFC04[1] = { { 0x06000001 } };
union AnimationStep D_800FFC08[1] = { { 0x07000001 } };
union AnimationStep D_800FFC0C[1] = { { 0x08000001 } };
union AnimationStep D_800FFC10[1] = { { 0x09000001 } };

union AnimationStep* D_800FFC14[10] = {
    D_800FFBEC,
    D_800FFBF0,
    D_800FFBF4,
    D_800FFBF8,
    D_800FFBFC,
    D_800FFC00,
    D_800FFC04,
    D_800FFC08,
    D_800FFC0C,
    D_800FFC10,
};
