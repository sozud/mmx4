// ShotObj, shot_object_update_funcs[36]
// 800A3924..800A3C78
#include "common.h"

s16 drone_beam_boxes[4][2] = {
    { -0x1280, 0x2AFF },
    { -0x1280, 0x2AFF },
    { -0xA80, 0x19FF },
    { -0xA80, 0x19FF },
};

void drone_beam_update(struct ShotObj* self)
{
    drone_beam_state_funcs[self->state](self);
}

void drone_beam_init(struct ShotObj* self)
{
    s32 owner_x;
    s32 x_pos;
    struct WeaponObj* owner;

    self->on_screen = 1;
    self->unk58.animation_steps = D_80105FF0;
    self->unk60 = 6;
    self->unk84.value = 0x6E;
    owner = self->unk7C;
    self->unk68 = NULL;
    self->unk54 = NULL;
    self->unk5C = 0;
    self->state++;
    self->unk42 &= 0x7FFF;

    if (self->unk2 != 0) {
        set_animation(self, 4);
        self->unk50.frames = drone_beam_boxes[3];
        owner_x = owner->x_pos.i.hi;
        x_pos = self->unk15 != 0 ? owner_x + 0x190 : owner_x - 0x190;
    } else {
        set_animation(self, 3);
        self->unk50.frames = drone_beam_boxes[2];
        owner_x = owner->x_pos.i.hi;
        x_pos = self->unk15 != 0 ? owner_x + 0x90 : owner_x - 0x90;
    }

    self->x_pos.i.hi = x_pos;
    self->y_pos.i.hi = owner->y_pos.i.hi - 3;
}

// drone_beam_active
INCLUDE_ASM("main/nonmatchings/shots/shot_36_drone_beam", func_800A3A4C);

void drone_beam_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void drone_beam_idle(struct ShotObj* self)
{
}

void (*drone_beam_state_funcs[])(struct ShotObj*) = {
    drone_beam_init,
    func_800A3A4C,
    drone_beam_despawn,
    drone_beam_idle,
};
