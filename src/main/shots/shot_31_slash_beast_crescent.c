// ShotObj, shot_object_update_funcs[31]
// 8009FF10..800A0170
#include "common.h"
#include "main/shots/shot_31_slash_beast_crescent.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"

#ifdef MMX4_PC
#include "main/collision_bounds.h"
#endif

// slash_beast_crescent_state_funcs
extern void (*slash_beast_crescent_state_funcs[])(struct ShotObj*);

void slash_beast_crescent_fly(struct ShotObj*);
void slash_beast_crescent_despawn(struct ShotObj*);

u8 slash_beast_crescent_boxes[2][4] = {
    { 0xF8, 0xEE, 0x0F, 0x23 },
    { 0xF7, 0xF1, 0x14, 0x1B },
};
s8 slash_beast_crescent_offsets[4] = { -72, -6, -60, -51 };

void slash_beast_crescent_update(struct ShotObj* self)
{
    slash_beast_crescent_state_funcs[self->state](self);
}

// slash_beast_crescent_init
#ifdef MMX4_PC
void func_8009FF4C(struct ShotObj* self);
#endif

#ifdef MMX4_PC
void func_8009FF4C(struct ShotObj* self)
{
    self->state = 1;
    self->on_screen = 1;
    self->unk58.collision_data = D_80106070;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk42 &= 0x7FFF;
    if (self->unk15 == 0)
        self->x_pos.i.hi += slash_beast_crescent_offsets[self->unk2 * 2];
    else
        self->x_pos.i.hi -= slash_beast_crescent_offsets[self->unk2 * 2];
    self->y_pos.i.hi += slash_beast_crescent_offsets[self->unk2 * 2 + 1];
    if (self->unk2 == 0) {
        self->y_vel.val = 0;
        self->x_vel.val = self->unk15 != 0 ? 0x50000 : 0xFFFB0000;
    } else {
        self->y_vel.val = 0x38919;
        self->x_vel.val = self->unk15 != 0 ? 0x38919 : 0xFFFC76E7;
    }
    self->unk5C = 1;
    self->unk60 = 6;
    self->unk16 = 0;
    self->unk68 = NULL;
    self->unk54 = slash_beast_crescent_boxes[self->unk2];
    self->unk50.data = slash_beast_crescent_boxes[self->unk2];
    set_animation(self, self->unk2 + 0x1A);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_31_slash_beast_crescent", func_8009FF4C);
#endif

void slash_beast_crescent_fly(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->state = 2;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
        return;
    }
    self->state = 2;
}

void slash_beast_crescent_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*slash_beast_crescent_state_funcs[])(struct ShotObj*) = {
    func_8009FF4C,
    slash_beast_crescent_fly,
    slash_beast_crescent_despawn,
};
