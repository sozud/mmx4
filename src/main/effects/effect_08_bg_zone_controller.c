// EffectObj, effect_object_update_funcs[8]
// 800B7078..800B75C8
#include "common.h"

void bg_zone_controller_update(struct EffectObj* self)
{
    bg_zone_controller_state_funcs[self->state](self);
}

void bg_zone_controller_init(struct EffectObj* self)
{
    self->unk5 = 4;
    self->ext.unk_effect.unk14 = 5;
    self->state++;
    bg_zone_controller_main(self);
}

void bg_zone_controller_main(struct EffectObj* self)
{
    self->ext.unk_effect.unk15 = self->ext.unk_effect.unk14;
    bg_zone_controller_update_zone(self);
    bg_zone_controller_zone_funcs[self->unk5](self);
}

void bg_zone_controller_zone_0(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_zone_0_enter(self);
    } else {
        bg_zone_controller_zone_0_scroll(self);
    }
}

void bg_zone_controller_zone_0_enter(struct EffectObj* self)
{
    self->unk6++;
    background_objects[0].unk4 = 2;
    self->ext.effect_8.unk16 = 0;
    self->ext.effect_8.unk18 = 0;
}

void bg_zone_controller_zone_0_scroll(struct EffectObj* self)
{
    s32 t;

    if (background_objects[0].unk14.val != background_objects[0].x_pos.val) {
        self->ext.effect_8.unk18 = background_objects[0].x_pos.i.hi - background_objects[0].unk14.i.hi;
        if (self->ext.effect_8.unk18 >= 0) {
            if (self->ext.effect_8.unk18 >= 8) {
                self->ext.effect_8.unk18 = 8;
            }
        } else {
            if (self->ext.effect_8.unk18 < -8) {
                self->ext.effect_8.unk18 = -8;
            }
        }
        self->ext.effect_8.unk17 += self->ext.effect_8.unk18;
        if (self->ext.effect_8.unk17 >= 0) {
            if (self->ext.effect_8.unk17 < 8) {
                return;
            }
            if (++self->ext.effect_8.unk16 > 2) {
                self->ext.effect_8.unk16 = 0;
            }
        } else {
            if (self->ext.effect_8.unk17 > -8) {
                return;
            }
            if (--self->ext.effect_8.unk16 < 0) {
                self->ext.effect_8.unk16 = 2;
            }
        }
        t = self->ext.effect_8.unk16;
        background_objects[1].unk4C = 1;
        background_objects[1].x_pos.i.hi = t << 9;
        self->ext.effect_8.unk17 = 0;
    }
}

void bg_zone_controller_zone_1(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_zone_1_enter(self);
    } else {
        bg_zone_controller_zone_1_done(self);
    }
}

void bg_zone_controller_zone_1_enter(struct EffectObj* self)
{
    self->unk6++;
}

void bg_zone_controller_zone_1_done(struct EffectObj* self)
{
    self->unk5 = 5;
    self->unk6 = 0;
}

void bg_zone_controller_zone_2(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_zone_2_enter(self);
    } else {
        bg_zone_controller_zone_2_wait(self);
    }
}

void bg_zone_controller_zone_2_enter(struct EffectObj* self)
{
    background_objects[1].unk4 = 1;
    background_objects[2].unk4 = 3;
    self->unk6++;
}

void bg_zone_controller_zone_2_wait(struct EffectObj* self)
{
    if (g_Player.x_pos.i.hi >= 0xDD0) {
        engine_obj.checkpoint = 2;
        engine_obj.unkF = -0x40;
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void bg_zone_controller_zone_3(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_zone_3_enter(self);
    } else {
        bg_zone_controller_zone_3_wait(self);
    }
}

void bg_zone_controller_zone_3_enter(struct EffectObj* self)
{
    background_objects[1].unk4 = 6;
    background_objects[2].unk4 = 1;
    self->unk6++;
}

void bg_zone_controller_zone_3_wait(struct EffectObj* self)
{
    if (g_Player.x_pos.i.hi <= 0x1708) {
        engine_obj.checkpoint = 3;
        engine_obj.unkF = -0x40;
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void bg_zone_controller_zone_4(struct EffectObj* self)
{
    if (self->unk6 == 0) {
        bg_zone_controller_zone_4_enter(self);
    } else {
        bg_zone_controller_zone_4_wait(self);
    }
}

void bg_zone_controller_zone_4_enter(struct EffectObj* self)
{
    background_objects[1].unk4 = 1;
    background_objects[2].unk4 = 3;
    self->unk6++;
}

void bg_zone_controller_zone_4_wait(struct EffectObj* self)
{
    if (g_Player.x_pos.i.hi <= 0x112C) {
        engine_obj.unkF = 0x40;
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void bg_zone_controller_idle(struct EffectObj* self)
{
}

void bg_zone_controller_update_zone(struct EffectObj* self)
{
    s8 value;

    value = 0;
    for (;;) {
        if ((g_Player.x_pos.i.hi - bg_zone_controller_zone_bounds[value]) >= 0) {
            if ((value = value + 1) < 3) {
                continue;
            }
        }
        break;
    }
    if ((value == 2) && (g_Player.y_pos.i.hi >= 0x128)) {
        value = 4;
    }
    self->ext.unk_effect.unk14 = value;
    if (value != self->ext.unk_effect.unk15) {
        self->unk5 = value;
        self->unk6 = 0;
    }
}

s16 bg_zone_controller_zone_bounds[4] = { 0x0760, 0x0808, 0x1700, 0 };

void (*bg_zone_controller_state_funcs[])(struct EffectObj*) = {
    bg_zone_controller_init,
    bg_zone_controller_main,
};

void (*bg_zone_controller_zone_funcs[6])(struct EffectObj*) = {
    bg_zone_controller_zone_0,
    bg_zone_controller_zone_1,
    bg_zone_controller_zone_2,
    bg_zone_controller_zone_3,
    bg_zone_controller_zone_4,
    bg_zone_controller_idle,
};
