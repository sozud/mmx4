// EffectObj, effect_object_update_funcs[32]
// 800BC518..800BC748
#include "common.h"

void func_800BC518(struct EffectObj* arg0)
{
    D_8010BF90[arg0->state](arg0);
}

void func_800BC554(struct EffectObj* arg0)
{
    arg0->ext.effect_32.unk15 = 0;
    arg0->state++;
}

void func_800BC568(struct EffectObj* arg0)
{
    func_800BC63C();
    if (arg0->ext.effect_32.unk15 != 0) {
        func_800BC5D4(arg0);
    }
    if ((arg0->ext.effect_32.palette.fields.step == 0) && (func_8002B160(BASE_OBJECT(arg0)) == 1)) {
        func_8002B0C8(OBJECT_HEADER(arg0));
    }
}

void func_800BC5D4(struct EffectObj* arg0)
{
    s32* entry;
    s8 timer;

    timer = arg0->ext.effect_32.palette.fields.timer - 1;
    arg0->ext.effect_32.palette.fields.timer = timer;
    if (timer == 0) {
        entry = arg0->ext.effect_32.palette_source.words + arg0->ext.effect_32.palette.fields.step;
        arg0->ext.effect_32.palette_source.words = entry;
        arg0->ext.effect_32.palette.packed = *entry;
        func_800DABE4(arg0->ext.effect_32.palette.fields.id,
            arg0->x_pos.i.hi - 0x30, arg0->y_pos.i.hi - 0x30);
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_32", func_800BC63C);

void func_800BC6FC(struct EffectObj* arg0, s32 arg1)
{
    arg0->ext.effect_32.palette_source.bytes = D_8010BF88[arg1 & 0xFF];
    arg0->ext.effect_32.palette.fields.timer = arg0->ext.effect_32.palette_source.bytes[0];
    arg0->ext.effect_32.palette.fields.unk1 = arg0->ext.effect_32.palette_source.bytes[1];
    arg0->ext.effect_32.palette.fields.step = arg0->ext.effect_32.palette_source.bytes[2];
    arg0->ext.effect_32.palette.fields.id = arg0->ext.effect_32.palette_source.bytes[3];
}

void (*D_8010BF90[])(struct EffectObj*) = {
    func_800BC554,
    func_800BC568,
};
