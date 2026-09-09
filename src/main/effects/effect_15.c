// EffectObj, effect_object_update_funcs[15]
// 800B8AF8..800B8F5C
#include "common.h"

void func_800B8AF8(struct EffectObj* arg0)
{
    D_8010B6D0[arg0->state](arg0);
}

void func_800B8B34(struct EffectObj* arg0)
{
    arg0->unk5 = 1;
    arg0->ext.effect_15.unk14 = 6;
    arg0->state++;
    func_800B8B6C(arg0);
}

void func_800B8B6C(struct EffectObj* arg0)
{
    arg0->ext.effect_15.unk15 = arg0->ext.effect_15.unk14;
    func_800B8E74(arg0);
    D_8010B6D8[arg0->unk5](arg0);
}

void func_800B8BC0(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B8C00();
    } else {
        func_800B8C20();
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_15", func_800B8C00);

INCLUDE_ASM("main/nonmatchings/effects/effect_15", func_800B8C20);

void func_800B8C30(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B8C70(arg0);
    } else {
        func_800B8C90(arg0);
    }
}

void func_800B8C70(struct EffectObj* arg0)
{
    background_objects[0].unk2E = 0x80;
    arg0->unk6++;
}

void func_800B8C90(struct EffectObj* arg0)
{
    arg0->unk5 = 6;
    arg0->unk6 = 0;
}

void func_800B8CA0(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B8CE0(arg0);
    } else {
        func_800B8D00(arg0);
    }
}

void func_800B8CE0(struct EffectObj* arg0)
{
    background_objects[0].unk2E = 0xC0;
    arg0->unk6++;
}

void func_800B8D00(struct EffectObj* arg0)
{
    arg0->unk5 = 6;
    arg0->unk6 = 0;
}

void func_800B8D10(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B8D50();
    } else {
        func_800B8D7C();
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_15", func_800B8D50);

INCLUDE_ASM("main/nonmatchings/effects/effect_15", func_800B8D7C);

void func_800B8D8C(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B8DCC();
    } else {
        func_800B8DEC();
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_15", func_800B8DCC);

INCLUDE_ASM("main/nonmatchings/effects/effect_15", func_800B8DEC);

void func_800B8DFC(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B8E3C(arg0);
    } else {
        func_800B8E5C(arg0);
    }
}

void func_800B8E3C(struct EffectObj* arg0)
{
    background_objects[2].unk4A = 9;
    arg0->unk6++;
}

void func_800B8E5C(struct EffectObj* arg0)
{
    arg0->unk5 = 6;
    arg0->unk6 = 0;
}

void func_800B8E6C(struct EffectObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/effects/effect_15", func_800B8E74);

void (*D_8010B6D0[])(struct EffectObj*) = {
    func_800B8B34,
    func_800B8B6C,
};
