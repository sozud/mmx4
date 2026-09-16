// ShotObj, shot_object_update_funcs[6]
// 8009A984..8009AD30
#include "common.h"

u8 D_80108D40[8] = { 0xFD, 0xFA, 8, 8, 0xF7, 0xF6, 0x10, 0x13 };
u8 D_80108D48[4] = { 0, 0, 4, 4 };
s8 D_80108D4C[16] = {
    -0x0D,
    0,
    0x0D,
    0,
    -0x0A,
    -0x0C,
    0x0A,
    -0x0C,
    0,
    -0x10,
    0,
    0x10,
    -0x0A,
    0x0C,
    0x0A,
    0x0C,
};

void func_8009A984(struct ShotObj* arg0)
{
    if (arg0->unk84.value == 0) {
        CollisionRelated(arg0);
    }
    D_80108D5C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_06", func_8009A9E4);

void func_8009AC40(struct ShotObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002D9BC(arg0);
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
    } else {
        if (arg0->unk84.value == 0) {
            if (func_8002BB80(arg0, &g_Player) != 0) {
                arg0->state++;
                return;
            }
            if (arg0->unk70 != 0) {
                func_800AF808(BASE_OBJECT(arg0));
                arg0->state++;
                return;
            }
        }
        if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) != 0) {
            arg0->state++;
            return;
        }
        func_8002B318(BASE_OBJECT(arg0), 0x10, 0x10);
        return;
    }
    arg0->state++;
}

void func_8009AD08(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009AD28(struct ShotObj* arg0)
{
}

void (*D_80108D5C[])(struct ShotObj*) = {
    func_8009A9E4,
    func_8009AC40,
    func_8009AD08,
    func_8009AD28,
};
