// MiscObj, misc_object_update_funcs[5]
// 800C8FA8..800C91B0
#include "common.h"

void pod_effect_update(struct MiscObj* self)
{
    pod_effect_state_funcs[self->state](self);
}

void pod_effect_launch_init(struct MiscObj* self)
{
    set_animation(self, 0xF);
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = FIXED(8.25);
    self->unk2C = FIXED(0.375);
    move_object(MOVING_OBJECT(self));
    self->state = 1;
}

void pod_effect_launch(struct MiscObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->y_vel.val == 0 || *(s32*)self->ext.misc_5.owner == 0) {
        self->state = 2;
    }
    is_on_screen(BASE_OBJECT(self));
}

void pod_effect_launch_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void pod_effect_init(struct MiscObj* self)
{
    set_animation(self, self->ext.misc_5.animation);
    self->state = 4;
}

void pod_effect_animate(struct MiscObj* self)
{
    struct MainObj* owner;

    animate_object(ANIMATED_OBJECT(self));
    if (self->unk2 == 0) {
        if (self->animation_step.fields.event != 0) {
            self->state = 5;
        } else if (self->animation_step.fields.relative_step < 0) {
            self->state = 5;
        }
    } else {
        owner = self->ext.misc_5.owner;
        if ((owner->air_state != 0) || (owner->state > 1)) {
            self->state = 5;
        }
    }
    is_on_screen(BASE_OBJECT(self));
}

void pod_effect_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*pod_effect_state_funcs[6])(struct MiscObj*) = {
    pod_effect_launch_init,
    pod_effect_launch,
    pod_effect_launch_despawn,
    pod_effect_init,
    pod_effect_animate,
    pod_effect_despawn,
};

s8 pod_effect_offsets[8] = { -19, -14, 0x13, -14, 0x11, 0x10, -18, 0x0E };

u32 pod_effect_unused = 0;
