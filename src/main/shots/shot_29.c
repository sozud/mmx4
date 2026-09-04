// ShotObj, shot_object_update_funcs[29]
// 8009F638..8009FB60
#include "common.h"

void func_8009F638(struct ShotObj* arg0)
{
    D_801091F0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_29", func_8009F674);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_29", func_8009F7C0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_29", func_8009F89C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_29", func_8009F94C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_29", func_8009F9E0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_29", func_8009FB38);

void func_8009FB58(struct ShotObj* arg0)
{
}

void (*D_801091F0[])(struct ShotObj*) = {
    func_8009F674,
    func_8009F7C0,
    func_8009FB38,
    func_8009FB58,
};
