// EffectObj, effect_object_update_funcs[26]
// 800BB1F0..800BB9B8
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_26", func_800BB1F0);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_26", func_800BB314);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_26", func_800BB364);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_26", func_800BB508);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_26", func_800BB588);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_26", func_800BB5F4);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_26", func_800BB68C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_26", func_800BB750);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_26", func_800BB85C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_26", func_800BB888);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_26", func_800BB928);

void func_800BB97C(struct EffectObj* arg0)
{
    D_8010BEA8[arg0->state](arg0);
}

void (*D_8010BEA8[])(struct EffectObj*) = {
    func_800BB1F0,
    func_800BB364,
    func_800BB5F4,
    func_800BB68C,
    func_800BB750,
    func_800BB85C,
    func_800BB888,
    func_800BB928,
};
