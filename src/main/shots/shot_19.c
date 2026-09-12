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

void func_8009CD80(struct ShotObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 != 0) {
        arg0->unk84.value = 0x40;
        arg0->on_screen = 0;
        arg0->state++;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

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
