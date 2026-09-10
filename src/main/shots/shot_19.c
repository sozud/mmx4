// ShotObj, shot_object_update_funcs[19]
// 8009CC64..8009CF38
#include "common.h"

u8 D_80108F9C[4] = { 0, 0, 4, 4 };
u8 D_80108FA0[8] = { 3, 5, 4, 6, 4, 6, 3, 5 };
s8 D_80108FA8[4] = { 0, 0, 0, 0 };

void func_8009CC64(struct ShotObj* arg0)
{
    D_80108FAC[arg0->state](arg0);
    CollisionRelated(arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_19", func_8009CCB4);

INCLUDE_ASM("main/nonmatchings/shots/shot_19", func_8009CD80);

INCLUDE_ASM("main/nonmatchings/shots/shot_19", func_8009CDE0);

void func_8009CF18(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108FAC[])(struct ShotObj*) = {
    func_8009CCB4,
    func_8009CD80,
    func_8009CDE0,
    func_8009CF18,
};
