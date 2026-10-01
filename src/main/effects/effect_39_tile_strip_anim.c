// EffectObj, effect_object_update_funcs[39]
// 800BDE68..800BE038
#include "common.h"

void tile_strip_anim_update(struct EffectObj* self)
{
    tile_strip_anim_state_funcs[self->state](self);
}

void tile_strip_anim_init(struct EffectObj* self)
{
    u8* temp_v0;

    self->ext.effect_39.unk14 = 1;
    if (self->unk2 == 0) {
        self->x_pos.i.hi = 0x940;
        self->y_pos.i.hi = 0x2D0;
    }
    self->ext.effect_39.palette_source.bytes = tile_strip_anim_scripts[self->unk2];
    self->ext.effect_39.palette.fields.timer = self->ext.effect_39.palette_source.bytes[0];
    self->ext.effect_39.palette.fields.unk1 = self->ext.effect_39.palette_source.bytes[1];
    self->ext.effect_39.palette.fields.step = self->ext.effect_39.palette_source.bytes[2];
    self->ext.effect_39.palette.fields.id = self->ext.effect_39.palette_source.bytes[3];
    self->state = (u8)self->state + 1;
}

void tile_strip_anim_main(struct EffectObj* self)
{
    tile_strip_anim_step(self);
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/effects/effect_39_tile_strip_anim", tile_strip_anim_step);
#else
void tile_strip_anim_step(struct EffectObj* self)
{
    s8 temp_v0;
    struct EffectPaletteExt* ext = &self->ext.effect_39;

    temp_v0 = ext->palette.fields.timer - 1;
    ext->palette.fields.timer = temp_v0;
    if (temp_v0 != 0) {
        return;
    }

    ext->palette_source.words += ext->palette.fields.step;
    ext->palette.packed = *ext->palette_source.words;

    if (self->unk2 == 0) {
        tile_strip_anim_refresh_row(self);
        return;
    }

    refresh_visible_tile_effect(ext->palette.fields.id,
        self->x_pos.i.hi - 0x40, self->y_pos.i.hi - 0x20);
}
#endif

void tile_strip_anim_refresh_row(struct EffectObj* self)
{
    u16 x;
    s32 i;

    x = self->x_pos.u.hi;
    i = 0;
    do {
        refresh_visible_tile_effect(self->ext.effect_39.palette.fields.id, (s16)x - 0x40,
            self->y_pos.i.hi - 0x20);
        x += 0x80;
        i += 1;
    } while (i < 0x1A);
}

u8 tile_strip_anim_script_0[4][4] = {
    { 8, 0, 1, 3 },
    { 8, 0, 1, 4 },
    { 8, 0, 1, 5 },
    { 8, 0, 0xFD, 6 },
};

u8 tile_strip_anim_script_1[4][4] = {
    { 8, 0, 1, 0 },
    { 8, 0, 1, 1 },
    { 8, 0, 1, 2 },
    { 8, 0, 0xFD, 3 },
};

u8* tile_strip_anim_scripts[2] = { tile_strip_anim_script_0[0], tile_strip_anim_script_1[0] };

void (*tile_strip_anim_state_funcs[])(struct EffectObj*) = {
    tile_strip_anim_init,
    tile_strip_anim_main,
};
