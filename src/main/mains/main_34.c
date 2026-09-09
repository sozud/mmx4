// MainObj, main_object_update_funcs[34]
// 8005E570..8005EC58
#include "common.h"

void func_8005E570(struct MainObj* arg0)
{
    D_800FE168[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005E5C0);

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005E754);

void func_8005E7CC(struct MainObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005E7EC);

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005E860);

void func_8005E8B4(struct MainObj* arg0)
{
    D_800FE19C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005E8F0);

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005E9C0);

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005EA18);

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005EA78);

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005EAF8);

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005EB40);

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005EBF4);

void func_8005EC38(struct MainObj* arg0)
{
    func_8002B718((struct MovingObj*)arg0);
}
