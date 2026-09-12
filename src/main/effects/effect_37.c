// EffectObj, effect_object_update_funcs[37]
// 800BD384..800BD654
#include "common.h"

void func_800BD384(struct EffectObj* arg0)
{
    D_8010C018[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_37", func_800BD3C0);

void func_800BD478(struct EffectObj* arg0)
{
    if (arg0->ext.effect_37.finished != 0) {
        D_8010C024[arg0->ext.effect_37.action](arg0);
        return;
    }

    if (--arg0->ext.effect_37.timer == 0) {
        arg0->ext.effect_37.finished = 1;
    }
}

void func_800BD4EC(struct EffectObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/effects/effect_37", func_800BD50C);

INCLUDE_ASM("main/nonmatchings/effects/effect_37", func_800BD5AC);

void (*D_8010C018[])(struct EffectObj*) = {
    func_800BD3C0,
    func_800BD478,
    func_800BD4EC,
};

void (*D_8010C024[2])(struct EffectObj*) = {
    func_800BD50C,
    func_800BD5AC,
};
