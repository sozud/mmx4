// EffectObj, effect_object_update_funcs[20]
// 800B9BD0..800B9EC0
#include "common.h"

void func_800B9BD0(struct EffectObj* arg0)
{
    D_8010B7D4[arg0->state](arg0);
}

void func_800B9C0C(struct EffectObj* arg0)
{
    arg0->unk5 = 2;
    arg0->ext.effect_20.unk14 = 3;
    arg0->state++;
    func_800B9C44(arg0);
}

void func_800B9C44(struct EffectObj* arg0)
{
    arg0->ext.effect_20.unk15 = arg0->ext.effect_20.unk14;
    func_800B9DE4(arg0);
    D_8010B7DC[arg0->unk5](arg0);
}

void func_800B9C98(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B9CD8(arg0);
    } else {
        func_800B9CF8(arg0);
    }
}

void func_800B9CD8(struct EffectObj* arg0)
{
    background_objects[0].unk2E = 0xC0;
    arg0->unk6++;
}

void func_800B9CF8(struct EffectObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_800B9D08(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B9D48(arg0);
    } else {
        func_800B9D68(arg0);
    }
}

void func_800B9D48(struct EffectObj* arg0)
{
    background_objects[0].unk2E = 0x90;
    arg0->unk6++;
}

void func_800B9D68(struct EffectObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_800B9D78(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B9DB8(arg0);
    } else {
        func_800B9DCC(arg0);
    }
}

void func_800B9DB8(struct EffectObj* arg0)
{
    arg0->unk6++;
}

void func_800B9DCC(struct EffectObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_800B9DDC(struct EffectObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/effects/effect_20", func_800B9DE4);

INCLUDE_ASM("main/nonmatchings/effects/effect_20", func_800B9E54);

void (*D_8010B7C0[4])(struct EffectObj*) = {
    func_800B9A08,
    func_800B9A78,
    func_800B9AE8,
    func_800B9B58,
};

s16 D_8010B7D0[2] = { 0x0740, 0x0A00 };

void (*D_8010B7D4[])(struct EffectObj*) = {
    func_800B9C0C,
    func_800B9C44,
};

void (*D_8010B7DC[4])(struct EffectObj*) = {
    func_800B9C98,
    func_800B9D08,
    func_800B9D78,
    func_800B9DDC,
};
