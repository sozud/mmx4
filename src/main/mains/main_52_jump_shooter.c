// MainObj, main_object_update_funcs[52]
// 8006A50C..8006AF70
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_52_jump_shooter.h"
#include "main/objects.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"
#include "main/1CF60.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1CF60.h"
#endif

// jump_shooter_state_funcs
extern void (*jump_shooter_state_funcs[])(struct MainObj*);
void func_8006A55C(struct MainObj*);
void jump_shooter_main(struct MainObj*);
void jump_shooter_despawn(struct MainObj*);

// jump_shooter_step_funcs
void jump_shooter_resume_step(struct MainObj* arg0);
void jump_shooter_fire(struct MainObj* arg0);
void jump_shooter_walk(struct MainObj* arg0);
void jump_shooter_jump(struct MainObj* arg0);

// jump_shooter_fire_funcs
extern void (*jump_shooter_fire_funcs[])(struct MainObj*);
void jump_shooter_fire_aim(struct MainObj*);
void jump_shooter_fire_ready(struct MainObj*);

void jump_shooter_fire_end(struct MainObj*);

// jump_shooter_walk_funcs
extern void (*jump_shooter_walk_funcs[])(struct MainObj*);
void jump_shooter_walk_start(struct MainObj*);

// jump_shooter_jump_funcs
extern void (*jump_shooter_jump_funcs[])(struct MainObj*);

void jump_shooter_jump_air(struct MainObj*);
void jump_shooter_jump_land(struct MainObj*);

void jump_shooter_face_player(struct AnimatedObj* self);

extern u8 jump_shooter_debris[];
extern void (*jump_shooter_step_funcs[])(struct MainObj*);

void jump_shooter_update(struct MainObj* self)
{
    jump_shooter_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

// jump_shooter_init
void func_8006A55C(struct MainObj* self)
{
    const u8* const* animations = (const u8* const*)jump_shooter_animations;

    self->hp = 9;
    self->contact_damage = 3;
    self->invincibility_timer = 0;
    self->collision_data = D_801077F8;
    self->bg_offset = g_Player.bg_offset;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->x_speed = 0;
    self->animation_table = animations;
    self->unk16 = VISUAL_SATURN_LAYER(6);
    self->terrain_box = &jump_shooter_terrain_box;
    self->hurt_box = &jump_shooter_hurt_box;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->attack_box = &jump_shooter_attack_box;
    jump_shooter_face_player(ANIMATED_OBJECT(self));
    self->unk7C = 0x5A;
    self->ext.main_52.unk80 = 0;
    self->ext.main_52.unk8C = 0;
    self->state = 1;
    self->unk5 = 3;
    self->unk6 = 0;
}

void jump_shooter_main(struct MainObj* self)
{
    s32 hit;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    jump_shooter_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    self->ext.main_52.saved_unk5 = self->unk5;
    hit = func_8002DD04(self);
    if (hit < 0) {
        spawn_explosion(self);
        spawn_debris(3, &jump_shooter_debris, self);
        drop_item(BASE_OBJECT(self), 0);
    } else if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
        return;
    }
    self->state = 2;
}

void jump_shooter_despawn(struct MainObj* self)
{
    self->ext.raw[0] = 0;
    self->ext.raw[1] = 0;
    self->ext.raw[2] = 0;
    self->ext.raw[3] = 0;
    self->ext.raw[4] = 0;
    self->ext.raw[5] = 0;
    despawn_object(OBJECT_HEADER(self));
}

void jump_shooter_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_52.saved_unk5;
}

void jump_shooter_fire(struct MainObj* self)
{
    jump_shooter_fire_funcs[self->unk6](self);
}

void jump_shooter_fire_aim(struct MainObj* self)
{
    jump_shooter_face_player(ANIMATED_OBJECT(self));
    func_8006AE80(self);
    if (self->ext.main_52.unk80 == 0) {
        set_animation(self, self->ext.main_52.unk88 + 0x12);
    } else {
        set_animation(self, self->ext.main_52.unk88 + 0x17);
    }
    self->unk6 = 1;
}

void jump_shooter_fire_ready(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk6 = 2;
        self->unk7C = 2;
        self->unk7E = 0xC;
    }
}

void jump_shooter_fire_shots(struct MainObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7E != 0) {
        return;
    }
    if (self->ext.main_52.unk80 == 0) {
        set_animation(self, self->ext.main_52.unk88 + 2);
    } else {
        set_animation(self, self->ext.main_52.unk88 + 7);
    }
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x1B;
        shot->unk2 = self->ext.main_52.unk88 + self->ext.main_52.unk80 * 5;
        shot->unk40 = self->unk40;
        shot->unk42 = self->unk42;
        shot->animation_table = (u32**)self->animation_table;
        shot->unk3C = (void*)self->sprite_frames;
        shot->bg_offset = self->bg_offset;
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        shot->unk15 = self->unk15;
        set_velocity_from_angle(MOVING_OBJECT(shot), self->ext.main_52.unk84);
        shot->state = 0;
    }
    if (--self->unk7C == 0) {
        self->unk7C = 0x1E;
        self->unk6 = 3;
        self->ext.main_52.unk8C = 0;
    } else {
        self->unk7E = 0x10;
    }
}

void jump_shooter_fire_end(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->ext.main_52.unk8C = 0;
        self->unk7C = 0x5A;
        if (self->ext.main_52.unk80 == 0) {
            self->unk5 = 3;
            self->unk6 = 0;
        } else {
            self->x_speed = 0;
            self->gravity = FIXED(0.25);
            self->unk5 = 4;
            self->unk6 = 1;
        }
    }
}

void jump_shooter_walk(struct MainObj* self)
{
    jump_shooter_walk_funcs[self->unk6](self);
}

void jump_shooter_walk_start(struct MainObj* self)
{
    jump_shooter_face_player(ANIMATED_OBJECT(self));
    if (self->unk15 == 0) {
        self->x_speed = FIXED(-1.8);
    } else {
        self->x_speed = FIXED(1.8);
    }
    set_animation(self, 0);
    self->unk6 = 1;
}

// jump_shooter_walk_move

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006AAB4(struct MainObj* arg0);
void func_8006AE80(struct MainObj* arg0);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_52_jump_shooter", func_8006AAB4);
#else
void func_8006AAB4(struct MainObj* arg0)
{
    struct Unk_unk68* bounds;
    s16 x;
    s16 y;

    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    bounds = arg0->terrain_box;
    x = arg0->x_pos.i.hi + bounds->unk0;
    y = arg0->y_pos.i.hi + bounds->unk1 + (u8)bounds->unk3 + 0x10;
    x = arg0->unk15 == 0 ? x - 0x10 : x + 0x10;
    if (func_8002D724(PLAYER_OBJECT(arg0), x, y) == 0) {
        set_animation(arg0, 1);
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        return;
    }
    if (arg0->unk15 == 0) {
        if (g_Player.x_pos.i.hi - arg0->x_pos.i.hi > 0x40) {
            arg0->unk15 = PLAYER_FACING_RIGHT;
            arg0->x_speed = 0x1CCCC;
            goto countdown;
        }
        if (!(arg0->collision_flags & 2)) {
            goto countdown;
        }
    } else {
        if (arg0->x_pos.i.hi - g_Player.x_pos.i.hi > 0x40) {
            arg0->unk15 = 0;
            arg0->x_speed = -0x1CCCC;
            goto countdown;
        }
        if (!(arg0->collision_flags & 1)) {
            goto countdown;
        }
    }
    set_animation(arg0, 1);
    arg0->unk5 = 4;
    arg0->unk6 = 0;
countdown:
    if (--arg0->unk7C != 0) {
        return;
    }
    arg0->ext.main_52.unk8C = 1;
    if ((g_Player.y_pos.i.hi - arg0->y_pos.i.hi >= 0 ? g_Player.y_pos.i.hi - arg0->y_pos.i.hi : arg0->y_pos.i.hi - g_Player.y_pos.i.hi) > 0x20) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        return;
    }
    if ((u32)(get_random() & 0xF) < 3) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        return;
    }
    set_animation(arg0, 1);
    arg0->unk5 = 4;
    arg0->unk6 = 0;
}
#endif

void jump_shooter_jump(struct MainObj* self)
{
    jump_shooter_jump_funcs[self->unk6](self);
}

void jump_shooter_jump_launch(struct MainObj* self)
{
    s8 event;

    animate_object(ANIMATED_OBJECT(self));
    event = self->animation_step.fields.event;
    if (2 == event) {
        u8 direction;

        self->ext.main_52.unk80 = 1;
        self->y_speed = FIXED(6);
        self->gravity = FIXED(0.25);
        direction = self->ext.main_52.unk8C;
        if (direction == 0) {
            if (self->unk15 != 0) {
                self->x_speed = FIXED(1.8);
            } else {
                self->x_speed = FIXED(-1.8);
            }
        } else if (direction == 1) {
            self->x_speed = 0;
        } else if (direction == event) {
            if (self->unk15 == 0) {
                self->x_speed = FIXED(1.8);
            } else {
                self->x_speed = FIXED(-1.8);
            }
        }
        move_with_gravity(ANIMATED_OBJECT(self));
        self->unk6 = 1;
    }
}

void jump_shooter_jump_air(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->y_speed == 0 && self->ext.main_52.unk8C != 0) {
        self->gravity = 0;
        self->unk5 = 2;
        self->unk6 = 0;
    }
    if (self->collision_flags & 8) {
        self->y_speed = 0;
        self->gravity = 0;
        set_animation(self, 0x11);
        self->unk6 = 2;
    }
}

void jump_shooter_jump_land(struct MainObj* self)
{
    animate_object(self);
    if (self->animation_step.fields.event != 0) {
        self->ext.main_52.unk80 = 0;
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void jump_shooter_face_player(struct AnimatedObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = PLAYER_FACING_RIGHT;
    }
}

// jump_shooter_aim_at_player
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006AE80(struct MainObj* arg0)
{
    u8 angle;
    u8 value;

    arg0->y_pos.i.hi -= 0x10;
    arg0->ext.main_52.unk84 = angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    arg0->y_pos.i.hi += 0x10;
    angle = arg0->ext.main_52.unk84;
    if (arg0->unk15 == 0) {
        if ((u8)(angle - 8) > 0x10) {
            return;
        }
        if (angle < 10) {
            value = 0;
        } else if (angle < 14) {
            value = 1;
        } else if (angle < 19) {
            value = 2;
        } else if (angle < 23) {
            value = 3;
        } else {
            value = 4;
        }
    } else {
        if (angle >= 0x20) {
            return;
        }
        if (angle < 3) {
            value = 2;
        } else if (angle < 7) {
            value = 1;
        } else if (angle < 9) {
            value = 0;
        } else if (angle < 24) {
            return;
        } else if (angle < 26) {
            value = 4;
        } else if (angle < 30) {
            value = 3;
        } else {
            value = 2;
        }
    }
    arg0->ext.main_52.unk88 = value;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_52_jump_shooter", func_8006AE80);
#endif

struct Unk_unk68 jump_shooter_hurt_box = { -14, -19, 25, 33 };

struct Unk_unk68 jump_shooter_attack_box = { -10, -18, 16, 30 };

struct Unk_unk68 jump_shooter_terrain_box = { 0, 0, 6, 15 };

union AnimationStep jump_shooter_anim_0[] = {
    { 8, 0, 1, 0x0F },
    { 8, 0, 1, 0x10 },
    { 7, 0, 1, 0x11 },
    { 8, 0, 1, 0x12 },
    { 8, 0, 1, 0x13 },
    { 7, 1, -5, 0x14 },
};

union AnimationStep jump_shooter_anim_1[] = {
    { 8, 0, 1, 0x00 },
    { 6, 0, 1, 0x01 },
    { 3, 0, 1, 0x02 },
    { 1, 2, 1, 0x02 },
    { 6, 0, 1, 0x03 },
    { 6, 1, 0, 0x04 },
};

union AnimationStep jump_shooter_anim_2[] = {
    { 1, 0, 1, 0x16 },
    { 6, 0, 1, 0x15 },
    { 1, 1, 0, 0x15 },
};

union AnimationStep jump_shooter_anim_3[] = {
    { 1, 0, 1, 0x18 },
    { 6, 0, 1, 0x17 },
    { 1, 1, 0, 0x17 },
};

union AnimationStep jump_shooter_anim_4[] = {
    { 1, 0, 1, 0x1A },
    { 6, 0, 1, 0x19 },
    { 1, 1, 0, 0x19 },
};

union AnimationStep jump_shooter_anim_5[] = {
    { 1, 0, 1, 0x1C },
    { 6, 0, 1, 0x1B },
    { 1, 1, 0, 0x1B },
};

union AnimationStep jump_shooter_anim_6[] = {
    { 1, 0, 1, 0x1E },
    { 6, 0, 1, 0x1D },
    { 1, 1, 0, 0x1D },
};

union AnimationStep jump_shooter_anim_7[] = {
    { 1, 0, 1, 0x06 },
    { 6, 0, 1, 0x05 },
    { 1, 1, 0, 0x05 },
};

union AnimationStep jump_shooter_anim_8[] = {
    { 1, 0, 1, 0x08 },
    { 6, 0, 1, 0x07 },
    { 1, 1, 0, 0x07 },
};

union AnimationStep jump_shooter_anim_9[] = {
    { 1, 0, 1, 0x0A },
    { 6, 0, 1, 0x09 },
    { 1, 1, 0, 0x09 },
};

union AnimationStep jump_shooter_anim_10[] = {
    { 1, 0, 1, 0x0C },
    { 6, 0, 1, 0x0B },
    { 1, 1, 0, 0x0B },
};

union AnimationStep jump_shooter_anim_11[] = {
    { 1, 0, 1, 0x0E },
    { 6, 0, 1, 0x0D },
    { 1, 1, 0, 0x0D },
};

union AnimationStep jump_shooter_anim_12[] = {
    { 1, 0, 1, 0x1F },
    { 1, 0, 1, 0x20 },
    { 1, 0, -2, 0x21 },
};

union AnimationStep jump_shooter_anim_13[] = {
    { 1, 1, 0, 0x22 },
};

union AnimationStep jump_shooter_anim_14[] = {
    { 1, 1, 0, 0x23 },
};

union AnimationStep jump_shooter_anim_15[] = {
    { 1, 1, 0, 0x24 },
};

union AnimationStep jump_shooter_anim_16[] = {
    { 1, 1, 0, 0x25 },
};

union AnimationStep jump_shooter_anim_17[] = {
    { 6, 0, 1, 0x03 },
    { 5, 0, 1, 0x01 },
    { 1, 1, 0, 0x01 },
};

union AnimationStep jump_shooter_anim_18[] = {
    { 2, 0, 1, 0x17 },
    { 1, 0, 1, 0x15 },
    { 1, 1, 0, 0x15 },
};

union AnimationStep jump_shooter_anim_19[] = {
    { 1, 1, 0, 0x17 },
};

union AnimationStep jump_shooter_anim_20[] = {
    { 2, 0, 1, 0x17 },
    { 1, 0, 1, 0x19 },
    { 1, 1, 0, 0x19 },
};

union AnimationStep jump_shooter_anim_21[] = {
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x19 },
    { 1, 0, 1, 0x1B },
    { 1, 1, 0, 0x1B },
};

union AnimationStep jump_shooter_anim_22[] = {
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x1B },
    { 1, 0, 1, 0x1D },
    { 1, 1, 0, 0x1D },
};

union AnimationStep jump_shooter_anim_23[] = {
    { 2, 0, 1, 0x07 },
    { 1, 0, 1, 0x05 },
    { 1, 1, 0, 0x05 },
};

union AnimationStep jump_shooter_anim_24[] = {
    { 1, 1, 0, 0x07 },
};

union AnimationStep jump_shooter_anim_25[] = {
    { 2, 0, 1, 0x07 },
    { 1, 0, 1, 0x09 },
    { 1, 1, 0, 0x09 },
};

union AnimationStep jump_shooter_anim_26[] = {
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x09 },
    { 1, 0, 1, 0x0B },
    { 1, 1, 0, 0x0B },
};

union AnimationStep jump_shooter_anim_27[] = {
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x0B },
    { 1, 0, 1, 0x0D },
    { 1, 1, 0, 0x0D },
};

union AnimationStep* jump_shooter_animations[28] = {
    jump_shooter_anim_0,
    jump_shooter_anim_1,
    jump_shooter_anim_2,
    jump_shooter_anim_3,
    jump_shooter_anim_4,
    jump_shooter_anim_5,
    jump_shooter_anim_6,
    jump_shooter_anim_7,
    jump_shooter_anim_8,
    jump_shooter_anim_9,
    jump_shooter_anim_10,
    jump_shooter_anim_11,
    jump_shooter_anim_12,
    jump_shooter_anim_13,
    jump_shooter_anim_14,
    jump_shooter_anim_15,
    jump_shooter_anim_16,
    jump_shooter_anim_17,
    jump_shooter_anim_18,
    jump_shooter_anim_19,
    jump_shooter_anim_20,
    jump_shooter_anim_21,
    jump_shooter_anim_22,
    jump_shooter_anim_23,
    jump_shooter_anim_24,
    jump_shooter_anim_25,
    jump_shooter_anim_26,
    jump_shooter_anim_27,
};

u8 jump_shooter_debris[4] = { 13, 14, 15, 16 };

void (*jump_shooter_state_funcs[3])() = {
    func_8006A55C,
    jump_shooter_main,
    jump_shooter_despawn,
};

void (*jump_shooter_step_funcs[5])() = {
    enemy_hit_reaction,
    jump_shooter_resume_step,
    jump_shooter_fire,
    jump_shooter_walk,
    jump_shooter_jump,
};

void (*jump_shooter_fire_funcs[4])(struct MainObj*) = {
    jump_shooter_fire_aim,
    jump_shooter_fire_ready,
    jump_shooter_fire_shots,
    jump_shooter_fire_end,
};

void (*jump_shooter_walk_funcs[2])(struct MainObj*) = {
    jump_shooter_walk_start,
    func_8006AAB4,
};

void (*jump_shooter_jump_funcs[3])(struct MainObj*) = {
    jump_shooter_jump_launch,
    jump_shooter_jump_air,
    jump_shooter_jump_land,
};
