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

void func_8006A70C(struct MainObj* arg0)
{
    arg0->ext.raw[0] = 0;
    arg0->ext.raw[1] = 0;
    arg0->ext.raw[2] = 0;
    arg0->ext.raw[3] = 0;
    arg0->ext.raw[4] = 0;
    arg0->ext.raw[5] = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

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

void func_8006AE50(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006AE80);
