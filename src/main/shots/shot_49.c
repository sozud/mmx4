// ShotObj, shot_object_update_funcs[49]
// 800A9DF4..800AA2FC
#include "common.h"

void (*double_aerial_funcs[])(struct ShotObj*) = {
    double_aerial_drop,
    func_800A9F30,
    double_aerial_fly,
    double_aerial_fly_alt,
};

// double_aerial_init
INCLUDE_ASM("main/nonmatchings/shots/shot_49", func_800A9DF4);

void double_aerial_drop(struct ShotObj* self)
{
    if (--self->timer == 0) {
        self->timer = 0x1D;
        self->unk5++;
        func_80015D60(self, 0xF);
        return;
    }
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
}

// double_aerial_split
INCLUDE_ASM("main/nonmatchings/shots/shot_49", func_800A9F30);

void double_aerial_fly(struct ShotObj* self)
{
    func_8002B694((struct AnimatedObj*)self);
    func_80015DC8(self);
}

void double_aerial_fly_alt(struct ShotObj* self)
{
    func_8002B694((struct AnimatedObj*)self);
    func_80015DC8(self);
}

void double_aerial_run(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    double_aerial_funcs[self->unk5](self);
    if (self->unk7C->state == 2) {
        func_800AF808(BASE_OBJECT(self));
        self->state = 2;
        self->on_screen = 0;
        return;
    }
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        func_800AF808(BASE_OBJECT(self));
        self->state = 2;
        self->on_screen = 0;
        return;
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->state = 2;
    self->unk5 = 0;
    self->unk6 = 0;
    self->on_screen = 0;
}

void double_aerial_update(struct ShotObj* self)
{
    double_aerial_state_funcs[self->state](self);
}

void func_800AA148(struct ShotObj* self)
{
    s32 x_vel;

    self->state = 1;
    self->on_screen = 1;
    self->unk16 = 3;
    self->unk58.data = (const u8*)D_80105FF0;
    self->unk5C = 3;
    self->unk5 = 0;
    self->unk6 = 0;
    self->unk7 = 0;
    self->timer = 0;
    self->unk8A = 0;
    self->bg_offset = 0;
    self->unk84.value = 0;
    self->unk68 = 0;
    self->unk54 = 0;
    self->unk50.data = 0;
    self->unk60 = 4;
    self->unk61 = 0;
    self->y_pos.i.hi -= 0x10;
    func_80015D60(self, 0x11);

    x_vel = FIXED(-3);
    self->timer = 0x14;
    if (self->unk2 != 0) {
        x_vel = FIXED(3);
    }
    self->y_vel.val = FIXED(4.5);
    self->x_vel.val = x_vel;
    self->unk28 = 0;
    self->unk2C = FIXED(0.34375);
}

void func_800AA20C(struct ShotObj* self)
{
    if ((self->unk70 & 0xB) || --self->timer == 0) {
        self->unk5++;
        if (self->id == 0x32) {
            func_80015D60(self, 0x18);
            self->unk68 = (struct Unk_unk68*)D_80109B9C;
            self->unk54 = D_80109B98;
            self->unk50.data = D_80109B98;
            self->unk60 = 4;
            return;
        }
        func_80015D60(self, 0x15);
        self->unk54 = D_80109BA0[0];
        self->unk50.data = D_80109BA0[0];
        self->unk68 = NULL;
        self->unk60 = 3;
        return;
    }
    if (self->animation_step.fields.relative_step == 0) {
        func_80015D60(self, 0x14);
    }
    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
}

void (*double_aerial_state_funcs[])(struct ShotObj*) = {
    func_800A9DF4,
    double_aerial_run,
    double_ball_despawn,
};
