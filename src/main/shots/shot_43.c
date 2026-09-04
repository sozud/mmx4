// ShotObj, shot_object_update_funcs[43]
// 800A6960..800A6FCC
#include "common.h"

void func_800A6960(struct ShotObj* arg0)
{
    D_801099C0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_43", func_800A699C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_43", func_800A6C00);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_43", func_800A6C7C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_43", func_800A6DCC);

void func_800A6DEC(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_43", func_800A6DF4);

void (*D_801099C0[])(struct ShotObj*) = {
    func_800A699C,
    func_800A6C00,
    func_800A6C7C,
    func_800A6DCC,
    func_800A6DEC,
};
