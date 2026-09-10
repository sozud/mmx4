// EffectObj, effect_object_update_funcs[38]
// 800BD654..800BDE68
#include "common.h"

void func_800BD654(struct EffectObj* arg0)
{
    D_8010C048[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_38", func_800BD690);

INCLUDE_ASM("main/nonmatchings/effects/effect_38", func_800BD708);

INCLUDE_ASM("main/nonmatchings/effects/effect_38", func_800BD7B0);

void func_800BD890(struct EffectObj* arg0)
{
    arg0->ext.effect_38.timer--;
    if (arg0->ext.effect_38.timer == 0) {
        arg0->ext.effect_38.timer = 0x64;
        arg0->state++;
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_38", func_800BD8C4);

INCLUDE_ASM("main/nonmatchings/effects/effect_38", func_800BD938);

void func_800BDA2C(struct EffectObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800BDA4C(void* arg0)
{
    struct MiscObj* obj = find_free_misc_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x22;
        obj->ext.pointer.unk50 = arg0;
        obj->unk2 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_38", func_800BDA94);

INCLUDE_ASM("main/nonmatchings/effects/effect_38", func_800BDB10);

INCLUDE_ASM("main/nonmatchings/effects/effect_38", func_800BDBD4);

INCLUDE_ASM("main/nonmatchings/effects/effect_38", func_800BDD08);

INCLUDE_ASM("main/nonmatchings/effects/effect_38", func_800BDDE8);

u16 D_8010C02C[14] = {
    0x0190,
    0x0700,
    0,
    0x0300,
    0x0190,
    0x0800,
    0,
    0x0300,
    0x0170,
    0x0C00,
    0,
    0x0300,
    0,
    0x0F78,
};

void (*D_8010C048[])(struct EffectObj*) = {
    func_800BD690,
    func_800BD708,
    func_800BD7B0,
    func_800BD890,
    func_800BD8C4,
    func_800BD938,
    func_800BDA2C,
};
