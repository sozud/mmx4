// MainObj, main_object_update_funcs[51]
// 80069A94..8006A50C
#include "common.h"

void func_80069A94(struct MainObj* arg0)
{
    D_800FFD84[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_51", func_80069AD0);

INCLUDE_ASM("main/nonmatchings/mains/main_51", func_80069BE4);

INCLUDE_ASM("main/nonmatchings/mains/main_51", func_80069CE4);

void func_80069D74(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_80069D94(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_51.saved_unk5;
}

void func_80069DA0(struct MainObj* arg0)
{
    D_800FFDB0[arg0->unk6](arg0);
}

void func_80069DDC(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80069E28(struct MainObj* arg0)
{
    D_800FFDB4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_51", func_80069E64);

INCLUDE_ASM("main/nonmatchings/mains/main_51", func_80069F28);

void func_80069FDC(struct MainObj* arg0)
{
    D_800FFDBC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_51", func_8006A018);

INCLUDE_ASM("main/nonmatchings/mains/main_51", func_8006A078);

void func_8006A0E4(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_8006A130(struct MainObj* arg0)
{
    D_800FFDC8[arg0->unk6](arg0);
}

void func_8006A16C(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    func_80015D60(arg0, 6);
    arg0->unk7C = 0x1A;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_51", func_8006A1B4);

INCLUDE_ASM("main/nonmatchings/mains/main_51", func_8006A208);

INCLUDE_ASM("main/nonmatchings/mains/main_51", func_8006A26C);

INCLUDE_ASM("main/nonmatchings/mains/main_51", func_8006A2BC);

INCLUDE_ASM("main/nonmatchings/mains/main_51", func_8006A388);

INCLUDE_ASM("main/nonmatchings/mains/main_51", func_8006A450);
