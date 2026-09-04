// EffectObj, effect_object_update_funcs[33]
// 800BC748..800BCE48
#include "common.h"

void func_800BC748(struct EffectObj* arg0)
{
    D_8010BF98[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_33", func_800BC784);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_33", func_800BC92C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_33", func_800BCD84);

void func_800BCE40(struct EffectObj* arg0)
{
}

void (*D_8010BF98[])(struct EffectObj*) = {
    func_800BC784,
    func_800BC92C,
    func_800BCD84,
    func_800BCE40,
};
