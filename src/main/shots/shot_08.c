// ShotObj, shot_object_update_funcs[8]
// 8009AEE4..8009B07C
#include "common.h"

u8 D_80108D84[4] = { 0xFB, 0xFC, 0x09, 0x07 };

INCLUDE_ASM("main/nonmatchings/shots/shot_08", func_8009AEE4);

void func_8009AF98(struct ShotObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002D9BC(arg0);

    if (func_8002DD04(MAIN_OBJECT(arg0)) != 0) {
        arg0->state = 2;
    }

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x10, 0x10);
        return;
    }

    arg0->state++;
}

void func_8009B020(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009B040(struct ShotObj* arg0)
{
    D_80108D88[arg0->state](arg0);
}

void (*D_80108D88[])(struct ShotObj*) = {
    func_8009AEE4,
    func_8009AF98,
    func_8009B020,
};
