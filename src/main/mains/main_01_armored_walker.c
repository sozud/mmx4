// MainObj, main_object_update_funcs[1]
// 80042120..80042914
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_01_armored_walker.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"
#include "main/objects.h"

extern struct Unk_unk68 armored_walker_terrain_box;
extern struct Unk_unk68 armored_walker_hit_box;
extern union AnimationStep* armored_walker_animations[];

extern u8 armored_walker_debris[8];

// armored_walker_state_funcs
extern void (*armored_walker_state_funcs[])(struct MainObj*);
void armored_walker_init(struct MainObj*);
void armored_walker_main(struct MainObj*);
void armored_walker_despawn(struct MainObj*);

// armored_walker_step_funcs
extern void (*armored_walker_step_funcs[])(struct MainObj*);
void armored_walker_pick_step(struct MainObj* arg0);
void func_800423A0(struct MainObj* arg0);
void armored_walker_hop(struct MainObj* arg0);
void armored_walker_land(struct MainObj* arg0);
void armored_walker_turn(struct MainObj* arg0);
void armored_walker_fall(struct MainObj* arg0);

// armored_walker_turn_funcs
void armored_walker_turn_brake(struct MainObj*);
void armored_walker_turn_flip(struct MainObj*);

// MainObj dispatcher tables
extern void (*armored_walker_turn_funcs[])(struct MainObj*);

void armored_walker_check_behind(struct MainObj* self);
void armored_walker_check_fall(struct MainObj* self);
void armored_walker_check_wall(struct MainObj* self);

void armored_walker_update(struct MainObj* self)
{
    armored_walker_state_funcs[self->state](self);
    CollisionRelated(PLAYER_OBJECT(self));
}

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_01_armored_walker", armored_walker_init);
#else
void armored_walker_init(struct MainObj* self)
{
    u8 state;
    s32 y_pos;
    s32 x_pos;

    state = (u8)self->state;
    self->unk5 = 2;
    y_pos = self->y_pos.val;
    self->unk7C = 0;
    self->unk2 = 0;
    state += 1;
    self->state = state;
    x_pos = self->x_pos.val;
    self->bg_offset = (s8)((u8)g_Player.bg_offset);
    self->unk1C.val = y_pos;
    self->unk18.val = x_pos;
    self->unk15 = self->x_pos.val > g_Player.x_pos.val ? 0 : PLAYER_FACING_RIGHT;
    self->animation_table = (u32**)armored_walker_animations;
    self->unk16 = VISUAL_SATURN_LAYER(6);
    self->terrain_box = &armored_walker_terrain_box;
    self->hurt_box = &armored_walker_hit_box;
    self->attack_box = &armored_walker_hit_box;
    self->collision_data = D_80106370;
    self->hp = 0xF;
    self->invincibility_timer = 0;
    self->contact_damage = 4;
    self->x_speed = 0;
    self->x_accel = 0;
    self->y_speed = 0;
    self->gravity = 0;
    self->air_state = 0;
    set_animation(self, 1);
}
#endif

void armored_walker_main(struct MainObj* obj)
{
    s32 hit;

    if (obj->unk5 != 0) {
        armored_walker_check_wall(obj);
        armored_walker_check_behind(obj);
        armored_walker_check_fall(obj);
    }

    obj->unk18.val = obj->x_pos.val;
    obj->unk1C.val = obj->y_pos.val;
    hit = func_8002DD04(obj);
    if (hit < 0) {
        spawn_explosion(obj);
        spawn_debris(5, armored_walker_debris, obj);
        drop_item(BASE_OBJECT(obj), 9);
    } else {
        armored_walker_step_funcs[obj->unk5](obj);
        func_8002D9BC(obj);
        if (func_8002B1E8(BASE_OBJECT(obj), 0x40, 0x40) == 0) {
            update_on_screen(BASE_OBJECT(obj), 0x20, 0x20);
            return;
        }
    }
    obj->state++;
}

void armored_walker_despawn(struct MainObj* self)
{
#ifdef MMX4_SATURN
    func_8001540C(2, 0, self);
#else
    stop_sound(2, 0xF);
#endif
    despawn_object(self);
}

void armored_walker_pick_step(struct MainObj* self)
{
    if (self->air_state != 0) {
        self->unk5 = 6;
    } else {
        self->unk5 = 2;
    }
}

// armored_walker_walk
void func_800423A0(struct MainObj* self)
{
    s32 speed;

    if (self->unk6 == 0) {
        self->unk6++;
        speed = FIXED(-3);
        self->x_accel = 0;
        if (self->unk15 != 0) {
            speed = FIXED(3);
        }
        self->x_speed = speed;
        func_8001540C(2, SATURN_SOUND(0xF, 0x75), self);
    }

    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}

void armored_walker_hop(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk6 == 0) {
        if (self->animation_step.fields.event != 0) {
            func_8001540C(2, SATURN_SOUND(0x11, 0x77), self);
            self->unk6++;
            self->x_speed = self->unk15 != 0 ? FIXED(-2) : FIXED(2);
            self->x_accel = 0;
            self->y_speed = FIXED(6);
            self->gravity = FIXED(0.2578125);
        }
    } else {
        move_with_gravity(ANIMATED_OBJECT(self));
        if (self->y_speed < 0) {
            set_animation(self, 4);
            self->unk5 = 6;
            self->unk6 = 0;
        }
    }
}

void armored_walker_land(struct MainObj* self)
{
    s32 distance;
    u8 turn;

    if (self->animation_step.fields.event != 0) {
        func_8001540C(2, SATURN_SOUND(0x12, 0x78), self);
        self->animation_step.fields.event = 0;
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        distance = self->x_pos.val - g_Player.x_pos.val;
        if (self->unk15 != 0) {
            turn = distance > 0;
        } else {
            turn = distance <= 0;
        }
        if (turn) {
            set_animation(self, 2);
            self->unk5 = 5;
        } else {
            set_animation(self, 1);
            self->unk5 = 2;
            self->air_state = 0;
        }
        self->unk6 = 0;
        self->unk7C = 0;
    }
}

void armored_walker_turn(struct MainObj* self)
{
    armored_walker_turn_funcs[self->unk6](self);
}

void armored_walker_turn_brake(struct MainObj* self)
{
    if (self->unk7C == 0) {
        self->unk6++;
        func_8001540C(2, SATURN_SOUND(0x10, 0x76), self);
        set_animation(self, 2);
        self->x_accel = FIXED(-0.08984375);
    } else {
        self->unk7C--;
        move_object(MOVING_OBJECT(self));
    }
    animate_object(ANIMATED_OBJECT(self));
}

void armored_walker_turn_flip(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk15 ^= PLAYER_FACING_RIGHT;
        set_animation(self, 1);
        self->unk6++;
        if (self->air_state == 0) {
            self->unk7C = 0x1E;
        }
        self->air_state = 0;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
}

void armored_walker_turn_pause(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk7C == 0x1E) {
        func_8001540C(2, SATURN_SOUND(0xF, 0x75), self);
    }
    if (self->unk7C == 0) {
        self->x_accel = 0;
        self->unk5 = 2;
        self->unk6 = 0;
    } else {
        self->unk7C--;
    }
}

void armored_walker_fall(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk6 == 0) {
        self->unk6++;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        self->x_accel = 0;
    }
    if (self->collision_flags & 8) {
        set_animation(self, 5);
        self->unk5 = 4;
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = 0;
        self->x_speed = 0;
        self->x_accel = 0;
        return;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
}

void armored_walker_check_fall(struct MainObj* self)
{
    if ((self->air_state == 0) && !(self->collision_flags & 8)) {
        set_animation(self, 4);
        self->unk5 = 6;
        self->unk6 = 0;
        self->air_state = -1;
    }
}

void armored_walker_check_behind(struct MainObj* self)
{
    s32 distance;

    if (self->unk5 == 2) {
        distance = self->x_pos.val - g_Player.x_pos.val;
        if (self->unk15 != 0) {
            if (distance > 0) {
                self->unk7C = 10;
                self->unk5 = 5;
                self->unk6 = 0;
            }
        } else if (distance < 0) {
            self->unk7C = 10;
            self->unk5 = 5;
            self->unk6 = 0;
        }
    }
}

void armored_walker_check_wall(struct MainObj* self)
{
    u8 blocked;

    if (self->air_state == 0 && self->unk5 == 2) {
        blocked = 0;
        if (self->unk15 != 0) {
            blocked = self->collision_flags & 1;
        } else if (self->collision_flags & 2) {
            blocked = 1;
        }
        if (blocked != 0) {
            self->unk5 = 3;
            self->unk6 = 0;
            self->air_state = 1;
            set_animation(self, 3);
        }
    }
}

struct Unk_unk68 armored_walker_terrain_box = { 0, 2, 18, 20 };

struct Unk_unk68 armored_walker_hit_box = { -19, -16, 46, 38 };

union AnimationStep armored_walker_anim_0[] = { { 1, 0, 0, 0x00 } };

union AnimationStep armored_walker_anim_1[] = {
    { 1, 0, 1, 0x00 },
    { 1, 0, 1, 0x01 },
    { 1, 0, -2, 0x02 },
};

union AnimationStep armored_walker_anim_2[] = {
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x04 },
    { 2, 0, 1, 0x05 },
    { 2, 0, 1, 0x06 },
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x08 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 2, 0, 1, 0x0C },
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x10 },
    { 1, 0, 1, 0x11 },
    { 1, 1, 0, 0x11 },
};

union AnimationStep armored_walker_anim_3[] = {
    { 1, 0, 1, 0x12 },
    { 1, 1, 1, 0x13 },
    { 1, 0, 1, 0x14 },
    { 1, 0, -2, 0x15 },
};

union AnimationStep armored_walker_anim_4[] = {
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x17 },
    { 1, 0, -2, 0x18 },
};

union AnimationStep armored_walker_anim_5[] = {
    { 4, 1, 1, 0x19 },
    { 1, 0, 1, 0x1B },
    { 1, 0, 1, 0x18 },
    { 6, 0, 1, 0x13 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x1C },
    { 3, 0, 1, 0x19 },
    { 1, 0, 1, 0x1B },
    { 4, 0, 1, 0x18 },
    { 1, 0, 1, 0x1D },
    { 2, 0, 0, 0x1A },
};

union AnimationStep armored_walker_anim_6[] = { { 2, 0, 0, 0x1E } };

union AnimationStep armored_walker_anim_7[] = { { 1, 0, 0, 0x1F } };

union AnimationStep armored_walker_anim_8[] = { { 1, 0, 0, 0x20 } };

union AnimationStep armored_walker_anim_9[] = { { 1, 0, 0, 0x21 } };

union AnimationStep armored_walker_anim_10[] = { { 1, 0, 0, 0x22 } };

union AnimationStep* armored_walker_animations[11] = {
    armored_walker_anim_0,
    armored_walker_anim_1,
    armored_walker_anim_2,
    armored_walker_anim_3,
    armored_walker_anim_4,
    armored_walker_anim_5,
    armored_walker_anim_6,
    armored_walker_anim_7,
    armored_walker_anim_8,
    armored_walker_anim_9,
    armored_walker_anim_10,
};

u8 armored_walker_debris[8] = { 6, 7, 8, 9, 10, 0, 0, 0 };

void (*armored_walker_state_funcs[])(struct MainObj*) = {
    armored_walker_init,
    armored_walker_main,
    armored_walker_despawn,
};

void (*armored_walker_step_funcs[7])(struct MainObj*) = {
    enemy_hit_reaction,
    armored_walker_pick_step,
    func_800423A0,
    armored_walker_hop,
    armored_walker_land,
    armored_walker_turn,
    armored_walker_fall,
};

void (*armored_walker_turn_funcs[3])() = { armored_walker_turn_brake, armored_walker_turn_flip, armored_walker_turn_pause };
