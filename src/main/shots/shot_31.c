// ShotObj, shot_object_update_funcs[31]
// 8009FF10..800A0170
#include "common.h"

void func_8009FF10(struct ShotObj* arg0)
{
    D_80109248[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_31", func_8009FF4C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_31", func_800A00C4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_31", func_800A0150);

void (*D_80109248[])(struct ShotObj*) = {
    func_8009FF4C,
    func_800A00C4,
    func_800A0150,
};
