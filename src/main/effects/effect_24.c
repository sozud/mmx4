// EffectObj, effect_object_update_funcs[24]
// 800BABA8..800BAF60
#include "common.h"

INCLUDE_ASM("main/nonmatchings/effects/effect_24", func_800BABA8);

INCLUDE_ASM("main/nonmatchings/effects/effect_24", func_800BAC58);

void func_800BAD10(struct EffectObj* arg0)
{
    if (--arg0->ext.effect_24.timer == 0) {
        arg0->unk5++;
    }
}

void func_800BAD44(struct EffectObj* arg0)
{
    struct EffectObj* spawned;
    struct EffectObj** entry;
    u32 index;
    s32 count;
    s32 expected;

    spawned = arg0->ext.effect_24.spawned_effect;
    if (spawned->id != 4 || *(u16*)spawned == 0x400) {
        index = 0;
        count = 0;
        expected = 1;
        entry = D_8013B8E8;
        do {
            if ((*entry)->unk5 == expected) {
                count++;
            }
            index++;
            entry++;
        } while (index < 0x16U);
        if (count == 0x16) {
            arg0->ext.effect_24.unk1B = 0;
            arg0->unk5++;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_24", func_800BADD0);

void func_800BAE5C(struct EffectObj* arg0)
{
    arg0->ext.effect_24.unk1A = 0xA;
    if (--arg0->ext.effect_24.timer == 0) {
        arg0->state++;
    }
}

void func_800BAE94(struct EffectObj* arg0)
{
    D_8010BE6C[arg0->unk5](arg0);
    if (arg0->ext.effect_24.unk1A == 0) {
        func_8001540C(0, 0x13, 0);
        arg0->ext.effect_24.unk1A = 0x3C;
    } else {
        arg0->ext.effect_24.unk1A--;
    }
}

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
