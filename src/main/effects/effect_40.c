// EffectObj, effect_object_update_funcs[40]
// 800BE038..800BE184
#include "common.h"

void func_800BE038(struct EffectObj* arg0)
{
    D_8010C0D4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_40", func_800BE074);

void func_800BE0FC(struct EffectObj* arg0);

void func_800BE0DC(struct EffectObj* arg0)
{
    func_800BE0FC(arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_40", func_800BE0FC);

void (*D_8010C0D4[])(struct EffectObj*) = {
    func_800BE074,
    func_800BE0DC,
};
