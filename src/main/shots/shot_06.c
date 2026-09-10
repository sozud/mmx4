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

INCLUDE_ASM("main/nonmatchings/shots/shot_06", func_8009AC40);

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
