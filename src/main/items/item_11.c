// ItemObj, item_object_update_funcs[11]
// 800C2BE0..800C3224
#include "common.h"

void func_800C2BE0(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010CFAC[arg0->state](arg0);
    func_8002E184(arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_11", func_800C2C3C);

INCLUDE_ASM("main/nonmatchings/items/item_11", func_800C2D6C);

void func_800C2DE0(struct ItemObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_800C2E00(struct ItemObj* arg0)
{
    is_on_screen(BASE_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/items/item_11", func_800C2E20);

INCLUDE_ASM("main/nonmatchings/items/item_11", func_800C2EAC);

void func_800C2F18(struct ItemObj* arg0)
{
    D_8010CFD0[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_11", func_800C2F54);

INCLUDE_ASM("main/nonmatchings/items/item_11", func_800C3030);

INCLUDE_ASM("main/nonmatchings/items/item_11", func_800C3114);

void func_800C3198(struct ItemObj* arg0)
{
    if (++arg0->unk84.timer == 0x32) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/items/item_11", func_800C31C4);

void (*D_8010CFAC[])(struct ItemObj*) = {
    func_800C2C3C,
    func_800C2D6C,
    func_800C2DE0,
    func_800C2E00,
};
