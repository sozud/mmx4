// EffectObj, effect_object_update_funcs[4]
// 800B5EB0..800B60BC
#include "common.h"

void func_800B5EB0(struct EffectObj* arg0)
{
    arg0->ext.effect_4.unk16 = -1;
    arg0->ext.effect_4.timer = 0x64;
    arg0->state++;
    func_80016FB4(3);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_04", func_800B5EEC);

void func_800B6060(struct EffectObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800B6080(struct EffectObj* arg0)
{
    D_8010B444[arg0->state](arg0);
}

void (*D_8010B444[])(struct EffectObj*) = {
    func_800B5EB0,
    func_800B5EEC,
    func_800B6060,
};
