// EffectObj, effect_object_update_funcs[19]
// 800B9940..800B9BD0
#include "common.h"

void func_800B9940(struct EffectObj* arg0)
{
    D_8010B7B8[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_19", func_800B997C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_19", func_800B99B4);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_19", func_800B9A08);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_19", func_800B9A48);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_19", func_800B9A68);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_19", func_800B9A78);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_19", func_800B9AB8);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_19", func_800B9AD8);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_19", func_800B9AE8);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_19", func_800B9B28);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_19", func_800B9B48);

void func_800B9B58(struct EffectObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_19", func_800B9B60);

void (*D_8010B7B8[])(struct EffectObj*) = {
    func_800B997C,
    func_800B99B4,
};
