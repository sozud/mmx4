// ShotObj, shot_object_update_funcs[26]
// 8009EE68..8009F240
#include "common.h"

void func_8009EE68(struct ShotObj* arg0)
{
    if (arg0->unk84 == 0) {
        CollisionRelated(arg0);
    }
    D_8010918C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_26", func_8009EEC8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_26", func_8009F160);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_26", func_8009F218);

void func_8009F238(struct ShotObj* arg0)
{
}

void (*D_8010918C[])(struct ShotObj*) = {
    func_8009EEC8,
    func_8009F160,
    func_8009F218,
    func_8009F238,
};
