// ShotObj, shot_object_update_funcs[27]
// 8009F240..8009F46C
#include "common.h"

u8 D_8010919C[4] = { 0xFD, 0xFD, 5, 5 };
s8 D_801091A0[20] = {
    2,
    -0x16,
    -0x0D,
    -0x19,
    -0x12,
    -0x11,
    -0x12,
    -5,
    -0x0C,
    5,
    2,
    -0x1D,
    -9,
    -0x1E,
    -0x12,
    -0x17,
    -0x15,
    -0x0B,
    -0x0C,
    -3,
};

void func_8009F240(struct ShotObj* arg0)
{
    D_801091B4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_27", func_8009F27C);

void func_8009F3A8(struct ShotObj* arg0)
{
    struct ShotObj* shot = arg0;

    func_80015DC8(ANIMATED_OBJECT(shot));
    func_8002B718(MOVING_OBJECT(shot));
    func_8002D9BC(shot);
    if (func_8002BB80(MAIN_OBJECT(shot), MAIN_OBJECT(&g_Player)) == 0) {
        if (func_8002DD04(MAIN_OBJECT(shot)) < 0) {
            func_800AF808(BASE_OBJECT(shot));
            shot->state = 2;
        }
        if (func_8002B1E8(BASE_OBJECT(shot), 0x20, 0x20) == 0) {
            func_8002B318(BASE_OBJECT(shot), 0x10, 0x10);
            return;
        }
    }
    shot->state = 2;
}

void func_8009F44C(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_801091B4[])(struct ShotObj*) = {
    func_8009F27C,
    func_8009F3A8,
    func_8009F44C,
};
