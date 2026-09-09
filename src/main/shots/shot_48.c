// ShotObj, shot_object_update_funcs[48]
// 800A9964..800A9DF4
#include "common.h"

INCLUDE_ASM("main/nonmatchings/shots/shot_48", func_800A9964);

INCLUDE_ASM("main/nonmatchings/shots/shot_48", func_800A9AEC);

INCLUDE_ASM("main/nonmatchings/shots/shot_48", func_800A9C24);

void func_800A9C7C(struct ShotObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->on_screen = 0;
        return;
    }
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_48", func_800A9CBC);

void func_800A9D98(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A9DB8(struct ShotObj* arg0)
{
    D_80109BC4[arg0->state](arg0);
}

u8 D_80109B88[2][4] = {
    { 0xF0, 0xF2, 0x1F, 0x1B },
    { 0xFE, 0xFE, 0x10, 0x10 },
};

u8 D_80109B90[2][4] = {
    { 0xF3, 0xBD, 0x26, 0x87 },
    { 0, 8, 0x2E, 0x78 },
};

u8 D_80109B98[4] = { 0xF9, 0xFA, 0x0D, 0x0B };

u8 D_80109B9C[4] = { 0, 0, 0x0E, 0x0E };

u8 D_80109BA0[2][4] = {
    { 0xF8, 0xF8, 0x10, 0x10 },
    { 0, 0, 0x0E, 0x0E },
};

u8 D_80109BA8[2][4] = {
    { 0xFC, 0xF9, 7, 0x0A },
    { 0, 6, 3, 7 },
};

u8 D_80109BB0[4] = { 0x1A, 0x1B, 0x1A, 0x1B };

u8 D_80109BB4[4] = { 0x1C, 0x1D, 0x1C, 0x1D };

void (*D_80109BB8[3])(struct ShotObj*) = {
    func_800A9AEC,
    func_800A9C24,
    func_800A9C7C,
};

void (*D_80109BC4[])(struct ShotObj*) = {
    func_800A9964,
    func_800A9CBC,
    func_800A9D98,
};
