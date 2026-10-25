// MainObj, main_object_update_funcs[12]
// 8004B8C0..8004C734
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_12_hover_sentry.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/1CF60.h"
#include "main/misc/misc_00_static_sprite.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1CF60.h"
#include "main/misc/misc_00_static_sprite.h"
#endif

extern u8 hover_sentry_debris[];

void hover_sentry_check_player_near(struct MainObj*);

void hover_sentry_main(struct MainObj* arg0);
void hover_sentry_despawn(struct MainObj*);

// hover_sentry_step_funcs
extern void (*hover_sentry_step_funcs[])(struct MainObj*);
void hover_sentry_resume_step(struct MainObj* arg0);
void hover_sentry_bob(struct MainObj* arg0);
void hover_sentry_alert(struct MainObj* arg0);

extern void (*hover_sentry_state_funcs[])(struct MainObj*);

#if defined(MMX4_PC) || defined(MMX4_SATURN)
extern struct Unk_unk68 D_800FB684, D_800FB688, D_800FB68C;
extern struct Unk_unk68 D_800FB694, D_800FB698;
void hover_sentry_face_player(struct MainObj* self);
#endif

void hover_sentry_update(struct MainObj* self)
{
    hover_sentry_state_funcs[self->state](self);
}

// hover_sentry_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
s32 func_8001540C(s32 arg0, s32 arg1, void* arg2);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004B8FC(struct MainObj* arg0);
void func_8004BCFC(struct MainObj* arg0);
void func_8004BF5C(struct MainObj* arg0);
void func_8004C210(struct MainObj* self);
void func_8004C394(struct MainObj* self);
void func_8004C56C(struct MainObj* self);
extern union AnimationStep* hover_sentry_animations[];
extern struct Unk_unk68 D_800FB690;
extern struct Unk_unk68 D_800FB69C;
extern struct Unk_unk68 D_800FB6A0;
extern struct Unk_unk68 D_800FB6A4;
extern struct Unk_unk68 D_80106870[];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004B8FC(struct MainObj* arg0)
{
    arg0->state = 1;
    arg0->unk6 = 0;
    arg0->unk7C = 0x90;
    arg0->invincibility_timer = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->animation_table = (const u8* const*)hover_sentry_animations;
    arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : PLAYER_FACING_RIGHT;
    arg0->ext.main_12.unk88 = 0;
    arg0->air_state = 0;
    arg0->ext.main_12.unk81 = 0;
    arg0->collision_data = D_80106870;

    switch (arg0->unk2) {
    case 0:
        arg0->hp = 3;
        arg0->contact_damage = 3;
        arg0->unk5 = 2;
        arg0->y_speed = -0x8000;
        arg0->gravity = -0x800;
        arg0->unk16 = VISUAL_SATURN_LAYER(6);
        arg0->terrain_box = &D_800FB684;
        arg0->hurt_box = &D_800FB68C;
        arg0->attack_box = &D_800FB688;
        arg0->x_speed = 0;
        arg0->x_accel = 0;
        set_animation(ANIMATED_OBJECT(arg0), 0);
        break;
    case 1:
        arg0->hp = 3;
        arg0->contact_damage = 3;
        arg0->unk5 = 6;
        arg0->ext.main_12.unk86 = arg0->y_pos.u.hi;
        arg0->y_speed = 0x4000;
        arg0->x_speed = 0;
        arg0->x_accel = 0;
        arg0->gravity = 0;
        arg0->unk16 = VISUAL_SATURN_LAYER(6);
        arg0->terrain_box = &D_800FB690;
        arg0->hurt_box = NULL;
        arg0->attack_box = NULL;
        arg0->ext.main_12.unk8A = 0;
        set_animation(ANIMATED_OBJECT(arg0), 3);
        break;
    case 2:
        arg0->hp = 3;
        arg0->contact_damage = 3;
        arg0->unk7E = 0;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        arg0->ext.main_12.unk86 = arg0->y_pos.u.hi;
        arg0->unk16 = VISUAL_SATURN_LAYER(6);
        arg0->terrain_box = NULL;
        arg0->hurt_box = NULL;
        arg0->attack_box = NULL;
        arg0->ext.main_12.unk8A = 0;
        set_animation(ANIMATED_OBJECT(arg0), 2);
        break;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_12_hover_sentry", func_8004B8FC);
#endif

void hover_sentry_main(struct MainObj* self)
{
    s32 result;
    s8 mode = self->unk5;

    if (mode != 5 || self->unk6 != 4) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    hover_sentry_check_player_near(self);
    hover_sentry_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    result = func_8002DD04(self);
    if (result < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(5, hover_sentry_debris, self);
        drop_item(BASE_OBJECT(self), 0xE);
    } else {
        if (result > 0) {
            SP_CUR_MAIN_OBJ->ext.main_12.saved_unk5 = self->unk5;
        }
        if (func_8002B160(BASE_OBJECT(self)) == 0) {
            is_on_screen(BASE_OBJECT(self));
            return;
        }
    }
    self->state++;
}

void hover_sentry_resume_step(struct MainObj* self)
{
    self->unk5 = SP_CUR_MAIN_OBJ->ext.main_12.saved_unk5;
}

void hover_sentry_bob(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if (SP_CUR_MAIN_OBJ->ext.main_12.unk88 == 0) {
        if (self->y_speed >= 0) {
            self->y_speed = FIXED(0.5);
            self->gravity = -self->gravity;
            SP_CUR_MAIN_OBJ->ext.main_12.unk88 = 1;
        }
    } else if (self->y_speed < 0) {
        self->y_speed = FIXED(-0.5);
        self->gravity = -self->gravity;
        SP_CUR_MAIN_OBJ->ext.main_12.unk88 = 0;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void hover_sentry_alert(struct MainObj* self)
{
    self->unk5 = 4;
    self->unk6 = 0;
    self->unk7 = 0;
    self->unk7E = 8;
    animate_object(self);
}

// hover_sentry_attack_0
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004BCFC(struct MainObj* arg0)
{
    s32 transition = 0;

    switch (arg0->unk6) {
    case 0:
        if (arg0->unk7E-- != 0)
            return;
        arg0->unk6 = 1;
        arg0->unk7 = 0;
        arg0->air_state = 1;
        arg0->ext.main_12.unk86 = arg0->y_pos.u.hi;
        arg0->y_speed = 0x80000;
        arg0->x_speed = 0;
        arg0->x_accel = 0;
        if (arg0->unk2 == 2) {
            if ((get_random() & 3) == 0) {
                arg0->ext.main_12.unk80 = 0x10;
                arg0->ext.main_12.unk81 = 1;
            } else {
                arg0->ext.main_12.unk80 = 0xF;
                arg0->ext.main_12.unk81 = 0;
            }
        } else {
            arg0->ext.main_12.unk80 = get_random() & 0xF;
        }
        arg0->gravity = 0;
        arg0->terrain_box = &D_800FB690;
        arg0->hurt_box = &D_800FB698;
        arg0->attack_box = &D_800FB694;
        set_animation(ANIMATED_OBJECT(arg0), 2);
        break;

    case 1: {
        struct Unk_unk68* bounds;
        s16 x;
        s16 y;

        move_with_gravity(ANIMATED_OBJECT(arg0));
        bounds = arg0->terrain_box;
        x = arg0->x_pos.i.hi + bounds->unk0;
        y = arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3 + 4;
        if (func_8002D724(PLAYER_OBJECT(arg0), x, y) != 0x24) {
            arg0->unk6 = 2;
            set_animation(ANIMATED_OBJECT(arg0), 9);
        } else if (arg0->unk7 == 0) {
            spawn_common_effect(arg0, 1);
            arg0->unk7 = 1;
            func_8001540C(2, SATURN_SOUND(0x25, 0x1F), arg0);
        }
        transition = (u8)arg0->collision_flags & 4;
        break;
    }

    case 2:
        move_with_gravity(ANIMATED_OBJECT(arg0));
        transition = arg0->y_pos.i.hi < g_Player.y_pos.i.hi;
        break;
    }

    if (transition) {
        hover_sentry_face_player(arg0);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
        set_animation(ANIMATED_OBJECT(arg0), 0xA);
    }
    animate_object(ANIMATED_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_12_hover_sentry", func_8004BCFC);
#endif

// hover_sentry_attack_1
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004BF5C(struct MainObj* arg0)
{
    switch (arg0->unk6) {
    case 0:
        if (arg0->animation_step.fields.event != 0) {
            arg0->unk6 = 1;
            set_animation(ANIMATED_OBJECT(arg0), 6);
        }
        break;
    case 1:
        if (arg0->animation_step.fields.event != 0) {
            arg0->unk6 = 2;
            set_animation(ANIMATED_OBJECT(arg0), 7);
            arg0->terrain_box = &D_800FB69C;
            arg0->hurt_box = &D_800FB6A4;
            arg0->attack_box = &D_800FB6A0;
        }
        break;
    case 2:
        if (arg0->animation_step.fields.event != 0) {
            arg0->unk6 = 3;
            arg0->unk7E = 10;
        }
        break;
    case 3:
        if (--arg0->unk7E == 0) {
            u8 direction;

            arg0->unk6 = 4;
            arg0->ext.main_12.unk8C = 0;
            direction = (u8)angle_to_object(
                OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
            if ((u8)(direction - 8) < 0x10) {
                arg0->unk15 = 0;
                if (direction < 0xC)
                    direction = 0xC;
                if (direction >= 0x15)
                    direction = 0x14;
            } else {
                arg0->unk15 = PLAYER_FACING_RIGHT;
                if ((u8)(direction - 0x18) < 4)
                    direction = 0x1C;
                else if ((u8)(direction - 5) < 3)
                    direction = 4;
            }
            set_velocity_from_angle(MOVING_OBJECT(arg0), direction);
            arg0->x_accel = 0;
            arg0->gravity = 0;
            arg0->x_speed *= 6;
            arg0->y_speed *= 6;
            set_animation(ANIMATED_OBJECT(arg0), 8);
        }
        break;
    case 4: {
        struct Unk_unk68* bounds;
        s16 x;
        s16 y;

        move_with_gravity(ANIMATED_OBJECT(arg0));
        bounds = arg0->terrain_box;
        x = arg0->x_pos.i.hi + bounds->unk0 + bounds->unk2;
        y = arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3;
        if (func_8002D724(PLAYER_OBJECT(arg0), x, y) == 0x24) {
            s16 tile = x / 16;
            if ((u16)tile != arg0->ext.main_12.unk8C) {
                spawn_common_effect(arg0, 1);
                func_8001540C(2, SATURN_SOUND(0x25, 0x1F), arg0);
                arg0->ext.main_12.unk8C = tile;
            }
        }
        break;
    }
    }
    animate_object(ANIMATED_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_12_hover_sentry", func_8004BF5C);
#endif

// hover_sentry_attack_2
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004C210(struct MainObj* self)
{
    switch (self->unk6) {
    case 0:
        move_with_gravity(ANIMATED_OBJECT(self));
        if ((s16)SP_CUR_MAIN_OBJ->ext.main_12.unk86 - self->y_pos.i.hi >= 16) {
            self->unk6 = 1;
            self->y_speed = FIXED(4);

            get_random();
            SP_CUR_MAIN_OBJ->ext.main_12.unk8A = 1;
            self->unk7C = 5;
            self->hurt_box = &D_800FB698;
            self->attack_box = &D_800FB694;
            set_animation(self, 5);
        }
        animate_object(ANIMATED_OBJECT(self));
        break;
    case 1:
        move_with_gravity(ANIMATED_OBJECT(self));
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.event < 0) {
            hover_sentry_face_player(self);
            self->unk6 = 2;
            set_animation(self, 2);
        }
        break;
    case 2:
        move_with_gravity(ANIMATED_OBJECT(self));
        animate_object(ANIMATED_OBJECT(self));
        self->unk7C = (u16)self->unk7C - 1;
        if (self->unk7C == 0) {
            hover_sentry_face_player(self);
            self->unk5 = 5;
            self->unk6 = 0;
            self->unk7 = 0;
            set_animation(self, 10);
        }
        break;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_12_hover_sentry", func_8004C210);
#endif

// hover_sentry_attack_3
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004C394(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->x_speed = (self->unk15 & PLAYER_FACING_RIGHT) ? FIXED(4) : FIXED(-4);
        self->x_accel = -0x2000;
        self->unk7C = 0x90;
        self->terrain_box = &D_800FB684;
        self->hurt_box = &D_800FB68C;
        self->attack_box = &D_800FB688;
        self->y_speed = 0;
        self->gravity = 0;
        set_animation(self, 1);
    } else {
        if ((self->unk15 & PLAYER_FACING_RIGHT) ? self->x_speed < 0 : self->x_speed >= 0) {
            s32 distance = self->y_pos.i.hi - g_Player.y_pos.i.hi;
            if (distance < 0) {
                distance = -distance;
            }
            self->unk15 = (self->x_pos.val < g_Player.x_pos.val && (s16)distance < 32) ? PLAYER_FACING_RIGHT : 0;
            self->unk6 = 0;
            if ((get_random() & 3) == 0) {
                self->unk5 = 4;
                self->unk6 = 0;
                self->unk7 = 0;
                self->unk7E = 1;
                if ((get_random() & 0x1F) == 0) {
                    SP_CUR_MAIN_OBJ->ext.main_12.unk81 = 1;
                }
            }
        }
        if (self->collision_flags & ((self->unk15 & PLAYER_FACING_RIGHT) ? 1 : 2)) {
            self->unk15 ^= PLAYER_FACING_RIGHT;
        }
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_12_hover_sentry", func_8004C394);
#endif

// hover_sentry_attack_4
void func_8004C56C(struct MainObj* self)
{
    if (self->unk6 == 0) {
        struct Unk_unk68* bounds;
        s16 x, y;

        move_with_gravity(ANIMATED_OBJECT(self));
        animate_object(ANIMATED_OBJECT(self));
        bounds = self->terrain_box;
        x = (u16)self->x_pos.u.hi + bounds->unk0;
        y = (u16)self->y_pos.u.hi + bounds->unk1 + bounds->unk3;
        if (self->unk7 == 0 && ((s32(*)(struct PlayerObj*, s16, s16))func_8002D724)(PLAYER_OBJECT(self), x, y) == 0x24) {
            spawn_common_effect(self, 1);
            self->unk7 = 1;
            func_8001540C(2, SATURN_SOUND(0x25, 0x1F), self);
        }
        if (self->collision_flags != 0) {
            self->unk5 = 7;
            self->unk6 = 0;
            self->unk7 = 0;
            self->air_state = 0;
        }
    }
}

void hover_sentry_despawn(struct MainObj* self)
{
    if (self->unk2 == 2) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    despawn_object(OBJECT_HEADER(self));
}

void hover_sentry_face_player(struct MainObj* self)
{
    if (self->x_pos.val < g_Player.x_pos.val) {
        self->unk15 = PLAYER_FACING_RIGHT;
    } else {
        self->unk15 = 0;
    }
}

void hover_sentry_check_player_near(struct MainObj* self)
{
    s16 distance;

    if (self->unk7C != 0) {
        if (self->unk5 == 2) {
            distance = (g_Player.x_pos.i.hi - self->x_pos.i.hi) < 0 ? self->x_pos.i.hi - g_Player.x_pos.i.hi : g_Player.x_pos.i.hi - self->x_pos.i.hi;
            if (distance < 0x90) {
                self->unk5 = 3;
                self->unk6 = 0;
            }
        }
    }
}

union AnimationStep hover_sentry_anim_0[] = {
    { 10, 0, 1, 0x00 },
    { 28, 0, 1, 0x01 },
    { 15, 0, -2, 0x02 },
};

union AnimationStep hover_sentry_anim_1[] = {
    { 4, 0, 1, 0x03 },
    { 4, 0, 1, 0x04 },
    { 4, 0, 1, 0x05 },
    { 4, 0, -3, 0x06 },
};

union AnimationStep hover_sentry_anim_2[] = {
    { 1, 0, 1, 0x07 },
    { 3, 0, -1, 0x07 },
};

union AnimationStep hover_sentry_anim_3[] = {
    { 6, 0, 1, 0x08 },
    { 6, 0, 1, 0x09 },
    { 6, 0, -2, 0x0A },
};

union AnimationStep hover_sentry_anim_4[] = {
    { 5, 0, 1, 0x0B },
    { 6, 0, 1, 0x0C },
    { 6, 1, -2, 0x0D },
};

union AnimationStep hover_sentry_anim_5[] = {
    { 6, 0, 1, 0x0E },
    { 6, 0, 1, 0x0F },
    { 5, 1, 1, 0x10 },
    { 4, 1, 1, 0x11 },
    { 6, 1, 1, 0x12 },
    { 6, -127, 1, 0x0B },
    { 6, -127, 1, 0x0C },
    { 6, 1, 1, 0x13 },
    { 6, 0, 1, 0x14 },
    { 5, 0, 1, 0x15 },
    { 4, 0, -10, 0x16 },
};

union AnimationStep hover_sentry_anim_6[] = {
    { 8, 0, 1, 0x17 },
    { 12, 1, -1, 0x18 },
};

union AnimationStep hover_sentry_anim_7[] = {
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 8, 0, 1, 0x1B },
    { 1, 1, -1, 0x1B },
};

union AnimationStep hover_sentry_anim_8[] = {
    { 2, 0, 1, 0x1C },
    { 2, 0, 1, 0x1D },
    { 2, 0, 1, 0x1E },
    { 2, 0, 1, 0x1F },
    { 2, 0, 1, 0x20 },
    { 2, 0, 1, 0x1B },
    { 2, 0, -2, 0x20 },
};

union AnimationStep hover_sentry_anim_9[] = {
    { 2, 0, 1, 0x0B },
    { 2, 0, -1, 0x0C },
};

union AnimationStep hover_sentry_anim_10[] = {
    { 6, 0, 1, 0x0D },
    { 1, 1, -1, 0x0D },
};

union AnimationStep hover_sentry_anim_11[] = {
    { 1, 0, 0, 0x21 },
};

union AnimationStep hover_sentry_anim_12[] = {
    { 1, 0, 0, 0x22 },
};

union AnimationStep hover_sentry_anim_13[] = {
    { 1, 0, 0, 0x23 },
};

union AnimationStep hover_sentry_anim_14[] = {
    { 1, 0, 0, 0x24 },
};

union AnimationStep hover_sentry_anim_15[] = {
    { 1, 0, 1, 0x25 },
    { 1, 0, 1, 0x26 },
    { 1, 0, 1, 0x25 },
    { 1, 0, -3, 0x27 },
};

union AnimationStep* hover_sentry_animations[] = {
    hover_sentry_anim_0,
    hover_sentry_anim_1,
    hover_sentry_anim_2,
    hover_sentry_anim_3,
    hover_sentry_anim_4,
    hover_sentry_anim_5,
    hover_sentry_anim_6,
    hover_sentry_anim_7,
    hover_sentry_anim_8,
    hover_sentry_anim_9,
    hover_sentry_anim_10,
    hover_sentry_anim_11,
    hover_sentry_anim_12,
    hover_sentry_anim_13,
    hover_sentry_anim_14,
    hover_sentry_anim_15,
};

u8 hover_sentry_debris[] = {
    0x0B,
    0x0C,
    0x0D,
    0x0E,
    0x0F,
    0x00,
    0x00,
    0x00,
};

struct Unk_unk68 D_800FB684 = { -2, 3, 18, 4 };

struct Unk_unk68 D_800FB688 = { -12, -2, 21, 11 };

struct Unk_unk68 D_800FB68C = { -16, -9, 34, 20 };

struct Unk_unk68 D_800FB690 = { 0, -5, 7, 17 };

struct Unk_unk68 D_800FB694 = { -7, -18, 13, 28 };

struct Unk_unk68 D_800FB698 = { -8, -24, 15, 38 };

struct Unk_unk68 D_800FB69C = { -5, 0, 17, 9 };

struct Unk_unk68 D_800FB6A0 = { -10, -15, 11, 31 };

struct Unk_unk68 D_800FB6A4 = { -15, -27, 25, 54 };

void (*hover_sentry_state_funcs[])(struct MainObj*) = {
    func_8004B8FC,
    hover_sentry_main,
    hover_sentry_despawn,
};

void (*hover_sentry_step_funcs[9])() = {
    enemy_hit_reaction,
    hover_sentry_resume_step,
    hover_sentry_bob,
    hover_sentry_alert,
    func_8004BCFC,
    func_8004BF5C,
    func_8004C210,
    func_8004C394,
    func_8004C56C,
};

u16 D_800FB6D8[18] = {
    0x0010,
    0x0010,
    0x0010,
    0x0010,
    0x0040,
    0x0040,
    0x0040,
    0x0040,
    0x0040,
    0x0040,
    0x0080,
    0x0080,
    0x0080,
    0x0080,
    0x00A0,
    0x00A0,
    0x00C0,
    0x0000,
};
