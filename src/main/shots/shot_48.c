// ShotObj, shot_object_update_funcs[48]
// 800A9964..800A9DF4
#include "common.h"

INCLUDE_ASM("main/nonmatchings/shots/shot_48", func_800A9964);

INCLUDE_ASM("main/nonmatchings/shots/shot_48", func_800A9AEC);

INCLUDE_ASM("main/nonmatchings/shots/shot_48", func_800A9C24);

void func_800A9C7C(struct ShotObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->on_screen = 0;
        return;
    }
    func_80015DC8();
}

INCLUDE_ASM("main/nonmatchings/shots/shot_48", func_800A9CBC);

void func_800A9D98(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A9DB8(struct ShotObj* arg0)
{
    D_80109BC4[arg0->state](arg0);
}

void (*D_80109BC4[])(struct ShotObj*) = {
    func_800A9964,
    func_800A9CBC,
    func_800A9D98,
};
