// EffectObj, effect_object_update_funcs[9]
// 800B75C8..800B7EE8
#include "common.h"

void func_800B75C8(struct EffectObj* arg0)
{
    D_8010B4F8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_09", func_800B7604);

INCLUDE_ASM("main/nonmatchings/effects/effect_09", func_800B7630);

void func_800B7668(struct EffectObj* arg0)
{
    D_8010B504[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_09", func_800B76A4);

INCLUDE_ASM("main/nonmatchings/effects/effect_09", func_800B7764);

INCLUDE_ASM("main/nonmatchings/effects/effect_09", func_800B7934);

INCLUDE_ASM("main/nonmatchings/effects/effect_09", func_800B7B18);

INCLUDE_ASM("main/nonmatchings/effects/effect_09", func_800B7CFC);

INCLUDE_ASM("main/nonmatchings/effects/effect_09", func_800B7E88);

void (*D_8010B4F8[])(struct EffectObj*) = {
    func_800B7604,
    func_800B7630,
    func_800B7668,
};
