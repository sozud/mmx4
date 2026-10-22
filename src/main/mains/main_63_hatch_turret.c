// MainObj, main_object_update_funcs[63]
// 8007BFF4..8007C30C
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_63_hatch_turret.h"
#include "main/objects.h"
#include "main/55C4.h"

// hatch_turret_state_funcs
extern void (*hatch_turret_state_funcs[])(struct MainObj*);
void func_8007BFF4(struct MainObj*);

void hatch_turret_despawn(struct MainObj* arg0);

extern void* hatch_turret_animations[13];

// hatch_turret_init
void func_8007BFF4(struct MainObj* self)
{
    s32 v = 1;

    self->state = v;
    self->on_screen = v;
    self->unk7C = 0x30;
    self->hp = 3;
    self->contact_damage = 3;
    self->unk7A = v;
    self->animation_table = (const u8* const*)hatch_turret_animations;
    self->unk5 = 0;
    self->unk6 = 0;
    self->unk7 = 0;
    self->invincibility_timer = 0;
    self->hurt_box = NULL;
    self->attack_box = NULL;
    self->terrain_box = NULL;
    self->collision_data = NULL;
    self->air_state = 0;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->unk16 = VISUAL_SATURN_LAYER(5);
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    set_animation(self, 0);
}

// hatch_turret_spawn_shot
void func_8007C090(struct WeaponObj* weapon)
{
    struct ShotObj* shot;

    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = weapon->active;
        shot->id = 0x28;
        shot->unk2 = weapon->unk2;
        shot->x_pos.val = weapon->x_pos.val;
        shot->y_pos.val = weapon->y_pos.val;
        shot->animation_table = weapon->animation_table;
        shot->unk40 = weapon->unk40;
        shot->unk3C = weapon->unk3C;
        shot->unk42 = weapon->unk42;
        shot->unk16 = weapon->unk16;
        shot->unk7C = weapon;
        shot->unk15 = weapon->unk15;
        weapon->unk7 = 1;
    }
}

// hatch_turret_main
#if defined(MMX4_PC) || defined(MMX4_SATURN)
s32 func_8001540C(s32 arg0, s32 arg1, void* arg2);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007C144(struct MainObj* arg0);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007C144(struct MainObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x80, 0x80) != 0) {
        arg0->state = 2;
        return;
    }
    switch (arg0->unk5) {
    case 0:
        if (arg0->unk7C == 0) {
            arg0->unk5 = 1;
            set_animation(arg0, 0);
        } else {
            arg0->unk7C--;
        }
        break;
    case 1:
        if (arg0->animation_step.fields.relative_step != 0) {
            animate_object(ANIMATED_OBJECT(arg0));
            break;
        }
        arg0->unk5 = 2;
        func_8001540C(2, SATURN_SOUND(0x78, 0x30), arg0);
        set_animation(arg0, 1);
        break;
    case 2:
        if (arg0->animation_step.fields.relative_step != 0) {
            animate_object(ANIMATED_OBJECT(arg0));
            break;
        }
        arg0->unk5 = 3;
        func_8001540C(2, SATURN_SOUND(0x79, 0x31), arg0);
        func_8007C090(WEAPON_OBJECT(arg0));
        break;
    case 3:
        if (arg0->unk7 == 0) {
            arg0->unk5 = 4;
            set_animation(arg0, 5);
        }
        break;
    case 4:
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk7C = 0x80;
            arg0->unk5 = 0;
        }
        animate_object(ANIMATED_OBJECT(arg0));
        break;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x80, 0x80);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_63_hatch_turret", func_8007C144);
#endif

void hatch_turret_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

void hatch_turret_update(struct MainObj* self)
{
    hatch_turret_state_funcs[self->state](self);
}

union AnimationStep hatch_turret_anim_0[] = {
    { 7, 0, 1, 0x00 },
    { 7, 0, 1, 0x01 },
    { 7, 0, 1, 0x02 },
    { 7, 0, 1, 0x03 },
    { 1, 0, 0, 0x03 },
};

union AnimationStep hatch_turret_anim_5[] = {
    { 7, 0, 1, 0x03 },
    { 7, 0, 1, 0x02 },
    { 7, 0, 1, 0x01 },
    { 7, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep hatch_turret_anim_1[] = {
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x05 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x06 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x07 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x08 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x09 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x0A },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x0B },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x0C },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x0D },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x0E },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x0F },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x10 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x11 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x12 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x13 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x19 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x1A },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x1B },
    { 1, 0, 0, 0x03 },
};

union AnimationStep hatch_turret_anim_2[] = {
    { 1, 0, 1, 0x1C },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1C },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1E },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1E },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1E },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1E },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1F },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1F },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1F },
    { 1, 0, 0, 0x24 },
};

union AnimationStep hatch_turret_anim_3[] = {
    { 1, 0, 1, 0x1F },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1F },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1F },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1E },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1E },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1E },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1E },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1D },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1C },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x1C },
    { 1, 0, 0, 0x24 },
};

struct Unk_unk68 hatch_turret_anim_4[8] = {
    { 1, 0, 1, 32 },
    { 1, 0, 1, 36 },
    { 1, 0, 1, 33 },
    { 1, 0, 1, 36 },
    { 1, 0, 1, 34 },
    { 1, 0, 1, 36 },
    { 1, 0, 1, 35 },
    { 1, 0, -7, 36 },
};

union AnimationStep hatch_turret_anim_6[] = {
    { 1, 0, 0, 0x25 },
};

union AnimationStep hatch_turret_anim_7[] = {
    { 1, 0, 0, 0x26 },
};

union AnimationStep hatch_turret_anim_8[] = {
    { 1, 0, 0, 0x27 },
};

union AnimationStep hatch_turret_anim_9[] = {
    { 1, 0, 0, 0x28 },
};

union AnimationStep hatch_turret_anim_10[] = {
    { 1, 0, 0, 0x29 },
};

union AnimationStep hatch_turret_anim_11[] = {
    { 1, 0, 0, 0x2A },
};

union AnimationStep hatch_turret_anim_12[] = {
    { 1, 0, 0, 0x2B },
};

void* hatch_turret_animations[13] = {
    hatch_turret_anim_0,
    hatch_turret_anim_1,
    hatch_turret_anim_2,
    hatch_turret_anim_3,
    hatch_turret_anim_4,
    hatch_turret_anim_5,
    hatch_turret_anim_6,
    hatch_turret_anim_7,
    hatch_turret_anim_8,
    hatch_turret_anim_9,
    hatch_turret_anim_10,
    hatch_turret_anim_11,
    hatch_turret_anim_12,
};

void (*hatch_turret_state_funcs[3])() = {
    func_8007BFF4,
    func_8007C144,
    hatch_turret_despawn,
};
