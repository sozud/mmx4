// ShotObj, shot_object_update_funcs[36]
// 800A3924..800A3C78
#include "common.h"

void func_800A3924(struct ShotObj* arg0)
{
    D_8010978C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_36", func_800A3960);

INCLUDE_ASM("main/nonmatchings/shots/shot_36", func_800A3A4C);

void func_800A3C50(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A3C70(struct ShotObj* arg0)
{
}

void (*D_8010978C[])(struct ShotObj*) = {
    func_800A3960,
    func_800A3A4C,
    func_800A3C50,
    func_800A3C70,
};
