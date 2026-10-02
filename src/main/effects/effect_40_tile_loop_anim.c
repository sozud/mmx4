// EffectObj, effect_object_update_funcs[40]
// 800BE038..800BE184
#include "common.h"

void tile_loop_anim_update(struct EffectObj* self)
{
    tile_loop_anim_state_funcs[self->state](self);
}

void tile_loop_anim_init(struct EffectObj* self)
{
    u8* temp_v0;

    self->ext.effect_40.unk14 = 1;
    self->y_pos.i.hi = 0x210;
    self->ext.effect_40.palette_source.bytes = tile_loop_anim_scripts[self->unk2];
    self->ext.effect_40.palette.fields.timer = *self->ext.effect_40.palette_source.bytes;
    self->ext.effect_40.palette.fields.unk1 = self->ext.effect_40.palette_source.bytes[1];
    self->ext.effect_40.palette.fields.step = self->ext.effect_40.palette_source.bytes[2];
    self->ext.effect_40.palette.fields.id = self->ext.effect_40.palette_source.bytes[3];
    self->state = (u8)self->state + 1;
}

void tile_loop_anim_step(struct EffectObj* arg0);

void tile_loop_anim_main(struct EffectObj* self)
{
    tile_loop_anim_step(self);
}

void tile_loop_anim_step(struct EffectObj* self)
{
    s8 timer;

    timer = self->ext.effect_40.palette.fields.timer - 1;
    self->ext.effect_40.palette.fields.timer = timer;
    if (timer == 0) {
        self->ext.effect_40.palette_source.words += self->ext.effect_40.palette.fields.step;
        self->ext.effect_40.palette.packed = *self->ext.effect_40.palette_source.words;
        apply_tile_effect(self->ext.effect_40.palette.fields.id,
            self->x_pos.i.hi - tile_loop_anim_offsets[self->unk2][0],
            self->y_pos.i.hi - tile_loop_anim_offsets[self->unk2][1]);
    }
}

u8 tile_loop_anim_script_0[6][4] = {
    { 9, 0, 1, 0 },
    { 9, 0, 1, 1 },
    { 9, 0, 1, 2 },
    { 0x40, 0, 1, 3 },
    { 9, 0, 1, 4 },
    { 9, 0, 0xFB, 5 },
};

u8 tile_loop_anim_script_1[6][4] = {
    { 0x40, 0, 1, 6 },
    { 9, 0, 1, 7 },
    { 9, 0, 1, 8 },
    { 9, 0, 1, 9 },
    { 9, 0, 1, 0x0A },
    { 9, 0, 0xFB, 0x0B },
};

s16 tile_loop_anim_offsets[2][2] = {
    { 0x30, 0x20 },
    { 0x40, 0x30 },
};

u8* tile_loop_anim_scripts[2] = { tile_loop_anim_script_0[0], tile_loop_anim_script_1[0] };

void (*tile_loop_anim_state_funcs[])(struct EffectObj*) = {
    tile_loop_anim_init,
    tile_loop_anim_main,
};
