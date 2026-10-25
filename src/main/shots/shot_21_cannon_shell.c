// ShotObj, shot_object_update_funcs[21]
// 8009D200..8009D74C
#include "common.h"
#include "main/objects.h"
#include "main/shots/shot_21_cannon_shell.h"
#include "main/object_motion.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"

// cannon_shell_state_funcs
extern void (*cannon_shell_state_funcs[])(struct ShotObj*);

void cannon_shell_fly(struct ShotObj*);

void cannon_shell_despawn(struct ShotObj*);
void cannon_shell_idle(struct ShotObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/collision_bounds.h"
#endif

u8 cannon_shell_hit_box[4] = { 0xF7, 0xF8, 0x11, 0x11 };
u8 cannon_shell_flat_hit_box[4] = { 0xF3, 0xFC, 0x18, 0x0B };
u8 cannon_shell_steep_hit_box[4] = { 0xFC, 0xF4, 0x08, 0x18 };
u8 cannon_shell_terrain_box[4] = { 0, 0, 5, 5 };
u8 cannon_shell_flat_terrain_box[4] = { 0, 2, 0x0A, 4 };
u8 cannon_shell_steep_terrain_box[4] = { 0, 0, 4, 0x0A };

void cannon_shell_update(struct ShotObj* self)
{
    cannon_shell_state_funcs[self->state](self);
}

// cannon_shell_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009D23C(struct ShotObj* arg0);
static s32 shot_21_abs(s32 value);
void func_8009D588(struct ShotObj* arg0);
static s32 shot_21_abs(s32 value)
{
    return value < 0 ? -value : value;
}
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_21_cannon_shell", func_8009D23C);
#else
void func_8009D23C(struct ShotObj* arg0)
{
    struct WeaponObj* owner;
    s32 distance;
    u32 half;
    u32 steps;

    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    owner = arg0->unk7C;
    arg0->on_screen = 1;
    arg0->unk68 = (struct Unk_unk68*)cannon_shell_terrain_box;
    arg0->unk54 = cannon_shell_hit_box;
    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    if (arg0->unk2 != 0) {
        arg0->unk50.data = cannon_shell_flat_hit_box;
        arg0->x_pos.i.hi = owner->x_pos.i.hi + 0xA;
        arg0->y_pos.i.hi = owner->y_pos.i.hi - 0x10;
    } else {
        arg0->unk50.data = cannon_shell_hit_box;
        arg0->x_pos.i.hi = owner->x_pos.i.hi + 0x12;
        arg0->y_pos.i.hi = owner->y_pos.i.hi;
    }
    arg0->x_vel.val = -0x28000;
    arg0->y_vel.val = 0x28000;
    arg0->unk28 = 0;
    half = (arg0->x_pos.val - g_Player.x_pos.val < 0 ? g_Player.x_pos.val - arg0->x_pos.val : arg0->x_pos.val - g_Player.x_pos.val) / 2;
    if (half < 0x200000)
        half += 0x100000;
    if (half > 0x400000)
        half -= arg0->unk2 << 21;
    distance = arg0->x_vel.val;
    if (distance < 0)
        distance = -distance;
    steps = half / (u32)distance;
    if (steps == 0)
        steps = 1;
    arg0->unk84.value = 0;
    arg0->unk70 = 0;
    arg0->unk7 = 1;
    arg0->unk2C = (u32)arg0->y_vel.val / steps;
    set_animation(arg0, 7);
}
#endif

void cannon_shell_fly(struct ShotObj* self)
{
    struct MiscObj* misc;

    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->state++;
        return;
    }
    func_8002D9BC(self);
    if (self->unk84.value != 0) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
    func_8009D588(self);
    if (background_objects[0].y_pos.i.hi + 0xE0 <= self->y_pos.i.hi) {
        self->unk70 = 1;
    }
    if (self->unk70 != 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->state++;
        return;
    }
    if (self->unk7 == 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x21;
            misc->id = 0x17;
            misc->unk2 = 0;
            misc->unk15 = get_random() & PLAYER_FACING_RIGHT;
            misc->ext.unk.unk54 = 0;
            misc->x_pos.i.hi = self->x_pos.i.hi;
            misc->y_pos.i.hi = self->y_pos.i.hi;
            misc->x_vel.val = 0;
            misc->y_vel.val = 0;
            misc->unk7 = 1;
            misc->unk16 = VISUAL_SATURN_LAYER(7);
        }
        self->unk7 = 1;
    } else {
        self->unk7--;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x120, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    } else {
        self->state++;
    }
}

void cannon_shell_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void cannon_shell_idle(struct ShotObj* self)
{
}

// cannon_shell_update_facing
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009D588(struct ShotObj* arg0)
{
    switch (arg0->unk84.value) {
    case 0:
        if (shot_21_abs(arg0->y_vel.val) >= shot_21_abs(arg0->x_vel.val / 2))
            return;
        set_animation(arg0, 8);
        arg0->unk68 = (struct Unk_unk68*)cannon_shell_flat_terrain_box;
        arg0->unk54 = cannon_shell_flat_hit_box;
        arg0->unk50.data = cannon_shell_flat_hit_box;
        break;
    case 1:
        if (shot_21_abs(arg0->y_vel.val) < shot_21_abs(arg0->x_vel.val / 2))
            return;
        set_animation(arg0, 9);
        arg0->unk68 = (struct Unk_unk68*)cannon_shell_terrain_box;
        arg0->unk54 = cannon_shell_hit_box;
        arg0->unk50.data = cannon_shell_hit_box;
        break;
    case 2:
        if (shot_21_abs(arg0->x_vel.val) >= shot_21_abs(arg0->y_vel.val / 2))
            return;
        set_animation(arg0, 0xA);
        arg0->unk68 = (struct Unk_unk68*)cannon_shell_steep_terrain_box;
        arg0->unk54 = cannon_shell_steep_hit_box;
        arg0->unk50.data = cannon_shell_steep_hit_box;
        break;
    default:
        return;
    }
    arg0->unk84.value++;
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_21_cannon_shell", func_8009D588);
#endif

void (*cannon_shell_state_funcs[])(struct ShotObj*) = {
    func_8009D23C,
    cannon_shell_fly,
    cannon_shell_despawn,
    cannon_shell_idle,
};
