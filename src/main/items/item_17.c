// ItemObj, item_object_update_funcs[17]
// 800C413C..800C42EC
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_17", func_800C413C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_17", func_800C41C8);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_17", func_800C4290);

void func_800C42B0(struct ItemObj* arg0)
{
    D_8010D18C[arg0->base.state](arg0);
}

void (*D_8010D18C[])(struct ItemObj*) = {
    func_800C413C,
    func_800C41C8,
    func_800C4290,
};
