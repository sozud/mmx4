// MainObj, main_object_update_funcs[29]
// 8005A4CC..8005B3FC
#include "common.h"

void func_8005A4CC(struct MainObj* arg0)
{
    if (arg0->unk2 >= 0) {
        D_800FD838[arg0->state](arg0);
    } else {
        D_800FD848[arg0->state](arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005A538);

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005A6C0);

void func_8005A750(struct MainObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005A758);

void func_8005AA0C(struct MainObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005AA14);

u8 func_8005AB34(struct MainObj* arg0)
{
    s32 state;

    state = func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    if ((u8)(state - 4) >= 24) {
        state = 1;
    }
    if ((u8)(state - 4) < 8) {
        state = 2;
    }
    if ((u8)(state - 12) < 8) {
        state = 0;
    }
    if ((u8)(state - 20) < 8) {
        state = 3;
    }
    return state;
}

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005ABC0);

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005ACA0);

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005AD00);

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005AEB4);

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005AF5C);

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005B24C);

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005B2C8);
