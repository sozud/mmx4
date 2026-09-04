// ItemObj, item_object_update_funcs[1]
// 800BEBB4..800BF730
#include "common.h"

void func_800BEBB4(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_8010C2F0[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_01", func_800BEBFC);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_01", func_800BED6C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_01", func_800BEED4);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_01", func_800BEFCC);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_01", func_800BF1FC);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_01", func_800BF508);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_01", func_800BF530);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_01", func_800BF5EC);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_01", func_800BF60C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_01", func_800BF638);

void (*D_8010C2F0[])(struct ItemObj*) = {
    func_800BEBFC,
    func_800BED6C,
    func_800BF530,
    func_800BF5EC,
};
