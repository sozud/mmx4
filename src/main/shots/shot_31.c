// ShotObj, shot_object_update_funcs[31]
// 8009FF10..800A0170
#include "common.h"

u8 D_8010923C[2][4] = {
    { 0xF8, 0xEE, 0x0F, 0x23 },
    { 0xF7, 0xF1, 0x14, 0x1B },
};
s8 D_80109244[4] = { -72, -6, -60, -51 };

void func_8009FF10(struct ShotObj* arg0)
{
    D_80109248[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_31", func_8009FF4C);

void func_800A00C4(struct ShotObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002D9BC(arg0);
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        arg0->state = 2;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
        return;
    }
    arg0->state = 2;
}

void func_800A0150(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80109248[])(struct ShotObj*) = {
    func_8009FF4C,
    func_800A00C4,
    func_800A0150,
};
