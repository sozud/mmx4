// ShotObj, shot_object_update_funcs[11]
// 8009B67C..8009B7F8
#include "common.h"

u8 D_80108E58[4] = { 0xFC, 0xFD, 0x06, 0x05 };

void func_8009B67C(struct ShotObj* arg0)
{
    D_80108E5C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_11", func_8009B6B8);

void func_8009B734(struct ShotObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002D9BC(arg0);
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
    } else if (func_8002BB80(arg0, &g_Player) == 0 && func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x10, 0x10);
        return;
    }
    arg0->state = 2;
}

void func_8009B7D8(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108E5C[])(struct ShotObj*) = {
    func_8009B6B8,
    func_8009B734,
    func_8009B7D8,
};
