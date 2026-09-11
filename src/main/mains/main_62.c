// MainObj, main_object_update_funcs[62]
// 8007B90C..8007BFF4
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_62", func_8007B90C);

INCLUDE_ASM("main/nonmatchings/mains/main_62", func_8007BABC);

INCLUDE_ASM("main/nonmatchings/mains/main_62", func_8007BB90);

void func_8007BC0C(struct BarObj* arg0)
{
    D_80102214[arg0->unk5](arg0);
}

void func_8007BC48(struct MainObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_62", func_8007BC50);

void func_8007BCC4(struct MainObj* arg0)
{
    s16 timer;

    timer = arg0->unk7E;
    if (timer == 0) {
        if (func_8007BABC(arg0) == 0) {
            arg0->unk5--;
            func_80015D60(arg0, 2);
            if (arg0->ext.main_62.unk86 != 0) {
                func_8001540C(2, 0xA2, arg0);
            }
        }
    } else {
        arg0->unk7E = timer - 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_62", func_8007BD4C);

INCLUDE_ASM("main/nonmatchings/mains/main_62", func_8007BE40);

void func_8007BF74(void)
{
}

void func_8007BF7C(struct BarObj* arg0)
{
    D_80102254[arg0->unk5](arg0);
}

void func_8007BFB8(struct MainObj* arg0)
{
    arg0->on_screen = 0;
    D_8010225C[arg0->state](arg0);
}
