// ShotObj, shot_object_update_funcs[37]
// 800A3C78..800A428C
#include "common.h"
#include "main/shots/shot_37_owl_feather.h"
#include "main/objects.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"
#include "main/55C4.h"
#include "main/1E1BC.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"
#endif

// owl_feather_state_funcs
extern void (*owl_feather_state_funcs[])(struct ShotObj*);

void owl_feather_despawn(struct ShotObj*);
void owl_feather_idle(struct ShotObj*);

s8 owl_feather_hit_box[4] = { -11, -11, 22, 22 };

u16 owl_feather_velocities[11][2] = {
    { 0x43, 0x28 },
    { 0x80, 0x28 },
    { 0xBC, 0x28 },
    { 0xF8, 0x28 },
    { 0x52, 0x70 },
    { 0x9E, 0x70 },
    { 0xEA, 0x70 },
    { 0x43, 0xB0 },
    { 0x80, 0xB0 },
    { 0xBC, 0xB0 },
    { 0xF8, 0xB0 },
};

void owl_feather_update(struct ShotObj* self)
{
    owl_feather_state_funcs[self->state](self);
}

// owl_feather_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A3CB4(struct ShotObj* arg0);
void func_800A3FEC(struct ShotObj* arg0);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A3CB4(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s16 background_x;
    s16 background_y;
    u16 best;
    u16 dx;
    u16 dy;
    u8 index;
    u8 i;

    arg0->on_screen = 1;
    arg0->unk58.data = (u8*)D_801060F0;
    arg0->unk60 = 6;
    arg0->unk68 = NULL;
    arg0->unk54 = (u8*)owl_feather_hit_box;
    arg0->unk5C = 0;
    arg0->unk84.value = 0;
    arg0->unk8C.word = 0;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    set_animation(arg0, 0xD);
    arg0->unk50.data = (u8*)owl_feather_hit_box;
    arg0->x_pos.i.hi = owner->x_pos.i.hi + (owner->unk15 != 0 ? 0x26 : -0x26);
    arg0->y_pos.i.hi = owner->y_pos.i.hi + 6;
    if (arg0->unk2 == 0) {
        set_velocity_from_angle(MOVING_OBJECT(arg0), angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)) & 0xFF);
        arg0->x_vel.val *= 4;
        arg0->y_vel.val *= 4;
        return;
    }
    if (arg0->unk2 >= 5) {
        arg0->x_pos.i.hi = owner->x_pos.i.hi;
        arg0->y_pos.i.hi = owner->y_pos.i.hi;
        set_velocity_from_angle(MOVING_OBJECT(arg0), (owner->ext.main_60.storm_timer + (arg0->unk2 - 5) * 8 + 4) & 0x1F);
        arg0->x_vel.val *= 8;
        arg0->y_vel.val *= 8;
        return;
    }
    background_x = background_objects[0].x_pos.i.hi;
    background_y = background_objects[0].y_pos.i.hi;
    if (arg0->unk2 == 1) {
        best = 0xFFFF;
        index = 0;
        for (i = 0; i < 11; i++) {
            s32 point_x = background_x + owl_feather_velocities[i][0];
            s32 point_y = background_y + owl_feather_velocities[i][1];
            dx = g_Player.x_pos.i.hi - point_x >= 0 ? g_Player.x_pos.i.hi - point_x : point_x - g_Player.x_pos.i.hi;
            dy = g_Player.y_pos.i.hi - point_y >= 0 ? g_Player.y_pos.i.hi - point_y : point_y - g_Player.y_pos.i.hi;
            if ((u16)(dx + dy) < best) {
                best = dx + dy;
                index = i;
            }
        }
        arg0->unk84.value = index;
    } else {
        do {
            arg0->unk84.value = (u8)get_random() % 11;
        } while ((owner->ext.main_60.feather_mask >> arg0->unk84.value) & 1);
    }
    owner->ext.main_60.feather_mask += 1 << arg0->unk84.value;
    set_velocity_from_angle(MOVING_OBJECT(arg0),
        angle_to_point(OBJECT_HEADER(arg0), (background_x + owl_feather_velocities[arg0->unk84.value][0]) << 16,
            (background_y + owl_feather_velocities[arg0->unk84.value][1]) << 16)
            & 0xFF);
    arg0->x_vel.val *= 2;
    arg0->y_vel.val *= 2;
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_37_owl_feather", func_800A3CB4);
#endif

// owl_feather_fly
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A3FEC(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s32 target_x;
    s32 target_y;
    s32 d;

    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    func_8002D9BC(arg0);
    func_8002DD04((struct MainObj*)arg0);
    if (arg0->unk2 != 0 && arg0->unk2 < 5) {
        if (owner->ext.main_60.feathers_holding == 0) {
            target_x = background_objects[0].x_pos.i.hi + owl_feather_velocities[arg0->unk84.value][0];
            target_y = background_objects[0].y_pos.i.hi + owl_feather_velocities[arg0->unk84.value][1];
            set_velocity_from_angle(MOVING_OBJECT(arg0),
                angle_to_point(OBJECT_HEADER(arg0), target_x << 16, target_y << 16) & 0xFF);
            arg0->x_vel.val *= 2;
            arg0->y_vel.val *= 2;
            d = arg0->x_pos.i.hi - target_x;
            if ((d < 0 ? -d : d) < 8)
                arg0->x_vel.val = 0;
            d = arg0->y_pos.i.hi - target_y;
            if ((d < 0 ? -d : d) < 8)
                arg0->y_vel.val = 0;
        } else if (arg0->unk8C.word == 0) {
            set_velocity_from_angle(MOVING_OBJECT(arg0), angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)) & 0xFF);
            arg0->unk8C.word = 1;
            arg0->x_vel.val *= 5;
            arg0->y_vel.val *= 5;
        }
    }
    if (owner->state == 2 || owner->active == 0 || func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) != 0) {
        arg0->state++;
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_37_owl_feather", func_800A3FEC);
#endif

void owl_feather_despawn(struct ShotObj* self)
{
    struct MainObj* owner;

    if (self->unk2 > 0 && self->unk2 < 5) {
        owner = MAIN_OBJECT(self->unk7C);
        owner->ext.main_60.feather_mask -= 1 << self->unk84.value;
    }
    ZeroObjectState(OBJECT_HEADER(self));
}

void owl_feather_idle(struct ShotObj* self)
{
}

void (*owl_feather_state_funcs[])(struct ShotObj*) = {
    func_800A3CB4,
    func_800A3FEC,
    owl_feather_despawn,
    owl_feather_idle,
};
