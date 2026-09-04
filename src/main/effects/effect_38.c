// EffectObj, effect_object_update_funcs[38]
// 800BD654..800BDE68
#include "common.h"

void func_800BD654(struct EffectObj* arg0)
{
    D_8010C048[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_38", func_800BD690);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_38", func_800BD708);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_38", func_800BD7B0);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_38", func_800BD890);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_38", func_800BD8C4);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_38", func_800BD938);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_38", func_800BDA2C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_38", func_800BDA4C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_38", func_800BDA94);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_38", func_800BDB10);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_38", func_800BDBD4);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_38", func_800BDD08);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_38", func_800BDDE8);

void (*D_8010C048[])(struct EffectObj*) = {
    func_800BD690,
    func_800BD708,
    func_800BD7B0,
    func_800BD890,
    func_800BD8C4,
    func_800BD938,
    func_800BDA2C,
};
