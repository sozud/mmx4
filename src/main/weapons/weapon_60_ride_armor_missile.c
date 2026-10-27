// WeaponObj, weapon_object_update_funcs[60]
// 80098F4C..800992FC
#include "common.h"
#include "main/weapons/weapon_60_ride_armor_missile.h"
#include "main/objects.h"
#include "main/object_motion.h"
#include "main/55C4.h"
#include "main/weapons/weapon_59_ride_armor_shot.h"

// ride_armor_missile_state_funcs
extern void (*ride_armor_missile_state_funcs[])(struct WeaponObj*);

void ride_armor_missile_despawn(struct WeaponObj*);
void func_80098DA0(struct WeaponObj* arg0);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/weapons/weapon_59_ride_armor_shot.h"
#endif

void ride_armor_missile_update(struct WeaponObj* arg0)
{
    ride_armor_missile_state_funcs[arg0->state](arg0);
}

// ride_armor_missile_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80098DA0(struct WeaponObj* arg0);
void func_80098F88(struct WeaponObj* self);
void func_80099118(struct WeaponObj* arg0);
#endif

extern u8 ride_armor_missile_hit_box[4];
extern struct Weapon60SpawnOffset ride_armor_missile_offsets[3];

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/weapons/weapon_60_ride_armor_missile", func_80098F88);
#else
void func_80098F88(struct WeaponObj* self)
{
    struct Weapon60SpawnOffset* offsets;
    u8 direction;
    u16 dx;

    self->state = 1;
    self->on_screen = 1;
    self->unk16 = 0;
    self->unk68 = NULL;
    self->unk54 = NULL;
    self->unk50 = ride_armor_missile_hit_box;
    dx = *(s16*)&ride_armor_missile_offsets[self->unk2];
    offsets = ride_armor_missile_offsets;
    if (self->unk15 != 0)
        dx = -dx;
    self->x_pos.i.hi += dx;
    self->y_pos.i.hi += ((s16*)((u8*)offsets - -(self->unk2 * 4)))[1];
    switch (self->unk2) {
    case 0:
        direction = (self->unk15 == 0) << 4;
        break;
    case 1:
        direction = self->unk15 == 0 ? 0x14 : 0x1C;
        break;
    case 2:
        direction = self->unk15 == 0 ? 0xC : 4;
        break;
    }
    self->ext.weapon_60.direction = direction;
    set_velocity_from_angle(MOVING_OBJECT(self), direction);
    self->unk5C = 1;
    self->unk60 = 3;
    self->unk88.half = 8;
    self->unk28.val = 0;
    self->unk2C = 0;
    self->unk8A = 1;
    self->ext.target = NULL;
    self->unk84.word = 0;
    self->x_vel.val *= 6;
    self->y_vel.val *= 6;
    set_animation(self, 0x21);
}
#endif

// ride_armor_missile_main
void func_80099118(struct WeaponObj* arg0)
{
    s16 timer;
    s16 trail;
    s16 next;
    s32 frames;
    s32 target;
    s32 direction;

    timer = arg0->unk88.half;
    if (timer != 0) {
        arg0->unk88.half = timer - 1;
        arg0->unk84.word = 0;
    }
    if (!(WEAPON_FRAME_COUNTER & 1) && (s16)arg0->unk88.half == 0) {
        frames = arg0->unk84.word + 1;
        arg0->unk84.word = frames;
        if (frames >= 0x1E0)
            arg0->unk88.half = 0x3C;
        func_80098DA0(arg0);
        if (arg0->ext.target != NULL) {
            target = angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(arg0->ext.target));
            direction = arg0->ext.weapon_60.direction;
            if (((direction - (target & 0xFF)) & 0x1F) >= 2) {
                if ((u32)((target - direction) & 0x1F) < 0x10)
                    arg0->ext.weapon_60.direction = direction + 2;
                else
                    arg0->ext.weapon_60.direction = direction - 2;
                arg0->ext.weapon_60.direction &= 0x1F;
            }
            target = arg0->ext.weapon_60.direction;
            set_velocity_from_angle(MOVING_OBJECT(arg0), target);
            arg0->x_vel.val *= 6;
            arg0->y_vel.val *= 6;
        }
    }
    trail = arg0->unk8A;
    if (trail == 0) {
        func_80098EA8(arg0);
        next = 1;
    } else {
        next = trail - 1;
    }
    arg0->unk8A = next;
    animate_object(ANIMATED_OBJECT(arg0));
    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0 && arg0->unk98 == 0) {
        update_on_screen(BASE_OBJECT(arg0), 0x10, 0x10);
        return;
    }
    arg0->state = 2;
    arg0->on_screen = 0;
    arg0->unk50 = NULL;
}

void ride_armor_missile_despawn(struct WeaponObj* arg0)
{
    struct PlayerObj* temp_a2;

    temp_a2 = arg0->owner;
    temp_a2->input.bytes.previous_high ^= 1 << arg0->unk2;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

u8 ride_armor_missile_hit_box[4] = { 0xFC, 0xFD, 6, 5 };

struct Weapon60SpawnOffset ride_armor_missile_offsets[3] = {
    { -0x28, 0 },
    { -0x28, 0 },
    { -0x28, 0 },
};

void (*ride_armor_missile_state_funcs[])(struct WeaponObj*) = {
    func_80098F88,
    func_80099118,
    ride_armor_missile_despawn,
};
