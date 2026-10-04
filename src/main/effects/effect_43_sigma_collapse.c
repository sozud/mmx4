// EffectObj, effect_object_update_funcs[43]
// 800BE57C..800BE83C
#include "common.h"

void sigma_collapse_init(struct EffectObj* self)
{
    if (self->unk2 == 0) {
        self->state = 1;
    } else {
        self->state = 2;
    }
}

void sigma_collapse_debris_start(struct EffectObj* self)
{
    self->ext.effect_9.transition_timer = 1;
    self->ext.effect_9.direction = (D_801406A8[func_8002938C(0xA4)] >> 7);
    self->unk5++;
}

void sigma_collapse_debris_drop(struct EffectObj* self)
{
    struct MiscObj* misc;

    if (D_80171EA8 == 0) {
        self->ext.effect_9.transition_timer -= 1;
        if (!(self->ext.effect_9.transition_timer & 0xFFFF)) {
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->active = 0x41;
                misc->id = 0x39;
                misc->unk2 = ((u32)get_random() & 0xFF) % 6;
                misc->unk40 = self->ext.effect_16.saved_background_2A;
            }
            func_8001540C(5, 0, NULL);
            start_screen_shake_y(5, 2, 1);
            self->ext.effect_9.transition_timer = 5;
        }
    } else {
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

void sigma_collapse_debris(struct EffectObj* self)
{
    sigma_collapse_debris_funcs[self->unk5](self);
}

void sigma_collapse_rumble_start(struct EffectObj* self)
{
    self->ext.effect_43.unk14 = 1;
    self->ext.effect_43.unk16 = 1;
    self->unk5++;
}

void sigma_collapse_rumble_shake(struct EffectObj* self)
{
    if (--(&self->ext.effect_43)->unk14 == 0) {
        func_8001540C(5, 0, NULL);
        start_screen_shake_x(0xA, 2, 1);
        self->ext.effect_43.unk14 = 0xA;
    }

    if (--(&self->ext.effect_43)->unk16 == 0) {
        func_8001540C(0, 0x13, NULL);
        self->ext.effect_43.unk16 = 0x28;
    }
}

void sigma_collapse_rumble(struct EffectObj* self)
{
    sigma_collapse_rumble_funcs[self->unk5](self);
}

void sigma_collapse_update(struct EffectObj* self)
{
    sigma_collapse_state_funcs[self->state](self);
}

void (*sigma_collapse_debris_funcs[2])(struct EffectObj*) = {
    sigma_collapse_debris_start,
    sigma_collapse_debris_drop,
};

void (*sigma_collapse_rumble_funcs[2])(struct EffectObj*) = {
    sigma_collapse_rumble_start,
    sigma_collapse_rumble_shake,
};

void (*sigma_collapse_state_funcs[])(struct EffectObj*) = {
    sigma_collapse_init,
    sigma_collapse_debris,
    sigma_collapse_rumble,
};
