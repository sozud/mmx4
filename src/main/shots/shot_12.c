// ShotObj, shot_object_update_funcs[12]
// 8009B7F8..8009BD28
#include "common.h"

void func_8009B7F8(struct ShotObj* arg0)
{
    D_80108E9C[arg0->base.state](arg0);
    if (arg0->base.state >= 3) {
        CollisionRelated(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_12", func_8009B85C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_12", func_8009B9B0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_12", func_8009BA4C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_12", func_8009BA6C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_12", func_8009BAE8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_12", func_8009BC14);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_12", func_8009BD08);

void (*D_80108E9C[])(struct ShotObj*) = {
    func_8009B85C,
    func_8009B9B0,
    func_8009BA4C,
    func_8009BA6C,
    func_8009BAE8,
    func_8009BC14,
    func_8009BD08,
};
