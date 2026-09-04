// ItemObj, item_object_update_funcs[27]
// 800C7164..800C7A68
#include "common.h"

void func_800C7164(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_8010D990[arg0->base.state](arg0);
    func_8002E184(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_27", func_800C71C0);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_27", func_800C7460);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_27", func_800C74D4);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_27", func_800C7538);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_27", func_800C7558);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_27", func_800C7578);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_27", func_800C7648);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_27", func_800C76A4);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_27", func_800C76E0);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_27", func_800C7754);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_27", func_800C77BC);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_27", func_800C7830);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_27", func_800C785C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_27", func_800C78BC);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_27", func_800C7970);

void (*D_8010D990[])(struct ItemObj*) = {
    func_800C71C0,
    func_800C7460,
    func_800C74D4,
    func_800C7538,
    func_800C7558,
};
