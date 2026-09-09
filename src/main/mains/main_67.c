// MainObj, main_object_update_funcs[67]
// 80082434..80083218
#include "common.h"

void func_80082434(struct MainObj* arg0)
{
    D_80103E84[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082470);

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082574);

void func_800826C8(struct MainObj* arg0)
{
    s32 y;

    arg0->unk18.val = arg0->x_pos.val;
    y = arg0->y_pos.val;
    arg0->unk1C.val = y;
    D_80103EAC[arg0->unk5](arg0, y);
}

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082710);

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082784);

void func_8008284C(struct MainObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8008286C(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_67.saved_unk5;
}

void func_80082878(struct MainObj* arg0)
{
    D_80103EB8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_800828B4);

void func_800829EC(struct MainObj* arg0)
{
    D_80103EBC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082A28);

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082AA8);

void func_80082B2C(struct MainObj* arg0)
{
    D_80103EC4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082B68);

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082BA4);

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082C04);

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082C70);

void func_80082CC4(struct MainObj* arg0)
{
    D_80103ED4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082D00);

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082D48);

void func_80082D9C(struct MainObj* arg0)
{
    D_80103EDC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082DD8);

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082E30);

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082E88);

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082F20);

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082FEC);

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_800830D0);

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_8008318C);
