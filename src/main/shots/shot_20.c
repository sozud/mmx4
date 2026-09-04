// ShotObj, shot_object_update_funcs[20]
// 8009CF38..8009D200
#include "common.h"

void func_8009CF38(struct ShotObj* arg0)
{
    D_80108FCC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_20", func_8009CF74);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_20", func_8009D048);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_20", func_8009D1D8);

void func_8009D1F8(struct ShotObj* arg0)
{
}

void (*D_80108FCC[])(struct ShotObj*) = {
    func_8009CF74,
    func_8009D048,
    func_8009D1D8,
    func_8009D1F8,
};
