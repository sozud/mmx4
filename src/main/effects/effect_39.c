// EffectObj, effect_object_update_funcs[39]
// 800BDE68..800BE038
#include "common.h"

void func_800BDE68(struct EffectObj* arg0)
{
    D_8010C08C[arg0->state](arg0);
}

void func_800BDEA4(struct EffectObj* arg0)
{
    u8* temp_v0;

    arg0->ext.effect_39.unk14 = 1;
    if (arg0->unk2 == 0) {
        arg0->x_pos.i.hi = 0x940;
        arg0->y_pos.i.hi = 0x2D0;
    }
    temp_v0 = D_8010C084[arg0->unk2];
    arg0->ext.effect_39.palette_source.bytes = temp_v0;
    arg0->ext.effect_39.palette.fields.timer = temp_v0[0];
    arg0->ext.effect_39.palette.fields.unk1 = arg0->ext.effect_39.palette_source.bytes[1];
    arg0->ext.effect_39.palette.fields.step = arg0->ext.effect_39.palette_source.bytes[2];
    arg0->ext.effect_39.palette.fields.id = arg0->ext.effect_39.palette_source.bytes[3];
    arg0->state = (u8)arg0->state + 1;
}

void func_800BDF20(struct EffectObj* arg0)
{
    func_800BDF40(arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_39", func_800BDF40);

void func_800BDFC8(struct EffectObj* arg0)
{
    u16 x;
    s32 i;

    x = arg0->x_pos.u.hi;
    i = 0;
    do {
        func_800DA984(arg0->ext.effect_39.palette.fields.id, (s16)x - 0x40,
            arg0->y_pos.i.hi - 0x20);
        x += 0x80;
        i += 1;
    } while (i < 0x1A);
}

u8 D_8010C064[4][4] = {
    { 8, 0, 1, 3 },
    { 8, 0, 1, 4 },
    { 8, 0, 1, 5 },
    { 8, 0, 0xFD, 6 },
};

u8 D_8010C074[4][4] = {
    { 8, 0, 1, 0 },
    { 8, 0, 1, 1 },
    { 8, 0, 1, 2 },
    { 8, 0, 0xFD, 3 },
};

u8* D_8010C084[2] = { D_8010C064[0], D_8010C074[0] };

void (*D_8010C08C[])(struct EffectObj*) = {
    func_800BDEA4,
    func_800BDF20,
};
