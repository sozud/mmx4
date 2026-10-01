// ShotObj, shot_object_update_funcs[52]
// 800AAAD4..800AAC98
#include "common.h"

void double_mine_shot_init(struct ShotObj* self)
{
    self->state = 1;
    self->on_screen = 1;
    self->unk5 = 0;
    self->unk6 = 0;
    self->unk7 = 0;
    self->timer = 0;
    self->unk8A = 0;
    self->bg_offset = 0;
    self->unk16 = 3;
    self->unk68 = NULL;
    self->unk54 = double_ball_box_5[0];
    self->unk50.data = double_ball_box_5[0];
    self->unk58.collision_bounds = D_801060F0;
    self->unk5C = 2;
    self->unk60 = 4;
    self->unk61 = 0;
    set_animation(self, 0x17);
    self->x_vel.val = 0;
    self->y_vel.val = FIXED(-4);
    self->unk28 = 0;
    self->unk2C = 0;
}

// double_mine_shot_fly
INCLUDE_ASM("main/nonmatchings/shots/shot_52_double_mine_shot", func_800AAB74);

void double_mine_shot_update(struct ShotObj* self)
{
    double_mine_shot_state_funcs[self->state](self);
}

void (*double_mine_shot_state_funcs[])(struct ShotObj*) = {
    double_mine_shot_init,
    func_800AAB74,
    double_ball_despawn,
};
