// ItemObj, item_object_update_funcs[7]
// 800C16F0..800C1994
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_07", func_800C16F0);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_07", func_800C1820);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_07", func_800C1938);

void func_800C1958(struct ItemObj* arg0)
{
    D_8010CB5C[arg0->base.state](arg0);
}

void (*D_8010CB5C[])(struct ItemObj*) = {
    func_800C16F0,
    func_800C1820,
    func_800C1938,
};
