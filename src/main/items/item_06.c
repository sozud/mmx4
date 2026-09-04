// ItemObj, item_object_update_funcs[6]
// 800C1390..800C16F0
#include "common.h"

void func_800C1390(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_8010CAA8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_06", func_800C13D8);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_06", func_800C14F0);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_06", func_800C1590);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_06", func_800C165C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_06", func_800C169C);

void (*D_8010CAA8[])(struct ItemObj*) = {
    func_800C13D8,
    func_800C14F0,
    func_800C1590,
    func_800C165C,
    func_800C169C,
};
