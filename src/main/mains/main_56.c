// MainObj, main_object_update_funcs[56]
// 8006FD50..80072194
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8006FD50);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8006FEC8);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8006FFC0);

void func_800700AC(struct MainObj* arg0)
{
    arg0->on_screen = 1;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk24 = 0;
        arg0->unk5++;
        func_80015D60(arg0, 0x27);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070118);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800701DC);

void func_80070294(struct MainObj* arg0)
{
    arg0->on_screen = 1;
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
        arg0->state++;
        func_80036B18();
    }
}

void func_800702E8(struct MainObj* arg0)
{
    D_80100D44[arg0->unk5](arg0);
    if (arg0->on_screen != 0) {
        is_on_screen(BASE_OBJECT(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070348);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800703E0);

void func_800704AC(struct MainObj* arg0)
{
    arg0->unk60 = 6;
    arg0->unk50 = (const u8*)&D_80100844;
    arg0->unk54 = (const u8*)&D_80100848;
    arg0->unk67 = 1;
    arg0->unk68 = NULL;
    arg0->unk70 = 0;
    arg0->unk6++;
    arg0->ext.main_56.flags &= ~2;
    func_80015D60(arg0, 1);
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070514);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070648);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800706D4);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070778);

void func_800708DC(struct MainObj* arg0)
{
    if (arg0->unk7 == 0) {
        arg0->unk7++;
        arg0->ext.main_56.unk88 = 0;
        func_80015D60(arg0, 2);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk7 = 0;
        arg0->unk7C = 0x14;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070948);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070A38);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070C88);

void func_80070CB0(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

void func_80070CDC(struct MainObj* arg0)
{
    D_80100D9C[arg0->unk6](arg0);
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070D2C);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070DDC);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070EE8);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8007100C);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800710D4);

void func_80071228(struct MainObj* arg0)
{
    if (arg0->unk7 == 0) {
        arg0->unk7++;
        arg0->unk60 = 9;
        arg0->unk68 = NULL;
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        func_80015D60(arg0, 5);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk7 = 0;
        arg0->unk7C = 0x14;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800712A4);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800713A4);

void func_80071468(struct MainObj* arg0)
{
    D_80100DC8[arg0->unk6](arg0);
    func_80015DC8(arg0);
    func_8002B718((struct MovingObj*)arg0);
}

void func_800714C0(struct MainObj* arg0)
{
    arg0->x_pos.val += arg0->unk20;
    arg0->y_pos.val -= arg0->unk24;
    arg0->unk24 -= arg0->unk2C;
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800714F4);

void func_80071598(struct MainObj* arg0)
{
    if (arg0->unk24 > 0) {
        arg0->unk2C = -FIXED(0.8125);
        arg0->unk24 = 0;
        arg0->unk6++;
        arg0->ext.main_56.flags &= ~2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800715D4);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8007168C);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071740);

void func_800718F4(struct MainObj* arg0)
{
    if (arg0->unk7C == 0) {
        if (arg0->unk7E != 0) {
            arg0->unk6--;
            arg0->unk7E--;
        } else {
            arg0->unk6++;
            arg0->unk7 = 0;
            func_80015D60(arg0, 0xA);
        }
    } else {
        arg0->unk7C--;
    }
}

void func_8007196C(struct MainObj* arg0)
{
    if (arg0->unk7 == 0 && arg0->animation_step.fields.relative_step == 0) {
        arg0->unk7++;
        arg0->unk7C = 0x28;
        func_80015D90(ANIMATED_OBJECT(arg0), 1, 2);
    }
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 1;
        arg0->unk7 = 0;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800719FC(struct MainObj* arg0)
{
    D_80100DE0[arg0->unk6](arg0);
}

void func_80071A38(struct MainObj* arg0)
{
    D_80100DEC[arg0->unk6](arg0);
}

void func_80071A74(struct MainObj* arg0)
{
    arg0->collision_data = (const u16*)D_801060F0;
    arg0->unk42 &= 0x7FFF;
    arg0->unk6++;
    func_8001540C(2, 0xB3, arg0);
    func_80015D60(arg0, 0x16);
}

void func_80071AD8(struct MainObj* arg0)
{
    if (arg0->unk7 == 0) {
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk7++;
            arg0->unk7C = 0x78;
        }
    } else if (--arg0->unk7C == 0) {
        arg0->unk7C = 0xA;
        arg0->unk7 = 0;
        arg0->ext.main_56.unk89 = 5;
        arg0->unk6++;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071B60);

void func_80071C00(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk24 = FIXED(8);
        arg0->unk20 = 0;
        arg0->unk6++;
        func_80015D60(arg0, 7);
        func_8001540C(2, 0xAF, arg0);
    }
}

void func_80071C60(struct MainObj* arg0)
{
    if (arg0->on_screen == 0) {
        arg0->state = 1;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
        arg0->collision_data = (const u16*)D_801079F8;
    }
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_80071CB0(struct MainObj* arg0)
{
    func_8002DD04(arg0);
    D_80100DF8[arg0->unk6](arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002D9BC(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x80, 0x80);
}

void func_80071D1C(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071D30);

void func_80071EEC(struct MainObj* arg0)
{
    func_80036AE4(0x14, g_Player.unk15);
    arg0->unk7C = 0x7F;
    arg0->unk7E = 0x19;
    arg0->ext.main_56.unk89 = 0x19;
    arg0->unk5++;
    func_80015D90(ANIMATED_OBJECT(arg0), 0x16, 0);
    is_on_screen(BASE_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071F5C);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8007203C);

void func_8007211C(struct MainObj* arg0)
{
    D_80100E34[arg0->unk5](arg0);
}

void func_80072158(struct MainObj* arg0)
{
    D_80100E40[arg0->state](arg0);
}
