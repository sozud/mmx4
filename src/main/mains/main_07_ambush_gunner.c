// MainObj, main_object_update_funcs[7]
// 800473C8..80047C88
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_07_ambush_gunner.h"
#include "main/objects.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/items/item_01_stage_block.h"
#include "main/misc/misc_02_rubble.h"
#include "main/object_motion.h"
#include "main/collision_bounds.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/collision_bounds.h"
#endif

extern u8 ambush_gunner_emerge_particles[8];

extern u8 ambush_gunner_debris[];

void ambush_gunner_main(struct MainObj* arg0);
void ambush_gunner_despawn(struct MainObj* arg0);

// ambush_gunner_step_funcs
extern void (*ambush_gunner_step_funcs[5])();

void ambush_gunner_emerge(struct MainObj* arg0);
void ambush_gunner_aim(struct MainObj* arg0);

void ambush_gunner_emerge_burst(struct MainObj*);
void ambush_gunner_emerge_finish(struct MainObj*);

// ambush_gunner_aim_funcs
void ambush_gunner_aim_start(struct MainObj*);

extern void (*ambush_gunner_state_funcs[])(struct MainObj*);
extern void (*ambush_gunner_emerge_funcs[])(struct MainObj*);
extern void (*ambush_gunner_aim_funcs[])(struct MainObj*);

void ambush_gunner_update(struct MainObj* self)
{
    ambush_gunner_state_funcs[self->state](self);
}

// ambush_gunner_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80047404(struct MainObj* arg0);
void func_80047818(struct MainObj* arg0);
extern struct Unk_unk68 ambush_gunner_terrain_box;
extern union AnimationStep* ambush_gunner_animations[];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80047404(struct MainObj* arg0)
{
    u8 kind = (u8)arg0->unk2;

    arg0->hp = 6;
    arg0->contact_damage = 3;
    arg0->invincibility_timer = 0;
    arg0->collision_data = D_80106670;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->animation_table = (const u8* const*)ambush_gunner_animations;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->terrain_box = NULL;
    arg0->attack_box = &ambush_gunner_terrain_box;
    arg0->hurt_box = &ambush_gunner_terrain_box;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;

    if (kind == 1) {
        set_animation(arg0, 1);
        arg0->unk5 = 3;
        arg0->unk15 = PLAYER_FACING_RIGHT;
        arg0->ext.main_7.unk90 = 1;
    } else if (kind >= 2 && kind <= 7) {
        set_animation(arg0, 0);
        arg0->unk5 = 2;
        arg0->unk7A = 1;
        arg0->invincibility_timer = 1;
        arg0->unk15 = (kind & 1) ? PLAYER_FACING_RIGHT : 0;
        arg0->ext.main_7.unk80 = kind >= 6;
        arg0->ext.main_7.unk84 = kind >= 6 ? 0x28
            : kind >= 4                    ? 0x8C
                                           : 0x64;
        arg0->ext.main_7.unk90 = 0;
    } else {
        set_animation(arg0, 1);
        arg0->unk5 = 3;
        arg0->unk15 = 0;
        arg0->ext.main_7.unk90 = 1;
    }
    arg0->state = 1;
    arg0->unk6 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_07_ambush_gunner", func_80047404);
#endif

void ambush_gunner_main(struct MainObj* self)
{
    s32 hit;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    ambush_gunner_step_funcs[self->unk5](self);
    if (self->ext.main_7.unk90 != 0) {
        func_8002D9BC(self);
        self->ext.main_7.saved_unk5 = self->unk5;
        hit = func_8002DD04(self);
        if (hit < 0) {
            spawn_explosion(BASE_OBJECT(self));
            spawn_debris(5, ambush_gunner_debris, self);
            if (!(self->unk2 & 1)) {
                func_800BF638(BASE_OBJECT(self), 0xE, self->x_pos.u.hi - 0xA, self->y_pos.i.hi);
            } else {
                func_800BF638(BASE_OBJECT(self), 0xE, self->x_pos.u.hi + 0xA, self->y_pos.i.hi);
            }
            self->state = 2;
            return;
        }
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
        if (self->unk5 != 2 || self->unk6 != 0) {
            update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
        }
    } else {
        self->state = 2;
    }
}

void ambush_gunner_despawn(struct MainObj* self)
{
    self->unk7A = 0;
    self->ext.main_7.unk80 = 0;
    self->ext.main_7.unk84 = 0;
    self->ext.main_7.saved_x_velocity = 0;
    self->ext.main_7.saved_y_velocity = 0;
    self->ext.main_7.unk90 = 0;
    self->ext.main_7.saved_unk5 = 0;
    self->invincibility_timer = 0;
    despawn_object(OBJECT_HEADER(self));
}

void ambush_gunner_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_7.saved_unk5;
}

void ambush_gunner_emerge(struct MainObj* self)
{
    ambush_gunner_emerge_funcs[self->unk6](self);
}

// ambush_gunner_emerge_wait
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_07_ambush_gunner", func_80047818);
#else
void func_80047818(struct MainObj* arg0)
{
    if ((arg0->unk15 == 0 && arg0->x_pos.val > g_Player.x_pos.val) || (arg0->unk15 != 0 && arg0->x_pos.val < g_Player.x_pos.val)) {
        if (arg0->ext.main_7.unk80 == 0) {
            if (ABS(arg0->x_pos.i.hi, g_Player.x_pos.i.hi) < (s16)arg0->ext.main_7.unk84) {
                arg0->unk7A = 0;
                arg0->unk6 = 1;
            }
        } else if (ABS(arg0->x_pos.i.hi, g_Player.x_pos.i.hi) > (s16)arg0->ext.main_7.unk84) {
            arg0->unk7A = 0;
            arg0->unk6 = 1;
        }
    }
}
#endif

void ambush_gunner_emerge_burst(struct MainObj* self)
{
    self->invincibility_timer = 0;
    self->ext.main_7.unk90 = 1;
    spawn_rubble(8, ambush_gunner_emerge_particles, self,
        self->unk15 == 0 ? FIXED(-3) : FIXED(3));
    func_8001540C(2, SATURN_SOUND(0x15, 0x14), self);
    animate_object(ANIMATED_OBJECT(self));
    self->unk6 = 2;
}

void ambush_gunner_emerge_finish(struct MainObj* self)
{
    if (self->animation_step.fields.event == 2) {
        func_8001540C(2, SATURN_SOUND(0x16, 0x15), self);
    }
    if (self->animation_step.fields.event == 1) {
        set_animation(self, 1);
        self->unk5 = 3;
        self->unk6 = 0;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void ambush_gunner_aim(struct MainObj* self)
{
    ambush_gunner_aim_funcs[self->unk6](self);
}

void ambush_gunner_aim_start(struct MainObj* self)
{
    self->unk7C = 0x28;
    self->unk6 = 1;
}

void ambush_gunner_aim_wait(struct MainObj* self)
{
    if (self->unk7C == 0) {
        set_velocity_from_angle(
            MOVING_OBJECT(self),
            angle_to_object(
                OBJECT_HEADER(self),
                OBJECT_HEADER(&g_Player))
                & 0xFF);

        if ((self->unk15 == 0 && self->x_speed < 0) || (self->unk15 != 0 && self->x_speed > 0)) {
            self->ext.main_7.saved_x_velocity = self->x_speed;
            self->ext.main_7.saved_y_velocity = self->y_speed;
            set_animation(self, 2);
            self->unk5 = 4;
            self->unk6 = 2;
        } else {
            self->unk7C = 0x3C;
        }

        self->x_speed = 0;
        self->y_speed = 0;
    } else {
        self->unk7C--;
    }
}

void ambush_gunner_fire(struct MainObj* self)
{
    if (self->animation_step.fields.event == 2) {
        struct ShotObj* shot;

        func_8001540C(2, SATURN_SOUND(0x17, 0x16), self);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 2;
            shot->unk40 = self->unk40;
            shot->unk42 = self->unk42;
            shot->animation_table = (u32**)self->animation_table;
            shot->unk3C = (void*)self->sprite_frames;
            shot->unk2 = (u8)self->unk2 & 1;
            shot->unk15 = self->unk15;
            shot->bg_offset = self->bg_offset;
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
            set_velocity_from_angle(MOVING_OBJECT(self),
                angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)) & 0xFF);
            if ((self->unk15 == 0 && self->x_speed < 0) || (self->unk15 != 0 && self->x_speed > 0)) {
                shot->x_vel.val = self->x_speed;
                shot->y_vel.val = self->y_speed;
            } else {
                shot->x_vel.val = self->ext.main_7.saved_x_velocity;
                shot->y_vel.val = self->ext.main_7.saved_y_velocity;
            }
            self->x_speed = 0;
            self->y_speed = 0;
        }
    }
    if (self->animation_step.fields.event == 1) {
        set_animation(self, 1);
        self->unk5 = 3;
        self->unk6 = 0;
    }
    animate_object(ANIMATED_OBJECT(self));
}

struct Unk_unk68 ambush_gunner_terrain_box = { -13, -12, 25, 24 };

union AnimationStep ambush_gunner_anim_0[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x02 },
    { 6, 0, 1, 0x03 },
    { 6, 0, 1, 0x04 },
    { 4, 0, 1, 0x05 },
    { 5, 0, 1, 0x06 },
    { 1, 0, 1, 0x07 },
    { 1, 0, 1, 0x08 },
    { 1, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 2, 0, 1, 0x0C },
    { 2, 0, 1, 0x0D },
    { 1, 2, 1, 0x0E },
    { 5, 0, 1, 0x0E },
    { 3, 0, 1, 0x0F },
    { 3, 0, 1, 0x10 },
    { 3, 0, 1, 0x11 },
    { 6, 0, 1, 0x0E },
    { 1, 0, 1, 0x12 },
    { 1, 0, 1, 0x13 },
    { 1, 0, 1, 0x14 },
    { 6, 0, 1, 0x15 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 6, 0, 1, 0x18 },
    { 1, 0, 1, 0x19 },
    { 1, 0, 1, 0x1A },
    { 6, 0, 1, 0x1B },
    { 5, 0, 1, 0x1C },
    { 8, 0, 1, 0x1D },
    { 5, 0, 1, 0x1C },
    { 4, 0, 1, 0x1B },
    { 1, 1, 0, 0x1B },
};

union AnimationStep ambush_gunner_anim_1[] = {
    { 1, 1, 0, 0x1B },
};

union AnimationStep ambush_gunner_anim_2[] = {
    { 2, 0, 1, 0x1E },
    { 2, 0, 1, 0x1F },
    { 1, 0, 1, 0x20 },
    { 1, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x1B },
    { 2, 0, 1, 0x1E },
    { 2, 0, 1, 0x1F },
    { 1, 0, 1, 0x20 },
    { 1, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x1B },
    { 2, 0, 1, 0x23 },
    { 2, 0, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 1, 0, 1, 0x26 },
    { 1, 0, 1, 0x27 },
    { 2, 0, 1, 0x1C },
    { 2, 0, 1, 0x23 },
    { 2, 0, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 1, 0, 1, 0x26 },
    { 1, 0, 1, 0x27 },
    { 1, 2, 1, 0x28 },
    { 1, 0, 1, 0x29 },
    { 1, 0, 1, 0x2A },
    { 2, 0, 1, 0x2B },
    { 3, 0, 1, 0x2C },
    { 4, 0, 1, 0x2D },
    { 4, 0, 1, 0x2E },
    { 1, 1, 0, 0x2E },
};

union AnimationStep ambush_gunner_anim_3[] = {
    { 1, 1, 0, 0x34 },
};

union AnimationStep ambush_gunner_anim_4[] = {
    { 1, 1, 0, 0x35 },
};

union AnimationStep ambush_gunner_anim_5[] = {
    { 1, 1, 0, 0x36 },
};

union AnimationStep ambush_gunner_anim_6[] = {
    { 2, 0, 1, 0x37 },
    { 3, 0, 1, 0x38 },
    { 3, 0, 1, 0x39 },
    { 3, 0, 1, 0x3A },
    { 2, 0, 1, 0x3B },
    { 1, 0, 1, 0x3C },
    { 1, 0, 1, 0x3D },
    { 1, 1, 0, 0x3E },
};

union AnimationStep ambush_gunner_anim_7[] = {
    { 1, 1, 0, 0x3F },
};

union AnimationStep ambush_gunner_anim_8[] = {
    { 1, 0, 1, 0x2F },
    { 1, 0, 1, 0x30 },
    { 1, 0, 1, 0x31 },
    { 1, 0, 1, 0x32 },
    { 1, 1, -4, 0x33 },
};

union AnimationStep* ambush_gunner_animations[] = {
    ambush_gunner_anim_0,
    ambush_gunner_anim_1,
    ambush_gunner_anim_2,
    ambush_gunner_anim_3,
    ambush_gunner_anim_4,
    ambush_gunner_anim_5,
    ambush_gunner_anim_6,
    ambush_gunner_anim_7,
    ambush_gunner_anim_8,
};

u8 ambush_gunner_debris[] = {
    0x03,
    0x04,
    0x05,
    0x06,
    0x07,
    0x00,
    0x00,
    0x00,
};

u8 ambush_gunner_emerge_particles[] = {
    0x01,
    0x02,
    0x03,
    0x04,
    0x01,
    0x02,
    0x03,
    0x04,
};

void (*ambush_gunner_state_funcs[])(struct MainObj*) = {
    func_80047404,
    ambush_gunner_main,
    ambush_gunner_despawn,
};

void (*ambush_gunner_step_funcs[5])() = {
    enemy_hit_reaction,
    ambush_gunner_resume_step,
    ambush_gunner_emerge,
    ambush_gunner_aim,
    ambush_gunner_fire,
};

void (*ambush_gunner_emerge_funcs[3])() = {
    func_80047818,
    ambush_gunner_emerge_burst,
    ambush_gunner_emerge_finish,
};

void (*ambush_gunner_aim_funcs[2])(struct MainObj*) = {
    ambush_gunner_aim_start,
    ambush_gunner_aim_wait,
};
