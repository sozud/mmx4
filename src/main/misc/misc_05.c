// MiscObj, misc_object_update_funcs[5]
// 800C8FA8..800C91B0
#include "common.h"

void func_800C8FA8(struct MiscObj* arg0)
{
    D_8010DC3C[arg0->state](arg0);
}

void func_800C8FE4(struct MiscObj* arg0)
{
    func_80015D60(arg0, 0xF);
    arg0->y_vel.val = FIXED(8.25);
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = FIXED(0.375);
    func_8002B718(MOVING_OBJECT(arg0));
    arg0->state = 1;
}

void func_800C903C(struct MiscObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->y_vel.val == 0 || *(s32*)arg0->ext.misc_24.main == 0) {
        arg0->state = 2;
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800C90A0(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_05", func_800C90C0);

INCLUDE_ASM("main/nonmatchings/misc/misc_05", func_800C90F8);

void func_800C9190(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}
