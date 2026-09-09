// ItemObj, item_object_update_funcs[9]
// 800C20AC..800C24E0
#include "common.h"

void func_800C20AC(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010CC94[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_09", func_800C20F4);

INCLUDE_ASM("main/nonmatchings/items/item_09", func_800C229C);

void func_800C24C0(struct ItemObj* arg0)
{
    arg0->on_screen = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void (*D_8010CC94[])(struct ItemObj*) = {
    func_800C20F4,
    func_800C229C,
    func_800C24C0,
};
