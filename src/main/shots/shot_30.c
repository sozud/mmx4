// ShotObj, shot_object_update_funcs[30]
// 8009FB60..8009FF10
#include "common.h"

void func_8009FB60(struct ShotObj* arg0)
{
    D_8010922C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_30", func_8009FB9C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_30", func_8009FD00);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_30", func_8009FE38);

void func_8009FE58(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_30", func_8009FE60);

void (*D_8010922C[])(struct ShotObj*) = {
    func_8009FB9C,
    func_8009FD00,
    func_8009FE38,
    func_8009FE58,
};
