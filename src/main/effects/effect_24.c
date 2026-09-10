// EffectObj, effect_object_update_funcs[24]
// 800BABA8..800BAF60
#include "common.h"

INCLUDE_ASM("main/nonmatchings/effects/effect_24", func_800BABA8);

INCLUDE_ASM("main/nonmatchings/effects/effect_24", func_800BAC58);

void func_800BAD10(struct EffectObj* arg0)
{
    u16 temp_v0;

    temp_v0 = arg0->ext.effect_24.timer - 1;
    arg0->ext.effect_24.timer = temp_v0;
    if (temp_v0 == 0) {
        arg0->unk5++;
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_24", func_800BAD44);

INCLUDE_ASM("main/nonmatchings/effects/effect_24", func_800BADD0);

void func_800BAE5C(struct EffectObj* arg0)
{
    arg0->ext.effect_24.unk1A = 0xA;
    if (--arg0->ext.effect_24.timer == 0) {
        arg0->state++;
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_24", func_800BAE94);

void func_800BAF04(struct EffectObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800BAF24(struct EffectObj* arg0)
{
    D_8010BE80[arg0->state](arg0);
}

void (*D_8010BE6C[5])(struct EffectObj*) = {
    func_800BAC58,
    func_800BAD10,
    func_800BAD44,
    func_800BADD0,
    func_800BAE5C,
};

void (*D_8010BE80[])(struct EffectObj*) = {
    func_800BABA8,
    func_800BAE94,
    func_800BAF04,
};
