// MainObj, main_object_update_funcs[13]
// 8004C734..8004CF24
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_13_heavy_mech.h"
#include "main/objects.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"
#include "main/stage_objects.h"

// heavy_mech_state_funcs
extern void (*heavy_mech_state_funcs[])(struct MainObj*);
void heavy_mech_init(struct MainObj*);

void heavy_mech_explode(struct MainObj*);
void heavy_mech_despawn(struct MainObj* arg0);

// heavy_mech_step_funcs
void heavy_mech_resume_step(struct MainObj* arg0);
void heavy_mech_idle(struct MainObj* arg0);

void heavy_mech_throw(struct MainObj* arg0);

// heavy_mech_idle_funcs
void heavy_mech_idle_start(struct MainObj*);

extern void (*heavy_mech_idle_funcs[])(struct MainObj*);
extern void (*heavy_mech_throw_funcs[])(struct MainObj*);

void heavy_mech_face_player(struct AnimatedObj* self);

extern u8 heavy_mech_debris[];
extern void (*heavy_mech_step_funcs[])();
void heavy_mech_check_fall(struct MainObj* self);
void heavy_mech_check_catch(struct MainObj* self);

void heavy_mech_update(struct MainObj* self)
{
    heavy_mech_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_13_heavy_mech", heavy_mech_init);
#else
void heavy_mech_init(struct MainObj* self)
{
    self->hp = 0x10;
    self->contact_damage = 3;
    self->invincibility_timer = 0;
    self->collision_data = D_801068F0;
    self->bg_offset = g_Player.bg_offset;
    self->animation_table = (const u8* const*)heavy_mech_animations;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->unk16 = VISUAL_SATURN_LAYER(6);
    self->terrain_box = &heavy_mech_terrain_box;
    self->hurt_box = &heavy_mech_hurt_box;
    self->attack_box = &heavy_mech_attack_box;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    heavy_mech_face_player(ANIMATED_OBJECT(self));
    set_animation(self, 0);
    self->ext.main_13.unk80 = 0x8000;
    self->state = 1;
    self->ext.main_13.unk84 = 0;
    self->unk5 = 2;
    self->unk6 = 0;
}
#endif

// heavy_mech_main
void func_8004C860(struct MainObj* self)
{
    heavy_mech_check_fall(self);
    heavy_mech_check_catch(self);
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    heavy_mech_step_funcs[self->unk5](self);
    if (self->state != 2) {
        func_8002D9BC(self);
    }
    self->ext.main_13.saved_unk5 = self->unk5;
    if (func_8002DD04(self) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(9, heavy_mech_debris, self);
        drop_item(BASE_OBJECT(self), 8);
        self->unk7C = 0x20;
        self->unk7E = 6;
        self->on_screen = 0;
        self->state = 2;
    } else if (self->state != 2) {
        if (func_8002B1E8(BASE_OBJECT(self), 0x68, 0x68) == 0) {
            update_on_screen(BASE_OBJECT(self), 0x48, 0x48);
        } else {
            self->state = 3;
        }
    }
}

void heavy_mech_explode(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->state = 3;
    } else if (--self->unk7E == 0) {
        self->unk7E = 6;
        func_800AF878(self, 1, 24, 32);
    }
}

void heavy_mech_despawn(struct MainObj* self)
{
    self->ext.main_13.unk80 = 0;
    self->ext.main_13.unk84 = 0;
    self->ext.main_13.unk88 = 0;
    self->ext.main_13.saved_unk5 = 0;
    despawn_object(OBJECT_HEADER(self));
}

void heavy_mech_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_13.saved_unk5;
}

void heavy_mech_idle(struct MainObj* self)
{
    heavy_mech_idle_funcs[self->unk6](self);
}

void heavy_mech_idle_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->unk7C = 0x3C;
    self->unk6 = 1;
}

// heavy_mech_idle_wait

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004CA94(struct MainObj* arg0);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004CA94(struct MainObj* arg0)
{
    u8 roll;
    s32 dx;
    u32 animation;

    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    roll = get_random() & 0xF;
    dx = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    if (dx < 0)
        dx = -dx;
    if (roll < 2) {
        arg0->unk7C = 0x3C;
        return;
    }
    if (roll < 4) {
        arg0->ext.main_13.unk80 = 0x8001;
        return;
    }
    animation = roll < (dx < 0x81 ? 12 : 8) ? 2 : 1;
    heavy_mech_face_player(ANIMATED_OBJECT(arg0));
    set_animation(arg0, animation);
    arg0->ext.main_13.unk88 = animation;
    arg0->unk5 = 4;
    arg0->unk6 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_13_heavy_mech", func_8004CA94);
#endif

void heavy_mech_fall(struct MainObj* self)
{
    if (self->collision_flags & 8) {
        if (self->ext.main_13.unk80 == 0x8000) {
            heavy_mech_face_player(ANIMATED_OBJECT(self));
        }
        set_animation(self, 0);
        self->unk5 = 2;
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = 0;
        self->x_speed = 0;
        self->x_accel = 0;
        self->air_state = 0;
    } else {
        move_with_gravity(ANIMATED_OBJECT(self));
    }
    animate_object(ANIMATED_OBJECT(self));
}

void heavy_mech_throw(struct MainObj* self)
{
    heavy_mech_throw_funcs[self->unk6](self);
}

void heavy_mech_throw_anim(struct MainObj* self)
{
    struct ShotObj* shot;
    s8 event;

    animate_object(ANIMATED_OBJECT(self));
    event = self->animation_step.fields.event;
    switch (event) {
    case 1:
        set_animation(self, 0);
        self->ext.main_13.unk88 = 0;
        self->unk5 = 2;
        self->unk6 = 0;
        break;
    case 2:
        func_8001540C(2, SATURN_SOUND(0x31, 0x33), self);
        if (self->animation_step.fields.event != 0) {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 5;
                shot->unk2 = 0;
                shot->unk40 = self->unk40;
                shot->unk42 = self->unk42;
                shot->animation_table = (u32**)self->animation_table;
                shot->unk3C = (void*)self->sprite_frames;
                shot->unk15 = self->unk15;
                shot->bg_offset = self->bg_offset;
                shot->x_pos.val = self->x_pos.val;
                shot->y_pos.val = self->y_pos.val;
                shot->unk84.collision_state = &self->ext.main_13.unk80;
                if (self->ext.main_13.unk88 == event) {
                    shot->state = 3;
                }
            }
        }
        break;
    }
}

void heavy_mech_stomp(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        start_screen_shake_x(8, 4, 1);
    }
    if (self->animation_step.fields.event == 1) {
        if (self->ext.main_13.unk80 == 0x8000) {
            set_animation(self, 0);
        }
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void heavy_mech_check_fall(struct MainObj* self)
{
    if (self->air_state == 0 && !(self->collision_flags & 8)) {
        self->unk5 = 3;
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        self->x_accel = 0;
        self->air_state = 1;
    }
}

void heavy_mech_check_catch(struct MainObj* self)
{
    if (self->unk5 != 5 && self->ext.main_13.unk80 == 0x8001) {
        set_animation(self, 3);
        self->ext.main_13.unk80 = 0x8000;
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void heavy_mech_face_player(struct AnimatedObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = PLAYER_FACING_RIGHT;
    }
}

struct Unk_unk68 heavy_mech_hurt_box = { -21, -23, 39, 50 };

struct Unk_unk68 heavy_mech_attack_box = { -18, -21, 33, 46 };

struct Unk_unk68 heavy_mech_terrain_box = { 0, 27, 26, 3 };

union AnimationStep heavy_mech_anim_0[] = {
    { 12, 0, 1, 0x00 },
    { 12, 0, 1, 0x01 },
    { 12, 0, 1, 0x02 },
    { 12, 0, 1, 0x03 },
    { 12, 0, 1, 0x00 },
    { 12, 0, 1, 0x01 },
    { 12, 0, 1, 0x02 },
    { 12, 0, 1, 0x03 },
    { 12, 0, 1, 0x04 },
    { 12, 0, 1, 0x05 },
    { 12, 0, 1, 0x02 },
    { 12, 0, 1, 0x03 },
    { 12, 0, 1, 0x04 },
    { 12, 0, 1, 0x05 },
    { 12, 0, 1, 0x02 },
    { 12, 1, -15, 0x03 },
};

union AnimationStep heavy_mech_anim_1[] = {
    { 10, 0, 1, 0x06 },
    { 6, 0, 1, 0x07 },
    { 14, 0, 1, 0x08 },
    { 13, 0, 1, 0x09 },
    { 1, 2, 1, 0x0D },
    { 4, 0, 1, 0x0D },
    { 14, 0, 1, 0x0A },
    { 9, 0, 1, 0x0B },
    { 1, 1, 0, 0x0B },
};

union AnimationStep heavy_mech_anim_2[] = {
    { 10, 0, 1, 0x06 },
    { 8, 0, 1, 0x0E },
    { 16, 0, 1, 0x0F },
    { 8, 0, 1, 0x10 },
    { 1, 2, 1, 0x11 },
    { 1, 0, 1, 0x11 },
    { 14, 0, 1, 0x12 },
    { 9, 0, 1, 0x13 },
    { 1, 1, 0, 0x13 },
};

union AnimationStep heavy_mech_anim_3[] = {
    { 16, 0, 1, 0x1B },
    { 18, 2, 1, 0x1C },
    { 12, 0, 1, 0x1B },
    { 18, 2, 1, 0x1A },
    { 12, 0, 1, 0x1B },
    { 18, 2, 1, 0x1C },
    { 12, 0, 1, 0x1B },
    { 17, 2, 1, 0x1A },
    { 1, 1, 0, 0x1A },
};

union AnimationStep heavy_mech_anim_4[] = {
    { 3, 0, 1, 0x14 },
    { 16, 0, 1, 0x15 },
    { 4, 0, 1, 0x16 },
    { 5, 0, 1, 0x17 },
    { 6, 0, 1, 0x18 },
    { 6, 0, 1, 0x19 },
    { 1, 1, 0, 0x19 },
};

union AnimationStep heavy_mech_anim_5[] = {
    { 1, 1, 0, 0x0C },
};

union AnimationStep heavy_mech_anim_6[] = {
    { 1, 1, 0, 0x1D },
};

union AnimationStep heavy_mech_anim_7[] = {
    { 1, 1, 0, 0x1E },
};

union AnimationStep heavy_mech_anim_8[] = {
    { 1, 1, 0, 0x1F },
};

union AnimationStep heavy_mech_anim_9[] = {
    { 1, 1, 0, 0x20 },
};

union AnimationStep heavy_mech_anim_10[] = {
    { 1, 1, 0, 0x21 },
};

union AnimationStep heavy_mech_anim_11[] = {
    { 1, 1, 0, 0x22 },
};

union AnimationStep heavy_mech_anim_12[] = {
    { 1, 1, 0, 0x24 },
};

union AnimationStep heavy_mech_anim_13[] = {
    { 1, 1, 0, 0x25 },
};

union AnimationStep heavy_mech_anim_14[] = {
    { 1, 1, 0, 0x26 },
};

union AnimationStep heavy_mech_anim_15[] = {
    { 1, 1, 0, 0x23 },
};

union AnimationStep heavy_mech_anim_16[] = {
    { 1, 1, 0, 0x27 },
};

union AnimationStep heavy_mech_anim_17[] = {
    { 1, 1, 0, 0x28 },
};

union AnimationStep* heavy_mech_animations[] = {
    heavy_mech_anim_0,
    heavy_mech_anim_1,
    heavy_mech_anim_2,
    heavy_mech_anim_3,
    heavy_mech_anim_4,
    heavy_mech_anim_5,
    heavy_mech_anim_6,
    heavy_mech_anim_7,
    heavy_mech_anim_8,
    heavy_mech_anim_9,
    heavy_mech_anim_10,
    heavy_mech_anim_11,
    heavy_mech_anim_12,
    heavy_mech_anim_13,
    heavy_mech_anim_14,
    heavy_mech_anim_15,
    heavy_mech_anim_16,
    heavy_mech_anim_17,
};

u8 heavy_mech_debris[] = {
    0x06,
    0x07,
    0x08,
    0x09,
    0x0A,
    0x0B,
    0x0C,
    0x0D,
    0x0E,
    0x00,
    0x00,
    0x00,
};

void (*heavy_mech_state_funcs[])() = {
    heavy_mech_init,
    func_8004C860,
    heavy_mech_explode,
    heavy_mech_despawn,
};

void (*heavy_mech_step_funcs[])() = {
    enemy_hit_reaction,
    heavy_mech_resume_step,
    heavy_mech_idle,
    heavy_mech_fall,
    heavy_mech_throw,
    heavy_mech_stomp,
};

void (*heavy_mech_idle_funcs[])() = {
    heavy_mech_idle_start,
    func_8004CA94,
};

void (*heavy_mech_throw_funcs[])() = {
    heavy_mech_throw_anim,
};
