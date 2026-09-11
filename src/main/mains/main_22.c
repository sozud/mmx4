// MainObj, main_object_update_funcs[22]
// 80054FE8..80055E04
#include "common.h"

void func_80054FE8(struct MainObj* arg0)
{
    D_800FCAEC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_22", func_80055024);

INCLUDE_ASM("main/nonmatchings/mains/main_22", func_80055164);

void func_8005529C(struct MainObj* arg0)
{
    arg0->ext.main_22.saved_unk5 = 0;
    arg0->ext.main_22.unk84 = 0;
    arg0->ext.main_22.unk94 = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_800552C4(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_22.saved_unk5;
}

void func_800552D0(struct MainObj* arg0)
{
    D_800FCB14[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_22", func_8005530C);

INCLUDE_ASM("main/nonmatchings/mains/main_22", func_80055358);

void func_800555B0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->ext.main_22.unk84 == 0) {
        func_80015D60(arg0, 0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80055604(struct MainObj* arg0)
{
    D_800FCB20[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_22", func_80055640);

INCLUDE_ASM("main/nonmatchings/mains/main_22", func_8005567C);

void func_800556D4(struct MainObj* arg0)
{
    D_800FCB28[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_22", func_80055710);

void func_80055758(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->ext.main_22.unk84 == 0) {
        func_800559BC(arg0);
        arg0->ext.main_22.unk84 = 0x1E;
        arg0->unk6++;
    }
}

void func_800557B0(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->ext.main_22.unk84 == 0) {
        arg0->unk6 = 0;
        arg0->unk5++;
    }
}

void func_800557FC(struct MainObj* arg0)
{
    D_800FCB34[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_22", func_80055838);

void func_80055880(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->ext.main_22.unk84 == 0) {
        func_80015D60(arg0, 0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_800558D4(struct MainObj* arg0)
{
    D_800FCB3C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_22", func_80055910);

INCLUDE_ASM("main/nonmatchings/mains/main_22", func_8005594C);

void func_800559B4(void)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_22", func_800559BC);

INCLUDE_ASM("main/nonmatchings/mains/main_22", func_80055C54);
