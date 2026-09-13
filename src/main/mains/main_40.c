// MainObj, main_object_update_funcs[40]
// 80061DC0..800623C4
#include "common.h"

void func_80061DC0(struct MainObj* arg0)
{
    D_800FEA78[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_40", func_80061DFC);

INCLUDE_ASM("main/nonmatchings/mains/main_40", func_80061F2C);

INCLUDE_ASM("main/nonmatchings/mains/main_40", func_800620C8);

void func_800621C0(struct MainObj* arg0)
{
    u8 state = arg0->ext.main_40.unk80;
    s32 offset;

    if (state >= 2U) {
        offset = (state - 2) * 2;
        ((void (*)(s32, s32, s32))func_800DABE4)(arg0->ext.main_40.unk81 + 0xB,
            arg0->x_pos.i.hi + D_800FEA5C[offset],
            arg0->y_pos.i.hi + D_800FEA5C[offset + 1]);
        func_80062240(arg0);
    }
    func_8002B108(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_40", func_80062240);

INCLUDE_ASM("main/nonmatchings/mains/main_40", func_80062338);
