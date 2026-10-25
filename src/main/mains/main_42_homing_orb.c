// MainObj, main_object_update_funcs[42]
// 80062D60..800631C8
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_42_homing_orb.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"

void homing_orb_main(struct MainObj*);
void homing_orb_despawn(struct MainObj* arg0);

// homing_orb_step_funcs
void homing_orb_start_idle(struct MainObj* arg0);
void homing_orb_wait(struct MainObj* arg0);

void homing_orb_leave(struct MainObj* arg0);

extern void (*homing_orb_state_funcs[])(struct MainObj*);

void homing_orb_update(struct MainObj* self)
{
    homing_orb_state_funcs[self->state](self);
}

// homing_orb_init

extern struct Unk_unk68 D_80107574[];
extern s8 homing_orb_hurt_box[4];
extern s8 homing_orb_attack_box[4];
extern union AnimationStep* homing_orb_animations[7];

void func_80062D9C(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk15 = 0;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->hp = 3;
    arg0->contact_damage = 3;
    arg0->collision_data = D_80107574;
    arg0->animation_table = (const u8* const*)homing_orb_animations;
    arg0->attack_box = homing_orb_hurt_box;
    arg0->hurt_box = homing_orb_attack_box;
    arg0->terrain_box = NULL;
    arg0->invincibility_timer = 0;
    arg0->animation_table = (const u8* const*)homing_orb_animations;
    arg0->x_speed = 0;
    arg0->x_accel = 0;
    arg0->y_speed = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->unk7C = 0xB4;
    arg0->ext.main_42.background_relative = 0;
    arg0->ext.main_42.unk84 = NULL;
    set_animation(arg0, 0);
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}

void homing_orb_start_idle(struct MainObj* self)
{
    set_animation(self, 0);
}

void homing_orb_wait(struct MainObj* self)
{
    s16 temp_v0;
    s32 temp_a2;

    temp_v0 = --self->unk7C;
    if (temp_v0 == 0) {
        self->unk7C = 0x5A;
        set_velocity_from_angle(
            MOVING_OBJECT(self),
            angle_to_object(
                OBJECT_HEADER(self),
                OBJECT_HEADER(&g_Player))
                & 0xFF);

        self->x_accel = -((s32)(self->x_speed * 0x2D) >> 8);
        temp_a2 = self->y_speed;
        self->x_speed = 0;
        self->y_speed = 0;
        self->gravity = -((s32)(temp_a2 * 0x2D) >> 8);
        set_animation(self, 1);
        self->unk5 = 3;
        self->ext.main_42.background_relative += 1;
        self->ext.main_42.unk84 = 0;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void homing_orb_lunge(struct MainObj* self)
{
    struct MiscObj* misc;

    if (--self->unk7C == 0x5A) {
        self->x_accel = -self->x_accel;
        self->gravity = -self->gravity;
    }
    if (--self->unk7C == 0) {
        if (self->ext.main_42.background_relative < 5) {
            self->unk7C = 0xB4;
            self->x_accel = 0;
            self->gravity = 0;
            self->x_speed = 0;
            self->y_speed = 0;
            set_animation(self, 0);
            self->unk5 = 2;
        } else {
            self->x_speed = 0;
            self->y_speed = FIXED(2);
            set_animation(self, 3);
            self->unk5 = 4;
            self->ext.main_42.unk84 = NULL;
        }
    }
    if (!(self->unk7C & 3)) {
        misc = func_8002AE90(self->ext.main_42.unk84, 0);
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0xE;
            misc->ext.pointer.unk50 = self;
            misc->x_pos.val = self->x_pos.val;
            misc->y_pos.val = self->y_pos.val;
            misc->unk2 = self->animation_step.fields.event;
            self->ext.main_42.unk84 = misc;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
}

void homing_orb_leave(struct MainObj* self)
{
    animate_object(self);
    move_object(self);
}

void homing_orb_main(struct MainObj* self)
{
    s32 hit;

    extern u8 homing_orb_debris[];
    extern void (*homing_orb_step_funcs[])(struct MainObj*);

    hit = func_8002DD04(self);
    if (hit < 0) {
        self->state += 1;
        self->unk5 = 0;
        self->unk42 &= 0x7FFF;
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(6, homing_orb_debris, self);
        return;
    }

    homing_orb_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
        return;
    }

    despawn_object(OBJECT_HEADER(self));
}

void homing_orb_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

s8 homing_orb_hurt_box[4] = { -6, -6, 11, 11 };

s8 homing_orb_attack_box[4] = { -10, -9, 17, 17 };

union AnimationStep homing_orb_anim_0[] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x03 },
    { 2, 0, 1, 0x04 },
    { 1, 0, -5, 0x04 },
};

union AnimationStep homing_orb_anim_1[] = {
    { 3, 0, 1, 0x00 },
    { 2, 1, 1, 0x14 },
    { 2, 2, 1, 0x15 },
    { 2, 3, 1, 0x16 },
    { 2, 4, 1, 0x17 },
    { 2, 5, 1, 0x18 },
    { 2, 6, 1, 0x19 },
    { 2, 7, 1, 0x1A },
    { 2, 8, 1, 0x1B },
    { 2, 9, 1, 0x1C },
    { 2, 10, 1, 0x1D },
    { 2, 11, 1, 0x1E },
    { 2, 12, 1, 0x1F },
    { 2, 13, 1, 0x20 },
    { 1, 14, 1, 0x04 },
    { 1, 14, -15, 0x04 },
};

union AnimationStep homing_orb_anim_2[] = {
    { 2, 0, 1, 0x05 },
    { 2, 0, 1, 0x06 },
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x08 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 2, 1, 1, 0x0C },
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x11 },
    { 2, 0, 1, 0x12 },
    { 1, 0, 1, 0x13 },
    { 1, 0, -15, 0x13 },
};

union AnimationStep homing_orb_anim_3[] = {
    { 2, 0, 1, 0x00 },
    { 2, 1, 1, 0x01 },
    { 2, 2, 1, 0x02 },
    { 2, 3, 1, 0x03 },
    { 2, 4, 1, 0x04 },
    { 2, 5, 1, 0x00 },
    { 2, 6, 1, 0x01 },
    { 2, 7, 1, 0x02 },
    { 2, 8, 1, 0x03 },
    { 2, 9, 1, 0x04 },
    { 2, 10, 1, 0x00 },
    { 2, 11, 1, 0x01 },
    { 2, 12, 1, 0x02 },
    { 2, 13, 1, 0x03 },
    { 1, 14, 1, 0x04 },
    { 1, 14, -15, 0x04 },
};

union AnimationStep homing_orb_anim_4[] = { { 1, 0, 0, 0x21 } };

union AnimationStep homing_orb_anim_5[] = { { 1, 0, 0, 0x22 } };

union AnimationStep homing_orb_anim_6[] = { { 1, 0, 0, 0x23 } };

union AnimationStep* homing_orb_animations[7] = {
    homing_orb_anim_0,
    homing_orb_anim_1,
    homing_orb_anim_2,
    homing_orb_anim_3,
    homing_orb_anim_4,
    homing_orb_anim_5,
    homing_orb_anim_6,
};

u8 homing_orb_debris[8] = { 4, 5, 6, 4, 5, 6, 0, 0 };

void (*homing_orb_state_funcs[])(struct MainObj*) = {
    func_80062D9C,
    homing_orb_main,
    homing_orb_despawn,
};

void (*homing_orb_step_funcs[5])() = {
    enemy_hit_reaction,
    homing_orb_start_idle,
    homing_orb_wait,
    homing_orb_lunge,
    homing_orb_leave,
};
