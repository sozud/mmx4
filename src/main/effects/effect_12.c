// EffectObj, effect_object_update_funcs[12]
// 800B806C..800B84DC
#include "common.h"

void func_800B806C(struct EffectObj* arg0)
{
    D_8010B62C[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_12", func_800B80A8);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_12", func_800B8114);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_12", func_800B8470);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_12", func_800B8490);

void (*D_8010B62C[])(struct EffectObj*) = {
    func_800B80A8,
    func_800B8114,
    func_800B8470,
};
