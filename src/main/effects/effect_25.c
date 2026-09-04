// EffectObj, effect_object_update_funcs[25]
// 800BAF60..800BB1F0
#include "common.h"

void func_800BAF60(struct EffectObj* arg0)
{
    D_8010BE90[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_25", func_800BAF9C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_25", func_800BAFD4);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_25", func_800BB028);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_25", func_800BB068);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_25", func_800BB088);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_25", func_800BB098);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_25", func_800BB0D8);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_25", func_800BB0F8);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_25", func_800BB108);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_25", func_800BB148);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_25", func_800BB168);

void func_800BB178(struct EffectObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_25", func_800BB180);

void (*D_8010BE90[])(struct EffectObj*) = {
    func_800BAF9C,
    func_800BAFD4,
};
