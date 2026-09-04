// ItemObj, item_object_update_funcs[0]
// 800BE9A0..800BEBB4
#include "common.h"

void func_800BE9A0(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_8010C148[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_00", func_800BE9E8);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_00", func_800BEB14);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_00", func_800BEB94);

void (*D_8010C148[])(struct ItemObj*) = {
    func_800BE9E8,
    func_800BEB14,
    func_800BEB94,
};
