// MainObj, main_object_update_funcs[38]
// 80060A88..80061590
#include "common.h"

void func_80060A88(struct MainObj* arg0)
{
    D_800FE8EC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060AC4);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060BC4);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060D3C);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060DC8);

void func_80060E08(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_38.saved_unk5;
}

void func_80060E14(struct MainObj* arg0)
{
    D_800FE918[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060E50);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060E94);

void func_80060F5C(struct MainObj* arg0)
{
    D_800FE920[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060F98);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060FF8);

void func_8006104C(struct MainObj* arg0)
{
    D_800FE928[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80061088);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_800610F0);

void func_8006114C(struct MainObj* arg0)
{
    D_800FE930[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80061188);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_800611E0);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80061240);

void func_8006128C(struct MainObj* arg0)
{
    D_800FE93C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_800612C8);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80061310);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_8006135C);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80061424);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_800614E8);
