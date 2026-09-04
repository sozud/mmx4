// ItemObj, item_object_update_funcs[15]
// 800C3CF8..800C3FEC
#include "common.h"

void func_800C3CF8(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->base.x_pos.val;
    arg0->unk1C.val = arg0->base.y_pos.val;
    D_8010D070[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_15", func_800C3D40);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_15", func_800C3E4C);

INCLUDE_ASM("asm/us/main/nonmatchings/items/item_15", func_800C3F98);

void (*D_8010D070[])(struct ItemObj*) = {
    func_800C3D40,
    func_800C3E4C,
    func_800C3F98,
};
