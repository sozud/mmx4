// ShotObj, shot_object_update_funcs[1]
// 80099B30..80099D10
#include "common.h"
#include "main/shots/shot_01_drill_copter_shot.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/collision_bounds.h"

// drill_copter_shot_state_funcs
extern void (*drill_copter_shot_state_funcs[])(struct ShotObj*);

void drill_copter_shot_fly(struct ShotObj*);
void drill_copter_shot_despawn(struct ShotObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/collision_bounds.h"
#endif

u8 drill_copter_shot_hit_box[4] = { 0xF8, 0xFC, 0x0D, 0x09 };
s8 drill_copter_shot_spawn_offsets[2][2] = { { 0x12, 0x09 }, { -0x12, 0x09 } };
u8 drill_copter_shot_anim_steps[5][4] = {
    { 3, 0, 1, 0x3B },
    { 3, 0, 1, 0x3C },
    { 3, 0, 1, 0x3D },
    { 3, 0, 1, 0x3E },
    { 3, 0, 0xFC, 0x3F },
};
u8* drill_copter_shot_animation = drill_copter_shot_anim_steps[0];

void drill_copter_shot_update(struct ShotObj* self)
{
    drill_copter_shot_state_funcs[self->state](self);
}

// drill_copter_shot_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80099B6C(struct ShotObj* self);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/shots/shot_01_drill_copter_shot", func_80099B6C);
#else
void func_80099B6C(struct ShotObj* self)
{
    s8(*offsets)[2];
    self->on_screen = 1;
    self->state++;
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->y_vel.val = 0;
    self->unk2C = 0;
    self->unk15 = self->unk2 ? 0 : PLAYER_FACING_RIGHT;
    self->animation_table = (u32**)&drill_copter_shot_animation;
    self->x_vel.val = self->unk15 ? FIXED(6) : FIXED(-6);
    offsets = drill_copter_shot_spawn_offsets;
    self->x_pos.i.hi += offsets[(s8)self->unk2][0];
    self->y_pos.i.hi += offsets[(s8)self->unk2][1];
    self->unk16 = VISUAL_SATURN_LAYER(6);
    self->unk68 = NULL;
    self->unk58.collision_data = D_80106070;
    self->unk54 = drill_copter_shot_hit_box;
    self->unk50.data = drill_copter_shot_hit_box;
    self->unk60 = 2;
    set_animation(ANIMATED_OBJECT(self), 0);
}
#endif

void drill_copter_shot_fly(struct ShotObj* self)
{
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        animate_object(ANIMATED_OBJECT(self));
        move_object(MOVING_OBJECT(self));
        func_8002D9BC(self);
        if (func_8002DD04(MAIN_OBJECT(self)) != 0) {
            self->state = 2;
        }
    } else {
        self->state++;
    }
    update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
}

void drill_copter_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*drill_copter_shot_state_funcs[])(struct ShotObj*) = {
    func_80099B6C,
    drill_copter_shot_fly,
    drill_copter_shot_despawn,
};
