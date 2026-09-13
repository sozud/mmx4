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

void func_8006A788(struct MainObj* arg0)
{
    func_8006AE50(ANIMATED_OBJECT(arg0));
    func_8006AE80(arg0);
    if (arg0->ext.main_52.unk80 == 0) {
        func_80015D60(arg0, arg0->ext.main_52.unk88 + 0x12);
    } else {
        func_80015D60(arg0, arg0->ext.main_52.unk88 + 0x17);
    }
    arg0->unk6 = 1;
}

void func_8006A7F0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk6 = 2;
        arg0->unk7C = 2;
        arg0->unk7E = 0xC;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006A83C);

void func_8006A998(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->ext.main_52.unk8C = 0;
        arg0->unk7C = 0x5A;
        if (arg0->ext.main_52.unk80 == 0) {
            arg0->unk5 = 3;
            arg0->unk6 = 0;
        } else {
            arg0->unk2C = FIXED(0.25);
            arg0->unk5 = 4;
            arg0->unk20 = 0;
            arg0->unk6 = 1;
        }
    }
}

void func_8006AA18(struct MainObj* arg0)
{
    D_800FFFD0[arg0->unk6](arg0);
}

void func_8006AA54(struct MainObj* arg0)
{
    func_8006AE50(ANIMATED_OBJECT(arg0));
    if (arg0->unk15 == 0) {
        arg0->unk20 = FIXED(-1.8);
    } else {
        arg0->unk20 = FIXED(1.8);
    }
    func_80015D60(arg0, 0);
    arg0->unk6 = 1;
}

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006AAB4);

void func_8006AC8C(struct MainObj* arg0)
{
    D_800FFFD8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006ACC8);

void func_8006AD84(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk24 == 0 && arg0->ext.main_52.unk8C != 0) {
        arg0->unk2C = 0;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
    if (arg0->unk70 & 8) {
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        func_80015D60(arg0, 0x11);
        arg0->unk6 = 2;
    }
}

void func_8006AE0C(struct MainObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.event != 0) {
        arg0->ext.main_52.unk80 = 0;
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_8006AE50(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_52", func_8006AE80);
