// ShotObj, shot_object_update_funcs[43]
// 800A6960..800A6FCC
#include "common.h"

void func_800A6960(struct ShotObj* arg0)
{
    D_801099C0[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_43", func_800A699C);

INCLUDE_ASM("main/nonmatchings/shots/shot_43", func_800A6C00);

INCLUDE_ASM("main/nonmatchings/shots/shot_43", func_800A6C7C);

void func_800A6DCC(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A6DEC(struct ShotObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/shots/shot_43", func_800A6DF4);

u8 D_801099B0[4] = { 0xF7, 0xFB, 0x0C, 0x08 };

u8 D_801099B4[4] = { 0xFA, 0xFA, 0x0C, 0x0D };

s32 D_801099B8[2] = { -0x40000, 0x40000 };

void (*D_801099C0[])(struct ShotObj*) = {
    func_800A699C,
    func_800A6C00,
    func_800A6C7C,
    func_800A6DCC,
    func_800A6DEC,
};
