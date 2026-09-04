// ItemObj, item_object_update_funcs[20]
// 800C4CE4..800C52CC
#include "common.h"

void func_800C4CE4(struct ItemObj* arg0)
{
    D_8010D234[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_20", func_800C4D20);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_20", func_800C4E78);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_20", func_800C4EC8);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_20", func_800C4F04);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_20", func_800C4F40);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_20", func_800C5058);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_20", func_800C5078);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_20", func_800C5210);

void (*D_8010D234[])(struct ItemObj*) = {
    func_800C4D20,
    func_800C4E78,
    func_800C5058,
};
