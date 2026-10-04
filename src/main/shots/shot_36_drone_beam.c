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

static __inline void beam_update_visibility(struct ShotObj* self, s16 camera_x, s16 owner_x, s32 offset)
{
    u16 distance = ABS(camera_x, owner_x - offset);
    update_on_screen(BASE_OBJECT(self), distance, 0x20);
}

// drone_beam_active
void func_800A3A4C(struct ShotObj* self)
{
    struct WeaponObj* owner;
    u16 distance;
    s16 adjusted_distance;

    owner = self->unk7C;
    animate_object(ANIMATED_OBJECT(self));

    if ((u32)(self->unk84.value - 0x1A) < 0x4A) {
        func_8002D9BC(self);
    }

    if (self->unk84.value == 0x46) {
        if (self->unk2 != 0) {
            self->unk50.frames = drone_beam_boxes[1];
        } else {
            self->unk50.frames = drone_beam_boxes[0];
        }
    }

    if (self->unk84.value == 0x19) {
        if (self->unk2 != 0) {
            set_animation(self, 6);
        } else {
            set_animation(self, 5);
        }
    }

    distance = ABS(background_objects[0].x_pos.i.hi, owner->x_pos.i.hi);

    if (distance >= 0x180) {
        if (self->unk2 != 0) {
            if (self->unk15 == 0) {
                self->x_pos.i.hi = owner->x_pos.u.hi - distance - 0x10;
            } else {
                self->x_pos.i.hi = distance + owner->x_pos.u.hi + 0x10;
            }
        } else {
            if (self->unk15 == 0) {
                adjusted_distance = distance - 0xF0;
                self->x_pos.i.hi = owner->x_pos.u.hi - adjusted_distance;
            } else {
                adjusted_distance = distance - 0xF0;
                self->x_pos.i.hi = owner->x_pos.u.hi + adjusted_distance;
            }
        }
    }

    if ((--self->unk84.value == 0) || (owner->active == 0) || (owner->state >= 2)) {
        self->state++;
    }

    beam_update_visibility(self, background_objects[0].x_pos.i.hi, owner->x_pos.i.hi, 0xA0);
}

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
