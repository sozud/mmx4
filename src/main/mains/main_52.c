// MainObj, main_object_update_funcs[52]
// 8006A50C..8006AF70
#include "common.h"

void func_8006A50C(struct MainObj* arg0)
{
    D_800FFFA0[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006A55C);

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006A638);

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006A70C);

void func_8006A740(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_52.saved_unk5;
}

void func_8006A74C(struct MainObj* arg0)
{
    D_800FFFC0[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006A788);

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006A7F0);

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006A83C);

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006A998);

void func_8006AA18(struct MainObj* arg0)
{
    D_800FFFD0[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006AA54);

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006AAB4);

void func_8006AC8C(struct MainObj* arg0)
{
    D_800FFFD8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006ACC8);

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006AD84);

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006AE0C);

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006AE50);

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006AE80);
