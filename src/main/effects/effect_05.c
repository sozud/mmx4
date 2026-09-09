// EffectObj, effect_object_update_funcs[5]
// 800B60BC..800B6A0C
#include "common.h"

INCLUDE_ASM("main/nonmatchings/effects/effect_05", func_800B60BC);

void func_800B649C(struct EffectObj* arg0)
{
    arg0->ext.effect_5.unk1C = 0;
    arg0->ext.effect_5.unk1E = 0;
    arg0->ext.effect_5.unk14 = 0;
    arg0->ext.effect_5.unk18 = 0;
    arg0->state++;
}

INCLUDE_ASM("main/nonmatchings/effects/effect_05", func_800B64BC);

INCLUDE_ASM("main/nonmatchings/effects/effect_05", func_800B6660);
