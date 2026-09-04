// ItemObj, item_object_update_funcs[2]
// 800BF730..800C0404
#include "common.h"

void func_800BF730(struct ItemObj* arg0)
{
    D_8010C730[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_02", func_800BF76C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_02", func_800BFA00);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_02", func_800BFB90);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_02", func_800BFBB0);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_02", func_800BFBD0);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_02", func_800BFCC0);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_02", func_800BFF0C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_02", func_800C00BC);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_02", func_800C03BC);

void (*D_8010C730[])(struct ItemObj*) = {
    func_800BF76C,
    func_800BFA00,
    func_800BFB90,
    func_800BFBB0,
};
