// EffectObj, effect_object_update_funcs[41]
// 800BE184..800BE2C4
#include "common.h"

void tile_blink_anim_update(struct EffectObj* self)
{
    tile_blink_anim_state_funcs[self->state](self);
}

void tile_blink_anim_init(struct EffectObj* self)
{
    u8* palette;

    self->ext.effect_41.unk14 = 1;
    palette = tile_blink_anim_scripts[0];
    self->ext.effect_41.palette_source.bytes = palette;
    self->ext.effect_41.palette.fields.timer = palette[0];
    self->ext.effect_41.palette.fields.unk1 = self->ext.effect_41.palette_source.bytes[1];
    self->ext.effect_41.palette.fields.step = self->ext.effect_41.palette_source.bytes[2];
    self->ext.effect_41.palette.fields.id = self->ext.effect_41.palette_source.bytes[3];
    self->state = (u8)self->state + 1;
}

void tile_blink_anim_main(struct EffectObj* self)
{
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        tile_blink_anim_step(self);
        return;
    }

    despawn_object(OBJECT_HEADER(self));
}

void tile_blink_anim_step(struct EffectObj* self)
{
    s8 timer;
    s32* frame;

    timer = self->ext.effect_41.palette.fields.timer - 1;
    self->ext.effect_41.palette.fields.timer = timer;
    if (timer != 0) {
        return;
    }

    frame = self->ext.effect_41.palette_source.words + self->ext.effect_41.palette.fields.step;
    self->ext.effect_41.palette_source.words = frame;
    self->ext.effect_41.palette.packed = *frame;
    refresh_visible_tile_effect(self->ext.effect_41.palette.fields.id,
        self->x_pos.i.hi - 0x10, self->y_pos.i.hi - 0x10);
}

u8 tile_blink_anim_script_data[6][4] = {
    { 0x0E, 0, 1, 0 },
    { 0x0E, 0, 1, 1 },
    { 0x0E, 0, 1, 2 },
    { 0x0E, 0, 1, 3 },
    { 0x0E, 0, 1, 4 },
    { 0x0E, 0, 0xFB, 5 },
};

u8* tile_blink_anim_scripts[1] = { tile_blink_anim_script_data[0] };

void (*tile_blink_anim_state_funcs[])(struct EffectObj*) = {
    tile_blink_anim_init,
    tile_blink_anim_main,
};
