// ShotObj, shot_object_update_funcs[48]
// 800A9964..800A9DF4
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_48", func_800A9964);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_48", func_800A9AEC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_48", func_800A9C24);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_48", func_800A9C7C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_48", func_800A9CBC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_48", func_800A9D98);

void func_800A9DB8(struct ShotObj* arg0)
{
    D_80109BC4[arg0->base.state](arg0);
}

void (*D_80109BC4[])(struct ShotObj*) = {
    func_800A9964,
    func_800A9CBC,
    func_800A9D98,
};
