// EffectObj, effect_object_update_funcs[13]
// 800B84DC..800B89B4
#include "common.h"

void func_800B84DC(struct EffectObj* arg0)
{
    D_8010B638[arg0->state](arg0);
}

void func_800B8518(struct EffectObj* arg0)
{
    arg0->ext.unk_effect.unk14 = 0;
    func_800B8630();
    arg0->ext.unk_effect.unk15 = 0;
    arg0->state++;
}

INCLUDE_ASM("main/nonmatchings/effects/effect_13", func_800B8554);

void func_800B8610(struct EffectObj* arg0)
{
    func_8002B108(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/effects/effect_13", func_800B8630);

INCLUDE_ASM("main/nonmatchings/effects/effect_13", func_800B875C);

INCLUDE_ASM("main/nonmatchings/effects/effect_13", func_800B887C);

void (*D_8010B638[])(struct EffectObj*) = {
    func_800B8518,
    func_800B8554,
    func_800B8610,
};

// active, item ID, little-endian X, little-endian Y
u8 D_8010B644[19][6] = {
    { 0, 1, 0x50, 0x15, 0xB0, 0x05 },
    { 0, 1, 0x10, 0x15, 0xD0, 0x05 },
    { 0, 1, 0xA0, 0x15, 0x00, 0x06 },
    { 0, 1, 0x60, 0x15, 0x20, 0x06 },
    { 0, 1, 0xE0, 0x14, 0x30, 0x06 },
    { 0, 1, 0xA0, 0x15, 0x40, 0x06 },
    { 0, 1, 0x10, 0x15, 0x80, 0x06 },
    { 0, 1, 0x80, 0x15, 0xB0, 0x06 },
    { 0, 1, 0xE0, 0x14, 0xE0, 0x06 },
    { 0, 1, 0xA0, 0x15, 0x10, 0x07 },
    { 0, 1, 0x30, 0x15, 0x30, 0x07 },
    { 0, 1, 0xE0, 0x14, 0x80, 0x07 },
    { 0, 1, 0x10, 0x15, 0xA0, 0x07 },
    { 0, 1, 0x40, 0x15, 0xC0, 0x07 },
    { 0, 1, 0xA0, 0x15, 0x20, 0x08 },
    { 0, 1, 0x20, 0x15, 0x20, 0x08 },
    { 0, 1, 0xE0, 0x14, 0x70, 0x08 },
    { 0, 1, 0x50, 0x15, 0xC0, 0x08 },
    { 0, 0xFF, 0, 0, 0, 0 },
};

u16 D_8010B6B6 = 0;
