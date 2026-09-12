// MainObj, main_object_update_funcs[70]
// 80088BA0..80089AA4
#include "common.h"

void func_80088BA0(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_801049E4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088BE8);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088C40);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088D30);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088D8C);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088E04);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088EA4);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088F78);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80088FF0);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_800890B0);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80089138);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_800891C8);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_8008924C);

void func_80089314(struct MainObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_80089334(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_70.saved_unk5;
}

void func_80089340(struct MainObj* arg0)
{
    D_80104A28[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_8008937C);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_800893DC);

void func_80089438(struct MainObj* arg0)
{
    D_80104A30[arg0->unk6](arg0);
}

void func_80089474(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 2);
    arg0->unk7C = 0x27;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_800894BC);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80089524);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80089588);

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80089798);

void func_80089910(struct MainObj* arg0)
{
    s16 timer;

    if (arg0->ext.main_70.unk87 != 0) {
        D_80104A4C[arg0->ext.main_70.unk86](arg0);
    } else {
        timer = arg0->ext.main_70.unk80 - 1;
        arg0->ext.main_70.unk80 = timer;
        if (timer == 0) {
            arg0->ext.main_70.unk87 = 1;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_70", func_80089984);

void func_80089A10(struct MainObj* arg0)
{
    s16 timer;

    timer = arg0->ext.main_70.unk82 - 1;
    arg0->ext.main_70.unk82 = timer;
    if (timer == 0) {
        arg0->ext.main_70.unk80 = 0x28;
        need_palette_load |= 1;
        arg0->ext.main_70.unk82 = 4;
        arg0->ext.main_70.unk86 ^= 1;
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        arg0->ext.main_70.unk87 = 0;
    } else {
        g_FilterAmountR = 0x1F;
        g_FilterAmountG = 0x3E0;
        g_FilterAmountB = 0x7C00;
    }
}
