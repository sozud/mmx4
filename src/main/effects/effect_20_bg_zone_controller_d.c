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
    s16 player_x = g_Player.x_pos.i.hi;
    s8 offset = 0;
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
INCLUDE_ASM("main/nonmatchings/effects/effect_20_bg_zone_controller_d", func_800B9E54);

void (*bg_zone_controller_c_zone_funcs[4])(struct EffectObj*) = {
    bg_zone_controller_c_zone_0,
    bg_zone_controller_c_zone_1,
    bg_zone_controller_c_zone_2,
    bg_zone_controller_c_idle,
};

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
