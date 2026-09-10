// ShotObj, shot_object_update_funcs[51]
// 800AA5E0..800AAAD4
#include "common.h"

void (*D_80109C04[])(struct ShotObj*) = {
    func_800AA20C,
    func_800AA5E0,
    func_800AA68C,
    func_800AA730,
    func_800AA7B4,
    func_800AA85C,
    func_800AA954,
};

INCLUDE_ASM("main/nonmatchings/shots/shot_51", func_800AA5E0);

INCLUDE_ASM("main/nonmatchings/shots/shot_51", func_800AA68C);

INCLUDE_ASM("main/nonmatchings/shots/shot_51", func_800AA730);

INCLUDE_ASM("main/nonmatchings/shots/shot_51", func_800AA7B4);

INCLUDE_ASM("main/nonmatchings/shots/shot_51", func_800AA85C);

void func_800AA954(struct ShotObj* arg0)
{
    arg0->timer--;
    if (arg0->timer == 0) {
        arg0->unk5 = 3;
    }
    func_80015DC8();
}

INCLUDE_ASM("main/nonmatchings/shots/shot_51", func_800AA994);

void func_800AAA98(struct ShotObj* arg0)
{
    D_80109C20[arg0->state](arg0);
}

void (*D_80109C20[])(struct ShotObj*) = {
    func_800AA148,
    func_800AA994,
    func_800A9D98,
};
