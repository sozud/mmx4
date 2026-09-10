// MainObj, main_object_update_funcs[56]
// 8006FD50..80072194
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8006FD50);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8006FEC8);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8006FFC0);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800700AC);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070118);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800701DC);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070294);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800702E8);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070348);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800703E0);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800704AC);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070514);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070648);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800706D4);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80070778);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800708DC);

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

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071228);

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

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_800718F4);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8007196C);

void func_800719FC(struct MainObj* arg0)
{
    D_80100DE0[arg0->unk6](arg0);
}

void func_80071A38(struct MainObj* arg0)
{
    D_80100DEC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071A74);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071AD8);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071B60);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071C00);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071C60);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071CB0);

void func_80071D1C(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
}

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071D30);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071EEC);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_80071F5C);

INCLUDE_ASM("main/nonmatchings/mains/main_56", func_8007203C);

void func_8007211C(struct BarObj* arg0)
{
    D_80100E34[arg0->unk5](arg0);
}

void func_80072158(struct MainObj* arg0)
{
    D_80100E40[arg0->state](arg0);
}
