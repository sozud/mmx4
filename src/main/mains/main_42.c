// MainObj, main_object_update_funcs[42]
// 80062D60..800631C8
#include "common.h"

void func_80062D60(struct MainObj* arg0)
{
    D_800FEF74[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_42", func_80062D9C);

void func_80062E70(struct MainObj* arg0)
{
    func_80015D60(arg0, 0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_42", func_80062E90);

INCLUDE_ASM("main/nonmatchings/mains/main_42", func_80062F60);

void func_800630AC(struct MainObj* arg0)
{
    func_80015DC8(arg0);
    func_8002B718(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_42", func_800630DC);

INCLUDE_ASM("main/nonmatchings/mains/main_42", func_800631A8);
