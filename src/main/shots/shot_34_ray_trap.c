// ShotObj, shot_object_update_funcs[34]
// 800A16FC..800A22D4
#include "common.h"
#include "main/shots/shot_34_ray_trap.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/collision_bounds.h"
#include "main/1E1BC.h"

// ray_trap_ride_funcs
extern void (*ray_trap_ride_funcs[])(struct ShotObj*);

void ray_trap_ride(struct ShotObj*);

// ray_trap_state_funcs
extern void (*ray_trap_state_funcs[])(struct ShotObj*);

void ray_trap_despawn(struct ShotObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#include "main/collision_bounds.h"
#endif

void func_80021DBC(s16* arg0, s16* arg1, s32 arg2);

struct Shot34Data {
    struct Unk_unk68 bounds[6];
    u8 effect_animation_ids[3][4];
    s8 trailing_data[4];
};

struct Shot34Data ray_trap_data = {
    {
        { -6, -10, 10, 18 },
        { -17, -10, 33, 18 },
        { 0, -1, 11, 3 },
        { -6, -5, 10, 11 },
        { -7, -15, 13, 30 },
        { 0, 0, 7, 8 },
    },
    {
        { 10, 10, 10, 11 },
        { 40, 40, 40, 42 },
        { 41, 41, 41, 42 },
    },
    { 18, 9, -18, 9 },
};

s32 ray_trap_wall_animations[4] = { 7, 6, 11, 15 };

s32 ray_trap_floor_animations[4] = { 4, 5, 3, 2 };

void (*ray_trap_ride_funcs[])(struct ShotObj*) = {
    func_800A19A8,
    func_800A1B1C,
    func_800A1BEC,
};

u8 ray_trap_crawl_boxes[4][4] = {
    { 8, 8, 13, 17 },
    { 7, 7, 12, 16 },
    { 9, 9, 14, 18 },
    { 6, 6, 11, 15 },
};

void (*ray_trap_step_funcs[])(struct ShotObj*) = {
    NULL,
    ray_trap_fall,
    ray_trap_chase,
    func_800A1CCC,
    func_800A1E3C,
    ray_trap_ride,
};

// ray_trap_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A16FC(struct ShotObj* arg0);
static void shot_34_orbit(struct ShotObj* arg0, struct MainObj* owner);
void func_800A19A8(struct ShotObj* arg0);
void func_800A1B1C(struct ShotObj* arg0);
void func_800A1BEC(struct ShotObj* arg0);
void func_800A1CCC(struct ShotObj* arg0);
void func_800A1E3C(struct ShotObj* arg0);
void func_800A2098(struct ShotObj* arg0);
void func_80021DBC(s16* arg0, s16* arg1, s32 arg2);
void ray_trap_check_airborne(struct ShotObj* arg0);
static void shot_34_orbit(struct ShotObj* arg0, struct MainObj* owner)
{
    arg0->unk84.halves[0] = 0x20;
    arg0->unk84.halves[1] = 0x20;
    func_80021DBC((s16*)&arg0->unk84.halves[0], (s16*)&arg0->unk84.halves[1], arg0->unk8C.bytes[0]);
}
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A16FC(struct ShotObj* arg0)
{
    arg0->x_vel.val = 0x60000;
    arg0->unk16 = VISUAL_SATURN_LAYER(5);
    arg0->unk18.val = arg0->x_pos.val;
    arg0->state = 1;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk1C.val = arg0->y_pos.val;
    switch (arg0->unk2) {
    case 0:
        arg0->unk54 = (u8*)&ray_trap_data.bounds[4];
        arg0->unk50.data = (u8*)&ray_trap_data.bounds[3];
        arg0->unk68 = &ray_trap_data.bounds[5];
        arg0->unk5C = 1;
        arg0->unk8C.bytes[3] = 0;
        arg0->timer = 0;
        arg0->unk15 = arg0->x_pos.val < g_Player.x_pos.val ? PLAYER_FACING_RIGHT : 0;
        break;
    case 1:
        arg0->unk54 = (u8*)&ray_trap_data.bounds[1];
        arg0->unk5C = 1;
        arg0->unk50.data = (u8*)&ray_trap_data.bounds[0];
        arg0->unk68 = NULL;
        arg0->timer = 0;
        break;
    case 2:
    case 3:
        arg0->unk5C = 3;
        arg0->unk54 = (u8*)&ray_trap_data.bounds[1];
        arg0->unk50.data = (u8*)&ray_trap_data.bounds[0];
        arg0->unk68 = &ray_trap_data.bounds[2];
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x30000 : -0x30000;
        arg0->unk8C.bytes[3] = 1;
        arg0->timer = 0xE10;
        break;
    }
    arg0->unk60 = 6;
    arg0->unk5C = 3;
    arg0->unk58.data = (u8*)D_80105FF0;
    arg0->unk67 = 0;
    arg0->unk8C.bytes[0] = 7;
    arg0->unk8C.bytes[2] = 0;
    arg0->unk5 = ray_trap_floor_animations[arg0->unk2];
    set_animation(arg0, ray_trap_wall_animations[arg0->unk2]);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_34_ray_trap", func_800A16FC);
#endif

void ray_trap_check_airborne(struct ShotObj* self)
{
    if (self->unk67 == 0 && !(self->unk70 & 8)) {
        self->unk2C = FIXED(0.2578125);
        self->unk67 = -1;
        self->y_vel.val = 0;
        self->unk28 = 0;
        self->unk5 = 1;
        self->unk6 = 0;
    }
}

void ray_trap_fall(struct ShotObj* arg0)
{
    struct ShotObj* self;
    u8 temp_v1;

    self = arg0;
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    temp_v1 = self->unk70;

    if (temp_v1 & 8) {
        self->y_vel.val = 0;
        self->unk2C = 0;
        set_animation(self, 9);
        self->unk5 = 4;
    } else if (temp_v1 & 3) {
        if (self->unk8C.bytes[3] == 0) {
            self->unk5 = 4;
            self->unk6 = 0;
            self->x_vel.val = 0;
            self->y_vel.val = FIXED(-3);
            return;
        }
        self->y_vel.val = 0;
        self->unk2C = 0;
        set_animation(self, 8);
        self->unk5 = 3;
    } else {
        return;
    }

    self->unk6 = 1;
}

// ray_trap_ride_move
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A19A8(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;

    switch (arg0->unk7) {
    case 0:
        arg0->unk7 = 1;
        arg0->y_vel.val = 0xA0000;
        arg0->x_vel.val = 0;
        arg0->unk8C.bytes[1] = 2;
    case 1:
        if (arg0->unk8C.bytes[1] != 0) {
            arg0->unk8C.bytes[1]--;
        } else {
            arg0->y_vel.val = 0;
            arg0->unk7++;
        }
        move_object(MOVING_OBJECT(arg0));
        break;
    case 2:
        if (owner->ext.main_55.unk87 != 0) {
            arg0->unk7 = 0;
            arg0->unk6++;
            break;
        }
        shot_34_orbit(arg0, owner);
        if (arg0->timer == 0) {
            arg0->timer = 3;
            arg0->unk8C.bytes[0] = (arg0->unk8C.bytes[0] - 1) & 0xF;
        } else {
            arg0->timer--;
        }
        arg0->x_pos.i.hi = owner->x_pos.i.hi + arg0->unk84.halves[0];
        arg0->y_pos.i.hi = owner->y_pos.i.hi + arg0->unk84.halves[1];
        break;
    }
    animate_object(ANIMATED_OBJECT(arg0));
    if (owner->active == 0)
        arg0->state = 2;
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_34_ray_trap", func_800A19A8);
#endif

// ray_trap_ride_wait
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A1B1C(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;

    if (!((owner->ext.main_55.unk88 >> arg0->unk8A) & 1)) {
        arg0->unk7 = 0;
        arg0->unk15 = g_Player.x_pos.val >= arg0->x_pos.val ? PLAYER_FACING_RIGHT : 0;
        arg0->unk6++;
    }
    shot_34_orbit(arg0, owner);
    arg0->x_pos.i.hi = owner->x_pos.i.hi + arg0->unk84.halves[0];
    arg0->y_pos.i.hi = owner->y_pos.i.hi + arg0->unk84.halves[1];
    animate_object(ANIMATED_OBJECT(arg0));
    if (owner->active == 0)
        arg0->state = 2;
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_34_ray_trap", func_800A1B1C);
#endif

// ray_trap_ride_return
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A1BEC(struct ShotObj* arg0)
{
    if (arg0->unk7 == 0) {
        arg0->unk7 = 1;
        arg0->unk15 = g_Player.x_pos.val >= arg0->x_pos.val ? PLAYER_FACING_RIGHT : 0;
        set_velocity_from_angle(MOVING_OBJECT(arg0),
            angle_to_point(OBJECT_HEADER(arg0), g_Player.x_pos.val + 0x1400000, g_Player.y_pos.val) & 0xFF);
        arg0->y_vel.val -= 0x30000;
    }
    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_34_ray_trap", func_800A1BEC);
#endif

void ray_trap_ride(struct ShotObj* self)
{
    ray_trap_ride_funcs[self->unk6](self);
}

// ray_trap_crawl_wall
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A1CCC(struct ShotObj* arg0)
{
    u8 flags;
    s32 reverse;

    arg0->unk8C.bytes[3] = 1;
    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    arg0->unk54 = (u8*)&ray_trap_data.bounds[1];
    arg0->unk50.data = (u8*)&ray_trap_data.bounds[0];
    arg0->unk68 = &ray_trap_data.bounds[2];
    if (arg0->unk6 == 0) {
        flags = arg0->unk70;
        if ((flags & 3) == 0)
            return;
        if (arg0->unk15 != 0)
            reverse = flags & 1;
        else
            reverse = (flags & 2) != 0;
        if (!(arg0->unk70 & 8)) {
            arg0->unk6++;
            arg0->x_vel.val = 0;
            arg0->unk15 ^= PLAYER_FACING_RIGHT;
            set_animation(arg0, ray_trap_crawl_boxes[0][arg0->unk2]);
        } else if (reverse) {
            arg0->unk15 ^= PLAYER_FACING_RIGHT;
            arg0->x_vel.val = -arg0->x_vel.val;
        }
        return;
    }
    if (arg0->animation_step.fields.relative_step != 0)
        return;
    arg0->unk5 = 4;
    arg0->unk6 = 0;
    arg0->y_vel.val = -0x30000;
    set_animation(arg0, ray_trap_crawl_boxes[1][arg0->unk2]);
    arg0->unk68 = &ray_trap_data.bounds[5];
    arg0->x_pos.i.hi += arg0->unk15 != 0 ? -0x10 : 0x10;
    arg0->unk67 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_34_ray_trap", func_800A1CCC);
#endif

// ray_trap_crawl_floor
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A1E3C(struct ShotObj* arg0)
{
    arg0->unk8C.bytes[3] = 0;
    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    arg0->unk54 = (u8*)&ray_trap_data.bounds[4];
    arg0->unk50.data = (u8*)&ray_trap_data.bounds[3];
    arg0->unk68 = &ray_trap_data.bounds[5];
    if (arg0->unk6 == 0) {
        if (arg0->unk70 & 8) {
            arg0->unk6 = 1;
            arg0->y_vel.val = 0;
            set_animation(arg0, ray_trap_crawl_boxes[2][arg0->unk2]);
        }
        return;
    }
    if (arg0->animation_step.fields.relative_step != 0)
        return;
    arg0->unk5 = 3;
    arg0->unk6 = 0;
    arg0->unk15 = arg0->x_pos.val < g_Player.x_pos.val ? PLAYER_FACING_RIGHT : 0;
    if (arg0->unk2 < 2)
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x90000 : -0x10000;
    else
        arg0->x_vel.val = arg0->unk15 != 0 ? 0x30000 : -0x30000;
    set_animation(arg0, ray_trap_crawl_boxes[3][arg0->unk2]);
    arg0->unk68 = &ray_trap_data.bounds[2];
    arg0->unk67 = 0;
    arg0->y_pos.i.hi += 0x10;
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_34_ray_trap", func_800A1E3C);
#endif

void ray_trap_chase(struct ShotObj* self)
{
    s16 shot_x;
    u8 collision_flags;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));

    if (self->unk6 == 0) {
        shot_x = self->x_pos.i.hi;
        if (ABS(g_Player.x_pos.i.hi, shot_x) < 8) {
            self->unk6++;
            self->x_vel.val = 0;
            set_animation(self, 0x11);
            return;
        }

        collision_flags = self->unk70;
        if (collision_flags & 3) {
            if (!(collision_flags & 8)) {
                self->unk6++;
                self->x_vel.val = 0;
                self->unk15 ^= PLAYER_FACING_RIGHT;
                set_animation(self, 0x11);
            }
        }
    } else if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 4;
        self->unk6 = 0;
        self->y_vel.val = FIXED(-3);
        set_animation(self, 0x10);
        self->unk68 = &ray_trap_data.bounds[2];
    }
}

// ray_trap_main
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A2098(struct ShotObj* arg0)
{
    s32 hit = func_8002DD04((struct MainObj*)arg0);

    if (arg0->unk2 >= 2) {
        if (((struct BaseObj*)arg0->unk7C)->state == 2)
            hit = -1;
        if (arg0->timer == 0)
            hit = -1;
        else
            arg0->timer--;
    }
    if (hit < 0) {
        spawn_explosion(BASE_OBJECT(arg0));
        if (arg0->unk2 == 2)
            spawn_debris(4, ray_trap_data.effect_animation_ids[1], arg0);
        else if (arg0->unk2 == 3)
            spawn_debris(4, ray_trap_data.effect_animation_ids[2], arg0);
        else if (arg0->unk2 >= 0 && arg0->unk2 < 2)
            spawn_debris(4, ray_trap_data.effect_animation_ids[0], arg0);
        arg0->state = 2;
        return;
    }
    arg0->unk8C.bytes[2] = 1;
    func_8002D9BC(arg0);
    if (arg0->unk2 == 0)
        ray_trap_check_airborne(arg0);
    ray_trap_step_funcs[arg0->unk5](arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x80, 0x80) != 0)
        arg0->state = 2;
    else
        is_on_screen(BASE_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_34_ray_trap", func_800A2098);
#endif

void ray_trap_despawn(struct ShotObj* self)
{
    struct MainObj* owner;

    if (self->unk2 < 2) {
        owner = MAIN_OBJECT(self->unk7C);
        owner->ext.main_55.unk85--;
        owner->ext.main_55.unk88 &= ~(1 << self->unk8A);
    }
    ZeroObjectState(OBJECT_HEADER(self));
}

void ray_trap_update(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    ray_trap_state_funcs[self->state](self);
    CollisionRelated(self);
}

void (*ray_trap_state_funcs[])(struct ShotObj*) = {
    func_800A16FC,
    func_800A2098,
    ray_trap_despawn,
};
