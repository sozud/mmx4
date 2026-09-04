// EffectObj, effect_object_update_funcs[24]
// 800BABA8..800BAF60
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_24", func_800BABA8);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_24", func_800BAC58);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_24", func_800BAD10);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_24", func_800BAD44);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_24", func_800BADD0);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_24", func_800BAE5C);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_24", func_800BAE94);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_24", func_800BAF04);

void func_800BAF24(struct EffectObj* arg0)
{
    D_8010BE80[arg0->state](arg0);
}

void (*D_8010BE80[])(struct EffectObj*) = {
    func_800BABA8,
    func_800BAE94,
    func_800BAF04,
};
