// ShotObj, shot_object_update_funcs[43]
// 800A6960..800A6FCC
#include "common.h"
#include "main/objects.h"
#include "main/shots/shot_43_gunship_shot.h"
#include "main/object_motion.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"

// gunship_shot_state_funcs
extern void (*gunship_shot_state_funcs[])(struct ShotObj*);

void gunship_shot_bullet_fall(struct ShotObj*);
void gunship_shot_missile_fly(struct ShotObj*);

void gunship_shot_despawn(struct ShotObj*);
void gunship_shot_idle(struct ShotObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/collision_bounds.h"
#endif

extern u8 gunship_shot_bullet_hit_box[4];
extern u8 gunship_shot_missile_hit_box[4];
extern s32 gunship_shot_missile_speeds[2];

void gunship_shot_update(struct ShotObj* self)
{
    gunship_shot_state_funcs[self->state](self);
}

// gunship_shot_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A699C(struct ShotObj* arg0);
void func_800A6DF4(struct ShotObj* arg0);
extern u8 gunship_shot_bullet_hit_box[4];
extern u8 gunship_shot_missile_hit_box[4];
extern s32 gunship_shot_missile_speeds[2];
#endif

void func_800A699C(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;

    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk60 = 5;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk42 &= 0x7FFF;
    if (arg0->unk2 < 2) {
        if (arg0->unk2 == 0) {
            if (arg0->unk15 == 0) {
                arg0->x_pos.i.hi = owner->x_pos.i.hi - 0x45;
            } else {
                arg0->x_pos.i.hi = owner->x_pos.i.hi + 0x45;
            }
            arg0->y_pos.i.hi = owner->y_pos.i.hi - 0x1A;
        } else {
            if (arg0->unk15 == 0) {
                arg0->x_pos.i.hi = owner->x_pos.i.hi - 0x45;
            } else {
                arg0->x_pos.i.hi = owner->x_pos.i.hi + 0x45;
            }
            arg0->y_pos.i.hi = owner->y_pos.i.hi - 9;
        }
        arg0->x_vel.val = gunship_shot_missile_speeds[arg0->unk15 != 0 ? 1 : 0];
        arg0->unk50.data = gunship_shot_bullet_hit_box;
        arg0->unk58.collision_data = D_80106070;
        arg0->unk68 = NULL;
        arg0->unk54 = gunship_shot_bullet_hit_box;
        set_animation(arg0, 2);
        arg0->state = 1;
        arg0->unk60 = 4;
    } else {
        arg0->unk50.data = gunship_shot_missile_hit_box;
        arg0->unk58.animation_steps = D_80105FF0;
        arg0->unk68 = NULL;
        arg0->unk54 = gunship_shot_missile_hit_box;
        arg0->x_vel.val = -0x28000;
        arg0->y_vel.val = 0x28000;
        switch (arg0->unk2) {
        case 2:
            arg0->x_pos.i.hi = owner->x_pos.i.hi + 0x14;
            arg0->y_pos.i.hi = owner->y_pos.i.hi - 0x27;
            break;
        case 3:
            arg0->x_pos.i.hi = owner->x_pos.i.hi + 8;
            arg0->y_pos.i.hi = owner->y_pos.i.hi - 0x19;
            break;
        case 4:
            arg0->x_pos.i.hi = owner->x_pos.i.hi + 8;
            arg0->y_pos.i.hi = owner->y_pos.i.hi - 0x33;
            break;
        case 5:
            arg0->x_pos.i.hi = owner->x_pos.i.hi + 0x14;
            arg0->y_pos.i.hi = owner->y_pos.i.hi - 0x40;
            break;
        }
        arg0->unk90.bytes[1] = 0x14;
        arg0->unk90.bytes[0] = 0xC;
        arg0->unk8C.word = 0x5A;
        set_animation(arg0, 5);
        arg0->unk7 = 2;
        arg0->state = 2;
        arg0->unk60 = 6;
    }
}

void gunship_shot_bullet_fall(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->state = 3;
        return;
    }
    func_8002D9BC(self);
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->state = 3;
}

void gunship_shot_missile_fly(struct ShotObj* self)
{
    struct MiscObj* misc;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->state = 3;
        return;
    }
    if (func_8002D9BC(self) != 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->state++;
        return;
    }
    if (self->unk8C.word != 0) {
        func_800A6DF4(self);
        self->unk8C.word--;
    }
    if (self->unk7 == 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x21;
            misc->id = 0x17;
            misc->unk2 = 0;
            misc->unk15 = get_random() & PLAYER_FACING_RIGHT;
            misc->ext.unk.unk54 = 0;
            misc->x_pos.i.hi = self->x_pos.i.hi;
            misc->y_pos.i.hi = self->y_pos.i.hi;
            misc->unk7 = 1;
            misc->x_vel.val = 0;
            misc->y_vel.val = 0;
            misc->unk16 = VISUAL_SATURN_LAYER(7);
        }
        self->unk7 = 2;
    } else {
        self->unk7--;
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
    } else {
        self->state++;
    }
}

void gunship_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void gunship_shot_idle(struct ShotObj* self)
{
}

// gunship_shot_missile_steer
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A6DF4(struct ShotObj* arg0)
{
    u8 timer = arg0->unk90.bytes[1];
    u8 target;
    u8 current;
    u8 next;
    s32 animation;

    arg0->unk90.bytes[1] = timer - 1;
    if (timer != 0)
        return;
    arg0->unk90.bytes[1] = 1;
    arg0->unk16 = VISUAL_SATURN_LAYER(5);
    target = angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    current = arg0->unk90.bytes[0];
    if (current < target) {
        if (target == current + 1)
            return;
        if (target - current < 0x11)
            next = (current + 1) & 0x1F;
        else
            next = ((current | 0x20) - 1) & 0x1F;
    } else if (target < current) {
        if (target == current - 1)
            return;
        if (current - target < 0x11)
            next = ((current | 0x20) - 1) & 0x1F;
        else
            next = (current + 1) & 0x1F;
    } else {
        return;
    }
    arg0->unk90.bytes[0] = next;
    set_velocity_from_angle(MOVING_OBJECT(arg0), next);
    arg0->x_vel.val *= 4;
    arg0->y_vel.val *= 4;
    animation = next / 2;
    set_animation(arg0, animation < 4 ? animation + 0xF : animation - 1);
}
#else
void func_800A6DF4(struct ShotObj* arg0)
{
#ifndef VERSION_EU
    u8 timer;
#endif
    u8 target;
    u8 next;

#ifdef VERSION_EU
    if (arg0->unk90.bytes[1]-- != 0)
        return;
#else
    timer = arg0->unk90.bytes[1]--;
    if (timer != 0)
        return;
#endif
    arg0->unk90.bytes[1] = 1;
    arg0->unk16 = VISUAL_SATURN_LAYER(5);
    target = angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    if (target > arg0->unk90.bytes[0]) {
        if (target == arg0->unk90.bytes[0] + 1)
            return;
        if (target - arg0->unk90.bytes[0] < 0x11)
            next = (arg0->unk90.bytes[0] + 1) & 0x1F;
        else
            next = ((arg0->unk90.bytes[0] | 0x20) - 1) & 0x1F;
    } else if (target < arg0->unk90.bytes[0]) {
        if (target == arg0->unk90.bytes[0] - 1)
            return;
        if (arg0->unk90.bytes[0] - target >= 0x11)
            next = (arg0->unk90.bytes[0] + 1) & 0x1F;
        else
            next = ((arg0->unk90.bytes[0] | 0x20) - 1) & 0x1F;
    } else {
        return;
    }
    arg0->unk90.bytes[0] = next;
    set_velocity_from_angle(MOVING_OBJECT(arg0), next);
    arg0->x_vel.val *= 4;
    arg0->y_vel.val *= 4;
    switch (next) {
    case 8:
    case 9:
        set_animation(arg0, 3);
        break;
    case 10:
    case 11:
        set_animation(arg0, 4);
        break;
    case 12:
    case 13:
        set_animation(arg0, 5);
        break;
    case 14:
    case 15:
        set_animation(arg0, 6);
        break;
    case 16:
    case 17:
        set_animation(arg0, 7);
        break;
    case 18:
    case 19:
        set_animation(arg0, 8);
        break;
    case 20:
    case 21:
        set_animation(arg0, 9);
        break;
    case 22:
    case 23:
        set_animation(arg0, 10);
        break;
    case 24:
    case 25:
        set_animation(arg0, 11);
        break;
    case 26:
    case 27:
        set_animation(arg0, 12);
        break;
    case 28:
    case 29:
        set_animation(arg0, 13);
        break;
    case 30:
    case 31:
        set_animation(arg0, 14);
        break;
    case 0:
    case 1:
        set_animation(arg0, 0xF);
        break;
    case 2:
    case 3:
        set_animation(arg0, 0x10);
        break;
    case 4:
    case 5:
        set_animation(arg0, 0x11);
        break;
    case 6:
    case 7:
        set_animation(arg0, 0x12);
        break;
    }
}
#endif

u8 gunship_shot_bullet_hit_box[4] = { 0xF7, 0xFB, 0x0C, 0x08 };

u8 gunship_shot_missile_hit_box[4] = { 0xFA, 0xFA, 0x0C, 0x0D };

s32 gunship_shot_missile_speeds[2] = { -0x40000, 0x40000 };

void (*gunship_shot_state_funcs[])(struct ShotObj*) = {
    func_800A699C,
    gunship_shot_bullet_fall,
    gunship_shot_missile_fly,
    gunship_shot_despawn,
    gunship_shot_idle,
};
