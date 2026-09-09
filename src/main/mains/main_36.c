// MainObj, main_object_update_funcs[36]
// 8005F510..8005FDBC
#include "common.h"

void func_8005F510(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FE4A8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_36", func_8005F558);

INCLUDE_ASM("main/nonmatchings/mains/main_36", func_8005F758);

INCLUDE_ASM("main/nonmatchings/mains/main_36", func_8005F844);

INCLUDE_ASM("main/nonmatchings/mains/main_36", func_8005F864);

INCLUDE_ASM("main/nonmatchings/mains/main_36", func_8005F87C);

void func_8005F9A4(struct MainObj* arg0)
{
    D_800FE4C4[arg0->unk6](arg0);
    is_on_screen((struct BaseObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_36", func_8005F9F4);

INCLUDE_ASM("main/nonmatchings/mains/main_36", func_8005FB38);

INCLUDE_ASM("main/nonmatchings/mains/main_36", func_8005FBBC);

INCLUDE_ASM("main/nonmatchings/mains/main_36", func_8005FCAC);

INCLUDE_ASM("main/nonmatchings/mains/main_36", func_8005FCD8);
