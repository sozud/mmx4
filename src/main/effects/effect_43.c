// EffectObj, effect_object_update_funcs[43]
// 800BE57C..800BE83C
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_43", func_800BE57C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_43", func_800BE598);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_43", func_800BE5F4);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_43", func_800BE6D8);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_43", func_800BE714);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_43", func_800BE730);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_43", func_800BE7C4);

void func_800BE800(struct EffectObj* arg0)
{
    D_8010C130[arg0->state](arg0);
}

void (*D_8010C130[])(struct EffectObj*) = {
    func_800BE57C,
    func_800BE6D8,
    func_800BE7C4,
};
