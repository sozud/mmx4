// EffectObj, effect_object_update_funcs[37]
// 800BD384..800BD654
#include "common.h"

void func_800BD384(struct EffectObj* arg0)
{
    D_8010C018[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_37", func_800BD3C0);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_37", func_800BD478);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_37", func_800BD4EC);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_37", func_800BD50C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_37", func_800BD5AC);

void (*D_8010C018[])(struct EffectObj*) = {
    func_800BD3C0,
    func_800BD478,
    func_800BD4EC,
};
