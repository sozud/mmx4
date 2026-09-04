// EffectObj, effect_object_update_funcs[4]
// 800B5EB0..800B60BC
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_04", func_800B5EB0);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_04", func_800B5EEC);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_04", func_800B6060);

void func_800B6080(struct EffectObj* arg0)
{
    D_8010B444[arg0->state](arg0);
}

void (*D_8010B444[])(struct EffectObj*) = {
    func_800B5EB0,
    func_800B5EEC,
    func_800B6060,
};
