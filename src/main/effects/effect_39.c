// EffectObj, effect_object_update_funcs[39]
// 800BDE68..800BE038
#include "common.h"

void func_800BDE68(struct EffectObj* arg0)
{
    D_8010C08C[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_39", func_800BDEA4);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_39", func_800BDF20);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_39", func_800BDF40);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_39", func_800BDFC8);

void (*D_8010C08C[])(struct EffectObj*) = {
    func_800BDEA4,
    func_800BDF20,
};
