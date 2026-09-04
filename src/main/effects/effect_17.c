// EffectObj, effect_object_update_funcs[17]
// 800B9100..800B9690
#include "common.h"

void func_800B9100(struct EffectObj* arg0)
{
    D_8010B79C[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_17", func_800B913C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_17", func_800B91E0);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_17", func_800B9310);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_17", func_800B9354);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_17", func_800B94B8);

void (*D_8010B79C[])(struct EffectObj*) = {
    func_800B913C,
    func_800B91E0,
    func_800B9310,
};
