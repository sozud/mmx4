// ItemObj, item_object_update_funcs[14]
// 800C3880..800C3CF8
#include "common.h"

void func_800C3880(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_8010D040[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_14", func_800C38C8);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_14", func_800C39AC);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_14", func_800C3A0C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_14", func_800C3A20);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_14", func_800C3A40);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_14", func_800C3A7C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_14", func_800C3AD4);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_14", func_800C3B40);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_14", func_800C3BA4);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_14", func_800C3C9C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_14", func_800C3CE4);

void (*D_8010D040[])(struct ItemObj*) = {
    func_800C38C8,
    func_800C39AC,
    func_800C3A0C,
    func_800C3A20,
};
