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

void func_80050BFC(struct MainObj* arg0)
{
    if (g_Player.x_pos.i.hi >= 0x18F1) {
        func_80036B18();
        arg0->ext.raw[0] = 0;
        arg0->ext.raw[1] = 0;
        arg0->ext.raw[2] = 0;
        arg0->ext.raw[3] = 0;
        arg0->ext.raw[4] = 0;
        arg0->ext.raw[5] = 0;
        engine_obj.unkF = 0x40;
        func_8002B0C8(OBJECT_HEADER(arg0));
    }
}

void func_80050C64(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_18.saved_unk5;
}

void func_80050C70(struct MainObj* arg0)
{
    D_800FC388[arg0->unk6](arg0);
}

void func_80050CAC(struct MainObj* arg0)
{
    if (arg0->unk15 == 0) {
        arg0->unk20 = FIXED(-1.375);
    } else {
        arg0->unk20 = FIXED(1.375);
    }
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = FIXED(-0.125);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->unk6 = 1;
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80050D14);

void func_80050E08(struct MainObj* arg0)
{
    D_800FC390[arg0->unk6](arg0);
}

void func_80050E44(struct MainObj* arg0)
{
    arg0->ext.main_18.unk84 = 1;
    func_80015D60(arg0, 1);
    arg0->unk7C = 1;
    arg0->unk2C = FIXED(0.0625);
    arg0->unk6 = 1;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->unk54 = (const u8*)&D_800FBF00;
    arg0->unk50 = (const u8*)&D_800FBF00;
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80050EB0);

void func_80050F60(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->collision_data = (const u16*)D_80106B74;
        arg0->unk54 = (const u8*)&D_800FBEF4;
        arg0->unk50 = (const u8*)&D_800FBEF4;
    }
    if (arg0->animation_step.fields.event == 1) {
        arg0->ext.main_18.unk84 = 0;
        arg0->ext.main_18.unk80 &= 0x3F;
        func_80015D60(arg0, 2);
        func_800527F0(arg0);
    }
}

void func_80050FE4(struct MainObj* arg0)
{
    D_800FC39C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80051020);

void func_80051060(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        if (arg0->unk15 != 0) {
            arg0->unk20 = FIXED(-3);
        } else {
            arg0->unk20 = FIXED(3);
        }
        arg0->unk28 = FIXED(0.09375);
        arg0->unk7C = 0x14;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        arg0->unk6 = 2;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800510D4(struct MainObj* arg0)
{
    if (!(arg0->unk70 & 3)) {
        func_8002B694(ANIMATED_OBJECT(arg0));
        if (arg0->unk20 == 0) {
            arg0->unk20 = 0;
            arg0->unk28 = 0;
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0x1C;
        arg0->unk6 = 3;
    }
}

void func_8005115C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_8001540C(2, 0x35, arg0);
        arg0->unk60 = 6;
        arg0->ext.main_18.unk81 = 1;
        func_80015D60(arg0, 3);
        if (arg0->unk15 != 0) {
            arg0->unk20 = FIXED(4);
        } else {
            arg0->unk20 = FIXED(-4);
        }
        arg0->unk6 = 4;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_800511E8);

void func_800512BC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));

    if (arg0->animation_step.fields.event == 2) {
        arg0->unk60 = 4;
        arg0->unk50 = (const u8*)&D_800FBEF4;
        arg0->unk54 = (const u8*)&D_800FBEF4;
    }

    if (arg0->animation_step.fields.event == 1) {
        func_80015D60(arg0, 2);
        func_800527F0(arg0);
        arg0->ext.main_18.unk83 = 0;
        arg0->ext.main_18.unk81 = 0;
        arg0->ext.main_18.unk80 = 0;
    }
}

void func_80051338(struct MainObj* arg0)
{
    D_800FC3B4[arg0->unk6](arg0);
}

void func_80051374(struct MainObj* arg0)
{
    arg0->ext.main_18.unk82 = 1;
    arg0->unk50 = (const u8*)&D_800FBF00;
    arg0->unk54 = (const u8*)&D_800FBF00;
    func_800527C0(ANIMATED_OBJECT(arg0));
    arg0->unk2C = FIXED(0.2578125);
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk7C = 0x5A;
    arg0->unk6 = 1;
}

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

void func_80051768(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->unk50 = (const u8*)&D_800FBF04;
        arg0->unk54 = (const u8*)&D_800FBF04;
    }
    if (arg0->animation_step.fields.event == 1) {
        func_80015D60(arg0, 8);
        arg0->unk6 = 1;
    }
}

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

void func_80051F94(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->unk50 = (const u8*)&D_800FBF04;
        arg0->unk54 = (const u8*)&D_800FBF04;
    }
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk68 = &D_800FBF0C;
        arg0->ext.main_18.unk86 = 0;
        arg0->unk5 = 8;
        arg0->unk6 = 0;
    }
}

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

void func_800522C8(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk2C = FIXED(0.0078125);
        arg0->unk16 = 5;
        arg0->unk24 = 0;
        arg0->unk6 = 3;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80052324);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80052374);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_800523EC);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80052444);

INCLUDE_ASM("main/nonmatchings/mains/main_18", func_80052524);

void func_80052614(struct MainObj* arg0)
{
    if (arg0->ext.main_18.unk81 == 0 && arg0->unk5C < arg0->ext.main_18.unk85 && arg0->ext.main_18.unk87 != 0 && arg0->ext.main_18.unk88 == 0) {
        arg0->ext.main_18.unk82 = 0;
        arg0->ext.main_18.unk85 = 0;
        arg0->ext.main_18.unk84 = 0;
        func_80015D60(arg0, 7);
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        arg0->unk5 = 8;
        arg0->unk6 = 0;
    }
}

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
