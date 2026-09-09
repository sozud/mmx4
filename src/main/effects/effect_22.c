// EffectObj, effect_object_update_funcs[22]
// 800BA57C..800BAA30
#include "common.h"

void func_800BA57C(struct EffectObj* arg0)
{
    D_8010BE24[arg0->state](arg0);
}

void func_800BA5B8(struct EffectObj* arg0)
{
    arg0->unk5 = 2;
    arg0->ext.effect_22.unk14 = 5;
    arg0->state++;
    func_800BA5F0(arg0);
}

void func_800BA5F0(struct EffectObj* arg0)
{
    arg0->ext.effect_22.unk15 = arg0->ext.effect_22.unk14;
    func_800BA9C0(arg0);
    D_8010BE2C[arg0->unk5](arg0);
}

void func_800BA644(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800BA684(arg0);
    } else {
        func_800BA6AC(arg0);
    }
}

void func_800BA684(struct EffectObj* arg0)
{
    arg0->unk6++;
    background_objects[0].unk4 = 2;
    arg0->ext.effect_22.unk16 = 0;
    arg0->ext.effect_22.unk18 = 0;
}

INCLUDE_ASM("main/nonmatchings/effects/effect_22", func_800BA6AC);

void func_800BA7C8(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800BA808(arg0);
    } else {
        func_800BA81C(arg0);
    }
}

void func_800BA808(struct EffectObj* arg0)
{
    arg0->unk6++;
}

void func_800BA81C(struct EffectObj* arg0)
{
    arg0->unk5 = 5;
    arg0->unk6 = 0;
}

void func_800BA82C(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800BA86C(arg0);
    } else {
        func_800BA898(arg0);
    }
}

void func_800BA86C(struct EffectObj* arg0)
{
    background_objects[1].unk4 = 1;
    background_objects[2].unk4 = 3;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/effects/effect_22", func_800BA898);

void func_800BA8CC(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800BA90C(arg0);
    } else {
        func_800BA938(arg0);
    }
}

void func_800BA90C(struct EffectObj* arg0)
{
    background_objects[1].unk4 = 1;
    background_objects[2].unk4 = 3;
    arg0->unk6++;
}

void func_800BA938(struct EffectObj* arg0)
{
    arg0->unk5 = 5;
    arg0->unk6 = 0;
}

void func_800BA948(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800BA988(arg0);
    } else {
        func_800BA9A8(arg0);
    }
}

void func_800BA988(struct EffectObj* arg0)
{
    background_objects[1].unk4 = 1;
    arg0->unk6++;
}

void func_800BA9A8(struct EffectObj* arg0)
{
    arg0->unk5 = 5;
    arg0->unk6 = 0;
}

void func_800BA9B8(struct EffectObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/effects/effect_22", func_800BA9C0);

void (*D_8010BE24[])(struct EffectObj*) = {
    func_800BA5B8,
    func_800BA5F0,
};

void (*D_8010BE2C[])(struct EffectObj*) = {
    func_800BA644,
    func_800BA7C8,
    func_800BA82C,
    func_800BA8CC,
    func_800BA948,
    func_800BA9B8,
};
