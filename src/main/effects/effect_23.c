// EffectObj, effect_object_update_funcs[23]
// 800BAA30..800BABA8
#include "common.h"

void func_800BAA30(struct EffectObj* arg0)
{
    D_8010BE64[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_23", func_800BAA6C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_23", func_800BAAE0);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_23", func_800BAB3C);

void (*D_8010BE64[])(struct EffectObj*) = {
    func_800BAA6C,
    func_800BAAE0,
};
