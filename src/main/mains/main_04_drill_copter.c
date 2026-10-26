// MainObj, main_object_update_funcs[4]
// 8004441C..80044F4C
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_04_drill_copter.h"
#include "main/objects.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/1E1BC.h"
#include "main/collision.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#include "main/collision.h"
#endif

// drill_copter_state_funcs
extern void (*drill_copter_state_funcs[])(struct MainObj*);

void drill_copter_despawn(struct MainObj*);

// drill_copter_step_funcs
void drill_copter_approach(struct MainObj* arg0);
void drill_copter_sway(struct MainObj* arg0);
void drill_copter_drop(struct MainObj* arg0);
void drill_copter_rise(struct MainObj* arg0);
void drill_copter_fire(struct MainObj* arg0);

// drill_copter_approach_funcs
extern void (*drill_copter_approach_funcs[])(struct MainObj*);
void drill_copter_approach_start(struct MainObj*);
void drill_copter_approach_fly(struct MainObj*);

// drill_copter_sway_funcs
extern void (*drill_copter_sway_funcs[])(struct MainObj*);
void drill_copter_sway_start(struct MainObj*);
void drill_copter_sway_move(struct MainObj*);

// drill_copter_drop_funcs
extern void (*drill_copter_drop_funcs[])(struct MainObj*);
void drill_copter_drop_start(struct MainObj*);
void drill_copter_drop_wait(struct MainObj*);

void drill_copter_drop_land(struct MainObj*);

// drill_copter_rise_funcs
void drill_copter_rise_start(struct MainObj*);
void drill_copter_rise_wait(struct MainObj*);
void drill_copter_rise_fly(struct MainObj*);

// drill_copter_fire_funcs
void drill_copter_fire_start(struct MainObj*);
void drill_copter_fire_wait(struct MainObj*);

void drill_copter_fire_reload(struct MainObj*);

extern void (*drill_copter_rise_funcs[])(struct MainObj*);
extern void (*drill_copter_fire_funcs[])(struct MainObj*);

extern struct Unk_unk68 D_800F9EBC;
extern struct Unk_unk68 D_800F9EC0;
extern struct Unk_unk68 D_800F9EC4[2];
extern u8* D_800FA0A8[];
extern u8 D_800FA0B4[];
extern union AnimationStep* drill_copter_animations[];
extern struct Unk_unk68 D_801064F0[];
extern void (*drill_copter_step_funcs[])();
void func_80044DE4(struct MainObj* self);

void drill_copter_update(struct MainObj* self)
{
    drill_copter_state_funcs[self->state](self);
}

// drill_copter_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
ret_s8 func_8002DD04(struct MainObj* object);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80044458(struct MainObj* self);
void func_80044508(struct MainObj* self);
#endif

void func_80044458(struct MainObj* self)
{
    self->unk5 = 1;
    self->unk7C = 0xB4;
    self->unk2 = 0;
    self->state++;
    self->bg_offset = g_Player.bg_offset;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->x_speed = 0;
    self->x_accel = 0;
    self->y_speed = 0;
    self->gravity = 0;
    self->unk15 = self->x_pos.val - g_Player.x_pos.val <= 0 ? PLAYER_FACING_RIGHT : 0;
    self->animation_table = (const u8* const*)drill_copter_animations;
    self->unk16 = VISUAL_SATURN_LAYER(6);
    self->collision_data = (const u16*)D_801064F0;
    self->hp = 6;
    self->terrain_box = NULL;
    self->hurt_box = &D_800F9EC0;
    self->attack_box = &D_800F9EC0;
    self->air_state = 0;
    self->contact_damage = 2;
}

// drill_copter_main
void func_80044508(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    if (self->unk2 == 1)
        CollisionRelated(PLAYER_OBJECT(self));
    func_8002D9BC(self);
    if (func_8002DD04(self) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(D_800FA0B4[(s8)self->unk2], D_800FA0A8[(s8)self->unk2], self);
        if (self->unk2 != 2)
            drop_item(BASE_OBJECT(self), 8);
        self->state = 2;
        return;
    }
    if (self->unk2 == 0)
        func_80044DE4(self);
    drill_copter_step_funcs[(s8)self->unk5](self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
        ((void (*)(struct BaseObj*, s32, s32))is_on_screen)(BASE_OBJECT(self), 0x20, 0x20);
        return;
    }
    self->state = 2;
}

void drill_copter_despawn(struct MainObj* self)
{
    if (self->unk2 == 2) {
        ZeroObjectState(OBJECT_HEADER(self));
    } else {
        despawn_object(OBJECT_HEADER(self));
    }
#ifdef MMX4_SATURN
    func_8001540C(2, 3, self);
#else
    stop_sound(2, 7);
    stop_sound(2, 8);
    stop_sound(2, 9);
#endif
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

    self->unk6++;
    x_vel = 0 != self->unk15 ? FIXED(2) : FIXED(-2);
    self->x_speed = x_vel;
    set_animation(self, 2);
    func_8001540C(2, SATURN_SOUND(7, 0x0C), self);
}

void drill_copter_approach_fly(struct MainObj* self)
{
    s32 distance;

    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    distance = ABS(self->x_pos.val, g_Player.x_pos.val);
    if (distance < 0x50000) {
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

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_04_drill_copter", drill_copter_sway_move);
#else
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
        self->unk15 = ((self->unk15 & PLAYER_FACING_RIGHT) == 0) << PLAYER_FACING_SHIFT;
        self->x_speed = -self->x_speed;
        object_x_2 = self->x_pos.val;
        distance_2 = object_x_2 - g_Player.x_pos.val;
        if (distance_2 <= -1) {
            distance_2 = g_Player.x_pos.val - object_x_2;
        }
        if (distance_2 > FIXED(64)) {
            self->unk5 = 1;
            self->unk6 = 0;
        }
    }
}
#endif

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
    self->unk6++;
    self->unk7C = 0x1E;
    self->air_state = -1;
    set_animation(self, 4);
    func_8001540C(2, SATURN_SOUND(8, 0x0D), self);
}

void drill_copter_drop_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk6++;
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.1875);
    }
}

void drill_copter_drop_fall(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->unk6++;
        self->y_speed = 0;
        self->gravity = 0;
        self->air_state = 0;
        set_animation(self, 5);
        func_8001540C(2, SATURN_SOUND(9, 0x0E), self);
    }
}

void drill_copter_drop_land(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
#ifdef MMX4_SATURN
        func_8001540C(2, 3, self);
#else
        stop_sound(2, 9);
#endif
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
        self->unk6++;
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = FIXED(3);
        self->gravity = 0;
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
        func_8001540C(2, SATURN_SOUND(0xA, 0x0F), self);
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
                shot->unk3C = (void*)sprite_frames;
                shot->unk2 = i;
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
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_04_drill_copter", func_80044DE4);
#else
void func_80044DE4(struct MainObj* self)
{
    struct MainObj* child;

    self->unk7C = (u16)self->unk7C - 1;
    if (self->unk7C != 0)
        return;
    child = find_free_main_obj();
    if (child == NULL)
        return;
    child->id = self->id;
    child->active = 0x41;
    child->on_screen = 1;
    child->unk40 = self->unk40;
    child->unk42 = self->unk42;
    child->sprite_frames = self->sprite_frames;
    child->unk2 = 1;
    child->bg_offset = self->bg_offset;
    child->x_pos.val = self->x_pos.val;
    child->y_pos.val = self->y_pos.val;
    child->unk18.val = self->unk18.val;
    child->unk1C.val = self->unk1C.val;
    child->unk15 = self->unk15;
    child->animation_table = (const u8* const*)drill_copter_animations;
    child->unk16 = self->unk16;
    child->terrain_box = &D_800F9EBC;
    child->attack_box = child->hurt_box = D_800F9EC4;
    child->hp = self->hp;
    child->contact_damage = self->contact_damage;
    child->state = self->state;
    child->unk5 = 3;
    child->x_speed = 0;
    child->x_accel = 0;
    child->y_speed = 0;
    child->gravity = 0;
    child->backref = self->backref;
    child->contact_damage = 4;
    child->air_state = 0;
    self->unk2 = 2;
    self->unk5 = 4;
    self->unk6 = 0;
    self->unk7E = 1;
}
#endif

struct Unk_unk68 D_800F9EBC = { 0, 8, 8, 16 };

struct Unk_unk68 D_800F9EC0 = { -9, -24, 14, 46 };

struct Unk_unk68 D_800F9EC4[2] = {
    { -9, -6, 14, 30 },
    { -9, -24, 14, 16 },
};

union AnimationStep drill_copter_anim_0[] = {
    { 1, 0, 0, 0x00 },
};

union AnimationStep drill_copter_anim_1[] = {
    { 1, 0, 0, 0x49 },
};

union AnimationStep drill_copter_anim_2[] = {
    { 1, 0, 1, 0x00 },
    { 1, 0, 1, 0x01 },
    { 1, 0, 1, 0x02 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, -5, 0x05 },
};

union AnimationStep drill_copter_anim_3[] = {
    { 1, 0, 1, 0x00 },
    { 1, 0, 1, 0x01 },
    { 1, 0, 1, 0x02 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x05 },
    { 1, 0, 1, 0x06 },
    { 1, 0, 1, 0x07 },
    { 1, 0, 1, 0x08 },
    { 1, 0, 1, 0x09 },
    { 1, 0, 1, 0x0A },
    { 1, 0, 1, 0x0B },
    { 1, 0, 1, 0x0C },
    { 1, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 1, 0, 1, 0x0F },
    { 1, 0, 1, 0x10 },
    { 1, 0, 1, 0x11 },
    { 1, 0, 1, 0x12 },
    { 1, 0, 1, 0x13 },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, -23, 0x17 },
};

union AnimationStep drill_copter_anim_4[] = {
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x19 },
    { 1, 0, -2, 0x1A },
};

union AnimationStep drill_copter_anim_5[] = {
    { 1, 0, 1, 0x1B },
    { 1, 0, 1, 0x1C },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x1E },
    { 1, 0, 1, 0x1F },
    { 1, 0, 1, 0x20 },
    { 2, 0, 1, 0x21 },
    { 2, 0, 1, 0x22 },
    { 2, 0, 1, 0x23 },
    { 2, 0, 1, 0x24 },
    { 3, 0, 1, 0x25 },
    { 5, 0, 1, 0x26 },
    { 3, 0, 1, 0x27 },
    { 5, 0, 1, 0x28 },
    { 3, 0, 1, 0x29 },
    { 7, 0, 1, 0x2A },
    { 7, 0, 1, 0x2B },
    { 10, 0, 1, 0x2C },
    { 10, 1, 1, 0x2D },
    { 11, 0, 1, 0x2E },
    { 11, 0, 0, 0x2F },
};

union AnimationStep drill_copter_anim_6[] = {
    { 2, 0, 1, 0x2F },
    { 2, 0, 1, 0x30 },
    { 2, 0, 1, 0x31 },
    { 2, 0, 1, 0x32 },
    { 2, 0, 0, 0x33 },
};

union AnimationStep drill_copter_anim_7[] = {
    { 4, 0, 1, 0x34 },
    { 6, 0, 1, 0x35 },
    { 9, 0, 1, 0x36 },
    { 6, 0, 1, 0x35 },
    { 4, 0, 1, 0x37 },
    { 2, 1, 1, 0x38 },
    { 2, 0, 1, 0x39 },
    { 2, 0, 1, 0x3A },
    { 2, 0, 1, 0x32 },
    { 2, 0, 0, 0x33 },
};

union AnimationStep drill_copter_anim_8[] = {
    { 1, 0, 1, 0x48 },
    { 1, 0, 1, 0x49 },
    { 1, 0, 1, 0x4A },
    { 1, 0, 1, 0x4B },
    { 1, 0, 1, 0x4C },
    { 1, 0, -5, 0x4D },
};

union AnimationStep drill_copter_anim_14[] = {
    { 3, 0, 1, 0x3B },
    { 3, 0, 1, 0x3C },
    { 3, 0, 1, 0x3D },
    { 3, 0, 1, 0x3E },
    { 3, 0, -4, 0x3F },
};

union AnimationStep drill_copter_anim_9[] = {
    { 2, 0, 1, 0x40 },
    { 2, 0, 1, 0x41 },
    { 2, 0, 1, 0x42 },
    { 2, 0, -3, 0x43 },
};

union AnimationStep drill_copter_anim_10[] = {
    { 1, 0, 0, 0x44 },
};

union AnimationStep drill_copter_anim_11[] = {
    { 1, 0, 0, 0x45 },
};

union AnimationStep drill_copter_anim_12[] = {
    { 1, 0, 0, 0x46 },
};

union AnimationStep drill_copter_anim_13[] = {
    { 1, 0, 0, 0x47 },
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
