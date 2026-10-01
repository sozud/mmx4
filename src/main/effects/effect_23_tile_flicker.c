// EffectObj, effect_object_update_funcs[23]
// 800BAA30..800BABA8
#include "common.h"

u8 D_8010BE44[3][4] = {
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 0xFE, 3 },
};

u8 D_8010BE50[3][4] = {
    { 2, 0, 1, 4 },
    { 2, 0, 1, 5 },
    { 2, 0, 0xFE, 6 },
};

u8* tile_flicker_scripts[2] = { D_8010BE44[0], D_8010BE50[0] };

void tile_flicker_update(struct EffectObj* self)
{
    tile_flicker_state_funcs[self->state](self);
}

void tile_flicker_init(struct EffectObj* self)
{
    self->ext.effect_23.unk14 = 0;
    if (self->unk2 != 0) {
        self->ext.effect_23.palette_source.bytes = tile_flicker_scripts[1];
    } else {
        self->ext.effect_23.palette_source.bytes = tile_flicker_scripts[0];
    }
    self->ext.effect_23.palette.fields.timer = self->ext.effect_23.palette_source.bytes[0];
    self->ext.effect_23.palette.fields.unk1 = self->ext.effect_23.palette_source.bytes[1];
    self->ext.effect_23.palette.fields.step = self->ext.effect_23.palette_source.bytes[2];
    self->ext.effect_23.palette.fields.id = self->ext.effect_23.palette_source.bytes[3];
    self->state++;
}

void tile_flicker_main(struct EffectObj* self)
{
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        if (engine_obj.character_state.bytes[0] == 0) {
            tile_flicker_step(self);
        }
    } else {
        despawn_object(OBJECT_HEADER(self));
    }
}

void tile_flicker_step(struct EffectObj* self)
{
    s32* entry;
    s8 timer;

    timer = self->ext.effect_23.palette.fields.timer - 1;
    self->ext.effect_23.palette.fields.timer = timer;
    if (timer == 0) {
        self->ext.effect_23.palette_source.words += self->ext.effect_23.palette.fields.step;
        self->ext.effect_23.palette.packed = *self->ext.effect_23.palette_source.words;
        refresh_visible_tile_effect(self->ext.effect_23.palette.fields.id,
            self->x_pos.i.hi - 0x40, self->y_pos.i.hi);
    }
}

void (*tile_flicker_state_funcs[])(struct EffectObj*) = {
    tile_flicker_init,
    tile_flicker_main,
};
