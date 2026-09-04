// EffectObj, effect_object_update_funcs[32]
// 800BC518..800BC748
#include "common.h"

void func_800BC518(struct EffectObj* arg0)
{
    D_8010BF90[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_32", func_800BC554);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_32", func_800BC568);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_32", func_800BC5D4);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_32", func_800BC63C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_32", func_800BC6FC);

void (*D_8010BF90[])(struct EffectObj*) = {
    func_800BC554,
    func_800BC568,
};
