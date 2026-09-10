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
u8 D_8010B434[16] = {
#ifdef VERSION_JP
    0x75,
    0x76,
    0x77,
    0x78,
    0x79,
    0x7A,
    0x7B,
    0x7C,
    0x7D,
    0,
    0x7E,
    0x7F,
    0x80,
    0,
    0,
    0,
#else
    0x76,
    0x77,
    0x78,
    0x79,
    0x7A,
    0x7B,
    0x7C,
    0x7D,
    0x7E,
    0,
    0x7F,
    0x80,
    0x81,
    0,
    0,
    0,
#endif
};

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
