// MainObj, main_object_update_funcs[43]
// 800631C8..80065930
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800631C8);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063234);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800632A4);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063334);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_8006346C);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063600);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_8006364C);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800636A0);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800637A8);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063814);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063854);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063914);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_8006398C);

void func_80063AE4(struct MainObj* arg0)
{
    D_800FF750[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063B20);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063DD8);

void func_80063F80(struct MainObj* arg0)
{
    D_800FF75C[arg0->unk6](arg0);
}

void func_80063FBC(struct MainObj* arg0)
{
    arg0->unk6 = 1;
    func_80015D60(arg0, 3);
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80063FE4);

void func_800640B4(struct MainObj* arg0)
{
    D_800FF768[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800640F0);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064154);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064338);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064360);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800643B0);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_8006458C);

void func_800646B0(struct MainObj* arg0)
{
    D_800FF784[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800646EC);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800648D0);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800649C0);

void func_80064AE8(struct MainObj* arg0)
{
    D_800FF790[arg0->unk6](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064B38);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064BA8);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064C0C);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064C84);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064CF4);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064DC8);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064E58);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064F24);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80064FD8);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80065088);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80065168);

void func_80065268(struct MainObj* arg0)
{
    arg0->unk7C = D_800FF7A4[(arg0->unk5C & 0x7F) >> 3];
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_8006528C);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_800652C8);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_8006530C);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_8006537C);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80065458);

void func_80065538(struct MainObj* arg0)
{
    D_800FF7AC[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80065574);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_8006565C);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80065704);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80065794);

INCLUDE_ASM("main/nonmatchings/mains/main_43", func_80065898);

void func_80065910(struct MainObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}
