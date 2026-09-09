// EffectObj, effect_object_update_funcs[19]
// 800B9940..800B9BD0
#include "common.h"

void func_800B9940(struct EffectObj* arg0)
{
    D_8010B7B8[arg0->state](arg0);
}

void func_800B997C(struct EffectObj* arg0)
{
    arg0->unk5 = 2;
    arg0->ext.effect_19.unk14 = 3;
    arg0->state++;
    func_800B99B4(arg0);
}

void func_800B99B4(struct EffectObj* arg0)
{
    arg0->ext.effect_19.unk15 = arg0->ext.effect_19.unk14;
    func_800B9B60();
    D_8010B7C0[arg0->unk5](arg0);
}

void func_800B9A08(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B9A48(arg0);
    } else {
        func_800B9A68(arg0);
    }
}

void func_800B9A48(struct EffectObj* arg0)
{
    background_objects[0].unk2E = 0xC0;
    arg0->unk6++;
}

void func_800B9A68(struct EffectObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_800B9A78(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B9AB8(arg0);
    } else {
        func_800B9AD8(arg0);
    }
}

void func_800B9AB8(struct EffectObj* arg0)
{
    background_objects[0].unk2E = 0x90;
    arg0->unk6++;
}

void func_800B9AD8(struct EffectObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_800B9AE8(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B9B28(arg0);
    } else {
        func_800B9B48(arg0);
    }
}

void func_800B9B28(struct EffectObj* arg0)
{
    background_objects[0].unk2E = 0x90;
    arg0->unk6++;
}

void func_800B9B48(struct EffectObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_800B9B58(struct EffectObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/effects/effect_19", func_800B9B60);

void (*D_8010B7B8[])(struct EffectObj*) = {
    func_800B997C,
    func_800B99B4,
};
