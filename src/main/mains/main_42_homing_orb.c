// MainObj, main_object_update_funcs[42]
// 80062D60..800631C8
#include "common.h"
#include "func_tables.h"

void homing_orb_update(struct MainObj* self)
{
    homing_orb_state_funcs[self->state](self);
}

// homing_orb_init
INCLUDE_ASM("main/nonmatchings/mains/main_42_homing_orb", func_80062D9C);

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
    extern u8 homing_orb_debris[];
    extern void (*homing_orb_step_funcs[])(struct MainObj*);

    if (func_8002DD04(self) < 0) {
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
    { 0x00010003 },
    { 0x01010003 },
    { 0x02010003 },
    { 0x03010003 },
    { 0x04010002 },
    { 0x04FB0001 },
};

union AnimationStep homing_orb_anim_1[] = {
    { 0x00010003 },
    { 0x14010102 },
    { 0x15010202 },
    { 0x16010302 },
    { 0x17010402 },
    { 0x18010502 },
    { 0x19010602 },
    { 0x1A010702 },
    { 0x1B010802 },
    { 0x1C010902 },
    { 0x1D010A02 },
    { 0x1E010B02 },
    { 0x1F010C02 },
    { 0x20010D02 },
    { 0x04010E01 },
    { 0x04F10E01 },
};

union AnimationStep homing_orb_anim_2[] = {
    { 0x05010002 },
    { 0x06010002 },
    { 0x07010002 },
    { 0x08010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0C010102 },
    { 0x0D010002 },
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010001 },
    { 0x13F10001 },
};

union AnimationStep homing_orb_anim_3[] = {
    { 0x00010002 },
    { 0x01010102 },
    { 0x02010202 },
    { 0x03010302 },
    { 0x04010402 },
    { 0x00010502 },
    { 0x01010602 },
    { 0x02010702 },
    { 0x03010802 },
    { 0x04010902 },
    { 0x00010A02 },
    { 0x01010B02 },
    { 0x02010C02 },
    { 0x03010D02 },
    { 0x04010E01 },
    { 0x04F10E01 },
};

union AnimationStep homing_orb_anim_4[] = { { 0x21000001 } };

union AnimationStep homing_orb_anim_5[] = { { 0x22000001 } };

union AnimationStep homing_orb_anim_6[] = { { 0x23000001 } };

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
