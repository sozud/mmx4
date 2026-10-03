// EffectObj, effect_object_update_funcs[20]
// 800B9BD0..800B9EC0
#include "common.h"

void bg_zone_controller_d_update(struct EffectObj* self)
{
    bg_zone_controller_d_state_funcs[self->state](self);
}

void bg_zone_controller_d_init(struct EffectObj* self)
{
    self->unk5 = 2;
    self->ext.effect_20.unk14 = 3;
    self->state++;
    bg_zone_controller_d_main(self);
}

void bg_zone_controller_d_main(struct EffectObj* self)
{
    self->ext.effect_20.unk15 = self->ext.effect_20.unk14;
    bg_zone_controller_d_update_zone(self);
    bg_zone_controller_d_zone_funcs[self->unk5](self);
}

void bg_zone_controller_d_zone_0(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_d_zone_0_enter(self);
    } else {
        bg_zone_controller_d_zone_0_done(self);
    }
}

void bg_zone_controller_d_zone_0_enter(struct EffectObj* self)
{
    background_objects[0].unk2E = 0xC0;
    self->unk6++;
}

void bg_zone_controller_d_zone_0_done(struct EffectObj* self)
{
    self->unk5 = 3;
    self->unk6 = 0;
}

void bg_zone_controller_d_zone_1(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_d_zone_1_enter(self);
    } else {
        bg_zone_controller_d_zone_1_done(self);
    }
}

void bg_zone_controller_d_zone_1_enter(struct EffectObj* self)
{
    background_objects[0].unk2E = 0x90;
    self->unk6++;
}

void bg_zone_controller_d_zone_1_done(struct EffectObj* self)
{
    self->unk5 = 3;
    self->unk6 = 0;
}

void bg_zone_controller_d_zone_2(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_d_zone_2_enter(self);
    } else {
        bg_zone_controller_d_zone_2_done(self);
    }
}

void bg_zone_controller_d_zone_2_enter(struct EffectObj* self)
{
    self->unk6++;
}

void bg_zone_controller_d_zone_2_done(struct EffectObj* self)
{
    self->unk5 = 3;
    self->unk6 = 0;
}

void bg_zone_controller_d_idle(struct EffectObj* self)
{
}

void bg_zone_controller_d_update_zone(struct EffectObj* self)
{
    s8 offset = 0;
    s16 player_x = g_Player.x_pos.i.hi;
    while (1) {
        if (player_x - bg_zone_controller_d_zone_bounds[offset] < 0) {
            break;
        }
        offset++;
        if (offset >= 2) {
            break;
        }
    }
    self->ext.effect_20.unk14 = offset;
    if (offset != self->ext.effect_20.unk15) {
        self->unk5 = offset;
        self->unk6 = 0;
    }
}

// bg_zone_controller_d_unused
s32 func_800B9E54(struct Effect21SpawnRecord* record)
{
    s32 x = record->x - background_objects[g_Player.bg_offset].x_pos.u.hi;
    s32 y = record->y - background_objects[g_Player.bg_offset].y_pos.u.hi;

    if ((u16)(x + 0x280) < 0x640 && (u16)(y + 0x1E0) < 0x4B0) {
        return 1;
    }
    return 0;
}

s16 bg_zone_controller_d_zone_bounds[2] = { 0x0740, 0x0A00 };

void (*bg_zone_controller_d_state_funcs[])(struct EffectObj*) = {
    bg_zone_controller_d_init,
    bg_zone_controller_d_main,
};

void (*bg_zone_controller_d_zone_funcs[4])(struct EffectObj*) = {
    bg_zone_controller_d_zone_0,
    bg_zone_controller_d_zone_1,
    bg_zone_controller_d_zone_2,
    bg_zone_controller_d_idle,
};
