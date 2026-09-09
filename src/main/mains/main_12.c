// MainObj, main_object_update_funcs[12]
// 8004B8C0..8004C734
#include "common.h"

void func_8004B8C0(struct MainObj* arg0)
{
    D_800FB6A8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004B8FC);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004BAF8);

void func_8004BC14(struct MainObj* arg0)
{
    arg0->unk5 = SP_CUR_MAIN_OBJ->ext.main_12.saved_unk5;
}

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004BC2C);

void func_8004BCC8(struct MainObj* arg0)
{
    arg0->unk5 = 4;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->unk7E = 8;
    func_80015DC8();
}

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004BCFC);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004BF5C);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004C210);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004C394);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004C56C);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004C654);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004C694);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004C6C4);
