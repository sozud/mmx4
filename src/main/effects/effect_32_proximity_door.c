// EffectObj, effect_object_update_funcs[32]
// 800BC518..800BC748
#include "common.h"

struct Effect29AnimationStep {
    u8 timer;
    u8 unused;
    s8 frame_step;
    u8 position;
};

struct Effect29AnimationStep tile_anim_trigger_open_steps[9] = {
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 3 },
    { 25, 0, 1, 4 },
    { 2, 0, 1, 5 },
    { 2, 0, 1, 6 },
    { 2, 0, 1, 7 },
    { 2, 0, 0, 8 },
};

struct Effect29AnimationStep tile_anim_trigger_close_steps[9] = {
    { 2, 0, 1, 8 },
    { 2, 0, 1, 7 },
    { 2, 0, 1, 6 },
    { 2, 0, 1, 5 },
    { 25, 0, 1, 4 },
    { 2, 0, 1, 3 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 1 },
    { 2, 0, 0, 0 },
};

u8* tile_anim_trigger_scripts[2] = {
    (u8*)tile_anim_trigger_open_steps,
    (u8*)tile_anim_trigger_close_steps,
};


void proximity_door_update(struct EffectObj* self)
{
    proximity_door_state_funcs[self->state](self);
}

void proximity_door_init(struct EffectObj* self)
{
    self->ext.effect_32.unk15 = 0;
    self->state++;
}

void proximity_door_main(struct EffectObj* self)
{
    proximity_door_check_player(self);
    if (self->ext.effect_32.unk15 != 0) {
        proximity_door_step(self);
    }
    if ((self->ext.effect_32.palette.fields.step == 0) && (func_8002B160(BASE_OBJECT(self)) == 1)) {
        despawn_object(OBJECT_HEADER(self));
    }
}

void proximity_door_step(struct EffectObj* self)
{
    s32* entry;
    s8 timer;

    timer = self->ext.effect_32.palette.fields.timer - 1;
    self->ext.effect_32.palette.fields.timer = timer;
    if (timer == 0) {
        entry = self->ext.effect_32.palette_source.words + self->ext.effect_32.palette.fields.step;
        self->ext.effect_32.palette_source.words = entry;
        self->ext.effect_32.palette.packed = *entry;
        apply_tile_effect(self->ext.effect_32.palette.fields.id,
            self->x_pos.i.hi - 0x30, self->y_pos.i.hi - 0x30);
    }
}

void proximity_door_check_player(struct EffectObj* self)
{
    s16 x_pos;
    s32 delta;

    x_pos = self->x_pos.i.hi;
    delta = g_Player.x_pos.i.hi - x_pos;
    if (delta >= 0 ? delta < 0x30 : (x_pos - g_Player.x_pos.i.hi) < 0x30) {
        if (self->ext.effect_32.unk15 != 1 && self->ext.effect_32.palette.fields.step == 0) {
            proximity_door_start_script(self, 0);
            self->ext.effect_32.unk15 = 1;
        }
    } else if (self->ext.effect_32.unk15 == 1 && self->ext.effect_32.palette.fields.step == 0) {
        proximity_door_start_script(self, 1);
        self->ext.effect_32.unk15 = -1;
    }
}

void proximity_door_start_script(struct EffectObj* self, s32 arg1)
{
    self->ext.effect_32.palette_source.bytes = tile_anim_trigger_scripts[arg1 & 0xFF];
    self->ext.effect_32.palette.fields.timer = self->ext.effect_32.palette_source.bytes[0];
    self->ext.effect_32.palette.fields.unk1 = self->ext.effect_32.palette_source.bytes[1];
    self->ext.effect_32.palette.fields.step = self->ext.effect_32.palette_source.bytes[2];
    self->ext.effect_32.palette.fields.id = self->ext.effect_32.palette_source.bytes[3];
}

void (*proximity_door_state_funcs[])(struct EffectObj*) = {
    proximity_door_init,
    proximity_door_main,
};
