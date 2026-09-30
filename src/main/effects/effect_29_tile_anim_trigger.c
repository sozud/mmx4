// EffectObj, effect_object_update_funcs[29]
// 800BC144..800BC2E0
#include "common.h"

struct Effect28AnimationStep tile_anim_script_0[3] = {
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, -2, 2 },
};

struct Effect28AnimationStep tile_anim_script_1[3] = {
    { 2, 0, 1, 3 },
    { 2, 0, 1, 4 },
    { 2, 0, -2, 5 },
};

struct Effect28AnimationStep tile_anim_script_2[4] = {
    { 4, 0, 1, 6 },
    { 4, 0, 1, 7 },
    { 4, 0, 1, 8 },
    { 4, 0, -3, 9 },
};

struct Effect28AnimationStep* tile_anim_scripts[3] = {
    tile_anim_script_0,
    tile_anim_script_1,
    tile_anim_script_2,
};


void tile_anim_trigger_update(struct EffectObj* self)
{
    tile_anim_trigger_state_funcs[self->state](self);
}

void tile_anim_trigger_init(struct EffectObj* self)
{
    struct Effect28AnimationStep* temp_v0;
    u8 temp_v1;

    self->ext.effect_29.unk14 = 2;
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        temp_v0 = tile_anim_scripts[self->unk2];
        self->ext.effect_29.palette_source.animation = temp_v0;
        self->ext.effect_29.palette.fields.timer = temp_v0->timer;
        self->ext.effect_29.palette.fields.unk1 = self->ext.effect_29.palette_source.animation->unused;
        self->ext.effect_29.palette.fields.step = self->ext.effect_29.palette_source.animation->frame_step;
        temp_v1 = self->ext.effect_29.palette_source.animation->frame;
        self->state = (u8)self->state + 1;
        self->ext.effect_29.palette.fields.id = temp_v1;
    }
}

void tile_anim_trigger_main(struct EffectObj* self)
{
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        tile_anim_trigger_step(self);
        return;
    }
    despawn_object(OBJECT_HEADER(self));
}

void tile_anim_trigger_step(struct EffectObj* self)
{
    s8 timer;
    s32* source;

    timer = self->ext.effect_29.palette.fields.timer - 1;
    self->ext.effect_29.palette.fields.timer = timer;
    if (timer == 0) {
        source = self->ext.effect_29.palette_source.words + self->ext.effect_29.palette.fields.step;
        self->ext.effect_29.palette_source.words = source;
        self->ext.effect_29.palette.packed = *source;
        refresh_visible_tile_effect(self->ext.effect_29.palette.fields.id,
            self->x_pos.i.hi - tile_anim_trigger_offsets[self->unk2][0],
            self->y_pos.i.hi - tile_anim_trigger_offsets[self->unk2][1]);
    }
}

void (*tile_anim_trigger_state_funcs[])(struct EffectObj*) = {
    tile_anim_trigger_init,
    tile_anim_trigger_main,
};

u8 tile_anim_trigger_offsets[4][2] = {
    { 0x28, 0x18 },
    { 0x40, 0x20 },
    { 0x10, 0x40 },
    { 0, 0 },
};

struct Effect29AnimationStep {
    u8 timer;
    u8 unused;
    s8 frame_step;
    u8 position;
};

extern struct Effect29AnimationStep tile_anim_trigger_open_steps[9];

extern struct Effect29AnimationStep tile_anim_trigger_close_steps[9];

extern u8* tile_anim_trigger_scripts[2];
