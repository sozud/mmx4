// EffectObj, effect_object_update_funcs[40]
// 800BE038..800BE184
#include "common.h"

void func_800BE038(struct EffectObj* arg0)
{
    D_8010C0D4[arg0->state](arg0);
}

void func_800BE074(struct EffectObj* arg0)
{
    u8* temp_v0;

    arg0->ext.effect_40.unk14 = 1;
    arg0->y_pos.i.hi = 0x210;
    temp_v0 = D_8010C0CC[arg0->unk2];
    arg0->ext.effect_40.palette_source.bytes = temp_v0;
    arg0->ext.effect_40.palette.fields.timer = *temp_v0;
    arg0->ext.effect_40.palette.fields.unk1 = arg0->ext.effect_40.palette_source.bytes[1];
    arg0->ext.effect_40.palette.fields.step = arg0->ext.effect_40.palette_source.bytes[2];
    arg0->ext.effect_40.palette.fields.id = arg0->ext.effect_40.palette_source.bytes[3];
    arg0->state = (u8)arg0->state + 1;
}

void func_800BE0FC(struct EffectObj* arg0);

void func_800BE0DC(struct EffectObj* arg0)
{
    func_800BE0FC(arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_40", func_800BE0FC);

u8 D_8010C094[6][4] = {
    { 9, 0, 1, 0 },
    { 9, 0, 1, 1 },
    { 9, 0, 1, 2 },
    { 0x40, 0, 1, 3 },
    { 9, 0, 1, 4 },
    { 9, 0, 0xFB, 5 },
};

u8 D_8010C0AC[6][4] = {
    { 0x40, 0, 1, 6 },
    { 9, 0, 1, 7 },
    { 9, 0, 1, 8 },
    { 9, 0, 1, 9 },
    { 9, 0, 1, 0x0A },
    { 9, 0, 0xFB, 0x0B },
};

u16 D_8010C0C4[4] = { 0x30, 0x20, 0x40, 0x30 };

u8* D_8010C0CC[2] = { D_8010C094[0], D_8010C0AC[0] };

void (*D_8010C0D4[])(struct EffectObj*) = {
    func_800BE074,
    func_800BE0DC,
};
