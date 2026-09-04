// ShotObj, shot_object_update_funcs[0]
// 800994A0..80099B30
#include "common.h"

void func_800994A0(struct ShotObj* arg0)
{
    D_80108C74[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_00", func_800994DC);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_00", func_80099784);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_00", func_8009982C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_00", func_800998D4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_00", func_800999D0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_00", func_80099A28);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_00", func_80099A8C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_00", func_80099B0C);

void (*D_80108C74[])(struct ShotObj*) = {
    func_800994DC,
    func_80099784,
    func_8009982C,
    func_80099A28,
    func_80099B0C,
    func_80099A8C,
};
