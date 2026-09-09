// MainObj, main_object_update_funcs[35]
// 8005EC58..8005F510
#include "common.h"

void func_8005EC58(struct MainObj* arg0)
{
    D_800FE2AC[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_35", func_8005ECA8);

INCLUDE_ASM("main/nonmatchings/mains/main_35", func_8005EE2C);

INCLUDE_ASM("main/nonmatchings/mains/main_35", func_8005EF40);

void func_8005EF6C(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_35.saved_unk5;
}

INCLUDE_ASM("main/nonmatchings/mains/main_35", func_8005EF78);

INCLUDE_ASM("main/nonmatchings/mains/main_35", func_8005EFB0);

INCLUDE_ASM("main/nonmatchings/mains/main_35", func_8005F0F4);

void func_8005F124(struct MainObj* arg0)
{
    D_800FE2D4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_35", func_8005F160);

INCLUDE_ASM("main/nonmatchings/mains/main_35", func_8005F1A4);

INCLUDE_ASM("main/nonmatchings/mains/main_35", func_8005F230);

INCLUDE_ASM("main/nonmatchings/mains/main_35", func_8005F2F4);

INCLUDE_ASM("main/nonmatchings/mains/main_35", func_8005F3D4);

INCLUDE_ASM("main/nonmatchings/mains/main_35", func_8005F47C);

INCLUDE_ASM("main/nonmatchings/mains/main_35", func_8005F4E0);
