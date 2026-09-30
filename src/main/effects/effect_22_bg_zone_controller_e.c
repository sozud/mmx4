// EffectObj, effect_object_update_funcs[22]
// 800BA57C..800BAA30
#include "common.h"

void bg_zone_controller_e_update(struct EffectObj* self)
{
    bg_zone_controller_e_state_funcs[self->state](self);
}

void bg_zone_controller_e_init(struct EffectObj* self)
{
    self->unk5 = 2;
    self->ext.effect_22.unk14 = 5;
    self->state++;
    bg_zone_controller_e_main(self);
}

void bg_zone_controller_e_main(struct EffectObj* self)
{
    self->ext.effect_22.unk15 = self->ext.effect_22.unk14;
    bg_zone_controller_e_update_zone(self);
    bg_zone_controller_e_zone_funcs[self->unk5](self);
}

void bg_zone_controller_e_zone_0(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_e_zone_0_enter(self);
    } else {
        bg_zone_controller_e_zone_0_scroll(self);
    }
}

void bg_zone_controller_e_zone_0_enter(struct EffectObj* self)
{
    self->unk6++;
    background_objects[0].unk4 = 2;
    self->ext.effect_22.unk16 = 0;
    self->ext.effect_22.unk18 = 0;
}

void bg_zone_controller_e_zone_0_scroll(struct EffectObj* self)
{
    s16 diff;
    s8 sum;
    s32 t;

    if (background_objects[0].unk14.val != background_objects[0].x_pos.val) {
        diff = background_objects[0].x_pos.i.hi - background_objects[0].unk14.i.hi;
        self->ext.effect_22.unk18 = diff;
        if (diff > -1) {
            if (diff >= 8) {
                self->ext.effect_22.unk18 = 8;
            }
        } else {
            if (diff < -8) {
                self->ext.effect_22.unk18 = -8;
            }
        }

        sum = self->ext.effect_22.unk17 + self->ext.effect_22.unk18;
        self->ext.effect_22.unk17 = sum;
        if ((s8)sum >= 0) {
            if ((s8)sum < 8) {
                return;
            }
            if (++self->ext.effect_22.unk16 > 2) {
                self->ext.effect_22.unk16 = 0;
            }
        } else {
            if ((s8)sum > -8) {
                return;
            }
            if (--self->ext.effect_22.unk16 < 0) {
                self->ext.effect_22.unk16 = 2;
            }
        }
        t = self->ext.effect_22.unk16;
        background_objects[1].unk4C = 1;
        background_objects[1].x_pos.i.hi = t << 9;
        self->ext.effect_22.unk17 = 0;
    }
}

void bg_zone_controller_e_zone_1(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_e_zone_1_enter(self);
    } else {
        bg_zone_controller_e_zone_1_done(self);
    }
}

void bg_zone_controller_e_zone_1_enter(struct EffectObj* self)
{
    self->unk6++;
}

void bg_zone_controller_e_zone_1_done(struct EffectObj* self)
{
    self->unk5 = 5;
    self->unk6 = 0;
}

void bg_zone_controller_e_zone_2(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_e_zone_2_enter(self);
    } else {
        bg_zone_controller_e_zone_2_wait(self);
    }
}

void bg_zone_controller_e_zone_2_enter(struct EffectObj* self)
{
    background_objects[1].unk4 = 1;
    background_objects[2].unk4 = 3;
    self->unk6++;
}

void bg_zone_controller_e_zone_2_wait(struct EffectObj* self)
{
    if (g_Player.x_pos.i.hi >= 0xFE0) {
        engine_obj.checkpoint = 2;
        engine_obj.unkF = -0x40;
    }
}

void bg_zone_controller_e_zone_3(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_e_zone_3_enter(self);
    } else {
        bg_zone_controller_e_zone_3_done(self);
    }
}

void bg_zone_controller_e_zone_3_enter(struct EffectObj* self)
{
    background_objects[1].unk4 = 1;
    background_objects[2].unk4 = 3;
    self->unk6++;
}

void bg_zone_controller_e_zone_3_done(struct EffectObj* self)
{
    self->unk5 = 5;
    self->unk6 = 0;
}

void bg_zone_controller_e_zone_4(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_e_zone_4_enter(self);
    } else {
        bg_zone_controller_e_zone_4_done(self);
    }
}

void bg_zone_controller_e_zone_4_enter(struct EffectObj* self)
{
    background_objects[1].unk4 = 1;
    self->unk6++;
}

void bg_zone_controller_e_zone_4_done(struct EffectObj* self)
{
    self->unk5 = 5;
    self->unk6 = 0;
}

void bg_zone_controller_e_idle(struct EffectObj* self)
{
}

void bg_zone_controller_e_update_zone(struct EffectObj* self)
{
    s8 offset = 0;
    s16 player_x = g_Player.x_pos.i.hi;
    while (1) {
        if (player_x - bg_zone_controller_e_zone_bounds[offset] < 0) {
            break;
        }
        offset++;
        if (offset >= 3) {
            break;
        }
    }
    self->ext.effect_22.unk14 = offset;
    if (offset != self->ext.effect_22.unk15) {
        self->unk5 = offset;
        self->unk6 = 0;
    }
}

s16 bg_zone_controller_e_zone_bounds[4] = { 0x0960, 0x0A08, 0x1700, 0 };

void (*bg_zone_controller_e_state_funcs[])(struct EffectObj*) = {
    bg_zone_controller_e_init,
    bg_zone_controller_e_main,
};

void (*bg_zone_controller_e_zone_funcs[6])(struct EffectObj*) = {
    bg_zone_controller_e_zone_0,
    bg_zone_controller_e_zone_1,
    bg_zone_controller_e_zone_2,
    bg_zone_controller_e_zone_3,
    bg_zone_controller_e_zone_4,
    bg_zone_controller_e_idle,
};

extern u8 D_8010BE44[3][4];

extern u8 D_8010BE50[3][4];

extern u8* tile_flicker_scripts[2];
