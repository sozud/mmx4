// EffectObj, effect_object_update_funcs[29]
// 800BC144..800BC2E0
#include "common.h"

void func_800BC144(struct EffectObj* arg0)
{
    D_8010BF30[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_29", func_800BC180);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_29", func_800BC210);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_29", func_800BC258);

void (*D_8010BF30[])(struct EffectObj*) = {
    func_800BC180,
    func_800BC210,
};
