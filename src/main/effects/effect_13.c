// EffectObj, effect_object_update_funcs[13]
// 800B84DC..800B89B4
#include "common.h"

void func_800B84DC(struct EffectObj* arg0)
{
    D_8010B638[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_13", func_800B8518);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_13", func_800B8554);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_13", func_800B8610);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_13", func_800B8630);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_13", func_800B875C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_13", func_800B887C);

void (*D_8010B638[])(struct EffectObj*) = {
    func_800B8518,
    func_800B8554,
    func_800B8610,
};
