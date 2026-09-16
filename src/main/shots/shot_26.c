// ShotObj, shot_object_update_funcs[26]
// 8009EE68..8009F240
#include "common.h"

u8 D_80109170[8] = { 0xFD, 0xFA, 8, 8, 0xF7, 0xF6, 0x10, 0x13 };
u8 D_80109178[4] = { 0, 0, 4, 4 };
s8 D_8010917C[16] = {
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

void func_8009EE68(struct ShotObj* arg0)
{
    if (arg0->unk84.value == 0) {
        CollisionRelated(arg0);
    }
    D_8010918C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_26", func_8009EEC8);

void func_8009F160(struct ShotObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002D9BC(arg0);
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
    } else {
        if (func_8002BB80(arg0, &g_Player) != 0) {
            arg0->state++;
            return;
        }
        if (arg0->unk70 != 0) {
            func_800AF808(BASE_OBJECT(arg0));
            arg0->state++;
            return;
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

void func_8009F218(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009F238(struct ShotObj* arg0)
{
}

void (*D_8010918C[])(struct ShotObj*) = {
    func_8009EEC8,
    func_8009F160,
    func_8009F218,
    func_8009F238,
};
