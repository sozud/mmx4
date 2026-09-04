// ShotObj, shot_object_update_funcs[6]
// 8009A984..8009AD30
#include "common.h"

void func_8009A984(struct ShotObj* arg0)
{
    if (arg0->unk84 == 0) {
        CollisionRelated(arg0);
    }
    D_80108D5C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_06", func_8009A9E4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_06", func_8009AC40);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_06", func_8009AD08);

void func_8009AD28(struct ShotObj* arg0)
{
}

void (*D_80108D5C[])(struct ShotObj*) = {
    func_8009A9E4,
    func_8009AC40,
    func_8009AD08,
    func_8009AD28,
};
