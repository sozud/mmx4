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

void func_800BD50C(struct EffectObj* arg0)
{
    if (--arg0->ext.effect_37.unk19 == 0) {
        need_palette_load |= 5;
        arg0->ext.effect_37.timer = arg0->ext.effect_37.unk1E;
        arg0->ext.effect_37.unk19 = arg0->ext.effect_37.unk1F;
        if (arg0->ext.effect_37.unk22 == 0) {
            arg0->ext.effect_37.action ^= 1;
        }
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        arg0->ext.effect_37.finished = 0;
    } else {
        g_FilterAmountR = 0x1F;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
    }
}

void func_800BD5AC(struct EffectObj* arg0)
{
    if (--arg0->ext.effect_37.unk19 == 0) {
        need_palette_load |= 5;
        arg0->ext.effect_37.timer = arg0->ext.effect_37.unk21;
        arg0->ext.effect_37.unk19 = arg0->ext.effect_37.unk1F;
        if (arg0->ext.effect_37.unk22 == 0) {
            arg0->ext.effect_37.action ^= 1;
        }
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        arg0->ext.effect_37.finished = 0;
    } else {
        g_FilterAmountR = 0x1F;
        g_FilterAmountG = 0x3E0;
        g_FilterAmountB = 0x7C00;
    }
}

void (*D_8010C018[])(struct EffectObj*) = {
    func_800BD3C0,
    func_800BD478,
    func_800BD4EC,
};

void (*D_8010C024[2])(struct EffectObj*) = {
    func_800BD50C,
    func_800BD5AC,
};
