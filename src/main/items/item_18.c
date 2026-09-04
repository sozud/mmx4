// ItemObj, item_object_update_funcs[18]
// 800C4544..800C470C
#include "common.h"

void func_800C4544(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_8010D1CC[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_18", func_800C458C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_18", func_800C460C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_18", func_800C4678);

void (*D_8010D1CC[])(struct ItemObj*) = {
    func_800C458C,
    func_800C460C,
    func_800C4678,
};
