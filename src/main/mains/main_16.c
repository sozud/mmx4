// MainObj, main_object_update_funcs[16]
// 8004E890..8004FF90
#include "common.h"

void func_8004E890(struct MainObj* arg0)
{
    D_800FBD8C[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004E8E0);

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004EA88);

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004EC44);

void func_8004ECB0(struct MainObj* arg0)
{
    arg0->ext.raw[0] = 0;
    arg0->ext.raw[1] = 0;
    arg0->ext.raw[2] = 0;
    arg0->ext.raw[3] = 0;
    arg0->ext.raw[4] = 0;
    arg0->ext.raw[5] = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8004ECE4(struct MainObj* arg0)
{
    D_800FBDC8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004ED20);

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004ED60);

void func_8004EF14(struct MainObj* arg0)
{
    if (arg0->unk70 & 8) {
        func_80015D60(arg0, 3);
        arg0->unk54 = (const u8*)&D_800FBBBC;
        arg0->unk67 = 0;
        func_8004FD38(arg0, 5);
        func_8004FD38(arg0, 2);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        return;
    }

    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8004EFA4(struct MainObj* arg0)
{
    D_800FBDD0[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004EFE0);

void func_8004F0C4(struct MainObj* arg0)
{
    arg0->unk24 = FIXED(8.25);
    arg0->unk2C = FIXED(0.375);
    arg0->unk67 = 1;
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->unk6 = 2;
}

void func_8004F118(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk24 == 0) {
        arg0->ext.main_16.unk90 = 0;
        if (arg0->ext.main_16.unk80 == 0) {
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            arg0->unk67 = 0;
            return;
        }
        func_8004FC50(ANIMATED_OBJECT(arg0));
        func_80015D60(arg0, 6);
        arg0->ext.main_16.unk80 = 0;
        arg0->unk5 = 7;
        arg0->unk6 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004F1A0);

void func_8004F228(struct MainObj* arg0)
{
    D_800FBDDC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004F264);

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004F2A0);

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004F34C);

void func_8004F424(struct MainObj* arg0)
{
    D_800FBDE8[arg0->unk6](arg0);
}

void func_8004F460(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 7);
        arg0->unk6 = 1;
        arg0->unk7C = 8;
        arg0->ext.main_16.unk80 = 0x18;
        arg0->ext.main_16.unk88 = 0;
        if (arg0->unk15 == 0) {
            arg0->ext.main_16.unk84 = -4;
        } else {
            arg0->ext.main_16.unk84 = 4;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004F4D4);

void func_8004F62C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 2);
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk67 = 0;
    }
}

void func_8004F67C(struct MainObj* arg0)
{
    D_800FBDF4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004F6B8);

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004F7D0);

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004F910);

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004F9B4);

void func_8004FAAC(struct MainObj* arg0)
{
    if (g_Player.x_pos.i.hi - arg0->x_pos.i.hi >= 0x11) {
        arg0->unk5 = 2;
        arg0->y_pos.u.hi -= 0x28;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004FAE4);

void func_8004FBF4(struct MainObj* arg0)
{
    if ((arg0->unk67 == 0) && (arg0->unk5 != 0xA) && !(arg0->unk70 & 8)) {
        arg0->unk5 = 3;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk28 = 0;
        arg0->unk67 = 1;
    }
}

void func_8004FC50(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004FC80);

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004FD38);
