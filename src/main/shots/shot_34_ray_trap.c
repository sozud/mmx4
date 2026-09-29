// ShotObj, shot_object_update_funcs[34]
// 800A16FC..800A22D4
#include "common.h"

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
INCLUDE_ASM("main/nonmatchings/shots/shot_34_ray_trap", func_800A16FC);

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
    s8 var_v0;
    u8 temp_v1;

    self = arg0;
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    temp_v1 = self->unk70;

    if (temp_v1 & 8) {
        self->y_vel.val = 0;
        self->unk2C = 0;
        set_animation(self, 9);
        var_v0 = 4;
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
        var_v0 = 3;
    } else {
        return;
    }

    self->unk5 = var_v0;
    self->unk6 = 1;
}

// ray_trap_ride_move
INCLUDE_ASM("main/nonmatchings/shots/shot_34_ray_trap", func_800A19A8);

// ray_trap_ride_wait
INCLUDE_ASM("main/nonmatchings/shots/shot_34_ray_trap", func_800A1B1C);

// ray_trap_ride_return
INCLUDE_ASM("main/nonmatchings/shots/shot_34_ray_trap", func_800A1BEC);

void ray_trap_ride(struct ShotObj* self)
{
    ray_trap_ride_funcs[self->unk6](self);
}

// ray_trap_crawl_wall
INCLUDE_ASM("main/nonmatchings/shots/shot_34_ray_trap", func_800A1CCC);

// ray_trap_crawl_floor
INCLUDE_ASM("main/nonmatchings/shots/shot_34_ray_trap", func_800A1E3C);

void ray_trap_chase(struct ShotObj* self)
{
    s16 shot_x;
    s32 distance;
    u8 collision_flags;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));

    if (self->unk6 == 0) {
        shot_x = self->x_pos.i.hi;
        distance = g_Player.x_pos.i.hi - shot_x;
        if (distance >= 0 ? distance < 8 : shot_x - g_Player.x_pos.i.hi < 8) {
            self->x_vel.val = 0;
            self->unk6++;
            set_animation(self, 0x11);
            return;
        }

        collision_flags = self->unk70;
        if ((collision_flags & 3) && !(collision_flags & 8)) {
            self->x_vel.val = 0;
            self->unk6++;
            self->unk15 ^= 0x40;
            set_animation(self, 0x11);
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
INCLUDE_ASM("main/nonmatchings/shots/shot_34_ray_trap", func_800A2098);

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
