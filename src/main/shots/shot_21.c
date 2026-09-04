// ShotObj, shot_object_update_funcs[21]
// 8009D200..8009D74C
#include "common.h"

void func_8009D200(struct ShotObj* arg0)
{
    D_80108FF4[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_21", func_8009D23C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_21", func_8009D3F4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_21", func_8009D560);

void func_8009D580(struct ShotObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_21", func_8009D588);

void (*D_80108FF4[])(struct ShotObj*) = {
    func_8009D23C,
    func_8009D3F4,
    func_8009D560,
    func_8009D580,
};
