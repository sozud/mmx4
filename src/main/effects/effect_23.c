// EffectObj, effect_object_update_funcs[23]
// 800BAA30..800BABA8
#include "common.h"

void func_800BAA30(struct EffectObj* arg0)
{
    D_8010BE64[arg0->state](arg0);
}

void func_800BAA6C(struct EffectObj* arg0)
{
    arg0->ext.effect_23.unk14 = 0;
    if (arg0->unk2 != 0) {
        arg0->ext.effect_23.palette_source.bytes = D_8010BE5C[1];
    } else {
        arg0->ext.effect_23.palette_source.bytes = D_8010BE5C[0];
    }
    arg0->ext.effect_23.palette.fields.timer = arg0->ext.effect_23.palette_source.bytes[0];
    arg0->ext.effect_23.palette.fields.unk1 = arg0->ext.effect_23.palette_source.bytes[1];
    arg0->ext.effect_23.palette.fields.step = arg0->ext.effect_23.palette_source.bytes[2];
    arg0->ext.effect_23.palette.fields.id = arg0->ext.effect_23.palette_source.bytes[3];
    arg0->state++;
}

void func_800BAAE0(struct EffectObj* arg0)
{
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        if (engine_obj.character_state.bytes[0] == 0) {
            func_800BAB3C(arg0);
        }
    } else {
        func_8002B0C8(OBJECT_HEADER(arg0));
    }
}

void func_800BAB3C(struct EffectObj* arg0)
{
    s32* entry;
    s8 timer;

    timer = arg0->ext.effect_23.palette.fields.timer - 1;
    arg0->ext.effect_23.palette.fields.timer = timer;
    if (timer == 0) {
        entry = arg0->ext.effect_23.palette_source.words + arg0->ext.effect_23.palette.fields.step;
        arg0->ext.effect_23.palette_source.words = entry;
        arg0->ext.effect_23.palette.packed = *entry;
        func_800DA984(arg0->ext.effect_23.palette.fields.id,
            arg0->x_pos.i.hi - 0x40, arg0->y_pos.i.hi);
    }
}

void (*D_8010BE64[])(struct EffectObj*) = {
    func_800BAA6C,
    func_800BAAE0,
};
