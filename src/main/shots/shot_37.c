// ShotObj, shot_object_update_funcs[37]
// 800A3C78..800A428C
#include "common.h"

void func_800A3C78(struct ShotObj* arg0)
{
    D_801097CC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_37", func_800A3CB4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_37", func_800A3FEC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_37", func_800A4230);

void func_800A4284(struct ShotObj* arg0)
{
}

void (*D_801097CC[])(struct ShotObj*) = {
    func_800A3CB4,
    func_800A3FEC,
    func_800A4230,
    func_800A4284,
};
