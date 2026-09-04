// ItemObj, item_object_update_funcs[9]
// 800C20AC..800C24E0
#include "common.h"

void func_800C20AC(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_8010CC94[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_09", func_800C20F4);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_09", func_800C229C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_09", func_800C24C0);

void (*D_8010CC94[])(struct ItemObj*) = {
    func_800C20F4,
    func_800C229C,
    func_800C24C0,
};
