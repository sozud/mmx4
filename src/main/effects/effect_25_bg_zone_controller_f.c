// EffectObj, effect_object_update_funcs[25]
// 800BAF60..800BB1F0
#include "common.h"

s16 bg_zone_controller_f_zone_bounds[2] = { 0x0580, 0x0A40 };

void bg_zone_controller_f_update(struct EffectObj* self)
{
    bg_zone_controller_f_state_funcs[self->state](self);
}

void bg_zone_controller_f_init(struct EffectObj* self)
{
    self->unk5 = 2;
    self->ext.effect_25.unk14 = 3;
    self->state++;
    bg_zone_controller_f_main(self);
}

void bg_zone_controller_f_main(struct EffectObj* self)
{
    self->ext.effect_25.unk15 = self->ext.effect_25.unk14;
    bg_zone_controller_f_update_zone(self);
    bg_zone_controller_f_zone_funcs[self->unk5](self);
}

void bg_zone_controller_f_zone_0(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_f_zone_0_enter(self);
    } else {
        bg_zone_controller_f_zone_0_done(self);
    }
}

void bg_zone_controller_f_zone_0_enter(struct EffectObj* self)
{
    background_objects[0].unk2E = 0xC0;
    self->unk6++;
}

void bg_zone_controller_f_zone_0_done(struct EffectObj* self)
{
    self->unk5 = 3;
    self->unk6 = 0;
}

void bg_zone_controller_f_zone_1(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_f_zone_1_enter(self);
    } else {
        bg_zone_controller_f_zone_1_done(self);
    }
}

void bg_zone_controller_f_zone_1_enter(struct EffectObj* self)
{
    background_objects[0].unk2E = 0x80;
    self->unk6++;
}

void bg_zone_controller_f_zone_1_done(struct EffectObj* self)
{
    self->unk5 = 3;
    self->unk6 = 0;
}

void bg_zone_controller_f_zone_2(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_f_zone_2_enter(self);
    } else {
        bg_zone_controller_f_zone_2_done(self);
    }
}

void bg_zone_controller_f_zone_2_enter(struct EffectObj* self)
{
    background_objects[0].unk2E = 0xC0;
    self->unk6++;
}

void bg_zone_controller_f_zone_2_done(struct EffectObj* self)
{
    self->unk5 = 3;
    self->unk6 = 0;
}

void bg_zone_controller_f_idle(struct EffectObj* self)
{
}

void bg_zone_controller_f_update_zone(struct EffectObj* self)
{
    s8 offset = 0;
    s16 player_x = g_Player.x_pos.i.hi;
    while (1) {
        if (player_x - bg_zone_controller_f_zone_bounds[offset] < 0) {
            break;
        }
        offset++;
        if (offset >= 2) {
            break;
        }
    }
    self->ext.effect_25.unk14 = offset;
    if (offset != self->ext.effect_25.unk15) {
        self->unk5 = offset;
        self->unk6 = 0;
    }
}

void (*bg_zone_controller_f_state_funcs[])(struct EffectObj*) = {
    bg_zone_controller_f_init,
    bg_zone_controller_f_main,
};

void (*bg_zone_controller_f_zone_funcs[4])(struct EffectObj*) = {
    bg_zone_controller_f_zone_0,
    bg_zone_controller_f_zone_1,
    bg_zone_controller_f_zone_2,
    bg_zone_controller_f_idle,
};
