// MainObj, main_object_update_funcs[55]
// 8006EB40..8006FD50
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006EB40);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006ECC4);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006ED44);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006EF28);

void func_8006F0A0(struct MainObj* arg0)
{
    D_801007F8[arg0->unk2](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F0DC);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F244);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F304);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F41C);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F494);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F504);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F584);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F5F4);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F7B4);

void func_8006F83C(struct MainObj* arg0)
{
    func_80015DC8(arg0);
    func_8002B718(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006F86C);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006FA24);

void func_8006FABC(struct MainObj* arg0)
{
    engine_obj.enable_boss = 0;
    func_8002B108(OBJECT_HEADER(arg0));
}

void func_8006FAE4(struct MainObj* arg0)
{
    D_80100838[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006FB20);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006FBFC);

INCLUDE_ASM("main/nonmatchings/mains/main_55", func_8006FCB8);
