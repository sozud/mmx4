// ShotObj, shot_object_update_funcs[49]
// 800A9DF4..800AA2FC
#include "common.h"

void (*D_80109BD0[])(struct ShotObj*) = {
    func_800A9EC0,
    func_800A9F30,
    func_800A9FD0,
    func_800AA000,
};

INCLUDE_ASM("main/nonmatchings/shots/shot_49", func_800A9DF4);

INCLUDE_ASM("main/nonmatchings/shots/shot_49", func_800A9EC0);

INCLUDE_ASM("main/nonmatchings/shots/shot_49", func_800A9F30);

void func_800A9FD0(struct ShotObj* arg0)
{
    func_8002B694((struct AnimatedObj*)arg0);
    func_80015DC8(arg0);
}

void func_800AA000(struct ShotObj* arg0)
{
    func_8002B694((struct AnimatedObj*)arg0);
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_49", func_800AA030);

void func_800AA10C(struct ShotObj* arg0)
{
    D_80109BE0[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_49", func_800AA148);

INCLUDE_ASM("main/nonmatchings/shots/shot_49", func_800AA20C);

void (*D_80109BE0[])(struct ShotObj*) = {
    func_800A9DF4,
    func_800AA030,
    func_800A9D98,
};
