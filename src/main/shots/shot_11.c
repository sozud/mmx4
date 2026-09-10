// ShotObj, shot_object_update_funcs[11]
// 8009B67C..8009B7F8
#include "common.h"

u8 D_80108E58[4] = { 0xFC, 0xFD, 0x06, 0x05 };

void func_8009B67C(struct ShotObj* arg0)
{
    D_80108E5C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_11", func_8009B6B8);

INCLUDE_ASM("main/nonmatchings/shots/shot_11", func_8009B734);

void func_8009B7D8(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108E5C[])(struct ShotObj*) = {
    func_8009B6B8,
    func_8009B734,
    func_8009B7D8,
};
