// ShotObj, shot_object_update_funcs[36]
// 800A3924..800A3C78
#include "common.h"

void func_800A3924(struct ShotObj* arg0)
{
    D_8010978C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_36", func_800A3960);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_36", func_800A3A4C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_36", func_800A3C50);

void func_800A3C70(struct ShotObj* arg0)
{
}

void (*D_8010978C[])(struct ShotObj*) = {
    func_800A3960,
    func_800A3A4C,
    func_800A3C50,
    func_800A3C70,
};
