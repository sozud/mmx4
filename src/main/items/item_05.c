// ItemObj, item_object_update_funcs[5]
// 800C0E74..800C1390
#include "common.h"

void func_800C0E74(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_8010CA9C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_05", func_800C0EBC);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_05", func_800C1050);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_05", func_800C1224);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_05", func_800C1244);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_05", func_800C1318);

void (*D_8010CA9C[])(struct ItemObj*) = {
    func_800C0EBC,
    func_800C1050,
    func_800C1224,
};
