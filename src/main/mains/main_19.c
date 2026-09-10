// MainObj, main_object_update_funcs[19]
// 8005284C..8005458C
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_8005284C);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_800528BC);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80052A68);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80052B94);

void func_80052C2C(struct MainObj* arg0)
{
    arg0->unk7C++;
    D_800FC7B8[arg0->unk6](arg0);
}

void func_80052C70(struct MainObj* arg0)
{
    func_8002B718((struct MovingObj*)arg0);
    CollisionRelated((struct PlayerObj*)arg0);
    if (arg0->unk70 != 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80052CB8);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80052E94);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_800531B4);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80053224);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80053274);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80053338);

void func_800535CC(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk6 = 0;
    } else {
        func_80015DC8(arg0);
    }
}

void func_80053604(struct MainObj* arg0)
{
    D_800FC7DC[arg0->unk6](arg0);
}

void func_80053640(struct MainObj* arg0)
{
    arg0->unk6 = 1;
    arg0->unk7C = 0;
    func_80015D60(arg0,
        D_800FC7E4[SP_CUR_MAIN_OBJ->ext.main_19.animation_index >> 1]);
}

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_8005368C);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_800537E0);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_8005398C);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80053A88);

u8 func_80053B18(struct PlayerObj* arg0, s16 arg1, s16 arg2)
{
    arg1 = arg0->x_pos.i.hi + arg1;
    arg2 = arg0->y_pos.i.hi + arg2;
    return func_8002D724(arg0, arg1, arg2);
}

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80053B54);

void func_80053D04(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80053D24);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80053EB8);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_8005402C);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_8005440C);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80054518);
