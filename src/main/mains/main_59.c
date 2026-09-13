// MainObj, main_object_update_funcs[59]
// 80074E84..8007501C
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_59", func_80074E84);

void func_80074F4C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002D9BC(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x18, 0x18);
    if ((arg0->animation_step.fields.relative_step < 0) || (func_8002B1E8(BASE_OBJECT(arg0), 0x18, 0x18) != 0)) {
        arg0->state++;
    }
}

void func_80074FC0(struct MainObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_80074FE0(struct MainObj* arg0)
{
    D_801016A8[arg0->state](arg0);
}
