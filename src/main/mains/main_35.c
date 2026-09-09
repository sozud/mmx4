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

void func_8005EF40(struct MainObj* arg0)
{
    arg0->unk7A = 0;
    arg0->ext.main_35.unk80 = 0;
    arg0->ext.main_35.unk84 = 0;
    arg0->ext.main_35.saved_unk5 = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8005EF6C(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_35.saved_unk5;
}

void func_8005EF78(struct MainObj* arg0)
{
    func_80015DC8();
    arg0->unk24 = 0x60000;
    func_8002B718((struct MovingObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_35", func_8005EFB0);

void func_8005F0F4(struct MainObj* arg0)
{
    if ((g_Player.x_pos.i.hi - arg0->x_pos.i.hi) >= 0xB5) {
        arg0->unk7A = 0;
        arg0->unk5 = 2;
    }
}

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

void func_8005F4E0(struct MainObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}
