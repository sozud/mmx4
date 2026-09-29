// MainObj, main_object_update_funcs[4]
// 8004441C..80044F4C
#include "common.h"
#include "func_tables.h"

void drill_copter_update(struct MainObj* self)
{
    drill_copter_state_funcs[self->state](self);
}

// drill_copter_init
INCLUDE_ASM("main/nonmatchings/mains/main_04_drill_copter", func_80044458);

// drill_copter_main
INCLUDE_ASM("main/nonmatchings/mains/main_04_drill_copter", func_80044508);

void drill_copter_despawn(struct MainObj* self)
{
    if (self->unk2 == 2) {
        ZeroObjectState(OBJECT_HEADER(self));
    } else {
        despawn_object(OBJECT_HEADER(self));
    }
    stop_sound(2, 7);
    stop_sound(2, 8);
    stop_sound(2, 9);
}

void drill_copter_noop(struct MainObj* self)
{
}

void drill_copter_approach(struct MainObj* self)
{
    drill_copter_approach_funcs[self->unk6](self);
}

void drill_copter_approach_start(struct MainObj* self)
{
    s32 x_vel;

    x_vel = FIXED(-2);
    self->unk6++;
    if (self->unk15 != 0) {
        x_vel = FIXED(2);
    }
    self->x_speed = x_vel;
    set_animation(self, 2);
    func_8001540C(2, 7, self);
}

void drill_copter_approach_fly(struct MainObj* self)
{
    s32 distance;

    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    distance = self->x_pos.val - g_Player.x_pos.val;
    if (distance < 0) {
        distance = g_Player.x_pos.val - self->x_pos.val;
    }
    if (distance <= 0x4FFFF) {
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void drill_copter_approach_idle(struct MainObj* self)
{
}

void drill_copter_sway(struct MainObj* self)
{
    drill_copter_sway_funcs[self->unk6](self);
}

void drill_copter_sway_start(struct MainObj* self)
{
    self->unk6++;
    set_animation(self, 3);
}

void drill_copter_sway_move(struct MainObj* self)
{
    s32 object_x;
    s32 object_x_2;
    s32 distance;
    s32 distance_2;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));

    object_x = self->x_pos.val;
    distance = object_x - g_Player.x_pos.val;
    if (distance < 0) {
        distance = g_Player.x_pos.val - object_x;
    }
    if (distance > FIXED(64)) {
        self->unk15 = ((self->unk15 & 0x40) == 0) << 6;
        self->x_speed = -self->x_speed;
        object_x_2 = self->x_pos.val;
        distance_2 = object_x_2 - g_Player.x_pos.val;
        if (distance_2 < 0) {
            distance_2 = g_Player.x_pos.val - object_x_2;
        }
        if (distance_2 > FIXED(64)) {
            self->unk5 = 1;
            self->unk6 = 0;
        }
    }
}

void drill_copter_sway_idle(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
}

void drill_copter_drop(struct MainObj* self)
{
    drill_copter_drop_funcs[self->unk6](self);
}

void drill_copter_drop_start(struct MainObj* self)
{
    self->unk7C = 0x1E;
    self->air_state = -1;
    self->unk6++;
    set_animation(self, 4);
    func_8001540C(2, 8, self);
}

void drill_copter_drop_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.1875);
        self->unk6++;
    }
}

void drill_copter_drop_fall(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->y_speed = 0;
        self->gravity = 0;
        self->air_state = 0;
        self->unk6++;
        set_animation(self, 5);
        func_8001540C(2, 9, self);
    }
}

void drill_copter_drop_land(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        stop_sound(2, 9);
        self->unk5 = 5;
        self->unk6 = 0;
        self->contact_damage = 2;
    }
}

void drill_copter_drop_idle(struct MainObj* self)
{
}

void drill_copter_rise(struct MainObj* self)
{
    drill_copter_rise_funcs[self->unk6](self);
}

void drill_copter_rise_start(struct MainObj* self)
{
    self->unk7C = 0x3C;
    self->unk6++;
    set_animation(self, 8);
}

void drill_copter_rise_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = FIXED(3);
        self->gravity = 0;
        self->unk6++;
    }
}

void drill_copter_rise_fly(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

void drill_copter_fire(struct MainObj* self)
{
    drill_copter_fire_funcs[self->unk6](self);
}

void drill_copter_fire_start(struct MainObj* self)
{
    self->unk7C = 0x28;
    self->unk6++;
}

void drill_copter_fire_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        set_animation(self, 7);
        self->unk7E = 3;
        self->unk6++;
    }
}

void drill_copter_fire_shots(struct MainObj* self)
{
    const u8* sprite_frames;
    u8 i;
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        func_8001540C(2, 0xA, self);
        self->animation_step.fields.event = 0;
        i = 0;
        do {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 1;
                shot->unk40 = self->unk40;
                shot->unk42 = self->unk42;
                sprite_frames = self->sprite_frames;
                shot->unk2 = i;
                shot->unk3C = (void*)sprite_frames;
                shot->bg_offset = self->bg_offset;
                shot->x_pos.val = self->x_pos.val;
                shot->y_pos.val = self->y_pos.val;
            }
            i++;
        } while (i < 2);
    }
    if (self->animation_step.fields.relative_step == 0) {
        if (--self->unk7E != 0) {
            set_animation(self, 7);
            return;
        }
        self->unk7C = 0x5A;
        self->unk6++;
    }
}

void drill_copter_fire_reload(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        set_animation(self, 7);
        self->unk6 = 2;
        self->unk7E = 3;
    }
}

// drill_copter_spawn_clone
INCLUDE_ASM("main/nonmatchings/mains/main_04_drill_copter", func_80044DE4);

struct Unk_unk68 D_800F9EBC = { 0, 8, 8, 16 };

struct Unk_unk68 D_800F9EC0 = { -9, -24, 14, 46 };

struct Unk_unk68 D_800F9EC4[2] = {
    { -9, -6, 14, 30 },
    { -9, -24, 14, 16 },
};

union AnimationStep drill_copter_anim_0[] = {
    { 0x00000001 },
};

union AnimationStep drill_copter_anim_1[] = {
    { 0x49000001 },
};

union AnimationStep drill_copter_anim_2[] = {
    { 0x00010001 },
    { 0x01010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05FB0001 },
};

union AnimationStep drill_copter_anim_3[] = {
    { 0x00010001 },
    { 0x01010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x10010001 },
    { 0x11010001 },
    { 0x12010001 },
    { 0x13010001 },
    { 0x14010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x17E90001 },
};

union AnimationStep drill_copter_anim_4[] = {
    { 0x18010001 },
    { 0x19010001 },
    { 0x1AFE0001 },
};

union AnimationStep drill_copter_anim_5[] = {
    { 0x1B010001 },
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1F010001 },
    { 0x20010001 },
    { 0x21010002 },
    { 0x22010002 },
    { 0x23010002 },
    { 0x24010002 },
    { 0x25010003 },
    { 0x26010005 },
    { 0x27010003 },
    { 0x28010005 },
    { 0x29010003 },
    { 0x2A010007 },
    { 0x2B010007 },
    { 0x2C01000A },
    { 0x2D01010A },
    { 0x2E01000B },
    { 0x2F00000B },
};

union AnimationStep drill_copter_anim_6[] = {
    { 0x2F010002 },
    { 0x30010002 },
    { 0x31010002 },
    { 0x32010002 },
    { 0x33000002 },
};

union AnimationStep drill_copter_anim_7[] = {
    { 0x34010004 },
    { 0x35010006 },
    { 0x36010009 },
    { 0x35010006 },
    { 0x37010004 },
    { 0x38010102 },
    { 0x39010002 },
    { 0x3A010002 },
    { 0x32010002 },
    { 0x33000002 },
};

union AnimationStep drill_copter_anim_8[] = {
    { 0x48010001 },
    { 0x49010001 },
    { 0x4A010001 },
    { 0x4B010001 },
    { 0x4C010001 },
    { 0x4DFB0001 },
};

union AnimationStep drill_copter_anim_14[] = {
    { 0x3B010003 },
    { 0x3C010003 },
    { 0x3D010003 },
    { 0x3E010003 },
    { 0x3FFC0003 },
};

union AnimationStep drill_copter_anim_9[] = {
    { 0x40010002 },
    { 0x41010002 },
    { 0x42010002 },
    { 0x43FD0002 },
};

union AnimationStep drill_copter_anim_10[] = {
    { 0x44000001 },
};

union AnimationStep drill_copter_anim_11[] = {
    { 0x45000001 },
};

union AnimationStep drill_copter_anim_12[] = {
    { 0x46000001 },
};

union AnimationStep drill_copter_anim_13[] = {
    { 0x47000001 },
};

union AnimationStep* drill_copter_animations[] = {
    drill_copter_anim_0,
    drill_copter_anim_1,
    drill_copter_anim_2,
    drill_copter_anim_3,
    drill_copter_anim_4,
    drill_copter_anim_5,
    drill_copter_anim_6,
    drill_copter_anim_7,
    drill_copter_anim_8,
    drill_copter_anim_9,
    drill_copter_anim_10,
    drill_copter_anim_11,
    drill_copter_anim_12,
    drill_copter_anim_13,
    drill_copter_anim_14,
};

u8 D_800FA070[] = {
    0x09,
    0x0A,
    0x0B,
    0x0C,
    0x0D,
    0x00,
    0x00,
    0x00,
};

u8 D_800FA078[] = {
    0x09,
    0x0B,
    0x0C,
    0x0D,
};

u8 D_800FA07C[4] = { '\n', 0, 0, 0 };

void (*drill_copter_state_funcs[])() = {
    func_80044458,
    func_80044508,
    drill_copter_despawn,
    drill_copter_noop,
};

void (*drill_copter_step_funcs[])() = {
    enemy_hit_reaction,
    drill_copter_approach,
    drill_copter_sway,
    drill_copter_drop,
    drill_copter_rise,
    drill_copter_fire,
};

u8* D_800FA0A8[] = {
    D_800FA070,
    D_800FA078,
    D_800FA07C,
};

u8 D_800FA0B4[] = {
    0x05,
    0x04,
    0x01,
    0x00,
};

void (*drill_copter_approach_funcs[])() = {
    drill_copter_approach_start,
    drill_copter_approach_fly,
    drill_copter_approach_idle,
};

void (*drill_copter_sway_funcs[])() = {
    drill_copter_sway_start,
    drill_copter_sway_move,
    drill_copter_sway_idle,
};

void (*drill_copter_drop_funcs[])() = {
    drill_copter_drop_start,
    drill_copter_drop_wait,
    drill_copter_drop_fall,
    drill_copter_drop_land,
    drill_copter_drop_idle,
};

void (*drill_copter_rise_funcs[])() = {
    drill_copter_rise_start,
    drill_copter_rise_wait,
    drill_copter_rise_fly,
};

void (*drill_copter_fire_funcs[])() = {
    drill_copter_fire_start,
    drill_copter_fire_wait,
    drill_copter_fire_shots,
    drill_copter_fire_reload,
};
