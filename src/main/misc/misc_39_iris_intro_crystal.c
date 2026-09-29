// MiscObj, misc_object_update_funcs[39]
// 800CF790..800CFB70
#include "common.h"

void iris_intro_crystal_update(struct MiscObj* self)
{
    iris_intro_crystal_state_funcs[self->state](self);
}

void iris_intro_crystal_run(struct MiscObj* self)
{
    iris_intro_crystal_step_funcs[self->unk5](self);
    update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
}

void iris_intro_crystal_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void iris_intro_crystal_start(struct MiscObj* self)
{
    self->unk15 = 0x40;
    self->y_vel.val = FIXED(0.5);
    self->unk16 = 0;
    self->x_vel.val = 0;
    self->ext.misc_39.timer = 0xD6;
    set_animation(self, 0xB);
    self->unk5 = 1;
}

void iris_intro_crystal_rise(struct MiscObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    timer = self->ext.misc_39.timer - 1;
    self->ext.misc_39.timer = timer;
    if (timer == 0) {
        self->ext.misc_39.timer = 0x78;
        self->unk5 = 2;
    }
}

void iris_intro_crystal_charge(struct MiscObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    timer = self->ext.misc_39.timer - 1;
    self->ext.misc_39.timer = timer;
    if (timer == 0) {
        set_animation(self, 0xC);
        set_animation(self->ext.misc_39.related, 0x21);
        self->unk5 = 3;
    }
}

// iris_intro_crystal_transform
INCLUDE_ASM("main/nonmatchings/misc/misc_39_iris_intro_crystal", func_800CF950);

void iris_intro_crystal_wait(struct MiscObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    timer = self->ext.misc_39.timer - 1;
    self->ext.misc_39.timer = timer;
    if (timer == 0) {
        self->ext.misc_39.timer = 0x76;
        self->y_vel.val = FIXED(-1);
        self->unk5 = 5;
    }
}

void iris_intro_crystal_leave(struct MiscObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    timer = self->ext.misc_39.timer - 1;
    self->ext.misc_39.timer = timer;
    if (timer == 0) {
        self->state = 1;
    }
}

void (*iris_intro_crystal_state_funcs[2])(struct MiscObj*) = {
    iris_intro_crystal_run,
    iris_intro_crystal_despawn,
};

void (*iris_intro_crystal_step_funcs[6])(struct MiscObj*) = {
    iris_intro_crystal_start,
    iris_intro_crystal_rise,
    iris_intro_crystal_charge,
    func_800CF950,
    iris_intro_crystal_wait,
    iris_intro_crystal_leave,
};
