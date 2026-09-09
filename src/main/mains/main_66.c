// MainObj, main_object_update_funcs[66]
// 800806A0..80082434
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_800806A0);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80080700);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80080834);

void func_80080D20(struct BarObj* arg0)
{
    D_80103C0C[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80080D5C);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80080DF4);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80080F04);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_8008107C);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_800810C4);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081104);

void func_80081198(struct MainObj* arg0)
{
    D_80103C1C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_800811D4);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081230);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_8008127C);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_800812E4);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_8008134C);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_800813BC);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081404);

void func_800814E8(struct MainObj* arg0)
{
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081508);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081564);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_800815B8);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081624);

void func_800816DC(struct MainObj* arg0)
{
    D_80103C4C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081718);

void func_80081830(struct MainObj* arg0)
{
    D_80103C50[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_8008186C);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_800818C4);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081954);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_800819C4);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081AD0);

void func_80081B64(struct MainObj* arg0)
{
    D_80103C64[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081BA0);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081CF8);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081D30);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80081E44);

void func_80082014(struct MainObj* arg0)
{

    D_80103C70[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80082050);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_800820A4);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80082170);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_8008225C);

INCLUDE_ASM("main/nonmatchings/mains/main_66", func_80082354);

void func_80082404(struct MainObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}
