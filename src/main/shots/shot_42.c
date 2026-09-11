// ShotObj, shot_object_update_funcs[42]
// 800A6374..800A6960
#include "common.h"

void func_800A6374(struct ShotObj* arg0)
{
    D_80109998[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_42", func_800A63B0);

INCLUDE_ASM("main/nonmatchings/shots/shot_42", func_800A6510);

INCLUDE_ASM("main/nonmatchings/shots/shot_42", func_800A6600);

INCLUDE_ASM("main/nonmatchings/shots/shot_42", func_800A666C);

void func_800A6794(struct ShotObj* arg0)
{
    s16 timer;

    timer = --arg0->timer;
    if (timer == 0) {
        arg0->state = 2;
        return;
    }
    if (!(timer & 3)) {
        func_800A666C(arg0, 0x10, 0x10);
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_42", func_800A67FC);

INCLUDE_ASM("main/nonmatchings/shots/shot_42", func_800A6860);

void func_800A6940(struct ShotObj* arg0)
{
    arg0->on_screen = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

u8 D_8010995C[4] = { 0xF8, 0xF8, 0x0F, 0x0E };

u8 D_80109960[4] = { 0, 0, 4, 4 };

u8 D_80109964[4] = { 0xF6, 0xF6, 0x13, 0x13 };

s16 D_80109968[8][2] = {
    { -0x18, 0 },
    { -0x16, -0x12 },
    { -0x0B, -0x20 },
    { 3, -0x2A },
    { 0x1B, -0x29 },
    { 0x2F, -0x23 },
    { 0x33, -0x10 },
    { 0x33, 2 },
};

u8 D_80109988[8] = { 0x10, 0x0E, 0x0C, 0x0A, 6, 4, 2, 0 };

u8 D_80109990[8] = { 0, 2, 4, 6, 0x0A, 0x0C, 0x0E, 0x10 };

void (*D_80109998[])(struct ShotObj*) = {
    func_800A63B0,
    func_800A6860,
    func_800A6940,
};

void (*D_801099A4[3])(struct ShotObj*) = {
    func_800A6510,
    func_800A6600,
    func_800A6794,
};
