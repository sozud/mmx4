// ShotObj, shot_object_update_funcs[48]
// 800A9964..800A9DF4
#include "common.h"

// double_ball_init
INCLUDE_ASM("main/nonmatchings/shots/shot_48_double_ball", func_800A9964);

void double_ball_travel(struct ShotObj* self)
{
    s8 temp_a0;
    s8 temp_a2;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_v1;

    temp_s2 = self->x_pos.val - ((s16)self->unk8C.half << 16);
    temp_s1 = self->y_pos.val - (self->unk8C.halves[1] << 16);
    temp_a2 = angle_from_delta(temp_s2, temp_s1);
    if ((s16)self->unk8A == 0) {
        temp_a0 = (u8)self->unk5;
        temp_v0 = (s16)self->unk8C.half;
        temp_v1 = self->unk8C.halves[1];
        self->x_pos.val = temp_v0 << 16;
        self->y_pos.val = temp_v1 << 16;
        temp_a0 += 1;
        self->unk5 = temp_a0;
        self->timer = 0x5A;
    } else {
        self->x_pos.val -= temp_s2 / (s16)self->unk8A;
        self->y_pos.val -= temp_s1 / (s16)self->unk8A;
        self->unk8A = (u16)self->unk8A - 1;
    }
    self->unk84.value = temp_a2 & 0xFF;
    animate_object(ANIMATED_OBJECT(self));
}

void double_ball_hold(struct ShotObj* self)
{

    if (--self->timer == 0) {
        self->unk5++;
        set_animation(self, 0xD);
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void double_ball_burst(struct ShotObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->state = 2;
        self->unk5 = 0;
        self->on_screen = 0;
        return;
    }
    animate_object(self);
}

void double_ball_run(struct ShotObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    double_ball_funcs[self->unk5](self);
    if (self->unk7C->state == 2) {
        spawn_explosion(BASE_OBJECT(self));
        self->state = 2;
        self->on_screen = 0;
        return;
    }
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
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

void double_ball_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void double_ball_update(struct ShotObj* self)
{
    double_ball_state_funcs[self->state](self);
}

u8 double_ball_boxes[2][4] = {
    { 0xF0, 0xF2, 0x1F, 0x1B },
    { 0xFE, 0xFE, 0x10, 0x10 },
};

u8 double_ball_box_1[2][4] = {
    { 0xF3, 0xBD, 0x26, 0x87 },
    { 0, 8, 0x2E, 0x78 },
};

u8 double_ball_box_2[4] = { 0xF9, 0xFA, 0x0D, 0x0B };

u8 double_ball_box_3[4] = { 0, 0, 0x0E, 0x0E };

u8 double_ball_box_4[2][4] = {
    { 0xF8, 0xF8, 0x10, 0x10 },
    { 0, 0, 0x0E, 0x0E },
};

u8 double_ball_box_5[2][4] = {
    { 0xFC, 0xF9, 7, 0x0A },
    { 0, 6, 3, 7 },
};

u8 double_ball_debris_0[4] = { 0x1A, 0x1B, 0x1A, 0x1B };

u8 double_ball_debris_1[4] = { 0x1C, 0x1D, 0x1C, 0x1D };

void (*double_ball_funcs[3])(struct ShotObj*) = {
    double_ball_travel,
    double_ball_hold,
    double_ball_burst,
};

void (*double_ball_state_funcs[])(struct ShotObj*) = {
    func_800A9964,
    double_ball_run,
    double_ball_despawn,
};
