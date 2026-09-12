// ShotObj, shot_object_update_funcs[32]
// 800A0170..800A03B8
#include "common.h"

u8 D_80109254[4] = { 0xF8, 0xCC, 0x0F, 0x23 };
u8 D_80109258[4] = { 0xF8, 0xCC, 0x0F, 0x65 };

INCLUDE_ASM("main/nonmatchings/shots/shot_32", func_800A0170);

void func_800A02FC(struct ShotObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002D9BC(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->state++;
    }
}

void func_800A035C(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800A037C(struct ShotObj* arg0)
{
    D_8010925C[arg0->state](arg0);
}

void (*D_8010925C[])(struct ShotObj*) = {
    func_800A0170,
    func_800A02FC,
    func_800A035C,
};
