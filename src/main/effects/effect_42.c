// EffectObj, effect_object_update_funcs[42]
// 800BE2C4..800BE57C
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_42", func_800BE2C4);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_42", func_800BE30C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_42", func_800BE32C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_42", func_800BE364);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_42", func_800BE434);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_42", func_800BE4A8);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_42", func_800BE4D4);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_42", func_800BE510);

void func_800BE540(struct EffectObj* arg0)
{
    D_8010C114[arg0->state](arg0);
}

void (*D_8010C114[])(struct EffectObj*) = {
    func_800BE2C4,
    func_800BE4D4,
    func_800BE510,
};
