// ItemObj, item_object_update_funcs[0]
// 800BE9A0..800BEBB4
#include "common.h"

void func_800BE9A0(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010C148[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_00", func_800BE9E8);

void func_800BEB14(struct ItemObj* arg0)
{
    u8 var_a0;

    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        func_800C813C(7, D_8010C158, arg0);
        var_a0 = 7;
        if (arg0->unk2 == 0) {
            var_a0 = 2;
        }
        func_800DABE4(var_a0, (s16)(arg0->x_pos.u.hi - 0x20),
            (s16)(arg0->y_pos.u.hi - 0x18));
        arg0->state = 2;
    }
}

void func_800BEB94(struct ItemObj* arg0)
{
    func_8002B108(OBJECT_HEADER(arg0));
}

void (*D_8010C148[])(struct ItemObj*) = {
    func_800BE9E8,
    func_800BEB14,
    func_800BEB94,
};

u8 D_8010C154[4] = { 0xE0, 0xE8, 0x40, 0x30 };
u8 D_8010C158[8] = { 0, 1, 2, 3, 4, 5, 6, 0 };
