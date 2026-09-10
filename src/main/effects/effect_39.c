// EffectObj, effect_object_update_funcs[39]
// 800BDE68..800BE038
#include "common.h"

void func_800BDE68(struct EffectObj* arg0)
{
    D_8010C08C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_39", func_800BDEA4);

void func_800BDF20(struct EffectObj* arg0)
{
    func_800BDF40(arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_39", func_800BDF40);

INCLUDE_ASM("main/nonmatchings/effects/effect_39", func_800BDFC8);

u8 D_8010C064[4][4] = {
    { 8, 0, 1, 3 },
    { 8, 0, 1, 4 },
    { 8, 0, 1, 5 },
    { 8, 0, 0xFD, 6 },
};

u8 D_8010C074[4][4] = {
    { 8, 0, 1, 0 },
    { 8, 0, 1, 1 },
    { 8, 0, 1, 2 },
    { 8, 0, 0xFD, 3 },
};

u8* D_8010C084[2] = { D_8010C064[0], D_8010C074[0] };

void (*D_8010C08C[])(struct EffectObj*) = {
    func_800BDEA4,
    func_800BDF20,
};
