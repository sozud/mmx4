// ShotObj, shot_object_update_funcs[42]
// 800A6374..800A6960
#include "common.h"
#include "main/shots/shot_42_peacock_missile.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/objects.h"
#include "main/object_motion.h"

extern u8 peacock_missile_explosion_box[4];

// peacock_missile_state_funcs
extern void (*peacock_missile_state_funcs[])(struct ShotObj*);

void peacock_missile_main(struct ShotObj*);
void peacock_missile_despawn(struct ShotObj*);

// peacock_missile_step_funcs
extern void (*peacock_missile_step_funcs[])(struct ShotObj*);

void peacock_missile_explode_start(struct ShotObj*);
void peacock_missile_explode(struct ShotObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/object_motion.h"
#endif

extern u8 peacock_missile_hit_box[4];
extern s16 peacock_missile_launch_offsets[8][2];
extern u8 peacock_missile_terrain_box[4];
extern u8 peacock_missile_turn_steps_ccw[8];
extern u8 peacock_missile_turn_steps_cw[8];

void peacock_missile_update(struct ShotObj* self)
{
    peacock_missile_state_funcs[self->state](self);
}

// peacock_missile_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A63B0(struct ShotObj* arg0);
void func_800A6510(struct ShotObj* arg0);
void func_800A666C(struct ShotObj* arg0, s32 x_range, s32 y_range);
extern u8 peacock_missile_hit_box[4];
extern u8 peacock_missile_terrain_box[4];
extern s16 peacock_missile_launch_offsets[8][2];
extern u8 peacock_missile_turn_steps_ccw[8];
extern u8 peacock_missile_turn_steps_cw[8];
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_42_peacock_missile", func_800A63B0);
#else
void func_800A63B0(struct ShotObj* arg0)
{
    s32 index = arg0->unk2 * 2;
    s16 dx;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->timer = 0xA;
    arg0->unk16 = VISUAL_SATURN_LAYER(4);
    arg0->unk68 = (struct Unk_unk68*)peacock_missile_terrain_box;
    arg0->unk50.data = peacock_missile_hit_box;
    arg0->unk5C = 3;
    arg0->unk60 = 6;
    arg0->unk90.val = 0x6E;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->unk8A = 0;
    arg0->unk84.value = 0;
    arg0->unk54 = NULL;
    arg0->unk58.data = NULL;
    arg0->unk61 = 0;
    arg0->unk8C.word = 0;
    dx = ((s16*)peacock_missile_launch_offsets)[index];
    if (((struct MainObj*)arg0->backref)->unk15 != 0) {
        arg0->x_pos.i.hi -= dx;
        arg0->unk84.value = peacock_missile_turn_steps_cw[arg0->unk2];
    } else {
        arg0->x_pos.i.hi += dx;
        arg0->unk84.value = peacock_missile_turn_steps_ccw[arg0->unk2];
    }
    arg0->y_pos.i.hi += ((s16*)peacock_missile_launch_offsets)[index + 1];
    set_animation(arg0, (arg0->unk84.value >> 1) + 0xD);
    set_velocity_from_angle(MOVING_OBJECT(arg0), (u8)arg0->unk84.value);
    arg0->unk2C = 0;
    arg0->unk28 = 0;
    arg0->x_vel.val *= 4;
    arg0->y_vel.val *= 4;
}
#endif

// peacock_missile_home
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A6510(struct ShotObj* arg0)
{
    s32 target;
    s32 direction;

    if (arg0->timer != 0) {
        arg0->timer--;
    } else if ((WEAPON_FRAME_COUNTER & 1) == 0) {
        target = angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(arg0->unk7C));
        direction = arg0->unk84.value;
        if (((direction - (target & 0xFF)) & 0x1F) >= 2) {
            direction = ((u32)((target - direction) & 0x1F) < 0x10) ? direction + 1 : direction - 1;
            arg0->unk84.value = direction & 0x1F;
            set_velocity_from_angle(MOVING_OBJECT(arg0), direction & 0x1E);
            arg0->x_vel.val *= 4;
            arg0->y_vel.val *= 4;
            set_animation(arg0, (arg0->unk84.value >> 1) + 0xD);
        }
    }
    move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_42_peacock_missile", func_800A6510);
#endif

void peacock_missile_explode_start(struct ShotObj* self)
{
    if (SHOT_OBJECT(self->backref)->state == 2) {
        self->unk50.data = NULL;
    } else {
        self->unk50.data = peacock_missile_explosion_box;
    }
    self->unk8C.word = 1;
    self->unk5 = 2;
    self->timer = 0x3C;
    self->unk60 = 6;
    set_animation(self, 0x1F);
}

// peacock_missile_spawn_explosion
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A666C(struct ShotObj* arg0, s32 x_range, s32 y_range)
{
    struct MiscObj* misc = find_free_misc_obj();
    u8 amount;

    if (misc == NULL)
        return;
    misc->active = 0x41;
    misc->id = 0x31;
    misc->unk2 = 4;
    misc->x_pos.val = arg0->x_pos.val;
    misc->y_pos.val = arg0->y_pos.val;
    amount = x_range & get_random();
    if (get_random() & 1)
        misc->x_pos.i.hi += amount;
    else
        misc->x_pos.i.hi -= amount;
    amount = y_range & get_random();
    if (get_random() & 1)
        misc->y_pos.i.hi += amount;
    else
        misc->y_pos.i.hi -= amount;
    misc->animation_table = arg0->animation_table;
    misc->unk40 = arg0->unk40;
    misc->unk3C = arg0->unk3C;
    misc->unk42 = arg0->unk42 & 0x7FFF;
    misc->ext.misc_49.owner = arg0;
    misc->unk15 = 0;
    misc->unk16 = arg0->unk16;
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_42_peacock_missile", func_800A666C);
#endif

void peacock_missile_explode(struct ShotObj* self)
{
    s16 timer;

    timer = --self->timer;
    if (timer == 0) {
        self->state = 2;
        return;
    }
    if (!(timer & 3)) {
        func_800A666C(self, 0x10, 0x10);
    }
    animate_object(ANIMATED_OBJECT(self));
}

s32 peacock_missile_hit_target(struct ShotObj* self)
{
    struct WeaponObj* weapon;

    weapon = self->unk7C;
    if (weapon->active != 0 && weapon->id == 0x17) {
        if (func_8002C160(COLLISION_OBJECT(self), COLLISION_OBJECT(weapon)) != 0) {
            return 1;
        }
    } else {
        self->unk5 = 1;
    }
    return 0;
}

void peacock_missile_main(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    peacock_missile_step_funcs[self->unk5](self);
    func_8002D9BC(self);

    if (self->unk8C.word == 0) {
        if ((s8)func_8002DD04(MAIN_OBJECT(self)) < 0) {
            spawn_explosion(self);
            self->unk5 = 1;
            return;
        }

        if (func_8002BB80(self, &g_Player) != 0 || peacock_missile_hit_target(self) != 0) {
            self->unk5 = 1;
            return;
        }

        if (self->unk90.val == 0) {
            self->unk5 = 1;
            return;
        } else {
            self->unk90.val--;
        }
    }

    is_on_screen(BASE_OBJECT(self));
}

void peacock_missile_despawn(struct ShotObj* self)
{
    self->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

u8 peacock_missile_hit_box[4] = { 0xF8, 0xF8, 0x0F, 0x0E };

u8 peacock_missile_terrain_box[4] = { 0, 0, 4, 4 };

u8 peacock_missile_explosion_box[4] = { 0xF6, 0xF6, 0x13, 0x13 };

s16 peacock_missile_launch_offsets[8][2] = {
    { -0x18, 0 },
    { -0x16, -0x12 },
    { -0x0B, -0x20 },
    { 3, -0x2A },
    { 0x1B, -0x29 },
    { 0x2F, -0x23 },
    { 0x33, -0x10 },
    { 0x33, 2 },
};

u8 peacock_missile_turn_steps_ccw[8] = { 0x10, 0x0E, 0x0C, 0x0A, 6, 4, 2, 0 };

u8 peacock_missile_turn_steps_cw[8] = { 0, 2, 4, 6, 0x0A, 0x0C, 0x0E, 0x10 };

void (*peacock_missile_state_funcs[])(struct ShotObj*) = {
    func_800A63B0,
    peacock_missile_main,
    peacock_missile_despawn,
};

void (*peacock_missile_step_funcs[3])(struct ShotObj*) = {
    func_800A6510,
    peacock_missile_explode_start,
    peacock_missile_explode,
};
