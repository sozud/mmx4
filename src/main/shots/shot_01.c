// ShotObj, shot_object_update_funcs[1]
// 80099B30..80099D10
#include "common.h"

void func_80099B30(struct ShotObj* arg0)
{
    D_80108CAC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_01", func_80099B6C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_01", func_80099C68);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_01", func_80099CF0);

void (*D_80108CAC[])(struct ShotObj*) = {
    func_80099B6C,
    func_80099C68,
    func_80099CF0,
};
