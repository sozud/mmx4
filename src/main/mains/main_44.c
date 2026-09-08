// MainObj, main_object_update_funcs[44]
// 80065930..80065B8C
#include "common.h"

#ifdef VERSION_JP
INCLUDE_ASM("main/nonmatchings/mains/main_44", func_8006596C_jp);
#endif

void func_80065930(struct MainObj* arg0)
{
    D_800FF87C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_44", func_8006596C);

INCLUDE_ASM("main/nonmatchings/mains/main_44", func_80065A54);

void func_80065B04(struct MainObj* arg0)
{
    func_8002B0C8(arg0);
}

void func_80065B24(struct MainObj* arg0)
{
    arg0->unk5 = arg0->unk94;
}

void func_80065B30(struct MainObj* arg0)
{
    D_800FF894[arg0->unk6](arg0);
}

void func_80065B6C(struct MainObj* arg0)
{
    func_80015DC8(arg0);
}
