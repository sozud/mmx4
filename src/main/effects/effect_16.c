// EffectObj, effect_object_update_funcs[16]
// 800B8F5C..800B9100
#include "common.h"

void func_800B8F5C(struct EffectObj* arg0)
{
    D_8010B6F4[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_16", func_800B8F98);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_16", func_800B902C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_16", func_800B9070);

void (*D_8010B6F4[])(struct EffectObj*) = {
    func_800B8F98,
    func_800B902C,
    func_800B9070,
};
