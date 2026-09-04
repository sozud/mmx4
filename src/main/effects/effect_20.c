// EffectObj, effect_object_update_funcs[20]
// 800B9BD0..800B9EC0
#include "common.h"

void func_800B9BD0(struct EffectObj* arg0)
{
    D_8010B7D4[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_20", func_800B9C0C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_20", func_800B9C44);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_20", func_800B9C98);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_20", func_800B9CD8);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_20", func_800B9CF8);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_20", func_800B9D08);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_20", func_800B9D48);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_20", func_800B9D68);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_20", func_800B9D78);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_20", func_800B9DB8);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_20", func_800B9DCC);

void func_800B9DDC(struct EffectObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_20", func_800B9DE4);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_20", func_800B9E54);

void (*D_8010B7D4[])(struct EffectObj*) = {
    func_800B9C0C,
    func_800B9C44,
};
