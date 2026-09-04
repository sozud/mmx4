// EffectObj, effect_object_update_funcs[41]
// 800BE184..800BE2C4
#include "common.h"

void func_800BE184(struct EffectObj* arg0)
{
    D_8010C0F8[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_41", func_800BE1C0);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_41", func_800BE214);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_41", func_800BE25C);

void (*D_8010C0F8[])(struct EffectObj*) = {
    func_800BE1C0,
    func_800BE214,
};
