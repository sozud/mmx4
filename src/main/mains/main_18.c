// MainObj, main_object_update_funcs[18]
// 80050708..8005284C
#include "common.h"

void func_80050708(struct MainObj* arg0)
{
    D_800FC344[arg0->state](arg0);
    if (arg0->ext.main_18.unk82 == 0 && arg0->state < 2) {
        CollisionRelated(PLAYER_OBJECT(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_8005077C);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80050874);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80050A9C);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80050BC4);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80050BFC);

void func_80050C64(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_18.saved_unk5;
}

void func_80050C70(struct MainObj* arg0)
{
    D_800FC388[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80050CAC);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80050D14);

void func_80050E08(struct MainObj* arg0)
{
    D_800FC390[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80050E44);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80050EB0);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80050F60);

void func_80050FE4(struct MainObj* arg0)
{
    D_800FC39C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80051020);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80051060);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_800510D4);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_8005115C);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_800511E8);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_800512BC);

void func_80051338(struct MainObj* arg0)
{
    D_800FC3B4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80051374);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_800513DC);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_800514A4);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80051564);

void func_80051630(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60((struct Unk19*)arg0, 6);
        arg0->unk6 = 5;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80051678);

void func_8005172C(struct MainObj* arg0)
{
    D_800FC3CC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80051768);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_800517D0);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80051A4C);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80051B74);

void func_80051C94(struct MainObj* arg0)
{
    D_800FC3DC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80051CD0);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80051D60);

void func_80051F68(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 10;
        arg0->unk6 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80051F94);

void func_80052008(struct MainObj* arg0)
{
    D_800FC3EC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80052044);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_8005216C);

void func_800521B0(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 9;
        arg0->unk6 = 0;
    }
}

void func_800521DC(struct MainObj* arg0)
{
    D_800FC3F8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80052218);

void func_800522A8(struct MainObj* arg0)
{
    if (g_Player.unkC0 == -1) {
        arg0->unk6 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_800522C8);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80052324);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80052374);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_800523EC);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80052444);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80052524);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80052614);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_800526AC);

void func_800527C0(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_800527F0);
