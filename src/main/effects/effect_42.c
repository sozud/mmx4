// EffectObj, effect_object_update_funcs[42]
// 800BE2C4..800BE57C
#include "common.h"

INCLUDE_ASM("main/nonmatchings/effects/effect_42", func_800BE2C4);

void func_800BE30C(struct EffectObj* arg0)
{
    arg0->ext.effect_42.owner->unk8C = 1;
    arg0->unk5++;
}

INCLUDE_ASM("main/nonmatchings/effects/effect_42", func_800BE32C);

INCLUDE_ASM("main/nonmatchings/effects/effect_42", func_800BE364);

INCLUDE_ASM("main/nonmatchings/effects/effect_42", func_800BE434);

void func_800BE4A8(struct EffectObj* arg0)
{
    u8 timer;

    timer = arg0->ext.effect_42.timer - 1;
    arg0->ext.effect_42.timer = timer;
    if (timer == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
    }
}

void func_800BE4D4(struct EffectObj* arg0)
{
    D_8010C100[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_42", func_800BE510);

void func_800BE540(struct EffectObj* arg0)
{
    D_8010C114[arg0->state](arg0);
}

void (*D_8010C114[])(struct EffectObj*) = {
    func_800BE2C4,
    func_800BE4D4,
    func_800BE510,
};
