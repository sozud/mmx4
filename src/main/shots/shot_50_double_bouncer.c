// ShotObj, shot_object_update_funcs[50]
// 800AA2FC..800AA5E0
#include "common.h"

void (*double_bouncer_step_funcs[])(struct ShotObj*) = {
    double_toss_land,
    func_800AA2FC,
    double_bouncer_bounce,
};

// double_bouncer_launch
INCLUDE_ASM("main/nonmatchings/shots/shot_50_double_bouncer", func_800AA2FC);

void double_bouncer_bounce(struct ShotObj* self)
{
    s32 velocity;

    velocity = self->x_vel.val;
    if (velocity < 0) {
        if (self->unk70 & 2) {
            self->x_vel.val = -velocity;
            if ((self->unk70 & 0xD) == 0xD) {
                self->unk84.value = 1;
            }
        }
    } else if (self->unk70 & 1) {
        self->x_vel.val = -velocity;
        if ((self->unk70 & 0xE) == 0xE) {
            self->unk84.value = 1;
        }
    }

    velocity = self->y_vel.val;
    if (velocity < 0) {
        if (self->unk70 & 8) {
            self->y_vel.val = -velocity;
            if ((self->unk70 & 0xC) == 0xC) {
                self->unk84.value = 1;
            }
        }
    } else if (self->unk70 & 4) {
        self->y_vel.val = -velocity;
        if ((self->unk70 & 0xC) == 0xC) {
            self->unk84.value = 1;
        }
    }

    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}

void double_bouncer_main(struct ShotObj* self)
{
    extern u8 double_ball_debris_0[];

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    double_bouncer_step_funcs[self->unk5](self);
    CollisionRelated(self);
    if (self->unk7C->state == 2 || self->unk84.value != 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, double_ball_debris_0, self);
        self->state = 2;
        self->on_screen = 0;
        return;
    }
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, double_ball_debris_0, self);
        self->state = 2;
        self->on_screen = 0;
        return;
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->state = 2;
    self->unk5 = 0;
    self->unk6 = 0;
    self->on_screen = 0;
}

void double_bouncer_update(struct ShotObj* self)
{
    double_bouncer_state_funcs[self->state](self);
}

void (*double_bouncer_state_funcs[])(struct ShotObj*) = {
    double_toss_init,
    double_bouncer_main,
    double_ball_despawn,
};
