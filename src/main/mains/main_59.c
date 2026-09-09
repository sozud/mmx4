// MainObj, main_object_update_funcs[59]
// 80074E84..8007501C
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_59", func_80074E84);

INCLUDE_ASM("main/nonmatchings/mains/main_59", func_80074F4C);

void func_80074FC0(struct MainObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_80074FE0(struct MainObj* arg0)
{
    D_801016A8[arg0->state](arg0);
}
