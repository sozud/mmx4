// EffectObj, effect_object_update_funcs[29]
// 800BC144..800BC2E0
#include "common.h"

void func_800BC144(struct EffectObj* arg0)
{
    D_8010BF30[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_29", func_800BC180);

INCLUDE_ASM("main/nonmatchings/effects/effect_29", func_800BC210);

INCLUDE_ASM("main/nonmatchings/effects/effect_29", func_800BC258);

void (*D_8010BF30[])(struct EffectObj*) = {
    func_800BC180,
    func_800BC210,
};

u8 D_8010BF38[4][2] = {
    { 0x28, 0x18 },
    { 0x40, 0x20 },
    { 0x10, 0x40 },
    { 0, 0 },
};

struct Effect29AnimationStep {
    u8 timer;
    u8 unused;
    s8 frame_step;
    u8 position;
};

struct Effect29AnimationStep D_8010BF40[9] = {
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 3 },
    { 25, 0, 1, 4 },
    { 2, 0, 1, 5 },
    { 2, 0, 1, 6 },
    { 2, 0, 1, 7 },
    { 2, 0, 0, 8 },
};

struct Effect29AnimationStep D_8010BF64[9] = {
    { 2, 0, 1, 8 },
    { 2, 0, 1, 7 },
    { 2, 0, 1, 6 },
    { 2, 0, 1, 5 },
    { 25, 0, 1, 4 },
    { 2, 0, 1, 3 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 1 },
    { 2, 0, 0, 0 },
};

u8* D_8010BF88[2] = {
    (u8*)D_8010BF40,
    (u8*)D_8010BF64,
};
