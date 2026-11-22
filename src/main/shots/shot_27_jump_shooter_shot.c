// ShotObj, shot_object_update_funcs[27]
// 8009F240..8009F46C
#include "common.h"
#include "main/shots/shot_27_jump_shooter_shot.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"
#include "main/objects.h"

// jump_shooter_shot_state_funcs
extern void (*jump_shooter_shot_state_funcs[])(struct ShotObj*);
void func_8009F27C(struct ShotObj*);
void jump_shooter_shot_fly(struct ShotObj*);
void jump_shooter_shot_despawn(struct ShotObj*);

u8 jump_shooter_shot_hit_box[4] = { 0xFD, 0xFD, 5, 5 };
s8 jump_shooter_shot_muzzle_offsets[20] = {
    2,
    -0x16,
    -0x0D,
    -0x19,
    -0x12,
    -0x11,
    -0x12,
    -5,
    -0x0C,
    5,
    2,
    -0x1D,
    -9,
    -0x1E,
    -0x12,
    -0x17,
    -0x15,
    -0x0B,
    -0x0C,
    -3,
};

void jump_shooter_shot_update(struct ShotObj* self)
{
    jump_shooter_shot_state_funcs[self->state](self);
}

// jump_shooter_shot_init
void func_8009F27C(struct ShotObj* self)
{
    self->state = 1;
    self->on_screen = 1;
    self->unk58.collision_data = D_80106070;
    self->unk42 &= 0x7FFF;
    self->unk28 *= 2;
    self->unk2C *= 2;
    if (self->unk15 == 0) {
        self->x_pos.i.hi += jump_shooter_shot_muzzle_offsets[self->unk2 * 2];
    } else {
        self->x_pos.i.hi -= jump_shooter_shot_muzzle_offsets[self->unk2 * 2];
    }
    self->y_pos.i.hi += jump_shooter_shot_muzzle_offsets[self->unk2 * 2 + 1];
    self->x_vel.val *= 2;
    self->y_vel.val *= 2;
    self->unk16 = 0;
    self->unk68 = NULL;
    self->unk54 = jump_shooter_shot_hit_box;
    self->unk50.data = jump_shooter_shot_hit_box;
    self->unk5C = 1;
    self->unk60 = DEMO_ALT(3, 2);
    set_animation(ANIMATED_OBJECT(self), 0xC);
}

void jump_shooter_shot_fly(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    func_8002D9BC(self);
    if (func_8002BB80(MAIN_OBJECT(self), MAIN_OBJECT(&g_Player)) != 0) {
        self->state = 2;
    } else {
        if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
            spawn_explosion(BASE_OBJECT(self));
            self->state = 2;
        }
        if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
            update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
        } else {
            self->state = 2;
        }
    }
}

void jump_shooter_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*jump_shooter_shot_state_funcs[])(struct ShotObj*) = {
    func_8009F27C,
    jump_shooter_shot_fly,
    jump_shooter_shot_despawn,
};
