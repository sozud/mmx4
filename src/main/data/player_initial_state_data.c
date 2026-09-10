#include "common.h"

struct PlayerInitialStateData {
    s32 unk20;
    s32 unk28;
    s32 unk24;
    s32 unk2C;
};

u8 D_800F8AD0[8] = { 0, 0x21, 0x22, 0x24, 0x23, 0, 0, 0 };

struct PlayerInitialStateData D_800F8AD8[5] = {
    { 0, 0, 0, 0 },
    { 0x28000, 0x3000, 0, 0 },
    { 0xC000, 0, 0x2C000, 0x4200 },
    { 0, 0, 0, 0 },
    { 0x28000, 0x3000, 0, 0 },
};

u8 D_800F8B28[8] = { 0, 0x4B, 0x64, 0, 0x4B, 0, 0, 0 };
