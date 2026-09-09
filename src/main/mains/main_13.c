// MainObj, main_object_update_funcs[13]
// 8004C734..8004CF24
#include "common.h"

void func_8004C734(struct MainObj* arg0)
{
    D_800FB858[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004C784);

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004C860);

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004C97C);

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004C9E8);

void func_8004CA14(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_13.saved_unk5;
}

void func_8004CA20(struct MainObj* arg0)
{
    D_800FB880[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004CA5C);

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004CA94);

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004CBD4);

void func_8004CC64(struct MainObj* arg0)
{
    D_800FB888[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004CCA0);

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004CDC8);

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004CE48);

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004CE94);

INCLUDE_ASM("main/nonmatchings/mains/main_13", func_8004CEF4);
