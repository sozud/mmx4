// MainObj, main_object_update_funcs[11]
// 8004A718..8004B8C0
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004A718);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004A78C);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004A9F4);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004AB6C);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004ACDC);

void func_8004ACF0(struct MainObj* arg0)
{
    arg0->state = 0;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004AD18);

void func_8004ADE8(struct MainObj* arg0)
{
    arg0->unk5 = SP_CUR_MAIN_OBJ->ext.main_11.saved_unk5;
}

void func_8004AE00(struct MainObj* arg0)
{
    func_8002B718((struct MovingObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004AE20);

void func_8004B040(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk15 ^= 0x40;
        func_80015D60(arg0, 0);
        if (arg0->unk2 == 0) {
            arg0->unk5 = 2;
        } else {
            arg0->unk5 = 4;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B0A0);

void func_8004B280(struct MainObj* arg0)
{
    D_800FB550[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B2BC);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B418);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B514);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B668);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B748);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B808);
