// MainObj, main_object_update_funcs[70]
// 80088BA0..80089AA4
#include "common.h"

void func_80088BA0(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_801049E4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088BE8);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088C40);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088D30);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088D8C);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088E04);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088EA4);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088F78);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088FF0);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_800890B0);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80089138);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_800891C8);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_8008924C);

void func_80089314(struct MainObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_80089334(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_70.saved_unk5;
}

void func_80089340(struct MainObj* arg0)
{
    D_80104A28[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_8008937C);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_800893DC);

void func_80089438(struct MainObj* arg0)
{
    D_80104A30[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80089474);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_800894BC);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80089524);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80089588);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80089798);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80089910);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80089984);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80089A10);
