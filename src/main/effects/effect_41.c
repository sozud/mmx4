// EffectObj, effect_object_update_funcs[41]
// 800BE184..800BE2C4
#include "common.h"

void func_800BE184(struct EffectObj* arg0)
{
    D_8010C0F8[arg0->state](arg0);
}

void func_800BE1C0(struct EffectObj* arg0)
{
    u8* palette;

    arg0->ext.effect_41.unk14 = 1;
    palette = D_8010C0F4[0];
    arg0->ext.effect_41.palette_source.bytes = palette;
    arg0->ext.effect_41.palette.fields.timer = palette[0];
    arg0->ext.effect_41.palette.fields.unk1 = arg0->ext.effect_41.palette_source.bytes[1];
    arg0->ext.effect_41.palette.fields.step = arg0->ext.effect_41.palette_source.bytes[2];
    arg0->ext.effect_41.palette.fields.id = arg0->ext.effect_41.palette_source.bytes[3];
    arg0->state = (u8)arg0->state + 1;
}

void func_800BE214(struct EffectObj* arg0)
{
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        func_800BE25C(arg0);
        return;
    }

    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_800BE25C(struct EffectObj* arg0)
{
    s8 timer;
    s32* frame;

    timer = arg0->ext.effect_41.palette.fields.timer - 1;
    arg0->ext.effect_41.palette.fields.timer = timer;
    if (timer != 0) {
        return;
    }

    frame = arg0->ext.effect_41.palette_source.words + arg0->ext.effect_41.palette.fields.step;
    arg0->ext.effect_41.palette_source.words = frame;
    arg0->ext.effect_41.palette.packed = *frame;
    func_800DA984(arg0->ext.effect_41.palette.fields.id,
        arg0->x_pos.i.hi - 0x10, arg0->y_pos.i.hi - 0x10);
}

u8 D_8010C0DC[6][4] = {
    { 0x0E, 0, 1, 0 },
    { 0x0E, 0, 1, 1 },
    { 0x0E, 0, 1, 2 },
    { 0x0E, 0, 1, 3 },
    { 0x0E, 0, 1, 4 },
    { 0x0E, 0, 0xFB, 5 },
};

u8* D_8010C0F4[1] = { D_8010C0DC[0] };

void (*D_8010C0F8[])(struct EffectObj*) = {
    func_800BE1C0,
    func_800BE214,
};
