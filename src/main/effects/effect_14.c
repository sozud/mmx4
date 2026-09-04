// EffectObj, effect_object_update_funcs[14]
// 800B89B4..800B8AF8
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_14", func_800B89B4);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_14", func_800B89CC);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_14", func_800B8A9C);

void func_800B8ABC(struct EffectObj* arg0)
{
    D_8010B6B8[arg0->state](arg0);
}

void (*D_8010B6B8[])(struct EffectObj*) = {
    func_800B89B4,
    func_800B89CC,
    func_800B8A9C,
};
