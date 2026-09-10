// EffectObj, effect_object_update_funcs[43]
// 800BE57C..800BE83C
#include "common.h"

void func_800BE57C(struct EffectObj* arg0)
{
    if (arg0->unk2 == 0) {
        arg0->state = 1;
    } else {
        arg0->state = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_43", func_800BE598);

INCLUDE_ASM("main/nonmatchings/effects/effect_43", func_800BE5F4);

void func_800BE6D8(struct EffectObj* arg0)
{
    D_8010C120[arg0->unk5](arg0);
}

void func_800BE714(struct EffectObj* arg0)
{
    arg0->ext.effect_43.unk14 = 1;
    arg0->ext.effect_43.unk16 = 1;
    arg0->unk5++;
}

INCLUDE_ASM("main/nonmatchings/effects/effect_43", func_800BE730);

void func_800BE7C4(struct EffectObj* arg0)
{
    D_8010C128[arg0->unk5](arg0);
}

void func_800BE800(struct EffectObj* arg0)
{
    D_8010C130[arg0->state](arg0);
}

void (*D_8010C120[2])(struct EffectObj*) = {
    func_800BE598,
    func_800BE5F4,
};

void (*D_8010C128[2])(struct EffectObj*) = {
    func_800BE714,
    func_800BE730,
};

void (*D_8010C130[])(struct EffectObj*) = {
    func_800BE57C,
    func_800BE6D8,
    func_800BE7C4,
};
