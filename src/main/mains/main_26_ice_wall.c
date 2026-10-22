// MainObj, main_object_update_funcs[26]
// 80058158..800586F0
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_26_ice_wall.h"
#include "main/1CF60.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/objects.h"
#include "main/CB184.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/CB184.h"
#endif

extern void (*ice_wall_break_funcs[])(struct BaseObj*);

void ice_wall_main(struct MainObj*);

// ice_wall_step_funcs
extern void (*ice_wall_step_funcs[])(struct MainObj*);
void ice_wall_start_idle(struct MainObj* arg0);
void ice_wall_idle(struct MainObj* arg0);

// ice_wall_break_funcs
void ice_wall_break_start(struct BaseObj*);
void ice_wall_break_idle(struct BaseObj*);
void ice_wall_break_remove(struct BaseObj* arg0);

extern void (*ice_wall_state_funcs[])(struct MainObj*);

void ice_wall_update(struct MainObj* self)
{
    ice_wall_state_funcs[self->state](self);
}

// ice_wall_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80058194(struct MainObj* arg0);
void func_800583B0(struct MainObj* arg0, s16 x, s16 y, s32 base);
extern union AnimationStep* ice_wall_animations[];
extern struct Unk_unk68 D_80106F74[];
extern struct Unk_unk68 ice_wall_hurt_box[];
extern union AnimationStep* ice_wall_animations[];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80058194(struct MainObj* arg0)
{
    arg0->state++;
    arg0->unk5 = 2;
    arg0->unk2 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->animation_table = (const u8* const*)ice_wall_animations;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->collision_data = (const u16*)D_80106F74;
    arg0->hurt_box = (const u8*)ice_wall_hurt_box;
    arg0->contact_damage = 3;
    arg0->hp = 9;
    arg0->ext.main_26.last_health = 9;
    arg0->ext.main_26.stage = 2;
    arg0->unk15 = 0;
    arg0->terrain_box = NULL;
    arg0->attack_box = NULL;
    arg0->invincibility_timer = 0;
    arg0->x_speed = 0;
    arg0->x_accel = 0;
    arg0->y_speed = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->x_pos.i.hi &= ~0xF;
    arg0->y_pos.i.hi &= ~0xF;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_26_ice_wall", func_80058194);
#endif

void ice_wall_start_idle(struct MainObj* self)
{
    self->unk5 = 2;
}

void ice_wall_idle(struct MainObj* self)
{
}

void ice_wall_main(struct MainObj* self)
{
    s32 hit = func_8002DD04(self);
    s32 stage;

    if (self->ext.main_26.last_health != self->hp) {
        stage = self->ext.main_26.stage--;
        if (stage != 1) {
            if (stage == 2) {
                func_800583B0(self, self->x_pos.i.hi, self->y_pos.i.hi, 0);
            }
        } else {
            func_800583B0(self, self->x_pos.i.hi, self->y_pos.i.hi, 5);
            self->hp = 1;
        }
        self->ext.main_26.last_health = self->hp;
    }
    if (func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi, self->y_pos.i.hi - 0x10) == 0 || hit < 0) {
        self->state++;
        self->unk5 = 0;
        self->unk42 &= 0x7FFF;
        func_8001540C(5, SATURN_SOUND(1, 0x23), NULL);
        return;
    }
    ice_wall_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x50, 0x30) != 0) {
        despawn_object(OBJECT_HEADER(self));
    }
}

// spawn_ice_chunks
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800583B0(struct MainObj* arg0, s16 x, s16 y, s32 base)
{
    u8 above;
    u8 below;
    u8 tile;
    s16 left = (x & -0x10) - 0x10;
    s16 top = y & -0x10;

    above = func_8002D724(PLAYER_OBJECT(arg0), x, y - 0x20);
    if (above != 0x38)
        above = func_8002D724(PLAYER_OBJECT(arg0), x, y - 0x30);
    below = func_8002D724(PLAYER_OBJECT(arg0), x, y + 0x30);

    switch (above) {
    case 0x31:
        tile = 2;
        break;
    case 0:
        tile = 3;
        break;
    case 0x30:
        tile = 1;
        break;
    case 0x3C:
        tile = 0;
        break;
    default:
        tile = 4;
        break;
    }
    apply_tile_effect(tile + base, left, top - 0x20);

    switch (below) {
    case 0x31:
        tile = 0x11;
        break;
    case 0:
        tile = 0x12;
        break;
    case 0x30:
        tile = 0x10;
        break;
    case 0x3C:
        tile = 0xF;
        break;
    default:
        tile = 0x13;
        break;
    }
    apply_tile_effect(tile + base, left, top + 0x10);

    base &= 0xFF;
    apply_tile_effect(base == 0 ? 0x1E : base == 5 ? 0x1F
                                                   : 0x20,
        left, top);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_26_ice_wall", func_800583B0);
#endif

void ice_wall_break_start(struct BaseObj* self)
{
    func_800583B0(self, self->x_pos.i.hi, self->y_pos.i.hi, 10);
    self->y_pos.u.hi += 0x18;
    spawn_debris(0xC, ice_wall_debris, self);
    self->unk5 += 2;
}

void ice_wall_break_idle(struct BaseObj* self)
{
}

void ice_wall_break_remove(struct BaseObj* self)
{
    despawn_object_permanently(OBJECT_HEADER(self));
}

void ice_wall_break(struct MainObj* self)
{
    ice_wall_break_funcs[self->unk5](BASE_OBJECT(self));
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x50, 0x30) != 0) {
        despawn_object_permanently(OBJECT_HEADER(self));
    }
}

struct Unk_unk68 ice_wall_hurt_box[] = {
    { -16, -16, 0x30, 0x30 },
};

union AnimationStep ice_wall_anim_0[] = {
    { 1, 0, 0, 0x00 },
};

union AnimationStep ice_wall_anim_1[] = {
    { 1, 0, 0, 0x01 },
};

union AnimationStep ice_wall_anim_2[] = {
    { 1, 0, 0, 0x02 },
};

union AnimationStep ice_wall_anim_3[] = {
    { 1, 0, 0, 0x03 },
};

union AnimationStep ice_wall_anim_4[] = {
    { 1, 0, 0, 0x04 },
};

union AnimationStep ice_wall_anim_5[] = {
    { 1, 0, 0, 0x05 },
};

union AnimationStep* ice_wall_animations[] = {
    ice_wall_anim_0,
    ice_wall_anim_1,
    ice_wall_anim_2,
    ice_wall_anim_3,
    ice_wall_anim_4,
    ice_wall_anim_5,
};

u8 ice_wall_debris[] = {
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x05,
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x05,
};

void (*ice_wall_state_funcs[])(struct MainObj*) = {
    func_80058194,
    ice_wall_main,
    ice_wall_break,
};

void (*ice_wall_step_funcs[])() = {
    enemy_hit_reaction,
    ice_wall_start_idle,
    ice_wall_idle,
};

void (*ice_wall_break_funcs[])(struct BaseObj*) = {
    ice_wall_break_start,
    ice_wall_break_idle,
    ice_wall_break_remove,
};
