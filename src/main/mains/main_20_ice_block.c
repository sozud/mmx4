// MainObj, main_object_update_funcs[20]
// 8005458C..80054C50
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_20_ice_block.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/mains/main_26_ice_wall.h"
#include "main/objects.h"
#include "main/1CF60.h"
#include "main/misc/misc_02_rubble.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1CF60.h"
#include "main/misc/misc_02_rubble.h"
#endif

extern struct Unk_unk68 ice_block_crumble_attack_box;

void ice_block_main(struct MainObj*);
void ice_block_break(struct MainObj*);

void ice_block_start_idle(struct MainObj* arg0);
void ice_block_idle(struct MainObj* arg0);

// ice_block_break_funcs
extern void (*ice_block_break_funcs[])(struct MainObj*);

void ice_block_break_crumble(struct MainObj*);
void ice_block_break_remove(struct MainObj* arg0);

extern void (*ice_block_state_funcs[])(struct MainObj*);

extern union AnimationStep* ice_block_animations[9];
extern struct Unk_unk68 D_80106C74[];
extern struct Unk_unk68 D_800FC844;
extern struct Unk_unk68 D_800FC848;
extern struct Unk_unk68 D_800FC84C;
extern struct Unk_unk68 D_800FC850;
extern struct Unk_unk68 D_800FC854;
extern struct Unk_unk68 D_800FC858;
extern struct Unk_unk68 D_800FC85C;
extern u8 ice_block_debris[4];
extern union AnimationStep* ice_wall_animations[];

void ice_block_update(struct MainObj* self)
{
    ice_block_state_funcs[self->state](self);
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    CollisionRelated(PLAYER_OBJECT(self));
}

// ice_block_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800545EC(struct MainObj* arg0);
void func_800548B8(struct MainObj* arg0);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_20_ice_block", func_800545EC);
#else
void func_800545EC(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->animation_table = (const u8* const*)ice_block_animations;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->collision_data = D_80106C74;
    arg0->unk15 = 0;
    arg0->terrain_box = NULL;
    arg0->invincibility_timer = 0;
    arg0->hp = 9;
    arg0->contact_damage = 3;
    arg0->ext.main_20.unk80 = 9;
    arg0->ext.main_20.unk81 = 2;
    if (arg0->unk2 != 0) {
        arg0->attack_box = &D_800FC844;
        arg0->hurt_box = &D_800FC848;
    } else {
        arg0->attack_box = NULL;
        arg0->hurt_box = &D_800FC84C;
    }
    arg0->x_speed = 0;
    arg0->x_accel = 0;
    arg0->y_speed = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->unk7C = 0;
    arg0->x_pos.i.hi &= ~0xF;
    arg0->y_pos.i.hi &= ~0xF;
    arg0->x_pos.i.hi += 8;
    arg0->y_pos.i.hi += 0x14;
    set_animation(arg0, 0);
    update_on_screen(BASE_OBJECT(arg0), 0x50, 0x50);
}
#endif

void ice_block_start_idle(struct MainObj* self)
{
    self->unk5 = 2;
    set_animation(self, 0);
}

void ice_block_idle(struct MainObj* self)
{
    animate_object(self);
}

void ice_block_main(struct MainObj* self)
{
    s32 collision = func_8002DD04(self);
    s32 countdown;

    if (self->unk2 == 0 && self->ext.main_20.unk80 != self->hp) {
        countdown = self->ext.main_20.unk81--;
        if (countdown != 1) {
            if (countdown == 2) {
                func_800583B0(self, self->x_pos.i.hi, self->y_pos.i.hi - 0x10, 0);
            }
        } else {
            func_800583B0(self, self->x_pos.i.hi, self->y_pos.i.hi - 0x10, 5);
            self->hp = 1;
        }
        self->ext.main_20.unk80 = self->hp;
    }
    if (collision < 0) {
        self->unk5 = 0;
        self->state++;
        self->unk42 &= 0x7FFF;
        return;
    }
    ice_block_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x80, 0x80) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
    } else {
        despawn_object(OBJECT_HEADER(self));
    }
}

// ice_block_break_start
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_20_ice_block", func_800548B8);
#else
void func_800548B8(struct MainObj* arg0)
{
    struct WeaponObj* weapon;
    u8 flags;
    u8 top;
    u8 bottom;

    if (arg0->unk2 == 0)
        func_800583B0(arg0, arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi - 0x10), 0xA);
    flags = 0;
    if (arg0->unk2 == 0) {
        top = func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi - 0x30));
        bottom = func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi + 0x30));
        switch (top) {
        case 0x30:
        case 0x31:
        case 0x3C:
            func_800583B0(arg0, arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi - 0x40), 0xA);
            break;
        case 0x38:
            flags = 1;
            break;
        }
        switch (bottom) {
        case 0x30:
        case 0x31:
        case 0x3C:
            func_800583B0(arg0, arg0->x_pos.i.hi, (s16)(arg0->y_pos.i.hi + 0x20), 0xA);
            break;
        case 0x38:
            flags += 2;
            break;
        }
    }
    switch (flags) {
    case 1:
        set_animation(arg0, 7);
        arg0->attack_box = &D_800FC850;
        break;
    case 2:
        set_animation(arg0, 6);
        arg0->attack_box = &D_800FC854;
        break;
    case 3:
        arg0->unk7C = 1;
        arg0->attack_box = &D_800FC858;
        break;
    case 0:
    default:
        set_animation(arg0, 8);
        arg0->attack_box = &D_800FC85C;
        break;
    }
    weapon = find_free_weapon_obj();
    if (weapon != NULL) {
        weapon->active = 1;
        weapon->id = 0x3A;
        weapon->owner = PLAYER_OBJECT(arg0);
        weapon->state = 0;
        weapon->unk5 = 0;
        weapon->unk6 = 0;
        weapon->unk2 = flags;
    }
    arg0->unk5++;
    spawn_explosion(BASE_OBJECT(arg0));
    spawn_debris(4, ice_block_debris, arg0);
    if (arg0->unk2 == 0)
        func_800C842C(0xC, ice_wall_debris, arg0, 0x1A, ice_wall_animations);
}
#endif

void ice_block_break_crumble(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->attack_box = (const u8*)&ice_block_crumble_attack_box;
    }
    if (self->animation_step.fields.relative_step < 0) {
        self->unk5++;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void ice_block_break_remove(struct MainObj* self)
{
    self->unk7C = 1;
    despawn_object_permanently(OBJECT_HEADER(self));
}

void ice_block_break(struct MainObj* self)
{
    ice_block_break_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x80, 0x80) == 0) {
        if (self->unk7C == 0) {
            update_on_screen(BASE_OBJECT(self), 0x50, 0x80);
        }
    } else {
        despawn_object_permanently(OBJECT_HEADER(self));
    }
}

struct Unk_unk68 D_800FC844 = { -7, -14, 14, 27 };

struct Unk_unk68 D_800FC848 = { -7, -14, 14, 27 };

struct Unk_unk68 D_800FC84C = { -24, -36, 48, 48 };

struct Unk_unk68 D_800FC850 = { -15, -16, 29, 64 };

struct Unk_unk68 D_800FC854 = { -15, -48, 29, 64 };

struct Unk_unk68 D_800FC858 = { -15, -16, 29, 32 };

struct Unk_unk68 D_800FC85C = { -15, -48, 29, 96 };

struct Unk_unk68 ice_block_crumble_attack_box = { 0, 0, 0, 0 };

union AnimationStep ice_block_anim_0[] = {
    { 12, 0, 1, 0x00 },
    { 1, 0, 1, 0x01 },
    { 1, 0, 1, 0x02 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x02 },
    { 1, 0, 1, 0x01 },
    { 1, 0, 1, 0x00 },
    { 1, 0, 1, 0x01 },
    { 1, 0, 1, 0x02 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x02 },
    { 1, 0, 1, 0x01 },
    { 1, 0, -12, 0x01 },
};

union AnimationStep ice_block_anim_1[] = {
    { 3, 0, 1, 0x04 },
    { 2, 0, 1, 0x05 },
    { 3, 0, 1, 0x06 },
    { 8, 0, 1, 0x07 },
    { 2, 0, 1, 0x00 },
    { 1, 0, 1, 0x08 },
    { 1, 0, 1, 0x09 },
    { 1, 0, 1, 0x0A },
    { 1, 0, 1, 0x0B },
    { 1, 0, 1, 0x0A },
    { 1, 0, 1, 0x09 },
    { 2, 0, -10, 0x08 },
};

union AnimationStep ice_block_anim_6[] = {
    { 3, 0, 1, 0x10 },
    { 4, 0, 1, 0x11 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 2, 0, 1, 0x14 },
    { 2, 0, 1, 0x15 },
    { 3, 0, 1, 0x16 },
    { 3, 1, 1, 0x17 },
    { 3, 0, 1, 0x18 },
    { 4, 0, 1, 0x19 },
    { 4, 0, 1, 0x1A },
    { 1, 0, -11, 0x1A },
};

union AnimationStep ice_block_anim_7[] = {
    { 3, 0, 1, 0x1B },
    { 4, 0, 1, 0x1C },
    { 3, 0, 1, 0x1D },
    { 3, 0, 1, 0x1E },
    { 2, 0, 1, 0x1F },
    { 2, 0, 1, 0x20 },
    { 3, 0, 1, 0x21 },
    { 3, 1, 1, 0x22 },
    { 3, 0, 1, 0x23 },
    { 4, 0, 1, 0x24 },
    { 4, 0, 1, 0x25 },
    { 1, 0, -11, 0x25 },
};

union AnimationStep ice_block_anim_8[] = {
    { 3, 0, 1, 0x26 },
    { 4, 0, 1, 0x27 },
    { 3, 0, 1, 0x28 },
    { 3, 0, 1, 0x29 },
    { 2, 0, 1, 0x2A },
    { 2, 0, 1, 0x2B },
    { 3, 0, 1, 0x2C },
    { 3, 1, 1, 0x2D },
    { 3, 0, 1, 0x2E },
    { 4, 0, 1, 0x2F },
    { 4, 0, 1, 0x30 },
    { 1, 0, -11, 0x30 },
};

union AnimationStep ice_block_anim_2[] = {
    { 1, 0, 0, 0x0C },
};

union AnimationStep ice_block_anim_3[] = {
    { 1, 0, 0, 0x0D },
};

union AnimationStep ice_block_anim_4[] = {
    { 1, 0, 0, 0x0E },
};

union AnimationStep ice_block_anim_5[] = {
    { 1, 0, 0, 0x0F },
};

union AnimationStep* ice_block_animations[9] = {
    ice_block_anim_0,
    ice_block_anim_1,
    ice_block_anim_2,
    ice_block_anim_3,
    ice_block_anim_4,
    ice_block_anim_5,
    ice_block_anim_6,
    ice_block_anim_7,
    ice_block_anim_8,
};

u8 ice_block_debris[4] = { 2, 3, 4, 5 };

void (*ice_block_state_funcs[3])() = {
    func_800545EC,
    ice_block_main,
    ice_block_break,
};

void (*ice_block_step_funcs[3])() = {
    enemy_hit_reaction,
    ice_block_start_idle,
    ice_block_idle,
};

void (*ice_block_break_funcs[3])() = {
    func_800548B8,
    ice_block_break_crumble,
    ice_block_break_remove,
};
