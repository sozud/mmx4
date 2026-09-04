// EffectObj, effect_object_update_funcs[34]
// 800BCE48..800BD1A4
#include "common.h"

void func_800BCE48(struct EffectObj* arg0)
{
    D_8010BFDC[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_34", func_800BCE84);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_34", func_800BCEE4);

void func_800BD01C(struct EffectObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_34", func_800BD024);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_34", func_800BD080);

void (*D_8010BFDC[])(struct EffectObj*) = {
    func_800BCE84,
    func_800BCEE4,
    func_800BD01C,
};
