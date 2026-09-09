// MainObj, main_object_update_funcs[63]
// 8007BFF4..8007C30C
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_63", func_8007BFF4);

INCLUDE_ASM("main/nonmatchings/mains/main_63", func_8007C090);

INCLUDE_ASM("main/nonmatchings/mains/main_63", func_8007C144);

void func_8007C2B0(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8007C2D0(struct MainObj* arg0)
{
    D_80102480[arg0->state](arg0);
}
