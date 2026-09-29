// ShotObj, shot_object_update_funcs[56]
// 800ADF30..800AE450
#include "common.h"

s8 sigma_spit_box_data[8][4] = {
    { -13, -12, 28, 23 },
    { -6, -6, 15, 12 },
    { -8, -15, 22, 29 },
    { -19, -22, 40, 44 },
    { -7, -13, 15, 18 },
    { -8, -14, 18, 20 },
    { -8, -11, 16, 19 },
    { -12, -13, 24, 23 },
};

s8* sigma_spit_boxes[8] = {
    sigma_spit_box_data[0],
    sigma_spit_box_data[1],
    sigma_spit_box_data[2],
    sigma_spit_box_data[3],
    sigma_spit_box_data[4],
    sigma_spit_box_data[5],
    sigma_spit_box_data[6],
    sigma_spit_box_data[7],
};

void (*sigma_spit_step_funcs[])(struct ShotObj*) = {
    sigma_spit_hit,
    sigma_spit_idle,
    sigma_spit_return,
    sigma_spit_fall,
};

// sigma_spit_init
INCLUDE_ASM("main/nonmatchings/shots/shot_56_sigma_spit", func_800ADF30);

void sigma_spit_return(struct ShotObj* self)
{
    struct WeaponObj* owner;
    s8 angle;

    owner = self->unk7C;
    angle = angle_to_point(OBJECT_HEADER(self),
        owner->x_pos.val + FIXED(16), owner->y_pos.val + FIXED(16));
    self->unk8C.byte = angle;
    set_velocity_from_angle(MOVING_OBJECT(self), angle & 0xFF);
    self->x_vel.val *= (get_random() & 3) + 2;
    self->y_vel.val *= (get_random() & 3) + 2;
    move_object(MOVING_OBJECT(self));
    if ((self->unk8C.bytes[0] ^ angle_to_point(OBJECT_HEADER(self), owner->x_pos.val + FIXED(16), owner->y_pos.val + FIXED(16))) & 0x10) {
        self->state = 2;
        self->unk5 = 0;
        return;
    }
    update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
}

void sigma_spit_fall(struct ShotObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
    if (self->on_screen == 0) {
        self->state = 2;
        self->unk5 = 0;
    }
}

void sigma_spit_hit(struct ShotObj* self)
{
    enemy_hit_reaction(self);
}

void sigma_spit_idle(struct ShotObj* self)
{
}

void sigma_spit_main(struct ShotObj* self)
{
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        self->state = 2;
        self->unk5 = 0;
        spawn_explosion(self);
        return;
    }

    sigma_spit_step_funcs[self->unk5](self);
    CollisionRelated(self);
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x28, 0x28) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x28, 0x28);
        return;
    }
    self->state = 2;
}

void sigma_spit_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void sigma_spit_update(struct ShotObj* self)
{
    if (self->unk7C->unk94 != 0) {
        self->state = 2;
        self->unk5 = 0;
    }
    self->on_screen = 0;
    sigma_spit_state_funcs[self->state](self);
}

void (*sigma_spit_state_funcs[])(struct ShotObj*) = {
    func_800ADF30,
    sigma_spit_main,
    sigma_spit_despawn,
};
