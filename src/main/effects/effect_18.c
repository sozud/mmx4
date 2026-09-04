// EffectObj, effect_object_update_funcs[18]
// 800B9690..800B9940
#include "common.h"

void func_800B9690(struct EffectObj* arg0)
{
    D_8010B7A8[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_18", func_800B96CC);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_18", func_800B96E0);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_18", func_800B97B0);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_18", func_800B97D0);

void (*D_8010B7A8[])(struct EffectObj*) = {
    func_800B96CC,
    func_800B96E0,
    func_800B97B0,
};
