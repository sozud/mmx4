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

INCLUDE_ASM("main/nonmatchings/shots/shot_26", func_8009F160);

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
