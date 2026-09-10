// ShotObj, shot_object_update_funcs[32]
// 800A0170..800A03B8
#include "common.h"

u8 D_80109254[4] = { 0xF8, 0xCC, 0x0F, 0x23 };
u8 D_80109258[4] = { 0xF8, 0xCC, 0x0F, 0x65 };

INCLUDE_ASM("main/nonmatchings/shots/shot_32", func_800A0170);

INCLUDE_ASM("main/nonmatchings/shots/shot_32", func_800A02FC);

void func_800A035C(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A037C(struct ShotObj* arg0)
{
    D_8010925C[arg0->state](arg0);
}

void (*D_8010925C[])(struct ShotObj*) = {
    func_800A0170,
    func_800A02FC,
    func_800A035C,
};
