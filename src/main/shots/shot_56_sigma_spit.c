// ShotObj, shot_object_update_funcs[56]
// 800ADF30..800AE450
#include "common.h"
#include "main/shots/shot_56_sigma_spit.h"
#include "main/object_motion.h"
#include "main/1E1BC.h"
#include "main/collision.h"
#include "main/objects.h"
#include "main/collision_bounds.h"
#include "main/55C4.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/55C4.h"
#include "main/collision_bounds.h"
#endif

// sigma_spit_step_funcs
extern void (*sigma_spit_step_funcs[])(struct ShotObj*);

void sigma_spit_idle(struct ShotObj*);
void sigma_spit_return(struct ShotObj*);
void sigma_spit_fall(struct ShotObj*);

// sigma_spit_state_funcs
extern void (*sigma_spit_state_funcs[])(struct ShotObj*);

void sigma_spit_main(struct ShotObj*);
void sigma_spit_despawn(struct ShotObj*);

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

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800ADF30(struct ShotObj* self);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800ADF30(struct ShotObj* self)
{
    struct WeaponObj* owner = self->unk7C;
    u32 frame;

    self->unk40 = owner->unk40;
    self->animation_table = owner->animation_table;
    self->unk3C = owner->unk3C;
    self->unk68 = NULL;
    self->unk42 = owner->unk42 & 0x7FFF;
    frame = get_random() & 3;
    set_animation_frame(ANIMATED_OBJECT(self), 0x15, frame);
    self->unk58.animation_steps = D_80105FF0;
    self->unk54 = (const u8*)sigma_spit_boxes[frame * 2];
    self->unk50.data = (const u8*)sigma_spit_boxes[frame * 2 + 1];
    self->unk16 = 0x20;
    self->unk15 = 0;
    self->bg_offset = owner->bg_offset;
    if (self->unk2 == 0) {
        self->unk5 = 2;
        self->unk5C = 3;
        self->unk60 = 6;
        switch (get_random() & 3) {
        case 0:
            self->x_pos.u.hi = background_objects[0].x_pos.u.hi + (get_random() & 0xFF);
            self->y_pos.u.hi = background_objects[0].y_pos.u.hi - 0x20;
            break;
        case 1:
            self->x_pos.u.hi = background_objects[0].x_pos.u.hi + 0x160;
            self->y_pos.u.hi = background_objects[0].y_pos.u.hi + (get_random() & 0xFF);
            break;
        case 2:
            self->x_pos.u.hi = background_objects[0].x_pos.u.hi + (get_random() & 0xFF);
            self->y_pos.u.hi = background_objects[0].y_pos.u.hi + 0x110;
            break;
        case 3:
            self->x_pos.u.hi = background_objects[0].x_pos.u.hi - 0x20;
            self->y_pos.u.hi = background_objects[0].y_pos.u.hi + (get_random() & 0xFF);
            break;
        }
    } else {
        self->unk5 = 3;
        set_velocity_from_angle(MOVING_OBJECT(self), (get_random() & 0xFF) % 7 + 1);
        self->unk2C = 0x4200;
        self->timer = 0x1E;
        self->unk60 = 6;
        self->unk28 = 0;
        self->unk5C = 3;
        self->x_vel.val = (u32)self->x_vel.val * 8;
        self->y_vel.val = (u32)self->y_vel.val * 10;
    }
    self->state++;
    update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_56_sigma_spit", func_800ADF30);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_56_sigma_spit", sigma_spit_return);
#else
void sigma_spit_return(struct ShotObj* self)
{
    struct WeaponObj* owner;

    owner = self->unk7C;
    set_velocity_from_angle(MOVING_OBJECT(self), (u8)(self->unk8C.byte = angle_to_point(OBJECT_HEADER(self), owner->x_pos.val + FIXED(16), owner->y_pos.val + FIXED(16))));
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
#endif

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
    enemy_hit_reaction(MAIN_OBJECT(self));
}

void sigma_spit_idle(struct ShotObj* self)
{
}

void sigma_spit_main(struct ShotObj* self)
{
    s32 hit;

    hit = func_8002DD04(MAIN_OBJECT(self));
    if (hit < 0) {
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
