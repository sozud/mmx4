// ShotObj, shot_object_update_funcs[50]
// 800AA2FC..800AA5E0
#include "common.h"

void (*D_80109BEC[])(struct ShotObj*) = {
    func_800AA20C,
    func_800AA2FC,
    func_800AA3A0,
};

INCLUDE_ASM("main/nonmatchings/shots/shot_50", func_800AA2FC);

INCLUDE_ASM("main/nonmatchings/shots/shot_50", func_800AA3A0);

INCLUDE_ASM("main/nonmatchings/shots/shot_50", func_800AA488);

void func_800AA5A4(struct ShotObj* arg0)
{
    D_80109BF8[arg0->state](arg0);
}

void (*D_80109BF8[])(struct ShotObj*) = {
    func_800AA148,
    func_800AA488,
    func_800A9D98,
};
