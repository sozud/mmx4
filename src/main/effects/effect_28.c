// EffectObj, effect_object_update_funcs[28]
// 800BBC14..800BC144
#include "common.h"

void func_800BBC14(struct EffectObj* arg0)
{
    D_8010BED4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_28", func_800BBC50);

INCLUDE_ASM("main/nonmatchings/effects/effect_28", func_800BBD24);

INCLUDE_ASM("main/nonmatchings/effects/effect_28", func_800BBD88);

void func_800BBE84(struct EffectObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/effects/effect_28", func_800BBEA4);

INCLUDE_ASM("main/nonmatchings/effects/effect_28", func_800BBF34);

INCLUDE_ASM("main/nonmatchings/effects/effect_28", func_800BBFCC);

void (*D_8010BED4[])(struct EffectObj*) = {
    func_800BBC50,
    func_800BBD24,
    func_800BBD88,
    func_800BBE84,
};

void (*D_8010BEE4[])(struct EffectObj*) = {
    func_800BBEA4,
    func_800BBF34,
};

s32 D_8010BEEC[4] = { 0, 1, 2, 3 };

struct Effect28AnimationStep {
    u8 timer;
    u8 unused;
    s8 frame_step;
    u8 frame;
};

struct Effect28AnimationStep D_8010BEFC[3] = {
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, -2, 2 },
};

struct Effect28AnimationStep D_8010BF08[3] = {
    { 2, 0, 1, 3 },
    { 2, 0, 1, 4 },
    { 2, 0, -2, 5 },
};

struct Effect28AnimationStep D_8010BF14[4] = {
    { 4, 0, 1, 6 },
    { 4, 0, 1, 7 },
    { 4, 0, 1, 8 },
    { 4, 0, -3, 9 },
};

struct Effect28AnimationStep* D_8010BF24[3] = {
    D_8010BEFC,
    D_8010BF08,
    D_8010BF14,
};
