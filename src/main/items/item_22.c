// ItemObj, item_object_update_funcs[22]
// 800C5544..800C5C4C
#include "common.h"

void func_800C5544(struct ItemObj* arg0)
{
    D_8010D318[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_22", func_800C5580);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_22", func_800C56B4);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_22", func_800C56F0);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_22", func_800C5710);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_22", func_800C5774);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_22", func_800C580C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_22", func_800C5904);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_22", func_800C5994);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_22", func_800C5B5C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_22", func_800C5BCC);

void (*D_8010D318[])(struct ItemObj*) = {
    func_800C5580,
    func_800C56B4,
    func_800C56F0,
    func_800C5710,
};
