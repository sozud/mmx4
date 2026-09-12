// ShotObj, shot_object_update_funcs[54]
// 800ABE08..800AC8C4
#include "common.h"

INCLUDE_ASM("main/nonmatchings/shots/shot_54", func_800ABE08);

void func_800AC114(struct ShotObj* arg0)
{
    s16 timer;

    timer = arg0->timer;
    if (timer != 0) {
        timer--;
        arg0->timer = timer;
        if (timer == 0) {
            arg0->y_vel.val = 0;
        }
    }
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x28, 0x28);
}

void func_800AC180(struct ShotObj* arg0)
{
    if (--arg0->timer == 0) {
        arg0->unk6++;
        func_8002B93C(MOVING_OBJECT(arg0),
            func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)) & 0xFF);
        arg0->x_vel.val *= 4;
        arg0->y_vel.val *= 4;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_54", func_800AC204);

void func_800AC31C(struct ShotObj* arg0)
{
    arg0->timer--;
    if (arg0->timer == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
    func_80015DC8(arg0);
}

void func_800AC364(struct ShotObj* arg0)
{
    D_80109DB8[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x28, 0x28);
}

void func_800AC3BC(struct ShotObj* arg0)
{
    s32 x_vel;

    if (arg0->unk70 & 8) {
        if (get_random() & 1) {
            x_vel = FIXED(2);
        } else {
            x_vel = FIXED(-2);
        }
        arg0->x_vel.val = x_vel;
        arg0->y_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        arg0->timer = 0x20;
        arg0->unk6++;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(arg0);
}

void func_800AC440(struct ShotObj* arg0)
{
    s16 timer;

    timer = arg0->timer - 1;
    arg0->timer = timer;
    if (timer == 0) {
        func_80015D60(arg0, 0x11);
        arg0->unk6++;
    }
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(arg0);
}

void func_800AC4A8(struct ShotObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(arg0);
}

void func_800AC4F8(struct ShotObj* arg0)
{
    D_80109DC4[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x28, 0x28);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_54", func_800AC550);

void func_800AC5BC(struct ShotObj* arg0)
{
    s16 timer;

    timer = arg0->timer - 1;
    arg0->timer = timer;
    if (timer == 0) {
        arg0->timer = 0x3C;
        arg0->unk50.data = NULL;
        arg0->unk6++;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x28, 0x28);
}

void func_800AC610(struct ShotObj* arg0)
{
    arg0->timer--;
    if (arg0->timer == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
    }
    if (arg0->timer & 1) {
        func_8002B318(BASE_OBJECT(arg0), 0x28, 0x28);
    }
}

void func_800AC66C(struct ShotObj* arg0)
{
    D_80109DD0[arg0->unk6](arg0);
}

void func_800AC6A8(struct ShotObj* arg0)
{
    func_8002B718((struct MovingObj*)arg0);
    func_80015DC8(arg0);
    func_8002B318((struct BaseObj*)arg0, 0x28, 0x28);
}

void func_800AC6E8(struct ShotObj* arg0)
{
    func_8009216C(arg0);
}

void func_800AC708(struct ShotObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/shots/shot_54", func_800AC710);

void func_800AC7CC(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800AC7EC(struct ShotObj* arg0)
{
    if (arg0->unk7C->unk94 != 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
    }
    arg0->on_screen = 0;
    D_80109DF8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_54", func_800AC848);

u8 D_80109D90[4] = { 0xF5, 0xFB, 9, 9 };

u8 D_80109D94[4] = { 0xF9, 0xF9, 0x0C, 0x0C };

u8 D_80109D98[4] = { 0xF6, 0xF8, 0x0E, 0x0E };

u8 D_80109D9C[4] = { 0xFC, 0xE7, 5, 0x35 };

u8 D_80109DA0[4] = { 0xE5, 0xFC, 0x35, 5 };

u8 D_80109DA4[4] = { 0xF1, 0xFA, 0x15, 9 };

u8 D_80109DA8[4] = { 0xFF, 0xFF, 6, 6 };

u8 D_80109DAC[4] = { 0xFE, 0, 0x0B, 0x0C };

s16 D_80109DB0[4] = { 2, 1, 0, -1 };

void (*D_80109DB8[3])(struct ShotObj*) = {
    func_800AC180,
    func_800AC204,
    func_800AC31C,
};

void (*D_80109DC4[3])(struct ShotObj*) = {
    func_800AC3BC,
    func_800AC440,
    func_800AC4A8,
};

void (*D_80109DD0[3])(struct ShotObj*) = {
    func_800AC550,
    func_800AC5BC,
    func_800AC610,
};

void (*D_80109DDC[7])(struct ShotObj*) = {
    func_800AC6E8,
    func_800AC708,
    func_800AC114,
    func_800AC364,
    func_800AC4F8,
    func_800AC66C,
    func_800AC6A8,
};

void (*D_80109DF8[])(struct ShotObj*) = {
    func_800ABE08,
    func_800AC710,
    func_800AC7CC,
};
